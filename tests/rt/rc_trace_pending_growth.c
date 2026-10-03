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
  for (unsigned j=0;j<32768;j++) {
    V v=C1(17,42);rc_push(t,v);
    if ((j&31)==0) sched_yield();
  }
  atomic_store(&done,1);
  while(atomic_load(&ready)) sched_yield();
  while(t->rcn) {V v=t->rcs[t->rcn-1];BEND_BARRIER();t->rcn--;assert(rc_obj(v) && FLD(v,0)==42);rc_drop(v);atomic_fetch_add(&turns,1);}
  t->live=0;return NULL;
}
static V run(void) {
  pthread_attr_t attr;pthread_attr_init(&attr);thr_stack(&attr);
  pthread_t thread;assert(!pthread_create(&thread,&attr,worker,NULL));pthread_attr_destroy(&attr);
  while(!atomic_load(&ready)) sched_yield();
  unsigned collected=0;
  do {gc_collect();collected++;} while(!atomic_load(&done) || collected<100);
  atomic_store(&ready,0); // release the worker to validate/free its rooted prefix
  assert(!pthread_join(thread,NULL));assert(gc_count>=100);
  return UNIT;
}
static void print(V v){(void)v;puts("ok");}
int main(int argc,char **argv) {bend_rc_req=1;bend_rc_trace_req=1;return bend_run_value(argc,argv,run,print);}
