import Base

# Unboxing splits a pair parameter into its halves. A half's type comes
# from the parameter's type arguments: the U32 half of `Array<U32> & U32`
# is a U32 (a uint32_t, never shared) even where the loop does not use it,
# and an array half stays an array. Each result is the program's own.

type Two<a, -A: Kind(a), -B: Kind(a)> is Kind(a):
  Two{x: A, y: B}

# the U32 half unused on every step
def fill(+j: Nat, r: Array<U32> & U32) -> Array<U32>:
  match j:
    case 0n:
      (h, z) = r
      h
    case 1n+q:
      (h, z) = r
      +i = U32.from_nat(q)
      fill(q, Array.swap(U32, h, i, U32.mul(i, 3)))

# the U32 half used
def sum(+j: Nat, r: Array<U32> & U32, acc: U32) -> U32:
  match j:
    case 0n:
      (a, x) = r
      U32.add(acc, x)
    case 1n+q:
      (a, x) = r
      sum(q, Array.get(U32, a, U32.from_nat(q)), U32.add(acc, x))

# a named type's parameters: y is a U32 here, x an array
def walk(+j: Nat, t: Two<&1, Array<U32>, U32>) -> U32:
  match j:
    case 0n:
      Two{x, y} = t
      sum(16n, (x, 0), y)
    case 1n+q:
      Two{x, +y} = t
      walk(q, Two{Array.set(U32, x, U32.from_nat(q), U32.add(y, U32.from_nat(q))), U32.inc(y)})

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(sum(16n, (fill(16n, (Array.new(U32, 4n, 0), 0)), 0), 0)))
    IO.print(U32.show(walk(16n, Two{Array.new(U32, 4n, 1), 5})))
