#define main program_main
#include "reduce-positive.c"
#undef main
#include <assert.h>
static KW arena[1<<20], borrowed[8192], snapshot[1<<20];
static KAU controls[KA_SEQ+16];
static KW make(KCtx*c,unsigned d,KU seed,int dag){
 if(!d)return (seed&1)?KIMM(0):KLI(1,seed);
 KW a=make(c,d-1,seed*1664525u+1u,dag),b=dag?a:make(c,d-1,seed*214013u+3u,dag),r=k_node(c,2+seed%4,2),ix=KIX(c,r);c->H[ix+1]=a;c->H[ix+2]=b;return r;
}
static KU ref(KCtx*c,KW v,KU x,int count){
 if(v==KIMM(0))return count?1:(x^17u);
 if(KIS_LI(v,1))return count?1:((KU)KLI_V(v)+3u);
 KU t=(KU)k_tag(c,v),l=ref(c,k_word(c,v,1),x,count),r=ref(c,k_word(c,v,2),x,count);
 if(count)return 1u+l+r;
 switch(t){case 2:return l+r;case 3:return l-r;case 4:return l*r;case 5:return l^r;default:assert(0);return 0;}
}
int main(void){
 KParams p={0};p.ab=(KW)(uintptr_t)arena;p.an=sizeof arena;p.heap0=1024;p.heapw=(sizeof arena/sizeof(KW))-p.heap0;p.nlanes=1;
 for(unsigned d=0;d<=10;d++)for(int dag=0;dag<2;dag++)for(KU x=0;x<3;x++){
  memset(arena,0,sizeof arena);memset(controls,0,sizeof controls);controls[KA_HEAP]=1;
  KCtx c={0};c.H=arena;c.G=borrowed;c.A=controls;c.P=&p;c.ab=p.ab;c.an=p.an;c.gb=(KW)(uintptr_t)borrowed;c.kqlim=100000;
  KW tree=make(&c,d,0xfffffffeu+x,dag),hp=c.hp;memcpy(snapshot,arena,sizeof arena);
  KU arg=x==2?0xffffffffu:x;for(KU count=0;count<2;count++){
   bool hit=false;KW got=(count?KR_count_try(&c,tree,&hit):KR_fold_try(&c,tree,arg,17u,&hit));assert(hit==(d<=8));
   KU expected=ref(&c,tree,arg,count);if(hit)assert((KU)got==expected);
   bool ok=true;KW actual=count?KQ_count(&c,tree,&ok):KQ_fold(&c,tree,arg,17u,&ok);assert(!c.err);if(hit)assert(ok&&(KU)actual==expected);else assert(!ok);
  }
  assert(c.hp==hp);if(hp>1026)assert(!memcmp(snapshot+1026,arena+1026,(hp-1026)*sizeof(KW)));
 }
 for(unsigned d=7;d<=8;d++) {
  memset(arena,0,sizeof arena);memset(borrowed,0,sizeof borrowed);memset(controls,0,sizeof controls);controls[KA_HEAP]=1;
  KCtx c={0};c.H=arena;c.G=borrowed;c.A=controls;c.P=&p;c.ab=p.ab;c.an=p.an;c.gb=(KW)(uintptr_t)borrowed;c.kqlim=100000;
  KW a=make(&c,d,0xfffffffeu,0);
  borrowed[4096]=5;borrowed[4097]=a;borrowed[4098]=KLI(1,UINT32_MAX);
  KW tree=(KW)(uintptr_t)(borrowed+4096),hp=c.hp,bs[8192];memcpy(bs,borrowed,sizeof bs);memcpy(snapshot,arena,sizeof arena);
  for(KU mode=0;mode<2;mode++) {
   bool hit=false;KW got=mode?KR_count_try(&c,tree,&hit):KR_fold_try(&c,tree,UINT32_MAX,17u,&hit);
   assert(hit==(d==7));KU expected=ref(&c,tree,UINT32_MAX,mode);if(hit)assert((KU)got==expected);
   bool ok=true;KW actual=mode?KQ_count(&c,tree,&ok):KQ_fold(&c,tree,UINT32_MAX,17u,&ok);assert(!c.err);if(hit)assert(ok&&(KU)actual==expected);else assert(!ok);
  }
  assert(c.hp==hp&&!memcmp(bs,borrowed,sizeof bs));assert(!memcmp(snapshot+1026,arena+1026,(hp-1026)*sizeof(KW)));
 }
 puts("pure postorder: depth0..10, mixed operators, DAGs, overflow, cap fallback, borrowed/arena mixtures and input preservation passed");
}
