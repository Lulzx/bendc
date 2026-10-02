import Base

def probe() -> IO(U32):
  import "./lib/arrays_layout_probe.c"
  import "./lib/arrays_layout_probe.js"

def read(r: Array<U32> & U32) -> U32:
  (a, x) = r
  x

def total(a: Array<U32>) -> U32:
  read(a[7])

def main() -> IO(Unit):
  do IO<Unit>:
    x : U32 <- probe()
    IO.print(U32.show(U32.add(x, total(Array.new(U32, 2n, 11)))))
