import Base
# Opt's min/max reassociation (m in BEND_OPT): a min or max of three U32s
# whose operand from the iteration before goes outermost. The DP cell reads
# its left neighbour from the array it writes; the loops carry a min and a
# max in a parameter. Ties and equal operands included.

def umin.go(x: U32, y: U32, lt: Bool) -> U32:
  match lt:
    case True{}:
      x
    case False{}:
      y

def umin(+x: U32, +y: U32) -> U32:
  umin.go(x, y, U32.is_lt(x, y))

def umax.go(x: U32, y: U32, gt: Bool) -> U32:
  match gt:
    case False{}:
      y
    case True{}:
      x

def umax(+x: U32, +y: U32) -> U32:
  umax.go(x, y, U32.is_gt(x, y))

def cell.f(+j: U32, +up: U32, cur: Array<U32> & U32) -> Array<U32>:
  (row, left) = cur
  v = umin(umin(U32.inc(up), U32.inc(left)), U32.add(j, 3))
  row[U32.inc(j)] <- v

def cells(+n: Nat, +j: U32, row: Array<U32>) -> Array<U32>:
  match n:
    case 0n:
      row
    case 1n+q:
      cells(q, U32.inc(j), cell.f(j, U32.mul(U32.and(j, 3), 2), Array.get(U32, row, j)))

def last(r: Array<U32> & U32) -> U32:
  (row, x) = r
  x

def lo(+n: Nat, +i: U32, +acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n+q:
      +a = U32.and(U32.mul(i, 2654435761), 1023)
      lo(q, U32.inc(i), umin(umin(a, acc), U32.add(U32.and(i, 7), 500)))

def hi(+n: Nat, +i: U32, +acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n+q:
      +a = U32.and(U32.mul(i, 40503), 4095)
      hi(q, U32.inc(i), umax(U32.and(i, 15), umax(acc, a)))

def dp() -> U32:
  last(Array.get(U32, cells(40n, 0, [5 : U32*64n]), 40))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(dp()))
    IO.print(U32.show(lo(1000n, 0, 4000000000)))
    IO.print(U32.show(hi(1000n, 0, 0)))
