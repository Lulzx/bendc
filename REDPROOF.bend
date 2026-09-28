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

def Red.one_ok(prim, one, n, ds, s):
  S.one(~prim, ~one, n, ds, s)
