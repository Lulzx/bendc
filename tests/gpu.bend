import Base

type Tree is Data:
  Leaf{v: U32}
  Node{l: Tree, r: Tree}

def pow2(n: Nat) -> U32:
  match n:
    case 0n:
      1
    case 1n+p:
      +q = p
      a b = pow2(q) pow2(q)
      (a + b : U32)

@unsafe
def fib(n: Nat) -> Nat:
  match n:
    case 0n:
      0n
    case 1n:
      1n
    case 2n+p:
      +q = p
      a b = fib((1n + q : Nat)) fib(q)
      (a + b : Nat)

def tree(n: Nat, v: U32) -> Tree:
  match n:
    case 0n:
      Leaf{v}
    case 1n+p:
      +q = p
      +w = v
      a b = tree(q, (w * 2 : U32)) tree(q, (w * 2 + 1 : U32))
      Node{a, b}

def tsum(t: Tree) -> U32:
  match t:
    case Leaf{v}:
      v
    case Node{l, r}:
      a b = tsum(l) tsum(r)
      (a + b : U32)

def range(n: Nat, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      +q = p
      range(q, U32.from_nat(q) <> acc)

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      sum(t, (acc + x : U32))

def fsum(n: Nat, acc: F32) -> F32:
  match n:
    case 0n:
      acc
    case 1n+p:
      fsum(p, (acc + 0.5 : F32))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(pow2!(16n)))
    IO.print(Nat.show(fib!(20n)))
    IO.print(U32.show(tsum!(tree!(10n, 1))))
    IO.print(U32.show(sum!(range(1000n, []), 0)))
    IO.print(F32.show(fsum!(100n, 0.0)))
    IO.print(String.concat(["gpu", "!"]))
