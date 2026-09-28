import Base

# x * k + b and b + x * k, k a power of two: one fused operation when the
# product is a normal float, the two as written when it is not (an
# underflow that rounds, an overflow), with the same result either way.
def mad(+x: F32, +c: F32) -> F32:
  (x * 0.5 + c : F32)

def dam(+x: F32, +c: F32) -> F32:
  (c + (x * 4.0 : F32) : F32)

def p16(n: Nat, +x: F32) -> F32:
  match n:
    case 0n:
      x
    case 1n+p:
      p16(p, (x * 65536.0 : F32))

def q16(n: Nat, +x: F32) -> F32:
  match n:
    case 0n:
      x
    case 1n+p:
      q16(p, (x / 65536.0 : F32))

def up(+r: F32) -> String:
  F32.show((p16(9n, r) * 32.0 : F32))

def main() -> IO(Unit):
  +m = (q16(7n, 1.0) / 16384.0 : F32)
  +u = (m / 8388608.0 : F32)
  +big = (p16(7n, 1.0) * 16384.0 : F32)
  do IO<Unit>:
    IO.print(F32.show(mad(3.0, 1.0)))
    IO.print(F32.show(dam(3.0, 1.0)))
    IO.print(F32.show(mad(F32.neg(0.75), 0.125)))
    IO.print(up(mad((m + u : F32), u)))
    IO.print(up(mad(m, u)))
    IO.print(up(dam((u * 4.0 : F32), u)))
    IO.print(F32.show(dam(big, 1.0)))
    IO.print(F32.show(mad((big * 1.5 : F32), 1.0)))
