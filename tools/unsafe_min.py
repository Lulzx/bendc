#!/usr/bin/env python3
"""Drops the @unsafe markers a file does not need: strips them all, then
re-adds one for each def the checker rejects, until the file checks.
Usage: tools/unsafe_min.py FILE.bend [bendc]   (rewrites FILE.bend)"""
import os, re, subprocess, sys
fn = sys.argv[1]
bendc = sys.argv[2] if len(sys.argv) > 2 else 'build/bendc'
base = os.environ.get('BEND_BASE', os.path.expanduser('~/.bend/bend2/base.bend'))
lines = [l for l in open(fn).read().split('\n')]
had = set()
out = []
for i, l in enumerate(lines):
    if l == '@unsafe':
        j = i + 1
        while not lines[j].startswith('def '): j += 1
        had.add(re.match(r'def ([^\s(:]+)', lines[j]).group(1)); continue
    out.append(l)
keep = set()
tmp = os.path.join(os.path.dirname(os.path.abspath(fn)), '_unsafe_min.bend')
def write(path):
    res = []
    for l in out:
        m = re.match(r'def ([^\s(:]+)', l)
        if m and m.group(1) in keep: res.append('@unsafe')
        res.append(l)
    open(path, 'w').write('\n'.join(res))
while True:
    write(tmp)
    r = subprocess.run([bendc, '--check-only', base, os.path.basename(tmp)], capture_output=True, text=True,
                       cwd=os.path.dirname(tmp))
    txt = r.stdout + r.stderr
    m = re.search(r'^Location: (\S+)', txt, re.M)
    # all proofs hold, or the one error left lists the defs that rely on @unsafe
    if 'SOME PROOFS FAIL' not in txt or re.search(r'^Error: \d+ defs? rel', txt, re.M): break
    if not m: print(txt); sys.exit(1)
    name = m.group(1)
    if name.startswith('_unsafe_min.'): name = name[len('_unsafe_min.'):]
    if name in keep or not any(re.match(r'def ' + re.escape(name) + r'[\s(:]', l) for l in out):
        print('stuck on', name); print(txt[:2000]); sys.exit(1)
    keep.add(name)
    print(len(keep), name, flush=True)
os.remove(tmp)
write(fn)
print('%d @unsafe (was %d); newly unsafe: %s' % (len(keep), len(had), sorted(keep - had)))
