import Base

def f(x: Nat) -> Nat:
  match x:
    case 0n:
      0n
    case 1n+p:
      f(1n+p)

def main() -> Nat:
  f(3n)
