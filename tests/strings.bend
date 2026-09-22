import Base

def greet(name: String) -> String:
  "Hello, " ++ name ++ "!"

def count_a(s: String, acc: Nat) -> Nat:
  match s:
    case SNil{}:
      acc
    case SCon{c, t}:
      count_a(t, Nat.add(acc, U32.to_nat(Bool.to_u32(Char.is_eq(c, 'a')))))

def main() -> IO(Unit):
  +s = {"banana bread" : String}
  do IO<Unit>:
    IO.print(greet("Bend"))
    IO.print(String.to_upper(s))
    IO.print(Nat.show(count_a(s, 0n)))
    IO.print(String.join(String.split(s, ' '), "|"))
    IO.print(Bool.show(String.starts_with(s, "ban")))
    IO.print(Bool.show(String.eq(s, "banana")))
    IO.print(String.reverse("stressed"))
    IO.print(U32.show(Maybe.default(&2, U32, U32.read("1234"), 0)))
    IO.print("tab\there \"quoted\" back\\slash")
    IO.print(Nat.show(String.length("héllo wörld ✓")))
    IO.print("héllo wörld ✓")
