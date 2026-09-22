import Base

type Shape is Data:
  Circle{r: U32}
  Square{s: U32}

def area(x: Shape) -> U32:
  match x:
    case Circle{+r}:
      (3 * r * r : U32)
    case Square{+s}:
      (s * s : U32)

def adder(k: U32) -> U32 -> U32:
  x => (x + k : U32)

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case Con{h, t}:
      sum(t, (acc + h : U32))

def pow2(+n: Nat) -> U32:
  match n:
    case 0n:
      1
    case 1n+p:
      a b = pow2(p) pow2(p)
      (a + b : U32)

def replicate(-A: Data, n: Nat, +x: A) -> List<A>:
  match n:
    case 0n:
      Nil{}
    case 1n+p:
      x <> replicate(A, p, x)

def twice(~f: U32 -> U32, x: U32) -> U32:
  f(f(x))

def main() -> IO(Unit):
  add2 = adder(2)
  add5 = adder(5)
  do IO<Unit>:
    IO.print(U32.show(area(Square{5})))
    IO.print(U32.show(area(Circle{2})))
    IO.print(U32.show(add5(add2(1))))
    IO.print(U32.show(sum([1, 2, 3, 4], 0)))
    IO.print(U32.show(pow2(16n)))
    IO.print(List.show(~&1, ~U32, ~U32.show, replicate(U32, 3n, 7)))
    IO.print(U32.show(twice(~(x => (x + 1 : U32)), 40)))
    IO.print(Nat.show(Nat.mul(1234n, 5678n)))
