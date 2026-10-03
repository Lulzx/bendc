import Base

type State is Type:
  State{a: Array<U32>, b: Array<U32>, c: Array<U32>, d: Array<U32>}
def finish3(+s: U32, r: Array<U32> & U32) -> U32:
  (d, x) = r
  (s + x : U32)
def finish2(+s: U32, d: Array<U32>, r: Array<U32> & U32) -> U32:
  (c, x) = r
  finish3((s + x : U32), Array.get(U32, d, 9))
def finish1(c: Array<U32>, d: Array<U32>, +s: U32, r: Array<U32> & U32) -> U32:
  (b, x) = r
  finish2((s + x : U32), d, Array.get(U32, c, 9))
def finish0(b: Array<U32>, c: Array<U32>, d: Array<U32>, r: Array<U32> & U32) -> U32:
  (a, x) = r
  finish1(c, d, x, Array.get(U32, b, 9))
def finish(st: State) -> U32:
  State{a, b, c, d} = st
  finish0(b, c, d, Array.get(U32, a, 9))

# The pair's lifted Array field is Word, so these are flow-only slots.
# An unknown replacement has a different mask and must drop descriptor0.
def descend(n: Nat, b: Array<U32>, c: Array<U32>, d: Array<U32>, r: Array<U32> & U32) -> U32:
  match n:
    case 0n:
      (a, x) = r
      finish(State{a, b, c, d})
    case 1n+n:
      (a, x) = r
      descend(n, b, c, d, Array.get(U32, Array.new(U32, 1n, 7), 9))
def entry(n: Nat, st: State) -> U32:
  State{a, b, c, d} = st
  descend(n, b, c, d, Array.get(U32, a, 9))
def make() -> State:
  State{Array.new(U32, 4n, 11), Array.set(U32, Array.new(U32, 4n, 23), 9, 47), Array.new(U32, 2n, 31), Array.new(U32, 3n, 37)}
def native() -> U32:
  entry(2n, make())
def unknown(st: State) -> IO(Unit):
  State{a, b, c, d} = st
  IO.print(U32.show(descend!(0n, b, c, d, Array.get(U32, a, 9))))
def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(native!()))
    unknown(make())
