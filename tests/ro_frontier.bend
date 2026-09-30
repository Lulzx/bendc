import Base

type Tree is Data:
  Leaf{v: U32}
  Node{l: Tree, r: Tree}

def gen(+d: Nat, +v: U32) -> Tree:
  match d:
    case 0n:
      Leaf{v}
    case 1n+p:
      l r = gen(p, v) gen(p, v)
      Node{l, r}

def read(t: Tree) -> U32:
  match t:
    case Leaf{v}:
      v
    case Node{l, r}:
      U32.add(read(l), read(r))

# Both trees are read-only through recursive, parallel calls.
def zip(+a: Tree, +b: Tree) -> Tree:
  match a b:
    case Leaf{x} Leaf{y}:
      Leaf{U32.mul(x, y)}
    case Node{a, b} Node{c, d}:
      l r = zip(a, c) zip(b, d)
      Node{l, r}
    case x y:
      Leaf{0}

# b escapes on a mismatch, so its clone must own b while borrowing a.
def mixed(+a: Tree, +b: Tree) -> Tree:
  match a b:
    case Node{a, b} Node{c, d}:
      l r = mixed(a, c) mixed(b, d)
      Node{l, r}
    case x y:
      y

# A local callable shadows this global def and takes the same arity.
def shadow(shadow: Tree -> Tree -> Tree, +t: Tree) -> Tree:
  l r = shadow(Leaf{1}, Leaf{2}) read(t)
  Node{l, Leaf{r}}

def main() -> IO(Unit):
  +a = gen(8n, 3)
  +b = gen(8n, 7)
  +p = zip(a, b)
  +q = mixed(a, b)
  f = {x => y => Node{x, y} : Tree -> Tree -> Tree}
  r = shadow(f, gen(5n, 11))
  IO.print(U32.show(U32.add(read(p), U32.add(read(p), U32.add(read(q), U32.add(read(q), U32.add(read(a), U32.add(read(b), read(r)))))))))
