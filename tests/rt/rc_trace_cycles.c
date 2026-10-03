#include "bendrt.h"
#include <assert.h>
static uintptr_t weak[68];
static V live_cycle;
static V root;
static const uintptr_t mask = UINT64_C(0xfedcba9876543210);
__attribute__((noinline)) static void cycles(void) {
  for (unsigned i=0;i<32;i++) {
    V *a=halloc(16385), *b=halloc(16385);
    a[0]=7; b[0]=9;
    a[1]=(V)b; b[1]=(V)a;
    a[2]=root; rc_dup(root);
    rc_dup((V)a); rc_dup((V)b);
    weak[i*2]=(uintptr_t)a ^ mask; weak[i*2+1]=(uintptr_t)b ^ mask;
    rc_drop((V)a); rc_drop((V)b);
  }
}
__attribute__((noinline)) static void wash_collect(unsigned depth) {
  volatile V clean[8192];
  for(unsigned i=0;i<8192;i++) clean[i]=0;
  if(depth) wash_collect(depth-1); else gc_collect();
  __asm__ volatile("" : : "r"(clean) : "memory");
}
__attribute__((noinline)) static void make_live_cycle(void) {
  V *a=halloc(4097), *b=halloc(4097);a[0]=11;b[0]=13;
  a[1]=(V)b;b[1]=(V)a;rc_dup((V)a);rc_dup((V)b);rc_drop((V)b);
  weak[64]=(uintptr_t)a^mask;weak[65]=(uintptr_t)b^mask;live_cycle=(V)a;
}
__attribute__((noinline)) static void check_live_cycle(void) {
  assert(rc_obj(live_cycle));V b=FLD(live_cycle,0);
  assert(rc_obj(b) && FLD(b,0)==live_cycle);
}
__attribute__((noinline)) static void drop_live_cycle(void) {
  V a=live_cycle;live_cycle=0;rc_drop(a);
}
static void *live_stage(void *unused) {
  (void)unused;thr_register((uintptr_t)__builtin_frame_address(0)+16);
  make_live_cycle();wash_collect(3);check_live_cycle();drop_live_cycle();
  thr_self->live=0;return NULL;
}
static V run(void) {
  root=C1(17,42); gc_root_add(&root,1);gc_root_add(&live_cycle,1);
  cycles();
  wash_collect(3);
  for(unsigned i=0;i<64;i++) assert(!rc_obj((V)(weak[i]^mask)));
  assert(rc_obj(root) && FLD(root,0)==42);
  assert(RC_REFS(*(V*)root)>=32); // Sweeping dead parents conservatively keeps counts.
  V child=C1(33,99);
  rc_push(thr_self,child); // Explicit buffer root, independent of refcounts.
  weak[0]=(uintptr_t)child ^ mask; child=0;
  wash_collect(3);
  assert(rc_obj(thr_self->rcs[thr_self->rcn-1]));
  child=thr_self->rcs[thr_self->rcn-1]; BEND_BARRIER(); thr_self->rcn--; rc_drop(child);
  V old=root; root=0; rc_drop(old); old=0;
  wash_collect(3);
  pthread_attr_t attr;pthread_attr_init(&attr);thr_stack(&attr);
  pthread_t worker;assert(!pthread_create(&worker,&attr,live_stage,NULL));
  pthread_attr_destroy(&attr);assert(!pthread_join(worker,NULL));wash_collect(3);
  assert(!rc_obj((V)(weak[64]^mask)) && !rc_obj((V)(weak[65]^mask)));
  assert(gc_count>0 && !gc_minor);
  return UNIT;
}
static void print(V v){(void)v;puts("ok");}
int main(int argc,char **argv) { bend_rc_req=1; bend_rc_trace_req=1; return bend_run_value(argc,argv,run,print); }
