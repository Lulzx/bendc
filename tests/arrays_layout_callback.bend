import Base

def alloc(~T: Data, v: T) -> Array<T>:
  Array.new(T, 2n, v)

def call(f: U32 -> Array<U32>, x: U32) -> Array<U32>:
  f(x)

def read(r: Array<U32> & U32) -> U32:
  (a, x) = r
  x

def main() -> IO(Unit):
  IO.print(U32.show(read(Array.get(U32, call(alloc(U32), 41), 1))))
