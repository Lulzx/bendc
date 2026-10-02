#!/usr/bin/env python3
# Runs binaries at several thread counts, interleaved, and prints the best
# wall time of R runs (and that run's CPU time) per binary and count.
# Usage: bench/scale.py [-r R] [-t 1,2,4,8] name=path ...
# Every binary must print the same last line.
import os, subprocess, sys, time

R, ts, bins = 3, [1, 2, 4, 8], []
a = sys.argv[1:]
while a:
    if a[0] == '-r': R = int(a[1]); a = a[2:]
    elif a[0] == '-t': ts = [int(x) for x in a[1].split(',')]; a = a[2:]
    else: n, p = a[0].split('=', 1); bins.append((n, p)); a = a[1:]

def run(p, t):
    s = time.perf_counter()
    q = subprocess.Popen([p, '--threads', str(t), '--gpu', 'off'], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    o = q.stdout.read().decode().strip().split('\n')[-1]
    _, st, ru = os.wait4(q.pid, 0)
    return time.perf_counter() - s, ru.ru_utime + ru.ru_stime, o

best, outs = {}, set()
for r in range(R):
    for t in ts:
        for n, p in bins:
            w, c, o = run(p, t)
            outs.add(o)
            k = (n, t)
            if k not in best or w < best[k][0]: best[k] = (w, c)
print('| binary | ' + ' | '.join('%d thr' % t for t in ts) + ' |')
print('|---' * (len(ts) + 1) + '|')
for n, p in bins:
    b1 = best[(n, ts[0])][0]
    print('| %s | ' % n + ' | '.join('%.3fs (%.2fx)' % (best[(n, t)][0], b1 / best[(n, t)][0]) for t in ts) + ' |')
print('outputs:', outs)
