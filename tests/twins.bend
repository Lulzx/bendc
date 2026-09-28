import Base

# Loops over F32 parameters: two new values that read each other's old
# ones, parameters swapped, a parameter set from a call or a literal, one
# used as a value and captured by a lambda, and more F32 parameters than
# the four kept in FP registers.
law mandel:
  for n: Nat
  for +zr: F32
  for +zi: F32
  for +cr: F32
  for +ci: F32
  String

@unsafe
def mandel(n, zr, zi, cr, ci):
  match n:
    case 0n:
      F32.show(zr) ++ " " ++ F32.show(zi)
    case 1n+p:
      +out = F32.is_gt((zr * zr + zi * zi : F32), 4.0)
      mandel(Bool.pick(Nat, out, 0n, p), (zr * zr - zi * zi + cr : F32), (zr * zi * 2.0 + ci : F32), cr, ci)

def swap(n: Nat, +a: F32, +b: F32) -> F32:
  match n:
    case 0n:
      (a - b * 10.0 : F32)
    case 1n+p:
      swap(p, b, (a + 1.0 : F32))

def half(+x: F32) -> F32:
  (x * 0.5 : F32)

def app(f: F32 -> F32, +y: F32) -> F32:
  f(y)

def mixed(n: Nat, +x: F32, acc: List<&2, String>) -> List<&2, String>:
  match n:
    case 0n:
      acc
    case 1n+ +p:
      mixed(p, Bool.pick(F32, Nat.is_eq(Nat.mod(p, 3n), 0n), 1.5, half((x * 3.0 : F32))),
        F32.show(app(y => (x + y : F32), 0.25)) <> acc)

def five(n: Nat, +a: F32, +b: F32, +c: F32, +d: F32, +e: F32) -> F32:
  match n:
    case 0n:
      (a + b + c + d + e : F32)
    case 1n+p:
      five(p, (b * 0.5 + e : F32), (a - 1.0 : F32), (d * 2.0 : F32), (c + e : F32), (e * 0.75 + a : F32))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print((mandel(100n, 0.0, 0.0, F32.neg(0.75), 0.1)))
    IO.print((mandel(100n, 0.0, 0.0, 0.3, 0.5)))
    IO.print((mandel(100n, 0.0, 0.0, F32.neg(1.25), 0.25)))
    IO.print(F32.show(swap(7n, 1.0, 2.0)))
    IO.print(String.join(mixed(6n, 1.0, []), " "))
    IO.print(F32.show(five(9n, 1.0, 2.0, 3.0, 4.0, 5.0)))
