import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./DEAD.bend as Dead

# The law that core.bend's literal pass (Tm.lit) preserves `run`, and the
# words it is stated in. LITPROOF.bend proves it.
#
# The pass puts a let's number in the place of each lookup of its variable,
# so the other program's terms are the source's with what the pass knew
# where they are (Tm.lits(t, s)): a state is related to one of its terms
# with the knowledge s, in a scope whose bindings s describes (Mirror). The
# scopes themselves are the same, up to the values' terms.

# Scopes
# ======

# The first bindings of e are those s knows of, the nearest first: of the
# same names, and of the literals s holds.
def Mirror(s: List<&2, Core.Sub>, e: List<&2, Core.Val>) -> Data:
  match s:
    case Nil{}:
      Unit
    case b <> r:
      match b:
        case Core.Sub{x, l}:
          match e:
            case Nil{}:
              Empty
            case v <> er:
              match v:
                case Core.VBnd{z, w}:
                  Sigma<&2, &2, {z == x : String}, _ => Sigma<&2, &2, {w == Core.VLit{l} : Core.Val}, _ => Mirror(r, er)>>
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
        case Core.Opq{x}:
          match e:
            case Nil{}:
              Empty
            case v <> er:
              match v:
                case Core.VBnd{z, w}:
                  Sigma<&2, &2, {z == x : String}, _ => Mirror(r, er)>
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

# Values
# ======

# v2 is v1 with a closure's body taken with what the pass knew of the
# closure's scope.
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
    case Core.VClo{+e1, +p1, b1}:
      match v2:
        case Core.VLit{l9}:
          Empty
        case Core.VCtr{k9, fs9}:
          Empty
        case Core.VClo{e2, p2, b2}:
          Sigma<&2, &2, {p1 == p2 : Core.Pt}, _ => Sigma<&2, &2, List<&2, Core.Sub>, s =>
            Sigma<&2, &2, {Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([p1]), s)) == b2 : Core.Tm},
            _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
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

# Results
# =======

# r2 is r1 with its values related; a scope the bindings of S describe (S:
# what the pass knew of the scope a match makes). A failure is related to
# any result: the law says nothing of a run that fails.
def RRel(r1: Core.Res, -S: List<&2, Core.Sub>, r2: Core.Res) -> Data:
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
    case Core.REnv{+e1}:
      match r2:
        case Core.REnv{e2}:
          Sigma<&2, &2, VRels(e1, e2), _ => Mirror(S, e1)>
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

# States
# ======

# k2 is k1 with its terms taken with what the pass knew of their scopes. S:
# what it knew of the scope k1 gets, for the terms that run in it.
def KRel(k1: Core.Kont, -S: List<&2, Core.Sub>, k2: Core.Kont) -> Data:
  match k1:
    case Core.KCall{f}:
      {Core.KCall{f} == k2 : Core.Kont}
    case Core.KApp{}:
      {Core.KApp{} == k2 : Core.Kont}
    case Core.KCtr{c}:
      {Core.KCtr{c} == k2 : Core.Kont}
    case Core.KLet{+e1, +p, b}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.KLet{e2, p, Core.Tm.lits(b, Core.Sub.bind(Core.Dead.names([p]), s))} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
    case Core.KBind{b}:
      {Core.KBind{Core.Tm.lits(b, S)} == k2 : Core.Kont}
    case Core.KMat{+e1, cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.KMat{e2, Core.Tms.lits(cs, s)} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
    case Core.KCase{+e1, vs, b, r}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.KCase{e2, vs2, Core.Tm.lits(b, S), Core.Tms.lits(r, s)} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>>>
    case Core.KSuc{c}:
      {Core.KSuc{c} == k2 : Core.Kont}
    case Core.KOp{op}:
      {Core.KOp{op} == k2 : Core.Kont}
    case Core.KTail{+e1, es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.KTail{e2, Core.Tms.lits(es, s)} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
    case Core.KATail{+e1, as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.KATail{e2, Core.Args.lits(as, s)} == k2 : Core.Kont},
        _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
    case Core.KCons{v}:
      Sigma<&2, &2, Core.Val, v2 => Sigma<&2, &2, {Core.KCons{v2} == k2 : Core.Kont}, _ => VRel(v, v2)>>
    case Core.KApply{vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.KApply{vs2} == k2 : Core.Kont}, _ => VRels(vs, vs2)>>
    case Core.KBody{b, r}:
      Sigma<&2, &2, List<&2, Core.Val>, r2 => Sigma<&2, &2, {Core.KBody{Core.Tm.lits(b, S), r2} == k2 : Core.Kont}, _ => VRels(r, r2)>>

# A let of a number to a variable, in its steps (the value's run and the
# binding): the other program's body is taken knowing the number.
def Let.k(k1: Core.Kont, +l: Core.Lit, k2: Core.Kont) -> Data:
  match k1:
    case Core.KLet{+e1, p, b}:
      match p:
        case Core.PtVar{+x}:
          Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
            Sigma<&2, &2, {Core.KLet{e2, Core.PtVar{x}, Core.Tm.lits(b, Core.Sub{x, l} <> s)} == k2 : Core.Kont},
            _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
        case Core.PtCtr{k9, qs9}:
          Empty
        case Core.PtNat{n9}:
          Empty
        case Core.PtSuc{k9, q9}:
          Empty
        case Core.PtNum{n9}:
          Empty
        case Core.PtFlt{s9}:
          Empty
    case Core.KCall{f9}:
      Empty
    case Core.KApp{}:
      Empty
    case Core.KCtr{c9}:
      Empty
    case Core.KBind{b9}:
      Empty
    case Core.KMat{e9, cs9}:
      Empty
    case Core.KCase{e9, vs9, b9, r9}:
      Empty
    case Core.KSuc{c9}:
      Empty
    case Core.KOp{op9}:
      Empty
    case Core.KTail{e9, es9}:
      Empty
    case Core.KATail{e9, as9}:
      Empty
    case Core.KCons{v9}:
      Empty
    case Core.KApply{vs9}:
      Empty
    case Core.KBody{b9, r9}:
      Empty

# The value's run: the number, in both (or the source failed).
def Let.res(r1: Core.Res, +l: Core.Lit, r2: Core.Res) -> Data:
  match r1:
    case Core.ROk{vs}:
      Sigma<&2, &2, {[Core.VLit{l}] == vs : List<&2, Core.Val>}, _ => {Core.ROk{[Core.VLit{l}]} == r2 : Core.Res}>
    case Core.REnv{e}:
      Empty
    case Core.RNo{}:
      Empty
    case Core.RFail{m}:
      Unit

# A pattern's step: when it matched, the values and the scope as SPat's.
def PatC.rel(h: Bool, -S: List<&2, Core.Sub>, e1: List<&2, Core.Val>, +ps: List<&2, Core.Pt>, vs: List<&2, Core.Val>,
    e2: List<&2, Core.Val>, vs2: List<&2, Core.Val>) -> Data:
  match h:
    case True{}:
      Sigma<&2, &2, List<&2, Core.Sub>, s => Sigma<&2, &2, VRels(vs, vs2), _ => Sigma<&2, &2, VRels(e1, e2),
        _ => Sigma<&2, &2, Mirror(s, e1), _ => {Core.Sub.bind(Core.Dead.names(ps), s) == S : List<&2, Core.Sub>}>>>>
    case False{}:
      Unit

# s2 is s1 in the program the pass took, a term with what the pass knew of
# its scope, or both are at a let of a number (Let.k). S: what the pass
# knew of the scope a match's patterns make.
def SRel(s1: Core.Sel, -S: List<&2, Core.Sub>, s2: Core.Sel) -> Data:
  match s1:
    case Core.SEval{+e1, t}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.SEval{e2, Core.Tm.lits(t, s)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
    case Core.SEvals{+e1, es}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.SEvals{e2, Core.Tms.lits(es, s)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
    case Core.SArgs{+e1, as}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.SArgs{e2, Core.Args.lits(as, s)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>
    case Core.SThen{+r1, +k1}:
      Either<&2, &2,
        Sigma<&2, &2, Core.Res, r2 => Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
          Sigma<&2, &2, {Core.SThen{r2, k2} == s2 : Core.Sel},
          _ => Sigma<&2, &2, KRel(k1, s, k2), _ => RRel(r1, s, r2)>>>>>,
        Sigma<&2, &2, Core.Lit, l => Sigma<&2, &2, Core.Res, r2 => Sigma<&2, &2, Core.Kont, k2 =>
          Sigma<&2, &2, {Core.SThen{r2, k2} == s2 : Core.Sel}, _ => Sigma<&2, &2, Let.k(k1, l, k2), _ => Let.res(r1, l, r2)>>>>>>
    case Core.SOk{+k1, vs}:
      Either<&2, &2,
        Sigma<&2, &2, Core.Kont, k2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
          Sigma<&2, &2, {Core.SOk{k2, vs2} == s2 : Core.Sel},
          _ => Sigma<&2, &2, KRel(k1, s, k2), _ => VRels(vs, vs2)>>>>>,
        Sigma<&2, &2, Core.Lit, +l => Sigma<&2, &2, Core.Kont, k2 =>
          Sigma<&2, &2, {Core.SOk{k2, [Core.VLit{l}]} == s2 : Core.Sel}, _ => Sigma<&2, &2, Let.k(k1, l, k2),
          _ => {[Core.VLit{l}] == vs : List<&2, Core.Val>}>>>>>
    case Core.SLook{e1, x}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SLook{e2, x} == s2 : Core.Sel}, _ => VRels(e1, e2)>>
    case Core.SLook2{h, v, e1, x}:
      Sigma<&2, &2, Core.Val, v2 => Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, {Core.SLook2{h, v2, e2, x} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRel(v, v2), _ => VRels(e1, e2)>>>>
    case Core.SCallDef{f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SCallDef{f, vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SFind{ds, f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SFind{Core.Defs.lit(ds), f, vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SFound{h, ps, b, ds, f, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SFound{h, ps, Core.Tm.lit(b), Core.Defs.lit(ds), f, vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SEnter{sh, f, ps, b, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SEnter{sh, f, ps, Core.Tm.lit(b), vs2} == s2 : Core.Sel}, _ => VRels(vs, vs2)>>
    case Core.SApply{vs, fv}:
      Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, Core.Val, fv2 => Sigma<&2, &2, {Core.SApply{vs2, fv2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => VRel(fv, fv2)>>>>
    case Core.SMatch{+e1, vs, cs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.SMatch{e2, vs2, Core.Tms.lits(cs, s)} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => Sigma<&2, &2, VRels(e1, e2), _ => Mirror(s, e1)>>>>>>
    case Core.SPat{+e1, +ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, List<&2, Core.Sub>, s =>
        Sigma<&2, &2, {Core.SPat{e2, ps, vs2} == s2 : Core.Sel},
        _ => Sigma<&2, &2, VRels(vs, vs2), _ => Sigma<&2, &2, VRels(e1, e2),
        _ => Sigma<&2, &2, Mirror(s, e1), _ => {Core.Sub.bind(Core.Dead.names(ps), s) == S : List<&2, Core.Sub>}>>>>>>>
    case Core.SPatC{+h, e1, +ps, vs}:
      Sigma<&2, &2, List<&2, Core.Val>, e2 => Sigma<&2, &2, List<&2, Core.Val>, vs2 => Sigma<&2, &2, {Core.SPatC{h, e2, ps, vs2} == s2 : Core.Sel},
        _ => PatC.rel(h, S, e1, ps, vs, e2, vs2)>>>

# The laws
# ========

# From related states, with as much fuel or more, the program the pass took
# gives a related result (natives as ok says).
law lit_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(vs1, vs2) -> PRel(prim(op, vs1), prim(op, vs2))
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for ds: List<&2, Core.Def>
  for S: List<&2, Core.Sub>
  for s1: Core.Sel
  for s2: Core.Sel
  for rel: SRel(s1, S, s2)
  RRel(Core.run(~prim, n, ds, s1), S, Core.run(~prim, m, Core.Defs.lit(ds), s2))

# A program's result, if it is values without closures (or no match): the
# program the pass took gives the same.
law lit_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> VRels(vs1, vs2) -> PRel(prim(op, vs1), prim(op, vs2))
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for ds: List<&2, Core.Def>
  for nf: Dead.Clean(Core.Prog.run(~prim, n, ds))
  {Core.Prog.run(~prim, n, ds) == Core.Prog.run(~prim, m, Core.Defs.lit(ds)) : Core.Res}
