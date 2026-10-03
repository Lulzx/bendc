import Base

# Different masks must move together with the self-tail Array parameters.
type R is Type:
  R{a: Array<U32>, b: Array<U32>, c: Array<U32>, d: Array<U32>}
type W is Type:
  W{a: Array<Nat>, b: Array<Nat>, c: Array<Nat>, d: Array<Nat>}

def cell(r: Array<U32> & U32) -> U32:
  (a, x) = r
  x

def word(r: Array<Nat> & Nat) -> Nat:
  (a, x) = r
  x

def rotate(n: Nat, r: R) -> U32:
  match n:
    case 0n:
      R{a, b, c, d} = r
      cell(Array.get(U32, a, 9))
    case 1n+n:
      R{a, b, c, d} = r
      rotate(n, R{b, c, d, a})

def rotate_word(n: Nat, r: W) -> Nat:
  match n:
    case 0n:
      W{a, b, c, d} = r
      word(Array.get(Nat, a, 9))
    case 1n+n:
      W{a, b, c, d} = r
      rotate_word(n, W{b, c, d, a})

def make() -> R:
  a = Array.new(U32, 1n, 11)
  b = Array.set(U32, Array.new(U32, 4n, 23), 9, 47)
  c = Array.new(U32, 2n, 31)
  d = Array.new(U32, 3n, 37)
  R{a, b, c, d}

def make_word() -> W:
  a = Array.new(Nat, 1n, 11n)
  b = Array.set(Nat, Array.new(Nat, 4n, 23n), 9, 47n)
  c = Array.new(Nat, 2n, 31n)
  d = Array.new(Nat, 3n, 37n)
  W{a, b, c, d}

def native() -> U32:
  rotate(5n, make())

def native_word() -> Nat:
  rotate_word(5n, make_word())

# Array.swap hands the exact same Array identity to the next lexical alias.
def alias_after(r: Array<U32> & U32) -> U32:
  (a, old) = r
  (old + cell(Array.get(U32, a, 9)) : U32)

def alias(a: Array<U32>) -> U32:
  alias_after(Array.swap(U32, a, 9, 59))

def alias_probe() -> U32:
  alias(Array.set(U32, Array.new(U32, 4n, 23), 9, 47))

# A new binder with the same name has a different Array size and mask.
def shadow(a: Array<U32>) -> U32:
  r = Array.get(U32, a, 9)
  a = Array.new(U32, 1n, 11)
  (cell(r) + cell(Array.get(U32, a, 9)) : U32)

def shadow_probe() -> U32:
  shadow(Array.set(U32, Array.new(U32, 4n, 23), 9, 47))

# The caller has no descriptor: the direct helper uses the cache fallback.
def peek(a: Array<U32>) -> U32:
  cell(Array.get(U32, a, 9))

def unknown() -> U32:
  peek(Array.set(U32, Array.new(U32, 4n, 23), 9, 47))

# Four CPU arrays cross a direct GPU entry: descriptors retain borrowed class.
def borrow4(a: Array<U32>, b: Array<U32>, c: Array<U32>, d: Array<U32>) -> U32:
  rotate(5n, R{a, b, c, d})

def borrow_words(a: Array<Nat>, b: Array<Nat>, c: Array<Nat>, d: Array<Nat>) -> Nat:
  rotate_word(5n, W{a, b, c, d})

def borrowed(r: R) -> IO(Unit):
  R{a, b, c, d} = r
  IO.print(U32.show(borrow4!(a, b, c, d)))

def borrowed_words(r: W) -> IO(Unit):
  W{a, b, c, d} = r
  IO.print(Nat.show(borrow_words!(a, b, c, d)))

def settle(n: Nat, +x: U32) -> U32:
  match n:
    case 0n:
      x
    case 1n+n:
      settle(n, x)

# A strict read in a function reaching a loop selects the direct KQ entry.
def direct_loop(n: Nat, a: Array<U32>) -> U32:
  r = Array.get(U32, a, 9)
  a = Array.new(U32, 1n, 11)
  settle(n, (cell(r) + cell(Array.get(U32, a, 9)) : U32))

# Eligible four-array frames preserve exact aliases and clear shadowed masks.
def rotate_shadow(n: Nat, r: R) -> U32:
  match n:
    case 0n:
      R{a, b, c, d} = r
      r = Array.get(U32, a, 9)
      a = Array.new(U32, 1n, 11)
      (cell(r) + cell(Array.get(U32, a, 9)) : U32)
    case 1n+n:
      R{a, b, c, d} = r
      rotate_shadow(n, R{b, c, d, a})

def native_shadow() -> U32:
  rotate_shadow(5n, make())

def main() -> IO(Unit):
  a = make()
  w = make_word()
  cpu = Array.set(U32, Array.new(U32, 4n, 23), 9, 47)
  do IO<Unit>:
    IO.print(U32.show(native!()))
    IO.print(Nat.show(native_word!()))
    IO.print(U32.show(alias_probe!()))
    IO.print(U32.show(shadow_probe!()))
    IO.print(U32.show(unknown!()))
    borrowed(a)
    borrowed_words(w)
    IO.print(U32.show(direct_loop!(5n, cpu)))
    IO.print(U32.show(native_shadow!()))
