import Base

type Term is Data:
  Input{}
  Value{n: U32}
  Sum{l: Term, r: Term}
  Difference{l: Term, r: Term}
  Product{l: Term, r: Term}
  Bits{l: Term, r: Term}

def fold(t: Term, +x: U32, +y: U32) -> U32:
  match t:
    case Input{}:
      U32.xor(x,y)
    case Value{n}:
      U32.add(n,3)
    case Sum{a,b}:
      U32.add(fold(a,x,y),fold(b,x,y))
    case Difference{a,b}:
      U32.sub(fold(a,x,y),fold(b,x,y))
    case Product{a,b}:
      U32.mul(fold(a,x,y),fold(b,x,y))
    case Bits{a,b}:
      U32.xor(fold(a,x,y),fold(b,x,y))

def count(t: Term) -> U32:
  match t:
    case Input{}:
      1
    case Value{n}:
      1
    case Sum{a,b}:
      U32.add(1,U32.add(count(a),count(b)))
    case Difference{a,b}:
      U32.add(1,U32.add(count(a),count(b)))
    case Product{a,b}:
      U32.add(1,U32.add(count(a),count(b)))
    case Bits{a,b}:
      U32.add(1,U32.add(count(a),count(b)))

def chain(d: Nat) -> Term:
  match d:
    case 0n:
      Input{}
    case 1n+ +p:
      Sum{chain(p),Value{U32.from_nat(p)}}

def alter(t: Term, +x: U32) -> U32:
  match t:
    case Input{}:
      x
    case Value{n}:
      n
    case Sum{a,b}:
      U32.add(alter(a,U32.inc(x)),alter(b,x))
    case Difference{a,b}:
      U32.sub(alter(a,x),alter(b,x))
    case Product{a,b}:
      U32.mul(alter(a,x),alter(b,x))
    case Bits{a,b}:
      U32.xor(alter(a,x),alter(b,x))

def duplicate(t: Term, +x: U32) -> U32:
  match t:
    case Input{}:
      x
    case Value{n}:
      n
    case Sum{+a,b}:
      U32.add(duplicate(a,x),duplicate(a,x))
    case Difference{a,b}:
      U32.sub(duplicate(a,x),duplicate(b,x))
    case Product{a,b}:
      U32.mul(duplicate(a,x),duplicate(b,x))
    case Bits{a,b}:
      U32.xor(duplicate(a,x),duplicate(b,x))

def main() -> IO(Unit):
  +a : Term = Bits{Input{},Value{4294967295}}
  +b : Term = Difference{Product{a,Value{11}},Sum{a,Value{2}}}
  IO.print(U32.show(fold!(b,9,17)))
