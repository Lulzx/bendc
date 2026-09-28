import Base

# Matches on known constructors (Core.Tm.known, after the inliner puts a
# pure's constructor where a bind matches): a case of another constructor is
# dropped, and K's case with a variable per field binds the fields; a field
# pattern that can fail keeps the match.

type P is Data:
  P{a: Nat, b: Nat}

def M.pure(+x: Nat) -> P:
  P{x, (x * 2n : Nat)}

def M.bind(m: P, f: Nat -> Nat) -> Nat:
  match m:
    case P{a, b}:
      f((a + b : Nat))

def N.pure(x: Nat) -> Maybe<Nat>:
  Some{x}

def N.bind(m: Maybe<Nat>, f: Nat -> Nat) -> Nat:
  match m:
    case None{}:
      0n
    case Some{y}:
      f(y)

def B.pure(x: Nat) -> Bool:
  True{}

def B.bind(m: Bool, f: Nat -> Nat) -> Nat:
  match m:
    case False{}:
      1n
    case True{}:
      f(2n)

def O.pure(x: Nat) -> Maybe<Nat>:
  Some{x}

def O.bind(m: Maybe<Nat>, f: Nat -> Nat) -> Nat:
  match m:
    case Some{0n}:
      50n
    case Some{1n+k}:
      f(k)
    case None{}:
      0n

def main() -> Nat:
  +a = M.bind(M.pure(3n), y => (y + 1n : Nat))
  +b = N.bind(N.pure(4n), y => (y * 10n : Nat))
  +c = B.bind(B.pure(5n), y => (y + 100n : Nat))
  +d = O.bind(O.pure(0n), y => y)
  +e = O.bind(O.pure(8n), y => y)
  (a + b + c + d + e : Nat)
