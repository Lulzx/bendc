import Base
import ./RED.bend as Red
import ./core.bend as Core

# Proof of RED.bend's laws.

# Shapes
# ======

def S.any(r: Core.Res) -> Red.Fits(r, Red.WAny{}):
  match r:
    case Core.ROk{vs}:
      Unit{}
    case Core.RFail{m}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.REnv{env}:
      Unit{}

def S.len(vs: List<&2, Core.Val>) -> Red.Len(vs, Core.Vals.len(vs)):
  match vs:
    case Nil{}:
      Unit{}
    case v <> r:
      S.len(r)

def S.lenval(vs: List<&2, Core.Val>, n: Nat, h: Red.Len(vs, n)) -> {Core.Vals.len(vs) == n : Nat}:
  match vs n:
    case Nil{} 0n:
      {==}
    case v <> r 1n+k:
      %S.lenval(r, k, h) : {1n+Core.Vals.len(r) == 1n+_ : Nat}
      {==}
    case Nil{} 1n+k:
      match h:
    case v <> r 0n:
      match h:

def S.fail(~prim: String -> List<&2, Core.Val> -> Core.Res, p: Nat, ds: List<&2, Core.Def>, m: String, k: Core.Kont, w: Red.Want)
    -> Red.Fits(Core.run(~prim, p, ds, Core.SThen{Core.RFail{m}, k}), w):
  match p:
    case 0n:
      Unit{}
    case 1n+q:
      Unit{}

# A list's tail evaluated after its head: as many values as terms.
def S.tail(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, x: Core.Res, v: Core.Val, es: List<&2, Core.Tm>,
    hx: Red.Fits(x, Red.WLen{Red.Tms.len(es)}),
    hy: Red.Fits(Core.run(~prim, p, ds, Core.SThen{x, Core.KCons{v}}), Red.WLen{1n+Red.Res.len(x)}))
    -> Red.Fits(Core.run(~prim, p, ds, Core.SThen{x, Core.KCons{v}}), Red.WLen{1n+Red.Tms.len(es)}):
  match x:
    case Core.ROk{vs}:
      %S.lenval(vs, Red.Tms.len(es), hx) : Red.Fits(Core.run(~prim, p, ds, Core.SThen{Core.ROk{vs}, Core.KCons{v}}), Red.WLen{1n+_})
      hy
    case Core.RFail{m}:
      S.fail(~prim, p, ds, m, Core.KCons{v}, Red.WLen{1n+Red.Tms.len(es)})
    case Core.RNo{}:
      match hx:
    case Core.REnv{env}:
      match hx:

def S.one(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}),
    +n: Nat, +ds: List<&2, Core.Def>, s: Core.Sel)
    -> Red.Fits(Core.run(~prim, n, ds, s), Red.Sel.want(s)):
  match n:
    case 0n:
      Unit{}
    case 1n+p:
      match s:
        case Core.SEval{+env, +e}:
          match e:
            case Core.CVar{+x}:
              S.one(~prim, ~one, p, ds, Core.SLook{env, x})
            case Core.CLit{+l}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}})
            case Core.CRef{+f}:
              S.one(~prim, ~one, p, ds, Core.SCallDef{f, Nil{}})
            case Core.CCall{+f, +as}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}})
            case Core.CApp{+f, +as}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, f <> as}), Core.KApp{}})
            case Core.CCtr{+k, +as}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}})
            case Core.CLam{+pt, +bd}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{env, pt, bd}}})
            case Core.CLet{+pt, +v, +bd}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}})
            case Core.CMat{+scrs, +cases}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}})
            case Core.CCse{+ps, +bd}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}})
            case Core.CSuc{+k, +x}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}})
            case Core.COp{+op, +x, +y}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}})
            case Core.CAnn{+x, +ty}:
              S.one(~prim, ~one, p, ds, Core.SEval{env, x})
            case Core.CTyp{+nm, +as}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}})
            case Core.CBox{}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}})
            case Core.CErr{+m}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.RFail{m}, Core.KApp{}})
        case Core.SEvals{+env, +es}:
          match es:
            case Nil{}:
              Unit{}
            case +e <> +r:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}})
        case Core.SArgs{+env, +as}:
          S.any(Core.run(~prim, 1n+p, ds, Core.SArgs{env, as}))
        case Core.SThen{+r, +k}:
          match r:
            case Core.RFail{+m}:
              Unit{}
            case Core.RNo{}:
              match k:
                case Core.KCall{+f}:
                  Unit{}
                case Core.KApp{}:
                  Unit{}
                case Core.KCtr{+c}:
                  Unit{}
                case Core.KLet{+env, +pt, +bd}:
                  Unit{}
                case Core.KBind{+bd}:
                  Unit{}
                case Core.KMat{+env, +cases}:
                  Unit{}
                case Core.KCase{+env, +vs, +bd, +rest}:
                  S.one(~prim, ~one, p, ds, Core.SMatch{env, vs, rest})
                case Core.KSuc{+c}:
                  Unit{}
                case Core.KOp{+op}:
                  Unit{}
                case Core.KTail{+env, +es}:
                  Unit{}
                case Core.KATail{+env, +as}:
                  Unit{}
                case Core.KCons{+v}:
                  Unit{}
                case Core.KApply{+vs}:
                  Unit{}
                case Core.KBody{+bd, +rest}:
                  Unit{}
            case Core.REnv{+env2}:
              match k:
                case Core.KCall{+f}:
                  Unit{}
                case Core.KApp{}:
                  Unit{}
                case Core.KCtr{+c}:
                  Unit{}
                case Core.KLet{+env, +pt, +bd}:
                  Unit{}
                case Core.KBind{+bd}:
                  S.one(~prim, ~one, p, ds, Core.SEval{env2, bd})
                case Core.KMat{+env, +cases}:
                  Unit{}
                case Core.KCase{+env, +vs, +bd, +rest}:
                  S.one(~prim, ~one, p, ds, Core.SEval{env2, bd})
                case Core.KSuc{+c}:
                  Unit{}
                case Core.KOp{+op}:
                  Unit{}
                case Core.KTail{+env, +es}:
                  Unit{}
                case Core.KATail{+env, +as}:
                  Unit{}
                case Core.KCons{+v}:
                  Unit{}
                case Core.KApply{+vs}:
                  Unit{}
                case Core.KBody{+bd, +rest}:
                  S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}})
            case Core.ROk{+vs}:
              S.one(~prim, ~one, p, ds, Core.SOk{k, vs})
        case Core.SOk{+k, +vs}:
          match k:
            case Core.KCall{+f}:
              S.one(~prim, ~one, p, ds, Core.SCallDef{f, vs})
            case Core.KApp{}:
              match vs:
                case Nil{}:
                  Unit{}
                case +f <> +r2:
                  S.one(~prim, ~one, p, ds, Core.SApply{r2, f})
            case Core.KCtr{+c}:
              Unit{}
            case Core.KLet{+env, +pt, +bd}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}})
            case Core.KBind{+bd}:
              Unit{}
            case Core.KMat{+env, +cases}:
              S.one(~prim, ~one, p, ds, Core.SMatch{env, vs, cases})
            case Core.KCase{+env, +vs2, +bd, +rest}:
              Unit{}
            case Core.KSuc{+c}:
              one("%suc", Core.VLit{Core.LNum{c}} <> vs)
            case Core.KOp{+op}:
              one(op, vs)
            case Core.KTail{+env, +es}:
              match vs:
                case Nil{}:
                  Unit{}
                case +v <> +r2:
                  S.tail(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, es}), v, es,
                    S.one(~prim, ~one, p, ds, Core.SEvals{env, es}),
                    S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}))
            case Core.KATail{+env, +as}:
              S.any(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KATail{env, as}, vs}))
            case Core.KCons{+v}:
              S.len(vs)
            case Core.KApply{+rest}:
              match vs:
                case Nil{}:
                  Unit{}
                case +v <> +r2:
                  S.one(~prim, ~one, p, ds, Core.SApply{rest, v})
            case Core.KBody{+bd, +rest}:
              Unit{}
        case Core.SLook{+env, +x}:
          match env:
            case Nil{}:
              Unit{}
            case +bn <> +r:
              match bn:
                case Core.VBnd{+y, +v}:
                  S.one(~prim, ~one, p, ds, Core.SLook2{String.eq(y, x), v, r, x})
                case Core.VLit{+l}:
                  S.one(~prim, ~one, p, ds, Core.SLook{r, x})
                case Core.VTrm{+t}:
                  S.one(~prim, ~one, p, ds, Core.SLook{r, x})
                case Core.VCtr{+k, +fs}:
                  S.one(~prim, ~one, p, ds, Core.SLook{r, x})
                case Core.VFun{+f, +as}:
                  S.one(~prim, ~one, p, ds, Core.SLook{r, x})
                case Core.VClo{+e2, +pt, +bd}:
                  S.one(~prim, ~one, p, ds, Core.SLook{r, x})
        case Core.SLook2{+hit, +v, +env, +x}:
          match hit:
            case True{}:
              Unit{}
            case False{}:
              S.one(~prim, ~one, p, ds, Core.SLook{env, x})
        case Core.SCallDef{+f, +vs}:
          S.one(~prim, ~one, p, ds, Core.SFind{ds, f, vs})
        case Core.SFind{+ds2, +f, +vs}:
          match ds2:
            case Nil{}:
              one(f, vs)
            case +d <> +r:
              match d:
                case Core.Def{+name, +ps, +bd, +ret}:
                  S.one(~prim, ~one, p, ds, Core.SFound{String.eq(name, f), ps, bd, r, f, vs})
        case Core.SFound{+hit, +ps, +bd, +ds2, +f, +vs}:
          match hit:
            case True{}:
              S.one(~prim, ~one, p, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, bd, vs})
            case False{}:
              S.one(~prim, ~one, p, ds, Core.SFind{ds2, f, vs})
        case Core.SEnter{+short, +f, +ps, +bd, +vs}:
          match short:
            case True{}:
              Unit{}
            case False{}:
              S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}})
        case Core.SApply{+vs, +fv}:
          match vs:
            case Nil{}:
              Unit{}
            case +v <> +r:
              match fv:
                case Core.VClo{+env, +pt, +bd}:
                  S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}})
                case Core.VFun{+f, +as}:
                  S.one(~prim, ~one, p, ds, Core.SCallDef{f, Core.Vals.cat(as, v <> r)})
                case Core.VCtr{+k, +fs}:
                  Unit{}
                case Core.VLit{+l}:
                  Unit{}
                case Core.VTrm{+t}:
                  Unit{}
                case Core.VBnd{+x, +y}:
                  Unit{}
        case Core.SMatch{+env, +vs, +cases}:
          match cases:
            case Nil{}:
              Unit{}
            case +c <> +r:
              match c:
                case Core.CCse{+ps, +bd}:
                  S.one(~prim, ~one, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}})
                case Core.CCall{+f, +as}:
                  Unit{}
                case Core.CApp{+f, +as}:
                  Unit{}
                case Core.CCtr{+k, +as}:
                  Unit{}
                case Core.CMat{+scrs, +cs}:
                  Unit{}
                case Core.CVar{+x}:
                  Unit{}
                case Core.CLit{+l}:
                  Unit{}
                case Core.CRef{+f}:
                  Unit{}
                case Core.CLam{+pt, +bd}:
                  Unit{}
                case Core.CLet{+pt, +v, +bd}:
                  Unit{}
                case Core.CSuc{+k, +x}:
                  Unit{}
                case Core.COp{+op, +x, +y}:
                  Unit{}
                case Core.CAnn{+x, +ty}:
                  Unit{}
                case Core.CTyp{+nm, +as}:
                  Unit{}
                case Core.CBox{}:
                  Unit{}
                case Core.CErr{+m}:
                  Unit{}
        case Core.SPat{+env, +ps, +vs}:
          S.any(Core.run(~prim, 1n+p, ds, Core.SPat{env, ps, vs}))
        case Core.SPatC{+hit, +env, +ps, +vs}:
          S.any(Core.run(~prim, 1n+p, ds, Core.SPatC{hit, env, ps, vs}))

# Shapes
# ======

# Tm.red and Val.red walk a list field as its head and the node rebuilt
# with the rest; these give the node with the field reduced as a whole. The
# rest is not a node of the term (top is False there): no redex is made of it.

def L.call(f: String, as: List<&2, Core.Arg>, top: Bool)
    -> {Core.CCall{f, Core.Args.red(as)} == Core.Tm.red(Core.CCall{f, as}, top) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          %L.call(f, r, False{}) : {Core.CCall{f, Core.Arg{rel, Core.Tm.red(e, True{})} <> Core.Args.red(r)} == Core.Tm.push.call(Core.Arg{rel, Core.Tm.red(e, True{})}, _) : Core.Tm}
          {==}

def L.app(f: Core.Tm, as: List<&2, Core.Tm>)
    -> {Core.CApp{Core.Tm.red(f, True{}), Core.Tms.red(as)} == Core.Tm.red(Core.CApp{f, as}, False{}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.app(f, r) : {Core.CApp{Core.Tm.red(f, True{}), Core.Tm.red(a, True{}) <> Core.Tms.red(r)} == Core.Tm.push(Core.Tm.red(a, True{}), _) : Core.Tm}
      {==}

def L.ctr(k: String, as: List<&2, Core.Tm>, top: Bool)
    -> {Core.CCtr{k, Core.Tms.red(as)} == Core.Tm.red(Core.CCtr{k, as}, top) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.ctr(k, r, False{}) : {Core.CCtr{k, Core.Tm.red(a, True{}) <> Core.Tms.red(r)} == Core.Tm.push(Core.Tm.red(a, True{}), _) : Core.Tm}
      {==}

def L.mat.cases(cs: List<&2, Core.Tm>, top: Bool)
    -> {Core.CMat{Nil{}, Core.Tms.red(cs)} == Core.Tm.red(Core.CMat{Nil{}, cs}, top) : Core.Tm}:
  match cs:
    case Nil{}:
      {==}
    case c <> r:
      %L.mat.cases(r, False{}) : {Core.CMat{Nil{}, Core.Tm.red(c, True{}) <> Core.Tms.red(r)} == Core.Tm.push.case(Core.Tm.red(c, True{}), _) : Core.Tm}
      {==}

def L.mat(scrs: List<&2, Core.Tm>, cs: List<&2, Core.Tm>, top: Bool)
    -> {Core.CMat{Core.Tms.red(scrs), Core.Tms.red(cs)} == Core.Tm.red(Core.CMat{scrs, cs}, top) : Core.Tm}:
  match scrs:
    case Nil{}:
      L.mat.cases(cs, top)
    case a <> r:
      %L.mat(r, cs, False{}) : {Core.CMat{Core.Tm.red(a, True{}) <> Core.Tms.red(r), Core.Tms.red(cs)} == Core.Tm.push(Core.Tm.red(a, True{}), _) : Core.Tm}
      {==}

def L.vctr(k: String, fs: List<&2, Core.Val>)
    -> {Core.VCtr{k, Core.Vals.red(fs)} == Core.Val.red(Core.VCtr{k, fs}) : Core.Val}:
  match fs:
    case Nil{}:
      {==}
    case f <> r:
      %L.vctr(k, r) : {Core.VCtr{k, Core.Val.red(f) <> Core.Vals.red(r)} == Core.Val.push(Core.Val.red(f), _) : Core.Val}
      {==}

def L.vfun(g: String, as: List<&2, Core.Val>)
    -> {Core.VFun{g, Core.Vals.red(as)} == Core.Val.red(Core.VFun{g, as}) : Core.Val}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.vfun(g, r) : {Core.VFun{g, Core.Val.red(a) <> Core.Vals.red(r)} == Core.Val.push(Core.Val.red(a), _) : Core.Val}
      {==}

def L.vclo(env: List<&2, Core.Val>, pt: Core.Pt, bd: Core.Tm)
    -> {Core.VClo{Core.Vals.red(env), pt, Core.Tm.red(bd, True{})} == Core.Val.red(Core.VClo{env, pt, bd}) : Core.Val}:
  match env:
    case Nil{}:
      {==}
    case e <> r:
      %L.vclo(r, pt, bd) : {Core.VClo{Core.Val.red(e) <> Core.Vals.red(r), pt, Core.Tm.red(bd, True{})} == Core.Val.push.env(Core.Val.red(e), _) : Core.Val}
      {==}

def L.vclo.rev(env: List<&2, Core.Val>, pt: Core.Pt, bd: Core.Tm)
    -> {Core.Val.red(Core.VClo{env, pt, bd}) == Core.VClo{Core.Vals.red(env), pt, Core.Tm.red(bd, True{})} : Core.Val}:
  %L.vclo(env, pt, bd) : {_ == Core.VClo{Core.Vals.red(env), pt, Core.Tm.red(bd, True{})} : Core.Val}
  {==}

# Lists
# =====

def L.len(vs: List<&2, Core.Val>) -> {Core.Vals.len(vs) == Core.Vals.len(Core.Vals.red(vs)) : Nat}:
  match vs:
    case Nil{}:
      {==}
    case v <> r:
      %L.len(r) : {1n+Core.Vals.len(r) == 1n+_ : Nat}
      {==}

def L.cat(a: List<&2, Core.Val>, b: List<&2, Core.Val>)
    -> {Core.Vals.red(Core.Vals.cat(a, b)) == Core.Vals.cat(Core.Vals.red(a), Core.Vals.red(b)) : List<&2, Core.Val>}:
  match a:
    case Nil{}:
      {==}
    case v <> r:
      %L.cat(r, b) : {Core.Val.red(v) <> Core.Vals.red(Core.Vals.cat(r, b)) == Core.Val.red(v) <> _ : List<&2, Core.Val>}
      {==}

def L.drop(n: Nat, vs: List<&2, Core.Val>)
    -> {Core.Vals.red(Core.Vals.drop(n, vs)) == Core.Vals.drop(n, Core.Vals.red(vs)) : List<&2, Core.Val>}:
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
    -> {Core.Vals.red(Core.Scope.bind(ps, vs)) == Core.Scope.bind(ps, Core.Vals.red(vs)) : List<&2, Core.Val>}:
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
              %L.bind(pr, vr) : {Core.VBnd{x, Core.Val.red(v)} <> Core.Vals.red(Core.Scope.bind(pr, vr)) == Core.VBnd{x, Core.Val.red(v)} <> _ : List<&2, Core.Val>}
              {==}

# Patterns
# ========

def L.pat(env: List<&2, Core.Val>, pt: Core.Pt, v: Core.Val, ps: List<&2, Core.Pt>, vs: List<&2, Core.Val>)
    -> {Core.Sel.red(Core.Pat.step(env, pt, v, ps, vs)) == Core.Pat.step(Core.Vals.red(env), pt, Core.Val.red(v), ps, Core.Vals.red(vs)) : Core.Sel}:
  match pt:
    case Core.PtVar{x}:
      {==}
    case Core.PtCtr{k, qs}:
      match v:
        case Core.VCtr{k2, +fs}:
          %L.vctr(k2, fs) : {Core.Sel.red(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          %L.len(fs) : {Core.Sel.red(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.SPatC{Bool.and(String.eq(k, k2), Nat.is_eq(Core.Pts.len(qs), _)), Core.Vals.red(env), Core.Pts.cat(qs, ps), Core.Vals.cat(Core.Vals.red(fs), Core.Vals.red(vs))} : Core.Sel}
          %L.cat(fs, vs) : {Core.Sel.red(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.SPatC{Bool.and(String.eq(k, k2), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs))), Core.Vals.red(env), Core.Pts.cat(qs, ps), _} : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.red(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.red(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.red(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.red(Core.Pat.step(env, Core.PtNat{n}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtNat{n}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.red(Core.Pat.step(env, Core.PtNat{n}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtNat{n}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.red(Core.Pat.step(env, Core.PtNat{n}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtNat{n}, _, ps, Core.Vals.red(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.red(Core.Pat.step(env, Core.PtNum{n}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtNum{n}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.red(Core.Pat.step(env, Core.PtNum{n}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtNum{n}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.red(Core.Pat.step(env, Core.PtNum{n}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtNum{n}, _, ps, Core.Vals.red(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.red(Core.Pat.step(env, Core.PtFlt{s}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtFlt{s}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.red(Core.Pat.step(env, Core.PtFlt{s}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtFlt{s}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.red(Core.Pat.step(env, Core.PtFlt{s}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtFlt{s}, _, ps, Core.Vals.red(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.red(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtSuc{k, q}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.red(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtSuc{k, q}, _, ps, Core.Vals.red(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.red(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.red(env), Core.PtSuc{k, q}, _, ps, Core.Vals.red(vs)) : Core.Sel}
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

def Le.succ(+a: Nat, +b: Nat, +h: Red.Le(a, b)) -> Red.Le(a, 1n+b):
  match a:
    case 0n:
      Unit{}
    case 1n+x:
      match b:
        case 0n:
          match h:
        case 1n+y:
          Le.succ(x, y, h)

def Le.refl(+a: Nat) -> Red.Le(a, a):
  match a:
    case 0n:
      Unit{}
    case 1n+x:
      Le.refl(x)

def L.nf.fail(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +m: String, +k: Core.Kont,
    +h: Red.NotOof(Core.run(~prim, p, ds, Core.SThen{Core.RFail{m}, k})))
    -> Red.NotOof(Core.RFail{m}):
  match p:
    case 0n:
      match h:
    case 1n+q:
      h

# A step that runs x then k does not run out of fuel if the whole does not.
def L.nf(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +r: Core.Res, +k: Core.Kont,
    +h: Red.NotOof(Core.run(~prim, p, ds, Core.SThen{r, k})))
    -> Red.NotOof(r):
  match r:
    case Core.RFail{m}:
      L.nf.fail(~prim, p, ds, m, k, h)
    case Core.ROk{vs}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.REnv{env}:
      Unit{}

def L.nf.red(+r: Core.Res, +h: Red.NotOof(r)) -> Red.NotOof(Core.Res.red(r)):
  match r:
    case Core.RFail{m}:
      h
    case Core.ROk{vs}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.REnv{env}:
      Unit{}

def L.nf.eq(-x: Core.Res, -y: Core.Res, e: {x == y : Core.Res}, h: Red.NotOof(x)) -> Red.NotOof(y):
  %e : Red.NotOof(_)
  h

# Fuel monotonicity
# ==================

def L.mono.then(~prim: String -> List<&2, Core.Val> -> Core.Res, -p: Nat, -q: Nat, -ds: List<&2, Core.Def>, -x: Core.Sel, -k: Core.Kont,
    e1: {Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k}) == Core.run(~prim, q, ds, Core.SThen{Core.run(~prim, p, ds, x), k}) : Core.Res},
    e2: {Core.run(~prim, p, ds, x) == Core.run(~prim, q, ds, x) : Core.Res})
    -> {Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k}) == Core.run(~prim, q, ds, Core.SThen{Core.run(~prim, q, ds, x), k}) : Core.Res}:
  %e2 : {Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k}) == Core.run(~prim, q, ds, Core.SThen{_, k}) : Core.Res}
  e1

# More fuel gives the same result, if the run does not run out of it.
def L.mono(~prim: String -> List<&2, Core.Val> -> Core.Res,
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, s: Core.Sel, +nf: Red.NotOof(Core.run(~prim, n, ds, s)))
    -> {Core.run(~prim, n, ds, s) == Core.run(~prim, m, ds, s) : Core.Res}:
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
                  L.mono(~prim, p, q, le, ds, Core.SLook{env, x}, nf)
                case Core.CLit{+l}:
                  L.mono(~prim, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, nf)
                case Core.CRef{+f}:
                  L.mono(~prim, p, q, le, ds, Core.SCallDef{f, Nil{}}, nf)
                case Core.CCall{+f, +as}:
                  L.mono.then(~prim, p, q, ds, Core.SArgs{env, as}, Core.KCall{f},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SArgs{env, as}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}, nf)))
                case Core.CApp{+f, +as}:
                  L.mono.then(~prim, p, q, ds, Core.SEvals{env, f <> as}, Core.KApp{},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, f <> as}), Core.KApp{}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEvals{env, f <> as}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, f <> as}), Core.KApp{}, nf)))
                case Core.CCtr{+k, +as}:
                  L.mono.then(~prim, p, q, ds, Core.SEvals{env, as}, Core.KCtr{k},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEvals{env, as}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}, nf)))
                case Core.CLam{+pt, +bd}:
                  L.mono(~prim, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{env, pt, bd}}}, nf)
                case Core.CLet{+pt, +v, +bd}:
                  L.mono.then(~prim, p, q, ds, Core.SEval{env, v}, Core.KLet{env, pt, bd},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEval{env, v}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}, nf)))
                case Core.CMat{+scrs, +cases}:
                  L.mono.then(~prim, p, q, ds, Core.SEvals{env, scrs}, Core.KMat{env, cases},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEvals{env, scrs}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}, nf)))
                case Core.CCse{+ps, +bd}:
                  L.mono(~prim, p, q, le, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, nf)
                case Core.CSuc{+k, +x}:
                  L.mono.then(~prim, p, q, ds, Core.SEval{env, x}, Core.KSuc{k},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEval{env, x}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}, nf)))
                case Core.COp{+op, +x, +y}:
                  L.mono.then(~prim, p, q, ds, Core.SEvals{env, [x, y]}, Core.KOp{op},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEvals{env, [x, y]}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}, nf)))
                case Core.CAnn{+x, +ty}:
                  L.mono(~prim, p, q, le, ds, Core.SEval{env, x}, nf)
                case Core.CTyp{+nm, +as}:
                  L.mono(~prim, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, nf)
                case Core.CBox{}:
                  L.mono(~prim, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, nf)
                case Core.CErr{+m}:
                  L.mono(~prim, p, q, le, ds, Core.SThen{Core.RFail{m}, Core.KApp{}}, nf)
            case Core.SEvals{+env, +es}:
              match es:
                case Nil{}:
                  {==}
                case +e <> +r:
                  L.mono.then(~prim, p, q, ds, Core.SEval{env, e}, Core.KTail{env, r},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEval{env, e}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}, nf)))
            case Core.SArgs{+env, +as}:
              match as:
                case Nil{}:
                  {==}
                case +a <> +r:
                  match a:
                    case Core.Arg{+rel, +e}:
                      match rel:
                        case Core.Run{}:
                          L.mono.then(~prim, p, q, ds, Core.SEval{env, e}, Core.KATail{env, r},
                            L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}}, nf),
                            L.mono(~prim, p, q, le, ds, Core.SEval{env, e}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}, nf)))
                        case Core.Era{}:
                          L.mono.then(~prim, p, q, ds, Core.SArgs{env, r}, Core.KCons{Core.VTrm{e}},
                            L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, r}), Core.KCons{Core.VTrm{e}}}, nf),
                            L.mono(~prim, p, q, le, ds, Core.SArgs{env, r}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, r}), Core.KCons{Core.VTrm{e}}, nf)))
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
                      L.mono(~prim, p, q, le, ds, Core.SMatch{env, vs, rest}, nf)
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
                      L.mono(~prim, p, q, le, ds, Core.SEval{env2, bd}, nf)
                    case Core.KMat{+env, +cases}:
                      {==}
                    case Core.KCase{+env, +vs, +bd, +rest}:
                      L.mono(~prim, p, q, le, ds, Core.SEval{env2, bd}, nf)
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
                      L.mono.then(~prim, p, q, ds, Core.SEval{env2, bd}, Core.KApply{rest},
                        L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}}, nf),
                        L.mono(~prim, p, q, le, ds, Core.SEval{env2, bd}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}, nf)))
                case Core.ROk{+vs}:
                  L.mono(~prim, p, q, le, ds, Core.SOk{k, vs}, nf)
            case Core.SOk{+k, +vs}:
              match k:
                case Core.KCall{+f}:
                  L.mono(~prim, p, q, le, ds, Core.SCallDef{f, vs}, nf)
                case Core.KApp{}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +f <> +r2:
                      L.mono(~prim, p, q, le, ds, Core.SApply{r2, f}, nf)
                case Core.KCtr{+c}:
                  {==}
                case Core.KLet{+env, +pt, +bd}:
                  L.mono.then(~prim, p, q, ds, Core.SPat{env, [pt], vs}, Core.KBind{bd},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SPat{env, [pt], vs}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}, nf)))
                case Core.KBind{+bd}:
                  {==}
                case Core.KMat{+env, +cases}:
                  L.mono(~prim, p, q, le, ds, Core.SMatch{env, vs, cases}, nf)
                case Core.KCase{+env, +vs2, +bd, +rest}:
                  {==}
                case Core.KSuc{+c}:
                  {==}
                case Core.KOp{+op}:
                  {==}
                case Core.KTail{+env, +es}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.mono.then(~prim, p, q, ds, Core.SEvals{env, es}, Core.KCons{v},
                        L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}, nf),
                        L.mono(~prim, p, q, le, ds, Core.SEvals{env, es}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}, nf)))
                case Core.KATail{+env, +as}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.mono.then(~prim, p, q, ds, Core.SArgs{env, as}, Core.KCons{v},
                        L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}}, nf),
                        L.mono(~prim, p, q, le, ds, Core.SArgs{env, as}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}, nf)))
                case Core.KCons{+v}:
                  {==}
                case Core.KApply{+rest}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.mono(~prim, p, q, le, ds, Core.SApply{rest, v}, nf)
                case Core.KBody{+bd, +rest}:
                  {==}
            case Core.SLook{+env, +x}:
              match env:
                case Nil{}:
                  {==}
                case +bn <> +r:
                  match bn:
                    case Core.VBnd{+y, +v}:
                      L.mono(~prim, p, q, le, ds, Core.SLook2{String.eq(y, x), v, r, x}, nf)
                    case Core.VLit{+l}:
                      L.mono(~prim, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VTrm{+t}:
                      L.mono(~prim, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VCtr{+k, +fs}:
                      L.mono(~prim, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VFun{+f, +as}:
                      L.mono(~prim, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VClo{+e2, +pt, +bd}:
                      L.mono(~prim, p, q, le, ds, Core.SLook{r, x}, nf)
            case Core.SLook2{+hit, +v, +env, +x}:
              match hit:
                case True{}:
                  {==}
                case False{}:
                  L.mono(~prim, p, q, le, ds, Core.SLook{env, x}, nf)
            case Core.SCallDef{+f, +vs}:
              L.mono(~prim, p, q, le, ds, Core.SFind{ds, f, vs}, nf)
            case Core.SFind{+ds2, +f, +vs}:
              match ds2:
                case Nil{}:
                  {==}
                case +d <> +r:
                  match d:
                    case Core.Def{+name, +ps, +bd, +ret}:
                      L.mono(~prim, p, q, le, ds, Core.SFound{String.eq(name, f), ps, bd, r, f, vs}, nf)
            case Core.SFound{+hit, +ps, +bd, +ds2, +f, +vs}:
              match hit:
                case True{}:
                  L.mono(~prim, p, q, le, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, bd, vs}, nf)
                case False{}:
                  L.mono(~prim, p, q, le, ds, Core.SFind{ds2, f, vs}, nf)
            case Core.SEnter{+short, +f, +ps, +bd, +vs}:
              match short:
                case True{}:
                  {==}
                case False{}:
                  L.mono.then(~prim, p, q, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}, Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)},
                    L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}, nf),
                    L.mono(~prim, p, q, le, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}, nf)))
            case Core.SApply{+vs, +fv}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r:
                  match fv:
                    case Core.VClo{+env, +pt, +bd}:
                      L.mono.then(~prim, p, q, ds, Core.SPat{env, [pt], [v]}, Core.KBody{bd, r},
                        L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}}, nf),
                        L.mono(~prim, p, q, le, ds, Core.SPat{env, [pt], [v]}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}, nf)))
                    case Core.VFun{+f, +as}:
                      L.mono(~prim, p, q, le, ds, Core.SCallDef{f, Core.Vals.cat(as, v <> r)}, nf)
                    case Core.VCtr{+k, +fs}:
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
                      L.mono.then(~prim, p, q, ds, Core.SPat{env, ps, vs}, Core.KCase{env, vs, bd, r},
                        L.mono(~prim, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}}, nf),
                        L.mono(~prim, p, q, le, ds, Core.SPat{env, ps, vs}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}, nf)))
                    case Core.CCall{+f, +as}:
                      {==}
                    case Core.CApp{+f, +as}:
                      {==}
                    case Core.CCtr{+k, +as}:
                      {==}
                    case Core.CMat{+scrs, +cs}:
                      {==}
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
                      L.mono(~prim, p, q, le, ds, Core.Pat.step(env, pt, v, pr, vr), nf)
            case Core.SPatC{+hit, +env, +ps, +vs}:
              match hit:
                case True{}:
                  L.mono(~prim, p, q, le, ds, Core.SPat{env, ps, vs}, nf)
                case False{}:
                  {==}

# The redex
# =========

# The source runs (CLam{pt, bd})(a) as: a to A, then the closure applied to
# A's value: pt against it to P, then bd in P's scope to B. The let runs a,
# pt and bd the same, in fewer steps. These give the states of P's and B's
# runs from A and P (or one that does not run out of fuel), so that the
# induction hypothesis can be taken at them before A and P are known.

def Beta.none() -> Core.Sel:
  Core.SPat{Nil{}, Nil{}, Nil{}}

def Beta.pat(+env: List<&2, Core.Val>, +pt: Core.Pt, +a: Core.Res) -> Core.Sel:
  match a:
    case Core.ROk{vs}:
      match vs:
        case v <> r:
          Core.SPat{env, [pt], [v]}
        case Nil{}:
          Beta.none()
    case other:
      Beta.none()

def Beta.body.env(p: Core.Res, +bd: Core.Tm) -> Core.Sel:
  match p:
    case Core.REnv{env2}:
      Core.SEval{env2, bd}
    case other:
      Beta.none()

def Beta.body(~prim: String -> List<&2, Core.Val> -> Core.Res, +n: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Res) -> Core.Sel:
  match a:
    case Core.ROk{vs}:
      match vs:
        case v <> r:
          Beta.body.env(Core.run(~prim, n, ds, Core.SPat{env, [pt], [v]}), bd)
        case Nil{}:
          Beta.none()
    case other:
      Beta.none()

# The source's run, from A on.
def Beta.src(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    +env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Res) -> Core.Res:
  Core.run(~prim, 1n+(1n+(1n+(1n+p))), ds, Core.SThen{Core.run(~prim, 1n+p, ds, Core.SThen{Core.run(~prim, p, ds,
    Core.SThen{a, Core.KTail{env, Nil{}}}), Core.KCons{Core.VClo{env, pt, bd}}}), Core.KApp{}})

def L.beta.nfa.fail(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +m: String,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, Core.RFail{m})))
    -> Red.NotOof(Core.RFail{m}):
  match p:
    case 0n:
      match nf:
    case 1n+q:
      nf

def L.beta.nfa(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Res,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, a)))
    -> Red.NotOof(a):
  match a:
    case Core.RFail{m}:
      L.beta.nfa.fail(~prim, p, ds, env, pt, bd, m, nf)
    case Core.ROk{vs}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.REnv{env2}:
      Unit{}

def L.beta.nfp.one(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +v: Core.Val, +r: List<&2, Core.Val>,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, Core.ROk{v <> r})))
    -> Red.NotOof(Core.run(~prim, 1n+p, ds, Core.SPat{env, [pt], [v]})):
  match p:
    case 0n:
      match nf:
    case 1n+p1:
      match p1:
        case 0n:
          match nf:
        case 1n+p2:
          match p2:
            case 0n:
              match nf:
            case 1n+p3:
              match p3:
                case 0n:
                  match nf:
                case 1n+p4:
                  L.nf(~prim, 1n+(1n+(1n+(1n+(1n+p4)))), ds, Core.run(~prim, 1n+(1n+(1n+(1n+(1n+p4)))), ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, Nil{}}, nf)

def L.beta.nfp(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Res,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, a)))
    -> Red.NotOof(Core.run(~prim, 1n+p, ds, Beta.pat(env, pt, a))):
  match a:
    case Core.ROk{vs}:
      match vs:
        case v <> r:
          L.beta.nfp.one(~prim, p, ds, env, pt, bd, v, r, nf)
        case Nil{}:
          Unit{}
    case Core.RFail{m}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.REnv{env2}:
      Unit{}

def L.beta.nfb.env(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +bd: Core.Tm, +pr: Core.Res,
    +nf: Red.NotOof(Core.run(~prim, 1n+(1n+p), ds, Core.SThen{pr, Core.KBody{bd, Nil{}}})))
    -> Red.NotOof(Core.run(~prim, 1n+p, ds, Beta.body.env(pr, bd))):
  match pr:
    case Core.REnv{env2}:
      L.nf(~prim, 1n+p, ds, Core.run(~prim, 1n+p, ds, Core.SEval{env2, bd}), Core.KApply{Nil{}}, nf)
    case Core.RFail{m}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.ROk{vs}:
      Unit{}

def L.beta.nfb.one(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +v: Core.Val, +r: List<&2, Core.Val>,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, Core.ROk{v <> r})))
    -> Red.NotOof(Core.run(~prim, p, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, Core.ROk{v <> r}))):
  match p:
    case 0n:
      match nf:
    case 1n+p1:
      match p1:
        case 0n:
          match nf:
        case 1n+p2:
          match p2:
            case 0n:
              match nf:
            case 1n+p3:
              match p3:
                case 0n:
                  match nf:
                case 1n+p4:
                  L.beta.nfb.env(~prim, 1n+(1n+(1n+p4)), ds, bd, Core.run(~prim, 1n+(1n+(1n+(1n+(1n+p4)))), ds, Core.SPat{env, [pt], [v]}), nf)

def L.beta.nfb.none(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Res,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, a)))
    -> Red.NotOof(Core.run(~prim, p, ds, Beta.none())):
  match p:
    case 0n:
      match nf:
    case 1n+q:
      Unit{}

def L.beta.nfb(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Res,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, a)))
    -> Red.NotOof(Core.run(~prim, p, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, a))):
  match a:
    case Core.ROk{vs}:
      match vs:
        case v <> r:
          L.beta.nfb.one(~prim, p, ds, env, pt, bd, v, r, nf)
        case Nil{}:
          L.beta.nfb.none(~prim, p, ds, env, pt, bd, Core.ROk{Nil{}}, nf)
    case Core.RFail{m}:
      L.beta.nfb.none(~prim, p, ds, env, pt, bd, Core.RFail{m}, nf)
    case Core.RNo{}:
      L.beta.nfb.none(~prim, p, ds, env, pt, bd, Core.RNo{}, nf)
    case Core.REnv{env2}:
      L.beta.nfb.none(~prim, p, ds, env, pt, bd, Core.REnv{env2}, nf)

# B, one value, is what the closure call gives.
def L.beta.b.one(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +w: Core.Val,
    +nf: Red.NotOof(Core.run(~prim, p, ds, Core.SThen{Core.ROk{[w]}, Core.KApply{Nil{}}})))
    -> {Core.run(~prim, p, ds, Core.SThen{Core.ROk{[w]}, Core.KApply{Nil{}}}) == Core.ROk{[w]} : Core.Res}:
  match p:
    case 0n:
      match nf:
    case 1n+p1:
      match p1:
        case 0n:
          match nf:
        case 1n+p2:
          match p2:
            case 0n:
              match nf:
            case 1n+p3:
              {==}

def L.beta.b.fail(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +m: String,
    +nf: Red.NotOof(Core.run(~prim, p, ds, Core.SThen{Core.RFail{m}, Core.KApply{Nil{}}})))
    -> {Core.run(~prim, p, ds, Core.SThen{Core.RFail{m}, Core.KApply{Nil{}}}) == Core.RFail{m} : Core.Res}:
  match p:
    case 0n:
      match nf:
    case 1n+q:
      {==}

def L.beta.b.vs(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +vs: List<&2, Core.Val>,
    fb: Red.Fits(Core.ROk{vs}, Red.WLen{1n}),
    +nf: Red.NotOof(Core.run(~prim, p, ds, Core.SThen{Core.ROk{vs}, Core.KApply{Nil{}}})))
    -> {Core.run(~prim, p, ds, Core.SThen{Core.ROk{vs}, Core.KApply{Nil{}}}) == Core.ROk{vs} : Core.Res}:
  match vs:
    case Nil{}:
      match fb:
    case w <> r:
      match r:
        case Nil{}:
          L.beta.b.one(~prim, p, ds, w, nf)
        case x <> r2:
          match fb:

def L.beta.b(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +b: Core.Res,
    fb: Red.Fits(b, Red.WLen{1n}),
    +nf: Red.NotOof(Core.run(~prim, p, ds, Core.SThen{b, Core.KApply{Nil{}}})))
    -> {Core.run(~prim, p, ds, Core.SThen{b, Core.KApply{Nil{}}}) == b : Core.Res}:
  match b:
    case Core.ROk{vs}:
      L.beta.b.vs(~prim, p, ds, vs, fb, nf)
    case Core.RFail{m}:
      L.beta.b.fail(~prim, p, ds, m, nf)
    case Core.RNo{}:
      match fb:
    case Core.REnv{env2}:
      match fb:

def L.beta.scope(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +bd: Core.Tm, +vs: List<&2, Core.Val>,
    +nf: Red.NotOof(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{vs}, Core.KBody{bd, Nil{}}})))
    -> {Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{vs}, Core.KBody{bd, Nil{}}}) == Core.RFail{"a value where a scope was due"} : Core.Res}:
  match p:
    case 0n:
      match nf:
    case 1n+q:
      {==}

# From P on: the source goes on to bd in P's scope, the let to its body.
def L.beta.p(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +ds: List<&2, Core.Def>, +bd: Core.Tm, +pr: Core.Res,
    fb: Red.Fits(Core.run(~prim, p, ds, Beta.body.env(pr, bd)), Red.Sel.want(Beta.body.env(pr, bd))),
    ib: {Core.run(~prim, p, ds, Beta.body.env(pr, bd)) == Core.run(~prim, 1n+q, ds, Beta.body.env(pr, bd)) : Core.Res},
    +nf: Red.NotOof(Core.run(~prim, 1n+p, ds, Core.SThen{pr, Core.KBody{bd, Nil{}}})))
    -> {Core.run(~prim, 1n+p, ds, Core.SThen{pr, Core.KBody{bd, Nil{}}}) == Core.run(~prim, 1n+(1n+q), ds, Core.SThen{pr, Core.KBind{bd}}) : Core.Res}:
  match pr:
    case Core.REnv{env2}:
      %ib : {Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{env2}, Core.KBody{bd, Nil{}}}) == _ : Core.Res}
      L.beta.b(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env2, bd}), fb, nf)
    case Core.ROk{vs}:
      L.beta.scope(~prim, p, ds, bd, vs, nf)
    case Core.RFail{m}:
      {==}
    case Core.RNo{}:
      {==}

def L.beta.ok(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +v: Core.Val,
    ip: {Core.run(~prim, 1n+p, ds, Beta.pat(env, pt, Core.ROk{[v]})) == Core.run(~prim, 1n+(1n+q), ds, Beta.pat(env, pt, Core.ROk{[v]})) : Core.Res},
    fb: Red.Fits(Core.run(~prim, p, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, Core.ROk{[v]})), Red.Sel.want(Beta.body(~prim, 1n+p, ds, env, pt, bd, Core.ROk{[v]}))),
    ib: {Core.run(~prim, p, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, Core.ROk{[v]})) == Core.run(~prim, 1n+q, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, Core.ROk{[v]})) : Core.Res},
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, Core.ROk{[v]})))
    -> {Beta.src(~prim, p, ds, env, pt, bd, Core.ROk{[v]}) == Core.run(~prim, 1n+(1n+(1n+(1n+q))), ds, Core.SThen{Core.ROk{[v]}, Core.KLet{env, pt, bd}}) : Core.Res}:
  match p:
    case 0n:
      match nf:
    case 1n+p1:
      match p1:
        case 0n:
          match nf:
        case 1n+p2:
          match p2:
            case 0n:
              match nf:
            case 1n+p3:
              match p3:
                case 0n:
                  match nf:
                case 1n+p4:
                  %ip : {Beta.src(~prim, 1n+(1n+(1n+(1n+p4))), ds, env, pt, bd, Core.ROk{[v]}) == Core.run(~prim, 1n+(1n+q), ds, Core.SThen{_, Core.KBind{bd}}) : Core.Res}
                  L.beta.p(~prim, 1n+(1n+(1n+(1n+p4))), q, ds, bd, Core.run(~prim, 1n+(1n+(1n+(1n+(1n+p4)))), ds, Core.SPat{env, [pt], [v]}), fb, ib, nf)

def L.beta.fail(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +m: String,
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, Core.RFail{m})))
    -> {Beta.src(~prim, p, ds, env, pt, bd, Core.RFail{m}) == Core.run(~prim, 1n+(1n+(1n+(1n+q))), ds, Core.SThen{Core.RFail{m}, Core.KLet{env, pt, bd}}) : Core.Res}:
  match p:
    case 0n:
      match nf:
    case 1n+p1:
      {==}

# The redex, from A on (A one value: fa).
def L.beta(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Res,
    fa: Red.Fits(a, Red.WLen{1n}),
    ip: {Core.run(~prim, 1n+p, ds, Beta.pat(env, pt, a)) == Core.run(~prim, 1n+(1n+q), ds, Beta.pat(env, pt, a)) : Core.Res},
    fb: Red.Fits(Core.run(~prim, p, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, a)), Red.Sel.want(Beta.body(~prim, 1n+p, ds, env, pt, bd, a))),
    ib: {Core.run(~prim, p, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, a)) == Core.run(~prim, 1n+q, ds, Beta.body(~prim, 1n+p, ds, env, pt, bd, a)) : Core.Res},
    +nf: Red.NotOof(Beta.src(~prim, p, ds, env, pt, bd, a)))
    -> {Beta.src(~prim, p, ds, env, pt, bd, a) == Core.run(~prim, 1n+(1n+(1n+(1n+q))), ds, Core.SThen{a, Core.KLet{env, pt, bd}}) : Core.Res}:
  match a:
    case Core.ROk{vs}:
      match vs:
        case Nil{}:
          match fa:
        case v <> r:
          match r:
            case Nil{}:
              L.beta.ok(~prim, p, q, ds, env, pt, bd, v, ip, fb, ib, nf)
            case w <> r2:
              match fa:
    case Core.RFail{m}:
      L.beta.fail(~prim, p, q, ds, env, pt, bd, m, nf)
    case Core.RNo{}:
      match fa:
    case Core.REnv{env2}:
      match fa:

# In one program, the redex and the let give the same result, if the redex
# does not run out of fuel: the let runs a, pt and bd with more.
def L.beta.law(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}),
    +k: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, +pt: Core.Pt, +bd: Core.Tm, +a: Core.Tm,
    +nf: Red.NotOof(Core.run(~prim, 1n+k, ds, Core.SEval{env, Core.CApp{Core.CLam{pt, bd}, [a]}})))
    -> {Core.run(~prim, 1n+k, ds, Core.SEval{env, Core.CApp{Core.CLam{pt, bd}, [a]}}) == Core.run(~prim, 1n+k, ds, Core.SEval{env, Core.CLet{pt, a, bd}}) : Core.Res}:
  match k:
    case 0n:
      match nf:
    case 1n+k1:
      match k1:
        case 0n:
          match nf:
        case 1n+k2:
          match k2:
            case 0n:
              match nf:
            case 1n+k3:
              match k3:
                case 0n:
                  match nf:
                case 1n+k4:
                  %L.mono(~prim, k4, 1n+(1n+(1n+(1n+k4))), Le.succ(k4, 1n+(1n+(1n+k4)), Le.succ(k4, 1n+(1n+k4), Le.succ(k4, 1n+k4, Le.succ(k4, k4, Le.refl(k4))))), ds, Core.SEval{env, a}, L.beta.nfa(~prim, k4, ds, env, pt, bd, Core.run(~prim, k4, ds, Core.SEval{env, a}), nf)) : {Core.run(~prim, 1n+(1n+(1n+(1n+(1n+k4)))), ds, Core.SEval{env, Core.CApp{Core.CLam{pt, bd}, [a]}}) == Core.run(~prim, 1n+(1n+(1n+(1n+k4))), ds, Core.SThen{_, Core.KLet{env, pt, bd}}) : Core.Res}
                  L.beta(~prim, k4, k4, ds, env, pt, bd, Core.run(~prim, k4, ds, Core.SEval{env, a}),
                    S.one(~prim, ~one, k4, ds, Core.SEval{env, a}),
                    L.mono(~prim, 1n+k4, 1n+(1n+k4), Le.succ(k4, k4, Le.refl(k4)), ds, Beta.pat(env, pt, Core.run(~prim, k4, ds, Core.SEval{env, a})), L.beta.nfp(~prim, k4, ds, env, pt, bd, Core.run(~prim, k4, ds, Core.SEval{env, a}), nf)),
                    S.one(~prim, ~one, k4, ds, Beta.body(~prim, 1n+k4, ds, env, pt, bd, Core.run(~prim, k4, ds, Core.SEval{env, a}))),
                    L.mono(~prim, k4, 1n+k4, Le.succ(k4, k4, Le.refl(k4)), ds, Beta.body(~prim, 1n+k4, ds, env, pt, bd, Core.run(~prim, k4, ds, Core.SEval{env, a})), L.beta.nfb(~prim, k4, ds, env, pt, bd, Core.run(~prim, k4, ds, Core.SEval{env, a}), nf)),
                    nf)

# f applied to one argument: a redex if f is a lambda (by the beta law, in
# the reduced program), else the node with its fields reduced. e is the
# induction hypothesis for the node.
def L.app1(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}),
    +p: Nat, +q: Nat, +ds: List<&2, Core.Def>, +env: List<&2, Core.Val>, f: Core.Tm, +a: Core.Tm,
    +e: {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{f, [a]}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(env), Core.CApp{Core.Tm.red(f, True{}), [Core.Tm.red(a, True{})]}}) : Core.Res},
    +nf: Red.NotOof(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{f, [a]}})))
    -> {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{f, [a]}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(env), Core.Tm.red(Core.CApp{f, [a]}, True{})}) : Core.Res}:
  match f:
    case Core.CLam{+pt, +bd}:
      %L.beta.law(~prim, ~one, q, Core.Defs.red(ds), Core.Vals.red(env), pt, Core.Tm.red(bd, True{}), Core.Tm.red(a, True{}), L.nf.eq(Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{Core.CLam{pt, bd}, [a]}})), Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(env), Core.CApp{Core.CLam{pt, Core.Tm.red(bd, True{})}, [Core.Tm.red(a, True{})]}}), e, L.nf.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{Core.CLam{pt, bd}, [a]}}), nf))) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{Core.CLam{pt, bd}, [a]}})) == _ : Core.Res}
      e
    case Core.CVar{x}:
      e
    case Core.CLit{l}:
      e
    case Core.CRef{g}:
      e
    case Core.CCall{g, as}:
      e
    case Core.CApp{g, as}:
      e
    case Core.CCtr{k, as}:
      e
    case Core.CLet{pt, v, bd}:
      e
    case Core.CMat{scrs, cs}:
      e
    case Core.CCse{ps, bd}:
      e
    case Core.CSuc{k, x}:
      e
    case Core.COp{op, x, y}:
      e
    case Core.CAnn{x, ty}:
      e
    case Core.CTyp{nm, as}:
      e
    case Core.CBox{}:
      e
    case Core.CErr{m}:
      e

# The same as a match's case: not one.
def L.mat.app1(~prim: String -> List<&2, Core.Val> -> Core.Res, +q: Nat, ds: List<&2, Core.Def>,
    env: List<&2, Core.Val>, vs: List<&2, Core.Val>, f: Core.Tm, a: Core.Tm, r: List<&2, Core.Tm>)
    -> {Core.RFail{"not a case"} == Core.run(~prim, 1n+q, ds, Core.SMatch{env, vs, Core.Tm.red(Core.CApp{f, [a]}, True{}) <> r}) : Core.Res}:
  match f:
    case Core.CLam{pt, bd}:
      {==}
    case Core.CVar{x}:
      {==}
    case Core.CLit{l}:
      {==}
    case Core.CRef{g}:
      {==}
    case Core.CCall{g, as}:
      {==}
    case Core.CApp{g, as}:
      {==}
    case Core.CCtr{k, as}:
      {==}
    case Core.CLet{pt, v, bd}:
      {==}
    case Core.CMat{scrs, cs}:
      {==}
    case Core.CCse{ps, bd}:
      {==}
    case Core.CSuc{k, x}:
      {==}
    case Core.COp{op, x, y}:
      {==}
    case Core.CAnn{x, ty}:
      {==}
    case Core.CTyp{nm, as}:
      {==}
    case Core.CBox{}:
      {==}
    case Core.CErr{m}:
      {==}

# Steps
# =====

# A step that runs x, then k on its result: the outer run and x's run, each
# by the induction hypothesis.
def L.then(~prim: String -> List<&2, Core.Val> -> Core.Res, -p: Nat, -q: Nat, -ds: List<&2, Core.Def>, -x: Core.Sel, -k: Core.Kont,
    e1: {Core.Res.red(Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SThen{Core.Res.red(Core.run(~prim, p, ds, x)), Core.Kont.red(k)}) : Core.Res},
    e2: {Core.Res.red(Core.run(~prim, p, ds, x)) == Core.run(~prim, q, Core.Defs.red(ds), Core.Sel.red(x)) : Core.Res})
    -> {Core.Res.red(Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SThen{Core.run(~prim, q, Core.Defs.red(ds), Core.Sel.red(x)), Core.Kont.red(k)}) : Core.Res}:
  %e2 : {Core.Res.red(Core.run(~prim, p, ds, Core.SThen{Core.run(~prim, p, ds, x), k})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SThen{_, Core.Kont.red(k)}) : Core.Res}
  e1

# The theorem, with the fuel and the program reusable, and ok and one
# templates. The source takes n steps, the reduced program m >= n.
def L.red(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.red(prim(op, vs)) == prim(op, Core.Vals.red(vs)) : Core.Res},
    ~one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n}),
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, s: Core.Sel, +nf: Red.NotOof(Core.run(~prim, n, ds, s)))
    -> {Core.Res.red(Core.run(~prim, n, ds, s)) == Core.run(~prim, m, Core.Defs.red(ds), Core.Sel.red(s)) : Core.Res}:
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
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{env, x}, nf)
                case Core.CLit{+l}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, nf)
                case Core.CRef{+f}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SCallDef{f, Nil{}}, nf)
                case Core.CCall{+f, +as}:
                  %L.call(f, as, True{}) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CCall{f, as}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(env), _}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SArgs{env, as}, Core.KCall{f},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SArgs{env, as}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}, nf)))
                case Core.CApp{+f, +as}:
                  match as:
                    case Nil{}:
                      L.then(~prim, p, q, ds, Core.SEvals{env, [f]}, Core.KApp{},
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [f]}), Core.KApp{}}, nf),
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, [f]}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, [f]}), Core.KApp{}, nf)))
                    case +a <> +r:
                      match r:
                        case +b2 <> +r2:
                          %L.app(f, b2 <> r2) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{f, a <> b2 <> r2}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(env), Core.Tm.push(Core.Tm.red(a, True{}), _)}) : Core.Res}
                          L.then(~prim, p, q, ds, Core.SEvals{env, f <> a <> b2 <> r2}, Core.KApp{},
                            L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, f <> a <> b2 <> r2}), Core.KApp{}}, nf),
                            L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, f <> a <> b2 <> r2}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, f <> a <> b2 <> r2}), Core.KApp{}, nf)))
                        case Nil{}:
                          L.app1(~prim, ~one, p, q, ds, env, f, a,
                            L.then(~prim, p, q, ds, Core.SEvals{env, [f, a]}, Core.KApp{},
                              L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [f, a]}), Core.KApp{}}, nf),
                              L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, [f, a]}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, [f, a]}), Core.KApp{}, nf))),
                            nf)
                case Core.CCtr{+k, +as}:
                  %L.ctr(k, as, True{}) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CCtr{k, as}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(env), _}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SEvals{env, as}, Core.KCtr{k},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, as}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}, nf)))
                case Core.CLam{+pt, +bd}:
                  %L.vclo.rev(env, pt, bd) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CLam{pt, bd}})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SThen{Core.ROk{Nil{}}, Core.KCons{_}}) : Core.Res}
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{env, pt, bd}}}, nf)
                case Core.CLet{+pt, +v, +bd}:
                  L.then(~prim, p, q, ds, Core.SEval{env, v}, Core.KLet{env, pt, bd},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, v}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}, nf)))
                case Core.CMat{+scrs, +cases}:
                  %L.mat(scrs, cases, True{}) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(env), _}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SEvals{env, scrs}, Core.KMat{env, cases},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, scrs}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}, nf)))
                case Core.CCse{+ps, +bd}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, nf)
                case Core.CSuc{+k, +x}:
                  L.then(~prim, p, q, ds, Core.SEval{env, x}, Core.KSuc{k},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, x}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}, nf)))
                case Core.COp{+op, +x, +y}:
                  L.then(~prim, p, q, ds, Core.SEvals{env, [x, y]}, Core.KOp{op},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, [x, y]}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}, nf)))
                case Core.CAnn{+x, +ty}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, x}, nf)
                case Core.CTyp{+nm, +as}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, nf)
                case Core.CBox{}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, nf)
                case Core.CErr{+m}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.RFail{m}, Core.KApp{}}, nf)
            case Core.SEvals{+env, +es}:
              match es:
                case Nil{}:
                  {==}
                case +e <> +r:
                  L.then(~prim, p, q, ds, Core.SEval{env, e}, Core.KTail{env, r},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, e}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}, nf)))
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
                            L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}}, nf),
                            L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env, e}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}, nf)))
                        case Core.Era{}:
                          L.then(~prim, p, q, ds, Core.SArgs{env, r}, Core.KCons{Core.VTrm{e}},
                            L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, r}), Core.KCons{Core.VTrm{e}}}, nf),
                            L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SArgs{env, r}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, r}), Core.KCons{Core.VTrm{e}}, nf)))
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
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SMatch{env, vs, rest}, nf)
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
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env2, bd}, nf)
                    case Core.KMat{+env, +cases}:
                      {==}
                    case Core.KCase{+env, +vs, +bd, +rest}:
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env2, bd}, nf)
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
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}}, nf),
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{env2, bd}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}, nf)))
                case Core.ROk{+vs}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SOk{k, vs}, nf)
            case Core.SOk{+k, +vs}:
              match k:
                case Core.KCall{+f}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SCallDef{f, vs}, nf)
                case Core.KApp{}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +f <> +r2:
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SApply{r2, f}, nf)
                case Core.KCtr{+c}:
                  %L.vctr(c, vs) : {Core.ROk{[_]} == Core.ROk{[Core.VCtr{c, Core.Vals.red(vs)}]} : Core.Res}
                  {==}
                case Core.KLet{+env, +pt, +bd}:
                  L.then(~prim, p, q, ds, Core.SPat{env, [pt], vs}, Core.KBind{bd},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, [pt], vs}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}, nf)))
                case Core.KBind{+bd}:
                  {==}
                case Core.KMat{+env, +cases}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SMatch{env, vs, cases}, nf)
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
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}, nf),
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEvals{env, es}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}, nf)))
                case Core.KATail{+env, +as}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.then(~prim, p, q, ds, Core.SArgs{env, as}, Core.KCons{v},
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}}, nf),
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SArgs{env, as}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}, nf)))
                case Core.KCons{+v}:
                  {==}
                case Core.KApply{+rest}:
                  match vs:
                    case Nil{}:
                      {==}
                    case +v <> +r2:
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SApply{rest, v}, nf)
                case Core.KBody{+bd, +rest}:
                  {==}
            case Core.SLook{+env, +x}:
              match env:
                case Nil{}:
                  {==}
                case +bn <> +r:
                  match bn:
                    case Core.VBnd{+y, +v}:
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook2{String.eq(y, x), v, r, x}, nf)
                    case Core.VLit{+l}:
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VTrm{+t}:
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VCtr{+k, +fs}:
                      %L.vctr(k, fs) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VCtr{k, fs} <> r, x})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SLook{_ <> Core.Vals.red(r), x}) : Core.Res}
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VFun{+f, +as}:
                      %L.vfun(f, as) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VFun{f, as} <> r, x})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SLook{_ <> Core.Vals.red(r), x}) : Core.Res}
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
                    case Core.VClo{+e2, +pt, +bd}:
                      %L.vclo(e2, pt, bd) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VClo{e2, pt, bd} <> r, x})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SLook{_ <> Core.Vals.red(r), x}) : Core.Res}
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{r, x}, nf)
            case Core.SLook2{+hit, +v, +env, +x}:
              match hit:
                case True{}:
                  {==}
                case False{}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SLook{env, x}, nf)
            case Core.SCallDef{+f, +vs}:
              L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SFind{ds, f, vs}, nf)
            case Core.SFind{+ds2, +f, +vs}:
              match ds2:
                case Nil{}:
                  ok(f, vs)
                case +d <> +r:
                  match d:
                    case Core.Def{+name, +ps, +bd, +ret}:
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SFound{String.eq(name, f), ps, bd, r, f, vs}, nf)
            case Core.SFound{+hit, +ps, +bd, +ds2, +f, +vs}:
              match hit:
                case True{}:
                  %L.len(vs) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, bd, ds2, f, vs})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SEnter{Nat.is_lt(_, Core.Pars.len(ps)), f, ps, Core.Tm.red(bd, True{}), Core.Vals.red(vs)}) : Core.Res}
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, bd, vs}, nf)
                case False{}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SFind{ds2, f, vs}, nf)
            case Core.SEnter{+short, +f, +ps, +bd, +vs}:
              match short:
                case True{}:
                  %L.vfun(f, vs) : {Core.ROk{[_]} == Core.ROk{[Core.VFun{f, Core.Vals.red(vs)}]} : Core.Res}
                  {==}
                case False{}:
                  %L.bind(ps, vs) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, bd, vs})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SThen{Core.run(~prim, q, Core.Defs.red(ds), Core.SEval{_, Core.Tm.red(bd, True{})}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), Core.Vals.red(vs))}}) : Core.Res}
                  %L.drop(Core.Pars.len(ps), vs) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, bd, vs})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SThen{Core.run(~prim, q, Core.Defs.red(ds), Core.SEval{Core.Vals.red(Core.Scope.bind(ps, vs)), Core.Tm.red(bd, True{})}), Core.KApply{_}}) : Core.Res}
                  L.then(~prim, p, q, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}, Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)},
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}, nf),
                    L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}, nf)))
            case Core.SApply{+vs, +fv}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r:
                  match fv:
                    case Core.VClo{+env, +pt, +bd}:
                      %L.vclo(env, pt, bd) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{env, pt, bd}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SApply{Core.Val.red(v) <> Core.Vals.red(r), _}) : Core.Res}
                      L.then(~prim, p, q, ds, Core.SPat{env, [pt], [v]}, Core.KBody{bd, r},
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}}, nf),
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, [pt], [v]}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}, nf)))
                    case Core.VFun{+f, +as}:
                      %L.vfun(f, as) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SApply{Core.Val.red(v) <> Core.Vals.red(r), _}) : Core.Res}
                      %L.cat(as, v <> r) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}})) == Core.run(~prim, q, Core.Defs.red(ds), Core.SCallDef{f, _}) : Core.Res}
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SCallDef{f, Core.Vals.cat(as, v <> r)}, nf)
                    case Core.VCtr{+k, +fs}:
                      %L.vctr(k, fs) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VCtr{k, fs}})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SApply{Core.Val.red(v) <> Core.Vals.red(r), _}) : Core.Res}
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
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}}, nf),
                        L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, ps, vs}, L.nf(~prim, p, ds, Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}, nf)))
                    case Core.CCall{+f, +as}:
                      %L.call(f, as, True{}) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CCall{f, as} <> r})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SMatch{Core.Vals.red(env), Core.Vals.red(vs), _ <> Core.Tms.red(r)}) : Core.Res}
                      {==}
                    case Core.CApp{+f, +as}:
                      match as:
                        case Nil{}:
                          {==}
                        case +a <> +r2:
                          match r2:
                            case +b2 <> +r3:
                              %L.app(f, b2 <> r3) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CApp{f, a <> b2 <> r3} <> r})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SMatch{Core.Vals.red(env), Core.Vals.red(vs), Core.Tm.push(Core.Tm.red(a, True{}), _) <> Core.Tms.red(r)}) : Core.Res}
                              {==}
                            case Nil{}:
                              L.mat.app1(~prim, q, Core.Defs.red(ds), Core.Vals.red(env), Core.Vals.red(vs), f, a, Core.Tms.red(r))
                    case Core.CCtr{+k, +as}:
                      %L.ctr(k, as, True{}) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CCtr{k, as} <> r})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SMatch{Core.Vals.red(env), Core.Vals.red(vs), _ <> Core.Tms.red(r)}) : Core.Res}
                      {==}
                    case Core.CMat{+scrs, +cs}:
                      %L.mat(scrs, cs, True{}) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CMat{scrs, cs} <> r})) == Core.run(~prim, 1n+q, Core.Defs.red(ds), Core.SMatch{Core.Vals.red(env), Core.Vals.red(vs), _ <> Core.Tms.red(r)}) : Core.Res}
                      {==}
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
                      %L.pat(env, pt, v, pr, vr) : {Core.Res.red(Core.run(~prim, 1n+p, ds, Core.SPat{env, pt <> pr, v <> vr})) == Core.run(~prim, q, Core.Defs.red(ds), _) : Core.Res}
                      L.red(~prim, ~ok, ~one, p, q, le, ds, Core.Pat.step(env, pt, v, pr, vr), nf)
            case Core.SPatC{+hit, +env, +ps, +vs}:
              match hit:
                case True{}:
                  L.red(~prim, ~ok, ~one, p, q, le, ds, Core.SPat{env, ps, vs}, nf)
                case False{}:
                  {==}

def Red.one_ok(prim, one, n, ds, s):
  S.one(~prim, ~one, n, ds, s)

def Red.red_ok(prim, ok, one, n, m, le, ds, s, nf):
  L.red(~prim, ~ok, ~one, n, m, le, ds, s, nf)
