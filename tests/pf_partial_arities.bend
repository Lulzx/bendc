import Base

type Grove3 is Data:
  Seed3{v: U32}
  Pack3{c0: Grove3, c1: Grove3, c2: Grove3}

def consume3(u: Grove3, v: Grove3) -> Grove3:
  match u v:
    case Pack3{u0, u1, u2} Pack3{v0, v1, v2}:
      Pack3{u0, v0, u1}
    case Pack3{u0, u1, u2} Seed3{x}:
      Seed3{0}
    case Seed3{x} Pack3{v0, v1, v2}:
      Seed3{0}
    case Seed3{x} Seed3{y}:
      Seed3{0}

def fan3(a: Grove3, b: Grove3, +flip: Bool) -> Grove3:
  match a b:
    case Seed3{+x} Seed3{+y}:
      match flip:
        case False{}:
          Pack3{Seed3{x}, Seed3{y}, Seed3{x}}
        case True{}:
          Pack3{Seed3{y}, Seed3{x}, Seed3{y}}
    case Pack3{a0, a1, a2} Pack3{b0, b1, b2}:
      u v = fan3(a0, b0, flip) fan3(a1, b1, flip)
      consume3(u, v)
    case Seed3{x} Pack3{b0, b1, b2}:
      Seed3{0}
    case Pack3{a0, a1, a2} Seed3{y}:
      Seed3{0}

def make3(d: Nat, +x: U32) -> Grove3:
  match d:
    case 0n:
      Seed3{x}
    case 1n+ +p:
      Pack3{make3(p, U32.add(x, 1)), make3(p, U32.add(x, 2)), make3(p, U32.add(x, 3))}

def fold3(t: Grove3) -> U32:
  match t:
    case Seed3{x}:
      x
    case Pack3{c0, c1, c2}:
      U32.add(U32.mul(fold3(c2), 37), U32.add(U32.mul(fold3(c1), 25), U32.add(U32.mul(fold3(c0), 13), 1)))

def run3(a: Grove3, b: Grove3, flip: Bool) -> U32:
  fold3(fan3(a, b, flip))

def shared3(d: Nat) -> U32:
  +a = make3(d, 11)
  U32.add(run3(a, a, False{}), fold3(a))

type Grove8 is Data:
  Seed8{v: U32}
  Pack8{c0: Grove8, c1: Grove8, c2: Grove8, c3: Grove8, c4: Grove8, c5: Grove8, c6: Grove8, c7: Grove8}

def consume8(u: Grove8, v: Grove8) -> Grove8:
  match u v:
    case Pack8{u0, u1, u2, u3, u4, u5, u6, u7} Pack8{v0, v1, v2, v3, v4, v5, v6, v7}:
      Pack8{u0, v0, u1, v1, u2, v2, u3, v3}
    case Pack8{u0, u1, u2, u3, u4, u5, u6, u7} Seed8{x}:
      Seed8{0}
    case Seed8{x} Pack8{v0, v1, v2, v3, v4, v5, v6, v7}:
      Seed8{0}
    case Seed8{x} Seed8{y}:
      Seed8{0}

def fan8(a: Grove8, b: Grove8, +flip: Bool) -> Grove8:
  match a b:
    case Seed8{+x} Seed8{+y}:
      match flip:
        case False{}:
          Pack8{Seed8{x}, Seed8{y}, Seed8{x}, Seed8{y}, Seed8{x}, Seed8{y}, Seed8{x}, Seed8{y}}
        case True{}:
          Pack8{Seed8{y}, Seed8{x}, Seed8{y}, Seed8{x}, Seed8{y}, Seed8{x}, Seed8{y}, Seed8{x}}
    case Pack8{a0, a1, a2, a3, a4, a5, a6, a7} Pack8{b0, b1, b2, b3, b4, b5, b6, b7}:
      u v = fan8(a0, b0, flip) fan8(a1, b1, flip)
      consume8(u, v)
    case Seed8{x} Pack8{b0, b1, b2, b3, b4, b5, b6, b7}:
      Seed8{0}
    case Pack8{a0, a1, a2, a3, a4, a5, a6, a7} Seed8{y}:
      Seed8{0}

def make8(d: Nat, +x: U32) -> Grove8:
  match d:
    case 0n:
      Seed8{x}
    case 1n+ +p:
      Pack8{make8(p, U32.add(x, 1)), make8(p, U32.add(x, 2)), make8(p, U32.add(x, 3)), make8(p, U32.add(x, 4)), make8(p, U32.add(x, 5)), make8(p, U32.add(x, 6)), make8(p, U32.add(x, 7)), make8(p, U32.add(x, 8))}

def fold8(t: Grove8) -> U32:
  match t:
    case Seed8{x}:
      x
    case Pack8{c0, c1, c2, c3, c4, c5, c6, c7}:
      U32.add(U32.mul(fold8(c7), 97), U32.add(U32.mul(fold8(c6), 85), U32.add(U32.mul(fold8(c5), 73), U32.add(U32.mul(fold8(c4), 61), U32.add(U32.mul(fold8(c3), 49), U32.add(U32.mul(fold8(c2), 37), U32.add(U32.mul(fold8(c1), 25), U32.add(U32.mul(fold8(c0), 13), 1))))))))

def run8(a: Grove8, b: Grove8, flip: Bool) -> U32:
  fold8(fan8(a, b, flip))

def shared8(d: Nat) -> U32:
  +a = make8(d, 11)
  U32.add(run8(a, a, False{}), fold8(a))

type Grove9 is Data:
  Seed9{v: U32}
  Pack9{c0: Grove9, c1: Grove9, c2: Grove9, c3: Grove9, c4: Grove9, c5: Grove9, c6: Grove9, c7: Grove9, c8: Grove9}

def consume9(u: Grove9, v: Grove9) -> Grove9:
  match u v:
    case Pack9{u0, u1, u2, u3, u4, u5, u6, u7, u8} Pack9{v0, v1, v2, v3, v4, v5, v6, v7, v8}:
      Pack9{u0, v0, u1, v1, u2, v2, u3, v3, u4}
    case Pack9{u0, u1, u2, u3, u4, u5, u6, u7, u8} Seed9{x}:
      Seed9{0}
    case Seed9{x} Pack9{v0, v1, v2, v3, v4, v5, v6, v7, v8}:
      Seed9{0}
    case Seed9{x} Seed9{y}:
      Seed9{0}

def fan9(a: Grove9, b: Grove9, +flip: Bool) -> Grove9:
  match a b:
    case Seed9{+x} Seed9{+y}:
      match flip:
        case False{}:
          Pack9{Seed9{x}, Seed9{y}, Seed9{x}, Seed9{y}, Seed9{x}, Seed9{y}, Seed9{x}, Seed9{y}, Seed9{x}}
        case True{}:
          Pack9{Seed9{y}, Seed9{x}, Seed9{y}, Seed9{x}, Seed9{y}, Seed9{x}, Seed9{y}, Seed9{x}, Seed9{y}}
    case Pack9{a0, a1, a2, a3, a4, a5, a6, a7, a8} Pack9{b0, b1, b2, b3, b4, b5, b6, b7, b8}:
      u v = fan9(a0, b0, flip) fan9(a1, b1, flip)
      consume9(u, v)
    case Seed9{x} Pack9{b0, b1, b2, b3, b4, b5, b6, b7, b8}:
      Seed9{0}
    case Pack9{a0, a1, a2, a3, a4, a5, a6, a7, a8} Seed9{y}:
      Seed9{0}

def make9(d: Nat, +x: U32) -> Grove9:
  match d:
    case 0n:
      Seed9{x}
    case 1n+ +p:
      Pack9{make9(p, U32.add(x, 1)), make9(p, U32.add(x, 2)), make9(p, U32.add(x, 3)), make9(p, U32.add(x, 4)), make9(p, U32.add(x, 5)), make9(p, U32.add(x, 6)), make9(p, U32.add(x, 7)), make9(p, U32.add(x, 8)), make9(p, U32.add(x, 9))}

def fold9(t: Grove9) -> U32:
  match t:
    case Seed9{x}:
      x
    case Pack9{c0, c1, c2, c3, c4, c5, c6, c7, c8}:
      U32.add(U32.mul(fold9(c8), 109), U32.add(U32.mul(fold9(c7), 97), U32.add(U32.mul(fold9(c6), 85), U32.add(U32.mul(fold9(c5), 73), U32.add(U32.mul(fold9(c4), 61), U32.add(U32.mul(fold9(c3), 49), U32.add(U32.mul(fold9(c2), 37), U32.add(U32.mul(fold9(c1), 25), U32.add(U32.mul(fold9(c0), 13), 1)))))))))

def run9(a: Grove9, b: Grove9, flip: Bool) -> U32:
  fold9(fan9(a, b, flip))

def shared9(d: Nat) -> U32:
  +a = make9(d, 11)
  U32.add(run9(a, a, False{}), fold9(a))

def main() -> U32:
  U32.add(shared9(3n), U32.add(run9(make9(3n, 3), make9(3n, 17), True{}), U32.add(run9(make9(3n, 3), make9(3n, 17), False{}), U32.add(run9(make9(3n, 3), make9(2n, 17), True{}), U32.add(run9(make9(3n, 3), make9(2n, 17), False{}), U32.add(run9(make9(3n, 3), make9(1n, 17), True{}), U32.add(run9(make9(3n, 3), make9(1n, 17), False{}), U32.add(run9(make9(3n, 3), make9(0n, 17), True{}), U32.add(run9(make9(3n, 3), make9(0n, 17), False{}), U32.add(run9(make9(2n, 3), make9(3n, 17), True{}), U32.add(run9(make9(2n, 3), make9(3n, 17), False{}), U32.add(run9(make9(2n, 3), make9(2n, 17), True{}), U32.add(run9(make9(2n, 3), make9(2n, 17), False{}), U32.add(run9(make9(2n, 3), make9(1n, 17), True{}), U32.add(run9(make9(2n, 3), make9(1n, 17), False{}), U32.add(run9(make9(2n, 3), make9(0n, 17), True{}), U32.add(run9(make9(2n, 3), make9(0n, 17), False{}), U32.add(run9(make9(1n, 3), make9(3n, 17), True{}), U32.add(run9(make9(1n, 3), make9(3n, 17), False{}), U32.add(run9(make9(1n, 3), make9(2n, 17), True{}), U32.add(run9(make9(1n, 3), make9(2n, 17), False{}), U32.add(run9(make9(1n, 3), make9(1n, 17), True{}), U32.add(run9(make9(1n, 3), make9(1n, 17), False{}), U32.add(run9(make9(1n, 3), make9(0n, 17), True{}), U32.add(run9(make9(1n, 3), make9(0n, 17), False{}), U32.add(run9(make9(0n, 3), make9(3n, 17), True{}), U32.add(run9(make9(0n, 3), make9(3n, 17), False{}), U32.add(run9(make9(0n, 3), make9(2n, 17), True{}), U32.add(run9(make9(0n, 3), make9(2n, 17), False{}), U32.add(run9(make9(0n, 3), make9(1n, 17), True{}), U32.add(run9(make9(0n, 3), make9(1n, 17), False{}), U32.add(run9(make9(0n, 3), make9(0n, 17), True{}), U32.add(run9(make9(0n, 3), make9(0n, 17), False{}), U32.add(shared8(3n), U32.add(run8(make8(3n, 3), make8(3n, 17), True{}), U32.add(run8(make8(3n, 3), make8(3n, 17), False{}), U32.add(run8(make8(3n, 3), make8(2n, 17), True{}), U32.add(run8(make8(3n, 3), make8(2n, 17), False{}), U32.add(run8(make8(3n, 3), make8(1n, 17), True{}), U32.add(run8(make8(3n, 3), make8(1n, 17), False{}), U32.add(run8(make8(3n, 3), make8(0n, 17), True{}), U32.add(run8(make8(3n, 3), make8(0n, 17), False{}), U32.add(run8(make8(2n, 3), make8(3n, 17), True{}), U32.add(run8(make8(2n, 3), make8(3n, 17), False{}), U32.add(run8(make8(2n, 3), make8(2n, 17), True{}), U32.add(run8(make8(2n, 3), make8(2n, 17), False{}), U32.add(run8(make8(2n, 3), make8(1n, 17), True{}), U32.add(run8(make8(2n, 3), make8(1n, 17), False{}), U32.add(run8(make8(2n, 3), make8(0n, 17), True{}), U32.add(run8(make8(2n, 3), make8(0n, 17), False{}), U32.add(run8(make8(1n, 3), make8(3n, 17), True{}), U32.add(run8(make8(1n, 3), make8(3n, 17), False{}), U32.add(run8(make8(1n, 3), make8(2n, 17), True{}), U32.add(run8(make8(1n, 3), make8(2n, 17), False{}), U32.add(run8(make8(1n, 3), make8(1n, 17), True{}), U32.add(run8(make8(1n, 3), make8(1n, 17), False{}), U32.add(run8(make8(1n, 3), make8(0n, 17), True{}), U32.add(run8(make8(1n, 3), make8(0n, 17), False{}), U32.add(run8(make8(0n, 3), make8(3n, 17), True{}), U32.add(run8(make8(0n, 3), make8(3n, 17), False{}), U32.add(run8(make8(0n, 3), make8(2n, 17), True{}), U32.add(run8(make8(0n, 3), make8(2n, 17), False{}), U32.add(run8(make8(0n, 3), make8(1n, 17), True{}), U32.add(run8(make8(0n, 3), make8(1n, 17), False{}), U32.add(run8(make8(0n, 3), make8(0n, 17), True{}), U32.add(run8(make8(0n, 3), make8(0n, 17), False{}), U32.add(shared3(3n), U32.add(run3(make3(3n, 3), make3(3n, 17), True{}), U32.add(run3(make3(3n, 3), make3(3n, 17), False{}), U32.add(run3(make3(3n, 3), make3(2n, 17), True{}), U32.add(run3(make3(3n, 3), make3(2n, 17), False{}), U32.add(run3(make3(3n, 3), make3(1n, 17), True{}), U32.add(run3(make3(3n, 3), make3(1n, 17), False{}), U32.add(run3(make3(3n, 3), make3(0n, 17), True{}), U32.add(run3(make3(3n, 3), make3(0n, 17), False{}), U32.add(run3(make3(2n, 3), make3(3n, 17), True{}), U32.add(run3(make3(2n, 3), make3(3n, 17), False{}), U32.add(run3(make3(2n, 3), make3(2n, 17), True{}), U32.add(run3(make3(2n, 3), make3(2n, 17), False{}), U32.add(run3(make3(2n, 3), make3(1n, 17), True{}), U32.add(run3(make3(2n, 3), make3(1n, 17), False{}), U32.add(run3(make3(2n, 3), make3(0n, 17), True{}), U32.add(run3(make3(2n, 3), make3(0n, 17), False{}), U32.add(run3(make3(1n, 3), make3(3n, 17), True{}), U32.add(run3(make3(1n, 3), make3(3n, 17), False{}), U32.add(run3(make3(1n, 3), make3(2n, 17), True{}), U32.add(run3(make3(1n, 3), make3(2n, 17), False{}), U32.add(run3(make3(1n, 3), make3(1n, 17), True{}), U32.add(run3(make3(1n, 3), make3(1n, 17), False{}), U32.add(run3(make3(1n, 3), make3(0n, 17), True{}), U32.add(run3(make3(1n, 3), make3(0n, 17), False{}), U32.add(run3(make3(0n, 3), make3(3n, 17), True{}), U32.add(run3(make3(0n, 3), make3(3n, 17), False{}), U32.add(run3(make3(0n, 3), make3(2n, 17), True{}), U32.add(run3(make3(0n, 3), make3(2n, 17), False{}), U32.add(run3(make3(0n, 3), make3(1n, 17), True{}), U32.add(run3(make3(0n, 3), make3(1n, 17), False{}), U32.add(run3(make3(0n, 3), make3(0n, 17), True{}), U32.add(run3(make3(0n, 3), make3(0n, 17), False{}), 0)))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))
