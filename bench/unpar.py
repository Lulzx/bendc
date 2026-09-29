#!/usr/bin/env python3
# Removes a Bend program's parallel annotations: `!` calls become plain
# calls and each parallel let `a b = f(x) g(y)` becomes a let per value, in
# order. What is left runs in parallel only where bendc finds it.
# Usage: bench/unpar.py in.bend out.bend
import re, sys

def split_top(s):
    out, d, cur = [], 0, ''
    for ch in s:
        if ch in '([{': d += 1
        if ch in ')]}': d -= 1
        if ch == ' ' and d == 0:
            if cur: out.append(cur)
            cur = ''
        else:
            cur += ch
    if cur: out.append(cur)
    return out

src = open(sys.argv[1]).read().replace('!(', '(')
res = []
for line in src.split('\n'):
    m = re.match(r'^(\s*)((?:\+?[a-z_][\w.]*\s+)+\+?[a-z_][\w.]*)\s*=\s*(.*)$', line)
    if m and not line.strip().startswith(('def ', '#', 'case ')):
        ind, lhs, rhs = m.groups()
        names, vals = lhs.split(), split_top(rhs)
        if len(names) != len(vals): sys.exit('unpar: cannot split: ' + line)
        res += ['%s%s = %s' % (ind, n, v) for n, v in zip(names, vals)]
    else:
        res.append(line)
open(sys.argv[2], 'w').write('\n'.join(res))
