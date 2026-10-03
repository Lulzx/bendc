#include <stdint.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "gpu.h"
KINLINE KW k_frame_size(KW l) { (void)l;return 8; }
KINLINE void k_cases(KCtx*c) { k_fail(c,KE_PC); }
KINLINE KW k_kq(KCtx*c,bool*ok) { (void)c;*ok=false;return 0; }
static KW H[65536],G[128];static KAU A[KA_SEQ+16];
int main(void) {
 KParams p={0};p.ab=(KW)(uintptr_t)H;p.an=sizeof H;p.heap0=1024;p.heapw=65536-p.heap0;p.nlanes=1;
 KCtx c={0};c.H=H;c.G=G;c.A=A;c.P=&p;c.ab=p.ab;c.an=p.an;c.gb=(KW)(uintptr_t)G;A[KA_HEAP]=1;k_anone(&c);
 KW a=k_anew(&c,3,23,true),b=k_anew(&c,3,29,true),d=k_anew(&c,3,31,true);
 KW ai=k_ainfo(&c,a),bi=k_ainfo(&c,b),di=k_ainfo(&c,d);assert(ai==((KW)7|KAI_NARROW));
 for(int i=0;i<500;i++) {
  assert(k_aiget(&c,a,ai,i)==23 && k_aiget(&c,b,bi,i)==29 && k_aiget(&c,d,di,i)==31);
  assert(k_aiswap(&c,a,ai,i,53)==23 && k_aiget(&c,a,ai,i)==53 && k_aiswap(&c,a,ai,i,23)==53);
 }
 assert(k_aiswap(&c,a,ai,3,((KW)1<<49)|53)==23 && k_aiget(&c,a,ai,3)==53);assert(k_aiswap(&c,a,ai,3,23)==53);
 KW wide=k_anew(&c,3,(KW)1<<49,false),wi=k_ainfo(&c,wide);assert(k_aiget(&c,wide,wi,11)==((KW)1<<49));assert(k_aiget(&c,wide,0,11)==((KW)1<<49));assert(k_aiswap(&c,wide,wi,11,(KW)1<<51)==((KW)1<<49));assert(k_aiget(&c,wide,wi,3)==((KW)1<<51));assert(k_aiswap(&c,wide,0,19,(KW)1<<49)==((KW)1<<51));
 G[0]=K_ARR_HDR(3);G[4]=(KW)1<<50;KW gp=(KW)(uintptr_t)G,gi=k_ainfo(&c,gp);assert(gi&KAI_CPU);assert(k_aiget(&c,gp,gi,11)==((KW)1<<50));assert(k_aiget(&c,gp,0,11)==((KW)1<<50));assert(k_aiswap(&c,gp,gi,11,99)==0 && c.err==KE_FX && G[4]==((KW)1<<50));c.err=0;
 G[0]=K_ARR_HDR(3)|K_ARR_NW;((KU*)(G+1))[3]=47;gi=k_ainfo(&c,gp);assert(k_aiget(&c,gp,gi,11)==47);
 assert(k_aiswap(&c,gp,gi,11,99)==0 && c.err==KE_FX && ((KU*)(G+1))[3]==47);
 c.err=0;assert(k_aiget(&c,a,0,13)==23);assert(k_aiswap(&c,a,0,13,59)==23);assert(k_aiswap(&c,a,0,13,23)==59);assert(k_aiget(&c,gp,0,11)==47);assert(k_aiswap(&c,gp,0,11,99)==0 && c.err==KE_FX);
 k_anone(&c);assert(k_aiget(&c,a,ai,13)==23 && k_aiget(&c,b,bi,13)==29 && k_aiget(&c,d,di,13)==31);
 assert(k_ainfo(&c,0)==KAI_NARROW);assert(k_aiget(&c,0,KAI_NARROW,99)==0);assert(k_aiget(&c,0,0,99)==0);assert(k_aiswap(&c,0,0,99,77)==0);assert(k_aiget(&c,0,0,99)==77);assert(k_aiswap(&c,0,0,99,0)==77);

 c.err=0;
 assert(KF_Array_dset(&c,a,19,((KW)1<<49)|67)==a);assert(k_aiget(&c,a,ai,3)==67);
 k_anone(&c);assert(KF_Array_dset(&c,b,21,71)==b);assert(k_aiget(&c,b,bi,5)==71);
 assert(KF_Array_dset(&c,wide,19,(KW)1<<52)==wide);assert(k_aiget(&c,wide,wi,3)==((KW)1<<52));
 c.err=0;assert(KF_Array_dset(&c,gp,11,99)==gp);assert(c.err==KE_FX && ((KU*)(G+1))[3]==47);
 c.err=0;G[0]=K_ARR_HDR(3);G[4]=(KW)1<<50;assert(KF_Array_dset(&c,gp,11,99)==gp);assert(c.err==KE_FX && G[4]==((KW)1<<50));
 c.err=0;assert(k_aiset(&c,a,ai,27,83)==a);assert(k_aiget(&c,a,ai,3)==83);
 assert(k_aiset(&c,b,0,21,79)==b);assert(k_aiget(&c,b,bi,5)==79);
 assert(k_aiset(&c,wide,wi,19,(KW)1<<53)==wide);assert(k_aiget(&c,wide,wi,3)==((KW)1<<53));
 c.err=0;assert(k_aiset(&c,gp,gi,11,99)==gp);assert(c.err==KE_FX && G[4]==((KW)1<<50));
 c.err=0;assert(k_aiset(&c,0,KAI_NARROW,9,99)==0);assert(c.err==KE_FX);
 puts("ok");
}
