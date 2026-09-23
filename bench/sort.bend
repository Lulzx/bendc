import Base

# Sequential allocation-heavy work: build a pseudo-random list of 1M U32s,
# merge sort it, and sum it.
def gen(n: Nat, s: U32, acc: List<U32>) -> List<U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      +t = (s * 1103515245 + 12345 : U32)
      gen(p, t, U32.shrn(t, 8n) <> acc)

def split(xs: List<U32>, a: List<U32>, b: List<U32>) -> List<U32> & List<U32>:
  match xs:
    case []:
      (a, b)
    case x <> t:
      split(t, b, x <> a)

law merge:
  for xs: List<U32>
  for ys: List<U32>
  List<U32>

@unsafe
def merge.pick(le: Bool, +x: U32, xt: List<U32>, +y: U32, yt: List<U32>) -> List<U32>:
  match le:
    case True{}:
      x <> merge(xt, y <> yt)
    case False{}:
      y <> merge(x <> xt, yt)

@unsafe
def merge(xs, ys):
  match xs ys:
    case Nil{} zs:
      zs
    case zs Nil{}:
      zs
    case +x <> xt +y <> yt:
      merge.pick(U32.is_le(x, y), x, xt, y, yt)

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

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      sum(t, (acc + x : U32))

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
    IO.print(U32.show(sum(msort(gen(arg(args, 1000000n), 7, [])), 0)))
