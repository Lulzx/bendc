import Base

type Tree is Data:
  Empty{}
  Leaf{anchor: Tree, value: U32}
  Branch{left: Tree, right: Tree}

def gen(d: Nat) -> Tree:
  match d:
    case 0n:
      Leaf{Empty{},7}
    case 1n+ +p:
      l r = gen(p) gen(p)
      Branch{l,r}

def fold(t: Tree) -> U32:
  match t:
    case Empty{}:
      0
    case Leaf{a,v}:
      v
    case Branch{a,b}:
      x y = fold(a) fold(b)
      U32.add(x,y)

def pointer(t: Tree) -> Tree:
  match t:
    case Branch{a,b}:
      x y = pointer(a) pointer(b)
      x
    case other:
      other

def main() -> U32:
  +t = gen(6n)
  U32.add(fold(t), fold(pointer(t)))
