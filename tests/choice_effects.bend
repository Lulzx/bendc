import Base

type Twig is Data:
  Leaf{v: U32}
  Node{l: Twig, r: Twig}

def mark(+x: U32) -> IO(U32):
  do IO<U32>:
    IO.print(U32.show(x))
    IO.pure(U32, x)

def effect_case(t: Bool) -> IO(Twig):
  match t:
    case False{}:
      do IO<Twig>:
        x : U32 <- mark(11)
        IO.pure(Twig, Node{Leaf{x}, Leaf{12}})
    case True{}:
      do IO<Twig>:
        y : U32 <- mark(21)
        IO.pure(Twig, Node{Leaf{22}, Leaf{y}})

def fold(t: Twig) -> U32:
  match t:
    case Leaf{x}:
      x
    case Node{l, r}:
      U32.add(U32.mul(fold(l), 13), U32.mul(fold(r), 37))

def main() -> IO(Unit):
  do IO<Unit>:
    a : Twig <- effect_case(False{})
    b : Twig <- effect_case(True{})
    IO.print(U32.show(U32.add(fold(a), fold(b))))
