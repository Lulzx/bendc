#!/usr/bin/env python3
"""Isolated diagnostic controls; no runtime files in the checkout are changed."""
from pathlib import Path
import subprocess,shutil,os,json,sys,hashlib
root=Path(__file__).resolve().parent.parent
os.chdir(root)
base=os.environ.get('BEND_BASE',str(Path.home()/'.bend/bend2/base.bend'))
out=root/'build/gpu-return-trace';out.mkdir(parents=True,exist_ok=True)
with (out/'pin_program.c').open('w') as f:
 subprocess.run(['build/bendc',base,'tests/gpu_growth_pinned.bend'],stdout=f,check=True)
results=[]
for name,kq in [('phase-trace',0)]:
 d=out/name;d.mkdir(exist_ok=True)
 rt=d/'rt';shutil.copytree(root/'rt',rt,dirs_exist_ok=True)
 gpu=(rt/'gpu.h').read_text()
 if name=='phase-trace':
  validator=r"""
KNOINLINE bool k_trace_tree(KTHR KCtx *c,KW root,KU stage) {
  KW vals[64],depths[64],sp=1,steps=0;vals[0]=root;depths[0]=0;
  while(sp) {
    KW v=vals[--sp],depth=depths[sp];
    if(KIS_LI(v,0)) continue;
    bool bad=!k_in(c,v) || (v&7) || depth>=32 || ++steps>131072;
    if(!bad) bad=c->H[KIX(c,v)-1]!=(K_BARE|2);
    if(bad || sp+2>64) {
      KU z=0;
      if(K_CAS(&c->A[7],z,stage)) {
        K_STORE(&c->A[8],(KU)v);K_STORE(&c->A[9],(KU)(v>>32));
        K_STORE(&c->A[10],(KU)root);K_STORE(&c->A[11],(KU)(root>>32));
        K_STORE(&c->A[12],(KU)depth);K_STORE(&c->A[13],(KU)c->lane);
        K_STORE(&c->A[14],(KU)c->hp);K_STORE(&c->A[15],(KU)c->blocks);
      }
      k_fail(c,KE_MATCH);return false;
    }
    KW ix=KIX(c,v);vals[sp]=c->H[ix];depths[sp++]=depth+1;
    vals[sp]=c->H[ix+1];depths[sp++]=depth+1;
  }
  return true;
}
"""
  gpu=gpu.replace('KNOINLINE KW k_tree_compact(',validator+'\nKNOINLINE KW k_tree_compact(')
  gpu=gpu.replace('  if(c->err || !k_tree_new(c,h0,e0,b0,r)) return r;',
    '  if(c->err || !k_trace_tree(c,r,1) || !k_tree_new(c,h0,e0,b0,r)) return r;')
  gpu=gpu.replace('  // A small closed graph fits back',
    '  if(!k_trace_tree(&out,root,2)) {k_fail(c,out.err);return r;}\n  // A small closed graph fits back')
  gpu=gpu.replace('    k_rewind(&out,0,0,b0);c->spare=out.spare;',
    '    if(!k_trace_tree(c,relocated,3)) return relocated;\n    k_rewind(&out,0,0,b0);c->spare=out.spare;')
  gpu=gpu.replace('    return relocated;',
    '    (void)k_trace_tree(c,relocated,4);\n    return relocated;')
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
# A control failure is experimental evidence, not a workflow infrastructure failure.
