import Base

# Two closed recursive types reuse constructor tags with different layouts.
# Reductions allocate temporary trees; fields must be traced by their type.
type Red is Data:
  RLeaf{value: U32, stamp: Nat}
  RFork{l: Red, r: Red}

type Blue is Data:
  BLeaf{value: U32}
  BFork{value: U32, l: Blue, r: Blue}

def red(n: Nat, v: U32) -> Red:
  match n:
    case 0n:
      RLeaf{v, 42n}
    case 1n+p:
      +q = p
      +w = v
      a b = red(q, w) red(q, w)
      RFork{a, b}

def zip(a: Red, b: Red) -> Red:
  match a b:
    case RLeaf{x, t} RLeaf{y, u}:
      RLeaf{U32.add(x, y), t}
    case RFork{al, ar} RFork{bl, br}:
      l r = zip(al, bl) zip(ar, br)
      RFork{l, r}
    case RLeaf{x, t} RFork{bl, br}:
      RLeaf{x, t}
    case RFork{al, ar} RLeaf{y, u}:
      RFork{al, ar}

def reduce(n: Nat) -> Red:
  match n:
    case 0n:
      red(2n, 1)
    case 1n+p:
      +q = p
      a b = reduce(q) reduce(q)
      zip(a, b)

def rsum(t: Red) -> U32:
  match t:
    case RLeaf{x, stamp}:
      U32.add(x, U32.from_nat(stamp))
    case RFork{l, r}:
      U32.add(rsum(l), rsum(r))

def blue(n: Nat, v: U32) -> Blue:
  match n:
    case 0n:
      BLeaf{v}
    case 1n+p:
      +q = p
      +w = v
      a b = blue(q, w) blue(q, w)
      BFork{7, a, b}

def bsum(t: Blue) -> U32:
  match t:
    case BLeaf{x}:
      x
    case BFork{x, l, r}:
      U32.add(x, U32.add(bsum(l), bsum(r)))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(rsum(reduce!(8n))))
    IO.print(U32.show(bsum(blue!(8n, 3))))
