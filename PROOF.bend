import Base
import ./LAWS.bend as Laws
import ./core.bend as Core

# Proof of LAWS.bend's erase_ok: `run` takes a program and a selector to the
# same result, erased, as it takes the erased program and selector to.
# Induction on the fuel; one case per step of `run`. A lemma's equation is
# stated with the form the other side needs on its left, for `%`.

# Shapes
# ======

# Tm.erase and Val.erase walk a list field as its head and the node rebuilt
# with the rest; these give the node with the field erased as a whole.

def L.call(f: String, as: List<&2, Core.Arg>)
    -> {Core.CCall{f, Core.Args.erase(as)} == Core.Tm.erase(Core.CCall{f, as}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          match rel:
            case Core.Run{}:
              %L.call(f, r) : {Core.CCall{f, Core.Arg{Core.Run{}, Core.Tm.erase(e)} <> Core.Args.erase(r)} == Core.Tm.push.call(Core.Arg{Core.Run{}, Core.Tm.erase(e)}, _) : Core.Tm}
              {==}
            case Core.Era{}:
              %L.call(f, r) : {Core.CCall{f, Core.Arg{Core.Era{}, Core.CBox{}} <> Core.Args.erase(r)} == Core.Tm.push.call(Core.Arg{Core.Era{}, Core.CBox{}}, _) : Core.Tm}
              {==}

def L.app(f: Core.Tm, as: List<&2, Core.Tm>)
    -> {Core.CApp{Core.Tm.erase(f), Core.Tms.erase(as)} == Core.Tm.erase(Core.CApp{f, as}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.app(f, r) : {Core.CApp{Core.Tm.erase(f), Core.Tm.erase(a) <> Core.Tms.erase(r)} == Core.Tm.push(Core.Tm.erase(a), _) : Core.Tm}
      {==}

def L.ctr(k: String, as: List<&2, Core.Tm>)
    -> {Core.CCtr{k, Core.Tms.erase(as)} == Core.Tm.erase(Core.CCtr{k, as}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.ctr(k, r) : {Core.CCtr{k, Core.Tm.erase(a) <> Core.Tms.erase(r)} == Core.Tm.push(Core.Tm.erase(a), _) : Core.Tm}
      {==}

def L.mat.cases(cs: List<&2, Core.Tm>)
    -> {Core.CMat{Nil{}, Core.Tms.erase(cs)} == Core.Tm.erase(Core.CMat{Nil{}, cs}) : Core.Tm}:
  match cs:
    case Nil{}:
      {==}
    case c <> r:
      %L.mat.cases(r) : {Core.CMat{Nil{}, Core.Tm.erase(c) <> Core.Tms.erase(r)} == Core.Tm.push.case(Core.Tm.erase(c), _) : Core.Tm}
      {==}

def L.mat(scrs: List<&2, Core.Tm>, cs: List<&2, Core.Tm>)
    -> {Core.CMat{Core.Tms.erase(scrs), Core.Tms.erase(cs)} == Core.Tm.erase(Core.CMat{scrs, cs}) : Core.Tm}:
  match scrs:
    case Nil{}:
      L.mat.cases(cs)
    case a <> r:
      %L.mat(r, cs) : {Core.CMat{Core.Tm.erase(a) <> Core.Tms.erase(r), Core.Tms.erase(cs)} == Core.Tm.push(Core.Tm.erase(a), _) : Core.Tm}
      {==}

def L.vctr(k: String, fs: List<&2, Core.Val>)
    -> {Core.VCtr{k, Core.Vals.erase(fs)} == Core.Val.erase(Core.VCtr{k, fs}) : Core.Val}:
  match fs:
    case Nil{}:
      {==}
    case f <> r:
      %L.vctr(k, r) : {Core.VCtr{k, Core.Val.erase(f) <> Core.Vals.erase(r)} == Core.Val.push(Core.Val.erase(f), _) : Core.Val}
      {==}

def L.vfun(g: String, as: List<&2, Core.Val>)
    -> {Core.VFun{g, Core.Vals.erase(as)} == Core.Val.erase(Core.VFun{g, as}) : Core.Val}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %L.vfun(g, r) : {Core.VFun{g, Core.Val.erase(a) <> Core.Vals.erase(r)} == Core.Val.push(Core.Val.erase(a), _) : Core.Val}
      {==}

def L.vclo(env: List<&2, Core.Val>, pt: Core.Pt, bd: Core.Tm)
    -> {Core.VClo{Core.Vals.erase(env), pt, Core.Tm.erase(bd)} == Core.Val.erase(Core.VClo{env, pt, bd}) : Core.Val}:
  match env:
    case Nil{}:
      {==}
    case e <> r:
      %L.vclo(r, pt, bd) : {Core.VClo{Core.Val.erase(e) <> Core.Vals.erase(r), pt, Core.Tm.erase(bd)} == Core.Val.push.env(Core.Val.erase(e), _) : Core.Val}
      {==}

def L.vclo.rev(env: List<&2, Core.Val>, pt: Core.Pt, bd: Core.Tm)
    -> {Core.Val.erase(Core.VClo{env, pt, bd}) == Core.VClo{Core.Vals.erase(env), pt, Core.Tm.erase(bd)} : Core.Val}:
  %L.vclo(env, pt, bd) : {_ == Core.VClo{Core.Vals.erase(env), pt, Core.Tm.erase(bd)} : Core.Val}
  {==}

# Lists
# =====

def L.len(vs: List<&2, Core.Val>) -> {Core.Vals.len(vs) == Core.Vals.len(Core.Vals.erase(vs)) : Nat}:
  match vs:
    case Nil{}:
      {==}
    case v <> r:
      %L.len(r) : {1n+Core.Vals.len(r) == 1n+_ : Nat}
      {==}

def L.cat(a: List<&2, Core.Val>, b: List<&2, Core.Val>)
    -> {Core.Vals.erase(Core.Vals.cat(a, b)) == Core.Vals.cat(Core.Vals.erase(a), Core.Vals.erase(b)) : List<&2, Core.Val>}:
  match a:
    case Nil{}:
      {==}
    case v <> r:
      %L.cat(r, b) : {Core.Val.erase(v) <> Core.Vals.erase(Core.Vals.cat(r, b)) == Core.Val.erase(v) <> _ : List<&2, Core.Val>}
      {==}

def L.drop(n: Nat, vs: List<&2, Core.Val>)
    -> {Core.Vals.erase(Core.Vals.drop(n, vs)) == Core.Vals.drop(n, Core.Vals.erase(vs)) : List<&2, Core.Val>}:
  match n:
    case 0n:
      {==}
    case 1n+m:
      match vs:
        case Nil{}:
          {==}
        case v <> r:
          L.drop(m, r)

def L.push(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, acc: List<&2, Core.Val>)
    -> {Core.Vals.erase(Core.Scope.push(ps, vs, acc)) == Core.Scope.push(ps, Core.Vals.erase(vs), Core.Vals.erase(acc)) : List<&2, Core.Val>}:
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
              L.push(pr, vr, Core.VBnd{x, v} <> acc)

def L.bind(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>)
    -> {Core.Vals.erase(Core.Scope.bind(ps, vs)) == Core.Scope.bind(ps, Core.Vals.erase(vs)) : List<&2, Core.Val>}:
  L.push(ps, vs, Nil{})

# Patterns
# ========

def L.pat(env: List<&2, Core.Val>, pt: Core.Pt, v: Core.Val, ps: List<&2, Core.Pt>, vs: List<&2, Core.Val>)
    -> {Core.Sel.erase(Core.Pat.step(env, pt, v, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), pt, Core.Val.erase(v), ps, Core.Vals.erase(vs)) : Core.Sel}:
  match pt:
    case Core.PtVar{x}:
      {==}
    case Core.PtCtr{k, qs}:
      match v:
        case Core.VCtr{k2, +fs}:
          %L.vctr(k2, fs) : {Core.Sel.erase(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          %L.len(fs) : {Core.Sel.erase(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.SPatC{Bool.and(String.eq(k, k2), Nat.is_eq(Core.Pts.len(qs), _)), Core.Vals.erase(env), Core.Pts.cat(qs, ps), Core.Vals.cat(Core.Vals.erase(fs), Core.Vals.erase(vs))} : Core.Sel}
          %L.cat(fs, vs) : {Core.Sel.erase(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VCtr{k2, fs}, ps, vs)) == Core.SPatC{Bool.and(String.eq(k, k2), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs))), Core.Vals.erase(env), Core.Pts.cat(qs, ps), _} : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.erase(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.erase(Core.Pat.step(env, Core.PtCtr{k, qs}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtCtr{k, qs}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.erase(Core.Pat.step(env, Core.PtNat{n}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtNat{n}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.erase(Core.Pat.step(env, Core.PtNat{n}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtNat{n}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.erase(Core.Pat.step(env, Core.PtNat{n}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtNat{n}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.erase(Core.Pat.step(env, Core.PtNum{n}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtNum{n}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.erase(Core.Pat.step(env, Core.PtNum{n}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtNum{n}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.erase(Core.Pat.step(env, Core.PtNum{n}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtNum{n}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.erase(Core.Pat.step(env, Core.PtFlt{s}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtFlt{s}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.erase(Core.Pat.step(env, Core.PtFlt{s}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtFlt{s}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.erase(Core.Pat.step(env, Core.PtFlt{s}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtFlt{s}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
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
          %L.vctr(k2, fs) : {Core.Sel.erase(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VCtr{k2, fs}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtSuc{k, q}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VFun{g, as}:
          %L.vfun(g, as) : {Core.Sel.erase(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VFun{g, as}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtSuc{k, q}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
          {==}
        case Core.VClo{e2, p2, bd}:
          %L.vclo(e2, p2, bd) : {Core.Sel.erase(Core.Pat.step(env, Core.PtSuc{k, q}, Core.VClo{e2, p2, bd}, ps, vs)) == Core.Pat.step(Core.Vals.erase(env), Core.PtSuc{k, q}, _, ps, Core.Vals.erase(vs)) : Core.Sel}
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

# Steps
# =====

# A step that runs x, then k on its result: the outer run and x's run, each
# by the induction hypothesis.
def L.then(~prim: String -> List<&2, Core.Val> -> Core.Res, -n: Nat, -ds: List<&2, Core.Def>, -x: Core.Sel, -k: Core.Kont,
    e1: {Core.Res.erase(Core.run(~prim, n, ds, Core.SThen{Core.run(~prim, n, ds, x), k})) == Core.run(~prim, n, Core.Defs.erase(ds), Core.SThen{Core.Res.erase(Core.run(~prim, n, ds, x)), Core.Kont.erase(k)}) : Core.Res},
    e2: {Core.Res.erase(Core.run(~prim, n, ds, x)) == Core.run(~prim, n, Core.Defs.erase(ds), Core.Sel.erase(x)) : Core.Res})
    -> {Core.Res.erase(Core.run(~prim, n, ds, Core.SThen{Core.run(~prim, n, ds, x), k})) == Core.run(~prim, n, Core.Defs.erase(ds), Core.SThen{Core.run(~prim, n, Core.Defs.erase(ds), Core.Sel.erase(x)), Core.Kont.erase(k)}) : Core.Res}:
  %e2 : {Core.Res.erase(Core.run(~prim, n, ds, Core.SThen{Core.run(~prim, n, ds, x), k})) == Core.run(~prim, n, Core.Defs.erase(ds), Core.SThen{_, Core.Kont.erase(k)}) : Core.Res}
  e1

# The theorem, with the fuel and the program reusable and ok a template: the
# proof applies ok once per native call, and a function is used at most once.
def L.ok(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.erase(prim(op, vs)) == prim(op, Core.Vals.erase(vs)) : Core.Res},
    +n: Nat, +ds: List<&2, Core.Def>, s: Core.Sel)
    -> {Core.Res.erase(Core.run(~prim, n, ds, s)) == Core.run(~prim, n, Core.Defs.erase(ds), Core.Sel.erase(s)) : Core.Res}:
  match n:
    case 0n:
      {==}
    case 1n+p:
      match s:
        case Core.SEval{+env, +e}:
          match e:
            case Core.CVar{+x}:
              L.ok(~prim, ~ok, p, ds, Core.SLook{env, x})
            case Core.CLit{+l}:
              L.ok(~prim, ~ok, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}})
            case Core.CRef{+f}:
              L.ok(~prim, ~ok, p, ds, Core.SCallDef{f, Nil{}})
            case Core.CCall{+f, +as}:
              %L.call(f, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CCall{f, as}})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SEval{Core.Vals.erase(env), _}) : Core.Res}
              L.then(~prim, p, ds, Core.SArgs{env, as}, Core.KCall{f},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}}),
                L.ok(~prim, ~ok, p, ds, Core.SArgs{env, as}))
            case Core.CApp{+f, +as}:
              %L.app(f, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CApp{f, as}})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SEval{Core.Vals.erase(env), _}) : Core.Res}
              L.then(~prim, p, ds, Core.SEvals{env, f <> as}, Core.KApp{},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, f <> as}), Core.KApp{}}),
                L.ok(~prim, ~ok, p, ds, Core.SEvals{env, f <> as}))
            case Core.CCtr{+k, +as}:
              %L.ctr(k, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CCtr{k, as}})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SEval{Core.Vals.erase(env), _}) : Core.Res}
              L.then(~prim, p, ds, Core.SEvals{env, as}, Core.KCtr{k},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}}),
                L.ok(~prim, ~ok, p, ds, Core.SEvals{env, as}))
            case Core.CLam{+pt, +bd}:
              %L.vclo.rev(env, pt, bd) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CLam{pt, bd}})) == Core.run(~prim, p, Core.Defs.erase(ds), Core.SThen{Core.ROk{Nil{}}, Core.KCons{_}}) : Core.Res}
              L.ok(~prim, ~ok, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{env, pt, bd}}})
            case Core.CLet{+pt, +v, +bd}:
              L.then(~prim, p, ds, Core.SEval{env, v}, Core.KLet{env, pt, bd},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}}),
                L.ok(~prim, ~ok, p, ds, Core.SEval{env, v}))
            case Core.CMat{+scrs, +cases}:
              %L.mat(scrs, cases) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SEval{env, Core.CMat{scrs, cases}})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SEval{Core.Vals.erase(env), _}) : Core.Res}
              L.then(~prim, p, ds, Core.SEvals{env, scrs}, Core.KMat{env, cases},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}}),
                L.ok(~prim, ~ok, p, ds, Core.SEvals{env, scrs}))
            case Core.CCse{+ps, +bd}:
              L.ok(~prim, ~ok, p, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}})
            case Core.CSuc{+k, +x}:
              L.then(~prim, p, ds, Core.SEval{env, x}, Core.KSuc{k},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}}),
                L.ok(~prim, ~ok, p, ds, Core.SEval{env, x}))
            case Core.COp{+op, +x, +y}:
              L.then(~prim, p, ds, Core.SEvals{env, [x, y]}, Core.KOp{op},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}}),
                L.ok(~prim, ~ok, p, ds, Core.SEvals{env, [x, y]}))
            case Core.CAnn{+x, +ty}:
              L.ok(~prim, ~ok, p, ds, Core.SEval{env, x})
            case Core.CTyp{+nm, +as}:
              L.ok(~prim, ~ok, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}})
            case Core.CBox{}:
              L.ok(~prim, ~ok, p, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}})
            case Core.CErr{+m}:
              L.ok(~prim, ~ok, p, ds, Core.SThen{Core.RFail{m}, Core.KApp{}})
        case Core.SEvals{+env, +es}:
          match es:
            case Nil{}:
              {==}
            case +e <> +r:
              L.then(~prim, p, ds, Core.SEval{env, e}, Core.KTail{env, r},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}}),
                L.ok(~prim, ~ok, p, ds, Core.SEval{env, e}))
        case Core.SArgs{+env, +as}:
          match as:
            case Nil{}:
              {==}
            case +a <> +r:
              match a:
                case Core.Arg{+rel, +e}:
                  match rel:
                    case Core.Run{}:
                      L.then(~prim, p, ds, Core.SEval{env, e}, Core.KATail{env, r},
                        L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}}),
                        L.ok(~prim, ~ok, p, ds, Core.SEval{env, e}))
                    case Core.Era{}:
                      L.then(~prim, p, ds, Core.SEval{env, Core.CBox{}}, Core.KATail{env, r},
                        L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, Core.CBox{}}), Core.KATail{env, r}}),
                        L.ok(~prim, ~ok, p, ds, Core.SEval{env, Core.CBox{}}))
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
                  L.ok(~prim, ~ok, p, ds, Core.SMatch{env, vs, rest})
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
                  L.ok(~prim, ~ok, p, ds, Core.SEval{env2, bd})
                case Core.KMat{+env, +cases}:
                  {==}
                case Core.KCase{+env, +vs, +bd, +rest}:
                  L.ok(~prim, ~ok, p, ds, Core.SEval{env2, bd})
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
                  L.then(~prim, p, ds, Core.SEval{env2, bd}, Core.KApply{rest},
                    L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env2, bd}), Core.KApply{rest}}),
                    L.ok(~prim, ~ok, p, ds, Core.SEval{env2, bd}))
            case Core.ROk{+vs}:
              L.ok(~prim, ~ok, p, ds, Core.SOk{k, vs})
        case Core.SOk{+k, +vs}:
          match k:
            case Core.KCall{+f}:
              L.ok(~prim, ~ok, p, ds, Core.SCallDef{f, vs})
            case Core.KApp{}:
              match vs:
                case Nil{}:
                  {==}
                case +f <> +r2:
                  L.ok(~prim, ~ok, p, ds, Core.SApply{r2, f})
            case Core.KCtr{+c}:
              %L.vctr(c, vs) : {Core.ROk{[_]} == Core.ROk{[Core.VCtr{c, Core.Vals.erase(vs)}]} : Core.Res}
              {==}
            case Core.KLet{+env, +pt, +bd}:
              L.then(~prim, p, ds, Core.SPat{env, [pt], vs}, Core.KBind{bd},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}}),
                L.ok(~prim, ~ok, p, ds, Core.SPat{env, [pt], vs}))
            case Core.KBind{+bd}:
              {==}
            case Core.KMat{+env, +cases}:
              L.ok(~prim, ~ok, p, ds, Core.SMatch{env, vs, cases})
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
                  L.then(~prim, p, ds, Core.SEvals{env, es}, Core.KCons{v},
                    L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}),
                    L.ok(~prim, ~ok, p, ds, Core.SEvals{env, es}))
            case Core.KATail{+env, +as}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r2:
                  L.then(~prim, p, ds, Core.SArgs{env, as}, Core.KCons{v},
                    L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}}),
                    L.ok(~prim, ~ok, p, ds, Core.SArgs{env, as}))
            case Core.KCons{+v}:
              {==}
            case Core.KApply{+rest}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r2:
                  L.ok(~prim, ~ok, p, ds, Core.SApply{rest, v})
            case Core.KBody{+bd, +rest}:
              {==}
        case Core.SLook{+env, +x}:
          match env:
            case Nil{}:
              {==}
            case +bn <> +r:
              match bn:
                case Core.VBnd{+y, +v}:
                  L.ok(~prim, ~ok, p, ds, Core.SLook2{String.eq(y, x), v, r, x})
                case Core.VLit{+l}:
                  L.ok(~prim, ~ok, p, ds, Core.SLook{r, x})
                case Core.VTrm{+t}:
                  L.ok(~prim, ~ok, p, ds, Core.SLook{r, x})
                case Core.VCtr{+k, +fs}:
                  %L.vctr(k, fs) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VCtr{k, fs} <> r, x})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SLook{_ <> Core.Vals.erase(r), x}) : Core.Res}
                  L.ok(~prim, ~ok, p, ds, Core.SLook{r, x})
                case Core.VFun{+f, +as}:
                  %L.vfun(f, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VFun{f, as} <> r, x})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SLook{_ <> Core.Vals.erase(r), x}) : Core.Res}
                  L.ok(~prim, ~ok, p, ds, Core.SLook{r, x})
                case Core.VClo{+e2, +pt, +bd}:
                  %L.vclo(e2, pt, bd) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SLook{Core.VClo{e2, pt, bd} <> r, x})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SLook{_ <> Core.Vals.erase(r), x}) : Core.Res}
                  L.ok(~prim, ~ok, p, ds, Core.SLook{r, x})
        case Core.SLook2{+hit, +v, +env, +x}:
          match hit:
            case True{}:
              {==}
            case False{}:
              L.ok(~prim, ~ok, p, ds, Core.SLook{env, x})
        case Core.SCallDef{+f, +vs}:
          L.ok(~prim, ~ok, p, ds, Core.SFind{ds, f, vs})
        case Core.SFind{+ds2, +f, +vs}:
          match ds2:
            case Nil{}:
              ok(f, vs)
            case +d <> +r:
              match d:
                case Core.Def{+name, +ps, +bd, +ret}:
                  L.ok(~prim, ~ok, p, ds, Core.SFound{String.eq(name, f), ps, bd, r, f, vs})
        case Core.SFound{+hit, +ps, +bd, +ds2, +f, +vs}:
          match hit:
            case True{}:
              %L.len(vs) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, bd, ds2, f, vs})) == Core.run(~prim, p, Core.Defs.erase(ds), Core.SEnter{Nat.is_lt(_, Core.Pars.len(ps)), f, ps, Core.Tm.erase(bd), Core.Vals.erase(vs)}) : Core.Res}
              L.ok(~prim, ~ok, p, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, bd, vs})
            case False{}:
              L.ok(~prim, ~ok, p, ds, Core.SFind{ds2, f, vs})
        case Core.SEnter{+short, +f, +ps, +bd, +vs}:
          match short:
            case True{}:
              %L.vfun(f, vs) : {Core.ROk{[_]} == Core.ROk{[Core.VFun{f, Core.Vals.erase(vs)}]} : Core.Res}
              {==}
            case False{}:
              %L.bind(ps, vs) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, bd, vs})) == Core.run(~prim, p, Core.Defs.erase(ds), Core.SThen{Core.run(~prim, p, Core.Defs.erase(ds), Core.SEval{_, Core.Tm.erase(bd)}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), Core.Vals.erase(vs))}}) : Core.Res}
              %L.drop(Core.Pars.len(ps), vs) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, bd, vs})) == Core.run(~prim, p, Core.Defs.erase(ds), Core.SThen{Core.run(~prim, p, Core.Defs.erase(ds), Core.SEval{Core.Vals.erase(Core.Scope.bind(ps, vs)), Core.Tm.erase(bd)}), Core.KApply{_}}) : Core.Res}
              L.then(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}, Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)},
                L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}),
                L.ok(~prim, ~ok, p, ds, Core.SEval{Core.Scope.bind(ps, vs), bd}))
        case Core.SApply{+vs, +fv}:
          match vs:
            case Nil{}:
              {==}
            case +v <> +r:
              match fv:
                case Core.VClo{+env, +pt, +bd}:
                  %L.vclo(env, pt, bd) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{env, pt, bd}})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SApply{Core.Val.erase(v) <> Core.Vals.erase(r), _}) : Core.Res}
                  L.then(~prim, p, ds, Core.SPat{env, [pt], [v]}, Core.KBody{bd, r},
                    L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}}),
                    L.ok(~prim, ~ok, p, ds, Core.SPat{env, [pt], [v]}))
                case Core.VFun{+f, +as}:
                  %L.vfun(f, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SApply{Core.Val.erase(v) <> Core.Vals.erase(r), _}) : Core.Res}
                  %L.cat(as, v <> r) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{f, as}})) == Core.run(~prim, p, Core.Defs.erase(ds), Core.SCallDef{f, _}) : Core.Res}
                  L.ok(~prim, ~ok, p, ds, Core.SCallDef{f, Core.Vals.cat(as, v <> r)})
                case Core.VCtr{+k, +fs}:
                  %L.vctr(k, fs) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VCtr{k, fs}})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SApply{Core.Val.erase(v) <> Core.Vals.erase(r), _}) : Core.Res}
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
                  L.then(~prim, p, ds, Core.SPat{env, ps, vs}, Core.KCase{env, vs, bd, r},
                    L.ok(~prim, ~ok, p, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}}),
                    L.ok(~prim, ~ok, p, ds, Core.SPat{env, ps, vs}))
                case Core.CCall{+f, +as}:
                  %L.call(f, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CCall{f, as} <> r})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SMatch{Core.Vals.erase(env), Core.Vals.erase(vs), _ <> Core.Tms.erase(r)}) : Core.Res}
                  {==}
                case Core.CApp{+f, +as}:
                  %L.app(f, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CApp{f, as} <> r})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SMatch{Core.Vals.erase(env), Core.Vals.erase(vs), _ <> Core.Tms.erase(r)}) : Core.Res}
                  {==}
                case Core.CCtr{+k, +as}:
                  %L.ctr(k, as) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CCtr{k, as} <> r})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SMatch{Core.Vals.erase(env), Core.Vals.erase(vs), _ <> Core.Tms.erase(r)}) : Core.Res}
                  {==}
                case Core.CMat{+scrs, +cs}:
                  %L.mat(scrs, cs) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SMatch{env, vs, Core.CMat{scrs, cs} <> r})) == Core.run(~prim, 1n+p, Core.Defs.erase(ds), Core.SMatch{Core.Vals.erase(env), Core.Vals.erase(vs), _ <> Core.Tms.erase(r)}) : Core.Res}
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
                  %L.pat(env, pt, v, pr, vr) : {Core.Res.erase(Core.run(~prim, 1n+p, ds, Core.SPat{env, pt <> pr, v <> vr})) == Core.run(~prim, p, Core.Defs.erase(ds), _) : Core.Res}
                  L.ok(~prim, ~ok, p, ds, Core.Pat.step(env, pt, v, pr, vr))
        case Core.SPatC{+hit, +env, +ps, +vs}:
          match hit:
            case True{}:
              L.ok(~prim, ~ok, p, ds, Core.SPat{env, ps, vs})
            case False{}:
              {==}

def Laws.erase_ok(prim, ok, n, ds, s):
  L.ok(~prim, ~ok, n, ds, s)

def Laws.erase_prog(prim, ok, n, ds):
  L.ok(~prim, ~ok, n, ds, Core.SCallDef{"main", Nil{}})
