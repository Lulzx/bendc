import Base

type Tree is Data:
  Leaf{n: Nat}
  Branch{left: Tree, right: Tree}

def fold(t: Tree) -> Nat:
  match t:
    case Leaf{n}:
      n
    case Branch{a,b}:
      x y = fold(a) fold(b)
      Nat.add(x,y)

def main() -> Nat:
  fold(Branch{Leaf{3n},Leaf{4n}})
