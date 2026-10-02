#include <assert.h>
#include "bendrt.h"
#include "gpu.h"
KINLINE KW k_frame_size(KW l) { (void)l;return 4; }
KINLINE void k_cases(KCtx*c) { k_fail(c,KE_PC); }
KINLINE KW k_kq(KCtx*c,bool*ok) { (void)c;*ok=false;return 0; }
#include "gpuhost.h"
#if BEND_METAL
static const char source[]=
"\n"
"KINLINE KW k_frame_size(KW l) { return 4; }\n"
"KINLINE void k_cases(KTHR KCtx *c) { k_fail(c, KE_PC); }\n"
"KINLINE KW k_kq(KTHR KCtx *c,KTHR bool *ok) { *ok=false; return 0; }\n"
"KCONST KW probe_masks[]={0,K_TREE_BARE_MASK|3};\n"
"kernel void prefix_small(device coherent(device) KW *H [[buffer(0)]],device KAU *A [[buffer(1)]],constant KParams &PP [[buffer(2)]],device KW *G [[buffer(3)]],uint lane [[thread_position_in_grid]]) {\n"
"  if(lane>=PP.nlanes) return;\n"
"  KCtx c;k_load(&c,H,A,&PP,G,lane);\n"
"  KW older=k_bnode(&c,2);H[KIX(&c,older)]=KLI(0,7);H[KIX(&c,older)+1]=KLI(0,11);\n"
"  KW h0=c.hp,e0=c.he,b0=c.blocks;\n"
"  KW r=k_bnode(&c,2);H[KIX(&c,r)]=KLI(0,13);H[KIX(&c,r)+1]=KLI(0,17);\n"
"  KW result=k_tree_compact(&c,h0,e0,b0,r,probe_masks,2);\n"
"  H[lane*8]=result;H[lane*8+1]=c.ab;H[lane*8+2]=c.hp;H[lane*8+3]=c.err;\n"
"  H[lane*8+4]=k_in(&c,result)?H[KIX(&c,result)]:0;\n"
"  H[lane*8+5]=k_in(&c,result)?H[KIX(&c,result)+1]:0;\n"
"  H[lane*8+6]=h0;H[lane*8+7]=r;\n"
"}\n";
#endif
int main(void) {
#if BEND_METAL
 setenv("BEND_GPU_MB0","4",1);setenv("BEND_GPU_MB","16",1);setenv("BEND_GPU_LANES","64",1);
 gc_init();const GpuFn functions[]={{NULL,0}};const GpuProg prog={source,NULL,NULL,functions,NULL};
 gpu_mode=gpu_setup(&prog);assert(gpu_mode==GPU_METAL);
 void*pool=g_pool_push();GId lib=g_compile(&prog),error=NULL;
 GId pipeline=lib?g_pipe(g_desc(lib,"prefix_small"),NULL,&error):NULL;assert(pipeline && g_heap());
 memset(gpu_A,0,gpu_An);memset(gpu_H,0,gpu_Hn);gpu_A[KA_HEAP]=1;
 KParams p={0};p.ab=(KW)(uintptr_t)gpu_H;p.an=gpu_Hn;p.gb=(KW)(uintptr_t)gc_base;
 p.lane0=8192;p.nlanes=8;p.heap0=65536;p.heapw=gpu_Hn/8-p.heap0;
 assert(g_dispatch(&p,pipeline));int bad=0;
 for(int lane=0;lane<8;lane++) {KW*s=gpu_H+lane*8;
 fprintf(stderr,"prefix unit lane %d: result=%llx base=%llx hp=%llu err=%llu left=%llx right=%llx h0=%llu oldroot=%llx\n",lane,(unsigned long long)s[0],(unsigned long long)s[1],(unsigned long long)s[2],(unsigned long long)s[3],(unsigned long long)s[4],(unsigned long long)s[5],(unsigned long long)s[6],(unsigned long long)s[7]);
 if(s[0]!=s[1]+8*(s[6]+1) || s[3] || s[4]!=KLI(0,13) || s[5]!=KLI(0,17)) bad++;
 }
 g_msg(pipeline,"release");g_msg(lib,"release");g_pool_pop(pool);return bad?1:0;
#else
 return 0;
#endif
}
