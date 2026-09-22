import Base

def lcg(n: Nat, seed: U32, acc: List<&2, U32>) -> List<&2, U32>:
  match n:
    case 0n:
      acc
    case 1n+p:
      +s = ((seed * 1103515245 : U32) + 12345 : U32)
      lcg(p, s, ((s >> 16n) % 1000 : U32) <> acc)

def is_sorted(xs: List<&2, U32>) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case x <> Nil{}:
      True{}
    case +x <> +y <> t:
      Bool.and(U32.is_le(x, y), is_sorted(y <> t))

def main() -> IO(Unit):
  +xs = lcg(2000n, 42, Nil{})
  +ys = List.sort(~U32, ~U32.is_le, xs)
  do IO<Unit>:
    IO.print(Bool.show(is_sorted(ys)))
    IO.print(List.show(~&2, ~U32, ~U32.show, List.take(&2, U32, ys, 10n)))
    IO.print(Nat.show(List.length(&2, U32, ys)))
    IO.print(U32.show(List.foldl(~&2, ~U32, ~U32, ~U32.add, ys, 0)))
