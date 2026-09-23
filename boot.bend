# The bootstrap's entry: bendc without its type checker, for building
# stage0 with the official bend (bootstrap.sh). Stage0 only has to
# translate bendc.bend to C (--no-check), and the official compiler's
# memory grows with the code main reaches, so leaving the checker out
# roughly halves it. Stage1 and stage2 are the full bendc.
import Base
import ./bendc.bend as B

def main() -> IO(Unit):
  do IO<Unit>:
    args : List<String> <- IO.args()
    B.Main.boot(B.IO.list2(args))
