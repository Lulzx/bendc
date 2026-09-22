import Base

# User-defined effects, written against the official effect ABI.
def Clock.now() -> IO(U32):
  import "./lib/clock.c"
  import "./lib/clock.js"

def shout(text: String) -> IO(Result<&1, &1, U32 & String, String>):
  import "./lib/shout.c"
  import "./lib/shout.js"

def worker(name: String, ms: U32) -> IO(String):
  do IO<String>:
    IO.sleep(ms)
    return name

def main() -> IO(Unit):
  do IO<Unit>:
    t0 : U32 <- Clock.now()
    loud : String <- IO.try(String, shout("hello, effects"))
    IO.print(loud)
    a : Chan(String) <- IO.fork(String, worker("slow", 200))
    b : Chan(String) <- IO.fork(String, worker("fast", 50))
    x : String <- IO.join(String, b)
    y : String <- IO.join(String, a)
    t1 : U32 <- Clock.now()
    IO.print(x ++ " then " ++ y)
    IO.print(Bool.show(U32.is_lt((t1 - t0 : U32), 240)))
