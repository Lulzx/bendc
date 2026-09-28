# The core IR: what bendc's front end hands its C back end (see "Core IR" in
# the README). A program's defs, their terms with every call of a global def
# explicit and its arguments marked relevant or erased, the parameters with
# their declared types, and the return types. Erasure (Tm.erase) replaces
# each erased argument by a box, and reduction (Tm.red) each lambda applied
# to one argument by a let; `run` gives the IR a semantics, LAWS.bend /
# PROOF.bend prove that erasure preserves it, and RED.bend / REDPROOF.bend
# that reduction does.

import Base

# Types
# =====

# An argument's or a parameter's relevance: erased ones are types, proofs
# and other values the checker sees and the program does not.
type Rel is Data:
  Run{}
  Era{}

type Pt is Data:
  PtVar{x: String}
  PtCtr{k: String, ps: List<&2, Pt>}
  PtNat{n: U32}
  PtSuc{k: U32, p: Pt}
  PtNum{n: U32}
  PtFlt{s: String}

type Lit is Data:
  LNum{n: U32}
  LNat{n: U32}
  LFlt{s: String}
  LStr{s: String}

type Tm is Data:
  CVar{x: String}
  CLit{l: Lit}
  CRef{f: String}
  CCall{f: String, args: List<&2, Arg>}
  CApp{f: Tm, args: List<&2, Tm>}
  CCtr{k: String, args: List<&2, Tm>}
  CLam{p: Pt, b: Tm}
  CLet{p: Pt, v: Tm, b: Tm}
  CMat{scrs: List<&2, Tm>, cases: List<&2, Tm>}
  CCse{ps: List<&2, Pt>, b: Tm}
  CSuc{k: U32, e: Tm}
  COp{op: String, a: Tm, b: Tm}
  CAnn{e: Tm, ty: String}
  CTyp{name: String, args: List<&2, Tm>}
  CBox{}
  CErr{msg: String}

type Arg is Data:
  Arg{rel: Rel, e: Tm}

# mode as in bendc's Param (0 plain, 1 erased, 2 shared, 3 template, 4 bare).
type Par is Data:
  Par{x: String, rel: Rel, mode: U32, ty: String}

type Def is Data:
  Def{name: String, ps: List<&2, Par>, body: Tm, ret: Tm}

# Erasure
# =======

def Tm.push.call(a: Arg, e: Tm) -> Tm:
  match e:
    case CCall{f, as}:
      CCall{f, a <> as}
    case other:
      other

def Tm.push(a: Tm, e: Tm) -> Tm:
  match e:
    case CApp{f, as}:
      CApp{f, a <> as}
    case CCtr{k, as}:
      CCtr{k, a <> as}
    case CMat{scrs, cases}:
      CMat{a <> scrs, cases}
    case CTyp{n, as}:
      CTyp{n, a <> as}
    case other:
      other

def Tm.push.case(c: Tm, e: Tm) -> Tm:
  match e:
    case CMat{scrs, cases}:
      CMat{scrs, c <> cases}
    case other:
      other

def Tm.push.fn(f: Tm, e: Tm) -> Tm:
  match e:
    case CApp{g, as}:
      CApp{f, as}
    case other:
      other

# t with each erased argument of a call replaced by a box (a list field is
# walked as its head and the node rebuilt with the rest).
def Tm.erase(t: Tm) -> Tm:
  match t:
    case CCall{f, as}:
      match as:
        case Nil{}:
          CCall{f, Nil{}}
        case a <> r:
          match a:
            case Arg{rel, e}:
              match rel:
                case Run{}:
                  Tm.push.call(Arg{Run{}, Tm.erase(e)}, Tm.erase(CCall{f, r}))
                case Era{}:
                  Tm.push.call(Arg{Era{}, CBox{}}, Tm.erase(CCall{f, r}))
    case CApp{f, as}:
      match as:
        case Nil{}:
          CApp{Tm.erase(f), Nil{}}
        case a <> r:
          Tm.push(Tm.erase(a), Tm.erase(CApp{f, r}))
    case CCtr{k, as}:
      match as:
        case Nil{}:
          CCtr{k, Nil{}}
        case a <> r:
          Tm.push(Tm.erase(a), Tm.erase(CCtr{k, r}))
    case CLam{p, b}:
      CLam{p, Tm.erase(b)}
    case CLet{p, v, b}:
      CLet{p, Tm.erase(v), Tm.erase(b)}
    case CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Tm.push(Tm.erase(a), Tm.erase(CMat{r, cases}))
        case Nil{}:
          match cases:
            case Nil{}:
              CMat{Nil{}, Nil{}}
            case c <> r:
              Tm.push.case(Tm.erase(c), Tm.erase(CMat{Nil{}, r}))
    case CCse{ps, b}:
      CCse{ps, Tm.erase(b)}
    case CSuc{k, e}:
      CSuc{k, Tm.erase(e)}
    case COp{op, a, b}:
      COp{op, Tm.erase(a), Tm.erase(b)}
    case CAnn{e, ty}:
      CAnn{Tm.erase(e), ty}
    case CTyp{n, as}:
      CBox{}
    case other:
      other

def Tms.erase(ts: List<&2, Tm>) -> List<&2, Tm>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      Tm.erase(t) <> Tms.erase(r)

def Arg.erase(a: Arg) -> Arg:
  match a:
    case Arg{rel, e}:
      match rel:
        case Run{}:
          Arg{Run{}, Tm.erase(e)}
        case Era{}:
          Arg{Era{}, CBox{}}

def Args.erase(as: List<&2, Arg>) -> List<&2, Arg>:
  match as:
    case Nil{}:
      Nil{}
    case a <> r:
      Arg.erase(a) <> Args.erase(r)

def Def.erase(d: Def) -> Def:
  match d:
    case Def{n, ps, b, ret}:
      Def{n, ps, Tm.erase(b), ret}

def Defs.erase(ds: List<&2, Def>) -> List<&2, Def>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Def.erase(d) <> Defs.erase(r)

# Semantics
# =========

# A value: an erased argument is bound unevaluated (VTrm: nothing reads it).
# A scope is a list of bindings, VBnd.
type Val is Data:
  VLit{l: Lit}
  VCtr{k: String, fs: List<&2, Val>}
  VClo{env: List<&2, Val>, p: Pt, b: Tm}
  VFun{f: String, args: List<&2, Val>}
  VTrm{t: Tm}
  VBnd{x: String, v: Val}

type Res is Data:
  ROk{vs: List<&2, Val>}
  REnv{env: List<&2, Val>}
  RNo{}
  RFail{msg: String}

# What to do with a result.
type Kont is Data:
  KCall{f: String}
  KApp{}
  KCtr{k: String}
  KLet{env: List<&2, Val>, p: Pt, b: Tm}
  KBind{b: Tm}
  KMat{env: List<&2, Val>, cases: List<&2, Tm>}
  KCase{env: List<&2, Val>, vs: List<&2, Val>, b: Tm, rest: List<&2, Tm>}
  KSuc{k: U32}
  KOp{op: String}
  KTail{env: List<&2, Val>, es: List<&2, Tm>}
  KATail{env: List<&2, Val>, as: List<&2, Arg>}
  KCons{v: Val}
  KApply{vs: List<&2, Val>}
  KBody{b: Tm, rest: List<&2, Val>}

# A step of the evaluator.
type Sel is Data:
  SEval{env: List<&2, Val>, e: Tm}
  SEvals{env: List<&2, Val>, es: List<&2, Tm>}
  SArgs{env: List<&2, Val>, as: List<&2, Arg>}
  SThen{r: Res, k: Kont}
  SOk{k: Kont, vs: List<&2, Val>}
  SLook{env: List<&2, Val>, x: String}
  SLook2{hit: Bool, v: Val, env: List<&2, Val>, x: String}
  SCallDef{f: String, vs: List<&2, Val>}
  SFind{ds: List<&2, Def>, f: String, vs: List<&2, Val>}
  SFound{hit: Bool, ps: List<&2, Par>, b: Tm, ds: List<&2, Def>, f: String, vs: List<&2, Val>}
  SEnter{short: Bool, f: String, ps: List<&2, Par>, b: Tm, vs: List<&2, Val>}
  SApply{vs: List<&2, Val>, fv: Val}
  SMatch{env: List<&2, Val>, vs: List<&2, Val>, cases: List<&2, Tm>}
  SPat{env: List<&2, Val>, ps: List<&2, Pt>, vs: List<&2, Val>}
  SPatC{hit: Bool, env: List<&2, Val>, ps: List<&2, Pt>, vs: List<&2, Val>}

def Val.push(v: Val, e: Val) -> Val:
  match e:
    case VCtr{k, fs}:
      VCtr{k, v <> fs}
    case VFun{f, as}:
      VFun{f, v <> as}
    case other:
      other

def Val.push.env(b: Val, e: Val) -> Val:
  match e:
    case VClo{env, p, t}:
      VClo{b <> env, p, t}
    case other:
      other

def Val.erase(v: Val) -> Val:
  match v:
    case VCtr{k, fs}:
      match fs:
        case Nil{}:
          VCtr{k, Nil{}}
        case f <> r:
          Val.push(Val.erase(f), Val.erase(VCtr{k, r}))
    case VFun{f, as}:
      match as:
        case Nil{}:
          VFun{f, Nil{}}
        case a <> r:
          Val.push(Val.erase(a), Val.erase(VFun{f, r}))
    case VClo{env, p, b}:
      match env:
        case Nil{}:
          VClo{Nil{}, p, Tm.erase(b)}
        case e <> r:
          Val.push.env(Val.erase(e), Val.erase(VClo{r, p, b}))
    case VBnd{x, y}:
      VBnd{x, Val.erase(y)}
    case VTrm{t}:
      VTrm{CBox{}}
    case VLit{l}:
      VLit{l}

def Vals.erase(vs: List<&2, Val>) -> List<&2, Val>:
  match vs:
    case Nil{}:
      Nil{}
    case v <> r:
      Val.erase(v) <> Vals.erase(r)

def Res.erase(r: Res) -> Res:
  match r:
    case ROk{vs}:
      ROk{Vals.erase(vs)}
    case REnv{env}:
      REnv{Vals.erase(env)}
    case RNo{}:
      RNo{}
    case RFail{m}:
      RFail{m}

def Kont.erase(k: Kont) -> Kont:
  match k:
    case KLet{env, p, b}:
      KLet{Vals.erase(env), p, Tm.erase(b)}
    case KBind{b}:
      KBind{Tm.erase(b)}
    case KMat{env, cases}:
      KMat{Vals.erase(env), Tms.erase(cases)}
    case KCase{env, vs, b, rest}:
      KCase{Vals.erase(env), Vals.erase(vs), Tm.erase(b), Tms.erase(rest)}
    case KTail{env, es}:
      KTail{Vals.erase(env), Tms.erase(es)}
    case KATail{env, as}:
      KATail{Vals.erase(env), Args.erase(as)}
    case KCons{v}:
      KCons{Val.erase(v)}
    case KApply{vs}:
      KApply{Vals.erase(vs)}
    case KBody{b, rest}:
      KBody{Tm.erase(b), Vals.erase(rest)}
    case other:
      other

def Sel.erase(s: Sel) -> Sel:
  match s:
    case SEval{env, e}:
      SEval{Vals.erase(env), Tm.erase(e)}
    case SEvals{env, es}:
      SEvals{Vals.erase(env), Tms.erase(es)}
    case SArgs{env, as}:
      SArgs{Vals.erase(env), Args.erase(as)}
    case SThen{r, k}:
      SThen{Res.erase(r), Kont.erase(k)}
    case SOk{k, vs}:
      SOk{Kont.erase(k), Vals.erase(vs)}
    case SLook{env, x}:
      SLook{Vals.erase(env), x}
    case SLook2{hit, v, env, x}:
      SLook2{hit, Val.erase(v), Vals.erase(env), x}
    case SCallDef{f, vs}:
      SCallDef{f, Vals.erase(vs)}
    case SFind{ds, f, vs}:
      SFind{Defs.erase(ds), f, Vals.erase(vs)}
    case SFound{hit, ps, b, ds, f, vs}:
      SFound{hit, ps, Tm.erase(b), Defs.erase(ds), f, Vals.erase(vs)}
    case SEnter{short, f, ps, b, vs}:
      SEnter{short, f, ps, Tm.erase(b), Vals.erase(vs)}
    case SApply{vs, fv}:
      SApply{Vals.erase(vs), Val.erase(fv)}
    case SMatch{env, vs, cases}:
      SMatch{Vals.erase(env), Vals.erase(vs), Tms.erase(cases)}
    case SPat{env, ps, vs}:
      SPat{Vals.erase(env), ps, Vals.erase(vs)}
    case SPatC{hit, env, ps, vs}:
      SPatC{hit, Vals.erase(env), ps, Vals.erase(vs)}

# The parameters bound to the first values (an erased one too: to its term).
def Scope.bind(ps: List<&2, Par>, vs: List<&2, Val>) -> List<&2, Val>:
  match ps:
    case Nil{}:
      Nil{}
    case Par{x, rel, mode, ty} <> pr:
      match vs:
        case Nil{}:
          Nil{}
        case v <> vr:
          VBnd{x, v} <> Scope.bind(pr, vr)

def Vals.drop(n: Nat, vs: List<&2, Val>) -> List<&2, Val>:
  match n:
    case 0n:
      vs
    case 1n+m:
      match vs:
        case Nil{}:
          Nil{}
        case v <> r:
          Vals.drop(m, r)

def Pars.len(ps: List<&2, Par>) -> Nat:
  match ps:
    case Nil{}:
      0n
    case p <> r:
      1n+Pars.len(r)

def Vals.len(vs: List<&2, Val>) -> Nat:
  match vs:
    case Nil{}:
      0n
    case v <> r:
      1n+Vals.len(r)

def Pts.len(ps: List<&2, Pt>) -> Nat:
  match ps:
    case Nil{}:
      0n
    case p <> r:
      1n+Pts.len(r)

def Vals.cat(a: List<&2, Val>, b: List<&2, Val>) -> List<&2, Val>:
  match a:
    case Nil{}:
      b
    case v <> r:
      v <> Vals.cat(r, b)

def Pts.cat(a: List<&2, Pt>, b: List<&2, Pt>) -> List<&2, Pt>:
  match a:
    case Nil{}:
      b
    case p <> r:
      p <> Pts.cat(r, b)

def Lit.eq(a: Lit, b: Lit) -> Bool:
  match a:
    case LNum{x}:
      match b:
        case LNum{y}:
          U32.is_eq(x, y)
        case other:
          False{}
    case LNat{x}:
      match b:
        case LNat{y}:
          U32.is_eq(x, y)
        case other:
          False{}
    case LFlt{x}:
      match b:
        case LFlt{y}:
          String.eq(x, y)
        case other:
          False{}
    case LStr{x}:
      match b:
        case LStr{y}:
          String.eq(x, y)
        case other:
          False{}

# One pattern against one value, then the rest.
def Pat.step(env: List<&2, Val>, p: Pt, v: Val, ps: List<&2, Pt>, vs: List<&2, Val>) -> Sel:
  match p:
    case PtVar{x}:
      SPat{VBnd{x, v} <> env, ps, vs}
    case PtCtr{+k, +qs}:
      match v:
        case VCtr{+k2, +fs}:
          SPatC{Bool.and(String.eq(k, k2), Nat.is_eq(Pts.len(qs), Vals.len(fs))), env,
            Pts.cat(qs, ps), Vals.cat(fs, vs)}
        case other:
          SPatC{False{}, env, ps, vs}
    case PtNat{n}:
      match v:
        case VLit{l}:
          SPatC{Lit.eq(LNat{n}, l), env, ps, vs}
        case other:
          SPatC{False{}, env, ps, vs}
    case PtNum{n}:
      match v:
        case VLit{l}:
          SPatC{Lit.eq(LNum{n}, l), env, ps, vs}
        case other:
          SPatC{False{}, env, ps, vs}
    case PtFlt{s}:
      match v:
        case VLit{l}:
          SPatC{Lit.eq(LFlt{s}, l), env, ps, vs}
        case other:
          SPatC{False{}, env, ps, vs}
    case PtSuc{+k, q}:
      match v:
        case VLit{l}:
          match l:
            case LNat{+m}:
              SPatC{U32.is_le(k, m), env, q <> ps, VLit{LNat{U32.sub(m, k)}} <> vs}
            case other:
              SPatC{False{}, env, ps, vs}
        case other:
          SPatC{False{}, env, ps, vs}

# The next step after a term.
def Tm.step(env: List<&2, Val>, e: Tm) -> Sel:
  match e:
    case CVar{x}:
      SLook{env, x}
    case CLit{l}:
      SThen{ROk{Nil{}}, KCons{VLit{l}}}
    case CRef{f}:
      SCallDef{f, Nil{}}
    case CLam{p, b}:
      SThen{ROk{Nil{}}, KCons{VClo{env, p, b}}}
    case CAnn{x, ty}:
      SEval{env, x}
    case CTyp{n, as}:
      SThen{ROk{Nil{}}, KCons{VTrm{CBox{}}}}
    case CBox{}:
      SThen{ROk{Nil{}}, KCons{VTrm{CBox{}}}}
    case CErr{m}:
      SThen{RFail{m}, KApp{}}
    case CCse{ps, b}:
      SThen{RFail{"a case outside a match"}, KApp{}}
    case other:
      SEval{env, other}

# The semantics: n steps of s in the program ds, where prim gives the
# natives and operators (a call of a def ds does not have). Every step
# costs one unit of fuel, the same with and without erasure.
def run(~prim: String -> List<&2, Val> -> Res, +n: Nat, +ds: List<&2, Def>, s: Sel) -> Res:
  match n:
    case 0n:
      RFail{"out of fuel"}
    case 1n+p:
      match s:
        case SEval{+env, e}:
          match e:
            case CCall{f, as}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SArgs{env, as}), KCall{f}})
            case CApp{f, as}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEvals{env, f <> as}), KApp{}})
            case CCtr{k, as}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEvals{env, as}), KCtr{k}})
            case CLet{pt, v, b}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEval{env, v}), KLet{env, pt, b}})
            case CMat{scrs, cases}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEvals{env, scrs}), KMat{env, cases}})
            case CSuc{k, x}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEval{env, x}), KSuc{k}})
            case COp{op, a, b}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEvals{env, [a, b]}), KOp{op}})
            case other:
              run(~prim, p, ds, Tm.step(env, other))
        case SEvals{+env, es}:
          match es:
            case Nil{}:
              ROk{Nil{}}
            case e <> r:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEval{env, e}), KTail{env, r}})
        case SArgs{+env, as}:
          match as:
            case Nil{}:
              ROk{Nil{}}
            case a <> r:
              match a:
                case Arg{rel, e}:
                  match rel:
                    case Run{}:
                      run(~prim, p, ds, SThen{run(~prim, p, ds, SEval{env, e}), KATail{env, r}})
                    case Era{}:
                      run(~prim, p, ds, SThen{run(~prim, p, ds, SArgs{env, r}), KCons{VTrm{e}}})
        case SThen{r, k}:
          match r:
            case RFail{m}:
              RFail{m}
            case RNo{}:
              match k:
                case KCase{+env, +vs, b, rest}:
                  run(~prim, p, ds, SMatch{env, vs, rest})
                case other:
                  RFail{"no pattern matches"}
            case REnv{env2}:
              match k:
                case KBind{b}:
                  run(~prim, p, ds, SEval{env2, b})
                case KCase{env, vs, b, rest}:
                  run(~prim, p, ds, SEval{env2, b})
                case KBody{b, rest}:
                  run(~prim, p, ds, SThen{run(~prim, p, ds, SEval{env2, b}), KApply{rest}})
                case other:
                  RFail{"a scope where a value was due"}
            case ROk{vs}:
              run(~prim, p, ds, SOk{k, vs})
        case SOk{k, vs}:
          match k:
            case KCall{f}:
              run(~prim, p, ds, SCallDef{f, vs})
            case KApp{}:
              match vs:
                case Nil{}:
                  RFail{"nothing to call"}
                case f <> r2:
                  run(~prim, p, ds, SApply{r2, f})
            case KCtr{c}:
              ROk{[VCtr{c, vs}]}
            case KMat{+env, cases}:
              run(~prim, p, ds, SMatch{env, vs, cases})
            case KSuc{c}:
              prim("%suc", VLit{LNum{c}} <> vs)
            case KOp{op}:
              prim(op, vs)
            case KCons{v}:
              ROk{v <> vs}
            case KLet{+env, pt, b}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SPat{env, [pt], vs}), KBind{b}})
            case KTail{+env, es}:
              match vs:
                case Nil{}:
                  RFail{"no value"}
                case v <> r2:
                  run(~prim, p, ds, SThen{run(~prim, p, ds, SEvals{env, es}), KCons{v}})
            case KATail{+env, as}:
              match vs:
                case Nil{}:
                  RFail{"no value"}
                case v <> r2:
                  run(~prim, p, ds, SThen{run(~prim, p, ds, SArgs{env, as}), KCons{v}})
            case KApply{rest}:
              match vs:
                case Nil{}:
                  RFail{"no value"}
                case v <> r2:
                  run(~prim, p, ds, SApply{rest, v})
            case other:
              RFail{"a value where a scope was due"}
        case SLook{env, +x}:
          match env:
            case Nil{}:
              RFail{"unbound variable"}
            case b <> r:
              match b:
                case VBnd{+y, v}:
                  run(~prim, p, ds, SLook2{String.eq(y, x), v, r, x})
                case other:
                  run(~prim, p, ds, SLook{r, x})
        case SLook2{hit, v, env, x}:
          match hit:
            case True{}:
              ROk{[v]}
            case False{}:
              run(~prim, p, ds, SLook{env, x})
        case SCallDef{f, vs}:
          run(~prim, p, ds, SFind{ds, f, vs})
        case SFind{ds2, +f, vs}:
          match ds2:
            case Nil{}:
              prim(f, vs)
            case d <> r:
              match d:
                case Def{name, ps, b, ret}:
                  run(~prim, p, ds, SFound{String.eq(name, f), ps, b, r, f, vs})
        case SFound{hit, +ps, b, ds2, +f, +vs}:
          match hit:
            case True{}:
              run(~prim, p, ds, SEnter{Nat.is_lt(Vals.len(vs), Pars.len(ps)), f, ps, b, vs})
            case False{}:
              run(~prim, p, ds, SFind{ds2, f, vs})
        case SEnter{short, f, +ps, b, +vs}:
          match short:
            case True{}:
              ROk{[VFun{f, vs}]}
            case False{}:
              run(~prim, p, ds, SThen{run(~prim, p, ds, SEval{Scope.bind(ps, vs), b}),
                KApply{Vals.drop(Pars.len(ps), vs)}})
        case SApply{vs, fv}:
          match vs:
            case Nil{}:
              ROk{[fv]}
            case v <> r:
              match fv:
                case VClo{env, pt, b}:
                  run(~prim, p, ds, SThen{run(~prim, p, ds, SPat{env, [pt], [v]}), KBody{b, r}})
                case VFun{f, as}:
                  run(~prim, p, ds, SCallDef{f, Vals.cat(as, v <> r)})
                case other:
                  RFail{"not a function"}
        case SMatch{+env, +vs, cases}:
          match cases:
            case Nil{}:
              RFail{"no case matches"}
            case c <> r:
              match c:
                case CCse{ps, b}:
                  run(~prim, p, ds, SThen{run(~prim, p, ds, SPat{env, ps, vs}), KCase{env, vs, b, r}})
                case other:
                  RFail{"not a case"}
        case SPat{env, ps, vs}:
          match ps:
            case Nil{}:
              match vs:
                case Nil{}:
                  REnv{env}
                case v <> r:
                  RNo{}
            case pt <> pr:
              match vs:
                case Nil{}:
                  RNo{}
                case v <> vr:
                  run(~prim, p, ds, Pat.step(env, pt, v, pr, vr))
        case SPatC{hit, env, ps, vs}:
          match hit:
            case True{}:
              run(~prim, p, ds, SPat{env, ps, vs})
            case False{}:
              RNo{}

# A program's result: main, called with no arguments.
def Prog.run(~prim: String -> List<&2, Val> -> Res, n: Nat, ds: List<&2, Def>) -> Res:
  run(~prim, n, ds, SCallDef{"main", Nil{}})

# Reduction
# =========

# The inliner's beta rule (Inl in bendc.bend) as a pass of its own: Tm.red
# makes every lambda applied to one argument a let, and REDPROOF.bend proves
# that this preserves `run` (RED.bend states the law).

def Red.is_lam(f: Tm) -> Bool:
  match f:
    case CLam{p, b}:
      True{}
    case other:
      False{}

# Whether f applied to a, then to r, is a redex.
def Red.is_beta(r: List<&2, Tm>, f: Tm) -> Bool:
  match r:
    case Nil{}:
      Red.is_lam(f)
    case a <> t:
      False{}

def Red.beta(f: Tm, a: Tm) -> Tm:
  match f:
    case CLam{p, b}:
      CLet{p, a, b}
    case other:
      CApp{other, [a]}

# t with its redexes reduced. A list field is walked as its head and the node
# rebuilt with the rest, which is not a node of t (top is False there).
def Tm.red(t: Tm, top: Bool) -> Tm:
  match t:
    case CCall{f, as}:
      match as:
        case Nil{}:
          CCall{f, Nil{}}
        case a <> r:
          match a:
            case Arg{rel, e}:
              Tm.push.call(Arg{rel, Tm.red(e, True{})}, Tm.red(CCall{f, r}, False{}))
    case CApp{+f, as}:
      match as:
        case Nil{}:
          CApp{Tm.red(f, True{}), Nil{}}
        case +a <> +r:
          Bool.pick(Unit -> Tm, Bool.and(top, Red.is_beta(r, f)),
            u => Red.beta(Tm.red(f, True{}), Tm.red(a, True{})),
            u => Tm.push(Tm.red(a, True{}), Tm.red(CApp{f, r}, False{})))(Unit{})
    case CCtr{k, as}:
      match as:
        case Nil{}:
          CCtr{k, Nil{}}
        case a <> r:
          Tm.push(Tm.red(a, True{}), Tm.red(CCtr{k, r}, False{}))
    case CLam{p, b}:
      CLam{p, Tm.red(b, True{})}
    case CLet{p, v, b}:
      CLet{p, Tm.red(v, True{}), Tm.red(b, True{})}
    case CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Tm.push(Tm.red(a, True{}), Tm.red(CMat{r, cases}, False{}))
        case Nil{}:
          match cases:
            case Nil{}:
              CMat{Nil{}, Nil{}}
            case c <> r:
              Tm.push.case(Tm.red(c, True{}), Tm.red(CMat{Nil{}, r}, False{}))
    case CCse{ps, b}:
      CCse{ps, Tm.red(b, True{})}
    case CSuc{k, e}:
      CSuc{k, Tm.red(e, True{})}
    case COp{op, a, b}:
      COp{op, Tm.red(a, True{}), Tm.red(b, True{})}
    case CAnn{e, ty}:
      CAnn{Tm.red(e, True{}), ty}
    case other:
      other

def Tms.red(ts: List<&2, Tm>) -> List<&2, Tm>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      Tm.red(t, True{}) <> Tms.red(r)

def Arg.red(a: Arg) -> Arg:
  match a:
    case Arg{rel, e}:
      Arg{rel, Tm.red(e, True{})}

def Args.red(as: List<&2, Arg>) -> List<&2, Arg>:
  match as:
    case Nil{}:
      Nil{}
    case a <> r:
      Arg.red(a) <> Args.red(r)

def Def.red(d: Def) -> Def:
  match d:
    case Def{n, ps, b, ret}:
      Def{n, ps, Tm.red(b, True{}), ret}

def Defs.red(ds: List<&2, Def>) -> List<&2, Def>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Def.red(d) <> Defs.red(r)

# The pass on the semantics' states: every term in them reduced.
def Val.red(v: Val) -> Val:
  match v:
    case VCtr{k, fs}:
      match fs:
        case Nil{}:
          VCtr{k, Nil{}}
        case f <> r:
          Val.push(Val.red(f), Val.red(VCtr{k, r}))
    case VFun{f, as}:
      match as:
        case Nil{}:
          VFun{f, Nil{}}
        case a <> r:
          Val.push(Val.red(a), Val.red(VFun{f, r}))
    case VClo{env, p, b}:
      match env:
        case Nil{}:
          VClo{Nil{}, p, Tm.red(b, True{})}
        case e <> r:
          Val.push.env(Val.red(e), Val.red(VClo{r, p, b}))
    case VBnd{x, y}:
      VBnd{x, Val.red(y)}
    case VTrm{t}:
      VTrm{Tm.red(t, True{})}
    case VLit{l}:
      VLit{l}

def Vals.red(vs: List<&2, Val>) -> List<&2, Val>:
  match vs:
    case Nil{}:
      Nil{}
    case v <> r:
      Val.red(v) <> Vals.red(r)

def Res.red(r: Res) -> Res:
  match r:
    case ROk{vs}:
      ROk{Vals.red(vs)}
    case REnv{env}:
      REnv{Vals.red(env)}
    case RNo{}:
      RNo{}
    case RFail{m}:
      RFail{m}

def Kont.red(k: Kont) -> Kont:
  match k:
    case KLet{env, p, b}:
      KLet{Vals.red(env), p, Tm.red(b, True{})}
    case KBind{b}:
      KBind{Tm.red(b, True{})}
    case KMat{env, cases}:
      KMat{Vals.red(env), Tms.red(cases)}
    case KCase{env, vs, b, rest}:
      KCase{Vals.red(env), Vals.red(vs), Tm.red(b, True{}), Tms.red(rest)}
    case KTail{env, es}:
      KTail{Vals.red(env), Tms.red(es)}
    case KATail{env, as}:
      KATail{Vals.red(env), Args.red(as)}
    case KCons{v}:
      KCons{Val.red(v)}
    case KApply{vs}:
      KApply{Vals.red(vs)}
    case KBody{b, rest}:
      KBody{Tm.red(b, True{}), Vals.red(rest)}
    case other:
      other

def Sel.red(s: Sel) -> Sel:
  match s:
    case SEval{env, e}:
      SEval{Vals.red(env), Tm.red(e, True{})}
    case SEvals{env, es}:
      SEvals{Vals.red(env), Tms.red(es)}
    case SArgs{env, as}:
      SArgs{Vals.red(env), Args.red(as)}
    case SThen{r, k}:
      SThen{Res.red(r), Kont.red(k)}
    case SOk{k, vs}:
      SOk{Kont.red(k), Vals.red(vs)}
    case SLook{env, x}:
      SLook{Vals.red(env), x}
    case SLook2{hit, v, env, x}:
      SLook2{hit, Val.red(v), Vals.red(env), x}
    case SCallDef{f, vs}:
      SCallDef{f, Vals.red(vs)}
    case SFind{ds, f, vs}:
      SFind{Defs.red(ds), f, Vals.red(vs)}
    case SFound{hit, ps, b, ds, f, vs}:
      SFound{hit, ps, Tm.red(b, True{}), Defs.red(ds), f, Vals.red(vs)}
    case SEnter{short, f, ps, b, vs}:
      SEnter{short, f, ps, Tm.red(b, True{}), Vals.red(vs)}
    case SApply{vs, fv}:
      SApply{Vals.red(vs), Val.red(fv)}
    case SMatch{env, vs, cases}:
      SMatch{Vals.red(env), Vals.red(vs), Tms.red(cases)}
    case SPat{env, ps, vs}:
      SPat{Vals.red(env), ps, Vals.red(vs)}
    case SPatC{hit, env, ps, vs}:
      SPatC{hit, Vals.red(env), ps, Vals.red(vs)}

# Known constructors
# ==================

# The inliner's case-of-known-constructor rule (Inl in bendc.bend) as a pass
# of its own: Tm.known drops each case of a match on K{as} whose pattern is
# another constructor's, and when the first case left is K's with a variable
# for each field, makes the match one on as, with that case alone (bendc
# compiles it as lets: no K is built). KNOWNPROOF.bend proves that this
# preserves `run` (KNOWN.bend states the law).

# Whether every pattern is a variable.
def Known.vars(ps: List<&2, Pt>) -> Bool:
  match ps:
    case Nil{}:
      True{}
    case p <> r:
      match p:
        case PtVar{x}:
          Known.vars(r)
        case other:
          False{}

# Whether there are as many patterns as terms.
def Known.same(ps: List<&2, Pt>, ts: List<&2, Tm>) -> Bool:
  match ps ts:
    case Nil{} Nil{}:
      True{}
    case p <> pr t <> tr:
      Known.same(pr, tr)
    case a b:
      False{}

# A match on K{as} with these cases, resolved as far as it can be.
def Known.cases(+k: String, +as: List<&2, Tm>, cases: List<&2, Tm>) -> Tm:
  match cases:
    case Nil{}:
      CMat{[CCtr{k, as}], Nil{}}
    case c <> +r:
      match c:
        case CCse{ps, +b}:
          match ps:
            case Nil{}:
              CMat{[CCtr{k, as}], CCse{Nil{}, b} <> r}
            case p <> pr:
              match p:
                case PtCtr{+pk, +qs}:
                  match pr:
                    case Nil{}:
                      Bool.pick(Unit -> Tm, String.eq(pk, k),
                        u => Bool.pick(Tm, Bool.and(Known.vars(qs), Known.same(qs, as)), CMat{as, [CCse{qs, b}]},
                          CMat{[CCtr{k, as}], CCse{[PtCtr{pk, qs}], b} <> r}),
                        u => Known.cases(k, as, r))(Unit{})
                    case q <> pr2:
                      CMat{[CCtr{k, as}], CCse{PtCtr{pk, qs} <> q <> pr2, b} <> r}
                case other:
                  CMat{[CCtr{k, as}], CCse{other <> pr, b} <> r}
        case other:
          CMat{[CCtr{k, as}], other <> r}

def Known.mat(scrs: List<&2, Tm>, cases: List<&2, Tm>) -> Tm:
  match scrs:
    case Nil{}:
      CMat{Nil{}, cases}
    case s <> r:
      match s:
        case CCtr{+k, +as}:
          match r:
            case Nil{}:
              Known.cases(k, as, cases)
            case t <> r2:
              CMat{CCtr{k, as} <> t <> r2, cases}
        case other:
          CMat{other <> r, cases}

def Known.node(t: Tm) -> Tm:
  match t:
    case CMat{scrs, cases}:
      Known.mat(scrs, cases)
    case other:
      other

def Known.top(top: Bool, t: Tm) -> Tm:
  match top:
    case True{}:
      Known.node(t)
    case False{}:
      t

# t with its matches on known constructors resolved (top as in Tm.red).
def Tm.known(t: Tm, top: Bool) -> Tm:
  match t:
    case CCall{f, as}:
      match as:
        case Nil{}:
          CCall{f, Nil{}}
        case a <> r:
          match a:
            case Arg{rel, e}:
              Tm.push.call(Arg{rel, Tm.known(e, True{})}, Tm.known(CCall{f, r}, False{}))
    case CApp{f, as}:
      match as:
        case Nil{}:
          CApp{Tm.known(f, True{}), Nil{}}
        case a <> r:
          Tm.push(Tm.known(a, True{}), Tm.known(CApp{f, r}, False{}))
    case CCtr{k, as}:
      match as:
        case Nil{}:
          CCtr{k, Nil{}}
        case a <> r:
          Tm.push(Tm.known(a, True{}), Tm.known(CCtr{k, r}, False{}))
    case CLam{p, b}:
      CLam{p, Tm.known(b, True{})}
    case CLet{p, v, b}:
      CLet{p, Tm.known(v, True{}), Tm.known(b, True{})}
    case CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Known.top(top, Tm.push(Tm.known(a, True{}), Tm.known(CMat{r, cases}, False{})))
        case Nil{}:
          match cases:
            case Nil{}:
              Known.top(top, CMat{Nil{}, Nil{}})
            case c <> r:
              Known.top(top, Tm.push.case(Tm.known(c, True{}), Tm.known(CMat{Nil{}, r}, False{})))
    case CCse{ps, b}:
      CCse{ps, Tm.known(b, True{})}
    case CSuc{k, e}:
      CSuc{k, Tm.known(e, True{})}
    case COp{op, a, b}:
      COp{op, Tm.known(a, True{}), Tm.known(b, True{})}
    case CAnn{e, ty}:
      CAnn{Tm.known(e, True{}), ty}
    case other:
      other

def Tms.known(ts: List<&2, Tm>) -> List<&2, Tm>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      Tm.known(t, True{}) <> Tms.known(r)

def Arg.known(a: Arg) -> Arg:
  match a:
    case Arg{rel, e}:
      Arg{rel, Tm.known(e, True{})}

def Args.known(as: List<&2, Arg>) -> List<&2, Arg>:
  match as:
    case Nil{}:
      Nil{}
    case a <> r:
      Arg.known(a) <> Args.known(r)

def Def.known(d: Def) -> Def:
  match d:
    case Def{n, ps, b, ret}:
      Def{n, ps, Tm.known(b, True{}), ret}

def Defs.known(ds: List<&2, Def>) -> List<&2, Def>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Def.known(d) <> Defs.known(r)

# The pass on the semantics' states: every term in them resolved.
def Val.known(v: Val) -> Val:
  match v:
    case VCtr{k, fs}:
      match fs:
        case Nil{}:
          VCtr{k, Nil{}}
        case f <> r:
          Val.push(Val.known(f), Val.known(VCtr{k, r}))
    case VFun{f, as}:
      match as:
        case Nil{}:
          VFun{f, Nil{}}
        case a <> r:
          Val.push(Val.known(a), Val.known(VFun{f, r}))
    case VClo{env, p, b}:
      match env:
        case Nil{}:
          VClo{Nil{}, p, Tm.known(b, True{})}
        case e <> r:
          Val.push.env(Val.known(e), Val.known(VClo{r, p, b}))
    case VBnd{x, y}:
      VBnd{x, Val.known(y)}
    case VTrm{t}:
      VTrm{Tm.known(t, True{})}
    case VLit{l}:
      VLit{l}

def Vals.known(vs: List<&2, Val>) -> List<&2, Val>:
  match vs:
    case Nil{}:
      Nil{}
    case v <> r:
      Val.known(v) <> Vals.known(r)

def Res.known(r: Res) -> Res:
  match r:
    case ROk{vs}:
      ROk{Vals.known(vs)}
    case REnv{env}:
      REnv{Vals.known(env)}
    case RNo{}:
      RNo{}
    case RFail{m}:
      RFail{m}

def Kont.known(k: Kont) -> Kont:
  match k:
    case KLet{env, p, b}:
      KLet{Vals.known(env), p, Tm.known(b, True{})}
    case KBind{b}:
      KBind{Tm.known(b, True{})}
    case KMat{env, cases}:
      KMat{Vals.known(env), Tms.known(cases)}
    case KCase{env, vs, b, rest}:
      KCase{Vals.known(env), Vals.known(vs), Tm.known(b, True{}), Tms.known(rest)}
    case KTail{env, es}:
      KTail{Vals.known(env), Tms.known(es)}
    case KATail{env, as}:
      KATail{Vals.known(env), Args.known(as)}
    case KCons{v}:
      KCons{Val.known(v)}
    case KApply{vs}:
      KApply{Vals.known(vs)}
    case KBody{b, rest}:
      KBody{Tm.known(b, True{}), Vals.known(rest)}
    case other:
      other

def Sel.known(s: Sel) -> Sel:
  match s:
    case SEval{env, e}:
      SEval{Vals.known(env), Tm.known(e, True{})}
    case SEvals{env, es}:
      SEvals{Vals.known(env), Tms.known(es)}
    case SArgs{env, as}:
      SArgs{Vals.known(env), Args.known(as)}
    case SThen{r, k}:
      SThen{Res.known(r), Kont.known(k)}
    case SOk{k, vs}:
      SOk{Kont.known(k), Vals.known(vs)}
    case SLook{env, x}:
      SLook{Vals.known(env), x}
    case SLook2{hit, v, env, x}:
      SLook2{hit, Val.known(v), Vals.known(env), x}
    case SCallDef{f, vs}:
      SCallDef{f, Vals.known(vs)}
    case SFind{ds, f, vs}:
      SFind{Defs.known(ds), f, Vals.known(vs)}
    case SFound{hit, ps, b, ds, f, vs}:
      SFound{hit, ps, Tm.known(b, True{}), Defs.known(ds), f, Vals.known(vs)}
    case SEnter{short, f, ps, b, vs}:
      SEnter{short, f, ps, Tm.known(b, True{}), Vals.known(vs)}
    case SApply{vs, fv}:
      SApply{Vals.known(vs), Val.known(fv)}
    case SMatch{env, vs, cases}:
      SMatch{Vals.known(env), Vals.known(vs), Tms.known(cases)}
    case SPat{env, ps, vs}:
      SPat{Vals.known(env), ps, Vals.known(vs)}
    case SPatC{hit, env, ps, vs}:
      SPatC{hit, Vals.known(env), ps, Vals.known(vs)}

# Dead lets
# =========

# The dead-let rule as a pass: Tm.dead drops each let of a variable that no
# lookup in its body reaches, with its value (which is not evaluated).
# DEADPROOF.bend proves that a run that does not fail gives a related result
# with the lets dropped (DEAD.bend states the law).

# Whether none of hs is y.
def Dead.none(hs: List<&2, String>, +y: String) -> Bool:
  match hs:
    case Nil{}:
      True{}
    case z <> r:
      Bool.and(Bool.not(String.eq(z, y)), Dead.none(r, y))

def Dead.cat(a: List<&2, String>, b: List<&2, String>) -> List<&2, String>:
  match a:
    case Nil{}:
      b
    case x <> r:
      x <> Dead.cat(r, b)

# The variables of ps, in the order a match binds them.
def Dead.names(ps: List<&2, Pt>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> r:
      match p:
        case PtVar{x}:
          x <> Dead.names(r)
        case PtCtr{k, qs}:
          Dead.cat(Dead.names(qs), Dead.names(r))
        case PtSuc{k, q}:
          Dead.names(q <> r)
        case PtNat{n}:
          Dead.names(r)
        case PtNum{n}:
          Dead.names(r)
        case PtFlt{s}:
          Dead.names(r)

# Whether a lookup in t reaches a binding of x made before t's scope, past
# the bindings of hs (made in t's scope, the nearest last).
def Dead.used(t: Tm, +hs: List<&2, String>, +x: String) -> Bool:
  match t:
    case CVar{+y}:
      Bool.and(String.eq(x, y), Dead.none(hs, y))
    case CCall{f, as}:
      match as:
        case Nil{}:
          False{}
        case a <> r:
          match a:
            case Arg{rel, e}:
              Bool.or(Dead.used(e, hs, x), Dead.used(CCall{f, r}, hs, x))
    case CApp{f, as}:
      match as:
        case Nil{}:
          Dead.used(f, hs, x)
        case a <> r:
          Bool.or(Dead.used(a, hs, x), Dead.used(CApp{f, r}, hs, x))
    case CCtr{k, as}:
      match as:
        case Nil{}:
          False{}
        case a <> r:
          Bool.or(Dead.used(a, hs, x), Dead.used(CCtr{k, r}, hs, x))
    case CLam{p, b}:
      Dead.used(b, Dead.cat(hs, Dead.names([p])), x)
    case CLet{p, v, b}:
      Bool.or(Dead.used(v, hs, x), Dead.used(b, Dead.cat(hs, Dead.names([p])), x))
    case CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Bool.or(Dead.used(a, hs, x), Dead.used(CMat{r, cases}, hs, x))
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case c <> r:
              Bool.or(Dead.used(c, hs, x), Dead.used(CMat{Nil{}, r}, hs, x))
    case CCse{ps, b}:
      Dead.used(b, Dead.cat(hs, Dead.names(ps)), x)
    case CSuc{k, e}:
      Dead.used(e, hs, x)
    case COp{op, a, b}:
      Bool.or(Dead.used(a, hs, x), Bool.or(Dead.used(b, hs, x), False{}))
    case CAnn{e, ty}:
      Dead.used(e, hs, x)
    case CLit{l}:
      False{}
    case CRef{f}:
      False{}
    case CTyp{n, as}:
      False{}
    case CBox{}:
      False{}
    case CErr{m}:
      False{}

def Dead.pick(u: Bool, x: String, v: Tm, b: Tm) -> Tm:
  match u:
    case True{}:
      CLet{PtVar{x}, v, b}
    case False{}:
      b

# A let of v to p with the body b: b alone if p is a variable b does not use.
def Dead.let(p: Pt, v: Tm, +b: Tm) -> Tm:
  match p:
    case PtVar{+x}:
      Dead.pick(Dead.used(b, Nil{}, x), x, v, b)
    case PtCtr{k, qs}:
      CLet{PtCtr{k, qs}, v, b}
    case PtNat{n}:
      CLet{PtNat{n}, v, b}
    case PtSuc{k, q}:
      CLet{PtSuc{k, q}, v, b}
    case PtNum{n}:
      CLet{PtNum{n}, v, b}
    case PtFlt{s}:
      CLet{PtFlt{s}, v, b}

# t with its dead lets dropped.
def Tm.dead(t: Tm) -> Tm:
  match t:
    case CCall{f, as}:
      match as:
        case Nil{}:
          CCall{f, Nil{}}
        case a <> r:
          match a:
            case Arg{rel, e}:
              Tm.push.call(Arg{rel, Tm.dead(e)}, Tm.dead(CCall{f, r}))
    case CApp{f, as}:
      match as:
        case Nil{}:
          CApp{Tm.dead(f), Nil{}}
        case a <> r:
          Tm.push(Tm.dead(a), Tm.dead(CApp{f, r}))
    case CCtr{k, as}:
      match as:
        case Nil{}:
          CCtr{k, Nil{}}
        case a <> r:
          Tm.push(Tm.dead(a), Tm.dead(CCtr{k, r}))
    case CLam{p, b}:
      CLam{p, Tm.dead(b)}
    case CLet{p, v, b}:
      Dead.let(p, Tm.dead(v), Tm.dead(b))
    case CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Tm.push(Tm.dead(a), Tm.dead(CMat{r, cases}))
        case Nil{}:
          match cases:
            case Nil{}:
              CMat{Nil{}, Nil{}}
            case c <> r:
              Tm.push.case(Tm.dead(c), Tm.dead(CMat{Nil{}, r}))
    case CCse{ps, b}:
      CCse{ps, Tm.dead(b)}
    case CSuc{k, e}:
      CSuc{k, Tm.dead(e)}
    case COp{op, a, b}:
      COp{op, Tm.dead(a), Tm.dead(b)}
    case CAnn{e, ty}:
      CAnn{Tm.dead(e), ty}
    case other:
      other

def Tms.dead(ts: List<&2, Tm>) -> List<&2, Tm>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      Tm.dead(t) <> Tms.dead(r)

def Arg.dead(a: Arg) -> Arg:
  match a:
    case Arg{rel, e}:
      Arg{rel, Tm.dead(e)}

def Args.dead(as: List<&2, Arg>) -> List<&2, Arg>:
  match as:
    case Nil{}:
      Nil{}
    case a <> r:
      Arg.dead(a) <> Args.dead(r)

def Def.dead(d: Def) -> Def:
  match d:
    case Def{n, ps, b, ret}:
      Def{n, ps, Tm.dead(b), ret}

def Defs.dead(ds: List<&2, Def>) -> List<&2, Def>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Def.dead(d) <> Defs.dead(r)

# The pass on values and results (DEAD.bend relates the states).
def Val.dead(v: Val) -> Val:
  match v:
    case VCtr{k, fs}:
      match fs:
        case Nil{}:
          VCtr{k, Nil{}}
        case f <> r:
          Val.push(Val.dead(f), Val.dead(VCtr{k, r}))
    case VFun{f, as}:
      match as:
        case Nil{}:
          VFun{f, Nil{}}
        case a <> r:
          Val.push(Val.dead(a), Val.dead(VFun{f, r}))
    case VClo{env, p, b}:
      match env:
        case Nil{}:
          VClo{Nil{}, p, Tm.dead(b)}
        case e <> r:
          Val.push.env(Val.dead(e), Val.dead(VClo{r, p, b}))
    case VBnd{x, y}:
      VBnd{x, Val.dead(y)}
    case VTrm{t}:
      VTrm{Tm.dead(t)}
    case VLit{l}:
      VLit{l}

def Vals.dead(vs: List<&2, Val>) -> List<&2, Val>:
  match vs:
    case Nil{}:
      Nil{}
    case v <> r:
      Val.dead(v) <> Vals.dead(r)

def Res.dead(r: Res) -> Res:
  match r:
    case ROk{vs}:
      ROk{Vals.dead(vs)}
    case REnv{env}:
      REnv{Vals.dead(env)}
    case RNo{}:
      RNo{}
    case RFail{m}:
      RFail{m}

# Literals
# ========

# The literal rule as a pass: Tm.lit puts a let's number in the place of
# each lookup of its variable in the let's body (the dead-let pass then
# drops the let). A string is left bound, so that it is built once.
# LITPROOF.bend proves that a run that does not fail gives a related result
# (LIT.bend states the law).

# What the pass knows of the bindings made in a term's scope, the nearest
# first: a let's literal (Sub), or a binding it does not know (Opq).
type Sub is Data:
  Sub{x: String, l: Lit}
  Opq{x: String}

def Sub.sel(h: Bool, a: Tm, b: Tm) -> Tm:
  match h:
    case True{}:
      a
    case False{}:
      b

# What a lookup of y becomes: the literal of the nearest binding of y, if
# the pass knows it, or the lookup.
def Sub.find(s: List<&2, Sub>, +y: String) -> Tm:
  match s:
    case Nil{}:
      CVar{y}
    case b <> r:
      match b:
        case Sub{x, l}:
          Sub.sel(String.eq(x, y), CLit{l}, Sub.find(r, y))
        case Opq{x}:
          Sub.sel(String.eq(x, y), CVar{y}, Sub.find(r, y))

# s with bindings of xs in front, in the order a match makes them.
def Sub.bind(xs: List<&2, String>, s: List<&2, Sub>) -> List<&2, Sub>:
  match xs:
    case Nil{}:
      s
    case x <> r:
      Sub.bind(r, Opq{x} <> s)

# t with the literals s knows in the place of their lookups. A list field
# is walked as its head and the node rebuilt with the rest.
def Tm.lits(t: Tm, +s: List<&2, Sub>) -> Tm:
  match t:
    case CVar{+y}:
      Sub.find(s, y)
    case CCall{f, as}:
      match as:
        case Nil{}:
          CCall{f, Nil{}}
        case a <> r:
          match a:
            case Arg{rel, e}:
              match rel:
                case Run{}:
                  Tm.push.call(Arg{Run{}, Tm.lits(e, s)}, Tm.lits(CCall{f, r}, s))
                case Era{}:
                  Tm.push.call(Arg{Era{}, e}, Tm.lits(CCall{f, r}, s))
    case CApp{f, as}:
      match as:
        case Nil{}:
          CApp{Tm.lits(f, s), Nil{}}
        case a <> r:
          Tm.push(Tm.lits(a, s), Tm.lits(CApp{f, r}, s))
    case CCtr{k, as}:
      match as:
        case Nil{}:
          CCtr{k, Nil{}}
        case a <> r:
          Tm.push(Tm.lits(a, s), Tm.lits(CCtr{k, r}, s))
    case CLam{+p, b}:
      CLam{p, Tm.lits(b, Sub.bind(Dead.names([p]), s))}
    case CLet{p, v, b}:
      match p:
        case PtVar{+x}:
          match v:
            case CLit{l}:
              match l:
                case LNum{+n}:
                  CLet{PtVar{x}, CLit{LNum{n}}, Tm.lits(b, Sub{x, LNum{n}} <> s)}
                case LNat{+n}:
                  CLet{PtVar{x}, CLit{LNat{n}}, Tm.lits(b, Sub{x, LNat{n}} <> s)}
                case LFlt{+f}:
                  CLet{PtVar{x}, CLit{LFlt{f}}, Tm.lits(b, Sub{x, LFlt{f}} <> s)}
                case LStr{z}:
                  CLet{PtVar{x}, CLit{LStr{z}}, Tm.lits(b, Opq{x} <> s)}
            case other:
              CLet{PtVar{x}, Tm.lits(other, s), Tm.lits(b, Opq{x} <> s)}
        case +other:
          CLet{other, Tm.lits(v, s), Tm.lits(b, Sub.bind(Dead.names([other]), s))}
    case CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Tm.push(Tm.lits(a, s), Tm.lits(CMat{r, cases}, s))
        case Nil{}:
          match cases:
            case Nil{}:
              CMat{Nil{}, Nil{}}
            case c <> r:
              Tm.push.case(Tm.lits(c, s), Tm.lits(CMat{Nil{}, r}, s))
    case CCse{+ps, b}:
      CCse{ps, Tm.lits(b, Sub.bind(Dead.names(ps), s))}
    case CSuc{k, e}:
      CSuc{k, Tm.lits(e, s)}
    case COp{op, a, b}:
      COp{op, Tm.lits(a, s), Tm.lits(b, s)}
    case CAnn{e, ty}:
      CAnn{Tm.lits(e, s), ty}
    case other:
      other

def Tms.lits(ts: List<&2, Tm>, +s: List<&2, Sub>) -> List<&2, Tm>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      Tm.lits(t, s) <> Tms.lits(r, s)

def Args.lits(as: List<&2, Arg>, +s: List<&2, Sub>) -> List<&2, Arg>:
  match as:
    case Nil{}:
      Nil{}
    case a <> r:
      match a:
        case Arg{rel, e}:
          match rel:
            case Run{}:
              Arg{Run{}, Tm.lits(e, s)} <> Args.lits(r, s)
            case Era{}:
              Arg{Era{}, e} <> Args.lits(r, s)

def Tm.lit(t: Tm) -> Tm:
  Tm.lits(t, Nil{})

def Def.lit(d: Def) -> Def:
  match d:
    case Def{n, ps, b, ret}:
      Def{n, ps, Tm.lit(b), ret}

def Defs.lit(ds: List<&2, Def>) -> List<&2, Def>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Def.lit(d) <> Defs.lit(r)
