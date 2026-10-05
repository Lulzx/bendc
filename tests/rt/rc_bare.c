#include "bendrt.h"
#include <assert.h>
// A bare leaf (packed, one field): a reference to something under a bare
// node, to tell "the fields are the case's now" from "the node's".
static V leaf(V x) { return C1(11, x); }
static V run(void) {
  size_t base = rc_live();
  // A take of an unshared bare node frees its slot: every word is a field
  // (no tag), and the case receives them with the reference the node held.
  V a = leaf(7), b = leaf(9);
  V n = B2(a, b);
  assert(rc_bare(n) && rc_unique(n));
  rc_take(n, 258);
  assert(rc_unique(a) && rc_unique(b) && rc_live() == base + 2);
  // A take of a shared one gives each field a reference before the node
  // loses one: the fields outlive it. (m itself outlives it here too: this
  // holds a reference of its own.)
  V m = B2(a, b);
  rc_dup(m);
  assert(!rc_unique(m));
  rc_take(m, 258);
  assert(!rc_unique(a) && !rc_unique(b));
  rc_drop(a);
  rc_drop(b);
  rc_drop(m);
  assert(rc_live() == base);
  // A reuse take answers an unshared node's slot as a token, which the case
  // builds its constructor in (BG2 writes the fresh count byte) and does not
  // free: the fields the take gave it are the constructor's.
  V c = leaf(11), d = leaf(13);
  V o = B2(c, d);
  V tok = rc_take_ru(o, 258);
  assert(tok == o && rc_bare(o));
  V r = BG2(tok, c, d);
  assert(r == o && rc_bare(r) && rc_unique(r));
  rc_take(r, 258);
  assert(rc_unique(c) && rc_unique(d) && rc_live() == base + 2);
  rc_drop(c);
  rc_drop(d);
  assert(rc_live() == base);
  // A case that does not build in its token frees it (RUF): the slot is
  // freed, the fields the take gave it are the case's.
  V e = leaf(17), f = leaf(19);
  V o2 = B2(e, f);
  V tok2 = rc_take_ru(o2, 258);
  assert(tok2 == o2);
  RUF(tok2, 258);
  assert(rc_unique(e) && rc_unique(f) && rc_live() == base + 2);
  rc_drop(e);
  rc_drop(f);
  assert(rc_live() == base);
  // A reuse take of a shared node answers no token, giving the fields
  // references like any shared take.
  V g = leaf(23), h = leaf(29);
  V o3 = B2(g, h);
  rc_dup(o3);
  assert(rc_take_ru(o3, 258) == 0 && !rc_unique(g) && !rc_unique(h));
  rc_drop(g);
  rc_drop(h);
  rc_drop(o3);
  assert(rc_live() == base);
  // Giving up several references at once: the node dies with the last, its
  // fields with it.
  V i = leaf(31), j = leaf(37);
  V p = B2(i, j);
  rc_dup(p);
  rc_dup(p);
  rc_dropn(p, 2);
  assert(rc_unique(p) && rc_live() == base + 3);
  rc_drop(p);
  assert(rc_live() == base);
  // A count that reaches its top (31) never frees the node: a bounded leak,
  // not a dangling one. (Its fields are numbers here, no references.)
  V q = B2(IMM(1), IMM(2));
  for (int k = 0; k < 40; k++) rc_dup(q);
  assert(!rc_unique(q));
  rc_dropn(q, 40);
  rc_dropn(q, 1);
  assert(rc_live() == base + 1);
  return UNIT;
}
static void print(V v){(void)v;puts("ok");}
// (bend_hless_req before the runtime starts: gc_hot.rcb, the bare flag)
int main(int argc,char **argv){bend_rc_req=1;bend_rc_trace_req=1;bend_hless_req=1;return bend_run_value(argc,argv,run,print);}
