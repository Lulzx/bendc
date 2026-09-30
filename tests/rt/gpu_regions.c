#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "gpu.h"
KINLINE KW k_frame_size(KW l) { return 8; }
KINLINE void k_cases(KCtx *c) { k_fail(c, KE_PC); }
KINLINE KW k_kq(KCtx *c, bool *ok) { *ok = false; return 0; }
static KU inner(KCtx *c) {
  KW a = k_anew(c, 10, 123, true);
  KW b = k_anew(c, 12, 456, true);
  KW d = k_anew(c, 9, 789, true);
  return (KU)(k_aget(c,a,1023)+k_aget(c,b,4095)+k_aget(c,d,511));
}
static KU nested(KCtx *c) {
  KW a=k_anew(c,9,42,true);
  KU x=KSCAL(inner(c));
  return x+(KU)k_aget(c,a,511);
}
int main(void) {
  KW *H=calloc(65536,sizeof(KW)); KAU A[64]={0};
  KParams p={0}; p.ab=(KW)(uintptr_t)H; p.an=65536*8; p.heap0=256; p.heapw=16384;
  KCtx a={0},b={0}; a.H=b.H=H; a.A=b.A=A; a.P=b.P=&p;
  a.ab=b.ab=p.ab; a.an=b.an=p.an; A[KA_HEAP]=1;
  KW keepa=k_anew(&a,6,99,true),keepb=k_anew(&b,6,88,true);
  KW ah=a.hp,ae=a.he,ab=a.blocks,bh=b.hp,be=b.he,bb=b.blocks;
  for(int i=0;i<200;i++) {
    KCtx *c=i&1?&a:&b;
    assert(KSCAL(nested(c))==1410 && c->err==0);
    assert(k_aget(&a,keepa,63)==99 && k_aget(&b,keepb,63)==88);
  }
  assert(a.hp==ah && a.he==ae && a.blocks==ab);
  assert(b.hp==bh && b.he==be && b.blocks==bb);
  assert(A[KA_HEAP]<40);
  // A failed call must give back its new spans, preserve earlier objects,
  // and leave the global index monotonic when the arena grows for retry.
  KW h=a.hp,e=a.he,b0=a.blocks;
  (void)k_anew(&a,11,777,true); (void)k_anew(&a,14,999,true);
  assert(a.err==KE_HEAP); k_rewind(&a,h,e,b0); a.err=0;
  p.heapw=65536-p.heap0;
  KCtx *c=&a;
  assert(KSCAL(inner(c))==1368 && a.err==0);
  assert(k_aget(&a,keepa,63)==99 && k_aget(&b,keepb,63)==88);
  free(H); puts("ok");
}
