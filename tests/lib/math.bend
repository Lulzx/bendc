import Base
import ./util.bend as U

type Vec is Data:
  Vec{x: U32, y: U32}

def square(+x: U32) -> U32:
  (x * x : U32)

def norm2(v: Vec) -> U32:
  match v:
    case Vec{x, y}:
      (square(x) + square(y) : U32)

def show(v: Vec) -> String:
  match v:
    case Vec{x, y}:
      U.paren(U32.show(x) ++ ", " ++ U32.show(y))
