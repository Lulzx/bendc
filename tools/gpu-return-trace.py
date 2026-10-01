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
for name,kq in [('original',0),('host-kq',1),('no-prefix-pack',0),('no-tree-compaction',0)]:
 d=out/name;d.mkdir(exist_ok=True)
 rt=d/'rt';shutil.copytree(root/'rt',rt,dirs_exist_ok=True)
 gpu=(rt/'gpu.h').read_text()
 if name=='no-prefix-pack':
  old='if(out.blocks!=b0 && out.H[out.blocks]==b0 && out.hp-out.hs<=e0-h0)'
  assert gpu.count(old)==1
  gpu=gpu.replace(old,'if(false && out.blocks!=b0 && out.H[out.blocks]==b0 && out.hp-out.hs<=e0-h0)')
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
