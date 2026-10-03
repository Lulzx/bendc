#define main program_main
#include "zipper-positive.c"
#undef main
#include <assert.h>
static KW arena[1<<20], borrowed[128];
static KAU controls[KA_SEQ+16];
static KW make(KCtx*c,unsigned d,unsigned seed,int dag) {
 if(!d){KW r=k_node(c,0,2),ix=KIX(c,r);for(int i=0;i<2;i++)c->H[ix+1+i]=(KU)(seed+i);return r;}
 KW a=make(c,d-1,seed,dag),b=dag?a:make(c,d-1,seed+11,dag),r=k_node(c,1,2),ix=KIX(c,r);c->H[ix+1]=a;c->H[ix+2]=b;return r;
}
static KW generic(KCtx*c,KW a,KW b) {
 if(k_tag(c,a)==0 && k_tag(c,b)==0) {
 KW r=k_node(c,0,2),ix=KIX(c,r);
 c->H[ix+1]=(KU)((KU)k_word(c,a,1)+(KU)k_word(c,b,1));
 c->H[ix+2]=(KU)k_word(c,a,2)^(KU)k_word(c,b,2);return r;
 }
 if(k_tag(c,a)==0) {KW r=k_node(c,0,2),ix=KIX(c,r);for(int i=0;i<2;i++)c->H[ix+1+i]=k_word(c,a,1+i);return r;}
 if(k_tag(c,b)==0) {KW r=k_node(c,1,2),ix=KIX(c,r);for(int i=0;i<2;i++)c->H[ix+1+i]=k_word(c,a,1+i);return r;}
 KW l=generic(c,k_word(c,a,1),k_word(c,b,1)),r=generic(c,k_word(c,a,2),k_word(c,b,2));KW out=k_node(c,1,2),ix=KIX(c,out);c->H[ix+1]=l;c->H[ix+2]=r;return out;
}
static int equal(KCtx*c,KW a,KW b) {
 if(k_tag(c,a)!=k_tag(c,b))return 0;
 for(int i=0;i<(k_tag(c,a)?2:2);i++)if(k_tag(c,a)?!equal(c,k_word(c,a,1+i),k_word(c,b,1+i)):k_word(c,a,1+i)!=k_word(c,b,1+i))return 0;
 return 1;
}
static KU hash(KCtx*c,KW a){if(k_tag(c,a)==0)return (KU)k_word(c,a,1)*31u+(KU)k_word(c,a,2);return hash(c,k_word(c,a,1))*2654435761u+hash(c,k_word(c,a,2));}
int main(void){
 KParams p={0};p.ab=(KW)(uintptr_t)arena;p.an=sizeof arena;p.heap0=1024;p.heapw=(sizeof arena/sizeof(KW))-p.heap0;p.nlanes=1;
 KCtx c={0};c.H=arena;c.G=borrowed;c.A=controls;c.P=&p;c.ab=p.ab;c.an=p.an;c.gb=(KW)(uintptr_t)borrowed;c.kqlim=100000;controls[KA_HEAP]=1;k_anone(&c);
 for(int d=0;d<=4;d++)for(int e=0;e<=4;e++)for(int dag=0;dag<2;dag++){
   KW a=make(&c,d,0xfffffffc,dag),b=make(&c,e,19,dag);KW beforeA[4096];
   KW hp=c.hp;assert(hp<3000);memcpy(beforeA,arena+1026,(hp-1026)*sizeof(KW));
   bool ok=true;KW fast=KQ_combine(&c,a,b,&ok), ref=generic(&c,a,b);
   assert(ok&&!c.err&&equal(&c,fast,ref));assert(!memcmp(beforeA,arena+1026,(hp-1026)*sizeof(KW)));
   memset(arena,0,sizeof arena);memset(controls,0,sizeof controls);controls[KA_HEAP]=1;c.hp=c.he=c.hs=c.blocks=c.spare=0;
 }
 for(int dag=0;dag<2;dag++){
   KW a=make(&c,3,0xfffffffc,dag),b=make(&c,3,19,dag);KW h0=c.hp,e0=c.he,b0=c.blocks;
   KW fast=KZ_combine_3(&c,a,b),end=c.hp,start=(c.blocks==b0?h0:c.blocks+2),count=0;
   for(KW at=start;at<end;at+=k_psize(arena[at])+1){assert(arena[at]&K_PACK);count++;}
   assert(count==15&&end-start==37);KU expected=hash(&c,fast);KW masks[]={0,6};
   KW compact=k_tree_compact(&c,h0,e0,b0,fast,masks,2);assert(!c.err&&hash(&c,compact)==expected);
   memset(arena,0,sizeof arena);memset(controls,0,sizeof controls);controls[KA_HEAP]=1;c.hp=c.he=c.hs=c.blocks=c.spare=0;
 }
 { // Two scalar cells can resemble a real pointer; never trace them.
   KW a=make(&c,0,0,0),b=make(&c,0,0,0),fake=(KW)(uintptr_t)(arena+1100),ix=KIX(&c,a);
   arena[ix+1]=(KU)fake;arena[ix+2]=(KU)(fake>>32);
   KW h0=c.hp,e0=c.he,b0=c.blocks,fast=KZ_combine_0(&c,a,b);KU expected=hash(&c,fast);KW masks[]={0,6};
   KW out=k_tree_compact(&c,h0,e0,b0,fast,masks,2);assert(!c.err&&hash(&c,out)==expected);
 }
 puts("depth 0..4 x 0..4, mixed topology, DAG aliases, input preservation and U32 overflow: passed");
}
