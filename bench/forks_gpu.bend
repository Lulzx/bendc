import Base

# The same as a !-call, on the GPU: a parallel let at every level of a 2^d tree, a little
# arithmetic at each leaf. The calls differ (they carry an index), so none
# can be shared.
def forks(d: Nat, i: U32) -> U32:
  match d:
    case 0n:
      U32.shrn((i * 2654435761 : U32), 16n)
    case 1n+p:
      +q = p
      +j = i
      a b = forks(q, (j * 2 : U32)) forks(q, (j * 2 + 1 : U32))
      (a + b : U32)

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
    IO.print(U32.show(forks!(arg(args, 24n), 0)))
