#!/bin/sh
# Runs the official runtime benchmarks (bench/runtime in the Bend repo) with
# bendc and with the official bend, as upstream's gates/perf.ts runs them:
# `bend main.bend -o main.c` built by `cc -std=c11 -O3` (with Metal for the
# GPU binary), and `bendc -o`; each binary in the three modes, SEQ-CPU
# (--threads 1 --gpu off), PAR-CPU (--threads N --gpu off, N the power of two
# under the core count) and PAR-GPU (--gpu SIZE); the outputs must agree.
# Prints the best of R runs (default 3), runs of the two compilers interleaved.
# With --rc, bendc's reference-counting build (BEND_RC=1) runs too, in its
# own column per mode; the fastest of the row's three is in bold.
# Usage: bench/official.sh [-r R] [-t THREADS] [--rc] [bendc-binary] [bench...]
#   BEND_UP: the Bend repo (default /tmp/bendup32); BEND: the official bend.
set -e
cd "$(dirname "$0")/.."
R=3
NT=
RC=0
while [ $# -gt 0 ]; do
  case "$1" in
    -r) R=$2; shift 2 ;;
    -t) NT=$2; shift 2 ;;
    --rc) RC=1; shift ;;
    *) break ;;
  esac
done
BENDC=${1:-build/bendc}
[ $# -gt 0 ] && shift
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
UP=${BEND_UP:-/tmp/bendup32}
BEND=${BEND:-bend}
export BEND_NO_TELEMETRY=1
python3 - "$BENDC" "$BASE" "$UP" "$BEND" "$R" "$NT" "$RC" "$@" <<'PY'
import os, subprocess, sys, time
bendc, base, up, bend, R, nt, rc = sys.argv[1:8]
R, rc = int(R), rc == '1'
only = sys.argv[8:]
src = os.path.join(up, 'bench', 'runtime')
benches = sorted(b for b in os.listdir(src) if not b.startswith('_') and (not only or b in only))
if not nt:
    nt, cores = 1, os.cpu_count()
    while nt * 2 <= cores: nt *= 2
    nt = str(nt)
# the GPU arena sizes of gates/perf.ts
MEM = {'tree-bitonic': '768MB', 'gameoflife': '512MB', 'kmeans': '768MB', 'mandelbrot': '512MB',
       'merkle': '768MB', 'nbody': '768MB', 'queens': '512MB', 'raytrace': '512MB',
       'symreg': '512MB', 'terrain': '1GB'}
CC = 'cc -std=c11 -O3 main.c -lpthread'
METAL = 'cc -std=c11 -O3 -DBEND_METAL=1 -x objective-c -fobjc-arc main.c -lpthread -framework Metal -framework Foundation'

def sh(cmd, cwd):
    p = subprocess.run(cmd, cwd=cwd, shell=True, capture_output=True, text=True)
    if p.returncode: sys.exit('%s: %s failed\n%s%s' % (cwd, cmd, p.stdout, p.stderr))

def run(cmd, cwd):
    t = time.perf_counter()
    p = subprocess.Popen(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    o = p.stdout.read().decode()
    _, status, ru = os.wait4(p.pid, 0)
    t = time.perf_counter() - t
    if os.waitstatus_to_exitcode(status): o += ' (exit %d)' % os.waitstatus_to_exitcode(status)
    return t, ru.ru_maxrss / (1 << 20), o.strip().split('\n')[-1]

def fmt(c, others):
    t, m = c
    s = '%.3fs %.1fM' % (t, m) if m < 100 else '%.3fs %.0fM' % (t, m)
    return '**%s**' % s if all(t < o[0] for o in others) else s

modes = [['--threads', '1', '--gpu', 'off'], ['--threads', nt, '--gpu', 'off'], None]
cols = [c for m in ('SEQ-CPU', 'PAR-CPU', 'PAR-GPU') for c in [m + ' bendc'] + ([m + ' bendc RC'] if rc else []) + [m + ' bend']]
print('| bench | ' + ' | '.join(cols) + ' | output |')
print('|---' * (len(cols) + 2) + '|')
for b in benches:
    d = os.path.abspath(os.path.join('build', 'official', b))
    os.makedirs(d, exist_ok=True)
    open(os.path.join(d, 'main.bend'), 'w').write(open(os.path.join(src, b, 'main.bend')).read())
    sh('%s main.bend -o main.c && %s -o cpu && %s -o gpu' % (bend, CC, METAL), d)
    sh('%s -o me %s main.bend' % (os.path.abspath(bendc), base), d)
    if rc: sh('BEND_RC=1 %s -o merc %s main.bend' % (os.path.abspath(bendc), base), d)
    row, outs = [b], set()
    for m, flags in enumerate(modes):
        flags = flags or ['--gpu', MEM.get(b, 'on')]
        bins = ['./me'] + (['./merc'] if rc else []) + ['./cpu' if m < 2 else './gpu']
        best = [(9e9, 0)] * len(bins)
        for i in range(R + 1):   # a warm run, then R timed ones
            for k, x in enumerate(bins):
                t, mem, o = run([x] + flags, d)
                outs.add(o)
                if i: best[k] = min(best[k], (t, mem))
        row += [fmt(c, best[:k] + best[k + 1:]) for k, c in enumerate(best)]
    row.append(' '.join(sorted(outs)) if len(outs) == 1 else 'DIFFER: ' + ' / '.join(sorted(outs)))
    print('| ' + ' | '.join(row) + ' |', flush=True)
PY
