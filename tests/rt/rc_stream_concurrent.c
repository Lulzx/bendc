#include "bendrt.h"
#include <assert.h>
static _Atomic int ready,done;static _Atomic unsigned runs;
static void *worker(void *unused) {
 (void)unused;thr_register((uintptr_t)__builtin_frame_address(0)+16);
 atomic_store(&ready,1);
 for(unsigned n=0;n<32;n++) {
  V a=arr_alloc(12);for(unsigned j=0;j<4096;j++)arr_cells(a)[j]=C1(23,j);
  rc_drop(a);atomic_fetch_add(&runs,1);
 }
 assert(thr_self->rcn==0 && thr_self->rccap<=1024);
 atomic_store(&done,1);thr_self->live=0;return NULL;
}
static V run(void) {
 pthread_attr_t attr;pthread_attr_init(&attr);thr_stack(&attr);pthread_t thread;
 assert(!pthread_create(&thread,&attr,worker,NULL));pthread_attr_destroy(&attr);
 while(!atomic_load(&ready))sched_yield();unsigned collected=0;
 do {gc_collect();collected++;}while(!atomic_load(&done)||collected<100);
 assert(!pthread_join(thread,NULL));assert(atomic_load(&runs)==32);return UNIT;
}
static void print(V v){(void)v;puts("ok");}
int main(int argc,char **argv){bend_rc_req=1;bend_rc_trace_req=1;return bend_run_value(argc,argv,run,print);}
