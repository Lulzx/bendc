import Base

# Allocates about 2 GB in total; the collector keeps the heap small.
def build(+n: Nat, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      build(p, U32.from_nat(p) <> acc)

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case Con{h, t}:
      sum(t, (acc + h : U32))

def loop(k: Nat, acc: U32) -> U32:
  match k:
    case 0n:
      acc
    case 1n+p:
      loop(p, (acc + sum(build(100000n, []), 0) : U32))

def main() -> IO(Unit):
  IO.print(U32.show(loop(800n, 0)))
