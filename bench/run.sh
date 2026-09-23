#!/bin/sh
# Benchmarks bendc against the official bend on this machine: each program is
# built by both, their outputs must agree, and the best of 3 runs is shown,
# with each run's peak memory; then building (source to binary) and checking.
# Usage: bench/run.sh [bendc-binary]   (default: build/bendc)
set -e
cd "$(dirname "$0")/.."
BENDC=${1:-build/bendc}
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
export BEND_NO_TELEMETRY=1
mkdir -p build/bench
python3 - "$BENDC" "$BASE" <<'PY'
import os, resource, subprocess, sys, tempfile, time
bendc, base = sys.argv[1], sys.argv[2]

def run(cmd, env=None):
    """Best wall time of 3 runs and the peak memory (MB) of the last."""
    best, rss = 9e9, 0
    for _ in range(3):
        pid_t = time.perf_counter()
        p = subprocess.Popen(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, env=env)
        _, status, ru = os.wait4(p.pid, 0)
        best = min(best, time.perf_counter() - pid_t)
        rss = ru.ru_maxrss / (1 << 20) if sys.platform == 'darwin' else ru.ru_maxrss / 1024
        assert status == 0, cmd
    return best, rss

def out(cmd):
    return subprocess.run(cmd, capture_output=True, text=True).stdout

progs = [('forks', '28'), ('forks_gpu', '28'), ('leaves', '14'), ('leaves_gpu', '14'), ('sort', '1000000')]
print('| program | bendc | official bend | bendc memory | official memory |')
print('|---|---|---|---|---|')
builds = []
for name, n in progs:
    src, me, off = 'bench/%s.bend' % name, 'build/bench/' + name, 'build/bench/%s.off' % name
    tb, _ = run([bendc, '-o', me, base, src])
    to, _ = run(['bend', src, '-o', off])
    builds.append((name, tb, to))
    a, b = out([me, '--', n]), out([off, n])
    assert a == b, (name, a, b)
    (t1, m1), (t2, m2) = run([me, '--', n]), run([off, n])
    print('| `%s %s` | %.2fs | %.2fs | %.0f MB | %.0f MB |' % (name, n, t1, t2, m1, m2))
print()
print('| task | bendc | official bend |')
print('|---|---|---|')
for name, tb, to in builds:
    print('| build `%s.bend` (source to binary) | %.2fs | %.2fs |' % (name, tb, to))
fresh = dict(os.environ, HOME=tempfile.mkdtemp())
(c1, m1), (c2, m2) = run([bendc, '--check-only', base, 'bendc.bend']), run(['bend', 'bendc.bend', '--check-only'], fresh)
print('| type-check `bendc.bend` | %.2fs, %.0f MB | %.2fs, %.0f MB |' % (c1, m1, c2, m2))
PY
