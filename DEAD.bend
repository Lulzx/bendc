import Base
import ./RED.bend as Red
import ./core.bend as Core

# The law that core.bend's dead-let pass (Tm.dead) preserves `run`, and the
# words it is stated in. DEADPROOF.bend proves it.
#
# The pass drops a let's binding, so the program without its dead lets runs
# in scopes with fewer bindings: its states are related to the source's, not
# a function of them. A scope's relation (ERel) says which bindings may be
# missing: those no lookup of what runs in the scope reaches. U stands for
# those lookups (Lk(t): the lookups of t) and hs holds the names bound after
# the scope's first binding, which a lookup passes before it reaches it: a
# binding of z may be missing if U(hs, z) is False. A binding a match is yet
# to make is in hs too (the patterns' names).

# The lookups of t: whether one reaches a binding of x, past the names h.
def Lk(t: Core.Tm) -> List<&2, String> -> String -> Bool:
  h => x => Core.Dead.used(t, h, x)

def Tru(b: Bool) -> Data:
  match b:
    case True{}:
      Unit
    case False{}:
      Empty

def Fls(b: Bool) -> Data:
  match b:
    case True{}:
      Empty
    case False{}:
      Unit

# Values and scopes
# =================

# v2 is v1 with its terms' dead lets dropped, and the bindings no lookup of
# a closure's body reaches missing from the closure's scope.
def VRel(v1: Core.Val, v2: Core.Val) -> Data:
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
          Sigma<&2, &2, {k1 == k2 : String}, _ => VRels(fs1, fs2)>
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
          Sigma<&2, &2, {p1 == p2 : Core.Pt}, _ => Sigma<&2, &2, {Core.Tm.dead(b1) == b2 : Core.Tm},
            _ => ERel(e1, Lk(Core.CLam{p1, Core.Tm.dead(b1)}), Nil{}, e2)>>
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
          Sigma<&2, &2, {f1 == f2 : String}, _ => VRels(as1, as2)>
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
          {Core.Tm.dead(t1) == t2 : Core.Tm}
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
          Sigma<&2, &2, {x1 == x2 : String}, _ => VRel(w1, w2)>

def VRels(vs1: List<&2, Core.Val>, vs2: List<&2, Core.Val>) -> Data:
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
          Sigma<&2, &2, VRel(v, w), _ => VRels(r, s)>

# e2 is e1 with some bindings missing that no lookup U stands for reaches
# (past hs), and the others related.
def ERel(e1: List<&2, Core.Val>, -U: List<&2, String> -> String -> Bool, +hs: List<&2, String>, e2: List<&2, Core.Val>) -> Data:
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit
        case y <> r2:
          Empty
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              Sigma<&2, &2, Fls(U(hs, z)), _ => ERel(r1, U, hs, Nil{})>
            case +y <> +r2:
              Either<&2, &2,
                Sigma<&2, &2, Fls(U(hs, z)), _ => ERel(r1, U, hs, y <> r2)>,
                Sigma<&2, &2, VRel(Core.VBnd{z, w}, y), _ => ERel(r1, U, z <> hs, r2)>>
        case other:
          match e2:
            case Nil{}:
              Empty
            case y <> r2:
              Sigma<&2, &2, VRel(other, y), _ => ERel(r1, U, hs, r2)>

# Results
# =======

# r2 is r1 with its values related, a scope's with U for its lookups. A
# failure is related to any result: the law says nothing of a run that
# fails (the source may fail in a let the other program does not run).
def RRel(r1: Core.Res, -U: List<&2, String> -> String -> Bool, r2: Core.Res) -> Data:
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          VRels(vs1, vs2)
        case Core.REnv{e}:
          Empty
        case Core.RNo{}:
          Empty
        case Core.RFail{m}:
          Empty
    case Core.REnv{e1}:
      match r2:
        case Core.REnv{e2}:
          ERel(e1, U, Nil{}, e2)
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
def PRel(r1: Core.Res, r2: Core.Res) -> Data:
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          VRels(vs1, vs2)
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

# That a value holds no closure (a related one is then the value with the
# pass taken).
def NoClos(vs: List<&2, Core.Val>) -> Data:
  match vs:
    case Nil{}:
      Unit
    case v <> r:
      Sigma<&2, &2, NoClo(v), _ => NoClos(r)>

def NoClo(v: Core.Val) -> Data:
  match v:
    case Core.VLit{l}:
      Unit
    case Core.VCtr{k, fs}:
      NoClos(fs)
    case Core.VClo{env, p, b}:
      Empty
    case Core.VFun{f, as}:
      NoClos(as)
    case Core.VTrm{t}:
      Unit
    case Core.VBnd{x, w}:
      NoClo(w)

# That a result is values without closures, or no match: not a failure.
def Clean(r: Core.Res) -> Data:
  match r:
    case Core.ROk{vs}:
      NoClos(vs)
    case Core.RNo{}:
      Unit
    case Core.REnv{env}:
      Empty
    case Core.RFail{m}:
      Empty

# States
# ======

# The node a list of terms being evaluated is the rest of: a match's
# scrutinees (WMat), an application's arguments (WApp), a constructor's or
# an operator's (WCtr), or an application's function and arguments (WHead).
type Wrap is Data:
  WMat{cs: List<&2, Core.Tm>}
  WApp{f: Core.Tm}
  WCtr{k: String}
  WHead{}

def Wrap.tm(w: Wrap, es: List<&2, Core.Tm>) -> Core.Tm:
  match w:
    case WMat{cs}:
      Core.CMat{es, cs}
    case WApp{f}:
      Core.CApp{f, es}
    case WCtr{k}:
      Core.CCtr{k, es}
    case WHead{}:
      match es:
        case Nil{}:
          Core.CBox{}
        case f <> r:
          Core.CApp{f, r}

# The lookups of what runs in the scope a continuation gets.
def Kont.U(k: Core.Kont) -> List<&2, String> -> String -> Bool:
  match k:
    case Core.KBind{b}:
      Lk(Core.Tm.dead(b))
    case Core.KCase{env, vs, b, rest}:
      Lk(Core.Tm.dead(b))
    case Core.KBody{b, rest}:
      Lk(Core.Tm.dead(b))
    case other:
      Lk(Core.CBox{})

# k2 is k1 with its terms' dead lets dropped, and its scope and values
# related (a scope with the lookups of what k1 runs in it).
def KRel(k1: Core.Kont, k2: Core.Kont) -> Data:
  match k1:
    case Core.KCall{f}:
      {Core.KCall{f} == k2 : Core.Kont}
    case Core.KApp{}:
      {Core.KApp{} == k2 : Core.Kont}
    case Core.KCtr{c}:
      {Core.KCtr{c} == k2 : Core.Kont}
    case Core.KLet{e1, +p, +b}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.KLet{e2, p, Core.Tm.dead(b)} == k2 : Core.Kont},
        _ => ERel(e1, Lk(Core.CCse{[p], Core.Tm.dead(b)}), Nil{}, e2)>>
    case Core.KBind{b}:
      {Core.KBind{Core.Tm.dead(b)} == k2 : Core.Kont}
    case Core.KMat{e1, +cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.KMat{e2, Core.Tms.dead(cs)} == k2 : Core.Kont},
        _ => ERel(e1, Lk(Core.CMat{Nil{}, Core.Tms.dead(cs)}), Nil{}, e2)>>
    case Core.KCase{e1, vs, b, +r}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 =>
        Sigma<&2, &2, {Core.KCase{e2, vs2, Core.Tm.dead(b), Core.Tms.dead(r)} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => ERel(e1, Lk(Core.CMat{Nil{}, Core.Tms.dead(r)}), Nil{}, e2)>>>>
    case Core.KSuc{c}:
      {Core.KSuc{c} == k2 : Core.Kont}
    case Core.KOp{op}:
      {Core.KOp{op} == k2 : Core.Kont}
    case Core.KTail{e1, +es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Wrap, w => Sigma<&2, &2, {Core.KTail{e2, Core.Tms.dead(es)} == k2 : Core.Kont},
        _ => ERel(e1, Lk(Wrap.tm(w, Core.Tms.dead(es))), Nil{}, e2)>>>
    case Core.KATail{e1, +as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, String, f => Sigma<&2, &2, {Core.KATail{e2, Core.Args.dead(as)} == k2 : Core.Kont},
        _ => ERel(e1, Lk(Core.CCall{f, Core.Args.dead(as)}), Nil{}, e2)>>>
    case Core.KCons{v}:
      Sigma<&2, &2, Core.Val, v2 => Sigma<&2, &2, {Core.KCons{v2} == k2 : Core.Kont}, _ => VRel(v, v2)>>
    case Core.KApply{vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.KApply{vs2} == k2 : Core.Kont}, _ => VRels(vs, vs2)>>
    case Core.KBody{b, r}:
      Sigma<&2, &2, List<&2, Core.Val>, r2 => Sigma<&2, &2, {Core.KBody{Core.Tm.dead(b), r2} == k2 : Core.Kont}, _ => VRels(r, r2)>>

# A dead let's steps: the source runs the value and binds it while the
# other program is at the let's body.
def Stut.let(p: Core.Pt, e1: List<&2, Core.Val>, +b: Core.Tm, s2: Core.Sel) -> Data:
  match p:
    case Core.PtVar{x}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SEval{e2, Core.Tm.dead(b)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, ERel(e1, Lk(Core.Tm.dead(b)), Nil{}, e2), _ => Fls(Core.Dead.used(Core.Tm.dead(b), Nil{}, x))>>>
    case Core.PtCtr{k, qs}:
      Empty
    case Core.PtNat{n}:
      Empty
    case Core.PtSuc{k, q}:
      Empty
    case Core.PtNum{n}:
      Empty
    case Core.PtFlt{s}:
      Empty

def Stut.bind(r1: Core.Res, +b: Core.Tm, s2: Core.Sel) -> Data:
  match r1:
    case Core.REnv{e1}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SEval{e2, Core.Tm.dead(b)} == s2 : Core.Sel},
        _ => ERel(e1, Lk(Core.Tm.dead(b)), Nil{}, e2)>>
    case Core.ROk{vs}:
      Empty
    case Core.RNo{}:
      Unit
    case Core.RFail{m}:
      Unit

def Stut.then(k1: Core.Kont, r1: Core.Res, s2: Core.Sel) -> Data:
  match k1:
    case Core.KLet{e1, p, b}:
      Stut.let(p, e1, b, s2)
    case Core.KBind{b}:
      Stut.bind(r1, b, s2)
    case other:
      Empty

def Stut.ok(k1: Core.Kont, s2: Core.Sel) -> Data:
  match k1:
    case Core.KLet{e1, p, b}:
      Stut.let(p, e1, b, s2)
    case other:
      Empty

# A pattern's step: when it matched, the values and the scope as SPat's.
def PatC.rel(h: Bool, -U: List<&2, String> -> String -> Bool, e1: List<&2, Core.Val>, ps: List<&2, Core.Pt>, vs: List<&2, Core.Val>,
    e2: List<&2, Core.Val>, vs2: List<&2, Core.Val>) -> Data:
  match h:
    case True{}:
      Sigma<&2, &2, VRels(vs, vs2), _ => ERel(e1, U, Core.Dead.names(ps), e2)>
    case False{}:
      Unit

# s2 is s1 in the program without dead lets, or s1 is at a dead let's
# steps and s2 at its body. U: the lookups of what runs in the scope a
# match's patterns make.
def SRel(s1: Core.Sel, -U: List<&2, String> -> String -> Bool, s2: Core.Sel) -> Data:
  match s1:
    case Core.SEval{e1, +t}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SEval{e2, Core.Tm.dead(t)} == s2 : Core.Sel},
        _ => ERel(e1, Lk(Core.Tm.dead(t)), Nil{}, e2)>>
    case Core.SEvals{e1, +es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, Wrap, w => Sigma<&2, &2, {Core.SEvals{e2, Core.Tms.dead(es)} == s2 : Core.Sel},
        _ => ERel(e1, Lk(Wrap.tm(w, Core.Tms.dead(es))), Nil{}, e2)>>>
    case Core.SArgs{e1, +as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, String, f => Sigma<&2, &2, {Core.SArgs{e2, Core.Args.dead(as)} == s2 : Core.Sel},
        _ => ERel(e1, Lk(Core.CCall{f, Core.Args.dead(as)}), Nil{}, e2)>>>
    case Core.SThen{+r1, +k1}:
      Either<&2, &2,
        Sigma<&2, &2, Core.Res, r2 => Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, {Core.SThen{r2, k2} == s2 : Core.Sel},
          _ => Sigma<&2, &2, KRel(k1, k2), _ => RRel(r1, Kont.U(k1), r2)>>>>,
        Stut.then(k1, r1, s2)>
    case Core.SOk{+k1, vs}:
      Either<&2, &2,
        Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SOk{k2, vs2} == s2 : Core.Sel},
          _ => Sigma<&2, &2, KRel(k1, k2), _ => VRels(vs, vs2)>>>>,
        Stut.ok(k1, s2)>
    case Core.SLook{e1, +x}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SLook{e2, x} == s2 : Core.Sel},
        _ => ERel(e1, Lk(Core.CVar{x}), Nil{}, e2)>>
    case Core.SLook2{h, v, e1, +x}:
      Sigma<&2, &2, Core.Val, v2 => Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SLook2{h, v2, e2, x} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRel(v, v2), _ => ERel(e1, Lk(Core.CVar{x}), Nil{}, e2)>>>>
    case Core.SCallDef{f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SCallDef{f, vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SFind{ds, f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SFind{Core.Defs.dead(ds), f, vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SFound{h, ps, b, ds, f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SFound{h, ps, Core.Tm.dead(b), Core.Defs.dead(ds), f, vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SEnter{sh, f, ps, b, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SEnter{sh, f, ps, Core.Tm.dead(b), vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SApply{vs, fv}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Core.Val, fv2 => Sigma<&2, &2, {Core.SApply{vs2, fv2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => VRel(fv, fv2)>>>>
    case Core.SMatch{e1, vs, +cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SMatch{e2, vs2, Core.Tms.dead(cs)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => ERel(e1, Lk(Core.CMat{Nil{}, Core.Tms.dead(cs)}), Nil{}, e2)>>>>
    case Core.SPat{e1, +ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SPat{e2, ps, vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => ERel(e1, U, Core.Dead.names(ps), e2)>>>>
    case Core.SPatC{+h, e1, +ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SPatC{h, e2, ps, vs2} == s2 : Core.Sel},
        _ => PatC.rel(h, U, e1, ps, vs, e2, vs2)>>>

# The laws
# ========

# From related states, with as much fuel or more, the program without its
# dead lets gives a related result (natives as ok says).
law dead_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(vs1, vs2) -> PRel(prim(op, vs1), prim(op, vs2))
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for ds: List<&2, Core.Def>
  for U: List<&2, String> -> String -> Bool
  for s1: Core.Sel
  for s2: Core.Sel
  for rel: SRel(s1, U, s2)
  RRel(Core.run(~prim, n, ds, s1), U, Core.run(~prim, m, Core.Defs.dead(ds), s2))

# A program's result, if it is values without closures (or no match): the
# program without its dead lets gives the same.
law dead_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(vs1, vs2) -> PRel(prim(op, vs1), prim(op, vs2))
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for ds: List<&2, Core.Def>
  for nf: Clean(Core.Prog.run(~prim, n, ds))
  {Core.Res.dead(Core.Prog.run(~prim, n, ds)) == Core.Prog.run(~prim, m, Core.Defs.dead(ds)) : Core.Res}
