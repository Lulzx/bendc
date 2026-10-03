#include "bendrt.h"
#include <assert.h>
static V run(void) {
 size_t base=rc_live();
 for(unsigned width=513;width<=527;width++)for(unsigned mode=0;mode<4;mode++)for(unsigned shared=0;shared<2;shared++) {
  V *a=halloc(width);a[0]=47; V fields[526];
  for(unsigned j=1;j<width;j++){fields[j-1]=C1(17,j);a[j]=fields[j-1];}
  assert(!bend_rp_size((V)a,width));if(shared)rc_dup((V)a);V tok=0;
  if(mode==0)rc_take((V)a,width);
  if(mode==1)tok=rc_take_ru((V)a,width);
  if(mode==2)rc_take_d((V)a,width,~(V)0);
  if(mode==3)tok=rc_take_ru_d((V)a,width,~(V)0);
  if(tok)RUF(tok,width);
  if(shared){for(unsigned j=1;j<width;j++)assert(!rc_unique(fields[j-1]));rc_drop((V)a);}
  for(unsigned j=1;j<width;j++){assert(rc_unique(fields[j-1]));assert(((V*)fields[j-1])[1]==j);rc_drop(fields[j-1]);}
  assert(rc_live()==base);
 }
 V x=C1(19,1),y=C1(19,2);V vals[]={4294967295u,x,y};V a=RPN(0,31,3,vals);
 assert(bend_rp_size(a,RP_SIZE+3));assert(!bend_rp_size(a,515));assert(!bend_rp_size(0,RP_SIZE+3));
 rc_take_d(a,RP_SIZE+3,~(V)0);rc_drop(x);rc_drop(y);assert(rc_live()==base);
 return UNIT;
}
static void print(V v){(void)v;puts("ok");}
int main(int argc,char **argv){bend_rc_req=1;bend_rc_trace_req=1;return bend_run_value(argc,argv,run,print);}
