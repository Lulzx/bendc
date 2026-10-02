#include "bendrt.h"
#include <assert.h>
static V vals[21 * 1024];
static V unit(void) {
  gc_root_add(vals, sizeof vals / sizeof *vals);
  for (unsigned n = 0; n <= 20; n++) {
    for (unsigned j = 0; j < 1024; j++) {
      V *p = halloc_b(n);
      for (unsigned k = 0; k < (n < 2 ? 2 : n); k++) p[k] = 17 + k;
      vals[n * 1024 + j] = (V)p;
    }
    for (unsigned j = 1; j < 1024; j++) {
      V a = vals[n * 1024 + j - 1], b = vals[n * 1024 + j];
      assert((a >> 4) != (b >> 4));
    }
  }
  for (unsigned i = 0; i < 21 * 1024; i += 3) bend_share(vals[i]);
  for (unsigned cycle = 0; cycle < 12; cycle++) {
    pthread_mutex_lock(&gc_lock); gc_collect_locked(); pthread_mutex_unlock(&gc_lock);
    for (unsigned i = 0; i < 21 * 1024; i++) {
      unsigned char f = *(unsigned char *)(gc_hot.bflags + (vals[i] >> 4));
      assert((f & 1) == (i % 3 == 0));
      assert(((V *)vals[i])[0] == 17);
    }
  }
  // Force a last-block reuse under each allocator, retaining the old
  // BK_SH history. No live unit values occupy this extra block.
  pthread_mutex_lock(&gc_lock);
  GcBlk *probe = gc_new_small(2, 0);
  uintptr_t bi = gc_bi(probe);
  unsigned char *flags = gc_bflags + bi * (GC_BLK / 16);
  memset(flags, 3, GC_BLK / 16);
  gc_bk[(uintptr_t)probe >> GC_BLK_SHIFT] = BK_BARE | BK_SH;
  probe->owned = 0; gc_kind[bi] = 0; gc_top = bi;
  GcBlk *ordinary = gc_new_small(0, 0);
  assert(gc_bi(ordinary) == bi);
  for (unsigned j = 0; j < GC_BLK / 16; j++) assert(flags[j] == 0);
  ordinary->owned = 0; gc_kind[bi] = 0; gc_top = bi;
  probe = gc_new_small(2, 0);
  assert(gc_bi(probe) == bi);
  for (unsigned j = 0; j < GC_BLK / 16; j++) assert(flags[j] == 0);
  memset(flags, 3, GC_BLK / 16);
  gc_bk[(uintptr_t)probe >> GC_BLK_SHIFT] = BK_BARE | BK_SH;
  probe->owned = 0; gc_kind[bi] = 0; gc_top = bi;
  pthread_mutex_unlock(&gc_lock);
  V *large = gc_alloc_large(GC_SMALL + 1, 0);
  assert(((uintptr_t)large - (uintptr_t)gc_base) >> GC_BLK_SHIFT == bi);
  for (unsigned j = 0; j < GC_BLK / 16; j++) assert(flags[j] == 0);
  return 0;
}
static void print(V v) { (void)v; puts("ok"); }
int main(int argc, char **argv) { return bend_run_value(argc, argv, unit, print); }
