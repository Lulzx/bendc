import Base

type Tree<-A: Data> is Data:
  Leaf{}
  Node{l: Tree<A>, v: A, r: Tree<A>}

type Box is Data:
  Box{v: F32}

def main() -> List<&2, Tree<String>> & Maybe<&2, Box> & Nat & Char & String & Bool:
  ([Node{Leaf{}, "a\n\"b\"", Node{Leaf{}, "c", Leaf{}}}, Leaf{}], Some{Box{3.0}}, 42n, '\'',
    "tab\there", True{})
