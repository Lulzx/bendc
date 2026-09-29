import Base

# Automatic parallelism over blocks: no parallel let is written here.
type Tree is Data:
  Leaf{v: U32}
  Node{l: Tree, r: Tree}

def gen(d: Nat, +s: U32) -> Tree:
  match d:
    case 0n:
      Leaf{(s * 2654435761 + 12345 : U32)}
    case 1n+p:
      +q = p
      l = gen(q, (s * 2 : U32))
      r = gen(q, (s * 2 + 1 : U32))
      Node{l, r}

# independent lets whose results a helper joins
def sum(t: Tree) -> U32:
  match t:
    case Leaf{v}:
      v
    case Node{l, r}:
      a = sum(l)
      b = sum(r)
      +m = (a * 3 : U32)
      (m + b + 1 : U32)

# a def that only joins recursive calls forks them too
def both(a: Tree, b: Tree) -> U32:
  x = sum(a)
  y = sum(b)
  U32.xor(x, y)

# calls after a let they read, and a tail call that stays a loop
def walk(n: Nat, +k: U32, acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n+p:
      +s = (k * 7 + 1 : U32)
      x = sum(gen(4n, s))
      y = sum(gen(4n, (s + 1 : U32)))
      walk(p, s, (acc + U32.xor(x, y) : U32))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(sum(gen(18n, 1))))
    IO.print(U32.show(both(gen(12n, 3), gen(12n, 5))))
    IO.print(U32.show(walk(20000n, 1, 0)))
