import Base

type Twig is Data:
  End{}
  Leaf{v: U32}
  Other{v: U32}
  Node{l: Twig, r: Twig}

def choose(t: Bool, x: U32, y: U32) -> Twig:
  match t:
    case False{}:
      Node{Leaf{x}, Other{y}}
    case True{}:
      Node{Other{y}, Leaf{x}}

# A call in an alternative payload must keep the original control flow.
def call_case(t: Bool, x: U32, y: U32) -> Twig:
  match t:
    case False{}:
      Node{Leaf{x}, Other{U32.add(y, 1)}}
    case True{}:
      Node{Other{y}, Leaf{x}}

def fold(t: Twig) -> U32:
  match t:
    case End{}:
      1
    case Leaf{x}:
      U32.add(x, 17)
    case Other{x}:
      U32.xor(x, 263)
    case Node{l, r}:
      U32.add(U32.mul(fold(l), 13), U32.mul(fold(r), 37))

def alias(+s: Bool, +x: U32, +y: U32) -> U32:
  +t = choose(s, x, y)
  U32.add(U32.add(fold(t), fold(t)), fold(call_case(s, x, y)))

def loop(d: Nat, +x: U32, +y: U32) -> U32:
  match d:
    case 0n:
      U32.add(alias(U32.is_gt(x, y), x, y), alias(U32.is_le(x, y), x, y))
    case 1n+p:
      U32.add(U32.add(alias(U32.is_gt(x, y), x, y), alias(U32.is_le(x, y), x, y)),
        loop(p, U32.add(x, 65535), U32.mul(y, 2654435761)))

def main() -> U32:
  loop(30n, 4294967295, 65535)
