import Base
type Z is Data:
  Leaf{x: Nat, y: Nat}
  Fork{l: Z, r: Z}
def combine(a: Z, b: Z) -> Z:
  match a b:
    case Leaf{a, b} Leaf{c, d}:
      Leaf{Nat.add(a, c), Nat.add(b, d)}
    case Leaf{a, b} Fork{c, d}:
      Leaf{a, b}
    case Fork{a, b} Leaf{c, d}:
      Fork{a, b}
    case Fork{a, b} Fork{c, d}:
      l r = combine(a, c) combine(b, d)
      Fork{l, r}
def tree(n: Nat, +x: Nat) -> Z:
  match n:
    case 0n:
      Leaf{x, x}
    case 1n+p:
      +q = tree(p, x)
      Fork{q, q}
def sum(z: Z) -> Nat:
  match z:
    case Leaf{a, b}:
      Nat.add(a, b)
    case Fork{a, b}:
      Nat.add(sum(a), sum(b))
def run() -> Nat:
  sum(combine(tree(3n, Nat.add(Nat.mul(65536n, 65536n), 1n)), tree(3n, Nat.add(Nat.mul(1048576n, 1048576n), 3n))))
def main() -> IO(Unit):
  IO.print(Nat.show(run!()))
