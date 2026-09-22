import Base
import ./lib/math.bend as M

def square(x: U32) -> U32:
  (x + 1000 : U32)

def main() -> IO(Unit):
  +v = {M.Vec{3, 4} : M.Vec}
  do IO<Unit>:
    IO.print(U32.show(M.norm2(v)))
    IO.print(M.show(v))
    IO.print(U32.show(M.square(7)) ++ " " ++ U32.show(square(7)))
