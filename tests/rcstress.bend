import Base

# Reference counts under threads: each of 320 rounds forks a tree of
# parallel lets whose branches share a string and a list (the threads take
# and drop references to them at once, and closures capture them), then drops the tree.
# tests/rcstress.env gives it a one-megabyte heap.
type Tree is Data:
  Leaf{v: U32}
  Node{l: Tree, r: Tree}

def build(+n: Nat, +x: U32) -> List<&2, U32>:
  match n:
    case 0n:
      Nil{}
    case 1n+ +p:
      (x + U32.from_nat(p) : U32) <> build(p, x)

def total(xs: List<&2, U32>) -> U32:
  match xs:
    case Nil{}:
      0
    case h <> t:
      (h + total(t) : U32)

def app(f: U32 -> U32, x: U32) -> U32:
  f(x)

def grow(+d: Nat, +s: String, +xs: List<&2, U32>, +x: U32) -> Tree:
  match d:
    case 0n:
      Leaf{app(y => (y + (total(xs) + U32.from_nat(String.length(s)) : U32) : U32), x)}
    case 1n+ +p:
      l r = grow(p, s, xs, (x * 2 : U32)) grow(p, s ++ "x", 1 <> xs, (x * 2 + 1 : U32))
      Node{l, r}

def sum(t: Tree) -> U32:
  match t:
    case Leaf{v}:
      v
    case Node{l, r}:
      a b = sum(l) sum(r)
      (a + b : U32)

def round(+k: U32) -> U32:
  +s = String.repeat("ab", 20n)
  +xs = build(30n, k)

  sum(grow(9n, s, xs, k))

def rounds(+n: Nat, acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n+ +p:
      rounds(p, (acc * 31 + round(U32.from_nat(p)) : U32))

def main() -> IO(Unit):
  IO.print(U32.show(rounds(320n, 0)))
