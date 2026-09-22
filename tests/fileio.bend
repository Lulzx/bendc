import Base

def show(r: File & Result<&1, &1, U32 & String, String>) -> IO(Unit):
  (f, res) = r
  do IO<Unit>:
    File.close(f)
    +text : String <- IO.pass(String, res)
    IO.write(text)
    IO.print(Nat.show(List.length(&2, String, String.lines(text))))

def done(r: File & Result<&1, &1, U32 & String, Unit>) -> IO(Unit):
  (f, res) = r
  do IO<Unit>:
    File.close(f)
    g : File <- IO.try(File, File.open("/tmp/bendc_test.txt", "r"))
    s : File & Result<&1, &1, U32 & String, String> <- File.read(g, 1000)
    show(s)

def main() -> IO(Unit):
  do IO<Unit>:
    f : File <- IO.try(File, File.open("/tmp/bendc_test.txt", "w"))
    r : File & Result<&1, &1, U32 & String, Unit> <- File.write(f, "line one\nline two\n")
    done(r)
