import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./REDPROOF.bend as RP
import ./DEAD.bend as Dead
import ./DEADPROOF.bend as DP
import ./LIT.bend as Law

# Proof of LIT.bend's laws. L.lit (lit_ok): induction on the source's fuel,
# one case per step of `run`. The other program runs the same steps, but a
# lookup the pass knew is a literal's: the source walks the scope to the
# binding (Look.lit: the binding is the literal's, by Mirror) while the
# other program takes the literal, in as many steps or fewer. A let of a
# number is two steps apart in the two programs' knowledge (Let.k): the
# value's run (Let.run) and its binding (Let.bind).

# Equations
# =========

def Str.sym(-a: String, -b: String, e: {a == b : String}) -> {b == a : String}:
  %e : {_ == a : String}
  {==}

# A type by a Boolean: the steps that branch on one computed in the proof
# (a lookup's hit) take it with an equation (DP.Dec).
def If(b: Bool, A: Data, B: Data) -> Data:
  match b:
    case True{}:
      A
    case False{}:
      B

def If.get(-b: Bool, -A: Data, -B: Data, e: {True{} == b : Bool}, h: If(b, A, B)) -> A:
  %DP.Bool.sym(True{}, b, e) : If(_, A, B)
  h

def If.not(-b: Bool, -A: Data, -B: Data, e: {False{} == b : Bool}, h: If(b, A, B)) -> B:
  %DP.Bool.sym(False{}, b, e) : If(_, A, B)
  h

def If.put(-b: Bool, -A: Data, -B: Data, e: {True{} == b : Bool}, a: A) -> If(b, A, B):
  %e : If(_, A, B)
  a

def If.putf(-b: Bool, -A: Data, -B: Data, e: {False{} == b : Bool}, a: B) -> If(b, A, B):
  %e : If(_, A, B)
  a

def Sel.t(-h: Bool, -a: Core.Tm, -b: Core.Tm, e: {True{} == h : Bool}) -> {a == Core.Sub.sel(h, a, b) : Core.Tm}:
  %e : {a == Core.Sub.sel(_, a, b) : Core.Tm}
  {==}

def Sel.f(-h: Bool, -a: Core.Tm, -b: Core.Tm, -c: Core.Tm, e: {False{} == h : Bool}, q: {c == b : Core.Tm})
    -> {c == Core.Sub.sel(h, a, b) : Core.Tm}:
  %e : {c == Core.Sub.sel(_, a, b) : Core.Tm}
  q

def Eq.hit(-z: String, -x: String, -y: String, ezx: {z == x : String}, e: {True{} == String.eq(x, y) : Bool})
    -> {True{} == String.eq(z, y) : Bool}:
  %Str.sym(z, x, ezx) : {True{} == String.eq(_, y) : Bool}
  e

def Eq.miss(-z: String, -x: String, -y: String, ezx: {z == x : String}, e: {False{} == String.eq(x, y) : Bool})
    -> {False{} == String.eq(z, y) : Bool}:
  %Str.sym(z, x, ezx) : {False{} == String.eq(_, y) : Bool}
  e

# What the pass knew
# ==================

# The nearest binding of y in e is the literal l's.
def LookLit(e: List<&2, Core.Val>, +y: String, +l: Core.Lit) -> Data:
  match e:
    case Nil{}:
      Empty
    case b <> r:
      match b:
        case Core.VBnd{z, w}:
          If(String.eq(z, y), {w == Core.VLit{l} : Core.Val}, LookLit(r, y, l))
        case Core.VLit{l9}:
          LookLit(r, y, l)
        case Core.VCtr{k9, fs9}:
          LookLit(r, y, l)
        case Core.VClo{env9, p9, b9}:
          LookLit(r, y, l)
        case Core.VFun{f9, as9}:
          LookLit(r, y, l)
        case Core.VTrm{t9}:
          LookLit(r, y, l)

# What the pass made of a lookup of y: the lookup, or a literal the scope
# binds y to.
def Found(e1: List<&2, Core.Val>, +sg: List<&2, Core.Sub>, +y: String) -> Data:
  Either<&2, &2, {Core.CVar{y} == Core.Sub.find(sg, y) : Core.Tm},
    Sigma<&2, &2, Core.Lit, l => Sigma<&2, &2, {Core.CLit{l} == Core.Sub.find(sg, y) : Core.Tm}, _ => LookLit(e1, y, l)>>>

# Whether the first binding the pass knows is y's.
def Dec.sub(sg: List<&2, Core.Sub>, y: String) -> Data:
  match sg:
    case Nil{}:
      Unit
    case b <> r:
      match b:
        case Core.Sub{x, l}:
          DP.Dec(String.eq(x, y))
        case Core.Opq{x}:
          DP.Dec(String.eq(x, y))

def Dec.sub.of(sg: List<&2, Core.Sub>, y: String) -> Dec.sub(sg, y):
  match sg:
    case Nil{}:
      Unit{}
    case b <> r:
      match b:
        case Core.Sub{x, l}:
          DP.Dec.of(String.eq(x, y))
        case Core.Opq{x}:
          DP.Dec.of(String.eq(x, y))

# Past a binding that is not y's.
def Found.lift(-h: Bool, -hz: Bool, -a: Core.Tm, -w: Core.Val, -er: List<&2, Core.Val>, -r: List<&2, Core.Sub>, +y: String,
    eh: {False{} == h : Bool}, ez: {False{} == hz : Bool}, fo: Found(er, r, y))
    -> Either<&2, &2, {Core.CVar{y} == Core.Sub.sel(h, a, Core.Sub.find(r, y)) : Core.Tm},
      Sigma<&2, &2, Core.Lit, l2 => Sigma<&2, &2, {Core.CLit{l2} == Core.Sub.sel(h, a, Core.Sub.find(r, y)) : Core.Tm},
      _ => If(hz, {w == Core.VLit{l2} : Core.Val}, LookLit(er, y, l2))>>>:
  match fo:
    case Inl{q}:
      Inl{Sel.f(h, a, Core.Sub.find(r, y), Core.CVar{y}, eh, q)}
    case Inr{c}:
      match c:
        case (+l2, q, ll):
          Inr{(l2, Sel.f(h, a, Core.Sub.find(r, y), Core.CLit{l2}, eh, q), If.putf(hz, {w == Core.VLit{l2} : Core.Val}, LookLit(er, y, l2), ez, ll))}

# A scope the pass knew: a lookup it made a literal finds the literal.
def Find.of(sg: List<&2, Core.Sub>, e1: List<&2, Core.Val>, +y: String, d: Dec.sub(sg, y), mir: Law.Mirror(sg, e1)) -> Found(e1, sg, y):
  match sg:
    case Nil{}:
      Inl{{==}}
    case b <> +r:
      match b:
        case Core.Sub{+x, +l}:
          match e1:
            case Nil{}:
              match mir:
            case v <> +er:
              match v:
                case Core.VBnd{+z, +w}:
                  match d:
                    case Inl{+e}:
                      match mir:
                        case (ezx, ewl, mr):
                          Inr{(l, Sel.t(String.eq(x, y), Core.CLit{l}, Core.Sub.find(r, y), e),
                            If.put(String.eq(z, y), {w == Core.VLit{l} : Core.Val}, LookLit(er, y, l), Eq.hit(z, x, y, ezx, e), ewl))}
                    case Inr{+e}:
                      match mir:
                        case (+ezx, ewl, mr):
                          Found.lift(String.eq(x, y), String.eq(z, y), Core.CLit{l}, w, er, r, y, e, Eq.miss(z, x, y, ezx, e),
                            Find.of(r, er, y, Dec.sub.of(r, y), mr))
                case Core.VLit{l9}:
                  match mir:
                case Core.VCtr{k9, fs9}:
                  match mir:
                case Core.VClo{env9, p9, b9}:
                  match mir:
                case Core.VFun{f9, as9}:
                  match mir:
                case Core.VTrm{t9}:
                  match mir:
        case Core.Opq{+x}:
          match e1:
            case Nil{}:
              match mir:
            case v <> +er:
              match v:
                case Core.VBnd{+z, +w}:
                  match d:
                    case Inl{e}:
                      Inl{Sel.t(String.eq(x, y), Core.CVar{y}, Core.Sub.find(r, y), e)}
                    case Inr{+e}:
                      match mir:
                        case (ezx, mr):
                          Found.lift(String.eq(x, y), String.eq(z, y), Core.CVar{y}, w, er, r, y, e, Eq.miss(z, x, y, ezx, e),
                            Find.of(r, er, y, Dec.sub.of(r, y), mr))
                case Core.VLit{l9}:
                  match mir:
                case Core.VCtr{k9, fs9}:
                  match mir:
                case Core.VClo{env9, p9, b9}:
                  match mir:
                case Core.VFun{f9, as9}:
                  match mir:
                case Core.VTrm{t9}:
                  match mir:

# Lookups
# =======

# A lookup in related scopes: related values, in as many steps.
def Look(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +le: Red.Le(p, q), +ds: List<&2, Core.Def>,
    e1: List<&2, Core.Val>, e2: List<&2, Core.Val>, +y: String, vr: Law.VRels(e1, e2), d: DP.Dec.env(e1, y), -S: List<&2, Core.Sub>)
    -> Law.RRel(Core.run(~prim, p, ds, Core.SLook{e1, y}), S, Core.run(~prim, q, Core.Defs.lit(ds), Core.SLook{e2, y})):
  match p:
    case 0n:
      Unit{}
    case 1n+i1:
      match i1:
        case 0n:
          match e1:
            case Nil{}:
              Unit{}
            case b <> r1:
              match b:
                case Core.VLit{l9}:
                  Unit{}
                case Core.VCtr{k9, fs9}:
                  Unit{}
                case Core.VClo{env9, p9, b9}:
                  Unit{}
                case Core.VFun{f9, as9}:
                  Unit{}
                case Core.VTrm{t9}:
                  Unit{}
                case Core.VBnd{x9, w9}:
                  Unit{}
        case 1n+i2:
          match q:
            case 0n:
              match le:
            case 1n+j1:
              match j1:
                case 0n:
                  match le:
                case 1n+j2:
                  match e1:
                    case Nil{}:
                      match e2:
                        case Nil{}:
                          Unit{}
                        case w9 <> s9:
                          match vr:
                    case b <> +r1:
                      match b:
                        case Core.VLit{+l1}:
                          match e2:
                            case Nil{}:
                              match vr:
                            case b2 <> +r2:
                              match b2:
                                case Core.VLit{+l2}:
                                  match vr:
                                    case (vb, vrs):
                                      Look(~prim, 1n+i2, 1n+j2, le, ds, r1, r2, y, vrs, DP.Dec.env.of(r1, y), S)
                                case Core.VCtr{+k2, +fs2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VClo{+env2, +p2, +b2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VFun{+f2, +as2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VTrm{+t2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VBnd{+x2, +w2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                        case Core.VCtr{+k1, +fs1}:
                          match e2:
                            case Nil{}:
                              match vr:
                            case b2 <> +r2:
                              match b2:
                                case Core.VLit{+l2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VCtr{+k2, +fs2}:
                                  match vr:
                                    case (vb, vrs):
                                      Look(~prim, 1n+i2, 1n+j2, le, ds, r1, r2, y, vrs, DP.Dec.env.of(r1, y), S)
                                case Core.VClo{+env2, +p2, +b2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VFun{+f2, +as2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VTrm{+t2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VBnd{+x2, +w2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                        case Core.VClo{+env1, +p1, +b1}:
                          match e2:
                            case Nil{}:
                              match vr:
                            case b2 <> +r2:
                              match b2:
                                case Core.VLit{+l2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VCtr{+k2, +fs2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VClo{+env2, +p2, +b2}:
                                  match vr:
                                    case (vb, vrs):
                                      Look(~prim, 1n+i2, 1n+j2, le, ds, r1, r2, y, vrs, DP.Dec.env.of(r1, y), S)
                                case Core.VFun{+f2, +as2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VTrm{+t2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VBnd{+x2, +w2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                        case Core.VFun{+f1, +as1}:
                          match e2:
                            case Nil{}:
                              match vr:
                            case b2 <> +r2:
                              match b2:
                                case Core.VLit{+l2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VCtr{+k2, +fs2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VClo{+env2, +p2, +b2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VFun{+f2, +as2}:
                                  match vr:
                                    case (vb, vrs):
                                      Look(~prim, 1n+i2, 1n+j2, le, ds, r1, r2, y, vrs, DP.Dec.env.of(r1, y), S)
                                case Core.VTrm{+t2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VBnd{+x2, +w2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                        case Core.VTrm{+t1}:
                          match e2:
                            case Nil{}:
                              match vr:
                            case b2 <> +r2:
                              match b2:
                                case Core.VLit{+l2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VCtr{+k2, +fs2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VClo{+env2, +p2, +b2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VFun{+f2, +as2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VTrm{+t2}:
                                  match vr:
                                    case (vb, vrs):
                                      Look(~prim, 1n+i2, 1n+j2, le, ds, r1, r2, y, vrs, DP.Dec.env.of(r1, y), S)
                                case Core.VBnd{+x2, +w2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                        case Core.VBnd{+x1, +w1}:
                          match e2:
                            case Nil{}:
                              match vr:
                            case b2 <> +r2:
                              match b2:
                                case Core.VLit{+l2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VCtr{+k2, +fs2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VClo{+env2, +p2, +b2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VFun{+f2, +as2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VTrm{+t2}:
                                  match vr:
                                    case (vb, vrs):
                                      match vb:
                                case Core.VBnd{+x2, +w2}:
                                  match vr:
                                    case (vb, +vrs):
                                      match vb:
                                        case (ez, vw):
                                          match d:
                                            case Inl{eu}:
                                              %ez : Law.RRel(Core.run(~prim, 1n+i2, ds, Core.SLook2{String.eq(x1, y), w1, r1, y}), S, Core.run(~prim, 1n+j2, Core.Defs.lit(ds), Core.SLook2{String.eq(_, y), w2, r2, y}))
                                              %eu : Law.RRel(Core.run(~prim, 1n+i2, ds, Core.SLook2{_, w1, r1, y}), S, Core.run(~prim, 1n+j2, Core.Defs.lit(ds), Core.SLook2{_, w2, r2, y}))
                                              (vw, Unit{})
                                            case Inr{eu}:
                                              %ez : Law.RRel(Core.run(~prim, 1n+i2, ds, Core.SLook2{String.eq(x1, y), w1, r1, y}), S, Core.run(~prim, 1n+j2, Core.Defs.lit(ds), Core.SLook2{String.eq(_, y), w2, r2, y}))
                                              %eu : Law.RRel(Core.run(~prim, 1n+i2, ds, Core.SLook2{_, w1, r1, y}), S, Core.run(~prim, 1n+j2, Core.Defs.lit(ds), Core.SLook2{_, w2, r2, y}))
                                              Look(~prim, i2, j2, le, ds, r1, r2, y, vrs, DP.Dec.env.of(r1, y), S)

# A lookup the pass made a literal: the source finds the literal, and the
# other program takes it (in three steps, the fewest a lookup takes).
def Look.lit(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, e1: List<&2, Core.Val>, +y: String, +l: Core.Lit,
    ll: LookLit(e1, y, l), d: DP.Dec.env(e1, y), +q: Nat, +le: Red.Le(p, q), +e2: List<&2, Core.Val>, -S: List<&2, Core.Sub>)
    -> Law.RRel(Core.run(~prim, p, ds, Core.SLook{e1, y}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{l}})):
  match p:
    case 0n:
      Unit{}
    case 1n+p1:
      match p1:
        case 0n:
          match e1:
            case Nil{}:
              Unit{}
            case b <> r1:
              match b:
                case Core.VLit{l9}:
                  Unit{}
                case Core.VCtr{k9, fs9}:
                  Unit{}
                case Core.VClo{env9, p9, b9}:
                  Unit{}
                case Core.VFun{f9, as9}:
                  Unit{}
                case Core.VTrm{t9}:
                  Unit{}
                case Core.VBnd{x9, w9}:
                  Unit{}
        case 1n+p2:
          match e1:
            case Nil{}:
              match ll:
            case b <> +r1:
              match b:
                case Core.VBnd{+z, +w}:
                  match d:
                    case Inl{+eu}:
                      match q:
                        case 0n:
                          match le:
                        case 1n+q1:
                          match q1:
                            case 0n:
                              match le:
                            case 1n+q2:
                              %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, y}), S, Core.ROk{[Core.VLit{l}]})
                              %DP.Val.sym(w, Core.VLit{l}, If.get(String.eq(z, y), {w == Core.VLit{l} : Core.Val}, LookLit(r1, y, l), eu, ll)) : Law.RRel(Core.ROk{[_]}, S, Core.ROk{[Core.VLit{l}]})
                              ({==}, Unit{})
                    case Inr{+eu}:
                      %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, y}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{l}}))
                      Look.lit(~prim, p2, ds, r1, y, l, If.not(String.eq(z, y), {w == Core.VLit{l} : Core.Val}, LookLit(r1, y, l), eu, ll),
                        DP.Dec.env.of(r1, y), q, DP.Le.down(p2, q, DP.Le.down(1n+p2, q, le)), e2, S)
                case Core.VLit{l9}:
                  Look.lit(~prim, 1n+p2, ds, r1, y, l, ll, DP.Dec.env.of(r1, y), q, DP.Le.down(1n+p2, q, le), e2, S)
                case Core.VCtr{k9, fs9}:
                  Look.lit(~prim, 1n+p2, ds, r1, y, l, ll, DP.Dec.env.of(r1, y), q, DP.Le.down(1n+p2, q, le), e2, S)
                case Core.VClo{env9, p9, b9}:
                  Look.lit(~prim, 1n+p2, ds, r1, y, l, ll, DP.Dec.env.of(r1, y), q, DP.Le.down(1n+p2, q, le), e2, S)
                case Core.VFun{f9, as9}:
                  Look.lit(~prim, 1n+p2, ds, r1, y, l, ll, DP.Dec.env.of(r1, y), q, DP.Le.down(1n+p2, q, le), e2, S)
                case Core.VTrm{t9}:
                  Look.lit(~prim, 1n+p2, ds, r1, y, l, ll, DP.Dec.env.of(r1, y), q, DP.Le.down(1n+p2, q, le), e2, S)

# A lookup: by what the pass made of it.
def Look.var(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +le: Red.Le(p, q), +ds: List<&2, Core.Def>, +e1: List<&2, Core.Val>,
    +e2: List<&2, Core.Val>, +sg: List<&2, Core.Sub>, +y: String, vr: Law.VRels(e1, e2), -S: List<&2, Core.Sub>, fo: Found(e1, sg, y))
    -> Law.RRel(Core.run(~prim, p, ds, Core.SLook{e1, y}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, Core.Sub.find(sg, y)})):
  match fo:
    case Inl{eq}:
      %eq : Law.RRel(Core.run(~prim, p, ds, Core.SLook{e1, y}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, _}))
      Look(~prim, p, q, le, ds, e1, e2, y, vr, DP.Dec.env.of(e1, y), S)
    case Inr{c}:
      match c:
        case (+l, eq, ll):
          %eq : Law.RRel(Core.run(~prim, p, ds, Core.SLook{e1, y}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, _}))
          Look.lit(~prim, p, ds, e1, y, l, ll, DP.Dec.env.of(e1, y), q, le, e2, S)

# Lets of numbers
# ===============

# The value's run: the number, in both.
def Let.run(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +le: Red.Le(p, q), +ds: List<&2, Core.Def>, +e1: List<&2, Core.Val>,
    +e2: List<&2, Core.Val>, +l: Core.Lit)
    -> Law.Let.res(Core.run(~prim, p, ds, Core.SEval{e1, Core.CLit{l}}), l, Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{l}})):
  match p:
    case 0n:
      Unit{}
    case 1n+p1:
      match p1:
        case 0n:
          Unit{}
        case 1n+p2:
          match p2:
            case 0n:
              Unit{}
            case 1n+p3:
              match q:
                case 0n:
                  match le:
                case 1n+q1:
                  match q1:
                    case 0n:
                      match le:
                    case 1n+q2:
                      match q2:
                        case 0n:
                          match le:
                        case 1n+q3:
                          ({==}, {==})

# The binding: the scopes, with the number bound, the pass knowing it.
def Let.bind(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +q: Nat, +le: Red.Le(p, q), +ds: List<&2, Core.Def>, +e1: List<&2, Core.Val>,
    +e2: List<&2, Core.Val>, +x: String, +l: Core.Lit, -sg: List<&2, Core.Sub>, vr: Law.VRels(e1, e2), mir: Law.Mirror(sg, e1))
    -> Law.RRel(Core.run(~prim, p, ds, Core.SPat{e1, [Core.PtVar{x}], [Core.VLit{l}]}), Core.Sub{x, l} <> sg,
      Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtVar{x}], [Core.VLit{l}]})):
  match p:
    case 0n:
      Unit{}
    case 1n+p1:
      match p1:
        case 0n:
          Unit{}
        case 1n+p2:
          match q:
            case 0n:
              match le:
            case 1n+q1:
              match q1:
                case 0n:
                  match le:
                case 1n+q2:
                  ((({==}, {==}), vr), ({==}, {==}, mir))

# Shapes
# ======

# Tm.lits walks a list field as its head and the node rebuilt with the
# rest; these give the node with the field's terms taken as a whole.

def D.call(+f: String, as: List<&2, Core.Arg>, +s: List<&2, Core.Sub>)
    -> {Core.CCall{f, Core.Args.lits(as, s)} == Core.Tm.lits(Core.CCall{f, as}, s) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          match rel:
            case Core.Run{}:
              %D.call(f, r, s) : {Core.CCall{f, Core.Arg{Core.Run{}, Core.Tm.lits(e, s)} <> Core.Args.lits(r, s)} == Core.Tm.push.call(Core.Arg{Core.Run{}, Core.Tm.lits(e, s)}, _) : Core.Tm}
              {==}
            case Core.Era{}:
              %D.call(f, r, s) : {Core.CCall{f, Core.Arg{Core.Era{}, e} <> Core.Args.lits(r, s)} == Core.Tm.push.call(Core.Arg{Core.Era{}, e}, _) : Core.Tm}
              {==}

def D.app(+f: Core.Tm, as: List<&2, Core.Tm>, +s: List<&2, Core.Sub>)
    -> {Core.CApp{Core.Tm.lits(f, s), Core.Tms.lits(as, s)} == Core.Tm.lits(Core.CApp{f, as}, s) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %D.app(f, r, s) : {Core.CApp{Core.Tm.lits(f, s), Core.Tm.lits(a, s) <> Core.Tms.lits(r, s)} == Core.Tm.push(Core.Tm.lits(a, s), _) : Core.Tm}
      {==}

def D.ctr(+k: String, as: List<&2, Core.Tm>, +s: List<&2, Core.Sub>)
    -> {Core.CCtr{k, Core.Tms.lits(as, s)} == Core.Tm.lits(Core.CCtr{k, as}, s) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %D.ctr(k, r, s) : {Core.CCtr{k, Core.Tm.lits(a, s) <> Core.Tms.lits(r, s)} == Core.Tm.push(Core.Tm.lits(a, s), _) : Core.Tm}
      {==}

def D.cases(cs: List<&2, Core.Tm>, +s: List<&2, Core.Sub>)
    -> {Core.CMat{Nil{}, Core.Tms.lits(cs, s)} == Core.Tm.lits(Core.CMat{Nil{}, cs}, s) : Core.Tm}:
  match cs:
    case Nil{}:
      {==}
    case c <> r:
      %D.cases(r, s) : {Core.CMat{Nil{}, Core.Tm.lits(c, s) <> Core.Tms.lits(r, s)} == Core.Tm.push.case(Core.Tm.lits(c, s), _) : Core.Tm}
      {==}

def D.mat(scrs: List<&2, Core.Tm>, +cs: List<&2, Core.Tm>, +s: List<&2, Core.Sub>)
    -> {Core.CMat{Core.Tms.lits(scrs, s), Core.Tms.lits(cs, s)} == Core.Tm.lits(Core.CMat{scrs, cs}, s) : Core.Tm}:
  match scrs:
    case Nil{}:
      D.cases(cs, s)
    case a <> r:
      %D.mat(r, cs, s) : {Core.CMat{Core.Tm.lits(a, s) <> Core.Tms.lits(r, s), Core.Tms.lits(cs, s)} == Core.Tm.push(Core.Tm.lits(a, s), _) : Core.Tm}
      {==}

# Lists
# =====

def Len.eq(vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs, vs2))
    -> {Core.Vals.len(vs) == Core.Vals.len(vs2) : Nat}:
  match vs:
    case Nil{}:
      match vs2:
        case Nil{}:
          {==}
        case w <> s:
          match vr:
    case v <> r:
      match vs2:
        case Nil{}:
          match vr:
        case w <> s:
          match vr:
            case (a, b):
              %Len.eq(r, s, b) : {1n+Core.Vals.len(r) == 1n+_ : Nat}
              {==}

def Drop(n: Nat, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs, vs2))
    -> Law.VRels(Core.Vals.drop(n, vs), Core.Vals.drop(n, vs2)):
  match n:
    case 0n:
      vr
    case 1n+m:
      match vs:
        case Nil{}:
          match vs2:
            case Nil{}:
              Unit{}
            case w <> s:
              match vr:
        case v <> r:
          match vs2:
            case Nil{}:
              match vr:
            case w <> s:
              match vr:
                case (a, b):
                  Drop(m, r, s, b)

def Cat(as: List<&2, Core.Val>, as2: List<&2, Core.Val>, +bs: List<&2, Core.Val>, +bs2: List<&2, Core.Val>,
    ra: Law.VRels(as, as2), rb: Law.VRels(bs, bs2)) -> Law.VRels(Core.Vals.cat(as, bs), Core.Vals.cat(as2, bs2)):
  match as:
    case Nil{}:
      match as2:
        case Nil{}:
          rb
        case w <> s:
          match ra:
    case v <> r:
      match as2:
        case Nil{}:
          match ra:
        case w <> s:
          match ra:
            case (a, b):
              (a, Cat(r, s, bs, bs2, b, rb))

# A def's parameters bound to related values: related scopes.
def Bind(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs, vs2))
    -> Law.VRels(Core.Scope.bind(ps, vs), Core.Scope.bind(ps, vs2)):
  match ps:
    case Nil{}:
      Unit{}
    case q <> pr:
      match q:
        case Core.Par{x, rel, mode, ty}:
          match vs:
            case Nil{}:
              match vs2:
                case Nil{}:
                  Unit{}
                case w <> s:
                  match vr:
            case v <> r:
              match vs2:
                case Nil{}:
                  match vr:
                case w <> s:
                  match vr:
                    case (a, b):
                      (({==}, a), Bind(pr, r, s, b))

# Natives
# =======

def Prim(r1: Core.Res, r2: Core.Res, h: Law.PRel(r1, r2), -S: List<&2, Core.Sub>) -> Law.RRel(r1, S, r2):
  match r1:
    case Core.ROk{vs1}:
      match r2:
        case Core.ROk{vs2}:
          h
        case Core.REnv{e}:
          match h:
        case Core.RNo{}:
          match h:
        case Core.RFail{m}:
          match h:
    case Core.REnv{e}:
      match h:
    case Core.RNo{}:
      match h:
    case Core.RFail{m}:
      Unit{}

# Patterns
# ========

def PatC.mk(h: Bool, -S: List<&2, Core.Sub>, -e1: List<&2, Core.Val>, -ps: List<&2, Core.Pt>, -vs: List<&2, Core.Val>,
    -e2: List<&2, Core.Val>, -vs2: List<&2, Core.Val>, sg: List<&2, Core.Sub>, vr: Law.VRels(vs, vs2), venv: Law.VRels(e1, e2),
    mir: Law.Mirror(sg, e1), eb: {Core.Sub.bind(Core.Dead.names(ps), sg) == S : List<&2, Core.Sub>})
    -> Law.PatC.rel(h, S, e1, ps, vs, e2, vs2):
  match h:
    case True{}:
      (sg, vr, venv, mir, eb)
    case False{}:
      Unit{}

def Tr.bind(+qs: List<&2, Core.Pt>, +pr: List<&2, Core.Pt>, -sg: List<&2, Core.Sub>, -S: List<&2, Core.Sub>,
    eb: {Core.Sub.bind(Core.Dead.cat(Core.Dead.names(qs), Core.Dead.names(pr)), sg) == S : List<&2, Core.Sub>})
    -> {Core.Sub.bind(Core.Dead.names(Core.Pts.cat(qs, pr)), sg) == S : List<&2, Core.Sub>}:
  %DP.Names.cat(qs, pr) : {Core.Sub.bind(_, sg) == S : List<&2, Core.Sub>}
  eb

# One pattern's step against related values.
def Pat.rel(+e1: List<&2, Core.Val>, pt: Core.Pt, +v: Core.Val, +pr: List<&2, Core.Pt>, +vr: List<&2, Core.Val>,
    +e2: List<&2, Core.Val>, +v2: Core.Val, +vr2: List<&2, Core.Val>, -S: List<&2, Core.Sub>, +sg: List<&2, Core.Sub>,
    vv: Law.VRel(v, v2), +rr: Law.VRels(vr, vr2), +venv: Law.VRels(e1, e2), +mir: Law.Mirror(sg, e1),
    +eb: {Core.Sub.bind(Core.Dead.names(pt <> pr), sg) == S : List<&2, Core.Sub>})
    -> Law.SRel(Core.Pat.step(e1, pt, v, pr, vr), S, Core.Pat.step(e2, pt, v2, pr, vr2)):
  match pt:
    case Core.PtVar{+x}:
      (Core.VBnd{x, v2} <> e2, vr2, Core.Opq{x} <> sg, {==}, rr, (({==}, vv), venv), ({==}, mir), eb)
    case Core.PtCtr{+k, +qs}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              (e2, vr2, {==}, Unit{})
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
                case (ek, +vf):
                  %ek : Law.SRel(Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, S, Core.SPatC{Bool.and(String.eq(k, _), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs2))), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  %Len.eq(fs1, fs2, vf) : Law.SRel(Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, S, Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), _)), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  (e2, Core.Vals.cat(fs2, vr2), {==}, PatC.mk(Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), S, e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr), e2, Core.Vals.cat(fs2, vr2),
                    sg, Cat(fs1, fs2, vr, vr2, vf, rr), venv, mir, Tr.bind(qs, pr, sg, S, eb)))
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtNat{+n}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              %vv : Law.SRel(Core.Pat.step(e1, Core.PtNat{n}, Core.VLit{l1}, pr, vr), S, Core.Pat.step(e2, Core.PtNat{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LNat{n}, l1), S, e1, pr, vr, e2, vr2, sg, rr, venv, mir, eb))
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtNum{+n}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              %vv : Law.SRel(Core.Pat.step(e1, Core.PtNum{n}, Core.VLit{l1}, pr, vr), S, Core.Pat.step(e2, Core.PtNum{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LNum{n}, l1), S, e1, pr, vr, e2, vr2, sg, rr, venv, mir, eb))
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtFlt{+n}:
      match v:
        case Core.VLit{l1}:
          match v2:
            case Core.VLit{l2}:
              %vv : Law.SRel(Core.Pat.step(e1, Core.PtFlt{n}, Core.VLit{l1}, pr, vr), S, Core.Pat.step(e2, Core.PtFlt{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LFlt{n}, l1), S, e1, pr, vr, e2, vr2, sg, rr, venv, mir, eb))
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})
    case Core.PtSuc{+k, +q}:
      match v:
        case Core.VLit{l1}:
          match l1:
            case Core.LNum{x9}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LNum{x9}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, Unit{})
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
            case Core.LNat{+m}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LNat{m}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr2, {==}, PatC.mk(U32.is_le(k, m), S, e1, q <> pr, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr,
                    e2, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr2, sg, ({==}, rr), venv, mir, eb))
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
            case Core.LFlt{x9}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LFlt{x9}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, Unit{})
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
            case Core.LStr{x9}:
              match v2:
                case Core.VLit{l2}:
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LStr{x9}}, pr, vr), S, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, vr2, {==}, Unit{})
                case Core.VCtr{k2, fs2}:
                  match vv:
                case Core.VClo{env2, p2, b2}:
                  match vv:
                case Core.VFun{f2, as2}:
                  match vv:
                case Core.VTrm{t2}:
                  match vv:
                case Core.VBnd{x2, w2}:
                  match vv:
        case Core.VCtr{k1, fs1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              (e2, vr2, {==}, Unit{})
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VClo{env1, p1, b1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              (e2, vr2, {==}, Unit{})
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VFun{f1, as1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              (e2, vr2, {==}, Unit{})
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VTrm{t1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              (e2, vr2, {==}, Unit{})
            case Core.VBnd{x2, w2}:
              match vv:
        case Core.VBnd{x1, w1}:
          match v2:
            case Core.VLit{l2}:
              match vv:
            case Core.VCtr{k2, fs2}:
              match vv:
            case Core.VClo{env2, p2, b2}:
              match vv:
            case Core.VFun{f2, as2}:
              match vv:
            case Core.VTrm{t2}:
              match vv:
            case Core.VBnd{x2, w2}:
              (e2, vr2, {==}, Unit{})

# The induction
# =============

# From related states, related results (lit_ok): one case per step of
# `run`, the source's fuel going down; the other program's goes down with
# it, but at a lookup the pass made a literal (Look.var).
def L.lit(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(vs1, vs2) -> Law.PRel(prim(op, vs1), prim(op, vs2)),
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, s1: Core.Sel, s2: Core.Sel,
    -S: List<&2, Core.Sub>, rel: Law.SRel(s1, S, s2))
    -> Law.RRel(Core.run(~prim, n, ds, s1), S, Core.run(~prim, m, Core.Defs.lit(ds), s2)):
  match n:
    case 0n:
      Unit{}
    case 1n+p:
      match m:
        case 0n:
          match le:
        case 1n+q:
          match s1:
            case Core.SEval{+e1, t}:
              match t:
                case Core.CVar{+x0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CVar{x0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      Look.var(~prim, p, q, le, ds, e1, e2, sg, x0, vr, S, Find.of(sg, e1, x0, Dec.sub.of(sg, x0), mir))
                case Core.CCall{+f0, +as0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f0, as0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      %D.call(f0, as0, sg) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f0, as0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, _}))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, as0}), Core.KCall{f0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SArgs{e2, Core.Args.lits(as0, sg)}), Core.KCall{f0}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SArgs{e2, Core.Args.lits(as0, sg)}), Core.KCall{f0}, Nil{}, {==}, {==},
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SArgs{e1, as0}, Core.SArgs{e2, Core.Args.lits(as0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                case Core.CApp{+f0, +as0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CApp{f0, as0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      %D.app(f0, as0, sg) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CApp{f0, as0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, _}))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, f0 <> as0}), Core.KApp{}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tm.lits(f0, sg) <> Core.Tms.lits(as0, sg)}), Core.KApp{}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tm.lits(f0, sg) <> Core.Tms.lits(as0, sg)}), Core.KApp{}, Nil{}, {==}, {==},
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, f0 <> as0}, Core.SEvals{e2, Core.Tm.lits(f0, sg) <> Core.Tms.lits(as0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                case Core.CCtr{+k0, +as0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCtr{k0, as0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      %D.ctr(k0, as0, sg) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCtr{k0, as0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, _}))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, as0}), Core.KCtr{k0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tms.lits(as0, sg)}), Core.KCtr{k0}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tms.lits(as0, sg)}), Core.KCtr{k0}, Nil{}, {==}, {==},
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, as0}, Core.SEvals{e2, Core.Tms.lits(as0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                case Core.CLam{+p0, +b0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLam{p0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e1, p0, b0}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, p0, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([p0]), sg))}}}, S, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, p0, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([p0]), sg))}}, Nil{}, {==}, (Core.VClo{e2, p0, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([p0]), sg))}, {==}, ({==}, sg, {==}, vr, mir)), Unit{})})
                case Core.CLet{p0, +v0, +b0}:
                  match p0:
                    case Core.PtVar{+x9}:
                      match v0:
                        case Core.CVar{+x7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CVar{x7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CVar{x7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CVar{x7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CVar{x7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CVar{x7}}, Core.SEval{e2, Core.Tm.lits(Core.CVar{x7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CCall{+f7, +as7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CCall{f7, as7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CCall{f7, as7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CCall{f7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CCall{f7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CCall{f7, as7}}, Core.SEval{e2, Core.Tm.lits(Core.CCall{f7, as7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CApp{+f7, +as7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CApp{f7, as7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CApp{f7, as7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CApp{f7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CApp{f7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CApp{f7, as7}}, Core.SEval{e2, Core.Tm.lits(Core.CApp{f7, as7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CCtr{+k7, +as7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CCtr{k7, as7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CCtr{k7, as7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CCtr{k7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CCtr{k7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CCtr{k7, as7}}, Core.SEval{e2, Core.Tm.lits(Core.CCtr{k7, as7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CLam{+p7, +b7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CLam{p7, b7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CLam{p7, b7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CLam{p7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CLam{p7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CLam{p7, b7}}, Core.SEval{e2, Core.Tm.lits(Core.CLam{p7, b7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CLet{+p7, +v7, +b7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CLet{p7, v7, b7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CLet{p7, v7, b7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CLet{p7, v7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CLet{p7, v7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CLet{p7, v7, b7}}, Core.SEval{e2, Core.Tm.lits(Core.CLet{p7, v7, b7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CMat{+scrs7, +cases7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CMat{scrs7, cases7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CMat{scrs7, cases7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CMat{scrs7, cases7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CMat{scrs7, cases7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CMat{scrs7, cases7}}, Core.SEval{e2, Core.Tm.lits(Core.CMat{scrs7, cases7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CCse{+ps7, +b7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CCse{ps7, b7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CCse{ps7, b7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CCse{ps7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CCse{ps7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CCse{ps7, b7}}, Core.SEval{e2, Core.Tm.lits(Core.CCse{ps7, b7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CSuc{+k7, +e7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CSuc{k7, e7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CSuc{k7, e7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CSuc{k7, e7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CSuc{k7, e7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CSuc{k7, e7}}, Core.SEval{e2, Core.Tm.lits(Core.CSuc{k7, e7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.COp{+op7, +a7, +b7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.COp{op7, a7, b7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.COp{op7, a7, b7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.COp{op7, a7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.COp{op7, a7, b7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.COp{op7, a7, b7}}, Core.SEval{e2, Core.Tm.lits(Core.COp{op7, a7, b7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CAnn{+e7, +ty7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CAnn{e7, ty7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CAnn{e7, ty7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CAnn{e7, ty7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CAnn{e7, ty7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CAnn{e7, ty7}}, Core.SEval{e2, Core.Tm.lits(Core.CAnn{e7, ty7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CLit{l8}:
                          match l8:
                            case Core.LNum{+n8}:
                              match rel:
                                case (+e2, +sg, eq, +vr, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CLit{Core.LNum{n8}}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CLit{Core.LNum{n8}}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{Core.LNum{n8}}}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Sub{x9, Core.LNum{n8}} <> sg)}}, S, Inr{(Core.LNum{n8}, Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{Core.LNum{n8}}}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Sub{x9, Core.LNum{n8}} <> sg)}, {==}, (e2, sg, {==}, vr, mir), Let.run(~prim, p, q, le, ds, e1, e2, Core.LNum{n8}))})
                            case Core.LNat{+n8}:
                              match rel:
                                case (+e2, +sg, eq, +vr, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CLit{Core.LNat{n8}}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CLit{Core.LNat{n8}}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{Core.LNat{n8}}}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Sub{x9, Core.LNat{n8}} <> sg)}}, S, Inr{(Core.LNat{n8}, Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{Core.LNat{n8}}}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Sub{x9, Core.LNat{n8}} <> sg)}, {==}, (e2, sg, {==}, vr, mir), Let.run(~prim, p, q, le, ds, e1, e2, Core.LNat{n8}))})
                            case Core.LFlt{+n8}:
                              match rel:
                                case (+e2, +sg, eq, +vr, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CLit{Core.LFlt{n8}}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CLit{Core.LFlt{n8}}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{Core.LFlt{n8}}}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Sub{x9, Core.LFlt{n8}} <> sg)}}, S, Inr{(Core.LFlt{n8}, Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.CLit{Core.LFlt{n8}}}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Sub{x9, Core.LFlt{n8}} <> sg)}, {==}, (e2, sg, {==}, vr, mir), Let.run(~prim, p, q, le, ds, e1, e2, Core.LFlt{n8}))})
                            case Core.LStr{+z8}:
                              match rel:
                                case (+e2, +sg, eq, +vr, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CLit{Core.LStr{z8}}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CLit{Core.LStr{z8}}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CLit{Core.LStr{z8}}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CLit{Core.LStr{z8}}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CLit{Core.LStr{z8}}}, Core.SEval{e2, Core.Tm.lits(Core.CLit{Core.LStr{z8}}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CRef{+f7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CRef{f7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CRef{f7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CRef{f7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CRef{f7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CRef{f7}}, Core.SEval{e2, Core.Tm.lits(Core.CRef{f7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CTyp{+n7, +as7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CTyp{n7, as7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CTyp{n7, as7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CTyp{n7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CTyp{n7, as7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CTyp{n7, as7}}, Core.SEval{e2, Core.Tm.lits(Core.CTyp{n7, as7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CBox{}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CBox{}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CBox{}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CBox{}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CBox{}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CBox{}}, Core.SEval{e2, Core.Tm.lits(Core.CBox{}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.CErr{+m7}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, Core.CErr{m7}, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CErr{m7}}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CErr{m7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(Core.CErr{m7}, sg)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.lits(b0, Core.Opq{x9} <> sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CErr{m7}}, Core.SEval{e2, Core.Tm.lits(Core.CErr{m7}, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                    case Core.PtCtr{+k9, +qs9}:
                      match rel:
                        case (+e2, +sg, eq, +vr, +mir):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtCtr{k9, qs9}, v0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtCtr{k9, qs9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtCtr{k9, qs9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtCtr{k9, qs9}]), sg))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtCtr{k9, qs9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtCtr{k9, qs9}]), sg))}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                            L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Core.SEval{e2, Core.Tm.lits(v0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                    case Core.PtNat{+n9}:
                      match rel:
                        case (+e2, +sg, eq, +vr, +mir):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtNat{n9}, v0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtNat{n9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtNat{n9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtNat{n9}]), sg))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtNat{n9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtNat{n9}]), sg))}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                            L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Core.SEval{e2, Core.Tm.lits(v0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                    case Core.PtSuc{+k9, +q9}:
                      match rel:
                        case (+e2, +sg, eq, +vr, +mir):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtSuc{k9, q9}, v0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtSuc{k9, q9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtSuc{k9, q9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtSuc{k9, q9}]), sg))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtSuc{k9, q9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtSuc{k9, q9}]), sg))}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                            L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Core.SEval{e2, Core.Tm.lits(v0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                    case Core.PtNum{+n9}:
                      match rel:
                        case (+e2, +sg, eq, +vr, +mir):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtNum{n9}, v0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtNum{n9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtNum{n9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtNum{n9}]), sg))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtNum{n9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtNum{n9}]), sg))}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                            L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Core.SEval{e2, Core.Tm.lits(v0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                    case Core.PtFlt{+s9}:
                      match rel:
                        case (+e2, +sg, eq, +vr, +mir):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtFlt{s9}, v0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtFlt{s9}, b0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtFlt{s9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtFlt{s9}]), sg))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(v0, sg)}), Core.KLet{e2, Core.PtFlt{s9}, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names([Core.PtFlt{s9}]), sg))}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                            L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Core.SEval{e2, Core.Tm.lits(v0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                case Core.CMat{+scrs0, +cases0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CMat{scrs0, cases0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      %D.mat(scrs0, cases0, sg) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CMat{scrs0, cases0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SEval{e2, _}))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, scrs0}), Core.KMat{e1, cases0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tms.lits(scrs0, sg)}), Core.KMat{e2, Core.Tms.lits(cases0, sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tms.lits(scrs0, sg)}), Core.KMat{e2, Core.Tms.lits(cases0, sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, scrs0}, Core.SEvals{e2, Core.Tms.lits(scrs0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                case Core.CCse{+ps0, +b0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCse{ps0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, S, Inl{(Core.RFail{"a case outside a match"}, Core.KApp{}, Nil{}, {==}, {==}, Unit{})})
                case Core.CSuc{+k0, +e0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CSuc{k0, e0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e0}), Core.KSuc{k0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(e0, sg)}), Core.KSuc{k0}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(e0, sg)}), Core.KSuc{k0}, Nil{}, {==}, {==},
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e0}, Core.SEval{e2, Core.Tm.lits(e0, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                case Core.COp{+op0, +a0, +b0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.COp{op0, a0, b0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, [a0, b0]}), Core.KOp{op0}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, [Core.Tm.lits(a0, sg), Core.Tm.lits(b0, sg)]}), Core.KOp{op0}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, [Core.Tm.lits(a0, sg), Core.Tm.lits(b0, sg)]}), Core.KOp{op0}, Nil{}, {==}, {==},
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, [a0, b0]}, Core.SEvals{e2, [Core.Tm.lits(a0, sg), Core.Tm.lits(b0, sg)]}, Nil{}, (e2, sg, {==}, vr, mir)))})
                case Core.CAnn{+e0, +ty0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CAnn{e0, ty0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e0}, Core.SEval{e2, Core.Tm.lits(e0, sg)}, S, (e2, sg, {==}, vr, mir))
                case Core.CLit{+l0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLit{l0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l0}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l0}}}, S, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VLit{l0}}, Nil{}, {==}, (Core.VLit{l0}, {==}, {==}), Unit{})})
                case Core.CRef{+f0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CRef{f0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SCallDef{f0, Nil{}}, Core.SCallDef{f0, Nil{}}, S, (Nil{}, {==}, Unit{}))
                case Core.CTyp{+n0, +as0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CTyp{n0, as0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, S, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, Nil{}, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})})
                case Core.CBox{}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CBox{}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, S, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, Nil{}, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})})
                case Core.CErr{+m0}:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CErr{m0}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.RFail{m0}, Core.KApp{}}, Core.SThen{Core.RFail{m0}, Core.KApp{}}, S, Inl{(Core.RFail{m0}, Core.KApp{}, Nil{}, {==}, {==}, Unit{})})
            case Core.SEvals{+e1, es}:
              match es:
                case Nil{}:
                  match rel:
                    case (e2, sg, eq, vr, mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEvals{e1, Nil{}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      Unit{}
                case +e <> +r:
                  match rel:
                    case (+e2, +sg, eq, +vr, +mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEvals{e1, e <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KTail{e1, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(e, sg)}), Core.KTail{e2, Core.Tms.lits(r, sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(e, sg)}), Core.KTail{e2, Core.Tms.lits(r, sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.lits(e, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
            case Core.SArgs{+e1, as}:
              match as:
                case Nil{}:
                  match rel:
                    case (e2, sg, eq, vr, mir):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Nil{}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      Unit{}
                case a <> +r:
                  match a:
                    case Core.Arg{rl, +e}:
                      match rl:
                        case Core.Run{}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Core.Arg{Core.Run{}, e} <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KATail{e1, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(e, sg)}), Core.KATail{e2, Core.Args.lits(r, sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{e2, Core.Tm.lits(e, sg)}), Core.KATail{e2, Core.Args.lits(r, sg)}, Nil{}, {==}, (e2, sg, {==}, vr, mir),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e}, Core.SEval{e2, Core.Tm.lits(e, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
                        case Core.Era{}:
                          match rel:
                            case (+e2, +sg, eq, +vr, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Core.Arg{Core.Era{}, e} <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, r}), Core.KCons{Core.VTrm{e}}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SArgs{e2, Core.Args.lits(r, sg)}), Core.KCons{Core.VTrm{e}}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SArgs{e2, Core.Args.lits(r, sg)}), Core.KCons{Core.VTrm{e}}, Nil{}, {==}, (Core.VTrm{e}, {==}, {==}),
                                L.lit(~prim, ~ok, p, q, le, ds, Core.SArgs{e1, r}, Core.SArgs{e2, Core.Args.lits(r, sg)}, Nil{}, (e2, sg, {==}, vr, mir)))})
            case Core.SThen{+r1, +k1}:
              match r1:
                case Core.ROk{+ov1}:
                  match k1:
                    case Core.KCall{+f1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCall{f1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCall{f1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KApp{}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KApp{}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KApp{}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KCtr{+k1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCtr{k1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCtr{k1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KLet{+env1, p1, +b1}:
                      match p1:
                        case Core.PtVar{+x}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, +sgk, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtVar{x}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                                case (+l, r2, k2, eq, lk, lr):
                                  match lk:
                                    case (+e2, +sg, eqk, +vr, +mir):
                                      match lr:
                                        case (ev, er):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtVar{x}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          %er : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtVar{x}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SThen{_, k2}))
                                          %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtVar{x}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SThen{Core.ROk{[Core.VLit{l}]}, _}))
                                          %ev : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{_}, Core.KLet{env1, Core.PtVar{x}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SThen{Core.ROk{[Core.VLit{l}]}, Core.KLet{e2, Core.PtVar{x}, Core.Tm.lits(b1, Core.Sub{x, l} <> sg)}}))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, [Core.VLit{l}]}, Core.SOk{Core.KLet{e2, Core.PtVar{x}, Core.Tm.lits(b1, Core.Sub{x, l} <> sg)}, [Core.VLit{l}]}, S, Inr{(l, Core.KLet{e2, Core.PtVar{x}, Core.Tm.lits(b1, Core.Sub{x, l} <> sg)}, {==}, (e2, sg, {==}, vr, mir), {==})})
                        case Core.PtCtr{+k9, +qs9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, +sgk, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                                case (l, r2, k2, eq, lk, lr):
                                  match lk:
                        case Core.PtNat{+n9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, +sgk, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtNat{n9}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtNat{n9}, b1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                                case (l, r2, k2, eq, lk, lr):
                                  match lk:
                        case Core.PtSuc{+k9, +q9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, +sgk, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtSuc{k9, q9}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtSuc{k9, q9}, b1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                                case (l, r2, k2, eq, lk, lr):
                                  match lk:
                        case Core.PtNum{+n9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, +sgk, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtNum{n9}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtNum{n9}, b1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                                case (l, r2, k2, eq, lk, lr):
                                  match lk:
                        case Core.PtFlt{+s9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, +sgk, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtFlt{s9}, b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtFlt{s9}, b1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, sgk, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                                case (l, r2, k2, eq, lk, lr):
                                  match lk:
                    case Core.KBind{+b1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KBind{b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KBind{b1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KMat{+env1, +cases1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KMat{env1, cases1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KMat{env1, cases1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KCase{+env1, +vs1, +b1, +rest1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCase{env1, vs1, b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCase{env1, vs1, b1, rest1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KSuc{+k1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KSuc{k1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KSuc{k1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KOp{+op1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KOp{op1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KOp{op1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KTail{+env1, +es1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KTail{env1, es1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KTail{env1, es1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KATail{+env1, +as1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KATail{env1, as1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KATail{env1, as1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KCons{+v1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCons{v1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCons{v1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KApply{+vs1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KApply{vs1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KApply{vs1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                    case Core.KBody{+b1, +rest1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KBody{b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                      L.lit(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KBody{b1, rest1}, ov1}, Core.SOk{k2, vs2}, S, Inl{(k2, vs2, sgk, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lk:
                case Core.REnv{+oe1}:
                  match k1:
                    case Core.KCall{+f1}:
                      Unit{}
                    case Core.KApp{}:
                      Unit{}
                    case Core.KCtr{+k1}:
                      Unit{}
                    case Core.KLet{+env1, +p1, +b1}:
                      Unit{}
                    case Core.KBind{+b1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{vs2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.REnv{+env2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      match rr:
                                        case (+venv, +mir):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBind{b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBind{b1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SThen{Core.REnv{env2}, _}))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{oe1, b1}, Core.SEval{env2, Core.Tm.lits(b1, sgk)}, S, (env2, sgk, {==}, venv, mir))
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lr:
                    case Core.KMat{+env1, +cases1}:
                      Unit{}
                    case Core.KCase{+env1, +vs1, +b1, +rest1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{vs2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.REnv{+env2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      match kr:
                                        case (e2, kvs2, sg0, eqk, vrs, venv0, mir0):
                                          match rr:
                                            case (+venv, +mir):
                                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KCase{env1, vs1, b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                              %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KCase{env1, vs1, b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SThen{Core.REnv{env2}, _}))
                                              L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{oe1, b1}, Core.SEval{env2, Core.Tm.lits(b1, sgk)}, S, (env2, sgk, {==}, venv, mir))
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lr:
                    case Core.KSuc{+k1}:
                      Unit{}
                    case Core.KOp{+op1}:
                      Unit{}
                    case Core.KTail{+env1, +es1}:
                      Unit{}
                    case Core.KATail{+env1, +as1}:
                      Unit{}
                    case Core.KCons{+v1}:
                      Unit{}
                    case Core.KApply{+vs1}:
                      Unit{}
                    case Core.KBody{+b1, +rest1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{vs2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.REnv{+env2}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      match kr:
                                        case (+rr2, eqk, +vrs):
                                          match rr:
                                            case (+venv, +mir):
                                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBody{b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                              %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBody{b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SThen{Core.REnv{env2}, _}))
                                              L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{oe1, b1}), Core.KApply{rest1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{env2, Core.Tm.lits(b1, sgk)}), Core.KApply{rr2}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{env2, Core.Tm.lits(b1, sgk)}), Core.KApply{rr2}, Nil{}, {==}, (rr2, {==}, vrs),
                                                L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{oe1, b1}, Core.SEval{env2, Core.Tm.lits(b1, sgk)}, Nil{}, (env2, sgk, {==}, venv, mir)))})
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lr:
                case Core.RNo{}:
                  match k1:
                    case Core.KCall{+f1}:
                      Unit{}
                    case Core.KApp{}:
                      Unit{}
                    case Core.KCtr{+k1}:
                      Unit{}
                    case Core.KLet{+env1, +p1, +b1}:
                      Unit{}
                    case Core.KBind{+b1}:
                      Unit{}
                    case Core.KMat{+env1, +cases1}:
                      Unit{}
                    case Core.KCase{+env1, +vs1, +b1, +rest1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{vs2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (+k2, +sgk, eq, kr, rr):
                                      match kr:
                                        case (+e2, +kvs2, +sg0, eqk, +vrs, +venv, +mir):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.RNo{}, Core.KCase{env1, vs1, b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.RNo{}, Core.KCase{env1, vs1, b1, rest1}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SThen{Core.RNo{}, _}))
                                          L.lit(~prim, ~ok, p, q, le, ds, Core.SMatch{env1, vs1, rest1}, Core.SMatch{e2, kvs2, Core.Tms.lits(rest1, sg0)}, S, (e2, kvs2, sg0, {==}, vrs, venv, mir))
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, sgk, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (l, r2, k2, eq, lk, lr):
                              match lr:
                    case Core.KSuc{+k1}:
                      Unit{}
                    case Core.KOp{+op1}:
                      Unit{}
                    case Core.KTail{+env1, +es1}:
                      Unit{}
                    case Core.KATail{+env1, +as1}:
                      Unit{}
                    case Core.KCons{+v1}:
                      Unit{}
                    case Core.KApply{+vs1}:
                      Unit{}
                    case Core.KBody{+b1, +rest1}:
                      Unit{}
                case Core.RFail{+msg}:
                  Unit{}
            case Core.SOk{+k1, +vs}:
              match k1:
                case Core.KCall{+f1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, +sgk, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SCallDef{f1, vs}, Core.SCallDef{f1, vs2}, S, (vs2, {==}, vr))
                    case Inr{st}:
                      match st:
                        case (l, k2, eq, lk, ev):
                          match lk:
                case Core.KApp{}:
                  match vs:
                    case Nil{}:
                      Unit{}
                    case +v <> +r:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, tla):
                              match tla:
                                case (vs2, tlb):
                                  match vs2:
                                    case Nil{}:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match vr:
                                            case (vv, vrest):
                                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApp{}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                              %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApp{}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, v2 <> r2}))
                                              L.lit(~prim, ~ok, p, q, le, ds, Core.SApply{r, v}, Core.SApply{r2, v2}, S, (r2, v2, {==}, vrest, vv))
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                case Core.KCtr{+k1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, +sgk, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCtr{k1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCtr{k1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                          (({==}, vr), Unit{})
                    case Inr{st}:
                      match st:
                        case (l, k2, eq, lk, ev):
                          match lk:
                case Core.KLet{+env1, p1, +b1}:
                  match p1:
                    case Core.PtVar{+x}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, +sgk, eq, kr, +vr):
                              match kr:
                                case (+e2, +sg0, eqk, +venv, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtVar{x}], vs}), Core.KBind{b1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtVar{x}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtVar{x}]), sg0))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtVar{x}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtVar{x}]), sg0))}, Core.Sub.bind(Core.Dead.names([Core.PtVar{x}]), sg0), {==}, {==},
                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtVar{x}], vs}, Core.SPat{e2, [Core.PtVar{x}], vs2}, Core.Sub.bind(Core.Dead.names([Core.PtVar{x}]), sg0), (e2, vs2, sg0, {==}, vr, venv, mir, {==})))})
                        case Inr{st}:
                          match st:
                            case (+l, k2, eq, lk, ev):
                              match lk:
                                case (+e2, +sg, eqk, +vr, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, [Core.VLit{l}]}))
                                  %ev : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, _}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{Core.KLet{e2, Core.PtVar{x}, Core.Tm.lits(b1, Core.Sub{x, l} <> sg)}, [Core.VLit{l}]}))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtVar{x}], [Core.VLit{l}]}), Core.KBind{b1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtVar{x}], [Core.VLit{l}]}), Core.KBind{Core.Tm.lits(b1, Core.Sub{x, l} <> sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtVar{x}], [Core.VLit{l}]}), Core.KBind{Core.Tm.lits(b1, Core.Sub{x, l} <> sg)}, Core.Sub{x, l} <> sg, {==}, {==},
                                    Let.bind(~prim, p, q, le, ds, env1, e2, x, l, sg, vr, mir))})
                    case Core.PtCtr{+k9, +qs9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, +sgk, eq, kr, +vr):
                              match kr:
                                case (+e2, +sg0, eqk, +venv, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtCtr{k9, qs9}], vs}), Core.KBind{b1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtCtr{k9, qs9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtCtr{k9, qs9}]), sg0))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtCtr{k9, qs9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtCtr{k9, qs9}]), sg0))}, Core.Sub.bind(Core.Dead.names([Core.PtCtr{k9, qs9}]), sg0), {==}, {==},
                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtCtr{k9, qs9}], vs}, Core.SPat{e2, [Core.PtCtr{k9, qs9}], vs2}, Core.Sub.bind(Core.Dead.names([Core.PtCtr{k9, qs9}]), sg0), (e2, vs2, sg0, {==}, vr, venv, mir, {==})))})
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                    case Core.PtNat{+n9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, +sgk, eq, kr, +vr):
                              match kr:
                                case (+e2, +sg0, eqk, +venv, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNat{n9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNat{n9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtNat{n9}], vs}), Core.KBind{b1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtNat{n9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtNat{n9}]), sg0))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtNat{n9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtNat{n9}]), sg0))}, Core.Sub.bind(Core.Dead.names([Core.PtNat{n9}]), sg0), {==}, {==},
                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtNat{n9}], vs}, Core.SPat{e2, [Core.PtNat{n9}], vs2}, Core.Sub.bind(Core.Dead.names([Core.PtNat{n9}]), sg0), (e2, vs2, sg0, {==}, vr, venv, mir, {==})))})
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                    case Core.PtSuc{+k9, +q9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, +sgk, eq, kr, +vr):
                              match kr:
                                case (+e2, +sg0, eqk, +venv, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtSuc{k9, q9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtSuc{k9, q9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtSuc{k9, q9}], vs}), Core.KBind{b1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtSuc{k9, q9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtSuc{k9, q9}]), sg0))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtSuc{k9, q9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtSuc{k9, q9}]), sg0))}, Core.Sub.bind(Core.Dead.names([Core.PtSuc{k9, q9}]), sg0), {==}, {==},
                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtSuc{k9, q9}], vs}, Core.SPat{e2, [Core.PtSuc{k9, q9}], vs2}, Core.Sub.bind(Core.Dead.names([Core.PtSuc{k9, q9}]), sg0), (e2, vs2, sg0, {==}, vr, venv, mir, {==})))})
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                    case Core.PtNum{+n9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, +sgk, eq, kr, +vr):
                              match kr:
                                case (+e2, +sg0, eqk, +venv, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNum{n9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNum{n9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtNum{n9}], vs}), Core.KBind{b1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtNum{n9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtNum{n9}]), sg0))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtNum{n9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtNum{n9}]), sg0))}, Core.Sub.bind(Core.Dead.names([Core.PtNum{n9}]), sg0), {==}, {==},
                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtNum{n9}], vs}, Core.SPat{e2, [Core.PtNum{n9}], vs2}, Core.Sub.bind(Core.Dead.names([Core.PtNum{n9}]), sg0), (e2, vs2, sg0, {==}, vr, venv, mir, {==})))})
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                    case Core.PtFlt{+s9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, +sgk, eq, kr, +vr):
                              match kr:
                                case (+e2, +sg0, eqk, +venv, +mir):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtFlt{s9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtFlt{s9}, b1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtFlt{s9}], vs}), Core.KBind{b1}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtFlt{s9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtFlt{s9}]), sg0))}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, [Core.PtFlt{s9}], vs2}), Core.KBind{Core.Tm.lits(b1, Core.Sub.bind(Core.Dead.names([Core.PtFlt{s9}]), sg0))}, Core.Sub.bind(Core.Dead.names([Core.PtFlt{s9}]), sg0), {==}, {==},
                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtFlt{s9}], vs}, Core.SPat{e2, [Core.PtFlt{s9}], vs2}, Core.Sub.bind(Core.Dead.names([Core.PtFlt{s9}]), sg0), (e2, vs2, sg0, {==}, vr, venv, mir, {==})))})
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                case Core.KBind{+b1}:
                  Unit{}
                case Core.KMat{+env1, +cases1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, +sgk, eq, kr, +vr):
                          match kr:
                            case (+e2, +sg0, eqk, +venv, +mir):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KMat{env1, cases1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KMat{env1, cases1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                              L.lit(~prim, ~ok, p, q, le, ds, Core.SMatch{env1, vs, cases1}, Core.SMatch{e2, vs2, Core.Tms.lits(cases1, sg0)}, S, (e2, vs2, sg0, {==}, vr, venv, mir))
                    case Inr{st}:
                      match st:
                        case (l, k2, eq, lk, ev):
                          match lk:
                case Core.KCase{+env1, +vs1, +b1, +rest1}:
                  Unit{}
                case Core.KSuc{+k1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, +sgk, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KSuc{k1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KSuc{k1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                          Prim(prim("%suc", Core.VLit{Core.LNum{k1}} <> vs), prim("%suc", Core.VLit{Core.LNum{k1}} <> vs2), ok("%suc", Core.VLit{Core.LNum{k1}} <> vs, Core.VLit{Core.LNum{k1}} <> vs2, ({==}, vr)), S)
                    case Inr{st}:
                      match st:
                        case (l, k2, eq, lk, ev):
                          match lk:
                case Core.KOp{+op1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, +sgk, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KOp{op1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KOp{op1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                          Prim(prim(op1, vs), prim(op1, vs2), ok(op1, vs, vs2, vr), S)
                    case Inr{st}:
                      match st:
                        case (l, k2, eq, lk, ev):
                          match lk:
                case Core.KTail{+env1, +es1}:
                  match vs:
                    case Nil{}:
                      Unit{}
                    case +v <> +r:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, tla):
                              match tla:
                                case (vs2, tlb):
                                  match vs2:
                                    case Nil{}:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match kr:
                                            case (+e2, +sg0, eqk, +venv, +mir):
                                              match vr:
                                                case (vv, vrest):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KTail{env1, es1}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KTail{env1, es1}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, v2 <> r2}))
                                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env1, es1}), Core.KCons{v}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tms.lits(es1, sg0)}), Core.KCons{v2}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEvals{e2, Core.Tms.lits(es1, sg0)}), Core.KCons{v2}, Nil{}, {==}, (v2, {==}, vv),
                                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SEvals{env1, es1}, Core.SEvals{e2, Core.Tms.lits(es1, sg0)}, Nil{}, (e2, sg0, {==}, venv, mir)))})
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                case Core.KATail{+env1, +as1}:
                  match vs:
                    case Nil{}:
                      Unit{}
                    case +v <> +r:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, tla):
                              match tla:
                                case (vs2, tlb):
                                  match vs2:
                                    case Nil{}:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match kr:
                                            case (+e2, +sg0, eqk, +venv, +mir):
                                              match vr:
                                                case (vv, vrest):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KATail{env1, as1}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KATail{env1, as1}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, v2 <> r2}))
                                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env1, as1}), Core.KCons{v}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SArgs{e2, Core.Args.lits(as1, sg0)}), Core.KCons{v2}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SArgs{e2, Core.Args.lits(as1, sg0)}), Core.KCons{v2}, Nil{}, {==}, (v2, {==}, vv),
                                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SArgs{env1, as1}, Core.SArgs{e2, Core.Args.lits(as1, sg0)}, Nil{}, (e2, sg0, {==}, venv, mir)))})
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                case Core.KCons{+v1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, +sgk, eq, kr, +vr):
                          match kr:
                            case (+v2, eqk, vv):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCons{v1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCons{v1}, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, vs2}))
                              (vv, vr)
                    case Inr{st}:
                      match st:
                        case (l, k2, eq, lk, ev):
                          match lk:
                case Core.KApply{+vs1}:
                  match vs:
                    case Nil{}:
                      Unit{}
                    case +v <> +r:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, tla):
                              match tla:
                                case (vs2, tlb):
                                  match vs2:
                                    case Nil{}:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (sgk, eq, kr, vr):
                                          match kr:
                                            case (+kvs2, eqk, vrs):
                                              match vr:
                                                case (vv, vrest):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApply{vs1}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApply{vs1}, v <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SOk{_, v2 <> r2}))
                                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SApply{vs1, v}, Core.SApply{kvs2, v2}, S, (kvs2, v2, {==}, vrs, vv))
                        case Inr{st}:
                          match st:
                            case (l, k2, eq, lk, ev):
                              match lk:
                case Core.KBody{+b1, +rest1}:
                  Unit{}
            case Core.SLook{+e1, +x}:
              match rel:
                case (+e2, eq, +vr):
                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SLook{e1, x}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                  Look(~prim, 1n+p, 1n+q, le, ds, e1, e2, x, vr, DP.Dec.env.of(e1, x), S)
            case Core.SLook2{hit, +v, +e1, +x}:
              match hit:
                case True{}:
                  match rel:
                    case (v2, e2, eq, vv, venv):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SLook2{True{}, v, e1, x}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      (vv, Unit{})
                case False{}:
                  match rel:
                    case (v2, +e2, eq, vv, venv):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SLook2{False{}, v, e1, x}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SLook{e1, x}, Core.SLook{e2, x}, S, (e2, {==}, venv))
            case Core.SCallDef{+f, +vs}:
              match rel:
                case (+vs2, eq, vr):
                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SCallDef{f, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                  L.lit(~prim, ~ok, p, q, le, ds, Core.SFind{ds, f, vs}, Core.SFind{Core.Defs.lit(ds), f, vs2}, S, (vs2, {==}, vr))
            case Core.SFind{ds2, +f, +vs}:
              match ds2:
                case Nil{}:
                  match rel:
                    case (+vs2, eq, vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFind{Nil{}, f, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      Prim(prim(f, vs), prim(f, vs2), ok(f, vs, vs2, vr), S)
                case df <> +dr:
                  match df:
                    case Core.Def{+name, +ps, +b, ret}:
                      match rel:
                        case (+vs2, eq, vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFind{Core.Def{name, ps, b, ret} <> dr, f, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SFound{String.eq(name, f), ps, b, dr, f, vs}, Core.SFound{String.eq(name, f), ps, Core.Tm.lit(b), Core.Defs.lit(dr), f, vs2}, S, (vs2, {==}, vr))
            case Core.SFound{hit, +ps, +b, +ds2, +f, +vs}:
              match hit:
                case True{}:
                  match rel:
                    case (+vs2, eq, +vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, b, ds2, f, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      %Len.eq(vs, vs2, vr) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, b, ds2, f, vs}), S, Core.run(~prim, q, Core.Defs.lit(ds), Core.SEnter{Nat.is_lt(_, Core.Pars.len(ps)), f, ps, Core.Tm.lit(b), vs2}))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, b, vs}, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, Core.Tm.lit(b), vs2}, S, (vs2, {==}, vr))
                case False{}:
                  match rel:
                    case (+vs2, eq, vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFound{False{}, ps, b, ds2, f, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SFind{ds2, f, vs}, Core.SFind{Core.Defs.lit(ds2), f, vs2}, S, (vs2, {==}, vr))
            case Core.SEnter{short, +f, +ps, +b, +vs}:
              match short:
                case True{}:
                  match rel:
                    case (vs2, eq, vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEnter{True{}, f, ps, b, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      (({==}, vr), Unit{})
                case False{}:
                  match rel:
                    case (+vs2, eq, +vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, b, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), b}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.lit(b)}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs2)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.lit(b)}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs2)}, Nil{}, {==}, (Core.Vals.drop(Core.Pars.len(ps), vs2), {==}, Drop(Core.Pars.len(ps), vs, vs2, vr)),
                        L.lit(~prim, ~ok, p, q, le, ds, Core.SEval{Core.Scope.bind(ps, vs), b}, Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.lit(b)}, Nil{}, (Core.Scope.bind(ps, vs2), Nil{}, {==}, Bind(ps, vs, vs2, vr), Unit{})))})
            case Core.SApply{vs, +fv}:
              match vs:
                case Nil{}:
                  match rel:
                    case (vs2, tla):
                      match vs2:
                        case Nil{}:
                          match tla:
                            case (fv2, eq, vr, fr):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{Nil{}, fv}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                              (fr, Unit{})
                        case w <> s:
                          match tla:
                            case (fv2, tlb):
                              match tlb:
                                case (eq, vr, fr):
                                  match vr:
                case +v <> +r:
                  match fv:
                    case Core.VLit{l9}:
                      Unit{}
                    case Core.VCtr{k9, fs9}:
                      Unit{}
                    case Core.VClo{+ce, +cp, +cb}:
                      match rel:
                        case (vs2, tla):
                          match vs2:
                            case Nil{}:
                              match tla:
                                case (fv2, tlb):
                                  match tlb:
                                    case (eq, vr, fr):
                                      match vr:
                            case +v2 <> +r2:
                              match tla:
                                case (fv2, tlb):
                                  match fv2:
                                    case Core.VLit{l8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VCtr{k8, fs8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VClo{+ce2, cp2, cb2}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match vr:
                                            case (vv, vrest):
                                              match fr:
                                                case (ep, +sg0, eb, +venv, +mir):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{ce, cp, cb}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                                  %ep : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{ce, cp, cb}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SApply{v2 <> r2, Core.VClo{ce2, _, cb2}}))
                                                  %eb : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{ce, cp, cb}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SApply{v2 <> r2, Core.VClo{ce2, cp, _}}))
                                                  L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{ce, [cp], [v]}), Core.KBody{cb, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{ce2, [cp], [v2]}), Core.KBody{Core.Tm.lits(cb, Core.Sub.bind(Core.Dead.names([cp]), sg0)), r2}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{ce2, [cp], [v2]}), Core.KBody{Core.Tm.lits(cb, Core.Sub.bind(Core.Dead.names([cp]), sg0)), r2}, Core.Sub.bind(Core.Dead.names([cp]), sg0), {==}, (r2, {==}, vrest),
                                                    L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{ce, [cp], [v]}, Core.SPat{ce2, [cp], [v2]}, Core.Sub.bind(Core.Dead.names([cp]), sg0), (ce2, [v2], sg0, {==}, (vv, Unit{}), venv, mir, {==})))})
                                    case Core.VFun{f8, as8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VTrm{t8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VBnd{x8, w8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                    case Core.VFun{+fg, +fa}:
                      match rel:
                        case (vs2, tla):
                          match vs2:
                            case Nil{}:
                              match tla:
                                case (fv2, tlb):
                                  match tlb:
                                    case (eq, vr, fr):
                                      match vr:
                            case +v2 <> +r2:
                              match tla:
                                case (fv2, tlb):
                                  match fv2:
                                    case Core.VLit{l8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VCtr{k8, fs8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VClo{env8, p8, b8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VFun{fg2, +fa2}:
                                      match tlb:
                                        case (eq, +vr, fr):
                                          match fr:
                                            case (ef, far):
                                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{fg, fa}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                              %ef : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{fg, fa}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), Core.SApply{v2 <> r2, Core.VFun{_, fa2}}))
                                              L.lit(~prim, ~ok, p, q, le, ds, Core.SCallDef{fg, Core.Vals.cat(fa, v <> r)}, Core.SCallDef{fg, Core.Vals.cat(fa2, v2 <> r2)}, S, (Core.Vals.cat(fa2, v2 <> r2), {==}, Cat(fa, fa2, v <> r, v2 <> r2, far, vr)))
                                    case Core.VTrm{t8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                                    case Core.VBnd{x8, w8}:
                                      match tlb:
                                        case (eq, vr, fr):
                                          match fr:
                    case Core.VTrm{t9}:
                      Unit{}
                    case Core.VBnd{x9, w9}:
                      Unit{}
            case Core.SMatch{+e1, +vs, cs}:
              match cs:
                case Nil{}:
                  Unit{}
                case c <> +r:
                  match c:
                    case Core.CVar{x0}:
                      Unit{}
                    case Core.CCall{f0, as0}:
                      Unit{}
                    case Core.CApp{f0, as0}:
                      Unit{}
                    case Core.CCtr{k0, as0}:
                      Unit{}
                    case Core.CLam{p0, b0}:
                      Unit{}
                    case Core.CLet{p0, v0, b0}:
                      Unit{}
                    case Core.CMat{scrs0, cases0}:
                      Unit{}
                    case Core.CCse{+ps0, +b0}:
                      match rel:
                        case (+e2, +vs2, +sg, eq, +vr, +venv, +mir):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SMatch{e1, vs, Core.CCse{ps0, b0} <> r}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{e1, ps0, vs}), Core.KCase{e1, vs, b0, r}}, Core.SThen{Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, ps0, vs2}), Core.KCase{e2, vs2, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names(ps0), sg)), Core.Tms.lits(r, sg)}}, S, Inl{(Core.run(~prim, q, Core.Defs.lit(ds), Core.SPat{e2, ps0, vs2}), Core.KCase{e2, vs2, Core.Tm.lits(b0, Core.Sub.bind(Core.Dead.names(ps0), sg)), Core.Tms.lits(r, sg)}, Core.Sub.bind(Core.Dead.names(ps0), sg), {==}, (e2, vs2, sg, {==}, vr, venv, mir),
                            L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{e1, ps0, vs}, Core.SPat{e2, ps0, vs2}, Core.Sub.bind(Core.Dead.names(ps0), sg), (e2, vs2, sg, {==}, vr, venv, mir, {==})))})
                    case Core.CSuc{k0, e0}:
                      Unit{}
                    case Core.COp{op0, a0, b0}:
                      Unit{}
                    case Core.CAnn{e0, ty0}:
                      Unit{}
                    case Core.CLit{l0}:
                      Unit{}
                    case Core.CRef{f0}:
                      Unit{}
                    case Core.CTyp{n0, as0}:
                      Unit{}
                    case Core.CBox{}:
                      Unit{}
                    case Core.CErr{m0}:
                      Unit{}
            case Core.SPat{+e1, ps, vs}:
              match ps:
                case Nil{}:
                  match vs:
                    case Nil{}:
                      match rel:
                        case (+e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          match tld:
                                            case (venv, mir, eb):
                                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, Nil{}, Nil{}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                              %eb : Law.RRel(Core.REnv{e1}, _, Core.REnv{e2})
                                              (venv, mir)
                                case w <> s:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          match vr:
                    case v <> vt:
                      match rel:
                        case (+e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          match vr:
                                case w <> s:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, Nil{}, v <> vt}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          Unit{}
                case +pt <> +pr:
                  match vs:
                    case Nil{}:
                      match rel:
                        case (+e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, pt <> pr, Nil{}}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                          Unit{}
                                case w <> s:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          match vr:
                    case +v <> +vt:
                      match rel:
                        case (+e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          match vr:
                                case +v2 <> +vt2:
                                  match tlb:
                                    case (+sg, eq, tlc):
                                      match tlc:
                                        case (vr, tld):
                                          match vr:
                                            case (vv, +rr):
                                              match tld:
                                                case (+venv, +mir, +eb):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, pt <> pr, v <> vt}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                                                  L.lit(~prim, ~ok, p, q, le, ds, Core.Pat.step(e1, pt, v, pr, vt), Core.Pat.step(e2, pt, v2, pr, vt2), S, Pat.rel(e1, pt, v, pr, vt, e2, v2, vt2, S, sg, vv, rr, venv, mir, eb))
            case Core.SPatC{hit, +e1, +ps, +vs}:
              match hit:
                case True{}:
                  match rel:
                    case (+e2, +vs2, eq, pc):
                      match pc:
                        case (sg, vr, venv, mir, eb):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPatC{True{}, e1, ps, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                          L.lit(~prim, ~ok, p, q, le, ds, Core.SPat{e1, ps, vs}, Core.SPat{e2, ps, vs2}, S, (e2, vs2, sg, {==}, vr, venv, mir, eb))
                case False{}:
                  match rel:
                    case (e2, vs2, eq, pc):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPatC{False{}, e1, ps, vs}), S, Core.run(~prim, 1n+q, Core.Defs.lit(ds), _))
                      Unit{}

# Equality
# ========

# Related values without closures are the same.
def Eq.val(v1: Core.Val, v2: Core.Val, vr: Law.VRel(v1, v2), c: Dead.NoClo(v1)) -> {v1 == v2 : Core.Val}:
  match v1:
    case Core.VLit{l}:
      match v2:
        case Core.VLit{l2}:
          %vr : {Core.VLit{l} == Core.VLit{_} : Core.Val}
          {==}
        case Core.VCtr{k8, fs8}:
          match vr:
        case Core.VClo{env8, p8, b8}:
          match vr:
        case Core.VFun{f8, as8}:
          match vr:
        case Core.VTrm{t8}:
          match vr:
        case Core.VBnd{x8, w8}:
          match vr:
    case Core.VCtr{+k, fs}:
      match fs:
        case Nil{}:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{k2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      %ek : {Core.VCtr{k, Nil{}} == Core.VCtr{_, Nil{}} : Core.Val}
                      {==}
                case w <> s:
                  match vr:
                    case (ek, vrs):
                      match vrs:
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{f8, as8}:
              match vr:
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
        case +f <> +r:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{+k2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                case +f2 <> +r2:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                        case (vf, vrr):
                          match c:
                            case (cf, cr):
                              %DP.Val.sym(Core.VCtr{k, r}, Core.VCtr{k2, r2}, Eq.val(Core.VCtr{k, r}, Core.VCtr{k2, r2}, (ek, vrr), cr)) : {Core.Val.push(f, _) == Core.VCtr{k2, f2 <> r2} : Core.Val}
                              %DP.Val.sym(f, f2, Eq.val(f, f2, vf, cf)) : {Core.VCtr{k2, _ <> r2} == Core.VCtr{k2, f2 <> r2} : Core.Val}
                              {==}
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{f8, as8}:
              match vr:
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
    case Core.VClo{ce, cp, cb}:
      match c:
    case Core.VFun{+g, fs}:
      match fs:
        case Nil{}:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{k8, fs8}:
              match vr:
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{g2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      %ek : {Core.VFun{g, Nil{}} == Core.VFun{_, Nil{}} : Core.Val}
                      {==}
                case w <> s:
                  match vr:
                    case (ek, vrs):
                      match vrs:
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
        case +f <> +r:
          match v2:
            case Core.VLit{l8}:
              match vr:
            case Core.VCtr{k8, fs8}:
              match vr:
            case Core.VClo{env8, p8, b8}:
              match vr:
            case Core.VFun{+g2, fs2}:
              match fs2:
                case Nil{}:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                case +f2 <> +r2:
                  match vr:
                    case (ek, vrs):
                      match vrs:
                        case (vf, vrr):
                          match c:
                            case (cf, cr):
                              %DP.Val.sym(Core.VFun{g, r}, Core.VFun{g2, r2}, Eq.val(Core.VFun{g, r}, Core.VFun{g2, r2}, (ek, vrr), cr)) : {Core.Val.push(f, _) == Core.VFun{g2, f2 <> r2} : Core.Val}
                              %DP.Val.sym(f, f2, Eq.val(f, f2, vf, cf)) : {Core.VFun{g2, _ <> r2} == Core.VFun{g2, f2 <> r2} : Core.Val}
                              {==}
            case Core.VTrm{t8}:
              match vr:
            case Core.VBnd{x8, w8}:
              match vr:
    case Core.VTrm{t}:
      match v2:
        case Core.VLit{l8}:
          match vr:
        case Core.VCtr{k8, fs8}:
          match vr:
        case Core.VClo{env8, p8, b8}:
          match vr:
        case Core.VFun{f8, as8}:
          match vr:
        case Core.VTrm{t2}:
          %vr : {Core.VTrm{t} == Core.VTrm{_} : Core.Val}
          {==}
        case Core.VBnd{x8, w8}:
          match vr:
    case Core.VBnd{+x, +w}:
      match v2:
        case Core.VLit{l8}:
          match vr:
        case Core.VCtr{k8, fs8}:
          match vr:
        case Core.VClo{env8, p8, b8}:
          match vr:
        case Core.VFun{f8, as8}:
          match vr:
        case Core.VTrm{t8}:
          match vr:
        case Core.VBnd{x2, +w2}:
          match vr:
            case (ex, vw):
              %ex : {Core.VBnd{x, w} == Core.VBnd{_, w2} : Core.Val}
              %DP.Val.sym(w, w2, Eq.val(w, w2, vw, c)) : {Core.VBnd{x, _} == Core.VBnd{x, w2} : Core.Val}
              {==}

def Eq.vals(vs1: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs1, vs2), c: Dead.NoClos(vs1))
    -> {vs1 == vs2 : List<&2, Core.Val>}:
  match vs1:
    case Nil{}:
      match vs2:
        case Nil{}:
          {==}
        case w <> s:
          match vr:
    case +v <> +r:
      match vs2:
        case Nil{}:
          match vr:
        case +w <> +s:
          match vr:
            case (vv, vrr):
              match c:
                case (cv, cr):
                  %Eq.val(v, w, vv, cv) : {v <> r == _ <> s : List<&2, Core.Val>}
                  %Eq.vals(r, s, vrr, cr) : {v <> r == v <> _ : List<&2, Core.Val>}
                  {==}

# Related results, the first clean: the same.
def Eq.res(r1: Core.Res, r2: Core.Res, -S: List<&2, Core.Sub>, rr: Law.RRel(r1, S, r2), c: Dead.Clean(r1))
    -> {r1 == r2 : Core.Res}:
  match r1:
    case Core.ROk{+vs1}:
      match r2:
        case Core.ROk{+vs2}:
          %Eq.vals(vs1, vs2, rr, c) : {Core.ROk{vs1} == Core.ROk{_} : Core.Res}
          {==}
        case Core.REnv{e9}:
          match rr:
        case Core.RNo{}:
          match rr:
        case Core.RFail{m9}:
          match rr:
    case Core.REnv{e1}:
      match c:
    case Core.RNo{}:
      match r2:
        case Core.ROk{vs9}:
          match rr:
        case Core.REnv{e9}:
          match rr:
        case Core.RNo{}:
          {==}
        case Core.RFail{m9}:
          match rr:
    case Core.RFail{m}:
      match c:

# The laws
# ========

def L.top(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(vs1, vs2) -> Law.PRel(prim(op, vs1), prim(op, vs2)),
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, s1: Core.Sel, s2: Core.Sel,
    -S: List<&2, Core.Sub>, rel: Law.SRel(s1, S, s2))
    -> Law.RRel(Core.run(~prim, n, ds, s1), S, Core.run(~prim, m, Core.Defs.lit(ds), s2)):
  L.lit(~prim, ~ok, n, m, le, ds, s1, s2, S, rel)

def Eq.top(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(vs1, vs2) -> Law.PRel(prim(op, vs1), prim(op, vs2)),
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, nf: Dead.Clean(Core.Prog.run(~prim, n, ds)))
    -> {Core.Prog.run(~prim, n, ds) == Core.Prog.run(~prim, m, Core.Defs.lit(ds)) : Core.Res}:
  Eq.res(Core.Prog.run(~prim, n, ds), Core.Prog.run(~prim, m, Core.Defs.lit(ds)), Nil{},
    L.top(~prim, ~ok, n, m, le, ds, Core.SCallDef{"main", Nil{}}, Core.SCallDef{"main", Nil{}}, Nil{}, (Nil{}, {==}, Unit{})), nf)

def Law.lit_ok(prim, ok, n, m, le, ds, S, s1, s2, rel):
  L.top(~prim, ~ok, n, m, le, ds, s1, s2, S, rel)

def Law.lit_prog(prim, ok, n, m, le, ds, nf):
  Eq.top(~prim, ~ok, n, m, le, ds, nf)
