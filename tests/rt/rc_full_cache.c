#include "bendrt.h"
#include <assert.h>
static V unit(void) {
  enum { WORDS = 2049, N = 12 };
  V *slots[N + 1];
  for (unsigned j = 0; j < N; ++j) {
    slots[j] = halloc(WORDS);
    for (unsigned i = 0; i < j; ++i) assert(slots[i] != slots[j]);
    slots[j][0] = 71 + j;
  }
  unsigned c = gc_cls_of[WORDS];
  GcCache *k = &thr_self->cache[0][c];
  GcBlk *old = k->blk;
  assert(old && old->nobj == 3);
  uintptr_t bi = gc_bi(old);
  __atomic_store_n(&old->owned, 0, __ATOMIC_RELEASE);
  k->blk = NULL; k->bump = k->end = NULL; k->bits = 0;
  k->j = (uint32_t)-1; k->idx = 0;
  __atomic_fetch_or(&gc_cand[(size_t)c * GC_CANDW + (bi >> 6)], 1ull << (bi & 63), __ATOMIC_RELAXED);
  thr_self->rcur[c] = (uint32_t)bi;
  slots[N] = halloc(WORDS);
  for (unsigned j = 0; j < N; ++j) {
    assert(slots[N] != slots[j]);
    assert(slots[j][0] == 71 + j);
  }
  return 0;
}
static void print(V v) { (void)v; puts("ok"); }
int main(int argc, char **argv) { bend_rc_req = 1; return bend_run_value(argc, argv, unit, print); }
