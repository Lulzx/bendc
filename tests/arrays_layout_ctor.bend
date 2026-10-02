import Base

def read(r: Array<U32> & U32) -> U32:
  (a, x) = r
  x

def main() -> IO(Unit):
  IO.print(U32.show(read(Array.get(U32, ANode{ALeaf{31}, ALeaf{43}}, 1))))
