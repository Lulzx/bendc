#include "bendrt.h"
#include <assert.h>
static _Atomic int ready,done;
static _Atomic unsigned long turns;
static void *worker(void *unused) {
  (void)unused;
  thr_register((uintptr_t)__builtin_frame_address(0)+16);
  Thr *t=thr_self;
  for(unsigned j=0;j<128;j++) {
    V *p=halloc(4097);p[0]=17;p[1]=42;rc_push(t,(V)p);
  }
  atomic_store(&ready,1);
  while(!atomic_load(&done)) {
    V v=t->rcs[t->rcn-1];BEND_BARRIER();t->rcn--;
    assert(rc_obj(v) && FLD(v,0)==42);
    rc_push(t,v);
    atomic_fetch_add_explicit(&turns,1,memory_order_relaxed);
  }
  while(t->rcn) {V v=t->rcs[t->rcn-1];BEND_BARRIER();t->rcn--;rc_drop(v);}
  t->live=0;return NULL;
}
static V run(void) {
  pthread_attr_t attr;pthread_attr_init(&attr);thr_stack(&attr);
  pthread_t thread;assert(!pthread_create(&thread,&attr,worker,NULL));pthread_attr_destroy(&attr);
  while(!atomic_load(&ready)) sched_yield();
  for(unsigned k=0;k<100;k++) gc_collect();
  atomic_store(&done,1);assert(!pthread_join(thread,NULL));
  assert(atomic_load(&turns)>0 && gc_count>=100);
  return UNIT;
}
static void print(V v){(void)v;puts("ok");}
int main(int argc,char **argv) {bend_rc_req=1;bend_rc_trace_req=1;return bend_run_value(argc,argv,run,print);}
