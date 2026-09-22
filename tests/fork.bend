import Base

def greet(name: String) -> IO(String):
  do IO<String>:
    IO.sleep(10)
    return "Hello, " ++ name

def main() -> IO(Unit):
  do IO<Unit>:
    chan : Chan(String) <- IO.fork(String, greet("Bend"))
    IO.print("Waiting...")
    text : String <- IO.join(String, chan)
    IO.print(text)
