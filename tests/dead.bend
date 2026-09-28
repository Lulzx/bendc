import Base

# Lets of a variable no lookup reaches (Core.Tm.dead): an unused let, one
# the next let of the same name hides, one a lambda's parameter hides, are
# dropped; one a lambda uses is kept.

def sum(n: Nat) -> Nat:
  match n:
    case 0n:
      0n
    case 1n+(+p):
      (1n + p + sum(p) : Nat)

def f(+n: Nat) -> Nat:
  x = sum(n)
  (n + 1n : Nat)

def g(+n: Nat) -> Nat:
  x = sum(n)
  x = (n * 3n : Nat)
  x

def ap(f: Nat -> Nat, a: Nat) -> Nat:
  f(a)

def h(+n: Nat) -> Nat:
  x = sum(n)
  ap(x => (x + n : Nat), 2n)

def kept(+n: Nat) -> Nat:
  +x = sum(n)
  (ap(y => (y + x : Nat), n) + x : Nat)

def main() -> Nat:
  +a = f(5n)
  +b = g(5n)
  +d = h(5n)
  +k = kept(4n)
  (a + b + d + k : Nat)
