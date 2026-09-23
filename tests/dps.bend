import Base

# Defs that build their result around a tail call compile to D_ functions
# (destination-passing): no stack frame per element.

# A hole in the last field, self-recursive.
def upto(n: Nat, +i: U32) -> List<U32>:
  match n:
    case 0n:
      []
    case 1n+p:
      i <> upto(p, U32.inc(i))

# A hole in a middle field of a five-field node.
type Chain is Data:
  Link{a: U32, rest: Chain, b: U32, c: U32, d: U32}
  End{}

def chain(n: Nat, +i: U32) -> Chain:
  match n:
    case 0n:
      End{}
    case 1n+p:
      Link{i, chain(p, U32.inc(i)), (i * 2 : U32), (i * 3 : U32), 7}

def chain.sum(c: Chain, acc: U32) -> U32:
  match c:
    case End{}:
      acc
    case Link{a, rest, b, c, d}:
      chain.sum(rest, (acc + a + b + c + d : U32))

# Erased parameters: the kept ones are not the first C parameters.
def rep(-A: Data, n: Nat, +x: A) -> List<A>:
  match n:
    case 0n:
      []
    case 1n+p:
      x <> rep(A, p, x)

# A group of three with different arities: merge picks through a helper,
# and the helper's calls go back through a plain tail call.
law merge:
  for xs: List<U32>
  for ys: List<U32>
  List<U32>

@unsafe
def merge.go(+x: U32, xt: List<U32>, ys: List<U32>) -> List<U32>:
  merge(x <> xt, ys)

@unsafe
def merge.pick(le: Bool, +x: U32, xt: List<U32>, +y: U32, yt: List<U32>) -> List<U32>:
  match le:
    case True{}:
      x <> merge(xt, y <> yt)
    case False{}:
      y <> merge.go(x, xt, yt)

@unsafe
def merge(xs, ys):
  match xs ys:
    case Nil{} zs:
      zs
    case zs Nil{}:
      zs
    case +x <> xt +y <> yt:
      merge.pick(U32.is_le(x, y), x, xt, y, yt)

def split(xs: List<U32>, a: List<U32>, b: List<U32>) -> List<U32> & List<U32>:
  match xs:
    case []:
      (a, b)
    case x <> t:
      split(t, b, x <> a)

law msort:
  for xs: List<U32>
  List<U32>

@unsafe
def msort.halves(h: List<U32> & List<U32>) -> List<U32>:
  (a, b) = h
  merge(msort(a), msort(b))

@unsafe
def msort(xs):
  match xs:
    case []:
      []
    case x <> []:
      [x]
    case +x <> +t:
      msort.halves(split(x <> t, [], []))

def gen(n: Nat, s: U32, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      +t = (s * 1103515245 + 12345 : U32)
      gen(p, t, U32.shrn(t, 8n) <> acc)

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      sum(t, (acc + x : U32))

# Sorts rounds lists of 5000, about 1 GB of allocation in all: the collector
# runs while merges have holes open.
law rounds:
  for k: Nat
  for +seed: U32
  for acc: U32
  for ok: Bool
  String

@unsafe
def rounds.next(k: Nat, +seed: U32, acc: U32, ok: Bool, xs: List<U32>, +prev: U32) -> String:
  match xs:
    case []:
      rounds(k, seed, acc, ok)
    case +x <> t:
      rounds.next(k, seed, (acc + x : U32), Bool.and(ok, U32.is_le(prev, x)), t, x)

@unsafe
def rounds(k, seed, acc, ok):
  match k:
    case 0n:
      U32.show(acc) ++ Bool.pick(String, ok, " sorted", " unsorted")
    case 1n+p:
      rounds.next(p, (seed * 69069 + 1 : U32), acc, ok, msort(gen(5000n, seed, [])), 0)

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(sum(upto(5000n, 1), 0)))
    IO.print(U32.show(chain.sum(chain(5000n, 1), 0)))
    IO.print(U32.show(sum(rep(U32, 5000n, 3), 0)))
    IO.print(rounds(400n, 7, 0, True{}))
