import Base

type Wide is Data:
  Atom{n: Nat}
  Split{l: Wide, r: Wide}
def wsum(t: Wide) -> U32:
  match t:
    case Atom{n}:
      U32.from_nat(n)
    case Split{a,b}:
      U32.add(wsum(a),wsum(b))

type Thin is Data:
  Input{}
  Value{n: U32}
  Sum{l: Thin,r: Thin}
def foldfp(t: Thin,+x: F32) -> U32:
  match t:
    case Input{}:
      F32.bits(x)
    case Value{n}:
      n
    case Sum{a,b}:
      U32.add(foldfp(a,x),foldfp(b,x))
def run() -> U32:
  +n = Nat.mul(65536n,65536n)
  +w : Wide = Split{Atom{n},Atom{11n}}
  +t : Thin = Sum{Input{},Value{3}}
  U32.add(wsum(w),foldfp(t,1.25))
def main() -> IO(Unit):
  IO.print(U32.show(run!()))
