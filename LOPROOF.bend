import Base
import ./core.bend as Core
import ./DEADPROOF.bend as DP
import ./LO.bend as Law

# Proof of LO.bend's laws. The round trip (up_lo) is an induction on the
# term; a list field is lowered as its head and the node with the rest, and
# the Shape lemmas give that node's constructor. The scope laws: Lo.sc
# (lo_scoped) is an induction on the term too, and L.scope (scope_ok) one
# on the fuel, a case per step of `run`, that each state the run reaches is
# scoped (Good.sel). lo_prog: the defs Lo gives are scoped by their
# parameters, so a run of main is.

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

# Lowering scopes
# ===============

def Str.sym(-a: List<&2, String>, -b: List<&2, String>, e: {a == b : List<&2, String>}) -> {b == a : List<&2, String>}:
  %e : {_ == a : List<&2, String>}
  {==}

# c is r, which is scoped.
def Sc.tr(-c: Core.Tm, -r: Core.Tm, -L: List<&2, String>, s: Law.Scoped(r, L), q: {c == r : Core.Tm}) -> Law.Scoped(c, L):
  %Tm.sym(c, r, q) : Law.Scoped(_, L)
  s

def Var.sc(h: Bool, +n: String, -bound: List<&2, String>, he: {h == Core.Dead.none(bound, n) : Bool})
    -> Law.Scoped(Bool.pick(Core.Tm, Bool.not(h), Core.CVar{n}, Core.CRef{n}), bound):
  match h:
    case True{}:
      Unit{}
    case False{}:
      he

def Call0.sc(h: Bool, +f: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, s: Law.Scoped(Core.Lo.go(f, ms, bound, True{}, Nil{}), bound)) -> Law.Scoped(Bool.pick(Unit -> Core.Tm, h, u => Core.CCall{Core.Lo.fname(f), Nil{}}, u => Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), Nil{}})(Unit{}), bound):
  match h:
    case True{}:
      Unit{}
    case False{}:
      s

def CallG.sc(+f: Core.Expr, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    sa: Law.Scoped(Core.Lo.go(a, ms, bound, True{}, Nil{}), bound), st: Law.Scoped(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))), bound),
    sh: Sigma<&2, &2, List<&2, Core.Arg>, as => {Core.CCall{Core.Lo.fname(f), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))) : Core.Tm}>)
    -> Law.Scoped(Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)))), bound):
  match sh:
    case (as, +q):
      %q : Law.Scoped(Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(a, ms, bound, True{}, Nil{}), _), bound)
      (sa, Sc.tr(Core.CCall{Core.Lo.fname(f), as}, Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))), bound, st, q))

def CallA.sc(+f: Core.Expr, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sa: Law.Scoped(Core.Lo.go(a, ms, bound, True{}, Nil{}), bound), st: Law.Scoped(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}), bound),
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as} == Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{})), bound):
  match sh:
    case (as, +q):
      %q : Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _), bound)
      (sa, Sc.tr(Core.CApp{Core.Lo.go(f, ms, bound, True{}, Nil{}), as}, Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}), bound, st, q))

def CallN.sc(h: Bool, +f: Core.Expr, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>,
    +he: {h == Core.Lo.global(bound, f) : Bool}, +sa: Law.Scoped(Core.Lo.go(a, ms, bound, True{}, Nil{}), bound),
    st1: Law.Scoped(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask))), bound), st2: Law.Scoped(Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{}), bound))
    -> Law.Scoped(Bool.pick(Unit -> Core.Tm, h, u => Core.Lo.arg(Core.Lo.mask(top, ms, f, mask), Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)))), u => Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECall{f, t}, ms, bound, False{}, Nil{})))(Unit{}), bound):
  match h:
    case True{}:
      CallG.sc(f, a, t, ms, bound, top, mask, sa, st1, Shape.g(t, f, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)), he))
    case False{}:
      CallA.sc(f, a, t, ms, bound, sa, st2, Shape.n(t, f, ms, bound, False{}, Nil{}, he))

def Ctr.sc(+n: String, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sa: Law.Scoped(Core.Lo.go(a, ms, bound, True{}, Nil{}), bound), st: Law.Scoped(Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}), bound),
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CCtr{n, as} == Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{})), bound):
  match sh:
    case (as, +q):
      %q : Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _), bound)
      (sa, Sc.tr(Core.CCtr{n, as}, Core.Lo.go(Core.ECtor{n, t}, ms, bound, False{}, Nil{}), bound, st, q))

def Mat.sc(+a: Core.Expr, +t: List<&2, Core.Expr>, +cs: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sa: Law.Scoped(Core.Lo.go(a, ms, bound, True{}, Nil{}), bound), st: Law.Scoped(Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}), bound),
    sh: Sigma<&2, &2, List<&2, Core.Tm>, ys => Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{ys, xs} == Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}) : Core.Tm}>>)
    -> Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{})), bound):
  match sh:
    case (ys, r):
      match r:
        case (xs, +q):
          %q : Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _), bound)
          (sa, Sc.tr(Core.CMat{ys, xs}, Core.Lo.go(Core.EMatch{t, cs}, ms, bound, False{}, Nil{}), bound, st, q))

def Case.sc(+c: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sc: Law.Scoped(Core.Lo.go(c, ms, bound, True{}, Nil{}), bound), st: Law.Scoped(Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}), bound),
    sh: Sigma<&2, &2, List<&2, Core.Tm>, xs => {Core.CMat{Nil{}, xs} == Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Law.Scoped(Core.Tm.push.case(Core.Lo.go(c, ms, bound, True{}, Nil{}), Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{})), bound):
  match sh:
    case (xs, +q):
      %q : Law.Scoped(Core.Tm.push.case(Core.Lo.go(c, ms, bound, True{}, Nil{}), _), bound)
      (sc, Sc.tr(Core.CMat{Nil{}, xs}, Core.Lo.go(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}), bound, st, q))

def Ty.sc(+n: String, +a: Core.Expr, +t: List<&2, Core.Expr>, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>,
    sh: Sigma<&2, &2, List<&2, Core.Tm>, as => {Core.CTyp{n, as} == Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{}) : Core.Tm}>)
    -> Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), Core.Lo.go(Core.ETy{n, t}, ms, bound, False{}, Nil{})), bound):
  match sh:
    case (as, +q):
      %q : Law.Scoped(Core.Tm.push(Core.Lo.go(a, ms, bound, True{}, Nil{}), _), bound)
      Unit{}

# Each variable a lowered term looks up is bound: one of bound, or one the
# term binds.
def Lo.sc(e: Core.Expr, +ms: Map<&2, List<&2, Bool>>, +bound: List<&2, String>, +top: Bool, +mask: List<&2, Bool>, ok: Law.NoErr(e)) -> Law.Scoped(Core.Lo.go(e, ms, bound, top, mask), bound):
  match e:
    case Core.EVar{+n}:
      Var.sc(Core.Dead.none(bound, n), n, bound, {==})
    case Core.ENum{n}:
      Unit{}
    case Core.ENat{n}:
      Unit{}
    case Core.EFlt{s}:
      Unit{}
    case Core.EStr{s}:
      Unit{}
    case Core.ECall{+f, args}:
      match args:
        case Nil{}:
          Call0.sc(Core.Lo.global(bound, f), f, ms, bound, Lo.sc(f, ms, bound, True{}, Nil{}, ok))
        case +a <> +t:
          match ok:
            case (oa, +ot):
              CallN.sc(Core.Lo.global(bound, f), f, a, t, ms, bound, top, mask, {==}, Lo.sc(a, ms, bound, True{}, Nil{}, oa),
                Lo.sc(Core.ECall{f, t}, ms, bound, False{}, Core.Lo.tail(Core.Lo.mask(top, ms, f, mask)), ot), Lo.sc(Core.ECall{f, t}, ms, bound, False{}, Nil{}, ot))
    case Core.ECtor{+n, args}:
      match args:
        case Nil{}:
          Unit{}
        case +a <> +t:
          match ok:
            case (oa, ot):
              Ctr.sc(n, a, t, ms, bound, Lo.sc(a, ms, bound, True{}, Nil{}, oa), Lo.sc(Core.ECtor{n, t}, ms, bound, False{}, Nil{}, ot),
                Shape.ctr(t, n, ms, bound, False{}, Nil{}))
    case Core.ELam{+p, b}:
      Lo.sc(b, ms, Core.Lo.bind(Core.Dead.names([Core.Lo.pat(p)]), bound), True{}, Nil{}, ok)
    case Core.ELet{+p, v, b}:
      match ok:
        case (ov, ob):
          (Lo.sc(v, ms, bound, True{}, Nil{}, ov), Lo.sc(b, ms, Core.Lo.bind(Core.Dead.names([Core.Lo.pat(p)]), bound), True{}, Nil{}, ob))
    case Core.EMatch{scrs, +cases}:
      match scrs:
        case +a <> +t:
          match ok:
            case (oa, ot):
              Mat.sc(a, t, cases, ms, bound, Lo.sc(a, ms, bound, True{}, Nil{}, oa), Lo.sc(Core.EMatch{t, cases}, ms, bound, False{}, Nil{}, ot),
                Shape.ss(t, cases, ms, bound, False{}, Nil{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Unit{}
            case +c <> +t:
              match ok:
                case (oc, ot):
                  Case.sc(c, t, ms, bound, Lo.sc(c, ms, bound, True{}, Nil{}, oc), Lo.sc(Core.EMatch{Nil{}, t}, ms, bound, False{}, Nil{}, ot),
                    Shape.cs(t, ms, bound, False{}, Nil{}))
    case Core.ECase{+ps, b}:
      Lo.sc(b, ms, Core.Lo.bind(Core.Dead.names(Core.Lo.pats(ps)), bound), True{}, Nil{}, ok)
    case Core.ESucc{k, x}:
      Lo.sc(x, ms, bound, True{}, Nil{}, ok)
    case Core.EOp{op, a, b}:
      match ok:
        case (oa, ob):
          (Lo.sc(a, ms, bound, True{}, Nil{}, oa), Lo.sc(b, ms, bound, True{}, Nil{}, ob))
    case Core.EAnn{x, ty}:
      Lo.sc(x, ms, bound, True{}, Nil{}, ok)
    case Core.ETy{+n, args}:
      match args:
        case Nil{}:
          Unit{}
        case +a <> +t:
          Ty.sc(n, a, t, ms, bound, Shape.ty(t, n, ms, bound, False{}, Nil{}))
    case Core.EErr{m}:
      ok

def Law.lo_scoped(e, ms, bound, top, mask, ok):
  Lo.sc(e, ms, bound, top, mask, ok)

# Runs of scoped states
# =====================

# t is scoped by B, and A is B.
def Sc.back(-t: Core.Tm, -A: List<&2, String>, -B: List<&2, String>, e: {A == B : List<&2, String>}, s: Law.Scoped(t, B))
    -> Law.Scoped(t, A):
  %Str.sym(A, B, e) : Law.Scoped(t, _)
  s

# The lists of scoped nodes.
def Call.args(+f: String, as: List<&2, Core.Arg>, -L: List<&2, String>, s: Law.Scoped(Core.CCall{f, as}, L)) -> Law.Scoped.args(as, L):
  match as:
    case Nil{}:
      Unit{}
    case a <> r:
      match a:
        case Core.Arg{rel, e}:
          match s:
            case (se, sr):
              (se, Call.args(f, r, L, sr))

def App.cons(-f: Core.Tm, -a: Core.Tm, -as: List<&2, Core.Tm>, -L: List<&2, String>, sa: Law.Scoped(a, L), s: Law.Scopeds(f <> as, L))
    -> Law.Scopeds(f <> a <> as, L):
  match s:
    case (sf, srs):
      (sf, (sa, srs))

def App.sc(+f: Core.Tm, as: List<&2, Core.Tm>, -L: List<&2, String>, s: Law.Scoped(Core.CApp{f, as}, L)) -> Law.Scopeds(f <> as, L):
  match as:
    case Nil{}:
      (s, Unit{})
    case a <> r:
      match s:
        case (sa, sr):
          App.cons(f, a, r, L, sa, App.sc(f, r, L, sr))

def Ctr.list(+k: String, as: List<&2, Core.Tm>, -L: List<&2, String>, s: Law.Scoped(Core.CCtr{k, as}, L)) -> Law.Scopeds(as, L):
  match as:
    case Nil{}:
      Unit{}
    case a <> r:
      match s:
        case (sa, sr):
          (sa, Ctr.list(k, r, L, sr))

def Mat.cases(cs: List<&2, Core.Tm>, -L: List<&2, String>, s: Law.Scoped(Core.CMat{Nil{}, cs}, L)) -> Law.Scopeds(cs, L):
  match cs:
    case Nil{}:
      Unit{}
    case c <> r:
      match s:
        case (sc, sr):
          (sc, Mat.cases(r, L, sr))

def Mat.ss(scrs: List<&2, Core.Tm>, +cs: List<&2, Core.Tm>, -L: List<&2, String>, s: Law.Scoped(Core.CMat{scrs, cs}, L)) -> Law.Scopeds(scrs, L):
  match scrs:
    case Nil{}:
      Unit{}
    case a <> r:
      match s:
        case (sa, sr):
          (sa, Mat.ss(r, cs, L, sr))

def Mat.cs(scrs: List<&2, Core.Tm>, +cs: List<&2, Core.Tm>, -L: List<&2, String>, s: Law.Scoped(Core.CMat{scrs, cs}, L)) -> Law.Scopeds(cs, L):
  match scrs:
    case Nil{}:
      Mat.cases(cs, L, s)
    case a <> r:
      match s:
        case (sa, sr):
          Mat.cs(r, cs, L, sr)

# Lists of good values.
def Cat.goods(a: List<&2, Core.Val>, -b: List<&2, Core.Val>, ga: Law.Goods(a), gb: Law.Goods(b)) -> Law.Goods(Core.Vals.cat(a, b)):
  match a:
    case Nil{}:
      gb
    case v <> r:
      match ga:
        case (gv, gr):
          (gv, Cat.goods(r, b, gr, gb))

def Drop.goods(n: Nat, vs: List<&2, Core.Val>, g: Law.Goods(vs)) -> Law.Goods(Core.Vals.drop(n, vs)):
  match n:
    case 0n:
      g
    case 1n+m:
      match vs:
        case Nil{}:
          Unit{}
        case v <> r:
          match g:
            case (gv, gr):
              Drop.goods(m, r, gr)

def Bind.goods.push(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, acc: List<&2, Core.Val>, g: Law.Goods(vs), ga: Law.Goods(acc))
    -> Law.Goods(Core.Scope.push(ps, vs, acc)):
  match ps:
    case Nil{}:
      ga
    case p <> pr:
      match p:
        case Core.Par{x, rel, m, ty}:
          match vs:
            case Nil{}:
              ga
            case v <> vr:
              match g:
                case (gv, gr):
                  Bind.goods.push(pr, vr, Core.VBnd{x, v} <> acc, gr, (gv, ga))

def Bind.goods(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, g: Law.Goods(vs)) -> Law.Goods(Core.Scope.bind(ps, vs)):
  Bind.goods.push(ps, vs, Nil{}, g, Unit{})

# With no fewer values than parameters, the scope binds the parameters, each
# in front of the ones before it.
def Bind.names.push(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, acc: List<&2, Core.Val>,
    lt: {False{} == Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)) : Bool})
    -> {Law.Env.names(Core.Scope.push(ps, vs, acc)) == Core.Lo.bind(Law.Pars.names(ps), Law.Env.names(acc)) : List<&2, String>}:
  match ps:
    case Nil{}:
      {==}
    case p <> pr:
      match p:
        case Core.Par{+x, rel, m, ty}:
          match vs:
            case Nil{}:
              Absurd({Law.Env.names(acc) == Core.Lo.bind(Law.Pars.names(pr), x <> Law.Env.names(acc)) : List<&2, String>}, Tru.of(False{}, DP.Bool.sym(False{}, True{}, lt)))
            case v <> vr:
              Bind.names.push(pr, vr, Core.VBnd{x, v} <> acc, lt)

def Bind.names(ps: List<&2, Core.Par>, vs: List<&2, Core.Val>, lt: {False{} == Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)) : Bool})
    -> {Law.Env.names(Core.Scope.bind(ps, vs)) == Core.Lo.bind(Law.Pars.names(ps), Nil{}) : List<&2, String>}:
  Bind.names.push(ps, vs, Nil{}, lt)

# What a native gives, as a result.
def Prim.lift(r: Core.Res, -F: List<&2, String>, g: Law.Good.prim(r)) -> Law.Good.res(r, F):
  match r:
    case Core.ROk{vs}:
      g
    case Core.REnv{env}:
      Absurd(Law.Good.res(Core.REnv{env}, F), g)
    case Core.RNo{}:
      g
    case Core.RFail{m}:
      g

def Look.h(h: Bool, -r: List<&2, Core.Val>, -x: String, nb: {False{} == Bool.and(Bool.not(h), Core.Dead.none(Law.Env.names(r), x)) : Bool})
    -> Law.Look.ok(h, r, x):
  match h:
    case True{}:
      Unit{}
    case False{}:
      nb

def Enter.h(h: Bool, -vs: List<&2, Core.Val>, -ps: List<&2, Core.Par>, he: {h == Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)) : Bool})
    -> Law.Enter.ok(h, vs, ps):
  match h:
    case True{}:
      Unit{}
    case False{}:
      he

def PatC.mk(h: Bool, -env: List<&2, Core.Val>, -ps: List<&2, Core.Pt>, -vs: List<&2, Core.Val>, -F: List<&2, String>, pk: Law.Pat.ok(env, ps, vs, F))
    -> Law.Good.sel(Core.SPatC{h, env, ps, vs}, F):
  match h:
    case True{}:
      pk
    case False{}:
      Unit{}

def Eq.cat(qs: List<&2, Core.Pt>, +pr: List<&2, Core.Pt>, -env: List<&2, Core.Val>, -F: List<&2, String>,
    eq: {Core.Lo.bind(Core.Dead.cat(Core.Dead.names(qs), Core.Dead.names(pr)), Law.Env.names(env)) == F : List<&2, String>})
    -> {Core.Lo.bind(Core.Dead.names(Core.Pts.cat(qs, pr)), Law.Env.names(env)) == F : List<&2, String>}:
  %DP.Names.cat(qs, pr) : {Core.Lo.bind(_, Law.Env.names(env)) == F : List<&2, String>}
  eq

# One pattern step of a good match is good.
def Step.good(+env: List<&2, Core.Val>, pt: Core.Pt, v: Core.Val, +pr: List<&2, Core.Pt>, +vr: List<&2, Core.Val>, -F: List<&2, String>,
    ge: Law.Goods(env), gv: Law.Good(v), gvr: Law.Goods(vr),
    eq: {Core.Lo.bind(Core.Dead.names(pt <> pr), Law.Env.names(env)) == F : List<&2, String>})
    -> Law.Good.sel(Core.Pat.step(env, pt, v, pr, vr), F):
  match pt:
    case Core.PtVar{x}:
      ((gv, ge), (gvr, eq))
    case Core.PtCtr{+k, +qs}:
      match v:
        case Core.VCtr{+k2, +fs}:
          match gv:
            case (u, gfs):
              PatC.mk(Bool.and(String.eq(k, k2), Nat.is_eq(Core.Pts.len(qs), Core.Vals.len(fs))), env, Core.Pts.cat(qs, pr), Core.Vals.cat(fs, vr), F,
                (ge, (Cat.goods(fs, vr, gfs, gvr), Eq.cat(qs, pr, env, F, eq))))
        case Core.VLit{l9}:
          Unit{}
        case Core.VClo{env9, pt9, b9}:
          Unit{}
        case Core.VFun{f9, as9}:
          Unit{}
        case Core.VTrm{t9}:
          Unit{}
        case Core.VBnd{x9, w9}:
          Unit{}
    case Core.PtNat{n}:
      match v:
        case Core.VLit{l}:
          PatC.mk(Core.Lit.eq(Core.LNat{n}, l), env, pr, vr, F, (ge, (gvr, eq)))
        case Core.VCtr{k9, fs9}:
          Unit{}
        case Core.VClo{env9, pt9, b9}:
          Unit{}
        case Core.VFun{f9, as9}:
          Unit{}
        case Core.VTrm{t9}:
          Unit{}
        case Core.VBnd{x9, w9}:
          Unit{}
    case Core.PtNum{n}:
      match v:
        case Core.VLit{l}:
          PatC.mk(Core.Lit.eq(Core.LNum{n}, l), env, pr, vr, F, (ge, (gvr, eq)))
        case Core.VCtr{k9, fs9}:
          Unit{}
        case Core.VClo{env9, pt9, b9}:
          Unit{}
        case Core.VFun{f9, as9}:
          Unit{}
        case Core.VTrm{t9}:
          Unit{}
        case Core.VBnd{x9, w9}:
          Unit{}
    case Core.PtFlt{s}:
      match v:
        case Core.VLit{l}:
          PatC.mk(Core.Lit.eq(Core.LFlt{s}, l), env, pr, vr, F, (ge, (gvr, eq)))
        case Core.VCtr{k9, fs9}:
          Unit{}
        case Core.VClo{env9, pt9, b9}:
          Unit{}
        case Core.VFun{f9, as9}:
          Unit{}
        case Core.VTrm{t9}:
          Unit{}
        case Core.VBnd{x9, w9}:
          Unit{}
    case Core.PtSuc{+k, q}:
      match v:
        case Core.VLit{l}:
          match l:
            case Core.LNat{+m}:
              PatC.mk(U32.is_le(k, m), env, q <> pr, Core.VLit{Core.LNat{U32.sub(m, k)}} <> vr, F, (ge, ((Unit{}, gvr), eq)))
            case Core.LNum{m}:
              Unit{}
            case Core.LFlt{m}:
              Unit{}
            case Core.LStr{m}:
              Unit{}
        case Core.VCtr{k9, fs9}:
          Unit{}
        case Core.VClo{env9, pt9, b9}:
          Unit{}
        case Core.VFun{f9, as9}:
          Unit{}
        case Core.VTrm{t9}:
          Unit{}
        case Core.VBnd{x9, w9}:
          Unit{}

# A run of a good state gives a good result: never a failed lookup.
def L.scope(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs:List<&2, Core.Val> -> Law.Goods(vs) -> Law.Good.prim(prim(op, vs)),
    +n: Nat, +ds: List<&2, Core.Def>, +gd: Law.Good.defs(ds), s: Core.Sel, -F: List<&2, String>, g: Law.Good.sel(s, F))
    -> Law.Good.res(Core.run(~prim, n, ds, s), F):
  match n:
    case 0n:
      {==}
    case 1n+p:
      match s:
        case Core.SEval{+env, e}:
          match e:
            case Core.CVar{+x}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SLook{env, x}, F, g)
            case Core.CLit{+l}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VLit{l}}}, F, (Nil{}, (Unit{}, Unit{})))
            case Core.CRef{+f}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SCallDef{f, Nil{}}, F, Unit{})
            case Core.CCall{+f, +as}:
              match g:
                case (ge, sc):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCall{f}}, F,
                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SArgs{env, as}, Nil{}, (ge, Call.args(f, as, Law.Env.names(env), sc))), Unit{})))
            case Core.CApp{+f, +as}:
              match g:
                case (ge, sc):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, f <> as}), Core.KApp{}}, F,
                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEvals{env, f <> as}, Nil{}, (ge, App.sc(f, as, Law.Env.names(env), sc))), Unit{})))
            case Core.CCtr{+k, +as}:
              match g:
                case (ge, sc):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, as}), Core.KCtr{k}}, F,
                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEvals{env, as}, Nil{}, (ge, Ctr.list(k, as, Law.Env.names(env), sc))), Unit{})))
            case Core.CLam{+pt, +bd}:
              match g:
                case (ge, sb):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VClo{env, pt, bd}}}, F, (Nil{}, (Unit{}, (sb, ge))))
            case Core.CLet{+pt, +v, +bd}:
              match g:
                case (+ge, sc):
                  match sc:
                    case (sv, sb):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, v}), Core.KLet{env, pt, bd}}, F,
                        (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env, v}, Nil{}, (ge, sv)), (ge, sb))))
            case Core.CMat{+scrs, +cases}:
              match g:
                case (+ge, +sc):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, scrs}), Core.KMat{env, cases}}, F,
                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEvals{env, scrs}, Nil{}, (ge, Mat.ss(scrs, cases, Law.Env.names(env), sc))),
                      (ge, Mat.cs(scrs, cases, Law.Env.names(env), sc)))))
            case Core.CCse{+ps, +bd}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.RFail{"a case outside a match"}, Core.KApp{}}, F, (Nil{}, ({==}, Unit{})))
            case Core.CSuc{+k, +x}:
              match g:
                case (ge, sx):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, x}), Core.KSuc{k}}, F,
                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env, x}, Nil{}, (ge, sx)), Unit{})))
            case Core.COp{+op, +x, +y}:
              match g:
                case (ge, sc):
                  match sc:
                    case (sx, sy):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, [x, y]}), Core.KOp{op}}, F,
                        (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEvals{env, [x, y]}, Nil{}, (ge, (sx, (sy, Unit{})))), Unit{})))
            case Core.CAnn{+x, +ty}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env, x}, F, g)
            case Core.CTyp{+nm, +as}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, F, (Nil{}, (Unit{}, Unit{})))
            case Core.CBox{}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.ROk{Nil{}}, Core.KCons{Core.VTrm{Core.CBox{}}}}, F, (Nil{}, (Unit{}, Unit{})))
            case Core.CErr{+m}:
              match g:
                case (ge, u):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.RFail{m}, Core.KApp{}}, F, (Nil{}, (u, Unit{})))
        case Core.SEvals{+env, es}:
          match es:
            case Nil{}:
              Unit{}
            case +e <> +r:
              match g:
                case (+ge, sc):
                  match sc:
                    case (se, sr):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KTail{env, r}}, F,
                        (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env, e}, Nil{}, (ge, se)), (ge, sr))))
        case Core.SArgs{+env, as}:
          match as:
            case Nil{}:
              Unit{}
            case a <> +r:
              match a:
                case Core.Arg{rel, +e}:
                  match rel:
                    case Core.Run{}:
                      match g:
                        case (+ge, sc):
                          match sc:
                            case (se, sr):
                              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, e}), Core.KATail{env, r}}, F,
                                (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env, e}, Nil{}, (ge, se)), (ge, sr))))
                    case Core.Era{}:
                      match g:
                        case (+ge, sc):
                          match sc:
                            case (se, sr):
                              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env, Core.CBox{}}), Core.KATail{env, r}}, F,
                                (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env, Core.CBox{}}, Nil{}, (ge, Unit{})), (ge, sr))))
        case Core.SThen{r, k}:
          match r:
            case Core.RFail{m}:
              match g:
                case (F2, gg):
                  match gg:
                    case (gr, gk):
                      gr
            case Core.RNo{}:
              match k:
                case Core.KCall{f9}:
                  {==}
                case Core.KApp{}:
                  {==}
                case Core.KCtr{k9}:
                  {==}
                case Core.KLet{env9, pt9, b9}:
                  {==}
                case Core.KBind{b9}:
                  {==}
                case Core.KMat{env9, cases9}:
                  {==}
                case Core.KCase{+env, +vs, b, +rest}:
                  match g:
                    case (F2, gg):
                      match gg:
                        case (gr, gk):
                          match gk:
                            case (ge, gk2):
                              match gk2:
                                case (gvs, gk3):
                                  match gk3:
                                    case (sb, srest):
                                      L.scope(~prim, ~ok, p, ds, gd, Core.SMatch{env, vs, rest}, F, (ge, (gvs, srest)))
                case Core.KSuc{k9}:
                  {==}
                case Core.KOp{op9}:
                  {==}
                case Core.KTail{env9, es9}:
                  {==}
                case Core.KATail{env9, as9}:
                  {==}
                case Core.KCons{v9}:
                  {==}
                case Core.KApply{vs9}:
                  {==}
                case Core.KBody{b9, rest9}:
                  {==}
            case Core.REnv{+env2}:
              match k:
                case Core.KCall{f9}:
                  {==}
                case Core.KApp{}:
                  {==}
                case Core.KCtr{k9}:
                  {==}
                case Core.KLet{env9, pt9, b9}:
                  {==}
                case Core.KBind{+b}:
                  match g:
                    case (F2, gg):
                      match gg:
                        case (gr, gk):
                          match gr:
                            case (eqn, genv2):
                              L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env2, b}, F, (genv2, Sc.back(b, Law.Env.names(env2), F2, eqn, gk)))
                case Core.KMat{env9, cases9}:
                  {==}
                case Core.KCase{env, vs, +b, rest}:
                  match g:
                    case (F2, gg):
                      match gg:
                        case (gr, gk):
                          match gr:
                            case (eqn, genv2):
                              match gk:
                                case (ge, gk2):
                                  match gk2:
                                    case (gvs, gk3):
                                      match gk3:
                                        case (sb, srest):
                                          L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env2, b}, F, (genv2, Sc.back(b, Law.Env.names(env2), F2, eqn, sb)))
                case Core.KSuc{k9}:
                  {==}
                case Core.KOp{op9}:
                  {==}
                case Core.KTail{env9, es9}:
                  {==}
                case Core.KATail{env9, as9}:
                  {==}
                case Core.KCons{v9}:
                  {==}
                case Core.KApply{vs9}:
                  {==}
                case Core.KBody{+b, +rest}:
                  match g:
                    case (F2, gg):
                      match gg:
                        case (gr, gk):
                          match gr:
                            case (eqn, genv2):
                              match gk:
                                case (sb, grest):
                                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEval{env2, b}), Core.KApply{rest}}, F,
                                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEval{env2, b}, Nil{}, (genv2, Sc.back(b, Law.Env.names(env2), F2, eqn, sb))), grest)))
            case Core.ROk{+vs}:
              match g:
                case (F2, gg):
                  match gg:
                    case (gr, gk):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SOk{k, vs}, F, (gr, (F2, gk)))
        case Core.SOk{k, +vs}:
          match k:
            case Core.KCall{+f}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (F2, gk):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SCallDef{f, vs}, F, gvs)
            case Core.KApp{}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r2:
                  match g:
                    case (gvs, gg):
                      match gvs:
                        case (gv, gr):
                          match gg:
                            case (F2, gk):
                              L.scope(~prim, ~ok, p, ds, gd, Core.SApply{r2, v}, F, (gr, gv))
            case Core.KCtr{+c}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (F2, gk):
                      ((Unit{}, gvs), Unit{})
            case Core.KLet{+env, +pt, +bd}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (F2, gk):
                      match gk:
                        case (ge, sb):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], vs}), Core.KBind{bd}}, F,
                            (Core.Lo.bind(Core.Dead.names([pt]), Law.Env.names(env)), (L.scope(~prim, ~ok, p, ds, gd, Core.SPat{env, [pt], vs}, Core.Lo.bind(Core.Dead.names([pt]), Law.Env.names(env)), (ge, (gvs, {==}))), sb)))
            case Core.KBind{b9}:
              {==}
            case Core.KMat{+env, +cases}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (F2, gk):
                      match gk:
                        case (ge, scs):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SMatch{env, vs, cases}, F, (ge, (gvs, scs)))
            case Core.KCase{env9, vs9, b9, rest9}:
              {==}
            case Core.KSuc{+c}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (F2, gk):
                      Prim.lift(prim("%suc", Core.VLit{Core.LNum{c}} <> vs), F, ok("%suc", Core.VLit{Core.LNum{c}} <> vs, (Unit{}, gvs)))
            case Core.KOp{+op}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (F2, gk):
                      Prim.lift(prim(op, vs), F, ok(op, vs, gvs))
            case Core.KTail{+env, +es}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r2:
                  match g:
                    case (gvs, gg):
                      match gvs:
                        case (gv, gr):
                          match gg:
                            case (F2, gk):
                              match gk:
                                case (ge, ses):
                                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEvals{env, es}), Core.KCons{v}}, F,
                                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEvals{env, es}, Nil{}, (ge, ses)), gv)))
            case Core.KATail{+env, +as}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r2:
                  match g:
                    case (gvs, gg):
                      match gvs:
                        case (gv, gr):
                          match gg:
                            case (F2, gk):
                              match gk:
                                case (ge, ses):
                                  L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SArgs{env, as}), Core.KCons{v}}, F,
                                    (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SArgs{env, as}, Nil{}, (ge, ses)), gv)))
            case Core.KCons{+v}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (F2, gk):
                      (gk, gvs)
            case Core.KApply{+rest}:
              match vs:
                case Nil{}:
                  {==}
                case +v <> +r2:
                  match g:
                    case (gvs, gg):
                      match gvs:
                        case (gv, gr):
                          match gg:
                            case (F2, gk):
                              L.scope(~prim, ~ok, p, ds, gd, Core.SApply{rest, v}, F, (gk, gv))
            case Core.KBody{b9, rest9}:
              {==}
        case Core.SLook{env, +x}:
          match env:
            case Nil{}:
              match g:
                case (ge, nb):
                  nb
            case b <> +r:
              match b:
                case Core.VBnd{+y, +v}:
                  match g:
                    case (ge, nb):
                      match ge:
                        case (gv, gr):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SLook2{String.eq(y, x), v, r, x}, F, (gv, (gr, Look.h(String.eq(y, x), r, x, nb))))
                case Core.VLit{l9}:
                  match g:
                    case (ge, nb):
                      match ge:
                        case (gb, gr):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SLook{r, x}, F, (gr, nb))
                case Core.VCtr{k9, fs9}:
                  match g:
                    case (ge, nb):
                      match ge:
                        case (gb, gr):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SLook{r, x}, F, (gr, nb))
                case Core.VClo{env9, pt9, b9}:
                  match g:
                    case (ge, nb):
                      match ge:
                        case (gb, gr):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SLook{r, x}, F, (gr, nb))
                case Core.VFun{f9, as9}:
                  match g:
                    case (ge, nb):
                      match ge:
                        case (gb, gr):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SLook{r, x}, F, (gr, nb))
                case Core.VTrm{t9}:
                  match g:
                    case (ge, nb):
                      match ge:
                        case (gb, gr):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SLook{r, x}, F, (gr, nb))
        case Core.SLook2{hit, +v, +env, +x}:
          match hit:
            case True{}:
              match g:
                case (gv, gg):
                  (gv, Unit{})
            case False{}:
              match g:
                case (gv, gg):
                  L.scope(~prim, ~ok, p, ds, gd, Core.SLook{env, x}, F, gg)
        case Core.SCallDef{+f, +vs}:
          L.scope(~prim, ~ok, p, ds, gd, Core.SFind{ds, f, vs}, F, (g, gd))
        case Core.SFind{ds2, +f, +vs}:
          match ds2:
            case Nil{}:
              match g:
                case (gvs, gds):
                  Prim.lift(prim(f, vs), F, ok(f, vs, gvs))
            case d <> +r:
              match d:
                case Core.Def{+name, +ps, +b, ret}:
                  match g:
                    case (gvs, gds):
                      match gds:
                        case (sb, gr):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SFound{String.eq(name, f), ps, b, r, f, vs}, F, (gvs, (gr, sb)))
        case Core.SFound{hit, +ps, +b, +ds2, +f, +vs}:
          match hit:
            case True{}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (gds, sb):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SEnter{Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), f, ps, b, vs}, F,
                        (gvs, (sb, Enter.h(Nat.is_lt(Core.Vals.len(vs), Core.Pars.len(ps)), vs, ps, {==}))))
            case False{}:
              match g:
                case (gvs, gg):
                  match gg:
                    case (gds, sb):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SFind{ds2, f, vs}, F, (gvs, gds))
        case Core.SEnter{short, +f, +ps, +b, +vs}:
          match short:
            case True{}:
              match g:
                case (gvs, gg):
                  ((Unit{}, gvs), Unit{})
            case False{}:
              match g:
                case (+gvs, gg):
                  match gg:
                    case (sb, en):
                      L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SEval{Core.Scope.bind(ps, vs), b}), Core.KApply{Core.Vals.drop(Core.Pars.len(ps), vs)}}, F,
                        (Nil{}, (L.scope(~prim, ~ok, p, ds, gd, Core.SEval{Core.Scope.bind(ps, vs), b}, Nil{},
                          (Bind.goods(ps, vs, gvs), Sc.back(b, Law.Env.names(Core.Scope.bind(ps, vs)), Core.Lo.bind(Law.Pars.names(ps), Nil{}), Bind.names(ps, vs, en), sb))),
                          Drop.goods(Core.Pars.len(ps), vs, gvs))))
        case Core.SApply{vs, fv}:
          match vs:
            case Nil{}:
              match g:
                case (gvs, gf):
                  (gf, Unit{})
            case +v <> +r:
              match fv:
                case Core.VClo{+env, +pt, +bd}:
                  match g:
                    case (gvs, gf):
                      match gvs:
                        case (gv, gr):
                          match gf:
                            case (sb, genv):
                              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, [pt], [v]}), Core.KBody{bd, r}}, F,
                                (Core.Lo.bind(Core.Dead.names([pt]), Law.Env.names(env)),
                                  (L.scope(~prim, ~ok, p, ds, gd, Core.SPat{env, [pt], [v]}, Core.Lo.bind(Core.Dead.names([pt]), Law.Env.names(env)),
                                    (genv, ((gv, Unit{}), {==}))), (sb, gr))))
                case Core.VFun{+f, +as}:
                  match g:
                    case (gvs, gf):
                      match gf:
                        case (u, gas):
                          L.scope(~prim, ~ok, p, ds, gd, Core.SCallDef{f, Core.Vals.cat(as, v <> r)}, F, Cat.goods(as, v <> r, gas, gvs))
                case Core.VLit{l9}:
                  {==}
                case Core.VCtr{k9, fs9}:
                  {==}
                case Core.VTrm{t9}:
                  {==}
                case Core.VBnd{x9, w9}:
                  {==}
        case Core.SMatch{+env, +vs, cases}:
          match cases:
            case Nil{}:
              {==}
            case c <> +r:
              match c:
                case Core.CCse{+ps, +bd}:
                  match g:
                    case (+ge, gg):
                      match gg:
                        case (+gvs, scs):
                          match scs:
                            case (sc, sr):
                              L.scope(~prim, ~ok, p, ds, gd, Core.SThen{Core.run(~prim, p, ds, Core.SPat{env, ps, vs}), Core.KCase{env, vs, bd, r}}, F,
                                (Core.Lo.bind(Core.Dead.names(ps), Law.Env.names(env)),
                                  (L.scope(~prim, ~ok, p, ds, gd, Core.SPat{env, ps, vs}, Core.Lo.bind(Core.Dead.names(ps), Law.Env.names(env)), (ge, (gvs, {==}))),
                                    (ge, (gvs, (sc, sr))))))
                case Core.CVar{x9}:
                  {==}
                case Core.CLit{l9}:
                  {==}
                case Core.CRef{f9}:
                  {==}
                case Core.CCall{f9, as9}:
                  {==}
                case Core.CApp{f9, as9}:
                  {==}
                case Core.CCtr{k9, as9}:
                  {==}
                case Core.CLam{pt9, b9}:
                  {==}
                case Core.CLet{pt9, v9, b9}:
                  {==}
                case Core.CMat{scrs9, cases9}:
                  {==}
                case Core.CSuc{k9, x9}:
                  {==}
                case Core.COp{op9, a9, b9}:
                  {==}
                case Core.CAnn{x9, ty9}:
                  {==}
                case Core.CTyp{n9, as9}:
                  {==}
                case Core.CBox{}:
                  {==}
                case Core.CErr{m9}:
                  {==}
        case Core.SPat{+env, ps, vs}:
          match ps:
            case Nil{}:
              match vs:
                case Nil{}:
                  match g:
                    case (ge, gg):
                      match gg:
                        case (gvs, eq):
                          (eq, ge)
                case v <> vr:
                  Unit{}
            case +pt <> +pr:
              match vs:
                case Nil{}:
                  Unit{}
                case +v <> +vr:
                  match g:
                    case (ge, gg):
                      match gg:
                        case (gvs, eq):
                          match gvs:
                            case (gv, gvr):
                              L.scope(~prim, ~ok, p, ds, gd, Core.Pat.step(env, pt, v, pr, vr), F, Step.good(env, pt, v, pr, vr, F, ge, gv, gvr, eq))
        case Core.SPatC{hit, +env, +ps, +vs}:
          match hit:
            case True{}:
              L.scope(~prim, ~ok, p, ds, gd, Core.SPat{env, ps, vs}, F, g)
            case False{}:
              Unit{}

# Each lowered def is scoped by its parameters.
def Names.params(ps: List<&2, Core.Param>, +m: List<&2, Bool>) -> {Law.Pars.names(Core.Lo.params(ps, m)) == Core.Lo.names(ps) : List<&2, String>}:
  match ps:
    case Nil{}:
      {==}
    case p <> r:
      match p:
        case Core.Param{+x, md, ty}:
          %Names.params(r, Core.Lo.tail(m)) : {x <> Law.Pars.names(Core.Lo.params(r, Core.Lo.tail(m))) == x <> _ : List<&2, String>}
          {==}

def Names.bind(ps: List<&2, Core.Param>, +m: List<&2, Bool>)
    -> {Core.Lo.bind(Law.Pars.names(Core.Lo.params(ps, m)), Nil{}) == Core.Lo.bind(Core.Lo.names(ps), Nil{}) : List<&2, String>}:
  %Names.params(ps, m) : {Core.Lo.bind(Law.Pars.names(Core.Lo.params(ps, m)), Nil{}) == Core.Lo.bind(_, Nil{}) : List<&2, String>}
  {==}

def Src.defs(+ms: Map<&2, List<&2, Bool>>, xs: List<&2, Law.Src>, sok: Law.Src.ok(xs)) -> Law.Good.defs(Law.Src.lo(ms, xs)):
  match xs:
    case Nil{}:
      Unit{}
    case x <> r:
      match x:
        case Law.Src{+name, +ps, +body, ret}:
          match sok:
            case (ob, sr):
              (Sc.back(Core.Lo.go(body, ms, Core.Lo.bind(Core.Lo.names(ps), Nil{}), True{}, Nil{}),
                  Core.Lo.bind(Law.Pars.names(Core.Lo.params(ps, Pair.snd(Map<&2, List<&2, Bool>>, List<&2, Bool>, Map.get(List<&2, Bool>, Nil{}, ms, name)))), Nil{}),
                  Core.Lo.bind(Core.Lo.names(ps), Nil{}),
                  Names.bind(ps, Pair.snd(Map<&2, List<&2, Bool>>, List<&2, Bool>, Map.get(List<&2, Bool>, Nil{}, ms, name))),
                  Lo.sc(body, ms, Core.Lo.bind(Core.Lo.names(ps), Nil{}), True{}, Nil{}, ob)),
                Src.defs(ms, r, sr))

def NoU(r: Core.Res, -F: List<&2, String>, g: Law.Good.res(r, F)) -> Law.NoUnbound(r):
  match r:
    case Core.ROk{vs}:
      Unit{}
    case Core.REnv{env}:
      Unit{}
    case Core.RNo{}:
      Unit{}
    case Core.RFail{m}:
      g

def Law.scope_ok(prim, ok, n, ds, gd, s, F, g):
  L.scope(~prim, ~ok, n, ds, gd, s, F, g)

def Prog.lo(~prim: String -> List<&2, Core.Val> -> Core.Res,
    ~ok: @op:String -> @vs:List<&2, Core.Val> -> Law.Goods(vs) -> Law.Good.prim(prim(op, vs)),
    +n: Nat, +ms: Map<&2, List<&2, Bool>>, +xs: List<&2, Law.Src>, sok: Law.Src.ok(xs))
    -> Law.NoUnbound(Core.Prog.run(~prim, n, Law.Src.lo(ms, xs))):
  NoU(Core.Prog.run(~prim, n, Law.Src.lo(ms, xs)), Nil{},
    L.scope(~prim, ~ok, n, Law.Src.lo(ms, xs), Src.defs(ms, xs, sok), Core.SCallDef{"main", Nil{}}, Nil{}, Unit{}))

def Law.lo_prog(prim, ok, n, ms, xs, sok):
  Prog.lo(~prim, ~ok, n, ms, xs, sok)
