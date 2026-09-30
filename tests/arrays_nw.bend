import Base
# Arrays of scalars (U32, F32, Bool, Char) that Array.new makes with a
# scalar type have 32-bit cells (narrow, see ARR_NW in rt/bendrt.h). Here
# with the generic accessors (a def whose type is a variable), with wide
# arrays of scalars (Array.map makes its result with Array.new(U, ...),
# which bendc does not specialize),
# with ANode and ALeaf matches and builds, clones, forks, atomics, and
# under a collection every megabyte (arrays_nw.env) while a parallel tree
# holds narrow arrays in lists.

def fill(+j: Nat, +s: U32, g: Array<U32>) -> Array<U32>:
  match j:
    case 0n:
      g
    case 1n+p:
      +c = U32.from_nat(p)
      fill(p, s, g[c] <- U32.add(U32.mul(s, 2654435761), c))

def sum.go(+j: Nat, r: Array<U32> & U32, acc: U32) -> U32:
  match j:
    case 0n:
      acc
    case 1n+p:
      (g, v) = r
      sum.go(p, g[U32.from_nat(p)], U32.add(U32.mul(acc, 31), v))

def sum(+n: Nat, a: Array<U32>) -> U32:
  sum.go(n, a[U32.from_nat(n)], 0)

# (generic: Array.get and Array.set of a type variable)
def gsum.go(~T: Data, ~f: T -> U32, +j: Nat, r: Array<T> & T, acc: U32) -> U32:
  match j:
    case 0n:
      acc
    case 1n+p:
      (g, v) = r
      gsum.go(~T, ~f, p, Array.get(T, g, U32.from_nat(p)), U32.add(U32.mul(acc, 31), f(v)))

def gsum(~T: Data, ~f: T -> U32, +n: Nat, a: Array<T>) -> U32:
  gsum.go(~T, ~f, n, Array.get(T, a, U32.from_nat(n)), 0)

def gset(~T: Data, +j: Nat, v: T, a: Array<T>) -> Array<T>:
  match j:
    case 0n:
      a
    case 1n+p:
      +w = v
      gset(~T, p, w, Array.set(T, a, U32.mul(U32.from_nat(p), 2), w))

def lsum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case h <> t:
      lsum(t, U32.add(U32.mul(acc, 7), h))

def u32id(x: U32) -> U32:
  x

def b2u(b: Bool) -> U32:
  match b:
    case False{}:
      0
    case True{}:
      1

def c2u(c: Char) -> U32:
  match c:
    case Chr{x}:
      x

def fsum.go(+j: Nat, r: Array<F32> & F32, acc: F32) -> F32:
  match j:
    case 0n:
      acc
    case 1n+p:
      (g, v) = r
      fsum.go(p, Array.get(F32, g, U32.from_nat(p)), F32.add(acc, v))

def ffill(+j: Nat, g: Array<F32>) -> Array<F32>:
  match j:
    case 0n:
      g
    case 1n+p:
      +c = U32.from_nat(p)
      ffill(p, Array.set(F32, g, c, F32.mul(U32.to_f32(c), 0.5)))

def bfill(+j: Nat, g: Array<Bool>) -> Array<Bool>:
  match j:
    case 0n:
      g
    case 1n+p:
      +c = U32.from_nat(p)
      bfill(p, Array.set(Bool, g, c, U32.is_eq(U32.and(c, 3), 1)))

def cfill(+j: Nat, g: Array<Char>) -> Array<Char>:
  match j:
    case 0n:
      g
    case 1n+p:
      +c = U32.from_nat(p)
      cfill(p, Array.set(Char, g, c, Chr{U32.add(97, U32.mod(c, 26))}))

def fin2(r: Array<U32> & U32, +n: Nat) -> U32:
  (a, x) = r
  U32.add(x, sum(n, a))

def addmany(+j: Nat, a: Array<U32>) -> Array<U32>:
  match j:
    case 0n:
      a
    case 1n+p:
      addmany(p, Array.set(U32, a, 0, U32.inc(U32.from_nat(p))))

# (a fork: a write through one handle is read through the other)
def forked.fin(r: Array<U32> & U32, s: Array<U32> & U32) -> U32:
  (b2, x) = r
  (a3, y) = s
  U32.add(U32.add(x, y), U32.add(sum(15n, a3), sum(15n, b2)))

def forked.go(b: Array<U32>, a2: Array<U32>) -> U32:
  forked.fin(Array.get(U32, b, 5), Array.get(U32, a2, 6))

def forked(r: Array<U32> & Array<U32>) -> U32:
  (a, b) = r
  forked.go(b, Array.set(U32, a, 5, 777))

def atom3(r: Array<U32> & U32, +o1: U32, +o2: U32) -> U32:
  (a4, o3) = r
  U32.add(U32.add(o1, o2), U32.add(o3, sum(7n, a4)))

def atom2(r: Array<U32> & U32, +o1: U32) -> U32:
  (a3, o2) = r
  atom3(Array.atomic.xor(a3, 4, 255), o1, o2)

def atom1(r: Array<U32> & U32) -> U32:
  (a2, o1) = r
  atom2(Array.atomic.max(a2, 3, 1000), o1)

def atom(a: Array<U32>) -> U32:
  atom1(Array.atomic.add(a, 3, 10))

def mka() -> Array<U32>:
  fill(64n, 7, [0 : U32*64n])

def mkm() -> Array<U32>:
  Array.map(~U32, ~U32, ~(x => U32.add(x, 1)), mka())

def mkw() -> Array<U32>:
  gset(~U32, 8n, 42, Array.map(~U32, ~U32, ~(x => U32.add(x, 3)), [0 : U32*32n]))

def mkn() -> Array<U32>:
  ANode{fill(8n, 1, [0 : U32*8n]), fill(8n, 2, [0 : U32*8n])}

def mkmix() -> Array<U32>:
  ANode{fill(8n, 3, [0 : U32*8n]), Array.map(~U32, ~U32, ~(x => U32.add(x, 9)), [0 : U32*8n])}

def arrays.go(r: Array<U32> & Array<U32>) -> List<&2, U32>:
  (a1, a2) = r
  [sum(64n, a1), gsum(~U32, ~u32id, 64n, a2), sum(64n, mkm()), gsum(~U32, ~u32id, 64n, mkm()),
   sum(32n, mkw()), gsum(~U32, ~u32id, 32n, mkw()), lsum(Array.to_list(~U32, mka()), 0),
   sum(16n, mkn()), gsum(~U32, ~u32id, 16n, mkn()), lsum(Array.to_list(~U32, mkn()), 0),
   sum(16n, mkmix()), lsum(Array.to_list(~U32, mkmix()), 0),
   sum(1n, fill(1n, 5, [0 : U32*1n])), lsum(Array.to_list(~U32, fill(1n, 5, [0 : U32*1n])), 0),
   F32.to_u32(fsum.go(16n, Array.get(F32, ffill(16n, [0.25 : F32*16n]), 16), 0.0)),
   gsum(~Bool, ~b2u, 16n, bfill(16n, [False{} : Bool*16n])),
   gsum(~Char, ~c2u, 40n, cfill(40n, [Chr{65} : Char*64n])),
   fin2(Array.get(U32, addmany(100n, fill(4n, 11, [0 : U32*4n])), 0), 4n),
   forked(Array.fork(U32, fill(16n, 13, [0 : U32*16n]))),
   atom(fill(8n, 17, [0 : U32*8n]))]

def arrays() -> List<&2, U32>:
  arrays.go(Array.clone(U32, mka()))

# A parallel tree: each leaf keeps a list of narrow arrays alive across
# the allocations of the next ones.
def keep(+k: Nat, +i: U32, acc: List<Array<U32>>) -> List<Array<U32>>:
  match k:
    case 0n:
      acc
    case 1n+p:
      keep(p, i, fill(256n, U32.add(i, U32.from_nat(p)), [0 : U32*256n]) <> acc)

def sums(xs: List<Array<U32>>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case h <> t:
      sums(t, U32.add(U32.mul(acc, 3), sum(256n, h)))

def leaf(+i: U32) -> U32:
  sums(keep(24n, i, Nil{}), 0)

def batch(+k: Nat, +i: U32) -> U32:
  match k:
    case 0n:
      leaf(i)
    case 1n+p:
      a b = batch(p, i) batch(p, U32.add(i, U32.shln(1, p)))
      U32.add(a, b)

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(List.show(~&2, ~U32, ~U32.show, arrays()))
    IO.print(U32.show(batch(9n, 0)))
