import Base

# The inliner's rules: a monad's bind and pure inlined, a match on a known
# constructor resolved (not when a field's pattern can fail: the next case
# is taken then), an applied lambda made a let.

def M.pure(x: Nat) -> Maybe<Nat>:
  Some{x}

def M.bind(m: Maybe<Nat>, f: Nat -> Nat) -> Nat:
  match m:
    case Some{1n+k}:
      f(k)
    case Some{0n}:
      100n
    case None{}:
      0n

def known(x: Nat) -> Nat:
  M.bind(M.pure(x), y => (y + 1n : Nat))

def beta(x: Nat) -> Nat:
  (y => (y * 3n : Nat))((x + 1n : Nat))

def main() -> Nat:
  (known(0n) + known(5n) + beta(4n) : Nat)
