import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./DEAD.bend as Dead

# The law that core.bend's inlining pass (Tm.inline) preserves `run`, and
# the words it is stated in. INLINEPROOF.bend proves it.
#
# The pass puts a def's body in the place of a call of it, in a match on
# the call's arguments with one case, a variable for each parameter. The
# body then runs in the caller's scope with the parameters bound in front,
# where the call ran it in a scope of the parameters alone: a scope of the
# other program has the source's bindings first, then more (ERel), which no
# lookup of a source that does not fail reaches. Its terms are the source's
# with the pass taken, to some depth j (the pass goes k deep, and a body it
# puts in place one less).

# The def's name and parameters.
def Def.name(d: Core.Def) -> String:
  match d:
    case Core.Def{n, ps, b, ret}:
      n

def Def.pars(d: Core.Def) -> List<&2, Core.Par>:
  match d:
    case Core.Def{n, ps, b, ret}:
      ps

# Values and scopes
# =================

# v2 is v1 with its terms' calls inlined, a closure's scope with more
# bindings after the source's.
def VRel(-ins: Map<&2, Core.Def>, v1: Core.Val, v2: Core.Val) -> Data:
  match v1:
    case Core.VLit{l1}:
      match v2:
        case Core.VLit{l2}:
          {l1 == l2 : Core.Lit}
        case Core.VCtr{k9, fs9}:
          Empty
        case Core.VClo{env9, p9, b9}:
          Empty
        case Core.VFun{f9, as9}:
          Empty
        case Core.VTrm{t9}:
          Empty
        case Core.VBnd{x9, w9}:
          Empty
    case Core.VCtr{k1, fs1}:
      match v2:
        case Core.VLit{l9}:
          Empty
        case Core.VCtr{k2, fs2}:
          Sigma<&2, &2, {k1 == k2 : String}, _ => VRels(ins, fs1, fs2)>
        case Core.VClo{env9, p9, b9}:
          Empty
        case Core.VFun{f9, as9}:
          Empty
        case Core.VTrm{t9}:
          Empty
        case Core.VBnd{x9, w9}:
          Empty
    case Core.VClo{e1, p1, b1}:
      match v2:
        case Core.VLit{l9}:
          Empty
        case Core.VCtr{k9, fs9}:
          Empty
        case Core.VClo{e2, p2, b2}:
          Sigma<&2, &2, {p1 == p2 : Core.Pt}, _ => Sigma<&2, &2, Nat, j =>
            Sigma<&2, &2, {Core.Tm.inline(ins, j, b1, True{}) == b2 : Core.Tm}, _ => ERel(ins, e1, e2)>>>
        case Core.VFun{f9, as9}:
          Empty
        case Core.VTrm{t9}:
          Empty
        case Core.VBnd{x9, w9}:
          Empty
    case Core.VFun{f1, as1}:
      match v2:
        case Core.VLit{l9}:
          Empty
        case Core.VCtr{k9, fs9}:
          Empty
        case Core.VClo{env9, p9, b9}:
          Empty
        case Core.VFun{f2, as2}:
          Sigma<&2, &2, {f1 == f2 : String}, _ => VRels(ins, as1, as2)>
        case Core.VTrm{t9}:
          Empty
        case Core.VBnd{x9, w9}:
          Empty
    case Core.VTrm{t1}:
      match v2:
        case Core.VLit{l9}:
          Empty
        case Core.VCtr{k9, fs9}:
          Empty
        case Core.VClo{env9, p9, b9}:
          Empty
        case Core.VFun{f9, as9}:
          Empty
        case Core.VTrm{t2}:
          {t1 == t2 : Core.Tm}
        case Core.VBnd{x9, w9}:
          Empty
    case Core.VBnd{x1, w1}:
      match v2:
        case Core.VLit{l9}:
          Empty
        case Core.VCtr{k9, fs9}:
          Empty
        case Core.VClo{env9, p9, b9}:
          Empty
        case Core.VFun{f9, as9}:
          Empty
        case Core.VTrm{t9}:
          Empty
        case Core.VBnd{x2, w2}:
          Sigma<&2, &2, {x1 == x2 : String}, _ => VRel(ins, w1, w2)>

def VRels(-ins: Map<&2, Core.Def>, vs1: List<&2, Core.Val>, vs2: List<&2, Core.Val>) -> Data:
  match vs1:
    case Nil{}:
      match vs2:
        case Nil{}:
          Unit
        case w <> s:
          Empty
    case v <> r:
      match vs2:
        case Nil{}:
          Empty
        case w <> s:
          Sigma<&2, &2, VRel(ins, v, w), _ => VRels(ins, r, s)>

# e2 has e1's bindings, related, then any others.
def ERel(-ins: Map<&2, Core.Def>, e1: List<&2, Core.Val>, e2: List<&2, Core.Val>) -> Data:
  match e1:
    case Nil{}:
      Unit
    case v <> r:
      match e2:
        case Nil{}:
          Empty
        case w <> s:
          Sigma<&2, &2, VRel(ins, v, w), _ => ERel(ins, r, s)>

# Results
# =======

# r2 is r1 with its values related. A failure is related to any result: the
# law says nothing of a run that fails (the source may fail a lookup the
# other program's larger scope answers).
def RRel(-ins: Map<&2, Core.Def>, r1: Core.Res, r2: Core.Res) -> Data:
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          VRels(ins, vs1, vs2)
        case Core.REnv{e}:
          Empty
        case Core.RNo{}:
          Empty
        case Core.RFail{m}:
          Empty
    case Core.REnv{e1}:
      match r2:
        case Core.REnv{e2}:
          ERel(ins, e1, e2)
        case Core.ROk{vs}:
          Empty
        case Core.RNo{}:
          Empty
        case Core.RFail{m}:
          Empty
    case Core.RNo{}:
      match r2:
        case Core.RNo{}:
          Unit
        case Core.ROk{vs}:
          Empty
        case Core.REnv{e}:
          Empty
        case Core.RFail{m}:
          Empty
    case Core.RFail{m}:
      Unit

# What the natives must do: give related values for related values, or fail.
def PRel(-ins: Map<&2, Core.Def>, r1: Core.Res, r2: Core.Res) -> Data:
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          VRels(ins, vs1, vs2)
        case Core.REnv{e}:
          Empty
        case Core.RNo{}:
          Empty
        case Core.RFail{m}:
          Empty
    case Core.REnv{e1}:
      Empty
    case Core.RNo{}:
      Empty
    case Core.RFail{m}:
      Unit

# Defs
# ====

# The first def of ds named f has the parameters ps and the body b.
def Found(ds: List<&2, Core.Def>, +f: String, ps: List<&2, Core.Par>, b: Core.Tm) -> Data:
  match ds:
    case Nil{}:
      Empty
    case d <> r:
      match d:
        case Core.Def{+name, ps2, b2, ret}:
          Either<&2, &2,
            Sigma<&2, &2, {True{} == String.eq(name, f) : Bool}, _ => Sigma<&2, &2, {ps == ps2 : List<&2, Core.Par>}, _ => {b == b2 : Core.Tm}>>,
            Sigma<&2, &2, {False{} == String.eq(name, f) : Bool}, _ => Found(r, f, ps, b)>>

# The same, past a def of the parameters ps2 and the body b2 (h: whether it
# is named f).
def Found.at(h: Bool, ps2: List<&2, Core.Par>, b2: Core.Tm, r: List<&2, Core.Def>, +f: String, ps: List<&2, Core.Par>, b: Core.Tm) -> Data:
  Either<&2, &2,
    Sigma<&2, &2, {True{} == h : Bool}, _ => Sigma<&2, &2, {ps == ps2 : List<&2, Core.Par>}, _ => {b == b2 : Core.Tm}>>,
    Sigma<&2, &2, {False{} == h : Bool}, _ => Found(r, f, ps, b)>>

# States
# ======

# A call's arguments where the other program runs them: as a call's (b),
# or as an inlined call's match's scrutinees.
def ArgsT(b: Bool, e2: List<&2, Core.Val>, as2: List<&2, Core.Arg>) -> Core.Sel:
  match b:
    case True{}:
      Core.SArgs{e2, as2}
    case False{}:
      Core.SEvals{e2, Core.Args.scrs(as2)}

def KArgsT(b: Bool, e2: List<&2, Core.Val>, as2: List<&2, Core.Arg>) -> Core.Kont:
  match b:
    case True{}:
      Core.KATail{e2, as2}
    case False{}:
      Core.KTail{e2, Core.Args.scrs(as2)}

# k2 is k1 with its terms' calls inlined, and its scope and values related.
def KRel(-ins: Map<&2, Core.Def>, k1: Core.Kont, k2: Core.Kont) -> Data:
  match k1:
    case Core.KCall{f}:
      {Core.KCall{f} == k2 : Core.Kont}
    case Core.KApp{}:
      {Core.KApp{} == k2 : Core.Kont}
    case Core.KCtr{c}:
      {Core.KCtr{c} == k2 : Core.Kont}
    case Core.KLet{e1, p, b}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, {Core.KLet{e2, p, Core.Tm.inline(ins, j, b, True{})} == k2 : Core.Kont}, _ => ERel(ins, e1, e2)>>>
    case Core.KBind{b}:
      Sigma<&2, &2, Nat, j => {Core.KBind{Core.Tm.inline(ins, j, b, True{})} == k2 : Core.Kont}>
    case Core.KMat{e1, cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, {Core.KMat{e2, Core.Tms.inline(ins, j, cs)} == k2 : Core.Kont}, _ => ERel(ins, e1, e2)>>>
    case Core.KCase{e1, vs, b, r}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, {Core.KCase{e2, vs2, Core.Tm.inline(ins, j, b, True{}), Core.Tms.inline(ins, j, r)} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(ins, vs, vs2), _ => ERel(ins, e1, e2)>>>>>
    case Core.KSuc{c}:
      {Core.KSuc{c} == k2 : Core.Kont}
    case Core.KOp{op}:
      {Core.KOp{op} == k2 : Core.Kont}
    case Core.KTail{e1, es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, {Core.KTail{e2, Core.Tms.inline(ins, j, es)} == k2 : Core.Kont}, _ => ERel(ins, e1, e2)>>>
    case Core.KATail{e1, as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Nat, j => Sigma<&2, &2, Bool, b =>
        Sigma<&2, &2, {KArgsT(b, e2, Core.Args.inline(ins, j, as)) == k2 : Core.Kont}, _ => ERel(ins, e1, e2)>>>>
    case Core.KCons{v}:
      Sigma<&2, &2, Core.Val, v2 => Sigma<&2, &2, {Core.KCons{v2} == k2 : Core.Kont}, _ => VRel(ins, v, v2)>>
    case Core.KApply{vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.KApply{vs2} == k2 : Core.Kont}, _ => VRels(ins, vs, vs2)>>
    case Core.KBody{b, r}:
      Sigma<&2, &2, Nat, j => Sigma<&2, &2, List<&2, Core.Val>, r2 =>
        Sigma<&2, &2, {Core.KBody{Core.Tm.inline(ins, j, b, True{}), r2} == k2 : Core.Kont}, _ => VRels(ins, r, r2)>>>

# An inlined call's steps
# -----------------------
#
# The source runs the arguments, then calls f: it finds f's def, the
# parameters ps and the body b, and runs b in a scope of the parameters.
# The other program runs the arguments as the match's scrutinees, then
# matches them (a variable for each parameter), and runs b with the pass
# taken in that scope in front of its own, while the source still looks for
# f's def. Its match binds the parameters in L+1 steps (L parameters), where
# the source's call binds them in one: the fuel it has left is that or more
# (the arguments' run took more), or so little the source runs out.

# m >= L+n, or m <= n (n = 4, 3, 2: the steps to the match's patterns).
def Room4(L: Nat, m: Nat) -> Data:
  Either<&2, &2, Red.Le(1n+1n+1n+1n+L, m), Red.Le(m, 1n+1n+1n+1n+0n)>

def Room3(L: Nat, m: Nat) -> Data:
  Either<&2, &2, Red.Le(1n+1n+1n+L, m), Red.Le(m, 1n+1n+1n+0n)>

def Room2(L: Nat, m: Nat) -> Data:
  Either<&2, &2, Red.Le(1n+1n+L, m), Red.Le(m, 1n+1n+0n)>

# The arguments' results: the values, one for each parameter, related.
def CallR(-ins: Map<&2, Core.Def>, r1: Core.Res, r2: Core.Res, L: Nat, m: Nat) -> Data:
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          Sigma<&2, &2, VRels(ins, vs1, vs2), _ => Sigma<&2, &2, Red.Len(vs2, L), _ => Room4(L, m)>>
        case Core.REnv{e}:
          Empty
        case Core.RNo{}:
          Empty
        case Core.RFail{m9}:
          Empty
    case Core.REnv{e1}:
      Unit
    case Core.RNo{}:
      Unit
    case Core.RFail{m9}:
      Unit

# The match an inlined call of a def with the parameters ps and body b is.
def Cases(ins: Map<&2, Core.Def>, ps: List<&2, Core.Par>, j: Nat, b: Core.Tm) -> List<&2, Core.Tm>:
  [Core.CCse{Core.Pars.vars(ps), Core.Tm.inline(ins, j, b, True{})}]

# The arguments' run and the call.
def Call.then(-ins: Map<&2, Core.Def>, ds: List<&2, Core.Def>, m: Nat, r1: Core.Res, k1: Core.Kont, s2: Core.Sel) -> Data:
  match k1:
    case Core.KCall{f}:
      Sigma<&2, &2, List<&2, Core.Par>, ps => Sigma<&2, &2, Core.Tm, b => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Core.Res, r2 =>
        Sigma<&2, &2, {Core.SThen{r2, Core.KMat{e2, Cases(ins, ps, j, b)}} == s2 : Core.Sel},
        _ => Sigma<&2, &2, Found(ds, f, ps, b), _ => CallR(ins, r1, r2, Core.Pars.len(ps), m)>>>>>>>
    case Core.KApp{}:
      Empty
    case Core.KCtr{c}:
      Empty
    case Core.KLet{e1, p, b}:
      Empty
    case Core.KBind{b}:
      Empty
    case Core.KMat{e1, cs}:
      Empty
    case Core.KCase{e1, vs, b, r}:
      Empty
    case Core.KSuc{c}:
      Empty
    case Core.KOp{op}:
      Empty
    case Core.KTail{e1, es}:
      Empty
    case Core.KATail{e1, as}:
      Empty
    case Core.KCons{v}:
      Empty
    case Core.KApply{vs}:
      Empty
    case Core.KBody{b, r}:
      Empty

# The arguments' values, the call due.
def Call.ok(-ins: Map<&2, Core.Def>, ds: List<&2, Core.Def>, m: Nat, k1: Core.Kont, vs1: List<&2, Core.Val>, s2: Core.Sel) -> Data:
  match k1:
    case Core.KCall{f}:
      Sigma<&2, &2, List<&2, Core.Par>, ps => Sigma<&2, &2, Core.Tm, b => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 =>
        Sigma<&2, &2, {Core.SOk{Core.KMat{e2, Cases(ins, ps, j, b)}, vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, Found(ds, f, ps, b), _ => Sigma<&2, &2, VRels(ins, vs1, vs2),
        _ => Sigma<&2, &2, Red.Len(vs2, Core.Pars.len(ps)), _ => Room3(Core.Pars.len(ps), m)>>>>>>>>>
    case Core.KApp{}:
      Empty
    case Core.KCtr{c}:
      Empty
    case Core.KLet{e1, p, b}:
      Empty
    case Core.KBind{b}:
      Empty
    case Core.KMat{e1, cs}:
      Empty
    case Core.KCase{e1, vs, b, r}:
      Empty
    case Core.KSuc{c}:
      Empty
    case Core.KOp{op}:
      Empty
    case Core.KTail{e1, es}:
      Empty
    case Core.KATail{e1, as}:
      Empty
    case Core.KCons{v}:
      Empty
    case Core.KApply{vs}:
      Empty
    case Core.KBody{b, r}:
      Empty

# The call: the other program at its match.
def Call.def(-ins: Map<&2, Core.Def>, ds: List<&2, Core.Def>, m: Nat, f: String, vs1: List<&2, Core.Val>, s2: Core.Sel) -> Data:
  Sigma<&2, &2, List<&2, Core.Par>, ps => Sigma<&2, &2, Core.Tm, b => Sigma<&2, &2, Nat, j =>
    Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 =>
    Sigma<&2, &2, {Core.SMatch{e2, vs2, Cases(ins, ps, j, b)} == s2 : Core.Sel},
    _ => Sigma<&2, &2, Found(ds, f, ps, b), _ => Sigma<&2, &2, VRels(ins, vs1, vs2),
    _ => Sigma<&2, &2, Red.Len(vs2, Core.Pars.len(ps)), _ => Room2(Core.Pars.len(ps), m)>>>>>>>>>

# The other program at the body, the parameters bound in front of its
# scope; the source looking for f's def in ds.
def Call.at(-ins: Map<&2, Core.Def>, ps: List<&2, Core.Par>, b: Core.Tm, vs1: List<&2, Core.Val>, s2: Core.Sel) -> Data:
  Sigma<&2, &2, Nat, j => Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 =>
    Sigma<&2, &2, {Core.SThen{Core.REnv{Core.Scope.push(ps, vs2, e2)}, Core.KCase{e2, vs2, Core.Tm.inline(ins, j, b, True{}), Nil{}}} == s2 : Core.Sel},
    _ => Sigma<&2, &2, VRels(ins, vs1, vs2), _ => Red.Len(vs2, Core.Pars.len(ps))>>>>>

def Call.find(-ins: Map<&2, Core.Def>, ds: List<&2, Core.Def>, f: String, vs1: List<&2, Core.Val>, s2: Core.Sel) -> Data:
  Sigma<&2, &2, List<&2, Core.Par>, ps => Sigma<&2, &2, Core.Tm, b =>
    Sigma<&2, &2, Found(ds, f, ps, b), _ => Call.at(ins, ps, b, vs1, s2)>>>

def Call.found(-ins: Map<&2, Core.Def>, h: Bool, ps2: List<&2, Core.Par>, b2: Core.Tm, ds: List<&2, Core.Def>, f: String,
    vs1: List<&2, Core.Val>, s2: Core.Sel) -> Data:
  Sigma<&2, &2, List<&2, Core.Par>, ps => Sigma<&2, &2, Core.Tm, b =>
    Sigma<&2, &2, Found.at(h, ps2, b2, ds, f, ps, b), _ => Call.at(ins, ps, b, vs1, s2)>>>

# Found: the call has an argument for each parameter.
def Call.enter(-ins: Map<&2, Core.Def>, sh: Bool, ps: List<&2, Core.Par>, b: Core.Tm, vs1: List<&2, Core.Val>, s2: Core.Sel) -> Data:
  Sigma<&2, &2, Dead.Fls(sh), _ => Call.at(ins, ps, b, vs1, s2)>

# s2 is s1 in the program the pass took, or s1 is at an inlined call's
# steps and s2 at the match's (m: the other program's fuel).
def SRel(-ins: Map<&2, Core.Def>, ds: List<&2, Core.Def>, m: Nat, s1: Core.Sel, s2: Core.Sel) -> Data:
  match s1:
    case Core.SEval{e1, t}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, {Core.SEval{e2, Core.Tm.inline(ins, j, t, True{})} == s2 : Core.Sel}, _ => ERel(ins, e1, e2)>>>
    case Core.SEvals{e1, es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, {Core.SEvals{e2, Core.Tms.inline(ins, j, es)} == s2 : Core.Sel}, _ => ERel(ins, e1, e2)>>>
    case Core.SArgs{e1, as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Nat, j => Sigma<&2, &2, Bool, b =>
        Sigma<&2, &2, {ArgsT(b, e2, Core.Args.inline(ins, j, as)) == s2 : Core.Sel}, _ => ERel(ins, e1, e2)>>>>
    case Core.SThen{r1, k1}:
      Either<&2, &2,
        Sigma<&2, &2, Core.Res, r2 => Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, {Core.SThen{r2, k2} == s2 : Core.Sel},
          _ => Sigma<&2, &2, KRel(ins, k1, k2), _ => RRel(ins, r1, r2)>>>>,
        Call.then(ins, ds, m, r1, k1, s2)>
    case Core.SOk{k1, vs}:
      Either<&2, &2,
        Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SOk{k2, vs2} == s2 : Core.Sel},
          _ => Sigma<&2, &2, KRel(ins, k1, k2), _ => VRels(ins, vs, vs2)>>>>,
        Call.ok(ins, ds, m, k1, vs, s2)>
    case Core.SLook{e1, x}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SLook{e2, x} == s2 : Core.Sel}, _ => ERel(ins, e1, e2)>>
    case Core.SLook2{h, v, e1, x}:
      Sigma<&2, &2, Core.Val, v2 => Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SLook2{h, v2, e2, x} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRel(ins, v, v2), _ => ERel(ins, e1, e2)>>>>
    case Core.SCallDef{f, vs}:
      Either<&2, &2,
        Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SCallDef{f, vs2} == s2 : Core.Sel}, _ => VRels(ins, vs, vs2)>>,
        Call.def(ins, ds, m, f, vs, s2)>
    case Core.SFind{ds1, f, vs}:
      Either<&2, &2,
        Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Nat, j =>
          Sigma<&2, &2, {Core.SFind{Core.Defs.inline(ins, j, ds1), f, vs2} == s2 : Core.Sel}, _ => VRels(ins, vs, vs2)>>>,
        Call.find(ins, ds1, f, vs, s2)>
    case Core.SFound{h, ps, b, ds1, f, vs}:
      Either<&2, &2,
        Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Nat, j =>
          Sigma<&2, &2, {Core.SFound{h, ps, Core.Tm.inline(ins, j, b, True{}), Core.Defs.inline(ins, j, ds1), f, vs2} == s2 : Core.Sel},
          _ => VRels(ins, vs, vs2)>>>,
        Call.found(ins, h, ps, b, ds1, f, vs, s2)>
    case Core.SEnter{sh, f, ps, b, vs}:
      Either<&2, &2,
        Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Nat, j =>
          Sigma<&2, &2, {Core.SEnter{sh, f, ps, Core.Tm.inline(ins, j, b, True{}), vs2} == s2 : Core.Sel}, _ => VRels(ins, vs, vs2)>>>,
        Call.enter(ins, sh, ps, b, vs, s2)>
    case Core.SApply{vs, fv}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Core.Val, fv2 => Sigma<&2, &2, {Core.SApply{vs2, fv2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(ins, vs, vs2), _ => VRel(ins, fv, fv2)>>>>
    case Core.SMatch{e1, vs, cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Nat, j =>
        Sigma<&2, &2, {Core.SMatch{e2, vs2, Core.Tms.inline(ins, j, cs)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(ins, vs, vs2), _ => ERel(ins, e1, e2)>>>>>
    case Core.SPat{e1, ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SPat{e2, ps, vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(ins, vs, vs2), _ => ERel(ins, e1, e2)>>>>
    case Core.SPatC{h, e1, ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SPatC{h, e2, ps, vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(ins, vs, vs2), _ => ERel(ins, e1, e2)>>>>

# The laws
# ========

# From related states, with as much fuel or more, the program the pass took
# gives a related result, if the defs ins holds are those of ds (agree: the
# first def of ds named f is the one ins holds for f, when it holds one
# named f)
# and the natives give related values for related values, one or a failure.
law inline_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ins: Map<&2, Core.Def>
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(ins, vs1, vs2) -> PRel(ins, prim(op, vs1), prim(op, vs2))
  for one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n})
  for k: Nat
  for ds: List<&2, Core.Def>
  for agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Def.name(Core.Inline.look(ins, f)), f)) ->
    Found(ds, f, Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f)))
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for s1: Core.Sel
  for s2: Core.Sel
  for rel: SRel(ins, ds, m, s1, s2)
  RRel(ins, Core.run(~prim, n, ds, s1), Core.run(~prim, m, Core.Defs.inline(ins, k, ds), s2))

# A program's result, if it is values without closures (or no match): the
# program the pass took gives the same.
law inline_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ins: Map<&2, Core.Def>
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(ins, vs1, vs2) -> PRel(ins, prim(op, vs1), prim(op, vs2))
  for one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n})
  for k: Nat
  for ds: List<&2, Core.Def>
  for agree: @f:String -> Dead.Tru(Core.Inline.has(ins, f)) -> Dead.Tru(String.eq(Def.name(Core.Inline.look(ins, f)), f)) ->
    Found(ds, f, Def.pars(Core.Inline.look(ins, f)), Core.Inline.body(Core.Inline.look(ins, f)))
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for nf: Dead.Clean(Core.Prog.run(~prim, n, ds))
  {Core.Prog.run(~prim, n, ds) == Core.Prog.run(~prim, m, Core.Defs.inline(ins, k, ds)) : Core.Res}
