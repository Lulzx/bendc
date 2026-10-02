#include <stdint.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpu.h"
KINLINE KW k_frame_size(KW l) { (void)l; return 8; }
KINLINE void k_cases(KCtx *c) { k_fail(c, KE_PC); }
KINLINE KW k_kq(KCtx *c, bool *ok) { (void)c; *ok=false; return 0; }
#include <assert.h>
static KW arena[1<<16], borrowed[128];
static KAU controls[KA_SEQ+16];
int main(void) {
 KParams p={0};p.ab=(KW)(uintptr_t)arena;p.an=sizeof arena;p.heap0=1024;p.heapw=(sizeof arena/sizeof(KW))-p.heap0;p.nlanes=1;
 KCtx c={0};c.H=arena;c.G=borrowed;c.A=controls;c.P=&p;c.ab=p.ab;c.an=p.an;c.gb=(KW)(uintptr_t)borrowed;controls[KA_HEAP]=1;
 k_anone(&c);
 KW a=k_anew(&c,3,23,true),b=k_anew(&c,3,29,true),d=k_anew(&c,3,31,true);

 for(int j=0;j<500;j++) {
  assert(k_aget(&c,a,j)==23);assert(k_aget(&c,b,j)==29);assert(k_aget(&c,d,j)==31);
  assert(k_aswap(&c,a,j,42)==23);assert(k_aget(&c,a,j)==42);assert(k_aswap(&c,a,j,23)==42);
 }
 KW wide=k_anew(&c,3,(KW)1<<48,false);assert(k_aget(&c,wide,11)==((KW)1<<48));
 assert(k_aget(&c,a,0)==23);assert(k_aget(&c,b,0)==29);assert(k_aget(&c,d,0)==31);
 borrowed[0]=K_ARR_HDR(3);borrowed[1+3]=(KW)1<<49;assert(k_aget(&c,(KW)(uintptr_t)borrowed,3)==((KW)1<<49));
 borrowed[0]=K_ARR_HDR(3)|K_ARR_NW;((KU*)(borrowed+1))[3]=47;assert(k_aget(&c,(KW)(uintptr_t)borrowed,11)==47);
 k_anone(&c);
 assert(k_aget(&c,a,0)==23 && k_aget(&c,b,0)==29 && k_aget(&c,d,0)==31);
 assert(!c.err);puts("ok");
}
