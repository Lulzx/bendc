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
// runtime, loaded at start (see g_preload): no extra link flags.
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
  const GpuFn *kqh;      // the KQ_ calls the host may run on the CPU (see gpu_kq_host)
} GpuProg;

#define GPU_OFF 0
#define GPU_METAL 1
#define GPU_SIM 2

static pthread_mutex_t gpu_lock = PTHREAD_MUTEX_INITIALIZER;
static KW gpu_kq_cpu;    // (see gpu_kq_host)
static KW gpu_kq_order;  // BEND_GPU_KQSORT: sort the waiting calls (see gpu_kq_sort)
static int gpu_mode = -1;
static int gpu_log;         // BEND_GPU_LOG: 1 for a line a call, 2 for more
static double gpu_tout;     // the last copy out's time (BEND_GPU_LOG)
static double gpu_secs[2];  // the device's time in the two kernels (BEND_GPU_LOG)
static KW *gpu_H;          // the arena
static size_t gpu_Hn;      // its bytes
static size_t gpu_Hmax;    // the most it grows to (BEND_GPU_MB), all of it reserved
static KW gpu_pin;          // the arena words below this hold results the CPU was given
static KW gpu_pin_min;      // the arena bytes a result's call used, for it to stay there
static KAU *gpu_A;         // the control words
static size_t gpu_An;
static KW gpu_qcap = (KW)1 << 16;
static KW gpu_lanes, gpu_budget, gpu_fork, gpu_kqep;
static KW gpu_qused;       // queue slots the last call used
static int gpu_used;       // the arena holds a call's lane states
static V *gpu_out;         // objects copied out so far (roots)
static size_t gpu_nout, gpu_capout;

static double gpu_now(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec + ts.tv_nsec * 1e-9;
}

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

// tcc cannot pass the linker Metal (nor weak imports): its programs have
// the simulator and the CPU.
#if defined(__APPLE__) && !defined(__TINYC__)
#define BEND_METAL 1
#else
#define BEND_METAL 0
#endif

#if BEND_METAL
// Metal is not linked: loading it costs about 4 MB of resident memory, which a
// run on the CPU would pay too. A run that may use the GPU loads it at start,
// by running the program again with Metal inserted
// (DYLD_INSERT_LIBRARIES): the loader then maps it as it maps linked
// libraries, for about 3 MB less than dlopen at the first call. Where the
// insertion is refused (a restricted process, say), g_open opens it.
#include <mach-o/dyld.h>
#define G_METAL "/System/Library/Frameworks/Metal.framework/Metal"
static void *(*MTLCreateSystemDefaultDevice)(void);
__attribute__((constructor)) static void g_preload(int argc, char **argv) {
  const char *m = getenv("BEND_GPU");
  if (getenv("BEND_METAL_PRELOAD")) {
    // (the second run: what programs it starts get neither variable)
    unsetenv("BEND_METAL_PRELOAD");
    unsetenv("DYLD_INSERT_LIBRARIES");
    return;
  }
  if ((m && (strcmp(m, "off") == 0 || strcmp(m, "sim") == 0)) || getenv("DYLD_INSERT_LIBRARIES")) return;
  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--") == 0) break;
    if (strcmp(argv[i], "--gpu") == 0 && i + 1 < argc && strcmp(argv[i + 1], "off") == 0) return;
    if (strcmp(argv[i], "--bend-help") == 0) return;
  }
  if (dlsym(RTLD_DEFAULT, "MTLCreateSystemDefaultDevice")) return;
  char path[PATH_MAX];
  uint32_t n = sizeof path;
  if (_NSGetExecutablePath(path, &n) != 0) return;
  setenv("DYLD_INSERT_LIBRARIES", G_METAL, 1);
  setenv("BEND_METAL_PRELOAD", "1", 1);
  execv(path, argv);
  unsetenv("DYLD_INSERT_LIBRARIES");
  unsetenv("BEND_METAL_PRELOAD");
}
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
static unsigned long long g_hint_hash;
static size_t g_hint_peak;

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

// A successful call teaches the next process its arena's initial size.
// Hints only affect growth: explicit sizes win, and malformed or stale
// hints are ignored. The code hash keeps unrelated programs separate.
static int g_hint_path(char *out, size_t n, unsigned long long h, int dir) {
  char base[PATH_MAX];
  return g_cache_path(base, sizeof base, h, dir) &&
    snprintf(out, n, "%s.arena", base) < (int)n;
}
static void g_hint_load(unsigned long long h) {
  if (getenv("BEND_GPU_MB0")) return;
  char path[PATH_MAX + 8];
  if (!g_hint_path(path, sizeof path, h, 0)) return;
  FILE *f = fopen(path, "r");
  if (!f) return;
  unsigned long long mb = 0; char end = 0;
  int ok = fscanf(f, "bend-arena-1 %llu%c", &mb, &end) == 2 && end == '\n' && fgetc(f) == EOF;
  fclose(f);
  if (!ok || mb < 64 || mb > (gpu_Hmax >> 20)) return;
  // (it wins over --gpu SIZE too, which only says how far the arena may
  // grow: a dispatch's first use of the arena's buffer costs with its size,
  // about 9 ms for 512 MB against 64 MB)
  gpu_Hn = (size_t)mb << 20;
  if (gpu_log == 2) fprintf(stderr, "bend gpu: arena hint %llu MB\n", mb);
}
static void g_hint_save(size_t need) {
  if (need <= g_hint_peak) return;
  g_hint_peak = need;
  // With room for the quarter gpu_run keeps free before it grows, in steps
  // of 64 MB (merkle's 276 MB took 512 MB in powers of 2, 448 MB this way).
  size_t step = (size_t)64 << 20;
  size_t n = (need + need / 3 + step - 1) / step * step;
  if (n > gpu_Hmax) n = gpu_Hmax;
  char path[PATH_MAX + 8], tmp[PATH_MAX + 40];
  if (!g_hint_path(path, sizeof path, g_hint_hash, 1)) return;
  snprintf(tmp, sizeof tmp, "%s.%d", path, (int)getpid());
  FILE *f = fopen(tmp, "w");
  if (!f) return;
  int ok = fprintf(f, "bend-arena-1 %llu\n", (unsigned long long)(n >> 20)) > 0;
  if (fclose(f) != 0) ok = 0;
  if (!ok || rename(tmp, path) != 0) unlink(tmp);
}

static GId g_url(const char *path) {
  return G_SEND(GId (*)(GId, GSel, GId))(g_class("NSURL"), g_sel("fileURLWithPath:"), g_str(path));
}

// Compiles the device code: the library, or NULL.
static GId g_compile(const GpuProg *prog) {
  size_t nh = strlen(K_GPU_H), np = strlen(prog->src);
  // (the program's leading flags, K_GPU_PACKED and K_FREE, go before gpu.h)
  size_t nz=0;
  for(;;) {
    const char* fl[]={"#define K_GPU_PACKED 1\n","#define K_FREE 1\n"};
    size_t k=0;
    for(int i=0;i<2;i++) if(strncmp(prog->src+nz,fl[i],strlen(fl[i]))==0) k=strlen(fl[i]);
    if(!k) break;
    nz+=k;
  }
  char *text = malloc(nz + nh + np + 1);
  if(nz)memcpy(text,prog->src,nz);
  memcpy(text+nz, K_GPU_H, nh);
  memcpy(text+nz+nh, prog->src, np + 1);
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
  MTLCreateSystemDefaultDevice = (void *(*)(void))dlsym(RTLD_DEFAULT, "MTLCreateSystemDefaultDevice");
  if (!MTLCreateSystemDefaultDevice) {
    void *mtl = dlopen(G_METAL, RTLD_LAZY);
    if (mtl) MTLCreateSystemDefaultDevice = (void *(*)(void))dlsym(mtl, "MTLCreateSystemDefaultDevice");
  }
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
  g_hint_hash = h;
  g_hint_load(h);
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
  double w0 = gpu_log ? gpu_now() : 0;
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
  if (gpu_log) {
    double (*tm)(GId, GSel) = G_SEND(double (*)(GId, GSel));
    double dt = tm(cb, g_sel("GPUEndTime")) - tm(cb, g_sel("GPUStartTime"));
    gpu_secs[pso != g_pso] += dt;
    if (gpu_log >= 2) fprintf(stderr, "bend gpu: %s %.4fs (%.4fs)\n", pso != g_pso ? "kq" : "main", dt, gpu_now() - w0);
  }
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
  const char *lv = getenv("BEND_GPU_LOG");
  gpu_log = lv == NULL ? 0 : lv[0] == '2' ? 2 : lv[0] == '3' ? 3 : 1;
  if (!bend_gpu || (m && strcmp(m, "off") == 0)) return GPU_OFF;
  int sim = m && strcmp(m, "sim") == 0;
#if !BEND_METAL
#ifdef __APPLE__
  if (!sim) gpu_note("%s", "no Metal");
#endif
  if (!sim) return GPU_OFF;
#endif
  // The arena starts small (a dispatch's first use of a buffer costs with its
  // size: 30-50 ms for 1 GB) and grows in place when a call fills it (see
  // gpu_grow): its most is reserved (untouched pages cost no memory).
  gpu_Hmax = (size_t)gpu_env("BEND_GPU_MB", 4096) << 20;
  size_t h0 = (size_t)gpu_env("BEND_GPU_MB0", 64) << 20;  // (smaller, to test the growth)
  gpu_Hn = gpu_Hmax < h0 ? gpu_Hmax : h0;
  if (bend_gpu_mb > 64) gpu_Hn = ((size_t)bend_gpu_mb << 20) < gpu_Hmax ? (size_t)bend_gpu_mb << 20 : gpu_Hmax;
  gpu_H = mmap(NULL, gpu_Hmax, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON | MAP_NORESERVE, -1, 0);
  gpu_An = ((KA_SEQ + gpu_qcap) * sizeof(KAU) + 0xffff) & ~(size_t)0xffff;
  gpu_A = mmap(NULL, gpu_An, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);
  if (gpu_H == MAP_FAILED || gpu_A == MAP_FAILED) return GPU_OFF;
  bend_arena_set((uintptr_t)gpu_H, gpu_Hmax);
  gpu_pin_min = (KW)gpu_env("BEND_GPU_PIN_MB", 32) << 20;
  gpu_lanes = (KW)gpu_env("BEND_GPU_LANES", sim ? 64 : 8192);
  // (the simulator runs every call on the device: it tests that code)
  gpu_kq_cpu = (KW)gpu_env("BEND_GPU_KQCPU", sim ? 0 : 4);
  gpu_kq_order = (KW)gpu_env("BEND_GPU_KQSORT", 1);
  gpu_budget = (KW)gpu_env("BEND_GPU_STEPS", sim ? 37 : 16384);
  KW f = 0;
  while (((KW)1 << f) < gpu_lanes) f++;
  gpu_fork = (KW)gpu_env("BEND_GPU_FORK", (long)f);
  pthread_mutex_lock(&gc_lock);
  gc_hook(gpu_hook);
  pthread_mutex_unlock(&gc_lock);
  if (sim) return GPU_SIM;
#if BEND_METAL
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
// of v. 0 when an object has no CPU form (a closure of a lambda). A narrow
// array (K_ARR_NW in rt/gpu.h: 32-bit scalar cells) becomes a CPU one.
#define GPU_NARROW(w) (((w) | 0x3f) == (ARR_TAG | 0x3f) && ((w) & K_ARR_NW))
static int gpu_copy_out(const GpuProg *prog, const KParams *P, KW v, V *out) {
  KW lo = P->ab + ((P->heap0 + 1) << 3), hi = P->ab + ((P->heap0 + P->heapw) << 3);
#define GPU_OBJ(w) ((w) >= lo && (w) < hi && ((w) & 7) == 0)
  // (counted, the copy holds a reference to each CPU object it reaches)
  // (marked first: another thread may hold what reaches it, see RC_TS)
  if (!GPU_OBJ(v)) { if (gc_hot.rc) rc_dup_in(v, 1); *out = v; return 1; }
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
      #ifdef K_GPU_PACKED
      if((h&K_PACK) && !(h&K_PACK_PTR))continue;
#endif
      if (!(h & (K_BARE|K_PACK)) && GPU_NARROW(gpu_H[i])) continue;
      for (KW k = 0; k < k_psize(h); k++) {
        KW w = gpu_H[i + k];
        if (GPU_OBJ(w) && !(gpu_H[KIX_H(P, w) - 1] & (GPU_FWD | GPU_SEEN))) {
          if (sp == cap) { cap *= 2; stk = realloc(stk, cap * sizeof(KW)); }
          stk[sp++] = w;
        }
      }
      continue;
    }
    // Second visit: the children are copied.
    // (a headerless node, K_BARE: its first word is a field, see k_bnode)
#ifdef K_GPU_PACKED
    if(h&K_PACK) {
      KW ar=K_PACK_AR(h);V*p=halloc(ar+1);p[0]=K_PACK_TAG(h);
      for(KW k=0;k<ar;k++) {
        KW w;
        if(h&K_PACK_PTR) {
          w=gpu_H[i+k];
          if(GPU_OBJ(w)) { KW hw=gpu_H[KIX_H(P,w)-1];if(!(hw&GPU_FWD)){ok=0;break;}w=hw&~GPU_FWD; }
          else if(gc_hot.rc)rc_dup_in(w,1);
        } else w=((KU*)(gpu_H+i))[k];
        p[k+1]=w;
      }
      gpu_keep((V)p);gpu_H[i-1]=GPU_FWD|(KW)p;sp--;continue;
    }
#endif
    int bare = (h & K_BARE) != 0;
    KW n = k_psize(h & ~GPU_SEEN);
    if (!bare && GPU_NARROW(gpu_H[i])) {
      unsigned d = (unsigned)(gpu_H[i] & 31);
      V *p = halloc(1 + ((size_t)1 << d));
      p[0] = ARR_HDR(d);
      const uint32_t *q = (const uint32_t *)&gpu_H[i + 1];
      for (size_t k = 0; k < (size_t)1 << d; k++) p[1 + k] = q[k];
      gpu_keep((V)p);
      gpu_H[i - 1] = GPU_FWD | (KW)p;
      sp--;
      continue;
    }
    V *p = bare ? halloc_b(n) : halloc(n);
    for (KW k = 0; k < n; k++) {
      KW w = gpu_H[i + k];
      if (k == 0 && !bare && (w >> 52) == 0x7ff) {
        Fn fn = NULL;
        for (const GpuFn *e = prog->fns; e->f; e++) {
          if (e->l == (w & 0xffffffffu)) fn = e->f;
        }
        if (!fn) { ok = 0; gpu_note("%s", "the value holds a function the CPU has no code for"); break; }
        w = (V)fn;
      } else if (k == 0 && !bare) {
        w &= RC_ADDR;  // (a word the device copied from a counted object: its count is not the copy's)
      } else if (GPU_OBJ(w)) {
        KW hw = gpu_H[KIX_H(P, w) - 1];
        if (!(hw & GPU_FWD)) { ok = 0; break; }
        w = hw & ~GPU_FWD;
      } else if (gc_hot.rc) {
        rc_dup_in(w, 1);
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
#undef GPU_NARROW
}

// A bigger arena (by f, a power of 2), for a call that filled this one: the
// reserved pages past it join it, so what it holds stays where it is.
static int gpu_grow(size_t f) {
  if (gpu_Hn >= gpu_Hmax) return 0;
  size_t n = gpu_Hn * f > gpu_Hmax ? gpu_Hmax : gpu_Hn * f;
#if BEND_METAL
  if (gpu_mode == GPU_METAL) {
    GId b = g_nocopy(gpu_H, n);
    if (!b) return 0;
    g_msg(g_bufH, "release");
    g_bufH = b;
  }
#endif
  gpu_Hn = n;
  if (gpu_log) fprintf(stderr, "bend gpu: arena grows to %llu MB\n", (unsigned long long)(n >> 20));
  return 1;
}

// Whether the CPU can have a call's result in place, in the arena: it reads
// it as its own (the objects are laid out alike), and the device too, when
// it is another call's argument. It must reach no closure (the device's
// hold labels, where the CPU has addresses) and no array (the CPU frees
// and reuses them), which its type says (pin, see Gen.gpu.pin in
// bendc.bend), and no object of the CPU's heap (its collector does not look
// into the arena), which it can only when an argument is one.
static int gpu_pinnable(int pin, V *args, int n) {
  uintptr_t gl = (uintptr_t)gc_base, gn = (uintptr_t)GC_MAXBLK << GC_BLK_SHIFT;
  for (int i = 0; i < n && pin; i++) pin = (uintptr_t)args[i] - gl >= gn;
  return pin;
}

// Runs target entry on args; 0 when the caller must run it on the CPU, 2 when
// the arena filled up (and may grow).
// Set while the host runs device calls on the CPU (gpu_kq_host): a !-call
// they make runs on the CPU too.
static int gpu_nest;

// When at most gpu_kq_cpu lanes wait for a KQ_ call (a serial tail: symreg's
// climb is 32 rounds of one chain, 0.17s on one lane) and each is one bendc
// lists in prog->kqh (scalar arguments and result), the host runs them on
// the CPU, where a serial chain runs far faster, and hands each lane its
// result as bend_kq would. 1 when it did.
//
// A call that could fork (its callees' parallel lets; the device runs them in
// order on the lane and, past K_KQSTEPS, gives up and forks through frames)
// is run on the CPU too, and that is always correct: F_name is the same pure
// def compiled for the CPU, and its value is the device's. Only speed is in
// question, and the CPU runtime runs such a call's parallel lets on its own
// threads, while the device would give a lone call one lane (or, past
// K_KQSTEPS, a restart through frames), so a few waiting calls are better
// off on the CPU either way. Its result is a scalar, so the lane keeps no
// pointer into the CPU's heap.
static int gpu_kq_host(const GpuProg *prog, KW *H, const KParams *P, KW waiting) {
  if (waiting > gpu_kq_cpu || prog->kqh == NULL) return 0;
  KW n = P->nlanes;
  Fn fs[64];
  KW ls[64], k = 0;
  for (KW l = 0; l < gpu_lanes; l++) {
    if (H[P->lane0 + l] != PC_KQ) continue;
    KW kq = H[P->lane0 + 7 * n + l];
    Fn f = NULL;
    for (const GpuFn *e = prog->kqh; e->f; e++) {
      if (e->l == kq) f = e->f;
    }
    if (f == NULL || k == 64) return 0;
    fs[k] = f;
    ls[k++] = l;
  }
  gpu_nest = 1;
  for (KW i = 0; i < k; i++) {
    KW l = ls[i];
    V a[KQ_ARGS];
    for (int j = 0; j < KQ_ARGS; j++) a[j] = H[P->lane0 + (10 + j) * n + l];
    H[P->lane0 + 2 * n + l] = fs[i](a);
    H[P->lane0 + l] = H[P->lane0 + 8 * n + l];
  }
  gpu_nest = 0;
  if (gpu_log == 2) fprintf(stderr, "bend gpu: kq ran %llu calls on the CPU\n", (unsigned long long)k);
  return 1;
}

// The waiting calls in order of their def and arguments, before the device
// runs them: a SIMD group runs its lanes' calls in step, and calls with the
// same def and leading arguments tend to take the same branches (raytrace's
// column quarters: pixels past the width, or not, alike across the group).
// Only the dispatch order changes. Each thread loads and saves the original
// lane's context, so the host need not read or move its heap/frame state.
//
// The def and the first two arguments order the calls, ties in lane order:
// a stable radix sort by each that differs somewhere, the last first, in
// 11-bit digits over the bits that differ. (A qsort comparing the lane
// states in place cost kmeans, which sorts 8192 calls 400 times, 0.3 s of
// the host's; and each key read is 64 KB of the arena the host touches,
// resident memory a run pays for.)
#define GPU_KS_MAX 3
static void gpu_kq_sort(KW *H, KParams *P, KW waiting) {
  KW n = P->nlanes, k = 0;
  KW *ix = malloc(2 * waiting * sizeof(KW));
  if (!ix) return;
  KW *t = ix + waiting, *base = ix;
  KW *L = H + P->lane0;
  for (KW l = 0; l < n && k < waiting; l++) {
    if (L[l] == PC_KQ) ix[k++] = l;
  }
  const KW *col[GPU_KS_MAX];
  KW diff[GPU_KS_MAX];
  int nv = 0;
  for (int j = 0; j < GPU_KS_MAX; j++) {
    const KW *c = L + (j == 0 ? 7 : 9 + j) * n;
    KW d = 0, v0 = c[ix[0]];
    for (KW i = 1; i < k; i++) d |= c[ix[i]] ^ v0;
    if (d) {
      col[nv] = c;
      diff[nv++] = d;
    }
  }
  static KW cnt[2049];
  for (int q = nv - 1; q >= 0; q--) {
    const KW *c = col[q];
    int lo = 0, hi = 64;
    while (!((diff[q] >> lo) & 1)) lo++;
    while (!((diff[q] >> (hi - 1)) & 1)) hi--;
    for (int sh = lo; sh < hi; sh += 11) {
      memset(cnt, 0, sizeof cnt);
      for (KW i = 0; i < k; i++) cnt[((c[ix[i]] >> sh) & 2047) + 1]++;
      for (int d = 1; d <= 2048; d++) cnt[d] += cnt[d - 1];
      for (KW i = 0; i < k; i++) t[cnt[(c[ix[i]] >> sh) & 2047]++] = ix[i];
      KW *s = ix;
      ix = t;
      t = s;
    }
  }
  P->kqmap = P->fn0 + 2 * P->nfn;
  H[P->kqmap] = k;
  for (KW i = 0; i < k; i++) H[P->kqmap + 1 + i] = ix[i];
  free(base);
}

static int gpu_run(const GpuProg *prog, KW entry, V *args, int n, int pin, V *out) {
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
  // The sorted-dispatch map is before the root frame and allocation area.
  KW rf = P.fn0 + 2 * nfn + gpu_lanes + 2;
  if (rf <= gpu_pin) rf = gpu_pin + 1;
  KW fs = k_frame_size(entry);
#ifdef KQ_SHARED
  P.q0 = (rf + fs + 63) / 64 * 64;
  P.heap0 = (P.q0 + KR_WORDS * gpu_lanes + K_CHUNK) / K_CHUNK * K_CHUNK;
#else
  P.heap0 = (rf + fs + K_CHUNK) / K_CHUNK * K_CHUNK;
#endif
  // (the lanes' states, the root frame and the KQ_ stacks come first)
  if (P.heap0 + 64 * K_CHUNK > gpu_Hn / 8) return gpu_Hn < gpu_Hmax ? 2 : 0;
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
  // (the first call's are fresh pages, which the host need not touch)
  if (gpu_used) {
    memset(H + P.lane0, 0, 10 * gpu_lanes * 8);
    memset(H + P.lane0 + (10 + KQ_ARGS) * gpu_lanes, 0, 2 * gpu_lanes * 8);
  }
  P.fresh = 1;
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
  size_t grow_tried = 0;
  for (;;) {
    // Keep completed frames and tasks instead of replaying a main dispatch
    // that fills the arena. Leave headroom for its next allocation burst.
    if ((KW)gpu_A[KA_HEAP] * K_CHUNK > P.heapw - P.heapw / 4 &&
        gpu_Hn < gpu_Hmax && grow_tried != gpu_Hn) {
      grow_tried = gpu_Hn;
      if (gpu_grow(2)) {
        P.an = gpu_Hn;
        P.heapw = gpu_Hn / 8 - P.heap0;
      }
    }
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
#if BEND_METAL
    else if (!g_heap() || !g_dispatch(&P, g_pso)) {
      return 0;
    }
#endif
    rounds++;
    P.fresh = 0;
    KW tail = gpu_A[KA_QTAIL];
    if (tail > gpu_qused) gpu_qused = tail < P.qcap ? tail : P.qcap;
    if (__atomic_load_n(&gpu_A[KA_ERR], __ATOMIC_SEQ_CST) != 0) break;
    if (__atomic_load_n(&gpu_A[KA_DONE], __ATOMIC_SEQ_CST) != 0) break;
    for (KW l = 0; l < gpu_lanes; l++) waiting += H[P.lane0 + l] == PC_KQ;
    if (gpu_log == 3) {
      KW act = 0, idle = 0;
      for (KW l = 0; l < gpu_lanes; l++) { KW pc = H[P.lane0 + l]; act += pc != PC_IDLE && pc != PC_KQ; idle += pc == PC_IDLE; }
      fprintf(stderr, "bend gpu: round: active %llu -> %llu, idle %llu, waiting %llu, queued %u\n", (unsigned long long)active,
        (unsigned long long)act, (unsigned long long)idle, (unsigned long long)waiting, (unsigned)(gpu_A[KA_QTAIL] - gpu_A[KA_QHEAD]));
    }
    if (waiting > 0 && gpu_kq_host(prog, H, &P, waiting)) waiting = 0;
    P.kqmap = 0;
    if (waiting > 1 && gpu_kq_order) gpu_kq_sort(H, &P, waiting);
    if (gpu_log == 3 && waiting > 0) {
      // (which calls wait: label, with K_KQLIM or not, and the first lane's depth)
      KW n = gpu_lanes, lab[8] = {0}, cnt[8] = {0}, lim[8] = {0}, dep[8] = {0};
      for (KW l = 0; l < n; l++) {
        if (H[P.lane0 + l] != PC_KQ) continue;
        KW kq = H[P.lane0 + 7 * n + l], j = 0;
        while (j < 8 && cnt[j] && lab[j] != kq) j++;
        if (j == 8) continue;
        if (!cnt[j]) dep[j] = H[P.lane0 + 3 * n + l] & 0xffffffff;
        lab[j] = kq; cnt[j]++; lim[j] += (H[P.lane0 + 9 * n + l] & K_KQLIM) != 0;
      }
      for (int j = 0; j < 8 && cnt[j]; j++)
        fprintf(stderr, "bend gpu: waiting kq %llu x%llu (lim %llu, dep %llu)\n", (unsigned long long)lab[j],
          (unsigned long long)cnt[j], (unsigned long long)lim[j], (unsigned long long)dep[j]);
    }
    if (waiting > 0) {
      // (again, after the arena grows, while a call runs out of it)
      for (;;) {
        gpu_A[KA_GROW] = 0;
        // (a fresh epoch, 1 to 2^24 - 1, for each dispatch: see k_take)
        gpu_kqep = gpu_kqep % 0xffffff + 1;
        P.kqep = gpu_kqep;
        if (gpu_mode == GPU_SIM) {
          for (KW l = 0; l < gpu_lanes; l++) prog->sim_kq(H, gpu_A, &P, (KW *)gc_base, (uint32_t)l);
        }
#if BEND_METAL
        else if (!g_dispatch(&P, g_pso_kq)) {
          return 0;
        }
#endif
        if (gpu_A[KA_GROW] == 0 || gpu_A[KA_ERR] != 0) break;
        // Grow for the calls still waiting. Their discarded spans stay in
        // each lane's free list, so the global bump must remain monotonic.
        KW left = 0;
        for (KW l = 0; l < gpu_lanes; l++) left += H[P.lane0 + l] == PC_KQ;
        // Reusable lane chunks keep their indices; do not rewind the global bump.
        size_t f = 4;
        while (f < (left == waiting ? 8 : 16) && f * (waiting - left) < 2 * waiting) f *= 2;
        if (!gpu_grow(f)) {
          gpu_A[KA_ERR] = KE_HEAP;
          break;
        }
        P.an = gpu_Hn;
        P.heapw = gpu_Hn / 8 - P.heap0;
      }
      if (__atomic_load_n(&gpu_A[KA_ERR], __ATOMIC_SEQ_CST) != 0) break;
      if (gpu_log == 2) {
        KW n = gpu_lanes, fb = 0, kq = 0;
        for (KW l = 0; l < n; l++) {
          KW *ls = H + P.lane0 + l;
          if (ls[9 * n] != ls[8 * n] && ls[0] == ls[9 * n]) { fb++; kq = ls[7 * n]; }
        }
        fprintf(stderr, "bend gpu: kq ran %llu lanes, %llu gave up (kq %llu)\n", (unsigned long long)waiting,
          (unsigned long long)fb, (unsigned long long)kq);
      }
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
    fprintf(stderr, "bend gpu: done in %llu dispatches, %llu MB of arena, %.3fs + %.3fs on the device\n",
      (unsigned long long)rounds, (unsigned long long)((KW)gpu_A[KA_HEAP] * K_CHUNK * 8 >> 20), gpu_secs[0],
      gpu_secs[1]);
  }
#if BEND_METAL
  if (gpu_mode == GPU_METAL)
    g_hint_save((size_t)(P.heap0 + (KW)gpu_A[KA_HEAP] * K_CHUNK) * 8);
#endif
  // A big result stays where it is (copying it out costs as much as the
  // call, and the next call may take it back), below half the arena.
  KW end = P.heap0 + (KW)gpu_A[KA_HEAP] * K_CHUNK;
  if (end > P.heap0 + P.heapw) end = P.heap0 + P.heapw;
  #ifdef K_GPU_PACKED
  const int can_pin=0; // CPU consumers require ordinary objects.
#else
  const int can_pin=1;
#endif
  if (can_pin && (end - P.heap0) * 8 >= gpu_pin_min && end * 8 <= gpu_Hmax / 2 && H[2] - P.ab < end * 8 &&
      gpu_pinnable(pin, args, n)) {
    gpu_tout = 0;
    gpu_pin = end;
    *out = H[2];
    // (Its nodes are shared: see bend_share_arena.)
    bend_share_arena(*out);
    if (gpu_log == 2) fprintf(stderr, "bend gpu: the result stays in the arena (%llu MB)\n", (unsigned long long)(end * 8 >> 20));
    return 1;
  }
  gpu_nout = 0;
  double t0 = gpu_log ? gpu_now() : 0;
  int ok = gpu_copy_out(prog, &P, H[2], out);
  if (gpu_log) gpu_tout = gpu_now() - t0;
  gpu_nout = 0;
  return ok;
}

static int gpu_call(const GpuProg *prog, KW entry, V *args, int n, int pin, V *out) {
  if (gpu_nest) return 0;
  pthread_mutex_lock(&gpu_lock);
  double t0 = gpu_now();
  if (gpu_mode < 0) gpu_mode = gpu_setup(prog);
  double t1 = gpu_now();
  int r = gpu_mode != GPU_OFF ? gpu_run(prog, entry, args, n, pin, out) : 0;
  while (r == 2) r = gpu_grow(4) ? gpu_run(prog, entry, args, n, pin, out) : 0;
  if (gpu_log == 2) fprintf(stderr, "bend gpu: call %.3fs (setup %.3fs, copy out %.3fs)\n", gpu_now() - t0, t1 - t0, gpu_tout);
  pthread_mutex_unlock(&gpu_lock);
  // (counted, the device's run consumed the arguments, as the CPU's would)
  if (r == 1 && gc_hot.rc)
    for (int i = 0; i < n; i++) rc_drop(args[i]);
  return r == 1;
}
