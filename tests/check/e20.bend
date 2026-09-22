import Base

def IsZero(n: Nat) -> Type:
  match n:
    case 0n:
      Unit
    case 1n+p:
      Empty

def main() -> IsZero(0n):
  Unit{}
