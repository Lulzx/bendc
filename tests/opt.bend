import Base

# Programs the optimizer (bendc's Opt) rewrites: each prints what the
# official bend prints, whatever inlining, simplification, specialization
# and fusion made of it.

# Known cases with literal patterns: only the case that matches is taken.
def kind(c: Char) -> String:
  match c:
    case 'a':
      "a"
    case 'b':
      "b"
    case other:
      "other"

def kinds(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{c, t}:
      kind(c) ++ " " ++ kinds(t)

# A parallel let stays one.
def tree(+n: Nat) -> U32:
  match n:
    case 0n:
      1
    case 1n+p:
      a b = tree(p) tree(p)
      (a + b + 1 : U32)

# A def passed as the function of a higher-order def (specialized; its
# erased parameters stay erased).
def inc(x: U32) -> U32:
  (x + 1 : U32)

def gen(n: Nat, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+(+p):
      gen(p, U32.from_nat(p) <> acc)

def gen2(n: Nat, acc: List<&2, U32>) -> List<&2, U32>:
  match n:
    case 0n:
      acc
    case 1n+(+p):
      gen2(p, U32.from_nat(p) <> acc)

def sum(xs: List<&2, U32>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      sum(t, (acc + x : U32))

def double(xs: List<&2, U32>) -> List<&2, U32>:
  match xs:
    case []:
      []
    case x <> t:
      (x * 2 : U32) <> double(t)

def show(xs: List<U32>) -> String:
  match xs:
    case []:
      ""
    case x <> t:
      U32.show(x) ++ "," ++ show(t)

# A pair of shows appended (fused twice over; the parameters stay apart).
def pair(a: U32, b: U32) -> String:
  "(" ++ U32.show(a) ++ ", " ++ U32.show(b) ++ ")"

# A def with an erased parameter passed as a function whose type has it:
# the application passes the erased argument too.
law pick:
  for -x: Nat
  for  y: Nat
  Nat

def pick(x, y):
  y

law apply:
  for f: @-x: Nat -> @y: Nat -> Nat
  Nat

def apply(f):
  f(3n, 4n)

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(kinds("abcab"))
    IO.print(U32.show(tree(10n)))
    IO.print(show(List.map(~U32, ~U32, ~inc, gen(10n, []))))
    IO.print(show(List.map(~U32, ~U32, ~x => (x * 3 : U32), List.map(~U32, ~U32, ~inc, gen(10n, [])))))
    IO.print(U32.show(List.foldr(~&1, ~U32, ~U32, ~x => acc => U32.xor(x, acc), List.map(~U32, ~U32, ~x => (x >> 1n : U32), List.map(~U32, ~U32, ~x => (x + 7 : U32), gen(10n, []))), 3)))
    IO.print(U32.show(List.foldl(~&1, ~U32, ~U32, ~acc => x => (acc * 3 + x : U32), List.map(~U32, ~U32, ~x => (x + 1 : U32), gen(10n, [])), 0)))
    IO.print(U32.show(sum(List.filter(~U32, ~x => U32.is_even(x), gen2(10n, [])), 0)))
    IO.print(U32.show(sum(double(double(gen2(10n, []))), 5)))
    IO.print(Nat.show(List.length(&1, U32, List.map(~U32, ~U32, ~inc, gen(10n, [])))))
    IO.print(U32.show(sum(List.filter(~U32, ~x => U32.is_even(U32.shrn(x, 1n)), double(gen2(10n, []))), 0)))
    IO.print(pair(3, 4) ++ pair(0, 12))
    IO.print(Nat.show(apply(pick)))
