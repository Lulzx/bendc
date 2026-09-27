import Base

# A Nat reaches 2^48 - 1, the official runtime's largest immediate; a
# result past it stops the program with an error (exit 1).
def fact(+n: Nat) -> Nat:
  match n:
    case 0n:
      1n
    case 1n+p:
      Nat.mul(1n+p, fact(p))

def main() -> IO(Unit):
  +f = fact(16n)
  +h = Nat.pow(2n, 47n)
  +top = Nat.add(h, Nat.sub(h, 1n))
  do IO<Unit>:
    IO.print(Nat.show(f))
    IO.print(Nat.show(Nat.div(f, fact(14n))))
    IO.print(Nat.show(top))
    IO.print(Nat.show(Nat.mod(top, Nat.pow(10n, 9n))))
    IO.print(U32.show(U32.from_nat(top)))
    IO.print(Bool.show(Nat.is_lt(f, top)))
    IO.print(Nat.show(Nat.add(top, 1n)))
    IO.print("unreached")
