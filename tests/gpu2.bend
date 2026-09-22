import Base

type Shape is Data:
  Circle{r: F32}
  Rect{w: F32, h: F32}

def area(s: Shape) -> F32:
  match s:
    case Circle{r}:
      +x = r
      (3.0 * x * x : F32)
    case Rect{w, h}:
      (w * h : F32)

def app(f: U32 -> U32, x: U32) -> U32:
  f(x)

def range(n: Nat, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      +q = p
      range(q, U32.from_nat(q) <> acc)

def add(a: U32, b: U32) -> U32:
  (a + b : U32)

# A closure made on the device, applied there.
def scaled(k: U32, xs: List<U32>) -> List<U32>:
  match xs:
    case []:
      []
    case x <> t:
      +j = k
      app(y => (y * j : U32), x) <> scaled(j, t)

# A function the device returns: a partial application.
def adder(k: U32) -> U32 -> U32:
  add(k)

def greet(n: Nat) -> String:
  match n:
    case 0n:
      "bend"
    case 1n+p:
      String.concat(["hi ", greet(p)])

def big(n: Nat) -> Nat:
  match n:
    case 0n:
      1n
    case 1n+p:
      (2n * big(p) : Nat)

def count(n: Nat) -> Nat:
  match n:
    case 0n:
      0n
    case 1n+p:
      +q = p
      a b = count(q) count(q)
      (1n + a + b : Nat)

def pairs(n: Nat) -> List<(U32 & Bool)>:
  match n:
    case 0n:
      []
    case 1n+p:
      +q = p
      (U32.from_nat(q), Nat.is_eq(Nat.mod(q, 2n), 0n)) <> pairs(q)

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      sum(t, (acc + x : U32))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(F32.show(area!(Rect{2.0, 3.5})))
    IO.print(F32.show(area!(Circle{2.0})))
    IO.print(U32.show(sum(scaled!(3, range(10n, [])), 0)))
    IO.print(U32.show(app!(add(10), 5)))
    IO.print(U32.show(app(adder!(3), 4)))
    IO.print(greet!(3n))
    IO.print(Nat.show(big!(10n)))
    IO.print(Nat.show(big!(70n)))
    IO.print(Nat.show(count!(12n)))
    IO.print(Nat.show(List.length(&1, (U32 & Bool), pairs!(5n))))
