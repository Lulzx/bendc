import Base
import ./core.bend as Core

# The laws of core.bend's lowering (Lo) and raising (Up), and the words
# they are stated in. LOPROOF.bend proves them.
#
# There is no semantics for bendc's syntax tree (Expr) here, so these laws
# do not say that lowering keeps a def's meaning. They say that it loses
# nothing (raising a lowered term gives the term back), and that a lowered
# def never fails a variable lookup when `run` runs it: each variable Lo
# emits is bound where it runs.

# Round trip
# ==========

law up_lo:
  for e: Core.Expr
  for ms: Map<&2, List<&2, Bool>>
  for bound: List<&2, String>
  for top: Bool
  for mask: List<&2, Bool>
  {e == Core.Up.go(Core.Lo.go(e, ms, bound, top, mask)) : Core.Expr}

law up_lo_pat:
  for p: Core.Pat
  {p == Core.Up.pat(Core.Lo.pat(p)) : Core.Pat}

law up_lo_params:
  for ps: List<&2, Core.Param>
  for mask: List<&2, Bool>
  {ps == Core.Up.params(Core.Lo.params(ps, mask)) : List<&2, Core.Param>}

# Scopes
# ======

# The names a scope binds, the nearest first (what a lookup finds).
def Env.names(env: List<&2, Core.Val>) -> List<&2, String>:
  match env:
    case Nil{}:
      Nil{}
    case b <> r:
      match b:
        case Core.VBnd{x, v}:
          x <> Env.names(r)
        case Core.VLit{l}:
          Env.names(r)
        case Core.VCtr{k, fs}:
          Env.names(r)
        case Core.VClo{e, p, t}:
          Env.names(r)
        case Core.VFun{f, as}:
          Env.names(r)
        case Core.VTrm{t}:
          Env.names(r)

def Pars.names(ps: List<&2, Core.Par>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> r:
      match p:
        case Core.Par{x, rel, m, ty}:
          x <> Pars.names(r)

def Unbound(m: String) -> Data:
  {False{} == String.eq(m, "unbound variable") : Bool}

# Each lookup of t is of a name of L or of one t binds, and no failure t
# writes is the one of a lookup (a type's arguments do not run).
def Scoped(t: Core.Tm, -L: List<&2, String>) -> Data:
  match t:
    case Core.CVar{x}:
      {False{} == Core.Dead.none(L, x) : Bool}
    case Core.CLit{l}:
      Unit
    case Core.CRef{f}:
      Unit
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          Unit
        case a <> r:
          match a:
            case Core.Arg{rel, e}:
              Sigma<&2, &2, Scoped(e, L), _ => Scoped(Core.CCall{f, r}, L)>
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Scoped(f, L)
        case a <> r:
          Sigma<&2, &2, Scoped(a, L), _ => Scoped(Core.CApp{f, r}, L)>
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          Unit
        case a <> r:
          Sigma<&2, &2, Scoped(a, L), _ => Scoped(Core.CCtr{k, r}, L)>
    case Core.CLam{p, b}:
      Scoped(b, Core.Lo.bind(Core.Dead.names([p]), L))
    case Core.CLet{p, v, b}:
      Sigma<&2, &2, Scoped(v, L), _ => Scoped(b, Core.Lo.bind(Core.Dead.names([p]), L))>
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Sigma<&2, &2, Scoped(a, L), _ => Scoped(Core.CMat{r, cases}, L)>
        case Nil{}:
          match cases:
            case Nil{}:
              Unit
            case c <> r:
              Sigma<&2, &2, Scoped(c, L), _ => Scoped(Core.CMat{Nil{}, r}, L)>
    case Core.CCse{ps, b}:
      Scoped(b, Core.Lo.bind(Core.Dead.names(ps), L))
    case Core.CSuc{k, e}:
      Scoped(e, L)
    case Core.COp{op, a, b}:
      Sigma<&2, &2, Scoped(a, L), _ => Scoped(b, L)>
    case Core.CAnn{e, ty}:
      Scoped(e, L)
    case Core.CTyp{n, as}:
      Unit
    case Core.CBox{}:
      Unit
    case Core.CErr{m}:
      Unbound(m)

def Scopeds(ts: List<&2, Core.Tm>, -L: List<&2, String>) -> Data:
  match ts:
    case Nil{}:
      Unit
    case t <> r:
      Sigma<&2, &2, Scoped(t, L), _ => Scopeds(r, L)>

def Scoped.args(as: List<&2, Core.Arg>, -L: List<&2, String>) -> Data:
  match as:
    case Nil{}:
      Unit
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          Sigma<&2, &2, Scoped(e, L), _ => Scoped.args(r, L)>

# A def's body is scoped by its parameters (bound as a call binds them).
def Good.defs(ds: List<&2, Core.Def>) -> Data:
  match ds:
    case Nil{}:
      Unit
    case d <> r:
      match d:
        case Core.Def{name, ps, b, ret}:
          Sigma<&2, &2, Scoped(b, Core.Lo.bind(Pars.names(ps), Nil{})), _ => Good.defs(r)>

# A closure's body is scoped by its scope and its pattern (Goods, a value's
# fields, is defined after Good: a reference to it sits under a binder).
def Good(v: Core.Val) -> Data:
  match v:
    case Core.VLit{l}:
      Unit
    case Core.VCtr{k, fs}:
      Sigma<&2, &2, Unit, _ => Goods(fs)>
    case Core.VClo{env, p, b}:
      Sigma<&2, &2, Scoped(b, Core.Lo.bind(Core.Dead.names([p]), Env.names(env))), _ => Goods(env)>
    case Core.VFun{f, as}:
      Sigma<&2, &2, Unit, _ => Goods(as)>
    case Core.VTrm{t}:
      Unit
    case Core.VBnd{x, w}:
      Good(w)

def Goods(vs: List<&2, Core.Val>) -> Data:
  match vs:
    case Nil{}:
      Unit
    case v <> r:
      Sigma<&2, &2, Good(v), _ => Goods(r)>

# A result: F is the names a scope it gives binds (a match's).
def Good.res(r: Core.Res, -F: List<&2, String>) -> Data:
  match r:
    case Core.ROk{vs}:
      Goods(vs)
    case Core.REnv{env}:
      Sigma<&2, &2, {Env.names(env) == F : List<&2, String>}, _ => Goods(env)>
    case Core.RNo{}:
      Unit
    case Core.RFail{m}:
      Unbound(m)

# What a native gives.
def Good.prim(r: Core.Res) -> Data:
  match r:
    case Core.ROk{vs}:
      Goods(vs)
    case Core.REnv{env}:
      Empty
    case Core.RNo{}:
      Unit
    case Core.RFail{m}:
      Unbound(m)

# A continuation: F is the names of the scope it takes (a match's).
def Good.k(k: Core.Kont, -F: List<&2, String>) -> Data:
  match k:
    case Core.KCall{f}:
      Unit
    case Core.KApp{}:
      Unit
    case Core.KCtr{c}:
      Unit
    case Core.KLet{env, p, b}:
      Sigma<&2, &2, Goods(env), _ => Scoped(b, Core.Lo.bind(Core.Dead.names([p]), Env.names(env)))>
    case Core.KBind{b}:
      Scoped(b, F)
    case Core.KMat{env, cases}:
      Sigma<&2, &2, Goods(env), _ => Scopeds(cases, Env.names(env))>
    case Core.KCase{env, vs, b, rest}:
      Sigma<&2, &2, Goods(env), _ => Sigma<&2, &2, Goods(vs), _ => Sigma<&2, &2, Scoped(b, F), _ => Scopeds(rest, Env.names(env))>>>
    case Core.KSuc{c}:
      Unit
    case Core.KOp{op}:
      Unit
    case Core.KTail{env, es}:
      Sigma<&2, &2, Goods(env), _ => Scopeds(es, Env.names(env))>
    case Core.KATail{env, as}:
      Sigma<&2, &2, Goods(env), _ => Scoped.args(as, Env.names(env))>
    case Core.KCons{v}:
      Good(v)
    case Core.KApply{vs}:
      Goods(vs)
    case Core.KBody{b, rest}:
      Sigma<&2, &2, Scoped(b, F), _ => Goods(rest)>

def Look.ok(hit: Bool, env: List<&2, Core.Val>, x: String) -> Data:
  match hit:
    case True{}:
      Unit
    case False{}:
      {False{} == Core.Dead.none(Env.names(env), x) : Bool}

def Enter.ok(short: Bool, vs: List<&2, Core.Val>, ps: List<&2, Core.Par>) -> Data:
  match short:
    case True{}:
      Unit
    case False{}:
      {False{} == Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)) : Bool}

def Pat.ok(env: List<&2, Core.Val>, ps: List<&2, Core.Pt>, vs: List<&2, Core.Val>, -F: List<&2, String>) -> Data:
  Sigma<&2, &2, Goods(env), _ => Sigma<&2, &2, Goods(vs),
    _ => {Core.Lo.bind(Core.Dead.names(ps), Env.names(env)) == F : List<&2, String>}>>

# A state: F is the names of the scope it gives, if it gives one (a match).
def Good.sel(s: Core.Sel, -F: List<&2, String>) -> Data:
  match s:
    case Core.SEval{env, e}:
      Sigma<&2, &2, Goods(env), _ => Scoped(e, Env.names(env))>
    case Core.SEvals{env, es}:
      Sigma<&2, &2, Goods(env), _ => Scopeds(es, Env.names(env))>
    case Core.SArgs{env, as}:
      Sigma<&2, &2, Goods(env), _ => Scoped.args(as, Env.names(env))>
    case Core.SThen{r, k}:
      Sigma<&2, &2, List<&2, String>, F2 => Sigma<&2, &2, Good.res(r, F2), _ => Good.k(k, F2)>>
    case Core.SOk{k, vs}:
      Sigma<&2, &2, Goods(vs), _ => Sigma<&2, &2, List<&2, String>, F2 => Good.k(k, F2)>>
    case Core.SLook{env, x}:
      Sigma<&2, &2, Goods(env), _ => {False{} == Core.Dead.none(Env.names(env), x) : Bool}>
    case Core.SLook2{hit, v, env, x}:
      Sigma<&2, &2, Good(v), _ => Sigma<&2, &2, Goods(env), _ => Look.ok(hit, env, x)>>
    case Core.SCallDef{f, vs}:
      Goods(vs)
    case Core.SFind{ds, f, vs}:
      Sigma<&2, &2, Goods(vs), _ => Good.defs(ds)>
    case Core.SFound{hit, ps, b, ds, f, vs}:
      Sigma<&2, &2, Goods(vs), _ => Sigma<&2, &2, Good.defs(ds), _ => Scoped(b, Core.Lo.bind(Pars.names(ps), Nil{}))>>
    case Core.SEnter{short, f, ps, b, vs}:
      Sigma<&2, &2, Goods(vs), _ => Sigma<&2, &2, Scoped(b, Core.Lo.bind(Pars.names(ps), Nil{})), _ => Enter.ok(short, vs, ps)>>
    case Core.SApply{vs, fv}:
      Sigma<&2, &2, Goods(vs), _ => Good(fv)>
    case Core.SMatch{env, vs, cases}:
      Sigma<&2, &2, Goods(env), _ => Sigma<&2, &2, Goods(vs), _ => Scopeds(cases, Env.names(env))>>
    case Core.SPat{env, ps, vs}:
      Pat.ok(env, ps, vs, F)
    case Core.SPatC{hit, env, ps, vs}:
      match hit:
        case True{}:
          Pat.ok(env, ps, vs, F)
        case False{}:
          Unit

# A result that is not a failed lookup.
def NoUnbound(r: Core.Res) -> Data:
  match r:
    case Core.ROk{vs}:
      Unit
    case Core.REnv{env}:
      Unit
    case Core.RNo{}:
      Unit
    case Core.RFail{m}:
      Unbound(m)

# No failure the term writes is the one of a lookup.
def NoErr(e: Core.Expr) -> Data:
  match e:
    case Core.EVar{n}:
      Unit
    case Core.ENum{n}:
      Unit
    case Core.ENat{n}:
      Unit
    case Core.EFlt{s}:
      Unit
    case Core.EStr{s}:
      Unit
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          NoErr(f)
        case a <> t:
          Sigma<&2, &2, NoErr(a), _ => NoErr(Core.ECall{f, t})>
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Unit
        case a <> t:
          Sigma<&2, &2, NoErr(a), _ => NoErr(Core.ECtor{n, t})>
    case Core.ELam{p, b}:
      NoErr(b)
    case Core.ELet{p, v, b}:
      Sigma<&2, &2, NoErr(v), _ => NoErr(b)>
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Sigma<&2, &2, NoErr(a), _ => NoErr(Core.EMatch{t, cases})>
        case Nil{}:
          match cases:
            case Nil{}:
              Unit
            case c <> t:
              Sigma<&2, &2, NoErr(c), _ => NoErr(Core.EMatch{Nil{}, t})>
    case Core.ECase{ps, b}:
      NoErr(b)
    case Core.ESucc{k, x}:
      NoErr(x)
    case Core.EOp{op, a, b}:
      Sigma<&2, &2, NoErr(a), _ => NoErr(b)>
    case Core.EAnn{x, ty}:
      NoErr(x)
    case Core.ETy{n, args}:
      Unit
    case Core.EErr{m}:
      Unbound(m)

# A def before lowering.
type Src is Data:
  Src{name: String, ps: List<&2, Core.Param>, body: Core.Expr, ret: Core.Expr}

def Src.lo(+ms: Map<&2, List<&2, Bool>>, xs: List<&2, Src>) -> List<&2, Core.Def>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> r:
      match x:
        case Src{name, ps, body, ret}:
          Core.Lo.def(ms, name, ps, body, ret) <> Src.lo(ms, r)

def Src.ok(xs: List<&2, Src>) -> Data:
  match xs:
    case Nil{}:
      Unit
    case x <> r:
      match x:
        case Src{name, ps, body, ret}:
          Sigma<&2, &2, NoErr(body), _ => Src.ok(r)>

# Lowering scopes
# ===============

# Each variable Lo emits is one of bound or bound in the term.
law lo_scoped:
  for e: Core.Expr
  for ms: Map<&2, List<&2, Bool>>
  for bound: List<&2, String>
  for top: Bool
  for mask: List<&2, Bool>
  for ok: NoErr(e)
  Scoped(Core.Lo.go(e, ms, bound, top, mask), bound)

# A run of a scoped state never fails a lookup (natives as ok says).
law scope_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> Goods(vs) -> Good.prim(prim(op, vs))
  for n: Nat
  for ds: List<&2, Core.Def>
  for gd: Good.defs(ds)
  for s: Core.Sel
  for F: List<&2, String>
  for g: Good.sel(s, F)
  Good.res(Core.run(~prim, n, ds, s), F)

# A program of lowered defs never fails a variable lookup.
law lo_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> Goods(vs) -> Good.prim(prim(op, vs))
  for n: Nat
  for ms: Map<&2, List<&2, Bool>>
  for xs: List<&2, Src>
  for sok: Src.ok(xs)
  NoUnbound(Core.Prog.run(~prim, n, Src.lo(ms, xs)))
