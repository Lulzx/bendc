#!/usr/bin/env python3
"""Check masks at real tails, lexical shadows and a direct queued entry."""
import os,re,subprocess,sys
from pathlib import Path
if len(sys.argv)<3:raise SystemExit('usage: check_codegen.py BENDC BASE [FIXTURE]')
f=Path(sys.argv[3]) if len(sys.argv)>3 else Path('tests/gpu_array_masks.bend')
r=subprocess.run([sys.argv[1],sys.argv[2],str(f)],capture_output=True,text=True,timeout=45,env=dict(os.environ,BEND_OPT='i..spfwh'))
if r.returncode:raise SystemExit(r.stderr)
s=r.stdout
cpu='\n'.join(l for l in s.splitlines() if not l.startswith('"'))
checks={
 'four Array descriptors':r'KX_rotate[^\n]*KCtx[^\n]*KW am1, KW am2, KW am3, KW am4',
 'all old masks before self tail':r'KW mi1 = am2; KW mi2 = am3; KW mi3 = am4; KW mi4 = am1; KSET',
 'all masks after pointer updates':r'am1 = mi1; am2 = mi2; am3 = mi3; am4 = mi4; continue;',
 'small helper has no descriptor ABI':r'KX_shadow\(KTHR KCtx \*c, KW a0\)',
 'small queued entry has no descriptor ABI':r'KX_direct__loop\(c, c->kqa\[0\], c->kqa\[1\]\)',
}
for name,pattern in checks.items():
 if not re.search(pattern,cpu):raise SystemExit('missing codegen invariant: '+name)
start=cpu.index('KNOINLINE KU KX_rotate__shadow_x37u(')
end=start+1+re.search(r'\nK(?:INLINE|NOINLINE)',cpu[start+1:]).start()
shadow=cpu[start:end]
if not ('k_aiget(c,' in shadow and 'k_aget(c,' in shadow):raise SystemExit('shadow must clear the old mask after rebinding')
for family in ['KX_rotate_x37u','KX_rotate__word_x37u']:
 if family not in cpu:raise SystemExit('missing native narrow or wide mask permutation')
print('ok')
