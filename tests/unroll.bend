import Base

# Calls that pass a small Nat literal for a parameter the callee matches on
# first call copies of the callee for it (u in BEND_OPT): a loop of a known
# count becomes a chain of copies. Each result is the same as the loop's.

# a table the unrolled loops read at a known index
def key(j: Nat) -> U32:
  match j:
    case 0n:
      7
    case 1n:
      11
    case 2n:
      13
    case 3n:
      17
    case 4n+k:
      19

# a counted loop whose second counter goes up
def mix(n: Nat, +j: Nat, +x: U32) -> U32:
  match n:
    case 0n:
      x
    case 1n+p:
      mix(p, 1n+j, U32.add(U32.mul(x, 31), key(j)))

# the counter read as a number, and matched with a Bool
def near(+i: Nat, +best: U32, +at: U32, lt: Bool) -> U32 & U32:
  match i lt:
    case 0n False{}:
      (best, at)
    case 0n True{}:
      (U32.from_nat(i), at)
    case 1n+(+k) False{}:
      +v = U32.mod(U32.mul(key(k), 2654435761), 1000)
      near(k, best, at, U32.is_lt(v, best))
    case 1n+(+k) True{}:
      +v = U32.mod(U32.mul(key(k), 2654435761), 1000)
      near(k, v, U32.from_nat(k), U32.is_lt(v, best))

# patterns two apart, and a literal over the limit (a loop as written)
def two(n: Nat, +acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n:
      U32.inc(acc)
    case 2n+(+p):
      two(p, U32.add(acc, U32.from_nat(p)))

# nested: an unrolled loop that calls another with a literal
def outer(n: Nat, +acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n+(+p):
      outer(p, mix(3n, 0n, U32.add(acc, U32.from_nat(p))))

def go(+s: U32) -> U32:
  +a = mix(22n, 0n, s)
  +r0 = Pair.fst(U32, U32, near(9n, 1000, 99, False{}))
  +r1 = Pair.snd(U32, U32, near(9n, 1000, 99, False{}))
  +b = two(9n, a)
  +c = two(100n, s)
  +e = outer(5n, s)
  U32.xor(U32.xor(U32.xor(a, r0), U32.xor(r1, b)), U32.xor(c, e))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(mix(22n, 0n, 5)))
    IO.print(U32.show(Pair.fst(U32, U32, near(9n, 1000, 99, False{}))))
    IO.print(U32.show(Pair.snd(U32, U32, near(9n, 1000, 99, False{}))))
    IO.print(U32.show(two(9n, 1)))
    IO.print(U32.show(two(100n, 1)))
    IO.print(U32.show(outer(5n, 2)))
    IO.print(U32.show(go(12345)))
