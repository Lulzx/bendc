import Base

# Unboxed parameters and flat results (bendc's Unb pass and U_ functions):
# pairs and single-constructor records passed as separate C parameters and
# returned through an out array, Array.get and Array.swap pairs opened in
# place, a record rebuilt where it is used whole, and parallel lets of 2, 3
# and 8 values past the fork frontier.

type P3 is Data:
  P3{a: U32, b: U32, c: U32}

type Box is Data:
  Box{v: P3, n: U32}

# a flat result built in a loop
def step(+n: Nat, p: P3) -> P3:
  match n:
    case 0n:
      p
    case 1n+k:
      P3{a, +b, +c} = p
      step(k, P3{U32.add(a, b), U32.xor(b, c), U32.inc(c)})

# a let-bound flat result, taken apart
def use.fin(q: P3) -> U32:
  P3{x, y, z} = q
  U32.add(U32.mul(x, 3), U32.add(y, z))

def use(+n: Nat) -> U32:
  q = step(n, P3{1, 2, 3})
  use.fin(q)

# a flat parameter used whole (it is rebuilt)
def keep(p: P3, +k: U32) -> Box:
  Box{p, k}

def box.sum(b: Box) -> U32:
  match b:
    case Box{P3{x, y, z}, n}:
      U32.add(U32.add(x, y), U32.add(z, n))

# a pair of an array and a cell threaded through a loop: reads and swaps
# (the pair arguments are opened in place)
def sweep.at(+i: U32, +k: Nat, r: Array<U32> & U32) -> Array<U32> & U32:
  (b, y) = r
  Array.swap(U32, b, U32.and(U32.inc(i), 15), U32.add(y, U32.from_nat(k)))

def sweep.end(r: Array<U32> & U32, acc: U32) -> U32:
  (a, x) = r
  U32.add(U32.mul(acc, 7), x)

def sweep(+j: Nat, r: Array<U32> & U32, acc: U32) -> U32:
  match j:
    case 0n:
      (a, x) = r
      sweep.end(Array.swap(U32, a, 3, x), acc)
    case 1n+k:
      (a, x) = r
      +i = U32.and(U32.from_nat(k), 15)
      sweep(k, sweep.at(i, k, Array.get(U32, a, i)), U32.add(U32.mul(acc, 31), x))

# returns straight from Array.swap and Array.get
def bump(+i: U32, r: Array<U32> & U32) -> Array<U32> & U32:
  (b, v) = r
  Array.swap(U32, b, i, U32.inc(v))

def peek(+i: U32, r: Array<U32> & U32) -> Array<U32> & U32:
  (a, x) = r
  Array.get(U32, a, i)

def bumps(+j: Nat, r: Array<U32> & U32, acc: U32) -> U32:
  match j:
    case 0n:
      (a, x) = r
      U32.add(acc, x)
    case 1n+k:
      (a, x) = r
      +i = U32.and(U32.mul(U32.from_nat(k), 7), 15)
      bumps(k, peek(i, bump(i, Array.get(U32, a, i))), U32.xor(acc, x))

# parallel lets of 2, 3 and 8 values
def tri(+d: Nat, +s: U32) -> U32:
  match d:
    case 0n:
      U32.and(U32.mul(s, 2654435761), 1023)
    case 1n+p:
      a b c = tri(p, U32.inc(s)) tri(p, U32.add(s, 7)) tri(p, U32.add(s, 13))
      U32.add(a, U32.xor(b, c))

def oct(+d: Nat, +s: U32) -> U32:
  match d:
    case 0n:
      U32.and(U32.mul(s, 40503), 255)
    case 1n+p:
      a b c e f g h i = oct(p, U32.inc(s)) oct(p, U32.add(s, 2)) oct(p, U32.add(s, 3)) oct(p, U32.add(s, 4)) oct(p, U32.add(s, 5)) oct(p, U32.add(s, 6)) oct(p, U32.add(s, 7)) oct(p, U32.add(s, 8))
      U32.add(U32.add(U32.add(a, b), U32.add(c, e)), U32.xor(U32.add(f, g), U32.add(h, i)))

def two.join(x: P3, y: P3) -> P3:
  P3{xa, xb, xc} = x
  P3{ya, yb, yc} = y
  P3{U32.add(xa, ya), U32.add(xb, yb), U32.xor(xc, yc)}

def two(+d: Nat, +s: U32) -> P3:
  match d:
    case 0n:
      P3{s, 1, U32.and(s, 7)}
    case 1n+p:
      x y = two(p, U32.mul(s, 3)) two(p, U32.add(s, 11))
      two.join(x, y)

def p3.sum(p: P3) -> U32:
  P3{a, b, c} = p
  U32.add(U32.mul(a, 3), U32.xor(b, c))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(use(20n)))
    IO.print(U32.show(box.sum(keep(step(5n, P3{4, 5, 6}), 9))))
    IO.print(U32.show(sweep(100n, Array.get(U32, [3 : U32*16n], 0), 0)))
    IO.print(U32.show(bumps(64n, ([0 : U32*16n], 0), 0)))
    IO.print(U32.show(tri(9n, 1)))
    IO.print(U32.show(oct(5n, 1)))
    IO.print(U32.show(p3.sum(two(12n, 5))))
