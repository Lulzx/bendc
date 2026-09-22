import Base

def add_strs(a: String, b: String) -> Maybe<&2, U32>:
  do Maybe<&2, U32>:
    x : U32 <- U32.read(a)
    y : U32 <- U32.read(b)
    return (x + y : U32)

def show_m(m: Maybe<&2, U32>) -> String:
  Maybe.show(~&2, ~U32, ~U32.show, m)

def arr() -> U32:
  a = [0 : U32*8n]
  a[5] <- 42
  a[3] <- 7
  Pair.snd(Array<U32>, U32, a[5])

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(show_m(add_strs("40", "2")))
    IO.print(show_m(add_strs("40", "x")))
    IO.print(U32.show(arr()))
    IO.print(F32.show((1.5 * 2.0 : F32)))
    IO.print(U32.show(F32.to_u32(F32.sqrt(144.0))))
