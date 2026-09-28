import Base

# Shifts by any count, float literals (exact and rounded, negative, ones
# too long for a compile-time conversion) and nested float arithmetic.
def shifts(+x: U32, +n: Nat) -> String:
  U32.show(U32.shrn(x, n)) ++ " " ++ U32.show(U32.shln(x, n))

def poly(+x: F32) -> F32:
  (((x * x * 0.5 + x * 0.25 : F32) - 1.125 : F32) / (x + 3.0 : F32) : F32)

def acc(n: Nat, +x: F32, +c: F32) -> F32:
  match n:
    case 0n:
      x
    case 1n+p:
      acc(p, (x * x * 0.5 + c : F32), c)

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(shifts(3000000000, 0n))
    IO.print(shifts(3000000000, 1n))
    IO.print(shifts(3000000000, 31n))
    IO.print(shifts(3000000000, 32n))
    IO.print(shifts(3000000000, 33n))
    IO.print(shifts(3000000000, 64n))
    IO.print(shifts(3000000000, 65n))
    IO.print(F32.show(0.1))
    IO.print(F32.show(0.3))
    IO.print(F32.show(F32.neg(2.25)))
    IO.print(F32.show(16777217.0))
    IO.print(F32.show(0.00001))
    IO.print(F32.show(0.1234567))
    IO.print(F32.show(123456789012345.0))
    IO.print(F32.show(poly(2.0)))
    IO.print(F32.show(poly(F32.neg(0.75))))
    IO.print(F32.show(acc(1000n, 0.0, 0.3)))
    IO.print(F32.show(F32.neg((0.5 * 3.0 : F32))))
