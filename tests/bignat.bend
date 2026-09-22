import Base

# Nat is unbounded (the expected output comes from Python: the official
# runtime stops at 2^48).
def fact(n: Nat) -> Nat:
  match n:
    case 0n:
      1n
    case 1n+p:
      Nat.mul(1n+p, fact(p))

def main() -> IO(Unit):
  +f = fact(30n)
  +big = Nat.pow(2n, 200n)
  do IO<Unit>:
    IO.print(Nat.show(f))
    IO.print(Nat.show(Nat.div(f, fact(28n))))
    IO.print(Nat.show(Nat.sub(big, 1n)))
    IO.print(Nat.show(Nat.mod(Nat.pow(3n, 300n), Nat.pow(10n, 40n))))
    IO.print(Nat.show(Nat.div(Nat.pow(7n, 90n), Nat.pow(3n, 70n))))
    IO.print(U32.show(U32.from_nat(big)))
    IO.print(Bool.show(Nat.is_lt(f, big)))
