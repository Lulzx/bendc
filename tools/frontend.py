#!/usr/bin/env python3
# Frontend fidelity: every test of the official repository (tests/<ns>/*.bend,
# positive or negative, with or without main) goes through two lanes, each
# comparing bendc's answer with the official one: stdout and stderr as printed
# (trailing spaces trimmed) plus the exit code, identical. Both run from the
# checkout's root on the test's relative path, as the official gate does.
#
#   check  bend F --check-only                       vs  bendc --check-only BASE F
#   parse  bend2/bend.ts book_load (tools/frontend_ref.ts, under bun)
#                                                    vs  bendc --parse-only BASE F
#
# The parse lane loads the file and its imports and stops before validation:
# nothing on success, the CLI's error report (SOME PROOFS FAIL, the error) on
# failure. It tells whether a program is refused while loading or while
# checking, which the check lane alone does not.
#
# The official answers are cached in build/frontend/ref/, keyed by the test's
# hash and the official binary's (check) or bend.ts's (parse), so a rerun
# only runs bendc.
#
# Usage: tools/frontend.py BENDC OFFICIAL_BEND UPSTREAM_CHECKOUT [--lane check|parse] [-j N] [FILTER..]
# Differences go to build/frontend/fails.txt (or $FRONTEND_OUT/fails.txt), with
# both answers under {ref,got}/LANE/ there.
import hashlib, json, os, re, subprocess, sys
from concurrent.futures import ThreadPoolExecutor

args = sys.argv[1:]
jobs = os.cpu_count() or 4
if '-j' in args:
    i = args.index('-j'); jobs = int(args[i + 1]); del args[i:i + 2]
lanes = ['check', 'parse']
if '--lane' in args:
    i = args.index('--lane'); lanes = [args[i + 1]]; del args[i:i + 2]
bendc, official, up = (os.path.abspath(a) for a in args[:3])
filters = args[3:]
base = os.path.join(up, 'bend2', 'base.bend')
root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
out = os.environ.get('FRONTEND_OUT') or os.path.join(root, 'build', 'frontend')
for d in ('ref', 'got'):
    for lane in lanes:
        os.makedirs(os.path.join(out, d, lane), exist_ok=True)

def sha(path):
    return hashlib.sha256(open(path, 'rb').read()).hexdigest()[:16]

oracle = {'check': sha(official), 'parse': sha(os.path.join(up, 'bend2', 'bend.ts'))}

def tests():
    ts, tdir = [], os.path.join(up, 'tests')
    for d in sorted(os.listdir(tdir)):
        if not os.path.isdir(os.path.join(tdir, d)): continue
        for f in sorted(os.listdir(os.path.join(tdir, d))):
            if not f.endswith('.bend'): continue
            name = d + '_' + f[:-5]
            if filters and not any(re.search(x, name) for x in filters): continue
            ts.append((name, os.path.join('tests', d, f)))
    return ts

def tidy(s):
    return re.sub(r'[ \t]+$', '', s, flags=re.M).rstrip()

def run(cmd):
    p = subprocess.run(['perl', '-e', 'alarm 60; exec @ARGV'] + cmd, cwd=up,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    code = 'timeout' if p.returncode in (-14, 142) else 'exit %d' % p.returncode
    return tidy(p.stdout.decode('utf8', 'replace')) + '\n' + code + '\n'

def key(lane, rel):
    return sha(os.path.join(up, rel)) + '-' + oracle[lane]

def cached(lane, name, rel):
    ref = os.path.join(out, 'ref', lane, name + '.txt')
    if os.path.exists(ref):
        k, _, body = open(ref).read().partition('\n')
        if k == key(lane, rel): return body
    return None

def store(lane, name, rel, body):
    open(os.path.join(out, 'ref', lane, name + '.txt'), 'w').write(key(lane, rel) + '\n' + body)
    return body

# The official parser runs in a few long-lived bun processes, each loading
# bend.ts once and a fresh book per file.
def parse_refs(todo):
    names = {rel: name for name, rel in todo}
    chunks = [todo[i::jobs] for i in range(jobs)]
    def batch(ch):
        if not ch: return
        p = subprocess.run(['bun', os.path.join(root, 'tools', 'frontend_ref.ts'), up] + [r for _, r in ch],
                           cwd=up, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        for line in p.stdout.decode('utf8', 'replace').splitlines():
            if line.startswith('{'):
                o = json.loads(line)
                store('parse', names[o['file']], o['file'], o['out'])
    with ThreadPoolExecutor(jobs) as ex:
        list(ex.map(batch, chunks))

def one(lane, t):
    name, rel = t
    ref = cached(lane, name, rel)
    if ref is None and lane == 'check':
        ref = store(lane, name, rel, run([official, rel, '--check-only']))
    if ref is None:
        ref = 'missing official answer\n'
    got = run([bendc, '--' + lane + '-only', base, rel])
    open(os.path.join(out, 'got', lane, name + '.txt'), 'w').write(got)
    return lane + ' ' + name, got == ref

ts = tests()
if 'parse' in lanes:
    parse_refs([t for t in ts if cached('parse', *t) is None])
fails, total = [], 0
for lane in lanes:
    with ThreadPoolExecutor(jobs) as ex:
        res = list(ex.map(lambda t: one(lane, t), ts))
    bad = [n for n, ok in res if not ok]
    fails += bad; total += len(res)
    print('%s: %d/%d identical' % (lane, len(res) - len(bad), len(res)))
open(os.path.join(out, 'fails.txt'), 'w').write(''.join(n + '\n' for n in fails))
print('total: %d/%d identical' % (total - len(fails), total))
for n in fails[:40]:
    print('  ' + n)
sys.exit(1 if fails else 0)
