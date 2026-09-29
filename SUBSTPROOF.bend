import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./REDPROOF.bend as RP
import ./DEAD.bend as Dead
import ./DEADPROOF.bend as DP
import ./SUBST.bend as Law

# Proof of SUBST.bend's laws. L.sub (subst_ok): induction on the source's
# fuel, one case per step of `run`, the other program's fuel found as the
# steps go (Then.go puts the fuel of a step's two runs together; REDPROOF's
# L.mono says more fuel gives the same result). A lookup (Look) walks the
# source's scope and what the pass knew of it together: where the pass put
# a let's value in place, the other program runs the value. At a let whose
# value goes in place (Let.sub) the source's steps to the let's body are
# taken at once: the value's run gives the source's value w, and the
# other program's value run twice, at the let and in the body's scope (the
# let's scope with its binding in front, none of whose names the scope
# has: ERel.fresh), gives values related to w.

# Booleans and equalities
# =======================

def Absurd(-A: Data, t: Empty) -> A:
  match t:

def Tru.of(-b: Bool, e: {True{} == b : Bool}) -> Dead.Tru(b):
  %e : Dead.Tru(_)
  Unit{}

def Fls.of(-b: Bool, e: {False{} == b : Bool}) -> Dead.Fls(b):
  %e : Dead.Fls(_)
  Unit{}

def And.l(a: Bool, -b: Bool, e: {True{} == Bool.and(a, b) : Bool}) -> {True{} == a : Bool}:
  match a:
    case True{}:
      {==}
    case False{}:
      Absurd({True{} == False{} : Bool}, Tru.of(False{}, e))

def And.r(a: Bool, -b: Bool, e: {True{} == Bool.and(a, b) : Bool}) -> {True{} == b : Bool}:
  match a:
    case True{}:
      e
    case False{}:
      Absurd({True{} == b : Bool}, Tru.of(False{}, e))

def Not.t(a: Bool, e: {True{} == Bool.not(a) : Bool}) -> {False{} == a : Bool}:
  match a:
    case True{}:
      Absurd({False{} == True{} : Bool}, Tru.of(False{}, e))
    case False{}:
      {==}

def Str.sym(-a: String, -b: String, e: {a == b : String}) -> {b == a : String}:
  %e : {_ == a : String}
  {==}

def Res.sym(-a: Core.Res, -b: Core.Res, e: {a == b : Core.Res}) -> {b == a : Core.Res}:
  %e : {_ == a : Core.Res}
  {==}

def Sb.sym(-a: List<&2, Core.Sb>, -b: List<&2, Core.Sb>, e: {a == b : List<&2, Core.Sb>}) -> {b == a : List<&2, Core.Sb>}:
  %e : {_ == a : List<&2, Core.Sb>}
  {==}

# b == c from a == b and a == c.
def Res.tr(-a: Core.Res, -b: Core.Res, -c: Core.Res, e1: {a == b : Core.Res}, e2: {a == c : Core.Res}) -> {b == c : Core.Res}:
  %e1 : {_ == c : Core.Res}
  e2

# Strings
# =======

# String.eq is sound (a name compared equal is the same name) and
# reflexive.

def Cmp.of(r: (String & String) & Cmp) -> Cmp:
  match r:
    case (ab, c):
      c

def IsEq(c: Cmp) -> Data:
  match c:
    case LT{}:
      Empty
    case EQ{}:
      Unit
    case GT{}:
      Empty

def IsEq.of(-c: Cmp, e: {EQ{} == c : Cmp}) -> IsEq(c):
  %e : IsEq(_)
  Unit{}
def Fin.eq(ab: Bool, bb: Bool, t: Cmp, e: {EQ{} == Word.cmp.fin(ab, bb, t) : Cmp}) -> Sigma<&2, &2, {EQ{} == t : Cmp}, _ => {ab == bb : Bool}>:
  match ab:
    case True{}:
      match bb:
        case True{}:
          match t:
            case LT{}:
              Absurd(Sigma<&2, &2, {EQ{} == LT{} : Cmp}, _ => {True{} == True{} : Bool}>, IsEq.of(LT{}, e))
            case GT{}:
              Absurd(Sigma<&2, &2, {EQ{} == GT{} : Cmp}, _ => {True{} == True{} : Bool}>, IsEq.of(GT{}, e))
            case EQ{}:
              ({==}, {==})
        case False{}:
          match t:
            case LT{}:
              Absurd(Sigma<&2, &2, {EQ{} == LT{} : Cmp}, _ => {True{} == False{} : Bool}>, IsEq.of(LT{}, e))
            case GT{}:
              Absurd(Sigma<&2, &2, {EQ{} == GT{} : Cmp}, _ => {True{} == False{} : Bool}>, IsEq.of(GT{}, e))
            case EQ{}:
              Absurd(Sigma<&2, &2, {EQ{} == EQ{} : Cmp}, _ => {True{} == False{} : Bool}>, IsEq.of(GT{}, e))
    case False{}:
      match bb:
        case True{}:
          match t:
            case LT{}:
              Absurd(Sigma<&2, &2, {EQ{} == LT{} : Cmp}, _ => {False{} == True{} : Bool}>, IsEq.of(LT{}, e))
            case GT{}:
              Absurd(Sigma<&2, &2, {EQ{} == GT{} : Cmp}, _ => {False{} == True{} : Bool}>, IsEq.of(GT{}, e))
            case EQ{}:
              Absurd(Sigma<&2, &2, {EQ{} == EQ{} : Cmp}, _ => {False{} == True{} : Bool}>, IsEq.of(LT{}, e))
        case False{}:
          match t:
            case LT{}:
              Absurd(Sigma<&2, &2, {EQ{} == LT{} : Cmp}, _ => {False{} == False{} : Bool}>, IsEq.of(LT{}, e))
            case GT{}:
              Absurd(Sigma<&2, &2, {EQ{} == GT{} : Cmp}, _ => {False{} == False{} : Bool}>, IsEq.of(GT{}, e))
            case EQ{}:
              ({==}, {==})

def Word.fin(-p: Nat, -ab: Bool, -at: Word(p), -bb: Bool, -bt: Word(p), h: Sigma<&2, &2, {EQ{} == Word.cmp(p, at, bt) : Cmp}, _ => {ab == bb : Bool}>,
    ih: {EQ{} == Word.cmp(p, at, bt) : Cmp} -> {at == bt : Word(p)}) -> {WCon{ab, at} == WCon{bb, bt} : Word(1n+p)}:
  match h:
    case (et, eb):
      %ih(et) : {WCon{ab, at} == WCon{bb, _} : Word(1n+p)}
      %eb : {WCon{ab, at} == WCon{_, at} : Word(1n+p)}
      {==}

def Word.sound(n: Nat, a: Word(n), b: Word(n), e: {EQ{} == Word.cmp(n, a, b) : Cmp}) -> {a == b : Word(n)}:
  match n:
    case 0n:
      match a:
        case WNil{}:
          match b:
            case WNil{}:
              {==}
    case 1n+(+p):
      match a:
        case WCon{+ab, +at}:
          match b:
            case WCon{+bb, +bt}:
              Word.fin(p, ab, at, bb, bt, Fin.eq(ab, bb, Word.cmp(p, at, bt), e), h => Word.sound(p, at, bt, h))

def U32.sound(a: U32, b: U32, e: {EQ{} == U32.cmp(a, b) : Cmp}) -> {a == b : U32}:
  match a:
    case U32{x}:
      match b:
        case U32{y}:
          %Word.sound(32n, x, y, e) : {U32{x} == U32{_} : U32}
          {==}

def Rec.of(h1: Char, h2: Char, rr: (String & String) & Cmp) -> {Cmp.of(String.cmp.rec(h1, h2, rr)) == Cmp.of(rr) : Cmp}:
  match rr:
    case (ab, c):
      match ab:
        case (a2, b2):
          {==}

def Cmp.tr(-a: Cmp, -b: Cmp, q: {a == b : Cmp}, e: {EQ{} == a : Cmp}) -> {EQ{} == b : Cmp}:
  %q : {EQ{} == _ : Cmp}
  e

def Str.fin(+x: U32, +y: U32, +t1: String, +t2: String, c: Cmp, ec: {c == U32.cmp(x, y) : Cmp},
    e: {EQ{} == Cmp.of(String.cmp.fin(t1, t2, ((Chr{x}, Chr{y}), c))) : Cmp},
    ih: {EQ{} == Cmp.of(String.cmp(t1, t2)) : Cmp} -> {t1 == t2 : String})
    -> {SCon{Chr{x}, t1} == SCon{Chr{y}, t2} : String}:
  match c:
    case LT{}:
      Absurd({SCon{Chr{x}, t1} == SCon{Chr{y}, t2} : String}, IsEq.of(LT{}, e))
    case GT{}:
      Absurd({SCon{Chr{x}, t1} == SCon{Chr{y}, t2} : String}, IsEq.of(GT{}, e))
    case EQ{}:
      %ih(Cmp.tr(Cmp.of(String.cmp.rec(Chr{x}, Chr{y}, String.cmp(t1, t2))), Cmp.of(String.cmp(t1, t2)), Rec.of(Chr{x}, Chr{y}, String.cmp(t1, t2)), e)) : {SCon{Chr{x}, t1} == SCon{Chr{y}, _} : String}
      %U32.sound(x, y, ec) : {SCon{Chr{x}, t1} == SCon{Chr{_}, t1} : String}
      {==}

def Str.sound(a: String, b: String, e: {EQ{} == Cmp.of(String.cmp(a, b)) : Cmp}) -> {a == b : String}:
  match a:
    case SNil{}:
      match b:
        case SNil{}:
          {==}
        case SCon{h, t}:
          Absurd({SNil{} == SCon{h, t} : String}, IsEq.of(LT{}, e))
    case SCon{h1, +t1}:
      match h1:
        case Chr{+x}:
          match b:
            case SNil{}:
              Absurd({SCon{Chr{x}, t1} == SNil{} : String}, IsEq.of(GT{}, e))
            case SCon{h2, +t2}:
              match h2:
                case Chr{+y}:
                  Str.fin(x, y, t1, t2, U32.cmp(x, y), {==}, e, h => Str.sound(t1, t2, h))


def Eq.fin(r: (String & String) & Cmp, e: {True{} == String.eq.fin(r) : Bool}) -> {EQ{} == Cmp.of(r) : Cmp}:
  match r:
    case (ab, c):
      match ab:
        case (a2, b2):
          match c:
            case LT{}:
              Absurd({EQ{} == LT{} : Cmp}, Tru.of(False{}, e))
            case EQ{}:
              {==}
            case GT{}:
              Absurd({EQ{} == GT{} : Cmp}, Tru.of(False{}, e))

# Names String.eq says are equal are.
def Str.eq(+a: String, +b: String, e: {True{} == String.eq(a, b) : Bool}) -> {a == b : String}:
  Str.sound(a, b, Eq.fin(String.cmp(a, b), e))

def Bool.refl(a: Bool) -> {EQ{} == Bool.cmp(a, a) : Cmp}:
  match a:
    case True{}:
      {==}
    case False{}:
      {==}

def Word.refl(n: Nat, a: Word(n)) -> {EQ{} == Word.cmp(n, a, a) : Cmp}:
  match n:
    case 0n:
      {==}
    case 1n+(+p):
      match a:
        case WCon{+ab, +at}:
          %Word.refl(p, at) : {EQ{} == Word.cmp.fin(ab, ab, _) : Cmp}
          Bool.refl(ab)

def U32.refl(a: U32) -> {EQ{} == U32.cmp(a, a) : Cmp}:
  match a:
    case U32{+x}:
      Word.refl(32n, x)

def Rec.to(h1: Char, h2: Char, rr: (String & String) & Cmp) -> {Cmp.of(rr) == Cmp.of(String.cmp.rec(h1, h2, rr)) : Cmp}:
  match rr:
    case (ab, c):
      match ab:
        case (a2, b2):
          {==}

def Str.refl.c(a: String) -> {EQ{} == Cmp.of(String.cmp(a, a)) : Cmp}:
  match a:
    case SNil{}:
      {==}
    case SCon{h, +t}:
      match h:
        case Chr{+x}:
          %U32.refl(x) : {EQ{} == Cmp.of(String.cmp.fin(t, t, ((Chr{x}, Chr{x}), _))) : Cmp}
          Cmp.tr(Cmp.of(String.cmp(t, t)), Cmp.of(String.cmp.rec(Chr{x}, Chr{x}, String.cmp(t, t))),
            Rec.to(Chr{x}, Chr{x}, String.cmp(t, t)), Str.refl.c(t))

def Fin.true(r: (String & String) & Cmp, e: {EQ{} == Cmp.of(r) : Cmp}) -> {True{} == String.eq.fin(r) : Bool}:
  match r:
    case (ab, c):
      match ab:
        case (a2, b2):
          %e : {True{} == Cmp.is_eq(_) : Bool}
          {==}

# A name is equal to itself.
def Str.refl(+a: String) -> {True{} == String.eq(a, a) : Bool}:
  Fin.true(String.cmp(a, a), Str.refl.c(a))


# Fuel
# ====

def Sum(a: Nat, b: Nat) -> Nat:
  match a:
    case 0n:
      b
    case 1n+x:
      1n+Sum(x, b)

def Le.suml(+a: Nat, +b: Nat) -> Red.Le(a, Sum(a, b)):
  match a:
    case 0n:
      Unit{}
    case 1n+x:
      Le.suml(x, b)

def Le.sumr(+a: Nat, +b: Nat) -> Red.Le(b, Sum(a, b)):
  match a:
    case 0n:
      RP.Le.refl(b)
    case 1n+x:
      RP.Le.succ(b, Sum(x, b), Le.sumr(x, b))

def IsOk(r: Core.Res) -> Data:
  match r:
    case Core.ROk{vs}:
      Unit
    case Core.REnv{e}:
      Empty
    case Core.RNo{}:
      Empty
    case Core.RFail{m}:
      Empty

def Ok.tr(-x: Core.Res, -y: Core.Res, e: {y == x : Core.Res}, h: IsOk(y)) -> IsOk(x):
  %e : IsOk(_)
  h

# A run that gives a value did not fail.
def Ok.no(-T: Data, -a: String, -vs: List<&2, Core.Val>, e: {Core.RFail{a} == Core.ROk{vs} : Core.Res}) -> T:
  Absurd(T, Ok.tr(Core.RFail{a}, Core.ROk{vs}, Res.sym(Core.RFail{a}, Core.ROk{vs}, e), Unit{}))

def NF.tr(-a: Core.Res, -b: Core.Res, e: {b == a : Core.Res}, nf: Red.NotOof(b)) -> Red.NotOof(a):
  %e : Red.NotOof(_)
  nf

# A result related to one that is not a failure is not one either.
def NF.ok(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -vs: List<&2, Core.Val>, -S: List<&2, Core.Sb>, r2: Core.Res,
    h: Law.RRel(prim, dz, Core.ROk{vs}, S, r2)) -> Red.NotOof(r2):
  match r2:
    case Core.ROk{v}:
      Unit{}
    case Core.REnv{e}:
      match h:
    case Core.RNo{}:
      match h:
    case Core.RFail{m}:
      match h:

def NF.env(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -e1: List<&2, Core.Val>, -S: List<&2, Core.Sb>, r2: Core.Res,
    h: Law.RRel(prim, dz, Core.REnv{e1}, S, r2)) -> Red.NotOof(r2):
  match r2:
    case Core.ROk{v}:
      match h:
    case Core.REnv{e}:
      Unit{}
    case Core.RNo{}:
      match h:
    case Core.RFail{m}:
      match h:

def NF.no(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -S: List<&2, Core.Sb>, r2: Core.Res,
    h: Law.RRel(prim, dz, Core.RNo{}, S, r2)) -> Red.NotOof(r2):
  match r2:
    case Core.ROk{v}:
      match h:
    case Core.REnv{e}:
      match h:
    case Core.RNo{}:
      Unit{}
    case Core.RFail{m}:
      match h:

# The other program's fuel can grow: a result related to one that is not
# a failure is not one, and more fuel gives it too.
def Tgt.fin(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, -r1: Core.Res, -S: List<&2, Core.Sb>, +a: Nat, +b: Nat, +le: Red.Le(a, b), t: Core.Sel,
    h: Law.RRel(prim, dz, r1, S, Core.run(~prim, a, dz, t)), +nf: Red.NotOof(Core.run(~prim, a, dz, t)))
    -> Law.RRel(prim, dz, r1, S, Core.run(~prim, b, dz, t)):
  %RP.L.mono(~prim, a, b, le, dz, t, nf) : Law.RRel(prim, dz, r1, S, _)
  h

def Tgt.mono(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, r1: Core.Res, -S: List<&2, Core.Sb>, +a: Nat, +b: Nat, +le: Red.Le(a, b), +t: Core.Sel,
    +h: Law.RRel(prim, dz, r1, S, Core.run(~prim, a, dz, t))) -> Law.RRel(prim, dz, r1, S, Core.run(~prim, b, dz, t)):
  match r1:
    case Core.RFail{m}:
      Unit{}
    case Core.ROk{vs}:
      Tgt.fin(~prim, dz, Core.ROk{vs}, S, a, b, le, t, h, NF.ok(prim, dz, vs, S, Core.run(~prim, a, dz, t), h))
    case Core.REnv{e}:
      Tgt.fin(~prim, dz, Core.REnv{e}, S, a, b, le, t, h, NF.env(prim, dz, e, S, Core.run(~prim, a, dz, t), h))
    case Core.RNo{}:
      Tgt.fin(~prim, dz, Core.RNo{}, S, a, b, le, t, h, NF.no(prim, dz, S, Core.run(~prim, a, dz, t), h))

# The source's fuel can shrink: with less, it fails, or gives the same.
def Src.fin(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, +a: Nat, +b: Nat, +le: Red.Le(a, b), +s1: Core.Sel, -S: List<&2, Core.Sb>,
    -t: Core.Res, -r: Core.Res, +er: {Core.run(~prim, a, ds, s1) == r : Core.Res}, nf: Red.NotOof(r),
    h: Law.RRel(prim, dz, Core.run(~prim, b, ds, s1), S, t)) -> Law.RRel(prim, dz, r, S, t):
  %er : Law.RRel(prim, dz, _, S, t)
  %Res.sym(Core.run(~prim, a, ds, s1), Core.run(~prim, b, ds, s1),
    RP.L.mono(~prim, a, b, le, ds, s1, NF.tr(Core.run(~prim, a, ds, s1), r, Res.sym(Core.run(~prim, a, ds, s1), r, er), nf))) : Law.RRel(prim, dz, _, S, t)
  h

def Src.go(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, +a: Nat, +b: Nat, +le: Red.Le(a, b), +s1: Core.Sel, -S: List<&2, Core.Sb>,
    -t: Core.Res, r: Core.Res, +er: {Core.run(~prim, a, ds, s1) == r : Core.Res},
    h: Law.RRel(prim, dz, Core.run(~prim, b, ds, s1), S, t)) -> Law.RRel(prim, dz, r, S, t):
  match r:
    case Core.RFail{m}:
      Unit{}
    case Core.ROk{vs}:
      Src.fin(~prim, ds, dz, a, b, le, s1, S, t, Core.ROk{vs}, er, Unit{}, h)
    case Core.REnv{e}:
      Src.fin(~prim, ds, dz, a, b, le, s1, S, t, Core.REnv{e}, er, Unit{}, h)
    case Core.RNo{}:
      Src.fin(~prim, ds, dz, a, b, le, s1, S, t, Core.RNo{}, er, Unit{}, h)

def Src.mono(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, +a: Nat, +b: Nat, +le: Red.Le(a, b), +s1: Core.Sel, -S: List<&2, Core.Sb>,
    -t: Core.Res, h: Law.RRel(prim, dz, Core.run(~prim, b, ds, s1), S, t)) -> Law.RRel(prim, dz, Core.run(~prim, a, ds, s1), S, t):
  Src.go(~prim, ds, dz, a, b, le, s1, S, t, Core.run(~prim, a, ds, s1), {==}, h)

# A step of the other program: one more unit of fuel.
def Up.go(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -r1: Core.Res, -S: List<&2, Core.Sb>, -t: Core.Sel, -t2: Core.Sel, -m: Nat,
    rr: Law.RRel(prim, dz, r1, S, Core.run(~prim, m, dz, t)), e: {Core.run(~prim, m, dz, t) == Core.run(~prim, 1n+m, dz, t2) : Core.Res})
    -> Law.RRel(prim, dz, r1, S, Core.run(~prim, 1n+m, dz, t2)):
  %e : Law.RRel(prim, dz, r1, S, _)
  rr

def Up.one(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -r1: Core.Res, -S: List<&2, Core.Sb>, -t: Core.Sel, -t2: Core.Sel,
    h: Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, r1, S, Core.run(~prim, m, dz, t))>,
    e: @m:Nat -> {Core.run(~prim, m, dz, t) == Core.run(~prim, 1n+m, dz, t2) : Core.Res})
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, r1, S, Core.run(~prim, m, dz, t2))>:
  match h:
    case (+m, rr):
      (1n+m, Up.go(~prim, dz, r1, S, t, t2, m, rr, e(m)))

# A step that runs x and gives its result to k: with fuel m1 for x's run and
# m2 for the rest, their sum does both.
def Then.fin(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, +m1: Nat, +m2: Nat, +x: Core.Sel, +k: Core.Kont, -r1: Core.Res, -S: List<&2, Core.Sb>,
    h: Law.RRel(prim, dz, r1, S, Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k})),
    +nf: Red.NotOof(Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k})))
    -> Law.RRel(prim, dz, r1, S, Core.run(~prim, Sum(m1, m2), dz, Core.SThen{Core.run(~prim, Sum(m1, m2), dz, x), k})):
  %RP.L.mono(~prim, m1, Sum(m1, m2), Le.suml(m1, m2), dz, x, RP.L.nf(~prim, m2, dz, Core.run(~prim, m1, dz, x), k, nf)) : Law.RRel(prim, dz, r1, S, Core.run(~prim, Sum(m1, m2), dz, Core.SThen{_, k}))
  %RP.L.mono(~prim, m2, Sum(m1, m2), Le.sumr(m1, m2), dz, Core.SThen{Core.run(~prim, m1, dz, x), k}, nf) : Law.RRel(prim, dz, r1, S, _)
  h

def Then.up(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, +m1: Nat, +m2: Nat, +x: Core.Sel, +k: Core.Kont, r1: Core.Res, -S: List<&2, Core.Sb>,
    +h: Law.RRel(prim, dz, r1, S, Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k})))
    -> Law.RRel(prim, dz, r1, S, Core.run(~prim, Sum(m1, m2), dz, Core.SThen{Core.run(~prim, Sum(m1, m2), dz, x), k})):
  match r1:
    case Core.RFail{m}:
      Unit{}
    case Core.ROk{vs}:
      Then.fin(~prim, dz, m1, m2, x, k, Core.ROk{vs}, S, h, NF.ok(prim, dz, vs, S, Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k}), h))
    case Core.REnv{e}:
      Then.fin(~prim, dz, m1, m2, x, k, Core.REnv{e}, S, h, NF.env(prim, dz, e, S, Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k}), h))
    case Core.RNo{}:
      Then.fin(~prim, dz, m1, m2, x, k, Core.RNo{}, S, h, NF.no(prim, dz, S, Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k}), h))

def Then.go2(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, r1: Core.Res, -S: List<&2, Core.Sb>, +x: Core.Sel, +k: Core.Kont, -t2: Core.Sel, +m1: Nat,
    h2: Sigma<&2, &2, Nat, m2 => Law.RRel(prim, dz, r1, S, Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k}))>,
    e: @M:Nat -> {Core.run(~prim, M, dz, Core.SThen{Core.run(~prim, M, dz, x), k}) == Core.run(~prim, 1n+M, dz, t2) : Core.Res})
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, r1, S, Core.run(~prim, m, dz, t2))>:
  match h2:
    case (+m2, rr2):
      (1n+Sum(m1, m2), Up.go(~prim, dz, r1, S, Core.SThen{Core.run(~prim, Sum(m1, m2), dz, x), k}, t2, Sum(m1, m2),
        Then.up(~prim, dz, m1, m2, x, k, r1, S, rr2), e(Sum(m1, m2))))

# The source runs a step's x (related to the other program's x with ri and
# Si), then gives its result to its continuation (f relates the rest, for
# the fuel the other program's x took).
def Then.go(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, r1: Core.Res, -S: List<&2, Core.Sb>, -ri: Core.Res, -Si: List<&2, Core.Sb>, +x: Core.Sel, +k: Core.Kont, -t2: Core.Sel,
    h1: Sigma<&2, &2, Nat, m1 => Law.RRel(prim, dz, ri, Si, Core.run(~prim, m1, dz, x))>,
    f: @m1:Nat -> Law.RRel(prim, dz, ri, Si, Core.run(~prim, m1, dz, x)) ->
      Sigma<&2, &2, Nat, m2 => Law.RRel(prim, dz, r1, S, Core.run(~prim, m2, dz, Core.SThen{Core.run(~prim, m1, dz, x), k}))>,
    e: @M:Nat -> {Core.run(~prim, M, dz, Core.SThen{Core.run(~prim, M, dz, x), k}) == Core.run(~prim, 1n+M, dz, t2) : Core.Res})
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, r1, S, Core.run(~prim, m, dz, t2))>:
  match h1:
    case (+m1, rr1):
      Then.go2(~prim, dz, r1, S, x, k, t2, m1, f(m1, rr1), e)

def Sig.tr(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -a: Core.Res, -b: Core.Res, e: {a == b : Core.Res}, -S: List<&2, Core.Sb>, -t: Core.Sel,
    h: Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, a, S, Core.run(~prim, m, dz, t))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, b, S, Core.run(~prim, m, dz, t))>:
  %e : Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, _, S, Core.run(~prim, m, dz, t))>
  h

# What a run related to one that gives w gives.
def Gives.of2(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -S: List<&2, Core.Sb>, -w: Core.Val, -e: List<&2, Core.Val>, -t: Core.Tm, +m: Nat, r2: Core.Res,
    eq: {Core.run(~prim, m, dz, Core.SEval{e, t}) == r2 : Core.Res}, rr: Law.RRel(prim, dz, Core.ROk{[w]}, S, r2))
    -> Law.Gives(prim, dz, w, e, t):
  match r2:
    case Core.ROk{vs2}:
      match vs2:
        case Nil{}:
          match rr:
        case w2 <> r3:
          match r3:
            case Nil{}:
              match rr:
                case (vr, u):
                  (w2, m, eq, vr)
            case w3 <> r4:
              match rr:
                case (vr, u):
                  match u:
    case Core.REnv{x}:
      match rr:
    case Core.RNo{}:
      match rr:
    case Core.RFail{x}:
      match rr:

def Gives.of(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, -S: List<&2, Core.Sb>, -w: Core.Val, +e: List<&2, Core.Val>, +t: Core.Tm,
    h: Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, S, Core.run(~prim, m, dz, Core.SEval{e, t}))>)
    -> Law.Gives(prim, dz, w, e, t):
  match h:
    case (+m, rr):
      Gives.of2(~prim, dz, S, w, e, t, m, Core.run(~prim, m, dz, Core.SEval{e, t}), {==}, rr)

# Natives
# =======

def Prim(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, r1: Core.Res, r2: Core.Res, h: Law.PRel(prim, dz, r1, r2), -S: List<&2, Core.Sb>)
    -> Law.RRel(prim, dz, r1, S, r2):
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          h
        case Core.REnv{e}:
          match h:
        case Core.RNo{}:
          match h:
        case Core.RFail{m}:
          match h:
    case Core.REnv{e}:
      match h:
    case Core.RNo{}:
      match h:
    case Core.RFail{m}:
      Unit{}

# Lists
# =====

def Len.eq(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(prim, dz, vs, vs2))
    -> {Core.Vals.len(vs) == Core.Vals.len(vs2) : Nat}:
  match vs:
    case Nil{}:
      match vs2:
        case Nil{}:
          {==}
        case w <> s:
          match vr:
    case v <> r:
      match vs2:
        case Nil{}:
          match vr:
        case w <> s:
          match vr:
            case (a, b):
              %Len.eq(prim, dz, r, s, b) : {1n+Core.Vals.len(r) == 1n+_ : Nat}
              {==}

def Drop(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, n: Nat, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(prim, dz, vs, vs2))
    -> Law.VRels(prim, dz, Core.Vals.drop(n, vs), Core.Vals.drop(n, vs2)):
  match n:
    case 0n:
      vr
    case 1n+m:
      match vs:
        case Nil{}:
          match vs2:
            case Nil{}:
              Unit{}
            case w <> s:
              match vr:
        case v <> r:
          match vs2:
            case Nil{}:
              match vr:
            case w <> s:
              match vr:
                case (a, b):
                  Drop(prim, dz, m, r, s, b)

def Cat(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, as: List<&2, Core.Val>, as2: List<&2, Core.Val>, +bs: List<&2, Core.Val>, +bs2: List<&2, Core.Val>,
    ra: Law.VRels(prim, dz, as, as2), rb: Law.VRels(prim, dz, bs, bs2)) -> Law.VRels(prim, dz, Core.Vals.cat(as, bs), Core.Vals.cat(as2, bs2)):
  match as:
    case Nil{}:
      match as2:
        case Nil{}:
          rb
        case w <> s:
          match ra:
    case v <> r:
      match as2:
        case Nil{}:
          match ra:
        case w <> s:
          match ra:
            case (a, b):
              (a, Cat(prim, dz, r, s, bs, bs2, b, rb))

# Scopes
# ======

def If.get(b: Bool, -A: Data, h: Law.If(b, A, Unit), e: {True{} == b : Bool}) -> A:
  match b:
    case True{}:
      h
    case False{}:
      Absurd(A, Tru.of(False{}, e))

def If.put(b: Bool, -A: Data, a: A, e: {True{} == b : Bool}) -> Law.If(b, A, Unit):
  match b:
    case True{}:
      a
    case False{}:
      Unit{}

def If.fst(b: Bool, -A: Data, -B: Data, h: Law.If(b, Sigma<&2, &2, A, _ => B>, Unit)) -> Law.If(b, A, Unit):
  match b:
    case True{}:
      match h:
        case (a, c):
          a
    case False{}:
      Unit{}

def Snd(-A: Data, -B: Data, h: Sigma<&2, &2, A, _ => B>) -> B:
  match h:
    case (a, b):
      b

def And.mk(a: Bool, -b: Bool, ea: {True{} == a : Bool}, eb: {True{} == b : Bool}) -> {True{} == Bool.and(a, b) : Bool}:
  match a:
    case True{}:
      eb
    case False{}:
      Absurd({True{} == Bool.and(False{}, b) : Bool}, Tru.of(False{}, ea))

def None.step(+h: String, -r: List<&2, String>, -x: String, +z: String, e: {True{} == Bool.not(String.eq(h, z)) : Bool},
    ih: Sigma<&2, &2, {True{} == Core.Dead.none(r, z) : Bool}, _ => {False{} == String.eq(x, z) : Bool}>)
    -> Sigma<&2, &2, {True{} == Bool.and(Bool.not(String.eq(h, z)), Core.Dead.none(r, z)) : Bool}, _ => {False{} == String.eq(x, z) : Bool}>:
  match ih:
    case (e1, e2):
      (And.mk(Bool.not(String.eq(h, z)), Core.Dead.none(r, z), e, e1), e2)

# Past a binding of x put at the end of hs: past hs, and not x.
def None.cat(hs: List<&2, String>, +x: String, +z: String, +e: {True{} == Core.Dead.none(Core.Dead.cat(hs, [x]), z) : Bool})
    -> Sigma<&2, &2, {True{} == Core.Dead.none(hs, z) : Bool}, _ => {False{} == String.eq(x, z) : Bool}>:
  match hs:
    case Nil{}:
      ({==}, Not.t(String.eq(x, z), And.l(Bool.not(String.eq(x, z)), True{}, e)))
    case +h <> r:
      None.step(h, r, x, z, And.l(Bool.not(String.eq(h, z)), Core.Dead.none(Core.Dead.cat(r, [x]), z), e),
        None.cat(r, x, z, And.r(Bool.not(String.eq(h, z)), Core.Dead.none(Core.Dead.cat(r, [x]), z), e)))

def Gives.mk(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -w: Core.Val, +e: List<&2, Core.Val>, +t: Core.Tm, w2: Core.Val, +m: Nat,
    eq: {Core.run(~prim, m, dz, Core.SEval{e, t}) == Core.ROk{[w2]} : Core.Res}, vr: Law.VRel(prim, dz, w, w2)) -> Law.Gives(prim, dz, w, e, t):
  (w2, m, eq, vr)

def Gives.tpush3(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, +e2: List<&2, Core.Val>, +x: String, +u: Core.Val, +z: String, -w2: Core.Val, +a: Nat,
    eq: {Core.run(~prim, 1n+a, dz, Core.SEval{e2, Core.CVar{z}}) == Core.ROk{[w2]} : Core.Res},
    +ne: {False{} == String.eq(x, z) : Bool})
    -> {Core.run(~prim, 1n+(1n+(1n+a)), dz, Core.SEval{Core.VBnd{x, u} <> e2, Core.CVar{z}}) == Core.ROk{[w2]} : Core.Res}:
  %ne : {Core.run(~prim, 1n+a, dz, Core.SLook2{_, u, e2, z}) == Core.ROk{[w2]} : Core.Res}
  eq

# A lookup of z past a binding of another name.
def Gives.tpush2(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -w: Core.Val, +e2: List<&2, Core.Val>, +x: String, +u: Core.Val, +z: String, w2: Core.Val, m: Nat,
    eq: {Core.run(~prim, m, dz, Core.SEval{e2, Core.CVar{z}}) == Core.ROk{[w2]} : Core.Res}, vr: Law.VRel(prim, dz, w, w2),
    +ne: {False{} == String.eq(x, z) : Bool}) -> Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{z}):
  match m:
    case 0n:
      Ok.no(Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{z}), "out of fuel", [w2], eq)
    case 1n+(+a):
      Gives.mk(~prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{z}, w2, 1n+(1n+(1n+a)), Gives.tpush3(~prim, dz, e2, x, u, z, w2, a, eq, ne), vr)

def Gives.tpush(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -w: Core.Val, +e2: List<&2, Core.Val>, +x: String, +u: Core.Val, +z: String, g: Law.Gives(prim, dz, w, e2, Core.CVar{z}),
    +ne: {False{} == String.eq(x, z) : Bool}) -> Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{z}):
  match g:
    case (w2, m, eq, vr):
      Gives.tpush2(~prim, dz, w, e2, x, u, z, w2, m, eq, vr, ne)

def Hit.eq(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, +x: String, +u: Core.Val, +e2: List<&2, Core.Val>)
    -> {Core.run(~prim, 3n, dz, Core.SEval{Core.VBnd{x, u} <> e2, Core.CVar{x}}) == Core.ROk{[u]} : Core.Res}:
  %Str.refl(x) : {Core.run(~prim, 1n, dz, Core.SLook2{_, u, e2, x}) == Core.ROk{[u]} : Core.Res}
  {==}

# A lookup of x in a scope whose first binding is x's.
def Gives.hit(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -w: Core.Val, +x: String, +u: Core.Val, +e2: List<&2, Core.Val>, vr: Law.VRel(prim, dz, w, u))
    -> Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{x}):
  Gives.mk(~prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{x}, u, 3n, Hit.eq(~prim, dz, x, u, e2), vr)

# What the pass knows past a binding.
def ERel.opq(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, s: List<&2, Core.Sb>, e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, h: Law.ERel(prim, dz, s, e1, hs, e2))
    -> Law.ERel(prim, dz, Core.Sb.opq(s), e1, hs, e2):
  match s:
    case Nil{}:
      h
    case b <> sr:
      match b:
        case Core.SbSub{y, +v2}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (eq, g, rest):
                      (eq, If.fst(Core.Dead.none(hs, z), Law.Gives(prim, dz, w, e2, Core.CVar{z}), Law.Gives(prim, dz, w, e2, v2), g),
                        ERel.opq(~prim, dz, sr, r, z <> hs, e2, rest))
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:
        case Core.SbOpq{y}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (eq, g, rest):
                      (eq, g, ERel.opq(~prim, dz, sr, r, z <> hs, e2, rest))
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:

# A binding of x in front of the other program's scope, at the end of hs
# (past hs, an entry is x's or not).
def Ent.tpush2(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, +hs: List<&2, String>, +x: String, +z: String, -w: Core.Val, +e2: List<&2, Core.Val>, +u: Core.Val,
    p: Sigma<&2, &2, {True{} == Core.Dead.none(hs, z) : Bool}, _ => {False{} == String.eq(x, z) : Bool}>,
    g: Law.If(Core.Dead.none(hs, z), Law.Gives(prim, dz, w, e2, Core.CVar{z}), Unit))
    -> Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{z}):
  match p:
    case (e1, ne):
      Gives.tpush(~prim, dz, w, e2, x, u, z, If.get(Core.Dead.none(hs, z), Law.Gives(prim, dz, w, e2, Core.CVar{z}), g, e1), ne)

def Ent.tpush(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, c: Bool, +hs: List<&2, String>, +x: String, +z: String, -w: Core.Val, +e2: List<&2, Core.Val>, +u: Core.Val,
    he: {c == Core.Dead.none(Core.Dead.cat(hs, [x]), z) : Bool},
    g: Law.If(Core.Dead.none(hs, z), Law.Gives(prim, dz, w, e2, Core.CVar{z}), Unit))
    -> Law.If(c, Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{z}), Unit):
  match c:
    case True{}:
      Ent.tpush2(~prim, dz, hs, x, z, w, e2, u, None.cat(hs, x, z, he), g)
    case False{}:
      Unit{}

def ERel.tpush(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, s: List<&2, Core.Sb>, e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, +x: String, +u: Core.Val, h: Law.ERel(prim, dz, Core.Sb.opq(s), e1, hs, e2))
    -> Law.ERel(prim, dz, Core.Sb.opq(s), e1, Core.Dead.cat(hs, [x]), Core.VBnd{x, u} <> e2):
  match s:
    case Nil{}:
      match e1:
        case Nil{}:
          Unit{}
        case c <> r:
          match h:
    case b <> sr:
      match b:
        case Core.SbSub{y, v2}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (eq, g, rest):
                      (eq, Ent.tpush(~prim, dz, Core.Dead.none(Core.Dead.cat(hs, [x]), z), hs, x, z, w, e2, u, {==}, g),
                        ERel.tpush(~prim, dz, sr, r, z <> hs, e2, x, u, rest))
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:
        case Core.SbOpq{y}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (eq, g, rest):
                      (eq, Ent.tpush(~prim, dz, Core.Dead.none(Core.Dead.cat(hs, [x]), z), hs, x, z, w, e2, u, {==}, g),
                        ERel.tpush(~prim, dz, sr, r, z <> hs, e2, x, u, rest))
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:

# A binding of x in front of both scopes, the pass knowing nothing of it.
def ERel.push(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, +s: List<&2, Core.Sb>, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>, +x: String, -w: Core.Val, +u: Core.Val, vr: Law.VRel(prim, dz, w, u),
    h: Law.ERel(prim, dz, s, e1, Nil{}, e2))
    -> Law.ERel(prim, dz, Core.SbOpq{x} <> Core.Sb.opq(s), Core.VBnd{x, w} <> e1, Nil{}, Core.VBnd{x, u} <> e2):
  ({==}, Gives.hit(~prim, dz, w, x, u, e2, vr), ERel.tpush(~prim, dz, s, e1, Nil{}, e2, x, u, ERel.opq(~prim, dz, s, e1, Nil{}, e2, h)))

# A binding of x in front of the other program's scope, when the source's
# has none of x.
def Ent.fresh(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, c: Bool, +x: String, +z: String, -w: Core.Val, +e2: List<&2, Core.Val>, +u: Core.Val,
    g: Law.If(c, Law.Gives(prim, dz, w, e2, Core.CVar{z}), Unit), +ne: {False{} == String.eq(x, z) : Bool})
    -> Law.If(c, Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, Core.CVar{z}), Unit):
  match c:
    case True{}:
      Gives.tpush(~prim, dz, w, e2, x, u, z, g, ne)
    case False{}:
      Unit{}

def Ne.of(+x: String, +y: String, -z: String, eq: {z == y : String}, f: {True{} == Bool.not(String.eq(x, y)) : Bool})
    -> {False{} == String.eq(x, z) : Bool}:
  %Str.sym(z, y, eq) : {False{} == String.eq(x, _) : Bool}
  Not.t(String.eq(x, y), f)

def ERel.fresh(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, s: List<&2, Core.Sb>, e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, +x: String, +u: Core.Val, h: Law.ERel(prim, dz, Core.Sb.opq(s), e1, hs, e2),
    +f: {True{} == Core.Sb.fresh(s, x) : Bool}) -> Law.ERel(prim, dz, Core.Sb.opq(s), e1, hs, Core.VBnd{x, u} <> e2):
  match s:
    case Nil{}:
      match e1:
        case Nil{}:
          Unit{}
        case c <> r:
          match h:
    case b <> sr:
      match b:
        case Core.SbSub{+y, v2}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (+eq, g, rest):
                      (eq, Ent.fresh(~prim, dz, Core.Dead.none(hs, z), x, z, w, e2, u, g,
                          Ne.of(x, y, z, eq, And.l(Bool.not(String.eq(x, y)), Core.Sb.fresh(sr, x), f))),
                        ERel.fresh(~prim, dz, sr, r, z <> hs, e2, x, u, rest, And.r(Bool.not(String.eq(x, y)), Core.Sb.fresh(sr, x), f)))
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:
        case Core.SbOpq{+y}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (+eq, g, rest):
                      (eq, Ent.fresh(~prim, dz, Core.Dead.none(hs, z), x, z, w, e2, u, g,
                          Ne.of(x, y, z, eq, And.l(Bool.not(String.eq(x, y)), Core.Sb.fresh(sr, x), f))),
                        ERel.fresh(~prim, dz, sr, r, z <> hs, e2, x, u, rest, And.r(Bool.not(String.eq(x, y)), Core.Sb.fresh(sr, x), f)))
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:

# Lookups
# =======

def Gives.rr2(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -w: Core.Val, +e2: List<&2, Core.Val>, +t: Core.Tm, -S0: List<&2, Core.Sb>, +m: Nat, -w2: Core.Val,
    eq: {Core.run(~prim, m, dz, Core.SEval{e2, t}) == Core.ROk{[w2]} : Core.Res}, vr: Law.VRel(prim, dz, w, w2))
    -> Law.RRel(prim, dz, Core.ROk{[w]}, S0, Core.run(~prim, m, dz, Core.SEval{e2, t})):
  %Res.sym(Core.run(~prim, m, dz, Core.SEval{e2, t}), Core.ROk{[w2]}, eq) : Law.RRel(prim, dz, Core.ROk{[w]}, S0, _)
  (vr, Unit{})

# What gives a value related to w: the result of a lookup that gives w.
def Gives.rr(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -w: Core.Val, +e2: List<&2, Core.Val>, +t: Core.Tm, -S0: List<&2, Core.Sb>, g: Law.Gives(prim, dz, w, e2, t))
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, S0, Core.run(~prim, m, dz, Core.SEval{e2, t}))>:
  match g:
    case (w2, +m, eq, vr):
      (m, Gives.rr2(~prim, dz, w, e2, t, S0, m, w2, eq, vr))

def Inv.to(+hs: List<&2, String>, -z: String, -x: String, e: {x == z : String}, inv: {True{} == Core.Dead.none(hs, x) : Bool})
    -> {True{} == Core.Dead.none(hs, z) : Bool}:
  %e : {True{} == Core.Dead.none(hs, _) : Bool}
  inv

def Inv.step(-z: String, -x: String, -hs: List<&2, String>, e: {False{} == String.eq(z, x) : Bool}, inv: {True{} == Core.Dead.none(hs, x) : Bool})
    -> {True{} == Core.Dead.none(z <> hs, x) : Bool}:
  %e : {True{} == Bool.and(Bool.not(_), Core.Dead.none(hs, x)) : Bool}
  inv

# The source's first binding, z's (the pass put v2 in place of its
# lookups): a lookup of x gives it, or goes on.
def Look.sub(~prim: String -> List<&2, Core.Val> -> Core.Res, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, -p2: Nat, +x: String, +z: String, cb: Bool, +he: {cb == String.eq(z, x) : Bool},
    -w: Core.Val, +v2: Core.Tm, +sr: List<&2, Core.Sb>, +r: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, -S0: List<&2, Core.Sb>,
    g: Law.If(Core.Dead.none(hs, z), Sigma<&2, &2, Law.Gives(prim, dz, w, e2, Core.CVar{z}), _ => Law.Gives(prim, dz, w, e2, v2)>, Unit),
    rest: Law.ERel(prim, dz, sr, r, z <> hs, e2), +inv: {True{} == Core.Dead.none(hs, x) : Bool},
    ih: @sr2:List<&2, Core.Sb> -> @r2:List<&2, Core.Val> -> @hs2:List<&2, String> -> Law.ERel(prim, dz, sr2, r2, hs2, e2) -> {True{} == Core.Dead.none(hs2, x) : Bool} ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, p2, ds, Core.SLook{r2, x}), S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(sr2, x)}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+p2, ds, Core.SLook2{cb, w, r, x}), S0,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sub.sel(cb, v2, Core.Sb.find(sr, x))}))>:
  match cb:
    case True{}:
      Gives.rr(~prim, dz, w, e2, v2, S0, Snd(Law.Gives(prim, dz, w, e2, Core.CVar{z}), Law.Gives(prim, dz, w, e2, v2),
        If.get(Core.Dead.none(hs, z), Sigma<&2, &2, Law.Gives(prim, dz, w, e2, Core.CVar{z}), _ => Law.Gives(prim, dz, w, e2, v2)>, g,
          Inv.to(hs, z, x, Str.sym(z, x, Str.eq(z, x, he)), inv))))
    case False{}:
      ih(sr, r, z <> hs, rest, Inv.step(z, x, hs, he, inv))

def Look.opq2(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -w: Core.Val, +e2: List<&2, Core.Val>, +z: String, +x: String, -S0: List<&2, Core.Sb>, e: {z == x : String},
    g: Law.Gives(prim, dz, w, e2, Core.CVar{z}))
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.CVar{x}}))>:
  %e : Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.CVar{_}}))>
  Gives.rr(~prim, dz, w, e2, Core.CVar{z}, S0, g)

# The source's first binding, z's (the pass left its lookups alone).
def Look.opq(~prim: String -> List<&2, Core.Val> -> Core.Res, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, -p2: Nat, +x: String, +z: String, cb: Bool, +he: {cb == String.eq(z, x) : Bool},
    -w: Core.Val, +sr: List<&2, Core.Sb>, +r: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, -S0: List<&2, Core.Sb>,
    g: Law.If(Core.Dead.none(hs, z), Law.Gives(prim, dz, w, e2, Core.CVar{z}), Unit),
    rest: Law.ERel(prim, dz, sr, r, z <> hs, e2), +inv: {True{} == Core.Dead.none(hs, x) : Bool},
    ih: @sr2:List<&2, Core.Sb> -> @r2:List<&2, Core.Val> -> @hs2:List<&2, String> -> Law.ERel(prim, dz, sr2, r2, hs2, e2) -> {True{} == Core.Dead.none(hs2, x) : Bool} ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, p2, ds, Core.SLook{r2, x}), S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(sr2, x)}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+p2, ds, Core.SLook2{cb, w, r, x}), S0,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sub.sel(cb, Core.CVar{x}, Core.Sb.find(sr, x))}))>:
  match cb:
    case True{}:
      Look.opq2(~prim, dz, w, e2, z, x, S0, Str.eq(z, x, he),
        If.get(Core.Dead.none(hs, z), Law.Gives(prim, dz, w, e2, Core.CVar{z}), g, Inv.to(hs, z, x, Str.sym(z, x, Str.eq(z, x, he)), inv)))
    case False{}:
      ih(sr, r, z <> hs, rest, Inv.step(z, x, hs, he, inv))

def Look.sub0(~prim: String -> List<&2, Core.Val> -> Core.Res, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, -p2: Nat, +x: String, +z: String, -y: String, eqzy: {z == y : String},
    -w: Core.Val, +v2: Core.Tm, +sr: List<&2, Core.Sb>, +r: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, -S0: List<&2, Core.Sb>,
    g: Law.If(Core.Dead.none(hs, z), Sigma<&2, &2, Law.Gives(prim, dz, w, e2, Core.CVar{z}), _ => Law.Gives(prim, dz, w, e2, v2)>, Unit),
    rest: Law.ERel(prim, dz, sr, r, z <> hs, e2), +inv: {True{} == Core.Dead.none(hs, x) : Bool},
    ih: @sr2:List<&2, Core.Sb> -> @r2:List<&2, Core.Val> -> @hs2:List<&2, String> -> Law.ERel(prim, dz, sr2, r2, hs2, e2) -> {True{} == Core.Dead.none(hs2, x) : Bool} ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, p2, ds, Core.SLook{r2, x}), S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(sr2, x)}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+p2), ds, Core.SLook{Core.VBnd{z, w} <> r, x}), S0,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(Core.SbSub{y, v2} <> sr, x)}))>:
  %eqzy : Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+p2), ds, Core.SLook{Core.VBnd{z, w} <> r, x}), S0,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(Core.SbSub{_, v2} <> sr, x)}))>
  Look.sub(~prim, ds, dz, p2, x, z, String.eq(z, x), {==}, w, v2, sr, r, hs, e2, S0, g, rest, inv, ih)

def Look.opq0(~prim: String -> List<&2, Core.Val> -> Core.Res, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, -p2: Nat, +x: String, +z: String, -y: String, eqzy: {z == y : String},
    -w: Core.Val, +sr: List<&2, Core.Sb>, +r: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, -S0: List<&2, Core.Sb>,
    g: Law.If(Core.Dead.none(hs, z), Law.Gives(prim, dz, w, e2, Core.CVar{z}), Unit),
    rest: Law.ERel(prim, dz, sr, r, z <> hs, e2), +inv: {True{} == Core.Dead.none(hs, x) : Bool},
    ih: @sr2:List<&2, Core.Sb> -> @r2:List<&2, Core.Val> -> @hs2:List<&2, String> -> Law.ERel(prim, dz, sr2, r2, hs2, e2) -> {True{} == Core.Dead.none(hs2, x) : Bool} ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, p2, ds, Core.SLook{r2, x}), S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(sr2, x)}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+p2), ds, Core.SLook{Core.VBnd{z, w} <> r, x}), S0,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(Core.SbOpq{y} <> sr, x)}))>:
  %eqzy : Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+p2), ds, Core.SLook{Core.VBnd{z, w} <> r, x}), S0,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(Core.SbOpq{_} <> sr, x)}))>
  Look.opq(~prim, ds, dz, p2, x, z, String.eq(z, x), {==}, w, sr, r, hs, e2, S0, g, rest, inv, ih)

# A run of one step of a lookup fails.
def Look.one(~prim: String -> List<&2, Core.Val> -> Core.Res, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, e1: List<&2, Core.Val>, -x: String, -S0: List<&2, Core.Sb>, -t: Core.Sel)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n, ds, Core.SLook{e1, x}), S0, Core.run(~prim, m, dz, t))>:
  match e1:
    case Nil{}:
      (0n, Unit{})
    case c <> r:
      match c:
        case Core.VLit{l}:
          (0n, Unit{})
        case Core.VCtr{k, fs}:
          (0n, Unit{})
        case Core.VClo{env, p, b}:
          (0n, Unit{})
        case Core.VFun{f, as}:
          (0n, Unit{})
        case Core.VTrm{t2}:
          (0n, Unit{})
        case Core.VBnd{y, v}:
          (0n, Unit{})

def Look.go(~prim: String -> List<&2, Core.Val> -> Core.Res, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, -p2: Nat, +x: String, s: List<&2, Core.Sb>, e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, -S0: List<&2, Core.Sb>,
    h: Law.ERel(prim, dz, s, e1, hs, e2), +inv: {True{} == Core.Dead.none(hs, x) : Bool},
    ih: @sr2:List<&2, Core.Sb> -> @r2:List<&2, Core.Val> -> @hs2:List<&2, String> -> Law.ERel(prim, dz, sr2, r2, hs2, e2) -> {True{} == Core.Dead.none(hs2, x) : Bool} ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, p2, ds, Core.SLook{r2, x}), S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(sr2, x)}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+p2), ds, Core.SLook{e1, x}), S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(s, x)}))>:
  match s:
    case Nil{}:
      match e1:
        case Nil{}:
          (0n, Unit{})
        case c <> r:
          match h:
    case b <> sr:
      match b:
        case Core.SbSub{y, +v2}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (eq, g, rest):
                      Look.sub0(~prim, ds, dz, p2, x, z, y, eq, w, v2, sr, r, hs, e2, S0, g, rest, inv, ih)
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:
        case Core.SbOpq{y}:
          match e1:
            case Nil{}:
              match h:
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  match h:
                    case (eq, g, rest):
                      Look.opq0(~prim, ds, dz, p2, x, z, y, eq, w, sr, r, hs, e2, S0, g, rest, inv, ih)
                case Core.VLit{l9}:
                  match h:
                case Core.VCtr{k9, fs9}:
                  match h:
                case Core.VClo{env9, p9, b9}:
                  match h:
                case Core.VFun{f9, as9}:
                  match h:
                case Core.VTrm{t9}:
                  match h:

# A lookup of x, none of hs: the source walks its scope and what the pass
# knew of it together.
def Look(~prim: String -> List<&2, Core.Val> -> Core.Res, +n: Nat, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, +x: String, s: List<&2, Core.Sb>, e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>, -S0: List<&2, Core.Sb>,
    h: Law.ERel(prim, dz, s, e1, hs, e2), +inv: {True{} == Core.Dead.none(hs, x) : Bool})
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, n, ds, Core.SLook{e1, x}), S0, Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.find(s, x)}))>:
  match n:
    case 0n:
      (0n, Unit{})
    case 1n+p:
      match p:
        case 0n:
          Look.one(~prim, ds, dz, e1, x, S0, Core.SEval{e2, Core.Sb.find(s, x)})
        case 1n+p2:
          Look.go(~prim, ds, dz, p2, x, s, e1, hs, e2, S0, h, inv,
            sr2 => r2 => hs2 => h2 => i2 => Look(~prim, p2, ds, dz, x, sr2, r2, hs2, e2, S0, h2, i2))

# Shapes
# ======

# Tm.subst walks a list field as its head and the node rebuilt with the
# rest; these give the node with the field's terms taken as a whole.

def Sh.call(+f: String, as: List<&2, Core.Arg>, +s: List<&2, Core.Sb>)
    -> {Core.CCall{f, Core.Args.subst(as, s)} == Core.Tm.subst(Core.CCall{f, as}, s) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          match rel:
            case Core.Run{}:
              %Sh.call(f, r, s) : {Core.CCall{f, Core.Arg{Core.Run{}, Core.Tm.subst(e, s)} <> Core.Args.subst(r, s)} == Core.Tm.push.call(Core.Arg{Core.Run{}, Core.Tm.subst(e, s)}, _) : Core.Tm}
              {==}
            case Core.Era{}:
              %Sh.call(f, r, s) : {Core.CCall{f, Core.Arg{Core.Era{}, e} <> Core.Args.subst(r, s)} == Core.Tm.push.call(Core.Arg{Core.Era{}, e}, _) : Core.Tm}
              {==}

def Sh.app(+f: Core.Tm, as: List<&2, Core.Tm>, +s: List<&2, Core.Sb>)
    -> {Core.CApp{Core.Tm.subst(f, s), Core.Tms.subst(as, s)} == Core.Tm.subst(Core.CApp{f, as}, s) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %Sh.app(f, r, s) : {Core.CApp{Core.Tm.subst(f, s), Core.Tm.subst(a, s) <> Core.Tms.subst(r, s)} == Core.Tm.push(Core.Tm.subst(a, s), _) : Core.Tm}
      {==}

def Sh.ctr(+k: String, as: List<&2, Core.Tm>, +s: List<&2, Core.Sb>)
    -> {Core.CCtr{k, Core.Tms.subst(as, s)} == Core.Tm.subst(Core.CCtr{k, as}, s) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %Sh.ctr(k, r, s) : {Core.CCtr{k, Core.Tm.subst(a, s) <> Core.Tms.subst(r, s)} == Core.Tm.push(Core.Tm.subst(a, s), _) : Core.Tm}
      {==}

def Sh.cases(cs: List<&2, Core.Tm>, +s: List<&2, Core.Sb>)
    -> {Core.CMat{Nil{}, Core.Tms.subst(cs, s)} == Core.Tm.subst(Core.CMat{Nil{}, cs}, s) : Core.Tm}:
  match cs:
    case Nil{}:
      {==}
    case c <> r:
      %Sh.cases(r, s) : {Core.CMat{Nil{}, Core.Tm.subst(c, s) <> Core.Tms.subst(r, s)} == Core.Tm.push.case(Core.Tm.subst(c, s), _) : Core.Tm}
      {==}

def Sh.mat(scrs: List<&2, Core.Tm>, +cs: List<&2, Core.Tm>, +s: List<&2, Core.Sb>)
    -> {Core.CMat{Core.Tms.subst(scrs, s), Core.Tms.subst(cs, s)} == Core.Tm.subst(Core.CMat{scrs, cs}, s) : Core.Tm}:
  match scrs:
    case Nil{}:
      Sh.cases(cs, s)
    case a <> r:
      %Sh.mat(r, cs, s) : {Core.CMat{Core.Tm.subst(a, s) <> Core.Tms.subst(r, s), Core.Tms.subst(cs, s)} == Core.Tm.push(Core.Tm.subst(a, s), _) : Core.Tm}
      {==}

# Binding
# =======

# A def's parameters bound to related values in front of related scopes,
# with bindings for all of them.
def Bind.push(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(prim, dz, vs, vs2),
    +s: List<&2, Core.Sb>, +acc: List<&2, Core.Val>, +acc2: List<&2, Core.Val>, ha: Law.ERel(prim, dz, s, acc, Nil{}, acc2),
    hl: {False{} == Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)) : Bool})
    -> Law.ERel(prim, dz, Core.Sb.pars(ps, s), Core.Scope.push(ps, vs, acc), Nil{}, Core.Scope.push(ps, vs2, acc2)):
  match ps:
    case Nil{}:
      ha
    case q <> pr:
      match q:
        case Core.Par{+x, rel, mode, ty}:
          match vs:
            case Nil{}:
              Absurd(Law.ERel(prim, dz, Core.Sb.pars(pr, Core.SbOpq{x} <> Core.Sb.opq(s)), Core.Scope.push(Core.Par{x, rel, mode, ty} <> pr, Nil{}, acc), Nil{},
                Core.Scope.push(Core.Par{x, rel, mode, ty} <> pr, vs2, acc2)), Fls.of(True{}, hl))
            case +v <> r:
              match vs2:
                case Nil{}:
                  match vr:
                case +w <> t:
                  match vr:
                    case (a, b):
                      Bind.push(~prim, dz, pr, r, t, b, Core.SbOpq{x} <> Core.Sb.opq(s), Core.VBnd{x, v} <> acc, Core.VBnd{x, w} <> acc2,
                        ERel.push(~prim, dz, s, acc, acc2, x, v, w, a, ha), hl)

# Patterns
# ========

def PatC.mk(h: Bool, -prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, -S: List<&2, Core.Sb>, -e1: List<&2, Core.Val>, +ps: List<&2, Core.Pt>, -vs: List<&2, Core.Val>,
    -e2: List<&2, Core.Val>, -vs2: List<&2, Core.Val>, s: List<&2, Core.Sb>, vr: Law.VRels(prim, dz, vs, vs2), he: Law.ERel(prim, dz, s, e1, Nil{}, e2),
    eS: {Core.Sb.bind(Core.Dead.names(ps), s) == S : List<&2, Core.Sb>})
    -> Law.PatC.rel(prim, dz, h, S, e1, ps, vs, e2, vs2):
  match h:
    case True{}:
      (s, vr, he, eS)
    case False{}:
      Unit{}

def Tr.bs(-a: List<&2, String>, -b: List<&2, String>, e: {a == b : List<&2, String>}, -s: List<&2, Core.Sb>, -S: List<&2, Core.Sb>, h: {Core.Sb.bind(a, s) == S : List<&2, Core.Sb>}) -> {Core.Sb.bind(b, s) == S : List<&2, Core.Sb>}:
  %e : {Core.Sb.bind(_, s) == S : List<&2, Core.Sb>}
  h

# One pattern's step against related values.
def Pat.rel(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, +e1: List<&2, Core.Val>, pt: Core.Pt, +v: Core.Val, +pr: List<&2, Core.Pt>, +vr: List<&2, Core.Val>,
    +e2: List<&2, Core.Val>, +v2: Core.Val, +vr2: List<&2, Core.Val>, -S: List<&2, Core.Sb>, +s: List<&2, Core.Sb>,
    vv: Law.VRel(prim, dz, v, v2), +rr: Law.VRels(prim, dz, vr, vr2), +h: Law.ERel(prim, dz, s, e1, Nil{}, e2),
    +eS: {Core.Sb.bind(Core.Dead.names(pt <> pr), s) == S : List<&2, Core.Sb>})
    -> Law.SRel(prim, dz, Core.Pat.step(e1, pt, v, pr, vr), S, Core.Pat.step(e2, pt, v2, pr, vr2)):
  match pt:
    case Core.PtVar{+x}:
      (Core.VBnd{x, v2} <> e2, vr2, Core.SbOpq{x} <> Core.Sb.opq(s), {==}, rr, ERel.push(~prim, dz, s, e1, e2, x, v, v2, vv, h), eS)
    case Core.PtCtr{+k, +qs}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              (e2, vr2, {==}, Unit{})
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
                case (ek, +vf):
                  %ek : Law.SRel(prim, dz, Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, S, Core.SPatC{Bool.and(String.eq(k, _), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs2))), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  %Len.eq(prim, dz, fs1, fs2, vf) : Law.SRel(prim, dz, Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, S, Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), _)), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  (e2, Core.Vals.cat(fs2, vr2), {==}, PatC.mk(Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), prim, dz, S, e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr), e2, Core.Vals.cat(fs2, vr2), s,
                    Cat(prim, dz, fs1, fs2, vr, vr2, vf, rr), h, Tr.bs(Core.Dead.cat(Core.Dead.names(qs), Core.Dead.names(pr)), Core.Dead.names(Core.Pts.cat(qs, pr)), DP.Names.cat(qs, pr), s, S, eS)))
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtNat{+n}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              %vv : Law.SRel(prim, dz, Core.Pat.step(e1, Core.PtNat{n}, Core.VLit{l1}, pr, vr), S, Core.Pat.step(e2, Core.PtNat{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LNat{n}, l1), prim, dz, S, e1, pr, vr, e2, vr2, s, rr, h, eS))
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtNum{+n}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              %vv : Law.SRel(prim, dz, Core.Pat.step(e1, Core.PtNum{n}, Core.VLit{l1}, pr, vr), S, Core.Pat.step(e2, Core.PtNum{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LNum{n}, l1), prim, dz, S, e1, pr, vr, e2, vr2, s, rr, h, eS))
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtFlt{+n}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              %vv : Law.SRel(prim, dz, Core.Pat.step(e1, Core.PtFlt{n}, Core.VLit{l1}, pr, vr), S, Core.Pat.step(e2, Core.PtFlt{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LFlt{n}, l1), prim, dz, S, e1, pr, vr, e2, vr2, s, rr, h, eS))
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtSuc{+k, +q}:
      match v:
        case Core.VLit{l1}:
          match l1:
            case Core.LNum{x9}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(prim, dz, Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LNum{x9}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, Unit{})
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
            case Core.LNat{+m}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(prim, dz, Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LNat{m}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr2, {==}, PatC.mk(U32.is_le(k, m), prim, dz, S, e1, q <> pr, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr,
                    e2, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr2, s, ({==}, rr), h, eS))
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
            case Core.LFlt{x9}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(prim, dz, Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LFlt{x9}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, Unit{})
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
            case Core.LStr{x9}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(prim, dz, Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LStr{x9}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, Unit{})
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})

# A let whose value goes in place
# ===============================

# The body's scope: the let's binding in front, the pass knowing v2 gives
# its value there (kn).
def ERel.let(~prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, +s: List<&2, Core.Sb>, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>, +x: String, -w: Core.Val, +u: Core.Val, -v2: Core.Tm,
    vr: Law.VRel(prim, dz, w, u), kn: Law.Gives(prim, dz, w, Core.VBnd{x, u} <> e2, v2), h: Law.ERel(prim, dz, s, e1, Nil{}, e2))
    -> Law.ERel(prim, dz, Core.SbSub{x, v2} <> Core.Sb.opq(s), Core.VBnd{x, w} <> e1, Nil{}, Core.VBnd{x, u} <> e2):
  ({==}, (Gives.hit(~prim, dz, w, x, u, e2, vr), kn), ERel.tpush(~prim, dz, s, e1, Nil{}, e2, x, u, ERel.opq(~prim, dz, s, e1, Nil{}, e2, h)))

# The other program's run of the let: the value gives u (with fuel m1),
# then the body runs with fuel 1+Sum(m1, m4), more than rr4's.
def Let.fin(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, +dz: List<&2, Core.Def>, +f: Nat, -S: List<&2, Core.Sb>, +x: String, +w: Core.Val, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>,
    +b: Core.Tm, +v2: Core.Tm, +b2: Core.Tm, +m1: Nat, +m4: Nat, +u: Core.Val,
    +eq1: {Core.run(~prim, m1, dz, Core.SEval{e2, v2}) == Core.ROk{[u]} : Core.Res},
    rr4: Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+(1n+(1n+f))), ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, m4, dz, Core.SEval{Core.VBnd{x, u} <> e2, b2})))
    -> Law.RRel(prim, dz, Core.run(~prim, 1n+f, ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, 1n+(1n+(1n+(1n+(1n+Sum(m1, m4))))), dz, Core.SEval{e2, Core.CLet{Core.PtVar{x}, v2, b2}})):
  %Res.tr(Core.run(~prim, m1, dz, Core.SEval{e2, v2}), Core.ROk{[u]}, Core.run(~prim, 1n+(1n+(1n+(1n+Sum(m1, m4)))), dz, Core.SEval{e2, v2}), eq1,
    RP.L.mono(~prim, m1, 1n+(1n+(1n+(1n+Sum(m1, m4)))),
      RP.Le.succ(m1, 1n+(1n+(1n+Sum(m1, m4))), RP.Le.succ(m1, 1n+(1n+Sum(m1, m4)), RP.Le.succ(m1, 1n+Sum(m1, m4), RP.Le.succ(m1, Sum(m1, m4), Le.suml(m1, m4))))),
      dz, Core.SEval{e2, v2},
      NF.tr(Core.run(~prim, m1, dz, Core.SEval{e2, v2}), Core.ROk{[u]}, Res.sym(Core.run(~prim, m1, dz, Core.SEval{e2, v2}), Core.ROk{[u]}, eq1), Unit{})))
    : Law.RRel(prim, dz, Core.run(~prim, 1n+f, ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, 1n+(1n+(1n+(1n+Sum(m1, m4)))), dz, Core.SThen{_, Core.KLet{e2, Core.PtVar{x}, b2}}))
  Tgt.mono(~prim, dz, Core.run(~prim, 1n+f, ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S, m4, 1n+Sum(m1, m4),
    RP.Le.succ(m4, Sum(m1, m4), Le.sumr(m1, m4)), Core.SEval{Core.VBnd{x, u} <> e2, b2},
    Src.mono(~prim, ds, dz, 1n+f, 1n+(1n+(1n+(1n+f))), RP.Le.succ(f, 1n+(1n+f), RP.Le.succ(f, 1n+f, RP.Le.succ(f, f, RP.Le.refl(f)))),
      Core.SEval{Core.VBnd{x, w} <> e1, b}, S, Core.run(~prim, m4, dz, Core.SEval{Core.VBnd{x, u} <> e2, b2}), rr4))

def Let.b4(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, +dz: List<&2, Core.Def>, +f: Nat, -S: List<&2, Core.Sb>, +x: String, +w: Core.Val, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>,
    +b: Core.Tm, +v2: Core.Tm, +b2: Core.Tm, +m1: Nat, +u: Core.Val,
    +eq1: {Core.run(~prim, m1, dz, Core.SEval{e2, v2}) == Core.ROk{[u]} : Core.Res},
    h4: Sigma<&2, &2, Nat, m4 => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+(1n+(1n+f))), ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, m4, dz, Core.SEval{Core.VBnd{x, u} <> e2, b2}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+f, ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.CLet{Core.PtVar{x}, v2, b2}}))>:
  match h4:
    case (+m4, rr4):
      (1n+(1n+(1n+(1n+(1n+Sum(m1, m4))))), Let.fin(~prim, ds, dz, f, S, x, w, e1, e2, b, v2, b2, m1, m4, u, eq1, rr4))

def Let.b3(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, +dz: List<&2, Core.Def>, +f: Nat, -S: List<&2, Core.Sb>, -s: List<&2, Core.Sb>, +x: String, +w: Core.Val, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>,
    +b: Core.Tm, +v2: Core.Tm, +b2: Core.Tm, +m1: Nat, +u: Core.Val,
    +eq1: {Core.run(~prim, m1, dz, Core.SEval{e2, v2}) == Core.ROk{[u]} : Core.Res}, vru: Law.VRel(prim, dz, w, u),
    ih2: @u2:Core.Val -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, Core.Sb.opq(s), Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u2} <> e2, v2}))>,
    ih3: @w3:Core.Val -> @u3:Core.Val -> Law.VRel(prim, dz, w3, u3) -> Law.Gives(prim, dz, w3, Core.VBnd{x, u3} <> e2, v2) ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+(1n+(1n+f))), ds, Core.SEval{Core.VBnd{x, w3} <> e1, b}), S,
        Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u3} <> e2, b2}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+f, ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.CLet{Core.PtVar{x}, v2, b2}}))>:
  Let.b4(~prim, ds, dz, f, S, x, w, e1, e2, b, v2, b2, m1, u, eq1,
    ih3(w, u, vru, Gives.of(~prim, dz, Core.Sb.opq(s), w, Core.VBnd{x, u} <> e2, v2, ih2(u))))

def Let.b2(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, +dz: List<&2, Core.Def>, +f: Nat, -S: List<&2, Core.Sb>, -s: List<&2, Core.Sb>, +x: String, +w: Core.Val, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>,
    +b: Core.Tm, +v2: Core.Tm, +b2: Core.Tm, +m1: Nat, r2: Core.Res, +eq: {Core.run(~prim, m1, dz, Core.SEval{e2, v2}) == r2 : Core.Res},
    rr1: Law.RRel(prim, dz, Core.ROk{[w]}, Core.Sb.opq(s), r2),
    ih2: @u2:Core.Val -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, Core.Sb.opq(s), Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u2} <> e2, v2}))>,
    ih3: @w3:Core.Val -> @u3:Core.Val -> Law.VRel(prim, dz, w3, u3) -> Law.Gives(prim, dz, w3, Core.VBnd{x, u3} <> e2, v2) ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+(1n+(1n+f))), ds, Core.SEval{Core.VBnd{x, w3} <> e1, b}), S,
        Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u3} <> e2, b2}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+f, ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.CLet{Core.PtVar{x}, v2, b2}}))>:
  match r2:
    case Core.ROk{vs2}:
      match vs2:
        case Nil{}:
          match rr1:
        case +u <> t:
          match t:
            case Nil{}:
              match rr1:
                case (vru, un):
                  Let.b3(~prim, ds, dz, f, S, s, x, w, e1, e2, b, v2, b2, m1, u, eq, vru, ih2, ih3)
            case u2 <> t2:
              match rr1:
                case (vru, un):
                  match un:
    case Core.REnv{e}:
      match rr1:
    case Core.RNo{}:
      match rr1:
    case Core.RFail{m}:
      match rr1:

# The let's value gave w: the source's steps to the body are taken at once.
def Let.body(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, +dz: List<&2, Core.Def>, +f: Nat, -S: List<&2, Core.Sb>, -s: List<&2, Core.Sb>, +x: String, +w: Core.Val, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>,
    +b: Core.Tm, +v2: Core.Tm, +b2: Core.Tm,
    ih1: Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, Core.Sb.opq(s), Core.run(~prim, m, dz, Core.SEval{e2, v2}))>,
    ih2: @u2:Core.Val -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.ROk{[w]}, Core.Sb.opq(s), Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u2} <> e2, v2}))>,
    ih3: @w3:Core.Val -> @u3:Core.Val -> Law.VRel(prim, dz, w3, u3) -> Law.Gives(prim, dz, w3, Core.VBnd{x, u3} <> e2, v2) ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+(1n+(1n+(1n+f))), ds, Core.SEval{Core.VBnd{x, w3} <> e1, b}), S,
        Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u3} <> e2, b2}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+f, ds, Core.SEval{Core.VBnd{x, w} <> e1, b}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.CLet{Core.PtVar{x}, v2, b2}}))>:
  match ih1:
    case (+m1, rr1):
      Let.b2(~prim, ds, dz, f, S, s, x, w, e1, e2, b, v2, b2, m1, Core.run(~prim, m1, dz, Core.SEval{e2, v2}), {==}, rr1, ih2, ih3)

# A let whose value v (it gives r with fuel p) goes in place of x's
# lookups: v2 in the other program. The source fails unless r is one
# value.
def Let.sub(~prim: String -> List<&2, Core.Val> -> Core.Res, +ds: List<&2, Core.Def>, +dz: List<&2, Core.Def>, r: Core.Res, +p: Nat, -S: List<&2, Core.Sb>, -s: List<&2, Core.Sb>, +x: String, +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>,
    +b: Core.Tm, +v2: Core.Tm, +b2: Core.Tm,
    ih1: Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, r, Core.Sb.opq(s), Core.run(~prim, m, dz, Core.SEval{e2, v2}))>,
    ih2: @u2:Core.Val -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, r, Core.Sb.opq(s), Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u2} <> e2, v2}))>,
    ih3: @w3:Core.Val -> @u3:Core.Val -> Law.VRel(prim, dz, w3, u3) -> Law.Gives(prim, dz, w3, Core.VBnd{x, u3} <> e2, v2) ->
      Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, p, ds, Core.SEval{Core.VBnd{x, w3} <> e1, b}), S,
        Core.run(~prim, m, dz, Core.SEval{Core.VBnd{x, u3} <> e2, b2}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, p, ds, Core.SThen{r, Core.KLet{e1, Core.PtVar{x}, b}}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.CLet{Core.PtVar{x}, v2, b2}}))>:
  match r:
    case Core.ROk{vs}:
      match vs:
        case Nil{}:
          match p:
            case 0n:
              (0n, Unit{})
            case 1n+p1:
              match p1:
                case 0n:
                  (0n, Unit{})
                case 1n+p2:
                  match p2:
                    case 0n:
                      (0n, Unit{})
                    case 1n+p3:
                      (0n, Unit{})
        case +w <> rest:
          match rest:
            case Nil{}:
              match p:
                case 0n:
                  (0n, Unit{})
                case 1n+p1:
                  match p1:
                    case 0n:
                      (0n, Unit{})
                    case 1n+p2:
                      match p2:
                        case 0n:
                          (0n, Unit{})
                        case 1n+p3:
                          match p3:
                            case 0n:
                              (0n, Unit{})
                            case 1n+(+f):
                              Let.body(~prim, ds, dz, f, S, s, x, w, e1, e2, b, v2, b2, ih1, ih2, ih3)
            case w2 <> rest2:
              match p:
                case 0n:
                  (0n, Unit{})
                case 1n+p1:
                  match p1:
                    case 0n:
                      (0n, Unit{})
                    case 1n+p2:
                      match p2:
                        case 0n:
                          (0n, Unit{})
                        case 1n+p3:
                          match p3:
                            case 0n:
                              (0n, Unit{})
                            case 1n+p4:
                              (0n, Unit{})
    case Core.REnv{e}:
      match p:
        case 0n:
          (0n, Unit{})
        case 1n+p1:
          (0n, Unit{})
    case Core.RNo{}:
      match p:
        case 0n:
          (0n, Unit{})
        case 1n+p1:
          (0n, Unit{})
    case Core.RFail{m}:
      match p:
        case 0n:
          (0n, Unit{})
        case 1n+p1:
          (0n, Unit{})

# The pass's decision at a let of x: in place (hT, from x being fresh) or
# not (hF).
def Let.dec(~prim: String -> List<&2, Core.Val> -> Core.Res, -ds: List<&2, Core.Def>, -dz: List<&2, Core.Def>, -p: Nat, -S: List<&2, Core.Sb>, -e1: List<&2, Core.Val>, -e2: List<&2, Core.Val>, +s: List<&2, Core.Sb>, +x: String, +v: Core.Tm, +b: Core.Tm,
    cb: Bool, he: {cb == Bool.and(Core.Sb.fresh(s, x), Core.Sb.want(x, v, b)) : Bool},
    hT: @ef:{True{} == Core.Sb.fresh(s, x) : Bool} -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x}, v, b}}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.let(True{}, x, s2 => Core.Tm.subst(v, s2), s2 => Core.Tm.subst(b, s2), s)}))>,
    hF: Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x}, v, b}}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.let(False{}, x, s2 => Core.Tm.subst(v, s2), s2 => Core.Tm.subst(b, s2), s)}))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x}, v, b}}), S,
      Core.run(~prim, m, dz, Core.SEval{e2, Core.Sb.let(cb, x, s2 => Core.Tm.subst(v, s2), s2 => Core.Tm.subst(b, s2), s)}))>:
  match cb:
    case True{}:
      hT(And.l(Core.Sb.fresh(s, x), Core.Sb.want(x, v, b), he))
    case False{}:
      hF

# The induction
# =============

def Enter.eq(+ps: List<&2, Core.Par>, -vs: List<&2, Core.Val>, -vs2: List<&2, Core.Val>, -f: String, -b: Core.Tm, e: {Core.Vals.len(vs) == Core.Vals.len(vs2) : Nat})
    -> {Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, b, vs2} == Core.SEnter{Nat.is_lt(Core.Vals.len(vs2), Core.Pars.len(ps)), f, ps, b, vs2} : Core.Sel}:
  %e : {Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, b, vs2} == Core.SEnter{Nat.is_lt(_, Core.Pars.len(ps)), f, ps, b, vs2} : Core.Sel}
  {==}

# One step of the source, from related states (ih: the law for fewer steps).
def Step(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ds: List<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(prim, Core.Defs.subst(ds), vs1, vs2) -> Law.PRel(prim, Core.Defs.subst(ds), prim(op, vs1), prim(op, vs2)), +p: Nat, +S: List<&2, Core.Sb>, s1: Core.Sel, s2: Core.Sel, rel: Law.SRel(prim, Core.Defs.subst(ds), s1, S, s2), ih: @S2:List<&2, Core.Sb> -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(prim, Core.Defs.subst(ds), t1, S2, t2) -> Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, t1), S2, Core.run(~prim, m, Core.Defs.subst(ds), t2))>, ih2: @S2:List<&2, Core.Sb> -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(prim, Core.Defs.subst(ds), t1, S2, t2) -> Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, t1), S2, Core.run(~prim, m, Core.Defs.subst(ds), t2))>, ih3: @S2:List<&2, Core.Sb> -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(prim, Core.Defs.subst(ds), t1, S2, t2) -> Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, t1), S2, Core.run(~prim, m, Core.Defs.subst(ds), t2))>, ih4: @S2:List<&2, Core.Sb> -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(prim, Core.Defs.subst(ds), t1, S2, t2) -> Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, t1), S2, Core.run(~prim, m, Core.Defs.subst(ds), t2))>, ih5: @S2:List<&2, Core.Sb> -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(prim, Core.Defs.subst(ds), t1, S2, t2) -> Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, t1), S2, Core.run(~prim, m, Core.Defs.subst(ds), t2))>)
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, s1), S, Core.run(~prim, m, Core.Defs.subst(ds), s2))>:
  match s1:
    case Core.SEval{+e1, t}:
      match t:
        case Core.CVar{+x}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CVar{x}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Look(~prim, p, ds, Core.Defs.subst(ds), x, s, e1, Nil{}, e2, S, h, {==})
        case Core.CLit{+l}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLit{l}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}), S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, Core.SEval{e2, Core.CLit{l}}, ih(S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, (Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}, S, {==}, (Core.VLit{l}, {==}, {==}), Unit{})), M => {==})
        case Core.CRef{+f}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CRef{f}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SCallDef{f, Nil{}}), S, Core.SCallDef{f, Nil{}}, Core.SEval{e2, Core.CRef{f}}, ih(S, Core.SCallDef{f, Nil{}}, Core.SCallDef{f, Nil{}}, (Nil{}, {==}, Unit{})), M => {==})
        case Core.CCall{+f, +as}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %Sh.call(f, as, s) : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SEval{e2, _}))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, as}), Core.KCall{f}}), S, Core.run(~prim, p, ds, Core.SArgs{e1, as}), s, Core.SArgs{e2, Core.Args.subst(as, s)}, Core.KCall{f}, Core.SEval{e2, Core.CCall{f, Core.Args.subst(as, s)}},
                ih(s, Core.SArgs{e1, as}, Core.SArgs{e2, Core.Args.subst(as, s)}, (e2, s, {==}, h)),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, as}), Core.KCall{f}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SArgs{e2, Core.Args.subst(as, s)}), Core.KCall{f}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SArgs{e2, Core.Args.subst(as, s)}), Core.KCall{f}, s, {==}, {==}, rr1)),
                M => {==})
        case Core.CApp{+f, +as}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CApp{f, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %Sh.app(f, as, s) : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CApp{f, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SEval{e2, _}))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, f <> as}), Core.KApp{}}), S, Core.run(~prim, p, ds, Core.SEvals{e1, f <> as}), s, Core.SEvals{e2, Core.Tm.subst(f, s) <> Core.Tms.subst(as, s)}, Core.KApp{}, Core.SEval{e2, Core.CApp{Core.Tm.subst(f, s), Core.Tms.subst(as, s)}},
                ih(s, Core.SEvals{e1, f <> as}, Core.SEvals{e2, Core.Tm.subst(f, s) <> Core.Tms.subst(as, s)}, (e2, s, {==}, h)),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, f <> as}), Core.KApp{}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, Core.Tm.subst(f, s) <> Core.Tms.subst(as, s)}), Core.KApp{}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, Core.Tm.subst(f, s) <> Core.Tms.subst(as, s)}), Core.KApp{}, s, {==}, {==}, rr1)),
                M => {==})
        case Core.CCtr{+k, +as}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCtr{k, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %Sh.ctr(k, as, s) : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCtr{k, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SEval{e2, _}))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, as}), Core.KCtr{k}}), S, Core.run(~prim, p, ds, Core.SEvals{e1, as}), s, Core.SEvals{e2, Core.Tms.subst(as, s)}, Core.KCtr{k}, Core.SEval{e2, Core.CCtr{k, Core.Tms.subst(as, s)}},
                ih(s, Core.SEvals{e1, as}, Core.SEvals{e2, Core.Tms.subst(as, s)}, (e2, s, {==}, h)),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, as}), Core.KCtr{k}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, Core.Tms.subst(as, s)}), Core.KCtr{k}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, Core.Tms.subst(as, s)}), Core.KCtr{k}, s, {==}, {==}, rr1)),
                M => {==})
        case Core.CLam{+p0, +b}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLam{p0, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e1, p0, b}}}), S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, p0, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([p0]), s))}}}, Core.SEval{e2, Core.CLam{p0, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([p0]), s))}}, ih(S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e1, p0, b}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, p0, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([p0]), s))}}}, (Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, p0, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([p0]), s))}}, S, {==}, (Core.VClo{e2, p0, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([p0]), s))}, {==}, ({==}, s, {==}, h)), Unit{})), M => {==})
        case Core.CLet{p0, +v, +b}:
          match p0:
            case Core.PtVar{+x}:
              match rel:
                case (+e2, +s, eq, +h):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x}, v, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Let.dec(~prim, ds, Core.Defs.subst(ds), p, S, e1, e2, s, x, v, b, Bool.and(Core.Sb.fresh(s, x), Core.Sb.want(x, v, b)), {==},
                    ef => Let.sub(~prim, ds, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SEval{e1, v}), p, S, s, x, e1, e2, b, Core.Tm.subst(v, Core.Sb.opq(s)), Core.Tm.subst(b, Core.SbSub{x, Core.Tm.subst(v, Core.Sb.opq(s))} <> Core.Sb.opq(s)),
                      ih(Core.Sb.opq(s), Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.subst(v, Core.Sb.opq(s))}, (e2, Core.Sb.opq(s), {==}, ERel.opq(~prim, Core.Defs.subst(ds), s, e1, Nil{}, e2, h))),
                      +u => ih2(Core.Sb.opq(s), Core.SEval{e1, v}, Core.SEval{Core.VBnd{x, u} <> e2, Core.Tm.subst(v, Core.Sb.opq(s))}, (Core.VBnd{x, u} <> e2, Core.Sb.opq(s), {==}, ERel.fresh(~prim, Core.Defs.subst(ds), s, e1, Nil{}, e2, x, u, ERel.opq(~prim, Core.Defs.subst(ds), s, e1, Nil{}, e2, h), ef))),
                      +w => +u => vr => kn => ih3(S, Core.SEval{Core.VBnd{x, w} <> e1, b}, Core.SEval{Core.VBnd{x, u} <> e2, Core.Tm.subst(b, Core.SbSub{x, Core.Tm.subst(v, Core.Sb.opq(s))} <> Core.Sb.opq(s))}, (Core.VBnd{x, u} <> e2, Core.SbSub{x, Core.Tm.subst(v, Core.Sb.opq(s))} <> Core.Sb.opq(s), {==}, ERel.let(~prim, Core.Defs.subst(ds), s, e1, e2, x, w, u, Core.Tm.subst(v, Core.Sb.opq(s)), vr, kn, h)))),
                    Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtVar{x}, b}}), S, Core.run(~prim, p, ds, Core.SEval{e1, v}), s, Core.SEval{e2, Core.Tm.subst(v, s)}, Core.KLet{e2, Core.PtVar{x}, Core.Tm.subst(b, Core.SbOpq{x} <> Core.Sb.opq(s))}, Core.SEval{e2, Core.CLet{Core.PtVar{x}, Core.Tm.subst(v, s), Core.Tm.subst(b, Core.SbOpq{x} <> Core.Sb.opq(s))}},
                      ih4(s, Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.subst(v, s)}, (e2, s, {==}, h)),
                      +m1 => rr1 => ih5(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtVar{x}, b}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtVar{x}, Core.Tm.subst(b, Core.SbOpq{x} <> Core.Sb.opq(s))}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtVar{x}, Core.Tm.subst(b, Core.SbOpq{x} <> Core.Sb.opq(s))}, s, {==}, (e2, s, {==}, h), rr1)),
                      M => {==}))
            case Core.PtCtr{+k9, +ps9}:
              match rel:
                case (+e2, +s, eq, +h):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtCtr{k9, ps9}, v, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtCtr{k9, ps9}, b}}), S, Core.run(~prim, p, ds, Core.SEval{e1, v}), s, Core.SEval{e2, Core.Tm.subst(v, s)}, Core.KLet{e2, Core.PtCtr{k9, ps9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtCtr{k9, ps9}]), s))}, Core.SEval{e2, Core.CLet{Core.PtCtr{k9, ps9}, Core.Tm.subst(v, s), Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtCtr{k9, ps9}]), s))}},
                    ih(s, Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.subst(v, s)}, (e2, s, {==}, h)),
                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtCtr{k9, ps9}, b}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtCtr{k9, ps9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtCtr{k9, ps9}]), s))}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtCtr{k9, ps9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtCtr{k9, ps9}]), s))}, s, {==}, (e2, s, {==}, h), rr1)),
                    M => {==})
            case Core.PtNat{+n9}:
              match rel:
                case (+e2, +s, eq, +h):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtNat{n9}, v, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtNat{n9}, b}}), S, Core.run(~prim, p, ds, Core.SEval{e1, v}), s, Core.SEval{e2, Core.Tm.subst(v, s)}, Core.KLet{e2, Core.PtNat{n9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNat{n9}]), s))}, Core.SEval{e2, Core.CLet{Core.PtNat{n9}, Core.Tm.subst(v, s), Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNat{n9}]), s))}},
                    ih(s, Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.subst(v, s)}, (e2, s, {==}, h)),
                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtNat{n9}, b}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtNat{n9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNat{n9}]), s))}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtNat{n9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNat{n9}]), s))}, s, {==}, (e2, s, {==}, h), rr1)),
                    M => {==})
            case Core.PtSuc{+k9, +p9}:
              match rel:
                case (+e2, +s, eq, +h):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtSuc{k9, p9}, v, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtSuc{k9, p9}, b}}), S, Core.run(~prim, p, ds, Core.SEval{e1, v}), s, Core.SEval{e2, Core.Tm.subst(v, s)}, Core.KLet{e2, Core.PtSuc{k9, p9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtSuc{k9, p9}]), s))}, Core.SEval{e2, Core.CLet{Core.PtSuc{k9, p9}, Core.Tm.subst(v, s), Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtSuc{k9, p9}]), s))}},
                    ih(s, Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.subst(v, s)}, (e2, s, {==}, h)),
                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtSuc{k9, p9}, b}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtSuc{k9, p9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtSuc{k9, p9}]), s))}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtSuc{k9, p9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtSuc{k9, p9}]), s))}, s, {==}, (e2, s, {==}, h), rr1)),
                    M => {==})
            case Core.PtNum{+n9}:
              match rel:
                case (+e2, +s, eq, +h):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtNum{n9}, v, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtNum{n9}, b}}), S, Core.run(~prim, p, ds, Core.SEval{e1, v}), s, Core.SEval{e2, Core.Tm.subst(v, s)}, Core.KLet{e2, Core.PtNum{n9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNum{n9}]), s))}, Core.SEval{e2, Core.CLet{Core.PtNum{n9}, Core.Tm.subst(v, s), Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNum{n9}]), s))}},
                    ih(s, Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.subst(v, s)}, (e2, s, {==}, h)),
                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtNum{n9}, b}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtNum{n9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNum{n9}]), s))}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtNum{n9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtNum{n9}]), s))}, s, {==}, (e2, s, {==}, h), rr1)),
                    M => {==})
            case Core.PtFlt{+s9}:
              match rel:
                case (+e2, +s, eq, +h):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtFlt{s9}, v, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtFlt{s9}, b}}), S, Core.run(~prim, p, ds, Core.SEval{e1, v}), s, Core.SEval{e2, Core.Tm.subst(v, s)}, Core.KLet{e2, Core.PtFlt{s9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtFlt{s9}]), s))}, Core.SEval{e2, Core.CLet{Core.PtFlt{s9}, Core.Tm.subst(v, s), Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtFlt{s9}]), s))}},
                    ih(s, Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.subst(v, s)}, (e2, s, {==}, h)),
                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, Core.PtFlt{s9}, b}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtFlt{s9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtFlt{s9}]), s))}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(v, s)}), Core.KLet{e2, Core.PtFlt{s9}, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([Core.PtFlt{s9}]), s))}, s, {==}, (e2, s, {==}, h), rr1)),
                    M => {==})
        case Core.CMat{+scrs, +cases}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CMat{scrs, cases}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %Sh.mat(scrs, cases, s) : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CMat{scrs, cases}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SEval{e2, _}))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, scrs}), Core.KMat{e1, cases}}), S, Core.run(~prim, p, ds, Core.SEvals{e1, scrs}), s, Core.SEvals{e2, Core.Tms.subst(scrs, s)}, Core.KMat{e2, Core.Tms.subst(cases, s)}, Core.SEval{e2, Core.CMat{Core.Tms.subst(scrs, s), Core.Tms.subst(cases, s)}},
                ih(s, Core.SEvals{e1, scrs}, Core.SEvals{e2, Core.Tms.subst(scrs, s)}, (e2, s, {==}, h)),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, scrs}), Core.KMat{e1, cases}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, Core.Tms.subst(scrs, s)}), Core.KMat{e2, Core.Tms.subst(cases, s)}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, Core.Tms.subst(scrs, s)}), Core.KMat{e2, Core.Tms.subst(cases, s)}, s, {==}, (e2, s, {==}, h), rr1)),
                M => {==})
        case Core.CCse{+ps, +b}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCse{ps, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}), S, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, Core.SEval{e2, Core.CCse{ps, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names(ps), s))}}, ih(S, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, (Core.RFail{"a case outside a match"}, Core.KApp{}, S, {==}, {==}, Unit{})), M => {==})
        case Core.CSuc{+k, +e}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CSuc{k, e}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KSuc{k}}), S, Core.run(~prim, p, ds, Core.SEval{e1, e}), s, Core.SEval{e2, Core.Tm.subst(e, s)}, Core.KSuc{k}, Core.SEval{e2, Core.CSuc{k, Core.Tm.subst(e, s)}},
                ih(s, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.subst(e, s)}, (e2, s, {==}, h)),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KSuc{k}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(e, s)}), Core.KSuc{k}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(e, s)}), Core.KSuc{k}, s, {==}, {==}, rr1)),
                M => {==})
        case Core.COp{+op, +a, +b}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.COp{op, a, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, [a, b]}), Core.KOp{op}}), S, Core.run(~prim, p, ds, Core.SEvals{e1, [a, b]}), s, Core.SEvals{e2, [Core.Tm.subst(a, s), Core.Tm.subst(b, s)]}, Core.KOp{op}, Core.SEval{e2, Core.COp{op, Core.Tm.subst(a, s), Core.Tm.subst(b, s)}},
                ih(s, Core.SEvals{e1, [a, b]}, Core.SEvals{e2, [Core.Tm.subst(a, s), Core.Tm.subst(b, s)]}, (e2, s, {==}, h)),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, [a, b]}), Core.KOp{op}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, [Core.Tm.subst(a, s), Core.Tm.subst(b, s)]}), Core.KOp{op}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e2, [Core.Tm.subst(a, s), Core.Tm.subst(b, s)]}), Core.KOp{op}, s, {==}, {==}, rr1)),
                M => {==})
        case Core.CAnn{+e, +ty}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CAnn{e, ty}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SEval{e1, e}), S, Core.SEval{e2, Core.Tm.subst(e, s)}, Core.SEval{e2, Core.CAnn{Core.Tm.subst(e, s), ty}}, ih(S, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.subst(e, s)}, (e2, s, {==}, h)), M => {==})
        case Core.CTyp{+name, +args}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CTyp{name, args}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}), S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SEval{e2, Core.CTyp{name, args}}, ih(S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, (Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, S, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})), M => {==})
        case Core.CBox{}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CBox{}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}), S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SEval{e2, Core.CBox{}}, ih(S, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, (Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, S, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})), M => {==})
        case Core.CErr{+msg}:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CErr{msg}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.RFail{msg}, Core.KApp{}}), S, Core.SThen{Core.RFail{msg}, Core.KApp{}}, Core.SEval{e2, Core.CErr{msg}}, ih(S, Core.SThen{Core.RFail{msg}, Core.KApp{}}, Core.SThen{Core.RFail{msg}, Core.KApp{}}, (Core.RFail{msg}, Core.KApp{}, S, {==}, {==}, Unit{})), M => {==})
    case Core.SEvals{+e1, es}:
      match es:
        case Nil{}:
          match rel:
            case (e2, s, eq, h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEvals{e1, Nil{}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              (1n, Unit{})
        case +e <> +r:
          match rel:
            case (+e2, +s, eq, +h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEvals{e1, e <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KTail{e1, r}}), S, Core.run(~prim, p, ds, Core.SEval{e1, e}), s, Core.SEval{e2, Core.Tm.subst(e, s)}, Core.KTail{e2, Core.Tms.subst(r, s)}, Core.SEvals{e2, Core.Tm.subst(e, s) <> Core.Tms.subst(r, s)},
                ih(s, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.subst(e, s)}, (e2, s, {==}, h)),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KTail{e1, r}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(e, s)}), Core.KTail{e2, Core.Tms.subst(r, s)}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(e, s)}), Core.KTail{e2, Core.Tms.subst(r, s)}, s, {==}, (e2, s, {==}, h), rr1)),
                M => {==})
    case Core.SArgs{+e1, as}:
      match as:
        case Nil{}:
          match rel:
            case (e2, s, eq, h):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Nil{}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              (1n, Unit{})
        case a <> +r:
          match a:
            case Core.Arg{rl, +e}:
              match rl:
                case Core.Run{}:
                  match rel:
                    case (+e2, +s, eq, +h):
                      %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Core.Arg{Core.Run{}, e} <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                      Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KATail{e1, r}}), S, Core.run(~prim, p, ds, Core.SEval{e1, e}), s, Core.SEval{e2, Core.Tm.subst(e, s)}, Core.KATail{e2, Core.Args.subst(r, s)}, Core.SArgs{e2, Core.Arg{Core.Run{}, Core.Tm.subst(e, s)} <> Core.Args.subst(r, s)},
                        ih(s, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.subst(e, s)}, (e2, s, {==}, h)),
                        +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KATail{e1, r}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(e, s)}), Core.KATail{e2, Core.Args.subst(r, s)}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.Tm.subst(e, s)}), Core.KATail{e2, Core.Args.subst(r, s)}, s, {==}, (e2, s, {==}, h), rr1)),
                        M => {==})
                case Core.Era{}:
                  match rel:
                    case (+e2, +s, eq, +h):
                      %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Core.Arg{Core.Era{}, e} <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                      Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CBox{}}), Core.KATail{e1, r}}), S, Core.run(~prim, p, ds, Core.SEval{e1, Core.CBox{}}), s, Core.SEval{e2, Core.CBox{}}, Core.KATail{e2, Core.Args.subst(r, s)}, Core.SArgs{e2, Core.Arg{Core.Era{}, e} <> Core.Args.subst(r, s)},
                        ih(s, Core.SEval{e1, Core.CBox{}}, Core.SEval{e2, Core.CBox{}}, (e2, s, {==}, h)),
                        +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CBox{}}), Core.KATail{e1, r}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.CBox{}}), Core.KATail{e2, Core.Args.subst(r, s)}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{e2, Core.CBox{}}), Core.KATail{e2, Core.Args.subst(r, s)}, s, {==}, (e2, s, {==}, h), rr1)),
                        M => {==})
    case Core.SThen{r1, +k1}:
      match r1:
        case Core.ROk{+ov1}:
          match rel:
            case (r2, rest0):
              match r2:
                case Core.ROk{+vs2}:
                  match rest0:
                    case (+k2, s, eq, kr, rr):
                      %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, k1}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                      Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SOk{k1, ov1}), S, Core.SOk{k2, vs2}, Core.SThen{Core.ROk{vs2}, k2}, ih(S, Core.SOk{k1, ov1}, Core.SOk{k2, vs2}, (k2, vs2, s, {==}, kr, rr)), M => {==})
                case Core.REnv{env9}:
                  match rest0:
                    case (+k2, s, eq, kr, rr):
                      match rr:
                case Core.RNo{}:
                  match rest0:
                    case (+k2, s, eq, kr, rr):
                      match rr:
                case Core.RFail{msg9}:
                  match rest0:
                    case (+k2, s, eq, kr, rr):
                      match rr:
        case Core.REnv{+env1}:
          match k1:
            case Core.KCall{+f}:
              (0n, Unit{})
            case Core.KApp{}:
              (0n, Unit{})
            case Core.KCtr{+c}:
              (0n, Unit{})
            case Core.KLet{+env, +pt, +b}:
              (0n, Unit{})
            case Core.KBind{+b}:
              match rel:
                case (r2, rest0):
                  match r2:
                    case Core.ROk{vs9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.REnv{+env2}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KBind{b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                          %kr : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KBind{b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SThen{Core.REnv{env2}, _}))>
                          Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SEval{env1, b}), S, Core.SEval{env2, Core.Tm.subst(b, s)}, Core.SThen{Core.REnv{env2}, Core.KBind{Core.Tm.subst(b, s)}}, ih(S, Core.SEval{env1, b}, Core.SEval{env2, Core.Tm.subst(b, s)}, (env2, s, {==}, rr)), M => {==})
                    case Core.RNo{}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.RFail{msg9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
            case Core.KMat{+env, +cs}:
              (0n, Unit{})
            case Core.KCase{+env, +vs, +b, +rest}:
              match rel:
                case (r2, rest0):
                  match r2:
                    case Core.ROk{vs9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.REnv{+env2}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match kr:
                            case (+e3, +vs2, +s3, ek, vr, er):
                              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KCase{env, vs, b, rest}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                              %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KCase{env, vs, b, rest}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SThen{Core.REnv{env2}, _}))>
                              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SEval{env1, b}), S, Core.SEval{env2, Core.Tm.subst(b, s)}, Core.SThen{Core.REnv{env2}, Core.KCase{e3, vs2, Core.Tm.subst(b, s), Core.Tms.subst(rest, s3)}}, ih(S, Core.SEval{env1, b}, Core.SEval{env2, Core.Tm.subst(b, s)}, (env2, s, {==}, rr)), M => {==})
                    case Core.RNo{}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.RFail{msg9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
            case Core.KSuc{+c}:
              (0n, Unit{})
            case Core.KOp{+op}:
              (0n, Unit{})
            case Core.KTail{+env, +es}:
              (0n, Unit{})
            case Core.KATail{+env, +as}:
              (0n, Unit{})
            case Core.KCons{+v}:
              (0n, Unit{})
            case Core.KApply{+rest}:
              (0n, Unit{})
            case Core.KBody{+b, +rest}:
              match rel:
                case (r2, rest0):
                  match r2:
                    case Core.ROk{vs9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.REnv{+env2}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match kr:
                            case (+r3, ek, vr):
                              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KBody{b, rest}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                              %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KBody{b, rest}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SThen{Core.REnv{env2}, _}))>
                              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env1, b}), Core.KApply{rest}}), S, Core.run(~prim, p, ds, Core.SEval{env1, b}), s, Core.SEval{env2, Core.Tm.subst(b, s)}, Core.KApply{r3}, Core.SThen{Core.REnv{env2}, Core.KBody{Core.Tm.subst(b, s), r3}},
                                ih(s, Core.SEval{env1, b}, Core.SEval{env2, Core.Tm.subst(b, s)}, (env2, s, {==}, rr)),
                                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env1, b}), Core.KApply{rest}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{env2, Core.Tm.subst(b, s)}), Core.KApply{r3}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{env2, Core.Tm.subst(b, s)}), Core.KApply{r3}, s, {==}, (r3, {==}, vr), rr1)),
                                M => {==})
                    case Core.RNo{}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.RFail{msg9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
        case Core.RNo{}:
          match k1:
            case Core.KCall{+f}:
              (0n, Unit{})
            case Core.KApp{}:
              (0n, Unit{})
            case Core.KCtr{+c}:
              (0n, Unit{})
            case Core.KLet{+env, +pt, +b}:
              (0n, Unit{})
            case Core.KBind{+b}:
              (0n, Unit{})
            case Core.KMat{+env, +cs}:
              (0n, Unit{})
            case Core.KCase{+env, +vs, +b, +rest}:
              match rel:
                case (r2, rest0):
                  match r2:
                    case Core.ROk{vs9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.REnv{env9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
                    case Core.RNo{}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match kr:
                            case (+e3, +vs2, +s3, ek, vr, er):
                              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.RNo{}, Core.KCase{env, vs, b, rest}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                              %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SThen{Core.RNo{}, Core.KCase{env, vs, b, rest}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SThen{Core.RNo{}, _}))>
                              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SMatch{env, vs, rest}), S, Core.SMatch{e3, vs2, Core.Tms.subst(rest, s3)}, Core.SThen{Core.RNo{}, Core.KCase{e3, vs2, Core.Tm.subst(b, s), Core.Tms.subst(rest, s3)}}, ih(S, Core.SMatch{env, vs, rest}, Core.SMatch{e3, vs2, Core.Tms.subst(rest, s3)}, (e3, vs2, s3, {==}, vr, er)), M => {==})
                    case Core.RFail{msg9}:
                      match rest0:
                        case (k2, +s, eq, kr, rr):
                          match rr:
            case Core.KSuc{+c}:
              (0n, Unit{})
            case Core.KOp{+op}:
              (0n, Unit{})
            case Core.KTail{+env, +es}:
              (0n, Unit{})
            case Core.KATail{+env, +as}:
              (0n, Unit{})
            case Core.KCons{+v}:
              (0n, Unit{})
            case Core.KApply{+rest}:
              (0n, Unit{})
            case Core.KBody{+b, +rest}:
              (0n, Unit{})
        case Core.RFail{+msg}:
          (0n, Unit{})
    case Core.SOk{k1, +vs}:
      match k1:
        case Core.KCall{+f}:
          match rel:
            case (k2, +vs2, s, eq, kr, vr):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %kr : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, vs2}))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SCallDef{f, vs}), S, Core.SCallDef{f, vs2}, Core.SOk{Core.KCall{f}, vs2}, ih(S, Core.SCallDef{f, vs}, Core.SCallDef{f, vs2}, (vs2, {==}, vr)), M => {==})
        case Core.KApp{}:
          match vs:
            case Nil{}:
              (0n, Unit{})
            case +fv <> +r:
              match rel:
                case (k2, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (s, eq, kr, vr):
                          match vr:
                    case +fv2 <> +r2:
                      match rest0:
                        case (s, eq, kr, vr):
                          match vr:
                            case (vv, rr):
                              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApp{}, fv <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                              %kr : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApp{}, fv <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, fv2 <> r2}))>
                              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SApply{r, fv}), S, Core.SApply{r2, fv2}, Core.SOk{Core.KApp{}, fv2 <> r2}, ih(S, Core.SApply{r, fv}, Core.SApply{r2, fv2}, (r2, fv2, {==}, rr, vv)), M => {==})
        case Core.KCtr{+c}:
          match rel:
            case (k2, +vs2, s, eq, kr, vr):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCtr{c}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %kr : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCtr{c}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, vs2}))>
              (1n, (({==}, vr), Unit{}))
        case Core.KLet{+env, +pt, +b}:
          match rel:
            case (k2, +vs2, s, eq, kr, vr):
              match kr:
                case (+e3, +s3, ek, er):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env, pt, b}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env, pt, b}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, vs2}))>
                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{b}}), S, Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.Sb.bind(Core.Dead.names([pt]), s3), Core.SPat{e3, [pt], vs2}, Core.KBind{Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3))}, Core.SOk{Core.KLet{e3, pt, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3))}, vs2},
                    ih(Core.Sb.bind(Core.Dead.names([pt]), s3), Core.SPat{env, [pt], vs}, Core.SPat{e3, [pt], vs2}, (e3, vs2, s3, {==}, vr, er, {==})),
                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{b}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SPat{e3, [pt], vs2}), Core.KBind{Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3))}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SPat{e3, [pt], vs2}), Core.KBind{Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3))}, Core.Sb.bind(Core.Dead.names([pt]), s3), {==}, {==}, rr1)),
                    M => {==})
        case Core.KBind{+b}:
          (0n, Unit{})
        case Core.KMat{+env, +cs}:
          match rel:
            case (k2, +vs2, s, eq, kr, vr):
              match kr:
                case (+e3, +s3, ek, er):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KMat{env, cs}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KMat{env, cs}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, vs2}))>
                  Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SMatch{env, vs, cs}), S, Core.SMatch{e3, vs2, Core.Tms.subst(cs, s3)}, Core.SOk{Core.KMat{e3, Core.Tms.subst(cs, s3)}, vs2}, ih(S, Core.SMatch{env, vs, cs}, Core.SMatch{e3, vs2, Core.Tms.subst(cs, s3)}, (e3, vs2, s3, {==}, vr, er)), M => {==})
        case Core.KCase{+env, +vs, +b, +rest}:
          (0n, Unit{})
        case Core.KSuc{+c}:
          match rel:
            case (k2, +vs2, s, eq, kr, vr):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KSuc{c}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %kr : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KSuc{c}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, vs2}))>
              (1n, Prim(prim, Core.Defs.subst(ds), prim("%suc", Core.VLit{Core.LNum{c}} <> vs), prim("%suc", Core.VLit{Core.LNum{c}} <> vs2), ok("%suc", Core.VLit{Core.LNum{c}} <> vs, Core.VLit{Core.LNum{c}} <> vs2, ({==}, vr)), S))
        case Core.KOp{+op}:
          match rel:
            case (k2, +vs2, s, eq, kr, vr):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KOp{op}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              %kr : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KOp{op}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, vs2}))>
              (1n, Prim(prim, Core.Defs.subst(ds), prim(op, vs), prim(op, vs2), ok(op, vs, vs2, vr), S))
        case Core.KTail{+env, +es}:
          match vs:
            case Nil{}:
              (0n, Unit{})
            case +v <> +r:
              match rel:
                case (k2, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (s, eq, kr, vr):
                          match vr:
                    case +v2 <> +r2:
                      match rest0:
                        case (s, eq, kr, vr):
                          match kr:
                            case (+e3, +s3, ek, er):
                              match vr:
                                case (vv, rr):
                                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KTail{env, es}, v <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                                  %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KTail{env, es}, v <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, v2 <> r2}))>
                                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}), S, Core.run(~prim, p, ds, Core.SEvals{env, es}), s3, Core.SEvals{e3, Core.Tms.subst(es, s3)}, Core.KCons{v2}, Core.SOk{Core.KTail{e3, Core.Tms.subst(es, s3)}, v2 <> r2},
                                    ih(s3, Core.SEvals{env, es}, Core.SEvals{e3, Core.Tms.subst(es, s3)}, (e3, s3, {==}, er)),
                                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e3, Core.Tms.subst(es, s3)}), Core.KCons{v2}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEvals{e3, Core.Tms.subst(es, s3)}), Core.KCons{v2}, s3, {==}, (v2, {==}, vv), rr1)),
                                    M => {==})
        case Core.KATail{+env, +as}:
          match vs:
            case Nil{}:
              (0n, Unit{})
            case +v <> +r:
              match rel:
                case (k2, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (s, eq, kr, vr):
                          match vr:
                    case +v2 <> +r2:
                      match rest0:
                        case (s, eq, kr, vr):
                          match kr:
                            case (+e3, +s3, ek, er):
                              match vr:
                                case (vv, rr):
                                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KATail{env, as}, v <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                                  %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KATail{env, as}, v <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, v2 <> r2}))>
                                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}}), S, Core.run(~prim, p, ds, Core.SArgs{env, as}), s3, Core.SArgs{e3, Core.Args.subst(as, s3)}, Core.KCons{v2}, Core.SOk{Core.KATail{e3, Core.Args.subst(as, s3)}, v2 <> r2},
                                    ih(s3, Core.SArgs{env, as}, Core.SArgs{e3, Core.Args.subst(as, s3)}, (e3, s3, {==}, er)),
                                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SArgs{e3, Core.Args.subst(as, s3)}), Core.KCons{v2}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SArgs{e3, Core.Args.subst(as, s3)}), Core.KCons{v2}, s3, {==}, (v2, {==}, vv), rr1)),
                                    M => {==})
        case Core.KCons{+v}:
          match rel:
            case (k2, +vs2, s, eq, kr, vr):
              match kr:
                case (+v2, ek, vv):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCons{v}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCons{v}, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, vs2}))>
                  (1n, (vv, vr))
        case Core.KApply{+rest}:
          match vs:
            case Nil{}:
              (0n, Unit{})
            case +v <> +r:
              match rel:
                case (k2, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (s, eq, kr, vr):
                          match vr:
                    case +v2 <> +r2:
                      match rest0:
                        case (s, eq, kr, vr):
                          match kr:
                            case (+rest2, ek, restr):
                              match vr:
                                case (vv, rr):
                                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApply{rest}, v <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                                  %ek : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApply{rest}, v <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SOk{_, v2 <> r2}))>
                                  Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SApply{rest, v}), S, Core.SApply{rest2, v2}, Core.SOk{Core.KApply{rest2}, v2 <> r2}, ih(S, Core.SApply{rest, v}, Core.SApply{rest2, v2}, (rest2, v2, {==}, restr, vv)), M => {==})
        case Core.KBody{+b, +rest}:
          (0n, Unit{})
    case Core.SLook{e1, x}:
      match rel:
    case Core.SLook2{h, v, e1, x}:
      match rel:
    case Core.SCallDef{+f, +vs}:
      match rel:
        case (+vs2, eq, vr):
          %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SCallDef{f, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
          Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SFind{ds, f, vs}), S, Core.SFind{Core.Defs.subst(ds), f, vs2}, Core.SCallDef{f, vs2}, ih(S, Core.SFind{ds, f, vs}, Core.SFind{Core.Defs.subst(ds), f, vs2}, (vs2, {==}, vr)), M => {==})
    case Core.SFind{ds2, +f, +vs}:
      match ds2:
        case Nil{}:
          match rel:
            case (+vs2, eq, vr):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SFind{Nil{}, f, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              (1n, Prim(prim, Core.Defs.subst(ds), prim(f, vs), prim(f, vs2), ok(f, vs, vs2, vr), S))
        case d <> +r:
          match d:
            case Core.Def{+name, +ps, +b, +ret}:
              match rel:
                case (+vs2, eq, vr):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SFind{Core.Def{name, ps, b, ret} <> r, f, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SFound{String.eq(name, f), ps, b, r, f, vs}), S, Core.SFound{String.eq(name, f), ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), Core.Defs.subst(r), f, vs2}, Core.SFind{Core.Defs.subst(Core.Def{name, ps, b, ret} <> r), f, vs2}, ih(S, Core.SFound{String.eq(name, f), ps, b, r, f, vs}, Core.SFound{String.eq(name, f), ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), Core.Defs.subst(r), f, vs2}, (vs2, {==}, vr)), M => {==})
    case Core.SFound{h, +ps, +b, +ds2, +f, +vs}:
      match h:
        case True{}:
          match rel:
            case (+vs2, eq, +vr):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, b, ds2, f, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, b, vs}), S, Core.SEnter{Nat.is_lt(Core.Vals.len(vs2), Core.Pars.len(ps)), f, ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), vs2}, Core.SFound{True{}, ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), Core.Defs.subst(ds2), f, vs2}, ih(S, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, b, vs}, Core.SEnter{Nat.is_lt(Core.Vals.len(vs2), Core.Pars.len(ps)), f, ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), vs2}, (vs2, Enter.eq(ps, vs, vs2, f, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), Len.eq(prim, Core.Defs.subst(ds), vs, vs2, vr)), vr, {==})), M => {==})
        case False{}:
          match rel:
            case (+vs2, eq, vr):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SFound{False{}, ps, b, ds2, f, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SFind{ds2, f, vs}), S, Core.SFind{Core.Defs.subst(ds2), f, vs2}, Core.SFound{False{}, ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), Core.Defs.subst(ds2), f, vs2}, ih(S, Core.SFind{ds2, f, vs}, Core.SFind{Core.Defs.subst(ds2), f, vs2}, (vs2, {==}, vr)), M => {==})
    case Core.SEnter{sh, +f, +ps, +b, +vs}:
      match sh:
        case True{}:
          match rel:
            case (+vs2, eq, vr, esh):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEnter{True{}, f, ps, b, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              (1n, (({==}, vr), Unit{}))
        case False{}:
          match rel:
            case (+vs2, eq, +vr, esh):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, b, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), b}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}), S, Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), b}), Core.Sb.pars(ps, Nil{}), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.subst(b, Core.Sb.pars(ps, Nil{}))}, Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs2)}, Core.SEnter{False{}, f, ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), vs2},
                ih(Core.Sb.pars(ps, Nil{}), Core.SEval{Core.Scope.bind(ps, vs), b}, Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.subst(b, Core.Sb.pars(ps, Nil{}))}, (Core.Scope.bind(ps, vs2), Core.Sb.pars(ps, Nil{}), {==}, Bind.push(~prim, Core.Defs.subst(ds), ps, vs, vs2, vr, Nil{}, Nil{}, Nil{}, Unit{}, esh))),
                +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), b}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.subst(b, Core.Sb.pars(ps, Nil{}))}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs2)}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.subst(b, Core.Sb.pars(ps, Nil{}))}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs2)}, Core.Sb.pars(ps, Nil{}), {==}, (Core.Vals.drop(Core.Pars.len(ps), vs2), {==}, Drop(prim, Core.Defs.subst(ds), Core.Pars.len(ps), vs, vs2, vr)), rr1)),
                M => {==})
    case Core.SApply{vs, fv}:
      match vs:
        case Nil{}:
          match rel:
            case (vs2, rest0):
              match vs2:
                case Nil{}:
                  match rest0:
                    case (+fv2, eq, vr, fr):
                      %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SApply{Nil{}, fv}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                      (1n, (fr, Unit{}))
                case w9 <> t9:
                  match rest0:
                    case (fv2, eq, vr, fr):
                      match vr:
        case +v <> +r:
          match fv:
            case Core.VLit{l9}:
              (0n, Unit{})
            case Core.VCtr{k9, fs9}:
              (0n, Unit{})
            case Core.VClo{+env, +pt, +b}:
              match rel:
                case (vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (fv2, eq, vr, fr):
                          match vr:
                    case +v2 <> +r2:
                      match rest0:
                        case (fv2, rest1):
                          match fv2:
                            case Core.VClo{+env2, pt2, b2}:
                              match rest1:
                                case (eq, vr, fr):
                                  match vr:
                                    case (vv, rr):
                                      match fr:
                                        case (ep, +s3, eb, er):
                                          %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{env, pt, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                                          %ep : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{env, pt, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SApply{v2 <> r2, Core.VClo{env2, _, b2}}))>
                                          %eb : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{env, pt, b}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SApply{v2 <> r2, Core.VClo{env2, pt, _}}))>
                                          Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{b, r}}), S, Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.Sb.bind(Core.Dead.names([pt]), s3), Core.SPat{env2, [pt], [v2]}, Core.KBody{Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3)), r2}, Core.SApply{v2 <> r2, Core.VClo{env2, pt, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3))}},
                                            ih(Core.Sb.bind(Core.Dead.names([pt]), s3), Core.SPat{env, [pt], [v]}, Core.SPat{env2, [pt], [v2]}, (env2, [v2], s3, {==}, (vv, Unit{}), er, {==})),
                                            +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{b, r}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SPat{env2, [pt], [v2]}), Core.KBody{Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3)), r2}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SPat{env2, [pt], [v2]}), Core.KBody{Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([pt]), s3)), r2}, Core.Sb.bind(Core.Dead.names([pt]), s3), {==}, (r2, {==}, rr), rr1)),
                                            M => {==})
                            case Core.VLit{l9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VCtr{k9, fs9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VFun{f9, as9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VTrm{t9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VBnd{x9, w9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
            case Core.VFun{+f, +as}:
              match rel:
                case (vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (fv2, eq, vr, fr):
                          match vr:
                    case +v2 <> +r2:
                      match rest0:
                        case (fv2, rest1):
                          match fv2:
                            case Core.VFun{f2, +as2}:
                              match rest1:
                                case (eq, vr, fr):
                                  match vr:
                                    case (vv, rr):
                                      match fr:
                                        case (ef, ar):
                                          %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                                          %ef : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}}), S, Core.run(~prim, m, Core.Defs.subst(ds), Core.SApply{v2 <> r2, Core.VFun{_, as2}}))>
                                          Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SCallDef{f, Core.Vals.cat(as, v <> r)}), S, Core.SCallDef{f, Core.Vals.cat(as2, v2 <> r2)}, Core.SApply{v2 <> r2, Core.VFun{f, as2}}, ih(S, Core.SCallDef{f, Core.Vals.cat(as, v <> r)}, Core.SCallDef{f, Core.Vals.cat(as2, v2 <> r2)}, (Core.Vals.cat(as2, v2 <> r2), {==}, Cat(prim, Core.Defs.subst(ds), as, as2, v <> r, v2 <> r2, ar, (vv, rr)))), M => {==})
                            case Core.VLit{l9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VCtr{k9, fs9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VClo{env9, p9, b9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VTrm{t9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
                            case Core.VBnd{x9, w9}:
                              match rest1:
                                case (eq, vr, fr):
                                  match fr:
            case Core.VTrm{t9}:
              (0n, Unit{})
            case Core.VBnd{x9, w9}:
              (0n, Unit{})
    case Core.SMatch{+env, +vs, cs}:
      match cs:
        case Nil{}:
          (0n, Unit{})
        case c <> +r:
          match c:
            case Core.CVar{x9}:
              (0n, Unit{})
            case Core.CLit{l9}:
              (0n, Unit{})
            case Core.CRef{f9}:
              (0n, Unit{})
            case Core.CCall{f9, as9}:
              (0n, Unit{})
            case Core.CApp{f9, as9}:
              (0n, Unit{})
            case Core.CCtr{k9, as9}:
              (0n, Unit{})
            case Core.CLam{p09, b9}:
              (0n, Unit{})
            case Core.CLet{p09, v9, b9}:
              (0n, Unit{})
            case Core.CMat{scrs9, cases9}:
              (0n, Unit{})
            case Core.CCse{+ps, +b}:
              match rel:
                case (+e3, +vs2, +s3, eq, +vr, +er):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CCse{ps, b} <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Then.go(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, b, r}}), S, Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.Sb.bind(Core.Dead.names(ps), s3), Core.SPat{e3, ps, vs2}, Core.KCase{e3, vs2, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names(ps), s3)), Core.Tms.subst(r, s3)}, Core.SMatch{e3, vs2, Core.Tms.subst(Core.CCse{ps, b} <> r, s3)},
                    ih(Core.Sb.bind(Core.Dead.names(ps), s3), Core.SPat{env, ps, vs}, Core.SPat{e3, ps, vs2}, (e3, vs2, s3, {==}, vr, er, {==})),
                    +m1 => rr1 => ih2(S, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, b, r}}, Core.SThen{Core.run(~prim, m1, Core.Defs.subst(ds), Core.SPat{e3, ps, vs2}), Core.KCase{e3, vs2, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names(ps), s3)), Core.Tms.subst(r, s3)}}, (Core.run(~prim, m1, Core.Defs.subst(ds), Core.SPat{e3, ps, vs2}), Core.KCase{e3, vs2, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names(ps), s3)), Core.Tms.subst(r, s3)}, Core.Sb.bind(Core.Dead.names(ps), s3), {==}, (e3, vs2, s3, {==}, vr, er), rr1)),
                    M => {==})
            case Core.CSuc{k9, e9}:
              (0n, Unit{})
            case Core.COp{op9, a9, b9}:
              (0n, Unit{})
            case Core.CAnn{e9, ty9}:
              (0n, Unit{})
            case Core.CTyp{name9, args9}:
              (0n, Unit{})
            case Core.CBox{}:
              (0n, Unit{})
            case Core.CErr{msg9}:
              (0n, Unit{})
    case Core.SPat{+env, ps, vs}:
      match ps:
        case Nil{}:
          match vs:
            case Nil{}:
              match rel:
                case (+e3, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (s3, eq, vr, er, eS):
                          %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SPat{env, Nil{}, Nil{}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                          %eS : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SPat{env, Nil{}, Nil{}}), _, Core.run(~prim, m, Core.Defs.subst(ds), Core.SPat{e3, Nil{}, Nil{}}))>
                          (1n, er)
                    case w9 <> t9:
                      match rest0:
                        case (s3, eq, vr, rest1):
                          match vr:
            case v <> r:
              match rel:
                case (e3, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (s3, eq, vr, rest1):
                          match vr:
                    case w9 <> t9:
                      match rest0:
                        case (s3, eq, vr, er, eS):
                          %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SPat{env, Nil{}, v <> r}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                          (1n, Unit{})
        case +pt <> +pr:
          match vs:
            case Nil{}:
              match rel:
                case (e3, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (s3, eq, vr, er, eS):
                          %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SPat{env, pt <> pr, Nil{}}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                          (1n, Unit{})
                    case w9 <> t9:
                      match rest0:
                        case (s3, eq, vr, rest1):
                          match vr:
            case +v <> +vr0:
              match rel:
                case (+e3, vs2, rest0):
                  match vs2:
                    case Nil{}:
                      match rest0:
                        case (+s3, eq, vr, rest1):
                          match vr:
                    case +v2 <> +r2:
                      match rest0:
                        case (+s3, eq, vr, rest1):
                          match vr:
                            case (vv, rr):
                              match rest1:
                                case (er, eS):
                                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SPat{env, pt <> pr, v <> vr0}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                                  Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.Pat.step(env, pt, v, pr, vr0)), S, Core.Pat.step(e3, pt, v2, pr, r2), Core.SPat{e3, pt <> pr, v2 <> r2}, ih(S, Core.Pat.step(env, pt, v, pr, vr0), Core.Pat.step(e3, pt, v2, pr, r2), Pat.rel(~prim, Core.Defs.subst(ds), env, pt, v, pr, vr0, e3, v2, r2, S, s3, vv, rr, er, eS)), M => {==})
    case Core.SPatC{h, +env, +ps, +vs}:
      match h:
        case True{}:
          match rel:
            case (+e3, +vs2, eq, pc):
              match pc:
                case (s3, vr, er, eS):
                  %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SPatC{True{}, env, ps, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
                  Up.one(~prim, Core.Defs.subst(ds), Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), S, Core.SPat{e3, ps, vs2}, Core.SPatC{True{}, e3, ps, vs2}, ih(S, Core.SPat{env, ps, vs}, Core.SPat{e3, ps, vs2}, (e3, vs2, s3, {==}, vr, er, eS)), M => {==})
        case False{}:
          match rel:
            case (e3, vs2, eq, pc):
              %eq : Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, 1n+p, ds, Core.SPatC{False{}, env, ps, vs}), S, Core.run(~prim, m, Core.Defs.subst(ds), _))>
              (1n, Unit{})

# From related states, related results (subst_ok): induction on the
# source's fuel.
def L.sub(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ds: List<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(prim, Core.Defs.subst(ds), vs1, vs2) -> Law.PRel(prim, Core.Defs.subst(ds), prim(op, vs1), prim(op, vs2)), +n: Nat, +S: List<&2, Core.Sb>, s1: Core.Sel, s2: Core.Sel, rel: Law.SRel(prim, Core.Defs.subst(ds), s1, S, s2))
    -> Sigma<&2, &2, Nat, m => Law.RRel(prim, Core.Defs.subst(ds), Core.run(~prim, n, ds, s1), S, Core.run(~prim, m, Core.Defs.subst(ds), s2))>:
  match n:
    case 0n:
      (0n, Unit{})
    case 1n+p:
      Step(~prim, ~ds, ~ok, p, S, s1, s2, rel,
        S2 => t1 => t2 => r => L.sub(~prim, ~ds, ~ok, p, S2, t1, t2, r),
        S2 => t1 => t2 => r => L.sub(~prim, ~ds, ~ok, p, S2, t1, t2, r),
        S2 => t1 => t2 => r => L.sub(~prim, ~ds, ~ok, p, S2, t1, t2, r),
        S2 => t1 => t2 => r => L.sub(~prim, ~ds, ~ok, p, S2, t1, t2, r),
        S2 => t1 => t2 => r => L.sub(~prim, ~ds, ~ok, p, S2, t1, t2, r))

# Equality
# ========

def Eq.val(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, v1: Core.Val, v2: Core.Val, vr: Law.VRel(prim, dz, v1, v2), c: Dead.NoClo(v1)) -> {v1 == v2 : Core.Val}:
  match v1:
    case Core.VLit{l}:
      match v2:
        case Core.VLit{l2}:
          %vr : {Core.VLit{l} == Core.VLit{_} : Core.Val}
          {==}
        case Core.VCtr{k8, fs8}:
          match vr:
        case Core.VClo{env8, p8, b8}:
          match vr:
        case Core.VFun{f8, as8}:
          match vr:
        case Core.VTrm{t8}:
          match vr:
        case Core.VBnd{x8, w8}:
          match vr:
    case Core.VCtr{+k, fs}:
      match fs:
        case Nil{}:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{k2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      %ek : {Core.VCtr{k, Nil{}} == Core.VCtr{_, Nil{}} : Core.Val}
                      {==}
                case w <> s:
                  match vr:
                    case (ek, vrs):
                      match vrs:
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{f8, as8}:
              match vr:
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
        case +f <> +r:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{+k2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                case +f2 <> +r2:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                        case (vf, vrr):
                          match c:
                            case (cf, cr):
                              %DP.Val.sym(Core.VCtr{k, r}, Core.VCtr{k2, r2}, Eq.val(prim, dz, Core.VCtr{k, r}, Core.VCtr{k2, r2}, (ek, vrr), cr)) : {Core.Val.push(f, _) == Core.VCtr{k2, f2 <> r2} : Core.Val}
                              %DP.Val.sym(f, f2, Eq.val(prim, dz, f, f2, vf, cf)) : {Core.VCtr{k2, _ <> r2} == Core.VCtr{k2, f2 <> r2} : Core.Val}
                              {==}
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{f8, as8}:
              match vr:
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
    case Core.VClo{ce, cp, cb}:
      match c:
    case Core.VFun{+g, fs}:
      match fs:
        case Nil{}:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{k8, fs8}:
              match vr:
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{g2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      %ek : {Core.VFun{g, Nil{}} == Core.VFun{_, Nil{}} : Core.Val}
                      {==}
                case w <> s:
                  match vr:
                    case (ek, vrs):
                      match vrs:
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
        case +f <> +r:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{k8, fs8}:
              match vr:
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{+g2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                case +f2 <> +r2:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                        case (vf, vrr):
                          match c:
                            case (cf, cr):
                              %DP.Val.sym(Core.VFun{g, r}, Core.VFun{g2, r2}, Eq.val(prim, dz, Core.VFun{g, r}, Core.VFun{g2, r2}, (ek, vrr), cr)) : {Core.Val.push(f, _) == Core.VFun{g2, f2 <> r2} : Core.Val}
                              %DP.Val.sym(f, f2, Eq.val(prim, dz, f, f2, vf, cf)) : {Core.VFun{g2, _ <> r2} == Core.VFun{g2, f2 <> r2} : Core.Val}
                              {==}
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
    case Core.VTrm{t}:
      match v2:
        case Core.VLit{l8}:
          match vr:
        case Core.VCtr{k8, fs8}:
          match vr:
        case Core.VClo{env8, p8, b8}:
          match vr:
        case Core.VFun{f8, as8}:
          match vr:
        case Core.VTrm{t2}:
          %vr : {Core.VTrm{t} == Core.VTrm{_} : Core.Val}
          {==}
        case Core.VBnd{x8, w8}:
          match vr:
    case Core.VBnd{+x, +w}:
      match v2:
        case Core.VLit{l8}:
          match vr:
        case Core.VCtr{k8, fs8}:
          match vr:
        case Core.VClo{env8, p8, b8}:
          match vr:
        case Core.VFun{f8, as8}:
          match vr:
        case Core.VTrm{t8}:
          match vr:
        case Core.VBnd{x2, +w2}:
          match vr:
            case (ex, vw):
              %ex : {Core.VBnd{x, w} == Core.VBnd{_, w2} : Core.Val}
              %DP.Val.sym(w, w2, Eq.val(prim, dz, w, w2, vw, c)) : {Core.VBnd{x, _} == Core.VBnd{x, w2} : Core.Val}
              {==}

def Eq.vals(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, vs1: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(prim, dz, vs1, vs2), c: Dead.NoClos(vs1))
    -> {vs1 == vs2 : List<&2, Core.Val>}:
  match vs1:
    case Nil{}:
      match vs2:
        case Nil{}:
          {==}
        case w <> s:
          match vr:
    case +v <> +r:
      match vs2:
        case Nil{}:
          match vr:
        case +w <> +s:
          match vr:
            case (vv, vrr):
              match c:
                case (cv, cr):
                  %Eq.val(prim, dz, v, w, vv, cv) : {v <> r == _ <> s : List<&2, Core.Val>}
                  %Eq.vals(prim, dz, r, s, vrr, cr) : {v <> r == v <> _ : List<&2, Core.Val>}
                  {==}

# Related results, the first clean: the second is the first with the pass
# taken.
def Eq.res(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, r1: Core.Res, r2: Core.Res, -S: List<&2, Core.Sb>, rr: Law.RRel(prim, dz, r1, S, r2), c: Dead.Clean(r1))
    -> {r1 == r2 : Core.Res}:
  match r1:
    case Core.ROk{+vs1}:
      match r2:
        case Core.ROk{+vs2}:
          %Eq.vals(prim, dz, vs1, vs2, rr, c) : {Core.ROk{vs1} == Core.ROk{_} : Core.Res}
          {==}
        case Core.REnv{e9}:
          match rr:
        case Core.RNo{}:
          match rr:
        case Core.RFail{m9}:
          match rr:
    case Core.REnv{e1}:
      match c:
    case Core.RNo{}:
      match r2:
        case Core.ROk{vs9}:
          match rr:
        case Core.REnv{e9}:
          match rr:
        case Core.RNo{}:
          {==}
        case Core.RFail{m9}:
          match rr:
    case Core.RFail{m}:
      match c:

# The laws
# ========

def Top.sub(~prim: String -> List<&2, Core.Val> -> Core.Res, +dz: List<&2, Core.Def>, r1: Core.Res, +t: Core.Sel,
    h: Sigma<&2, &2, Nat, m => Law.RRel(prim, dz, r1, Nil{}, Core.run(~prim, m, dz, t))>, c: Dead.Clean(r1))
    -> Sigma<&2, &2, Nat, m => {r1 == Core.run(~prim, m, dz, t) : Core.Res}>:
  match h:
    case (+m, rr):
      (m, Eq.res(prim, dz, r1, Core.run(~prim, m, dz, t), Nil{}, rr, c))

def Law.subst_ok(prim, ds, ok, n, S, s1, s2, rel):
  L.sub(~prim, ~ds, ~ok, n, S, s1, s2, rel)

def P.sub(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ds: List<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(prim, Core.Defs.subst(ds), vs1, vs2) -> Law.PRel(prim, Core.Defs.subst(ds), prim(op, vs1), prim(op, vs2)), +n: Nat, nf: Dead.Clean(Core.Prog.run(~prim, n, ds)))
    -> Sigma<&2, &2, Nat, m => {Core.Prog.run(~prim, n, ds) == Core.Prog.run(~prim, m, Core.Defs.subst(ds)) : Core.Res}>:
  Top.sub(~prim, Core.Defs.subst(ds), Core.Prog.run(~prim, n, ds), Core.SCallDef{"main", Nil{}},
    L.sub(~prim, ~ds, ~ok, n, Nil{}, Core.SCallDef{"main", Nil{}}, Core.SCallDef{"main", Nil{}}, (Nil{}, {==}, Unit{})), nf)

def Law.subst_prog(prim, ds, ok, n, nf):
  P.sub(~prim, ~ds, ~ok, n, nf)
