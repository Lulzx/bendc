import Base
import ./core.bend as Core

law erase_ok:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.erase(prim(op, vs)) == prim(op, Core.Vals.erase(vs)) : Core.Res}
  for n: Nat
  for ds: List<&2, Core.Def>
  for s: Core.Sel
  {Core.Res.erase(Core.run(~prim, n, ds, s)) == Core.run(~prim, n, Core.Defs.erase(ds), Core.Sel.erase(s)) : Core.Res}

# A whole program: main, erased, gives its result erased.
law erase_prog:
  for ~prim: String -> List<&2, Core.Val> -> Core.Res
  for ok: @op:String -> @vs:List<&2, Core.Val> -> {Core.Res.erase(prim(op, vs)) == prim(op, Core.Vals.erase(vs)) : Core.Res}
  for n: Nat
  for ds: List<&2, Core.Def>
  {Core.Res.erase(Core.Prog.run(~prim, n, ds)) == Core.Prog.run(~prim, n, Core.Defs.erase(ds)) : Core.Res}
