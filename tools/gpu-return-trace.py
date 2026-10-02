#!/usr/bin/env python3
"""Isolated diagnostic controls; no runtime files in the checkout are changed."""
from pathlib import Path
import subprocess,shutil,os,json,sys,hashlib
root=Path(__file__).resolve().parent.parent
os.chdir(root)
base=os.environ.get('BEND_BASE',str(Path.home()/'.bend/bend2/base.bend'))
out=root/'build/gpu-return-trace';out.mkdir(parents=True,exist_ok=True)
receipt=json.loads((root/'tools/gpu-return-program.json').read_text())
fixture=root/'tools/gpu-return-program.c'
assert hashlib.sha256(fixture.read_bytes()).hexdigest()==receipt['generated_c_sha256']
shutil.copyfile(fixture,out/'pin_program.c')
results=[]
for name,kq in [('explicit-birth-zero',0)]:
 d=out/name;d.mkdir(exist_ok=True)
 rt=d/'rt';shutil.copytree(root/'rt',rt,dirs_exist_ok=True)
 gpu=(rt/'gpu.h').read_text()
 if name.startswith('explicit-birth'):
  gpu=gpu.replace('if (c->H[p + i] - b < n) return r;', 'if (k_in(c, c->H[p + i])) return r;')
  start=gpu.index('#define K_TREE_STACK')
  end=gpu.index('// A flat def keeps a Nat',start)
  gpu=gpu[:start]+r"""#define K_TREE_STACK KW kt_birth[32][5], kt_nb=0
#define K_TREE_MARK(id) do { \
  if(kt_nb>0) { \
    KW kt_prev=kt_nb-1; \
    if(kt_birth[kt_prev][3]==sp && k_tree_schema(id)[0]==0 && k_tree_schema(kt_birth[kt_prev][4])[0]==0) \
      k_rewind(c,kt_birth[kt_prev][0],kt_birth[kt_prev][1],kt_birth[kt_prev][2]); \
  } \
  bool kt_add=kt_nb==0; \
  if(kt_nb>0) kt_add=kt_birth[kt_nb-1][3]!=sp; \
  if(kt_add) { \
    if(kt_nb==32){*ok=false;return 0;} \
    kt_birth[kt_nb][0]=c->hp;kt_birth[kt_nb][1]=c->he; \
    kt_birth[kt_nb][2]=c->blocks;kt_birth[kt_nb][3]=sp; \
    kt_birth[kt_nb][4]=(id);kt_nb++; \
  } \
} while(0)
#define K_TREE_RET do { \
  while(kt_nb>0) { \
    KW kt_ix=kt_nb-1; \
    if(kt_birth[kt_ix][3]!=sp) break; \
    kt_nb=kt_ix;KCP KW *kt_schema=k_tree_schema(kt_birth[kt_ix][4]); \
    if(kt_schema[0]==0) k_rewind(c,kt_birth[kt_ix][0],kt_birth[kt_ix][1],kt_birth[kt_ix][2]); \
    else RV=k_tree_compact(c,kt_birth[kt_ix][0],kt_birth[kt_ix][1],kt_birth[kt_ix][2],RV,kt_schema+1,kt_schema[0]); \
    if(c->err){*ok=false;return 0;} \
  } \
} while(0)

"""+gpu[end:]
  if name.endswith('-zero'):
   gpu=gpu.replace('KW kt_birth[32][5], kt_nb=0','KW kt_birth[32][5]={{0}}, kt_nb=0')
  elif name.endswith('-flat'):
   import re
   gpu=gpu.replace('KW kt_birth[32][5], kt_nb=0', 'KW kt_h[32],kt_e[32],kt_b[32],kt_s[32],kt_t[32],kt_nb=0')
   fields=['kt_h','kt_e','kt_b','kt_s','kt_t']
   gpu=re.sub(r'kt_birth\[([^]]+)\]\[([0-4])\]',lambda m:fields[int(m[2])]+'['+m[1]+']',gpu)
   assert 'kt_birth[' not in gpu
  elif name.endswith('-index'):
   gpu=gpu.replace('if((mask&((KW)1<<i)) && v-base<bytes) v=KPTR(c,h0)+(v-base);',
     'if((mask&((KW)1<<i)) && k_in(&out,v) && KIX(&out,v)>=lo && KIX(&out,v)<out.hp) v=KPTR(c,h0+KIX(&out,v)-lo);')
   gpu=gpu.replace('KW relocated=KPTR(c,h0)+(root-base);','KW relocated=KPTR(c,h0+KIX(&out,root)-lo);')
  elif name.endswith('-aligned'):
   gpu=gpu.replace('if((mask&((KW)1<<i)) && v-base<bytes) v=KPTR(c,h0)+(v-base);',
     'if(mask&((KW)1<<i)) { if(!(v&7) && k_in(&out,v)) { KW vi=KIX(&out,v); if(vi>=lo && vi<out.hp) v=KPTR(c,h0+vi-lo); } }')
   gpu=gpu.replace('KW relocated=KPTR(c,h0)+(root-base);','KW relocated=KPTR(c,h0+1);')
 elif name=='split-prefix':
  start=gpu.index('    KW lo=out.hs,words=out.hp-lo,base=KPTR(&out,lo),bytes=words<<3;')
  end=gpu.index('    k_rewind(&out,0,0,b0);c->spare=out.spare;',start)
  body=gpu[start:end].replace('out.', 'out->').replace('&out','out')
  body=body.replace('KW relocated=KPTR(c,h0)+(root-base);','return KPTR(c,h0)+(root-base);')
  helper='KNOINLINE KW k_tree_pack(KTHR KCtx *c,KTHR KCtx *out,KW h0,KW root,KCP KW *masks,KW nmasks) {\n'+body+'}\n'
  gpu=gpu[:start]+'    KW words=out.hp-out.hs;\n    KW relocated=k_tree_pack(c,&out,h0,root,masks,nmasks);\n'+gpu[end:]
  gpu=gpu.replace('KNOINLINE KW k_tree_compact(',helper+'KNOINLINE KW k_tree_compact(')
 elif name=='guarded-prefix':
  gpu=gpu.replace('      (void)k_tree_layout(&out,KPTR(&out,at+1),masks,nmasks,&mask,&first);',
    '      if(n>=64 || n+1>out.hp-at || !k_tree_layout(&out,KPTR(&out,at+1),masks,nmasks,&mask,&first)) {k_fail(c,KE_MATCH);return r;}')
 elif name=='volatile-root':
  gpu=gpu.replace('KW root=k_tree_copy_node(c,&out,r);','volatile KW root=k_tree_copy_node(c,&out,r);')
  gpu=gpu.replace('KW relocated=KPTR(c,h0)+(root-base);','volatile KW relocated=KPTR(c,h0)+(root-base);')
 elif name=='return-words':
  record='if(c->lane==0) { K_STORE(&c->A[7],stage); K_STORE(&c->A[8],(KU)value); K_STORE(&c->A[9],(KU)(value>>32)); K_STORE(&c->A[10],(KU)r); K_STORE(&c->A[11],(KU)(r>>32)); K_STORE(&c->A[12],(KU)h0); K_STORE(&c->A[13],(KU)e0); K_STORE(&c->A[14],(KU)c->hp); K_STORE(&c->A[15],(KU)c->he); }'
  gpu=gpu.replace('    return relocated;', record.replace('stage','1').replace('value','relocated')+'\n    return relocated;')
  gpu=gpu.replace('  return root;', record.replace('stage','2').replace('value','root')+'\n  return root;')
 elif name=='index-prefix':
  gpu=gpu.replace('if((mask&((KW)1<<i)) && v-base<bytes) v=KPTR(c,h0)+(v-base);',
    'if((mask&((KW)1<<i)) && k_in(&out,v) && KIX(&out,v)>=lo && KIX(&out,v)<out.hp) v=KPTR(c,h0+KIX(&out,v)-lo);')
  gpu=gpu.replace('KW relocated=KPTR(c,h0)+(root-base);','KW relocated=KPTR(c,h0+KIX(&out,root)-lo);')
 elif name=='phase-trace':
  validator=r"""
KNOINLINE bool k_trace_value(KTHR KCtx *c,KW v,KW root,KU stage) {
  if(KIS_LI(v,0) || (k_in(c,v) && !(v&7) && c->H[KIX(c,v)-1]==(K_BARE|2))) return true;
  KU z=0;
  if(K_CAS(&c->A[7],z,stage)) {
    K_STORE(&c->A[8],(KU)v);K_STORE(&c->A[9],(KU)(v>>32));
    K_STORE(&c->A[10],(KU)root);K_STORE(&c->A[11],(KU)(root>>32));
    K_STORE(&c->A[12],(KU)c->hp);K_STORE(&c->A[13],(KU)c->lane);
    K_STORE(&c->A[14],(KU)c->he);K_STORE(&c->A[15],(KU)c->blocks);
  }
  k_fail(c,KE_MATCH);return false;
}
KNOINLINE bool k_trace_node(KTHR KCtx *c,KW root,KU stage) {
  if(!k_trace_value(c,root,root,stage)) return false;
  if(!k_in(c,root)) return true;
  KW ix=KIX(c,root);
  return k_trace_value(c,c->H[ix],root,stage) && k_trace_value(c,c->H[ix+1],root,stage);
}
"""
  gpu=gpu.replace('KINLINE KW k_tree_copy_node(',validator+'\nKINLINE KW k_tree_copy_node(')
  gpu=gpu.replace('  KW ix=KIX(src,v), raw=', '  if(!k_trace_node(src,v,1)) {k_fail(out,src->err);return 0;}\n  KW ix=KIX(src,v), raw=')
  gpu=gpu.replace('  return r;\n}\n// Bit 31', '  (void)k_trace_node(out,r,2);\n  return r;\n}\n// Bit 31')
  gpu=gpu.replace('      c->H[h0+at-lo]=raw;', '      if(!k_trace_node(&out,KPTR(&out,at+1),3)) {k_fail(c,out.err);return r;}\n      c->H[h0+at-lo]=raw;')
  gpu=gpu.replace('      at+=n+1;', '      if(!k_trace_node(c,KPTR(c,h0+at+1-lo),4)) return r;\n      at+=n+1;')
  gpu=gpu.replace('    return relocated;', '    (void)k_trace_node(c,relocated,5);\n    return relocated;')
 elif name=='safe-region':
  old='if (c->H[p + i] - b < n) return r;'
  assert gpu.count(old)==1
  gpu=gpu.replace(old,'if (k_in(c, c->H[p + i])) return r;')
 elif name=='no-prefix-pack':
  old='if(out.blocks!=b0 && out.H[out.blocks]==b0 && out.hp-out.hs<=e0-h0)'
  assert gpu.count(old)==1
  gpu=gpu.replace(old,'if(false && out.blocks!=b0 && out.H[out.blocks]==b0 && out.hp-out.hs<=e0-h0)')
 elif name=='scratch-prefix':
  gpu=gpu.replace('out.hp-out.hs<=e0-h0)', 'out.hp-out.hs<=e0-h0 && out.hp-out.hs<=K_CHUNK)')
  old='    for(KW at=lo;at<out.hp;) {\n      KW raw=out.H[at],n=raw & ~K_BARE,mask=0,first=0;'
  new='    KW packed[K_CHUNK];\n    for(KW i=0;i<words;i++) packed[i]=out.H[lo+i];\n    for(KW at=lo;at<out.hp;) {\n      KW raw=packed[at-lo],n=raw & ~K_BARE,mask=0,first=0;'
  assert gpu.count(old)==1
  gpu=gpu.replace(old,new).replace('KW v=out.H[at+1+i];','KW v=packed[at+1+i-lo];')
 elif name=='no-tree-compaction':
  old='if(c->err || !k_tree_new(c,h0,e0,b0,r)) return r;'
  assert gpu.count(old)==1
  gpu=gpu.replace(old,'return r; // diagnostic control only\n  '+old)

 if name in ('host-trace','index-prefix','return-words','volatile-root','split-prefix','guarded-prefix','explicit-birth'):
  host=(rt/'gpuhost.h').read_text()
  helper=r"""
static KW trace_roots[512];static unsigned trace_nr;
static void gpu_trace_roots(KW *H,const KParams *P,const char *phase) {
  for(unsigned ri=0;ri<trace_nr;ri++) {
    KW stack[64],depth[64];unsigned sp=1,visits=0;stack[0]=trace_roots[ri];depth[0]=0;
    while(sp) {
      KW v=stack[--sp],d=depth[sp];
      if(KIS_LI(v,0)) continue;
      KW off=v-P->ab;
      if((v&7) || off<8 || off>P->an-16 || d>32 || ++visits>32768 || H[(off>>3)-1]!=(K_BARE|2)) {
        fprintf(stderr,"host phase %s: root %u/%u=%llx bad=%llx depth=%llu visits=%u\n",phase,ri,trace_nr,(unsigned long long)trace_roots[ri],(unsigned long long)v,(unsigned long long)d,visits);return;
      }
      KW ix=off>>3;
      stack[sp]=H[ix];depth[sp++]=d+1;stack[sp]=H[ix+1];depth[sp++]=d+1;
    }
  }
  fprintf(stderr,"host phase %s: %u roots valid\n",phase,trace_nr);
}
static void gpu_trace_save(KW *H,const KParams *P) {
  for(KW l=0;l<P->nlanes;l++) {
    KW v=H[P->lane0+2*P->nlanes+l],off=v-P->ab;
    if(l<4) fprintf(stderr,"host lane %llu pc=%llu rv=%llx hp=%llu he=%llu kq=%llu blocks=%llu spare=%llu\n",(unsigned long long)l,(unsigned long long)H[P->lane0+l],(unsigned long long)v,(unsigned long long)H[P->lane0+4*P->nlanes+l],(unsigned long long)H[P->lane0+5*P->nlanes+l],(unsigned long long)H[P->lane0+7*P->nlanes+l],(unsigned long long)H[P->lane0+22*P->nlanes+l],(unsigned long long)H[P->lane0+23*P->nlanes+l]);
    if(H[P->lane0+l]!=PC_IDLE && !(v&7) && off>=8 && off<P->an && H[(off>>3)-1]==(K_BARE|2) && trace_nr<512) trace_roots[trace_nr++]=v;
  }
  gpu_trace_roots(H,P,"after-kq");
}
"""
  marker='static int gpu_run('
  # Place immediately before gpu_run, after all Metal and runtime declarations.
  pos=host.index(marker)
  host=host[:pos]+helper+'\n'+host[pos:]
  host=host.replace('    rounds++;','    gpu_trace_roots(H,&P,"after-main");\n    rounds++;')
  host=host.replace('      if (gpu_log == 2) {\n        KW n = gpu_lanes', '      gpu_trace_save(H,&P);\n      if (gpu_log == 2) {\n        KW n = gpu_lanes')
  (rt/'gpuhost.h').write_text(host)
 (rt/'gpu.h').write_text(gpu)
 literal='\n'.join(json.dumps(line+'\n') for line in gpu.split('\n'))
 (rt/'gpu_src.h').write_text('static const char K_GPU_H[]=\n'+literal+';\n')
 binary=d/'scan'
 cmd=['cc','-O2','-w','-I',str(rt),'-I',str(out),'tools/gpu-return-trace.c','-o',str(binary),'-lm','-lpthread']
 if sys.platform=='darwin':cmd.insert(1,'-mno-outline')
 else:cmd.append('-ldl')
 subprocess.run(cmd,check=True)
 env=dict(os.environ,BEND_GPU='metal' if sys.platform=='darwin' else 'sim',BEND_GPU_KQCPU=str(kq),BEND_GPU_PIN_MB='0')
 p=subprocess.run([str(binary)],env=env,capture_output=True)
 (d/'stdout').write_bytes(p.stdout);(d/'stderr').write_bytes(p.stderr)
 print('===',name,'host_kq',kq,'exit',p.returncode,'===',flush=True)
 print(p.stderr.decode(errors='replace'),flush=True)
 results.append({'name':name,'host_kq':kq,'exit':p.returncode,'gpu_header_sha256':hashlib.sha256(gpu.encode()).hexdigest()})
 (out/'results.json').write_text(json.dumps(results,indent=2)+'\n')
 if name.startswith('explicit-birth'):
  q=subprocess.run([str(binary)],env=dict(env,BEND_SCAN_SPECIAL='1',BEND_GPU_FORK='0'),capture_output=True)
  (d/'special.stderr').write_bytes(q.stderr);print('=== parent entry forcing depth7 KQ producer exit',q.returncode,'===',flush=True);print(q.stderr.decode(errors='replace'),flush=True)
  ordinary=d/'ordinary';ordinary_cmd=cmd.copy();ordinary_cmd[ordinary_cmd.index('tools/gpu-return-trace.c')]=str(out/'pin_program.c');ordinary_cmd[ordinary_cmd.index(str(binary))]=str(ordinary)
  subprocess.run(ordinary_cmd,check=True)
  q=subprocess.run([str(ordinary)],env=dict(env,BEND_GPU_MB0='4',BEND_GPU_MB='128',BEND_GPU_LANES='64',BEND_GPU_KQCPU='0',BEND_GPU_PIN_MB='0',BEND_GPU_LOG='1'),capture_output=True)
  (d/'ordinary.stderr').write_bytes(q.stderr);(d/'ordinary.stdout').write_bytes(q.stdout)
  print('=== ordinary full fixture exit',q.returncode,'===',flush=True);print(q.stdout.decode(errors='replace'),flush=True);print(q.stderr.decode(errors='replace'),flush=True)
# A control failure is experimental evidence, not a workflow infrastructure failure.
