import Base

type S is Type:
  S{a: Array<U32>, b: Array<U32>, c: Array<U32>, d: Array<U32>}
type W is Type:
  W{a: Array<Nat>, b: Array<Nat>, c: Array<Nat>, d: Array<Nat>}

def read.f3(+sum: U32, r: Array<U32> & U32) -> U32:
  (d, x) = r
  (sum + x : U32)
def read.f2(+sum: U32, d: Array<U32>, r: Array<U32> & U32) -> U32:
  (c, x) = r
  read.f3((sum + x : U32), Array.get(U32, d, 9))
def read.f1(b: Array<U32>, c: Array<U32>, d: Array<U32>, r: Array<U32> & U32) -> U32:
  (a, x) = r
  read.f2(x, d, Array.get(U32, c, 9))
def read.start(r: S) -> U32:
  S{a, b, c, d} = r
  read.f1(b, c, d, Array.get(U32, a, 9))

# The extra first-stage read keeps all four Array formals live.
def read.first(c: Array<U32>, d: Array<U32>, +sum: U32, r: Array<U32> & U32) -> U32:
  (b, x) = r
  read.f2((sum + x : U32), d, Array.get(U32, c, 9))
def read.bridge(b: Array<U32>, c: Array<U32>, d: Array<U32>, r: Array<U32> & U32) -> U32:
  (a, x) = r
  read.first(c, d, x, Array.get(U32, b, 9))

def read.all(r: S) -> U32:
  S{a, b, c, d} = r
  read.bridge(b, c, d, Array.get(U32, a, 9))
def word.f3(+sum: U32, r: Array<Nat> & Nat) -> U32:
  (d, x) = r
  (sum + U32.from_nat(Nat.mod(x, 1073741823n)) : U32)
def word.f2(+sum: U32, d: Array<Nat>, r: Array<Nat> & Nat) -> U32:
  (c, x) = r
  word.f3((sum + U32.from_nat(Nat.mod(x, 1073741823n)) : U32), Array.get(Nat, d, 9))
def word.first(c: Array<Nat>, d: Array<Nat>, +sum: U32, r: Array<Nat> & Nat) -> U32:
  (b, x) = r
  word.f2((sum + U32.from_nat(Nat.mod(x, 1073741823n)) : U32), d, Array.get(Nat, c, 9))
def word.bridge(b: Array<Nat>, c: Array<Nat>, d: Array<Nat>, r: Array<Nat> & Nat) -> U32:
  (a, x) = r
  word.first(c, d, U32.from_nat(Nat.mod(x, 1073741823n)), Array.get(Nat, b, 9))
def word.all(r: W) -> U32:
  W{a, b, c, d} = r
  word.bridge(b, c, d, Array.get(Nat, a, 9))

def update.stage(a: Array<U32>, b: Array<U32>, c: Array<U32>, r: Array<U32> & U32) -> S:
  (d, x) = r
  S{a, b, c, Array.set(U32, d, 9, U32.inc(x))}
def update.all(r: S) -> S:
  S{a, b, c, d} = r
  update.stage(a, b, c, Array.get(U32, d, 9))
def update_word.stage(a: Array<Nat>, b: Array<Nat>, c: Array<Nat>, r: Array<Nat> & Nat) -> W:
  (d, x) = r
  W{a, b, c, Array.set(Nat, d, 9, Nat.add(x, 1n))}
def update_word.all(r: W) -> W:
  W{a, b, c, d} = r
  update_word.stage(a, b, c, Array.get(Nat, d, 9))

def make() -> S:
  S{Array.new(U32, 1n, 11), Array.set(U32, Array.new(U32, 4n, 23), 9, 47), Array.new(U32, 2n, 31), Array.new(U32, 3n, 37)}
def make_word() -> W:
  +big = Nat.mul(0n, 0n)
  W{Array.new(Nat, 1n, Nat.add(big, 11n)), Array.set(Nat, Array.new(Nat, 4n, Nat.add(big, 23n)), 9, Nat.add(big, 47n)), Array.new(Nat, 2n, Nat.add(big, 31n)), Array.new(Nat, 3n, Nat.add(big, 37n))}
def native() -> U32:
  read.all(make())
def native_word() -> U32:
  word.all(make_word())
def native_write() -> U32:
  read.all(update.all(make()))
def native_word_write() -> U32:
  word.all(update_word.all(make_word()))
def borrowed(r: S) -> IO(Unit):
  IO.print(U32.show(read.all!(r)))
def unknown(r: S) -> IO(Unit):
  S{a, b, c, d} = r
  IO.print(U32.show(read.bridge!(b, c, d, Array.get(U32, a, 9))))
def borrowed_word(r: W) -> IO(Unit):
  IO.print(U32.show(word.all!(r)))
def unknown_word(r: W) -> IO(Unit):
  W{a, b, c, d} = r
  IO.print(U32.show(word.bridge!(b, c, d, Array.get(Nat, a, 9))))
def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(native!()))
    IO.print(U32.show(native_word!()))
    borrowed(make())
    unknown(make())
    borrowed_word(make_word())
    unknown_word(make_word())
    IO.print(U32.show(native_write!()))
    IO.print(U32.show(native_word_write!()))
