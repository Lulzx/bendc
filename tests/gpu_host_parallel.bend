import Base

def serial(n: Nat) -> U32:
  match n:
    case 0n:
      0
    case 1n+p:
      x = serial(p)
      U32.add(x, 1)

# The compiler may parallelize these operands; the serial host policy
# must still recognize the original serial spelling.
def implicit(n: Nat) -> U32:
  match n:
    case 0n:
      1
    case 1n+p:
      +q = p
      U32.add(implicit(q), implicit(q))

def split(n: Nat) -> U32:
  match n:
    case 0n:
      serial(32n)
    case 1n+p:
      +q = p
      a b = split(q) split(q)
      U32.add(a, b)

# No parallel let here: eligibility must inspect the callee too.
def bridge(+n: Nat) -> U32:
  x = split(n)
  U32.add(x, serial(n))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(bridge!(6n)))
    IO.print(U32.show(implicit!(6n)))
