// gpuhost.h: the host side of f!(x) calls (the device side is gpu.h, which
// comes before this in a program with !-calls).
//
// gpu_call lays out an arena (control words, the task queue, lane states,
// the table of CPU functions the device knows, the root frame, the heap),
// starts lane 0 on the target, and dispatches the kernel until the root
// frame returns or a lane fails. The device reads the CPU heap in place
// through a buffer over it, so the arguments are not copied; the result is
// copied out of the arena into the CPU heap. On a failure, or with no GPU,
// the caller runs the call on the CPU.
//
// On Apple the kernel runs on Metal, reached through the Objective-C
// runtime (no extra link flags). BEND_GPU=sim runs it in a simulator on the
// CPU instead (the same code as C, lanes interleaved); BEND_GPU=off, or
// --gpu off, runs !-calls on the CPU. BEND_GPU_LOG=1 says what happened.

#include <dlfcn.h>
#include "gpu_src.h"

typedef struct { Fn f; KW l; } GpuFn;

typedef struct {
  const char *src;       // the generated device code (Metal gets gpu.h first)
  void (*sim)(KW *, KAU *, const KParams *, KW *, uint32_t);
  const GpuFn *fns;
} GpuProg;

#define GPU_OFF 0
#define GPU_METAL 1
#define GPU_SIM 2

static pthread_mutex_t gpu_lock = PTHREAD_MUTEX_INITIALIZER;
static int gpu_mode = -1;
static int gpu_log;
static KW *gpu_H;          // the arena
static size_t gpu_Hn;      // its bytes
static KAU *gpu_A;         // the control words
static size_t gpu_An;
static KW gpu_qcap = (KW)1 << 16;
static KW gpu_lanes, gpu_budget, gpu_fork;
static V *gpu_out;         // objects copied out so far (roots)
static size_t gpu_nout, gpu_capout;

static void gpu_note(const char *fmt, const char *s) {
  if (gpu_log) {
    fprintf(stderr, "bend gpu: ");
    fprintf(stderr, fmt, s);
    fprintf(stderr, "\n");
  }
}

static void gpu_hook(void) {
  if (gpu_nout) gc_scan(gpu_out, gpu_out + gpu_nout);
}

static long gpu_env(const char *name, long dflt) {
  const char *s = getenv(name);
  return s && *s ? strtol(s, NULL, 10) : dflt;
}

// Metal, through the Objective-C runtime
// --------------------------------------

#ifdef __APPLE__
typedef void *GId;
typedef void *GSel;
typedef struct { unsigned long w, h, d; } GSize;
static GId (*g_class)(const char *);
static GSel (*g_sel)(const char *);
static void *g_send;
static void *(*g_pool_push)(void);
static void (*g_pool_pop)(void *);
static GId g_dev, g_queue, g_pso, g_bufH, g_bufA, g_bufG;
static KW g_bufG_len;
static unsigned long g_tpg;

#define G_SEND(T) ((T)g_send)
static GId g_msg(GId o, const char *s) { return G_SEND(GId (*)(GId, GSel))(o, g_sel(s)); }

static const char *g_err_text(GId err) {
  if (!err) return "unknown error";
  GId d = g_msg(err, "localizedDescription");
  return d ? G_SEND(const char *(*)(GId, GSel))(d, g_sel("UTF8String")) : "unknown error";
}

static GId g_nocopy(void *p, size_t n) {
  return G_SEND(GId (*)(GId, GSel, void *, unsigned long, unsigned long, void *))(g_dev,
    g_sel("newBufferWithBytesNoCopy:length:options:deallocator:"), p, n, 0, NULL);
}

static int g_init(const GpuProg *prog) {
  void *objc = dlopen("/usr/lib/libobjc.A.dylib", RTLD_LAZY);
  void *mtl = dlopen("/System/Library/Frameworks/Metal.framework/Metal", RTLD_LAZY);
  void *fnd = dlopen("/System/Library/Frameworks/Foundation.framework/Foundation", RTLD_LAZY);
  if (!objc || !mtl || !fnd) { gpu_note("%s", "no Metal"); return 0; }
  g_class = (GId (*)(const char *))dlsym(objc, "objc_getClass");
  g_sel = (GSel (*)(const char *))dlsym(objc, "sel_registerName");
  g_send = dlsym(objc, "objc_msgSend");
  g_pool_push = (void *(*)(void))dlsym(objc, "objc_autoreleasePoolPush");
  g_pool_pop = (void (*)(void *))dlsym(objc, "objc_autoreleasePoolPop");
  GId (*create)(void) = (GId (*)(void))dlsym(mtl, "MTLCreateSystemDefaultDevice");
  if (!g_class || !g_sel || !g_send || !create || !g_pool_push) { gpu_note("%s", "no Metal"); return 0; }
  void *pool = g_pool_push();
  g_dev = create();
  if (!g_dev) { gpu_note("%s", "no GPU"); g_pool_pop(pool); return 0; }
  size_t nh = strlen(K_GPU_H), np = strlen(prog->src);
  char *text = malloc(nh + np + 1);
  memcpy(text, K_GPU_H, nh);
  memcpy(text + nh, prog->src, np + 1);
  GId src = G_SEND(GId (*)(GId, GSel, const char *))(g_class("NSString"), g_sel("stringWithUTF8String:"), text);
  free(text);
  GId opts = g_msg(g_msg(g_class("MTLCompileOptions"), "alloc"), "init");
  G_SEND(void (*)(GId, GSel, unsigned long))(opts, g_sel("setLanguageVersion:"), (3ul << 16) | 2);
  G_SEND(void (*)(GId, GSel, signed char))(opts, g_sel("setFastMathEnabled:"), 0);
  GId err = NULL;
  GId lib = G_SEND(GId (*)(GId, GSel, GId, GId, GId *))(g_dev, g_sel("newLibraryWithSource:options:error:"), src,
    opts, &err);
  if (!lib) { gpu_note("the kernel does not compile: %s", g_err_text(err)); g_pool_pop(pool); return 0; }
  GId name = G_SEND(GId (*)(GId, GSel, const char *))(g_class("NSString"), g_sel("stringWithUTF8String:"),
    "bend_kernel");
  GId fn = G_SEND(GId (*)(GId, GSel, GId))(lib, g_sel("newFunctionWithName:"), name);
  err = NULL;
  g_pso = fn ? G_SEND(GId (*)(GId, GSel, GId, GId *))(g_dev, g_sel("newComputePipelineStateWithFunction:error:"), fn,
    &err) : NULL;
  if (!g_pso) { gpu_note("no pipeline: %s", g_err_text(err)); g_pool_pop(pool); return 0; }
  g_tpg = G_SEND(unsigned long (*)(GId, GSel))(g_pso, g_sel("maxTotalThreadsPerThreadgroup"));
  if (g_tpg > 256) g_tpg = 256;
  g_queue = g_msg(g_dev, "newCommandQueue");
  g_bufH = g_nocopy(gpu_H, gpu_Hn);
  g_bufA = g_nocopy(gpu_A, gpu_An);
  g_pool_pop(pool);
  if (!g_queue || !g_bufH || !g_bufA) { gpu_note("%s", "no buffers"); return 0; }
  return 1;
}

// One dispatch of every lane; 0 when the GPU failed.
static int g_dispatch(const KParams *P) {
  void *pool = g_pool_push();
  GId cb = g_msg(g_queue, "commandBuffer");
  GId enc = g_msg(cb, "computeCommandEncoder");
  G_SEND(void (*)(GId, GSel, GId))(enc, g_sel("setComputePipelineState:"), g_pso);
  void (*set)(GId, GSel, GId, unsigned long, unsigned long) = G_SEND(void (*)(GId, GSel, GId, unsigned long,
    unsigned long));
  set(enc, g_sel("setBuffer:offset:atIndex:"), g_bufH, 0, 0);
  set(enc, g_sel("setBuffer:offset:atIndex:"), g_bufA, 0, 1);
  G_SEND(void (*)(GId, GSel, const void *, unsigned long, unsigned long))(enc, g_sel("setBytes:length:atIndex:"), P,
    sizeof(KParams), 2);
  set(enc, g_sel("setBuffer:offset:atIndex:"), g_bufG, 0, 3);
  GSize grid = {(unsigned long)P->nlanes, 1, 1}, tg = {g_tpg, 1, 1};
  G_SEND(void (*)(GId, GSel, GSize, GSize))(enc, g_sel("dispatchThreads:threadsPerThreadgroup:"), grid, tg);
  g_msg(enc, "endEncoding");
  g_msg(cb, "commit");
  g_msg(cb, "waitUntilCompleted");
  unsigned long st = G_SEND(unsigned long (*)(GId, GSel))(cb, g_sel("status"));
  if (st != 4) gpu_note("a dispatch failed: %s", g_err_text(g_msg(cb, "error")));
  g_pool_pop(pool);
  return st == 4;
}

// A buffer over the CPU heap in use, for the device to read.
static int g_heap(void) {
  KW len = (KW)gc_top << GC_BLK_SHIFT;
  if (len == 0) len = (KW)1 << GC_BLK_SHIFT;
  if (g_bufG && g_bufG_len == len) return 1;
  if (g_bufG) g_msg(g_bufG, "release");
  g_bufG = g_nocopy(gc_base, len);
  g_bufG_len = len;
  return g_bufG != NULL;
}
#endif

// The arena and the run
// ---------------------

static int gpu_setup(const GpuProg *prog) {
  const char *m = getenv("BEND_GPU");
  gpu_log = getenv("BEND_GPU_LOG") != NULL;
  if (!bend_gpu || (m && strcmp(m, "off") == 0)) return GPU_OFF;
  int sim = m && strcmp(m, "sim") == 0;
#ifndef __APPLE__
  if (!sim) return GPU_OFF;
#endif
  gpu_Hn = (size_t)gpu_env("BEND_GPU_MB", 1024) << 20;
  gpu_H = mmap(NULL, gpu_Hn, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
  gpu_An = ((KA_SEQ + gpu_qcap) * sizeof(KAU) + 0xffff) & ~(size_t)0xffff;
  gpu_A = mmap(NULL, gpu_An, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
  if (gpu_H == MAP_FAILED || gpu_A == MAP_FAILED) return GPU_OFF;
  gpu_lanes = (KW)gpu_env("BEND_GPU_LANES", sim ? 64 : 8192);
  gpu_budget = (KW)gpu_env("BEND_GPU_STEPS", sim ? 37 : 16384);
  KW f = 0;
  while (((KW)1 << f) < gpu_lanes) f++;
  gpu_fork = (KW)gpu_env("BEND_GPU_FORK", (long)f + 2);
  pthread_mutex_lock(&gc_lock);
  gc_hook(gpu_hook);
  pthread_mutex_unlock(&gc_lock);
  if (sim) return GPU_SIM;
#ifdef __APPLE__
  if (g_init(prog)) return GPU_METAL;
#endif
  return GPU_OFF;
}

static void gpu_keep(V v) {
  if (gpu_nout == gpu_capout) {
    gpu_capout = gpu_capout ? gpu_capout * 2 : 1024;
    gpu_out = realloc(gpu_out, gpu_capout * sizeof(V));
  }
  gpu_out[gpu_nout++] = v;
}

#define GPU_FWD ((KW)1 << 63)
#define KIX_H(P, v) (((v) - (P)->ab) >> 3)
#define GPU_SEEN ((KW)1 << 62)

// Copies the arena objects reachable from v into the CPU heap, children
// first (a parent is never older than its children), and answers the copy
// of v. 0 when an object has no CPU form (a closure of a lambda).
static int gpu_copy_out(const GpuProg *prog, const KParams *P, KW v, V *out) {
  KW lo = P->ab + ((P->heap0 + 1) << 3), hi = P->ab + ((P->heap0 + P->heapw) << 3);
#define GPU_OBJ(w) ((w) >= lo && (w) < hi && ((w) & 7) == 0)
  if (!GPU_OBJ(v)) { *out = v; return 1; }
  size_t cap = 1024, sp = 0;
  KW *stk = malloc(cap * sizeof(KW));
  stk[sp++] = v;
  int ok = 1;
  while (sp > 0 && ok) {
    KW o = stk[sp - 1];
    KW i = KIX_H(P, o);
    KW h = gpu_H[i - 1];
    if (h & GPU_FWD) { sp--; continue; }
    if (!(h & GPU_SEEN)) {
      // First visit: push the children.
      gpu_H[i - 1] = h | GPU_SEEN;
      for (KW k = 0; k < h; k++) {
        KW w = gpu_H[i + k];
        if (GPU_OBJ(w) && !(gpu_H[KIX_H(P, w) - 1] & (GPU_FWD | GPU_SEEN))) {
          if (sp == cap) { cap *= 2; stk = realloc(stk, cap * sizeof(KW)); }
          stk[sp++] = w;
        }
      }
      continue;
    }
    // Second visit: the children are copied.
    KW n = h & ~GPU_SEEN;
    V *p = halloc(n);
    for (KW k = 0; k < n; k++) {
      KW w = gpu_H[i + k];
      if (k == 0 && (w >> 52) == 0x7ff) {
        Fn fn = NULL;
        for (const GpuFn *e = prog->fns; e->f; e++) {
          if (e->l == (w & 0xffffffffu)) fn = e->f;
        }
        if (!fn) { ok = 0; gpu_note("%s", "the value holds a function the CPU has no code for"); break; }
        w = (V)fn;
      } else if (GPU_OBJ(w)) {
        KW hw = gpu_H[KIX_H(P, w) - 1];
        if (!(hw & GPU_FWD)) { ok = 0; break; }
        w = hw & ~GPU_FWD;
      }
      p[k] = w;
    }
    gpu_keep((V)p);
    gpu_H[i - 1] = GPU_FWD | (KW)p;
    sp--;
  }
  free(stk);
  if (ok) *out = (V)(gpu_H[KIX_H(P, v) - 1] & ~GPU_FWD);
  return ok;
#undef GPU_OBJ
}

// Runs target entry on args; 0 when the caller must run it on the CPU.
static int gpu_run(const GpuProg *prog, KW entry, V *args, int n, V *out) {
  KParams P;
  memset(&P, 0, sizeof P);
  KW *H = gpu_H;
  KW nfn = 0;
  while (prog->fns[nfn].f) nfn++;
  P.ab = (KW)(uintptr_t)gpu_H;
  P.an = gpu_Hn;
  P.gb = (KW)(uintptr_t)gc_base;
  P.qcap = gpu_qcap;
  P.qd = 16;
  P.lane0 = P.qd + 4 * P.qcap;
  P.fn0 = P.lane0 + K_LANE * gpu_lanes;
  P.nfn = nfn;
  KW rf = P.fn0 + 2 * nfn + 1;
  KW fs = k_frame_size(entry);
  P.q0 = (rf + fs + 63) / 64 * 64;
  P.heap0 = (P.q0 + KR_WORDS * gpu_lanes + K_CHUNK) / K_CHUNK * K_CHUNK;
  P.heapw = gpu_Hn / 8 - P.heap0;
  P.budget = gpu_budget;
  P.nlanes = gpu_lanes;
  P.fork_limit = gpu_fork;
  // Control words and queue.
  memset(gpu_A, 0, (KA_SEQ + P.qcap) * sizeof(KAU));
  gpu_A[KA_HEAP] = 1;
  for (KW i = 0; i < P.qcap; i++) gpu_A[KA_SEQ + i] = (KAU)i;
  memset(H, 0, P.qd * 8);  // the queue's data is written before it is read
  memset(H + P.lane0, 0, K_LANE * gpu_lanes * 8);
  for (KW i = 0; i < nfn; i++) {
    H[P.fn0 + 2 * i] = (KW)(uintptr_t)prog->fns[i].f;
    H[P.fn0 + 2 * i + 1] = prog->fns[i].l;
  }
  // The root frame, and lane 0 at the target's entry.
  H[rf - 1] = fs;
  H[rf] = PC_ROOT;
  H[rf + 1] = 0;
  H[rf + 2] = 0;
  H[rf + 3] = fs;
  for (int i = 0; i < n; i++) H[rf + 4 + i] = args[i];
  H[P.lane0] = entry;
  H[P.lane0 + 1] = rf;
  __atomic_thread_fence(__ATOMIC_SEQ_CST);
  KW rounds = 0;
  for (;;) {
    if (gpu_mode == GPU_SIM) {
      for (KW l = 0; l < gpu_lanes; l++) prog->sim(H, gpu_A, &P, (KW *)gc_base, (uint32_t)l);
    }
#ifdef __APPLE__
    else if (!g_heap() || !g_dispatch(&P)) {
      return 0;
    }
#endif
    rounds++;
    if (__atomic_load_n(&gpu_A[KA_ERR], __ATOMIC_SEQ_CST) != 0) {
      if (gpu_log) fprintf(stderr, "bend gpu: a lane failed (error %u), running on the CPU\n", gpu_A[KA_ERR]);
      return 0;
    }
    if (__atomic_load_n(&gpu_A[KA_DONE], __ATOMIC_SEQ_CST) != 0) break;
  }
  if (gpu_log) {
    fprintf(stderr, "bend gpu: done in %llu dispatches, %llu MB of arena\n", (unsigned long long)rounds,
      (unsigned long long)((KW)gpu_A[KA_HEAP] * K_CHUNK * 8 >> 20));
  }
  gpu_nout = 0;
  int ok = gpu_copy_out(prog, &P, H[2], out);
  gpu_nout = 0;
  return ok;
}

static int gpu_call(const GpuProg *prog, KW entry, V *args, int n, V *out) {
  pthread_mutex_lock(&gpu_lock);
  if (gpu_mode < 0) gpu_mode = gpu_setup(prog);
  int ok = gpu_mode != GPU_OFF && gpu_run(prog, entry, args, n, out);
  pthread_mutex_unlock(&gpu_lock);
  return ok;
}
