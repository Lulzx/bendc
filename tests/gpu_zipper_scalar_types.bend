import Base
type Mix is Data:
  Cell{x: U32, y: F32, z: Bool}
  Node{l: Mix, r: Mix}
def merge(a: Mix, b: Mix) -> Mix:
  match a b:
    case Cell{a,b,c} Cell{d,e,f}:
      Cell{U32.add(a,d), F32.add(b,e), c}
    case Cell{a,b,c} Node{d,e}:
      Cell{a,b,c}
    case Node{a,b} Cell{c,d,e}:
      Node{a,b}
    case Node{a,b} Node{c,d}:
      l r = merge(a,c) merge(b,d)
      Node{l,r}
def measure(x: Mix) -> U32:
  match x:
    case Cell{a,b,c}:
      U32.add(a,U32.from_nat(F32.to_nat(b)))
    case Node{a,b}:
      U32.add(measure(a),measure(b))
def run() -> U32:
  +a : Mix = Node{Cell{4294967295, 1.5, True{}},Cell{11,2.5,False{}}}
  +b : Mix = Node{Cell{2, 3.5, False{}},Cell{13,4.5,True{}}}
  measure(merge(a,b))
def main() -> IO(Unit):
  IO.print(U32.show(run!()))
