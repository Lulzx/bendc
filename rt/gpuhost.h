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
// runtime (no extra link flags: this file asks the linker for Metal).
// BEND_GPU=sim runs it in a simulator on the CPU instead (the same code as
// C, lanes interleaved); BEND_GPU=off, or --gpu off, runs !-calls on the
// CPU. BEND_GPU_LOG=1 says what happened.

#include <dlfcn.h>
#include <limits.h>
#include <sys/stat.h>
#include "gpu_src.h"

typedef struct { Fn f; KW l; } GpuFn;

typedef struct {
  const char *src;       // the generated device code (Metal gets gpu.h first)
  void (*sim)(KW *, KAU *, const KParams *, KW *, uint32_t);
  void (*sim_kq)(KW *, KAU *, const KParams *, KW *, uint32_t);
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
static size_t gpu_Hmax;    // the most it grows to (BEND_GPU_MB)
static KAU *gpu_A;         // the control words
static size_t gpu_An;
static KW gpu_qcap = (KW)1 << 16;
static KW gpu_lanes, gpu_budget, gpu_fork;
static KW gpu_qused;       // queue slots the last call used
static int gpu_used;       // the arena holds a call's lane states
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
// Metal is linked (weakly, so a Mac without it still runs the program): the
// loader maps it with the program for less memory than dlopen at the first
// call (15 MB against 18).
__asm__(".linker_option \"-framework\", \"Metal\"");
extern void *MTLCreateSystemDefaultDevice(void) __attribute__((weak_import));
typedef void *GId;
typedef void *GSel;
typedef struct { unsigned long w, h, d; } GSize;
static GId (*g_class)(const char *);
static GSel (*g_sel)(const char *);
static void *g_send;
static void *(*g_pool_push)(void);
static void (*g_pool_pop)(void *);
static GId g_dev, g_queue, g_pso, g_pso_kq, g_bufH, g_bufA, g_bufG;
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

// An NSString of a C string.
static GId g_str(const char *s) {
  return G_SEND(GId (*)(GId, GSel, const char *))(g_class("NSString"), g_sel("stringWithUTF8String:"), s);
}

static GId g_new(const char *cls) { return g_msg(g_msg(g_class(cls), "alloc"), "init"); }

// The device code's hash, which names its file in the cache.
static unsigned long long g_hash(const GpuProg *prog) {
  unsigned long long h = 0xcbf29ce484222325ull;
  for (const char *t = K_GPU_H; *t; t++) h = (h ^ (unsigned char)*t) * 0x100000001b3ull;
  for (const char *t = prog->src; *t; t++) h = (h ^ (unsigned char)*t) * 0x100000001b3ull;
  return h;
}

// ~/Library/Caches/bend/<hash>.gpu: Metal's binary archive of the two
// pipelines, which the first run writes (with dir, makes the directory).
static int g_cache_path(char *out, size_t n, unsigned long long h, int dir) {
  const char *home = getenv("HOME");
  if (!home || !*home) return 0;
  if (dir) {
    snprintf(out, n, "%s/Library/Caches/bend", home);
    mkdir(out, 0755);
  }
  return snprintf(out, n, "%s/Library/Caches/bend/%016llx.gpu", home, h) < (int)n;
}

static GId g_url(const char *path) {
  return G_SEND(GId (*)(GId, GSel, GId))(g_class("NSURL"), g_sel("fileURLWithPath:"), g_str(path));
}

// Compiles the device code: the library, or NULL.
static GId g_compile(const GpuProg *prog) {
  size_t nh = strlen(K_GPU_H), np = strlen(prog->src);
  char *text = malloc(nh + np + 1);
  memcpy(text, K_GPU_H, nh);
  memcpy(text + nh, prog->src, np + 1);
  GId src = g_str(text);
  free(text);
  GId opts = g_new("MTLCompileOptions");
  G_SEND(void (*)(GId, GSel, unsigned long))(opts, g_sel("setLanguageVersion:"), (3ul << 16) | 2);
  G_SEND(void (*)(GId, GSel, signed char))(opts, g_sel("setFastMathEnabled:"), 0);
  GId err = NULL;
  GId lib = G_SEND(GId (*)(GId, GSel, GId, GId, GId *))(g_dev, g_sel("newLibraryWithSource:options:error:"), src,
    opts, &err);
  if (!lib) gpu_note("the kernel does not compile: %s", g_err_text(err));
  return lib;
}

// A pipeline descriptor for kernel name of lib, or NULL.
static GId g_desc(GId lib, const char *name) {
  GId fn = G_SEND(GId (*)(GId, GSel, GId))(lib, g_sel("newFunctionWithName:"), g_str(name));
  if (!fn) return NULL;
  GId d = g_new("MTLComputePipelineDescriptor");
  G_SEND(void (*)(GId, GSel, GId))(d, g_sel("setComputeFunction:"), fn);
  return d;
}

// The pipeline of d, from archive ar when it is not NULL (else err says why).
static GId g_pipe(GId d, GId ar, GId *err) {
  if (ar) {
    GId arr = G_SEND(GId (*)(GId, GSel, GId))(g_class("NSArray"), g_sel("arrayWithObject:"), ar);
    G_SEND(void (*)(GId, GSel, GId))(d, g_sel("setBinaryArchives:"), arr);
  }
  GId pso = G_SEND(GId (*)(GId, GSel, GId, unsigned long, void *, GId *))(g_dev,
    g_sel("newComputePipelineStateWithDescriptor:options:reflection:error:"), d, ar ? 4ul : 0ul, NULL, err);
  if (!pso && !ar) gpu_note("no pipeline: %s", g_err_text(*err));
  return pso;
}

// The pipelines from the cache, which holds the compiled library and the
// GPU's code for it: loading them costs less time and memory than compiling
// (1 MB against 2.5). An archive for another GPU or OS misses, and the
// pipelines compile again.
static int g_load(unsigned long long h) {
  char path[PATH_MAX];
  if (!g_cache_path(path, sizeof path, h, 0) || access(path, R_OK) != 0) return 0;
  GId url = g_url(path), err = NULL;
  GId lib = G_SEND(GId (*)(GId, GSel, GId, GId *))(g_dev, g_sel("newLibraryWithURL:error:"), url, &err);
  GId d = lib ? g_desc(lib, "bend_kernel") : NULL;
  GId d_kq = lib ? g_desc(lib, "bend_kq") : NULL;
  GId ad = g_new("MTLBinaryArchiveDescriptor");
  G_SEND(void (*)(GId, GSel, GId))(ad, g_sel("setUrl:"), url);
  GId ar = d && d_kq ? G_SEND(GId (*)(GId, GSel, GId, GId *))(g_dev, g_sel("newBinaryArchiveWithDescriptor:error:"),
    ad, &err) : NULL;
  g_pso = ar ? g_pipe(d, ar, &err) : NULL;
  g_pso_kq = g_pso ? g_pipe(d_kq, ar, &err) : NULL;
  if (!g_pso || !g_pso_kq) gpu_note("the cached GPU code does not load (%s): compiling", g_err_text(err));
  return g_pso && g_pso_kq;
}

// Writes the archive of pipeline descriptors d and d_kq to the cache (to a
// file of this process, then renamed, so a run never reads half of one).
static void g_save(unsigned long long h, GId d, GId d_kq) {
  char path[PATH_MAX], tmp[PATH_MAX + 32];
  if (!g_cache_path(path, sizeof path, h, 1)) return;
  snprintf(tmp, sizeof tmp, "%s.%d", path, (int)getpid());
  GId err = NULL;
  GId ar = G_SEND(GId (*)(GId, GSel, GId, GId *))(g_dev, g_sel("newBinaryArchiveWithDescriptor:error:"),
    g_new("MTLBinaryArchiveDescriptor"), &err);
  signed char (*add)(GId, GSel, GId, GId *) = G_SEND(signed char (*)(GId, GSel, GId, GId *));
  int ok = ar && add(ar, g_sel("addComputePipelineFunctionsWithDescriptor:error:"), d, &err) &&
    add(ar, g_sel("addComputePipelineFunctionsWithDescriptor:error:"), d_kq, &err) &&
    add(ar, g_sel("serializeToURL:error:"), g_url(tmp), &err) && rename(tmp, path) == 0;
  if (!ok) {
    unlink(tmp);
    gpu_note("cannot cache the GPU code: %s", g_err_text(err));
  }
}

static int g_open(void) {
  void *objc = dlopen("/usr/lib/libobjc.A.dylib", RTLD_LAZY);
  if (!objc || !MTLCreateSystemDefaultDevice) { gpu_note("%s", "no Metal"); return 0; }
  g_class = (GId (*)(const char *))dlsym(objc, "objc_getClass");
  g_sel = (GSel (*)(const char *))dlsym(objc, "sel_registerName");
  g_send = dlsym(objc, "objc_msgSend");
  g_pool_push = (void *(*)(void))dlsym(objc, "objc_autoreleasePoolPush");
  g_pool_pop = (void (*)(void *))dlsym(objc, "objc_autoreleasePoolPop");
  if (!g_class || !g_sel || !g_send || !g_pool_push) { gpu_note("%s", "no Metal"); return 0; }
  return 1;
}

static int g_init(const GpuProg *prog) {
  if (!g_open()) return 0;
  void *pool = g_pool_push();
  g_dev = MTLCreateSystemDefaultDevice();
  if (!g_dev) { gpu_note("%s", "no GPU"); g_pool_pop(pool); return 0; }
  unsigned long long h = g_hash(prog);
  if (!g_load(h)) {
    GId lib = g_compile(prog);
    GId d = lib ? g_desc(lib, "bend_kernel") : NULL;
    GId d_kq = lib ? g_desc(lib, "bend_kq") : NULL;
    GId err = NULL;
    g_pso = d ? g_pipe(d, NULL, &err) : NULL;
    g_pso_kq = d_kq ? g_pipe(d_kq, NULL, &err) : NULL;
    if (!g_pso || !g_pso_kq) { g_pool_pop(pool); return 0; }
    g_save(h, d, d_kq);
  }
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
static int g_dispatch(const KParams *P, GId pso) {
  void *pool = g_pool_push();
  GId cb = g_msg(g_queue, "commandBuffer");
  GId enc = g_msg(cb, "computeCommandEncoder");
  G_SEND(void (*)(GId, GSel, GId))(enc, g_sel("setComputePipelineState:"), pso);
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
  // The arena starts small (a dispatch's first use of a buffer costs with its
  // size: 30 ms for 1 GB) and grows when a call fills it (see gpu_call).
  gpu_Hmax = (size_t)gpu_env("BEND_GPU_MB", 4096) << 20;
  gpu_Hn = gpu_Hmax < ((size_t)64 << 20) ? gpu_Hmax : (size_t)64 << 20;
  gpu_H = mmap(NULL, gpu_Hn, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
  gpu_An = ((KA_SEQ + gpu_qcap) * sizeof(KAU) + 0xffff) & ~(size_t)0xffff;
  gpu_A = mmap(NULL, gpu_An, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
  if (gpu_H == MAP_FAILED || gpu_A == MAP_FAILED) return GPU_OFF;
  gpu_lanes = (KW)gpu_env("BEND_GPU_LANES", sim ? 64 : 8192);
  gpu_budget = (KW)gpu_env("BEND_GPU_STEPS", sim ? 37 : 16384);
  KW f = 0;
  while (((KW)1 << f) < gpu_lanes) f++;
  gpu_fork = (KW)gpu_env("BEND_GPU_FORK", (long)f);
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

// Runs target entry on args; 0 when the caller must run it on the CPU, 2 when
// the arena filled up (and may grow).
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
#ifdef KQ_SHARED
  P.q0 = (rf + fs + 63) / 64 * 64;
  P.heap0 = (P.q0 + KR_WORDS * gpu_lanes + K_CHUNK) / K_CHUNK * K_CHUNK;
#else
  P.heap0 = (rf + fs + K_CHUNK) / K_CHUNK * K_CHUNK;
#endif
  P.heapw = gpu_Hn / 8 - P.heap0;
  P.budget = gpu_budget;
  P.nlanes = gpu_lanes;
  P.fork_limit = gpu_fork;
  // Control words, the queue and the lane states start zero: fresh pages
  // are, so only what a call used is cleared (pages never touched cost no
  // memory).
  memset(gpu_A, 0, (KA_SEQ + gpu_qused) * sizeof(KAU));
  gpu_qused = 0;
  gpu_A[KA_HEAP] = 1;
  memset(H, 0, P.qd * 8);
  // A lane's other words are set before they are read.
  if (gpu_used) memset(H + P.lane0, 0, 10 * gpu_lanes * 8);
  gpu_used = 1;
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
  H[P.lane0 + gpu_lanes] = rf;
  __atomic_thread_fence(__ATOMIC_SEQ_CST);
  KW rounds = 0;
  for (;;) {
    // The lanes running (not idle, not waiting for bend_kq): idle lanes stay
    // in the dispatch while one does.
    KW active = 0, waiting = 0;
    for (KW l = 0; l < gpu_lanes; l++) {
      KW pc = H[P.lane0 + l];
      active += pc != PC_IDLE && pc != PC_KQ;
    }
    gpu_A[KA_ACTIVE] = (KAU)active;
    __atomic_thread_fence(__ATOMIC_SEQ_CST);
    if (gpu_mode == GPU_SIM) {
      for (KW l = 0; l < gpu_lanes; l++) prog->sim(H, gpu_A, &P, (KW *)gc_base, (uint32_t)l);
    }
#ifdef __APPLE__
    else if (!g_heap() || !g_dispatch(&P, g_pso)) {
      return 0;
    }
#endif
    rounds++;
    KW tail = gpu_A[KA_QTAIL];
    if (tail > gpu_qused) gpu_qused = tail < P.qcap ? tail : P.qcap;
    if (__atomic_load_n(&gpu_A[KA_ERR], __ATOMIC_SEQ_CST) != 0) break;
    if (__atomic_load_n(&gpu_A[KA_DONE], __ATOMIC_SEQ_CST) != 0) break;
    for (KW l = 0; l < gpu_lanes; l++) waiting += H[P.lane0 + l] == PC_KQ;
    if (waiting > 0) {
      if (gpu_mode == GPU_SIM) {
        for (KW l = 0; l < gpu_lanes; l++) prog->sim_kq(H, gpu_A, &P, (KW *)gc_base, (uint32_t)l);
      }
#ifdef __APPLE__
      else if (!g_dispatch(&P, g_pso_kq)) {
        return 0;
      }
#endif
      if (__atomic_load_n(&gpu_A[KA_ERR], __ATOMIC_SEQ_CST) != 0) break;
    } else if (active == 0 && gpu_A[KA_QHEAD] == gpu_A[KA_QTAIL]) {
      // Nothing runs, waits or is queued, and the root has not returned.
      gpu_note("%s", "the device stalled");
      return 0;
    }
  }
  if (__atomic_load_n(&gpu_A[KA_ERR], __ATOMIC_SEQ_CST) != 0) {
    if (gpu_A[KA_ERR] == KE_HEAP && gpu_Hn < gpu_Hmax) return 2;
    if (gpu_log) fprintf(stderr, "bend gpu: a lane failed (error %u), running on the CPU\n", gpu_A[KA_ERR]);
    return 0;
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

// A 4x bigger arena, for a call that filled this one.
static int gpu_grow(void) {
  size_t n = gpu_Hn * 4 > gpu_Hmax ? gpu_Hmax : gpu_Hn * 4;
  KW *h = mmap(NULL, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
  if (h == MAP_FAILED) return 0;
#ifdef __APPLE__
  if (gpu_mode == GPU_METAL) {
    GId b = g_nocopy(h, n);
    if (!b) { munmap(h, n); return 0; }
    g_msg(g_bufH, "release");
    g_bufH = b;
  }
#endif
  munmap(gpu_H, gpu_Hn);
  gpu_used = 0;
  gpu_H = h;
  gpu_Hn = n;
  if (gpu_log) fprintf(stderr, "bend gpu: arena grows to %llu MB\n", (unsigned long long)(n >> 20));
  return 1;
}

static int gpu_call(const GpuProg *prog, KW entry, V *args, int n, V *out) {
  // A bignum argument (bit 63): the device only has Nats below 2^63.
  for (int i = 0; i < n; i++) {
    if (args[i] >> 63) return 0;
  }
  pthread_mutex_lock(&gpu_lock);
  if (gpu_mode < 0) gpu_mode = gpu_setup(prog);
  int r = gpu_mode != GPU_OFF ? gpu_run(prog, entry, args, n, out) : 0;
  while (r == 2) r = gpu_grow() ? gpu_run(prog, entry, args, n, out) : 0;
  pthread_mutex_unlock(&gpu_lock);
  return r == 1;
}
