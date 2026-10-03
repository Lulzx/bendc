import Base
type Z is Data:
  Leaf{x: U32, y: U32}
  Fork{l: Z, r: Z}
def combine(a: Z, b: Z) -> Z:
  match a b:
    case Leaf{a, b} Leaf{c, d}:
      Leaf{U32.add(a, c), U32.xor(b, d)}
    case Leaf{a, b} Fork{c, d}:
      Leaf{a, b}
    case Fork{a, b} Leaf{c, d}:
      Fork{a, b}
    case Fork{a, b} Fork{c, d}:
      l r = combine(a, c) combine(b, d)
      Fork{l, r}
def tree(n: Nat, +x: U32) -> Z:
  match n:
    case 0n:
      Leaf{x, x}
    case 1n+p:
      +q = tree(p, x)
      Fork{q, q}
def sum(z: Z) -> U32:
  match z:
    case Leaf{a, b}:
      U32.add(a, b)
    case Fork{a, b}:
      U32.add(sum(a), sum(b))
def run() -> U32:
  sum(combine(tree(3n, 10), tree(3n, 19)))
type W is Data:
  WLeaf{x: Nat, y: Nat}
  WFork{l: W, r: W}
def wcombine(a: W, b: W) -> W:
  match a b:
    case WLeaf{a, b} WLeaf{c, d}:
      WLeaf{Nat.add(a, c), Nat.add(b, d)}
    case WLeaf{a, b} WFork{c, d}:
      WLeaf{a, b}
    case WFork{a, b} WLeaf{c, d}:
      WFork{a, b}
    case WFork{a, b} WFork{c, d}:
      l r = wcombine(a, c) wcombine(b, d)
      WFork{l, r}
def wtree(n: Nat, +x: Nat) -> W:
  match n:
    case 0n:
      WLeaf{x, x}
    case 1n+p:
      +q = wtree(p, x)
      WFork{q, q}
def wsum(z: W) -> Nat:
  match z:
    case WLeaf{a, b}:
      Nat.add(a, b)
    case WFork{a, b}:
      Nat.add(wsum(a), wsum(b))
def wrun() -> Nat:
  wsum(wcombine(wtree(3n, Nat.add(Nat.mul(65536n, 65536n), 1n)), wtree(3n, Nat.add(Nat.mul(1048576n, 1048576n), 3n))))
def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(run!()))
    IO.print(Nat.show(wrun!()))
