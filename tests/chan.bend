import Base

# Lists wait in a buffered channel while the collector runs (tests/chan.env
# collects every megabyte): the channel's buffer must keep them alive.
def build(+n: Nat, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      build(p, U32.from_nat(p) <> acc)

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case Con{h, t}:
      sum(t, (acc + h : U32))

def churn(k: Nat, acc: U32) -> U32:
  match k:
    case 0n:
      acc
    case 1n+p:
      churn(p, (acc + sum(build(100000n, []), 0) : U32))

def fill(k: Nat, +c: Chan(List<U32>)) -> IO(Unit):
  match k:
    case 0n:
      IO.pure(Unit, Unit{})
    case 1n+p:
      do IO<Unit>:
        ok : Bool <- Chan.send(List<U32>, c, build(1000n, []))
        fill(p, c)

def got(m: Maybe<&1, List<U32>>) -> U32:
  match m:
    case None{}:
      0
    case Some{xs}:
      sum(xs, 0)

def drain(k: Nat, +c: Chan(List<U32>), acc: U32) -> IO(U32):
  match k:
    case 0n:
      IO.pure(U32, acc)
    case 1n+p:
      do IO<U32>:
        m : Maybe<&1, List<U32>> <- Chan.recv(List<U32>, c)
        drain(p, c, (acc + got(m) : U32))

def main() -> IO(Unit):
  do IO<Unit>:
    +c : Chan(List<U32>) <- Chan.new(List<U32>, 64)
    fill(64n, c)
    IO.print(U32.show(churn(40n, 0)))
    total : U32 <- drain(64n, c, 0)
    IO.print(U32.show(total))
