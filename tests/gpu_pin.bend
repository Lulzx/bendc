import Base

# Results that stay in the device's arena (tests/gpu_pin.env pins every
# one): the CPU reads them in place, and later calls take them back.

type Tree is Data:
  Leaf{v: U32}
  Node{h: U32, l: Tree, r: Tree}

def mk(d: Nat, +b: U32) -> Tree:
  match d:
    case 0n:
      Leaf{(b * 7 : U32)}
    case 1n+p:
      +q = p
      l r = mk(q, (b * 2 : U32)) mk(q, (b * 2 + 1 : U32))
      Node{b, l, r}

def sum(t: Tree) -> U32:
  match t:
    case Leaf{v}:
      v
    case Node{h, l, r}:
      a c = sum(l) sum(r)
      (h + a + c : U32)

# A tree holding the argument twice: new nodes over pinned ones.
def twice(t: Tree, +k: U32) -> Tree:
  match t:
    case Leaf{+v}:
      Node{k, Leaf{v}, Leaf{(v + k : U32)}}
    case Node{h, l, r}:
      Node{(h + k : U32), twice(l, k), r}

def pairs(n: Nat) -> List<(U32 & U32)>:
  match n:
    case 0n:
      []
    case 1n+p:
      +q = p
      (U32.from_nat(q), (U32.from_nat(q) * 3 : U32)) <> pairs(q)

def psum(xs: List<(U32 & U32)>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      (a, b) = x
      psum(t, (acc + a + b : U32))

def main() -> IO(Unit):
  t = mk!(12n, 1)
  u = twice!(t, 5)
  +w = twice!(u, 9)
  do IO<Unit>:
    IO.print(U32.show(sum(w)))
    IO.print(U32.show(sum!(w)))
    IO.print(U32.show(psum(pairs!(20n), 0)))
