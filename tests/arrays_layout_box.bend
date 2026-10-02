import Base

type Box is Type:
  Box{a: Array<U32>, pad: U32}

def foreign_box() -> IO(Box):
  import "./lib/arrays_layout_box.c"
  import "./lib/arrays_layout_box.js"

def read(r: Array<U32> & U32) -> U32:
  (a, x) = r
  x

def use(b: Box) -> U32:
  Box{a, pad} = b
  read(a[1])

def main() -> IO(Unit):
  do IO<Unit>:
    b : Box <- foreign_box()
    IO.print(U32.show(use(b)))
