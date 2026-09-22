import Base
import ./util/sq.bend as S

def area(+w: U32, +h: U32) -> U32:
  (S.twice(w) * h : U32)
