// A slot in a thread's allocation cache has its allocation bit before it is
// handed out (see GcCache in rt/bendrt.h), so a collection can mark it from
// a stale pointer; the object later built there is then old, and a minor
// collection would not trace from it, but that its block is dirty
// (gc_dirty_caches). Here: a stale root marks slot s of the 3-word cache,
// s is then built with the only reference to a young node y (in a block
// the 4-word cache has left), and a minor collection must keep y.
// (Pointers to s and y are kept xored, and the stack is scrubbed before
// each collection, so that no root but the planted one reaches them.)
#include "bendrt.h"

#define HIDE 0x5a5a5a5a5a5a5a5aull
static V holder[1];  // a root: node h
static V stale[1];   // a root: the stale pointer to s
static uintptr_t hid_s, hid_y;

__attribute__((noinline)) static void scrub(void) {
  volatile V z[2048];
  for (int i = 0; i < 2048; i++) z[i] = 0;
}

__attribute__((noinline)) static void make_h(void) {
  V *h = halloc(2);
  h[0] = 1;
  h[1] = IMM(0);
  holder[0] = (V)h;
}

// 1 when the slot after a new 3-word node is in the cache, not handed out.
__attribute__((noinline)) static int plant(void) {
  V *a = halloc(3);
  a[0] = 1;
  a[1] = a[2] = IMM(0);
  GcCache *k = &thr_self->cache[0][1];
  if (k->bump != a + 3 || k->bump >= k->end) return 0;
  stale[0] = (V)(a + 3);
  hid_s = (uintptr_t)(a + 3) ^ HIDE;
  return 1;
}

__attribute__((noinline)) static int build(void) {
  V *s = halloc(3);
  if ((uintptr_t)s != (hid_s ^ HIDE)) return 0;
  V *y = halloc(4);
  y[0] = 1;
  y[1] = IMM(7);
  y[2] = IMM(8);
  y[3] = IMM(9);
  s[0] = 1;
  s[1] = (V)y;
  s[2] = IMM(0);
  // h, old, now points to s (as a token rebuilt would)
  bend_ru_dirty(holder[0]);
  ((V *)holder[0])[1] = (V)s;
  hid_y = (uintptr_t)y ^ HIDE;
  // The 4-word cache leaves y's block, which a collection then sweeps.
  GcBlk *yb = thr_self->cache[0][2].blk;
  for (int i = 0; i < 100000 && thr_self->cache[0][2].blk == yb; i++) {
    V *g = halloc(4);
    g[0] = 1;
    g[1] = g[2] = g[3] = IMM(0);
  }
  return thr_self->cache[0][2].blk != yb;
}

static const char *window_msg = "ok";

static V window_main(void) {
  gc_root_add(holder, 1);
  gc_root_add(stale, 1);
  gc_collect();
  make_h();
  scrub();
  gc_collect();  // h is old
  int planted = 0;
  for (int i = 0; i < 1000 && !planted; i++) planted = plant();
  if (!planted) { window_msg = "no slot to plant"; return UNIT; }
  scrub();
  gc_collect();  // s is marked, not handed out
  stale[0] = 0;
  if (!build()) { window_msg = "s was not handed out next, or the cache did not move"; return UNIT; }
  scrub();
  gc_collect();  // minor: y is reached only from s
  V *y = (V *)(hid_y ^ HIDE);
  uint32_t i;
  GcBlk *b = gc_slot((V)y, &i);
  if (!gc_minor) window_msg = "the collection was not minor";
  else if (b == NULL || !(GC_ALLOC(b)[i >> 6] & (1ull << (i & 63)))) window_msg = "a young node reached from a stale-marked slot was freed";
  else if (y[1] != IMM(7) || y[3] != IMM(9)) window_msg = "a young node reached from a stale-marked slot was overwritten";
  return UNIT;
}

static void window_print(V v) {
  (void)v;
  fputs(window_msg, stdout);
}

int main(int argc, char **argv) {
  (void)argc;
  char *av[] = {argv[0], "--threads", "1", NULL};
  return bend_run_value(3, av, window_main, window_print);
}
