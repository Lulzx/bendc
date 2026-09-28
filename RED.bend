import Base
import ./core.bend as Core

# The law that core.bend's reduction pass (Tm.red) preserves `run`, and the
# words it is stated in. REDPROOF.bend proves it.

# Fuel
# ====

# a <= b.
def Le(a: Nat, b: Nat) -> Data:
  match a:
    case 0n:
      Unit
    case 1n+x:
      match b:
        case 0n:
          Empty
        case 1n+y:
          Le(x, y)

def NotOof.m(b: Bool) -> Data:
  match b:
    case True{}:
      Empty
    case False{}:
      Unit

# That a result is not the failure `run` gives out of fuel.
def NotOof(r: Core.Res) -> Data:
  match r:
    case Core.RFail{m}:
      NotOof.m(String.eq(m, "out of fuel"))
    case other:
      Unit

# Shapes
# ======

# The values a run gives: n of them, or any result.
type Want is Data:
  WLen{n: Nat}
  WAny{}

def Len(vs: List<&2, Core.Val>, n: Nat) -> Data:
  match vs n:
    case Nil{} 0n:
      Unit
    case v <> r 1n+k:
      Len(r, k)
    case a b:
      Empty

def Fits.ok(vs: List<&2, Core.Val>, w: Want) -> Data:
  match w:
    case WLen{n}:
      Len(vs, n)
    case WAny{}:
      Unit

def Fits.no(w: Want) -> Data:
  match w:
    case WLen{n}:
      Empty
    case WAny{}:
      Unit

# Whether r is what w wants: a failure, or the values.
def Fits(r: Core.Res, w: Want) -> Data:
  match r:
    case Core.ROk{vs}:
      Fits.ok(vs, w)
    case Core.RFail{m}:
      Unit
    case Core.RNo{}:
      Fits.no(w)
    case Core.REnv{env}:
      Fits.no(w)

def Tms.len(ts: List<&2, Core.Tm>) -> Nat:
  match ts:
    case Nil{}:
      0n
    case t <> r:
      1n+Tms.len(r)

def Res.len(r: Core.Res) -> Nat:
  match r:
    case Core.ROk{vs}:
      Core.Vals.len(vs)
    case other:
      0n

def Kont.want(k: Core.Kont, r: Core.Res) -> Want:
  match k:
    case Core.KTail{env, es}:
      WLen{1n+Tms.len(es)}
    case Core.KATail{env, as}:
      WAny{}
    case Core.KCons{v}:
      WLen{1n+Res.len(r)}
    case other:
      WLen{1n}

# What a step gives: a term evaluates to one value, a list of terms to one
# value each.
def Sel.want(s: Core.Sel) -> Want:
  match s:
    case Core.SEvals{env, es}:
      WLen{Tms.len(es)}
    case Core.SArgs{env, as}:
      WAny{}
    case Core.SThen{r, k}:
      Kont.want(k, r)
    case Core.SOk{k, vs}:
      Kont.want(k, Core.ROk{vs})
    case Core.SPat{env, ps, vs}:
      WAny{}
    case Core.SPatC{hit, env, ps, vs}:
      WAny{}
    case other:
      WLen{1n}

# The laws
# ========

# If natives give one value or fail, so does a term (a step gives what
# Sel.want says).
law one_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for one: @op:String -> @vs:List<&2, Core.Val> -> Fits(prim(op, vs), WLen{1n})
  for n: Nat
  for ds: List<&2, Core.Def>
  for s: Core.Sel
  Fits(Core.run(~prim, n, ds, s), Sel.want(s))

# If a run does not run out of fuel, the reduced program, with as much fuel
# or more, gives the same result, reduced (a closure's body is a term).
law red_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.red(prim(op, vs)) == prim(op, Core.Vals.red(vs)) : Core.Res}
  for one: @op:String -> @vs:List<&2, Core.Val> -> Fits(prim(op, vs), WLen{1n})
  for n: Nat
  for m: Nat
  for le: Le(n, m)
  for ds: List<&2, Core.Def>
  for s: Core.Sel
  for nf: NotOof(Core.run(~prim, n, ds, s))
  {Core.Res.red(Core.run(~prim, n, ds, s)) == Core.run(~prim, m, Core.Defs.red(ds), Core.Sel.red(s)) : Core.Res}

# The same for a program's result.
law red_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.red(prim(op, vs)) == prim(op, Core.Vals.red(vs)) : Core.Res}
  for one: @op:String -> @vs:List<&2, Core.Val> -> Fits(prim(op, vs), WLen{1n})
  for n: Nat
  for m: Nat
  for le: Le(n, m)
  for ds: List<&2, Core.Def>
  for nf: NotOof(Core.Prog.run(~prim, n, ds))
  {Core.Res.red(Core.Prog.run(~prim, n, ds)) == Core.Prog.run(~prim, m, Core.Defs.red(ds)) : Core.Res}
