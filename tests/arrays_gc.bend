import Base
# Two 1024-cell arrays (large objects to the collector) per leaf of a
# parallel tree, with a collection every megabyte (arrays_gc.env): a thread
# stopped by a collection while it unlocks after allocating an array holds
# only the array's block header, which must keep the array alive.

def fill(+j: Nat, +s: U32, g: Array<U32>) -> Array<U32>:
  match j:
    case 0n:
      g
    case 1n+p:
      +c = U32.from_nat(p)
      fill(p, s, g[c] <- U32.add(s, c))

def sum.go(+j: Nat, r: Array<U32> & U32, acc: U32) -> U32:
  match j:
    case 0n:
      acc
    case 1n+p:
      (g, v) = r
      sum.go(p, g[U32.from_nat(p)], U32.add(U32.mul(acc, 31), v))

def leaf(+i: U32) -> U32:
  g = fill(1024n, i, [0 : U32*1024n])
  h = fill(1024n, U32.mul(i, 7), [0 : U32*1024n])
  U32.add(sum.go(1024n, g[1023], 0), sum.go(1024n, h[1023], 0))

def batch(+k: Nat, +i: U32) -> U32:
  match k:
    case 0n:
      leaf(i)
    case 1n+p:
      a b = batch(p, i) batch(p, U32.add(i, U32.shln(1, p)))
      U32.add(a, b)

def main() -> U32:
  batch(12n, 0)
