import Base

def fill(n: Nat, m: Map<&2, U32>) -> Map<&2, U32>:
  match n:
    case 0n:
      m
    case 1n+ +p:
      +k = U32.from_nat(p)
      fill(p, Map.set(&2, U32, m, "k" ++ U32.show(k), (k * k : U32)))

def show_pair(p: Sigma<&2, &2, String, _ => U32>) -> String:
  (k, v) = p
  k ++ "=" ++ U32.show(v)

def main() -> IO(Unit):
  +m = fill(20n, Map.new(&2, U32))
  do IO<Unit>:
    IO.print(Nat.show(Map.size(&2, U32, m)))
    IO.print(U32.show(Pair.snd(Map<&2, U32>, U32, Map.get(U32, 0, m, "k7"))))
    IO.print(U32.show(Pair.snd(Map<&2, U32>, U32, Map.get(U32, 999, m, "zz"))))
    IO.print(String.join(List.sort(~String, ~String.is_le, Map.keys(&2, U32, m)), ","))
    IO.print(Bool.show(Pair.snd(Map<&2, U32>, Bool, Map.has(&2, U32, m, "k19"))))
