import Base

# List pipelines over Base's higher-order list functions and user-defined
# ones: each stage builds a list the next one walks, unless the compiler
# fuses them. Each round builds pseudo-random lists of U32s, then maps,
# filters and folds them.
def gen(n: Nat, s: U32, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      +t = (s * 1103515245 + 12345 : U32)
      gen(p, t, U32.shrn(t, 8n) <> acc)

def gen2(n: Nat, s: U32, acc: List<&2, U32>) -> List<&2, U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      +t = (s * 1103515245 + 12345 : U32)
      gen2(p, t, U32.shrn(t, 8n) <> acc)

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

def round(+n: Nat, +s: U32) -> U32:
  +a = List.foldl(~&1, ~U32, ~U32, ~acc => x => (acc + x : U32), List.map(~U32, ~U32, ~x => (x * 3 + 1 : U32), gen(n, s, [])), 0)
  +b = sum(List.filter(~U32, ~x => U32.is_even(x), gen2(n, (s + 1 : U32), [])), 0)
  +c = List.foldr(~&1, ~U32, ~U32, ~x => acc => U32.xor(x, acc), List.map(~U32, ~U32, ~x => (x >> 3n : U32), List.map(~U32, ~U32, ~x => (x + 7 : U32), gen(n, (s + 2 : U32), []))), s)
  +d = U32.from_nat(List.length(&1, U32, List.map(~U32, ~U32, ~x => (x * 5 : U32), gen(n, (s + 3 : U32), []))))
  +e = sum(double(double(gen2(n, (s + 4 : U32), []))), 0)
  U32.xor(U32.xor(a, b), U32.xor(U32.xor(c, d), e))

def rounds(k: Nat, +n: Nat, acc: U32) -> U32:
  match k:
    case 0n:
      acc
    case 1n+(+p):
      rounds(p, n, (acc * 31 + round(n, U32.from_nat(p)) : U32))

# The size comes from the command line (its last number), so no compiler
# can fold the work away at compile time.
def arg(xs: List<String>, d: Nat) -> Nat:
  match xs:
    case x <> t:
      arg(t, Maybe.default(&2, Nat, Nat.read(x), d))
    case []:
      d

def main() -> IO(Unit):
  do IO<Unit>:
    args : List<String> <- IO.args()
    IO.print(U32.show(rounds(20n, arg(args, 100000n), 0)))
