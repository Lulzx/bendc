import Base

# A value main that holds functions prints them normalized, as bend does.
def f(x: Nat, y: Nat) -> Nat:
  match x:
    case 0n:
      y
    case 1n+p:
      f(p, 1n+y)

def adder(k: U32) -> U32 -> U32:
  x => (x + k : U32)

type Box is Type:
  B{g: Nat -> Nat}

def main() -> (Nat -> Nat) & (Nat -> Nat) & Box & (U32 -> U32 -> U32) & (U32 -> U32):
  (f(3n), x => f(x, 2n), B{+x => Nat.mul(x, x)}, U32.add, adder(2))
