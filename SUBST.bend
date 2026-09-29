import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./DEAD.bend as Dead

# The law that core.bend's substitution pass (Tm.subst) preserves `run`, and
# the words it is stated in. SUBSTPROOF.bend proves it.
#
# The pass puts a let's value v in the place of lookups of its variable x,
# and keeps the let, so the other program's scopes have the source's
# bindings, and more: a lookup the pass replaced runs v (v2: v with the
# pass taken) in the scope of the lookup, the let's scope with x's binding
# in front, where it takes more steps than the lookup. So the law does not
# bound the other program's fuel by the source's: from related states, for
# a source that does not fail, there is fuel with which the other program
# gives a related result.
#
# A scope of the other program is related to one of the source's by what
# its lookups give (Gives): a lookup of a name the source binds gives a
# value related to the source's binding. What the pass knew of the
# source's scope (s, one entry for each binding, the nearest first) is in
# the relation: where it put a let's value in place, v2 gives there what
# the let's variable is bound to. The natives (prim) and the other
# program's defs (dz) are in the words, as Gives runs terms.

def If(b: Bool, A: Data, B: Data) -> Data:
  match b:
    case True{}:
      A
    case False{}:
      B

# Values and scopes
# =================

# v2 is v1 with its closures' bodies taken with what the pass knew of their
# scopes, and those scopes related.
def VRel(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, v1: Core.Val, v2: Core.Val) -> Data:
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
          Sigma<&2, &2, {k1 == k2 : String}, _ => VRels(prim, dz, fs1, fs2)>
        case Core.VClo{env9, p9, b9}:
          Empty
        case Core.VFun{f9, as9}:
          Empty
        case Core.VTrm{t9}:
          Empty
        case Core.VBnd{x9, w9}:
          Empty
    case Core.VClo{env1, p1, b1}:
      match v2:
        case Core.VLit{l9}:
          Empty
        case Core.VCtr{k9, fs9}:
          Empty
        case Core.VClo{env2, p2, b2}:
          Sigma<&2, &2, {p1 == p2 : Core.Pt}, _ => Sigma<&2, &2, List<&2, Core.Sb>, s =>
            Sigma<&2, &2, {Core.Tm.subst(b1, Core.Sb.bind(Core.Dead.names([p1]), s)) == b2 : Core.Tm},
            _ => ERel(prim, dz, s, env1, Nil{}, env2)>>>
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
          Sigma<&2, &2, {f1 == f2 : String}, _ => VRels(prim, dz, as1, as2)>
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
          Sigma<&2, &2, {x1 == x2 : String}, _ => VRel(prim, dz, w1, w2)>

def VRels(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, vs1: List<&2, Core.Val>, vs2: List<&2, Core.Val>) -> Data:
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
          Sigma<&2, &2, VRel(prim, dz, v, w), _ => VRels(prim, dz, r, s)>

# t runs in e2 to one value, related to w, with some fuel.
def Gives(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, w: Core.Val, e2: List<&2, Core.Val>, t: Core.Tm) -> Data:
  Sigma<&2, &2, Core.Val, w2 => Sigma<&2, &2, Nat, m =>
    Sigma<&2, &2, {Core.run(~prim, m, dz, Core.SEval{e2, t}) == Core.ROk{[w2]} : Core.Res}, _ => VRel(prim, dz, w, w2)>>>

# e2 is related to e1, s knowing e1's bindings (one for each, with the
# same names): a lookup in e2 of the name of a binding of e1 none of hs is
# (the names of the bindings before it) gives a value related to it, and
# so does v2 if s knows it for the binding.
def ERel(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, s: List<&2, Core.Sb>, e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>) -> Data:
  match s:
    case Nil{}:
      match e1:
        case Nil{}:
          Unit
        case c <> r:
          Empty
    case b <> sr:
      match b:
        case Core.SbSub{y, +v2}:
          match e1:
            case Nil{}:
              Empty
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  Sigma<&2, &2, {z == y : String}, _ => Sigma<&2, &2,
                    If(Core.Dead.none(hs, z), Sigma<&2, &2, Gives(prim, dz, w, e2, Core.CVar{z}), _ => Gives(prim, dz, w, e2, v2)>, Unit),
                    _ => ERel(prim, dz, sr, r, z <> hs, e2)>>
                case other:
                  Empty
        case Core.SbOpq{y}:
          match e1:
            case Nil{}:
              Empty
            case c <> r:
              match c:
                case Core.VBnd{+z, +w}:
                  Sigma<&2, &2, {z == y : String}, _ => Sigma<&2, &2, If(Core.Dead.none(hs, z), Gives(prim, dz, w, e2, Core.CVar{z}), Unit),
                    _ => ERel(prim, dz, sr, r, z <> hs, e2)>>
                case other:
                  Empty

# Results
# =======

# r2 is r1 with its values related, a scope's with S for what the pass knew
# of it. A failure is related to any result: the law says nothing of a run
# that fails.
def RRel(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, r1: Core.Res, S: List<&2, Core.Sb>, r2: Core.Res) -> Data:
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          VRels(prim, dz, vs1, vs2)
        case Core.REnv{e}:
          Empty
        case Core.RNo{}:
          Empty
        case Core.RFail{m}:
          Empty
    case Core.REnv{e1}:
      match r2:
        case Core.REnv{e2}:
          ERel(prim, dz, S, e1, Nil{}, e2)
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
def PRel(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, r1: Core.Res, r2: Core.Res) -> Data:
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          VRels(prim, dz, vs1, vs2)
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

# States
# ======

# k2 is k1 with its terms taken with what the pass knew of their scopes. S:
# what it knew of the scope k1 gets, for the terms that run in it.
def KRel(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, k1: Core.Kont, -S: List<&2, Core.Sb>, k2: Core.Kont) -> Data:
  match k1:
    case Core.KCall{f}:
      {Core.KCall{f} == k2 : Core.Kont}
    case Core.KApp{}:
      {Core.KApp{} == k2 : Core.Kont}
    case Core.KCtr{c}:
      {Core.KCtr{c} == k2 : Core.Kont}
    case Core.KLet{e1, +p, b}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.KLet{e2, p, Core.Tm.subst(b, Core.Sb.bind(Core.Dead.names([p]), s))} == k2 : Core.Kont},
        _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>
    case Core.KBind{b}:
      {Core.KBind{Core.Tm.subst(b, S)} == k2 : Core.Kont}
    case Core.KMat{e1, cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.KMat{e2, Core.Tms.subst(cs, s)} == k2 : Core.Kont},
        _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>
    case Core.KCase{e1, vs, b, r}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.KCase{e2, vs2, Core.Tm.subst(b, S), Core.Tms.subst(r, s)} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(prim, dz, vs, vs2), _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>>>
    case Core.KSuc{c}:
      {Core.KSuc{c} == k2 : Core.Kont}
    case Core.KOp{op}:
      {Core.KOp{op} == k2 : Core.Kont}
    case Core.KTail{e1, es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.KTail{e2, Core.Tms.subst(es, s)} == k2 : Core.Kont},
        _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>
    case Core.KATail{e1, as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.KATail{e2, Core.Args.subst(as, s)} == k2 : Core.Kont},
        _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>
    case Core.KCons{v}:
      Sigma<&2, &2, Core.Val, v2 => Sigma<&2, &2, {Core.KCons{v2} == k2 : Core.Kont}, _ => VRel(prim, dz, v, v2)>>
    case Core.KApply{vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.KApply{vs2} == k2 : Core.Kont}, _ => VRels(prim, dz, vs, vs2)>>
    case Core.KBody{b, r}:
      Sigma<&2, &2, List<&2, Core.Val>, r2 => Sigma<&2, &2, {Core.KBody{Core.Tm.subst(b, S), r2} == k2 : Core.Kont}, _ => VRels(prim, dz, r, r2)>>

# A pattern's step: when it matched, the values and the scope as SPat's.
def PatC.rel(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, h: Bool, -S: List<&2, Core.Sb>, e1: List<&2, Core.Val>, +ps: List<&2, Core.Pt>, vs: List<&2, Core.Val>,
    e2: List<&2, Core.Val>, vs2: List<&2, Core.Val>) -> Data:
  match h:
    case True{}:
      Sigma<&2, &2, List<&2, Core.Sb>, s => Sigma<&2, &2, VRels(prim, dz, vs, vs2), _ => Sigma<&2, &2, ERel(prim, dz, s, e1, Nil{}, e2),
        _ => {Core.Sb.bind(Core.Dead.names(ps), s) == S : List<&2, Core.Sb>}>>>
    case False{}:
      Unit

# s2 is s1 in the program the pass took, a term with what the pass knew of
# its scope. S: what the pass knew of the scope a match's patterns make. A
# lookup's steps are not related (the other program may run a let's value
# there).
def SRel(-prim: String -> List<&2, Core.Val> -> Core.Res, -dz: List<&2, Core.Def>, s1: Core.Sel, -S: List<&2, Core.Sb>, s2: Core.Sel) -> Data:
  match s1:
    case Core.SEval{e1, t}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.SEval{e2, Core.Tm.subst(t, s)} == s2 : Core.Sel}, _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>
    case Core.SEvals{e1, es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.SEvals{e2, Core.Tms.subst(es, s)} == s2 : Core.Sel}, _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>
    case Core.SArgs{e1, as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.SArgs{e2, Core.Args.subst(as, s)} == s2 : Core.Sel}, _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>
    case Core.SThen{r1, +k1}:
      Sigma<&2, &2, Core.Res, r2 => Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.SThen{r2, k2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, KRel(prim, dz, k1, s, k2), _ => RRel(prim, dz, r1, s, r2)>>>>>
    case Core.SOk{k1, vs}:
      Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.SOk{k2, vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, KRel(prim, dz, k1, s, k2), _ => VRels(prim, dz, vs, vs2)>>>>>
    case Core.SLook{e1, x}:
      Empty
    case Core.SLook2{h, v, e1, x}:
      Empty
    case Core.SCallDef{f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SCallDef{f, vs2} == s2 : Core.Sel}, _ => VRels(prim, dz, vs, vs2)>>
    case Core.SFind{ds, f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SFind{Core.Defs.subst(ds), f, vs2} == s2 : Core.Sel}, _ => VRels(prim, dz, vs, vs2)>>
    case Core.SFound{h, +ps, b, ds, f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2,
        {Core.SFound{h, ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), Core.Defs.subst(ds), f, vs2} == s2 : Core.Sel},
        _ => VRels(prim, dz, vs, vs2)>>
    case Core.SEnter{+sh, f, +ps, b, +vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SEnter{sh, f, ps, Core.Tm.subst(b, Core.Sb.pars(ps, Nil{})), vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(prim, dz, vs, vs2), _ => {sh == Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)) : Bool}>>>
    case Core.SApply{vs, fv}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Core.Val, fv2 => Sigma<&2, &2, {Core.SApply{vs2, fv2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(prim, dz, vs, vs2), _ => VRel(prim, dz, fv, fv2)>>>>
    case Core.SMatch{e1, vs, cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.SMatch{e2, vs2, Core.Tms.subst(cs, s)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(prim, dz, vs, vs2), _ => ERel(prim, dz, s, e1, Nil{}, e2)>>>>>
    case Core.SPat{e1, +ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sb>, s =>
        Sigma<&2, &2, {Core.SPat{e2, ps, vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(prim, dz, vs, vs2), _ => Sigma<&2, &2, ERel(prim, dz, s, e1, Nil{}, e2),
        _ => {Core.Sb.bind(Core.Dead.names(ps), s) == S : List<&2, Core.Sb>}>>>>>>
    case Core.SPatC{+h, e1, +ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SPatC{h, e2, ps, vs2} == s2 : Core.Sel},
        _ => PatC.rel(prim, dz, h, S, e1, ps, vs, e2, vs2)>>>

# The laws
# ========

# From related states, for a source that does not fail, the program the
# pass took gives a related result with some fuel (natives as ok says).
law subst_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ds: List<&2, Core.Def>
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(prim, Core.Defs.subst(ds), vs1, vs2) ->
    PRel(prim, Core.Defs.subst(ds), prim(op, vs1), prim(op, vs2))
  for n: Nat
  for S: List<&2, Core.Sb>
  for s1: Core.Sel
  for s2: Core.Sel
  for rel: SRel(prim, Core.Defs.subst(ds), s1, S, s2)
  Sigma<&2, &2, Nat, m => RRel(prim, Core.Defs.subst(ds), Core.run(~prim, n, ds, s1), S, Core.run(~prim, m, Core.Defs.subst(ds), s2))>

# A program's result, if it is values without closures (or no match): the
# program the pass took gives the same, with some fuel (and with more, as
# it does not run out: REDPROOF.bend's L.mono).
law subst_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ds: List<&2, Core.Def>
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(prim, Core.Defs.subst(ds), vs1, vs2) ->
    PRel(prim, Core.Defs.subst(ds), prim(op, vs1), prim(op, vs2))
  for n: Nat
  for nf: Dead.Clean(Core.Prog.run(~prim, n, ds))
  Sigma<&2, &2, Nat, m => {Core.Prog.run(~prim, n, ds) == Core.Prog.run(~prim, m, Core.Defs.subst(ds)) : Core.Res}>
