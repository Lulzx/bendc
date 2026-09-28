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
def Bind(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, vs2: List<&2, Core.Val>, vr: Law.VRels(vs, vs2),
    -U: List<&2, String> -> String -> Bool, +hs: List<&2, String>)
    -> Law.ERel(Core.Scope.bind(ps, vs), U, hs, Core.Scope.bind(ps, vs2)):
  match ps:
    case Nil{}:
      Unit{}
    case q <> pr:
      match q:
        case Core.Par{+x, rel, mode, ty}:
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
                      Inr{(({==}, a), Bind(pr, r, s, b, U, x <> hs))}

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
