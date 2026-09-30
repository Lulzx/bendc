import Base

type Tree is Data:
  End{}
  Leaf{v: U32}
  Node{l: Tree, r: Tree}

def zip(a: Tree, b: Tree) -> Tree:
  match a b:
    case Leaf{0} Leaf{v}:
      Leaf{U32.add(v, 100)}
    case Leaf{x} Leaf{y}:
      Leaf{U32.add(x, y)}
    case Node{a, b} Node{c, d}:
      l r = zip(a, c) zip(b, d)
      Node{l, r}
    case x y:
      End{}

def sum(t: Tree) -> U32:
  match t:
    case End{}:
      0
    case Leaf{v}:
      v
    case Node{l, r}:
      a b = sum(l) sum(r)
      U32.add(a, b)

def gen(+d: Nat, +v: U32) -> Tree:
  match d:
    case 0n:
      Leaf{v}
    case 1n+p:
      Node{gen(p, v), gen(p, v)}

# The carry is a heap value outside the match; its ownership still matters
# when the first arm matches an immediate.
def carried(t: Tree, carry: Tree) -> Tree:
  match t:
    case End{}:
      carry
    case Leaf{v}:
      carry
    case Node{l, r}:
      carry

# This user name must remain distinct from the compiler's slow entry.
def zip_slow() -> U32:
  42

# The immediate arm allocates and shares heap locals across calls. This
# exercises collection and RC ownership inside the small entry wrapper.
def touch(t: Tree) -> U32:
  match t:
    case Leaf{v}:
      +x = gen(12n, v)
      a b = sum(x) sum(x)
      U32.add(a, b)
    case other:
      0

def repeat(n: Nat) -> U32:
  match n:
    case 0n:
      0
    case 1n+p:
      U32.add(touch(Leaf{3}), repeat(p))

def main() -> IO(Unit):
  +a = gen(10n, 0)
  t = zip!(a, a)
  f = {x => zip(x, Leaf{7}) : Tree -> Tree}
  p = sum(f(Leaf{0}))
  q = sum(zip(Leaf{3}, Leaf{7}))
  r = sum(zip(Node{Leaf{0}, Leaf{3}}, Node{Leaf{7}, Leaf{7}}))
  s = sum(carried(End{}, gen(9n, 3)))
  IO.print(U32.show(U32.add(sum(t), U32.add(p, U32.add(q, U32.add(r, U32.add(s, U32.add(zip_slow(), repeat(40n)))))))))
