import Base
import ./RED.bend as Red
import ./core.bend as Core

# The law that core.bend's known-constructor pass (Tm.known) preserves
# `run`, in RED.bend's words. KNOWNPROOF.bend proves it.

# If a run does not run out of fuel, the resolved program, with as much fuel
# or more, gives the same result, resolved (a closure's body is a term).
law known_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.known(prim(op, vs)) == prim(op, Core.Vals.known(vs)) : Core.Res}
  for one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n})
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for ds: List<&2, Core.Def>
  for s: Core.Sel
  for nf: Red.NotOof(Core.run(~prim, n, ds, s))
  {Core.Res.known(Core.run(~prim, n, ds, s)) == Core.run(~prim, m, Core.Defs.known(ds), Core.Sel.known(s)) : Core.Res}

# The same for a program's result.
law known_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.known(prim(op, vs)) == prim(op, Core.Vals.known(vs)) : Core.Res}
  for one: @op:String -> @vs:List<&2, Core.Val> -> Red.Fits(prim(op, vs), Red.WLen{1n})
  for n: Nat
  for m: Nat
  for le: Red.Le(n, m)
  for ds: List<&2, Core.Def>
  for nf: Red.NotOof(Core.Prog.run(~prim, n, ds))
  {Core.Res.known(Core.Prog.run(~prim, n, ds)) == Core.Prog.run(~prim, m, Core.Defs.known(ds)) : Core.Res}
