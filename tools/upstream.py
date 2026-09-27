#!/usr/bin/env python3
# Runs the official Bend repository's tests with a bendc: every test that
# imports Base, has a main and expects output (its `#|` lines, not a
# failed check or an error) is compiled, run from the repository's root under a 5 s alarm, and
# its stdout and stderr compared with those lines as the official gate
# (gates/test.ts) compares them: trailing spaces and blank ends trimmed, a
# nonzero exit appended as "exit N" ("timeout" for the alarm). With
# --check, the tests whose check fails (`#|SOME PROOFS FAIL`) go through
# bendc --check-only instead, its answer compared the same way.
#
# Usage: tools/upstream.py BENDC UPSTREAM_CHECKOUT [--js | --check] [-j N] [FILTER..]
# The checkout's bend2/base.bend is the Base; build/upstream/ holds the
# outputs, and build/upstream/fails.txt the failures.
import os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

args = sys.argv[1:]
js = '--js' in args
check = '--check' in args
args = [a for a in args if a not in ('--js', '--check')]
jobs = os.cpu_count() or 4
if '-j' in args:
    i = args.index('-j'); jobs = int(args[i + 1]); del args[i:i + 2]
bendc, up, filters = os.path.abspath(args[0]), os.path.abspath(args[1]), args[2:]
base = os.path.join(up, 'bend2', 'base.bend')
root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
out = os.path.join(root, 'build', 'upstream')
os.makedirs(out, exist_ok=True)
rto = os.path.join(root, 'build', 'bendrt.o')

def tidy(s):
    return re.sub(r'[ \t]+$', '', s, flags=re.M).strip()

def tests():
    ts = []
    tdir = os.path.join(up, 'tests')
    for d in sorted(os.listdir(tdir)):
        if not os.path.isdir(os.path.join(tdir, d)): continue
        for f in sorted(os.listdir(os.path.join(tdir, d))):
            if not f.endswith('.bend'): continue
            src = open(os.path.join(tdir, d, f)).read()
            want = tidy('\n'.join(l[2:] for l in src.split('\n') if l.startswith('#|')))
            effs = re.findall(r'^\s*import "\./[a-z0-9_]+\.(c|js)"$', src, re.M)
            lanes = [l for l in ('c', 'js') if re.search(r'^import Base$', src, re.M)
                     and (not effs or l in effs)]
            if check:
                if not want.startswith('SOME PROOFS FAIL'): continue
            else:
                if not re.search(r'^(def|law) main(\(|:)', src, re.M): continue
                if re.match(r'(SOME PROOFS FAIL|Error:)', want) or not (('js' if js else 'c') in lanes): continue
            name = d + '_' + f[:-5]
            if filters and not any(x in name for x in filters): continue
            ts.append((name, os.path.join('tests', d, f), want))
    return ts

def run(cmd, cwd):
    p = subprocess.run(['perl', '-e', 'alarm 5; exec @ARGV'] + cmd, cwd=cwd,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    got = tidy(p.stdout.decode('utf8', 'replace'))
    if p.returncode != 0:
        code = p.returncode if p.returncode > 0 else 128 - p.returncode
        tail = 'timeout' if code == 142 else 'exit %d' % code
        got = tail if got == '' else got + '\n' + tail
    return got

def one(t):
    name, path, want = t
    if check:
        return name, 'run', want, run([bendc, '--check-only', base, path], up)
    o = os.path.join(out, name)
    ext = '.js' if js else '.c'
    with open(o + ext, 'w') as f, open(o + '.err', 'w') as e:
        r = subprocess.run(['perl', '-e', 'alarm 60; exec @ARGV', bendc] + (['--js'] if js else []) + [base, path], cwd=up,
                           stdout=f, stderr=e)
    if r.returncode != 0:
        return name, 'bendc', want, tidy(open(o + '.err').read())
    if js:
        return name, 'run', want, run(['bun', o + '.js'], up)
    r = subprocess.run([os.environ.get('CC', 'clang'), '-O2', '-w', '-DBEND_RT_SPLIT', '-I', os.path.join(root, 'rt'),
                        o + '.c', rto, '-o', o, '-lm', '-lpthread'] + (['-ldl'] if sys.platform == 'linux' else []),
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    if r.returncode != 0:
        return name, 'clang', want, tidy(r.stdout.decode('utf8', 'replace'))[:2000]
    got = run([o], up)
    return name, 'run', want, got

ts = tests()
fails = []
with ThreadPoolExecutor(jobs) as ex:
    for name, stage, want, got in ex.map(one, ts):
        if stage == 'run' and got == want:
            continue
        fails.append((name, stage, want, got))
        print('FAIL %s (%s)' % (name, stage), flush=True)
with open(os.path.join(out, 'fails.txt'), 'w') as f:
    for name, stage, want, got in fails:
        f.write('=== %s (%s)\n--- want\n%s\n--- got\n%s\n' % (name, stage, want, got))
print('%d passed, %d failed' % (len(ts) - len(fails), len(fails)))
