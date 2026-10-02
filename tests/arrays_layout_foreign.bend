import Base

def foreign_make() -> IO(Array<U32>):
  import "./lib/arrays_layout_wide.c"
  import "./lib/arrays_layout_wide.js"

def read(r: Array<U32> & U32) -> U32:
  (a, x) = r
  x

def main() -> IO(Unit):
  do IO<Unit>:
    a : Array<U32> <- foreign_make()
    IO.print(U32.show(read(a[1])))
