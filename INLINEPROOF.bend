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

# An inlined call
# ===============

def Nat.sym(-a: Nat, -b: Nat, e: {a == b : Nat}) -> {b == a : Nat}:
  %e : {_ == a : Nat}
  {==}

def Len.val(vs: List<&2, Core.Val>, +n: Nat, h: Red.Len(vs, n)) -> {n == Core.Vals.len(vs) : Nat}:
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
          %Len.val(r, c, h) : {1n+c == 1n+_ : Nat}
          {==}

def Fits.conv(-x: Core.Res, -a: Nat, -b: Nat, e: {a == b : Nat}, h: Red.Fits(x, Red.WLen{a})) -> Red.Fits(x, Red.WLen{b}):
  %e : Red.Fits(x, Red.WLen{_})
  h

def Room4.conv(-a: Nat, -b: Nat, -q: Nat, e: {a == b : Nat}, h: Law.Room4(a, q)) -> Law.Room4(b, q):
  %e : Law.Room4(_, q)
  h

# The arguments' results, as the inlined call's steps want them.
def CallR.mk(-ins: Map<&2, Core.Def>, r1: Core.Res, x: Core.Res, -L: Nat, -q: Nat, rr: Law.RRel(ins, r1, x),
    fx: Red.Fits(x, Red.WLen{L}), hroom: IsOk(x) -> Law.Room4(L, q)) -> Law.CallR(ins, r1, x, L, q):
  match r1:
    case Core.ROk{vs1}:
      match x:
        case Core.ROk{vs2}:
          (rr, fx, hroom(Unit{}))
        case Core.REnv{e}:
          match rr:
        case Core.RNo{}:
          match rr:
        case Core.RFail{m}:
          match rr:
    case Core.REnv{e}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.RFail{m}:
      Unit{}

def Le.absurd(-T: Data, -a: Nat, h: Red.Le(1n+a, 0n)) -> T:
  match h:

# The call has an argument for each parameter.
def Enter.short(-ins: Map<&2, Core.Def>, +ps: List<&2, Core.Par>, +vs1: List<&2, Core.Val>, +vs2: List<&2, Core.Val>,
    vr: Law.VRels(ins, vs1, vs2), hl: Red.Len(vs2, Core.Pars.len(ps))) -> Dead.Fls(Nat.is_lt(Core.Vals.len(vs1), Core.Pars.len(ps))):
  %Nat.sym(Core.Pars.len(ps), Core.Vals.len(vs1), Len.val(vs1, Core.Pars.len(ps), Len.rel(ins, vs1, vs2, Core.Pars.len(ps), vr, hl)))
    : Dead.Fls(Nat.is_lt(Core.Vals.len(vs1), _))
  Nat.lt.self(Core.Vals.len(vs1))

# The source's call runs out of fuel before it finds f's def.
def Find.one(~prim: String -> List<&2, Core.Val> -> Core.Res, -prog: List<&2, Core.Def>, dz: List<&2, Core.Def>, +f: String, -vs: List<&2, Core.Val>,
    -ps: List<&2, Core.Par>, -b: Core.Tm, fd: Law.Found(dz, f, ps, b))
    -> {Core.RFail{"out of fuel"} == Core.run(~prim, 1n, prog, Core.SFind{dz, f, vs}) : Core.Res}:
  match dz:
    case Nil{}:
      match fd:
    case d <> r:
      match d:
        case Core.Def{name, ps2, b2, ret}:
          {==}

def Call.small(~prim: String -> List<&2, Core.Val> -> Core.Res, -ins: Map<&2, Core.Def>, ds: List<&2, Core.Def>, +p: Nat, +q: Nat,
    le: Red.Le(p, q), lr: Red.Le(q, 1n), +f: String, -vs1: List<&2, Core.Val>, -ps: List<&2, Core.Par>, -b: Core.Tm,
    fd: Law.Found(ds, f, ps, b), -y: Core.Res)
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SCallDef{f, vs1}), y):
  match p:
    case 0n:
      Unit{}
    case 1n+p1:
      match p1:
        case 0n:
          %Find.one(~prim, ds, ds, f, vs1, ps, b, fd) : Law.RRel(ins, _, y)
          Unit{}
        case 1n+p2:
          Le.absurd(Law.RRel(ins, Core.run(~prim, 1n+1n+1n+p2, ds, Core.SCallDef{f, vs1}), y), p2,
            Le.trans(1n+1n+p2, q, 1n, le, lr))

# The source's call and the other program's match: the match binds the
# parameters, and the other program waits at the body.
def Call.def.go(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +f: String, vs1: List<&2, Core.Val>, +ps: List<&2, Core.Par>, +b: Core.Tm,
    +j: Nat, +e2: List<&2, Core.Val>, +vs2: List<&2, Core.Val>, fd: Law.Found(ds, f, ps, b), vr: Law.VRels(ins, vs1, vs2),
    +hl: Red.Len(vs2, Core.Pars.len(ps)), room: Law.Room2(Core.Pars.len(ps), 1n+q), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SCallDef{f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SMatch{e2, vs2, Law.Cases(ins, ps, j, b)})):
  match room:
    case Inl{lr}:
      %Pat.vars(~prim, ps, vs2, q, Core.Defs.inline(ins, k, ds), e2, hl, lr) : Law.RRel(ins, Core.run(~prim, p, ds, Core.SFind{ds, f, vs1}),
        Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SThen{_, Core.KCase{e2, vs2, Core.Tm.inline(ins, j, b, True{}), Nil{}}}))
      ih(q, le, Core.SFind{ds, f, vs1}, Core.SThen{Core.REnv{Core.Scope.push(ps, vs2, e2)}, Core.KCase{e2, vs2, Core.Tm.inline(ins, j, b, True{}), Nil{}}},
        Inr{(ps, b, fd, j, e2, vs2, {==}, vr, hl)})
    case Inr{lr}:
      Call.small(~prim, ins, ds, p, q, le, lr, f, vs1, ps, b, fd, Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SMatch{e2, vs2, Law.Cases(ins, ps, j, b)}))

def Call.def.step(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +f: String, vs1: List<&2, Core.Val>, s2: Core.Sel,
    h: Law.Call.def(ins, ds, 1n+q, f, vs1, s2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SCallDef{f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2)):
  match h:
    case (+ps, +b, +j, +e2, +vs2, eq, fd, vr, hl, room):
      %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SCallDef{f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), _))
      Call.def.go(~prim, ~ins, ~ok, ~one, ~ds, ~agree, k, p, q, le, f, vs1, ps, b, j, e2, vs2, fd, vr, hl, room, ih)

# The arguments' values: the call due, and the match.
def Call.ok.step(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +f: String, vs1: List<&2, Core.Val>, s2: Core.Sel,
    h: Law.Call.ok(ins, ds, 1n+q, Core.KCall{f}, vs1, s2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f}, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2)):
  match h:
    case (+ps, +b, +j, +e2, +vs2, eq, fd, vr, hl, room):
      %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f}, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), _))
      ih(q, le, Core.SCallDef{f, vs1}, Core.SMatch{e2, vs2, Law.Cases(ins, ps, j, b)}, Inr{(ps, b, j, e2, vs2, {==}, fd, vr, hl, room)})

# The arguments' run done.
def Call.then.go(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +vs1: List<&2, Core.Val>, +f: String, +ps: List<&2, Core.Par>, +b: Core.Tm,
    +j: Nat, +e2: List<&2, Core.Val>, r2: Core.Res, s2: Core.Sel,
    eq: {Core.SThen{r2, Core.KMat{e2, Law.Cases(ins, ps, j, b)}} == s2 : Core.Sel}, fd: Law.Found(ds, f, ps, b),
    cr: Law.CallR(ins, Core.ROk{vs1}, r2, Core.Pars.len(ps), 1n+q), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{vs1}, Core.KCall{f}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2)):
  match r2:
    case Core.ROk{+vs2}:
      match cr:
        case (vr, hl, room):
          %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{vs1}, Core.KCall{f}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), _))
          ih(q, le, Core.SOk{Core.KCall{f}, vs1}, Core.SOk{Core.KMat{e2, Law.Cases(ins, ps, j, b)}, vs2}, Inr{(ps, b, j, e2, vs2, {==}, fd, vr, hl, room)})
    case Core.REnv{e9}:
      match cr:
    case Core.RNo{}:
      match cr:
    case Core.RFail{m9}:
      match cr:

def Call.then.step(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), r1: Core.Res, +f: String, s2: Core.Sel,
    h: Law.Call.then(ins, ds, 1n+q, r1, Core.KCall{f}, s2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{r1, Core.KCall{f}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2)):
  match r1:
    case Core.ROk{+vs1}:
      match h:
        case (+ps, +b, +j, +e2, r2, eq, fd, cr):
          Call.then.go(~prim, ~ins, ~ok, ~one, ~ds, ~agree, k, p, q, le, vs1, f, ps, b, j, e2, r2, s2, eq, fd, cr, ih)
    case Core.REnv{e9}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.RFail{m9}:
      Unit{}

# The source looks for f's def.
def Call.find.step(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), dz: List<&2, Core.Def>, +f: String, +vs1: List<&2, Core.Val>, s2: Core.Sel,
    h: Law.Call.find(ins, dz, f, vs1, s2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SFind{dz, f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2)):
  match dz:
    case Nil{}:
      match h:
        case (ps, b, fd, at):
          match fd:
    case d <> +r:
      match d:
        case Core.Def{+name, +ps2, +b2, ret}:
          match h:
            case (ps, b, fd, at):
              ih(1n+q, RP.Le.succ(p, q, le), Core.SFound{String.eq(name, f), ps2, b2, r, f, vs1}, s2, Inr{(ps, b, fd, at)})

def Call.found.step(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), hb: Bool, +ps2: List<&2, Core.Par>, +b2: Core.Tm, +r: List<&2, Core.Def>,
    +f: String, +vs1: List<&2, Core.Val>, s2: Core.Sel, h: Law.Call.found(ins, hb, ps2, b2, r, f, vs1, s2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SFound{hb, ps2, b2, r, f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2)):
  match h:
    case (+ps, +b, fa, at):
      match fa:
        case Inl{c}:
          match c:
            case (eh, eps, eb):
              match at:
                case (+j, +e2, +vs2, eq, +vr, +hl):
                  %eh : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SFound{_, ps2, b2, r, f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2))
                  %eps : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SFound{True{}, _, b2, r, f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2))
                  %eb : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, _, r, f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2))
                  ih(1n+q, RP.Le.succ(p, q, le), Core.SEnter{Nat.is_lt(Core.Vals.len(vs1), Core.Pars.len(ps)), f, ps, b, vs1}, s2,
                    Inr{(Enter.short(ins, ps, vs1, vs2, vr, hl), j, e2, vs2, eq, vr, hl)})
        case Inr{c}:
          match c:
            case (eh, fd):
              %eh : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SFound{_, ps2, b2, r, f, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2))
              ih(1n+q, RP.Le.succ(p, q, le), Core.SFind{r, f, vs1}, s2, Inr{(ps, b, fd, at)})

# The body runs in the parameters' scope, the other program's in front of
# its own; the value, applied to no more arguments, is the call's.
def Call.enter.step(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), sh: Bool, +f: String, +ps: List<&2, Core.Par>, +b: Core.Tm,
    +vs1: List<&2, Core.Val>, s2: Core.Sel, h: Law.Call.enter(ins, sh, ps, b, vs1, s2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEnter{sh, f, ps, b, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), s2)):
  match sh:
    case True{}:
      match h:
        case (fl, at):
          match fl:
    case False{}:
      match h:
        case (fl, at):
          match at:
            case (+j, +e2, +vs2, eq, +vr, hl):
              %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, b, vs1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), _))
              %Drop.all(vs1, Core.Pars.len(ps), Len.rel(ins, vs1, vs2, Core.Pars.len(ps), vr, hl)) : Law.RRel(ins,
                Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs1), b}), Core.KApply{_}}),
                Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{Core.Scope.push(ps, vs2, e2), Core.Tm.inline(ins, j, b, True{})}))
              Apply1(~prim, ins, p, ds, Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs1), b}),
                Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{Core.Scope.push(ps, vs2, e2), Core.Tm.inline(ins, j, b, True{})}),
                ih(q, le, Core.SEval{Core.Scope.bind(ps, vs1), b}, Core.SEval{Core.Scope.push(ps, vs2, e2), Core.Tm.inline(ins, j, b, True{})},
                  (Core.Scope.push(ps, vs2, e2), j, {==}, Bind.push(ins, ps, vs1, vs2, vr, Nil{}, e2, Unit{}))),
                RP.S.one(~prim, ~one, p, ds, Core.SEval{Core.Scope.bind(ps, vs1), b}))

# A call's term
# =============

def Eq.args0(+e2: List<&2, Core.Val>, as: List<&2, Core.Arg>, +ins: Map<&2, Core.Def>)
    -> {Law.ArgsT(True{}, e2, Core.Args.inline(ins, 0n, as)) == Core.SArgs{e2, as} : Core.Sel}:
  %Args.zero(as, ins) : {Core.SArgs{e2, _} == Core.SArgs{e2, as} : Core.Sel}
  {==}

# The scrutinees, one for each parameter.
def Eq.len(+as2: List<&2, Core.Arg>, +ps: List<&2, Core.Par>, hq: Dead.Tru(Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps))))
    -> {Red.Tms.len(Core.Args.scrs(as2)) == Core.Pars.len(ps) : Nat}:
  %Scrs.len(as2) : {_ == Core.Pars.len(ps) : Nat}
  Nat.eq.of(Core.Args.len(as2), Core.Pars.len(ps), hq)

# What the pass inlines: f's def, an argument for each parameter.
def Yes(ds: List<&2, Core.Def>, f: String, ps: List<&2, Core.Par>, b: Core.Tm, as2: List<&2, Core.Arg>) -> Data:
  Sigma<&2, &2, Law.Found(ds, f, ps, b), _ => Dead.Tru(Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps)))>

def Yes.mk(ds: List<&2, Core.Def>, +hb: Bool, +name: String, +f: String, +ps: List<&2, Core.Par>, b: Core.Tm, +as2: List<&2, Core.Arg>,
    ag: Dead.Tru(hb) -> Dead.Tru(String.eq(name, f)) -> Law.Found(ds, f, ps, b),
    +hc: Dead.Tru(Bool.and(hb, Bool.and(String.eq(name, f), Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps)))))) -> Yes(ds, f, ps, b, as2):
  (ag(And.l(hb, Bool.and(String.eq(name, f), Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps))), hc),
     And.l(String.eq(name, f), Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps)),
       And.r(hb, Bool.and(String.eq(name, f), Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps))), hc))),
   And.r(String.eq(name, f), Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps)),
     And.r(hb, Bool.and(String.eq(name, f), Nat.is_eq(Core.Args.len(as2), Core.Pars.len(ps))), hc)))

# The call inlined: the arguments run as the match's scrutinees.
def L.call.in(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +e1: List<&2, Core.Val>, +f: String, +as: List<&2, Core.Arg>, +e2: List<&2, Core.Val>,
    +j: Nat, +ps: List<&2, Core.Par>, +b: Core.Tm, y: Yes(ds, f, ps, b, Core.Args.inline(ins, 1n+j, as)),
    h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f, as}}),
         Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2,
           Core.CMat{Core.Args.scrs(Core.Args.inline(ins, 1n+j, as)), [Core.CCse{Core.Pars.vars(ps), Core.Tm.inline(ins, j, b, True{})}]}})):
  match y:
    case (fd, +hq):
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, as}), Core.KCall{f}},
        Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))}), Core.KMat{e2, Law.Cases(ins, ps, j, b)}},
        Inr{(ps, b, j, e2, Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))}), {==}, fd,
          CallR.mk(ins, Core.run(~prim, p, ds, Core.SArgs{e1, as}), Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))}),
            Core.Pars.len(ps), q,
            ih(q, le, Core.SArgs{e1, as}, Core.SEvals{e2, Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))}, (e2, 1n+j, False{}, {==}, h)),
            Fits.conv(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))}),
              Red.Tms.len(Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))), Core.Pars.len(ps),
              Eq.len(Core.Args.inline(ins, 1n+j, as), ps, hq),
              RP.S.one(~prim, ~one, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))})),
            ok => Room4.conv(Red.Tms.len(Core.Args.scrs(Core.Args.inline(ins, 1n+j, as))), Core.Pars.len(ps), q,
              Eq.len(Core.Args.inline(ins, 1n+j, as), ps, hq),
              Room.of(Core.Args.scrs(Core.Args.inline(ins, 1n+j, as)), q,
                Fuel.evals(~prim, Core.Args.scrs(Core.Args.inline(ins, 1n+j, as)), q, Core.Defs.inline(ins, k, ds), e2, ok)))))})

# The call, inlined (c) or not.
def L.call.pick(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +e1: List<&2, Core.Val>, +f: String, +as: List<&2, Core.Arg>, +e2: List<&2, Core.Val>,
    +j: Nat, +ps: List<&2, Core.Par>, +b: Core.Tm, c: Bool, yes: Dead.Tru(c) -> Yes(ds, f, ps, b, Core.Args.inline(ins, 1n+j, as)),
    h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f, as}}),
         Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Bool.pick(Core.Tm, c,
           Core.CMat{Core.Args.scrs(Core.Args.inline(ins, 1n+j, as)), [Core.CCse{Core.Pars.vars(ps), Core.Tm.inline(ins, j, b, True{})}]},
           Core.CCall{f, Core.Args.inline(ins, 1n+j, as)})})):
  match c:
    case True{}:
      L.call.in(~prim, ~ins, ~ok, ~one, ~ds, ~agree, k, p, q, le, e1, f, as, e2, j, ps, b, yes(Unit{}), h, ih, ih2)
    case False{}:
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, as}), Core.KCall{f}},
        Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SArgs{e2, Core.Args.inline(ins, 1n+j, as)}), Core.KCall{f}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SArgs{e2, Core.Args.inline(ins, 1n+j, as)}), Core.KCall{f}, {==}, {==},
          ih(q, le, Core.SArgs{e1, as}, Core.SArgs{e2, Core.Args.inline(ins, 1n+j, as)}, (e2, 1n+j, True{}, {==}, h)))})

# The call against the pass's term for it, at d (f's def when hb).
def L.call.at(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +e1: List<&2, Core.Val>, +f: String, +as: List<&2, Core.Arg>, +e2: List<&2, Core.Val>,
    +j: Nat, +hb: Bool, d: Core.Def,
    ag: Dead.Tru(hb) -> Dead.Tru(String.eq(Law.Def.name(d), f)) -> Law.Found(ds, f, Law.Def.pars(d), Core.Inline.body(d)),
    h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f, as}}),
         Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Inline.at(hb, d, f, Core.CCall{f, Core.Args.inline(ins, 1n+j, as)},
           Core.Tm.inline(ins, j, Core.Inline.body(d), True{}))})):
  match d:
    case Core.Def{+name, +ps, +db, ret}:
      L.call.pick(~prim, ~ins, ~ok, ~one, ~ds, ~agree, k, p, q, le, e1, f, as, e2, j, ps, db,
        Bool.and(hb, Bool.and(String.eq(name, f), Nat.is_eq(Core.Args.len(Core.Args.inline(ins, 1n+j, as)), Core.Pars.len(ps)))),
        hc => Yes.mk(ds, hb, name, f, ps, db, Core.Args.inline(ins, 1n+j, as), ag, hc),
        h, ih, ih2)

# A call's step: the pass's term for it inlined or not.
def L.call(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +m: Nat, +le: Red.Le(1n+p, m), +e1: List<&2, Core.Val>, +f: String, +as: List<&2, Core.Arg>, +e2: List<&2, Core.Val>,
    +j: Nat, h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f, as}}),
         Core.run(~prim, m, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, Core.CCall{f, as}, True{})})):
  match m:
    case 0n:
      match le:
    case 1n+q:
      match j:
        case 0n:
          ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, as}), Core.KCall{f}},
            Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SArgs{e2, as}), Core.KCall{f}},
            Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SArgs{e2, as}), Core.KCall{f}, {==}, {==},
              ih(q, le, Core.SArgs{e1, as}, Core.SArgs{e2, as}, (e2, 0n, True{}, Eq.args0(e2, as, ins), h)))})
        case 1n+i:
          %Sh.callT(as, ins, i, f) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f, as}}),
            Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
          L.call.at(~prim, ~ins, ~ok, ~one, ~ds, ~agree, k, p, q, le, e1, f, as, e2, i, Core.Inline.has(ins, f), Core.Inline.look(ins, f), agree(f), h, ih, ih2)

# Steps
# =====

# A term's step, the pass taken j deep.
def Step.eval(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +e1: List<&2, Core.Val>, t: Core.Tm, +e2: List<&2, Core.Val>, +j: Nat,
    +h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, t}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, t, True{})})):
  match t:
    case Core.CVar{+x}:
      %Sh.var(ins, j, x) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CVar{x}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SLook{e1, x}, Core.SLook{e2, x}, (e2, {==}, h))
    case Core.CLit{+l}:
      %Sh.lit(ins, j, l) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLit{l}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}, {==}, (Core.VLit{l}, {==}, {==}), Unit{})})
    case Core.CRef{+f}:
      %Sh.ref(ins, j, f) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CRef{f}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SCallDef{f, Nil{}}, Core.SCallDef{f, Nil{}}, Inl{(Nil{}, {==}, Unit{})})
    case Core.CCall{+f, +as}:
      L.call(~prim, ~ins, ~ok, ~one, ~ds, ~agree, k, p, 1n+q, le, e1, f, as, e2, j, h, ih, ih2)
    case Core.CApp{+f, +as}:
      %Sh.app(ins, j, f, as) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CApp{f, as}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, f <> as}), Core.KApp{}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Tm.inline(ins, j, f, True{}) <> Core.Tms.inline(ins, j, as)}), Core.KApp{}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Tm.inline(ins, j, f, True{}) <> Core.Tms.inline(ins, j, as)}), Core.KApp{}, {==}, {==},
          ih(q, le, Core.SEvals{e1, f <> as}, Core.SEvals{e2, Core.Tm.inline(ins, j, f, True{}) <> Core.Tms.inline(ins, j, as)}, (e2, j, {==}, h)))})
    case Core.CCtr{+c, +as}:
      %Sh.ctr(ins, j, c, as) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCtr{c, as}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, as}), Core.KCtr{c}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Tms.inline(ins, j, as)}), Core.KCtr{c}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Tms.inline(ins, j, as)}), Core.KCtr{c}, {==}, {==},
          ih(q, le, Core.SEvals{e1, as}, Core.SEvals{e2, Core.Tms.inline(ins, j, as)}, (e2, j, {==}, h)))})
    case Core.CLam{+pt, +b}:
      %Sh.lam(ins, j, pt, b) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLam{pt, b}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e1, pt, b}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, pt, Core.Tm.inline(ins, j, b, True{})}}}, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, pt, Core.Tm.inline(ins, j, b, True{})}}, {==}, (Core.VClo{e2, pt, Core.Tm.inline(ins, j, b, True{})}, {==}, ({==}, j, {==}, h)), Unit{})})
    case Core.CLet{+pt, +v, +b}:
      %Sh.let(ins, j, pt, v, b) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{pt, v, b}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v}), Core.KLet{e1, pt, b}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, v, True{})}), Core.KLet{e2, pt, Core.Tm.inline(ins, j, b, True{})}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, v, True{})}), Core.KLet{e2, pt, Core.Tm.inline(ins, j, b, True{})}, {==}, (e2, j, {==}, h),
          ih(q, le, Core.SEval{e1, v}, Core.SEval{e2, Core.Tm.inline(ins, j, v, True{})}, (e2, j, {==}, h)))})
    case Core.CMat{+scrs, +cs}:
      %Sh.mat(ins, j, scrs, cs) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CMat{scrs, cs}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, scrs}), Core.KMat{e1, cs}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Tms.inline(ins, j, scrs)}), Core.KMat{e2, Core.Tms.inline(ins, j, cs)}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Tms.inline(ins, j, scrs)}), Core.KMat{e2, Core.Tms.inline(ins, j, cs)}, {==}, (e2, j, {==}, h),
          ih(q, le, Core.SEvals{e1, scrs}, Core.SEvals{e2, Core.Tms.inline(ins, j, scrs)}, (e2, j, {==}, h)))})
    case Core.CCse{+ps, +b}:
      %Sh.cse(ins, j, ps, b) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCse{ps, b}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, Inl{(Core.RFail{"a case outside a match"}, Core.KApp{}, {==}, {==}, Unit{})})
    case Core.CSuc{+n, +e}:
      %Sh.suc(ins, j, n, e) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CSuc{n, e}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KSuc{n}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}), Core.KSuc{n}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}), Core.KSuc{n}, {==}, {==},
          ih(q, le, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}, (e2, j, {==}, h)))})
    case Core.COp{+op, +a, +b}:
      %Sh.op(ins, j, op, a, b) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.COp{op, a, b}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, [a, b]}), Core.KOp{op}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, [Core.Tm.inline(ins, j, a, True{}), Core.Tm.inline(ins, j, b, True{})]}), Core.KOp{op}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, [Core.Tm.inline(ins, j, a, True{}), Core.Tm.inline(ins, j, b, True{})]}), Core.KOp{op}, {==}, {==},
          ih(q, le, Core.SEvals{e1, [a, b]}, Core.SEvals{e2, [Core.Tm.inline(ins, j, a, True{}), Core.Tm.inline(ins, j, b, True{})]}, (e2, j, {==}, h)))})
    case Core.CAnn{+e, +ty}:
      %Sh.ann(ins, j, e, ty) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CAnn{e, ty}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}, (e2, j, {==}, h))
    case Core.CTyp{+n, +as}:
      %Sh.typ(ins, j, n, as) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CTyp{n, as}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})})
    case Core.CBox{}:
      %Sh.box(ins, j) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CBox{}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})})
    case Core.CErr{+m}:
      %Sh.err(ins, j, m) : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CErr{m}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, _}))
      ih(q, le, Core.SThen{Core.RFail{m}, Core.KApp{}}, Core.SThen{Core.RFail{m}, Core.KApp{}}, Inl{(Core.RFail{m}, Core.KApp{}, {==}, {==}, Unit{})})

def Step.evals(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +e1: List<&2, Core.Val>, es: List<&2, Core.Tm>, +e2: List<&2, Core.Val>, +j: Nat,
    +h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SEvals{e1, es}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SEvals{e2, Core.Tms.inline(ins, j, es)})):
  match es:
    case Nil{}:
      Unit{}
    case +t <> +r:
      ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, t}), Core.KTail{e1, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, t, True{})}), Core.KTail{e2, Core.Tms.inline(ins, j, r)}},
        Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, t, True{})}), Core.KTail{e2, Core.Tms.inline(ins, j, r)}, {==}, (e2, j, {==}, h),
          ih(q, le, Core.SEval{e1, t}, Core.SEval{e2, Core.Tm.inline(ins, j, t, True{})}, (e2, j, {==}, h)))})

# A call's arguments, where the other program runs them as a call's (bb)
# or as scrutinees.
def Step.args(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), +e1: List<&2, Core.Val>, +e2: List<&2, Core.Val>, +j: Nat, bb: Bool, as: List<&2, Core.Arg>,
    +h: Law.ERel(ins, e1, e2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SArgs{e1, as}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Law.ArgsT(bb, e2, Core.Args.inline(ins, j, as)))):
  match bb:
    case True{}:
      match as:
        case Nil{}:
          Unit{}
        case a <> +r:
          match a:
            case Core.Arg{rl, +e}:
              match rl:
                case Core.Run{}:
                  ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KATail{e1, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}), Core.KATail{e2, Core.Args.inline(ins, j, r)}},
                    Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}), Core.KATail{e2, Core.Args.inline(ins, j, r)}, {==}, (e2, j, True{}, {==}, h),
                      ih(q, le, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}, (e2, j, {==}, h)))})
                case Core.Era{}:
                  ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CBox{}}), Core.KATail{e1, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.CBox{}}), Core.KATail{e2, Core.Args.inline(ins, j, r)}},
                    Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.CBox{}}), Core.KATail{e2, Core.Args.inline(ins, j, r)}, {==}, (e2, j, True{}, {==}, h),
                      ih(q, le, Core.SEval{e1, Core.CBox{}}, Core.SEval{e2, Core.CBox{}}, (e2, 0n, {==}, h)))})
    case False{}:
      match as:
        case Nil{}:
          Unit{}
        case a <> +r:
          match a:
            case Core.Arg{rl, +e}:
              match rl:
                case Core.Run{}:
                  ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KATail{e1, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}), Core.KTail{e2, Core.Args.scrs(Core.Args.inline(ins, j, r))}},
                    Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}), Core.KTail{e2, Core.Args.scrs(Core.Args.inline(ins, j, r))}, {==}, (e2, j, False{}, {==}, h),
                      ih(q, le, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.inline(ins, j, e, True{})}, (e2, j, {==}, h)))})
                case Core.Era{}:
                  ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CBox{}}), Core.KATail{e1, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.CBox{}}), Core.KTail{e2, Core.Args.scrs(Core.Args.inline(ins, j, r))}},
                    Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{e2, Core.CBox{}}), Core.KTail{e2, Core.Args.scrs(Core.Args.inline(ins, j, r))}, {==}, (e2, j, False{}, {==}, h),
                      ih(q, le, Core.SEval{e1, Core.CBox{}}, Core.SEval{e2, Core.CBox{}}, (e2, 0n, {==}, h)))})

def Step.then(~prim: String -> List<&2, Core.Val> -> Core.Res, ~ins: Map<&2, Core.Def>, ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(ins, vs1, vs2) -> Law.PRel(ins, prim(op, vs1), prim(op, vs2)), ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), ~ds: List<&2, Core.Def>, ~agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Law.Def.name(Core.Inline.look(ins, f)), f)) -> Law.Found(ds, f, Law.Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f))), +k: Nat, +p: Nat, +q: Nat, +le: Red.Le(p, q), r1: Core.Res, r2: Core.Res, +rr: Law.RRel(ins, r1, r2), k1: Core.Kont, +k2: Core.Kont,
    kr: Law.KRel(ins, k1, k2), ih: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)), ih2: @m2:Nat -> Red.Le(p, m2) -> @t1:Core.Sel -> @t2:Core.Sel -> Law.SRel(ins, ds, m2, t1, t2) -> Law.RRel(ins, Core.run(~prim, p, ds, t1), Core.run(~prim, m2, Core.Defs.inline(ins, k, ds), t2)))
    -> Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{r1, k1}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SThen{r2, k2})):
  match r1:
    case Core.ROk{+vs1}:
      match r2:
        case Core.ROk{+vs2}:
          ih(q, le, Core.SOk{k1, vs1}, Core.SOk{k2, vs2}, Inl{(k2, vs2, {==}, kr, rr)})
        case Core.REnv{+env2}:
          match rr:
        case Core.RNo{}:
          match rr:
        case Core.RFail{+m2}:
          match rr:
    case Core.REnv{+env1}:
      match r2:
        case Core.ROk{+vs2}:
          match rr:
        case Core.REnv{+env2}:
          match k1:
            case Core.KCall{+fa}:
              Unit{}
            case Core.KApp{}:
              Unit{}
            case Core.KCtr{+ka}:
              Unit{}
            case Core.KLet{+enva, +pa, +ba}:
              Unit{}
            case Core.KBind{+ba}:
              match kr:
                case (+j, eq):
                  %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KBind{ba}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SThen{Core.REnv{env2}, _}))
                  ih(q, le, Core.SEval{env1, ba}, Core.SEval{env2, Core.Tm.inline(ins, j, ba, True{})}, (env2, j, {==}, rr))
            case Core.KMat{+enva, +casesa}:
              Unit{}
            case Core.KCase{+enva, +vsa, +ba, +resta}:
              match kr:
                case (+e2, +vs2, +j, eq, +vr, +h):
                  %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KCase{enva, vsa, ba, resta}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SThen{Core.REnv{env2}, _}))
                  ih(q, le, Core.SEval{env1, ba}, Core.SEval{env2, Core.Tm.inline(ins, j, ba, True{})}, (env2, j, {==}, rr))
            case Core.KSuc{+ka}:
              Unit{}
            case Core.KOp{+opa}:
              Unit{}
            case Core.KTail{+enva, +esa}:
              Unit{}
            case Core.KATail{+enva, +asa}:
              Unit{}
            case Core.KCons{+va}:
              Unit{}
            case Core.KApply{+vsa}:
              Unit{}
            case Core.KBody{+ba, +resta}:
              match kr:
                case (+j, +rest2, eq, +vr):
                  %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env1}, Core.KBody{ba, resta}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SThen{Core.REnv{env2}, _}))
                  ih2(q, le, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env1, ba}), Core.KApply{resta}}, Core.SThen{Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{env2, Core.Tm.inline(ins, j, ba, True{})}), Core.KApply{rest2}},
                    Inl{(Core.run(~prim, q, Core.Defs.inline(ins, k, ds), Core.SEval{env2, Core.Tm.inline(ins, j, ba, True{})}), Core.KApply{rest2}, {==}, (rest2, {==}, vr),
                      ih(q, le, Core.SEval{env1, ba}, Core.SEval{env2, Core.Tm.inline(ins, j, ba, True{})}, (env2, j, {==}, rr)))})
        case Core.RNo{}:
          match rr:
        case Core.RFail{+m2}:
          match rr:
    case Core.RNo{}:
      match r2:
        case Core.ROk{+vs2}:
          match rr:
        case Core.REnv{+env2}:
          match rr:
        case Core.RNo{}:
          match k1:
            case Core.KCall{+fa}:
              Unit{}
            case Core.KApp{}:
              Unit{}
            case Core.KCtr{+ka}:
              Unit{}
            case Core.KLet{+enva, +pa, +ba}:
              Unit{}
            case Core.KBind{+ba}:
              Unit{}
            case Core.KMat{+enva, +casesa}:
              Unit{}
            case Core.KCase{+enva, +vsa, +ba, +resta}:
              match kr:
                case (+e2, +vs2, +j, eq, +vr, +h):
                  %eq : Law.RRel(ins, Core.run(~prim, 1n+p, ds, Core.SThen{Core.RNo{}, Core.KCase{enva, vsa, ba, resta}}), Core.run(~prim, 1n+q, Core.Defs.inline(ins, k, ds), Core.SThen{Core.RNo{}, _}))
                  ih(q, le, Core.SMatch{enva, vsa, resta}, Core.SMatch{e2, vs2, Core.Tms.inline(ins, j, resta)}, (e2, vs2, j, {==}, vr, h))
            case Core.KSuc{+ka}:
              Unit{}
            case Core.KOp{+opa}:
              Unit{}
            case Core.KTail{+enva, +esa}:
              Unit{}
            case Core.KATail{+enva, +asa}:
              Unit{}
            case Core.KCons{+va}:
              Unit{}
            case Core.KApply{+vsa}:
              Unit{}
            case Core.KBody{+ba, +resta}:
              Unit{}
        case Core.RFail{+m2}:
          match rr:
    case Core.RFail{+m1}:
      Unit{}

