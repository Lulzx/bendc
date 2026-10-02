import Base

def make() -> Array<U32>:
  Array.new(U32, 2n, 37)

def read(r: Array<U32> & U32) -> U32:
  (a, x) = r
  x

def main() -> IO(Unit):
  IO.print(U32.show(read(Array.get(U32, make!(), 1))))
