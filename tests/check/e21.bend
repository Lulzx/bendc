import Base

def f(xs: List<U32>) -> U32:
  match xs:
    case Nil{}:
      0
    case Con{h, t}:
      (h + f(t) : U32)

def main() -> U32:
  f([1, 2, 3])
