import Base
import ./mods/fwd.bend as M

# A module's names resolve to its own even when declared further down.
def main() -> M.A:
  M.A1{M.B1{M.A0{}}}
