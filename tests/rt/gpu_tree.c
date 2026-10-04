
#include <stdint.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
// (every frame compacts: these check the copying itself, see K_TREE_LAZY)
#define K_TREE_LAZY 0
#include "gpu.h"
KINLINE KW k_frame_size(KW l) { (void)l; return 0; }
KINLINE void k_cases(KCtx *c) { k_fail(c, KE_PC); }
KINLINE KW k_kq(KCtx *c, bool *ok) { (void)c; *ok=false; return 0; }
static KW masks[]={0,6};
static KW leaf(KCtx*c,KW a) {KW p=k_node(c,0,3),i=KIX(c,p);c->H[i+1]=a;c->H[i+2]=2;c->H[i+3]=3;return p;}
static KW pair(KCtx*c,KW a,KW b) {KW p=k_node(c,1,2),i=KIX(c,p);c->H[i+1]=a;c->H[i+2]=b;return p;}
static KW make(KCtx*c,int d,KW a) {if(!d)return leaf(c,a);KW l=make(c,d-1,a),r=make(c,d-1,a);return pair(c,l,r);}
static KW merge(KCtx*c,KW a,KW b) {if(!k_tag(c,a))return leaf(c,k_word(c,a,1)+k_word(c,b,1));KW l=merge(c,k_word(c,a,1),k_word(c,b,1));KW r=merge(c,k_word(c,a,2),k_word(c,b,2));return pair(c,l,r);}
static KW sum(KCtx*c,KW a) {return !k_tag(c,a)?k_word(c,a,1):sum(c,k_word(c,a,1))+sum(c,k_word(c,a,2));}
static KW bare_pair(KCtx*c,KW a,KW b) {KW p=k_bnode(c,2),i=KIX(c,p);c->H[i]=a;c->H[i+1]=b;return p;}
static KW bare_make(KCtx*c,int d,KW v) {if(!d)return KLI(0,v);KW l=bare_make(c,d-1,v),r=bare_make(c,d-1,v);return bare_pair(c,l,r);}
static KW bare_sum(KCtx*c,KW a) {return !k_in(c,a)?KLI_V(a):bare_sum(c,c->H[KIX(c,a)])+bare_sum(c,c->H[KIX(c,a)+1]);}
static KW fold(KCtx*c,int depth,int compact) {
  KW h0=c->hp,e0=c->he,b0=c->blocks,r;
  if(!depth)r=make(c,3,1);
  else {KW l=fold(c,depth-1,compact);if(c->err)return 0;KW right=fold(c,depth-1,compact);if(c->err)return 0;r=merge(c,l,right);}
  return compact?k_tree_compact(c,h0,e0,b0,r,masks,2):r;
}
KCONST KW empty_schema[]={0};
KINLINE KCP KW *k_tree_schema(KW id) {(void)id;return empty_schema;}
static KW scalar_rounds(KCtx *c,bool *ok) {
  KW sp=0,RV=0;K_TREE_STACK;
  for(int i=0;i<200;i++) {
    K_TREE_MARK(0);
    KW t=make(c,7,1);if(c->err){*ok=false;return 0;}
    RV+=sum(c,t);
  }
  K_TREE_RET;return RV;
}
static void init(KCtx*c,KParams*p,KW*h,KAU*a,KW words) {memset(c,0,sizeof(*c));memset(p,0,sizeof(*p));memset(h,0,words*8);memset(a,0,32*4);p->ab=(KW)h;p->an=words*8;p->heap0=256;p->heapw=words-256;c->H=h;c->A=a;c->ab=p->ab;c->an=p->an;c->P=p;K_STORE(a+KA_HEAP,1);}
int main(void) {
  KW words=65536;KW*h=calloc(words,8);KAU a[32];KCtx c;KParams p;
  for(int compact=0;compact<2;compact++) {
    init(&c,&p,h,a,words);KW r=0;int count=0;
    for(;count<128;count++) {
      KW h0=c.hp,e0=c.he,b0=c.blocks;
      r=fold(&c,10,compact);if(c.err)break;assert(sum(&c,r)==8192);
      k_rewind(&c,h0,e0,b0);
    }

    if(compact)assert(count==128 && a[KA_HEAP]<80);else assert(count<128 && c.err==KE_HEAP);
  }
  // A scalar equal to an arena pointer must not be rewritten.
  init(&c,&p,h,a,words);KW scalar=KPTR(&c,513),r=leaf(&c,scalar);
  r=k_tree_compact(&c,0,0,0,r,masks,2);assert(k_word(&c,r,1)==scalar);
  // DAG aliases may be copied separately; their values must survive.
  init(&c,&p,h,a,words);KW l=leaf(&c,7);r=pair(&c,l,l);
  r=k_tree_compact(&c,0,0,0,r,masks,2);assert(sum(&c,r)==14);
  // Older objects in the starting span must retain both address and data.
  init(&c,&p,h,a,words);KW older=leaf(&c,7),h0=c.hp,e0=c.he,b0=c.blocks;
  r=pair(&c,older,leaf(&c,9));
  r=k_tree_compact(&c,h0,e0,b0,r,masks,2);
  assert(k_word(&c,r,1)==older && sum(&c,r)==16 && sum(&c,older)==7);
  assert(k_tree_compact(&c,c.hp,c.he,c.blocks,older,masks,2)==older);
  // A copied DAG can pack into the old prefix without changing its older
  // neighbor. All copied child pointers must follow the relocated graph.
  init(&c,&p,h,a,words);older=leaf(&c,17);h0=c.hp;e0=c.he;b0=c.blocks;
  l=leaf(&c,7);r=pair(&c,l,l);
  r=k_tree_compact(&c,h0,e0,b0,r,masks,2);
  assert(c.blocks==b0 && r==KPTR(&c,h0+1) && sum(&c,r)==14 && sum(&c,older)==17);
  // If the live graph does not fit the starting tail, abandon the private
  // staging copy and use output spans, preserving all older objects.
  init(&c,&p,h,a,words);older=leaf(&c,7);KW padding=k_alloc(&c,243);
  c.H[KIX(&c,padding)]=123;h0=c.hp;e0=c.he;b0=c.blocks;
  assert(e0-h0==5);r=pair(&c,older,leaf(&c,9));
  r=k_tree_compact(&c,h0,e0,b0,r,masks,2);
  assert(c.blocks!=b0 && sum(&c,r)==16 && sum(&c,older)==7);
  assert(c.H[KIX(&c,padding)]==123);
  // Depth guard aborts without modifying the source graph.
  init(&c,&p,h,a,words);r=leaf(&c,1);for(int i=0;i<70;i++)r=pair(&c,r,leaf(&c,0));
  KW old=r,check=sum(&c,r);r=k_tree_compact(&c,0,0,0,r,masks,2);assert(r==old && c.err==0 && sum(&c,r)==check);
  // Output allocation failure preserves the source for host retry.
  init(&c,&p,h,a,words);r=make(&c,7,9);old=r;check=sum(&c,r);
  p.heapw=a[KA_HEAP]*K_CHUNK;
  r=k_tree_compact(&c,0,0,0,r,masks,2);assert(r==old && c.err==KE_HEAP && sum(&c,r)==check);
  // Reentry at the same stack depth discards only a pure scalar call's
  // dead temporary graphs; its older caller objects remain valid.
  init(&c,&p,h,a,words);older=leaf(&c,17);h0=c.hp;e0=c.he;b0=c.blocks;
  bool ok=true;assert(scalar_rounds(&c,&ok)==25600 && ok && c.err==0);
  assert(c.hp==h0 && c.he==e0 && c.blocks==b0 && sum(&c,older)==17);
  assert(a[KA_HEAP]<20);
  // Headerless branches and immediate leaves use the exact type schema.
  KW bare_masks[]={0,K_TREE_BARE_MASK|3};
  init(&c,&p,h,a,words);older=bare_pair(&c,KLI(0,7),KLI(0,11));
  h0=c.hp;e0=c.he;b0=c.blocks;
  r=bare_pair(&c,older,bare_pair(&c,KLI(0,13),KLI(0,17)));
  r=k_tree_compact(&c,h0,e0,b0,r,bare_masks,2);
  assert(c.err==0 && bare_sum(&c,r)==48 && bare_sum(&c,older)==18);
  assert(c.H[KIX(&c,r)]==older && (c.H[KIX(&c,r)-1]&K_BARE));
  // Multi-span bare graphs survive repeated copying and reclamation.
  init(&c,&p,h,a,words);older=bare_pair(&c,KLI(0,7),KLI(0,11));h0=c.hp;e0=c.he;b0=c.blocks;
  for(int round=0;round<128;round++) {
    r=bare_make(&c,7,1);r=k_tree_compact(&c,h0,e0,b0,r,bare_masks,2);
    assert(c.err==0 && bare_sum(&c,r)==128 && bare_sum(&c,older)==18);
    // The root precedes descendants in other spans. The legacy one-node
    // region helper must not reuse their storage based on the root alone.
    r=k_region(&c,h0,e0,r);
    KW noise=k_alloc(&c,130);
    for(KW j=0;j<130;j++)c.H[KIX(&c,noise)+j]=0;
    assert(c.err==0 && bare_sum(&c,r)==128 && bare_sum(&c,older)==18);
    k_rewind(&c,h0,e0,b0);
  }
  assert(a[KA_HEAP]<32);
  // A new root in the last span can reach live descendants in that span
  // indirectly, through a compacted child rooted in an earlier one.
  init(&c,&p,h,a,words);h0=c.hp;e0=c.he;b0=c.blocks;
  l=bare_make(&c,7,1);l=k_tree_compact(&c,h0,e0,b0,l,bare_masks,2);
  KW late=c.hs+1,left=h[late],right=h[late+1];
  assert(KIX(&c,l)<c.hs && h[late-1]==(K_BARE|2));
  r=bare_pair(&c,l,KLI(0,1));
  assert(KIX(&c,r)>=c.hs && bare_sum(&c,r)==129);
  r=k_region(&c,h0,e0,r);
  assert(h[late]==left && h[late+1]==right && bare_sum(&c,r)==129);
  KW noise2=k_alloc(&c,130);
  for(KW j=0;j<130;j++)h[KIX(&c,noise2)+j]=15;
  assert(bare_sum(&c,r)==129);
  // A scalar field with address-shaped bits is not a Self pointer.
  init(&c,&p,h,a,words);scalar=KPTR(&c,513);r=k_bnode(&c,3);
  c.H[KIX(&c,r)]=scalar;c.H[KIX(&c,r)+1]=KLI(0,23);c.H[KIX(&c,r)+2]=KLI(0,29);
  KW mixed_masks[]={0,K_TREE_BARE_MASK|6};
  r=k_tree_compact(&c,0,0,0,r,mixed_masks,2);
  assert(c.err==0 && c.H[KIX(&c,r)]==scalar && KLI_V(c.H[KIX(&c,r)+1])==23);
  // A mismatched headered schema must preserve the original bare graph.
  init(&c,&p,h,a,words);r=bare_pair(&c,KLI(0,31),KLI(0,37));old=r;
  r=k_tree_compact(&c,0,0,0,r,masks,2);
  assert(r==old && c.err==0 && bare_sum(&c,r)==68);
  free(h);puts("ok");
}
