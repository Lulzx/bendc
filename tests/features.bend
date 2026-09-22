import Base

# A law with a proof: proofs are erased at runtime.
law add_zero:
  for x: Nat
  {Nat.add(x, 0n) == x : Nat}

def add_zero(x):
  match x:
    case 0n:
      {==}
    case 1n+p:
      %add_zero(p) : {1n+Nat.add(p, 0n) == 1n+_ : Nat}
      {==}

type Tree is Data:
  Leaf{}
  Node{l: Tree, v: U32, r: Tree}

def to_list(t: Tree, acc: List<&2, U32>) -> List<&2, U32>:
  match t:
    case Leaf{}:
      acc
    case Node{l, v, r}:
      to_list(l, v <> to_list(r, acc))

def depth(t: Tree) -> Nat:
  match t:
    case Leaf{}:
      0n
    case Node{l, v, r}:
      1n+Nat.max(depth(l), depth(r))

# Nested and literal patterns.
def classify(c: Char) -> String:
  match c:
    case 'a':
      "letter a"
    case '\n':
      "newline"
    case other:
      "other"

def firsts(xs: List<&2, List<&2, U32>>) -> List<&2, U32>:
  match xs:
    case Nil{}:
      Nil{}
    case (h <> t) <> rest:
      h <> firsts(rest)
    case Nil{} <> rest:
      firsts(rest)

def nat_kind(n: Nat) -> String:
  match n:
    case 0n:
      "zero"
    case 1n:
      "one"
    case 2n+k:
      "big(" ++ Nat.show(k) ++ ")"

# Closures capturing several variables, and currying.
def make(a: U32, b: U32, +c: U32) -> U32 -> U32 -> U32:
  x => y => (((a * x : U32) + (b * y : U32) : U32) + c : U32)

def compose(f: U32 -> U32, g: U32 -> U32) -> U32 -> U32:
  x => f(g(x))

def bits(+x: U32) -> String:
  U32.show((x .&. 255 : U32)) ++ " " ++ U32.show((x .|. 1 : U32)) ++ " " ++
    U32.show((x .^. 15 : U32)) ++ " " ++ U32.show((x << 3n : U32)) ++ " " ++
    U32.show((x >> 2n : U32))

def logic(+a: U32, +b: U32) -> String:
  Bool.show((a < b : U32) && (b <= 100 : U32)) ++ " " ++ Bool.show((a > b : U32) || (a >= 5 : U32))

def arr_fill(i: Nat, a: Array<U32>) -> Array<U32>:
  match i:
    case 0n:
      a
    case 1n+ +p:
      arr_fill(p, Array.set(U32, a, U32.from_nat(p), (U32.from_nat(p) * 3 : U32)))

law insert:
  for t: Tree
  for +x: U32
  Tree

@unsafe
def insert.go(l: Tree, +v: U32, r: Tree, +x: U32, c: Cmp) -> Tree:
  match c:
    case LT{}:
      Node{insert(l, x), v, r}
    case EQ{}:
      Node{l, v, r}
    case GT{}:
      Node{l, v, insert(r, x)}

@unsafe
def insert(t, x):
  match t:
    case Leaf{}:
      Node{Leaf{}, x, Leaf{}}
    case Node{l, +v, r}:
      insert.go(l, v, r, x, U32.cmp(x, v))

def build(xs: List<&2, U32>, t: Tree) -> Tree:
  match xs:
    case Nil{}:
      t
    case h <> rest:
      build(rest, insert(t, h))

law arr_sum:
  for a: Array<U32>
  for i: Nat
  for acc: U32
  U32

@unsafe
def arr_sum.go(p: Nat, acc: U32, r: Array<U32> & U32) -> U32:
  (a, v) = r
  arr_sum(a, p, (acc + v : U32))

@unsafe
def arr_sum(a, i, acc):
  match i:
    case 0n:
      acc
    case 1n+ +p:
      arr_sum.go(p, acc, Array.get(U32, a, U32.from_nat(p)))

def main() -> IO(Unit):
  +t = build([50, 30, 70, 20, 40, 60, 80, 30, 65], Leaf{})
  f = make(2, 3, 4)
  h = compose(x => (x + 1 : U32), x => (x * 10 : U32))
  do IO<Unit>:
    IO.print(List.show(~&2, ~U32, ~U32.show, to_list(t, Nil{})))
    IO.print(Nat.show(depth(t)))
    IO.print(classify('a') ++ ", " ++ classify('\n') ++ ", " ++ classify('z'))
    IO.print(List.show(~&2, ~U32, ~U32.show, firsts([[1, 2], [], [3], [4, 5, 6]])))
    IO.print(nat_kind(0n) ++ " " ++ nat_kind(1n) ++ " " ++ nat_kind(9n))
    IO.print(U32.show(f(10, 100)))
    IO.print(U32.show(h(4)))
    IO.print(bits(1000))
    IO.print(logic(3, 50) ++ " / " ++ logic(60, 50))
    IO.print(U32.show(arr_sum(arr_fill(16n, [0 : U32*16n]), 16n, 0)))
    IO.print(Nat.show(Set.size(Set.from_list(["a", "b", "a", "c", "b"]))))
    IO.print(U32.show((4294967295 + 2 : U32)) ++ " " ++ U32.show((7 / 0 : U32)) ++ " " ++ Nat.show(Nat.sub(3n, 5n)))
    IO.print(F32.show((0.1 + 0.2 : F32)) ++ " " ++ F32.show(F32.floor(F32.neg(2.5))))
    IO.print(String.join(List.reverse(&2, String, ["c", "b", "a"]), ""))
    code : U32 <- IO.pure(U32, 3)
    IO.die(Unit, code, "bye")
