import Base

# Uniform numeric work: 16384 leaves, each a 200,000-step F32 loop.
def iter(n: Nat, +x: F32, +c: F32) -> F32:
  match n:
    case 0n:
      x
    case 1n+p:
      iter(p, (x * x * 0.5 + c : F32), c)

def leaf(i: U32) -> F32:
  +f = U32.to_f32(i)
  iter(200000n, 0.0, (f * 0.00001 : F32))

def work(d: Nat, i: U32) -> F32:
  match d:
    case 0n:
      leaf(i)
    case 1n+p:
      +q = p
      +j = i
      a b = work(q, (j * 2 : U32)) work(q, (j * 2 + 1 : U32))
      (a + b : F32)

# The size comes from the command line, so no compiler can fold the work
# away at compile time.
def arg(xs: List<String>, d: Nat) -> Nat:
  match xs:
    case x <> t:
      Maybe.default(&2, Nat, Nat.read(x), d)
    case []:
      d

def main() -> IO(Unit):
  do IO<Unit>:
    args : List<String> <- IO.args()
    IO.print(F32.show(work!(arg(args, 14n), 0)))
