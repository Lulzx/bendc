import Base

# Lookups of variables let-bound to numbers (Core.Tm.lit): each becomes the
# number, and the let is dropped; a lookup the next let of the same name or
# a lambda's parameter hides is left as it is.

def ap(f: U32 -> U32, a: U32) -> U32:
  f(a)

def twice(+n: U32) -> U32:
  +k : U32 = 7
  (n + k + k : U32)

def hidden(+n: U32) -> U32:
  +k : U32 = 7
  k = (n * 3 : U32)
  (k + 1 : U32)

def param(+n: U32) -> U32:
  +k : U32 = 7
  (ap(k => (k + n : U32), 2) + k : U32)

def captured(+n: U32) -> U32:
  +k : U32 = 5
  ap(x => (x + k : U32), n)

def field(xs: List<U32>) -> U32:
  match xs:
    case []:
      0
    case +h <> r:
      +k : U32 = 100
      (h + k + k : U32)

def nat(+n: Nat) -> Nat:
  +m : Nat = 3n
  (n + m + m : Nat)

def to_u32(n: Nat) -> U32:
  match n:
    case 0n:
      0
    case 1n+p:
      (1 + to_u32(p) : U32)

def main() -> U32:
  +a = twice(1)
  +b = hidden(2)
  +c = param(3)
  +d = captured(4)
  +e = field([])
  +f = field([9])
  +g = nat(2n)
  (a + b + c + d + e + f + to_u32(g) : U32)
