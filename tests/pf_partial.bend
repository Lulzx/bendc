import Base

type Grove is Data:
  Seed{v: U32}
  Fork{l: Grove, r: Grove}

def zip(u: Grove, v: Grove) -> Grove:
  match u v:
    case Fork{ul, ur} Fork{vl, vr}:
      Fork{Fork{ul, vl}, Fork{ur, vr}}
    case Fork{ul, ur} Seed{v}:
      Seed{0}
    case Seed{u} Fork{vl, vr}:
      Seed{0}
    case Seed{u} Seed{v}:
      Seed{0}

def weave(a: Grove, b: Grove, +flip: Bool) -> Grove:
  match a b:
    case Seed{x} Seed{y}:
      match flip:
        case False{}:
          Fork{Seed{x}, Seed{y}}
        case True{}:
          Fork{Seed{y}, Seed{x}}
    case Fork{al, ar} Fork{bl, br}:
      u v = weave(al, bl, flip) weave(ar, br, flip)
      zip(u, v)
    case Seed{x} Fork{bl, br}:
      Seed{0}
    case Fork{al, ar} Seed{y}:
      Seed{0}

def make(d: Nat, +x: U32) -> Grove:
  match d:
    case 0n:
      Seed{x}
    case 1n+ +p:
      Fork{make(p, U32.add(x, 1)), make(p, U32.add(x, 7))}

def fold(t: Grove) -> U32:
  match t:
    case Seed{x}:
      x
    case Fork{l, r}:
      U32.add(U32.add(U32.mul(fold(l), 13), U32.mul(fold(r), 37)), 1)

def run(+d: Nat, +flip: Bool) -> U32:
  fold(weave(make(d, 3), make(d, 17), flip))

def shared(d: Nat) -> U32:
  +a = make(d, 11)
  U32.add(fold(weave(a, a, False{})), fold(a))

def pass_grove(a: Grove) -> Grove:
  match a:
    case x:
      x

def untouched(+d: Nat) -> Grove:
  a = weave(make(d, 2), make(d, 4), False{})
  pass_grove(a)

def main() -> U32:
  U32.add(fold(weave(make(0n, 3), make(0n, 17), False{})), U32.add(fold(weave(make(0n, 3), make(0n, 17), True{})), U32.add(fold(weave(make(0n, 3), make(1n, 17), False{})), U32.add(fold(weave(make(0n, 3), make(1n, 17), True{})), U32.add(fold(weave(make(0n, 3), make(2n, 17), False{})), U32.add(fold(weave(make(0n, 3), make(2n, 17), True{})), U32.add(fold(weave(make(0n, 3), make(3n, 17), False{})), U32.add(fold(weave(make(0n, 3), make(3n, 17), True{})), U32.add(fold(weave(make(0n, 3), make(4n, 17), False{})), U32.add(fold(weave(make(0n, 3), make(4n, 17), True{})), U32.add(fold(weave(make(1n, 3), make(0n, 17), False{})), U32.add(fold(weave(make(1n, 3), make(0n, 17), True{})), U32.add(fold(weave(make(1n, 3), make(1n, 17), False{})), U32.add(fold(weave(make(1n, 3), make(1n, 17), True{})), U32.add(fold(weave(make(1n, 3), make(2n, 17), False{})), U32.add(fold(weave(make(1n, 3), make(2n, 17), True{})), U32.add(fold(weave(make(1n, 3), make(3n, 17), False{})), U32.add(fold(weave(make(1n, 3), make(3n, 17), True{})), U32.add(fold(weave(make(1n, 3), make(4n, 17), False{})), U32.add(fold(weave(make(1n, 3), make(4n, 17), True{})), U32.add(fold(weave(make(2n, 3), make(0n, 17), False{})), U32.add(fold(weave(make(2n, 3), make(0n, 17), True{})), U32.add(fold(weave(make(2n, 3), make(1n, 17), False{})), U32.add(fold(weave(make(2n, 3), make(1n, 17), True{})), U32.add(fold(weave(make(2n, 3), make(2n, 17), False{})), U32.add(fold(weave(make(2n, 3), make(2n, 17), True{})), U32.add(fold(weave(make(2n, 3), make(3n, 17), False{})), U32.add(fold(weave(make(2n, 3), make(3n, 17), True{})), U32.add(fold(weave(make(2n, 3), make(4n, 17), False{})), U32.add(fold(weave(make(2n, 3), make(4n, 17), True{})), U32.add(fold(weave(make(3n, 3), make(0n, 17), False{})), U32.add(fold(weave(make(3n, 3), make(0n, 17), True{})), U32.add(fold(weave(make(3n, 3), make(1n, 17), False{})), U32.add(fold(weave(make(3n, 3), make(1n, 17), True{})), U32.add(fold(weave(make(3n, 3), make(2n, 17), False{})), U32.add(fold(weave(make(3n, 3), make(2n, 17), True{})), U32.add(fold(weave(make(3n, 3), make(3n, 17), False{})), U32.add(fold(weave(make(3n, 3), make(3n, 17), True{})), U32.add(fold(weave(make(3n, 3), make(4n, 17), False{})), U32.add(fold(weave(make(3n, 3), make(4n, 17), True{})), U32.add(fold(weave(make(4n, 3), make(0n, 17), False{})), U32.add(fold(weave(make(4n, 3), make(0n, 17), True{})), U32.add(fold(weave(make(4n, 3), make(1n, 17), False{})), U32.add(fold(weave(make(4n, 3), make(1n, 17), True{})), U32.add(fold(weave(make(4n, 3), make(2n, 17), False{})), U32.add(fold(weave(make(4n, 3), make(2n, 17), True{})), U32.add(fold(weave(make(4n, 3), make(3n, 17), False{})), U32.add(fold(weave(make(4n, 3), make(3n, 17), True{})), U32.add(fold(weave(make(4n, 3), make(4n, 17), False{})), U32.add(fold(weave(make(4n, 3), make(4n, 17), True{})), U32.add(shared(0n), U32.add(shared(1n), U32.add(shared(2n), U32.add(shared(3n), shared(4n)))))))))))))))))))))))))))))))))))))))))))))))))))))))
