import Base

# Nodes of 2 to 6 words, in blocks that are fresh and in blocks the
# collector left partly free (every other node of a list stays), on the
# worker threads too.
type Sh is Data:
  S1{a: U32}
  S2{a: U32, b: U32}
  S3{a: U32, b: U32, c: U32}
  S4{a: U32, b: U32, c: U32, d: U32}
  S5{a: U32, b: U32, c: U32, d: U32, e: U32}

def mk.go(+r: U32, +i: U32) -> Sh:
  match r:
    case 0:
      S1{i}
    case 1:
      S2{i, 1}
    case 2:
      S3{i, 1, 2}
    case 3:
      S4{i, 1, 2, 3}
    case other:
      S5{i, 1, 2, 3, 4}

def mk(+i: U32) -> Sh:
  mk.go((i % 5 : U32), i)

def val(x: Sh) -> U32:
  match x:
    case S1{+a}:
      a
    case S2{+a, +b}:
      (a + b : U32)
    case S3{+a, +b, +c}:
      (a + b + c : U32)
    case S4{+a, +b, +c, +d}:
      (a + b + c + d : U32)
    case S5{+a, +b, +c, +d, +e}:
      (a + b + c + d + e : U32)

def build(n: Nat, +i: U32, acc: List<Sh>) -> List<Sh>:
  match n:
    case 0n:
      acc
    case 1n+p:
      build(p, U32.inc(i), mk(i) <> acc)

# Every other node.
def halve(xs: List<Sh>) -> List<Sh>:
  match xs:
    case Nil{}:
      Nil{}
    case Con{h, t}:
      match t:
        case Nil{}:
          [h]
        case Con{u, r}:
          h <> halve(r)

def sum(xs: List<Sh>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case Con{h, t}:
      sum(t, (acc + val(h) : U32))

def round(k: Nat, +i: U32, keep: List<Sh>) -> U32:
  match k:
    case 0n:
      sum(keep, 0)
    case 1n+p:
      round(p, (i + 20000 : U32), halve(build(20000n, i, keep)))

def work(+s: U32) -> U32:
  round(40n, s, [])

def main() -> IO(Unit):
  a b = work(0) work(7)
  c d = work(11) work(13)
  IO.print(U32.show((a + b + c + d : U32)))
