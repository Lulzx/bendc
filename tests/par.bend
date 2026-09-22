import Base

# Parallel lets fork onto the worker pool; f!(x) is a parallel call.
def pow2(+n: Nat) -> U32:
  match n:
    case 0n:
      1
    case 1n+p:
      a b = pow2(p) pow2(p)
      (a + b : U32)

def fib(n: Nat) -> Nat:
  match n:
    case 0n:
      0n
    case 1n:
      1n
    case 2n+p:
      +q = p
      a b = fib(1n+q) fib(q)
      Nat.add(a, b)

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(pow2!(22n)))
    IO.print(Nat.show(fib!(25n)))
