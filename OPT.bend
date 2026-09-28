import Base

# Laws for the optimizer's rewrites (bendc.bend, Opt), stated on Bend
# source and proven by induction; the official bend and bendc --check-only
# both check them. Each law is one rewrite on an instance the optimizer
# meets (bench/pipe.bend has each of these pipelines).

# Fusion
# ======

# A map of a map is one map, of the composed function.
law map_map:
  for ~A: Type
  for ~B: Type
  for ~C: Type
  for ~f: B -> C
  for ~g: A -> B
  for xs: List<A>
  {List.map(~B, ~C, ~f, List.map(~A, ~B, ~g, xs)) == List.map(~A, ~C, ~x => f(g(x)), xs) : List<C>}

def map_map(A, B, C, f, g, xs):
  match xs:
    case Nil{}:
      {==}
    case h <> t:
      %map_map(~A, ~B, ~C, ~f, ~g, t) : {List.map(~B, ~C, ~f, List.map(~A, ~B, ~g, h <> t)) == f(g(h)) <> _ : List<C>}
      {==}

# A right fold of a map folds the list itself.
law foldr_map:
  for ~A: Type
  for ~B: Type
  for ~C: Type
  for ~f: B -> C -> C
  for ~g: A -> B
  for xs: List<A>
  for z: C
  {List.foldr(~&1, ~B, ~C, ~f, List.map(~A, ~B, ~g, xs), z) == List.foldr(~&1, ~A, ~C, ~x => acc => f(g(x), acc), xs, z) : C}

def foldr_map(A, B, C, f, g, xs, z):
  match xs:
    case Nil{}:
      {==}
    case h <> t:
      %foldr_map(~A, ~B, ~C, ~f, ~g, t, z) : {List.foldr(~&1, ~B, ~C, ~f, List.map(~A, ~B, ~g, h <> t), z) == f(g(h), _) : C}
      {==}

# A left fold of a map folds the list itself.
law foldl_map:
  for ~A: Type
  for ~B: Type
  for ~C: Type
  for ~f: C -> B -> C
  for ~g: A -> B
  for xs: List<A>
  for z: C
  {List.foldl(~&1, ~B, ~C, ~f, List.map(~A, ~B, ~g, xs), z) == List.foldl(~&1, ~A, ~C, ~acc => x => f(acc, g(x)), xs, z) : C}

def foldl_map(A, B, C, f, g, xs, z):
  match xs:
    case Nil{}:
      {==}
    case h <> t:
      foldl_map(~A, ~B, ~C, ~f, ~g, t, f(z, g(h)))

# A map keeps the length.
law length_map:
  for ~A: Type
  for ~B: Type
  for ~f: A -> B
  for xs: List<A>
  {List.length(&1, B, List.map(~A, ~B, ~f, xs)) == List.length(&1, A, xs) : Nat}

def length_map(A, B, f, xs):
  match xs:
    case Nil{}:
      {==}
    case h <> t:
      %length_map(~A, ~B, ~f, t) : {List.length(&1, B, List.map(~A, ~B, ~f, h <> t)) == 1n+_ : Nat}
      {==}

# The fused def the optimizer makes of sum(double(xs), acc) (bench/pipe.bend):
# double's body with sum around each result, sum unfolded on the
# constructor, and sum(double(t), ..) made a call of the fused def.
def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      sum(t, (acc + x : U32))

def double(xs: List<U32>) -> List<U32>:
  match xs:
    case []:
      []
    case x <> t:
      (x * 2 : U32) <> double(t)

def sum_double(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case []:
      acc
    case x <> t:
      sum_double(t, (acc + (x * 2 : U32) : U32))

law fused:
  for xs: List<U32>
  for acc: U32
  {sum(double(xs), acc) == sum_double(xs, acc) : U32}

def fused(xs, acc):
  match xs:
    case []:
      {==}
    case x <> t:
      fused(t, (acc + (x * 2 : U32) : U32))

# Specialization
# ==============

# A copy of List.map for a known function (its self-calls drop it) is the
# map of that function.
def map3(xs: List<U32>) -> List<U32>:
  match xs:
    case []:
      []
    case x <> t:
      (x * 3 + 1 : U32) <> map3(t)

law specialized:
  for xs: List<U32>
  {map3(xs) == List.map(~U32, ~U32, ~x => (x * 3 + 1 : U32), xs) : List<U32>}

def specialized(xs):
  match xs:
    case []:
      {==}
    case x <> t:
      %specialized(t) : {map3(x <> t) == (x * 3 + 1 : U32) <> _ : List<U32>}
      {==}

# Simplification
# ==============

# Inlining Bool.not into a match on it, then case of case: the outer match
# goes into the inner one's cases, where it meets known constructors.
law case_of_case:
  for c: Bool
  for a: U32
  for b: U32
  {Bool.pick(U32, Bool.not(c), a, b) == Bool.pick(U32, c, b, a) : U32}

def case_of_case(c, a, b):
  match c:
    case True{}:
      {==}
    case False{}:
      {==}

def main() -> IO(Unit):
  IO.print(U32.show(sum_double([1, 2, 3], 0)))
