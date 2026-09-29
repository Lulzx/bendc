import Base
# Frees on many threads, checked: tests/par_free.cflags builds the runtime
# with BEND_DEBUG_POISON (a node a match frees, or takes for reuse, is
# poisoned, and a match that meets one stops). The tree-bitonic benchmark,
# smaller and run a few times, forking deep (tests/par_free.env). A match
# reads a node's fields, then frees its slot; the free cleared the slot's
# allocation bit relaxed, and on arm64 the reads could finish after another
# thread made a node in the slot: they got that node's fields, and the
# thread went on to free or rebuild nodes the other one still held.

type Tree is Data:
  Leaf{v: U32}
  Node{l: Tree, r: Tree}

type Stat is Data:
  St{lo: U32, hi: U32, ok: U32, mx: U32}

# xorshift: x ^= x<<13; x ^= x>>17; x ^= x<<5
def prng(+x: U32) -> U32:
  +b = U32.xor(x, U32.shln(x, 13n))
  +d = U32.xor(b, U32.shrn(b, 17n))
  U32.xor(d, U32.shln(d, 5n))

def key(i: U32) -> U32:
  prng(U32.mul(U32.inc(i), 2654435761))

def warp_leaf.go(x: U32, y: U32, t: Bool) -> Tree:
  match t:
    case False{}:
      Node{Leaf{x}, Leaf{y}}
    case True{}:
      Node{Leaf{y}, Leaf{x}}

def warp_leaf(+x: U32, +y: U32, s: Bool) -> Tree:
  warp_leaf.go(x, y, Bool.xor(s, U32.is_gt(x, y)))

def warp_zip(wa: Tree, wb: Tree) -> Tree:
  match wa wb:
    case Node{a0, a1} Node{b0, b1}:
      Node{Node{a0, b0}, Node{a1, b1}}
    case Node{a0, a1} Leaf{bv}:
      Leaf{0}
    case Leaf{av} Node{b0, b1}:
      Leaf{0}
    case Leaf{av} Leaf{bv}:
      Leaf{0}

def warp(a: Tree, b: Tree, +s: Bool) -> Tree:
  match a b:
    case Leaf{av} Leaf{bv}:
      warp_leaf(av, bv, s)
    case Leaf{av} Node{ba, bb}:
      Leaf{0}
    case Node{aa, ab} Leaf{bv}:
      Leaf{0}
    case Node{aa, ab} Node{ba, bb}:
      wa wb = warp(aa, ba, s) warp(ab, bb, s)
      warp_zip(wa, wb)

def warp_node(t: Tree, +s: Bool) -> Tree:
  match t:
    case Leaf{v}:
      Leaf{v}
    case Node{a, b}:
      warp(a, b, s)

def flow(+d: Nat, +s: Bool, w: Tree) -> Tree:
  match d w:
    case 0n Leaf{v}:
      Leaf{v}
    case 0n Node{wa, wb}:
      Node{wa, wb}
    case 1n+p Leaf{v}:
      Leaf{v}
    case 1n+p Node{wa, wb}:
      fa fb = flow(p, s, warp_node(wa, s)) flow(p, s, warp_node(wb, s))
      Node{fa, fb}

def bsort(+d: Nat, +s: Bool, +x: U32) -> Tree:
  match d:
    case 0n:
      Leaf{key(x)}
    case 1n+p:
      sa sb = bsort(p, False{}, U32.inc(U32.shl(x))) bsort(p, True{}, U32.shl(x))
      flow(p, s, warp(sa, sb, s))

def stat_join.go(alo: U32, bhi: U32, aok: U32, bok: U32, amx: U32,
                 bmx: U32, t: Bool) -> Stat:
  match t:
    case False{}:
      St{alo, bhi, 0, U32.add(U32.mul(amx, 2654435761), bmx)}
    case True{}:
      St{alo, bhi, U32.and(aok, bok), U32.add(U32.mul(amx, 2654435761), bmx)}

def stat_join(a: Stat, b: Stat) -> Stat:
  match a b:
    case St{alo, ahi, aok, amx} St{blo, bhi, bok, bmx}:
      stat_join.go(alo, bhi, aok, bok, amx, bmx, U32.is_le(ahi, blo))

def scan(t: Tree) -> Stat:
  match t:
    case Leaf{+v}:
      St{v, v, 1, v}
    case Node{a, b}:
      l r = scan(a) scan(b)
      stat_join(l, r)

def stat_out(s: Stat) -> U32:
  match s:
    case St{lo, hi, ok, mx}:
      U32.add(U32.xor(U32.mul(mx, 2654435761), U32.add(hi, U32.mul(lo, 340573321))), U32.mul(ok, 2246822519))

# n sorts of 2^d leaves, their checksums mixed
def rounds(n: Nat, +d: Nat, +i: U32, acc: U32) -> U32:
  match n:
    case 0n:
      acc
    case 1n+p:
      rounds(p, d, U32.inc(i), U32.add(U32.mul(acc, 31), stat_out(scan(bsort(d, False{}, U32.shl(i))))))

def main() -> IO(Unit):
  IO.print(U32.show(rounds(3n, 18n, 1, 0)))
