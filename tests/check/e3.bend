import Base

def f(xs: List<U32>) -> U32:
  match xs:
    case Nil{}:
      0

def main() -> U32:
  f([1])
