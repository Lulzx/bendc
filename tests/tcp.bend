import Base

# A TCP echo over loopback: the server and the client run concurrently.
def serve.got(l: Listener, r: Socket & Result<&1, &1, U32 & String, String>) -> IO(String):
  (s, res) = r
  do IO<String>:
    msg : String <- IO.pass(String, res)
    Socket.close(s)
    Listener.close(l)
    return msg

def serve.conn(r: Listener & Result<&1, &1, U32 & String, Socket>) -> IO(String):
  (l, res) = r
  do IO<String>:
    s : Socket <- IO.pass(Socket, res)
    got : Socket & Result<&1, &1, U32 & String, String> <- TCP.recv(s, 1024)
    serve.got(l, got)

def serve(port: U32) -> IO(String):
  do IO<String>:
    l : Listener <- IO.try(Listener, TCP.listen("127.0.0.1", port))
    r : Listener & Result<&1, &1, U32 & String, Socket> <- TCP.accept(l)
    serve.conn(r)

def client.sent(r: Socket & Result<&1, &1, U32 & String, Unit>) -> IO(Unit):
  (s, res) = r
  do IO<Unit>:
    u : Unit <- IO.pass(Unit, res)
    Socket.close(s)

# The socket, else what comes next.
def client.or(r: Result<&1, &1, U32 & String, Socket>, next: IO(Socket)) -> IO(Socket):
  match r:
    case Done{s}:
      IO.pure(Socket, s)
    case Fail{e}:
      next

# The server may not be listening yet (a loaded machine): try n more
# times, 20 ms apart.
def client.conn(+port: U32, n: Nat) -> IO(Socket):
  match n:
    case 0n:
      IO.try(Socket, TCP.connect("127.0.0.1", port))
    case 1n+p:
      do IO<Socket>:
        IO.sleep(20)
        r : Result<&1, &1, U32 & String, Socket> <- TCP.connect("127.0.0.1", port)
        client.or(r, client.conn(port, p))

def client(port: U32) -> IO(Unit):
  do IO<Unit>:
    IO.sleep(50)
    s : Socket <- client.conn(port, 250n)
    r : Socket & Result<&1, &1, U32 & String, Unit> <- TCP.send(s, "ping over tcp")
    client.sent(r)

def main() -> IO(Unit):
  do IO<Unit>:
    srv : Chan(String) <- IO.fork(String, serve(47831))
    cli : Chan(Unit) <- IO.fork(Unit, client(47831))
    msg : String <- IO.join(String, srv)
    u : Unit <- IO.join(Unit, cli)
    IO.print("server got: " ++ msg)
