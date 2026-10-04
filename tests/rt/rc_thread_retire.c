#include <stddef.h>
#include <signal.h>
#include <pthread.h>
#include <stdatomic.h>
static int retirement_kill(pthread_t,int);
#define pthread_kill retirement_kill
#include "bendrt.h"
#undef pthread_kill
#include <assert.h>
static _Atomic int ready,signaled,retired,helper_ready,helper_done;
static V heap;
static Thr *registered;
static int retirement_kill(pthread_t thread,int sig) {
  int result=pthread_kill(thread,sig);
  assert(result==0);
  if(!pthread_equal(thread,registered->id))return result;
  atomic_store_explicit(&signaled,1,memory_order_release);
  while(!atomic_load_explicit(&retired,memory_order_acquire))sched_yield();
  return result;
}
static void *worker(void *unused) {
  (void)unused;
  sigset_t mask;sigemptyset(&mask);sigaddset(&mask,GC_SIG);
  assert(!pthread_sigmask(SIG_BLOCK,&mask,NULL));
  thr_register((uintptr_t)__builtin_frame_address(0)+16);
  registered=thr_self;
  atomic_store_explicit(&ready,1,memory_order_release);
  while(!atomic_load_explicit(&signaled,memory_order_acquire))sched_yield();
  // The collector already observed live and successfully queued its signal.
  // Retire before returning from its kill call; this thread never parks.
  thr_self->live=0;
#ifndef BASELINE
  // Deliver the queued signal during cleanup after retirement. It must not
  // enter parking or become an uncounted marking helper.
  assert(!pthread_sigmask(SIG_UNBLOCK,&mask,NULL));
  assert(!atomic_load(&thr_self->parked));
#endif
  atomic_store_explicit(&retired,1,memory_order_release);
  return NULL;
}
static void *live_helper(void *unused) {
  (void)unused;thr_register((uintptr_t)__builtin_frame_address(0)+16);
  atomic_store_explicit(&helper_ready,1,memory_order_release);
  while(!atomic_load_explicit(&helper_done,memory_order_acquire))sched_yield();
  thr_self->live=0;return NULL;
}
#ifndef BASELINE
_Static_assert(sizeof(_Atomic int)==sizeof(int),"atomic liveness keeps int ABI");
_Static_assert(offsetof(Thr,parked)==offsetof(Thr,live)+sizeof(int),"park flag uses adjacent old padding");
#if UINTPTR_MAX > UINT32_MAX
_Static_assert(offsetof(Thr,dq)==offsetof(Thr,live)+2*sizeof(int),"deque offset remains unchanged on64bit");
#endif
#endif
static V run(void) {
  pthread_attr_t attr;pthread_attr_init(&attr);thr_stack(&attr);pthread_t thread;
  assert(!pthread_create(&thread,&attr,worker,NULL));pthread_attr_destroy(&attr);
  while(!atomic_load_explicit(&ready,memory_order_acquire))sched_yield();
  pthread_t helper;pthread_attr_init(&attr);thr_stack(&attr);
  assert(!pthread_create(&helper,&attr,live_helper,NULL));pthread_attr_destroy(&attr);
  while(!atomic_load_explicit(&helper_ready,memory_order_acquire))sched_yield();
  gc_limit=SIZE_MAX; // prevent automatic collection before the forced race
  heap=arr_alloc(15);gc_root_add(&heap,1);
  for(unsigned j=0;j<32768;j++)arr_cells(heap)[j]=C2(37,j,IMM(0));
  gc_collect();
  assert(gc_nmks==2); // collector and live helper; retired target is excluded
  for(unsigned j=0;j<32768;j++)assert(FLD(arr_cells(heap)[j],0)==j);
  assert(!pthread_join(thread,NULL));
  assert(atomic_load(&retired) && !registered->live);
#ifdef TEST_PARKED
  assert(!atomic_load(&registered->parked));
#endif
  assert(atomic_load(&gc_acks)==1 && atomic_load(&gc_inside)==0);
  atomic_store_explicit(&helper_done,1,memory_order_release);
  assert(!pthread_join(helper,NULL));
  gc_collect();return UNIT;
}
static void print(V v){(void)v;puts("ok");}
int main(int argc,char **argv){bend_rc_req=1;bend_rc_trace_req=1;return bend_run_value(argc,argv,run,print);}
