import Base

# Utilities
# =========

def Str.eq(+a: String, +b: String) -> Bool:
  String.eq(a, b)

def Str.chr(c: U32) -> String:
  SCon{Chr{c}, SNil{}}

law Str.has:
  for xs: List<&2, String>
  for +x: String
  Bool

@unsafe
def Str.has.if(t: List<&2, String>, +x: String, hit: Bool) -> Bool:
  match hit:
    case True{}:
      True{}
    case False{}:
      Str.has(t, x)

@unsafe
def Str.has(xs, x):
  match xs:
    case Nil{}:
      False{}
    case +h <> t:
      Str.has.if(t, x, String.eq(h, x))

def Str.pad(+s: String, n: Nat) -> String:
  +m = String.length(s)
  s ++ String.repeat(" ", Nat.sub(n, m))

def Str.padl(+s: String, n: Nat) -> String:
  +m = String.length(s)
  String.repeat(" ", Nat.sub(n, m)) ++ s

def Str.last_dot.go(s: String, +i: Nat, +at: Nat) -> Nat:
  match s:
    case SNil{}:
      at
    case SCon{Chr{+c}, t}:
      Str.last_dot.go(t, 1n+i, Bool.pick(Nat, U32.is_eq(c, 46), i, at))

def Str.last_dot(s: String) -> Nat:
  Str.last_dot.go(s, 0n, 999999n)

# The index of the first dot, or the length.
def Str.first_dot(s: String) -> Nat:
  match s:
    case SNil{}:
      0n
    case SCon{Chr{+c}, t}:
      Bool.pick(Nat, U32.is_eq(c, 46), 0n, 1n+Str.first_dot(t))

def Str.has_dot(s: String) -> Bool:
  match s:
    case SNil{}:
      False{}
    case SCon{Chr{+c}, t}:
      Bool.or(U32.is_eq(c, 46), Str.has_dot(t))

def Str.codes(s: String) -> List<&2, U32>:
  match s:
    case SNil{}:
      Nil{}
    case SCon{Chr{c}, t}:
      c <> Str.codes(t)

# Short-circuit and/or: the second operand runs only when needed.
def Lazy.and(a: Bool, f: Unit -> Bool) -> Bool:
  match a:
    case True{}:
      f(Unit{})
    case False{}:
      False{}

def Str.subset(xs: List<&2, String>, +ys: List<&2, String>) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case +h <> t:
      Lazy.and(Str.has(ys, h), u => Str.subset(t, ys))

law Str.index:
  for xs: List<&2, String>
  for +k: String
  for +i: Nat
  Maybe<&2, Nat>

@unsafe
def Str.index.if(t: List<&2, String>, +k: String, +i: Nat, hit: Bool) -> Maybe<&2, Nat>:
  match hit:
    case True{}:
      Some{i}
    case False{}:
      Str.index(t, k, 1n+i)

#
# term_show prints a lowered term as the official does. bnd holds the names
# of the enclosing binders, innermost first; n is their count. Precedences
# are shifted by one (the official -1 is 0 here).
@unsafe
def Str.index(xs, k, i):
  match xs:
    case Nil{}:
      None{}
    case +h <> t:
      Str.index.if(t, k, i, String.eq(h, k))

def Str.count_nl(s: String) -> Nat:
  match s:
    case SNil{}:
      0n
    case SCon{Chr{+c}, t}:
      Nat.add(Bool.pick(Nat, U32.is_eq(c, 10), 1n, 0n), Str.count_nl(t))

def Str.first(+s: String) -> U32:
  match s:
    case SNil{}:
      0
    case SCon{Chr{x}, t}:
      x

def Str.second(+s: String) -> U32:
  match s:
    case SCon{h, SCon{Chr{x}, t}}:
      x
    case other:
      0

def Str.prefix(+s: String, p: String) -> Bool:
  String.starts_with(s, p)

def Str.from_codes(cs: List<&2, U32>) -> String:
  match cs:
    case Nil{}:
      SNil{}
    case c <> t:
      SCon{Chr{c}, Str.from_codes(t)}

law Str.word_at:
  for s: String
  String

@unsafe
def Str.word_at.if(+c: U32, t: String, ok: Bool) -> String:
  match ok:
    case True{}:
      SCon{Chr{c}, Str.word_at(t)}
    case False{}:
      ""

def is_head(+c: U32) -> Bool:
  Bool.or(Bool.or(Bool.and(U32.is_ge(c, 65), U32.is_le(c, 90)), Bool.and(U32.is_ge(c, 97), U32.is_le(c, 122))),
    U32.is_eq(c, 95))

def is_digit(+c: U32) -> Bool:
  Bool.and(U32.is_ge(c, 48), U32.is_le(c, 57))

def is_name(+c: U32) -> Bool:
  Bool.or(Bool.or(is_head(c), is_digit(c)), U32.is_eq(c, 46))

@unsafe
def Str.word_at(s):
  match s:
    case SCon{Chr{+c}, t}:
      Str.word_at.if(c, t, Bool.or(is_name(c), U32.is_eq(c, 46)))
    case SNil{}:
      ""

law Str.words.go:
  for s: String
  for +cur: String
  for acc: List<&2, String>
  List<&2, String>

@unsafe
def Str.words(s: String) -> List<&2, String>:
  Str.words.go(s, "", Nil{})

def Str.words.push(+cur: String, +acc: List<&2, String>) -> List<&2, String>:
  Bool.pick(List<&2, String>, String.is_empty(cur), acc, cur <> acc)

@unsafe
def Str.words.chr(t: String, +c: U32, +cur: String, acc: List<&2, String>, sp: Bool) -> List<&2, String>:
  match sp:
    case True{}:
      Str.words.go(t, "", Str.words.push(cur, acc))
    case False{}:
      Str.words.go(t, cur ++ Str.chr(c), acc)

def is_space(+c: U32) -> Bool:
  Bool.or(Bool.or(U32.is_eq(c, 32), U32.is_eq(c, 10)), Bool.or(U32.is_eq(c, 13), U32.is_eq(c, 9)))

@unsafe
def Str.words.go(s, cur, acc):
  match s:
    case SNil{}:
      List.reverse(&2, String, Str.words.push(cur, acc))
    case SCon{Chr{+c}, t}:
      Str.words.chr(t, c, cur, acc, is_space(c))

def Str.until_hash(ws: List<&2, String>) -> List<&2, String>:
  match ws:
    case Nil{}:
      Nil{}
    case +w <> t:
      Bool.pick(List<&2, String>, String.starts_with(w, "#"), Nil{}, w <> Str.until_hash(t))

def Str.trim(s: String) -> String:
  String.trim(s)

law Str.index_of:
  for s: String
  for +p: String
  for +i: Nat
  Nat

@unsafe
def Str.index_of.if(t: String, +p: String, +i: Nat, hit: Bool) -> Nat:
  match hit:
    case True{}:
      i
    case False{}:
      Str.index_of(t, p, 1n+i)

@unsafe
def Str.index_of(s, p, i):
  match s:
    case SNil{}:
      0n
    case SCon{h, +t}:
      Str.index_of.if(t, p, i, String.starts_with(SCon{h, t}, p))

law Str.unique:
  for xs: List<&2, String>
  for +seen: List<&2, String>
  List<&2, String>

@unsafe
def Str.unique.if(+x: String, t: List<&2, String>, +seen: List<&2, String>, dup: Bool) -> List<&2, String>:
  match dup:
    case True{}:
      Str.unique(t, seen)
    case False{}:
      x <> Str.unique(t, x <> seen)

@unsafe
def Str.unique(xs, seen):
  match xs:
    case Nil{}:
      Nil{}
    case +x <> t:
      Str.unique.if(x, t, seen, Str.has(seen, x))

def Str.filter_in.if(x: String, rest: List<&2, String>, keep: Bool) -> List<&2, String>:
  match keep:
    case True{}:
      x <> rest
    case False{}:
      rest

def Str.filter_in(xs: List<&2, String>, +set: List<&2, String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case +x <> t:
      Str.filter_in.if(x, Str.filter_in(t, set), Str.has(set, x))

# Parser monad
# ============

type Sp is Data:
  NoSp{}
  Sp{src: String, beg: U32, end: U32}

# The Bend type checker, ported from the official bend.ts: the same parser,
# the same core terms, normalizer, quantity and termination checks, and the
# same error reports. JavaScript closures (higher-order binders) become
# closure values (Clo); the book the official checker mutates is threaded
# through a state-and-error monad.
type Q is Data:
  QNone{}
  QLone{}
  QMany{}
  QUnd{}

type LV is Data:
  LNat{n: Nat}
  LStr{s: String}

type Pt is Data:
  PVar{k: String, i: U32, q: Q, s: Sp}
  PCtr{k: String, xs: List<&2, Pt>, s: Sp}

# A term, or one of the values the checker attaches to terms: closures
# (CSyn .. CConst: a binder's body), environment entries (EB, EPat) and
# context entries (CB). Bend has no mutually recursive types, so they share
# this one.
type Tm is Data:
  Var{k: String, i: U32, s: Sp}
  Cel{k: String, s: Sp, v: Tm}
  VPl{k: String, s: Sp}
  VRf{k: String, i: U32, s: Sp, r: Tm}
  Ref{k: String, s: Sp, b: Bool}
  Sub{i: U32, p: Pt, f: Tm, s: Sp}
  Let{ks: List<&2, String>, ids: List<&2, U32>, vs: List<&2, Tm>, f: Tm, s: Sp, qs: List<&2, Q>}
  Typ{g: Tm, s: Sp}
  Qnt{s: Sp}
  TQua{q: Q, s: Sp}
  Min{a: Tm, b: Tm, s: Sp}
  All{q: Q, k: String, i: U32, a: Tm, b: Tm, s: Sp}
  Lam{k: String, i: U32, f: Tm, s: Sp, q: Q}
  TApp{f: Tm, x: Tm, s: Sp}
  ADT{k: String, xs: List<&2, Tm>, s: Sp, r: List<&2, String>}
  Ctr{k: String, xs: List<&2, Tm>, s: Sp}
  Lit{v: LV, s: Sp}
  Mat{k: String, h: Tm, m: Tm, s: Sp}
  Efq{s: Sp}
  Eql{a: Tm, b: Tm, t: Tm, s: Sp}
  Rfl{s: Sp}
  Rwt{e: Tm, p: Tm, f: Tm, s: Sp}
  Hol{k: String, s: Sp}
  Ann{x: Tm, t: Tm, s: Sp}
  CSyn{env: List<&2, Tm>, i: U32, b: Tm}
  CLet{env: List<&2, Tm>, ids: List<&2, U32>, b: Tm}
  CSnf{c: Tm}
  CExt{lhs: Tm, k: String, n: Nat, xs: List<&2, Tm>}
  CGoal{cur: Tm, n: Nat, xs: List<&2, Tm>, tb: Tm, ck: String, cs: Sp, tq: Q, ctx: List<&2, Tm>, dn: String}
  CRwt{a: Tm, t: Tm, s: Sp}
  CConst{t: Tm}
  EB{i: U32, v: Tm}
  EPat{p: Pt, env: List<&2, Tm>}
  CB{i: U32, q: Q, k: String, t: Tm}

type CtrD is Data:
  CtrD{k: String, n: Nat, t: Tm}

# A def (a law has no value) or a datatype.
type Tld is Data:
  TDef{n: Nat, x: Nat, t: Tm, v: Maybe<&2, Tm>, u: Bool, b: Bool, imps: Maybe<&2, List<&2, String>>}
  TADT{n: Nat, g: Nat, t: Tm, cs: List<&2, CtrD>, b: Bool}

type Book is Data:
  Book{tlds: Map<&2, Tld>, ctrs: Map<&2, CtrD>, order: List<&2, String>, hols: Nat, open: Nat,
    tmps: Map<&2, String>, tcnt: Map<&2, Nat>}

type Msg is Data:
  MNone{}
  MStr{s: String}
  MTm{t: Tm}

type Err is Data:
  Err{bok: Book, ctx: List<&2, Tm>, exp: Msg, obs: Msg, spn: Sp, dn: String, nte: String}

#
# The official parser works on characters: a cursor (the rest of the text,
# its position and column, whether a newline came since the last visible
# character, and the character before), a scope of binder names, and the
# book being built.
type SB is Data:
  SB{k: String, i: U32}

type Cur is Data:
  Cur{rest: String, pos: U32, col: U32, nl: Bool, prev: U32}

type SB2 is Data:
  SB2{k: String, v: String}

type PS is Data:
  PS{cur: Cur, stk: List<&2, SB>, stn: Nat, frs: U32, book: Book, src: String, ns: String, dir: String,
    al: List<&2, SB2>}

def P(-A: Type) -> Type:
  PS -> Result<&1, &1, Err, A & PS>

def Cur.peek(+c: Cur) -> U32:
  Cur{rest, pos, col, nl, prev} = c
  Str.first(rest)

def PS.cur(+ps: PS) -> Cur:
  PS{+cur, stk, stn, frs, book, src, ns, dir, al} = ps
  cur

def P.peek() -> P(U32):
  +ps => Done{(Cur.peek(PS.cur(ps)), ps)}

def PS.set_cur(ps: PS, c: Cur) -> PS:
  PS{cur, stk, stn, frs, book, src, ns, dir, al} = ps
  PS{c, stk, stn, frs, book, src, ns, dir, al}

law Cur.skip:
  for +c: Cur
  Cur

@unsafe
def P.skip() -> P(Unit):
  +ps => Done{(Unit{}, PS.set_cur(ps, Cur.skip(PS.cur(ps))))}

def P.pure(-A: Type, x: A) -> P(A):
  ps => Done{(x, ps)}

def book_nil() -> Book:
  Book{MTip{}, MTip{}, Nil{}, 0n, 0n, MTip{}, MTip{}}

def err0(exp: String, obs: Msg, spn: Sp) -> Err:
  Err{book_nil(), Nil{}, MStr{exp}, obs, spn, "", ""}

def P.go.done(-A: Type, -B: Type, v: A & PS, f: A -> P(B)) -> Result<&1, &1, Err, B & PS>:
  (a, ps) = v
  f(a, ps)

def P.go(-A: Type, -B: Type, r: Result<&1, &1, Err, A & PS>, f: A -> P(B)) ->
  Result<&1, &1, Err, B & PS>:
  match r:
    case Fail{e}:
      Fail{e}
    case Done{v}:
      P.go.done(A, B, v, f)

def P.throw(-A: Type, e: Err) -> P(A):
  ps => Fail{e}

def Cur.pos(+c: Cur) -> U32:
  Cur{rest, +pos, col, nl, prev} = c
  pos

def PS.src(+ps: PS) -> String:
  PS{cur, stk, stn, frs, book, +src, ns, dir, al} = ps
  src

def P.fail.go(exp: String, +ps: PS) -> Result<&1, &1, Err, Unit & PS>:
  +c = Cur.peek(PS.cur(ps))
  +pos = Cur.pos(PS.cur(ps))
  Fail{err0(exp, MStr{Bool.pick(String, U32.is_zero(c), "end of input", "'" ++ Str.chr(c) ++ "'")},
    Sp{PS.src(ps), pos, pos})}

def P.fail(-A: Type, exp: String) -> P(A):
  ps => P.go(Unit, A, P.fail.go(exp, ps), u => P.throw(A, err0("", MNone{}, NoSp{})))

def P.eat.if(+s: String, ok: Bool) -> P(Unit):
  match ok:
    case True{}:
      P.pure(Unit, Unit{})
    case False{}:
      P.fail(Unit, "'" ++ s ++ "'")

def P.bind(-A: Type, -B: Type, m: P(A), f: A -> P(B)) -> P(B):
  ps => P.go(A, B, m(ps), f)

def Cur.rest(+c: Cur) -> String:
  Cur{+rest, pos, col, nl, prev} = c
  rest

def P.at(s: String) -> P(Bool):
  +ps => Done{(Str.prefix(Cur.rest(PS.cur(ps)), s), ps)}

def Cur.step.go(rest: String, +pos: U32, +col: U32, nl: Bool) -> Cur:
  match rest:
    case SNil{}:
      Cur{SNil{}, pos, col, nl, 0}
    case SCon{Chr{+x}, t}:
      Cur{t, U32.inc(pos), Bool.pick(U32, U32.is_eq(x, 10), 1, U32.inc(col)),
        Bool.pick(Bool, U32.is_eq(x, 10), True{},
          Bool.pick(Bool, Bool.or(U32.is_eq(x, 32), Bool.or(U32.is_eq(x, 13), U32.is_eq(x, 9))), nl,
            False{})), x}

# Moves over one character.
def Cur.step(c: Cur) -> Cur:
  Cur{rest, +pos, +col, nl, prev} = c
  Cur.step.go(rest, pos, col, nl)

@unsafe
def Cur.steps(c: Cur, n: Nat) -> Cur:
  match n:
    case 0n:
      c
    case 1n+m:
      Cur.steps(Cur.step(c), m)

def P.take.if(+s: String, ok: Bool) -> P(Bool):
  match ok:
    case True{}:
      +ps => Done{(True{}, PS.set_cur(ps, Cur.steps(PS.cur(ps), String.length(s))))}
    case False{}:
      P.pure(Bool, False{})

def P.take(+s: String) -> P(Bool):
  do P<Bool>:
    ok : Bool <- P.at(s)
    P.take.if(s, ok)

def P.eat(+s: String) -> P(Unit):
  do P<Unit>:
    P.skip()
    ok : Bool <- P.take(s)
    P.eat.if(s, ok)

# Expressions
# ===========

law P.term:
  for +lvl: U32
  P(Tm)

def P.brace.rfl() -> P(Tm):
  do P<Tm>:
    P.eat("}")
    return Rfl{NoSp{}}

def P.pos() -> P(U32):
  +ps => Done{(Cur.pos(PS.cur(ps)), ps)}

def P.span(+beg: U32) -> P(Sp):
  +ps => Done{(Sp{PS.src(ps), beg, Cur.pos(PS.cur(ps))}, ps)}

@unsafe
def P.term0() -> P(Tm):
  P.term(0)

def PS.push(ps: PS, b: SB) -> PS:
  PS{cur, stk, stn, frs, book, src, ns, dir, al} = ps
  PS{cur, b <> stk, 1n+stn, frs, book, src, ns, dir, al}

def PS.opened(ps: PS, +k: String, +i: U32, keep: Bool) -> PS:
  match keep:
    case True{}:
      PS.push(ps, SB{k, i})
    case False{}:
      ps

def P.open.go(+k: String, ps: PS) -> Result<&1, &1, Err, U32 & PS>:
  PS{cur, stk, stn, +frs, book, src, ns, dir, al} = ps
  Done{(frs, PS.opened(PS{cur, stk, stn, U32.inc(frs), book, src, ns, dir, al}, k, frs,
    Bool.not(String.eq(k, "_"))))}

# A fresh binder id; k (unless "_") now names it.
def P.open(+k: String) -> P(U32):
  ps => P.open.go(k, ps)

@unsafe
def P.brace.go(+beg: U32, +a: Tm, eq: Bool, ne: Bool) -> P(Tm):
  match eq ne:
    case True{} x:
      do P<Tm>:
        b : Tm <- P.term0()
        P.eat(":")
        ty : Tm <- P.term0()
        P.eat("}")
        return Eql{a, b, ty, NoSp{}}
    case False{} True{}:
      do P<Tm>:
        +pos : U32 <- P.pos()
        ns : Sp <- P.span((pos - 2 : U32))
        b : Tm <- P.term0()
        P.eat(":")
        ty : Tm <- P.term0()
        P.eat("}")
        +s : Sp <- P.span(beg)
        +i : U32 <- P.open("_")
        return All{QLone{}, "_", i, Eql{a, b, ty, s}, CSyn{Nil{}, i, Ref{"Empty", ns, False{}}}, s}
    case False{} False{}:
      do P<Tm>:
        P.eat(":")
        ty : Tm <- P.term0()
        P.eat("}")
        return Ann{a, ty, NoSp{}}

# Branching in the parser monad: both actions are built, one runs.
def P.if(-A: Type, c: Bool, t: P(A), e: P(A)) -> P(A):
  match c:
    case True{}:
      t
    case False{}:
      e

@unsafe
def P.brace.term(+beg: U32) -> P(Tm):
  do P<Tm>:
    +a : Tm <- P.term0()
    P.skip()
    +eq : Bool <- P.take("==")
    ne : Bool <- P.if(Bool, eq, P.pure(Bool, False{}), P.take("!="))
    P.brace.go(beg, a, eq, ne)

def P.bump() -> P(Unit):
  +ps => Done{(Unit{}, PS.set_cur(ps, Cur.step(PS.cur(ps))))}

# {==}  {a == b : T}  {a != b : T}  {x : T}
@unsafe
def P.brace(+beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    P.skip()
    rfl : Bool <- P.take("==")
    P.if(Tm, rfl, P.brace.rfl(), P.brace.term(beg))

law P.args:
  for +close: String
  P(List<&2, Tm>)

def list.build(xs: List<&2, Tm>, +s: Sp) -> Tm:
  match xs:
    case Nil{}:
      Ctr{"Nil", Nil{}, s}
    case x <> t:
      Ctr{"Con", [x, list.build(t, s)], s}

@unsafe
def P.brack.list(+beg: U32, xs: List<&2, Tm>) -> P(Tm):
  do P<Tm>:
    comma : Bool <- P.take(",")
    ys : List<&2, Tm> <- P.args("]")
    +spn : Sp <- P.span(beg)
    return list.build(List.append(&2, Tm, xs, ys), spn)

def P.brack.log2.go(+s: Sp, n: Nat, m: Maybe<&2, Nat>) -> P(Tm):
  match m:
    case None{}:
      P.throw(Tm, err0("a power of two count (^d takes a depth)", MNone{}, s))
    case Some{k}:
      P.pure(Tm, Lit{LNat{k}, s})

law Nat.log2_exact.go:
  for +n: Nat
  for +k: Nat
  for +p: Nat
  Maybe<&2, Nat>

# log2(n) when n is a power of two.
@unsafe
def Nat.log2_exact(+n: Nat) -> Maybe<&2, Nat>:
  Nat.log2_exact.go(n, 0n, 1n)

def P.brack.log2(+s: Sp, m: Maybe<&2, Nat>) -> P(Tm):
  match m:
    case None{}:
      P.throw(Tm, err0("a power of two count (^d takes a depth)", MNone{}, s))
    case Some{+n}:
      P.brack.log2.go(s, n, Nat.log2_exact(n))

def Tm.span(t: Tm) -> Sp:
  match t:
    case Var{k, i, s}:
      s
    case Cel{k, s, v}:
      s
    case VPl{k, s}:
      s
    case VRf{k, i, s, r}:
      s
    case Ref{k, s, b}:
      s
    case Sub{i, p, f, s}:
      s
    case Let{ks, ids, vs, f, s, qs}:
      s
    case Typ{g, s}:
      s
    case Qnt{s}:
      s
    case TQua{q, s}:
      s
    case Min{a, b, s}:
      s
    case All{q, k, i, a, b, s}:
      s
    case Lam{k, i, f, s, q}:
      s
    case TApp{f, x, s}:
      s
    case ADT{k, xs, s, r}:
      s
    case Ctr{k, xs, s}:
      s
    case Lit{v, s}:
      s
    case Mat{k, h, m, s}:
      s
    case Efq{s}:
      s
    case Eql{a, b, ty, s}:
      s
    case Rfl{s}:
      s
    case Rwt{e, p, f, s}:
      s
    case Hol{k, s}:
      s
    case Ann{x, ty, s}:
      s
    case other:
      NoSp{}

def Maybe.map_nat(m: Maybe<&2, Nat>) -> Maybe<&2, Nat>:
  match m:
    case None{}:
      None{}
    case Some{+n}:
      Bool.pick(Maybe<&2, Nat>, Nat.is_le(1n+n, 4294967295n), Some{1n+n}, None{})

# The count of a Succ chain ending at Zero or a Nat literal, if it is one.
def nat_from_term(t: Tm) -> Maybe<&2, Nat>:
  match t:
    case Ctr{"Succ", x <> Nil{}, s}:
      Maybe.map_nat(nat_from_term(x))
    case Ctr{"Zero", Nil{}, s}:
      Some{0n}
    case Lit{LNat{n}, s}:
      Some{n}
    case other:
      None{}

# A count must be a power of two; it becomes the depth.
def P.brack.depth(cnt: Bool, +n: Tm) -> P(Tm):
  match cnt:
    case True{}:
      P.brack.log2(Tm.span(n), nat_from_term(n))
    case False{}:
      P.pure(Tm, n)

law P.ns:
  for tm: Tm
  for ty: Tm
  P(Tm)

@unsafe
def P.brack.arr(+beg: U32, x: Tm) -> P(Tm):
  do P<Tm>:
    +ty : Tm <- P.term(12)
    P.skip()
    +cnt : Bool <- P.take("*")
    P.if(Unit, cnt, P.pure(Unit, Unit{}), P.eat("^"))
    n : Tm <- P.term0()
    P.eat("]")
    +s : Sp <- P.span(beg)
    x2 : Tm <- P.ns(x, ty)
    d : Tm <- P.brack.depth(cnt, n)
    return TApp{TApp{TApp{Ref{"Array.new", s, False{}}, ty, s}, d, s}, x2, s}

@unsafe
def P.brack.first(+beg: U32) -> P(Tm):
  do P<Tm>:
    +x : Tm <- P.term0()
    P.skip()
    arr : Bool <- P.take(":")
    P.if(Tm, arr, P.brack.arr(beg, x), P.brack.list(beg, [x]))

# [a, b]  [v : T*n]  [v : T^d]
@unsafe
def P.brack(+beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    P.skip()
    empty : Bool <- P.at("]")
    P.if(Tm, empty, P.brack.list(beg, Nil{}), P.brack.first(beg))

law P.amp:
  for +d: U32
  for +beg: U32
  P(Tm)

law P.ops:
  for out: Tm
  for +lvl: U32
  P(Tm)

# The term with span s (when it has none).
def Tm.respan(t: Tm, s: Sp) -> Tm:
  match t:
    case Var{k, i, NoSp{}}:
      Var{k, i, s}
    case Ref{k, NoSp{}, b}:
      Ref{k, s, b}
    case Typ{g, NoSp{}}:
      Typ{g, s}
    case Qnt{NoSp{}}:
      Qnt{s}
    case TQua{q, NoSp{}}:
      TQua{q, s}
    case TApp{f, x, NoSp{}}:
      TApp{f, x, s}
    case ADT{k, xs, NoSp{}, r}:
      ADT{k, xs, s, r}
    case Ctr{k, xs, NoSp{}}:
      Ctr{k, xs, s}
    case Lit{v, NoSp{}}:
      Lit{v, s}
    case Rfl{NoSp{}}:
      Rfl{s}
    case Hol{k, NoSp{}}:
      Hol{k, s}
    case other:
      other

def Tm.spanned(t: Tm, s: Sp) -> Tm:
  match t:
    case Let{ks, ids, vs, f, NoSp{}, qs}:
      Let{ks, ids, vs, f, s, qs}
    case Min{a, b, NoSp{}}:
      Min{a, b, s}
    case All{q, k, i, a, b, NoSp{}}:
      All{q, k, i, a, b, s}
    case Lam{k, i, f, NoSp{}, q}:
      Lam{k, i, f, s, q}
    case Mat{k, h, m, NoSp{}}:
      Mat{k, h, m, s}
    case Efq{NoSp{}}:
      Efq{s}
    case Eql{a, b, ty, NoSp{}}:
      Eql{a, b, ty, s}
    case Rwt{e, p, f, NoSp{}}:
      Rwt{e, p, f, s}
    case Ann{x, ty, NoSp{}}:
      Ann{x, ty, s}
    case VPl{k, NoSp{}}:
      VPl{k, s}
    case VRf{k, i, NoSp{}, r}:
      VRf{k, i, s, r}
    case Sub{i, p, f, NoSp{}}:
      Sub{i, p, f, s}
    case other:
      Tm.respan(other, s)

def P.cur() -> P(Cur):
  +ps => Done{(PS.cur(ps), ps)}

def P.set_cur(c: Cur) -> P(Unit):
  ps => Done{(Unit{}, PS.set_cur(ps, c))}

def P.lexeme.dot.c(+k: String, c: Bool) -> P(String):
  match c:
    case True{}:
      P.fail(String, "a name (a name cannot end in '.')")
    case False{}:
      P.pure(String, k)

def P.lexeme.dot(+k: String) -> P(String):
  P.lexeme.dot.c(k, String.ends_with(k, "."))

def P.lexeme.fin(r: String & Cur) -> P(String):
  (k, c) = r
  do P<String>:
    P.set_cur(c)
    P.lexeme.dot(k)

law Cur.name:
  for +c: Cur
  for acc: String
  String & Cur

@unsafe
def P.lexeme.go(+c: Cur) -> P(String):
  P.lexeme.fin(Cur.name(c, ""))

def P.lexeme.if(+c: Cur, ok: Bool) -> P(String):
  match ok:
    case True{}:
      P.lexeme.go(c)
    case False{}:
      P.fail(String, "a name")

def P.lexeme() -> P(String):
  do P<String>:
    P.skip()
    +c : Cur <- P.cur()
    P.lexeme.if(c, is_head(Cur.peek(c)))

def KEYWORDS() -> List<&2, String>:
  ["def", "type", "law", "match", "case", "do", "return", "for", "exs", "where", "is", "import",
   "Type", "Data", "Kind", "Quant"]

def PS.stk(+ps: PS) -> List<&2, SB>:
  PS{cur, +stk, stn, frs, book, src, ns, dir, al} = ps
  stk

law SB.find:
  for xs: List<&2, SB>
  for +k: String
  Maybe<&2, U32>

@unsafe
def P.lookup(+k: String) -> P(Maybe<&2, U32>):
  +ps => Done{(SB.find(PS.stk(ps), k), ps)}

law Map.find.go:
  for -V: Data
  for m: Map<&2, V>
  for +k: String
  Maybe<&2, V>

@unsafe
def Map.find(-V: Data, +m: Map<&2, V>, +k: String) -> Maybe<&2, V>:
  Map.find.go(V, m, k)

def book_ctr(+book: Book, +k: String) -> Maybe<&2, CtrD>:
  Book{tlds, +ctrs, order, hols, open, tmps, tcnt} = book
  Map.find(CtrD, ctrs, k)

def book_tld(+book: Book, +k: String) -> Maybe<&2, Tld>:
  Book{+tlds, ctrs, order, hols, open, tmps, tcnt} = book
  Map.find(Tld, tlds, k)

def book_has(+book: Book, +k: String) -> Bool:
  Maybe.is_some(&2, Tld, book_tld(book, k))

def PS.book(+ps: PS) -> Book:
  PS{cur, stk, stn, frs, +book, src, ns, dir, al} = ps
  book

def PS.al(+ps: PS) -> List<&2, SB2>:
  PS{cur, stk, stn, frs, book, src, ns, dir, +al} = ps
  al

def PS.ns(+ps: PS) -> String:
  PS{cur, stk, stn, frs, book, src, +ns, dir, al} = ps
  ns

def PS.qual(+ps: PS, +k: String) -> String:
  Bool.pick(String, String.is_empty(PS.ns(ps)), k, PS.ns(ps) ++ "." ++ k)

def PS.reso.alias(q: String, m: Maybe<&2, String>, rest: String, dot: Bool) -> String:
  match m dot:
    case Some{a} True{}:
      a ++ rest
    case x d:
      q

law SB2.find:
  for xs: List<&2, SB2>
  for +k: String
  Maybe<&2, String>

# The name k resolves to: qualified by the namespace (or an alias) when
# such a name exists, else k itself.
@unsafe
def PS.reso(+ps: PS, +k: String) -> String:
  +dot = Str.first_dot(k)
  +q = PS.reso.alias(PS.qual(ps, k), SB2.find(PS.al(ps), String.take(k, dot)), String.drop(k, dot),
    Nat.is_lt(dot, String.length(k)))
  Bool.pick(String, Bool.or(book_has(PS.book(ps), q), Maybe.is_some(&2, CtrD, book_ctr(PS.book(ps), q))),
    q, k)

def P.reso(+k: String) -> P(String):
  +ps => Done{(PS.reso(ps, k), ps)}

def P.fresh_id.go(ps: PS) -> Result<&1, &1, Err, U32 & PS>:
  PS{cur, stk, stn, +frs, book, src, ns, dir, al} = ps
  Done{(frs, PS{cur, stk, stn, U32.inc(frs), book, src, ns, dir, al})}

def P.fresh_id() -> P(U32):
  ps => P.fresh_id.go(ps)

def P.var.free(+k: String, +q: String, +s: Sp, dot: Bool) -> P(Tm):
  match dot:
    case True{}:
      P.pure(Tm, Ref{q, s, False{}})
    case False{}:
      do P<Tm>:
        i : U32 <- P.fresh_id()
        return VRf{k, i, s, Ref{q, s, False{}}}

def P.var.found(+k: String, m: Maybe<&2, U32>, +s: Sp) -> P(Tm):
  match m:
    case Some{i}:
      P.pure(Tm, Var{k, i, s})
    case None{}:
      do P<Tm>:
        +q : String <- P.reso(k)
        P.var.free(k, q, s, Str.has_dot(k))

def P.var(+k: String, +s: Sp) -> P(Tm):
  do P<Tm>:
    m : Maybe<&2, U32> <- P.lookup(k)
    P.var.found(k, m, s)

def P.base.var(+k: String, +beg: U32) -> P(Tm):
  do P<Tm>:
    s : Sp <- P.span(beg)
    P.var(k, s)

@unsafe
def P.base.ctor(+k: String, +beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    xs : List<&2, Tm> <- P.args("}")
    q : String <- P.reso(k)
    s : Sp <- P.span(beg)
    return Ctr{q, xs, s}

@unsafe
def P.base.name(+k: String, +beg: U32) -> P(Tm):
  do P<Tm>:
    brace : Bool <- P.at("{")
    P.if(Tm, brace, P.base.ctor(k, beg), P.base.var(k, beg))

law P.do:
  for +beg: U32
  P(Tm)

@unsafe
def P.base.word.go(+k: String, +beg: U32, m: Maybe<&2, Nat>) -> P(Tm):
  match m:
    case Some{0n}:
      do P<Tm>:
        +s : Sp <- P.span(beg)
        return Typ{TQua{QLone{}, s}, s}
    case Some{1n}:
      do P<Tm>:
        +s : Sp <- P.span(beg)
        return Typ{TQua{QMany{}, s}, s}
    case Some{2n}:
      do P<Tm>:
        s : Sp <- P.span(beg)
        return Qnt{s}
    case Some{3n}:
      do P<Tm>:
        P.eat("(")
        g : Tm <- P.term0()
        P.eat(")")
        s : Sp <- P.span(beg)
        return Typ{g, s}
    case Some{4n}:
      P.do(beg)
    case Some{5n}:
      P.fail(Tm, "a term (a match heads a def body, not a term)")
    case Some{6n}:
      P.fail(Tm, "a match heading this case (this case is orphaned)")
    case Some{7n}:
      P.fail(Tm, "a do-block heading this return")
    case other:
      P.if(Tm, Str.has(KEYWORDS(), k), P.fail(Tm, "a term (the keyword '" ++ k ++ "' cannot head one)"),
        P.base.name(k, beg))

@unsafe
def P.base.word(+k: String, +beg: U32) -> P(Tm):
  P.base.word.go(k, beg, Str.index(["Type", "Data", "Quant", "Kind", "do", "match", "case", "return"],
    k, 0n))

def P.peek_rest() -> P(String):
  +ps => Done{(Cur.rest(PS.cur(ps)), ps)}

def P.book() -> P(Book):
  +ps => Done{(PS.book(ps), ps)}

def Tld.adt_ng(t: Maybe<&2, Tld>) -> Maybe<&1, Nat & Nat>:
  match t:
    case Some{TADT{n, g, ty, cs, tbase}}:
      Some{(n, g)}
    case other:
      None{}

def Tm.name(t: Tm) -> String:
  match t:
    case Var{k, i, s}:
      k
    case VRf{k, i, s, r}:
      k
    case VPl{k, s}:
      k
    case Ref{k, s, b}:
      k
    case ADT{k, xs, s, r}:
      k
    case Ctr{k, xs, s}:
      k
    case other:
      ""

def Tm.is_var(t: Tm) -> Bool:
  match t:
    case Var{k, i, s}:
      True{}
    case VRf{k, i, s, r}:
      True{}
    case VPl{k, s}:
      True{}
    case other:
      False{}

def Tm.is_ref(t: Tm) -> Bool:
  match t:
    case Ref{k, s, b}:
      True{}
    case other:
      False{}

def P.plus.key(+t: Tm) -> P(String):
  match t:
    case ADT{k, xs, s, r}:
      P.pure(String, k)
    case other:
      P.if(String, Bool.or(Tm.is_var(other), Tm.is_ref(other)), P.reso(Tm.name(other)), P.pure(String, ""))

def Tm.is_adt(t: Tm) -> Bool:
  match t:
    case ADT{k, xs, s, r}:
      True{}
    case other:
      False{}

def plus.args(xs: List<&2, Tm>, g: Nat) -> List<&2, Tm>:
  match xs g:
    case x <> t 1n+h:
      TQua{QMany{}, Tm.span(x)} <> plus.args(t, h)
    case ys k:
      ys

def List.repeat_tm(+x: Tm, n: Nat) -> List<&2, Tm>:
  match n:
    case 0n:
      Nil{}
    case 1n+m:
      x <> List.repeat_tm(x, m)

def P.plus.xs(t: Tm, n: Nat, +s: Sp) -> List<&2, Tm>:
  match t:
    case ADT{k, xs, as, r}:
      xs
    case other:
      List.repeat_tm(TQua{QLone{}, s}, n)

def P.plus.adt(+t: Tm, +k: String, +s: Sp, v: Nat & Nat) -> P(Tm):
  (n, g) = v
  +gg = g
  +nn = n
  P.if(Tm, Bool.or(Nat.is_eq(gg, 0n), Bool.and(Nat.is_lt(gg, nn), Bool.not(Tm.is_adt(t)))),
    P.fail(Tm, "a quantified datatype after + (+D<..> sets D's leading quantities to &2)"),
    P.pure(Tm, ADT{k, plus.args(P.plus.xs(t, nn, s), gg), s, Nil{}}))

def P.plus.go(+t: Tm, +k: String, +s: Sp, ng: Maybe<&1, Nat & Nat>) -> P(Tm):
  match ng:
    case None{}:
      P.if(Tm, Tm.is_var(t), P.pure(Tm, VPl{Tm.name(t), s}),
        P.fail(Tm, "a quantified datatype after + (+D<..> sets D's leading quantities to &2)"))
    case Some{v}:
      P.plus.adt(t, k, s, v)

@unsafe
def P.plus(+beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    +t : Tm <- P.term(12)
    +s : Sp <- P.span(beg)
    +k : String <- P.plus.key(t)
    b : Book <- P.book()
    P.plus.go(t, k, s, Tld.adt_ng(book_tld(b, k)))

# \{K: h; ...; tail}: a match written out, arm by arm.
def arms.build(arms: List<&2, Tm>, tail: Tm, +s: Sp) -> Tm:
  match arms:
    case Nil{}:
      tail
    case Ctr{k, h <> Nil{}, as} <> t:
      Mat{k, h, arms.build(t, tail, s), s}
    case x <> t:
      arms.build(t, tail, s)

def P.arms.fin(r: List<&2, Tm> & Tm, +s: Sp) -> Tm:
  (arms, tail) = r
  arms.build(arms, Tm.spanned(tail, s), s)

law P.arms.go:
  for +acc: List<&2, Tm>
  P(List<&2, Tm> & Tm)

@unsafe
def P.arms(+beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    P.eat("{")
    r : List<&2, Tm> & Tm <- P.arms.go(Nil{})
    s : Sp <- P.span(beg)
    return P.arms.fin(r, s)

def word_to_term.go(+n: U32, +i: Nat, out: Tm, +s: Sp) -> Tm:
  match i:
    case 0n:
      out
    case 1n+j:
      word_to_term.go(n, j, Ctr{"WCon", [Ctr{Bool.pick(String, U32.is_zero(((n >> j : U32) .&. 1 : U32)),
        "False", "True"), Nil{}, s}, out], s}, s)

# The 32 bits of n as a Word, least significant first.
def word_to_term(+n: U32, +s: Sp) -> Tm:
  word_to_term.go(n, 32n, Ctr{"WNil", Nil{}, s}, s)

def u32_to_term(+n: U32, +s: Sp) -> Tm:
  Ctr{"U32", [word_to_term(n, s)], s}

def P.chr_lit.fin(+beg: U32, +n: U32, ok: Bool) -> P(Tm):
  match ok:
    case True{}:
      do P<Tm>:
        +spn : Sp <- P.span(beg)
        return Ctr{"Chr", [u32_to_term(n, spn)], spn}
    case False{}:
      P.fail(Tm, "a closing '")

def P.char.take(+c: U32) -> P(U32):
  do P<U32>:
    P.bump()
    return c

def P.char.plain() -> P(U32):
  do P<U32>:
    +c : U32 <- P.peek()
    P.if(U32, U32.is_zero(c), P.fail(U32, "a character"), P.char.take(c))

law uesc.hex:
  for s: String
  for +acc: U32
  for +n: Nat
  Maybe<&1, U32 & Nat>

@unsafe
def uesc.if(t: String, ok: Bool) -> Maybe<&1, U32 & Nat>:
  match ok:
    case True{}:
      uesc.hex(t, 0, 0n)
    case False{}:
      None{}

# A \u{hex} escape: its value and length (from the 'u'), if it is one.
def uesc(s: String) -> Maybe<&1, U32 & Nat>:
  match s:
    case SCon{Chr{+u}, SCon{Chr{123}, t}}:
      uesc.if(t, Bool.or(U32.is_eq(u, 117), U32.is_eq(u, 85)))
    case other:
      None{}

def ESCAPES() -> List<&2, U32>:
  [110, 10, 116, 9, 114, 13, 48, 0, 92, 92, 39, 39, 34, 34]

def P.escape.u.go(v: U32 & Nat) -> P(U32):
  (x, n) = v
  +xx = x
  +ps => Done{(xx, PS.set_cur(ps, Cur.steps(PS.cur(ps), n)))}

def P.escape.named(m: Maybe<&2, U32>) -> P(U32):
  match m:
    case Some{v}:
      P.pure(U32, v)
    case None{}:
      P.fail(U32, "an escape (\\n \\t \\r \\0 \\\\ \\' \\\" \\u{1F600})")

law escape.find:
  for e: List<&2, U32>
  for +c: U32
  Maybe<&2, U32>

@unsafe
def P.escape.u(m: Maybe<&1, U32 & Nat>) -> P(U32):
  match m:
    case Some{v}:
      P.escape.u.go(v)
    case None{}:
      do P<U32>:
        +c : U32 <- P.peek()
        P.bump()
        P.escape.named(escape.find(ESCAPES(), c))

def P.escape() -> P(U32):
  do P<U32>:
    r : String <- P.peek_rest()
    P.escape.u(uesc(r))

# One (possibly escaped) character of a literal.
def P.char() -> P(U32):
  do P<U32>:
    esc : Bool <- P.take("\\")
    P.if(U32, esc, P.escape(), P.char.plain())

def P.chr_lit(+beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    +n : U32 <- P.char()
    ok : Bool <- P.take("'")
    P.chr_lit.fin(beg, n, ok)

def chr_term(+c: U32, +s: Sp) -> Tm:
  Ctr{"Chr", [u32_to_term(c, s)], s}

def lit_chain(cs: List<&2, U32>, +s: Sp) -> Tm:
  match cs:
    case Nil{}:
      Ctr{"SNil", Nil{}, s}
    case c <> t:
      Ctr{"SCon", [chr_term(c, s), lit_chain(t, s)], s}

def codes.plain(cs: List<&2, U32>) -> Bool:
  match cs:
    case Nil{}:
      True{}
    case +c <> t:
      Bool.and(Bool.and(U32.is_le(c, 1114111), Bool.or(U32.is_lt(c, 55296), U32.is_gt(c, 57343))),
        codes.plain(t))

def lit_of(+cs: List<&2, U32>, +s: Sp) -> Tm:
  Bool.pick(Tm, codes.plain(cs), Lit{LStr{Str.from_codes(cs)}, s}, lit_chain(cs, s))

law P.str.go:
  for +acc: List<&2, U32>
  P(List<&2, U32>)

@unsafe
def P.str_lit(+beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    +cs : List<&2, U32> <- P.str.go(Nil{})
    s : Sp <- P.span(beg)
    return lit_of(cs, s)

def P.name.check.c(+k: String, c: Bool) -> P(String):
  match c:
    case True{}:
      P.fail(String, "a name (got the keyword '" ++ k ++ "')")
    case False{}:
      P.pure(String, k)

def P.name.check(+k: String) -> P(String):
  P.name.check.c(k, Str.has(KEYWORDS(), k))

def P.name() -> P(String):
  do P<String>:
    +k : String <- P.lexeme()
    P.name.check(k)

def book_hole(book: Book) -> Book:
  Book{tlds, ctrs, order, hols, open, tmps, tcnt} = book
  Book{tlds, ctrs, order, 1n+hols, open, tmps, tcnt}

def PS.set_book(ps: PS, b: Book) -> PS:
  PS{cur, stk, stn, frs, book, src, ns, dir, al} = ps
  PS{cur, stk, stn, frs, b, src, ns, dir, al}

def P.set_book(b: Book) -> P(Unit):
  ps => Done{(Unit{}, PS.set_book(ps, b))}

def P.count_hole() -> P(Unit):
  do P<Unit>:
    b : Book <- P.book()
    P.set_book(book_hole(b))

def P.hole(+beg: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    +k : String <- P.name()
    P.if(Unit, String.eq(k, "TODO"), P.count_hole(), P.pure(Unit, Unit{}))
    s : Sp <- P.span(beg)
    return Hol{k, s}

law P.rwt:
  for +beg: U32
  P(Tm)

law P.all:
  for +exi: Bool
  P(Tm)

law P.tup:
  for +beg: U32
  P(Tm)

@unsafe
def P.base.sym.go(+c: U32, +beg: U32, m: Maybe<&2, Nat>) -> P(Tm):
  match m:
    case Some{0n}:
      P.all(False{})
    case Some{1n}:
      do P<Tm>:
        +r : String <- P.peek_rest()
        P.amp(Str.second(r), beg)
    case Some{2n}:
      P.plus(beg)
    case Some{3n}:
      P.arms(beg)
    case Some{4n}:
      P.rwt(beg)
    case Some{5n}:
      P.brace(beg)
    case Some{6n}:
      do P<Tm>:
        P.bump()
        P.tup(beg)
    case Some{7n}:
      P.brack(beg)
    case Some{8n}:
      P.chr_lit(beg)
    case Some{9n}:
      P.str_lit(beg)
    case Some{10n}:
      P.hole(beg)
    case other:
      P.fail(Tm, "a term")

# The syntax of each symbol that starts a term.
@unsafe
def P.base.sym(+c: U32, +beg: U32) -> P(Tm):
  P.base.sym.go(c, beg, Str.index(["@", "&", "+", "\\", "%", "{", "(", "[", "'", "\"", "?"],
    Str.chr(c), 0n))

law P.num:
  P(Tm)

@unsafe
def P.base.go(+c: U32, +beg: U32, kind: Nat) -> P(Tm):
  match kind:
    case 0n:
      do P<Tm>:
        +k : String <- P.lexeme()
        P.base.word(k, beg)
    case 1n:
      P.num()
    case 2n+p:
      P.base.sym(c, beg)

@unsafe
def P.base(+beg: U32) -> P(Tm):
  do P<Tm>:
    +c : U32 <- P.peek()
    P.base.go(c, beg, Bool.pick(Nat, is_head(c), 0n, Bool.pick(Nat, is_digit(c), 1n, 2n)))

@unsafe
def P.term(lvl):
  do P<Tm>:
    P.skip()
    +beg : U32 <- P.pos()
    base : Tm <- P.base(beg)
    s : Sp <- P.span(beg)
    P.ops(Tm.spanned(base, s), lvl)

def amp.q(k: Nat) -> Q:
  match k:
    case 0n:
      QNone{}
    case 1n:
      QLone{}
    case 2n+p:
      QMany{}

@unsafe
def P.amp.go(+beg: U32, code: Nat) -> P(Tm):
  match code:
    case 0n:
      P.all(True{})
    case 1n+k:
      do P<Tm>:
        P.bump()
        P.bump()
        s : Sp <- P.span(beg)
        return TQua{amp.q(k), s}

def amp.code(+d: U32) -> Nat:
  Bool.pick(Nat, U32.is_eq(d, 48), 1n, Bool.pick(Nat, U32.is_eq(d, 49), 2n,
    Bool.pick(Nat, U32.is_eq(d, 50), 3n, 0n)))

@unsafe
def P.amp(d, beg):
  P.amp.go(beg, amp.code(d))

type Op is Data:
  Op{sym: String, prec: U32, right: Bool, name: String}

def OPS() -> List<&2, Op>:
  [Op{".|.", 6, False{}, ".or"}, Op{".^.", 7, False{}, ".xor"}, Op{".&.", 8, False{}, ".and"},
   Op{"||", 2, False{}, "Bool.or"}, Op{"&&", 3, False{}, "Bool.and"}, Op{"<=", 4, False{}, ".is_le"},
   Op{">=", 4, False{}, ".is_ge"}, Op{"<>", 5, True{}, ""}, Op{"++", 5, True{}, "String.append"},
   Op{"<<", 9, False{}, ".shln"}, Op{">>", 9, False{}, ".shrn"}, Op{"&", 1, True{}, ""},
   Op{"|", 1, True{}, ""}, Op{">", 4, False{}, ".is_gt"}, Op{"+", 10, False{}, ".add"},
   Op{"-", 10, False{}, ".sub"}, Op{"*", 11, False{}, ".mul"}, Op{"/", 11, False{}, ".div"},
   Op{"%", 11, False{}, ".mod"}]

def P.call.head.var(+k: String, +s: Sp, t: Tm) -> P(Tm):
  do P<Tm>:
    m : Maybe<&2, U32> <- P.lookup(k)
    q : String <- P.reso(k)
    return Bool.pick(Tm, Maybe.is_some(&2, U32, m), t, Ref{q, s, False{}})

def P.call.head(+out: Tm) -> P(Tm):
  match out:
    case Var{+k, i, +s}:
      P.call.head.var(k, s, Var{k, i, s})
    case VRf{+k, i, +s, r}:
      P.call.head.var(k, s, VRf{k, i, s, r})
    case other:
      P.pure(Tm, other)

def Tm.bang(t: Tm) -> Tm:
  match t:
    case Ref{k, s, b}:
      Ref{k, s, True{}}
    case other:
      other

@unsafe
def P.call.bang.go(h: Tm, +lvl: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    P.ops(Tm.bang(h), lvl)

@unsafe
def P.call.bang(+h: Tm, +lvl: U32) -> P(Tm):
  P.if(Tm, Tm.is_ref(h), P.call.bang.go(h, lvl), P.fail(Tm, "a named def before ! (only f!(..) offloads)"))

def P.span.from(s: Sp) -> P(Sp):
  match s:
    case NoSp{}:
      P.pure(Sp, NoSp{})
    case Sp{src, +beg, end}:
      P.span(beg)

def span.grow(out: Tm) -> P(Sp):
  P.span.from(Tm.span(out))

def Tld.x(t: Maybe<&2, Tld>) -> Nat:
  match t:
    case Some{TDef{n, x, ty, v, u, b, imps}}:
      x
    case other:
      0n

@unsafe
def apps(f: Tm, xs: List<&2, Tm>, +s: Sp) -> Tm:
  match xs:
    case Nil{}:
      f
    case x <> t:
      apps(TApp{f, x, s}, t, s)

law P.call.tmpl:
  for +h: Tm
  for +x: Nat
  for +ts: List<&2, Tm>
  P(List<&2, Tm>)

@unsafe
def P.call.args(+h: Tm, +lvl: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    b : Book <- P.book()
    +x : Nat <- P.pure(Nat, Tld.x(book_tld(b, Bool.pick(String, Tm.is_ref(h), Tm.name(h), ""))))
    P.skip()
    ts : List<&2, Tm> <- P.call.tmpl(h, x, Nil{})
    xs : List<&2, Tm> <- P.args(")")
    s2 : Sp <- span.grow(h)
    P.ops(apps(h, List.append(&2, Tm, ts, xs), s2), lvl)

@unsafe
def P.call(out: Tm, +lvl: U32) -> P(Tm):
  do P<Tm>:
    +h : Tm <- P.call.head(out)
    bang : Bool <- P.at("!")
    P.if(Tm, bang, P.call.bang(h, lvl), P.call.args(h, lvl))

def Cur.nl(+c: Cur) -> Bool:
  Cur{rest, pos, col, +nl, prev} = c
  nl

def P.nl() -> P(Bool):
  +ps => Done{(Cur.nl(PS.cur(ps)), ps)}

@unsafe
def P.index.set(out: Tm, ix: Tm, +s2: Sp, +lvl: U32) -> P(Tm):
  do P<Tm>:
    v : Tm <- P.term(2)
    P.ops(apps(Ref{"Array.set", s2, False{}}, [Ref{"U32", s2, False{}}, out, ix, v], s2), lvl)

@unsafe
def P.index(+out: Tm, +lvl: U32) -> P(Tm):
  do P<Tm>:
    P.bump()
    ix0 : Tm <- P.term0()
    P.eat("]")
    +s2 : Sp <- span.grow(out)
    +ix : Tm <- P.ns(ix0, Ref{"U32", s2, False{}})
    P.skip()
    +nl : Bool <- P.nl()
    set : Bool <- P.if(Bool, nl, P.pure(Bool, False{}), P.take("<-"))
    P.if(Tm, set, P.index.set(out, ix, s2, lvl), P.ops(TApp{TApp{TApp{Ref{"Array.get", s2, False{}},
      Ref{"U32", s2, False{}}, s2}, out, s2}, ix, s2}, lvl))

def PS.stn(+ps: PS) -> Nat:
  PS{cur, stk, +stn, frs, book, src, ns, dir, al} = ps
  stn

def P.stn() -> P(Nat):
  +ps => Done{(PS.stn(ps), ps)}

def SB.drop(xs: List<&2, SB>, n: Nat) -> List<&2, SB>:
  match xs n:
    case ys 0n:
      ys
    case y <> t 1n+m:
      SB.drop(t, m)
    case Nil{} k:
      Nil{}

def P.close.go(+n0: Nat, ps: PS) -> Result<&1, &1, Err, Unit & PS>:
  PS{cur, stk, +stn, frs, book, src, ns, dir, al} = ps
  Done{(Unit{}, PS{cur, SB.drop(stk, Nat.sub(stn, n0)), Nat.min(stn, n0), frs, book, src, ns, dir, al})}

# Drops the binders opened since the scope had n0 of them.
def P.close(+n0: Nat) -> P(Unit):
  ps => P.close.go(n0, ps)

def P.binder.go(+k: String, q: Q, s: Sp) -> P(Pt):
  do P<Pt>:
    i : U32 <- P.open(k)
    return PVar{k, i, q, s}

def P.binder(t: Tm) -> P(Pt):
  match t:
    case Var{+k, i, s}:
      P.binder.go(k, QLone{}, s)
    case VRf{+k, i, s, r}:
      P.binder.go(k, QLone{}, s)
    case VPl{+k, s}:
      P.binder.go(k, QMany{}, s)
    case other:
      P.fail(Pt, "a lambda binder (one name: k => body)")

def lam.build(x: Pt, f: Tm) -> Tm:
  match x:
    case PVar{k, +i, q, s}:
      Lam{k, i, CSyn{Nil{}, i, f}, s, q}
    case other:
      f

def Cur.col(+c: Cur) -> U32:
  Cur{rest, pos, +col, nl, prev} = c
  col

def P.col() -> P(U32):
  +ps => Done{(Cur.col(PS.cur(ps)), ps)}

#
# A def, case, lambda or parenthesized body: a match (rows of patterns), a
# let (names or patterns bound to values) or a reply (the result).
# A row of a match is a Body too (Row), as Bend has no mutually recursive
# types.
type Body is Data:
  BMatch{es: List<&2, Tm>, rows: List<&2, Body>, s: Sp}
  BLocal{ks: List<&2, Pt>, q: Q, vs: List<&2, Tm>, f: Body}
  BReply{x: Tm, s: Sp}
  Row{ps: List<&2, Pt>, f: Body}

law P.flatten:
  for b: Body
  for vars: List<&2, Pt>
  P(Tm)

law P.body:
  for +col: U32
  P(Body)

@unsafe
def P.block() -> P(Tm):
  do P<Tm>:
    P.skip()
    +c : U32 <- P.col()
    b : Body <- P.body((c - 1 : U32))
    P.flatten(b, Nil{})

@unsafe
def P.lam(out: Tm, +lvl: U32) -> P(Tm):
  do P<Tm>:
    ok : Bool <- P.take("=>")
    +n0 : Nat <- P.stn()
    x : Pt <- P.binder(out)
    f : Tm <- P.block()
    P.close(n0)
    P.ops(lam.build(x, f), lvl)

@unsafe
def P.arrow(+out: Tm, +lvl: U32) -> P(Tm):
  do P<Tm>:
    ok : Bool <- P.take("->")
    b : Tm <- P.term0()
    s2 : Sp <- span.grow(out)
    +i : U32 <- P.open("_")
    P.ops(All{QLone{}, "_", i, out, CSyn{Nil{}, i, b}, s2}, lvl)

@unsafe
def P.minq(+out: Tm, +lvl: U32) -> P(Tm):
  do P<Tm>:
    ok : Bool <- P.take("<&>")
    b : Tm <- P.term(5)
    s2 : Sp <- span.grow(out)
    P.ops(Min{out, b, s2}, lvl)

def infix.build(+sym: String, name: String, +out: Tm, +b: Tm, +s: Sp, t: Sp) -> Tm:
  Bool.pick(Tm, String.eq(sym, "<>"), Ctr{"Con", [out, b], s},
    Bool.pick(Tm, String.eq(sym, "&"), TApp{TApp{Ref{"Pair", s, False{}}, out, s}, b, s},
      Bool.pick(Tm, String.eq(sym, "|"), TApp{TApp{Ref{"Or", s, False{}}, out, s}, b, s},
        TApp{TApp{Ref{name, t, False{}}, out, s}, b, s})))

@unsafe
def P.infix.go(+out: Tm, +lvl: U32, +sym: String, +prec: U32, right: Bool, +name: String) -> P(Tm):
  do P<Tm>:
    ok : Bool <- P.take(sym)
    +pos : U32 <- P.pos()
    +t : Sp <- P.span((pos - U32.from_nat(String.length(sym)) : U32))
    b : Tm <- P.term(Bool.pick(U32, right, prec, U32.inc(prec)))
    +s : Sp <- span.grow(out)
    P.ops(infix.build(sym, name, out, b, s, t), lvl)

@unsafe
def P.infix(+out: Tm, +lvl: U32, m: Maybe<&2, Op>, arrow: Bool) -> P(Tm):
  match m:
    case None{}:
      P.pure(Tm, out)
    case Some{Op{+sym, +prec, +right, +name}}:
      P.if(Tm, Bool.or(U32.is_lt(prec, lvl), arrow), P.pure(Tm, out), P.infix.go(out, lvl, sym, prec, right, name))

law op.find:
  for ops: List<&2, Op>
  for +r: String
  for +prev: U32
  Maybe<&2, Op>

law P.lt:
  for +out: Tm
  for +lvl: U32
  P(Tm)

@unsafe
def P.ops.go(out: Tm, +lvl: U32, +r: String, +prev: U32, k: Nat) -> P(Tm):
  match k:
    case 0n:
      P.pure(Tm, out)
    case 1n:
      P.call(out, lvl)
    case 2n:
      P.index(out, lvl)
    case 3n:
      P.lt(out, lvl)
    case 4n:
      P.lam(out, lvl)
    case 5n:
      P.arrow(out, lvl)
    case 6n:
      P.minq(out, lvl)
    case 7n+p:
      P.infix(out, lvl, op.find(OPS(), r, prev), Str.prefix(r, "<-"))

def Cur.prev(+c: Cur) -> U32:
  Cur{rest, pos, col, nl, +prev} = c
  prev

def P.prev() -> P(U32):
  +ps => Done{(Cur.prev(PS.cur(ps)), ps)}

def ops.lt(+r: String, +lvl: U32, +prev: U32) -> Bool:
  +nx = Str.second(r)
  Bool.and(Bool.and(Str.prefix(r, "<"), Bool.not(Bool.or(Bool.or(U32.is_eq(nx, 45), U32.is_eq(nx, 61)),
    Bool.or(U32.is_eq(nx, 60), U32.is_eq(nx, 62))))),
    Bool.and(Bool.not(Str.prefix(r, "<&>")), Bool.or(U32.is_le(lvl, 4),
      Bool.not(Bool.or(is_space(prev), U32.is_zero(prev))))))

@unsafe
def P.ops(out, lvl):
  do P<Tm>:
    P.skip()
    +nl : Bool <- P.nl()
    +r : String <- P.peek_rest()
    +prev : U32 <- P.prev()
    +call : Bool = Bool.or(Str.prefix(r, "("), Str.prefix(r, "!("))
    +idx : Bool = Str.prefix(r, "[")
    P.ops.go(out, lvl, r, prev, Bool.pick(Nat, Bool.and(nl, Bool.or(Str.prefix(r, "("), idx)), 0n,
      Bool.pick(Nat, call, 1n, Bool.pick(Nat, idx, 2n,
        Bool.pick(Nat, ops.lt(r, lvl, prev), 3n,
          Bool.pick(Nat, Bool.and(U32.is_zero(lvl), Str.prefix(r, "=>")), 4n,
            Bool.pick(Nat, Bool.and(U32.is_zero(lvl), Str.prefix(r, "->")), 5n,
              Bool.pick(Nat, Bool.and(U32.is_le(lvl, 5), Str.prefix(r, "<&>")), 6n, 7n))))))))

# Statements
# ==========

def Tld.adt_fill(t: Maybe<&2, Tld>, +len: Nat) -> Maybe<&2, Nat>:
  match t:
    case Some{TADT{+n, +g, ty, cs, tbase}}:
      Bool.pick(Maybe<&2, Nat>, Nat.is_eq(Nat.add(len, g), n), Some{g}, None{})
    case other:
      None{}

def fill.go(m: Maybe<&2, Nat>, xs: List<&2, Tm>, +s: Sp) -> List<&2, Tm>:
  match m:
    case None{}:
      xs
    case Some{g}:
      List.append(&2, Tm, List.repeat_tm(TQua{QLone{}, s}, g), xs)

# D<A> may leave out D's leading quantities: they are &1.
def P.fill(+k: String, +xs: List<&2, Tm>, +s: Sp) -> P(List<&2, Tm>):
  do P<List<&2, Tm>>:
    b : Book <- P.book()
    return fill.go(Tld.adt_fill(book_tld(b, k), List.length(&2, Tm, xs)), xs, s)

law P.do_stmt:
  for +m: String
  for +ts: List<&2, Tm>
  for +col: U32
  P(Tm)

@unsafe
def P.do(beg):
  do P<Tm>:
    +m : String <- P.name()
    P.eat("<")
    args : List<&2, Tm> <- P.args(">")
    +q : String <- P.reso(m)
    s : Sp <- P.span(beg)
    +ts : List<&2, Tm> <- P.fill(q, args, s)
    P.eat(":")
    P.skip()
    +col : U32 <- P.col()
    P.do_stmt(m, ts, col)

# Whether the word w comes next (not as the start of a longer name).
def P.at_word(+w: String) -> P(Bool):
  do P<Bool>:
    P.skip()
    +r : String <- P.peek_rest()
    return Bool.and(Str.prefix(r, w), Bool.not(is_name(Str.first(String.drop(r, String.length(w))))))

law P.row:
  for +col: U32
  for +ccol: U32
  for +n: Nat
  for +rcol: U32
  P(List<&2, Body>)

@unsafe
def P.rows(+col: U32, +ccol: U32, +n: Nat) -> P(List<&2, Body>):
  do P<List<&2, Body>>:
    cw : Bool <- P.at_word("case")
    +c : U32 <- P.col()
    P.if(List<&2, Body>, Bool.and(U32.is_gt(ccol, col), Bool.and(cw, U32.is_ge(c, ccol))), P.row(col, ccol, n, c),
      P.pure(List<&2, Body>, Nil{}))

law P.terms:
  P(List<&2, Tm>)

@unsafe
def P.body.match(+col: U32, +beg: U32) -> P(Body):
  do P<Body>:
    +es : List<&2, Tm> <- P.terms()
    P.skip()
    +ccol : U32 <- P.col()
    rows : List<&2, Body> <- P.rows(col, ccol, List.length(&2, Tm, es))
    s : Sp <- P.span(beg)
    return BMatch{es, rows, s}

def P.body.erased_name(+beg: U32) -> P(Tm):
  do P<Tm>:
    k : String <- P.name()
    s : Sp <- P.span(beg)
    return Var{k, 0, s}

@unsafe
def P.body.ty() -> P(Maybe<&2, Tm>):
  do P<Maybe<&2, Tm>>:
    t : Tm <- P.term0()
    return Some{t}

# x : T with no '=' after it is not a typed let: back to before the ':'.
def P.body.ty_ok(at: Cur, ty: Maybe<&2, Tm>, eq: Bool) -> P(Maybe<&2, Tm>):
  match ty eq:
    case Some{t} False{}:
      do P<Maybe<&2, Tm>>:
        P.set_cur(at)
        return None{}
    case m e:
      P.pure(Maybe<&2, Tm>, m)

@unsafe
def P.body.let.ann(+beg: U32, ty: Maybe<&2, Tm>) -> P(List<&2, Tm>):
  match ty:
    case None{}:
      P.pure(List<&2, Tm>, Nil{})
    case Some{t}:
      do P<List<&2, Tm>>:
        v : Tm <- P.term0()
        s : Sp <- P.span(beg)
        return [Ann{v, t, s}]

@unsafe
def P.body.let.eq(+beg: U32, ty: Maybe<&2, Tm>) -> P(List<&2, Tm>):
  do P<List<&2, Tm>>:
    P.eat("=")
    P.body.let.ann(beg, ty)

law P.patt:
  for +t: Tm
  P(Pt)

@unsafe
def P.body.binders(ts: List<&2, Tm>, +names: Bool) -> P(List<&2, Pt>):
  match ts:
    case Nil{}:
      P.pure(List<&2, Pt>, Nil{})
    case +x <> t:
      do P<List<&2, Pt>>:
        P.if(Unit, Bool.and(names, Bool.not(Tm.is_var(x))),
          P.throw(Unit, err0("a name (a parallel or typed let binds names; destructure in its body)", MNone{},
            Tm.span(x))), P.pure(Unit, Unit{}))
        p : Pt <- P.patt(x)
        ps : List<&2, Pt> <- P.body.binders(t, names)
        return p <> ps

law P.body.vals:
  for +vs: List<&2, Tm>
  for +n: Nat
  P(List<&2, Tm>)

def Lst.empty(a, -A: Kind(a), xs: List<a, A>) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case h <> t:
      False{}

@unsafe
def P.body.let(+col: U32, +beg: U32, +q: Q, +ts: List<&2, Tm>, +ty: Maybe<&2, Tm>, +vs0: List<&2, Tm>) ->
  P(Body):
  do P<Body>:
    vs1 : List<&2, Tm> <- P.if(List<&2, Tm>, Lst.empty(&2, Tm, vs0), P.body.let.eq(beg, ty), P.pure(List<&2, Tm>, vs0))
    vs : List<&2, Tm> <- P.body.vals(vs1, List.length(&2, Tm, ts))
    P.skip()
    semi : Bool <- P.take(";")
    +n0 : Nat <- P.stn()
    ks : List<&2, Pt> <- P.body.binders(ts, Bool.or(Nat.is_gt(List.length(&2, Tm, ts), 1n), Maybe.is_some(&2, Tm, ty)))
    f : Body <- P.body(col)
    P.close(n0)
    return BLocal{ks, q, vs, f}

def P.more(+col: U32) -> P(Bool):
  do P<Bool>:
    semi : Bool <- P.at(";")
    +c : U32 <- P.peek()
    +cc : U32 <- P.col()
    return Bool.or(semi, Bool.and(Bool.not(U32.is_zero(c)), U32.is_eq(cc, col)))

@unsafe
def P.body.reply.go(+col: U32, +beg: U32, +bcol: U32, +t: Tm, w: Maybe<&2, Tm>) -> P(Body):
  match w:
    case None{}:
      do P<Body>:
        s : Sp <- P.span(beg)
        return BReply{t, s}
    case Some{x}:
      do P<Body>:
        more : Bool <- P.more(bcol)
        s : Sp <- P.span(beg)
        P.if(Body, more, P.body.let(col, beg, QLone{}, [x], None{}, [t]), P.pure(Body, BReply{t, s}))

def term_unapply.go(t: Tm, xs: List<&2, Tm>) -> Tm & List<&2, Tm>:
  match t:
    case TApp{f, x, s}:
      term_unapply.go(f, x <> xs)
    case other:
      (other, xs)

def term_unapply(t: Tm) -> Tm & List<&2, Tm>:
  term_unapply.go(t, Nil{})

def term_write.go(r: Tm & List<&2, Tm>) -> Maybe<&2, Tm>:
  (h, xs) = r
  match h xs:
    case Ref{"Array.set", s, b} a <> +x <> i <> v <> Nil{}:
      Bool.pick(Maybe<&2, Tm>, Tm.is_var(x), Some{x}, None{})
    case p q:
      None{}

def term_write(t: Tm) -> Maybe<&2, Tm>:
  term_write.go(term_unapply(t))

@unsafe
def P.body.reply(+col: U32, +beg: U32, +bcol: U32, +t: Tm) -> P(Body):
  P.body.reply.go(col, beg, bcol, t, term_write(t))

def Q.is_lone(q: Q) -> Bool:
  match q:
    case QLone{}:
      True{}
    case other:
      False{}

def Lst.head(-A: Data, d: A, xs: List<&2, A>) -> A:
  match xs:
    case Nil{}:
      d
    case h <> t:
      h

@unsafe
def P.body.local.go(
  +col: U32, +beg: U32, +bcol: U32, +q: Q, +ts: List<&2, Tm>, +ty: Maybe<&2, Tm>, eq: Bool
) -> P(Body):
  +one = Nat.is_eq(List.length(&2, Tm, ts), 1n)
  +plain = Bool.and(Bool.and(Maybe.is_none(&2, Tm, ty), Q.is_lone(q)), Bool.and(one, Bool.not(eq)))
  P.if(Body, plain, P.body.reply(col, beg, bcol, Lst.head(Tm, Efq{NoSp{}}, ts)),
    P.body.let(col, beg, q, ts, ty, Nil{}))

law P.local.names:
  for +q: Q
  for +ts: List<&2, Tm>
  P(List<&2, Tm>)

@unsafe
def P.body.local(+col: U32, +beg: U32, +bcol: U32) -> P(Body):
  do P<Body>:
    +neg : Bool <- P.take("-")
    +q : Q <- P.pure(Q, Bool.pick(Q, neg, QNone{}, QLone{}))
    first : Tm <- P.if(Tm, neg, P.body.erased_name(beg), P.term0())
    P.skip()
    +ts : List<&2, Tm> <- P.local.names(q, [first])
    +at : Cur <- P.cur()
    colon : Bool <- P.if(Bool, Nat.is_eq(List.length(&2, Tm, ts), 1n), P.take(":"), P.pure(Bool, False{}))
    ty0 : Maybe<&2, Tm> <- P.if(Maybe<&2, Tm>, colon, P.body.ty(), P.pure(Maybe<&2, Tm>, None{}))
    P.skip()
    +eq : Bool <- P.at("=")
    +ty : Maybe<&2, Tm> <- P.body.ty_ok(at, ty0, eq)
    eqeq : Bool <- P.at("==")
    P.body.local.go(col, beg, bcol, q, ts, ty, Bool.and(eq, Bool.not(eqeq)))

def P.word.if(+w: String, ok: Bool) -> P(Bool):
  match ok:
    case True{}:
      P.take(w)
    case False{}:
      P.pure(Bool, False{})

def P.word(+w: String) -> P(Bool):
  do P<Bool>:
    ok : Bool <- P.at_word(w)
    P.word.if(w, ok)

@unsafe
def P.body(col):
  do P<Body>:
    P.skip()
    +beg : U32 <- P.pos()
    +bcol : U32 <- P.col()
    mat : Bool <- P.word("match")
    P.if(Body, mat, P.body.match(col, beg), P.body.local(col, beg, bcol))

@unsafe
def P.body.vals.more(+vs: List<&2, Tm>, +n: Nat) -> P(List<&2, Tm>):
  do P<List<&2, Tm>>:
    v : Tm <- P.term0()
    P.body.vals(List.append(&2, Tm, vs, [v]), n)

@unsafe
def P.body.vals(vs, n):
  P.if(List<&2, Tm>, Nat.is_ge(List.length(&2, Tm, vs), n), P.pure(List<&2, Tm>, vs), P.body.vals.more(vs, n))

# Declarations
# ============

def P.get() -> P(PS):
  +ps => Done{(ps, ps)}

def P.put(ps: PS) -> P(Unit):
  old => Done{(Unit{}, ps)}

def P.qual(+k: String) -> P(String):
  +ps => Done{(PS.qual(ps, k), ps)}

def P.quant() -> P(Q):
  do P<Q>:
    P.skip()
    +minus : Bool <- P.take("-")
    plus : Bool <- P.if(Bool, minus, P.pure(Bool, False{}), P.take("+"))
    return Bool.pick(Q, minus, QNone{}, Bool.pick(Q, plus, QMany{}, QLone{}))

@unsafe
def P.patts(xs: List<&2, Tm>) -> P(List<&2, Pt>):
  match xs:
    case Nil{}:
      P.pure(List<&2, Pt>, Nil{})
    case x <> t:
      do P<List<&2, Pt>>:
        p : Pt <- P.patt(x)
        ps : List<&2, Pt> <- P.patts(t)
        return p <> ps

@unsafe
def P.patt.ctr.n(+k: String, xs: List<&2, Tm>, +s: Sp, +n: Nat, ok: Bool) -> P(Pt):
  match ok:
    case False{}:
      P.throw(Pt, err0("a " ++ k ++ " pattern with " ++ Nat.show(n) ++
        Bool.pick(String, Nat.is_eq(n, 1n), " field", " fields"), MNone{}, s))
    case True{}:
      do P<Pt>:
        ps : List<&2, Pt> <- P.patts(xs)
        return PCtr{k, ps, s}

@unsafe
def P.patt.ctr(+k: String, +xs: List<&2, Tm>, +s: Sp, c: Maybe<&2, CtrD>) -> P(Pt):
  match c:
    case None{}:
      P.throw(Pt, err0("a declared constructor (unknown: " ++ k ++ ")", MNone{}, s))
    case Some{CtrD{ck, +n, ty}}:
      P.patt.ctr.n(k, xs, s, n, Nat.is_eq(n, List.length(&2, Tm, xs)))

def P.patt.var.go(+t: Tm, ctr: Bool) -> P(Pt):
  match ctr:
    case True{}:
      P.throw(Pt, err0("a braced constructor pattern (" ++ Tm.name(t) ++ " is a constructor: write " ++
        Tm.name(t) ++ "{}, or rename the binder)", MNone{}, Tm.span(t)))
    case False{}:
      P.binder(t)

law higher:
  for +book: Book
  for tm: Tm
  for +env: List<&2, Tm>
  Tm

@unsafe
def higher0(+book: Book, tm: Tm) -> Tm:
  higher(book, tm, Nil{})

def Q.def(q: Q) -> Q:
  match q:
    case QUnd{}:
      QLone{}
    case other:
      other

def quant_show(q: Q) -> String:
  match q:
    case QNone{}:
      "-"
    case QMany{}:
      "+"
    case other:
      ""

#
# higher(env, tm) is the official term_higher: variables bound in env are
# replaced, a binder keeps its body under env (a CSyn), and an application
# of a lambda reduces.
def syn_body(c: Tm) -> Tm:
  match c:
    case CSyn{env, i, b}:
      b
    case CLet{env, ids, b}:
      b
    case other:
      other

def show.bound_at.c(+n: Nat, +i: U32, c: Maybe<&2, Nat>) -> Bool:
  match c:
    case None{}:
      False{}
    case Some{j}:
      Nat.is_eq(Nat.sub(Nat.sub(n, 1n), j), U32.to_nat(i))

# Whether the innermost binder named k sits at depth i.
def show.bound_at(+bnd: List<&2, String>, +n: Nat, +k: String, +i: U32) -> Bool:
  show.bound_at.c(n, i, Str.index(bnd, k, 0n))

def show.paren(b: Bool, s: String) -> String:
  match b:
    case True{}:
      "(" ++ s ++ ")"
    case False{}:
      s

law show_hex.more:
  for +n: U32
  for acc: String
  for last: Bool
  String

@unsafe
def U32.show_hex.go(+n: U32, acc: String) -> String:
  +d = (n .&. 15 : U32)
  +c = Str.chr(Bool.pick(U32, U32.is_lt(d, 10), (48 + d : U32), (87 + d : U32)))
  show_hex.more(n, c ++ acc, U32.is_lt(n, 16))

def U32.show_hex(+n: U32) -> String:
  U32.show_hex.go(n, "")

def show.chr(+c: U32, +quote: U32) -> String:
  Bool.pick(String, U32.is_eq(c, 10), "\\n",
    Bool.pick(String, U32.is_eq(c, 9), "\\t",
      Bool.pick(String, U32.is_eq(c, 13), "\\r",
        Bool.pick(String, U32.is_eq(c, 0), "\\0",
          Bool.pick(String, Bool.or(U32.is_eq(c, 92), U32.is_eq(c, quote)), "\\" ++ Str.chr(c),
            Bool.pick(String, Bool.or(Bool.or(U32.is_lt(c, 32), U32.is_eq(c, 127)),
              Bool.or(Bool.and(U32.is_ge(c, 55296), U32.is_le(c, 57343)), U32.is_gt(c, 1114111))),
              "\\u{" ++ U32.show_hex(c) ++ "}", Str.chr(c)))))))

def show.text(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{Chr{c}, t}:
      show.chr(c, 34) ++ show.text(t)

def show.join(xs: List<&2, String>, +sep: String) -> String:
  String.join(xs, sep)

def show.let_ks(ks: List<&2, String>, qs: List<&2, Q>) -> List<&2, String>:
  match ks qs:
    case k <> kt q <> qt:
      (quant_show(q) ++ k) <> show.let_ks(kt, qt)
    case k <> kt Nil{}:
      k <> show.let_ks(kt, Nil{})
    case a b:
      Nil{}

def show.qua(q: Q) -> String:
  match q:
    case QNone{}:
      "&0"
    case QMany{}:
      "&2"
    case other:
      "&1"

def show.rems(r: List<&2, String>) -> String:
  match r:
    case Nil{}:
      ""
    case c <> t:
      " - " ++ c ++ "{}" ++ show.rems(t)

law show.typ:
  for g: Tm
  for +bnd: List<&2, String>
  for +n: Nat
  String

law show.app:
  for t: Tm
  for +p: U32
  for +bnd: List<&2, String>
  for +n: Nat
  String

law show.rwt:
  for e: Tm
  for pr: Tm
  for f: Tm
  for +bnd: List<&2, String>
  for +n: Nat
  String

law show.ctr:
  for +t: Tm
  for +p: U32
  for +bnd: List<&2, String>
  for +n: Nat
  String

law show.args:
  for +bnd: List<&2, String>
  for +n: Nat
  for xs: List<&2, Tm>
  for +p: U32
  List<&2, String>

law show.arms:
  for t: Tm
  for +bnd: List<&2, String>
  for +n: Nat
  List<&2, String>

@unsafe
def term_show.go(t: Tm, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  match t:
    case Var{+k, +i, s}:
      Bool.pick(String, show.bound_at(bnd, n, k, i), k, k ++ "^" ++ U32.show(i))
    case Ref{+k, s, b}:
      Bool.pick(String, Str.has(bnd, k), k ++ "^", k) ++ Bool.pick(String, b, "!", "")
    case Sub{i, pt, f, s}:
      term_show.go(f, p, bnd, n)
    case Let{+ks, ids, vs, f, s, qs}:
      +vs2 = show.args(bnd, n, vs, 2)
      +m = List.length(&2, String, ks)
      +f2 = term_show.go(syn_body(f), 0, List.append(&2, String, List.reverse(&2, String, ks), bnd), Nat.add(n, m))
      show.paren(U32.is_ge(p, 1), show.join(show.let_ks(ks, qs), " ") ++ " = " ++ show.join(vs2, " ") ++
        "; " ++ f2)
    case Typ{g, s}:
      show.typ(g, bnd, n)
    case Qnt{s}:
      "Quant"
    case TQua{q, s}:
      show.qua(q)
    case Min{a, b, s}:
      show.paren(U32.is_gt(p, 2), term_show.go(a, 3, bnd, n) ++ " <&> " ++ term_show.go(b, 3, bnd, n))
    case All{q, +k, i, a, b, s}:
      show.paren(U32.is_gt(p, 2), "@" ++ quant_show(q) ++ k ++ ":" ++ term_show.go(a, 3, bnd, n) ++ " -> " ++
        term_show.go(syn_body(b), 2, k <> bnd, 1n+n))
    case Lam{+k, i, f, s, q}:
      show.paren(U32.is_gt(p, 1), quant_show(Q.def(q)) ++ k ++ " => " ++
        term_show.go(syn_body(f), 0, k <> bnd, 1n+n))
    case TApp{f, x, s}:
      show.app(TApp{f, x, s}, p, bnd, n)
    case ADT{+k, xs, s, r}:
      +rs = show.rems(r)
      +as = show.args(bnd, n, xs, 1)
      show.paren(Bool.and(Bool.not(String.is_empty(rs)), U32.is_gt(p, 2)), k ++
        Bool.pick(String, Bool.and(Lst.empty(&2, String, as), String.is_empty(rs)), "",
          "<" ++ show.join(as, ", ") ++ ">") ++ rs)
    case Ctr{k, xs, s}:
      show.ctr(Ctr{k, xs, s}, p, bnd, n)
    case Lit{LNat{v}, s}:
      Nat.show(v) ++ "n"
    case Lit{LStr{v}, s}:
      "\"" ++ show.text(v) ++ "\""
    case Mat{k, h, m, s}:
      "\\{" ++ show.join(show.arms(Mat{k, h, m, s}, bnd, n), "; ") ++ "}"
    case Efq{s}:
      "\\{}"
    case Eql{a, b, ty, s}:
      "{" ++ term_show.go(a, 2, bnd, n) ++ " == " ++ term_show.go(b, 2, bnd, n) ++ " : " ++
        term_show.go(ty, 2, bnd, n) ++ "}"
    case Rfl{s}:
      "{==}"
    case Hol{k, s}:
      "?" ++ k
    case Rwt{e, pr, f, s}:
      show.paren(U32.is_gt(p, 1), show.rwt(e, pr, f, bnd, n))
    case Ann{x, ty, s}:
      "{" ++ term_show.go(x, 2, bnd, n) ++ " : " ++ term_show.go(ty, 2, bnd, n) ++ "}"
    case Cel{k, s, v}:
      term_show.go(v, p, bnd, n)
    case VRf{k, i, s, r}:
      term_show.go(r, p, bnd, n)
    case VPl{k, s}:
      k
    case other:
      "?"

def term_show(t: Tm, +p: U32, +bnd: List<&2, String>) -> String:
  term_show.go(t, p, bnd, List.length(&2, String, bnd))

law term_lower:
  for +book: Book
  for term: Tm
  for +d: U32
  Tm

@unsafe
def P.patt.other(+t: Tm) -> P(Pt):
  do P<Pt>:
    +b : Book <- P.book()
    P.throw(Pt, err0("a pattern (a binder or a constructor)",
      MStr{term_show(term_lower(b, higher0(b, t), 0), 0, Nil{})}, Tm.span(t)))

def P.patt.var(+t: Tm, var: Bool) -> P(Pt):
  match var:
    case True{}:
      do P<Pt>:
        +q : String <- P.reso(Tm.name(t))
        b : Book <- P.book()
        P.patt.var.go(t, Maybe.is_some(&2, CtrD, book_ctr(b, q)))
    case False{}:
      P.patt.other(t)

def nat_full(n: Nat, +s: Sp) -> Tm:
  match n:
    case 0n:
      Ctr{"Zero", Nil{}, s}
    case 1n+p:
      Ctr{"Succ", [nat_full(p, s)], s}

def lit_full(t: Tm) -> Tm:
  match t:
    case Lit{LStr{x}, +s}:
      lit_chain(Str.codes(x), s)
    case Lit{LNat{n}, +s}:
      nat_full(n, s)
    case other:
      other

@unsafe
def P.patt(t):
  match t:
    case Ctr{+k, xs, +s}:
      do P<Pt>:
        b : Book <- P.book()
        P.patt.ctr(k, xs, s, book_ctr(b, k))
    case Lit{v, s}:
      P.patt(lit_full(Lit{v, s}))
    case other:
      P.patt.var(other, Tm.is_var(other))

@unsafe
def P.arms.more(acc: List<&2, Tm>, +t: Tm, arm: Bool) -> P(List<&2, Tm> & Tm):
  match arm:
    case True{}:
      do P<List<&2, Tm> & Tm>:
        +k : String <- P.reso(Tm.name(t))
        h : Tm <- P.term0()
        P.skip()
        semi : Bool <- P.take(";")
        P.arms.go(List.append(&2, Tm, acc, [Ctr{k, [h], Tm.span(t)}]))
    case False{}:
      do P<List<&2, Tm> & Tm>:
        P.skip()
        semi : Bool <- P.take(";")
        P.eat("}")
        return (acc, t)

@unsafe
def P.arms.item(acc: List<&2, Tm>) -> P(List<&2, Tm> & Tm):
  do P<List<&2, Tm> & Tm>:
    +t : Tm <- P.term0()
    P.skip()
    +named : Bool <- P.pure(Bool, Bool.or(Tm.is_var(t), Tm.is_ref(t)))
    colon : Bool <- P.if(Bool, named, P.take(":"), P.pure(Bool, False{}))
    P.arms.more(acc, t, colon)

@unsafe
def P.arms.go(acc):
  do P<List<&2, Tm> & Tm>:
    P.skip()
    close : Bool <- P.take("}")
    P.if(List<&2, Tm> & Tm, close, P.pure(List<&2, Tm> & Tm, (acc, Efq{NoSp{}})), P.arms.item(acc))

@unsafe
def P.rwt.named(+e0: Tm) -> P(String & Tm):
  do P<String & Tm>:
    e : Tm <- P.term0()
    return (Tm.name(e0), e)

# %e : P; f   and   %k@e : P; f
@unsafe
def P.rwt.name(+e0: Tm, at: Bool) -> P(String & Tm):
  match at:
    case True{}:
      P.if(String & Tm, Tm.is_var(e0), P.rwt.named(e0),
        P.fail(String & Tm, "a name before @ (a rewrite binder is one name: %e@E : P)"))
    case False{}:
      P.pure(String & Tm, ("", e0))

def P.push_scope(b: SB) -> P(Unit):
  ps => Done{(Unit{}, PS.push(ps, b))}

@unsafe
def P.rwt.go(+beg: U32, +e0: Tm, r: String & Tm) -> P(Tm):
  (k, e) = r
  +kk = k
  do P<Tm>:
    P.eat(":")
    +n0 : Nat <- P.stn()
    +xi : U32 <- P.fresh_id()
    P.push_scope(SB{"_", xi})
    +ei : U32 <- P.open(kk)
    pr : Tm <- P.term0()
    P.close(n0)
    P.skip()
    semi : Bool <- P.take(";")
    f : Tm <- P.block()
    +s : Sp <- P.span(beg)
    return Rwt{e, Lam{"_", xi, CSyn{Nil{}, xi, Lam{kk, ei, CSyn{Nil{}, ei, pr}, Tm.span(e0), QUnd{}}}, s, QUnd{}},
      f, s}

@unsafe
def P.rwt(beg):
  do P<Tm>:
    P.bump()
    +e0 : Tm <- P.term0()
    P.skip()
    at : Bool <- P.take("@")
    r : String & Tm <- P.rwt.name(e0, at)
    P.rwt.go(beg, e0, r)

@unsafe
def P.str.more(acc: List<&2, U32>) -> P(List<&2, U32>):
  do P<List<&2, U32>>:
    c : U32 <- P.char()
    P.str.go(c <> acc)

@unsafe
def P.str.go(acc):
  do P<List<&2, U32>>:
    done : Bool <- P.take("\"")
    +c : U32 <- P.peek()
    P.if(List<&2, U32>, done, P.pure(List<&2, U32>, List.reverse(&2, U32, acc)),
      P.if(List<&2, U32>, U32.is_zero(c), P.fail(List<&2, U32>, "a closing \""), P.str.more(acc)))

def all.build(exi: Bool, q: Q, +k: String, +i: U32, a: Tm, b: Tm, +s: Sp) -> Tm:
  match exi:
    case True{}:
      TApp{TApp{Ref{"Exists", s, False{}}, a, s}, Lam{k, i, CSyn{Nil{}, i, b}, s, QUnd{}}, s}
    case False{}:
      All{q, k, i, a, CSyn{Nil{}, i, b}, NoSp{}}

# @x:A -> B   @-x:A -> B   &x:A -> B (a dependent pair)
@unsafe
def P.all(exi):
  do P<Tm>:
    +beg : U32 <- P.pos()
    P.bump()
    q : Q <- P.if(Q, exi, P.pure(Q, QLone{}), P.quant())
    +k : String <- P.name()
    P.eat(":")
    a : Tm <- P.term(1)
    P.eat("->")
    +n0 : Nat <- P.stn()
    +i : U32 <- P.open(k)
    b : Tm <- P.term0()
    P.close(n0)
    s : Sp <- P.span(beg)
    return all.build(exi, q, k, i, a, b, s)

def Body.reply_x(b: Body) -> Tm:
  match b:
    case BReply{x, s}:
      x
    case other:
      Efq{NoSp{}}

@unsafe
def P.tup.more(+beg: U32, b: Body) -> P(Tm):
  do P<Tm>:
    rest : Tm <- P.tup(beg)
    s : Sp <- P.span(beg)
    return Ctr{"Tuple", [Body.reply_x(b), rest], s}

@unsafe
def P.tup.ann(out: Tm) -> P(Tm):
  do P<Tm>:
    ty : Tm <- P.term0()
    P.ns(out, ty)

@unsafe
def P.tup.end(b: Body) -> P(Tm):
  do P<Tm>:
    +out : Tm <- P.flatten(b, Nil{})
    ann : Bool <- P.take(":")
    out2 : Tm <- P.if(Tm, ann, P.tup.ann(out), P.pure(Tm, out))
    P.eat(")")
    return out2

def Body.is_reply(+b: Body) -> Bool:
  match b:
    case BReply{x, s}:
      True{}
    case other:
      False{}

# (a, b, c), or a parenthesized body with an optional ': T'.
@unsafe
def P.tup(beg):
  do P<Tm>:
    P.skip()
    +col : U32 <- P.col()
    +b : Body <- P.body((col - 1 : U32))
    P.skip()
    +reply : Bool <- P.pure(Bool, Body.is_reply(b))
    comma : Bool <- P.if(Bool, reply, P.take(","), P.pure(Bool, False{}))
    P.if(Tm, comma, P.tup.more(beg, b), P.tup.end(b))

def P.steps(n: Nat) -> P(Unit):
  +ps => Done{(Unit{}, PS.set_cur(ps, Cur.steps(PS.cur(ps), n)))}

def F32.is_finite(+f: F32) -> Bool:
  +b = F32.bits(f)
  Bool.not(U32.is_eq((b .&. 2139095040 : U32), 2139095040))

def P.flt.go(+txt: String, m: Maybe<&2, F32>, +s: Sp) -> P(Tm):
  match m:
    case Some{+f}:
      P.if(Tm, F32.is_finite(f), P.pure(Tm, Ctr{"F32", [word_to_term(F32.bits(f), s)], s}),
        P.fail(Tm, "a float literal with a finite f32 value (got " ++ txt ++ ")"))
    case None{}:
      P.fail(Tm, "a float literal with a finite f32 value (got " ++ txt ++ ")")

def digits.span(s: String) -> Nat:
  match s:
    case SNil{}:
      0n
    case SCon{Chr{+c}, t}:
      Bool.pick(Nat, is_digit(c), 1n+digits.span(t), 0n)

def flt.exp(+s: String) -> String:
  +e = Str.first(s)
  +sign = Bool.or(U32.is_eq(Str.second(s), 43), U32.is_eq(Str.second(s), 45))
  +ed = digits.span(String.drop(s, Bool.pick(Nat, sign, 2n, 1n)))
  Bool.pick(String, Bool.and(Bool.or(U32.is_eq(e, 101), U32.is_eq(e, 69)), Nat.is_gt(ed, 0n)),
    String.take(s, Nat.add(ed, Bool.pick(Nat, sign, 2n, 1n))), "")

# The fraction and exponent of a float literal.
def flt.text(+s: String) -> String:
  +fd = digits.span(String.drop(s, 1n))
  +rest = String.drop(s, 1n+fd)
  String.take(s, 1n+fd) ++ flt.exp(rest)

def P.flt(+beg: U32, +ds: String, +r: String) -> P(Tm):
  +txt = flt.text(r)
  do P<Tm>:
    P.steps(String.length(txt))
    s : Sp <- P.span(beg)
    P.flt.go(ds ++ txt, F32.read(ds ++ txt), s)

def P.nat.lit(+beg: U32, +n: Nat) -> P(Tm):
  do P<Tm>:
    +c : U32 <- P.peek()
    s : Sp <- P.span(beg)
    P.if(Tm, is_name(c), P.fail(Tm, "a nat literal (NUMBER n)"), P.pure(Tm, Lit{LNat{n}, s}))

def nat.succs(n: Nat, out: Tm, +s: Sp) -> Tm:
  match n:
    case 0n:
      out
    case 1n+m:
      nat.succs(m, Ctr{"Succ", [out], s}, s)

def nat.plus.big(+n: Nat, +out: Tm, +s: Sp) -> Tm:
  Bool.pick(Tm, Nat.is_gt(n, 256n),
    TApp{TApp{Ref{"Nat.add", s, False{}}, Lit{LNat{n}, s}, s}, out, s}, nat.succs(n, out, s))

def nat.plus(+n: Nat, out: Tm, +s: Sp) -> Tm:
  match out:
    case Lit{LNat{+v}, ls}:
      Bool.pick(Tm, Nat.is_le(Nat.add(n, v), 4294967295n), Lit{LNat{Nat.add(n, v)}, s},
        nat.plus.big(n, Lit{LNat{v}, ls}, s))
    case other:
      nat.plus.big(n, other, s)

@unsafe
def P.nat.plus(+beg: U32, +n: Nat) -> P(Tm):
  do P<Tm>:
    out : Tm <- P.term0()
    spn : Sp <- P.span(beg)
    return nat.plus(n, out, spn)

@unsafe
def P.nat.go(+beg: U32, +n: Nat) -> P(Tm):
  do P<Tm>:
    plus : Bool <- P.take("+")
    P.if(Tm, plus, P.nat.plus(beg, n), P.nat.lit(beg, n))

@unsafe
def P.nat(+beg: U32, +ds: String, +n: Nat) -> P(Tm):
  P.if(Tm, Nat.is_gt(n, 4294967295n), P.fail(Tm, "a nat literal up to 4294967295n (got " ++ ds ++ "n)"),
    P.nat.go(beg, n))

def digits.val(s: String, n: Nat, +acc: Nat) -> Nat:
  match s n:
    case SCon{Chr{+c}, t} 1n+m:
      digits.val(t, m, Nat.add(Nat.mul(acc, 10n), U32.to_nat((c - 48 : U32))))
    case r k:
      acc

@unsafe
def P.num.go(+beg: U32, +ds: String, +r: String, kind: Nat) -> P(Tm):
  match kind:
    case 0n:
      +v = digits.val(ds, String.length(ds), 0n)
      do P<Tm>:
        +c : U32 <- P.peek()
        s : Sp <- P.span(beg)
        P.if(Tm, is_name(c), P.fail(Tm, "a numeric literal (NUMBER is U32, NUMBER n is Nat)"),
          P.if(Tm, Nat.is_gt(v, 4294967295n), P.fail(Tm, "a u32 literal up to 4294967295 (got " ++ ds ++ ")"),
            P.pure(Tm, u32_to_term(U32.from_nat(v), s))))
    case 1n:
      do P<Tm>:
        P.bump()
        P.nat(beg, ds, digits.val(ds, String.length(ds), 0n))
    case 2n+p:
      P.flt(beg, ds, r)

# 0: a U32, 1: a Nat (n), 2: an F32 (.digits)
def num.kind(+r: String) -> Nat:
  Bool.pick(Nat, U32.is_eq(Str.first(r), 110), 1n,
    Bool.pick(Nat, Bool.and(U32.is_eq(Str.first(r), 46), is_digit(Str.second(r))), 2n, 0n))

@unsafe
def P.num():
  do P<Tm>:
    +beg : U32 <- P.pos()
    +r : String <- P.peek_rest()
    +nd : Nat <- P.pure(Nat, digits.span(r))
    +ds : String <- P.pure(String, String.take(r, nd))
    P.steps(nd)
    +r2 : String <- P.peek_rest()
    P.num.go(beg, ds, r2, num.kind(r2))

@unsafe
def P.call.tmpl.go(+h: Tm, +x: Nat, ts: List<&2, Tm>) -> P(List<&2, Tm>):
  do P<List<&2, Tm>>:
    P.bump()
    t : Tm <- P.term0()
    P.skip()
    comma : Bool <- P.take(",")
    P.skip()
    P.call.tmpl(h, x, List.append(&2, Tm, ts, [t]))

@unsafe
def P.call.tmpl.one(+h: Tm, +x: Nat, +ts: List<&2, Tm>) -> P(List<&2, Tm>):
  P.if(List<&2, Tm>, Nat.is_eq(List.length(&2, Tm, ts), x),
    P.fail(List<&2, Tm>, "a term (" ++ Tm.name(h) ++ " takes " ++ Nat.show(x) ++ " ~)"),
    P.call.tmpl.go(h, x, ts))

# The ~ arguments of a template call.
@unsafe
def P.call.tmpl(h, x, ts):
  do P<List<&2, Tm>>:
    tl : Bool <- P.at("~")
    P.if(List<&2, Tm>, Bool.and(Nat.is_gt(x, 0n), tl), P.call.tmpl.one(h, x, ts), P.pure(List<&2, Tm>, ts))

@unsafe
def P.lt.adt.go(+out: Tm, a: Tm, +s2: Sp, +lvl: U32) -> P(Tm):
  do P<Tm>:
    comma : Bool <- P.take(",")
    +k : String <- P.reso(Tm.name(out))
    rest : List<&2, Tm> <- P.args(">")
    xs : List<&2, Tm> <- P.fill(k, a <> rest, s2)
    P.ops(ADT{k, xs, s2, Nil{}}, lvl)

@unsafe
def P.lt.adt(+out: Tm, a: Tm, +s2: Sp, +lvl: U32) -> P(Tm):
  P.if(Tm, Bool.or(Tm.is_var(out), Tm.is_ref(out)), P.lt.adt.go(out, a, s2, lvl),
    P.fail(Tm, "a family name before <..> (a comparison here needs parens)"))

# f<A, B> (a family instance), or a < comparison.
@unsafe
def P.lt(out, lvl):
  do P<Tm>:
    P.bump()
    +pos : U32 <- P.pos()
    +t2 : Sp <- P.span((pos - 1 : U32))
    +a : Tm <- P.term(5)
    P.skip()
    +s2 : Sp <- span.grow(out)
    gt : Bool <- P.at(">")
    comma : Bool <- P.at(",")
    P.if(Tm, Bool.or(gt, comma), P.lt.adt(out, a, s2, lvl),
      P.ops(TApp{TApp{Ref{".is_lt", t2, False{}}, out, s2}, a, s2}, lvl))

@unsafe
def P.ns.args(xs: List<&2, Tm>, +ty: Tm) -> P(List<&2, Tm>):
  match xs:
    case Nil{}:
      P.pure(List<&2, Tm>, Nil{})
    case x <> t:
      do P<List<&2, Tm>>:
        y : Tm <- P.ns(x, ty)
        ys : List<&2, Tm> <- P.ns.args(t, ty)
        return y <> ys

# Rebuilds an application; the spans are not needed after parsing.
def apps.span(f: Tm, ys: List<&2, Tm>, xs: List<&2, Tm>) -> Tm:
  apps(f, ys, NoSp{})

@unsafe
def P.ns.op.go(+k: String, hk: String, +s: Sp, b: Bool, +xs: List<&2, Tm>, +ty: Tm) -> P(Tm):
  do P<Tm>:
    q : String <- P.reso(hk ++ k)
    ys : List<&2, Tm> <- P.ns.args(xs, ty)
    return apps.span(Ref{q, s, b}, ys, xs)

@unsafe
def P.ns.op(+k: String, +s: Sp, b: Bool, xs: List<&2, Tm>, +ty: Tm, h: Tm) -> P(Tm):
  match h:
    case Var{hk, i, hs}:
      P.ns.op.go(k ++ "", hk, s, b, xs, ty)
    case VRf{hk, i, hs, r}:
      P.ns.op.go(k, hk, s, b, xs, ty)
    case Ref{hk, hs, hb}:
      P.ns.op.go(k, hk, s, b, xs, ty)
    case ADT{hk, hxs, hs, r}:
      P.ns.op.go(k, hk, s, b, xs, ty)
    case other:
      P.throw(Tm, err0("a type name after : (the operators' namespace)", MNone{}, Tm.span(other)))

def term_head(t: Tm) -> Tm:
  Pair.fst(Tm, List<&2, Tm>, term_unapply(t))

@unsafe
def P.ns.ref(+k: String, +s: Sp, b: Bool, +xs: List<&2, Tm>, +ty: Tm, op: Bool, logic: Bool) -> P(Tm):
  match op logic:
    case True{} l:
      P.ns.op(k, s, b, xs, ty, term_head(ty))
    case False{} True{}:
      do P<Tm>:
        ys : List<&2, Tm> <- P.ns.args(xs, ty)
        return apps.span(Ref{k, s, b}, ys, xs)
    case False{} False{}:
      P.pure(Tm, apps(Ref{k, s, b}, xs, NoSp{}))

@unsafe
def P.ns.app(r: Tm & List<&2, Tm>, ty: Tm) -> P(Tm):
  (f, xs) = r
  match f:
    case Ref{+k, +s, b}:
      P.ns.ref(k, s, b, xs, ty, Nat.is_eq(Str.last_dot(k), 0n),
        Str.has(["Bool.and", "Bool.or", "String.append"], k))
    case other:
      P.pure(Tm, apps(other, xs, NoSp{}))

# Operators without a type (".add") take the namespace of the ': T' that
# annotates them: (a + b : U32) calls U32.add.
@unsafe
def P.ns(tm, ty):
  match tm:
    case Let{ks, +ids, vs, f, s, qs}:
      do P<Tm>:
        b : Tm <- P.ns(syn_body(f), ty)
        return Let{ks, ids, vs, CLet{Nil{}, ids, b}, s, qs}
    case other:
      P.ns.app(term_unapply(other), ty)

@unsafe
def P.args.one(+close: String) -> P(List<&2, Tm>):
  do P<List<&2, Tm>>:
    x : Tm <- P.term0()
    P.skip()
    comma : Bool <- P.take(",")
    xs : List<&2, Tm> <- P.args(close)
    return x <> xs

@unsafe
def P.args(close):
  do P<List<&2, Tm>>:
    P.skip()
    done : Bool <- P.take(close)
    P.if(List<&2, Tm>, done, P.pure(List<&2, Tm>, Nil{}), P.args.one(close))

def List.init_tm(xs: List<&2, Tm>) -> List<&2, Tm>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> Nil{}:
      Nil{}
    case h <> t:
      h <> List.init_tm(t)

def List.last_tm(xs: List<&2, Tm>) -> List<&2, Tm>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> Nil{}:
      [h]
    case h <> t:
      List.last_tm(t)

def do.call(+book: Book, +ps: PS, +m: String, +op: String, +ts: List<&2, Tm>, xs: List<&2, Tm>,
  ys: List<&2, Tm>, +s: Sp
) -> Tm:
  apps(Ref{PS.reso(ps, m ++ op), s, False{}}, List.append(&2, Tm, List.append(&2, Tm, List.append(&2, Tm,
    List.init_tm(ts), xs), List.last_tm(ts)), ys), s)

def P.docall(+m: String, +op: String, +ts: List<&2, Tm>, xs: List<&2, Tm>, ys: List<&2, Tm>, +s: Sp) ->
  P(Tm):
  +ps => Done{(do.call(PS.book(ps), ps, m, op, ts, xs, ys, s), ps)}

@unsafe
def P.do_ret(+m: String, +ts: List<&2, Tm>, +beg: U32) -> P(Tm):
  do P<Tm>:
    e : Tm <- P.term0()
    s : Sp <- P.span(beg)
    P.docall(m, ".pure", ts, Nil{}, [e], s)

def Tld.is_adt(t: Maybe<&2, Tld>) -> Bool:
  match t:
    case Some{TADT{n, g, ty, cs, tbase}}:
      True{}
    case other:
      False{}

# The last statement of a block: its value, annotated with the block's type.
def P.do_last(+m: String, +ts: List<&2, Tm>, +t: Tm) -> P(Tm):
  do P<Tm>:
    +k : String <- P.reso(m)
    b : Book <- P.book()
    c : Tm <- P.docall(m, "", ts, Nil{}, Nil{}, Tm.span(t))
    return Ann{t, Bool.pick(Tm, Tld.is_adt(book_tld(b, k)), ADT{k, ts, Tm.span(t), Nil{}}, c), Tm.span(t)}

def Pt.k(p: Pt) -> String:
  match p:
    case PVar{k, i, q, s}:
      k
    case PCtr{k, xs, s}:
      k

def Pt.i(p: Pt) -> U32:
  match p:
    case PVar{k, i, q, s}:
      i
    case PCtr{k, xs, s}:
      0

def Pt.q(p: Pt) -> Q:
  match p:
    case PVar{k, i, q, s}:
      q
    case PCtr{k, xs, s}:
      QLone{}

def do.let(+x: Pt, v: Tm, f: Tm, s: Sp) -> Tm:
  Let{[Pt.k(x)], [Pt.i(x)], [v], CLet{Nil{}, [Pt.i(x)], f}, s, [Pt.q(x)]}

def do.lam(+x: Pt, f: Tm, s: Sp) -> Tm:
  Lam{Pt.k(x), Pt.i(x), CSyn{Nil{}, Pt.i(x), f}, s, Pt.q(x)}

@unsafe
def P.do_bind(
  +m: String, +ts: List<&2, Tm>, +col: U32, +beg: U32, +t: Tm, +a: Tm, typed: Bool, asg: Bool, step: Bool
) -> P(Tm):
  do P<Tm>:
    +v : Tm <- P.if(Tm, step, P.pure(Tm, t), P.term0())
    P.skip()
    semi : Bool <- P.take(";")
    +s : Sp <- P.span(beg)
    +n0 : Nat <- P.stn()
    +x : Pt <- P.binder(Bool.pick(Tm, typed, t, Var{"_", 0, NoSp{}}))
    +f : Tm <- P.do_stmt(m, ts, col)
    P.close(n0)
    P.if(Tm, asg, P.pure(Tm, do.let(x, Ann{v, a, s}, f, s)), P.docall(m, ".bind", ts, [a], [v, do.lam(x, f, s)], s))

@unsafe
def P.do_arrow(+m: String, +ts: List<&2, Tm>, +col: U32, +beg: U32, +t: Tm, +a: Tm) -> P(Tm):
  do P<Tm>:
    arr : Bool <- P.take("<-")
    P.if(Tm, arr, P.do_bind(m, ts, col, beg, t, a, False{}, False{}, False{}), P.do_last(m, ts, t))

@unsafe
def P.do_step.go(
  +m: String, +ts: List<&2, Tm>, +col: U32, +beg: U32, +t: Tm, +a: Tm, typed: Bool, step: Bool, +asg: Bool
) -> P(Tm):
  match typed:
    case True{}:
      do P<Tm>:
        P.if(Unit, asg, P.pure(Unit, Unit{}), P.eat("<-"))
        P.do_bind(m, ts, col, beg, t, a, True{}, asg, False{})
    case False{}:
      P.if(Tm, step, P.do_bind(m, ts, col, beg, t, a, False{}, False{}, True{}), P.do_arrow(m, ts, col, beg, t, a))

@unsafe
def P.do_step(+m: String, +ts: List<&2, Tm>, +col: U32, +beg: U32) -> P(Tm):
  do P<Tm>:
    +t : Tm <- P.term0()
    P.skip()
    +typed : Bool <- P.if(Bool, Tm.is_var(t), P.take(":"), P.pure(Bool, False{}))
    +step : Bool <- P.if(Bool, typed, P.pure(Bool, False{}), P.more(col))
    +a : Tm <- P.if(Tm, typed, P.term(1), P.if(Tm, step, P.var("Unit", Tm.span(t)), P.pure(Tm, t)))
    P.skip()
    eqeq : Bool <- P.at("==")
    asg : Bool <- P.if(Bool, Bool.and(typed, Bool.not(eqeq)), P.take("="), P.pure(Bool, False{}))
    P.do_step.go(m, ts, col, beg, t, a, typed, step, asg)

# The rest of a do block, from column col.
@unsafe
def P.do_stmt(m, ts, col):
  do P<Tm>:
    P.skip()
    +beg : U32 <- P.pos()
    ret : Bool <- P.word("return")
    P.if(Tm, ret, P.do_ret(m, ts, beg), P.do_step(m, ts, col, beg))

@unsafe
def P.row(col, ccol, n, rcol):
  do P<List<&2, Body>>:
    w : Bool <- P.word("case")
    +qs : List<&2, Tm> <- P.terms()
    P.if(Unit, Nat.is_eq(List.length(&2, Tm, qs), n), P.pure(Unit, Unit{}),
      P.fail(Unit, Nat.show(n) ++ " patterns (one per scrutinee)"))
    +n0 : Nat <- P.stn()
    ps : List<&2, Pt> <- P.patts(qs)
    f : Body <- P.body(rcol)
    P.close(n0)
    rest : List<&2, Body> <- P.rows(col, ccol, n)
    return Row{ps, f} <> rest

@unsafe
def P.local.names.more(+q: Q, ts: List<&2, Tm>) -> P(List<&2, Tm>):
  do P<List<&2, Tm>>:
    t : Tm <- P.term0()
    P.skip()
    P.local.names(q, List.append(&2, Tm, ts, [t]))

# More names of a parallel let: a b c = ...
@unsafe
def P.local.names(q, ts):
  do P<List<&2, Tm>>:
    nl : Bool <- P.nl()
    +c : U32 <- P.peek()
    r : String <- P.peek_rest()
    +more : Bool <- P.pure(Bool, Bool.and(Bool.and(Bool.not(nl), Bool.or(is_head(c),
      Bool.and(Q.is_lone(q), U32.is_eq(c, 43)))), Bool.not(Str.has(KEYWORDS(), Str.word_at(r)))))
    P.if(List<&2, Tm>, more, P.local.names.more(q, ts), P.pure(List<&2, Tm>, ts))

@unsafe
def P.terms.more(x: Tm) -> P(List<&2, Tm>):
  do P<List<&2, Tm>>:
    comma : Bool <- P.take(",")
    xs : List<&2, Tm> <- P.terms()
    return x <> xs

@unsafe
def P.terms():
  do P<List<&2, Tm>>:
    +x : Tm <- P.term0()
    P.skip()
    colon : Bool <- P.take(":")
    P.if(List<&2, Tm>, colon, P.pure(List<&2, Tm>, [x]), P.terms.more(x))

def Pt.s(p: Pt) -> Sp:
  match p:
    case PVar{k, i, q, s}:
      s
    case PCtr{k, xs, s}:
      s

# Peels the lambdas flatten put around the let's names.
def P.flatten.strip(ws: List<&2, Pt>, g: Tm) -> P(Tm):
  match ws g:
    case Nil{} t:
      P.pure(Tm, t)
    case w <> wt Lam{k, i, f, s, q}:
      P.flatten.strip(wt, syn_body(f))
    case w <> wt t:
      P.throw(Tm, err0("a parameter or field scrutinee (a match cannot scrutinize a local binder: give it its own def)",
        MNone{}, Pt.s(w)))

def flatten.lams(vars: List<&2, Pt>, x: Tm) -> Tm:
  match vars:
    case Nil{}:
      x
    case PVar{+k, +i, q, s} <> t:
      Lam{k, i, CSyn{Nil{}, i, flatten.lams(t, x)}, s, q}
    case p <> t:
      flatten.lams(t, x)

def Pt.ks(ps: List<&2, Pt>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> t:
      Pt.k(p) <> Pt.ks(t)

def Pt.is(ps: List<&2, Pt>) -> List<&2, U32>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> t:
      Pt.i(p) <> Pt.is(t)

def quant_dem(q: Q, qt: Q) -> Q:
  match q:
    case QNone{}:
      QNone{}
    case other:
      qt

def Pt.qs(ps: List<&2, Pt>, +q: Q) -> List<&2, Q>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> t:
      quant_dem(q, Pt.q(p)) <> Pt.qs(t, q)

@unsafe
def P.flatten.let(+ws: List<&2, Pt>, +q: Q, vs: List<&2, Tm>, f: Body, vars: List<&2, Pt>) -> P(Tm):
  do P<Tm>:
    g : Tm <- P.flatten(f, ws)
    body : Tm <- P.flatten.strip(ws, g)
    P.pure(Tm, flatten.lams(vars, Let{Pt.ks(ws), Pt.is(ws), vs, CLet{Nil{}, Pt.is(ws), body},
      Pt.s(Lst.head(Pt, PVar{"_", 0, QLone{}, NoSp{}}, ws)), Pt.qs(ws, q)}))

def Sp.or(a: Sp, b: Sp) -> Sp:
  match a:
    case NoSp{}:
      b
    case other:
      other

def P.mf.bad(e: Tm, +s: Sp) -> P(Tm):
  match e:
    case Var{k, i, es}:
      P.throw(Tm, err0("a match on a parameter or field (this name is a def or a consumed binder: give the value its own def)",
        MNone{}, es))
    case VRf{k, i, es, r}:
      P.throw(Tm, err0("a match on a parameter or field (this name is a def or a consumed binder: give the value its own def)",
        MNone{}, es))
    case Ctr{k, xs, es}:
      P.throw(Tm, err0("an undestructed scrutinee (this value is already a constructor: bind its fields directly; if an outer match destructed it, fold the pattern into the outer case)",
        MNone{}, s))
    case Lit{v, es}:
      P.throw(Tm, err0("an undestructed scrutinee (this value is already a constructor: bind its fields directly; if an outer match destructed it, fold the pattern into the outer case)",
        MNone{}, s))
    case other:
      P.throw(Tm, err0("a parameter or field scrutinee (a match cannot scrutinize a computed value: give it its own def)",
        MNone{}, Sp.or(Tm.span(other), s)))

law P.mf.col:
  for +e: Tm
  for et: List<&2, Tm>
  for +rows: List<&2, Body>
  for +s: Sp
  for +x: Pt
  for xt: List<&2, Pt>
  for v: Maybe<&2, Pt>
  P(Tm)

def Tm.var_i(t: Tm) -> Maybe<&2, U32>:
  match t:
    case Var{k, i, s}:
      Some{i}
    case other:
      None{}

def Tm.strip_subs(t: Tm) -> Tm:
  match t:
    case Sub{i, p, f, s}:
      Tm.strip_subs(f)
    case other:
      other

law vars.find:
  for vars: List<&2, Pt>
  for +i: U32
  Maybe<&2, Pt>

@unsafe
def P.mf.vars(+e: Tm, et: List<&2, Tm>, rows: List<&2, Body>, +s: Sp, vars: List<&2, Pt>) -> P(Tm):
  match vars:
    case Nil{}:
      P.mf.bad(Tm.strip_subs(e), s)
    case +x <> +xt:
      P.mf.col(e, et, rows, s, x, xt, vars.find(x <> xt, Maybe.default(&2, U32, Tm.var_i(e), 4294967295)))

@unsafe
def P.match_flatten(es: List<&2, Tm>, rows: List<&2, Body>, +s: Sp, vars: List<&2, Pt>) -> P(Tm):
  match es rows:
    case Nil{} Row{ps, f} <> t:
      P.flatten(f, vars)
    case Nil{} other <> t:
      P.flatten(other, vars)
    case Nil{} Nil{}:
      P.throw(Tm, err0("a case (this match has no row to return)", MNone{}, s))
    case e <> et rs:
      P.mf.vars(e, et, rs, s, vars)

@unsafe
def P.flatten.local(ks: List<&2, Pt>, q: Q, +vs: List<&2, Tm>, f: Body, vars: List<&2, Pt>) -> P(Tm):
  match ks:
    case PCtr{k, xs, s} <> Nil{}:
      P.match_flatten(vs, [Row{[PCtr{k, xs, s}], f}], Tm.span(Lst.head(Tm, Efq{NoSp{}}, vs)), vars)
    case other:
      P.flatten.let(other, q, vs, f, vars)

@unsafe
def P.flatten(b, vars):
  match b:
    case BReply{x, s}:
      P.pure(Tm, flatten.lams(vars, x))
    case BLocal{ks, q, vs, f}:
      P.flatten.local(ks, q, vs, f, vars)
    case BMatch{es, rows, s}:
      P.match_flatten(es, rows, s, vars)
    case Row{ps, f}:
      P.flatten(f, vars)

# The scrutinee is not the next parameter: that parameter becomes a lambda.
@unsafe
def P.mf.skip(+e: Tm, et: List<&2, Tm>, rows: List<&2, Body>, +s: Sp, x: Pt, xt: List<&2, Pt>) -> P(Tm):
  do P<Tm>:
    t : Tm <- P.match_flatten(e <> et, rows, s, xt)
    return flatten.lams([x], t)

law body_sub:
  for b: Body
  for +i: U32
  for +v: Pt
  Body

@unsafe
def P.mf.varrows(rows: List<&2, Body>, +w: Pt) -> P(List<&2, Body>):
  match rows:
    case Nil{}:
      P.pure(List<&2, Body>, Nil{})
    case Row{PVar{k, i, q, ps} <> rest, f} <> t:
      do P<List<&2, Body>>:
        rs : List<&2, Body> <- P.mf.varrows(t, w)
        return Row{rest, body_sub(f, i, w)} <> rs
    case Row{p <> rest, f} <> t:
      P.throw(List<&2, Body>, err0("a variable pattern (this column has no constructor row)", MNone{}, Pt.s(p)))
    case r <> t:
      P.mf.varrows(t, w)

def quant_join(a: Q, b: Q) -> Q:
  match a b:
    case QMany{} y:
      QMany{}
    case x QMany{}:
      QMany{}
    case QNone{} y:
      y
    case x y:
      x

#
# A body becomes a term: lets become Let, and a match on the parameters
# becomes a tree of Mat eliminators (the official match_flatten).
@unsafe
def patt_mark(+q: Q, rows: List<&2, Body>) -> Q:
  match rows:
    case Nil{}:
      q
    case Row{PVar{k, i, pq, s} <> rest, f} <> t:
      patt_mark(quant_join(q, pq), t)
    case r <> t:
      patt_mark(q, t)

def Pt.var_q(p: Pt) -> Q:
  match p:
    case PVar{k, i, q, s}:
      q
    case other:
      QLone{}

def Pt.with_q(p: Pt, q: Q) -> Pt:
  match p:
    case PVar{k, i, pq, s}:
      PVar{k, i, q, s}
    case other:
      other

def Pt.same(+a: Pt, +b: Pt) -> Bool:
  U32.is_eq(Pt.i(a), Pt.i(b))

def vars.replace(vars: List<&2, Pt>, +w: Pt) -> List<&2, Pt>:
  match vars:
    case Nil{}:
      Nil{}
    case +p <> t:
      Bool.pick(Pt, Pt.same(p, w), w, p) <> vars.replace(t, w)

# A column of variable patterns: each row's variable becomes the scrutinee.
@unsafe
def P.mf.varcol(
  +e: Tm, et: List<&2, Tm>, +rows: List<&2, Body>, +s: Sp, +x: Pt, xt: List<&2, Pt>, +v: Pt
) -> P(Tm):
  +w = Pt.with_q(v, patt_mark(Pt.var_q(v), rows))
  do P<Tm>:
    rs : List<&2, Body> <- P.mf.varrows(rows, w)
    P.match_flatten(et, rs, s, vars.replace(x <> xt, w))

# Fresh variables for the fields of the constructor column.
def P.mf.fields(ps: List<&2, Pt>, +xq: Q) -> P(List<&2, Pt>):
  match ps:
    case Nil{}:
      P.pure(List<&2, Pt>, Nil{})
    case PVar{k, i, q, s} <> t:
      do P<List<&2, Pt>>:
        rest : List<&2, Pt> <- P.mf.fields(t, xq)
        return PVar{k, i, quant_join(q, xq), s} <> rest
    case p <> t:
      do P<List<&2, Pt>>:
        +i : U32 <- P.fresh_id()
        rest : List<&2, Pt> <- P.mf.fields(t, xq)
        return PVar{"_" ++ U32.show(i), i, xq, Pt.s(p)} <> rest

law patt_term:
  for p: Pt
  for +s: Sp
  Tm

@unsafe
def patt_terms(ps: List<&2, Pt>, +s: Sp) -> List<&2, Tm>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> t:
      patt_term(p, s) <> patt_terms(t, s)

@unsafe
def mf.rows.ctr(
  k: String, pxs: List<&2, Pt>, rest: List<&2, Pt>, f: Body, +ck: String, +x: Pt, +kx: Pt, +xs: List<&2, Pt>,
  hit: Bool, tail: List<&2, Body>
) -> List<&2, Body>:
  match hit:
    case True{}:
      Row{List.append(&2, Pt, pxs, rest), body_sub(f, Pt.i(x), kx)} <> tail
    case False{}:
      tail

# The rows that fit constructor ck, specialized to its fields.
@unsafe
def mf.rows(rows: List<&2, Body>, +ck: String, +x: Pt, +kx: Pt, +xs: List<&2, Pt>) -> List<&2, Body>:
  match rows:
    case Nil{}:
      Nil{}
    case Row{PCtr{+k, pxs, s} <> rest, f} <> t:
      mf.rows.ctr(k, pxs, rest, f, ck, x, kx, xs, String.eq(k, ck), mf.rows(t, ck, x, kx, xs))
    case Row{PVar{k, +i, q, s} <> rest, f} <> t:
      Row{List.append(&2, Pt, xs, rest), body_sub(body_sub(f, i, x), Pt.i(x), kx)} <> mf.rows(t, ck, x, kx, xs)
    case r <> t:
      mf.rows(t, ck, x, kx, xs)

def mf.others.if(r: Body, rest: List<&2, Body>, drop: Bool) -> List<&2, Body>:
  match drop:
    case True{}:
      rest
    case False{}:
      r <> rest

def mf.others(rows: List<&2, Body>, +ck: String) -> List<&2, Body>:
  match rows:
    case Nil{}:
      Nil{}
    case Row{PCtr{+k, pxs, s} <> rest, f} <> t:
      mf.others.if(Row{PCtr{k, pxs, s} <> rest, f}, mf.others(t, ck), String.eq(k, ck))
    case r <> t:
      r <> mf.others(t, ck)

@unsafe
def P.mf.ctr(
  +e: Tm, +et: List<&2, Tm>, +rows: List<&2, Body>, +s: Sp, +x: Pt, +xt: List<&2, Pt>, c: Maybe<&2, Pt>
) -> P(Tm):
  match c:
    case None{}:
      P.pure(Tm, Efq{s})
    case Some{PCtr{+ck, cxs, +cs}}:
      +xq = patt_mark(Pt.var_q(x), rows)
      do P<Tm>:
        +xs : List<&2, Pt> <- P.mf.fields(cxs, xq)
        +kx : Pt <- P.pure(Pt, PCtr{ck, xs, Pt.s(x)})
        ps : List<&2, Body> <- P.pure(List<&2, Body>, mf.rows(rows, ck, x, kx, xs))
        pt : Tm <- P.match_flatten(List.append(&2, Tm, patt_terms(xs, NoSp{}), et), ps, s,
          List.append(&2, Pt, xs, xt))
        dt : Tm <- P.match_flatten(e <> et, mf.others(rows, ck), s, x <> xt)
        return Mat{ck, pt, dt, cs}
    case Some{other}:
      P.pure(Tm, Efq{s})

@unsafe
def P.mf.col.var(
  +e: Tm, +et: List<&2, Tm>, +rows: List<&2, Body>, +s: Sp, +x: Pt, +xt: List<&2, Pt>, +w: Pt,
  c: Maybe<&2, Pt>, norows: Bool
) -> P(Tm):
  match c norows:
    case None{} False{}:
      P.mf.varcol(e, et, rows, s, x, xt, w)
    case m b:
      P.if(Tm, Pt.same(w, x), P.mf.ctr(e, et, rows, s, x, xt, m), P.mf.skip(e, et, rows, s, x, xt))

def rows.ctr(rows: List<&2, Body>) -> Maybe<&2, Pt>:
  match rows:
    case Nil{}:
      None{}
    case Row{PCtr{k, xs, s} <> t, f} <> rest:
      Some{PCtr{k, xs, s}}
    case r <> rest:
      rows.ctr(rest)

@unsafe
def P.mf.col(e, et, rows, s, x, xt, v):
  match v:
    case Some{+w}:
      P.mf.col.var(e, et, rows, s, x, xt, w, rows.ctr(rows), Nat.is_eq(List.length(&2, Body, rows), 0n))
    case None{}:
      P.mf.skip(e, et, rows, s, x, xt)

type TC is Data:
  TC{q: Q, k: String, i: U32, t: Tm, s: Sp}

law P.tele:
  for +close: String
  for +tele: List<&2, TC>
  for +tk: Nat
  P(List<&2, TC> & Nat)

def TC.k(c: TC) -> String:
  TC{q, k, i, t, s} = c
  k

def TC.names(tele: List<&2, TC>) -> List<&2, String>:
  match tele:
    case Nil{}:
      Nil{}
    case c <> t:
      TC.k(c) <> TC.names(t)

@unsafe
def P.tele.one(+close: String, +tele: List<&2, TC>, +tk: Nat) -> P(List<&2, TC> & Nat):
  +paren = String.eq(close, ")")
  +len = List.length(&2, TC, tele)
  do P<List<&2, TC> & Nat>:
    tl : Bool <- P.at("~")
    P.if(Unit, Bool.and(Bool.and(paren, tl), Nat.is_lt(tk, len)),
      P.fail(Unit, "a plain binder (only leading binders take ~)"), P.pure(Unit, Unit{}))
    +ct : Bool <- P.if(Bool, paren, P.take("~"), P.pure(Bool, False{}))
    +q : Q <- P.if(Q, ct, P.pure(Q, QNone{}), P.quant())
    +beg : U32 <- P.pos()
    +k : String <- P.name()
    P.if(Unit, Bool.and(Bool.not(paren), Str.has(TC.names(tele), k)),
      P.fail(Unit, "a fresh field name (duplicate declaration: " ++ k ++ ")"), P.pure(Unit, Unit{}))
    +s : Sp <- P.span(beg)
    P.skip()
    colon : Bool <- P.at(":")
    +bare : Bool <- P.pure(Bool, Bool.and(Q.is_lone(q), Bool.not(colon)))
    P.if(Unit, bare, P.pure(Unit, Unit{}), P.eat(":"))
    ty : Tm <- P.if(Tm, bare, P.pure(Tm, Qnt{s}), P.term0())
    +i : U32 <- P.open(k)
    P.skip()
    comma : Bool <- P.take(",")
    P.tele(close, List.append(&2, TC, tele, [TC{Bool.pick(Q, bare, QNone{}, q), k, i, ty, s}]),
      Bool.pick(Nat, ct, 1n+tk, tk))

# Parameters up to close: (x: A, -y: B, +z: C, ~f: F, a) or {x: A, ..}.
@unsafe
def P.tele(close, tele, tk):
  do P<List<&2, TC> & Nat>:
    P.skip()
    done : Bool <- P.take(close)
    P.if(List<&2, TC> & Nat, done, P.pure(List<&2, TC> & Nat, (tele, tk)), P.tele.one(close, tele, tk))

def P.fresh(+k: String) -> P(Unit):
  do P<Unit>:
    b : Book <- P.book()
    P.if(Unit, book_has(b, k), P.fail(Unit, "a fresh name (duplicate declaration: " ++ k ++ ")"),
      P.pure(Unit, Unit{}))

def ops.text(s: Sp, +k: String) -> String:
  match s:
    case Sp{src, +beg, +end}:
      String.take(String.drop(src, U32.to_nat(beg)), Nat.sub(U32.to_nat(end), U32.to_nat(beg)))
    case NoSp{}:
      k

def ops.err(r: Tm) -> Err:
  match r:
    case Ref{k, +s, b}:
      Err{book_nil(), Nil{}, MStr{"a type for this operator (write (a " ++ ops.text(s, k) ++ " b : Nat))"}, MNone{},
        s, "", "Note: we broke this after launch, sorry. Until 2.0.16 a bare operator meant Nat.\n" ++
        "That was a bug: operators demand annotation. Wrap the expression and it'll work again."}
    case other:
      err0("a type for this operator", MNone{}, NoSp{})

def P.check_ops.c(c: Maybe<&2, Tm>) -> P(Unit):
  match c:
    case None{}:
      P.pure(Unit, Unit{})
    case Some{r}:
      P.throw(Unit, ops.err(r))

law ops.bare:
  for t: Tm
  Maybe<&2, Tm>

# A bare operator (".add") names no type: the official checker rejects it.
@unsafe
def P.check_ops(t: Tm) -> P(Unit):
  P.check_ops.c(ops.bare(t))

def book_set(book: Book, k: String, t: Tld) -> Book:
  Book{tlds, ctrs, order, hols, open, tmps, tcnt} = book
  Book{Map.set(&2, Tld, tlds, k, t), ctrs, order, hols, open, tmps, tcnt}

def TC.vars(tele: List<&2, TC>) -> List<&2, Pt>:
  match tele:
    case Nil{}:
      Nil{}
    case TC{q, k, i, t, s} <> rest:
      PVar{k, i, QLone{}, s} <> TC.vars(rest)

def Tld.with_v(t: Maybe<&2, Tld>, v: Tm) -> Tld:
  match t:
    case Some{TDef{n, x, ty, old, u, b, imps}}:
      TDef{n, x, ty, Some{v}, u, b, imps}
    case other:
      TDef{0n, 0n, Qnt{NoSp{}}, Some{v}, False{}, False{}, None{}}

@unsafe
def P.def.value(+k: String, tele: List<&2, TC>) -> P(Unit):
  do P<Unit>:
    body : Body <- P.body(0)
    +flat : Tm <- P.flatten(body, TC.vars(tele))
    +b : Book <- P.book()
    P.check_ops(flat)
    P.set_book(book_set(b, k, Tld.with_v(book_tld(b, k),
      higher0(b, term_lower(b, higher0(b, flat), 0)))))

law P.imports:
  for +acc: List<&2, String>
  P(List<&2, String>)

def Tld.law_x(t: Maybe<&2, Tld>) -> Nat:
  match t:
    case Some{TDef{n, x, ty, v, u, b, imps}}:
      x
    case other:
      0n

def Tld.with_imps(t: Maybe<&2, Tld>, ims: List<&2, String>) -> Tld:
  match t:
    case Some{TDef{n, x, ty, v, u, b, old}}:
      TDef{n, x, ty, v, u, b, Some{ims}}
    case other:
      TDef{0n, 0n, Qnt{NoSp{}}, None{}, False{}, False{}, Some{ims}}

@unsafe
def P.def.foreign(+k: String) -> P(Unit):
  do P<Unit>:
    b : Book <- P.book()
    P.if(Unit, Nat.is_gt(Tld.law_x(book_tld(b, k)), 0n), P.fail(Unit, "a body (a template is not foreign)"),
      P.pure(Unit, Unit{}))
    ims : List<&2, String> <- P.imports(Nil{})
    +b2 : Book <- P.book()
    P.set_book(book_set(b2, k, Tld.with_imps(book_tld(b2, k), ims)))

def book_push(book: Book, k: String) -> Book:
  Book{tlds, ctrs, order, hols, open, tmps, tcnt} = book
  Book{tlds, ctrs, k <> order, hols, open, tmps, tcnt}

def P.def.body(+k: String, +n0: Nat, +tele: List<&2, TC>) -> P(Unit):
  do P<Unit>:
    P.eat(":")
    imp : Bool <- P.at_word("import")
    P.if(Unit, imp, P.def.foreign(k), P.def.value(k, tele))
    P.close(n0)
    b : Book <- P.book()
    P.set_book(book_push(b, k))

def TC.all_qnt(tele: List<&2, TC>) -> Bool:
  match tele:
    case Nil{}:
      True{}
    case TC{q, k, i, Qnt{s}, cs} <> t:
      TC.all_qnt(t)
    case c <> t:
      False{}

def Tld.law_fill(t: Maybe<&2, Tld>, n: Nat, u2: Bool) -> Tld:
  match t:
    case Some{TDef{n0, x, ty, v, u, b, imps}}:
      TDef{n, x, ty, v, Bool.or(u, u2), b, imps}
    case other:
      TDef{n, 0n, Qnt{NoSp{}}, None{}, u2, False{}, None{}}

# def f(x, y): fills the law f.
def P.def.fill(u: Bool, +k: String, +n0: Nat, +tele: List<&2, TC>) -> P(Unit):
  do P<Unit>:
    b : Book <- P.book()
    +lx : Nat <- P.pure(Nat, Tld.law_x(book_tld(b, k)))
    P.if(Unit, TC.all_qnt(tele), P.pure(Unit, Unit{}), P.fail(Unit, "a name"))
    P.if(Unit, Nat.is_lt(List.length(&2, TC, tele), lx),
      P.fail(Unit, "a name for each ~ clause of the law (" ++ Nat.show(lx) ++ ")"), P.pure(Unit, Unit{}))
    +b2 : Book <- P.book()
    P.set_book(book_set(b2, k, Tld.law_fill(book_tld(b2, k), List.length(&2, TC, tele), u)))
    P.def.body(k, n0, tele)

def tele_bind(tele: List<&2, TC>, end: Tm) -> Tm:
  match tele:
    case Nil{}:
      end
    case TC{q, k, +i, t, s} <> rest:
      All{q, k, i, t, CSyn{Nil{}, i, tele_bind(rest, end)}, s}

def P.def.new(u: Bool, +k: String, +n0: Nat, +tele: List<&2, TC>, tk: Nat) -> P(Unit):
  do P<Unit>:
    arrow : Bool <- P.take("->")
    P.if(Unit, arrow, P.pure(Unit, Unit{}), P.fail(Unit,
      "'->' (a def with no return type fills a law; no law named " ++ k ++ " is in scope)"))
    ret : Tm <- P.term0()
    +b : Book <- P.book()
    P.set_book(book_set(b, k, TDef{List.length(&2, TC, tele), tk, higher0(b, tele_bind(tele, ret)), None{}, u,
      False{}, None{}}))
    P.def.body(k, n0, tele)

def P.def.go(+u: Bool, +k: String, lw: Bool, +n0: Nat, r: List<&2, TC> & Nat) -> P(Unit):
  (tele, tk) = r
  +tel = tele
  P.if(Unit, lw, P.def.fill(u, k, n0, tel), P.def.new(u, k, n0, tel, tk))

# A lw that a def of the same name may fill.
def Tld.open_law(t: Maybe<&2, Tld>) -> Bool:
  match t:
    case Some{TDef{n, x, ty, None{}, u, False{}, None{}}}:
      True{}
    case other:
      False{}

def P.def(u: Bool) -> P(Unit):
  do P<Unit>:
    w : Bool <- P.word("def")
    +nm : String <- P.name()
    +q : String <- P.reso(nm)
    b : Book <- P.book()
    +lw : Bool <- P.pure(Bool, Tld.open_law(book_tld(b, q)))
    +k : String <- P.if(String, lw, P.pure(String, q), P.qual(nm))
    P.if(Unit, lw, P.pure(Unit, Unit{}), P.fresh(k))
    +n0 : Nat <- P.stn()
    P.eat("(")
    P.skip()
    tl : Bool <- P.at("~")
    P.if(Unit, Bool.and(lw, tl), P.fail(Unit, "a name"), P.pure(Unit, Unit{}))
    r : List<&2, TC> & Nat <- P.tele(")", Nil{}, 0n)
    P.skip()
    P.def.go(u, k, lw, n0, r)

def PS.dir(+ps: PS) -> String:
  PS{cur, stk, stn, frs, book, src, ns, +dir, al} = ps
  dir

def P.dir() -> P(String):
  +ps => Done{(PS.dir(ps), ps)}

law P.until_quote:
  for +acc: String
  P(String)

@unsafe
def P.import1(acc: List<&2, String>) -> P(List<&2, String>):
  do P<List<&2, String>>:
    P.eat("\"")
    +eff : String <- P.until_quote("")
    P.eat("\"")
    P.if(Unit, Bool.or(String.ends_with(eff, ".c"), String.ends_with(eff, ".js")), P.pure(Unit, Unit{}),
      P.fail(Unit, "a .c or .js path"))
    +dir : String <- P.dir()
    P.imports(List.append(&2, String, acc, [dir ++ eff]))

@unsafe
def P.imports(acc):
  do P<List<&2, String>>:
    w : Bool <- P.word("import")
    P.if(List<&2, String>, w, P.import1(acc), P.pure(List<&2, String>, acc))

@unsafe
def P.until_quote.more(+c: U32, acc: String) -> P(String):
  do P<String>:
    P.bump()
    P.until_quote(SCon{Chr{c}, acc})

@unsafe
def P.until_quote(acc):
  do P<String>:
    +c : U32 <- P.peek()
    P.if(String, Bool.or(U32.is_eq(c, 34), U32.is_zero(c)), P.pure(String, String.reverse(acc)),
      P.until_quote.more(c, acc))

law P.ctor:
  for +k: String
  for +params: List<&2, TC>
  for cs: List<&2, CtrD>
  P(List<&2, CtrD>)

@unsafe
def P.ctors(+k: String, +params: List<&2, TC>, +cs: List<&2, CtrD>) -> P(List<&2, CtrD>):
  do P<List<&2, CtrD>>:
    P.skip()
    +c : U32 <- P.peek()
    d : Bool <- P.at_word("def")
    t : Bool <- P.at_word("type")
    l : Bool <- P.at_word("law")
    P.if(List<&2, CtrD>, Bool.or(Bool.not(is_head(c)), Bool.or(d, Bool.or(t, l))), P.pure(List<&2, CtrD>, cs),
      P.ctor(k, params, cs))

# The index of the first parameter that is not a bare quantity.
def TC.first_typed(tele: List<&2, TC>) -> Nat:
  match tele:
    case Nil{}:
      0n
    case TC{q, k, i, Qnt{s}, cs} <> t:
      1n+TC.first_typed(t)
    case c <> t:
      0n

def P.type.go(+k: String, +n0: Nat, +params: List<&2, TC>) -> P(Unit):
  do P<Unit>:
    isw : Bool <- P.word("is")
    P.if(Unit, isw, P.pure(Unit, Unit{}), P.fail(Unit, "'is'"))
    kind : Tm <- P.term0()
    P.eat(":")
    +b : Book <- P.book()
    +tt : Tm <- P.pure(Tm, higher0(b, tele_bind(params, kind)))
    +n : Nat <- P.pure(Nat, List.length(&2, TC, params))
    +g : Nat <- P.pure(Nat, TC.first_typed(params))
    P.set_book(book_set(b, k, TADT{n, g, tt, Nil{}, False{}}))
    cs : List<&2, CtrD> <- P.ctors(k, params, Nil{})
    b2 : Book <- P.book()
    P.set_book(book_push(book_set(b2, k, TADT{n, g, tt, cs, False{}}), k))
    P.close(n0)

# type D<params> is K:
#   C{fields}
def P.type() -> P(Unit):
  do P<Unit>:
    w : Bool <- P.word("type")
    nm : String <- P.name()
    +k : String <- P.qual(nm)
    P.fresh(k)
    +n0 : Nat <- P.stn()
    P.skip()
    lt : Bool <- P.take("<")
    r : List<&2, TC> & Nat <- P.if(List<&2, TC> & Nat, lt, P.tele(">", Nil{}, 0n), P.pure(List<&2, TC> & Nat, (Nil{}, 0n)))
    P.type.go(k, n0, Pair.fst(List<&2, TC>, Nat, r))

def book_set_ctr(book: Book, k: String, c: CtrD) -> Book:
  Book{tlds, ctrs, order, hols, open, tmps, tcnt} = book
  Book{tlds, Map.set(&2, CtrD, ctrs, k, c), order, hols, open, tmps, tcnt}

def TC.params(tele: List<&2, TC>) -> List<&2, Tm>:
  match tele:
    case Nil{}:
      Nil{}
    case TC{q, k, i, t, s} <> rest:
      Var{k, i, NoSp{}} <> TC.params(rest)

@unsafe
def P.ctor(k, params, cs):
  do P<List<&2, CtrD>>:
    nm : String <- P.name()
    +c : String <- P.qual(nm)
    b : Book <- P.book()
    P.if(Unit, Maybe.is_some(&2, CtrD, book_ctr(b, c)),
      P.fail(Unit, "a fresh constructor name (duplicate declaration: " ++ c ++ ")"), P.pure(Unit, Unit{}))
    P.eat("{")
    +n1 : Nat <- P.stn()
    r : List<&2, TC> & Nat <- P.tele("}", Nil{}, 0n)
    +fs : List<&2, TC> <- P.pure(List<&2, TC>, Pair.fst(List<&2, TC>, Nat, r))
    +b2 : Book <- P.book()
    +ctr : CtrD <- P.pure(CtrD, CtrD{c, List.length(&2, TC, fs), higher0(b2, tele_bind(List.append(&2, TC, params, fs),
      ADT{k, TC.params(params), NoSp{}, Nil{}}))})
    P.close(n1)
    P.set_book(book_set_ctr(b2, c, ctr))
    P.ctors(k, params, List.append(&2, CtrD, cs, [ctr]))

# law f:
#   for x: A        (also for -x, for +x, for ~x, and "for y: B where P(y)")
#   exs z: C
#   T
type LC is Data:
  LC{all: Bool, q: Q, k: String, i: U32, a: Tm, s: Sp}

def LC.first_exs(cls: List<&2, LC>) -> Nat:
  match cls:
    case Nil{}:
      0n
    case LC{True{}, q, k, i, a, s} <> t:
      1n+LC.first_exs(t)
    case c <> t:
      0n

def LC.bind.one(all: Bool, q: Q, +k: String, +i: U32, a: Tm, +s: Sp, rest: Tm) -> Tm:
  match all:
    case True{}:
      All{q, k, i, a, CSyn{Nil{}, i, rest}, s}
    case False{}:
      TApp{TApp{Ref{"Exists", s, False{}}, a, s}, Lam{k, i, CSyn{Nil{}, i, rest}, s, QUnd{}}, s}

def LC.bind(cls: List<&2, LC>, end: Tm) -> Tm:
  match cls:
    case Nil{}:
      end
    case LC{all, q, k, +i, a, +s} <> t:
      LC.bind.one(all, q, k, i, a, s, LC.bind(t, end))

def P.law.fin(+k: String, r: List<&2, LC> & Nat, body: Tm, +b: Book) -> P(Unit):
  (cls, tc) = r
  +cl = cls
  P.set_book(book_push(book_set(b, k, TDef{LC.first_exs(cl), tc, higher0(b, LC.bind(cl, body)), None{}, False{},
    False{}, None{}}), k))

law P.clause:
  for +cls: List<&2, LC>
  for +tc: Nat
  for +all: Bool
  P(List<&2, LC> & Nat)

@unsafe
def P.clauses(+cls: List<&2, LC>, +tc: Nat) -> P(List<&2, LC> & Nat):
  do P<List<&2, LC> & Nat>:
    +f : Bool <- P.at_word("for")
    e : Bool <- P.at_word("exs")
    P.if(List<&2, LC> & Nat, Bool.or(f, e), P.clause(cls, tc, f), P.pure(List<&2, LC> & Nat, (cls, tc)))

def P.law() -> P(Unit):
  do P<Unit>:
    w : Bool <- P.word("law")
    nm : String <- P.name()
    +k : String <- P.qual(nm)
    P.fresh(k)
    P.eat(":")
    +n0 : Nat <- P.stn()
    r : List<&2, LC> & Nat <- P.clauses(Nil{}, 0n)
    body : Tm <- P.block()
    P.close(n0)
    b : Book <- P.book()
    P.law.fin(k, r, body, b)

def P.clause.where(+c: String, a0: Tm, +s: Sp) -> P(Tm):
  do P<Tm>:
    +beg2 : U32 <- P.pos()
    w : Bool <- P.word("where")
    ws : Sp <- P.span(beg2)
    +n1 : Nat <- P.stn()
    +i : U32 <- P.open(c)
    pw : Tm <- P.term0()
    P.close(n1)
    return TApp{TApp{Ref{"Exists", ws, False{}}, a0, s}, Lam{c, i, CSyn{Nil{}, i, pw}, s, QUnd{}}, s}

@unsafe
def P.clause(cls, tc, all):
  do P<List<&2, LC> & Nat>:
    w : Bool <- P.word(Bool.pick(String, all, "for", "exs"))
    P.skip()
    tl : Bool <- P.at("~")
    P.if(Unit, Bool.and(Bool.and(all, tl), Nat.is_lt(tc, List.length(&2, LC, cls))),
      P.fail(Unit, "a plain clause (only leading clauses take ~)"), P.pure(Unit, Unit{}))
    +ct : Bool <- P.if(Bool, all, P.take("~"), P.pure(Bool, False{}))
    q : Q <- P.if(Q, ct, P.pure(Q, QNone{}), P.if(Q, all, P.quant(), P.pure(Q, QLone{})))
    +beg : U32 <- P.pos()
    +c : String <- P.name()
    +s : Sp <- P.span(beg)
    P.eat(":")
    +a0 : Tm <- P.term0()
    wh : Bool <- P.at_word("where")
    a : Tm <- P.if(Tm, wh, P.clause.where(c, a0, s), P.pure(Tm, a0))
    +i : U32 <- P.open(c)
    P.clauses(List.append(&2, LC, cls, [LC{all, q, c, i, a, s}]), Bool.pick(Nat, ct, 1n+tc, tc))

def PS.set_scope(ps: PS, s: List<&2, SB>, n: Nat, f: U32) -> PS:
  PS{cur, stk, stn, frs, book, src, ns, dir, al} = ps
  PS{cur, s, n, f, book, src, ns, dir, al}

def P.reset_scope() -> P(Unit):
  ps => Done{(Unit{}, PS.set_scope(ps, Nil{}, 0n, 0))}

law P.decl:
  P(Unit)

# A whole file, declaration by declaration.
@unsafe
def P.decls() -> P(Unit):
  do P<Unit>:
    P.skip()
    +c : U32 <- P.peek()
    P.if(Unit, U32.is_zero(c), P.pure(Unit, Unit{}), P.decl())

def P.unsafe() -> P(Unit):
  do P<Unit>:
    w : Bool <- P.word("unsafe")
    P.if(Unit, w, P.pure(Unit, Unit{}), P.fail(Unit, "'unsafe' (the one decorator)"))
    P.skip()
    d : Bool <- P.at_word("def")
    P.if(Unit, d, P.def(True{}), P.fail(Unit, "'def' (@unsafe marks the def below it)"))

def P.decl.go(at: Bool, d: Bool, t: Bool, l: Bool) -> P(Unit):
  match at:
    case True{}:
      P.unsafe()
    case False{}:
      P.if(Unit, d, P.def(False{}), P.if(Unit, t, P.type(), P.if(Unit, l, P.law(),
        P.fail(Unit, "'def', 'type' or 'law'"))))

@unsafe
def P.decl():
  do P<Unit>:
    P.reset_scope()
    at : Bool <- P.take("@")
    d : Bool <- P.at_word("def")
    t : Bool <- P.at_word("type")
    l : Bool <- P.at_word("law")
    P.decl.go(at, d, t, l)
    P.decls()

# Misc
# ====

@unsafe
def vars.find.if(v: Pt, t: List<&2, Pt>, +i: U32, hit: Bool) -> Maybe<&2, Pt>:
  match hit:
    case True{}:
      Some{v}
    case False{}:
      vars.find(t, i)

@unsafe
def vars.find(vars, i):
  match vars:
    case Nil{}:
      None{}
    case PVar{+k, +j, +q, +s} <> t:
      vars.find.if(PVar{k, j, q, s}, t, i, U32.is_eq(i, j))
    case p <> t:
      vars.find(t, i)

type Us is Data:
  Us{i: U32, q: Q}

def Nat.to_u32(n: Nat) -> U32:
  U32.from_nat(n)

def Q.eq(a: Q, b: Q) -> Bool:
  match a b:
    case QNone{} QNone{}:
      True{}
    case QLone{} QLone{}:
      True{}
    case QMany{} QMany{}:
      True{}
    case QUnd{} QUnd{}:
      True{}
    case x y:
      False{}

def Q.is_none(q: Q) -> Bool:
  match q:
    case QNone{}:
      True{}
    case other:
      False{}

def Q.is_many(q: Q) -> Bool:
  match q:
    case QMany{}:
      True{}
    case other:
      False{}

def quant_add(a: Q, b: Q) -> Q:
  match a b:
    case QNone{} y:
      y
    case x QNone{}:
      x
    case x y:
      QMany{}

law uses_get:
  for u: List<&2, Us>
  for +i: U32
  Q

@unsafe
def uses_get.if(q: Q, t: List<&2, Us>, +i: U32, hit: Bool) -> Q:
  match hit:
    case True{}:
      q
    case False{}:
      uses_get(t, i)

# Uses: how many times each variable (by depth) was consumed.
@unsafe
def uses_get(u, i):
  match u:
    case Nil{}:
      QNone{}
    case Us{+j, q} <> t:
      uses_get.if(q, t, i, U32.is_eq(i, j))

def uses_one(+i: U32, q: Q) -> List<&2, Us>:
  [Us{i, q}]

def Us.i(u: Us) -> U32:
  Us{i, q} = u
  i

def Us.q(u: Us) -> Q:
  Us{i, q} = u
  q

law uses_put:
  for +f: U32
  for +x: Us
  for a: List<&2, Us>
  List<&2, Us>

@unsafe
def uses_put.if(+f: U32, +x: Us, +j: U32, +q: Q, t: List<&2, Us>, same: Bool) -> List<&2, Us>:
  match same:
    case True{}:
      Us{j, Bool.pick(Q, U32.is_zero(f), quant_add(q, Us.q(x)), quant_join(q, Us.q(x)))} <> t
    case False{}:
      Us{j, q} <> uses_put(f, x, t)

# The uses of b merged into a, combining a variable's two entries with f
# (0: quant_add, 1: quant_join).
@unsafe
def uses_put(f, x, a):
  match a:
    case Nil{}:
      [x]
    case Us{+j, +q} <> t:
      uses_put.if(f, x, j, q, t, U32.is_eq(Us.i(x), j))

@unsafe
def uses_merge(+f: U32, a: List<&2, Us>, b: List<&2, Us>) -> List<&2, Us>:
  match b:
    case Nil{}:
      a
    case x <> t:
      uses_merge(f, uses_put(f, x, a), t)

def uses_add(a: List<&2, Us>, b: List<&2, Us>) -> List<&2, Us>:
  uses_merge(0, a, b)

# A variable used in only one branch keeps its use (quant_join).
def uses_join(a: List<&2, Us>, b: List<&2, Us>) -> List<&2, Us>:
  uses_merge(1, a, b)

def uses_del.if(x: Us, rest: List<&2, Us>, drop: Bool) -> List<&2, Us>:
  match drop:
    case True{}:
      rest
    case False{}:
      x <> rest

def uses_del(u: List<&2, Us>, +i: U32) -> List<&2, Us>:
  match u:
    case Nil{}:
      Nil{}
    case Us{+j, q} <> t:
      uses_del.if(Us{j, q}, uses_del(t, i), U32.is_eq(i, j))

law env_get:
  for env: List<&2, Tm>
  for +i: U32
  Maybe<&2, Tm>

@unsafe
def env_get.if(v: Tm, t: List<&2, Tm>, +i: U32, hit: Bool) -> Maybe<&2, Tm>:
  match hit:
    case True{}:
      Some{v}
    case False{}:
      env_get(t, i)

@unsafe
def env_get(env, i):
  match env:
    case Nil{}:
      None{}
    case EB{+j, v} <> t:
      env_get.if(v, t, i, U32.is_eq(i, j))
    case x <> t:
      env_get(t, i)

def env_set(env: List<&2, Tm>, i: U32, v: Tm) -> List<&2, Tm>:
  EB{i, v} <> env

@unsafe
def env_sets(env: List<&2, Tm>, ids: List<&2, U32>, vs: List<&2, Tm>) -> List<&2, Tm>:
  match ids vs:
    case i <> it v <> vt:
      env_sets(env_set(env, i, v), it, vt)
    case a b:
      env

def Map.find.leaf(-V: Data, v: V, hit: Bool) -> Maybe<&2, V>:
  match hit:
    case True{}:
      Some{v}
    case False{}:
      None{}

@unsafe
def Map.find.node(-V: Data, lo: Map<&2, V>, hi: Map<&2, V>, +k: String, bit: Bool) ->
  Maybe<&2, V>:
  match bit:
    case True{}:
      Map.find.go(V, hi, k)
    case False{}:
      Map.find.go(V, lo, k)

@unsafe
def Map.find.go(V, m, k):
  match m:
    case MTip{}:
      None{}
    case MLeaf{+key, v}:
      Map.find.leaf(V, v, String.eq(key, k))
    case MNode{+pos, lo, hi}:
      Map.find.node(V, lo, hi, k, Pair.snd(String, Bool, Map.bit(k, pos)))

def book_opened(book: Book) -> Book:
  Book{tlds, ctrs, order, hols, open, tmps, tcnt} = book
  Book{tlds, ctrs, order, hols, 1n+open, tmps, tcnt}

def book_order(+book: Book) -> List<&2, String>:
  Book{tlds, ctrs, +order, hols, open, tmps, tcnt} = book
  List.reverse(&2, String, order)

def Sp.is_none(s: Sp) -> Bool:
  match s:
    case NoSp{}:
      True{}
    case other:
      False{}

def lit_step(t: Tm) -> Tm:
  match t:
    case Lit{LNat{0n}, s}:
      Ctr{"Zero", Nil{}, s}
    case Lit{LNat{1n+p}, +s}:
      Ctr{"Succ", [Lit{LNat{p}, s}], s}
    case Lit{LStr{SNil{}}, s}:
      Ctr{"SNil", Nil{}, s}
    case Lit{LStr{SCon{Chr{c}, rest}}, +s}:
      Ctr{"SCon", [chr_term(c, s), Lit{LStr{rest}, s}], s}
    case other:
      other

def is_ctr(+t: Tm, +k: String, n: Nat) -> Bool:
  match t:
    case Ctr{+k2, +xs, s}:
      Bool.and(String.eq(k, k2), Nat.is_eq(List.length(&2, Tm, xs), n))
    case other:
      False{}

law term_strip:
  for t: Tm
  Tm

law u32_bits:
  for w: Tm
  for +i: U32
  for +n: U32
  Maybe<&2, U32>

@unsafe
def u32_from_term.if(w: Tm, ok: Bool) -> Maybe<&2, U32>:
  match ok:
    case True{}:
      u32_bits(term_strip(w), 0, 0)
    case False{}:
      None{}

def u32_from_term.go(t: Tm, +k: String) -> Maybe<&2, U32>:
  match t:
    case Ctr{+k2, w <> Nil{}, s}:
      u32_from_term.if(w, String.eq(k, k2))
    case other:
      None{}

# The number a U32 (or F32, when k is "F32") constructor holds.
@unsafe
def u32_from_term(t: Tm, +k: String) -> Maybe<&2, U32>:
  u32_from_term.go(term_strip(t), k)

@unsafe
def u32_bits.next(rest: Tm, +i: U32, +n: U32) -> Maybe<&2, U32>:
  Bool.pick(Maybe<&2, U32>, U32.is_ge(i, 32), None{}, u32_bits(term_strip(rest), U32.inc(i), n))

@unsafe
def u32_bits.bit(b: Tm, rest: Tm, +i: U32, +n: U32) -> Maybe<&2, U32>:
  match b:
    case Ctr{"True", Nil{}, s}:
      u32_bits.next(rest, i, (n .|. (1 << U32.to_nat(i) : U32) : U32))
    case Ctr{"False", Nil{}, s}:
      u32_bits.next(rest, i, n)
    case other:
      None{}

@unsafe
def u32_bits(w, i, n):
  match w:
    case Ctr{"WCon", b <> rest <> Nil{}, s}:
      u32_bits.bit(term_strip(b), rest, i, n)
    case Ctr{"WNil", Nil{}, s}:
      Bool.pick(Maybe<&2, U32>, U32.is_eq(i, 32), Some{n}, None{})
    case other:
      None{}

def term_force(t: Tm) -> Tm:
  match t:
    case Cel{k, s, v}:
      term_force(v)
    case VRf{k, i, s, r}:
      term_force(r)
    case other:
      other

@unsafe
def term_strip.go(t: Tm) -> Tm:
  match t:
    case Ann{x, ty, s}:
      term_strip(x)
    case other:
      other

@unsafe
def term_strip(t):
  term_strip.go(term_force(t))

def term_cell(+t: Tm, +k: String) -> Tm:
  match t:
    case Cel{k2, s, v}:
      Cel{k2, s, v}
    case other:
      Cel{k, Tm.span(other), other}

def term_cells(vs: List<&2, Tm>, ks: List<&2, String>) -> List<&2, Tm>:
  match vs ks:
    case v <> vt k <> kt:
      term_cell(v, k) <> term_cells(vt, kt)
    case v <> vt Nil{}:
      term_cell(v, "_") <> term_cells(vt, Nil{})
    case a b:
      Nil{}

def term_args(t: Tm) -> List<&2, Tm>:
  Pair.snd(Tm, List<&2, Tm>, term_unapply(t))

#
# term_wnf is the official stack machine. A frame is an argument (FApp), a
# match waiting for its scrutinee (FMat) or a quantity minimum (FMna, FMnb).
# lhs remembers the call a def's body came from (and how many parameters
# are still to be bound), so a match stuck on a variable gives back the
# call, not the unfolded body: `x => f(x, 2n)` stays as it is.
type LH is Data:
  LNo{}
  LH{t: Tm, n: Nat}

type Fr is Data:
  FApp{x: Tm, s: Sp}
  FMat{t: Tm, e: Tm, lhs: LH, s: Sp}
  FMna{b: Tm, s: Sp}
  FMnb{a: Tm, s: Sp}

law wnf.go:
  for +book: Book
  for tm: Tm
  for frs: List<&2, Fr>
  for lhs: LH
  Tm

@unsafe
def term_wnf(+book: Book, t: Tm) -> Tm:
  wnf.go(book, t, Nil{}, LNo{})

law snf.go:
  for +book: Book
  for tm: Tm
  Tm

@unsafe
def term_snf(+book: Book, term: Tm) -> Tm:
  snf.go(book, term_wnf(book, term))

law lhs_ext:
  for +book: Book
  for lhs: Tm
  for +k: String
  for n: Nat
  for xs: List<&2, Tm>
  Tm

law mat_goal:
  for +book: Book
  for tel: Tm
  for n: Nat
  for xs: List<&2, Tm>
  for tb: Tm
  for +ck: String
  for +cs: Sp
  for +tq: Q
  for ctx: List<&2, Tm>
  for dn: String
  Tm

# Applies a binder's body to its arguments.
@unsafe
def clo_apply(+book: Book, c: Tm, +xs: List<&2, Tm>) -> Tm:
  match c:
    case CSyn{env, i, b}:
      higher(book, b, env_set(env, i, Lst.head(Tm, Var{"_", 0, NoSp{}}, xs)))
    case CLet{env, ids, b}:
      higher(book, b, env_sets(env, ids, xs))
    case CSnf{c2}:
      term_snf(book, clo_apply(book, c2, xs))
    case CExt{lhs, k, 1n+n, ys}:
      lhs_ext(book, lhs, k, n, List.append(&2, Tm, ys, xs))
    case CGoal{cur, n, ys, tb, ck, cs, tq, ctx, dn}:
      mat_goal(book, clo_apply(book, cur, xs), n, List.append(&2, Tm, ys, xs), tb, ck, cs, tq, ctx, dn)
    case CRwt{a, ty, s}:
      All{QLone{}, "e", 0, Eql{a, Lst.head(Tm, Var{"_", 0, NoSp{}}, xs), ty, NoSp{}},
        CConst{Typ{TQua{QLone{}, NoSp{}}, NoSp{}}}, s}
    case CConst{t}:
      t
    case other:
      other

@unsafe
def term_apply.go(+book: Book, fn: Tm, x: Tm, s: Sp) -> Tm:
  match fn:
    case Lam{k, i, f, ls, q}:
      clo_apply(book, f, [x])
    case other:
      TApp{other, x, s}

@unsafe
def term_apply(+book: Book, fn: Tm, x: Tm, s: Sp) -> Tm:
  term_apply.go(book, term_strip(fn), x, s)

def term_apply1(+book: Book, fn: Tm, x: Tm) -> Tm:
  term_apply(book, fn, x, NoSp{})

@unsafe
def lhs_ext(book, lhs, k, n, xs):
  match n:
    case 0n:
      term_apply(book, lhs, Ctr{k, xs, NoSp{}}, NoSp{})
    case 1n+p:
      Lam{"_", 0, CExt{lhs, k, 1n+p, xs}, NoSp{}, QUnd{}}

@unsafe
def higher.val(+book: Book, v: Tm, s: Sp) -> Tm:
  match v:
    case EPat{p, env}:
      higher(book, patt_term(p, s), env)
    case Cel{k, cs, x}:
      Cel{k, cs, x}
    case other:
      Tm.respan(other, s)

@unsafe
def higher.var(+book: Book, m: Maybe<&2, Tm>, d: Tm, s: Sp) -> Tm:
  match m:
    case None{}:
      d
    case Some{v}:
      higher.val(book, v, s)

@unsafe
def higher.app(+book: Book, f: Tm, x: Tm, s: Sp) -> Tm:
  match f:
    case Lam{k, i, c, ls, q}:
      clo_apply(book, c, [x])
    case other:
      TApp{other, x, s}

@unsafe
def highers(+book: Book, xs: List<&2, Tm>, +env: List<&2, Tm>) -> List<&2, Tm>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> t:
      higher(book, h, env) <> highers(book, t, env)

@unsafe
def higher(book, tm, env):
  match tm:
    case Var{+k, +i, +s}:
      higher.var(book, env_get(env, i), Ref{k, s, False{}}, s)
    case VRf{k, +i, +s, r}:
      higher.var(book, env_get(env, i), r, s)
    case Sub{i, p, f, s}:
      higher(book, f, EB{i, EPat{p, env}} <> env)
    case Let{ks, +ids, vs, f, s, qs}:
      Let{ks, ids, highers(book, vs, env), CLet{env, ids, syn_body(f)}, s, qs}
    case All{q, k, +i, a, b, s}:
      All{q, k, i, higher(book, a, env), CSyn{env, i, syn_body(b)}, s}
    case Lam{k, +i, f, s, q}:
      Lam{k, i, CSyn{env, i, syn_body(f)}, s, q}
    case Typ{g, s}:
      Typ{higher(book, g, env), s}
    case Min{a, b, s}:
      Min{higher(book, a, env), higher(book, b, env), s}
    case TApp{f, x, s}:
      higher.app(book, higher(book, f, env), higher(book, x, env), s)
    case ADT{k, xs, s, r}:
      ADT{k, highers(book, xs, env), s, r}
    case Ctr{k, xs, s}:
      Ctr{k, highers(book, xs, env), s}
    case Mat{k, h, m, s}:
      Mat{k, higher(book, h, env), higher(book, m, env), s}
    case Eql{a, b, ty, s}:
      Eql{higher(book, a, env), higher(book, b, env), higher(book, ty, env), s}
    case Rwt{e, p, f, s}:
      Rwt{higher(book, e, env), higher(book, p, env), higher(book, f, env), s}
    case Ann{x, ty, s}:
      Ann{higher(book, x, env), higher(book, ty, env), s}
    case other:
      other

@unsafe
def patt_term(p, s):
  match p:
    case PVar{k, i, q, ps}:
      Var{k, i, Sp.or(s, ps)}
    case PCtr{k, xs, ps}:
      Ctr{k, patt_terms(xs, s), Sp.or(s, ps)}

law lowers:
  for +book: Book
  for xs: List<&2, Tm>
  for +d: U32
  List<&2, Tm>

# term_lower: back to syntax, binders numbered by depth.
@unsafe
def lowers(book, xs, d):
  match xs:
    case Nil{}:
      Nil{}
    case h <> t:
      term_lower(book, h, d) <> lowers(book, t, d)

def let_vars.fresh(ks: List<&2, String>, +d: U32) -> List<&2, Tm>:
  match ks:
    case Nil{}:
      Nil{}
    case k <> t:
      Var{k, d, NoSp{}} <> let_vars.fresh(t, U32.inc(d))

def let_ids(ks: List<&2, String>, +d: U32) -> List<&2, U32>:
  match ks:
    case Nil{}:
      Nil{}
    case k <> t:
      d <> let_ids(t, U32.inc(d))

@unsafe
def term_lower.go(+book: Book, term: Tm, +d: U32) -> Tm:
  match term:
    case Var{k, i, s}:
      Var{k, i, s}
    case Sub{i, p, f, s}:
      Sub{i, p, term_lower(book, f, d), s}
    case Let{+ks, ids, vs, f, s, qs}:
      +n = U32.from_nat(List.length(&2, String, ks))
      Let{ks, let_ids(ks, d), lowers(book, vs, d), CLet{Nil{}, Nil{},
        term_lower(book, clo_apply(book, f, let_vars.fresh(ks, d)), (d + n : U32))}, s, qs}
    case Typ{g, s}:
      Typ{term_lower(book, g, d), s}
    case Min{a, b, s}:
      Min{term_lower(book, a, d), term_lower(book, b, d), s}
    case All{q, +k, i, a, b, s}:
      All{q, k, d, term_lower(book, a, d), CSyn{Nil{}, d,
        term_lower(book, clo_apply(book, b, [Var{k, d, NoSp{}}]), U32.inc(d))}, s}
    case Lam{+k, i, f, s, q}:
      Lam{k, d, CSyn{Nil{}, d, term_lower(book, clo_apply(book, f, [Var{k, d, NoSp{}}]),
        U32.inc(d))}, s, q}
    case TApp{f, x, s}:
      TApp{term_lower(book, f, d), term_lower(book, x, d), s}
    case ADT{k, xs, s, r}:
      ADT{k, lowers(book, xs, d), s, r}
    case Ctr{k, xs, s}:
      Ctr{k, lowers(book, xs, d), s}
    case Mat{k, h, m, s}:
      Mat{k, term_lower(book, h, d), term_lower(book, m, d), s}
    case Eql{a, b, ty, s}:
      Eql{term_lower(book, a, d), term_lower(book, b, d), term_lower(book, ty, d), s}
    case Rwt{e, p, f, s}:
      Rwt{term_lower(book, e, d), term_lower(book, p, d), term_lower(book, f, d), s}
    case Ann{x, ty, s}:
      Ann{term_lower(book, x, d), term_lower(book, ty, d), s}
    case other:
      other

@unsafe
def term_lower(book, term, d):
  term_lower.go(book, term_force(term), d)

def tld_n(t: Tld) -> Nat:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      n
    case TADT{n, g, ty, cs, tbase}:
      n

# The number of argument frames on top, up to n.
def frs_apps(frs: List<&2, Fr>, n: Nat) -> Nat:
  match frs n:
    case fs 0n:
      0n
    case FApp{x, s} <> t 1n+m:
      1n+frs_apps(t, m)
    case fs k:
      0n

@unsafe
def lhs_step(+book: Book, lhs: LH, x: Tm, s: Sp) -> LH:
  match lhs:
    case LNo{}:
      LNo{}
    case LH{t, 0n}:
      LNo{}
    case LH{t, 1n+n}:
      LH{term_apply(book, t, x, s), n}

@unsafe
def lhs_mat(+book: Book, lhs: LH, +k: String, +len: Nat) -> LH:
  match lhs:
    case LNo{}:
      LNo{}
    case LH{t, n}:
      LH{lhs_ext(book, t, k, len, Nil{}), Nat.add(Nat.sub(n, 1n), len)}

def lhs_or(lhs: LH, t: Tm) -> Tm:
  match lhs:
    case LNo{}:
      t
    case LH{lt, n}:
      lt

def app_frames(xs: List<&2, Tm>, rest: List<&2, Fr>) -> List<&2, Fr>:
  match xs:
    case Nil{}:
      rest
    case x <> t:
      FApp{term_cell(x, "_"), NoSp{}} <> app_frames(t, rest)

law wnf.back:
  for +book: Book
  for tm: Tm
  for frs: List<&2, Fr>
  Tm

@unsafe
def wnf.lam(+book: Book, tm: Tm, frs: List<&2, Fr>, lhs: LH) -> Tm:
  match frs:
    case FApp{+x, +s} <> rest:
      wnf.go(book, term_apply(book, tm, x, s), rest, lhs_step(book, lhs, x, s))
    case other:
      wnf.back(book, tm, other)

@unsafe
def wnf.mat(+book: Book, tm: Tm, frs: List<&2, Fr>, lhs: LH) -> Tm:
  match frs:
    case FApp{+x, s} <> rest:
      wnf.go(book, x, FMat{tm, x, lhs, s} <> rest, LNo{})
    case other:
      wnf.back(book, tm, other)

@unsafe
def wnf.efq(+book: Book, tm: Tm, frs: List<&2, Fr>, lhs: LH) -> Tm:
  match frs lhs:
    case FApp{x, s} <> rest LH{t, 1n+n}:
      wnf.back(book, t, FApp{x, s} <> rest)
    case fs l:
      wnf.back(book, tm, fs)

@unsafe
def wnf.rwt(+book: Book, e: Tm, tm: Tm, f: Tm, frs: List<&2, Fr>, lhs: LH) -> Tm:
  match e:
    case Rfl{s}:
      wnf.go(book, f, frs, lhs)
    case other:
      wnf.back(book, tm, frs)

@unsafe
def wnf.ref.def(+book: Book, tm: Tm, v: Tm, n: Nat, frs: List<&2, Fr>, short: Bool) -> Tm:
  match short:
    case True{}:
      wnf.back(book, tm, frs)
    case False{}:
      wnf.go(book, v, frs, LH{tm, n})

def Tm.ref_k(t: Tm) -> String:
  match t:
    case Ref{k, s, b}:
      k
    case other:
      ""

@unsafe
def wnf.ref(+book: Book, tld: Maybe<&2, Tld>, +tm: Tm, +frs: List<&2, Fr>, lhs: LH) -> Tm:
  match tld:
    case Some{TADT{0n, g, ty, cs, tbase}}:
      wnf.back(book, ADT{Tm.ref_k(tm), Nil{}, Tm.span(tm), Nil{}}, frs)
    case Some{TDef{+n, x, ty, Some{v}, u, b, imps}}:
      wnf.ref.def(book, tm, v, n, frs, Nat.is_lt(frs_apps(frs, n), n))
    case other:
      wnf.back(book, tm, frs)

@unsafe
def wnf.go(book, tm, frs, lhs):
  match tm:
    case Cel{k, s, v}:
      wnf.go(book, v, frs, LNo{})
    case VRf{k, i, s, r}:
      wnf.go(book, r, frs, LNo{})
    case Ann{x, ty, s}:
      wnf.go(book, x, frs, lhs)
    case Min{a, b, s}:
      wnf.go(book, a, FMna{b, s} <> frs, lhs)
    case Let{ks, ids, vs, f, s, qs}:
      wnf.go(book, clo_apply(book, f, term_cells(vs, ks)), frs, lhs)
    case TApp{f, x, s}:
      wnf.go(book, f, FApp{term_cell(x, "_"), s} <> frs, LNo{})
    case Lam{k, i, f, s, q}:
      wnf.lam(book, Lam{k, i, f, s, q}, frs, lhs)
    case Mat{k, h, m, s}:
      wnf.mat(book, Mat{k, h, m, s}, frs, lhs)
    case Efq{s}:
      wnf.efq(book, Efq{s}, frs, lhs)
    case Rwt{+e, p, +f, s}:
      wnf.rwt(book, term_wnf(book, e), Rwt{e, p, f, s}, f, frs, lhs)
    case Ref{+k, +s, b}:
      wnf.ref(book, book_tld(book, k), Ref{k, s, b}, frs, lhs)
    case other:
      wnf.back(book, other, frs)

def Tm.is_qua(t: Tm) -> Bool:
  match t:
    case TQua{q, s}:
      True{}
    case other:
      False{}

def wnf.mnb(tm: Tm, +a: Tm, s: Sp) -> Tm:
  match tm:
    case TQua{QMany{}, +qs}:
      a
    case TQua{QLone{}, qs}:
      Bool.pick(Tm, Tm.is_qua(a), TQua{QLone{}, qs}, Min{a, TQua{QLone{}, qs}, s})
    case TQua{q, qs}:
      TQua{q, qs}
    case other:
      Min{a, other, s}

def lit.to_ctr(t: Tm) -> Tm:
  match t:
    case Lit{v, s}:
      lit_step(Lit{v, s})
    case other:
      other

law wnf.walk:
  for +book: Book
  for +k: String
  for +xs: List<&2, Tm>
  for ctr: Tm
  for w: Tm
  for t: Tm
  for e: Tm
  for lhs: LH
  for s: Sp
  for rest: List<&2, Fr>
  Tm

@unsafe
def wnf.matd(+book: Book, tm: Tm, +t: Tm, e: Tm, lhs: LH, s: Sp, rest: List<&2, Fr>) -> Tm:
  match tm:
    case Ctr{+k, +xs, cs}:
      wnf.walk(book, k, xs, Ctr{k, xs, cs}, t, t, e, lhs, s, rest)
    case other:
      wnf.back(book, term_apply(book, lhs_or(lhs, t), e, s), rest)

law wnf.mna:
  for +book: Book
  for tm: Tm
  for b: Tm
  for s: Sp
  for rest: List<&2, Fr>
  Tm

@unsafe
def wnf.back(book, tm, frs):
  match frs:
    case Nil{}:
      tm
    case FApp{x, s} <> rest:
      wnf.back(book, term_apply(book, tm, x, s), rest)
    case FMna{b, s} <> rest:
      wnf.mna(book, tm, b, s, rest)
    case FMnb{a, s} <> rest:
      wnf.back(book, wnf.mnb(tm, a, s), rest)
    case FMat{t, e, lhs, s} <> rest:
      wnf.matd(book, lit.to_ctr(tm), t, e, lhs, s, rest)

@unsafe
def wnf.mna(book, tm, b, s, rest):
  match tm:
    case TQua{QMany{}, qs}:
      wnf.go(book, b, rest, LNo{})
    case TQua{QNone{}, qs}:
      wnf.back(book, TQua{QNone{}, qs}, rest)
    case other:
      wnf.go(book, b, FMnb{other, s} <> rest, LNo{})

@unsafe
def wnf.walk.mat(
  +book: Book, +k: String, +xs: List<&2, Tm>, ctr: Tm, w: Tm, h: Tm, m: Tm, t: Tm, e: Tm, lhs: LH,
  s: Sp, rest: List<&2, Fr>, hit: Bool
) -> Tm:
  match hit:
    case True{}:
      wnf.go(book, h, app_frames(xs, rest), lhs_mat(book, lhs, k, List.length(&2, Tm, xs)))
    case False{}:
      wnf.walk(book, k, xs, ctr, m, t, e, lhs, s, rest)

@unsafe
def wnf.walk(book, k, xs, ctr, w, t, e, lhs, s, rest):
  match w:
    case Ann{x, ty, as}:
      wnf.walk(book, k, xs, ctr, x, t, e, lhs, s, rest)
    case Mat{+k2, +h, +m, ms}:
      wnf.walk.mat(book, k, xs, ctr, Mat{k2, h, m, ms}, h, m, t, e, lhs, s, rest, String.eq(k, k2))
    case Efq{es}:
      wnf.back(book, term_apply(book, lhs_or(lhs, t), e, s), rest)
    case other:
      wnf.go(book, other, FApp{ctr, NoSp{}} <> rest, lhs)

law snfs:
  for +book: Book
  for xs: List<&2, Tm>
  List<&2, Tm>

# The strong normal form: every binder's body normalized too. An applied
# def stays a call.
@unsafe
def snfs(book, xs):
  match xs:
    case Nil{}:
      Nil{}
    case h <> t:
      term_snf(book, h) <> snfs(book, t)

@unsafe
def snf.fun(+book: Book, f: Tm) -> Tm:
  match f:
    case Ref{k, s, b}:
      Ref{k, s, b}
    case other:
      term_snf(book, other)

@unsafe
def snf.go(book, tm):
  match tm:
    case Var{k, i, s}:
      Var{k, i, s}
    case Ref{k, s, b}:
      Ref{k, s, b}
    case Sub{i, p, f, s}:
      Sub{i, p, term_snf(book, f), s}
    case Typ{g, s}:
      Typ{term_snf(book, g), s}
    case Min{a, b, s}:
      Min{term_snf(book, a), term_snf(book, b), s}
    case All{q, k, i, a, b, s}:
      All{q, k, i, term_snf(book, a), CSnf{b}, s}
    case Lam{k, i, f, s, q}:
      Lam{k, i, CSnf{f}, s, QUnd{}}
    case TApp{f, x, s}:
      TApp{snf.fun(book, f), term_snf(book, x), s}
    case ADT{k, xs, s, r}:
      ADT{k, snfs(book, xs), s, r}
    case Ctr{k, xs, s}:
      Ctr{k, snfs(book, xs), s}
    case Mat{k, h, m, s}:
      Mat{k, term_snf(book, h), term_snf(book, m), s}
    case Eql{a, b, ty, s}:
      Eql{term_snf(book, a), term_snf(book, b), term_snf(book, ty), s}
    case Rwt{e, p, f, s}:
      Rwt{term_snf(book, e), term_snf(book, p), term_snf(book, f), s}
    case other:
      other

#
# le: False compares for equality ("EQ"), True for subsumption ("LE"),
# where a Kind accepts a kind that allows at least as many uses.
def Tm.is_lam(t: Tm) -> Bool:
  match t:
    case Lam{k, i, f, s, q}:
      True{}
    case other:
      False{}

def Tm.is_lit(t: Tm) -> Bool:
  match t:
    case Lit{v, s}:
      True{}
    case other:
      False{}

def Tm.is_ctr(t: Tm) -> Bool:
  match t:
    case Ctr{k, xs, s}:
      True{}
    case other:
      False{}

def Tm.lam_k(a: Tm, b: Tm) -> String:
  match a b:
    case Lam{k, i, f, s, q} y:
      k
    case x Lam{k, i, f, s, q}:
      k
    case x y:
      "_"

law cmp.wnf:
  for le: Bool
  for +book: Book
  for +a: Tm
  for +b: Tm
  for +dep: U32
  Bool

@unsafe
def term_compare(le: Bool, +book: Book, lhs: Tm, rhs: Tm, +dep: U32) -> Bool:
  cmp.wnf(le, book, term_wnf(book, lhs), term_wnf(book, rhs), dep)

# A literal compared with a constructor takes one step.
def cmp.lit(+a: Tm, +b: Tm) -> Tm:
  Bool.pick(Tm, Bool.and(Tm.is_lit(a), Tm.is_ctr(b)), lit_step(a), a)

law cmp.go:
  for +le: Bool
  for +book: Book
  for a: Tm
  for b: Tm
  for +dep: U32
  Bool

@unsafe
def cmp.lam(le: Bool, +book: Book, +a: Tm, +b: Tm, +dep: U32, lam: Bool) -> Bool:
  match lam:
    case True{}:
      +x = {Var{Tm.lam_k(a, b), dep, NoSp{}} : Tm}
      term_compare(le, book, term_apply1(book, a, x), term_apply1(book, b, x), U32.inc(dep))
    case False{}:
      cmp.go(le, book, cmp.lit(a, b), cmp.lit(b, a), dep)

@unsafe
def cmp.wnf(le, book, a, b, dep):
  cmp.lam(le, book, a, b, dep, Bool.or(Tm.is_lam(a), Tm.is_lam(b)))

law cmps:
  for xs: List<&2, Tm>
  for ys: List<&2, Tm>
  for +book: Book
  for +dep: U32
  Bool

@unsafe
def cmps(xs, ys, book, dep):
  match xs ys:
    case x <> xt y <> yt:
      Lazy.and(term_compare(False{}, book, x, y, dep), u => cmps(xt, yt, book, dep))
    case Nil{} Nil{}:
      True{}
    case p q:
      False{}

def Tm.is_many(t: Tm) -> Bool:
  match t:
    case TQua{QMany{}, s}:
      True{}
    case other:
      False{}

def Tm.is_qua_not_many(t: Tm) -> Bool:
  match t:
    case TQua{QMany{}, s}:
      False{}
    case TQua{q, s}:
      True{}
    case other:
      False{}

def Lazy.or(a: Bool, f: Unit -> Bool) -> Bool:
  match a:
    case True{}:
      True{}
    case False{}:
      f(Unit{})

@unsafe
def cmp.kind.rmin(+book: Book, +g: Tm, h: Tm, +dep: U32) -> Bool:
  match h:
    case Min{a, b, s}:
      Lazy.or(term_compare(True{}, book, Typ{g, NoSp{}}, Typ{a, NoSp{}}, dep), u => term_compare(True{}, book, Typ{g, NoSp{}}, Typ{b, NoSp{}}, dep))
    case other:
      term_compare(True{}, book, g, other, dep)

@unsafe
def cmp.kind.min(+book: Book, g: Tm, +h: Tm, +dep: U32) -> Bool:
  match g:
    case Min{a, b, s}:
      Lazy.and(term_compare(True{}, book, Typ{a, NoSp{}}, Typ{h, NoSp{}}, dep), u => term_compare(True{}, book, Typ{b, NoSp{}}, Typ{h, NoSp{}}, dep))
    case other:
      cmp.kind.rmin(book, other, h, dep)

@unsafe
def cmp.kind.go(+book: Book, g: Tm, h: Tm, +dep: U32, done: Bool) -> Bool:
  match done:
    case True{}:
      True{}
    case False{}:
      cmp.kind.min(book, g, h, dep)

@unsafe
def cmp.kind(+book: Book, +g: Tm, +h: Tm, +dep: U32) -> Bool:
  cmp.kind.go(book, g, h, dep, Bool.or(Tm.is_many(g), Tm.is_qua_not_many(h)))

@unsafe
def cmp.typ(le: Bool, +book: Book, g: Tm, h: Tm, +dep: U32) -> Bool:
  match le:
    case False{}:
      term_compare(False{}, book, g, h, dep)
    case True{}:
      cmp.kind(book, term_wnf(book, g), term_wnf(book, h), dep)

@unsafe
def cmp.go(le, book, a, b, dep):
  match a b:
    case Var{k, i, s} Var{k2, j, s2}:
      U32.is_eq(i, j)
    case Ref{k, s, x} Ref{k2, s2, y}:
      String.eq(k, k2)
    case Typ{g, s} Typ{h, s2}:
      cmp.typ(le, book, g, h, dep)
    case Qnt{s} Qnt{s2}:
      True{}
    case TQua{q, s} TQua{q2, s2}:
      Q.eq(q, q2)
    case Min{a1, b1, s} Min{a2, b2, s2}:
      Lazy.and(term_compare(False{}, book, a1, a2, dep), u => term_compare(False{}, book, b1, b2, dep))
    case All{+q, +k, i, a1, b1, s} All{q2, k2, j, a2, b2, s2}:
      +x = {Var{k, dep, NoSp{}} : Tm}
      Lazy.and(Q.eq(q, q2), u => Lazy.and(term_compare(le, book, a2, a1, dep), u => term_compare(le, book, clo_apply(book, b1, [x]), clo_apply(book, b2, [x]), U32.inc(dep))))
    case TApp{f1, x1, s} TApp{f2, x2, s2}:
      Lazy.and(term_compare(False{}, book, f1, f2, dep), u => term_compare(False{}, book, x1, x2, dep))
    case ADT{+k, +xs, s, +r} ADT{+k2, +ys, s2, +r2}:
      Lazy.and(Bool.and(String.eq(k, k2), Nat.is_eq(List.length(&2, Tm, xs), List.length(&2, Tm, ys))), u => Lazy.and(Bool.or(le, Nat.is_eq(List.length(&2, String, r), List.length(&2, String, r2))), u => Lazy.and(Str.subset(r2, r), u => cmps(xs, ys, book, dep))))
    case Ctr{+k, +xs, s} Ctr{+k2, +ys, s2}:
      Lazy.and(Bool.and(String.eq(k, k2), Nat.is_eq(List.length(&2, Tm, xs), List.length(&2, Tm, ys))), u => cmps(xs, ys, book, dep))
    case Lit{LNat{n}, s} Lit{LNat{m}, s2}:
      Nat.is_eq(n, m)
    case Lit{LStr{x}, s} Lit{LStr{y}, s2}:
      String.eq(x, y)
    case Mat{k, h1, m1, s} Mat{k2, h2, m2, s2}:
      Lazy.and(String.eq(k, k2), u => Lazy.and(term_compare(False{}, book, h1, h2, dep), u => term_compare(False{}, book, m1, m2, dep)))
    case Efq{s} Efq{s2}:
      True{}
    case Eql{a1, b1, t1, s} Eql{a2, b2, t2, s2}:
      Lazy.and(term_compare(False{}, book, a1, a2, dep), u => Lazy.and(term_compare(False{}, book, b1, b2, dep), u => term_compare(False{}, book, t1, t2, dep)))
    case Rfl{s} Rfl{s2}:
      True{}
    case Hol{k, s} Hol{k2, s2}:
      String.eq(k, k2)
    case Rwt{e1, p1, f1, s} Rwt{e2, p2, f2, s2}:
      Lazy.and(term_compare(False{}, book, e1, e2, dep), u => Lazy.and(term_compare(False{}, book, p1, p2, dep), u => term_compare(False{}, book, f1, f2, dep)))
    case x y:
      False{}

@unsafe
def show_hex.more(n, acc, last):
  match last:
    case True{}:
      acc
    case False{}:
      U32.show_hex.go((n >> 4n : U32), acc)

def show.chain.cons(x: Tm, r: List<&2, Tm> & Tm) -> List<&2, Tm> & Tm:
  (xs, t) = r
  (x <> xs, t)

def Lst.last(-A: Data, d: A, xs: List<&2, A>) -> A:
  match xs:
    case Nil{}:
      d
    case h <> Nil{}:
      h
    case h <> t:
      Lst.last(A, d, t)

law show.chain:
  for t: Tm
  for +k: String
  for +n: Nat
  List<&2, Tm> & Tm

@unsafe
def show.chain.if(+t: Tm, +xs: List<&2, Tm>, +k: String, +n: Nat, hit: Bool) ->
  List<&2, Tm> & Tm:
  match hit:
    case True{}:
      show.chain.cons(Lst.head(Tm, t, xs), show.chain(Lst.last(Tm, t, xs), k, n))
    case False{}:
      (Nil{}, t)

# The heads of a chain of k nodes with n fields, and its tail.
@unsafe
def show.chain(t, k, n):
  match t:
    case Ctr{+k2, +xs, s}:
      show.chain.if(Ctr{k2, xs, s}, xs, k, n, Bool.and(String.eq(k, k2),
        Nat.is_eq(List.length(&2, Tm, xs), n)))
    case other:
      (Nil{}, other)

@unsafe
def show.args(bnd, n, xs, p):
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      term_show.go(x, p, bnd, n) <> show.args(bnd, n, t, p)

def show.chr_term.u(m: Maybe<&2, U32>, +quote: U32) -> Maybe<&2, String>:
  match m:
    case None{}:
      None{}
    case Some{+c}:
      Some{show.chr(c, quote)}

# A character (a Chr of a U32), escaped for quote.
def show.chr_term(t: Tm, +quote: U32) -> Maybe<&2, String>:
  match t:
    case Ctr{"Chr", x <> Nil{}, s}:
      show.chr_term.u(u32_from_term(x, "U32"), quote)
    case other:
      None{}

def show.chrs.cat(a: Maybe<&2, String>, b: Maybe<&2, String>) -> Maybe<&2, String>:
  match a b:
    case Some{x} Some{y}:
      Some{x ++ y}
    case p q:
      None{}

def show.chrs(xs: List<&2, Tm>) -> Maybe<&2, String>:
  match xs:
    case Nil{}:
      Some{""}
    case x <> t:
      show.chrs.cat(show.chr_term(x, 34), show.chrs(t))

def show.str_tail(t: Tm) -> Maybe<&2, String>:
  match t:
    case Lit{LStr{x}, s}:
      Some{show.text(x)}
    case Ctr{"SNil", Nil{}, s}:
      Some{""}
    case other:
      None{}

def show.str.c(c: Maybe<&2, String>) -> Maybe<&2, String>:
  match c:
    case None{}:
      None{}
    case Some{x}:
      Some{"\"" ++ x ++ "\""}

def show.str.go(r: List<&2, Tm> & Tm) -> Maybe<&2, String>:
  (cs, t) = r
  show.str.c(show.chrs.cat(show.chrs(cs), show.str_tail(t)))

def show.str(t: Tm) -> Maybe<&2, String>:
  show.str.go(show.chain(t, "SCon", 2n))

def show.arr.cat(a: Maybe<&2, List<&2, String>>, b: Maybe<&2, List<&2, String>>) ->
  Maybe<&2, List<&2, String>>:
  match a b:
    case Some{x} Some{y}:
      Some{List.append(&2, String, x, y)}
    case p q:
      None{}

law show.arr:
  for t: Tm
  for +bnd: List<&2, String>
  for +n: Nat
  Maybe<&2, List<&2, String>>

@unsafe
def show.arr(t, bnd, n):
  match t:
    case Ctr{"ALeaf", x <> Nil{}, s}:
      Some{[term_show.go(x, 1, bnd, n)]}
    case Ctr{"ANode", l <> r <> Nil{}, s}:
      show.arr.cat(show.arr(l, bnd, n), show.arr(r, bnd, n))
    case other:
      None{}

def Word.from_u32(+b: U32) -> Word(32n):
  match b:
    case U32{w}:
      w

def F32.from_bits(+b: U32) -> F32:
  F32{Word.from_u32(b)}

def f32_show(+bits: U32) -> String:
  +s = F32.show(F32.from_bits(bits))
  Bool.pick(String, Bool.or(String.contains(s, "."), Bool.or(String.contains(s, "e"),
    Bool.or(String.contains(s, "n"), String.contains(s, "i")))), s, s ++ ".0")

@unsafe
def show.typ(g, bnd, n):
  match g:
    case TQua{QLone{}, s}:
      "Type"
    case TQua{QMany{}, s}:
      "Data"
    case other:
      "Kind(" ++ term_show.go(other, 1, bnd, n) ++ ")"

@unsafe
def show.arms(t, bnd, n):
  match t:
    case Mat{k, h, m, s}:
      (k ++ ": " ++ term_show.go(h, 2, bnd, n)) <> show.arms(m, bnd, n)
    case Efq{s}:
      Nil{}
    case other:
      [term_show.go(other, 2, bnd, n)]

@unsafe
def show.app.go(r: Tm & List<&2, Tm>, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  (h, xs) = r
  match h xs:
    case Ref{"Exists", s, b} a <> Lam{+k, i, f, ls, q} <> Nil{}:
      show.paren(U32.is_gt(p, 2), "&" ++ k ++ ":" ++ term_show.go(a, 3, bnd, n) ++ " -> " ++
        term_show.go(syn_body(f), 2, k <> bnd, 1n+n))
    case hd args:
      term_show.go(hd, 3, bnd, n) ++ "(" ++ show.join(show.args(bnd, n, args, 1), ", ") ++ ")"

@unsafe
def show.app(t, p, bnd, n):
  show.app.go(term_unapply(t), p, bnd, n)

@unsafe
def show.rwt.inner(es: String, pr: Tm, +k1: String, b: Tm, f: Tm, +bnd: List<&2, String>, +n: Nat) ->
  String:
  match b:
    case Lam{+k2, i, f2, s, q}:
      "%" ++ Bool.pick(String, String.is_empty(k2), "", k2 ++ "@") ++ es ++ " : " ++
        term_show.go(syn_body(f2), 2, k2 <> k1 <> bnd, 2n+n) ++ "; " ++ term_show.go(f, 0, bnd, n)
    case other:
      "%" ++ es ++ " : " ++ term_show.go(pr, 2, bnd, n) ++ "; " ++ term_show.go(f, 0, bnd, n)

@unsafe
def show.rwt.go(es: String, pr: Tm, f: Tm, +bnd: List<&2, String>, +n: Nat) -> String:
  match pr:
    case Lam{+k1, i, +f1, s, q}:
      show.rwt.inner(es, Lam{k1, i, f1, s, q}, k1, term_strip(syn_body(f1)), f, bnd, n)
    case other:
      "%" ++ es ++ " : " ++ term_show.go(other, 2, bnd, n) ++ "; " ++ term_show.go(f, 0, bnd, n)

@unsafe
def show.rwt(e, pr, f, bnd, n):
  show.rwt.go(term_show.go(e, 2, bnd, n), term_strip(pr), f, bnd, n)

@unsafe
def show.ctr.plain(t: Tm, +bnd: List<&2, String>, +n: Nat) -> String:
  match t:
    case Ctr{k, xs, s}:
      k ++ "{" ++ show.join(show.args(bnd, n, xs, 1), ", ") ++ "}"
    case other:
      "?"

@unsafe
def show.ctr.arr(t: Tm, m: Maybe<&2, List<&2, String>>, +bnd: List<&2, String>, +n: Nat) -> String:
  match m:
    case Some{xs}:
      "[" ++ show.join(xs, ", ") ++ "]"
    case None{}:
      show.ctr.plain(t, bnd, n)

@unsafe
def show.ctr.tup(+t: Tm, r: List<&2, Tm> & Tm, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  (xs, tl) = r
  match xs:
    case Nil{}:
      show.ctr.arr(t, show.arr(t, bnd, n), bnd, n)
    case h <> rest:
      "(" ++ show.join(show.args(bnd, n, List.append(&2, Tm, h <> rest, [tl]), 1), ", ") ++ ")"

@unsafe
def show.ctr.lst(+t: Tm, r: List<&2, Tm> & Tm, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  (xs, tl) = r
  match xs tl:
    case ys Ctr{"Nil", Nil{}, s}:
      "[" ++ show.join(show.args(bnd, n, ys, 1), ", ") ++ "]"
    case Nil{} other:
      show.ctr.tup(t, show.chain(t, "Tuple", 2n), p, bnd, n)
    case ys other:
      show.paren(U32.is_gt(p, 2), show.join(show.args(bnd, n, ys, 3), " <> ") ++ " <> " ++
        term_show.go(other, 2, bnd, n))

@unsafe
def show.ctr.str(+t: Tm, m: Maybe<&2, String>, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  match m:
    case Some{c}:
      c
    case None{}:
      show.ctr.lst(t, show.chain(t, "Con", 2n), p, bnd, n)

@unsafe
def show.ctr.chr(+t: Tm, m: Maybe<&2, String>, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  match m:
    case Some{c}:
      "'" ++ c ++ "'"
    case None{}:
      show.ctr.str(t, show.str(t), p, bnd, n)

@unsafe
def show.ctr.succ(+t: Tm, r: List<&2, Tm> & Tm, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  (xs, tl) = r
  match xs:
    case Nil{}:
      show.ctr.chr(t, show.chr_term(t, 39), p, bnd, n)
    case +h <> rest:
      show.paren(U32.is_gt(p, 2), Nat.show(List.length(&2, Tm, h <> rest)) ++ "n+" ++
        term_show.go(tl, 2, bnd, n))

@unsafe
def show.ctr.nat(+t: Tm, m: Maybe<&2, Nat>, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  match m:
    case Some{v}:
      Nat.show(v) ++ "n"
    case None{}:
      show.ctr.succ(t, show.chain(t, "Succ", 1n), p, bnd, n)

@unsafe
def show.ctr.f32(+t: Tm, m: Maybe<&2, U32>, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  match m:
    case Some{v}:
      f32_show(v)
    case None{}:
      show.ctr.nat(t, nat_from_term(t), p, bnd, n)

@unsafe
def show.ctr.u32(+t: Tm, m: Maybe<&2, U32>, +p: U32, +bnd: List<&2, String>, +n: Nat) -> String:
  match m:
    case Some{v}:
      U32.show(v)
    case None{}:
      show.ctr.f32(t, u32_from_term(t, "F32"), p, bnd, n)

@unsafe
def show.ctr(t, p, bnd, n):
  show.ctr.u32(t, u32_from_term(t, "U32"), p, bnd, n)

def err.make(+book: Book, ctx: List<&2, Tm>, exp: Msg, obs: Msg, spn: Sp, dn: String) -> Err:
  Err{book, ctx, exp, obs, spn, dn, ""}

def ctx_bind(ctx: List<&2, Tm>, i: U32, q: Q, k: String, ty: Tm) -> List<&2, Tm>:
  CB{i, q, k, ty} <> ctx

def ctx_len(ctx: List<&2, Tm>) -> U32:
  match ctx:
    case Nil{}:
      0
    case CB{+i, q, k, ty} <> t:
      U32.max(U32.inc(i), ctx_len(t))
    case x <> t:
      ctx_len(t)

law ctx_name:
  for ctx: List<&2, Tm>
  for +i: U32
  String

@unsafe
def ctx_name.if(k: String, t: List<&2, Tm>, +i: U32, hit: Bool) -> String:
  match hit:
    case True{}:
      k
    case False{}:
      ctx_name(t, i)

@unsafe
def ctx_name(ctx, i):
  match ctx:
    case Nil{}:
      "_"
    case CB{+j, q, +k, ty} <> t:
      ctx_name.if(k, t, i, U32.is_eq(i, j))
    case x <> t:
      ctx_name(t, i)

law ctx_scope.c:
  for +ctx: List<&2, Tm>
  for +i: U32
  for +n: U32
  for c: Bool
  List<&2, String>

@unsafe
def ctx_scope.go(+ctx: List<&2, Tm>, +i: U32, +n: U32) -> List<&2, String>:
  ctx_scope.c(ctx, i, n, U32.is_ge(i, n))

@unsafe
def ctx_scope.c(ctx, i, n, c):
  match c:
    case True{}:
      Nil{}
    case False{}:
      ctx_name(ctx, i) <> ctx_scope.go(ctx, U32.inc(i), n)

# The names in scope, outermost first.
def ctx_scope(+ctx: List<&2, Tm>) -> List<&2, String>:
  ctx_scope.go(ctx, 0, ctx_len(ctx))

def expr_show(+book: Book, m: Msg, +bnd: List<&2, String>) -> String:
  match m:
    case MNone{}:
      ""
    case MStr{s}:
      s
    case MTm{t}:
      term_show(term_lower(book, term_snf(book, t), U32.from_nat(List.length(&2, String, bnd))), 0,
        List.reverse(&2, String, bnd))

def typeless.note(+book: Book, tm: Tm) -> String:
  match tm:
    case Ctr{+k, xs, s}:
      Bool.pick(String, Tld.is_adt(book_tld(book, k)), " (" ++ k ++
        " is a datatype: write its arguments as <>)", "")
    case other:
      ""

def typeless_show(+book: Book, +ctx: List<&2, Tm>, +tm: Tm) -> String:
  "non-inferrable term '" ++ expr_show(book, MTm{tm}, ctx_scope(ctx)) ++ "'" ++ typeless.note(book, tm)

def List.take_strn(n: Nat, xs: List<&2, String>) -> List<&2, String>:
  match n xs:
    case 0n ys:
      Nil{}
    case 1n+m y <> t:
      y <> List.take_strn(m, t)
    case k Nil{}:
      Nil{}

def List.take_str(xs: List<&2, String>, n: U32) -> List<&2, String>:
  List.take_strn(U32.to_nat(n), xs)

def ctx_sorted(ctx: List<&2, Tm>) -> List<&2, Tm>:
  List.reverse(&2, Tm, ctx)

def ctx_width(ctx: List<&2, Tm>) -> Nat:
  match ctx:
    case Nil{}:
      0n
    case CB{i, q, k, ty} <> t:
      Nat.max(String.length(k), ctx_width(t))
    case x <> t:
      ctx_width(t)

def err.ctx_lines(+book: Book, ctx: List<&2, Tm>, +bnd: List<&2, String>, +wid: Nat) -> String:
  match ctx:
    case Nil{}:
      ""
    case CB{+i, q, k, ty} <> t:
      "\n- " ++ Str.pad(k, wid) ++ " : " ++ term_show(term_lower(book, term_snf(book, ty), i), 0,
        List.reverse(&2, String, List.take_str(bnd, i))) ++ err.ctx_lines(book, t, bnd, wid)
    case x <> t:
      err.ctx_lines(book, t, bnd, wid)

def List.drop_str(xs: List<&2, String>, n: Nat) -> List<&2, String>:
  match xs n:
    case ys 0n:
      ys
    case y <> t 1n+m:
      List.drop_str(t, m)
    case Nil{} k:
      Nil{}

law err.lines.one:
  for l: String
  for t: List<&2, String>
  for +i: Nat
  for +end: Nat
  for +at: Nat
  for +w: Nat
  for past: Bool
  String

@unsafe
def err.lines.each(lns: List<&2, String>, +i: Nat, +end: Nat, +at: Nat, +w: Nat) -> String:
  match lns:
    case Nil{}:
      ""
    case l <> t:
      err.lines.one(l, t, i, end, at, w, Nat.is_gt(i, end))

def err.lines.go(+lns: List<&2, String>, +at: Nat) -> String:
  +beg = Nat.max(1n, Nat.sub(at, 1n))
  +end = Nat.min(List.length(&2, String, lns), Nat.add(at, 1n))
  +w = String.length(Nat.show(end))
  err.lines.each(List.drop_str(lns, Nat.sub(beg, 1n)), beg, end, at, w)

# The source lines around a span (the official three-line excerpt).
def err.lines(s: Sp) -> String:
  match s:
    case NoSp{}:
      ""
    case Sp{+src, +beg, end}:
      err.lines.go(String.split(src, '\n'), Nat.add(1n, Str.count_nl(String.take(src, U32.to_nat(beg)))))

@unsafe
def err.lines.one(l, t, i, end, at, w, past):
  match past:
    case True{}:
      ""
    case False{}:
      "\n" ++ Str.padl(Nat.show(i), w) ++ Bool.pick(String, Nat.is_eq(i, at), ">| ", " | ") ++ l ++
        err.lines.each(t, 1n+i, end, at, w)

def err.msg(+book: Book, exp: Msg, obs: Msg, +bnd: List<&2, String>) -> String:
  match obs:
    case MNone{}:
      "\n- message  : " ++ expr_show(book, exp, bnd)
    case other:
      "\n- expected : " ++ expr_show(book, exp, bnd) ++ "\n- observed : " ++ expr_show(book, other, bnd)

def err_show(e: Err) -> String:
  Err{+bok, +ctx, exp, obs, spn, +dn, +nte} = e
  +bnd = ctx_scope(ctx)
  +msg = err.msg(bok, exp, obs, bnd)
  +cl = err.ctx_lines(bok, ctx_sorted(ctx), bnd, ctx_width(ctx))
  +sp = err.lines(spn)
  +df = Bool.pick(String, String.is_empty(dn), "", " " ++ dn)
  "Error:" ++ msg ++ Bool.pick(String, Lst.empty(&2, Tm, ctx), "", "\nContext:") ++ cl ++
    Bool.pick(String, Bool.and(String.is_empty(df), String.is_empty(sp)), "", "\nLocation:" ++ df ++ sp) ++
    Bool.pick(String, String.is_empty(nte), "", "\n" ++ nte)

law Cur.line:
  for +c: Cur
  Cur

@unsafe
def Cur.skip.c(c: Cur, k: Nat) -> Cur:
  match k:
    case 0n:
      c
    case 1n:
      Cur.skip(Cur.step(c))
    case 2n+p:
      Cur.skip(Cur.line(c))

@unsafe
def Cur.skip.go(+x: U32, c: Cur) -> Cur:
  Cur.skip.c(c, Bool.pick(Nat, is_space(x), 1n, Bool.pick(Nat, U32.is_eq(x, 35), 2n, 0n)))

# Skips spaces and # comments.
@unsafe
def Cur.skip(c):
  Cur.skip.go(Cur.peek(c), c)

@unsafe
def Cur.line.c(c: Cur, stop: Bool) -> Cur:
  match stop:
    case True{}:
      c
    case False{}:
      Cur.line(Cur.step(c))

@unsafe
def Cur.line.go(+x: U32, c: Cur) -> Cur:
  Cur.line.c(c, Bool.or(U32.is_eq(x, 10), U32.is_zero(x)))

# Moves to the end of the line (before its newline).
@unsafe
def Cur.line(c):
  Cur.line.go(Cur.peek(c), c)

@unsafe
def Cur.name.c(+x: U32, c: Cur, acc: String, ok: Bool) -> String & Cur:
  match ok:
    case True{}:
      Cur.name(Cur.step(c), SCon{Chr{x}, acc})
    case False{}:
      (String.reverse(acc), c)

@unsafe
def Cur.name.go(+x: U32, c: Cur, acc: String) -> String & Cur:
  Cur.name.c(x, c, acc, is_name(x))

@unsafe
def Cur.name(c, acc):
  Cur.name.go(Cur.peek(c), c, acc)

def PS.frs(+ps: PS) -> U32:
  PS{cur, stk, stn, +frs, book, src, ns, dir, al} = ps
  frs

@unsafe
def SB.find.if(t: List<&2, SB>, +k: String, +i: U32, hit: Bool) -> Maybe<&2, U32>:
  match hit:
    case True{}:
      Some{i}
    case False{}:
      SB.find(t, k)

@unsafe
def SB.find(xs, k):
  match xs:
    case Nil{}:
      None{}
    case SB{+k2, +i} <> t:
      SB.find.if(t, k, i, String.eq(k, k2))

@unsafe
def SB2.find.if(t: List<&2, SB2>, +k: String, v: String, hit: Bool) -> Maybe<&2, String>:
  match hit:
    case True{}:
      Some{v}
    case False{}:
      SB2.find(t, k)

@unsafe
def SB2.find(xs, k):
  match xs:
    case Nil{}:
      None{}
    case SB2{+k2, v} <> t:
      SB2.find.if(t, k, v, String.eq(k, k2))

@unsafe
def escape.find.if(t: List<&2, U32>, +c: U32, v: U32, hit: Bool) -> Maybe<&2, U32>:
  match hit:
    case True{}:
      Some{v}
    case False{}:
      escape.find(t, c)

@unsafe
def escape.find(e, c):
  match e:
    case +k <> v <> t:
      escape.find.if(t, c, v, U32.is_eq(k, c))
    case other:
      None{}

def is_hex(+c: U32) -> Bool:
  Bool.or(is_digit(c), Bool.or(Bool.and(U32.is_ge(c, 97), U32.is_le(c, 102)),
    Bool.and(U32.is_ge(c, 65), U32.is_le(c, 70))))

def hex_val(+c: U32) -> U32:
  Bool.pick(U32, is_digit(c), (c - 48 : U32), Bool.pick(U32, U32.is_ge(c, 97), (c - 87 : U32), (c - 55 : U32)))

@unsafe
def uesc.hex.if(t: String, +c: U32, +acc: U32, +n: Nat, hex: Bool, close: Bool) -> Maybe<&1, U32 & Nat>:
  match hex close:
    case True{} x:
      Bool.pick(Maybe<&1, U32 & Nat>, Nat.is_ge(n, 8n), None{},
        uesc.hex(t, ((acc * 16 : U32) + hex_val(c) : U32), 1n+n))
    case False{} True{}:
      Bool.pick(Maybe<&1, U32 & Nat>, Nat.is_eq(n, 0n), None{}, Some{(acc, Nat.add(n, 3n))})
    case False{} False{}:
      None{}

@unsafe
def uesc.hex(s, acc, n):
  match s:
    case SCon{Chr{+c}, t}:
      uesc.hex.if(t, c, acc, n, is_hex(c), U32.is_eq(c, 125))
    case SNil{}:
      None{}

@unsafe
def Nat.log2_exact.cmp(+n: Nat, +k: Nat, +p: Nat, c: Cmp) -> Maybe<&2, Nat>:
  match c:
    case LT{}:
      Nat.log2_exact.go(n, 1n+k, Nat.double(p))
    case EQ{}:
      Some{k}
    case GT{}:
      None{}

@unsafe
def Nat.log2_exact.go(n, k, p):
  Nat.log2_exact.cmp(n, k, p, Nat.cmp(p, n))

def op.ok(+sym: String, +r: String, +prev: U32) -> Bool:
  +nx = Str.first(String.drop(r, String.length(sym)))
  +c0 = Str.first(sym)
  Bool.and(Str.prefix(r, sym), Bool.and(
    Bool.not(Bool.and(Bool.or(String.eq(sym, "-"), String.eq(sym, "+")), Bool.or(U32.is_eq(nx, 62), is_head(nx)))),
    Bool.and(Bool.not(Bool.and(U32.is_eq(c0, 62), Bool.not(Bool.or(is_space(prev), U32.is_zero(prev))))),
      Bool.not(Bool.and(String.eq(sym, "%"), Bool.not(is_space(nx)))))))

@unsafe
def op.find.if(t: List<&2, Op>, +r: String, +prev: U32, o: Op, hit: Bool) -> Maybe<&2, Op>:
  match hit:
    case True{}:
      Some{o}
    case False{}:
      op.find(t, r, prev)

# The operator at the head of r (prev: the character before it).
@unsafe
def op.find(ops, r, prev):
  match ops:
    case Nil{}:
      None{}
    case Op{+sym, +prec, +right, +name} <> t:
      op.find.if(t, r, prev, Op{sym, prec, right, name}, op.ok(sym, r, prev))

def Pt.is_var(+p: Pt) -> Bool:
  match p:
    case PVar{k, i, q, s}:
      True{}
    case other:
      False{}

# The Sub-substitution of a body: a variable scrutinee i becomes pattern v.
def body_sub.scrut(+i: U32, +v: Pt, e: Tm) -> Tm:
  match e:
    case Var{+k, +j, +s}:
      Bool.pick(Tm, U32.is_eq(i, j), patt_term(v, s), Var{k, j, s})
    case other:
      Sub{i, v, other, NoSp{}}

def body_sub.scruts(+i: U32, +v: Pt, es: List<&2, Tm>) -> List<&2, Tm>:
  match es:
    case Nil{}:
      Nil{}
    case e <> t:
      body_sub.scrut(i, v, e) <> body_sub.scruts(i, v, t)

@unsafe
def body_sub.rows(rows: List<&2, Body>, +i: U32, +v: Pt) -> List<&2, Body>:
  match rows:
    case Nil{}:
      Nil{}
    case r <> t:
      body_sub(r, i, v) <> body_sub.rows(t, i, v)

@unsafe
def body_sub(b, i, v):
  match b:
    case BMatch{es, rows, s}:
      BMatch{body_sub.scruts(i, v, es), body_sub.rows(rows, i, v), s}
    case BLocal{ks, q, vs, f}:
      BLocal{ks, q, body_sub.scruts(i, v, vs), body_sub(f, i, v)}
    case BReply{x, s}:
      BReply{Sub{i, v, x, NoSp{}}, s}
    case Row{ps, f}:
      Row{ps, body_sub(f, i, v)}

def Row.first(r: Body) -> Pt:
  match r:
    case Row{p <> t, f}:
      p
    case other:
      PVar{"_", 0, QLone{}, NoSp{}}

def ops.first(a: Maybe<&2, Tm>, b: Maybe<&2, Tm>) -> Maybe<&2, Tm>:
  match a:
    case Some{x}:
      Some{x}
    case None{}:
      b

@unsafe
def ops.bares(xs: List<&2, Tm>) -> Maybe<&2, Tm>:
  match xs:
    case Nil{}:
      None{}
    case x <> t:
      ops.first(ops.bare(x), ops.bares(t))

@unsafe
def ops.bare(t):
  match t:
    case Ref{+k, +s, b}:
      Bool.pick(Maybe<&2, Tm>, Nat.is_eq(Str.last_dot(k), 0n), Some{Ref{k, s, b}}, None{})
    case Sub{i, p, f, s}:
      ops.bare(f)
    case Let{ks, ids, vs, f, s, qs}:
      ops.first(ops.bares(vs), ops.bare(syn_body(f)))
    case Typ{g, s}:
      ops.bare(g)
    case Min{a, b, s}:
      ops.first(ops.bare(a), ops.bare(b))
    case All{q, k, i, a, b, s}:
      ops.first(ops.bare(a), ops.bare(syn_body(b)))
    case Lam{k, i, f, s, q}:
      ops.bare(syn_body(f))
    case TApp{f, x, s}:
      ops.first(ops.bare(f), ops.bare(x))
    case ADT{k, xs, s, r}:
      ops.bares(xs)
    case Ctr{k, xs, s}:
      ops.bares(xs)
    case Mat{k, h, m, s}:
      ops.first(ops.bare(h), ops.bare(m))
    case Eql{a, b, ty, s}:
      ops.first(ops.bare(a), ops.first(ops.bare(b), ops.bare(ty)))
    case Rwt{e, p, f, s}:
      ops.first(ops.bare(e), ops.first(ops.bare(p), ops.bare(f)))
    case Ann{x, ty, s}:
      ops.first(ops.bare(x), ops.bare(ty))
    case VRf{k, i, s, r}:
      ops.bare(r)
    case other:
      None{}

#
# K(A): a check that may fail with an Err and may add template instances to
# the book.
def K(-A: Type) -> Type:
  Book -> Result<&1, &1, Err, A & Book>

def K.go.done(-A: Type, -B: Type, v: A & Book, f: A -> K(B)) -> Result<&1, &1, Err, B & Book>:
  (a, b) = v
  f(a, b)

def K.go(-A: Type, -B: Type, r: Result<&1, &1, Err, A & Book>, f: A -> K(B)) ->
  Result<&1, &1, Err, B & Book>:
  match r:
    case Fail{e}:
      Fail{e}
    case Done{v}:
      K.go.done(A, B, v, f)

def K.bind(-A: Type, -B: Type, m: K(A), f: A -> K(B)) -> K(B):
  b => K.go(A, B, m(b), f)

def K.pure(-A: Type, x: A) -> K(A):
  b => Done{(x, b)}

def K.throw(-A: Type, e: Err) -> K(A):
  b => Fail{e}

def K.book() -> K(Book):
  +b => Done{(b, b)}

def K.set_book(b: Book) -> K(Unit):
  old => Done{(Unit{}, b)}

def K.if(-A: Type, c: Bool, t: K(A), e: K(A)) -> K(A):
  match c:
    case True{}:
      t
    case False{}:
      e

# An error raised with the current book.
def K.err(-A: Type, ctx: List<&2, Tm>, exp: Msg, obs: Msg, s: Sp, +dn: String) -> K(A):
  +b => Fail{err.make(b, ctx, exp, obs, s, dn)}

# The lhs of the def being checked: the call it is (for termination), how
# many parameters remain, its name, its parameters' quantities, whether it
# is @unsafe, and how deep template instantiation is.
type CL is Data:
  CL{t: Tm, n: Nat, dn: String, qs: List<&2, Q>, u: Bool, z: Nat}

def CL.dn(+l: CL) -> String:
  CL{t, n, +dn, qs, u, z} = l
  dn

def CL.u(+l: CL) -> Bool:
  CL{t, n, dn, qs, +u, z} = l
  u

type IR is Data:
  IR{ty: Tm, us: List<&2, Us>, x: Nat}

def lhs_kind(+l: CL, +q: Q) -> Q:
  Bool.pick(Q, Bool.and(CL.u(l), Q.is_many(q)), QLone{}, q)

law ctx_get:
  for ctx: List<&2, Tm>
  for +i: U32
  Maybe<&2, Tm>

@unsafe
def ctx_get.if(ty: Tm, t: List<&2, Tm>, +i: U32, hit: Bool) -> Maybe<&2, Tm>:
  match hit:
    case True{}:
      Some{ty}
    case False{}:
      ctx_get(t, i)

@unsafe
def ctx_get(ctx, i):
  match ctx:
    case Nil{}:
      None{}
    case CB{+j, q, k, ty} <> t:
      ctx_get.if(ty, t, i, U32.is_eq(i, j))
    case x <> t:
      ctx_get(t, i)

def typ(q: Q) -> Tm:
  Typ{TQua{q, NoSp{}}, NoSp{}}

def quant_used(+ctx: List<&2, Tm>, +k: String, +q: Q, +u: Q, s: Sp, +dn: String) -> K(Unit):
  K.if(Unit, Q.eq(quant_join(u, q), q), K.pure(Unit, Unit{}),
    K.err(Unit, ctx, MStr{quant_show(q) ++ k}, MStr{Bool.pick(String, Q.is_many(u), k ++ " (consumed more than once)",
      quant_show(u) ++ k)}, s, dn))

def tele_head.go(t: Tm, +ctx: List<&2, Tm>, +dn: String, +s: Sp) -> K(Tm):
  match t:
    case All{q, k, i, a, b, as}:
      K.pure(Tm, All{q, k, i, a, b, as})
    case other:
      K.err(Tm, ctx, MStr{"unreachable (a telescope binds its parameters and fields)"}, MNone{}, s, dn)

def tele_head(+tel: Tm, +ctx: List<&2, Tm>, +dn: String, +s: Sp) -> K(Tm):
  do K<Tm>:
    b : Book <- K.book()
    tele_head.go(term_wnf(b, tel), ctx, dn, s)

def All.q(t: Tm) -> Q:
  match t:
    case All{q, k, i, a, b, s}:
      q
    case other:
      QLone{}

def All.a(t: Tm) -> Tm:
  match t:
    case All{q, k, i, a, b, s}:
      a
    case other:
      other

def All.b(t: Tm) -> Tm:
  match t:
    case All{q, k, i, a, b, s}:
      b
    case other:
      CConst{other}

def All.k(t: Tm) -> String:
  match t:
    case All{q, k, i, a, b, s}:
      k
    case other:
      "_"

@unsafe
def tele_fill(+tel: Tm, xs: List<&2, Tm>, +ctx: List<&2, Tm>, +dn: String, +s: Sp) -> K(Tm):
  match xs:
    case Nil{}:
      K.pure(Tm, tel)
    case x <> t:
      do K<Tm>:
        +h : Tm <- tele_head(tel, ctx, dn, s)
        b : Book <- K.book()
        tele_fill(clo_apply(b, All.b(h), [x]), t, ctx, dn, s)

law term_check:
  for +l: CL
  for tm: Tm
  for +qt: Q
  for +ty: Tm
  for +ctx: List<&2, Tm>
  for +d: U32
  K(List<&2, Us>)

# Checks xs against the telescope tel; answers their uses and what is left.
@unsafe
def tele_check(
  +l: CL, +tel: Tm, xs: List<&2, Tm>, +qt: Q, +ctx: List<&2, Tm>, +d: U32, +s: Sp, us: List<&2, Us>
) -> K(List<&2, Us> & Tm):
  match xs:
    case Nil{}:
      K.pure(List<&2, Us> & Tm, (us, tel))
    case +x <> t:
      do K<List<&2, Us> & Tm>:
        +h : Tm <- tele_head(tel, ctx, CL.dn(l), s)
        u : List<&2, Us> <- term_check(l, x, quant_dem(All.q(h), qt), All.a(h), ctx, d)
        b : Book <- K.book()
        tele_check(l, clo_apply(b, All.b(h), [x]), t, qt, ctx, d, s, uses_add(us, u))

type Dom is Data:
  Dom{q: Q, k: String, a: Tm}

@unsafe
def tele_unbind.go(+book: Book, t: Tm, +j: U32, doms: List<&2, Dom>) -> List<&2, Dom> & Tm:
  match t:
    case All{q, +k, i, a, b, s}:
      tele_unbind.go(book, term_wnf(book, clo_apply(book, b, [Var{k, j, NoSp{}}])), U32.inc(j),
        List.append(&2, Dom, doms, [Dom{q, k, a}]))
    case other:
      (doms, other)

# The parameters of a type, and what it returns.
def tele_unbind(+book: Book, t: Tm) -> List<&2, Dom> & Tm:
  tele_unbind.go(book, term_wnf(book, t), 0, Nil{})

def Dom.qs(ds: List<&2, Dom>) -> List<&2, Q>:
  match ds:
    case Nil{}:
      Nil{}
    case Dom{q, k, a} <> t:
      q <> Dom.qs(t)

def Dom.ctx(ds: List<&2, Dom>, +d: U32, ctx: List<&2, Tm>) -> List<&2, Tm>:
  match ds:
    case Nil{}:
      ctx
    case Dom{q, k, a} <> t:
      Dom.ctx(t, U32.inc(d), ctx_bind(ctx, d, q, k, a))

law ctrs_find:
  for cs: List<&2, CtrD>
  for +k: String
  Maybe<&2, CtrD>

@unsafe
def ctrs_find.if(c: CtrD, rest: List<&2, CtrD>, +k: String, hit: Bool) -> Maybe<&2, CtrD>:
  match hit:
    case True{}:
      Some{c}
    case False{}:
      ctrs_find(rest, k)

@unsafe
def ctrs_find(cs, k):
  match cs:
    case Nil{}:
      None{}
    case CtrD{+k2, n, t} <> rest:
      ctrs_find.if(CtrD{k2, n, t}, rest, k, String.eq(k, k2))

def ctrs_drop.if(c: CtrD, rest: List<&2, CtrD>, drop: Bool) -> List<&2, CtrD>:
  match drop:
    case True{}:
      rest
    case False{}:
      c <> rest

def ctrs_drop(cs: List<&2, CtrD>, +r: List<&2, String>) -> List<&2, CtrD>:
  match cs:
    case Nil{}:
      Nil{}
    case CtrD{+k, n, t} <> rest:
      ctrs_drop.if(CtrD{k, n, t}, ctrs_drop(rest, r), Str.has(r, k))

type AD is Data:
  AD{n: Nat, g: Nat, t: Tm, cs: List<&2, CtrD>}

def ADT.r(t: Tm) -> List<&2, String>:
  match t:
    case ADT{k, xs, s, r}:
      r
    case other:
      Nil{}

def book_adt.go(+adt: Tm, t: Maybe<&2, Tld>, +ctx: List<&2, Tm>, +dn: String) -> K(AD):
  match t:
    case Some{TADT{n, g, ty, cs, tbase}}:
      K.pure(AD, AD{n, g, ty, ctrs_drop(cs, ADT.r(adt))})
    case other:
      K.err(AD, ctx, MStr{"a declared datatype (unknown: " ++ Tm.name(adt) ++ ")"}, MNone{}, Tm.span(adt), dn)

# A datatype instance's declaration, less the constructors already matched.
def book_adt(+adt: Tm, +ctx: List<&2, Tm>, +dn: String) -> K(AD):
  do K<AD>:
    b : Book <- K.book()
    book_adt.go(adt, book_tld(b, Tm.name(adt)), ctx, dn)

def ADT.xs(t: Tm) -> List<&2, Tm>:
  match t:
    case ADT{k, xs, s, r}:
      xs
    case other:
      Nil{}

def AD.cs(a: AD) -> List<&2, CtrD>:
  AD{n, g, t, cs} = a
  cs

def CtrD.names(cs: List<&2, CtrD>) -> List<&2, String>:
  match cs:
    case Nil{}:
      Nil{}
    case CtrD{k, n, t} <> rest:
      k <> CtrD.names(rest)

@unsafe
def book_fam.go(+book: Book, t: Tm, +d: U32, +k: String) -> String:
  match t:
    case All{q, +ak, i, a, b, s}:
      book_fam.go(book, term_strip(clo_apply(book, b, [Var{ak, d, NoSp{}}])), U32.inc(d), k)
    case ADT{ak, xs, s, r}:
      ak
    case other:
      k

def book_fam.ctr(+book: Book, c: Maybe<&2, CtrD>, +k: String) -> String:
  match c:
    case Some{CtrD{ck, n, t}}:
      book_fam.go(book, term_strip(t), 0, k)
    case None{}:
      k

# The family a constructor builds.
def book_fam(+book: Book, +k: String) -> String:
  book_fam.ctr(book, book_ctr(book, k), k)

def ctx_dead.tld(t: Maybe<&2, Tld>, +r: List<&2, String>) -> Bool:
  match t:
    case Some{TADT{n, g, ty, cs, tbase}}:
      Lst.empty(&2, CtrD, ctrs_drop(cs, r))
    case other:
      False{}

def ctx_dead.ty(+book: Book, t: Tm) -> Bool:
  match t:
    case ADT{+k, xs, s, +r}:
      ctx_dead.tld(book_tld(book, k), r)
    case other:
      False{}

# Whether some live variable's type is a datatype without constructors.
def ctx_dead(+book: Book, ctx: List<&2, Tm>) -> Bool:
  match ctx:
    case Nil{}:
      False{}
    case CB{i, +q, k, ty} <> t:
      Lazy.or(Lazy.and(Bool.not(Q.is_none(q)), u => ctx_dead.ty(book, term_wnf(book, ty))), u => ctx_dead(book, t))
    case x <> t:
      ctx_dead(book, t)

def descend.lit(+a: Tm, +p: Tm) -> Tm:
  Bool.pick(Tm, Bool.and(Tm.is_lit(a), Tm.is_ctr(p)), lit_step(a), a)

law descend.go:
  for +book: Book
  for +a: Tm
  for p: Tm
  U32

#
# How an argument of a self-call compares with the parameter's column: 0
# the same, 1 smaller (a part of it), 2 not known to be smaller.
@unsafe
def term_descend(+book: Book, q: Q, arg: Tm, +col: Tm) -> U32:
  match q:
    case QNone{}:
      0
    case other:
      descend.go(book, descend.lit(term_strip(arg), term_strip(col)), term_strip(col))

def descend.var(a: Tm, +i: U32) -> U32:
  match a:
    case Var{k, j, s}:
      Bool.pick(U32, U32.is_eq(i, j), 0, 2)
    case other:
      2

def descend.same(+a: Tm, +k: String, +xs: List<&2, Tm>) -> Bool:
  match a:
    case Ctr{+k2, +ys, s}:
      Bool.and(String.eq(k, k2), Nat.is_eq(List.length(&2, Tm, xs), List.length(&2, Tm, ys)))
    case other:
      False{}

def Ctr.xs(t: Tm) -> List<&2, Tm>:
  match t:
    case Ctr{k, xs, s}:
      xs
    case other:
      Nil{}

law descend.sub:
  for +book: Book
  for +a: Tm
  for ps: List<&2, Tm>
  U32

@unsafe
def descend.sub.if(+book: Book, +a: Tm, ps: List<&2, Tm>, gt: Bool) -> U32:
  match gt:
    case True{}:
      descend.sub(book, a, ps)
    case False{}:
      1

# Whether a is (within) one of the fields ps: then it is smaller.
@unsafe
def descend.sub(book, a, ps):
  match ps:
    case Nil{}:
      2
    case p <> t:
      descend.sub.if(book, a, t, U32.is_eq(term_descend(book, QLone{}, a, p), 2))

@unsafe
def descend.ctr.fields(+book: Book, +a: Tm, +xs: List<&2, Tm>, +ord: U32) -> U32:
  Bool.pick(U32, U32.is_eq(ord, 2), descend.sub(book, a, xs), ord)

law descend.fields:
  for +book: Book
  for as: List<&2, Tm>
  for ps: List<&2, Tm>
  for +ord: U32
  U32

@unsafe
def descend.ctr(+book: Book, +a: Tm, +k: String, +xs: List<&2, Tm>, same: Bool) -> U32:
  match same:
    case True{}:
      descend.ctr.fields(book, a, xs, descend.fields(book, Ctr.xs(a), xs, 0))
    case False{}:
      descend.sub(book, a, xs)

@unsafe
def descend.go(book, a, p):
  match p:
    case Var{k, +i, s}:
      descend.var(a, i)
    case Ctr{+k, +xs, s}:
      descend.ctr(book, a, k, xs, descend.same(a, k, xs))
    case other:
      2

@unsafe
def descend.fields.next(+book: Book, as: List<&2, Tm>, ps: List<&2, Tm>, +ord: U32, stop: Bool) -> U32:
  match stop:
    case True{}:
      2
    case False{}:
      descend.fields(book, as, ps, ord)

@unsafe
def descend.fields.step(+book: Book, as: List<&2, Tm>, ps: List<&2, Tm>, +ord: U32, +fld: U32) -> U32:
  descend.fields.next(book, as, ps, Bool.pick(U32, U32.is_eq(fld, 0), ord, fld), U32.is_eq(fld, 2))

@unsafe
def descend.fields(book, as, ps, ord):
  match as ps:
    case a <> at p <> pt:
      descend.fields.step(book, at, pt, ord, term_descend(book, QLone{}, a, p))
    case x y:
      ord

def cl.cols(t: Tm) -> List<&2, Tm>:
  term_args(t)

law descend.args:
  for +book: Book
  for qs: List<&2, Q>
  for sp: List<&2, Tm>
  for cols: List<&2, Tm>
  for +ord: U32
  U32

@unsafe
def descend.args.if(+book: Book, qs: List<&2, Q>, sp: List<&2, Tm>, cols: List<&2, Tm>, +ord: U32, +o: U32, eq: Bool) -> U32:
  match eq:
    case True{}:
      descend.args(book, qs, sp, cols, ord)
    case False{}:
      o

@unsafe
def descend.args.step(+book: Book, qs: List<&2, Q>, sp: List<&2, Tm>, cols: List<&2, Tm>, +ord: U32, +o: U32) -> U32:
  descend.args.if(book, qs, sp, cols, ord, o, U32.is_eq(o, 0))

@unsafe
def descend.args(book, qs, sp, cols, ord):
  match qs sp cols:
    case q <> qt x <> xt c <> ct:
      descend.args.step(book, qt, xt, ct, ord, term_descend(book, q, x, c))
    case a b c:
      ord

def CL.decreases(+book: Book, l: CL, sp: List<&2, Tm>) -> Bool:
  CL{t, n, dn, qs, u, z} = l
  U32.is_eq(descend.args(book, qs, sp, cl.cols(t), 0), 1)

def IR.ty(r: IR) -> Tm:
  IR{ty, us, x} = r
  ty

def IR.us(r: IR) -> List<&2, Us>:
  IR{ty, us, x} = r
  us

def infer.var.go(+t: Tm, +i: U32, +qt: Q, +ctx: List<&2, Tm>, +s: Sp, +l: CL, m: Maybe<&2, Tm>) -> K(IR):
  match m:
    case None{}:
      K.err(IR, ctx, MStr{"a bound variable"}, MTm{t}, s, CL.dn(l))
    case Some{ty}:
      K.pure(IR, IR{ty, uses_one(i, qt), 0n})

def infer.var(+t: Tm, +i: U32, +qt: Q, +ctx: List<&2, Tm>, +s: Sp, +l: CL) -> K(IR):
  infer.var.go(t, i, qt, ctx, s, l, ctx_get(ctx, i))

def infer.fail(+l: CL, +tm: Tm, +ctx: List<&2, Tm>) -> K(IR):
  do K<IR>:
    book : Book <- K.book()
    +t : Tm <- K.pure(Tm, lit.to_ctr(tm))
    +undeclared : Bool <- K.pure(Bool, Bool.and(Tm.is_ctr(t),
      Bool.not(Maybe.is_some(&2, CtrD, book_ctr(book, Tm.name(t))))))
    K.err(IR, ctx, MStr{Bool.pick(String, undeclared, "a declared constructor", "an annotated term (cannot infer)")},
      MTm{tm}, Tm.span(tm), CL.dn(l))

def Tld.x_of(t: Tld) -> Nat:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      x
    case other:
      0n

def Tld.is_open(t: Tld) -> Bool:
  match t:
    case TDef{n, x, ty, None{}, u, b, None{}}:
      True{}
    case other:
      False{}

def Tld.is_base(t: Tld) -> Bool:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      b
    case other:
      False{}

def List.drop_tm(xs: List<&2, Tm>, n: Nat) -> List<&2, Tm>:
  match xs n:
    case ys 0n:
      ys
    case y <> t 1n+m:
      List.drop_tm(t, m)
    case Nil{} k:
      Nil{}

def infer.ref.fin(+l: CL, +k: String, +s: Sp, b: Bool, +tld: Tld, +ctx: List<&2, Tm>, +x: Nat) -> K(IR):
  match tld:
    case TADT{n, g, ty, cs, tbase}:
      K.if(IR, Nat.is_gt(n, 0n), K.err(IR, ctx, MStr{"a family instance (write " ++ k ++ "<..>)"},
        MTm{Ref{k, s, b}}, s, CL.dn(l)), K.pure(IR, IR{ty, Nil{}, x}))
    case TDef{n, dx, ty, v, u, bb, imps}:
      K.pure(IR, IR{ty, Nil{}, x})

# Whether this is a self-call (of a def that is not @unsafe) that shrinks
# no argument.
def infer.ref.bad_self(+book: Book, l: CL, sp: List<&2, Tm>, self: Bool) -> Bool:
  match self:
    case True{}:
      Bool.not(CL.decreases(book, l, sp))
    case False{}:
      False{}

# A self-call of a def that is not @unsafe must shrink an argument.
def infer.ref.self(
  +l: CL, +k: String, +s: Sp, +b: Bool, +tld: Tld, +ctx: List<&2, Tm>, sp: List<&2, Tm>, +x: Nat
) -> K(IR):
  do K<IR>:
    book : Book <- K.book()
    K.if(Unit, infer.ref.bad_self(book, l, sp, Bool.and(String.eq(k, CL.dn(l)), Bool.not(CL.u(l)))),
      K.err(Unit, ctx, MStr{"a decreasing self-call (arguments are read left to right: each passed unchanged until one shrinks)"},
        MTm{Ref{k, s, b}}, s, CL.dn(l)), K.pure(Unit, Unit{}))
    infer.ref.fin(l, k, s, b, tld, ctx, x)

law def_inst:
  for +l: CL
  for +tm: Tm
  for +tld: Tld
  for +sp: List<&2, Tm>
  for +ctx: List<&2, Tm>
  for +d: U32
  K(String)

@unsafe
def infer.ref.inst(
  +l: CL, +k: String, +s: Sp, +b: Bool, +tld: Tld, +qt: Q, +ctx: List<&2, Tm>, +d: U32, +sp: List<&2, Tm>
) -> K(IR):
  do K<IR>:
    +o : String <- def_inst(l, Ref{k, s, b}, tld, sp, ctx, d)
    book : Book <- K.book()
    +x : Nat <- K.pure(Nat, Tld.x_of(tld))
    infer.ref.self(l, o, s, b, Maybe.default(&2, Tld, book_tld(book, o), tld), ctx, List.drop_tm(sp, x), x)

@unsafe
def infer.ref.live(
  +l: CL, +k: String, +s: Sp, +b: Bool, +tld: Tld, +qt: Q, +ctx: List<&2, Tm>, +d: U32, +sp: List<&2, Tm>
) -> K(IR):
  do K<IR>:
    book : Book <- K.book()
    +caller_x : Nat <- K.pure(Nat, Tld.x(book_tld(book, CL.dn(l))))
    +gen : Bool <- K.pure(Bool, Bool.and(Nat.is_gt(Tld.x_of(tld), 0n), Nat.is_eq(0n, caller_x)))
    +self : Bool <- K.pure(Bool, String.eq(k, CL.dn(l)))
    K.if(Unit, Bool.and(Bool.and(Tld.is_open(tld), Bool.not(self)),
      Bool.or(Bool.and(Bool.not(Tld.is_base(tld)), Bool.not(CL.u(l))), gen)),
      K.err(Unit, ctx, MStr{"a filled definition (an unfilled law is a dead claim: live code cannot use it)"},
        MTm{Ref{k, s, b}}, s, CL.dn(l)), K.pure(Unit, Unit{}))
    K.if(IR, gen, infer.ref.inst(l, k, s, b, tld, qt, ctx, d, sp), infer.ref.self(l, k, s, b, tld, ctx, sp, 0n))

@unsafe
def infer.ref(
  +l: CL, +k: String, +s: Sp, +b: Bool, t: Maybe<&2, Tld>, +qt: Q, +ctx: List<&2, Tm>, +d: U32, sp: List<&2, Tm>
) -> K(IR):
  match t:
    case None{}:
      K.err(IR, ctx, MStr{"a defined name"}, MTm{Ref{k, s, b}}, s, CL.dn(l))
    case Some{+tld}:
      K.if(IR, Q.is_none(qt), infer.ref.fin(l, k, s, b, tld, ctx, 0n),
        infer.ref.live(l, k, s, b, tld, qt, ctx, d, sp))

law infer.app:
  for +l: CL
  for fi: IR
  for +x: Tm
  for +qt: Q
  for +ctx: List<&2, Tm>
  for +d: U32
  for +s: Sp
  K(IR)

law infer.adt:
  for +l: CL
  for +ad: AD
  for +k: String
  for +xs: List<&2, Tm>
  for +s: Sp
  for +qt: Q
  for +ctx: List<&2, Tm>
  for +d: U32
  K(IR)

law term_infer:
  for +l: CL
  for tm: Tm
  for +qt: Q
  for +ctx: List<&2, Tm>
  for +d: U32
  for sp: List<&2, Tm>
  K(IR)

@unsafe
def term_infer(l, tm, qt, ctx, d, sp):
  match tm:
    case Cel{k, s, v}:
      term_infer(l, v, qt, ctx, d, sp)
    case Var{+k, +i, +s}:
      infer.var(Var{k, i, s}, i, qt, ctx, s, l)
    case VRf{+k, +i, +s, r}:
      infer.var(Var{k, i, s}, i, qt, ctx, s, l)
    case Ref{+k, +s, b}:
      do K<IR>:
        book : Book <- K.book()
        infer.ref(l, k, s, b, book_tld(book, k), qt, ctx, d, sp)
    case Typ{g, s}:
      do K<IR>:
        u : List<&2, Us> <- term_check(l, g, QNone{}, Qnt{s}, ctx, d)
        return IR{typ(QLone{}), Nil{}, 0n}
    case Qnt{s}:
      K.pure(IR, IR{typ(QLone{}), Nil{}, 0n})
    case TQua{q, s}:
      K.pure(IR, IR{Qnt{s}, Nil{}, 0n})
    case Min{a, b, +s}:
      do K<IR>:
        ua : List<&2, Us> <- term_check(l, a, qt, Qnt{s}, ctx, d)
        ub : List<&2, Us> <- term_check(l, b, qt, Qnt{s}, ctx, d)
        return IR{Qnt{s}, uses_add(ua, ub), 0n}
    case All{+q, +k, i, +a, b, +s}:
      do K<IR>:
        ua : List<&2, Us> <- term_check(l, a, QNone{}, typ(lhs_kind(l, q)), ctx, d)
        book : Book <- K.book()
        ub : List<&2, Us> <- term_check(l, clo_apply(book, b, [Var{k, d, NoSp{}}]), QNone{}, typ(QLone{}),
          ctx_bind(ctx, d, q, k, a), U32.inc(d))
        return IR{typ(QLone{}), Nil{}, 0n}
    case TApp{f, +x, +s}:
      do K<IR>:
        fi : IR <- term_infer(l, f, qt, ctx, d, x <> sp)
        infer.app(l, fi, x, qt, ctx, d, s)
    case ADT{+k, +xs, +s, r}:
      do K<IR>:
        +ad : AD <- book_adt(ADT{k, xs, s, r}, ctx, CL.dn(l))
        infer.adt(l, ad, k, xs, s, qt, ctx, d)
    case Eql{+a, +b, +t, s}:
      do K<IR>:
        ut : List<&2, Us> <- term_check(l, t, QNone{}, typ(QLone{}), ctx, d)
        ua : List<&2, Us> <- term_check(l, a, QNone{}, t, ctx, d)
        ub : List<&2, Us> <- term_check(l, b, QNone{}, t, ctx, d)
        return IR{typ(QMany{}), Nil{}, 0n}
    case Ann{x, +t, s}:
      do K<IR>:
        ut : List<&2, Us> <- term_check(l, t, QNone{}, typ(QLone{}), ctx, d)
        u : List<&2, Us> <- term_check(l, x, qt, t, ctx, d)
        return IR{t, u, 0n}
    case other:
      infer.fail(l, other, ctx)

@unsafe
def infer.app.go(
  +l: CL, fw: Tm, +fty: Tm, fus: List<&2, Us>, +x: Tm, +qt: Q, +ctx: List<&2, Tm>, +d: U32, +s: Sp
) -> K(IR):
  match fw:
    case All{q, k, i, a, b, as}:
      do K<IR>:
        ux : List<&2, Us> <- term_check(l, x, quant_dem(q, qt), a, ctx, d)
        book : Book <- K.book()
        return IR{clo_apply(book, b, [x]), uses_add(fus, ux), 0n}
    case other:
      K.err(IR, ctx, MStr{"a function type"}, MTm{fty}, s, CL.dn(l))

@unsafe
def infer.app(l, fi, x, qt, ctx, d, s):
  IR{+fty, fus, fx} = fi
  match fx:
    case 1n+m:
      K.pure(IR, IR{fty, fus, m})
    case 0n:
      do K<IR>:
        book : Book <- K.book()
        infer.app.go(l, term_wnf(book, fty), fty, fus, x, qt, ctx, d, s)

def AD.n(+a: AD) -> Nat:
  AD{+n, g, t, cs} = a
  n

def AD.t(+a: AD) -> Tm:
  AD{n, g, +t, cs} = a
  t

def infer.adt.fin(r: List<&2, Us> & Tm) -> IR:
  (us, tel) = r
  IR{tel, us, 0n}

@unsafe
def infer.adt.go(+l: CL, +ad: AD, xs: List<&2, Tm>, +s: Sp, +qt: Q, +ctx: List<&2, Tm>, +d: U32) -> K(IR):
  do K<IR>:
    r : List<&2, Us> & Tm <- tele_check(l, AD.t(ad), xs, qt, ctx, d, s, Nil{})
    return infer.adt.fin(r)

@unsafe
def infer.adt(l, ad, k, xs, s, qt, ctx, d):
  K.if(IR, Nat.is_eq(List.length(&2, Tm, xs), AD.n(ad)), infer.adt.go(l, ad, xs, s, qt, ctx, d),
    K.err(IR, ctx, MStr{k ++ " with " ++ Nat.show(AD.n(ad)) ++ Bool.pick(String, Nat.is_eq(AD.n(ad), 1n),
      " parameter", " parameters")}, MTm{ADT{k, xs, s, Nil{}}}, s, CL.dn(l)))

def Tld.dval(t: Tld) -> Maybe<&2, Tm>:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      v
    case other:
      None{}

def Tld.t(t: Tld) -> Tm:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      ty
    case TADT{n, g, ty, cs, tbase}:
      ty

def Tld.is_def(t: Tld) -> Bool:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      True{}
    case other:
      False{}

def Sp.eq(a: Sp, b: Sp) -> Bool:
  match a b:
    case NoSp{} NoSp{}:
      True{}
    case Sp{x, b1, e1} Sp{y, b2, e2}:
      Bool.and(U32.is_eq(b1, b2), U32.is_eq(e1, e2))
    case p q:
      False{}

def Msg.is_kind(m: Msg, +kind: Tm) -> Bool:
  match m kind:
    case MTm{Typ{TQua{q, s}, s2}} Typ{TQua{q2, t}, t2}:
      Bool.and(Q.eq(q, q2), Sp.eq(s, t))
    case x y:
      False{}

def check_kind.err(e: Err, +kind: Tm, +s: Sp) -> Err:
  Err{bok, ctx, +exp, obs, spn, dn, nte} = e
  Err{bok, ctx, exp, obs, Bool.pick(Sp, Msg.is_kind(exp, kind), s, spn), dn, nte}

def check_kind.go(r: Result<&1, &1, Err, List<&2, Us> & Book>, +kind: Tm, +s: Sp) -> Result<&1, &1, Err, Unit & Book>:
  match r:
    case Done{v}:
      Done{(Unit{}, Pair.snd(List<&2, Us>, Book, v))}
    case Fail{e}:
      Fail{check_kind.err(e, kind, s)}

law check_kind:
  for +l: CL
  for +t: Tm
  for q: Q
  for +ctx: List<&2, Tm>
  for +d: U32
  for +s: Sp
  K(Unit)

@unsafe
def check_kind(l, t, q, ctx, d, s):
  +kind = {Typ{TQua{lhs_kind(l, q), s}, s} : Tm}
  b => check_kind.go(term_check(l, t, QNone{}, kind, ctx, d)(b), kind, s)

def check.infer.cmp(+l: CL, +tm: Tm, xi: IR, +ty: Tm, +ctx: List<&2, Tm>, +d: U32, ok: Bool) -> K(List<&2, Us>):
  IR{xty, xus, x} = xi
  match ok:
    case True{}:
      K.pure(List<&2, Us>, xus)
    case False{}:
      K.err(List<&2, Us>, ctx, MTm{ty}, MTm{xty}, Tm.span(tm), CL.dn(l))

@unsafe
def check.infer(+l: CL, +tm: Tm, +qt: Q, +ty: Tm, +ctx: List<&2, Tm>, +d: U32) -> K(List<&2, Us>):
  do K<List<&2, Us>>:
    +xi : IR <- term_infer(l, tm, qt, ctx, d, Nil{})
    book : Book <- K.book()
    check.infer.cmp(l, tm, xi, ty, ctx, d, term_compare(True{}, book, IR.ty(xi), ty, d))

# The values of a let, each inferred in the outer context.
@unsafe
def check.lets(
  +l: CL, ks: List<&2, String>, vs: List<&2, Tm>, qs: List<&2, Q>, +qt: Q, +ctx0: List<&2, Tm>, fctx: List<&2, Tm>,
  +d: U32, +j: U32, us: List<&2, Us>
) -> K(List<&2, Tm> & List<&2, Us>):
  match ks vs qs:
    case +k <> kt v <> vt +q <> qt2:
      do K<List<&2, Tm> & List<&2, Us>>:
        +vi : IR <- term_infer(l, v, quant_dem(q, qt), ctx0, d, Nil{})
        check_kind(l, IR.ty(vi), q, ctx0, d, NoSp{})
        check.lets(l, kt, vt, qt2, qt, ctx0, ctx_bind(fctx, (d + j : U32), q, k, IR.ty(vi)), d, U32.inc(j),
          uses_add(us, IR.us(vi)))
    case a b c:
      K.pure(List<&2, Tm> & List<&2, Us>, (fctx, us))

def let.vars(ks: List<&2, String>, vs: List<&2, Tm>, +d: U32) -> List<&2, Tm>:
  match ks vs:
    case k <> kt v <> vt:
      VRf{k, d, NoSp{}, v} <> let.vars(kt, vt, U32.inc(d))
    case a b:
      Nil{}

def check.let.used(
  +l: CL, ks: List<&2, String>, qs: List<&2, Q>, +ctx: List<&2, Tm>, +d: U32, +s: Sp, +fu: List<&2, Us>
) -> K(List<&2, Us>):
  match ks qs:
    case +k <> kt q <> qt:
      do K<List<&2, Us>>:
        quant_used(ctx, k, q, uses_get(fu, d), s, CL.dn(l))
        check.let.used(l, kt, qt, ctx, U32.inc(d), s, uses_del(fu, d))
    case a b:
      K.pure(List<&2, Us>, fu)

@unsafe
def check.let.body(
  +l: CL, +ks: List<&2, String>, vs: List<&2, Tm>, f: Tm, +s: Sp, +qs: List<&2, Q>, +qt: Q, +ty: Tm,
  +ctx: List<&2, Tm>, +d: U32, r: List<&2, Tm> & List<&2, Us>
) -> K(List<&2, Us>):
  (fctx, us) = r
  +n = U32.from_nat(List.length(&2, String, ks))
  do K<List<&2, Us>>:
    book : Book <- K.book()
    fu : List<&2, Us> <- term_check(l, clo_apply(book, f, let.vars(ks, vs, d)), qt, ty, fctx, (d + n : U32))
    fu2 : List<&2, Us> <- check.let.used(l, ks, qs, ctx, d, s, fu)
    return uses_add(us, fu2)

def check.typeless(-A: Type, +l: CL, +tm: Tm, +ty: Tm, +ctx: List<&2, Tm>, +s: Sp) -> K(A):
  do K<A>:
    book : Book <- K.book()
    K.err(A, ctx, MTm{ty}, MStr{typeless_show(book, ctx, tm)}, s, CL.dn(l))

def check.rfl(+l: CL, +s: Sp, tw: Tm, +ty: Tm, +ctx: List<&2, Tm>, +d: U32) -> K(List<&2, Us>):
  match tw:
    case Eql{+a, +b, t, es}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        K.if(List<&2, Us>, term_compare(False{}, book, a, b, d), K.pure(List<&2, Us>, Nil{}),
          K.err(List<&2, Us>, ctx, MTm{a}, MTm{b}, s, CL.dn(l)))
    case other:
      check.typeless(List<&2, Us>, l, Rfl{s}, ty, ctx, s)

law check.mat:
  for +l: CL
  for +k: String
  for h: Tm
  for m: Tm
  for +s: Sp
  for +tall: Tm
  for +ak: String
  for +axs: List<&2, Tm>
  for +r: List<&2, String>
  for c: Maybe<&2, CtrD>
  for +qt: Q
  for +ty: Tm
  for +ctx: List<&2, Tm>
  for +d: U32
  K(List<&2, Us>)

@unsafe
def check.elim.go(
  +l: CL, tm: Tm, +s: Sp, +tall: Tm, +ak: String, +axs: List<&2, Tm>, +r: List<&2, String>, +rem: List<&2, CtrD>,
  +qt: Q, +ty: Tm, +ctx: List<&2, Tm>, +d: U32
) -> K(List<&2, Us>):
  match tm:
    case Efq{es}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        K.if(List<&2, Us>, Lazy.and(Bool.not(Lst.empty(&2, CtrD, rem)), u => Bool.not(ctx_dead(book, ctx))),
          K.err(List<&2, Us>, ctx, MStr{"cases for " ++ String.join(CtrD.names(rem), ", ")}, MTm{Efq{es}}, s, CL.dn(l)),
          K.pure(List<&2, Us>, Nil{}))
    case Mat{+k, h, m, ms}:
      check.mat(l, k, h, m, s, tall, ak, axs, r, ctrs_find(rem, k), qt, ty, ctx, d)
    case other:
      K.pure(List<&2, Us>, Nil{})

@unsafe
def check.elim.adt(
  +l: CL, +tm: Tm, +s: Sp, +tall: Tm, aw: Tm, +qt: Q, +ty: Tm, +ctx: List<&2, Tm>, +d: U32
) -> K(List<&2, Us>):
  match aw:
    case ADT{+ak, +axs, as, +r}:
      do K<List<&2, Us>>:
        +ad : AD <- book_adt(ADT{ak, axs, as, r}, ctx, CL.dn(l))
        check.elim.go(l, tm, s, tall, ak, axs, r, AD.cs(ad), qt, ty, ctx, d)
    case other:
      K.err(List<&2, Us>, ctx, MStr{"a datatype"}, MTm{All.a(tall)}, s, CL.dn(l))

# A match (or an empty one) checks against a function type on a datatype.
@unsafe
def check.elim(+l: CL, +tm: Tm, +s: Sp, tw: Tm, +qt: Q, +ty: Tm, +ctx: List<&2, Tm>, +d: U32) -> K(List<&2, Us>):
  match tw:
    case All{+q, +k, +i, +a, +b, as}:
      do K<List<&2, Us>>:
        K.if(Unit, Bool.and(Bool.not(Q.is_none(qt)), Q.is_none(q)),
          K.err(Unit, ctx, MStr{"a live scrutinee (a - scrutinee matches only in a dead region)"}, MNone{}, s, CL.dn(l)),
          K.pure(Unit, Unit{}))
        book : Book <- K.book()
        check.elim.adt(l, tm, s, All{q, k, i, a, b, as}, term_wnf(book, a), qt, ty, ctx, d)
    case other:
      check.typeless(List<&2, Us>, l, tm, ty, ctx, s)

law check.lam:
  for +l: CL
  for +k: String
  for f: Tm
  for +s: Sp
  for lq: Q
  for tw: Tm
  for +qt: Q
  for +ty: Tm
  for +ctx: List<&2, Tm>
  for +d: U32
  K(List<&2, Us>)

law check.ctr:
  for +l: CL
  for +k: String
  for +xs: List<&2, Tm>
  for +s: Sp
  for tw: Tm
  for +qt: Q
  for +ty: Tm
  for +ctx: List<&2, Tm>
  for +d: U32
  K(List<&2, Us>)

law check.lit:
  for +l: CL
  for +lit: Tm
  for tw: Tm
  for +qt: Q
  for +ty: Tm
  for +ctx: List<&2, Tm>
  for +d: U32
  K(List<&2, Us>)

law check.rwt:
  for +l: CL
  for +e: Tm
  for +p: Tm
  for f: Tm
  for +s: Sp
  for ei: IR
  for ew: Tm
  for +qt: Q
  for +ty: Tm
  for +ctx: List<&2, Tm>
  for +d: U32
  K(List<&2, Us>)

@unsafe
def term_check(l, tm, qt, ty, ctx, d):
  match tm:
    case Cel{k, s, v}:
      term_check(l, v, qt, ty, ctx, d)
    case Lam{+k, i, f, +s, q}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        check.lam(l, k, f, s, q, term_wnf(book, ty), qt, ty, ctx, d)
    case Let{+ks, ids, +vs, f, +s, +qs}:
      do K<List<&2, Us>>:
        r : List<&2, Tm> & List<&2, Us> <- check.lets(l, ks, vs, qs, qt, ctx, ctx, d, 0, Nil{})
        check.let.body(l, ks, vs, f, s, qs, qt, ty, ctx, d, r)
    case Ctr{+k, +xs, +s}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        check.ctr(l, k, xs, s, term_wnf(book, ty), qt, ty, ctx, d)
    case Lit{+v, +s}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        check.lit(l, Lit{v, s}, term_wnf(book, ty), qt, ty, ctx, d)
    case Mat{+k, +h, +m, +s}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        check.elim(l, Mat{k, h, m, s}, s, term_wnf(book, ty), qt, ty, ctx, d)
    case Efq{+s}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        check.elim(l, Efq{s}, s, term_wnf(book, ty), qt, ty, ctx, d)
    case Rfl{+s}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        check.rfl(l, s, term_wnf(book, ty), ty, ctx, d)
    case Hol{+k, +s}:
      K.if(List<&2, Us>, String.eq(k, "TODO"), K.pure(List<&2, Us>, Nil{}),
        K.err(List<&2, Us>, ctx, MTm{ty}, MTm{Hol{k, s}}, s, CL.dn(l)))
    case Rwt{+e, +p, f, +s}:
      do K<List<&2, Us>>:
        +ei : IR <- term_infer(l, e, qt, ctx, d, Nil{})
        book : Book <- K.book()
        check.rwt(l, e, p, f, s, ei, term_wnf(book, IR.ty(ei)), qt, ty, ctx, d)
    case other:
      check.infer(l, other, qt, ty, ctx, d)

def CL.under(+l: CL, +x: Tm) -> K(CL):
  CL{+t, +n, +dn, +qs, +u, +z} = l
  match n:
    case 0n:
      K.pure(CL, CL{t, n, dn, qs, u, z})
    case 1n+m:
      do K<CL>:
        book : Book <- K.book()
        return CL{term_apply1(book, t, x), m, dn, qs, u, z}

@unsafe
def check.lam(l, k, f, s, lq, tw, qt, ty, ctx, d):
  match tw:
    case All{+q, ak, ai, +a, b, as}:
      +x = {Var{k, d, NoSp{}} : Tm}
      +many = Bool.and(Q.is_many(lq), Q.is_lone(q))
      +q2 = Bool.pick(Q, many, QMany{}, q)
      do K<List<&2, Us>>:
        K.if(Unit, many, check_kind(l, a, q2, ctx, d, s), K.pure(Unit, Unit{}))
        fl : CL <- CL.under(l, x)
        +book : Book <- K.book()
        +u : List<&2, Us> <- term_check(fl, clo_apply(book, f, [x]), qt, clo_apply(book, b, [x]),
          ctx_bind(ctx, d, q2, k, a), U32.inc(d))
        quant_used(ctx, k, q2, uses_get(u, d), s, CL.dn(l))
        return uses_del(u, d)
    case other:
      check.typeless(List<&2, Us>, l, Lam{k, 0, f, s, lq}, ty, ctx, s)

@unsafe
def check.ctr.fields(
  +l: CL, ct: Tm, xs: List<&2, Tm>, +s: Sp, axs: List<&2, Tm>, +qt: Q, +ctx: List<&2, Tm>, +d: U32
) -> K(List<&2, Us>):
  do K<List<&2, Us>>:
    +tel : Tm <- tele_fill(ct, axs, ctx, CL.dn(l), s)
    r : List<&2, Us> & Tm <- tele_check(l, tel, xs, qt, ctx, d, s, Nil{})
    return Pair.fst(List<&2, Us>, Tm, r)

@unsafe
def check.ctr.find(
  +l: CL, +k: String, +xs: List<&2, Tm>, +s: Sp, +ak: String, +axs: List<&2, Tm>, +cs: List<&2, CtrD>,
  c: Maybe<&2, CtrD>, +qt: Q, +ty: Tm, +ctx: List<&2, Tm>, +d: U32
) -> K(List<&2, Us>):
  match c:
    case None{}:
      do K<List<&2, Us>>:
        +book : Book <- K.book()
        K.if(List<&2, Us>, Maybe.is_some(&2, CtrD, book_ctr(book, k)),
          K.err(List<&2, Us>, ctx, MTm{ty}, MTm{Ref{book_fam(book, k), s, False{}}}, s, CL.dn(l)),
          K.err(List<&2, Us>, ctx, MStr{"a declared constructor (" ++ ak ++ " declares " ++
            String.join(CtrD.names(cs), ", ") ++ ")"}, MTm{Ctr{k, xs, s}}, s, CL.dn(l)))
    case Some{CtrD{ck, +n, ct}}:
      K.if(List<&2, Us>, Nat.is_eq(n, List.length(&2, Tm, xs)), check.ctr.fields(l, ct, xs, s, axs, qt, ctx, d),
        K.err(List<&2, Us>, ctx, MStr{k ++ " with " ++ Nat.show(n) ++ Bool.pick(String, Nat.is_eq(n, 1n), " field",
          " fields")}, MTm{Ctr{k, xs, s}}, s, CL.dn(l)))

@unsafe
def check.ctr(l, k, xs, s, tw, qt, ty, ctx, d):
  match tw:
    case ADT{+ak, +axs, as, +r}:
      do K<List<&2, Us>>:
        +ad : AD <- book_adt(ADT{ak, axs, as, r}, ctx, CL.dn(l))
        book : Book <- K.book()
        check.ctr.find(l, k, xs, s, ak, axs, AD.cs(ad), ctrs_find(AD.cs(ad), k), qt, ty, ctx, d)
    case other:
      do K<List<&2, Us>>:
        +book : Book <- K.book()
        K.if(List<&2, Us>, Maybe.is_some(&2, CtrD, book_ctr(book, k)),
          K.err(List<&2, Us>, ctx, MTm{ty}, MTm{Ref{book_fam(book, k), s, False{}}}, s, CL.dn(l)),
          check.typeless(List<&2, Us>, l, Ctr{k, xs, s}, ty, ctx, s))

def lit.ctr(v: LV) -> String:
  match v:
    case LNat{0n}:
      "Zero"
    case LNat{n}:
      "Succ"
    case LStr{SNil{}}:
      "SNil"
    case LStr{s}:
      "SCon"

def Lit.v(t: Tm) -> LV:
  match t:
    case Lit{v, s}:
      v
    case other:
      LNat{0n}

# Whether the datatype is Base's (its literal needs no expansion).
def check.lit.base_adt(cs: List<&2, CtrD>) -> Bool:
  True{}

def check.lit.base(t: Maybe<&2, Tld>, +r: List<&2, String>, +c: String) -> Bool:
  match t:
    case Some{TADT{n, g, ty, +cs, tbase}}:
      Bool.and(check.lit.base_adt(cs), Maybe.is_some(&2, CtrD, ctrs_find(ctrs_drop(cs, r), c)))
    case other:
      False{}

@unsafe
def check.lit(l, lit, tw, qt, ty, ctx, d):
  match tw:
    case ADT{+ak, axs, as, +r}:
      do K<List<&2, Us>>:
        book : Book <- K.book()
        K.if(List<&2, Us>, check.lit.base(book_tld(book, ak), r, lit.ctr(Lit.v(lit))), K.pure(List<&2, Us>, Nil{}),
          term_check(l, lit_step(lit), qt, ty, ctx, d))
    case other:
      term_check(l, lit_step(lit), qt, ty, ctx, d)

@unsafe
def check.rwt(l, e, p, f, s, ei, ew, qt, ty, ctx, d):
  match ew:
    case Eql{+a, +b, +t, es}:
      do K<List<&2, Us>>:
        up : List<&2, Us> <- term_check(l, p, QNone{}, All{QLone{}, "_", 0, t, CRwt{a, t, s}, s}, ctx, d)
        +book : Book <- K.book()
        +bg : Tm <- K.pure(Tm, term_apply1(book, term_apply1(book, p, b), e))
        K.if(Unit, term_compare(True{}, book, bg, ty, d), K.pure(Unit, Unit{}),
          K.err(Unit, ctx, MTm{ty}, MTm{bg}, s, CL.dn(l)))
        uf : List<&2, Us> <- term_check(l, f, qt, term_apply1(book, term_apply1(book, p, a), Rfl{s}), ctx, d)
        return uses_add(IR.us(ei), uf)
    case other:
      K.err(List<&2, Us>, ctx, MStr{"an equation {a == b : T}"}, MTm{IR.ty(ei)}, Sp.or(Tm.span(e), s), CL.dn(l))

def CL.ext(+l: CL, +k: String, +n: Nat) -> K(CL):
  CL{+t, +ln, +dn, +qs, +u, +z} = l
  match ln:
    case 0n:
      K.pure(CL, CL{t, ln, dn, qs, u, z})
    case 1n+m:
      do K<CL>:
        book : Book <- K.book()
        return CL{lhs_ext(book, t, k, n, Nil{}), Nat.add(m, n), dn, qs, u, z}

@unsafe
def check.mat(l, k, h, m, s, tall, ak, axs, r, c, qt, ty, ctx, d):
  match c:
    case None{}:
      K.err(List<&2, Us>, ctx, MStr{"a constructor of " ++ ak ++ " (missing, or already matched)"},
        MTm{Mat{k, h, m, s}}, s, CL.dn(l))
    case Some{CtrD{ck, +n, ct}}:
      do K<List<&2, Us>>:
        +tel : Tm <- tele_fill(ct, axs, ctx, CL.dn(l), s)
        hl : CL <- CL.ext(l, k, n)
        book : Book <- K.book()
        uh : List<&2, Us> <- term_check(hl, h, qt, mat_goal(book, tel, n, Nil{}, All.b(tall), k, s, All.q(tall), ctx,
          CL.dn(l)), ctx, d)
        um : List<&2, Us> <- term_check(l, m, qt, All{All.q(tall), All.k(tall), 0, ADT{ak, axs, s,
          List.append(&2, String, r, [k])}, All.b(tall), s}, ctx, d)
        return uses_join(uh, um)

def mat_goal.dem(q: Q, +tq: Q) -> Q:
  match q:
    case QNone{}:
      QNone{}
    case QLone{}:
      tq
    case other:
      quant_add(tq, tq)

def mat_goal.go(
  t: Tm, m: Nat, xs: List<&2, Tm>, tb: Tm, +ck: String, +cs: Sp, +tq: Q, ctx: List<&2, Tm>, dn: String
) -> Tm:
  match t:
    case All{q, k, i, a, b, s}:
      All{mat_goal.dem(q, tq), k, i, a, CGoal{b, m, xs, tb, ck, cs, tq, ctx, dn}, cs}
    case other:
      Efq{cs}

# The goal of a match case: the motive applied to the constructor, bound
# over its fields (each field as live as the scrutinee).
@unsafe
def mat_goal(book, tel, n, xs, tb, ck, cs, tq, ctx, dn):
  match n:
    case 0n:
      clo_apply(book, tb, [Ctr{ck, xs, cs}])
    case 1n+m:
      mat_goal.go(term_wnf(book, tel), m, xs, tb, ck, cs, tq, ctx, dn)

law term_key:
  for t: Tm
  String

@unsafe
def term_key.list(xs: List<&2, Tm>) -> String:
  match xs:
    case Nil{}:
      ""
    case x <> t:
      term_key(x) ++ "," ++ term_key.list(t)

# A text that is equal for equal lowered terms (the official JSON key).
@unsafe
def term_key(t):
  match t:
    case Var{k, i, s}:
      "V" ++ U32.show(i)
    case Ref{k, s, b}:
      "R" ++ k ++ Bool.pick(String, b, "!", "")
    case Sub{i, p, f, s}:
      term_key(f)
    case Let{ks, ids, vs, f, s, qs}:
      "L(" ++ term_key.list(vs) ++ term_key(syn_body(f)) ++ ")"
    case Typ{g, s}:
      "T(" ++ term_key(g) ++ ")"
    case Qnt{s}:
      "Q"
    case TQua{q, s}:
      "&" ++ show.qua(q)
    case Min{a, b, s}:
      "M(" ++ term_key(a) ++ "," ++ term_key(b) ++ ")"
    case All{q, k, i, a, b, s}:
      "A" ++ quant_show(q) ++ U32.show(i) ++ "(" ++ term_key(a) ++ "," ++ term_key(syn_body(b)) ++ ")"
    case Lam{k, i, f, s, q}:
      "F" ++ quant_show(q) ++ U32.show(i) ++ "(" ++ term_key(syn_body(f)) ++ ")"
    case TApp{f, x, s}:
      "@(" ++ term_key(f) ++ "," ++ term_key(x) ++ ")"
    case ADT{k, xs, s, r}:
      "D" ++ k ++ "(" ++ term_key.list(xs) ++ String.join(r, ",") ++ ")"
    case Ctr{k, xs, s}:
      "C" ++ k ++ "(" ++ term_key.list(xs) ++ ")"
    case Lit{LNat{n}, s}:
      "N" ++ Nat.show(n)
    case Lit{LStr{x}, s}:
      "S\"" ++ show.text(x) ++ "\""
    case Mat{k, h, m, s}:
      "X" ++ k ++ "(" ++ term_key(h) ++ "," ++ term_key(m) ++ ")"
    case Efq{s}:
      "E"
    case Eql{a, b, ty, s}:
      "=(" ++ term_key(a) ++ "," ++ term_key(b) ++ "," ++ term_key(ty) ++ ")"
    case Rfl{s}:
      "r"
    case Rwt{e, p, f, s}:
      "%(" ++ term_key(e) ++ "," ++ term_key(p) ++ "," ++ term_key(f) ++ ")"
    case Hol{k, s}:
      "?" ++ k
    case Ann{x, ty, s}:
      ":(" ++ term_key(x) ++ "," ++ term_key(ty) ++ ")"
    case other:
      "_"

def Book.tmp(+book: Book, +key: String) -> Maybe<&2, String>:
  Book{tlds, ctrs, order, hols, open, +tmps, tcnt} = book
  Map.find(String, tmps, key)

def Book.tcnt(+book: Book, +k: String) -> Nat:
  Book{tlds, ctrs, order, hols, open, tmps, +tcnt} = book
  Maybe.default(&2, Nat, Map.find(Nat, tcnt, k), 0n)

def Book.add_tmp(book: Book, +k: String, key: String, o: String) -> Book:
  Book{tlds, ctrs, order, hols, open, tmps, +tcnt} = book
  +n = Maybe.default(&2, Nat, Map.find(Nat, tcnt, k), 0n)
  Book{tlds, ctrs, order, hols, open, Map.set(&2, String, tmps, key, o), Map.set(&2, Nat, tcnt, k, 1n+n)}

def inst.closed.err.go(e: Err, obs: Msg, +bok: Book, +l: CL, +tm: Tm, +ctx: List<&2, Tm>, +d: U32) -> Err:
  match obs:
    case MTm{Var{k, +i, s}}:
      Bool.pick(Err, U32.is_lt(i, d), err.make(bok, ctx, MStr{"a template applied to closed ~ arguments (" ++ k ++
        " is a variable here, not comptime: pass it at run time)"}, MTm{tm}, Tm.span(tm), CL.dn(l)), e)
    case other:
      e

def inst.closed.err(e: Err, +l: CL, +tm: Tm, +ctx: List<&2, Tm>, +d: U32) -> Err:
  Err{+bok, ectx, exp, +obs, spn, dn, nte} = e
  inst.closed.err.go(Err{bok, ectx, exp, obs, spn, dn, nte}, obs, bok, l, tm, ctx, d)

def inst.closed.go(
  r: Result<&1, &1, Err, List<&2, Us> & Book>, +l: CL, +tm: Tm, +ctx: List<&2, Tm>, +d: U32
) -> Result<&1, &1, Err, List<&2, Us> & Book>:
  match r:
    case Done{v}:
      Done{v}
    case Fail{e}:
      Fail{inst.closed.err(e, l, tm, ctx, d)}

@unsafe
def inst.closed(+l: CL, +tm: Tm, +a: Tm, +ty: Tm, +ctx: List<&2, Tm>, +d: U32) -> K(List<&2, Us>):
  b => inst.closed.go(term_check(l, a, QNone{}, ty, Nil{}, d)(b), l, tm, ctx, d)

# Checks a template's ~ arguments against its telescope; answers the
# instance's type.
@unsafe
def inst.args(+l: CL, +tm: Tm, +tel: Tm, xs: List<&2, Tm>, +ctx: List<&2, Tm>, +d: U32) -> K(Tm):
  match xs:
    case Nil{}:
      K.pure(Tm, tel)
    case +a <> t:
      do K<Tm>:
        +h : Tm <- tele_head(tel, ctx, CL.dn(l), Tm.span(tm))
        u : List<&2, Us> <- inst.closed(l, tm, a, All.a(h), ctx, d)
        book : Book <- K.book()
        inst.args(l, tm, clo_apply(book, All.b(h), [a]), t, ctx, d)

def List.take_tm(xs: List<&2, Tm>, n: Nat) -> List<&2, Tm>:
  match xs n:
    case y <> t 1n+m:
      y <> List.take_tm(t, m)
    case ys k:
      Nil{}

def Tld.dn(t: Tld) -> Nat:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      n
    case other:
      0n

def Tld.du(t: Tld) -> Bool:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      u
    case other:
      False{}

def CL.z(+l: CL) -> Nat:
  CL{t, n, dn, qs, u, +z} = l
  z

@unsafe
def applys(+book: Book, f: Tm, xs: List<&2, Tm>) -> Tm:
  match xs:
    case Nil{}:
      f
    case x <> t:
      applys(book, term_apply1(book, f, x), t)

# Binds a template's ~ parameters to fresh names: the body is checked once,
# for any arguments.
def def_check.tmpl(+k: String, +x: Nat, t: Tm, v: Tm, ty: Tm) -> K(Tm & Tm & Tm):
  match x:
    case 0n:
      K.pure(Tm & Tm & Tm, (t, v, ty))
    case 1n+m:
      do K<Tm & Tm & Tm>:
        +h : Tm <- tele_head(ty, Nil{}, k, NoSp{})
        +o : String <- K.pure(String, k ++ "~" ++ All.k(h))
        +book : Book <- K.book()
        K.if(Unit, book_has(book, o), K.err(Unit, Nil{}, MStr{"a fresh ~ binder name"}, MStr{All.k(h)}, NoSp{}, ""),
          K.pure(Unit, Unit{}))
        K.set_book(book_set(book, o, TDef{0n, 0n, All.a(h), None{}, False{}, True{}, None{}}))
        +b2 : Book <- K.book()
        def_check.tmpl(k, m, TApp{t, Ref{o, NoSp{}, False{}}, NoSp{}}, term_apply1(b2, v, Ref{o, NoSp{}, False{}}),
          clo_apply(b2, All.b(h), [Ref{o, NoSp{}, False{}}]))

# A template's ~ names do not outlive its check.
@unsafe
def def_check.go(+k: String, +tld: Tld, +z: Nat, qs: List<&2, Q>, r: Tm & Tm & Tm, old: Book, tmpl: Bool) -> K(Unit):
  (t, rest) = r
  (v, ty) = rest
  do K<Unit>:
    u : List<&2, Us> <- term_check(CL{t, Nat.sub(Tld.dn(tld), Tld.x_of(tld)), k, qs, Tld.du(tld), z}, v, QLone{}, ty,
      Nil{}, 0)
    b : Book <- K.book()
    K.set_book(Bool.pick(Book, tmpl, old, b))

@unsafe
def def_check(+k: String, +tld: Tld, +z: Nat) -> K(Unit):
  do K<Unit>:
    +book : Book <- K.book()
    +qs : List<&2, Q> <- K.pure(List<&2, Q>, Dom.qs(Pair.fst(List<&2, Dom>, Tm, tele_unbind(book, Tld.t(tld)))))
    r : Tm & Tm & Tm <- def_check.tmpl(k, Tld.x_of(tld), Ref{k, NoSp{}, False{}},
      Maybe.default(&2, Tm, Tld.dval(tld), Efq{NoSp{}}), Tld.t(tld))
    def_check.go(k, tld, z, qs, r, book, Nat.is_gt(Tld.x_of(tld), 0n))

@unsafe
def def_inst.make(+tm: Tm, +tld: Tld, +xs: List<&2, Tm>, +ty: Tm, +key: String, +z: Nat) -> K(String):
  +k = Tm.name(tm)
  do K<String>:
    +book : Book <- K.book()
    +o : String <- K.pure(String, k ++ "~" ++ Nat.show(Book.tcnt(book, k)))
    +n : Nat <- K.pure(Nat, Nat.sub(Tld.dn(tld), Tld.x_of(tld)))
    +v : Tm <- K.pure(Tm, applys(book, Maybe.default(&2, Tm, Tld.dval(tld), Efq{NoSp{}}), xs))
    K.set_book(book_set(Book.add_tmp(book, k, key, o), o, TDef{n, 0n, ty, None{}, Tld.du(tld), False{}, None{}}))
    def_check(o, TDef{n, 0n, ty, Some{v}, Tld.du(tld), False{}, None{}}, z)
    b2 : Book <- K.book()
    K.set_book(book_set(b2, o, TDef{n, 0n, ty, Some{v}, Tld.du(tld), False{}, None{}}))
    return o

@unsafe
def def_inst.new(+l: CL, +tm: Tm, +tld: Tld, +xs: List<&2, Tm>, +ty: Tm, +key: String, +ctx: List<&2, Tm>) ->
  K(String):
  +z = {1n+CL.z(l) : Nat}
  K.if(String, Nat.is_gt(z, 64n),
    K.err(String, ctx, MStr{"a template that stops instantiating itself (64 levels at most)"}, MTm{tm}, Tm.span(tm),
      CL.dn(l)), def_inst.make(tm, tld, xs, ty, key, z))

@unsafe
def def_inst.find(
  +l: CL, +tm: Tm, +tld: Tld, +xs: List<&2, Tm>, +ty: Tm, +key: String, +ctx: List<&2, Tm>, m: Maybe<&2, String>
) -> K(String):
  match m:
    case Some{+o}:
      do K<String>:
        book : Book <- K.book()
        K.if(String, Bool.and(Bool.not(Maybe.is_some(&2, Tm, Tld.dval(Maybe.default(&2, Tld, book_tld(book, o), tld)))),
          Bool.not(String.eq(o, CL.dn(l)))),
          K.err(String, ctx, MStr{"a decreasing self-call (arguments are read left to right: each passed unchanged until one shrinks)"},
            MTm{tm}, Tm.span(tm), CL.dn(l)), K.pure(String, o))
    case None{}:
      def_inst.new(l, tm, tld, xs, ty, key, ctx)

@unsafe
def def_inst.go(+l: CL, +tm: Tm, +tld: Tld, +xs: List<&2, Tm>, +ctx: List<&2, Tm>, +d: U32) -> K(String):
  do K<String>:
    +ty : Tm <- inst.args(l, tm, Tld.t(tld), xs, ctx, d)
    +book : Book <- K.book()
    +key : String <- K.pure(String, term_key.list(lowers(book, xs, 0)))
    K.if(Unit, Nat.is_gt(String.length(key), 32768n),
      K.err(Unit, ctx, MStr{"a ~ argument that stops growing"}, MTm{tm}, Tm.span(tm), CL.dn(l)), K.pure(Unit, Unit{}))
    def_inst.find(l, tm, tld, xs, ty, Tm.name(tm) ++ "\n" ++ key, ctx, Book.tmp(book, Tm.name(tm) ++ "\n" ++ key))

# The instance of a template for its ~ arguments (made and checked once).
@unsafe
def def_inst(l, tm, tld, sp, ctx, d):
  +x = Tld.x_of(tld)
  +xs = List.take_tm(sp, x)
  K.if(String, Nat.is_lt(List.length(&2, Tm, xs), x),
    K.err(String, ctx, MStr{"a template applied to closed ~ arguments (a def parameter is not comptime)"}, MTm{tm},
      Tm.span(tm), CL.dn(l)), def_inst.go(l, tm, tld, xs, ctx, d))

def book_reset(b: Book) -> Book:
  Book{tlds, ctrs, order, hols, open, tmps, tcnt} = b
  Book{MTip{}, MTip{}, order, hols, open, tmps, tcnt}

def Tld.is_law_open(t: Tld) -> Bool:
  match t:
    case TDef{n, x, ty, None{}, u, False{}, None{}}:
      True{}
    case other:
      False{}

def Tld.dec(t: Tld) -> Tld:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      TDef{n, x, ty, None{}, u, b, imps}
    case other:
      other

def Tld.imps(t: Tld) -> Maybe<&2, List<&2, String>>:
  match t:
    case TDef{n, x, ty, v, u, b, imps}:
      imps
    case other:
      None{}

@unsafe
def book_set_ctrs(b: Book, cs: List<&2, CtrD>) -> Book:
  match cs:
    case Nil{}:
      b
    case CtrD{+ck, n, t} <> rest:
      book_set_ctrs(book_set_ctr(b, ck, CtrD{ck, n, t}), rest)

def CL.of(+k: String, u: Bool) -> CL:
  CL{Ref{k, NoSp{}, False{}}, 0n, k, Nil{}, u, 0n}

def valid.kind(+k: String, +ty: Tm, r: List<&2, Dom> & Tm) -> K(Tm):
  (doms, +kind) = r
  match kind:
    case Typ{g, s}:
      K.pure(Tm, Typ{g, s})
    case other:
      K.err(Tm, Dom.ctx(doms, 0, Nil{}), MStr{"a kind (type " ++ k ++ "<..> is Kind(g))"}, MTm{other},
        Sp.or(Tm.span(other), Tm.span(ty)), k)

def valid.tip.var(t: Tm, +d: U32) -> Bool:
  match t:
    case Var{k, i, s}:
      U32.is_eq(i, d)
    case other:
      False{}

def valid.tip.params(+book: Book, xs: List<&2, Tm>, +d: U32) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case x <> t:
      Lazy.and(valid.tip.var(term_wnf(book, x), d), u => valid.tip.params(book, t, U32.inc(d)))

def valid.tip.ok(+book: Book, +k: String, +n: Nat, tip: Tm) -> Bool:
  match tip:
    case ADT{+k2, +xs, s, r}:
      Lazy.and(Bool.and(String.eq(k, k2), Nat.is_eq(List.length(&2, Tm, xs), n)), u => Lazy.and(Lst.empty(&2, String, r), u => valid.tip.params(book, xs, 0)))
    case other:
      False{}

def valid.tip(+k: String, +n: Nat, +ck: String, +tip: Tm, +ctx: List<&2, Tm>) -> K(Unit):
  do K<Unit>:
    book : Book <- K.book()
    K.if(Unit, valid.tip.ok(book, k, n, tip), K.pure(Unit, Unit{}),
      K.err(Unit, ctx, MStr{"a telescope tipped at " ++ k ++ " applied to its own parameters"}, MTm{tip}, NoSp{}, ck))

@unsafe
def valid.fields(
  +k: String, +n: Nat, +kind: Tm, +ck: String, tel: Tm, left: Nat, +d: U32, +ctx: List<&2, Tm>
) -> K(Unit):
  match left:
    case 1n+m:
      do K<Unit>:
        +h : Tm <- tele_head(tel, ctx, ck, NoSp{})
        +q : Q <- K.pure(Q, All.q(h))
        u : List<&2, Us> <- term_check(CL.of(ck, False{}), All.a(h), QNone{},
          Bool.pick(Tm, Bool.and(Nat.is_ge(U32.to_nat(d), n), Q.is_lone(q)), kind, typ(q)), ctx, d)
        book : Book <- K.book()
        valid.fields(k, n, kind, ck, clo_apply(book, All.b(h), [Var{All.k(h), d, NoSp{}}]), m, U32.inc(d),
          ctx_bind(ctx, d, q, All.k(h), All.a(h)))
    case 0n:
      do K<Unit>:
        book : Book <- K.book()
        valid.tip(k, n, ck, term_wnf(book, tel), ctx)

def valid.ctrs(+k: String, +n: Nat, +kind: Tm, cs: List<&2, CtrD>) -> K(Unit):
  match cs:
    case Nil{}:
      K.pure(Unit, Unit{})
    case CtrD{+ck, cn, ct} <> rest:
      do K<Unit>:
        valid.fields(k, n, kind, ck, ct, Nat.add(n, cn), 0, Nil{})
        valid.ctrs(k, n, kind, rest)

def valid.adt(+k: String, +n: Nat, +ty: Tm, cs: List<&2, CtrD>) -> K(Unit):
  do K<Unit>:
    u : List<&2, Us> <- term_check(CL.of(k, False{}), ty, QNone{}, typ(QLone{}), Nil{}, 0)
    book : Book <- K.book()
    r : List<&2, Dom> & Tm <- K.pure(List<&2, Dom> & Tm, tele_unbind(book, ty))
    +kind : Tm <- valid.kind(k, ty, r)
    valid.ctrs(k, n, kind, cs)

@unsafe
def valid.ret(+book: Book, t: Tm, +d: U32) -> Tm:
  match t:
    case All{q, +k, i, a, b, s}:
      valid.ret(book, term_strip(clo_apply(book, b, [Var{k, d, NoSp{}}])), U32.inc(d))
    case other:
      other

def valid.io.base(t: Maybe<&2, Tld>) -> Bool:
  match t:
    case Some{TDef{n, x, ty, v, u, True{}, imps}}:
      True{}
    case other:
      False{}

def valid.io(+book: Book, h: Tm) -> Bool:
  match h:
    case Ref{"IO", s, b}:
      valid.io.base(book_tld(book, "IO"))
    case other:
      False{}

# A foreign def must return Base's IO directly.
def valid.foreign(+k: String, +dd: Tld, m: Maybe<&2, List<&2, String>>) -> K(Unit):
  match m:
    case None{}:
      K.pure(Unit, Unit{})
    case Some{ims}:
      do K<Unit>:
        +book : Book <- K.book()
        +tip : Tm <- K.pure(Tm, valid.ret(book, term_strip(Tld.t(dd)), 0))
        K.if(Unit, valid.io(book, term_head(tip)), K.pure(Unit, Unit{}),
          K.err(Unit, Nil{}, MStr{"a foreign definition returning base IO(...) directly (return type aliases are not unfolded)"},
            MStr{k}, Tm.span(tip), k))

def valid.def(+k: String, +tld: Tld, +fin: Bool) -> K(Unit):
  do K<Unit>:
    +book : Book <- K.book()
    +open : Bool <- K.pure(Bool, Bool.and(fin, Tld.is_law_open(tld)))
    b1 : Book <- K.pure(Book, Bool.pick(Book, open, book_opened(book), book))
    K.set_book(book_set(b1, k, Tld.dec(tld)))
    +dd : Tld <- K.pure(Tld, Bool.pick(Tld, fin, tld, Tld.dec(tld)))
    u : List<&2, Us> <- term_check(CL.of(k, Tld.du(dd)), Tld.t(dd), QNone{}, typ(QLone{}), Nil{}, 0)
    valid.foreign(k, dd, Tld.imps(dd))
    K.if(Unit, Maybe.is_some(&2, Tm, Tld.dval(dd)), def_check(k, dd, 0n), K.pure(Unit, Unit{}))
    b2 : Book <- K.book()
    K.set_book(book_set(b2, k, dd))

def book_valid.one(+k: String, +tld: Tld, fin: Bool) -> K(Unit):
  match tld:
    case TADT{+n, g, +ty, +cs, b}:
      do K<Unit>:
        book : Book <- K.book()
        K.set_book(book_set_ctrs(book_set(book, k, tld), cs))
        valid.adt(k, n, ty, cs)
    case TDef{n, x, ty, v, u, b, imps}:
      valid.def(k, tld, fin)

# Checks every declaration in order: each sees only the ones before it
# (and itself, for recursion).
def book_valid(order: List<&2, String>, +full: Book) -> K(Unit):
  match order:
    case Nil{}:
      K.pure(Unit, Unit{})
    case +k <> +rest:
      do K<Unit>:
        book_valid.one(k, Maybe.default(&2, Tld, book_tld(full, k), TADT{0n, 0n, Qnt{NoSp{}}, Nil{}, False{}}),
          Bool.not(Str.has(rest, k)))
        book_valid(rest, full)

def CtrD.k(c: CtrD) -> String:
  CtrD{k, n, t} = c
  k

type Imp is Data:
  Imp{path: String, alias: String, beg: U32}

def is_ident.rest(s: String) -> Bool:
  match s:
    case SNil{}:
      True{}
    case SCon{Chr{+c}, t}:
      Bool.and(Bool.or(is_head(c), is_digit(c)), is_ident.rest(t))

def is_ident(s: String) -> Bool:
  match s:
    case SNil{}:
      False{}
    case SCon{Chr{+c}, t}:
      Bool.and(is_head(c), is_ident.rest(t))

# An import line: (path, alias); the alias is "" for Base.
def import.base(base: Bool) -> Maybe<&1, String & String>:
  match base:
    case True{}:
      Some{("Base", "")}
    case False{}:
      None{}

def import.as(is_as: Bool, p: String, +a: String) -> Maybe<&1, String & String>:
  match is_as:
    case True{}:
      Bool.pick(Maybe<&1, String & String>, is_ident(a), Some{(p, a)}, None{})
    case False{}:
      None{}

# (String patterns would do, but the official compiler expands them char by
# char, with the other arms copied into each branch.)
def import.parse(ws: List<&2, String>) -> Maybe<&1, String & String>:
  match ws:
    case +w <> Nil{}:
      import.base(String.eq(w, "Base"))
    case p <> +k <> +a <> Nil{}:
      import.as(String.eq(k, "as"), p, a)
    case other:
      None{}

type Hdr is Data:
  Hdr{lines: List<&2, String>, imps: List<&2, Imp>, err: Maybe<&2, Err>}

law header.go:
  for +src: String
  for ls: List<&2, String>
  for +off: Nat
  for done: List<&2, String>
  for imps: List<&2, Imp>
  Hdr

# The imports at the top of a file (each blanked out of its lines).
@unsafe
def header(+src: String) -> Hdr:
  header.go(src, String.split(src, '\n'), 0n, Nil{}, Nil{})

def header.go.rest(t: List<&2, String>, done: List<&2, String>, imps: List<&2, Imp>) -> Hdr:
  Hdr{List.append(&2, String, List.reverse(&2, String, done), t), imps, None{}}

@unsafe
def header.go.next(+src: String, t: List<&2, String>, +off: Nat, done: List<&2, String>, imps: List<&2, Imp>) -> Hdr:
  header.go(src, t, off, done, imps)

@unsafe
def header.rest(
  +src: String, +l: String, t: List<&2, String>, +off: Nat, done: List<&2, String>, imps: List<&2, Imp>, blank: Bool
) -> Hdr:
  match blank:
    case True{}:
      header.go.next(src, t, Nat.add(off, 1n+String.length(l)), l <> done, imps)
    case False{}:
      Hdr{List.append(&2, String, List.reverse(&2, String, l <> done), t), imps, None{}}

@unsafe
def header.imp.go(
  +src: String, +l: String, t: List<&2, String>, +off: Nat, done: List<&2, String>, imps: List<&2, Imp>,
  v: String & String
) -> Hdr:
  (p, a) = v
  +pp = p
  +beg = U32.from_nat(Nat.add(off, Str.index_of(l, pp, 0n)))
  header.go.next(src, t, Nat.add(off, 1n+String.length(l)), "" <> done, List.append(&2, Imp, imps, [Imp{pp, a, beg}]))

@unsafe
def header.imp(
  +src: String, +l: String, t: List<&2, String>, +off: Nat, done: List<&2, String>, imps: List<&2, Imp>, +tl: String,
  m: Maybe<&1, String & String>
) -> Hdr:
  match m:
    case None{}:
      +beg = U32.from_nat(Nat.add(off, Str.index_of(l, tl, 0n)))
      Hdr{Nil{}, Nil{}, Some{err0("an import ('import Base', or 'import <path> as <Name>')", MStr{"'" ++ tl ++ "'"},
        Sp{src, beg, beg})}}
    case Some{v}:
      header.imp.go(src, l, t, off, done, imps, v)

@unsafe
def header.line.go(
  +src: String, +l: String, t: List<&2, String>, +off: Nat, done: List<&2, String>, imps: List<&2, Imp>, +tl: String,
  imp: Bool, blank: Bool
) -> Hdr:
  match imp:
    case True{}:
      header.imp(src, l, t, off, done, imps, tl, import.parse(Str.until_hash(Str.words(String.drop(tl, 6n)))))
    case False{}:
      header.rest(src, l, t, off, done, imps, blank)

@unsafe
def header.line(
  +src: String, +l: String, t: List<&2, String>, +off: Nat, done: List<&2, String>, imps: List<&2, Imp>, +tl: String
) -> Hdr:
  +is_imp = Bool.or(String.eq(tl, "import"), Bool.and(String.starts_with(tl, "import"),
    is_space(Str.first(String.drop(tl, 6n)))))
  header.line.go(src, l, t, off, done, imps, tl, is_imp,
    Bool.or(String.is_empty(tl), String.starts_with(tl, "#")))

@unsafe
def header.go(src, ls, off, done, imps):
  match ls:
    case Nil{}:
      Hdr{List.reverse(&2, String, done), imps, None{}}
    case +l <> t:
      header.line(src, l, t, off, done, imps, Str.trim(l))

def parse_file.fin(r: Result<&1, &1, Err, Unit & PS>) -> Result<&1, &1, Err, Book>:
  match r:
    case Fail{e}:
      Fail{e}
    case Done{v}:
      Done{PS.book(Pair.snd(Unit, PS, v))}

# Parses a file's text into the book: ns qualifies its names, al maps its
# import aliases to namespaces, dir resolves its effect files.
def parse_file(book: Book, +src: String, text: String, ns: String, dir: String, al: List<&2, SB2>) ->
  Result<&1, &1, Err, Book>:
  parse_file.fin(P.decls()(PS{Cur{text, 0, 1, True{}, 0}, Nil{}, 0n, 0, book, src, ns, dir, al}))

def book_len(+b: Book) -> Nat:
  List.length(&2, String, book_order(b))

def mark_base.tld(b: Book, +k: String, t: Maybe<&2, Tld>) -> Book:
  match t:
    case Some{TDef{n, x, ty, v, u, bb, imps}}:
      book_set(b, k, TDef{n, x, ty, v, u, True{}, imps})
    case Some{TADT{n, g, ty, cs, bb}}:
      book_set(b, k, TADT{n, g, ty, cs, True{}})
    case None{}:
      b

def mark_base.one(+b: Book, +k: String) -> Book:
  mark_base.tld(b, k, book_tld(b, k))

def mark_base.go(ks: List<&2, String>, +i: Nat, +n0: Nat, +b: Book) -> Book:
  match ks:
    case Nil{}:
      b
    case +k <> t:
      mark_base.go(t, 1n+i, n0, Bool.pick(Book, Nat.is_ge(i, n0), mark_base.one(b, k), b))

# Marks the declarations after the first n0 as Base's.
def mark_base(+b: Book, +n0: Nat) -> Book:
  mark_base.go(book_order(b), 0n, n0, b)

def Book.holes(+b: Book) -> Nat:
  Book{tlds, ctrs, order, +hols, +open, tmps, tcnt} = b
  Nat.add(hols, open)

def Tld.base_of(t: Maybe<&2, Tld>) -> Bool:
  match t:
    case Some{TDef{n, x, ty, v, u, b, imps}}:
      b
    case Some{TADT{n, g, ty, cs, b}}:
      b
    case None{}:
      False{}

def check_book.owned(+b: Book) -> Result<&1, &1, Err, Book>:
  Bool.pick(Result<&1, &1, Err, Book>, Bool.and(book_has(b, "Clo.apply"), Bool.not(Tld.base_of(book_tld(b, "Clo.apply")))),
    Fail{Err{book_nil(), Nil{}, MStr{"Clo.apply is a name the compiler encodes itself: name yours apart"}, MNone{}, NoSp{},
      "", "!raw"}}, Done{b})

def check_book.holes(+b: Book) -> Result<&1, &1, Err, Book>:
  +n = Book.holes(b)
  Bool.pick(Result<&1, &1, Err, Book>, Nat.is_eq(n, 0n), check_book.owned(b),
    Fail{Err{book_nil(), Nil{}, MStr{Nat.show(n) ++ " TODO" ++ Bool.pick(String, Nat.is_eq(n, 1n), "", "s") ++
      " found.\nThe code is incomplete, and not a valid proof yet."}, MNone{}, NoSp{}, "", "!raw"}})

def check_book.fin(r: Result<&1, &1, Err, Unit & Book>) -> Result<&1, &1, Err, Book>:
  match r:
    case Fail{e}:
      Fail{e}
    case Done{v}:
      check_book.holes(Pair.snd(Unit, Book, v))

# Checks a loaded book: every declaration, no open law or TODO, no name
# the compiler owns.
def check_book(b: Book) -> Result<&1, &1, Err, Book>:
  +full = b
  check_book.fin(book_valid(book_order(full), full)(book_reset(full)))

def show_err.raw(m: Msg) -> String:
  match m:
    case MStr{s}:
      s
    case other:
      ""

# An error, as the official bend prints it.
def show_err(e: Err) -> String:
  Err{bok, ctx, +exp, obs, spn, dn, +nte} = e
  Bool.pick(String, String.eq(nte, "!raw"), "Error: " ++ show_err.raw(exp),
    err_show(Err{bok, ctx, exp, obs, spn, dn, nte}))

law refs.list:
  for xs: List<&2, Tm>
  for acc: List<&2, String>
  List<&2, String>

# The names a term refers to.
@unsafe
def term_refs(t: Tm, acc: List<&2, String>) -> List<&2, String>:
  match t:
    case Ref{k, s, b}:
      k <> acc
    case ADT{k, xs, s, r}:
      refs.list(xs, k <> acc)
    case Cel{k, s, v}:
      term_refs(v, acc)
    case VRf{k, i, s, r}:
      term_refs(r, acc)
    case Sub{i, p, f, s}:
      term_refs(f, acc)
    case Let{ks, ids, vs, f, s, qs}:
      term_refs(f, refs.list(vs, acc))
    case Typ{g, s}:
      term_refs(g, acc)
    case Min{a, b, s}:
      term_refs(b, term_refs(a, acc))
    case All{q, k, i, a, b, s}:
      term_refs(b, term_refs(a, acc))
    case Lam{k, i, f, s, q}:
      term_refs(f, acc)
    case TApp{f, x, s}:
      term_refs(x, term_refs(f, acc))
    case Ctr{k, xs, s}:
      refs.list(xs, acc)
    case Mat{k, h, m, s}:
      term_refs(m, term_refs(h, acc))
    case Eql{a, b, ty, s}:
      term_refs(ty, term_refs(b, term_refs(a, acc)))
    case Rwt{e, p, f, s}:
      term_refs(f, term_refs(p, term_refs(e, acc)))
    case Ann{x, ty, s}:
      term_refs(ty, term_refs(x, acc))
    case CSyn{env, i, b}:
      term_refs(b, refs.list(env, acc))
    case CLet{env, ids, b}:
      term_refs(b, refs.list(env, acc))
    case EB{i, v}:
      term_refs(v, acc)
    case other:
      acc

@unsafe
def refs.list(xs, acc):
  match xs:
    case Nil{}:
      acc
    case x <> t:
      refs.list(t, term_refs(x, acc))

def CtrD.ts(cs: List<&2, CtrD>) -> List<&2, Tm>:
  match cs:
    case Nil{}:
      Nil{}
    case CtrD{k, n, t} <> rest:
      t <> CtrD.ts(rest)

def tld_refs.v(v: Maybe<&2, Tm>) -> List<&2, String>:
  match v:
    case Some{x}:
      term_refs(x, Nil{})
    case None{}:
      Nil{}

def tld_refs(t: Maybe<&2, Tld>) -> List<&2, String>:
  match t:
    case Some{TDef{n, x, ty, v, u, b, imps}}:
      term_refs(ty, tld_refs.v(v))
    case Some{TADT{n, g, ty, cs, b}}:
      refs.list(CtrD.ts(cs), Nil{})
    case None{}:
      Nil{}

def Tld.bad(t: Maybe<&2, Tld>) -> Bool:
  match t:
    case Some{TDef{n, x, ty, v, u, b, imps}}:
      Bool.or(u, Bool.and(Maybe.is_some(&2, List<&2, String>, imps), Bool.not(b)))
    case other:
      False{}

type Use is Data:
  Use{r: String, by: String}

def report.uses(rs: List<&2, String>, +k: String, uses: List<&2, Use>) -> List<&2, Use>:
  match rs:
    case Nil{}:
      uses
    case r <> t:
      report.uses(t, k, Use{r, k} <> uses)

law report.walk:
  for +b: Book
  for q: List<&2, String>
  for seen: Set()
  for uses: List<&2, Use>
  List<&2, Use>

@unsafe
def report.walk.one(+b: Book, +k: String, t: List<&2, String>, r: Set() & Bool, uses: List<&2, Use>) ->
  List<&2, Use>:
  (seen, hit) = r
  match hit:
    case True{}:
      report.walk(b, t, seen, uses)
    case False{}:
      +rs = tld_refs(book_tld(b, k))
      report.walk(b, List.append(&2, String, rs, t), Set.add(seen, k), report.uses(rs, k, uses))

# Walks the definitions reachable from q, recording who uses what.
@unsafe
def report.walk(b, q, seen, uses):
  match q:
    case Nil{}:
      uses
    case +k <> t:
      report.walk.one(b, k, t, Set.has(seen, k), uses)

def report.users.if(by: String, rest: List<&2, String>, hit: Bool) -> List<&2, String>:
  match hit:
    case True{}:
      by <> rest
    case False{}:
      rest

def report.users(uses: List<&2, Use>, +k: String) -> List<&2, String>:
  match uses:
    case Nil{}:
      Nil{}
    case Use{+r, by} <> t:
      report.users.if(by, report.users(t, k), String.eq(r, k))

law report.close:
  for +uses: List<&2, Use>
  for todo: List<&2, String>
  for bad: List<&2, String>
  List<&2, String>

law report.close.add:
  for +uses: List<&2, Use>
  for todo: List<&2, String>
  for +bad: List<&2, String>
  for us: List<&2, String>
  List<&2, String>

# The names that rely on unsafe or foreign code: the closure of bad
# under "is used by".
@unsafe
def report.close(uses, todo, bad):
  match todo:
    case Nil{}:
      bad
    case +k <> t:
      report.close.add(uses, t, bad, report.users(uses, k))

@unsafe
def report.close.add.if(
  +uses: List<&2, Use>, todo: List<&2, String>, +bad: List<&2, String>, +u: String, us: List<&2, String>, seen: Bool
) -> List<&2, String>:
  match seen:
    case True{}:
      report.close.add(uses, todo, bad, us)
    case False{}:
      report.close.add(uses, List.append(&2, String, todo, [u]), u <> bad, us)

@unsafe
def report.close.add(uses, todo, bad, us):
  match us:
    case Nil{}:
      report.close(uses, todo, bad)
    case +u <> t:
      report.close.add.if(uses, todo, bad, u, t, Str.has(bad, u))

def report.bad_all(+b: Book, ks: List<&2, String>) -> List<&2, String>:
  match ks:
    case Nil{}:
      Nil{}
    case +k <> t:
      Str.filter_in.if(k, report.bad_all(b, t), Tld.bad(book_tld(b, k)))

def List.drop_str2(xs: List<&2, String>, n: Nat) -> List<&2, String>:
  match xs n:
    case ys 0n:
      ys
    case y <> t 1n+m:
      List.drop_str2(t, m)
    case Nil{} k:
      Nil{}

def Book.tlds(+b: Book) -> Map<&2, Tld>:
  Book{+tlds, ctrs, order, hols, open, tmps, tcnt} = b
  tlds

def report.go(+b: Book, +own: List<&2, String>, +bad: List<&2, String>, none: Bool) -> List<&2, String>:
  match none:
    case True{}:
      Nil{}
    case False{}:
      Str.filter_in(own, report.close(report.walk(b, own, Set.new(), Nil{}), bad, bad))

# The defs of the file (those after the first n0) that rely on unsafe or
# foreign code.
def report(+b: Book, +n0: Nat) -> List<&2, String>:
  +own = Str.unique(List.drop_str2(book_order(b), n0), Nil{})
  +bad = report.bad_all(b, Map.keys(&2, Tld, Book.tlds(b)))
  report.go(b, own, bad, Lst.empty(&2, String, bad))

def report_lines(ks: List<&2, String>) -> String:
  match ks:
    case Nil{}:
      ""
    case k <> t:
      "- " ++ k ++ "\n" ++ report_lines(t)

# The official report line for the file's unsafe or foreign defs.
def report_text(ks: List<&2, String>) -> String:
  match ks:
    case Nil{}:
      ""
    case +h <> +t:
      +n = List.length(&2, String, h <> t)
      "All terms check, but " ++ Nat.show(n) ++ " def" ++ Bool.pick(String, Nat.is_eq(n, 1n), " relies", "s rely") ++
        " on unsafe or foreign code:\n" ++ report_lines(h <> t)

def has_fun.cs(t: Maybe<&2, Tld>) -> List<&2, CtrD>:
  match t:
    case Some{TADT{n, g, ty, cs, bb}}:
      cs
    case other:
      Nil{}

@unsafe
def has_fun.fill(+b: Book, t: Tm, xs: List<&2, Tm>) -> Tm:
  match xs:
    case Nil{}:
      t
    case x <> rest:
      has_fun.fill(b, clo_apply(b, All.b(term_wnf(b, t)), [x]), rest)

law has_fun.field:
  for +b: Book
  for t: Tm
  for m: Nat
  for +d: U32
  for +seen: List<&2, String>
  Bool

@unsafe
def has_fun.fields(+b: Book, t: Tm, n: Nat, +d: U32, +seen: List<&2, String>) -> Bool:
  match n:
    case 0n:
      False{}
    case 1n+m:
      has_fun.field(b, term_wnf(b, t), m, d, seen)

@unsafe
def has_fun.ctrs(+b: Book, +xs: List<&2, Tm>, cs: List<&2, CtrD>, +seen: List<&2, String>) -> Bool:
  match cs:
    case Nil{}:
      False{}
    case CtrD{k, +n, t} <> rest:
      Lazy.or(has_fun.fields(b, has_fun.fill(b, t, xs), n, 0, seen), u => has_fun.ctrs(b, xs, rest, seen))

@unsafe
def has_fun.adt.c(+b: Book, +k: String, +xs: List<&2, Tm>, +key: String, +seen: List<&2, String>, c: Bool) -> Bool:
  match c:
    case True{}:
      False{}
    case False{}:
      has_fun.ctrs(b, xs, has_fun.cs(book_tld(b, k)), key <> seen)

@unsafe
def has_fun.adt(+b: Book, +k: String, +xs: List<&2, Tm>, +key: String, +seen: List<&2, String>) -> Bool:
  has_fun.adt.c(b, k, xs, key, seen, Str.has(seen, key))

@unsafe
def has_fun.go(+b: Book, t: Tm, +seen: List<&2, String>) -> Bool:
  match t:
    case All{q, k, i, a, c, s}:
      True{}
    case ADT{+k, +xs, s, r}:
      has_fun.adt(b, k, xs, term_key(term_lower(b, ADT{k, xs, s, r}, 0)), seen)
    case other:
      False{}

law has_fun:
  for +b: Book
  for t: Tm
  for +seen: List<&2, String>
  Bool

# Whether values of type t may hold a function (then a value main is
# printed by normalizing it, as the official bend does).
@unsafe
def has_fun(b, t, seen):
  has_fun.go(b, term_wnf(b, t), seen)

@unsafe
def has_fun.field(b, t, m, d, seen):
  match t:
    case All{q, +k, i, a, c, s}:
      Lazy.or(has_fun(b, a, seen), u => has_fun.fields(b, clo_apply(b, c, [Var{k, d, NoSp{}}]), m, U32.inc(d), seen))
    case other:
      False{}

def main_tld(+b: Book) -> Maybe<&2, Tld>:
  book_tld(b, "main")

def main_has_fun.go(+b: Book, t: Maybe<&2, Tld>) -> Bool:
  match t:
    case Some{TDef{n, x, ty, v, u, bb, imps}}:
      has_fun(b, ty, Nil{})
    case other:
      False{}

# Whether main returns a value that may hold a function.
def main_has_fun(+b: Book) -> Bool:
  main_has_fun.go(b, main_tld(b))

def show_main.go(+b: Book, t: Maybe<&2, Tld>) -> String:
  match t:
    case Some{TDef{n, x, ty, Some{v}, u, bb, imps}}:
      term_show(term_lower(b, term_snf(b, v), 0), 0, Nil{})
    case other:
      ""

def main_is_io.go(+b: Book, t: Maybe<&2, Tld>) -> Bool:
  match t:
    case Some{TDef{n, x, ty, v, u, bb, imps}}:
      valid.io(b, term_head(term_strip(ty)))
    case other:
      False{}

def main_is_io(+b: Book) -> Bool:
  main_is_io.go(b, main_tld(b))

# main's value, normalized and printed as the official bend prints it.
def show_main(+b: Book) -> String:
  show_main.go(b, main_tld(b))
