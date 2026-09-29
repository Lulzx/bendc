import Base
import ./RED.bend as Red
import ./core.bend as Core
import ./REDPROOF.bend as RP
import ./DEAD.bend as Law

# Proof of DEAD.bend's laws. L.dead (dead_ok): induction on the source's
# fuel, one case per step of `run`; at a dead let's steps (the value's run
# and its binding) the source steps while the other program stays at the
# let's body, so its fuel is the source's plus the steps left. A lookup
# (Look) passes the bindings the other program lacks: none is the one it
# looks for, since no lookup reaches them. The scope relations of the steps
# differ in the lookups they stand for: the conversions (Conv) give one from
# another where the first's are more.

# Booleans
# ========

def OrL(a: Bool, b: Bool, h: Law.Fls(Bool.or(a, b))) -> Law.Fls(a):
  match a:
    case True{}:
      match h:
    case False{}:
      Unit{}

def OrR(a: Bool, b: Bool, h: Law.Fls(Bool.or(a, b))) -> Law.Fls(b):
  match a:
    case True{}:
      match h:
    case False{}:
      h

def OrI(a: Bool, b: Bool, ha: Law.Fls(a), hb: Law.Fls(b)) -> Law.Fls(Bool.or(a, b)):
  match a:
    case True{}:
      match ha:
    case False{}:
      hb

def Contra(-T: Data, c: Bool, a: Law.Fls(c), t: Law.Tru(c)) -> T:
  match c:
    case True{}:
      match a:
    case False{}:
      match t:

def Fls.of(-b: Bool, e: {False{} == b : Bool}) -> Law.Fls(b):
  %e : Law.Fls(_)
  Unit{}

def Tm.sym(-x: Core.Tm, -y: Core.Tm, e: {x == y : Core.Tm}) -> {y == x : Core.Tm}:
  %e : {_ == x : Core.Tm}
  {==}

# Transports
# ==========

def Tr.lk(-a: Core.Tm, -b: Core.Tm, e: {a == b : Core.Tm}, -e1: List<&2, Core.Val>, -hs: List<&2, String>, -e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(a), hs, e2)) -> Law.ERel(e1, Law.Lk(b), hs, e2):
  %e : Law.ERel(e1, Law.Lk(_), hs, e2)
  h

def Tr.hs(-a: List<&2, String>, -b: List<&2, String>, e: {a == b : List<&2, String>}, -e1: List<&2, Core.Val>,
    -U: List<&2, String> -> String -> Bool, -e2: List<&2, Core.Val>,
    h: Law.ERel(e1, U, a, e2)) -> Law.ERel(e1, U, b, e2):
  %e : Law.ERel(e1, U, _, e2)
  h

# Conversions
# ===========

# A scope related for the lookups of a term, related for those of a part of
# it: a binding missing that none of the term's lookups reaches is one none
# of the part's reaches. (Shift: the lookups of a case's body, past its
# patterns' names.)

def Conv.call.l(+f: String, +rel: Core.Rel, +e: Core.Tm, +r: List<&2, Core.Arg>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CCall{f, Core.Arg{rel, e} <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(e), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCall{f, r}, hs, z), a9), Conv.call.l(f, rel, e, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCall{f, r}, hs, z), a9), Conv.call.l(f, rel, e, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.call.l(f, rel, e, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.l(f, rel, e, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.l(f, rel, e, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.l(f, rel, e, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.l(f, rel, e, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.l(f, rel, e, r, r1, hs, r2, b9))

def Conv.call.r(+f: String, +rel: Core.Rel, +e: Core.Tm, +r: List<&2, Core.Arg>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CCall{f, Core.Arg{rel, e} <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CCall{f, r}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCall{f, r}, hs, z), a9), Conv.call.r(f, rel, e, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCall{f, r}, hs, z), a9), Conv.call.r(f, rel, e, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.call.r(f, rel, e, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.r(f, rel, e, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.r(f, rel, e, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.r(f, rel, e, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.r(f, rel, e, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.call.r(f, rel, e, r, r1, hs, r2, b9))

# A box looks nothing up: any scope's relation holds for it.
def Conv.box(-U: List<&2, String> -> String -> Bool, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, U, hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CBox{}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (Unit{}, Conv.box(U, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(Unit{}, Conv.box(U, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.box(U, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.box(U, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.box(U, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.box(U, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.box(U, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.box(U, r1, hs, r2, b9))

def Conv.ctr.l(+k: String, +e: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CCtr{k, e <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(e), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCtr{k, r}, hs, z), a9), Conv.ctr.l(k, e, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCtr{k, r}, hs, z), a9), Conv.ctr.l(k, e, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.ctr.l(k, e, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.l(k, e, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.l(k, e, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.l(k, e, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.l(k, e, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.l(k, e, r, r1, hs, r2, b9))

def Conv.ctr.r(+k: String, +e: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CCtr{k, e <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CCtr{k, r}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCtr{k, r}, hs, z), a9), Conv.ctr.r(k, e, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCtr{k, r}, hs, z), a9), Conv.ctr.r(k, e, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.ctr.r(k, e, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.r(k, e, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.r(k, e, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.r(k, e, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.r(k, e, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.ctr.r(k, e, r, r1, hs, r2, b9))

def Conv.app.l(+f: Core.Tm, +e: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CApp{f, e <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(e), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CApp{f, r}, hs, z), a9), Conv.app.l(f, e, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CApp{f, r}, hs, z), a9), Conv.app.l(f, e, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.app.l(f, e, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.l(f, e, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.l(f, e, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.l(f, e, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.l(f, e, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.l(f, e, r, r1, hs, r2, b9))

def Conv.app.r(+f: Core.Tm, +e: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CApp{f, e <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CApp{f, r}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CApp{f, r}, hs, z), a9), Conv.app.r(f, e, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CApp{f, r}, hs, z), a9), Conv.app.r(f, e, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.app.r(f, e, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.r(f, e, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.r(f, e, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.r(f, e, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.r(f, e, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.app.r(f, e, r, r1, hs, r2, b9))

def Conv.mat.l(+e: Core.Tm, +r: List<&2, Core.Tm>, +cs: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CMat{e <> r, cs}), hs, e2)) -> Law.ERel(e1, Law.Lk(e), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CMat{r, cs}, hs, z), a9), Conv.mat.l(e, r, cs, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CMat{r, cs}, hs, z), a9), Conv.mat.l(e, r, cs, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.mat.l(e, r, cs, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.l(e, r, cs, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.l(e, r, cs, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.l(e, r, cs, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.l(e, r, cs, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.l(e, r, cs, r1, hs, r2, b9))

def Conv.mat.r(+e: Core.Tm, +r: List<&2, Core.Tm>, +cs: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CMat{e <> r, cs}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CMat{r, cs}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CMat{r, cs}, hs, z), a9), Conv.mat.r(e, r, cs, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CMat{r, cs}, hs, z), a9), Conv.mat.r(e, r, cs, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.mat.r(e, r, cs, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.r(e, r, cs, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.r(e, r, cs, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.r(e, r, cs, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.r(e, r, cs, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.mat.r(e, r, cs, r1, hs, r2, b9))

def Conv.cases.l(+c: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CMat{Nil{}, c <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(c), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrL(Core.Dead.used(c, hs, z), Core.Dead.used(Core.CMat{Nil{}, r}, hs, z), a9), Conv.cases.l(c, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrL(Core.Dead.used(c, hs, z), Core.Dead.used(Core.CMat{Nil{}, r}, hs, z), a9), Conv.cases.l(c, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.cases.l(c, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.l(c, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.l(c, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.l(c, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.l(c, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.l(c, r, r1, hs, r2, b9))

def Conv.cases.r(+c: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CMat{Nil{}, c <> r}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CMat{Nil{}, r}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrR(Core.Dead.used(c, hs, z), Core.Dead.used(Core.CMat{Nil{}, r}, hs, z), a9), Conv.cases.r(c, r, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrR(Core.Dead.used(c, hs, z), Core.Dead.used(Core.CMat{Nil{}, r}, hs, z), a9), Conv.cases.r(c, r, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.cases.r(c, r, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.r(c, r, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.r(c, r, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.r(c, r, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.r(c, r, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.cases.r(c, r, r1, hs, r2, b9))

def Conv.let.l(+p: Core.Pt, +v: Core.Tm, +b: Core.Tm, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CLet{p, v, b}), hs, e2)) -> Law.ERel(e1, Law.Lk(v), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrL(Core.Dead.used(v, hs, z), Core.Dead.used(b, Core.Dead.cat(hs, Core.Dead.names([p])), z), a9), Conv.let.l(p, v, b, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrL(Core.Dead.used(v, hs, z), Core.Dead.used(b, Core.Dead.cat(hs, Core.Dead.names([p])), z), a9), Conv.let.l(p, v, b, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.let.l(p, v, b, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.l(p, v, b, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.l(p, v, b, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.l(p, v, b, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.l(p, v, b, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.l(p, v, b, r1, hs, r2, b9))

def Conv.let.r(+p: Core.Pt, +v: Core.Tm, +b: Core.Tm, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CLet{p, v, b}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CCse{[p], b}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (OrR(Core.Dead.used(v, hs, z), Core.Dead.used(b, Core.Dead.cat(hs, Core.Dead.names([p])), z), a9), Conv.let.r(p, v, b, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(OrR(Core.Dead.used(v, hs, z), Core.Dead.used(b, Core.Dead.cat(hs, Core.Dead.names([p])), z), a9), Conv.let.r(p, v, b, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.let.r(p, v, b, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.r(p, v, b, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.r(p, v, b, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.r(p, v, b, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.r(p, v, b, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.let.r(p, v, b, r1, hs, r2, b9))

def Shift(+ps: List<&2, Core.Pt>, +b: Core.Tm, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CCse{ps, b}), hs, e2)) -> Law.ERel(e1, Law.Lk(b), Core.Dead.cat(hs, Core.Dead.names(ps)), e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (a9, Shift(ps, b, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(a9, Shift(ps, b, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Shift(ps, b, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Shift(ps, b, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Shift(ps, b, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Shift(ps, b, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Shift(ps, b, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Shift(ps, b, r1, hs, r2, b9))

# An application's lookups, as its arguments' (the function's are more).
def App.ctr(+f: Core.Tm, as: List<&2, Core.Tm>, +hs: List<&2, String>, +z: String, +a: Law.Fls(Core.Dead.used(Core.CApp{f, as}, hs, z)))
    -> Law.Fls(Core.Dead.used(Core.CCtr{"", as}, hs, z)):
  match as:
    case Nil{}:
      Unit{}
    case +e <> +r:
      OrI(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CCtr{"", r}, hs, z),
        OrL(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CApp{f, r}, hs, z), a),
        App.ctr(f, r, hs, z, OrR(Core.Dead.used(e, hs, z), Core.Dead.used(Core.CApp{f, r}, hs, z), a)))


def Conv.head(+f: Core.Tm, +as: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CApp{f, as}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CCtr{"", as}), hs, e2):
  match e1:
    case Nil{}:
      match e2:
        case Nil{}:
          Unit{}
        case y <> r2:
          match h:
    case x <> r1:
      match x:
        case Core.VBnd{+z, +w}:
          match e2:
            case Nil{}:
              match h:
                case (a9, b9):
                  (App.ctr(f, as, hs, z, a9), Conv.head(f, as, r1, hs, Nil{}, b9))
            case +y <> +r2:
              match h:
                case Inl{d9}:
                  match d9:
                    case (a9, b9):
                      Inl{(App.ctr(f, as, hs, z, a9), Conv.head(f, as, r1, hs, y <> r2, b9))}
                case Inr{k9}:
                  match k9:
                    case (a9, b9):
                      Inr{(a9, Conv.head(f, as, r1, z <> hs, r2, b9))}
        case Core.VLit{l9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.head(f, as, r1, hs, r2, b9))
        case Core.VCtr{k9, fs9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.head(f, as, r1, hs, r2, b9))
        case Core.VClo{env9, p9, b9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.head(f, as, r1, hs, r2, b9))
        case Core.VFun{f9, as9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.head(f, as, r1, hs, r2, b9))
        case Core.VTrm{t9}:
          match e2:
            case Nil{}:
              match h:
            case y <> r2:
              match h:
                case (a9, b9):
                  (a9, Conv.head(f, as, r1, hs, r2, b9))

# An application's lookups, as its function's.
def Conv.fn(+f: Core.Tm, as: List<&2, Core.Tm>, +e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CApp{f, as}), hs, e2)) -> Law.ERel(e1, Law.Lk(f), hs, e2):
  match as:
    case Nil{}:
      h
    case +e <> +r:
      Conv.fn(f, r, e1, hs, e2, Conv.app.r(f, e, r, e1, hs, e2, h))

# A match's lookups, as its cases'.
def Conv.skip(scrs: List<&2, Core.Tm>, +cs: List<&2, Core.Tm>, +e1: List<&2, Core.Val>, +hs: List<&2, String>, +e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Core.CMat{scrs, cs}), hs, e2)) -> Law.ERel(e1, Law.Lk(Core.CMat{Nil{}, cs}), hs, e2):
  match scrs:
    case Nil{}:
      h
    case +e <> +r:
      Conv.skip(r, cs, e1, hs, e2, Conv.mat.r(e, r, cs, e1, hs, e2, h))

# The rest of a list of terms after its head.
def Wrap.next(w: Law.Wrap) -> Law.Wrap:
  match w:
    case Law.WMat{cs}:
      Law.WMat{cs}
    case Law.WApp{f}:
      Law.WApp{f}
    case Law.WCtr{k}:
      Law.WCtr{k}
    case Law.WHead{}:
      Law.WCtr{""}

def Conv.wrap.l(w: Law.Wrap, +e: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Law.Wrap.tm(w, e <> r)), hs, e2)) -> Law.ERel(e1, Law.Lk(e), hs, e2):
  match w:
    case Law.WMat{cs}:
      Conv.mat.l(e, r, cs, e1, hs, e2, h)
    case Law.WApp{f}:
      Conv.app.l(f, e, r, e1, hs, e2, h)
    case Law.WCtr{k}:
      Conv.ctr.l(k, e, r, e1, hs, e2, h)
    case Law.WHead{}:
      Conv.fn(e, r, e1, hs, e2, h)

def Conv.wrap.r(+w: Law.Wrap, +e: Core.Tm, +r: List<&2, Core.Tm>, e1: List<&2, Core.Val>, +hs: List<&2, String>, e2: List<&2, Core.Val>,
    h: Law.ERel(e1, Law.Lk(Law.Wrap.tm(w, e <> r)), hs, e2)) -> Law.ERel(e1, Law.Lk(Law.Wrap.tm(Wrap.next(w), r)), hs, e2):
  match w:
    case Law.WMat{cs}:
      Conv.mat.r(e, r, cs, e1, hs, e2, h)
    case Law.WApp{f}:
      Conv.app.r(f, e, r, e1, hs, e2, h)
    case Law.WCtr{k}:
      Conv.ctr.r(k, e, r, e1, hs, e2, h)
    case Law.WHead{}:
      Conv.head(e, r, e1, hs, e2, h)

# Shapes
# ======

# Tm.dead walks a list field as its head and the node rebuilt with the
# rest; these give the node with the field's terms taken as a whole.

def D.call(f: String, as: List<&2, Core.Arg>)
    -> {Core.CCall{f, Core.Args.dead(as)} == Core.Tm.dead(Core.CCall{f, as}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          %D.call(f, r) : {Core.CCall{f, Core.Arg{rel, Core.Tm.dead(e)} <> Core.Args.dead(r)} == Core.Tm.push.call(Core.Arg{rel, Core.Tm.dead(e)}, _) : Core.Tm}
          {==}

def D.app(f: Core.Tm, as: List<&2, Core.Tm>)
    -> {Core.CApp{Core.Tm.dead(f), Core.Tms.dead(as)} == Core.Tm.dead(Core.CApp{f, as}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %D.app(f, r) : {Core.CApp{Core.Tm.dead(f), Core.Tm.dead(a) <> Core.Tms.dead(r)} == Core.Tm.push(Core.Tm.dead(a), _) : Core.Tm}
      {==}

def D.ctr(k: String, as: List<&2, Core.Tm>)
    -> {Core.CCtr{k, Core.Tms.dead(as)} == Core.Tm.dead(Core.CCtr{k, as}) : Core.Tm}:
  match as:
    case Nil{}:
      {==}
    case a <> r:
      %D.ctr(k, r) : {Core.CCtr{k, Core.Tm.dead(a) <> Core.Tms.dead(r)} == Core.Tm.push(Core.Tm.dead(a), _) : Core.Tm}
      {==}

def D.cases(cs: List<&2, Core.Tm>)
    -> {Core.CMat{Nil{}, Core.Tms.dead(cs)} == Core.Tm.dead(Core.CMat{Nil{}, cs}) : Core.Tm}:
  match cs:
    case Nil{}:
      {==}
    case c <> r:
      %D.cases(r) : {Core.CMat{Nil{}, Core.Tm.dead(c) <> Core.Tms.dead(r)} == Core.Tm.push.case(Core.Tm.dead(c), _) : Core.Tm}
      {==}

def D.mat(scrs: List<&2, Core.Tm>, cs: List<&2, Core.Tm>)
    -> {Core.CMat{Core.Tms.dead(scrs), Core.Tms.dead(cs)} == Core.Tm.dead(Core.CMat{scrs, cs}) : Core.Tm}:
  match scrs:
    case Nil{}:
      D.cases(cs)
    case a <> r:
      %D.mat(r, cs) : {Core.CMat{Core.Tm.dead(a) <> Core.Tms.dead(r), Core.Tms.dead(cs)} == Core.Tm.push(Core.Tm.dead(a), _) : Core.Tm}
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

# A def's parameters bound to related values: related scopes, none missing.
# The names a def's parameters bound to vs put in front of hs.
def Bind.hs(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, hs: List<&2, String>) -> List<&2, String>:
  match ps:
    case Nil{}:
      hs
    case q <> pr:
      match q:
        case Core.Par{x, rel, mode, ty}:
          match vs:
            case Nil{}:
              hs
            case v <> r:
              x <> Bind.hs(pr, r, hs)

# A def's parameters bound to related values in front of related scopes:
# related scopes, none missing (acc's relation past the parameters' names).
def Bind.push(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs, vs2),
    -U: List<&2, String> -> String -> Bool, +hs: List<&2, String>, acc: List<&2, Core.Val>, acc2: List<&2, Core.Val>,
    ha: Law.ERel(acc, U, Bind.hs(ps, vs, hs), acc2))
    -> Law.ERel(Core.Scope.push(ps, vs, acc), U, hs, Core.Scope.push(ps, vs2, acc2)):
  match ps:
    case Nil{}:
      ha
    case q <> pr:
      match q:
        case Core.Par{+x, rel, mode, ty}:
          match vs:
            case Nil{}:
              match vs2:
                case Nil{}:
                  ha
                case w <> s:
                  match vr:
            case v <> r:
              match vs2:
                case Nil{}:
                  match vr:
                case w <> s:
                  match vr:
                    case (a, b):
                      Bind.push(pr, r, s, b, U, hs, Core.VBnd{x, v} <> acc, Core.VBnd{x, w} <> acc2, Inr{(({==}, a), ha)})

# A def's parameters bound to related values: related scopes, none missing.
def Bind(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs, vs2),
    -U: List<&2, String> -> String -> Bool, +hs: List<&2, String>)
    -> Law.ERel(Core.Scope.bind(ps, vs), U, hs, Core.Scope.bind(ps, vs2)):
  Bind.push(ps, vs, vs2, vr, U, hs, Nil{}, Nil{}, Unit{})

def Names.assoc(a: List<&2, String>, +b: List<&2, String>, +c: List<&2, String>)
    -> {Core.Dead.cat(Core.Dead.cat(a, b), c) == Core.Dead.cat(a, Core.Dead.cat(b, c)) : List<&2, String>}:
  match a:
    case Nil{}:
      {==}
    case x <> r:
      %Names.assoc(r, b, c) : {x <> Core.Dead.cat(Core.Dead.cat(r, b), c) == x <> _ : List<&2, String>}
      {==}

def Names.cat(qs: List<&2, Core.Pt>, +pr: List<&2, Core.Pt>)
    -> {Core.Dead.cat(Core.Dead.names(qs), Core.Dead.names(pr)) == Core.Dead.names(Core.Pts.cat(qs, pr)) : List<&2, String>}:
  match qs:
    case Nil{}:
      {==}
    case q <> +r:
      match q:
        case Core.PtVar{x}:
          %Names.cat(r, pr) : {x <> Core.Dead.cat(Core.Dead.names(r), Core.Dead.names(pr)) == x <> _ : List<&2, String>}
          {==}
        case Core.PtCtr{k, +qs2}:
          %Names.cat(r, pr) : {Core.Dead.cat(Core.Dead.cat(Core.Dead.names(qs2), Core.Dead.names(r)), Core.Dead.names(pr)) == Core.Dead.cat(Core.Dead.names(qs2), _) : List<&2, String>}
          Names.assoc(Core.Dead.names(qs2), Core.Dead.names(r), Core.Dead.names(pr))
        case Core.PtSuc{k, q2}:
          Names.cat(q2 <> r, pr)
        case Core.PtNat{n}:
          Names.cat(r, pr)
        case Core.PtNum{n}:
          Names.cat(r, pr)
        case Core.PtFlt{s}:
          Names.cat(r, pr)

# Fuel
# ====

def Le.down(+a: Nat, +b: Nat, +h: Red.Le(1n+a, b)) -> Red.Le(a, b):
  match b:
    case 0n:
      match h:
    case 1n+c:
      RP.Le.succ(a, c, h)

# Natives
# =======

def Prim(r1: Core.Res, r2: Core.Res, h: Law.PRel(r1, r2), -U: List<&2, String> -> String -> Bool) -> Law.RRel(r1, U, r2):
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

# Decisions
# =========

# A Boolean's value, as a proof: the steps that branch on one computed in
# the proof (a lookup's hit, a let's use) take it as an argument.
def Dec(b: Bool) -> Data:
  Either<&2, &2, {True{} == b : Bool}, {False{} == b : Bool}>

def Dec.of(b: Bool) -> Dec(b):
  match b:
    case True{}:
      Inl{{==}}
    case False{}:
      Inr{{==}}

def Bool.sym(-x: Bool, -y: Bool, e: {x == y : Bool}) -> {y == x : Bool}:
  %e : {_ == x : Bool}
  {==}

# Whether a scope's first binding is x's.
def Dec.env(e: List<&2, Core.Val>, x: String) -> Data:
  match e:
    case Nil{}:
      Unit
    case b <> r:
      match b:
        case Core.VBnd{z, w}:
          Dec(String.eq(z, x))
        case other:
          Unit

def Dec.env.of(e: List<&2, Core.Val>, x: String) -> Dec.env(e, x):
  match e:
    case Nil{}:
      Unit{}
    case b <> r:
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
        case Core.VBnd{z, w}:
          Dec.of(String.eq(z, x))

# Whether a term is a let of a variable its body uses.
def Dec.tm(t: Core.Tm) -> Data:
  match t:
    case Core.CLet{p, v, +b}:
      match p:
        case Core.PtVar{x}:
          Dec(Core.Dead.used(Core.Tm.dead(b), Nil{}, x))
        case other:
          Unit
    case other:
      Unit

def Dec.tm.of(t: Core.Tm) -> Dec.tm(t):
  match t:
    case Core.CVar{x}:
      Unit{}
    case Core.CCall{f, as}:
      Unit{}
    case Core.CApp{f, as}:
      Unit{}
    case Core.CCtr{k, as}:
      Unit{}
    case Core.CLam{p, b}:
      Unit{}
    case Core.CLet{p, v, b}:
      match p:
        case Core.PtVar{x}:
          Dec.of(Core.Dead.used(Core.Tm.dead(b), Nil{}, x))
        case Core.PtCtr{k9, qs9}:
          Unit{}
        case Core.PtNat{n9}:
          Unit{}
        case Core.PtSuc{k9, q9}:
          Unit{}
        case Core.PtNum{n9}:
          Unit{}
        case Core.PtFlt{s9}:
          Unit{}
    case Core.CMat{scrs, cases}:
      Unit{}
    case Core.CCse{ps, b}:
      Unit{}
    case Core.CSuc{k, e}:
      Unit{}
    case Core.COp{op, a, b}:
      Unit{}
    case Core.CAnn{e, ty}:
      Unit{}
    case Core.CLit{l}:
      Unit{}
    case Core.CRef{f}:
      Unit{}
    case Core.CTyp{n, as}:
      Unit{}
    case Core.CBox{}:
      Unit{}
    case Core.CErr{m}:
      Unit{}

def Dec.sel(s: Core.Sel) -> Data:
  match s:
    case Core.SEval{env, e}:
      Dec.tm(e)
    case other:
      Unit

def Dec.sel.of(s: Core.Sel) -> Dec.sel(s):
  match s:
    case Core.SEval{env, e}:
      Dec.tm.of(e)
    case Core.SEvals{env, es}:
      Unit{}
    case Core.SArgs{env, as}:
      Unit{}
    case Core.SThen{r, k}:
      Unit{}
    case Core.SOk{k, vs}:
      Unit{}
    case Core.SLook{env, x}:
      Unit{}
    case Core.SLook2{hit, v, env, x}:
      Unit{}
    case Core.SCallDef{f, vs}:
      Unit{}
    case Core.SFind{ds, f, vs}:
      Unit{}
    case Core.SFound{hit, ps, b, ds, f, vs}:
      Unit{}
    case Core.SEnter{short, f, ps, b, vs}:
      Unit{}
    case Core.SApply{vs, fv}:
      Unit{}
    case Core.SMatch{env, vs, cases}:
      Unit{}
    case Core.SPat{env, ps, vs}:
      Unit{}
    case Core.SPatC{hit, env, ps, vs}:
      Unit{}

# Patterns
# ========

def PatC.mk(h: Bool, -U: List<&2, String> -> String -> Bool, -e1: List<&2, Core.Val>, -ps: List<&2, Core.Pt>, -vs: List<&2, Core.Val>,
    -e2: List<&2, Core.Val>, -vs2: List<&2, Core.Val>, vr: Law.VRels(vs, vs2), he: Law.ERel(e1, U, Core.Dead.names(ps), e2))
    -> Law.PatC.rel(h, U, e1, ps, vs, e2, vs2):
  match h:
    case True{}:
      (vr, he)
    case False{}:
      Unit{}

# A dead let's binding: the source's scope with it is related to the other
# program's without it.
def Bind.stut(~prim: String -> List<&2, Core.Val> -> Core.Res, +p: Nat, +ds: List<&2, Core.Def>, +e1: List<&2, Core.Val>, +x: String,
    vs: List<&2, Core.Val>, +b: Core.Tm, e2: List<&2, Core.Val>, +h: Law.ERel(e1, Law.Lk(Core.Tm.dead(b)), Nil{}, e2),
    +u: Law.Fls(Core.Dead.used(Core.Tm.dead(b), Nil{}, x)))
    -> Law.Stut.bind(Core.run(~prim, p, ds, Core.SPat{e1, [Core.PtVar{x}], vs}), b, Core.SEval{e2, Core.Tm.dead(b)}):
  match p:
    case 0n:
      Unit{}
    case 1n+p2:
      match p2:
        case 0n:
          match vs:
            case Nil{}:
              Unit{}
            case v <> vr:
              Unit{}
        case 1n+p3:
          match vs:
            case Nil{}:
              Unit{}
            case v <> vr:
              match vr:
                case Nil{}:
                  match e2:
                    case Nil{}:
                      (Nil{}, {==}, (u, h))
                    case +y <> +r2:
                      (y <> r2, {==}, Inl{(u, h)})
                case w <> s:
                  Unit{}

# One pattern's step against related values.
def Pat.rel(+e1: List<&2, Core.Val>, pt: Core.Pt, +v: Core.Val, +pr: List<&2, Core.Pt>, +vr: List<&2, Core.Val>,
    +e2: List<&2, Core.Val>, +v2: Core.Val, +vr2: List<&2, Core.Val>, -U: List<&2, String> -> String -> Bool,
    vv: Law.VRel(v, v2), +rr: Law.VRels(vr, vr2), +h: Law.ERel(e1, U, Core.Dead.names(pt <> pr), e2))
    -> Law.SRel(Core.Pat.step(e1, pt, v, pr, vr), U, Core.Pat.step(e2, pt, v2, pr, vr2)):
  match pt:
    case Core.PtVar{+x}:
      (Core.VBnd{x, v2} <> e2, vr2, {==}, (rr, Inr{(({==}, vv), h)}))
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
                  %ek : Law.SRel(Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, U, Core.SPatC{Bool.and(String.eq(k, _), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs2))), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  %Len.eq(fs1, fs2, vf) : Law.SRel(Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr)}, U, Core.SPatC{Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), _)), e2, Core.Pts.cat(qs, pr), Core.Vals.cat(fs2, vr2)})
                  (e2, Core.Vals.cat(fs2, vr2), {==}, PatC.mk(Bool.and(String.eq(k, k1), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs1))), U, e1, Core.Pts.cat(qs, pr), Core.Vals.cat(fs1, vr), e2, Core.Vals.cat(fs2, vr2),
                    Cat(fs1, fs2, vr, vr2, vf, rr), Tr.hs(Core.Dead.cat(Core.Dead.names(qs), Core.Dead.names(pr)), Core.Dead.names(Core.Pts.cat(qs, pr)), Names.cat(qs, pr), e1, U, e2, h)))
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
              %vv : Law.SRel(Core.Pat.step(e1, Core.PtNat{n}, Core.VLit{l1}, pr, vr), U, Core.Pat.step(e2, Core.PtNat{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LNat{n}, l1), U, e1, pr, vr, e2, vr2, rr, h))
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
              %vv : Law.SRel(Core.Pat.step(e1, Core.PtNum{n}, Core.VLit{l1}, pr, vr), U, Core.Pat.step(e2, Core.PtNum{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LNum{n}, l1), U, e1, pr, vr, e2, vr2, rr, h))
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
              %vv : Law.SRel(Core.Pat.step(e1, Core.PtFlt{n}, Core.VLit{l1}, pr, vr), U, Core.Pat.step(e2, Core.PtFlt{n}, Core.VLit{_}, pr, vr2))
              (e2, vr2, {==}, PatC.mk(Core.Lit.eq(Core.LFlt{n}, l1), U, e1, pr, vr, e2, vr2, rr, h))
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
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LNum{x9}}, pr, vr), U, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
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
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LNat{m}}, pr, vr), U, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
                  (e2, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr2, {==}, PatC.mk(U32.is_le(k, m), U, e1, q <> pr, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr,
                    e2, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr2, ({==}, rr), h))
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
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LFlt{x9}}, pr, vr), U, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
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
                  %vv : Law.SRel(Core.Pat.step(e1, Core.PtSuc{k, q}, Core.VLit{Core.LStr{x9}}, pr, vr), U, Core.Pat.step(e2, Core.PtSuc{k, q}, Core.VLit{_}, pr, vr2))
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

# Lookups
# =======

def Val.sym(-x: Core.Val, -y: Core.Val, e: {x == y : Core.Val}) -> {y == x : Core.Val}:
  %e : {_ == x : Core.Val}
  {==}

# A binding the other program lacks is not x's, if none of hs is x.
def Miss(-z: String, -x: String, -hs: List<&2, String>, eu: {True{} == String.eq(z, x) : Bool}, inv: Law.Tru(Core.Dead.none(hs, x)))
    -> Law.Tru(Bool.and(String.eq(z, x), Core.Dead.none(hs, x))):
  %eu : Law.Tru(Bool.and(_, Core.Dead.none(hs, x)))
  inv

def Inv.step(-z: String, -x: String, -hs: List<&2, String>, eu: {False{} == String.eq(z, x) : Bool}, inv: Law.Tru(Core.Dead.none(hs, x)))
    -> Law.Tru(Core.Dead.none(z <> hs, x)):
  %eu : Law.Tru(Bool.and(Bool.not(_), Core.Dead.none(hs, x)))
  inv

# A lookup of x: the source passes the bindings the other program lacks (a
# step each), and the two meet at the rest. hs: the names of the bindings
# both have passed, none of them x.
def Look(~prim: String -> List<&2, Core.Val> -> Core.Res, +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>,
    +x: String, e1: List<&2, Core.Val>, d: Dec.env(e1, x), +hs: List<&2, String>, e2: List<&2, Core.Val>, -U: List<&2, String> -> String -> Bool,
    h: Law.ERel(e1, Law.Lk(Core.CVar{x}), hs, e2), +inv: Law.Tru(Core.Dead.none(hs, x)))
    -> Law.RRel(Core.run(~prim, n, ds, Core.SLook{e1, x}), U, Core.run(~prim, m, Core.Defs.dead(ds), Core.SLook{e2, x})):
  match n:
    case 0n:
      Unit{}
    case 1n+p:
      match p:
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
          match m:
            case 0n:
              match le:
            case 1n+q:
              match q:
                case 0n:
                  match le:
                case 1n+q2:
                  match e1:
                    case Nil{}:
                      Unit{}
                    case b <> +r1:
                      match b:
                        case Core.VBnd{+z, +w}:
                            match d:
                              case Inl{eu}:
                                match e2:
                                  case Nil{}:
                                    match h:
                                      case (a, h2):
                                        Contra(Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Nil{}, x})), Bool.and(String.eq(z, x), Core.Dead.none(hs, x)), a, Miss(z, x, hs, eu, inv))
                                  case y <> r2:
                                    match y:
                                      case Core.VLit{l8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                Contra(Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VLit{l8} <> r2, x})), Bool.and(String.eq(z, x), Core.Dead.none(hs, x)), a, Miss(z, x, hs, eu, inv))
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VCtr{k8, fs8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                Contra(Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VCtr{k8, fs8} <> r2, x})), Bool.and(String.eq(z, x), Core.Dead.none(hs, x)), a, Miss(z, x, hs, eu, inv))
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VClo{env8, p8, b8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                Contra(Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VClo{env8, p8, b8} <> r2, x})), Bool.and(String.eq(z, x), Core.Dead.none(hs, x)), a, Miss(z, x, hs, eu, inv))
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VFun{f8, as8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                Contra(Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VFun{f8, as8} <> r2, x})), Bool.and(String.eq(z, x), Core.Dead.none(hs, x)), a, Miss(z, x, hs, eu, inv))
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VTrm{t8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                Contra(Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VTrm{t8} <> r2, x})), Bool.and(String.eq(z, x), Core.Dead.none(hs, x)), a, Miss(z, x, hs, eu, inv))
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VBnd{z2, w2}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                Contra(Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VBnd{z2, w2} <> r2, x})), Bool.and(String.eq(z, x), Core.Dead.none(hs, x)), a, Miss(z, x, hs, eu, inv))
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                                  case (ez, vw):
                                                    %ez : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VBnd{_, w2} <> r2, x}))
                                                    %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+q2, Core.Defs.dead(ds), Core.SLook2{_, w2, r2, x}))
                                                    (vw, Unit{})
                              case Inr{+eu}:
                                match e2:
                                  case Nil{}:
                                    match h:
                                      case (a, h2):
                                        %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Nil{}, x}))
                                        Look(~prim, p2, 1n+(1n+q2), RP.Le.succ(p2, 1n+q2, RP.Le.succ(p2, q2, le)), ds, x, r1, Dec.env.of(r1, x), hs, Nil{}, U, h2, inv)
                                  case y <> r2:
                                    match y:
                                      case Core.VLit{l8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VLit{l8} <> r2, x}))
                                                Look(~prim, p2, 1n+(1n+q2), RP.Le.succ(p2, 1n+q2, RP.Le.succ(p2, q2, le)), ds, x, r1, Dec.env.of(r1, x), hs, Core.VLit{l8} <> r2, U, h2, inv)
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VCtr{k8, fs8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VCtr{k8, fs8} <> r2, x}))
                                                Look(~prim, p2, 1n+(1n+q2), RP.Le.succ(p2, 1n+q2, RP.Le.succ(p2, q2, le)), ds, x, r1, Dec.env.of(r1, x), hs, Core.VCtr{k8, fs8} <> r2, U, h2, inv)
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VClo{env8, p8, b8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VClo{env8, p8, b8} <> r2, x}))
                                                Look(~prim, p2, 1n+(1n+q2), RP.Le.succ(p2, 1n+q2, RP.Le.succ(p2, q2, le)), ds, x, r1, Dec.env.of(r1, x), hs, Core.VClo{env8, p8, b8} <> r2, U, h2, inv)
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VFun{f8, as8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VFun{f8, as8} <> r2, x}))
                                                Look(~prim, p2, 1n+(1n+q2), RP.Le.succ(p2, 1n+q2, RP.Le.succ(p2, q2, le)), ds, x, r1, Dec.env.of(r1, x), hs, Core.VFun{f8, as8} <> r2, U, h2, inv)
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VTrm{t8}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VTrm{t8} <> r2, x}))
                                                Look(~prim, p2, 1n+(1n+q2), RP.Le.succ(p2, 1n+q2, RP.Le.succ(p2, q2, le)), ds, x, r1, Dec.env.of(r1, x), hs, Core.VTrm{t8} <> r2, U, h2, inv)
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                      case Core.VBnd{z2, w2}:
                                        match h:
                                          case Inl{dd}:
                                            match dd:
                                              case (a, h2):
                                                %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VBnd{z2, w2} <> r2, x}))
                                                Look(~prim, p2, 1n+(1n+q2), RP.Le.succ(p2, 1n+q2, RP.Le.succ(p2, q2, le)), ds, x, r1, Dec.env.of(r1, x), hs, Core.VBnd{z2, w2} <> r2, U, h2, inv)
                                          case Inr{kk}:
                                            match kk:
                                              case (vb, h2):
                                                match vb:
                                                  case (ez, vw):
                                                    %ez : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{String.eq(z, x), w, r1, x}), U, Core.run(~prim, 1n+(1n+q2), Core.Defs.dead(ds), Core.SLook{Core.VBnd{_, w2} <> r2, x}))
                                                    %eu : Law.RRel(Core.run(~prim, 1n+p2, ds, Core.SLook2{_, w, r1, x}), U, Core.run(~prim, 1n+q2, Core.Defs.dead(ds), Core.SLook2{_, w2, r2, x}))
                                                    Look(~prim, p2, q2, le, ds, x, r1, Dec.env.of(r1, x), z <> hs, r2, U, h2, Inv.step(z, x, hs, eu, inv))
                        case Core.VLit{l9}:
                          match e2:
                            case Nil{}:
                              match h:
                            case y <> r2:
                              match y:
                                case Core.VLit{l8}:
                                  match h:
                                    case (vb, h2):
                                      Look(~prim, 1n+p2, 1n+q2, le, ds, x, r1, Dec.env.of(r1, x), hs, r2, U, h2, inv)
                                case Core.VCtr{k8, fs8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VClo{env8, p8, b8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VFun{f8, as8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VTrm{t8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VBnd{x8, w8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                        case Core.VCtr{k9, fs9}:
                          match e2:
                            case Nil{}:
                              match h:
                            case y <> r2:
                              match y:
                                case Core.VLit{l8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VCtr{k8, fs8}:
                                  match h:
                                    case (vb, h2):
                                      Look(~prim, 1n+p2, 1n+q2, le, ds, x, r1, Dec.env.of(r1, x), hs, r2, U, h2, inv)
                                case Core.VClo{env8, p8, b8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VFun{f8, as8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VTrm{t8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VBnd{x8, w8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                        case Core.VClo{env9, p9, b9}:
                          match e2:
                            case Nil{}:
                              match h:
                            case y <> r2:
                              match y:
                                case Core.VLit{l8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VCtr{k8, fs8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VClo{env8, p8, b8}:
                                  match h:
                                    case (vb, h2):
                                      Look(~prim, 1n+p2, 1n+q2, le, ds, x, r1, Dec.env.of(r1, x), hs, r2, U, h2, inv)
                                case Core.VFun{f8, as8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VTrm{t8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VBnd{x8, w8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                        case Core.VFun{f9, as9}:
                          match e2:
                            case Nil{}:
                              match h:
                            case y <> r2:
                              match y:
                                case Core.VLit{l8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VCtr{k8, fs8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VClo{env8, p8, b8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VFun{f8, as8}:
                                  match h:
                                    case (vb, h2):
                                      Look(~prim, 1n+p2, 1n+q2, le, ds, x, r1, Dec.env.of(r1, x), hs, r2, U, h2, inv)
                                case Core.VTrm{t8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VBnd{x8, w8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                        case Core.VTrm{t9}:
                          match e2:
                            case Nil{}:
                              match h:
                            case y <> r2:
                              match y:
                                case Core.VLit{l8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VCtr{k8, fs8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VClo{env8, p8, b8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VFun{f8, as8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:
                                case Core.VTrm{t8}:
                                  match h:
                                    case (vb, h2):
                                      Look(~prim, 1n+p2, 1n+q2, le, ds, x, r1, Dec.env.of(r1, x), hs, r2, U, h2, inv)
                                case Core.VBnd{x8, w8}:
                                  match h:
                                    case (vb, h2):
                                      match vb:

# The induction
# =============

def Tr.pick(-u: Bool, -c: Bool, e: {u == c : Bool}, -x: String, -v: Core.Tm, -b: Core.Tm, -e1: List<&2, Core.Val>,
    -hs: List<&2, String>, -e2: List<&2, Core.Val>, h: Law.ERel(e1, Law.Lk(Core.Dead.pick(u, x, v, b)), hs, e2))
    -> Law.ERel(e1, Law.Lk(Core.Dead.pick(c, x, v, b)), hs, e2):
  %e : Law.ERel(e1, Law.Lk(Core.Dead.pick(_, x, v, b)), hs, e2)
  h

# From related states, related results (dead_ok): one case per step of
# `run`, the source's fuel going down. At a dead let the source runs the
# value and binds it (Stut) while the other program stays at the let's
# body, with the fuel it had. d: whether a let's variable is used.
def L.dead(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(vs1, vs2) -> Law.PRel(prim(op, vs1), prim(op, vs2)),
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, s1: Core.Sel, d: Dec.sel(s1), s2: Core.Sel,
    -U: List<&2, String> -> String -> Bool, rel: Law.SRel(s1, U, s2))
    -> Law.RRel(Core.run(~prim, n, ds, s1), U, Core.run(~prim, m, Core.Defs.dead(ds), s2)):
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
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CVar{x0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SLook{e1, x0}, Unit{}, Core.SLook{e2, x0}, U, (e2, {==}, h))
                case Core.CCall{+f0, +as0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f0, as0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      %D.call(f0, as0) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCall{f0, as0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SEval{e2, _}))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{e1, as0}), Core.KCall{f0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SArgs{e2, Core.Args.dead(as0)}), Core.KCall{f0}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SArgs{e2, Core.Args.dead(as0)}), Core.KCall{f0}, {==}, {==},
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SArgs{e1, as0}, Unit{}, Core.SArgs{e2, Core.Args.dead(as0)}, Law.Lk(Core.CBox{}), (e2, f0, {==}, Tr.lk(Core.Tm.dead(Core.CCall{f0, as0}), Core.CCall{f0, Core.Args.dead(as0)}, Tm.sym(Core.CCall{f0, Core.Args.dead(as0)}, Core.Tm.dead(Core.CCall{f0, as0}), D.call(f0, as0)), e1, Nil{}, e2, h))))})
                case Core.CApp{+f0, +as0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CApp{f0, as0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      %D.app(f0, as0) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CApp{f0, as0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SEval{e2, _}))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, f0 <> as0}), Core.KApp{}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tm.dead(f0) <> Core.Tms.dead(as0)}), Core.KApp{}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tm.dead(f0) <> Core.Tms.dead(as0)}), Core.KApp{}, {==}, {==},
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, f0 <> as0}, Unit{}, Core.SEvals{e2, Core.Tm.dead(f0) <> Core.Tms.dead(as0)}, Law.Lk(Core.CBox{}), (e2, Law.WHead{}, {==}, Tr.lk(Core.Tm.dead(Core.CApp{f0, as0}), Core.CApp{Core.Tm.dead(f0), Core.Tms.dead(as0)}, Tm.sym(Core.CApp{Core.Tm.dead(f0), Core.Tms.dead(as0)}, Core.Tm.dead(Core.CApp{f0, as0}), D.app(f0, as0)), e1, Nil{}, e2, h))))})
                case Core.CCtr{+k0, +as0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCtr{k0, as0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      %D.ctr(k0, as0) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCtr{k0, as0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SEval{e2, _}))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, as0}), Core.KCtr{k0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tms.dead(as0)}), Core.KCtr{k0}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tms.dead(as0)}), Core.KCtr{k0}, {==}, {==},
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, as0}, Unit{}, Core.SEvals{e2, Core.Tms.dead(as0)}, Law.Lk(Core.CBox{}), (e2, Law.WCtr{k0}, {==}, Tr.lk(Core.Tm.dead(Core.CCtr{k0, as0}), Core.CCtr{k0, Core.Tms.dead(as0)}, Tm.sym(Core.CCtr{k0, Core.Tms.dead(as0)}, Core.Tm.dead(Core.CCtr{k0, as0}), D.ctr(k0, as0)), e1, Nil{}, e2, h))))})
                case Core.CLam{+p0, +b0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLam{p0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e1, p0, b0}}}, Unit{}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, p0, Core.Tm.dead(b0)}}}, U, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VClo{e2, p0, Core.Tm.dead(b0)}}, {==}, (Core.VClo{e2, p0, Core.Tm.dead(b0)}, {==}, ({==}, {==}, h)), Unit{})})
                case Core.CLet{p0, +v0, +b0}:
                  match p0:
                    case Core.PtVar{+x9}:
                      match d:
                        case Inl{+eu}:
                          match rel:
                            case (+e2, eq, +h):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              %eu : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SEval{e2, Core.Dead.pick(_, x9, Core.Tm.dead(v0), Core.Tm.dead(b0))}))
                              L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.dead(b0)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtVar{x9}, Core.Tm.dead(b0)}, {==}, (e2, {==}, Conv.let.r(Core.PtVar{x9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, Tr.pick(Core.Dead.used(Core.Tm.dead(b0), Nil{}, x9), True{}, Bool.sym(True{}, Core.Dead.used(Core.Tm.dead(b0), Nil{}, x9), eu), x9, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h))),
                                L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Dec.tm.of(v0), Core.SEval{e2, Core.Tm.dead(v0)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.let.l(Core.PtVar{x9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, Tr.pick(Core.Dead.used(Core.Tm.dead(b0), Nil{}, x9), True{}, Bool.sym(True{}, Core.Dead.used(Core.Tm.dead(b0), Nil{}, x9), eu), x9, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h)))))})
                        case Inr{+eu}:
                          match rel:
                            case (+e2, eq, +h):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              %eu : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtVar{x9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SEval{e2, Core.Dead.pick(_, x9, Core.Tm.dead(v0), Core.Tm.dead(b0))}))
                              L.dead(~prim, ~ok, p, 1n+q, RP.Le.succ(p, q, le), ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtVar{x9}, b0}}, Unit{}, Core.SEval{e2, Core.Tm.dead(b0)}, U, Inr{(e2, {==}, Tr.pick(Core.Dead.used(Core.Tm.dead(b0), Nil{}, x9), False{}, Bool.sym(False{}, Core.Dead.used(Core.Tm.dead(b0), Nil{}, x9), eu), x9, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h), Fls.of(Core.Dead.used(Core.Tm.dead(b0), Nil{}, x9), eu))})
                    case Core.PtCtr{+k9, +qs9}:
                      match rel:
                        case (+e2, eq, +h):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtCtr{k9, qs9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtCtr{k9, qs9}, b0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtCtr{k9, qs9}, Core.Tm.dead(b0)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtCtr{k9, qs9}, Core.Tm.dead(b0)}, {==}, (e2, {==}, Conv.let.r(Core.PtCtr{k9, qs9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h)),
                            L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Dec.tm.of(v0), Core.SEval{e2, Core.Tm.dead(v0)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.let.l(Core.PtCtr{k9, qs9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h))))})
                    case Core.PtNat{+n9}:
                      match rel:
                        case (+e2, eq, +h):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtNat{n9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtNat{n9}, b0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtNat{n9}, Core.Tm.dead(b0)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtNat{n9}, Core.Tm.dead(b0)}, {==}, (e2, {==}, Conv.let.r(Core.PtNat{n9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h)),
                            L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Dec.tm.of(v0), Core.SEval{e2, Core.Tm.dead(v0)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.let.l(Core.PtNat{n9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h))))})
                    case Core.PtSuc{+k9, +q9}:
                      match rel:
                        case (+e2, eq, +h):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtSuc{k9, q9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtSuc{k9, q9}, b0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtSuc{k9, q9}, Core.Tm.dead(b0)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtSuc{k9, q9}, Core.Tm.dead(b0)}, {==}, (e2, {==}, Conv.let.r(Core.PtSuc{k9, q9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h)),
                            L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Dec.tm.of(v0), Core.SEval{e2, Core.Tm.dead(v0)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.let.l(Core.PtSuc{k9, q9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h))))})
                    case Core.PtNum{+n9}:
                      match rel:
                        case (+e2, eq, +h):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtNum{n9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtNum{n9}, b0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtNum{n9}, Core.Tm.dead(b0)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtNum{n9}, Core.Tm.dead(b0)}, {==}, (e2, {==}, Conv.let.r(Core.PtNum{n9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h)),
                            L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Dec.tm.of(v0), Core.SEval{e2, Core.Tm.dead(v0)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.let.l(Core.PtNum{n9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h))))})
                    case Core.PtFlt{+s9}:
                      match rel:
                        case (+e2, eq, +h):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLet{Core.PtFlt{s9}, v0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, v0}), Core.KLet{e1, Core.PtFlt{s9}, b0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtFlt{s9}, Core.Tm.dead(b0)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(v0)}), Core.KLet{e2, Core.PtFlt{s9}, Core.Tm.dead(b0)}, {==}, (e2, {==}, Conv.let.r(Core.PtFlt{s9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h)),
                            L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, v0}, Dec.tm.of(v0), Core.SEval{e2, Core.Tm.dead(v0)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.let.l(Core.PtFlt{s9}, Core.Tm.dead(v0), Core.Tm.dead(b0), e1, Nil{}, e2, h))))})
                case Core.CMat{+scrs0, +cases0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CMat{scrs0, cases0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      %D.mat(scrs0, cases0) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CMat{scrs0, cases0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SEval{e2, _}))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, scrs0}), Core.KMat{e1, cases0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tms.dead(scrs0)}), Core.KMat{e2, Core.Tms.dead(cases0)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tms.dead(scrs0)}), Core.KMat{e2, Core.Tms.dead(cases0)}, {==}, (e2, {==}, Conv.skip(Core.Tms.dead(scrs0), Core.Tms.dead(cases0), e1, Nil{}, e2, Tr.lk(Core.Tm.dead(Core.CMat{scrs0, cases0}), Core.CMat{Core.Tms.dead(scrs0), Core.Tms.dead(cases0)}, Tm.sym(Core.CMat{Core.Tms.dead(scrs0), Core.Tms.dead(cases0)}, Core.Tm.dead(Core.CMat{scrs0, cases0}), D.mat(scrs0, cases0)), e1, Nil{}, e2, h))),
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, scrs0}, Unit{}, Core.SEvals{e2, Core.Tms.dead(scrs0)}, Law.Lk(Core.CBox{}), (e2, Law.WMat{Core.Tms.dead(cases0)}, {==}, Tr.lk(Core.Tm.dead(Core.CMat{scrs0, cases0}), Core.CMat{Core.Tms.dead(scrs0), Core.Tms.dead(cases0)}, Tm.sym(Core.CMat{Core.Tms.dead(scrs0), Core.Tms.dead(cases0)}, Core.Tm.dead(Core.CMat{scrs0, cases0}), D.mat(scrs0, cases0)), e1, Nil{}, e2, h))))})
                case Core.CCse{+ps0, +b0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CCse{ps0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, Unit{}, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, U, Inl{(Core.RFail{"a case outside a match"}, Core.KApp{}, {==}, {==}, Unit{})})
                case Core.CSuc{+k0, +e0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CSuc{k0, e0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e0}), Core.KSuc{k0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(e0)}), Core.KSuc{k0}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(e0)}), Core.KSuc{k0}, {==}, {==},
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e0}, Dec.tm.of(e0), Core.SEval{e2, Core.Tm.dead(e0)}, Law.Lk(Core.CBox{}), (e2, {==}, h)))})
                case Core.COp{+op0, +a0, +b0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.COp{op0, a0, b0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{e1, [a0, b0]}), Core.KOp{op0}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, [Core.Tm.dead(a0), Core.Tm.dead(b0)]}), Core.KOp{op0}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, [Core.Tm.dead(a0), Core.Tm.dead(b0)]}), Core.KOp{op0}, {==}, {==},
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SEvals{e1, [a0, b0]}, Unit{}, Core.SEvals{e2, [Core.Tm.dead(a0), Core.Tm.dead(b0)]}, Law.Lk(Core.CBox{}), (e2, Law.WCtr{""}, {==}, h)))})
                case Core.CAnn{+e0, +ty0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CAnn{e0, ty0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e0}, Dec.tm.of(e0), Core.SEval{e2, Core.Tm.dead(e0)}, U, (e2, {==}, h))
                case Core.CLit{+l0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CLit{l0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l0}}}, Unit{}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l0}}}, U, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VLit{l0}}, {==}, (Core.VLit{l0}, {==}, {==}), Unit{})})
                case Core.CRef{+f0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CRef{f0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SCallDef{f0, Nil{}}, Unit{}, Core.SCallDef{f0, Nil{}}, U, (Nil{}, {==}, Unit{}))
                case Core.CTyp{+n0, +as0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CTyp{n0, as0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Unit{}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, U, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})})
                case Core.CBox{}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CBox{}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, Unit{}, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, U, Inl{(Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}, {==}, (Core.VTrm{Core.CBox{}}, {==}, {==}), Unit{})})
                case Core.CErr{+m0}:
                  match rel:
                    case (+e2, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEval{e1, Core.CErr{m0}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.RFail{m0}, Core.KApp{}}, Unit{}, Core.SThen{Core.RFail{m0}, Core.KApp{}}, U, Inl{(Core.RFail{m0}, Core.KApp{}, {==}, {==}, Unit{})})
            case Core.SEvals{+e1, es}:
              match es:
                case Nil{}:
                  match rel:
                    case (e2, w, eq, h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEvals{e1, Nil{}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      Unit{}
                case +e <> +r:
                  match rel:
                    case (+e2, +w, eq, +h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEvals{e1, e <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KTail{e1, r}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(e)}), Core.KTail{e2, Core.Tms.dead(r)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(e)}), Core.KTail{e2, Core.Tms.dead(r)}, {==}, (e2, Wrap.next(w), {==}, Conv.wrap.r(w, Core.Tm.dead(e), Core.Tms.dead(r), e1, Nil{}, e2, h)),
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e}, Dec.tm.of(e), Core.SEval{e2, Core.Tm.dead(e)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.wrap.l(w, Core.Tm.dead(e), Core.Tms.dead(r), e1, Nil{}, e2, h))))})
            case Core.SArgs{+e1, as}:
              match as:
                case Nil{}:
                  match rel:
                    case (e2, f, eq, h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Nil{}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      Unit{}
                case a <> +r:
                  match a:
                    case Core.Arg{rl, +e}:
                      match rl:
                        case Core.Run{}:
                          match rel:
                            case (+e2, +f, eq, +h):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Core.Arg{Core.Run{}, e} <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, e}), Core.KATail{e1, r}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(e)}), Core.KATail{e2, Core.Args.dead(r)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.Tm.dead(e)}), Core.KATail{e2, Core.Args.dead(r)}, {==}, (e2, f, {==}, Conv.call.r(f, Core.Run{}, Core.Tm.dead(e), Core.Args.dead(r), e1, Nil{}, e2, h)),
                                L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, e}, Dec.tm.of(e), Core.SEval{e2, Core.Tm.dead(e)}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.call.l(f, Core.Run{}, Core.Tm.dead(e), Core.Args.dead(r), e1, Nil{}, e2, h))))})
                        case Core.Era{}:
                          match rel:
                            case (+e2, +f, eq, +h):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SArgs{e1, Core.Arg{Core.Era{}, e} <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{e1, Core.CBox{}}), Core.KATail{e1, r}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.CBox{}}), Core.KATail{e2, Core.Args.dead(r)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{e2, Core.CBox{}}), Core.KATail{e2, Core.Args.dead(r)}, {==}, (e2, f, {==}, Conv.call.r(f, Core.Era{}, Core.Tm.dead(e), Core.Args.dead(r), e1, Nil{}, e2, h)),
                                L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{e1, Core.CBox{}}, Dec.tm.of(Core.CBox{}), Core.SEval{e2, Core.CBox{}}, Law.Lk(Core.CBox{}), (e2, {==}, Conv.box(Law.Lk(Core.CCall{f, Core.Arg{Core.Era{}, Core.Tm.dead(e)} <> Core.Args.dead(r)}), e1, Nil{}, e2, h))))})
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
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCall{f1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCall{f1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KApp{}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KApp{}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KApp{}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KCtr{+k1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCtr{k1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCtr{k1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
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
                                        case (+k2, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtVar{x}, b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                                case (+e2, eq, h, u):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtVar{x}, b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                  L.dead(~prim, ~ok, p, 1n+q, RP.Le.succ(p, q, le), ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, ov1}, Unit{}, Core.SEval{e2, Core.Tm.dead(b1)}, U, Inr{(e2, {==}, h, u)})
                        case Core.PtCtr{+k9, +qs9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                        case Core.PtNat{+n9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtNat{n9}, b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtNat{n9}, b1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                        case Core.PtSuc{+k9, +q9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtSuc{k9, q9}, b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtSuc{k9, q9}, b1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                        case Core.PtNum{+n9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtNum{n9}, b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtNum{n9}, b1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                        case Core.PtFlt{+s9}:
                          match rel:
                            case Inl{c}:
                              match c:
                                case (r2, tla):
                                  match r2:
                                    case Core.ROk{+vs2}:
                                      match tla:
                                        case (+k2, eq, kr, rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KLet{env1, Core.PtFlt{s9}, b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KLet{env1, Core.PtFlt{s9}, b1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                    case Core.REnv{env2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RNo{}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                                    case Core.RFail{msg2}:
                                      match tla:
                                        case (k2, eq, kr, rr):
                                          match rr:
                            case Inr{st}:
                              match st:
                    case Core.KBind{+b1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KBind{b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KBind{b1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KMat{+env1, +cases1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KMat{env1, cases1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KMat{env1, cases1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KCase{+env1, +vs1, +b1, +rest1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCase{env1, vs1, b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCase{env1, vs1, b1, rest1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KSuc{+k1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KSuc{k1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KSuc{k1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KOp{+op1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KOp{op1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KOp{op1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KTail{+env1, +es1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KTail{env1, es1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KTail{env1, es1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KATail{+env1, +as1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KATail{env1, as1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KATail{env1, as1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KCons{+v1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KCons{v1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KCons{v1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KApply{+vs1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KApply{vs1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KApply{vs1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                    case Core.KBody{+b1, +rest1}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (r2, tla):
                              match r2:
                                case Core.ROk{+vs2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.ROk{ov1}, Core.KBody{b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SOk{Core.KBody{b1, rest1}, ov1}, Unit{}, Core.SOk{k2, vs2}, U, Inl{(k2, vs2, {==}, kr, rr)})
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
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
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.REnv{+env2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBind{b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBind{b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SThen{Core.REnv{env2}, _}))
                                      L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{oe1, b1}, Dec.tm.of(b1), Core.SEval{env2, Core.Tm.dead(b1)}, U, (env2, {==}, rr))
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
                            case (+e2, eq, h):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBind{b1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              L.dead(~prim, ~ok, p, 1n+q, RP.Le.succ(p, q, le), ds, Core.SEval{oe1, b1}, Dec.tm.of(b1), Core.SEval{e2, Core.Tm.dead(b1)}, U, (e2, {==}, h))
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
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.REnv{+env2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      match kr:
                                        case (+e2, +kvs2, eqk, vr, h):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KCase{env1, vs1, b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KCase{env1, vs1, b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SThen{Core.REnv{env2}, _}))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{oe1, b1}, Dec.tm.of(b1), Core.SEval{env2, Core.Tm.dead(b1)}, U, (env2, {==}, rr))
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
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
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.REnv{+env2}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      match kr:
                                        case (+rr2, eqk, vrs):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBody{b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.REnv{oe1}, Core.KBody{b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SThen{Core.REnv{env2}, _}))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{oe1, b1}), Core.KApply{rest1}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{env2, Core.Tm.dead(b1)}), Core.KApply{rr2}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{env2, Core.Tm.dead(b1)}), Core.KApply{rr2}, {==}, (rr2, {==}, vrs),
                                            L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{oe1, b1}, Dec.tm.of(b1), Core.SEval{env2, Core.Tm.dead(b1)}, Law.Lk(Core.CBox{}), (env2, {==}, rr)))})
                                case Core.RNo{}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
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
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.REnv{env2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                                case Core.RNo{}:
                                  match tla:
                                    case (+k2, eq, kr, rr):
                                      match kr:
                                        case (+e2, +kvs2, eqk, vr, h):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.RNo{}, Core.KCase{env1, vs1, b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SThen{Core.RNo{}, Core.KCase{env1, vs1, b1, rest1}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SThen{Core.RNo{}, _}))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.SMatch{env1, vs1, rest1}, Unit{}, Core.SMatch{e2, kvs2, Core.Tms.dead(rest1)}, U, (e2, kvs2, {==}, vr, h))
                                case Core.RFail{msg2}:
                                  match tla:
                                    case (k2, eq, kr, rr):
                                      match rr:
                        case Inr{st}:
                          match st:
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
                        case (+k2, +vs2, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCall{f1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SCallDef{f1, vs}, Unit{}, Core.SCallDef{f1, vs2}, U, (vs2, {==}, vr))
                    case Inr{st}:
                      match st:
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
                                        case (eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (eq, kr, vr):
                                          match vr:
                                            case (vv, vrest):
                                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApp{}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                              %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApp{}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, v2 <> r2}))
                                              L.dead(~prim, ~ok, p, q, le, ds, Core.SApply{r, v}, Unit{}, Core.SApply{r2, v2}, U, (r2, v2, {==}, vrest, vv))
                        case Inr{st}:
                          match st:
                case Core.KCtr{+k1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCtr{k1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCtr{k1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                          (({==}, vr), Unit{})
                    case Inr{st}:
                      match st:
                case Core.KLet{+env1, p1, +b1}:
                  match p1:
                    case Core.PtVar{+x}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, eq, kr, +vr):
                              match kr:
                                case (+e2, eqk, +h):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtVar{x}], vs}), Core.KBind{b1}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtVar{x}], vs2}), Core.KBind{Core.Tm.dead(b1)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtVar{x}], vs2}), Core.KBind{Core.Tm.dead(b1)}, {==}, {==},
                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtVar{x}], vs}, Unit{}, Core.SPat{e2, [Core.PtVar{x}], vs2}, Law.Lk(Core.Tm.dead(b1)), (e2, vs2, {==}, vr, Shift([Core.PtVar{x}], Core.Tm.dead(b1), env1, Nil{}, e2, h))))})
                        case Inr{st}:
                          match st:
                            case (+e2, eq, +h, +u):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtVar{x}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              L.dead(~prim, ~ok, p, 1n+q, RP.Le.succ(p, q, le), ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtVar{x}], vs}), Core.KBind{b1}}, Unit{}, Core.SEval{e2, Core.Tm.dead(b1)}, U, Inr{Bind.stut(~prim, p, ds, env1, x, vs, b1, e2, h, u)})
                    case Core.PtCtr{+k9, +qs9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, eq, kr, +vr):
                              match kr:
                                case (+e2, eqk, +h):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtCtr{k9, qs9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtCtr{k9, qs9}], vs}), Core.KBind{b1}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtCtr{k9, qs9}], vs2}), Core.KBind{Core.Tm.dead(b1)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtCtr{k9, qs9}], vs2}), Core.KBind{Core.Tm.dead(b1)}, {==}, {==},
                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtCtr{k9, qs9}], vs}, Unit{}, Core.SPat{e2, [Core.PtCtr{k9, qs9}], vs2}, Law.Lk(Core.Tm.dead(b1)), (e2, vs2, {==}, vr, Shift([Core.PtCtr{k9, qs9}], Core.Tm.dead(b1), env1, Nil{}, e2, h))))})
                        case Inr{st}:
                          match st:
                    case Core.PtNat{+n9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, eq, kr, +vr):
                              match kr:
                                case (+e2, eqk, +h):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNat{n9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNat{n9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtNat{n9}], vs}), Core.KBind{b1}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtNat{n9}], vs2}), Core.KBind{Core.Tm.dead(b1)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtNat{n9}], vs2}), Core.KBind{Core.Tm.dead(b1)}, {==}, {==},
                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtNat{n9}], vs}, Unit{}, Core.SPat{e2, [Core.PtNat{n9}], vs2}, Law.Lk(Core.Tm.dead(b1)), (e2, vs2, {==}, vr, Shift([Core.PtNat{n9}], Core.Tm.dead(b1), env1, Nil{}, e2, h))))})
                        case Inr{st}:
                          match st:
                    case Core.PtSuc{+k9, +q9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, eq, kr, +vr):
                              match kr:
                                case (+e2, eqk, +h):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtSuc{k9, q9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtSuc{k9, q9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtSuc{k9, q9}], vs}), Core.KBind{b1}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtSuc{k9, q9}], vs2}), Core.KBind{Core.Tm.dead(b1)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtSuc{k9, q9}], vs2}), Core.KBind{Core.Tm.dead(b1)}, {==}, {==},
                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtSuc{k9, q9}], vs}, Unit{}, Core.SPat{e2, [Core.PtSuc{k9, q9}], vs2}, Law.Lk(Core.Tm.dead(b1)), (e2, vs2, {==}, vr, Shift([Core.PtSuc{k9, q9}], Core.Tm.dead(b1), env1, Nil{}, e2, h))))})
                        case Inr{st}:
                          match st:
                    case Core.PtNum{+n9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, eq, kr, +vr):
                              match kr:
                                case (+e2, eqk, +h):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNum{n9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtNum{n9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtNum{n9}], vs}), Core.KBind{b1}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtNum{n9}], vs2}), Core.KBind{Core.Tm.dead(b1)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtNum{n9}], vs2}), Core.KBind{Core.Tm.dead(b1)}, {==}, {==},
                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtNum{n9}], vs}, Unit{}, Core.SPat{e2, [Core.PtNum{n9}], vs2}, Law.Lk(Core.Tm.dead(b1)), (e2, vs2, {==}, vr, Shift([Core.PtNum{n9}], Core.Tm.dead(b1), env1, Nil{}, e2, h))))})
                        case Inr{st}:
                          match st:
                    case Core.PtFlt{+s9}:
                      match rel:
                        case Inl{c}:
                          match c:
                            case (+k2, +vs2, eq, kr, +vr):
                              match kr:
                                case (+e2, eqk, +h):
                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtFlt{s9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KLet{env1, Core.PtFlt{s9}, b1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env1, [Core.PtFlt{s9}], vs}), Core.KBind{b1}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtFlt{s9}], vs2}), Core.KBind{Core.Tm.dead(b1)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, [Core.PtFlt{s9}], vs2}), Core.KBind{Core.Tm.dead(b1)}, {==}, {==},
                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{env1, [Core.PtFlt{s9}], vs}, Unit{}, Core.SPat{e2, [Core.PtFlt{s9}], vs2}, Law.Lk(Core.Tm.dead(b1)), (e2, vs2, {==}, vr, Shift([Core.PtFlt{s9}], Core.Tm.dead(b1), env1, Nil{}, e2, h))))})
                        case Inr{st}:
                          match st:
                case Core.KBind{+b1}:
                  Unit{}
                case Core.KMat{+env1, +cases1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, eq, kr, +vr):
                          match kr:
                            case (+e2, eqk, h):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KMat{env1, cases1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KMat{env1, cases1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                              L.dead(~prim, ~ok, p, q, le, ds, Core.SMatch{env1, vs, cases1}, Unit{}, Core.SMatch{e2, vs2, Core.Tms.dead(cases1)}, U, (e2, vs2, {==}, vr, h))
                    case Inr{st}:
                      match st:
                case Core.KCase{+env1, +vs1, +b1, +rest1}:
                  Unit{}
                case Core.KSuc{+k1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KSuc{k1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KSuc{k1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                          Prim(prim("%suc", Core.VLit{Core.LNum{k1}} <> vs), prim("%suc", Core.VLit{Core.LNum{k1}} <> vs2), ok("%suc", Core.VLit{Core.LNum{k1}} <> vs, Core.VLit{Core.LNum{k1}} <> vs2, ({==}, vr)), U)
                    case Inr{st}:
                      match st:
                case Core.KOp{+op1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, eq, kr, +vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KOp{op1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          %kr : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KOp{op1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                          Prim(prim(op1, vs), prim(op1, vs2), ok(op1, vs, vs2, vr), U)
                    case Inr{st}:
                      match st:
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
                                        case (eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (eq, kr, vr):
                                          match kr:
                                            case (+e2, +w, eqk, +h):
                                              match vr:
                                                case (vv, vrest):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KTail{env1, es1}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KTail{env1, es1}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, v2 <> r2}))
                                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env1, es1}), Core.KCons{v}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tms.dead(es1)}), Core.KCons{v2}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEvals{e2, Core.Tms.dead(es1)}), Core.KCons{v2}, {==}, (v2, {==}, vv),
                                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SEvals{env1, es1}, Unit{}, Core.SEvals{e2, Core.Tms.dead(es1)}, Law.Lk(Core.CBox{}), (e2, w, {==}, h)))})
                        case Inr{st}:
                          match st:
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
                                        case (eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (eq, kr, vr):
                                          match kr:
                                            case (+e2, +f, eqk, +h):
                                              match vr:
                                                case (vv, vrest):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KATail{env1, as1}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KATail{env1, as1}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, v2 <> r2}))
                                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env1, as1}), Core.KCons{v}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SArgs{e2, Core.Args.dead(as1)}), Core.KCons{v2}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SArgs{e2, Core.Args.dead(as1)}), Core.KCons{v2}, {==}, (v2, {==}, vv),
                                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SArgs{env1, as1}, Unit{}, Core.SArgs{e2, Core.Args.dead(as1)}, Law.Lk(Core.CBox{}), (e2, f, {==}, h)))})
                        case Inr{st}:
                          match st:
                case Core.KCons{+v1}:
                  match rel:
                    case Inl{c}:
                      match c:
                        case (+k2, +vs2, eq, kr, +vr):
                          match kr:
                            case (+v2, eqk, vv):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCons{v1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                              %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KCons{v1}, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, vs2}))
                              (vv, vr)
                    case Inr{st}:
                      match st:
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
                                        case (eq, kr, vr):
                                          match vr:
                                    case +v2 <> +r2:
                                      match tlb:
                                        case (eq, kr, vr):
                                          match kr:
                                            case (+kvs2, eqk, vrs):
                                              match vr:
                                                case (vv, vrest):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApply{vs1}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                                  %eqk : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SOk{Core.KApply{vs1}, v <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SOk{_, v2 <> r2}))
                                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SApply{vs1, v}, Unit{}, Core.SApply{kvs2, v2}, U, (kvs2, v2, {==}, vrs, vv))
                        case Inr{st}:
                          match st:
                case Core.KBody{+b1, +rest1}:
                  Unit{}
            case Core.SLook{+e1, +x}:
              match rel:
                case (+e2, eq, +h):
                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SLook{e1, x}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                  Look(~prim, 1n+p, 1n+q, le, ds, x, e1, Dec.env.of(e1, x), Nil{}, e2, U, h, Unit{})
            case Core.SLook2{hit, +v, +e1, +x}:
              match hit:
                case True{}:
                  match rel:
                    case (v2, e2, eq, vv, h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SLook2{True{}, v, e1, x}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      (vv, Unit{})
                case False{}:
                  match rel:
                    case (v2, +e2, eq, vv, h):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SLook2{False{}, v, e1, x}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SLook{e1, x}, Unit{}, Core.SLook{e2, x}, U, (e2, {==}, h))
            case Core.SCallDef{+f, +vs}:
              match rel:
                case (+vs2, eq, vr):
                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SCallDef{f, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                  L.dead(~prim, ~ok, p, q, le, ds, Core.SFind{ds, f, vs}, Unit{}, Core.SFind{Core.Defs.dead(ds), f, vs2}, U, (vs2, {==}, vr))
            case Core.SFind{ds2, +f, +vs}:
              match ds2:
                case Nil{}:
                  match rel:
                    case (+vs2, eq, vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFind{Nil{}, f, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      Prim(prim(f, vs), prim(f, vs2), ok(f, vs, vs2, vr), U)
                case df <> +dr:
                  match df:
                    case Core.Def{+name, +ps, +b, ret}:
                      match rel:
                        case (+vs2, eq, vr):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFind{Core.Def{name, ps, b, ret} <> dr, f, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SFound{String.eq(name, f), ps, b, dr, f, vs}, Unit{}, Core.SFound{String.eq(name, f), ps, Core.Tm.dead(b), Core.Defs.dead(dr), f, vs2}, U, (vs2, {==}, vr))
            case Core.SFound{hit, +ps, +b, +ds2, +f, +vs}:
              match hit:
                case True{}:
                  match rel:
                    case (+vs2, eq, +vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, b, ds2, f, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      %Len.eq(vs, vs2, vr) : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFound{True{}, ps, b, ds2, f, vs}), U, Core.run(~prim, q, Core.Defs.dead(ds), Core.SEnter{Nat.is_lt(_, Core.Pars.len(ps)), f, ps, Core.Tm.dead(b), vs2}))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, b, vs}, Unit{}, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, Core.Tm.dead(b), vs2}, U, (vs2, {==}, vr))
                case False{}:
                  match rel:
                    case (+vs2, eq, vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SFound{False{}, ps, b, ds2, f, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SFind{ds2, f, vs}, Unit{}, Core.SFind{Core.Defs.dead(ds2), f, vs2}, U, (vs2, {==}, vr))
            case Core.SEnter{short, +f, +ps, +b, +vs}:
              match short:
                case True{}:
                  match rel:
                    case (vs2, eq, vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEnter{True{}, f, ps, b, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      (({==}, vr), Unit{})
                case False{}:
                  match rel:
                    case (+vs2, eq, +vr):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SEnter{False{}, f, ps, b, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), b}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.dead(b)}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs2)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.dead(b)}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs2)}, {==}, (Core.Vals.drop(Core.Pars.len(ps), vs2), {==}, Drop(Core.Pars.len(ps), vs, vs2, vr)),
                        L.dead(~prim, ~ok, p, q, le, ds, Core.SEval{Core.Scope.bind(ps, vs), b}, Dec.tm.of(b), Core.SEval{Core.Scope.bind(ps, vs2), Core.Tm.dead(b)}, Law.Lk(Core.CBox{}), (Core.Scope.bind(ps, vs2), {==}, Bind(ps, vs, vs2, vr, Law.Lk(Core.Tm.dead(b)), Nil{}))))})
            case Core.SApply{vs, +fv}:
              match vs:
                case Nil{}:
                  match rel:
                    case (vs2, tla):
                      match vs2:
                        case Nil{}:
                          match tla:
                            case (fv2, eq, vr, fr):
                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{Nil{}, fv}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
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
                                                case (ep, eb, h):
                                                  %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{ce, cp, cb}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                                  %ep : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{ce, cp, cb}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SApply{v2 <> r2, Core.VClo{ce2, _, cb2}}))
                                                  %eb : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VClo{ce, cp, cb}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SApply{v2 <> r2, Core.VClo{ce2, cp, _}}))
                                                  L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{ce, [cp], [v]}), Core.KBody{cb, r}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{ce2, [cp], [v2]}), Core.KBody{Core.Tm.dead(cb), r2}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{ce2, [cp], [v2]}), Core.KBody{Core.Tm.dead(cb), r2}, {==}, (r2, {==}, vrest),
                                                    L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{ce, [cp], [v]}, Unit{}, Core.SPat{ce2, [cp], [v2]}, Law.Lk(Core.Tm.dead(cb)), (ce2, [v2], {==}, (vv, Unit{}), Shift([cp], Core.Tm.dead(cb), ce, Nil{}, ce2, h))))})
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
                                              %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{fg, fa}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                              %ef : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SApply{v <> r, Core.VFun{fg, fa}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), Core.SApply{v2 <> r2, Core.VFun{_, fa2}}))
                                              L.dead(~prim, ~ok, p, q, le, ds, Core.SCallDef{fg, Core.Vals.cat(fa, v <> r)}, Unit{}, Core.SCallDef{fg, Core.Vals.cat(fa2, v2 <> r2)}, U, (Core.Vals.cat(fa2, v2 <> r2), {==}, Cat(fa, fa2, v <> r, v2 <> r2, far, vr)))
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
                        case (+e2, +vs2, eq, +vr, +h):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SMatch{e1, vs, Core.CCse{ps0, b0} <> r}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SThen{Core.run(~prim, p, ds, Core.SPat{e1, ps0, vs}), Core.KCase{e1, vs, b0, r}}, Unit{}, Core.SThen{Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, ps0, vs2}), Core.KCase{e2, vs2, Core.Tm.dead(b0), Core.Tms.dead(r)}}, U, Inl{(Core.run(~prim, q, Core.Defs.dead(ds), Core.SPat{e2, ps0, vs2}), Core.KCase{e2, vs2, Core.Tm.dead(b0), Core.Tms.dead(r)}, {==}, (e2, vs2, {==}, vr, Conv.cases.r(Core.CCse{ps0, Core.Tm.dead(b0)}, Core.Tms.dead(r), e1, Nil{}, e2, h)),
                            L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{e1, ps0, vs}, Unit{}, Core.SPat{e2, ps0, vs2}, Law.Lk(Core.Tm.dead(b0)), (e2, vs2, {==}, vr, Shift(ps0, Core.Tm.dead(b0), e1, Nil{}, e2, Conv.cases.l(Core.CCse{ps0, Core.Tm.dead(b0)}, Core.Tms.dead(r), e1, Nil{}, e2, h)))))})
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
                        case (e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (eq, vr, h):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, Nil{}, Nil{}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      h
                                case w <> s:
                                  match tlb:
                                    case (eq, vr, h):
                                      match vr:
                    case v <> vt:
                      match rel:
                        case (e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (eq, vr, h):
                                      match vr:
                                case w <> s:
                                  match tlb:
                                    case (eq, vr, h):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, Nil{}, v <> vt}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      Unit{}
                case +pt <> +pr:
                  match vs:
                    case Nil{}:
                      match rel:
                        case (e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (eq, vr, h):
                                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, pt <> pr, Nil{}}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                      Unit{}
                                case w <> s:
                                  match tlb:
                                    case (eq, vr, h):
                                      match vr:
                    case +v <> +vt:
                      match rel:
                        case (+e2, tla):
                          match tla:
                            case (vs2, tlb):
                              match vs2:
                                case Nil{}:
                                  match tlb:
                                    case (eq, vr, +h):
                                      match vr:
                                case +v2 <> +vt2:
                                  match tlb:
                                    case (eq, vr, +h):
                                      match vr:
                                        case (vv, +rr):
                                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPat{e1, pt <> pr, v <> vt}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                                          L.dead(~prim, ~ok, p, q, le, ds, Core.Pat.step(e1, pt, v, pr, vt), Dec.sel.of(Core.Pat.step(e1, pt, v, pr, vt)), Core.Pat.step(e2, pt, v2, pr, vt2), U, Pat.rel(e1, pt, v, pr, vt, e2, v2, vt2, U, vv, rr, h))
            case Core.SPatC{hit, +e1, +ps, +vs}:
              match hit:
                case True{}:
                  match rel:
                    case (+e2, +vs2, eq, pc):
                      match pc:
                        case (vr, h):
                          %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPatC{True{}, e1, ps, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                          L.dead(~prim, ~ok, p, q, le, ds, Core.SPat{e1, ps, vs}, Unit{}, Core.SPat{e2, ps, vs2}, U, (e2, vs2, {==}, vr, h))
                case False{}:
                  match rel:
                    case (e2, vs2, eq, pc):
                      %eq : Law.RRel(Core.run(~prim, 1n+p, ds, Core.SPatC{False{}, e1, ps, vs}), U, Core.run(~prim, 1n+q, Core.Defs.dead(ds), _))
                      Unit{}

# Equality
# ========

# Related values without closures: the second is the first with the pass
# taken.
def Eq.val(v1: Core.Val, v2: Core.Val, vr: Law.VRel(v1, v2), c: Law.NoClo(v1)) -> {Core.Val.dead(v1) == v2 : Core.Val}:
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
                              %Val.sym(Core.Val.dead(Core.VCtr{k, r}), Core.VCtr{k2, r2}, Eq.val(Core.VCtr{k, r}, Core.VCtr{k2, r2}, (ek, vrr), cr)) : {Core.Val.push(Core.Val.dead(f), _) == Core.VCtr{k2, f2 <> r2} : Core.Val}
                              %Val.sym(Core.Val.dead(f), f2, Eq.val(f, f2, vf, cf)) : {Core.VCtr{k2, _ <> r2} == Core.VCtr{k2, f2 <> r2} : Core.Val}
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
                              %Val.sym(Core.Val.dead(Core.VFun{g, r}), Core.VFun{g2, r2}, Eq.val(Core.VFun{g, r}, Core.VFun{g2, r2}, (ek, vrr), cr)) : {Core.Val.push(Core.Val.dead(f), _) == Core.VFun{g2, f2 <> r2} : Core.Val}
                              %Val.sym(Core.Val.dead(f), f2, Eq.val(f, f2, vf, cf)) : {Core.VFun{g2, _ <> r2} == Core.VFun{g2, f2 <> r2} : Core.Val}
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
          %vr : {Core.VTrm{Core.Tm.dead(t)} == Core.VTrm{_} : Core.Val}
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
              %ex : {Core.VBnd{x, Core.Val.dead(w)} == Core.VBnd{_, w2} : Core.Val}
              %Val.sym(Core.Val.dead(w), w2, Eq.val(w, w2, vw, c)) : {Core.VBnd{x, _} == Core.VBnd{x, w2} : Core.Val}
              {==}

def Eq.vals(vs1: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs1, vs2), c: Law.NoClos(vs1))
    -> {Core.Vals.dead(vs1) == vs2 : List<&2, Core.Val>}:
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
                  %Eq.val(v, w, vv, cv) : {Core.Val.dead(v) <> Core.Vals.dead(r) == _ <> s : List<&2, Core.Val>}
                  %Eq.vals(r, s, vrr, cr) : {Core.Val.dead(v) <> Core.Vals.dead(r) == Core.Val.dead(v) <> _ : List<&2, Core.Val>}
                  {==}

# Related results, the first clean: the second is the first with the pass
# taken.
def Eq.res(r1: Core.Res, r2: Core.Res, -U: List<&2, String> -> String -> Bool, rr: Law.RRel(r1, U, r2), c: Law.Clean(r1))
    -> {Core.Res.dead(r1) == r2 : Core.Res}:
  match r1:
    case Core.ROk{+vs1}:
      match r2:
        case Core.ROk{+vs2}:
          %Eq.vals(vs1, vs2, rr, c) : {Core.ROk{Core.Vals.dead(vs1)} == Core.ROk{_} : Core.Res}
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
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, +s1: Core.Sel, s2: Core.Sel,
    -U: List<&2, String> -> String -> Bool, rel: Law.SRel(s1, U, s2))
    -> Law.RRel(Core.run(~prim, n, ds, s1), U, Core.run(~prim, m, Core.Defs.dead(ds), s2)):
  L.dead(~prim, ~ok, n, m, le, ds, s1, Dec.sel.of(s1), s2, U, rel)

def Eq.top(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs1:List<&2, Core.Val> -> @vs2:List<&2, Core.Val> -> Law.VRels(vs1, vs2) -> Law.PRel(prim(op, vs1), prim(op, vs2)),
    +n: Nat, +m: Nat, +le: Red.Le(n, m), +ds: List<&2, Core.Def>, nf: Law.Clean(Core.Prog.run(~prim, n, ds)))
    -> {Core.Res.dead(Core.Prog.run(~prim, n, ds)) == Core.Prog.run(~prim, m, Core.Defs.dead(ds)) : Core.Res}:
  Eq.res(Core.Prog.run(~prim, n, ds), Core.Prog.run(~prim, m, Core.Defs.dead(ds)), Law.Lk(Core.CBox{}),
    L.top(~prim, ~ok, n, m, le, ds, Core.SCallDef{"main", Nil{}}, Core.SCallDef{"main", Nil{}}, Law.Lk(Core.CBox{}), (Nil{}, {==}, Unit{})), nf)

def Law.dead_ok(prim, ok, n, m, le, ds, U, s1, s2, rel):
  L.top(~prim, ~ok, n, m, le, ds, s1, s2, U, rel)

def Law.dead_prog(prim, ok, n, m, le, ds, nf):
  Eq.top(~prim, ~ok, n, m, le, ds, nf)
