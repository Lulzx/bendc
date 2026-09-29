import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./REDPROOF.bend as RP
import ./DEAD.bend as Dead
import ./INLINE.bend as Law

# Proof of INLINE.bend's laws. L.inl (inline_ok): induction on the source's
# fuel, one case per step of `run` (Step); each step's lemma takes the
# induction hypothesis for the fuel one less, at any fuel of the other
# program as much or more. At an inlined call (the Call lemmas) the source
# looks for the def while the other program, having bound the parameters,
# waits at the body; its match took L+1 steps where the call's binding
# takes one, and the arguments' run (Fuel) shows it had them to spare.

# Booleans and numbers
# ====================

def Contra(-T: Data, c: Bool, a: Dead.Fls(c), t: Dead.Tru(c)) -> T:
  match c:
    case True{}:
      match a:
    case False{}:
      match t:

def And.l(a: Bool, b: Bool, h: Dead.Tru(Bool.and(a, b))) -> Dead.Tru(a):
  match a:
    case True{}:
      Unit{}
    case False{}:
      match h:

def And.r(a: Bool, b: Bool, h: Dead.Tru(Bool.and(a, b))) -> Dead.Tru(b):
  match a:
    case True{}:
      h
    case False{}:
      match h:

# Nat.is_eq a b: a is b.
def Nat.eq.of(a: Nat, b: Nat, h: Dead.Tru(Nat.is_eq(a, b))) -> {a == b : Nat}:
  match a b:
    case 0n 0n:
      {==}
    case 0n 1n+y:
      match h:
    case 1n+x 0n:
      match h:
    case 1n+x 1n+y:
      %Nat.eq.of(x, y, h) : {1n+x == 1n+_ : Nat}
      {==}

def Nat.lt.self(a: Nat) -> Dead.Fls(Nat.is_lt(a, a)):
  match a:
    case 0n:
      Unit{}
    case 1n+x:
      Nat.lt.self(x)

def Le.down(+a: Nat, +b: Nat, +h: Red.Le(1n+a, b)) -> Red.Le(a, b):
  match b:
    case 0n:
      match h:
    case 1n+c:
      RP.Le.succ(a, c, h)

def Le.trans(a: Nat, +b: Nat, +c: Nat, h1: Red.Le(a, b), h2: Red.Le(b, c)) -> Red.Le(a, c):
  match a:
    case 0n:
      Unit{}
    case 1n+x:
      match b:
        case 0n:
          match h1:
        case 1n+y:
          match c:
            case 0n:
              match h2:
            case 1n+z:
              Le.trans(x, y, z, h1, h2)

# a <= b or b <= a.
def Le.total(a: Nat, +b: Nat) -> Either<&2, &2, Red.Le(a, b), Red.Le(b, a)>:
  match a:
    case 0n:
      Inl{Unit{}}
    case 1n+x:
      match b:
        case 0n:
          Inr{Unit{}}
        case 1n+y:
          Le.total(x, y)

# Lists
# =====

def Len.eq(-ins: Map<&2, Core.Def>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(ins, vs, vs2))
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
              %Len.eq(ins, r, s, b) : {1n+Core.Vals.len(r) == 1n+_ : Nat}
              {==}

# Related lists of the same length.
def Len.rel(-ins: Map<&2, Core.Def>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, +n: Nat, vr: Law.VRels(ins, vs, vs2), h: Red.Len(vs2, n))
    -> Red.Len(vs, n):
  match vs:
    case Nil{}:
      match vs2:
        case Nil{}:
          h
        case w <> s:
          match vr:
    case v <> r:
      match vs2:
        case Nil{}:
          match vr:
        case w <> s:
          match n:
            case 0n:
              match h:
            case 1n+c:
              match vr:
                case (a, b):
                  Len.rel(ins, r, s, c, b, h)

def Drop.all(vs: List<&2, Core.Val>, +n: Nat, h: Red.Len(vs, n)) -> {Nil{} == Core.Vals.drop(n, vs) : List<&2, Core.Val>}:
  match vs:
    case Nil{}:
      match n:
        case 0n:
          {==}
        case 1n+c:
          match h:
    case v <> r:
      match n:
        case 0n:
          match h:
        case 1n+c:
          Drop.all(r, c, h)

def Drop(-ins: Map<&2, Core.Def>, n: Nat, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(ins, vs, vs2))
    -> Law.VRels(ins, Core.Vals.drop(n, vs), Core.Vals.drop(n, vs2)):
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
                  Drop(ins, m, r, s, b)

def Cat(-ins: Map<&2, Core.Def>, as: List<&2, Core.Val>, as2: List<&2, Core.Val>, +bs: List<&2, Core.Val>, +bs2: List<&2, Core.Val>,
    ra: Law.VRels(ins, as, as2), rb: Law.VRels(ins, bs, bs2)) -> Law.VRels(ins, Core.Vals.cat(as, bs), Core.Vals.cat(as2, bs2)):
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
              (a, Cat(ins, r, s, bs, bs2, b, rb))

# A def's parameters bound to related values in front of related scopes.
def Bind.push(-ins: Map<&2, Core.Def>, ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(ins, vs, vs2),
    acc: List<&2, Core.Val>, acc2: List<&2, Core.Val>, ha: Law.ERel(ins, acc, acc2))
    -> Law.ERel(ins, Core.Scope.push(ps, vs, acc), Core.Scope.push(ps, vs2, acc2)):
  match ps:
    case Nil{}:
      ha
    case q <> pr:
      match q:
        case Core.Par{+x, rel, mode, ty}:
          match vs:
            case Nil{}:
              match vs2:
                case Nil{}:
                  ha
                case w <> s:
                  match vr:
            case v <> r:
              match vs2:
                case Nil{}:
                  match vr:
                case w <> s:
                  match vr:
                    case (a, b):
                      Bind.push(ins, pr, r, s, b, Core.VBnd{x, v} <> acc, Core.VBnd{x, w} <> acc2, (({==}, a), ha))

# Natives
# =======

def Prim(-ins: Map<&2, Core.Def>, r1: Core.Res, r2: Core.Res, h: Law.PRel(ins, r1, r2)) -> Law.RRel(ins, r1, r2):
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

# Shapes
# ======

# A term with the pass taken, a node at a time (at depth 0 it is the term).

def Tms.zero(ts: List<&2, Core.Tm>, +ins: Map<&2, Core.Def>) -> {ts == Core.Tms.inline(ins, 0n, ts) : List<&2, Core.Tm>}:
  match ts:
    case Nil{}:
      {==}
    case t <> r:
      %Tms.zero(r, ins) : {t <> r == t <> _ : List<&2, Core.Tm>}
      {==}

def Args.zero(as: List<&2, Core.Arg>, +ins: Map<&2, Core.Def>) -> {as == Core.Args.inline(ins, 0n, as) : List<&2, Core.Arg>}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          %Args.zero(r, ins) : {Core.Arg{rel, e} <> r == Core.Arg{rel, e} <> _ : List<&2, Core.Arg>}
          {==}

def Sh.var(+ins: Map<&2, Core.Def>, k: Nat, x: String) -> {Core.CVar{x} == Core.Tm.inline(ins, k, Core.CVar{x}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.lit(+ins: Map<&2, Core.Def>, k: Nat, l: Core.Lit) -> {Core.CLit{l} == Core.Tm.inline(ins, k, Core.CLit{l}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.ref(+ins: Map<&2, Core.Def>, k: Nat, f: String) -> {Core.CRef{f} == Core.Tm.inline(ins, k, Core.CRef{f}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.typ(+ins: Map<&2, Core.Def>, k: Nat, n: String, as: List<&2, Core.Tm>)
    -> {Core.CTyp{n, as} == Core.Tm.inline(ins, k, Core.CTyp{n, as}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.box(+ins: Map<&2, Core.Def>, k: Nat) -> {Core.CBox{} == Core.Tm.inline(ins, k, Core.CBox{}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.err(+ins: Map<&2, Core.Def>, k: Nat, m: String) -> {Core.CErr{m} == Core.Tm.inline(ins, k, Core.CErr{m}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.lam(+ins: Map<&2, Core.Def>, k: Nat, p: Core.Pt, b: Core.Tm)
    -> {Core.CLam{p, Core.Tm.inline(ins, k, b, True{})} == Core.Tm.inline(ins, k, Core.CLam{p, b}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.let(+ins: Map<&2, Core.Def>, k: Nat, p: Core.Pt, v: Core.Tm, b: Core.Tm)
    -> {Core.CLet{p, Core.Tm.inline(ins, k, v, True{}), Core.Tm.inline(ins, k, b, True{})} == Core.Tm.inline(ins, k, Core.CLet{p, v, b}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.cse(+ins: Map<&2, Core.Def>, k: Nat, ps: List<&2, Core.Pt>, b: Core.Tm)
    -> {Core.CCse{ps, Core.Tm.inline(ins, k, b, True{})} == Core.Tm.inline(ins, k, Core.CCse{ps, b}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.suc(+ins: Map<&2, Core.Def>, k: Nat, n: U32, e: Core.Tm)
    -> {Core.CSuc{n, Core.Tm.inline(ins, k, e, True{})} == Core.Tm.inline(ins, k, Core.CSuc{n, e}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.op(+ins: Map<&2, Core.Def>, k: Nat, op: String, a: Core.Tm, b: Core.Tm)
    -> {Core.COp{op, Core.Tm.inline(ins, k, a, True{}), Core.Tm.inline(ins, k, b, True{})} == Core.Tm.inline(ins, k, Core.COp{op, a, b}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.ann(+ins: Map<&2, Core.Def>, k: Nat, e: Core.Tm, ty: String)
    -> {Core.CAnn{Core.Tm.inline(ins, k, e, True{}), ty} == Core.Tm.inline(ins, k, Core.CAnn{e, ty}, True{}) : Core.Tm}:
  match k:
    case 0n:
      {==}
    case 1n+j:
      {==}

def Sh.app.s(as: List<&2, Core.Tm>, +ins: Map<&2, Core.Def>, +j: Nat, +f: Core.Tm, top: Bool)
    -> {Core.CApp{Core.Tm.inline(ins, 1n+j, f, True{}), Core.Tms.inline(ins, 1n+j, as)} == Core.Tm.inline(ins, 1n+j, Core.CApp{f, as}, top) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %Sh.app.s(r, ins, j, f, False{}) : {Core.CApp{Core.Tm.inline(ins, 1n+j, f, True{}), Core.Tm.inline(ins, 1n+j, a, True{}) <> Core.Tms.inline(ins, 1n+j, r)} == Core.Tm.push(Core.Tm.inline(ins, 1n+j, a, True{}), _) : Core.Tm}
      {==}

def Sh.app(+ins: Map<&2, Core.Def>, k: Nat, f: Core.Tm, as: List<&2, Core.Tm>)
    -> {Core.CApp{Core.Tm.inline(ins, k, f, True{}), Core.Tms.inline(ins, k, as)} == Core.Tm.inline(ins, k, Core.CApp{f, as}, True{}) : Core.Tm}:
  match k:
    case 0n:
      %Tms.zero(as, ins) : {Core.CApp{f, _} == Core.CApp{f, as} : Core.Tm}
      {==}
    case 1n+j:
      Sh.app.s(as, ins, j, f, True{})

def Sh.ctr.s(as: List<&2, Core.Tm>, +ins: Map<&2, Core.Def>, +j: Nat, +c: String, top: Bool)
    -> {Core.CCtr{c, Core.Tms.inline(ins, 1n+j, as)} == Core.Tm.inline(ins, 1n+j, Core.CCtr{c, as}, top) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %Sh.ctr.s(r, ins, j, c, False{}) : {Core.CCtr{c, Core.Tm.inline(ins, 1n+j, a, True{}) <> Core.Tms.inline(ins, 1n+j, r)} == Core.Tm.push(Core.Tm.inline(ins, 1n+j, a, True{}), _) : Core.Tm}
      {==}

def Sh.ctr(+ins: Map<&2, Core.Def>, k: Nat, c: String, as: List<&2, Core.Tm>)
    -> {Core.CCtr{c, Core.Tms.inline(ins, k, as)} == Core.Tm.inline(ins, k, Core.CCtr{c, as}, True{}) : Core.Tm}:
  match k:
    case 0n:
      %Tms.zero(as, ins) : {Core.CCtr{c, _} == Core.CCtr{c, as} : Core.Tm}
      {==}
    case 1n+j:
      Sh.ctr.s(as, ins, j, c, True{})

def Sh.cases(cs: List<&2, Core.Tm>, +ins: Map<&2, Core.Def>, +j: Nat, top: Bool)
    -> {Core.CMat{Nil{}, Core.Tms.inline(ins, 1n+j, cs)} == Core.Tm.inline(ins, 1n+j, Core.CMat{Nil{}, cs}, top) : Core.Tm}:
  match cs:
    case Nil{}:
      {==}
    case c <> r:
      %Sh.cases(r, ins, j, False{}) : {Core.CMat{Nil{}, Core.Tm.inline(ins, 1n+j, c, True{}) <> Core.Tms.inline(ins, 1n+j, r)} == Core.Tm.push.case(Core.Tm.inline(ins, 1n+j, c, True{}), _) : Core.Tm}
      {==}

def Sh.mat.s(scrs: List<&2, Core.Tm>, +ins: Map<&2, Core.Def>, +j: Nat, +cs: List<&2, Core.Tm>, top: Bool)
    -> {Core.CMat{Core.Tms.inline(ins, 1n+j, scrs), Core.Tms.inline(ins, 1n+j, cs)} == Core.Tm.inline(ins, 1n+j, Core.CMat{scrs, cs}, top) : Core.Tm}:
  match scrs:
    case Nil{}:
      Sh.cases(cs, ins, j, top)
    case a <> r:
      %Sh.mat.s(r, ins, j, cs, False{}) : {Core.CMat{Core.Tm.inline(ins, 1n+j, a, True{}) <> Core.Tms.inline(ins, 1n+j, r), Core.Tms.inline(ins, 1n+j, cs)} == Core.Tm.push(Core.Tm.inline(ins, 1n+j, a, True{}), _) : Core.Tm}
      {==}

def Sh.mat(+ins: Map<&2, Core.Def>, k: Nat, scrs: List<&2, Core.Tm>, cs: List<&2, Core.Tm>)
    -> {Core.CMat{Core.Tms.inline(ins, k, scrs), Core.Tms.inline(ins, k, cs)} == Core.Tm.inline(ins, k, Core.CMat{scrs, cs}, True{}) : Core.Tm}:
  match k:
    case 0n:
      %Tms.zero(scrs, ins) : {Core.CMat{_, Core.Tms.inline(ins, 0n, cs)} == Core.CMat{scrs, cs} : Core.Tm}
      %Tms.zero(cs, ins) : {Core.CMat{scrs, _} == Core.CMat{scrs, cs} : Core.Tm}
      {==}
    case 1n+j:
      Sh.mat.s(scrs, ins, j, cs, True{})

# A call not inlined: its arguments with the pass taken.
def Sh.callF.s(as: List<&2, Core.Arg>, +ins: Map<&2, Core.Def>, +j: Nat, +f: String)
    -> {Core.CCall{f, Core.Args.inline(ins, 1n+j, as)} == Core.Tm.inline(ins, 1n+j, Core.CCall{f, as}, False{}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{+rel, +e}:
          %Sh.callF.s(r, ins, j, f) : {Core.CCall{f, Core.Arg{rel, Core.Tm.inline(ins, 1n+j, e, True{})} <> Core.Args.inline(ins, 1n+j, r)} == Core.Tm.push.call(Core.Arg{rel, Core.Tm.inline(ins, 1n+j, e, True{})}, _) : Core.Tm}
          {==}

def Sh.callF(as: List<&2, Core.Arg>, +ins: Map<&2, Core.Def>, k: Nat, +f: String)
    -> {Core.CCall{f, Core.Args.inline(ins, k, as)} == Core.Tm.inline(ins, k, Core.CCall{f, as}, False{}) : Core.Tm}:
  match k:
    case 0n:
      %Args.zero(as, ins) : {Core.CCall{f, _} == Core.CCall{f, as} : Core.Tm}
      {==}
    case 1n+j:
      Sh.callF.s(as, ins, j, f)

# A call at depth 1+j: inlined, if Inline.at says so.
def Sh.callT(as: List<&2, Core.Arg>, +ins: Map<&2, Core.Def>, +j: Nat, +f: String)
    -> {Core.Inline.at(Core.Inline.has(ins, f), Core.Inline.look(ins, f), f, Core.CCall{f, Core.Args.inline(ins, 1n+j, as)}, Core.Tm.inline(ins, j, Core.Inline.body(Core.Inline.look(ins, f)), True{}))
        == Core.Tm.inline(ins, 1n+j, Core.CCall{f, as}, True{}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{+rel, +e}:
          %Sh.callF.s(r, ins, j, f) : {Core.Inline.at(Core.Inline.has(ins, f), Core.Inline.look(ins, f), f, Core.CCall{f, Core.Arg{rel, Core.Tm.inline(ins, 1n+j, e, True{})} <> Core.Args.inline(ins, 1n+j, r)}, Core.Tm.inline(ins, j, Core.Inline.body(Core.Inline.look(ins, f)), True{}))
            == Core.Inline.at(Core.Inline.has(ins, f), Core.Inline.look(ins, f), f, Core.Tm.push.call(Core.Arg{rel, Core.Tm.inline(ins, 1n+j, e, True{})}, _), Core.Tm.inline(ins, j, Core.Inline.body(Core.Inline.look(ins, f)), True{})) : Core.Tm}
          {==}

# The scrutinees of an inlined call: one for each argument.
def Scrs.len(as: List<&2, Core.Arg>) -> {Core.Args.len(as) == Red.Tms.len(Core.Args.scrs(as)) : Nat}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          match rel:
            case Core.Run{}:
              %Scrs.len(r) : {1n+Core.Args.len(r) == 1n+_ : Nat}
              {==}
            case Core.Era{}:
              %Scrs.len(r) : {1n+Core.Args.len(r) == 1n+_ : Nat}
              {==}

# Fuel
# ====

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

# The fuel a run of the terms es that gives values needs: 1 for none, 3 and
# at least 2 more for each.
def Need(es: List<&2, Core.Tm>, q: Nat) -> Data:
  match es:
    case Nil{}:
      Red.Le(1n, q)
    case e <> r:
      match q:
        case 0n:
          Empty
        case 1n+a:
          match a:
            case 0n:
              Empty
            case 1n+b:
              match b:
                case 0n:
                  Empty
                case 1n+c:
                  Sigma<&2, &2, Need(r, c), _ => Red.Le(1n+1n+0n, c)>

def Fuel.cons(~prim: String -> List<&2, Core.Val> -> Core.Res, +q: Nat, +dz: List<&2, Core.Def>, x: Core.Res, +v: Core.Val,
    h: IsOk(Core.run(~prim, q, dz, Core.SThen{x, Core.KCons{v}}))) -> Sigma<&2, &2, Red.Le(1n+1n+0n, q), _ => IsOk(x)>:
  match q:
    case 0n:
      match h:
    case 1n+a:
      match a:
        case 0n:
          match x:
            case Core.ROk{vs}:
              match h:
            case Core.REnv{e}:
              match h:
            case Core.RNo{}:
              match h:
            case Core.RFail{m}:
              match h:
        case 1n+b:
          match x:
            case Core.ROk{vs}:
              (Unit{}, Unit{})
            case Core.REnv{e}:
              match h:
            case Core.RNo{}:
              match h:
            case Core.RFail{m}:
              match h:

def Fuel.pair(~prim: String -> List<&2, Core.Val> -> Core.Res, +c: Nat, +dz: List<&2, Core.Def>, +env: List<&2, Core.Val>, -e: Core.Tm,
    +r: List<&2, Core.Tm>, pr: Sigma<&2, &2, Red.Le(1n+1n+0n, c), _ => IsOk(Core.run(~prim, c, dz, Core.SEvals{env, r}))>,
    ih: @c:Nat -> IsOk(Core.run(~prim, c, dz, Core.SEvals{env, r})) -> Need(r, c)) -> Need(e <> r, 1n+1n+1n+c):
  match pr:
    case (l2, ok):
      (ih(c, ok), l2)

def Fuel.tail(~prim: String -> List<&2, Core.Val> -> Core.Res, +q1: Nat, +dz: List<&2, Core.Def>, x: Core.Res, +env: List<&2, Core.Val>,
    -e: Core.Tm, +r: List<&2, Core.Tm>, h: IsOk(Core.run(~prim, q1, dz, Core.SThen{x, Core.KTail{env, r}})),
    ih: @c:Nat -> IsOk(Core.run(~prim, c, dz, Core.SEvals{env, r})) -> Need(r, c)) -> Need(e <> r, 1n+q1):
  match q1:
    case 0n:
      match h:
    case 1n+q2:
      match q2:
        case 0n:
          match x:
            case Core.ROk{vs0}:
              match h:
            case Core.REnv{e9}:
              match h:
            case Core.RNo{}:
              match h:
            case Core.RFail{m}:
              match h:
        case 1n+q3:
          match x:
            case Core.ROk{vs0}:
              match vs0:
                case Nil{}:
                  match h:
                case v <> rest:
                  Fuel.pair(~prim, q3, dz, env, e, r, Fuel.cons(~prim, q3, dz, Core.run(~prim, q3, dz, Core.SEvals{env, r}), v, h), ih)
            case Core.REnv{e9}:
              match h:
            case Core.RNo{}:
              match h:
            case Core.RFail{m}:
              match h:

def Fuel.evals(~prim: String -> List<&2, Core.Val> -> Core.Res, es: List<&2, Core.Tm>, +q: Nat, +dz: List<&2, Core.Def>, +env: List<&2, Core.Val>,
    h: IsOk(Core.run(~prim, q, dz, Core.SEvals{env, es}))) -> Need(es, q):
  match es:
    case Nil{}:
      match q:
        case 0n:
          match h:
        case 1n+c:
          Unit{}
    case +e <> +r:
      match q:
        case 0n:
          match h:
        case 1n+q1:
          Fuel.tail(~prim, q1, dz, Core.run(~prim, q1, dz, Core.SEval{env, e}), env, e, r, h,
            c => hc => Fuel.evals(~prim, r, c, dz, env, hc))

def Need.le(r: List<&2, Core.Tm>, +c: Nat, hn: Need(r, c), +l2: Red.Le(1n+1n+0n, c)) -> Red.Le(1n+1n+Red.Tms.len(r), c):
  match r:
    case Nil{}:
      l2
    case e <> +s:
      match c:
        case 0n:
          match hn:
        case 1n+a:
          match a:
            case 0n:
              match hn:
            case 1n+b:
              match b:
                case 0n:
                  match hn:
                case 1n+d:
                  match hn:
                    case (hs, ls):
                      Le.down(Red.Tms.len(s), d, Le.down(1n+Red.Tms.len(s), d, Need.le(s, d, hs, ls)))

# The room a run of the scrutinees leaves the match.
def Room.of(es: List<&2, Core.Tm>, +q: Nat, h: Need(es, q)) -> Law.Room4(Red.Tms.len(es), q):
  match es:
    case Nil{}:
      Le.total(1n+1n+1n+1n+0n, q)
    case e <> r:
      match q:
        case 0n:
          match h:
        case 1n+a:
          match a:
            case 0n:
              match h:
            case 1n+b:
              match b:
                case 0n:
                  match h:
                case 1n+c:
                  match h:
                    case (hn, l2):
                      Inl{Need.le(r, c, hn, l2)}

# The match's patterns, a variable for each parameter, bind them as a call
# does, in L+1 steps.
def Pat.vars(~prim: String -> List<&2, Core.Val> -> Core.Res, ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, +q: Nat, +dz: List<&2, Core.Def>,
    +env: List<&2, Core.Val>, hl: Red.Len(vs, Core.Pars.len(ps)), hq: Red.Le(1n+Core.Pars.len(ps), q))
    -> {Core.REnv{Core.Scope.push(ps, vs, env)} == Core.run(~prim, q, dz, Core.SPat{env, Core.Pars.vars(ps), vs}) : Core.Res}:
  match ps:
    case Nil{}:
      match vs:
        case Nil{}:
          match q:
            case 0n:
              match hq:
            case 1n+c:
              {==}
        case v <> r:
          match hl:
    case pa <> pr:
      match pa:
        case Core.Par{+x, rel, mode, ty}:
          match vs:
            case Nil{}:
              match hl:
            case v <> vr:
              match q:
                case 0n:
                  match hq:
                case 1n+c:
                  Pat.vars(~prim, pr, vr, c, dz, Core.VBnd{x, v} <> env, hl, hq)

# The body's value, applied to no more arguments.
def Apply1(~prim: String -> List<&2, Core.Val> -> Core.Res, -ins: Map<&2, Core.Def>, +p: Nat, +dz: List<&2, Core.Def>, x: Core.Res, -y: Core.Res,
    rr: Law.RRel(ins, x, y), fx: Red.Fits(x, Red.WLen{1n})) -> Law.RRel(ins, Core.run(~prim, p, dz, Core.SThen{x, Core.KApply{Nil{}}}), y):
  match p:
    case 0n:
      Unit{}
    case 1n+p1:
      match p1:
        case 0n:
          match x:
            case Core.ROk{vs}:
              Unit{}
            case Core.REnv{e}:
              Unit{}
            case Core.RNo{}:
              Unit{}
            case Core.RFail{m}:
              Unit{}
        case 1n+p2:
          match p2:
            case 0n:
              match x:
                case Core.ROk{vs}:
                  match vs:
                    case Nil{}:
                      Unit{}
                    case v <> r:
                      Unit{}
                case Core.REnv{e}:
                  Unit{}
                case Core.RNo{}:
                  Unit{}
                case Core.RFail{m}:
                  Unit{}
            case 1n+p3:
              match x:
                case Core.ROk{vs}:
                  match vs:
                    case Nil{}:
                      Unit{}
                    case v <> r:
                      match r:
                        case Nil{}:
                          rr
                        case w <> s:
                          match fx:
                case Core.REnv{e}:
                  Unit{}
                case Core.RNo{}:
                  Unit{}
                case Core.RFail{m}:
                  Unit{}

# Patterns
# ========

# One pattern's step against related values.
def Pat.rel(-ins: Map<&2, Core.Def>, -ds: List<&2, Core.Def>, -m: Nat, +e1: List<&2, Core.Val>, pt: Core.Pt, +v: Core.Val, +pr: List<&2, Core.Pt>,
    +vr: List<&2, Core.Val>, +e2: List<&2, Core.Val>, +v2: Core.Val, +vr2: List<&2, Core.Val>, vv: Law.VRel(ins, v, v2),
    +rr: Law.VRels(ins, vr, vr2), +h: Law.ERel(ins, e1, e2))
    -> Law.SRel(ins, ds, m, Core.Pat.step(e1, pt, v, pr, vr), Core.Pat.step(e2, pt, v2, pr, vr2)):
  match pt:
    case Core.PtVar{+x}:
      (Core.VBnd{x, v2} <> e2, vr2, {==}, rr, (({==}, vv), h))
    case Core.PtCtr{+kp, +qs}:
      match v:
        case Core.VLit{+l1}:
          match v2:
            case Core.VLit{+l2}:
              (e2, vr2, {==}, rr, h)
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VCtr{+k1, +fs1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
                case (ek, +vf):
                  %ek : Law.SRel(ins, ds, m, Core.SPatC{Bool.and(String.eq(kp, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, Core.SPatC{Bool.and(String.eq(kp, _), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs2))), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  %Len.eq(ins, fs1, fs2, vf) : Law.SRel(ins, ds, m, Core.SPatC{Bool.and(String.eq(kp, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, Core.SPatC{Bool.and(String.eq(kp, k1), Nat.is_eq(Core.Pts.len(qs), _)), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  (e2, Core.Vals.cat(fs2, vr2), {==}, Cat(ins, fs1, fs2, vr, vr2, vf, rr), h)
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VClo{+env1, +p1, +b1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              (e2, vr2, {==}, rr, h)
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VFun{+f1, +as1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              (e2, vr2, {==}, rr, h)
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VTrm{+t1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              (e2, vr2, {==}, rr, h)
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VBnd{+x1, +w1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              (e2, vr2, {==}, rr, h)
    case Core.PtNat{+n}:
      match v:
        case Core.VLit{+l1}:
          match v2:
            case Core.VLit{+l2}:
              %vv : Law.SRel(ins, ds, m, Core.Pat.step(e1, Core.PtNat{n}, Core.VLit{l1}, pr, vr), Core.Pat.step(e2, Core.PtNat{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, rr, h)
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VCtr{+k1, +fs1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              (e2, vr2, {==}, rr, h)
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VClo{+env1, +p1, +b1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              (e2, vr2, {==}, rr, h)
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VFun{+f1, +as1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              (e2, vr2, {==}, rr, h)
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VTrm{+t1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              (e2, vr2, {==}, rr, h)
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VBnd{+x1, +w1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              (e2, vr2, {==}, rr, h)
    case Core.PtNum{+n}:
      match v:
        case Core.VLit{+l1}:
          match v2:
            case Core.VLit{+l2}:
              %vv : Law.SRel(ins, ds, m, Core.Pat.step(e1, Core.PtNum{n}, Core.VLit{l1}, pr, vr), Core.Pat.step(e2, Core.PtNum{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, rr, h)
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VCtr{+k1, +fs1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              (e2, vr2, {==}, rr, h)
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VClo{+env1, +p1, +b1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              (e2, vr2, {==}, rr, h)
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VFun{+f1, +as1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              (e2, vr2, {==}, rr, h)
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VTrm{+t1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              (e2, vr2, {==}, rr, h)
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VBnd{+x1, +w1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              (e2, vr2, {==}, rr, h)
    case Core.PtFlt{+n}:
      match v:
        case Core.VLit{+l1}:
          match v2:
            case Core.VLit{+l2}:
              %vv : Law.SRel(ins, ds, m, Core.Pat.step(e1, Core.PtFlt{n}, Core.VLit{l1}, pr, vr), Core.Pat.step(e2, Core.PtFlt{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, rr, h)
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VCtr{+k1, +fs1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              (e2, vr2, {==}, rr, h)
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VClo{+env1, +p1, +b1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              (e2, vr2, {==}, rr, h)
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VFun{+f1, +as1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              (e2, vr2, {==}, rr, h)
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VTrm{+t1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              (e2, vr2, {==}, rr, h)
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VBnd{+x1, +w1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              (e2, vr2, {==}, rr, h)
    case Core.PtSuc{+ks, +q}:
      match v:
        case Core.VLit{+l1}:
          match l1:
            case Core.LNum{+n9}:
              match v2:
                case Core.VLit{+l2}:
                  %vv : Law.SRel(ins, ds, m, Core.Pat.step(e1, Core.PtSuc{ks, q}, Core.VLit{Core.LNum{n9}}, pr, vr), Core.Pat.step(e2, Core.PtSuc{ks, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, rr, h)
                case Core.VCtr{+k2, +fs2}:
                  match vv:
                case Core.VClo{+env2, +p2, +b2}:
                  match vv:
                case Core.VFun{+f2, +as2}:
                  match vv:
                case Core.VTrm{+t2}:
                  match vv:
                case Core.VBnd{+x2, +w2}:
                  match vv:
            case Core.LNat{+n9}:
              match v2:
                case Core.VLit{+l2}:
                  %vv : Law.SRel(ins, ds, m, Core.Pat.step(e1, Core.PtSuc{ks, q}, Core.VLit{Core.LNat{n9}}, pr, vr), Core.Pat.step(e2, Core.PtSuc{ks, q}, Core.VLit{_}, pr, vr2))
                  (e2, Core.VLit{Core.LNat{U32.sub(n9, ks)}} <> vr2, {==}, ({==}, rr), h)
                case Core.VCtr{+k2, +fs2}:
                  match vv:
                case Core.VClo{+env2, +p2, +b2}:
                  match vv:
                case Core.VFun{+f2, +as2}:
                  match vv:
                case Core.VTrm{+t2}:
                  match vv:
                case Core.VBnd{+x2, +w2}:
                  match vv:
            case Core.LFlt{+s9}:
              match v2:
                case Core.VLit{+l2}:
                  %vv : Law.SRel(ins, ds, m, Core.Pat.step(e1, Core.PtSuc{ks, q}, Core.VLit{Core.LFlt{s9}}, pr, vr), Core.Pat.step(e2, Core.PtSuc{ks, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, rr, h)
                case Core.VCtr{+k2, +fs2}:
                  match vv:
                case Core.VClo{+env2, +p2, +b2}:
                  match vv:
                case Core.VFun{+f2, +as2}:
                  match vv:
                case Core.VTrm{+t2}:
                  match vv:
                case Core.VBnd{+x2, +w2}:
                  match vv:
            case Core.LStr{+s9}:
              match v2:
                case Core.VLit{+l2}:
                  %vv : Law.SRel(ins, ds, m, Core.Pat.step(e1, Core.PtSuc{ks, q}, Core.VLit{Core.LStr{s9}}, pr, vr), Core.Pat.step(e2, Core.PtSuc{ks, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, rr, h)
                case Core.VCtr{+k2, +fs2}:
                  match vv:
                case Core.VClo{+env2, +p2, +b2}:
                  match vv:
                case Core.VFun{+f2, +as2}:
                  match vv:
                case Core.VTrm{+t2}:
                  match vv:
                case Core.VBnd{+x2, +w2}:
                  match vv:
        case Core.VCtr{+k1, +fs1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              (e2, vr2, {==}, rr, h)
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VClo{+env1, +p1, +b1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              (e2, vr2, {==}, rr, h)
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VFun{+f1, +as1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              (e2, vr2, {==}, rr, h)
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VTrm{+t1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              (e2, vr2, {==}, rr, h)
            case Core.VBnd{+x2, +w2}:
              match vv:
        case Core.VBnd{+x1, +w1}:
          match v2:
            case Core.VLit{+l2}:
              match vv:
            case Core.VCtr{+k2, +fs2}:
              match vv:
            case Core.VClo{+env2, +p2, +b2}:
              match vv:
            case Core.VFun{+f2, +as2}:
              match vv:
            case Core.VTrm{+t2}:
              match vv:
            case Core.VBnd{+x2, +w2}:
              (e2, vr2, {==}, rr, h)

# Lookups
# =======

def Look(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +m: Nat, +le: Red.Le(1n+p, m), e1: List<&2, Core.Val>, +x: String, e2: List<&2, Core.Val>,
    h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SLook{e1, x}), Core.run(~prim, m, Core.Defs.inline(ins, k, ds), Core.SLook{e2, x})):
  match m:
    case 0n:
      match le:
    case 1n+q:
      match e1:
        case Nil{}:
          Unit{}
        case b1 <> +r1:
          match b1:
            case Core.VLit{+l1}:
              match e2:
                case Nil{}:
                  match h:
                case b2 <> +r2:
                  match b2:
                    case Core.VLit{+l2}:
                      match h:
                        case (vv, +hr):
                          ih(q, le, Core.SLook{r1, x}, Core.SLook{r2, x}, (r2, {==}, hr))
                    case Core.VCtr{+k2, +fs2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VClo{+env2, +p2, +b2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VFun{+f2, +as2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VTrm{+t2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VBnd{+x2, +w2}:
                      match h:
                        case (vv, +hr):
                          match vv:
            case Core.VCtr{+k1, +fs1}:
              match e2:
                case Nil{}:
                  match h:
                case b2 <> +r2:
                  match b2:
                    case Core.VLit{+l2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VCtr{+k2, +fs2}:
                      match h:
                        case (vv, +hr):
                          ih(q, le, Core.SLook{r1, x}, Core.SLook{r2, x}, (r2, {==}, hr))
                    case Core.VClo{+env2, +p2, +b2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VFun{+f2, +as2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VTrm{+t2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VBnd{+x2, +w2}:
                      match h:
                        case (vv, +hr):
                          match vv:
            case Core.VClo{+env1, +p1, +b1}:
              match e2:
                case Nil{}:
                  match h:
                case b2 <> +r2:
                  match b2:
                    case Core.VLit{+l2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VCtr{+k2, +fs2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VClo{+env2, +p2, +b2}:
                      match h:
                        case (vv, +hr):
                          ih(q, le, Core.SLook{r1, x}, Core.SLook{r2, x}, (r2, {==}, hr))
                    case Core.VFun{+f2, +as2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VTrm{+t2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VBnd{+x2, +w2}:
                      match h:
                        case (vv, +hr):
                          match vv:
            case Core.VFun{+f1, +as1}:
              match e2:
                case Nil{}:
                  match h:
                case b2 <> +r2:
                  match b2:
                    case Core.VLit{+l2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VCtr{+k2, +fs2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VClo{+env2, +p2, +b2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VFun{+f2, +as2}:
                      match h:
                        case (vv, +hr):
                          ih(q, le, Core.SLook{r1, x}, Core.SLook{r2, x}, (r2, {==}, hr))
                    case Core.VTrm{+t2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VBnd{+x2, +w2}:
                      match h:
                        case (vv, +hr):
                          match vv:
            case Core.VTrm{+t1}:
              match e2:
                case Nil{}:
                  match h:
                case b2 <> +r2:
                  match b2:
                    case Core.VLit{+l2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VCtr{+k2, +fs2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VClo{+env2, +p2, +b2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VFun{+f2, +as2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VTrm{+t2}:
                      match h:
                        case (vv, +hr):
                          ih(q, le, Core.SLook{r1, x}, Core.SLook{r2, x}, (r2, {==}, hr))
                    case Core.VBnd{+x2, +w2}:
                      match h:
                        case (vv, +hr):
                          match vv:
            case Core.VBnd{+x1, +w1}:
              match e2:
                case Nil{}:
                  match h:
                case b2 <> +r2:
                  match b2:
                    case Core.VLit{+l2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VCtr{+k2, +fs2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VClo{+env2, +p2, +b2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VFun{+f2, +as2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VTrm{+t2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                    case Core.VBnd{+x2, +w2}:
                      match h:
                        case (vv, +hr):
                          match vv:
                            case (ey, +vw):
                              %ey : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SLook{Core.VBnd{x1, w1} <> r1, x}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SLook{Core.VBnd{_, w2} <> r2, x}))
                              ih(q, le, Core.SLook2{String.eq(x1, x), w1, r1, x}, Core.SLook2{String.eq(x1, x), w2, r2, x}, (w2, r2, {==}, vw, hr))

