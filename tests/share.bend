import Base

# Values used more than once while matches free the nodes they open: a
# shared tree matched twice, a list a closure captures and a call reads, a
# tree both halves of a parallel let read, nodes freed and reused.
type Tree is Data:
  Leaf{}
  Node{l: Tree, v: U32, r: Tree}

def build(+n: Nat, +k: U32) -> Tree:
  match n:
    case 0n:
      Leaf{}
    case 1n+p:
      Node{build(p, (k * 2 : U32)), k, build(p, ((k * 2 : U32) + 1 : U32))}

def sum(t: Tree) -> U32:
  match t:
    case Leaf{}:
      0
    case Node{l, v, r}:
      ((sum(l) + v : U32) + sum(r) : U32)

def mirror(t: Tree) -> Tree:
  match t:
    case Leaf{}:
      Leaf{}
    case Node{l, v, r}:
      Node{mirror(r), v, mirror(l)}

def leftmost(t: Tree) -> U32:
  match t:
    case Leaf{}:
      0
    case Node{Leaf{}, v, r}:
      v
    case Node{l, v, r}:
      leftmost(l)

def range(+n: Nat, acc: List<&2, U32>) -> List<&2, U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      range(p, U32.from_nat(p) <> acc)

def total(xs: List<&2, U32>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case h <> t:
      total(t, (acc + h : U32))

def adder(+xs: List<&2, U32>) -> U32 -> U32:
  x => (total(xs, 0) + x : U32)

def both(+t: Tree) -> U32:
  a b = sum(t) sum(mirror(t))
  (a + b : U32)

def rounds(k: Nat, +acc: U32) -> U32:
  match k:
    case 0n:
      acc
    case 1n+p:
      +t = build(12n, 1)
      rounds(p, ((acc + sum(t) : U32) + leftmost(mirror(t)) : U32))

def main() -> IO(Unit):
  +t = build(10n, 1)
  +xs = range(1000n, Nil{})
  f = adder(xs)
  do IO<Unit>:
    IO.print(U32.show(sum(t)))
    IO.print(U32.show(sum(mirror(t))))
    IO.print(U32.show(leftmost(t)))
    IO.print(U32.show(leftmost(mirror(t))))
    IO.print(U32.show(f(1)))
    IO.print(U32.show(total(xs, 2)))
    IO.print(U32.show(both(t)))
    IO.print(U32.show(rounds(50n, 0)))
