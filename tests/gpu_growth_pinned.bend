import Base

# Child tasks retain tree results until their parent consumes them. Repeated
# producers must keep their saved frames and values across arena growth.
# Read a pinned result on CPU and GPU before and after later calls grow the
# arena, distinguishing its initial layout from its retained lifetime.
type Tree is Data:
  Leaf{v: U32}
  Node{l: Tree, r: Tree}

def make(n: Nat, +v: U32) -> Tree:
  match n:
    case 0n:
      Leaf{v}
    case 1n+p:
      +q = p
      a b = make(q, U32.inc(v)) make(q, U32.add(v, 2))
      Node{a, b}

def sum(t: Tree) -> U32:
  match t:
    case Leaf{v}:
      v
    case Node{l, r}:
      U32.add(sum(l), sum(r))

def rounds(n: Nat, acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n+p:
      +q = p
      value = sum(make(14n, 1))
      rounds(q, U32.add(acc, value))

def main() -> IO(Unit):
  +keep = make!(13n, 3)
  do IO<Unit>:
    IO.print(U32.show(sum(keep)))
    IO.print(U32.show(sum!(keep)))
    IO.print(U32.show(rounds!(8n, 0)))
    IO.print(U32.show(rounds!(5n, 9)))
    IO.print(U32.show(sum(keep)))
    IO.print(U32.show(sum!(keep)))
