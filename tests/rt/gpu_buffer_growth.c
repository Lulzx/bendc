// GPU-written arena contents must survive buffer growth and later dispatches.
// This checks the host buffer path independently of generated Tree programs.
#include <assert.h>
#include "bendrt.h"
#include "gpu.h"
KINLINE KW k_frame_size(KW label) { (void)label; return 4; }
KINLINE void k_cases(KCtx *c) { k_fail(c, KE_PC); }
KINLINE KW k_kq(KCtx *c, bool *ok) { (void)c; *ok = false; return 0; }
#include "gpuhost.h"

#if BEND_METAL
static const char source[] =
  "KINLINE KW k_frame_size(KW l) { return 4; }\n"
  "KINLINE void k_cases(KTHR KCtx *c) { k_fail(c, KE_PC); }\n"
  "KINLINE KW k_kq(KTHR KCtx *c, KTHR bool *ok) { *ok=false; return 0; }\n"
  "kernel void arena_fill(device KW *H [[buffer(0)]], constant KParams &P [[buffer(2)]], uint lane [[thread_position_in_grid]]) {\n"
  " if (lane<P.nlanes) { KW i=P.heap0+lane; H[i]=0xffff000000000003ul ^ (i*0x9e3779b97f4a7c15ul); }\n"
  "}\n";
static KW pattern(KW i) { return UINT64_C(0xffff000000000003) ^ (i * UINT64_C(0x9e3779b97f4a7c15)); }
static void check(KW words) {
  for (KW i = 0; i < words; i++) {
    if (gpu_H[i] != pattern(i)) {
      fprintf(stderr, "shared arena word %llu changed: %llx != %llx\n",
        (unsigned long long)i, (unsigned long long)gpu_H[i], (unsigned long long)pattern(i));
      abort();
    }
  }
}
#endif
int main(void) {
#if BEND_METAL
  setenv("BEND_GPU_MB0", "4", 1);
  setenv("BEND_GPU_MB", "16", 1);
  setenv("BEND_GPU_LANES", "64", 1);
  unsetenv("BEND_GPU");
  gc_init();
  const GpuFn functions[] = {{NULL, 0}};
  const GpuProg prog = {source, NULL, NULL, functions, NULL};
  gpu_mode = gpu_setup(&prog);
  // Absence of a device is permitted; a present device must compile the probe.
  if (g_dev) assert(gpu_mode == GPU_METAL);
  if (gpu_mode == GPU_METAL) {
    void *pool = g_pool_push();
    GId lib = g_compile(&prog), error = NULL;
    GId pipeline = lib ? g_pipe(g_desc(lib, "arena_fill"), NULL, &error) : NULL;
    assert(pipeline && g_heap());
    KParams p = {0};
    p.nlanes = gpu_Hn / sizeof(KW);
    assert(g_dispatch(&p, pipeline, NULL));
    KW old = p.nlanes;
    check(old);
    for (int step = 0; step < 2; step++) {
      assert(gpu_grow(2));
      check(old);
      p.heap0 = old;
      p.nlanes = gpu_Hn / sizeof(KW) - old;
      assert(g_dispatch(&p, pipeline, NULL));
      old += p.nlanes;
      check(old);
    }
    g_msg(pipeline, "release");
    g_msg(lib, "release");
    g_pool_pop(pool);
  }
#endif
  puts("ok");
  return 0;
}
