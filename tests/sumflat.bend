import Base

# A type of U32-only constructors becomes a record of its widest
# constructor's fields and a tag: a def passes and returns it as its
# fields. Its values still go in lists, closures and parallel lets, its
# patterns nest, and a variable pattern takes any constructor.

type Acc is Data:
  Acc0{}
  Acc1{a: U32}
  Acc2{a: U32, b: U32}
  Acc3{a: U32, b: U32, c: U32}

def add(x: Acc, +k: U32) -> Acc:
  match x:
    case Acc0{}:
      Acc1{k}
    case Acc1{a}:
      Acc2{a, k}
    case Acc2{a, b}:
      Acc3{a, b, k}
    case Acc3{a, b, c}:
      Acc3{U32.add(a, k), b, U32.xor(c, k)}

def sum(x: Acc) -> U32:
  match x:
    case Acc0{}:
      0
    case Acc1{a}:
      a
    case Acc2{a, b}:
      U32.add(U32.mul(a, 3), b)
    case Acc3{a, b, c}:
      U32.add(U32.add(U32.mul(a, 5), U32.mul(b, 7)), c)

# two scrutinees, and a variable pattern for the rest
def merge(x: Acc, y: Acc) -> Acc:
  match x y:
    case Acc0{} other:
      other
    case Acc1{a} Acc1{b}:
      Acc2{a, b}
    case Acc3{a, b, c} Acc3{d, e, f}:
      Acc3{U32.add(a, d), U32.add(b, e), U32.add(c, f)}
    case p q:
      Acc1{U32.add(sum(p), sum(q))}

def run(+j: Nat, x: Acc) -> Acc:
  match j:
    case 0n:
      x
    case 1n+q:
      run(q, add(x, U32.from_nat(q)))

# a list of them, with a nested pattern
def firsts(xs: List<&2, Acc>) -> U32:
  match xs:
    case Nil{}:
      0
    case Acc1{a} <> t:
      U32.add(a, firsts(t))
    case h <> t:
      U32.add(sum(h), firsts(t))

def build(+j: Nat) -> List<&2, Acc>:
  match j:
    case 0n:
      Nil{}
    case 1n+q:
      run(Nat.mod(q, 5n), Acc0{}) <> build(q)

# a parallel let of them
def tree(+d: Nat, +i: U32) -> Acc:
  match d:
    case 0n:
      run(U32.to_nat(U32.and(i, 3)), Acc1{i})
    case 1n+p:
      a b = tree(p, U32.mul(i, 2)) tree(p, U32.inc(U32.mul(i, 2)))
      merge(a, b)

# closures: one that takes an Acc, one that holds one
def adder(k: U32) -> Acc -> U32:
  x => sum(add(x, k))

def holder(y: Acc) -> U32 -> U32:
  k => sum(add(y, k))

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(sum(run(7n, Acc0{}))))
    IO.print(U32.show(firsts(build(12n))))
    IO.print(U32.show(sum(tree(6n, 1))))
    IO.print(U32.show(U32.add(adder(9)(Acc2{1, 2}), holder(Acc3{4, 5, 6})(7))))
