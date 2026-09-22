import Base

def replicate(-A: Data, n: Nat, +x: A) -> List<A>:
  match n:
    case 0n:
      Nil{}
    case 1n+p:
      x <> replicate(A, p, x)

def main() -> List<U32>:
  replicate(U32, 3n, 7)
