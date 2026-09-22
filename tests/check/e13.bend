import Base

type Box is Type:
  B{v: U32}

def dup(+b: Box) -> Box & Box:
  (b, b)

def main() -> U32:
  1
