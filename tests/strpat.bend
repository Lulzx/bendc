import Base

def cmd(args: List<&2, String>) -> String:
  match args:
    case "--help" <> Nil{}:
      "help"
    case "run" <> file <> Nil{}:
      "running " ++ file
    case "" <> rest:
      "empty"
    case other:
      "unknown"

def main() -> IO(Unit):
  do IO<Unit>:
    IO.print(cmd(["--help"]))
    IO.print(cmd(["run", "x.bend"]))
    IO.print(cmd(["", "y"]))
    IO.print(cmd(["run"]))
