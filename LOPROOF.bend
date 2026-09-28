import Base
import ./core.bend as Core
import ./DEADPROOF.bend as DP
import ./LO.bend as Law

# Proof of LO.bend's laws. The round trip (up_lo) is an induction on the
# term; a list field is lowered as its head and the node with the rest, and
# the Shape lemmas give that node's constructor. The scope laws: Lo.scoped
# (lo_scoped) is an induction on the term too, and L.scope (scope_ok) one
# on the fuel, a case per step of `run`, that each state the run reaches is
# scoped (Good.sel).

# Patterns
# ========

def Pt.sym(-a: Core.Pt, -b: Core.Pt, e: {a == b : Core.Pt}) -> {b == a : Core.Pt}:
  %e : {_ == a : Core.Pt}
  {==}

def Pat.sym(-a: Core.Pat, -b: Core.Pat, e: {a == b : Core.Pat}) -> {b == a : Core.Pat}:
  %e : {_ == a : Core.Pat}
  {==}

# A constructor pattern lowers to one with its fields lowered.
def Pat.lo.ctr(+n: String, ps: List<&2, Core.Pat>)
    -> {Core.PtCtr{n, Core.Lo.pats(ps)} == Core.Lo.pat(Core.PCtor{n, ps}) : Core.Pt}:
  match ps:
    case Nil{}:
      {==}
    case a <> t:
      %Pat.lo.ctr(n, t) : {Core.PtCtr{n, Core.Lo.pat(a) <> Core.Lo.pats(t)} == Core.Lo.pt.push(Core.Lo.pat(a), _) : Core.Pt}
      {==}

def Pat.up.ctr(+n: String, ps: List<&2, Core.Pt>)
    -> {Core.PCtor{n, Core.Up.pats(ps)} == Core.Up.pat(Core.PtCtr{n, ps}) : Core.Pat}:
  match ps:
    case Nil{}:
      {==}
    case a <> t:
      %Pat.up.ctr(n, t) : {Core.PCtor{n, Core.Up.pat(a) <> Core.Up.pats(t)} == Core.Up.pt.push(Core.Up.pat(a), _) : Core.Pat}
      {==}

def Pat.tl(+n: String, +t: List<&2, Core.Pat>, ih: {Core.PCtor{n, t} == Core.Up.pat(Core.Lo.pat(Core.PCtor{n, t})) : Core.Pat})
    -> {Core.PCtor{n, t} == Core.PCtor{n, Core.Up.pats(Core.Lo.pats(t))} : Core.Pat}:
  %Pat.sym(Core.PCtor{n, Core.Up.pats(Core.Lo.pats(t))}, Core.Up.pat(Core.PtCtr{n, Core.Lo.pats(t)}), Pat.up.ctr(n, Core.Lo.pats(t))) : {Core.PCtor{n, t} == _ : Core.Pat}
  %Pt.sym(Core.PtCtr{n, Core.Lo.pats(t)}, Core.Lo.pat(Core.PCtor{n, t}), Pat.lo.ctr(n, t)) : {Core.PCtor{n, t} == Core.Up.pat(_) : Core.Pat}
  ih

# Raising a lowered pattern gives it back.
def Pat.rt(p: Core.Pat) -> {p == Core.Up.pat(Core.Lo.pat(p)) : Core.Pat}:
  match p:
    case Core.PVar{x}:
      {==}
    case Core.PCtor{+n, ps}:
      match ps:
        case Nil{}:
          {==}
        case +a <> +t:
          %Pat.lo.ctr(n, t) : {Core.PCtor{n, a <> t} == Core.Up.pat(Core.Lo.pt.push(Core.Lo.pat(a), _)) : Core.Pat}
          %Pat.up.ctr(n, Core.Lo.pats(t)) : {Core.PCtor{n, a <> t} == Core.Up.pt.push(Core.Up.pat(Core.Lo.pat(a)), _) : Core.Pat}
          %Pat.rt(a) : {Core.PCtor{n, a <> t} == Core.Up.pt.push(_, Core.PCtor{n, Core.Up.pats(Core.Lo.pats(t))}) : Core.Pat}
          %Pat.tl(n, t, Pat.rt(Core.PCtor{n, t})) : {Core.PCtor{n, a <> t} == Core.Up.pt.push(a, _) : Core.Pat}
          {==}
    case Core.PNat{n}:
      {==}
    case Core.PSucc{k, q}:
      %Pat.rt(q) : {Core.PSucc{k, q} == Core.PSucc{k, _} : Core.Pat}
      {==}
    case Core.PNum{n}:
      {==}
    case Core.PFlt{s}:
      {==}

# Terms
# =====

def Tm.sym(-a: Core.Tm, -b: Core.Tm, e: {a == b : Core.Tm}) -> {b == a : Core.Tm}:
  %e : {_ == a : Core.Tm}
  {==}

def Absurd(-A: Data, t: Empty) -> A:
  match t:

def Tru(b: Bool) -> Data:
  match b:
    case True{}:
      Unit
    case False{}:
      Empty

def Tru.of(-b: Bool, h: {True{} == b : Bool}) -> Tru(b):
  %h : Tru(_)
  Unit{}

# E raises back from R, and C is R: E raises back from C.
def Tr(-e: Core.Expr, -c: Core.Tm, -r: Core.Tm, ih: {e == Core.Up.go(r) : Core.Expr}, q: {c == r : Core.Tm})
    -> {e == Core.Up.go(c) : Core.Expr}:
  %Tm.sym(c, r, q) : {e == Core.Up.go(_) : Core.Expr}
  ih

def Pats.rt(ps: List<&2, Core.Pat>) -> {ps == Core.Up.pats(Core.Lo.pats(ps)) : List<&2, Core.Pat>}:
  match ps:
    case Nil{}:
      {==}
    case +p <> +r:
      %Pat.rt(p) : {p <> r == _ <> Core.Up.pats(Core.Lo.pats(r)) : List<&2, Core.Pat>}
      %Pats.rt(r) : {p <> r == p <> _ : List<&2, Core.Pat>}
      {==}

# A call of a global lowers to a call of its name.
def Glob.var(f: Core.Expr, +bound: List<&2, String>, he: {True{} == Core.Lo.global(bound, f) : Bool})
    -> {f == Core.EVar{Core.Lo.fname(f)} : Core.Expr}:
  match f:
    case Core.EVar{n9}:
      {==}
    case Core.ENum{n9}:
      Absurd({Core.ENum{n9} == Core.EVar{Core.Lo.fname(Core.ENum{n9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ENat{n9}:
      Absurd({Core.ENat{n9} == Core.EVar{Core.Lo.fname(Core.ENat{n9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.EFlt{s9}:
      Absurd({Core.EFlt{s9} == Core.EVar{Core.Lo.fname(Core.EFlt{s9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.EStr{s9}:
      Absurd({Core.EStr{s9} == Core.EVar{Core.Lo.fname(Core.EStr{s9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ECall{f9, args9}:
      Absurd({Core.ECall{f9, args9} == Core.EVar{Core.Lo.fname(Core.ECall{f9, args9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ECtor{n9, args9}:
      Absurd({Core.ECtor{n9, args9} == Core.EVar{Core.Lo.fname(Core.ECtor{n9, args9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ELam{p9, b9}:
      Absurd({Core.ELam{p9, b9} == Core.EVar{Core.Lo.fname(Core.ELam{p9, b9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ELet{p9, v9, b9}:
      Absurd({Core.ELet{p9, v9, b9} == Core.EVar{Core.Lo.fname(Core.ELet{p9, v9, b9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.EMatch{scrs9, cases9}:
      Absurd({Core.EMatch{scrs9, cases9} == Core.EVar{Core.Lo.fname(Core.EMatch{scrs9, cases9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ECase{ps9, b9}:
      Absurd({Core.ECase{ps9, b9} == Core.EVar{Core.Lo.fname(Core.ECase{ps9, b9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ESucc{k9, e9}:
      Absurd({Core.ESucc{k9, e9} == Core.EVar{Core.Lo.fname(Core.ESucc{k9, e9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.EOp{op9, a9, b9}:
      Absurd({Core.EOp{op9, a9, b9} == Core.EVar{Core.Lo.fname(Core.EOp{op9, a9, b9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.EAnn{e9, ty9}:
      Absurd({Core.EAnn{e9, ty9} == Core.EVar{Core.Lo.fname(Core.EAnn{e9, ty9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.ETy{n9, args9}:
      Absurd({Core.ETy{n9, args9} == Core.EVar{Core.Lo.fname(Core.ETy{n9, args9})} : Core.Expr}, Tru.of(False{}, he))
    case Core.EErr{m9}:
      Absurd({Core.EErr{m9} == Core.EVar{Core.Lo.fname(Core.EErr{m9})} : Core.Expr}, Tru.of(False{}, he))

# The shapes of lowered list nodes
# ================================

def Shape.g0(+f: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>, he: {True{} == Core.Lo.global(bound, f) : Bool})
    -> {Core.CCall{Core.Lo.fname(f), Nil{}} == Core.Lo.go(Core.ECall{f, Nil{}}, ms, bound, top, mask) : Core.Tm}:
  %he : {Core.CCall{Core.Lo.fname(f), Nil{}} == Bool.pick(Unit -> Core.Tm, _, u => Core.CCall{Core.Lo.fname(f), Nil{}}, u => Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Nil{}})(Unit{}) : Core.Tm}
  {==}

def Shape.g1(+f: Core.Expr, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    -as: List<&2, Core.Arg>, he: {True{} == Core.Lo.global(bound, f) : Bool},
    q: {Core.CCall{Core.Lo.fname(f), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))) : Core.Tm})
    -> {Core.CCall{Core.Lo.fname(f), Core.Arg{Core.Lo.rel(Core.Lo.mask(top, ms, f, mask)), Core.Lo.go(b, ms, bound, True{}, Nil{})} <> as} == Core.Lo.go(Core.ECall{f, b <> t}, ms, bound, top, mask) : Core.Tm}:
  %he : {Core.CCall{Core.Lo.fname(f), Core.Arg{Core.Lo.rel(Core.Lo.mask(top, ms, f, mask)), Core.Lo.go(b, ms, bound, True{}, Nil{})} <> as} == Bool.pick(Unit -> Core.Tm, _, u => Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)))), u => Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{})))(Unit{}) : Core.Tm}
  %q : {Core.CCall{Core.Lo.fname(f), Core.Arg{Core.Lo.rel(Core.Lo.mask(top, ms, f, mask)), Core.Lo.go(b, ms, bound, True{}, Nil{})} <> as} == Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(b, ms, bound, True{}, Nil{}), _) : Core.Tm}
  {==}

def Shape.g2(+f: Core.Expr, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    he: {True{} == Core.Lo.global(bound, f) : Bool},
    sh: Sigma<&2, &2, List<&2, Core.Arg>, as => {Core.CCall{Core.Lo.fname(f), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))) : Core.Tm}>)
    -> Sigma<&2, &2, List<&2, Core.Arg>, as => {Core.CCall{Core.Lo.fname(f), as} == Core.Lo.go(Core.ECall{f, b <> t}, ms, bound, top, mask) : Core.Tm}>:
  match sh:
    case (as, q):
      (Core.Arg{Core.Lo.rel(Core.Lo.mask(top, ms, f, mask)), Core.Lo.go(b, ms, bound, True{}, Nil{})} <> as, Shape.g1(f, b, t, ms, bound, top, mask, as, he, q))

def Shape.g(t: List<&2, Core.Expr>, +f: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    +he: {True{} == Core.Lo.global(bound, f) : Bool})
    -> Sigma<&2, &2, List<&2, Core.Arg>, as => {Core.CCall{Core.Lo.fname(f), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, top, mask) : Core.Tm}>:
  match t:
    case Nil{}:
      (Nil{}, Shape.g0(f, ms, bound, top, mask, he))
    case +b <> +t2:
      Shape.g2(f, b, t2, ms, bound, top, mask, he, Shape.g(t2, f, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)), he))

def Shape.n0(+f: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>, he: {False{} == Core.Lo.global(bound, f) : Bool})
    -> {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Nil{}} == Core.Lo.go(Core.ECall{f, Nil{}}, ms, bound, top, mask) : Core.Tm}:
  %he : {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Nil{}} == Bool.pick(Unit -> Core.Tm, _, u => Core.CCall{Core.Lo.fname(f), Nil{}}, u => Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Nil{}})(Unit{}) : Core.Tm}
  {==}

def Shape.n1(+f: Core.Expr, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    -as: List<&2, Core.Tm>, he: {False{} == Core.Lo.global(bound, f) : Bool},
    q: {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}) : Core.Tm})
    -> {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as} == Core.Lo.go(Core.ECall{f, b <> t}, ms, bound, top, mask) : Core.Tm}:
  %he : {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as} == Bool.pick(Unit -> Core.Tm, _, u => Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)))), u => Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{})))(Unit{}) : Core.Tm}
  %q : {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as} == Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), _) : Core.Tm}
  {==}

def Shape.n2(+f: Core.Expr, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    he: {False{} == Core.Lo.global(bound, f) : Bool},
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as} == Core.Lo.go(Core.ECall{f, b <> t}, ms, bound, top, mask) : Core.Tm}>:
  match sh:
    case (as, q):
      (Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as, Shape.n1(f, b, t, ms, bound, top, mask, as, he, q))

def Shape.n(t: List<&2, Core.Expr>, +f: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    +he: {False{} == Core.Lo.global(bound, f) : Bool})
    -> Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, top, mask) : Core.Tm}>:
  match t:
    case Nil{}:
      (Nil{}, Shape.n0(f, ms, bound, top, mask, he))
    case +b <> +t2:
      Shape.n2(f, b, t2, ms, bound, top, mask, he, Shape.n(t2, f, ms, bound, False{}, Nil{}, he))

def Shape.ctr1(+n: String, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, -as: List<&2, Core.Tm>,
    q: {Core.CCtr{n, as} == Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}) : Core.Tm})
    -> {Core.CCtr{n, Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as} == Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{})) : Core.Tm}:
  %q : {Core.CCtr{n, Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as} == Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), _) : Core.Tm}
  {==}

def Shape.ctr2(+n: String, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CCtr{n, as} == Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CCtr{n, as} == Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{})) : Core.Tm}>:
  match sh:
    case (as, q):
      (Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as, Shape.ctr1(n, b, t, ms, bound, as, q))

def Shape.ctr(t: List<&2, Core.Expr>, +n: String, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CCtr{n, as} == Core.Lo.go(Core.ECtor{n, t}, ms, bound, top, mask) : Core.Tm}>:
  match t:
    case Nil{}:
      (Nil{}, {==})
    case +b <> +t2:
      Shape.ctr2(n, b, t2, ms, bound, Shape.ctr(t2, n, ms, bound, False{}, Nil{}))

def Shape.ty1(+n: String, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, -as: List<&2, Core.Tm>,
    q: {Core.CTyp{n, as} == Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{}) : Core.Tm})
    -> {Core.CTyp{n, Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as} == Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{})) : Core.Tm}:
  %q : {Core.CTyp{n, Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as} == Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), _) : Core.Tm}
  {==}

def Shape.ty2(+n: String, +b: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CTyp{n, as} == Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CTyp{n, as} == Core.Tm.push(Core.Lo.go(b, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{})) : Core.Tm}>:
  match sh:
    case (as, q):
      (Core.Lo.go(b, ms, bound, True{}, Nil{}) <> as, Shape.ty1(n, b, t, ms, bound, as, q))

def Shape.ty(t: List<&2, Core.Expr>, +n: String, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CTyp{n, as} == Core.Lo.go(Core.ETy{n, t}, ms, bound, top, mask) : Core.Tm}>:
  match t:
    case Nil{}:
      (Nil{}, {==})
    case +b <> +t2:
      Shape.ty2(n, b, t2, ms, bound, Shape.ty(t2, n, ms, bound, False{}, Nil{}))

def Shape.cs1(+c: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, -xs: List<&2, Core.Tm>,
    q: {Core.CMat{Nil{}, xs} == Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}) : Core.Tm})
    -> {Core.CMat{Nil{}, Core.Lo.go(c, ms, bound, True{}, Nil{}) <> xs} == Core.Tm.push.case(Core.Lo.go(c, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{})) : Core.Tm}:
  %q : {Core.CMat{Nil{}, Core.Lo.go(c, ms, bound, True{}, Nil{}) <> xs} == Core.Tm.push.case(Core.Lo.go(c, ms, bound, True{}, Nil{}), _) : Core.Tm}
  {==}

def Shape.cs2(+c: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sh: Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{Nil{}, xs} == Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{Nil{}, xs} == Core.Tm.push.case(Core.Lo.go(c, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{})) : Core.Tm}>:
  match sh:
    case (xs, q):
      (Core.Lo.go(c, ms, bound, True{}, Nil{}) <> xs, Shape.cs1(c, t, ms, bound, xs, q))

def Shape.cs(t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{Nil{}, xs} == Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, top, mask) : Core.Tm}>:
  match t:
    case Nil{}:
      (Nil{}, {==})
    case +c <> +t2:
      Shape.cs2(c, t2, ms, bound, Shape.cs(t2, ms, bound, False{}, Nil{}))

def Shape.ss1(+a: Core.Expr, +t: List<&2, Core.Expr>, +cs: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, -ys: List<&2, Core.Tm>, -xs: List<&2, Core.Tm>,
    q: {Core.CMat{ys, xs} == Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}) : Core.Tm})
    -> {Core.CMat{Core.Lo.go(a, ms, bound, True{}, Nil{}) <> ys, xs} == Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{})) : Core.Tm}:
  %q : {Core.CMat{Core.Lo.go(a, ms, bound, True{}, Nil{}) <> ys, xs} == Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _) : Core.Tm}
  {==}

def Shape.ss2(+a: Core.Expr, +t: List<&2, Core.Expr>, +cs: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sh: Sigma<&2, &2, List<&2, Core.Tm>, ys => Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{ys, xs} == Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}) : Core.Tm}>>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, ys => Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{ys, xs} == Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{})) : Core.Tm}>>:
  match sh:
    case (ys, r):
      match r:
        case (xs, q):
          (Core.Lo.go(a, ms, bound, True{}, Nil{}) <> ys, (xs, Shape.ss1(a, t, cs, ms, bound, ys, xs, q)))

def Shape.ss0(+ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>, +cs: List<&2, Core.Expr>,
    sh: Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{Nil{}, xs} == Core.Lo.go(Core.EMatch{Nil{}, cs}, ms, bound, top, mask) : Core.Tm}>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, ys => Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{ys, xs} == Core.Lo.go(Core.EMatch{Nil{}, cs}, ms, bound, top, mask) : Core.Tm}>>:
  match sh:
    case (xs, q):
      (Nil{}, (xs, q))

def Shape.ss(t: List<&2, Core.Expr>, +cs: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>)
    -> Sigma<&2, &2, List<&2, Core.Tm>, ys => Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{ys, xs} == Core.Lo.go(Core.EMatch{t, cs}, ms, bound, top, mask) : Core.Tm}>>:
  match t:
    case Nil{}:
      Shape.ss0(ms, bound, top, mask, cs, Shape.cs(cs, ms, bound, top, mask))
    case +a <> +t2:
      Shape.ss2(a, t2, cs, ms, bound, Shape.ss(t2, cs, ms, bound, False{}, Nil{}))

# The round trip
# ==============

def Var.rt(h: Bool, +n: String) -> {Core.EVar{n} == Core.Up.go(Bool.pick(Core.Tm, h, Core.CVar{n}, Core.CRef{n})) : Core.Expr}:
  match h:
    case True{}:
      {==}
    case False{}:
      {==}

def Call0.rt(h: Bool, +f: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +he: {h == Core.Lo.global(bound, f) : Bool}, ih: {f == Core.Up.go(Core.Lo.go(f, ms, bound, True{}, Nil{})) : Core.Expr})
    -> {Core.ECall{f, Nil{}} == Core.Up.go(Bool.pick(Unit -> Core.Tm, h, u => Core.CCall{Core.Lo.fname(f), Nil{}}, u => Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Nil{}})(Unit{})) : Core.Expr}:
  match h:
    case True{}:
      %Glob.var(f, bound, he) : {Core.ECall{f, Nil{}} == Core.ECall{_, Nil{}} : Core.Expr}
      {==}
    case False{}:
      %ih : {Core.ECall{f, Nil{}} == Core.ECall{_, Nil{}} : Core.Expr}
      {==}

def CallG.step(+f: Core.Expr, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    iha: {a == Core.Up.go(Core.Lo.go(a, ms, bound, True{}, Nil{})) : Core.Expr}, iht: {Core.ECall{f, t} == Core.Up.go(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)))) : Core.Expr},
    sh: Sigma<&2, &2, List<&2, Core.Arg>, as => {Core.CCall{Core.Lo.fname(f), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))) : Core.Tm}>)
    -> {Core.ECall{f, a <> t} == Core.Up.go(Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))))) : Core.Expr}:
  match sh:
    case (as, +q):
      %q : {Core.ECall{f, a <> t} == Core.Up.go(Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(a, ms, bound, True{}, Nil{}), _)) : Core.Expr}
      %iha : {Core.ECall{f, a <> t} == Core.Expr.push(_, Core.Up.go(Core.CCall{Core.Lo.fname(f), as})) : Core.Expr}
      %Tr(Core.ECall{f, t}, Core.CCall{Core.Lo.fname(f), as}, Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))), iht, q) : {Core.ECall{f, a <> t} == Core.Expr.push(a, _) : Core.Expr}
      {==}

def CallA.step(+f: Core.Expr, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    iha: {a == Core.Up.go(Core.Lo.go(a, ms, bound, True{}, Nil{})) : Core.Expr}, iht: {Core.ECall{f, t} == Core.Up.go(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{})) : Core.Expr},
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> {Core.ECall{f, a <> t} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}))) : Core.Expr}:
  match sh:
    case (as, +q):
      %q : {Core.ECall{f, a <> t} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _)) : Core.Expr}
      %iha : {Core.ECall{f, a <> t} == Core.Expr.push(_, Core.Up.go(Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as})) : Core.Expr}
      %Tr(Core.ECall{f, t}, Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as}, Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}), iht, q) : {Core.ECall{f, a <> t} == Core.Expr.push(a, _) : Core.Expr}
      {==}

def CallN.rt(h: Bool, +f: Core.Expr, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    +he: {h == Core.Lo.global(bound, f) : Bool}, +iha: {a == Core.Up.go(Core.Lo.go(a, ms, bound, True{}, Nil{})) : Core.Expr},
    iht1: {Core.ECall{f, t} == Core.Up.go(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)))) : Core.Expr}, iht2: {Core.ECall{f, t} == Core.Up.go(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{})) : Core.Expr})
    -> {Core.ECall{f, a <> t} == Core.Up.go(Bool.pick(Unit -> Core.Tm, h, u => Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)))), u => Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{})))(Unit{})) : Core.Expr}:
  match h:
    case True{}:
      CallG.step(f, a, t, ms, bound, top, mask, iha, iht1, Shape.g(t, f, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)), he))
    case False{}:
      CallA.step(f, a, t, ms, bound, iha, iht2, Shape.n(t, f, ms, bound, False{}, Nil{}, he))

def Ctr.step(+n: String, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    iha: {a == Core.Up.go(Core.Lo.go(a, ms, bound, True{}, Nil{})) : Core.Expr}, iht: {Core.ECtor{n, t} == Core.Up.go(Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{})) : Core.Expr},
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CCtr{n, as} == Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> {Core.ECtor{n, a <> t} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}))) : Core.Expr}:
  match sh:
    case (as, +q):
      %q : {Core.ECtor{n, a <> t} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _)) : Core.Expr}
      %iha : {Core.ECtor{n, a <> t} == Core.Expr.push(_, Core.Up.go(Core.CCtr{n, as})) : Core.Expr}
      %Tr(Core.ECtor{n, t}, Core.CCtr{n, as}, Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}), iht, q) : {Core.ECtor{n, a <> t} == Core.Expr.push(a, _) : Core.Expr}
      {==}

def Ty.step(+n: String, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    iha: {a == Core.Up.go(Core.Lo.go(a, ms, bound, True{}, Nil{})) : Core.Expr}, iht: {Core.ETy{n, t} == Core.Up.go(Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{})) : Core.Expr},
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CTyp{n, as} == Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> {Core.ETy{n, a <> t} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{}))) : Core.Expr}:
  match sh:
    case (as, +q):
      %q : {Core.ETy{n, a <> t} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _)) : Core.Expr}
      %iha : {Core.ETy{n, a <> t} == Core.Expr.push(_, Core.Up.go(Core.CTyp{n, as})) : Core.Expr}
      %Tr(Core.ETy{n, t}, Core.CTyp{n, as}, Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{}), iht, q) : {Core.ETy{n, a <> t} == Core.Expr.push(a, _) : Core.Expr}
      {==}

def Mat.step(+a: Core.Expr, +t: List<&2, Core.Expr>, +cs: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    iha: {a == Core.Up.go(Core.Lo.go(a, ms, bound, True{}, Nil{})) : Core.Expr}, iht: {Core.EMatch{t, cs} == Core.Up.go(Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{})) : Core.Expr},
    sh: Sigma<&2, &2, List<&2, Core.Tm>, ys => Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{ys, xs} == Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}) : Core.Tm}>>)
    -> {Core.EMatch{a <> t, cs} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}))) : Core.Expr}:
  match sh:
    case (ys, r):
      match r:
        case (xs, +q):
          %q : {Core.EMatch{a <> t, cs} == Core.Up.go(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _)) : Core.Expr}
          %iha : {Core.EMatch{a <> t, cs} == Core.Expr.push(_, Core.Up.go(Core.CMat{ys, xs})) : Core.Expr}
          %Tr(Core.EMatch{t, cs}, Core.CMat{ys, xs}, Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}), iht, q) : {Core.EMatch{a <> t, cs} == Core.Expr.push(a, _) : Core.Expr}
          {==}

def Case.step(+c: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    ihc: {c == Core.Up.go(Core.Lo.go(c, ms, bound, True{}, Nil{})) : Core.Expr}, iht: {Core.EMatch{Nil{}, t} == Core.Up.go(Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{})) : Core.Expr},
    sh: Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{Nil{}, xs} == Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> {Core.EMatch{Nil{}, c <> t} == Core.Up.go(Core.Tm.push.case(Core.Lo.go(c, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}))) : Core.Expr}:
  match sh:
    case (xs, +q):
      %q : {Core.EMatch{Nil{}, c <> t} == Core.Up.go(Core.Tm.push.case(Core.Lo.go(c, ms, bound, True{}, Nil{}), _)) : Core.Expr}
      %ihc : {Core.EMatch{Nil{}, c <> t} == Core.Expr.push.case(_, Core.Up.go(Core.CMat{Nil{}, xs})) : Core.Expr}
      %Tr(Core.EMatch{Nil{}, t}, Core.CMat{Nil{}, xs}, Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}), iht, q) : {Core.EMatch{Nil{}, c <> t} == Core.Expr.push.case(c, _) : Core.Expr}
      {==}

# Raising a lowered term gives it back.
def Ex.rt(e: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>) -> {e == Core.Up.go(Core.Lo.go(e, ms, bound, top, mask)) : Core.Expr}:
  match e:
    case Core.EVar{+n}:
      Var.rt(Core.Lo.bound(bound, n), n)
    case Core.ENum{n}:
      {==}
    case Core.ENat{n}:
      {==}
    case Core.EFlt{s}:
      {==}
    case Core.EStr{s}:
      {==}
    case Core.ECall{+f, args}:
      match args:
        case Nil{}:
          Call0.rt(Core.Lo.global(bound, f), f, ms, bound, {==}, Ex.rt(f, ms, bound, True{}, Nil{}))
        case +a <> +t:
          CallN.rt(Core.Lo.global(bound, f), f, a, t, ms, bound, top, mask, {==}, Ex.rt(a, ms, bound, True{}, Nil{}),
            Ex.rt(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))), Ex.rt(Core.ECall{f, t}, ms, bound, False{}, Nil{}))
    case Core.ECtor{+n, args}:
      match args:
        case Nil{}:
          {==}
        case +a <> +t:
          Ctr.step(n, a, t, ms, bound, Ex.rt(a, ms, bound, True{}, Nil{}), Ex.rt(Core.ECtor{n, t}, ms, bound, False{}, Nil{}),
            Shape.ctr(t, n, ms, bound, False{}, Nil{}))
    case Core.ELam{+p, +b}:
      %Pat.rt(p) : {Core.ELam{p, b} == Core.ELam{_, Core.Up.go(Core.Lo.go(b, ms, Core.Lo.bind(Core.Dead.names([Core.Lo.pat(p)]), bound), True{}, Nil{}))} : Core.Expr}
      %Ex.rt(b, ms, Core.Lo.bind(Core.Dead.names([Core.Lo.pat(p)]), bound), True{}, Nil{}) : {Core.ELam{p, b} == Core.ELam{p, _} : Core.Expr}
      {==}
    case Core.ELet{+p, +v, +b}:
      %Pat.rt(p) : {Core.ELet{p, v, b} == Core.ELet{_, Core.Up.go(Core.Lo.go(v, ms, bound, True{}, Nil{})), Core.Up.go(Core.Lo.go(b, ms, Core.Lo.bind(Core.Dead.names([Core.Lo.pat(p)]), bound), True{}, Nil{}))} : Core.Expr}
      %Ex.rt(v, ms, bound, True{}, Nil{}) : {Core.ELet{p, v, b} == Core.ELet{p, _, Core.Up.go(Core.Lo.go(b, ms, Core.Lo.bind(Core.Dead.names([Core.Lo.pat(p)]), bound), True{}, Nil{}))} : Core.Expr}
      %Ex.rt(b, ms, Core.Lo.bind(Core.Dead.names([Core.Lo.pat(p)]), bound), True{}, Nil{}) : {Core.ELet{p, v, b} == Core.ELet{p, v, _} : Core.Expr}
      {==}
    case Core.EMatch{scrs, +cases}:
      match scrs:
        case +a <> +t:
          Mat.step(a, t, cases, ms, bound, Ex.rt(a, ms, bound, True{}, Nil{}), Ex.rt(Core.EMatch{t, cases}, ms, bound, False{}, Nil{}),
            Shape.ss(t, cases, ms, bound, False{}, Nil{}))
        case Nil{}:
          match cases:
            case Nil{}:
              {==}
            case +c <> +t:
              Case.step(c, t, ms, bound, Ex.rt(c, ms, bound, True{}, Nil{}), Ex.rt(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}),
                Shape.cs(t, ms, bound, False{}, Nil{}))
    case Core.ECase{+ps, +b}:
      %Pats.rt(ps) : {Core.ECase{ps, b} == Core.ECase{_, Core.Up.go(Core.Lo.go(b, ms, Core.Lo.bind(Core.Dead.names(Core.Lo.pats(ps)), bound), True{}, Nil{}))} : Core.Expr}
      %Ex.rt(b, ms, Core.Lo.bind(Core.Dead.names(Core.Lo.pats(ps)), bound), True{}, Nil{}) : {Core.ECase{ps, b} == Core.ECase{ps, _} : Core.Expr}
      {==}
    case Core.ESucc{k, +x}:
      %Ex.rt(x, ms, bound, True{}, Nil{}) : {Core.ESucc{k, x} == Core.ESucc{k, _} : Core.Expr}
      {==}
    case Core.EOp{op, +a, +b}:
      %Ex.rt(a, ms, bound, True{}, Nil{}) : {Core.EOp{op, a, b} == Core.EOp{op, _, Core.Up.go(Core.Lo.go(b, ms, bound, True{}, Nil{}))} : Core.Expr}
      %Ex.rt(b, ms, bound, True{}, Nil{}) : {Core.EOp{op, a, b} == Core.EOp{op, a, _} : Core.Expr}
      {==}
    case Core.EAnn{+x, ty}:
      %Ex.rt(x, ms, bound, True{}, Nil{}) : {Core.EAnn{x, ty} == Core.EAnn{_, ty} : Core.Expr}
      {==}
    case Core.ETy{+n, args}:
      match args:
        case Nil{}:
          {==}
        case +a <> +t:
          Ty.step(n, a, t, ms, bound, Ex.rt(a, ms, bound, True{}, Nil{}), Ex.rt(Core.ETy{n, t}, ms, bound, False{}, Nil{}),
            Shape.ty(t, n, ms, bound, False{}, Nil{}))
    case Core.EErr{m}:
      {==}

def Params.rt(ps: List<&2, Core.Param>, +mask: List<&2, Bool>) -> {ps == Core.Up.params(Core.Lo.params(ps, mask)) : List<&2, Core.Param>}:
  match ps:
    case Nil{}:
      {==}
    case p <> +r:
      match p:
        case Core.Param{x, m, t}:
          %Params.rt(r, Core.Lo.tail(mask)) : {Core.Param{x, m, t} <> r == Core.Param{x, m, t} <> _ : List<&2, Core.Param>}
          {==}

def Law.up_lo(e, ms, bound, top, mask):
  Ex.rt(e, ms, bound, top, mask)

def Law.up_lo_pat(p):
  Pat.rt(p)

def Law.up_lo_params(ps, mask):
  Params.rt(ps, mask)
