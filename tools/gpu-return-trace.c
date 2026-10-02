// Diagnostic for the closed Tree in gpu_growth_pinned.bend.
// Inspect bounded raw fields before the ordinary CPU consumer runs.
#define main fixture_main
#include "pin_program.c"
#undef main

static int scan_failed;
static V scan_main(void) {
  int special=getenv("BEND_SCAN_SPECIAL")!=NULL;
  V root;
  if(special) { V args[]={1};if(!gpu_call(&K_PROG,KL_make_x37s2491568216x8239786,args,1,1,&root)) {fprintf(stderr,"special producer failed\n");scan_failed=1;return UNIT;} }
  else root=G_make(13,3);
  unsigned expected_nodes=special?255:8191,expected_leaves=special?256:8192;
  uint64_t expected_sum=special?3328:184320;
  fprintf(stderr, "pin scan: mode=%d root=%llx arena=%llx bytes=%llu\n", gpu_mode,
    (unsigned long long)root, (unsigned long long)(uintptr_t)gpu_H, (unsigned long long)gpu_Hn);
  if(gpu_A) {fprintf(stderr,"phase trace:");for(int i=7;i<16;i++) fprintf(stderr," %u",gpu_A[i]);fprintf(stderr,"\n");}
  if ((gpu_mode!=GPU_METAL && gpu_mode!=GPU_SIM) ||
      !gpu_A || gpu_A[KA_ERR]!=0 || gpu_A[KA_DONE]!=1) {
    fprintf(stderr,"pin scan: no completed device call to inspect\n");
    scan_failed=1;return UNIT;
  }
  int pinned=(uintptr_t)root-(uintptr_t)gpu_H<gpu_Hn;
  int expected_pin=atol(getenv("BEND_GPU_PIN_MB"))==0;
  if (pinned!=expected_pin) {
    fprintf(stderr,"pin scan: expected %s result but got %s\n",
      expected_pin?"arena":"CPU",pinned?"arena":"CPU");
    scan_failed=1;return UNIT;
  }
  struct Item { V value; unsigned depth; uint64_t path; } stack[64];
  unsigned sp=1, visits=0, leaves=0, nodes=0;
  uint64_t sum=0;
  stack[0]=(struct Item){root,0,0};
  while (sp) {
    struct Item item=stack[--sp]; V v=item.value;
    if (++visits>32768) { fprintf(stderr,"pin scan: too many visits\n");scan_failed=1;break; }
    if (IS_LI(v,0)) {sum+=LI_V(v);leaves++;continue;}
    uintptr_t offset=(uintptr_t)v-(uintptr_t)gpu_H;
    int arena=gpu_Hn>=2*sizeof(KW) && offset>=sizeof(KW) && offset<=gpu_Hn-2*sizeof(KW);
    uintptr_t cpu_offset=(uintptr_t)v-gc_hot.base;
    int cpu=gc_hot.span>=2*sizeof(V) && cpu_offset<=gc_hot.span-2*sizeof(V);
    if ((v&7) || (!arena && !cpu)) {
      fprintf(stderr,"pin scan: invalid value=%016llx depth=%u path=%llx\n",
        (unsigned long long)v,item.depth,(unsigned long long)item.path);
      scan_failed=1;break;
    }
    KW h=arena?((KW *)v)[-1]:0,a=((V *)v)[0],b=((V *)v)[1];
    if ((arena && h!=(K_BARE|2)) || sp+2>64 || item.depth>=32) {
      fprintf(stderr,"pin scan: invalid node offset=%llx header=%016llx left=%016llx right=%016llx depth=%u path=%llx\n",
        (unsigned long long)offset,(unsigned long long)h,(unsigned long long)a,(unsigned long long)b,
        item.depth,(unsigned long long)item.path);
      scan_failed=1;break;
    }
    if (nodes<16) fprintf(stderr,"pin node: depth=%u path=%llx value=%llx header=%llx left=%llx right=%llx\n",item.depth,(unsigned long long)item.path,(unsigned long long)v,(unsigned long long)h,(unsigned long long)a,(unsigned long long)b);
    nodes++;
    stack[sp++]=(struct Item){b,item.depth+1,(item.path<<1)|1};
    stack[sp++]=(struct Item){a,item.depth+1,item.path<<1};
  }
  if (nodes!=expected_nodes || leaves!=expected_leaves || sum!=expected_sum) scan_failed=1;
  fprintf(stderr,"pin scan: nodes=%u leaves=%u sum=%llu invalid=%d\n",nodes,leaves,(unsigned long long)sum,scan_failed);
  if (!scan_failed) {
    bend_share(root);
    fprintf(stderr,"pin scan: running ordinary CPU sum\n");
    V actual=F_sum(root);
    fprintf(stderr,"pin scan: CPU sum=%llu\n",(unsigned long long)actual);
    if (actual!=expected_sum) scan_failed=1;
  }
  return UNIT;
}
static void scan_print(V value) { (void)value; }
int main(int argc, char **argv) {
  setenv("BEND_GPU_MB0","4",1);setenv("BEND_GPU_MB","128",1);
  setenv("BEND_GPU_LANES","64",1);
  if (!getenv("BEND_GPU_KQCPU")) setenv("BEND_GPU_KQCPU","0",1);
  if (!getenv("BEND_GPU_PIN_MB")) setenv("BEND_GPU_PIN_MB","0",1);setenv("BEND_GPU_LOG","2",1);
  bend_print_fn=scan_print;
  int r=bend_start(argc,argv,scan_main,1);
  return r?r:scan_failed;
}
