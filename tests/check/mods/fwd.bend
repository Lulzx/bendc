import Base

# A type that names a type declared below it.
type A is Data:
  A0{}
  A1{b: B}

type B is Data:
  B0{}
  B1{a: A}
