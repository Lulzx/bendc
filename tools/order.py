#!/usr/bin/env python3
"""Reorders the top-level blocks of a Bend file so every name is defined
before use (Bend requires this). Mutually recursive defs must be tied by a
`law` forward declaration, which then satisfies uses of that name."""
import re, sys, heapq

def blocks(src):
    lines = src.split('\n')
    out, cur, pend = [], None, []   # pend: comments/@unsafe before a block
    head = []
    for ln in lines:
        top = ln[:1] not in ('', ' ', '\t')
        if top and ln.startswith(('def ', 'law ', 'type ')):
            if cur is not None: out.append(cur)
            cur = pend + [ln]; pend = []
        elif top and (ln.startswith('#') or ln.startswith('@')):
            if cur is not None and ln.startswith('@'):
                out.append(cur); cur = None
            if cur is not None and not pend and not cur[-1].strip()=='' and ln.startswith('#'):
                # comment directly after block text: belongs to next block
                out.append(cur); cur = None
            pend.append(ln)
        elif top and cur is None:
            head.extend(pend); pend = []
            head.append(ln)
        elif top:
            cur.append(ln)
        else:
            if cur is None:
                if ln.strip()=='' : (pend.append(ln) if pend else head.append(ln)); continue
                head.append(ln)
            else:
                cur.append(ln)
    if cur is not None: out.append(cur)
    return head + pend, out

ID = re.compile(r'[A-Za-z_][A-Za-z0-9_.]*')
def strip(text):
    text = re.sub(r'"(\\.|[^"\\])*"', '""', text)
    text = re.sub(r"'(\\.|[^'\\])'", "''", text)
    return re.sub(r'#.*', '', text)

def info(b):
    first = next(l for l in b if l.startswith(('def ','law ','type ')))
    kind, rest = first.split(' ', 1)
    name = ID.match(rest).group(0)
    defs = {name}
    if kind == 'type':
        for l in b[1:]:
            m = re.match(r'\s+([A-Za-z_][A-Za-z0-9_.]*)\{', l)
            if m: defs.add(m.group(1))
    uses = set(ID.findall(strip('\n'.join(b))))
    # a do block over M uses M.bind and M.pure
    for m in re.findall(r'\bdo ([A-Za-z_][A-Za-z0-9_.]*)<', '\n'.join(b)):
        uses |= {m + '.bind', m + '.pure'}
    return kind, name, defs, uses

def split_top(s, sep=','):
    parts, depth, cur = [], 0, ''
    for ch in s:
        if ch in '([{<': depth += 1
        if ch in ')]}>': depth -= 1
        if ch == sep and depth == 0: parts.append(cur); cur = ''
        else: cur += ch
    if cur.strip(): parts.append(cur)
    return [x.strip() for x in parts]

def lawify(b):
    """Split `def f(x: A) -> R:` into `law f: for x: A; R` + `def f(x):`."""
    i = next(k for k, l in enumerate(b) if l.startswith('def '))
    # header runs until a line ending with ':' at paren depth 0
    hdr, j, depth = '', i, 0
    while True:
        hdr += ' ' + b[j].strip(); depth += b[j].count('(') - b[j].count(')')
        if depth == 0 and b[j].rstrip().endswith(':'): break
        j += 1
    hdr = hdr.strip()[4:-1]
    name = ID.match(hdr).group(0)
    rest = hdr[len(name):].strip()
    assert rest.startswith('('), hdr
    d, k = 0, 0
    for k, ch in enumerate(rest):
        d += (ch == '(') - (ch == ')')
        if d == 0: break
    params, ret = split_top(rest[1:k]), rest[k+1:].strip()
    assert ret.startswith('->'), 'no return type: ' + name
    ret = ret[2:].strip()
    law = ['law %s:' % name]
    names = []
    for prm in params:
        if ':' in prm:
            n, t = prm.split(':', 1)
            n = n.strip()
            if n.startswith('~'): sys.exit('cannot lawify template ' + name)
            law.append('  for %s: %s' % (n, t.strip()))
            names.append(n.lstrip('+-'))
        else:
            law.append('  for -%s: Quant' % prm); names.append(prm)
    law.append('  ' + ret)
    newdef = b[:i] + ['def %s(%s):' % (name, ', '.join(names))] + b[j+1:]
    return law, newdef

def sccs(n, deps):
    idx, low, on, st, res, c = {}, {}, set(), [], [], [0]
    sys.setrecursionlimit(100000)
    def go(v):
        idx[v] = low[v] = c[0]; c[0] += 1; st.append(v); on.add(v)
        for w in deps[v]:
            if w not in idx: go(w); low[v] = min(low[v], low[w])
            elif w in on: low[v] = min(low[v], idx[w])
        if low[v] == idx[v]:
            comp = []
            while True:
                w = st.pop(); on.discard(w); comp.append(w)
                if w == v: break
            res.append(comp)
    for v in range(n):
        if v not in idx: go(v)
    return res

def compute_deps(inf):
    laws = {i[1]: k for k, i in enumerate(inf) if i[0] == 'law'}
    owner = {}
    for k, (kind, name, defs, _) in enumerate(inf):
        for d in defs:
            if kind == 'def' and d in laws: continue
            owner[d] = k
    deps = []
    for k, (kind, name, defs, uses) in enumerate(inf):
        ds = set()
        for u in uses:
            if u in defs and not (kind == 'def' and u in laws): continue
            if u in laws and laws[u] != k: ds.add(laws[u])
            elif u in owner and owner[u] != k: ds.add(owner[u])
        if kind == 'def' and name in laws: ds.add(laws[name])
        ds.discard(k); deps.append(ds)
    return deps

# Sections of bendc.bend, by name prefix (first match wins).
SECTIONS = [
    ('Utilities', r'^(Str|Doc)(\.|$)'),
    ('Lexer', r'^(Lex(\.|$)|TK$|Tok$|Toks$|Line$)'),
    ('Layout', r'^(Lay\.|LS$|TK\.show|Tok\.show|Toks\.show)'),
    ('IO helpers', r'^IO\.'),
    ('AST', r'^(Pat|Expr|Stmt|Param|Field|Ctor|Decl)$'),
    ('Parser monad', r'^(Parser(\.|$)|P\.(eof_tok|peek|peek2|stuck|skip|err|tok_|is|expect|eat|ident|nls|is_nl|which|tok_which|head|tuple|ptuple|elist|plist)(\.|$))'),
    ('Expressions', r'^(OpInfo$|P\.(ops|op_find|mk_bin|bin|expr|term|list|gt|is_gt|tyargs|after_id|paren|log2|arr|brack|brace|neg|dep|amp|primary|postfix)(\.|$))'),
    ('Patterns', r'^P\.(pats|pat|pat1|pat_seq)(\.|$)'),
    ('Statements', r'^(Fold\.|P\.(scan|skip_line|skip_block|bind|skip_ann|bind_stmt|exprs_n|lets|let_stmt|stmts|cases|is_de|is_in|scrs|match|init|last|do|expect_in|body|stmt)(\.|$))'),
    ('Declarations', r'^P\.'),
    ('AST printing', r'^(Show\.|[A-Z][A-Za-z]*s?\.show(\.|$))'),
    ('Operator resolution', r'^R\.'),
    ('Free variables', r'^(FV\.|Pats?\.vars)'),
    ('Global tables', r'^(CInfo|DInfo|G|Natives)(\.|$)'),
    ('Code generation', r'^(St|Gen|Bind|Env|Tgt|Self|PatR|Split|Sig|Dps|DEdge|DGrp)(\.|$)'),
    ('Value printers', r'^(TB$|Ty\.)'),
    ('Modules', r'^(Mod\.|Qual$)'),
    ('Driver', r'^(Main\.|main$)'),
]
PRINTER_GEN = r'^Gen\.(entry|printer|memo)'

def section_of(name):
    if re.match(PRINTER_GEN, name): return 'Value printers'
    for title, rx in SECTIONS:
        if re.match(rx, name): return title
    return 'Misc'

def section_order(bs, inf, deps):
    titles = [t for t, _ in SECTIONS] + ['Misc']
    by_sec = {t: [] for t in titles}
    for k, i in enumerate(inf):
        by_sec[section_of(i[1])].append(k)
    done, order, onstack = set(), [], set()
    sys.setrecursionlimit(100000)
    def visit(k):
        if k in done: return
        if k in onstack: sys.exit('cycle at ' + inf[k][1])
        onstack.add(k)
        for j in sorted(deps[k]): visit(j)
        onstack.discard(k); done.add(k); order.append(k)
    global HEADERS
    HEADERS = {}
    for t in titles:
        first = len(order)
        for k in by_sec[t]: visit(k)
        if len(order) > first: HEADERS[order[first]] = t
    return order

HEADERS = {}

def strip_headers(lines):
    out, i = [], 0
    while i < len(lines):
        if (i + 1 < len(lines) and lines[i].startswith('# ') and
                re.match(r'^# [=-]{3,}$', lines[i + 1])):
            i += 2
            while i < len(lines) and lines[i].strip() == '': i += 1
            continue
        out.append(lines[i]); i += 1
    return out

def main(path):
    src = open(path).read().rstrip('\n')
    head, bs = blocks(src)
    while True:
        inf = [info(b) for b in bs]
        deps = compute_deps(inf)
        cyc = [c for c in sccs(len(bs), deps) if len(c) > 1]
        if not cyc: break
        for comp in cyc:
            for k in comp:
                if inf[k][0] == 'def' and not any(l.startswith('@unsafe') for l in bs[k]):
                    i = next(j for j, l in enumerate(bs[k]) if l.startswith('def '))
                    bs[k] = bs[k][:i] + ['@unsafe'] + bs[k][i:]
            cand = [k for k in comp if inf[k][0] == 'def']
            k = min(cand, key=lambda k: (len(inf[k][1]), k))
            law, nd = lawify(bs[k])
            print('lawified', inf[k][1], file=sys.stderr)
            bs[k] = nd; bs.append(law)
    order = section_order(bs, inf, deps)
    inf = [info(b) for b in bs]
    lawn = {i[1] for i in inf if i[0] == 'law'}
    filled = set()
    for k in order:
        kind, name, defs, uses = inf[k]
        if kind == 'def':
            early = (uses & lawn) - filled - {name}
            if early and not any(l.startswith('@unsafe') for l in bs[k]):
                i = next(j for j, l in enumerate(bs[k]) if l.startswith('def '))
                bs[k] = bs[k][:i] + ['@unsafe'] + bs[k][i:]
            if name in lawn: filled.add(name)
    parts = ['\n'.join(strip_headers(head)).rstrip('\n')]
    for k in order:
        if k in HEADERS:
            parts.append('# %s\n# %s' % (HEADERS[k], '=' * len(HEADERS[k])))
        parts.append('\n'.join(strip_headers(bs[k])).strip('\n'))
    open(path, 'w').write('\n\n'.join(parts) + '\n')

main(sys.argv[1])
