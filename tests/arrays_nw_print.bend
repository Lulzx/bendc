import Base
# A narrow array (32-bit cells, see ARR_NW in rt/bendrt.h) as the result.

def fill(+j: Nat, g: Array<U32>) -> Array<U32>:
  match j:
    case 0n:
      g
    case 1n+p:
      +c = U32.from_nat(p)
      fill(p, g[c] <- U32.mul(c, 4000000000))

def main() -> Array<U32>:
  fill(8n, [0 : U32*8n])
