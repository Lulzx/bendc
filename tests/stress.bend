import Base

def build(n: Nat) -> List<&2, U32>:
  match n:
    case 0n:
      Nil{}
    case 1n+ +p:
      U32.from_nat(p) <> build(p)

def total(xs: List<&2, U32>) -> U32:
  match xs:
    case Nil{}:
      0
    case h <> t:
      (h + total(t) : U32)

def fib(n: Nat) -> U32:
  match n:
    case 0n:
      0
    case 1n:
      1
    case 2n+ +p:
      a b = fib(1n+p) fib(p)
      (a + b : U32)

def main() -> IO(Unit):
  +xs = build(5000n)
  +s = String.repeat("abc", 2000n)
  do IO<Unit>:
    IO.print(U32.show(total(xs)))
    IO.print(Nat.show(String.length(String.append(s, s))))
    IO.print(U32.show(fib(27n)))
