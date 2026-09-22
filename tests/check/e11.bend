import Base

def twice(~f: U32 -> U32, x: U32) -> U32:
  f(f(x))

def g(k: U32, y: U32) -> U32:
  twice(~(x => (x + k : U32)), y)

def main() -> U32:
  g(1, 2)
