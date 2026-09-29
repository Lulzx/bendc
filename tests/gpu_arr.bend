import Base

# Arrays on the device: U32 ones are narrow there (32-bit cells, see
# K_ARR_NW in rt/gpu.h), others are words; a narrow one the CPU gets back
# is widened; indices wrap; a clone is a new array; a CPU array is read in
# place.

def fill(j: Nat, +m: U32, a: Array<U32>) -> Array<U32>:
  match j:
    case 0n:
      a
    case 1n+q:
      +p = q
      +i = U32.from_nat(p)
      fill(p, m, Array.set(U32, a, i, (i * m + 1 : U32)))

def sum(j: Nat, +k: U32, r: Array<U32> & U32, acc: U32) -> U32:
  match j:
    case 0n:
      acc
    case 1n+q:
      (a, x) = r
      +p = q
      sum(p, k, Array.get(U32, a, (U32.from_nat(p) + k : U32)), (acc * 31 + x : U32))

def total(a: Array<U32>, +n: Nat, +k: U32) -> U32:
  sum(n, k, Array.get(U32, a, k), 0)

def lit(+k: U32) -> U32:
  total(fill(16n, 3, [k : U32*16n]), 16n, 64)

def mk(+k: U32) -> Array<U32>:
  fill(12n, k, Array.new(U32, 4n, k))

def nfill(j: Nat, a: Array<Nat>) -> Array<Nat>:
  match j:
    case 0n:
      a
    case 1n+q:
      +p = q
      nfill(p, Array.set(Nat, a, U32.from_nat(p), (p * p + 7n : Nat)))

def nsum(j: Nat, r: Array<Nat> & Nat, acc: Nat) -> Nat:
  match j:
    case 0n:
      acc
    case 1n+q:
      (a, x) = r
      +p = q
      nsum(p, Array.get(Nat, a, U32.from_nat(p)), (acc * 3n + x : Nat))

def wide(+n: Nat) -> Nat:
  nsum(8n, Array.get(Nat, nfill(8n, Array.new(Nat, 3n, n)), 9), 0n)

def both(r: Array<U32> & Array<U32>) -> U32:
  (a, b) = r
  (total(a, 16n, 1) + total(fill(4n, 5, b), 16n, 2) : U32)

def cl(+k: U32) -> U32:
  both(Array.clone(U32, fill(16n, k, Array.new(U32, 4n, 0))))

def main() -> IO(Unit):
  c = fill(16n, 7, Array.new(U32, 4n, 0))
  d = fill(16n, 7, Array.new(U32, 4n, 0))
  do IO<Unit>:
    IO.print(U32.show(lit!(9)))
    IO.print(U32.show(total(mk!(5), 16n, 3)))
    IO.print(Nat.show(wide!(2n)))
    IO.print(U32.show(cl!(11)))
    IO.print(U32.show(total!(c, 16n, 5)))
    IO.print(U32.show(total(d, 16n, 5)))
