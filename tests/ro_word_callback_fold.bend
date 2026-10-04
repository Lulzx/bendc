import Base

type Tree is Data:
  Leaf{value: U32}
  Branch{left: Tree, right: Tree}

def effect(f: Tree -> U32, t: Tree) -> U32:
  match t:
    case Branch{a,b}:
      x y = f(a) U32.inc(0)
      U32.add(x,y)
    case leaf:
      f(leaf)

def main() -> U32:
  f = {x => 3 : Tree -> U32}
  effect(f,Branch{Leaf{1},Leaf{2}})
