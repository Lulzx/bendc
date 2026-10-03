#include "bendrt.h"
#include <assert.h>
static V run(void) {
 size_t base=rc_live();V a=arr_alloc(12);
 for(unsigned j=0;j<4096;j++)arr_cells(a)[j]=C1(23,j);
 rc_drop(a);assert(rc_live()==base);assert(thr_self->rccap<=1024);
 // A deep chain of wide arrays tests iterative continuation frames.
 a=C1(29,42);
 for(unsigned j=0;j<4096;j++) {
  V n=arr_alloc(6);for(unsigned k=0;k<64;k++)arr_cells(n)[k]=UNIT;
  arr_cells(n)[0]=a;a=n;
 }
 rc_drop(a);assert(rc_live()==base);assert(thr_self->rcn==0);
 // Nested traversal must preserve an outer pending continuation verbatim.
 V outer=arr_alloc(6);for(unsigned k=0;k<64;k++)arr_cells(outer)[k]=UNIT;
 arr_cells(outer)[1]=C1(31,7);
 rc_push(thr_self,2);rc_push(thr_self,outer|2);
 size_t prefix=thr_self->rcn;
 a=arr_alloc(12);for(unsigned j=0;j<4096;j++)arr_cells(a)[j]=C1(23,j);
 rc_publish(a);
 assert(thr_self->rcn==prefix && thr_self->rcs[0]==2 && thr_self->rcs[1]==(outer|2));
 rc_drop(a);
 assert(thr_self->rcn==prefix && thr_self->rcs[0]==2 && thr_self->rcs[1]==(outer|2));
 thr_self->rcn=0;rc_drop(outer);assert(rc_live()==base);
 return UNIT;
}
static void print(V v){(void)v;puts("ok");}
int main(int argc,char **argv){bend_rc_req=1;bend_rc_trace_req=1;return bend_run_value(argc,argv,run,print);}
