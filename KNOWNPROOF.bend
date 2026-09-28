import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./REDPROOF.bend as RP
import ./KNOWN.bend as Law

# Proof of KNOWN.bend's laws, the way REDPROOF.bend proves RED.bend's (its
# S.one and L.mono are reused). K.mat: in one program, a match and the
# match Tm.known's rule makes of it give the same result. L.known
# (known_ok): induction on the fuel, one case per step of `run`, and a
# match's node by K.mat in the resolved program.

# Shapes
# ======

# Tm.known and Val.known walk a list field as its head and the node rebuilt
# with the rest; these give the node with the field resolved as a whole. The
# rest is not a node of the term (top is False there): the rule is not taken
# on it.

def L.call(f: String, as: List<&2, Core.Arg>, top: Bool)
    -> {Core.CCall{f, Core.Args.known(as)} == Core.Tm.known(Core.CCall{f, as}, top) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          %L.call(f, r, False{}) : {Core.CCall{f, Core.Arg{rel, Core.Tm.known(e, True{})} <> Core.Args.known(r)} == Core.Tm.push.call(Core.Arg{rel, Core.Tm.known(e, True{})}, _) : Core.Tm}
          {==}

def L.app(f: Core.Tm, as: List<&2, Core.Tm>, top: Bool)
    -> {Core.CApp{Core.Tm.known(f, True{}), Core.Tms.known(as)} == Core.Tm.known(Core.CApp{f, as}, top) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.app(f, r, False{}) : {Core.CApp{Core.Tm.known(f, True{}), Core.Tm.known(a, True{}) <> Core.Tms.known(r)} == Core.Tm.push(Core.Tm.known(a, True{}), _) : Core.Tm}
      {==}

def L.ctr(k: String, as: List<&2, Core.Tm>, top: Bool)
    -> {Core.CCtr{k, Core.Tms.known(as)} == Core.Tm.known(Core.CCtr{k, as}, top) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.ctr(k, r, False{}) : {Core.CCtr{k, Core.Tm.known(a, True{}) <> Core.Tms.known(r)} == Core.Tm.push(Core.Tm.known(a, True{}), _) : Core.Tm}
      {==}

def L.mat.cases(cs: List<&2, Core.Tm>)
    -> {Core.CMat{Nil{}, Core.Tms.known(cs)} == Core.Tm.known(Core.CMat{Nil{}, cs}, False{}) : Core.Tm}:
  match cs:
    case Nil{}:
      {==}
    case c <> r:
      %L.mat.cases(r) : {Core.CMat{Nil{}, Core.Tm.known(c, True{}) <> Core.Tms.known(r)} == Core.Tm.push.case(Core.Tm.known(c, True{}), _) : Core.Tm}
      {==}

def L.mat(scrs: List<&2, Core.Tm>, cs: List<&2, Core.Tm>)
    -> {Core.CMat{Core.Tms.known(scrs), Core.Tms.known(cs)} == Core.Tm.known(Core.CMat{scrs, cs}, False{}) : Core.Tm}:
  match scrs:
    case Nil{}:
      L.mat.cases(cs)
    case a <> r:
      %L.mat(r, cs) : {Core.CMat{Core.Tm.known(a, True{}) <> Core.Tms.known(r), Core.Tms.known(cs)} == Core.Tm.push(Core.Tm.known(a, True{}), _) : Core.Tm}
      {==}

# At a node of t (top), the match with its fields resolved, then itself.
def L.mat.top(scrs: List<&2, Core.Tm>, cs: List<&2, Core.Tm>, top: Bool)
    -> {Core.Known.top(top, Core.CMat{Core.Tms.known(scrs), Core.Tms.known(cs)}) == Core.Tm.known(Core.CMat{scrs, cs}, top) : Core.Tm}:
  match scrs:
    case Nil{}:
      match cs:
        case Nil{}:
          {==}
        case c <> r:
          %L.mat.cases(r) : {Core.Known.top(top, Core.CMat{Nil{}, Core.Tm.known(c, True{}) <> Core.Tms.known(r)}) == Core.Known.top(top, Core.Tm.push.case(Core.Tm.known(c, True{}), _)) : Core.Tm}
          {==}
    case a <> r:
      %L.mat(r, cs) : {Core.Known.top(top, Core.CMat{Core.Tm.known(a, True{}) <> Core.Tms.known(r), Core.Tms.known(cs)}) == Core.Known.top(top, Core.Tm.push(Core.Tm.known(a, True{}), _)) : Core.Tm}
      {==}

def L.vctr(k: String, fs: List<&2, Core.Val>)
    -> {Core.VCtr{k, Core.Vals.known(fs)} == Core.Val.known(Core.VCtr{k, fs}) : Core.Val}:
  match fs:
    case Nil{}:
      {==}
    case f <> r:
      %L.vctr(k, r) : {Core.VCtr{k, Core.Val.known(f) <> Core.Vals.known(r)} == Core.Val.push(Core.Val.known(f), _) : Core.Val}
      {==}

def L.vfun(g: String, as: List<&2, Core.Val>)
    -> {Core.VFun{g, Core.Vals.known(as)} == Core.Val.known(Core.VFun{g, as}) : Core.Val}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.vfun(g, r) : {Core.VFun{g, Core.Val.known(a) <> Core.Vals.known(r)} == Core.Val.push(Core.Val.known(a), _) : Core.Val}
      {==}

def L.vclo(env: List<&2, Core.Val>, pt: Core.Pt, bd: Core.Tm)
    -> {Core.VClo{Core.Vals.known(env), pt, Core.Tm.known(bd, True{})} == Core.Val.known(Core.VClo{env, pt, bd}) : Core.Val}:
  match env:
    case Nil{}:
      {==}
    case e <> r:
      %L.vclo(r, pt, bd) : {Core.VClo{Core.Val.known(e) <> Core.Vals.known(r), pt, Core.Tm.known(bd, True{})} == Core.Val.push.env(Core.Val.known(e), _) : Core.Val}
      {==}

def L.vclo.rev(env: List<&2, Core.Val>, pt: Core.Pt, bd: Core.Tm)
    -> {Core.Val.known(Core.VClo{env, pt, bd}) == Core.VClo{Core.Vals.known(env), pt, Core.Tm.known(bd, True{})} : Core.Val}:
  %L.vclo(env, pt, bd) : {_ == Core.VClo{Core.Vals.known(env), pt, Core.Tm.known(bd, True{})} : Core.Val}
  {==}

# Lists
# =====

def L.len(vs: List<&2, Core.Val>) -> {Core.Vals.len(vs) == Core.Vals.len(Core.Vals.known(vs)) : Nat}:
  match vs:
    case Nil{}:
      {==}
    case v <> r:
      %L.len(r) : {1n+Core.Vals.len(r) == 1n+_ : Nat}
      {==}

def L.cat(a: List<&2, Core.Val>, b: List<&2, Core.Val>)
    -> {Core.Vals.known(Core.Vals.cat(a, b)) == Core.Vals.cat(Core.Vals.known(a), Core.Vals.known(b)) : List<&2, Core.Val>}:
  match a:
    case Nil{}:
      {==}
    case v <> r:
      %L.cat(r, b) : {Core.Val.known(v) <> Core.Vals.known(Core.Vals.cat(r, b)) == Core.Val.known(v) <> _ : List<&2, Core.Val>}
      {==}

def L.drop(n: Nat, vs: List<&2, Core.Val>)
    -> {Core.Vals.known(Core.Vals.drop(n, vs)) == Core.Vals.drop(n, Core.Vals.known(vs)) : List<&2, Core.Val>}:
  match n:
    case 0n:
      {==}
    case 1n+m:
      match vs:
        case Nil{}:
          {==}
        case v <> r:
          L.drop(m, r)

def L.bind(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>)
    -> {Core.Vals.known(Core.Scope.bind(ps, vs)) == Core.Scope.bind(ps, Core.Vals.known(vs)) : List<&2, Core.Val>}:
  match ps:
    case Nil{}:
      {==}
    case q <> pr:
      match q:
        case Core.Par{x, rel, mode, ty}:
          match vs:
            case Nil{}:
              {==}
            case v <> vr:
              %L.bind(pr, vr) : {Core.VBnd{x, Core.Val.known(v)} <> Core.Vals.known(Core.Scope.bind(pr, vr)) == Core.VBnd{x, Core.Val.known(v)} <> _ : List<&2, Core.Val>}
              {==}

# Patterns
# ========

def L.pat(env: List<&2, Core.Val>, pt: Core.Pt, v: Core.Val, ps: List<&2, Core.Pt>, vs: List<&2, Core.Val>)
    -> {Core.Sel.known(Core.Pat.step(env, pt, v, ps, vs)) == Core.Pat.step(Core.Vals.known(env), pt, Core.Val.known(v), ps, Core.Vals.known(vs)) : Core.Sel}:
  match pt:
    case Core.PtVar{x}:
      {==}
    case Core.PtCtr{k, qs}:
      match v:
        case Core.VCtr{k2, +fs}:
          %L.vctr(k2, fs) : {Core.Sel.known(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          %L.len(fs) : {Core.Sel.known(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.SPatC{Bool.and(String.eq(k, k2), Nat.is_eq(Core.Pts.len(qs), _)), Core.Vals.known(env), Core.Pts.cat(qs, ps), Core.Vals.cat(Core.Vals.known(fs), Core.Vals.known(vs))} : Core.Sel}
          %L.cat(fs, vs) : {Core.Sel.known(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.SPatC{Bool.and(String.eq(k, k2), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs))), Core.Vals.known(env), Core.Pts.cat(qs, ps), _} : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.known(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.known(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VLit{l}:
          {==}
        case Core.VTrm{t}:
          {==}
        case Core.VBnd{y, w}:
          {==}
    case Core.PtNat{n}:
      match v:
        case Core.VCtr{k2, fs}:
          %L.vctr(k2, fs) : {Core.Sel.known(Core.Pat.step(env, Core.PtNat{n}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtNat{n}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.known(Core.Pat.step(env, Core.PtNat{n}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtNat{n}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.known(Core.Pat.step(env, Core.PtNat{n}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtNat{n}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VLit{l}:
          {==}
        case Core.VTrm{t}:
          {==}
        case Core.VBnd{y, w}:
          {==}
    case Core.PtNum{n}:
      match v:
        case Core.VCtr{k2, fs}:
          %L.vctr(k2, fs) : {Core.Sel.known(Core.Pat.step(env, Core.PtNum{n}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtNum{n}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.known(Core.Pat.step(env, Core.PtNum{n}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtNum{n}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.known(Core.Pat.step(env, Core.PtNum{n}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtNum{n}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VLit{l}:
          {==}
        case Core.VTrm{t}:
          {==}
        case Core.VBnd{y, w}:
          {==}
    case Core.PtFlt{s}:
      match v:
        case Core.VCtr{k2, fs}:
          %L.vctr(k2, fs) : {Core.Sel.known(Core.Pat.step(env, Core.PtFlt{s}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtFlt{s}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.known(Core.Pat.step(env, Core.PtFlt{s}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtFlt{s}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.known(Core.Pat.step(env, Core.PtFlt{s}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtFlt{s}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VLit{l}:
          {==}
        case Core.VTrm{t}:
          {==}
        case Core.VBnd{y, w}:
          {==}
    case Core.PtSuc{k, q}:
      match v:
        case Core.VCtr{k2, fs}:
          %L.vctr(k2, fs) : {Core.Sel.known(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtSuc{k, q}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.known(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtSuc{k, q}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.known(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.known(env), Core.PtSuc{k, q}, _, ps, Core.Vals.known(vs)) : Core.Sel}
          {==}
        case Core.VLit{l}:
          match l:
            case Core.LNum{m}:
              {==}
            case Core.LNat{m}:
              {==}
            case Core.LFlt{m}:
              {==}
            case Core.LStr{m}:
              {==}
        case Core.VTrm{t}:
          {==}
        case Core.VBnd{y, w}:
          {==}


# Fuel
# ====

def L.nf.known(+r: Core.Res, +h: Red.NotOof(r)) -> Red.NotOof(Core.Res.known(r)):
  match r:
    case Core.RFail{m}:
      h
    case Core.ROk{vs}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.REnv{env}:
      Unit{}

# The rule
# ========

# Tm.known's rule holds in one program, whatever the program: KL, by
# induction on the cases. A case of another constructor fails to match K's
# value, the source takes the next (SkipE); K's case with a variable per
# field binds the fields of K's value, the resolved match binds as's values
# (HitE). Kn.x is the run that gives the value of [K{as}] from the value A
# of as, in two steps more than as's; L.mono takes A at the fuel each side
# has.

def Tru(b: Bool) -> Data:
  match b:
    case True{}:
      Unit
    case False{}:
      Empty

def Tru.of(-b: Bool, h: {True{} == b : Bool}) -> Tru(b):
  %h : Tru(_)
  Unit{}

def NotNo(r: Core.Res) -> Data:
  match r:
    case Core.RNo{}:
      Empty
    case Core.ROk{vs}:
      Unit
    case Core.REnv{env}:
      Unit
    case Core.RFail{m}:
      Unit

def Res.sym(-x: Core.Res, -y: Core.Res, e: {x == y : Core.Res}) -> {y == x : Core.Res}:
  %e : {_ == x : Core.Res}
  {==}

def Then.cong(~prim: String -> List<&2, Core.Val> -> Core.Res, -p: Nat, -ds: List<&2, Core.Def>, -x: Core.Res, -y: Core.Res, -k: Core.Kont, e: {y == x : Core.Res})
    -> {Core.run(~prim, p, ds, Core.SThen{x, k}) == Core.run(~prim, p, ds, Core.SThen{y, k}) : Core.Res}:
  %e : {Core.run(~prim, p, ds, Core.SThen{_, k}) == Core.run(~prim, p, ds, Core.SThen{y, k}) : Core.Res}
  {==}

def Pts.catnil(ps: List<&2, Core.Pt>) -> {ps == Core.Pts.cat(ps, Nil{}) : List<&2, Core.Pt>}:
  match ps:
    case Nil{}:
      {==}
    case p <> r:
      %Pts.catnil(r) : {p <> r == p <> _ : List<&2, Core.Pt>}
      {==}

def Vals.catnil(vs: List<&2, Core.Val>) -> {vs == Core.Vals.cat(vs, Nil{}) : List<&2, Core.Val>}:
  match vs:
    case Nil{}:
      {==}
    case v <> r:
      %Vals.catnil(r) : {v <> r == v <> _ : List<&2, Core.Val>}
      {==}

# [K{as}]'s value from A.
def Kn.res(+k: String, a: Core.Res) -> Core.Res:
  match a:
    case Core.ROk{vs}:
      Core.ROk{[Core.VCtr{k, vs}]}
    case Core.RFail{m}:
      Core.RFail{m}
    case Core.RNo{}:
      Core.RNo{}
    case Core.REnv{env}:
      Core.REnv{env}

def Kn.nf(+k: String, +a: Core.Res, +h: Red.NotOof(Kn.res(k, a))) -> Red.NotOof(a):
  match a:
    case Core.RFail{m}:
      h
    case Core.ROk{vs}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.REnv{env}:
      Unit{}

def Kn.x(~prim: String -> List<&2, Core.Val> -> Core.Res, +n2: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +a: Core.Res) -> Core.Res:
  Core.run(~prim, 1n+n2, ds, Core.SThen{Core.run(~prim, n2, ds, Core.SThen{a, Core.KCtr{k}}), Core.KTail{env, Nil{}}})

def Kn.x.ok(~prim: String -> List<&2, Core.Val> -> Core.Res, +a: Core.Res, +n2: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, -w: Nat,
    fa: Red.Fits(a, Red.WLen{w}), +nf: Red.NotOof(Kn.x(~prim, n2, ds, env, k, a)))
    -> {Kn.res(k, a) == Kn.x(~prim, n2, ds, env, k, a) : Core.Res}:
  match a:
    case Core.ROk{vs}:
      match n2:
        case 0n:
          match nf:
        case 1n+n3:
          match n3:
            case 0n:
              match nf:
            case 1n+n4:
              match n4:
                case 0n:
                  match nf:
                case 1n+n5:
                  {==}
    case Core.RFail{m}:
      match n2:
        case 0n:
          match nf:
        case 1n+n3:
          {==}
    case Core.RNo{}:
      match fa:
    case Core.REnv{env2}:
      match fa:

# A case of another constructor: its pattern does not match, the next case is taken.
def Skip.eq(~prim: String -> List<&2, Core.Val> -> Core.Res, +g: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +vs: List<&2, Core.Val>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +he: {False{} == String.eq(pk, k) : Bool})
    -> {Core.run(~prim, 1n+g, ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}) == Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}) : Core.Res}:
  %he : {Core.run(~prim, 1n+g, ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}) == Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, 1n+g, ds, Core.SPatC{Bool.and(_, Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(vs))), env, Core.Pts.cat(qs, Nil{}), Core.Vals.cat(vs, Nil{})}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) : Core.Res}
  {==}

def Skip.m(~prim: String -> List<&2, Core.Val> -> Core.Res, +n2: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +vs: List<&2, Core.Val>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +he: {False{} == String.eq(pk, k) : Bool},
    +nf: Red.NotOof(Core.run(~prim, n2, ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r})))
    -> {Core.run(~prim, n2, ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}) == Core.run(~prim, n2, ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}) : Core.Res}:
  match n2:
    case 0n:
      match nf:
    case 1n+n3:
      match n3:
        case 0n:
          match nf:
        case 1n+n4:
          match n4:
            case 0n:
              match nf:
            case 1n+g:
              %Skip.eq(~prim, g, ds, env, k, vs, pk, qs, b, r, he) : {Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}) == _ : Core.Res}
              Res.sym(Core.run(~prim, 1n+g, ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}), Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}),
                RP.L.mono(~prim, 1n+g, 1n+(1n+(1n+g)), RP.Le.succ(1n+g, 1n+(1n+g), RP.Le.succ(1n+g, 1n+g, RP.Le.refl(1n+g))), ds, Core.SMatch{env, [Core.VCtr{k, vs}], r},
                  RP.L.nf.eq(Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}), Core.run(~prim, 1n+g, ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}), Res.sym(Core.run(~prim, 1n+g, ds, Core.SMatch{env, [Core.VCtr{k, vs}], r}), Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}), Skip.eq(~prim, g, ds, env, k, vs, pk, qs, b, r, he)), nf)))

def Skip.a(~prim: String -> List<&2, Core.Val> -> Core.Res, +a: Core.Res, +n2: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, -w: Nat, fa: Red.Fits(a, Red.WLen{w}),
    +he: {False{} == String.eq(pk, k) : Bool}, +nf: Red.NotOof(Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, a), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}})))
    -> {Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, a), Core.KMat{env, r}}) == Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, a), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) : Core.Res}:
  match a:
    case Core.ROk{vs}:
      Skip.m(~prim, n2, ds, env, k, vs, pk, qs, b, r, he, nf)
    case Core.RFail{m}:
      {==}
    case Core.RNo{}:
      match fa:
    case Core.REnv{e2}:
      match fa:

def SkipE(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +N: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +he: {False{} == String.eq(pk, k) : Bool},
    +nf: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}})))
    -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], r}}) == Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) : Core.Res}:
  match N:
    case 0n:
      match nf:
    case 1n+n:
      match n:
        case 0n:
          match nf:
        case 1n+n1:
          match n1:
            case 0n:
              match nf:
            case 1n+n2:
              %Kn.x.ok(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, Red.Tms.len(as), RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), RP.L.nf(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, nf)) : {Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{_, Core.KMat{env, r}}) == Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) : Core.Res}
              %Kn.x.ok(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, Red.Tms.len(as), RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), RP.L.nf(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, nf)) : {Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, r}}) == Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{_, Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) : Core.Res}
              Skip.a(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, pk, qs, b, r, Red.Tms.len(as), RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), he,
                RP.L.nf.eq(Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}), Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}), Then.cong(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, Kn.x.ok(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, Red.Tms.len(as), RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), RP.L.nf(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, nf))), nf))

# K's case: the fields' patterns are variables, as many as the fields.
def Same.len(qs: List<&2, Core.Pt>, as: List<&2, Core.Tm>, vs: List<&2, Core.Val>, hs: Tru(Core.Known.same(qs, as)),
    hl: Red.Len(vs, Red.Tms.len(as)))
    -> {True{} == Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(vs)) : Bool}:
  match qs:
    case Nil{}:
      match as:
        case Nil{}:
          match vs:
            case Nil{}:
              {==}
            case v <> vr:
              match hl:
        case t <> tr:
          match hs:
    case q <> qr:
      match as:
        case Nil{}:
          match hs:
        case t <> tr:
          match vs:
            case Nil{}:
              match hl:
            case v <> vr:
              Same.len(qr, tr, vr, hs, hl)

# Variables always match.
def Vars.nn(~prim: String -> List<&2, Core.Val> -> Core.Res, +g: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, qs: List<&2, Core.Pt>, as: List<&2, Core.Tm>,
    vs: List<&2, Core.Val>, hv: Tru(Core.Known.vars(qs)), hs: Tru(Core.Known.same(qs, as)), hl: Red.Len(vs, Red.Tms.len(as)))
    -> NotNo(Core.run(~prim, g, ds, Core.SPat{env, qs, vs})):
  match g:
    case 0n:
      Unit{}
    case 1n+h:
      match qs:
        case Nil{}:
          match as:
            case Nil{}:
              match vs:
                case Nil{}:
                  Unit{}
                case v <> vr:
                  match hl:
            case t <> tr:
              match hs:
        case q <> qr:
          match q:
            case Core.PtVar{x}:
              match as:
                case Nil{}:
                  match hs:
                case t <> tr:
                  match vs:
                    case Nil{}:
                      match hl:
                    case v <> vr:
                      Vars.nn(~prim, h, ds, Core.VBnd{x, v} <> env, qr, tr, vr, hv, hs, hl)
            case Core.PtCtr{k2, ps2}:
              match hv:
            case Core.PtNat{n}:
              match hv:
            case Core.PtSuc{n, p2}:
              match hv:
            case Core.PtNum{n}:
              match hv:
            case Core.PtFlt{s}:
              match hv:

def Hit.eq(~prim: String -> List<&2, Core.Val> -> Core.Res, +g: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>, +vs: List<&2, Core.Val>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +hl: Red.Len(vs, Red.Tms.len(as)),
    +he: {True{} == String.eq(pk, k) : Bool}, +hs: Tru(Core.Known.same(qs, as)))
    -> {Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) == Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}) : Core.Res}:
  %he : {Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) == Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, 1n+g, ds, Core.SPatC{Bool.and(_, Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(vs))), env, Core.Pts.cat(qs, Nil{}), Core.Vals.cat(vs, Nil{})}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) : Core.Res}
  %Same.len(qs, as, vs, hs, hl) : {Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) == Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, 1n+g, ds, Core.SPatC{Bool.and(True{}, _), env, Core.Pts.cat(qs, Nil{}), Core.Vals.cat(vs, Nil{})}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) : Core.Res}
  %Pts.catnil(qs) : {Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) == Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, _, Core.Vals.cat(vs, Nil{})}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) : Core.Res}
  %Vals.catnil(vs) : {Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) == Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, _}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) : Core.Res}
  {==}

def Hit.p(~prim: String -> List<&2, Core.Val> -> Core.Res, +pr: Core.Res, +g: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +vs: List<&2, Core.Val>, +b: Core.Tm,
    +r: List<&2, Core.Tm>, +w: Core.Val, +nn: NotNo(pr))
    -> {Core.run(~prim, 1n+(1n+g), ds, Core.SThen{pr, Core.KCase{env, [w], b, r}}) == Core.run(~prim, 1n+(1n+g), ds, Core.SThen{pr, Core.KCase{env, vs, b, Nil{}}}) : Core.Res}:
  match pr:
    case Core.RFail{m}:
      {==}
    case Core.REnv{e2}:
      {==}
    case Core.ROk{x}:
      {==}
    case Core.RNo{}:
      match nn:

def Hit.m(~prim: String -> List<&2, Core.Val> -> Core.Res, +n2: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>, +vs: List<&2, Core.Val>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +hl: Red.Len(vs, Red.Tms.len(as)),
    +he: {True{} == String.eq(pk, k) : Bool}, +hv: Tru(Core.Known.vars(qs)), +hs: Tru(Core.Known.same(qs, as)),
    +nf: Red.NotOof(Core.run(~prim, n2, ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r})))
    -> {Core.run(~prim, n2, ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}) == Core.run(~prim, n2, ds, Core.SMatch{env, vs, [Core.CCse{qs, b}]}) : Core.Res}:
  match n2:
    case 0n:
      match nf:
    case 1n+n3:
      match n3:
        case 0n:
          match nf:
        case 1n+n4:
          match n4:
            case 0n:
              match nf:
            case 1n+g:
              %Hit.eq(~prim, g, ds, env, k, as, vs, pk, qs, b, r, hl, he, hs) : {_ == Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, vs, [Core.CCse{qs, b}]}) : Core.Res}
              %RP.L.mono(~prim, g, 1n+(1n+g), RP.Le.succ(g, 1n+g, RP.Le.succ(g, g, RP.Le.refl(g))), ds, Core.SPat{env, qs, vs}, RP.L.nf(~prim, 1n+(1n+g), ds, Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}, RP.L.nf.eq(Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}), Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}), Res.sym(Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}), Core.run(~prim, 1n+(1n+(1n+g)), ds, Core.SMatch{env, [Core.VCtr{k, vs}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}), Hit.eq(~prim, g, ds, env, k, as, vs, pk, qs, b, r, hl, he, hs)), nf))) : {Core.run(~prim, 1n+(1n+g), ds, Core.SThen{Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), Core.KCase{env, [Core.VCtr{k, vs}], b, r}}) == Core.run(~prim, 1n+(1n+g), ds, Core.SThen{_, Core.KCase{env, vs, b, Nil{}}}) : Core.Res}
              Hit.p(~prim, Core.run(~prim, g, ds, Core.SPat{env, qs, vs}), g, ds, env, vs, b, r, Core.VCtr{k, vs}, Vars.nn(~prim, g, ds, env, qs, as, vs, hv, hs, hl))

def Hit.a(~prim: String -> List<&2, Core.Val> -> Core.Res, +a: Core.Res, +n2: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, fa: Red.Fits(a, Red.WLen{Red.Tms.len(as)}),
    +he: {True{} == String.eq(pk, k) : Bool}, +hv: Tru(Core.Known.vars(qs)), +hs: Tru(Core.Known.same(qs, as)),
    +nf: Red.NotOof(Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, a), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}})))
    -> {Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, a), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) == Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{a, Core.KMat{env, [Core.CCse{qs, b}]}}) : Core.Res}:
  match a:
    case Core.ROk{vs}:
      Hit.m(~prim, n2, ds, env, k, as, vs, pk, qs, b, r, fa, he, hv, hs, nf)
    case Core.RFail{m}:
      {==}
    case Core.RNo{}:
      match fa:
    case Core.REnv{e2}:
      match fa:

def HitE(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +N: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +he: {True{} == String.eq(pk, k) : Bool},
    +hv: Tru(Core.Known.vars(qs)), +hs: Tru(Core.Known.same(qs, as)), +nf: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}})))
    -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) == Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{as, [Core.CCse{qs, b}]}}) : Core.Res}:
  match N:
    case 0n:
      match nf:
    case 1n+n:
      match n:
        case 0n:
          match nf:
        case 1n+n1:
          match n1:
            case 0n:
              match nf:
            case 1n+n2:
              %Kn.x.ok(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, Red.Tms.len(as), RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), RP.L.nf(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, nf)) : {Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{_, Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) == Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Core.run(~prim, 1n+(1n+n2), ds, Core.SEvals{env, as}), Core.KMat{env, [Core.CCse{qs, b}]}}) : Core.Res}
              %RP.L.mono(~prim, n2, 1n+(1n+n2), RP.Le.succ(n2, 1n+n2, RP.Le.succ(n2, n2, RP.Le.refl(n2))), ds, Core.SEvals{env, as}, Kn.nf(k, Core.run(~prim, n2, ds, Core.SEvals{env, as}), RP.L.nf.eq(Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Res.sym(Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Kn.x.ok(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, Red.Tms.len(as), RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), RP.L.nf(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, nf))), RP.L.nf(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, nf)))) : {Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) == Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{_, Core.KMat{env, [Core.CCse{qs, b}]}}) : Core.Res}
              Hit.a(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, as, pk, qs, b, r, RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), he, hv, hs,
                RP.L.nf.eq(Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}), Core.run(~prim, 1n+(1n+n2), ds, Core.SThen{Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}), Then.cong(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Kn.res(k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, Kn.x.ok(~prim, Core.run(~prim, n2, ds, Core.SEvals{env, as}), n2, ds, env, k, Red.Tms.len(as), RP.S.one(~prim, ~one, n2, ds, Core.SEvals{env, as}), RP.L.nf(~prim, 1n+(1n+n2), ds, Kn.x(~prim, n2, ds, env, k, Core.run(~prim, n2, ds, Core.SEvals{env, as})), Core.KMat{env, Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}, nf))), nf))

# The rule's choices at K's case: the constructor's name, the fields' patterns.
def KL.s(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +N: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +s: Bool, +hs: {s == Core.Known.same(qs, as) : Bool},
    +hv: {True{} == Core.Known.vars(qs) : Bool}, +he: {True{} == String.eq(pk, k) : Bool}, +nf: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}})))
    -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) == Core.run(~prim, N, ds, Core.SEval{env, Bool.pick(Core.Tm, s, Core.CMat{as, [Core.CCse{qs, b}]}, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r})}) : Core.Res}:
  match s:
    case False{}:
      {==}
    case True{}:
      HitE(~prim, ~one, N, ds, env, k, as, pk, qs, b, r, he, Tru.of(Core.Known.vars(qs), hv), Tru.of(Core.Known.same(qs, as), hs), nf)

def KL.v(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +N: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +v: Bool, +hv: {v == Core.Known.vars(qs) : Bool},
    +he: {True{} == String.eq(pk, k) : Bool}, +nf: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}})))
    -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) == Core.run(~prim, N, ds, Core.SEval{env, Bool.pick(Core.Tm, Bool.and(v, Core.Known.same(qs, as)), Core.CMat{as, [Core.CCse{qs, b}]}, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r})}) : Core.Res}:
  match v:
    case False{}:
      {==}
    case True{}:
      KL.s(~prim, ~one, N, ds, env, k, as, pk, qs, b, r, Core.Known.same(qs, as), {==}, hv, he, nf)

def KL.pick(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +N: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>,
    +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +e: Bool, +he: {e == String.eq(pk, k) : Bool},
    ih: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], r}})) -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], r}}) == Core.run(~prim, N, ds, Core.SEval{env, Core.Known.cases(k, as, r)}) : Core.Res}, +nf: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}})))
    -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}) == Core.run(~prim, N, ds, Core.SEval{env, Bool.pick(Unit -> Core.Tm, e, u => Bool.pick(Core.Tm, Bool.and(Core.Known.vars(qs), Core.Known.same(qs, as)), Core.CMat{as, [Core.CCse{qs, b}]}, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}), u => Core.Known.cases(k, as, r))(Unit{})}) : Core.Res}:
  match e:
    case True{}:
      KL.v(~prim, ~one, N, ds, env, k, as, pk, qs, b, r, Core.Known.vars(qs), {==}, he, nf)
    case False{}:
      %SkipE(~prim, ~one, N, ds, env, k, as, pk, qs, b, r, he, nf) : {_ == Core.run(~prim, N, ds, Core.SEval{env, Core.Known.cases(k, as, r)}) : Core.Res}
      ih(RP.L.nf.eq(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}), Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], r}}), Res.sym(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], r}}), Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}}), SkipE(~prim, ~one, N, ds, env, k, as, pk, qs, b, r, he, nf)), nf))

def KL(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +N: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +k: String, +as: List<&2, Core.Tm>,
    cases: List<&2, Core.Tm>, +nf: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], cases}})))
    -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{[Core.CCtr{k, as}], cases}}) == Core.run(~prim, N, ds, Core.SEval{env, Core.Known.cases(k, as, cases)}) : Core.Res}:
  match cases:
    case Nil{}:
      {==}
    case c <> +r:
      match c:
        case Core.CCse{ps, +b}:
          match ps:
            case Nil{}:
              {==}
            case p <> pr:
              match p:
                case Core.PtCtr{+pk, +qs}:
                  match pr:
                    case Nil{}:
                      KL.pick(~prim, ~one, N, ds, env, k, as, pk, qs, b, r, String.eq(pk, k), {==},
                        h => KL(~prim, ~one, N, ds, env, k, as, r, h), nf)
                    case q <> pr2:
                      {==}
                case Core.PtVar{x}:
                  {==}
                case Core.PtNat{n}:
                  {==}
                case Core.PtSuc{n, p2}:
                  {==}
                case Core.PtNum{n}:
                  {==}
                case Core.PtFlt{s}:
                  {==}

        case Core.CVar{x}:
          {==}
        case Core.CLit{l}:
          {==}
        case Core.CRef{f}:
          {==}
        case Core.CCall{f, as2}:
          {==}
        case Core.CApp{f, as2}:
          {==}
        case Core.CCtr{k2, as2}:
          {==}
        case Core.CLam{pt, bd}:
          {==}
        case Core.CLet{pt, v, bd}:
          {==}
        case Core.CMat{scrs2, cs2}:
          {==}
        case Core.CSuc{n, x}:
          {==}
        case Core.COp{op, x, y}:
          {==}
        case Core.CAnn{x, ty}:
          {==}
        case Core.CTyp{nm, as2}:
          {==}
        case Core.CBox{}:
          {==}
        case Core.CErr{m}:
          {==}

# The rule on a match, in one program.
def K.mat(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +N: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, scrs: List<&2, Core.Tm>, +cases: List<&2, Core.Tm>,
    +nf: Red.NotOof(Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{scrs, cases}})))
    -> {Core.run(~prim, N, ds, Core.SEval{env, Core.CMat{scrs, cases}}) == Core.run(~prim, N, ds, Core.SEval{env, Core.Known.mat(scrs, cases)}) : Core.Res}:
  match scrs:
    case Nil{}:
      {==}
    case s <> r:
      match s:
        case Core.CCtr{+k, +as}:
          match r:
            case Nil{}:
              KL(~prim, ~one, N, ds, env, k, as, cases, nf)
            case t <> r2:
              {==}
        case Core.CVar{x}:
          {==}
        case Core.CLit{l}:
          {==}
        case Core.CRef{f}:
          {==}
        case Core.CCall{f, as2}:
          {==}
        case Core.CApp{f, as2}:
          {==}
        case Core.CLam{pt, bd}:
          {==}
        case Core.CLet{pt, v, bd}:
          {==}
        case Core.CMat{scrs2, cs2}:
          {==}
        case Core.CCse{ps, bd}:
          {==}
        case Core.CSuc{n, x}:
          {==}
        case Core.COp{op, x, y}:
          {==}
        case Core.CAnn{x, ty}:
          {==}
        case Core.CTyp{nm, as2}:
          {==}
        case Core.CBox{}:
          {==}
        case Core.CErr{m}:
          {==}

# A resolved match is a match: as a case, not one.
def NC.pick2(~prim: String -> List<&2, Core.Val> -> Core.Res, +q: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +vs: List<&2, Core.Val>, +rs: List<&2, Core.Tm>,
    +s1: List<&2, Core.Tm>, +c1: List<&2, Core.Tm>, +s2: List<&2, Core.Tm>, +c2: List<&2, Core.Tm>, +h: Bool)
    -> {Core.RFail{"not a case"} == Core.run(~prim, 1n+q, ds, Core.SMatch{env, vs, Bool.pick(Core.Tm, h, Core.CMat{s1, c1}, Core.CMat{s2, c2}) <> rs}) : Core.Res}:
  match h:
    case True{}:
      {==}
    case False{}:
      {==}

def NC.pick(~prim: String -> List<&2, Core.Val> -> Core.Res, +q: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +vs: List<&2, Core.Val>, +rs: List<&2, Core.Tm>,
    +k: String, +as: List<&2, Core.Tm>, +pk: String, +qs: List<&2, Core.Pt>, +b: Core.Tm, +r: List<&2, Core.Tm>, +e: Bool,
    ih: {Core.RFail{"not a case"} == Core.run(~prim, 1n+q, ds, Core.SMatch{env, vs, Core.Known.cases(k, as, r) <> rs}) : Core.Res})
    -> {Core.RFail{"not a case"} == Core.run(~prim, 1n+q, ds, Core.SMatch{env, vs, Bool.pick(Unit -> Core.Tm, e, u => Bool.pick(Core.Tm, Bool.and(Core.Known.vars(qs), Core.Known.same(qs, as)), Core.CMat{as, [Core.CCse{qs, b}]}, Core.CMat{[Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r}), u => Core.Known.cases(k, as, r))(Unit{}) <> rs}) : Core.Res}:
  match e:
    case True{}:
      NC.pick2(~prim, q, ds, env, vs, rs, as, [Core.CCse{qs, b}], [Core.CCtr{k, as}], Core.CCse{[Core.PtCtr{pk, qs}], b} <> r, Bool.and(Core.Known.vars(qs), Core.Known.same(qs, as)))
    case False{}:
      ih

def NC.cases(~prim: String -> List<&2, Core.Val> -> Core.Res, +q: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +vs: List<&2, Core.Val>, +rs: List<&2, Core.Tm>,
    +k: String, +as: List<&2, Core.Tm>, cases: List<&2, Core.Tm>)
    -> {Core.RFail{"not a case"} == Core.run(~prim, 1n+q, ds, Core.SMatch{env, vs, Core.Known.cases(k, as, cases) <> rs}) : Core.Res}:
  match cases:
    case Nil{}:
      {==}
    case c <> +r:
      match c:
        case Core.CCse{ps, +b}:
          match ps:
            case Nil{}:
              {==}
            case p <> pr:
              match p:
                case Core.PtCtr{+pk, +qs}:
                  match pr:
                    case Nil{}:
                      NC.pick(~prim, q, ds, env, vs, rs, k, as, pk, qs, b, r, String.eq(pk, k), NC.cases(~prim, q, ds, env, vs, rs, k, as, r))
                    case q2 <> pr2:
                      {==}
                case Core.PtVar{x}:
                  {==}
                case Core.PtNat{n}:
                  {==}
                case Core.PtSuc{n, p2}:
                  {==}
                case Core.PtNum{n}:
                  {==}
                case Core.PtFlt{s}:
                  {==}

        case Core.CVar{x}:
          {==}
        case Core.CLit{l}:
          {==}
        case Core.CRef{f}:
          {==}
        case Core.CCall{f, as2}:
          {==}
        case Core.CApp{f, as2}:
          {==}
        case Core.CCtr{k2, as2}:
          {==}
        case Core.CLam{pt, bd}:
          {==}
        case Core.CLet{pt, v, bd}:
          {==}
        case Core.CMat{scrs2, cs2}:
          {==}
        case Core.CSuc{n, x}:
          {==}
        case Core.COp{op, x, y}:
          {==}
        case Core.CAnn{x, ty}:
          {==}
        case Core.CTyp{nm, as2}:
          {==}
        case Core.CBox{}:
          {==}
        case Core.CErr{m}:
          {==}

def NC.mat(~prim: String -> List<&2, Core.Val> -> Core.Res, +q: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +vs: List<&2, Core.Val>, +rs: List<&2, Core.Tm>,
    scrs: List<&2, Core.Tm>, +cases: List<&2, Core.Tm>)
    -> {Core.RFail{"not a case"} == Core.run(~prim, 1n+q, ds, Core.SMatch{env, vs, Core.Known.mat(scrs, cases) <> rs}) : Core.Res}:
  match scrs:
    case Nil{}:
      {==}
    case s <> r:
      match s:
        case Core.CCtr{+k, +as}:
          match r:
            case Nil{}:
              NC.cases(~prim, q, ds, env, vs, rs, k, as, cases)
            case t <> r2:
              {==}
        case Core.CVar{x}:
          {==}
        case Core.CLit{l}:
          {==}
        case Core.CRef{f}:
          {==}
        case Core.CCall{f, as2}:
          {==}
        case Core.CApp{f, as2}:
          {==}
        case Core.CLam{pt, bd}:
          {==}
        case Core.CLet{pt, v, bd}:
          {==}
        case Core.CMat{scrs2, cs2}:
          {==}
        case Core.CCse{ps, bd}:
          {==}
        case Core.CSuc{n, x}:
          {==}
        case Core.COp{op, x, y}:
          {==}
        case Core.CAnn{x, ty}:
          {==}
        case Core.CTyp{nm, as2}:
          {==}
        case Core.CBox{}:
          {==}
        case Core.CErr{m}:
          {==}

# A match, resolved: e is the induction hypothesis for the match with its
# fields resolved, and the rule gives the resolved node in the resolved
# program.
def L.matk(~prim: String -> List<&2, Core.Val> -> Core.Res, ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}), +p: Nat, +q: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +scrs: List<&2, Core.Tm>, +cases: List<&2, Core.Tm>,
    +e: {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(env), Core.CMat{Core.Tms.known(scrs), Core.Tms.known(cases)}}) : Core.Res}, +nf: Red.NotOof(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})))
    -> {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(env), Core.Tm.known(Core.CMat{scrs, cases}, True{})}) : Core.Res}:
  %L.mat.top(scrs, cases, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(env), _}) : Core.Res}
  %K.mat(~prim, ~one, 1n+q, Core.Defs.known(ds), Core.Vals.known(env), Core.Tms.known(scrs), Core.Tms.known(cases), RP.L.nf.eq(Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})), Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(env), Core.CMat{Core.Tms.known(scrs), Core.Tms.known(cases)}}), e, L.nf.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}}), nf))) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})) == _ : Core.Res}
  e

# Steps
# =====

# A step that runs x, then k on its result: the outer run and x's run, each
# by the induction hypothesis.
def L.then(~prim: String -> List<&2, Core.Val> -> Core.Res, -p: Nat, -q: Nat, -ds: List<&2, Core.Def>, -x: Core.Sel, -k: Core.Kont,
    e1: {Core.Res.known(Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SThen{Core.Res.known(Core.run(~prim, p, ds, x)), Core.Kont.known(k)}) : Core.Res},
    e2: {Core.Res.known(Core.run(~prim, p, ds, x)) == Core.run(~prim, q, Core.Defs.known(ds), Core.Sel.known(x)) : Core.Res})
    -> {Core.Res.known(Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SThen{Core.run(~prim, q, Core.Defs.known(ds), Core.Sel.known(x)), Core.Kont.known(k)}) : Core.Res}:
  %e2 : {Core.Res.known(Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SThen{_, Core.Kont.known(k)}) : Core.Res}
  e1

def L.known(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.known(prim(op, vs)) == prim(op, Core.Vals.known(vs)) : Core.Res},
    ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}),
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, s: Core.Sel, +nf: Red.NotOof(Core.run(~prim, n, ds, s)))
    -> {Core.Res.known(Core.run(~prim, n, ds, s)) == Core.run(~prim, m, Core.Defs.known(ds), Core.Sel.known(s)) : Core.Res}:
  match n:
    case 0n:
      match nf:
    case 1n+p:
      match m:
        case 0n:
          match le:
        case 1n+q:
          match s:
            case Core.SEval{+env, +e}:
              match e:
                case Core.CVar{+x}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{env, x}, nf)
                case Core.CLit{+l}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, nf)
                case Core.CRef{+f}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SCallDef{f, Nil{}}, nf)
                case Core.CCall{+f, +as}:
                  %L.call(f, as, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CCall{f, as}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(env), _}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SArgs{env, as}, Core.KCall{f},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SArgs{env, as}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}, nf)))
                case Core.CApp{+f, +as}:
                  %L.app(f, as, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{f, as}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(env), _}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SEvals{env, f <> as}, Core.KApp{},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, f <> as}), Core.KApp{}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, f <> as}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, f <> as}), Core.KApp{}, nf)))
                case Core.CCtr{+k, +as}:
                  %L.ctr(k, as, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CCtr{k, as}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(env), _}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SEvals{env, as}, Core.KCtr{k},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, as}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}, nf)))
                case Core.CLam{+pt, +bd}:
                  %L.vclo.rev(env, pt, bd) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CLam{pt, bd}})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SThen{Core.ROk{Nil{}}, Core.KCons{_}}) : Core.Res}
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{env, pt, bd}}}, nf)
                case Core.CLet{+pt, +v, +bd}:
                  L.then(~prim, p, q, ds, Core.SEval{env, v}, Core.KLet{env, pt, bd},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, v}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}, nf)))
                case Core.CMat{+scrs, +cases}:
                  L.matk(~prim, ~one, p, q, ds, env, scrs, cases,
                    L.then(~prim, p, q, ds, Core.SEvals{env, scrs}, Core.KMat{env, cases},
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}}, nf),
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, scrs}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}, nf))),
                    nf)
                case Core.CCse{+ps, +bd}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, nf)
                case Core.CSuc{+k, +x}:
                  L.then(~prim, p, q, ds, Core.SEval{env, x}, Core.KSuc{k},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, x}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}, nf)))
                case Core.COp{+op, +x, +y}:
                  L.then(~prim, p, q, ds, Core.SEvals{env, [x, y]}, Core.KOp{op},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, [x, y]}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}, nf)))
                case Core.CAnn{+x, +ty}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, x}, nf)
                case Core.CTyp{+nm, +as}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, nf)
                case Core.CBox{}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, nf)
                case Core.CErr{+m}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.RFail{m}, Core.KApp{}}, nf)
            case Core.SEvals{+env, +es}:
              match es:
                case Nil{}:
                  {==}
                case +e <> +r:
                  L.then(~prim, p, q, ds, Core.SEval{env, e}, Core.KTail{env, r},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, e}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}, nf)))
            case Core.SArgs{+env, +as}:
              match as:
                case Nil{}:
                  {==}
                case +a <> +r:
                  match a:
                    case Core.Arg{+rel, +e}:
                      match rel:
                        case Core.Run{}:
                          L.then(~prim, p, q, ds, Core.SEval{env, e}, Core.KATail{env, r},
                            L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}}, nf),
                            L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, e}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}, nf)))
                        case Core.Era{}:
                          L.then(~prim, p, q, ds, Core.SArgs{env, r}, Core.KCons{Core.VTrm{e}},
                            L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, r}), Core.KCons{Core.VTrm{e}}}, nf),
                            L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SArgs{env, r}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, r}), Core.KCons{Core.VTrm{e}}, nf)))
            case Core.SThen{+r, +k}:
              match r:
                case Core.RFail{+m}:
                  {==}
                case Core.RNo{}:
                  match k:
                    case Core.KCall{+f}:
                      {==}
                    case Core.KApp{}:
                      {==}
                    case Core.KCtr{+c}:
                      {==}
                    case Core.KLet{+env, +pt, +bd}:
                      {==}
                    case Core.KBind{+bd}:
                      {==}
                    case Core.KMat{+env, +cases}:
                      {==}
                    case Core.KCase{+env, +vs, +bd, +rest}:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SMatch{env, vs, rest}, nf)
                    case Core.KSuc{+c}:
                      {==}
                    case Core.KOp{+op}:
                      {==}
                    case Core.KTail{+env, +es}:
                      {==}
                    case Core.KATail{+env, +as}:
                      {==}
                    case Core.KCons{+v}:
                      {==}
                    case Core.KApply{+vs}:
                      {==}
                    case Core.KBody{+bd, +rest}:
                      {==}
                case Core.REnv{+env2}:
                  match k:
                    case Core.KCall{+f}:
                      {==}
                    case Core.KApp{}:
                      {==}
                    case Core.KCtr{+c}:
                      {==}
                    case Core.KLet{+env, +pt, +bd}:
                      {==}
                    case Core.KBind{+bd}:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env2, bd}, nf)
                    case Core.KMat{+env, +cases}:
                      {==}
                    case Core.KCase{+env, +vs, +bd, +rest}:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env2, bd}, nf)
                    case Core.KSuc{+c}:
                      {==}
                    case Core.KOp{+op}:
                      {==}
                    case Core.KTail{+env, +es}:
                      {==}
                    case Core.KATail{+env, +as}:
                      {==}
                    case Core.KCons{+v}:
                      {==}
                    case Core.KApply{+vs}:
                      {==}
                    case Core.KBody{+bd, +rest}:
                      L.then(~prim, p, q, ds, Core.SEval{env2, bd}, Core.KApply{rest},
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}}, nf),
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env2, bd}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}, nf)))
                case Core.ROk{+vs}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SOk{k, vs}, nf)
            case Core.SOk{+k, +vs}:
              match k:
                case Core.KCall{+f}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SCallDef{f, vs}, nf)
                case Core.KApp{}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +f <> +r2:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SApply{r2, f}, nf)
                case Core.KCtr{+c}:
                  %L.vctr(c, vs) : {Core.ROk{[_]} == Core.ROk{[Core.VCtr{c, Core.Vals.known(vs)}]} : Core.Res}
                  {==}
                case Core.KLet{+env, +pt, +bd}:
                  L.then(~prim, p, q, ds, Core.SPat{env, [pt], vs}, Core.KBind{bd},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, [pt], vs}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}, nf)))
                case Core.KBind{+bd}:
                  {==}
                case Core.KMat{+env, +cases}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SMatch{env, vs, cases}, nf)
                case Core.KCase{+env, +vs2, +bd, +rest}:
                  {==}
                case Core.KSuc{+c}:
                  ok("%suc", Core.VLit{Core.LNum{c}} <> vs)
                case Core.KOp{+op}:
                  ok(op, vs)
                case Core.KTail{+env, +es}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.then(~prim, p, q, ds, Core.SEvals{env, es}, Core.KCons{v},
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}, nf),
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, es}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}, nf)))
                case Core.KATail{+env, +as}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.then(~prim, p, q, ds, Core.SArgs{env, as}, Core.KCons{v},
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}}, nf),
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SArgs{env, as}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}, nf)))
                case Core.KCons{+v}:
                  {==}
                case Core.KApply{+rest}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SApply{rest, v}, nf)
                case Core.KBody{+bd, +rest}:
                  {==}
            case Core.SLook{+env, +x}:
              match env:
                case Nil{}:
                  {==}
                case +bn <> +r:
                  match bn:
                    case Core.VBnd{+y, +v}:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook2{String.eq(y, x), v, r, x}, nf)
                    case Core.VLit{+l}:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VTrm{+t}:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VCtr{+k, +fs}:
                      %L.vctr(k, fs) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VCtr{k, fs} <> r, x})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SLook{_ <> Core.Vals.known(r), x}) : Core.Res}
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VFun{+f, +as}:
                      %L.vfun(f, as) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VFun{f, as} <> r, x})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SLook{_ <> Core.Vals.known(r), x}) : Core.Res}
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VClo{+e2, +pt, +bd}:
                      %L.vclo(e2, pt, bd) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VClo{e2, pt, bd} <> r, x})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SLook{_ <> Core.Vals.known(r), x}) : Core.Res}
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
            case Core.SLook2{+hit, +v, +env, +x}:
              match hit:
                case True{}:
                  {==}
                case False{}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{env, x}, nf)
            case Core.SCallDef{+f, +vs}:
              L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SFind{ds, f, vs}, nf)
            case Core.SFind{+ds2, +f, +vs}:
              match ds2:
                case Nil{}:
                  ok(f, vs)
                case +d <> +r:
                  match d:
                    case Core.Def{+name, +ps, +bd, +ret}:
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SFound{String.eq(name, f), ps, bd, r, f, vs}, nf)
            case Core.SFound{+hit, +ps, +bd, +ds2, +f, +vs}:
              match hit:
                case True{}:
                  %L.len(vs) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, bd, ds2, f, vs})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SEnter{Nat.is_lt(_, Core.Pars.len(ps)), f, ps, Core.Tm.known(bd, True{}), Core.Vals.known(vs)}) : Core.Res}
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, bd, vs}, nf)
                case False{}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SFind{ds2, f, vs}, nf)
            case Core.SEnter{+short, +f, +ps, +bd, +vs}:
              match short:
                case True{}:
                  %L.vfun(f, vs) : {Core.ROk{[_]} == Core.ROk{[Core.VFun{f, Core.Vals.known(vs)}]} : Core.Res}
                  {==}
                case False{}:
                  %L.bind(ps, vs) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, bd, vs})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SThen{Core.run(~prim, q, Core.Defs.known(ds), Core.SEval{_, Core.Tm.known(bd, True{})}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), Core.Vals.known(vs))}}) : Core.Res}
                  %L.drop(Core.Pars.len(ps), vs) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, bd, vs})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SThen{Core.run(~prim, q, Core.Defs.known(ds), Core.SEval{Core.Vals.known(Core.Scope.bind(ps, vs)), Core.Tm.known(bd, True{})}), Core.KApply{_}}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}, Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)},
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}, nf),
                    L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}, nf)))
            case Core.SApply{+vs, +fv}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r:
                  match fv:
                    case Core.VClo{+env, +pt, +bd}:
                      %L.vclo(env, pt, bd) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{env, pt, bd}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SApply{Core.Val.known(v) <> Core.Vals.known(r), _}) : Core.Res}
                      L.then(~prim, p, q, ds, Core.SPat{env, [pt], [v]}, Core.KBody{bd, r},
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}}, nf),
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, [pt], [v]}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}, nf)))
                    case Core.VFun{+f, +as}:
                      %L.vfun(f, as) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SApply{Core.Val.known(v) <> Core.Vals.known(r), _}) : Core.Res}
                      %L.cat(as, v <> r) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}})) == Core.run(~prim, q, Core.Defs.known(ds), Core.SCallDef{f, _}) : Core.Res}
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SCallDef{f, Core.Vals.cat(as, v <> r)}, nf)
                    case Core.VCtr{+k, +fs}:
                      %L.vctr(k, fs) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VCtr{k, fs}})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SApply{Core.Val.known(v) <> Core.Vals.known(r), _}) : Core.Res}
                      {==}
                    case Core.VLit{+l}:
                      {==}
                    case Core.VTrm{+t}:
                      {==}
                    case Core.VBnd{+x, +y}:
                      {==}
            case Core.SMatch{+env, +vs, +cases}:
              match cases:
                case Nil{}:
                  {==}
                case +c <> +r:
                  match c:
                    case Core.CCse{+ps, +bd}:
                      L.then(~prim, p, q, ds, Core.SPat{env, ps, vs}, Core.KCase{env, vs, bd, r},
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}}, nf),
                        L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, ps, vs}, RP.L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}, nf)))
                    case Core.CCall{+f, +as}:
                      %L.call(f, as, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CCall{f, as} <> r})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SMatch{Core.Vals.known(env), Core.Vals.known(vs), _ <> Core.Tms.known(r)}) : Core.Res}
                      {==}
                    case Core.CApp{+f, +as}:
                      %L.app(f, as, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CApp{f, as} <> r})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SMatch{Core.Vals.known(env), Core.Vals.known(vs), _ <> Core.Tms.known(r)}) : Core.Res}
                      {==}
                    case Core.CCtr{+k, +as}:
                      %L.ctr(k, as, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CCtr{k, as} <> r})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SMatch{Core.Vals.known(env), Core.Vals.known(vs), _ <> Core.Tms.known(r)}) : Core.Res}
                      {==}
                    case Core.CMat{+scrs, +cs}:
                      %L.mat.top(scrs, cs, True{}) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CMat{scrs, cs} <> r})) == Core.run(~prim, 1n+q, Core.Defs.known(ds), Core.SMatch{Core.Vals.known(env), Core.Vals.known(vs), _ <> Core.Tms.known(r)}) : Core.Res}
                      NC.mat(~prim, q, Core.Defs.known(ds), Core.Vals.known(env), Core.Vals.known(vs), Core.Tms.known(r), Core.Tms.known(scrs), Core.Tms.known(cs))
                    case Core.CVar{+x}:
                      {==}
                    case Core.CLit{+l}:
                      {==}
                    case Core.CRef{+f}:
                      {==}
                    case Core.CLam{+pt, +bd}:
                      {==}
                    case Core.CLet{+pt, +v, +bd}:
                      {==}
                    case Core.CSuc{+k, +x}:
                      {==}
                    case Core.COp{+op, +x, +y}:
                      {==}
                    case Core.CAnn{+x, +ty}:
                      {==}
                    case Core.CTyp{+nm, +as}:
                      {==}
                    case Core.CBox{}:
                      {==}
                    case Core.CErr{+m}:
                      {==}
            case Core.SPat{+env, +ps, +vs}:
              match ps:
                case Nil{}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r:
                      {==}
                case +pt <> +pr:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +vr:
                      %L.pat(env, pt, v, pr, vr) : {Core.Res.known(Core.run(~prim, 1n+p, ds, Core.SPat{env, pt <> pr, v <> vr})) == Core.run(~prim, q, Core.Defs.known(ds), _) : Core.Res}
                      L.known(~prim, ~ok, ~one, p, q, le, ds, Core.Pat.step(env, pt, v, pr, vr), nf)
            case Core.SPatC{+hit, +env, +ps, +vs}:
              match hit:
                case True{}:
                  L.known(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, ps, vs}, nf)
                case False{}:
                  {==}


def Law.known_ok(prim, ok, one, n, m, le, ds, s, nf):
  L.known(~prim, ~ok, ~one, n, m, le, ds, s, nf)

def Law.known_prog(prim, ok, one, n, m, le, ds, nf):
  L.known(~prim, ~ok, ~one, n, m, le, ds, Core.SCallDef{"main", Nil{}}, nf)
