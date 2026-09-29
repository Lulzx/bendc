import Base
# Case fields and lets that rebind a parameter's name: the parameter is used
# once (not shared), its node is freed by the match; where another path uses
# it twice it is still shared.

type T is Data:
  Lf{a: U32, b: U32}
  Nd{l: T, r: T}

type P is Data:
  P{a: U32, b: U32}

def mk(+d: Nat, +s: U32) -> T:
  match d:
    case 0n:
      Lf{s, U32.mul(s, 3)}
    case 1n+p:
      Nd{mk(p, U32.inc(U32.mul(s, 2))), mk(p, U32.mul(s, 2))}

def zip(a: T, b: T) -> T:
  match a b:
    case Lf{a, b} Lf{c, d}:
      Lf{U32.add(a, c), U32.add(b, d)}
    case Lf{a, b} Nd{l, r}:
      Lf{a, b}
    case Nd{l, r} Lf{a, b}:
      Nd{l, r}
    case Nd{a, b} Nd{c, d}:
      Nd{zip(a, c), zip(b, d)}

def sum(t: T) -> U32:
  match t:
    case Lf{a, b}:
      U32.add(U32.mul(a, 7), b)
    case Nd{l, r}:
      U32.add(U32.mul(sum(l), 31), sum(r))

def both(x: P, y: P) -> U32:
  match x y:
    case P{a, b} P{c, d}:
      U32.add(U32.mul(a, d), U32.mul(b, c))

def psum(a: P) -> U32:
  match a:
    case P{a, b}:
      U32.add(a, b)

def pick(+a: P, k: Bool) -> U32:
  match k:
    case True{}:
      both(a, a)
    case False{}:
      psum(a)

def relet(a: U32, t: T) -> U32:
  a = sum(t)
  U32.mul(a, 5)

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(U32.show(sum(zip(zip(mk(6n, 1), mk(6n, 5)), mk(6n, 9)))))
    IO.print(U32.show(pick(P{3, 4}, True{})))
    IO.print(U32.show(pick(P{3, 4}, False{})))
    IO.print(U32.show(relet(1, mk(4n, 2))))
