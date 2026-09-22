# bendc: a Bend compiler written in Bend.
# Compiles a Bend program (plus the parts of Base it uses) to C.
# Usage: bendc <base.bend> <input.bend>  (C goes to stdout)

import Base
import ./check.bend as Chk
import ./rt/rtjs.bend as RtJs
import ./rt/gpuh.bend as GpuH

# Utilities
# =========

def Str.eq(+a: String, +b: String) -> Bool:
  String.eq(a, b)

def Str.chr(c: U32) -> String:
  SCon{Chr{c}, SNil{}}

def Str.rev(s: String) -> String:
  String.reverse(s)

# Rope for linear-time output building.
type Doc is Data:
  DNil{}
  DStr{s: String}
  DCat{a: Doc, b: Doc}

@unsafe
def Doc.go(d: Doc, acc: String) -> String:
  match d:
    case DNil{}:
      acc
    case DStr{s}:
      String.append(s, acc)
    case DCat{a, b}:
      Doc.go(a, Doc.go(b, acc))

def Doc.flat(d: Doc) -> String:
  Doc.go(d, SNil{})

def Doc.list(xs: List<&2, Doc>) -> Doc:
  match xs:
    case Nil{}:
      DNil{}
    case h <> t:
      DCat{h, Doc.list(t)}

def Doc.sep.go(xs: List<&2, Doc>, +sep: String) -> Doc:
  match xs:
    case Nil{}:
      DNil{}
    case h <> t:
      DCat{DStr{sep}, DCat{h, Doc.sep.go(t, sep)}}

def Doc.sep(xs: List<&2, Doc>, +sep: String) -> Doc:
  match xs:
    case Nil{}:
      DNil{}
    case h <> t:
      DCat{h, Doc.sep.go(t, sep)}

def Str.has(xs: List<&2, String>, +x: String) -> Bool:
  List.contains(~String, ~String.eq, xs, x)

def Str.split_tab.cons(+c: U32, r: String & String) -> String & String:
  (a, b) = r
  (SCon{Chr{c}, a}, b)

law Str.split_tab:
  for s: String
  String & String

@unsafe
def Str.split_tab.if(+c: U32, t: String, tab: Bool) -> String & String:
  match tab:
    case True{}:
      ("", t)
    case False{}:
      Str.split_tab.cons(c, Str.split_tab(t))

@unsafe
def Str.split_tab(s):
  match s:
    case SNil{}:
      ("", "")
    case SCon{Chr{+c}, t}:
      Str.split_tab.if(c, t, U32.is_eq(c, 9))

def Str.codes32(s: String) -> List<&2, U32>:
  match s:
    case SNil{}:
      Nil{}
    case SCon{Chr{x}, t}:
      x <> Str.codes32(t)

# Lexer
# =====

type TK is Data:
  KId{s: String}
  KNat{n: U32}
  KNatPlus{n: U32}
  KNum{n: U32}
  KFlt{s: String}
  KChr{n: U32}
  KStr{s: String}
  KSym{s: String}
  KNL{}
  KIn{}
  KDe{}
  KEof{}
  KErr{s: String}

type Tok is Data:
  Tok{k: TK, sp: Bool, line: U32}

def Toks() -> Data:
  List<&2, Tok>

def Lex.is_idc(+c: Char) -> Bool:
  +x = Char.to_u32(c)
  Bool.or(Char.is_alpha(c), Bool.or(Char.is_digit(c),
    Bool.or(U32.is_eq(x, 95), U32.is_eq(x, 46))))

def Lex.is_ids(+c: Char) -> Bool:
  Bool.or(Char.is_alpha(c), U32.is_eq(Char.to_u32(c), 95))

# Spans a run of identifier chars; returns (reversed-acc result, rest).
law Lex.id:
  for s: String
  for acc: String
  String & String

@unsafe
def Lex.id.if(c: Char, t: String, acc: String, b: Bool) -> String & String:
  match b:
    case True{}:
      Lex.id(t, SCon{c, acc})
    case False{}:
      (Str.rev(acc), SCon{c, t})

@unsafe
def Lex.id(s, acc):
  match s:
    case SNil{}:
      (Str.rev(acc), SNil{})
    case SCon{+c, t}:
      Lex.id.if(c, t, acc, Lex.is_idc(c))

# Spans digits, accumulating a U32 value.
law Lex.digits:
  for s: String
  for acc: U32
  U32 & String

@unsafe
def Lex.digits.if(c: Char, t: String, +acc: U32, b: Bool) -> U32 & String:
  match b:
    case True{}:
      Lex.digits(t, ((acc * 10 : U32) + (Char.to_u32(c) - 48 : U32) : U32))
    case False{}:
      (acc, SCon{c, t})

@unsafe
def Lex.digits(s, acc):
  match s:
    case SNil{}:
      (acc, SNil{})
    case SCon{+c, t}:
      Lex.digits.if(c, t, acc, Char.is_digit(c))

# Spans digit chars as text (for float fractions).
law Lex.dtext:
  for s: String
  for acc: String
  String & String

@unsafe
def Lex.dtext.if(c: Char, t: String, acc: String, b: Bool) -> String & String:
  match b:
    case True{}:
      Lex.dtext(t, SCon{c, acc})
    case False{}:
      (Str.rev(acc), SCon{c, t})

@unsafe
def Lex.dtext(s, acc):
  match s:
    case SNil{}:
      (Str.rev(acc), SNil{})
    case SCon{+c, t}:
      Lex.dtext.if(c, t, acc, Char.is_digit(c))

# Escape char after a backslash.
def Lex.esc(x: U32) -> U32:
  +y = x
  Bool.pick(U32, U32.is_eq(y, 110), 10,
    Bool.pick(U32, U32.is_eq(y, 116), 9,
      Bool.pick(U32, U32.is_eq(y, 114), 13,
        Bool.pick(U32, U32.is_eq(y, 48), 0, y))))

def Lex.lit_char.esc(t: String) -> U32 & String:
  match t:
    case SNil{}:
      (92, SNil{})
    case SCon{Chr{y}, t2}:
      (Lex.esc(y), t2)

def Lex.lit_char.if(+x: U32, t: String, esc: Bool) -> U32 & String:
  match esc:
    case False{}:
      (x, t)
    case True{}:
      Lex.lit_char.esc(t)

# One (possibly escaped) char of a literal: (code, rest).
def Lex.lit_char(s: String) -> U32 & String:
  match s:
    case SNil{}:
      (0, SNil{})
    case SCon{Chr{+x}, t}:
      Lex.lit_char.if(x, t, U32.is_eq(x, 92))

# String literal body: (text, rest after closing quote).
law Lex.str:
  for s: String
  for acc: String
  String & String

@unsafe
def Lex.str.next(acc: String, r: U32 & String) -> String & String:
  (c, t) = r
  Lex.str(t, SCon{Chr{c}, acc})

@unsafe
def Lex.str.if(x: U32, t: String, acc: String, q: Bool) -> String & String:
  match q:
    case True{}:
      (Str.rev(acc), t)
    case False{}:
      Lex.str.next(acc, Lex.lit_char(SCon{Chr{x}, t}))

@unsafe
def Lex.str(s, acc):
  match s:
    case SNil{}:
      (Str.rev(acc), SNil{})
    case SCon{Chr{+x}, t}:
      Lex.str.if(x, t, acc, U32.is_eq(x, 34))

def Lex.drop1(s: String) -> String:
  match s:
    case SNil{}:
      SNil{}
    case SCon{h, t}:
      t

# Operators, longest first.
def Lex.ops3() -> List<&2, String>:
  [".&.", ".|.", ".^.", "<&>"]

def Lex.ops2() -> List<&2, String>:
  ["=>", "->", "<-", "<>", "<=", ">=", "==", "!=", "++", "&&", "||", ">>", "<<"]

def Lex.op_of.two(m: Maybe<&2, String>, s: String) -> String:
  match m:
    case Some{o}:
      o
    case None{}:
      String.take(s, 1n)

# Lexes one line. acc is reversed.
law Lex.line:
  for s: String
  for sp: Bool
  for +ln: U32
  for acc: Toks()
  Toks()

def Lex.class(+x: U32) -> Nat:
  # 0 space, 1 comment, 2 ident, 3 digit, 4 char, 5 string, 6 op
  Bool.pick(Nat, Bool.or(U32.is_eq(x, 32), U32.is_eq(x, 9)), 0n,
  Bool.pick(Nat, U32.is_eq(x, 35), 1n,
  Bool.pick(Nat, Lex.is_ids(Chr{x}), 2n,
  Bool.pick(Nat, Char.is_digit(Chr{x}), 3n,
  Bool.pick(Nat, U32.is_eq(x, 39), 4n,
  Bool.pick(Nat, U32.is_eq(x, 34), 5n,
  Bool.pick(Nat, U32.is_eq(x, 13), 0n, 6n)))))))

@unsafe
def Lex.line.id(sp: Bool, +ln: U32, acc: Toks(), r: String & String) -> Toks():
  (name, rest) = r
  Lex.line(rest, False{}, ln, Tok{KId{name}, sp, ln} <> acc)

@unsafe
def Lex.line.chr(sp: Bool, +ln: U32, acc: Toks(), r: U32 & String) -> Toks():
  (c, rest) = r
  Lex.line(Lex.drop1(rest), False{}, ln, Tok{KChr{c}, sp, ln} <> acc)

@unsafe
def Lex.line.str(sp: Bool, +ln: U32, acc: Toks(), r: String & String) -> Toks():
  (s, rest) = r
  Lex.line(rest, False{}, ln, Tok{KStr{s}, sp, ln} <> acc)

@unsafe
def Lex.line.op(s: String, sp: Bool, +ln: U32, acc: Toks(), +op: String) ->
  Toks():
  Lex.line(String.drop(s, String.length(op)), False{}, ln,
    Tok{KSym{op}, sp, ln} <> acc)

@unsafe
def Lex.line.nat.if(
  sp: Bool, +ln: U32, acc: Toks(), +v: U32, x: U32, t: String, plus: Bool
) -> Toks():
  match plus:
    case True{}:
      Lex.line(t, False{}, ln, Tok{KNatPlus{v}, sp, ln} <> acc)
    case False{}:
      Lex.line(SCon{Chr{x}, t}, False{}, ln, Tok{KNat{v}, sp, ln} <> acc)

@unsafe
def Lex.line.nat(sp: Bool, +ln: U32, acc: Toks(), +v: U32, t: String) -> Toks():
  match t:
    case SNil{}:
      Lex.line(SNil{}, False{}, ln, Tok{KNat{v}, sp, ln} <> acc)
    case SCon{Chr{+x}, t2}:
      Lex.line.nat.if(sp, ln, acc, v, x, t2, U32.is_eq(x, 43))

@unsafe
def Lex.line.flt(sp: Bool, +ln: U32, acc: Toks(), +v: U32, r: String & String) ->
  Toks():
  (frac, rest) = r
  Lex.line(rest, False{}, ln,
    Tok{KFlt{U32.show(v) ++ "." ++ frac}, sp, ln} <> acc)

@unsafe
def Lex.line.num.if(
  sp: Bool, +ln: U32, acc: Toks(), +v: U32, x: U32, t: String, k: Nat
) -> Toks():
  match k:
    case 0n:
      Lex.line(SCon{Chr{x}, t}, False{}, ln, Tok{KNum{v}, sp, ln} <> acc)
    case 1n:
      Lex.line.nat(sp, ln, acc, v, t)
    case 2n+p:
      Lex.line.flt(sp, ln, acc, v, Lex.dtext(t, SNil{}))

@unsafe
def Lex.line.num.go(sp: Bool, +ln: U32, acc: Toks(), +v: U32, rest: String) ->
  Toks():
  match rest:
    case SNil{}:
      Lex.line(SNil{}, False{}, ln, Tok{KNum{v}, sp, ln} <> acc)
    case SCon{Chr{+x}, t}:
      Lex.line.num.if(sp, ln, acc, v, x, t,
        Bool.pick(Nat, U32.is_eq(x, 110), 1n,
          Bool.pick(Nat, U32.is_eq(x, 46), 2n, 0n)))

# After digits: Nat literal (n / n+), float (.digits) or U32.
@unsafe
def Lex.line.num(sp: Bool, +ln: U32, acc: Toks(), r: U32 & String) -> Toks():
  (v, rest) = r
  Lex.line.num.go(sp, ln, acc, v, rest)

# A lexed line: indentation, line number, tokens.
type Line is Data:
  Line{ind: U32, ln: U32, toks: List<&2, Tok>}

def Lex.lines.put(l: Line, rest: List<&2, Line>) -> List<&2, Line>:
  match l:
    case Line{i, n, Nil{}}:
      rest
    case Line{i, n, h <> t}:
      Line{i, n, h <> t} <> rest

law Lex.find_op:
  for ops: List<&2, String>
  for +s: String
  Maybe<&2, String>

@unsafe
def Lex.find_op.if(h: String, t: List<&2, String>, +s: String, b: Bool) ->
  Maybe<&2, String>:
  match b:
    case True{}:
      Some{h}
    case False{}:
      Lex.find_op(t, s)

def Lex.find_op(ops, s):
  match ops:
    case Nil{}:
      None{}
    case +h <> t:
      Lex.find_op.if(h, t, s, String.starts_with(s, h))

def Lex.op_of.go(m: Maybe<&2, String>, +s: String) -> String:
  match m:
    case Some{o}:
      o
    case None{}:
      Lex.op_of.two(Lex.find_op(Lex.ops2(), s), s)

def Lex.op_of(+s: String) -> String:
  Lex.op_of.go(Lex.find_op(Lex.ops3(), s), s)

@unsafe
def Lex.line.go(x: U32, t: String, sp: Bool, +ln: U32, acc: Toks(), cls: Nat) ->
  Toks():
  match cls:
    case 0n:
      Lex.line(t, True{}, ln, acc)
    case 1n:
      acc
    case 2n:
      Lex.line.id(sp, ln, acc, Lex.id(SCon{Chr{x}, t}, SNil{}))
    case 3n:
      Lex.line.num(sp, ln, acc, Lex.digits(SCon{Chr{x}, t}, 0))
    case 4n:
      Lex.line.chr(sp, ln, acc, Lex.lit_char(t))
    case 5n:
      Lex.line.str(sp, ln, acc, Lex.str(t, SNil{}))
    case 6n+p:
      +s = {SCon{Chr{x}, t} : String}
      Lex.line.op(s, sp, ln, acc, Lex.op_of(s))

@unsafe
def Lex.line(s, sp, ln, acc):
  match s:
    case SNil{}:
      acc
    case SCon{Chr{+x}, t}:
      Lex.line.go(x, t, sp, ln, acc, Lex.class(x))

law Lex.indent:
  for s: String
  U32

@unsafe
def Lex.indent.if(t: String, b: Bool) -> U32:
  match b:
    case True{}:
      U32.inc(Lex.indent(t))
    case False{}:
      0

# Leading indentation width.
def Lex.indent(s):
  match s:
    case SNil{}:
      0
    case SCon{Chr{+x}, t}:
      Lex.indent.if(t, U32.is_eq(x, 32))

def Lex.lines.go(ls: List<&2, String>, +ln: U32) -> List<&2, Line>:
  match ls:
    case Nil{}:
      Nil{}
    case +l <> t:
      Lex.lines.put(Line{Lex.indent(l), ln,
        List.reverse(&2, Tok, Lex.line(l, True{}, ln, Nil{}))},
        Lex.lines.go(t, U32.inc(ln)))

def Lex.lines(src: String) -> List<&2, Line>:
  Lex.lines.go(String.lines(src), 1)

# Turns lines into a token stream with KNL / KIn / KDe. Newlines inside
# brackets are ignored; a deeper line opens a block only after a ':'.
type LS is Data:
  LS{acc: List<&2, Tok>, depth: U32, colon: Bool, stack: List<&2, U32>, op: Bool}

def Lay.is_sym(+k: TK, +s: String) -> Bool:
  match k:
    case KSym{x}:
      Str.eq(x, s)
    case other:
      False{}

def Lay.delta(+k: TK) -> U32:
  Bool.pick(U32, Bool.or(Lay.is_sym(k, "("), Bool.or(Lay.is_sym(k, "["),
    Lay.is_sym(k, "{"))), 1,
    Bool.pick(U32, Bool.or(Lay.is_sym(k, ")"), Bool.or(Lay.is_sym(k, "]"),
      Lay.is_sym(k, "}"))), 4294967295, 0))

def Lay.is_op(+k: TK) -> Bool:
  match k:
    case KSym{+x}:
      List.contains(~String, ~String.eq, ["->", "=>", "&", "|", "++", "<>", "&&",
        "||", "+", "*", ",", "=", "<-"], x)
    case other:
      False{}

def Lay.toks(ts: List<&2, Tok>, st: LS) -> LS:
  match ts:
    case Nil{}:
      st
    case Tok{+k, sp, ln} <> t:
      LS{acc, depth, colon, stack, op} = st
      +d = (depth + Lay.delta(k) : U32)
      Lay.toks(t, LS{Tok{k, sp, ln} <> acc, d,
        Bool.and(Lay.is_sym(k, ":"), U32.is_zero(d)), stack, Lay.is_op(k)})

def Lay.top(+stack: List<&2, U32>) -> U32:
  match stack:
    case Nil{}:
      0
    case h <> t:
      h

def Lay.tok(k: TK, +ln: U32) -> Tok:
  Tok{k, True{}, ln}

def Lay.dedent(depth: U32, colon: Bool, +ln: U32, r: List<&2, U32> & List<&2, Tok>) ->
  LS:
  (stack, acc) = r
  LS{acc, depth, colon, stack, False{}}

def Lay.start.gt(
  acc: List<&2, Tok>, depth: U32, colon: Bool, stack: List<&2, U32>, +ind: U32,
  +ln: U32, open: Bool
) -> LS:
  match open:
    case True{}:
      LS{Lay.tok(KIn{}, ln) <> acc, depth, colon, ind <> stack, False{}}
    case False{}:
      LS{acc, depth, colon, stack, False{}}

law Lay.pop:
  for stack: List<&2, U32>
  for +ind: U32
  for acc: List<&2, Tok>
  for +ln: U32
  List<&2, U32> & List<&2, Tok>

@unsafe
def Lay.start.go(
  acc: List<&2, Tok>, depth: U32, +colon: Bool, stack: List<&2, U32>, +ind: U32,
  +ln: U32, c: Cmp
) -> LS:
  match c:
    case GT{}:
      Lay.start.gt(acc, depth, colon, stack, ind, ln, colon)
    case EQ{}:
      LS{Lay.tok(KNL{}, ln) <> acc, depth, colon, stack, False{}}
    case LT{}:
      Lay.dedent(depth, colon, ln, Lay.pop(stack, ind, Lay.tok(KNL{}, ln) <> acc, ln))

def Lay.start.op(
  acc: List<&2, Tok>, depth: U32, colon: Bool, stack: List<&2, U32>, +ind: U32,
  +ln: U32, c: Cmp, op: Bool
) -> LS:
  match op:
    case True{}:
      LS{acc, depth, colon, stack, False{}}
    case False{}:
      Lay.start.go(acc, depth, colon, stack, ind, ln, c)

# Handles the start of a line at bracket depth 0.
def Lay.start(st: LS, +ind: U32, +ln: U32) -> LS:
  LS{acc, depth, colon, +stack, op} = st
  +top = Lay.top(stack)
  Lay.start.op(acc, depth, colon, stack, ind, ln, U32.cmp(ind, top), op)

def Lay.line.go(+ind: U32, +ln: U32, toks: List<&2, Tok>, st: LS, top: Bool) -> LS:
  match top:
    case True{}:
      Lay.toks(toks, Lay.start(st, ind, ln))
    case False{}:
      Lay.toks(toks, st)

def Lay.line(l: Line, st: LS) -> LS:
  Line{+ind, +ln, toks} = l
  LS{acc, +depth, colon, stack, op} = st
  Lay.line.go(ind, ln, toks, LS{acc, depth, colon, stack, op}, U32.is_zero(depth))

def Lay.lines(ls: List<&2, Line>, st: LS) -> LS:
  match ls:
    case Nil{}:
      st
    case l <> t:
      Lay.lines(t, Lay.line(l, st))

def Lay.finish.go(r: List<&2, U32> & List<&2, Tok>) -> List<&2, Tok>:
  (stack2, acc2) = r
  List.reverse(&2, Tok, Lay.tok(KEof{}, 0) <> acc2)

@unsafe
def Lay.finish(st: LS) -> List<&2, Tok>:
  LS{acc, depth, colon, stack, op} = st
  Lay.finish.go(Lay.pop(stack, 0, Lay.tok(KNL{}, 0) <> acc, 0))

def Lex.all(src: String) -> List<&2, Tok>:
  Lay.finish(Lay.lines(Lex.lines(src), LS{Nil{}, 0, False{}, [0], False{}}))

# Layout
# ======

def TK.show(k: TK) -> String:
  match k:
    case KId{s}:
      s
    case KNat{n}:
      U32.show(n) ++ "n"
    case KNatPlus{n}:
      U32.show(n) ++ "n+"
    case KNum{n}:
      U32.show(n)
    case KFlt{s}:
      s
    case KChr{n}:
      "'" ++ U32.show(n) ++ "'"
    case KStr{s}:
      "\"" ++ s ++ "\""
    case KSym{s}:
      s
    case KNL{}:
      "<NL>\n"
    case KIn{}:
      "<IN>"
    case KDe{}:
      "<DE>"
    case KEof{}:
      "<EOF>"
    case KErr{s}:
      "<ERR " ++ s ++ ">"

def Tok.show(t: Tok) -> String:
  Tok{k, sp, ln} = t
  Bool.pick(String, sp, " ", "") ++ TK.show(k)

def Toks.show(ts: List<&2, Tok>) -> String:
  match ts:
    case Nil{}:
      ""
    case h <> t:
      Tok.show(h) ++ Toks.show(t)

@unsafe
def Lay.pop.if(
  h: U32, t: List<&2, U32>, +ind: U32, acc: List<&2, Tok>, +ln: U32, gt: Bool
) -> List<&2, U32> & List<&2, Tok>:
  match gt:
    case True{}:
      Lay.pop(t, ind, Lay.tok(KDe{}, ln) <> acc, ln)
    case False{}:
      (h <> t, acc)

# Pops levels deeper than ind, emitting KDe for each.
@unsafe
def Lay.pop(stack, ind, acc, ln):
  match stack:
    case Nil{}:
      (Nil{}, acc)
    case +h <> t:
      Lay.pop.if(h, t, ind, acc, ln, U32.is_gt(h, ind))

# IO helpers
# ==========

def IO.read_fin(r: File & Result<&1, &1, U32 & String, String>) -> IO(String):
  (f2, res) = r
  do IO<String>:
    File.close(f2)
    IO.pass(String, res)

def IO.read_sized(r: File & Result<&1, &1, U32 & String, U32>) -> IO(File & Result<&1, &1, U32 & String, String>):
  (f, res) = r
  match res:
    case Done{n}:
      File.read(f, U32.inc(n))
    case Fail{e}:
      File.read(f, 2000000000)

# Reads with the file's size (the read effect allocates as much as asked).
def IO.read_all(f: File) -> IO(File & Result<&1, &1, U32 & String, String>):
  do IO<File & Result<&1, &1, U32 & String, String>>:
    sz : File & Result<&1, &1, U32 & String, U32> <- File.size(f)
    IO.read_sized(sz)

def IO.read_file(path: String) -> IO(String):
  do IO<String>:
    f : File <- IO.try(File, File.open(path, "r"))
    r : File & Result<&1, &1, U32 & String, String> <- IO.read_all(f)
    IO.read_fin(r)

def IO.list2(xs: List<String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> t:
      h <> IO.list2(t)

def IO.write_err(+s: String) -> IO(Unit):
  IO.print_err(String.take(s, Nat.sub(String.length(s), 1n)))

# AST
# ===

type Pat is Data:
  PVar{name: String}
  PCtor{name: String, args: List<&2, Pat>}
  PNat{n: U32}
  PSucc{k: U32, p: Pat}
  PNum{n: U32}

type Expr is Data:
  EVar{name: String}
  ENum{n: U32}
  ENat{n: U32}
  EFlt{s: String}
  EStr{s: String}
  ECall{f: Expr, args: List<&2, Expr>}
  ECtor{name: String, args: List<&2, Expr>}
  ELam{pat: Pat, body: Expr}
  ELet{pat: Pat, val: Expr, body: Expr}
  EMatch{scrs: List<&2, Expr>, cases: List<&2, Expr>}
  ECase{pats: List<&2, Pat>, body: Expr}
  ESucc{k: U32, e: Expr}
  EOp{op: String, a: Expr, b: Expr}
  EAnn{e: Expr, ty: String}
  ETy{name: String, args: List<&2, Expr>}
  EErr{msg: String}

type Stmt is Data:
  SLet{pat: Pat, val: Expr}
  SBind{name: String, val: Expr}
  SRet{e: Expr}
  SExp{e: Expr}
  SSkip{}

# mode: 0 plain, 1 erased (-), 2 shared (+), 3 template (~), 4 bare
type Param is Data:
  Param{name: String, mode: U32, ty: String}

type Field is Data:
  Field{name: String, ty: Expr}

type Ctor is Data:
  Ctor{name: String, fields: List<&2, Field>}

type Decl is Data:
  DDef{name: String, params: List<&2, Param>, body: Expr, ret: Expr}
  DEff{name: String, params: List<&2, Param>, imports: List<&2, String>}
  DLaw{name: String, params: List<&2, Param>}
  DType{name: String, params: List<&2, String>, ctors: List<&2, Ctor>}
  DImport{path: String, alias: String}

# Parser monad
# ============

def Parser(-A: Type) -> Type:
  Toks() -> A & Toks()

def Parser.go(-A: Type, -B: Type, r: A & Toks(), f: A -> Parser(B)) ->
  B & Toks():
  (a, ts) = r
  f(a, ts)

def Parser.bind(-A: Type, -B: Type, m: Parser(A), f: A -> Parser(B)) ->
  Parser(B):
  ts => Parser.go(A, B, m(ts), f)

def Parser.pure(-A: Type, x: A) -> Parser(A):
  ts => (x, ts)

def P.eof_tok() -> Tok:
  Tok{KEof{}, True{}, 0}

def P.peek.go(ts: Toks()) -> Tok & Toks():
  match ts:
    case Nil{}:
      (P.eof_tok(), Nil{})
    case +h <> t:
      (h, h <> t)

# Head token (not consumed).
def P.peek() -> Parser(Tok):
  ts => P.peek.go(ts)

def P.stuck(+k: TK) -> Bool:
  match k:
    case KErr{s}:
      True{}
    case KEof{}:
      True{}
    case other:
      False{}

def P.skip.if(h: Tok, t: Toks(), stuck: Bool) -> Unit & Toks():
  match stuck:
    case True{}:
      (Unit{}, h <> t)
    case False{}:
      (Unit{}, t)

def P.skip.go(ts: Toks()) -> Unit & Toks():
  match ts:
    case Nil{}:
      (Unit{}, Nil{})
    case Tok{+k, sp, ln} <> t:
      P.skip.if(Tok{k, sp, ln}, t, P.stuck(k))

# Drops the head token (never drops an error or EOF).
def P.skip() -> Parser(Unit):
  ts => P.skip.go(ts)

def P.err.go(+msg: String, ts: Toks()) -> Unit & Toks():
  match ts:
    case Tok{KErr{s}, sp, ln} <> t:
      (Unit{}, [Tok{KErr{s}, sp, ln}])
    case Tok{k, sp, +ln} <> t:
      (Unit{}, [Tok{KErr{"line " ++ U32.show(ln) ++ ": " ++ msg ++
        " (got '" ++ TK.show(k) ++ "')"}, sp, ln}])
    case Nil{}:
      (Unit{}, [Tok{KErr{msg ++ " (at end)"}, True{}, 0}])

# Replaces the stream by an error (keeps the first error).
def P.err(msg: String) -> Parser(Unit):
  ts => P.err.go(msg, ts)

def P.expect.if(+s: String, b: Bool) -> Parser(Unit):
  match b:
    case True{}:
      P.skip()
    case False{}:
      P.err("expected '" ++ s ++ "'")

def P.tok_is(+t: Tok, +s: String) -> Bool:
  match t:
    case Tok{KSym{x}, sp, ln}:
      Str.eq(x, s)
    case other:
      False{}

def P.expect(+s: String) -> Parser(Unit):
  do Parser<Unit>:
    t : Tok <- P.peek()
    P.expect.if(s, P.tok_is(t, s))

def P.eat.if(b: Bool) -> Parser(Bool):
  match b:
    case True{}:
      do Parser<Bool>:
        P.skip()
        return True{}
    case False{}:
      Parser.pure(Bool, False{})

# Consumes the symbol if present.
def P.eat(+s: String) -> Parser(Bool):
  do Parser<Bool>:
    t : Tok <- P.peek()
    P.eat.if(P.tok_is(t, s))

def P.ident.k(k: TK) -> Parser(String):
  match k:
    case KId{s}:
      do Parser<String>:
        P.skip()
        return s
    case other:
      do Parser<String>:
        P.err("expected an identifier")
        return ""

def P.tok_kind(t: Tok) -> TK:
  Tok{k, sp, ln} = t
  k

def P.ident() -> Parser(String):
  do Parser<String>:
    t : Tok <- P.peek()
    P.ident.k(P.tok_kind(t))

def P.is_nl(t: Tok) -> Bool:
  match t:
    case Tok{KNL{}, sp, ln}:
      True{}
    case other:
      False{}

# Type head name of a type expression.
def P.head(e: Expr) -> String:
  match e:
    case EVar{n}:
      n
    case ECall{EVar{n}, args}:
      n
    case ETy{n, targs}:
      n
    case other:
      ""

def P.tuple(xs: List<&2, Expr>) -> Expr:
  match xs:
    case Nil{}:
      ECtor{"Unit", Nil{}}
    case h <> Nil{}:
      h
    case h <> t:
      ECtor{"Tuple", [h, P.tuple(t)]}

def P.ptuple(xs: List<&2, Pat>) -> Pat:
  match xs:
    case Nil{}:
      PCtor{"Unit", Nil{}}
    case h <> Nil{}:
      h
    case h <> t:
      PCtor{"Tuple", [h, P.ptuple(t)]}

def P.elist(xs: List<&2, Expr>) -> Expr:
  match xs:
    case Nil{}:
      ECtor{"Nil", Nil{}}
    case h <> t:
      ECtor{"Con", [h, P.elist(t)]}

def P.plist(xs: List<&2, Pat>) -> Pat:
  match xs:
    case Nil{}:
      PCtor{"Nil", Nil{}}
    case h <> t:
      PCtor{"Con", [h, P.plist(t)]}

law P.nls:
  Parser(Unit)

@unsafe
def P.nls.if(b: Bool) -> Parser(Unit):
  match b:
    case True{}:
      do Parser<Unit>:
        P.skip()
        P.nls()
    case False{}:
      Parser.pure(Unit, Unit{})

# Skips newlines.
@unsafe
def P.nls():
  do Parser<Unit>:
    t : Tok <- P.peek()
    P.nls.if(P.is_nl(t))

law P.which:
  for +s: String
  for xs: List<&2, String>
  Nat

@unsafe
def P.which.if(+s: String, t: List<&2, String>, hit: Bool) -> Nat:
  match hit:
    case True{}:
      0n
    case False{}:
      1n+P.which(s, t)

# Index of s in xs (or length when absent).
@unsafe
def P.which(s, xs):
  match xs:
    case Nil{}:
      0n
    case h <> t:
      P.which.if(s, t, String.eq(s, h))

# Symbol index of a token (or 99 when not a symbol).
def P.tok_which(t: Tok, xs: List<&2, String>) -> Nat:
  match t:
    case Tok{KSym{s}, sp, ln}:
      P.which(s, xs)
    case other:
      99n

# Expressions
# ===========

type OpInfo is Data:
  OpInfo{op: String, prec: U32, right: Bool}

def P.ops() -> List<&2, OpInfo>:
  [OpInfo{"->", 1, True{}}, OpInfo{"|", 2, True{}}, OpInfo{"&", 3, True{}},
   OpInfo{"<&>", 3, True{}}, OpInfo{"||", 4, False{}},
   OpInfo{"&&", 5, False{}}, OpInfo{"<>", 6, True{}}, OpInfo{"++", 6, True{}},
   OpInfo{"<", 7, False{}}, OpInfo{"<=", 7, False{}}, OpInfo{">", 7, False{}},
   OpInfo{">=", 7, False{}}, OpInfo{".|.", 8, False{}},
   OpInfo{".^.", 9, False{}}, OpInfo{".&.", 10, False{}},
   OpInfo{"<<", 11, False{}}, OpInfo{">>", 11, False{}},
   OpInfo{"+", 12, False{}}, OpInfo{"-", 12, False{}},
   OpInfo{"*", 13, False{}}, OpInfo{"/", 13, False{}}, OpInfo{"%", 13, False{}}]

def P.mk_bin.go(op: String, a: Expr, b: Expr, k: Nat) -> Expr:
  match k:
    case 0n:
      ETy{"->", [a, b]}
    case 1n:
      ETy{"|", [a, b]}
    case 2n:
      ETy{"&", [a, b]}
    case 3n:
      ETy{"#q", Nil{}}
    case 4n:
      ECall{EVar{"Bool.or"}, [a, b]}
    case 5n:
      ECall{EVar{"Bool.and"}, [a, b]}
    case 6n:
      ECtor{"Con", [a, b]}
    case 7n:
      ECall{EVar{"String.append"}, [a, b]}
    case 8n+p:
      EOp{op, a, b}

law P.expr:
  Parser(Expr)

law P.term:
  Parser(Expr)

law P.bin:
  for min: U32
  Parser(Expr)

@unsafe
def P.expr():
  P.bin(1)

def P.gt.if(s: String, sp: Bool, +ln: U32, t: Toks(), k: Nat) -> Unit & Toks():
  match k:
    case 0n:
      (Unit{}, t)
    case 1n:
      (Unit{}, Tok{KSym{">"}, False{}, ln} <> t)
    case 2n:
      (Unit{}, Tok{KSym{"="}, False{}, ln} <> t)
    case 3n+p:
      P.err.go("expected '>'", Tok{KSym{s}, sp, ln} <> t)

def P.is_gt(+t: Tok) -> Bool:
  Bool.or(P.tok_is(t, ">"), Bool.or(P.tok_is(t, ">>"), P.tok_is(t, ">=")))

# '[' ... ']': list literal or array literal [v : T*n] / [v : T^d].
def P.log2(n: U32) -> U32:
  U32.from_nat(U32.log2(n))

def P.arr.size.lit(t: Tok) -> Parser(Expr):
  match t:
    case Tok{KNat{n}, sp, ln}:
      do Parser<Expr>:
        P.skip()
        return ENat{P.log2(n)}
    case other:
      do Parser<Expr>:
        P.err("expected an array size")
        return ENat{0}

@unsafe
def P.arr.size(pow: Bool, t: Tok) -> Parser(Expr):
  match pow:
    case True{}:
      P.term()
    case False{}:
      P.arr.size.lit(t)

@unsafe
def P.arr(v: Expr) -> Parser(Expr):
  do Parser<Expr>:
    P.skip()
    ty : Expr <- P.term()
    t : Tok <- P.peek()
    P.skip()
    t2 : Tok <- P.peek()
    d : Expr <- P.arr.size(P.tok_is(t, "^"), t2)
    P.expect("]")
    return ECall{EVar{"Array.new"}, [ETy{"", Nil{}}, d, v]}

# '{' ... '}': reflexivity, equality type, or annotation.
def P.brace.tail(e: Expr, k: Nat) -> Parser(Expr):
  match k:
    case 0n:
      do Parser<Expr>:
        P.skip()
        b : Expr <- P.expr()
        P.expect(":")
        ty : Expr <- P.expr()
        P.expect("}")
        return ETy{"", Nil{}}
    case 1n:
      do Parser<Expr>:
        P.skip()
        b : Expr <- P.expr()
        P.expect(":")
        ty : Expr <- P.expr()
        P.expect("}")
        return ETy{"", Nil{}}
    case 2n:
      do Parser<Expr>:
        P.skip()
        ty : Expr <- P.expr()
        P.expect("}")
        return EAnn{e, P.head(ty)}
    case 3n+p:
      do Parser<Expr>:
        P.expect("}")
        return e

# Negation of a numeric literal.
def P.neg(e: Expr) -> Expr:
  match e:
    case ENum{n}:
      ENum{(0 - n : U32)}
    case EFlt{s}:
      EFlt{"-" ++ s}
    case other:
      other

# '@x: A -> B' and '&x: A -> B' (dependent types), '&1' (quantities).
def P.dep() -> Parser(Expr):
  do Parser<Expr>:
    e1 : Bool <- P.eat("-")
    e2 : Bool <- P.eat("+")
    x : String <- P.ident()
    P.expect(":")
    ty : Expr <- P.expr()
    return ETy{"", Nil{}}

def P.amp.go(t: Tok) -> Parser(Expr):
  match t:
    case Tok{KNum{n}, sp, ln}:
      do Parser<Expr>:
        P.skip()
        return ETy{"#q", Nil{}}
    case other:
      P.dep()

def P.mk_bin(+op: String, a: Expr, b: Expr) -> Expr:
  P.mk_bin.go(op, a, b, P.which(op, ["->", "|", "&", "<&>", "||", "&&", "<>",
    "++"]))

# Type arguments after '<', up to '>' (splitting '>>').
def P.gt.go(ts: Toks()) -> Unit & Toks():
  match ts:
    case Tok{KSym{+s}, sp, +ln} <> t:
      P.gt.if(s, sp, ln, t, P.which(s, [">", ">>", ">="]))
    case other:
      P.err.go("expected '>'", other)

def P.gt() -> Parser(Unit):
  ts => P.gt.go(ts)

def P.brace.body() -> Parser(Expr):
  do Parser<Expr>:
    e : Expr <- P.expr()
    t : Tok <- P.peek()
    P.brace.tail(e, P.tok_which(t, ["==", "!=", ":"]))

def P.brace.go(refl: Bool) -> Parser(Expr):
  match refl:
    case True{}:
      do Parser<Expr>:
        P.skip()
        P.expect("}")
        return ETy{"", Nil{}}
    case False{}:
      P.brace.body()

def P.brace() -> Parser(Expr):
  do Parser<Expr>:
    P.skip()
    t : Tok <- P.peek()
    P.brace.go(P.tok_is(t, "=="))

law P.op_find:
  for +s: String
  for xs: List<&2, OpInfo>
  OpInfo

@unsafe
def P.op_find.if(+s: String, t: List<&2, OpInfo>, h: OpInfo, hit: Bool) ->
  OpInfo:
  match hit:
    case True{}:
      h
    case False{}:
      P.op_find(s, t)

@unsafe
def P.op_find(s, xs):
  match xs:
    case Nil{}:
      OpInfo{"", 0, False{}}
    case OpInfo{+o, p, r} <> t:
      P.op_find.if(s, t, OpInfo{o, p, r}, String.eq(s, o))

law P.bin.loop:
  for +min: U32
  for lhs: Expr
  Parser(Expr)

@unsafe
def P.bin.loop.go(+min: U32, lhs: Expr, o: String, +p: U32, r: Bool, ok: Bool) ->
  Parser(Expr):
  match ok:
    case False{}:
      Parser.pure(Expr, lhs)
    case True{}:
      do Parser<Expr>:
        P.skip()
        rhs : Expr <- P.bin(Bool.pick(U32, r, p, U32.inc(p)))
        P.bin.loop(min, P.mk_bin(o, lhs, rhs))

@unsafe
def P.bin.loop.op(+min: U32, lhs: Expr, op: OpInfo) -> Parser(Expr):
  OpInfo{o, +p, r} = op
  P.bin.loop.go(min, lhs, o, p, r, Bool.and(U32.is_ne(p, 0), U32.is_ge(p, min)))

# Binary operator at the head (operators need a space before them).
def P.tok_op(t: Tok) -> OpInfo:
  match t:
    case Tok{KSym{s}, True{}, ln}:
      P.op_find(s, P.ops())
    case other:
      OpInfo{"", 0, False{}}

@unsafe
def P.bin.loop(min, lhs):
  do Parser<Expr>:
    t : Tok <- P.peek()
    P.bin.loop.op(min, lhs, P.tok_op(t))

@unsafe
def P.bin(min):
  do Parser<Expr>:
    lhs : Expr <- P.term()
    P.bin.loop(min, lhs)

law P.list:
  for +close: String
  Parser(List<&2, Expr>)

# Comma-separated expressions up to (and including) a closing symbol.
@unsafe
def P.list.more(+close: String, more: Bool) -> Parser(List<&2, Expr>):
  match more:
    case True{}:
      P.list(close)
    case False{}:
      do Parser<List<&2, Expr>>:
        P.expect(close)
        return Nil{}

@unsafe
def P.list.item(+close: String) -> Parser(List<&2, Expr>):
  do Parser<List<&2, Expr>>:
    e : Expr <- P.expr()
    more : Bool <- P.eat(",")
    rest : List<&2, Expr> <- P.list.more(close, more)
    return e <> rest

@unsafe
def P.list.go(+close: String, at_close: Bool) -> Parser(List<&2, Expr>):
  match at_close:
    case True{}:
      do Parser<List<&2, Expr>>:
        P.skip()
        return Nil{}
    case False{}:
      P.list.item(close)

@unsafe
def P.list.stuck(+close: String, +t: Tok, stuck: Bool) -> Parser(List<&2, Expr>):
  match stuck:
    case True{}:
      do Parser<List<&2, Expr>>:
        P.err("unterminated list")
        return Nil{}
    case False{}:
      P.list.go(close, P.tok_is(t, close))

@unsafe
def P.list(close):
  do Parser<List<&2, Expr>>:
    +t : Tok <- P.peek()
    P.list.stuck(close, t, P.stuck(P.tok_kind(t)))

# '(' ... ')': unit, tuple, annotation or parens.
def P.paren.tail(e: Expr, k: Nat) -> Parser(Expr):
  match k:
    case 0n:
      do Parser<Expr>:
        P.skip()
        rest : List<&2, Expr> <- P.list(")")
        return P.tuple(e <> rest)
    case 1n:
      do Parser<Expr>:
        P.skip()
        ty : Expr <- P.expr()
        P.expect(")")
        return EAnn{e, P.head(ty)}
    case 2n+p:
      do Parser<Expr>:
        P.expect(")")
        return e

def P.paren.body() -> Parser(Expr):
  do Parser<Expr>:
    e : Expr <- P.expr()
    t : Tok <- P.peek()
    P.paren.tail(e, P.tok_which(t, [",", ":"]))

def P.paren.go(unit: Bool) -> Parser(Expr):
  match unit:
    case True{}:
      do Parser<Expr>:
        P.skip()
        return ECtor{"Unit", Nil{}}
    case False{}:
      P.paren.body()

def P.paren() -> Parser(Expr):
  do Parser<Expr>:
    P.skip()
    t : Tok <- P.peek()
    P.paren.go(P.tok_is(t, ")"))

def P.brack.tail(e: Expr, arr: Bool) -> Parser(Expr):
  match arr:
    case True{}:
      P.arr(e)
    case False{}:
      do Parser<Expr>:
        _e : Bool <- P.eat(",")
        rest : List<&2, Expr> <- P.list("]")
        return P.elist(e <> rest)

def P.brack.body() -> Parser(Expr):
  do Parser<Expr>:
    e : Expr <- P.expr()
    t : Tok <- P.peek()
    P.brack.tail(e, P.tok_is(t, ":"))

def P.brack.go(empty: Bool) -> Parser(Expr):
  match empty:
    case True{}:
      do Parser<Expr>:
        P.skip()
        return ECtor{"Nil", Nil{}}
    case False{}:
      P.brack.body()

def P.brack() -> Parser(Expr):
  do Parser<Expr>:
    P.skip()
    t : Tok <- P.peek()
    P.brack.go(P.tok_is(t, "]"))

@unsafe
def P.primary.sym(k: Nat) -> Parser(Expr):
  match k:
    case 0n:
      P.paren()
    case 1n:
      P.brack()
    case 2n:
      P.brace()
    case 3n:
      do Parser<Expr>:
        P.skip()
        P.term()
    case 4n:
      do Parser<Expr>:
        P.skip()
        P.term()
    case 5n:
      do Parser<Expr>:
        P.skip()
        e : Expr <- P.term()
        return P.neg(e)
    case 6n:
      do Parser<Expr>:
        P.skip()
        P.dep()
    case 7n:
      do Parser<Expr>:
        P.skip()
        t : Tok <- P.peek()
        P.amp.go(t)
    case 8n:
      do Parser<Expr>:
        P.skip()
        x : String <- P.ident()
        return ETy{"", Nil{}}
    case 9n+p:
      do Parser<Expr>:
        P.err("unexpected symbol")
        return EErr{""}

law P.tyargs:
  Parser(List<&2, Expr>)

@unsafe
def P.tyargs.more(more: Bool) -> Parser(List<&2, Expr>):
  match more:
    case True{}:
      P.tyargs()
    case False{}:
      do Parser<List<&2, Expr>>:
        P.gt()
        return Nil{}

@unsafe
def P.tyargs.item() -> Parser(List<&2, Expr>):
  do Parser<List<&2, Expr>>:
    e : Expr <- P.expr()
    more : Bool <- P.eat(",")
    rest : List<&2, Expr> <- P.tyargs.more(more)
    return e <> rest

@unsafe
def P.tyargs.close(close: Bool) -> Parser(List<&2, Expr>):
  match close:
    case True{}:
      do Parser<List<&2, Expr>>:
        P.gt()
        return Nil{}
    case False{}:
      P.tyargs.item()

@unsafe
def P.tyargs.go(+t: Tok, stuck: Bool) -> Parser(List<&2, Expr>):
  match stuck:
    case True{}:
      Parser.pure(List<&2, Expr>, Nil{})
    case False{}:
      P.tyargs.close(P.is_gt(t))

@unsafe
def P.tyargs():
  do Parser<List<&2, Expr>>:
    +t : Tok <- P.peek()
    P.tyargs.go(t, P.stuck(P.tok_kind(t)))

def P.after_id.k(+name: String, k: Nat) -> Parser(Expr):
  match k:
    case 0n:
      do Parser<Expr>:
        P.skip()
        args : List<&2, Expr> <- P.list("}")
        return ECtor{name, args}
    case 1n:
      do Parser<Expr>:
        P.skip()
        args : List<&2, Expr> <- P.tyargs()
        return ETy{name, args}
    case 2n+p:
      Parser.pure(Expr, EVar{name})

def P.after_id.go(+name: String, k: Nat, lam: Bool) -> Parser(Expr):
  match lam:
    case True{}:
      do Parser<Expr>:
        P.skip()
        body : Expr <- P.expr()
        return ELam{PVar{name}, body}
    case False{}:
      P.after_id.k(name, k)

def P.tok_sp(t: Tok) -> Bool:
  Tok{k, sp, ln} = t
  sp

# After an identifier: lambda, constructor, type application or variable.
def P.after_id(+name: String, +t: Tok) -> Parser(Expr):
  P.after_id.go(name, Bool.pick(Nat, P.tok_sp(t), 3n, P.tok_which(t, ["{", "<"])),
    P.tok_is(t, "=>"))

@unsafe
def P.primary.k(k: TK) -> Parser(Expr):
  match k:
    case KId{name}:
      do Parser<Expr>:
        P.skip()
        t : Tok <- P.peek()
        P.after_id(name, t)
    case KNum{n}:
      do Parser<Expr>:
        P.skip()
        return ENum{n}
    case KNat{n}:
      do Parser<Expr>:
        P.skip()
        return ENat{n}
    case KNatPlus{n}:
      do Parser<Expr>:
        P.skip()
        e : Expr <- P.term()
        return ESucc{n, e}
    case KFlt{s}:
      do Parser<Expr>:
        P.skip()
        return EFlt{s}
    case KChr{n}:
      do Parser<Expr>:
        P.skip()
        return ECtor{"Chr", [ENum{n}]}
    case KStr{s}:
      do Parser<Expr>:
        P.skip()
        return EStr{s}
    case KSym{s}:
      P.primary.sym(P.which(s, ["(", "[", "{", "~", "+", "-", "@", "&", "?"]))
    case other:
      do Parser<Expr>:
        P.err("expected an expression")
        return EErr{""}

def P.primary() -> Parser(Expr):
  do Parser<Expr>:
    t : Tok <- P.peek()
    P.primary.k(P.tok_kind(t))

law P.postfix:
  for e: Expr
  Parser(Expr)

# Postfix: calls f(..), f!(..), and indexing a[i].
@unsafe
def P.postfix.k(e: Expr, k: Nat) -> Parser(Expr):
  match k:
    case 0n:
      do Parser<Expr>:
        P.skip()
        args : List<&2, Expr> <- P.list(")")
        P.postfix(ECall{e, args})
    case 1n:
      do Parser<Expr>:
        P.skip()
        P.expect("(")
        args : List<&2, Expr> <- P.list(")")
        P.postfix(ECall{EVar{"%gpu"}, e <> args})
    case 2n:
      do Parser<Expr>:
        P.skip()
        i : Expr <- P.expr()
        P.expect("]")
        P.postfix(ECall{EVar{"Array.get"}, [ETy{"U32", Nil{}}, e, i]})
    case 3n+p:
      Parser.pure(Expr, e)

@unsafe
def P.postfix.t(e: Expr, +t: Tok) -> Parser(Expr):
  P.postfix.k(e, Bool.pick(Nat, P.tok_sp(t), 9n, P.tok_which(t, ["(", "!", "["])))

@unsafe
def P.postfix(e):
  do Parser<Expr>:
    t : Tok <- P.peek()
    P.postfix.t(e, t)

def P.term():
  do Parser<Expr>:
    e : Expr <- P.primary()
    P.postfix(e)

# Patterns
# ========

def P.pat_seq.stop(+stops: List<&2, String>, +t: Tok) -> Bool:
  Bool.or(P.stuck(P.tok_kind(t)), Bool.or(P.is_nl(t),
    Nat.is_lt(P.tok_which(t, stops), List.length(&2, String, stops))))

law P.pat:
  Parser(Pat)

@unsafe
def P.pat.cons(p: Pat, cons: Bool) -> Parser(Pat):
  match cons:
    case True{}:
      do Parser<Pat>:
        P.skip()
        rest : Pat <- P.pat()
        return PCtor{"Con", [p, rest]}
    case False{}:
      Parser.pure(Pat, p)

law P.pat_seq:
  for +stops: List<&2, String>
  Parser(List<&2, Pat>)

# Space-separated patterns up to (not including) one of the stop symbols.
@unsafe
def P.pat_seq.go(+stops: List<&2, String>, +t: Tok, stop: Bool) ->
  Parser(List<&2, Pat>):
  match stop:
    case True{}:
      Parser.pure(List<&2, Pat>, Nil{})
    case False{}:
      do Parser<List<&2, Pat>>:
        p : Pat <- P.pat()
        rest : List<&2, Pat> <- P.pat_seq(stops)
        return p <> rest

@unsafe
def P.pat_seq(stops):
  do Parser<List<&2, Pat>>:
    +t : Tok <- P.peek()
    P.pat_seq.go(stops, t, P.pat_seq.stop(stops, t))

law P.pats:
  for +close: String
  Parser(List<&2, Pat>)

@unsafe
def P.pats.more(+close: String, more: Bool) -> Parser(List<&2, Pat>):
  match more:
    case True{}:
      P.pats(close)
    case False{}:
      do Parser<List<&2, Pat>>:
        P.expect(close)
        return Nil{}

@unsafe
def P.pats.item(+close: String) -> Parser(List<&2, Pat>):
  do Parser<List<&2, Pat>>:
    p : Pat <- P.pat()
    more : Bool <- P.eat(",")
    rest : List<&2, Pat> <- P.pats.more(close, more)
    return p <> rest

@unsafe
def P.pats.close(+close: String, at: Bool) -> Parser(List<&2, Pat>):
  match at:
    case True{}:
      do Parser<List<&2, Pat>>:
        P.skip()
        return Nil{}
    case False{}:
      P.pats.item(close)

@unsafe
def P.pats.go(+close: String, +t: Tok, stuck: Bool) -> Parser(List<&2, Pat>):
  match stuck:
    case True{}:
      Parser.pure(List<&2, Pat>, Nil{})
    case False{}:
      P.pats.close(close, P.tok_is(t, close))

# Comma-separated patterns up to (and including) a closing symbol.
@unsafe
def P.pats(close):
  do Parser<List<&2, Pat>>:
    +t : Tok <- P.peek()
    P.pats.go(close, t, P.stuck(P.tok_kind(t)))

@unsafe
def P.pat.id(+name: String, ctor: Bool) -> Parser(Pat):
  match ctor:
    case True{}:
      do Parser<Pat>:
        P.skip()
        args : List<&2, Pat> <- P.pats("}")
        return PCtor{name, args}
    case False{}:
      Parser.pure(Pat, PVar{name})

law P.pat1:
  Parser(Pat)

@unsafe
def P.pat.sym(k: Nat) -> Parser(Pat):
  match k:
    case 0n:
      do Parser<Pat>:
        P.skip()
        P.pat1()
    case 1n:
      do Parser<Pat>:
        P.skip()
        P.pat1()
    case 2n:
      do Parser<Pat>:
        P.skip()
        ps : List<&2, Pat> <- P.pats(")")
        return P.ptuple(ps)
    case 3n:
      do Parser<Pat>:
        P.skip()
        ps : List<&2, Pat> <- P.pats("]")
        return P.plist(ps)
    case 4n+p:
      do Parser<Pat>:
        P.err("expected a pattern")
        return PVar{"_"}

# A string literal pattern: a chain of SCon cells.
def P.pstr(s: String) -> Pat:
  match s:
    case SNil{}:
      PCtor{"SNil", Nil{}}
    case SCon{Chr{c}, t}:
      PCtor{"SCon", [PCtor{"Chr", [PNum{c}]}, P.pstr(t)]}

@unsafe
def P.pat1.k(k: TK) -> Parser(Pat):
  match k:
    case KId{name}:
      do Parser<Pat>:
        P.skip()
        +t : Tok <- P.peek()
        P.pat.id(name, Bool.and(P.tok_is(t, "{"), Bool.not(P.tok_sp(t))))
    case KNat{n}:
      do Parser<Pat>:
        P.skip()
        return PNat{n}
    case KNatPlus{n}:
      do Parser<Pat>:
        P.skip()
        p : Pat <- P.pat1()
        return PSucc{n, p}
    case KNum{n}:
      do Parser<Pat>:
        P.skip()
        return PNum{n}
    case KChr{n}:
      do Parser<Pat>:
        P.skip()
        return PCtor{"Chr", [PNum{n}]}
    case KStr{s}:
      do Parser<Pat>:
        P.skip()
        return P.pstr(s)
    case KSym{s}:
      P.pat.sym(P.which(s, ["+", "-", "(", "["]))
    case other:
      do Parser<Pat>:
        P.err("expected a pattern")
        return PVar{"_"}

@unsafe
def P.pat1():
  do Parser<Pat>:
    t : Tok <- P.peek()
    P.pat1.k(P.tok_kind(t))

@unsafe
def P.pat():
  do Parser<Pat>:
    p : Pat <- P.pat1()
    t : Tok <- P.peek()
    P.pat.cons(p, P.tok_is(t, "<>"))

# Statements
# ==========

def P.skip_ann.go(ann: Bool) -> Parser(Unit):
  match ann:
    case True{}:
      do Parser<Unit>:
        P.skip()
        ty : Expr <- P.expr()
        return Unit{}
    case False{}:
      Parser.pure(Unit, Unit{})

# Skips an optional ': Type' annotation.
def P.skip_ann() -> Parser(Unit):
  do Parser<Unit>:
    t : Tok <- P.peek()
    P.skip_ann.go(P.tok_is(t, ":"))

# Array write 'a[i] <- v' or monadic bind 'x : T <- v' / 'x <- v'.
def P.bind.arr(+name: String, arr: Bool) -> Parser(List<&2, Stmt>):
  match arr:
    case True{}:
      do Parser<List<&2, Stmt>>:
        P.skip()
        i : Expr <- P.expr()
        P.expect("]")
        P.expect("<-")
        v : Expr <- P.expr()
        return [SLet{PVar{name}, ECall{EVar{"Array.set"}, [ETy{"U32", Nil{}}, EVar{name}, i, v]}}]
    case False{}:
      do Parser<List<&2, Stmt>>:
        P.skip_ann()
        P.expect("<-")
        v : Expr <- P.expr()
        return [SBind{name, v}]

def P.bind_stmt() -> Parser(List<&2, Stmt>):
  do Parser<List<&2, Stmt>>:
    e1 : Bool <- P.eat("+")
    name : String <- P.ident()
    +t : Tok <- P.peek()
    P.bind.arr(name, Bool.and(P.tok_is(t, "["), Bool.not(P.tok_sp(t))))

# Values of a parallel let: one expression per pattern.
def P.exprs_n(n: Nat) -> Parser(List<&2, Expr>):
  match n:
    case 0n:
      Parser.pure(List<&2, Expr>, Nil{})
    case 1n+p:
      do Parser<List<&2, Expr>>:
        e : Expr <- P.expr()
        rest : List<&2, Expr> <- P.exprs_n(p)
        return e <> rest

def P.lets(ps: List<&2, Pat>, vs: List<&2, Expr>) -> List<&2, Stmt>:
  match ps vs:
    case p <> pt v <> vt:
      SLet{p, v} <> P.lets(pt, vt)
    case pl vl:
      Nil{}

law P.stmts:
  Parser(List<&2, Stmt>)

def P.is_de(t: Tok) -> Bool:
  match t:
    case Tok{KDe{}, sp, ln}:
      True{}
    case other:
      False{}

def P.is_in(t: Tok) -> Bool:
  match t:
    case Tok{KIn{}, sp, ln}:
      True{}
    case other:
      False{}

# Folds a statement list into an expression.
def Fold.plain(ss: List<&2, Stmt>) -> Expr:
  match ss:
    case Nil{}:
      EErr{"empty block"}
    case SLet{p, v} <> Nil{}:
      v
    case SBind{x, v} <> Nil{}:
      v
    case SRet{e} <> Nil{}:
      e
    case SExp{e} <> Nil{}:
      e
    case SSkip{} <> Nil{}:
      ETy{"", Nil{}}
    case SLet{p, v} <> t:
      ELet{p, v, Fold.plain(t)}
    case SBind{x, v} <> t:
      ELet{PVar{x}, v, Fold.plain(t)}
    case SRet{e} <> t:
      e
    case SExp{e} <> t:
      ELet{PVar{"_"}, e, Fold.plain(t)}
    case SSkip{} <> t:
      Fold.plain(t)

def Fold.app(+m: String, +f: String, +xs: List<&2, Expr>, ys: List<&2, Expr>) ->
  Expr:
  ECall{EVar{m ++ "." ++ f}, List.append(&2, Expr, xs, ys)}

def Fold.do(+m: String, +xs: List<&2, Expr>, +r: Expr, ss: List<&2, Stmt>) ->
  Expr:
  match ss:
    case Nil{}:
      EErr{"empty do block"}
    case SLet{p, v} <> Nil{}:
      v
    case SBind{x, v} <> Nil{}:
      v
    case SRet{e} <> Nil{}:
      Fold.app(m, "pure", xs, [r, e])
    case SExp{e} <> Nil{}:
      e
    case SSkip{} <> Nil{}:
      ETy{"", Nil{}}
    case SLet{p, v} <> t:
      ELet{p, v, Fold.do(m, xs, r, t)}
    case SBind{x, v} <> t:
      Fold.app(m, "bind", xs, [ETy{"", Nil{}}, r, v, ELam{PVar{x}, Fold.do(m, xs, r, t)}])
    case SRet{e} <> t:
      Fold.app(m, "pure", xs, [r, e])
    case SExp{e} <> t:
      Fold.app(m, "bind", xs, [ETy{"", Nil{}}, r, e, ELam{PVar{"_"}, Fold.do(m, xs, r, t)}])
    case SSkip{} <> t:
      Fold.do(m, xs, r, t)

def P.init(xs: List<&2, Expr>) -> List<&2, Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> Nil{}:
      Nil{}
    case h <> t:
      h <> P.init(t)

def P.last(xs: List<&2, Expr>) -> Expr:
  match xs:
    case Nil{}:
      ETy{"", Nil{}}
    case h <> Nil{}:
      h
    case h <> t:
      P.last(t)

def P.expect_in.go(ok: Bool) -> Parser(Unit):
  match ok:
    case True{}:
      P.skip()
    case False{}:
      P.err("expected an indented block")

def P.expect_in() -> Parser(Unit):
  do Parser<Unit>:
    t : Tok <- P.peek()
    P.expect_in.go(P.is_in(t))

@unsafe
def P.do() -> Parser(Expr):
  do Parser<Expr>:
    P.skip()
    m : String <- P.ident()
    P.expect("<")
    +args : List<&2, Expr> <- P.tyargs()
    P.expect(":")
    P.expect_in()
    ss : List<&2, Stmt> <- P.stmts()
    return Fold.do(m, P.init(args), P.last(args), ss)

# A block body: an indented statement list, folded.
@unsafe
def P.body() -> Parser(Expr):
  do Parser<Expr>:
    P.expect_in()
    ss : List<&2, Stmt> <- P.stmts()
    return Fold.plain(ss)

# A parallel let (two names or more) keeps its values together, as one let
# of a %par pattern: its values may run in parallel.
def P.lets.par(+ps: List<&2, Pat>, +vs: List<&2, Expr>) -> List<&2, Stmt>:
  Bool.pick(List<&2, Stmt>, Nat.is_gt(List.length(&2, Pat, ps), 1n),
    [SLet{PCtor{"%par", ps}, ECtor{"%par", vs}}], P.lets(ps, vs))

def P.let_stmt() -> Parser(List<&2, Stmt>):
  do Parser<List<&2, Stmt>>:
    +ps : List<&2, Pat> <- P.pat_seq(["=", ":"])
    P.skip_ann()
    P.expect("=")
    +vs : List<&2, Expr> <- P.exprs_n(List.length(&2, Pat, ps))
    return P.lets.par(ps, vs)

def P.stmt.scan.go(k: Nat) -> Parser(List<&2, Stmt>):
  match k:
    case 0n:
      do Parser<List<&2, Stmt>>:
        e : Expr <- P.expr()
        return [SExp{e}]
    case 1n:
      P.let_stmt()
    case 2n+p:
      P.bind_stmt()

def P.stmt.scan(k: U32) -> Parser(List<&2, Stmt>):
  P.stmt.scan.go(U32.to_nat(k))

law P.scan.go:
  for ts: Toks()
  for +depth: U32
  U32

@unsafe
def P.scan.end(t: Toks(), +depth: U32, top: Bool) -> U32:
  match top:
    case True{}:
      0
    case False{}:
      P.scan.go(t, depth)

@unsafe
def P.scan.top(t: Toks(), +depth: U32, +r: U32, top: Bool) -> U32:
  match top:
    case True{}:
      r
    case False{}:
      P.scan.go(t, depth)

@unsafe
def P.scan.sym(t: Toks(), +depth: U32, k: Nat) -> U32:
  match k:
    case 0n:
      P.scan.top(t, depth, 1, U32.is_zero(depth))
    case 1n:
      P.scan.top(t, depth, 2, U32.is_zero(depth))
    case 2n:
      P.scan.go(t, U32.inc(depth))
    case 3n:
      P.scan.go(t, U32.inc(depth))
    case 4n:
      P.scan.go(t, U32.inc(depth))
    case 5n:
      P.scan.go(t, (depth - 1 : U32))
    case 6n:
      P.scan.go(t, (depth - 1 : U32))
    case 7n:
      P.scan.go(t, (depth - 1 : U32))
    case 8n+p:
      P.scan.go(t, depth)

# Finds the first '=' or '<-' at depth 0 on the current line:
# 0 none, 1 '=', 2 '<-'.
@unsafe
def P.scan.go(ts, depth):
  match ts:
    case Nil{}:
      0
    case Tok{KSym{+s}, sp, ln} <> t:
      P.scan.sym(t, depth, P.which(s, ["=", "<-", "(", "[", "{", ")", "]", "}"]))
    case Tok{KId{s}, sp, ln} <> t:
      P.scan.go(t, depth)
    case Tok{KNL{}, sp, ln} <> t:
      P.scan.end(t, depth, U32.is_zero(depth))
    case Tok{KIn{}, sp, ln} <> t:
      0
    case Tok{KDe{}, sp, ln} <> t:
      0
    case Tok{KEof{}, sp, ln} <> t:
      0
    case Tok{KErr{e}, sp, ln} <> t:
      0
    case h <> t:
      P.scan.go(t, depth)

def P.scan.ret(+ts: Toks()) -> U32 & Toks():
  (P.scan.go(ts, 0), ts)

def P.scan() -> Parser(U32):
  ts => P.scan.ret(ts)

law P.skip_block.go:
  for ts: Toks()
  for +depth: U32
  Toks()

# Skips the rest of the line (up to, not including, the newline).
@unsafe
def P.skip_line.go(ts: Toks()) -> Toks():
  match ts:
    case Nil{}:
      Nil{}
    case Tok{KNL{}, sp, ln} <> t:
      Tok{KNL{}, sp, ln} <> t
    case Tok{KDe{}, sp, ln} <> t:
      Tok{KDe{}, sp, ln} <> t
    case Tok{KEof{}, sp, ln} <> t:
      Tok{KEof{}, sp, ln} <> t
    case Tok{KErr{e}, sp, ln} <> t:
      Tok{KErr{e}, sp, ln} <> t
    case Tok{KIn{}, sp, ln} <> t:
      P.skip_block.go(t, 1)
    case h <> t:
      P.skip_line.go(t)

@unsafe
def P.skip_block.de(t: Toks(), +depth: U32, last: Bool) -> Toks():
  match last:
    case True{}:
      t
    case False{}:
      P.skip_block.go(t, (depth - 1 : U32))

# Skips tokens until the matching dedent (consumed).
@unsafe
def P.skip_block.go(ts, depth):
  match ts:
    case Nil{}:
      Nil{}
    case Tok{KIn{}, sp, ln} <> t:
      P.skip_block.go(t, U32.inc(depth))
    case Tok{KDe{}, sp, ln} <> t:
      P.skip_block.de(t, depth, U32.is_eq(depth, 1))
    case Tok{KEof{}, sp, ln} <> t:
      Tok{KEof{}, sp, ln} <> t
    case h <> t:
      P.skip_block.go(t, depth)

def P.skip_line() -> Parser(Unit):
  ts => (Unit{}, P.skip_line.go(ts))

law P.cases:
  Parser(List<&2, Expr>)

# A 'case' list of a match.
@unsafe
def P.cases.go(k: Nat) -> Parser(List<&2, Expr>):
  match k:
    case 0n:
      do Parser<List<&2, Expr>>:
        P.skip()
        ps : List<&2, Pat> <- P.pat_seq([":"])
        P.expect(":")
        body : Expr <- P.body()
        rest : List<&2, Expr> <- P.cases()
        return ECase{ps, body} <> rest
    case 1n+p:
      Parser.pure(List<&2, Expr>, Nil{})

def P.tok_which_id(t: Tok, xs: List<&2, String>) -> Nat:
  match t:
    case Tok{KId{s}, sp, ln}:
      P.which(s, xs)
    case other:
      99n

@unsafe
def P.cases.de(de: Bool) -> Parser(List<&2, Expr>):
  match de:
    case True{}:
      do Parser<List<&2, Expr>>:
        P.skip()
        return Nil{}
    case False{}:
      do Parser<List<&2, Expr>>:
        +t : Tok <- P.peek()
        P.cases.go(P.tok_which_id(t, ["case"]))

@unsafe
def P.cases():
  do Parser<List<&2, Expr>>:
    P.nls()
    t : Tok <- P.peek()
    P.cases.de(P.is_de(t))

def P.match.body(has: Bool) -> Parser(List<&2, Expr>):
  match has:
    case True{}:
      do Parser<List<&2, Expr>>:
        P.skip()
        P.cases()
    case False{}:
      Parser.pure(List<&2, Expr>, Nil{})

law P.scrs:
  Parser(List<&2, Expr>)

@unsafe
def P.scrs.go(+t: Tok, stop: Bool) -> Parser(List<&2, Expr>):
  match stop:
    case True{}:
      Parser.pure(List<&2, Expr>, Nil{})
    case False{}:
      do Parser<List<&2, Expr>>:
        e : Expr <- P.expr()
        rest : List<&2, Expr> <- P.scrs()
        return e <> rest

@unsafe
def P.scrs():
  do Parser<List<&2, Expr>>:
    +t : Tok <- P.peek()
    P.scrs.go(t, Bool.or(P.tok_is(t, ":"), P.stuck(P.tok_kind(t))))

def P.match() -> Parser(Expr):
  do Parser<Expr>:
    P.skip()
    scrs : List<&2, Expr> <- P.scrs()
    P.expect(":")
    t : Tok <- P.peek()
    cases : List<&2, Expr> <- P.match.body(P.is_in(t))
    return EMatch{scrs, cases}

def P.stmt.id(k: Nat) -> Parser(List<&2, Stmt>):
  match k:
    case 0n:
      do Parser<List<&2, Stmt>>:
        e : Expr <- P.match()
        return [SExp{e}]
    case 1n:
      do Parser<List<&2, Stmt>>:
        P.skip()
        e : Expr <- P.expr()
        return [SRet{e}]
    case 2n:
      do Parser<List<&2, Stmt>>:
        e : Expr <- P.do()
        return [SExp{e}]
    case 3n+p:
      do Parser<List<&2, Stmt>>:
        k : U32 <- P.scan()
        P.stmt.scan(k)

def P.stmt.go(+t: Tok, rw: Bool) -> Parser(List<&2, Stmt>):
  match rw:
    case True{}:
      do Parser<List<&2, Stmt>>:
        P.skip_line()
        return [SSkip{}]
    case False{}:
      P.stmt.id(P.tok_which_id(t, ["match", "return", "do"]))

def P.stmt() -> Parser(List<&2, Stmt>):
  do Parser<List<&2, Stmt>>:
    +t : Tok <- P.peek()
    P.stmt.go(t, P.tok_is(t, "%"))

@unsafe
def P.stmts.go(+t: Tok, k: Nat) -> Parser(List<&2, Stmt>):
  match k:
    case 0n:
      do Parser<List<&2, Stmt>>:
        P.skip()
        return Nil{}
    case 1n:
      Parser.pure(List<&2, Stmt>, Nil{})
    case 2n+p:
      do Parser<List<&2, Stmt>>:
        s : List<&2, Stmt> <- P.stmt()
        rest : List<&2, Stmt> <- P.stmts()
        return List.append(&2, Stmt, s, rest)

# Statements up to (and including) the block's dedent.
def P.stmts():
  do Parser<List<&2, Stmt>>:
    P.nls()
    +t : Tok <- P.peek()
    P.stmts.go(t, Bool.pick(Nat, P.is_de(t), 0n,
      Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n)))

# Declarations
# ============

def P.tok_is_id(+t: Tok, +s: String) -> Bool:
  match t:
    case Tok{KId{x}, sp, ln}:
      Str.eq(x, s)
    case other:
      False{}

def P.param.mode(+t: Tok) -> U32:
  Bool.pick(U32, P.tok_is(t, "-"), 1,
    Bool.pick(U32, P.tok_is(t, "+"), 2,
      Bool.pick(U32, P.tok_is(t, "~"), 3, 0)))

def P.param.ty(name: String, +mode: U32, has: Bool) -> Parser(Param):
  match has:
    case True{}:
      do Parser<Param>:
        P.skip()
        ty : Expr <- P.expr()
        return Param{name, mode, P.head(ty)}
    case False{}:
      Parser.pure(Param, Param{name, Bool.pick(U32, U32.is_zero(mode), 4, mode), ""})

def P.param.skip_mode.go(z: Bool) -> Parser(Unit):
  match z:
    case True{}:
      Parser.pure(Unit, Unit{})
    case False{}:
      P.skip()

def P.param.skip_mode(mode: U32) -> Parser(Unit):
  P.param.skip_mode.go(U32.is_zero(mode))

def P.param() -> Parser(Param):
  do Parser<Param>:
    +t : Tok <- P.peek()
    +mode : U32 <- Parser.pure(U32, P.param.mode(t))
    P.param.skip_mode(mode)
    name : String <- P.ident()
    t2 : Tok <- P.peek()
    P.param.ty(name, mode, P.tok_is(t2, ":"))

def P.ret.go(has: Bool) -> Parser(Expr):
  match has:
    case True{}:
      do Parser<Expr>:
        P.skip()
        P.expr()
    case False{}:
      Parser.pure(Expr, ETy{"", Nil{}})

def P.file.err(ts: Toks()) -> String:
  match ts:
    case Tok{KErr{e}, sp, ln} <> t:
      e
    case other:
      ""

# Parses a whole file; the error (if any) is returned beside the decls.
def P.file.fin(r: List<&2, Decl> & Toks()) -> List<&2, Decl> & String:
  (ds, ts) = r
  (ds, P.file.err(ts))

# Skips the remaining lines of a block, including its dedent.
def P.skip_rest() -> Parser(Unit):
  ts => (Unit{}, P.skip_block.go(ts, 1))

def P.eff.go(ts: Toks(), acc: List<&2, String>) -> List<&2, String> & Toks():
  match ts:
    case Nil{}:
      (acc, Nil{})
    case Tok{KStr{x}, sp, ln} <> t:
      P.eff.go(t, List.append(&2, String, acc, [x]))
    case Tok{KDe{}, sp, ln} <> t:
      (acc, t)
    case Tok{KEof{}, sp, ln} <> t:
      (acc, Tok{KEof{}, sp, ln} <> t)
    case Tok{KErr{e}, sp, ln} <> t:
      (acc, Tok{KErr{e}, sp, ln} <> t)
    case h <> t:
      P.eff.go(t, acc)

# The files a foreign def imports, up to (and including) its dedent.
def P.eff.imports() -> Parser(List<&2, String>):
  ts => P.eff.go(ts, Nil{})

@unsafe
def P.def.body(name: String, params: List<&2, Param>, ret: Expr, eff: Bool) -> Parser(Decl):
  match eff:
    case True{}:
      do Parser<Decl>:
        imps : List<&2, String> <- P.eff.imports()
        return DEff{name, params, imps}
    case False{}:
      do Parser<Decl>:
        ss : List<&2, Stmt> <- P.stmts()
        return DDef{name, params, Fold.plain(ss), ret}

def P.import.alias(has: Bool) -> Parser(String):
  match has:
    case True{}:
      do Parser<String>:
        P.skip()
        P.ident()
    case False{}:
      Parser.pure(String, "")

def P.import.path.cat(s: String, r: String & Toks()) -> String & Toks():
  (rest, ts) = r
  (s ++ rest, ts)

law P.params:
  Parser(List<&2, Param>)

@unsafe
def P.params.more(more: Bool) -> Parser(List<&2, Param>):
  match more:
    case True{}:
      P.params()
    case False{}:
      do Parser<List<&2, Param>>:
        P.expect(")")
        return Nil{}

@unsafe
def P.params.go(close: Bool) -> Parser(List<&2, Param>):
  match close:
    case True{}:
      do Parser<List<&2, Param>>:
        P.skip()
        return Nil{}
    case False{}:
      do Parser<List<&2, Param>>:
        p : Param <- P.param()
        more : Bool <- P.eat(",")
        rest : List<&2, Param> <- P.params.more(more)
        return p <> rest

# Parameters up to (and including) ')'.
@unsafe
def P.params():
  do Parser<List<&2, Param>>:
    +t : Tok <- P.peek()
    P.params.go(Bool.or(P.tok_is(t, ")"), P.stuck(P.tok_kind(t))))

def P.def() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    name : String <- P.ident()
    P.expect("(")
    params : List<&2, Param> <- P.params()
    t : Tok <- P.peek()
    ret : Expr <- P.ret.go(P.tok_is(t, "->"))
    P.expect(":")
    P.expect_in()
    t2 : Tok <- P.peek()
    P.def.body(name, params, ret, P.tok_is_id(t2, "import"))

law P.fields:
  Parser(List<&2, Field>)

@unsafe
def P.fields.go(close: Bool) -> Parser(List<&2, Field>):
  match close:
    case True{}:
      do Parser<List<&2, Field>>:
        P.skip()
        return Nil{}
    case False{}:
      do Parser<List<&2, Field>>:
        e1 : Bool <- P.eat("+")
        e2 : Bool <- P.eat("-")
        name : String <- P.ident()
        P.expect(":")
        ty : Expr <- P.expr()
        e3 : Bool <- P.eat(",")
        rest : List<&2, Field> <- P.fields()
        return Field{name, ty} <> rest

# Constructor fields up to (and including) '}'.
@unsafe
def P.fields():
  do Parser<List<&2, Field>>:
    +t : Tok <- P.peek()
    P.fields.go(Bool.or(P.tok_is(t, "}"), P.stuck(P.tok_kind(t))))

law P.ctors:
  Parser(List<&2, Ctor>)

@unsafe
def P.ctors.go(+t: Tok, k: Nat) -> Parser(List<&2, Ctor>):
  match k:
    case 0n:
      do Parser<List<&2, Ctor>>:
        P.skip()
        return Nil{}
    case 1n:
      Parser.pure(List<&2, Ctor>, Nil{})
    case 2n+p:
      do Parser<List<&2, Ctor>>:
        name : String <- P.ident()
        P.expect("{")
        fields : List<&2, Field> <- P.fields()
        rest : List<&2, Ctor> <- P.ctors()
        return Ctor{name, fields} <> rest

# Constructor lines up to (and including) the dedent.
@unsafe
def P.ctors():
  do Parser<List<&2, Ctor>>:
    P.nls()
    +t : Tok <- P.peek()
    P.ctors.go(t, Bool.pick(Nat, P.is_de(t), 0n,
      Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n)))

def P.type.body(has: Bool) -> Parser(List<&2, Ctor>):
  match has:
    case True{}:
      do Parser<List<&2, Ctor>>:
        P.skip()
        P.ctors()
    case False{}:
      Parser.pure(List<&2, Ctor>, Nil{})

law P.until_is.go:
  for ts: Toks()
  Toks()

@unsafe
def P.until_is.if(h: Tok, t: Toks(), hit: Bool) -> Toks():
  match hit:
    case True{}:
      t
    case False{}:
      P.until_is.go(t)

@unsafe
def P.until_is.go(ts):
  match ts:
    case Nil{}:
      Nil{}
    case Tok{KId{+s}, sp, ln} <> t:
      P.until_is.if(Tok{KId{s}, sp, ln}, t, Str.eq(s, "is"))
    case Tok{KEof{}, sp, ln} <> t:
      Tok{KEof{}, sp, ln} <> t
    case Tok{KErr{e}, sp, ln} <> t:
      Tok{KErr{e}, sp, ln} <> t
    case h <> t:
      P.until_is.go(t)

# Skips to just after the 'is' keyword.
def P.until_is() -> Parser(Unit):
  ts => (Unit{}, P.until_is.go(ts))

law P.law.go:
  for +t: Tok
  for k: Nat
  Parser(List<&2, Param>)

# The 'for' parameters of a law, up to (and including) the dedent.
@unsafe
def P.law.lines() -> Parser(List<&2, Param>):
  do Parser<List<&2, Param>>:
    P.nls()
    +t : Tok <- P.peek()
    P.law.go(t, Bool.pick(Nat, P.is_de(t), 0n,
      Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n)))

@unsafe
def P.law.line(k: Nat) -> Parser(List<&2, Param>):
  match k:
    case 0n:
      do Parser<List<&2, Param>>:
        P.skip()
        p : Param <- P.param()
        P.skip_line()
        rest : List<&2, Param> <- P.law.lines()
        return p <> rest
    case 1n+p:
      do Parser<List<&2, Param>>:
        P.skip_line()
        P.law.lines()

@unsafe
def P.law.go(t, k):
  match k:
    case 0n:
      do Parser<List<&2, Param>>:
        P.skip()
        return Nil{}
    case 1n:
      Parser.pure(List<&2, Param>, Nil{})
    case 2n+p:
      P.law.line(P.tok_which_id(t, ["for"]))

def P.law() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    name : String <- P.ident()
    P.expect(":")
    P.expect_in()
    params : List<&2, Param> <- P.law.lines()
    return DLaw{name, params}

law P.decl:
  Parser(Decl)

law P.decls:
  Parser(List<&2, Decl>)

@unsafe
def P.decls.go(stop: Bool) -> Parser(List<&2, Decl>):
  match stop:
    case True{}:
      Parser.pure(List<&2, Decl>, Nil{})
    case False{}:
      do Parser<List<&2, Decl>>:
        d : Decl <- P.decl()
        rest : List<&2, Decl> <- P.decls()
        return d <> rest

@unsafe
def P.decls():
  do Parser<List<&2, Decl>>:
    P.nls()
    t : Tok <- P.peek()
    P.decls.go(P.stuck(P.tok_kind(t)))

def P.file(src: String) -> List<&2, Decl> & String:
  P.file.fin(P.decls()(Lex.all(src)))

law P.tparams:
  Parser(List<&2, String>)

# Type parameters '<a, -A: Kind(a)>' ('<-' starts one with an erased mark).
@unsafe
def P.tparams.opt(k: Nat) -> Parser(List<&2, String>):
  match k:
    case 0n:
      do Parser<List<&2, String>>:
        P.skip()
        P.tparams()
    case 1n:
      do Parser<List<&2, String>>:
        P.skip()
        P.tparams()
    case 2n+p:
      Parser.pure(List<&2, String>, Nil{})

def P.type() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    name : String <- P.ident()
    +t0 : Tok <- P.peek()
    params : List<&2, String> <- P.tparams.opt(P.tok_which(t0, ["<", "<-"]))
    P.until_is()
    kind : Expr <- P.expr()
    P.expect(":")
    t : Tok <- P.peek()
    ctors : List<&2, Ctor> <- P.type.body(P.is_in(t))
    return DType{name, params, ctors}

@unsafe
def P.tparams.more(more: Bool) -> Parser(List<&2, String>):
  match more:
    case True{}:
      P.tparams()
    case False{}:
      do Parser<List<&2, String>>:
        P.gt()
        return Nil{}

@unsafe
def P.tparams():
  do Parser<List<&2, String>>:
    e1 : Bool <- P.eat("-")
    name : String <- P.ident()
    P.skip_ann()
    more : Bool <- P.eat(",")
    rest : List<&2, String> <- P.tparams.more(more)
    return name <> rest

law P.import.path.go:
  for ts: Toks()
  String & Toks()

@unsafe
def P.import.path.id(+s: String, sp: Bool, +ln: U32, t: Toks(), stop: Bool) ->
  String & Toks():
  match stop:
    case True{}:
      ("", Tok{KId{s}, sp, ln} <> t)
    case False{}:
      P.import.path.cat(s, P.import.path.go(t))

# The path: the text of the tokens up to 'as' or the end of the line.
@unsafe
def P.import.path.go(ts):
  match ts:
    case Tok{KId{+s}, sp, ln} <> t:
      P.import.path.id(s, sp, ln, t, Str.eq(s, "as"))
    case Tok{KSym{s}, sp, ln} <> t:
      P.import.path.cat(s, P.import.path.go(t))
    case Tok{KNum{n}, sp, ln} <> t:
      P.import.path.cat(U32.show(n), P.import.path.go(t))
    case other:
      ("", other)

def P.import.path() -> Parser(String):
  ts => P.import.path.go(ts)

# 'import Base' or 'import ./file.bend as M'.
def P.import() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    path : String <- P.import.path()
    t : Tok <- P.peek()
    alias : String <- P.import.alias(P.tok_is_id(t, "as"))
    P.skip_line()
    return DImport{path, alias}

def P.decl.go(k: Nat) -> Parser(Decl):
  match k:
    case 0n:
      P.def()
    case 1n:
      P.type()
    case 2n:
      P.law()
    case 3n:
      P.import()
    case 4n+p:
      do Parser<Decl>:
        P.err("expected a declaration")
        return DImport{"", ""}

@unsafe
def P.decl.at(at: Bool, +t: Tok) -> Parser(Decl):
  match at:
    case True{}:
      do Parser<Decl>:
        P.skip()
        P.skip()
        P.nls()
        P.decl()
    case False{}:
      P.decl.go(P.tok_which_id(t, ["def", "type", "law", "import"]))

@unsafe
def P.decl():
  do Parser<Decl>:
    +t : Tok <- P.peek()
    P.decl.at(P.tok_is(t, "@"), t)

# AST printing
# ============

def Param.show(p: Param) -> String:
  Param{n, m, t} = p
  U32.show(m) ++ n ++ ":" ++ t

law Pat.show:
  for p: Pat
  String

@unsafe
def Pats.show(xs: List<&2, Pat>) -> String:
  match xs:
    case Nil{}:
      ""
    case h <> Nil{}:
      Pat.show(h)
    case h <> t:
      Pat.show(h) ++ " " ++ Pats.show(t)

@unsafe
def Pat.show(p):
  match p:
    case PVar{n}:
      n
    case PCtor{n, args}:
      n ++ "{" ++ Pats.show(args) ++ "}"
    case PNat{n}:
      U32.show(n) ++ "n"
    case PSucc{k, q}:
      U32.show(k) ++ "n+" ++ Pat.show(q)
    case PNum{n}:
      U32.show(n)

law Expr.show:
  for e: Expr
  String

@unsafe
def Fields.show(fs: List<&2, Field>) -> String:
  match fs:
    case Nil{}:
      ""
    case Field{n, t} <> r:
      n ++ ":" ++ Expr.show(t) ++ " " ++ Fields.show(r)

def Ctor.show(c: Ctor) -> String:
  Ctor{n, fs} = c
  n ++ "{" ++ Fields.show(fs) ++ "}"

@unsafe
def Exprs.show(xs: List<&2, Expr>) -> String:
  match xs:
    case Nil{}:
      ""
    case h <> Nil{}:
      Expr.show(h)
    case h <> t:
      Expr.show(h) ++ " " ++ Exprs.show(t)

@unsafe
def Expr.show(e):
  match e:
    case EVar{n}:
      n
    case ENum{n}:
      U32.show(n)
    case ENat{n}:
      U32.show(n) ++ "n"
    case EFlt{s}:
      s
    case EStr{s}:
      "\"" ++ s ++ "\""
    case ECall{f, args}:
      "(" ++ Expr.show(f) ++ " " ++ Exprs.show(args) ++ ")"
    case ECtor{n, args}:
      n ++ "{" ++ Exprs.show(args) ++ "}"
    case ELam{p, b}:
      "(\\" ++ Pat.show(p) ++ " " ++ Expr.show(b) ++ ")"
    case ELet{p, v, b}:
      "(let " ++ Pat.show(p) ++ " " ++ Expr.show(v) ++ " " ++ Expr.show(b) ++ ")"
    case EMatch{scrs, cases}:
      "(match [" ++ Exprs.show(scrs) ++ "] " ++
        Exprs.show(cases) ++ ")"
    case ECase{ps, b}:
      "(case " ++ Pats.show(ps) ++ " => " ++ Expr.show(b) ++ ")"
    case ESucc{k, x}:
      "(" ++ U32.show(k) ++ "n+ " ++ Expr.show(x) ++ ")"
    case EOp{op, a, b}:
      "(" ++ op ++ " " ++ Expr.show(a) ++ " " ++ Expr.show(b) ++ ")"
    case EAnn{x, t}:
      "(: " ++ Expr.show(x) ++ " " ++ t ++ ")"
    case ETy{n, targs}:
      "#" ++ n
    case EErr{m}:
      "(ERR " ++ m ++ ")"

def Params.show(xs: List<&2, Param>) -> String:
  match xs:
    case Nil{}:
      ""
    case h <> t:
      Param.show(h) ++ " " ++ Params.show(t)

def Ctors.show(xs: List<&2, Ctor>) -> String:
  match xs:
    case Nil{}:
      ""
    case h <> t:
      Ctor.show(h) ++ " " ++ Ctors.show(t)

@unsafe
def Decl.show(d: Decl) -> String:
  match d:
    case DDef{n, ps, b, r}:
      "def " ++ n ++ "(" ++ Params.show(ps) ++ ") = " ++ Expr.show(b)
    case DEff{n, ps, ims}:
      "eff " ++ n ++ "(" ++ Params.show(ps) ++ ")"
    case DLaw{n, ps}:
      "law " ++ n ++ "(" ++ Params.show(ps) ++ ")"
    case DType{n, tps, cs}:
      "type " ++ n ++ " " ++ Ctors.show(cs)
    case DImport{p, a}:
      "import " ++ p ++ " as " ++ a

def Decls.show.go(xs: List<&2, Decl>) -> String:
  match xs:
    case Nil{}:
      ""
    case h <> t:
      Decl.show(h) ++ "\n" ++ Decls.show.go(t)

def Decls.show(ds: List<&2, Decl>) -> String:
  Decls.show.go(ds)

# Operator resolution
# ===================

def R.opname.go(k: Nat) -> String:
  match k:
    case 0n:
      "add"
    case 1n:
      "sub"
    case 2n:
      "mul"
    case 3n:
      "div"
    case 4n:
      "mod"
    case 5n:
      "is_lt"
    case 6n:
      "is_le"
    case 7n:
      "is_gt"
    case 8n:
      "is_ge"
    case 9n:
      "and"
    case 10n:
      "or"
    case 11n:
      "xor"
    case 12n:
      "shln"
    case 13n:
      "shrn"
    case 14n+p:
      "?"

# '(a + b : T)' calls T.add; operators with no annotation belong to Nat.
def R.opname(+op: String) -> String:
  R.opname.go(P.which(op, ["+", "-", "*", "/", "%", "<", "<=", ">", ">=", ".&.",
    ".|.", ".^.", "<<", ">>"]))

law R.ops:
  for e: Expr
  for +ty: String
  Expr

@unsafe
def R.opss(xs: List<&2, Expr>, +ty: String) -> List<&2, Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> t:
      R.ops(h, ty) <> R.opss(t, ty)

@unsafe
def R.ops(e, ty):
  match e:
    case EOp{op, a, b}:
      ECall{EVar{ty ++ "." ++ R.opname(op)}, [R.ops(a, ty), R.ops(b, ty)]}
    case EAnn{x, +t}:
      R.ops(x, Bool.pick(String, String.is_empty(t), ty, t))
    case ECall{f, args}:
      ECall{R.ops(f, ty), R.opss(args, ty)}
    case ECtor{n, args}:
      ECtor{n, R.opss(args, ty)}
    case ELam{p, b}:
      ELam{p, R.ops(b, ty)}
    case ELet{p, v, b}:
      ELet{p, R.ops(v, ty), R.ops(b, ty)}
    case EMatch{scrs, cases}:
      EMatch{R.opss(scrs, ty), R.opss(cases, ty)}
    case ECase{ps, b}:
      ECase{ps, R.ops(b, ty)}
    case ESucc{k, x}:
      ESucc{k, R.ops(x, ty)}
    case other:
      other

# Free variables
# ==============

def FV.var(+x: String, +bound: List<&2, String>, +acc: List<&2, String>) ->
  List<&2, String>:
  Bool.pick(List<&2, String>, Bool.or(Str.has(bound, x), Str.has(acc, x)), acc,
    x <> acc)

law Pat.vars:
  for p: Pat
  for acc: List<&2, String>
  List<&2, String>

@unsafe
def Pats.vars(ps: List<&2, Pat>, acc: List<&2, String>) -> List<&2, String>:
  match ps:
    case Nil{}:
      acc
    case h <> t:
      Pats.vars(t, Pat.vars(h, acc))

@unsafe
def Pat.vars(p, acc):
  match p:
    case PVar{x}:
      x <> acc
    case PCtor{n, args}:
      Pats.vars(args, acc)
    case PSucc{k, q}:
      Pat.vars(q, acc)
    case other:
      acc

law FV.expr:
  for e: Expr
  for +bound: List<&2, String>
  for acc: List<&2, String>
  List<&2, String>

@unsafe
def FV.exprs(xs: List<&2, Expr>, +bound: List<&2, String>, acc: List<&2, String>) ->
  List<&2, String>:
  match xs:
    case Nil{}:
      acc
    case h <> t:
      FV.exprs(t, bound, FV.expr(h, bound, acc))

@unsafe
def FV.expr(e, bound, acc):
  match e:
    case EVar{x}:
      FV.var(x, bound, acc)
    case ECall{f, args}:
      FV.exprs(args, bound, FV.expr(f, bound, acc))
    case ECtor{n, args}:
      FV.exprs(args, bound, acc)
    case ELam{p, b}:
      FV.expr(b, Pat.vars(p, bound), acc)
    case ELet{p, v, b}:
      FV.expr(b, Pat.vars(p, bound), FV.expr(v, bound, acc))
    case EMatch{scrs, cases}:
      FV.exprs(cases, bound, FV.exprs(scrs, bound, acc))
    case ECase{ps, b}:
      FV.expr(b, Pats.vars(ps, bound), acc)
    case ESucc{k, x}:
      FV.expr(x, bound, acc)
    case EOp{op, a, b}:
      FV.expr(b, bound, FV.expr(a, bound, acc))
    case EAnn{x, t}:
      FV.expr(x, bound, acc)
    case other:
      acc

# Global tables
# =============

# kind: 0 node, 1 nullary, 2 newtype, 3 Nat zero, 4 Nat succ
type CInfo is Data:
  CInfo{tag: U32, arity: U32, kind: U32, single: Bool}

# kind: 0 def, 1 effect, 2 native, 3 dead (types, laws, type-level)
# mask: one flag per parameter, True when kept at runtime.
type DInfo is Data:
  DInfo{kind: U32, mask: List<&2, Bool>}

type G is Data:
  G{ctors: Map<&2, CInfo>, defs: Map<&2, DInfo>, bodies: Map<&2, Decl>}

def G.opt_ctors(m: Map<&2, CInfo>) -> Map<&2, Maybe<&2, CInfo>>:
  match m:
    case MTip{}:
      MTip{}
    case MLeaf{k, v}:
      MLeaf{k, Some{v}}
    case MNode{p, lo, hi}:
      MNode{p, G.opt_ctors(lo), G.opt_ctors(hi)}

def G.ctor(+g: G, +name: String) -> Maybe<&2, CInfo>:
  G{ctors, defs, bodies} = g
  Pair.snd(Map<&2, Maybe<&2, CInfo>>, Maybe<&2, CInfo>,
    Map.get(Maybe<&2, CInfo>, None{}, G.opt_ctors(ctors), name))

def G.get(-V: Data, +d: V, +m: Map<&2, V>, +key: String) -> V:
  Pair.snd(Map<&2, V>, V, Map.get(V, d, m, key))

def G.def(+g: G, +name: String) -> DInfo:
  G{ctors, defs, bodies} = g
  G.get(DInfo, DInfo{99, Nil{}}, defs, name)

def G.body(+g: G, +name: String) -> Decl:
  G{ctors, defs, bodies} = g
  G.get(Decl, DImport{"", ""}, bodies, name)

def Natives() -> List<&2, String>:
  ["U32.inc", "U32.add", "U32.sub", "U32.mul", "U32.div", "U32.mod", "U32.not",
   "U32.and", "U32.or", "U32.xor", "U32.shl", "U32.shr", "U32.shln", "U32.shrn",
   "U32.cmp", "U32.is_eq", "U32.is_ne", "U32.is_lt", "U32.is_le", "U32.is_gt",
   "U32.is_ge", "U32.is_zero", "U32.is_even", "U32.to_nat", "U32.from_nat",
   "U32.min", "U32.max", "U32.pow", "U32.log2", "U32.to_f32",
   "Nat.double", "Nat.add", "Nat.sub", "Nat.mul", "Nat.divmod", "Nat.div",
   "Nat.mod", "Nat.cmp", "Nat.is_eq", "Nat.is_ne", "Nat.is_lt", "Nat.is_le",
   "Nat.is_gt", "Nat.is_ge", "Nat.min", "Nat.max", "Nat.pow", "Nat.show",
   "F32.add", "F32.sub", "F32.mul", "F32.div", "F32.mod", "F32.pow", "F32.atan2",
   "F32.is_eq", "F32.is_ne", "F32.is_lt", "F32.is_le", "F32.is_gt", "F32.is_ge",
   "F32.neg", "F32.abs", "F32.sqrt", "F32.exp", "F32.log", "F32.log2",
   "F32.log10", "F32.sin", "F32.cos", "F32.tan", "F32.asin", "F32.acos",
   "F32.atan", "F32.sinh", "F32.cosh", "F32.tanh", "F32.floor", "F32.ceil",
   "F32.trunc", "F32.bits", "F32.to_u32", "F32.show", "F32.read"]

def G.is_native(+name: String) -> Bool:
  Str.has(Natives(), name)

def G.erased_ty(+t: String) -> Bool:
  Str.has(["Type", "Data", "Quant", "Kind"], t)

def G.keep(p: Param) -> Bool:
  Param{n, +m, +t} = p
  Bool.not(Bool.or(Bool.or(U32.is_eq(m, 1), U32.is_eq(m, 4)), G.erased_ty(t)))

def G.mask(ps: List<&2, Param>) -> List<&2, Bool>:
  match ps:
    case Nil{}:
      Nil{}
    case h <> t:
      G.keep(h) <> G.mask(t)

def G.ctor_kind(+tname: String, +name: String, +n: U32, +ar: U32) -> U32:
  Bool.pick(U32, Str.eq(tname, "Nat"), Bool.pick(U32, Str.eq(name, "Zero"), 3, 4),
    Bool.pick(U32, Bool.and(U32.is_eq(n, 1), U32.is_eq(ar, 1)), 2,
      Bool.pick(U32, U32.is_zero(ar), 1, 0)))

# Constructors of a type.
def G.ctors(
  +tname: String, cs: List<&2, Ctor>, +i: U32, +n: U32, m: Map<&2, CInfo>
) -> Map<&2, CInfo>:
  match cs:
    case Nil{}:
      m
    case Ctor{+name, fields} <> t:
      +ar = U32.from_nat(List.length(&2, Field, fields))
      G.ctors(tname, t, U32.inc(i), n, Map.set(&2, CInfo, m, name,
        CInfo{i, ar, G.ctor_kind(tname, name, n, ar), U32.is_eq(n, 1)}))

def G.laws(ds: List<&2, Decl>, m: Map<&2, List<&2, Param>>) ->
  Map<&2, List<&2, Param>>:
  match ds:
    case Nil{}:
      m
    case DLaw{name, ps} <> t:
      G.laws(t, Map.set(&2, List<&2, Param>, m, name, ps))
    case d <> t:
      G.laws(t, m)

def G.params.go(lps: List<&2, Param>, ps: List<&2, Param>) -> List<&2, Param>:
  match lps:
    case Nil{}:
      ps
    case h <> t:
      h <> t

# Parameter modes of a def come from its law when it fills one.
def G.params(+laws: Map<&2, List<&2, Param>>, +name: String, ps: List<&2, Param>) ->
  List<&2, Param>:
  G.params.go(G.get(List<&2, Param>, Nil{}, laws, name), ps)

def G.add.type(+name: String, ps: List<&2, String>, +cs: List<&2, Ctor>, g: G) -> G:
  G{ctors, defs, bodies} = g
  +n = U32.from_nat(List.length(&2, Ctor, cs))
  G{G.ctors(name, cs, 0, n, ctors), Map.set(&2, DInfo, defs, name,
    DInfo{3, Nil{}}), Map.set(&2, Decl, bodies, "%" ++ name, DType{name, ps, cs})}

def G.add.law(+name: String, ps: List<&2, Param>, g: G) -> G:
  G{ctors, defs, bodies} = g
  G{ctors, Map.set(&2, DInfo, defs, name,
    DInfo{Bool.pick(U32, G.is_native(name), 2, 3), G.mask(ps)}), bodies}

def G.add.def(
  +name: String, +ps: List<&2, Param>, body: Expr, ret: Expr,
  +laws: Map<&2, List<&2, Param>>, g: G
) -> G:
  G{ctors, defs, bodies} = g
  G{ctors, Map.set(&2, DInfo, defs, name,
    DInfo{Bool.pick(U32, G.is_native(name), 2, 0),
      G.mask(G.params(laws, name, ps))}),
    Map.set(&2, Decl, bodies, name, DDef{name, ps, body, ret})}

def G.add.eff(+name: String, +ps: List<&2, Param>, ims: List<&2, String>, g: G) -> G:
  G{ctors, defs, bodies} = g
  G{ctors, Map.set(&2, DInfo, defs, name, DInfo{1, G.mask(ps)}),
    Map.set(&2, Decl, bodies, name, DEff{name, ps, ims})}

def G.add(d: Decl, +laws: Map<&2, List<&2, Param>>, g: G) -> G:
  match d:
    case DType{name, ps, cs}:
      G.add.type(name, ps, cs, g)
    case DLaw{name, ps}:
      G.add.law(name, ps, g)
    case DDef{name, ps, body, ret}:
      G.add.def(name, ps, body, ret, laws, g)
    case DEff{name, ps, ims}:
      G.add.eff(name, ps, ims, g)
    case DImport{p, a}:
      g

def G.build(
  ds: List<&2, Decl>, +laws: Map<&2, List<&2, Param>>, g: G
) -> G:
  match ds:
    case Nil{}:
      g
    case d <> t:
      G.build(t, laws, G.add(d, laws, g))

def G.new(+ds: List<&2, Decl>) -> G:
  G.build(ds, G.laws(ds, MTip{}), G{MTip{}, MTip{}, MTip{}})

def DInfo.mask(i: DInfo) -> List<&2, Bool>:
  DInfo{kind, mask} = i
  mask

# Code generation
# ===============

def Gen.mangle.chr(+x: U32) -> String:
  Bool.pick(String, U32.is_eq(x, 46), "_d",
    Bool.pick(String, U32.is_eq(x, 95), "__",
      Bool.pick(String, Bool.or(Char.is_alpha(Chr{x}), Char.is_digit(Chr{x})),
        Str.chr(x), "_x" ++ U32.show(x))))

def Gen.mangle(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{Chr{x}, t}:
      Gen.mangle.chr(x) ++ Gen.mangle(t)

def Gen.f(name: String) -> String:
  "F_" ++ Gen.mangle(name)

def Gen.w(name: String) -> String:
  "W_" ++ Gen.mangle(name)

def Gen.host.chr(+x: U32) -> String:
  Bool.pick(String, U32.is_eq(x, 46), "_", Str.chr(x))

def Gen.host(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{Chr{x}, t}:
      Gen.host.chr(x) ++ Gen.host(t)

# Octal escape of one byte.
def Gen.oct(+b: U32) -> String:
  "\\" ++ Str.chr((48 + ((b >> 6n : U32) .&. 7 : U32) : U32)) ++
    Str.chr((48 + ((b >> 3n : U32) .&. 7 : U32) : U32)) ++
    Str.chr((48 + (b .&. 7 : U32) : U32))

def Gen.utf8(+x: U32) -> String:
  Bool.pick(String, U32.is_lt(x, 128), Gen.oct(x),
    Bool.pick(String, U32.is_lt(x, 2048),
      Gen.oct((192 .|. (x >> 6n : U32) : U32)) ++ Gen.oct((128 .|. (x .&. 63 : U32) : U32)),
      Bool.pick(String, U32.is_lt(x, 65536),
        Gen.oct((224 .|. (x >> 12n : U32) : U32)) ++
        Gen.oct((128 .|. ((x >> 6n : U32) .&. 63 : U32) : U32)) ++
        Gen.oct((128 .|. (x .&. 63 : U32) : U32)),
        Gen.oct((240 .|. (x >> 18n : U32) : U32)) ++
        Gen.oct((128 .|. ((x >> 12n : U32) .&. 63 : U32) : U32)) ++
        Gen.oct((128 .|. ((x >> 6n : U32) .&. 63 : U32) : U32)) ++
        Gen.oct((128 .|. (x .&. 63 : U32) : U32)))))

# A code point as C string-literal text (UTF-8, escaped).
def Gen.lit_chr(+x: U32) -> String:
  Bool.pick(String, Bool.and(Bool.and(U32.is_ge(x, 32), U32.is_lt(x, 127)),
    Bool.not(Str.has(["\"", "\\", "?"], Str.chr(x)))), Str.chr(x),
    Gen.utf8(x))

def Gen.lit(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{Chr{x}, t}:
      Gen.lit_chr(x) ++ Gen.lit(t)

type Bind is Data:
  Bind{name: String, c: String}

type St is Data:
  St{n: U32, protos: Doc, code: Doc, refs: List<&2, String>, errs: List<&2, String>,
    memo: List<&2, Bind>, effs: List<&2, String>}

def Gen(-A: Type) -> Type:
  St -> A & St

def Gen.go(-A: Type, -B: Type, r: A & St, f: A -> Gen(B)) -> B & St:
  (a, st) = r
  f(a, st)

def Gen.bind(-A: Type, -B: Type, m: Gen(A), f: A -> Gen(B)) -> Gen(B):
  st => Gen.go(A, B, m(st), f)

def Gen.pure(-A: Type, x: A) -> Gen(A):
  st => (x, st)

def Gen.fresh.go(st: St) -> U32 & St:
  St{+n, protos, code, refs, errs, memo, effs} = st
  (n, St{U32.inc(n), protos, code, refs, errs, memo, effs})

# A fresh number.
def Gen.fresh() -> Gen(U32):
  st => Gen.fresh.go(st)

def Gen.code.go(d: Doc, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, DCat{code, d}, refs, errs, memo, effs})

# Appends a top-level C definition.
def Gen.code(d: Doc) -> Gen(Unit):
  st => Gen.code.go(d, st)

def Gen.proto.go(d: Doc, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, DCat{protos, d}, code, refs, errs, memo, effs})

# Appends a prototype.
def Gen.proto(d: Doc) -> Gen(Unit):
  st => Gen.proto.go(d, st)

def Gen.ref.go(name: String, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, name <> refs, errs, memo, effs})

# Records a reference to a global def.
def Gen.ref(name: String) -> Gen(Unit):
  st => Gen.ref.go(name, st)

def Gen.take_refs.go(st: St) -> List<&2, String> & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (refs, St{n, protos, code, Nil{}, errs, memo, effs})

def Gen.take_refs() -> Gen(List<&2, String>):
  st => Gen.take_refs.go(st)

def Gen.error.go(msg: String, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, msg <> errs, memo, effs})

def Gen.error(msg: String) -> Gen(Unit):
  st => Gen.error.go(msg, st)

def Env() -> Data:
  List<&2, Bind>

# Joins C expressions with commas.
def Gen.commas(xs: List<&2, Doc>) -> Doc:
  Doc.sep(xs, ", ")

def Gen.len(xs: List<&2, Doc>) -> U32:
  U32.from_nat(List.length(&2, Doc, xs))

# Applies a closure to extra arguments.
def Gen.apply(xs: List<&2, Doc>, f: Doc) -> Doc:
  match xs:
    case Nil{}:
      f
    case h <> t:
      Gen.apply(t, Doc.list([DStr{"apply("}, f, DStr{", "}, h, DStr{")"}]))

# An array literal of arguments, or 0 when empty.
def Gen.arr(xs: List<&2, Doc>) -> Doc:
  match xs:
    case Nil{}:
      DStr{"0"}
    case h <> t:
      Doc.list([DStr{"(V[]){"}, Gen.commas(h <> t), DStr{"}"}])

type Tgt is Data:
  TRet{}
  TSet{v: String}

type Self is Data:
  Self{name: String, mask: List<&2, Bool>, cps: List<&2, String>}

def Self.none() -> Self:
  Self{"", Nil{}, Nil{}}

def Gen.ret(t: Tgt, d: Doc) -> Doc:
  match t:
    case TRet{}:
      Doc.list([DStr{"return "}, d, DStr{";\n"}])
    case TSet{v}:
      Doc.list([DStr{v}, DStr{" = "}, d, DStr{";\n"}])

# A pattern against a C path yields tests and bindings.
type PatR is Data:
  PatR{conds: List<&2, String>, binds: Env()}

def Gen.pat.var(+x: String, path: String, r: PatR) -> PatR:
  PatR{conds, +binds} = r
  PatR{conds, Bool.pick(Env(), Str.eq(x, "_"), binds, Bind{x, path} <> binds)}

def Gen.pat.cond(c: String, r: PatR) -> PatR:
  PatR{conds, binds} = r
  PatR{c <> conds, binds}

def Gen.pat.tag(single: Bool, c: String, r: PatR) -> PatR:
  match single:
    case True{}:
      r
    case False{}:
      Gen.pat.cond(c, r)

def Gen.and(cs: List<&2, String>) -> String:
  match cs:
    case Nil{}:
      "1"
    case h <> Nil{}:
      h
    case h <> t:
      h ++ " && " ++ Gen.and(t)

law Env.find:
  for env: Env()
  for +x: String
  Maybe<&2, String>

@unsafe
def Env.find.if(c: String, t: Env(), +x: String, hit: Bool) -> Maybe<&2, String>:
  match hit:
    case True{}:
      Some{c}
    case False{}:
      Env.find(t, x)

@unsafe
def Env.find(env, x):
  match env:
    case Nil{}:
      None{}
    case Bind{+n, c} <> t:
      Env.find.if(c, t, x, String.eq(n, x))

def Env.has(+env: Env(), +x: String) -> Bool:
  Maybe.is_some(&2, String, Env.find(env, x))

law Gen.pat:
  for +g: G
  for p: Pat
  for +path: String
  for r: PatR
  PatR

# Field i of a node at path (99: the value itself, for newtypes).
@unsafe
def Gen.pat.fields(
  +g: G, args: List<&2, Pat>, +path: String, +i: U32, r: PatR
) -> PatR:
  match args:
    case Nil{}:
      r
    case h <> t:
      Gen.pat.fields(g, t, path, U32.inc(i), Gen.pat(g, h,
        Bool.pick(String, U32.is_eq(i, 99), path,
          "FLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), r))

@unsafe
def Gen.pat.kind(
  +g: G, kind: Nat, +tag: U32, +single: Bool, args: List<&2, Pat>,
  +path: String, r: PatR
) -> PatR:
  match kind:
    case 0n:
      Gen.pat.fields(g, args, path, 0, Gen.pat.tag(single,
        "TAG(" ++ path ++ ") == " ++ U32.show(tag), r))
    case 1n:
      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
    case 2n:
      Gen.pat.fields(g, args, path, 99, r)
    case 3n:
      Gen.pat.cond("(" ++ path ++ ") == 0", r)
    case 4n+p:
      Gen.pat.fields(g, args, "nat_subk(" ++ path ++ ", 1)", 99,
        Gen.pat.cond("(" ++ path ++ ") != 0", r))

@unsafe
def Gen.pat.ctor(
  +g: G, info: Maybe<&2, CInfo>, name: String, args: List<&2, Pat>,
  +path: String, r: PatR
) -> PatR:
  match info:
    case None{}:
      Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
    case Some{CInfo{+tag, ar, +kind, +single}}:
      Gen.pat.kind(g, U32.to_nat(kind), tag, single, args, path, r)

@unsafe
def Gen.pat(g, p, path, r):
  match p:
    case PVar{x}:
      Gen.pat.var(x, path, r)
    case PCtor{+name, args}:
      Gen.pat.ctor(g, G.ctor(g, name), name, args, path, r)
    case PNat{n}:
      Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
    case PSucc{+k, q}:
      Gen.pat(g, q, "nat_subk(" ++ path ++ ", " ++ U32.show(k) ++ ")",
        Gen.pat.cond("nat_ge(" ++ path ++ ", " ++ U32.show(k) ++ ")", r))
    case PNum{n}:
      Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)

def Gen.pats(+g: G, ps: List<&2, Pat>, paths: List<&2, String>, r: PatR) -> PatR:
  match ps paths:
    case p <> pt c <> ct:
      Gen.pats(g, pt, ct, Gen.pat(g, p, c, r))
    case pl cl:
      r

# String literals are built once and cached.
def Gen.str(s: String) -> Gen(Doc):
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    +name : String <- Gen.pure(String, "S" ++ U32.show(k))
    Gen.proto(DStr{"static V " ++ name ++ "(void);\n"})
    Gen.code(DStr{"static V " ++ name ++ "(void) { static V c; return STRC(c, \"" ++
      Gen.lit(s) ++ "\"); }\n"})
    return DStr{name ++ "()"}

def Gen.clo.go(+name: String, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, memo, ("%clo\t" ++ name) <> effs})

# Records a def the CPU makes a closure of (the device gets code for it).
def Gen.clo(+name: String) -> Gen(Unit):
  st => Gen.clo.go(name, st)

def Gen.var.kind(+name: String, kind: Nat, +total: U32) -> Gen(Doc):
  match kind:
    case 3n:
      Gen.pure(Doc, DStr{"0"})
    case 99n:
      do Gen<Doc>:
        Gen.error("unknown name: " ++ name)
        return DStr{"0"}
    case other:
      do Gen<Doc>:
        Gen.ref(name)
        Gen.clo(name)
        return Bool.pick(Doc, U32.is_zero(total), DStr{Gen.f(name) ++ "()"},
          DStr{"mk_clo(" ++ Gen.w(name) ++ ", " ++ U32.show(total) ++ ", 0, 0)"})

def Gen.var.def(+name: String, info: DInfo) -> Gen(Doc):
  DInfo{+kind, +mask} = info
  Gen.var.kind(name, U32.to_nat(kind), U32.from_nat(List.length(&2, Bool, mask)))

def Gen.var.global(+g: G, +name: String, hole: Bool) -> Gen(Doc):
  match hole:
    case True{}:
      Gen.pure(Doc, DStr{"0"})
    case False{}:
      Gen.var.def(name, G.def(g, name))

def Gen.var.found(+g: G, +name: String, m: Maybe<&2, String>) -> Gen(Doc):
  match m:
    case Some{c}:
      Gen.pure(Doc, DStr{c})
    case None{}:
      Gen.var.global(g, name, Str.eq(name, "_"))

def Gen.var(+g: G, +env: Env(), +name: String) -> Gen(Doc):
  Gen.var.found(g, name, Env.find(env, name))

# Splits call arguments against a parameter mask.
type Split is Data:
  Split{kept: List<&2, Expr>, all: List<&2, Expr>, extra: List<&2, Expr>, full: Bool}

def Gen.split(mask: List<&2, Bool>, args: List<&2, Expr>, r: Split) -> Split:
  match mask args:
    case Nil{} xs:
      Split{kept, all, extra, full} = r
      Split{kept, all, xs, True{}}
    case m <> mt Nil{}:
      Split{kept, all, extra, full} = r
      Split{kept, all, Nil{}, False{}}
    case True{} <> mt +a <> at:
      Split{kept, all, extra, full} = r
      Gen.split(mt, at, Split{List.append(&2, Expr, kept, [a]),
        List.append(&2, Expr, all, [a]), extra, full})
    case False{} <> mt a <> at:
      Split{kept, all, extra, full} = r
      Gen.split(mt, at, Split{kept, List.append(&2, Expr, all, [ETy{"", Nil{}}]), extra, full})

def Gen.ctor.node(+tag: U32, +ds: List<&2, Doc>) -> Doc:
  +n = Gen.len(ds)
  Bool.pick(Doc, U32.is_le(n, 4),
    Doc.list([DStr{"C" ++ U32.show(n) ++ "(" ++ U32.show(tag) ++ ", "}, Gen.commas(ds),
      DStr{")"}]),
    Doc.list([DStr{"CN(" ++ U32.show(tag) ++ ", " ++ U32.show(n) ++ ", "},
      Gen.arr(ds), DStr{")"}]))

def Gen.ctor.kind(+tag: U32, kind: Nat, ds: List<&2, Doc>) -> Doc:
  match kind:
    case 0n:
      Gen.ctor.node(tag, ds)
    case 1n:
      DStr{"IMM(" ++ U32.show(tag) ++ ")"}
    case 2n:
      Doc.list(ds)
    case 3n:
      DStr{"0"}
    case 4n+p:
      Doc.list([DStr{"nat_addk("}, Doc.list(ds), DStr{", 1)"}])

def Gen.caps.put(x: String, m: Maybe<&2, String>, rest: Env()) -> Env():
  match m:
    case None{}:
      rest
    case Some{c}:
      Bind{x, c} <> rest

# Captured variables of a lambda: (name, outer C expression) pairs.
def Gen.caps(names: List<&2, String>, +env: Env()) -> Env():
  match names:
    case Nil{}:
      Nil{}
    case +x <> t:
      Gen.caps.put(x, Env.find(env, x), Gen.caps(t, env))

# Inner environment: capture i lives at a[i].
def Gen.caps.inner(caps: Env(), +i: U32) -> Env():
  match caps:
    case Nil{}:
      Nil{}
    case Bind{x, c} <> t:
      Bind{x, "a[" ++ U32.show(i) ++ "]"} <> Gen.caps.inner(t, U32.inc(i))

def Gen.caps.outer(caps: Env()) -> List<&2, Doc>:
  match caps:
    case Nil{}:
      Nil{}
    case Bind{x, c} <> t:
      DStr{c} <> Gen.caps.outer(t)

def Gen.scrs.put(+c: String, d: Doc, r: List<&2, String> & Doc) ->
  List<&2, String> & Doc:
  (cs, code) = r
  (c <> cs, Doc.list([DStr{"V " ++ c ++ " = "}, d, DStr{";\n"}, code]))

# Self tail call: rebinds the parameters and jumps back to the top.
def Gen.tail.assign(cps: List<&2, String>, +i: U32) -> Doc:
  match cps:
    case Nil{}:
      DNil{}
    case c <> t:
      Doc.list([DStr{c ++ " = t" ++ U32.show(i) ++ "; "}, Gen.tail.assign(t, U32.inc(i))])

def Gen.tail.temps(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"V t" ++ U32.show(i) ++ " = "}, d, DStr{"; "},
        Gen.tail.temps(t, U32.inc(i))])

def Gen.is_ret(t: Tgt) -> Bool:
  match t:
    case TRet{}:
      True{}
    case TSet{v}:
      False{}

def Gen.is_tail(+env: Env(), +self: Self, +tgt: Tgt, +name: String, +args: List<&2, Expr>) ->
  Bool:
  Self{+sn, +mask, cps} = self
  Bool.and(Bool.and(Gen.is_ret(tgt), Str.eq(sn, name)), Bool.and(
    Bool.not(Env.has(env, name)),
    Nat.is_eq(List.length(&2, Bool, mask), List.length(&2, Expr, args))))

law Gen.lam:
  for +g: G
  for +env: Env()
  for +p: Pat
  for +body: Expr
  Gen(Doc)

law Gen.let:
  for +g: G
  for +env: Env()
  for +self: Self
  for +tgt: Tgt
  for p: Pat
  for v: Expr
  for body: Expr
  Gen(Doc)

law Gen.call:
  for +g: G
  for +env: Env()
  for f: Expr
  for args: List<&2, Expr>
  Gen(Doc)

law Gen.ctor:
  for +g: G
  for +env: Env()
  for +name: String
  for args: List<&2, Expr>
  Gen(Doc)

law Gen.expr:
  for +g: G
  for +env: Env()
  for e: Expr
  Gen(Doc)

@unsafe
def Gen.exprs(+g: G, +env: Env(), xs: List<&2, Expr>) -> Gen(List<&2, Doc>):
  match xs:
    case Nil{}:
      Gen.pure(List<&2, Doc>, Nil{})
    case h <> t:
      do Gen<List<&2, Doc>>:
        d : Doc <- Gen.expr(g, env, h)
        ds : List<&2, Doc> <- Gen.exprs(g, env, t)
        return d <> ds

def Gen.call.full(
  +g: G, +env: Env(), +name: String, +mask: List<&2, Bool>, kept: List<&2, Expr>,
  all: List<&2, Expr>, extra: List<&2, Expr>, full: Bool
) -> Gen(Doc):
  match full:
    case True{}:
      do Gen<Doc>:
        ks : List<&2, Doc> <- Gen.exprs(g, env, kept)
        xs : List<&2, Doc> <- Gen.exprs(g, env, extra)
        return Gen.apply(xs, Doc.list([DStr{Gen.f(name) ++ "("}, Gen.commas(ks), DStr{")"}]))
    case False{}:
      do Gen<Doc>:
        Gen.clo(name)
        +as : List<&2, Doc> <- Gen.exprs(g, env, all)
        return Doc.list([DStr{"mk_clo(" ++ Gen.w(name) ++ ", " ++
          U32.show(U32.from_nat(List.length(&2, Bool, mask))) ++ ", " ++
          U32.show(Gen.len(as)) ++ ", "}, Gen.arr(as), DStr{")"}])

@unsafe
def Gen.call.split(+g: G, +env: Env(), +name: String, +mask: List<&2, Bool>, s: Split) ->
  Gen(Doc):
  Split{kept, all, extra, full} = s
  Gen.call.full(g, env, name, mask, kept, all, extra, full)

@unsafe
def Gen.call.kind(
  +g: G, +env: Env(), +name: String, kind: Nat, +mask: List<&2, Bool>, s: Split
) -> Gen(Doc):
  match kind:
    case 3n:
      Gen.pure(Doc, DStr{"0"})
    case 99n:
      do Gen<Doc>:
        Gen.error("unknown function: " ++ name)
        return DStr{"0"}
    case other:
      do Gen<Doc>:
        Gen.ref(name)
        Gen.call.split(g, env, name, mask, s)

@unsafe
def Gen.call.def(+g: G, +env: Env(), +name: String, info: DInfo, args: List<&2, Expr>) ->
  Gen(Doc):
  DInfo{kind, +mask} = info
  Gen.call.kind(g, env, name, U32.to_nat(kind), mask,
    Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}))

@unsafe
def Gen.call.local(+g: G, +env: Env(), f: Expr, args: List<&2, Expr>) -> Gen(Doc):
  do Gen<Doc>:
    fd : Doc <- Gen.expr(g, env, f)
    xs : List<&2, Doc> <- Gen.exprs(g, env, args)
    return Gen.apply(xs, fd)

@unsafe
def Gen.call.var(+g: G, +env: Env(), +name: String, args: List<&2, Expr>, local: Bool) ->
  Gen(Doc):
  match local:
    case True{}:
      Gen.call.local(g, env, EVar{name}, args)
    case False{}:
      Gen.call.def(g, env, name, G.def(g, name), args)

def Gen.gpu.go(+name: String, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, memo, ("%gpu\t" ++ name) <> effs})

# Records a !-call target (with the effects' files, told apart by "%gpu\t").
def Gen.gpu(+name: String) -> Gen(Unit):
  st => Gen.gpu.go(name, st)

def Gen.gpu.params(n: Nat, +i: U32) -> List<&2, String>:
  match n:
    case 0n:
      Nil{}
    case 1n+m:
      ("a" ++ U32.show(i)) <> Gen.gpu.params(m, U32.inc(i))

def Gen.cparams.go(ps: List<&2, String>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case h <> t:
      ("V " ++ h) <> Gen.cparams.go(t)

def Gen.cparams(ps: List<&2, String>) -> String:
  match ps:
    case Nil{}:
      "void"
    case h <> t:
      String.join(Gen.cparams.go(h <> t), ", ")

# f!(args) with every argument of a def: G_f tries the device, then the CPU.
@unsafe
def Gen.call.gpu(+g: G, +env: Env(), +name: String, kept: List<&2, Expr>) -> Gen(Doc):
  do Gen<Doc>:
    Gen.ref(name)
    Gen.gpu(name)
    +ks : List<&2, Doc> <- Gen.exprs(g, env, kept)
    Gen.proto(DStr{"static V G_" ++ Gen.mangle(name) ++ "(" ++ Gen.cparams(Gen.gpu.params(U32.to_nat(Gen.len(ks)), 0)) ++ ");\n"})
    return Doc.list([DStr{"G_" ++ Gen.mangle(name) ++ "("}, Gen.commas(ks), DStr{")"}])

@unsafe
def Gen.call.bang.pick(
  kind: Nat, extra: List<&2, Expr>, full: Bool, +g: G, +env: Env(), +name: String, kept: List<&2, Expr>,
  args: List<&2, Expr>
) -> Gen(Doc):
  match kind extra full:
    case 0n Nil{} True{}:
      Gen.call.gpu(g, env, name, kept)
    case k e f:
      Gen.call(g, env, EVar{name}, args)

@unsafe
def Gen.call.bang.split(+g: G, +env: Env(), +name: String, kind: Nat, s: Split, args: List<&2, Expr>) -> Gen(Doc):
  Split{kept, all, extra, full} = s
  Gen.call.bang.pick(kind, extra, full, g, env, name, kept, args)

@unsafe
def Gen.call.bang.def(+g: G, +env: Env(), +name: String, info: DInfo, +args: List<&2, Expr>) -> Gen(Doc):
  DInfo{kind, +mask} = info
  Gen.call.bang.split(g, env, name, U32.to_nat(kind), Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}),
    args)

@unsafe
def Gen.call.bang.var(+g: G, +env: Env(), +name: String, args: List<&2, Expr>, local: Bool) -> Gen(Doc):
  match local:
    case True{}:
      Gen.call.local(g, env, EVar{name}, args)
    case False{}:
      Gen.call.bang.def(g, env, name, G.def(g, name), args)

# f!(args): a call the device may run (see the GPU backend below).
@unsafe
def Gen.call.bang(+g: G, +env: Env(), args: List<&2, Expr>) -> Gen(Doc):
  match args:
    case EVar{+name} <> xs:
      Gen.call.bang.var(g, env, name, xs, Env.has(env, name))
    case f <> xs:
      Gen.call(g, env, f, xs)
    case Nil{}:
      Gen.pure(Doc, DStr{"0"})

@unsafe
def Gen.call.name(+g: G, +env: Env(), +name: String, args: List<&2, Expr>, bang: Bool) -> Gen(Doc):
  match bang:
    case True{}:
      Gen.call.bang(g, env, args)
    case False{}:
      Gen.call.var(g, env, name, args, Env.has(env, name))

@unsafe
def Gen.call(g, env, f, args):
  match f:
    case EVar{+name}:
      Gen.call.name(g, env, name, args, Str.eq(name, "%gpu"))
    case other:
      Gen.call.local(g, env, other, args)

@unsafe
def Gen.ctor.info(+g: G, +env: Env(), name: String, info: Maybe<&2, CInfo>,
  args: List<&2, Expr>
) -> Gen(Doc):
  match info:
    case None{}:
      do Gen<Doc>:
        Gen.error("unknown constructor: " ++ name)
        return DStr{"0"}
    case Some{CInfo{tag, ar, kind, single}}:
      do Gen<Doc>:
        ds : List<&2, Doc> <- Gen.exprs(g, env, args)
        return Gen.ctor.kind(tag, U32.to_nat(kind), ds)

@unsafe
def Gen.ctor(g, env, name, args):
  Gen.ctor.info(g, env, name, G.ctor(g, name), args)

# Scrutinees are bound to fresh C variables.
@unsafe
def Gen.scrs(+g: G, +env: Env(), xs: List<&2, Expr>) ->
  Gen(List<&2, String> & Doc):
  match xs:
    case Nil{}:
      Gen.pure(List<&2, String> & Doc, (Nil{}, DNil{}))
    case h <> t:
      do Gen<List<&2, String> & Doc>:
        +k : U32 <- Gen.fresh()
        +c : String <- Gen.pure(String, "s" ++ U32.show(k))
        d : Doc <- Gen.expr(g, env, h)
        r : List<&2, String> & Doc <- Gen.scrs(g, env, t)
        return Gen.scrs.put(c, d, r)

def Gen.tail(+g: G, +env: Env(), cps: List<&2, String>, s: Split) -> Gen(Doc):
  Split{kept, all, extra, full} = s
  do Gen<Doc>:
    ds : List<&2, Doc> <- Gen.exprs(g, env, kept)
    return Doc.list([DStr{"{ "}, Gen.tail.temps(ds, 0), Gen.tail.assign(cps, 0),
      DStr{"goto top; }\n"}])

@unsafe
def Gen.tail.self(+g: G, +env: Env(), self: Self, args: List<&2, Expr>) -> Gen(Doc):
  Self{sn, +mask, cps} = self
  Gen.tail(g, env, cps, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}))

@unsafe
def Gen.stmt.call(
  +g: G, +env: Env(), +self: Self, +tgt: Tgt, +name: String, args: List<&2, Expr>,
  tail: Bool
) -> Gen(Doc):
  match tail:
    case True{}:
      Gen.tail.self(g, env, self, args)
    case False{}:
      do Gen<Doc>:
        d : Doc <- Gen.call(g, env, EVar{name}, args)
        return Gen.ret(tgt, d)

law Gen.stmt:
  for +g: G
  for +env: Env()
  for +self: Self
  for +tgt: Tgt
  for e: Expr
  Gen(Doc)

# A statement-level expression used as a value: ({ V r; ...; r; }).
@unsafe
def Gen.block(+g: G, +env: Env(), e: Expr) -> Gen(Doc):
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    +r : String <- Gen.pure(String, "r" ++ U32.show(k))
    b : Doc <- Gen.stmt(g, env, Self.none(), TSet{r}, e)
    return Doc.list([DStr{"({ V " ++ r ++ ";\n"}, b, DStr{r ++ "; })"}])

@unsafe
def Gen.expr(g, env, e):
  match e:
    case EVar{name}:
      Gen.var(g, env, name)
    case ENum{n}:
      Gen.pure(Doc, DStr{U32.show(n) ++ "u"})
    case ENat{n}:
      Gen.pure(Doc, DStr{U32.show(n) ++ "u"})
    case EFlt{s}:
      Gen.pure(Doc, DStr{"VF(" ++ s ++ "f)"})
    case EStr{s}:
      Gen.str(s)
    case ECall{f, args}:
      Gen.call(g, env, f, args)
    case ECtor{name, args}:
      Gen.ctor(g, env, name, args)
    case ELam{p, body}:
      Gen.lam(g, env, p, body)
    case ELet{p, v, body}:
      Gen.block(g, env, ELet{p, v, body})
    case EMatch{scrs, cases}:
      Gen.block(g, env, EMatch{scrs, cases})
    case ESucc{k, x}:
      do Gen<Doc>:
        d : Doc <- Gen.expr(g, env, x)
        return Doc.list([DStr{"nat_addk("}, d, DStr{", " ++ U32.show(k) ++ ")"}])
    case ETy{n, targs}:
      Gen.pure(Doc, DStr{"0"})
    case EErr{m}:
      do Gen<Doc>:
        Gen.error("parse error: " ++ m)
        return DStr{"0"}
    case other:
      do Gen<Doc>:
        Gen.error("unexpected expression: " ++ Expr.show(other))
        return DStr{"0"}

@unsafe
def Gen.let.var(
  +g: G, +env: Env(), +self: Self, +tgt: Tgt, +x: String, v: Expr, body: Expr,
  hole: Bool
) -> Gen(Doc):
  match hole:
    case True{}:
      do Gen<Doc>:
        d : Doc <- Gen.expr(g, env, v)
        b : Doc <- Gen.stmt(g, env, self, tgt, body)
        return Doc.list([DStr{"(void)("}, d, DStr{");\n"}, b])
    case False{}:
      do Gen<Doc>:
        +k : U32 <- Gen.fresh()
        +c : String <- Gen.pure(String, "v" ++ U32.show(k))
        d : Doc <- Gen.expr(g, env, v)
        b : Doc <- Gen.stmt(g, Bind{x, c} <> env, self, tgt, body)
        return Doc.list([DStr{"V " ++ c ++ " = "}, d, DStr{";\n"}, b])

law Gen.cases:
  for +g: G
  for +env: Env()
  for +self: Self
  for +tgt: Tgt
  for +cs: List<&2, String>
  for cases: List<&2, Expr>
  Gen(Doc)

@unsafe
def Gen.cases.next(
  +g: G, +env: Env(), +self: Self, +tgt: Tgt, +cs: List<&2, String>,
  rest: List<&2, Expr>, conds: List<&2, String>, b: Doc
) -> Gen(Doc):
  match conds:
    case Nil{}:
      Gen.pure(Doc, Doc.list([DStr{"{\n"}, b, DStr{"}\n"}]))
    case h <> t:
      do Gen<Doc>:
        more : Doc <- Gen.cases(g, env, self, tgt, cs, rest)
        return Doc.list([DStr{"if (" ++ Gen.and(h <> t) ++ ") {\n"}, b,
          DStr{"} else "}, more])

@unsafe
def Gen.match.go(
  +g: G, +env: Env(), +self: Self, +tgt: Tgt, cases: List<&2, Expr>,
  r: List<&2, String> & Doc
) -> Gen(Doc):
  (cs, decls) = r
  do Gen<Doc>:
    body : Doc <- Gen.cases(g, env, self, tgt, cs, cases)
    return Doc.list([decls, body])

@unsafe
def Gen.match(+g: G, +env: Env(), +self: Self, +tgt: Tgt, scrs: List<&2, Expr>,
  cases: List<&2, Expr>
) -> Gen(Doc):
  do Gen<Doc>:
    r : List<&2, String> & Doc <- Gen.scrs(g, env, scrs)
    Gen.match.go(g, env, self, tgt, cases, r)

@unsafe
def Gen.stmt(g, env, self, tgt, e):
  match e:
    case ELet{p, v, body}:
      Gen.let(g, env, self, tgt, p, v, body)
    case EMatch{scrs, cases}:
      Gen.match(g, env, self, tgt, scrs, cases)
    case ECall{EVar{+name}, +args}:
      Gen.stmt.call(g, env, self, tgt, name, args, Gen.is_tail(env, self, tgt, name, args))
    case other:
      do Gen<Doc>:
        d : Doc <- Gen.expr(g, env, other)
        return Gen.ret(tgt, d)

def PatR.binds(r: PatR) -> Env():
  PatR{conds, binds} = r
  binds

@unsafe
def Gen.lam(g, env, p, body):
  +caps = Gen.caps(FV.expr(body, Pat.vars(p, Nil{}), Nil{}), env)
  +n = U32.from_nat(List.length(&2, Bind, caps))
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    +name : String <- Gen.pure(String, "L" ++ U32.show(k))
    Gen.proto(DStr{"static V " ++ name ++ "(V *a);\n"})
    +binds : Env() <- Gen.pure(Env(), PatR.binds(Gen.pat(g, p, "a[" ++ U32.show(n) ++ "]",
      PatR{Nil{}, Nil{}})))
    b : Doc <- Gen.stmt(g, List.append(&2, Bind, binds, Gen.caps.inner(caps, 0)),
      Self.none(), TRet{}, body)
    Gen.code(Doc.list([DStr{"static V " ++ name ++ "(V *a) {\n"}, b, DStr{"}\n"}]))
    return Doc.list([DStr{"mk_clo(" ++ name ++ ", " ++ U32.show(U32.inc(n)) ++ ", " ++
      U32.show(n) ++ ", "}, Gen.arr(Gen.caps.outer(caps)), DStr{")"}])

@unsafe
def Gen.let.pat(+g: G, +env: Env(), +self: Self, +tgt: Tgt, +p: Pat, v: Expr, body: Expr) ->
  Gen(Doc):
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    +c : String <- Gen.pure(String, "v" ++ U32.show(k))
    d : Doc <- Gen.expr(g, env, v)
    +binds : Env() <- Gen.pure(Env(), PatR.binds(Gen.pat(g, p, c, PatR{Nil{}, Nil{}})))
    b : Doc <- Gen.stmt(g, List.append(&2, Bind, binds, env), self, tgt, body)
    return Doc.list([DStr{"V " ++ c ++ " = "}, d, DStr{";\n"}, b])

def Gen.par.name(+k: U32, +i: U32) -> String:
  "p" ++ U32.show(k) ++ "_" ++ U32.show(i)

# Binds each name of a parallel let to its value's C variable.
def Gen.par.env(ps: List<&2, Pat>, +k: U32, +i: U32, +env: Env()) -> Env():
  match ps:
    case Nil{}:
      env
    case PVar{+x} <> t:
      Gen.par.env(t, k, U32.inc(i), Bool.pick(Env(), Str.eq(x, "_"), env,
        Bind{x, Gen.par.name(k, i)} <> env))
    case other <> t:
      Gen.par.env(t, k, U32.inc(i), env)

law Gen.par.vals:
  for +g: G
  for +env: Env()
  for +k: U32
  for +i: U32
  for vs: List<&2, Expr>
  Gen(Doc)

# Forks every value but the last, evaluates the last, then joins the forks
# in reverse.
@unsafe
def Gen.par.vals(g, env, k, i, vs):
  match vs:
    case Nil{}:
      Gen.pure(Doc, DNil{})
    case v <> Nil{}:
      do Gen<Doc>:
        d : Doc <- Gen.expr(g, env, v)
        return Doc.list([DStr{"V " ++ Gen.par.name(k, i) ++ " = "}, d, DStr{";\n"}])
    case v <> t:
      do Gen<Doc>:
        c : Doc <- Gen.lam(g, env, PVar{"_"}, v)
        rest : Doc <- Gen.par.vals(g, env, k, U32.inc(i), t)
        return Doc.list([DStr{"V " ++ Gen.par.name(k, i) ++ "t = par_fork("}, c, DStr{");\n"},
          rest, DStr{"V " ++ Gen.par.name(k, i) ++ " = par_join(" ++ Gen.par.name(k, i) ++
          "t);\n"}])

@unsafe
def Gen.par(+g: G, +env: Env(), +self: Self, +tgt: Tgt, ps: List<&2, Pat>, vs: List<&2, Expr>,
  body: Expr
) -> Gen(Doc):
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    pre : Doc <- Gen.par.vals(g, env, k, 0, vs)
    b : Doc <- Gen.stmt(g, Gen.par.env(ps, k, 0, env), self, tgt, body)
    return Doc.list([pre, b])

@unsafe
def Gen.let.par(+g: G, +env: Env(), +self: Self, +tgt: Tgt, ps: List<&2, Pat>, v: Expr,
  body: Expr
) -> Gen(Doc):
  match v:
    case ECtor{n, vs}:
      Gen.par(g, env, self, tgt, ps, vs, body)
    case other:
      Gen.par(g, env, self, tgt, ps, [other], body)

@unsafe
def Gen.let.ctor(+g: G, +env: Env(), +self: Self, +tgt: Tgt, name: String, ps: List<&2, Pat>,
  v: Expr, body: Expr, par: Bool
) -> Gen(Doc):
  match par:
    case True{}:
      Gen.let.par(g, env, self, tgt, ps, v, body)
    case False{}:
      Gen.let.pat(g, env, self, tgt, PCtor{name, ps}, v, body)

@unsafe
def Gen.let(g, env, self, tgt, p, v, body):
  match p:
    case PVar{+x}:
      Gen.let.var(g, env, self, tgt, x, v, body, Str.eq(x, "_"))
    case PCtor{+name, ps}:
      Gen.let.ctor(g, env, self, tgt, name, ps, v, body, Str.eq(name, "%par"))
    case other:
      Gen.let.pat(g, env, self, tgt, other, v, body)

def PatR.conds(r: PatR) -> List<&2, String>:
  PatR{conds, binds} = r
  conds

@unsafe
def Gen.cases(g, env, self, tgt, cs, cases):
  match cases:
    case Nil{}:
      Gen.pure(Doc, DStr{"{ bend_fail(\"incomplete match\"); }\n"})
    case ECase{ps, body} <> t:
      +pr = Gen.pats(g, ps, cs, PatR{Nil{}, Nil{}})
      +conds = PatR.conds(pr)
      +binds = PatR.binds(pr)
      do Gen<Doc>:
        b : Doc <- Gen.stmt(g, List.append(&2, Bind, binds, env), self, tgt, body)
        Gen.cases.next(g, env, self, tgt, cs, t, List.reverse(&2, String, conds), b)
    case other <> t:
      Gen.cases(g, env, self, tgt, cs, t)

# C parameter list and environment of a def.
type Sig is Data:
  Sig{params: List<&2, String>, env: Env(), wargs: List<&2, String>}

def Gen.sig(ps: List<&2, Param>, mask: List<&2, Bool>, +i: U32, r: Sig) -> Sig:
  match ps mask:
    case Param{x, m, t} <> pt True{} <> mt:
      Sig{params, env, wargs} = r
      +c = "a" ++ U32.show(i)
      Gen.sig(pt, mt, U32.inc(i), Sig{List.append(&2, String, params, [c]),
        Bind{x, c} <> env, List.append(&2, String, wargs, ["a[" ++ U32.show(i) ++ "]"])})
    case Param{x, m, t} <> pt False{} <> mt:
      Sig{params, env, wargs} = r
      Gen.sig(pt, mt, U32.inc(i), Sig{params, Bind{x, "0"} <> env, wargs})
    case pl ml:
      r

def Gen.wrapper(+name: String, wargs: List<&2, String>) -> Gen(Unit):
  +w = Gen.w(name)
  do Gen<Unit>:
    Gen.proto(DStr{"static V " ++ w ++ "(V *a);\n"})
    Gen.code(DStr{"static V " ++ w ++ "(V *a) { (void)a; return " ++ Gen.f(name) ++ "(" ++
      String.join(wargs, ", ") ++ "); }\n"})

def Gen.def.body(+g: G, +name: String, +mask: List<&2, Bool>, body: Expr, sig: Sig) ->
  Gen(Unit):
  Sig{+params, env, +wargs} = sig
  +head = "static V " ++ Gen.f(name) ++ "(" ++ Gen.cparams(params) ++ ")"
  do Gen<Unit>:
    Gen.proto(DStr{head ++ ";\n"})
    b : Doc <- Gen.stmt(g, env, Self{name, mask, params}, TRet{}, R.ops(body, "Nat"))
    Gen.code(Doc.list([DStr{head ++ " {\ntop:;\n"}, b, DStr{"}\n"}]))
    Gen.wrapper(name, wargs)

def Gen.eff.args(n: Nat, +i: U32) -> List<&2, String>:
  match n:
    case 0n:
      Nil{}
    case 1n+p:
      ("a[" ++ U32.show(i) ++ "]") <> Gen.eff.args(p, U32.inc(i))

def Gen.cid(name: String) -> String:
  "CID_" ++ Gen.host(String.to_upper(name))

def Gen.effs.c.if(h: String, rest: List<&2, String>, keep: Bool) -> List<&2, String>:
  match keep:
    case True{}:
      h <> rest
    case False{}:
      rest

def Gen.effs.c(ims: List<&2, String>) -> List<&2, String>:
  match ims:
    case Nil{}:
      Nil{}
    case +h <> t:
      Gen.effs.c.if(h, Gen.effs.c(t), String.ends_with(h, ".c"))

def Gen.effs.go(ims: List<&2, String>, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, memo, List.append(&2, String, Gen.effs.c(ims), effs)})

# Records the C files a foreign def imports.
def Gen.effs(ims: List<&2, String>) -> Gen(Unit):
  st => Gen.effs.go(ims, st)

# Effects: F builds a closure R => k => {args..., k}, a request node the
# event loop answers (see io_step in bendrt.h).
def Gen.def.eff(+name: String, sig: Sig, ims: List<&2, String>) -> Gen(Unit):
  Sig{+params, env, +wargs} = sig
  +n = U32.from_nat(List.length(&2, String, params))
  +e = "E_" ++ Gen.mangle(name)
  +head = "static V " ++ Gen.f(name) ++ "(" ++ Gen.cparams(params) ++ ")"
  do Gen<Unit>:
    Gen.effs(ims)
    Gen.proto(DStr{head ++ ";\nstatic V " ++ e ++ "(V *a);\n"})
    Gen.code(DStr{"static V " ++ e ++ "(V *a) { return io_req(" ++ Gen.cid(name) ++ ", " ++
      U32.show(U32.inc(n)) ++ ", (V[]){" ++ String.join(List.append(&2, String,
        Gen.eff.args(U32.to_nat(n), 0), ["a[" ++ U32.show(U32.inc(n)) ++ "]"]), ", ") ++
      "}); }\n"})
    Gen.code(DStr{head ++ " { return mk_clo(" ++ e ++ ", " ++ U32.show((n + 2 : U32)) ++
      ", " ++ U32.show(n) ++ ", " ++ Bool.pick(String, U32.is_zero(n), "0",
        "(V[]){" ++ String.join(params, ", ") ++ "}") ++ "); }\n"})
    Gen.wrapper(name, wargs)

def Sig.wargs(s: Sig) -> List<&2, String>:
  Sig{params, env, wargs} = s
  wargs

def Gen.def.native(
  +g: G, +name: String, +mask: List<&2, Bool>, body: Expr, sig: Sig, native: Bool
) -> Gen(Unit):
  match native:
    case True{}:
      Gen.wrapper(name, Sig.wargs(sig))
    case False{}:
      Gen.def.body(g, name, mask, body, sig)

def Gen.dummy_params(mask: List<&2, Bool>) -> List<&2, Param>:
  match mask:
    case Nil{}:
      Nil{}
    case h <> t:
      Param{"_", 0, ""} <> Gen.dummy_params(t)

# A law with no def: natives get a wrapper; others are dead.
def Gen.def.law(+name: String, +mask: List<&2, Bool>, native: Bool) -> Gen(Unit):
  match native:
    case True{}:
      Gen.wrapper(name, Sig.wargs(Gen.sig(Gen.dummy_params(mask), mask, 0,
        Sig{Nil{}, Nil{}, Nil{}})))
    case False{}:
      Gen.pure(Unit, Unit{})

def Gen.def.decl(+g: G, +name: String, +info: DInfo, d: Decl) -> Gen(Unit):
  DInfo{+kind, +mask} = info
  match d:
    case DDef{n, ps, body, ret}:
      Gen.def.native(g, name, mask, body, Gen.sig(ps, mask, 0, Sig{Nil{}, Nil{}, Nil{}}),
        U32.is_eq(kind, 2))
    case DEff{n, ps, ims}:
      Gen.def.eff(name, Gen.sig(ps, mask, 0, Sig{Nil{}, Nil{}, Nil{}}), ims)
    case other:
      Gen.def.law(name, mask, U32.is_eq(kind, 2))

def Gen.def(+g: G, +name: String) -> Gen(Unit):
  Gen.def.decl(g, name, G.def(g, name), G.body(g, name))

def Gen.dedup(xs: List<&2, String>, +acc: List<&2, String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      List.reverse(&2, String, acc)
    case +h <> t:
      Gen.dedup(t, Bool.pick(List<&2, String>, Str.has(acc, h), acc, h <> acc))

def Gen.effs.tagged.if(+h: String, rest: List<&2, String>, hit: Bool) -> List<&2, String>:
  match hit:
    case True{}:
      String.drop(h, 5n) <> rest
    case False{}:
      rest

# The entries of effs tagged tag ("%gpu\t": the !-call targets; "%clo\t":
# defs the CPU makes closures of), untagged.
def Gen.effs.tagged(effs: List<&2, String>, +tag: String) -> List<&2, String>:
  match effs:
    case Nil{}:
      Nil{}
    case +h <> t:
      Gen.effs.tagged.if(h, Gen.effs.tagged(t, tag), String.starts_with(h, tag))

def Gen.effs.files.if(h: String, rest: List<&2, String>, tagged: Bool) -> List<&2, String>:
  match tagged:
    case True{}:
      rest
    case False{}:
      h <> rest

# The C files effects import, among effs.
def Gen.effs.files(effs: List<&2, String>) -> List<&2, String>:
  match effs:
    case Nil{}:
      Nil{}
    case +h <> t:
      Gen.effs.files.if(h, Gen.effs.files(t), String.starts_with(h, "%"))

def Gen.gpu.args(+n: Nat) -> String:
  String.join(Gen.gpu.params(n, 0), ", ")

def K.label.name(+name: String) -> String:
  Bool.pick(String, String.starts_with(name, "%wrap "), "KLW_" ++ Gen.mangle(String.drop(name, 6n)),
    "KL_" ++ Gen.mangle(name))

def Gen.gpu.stub.pick(kernel: Bool, head: String, cpu: String, +name: String, +n: Nat) -> String:
  match kernel:
    case True{}:
      head ++ "V ga[] = {" ++ String.join(List.append(&2, String, Gen.gpu.params(n, 0), ["0"]), ", ") ++ "}, r;\nif (gpu_call(&K_PROG, " ++ K.label.name(name) ++ ", ga, " ++
        U32.show(U32.from_nat(n)) ++ ", &r)) return r;\n" ++ cpu
    case False{}:
      head ++ cpu

def Gen.gpu.stub.go(+name: String, kernel: Bool, +n: Nat) -> String:
  Gen.gpu.stub.pick(kernel, "static V G_" ++ Gen.mangle(name) ++ "(" ++ Gen.cparams(Gen.gpu.params(n, 0)) ++ ") {\n",
    "return " ++ Gen.f(name) ++ "(" ++ Gen.gpu.args(n) ++ ");\n}\n", name, n)

def K.kept(mask: List<&2, Bool>) -> U32:
  match mask:
    case Nil{}:
      0
    case True{} <> t:
      U32.inc(K.kept(t))
    case False{} <> t:
      K.kept(t)

# G_f for a target f: on the device when it compiled, else on the CPU.
def Gen.gpu.stub(+g: G, +name: String, kernel: Bool) -> String:
  Gen.gpu.stub.go(name, kernel, U32.to_nat(K.kept(DInfo.mask(G.def(g, name)))))

def Gen.gpu.stubs(+g: G, ts: List<&2, String>, +kernel: Bool) -> String:
  match ts:
    case Nil{}:
      ""
    case +t <> rest:
      Gen.gpu.stub(g, t, kernel) ++ Gen.gpu.stubs(g, rest, kernel)

def Gen.gpu.fns(ws: List<&2, String>) -> String:
  match ws:
    case Nil{}:
      ""
    case +w <> t:
      "{" ++ Gen.w(w) ++ ", " ++ K.label.name("%wrap " ++ w) ++ "}, " ++ Gen.gpu.fns(t)

def Gen.gpu.errs(es: List<&2, String>) -> String:
  match es:
    case Nil{}:
      ""
    case e <> t:
      "// - " ++ e ++ "\n" ++ Gen.gpu.errs(t)

def K.lit.go(s: String) -> String:
  match s:
    case SNil{}:
      "\"\n"
    case SCon{Chr{10}, t}:
      "\\n\"\n\"" ++ K.lit.go(t)
    case SCon{Chr{34}, t}:
      "\\\"" ++ K.lit.go(t)
    case SCon{Chr{92}, t}:
      "\\\\" ++ K.lit.go(t)
    case SCon{c, t}:
      SCon{c, K.lit.go(t)}

# A C string literal of s, a line each.
def K.lit(s: String) -> String:
  "\"" ++ K.lit.go(s)

def Gen.gpu.emit.errs(+g: G, +ts: List<&2, String>, errs: List<&2, String>, +tables: String, +cases: String,
  wraps: List<&2, String>) -> String:
  match errs:
    case Nil{}:
      "\n// The device code of the !-calls (rt/gpu.h)\n" ++ GpuH.head() ++ tables ++ GpuH.mid() ++ cases ++
        GpuH.tail() ++ "#include \"gpuhost.h\"\n\nstatic const char K_SRC[] =\n" ++ GpuH.head_lit() ++ K.lit(tables) ++
        GpuH.mid_lit() ++ K.lit(cases) ++ GpuH.tail_lit() ++ ";\n\nstatic const GpuFn K_FNS[] = {" ++ Gen.gpu.fns(wraps) ++
        "{0, 0}};\nstatic GpuProg K_PROG = {K_SRC, bend_kernel, K_FNS, K_FRAME, K_NLABELS};\n\n" ++
        Gen.gpu.stubs(g, ts, True{})
    case e <> t:
      "\n// The !-calls run on the CPU:\n" ++ Gen.gpu.errs(e <> t) ++ Gen.gpu.stubs(g, ts, False{})

# The device code: tables (label defines and frame sizes), the cases of the
# kernel's switch, the defs it has wrappers for, and errors.
type KOut is Data:
  KOut{tables: String, cases: String, wraps: List<&2, String>, errs: List<&2, String>}

def Gen.gpu.emit(+g: G, +ts: List<&2, String>, out: KOut) -> String:
  KOut{tables, cases, wraps, errs} = out
  Gen.gpu.emit.errs(g, ts, errs, tables, cases, wraps)

#
# The functions a !-call can reach compile into one flat state machine (see
# rt/gpu.h): a function is an entry block, a call ends a block (the callee
# returns to a fresh one), every local lives in a frame slot, S(k), and a
# parallel let forks thunks and joins. The text compiles as MSL (the Metal
# kernel) and as C (the CPU simulator).
type KSt is Data:
  KSt{n: U32, sl: U32, curl: U32, cur: Doc, out: Doc, fns: List<&2, Bind>, todo: List<&2, String>,
    frames: List<&2, Bind>, errs: List<&2, String>}

def K.defines(fns: List<&2, Bind>) -> String:
  match fns:
    case Nil{}:
      ""
    case Bind{+name, l} <> t:
      "#define " ++ K.label.name(name) ++ " " ++ l ++ "\n" ++ K.defines(t)

def K.wraps.if(name: String, rest: List<&2, String>, wrap: Bool) -> List<&2, String>:
  match wrap:
    case True{}:
      String.drop(name, 6n) <> rest
    case False{}:
      rest

# The defs whose wrappers the device has code for.
def K.wraps(fns: List<&2, Bind>) -> List<&2, String>:
  match fns:
    case Nil{}:
      Nil{}
    case Bind{+name, l} <> t:
      K.wraps.if(name, K.wraps(t), String.starts_with(name, "%wrap "))

law K.frame_table:
  for +frames: List<&2, Bind>
  for +l: U32
  for +n: U32
  String

def K.block_doc.if(none: Bool, +l: U32, d: Doc) -> Doc:
  match none:
    case True{}:
      DNil{}
    case False{}:
      Doc.list([DStr{"case " ++ U32.show(l) ++ ": {\n"}, d, DStr{"break;\n}\n"}])

# A finished block as a case (label 0: none, while a lambda compiles).
def K.block_doc(+l: U32, d: Doc) -> Doc:
  K.block_doc.if(U32.is_zero(l), l, d)

@unsafe
def K.fin(r: Unit & KSt) -> KOut:
  (u, st) = r
  KSt{+n, sl, +curl, cur, out, +fns, todo, +frames, errs} = st
  KOut{"#define K_NLABELS " ++ U32.show(n) ++ "\n" ++ K.defines(fns) ++ "KCONST KW K_FRAME[] = {" ++
    K.frame_table(frames, 0, n) ++ "0};\n", Doc.flat(DCat{out, K.block_doc(curl, cur)}), K.wraps(fns), errs}

def KM(-A: Type) -> Type:
  KSt -> A & KSt

def KM.go(-A: Type, -B: Type, r: A & KSt, f: A -> KM(B)) -> B & KSt:
  (a, st) = r
  f(a, st)

def KM.bind(-A: Type, -B: Type, m: KM(A), f: A -> KM(B)) -> KM(B):
  st => KM.go(A, B, m(st), f)

def KM.pure(-A: Type, x: A) -> KM(A):
  st => (x, st)

law K.all:
  for +g: G
  for fuel: Nat
  KM(Unit)

def K.fn.new(+name: String, st: KSt) -> U32 & KSt:
  KSt{+n, sl, curl, cur, out, fns, todo, frames, errs} = st
  (n, KSt{U32.inc(n), sl, curl, cur, out, Bind{name, U32.show(n)} <> fns, name <> todo, frames, errs})

def K.fn.found(+name: String, m: Maybe<&2, String>, st: KSt) -> U32 & KSt:
  match m:
    case Some{l}:
      (Maybe.default(&2, U32, U32.read(l), 0), st)
    case None{}:
      K.fn.new(name, st)

# The entry label of a function, made (and queued to compile) on first use.
def K.fn.go(+name: String, st: KSt) -> U32 & KSt:
  KSt{+n, sl, curl, cur, out, +fns, todo, frames, errs} = st
  K.fn.found(name, Env.find(fns, name), KSt{n, sl, curl, cur, out, fns, todo, frames, errs})

def K.fn(+name: String) -> KM(U32):
  st => K.fn.go(name, st)

def K.wrap.name(+name: String) -> String:
  "%wrap " ++ name

def K.clos(cs: List<&2, String>) -> KM(Unit):
  match cs:
    case Nil{}:
      KM.pure(Unit, Unit{})
    case +c <> rest:
      do KM<Unit>:
        +w : U32 <- K.fn(K.wrap.name(c))
        K.clos(rest)

def K.targets(ts: List<&2, String>) -> KM(Unit):
  match ts:
    case Nil{}:
      KM.pure(Unit, Unit{})
    case +t <> rest:
      do KM<Unit>:
        +l : U32 <- K.fn(t)
        +w : U32 <- K.fn(K.wrap.name(t))
        K.targets(rest)

@unsafe
def K.program.m(+g: G, ts: List<&2, String>, clos: List<&2, String>) -> KM(Unit):
  do KM<Unit>:
    K.targets(ts)
    K.clos(clos)
    K.all(g, 100000n)

# The device code for the !-call targets ts, with wrappers for the defs the
# CPU makes closures of (clos), which the targets may be handed.
def K.program(+g: G, ts: List<&2, String>, clos: List<&2, String>) -> KOut:
  K.fin(K.program.m(g, ts, clos)(KSt{8, 0, 0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}}))

def Gen.gpu.tail(+g: G, ts: List<&2, String>, clos: List<&2, String>) -> String:
  match ts:
    case Nil{}:
      ""
    case +t <> +rest:
      Gen.gpu.emit(g, t <> rest, K.program(g, t <> rest, clos))

# The C output: head (constructor ids and the runtime), the C files the
# program's effects import (spliced in by the driver), then the body.
type COut is Data:
  COut{head: String, effs: List<&2, String>, body: String, errs: List<&2, String>}

def Gen.program.fin(+g: G, cids: String, r: String & St) -> COut:
  (entry, st) = r
  St{n, protos, code, refs, errs, memo, +effs} = st
  COut{cids ++ "#include \"bendrt.h\"\n\n", Gen.dedup(List.reverse(&2, String, Gen.effs.files(effs)), Nil{}),
    Doc.flat(Doc.list([protos, DStr{"\n"}, code, DStr{Gen.gpu.tail(g, Gen.dedup(Gen.effs.tagged(effs, "%gpu\t"), Nil{}),
    Gen.dedup(Gen.effs.tagged(effs, "%clo\t"), Nil{}))},
    DStr{"\n" ++ entry}])), errs}

law Gen.all:
  for +g: G
  for queue: List<&2, String>
  for done: Set()
  Gen(Unit)

@unsafe
def Gen.all.go(+g: G, +h: String, t: List<&2, String>, done: Set(), seen: Bool) ->
  Gen(Unit):
  match seen:
    case True{}:
      Gen.all(g, t, done)
    case False{}:
      do Gen<Unit>:
        Gen.def(g, h)
        refs : List<&2, String> <- Gen.take_refs()
        Gen.all(g, List.append(&2, String, refs, t), Set.add(done, h))

@unsafe
def Gen.all.seen(+g: G, +h: String, t: List<&2, String>, r: Set() & Bool) -> Gen(Unit):
  (done, seen) = r
  Gen.all.go(g, h, t, done, seen)

# Generates every def reachable from the queue.
@unsafe
def Gen.all(g, queue, done):
  match queue:
    case Nil{}:
      Gen.pure(Unit, Unit{})
    case +h <> t:
      Gen.all.seen(g, h, t, Set.has(done, h))

def Ty.head(e: Expr) -> String:
  match e:
    case EVar{n}:
      n
    case ETy{n, args}:
      n
    case ECall{EVar{n}, args}:
      n
    case other:
      "?"

law Gen.printer:
  for +g: G
  for +ty: Expr
  Gen(String)

@unsafe
def Gen.entry.ty(+g: G, +ret: Expr, io: Bool) -> Gen(String):
  match io:
    case True{}:
      Gen.pure(String,
        "int main(int argc, char **argv) { return bend_run(argc, argv, F_main); }\n")
    case False{}:
      do Gen<String>:
        p : String <- Gen.printer(g, ret)
        return "int main(int argc, char **argv) { return bend_run_value(argc, argv, F_main, " ++
          p ++ "); }\n"

# A main that returns IO runs it; any other main is evaluated and its value
# printed in Bend syntax, driven by main's return type.
def Gen.entry(+g: G, d: Decl) -> Gen(String):
  match d:
    case DDef{n, ps, b, +ret}:
      Gen.entry.ty(g, ret, Str.eq(Ty.head(ret), "IO"))
    case other:
      do Gen<String>:
        Gen.error("no main definition")
        return ""

def Gen.program.m(+g: G) -> Gen(String):
  do Gen<String>:
    Gen.all(g, ["main"], Set.new())
    Gen.entry(g, G.body(g, "main"))

def Gen.cids.line(+name: String, kind: Nat, +tag: U32) -> String:
  match kind:
    case 0n:
      "#define " ++ Gen.cid(name) ++ " " ++ U32.show(tag) ++ "u\n"
    case 1n:
      "#define " ++ Gen.cid(name) ++ " ((1u << 16) | " ++ U32.show(tag) ++ "u)\n"
    case 2n:
      "#define " ++ Gen.cid(name) ++ " ((2u << 16) | " ++ U32.show(tag) ++ "u)\n"
    case other:
      ""

def Gen.cids.kind(+name: String, info: Maybe<&2, CInfo>) -> String:
  match info:
    case None{}:
      ""
    case Some{CInfo{tag, ar, kind, single}}:
      Gen.cids.line(name, U32.to_nat(kind), tag)

def Gen.cids.ctors(+g: G, cs: List<&2, Ctor>) -> String:
  match cs:
    case Nil{}:
      ""
    case Ctor{+name, fs} <> t:
      Gen.cids.kind(name, G.ctor(g, name)) ++ Gen.cids.ctors(g, t)

# Constructor and effect ids, as the effect ABI names them (CID_NAME).
def Gen.cids(+g: G, ds: List<&2, Decl>, +i: U32) -> String:
  match ds:
    case Nil{}:
      ""
    case DType{n, ps, cs} <> t:
      Gen.cids.ctors(g, cs) ++ Gen.cids(g, t, i)
    case DEff{+n, ps, ims} <> t:
      "#define " ++ Gen.cid(n) ++ " ((3u << 16) | " ++ U32.show(i) ++ "u)\n" ++
        Gen.cids(g, t, U32.inc(i))
    case d <> t:
      Gen.cids(g, t, i)

def Gen.program(+ds: List<&2, Decl>) -> COut:
  +g = G.new(ds)
  Gen.program.fin(g, Gen.cids(g, ds, 0),
    Gen.program.m(g)(St{0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}}))

# Value printers
# ==============

type TB is Data:
  TB{name: String, ty: Expr}

def Ty.args(e: Expr) -> List<&2, Expr>:
  match e:
    case ETy{n, args}:
      args
    case ECall{f, args}:
      args
    case other:
      Nil{}

def Ty.bind.go(ps: List<&2, String>, xs: List<&2, Expr>) -> List<&2, TB>:
  match ps xs:
    case p <> pt x <> xt:
      TB{p, x} <> Ty.bind.go(pt, xt)
    case pl xl:
      Nil{}

# Binds type parameters to arguments, aligned from the right (a leading
# quantity argument may be left out).
def Ty.bind(ps: List<&2, String>, xs: List<&2, Expr>) -> List<&2, TB>:
  Ty.bind.go(List.reverse(&2, String, ps), List.reverse(&2, Expr, xs))

def Gen.memo.find.go(st: St, +k: String) -> Maybe<&2, String> & St:
  St{n, protos, code, refs, errs, +memo, effs} = st
  (Env.find(memo, k), St{n, protos, code, refs, errs, memo, effs})

def Gen.memo.find(+k: String) -> Gen(Maybe<&2, String>):
  st => Gen.memo.find.go(st, k)

def Gen.memo.add.go(st: St, b: Bind) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, b <> memo, effs})

def Gen.memo.add(b: Bind) -> Gen(Unit):
  st => Gen.memo.add.go(st, b)

def Gen.printer.test(+kind: U32, +tag: U32, single: Bool) -> String:
  Bool.pick(String, single, "if (1)",
    Bool.pick(String, U32.is_eq(kind, 1), "if (v == IMM(" ++ U32.show(tag) ++ "))",
      "if (!(v & 1) && TAG(v) == " ++ U32.show(tag) ++ ")"))

law Ty.find:
  for sub: List<&2, TB>
  for +x: String
  Maybe<&2, Expr>

@unsafe
def Ty.find.if(t: Expr, rest: List<&2, TB>, +x: String, hit: Bool) -> Maybe<&2, Expr>:
  match hit:
    case True{}:
      Some{t}
    case False{}:
      Ty.find(rest, x)

@unsafe
def Ty.find(sub, x):
  match sub:
    case Nil{}:
      None{}
    case TB{+n, t} <> rest:
      Ty.find.if(t, rest, x, String.eq(n, x))

law Ty.subst:
  for e: Expr
  for +sub: List<&2, TB>
  Expr

@unsafe
def Ty.substs(xs: List<&2, Expr>, +sub: List<&2, TB>) -> List<&2, Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> t:
      Ty.subst(h, sub) <> Ty.substs(t, sub)

@unsafe
def Ty.subst(e, sub):
  match e:
    case EVar{+n}:
      Maybe.default(&2, Expr, Ty.find(sub, n), EVar{n})
    case ETy{n, args}:
      ETy{n, Ty.substs(args, sub)}
    case ECall{f, args}:
      ECall{f, Ty.substs(args, sub)}
    case other:
      other

law Ty.tuple:
  for e: Expr
  List<&2, Expr>

@unsafe
def Ty.tuple.args(e: Expr, args: List<&2, Expr>) -> List<&2, Expr>:
  match args:
    case a <> b <> Nil{}:
      a <> Ty.tuple(b)
    case other:
      [e]

@unsafe
def Ty.tuple.go(e: Expr, args: List<&2, Expr>, pair: Bool) -> List<&2, Expr>:
  match pair:
    case True{}:
      Ty.tuple.args(e, args)
    case False{}:
      [e]

# Components of a (right-nested) pair type.
@unsafe
def Ty.tuple(e):
  match e:
    case ETy{+n, +args}:
      Ty.tuple.go(ETy{n, args}, args, Str.eq(n, "&"))
    case other:
      [other]

@unsafe
def Gen.printer.tuple(+g: G, xs: List<&2, Expr>, +path: String) -> Gen(Doc):
  match xs:
    case Nil{}:
      Gen.pure(Doc, DNil{})
    case h <> Nil{}:
      do Gen<Doc>:
        f : String <- Gen.printer(g, h)
        return DStr{f ++ "(" ++ path ++ ");\n"}
    case h <> t:
      do Gen<Doc>:
        f : String <- Gen.printer(g, h)
        rest : Doc <- Gen.printer.tuple(g, t, "FLD(" ++ path ++ ", 1)")
        return Doc.list([DStr{f ++ "(FLD(" ++ path ++ ", 0));\npr_s(\", \");\n"}, rest])

@unsafe
def Gen.printer.fields(
  +g: G, +sub: List<&2, TB>, fs: List<&2, Field>, +path: String, +i: U32
) -> Gen(Doc):
  match fs:
    case Nil{}:
      Gen.pure(Doc, DNil{})
    case Field{n, t} <> rest:
      do Gen<Doc>:
        f : String <- Gen.printer(g, Ty.subst(t, sub))
        more : Doc <- Gen.printer.fields(g, sub, rest, path, U32.inc(i))
        return Doc.list([DStr{Bool.pick(String, U32.is_zero(i), "", "pr_s(\", \");\n") ++ f ++
          "(" ++ Bool.pick(String, Str.eq(path, "v"), "v", path ++ U32.show(i) ++ ")") ++
          ");\n"}, more])

@unsafe
def Gen.printer.ctor(
  +g: G, +sub: List<&2, TB>, +name: String, fields: List<&2, Field>,
  info: Maybe<&2, CInfo>
) -> Gen(Doc):
  match info:
    case None{}:
      Gen.pure(Doc, DNil{})
    case Some{CInfo{+tag, ar, +kind, +single}}:
      do Gen<Doc>:
        fs : Doc <- Gen.printer.fields(g, sub, fields, Bool.pick(String, U32.is_eq(kind, 2),
          "v", "FLD(v, "), 0)
        return Doc.list([DStr{Gen.printer.test(kind, tag, single) ++ " { pr_s(\"" ++ name ++
          "{\");\n"}, fs, DStr{"pr_s(\"}\"); return; }\n"}])

@unsafe
def Gen.printer.ctors(+g: G, +sub: List<&2, TB>, cs: List<&2, Ctor>) -> Gen(Doc):
  match cs:
    case Nil{}:
      Gen.pure(Doc, DNil{})
    case Ctor{+name, fields} <> t:
      do Gen<Doc>:
        one : Doc <- Gen.printer.ctor(g, sub, name, fields, G.ctor(g, name))
        rest : Doc <- Gen.printer.ctors(g, sub, t)
        return Doc.list([one, rest])

@unsafe
def Gen.printer.adt(+g: G, +ty: Expr, d: Decl) -> Gen(Doc):
  match d:
    case DType{name, ps, cs}:
      do Gen<Doc>:
        b : Doc <- Gen.printer.ctors(g, Ty.bind(ps, Ty.args(ty)), cs)
        return Doc.list([b, DStr{"pr_s(\"?\");\n"}])
    case other:
      Gen.pure(Doc, DStr{"(void)v; pr_s(\"?\");\n"})

@unsafe
def Gen.printer.head(+g: G, +ty: Expr, k: Nat) -> Gen(Doc):
  match k:
    case 0n:
      Gen.pure(Doc, DStr{"pr_u32(v);\n"})
    case 1n:
      Gen.pure(Doc, DStr{"pr_nat(v);\n"})
    case 2n:
      Gen.pure(Doc, DStr{"pr_f32(v);\n"})
    case 3n:
      Gen.pure(Doc, DStr{"pr_char(v);\n"})
    case 4n:
      Gen.pure(Doc, DStr{"pr_str(v);\n"})
    case 5n:
      do Gen<Doc>:
        e : String <- Gen.printer(g, P.last(Ty.args(ty)))
        return DStr{"pr_s(\"[\");\nfor (int i = 0; TAG(v) == 1; i++) { if (i) pr_s(\", \"); " ++
          e ++ "(FLD(v, 0)); v = FLD(v, 1); }\npr_s(\"]\");\n"}
    case 6n:
      do Gen<Doc>:
        parts : Doc <- Gen.printer.tuple(g, Ty.tuple(ty), "v")
        return Doc.list([DStr{"pr_s(\"(\");\n"}, parts, DStr{"pr_s(\")\");\n"}])
    case 7n:
      Gen.pure(Doc, DStr{"(void)v; pr_s(\"<function>\");\n"})
    case 8n+p:
      Gen.printer.adt(g, ty, G.body(g, "%" ++ Ty.head(ty)))

@unsafe
def Gen.printer.body(+g: G, +ty: Expr, +h: String) -> Gen(Doc):
  Gen.printer.head(g, ty, P.which(h, ["U32", "Nat", "F32", "Char", "String", "List", "&",
    "->"]))

@unsafe
def Gen.printer.memo(+g: G, +ty: Expr, +key: String, m: Maybe<&2, String>) -> Gen(String):
  match m:
    case Some{f}:
      Gen.pure(String, f)
    case None{}:
      do Gen<String>:
        +k : U32 <- Gen.fresh()
        +f : String <- Gen.pure(String, "P" ++ U32.show(k))
        Gen.memo.add(Bind{key, f})
        Gen.proto(DStr{"static void " ++ f ++ "(V v);\n"})
        b : Doc <- Gen.printer.body(g, ty, Ty.head(ty))
        Gen.code(Doc.list([DStr{"static void " ++ f ++ "(V v) {\n"}, b, DStr{"}\n"}]))
        return f

# Returns the name of a C function printing values of a type.
@unsafe
def Gen.printer(g, ty):
  +key = Expr.show(ty)
  do Gen<String>:
    m : Maybe<&2, String> <- Gen.memo.find(key)
    Gen.printer.memo(g, ty, key, m)

# Modules
# =======

def Mod.ctor_names(cs: List<&2, Ctor>, acc: List<&2, String>) -> List<&2, String>:
  match cs:
    case Nil{}:
      acc
    case Ctor{n, fs} <> t:
      Mod.ctor_names(t, n <> acc)

# Top-level names a module defines (defs, laws, effects, types, ctors).
def Mod.names(ds: List<&2, Decl>, acc: List<&2, String>) -> List<&2, String>:
  match ds:
    case Nil{}:
      acc
    case DDef{n, ps, b, r} <> t:
      Mod.names(t, n <> acc)
    case DEff{n, ps, ims} <> t:
      Mod.names(t, n <> acc)
    case DLaw{n, ps} <> t:
      Mod.names(t, n <> acc)
    case DType{n, ps, cs} <> t:
      Mod.names(t, n <> Mod.ctor_names(cs, acc))
    case DImport{p, a} <> t:
      Mod.names(t, acc)

type Qual is Data:
  Qual{alias: String, names: List<&2, String>}

def Mod.q(+q: Qual, +x: String) -> String:
  Qual{+alias, +names} = q
  Bool.pick(String, Str.has(names, x), alias ++ "." ++ x, x)

def Mod.param_names(ps: List<&2, Param>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case Param{n, m, t} <> rest:
      n <> Mod.param_names(rest)

def Mod.var(+q: Qual, +bound: List<&2, String>, +x: String) -> String:
  Bool.pick(String, Str.has(bound, x), x, Mod.q(q, x))

law Mod.pat:
  for +q: Qual
  for p: Pat
  Pat

@unsafe
def Mod.pats(+q: Qual, ps: List<&2, Pat>) -> List<&2, Pat>:
  match ps:
    case Nil{}:
      Nil{}
    case h <> t:
      Mod.pat(q, h) <> Mod.pats(q, t)

@unsafe
def Mod.pat(q, p):
  match p:
    case PCtor{n, args}:
      PCtor{Mod.q(q, n), Mod.pats(q, args)}
    case PSucc{k, x}:
      PSucc{k, Mod.pat(q, x)}
    case other:
      other

law Mod.expr:
  for +q: Qual
  for +bound: List<&2, String>
  for e: Expr
  Expr

@unsafe
def Mod.fields(+q: Qual, fs: List<&2, Field>) -> List<&2, Field>:
  match fs:
    case Nil{}:
      Nil{}
    case Field{n, ty} <> t:
      Field{n, Mod.expr(q, Nil{}, ty)} <> Mod.fields(q, t)

def Mod.ctors(+q: Qual, cs: List<&2, Ctor>) -> List<&2, Ctor>:
  match cs:
    case Nil{}:
      Nil{}
    case Ctor{n, fs} <> t:
      Ctor{Mod.q(q, n), Mod.fields(q, fs)} <> Mod.ctors(q, t)

@unsafe
def Mod.decl(+q: Qual, d: Decl) -> Decl:
  match d:
    case DDef{n, +ps, b, r}:
      DDef{Mod.q(q, n), ps, Mod.expr(q, Mod.param_names(ps), b), Mod.expr(q, Nil{}, r)}
    case DEff{n, ps, ims}:
      DEff{Mod.q(q, n), ps, ims}
    case DLaw{n, ps}:
      DLaw{Mod.q(q, n), ps}
    case DType{n, ps, cs}:
      DType{Mod.q(q, n), ps, Mod.ctors(q, cs)}
    case DImport{p, a}:
      DImport{p, a}

def Mod.decls(+q: Qual, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Mod.decl(q, d) <> Mod.decls(q, t)

def Mod.qualify(+alias: String, +ds: List<&2, Decl>) -> List<&2, Decl>:
  Mod.decls(Qual{alias, Mod.names(ds, Nil{})}, ds)

@unsafe
def Mod.exprs(+q: Qual, +bound: List<&2, String>, xs: List<&2, Expr>) -> List<&2, Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> t:
      Mod.expr(q, bound, h) <> Mod.exprs(q, bound, t)

# Renames references to module names (locals shadow them).
@unsafe
def Mod.expr(q, bound, e):
  match e:
    case EVar{x}:
      EVar{Mod.var(q, bound, x)}
    case ECall{f, args}:
      ECall{Mod.expr(q, bound, f), Mod.exprs(q, bound, args)}
    case ECtor{n, args}:
      ECtor{Mod.q(q, n), Mod.exprs(q, bound, args)}
    case ELam{+p, b}:
      ELam{Mod.pat(q, p), Mod.expr(q, Pat.vars(p, bound), b)}
    case ELet{+p, v, b}:
      ELet{Mod.pat(q, p), Mod.expr(q, bound, v), Mod.expr(q, Pat.vars(p, bound), b)}
    case EMatch{scrs, cases}:
      EMatch{Mod.exprs(q, bound, scrs), Mod.exprs(q, bound, cases)}
    case ECase{+ps, b}:
      ECase{Mod.pats(q, ps), Mod.expr(q, Pats.vars(ps, bound), b)}
    case ESucc{k, x}:
      ESucc{k, Mod.expr(q, bound, x)}
    case EOp{op, a, b}:
      EOp{op, Mod.expr(q, bound, a), Mod.expr(q, bound, b)}
    case EAnn{x, t}:
      EAnn{Mod.expr(q, bound, x), Mod.var(q, bound, t)}
    case ETy{n, args}:
      ETy{Mod.var(q, bound, n), Mod.exprs(q, bound, args)}
    case other:
      other

law Mod.dir.go:
  for s: String
  String

@unsafe
def Mod.dir.if(x: U32, t: String, slash: Bool) -> String:
  match slash:
    case True{}:
      SCon{Chr{x}, t}
    case False{}:
      Mod.dir.go(t)

@unsafe
def Mod.dir.go(s):
  match s:
    case SNil{}:
      SNil{}
    case SCon{Chr{+x}, t}:
      Mod.dir.if(x, t, U32.is_eq(x, 47))

# Directory part of a path, with its trailing '/'.
def Mod.dir(path: String) -> String:
  Str.rev(Mod.dir.go(Str.rev(path)))

# Driver
# ======

def Main.lib.or(r: Result<&1, &1, U32 & String, String>) -> IO(String):
  match r:
    case Done{v}:
      IO.pure(String, v)
    case Fail{e}:
      do IO<String>:
        home : String <- IO.try(String, IO.get_env("HOME"))
        return home ++ "/.bend/lib"

# Where hub packages live: $BEND_LIB, or ~/.bend/lib.
def Main.lib() -> IO(String):
  do IO<String>:
    r : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_LIB")
    Main.lib.or(r)

def Main.hub.url(r: Result<&1, &1, U32 & String, String>) -> String:
  match r:
    case Done{v}:
      v
    case Fail{e}:
      "https://hub.bend-lang.com"

law Main.load:
  for fuel: Nat
  for +path: String
  IO(List<&2, Decl>)

# Fetches a hub package into lib, unless it is there (see rt/hub.c).
def Hub.ensure(lib: String, hub: String, rel: String) ->
  IO(Result<&1, &1, U32 & String, Unit>):
  import "./rt/hub.c"
  import "./rt/hub.js"

# An import by content hash (0x<hash>/path.bend) is fetched from the hub.
@unsafe
def Main.load.hub(f: Nat, +p: String) -> IO(List<&2, Decl>):
  do IO<List<&2, Decl>>:
    +lib : String <- Main.lib()
    hr : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_HUB")
    u : Unit <- IO.try(Unit, Hub.ensure(lib, Main.hub.url(hr), p))
    Main.load(f, lib ++ "/" ++ p)

def Eff.path(+dir: String, +p: String) -> String:
  Bool.pick(String, String.starts_with(p, "/"), p, dir ++ p)

@unsafe
def Main.load.import(f: Nat, +dir: String, +p: String, hub: Bool) -> IO(List<&2, Decl>):
  match hub:
    case True{}:
      Main.load.hub(f, p)
    case False{}:
      Main.load(f, Eff.path(dir, p))

def Eff.paths(+dir: String, ps: List<&2, String>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case h <> t:
      Eff.path(dir, h) <> Eff.paths(dir, t)

def Eff.decl(+dir: String, d: Decl) -> Decl:
  match d:
    case DEff{n, ps, ims}:
      DEff{n, ps, Eff.paths(dir, ims)}
    case other:
      other

# Resolves the files foreign defs import against their file's directory.
def Eff.decls(+dir: String, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case h <> t:
      Eff.decl(dir, h) <> Eff.decls(dir, t)

def Main.resolve(+dir: String, r: Result<&2, &2, String, List<&2, Decl>>) ->
  Result<&2, &2, String, List<&2, Decl>>:
  match r:
    case Fail{e}:
      Fail{e}
    case Done{ds}:
      Done{Eff.decls(dir, ds)}

def Main.parse.fin(r: List<&2, Decl> & String) -> Result<&2, &2, String, List<&2, Decl>>:
  (ds, +err) = r
  Bool.pick(Result<&2, &2, String, List<&2, Decl>>, String.is_empty(err), Done{ds},
    Fail{err})

def Main.parse(src: String) -> Result<&2, &2, String, List<&2, Decl>>:
  Main.parse.fin(P.file(src))

law Main.effs:
  for ps: List<&2, String>
  for acc: String
  IO(String)

# Reads the effect sources to splice into the output.
@unsafe
def Main.effs(ps, acc):
  match ps:
    case Nil{}:
      IO.pure(String, acc)
    case p <> t:
      do IO<String>:
        src : String <- IO.read_file(p)
        Main.effs(t, acc ++ src ++ "\n")

def Main.emit.ok(head: String, effs: List<&2, String>, body: String) -> IO(Unit):
  do IO<Unit>:
    srcs : String <- Main.effs(effs, "")
    IO.write(head ++ srcs ++ body)

def Main.emit(r: COut) -> IO(Unit):
  COut{head, effs, body, errs} = r
  match errs:
    case Nil{}:
      Main.emit.ok(head, effs, body)
    case e <> t:
      do IO<Unit>:
        IO.print_err(String.join(List.reverse(&2, String, e <> t), "\n"))
        IO.die(Unit, 1, "bendc: compilation failed")

law Main.js.effs:
  for es: List<&2, String>
  for acc: String
  IO(String)

@unsafe
def Main.emit.js.ok(head: String, effs: List<&2, String>, body: String) -> IO(Unit):
  do IO<Unit>:
    tab : String <- Main.js.effs(effs, "")
    IO.write(head ++ "\nconst EFF = {\n" ++ tab ++ "};\n\n" ++ body)

def Main.emit.js(r: COut) -> IO(Unit):
  COut{head, effs, body, errs} = r
  match errs:
    case Nil{}:
      Main.emit.js.ok(head, effs, body)
    case e <> t:
      do IO<Unit>:
        IO.print_err(String.join(List.reverse(&2, String, e <> t), "\n"))
        IO.die(Unit, 1, "bendc: compilation failed")

#
# bendc --js emits a JavaScript program (for Bun, or Node when it makes no
# system calls) with values as the official JS target has them, so effect
# files written for it (.js imports) run unchanged. See rt/bendrt.js.
# A constructor's type, field names, and whether its type has only it.
type JCI is Data:
  JCI{ty: String, fields: List<&2, String>, single: Bool}

type JG is Data:
  JG{g: G, jm: Map<&2, JCI>}

def Field.names(fs: List<&2, Field>) -> List<&2, String>:
  match fs:
    case Nil{}:
      Nil{}
    case Field{n, t} <> rest:
      n <> Field.names(rest)

def J.info.ctors(+ty: String, cs: List<&2, Ctor>, +single: Bool, m: Map<&2, JCI>) -> Map<&2, JCI>:
  match cs:
    case Nil{}:
      m
    case Ctor{name, fs} <> t:
      J.info.ctors(ty, t, single, Map.set(&2, JCI, m, name, JCI{ty, Field.names(fs), single}))

def J.info(ds: List<&2, Decl>, m: Map<&2, JCI>) -> Map<&2, JCI>:
  match ds:
    case Nil{}:
      m
    case DType{n, ps, +cs} <> t:
      J.info(t, J.info.ctors(n, cs, Nat.is_eq(List.length(&2, Ctor, cs), 1n), m))
    case d <> t:
      J.info(t, m)

def JG.g(+j: JG) -> G:
  JG{+g, jm} = j
  g

law J.all:
  for +j: JG
  for queue: List<&2, String>
  for done: Set()
  Gen(Unit)

law J.printer:
  for +j: JG
  for +ty: Expr
  Gen(String)

@unsafe
def J.entry.ty(+j: JG, +ret: Expr, io: Bool) -> Gen(String):
  match io:
    case True{}:
      Gen.pure(String, "bend_run(F_main);\n")
    case False{}:
      do Gen<String>:
        p : String <- J.printer(j, ret)
        return "bend_run_value(F_main, " ++ p ++ ");\n"

def J.entry(+j: JG, d: Decl) -> Gen(String):
  match d:
    case DDef{n, ps, b, +ret}:
      J.entry.ty(j, ret, Str.eq(Ty.head(ret), "IO"))
    case other:
      do Gen<String>:
        Gen.error("no main definition")
        return ""

@unsafe
def J.program.m(+j: JG) -> Gen(String):
  do Gen<String>:
    J.all(j, ["main"], Set.new())
    J.entry(j, G.body(JG.g(j), "main"))

def J.program.fin(r: String & St) -> COut:
  (entry, st) = r
  St{n, protos, code, refs, errs, memo, effs} = st
  COut{RtJs.src(), Gen.dedup(List.reverse(&2, String, Gen.effs.files(effs)), Nil{}), Doc.flat(Doc.list([code, DStr{"\n" ++ entry}])), errs}

def J.program(+ds: List<&2, Decl>) -> COut:
  J.program.fin(J.program.m(JG{G.new(ds), J.info(ds, MTip{})})(St{0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}}))

def Main.emit.to(js: Bool, +ds: List<&2, Decl>) -> IO(Unit):
  match js:
    case True{}:
      Main.emit.js(J.program(ds))
    case False{}:
      Main.emit(Gen.program(ds))

def Main.compile(js: Bool, base: Result<&2, &2, String, List<&2, Decl>>,
  user: Result<&2, &2, String, List<&2, Decl>>
) -> IO(Unit):
  match base user:
    case Fail{e} u:
      IO.die(Unit, 1, "bendc: parse error in base: " ++ e)
    case Done{b} Fail{e}:
      IO.die(Unit, 1, "bendc: parse error: " ++ e)
    case Done{b} Done{u}:
      Main.emit.to(js, List.append(&2, Decl, b, u))

def Main.ast(r: Result<&2, &2, String, List<&2, Decl>>) -> IO(Unit):
  match r:
    case Fail{e}:
      IO.die(Unit, 1, "bendc: parse error: " ++ e)
    case Done{ds}:
      IO.write(Decls.show(ds))

def Main.chk.fail(-A: Type, e: Chk.Err) -> IO(A):
  IO.die(A, 1, Chk.show_err(e))

def Main.read_opt.res(r: Result<&1, &1, U32 & String, String>) -> Maybe<&2, String>:
  match r:
    case Done{v}:
      Some{v}
    case Fail{e}:
      None{}

def Main.read_opt.fin(r: File & Result<&1, &1, U32 & String, String>) -> IO(Maybe<&2, String>):
  (f2, res) = r
  do IO<Maybe<&2, String>>:
    File.close(f2)
    return Main.read_opt.res(res)

def Main.read_opt.open(r: Result<&1, &1, U32 & String, File>) -> IO(Maybe<&2, String>):
  match r:
    case Done{f}:
      do IO<Maybe<&2, String>>:
        got : File & Result<&1, &1, U32 & String, String> <- IO.read_all(f)
        Main.read_opt.fin(got)
    case Fail{e}:
      IO.pure(Maybe<&2, String>, None{})

# A file's text, if it can be read.
def Main.read_opt(path: String) -> IO(Maybe<&2, String>):
  do IO<Maybe<&2, String>>:
    r : Result<&1, &1, U32 & String, File> <- File.open(path, "r")
    Main.read_opt.open(r)

def Main.chk.loading() -> String:
  "\u{0}"

type CS is Data:
  CS{book: Chk.Book, seen: List<&2, Chk.SB2>, n0: Nat}

law Main.chk.load:
  for fuel: Nat
  for +base: String
  for +file: String
  for +ns: String
  for +sp: Chk.Sp
  for +st: CS
  IO(CS)

def Main.chk.hub(+rel: String) -> IO(String):
  do IO<String>:
    +lib : String <- Main.lib()
    hr : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_HUB")
    u : Unit <- IO.try(Unit, Hub.ensure(lib, Main.hub.url(hr), rel))
    return lib ++ "/" ++ rel

def Main.chk.is_hub.hex(s: String) -> Bool:
  match s:
    case SCon{Chr{+c}, t}:
      Bool.or(U32.is_eq(c, 47), Bool.and(Bool.or(Char.is_digit(Chr{c}), Bool.and(U32.is_ge(c, 97), U32.is_le(c, 102))),
        Main.chk.is_hub.hex(t)))
    case SNil{}:
      False{}

def Main.chk.is_hub(+rel: String) -> Bool:
  Bool.and(String.starts_with(rel, "0x"), Main.chk.is_hub.hex(String.drop(rel, 2n)))

def Path.dirname(+p: String) -> String:
  +d = Mod.dir(p)
  Bool.pick(String, String.is_empty(d), ".", Bool.pick(String, String.eq(d, "/"), "/",
    String.take(d, Nat.sub(String.length(d), 1n))))

#
# Files are loaded into the checker's book as the official bend loads them:
# imports first (each file once, in its own namespace), then the file's
# declarations. The whole book is then checked.
def Path.push(+seg: String, st: List<&2, String>, abs: Bool) -> List<&2, String>:
  match st:
    case Nil{}:
      Bool.pick(List<&2, String>, String.eq(seg, ".."), Bool.pick(List<&2, String>, abs, Nil{}, [".."]), [seg])
    case +h <> +t:
      Bool.pick(List<&2, String>, String.eq(seg, ".."),
        Bool.pick(List<&2, String>, String.eq(h, ".."), ".." <> h <> t, t), seg <> h <> t)

def Path.fold(segs: List<&2, String>, +st: List<&2, String>, +abs: Bool) -> List<&2, String>:
  match segs:
    case Nil{}:
      st
    case +g <> t:
      Path.fold(t, Bool.pick(List<&2, String>, Bool.or(String.is_empty(g), String.eq(g, ".")), st,
        Path.push(g, st, abs)), abs)

# A path without "." or ".." segments (as path.posix.normalize makes it).
def Path.norm(+p: String) -> String:
  +abs = String.starts_with(p, "/")
  +body = String.join(List.reverse(&2, String, Path.fold(String.split(p, '/'), Nil{}, abs)), "/")
  Bool.pick(String, abs, "/" ++ body, Bool.pick(String, String.is_empty(body), ".", body))

def Path.join(+a: String, +b: String) -> String:
  Path.norm(a ++ "/" ++ b)

@unsafe
def Main.chk.imp.rel(
  f: Nat, +base: String, +dir: String, +ns: String, +sp: Chk.Sp, +rel: String, +alias: String, +path: String, st: CS,
  al: List<&2, Chk.SB2>, bend: Bool
) -> IO(CS & List<&2, Chk.SB2>):
  match bend:
    case False{}:
      Main.chk.fail(CS & List<&2, Chk.SB2>, Chk.err0("an import of a .bend file", Chk.MStr{"'" ++ path ++ "'"}, sp))
    case True{}:
      +abs = String.starts_with(rel, "/")
      +hub = Main.chk.is_hub(rel)
      +sub = Bool.pick(String, Bool.or(abs, hub), rel, Path.join(Path.dirname(ns), rel))
      +ns2 = String.take(sub, Nat.sub(String.length(sub), 5n))
      do IO<CS & List<&2, Chk.SB2>>:
        +at : String <- Bool.pick(IO(String), hub, Main.chk.hub(rel),
          IO.pure(String, Bool.pick(String, abs, rel, dir ++ rel)))
        st2 : CS <- Main.chk.load(f, base, at, ns2, sp, st)
        return (st2, List.append(&2, Chk.SB2, al, [Chk.SB2{alias, ns2}]))

@unsafe
def Main.chk.imp.go(
  f: Nat, +base: String, +dir: String, +ns: String, +sp: Chk.Sp, +rel: String, +alias: String, +path: String, st: CS,
  al: List<&2, Chk.SB2>, base_imp: Bool
) -> IO(CS & List<&2, Chk.SB2>):
  match base_imp:
    case True{}:
      do IO<CS & List<&2, Chk.SB2>>:
        st2 : CS <- Main.chk.load(f, base, base, "", sp, st)
        return (st2, al)
    case False{}:
      Main.chk.imp.rel(f, base, dir, ns, sp, rel, alias, path, st, al, String.ends_with(rel, ".bend"))

# An import of a file as alias: where it is and its namespace.
@unsafe
def Main.chk.imp(
  f: Nat, +base: String, +dir: String, +ns: String, +src: String, imp: Chk.Imp, st: CS, al: List<&2, Chk.SB2>
) -> IO(CS & List<&2, Chk.SB2>):
  Chk.Imp{+path, +alias, +beg} = imp
  +sp = {Chk.Sp{src, beg, beg} : Chk.Sp}
  +rel = Path.norm(path)
  Main.chk.imp.go(f, base, dir, ns, sp, rel, alias, path, st, al, String.is_empty(alias))

law Main.chk.imps:
  for +f: Nat
  for +base: String
  for +dir: String
  for +ns: String
  for +src: String
  for imps: List<&2, Chk.Imp>
  for st: CS
  for al: List<&2, Chk.SB2>
  IO(CS & List<&2, Chk.SB2>)

@unsafe
def Main.chk.imps.next(
  f: Nat, +base: String, +dir: String, +ns: String, +src: String, imps: List<&2, Chk.Imp>,
  r: CS & List<&2, Chk.SB2>
) -> IO(CS & List<&2, Chk.SB2>):
  (st, al) = r
  Main.chk.imps(f, base, dir, ns, src, imps, st, al)

@unsafe
def Main.chk.imps(f, base, dir, ns, src, imps, st, al):
  match imps:
    case Nil{}:
      IO.pure(CS & List<&2, Chk.SB2>, (st, al))
    case i <> t:
      do IO<CS & List<&2, Chk.SB2>>:
        r : CS & List<&2, Chk.SB2> <- Main.chk.imp(f, base, dir, ns, src, i, st, al)
        Main.chk.imps.next(f, base, dir, ns, src, t, r)

def Main.chk.parsed(
  +base: String, +file: String, +ns: String, seen: List<&2, Chk.SB2>, +n1: Nat, r: Result<&1, &1, Chk.Err, Chk.Book>
) -> IO(CS):
  match r:
    case Fail{e}:
      Main.chk.fail(CS, e)
    case Done{+b}:
      IO.pure(CS, CS{Bool.pick(Chk.Book, String.eq(Path.norm(file), Path.norm(base)), Chk.mark_base(b, n1), b),
        Chk.SB2{Path.norm(file), ns} <> seen, n1})

# Spans index the text as parsed (its import lines blanked).
def Main.chk.parse_text(book: Chk.Book, +text: String, ns: String, dir: String, al: List<&2, Chk.SB2>) ->
  Result<&1, &1, Chk.Err, Chk.Book>:
  Chk.parse_file(book, text, text, ns, dir, al)

# After a file's imports: its declarations join the book.
@unsafe
def Main.chk.parse(
  +base: String, +file: String, +ns: String, +src: String, lines: List<&2, String>, r: CS & List<&2, Chk.SB2>
) -> IO(CS):
  (st, al) = r
  CS{+book, seen, n0} = st
  +n1 = Chk.book_len(book)
  Main.chk.parsed(base, file, ns, seen, n1, Main.chk.parse_text(book, String.join(lines, "\n"), ns, Mod.dir(file), al))

def CS.mark(st: CS, +real: String) -> CS:
  CS{book, seen, n0} = st
  CS{book, Chk.SB2{real, Main.chk.loading()} <> seen, n0}

@unsafe
def Main.chk.hdr(f: Nat, +base: String, +file: String, +ns: String, +src: String, st: CS, h: Chk.Hdr) -> IO(CS):
  Chk.Hdr{lines, imps, err} = h
  match err:
    case Some{e}:
      Main.chk.fail(CS, e)
    case None{}:
      do IO<CS>:
        r : CS & List<&2, Chk.SB2> <- Main.chk.imps(f, base, Mod.dir(file), ns, src, imps,
          CS.mark(st, Path.norm(file)), Nil{})
        Main.chk.parse(base, file, ns, src, lines, r)

@unsafe
def Main.chk.src(f: Nat, +base: String, +file: String, +ns: String, +src: String, st: CS) -> IO(CS):
  Main.chk.hdr(f, base, file, ns, src, st, Chk.header(src))

@unsafe
def Main.chk.read(
  f: Nat, +base: String, +file: String, +ns: String, +sp: Chk.Sp, st: CS, m: Maybe<&2, String>
) -> IO(CS):
  match m:
    case None{}:
      Main.chk.fail(CS, Chk.err0("no such file: " ++ file, Chk.MNone{}, sp))
    case Some{src}:
      Main.chk.src(f, base, file, ns, src, st)

def CS.at_end(st: CS) -> CS:
  CS{+book, seen, n0} = st
  CS{book, seen, Chk.book_len(book)}

@unsafe
def Main.chk.seen(
  f: Nat, +base: String, +file: String, +ns: String, +sp: Chk.Sp, st: CS, done: Maybe<&2, String>
) -> IO(CS):
  match done:
    case Some{+v}:
      Bool.pick(IO(CS), String.eq(v, Main.chk.loading()),
        Main.chk.fail(CS, Chk.err0("an import cycle through " ++ file, Chk.MNone{}, sp)),
        Bool.pick(IO(CS), String.eq(v, ns), IO.pure(CS, CS.at_end(st)),
          Main.chk.fail(CS, Chk.err0("one namespace per file (" ++ file ++ " is both '" ++ v ++ "' and '" ++ ns ++ "')",
            Chk.MNone{}, sp))))
    case None{}:
      do IO<CS>:
        m : Maybe<&2, String> <- Main.read_opt(file)
        Main.chk.read(f, base, file, ns, sp, st, m)

def CS.seen(+st: CS) -> List<&2, Chk.SB2>:
  CS{book, +seen, n0} = st
  seen

@unsafe
def Main.chk.load(fuel, base, file, ns, sp, st):
  match fuel:
    case 0n:
      IO.die(CS, 1, "bendc: imports nested too deeply at " ++ file)
    case 1n+f:
      Main.chk.seen(f, base, file, ns, sp, st, Chk.SB2.find(CS.seen(st), Path.norm(file)))

def Main.check.res(+n0: Nat, r: Result<&1, &1, Chk.Err, Chk.Book>) -> IO(Chk.Book & Nat):
  match r:
    case Fail{e}:
      Main.chk.fail(Chk.Book & Nat, e)
    case Done{b}:
      IO.pure(Chk.Book & Nat, (b, n0))

def Main.check.fin(st: CS) -> IO(Chk.Book & Nat):
  CS{book, seen, +n0} = st
  Main.check.res(n0, Chk.check_book(book))

# Loads and checks a program; answers the checked book and where the
# file's own declarations start.
@unsafe
def Main.check(+base: String, +file: String) -> IO(Chk.Book & Nat):
  do IO<Chk.Book & Nat>:
    st : CS <- Main.chk.load(64n, base, file, "", Chk.NoSp{}, CS{Chk.book_nil(), Nil{}, 0n})
    Main.check.fin(st)

def Main.check_only.fin(r: Chk.Book & Nat) -> IO(Unit):
  (b, n0) = r
  +bad = Chk.report(b, n0)
  Bool.pick(IO(Unit), List.is_empty(&2, String, bad), IO.write("All terms check.\n"),
    IO.write(Chk.report_text(bad)))

@unsafe
def Main.build(js: Bool, +base_path: String, user_path: String) -> IO(Unit):
  do IO<Unit>:
    base : String <- IO.read_file(base_path)
    user : List<&2, Decl> <- Main.load(64n, user_path)
    Main.compile(js, Main.resolve(Mod.dir(base_path), Main.parse(base)), Done{user})

# Whether main returns a value (not IO) that may hold a function.
def Main.normalized(+b: Chk.Book) -> Bool:
  Bool.and(Bool.not(Chk.main_is_io(b)), Chk.main_has_fun(b))

law J.hex.go:
  for +n: U32
  for acc: String
  String

@unsafe
def J.hex(+n: U32) -> String:
  J.hex.go(n, "")

# A JS string literal.
def J.lit_chr(+x: U32) -> String:
  Bool.pick(String, Bool.and(Bool.and(U32.is_ge(x, 32), U32.is_lt(x, 127)),
    Bool.not(Str.has(["\"", "\\"], Str.chr(x)))), Str.chr(x),
    "\\u{" ++ J.hex(x) ++ "}")

def J.lit(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{Chr{x}, t}:
      J.lit_chr(x) ++ J.lit(t)

# A program that prints a value computed at compile time.
def Main.emit_value(js: Bool, v: String) -> IO(Unit):
  match js:
    case True{}:
      IO.write("process.stdout.write(\"" ++ J.lit(v) ++ "\\n\");\n")
    case False{}:
      IO.write("#include <stdio.h>\n\nint main(void) {\n  fputs(\"" ++ Gen.lit(v) ++
        "\\n\", stdout);\n  return 0;\n}\n")

@unsafe
def Main.checked.go(js: Bool, +base_path: String, user_path: String, +bk: Chk.Book, norm: Bool) -> IO(Unit):
  match norm:
    case True{}:
      Main.emit_value(js, Chk.show_main(bk))
    case False{}:
      Main.build(js, base_path, user_path)

# After checking: report defs that rely on unsafe or foreign code (on
# stderr), then compile. A value main that may hold a function is printed
# as the checker normalizes it.
@unsafe
def Main.checked(js: Bool, +base_path: String, user_path: String, r: Chk.Book & Nat) -> IO(Unit):
  (b, n0) = r
  +bk = b
  +bad = Chk.report(bk, n0)
  do IO<Unit>:
    Bool.pick(IO(Unit), List.is_empty(&2, String, bad), IO.pure(Unit, Unit{}), IO.write_err(Chk.report_text(bad)))
    Main.checked.go(js, base_path, user_path, bk, Main.normalized(bk))

@unsafe
def Main.run(args: List<&2, String>) -> IO(Unit):
  match args:
    case "--tokens" <> path <> Nil{}:
      do IO<Unit>:
        src : String <- IO.read_file(path)
        IO.print(Toks.show(Lex.all(src)))
    case "--ast" <> path <> Nil{}:
      do IO<Unit>:
        src : String <- IO.read_file(path)
        Main.ast(Main.parse(src))
    case "--check-only" <> base_path <> user_path <> Nil{}:
      do IO<Unit>:
        r : Chk.Book & Nat <- Main.check(base_path, user_path)
        Main.check_only.fin(r)
    case "--no-check" <> +base_path <> user_path <> Nil{}:
      Main.build(False{}, base_path, user_path)
    case "--js" <> +base_path <> +user_path <> Nil{}:
      do IO<Unit>:
        r : Chk.Book & Nat <- Main.check(base_path, user_path)
        Main.checked(True{}, base_path, user_path, r)
    case +base_path <> +user_path <> Nil{}:
      do IO<Unit>:
        r : Chk.Book & Nat <- Main.check(base_path, user_path)
        Main.checked(False{}, base_path, user_path, r)
    case other:
      IO.die(Unit, 1, "usage: bendc [--check-only | --no-check | --js] <base.bend> <input.bend> | --tokens <file> | --ast <file>")

def main() -> IO(Unit):
  do IO<Unit>:
    args : List<String> <- IO.args()
    Main.run(IO.list2(args))

law Main.imports:
  for +f: Nat
  for +dir: String
  for ds: List<&2, Decl>
  IO(List<&2, Decl>)

@unsafe
def Main.load.parsed(
  f: Nat, +dir: String, +path: String, r: Result<&2, &2, String, List<&2, Decl>>
) -> IO(List<&2, Decl>):
  match r:
    case Fail{e}:
      IO.die(List<&2, Decl>, 1, "bendc: parse error in " ++ path ++ ": " ++ e)
    case Done{+ds}:
      do IO<List<&2, Decl>>:
        imported : List<&2, Decl> <- Main.imports(f, dir, ds)
        return List.append(&2, Decl, imported, Eff.decls(dir, ds))

@unsafe
def Main.imports.one(
  +f: Nat, +dir: String, +p: String, a: String, t: List<&2, Decl>, base: Bool
) -> IO(List<&2, Decl>):
  match base:
    case True{}:
      Main.imports(f, dir, t)
    case False{}:
      do IO<List<&2, Decl>>:
        sub : List<&2, Decl> <- Main.load.import(f, dir, p, String.starts_with(p, "0x"))
        rest : List<&2, Decl> <- Main.imports(f, dir, t)
        return List.append(&2, Decl, Mod.qualify(a, sub), rest)

@unsafe
def Main.imports(f, dir, ds):
  match ds:
    case Nil{}:
      IO.pure(List<&2, Decl>, Nil{})
    case DImport{+p, a} <> t:
      Main.imports.one(f, dir, p, a, t, Str.eq(p, "Base"))
    case d <> t:
      Main.imports(f, dir, t)

# Loads a file and (recursively) the modules it imports; an imported
# module's names are qualified by its alias.
@unsafe
def Main.load(fuel, path):
  match fuel:
    case 0n:
      IO.die(List<&2, Decl>, 1, "bendc: imports nested too deeply at " ++ path)
    case 1n+f:
      do IO<List<&2, Decl>>:
        src : String <- IO.read_file(path)
        Main.load.parsed(f, Mod.dir(path), path, Main.parse(src))

def Main.js.wrap(src: String, +host: String) -> String:
  "...(() => {\n" ++ src ++ "\nreturn { [\"" ++ host ++ "\"]: { run: typeof " ++ host ++ " === \"function\" ? " ++ host ++
    " : undefined, need: typeof " ++ host ++ "_need === \"function\" ? " ++ host ++ "_need : undefined } };\n})(),\n"

def Main.js.eff(r: String & String) -> IO(String):
  (path, host) = r
  +h = host
  do IO<String>:
    src : String <- IO.read_file(path)
    return Main.js.wrap(src, h)

# The effect table: each JS file an effect imports, wrapped as the official
# target wraps it, answering its host function.
@unsafe
def Main.js.effs(es, acc):
  match es:
    case Nil{}:
      IO.pure(String, acc)
    case e <> t:
      do IO<String>:
        w : String <- Main.js.eff(Str.split_tab(e))
        Main.js.effs(t, acc ++ w)

# Misc
# ====

def KM.if(-A: Type, c: Bool, t: KM(A), e: KM(A)) -> KM(A):
  match c:
    case True{}:
      t
    case False{}:
      e

def K.fresh.go(st: KSt) -> U32 & KSt:
  KSt{+n, sl, curl, cur, out, fns, todo, frames, errs} = st
  (n, KSt{U32.inc(n), sl, curl, cur, out, fns, todo, frames, errs})

# A fresh block label.
def K.fresh() -> KM(U32):
  st => K.fresh.go(st)

def K.slot.go(st: KSt) -> U32 & KSt:
  KSt{n, +sl, curl, cur, out, fns, todo, frames, errs} = st
  (sl, KSt{n, U32.inc(sl), curl, cur, out, fns, todo, frames, errs})

# A fresh frame slot of the function being compiled.
def K.slot() -> KM(U32):
  st => K.slot.go(st)

def K.put.go(d: Doc, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs} = st
  (Unit{}, KSt{n, sl, curl, DCat{cur, d}, out, fns, todo, frames, errs})

# Appends a statement to the current block.
def K.put(d: Doc) -> KM(Unit):
  st => K.put.go(d, st)

def K.putS(s: String) -> KM(Unit):
  K.put(DStr{s})

def K.start.go(+l: U32, st: KSt) -> Unit & KSt:
  KSt{n, sl, +curl, cur, out, fns, todo, frames, errs} = st
  (Unit{}, KSt{n, sl, l, DNil{}, DCat{out, K.block_doc(curl, cur)}, fns, todo, frames, errs})

# Ends the current block and starts block l.
def K.start(+l: U32) -> KM(Unit):
  st => K.start.go(l, st)

def K.error.go(msg: String, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs} = st
  (Unit{}, KSt{n, sl, curl, cur, out, fns, todo, frames, msg <> errs})

def K.error(msg: String) -> KM(Unit):
  st => K.error.go(msg, st)

def S(+k: U32) -> String:
  "KS(" ++ U32.show(k) ++ ")"

def K.frame.go(+l: U32, +size: U32, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs} = st
  (Unit{}, KSt{n, sl, curl, cur, out, fns, todo, Bind{U32.show(l), U32.show((size + 4 : U32))} <> frames, errs})

# Records a function's frame size (header and slots).
def K.frame(+l: U32, +size: U32) -> KM(Unit):
  st => K.frame.go(l, size, st)

def K.take_todo.go(st: KSt) -> List<&2, String> & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs} = st
  (todo, KSt{n, sl, curl, cur, out, fns, Nil{}, frames, errs})

def K.take_todo() -> KM(List<&2, String>):
  st => K.take_todo.go(st)

def K.enter.go(+l: U32, st: KSt) -> U32 & KSt:
  KSt{n, +sl, curl, cur, out, fns, todo, frames, errs} = st
  (sl, KSt{n, 0, curl, cur, out, fns, todo, frames, errs})

# Starts compiling a function at label l; answers the outer slot count.
def K.enter(+l: U32) -> KM(U32):
  do KM<U32>:
    +old : U32 <- st => K.enter.go(l, st)
    return old

def K.leave.go(+old: U32, st: KSt) -> U32 & KSt:
  KSt{n, +sl, curl, cur, out, fns, todo, frames, errs} = st
  (sl, KSt{n, old, curl, cur, out, fns, todo, frames, errs})

# Ends a function: restores the outer slot count, answers this one's.
def K.leave(+old: U32) -> KM(U32):
  st => K.leave.go(old, st)

# The current block, set aside while a nested function compiles.
def K.save.go(st: KSt) -> (U32 & Doc) & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs} = st
  ((curl, cur), KSt{n, sl, 0, DNil{}, out, fns, todo, frames, errs})

def K.save() -> KM(U32 & Doc):
  st => K.save.go(st)

def K.restore.go(r: U32 & Doc, st: KSt) -> Unit & KSt:
  (l, d) = r
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs} = st
  (Unit{}, KSt{n, sl, l, d, DCat{out, K.block_doc(curl, cur)}, fns, todo, frames, errs})

def K.restore(r: U32 & Doc) -> KM(Unit):
  st => K.restore.go(r, st)

law K.expr:
  for +g: G
  for +env: Env()
  for e: Expr
  KM(Doc)

type KSelf is Data:
  KSelf{name: String, entry: U32, mask: List<&2, Bool>}

type KTgt is Data:
  KRet{}
  KSet{slot: U32, merge: U32}

law K.stmt:
  for +g: G
  for +env: Env()
  for +self: KSelf
  for +tgt: KTgt
  for e: Expr
  KM(Unit)

def KSelf.none() -> KSelf:
  KSelf{"", 0, Nil{}}

@unsafe
def K.exprs(+g: G, +env: Env(), xs: List<&2, Expr>) -> KM(List<&2, Doc>):
  match xs:
    case Nil{}:
      KM.pure(List<&2, Doc>, Nil{})
    case h <> t:
      do KM<List<&2, Doc>>:
        d : Doc <- K.expr(g, env, h)
        +k : U32 <- K.slot()
        K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
        ds : List<&2, Doc> <- K.exprs(g, env, t)
        return DStr{S(k)} <> ds

def K.args.put(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"c->H[nf + " ++ U32.show((i + 4 : U32)) ++ "] = "}, d, DStr{";\n"}, K.args.put(t, U32.inc(i))])

# Calls the function at entry with args; the value is in a fresh slot.
def K.invoke(+entry: U32, ds: List<&2, Doc>) -> KM(Doc):
  do KM<Doc>:
    +ret : U32 <- K.fresh()
    K.put(Doc.list([DStr{"{ KW nf = k_push(c, " ++ U32.show(ret) ++ ", K_FRAME[" ++ U32.show(entry) ++ "]);\n"},
      K.args.put(ds, 0), DStr{"c->fp = nf; c->pc = " ++ U32.show(entry) ++ "; }\n"}]))
    K.start(ret)
    +k : U32 <- K.slot()
    K.putS(S(k) ++ " = c->rv;\n")
    return DStr{S(k)}

# Applies a closure to one argument.
def K.apply1(f: Doc, x: Doc) -> KM(Doc):
  do KM<Doc>:
    +ret : U32 <- K.fresh()
    K.put(Doc.list([DStr{"k_call_clo(c, "}, f, DStr{", "}, x, DStr{", " ++ U32.show(ret) ++ ");\n"}]))
    K.start(ret)
    +k : U32 <- K.slot()
    K.putS(S(k) ++ " = c->rv;\n")
    return DStr{S(k)}

def K.apply(xs: List<&2, Doc>, f: Doc) -> KM(Doc):
  match xs:
    case Nil{}:
      KM.pure(Doc, f)
    case h <> t:
      do KM<Doc>:
        r : Doc <- K.apply1(f, h)
        K.apply(t, r)

def K.clo.args(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"c->H[w + " ++ U32.show((i + 3 : U32)) ++ "] = "}, d, DStr{";\n"}, K.clo.args(t, U32.inc(i))])

# A closure of the function at label l over the words ds.
def K.clo(+l: U32, +arity: U32, +ds: List<&2, Doc>) -> KM(Doc):
  +n = Gen.len(ds)
  do KM<Doc>:
    +k : U32 <- K.slot()
    K.put(Doc.list([DStr{"{ KW p = k_alloc(c, " ++ U32.show((n + 3 : U32)) ++ "); KW w = KIX(c, p);\n" ++
      "c->H[w] = KCLO | " ++ U32.show(l) ++ "; c->H[w + 1] = " ++ U32.show(arity) ++ "; c->H[w + 2] = " ++
      U32.show(n) ++ ";\n"}, K.clo.args(ds, 0), DStr{S(k) ++ " = p; }\n"}]))
    return DStr{S(k)}

# A def as a value: a closure of its wrapper, which takes every parameter.
def K.def_value(+name: String, +total: U32) -> KM(Doc):
  do KM<Doc>:
    +w : U32 <- K.fn(K.wrap.name(name))
    K.clo(w, total, Nil{})

def K.call.zero(+name: String) -> KM(Doc):
  do KM<Doc>:
    +e : U32 <- K.fn(name)
    K.invoke(e, Nil{})

# An effect cannot run on the device.
def K.effect() -> KM(Doc):
  do KM<Doc>:
    K.putS("k_fail(c, KE_FX);\n")
    return DStr{"0"}

def K.var.kind(+name: String, kind: Nat, +total: U32) -> KM(Doc):
  match kind:
    case 3n:
      KM.pure(Doc, DStr{"0"})
    case 99n:
      do KM<Doc>:
        K.error("unknown name: " ++ name)
        return DStr{"0"}
    case 1n:
      KM.if(Doc, U32.is_zero(total), K.effect(), K.def_value(name, total))
    case other:
      KM.if(Doc, U32.is_zero(total), K.call.zero(name), K.def_value(name, total))

def K.var.def(+name: String, info: DInfo) -> KM(Doc):
  DInfo{+kind, +mask} = info
  K.var.kind(name, U32.to_nat(kind), U32.from_nat(List.length(&2, Bool, mask)))

def K.var.found(+g: G, +name: String, m: Maybe<&2, String>) -> KM(Doc):
  match m:
    case Some{c}:
      KM.pure(Doc, DStr{c})
    case None{}:
      KM.if(Doc, Str.eq(name, "_"), KM.pure(Doc, DStr{"0"}), K.var.def(name, G.def(g, name)))

def K.var(+g: G, +env: Env(), +name: String) -> KM(Doc):
  K.var.found(g, name, Env.find(env, name))

def K.commas_pre(ds: List<&2, Doc>) -> List<&2, Doc>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Doc.list([DStr{", "}, d]) <> K.commas_pre(t)

# A full call: natives are expressions, effects fail, defs are called.
def K.call.kind(+name: String, kind: Nat, ks: List<&2, Doc>) -> KM(Doc):
  match kind:
    case 3n:
      KM.pure(Doc, DStr{"0"})
    case 2n:
      KM.pure(Doc, Doc.list([DStr{"K" ++ Gen.f(name) ++ "(c"}, Doc.list(K.commas_pre(ks)), DStr{")"}]))
    case 1n:
      K.effect()
    case other:
      do KM<Doc>:
        +e : U32 <- K.fn(name)
        K.invoke(e, ks)

@unsafe
def K.call.full(
  +g: G, +env: Env(), +name: String, +mask: List<&2, Bool>, kind: Nat, kept: List<&2, Expr>, all: List<&2, Expr>,
  extra: List<&2, Expr>, full: Bool
) -> KM(Doc):
  match full:
    case True{}:
      do KM<Doc>:
        ks : List<&2, Doc> <- K.exprs(g, env, kept)
        r : Doc <- K.call.kind(name, kind, ks)
        xs : List<&2, Doc> <- K.exprs(g, env, extra)
        K.apply(xs, r)
    case False{}:
      do KM<Doc>:
        as : List<&2, Doc> <- K.exprs(g, env, all)
        +w : U32 <- K.fn(K.wrap.name(name))
        K.clo(w, U32.from_nat(List.length(&2, Bool, mask)), as)

@unsafe
def K.call.def.kind(
  kind: Nat, +g: G, +env: Env(), +name: String, +mask: List<&2, Bool>, kept: List<&2, Expr>, all: List<&2, Expr>,
  extra: List<&2, Expr>, full: Bool
) -> KM(Doc):
  match kind:
    case 3n:
      KM.pure(Doc, DStr{"0"})
    case 99n:
      do KM<Doc>:
        K.error("unknown function: " ++ name)
        return DStr{"0"}
    case other:
      K.call.full(g, env, name, mask, other, kept, all, extra, full)

@unsafe
def K.call.def.go(+g: G, +env: Env(), +name: String, +mask: List<&2, Bool>, kind: Nat, s: Split) -> KM(Doc):
  Split{kept, all, extra, full} = s
  K.call.def.kind(kind, g, env, name, mask, kept, all, extra, full)

@unsafe
def K.call.def(+g: G, +env: Env(), +name: String, info: DInfo, args: List<&2, Expr>) -> KM(Doc):
  DInfo{kind, +mask} = info
  K.call.def.go(g, env, name, mask, U32.to_nat(kind), Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}))

@unsafe
def K.call.local(+g: G, +env: Env(), f: Expr, args: List<&2, Expr>) -> KM(Doc):
  do KM<Doc>:
    fd : Doc <- K.expr(g, env, f)
    +k : U32 <- K.slot()
    K.put(Doc.list([DStr{S(k) ++ " = "}, fd, DStr{";\n"}]))
    xs : List<&2, Doc> <- K.exprs(g, env, args)
    K.apply(xs, DStr{S(k)})

@unsafe
def K.call.var(+g: G, +env: Env(), +name: String, args: List<&2, Expr>, local: Bool) -> KM(Doc):
  match local:
    case True{}:
      K.call.local(g, env, EVar{name}, args)
    case False{}:
      K.call.def(g, env, name, G.def(g, name), args)

law K.call:
  for +g: G
  for +env: Env()
  for f: Expr
  for args: List<&2, Expr>
  KM(Doc)

# A !-call on the device is a call.
@unsafe
def K.call.bang(+g: G, +env: Env(), args: List<&2, Expr>) -> KM(Doc):
  match args:
    case f <> xs:
      K.call(g, env, f, xs)
    case Nil{}:
      KM.pure(Doc, DStr{"0"})

@unsafe
def K.call(g, env, f, args):
  match f:
    case EVar{"%gpu"}:
      K.call.bang(g, env, args)
    case EVar{+name}:
      K.call.var(g, env, name, args, Env.has(env, name))
    case other:
      K.call.local(g, env, other, args)

def K.ctor.fields(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"c->H[w + " ++ U32.show(U32.inc(i)) ++ "] = "}, d, DStr{";\n"}, K.ctor.fields(t, U32.inc(i))])

def K.ctor.kind(+tag: U32, kind: Nat, +ds: List<&2, Doc>) -> KM(Doc):
  match kind:
    case 0n:
      do KM<Doc>:
        +k : U32 <- K.slot()
        K.put(Doc.list([DStr{"{ KW p = k_node(c, " ++ U32.show(tag) ++ ", " ++ U32.show(Gen.len(ds)) ++
          "); KW w = KIX(c, p);\n"}, K.ctor.fields(ds, 0), DStr{S(k) ++ " = p; }\n"}]))
        return DStr{S(k)}
    case 1n:
      KM.pure(Doc, DStr{"KIMM(" ++ U32.show(tag) ++ ")"})
    case 2n:
      KM.pure(Doc, Doc.list(ds))
    case 3n:
      KM.pure(Doc, DStr{"0"})
    case 4n+p:
      KM.pure(Doc, Doc.list([DStr{"k_nat_add(c, "}, Doc.list(ds), DStr{", 1)"}]))

@unsafe
def K.ctor(+g: G, +env: Env(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Expr>) -> KM(Doc):
  match info:
    case None{}:
      do KM<Doc>:
        K.error("unknown constructor: " ++ name)
        return DStr{"0"}
    case Some{CInfo{tag, ar, kind, single}}:
      do KM<Doc>:
        ds : List<&2, Doc> <- K.exprs(g, env, args)
        K.ctor.kind(tag, U32.to_nat(kind), ds)

# A string literal, built cell by cell from its end.
def K.str.cells(cs: List<&2, U32>) -> Doc:
  match cs:
    case Nil{}:
      DNil{}
    case x <> t:
      Doc.list([K.str.cells(t), DStr{"{ KW p = k_node(c, 1, 2); c->H[KIX(c, p) + 1] = " ++ U32.show(x) ++
        "; c->H[KIX(c, p) + 2] = r; r = p; }\n"}])

def K.str(s: String) -> KM(Doc):
  do KM<Doc>:
    +k : U32 <- K.slot()
    K.put(Doc.list([DStr{"{ KW r = KIMM(0);\n"}, K.str.cells(Str.codes32(s)), DStr{S(k) ++ " = r; }\n"}]))
    return DStr{S(k)}

law K.lam:
  for +g: G
  for +env: Env()
  for +p: Pat
  for +body: Expr
  KM(Doc)

@unsafe
def K.block(+g: G, +env: Env(), e: Expr) -> KM(Doc):
  do KM<Doc>:
    +k : U32 <- K.slot()
    +m : U32 <- K.fresh()
    K.stmt(g, env, KSelf.none(), KSet{k, m}, e)
    K.start(m)
    return DStr{S(k)}

@unsafe
def K.expr(g, env, e):
  match e:
    case EVar{name}:
      K.var(g, env, name)
    case ENum{n}:
      KM.pure(Doc, DStr{U32.show(n) ++ "u"})
    case ENat{n}:
      KM.pure(Doc, DStr{U32.show(n) ++ "u"})
    case EFlt{s}:
      KM.pure(Doc, DStr{"KUF(" ++ s ++ "f)"})
    case EStr{s}:
      K.str(s)
    case ECall{f, args}:
      K.call(g, env, f, args)
    case ECtor{+name, args}:
      K.ctor(g, env, name, G.ctor(g, name), args)
    case ELam{p, body}:
      K.lam(g, env, p, body)
    case ELet{p, v, body}:
      K.block(g, env, ELet{p, v, body})
    case EMatch{scrs, cases}:
      K.block(g, env, EMatch{scrs, cases})
    case ESucc{k, x}:
      do KM<Doc>:
        d : Doc <- K.expr(g, env, x)
        return Doc.list([DStr{"k_nat_add(c, "}, d, DStr{", " ++ U32.show(k) ++ ")"}])
    case ETy{n, targs}:
      KM.pure(Doc, DStr{"0"})
    case EErr{m}:
      do KM<Doc>:
        K.error("parse error: " ++ m)
        return DStr{"0"}
    case other:
      do KM<Doc>:
        K.error("unexpected expression: " ++ Expr.show(other))
        return DStr{"0"}

def K.caps.inner(caps: Env(), +i: U32) -> Env():
  match caps:
    case Nil{}:
      Nil{}
    case Bind{x, c} <> t:
      Bind{x, S(i)} <> K.caps.inner(t, U32.inc(i))

def K.caps.outer(caps: Env()) -> List<&2, Doc>:
  match caps:
    case Nil{}:
      Nil{}
    case Bind{x, c} <> t:
      DStr{c} <> K.caps.outer(t)

def K.slots.go(+n: U32, st: KSt) -> U32 & KSt:
  KSt{m, sl, curl, cur, out, fns, todo, frames, errs} = st
  (n, KSt{m, (sl + n : U32), curl, cur, out, fns, todo, frames, errs})

# Takes n slots (a function's parameters); answers n.
def K.slots(+n: U32) -> KM(U32):
  st => K.slots.go(n, st)

law K.pat:
  for +g: G
  for p: Pat
  for +path: String
  for r: PatR
  PatR

# A lambda: a function over its captures and its argument (slots 0..n).
@unsafe
def K.lam(g, env, p, body):
  +caps = Gen.caps(FV.expr(body, Pat.vars(p, Nil{}), Nil{}), env)
  +n = U32.from_nat(List.length(&2, Bind, caps))
  do KM<Doc>:
    +l : U32 <- K.fresh()
    saved : U32 & Doc <- K.save()
    +old : U32 <- K.enter(l)
    +arg : U32 <- K.slots(U32.inc(n))
    +binds : Env() <- KM.pure(Env(), PatR.binds(K.pat(g, p, S(n), PatR{Nil{}, Nil{}})))
    K.start(l)
    K.stmt(g, List.append(&2, Bind, binds, K.caps.inner(caps, 0)), KSelf.none(), KRet{}, body)
    +size : U32 <- K.leave(old)
    K.frame(l, size)
    K.restore(saved)
    K.clo(l, U32.inc(n), K.caps.outer(caps))

@unsafe
def K.pat.fields(+g: G, args: List<&2, Pat>, +path: String, +i: U32, r: PatR) -> PatR:
  match args:
    case Nil{}:
      r
    case h <> t:
      K.pat.fields(g, t, path, U32.inc(i), K.pat(g, h,
        Bool.pick(String, U32.is_eq(i, 99), path, "KFLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), r))

@unsafe
def K.pat.kind(+g: G, kind: Nat, +tag: U32, +single: Bool, args: List<&2, Pat>, +path: String, r: PatR) -> PatR:
  match kind:
    case 0n:
      K.pat.fields(g, args, path, 0, Gen.pat.tag(single, "KTAG(" ++ path ++ ") == " ++ U32.show(tag), r))
    case 1n:
      Gen.pat.tag(single, "(" ++ path ++ ") == KIMM(" ++ U32.show(tag) ++ ")", r)
    case 2n:
      K.pat.fields(g, args, path, 99, r)
    case 3n:
      Gen.pat.cond("(" ++ path ++ ") == 0", r)
    case 4n+p:
      K.pat.fields(g, args, "((" ++ path ++ ") - 1)", 99, Gen.pat.cond("k_nz(c, " ++ path ++ ")", r))

@unsafe
def K.pat.ctor(+g: G, info: Maybe<&2, CInfo>, name: String, args: List<&2, Pat>, +path: String, r: PatR) -> PatR:
  match info:
    case None{}:
      Gen.pat.cond("0", r)
    case Some{CInfo{+tag, ar, +kind, +single}}:
      K.pat.kind(g, U32.to_nat(kind), tag, single, args, path, r)

@unsafe
def K.pat(g, p, path, r):
  match p:
    case PVar{x}:
      Gen.pat.var(x, path, r)
    case PCtor{+name, args}:
      K.pat.ctor(g, G.ctor(g, name), name, args, path, r)
    case PNat{n}:
      Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
    case PSucc{+k, q}:
      K.pat(g, q, "((" ++ path ++ ") - " ++ U32.show(k) ++ ")", Gen.pat.cond("k_nge(c, " ++ path ++ ", " ++ U32.show(k) ++ ")", r))
    case PNum{n}:
      Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)

@unsafe
def K.pats(+g: G, ps: List<&2, Pat>, paths: List<&2, String>, r: PatR) -> PatR:
  match ps paths:
    case p <> pt c <> ct:
      K.pats(g, pt, ct, K.pat(g, p, c, r))
    case pl cl:
      r

def K.ret(t: KTgt, d: Doc) -> KM(Unit):
  match t:
    case KRet{}:
      K.put(Doc.list([DStr{"k_ret(c, "}, d, DStr{");\n"}]))
    case KSet{k, m}:
      K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\nc->pc = " ++ U32.show(m) ++ ";\n"}]))

def K.tail.set(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{S(i) ++ " = "}, d, DStr{"; "}, K.tail.set(t, U32.inc(i))])

# A self tail call: the arguments (already in slots) become the parameters.
@unsafe
def K.tail(+g: G, +env: Env(), +entry: U32, s: Split) -> KM(Unit):
  Split{kept, all, extra, full} = s
  do KM<Unit>:
    ds : List<&2, Doc> <- K.exprs(g, env, kept)
    K.put(Doc.list([DStr{"{ "}, K.tail.set(ds, 0), DStr{"c->pc = " ++ U32.show(entry) ++ "; }\n"}]))

def K.is_ret(t: KTgt) -> Bool:
  match t:
    case KRet{}:
      True{}
    case KSet{k, m}:
      False{}

def KSelf.is_tail(+env: Env(), +self: KSelf, +tgt: KTgt, +name: String, +args: List<&2, Expr>) -> Bool:
  KSelf{+sn, e, +mask} = self
  Bool.and(Bool.and(K.is_ret(tgt), Str.eq(sn, name)), Bool.and(Bool.not(Env.has(env, name)),
    Nat.is_eq(List.length(&2, Bool, mask), List.length(&2, Expr, args))))

@unsafe
def K.tail.self(+g: G, +env: Env(), self: KSelf, args: List<&2, Expr>) -> KM(Unit):
  KSelf{sn, +entry, +mask} = self
  K.tail(g, env, entry, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}))

@unsafe
def K.stmt.call(+g: G, +env: Env(), +self: KSelf, +tgt: KTgt, +name: String, args: List<&2, Expr>, tail: Bool) ->
  KM(Unit):
  match tail:
    case True{}:
      K.tail.self(g, env, self, args)
    case False{}:
      do KM<Unit>:
        d : Doc <- K.call(g, env, EVar{name}, args)
        K.ret(tgt, d)

@unsafe
def K.let.var(+g: G, +env: Env(), +self: KSelf, +tgt: KTgt, +x: String, v: Expr, body: Expr) -> KM(Unit):
  do KM<Unit>:
    d : Doc <- K.expr(g, env, v)
    +k : U32 <- K.slot()
    K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
    K.stmt(g, Bool.pick(Env(), Str.eq(x, "_"), env, Bind{x, S(k)} <> env), self, tgt, body)

@unsafe
def K.let.pat(+g: G, +env: Env(), +self: KSelf, +tgt: KTgt, +p: Pat, v: Expr, body: Expr) -> KM(Unit):
  do KM<Unit>:
    d : Doc <- K.expr(g, env, v)
    +k : U32 <- K.slot()
    K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
    +binds : Env() <- KM.pure(Env(), PatR.binds(K.pat(g, p, S(k), PatR{Nil{}, Nil{}})))
    K.stmt(g, List.append(&2, Bind, binds, env), self, tgt, body)

#
# Each value becomes a thunk (a closure). Below the fork limit the thunks
# but the last go to the queue, the last runs here, and a join record
# collects the values; the lane that brings the last value continues. Past
# the limit they run one after the other.
@unsafe
def K.par.thunks(+g: G, +env: Env(), vs: List<&2, Expr>) -> KM(List<&2, U32>):
  match vs:
    case Nil{}:
      KM.pure(List<&2, U32>, Nil{})
    case v <> t:
      do KM<List<&2, U32>>:
        d : Doc <- K.lam(g, env, PVar{"_"}, v)
        +k : U32 <- K.slot()
        K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
        ks : List<&2, U32> <- K.par.thunks(g, env, t)
        return k <> ks

# Past the fork limit the values are evaluated one after the other.
@unsafe
def K.par.seq(+g: G, +env: Env(), vs: List<&2, Expr>, rs: List<&2, U32>) -> KM(Unit):
  match vs rs:
    case v <> vt +r <> rt:
      do KM<Unit>:
        x : Doc <- K.expr(g, env, v)
        K.put(Doc.list([DStr{S(r) ++ " = "}, x, DStr{";\n"}]))
        K.par.seq(g, env, vt, rt)
    case a b:
      KM.pure(Unit, Unit{})

def K.par.push(thunks: List<&2, U32>, +j: U32, +i: U32) -> Doc:
  match thunks:
    case Nil{}:
      DNil{}
    case t <> Nil{}:
      DNil{}
    case t <> rest:
      Doc.list([DStr{"if (!k_push_task(c, PC_TASK, " ++ S(j) ++ ", " ++ S(t) ++ ", (c->dep + 1) | ((KW)" ++ U32.show(i) ++
        " << 32))) k_fail(c, KE_QUEUE);\n"}, K.par.push(rest, j, U32.inc(i))])

def K.par.collect(rs: List<&2, U32>, +j: U32, +i: U32) -> Doc:
  match rs:
    case Nil{}:
      DNil{}
    case r <> t:
      Doc.list([DStr{S(r) ++ " = c->H[" ++ S(j) ++ " + " ++ U32.show((i + 4 : U32)) ++ "];\n"}, K.par.collect(t, j, U32.inc(i))])

@unsafe
def K.par.env(+g: G, ps: List<&2, Pat>, rs: List<&2, U32>, +env: Env()) -> Env():
  match ps rs:
    case p <> pt +r <> rt:
      K.par.env(g, pt, rt, List.append(&2, Bind, PatR.binds(K.pat(g, p, S(r), PatR{Nil{}, Nil{}})), env))
    case a b:
      env

def K.newslots(n: Nat) -> KM(List<&2, U32>):
  match n:
    case 0n:
      KM.pure(List<&2, U32>, Nil{})
    case 1n+m:
      do KM<List<&2, U32>>:
        +k : U32 <- K.slot()
        ks : List<&2, U32> <- K.newslots(m)
        return k <> ks

def List.last_u32(xs: List<&2, U32>) -> U32:
  match xs:
    case Nil{}:
      0
    case x <> Nil{}:
      x
    case x <> t:
      List.last_u32(t)

@unsafe
def K.par(+g: G, +env: Env(), +self: KSelf, +tgt: KTgt, +ps: List<&2, Pat>, +vs: List<&2, Expr>, body: Expr) -> KM(Unit):
  +n = List.length(&2, Expr, vs)
  do KM<Unit>:
    +rs : List<&2, U32> <- K.newslots(n)
    +j : U32 <- K.slot()
    +lpar : U32 <- K.fresh()
    +lseq : U32 <- K.fresh()
    +lcont : U32 <- K.fresh()
    +lbody : U32 <- K.fresh()
    K.putS("c->pc = c->dep < c->P->fork_limit ? " ++ U32.show(lpar) ++ " : " ++ U32.show(lseq) ++ ";\n")
    K.start(lseq)
    K.par.seq(g, env, vs, rs)
    K.putS("c->pc = " ++ U32.show(lbody) ++ ";\n")
    K.start(lpar)
    +thunks : List<&2, U32> <- K.par.thunks(g, env, vs)
    K.putS(S(j) ++ " = k_join_new(c, " ++ U32.show(U32.from_nat(n)) ++ ", " ++ U32.show(lcont) ++ ");\n")
    K.put(K.par.push(thunks, j, 0))
    K.putS("c->dep += 1;\n")
    x : Doc <- K.apply1(DStr{S(List.last_u32(thunks))}, DStr{"0"})
    K.put(Doc.list([DStr{"k_arrive(c, " ++ S(j) ++ ", " ++ U32.show(U32.from_nat(Nat.sub(n, 1n))) ++ ", "}, x,
      DStr{");\n"}]))
    K.start(lcont)
    K.put(K.par.collect(rs, j, 0))
    K.putS("c->pc = " ++ U32.show(lbody) ++ ";\n")
    K.start(lbody)
    K.stmt(g, K.par.env(g, ps, rs, env), self, tgt, body)

@unsafe
def K.let.par(+g: G, +env: Env(), +self: KSelf, +tgt: KTgt, ps: List<&2, Pat>, v: Expr, body: Expr) -> KM(Unit):
  match v:
    case ECtor{n, vs}:
      K.par(g, env, self, tgt, ps, vs, body)
    case other:
      K.par(g, env, self, tgt, ps, [other], body)

@unsafe
def K.let.ctor(
  +g: G, +env: Env(), +self: KSelf, +tgt: KTgt, name: String, ps: List<&2, Pat>, v: Expr, body: Expr, par: Bool
) -> KM(Unit):
  match par:
    case True{}:
      K.let.par(g, env, self, tgt, ps, v, body)
    case False{}:
      K.let.pat(g, env, self, tgt, PCtor{name, ps}, v, body)

@unsafe
def K.let(+g: G, +env: Env(), +self: KSelf, +tgt: KTgt, p: Pat, v: Expr, body: Expr) -> KM(Unit):
  match p:
    case PVar{+x}:
      K.let.var(g, env, self, tgt, x, v, body)
    case PCtor{+name, ps}:
      K.let.ctor(g, env, self, tgt, name, ps, v, body, Str.eq(name, "%par"))
    case other:
      K.let.pat(g, env, self, tgt, other, v, body)

type KCase is Data:
  KCase{label: U32, conds: List<&2, String>, env: Env(), body: Expr}

law K.cases:
  for +g: G
  for +env: Env()
  for +cs: List<&2, String>
  for cases: List<&2, Expr>
  KM(List<&2, KCase>)

@unsafe
def K.cases(g, env, cs, cases):
  match cases:
    case Nil{}:
      KM.pure(List<&2, KCase>, Nil{})
    case ECase{ps, body} <> t:
      +pr = K.pats(g, ps, cs, PatR{Nil{}, Nil{}})
      do KM<List<&2, KCase>>:
        +l : U32 <- K.fresh()
        rest : List<&2, KCase> <- K.cases(g, env, cs, t)
        return KCase{l, List.reverse(&2, String, PatR.conds(pr)), List.append(&2, Bind, PatR.binds(pr), env), body} <> rest
    case other <> t:
      K.cases(g, env, cs, t)

def K.dispatch(cases: List<&2, KCase>) -> Doc:
  match cases:
    case Nil{}:
      DStr{"{ k_fail(c, KE_MATCH); }\n"}
    case KCase{l, conds, env, b} <> t:
      Doc.list([DStr{"if (" ++ Gen.and(conds) ++ ") { c->pc = " ++ U32.show(l) ++ "; } else "}, K.dispatch(t)])

@unsafe
def K.bodies(+g: G, +self: KSelf, +tgt: KTgt, cases: List<&2, KCase>) -> KM(Unit):
  match cases:
    case Nil{}:
      KM.pure(Unit, Unit{})
    case KCase{+l, conds, +env, body} <> t:
      do KM<Unit>:
        K.start(l)
        K.stmt(g, env, self, tgt, body)
        K.bodies(g, self, tgt, t)

def K.doc_strs(ds: List<&2, Doc>) -> List<&2, String>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Doc.flat(d) <> K.doc_strs(t)

@unsafe
def K.match(+g: G, +env: Env(), +self: KSelf, +tgt: KTgt, scrs: List<&2, Expr>, cases: List<&2, Expr>) -> KM(Unit):
  do KM<Unit>:
    ds : List<&2, Doc> <- K.exprs(g, env, scrs)
    +cs : List<&2, KCase> <- K.cases(g, env, K.doc_strs(ds), cases)
    K.put(K.dispatch(cs))
    K.bodies(g, self, tgt, cs)

@unsafe
def K.stmt(g, env, self, tgt, e):
  match e:
    case ELet{p, v, body}:
      K.let(g, env, self, tgt, p, v, body)
    case EMatch{scrs, cases}:
      K.match(g, env, self, tgt, scrs, cases)
    case ECall{EVar{+name}, +args}:
      K.stmt.call(g, env, self, tgt, name, args, KSelf.is_tail(env, self, tgt, name, args))
    case other:
      do KM<Unit>:
        d : Doc <- K.expr(g, env, other)
        K.ret(tgt, d)

def K.sig.env(ps: List<&2, Param>, mask: List<&2, Bool>, +i: U32) -> Env():
  match ps mask:
    case Param{x, m, t} <> pt True{} <> mt:
      Bind{x, S(i)} <> K.sig.env(pt, mt, U32.inc(i))
    case Param{x, m, t} <> pt False{} <> mt:
      Bind{x, "0"} <> K.sig.env(pt, mt, i)
    case pl ml:
      Nil{}

def K.def.body(+g: G, +name: String, +l: U32, +mask: List<&2, Bool>, ps: List<&2, Param>, body: Expr) -> KM(Unit):
  do KM<Unit>:
    +old : U32 <- K.enter(l)
    +np : U32 <- K.slots(K.kept(mask))
    K.start(l)
    K.stmt(g, K.sig.env(ps, mask, 0), KSelf{name, l, mask}, KRet{}, R.ops(body, "Nat"))
    +size : U32 <- K.leave(old)
    K.frame(l, size)

# A def's wrapper: every parameter a slot, calling the def with the kept ones.
def K.wrap.args(mask: List<&2, Bool>, +i: U32) -> List<&2, Doc>:
  match mask:
    case Nil{}:
      Nil{}
    case True{} <> t:
      DStr{S(i)} <> K.wrap.args(t, U32.inc(i))
    case False{} <> t:
      K.wrap.args(t, U32.inc(i))

def K.wrapper(+name: String, +l: U32, +mask: List<&2, Bool>, kind: Nat) -> KM(Unit):
  do KM<Unit>:
    +old : U32 <- K.enter(l)
    +np : U32 <- K.slots(U32.from_nat(List.length(&2, Bool, mask)))
    K.start(l)
    r : Doc <- K.call.kind(name, kind, K.wrap.args(mask, 0))
    K.put(Doc.list([DStr{"k_ret(c, "}, r, DStr{");\n"}]))
    +size : U32 <- K.leave(old)
    K.frame(l, size)

def K.def.decl.def(kind: Nat, +g: G, +name: String, +l: U32, +mask: List<&2, Bool>, ps: List<&2, Param>, body: Expr) ->
  KM(Unit):
  match kind:
    case 0n:
      K.def.body(g, name, l, mask, ps, body)
    case other:
      K.wrapper(name, l, mask, other)

def K.def.decl.go(d: Decl, +g: G, +name: String, +l: U32, kind: Nat, +mask: List<&2, Bool>) -> KM(Unit):
  match d:
    case DDef{n, ps, body, ret}:
      K.def.decl.def(kind, g, name, l, mask, ps, body)
    case other:
      K.wrapper(name, l, mask, kind)

def K.def.decl(+g: G, +name: String, +l: U32, info: DInfo, d: Decl) -> KM(Unit):
  DInfo{kind, mask} = info
  K.def.decl.go(d, g, name, l, U32.to_nat(kind), mask)

def K.one.wrap.go(+name: String, +l: U32, info: DInfo) -> KM(Unit):
  DInfo{kind, +mask} = info
  K.wrapper(name, l, mask, U32.to_nat(kind))

def K.one.wrap(+g: G, +name: String, +l: U32) -> KM(Unit):
  K.one.wrap.go(name, l, G.def(g, name))

# Compiles one queued function (a def, or "%wrap name").
def K.one(+g: G, +key: String, +l: U32) -> KM(Unit):
  KM.if(Unit, String.starts_with(key, "%wrap "), K.one.wrap(g, String.drop(key, 6n), l), K.def.decl(g, key, l,
    G.def(g, key), G.body(g, key)))

def K.label.go(+name: String, st: KSt) -> U32 & KSt:
  KSt{n, sl, curl, cur, out, +fns, todo, frames, errs} = st
  (Maybe.default(&2, U32, U32.read(Maybe.default(&2, String, Env.find(fns, name), "0")), 0),
    KSt{n, sl, curl, cur, out, fns, todo, frames, errs})

def K.label(+name: String) -> KM(U32):
  st => K.label.go(name, st)

@unsafe
def K.all.list(+g: G, fuel: Nat, todo: List<&2, String>) -> KM(Unit):
  match todo:
    case Nil{}:
      KM.pure(Unit, Unit{})
    case +h <> t:
      do KM<Unit>:
        +l : U32 <- K.label(h)
        K.one(g, h, l)
        more : List<&2, String> <- K.take_todo()
        K.all.list(g, fuel, List.append(&2, String, t, more))

# Compiles queued functions until none is left.
@unsafe
def K.all(g, fuel):
  match fuel:
    case 0n:
      KM.pure(Unit, Unit{})
    case 1n+f:
      do KM<Unit>:
        todo : List<&2, String> <- K.take_todo()
        K.all.list(g, f, todo)

# The frame table and the entry labels the host needs.
def K.frame_of(frames: List<&2, Bind>, +l: U32) -> String:
  Maybe.default(&2, String, Env.find(frames, U32.show(l)), "0")

@unsafe
def K.frame_table.go(+frames: List<&2, Bind>, +l: U32, +n: U32, done: Bool) -> String:
  match done:
    case True{}:
      ""
    case False{}:
      K.frame_of(frames, l) ++ "u, " ++ K.frame_table(frames, U32.inc(l), n)

@unsafe
def K.frame_table(frames, l, n):
  K.frame_table.go(frames, l, n, U32.is_ge(l, n))

def Path.base(+p: String) -> String:
  String.drop(p, String.length(Mod.dir(p)))

def CS.book(+st: CS) -> Chk.Book:
  CS{+book, seen, n0} = st
  book

def J.opt(m: Map<&2, JCI>) -> Map<&2, Maybe<&2, JCI>>:
  match m:
    case MTip{}:
      MTip{}
    case MLeaf{k, v}:
      MLeaf{k, Some{v}}
    case MNode{p, lo, hi}:
      MNode{p, J.opt(lo), J.opt(hi)}

def J.ctor(+j: JG, +name: String) -> Maybe<&2, JCI>:
  JG{g, +jm} = j
  Pair.snd(Map<&2, Maybe<&2, JCI>>, Maybe<&2, JCI>,
    Map.get(Maybe<&2, JCI>, None{}, J.opt(jm), name))

# How a type's values are represented: 0 an object, 1 a boolean, 2 a
# BigInt (Nat), 3 a string (String), 4 a one-code-point string (Char).
def J.kind(+ty: String) -> Nat:
  P.which(ty, ["", "Bool", "Nat", "String", "Char"])

def J.nth(xs: List<&2, String>, n: Nat) -> String:
  match xs n:
    case x <> t 0n:
      x
    case x <> t 1n+m:
      J.nth(t, m)
    case Nil{} k:
      "_"

@unsafe
def J.hex.more(+n: U32, acc: String, last: Bool) -> String:
  match last:
    case True{}:
      acc
    case False{}:
      J.hex.go((n >> 4n : U32), acc)

@unsafe
def J.hex.go(n, acc):
  +d = (n .&. 15 : U32)
  +c = Str.chr(Bool.pick(U32, U32.is_lt(d, 10), (48 + d : U32), (87 + d : U32)))
  J.hex.more(n, c ++ acc, U32.is_lt(n, 16))

def J.str(s: String) -> Doc:
  DStr{"\"" ++ J.lit(s) ++ "\""}

law J.pat:
  for +j: JG
  for p: Pat
  for +path: String
  for r: PatR
  PatR

@unsafe
def J.pat.fields(+j: JG, args: List<&2, Pat>, +paths: List<&2, String>, r: PatR) -> PatR:
  match args paths:
    case a <> at +p <> pt:
      J.pat.fields(j, at, pt, J.pat(j, a, p, r))
    case x y:
      r

def J.paths(+path: String, fs: List<&2, String>) -> List<&2, String>:
  match fs:
    case Nil{}:
      Nil{}
    case f <> t:
      ("(" ++ path ++ ")." ++ f) <> J.paths(path, t)

@unsafe
def J.pat.kind(
  +j: JG, kind: Nat, +name: String, args: List<&2, Pat>, +path: String, fs: List<&2, String>, single: Bool, +r: PatR
) -> PatR:
  match kind:
    case 1n:
      Gen.pat.cond("(" ++ path ++ ") === " ++ Bool.pick(String, Str.eq(name, "True"), "true", "false"), r)
    case 2n:
      Bool.pick(PatR, Str.eq(name, "Zero"), Gen.pat.cond("(" ++ path ++ ") === 0n", r),
        J.pat.fields(j, args, ["((" ++ path ++ ") - 1n)"], Gen.pat.cond("(" ++ path ++ ") > 0n", r)))
    case 3n:
      Bool.pick(PatR, Str.eq(name, "SNil"), Gen.pat.cond("(" ++ path ++ ") === \"\"", r),
        J.pat.fields(j, args, ["str_head(" ++ path ++ ")", "str_tail(" ++ path ++ ")"],
          Gen.pat.cond("(" ++ path ++ ") !== \"\"", r)))
    case 4n:
      J.pat.fields(j, args, ["(" ++ path ++ ").codePointAt(0)"], r)
    case other:
      J.pat.fields(j, args, J.paths(path, fs), Gen.pat.tag(single, "(" ++ path ++ ").$ === \"" ++ name ++ "\"", r))

@unsafe
def J.pat.ctor(+j: JG, info: Maybe<&2, JCI>, +name: String, args: List<&2, Pat>, +path: String, r: PatR) -> PatR:
  match info:
    case None{}:
      Gen.pat.cond("false /* unknown constructor " ++ name ++ " */", r)
    case Some{JCI{+ty, fs, single}}:
      J.pat.kind(j, J.kind(ty), name, args, path, fs, single, r)

law J.expr:
  for +j: JG
  for +env: Env()
  for e: Expr
  Gen(Doc)

@unsafe
def J.exprs(+j: JG, +env: Env(), xs: List<&2, Expr>) -> Gen(List<&2, Doc>):
  match xs:
    case Nil{}:
      Gen.pure(List<&2, Doc>, Nil{})
    case h <> t:
      do Gen<List<&2, Doc>>:
        d : Doc <- J.expr(j, env, h)
        ds : List<&2, Doc> <- J.exprs(j, env, t)
        return d <> ds

def J.obj.fields(fs: List<&2, String>, ds: List<&2, Doc>) -> List<&2, Doc>:
  match fs ds:
    case f <> ft d <> dt:
      Doc.list([DStr{", " ++ f ++ ": "}, d]) <> J.obj.fields(ft, dt)
    case a b:
      Nil{}

def J.ctor.kind(kind: Nat, +name: String, fs: List<&2, String>, ds: List<&2, Doc>) -> Doc:
  match kind:
    case 1n:
      DStr{Bool.pick(String, Str.eq(name, "True"), "true", "false")}
    case 2n:
      Bool.pick(Doc, Str.eq(name, "Zero"), DStr{"0n"}, Doc.list([DStr{"("}, Doc.list(ds), DStr{" + 1n)"}]))
    case 3n:
      Bool.pick(Doc, Str.eq(name, "SNil"), DStr{"\"\""}, Doc.list([DStr{"str_cons("}, Gen.commas(ds), DStr{")"}]))
    case 4n:
      Doc.list([DStr{"char_new("}, Doc.list(ds), DStr{")"}])
    case other:
      Doc.list([DStr{"({$: \"" ++ name ++ "\""}, Doc.list(J.obj.fields(fs, ds)), DStr{"})"}])

@unsafe
def J.ctor.build(+j: JG, +env: Env(), +name: String, info: Maybe<&2, JCI>, args: List<&2, Expr>) -> Gen(Doc):
  match info:
    case None{}:
      do Gen<Doc>:
        Gen.error("unknown constructor: " ++ name)
        return DStr{"null"}
    case Some{JCI{+ty, fs, single}}:
      do Gen<Doc>:
        ds : List<&2, Doc> <- J.exprs(j, env, args)
        return J.ctor.kind(J.kind(ty), name, fs, ds)

@unsafe
def J.pat(j, p, path, r):
  match p:
    case PVar{x}:
      Gen.pat.var(x, path, r)
    case PCtor{+name, args}:
      J.pat.ctor(j, J.ctor(j, name), name, args, path, r)
    case PNat{n}:
      Gen.pat.cond("(" ++ path ++ ") === " ++ U32.show(n) ++ "n", r)
    case PSucc{+k, q}:
      J.pat(j, q, "((" ++ path ++ ") - " ++ U32.show(k) ++ "n)",
        Gen.pat.cond("(" ++ path ++ ") >= " ++ U32.show(k) ++ "n", r))
    case PNum{n}:
      Gen.pat.cond("(" ++ path ++ ") === " ++ U32.show(n), r)

@unsafe
def J.pats(+j: JG, ps: List<&2, Pat>, paths: List<&2, String>, r: PatR) -> PatR:
  match ps paths:
    case p <> pt c <> ct:
      J.pats(j, pt, ct, J.pat(j, p, c, r))
    case pl cl:
      r

law J.stmt:
  for +j: JG
  for +env: Env()
  for +self: Self
  for +tgt: Tgt
  for e: Expr
  Gen(Doc)

# Applies a curried function to arguments, one at a time.
def J.apply(xs: List<&2, Doc>, f: Doc) -> Doc:
  match xs:
    case Nil{}:
      f
    case h <> t:
      J.apply(t, Doc.list([f, DStr{"("}, h, DStr{")"}]))

def J.var.kind(+name: String, kind: Nat, +total: U32) -> Gen(Doc):
  match kind:
    case 3n:
      Gen.pure(Doc, DStr{"null"})
    case 99n:
      do Gen<Doc>:
        Gen.error("unknown name: " ++ name)
        return DStr{"null"}
    case other:
      do Gen<Doc>:
        Gen.ref(name)
        Gen.clo(name)
        return Bool.pick(Doc, U32.is_zero(total), DStr{Gen.f(name) ++ "()"}, DStr{Gen.w(name)})

def J.var.def(+name: String, info: DInfo) -> Gen(Doc):
  DInfo{+kind, +mask} = info
  J.var.kind(name, U32.to_nat(kind), U32.from_nat(List.length(&2, Bool, mask)))

def J.var.found(+j: JG, +name: String, m: Maybe<&2, String>) -> Gen(Doc):
  match m:
    case Some{c}:
      Gen.pure(Doc, DStr{c})
    case None{}:
      Bool.pick(Gen(Doc), Str.eq(name, "_"), Gen.pure(Doc, DStr{"null"}), J.var.def(name, G.def(JG.g(j), name)))

def J.var(+j: JG, +env: Env(), +name: String) -> Gen(Doc):
  J.var.found(j, name, Env.find(env, name))

def J.nulls(all: List<&2, Expr>) -> List<&2, Expr>:
  all

@unsafe
def J.call.full(
  +j: JG, +env: Env(), +name: String, kept: List<&2, Expr>, all: List<&2, Expr>, extra: List<&2, Expr>, full: Bool
) -> Gen(Doc):
  match full:
    case True{}:
      do Gen<Doc>:
        ks : List<&2, Doc> <- J.exprs(j, env, kept)
        xs : List<&2, Doc> <- J.exprs(j, env, extra)
        return J.apply(xs, Doc.list([DStr{Gen.f(name) ++ "("}, Gen.commas(ks), DStr{")"}]))
    case False{}:
      do Gen<Doc>:
        as : List<&2, Doc> <- J.exprs(j, env, all)
        return J.apply(as, DStr{Gen.w(name)})

@unsafe
def J.call.split(+j: JG, +env: Env(), +name: String, s: Split) -> Gen(Doc):
  Split{kept, all, extra, full} = s
  J.call.full(j, env, name, kept, all, extra, full)

@unsafe
def J.call.kind(+j: JG, +env: Env(), +name: String, kind: Nat, s: Split) -> Gen(Doc):
  match kind:
    case 3n:
      Gen.pure(Doc, DStr{"null"})
    case 99n:
      do Gen<Doc>:
        Gen.error("unknown function: " ++ name)
        return DStr{"null"}
    case other:
      do Gen<Doc>:
        Gen.ref(name)
        J.call.split(j, env, name, s)

@unsafe
def J.call.def(+j: JG, +env: Env(), +name: String, info: DInfo, args: List<&2, Expr>) -> Gen(Doc):
  DInfo{kind, +mask} = info
  J.call.kind(j, env, name, U32.to_nat(kind), Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}))

@unsafe
def J.call.local(+j: JG, +env: Env(), f: Expr, args: List<&2, Expr>) -> Gen(Doc):
  do Gen<Doc>:
    fd : Doc <- J.expr(j, env, f)
    xs : List<&2, Doc> <- J.exprs(j, env, args)
    return J.apply(xs, Doc.list([DStr{"("}, fd, DStr{")"}]))

@unsafe
def J.call.var(+j: JG, +env: Env(), +name: String, args: List<&2, Expr>, local: Bool) -> Gen(Doc):
  match local:
    case True{}:
      J.call.local(j, env, EVar{name}, args)
    case False{}:
      J.call.def(j, env, name, G.def(JG.g(j), name), args)

law J.call:
  for +j: JG
  for +env: Env()
  for f: Expr
  for args: List<&2, Expr>
  Gen(Doc)

# f!(args) runs as a call in JavaScript.
@unsafe
def J.call.bang(+j: JG, +env: Env(), args: List<&2, Expr>) -> Gen(Doc):
  match args:
    case f <> xs:
      J.call(j, env, f, xs)
    case Nil{}:
      Gen.pure(Doc, DStr{"0"})

@unsafe
def J.call.name(+j: JG, +env: Env(), +name: String, args: List<&2, Expr>, bang: Bool) -> Gen(Doc):
  match bang:
    case True{}:
      J.call.bang(j, env, args)
    case False{}:
      J.call.var(j, env, name, args, Env.has(env, name))

@unsafe
def J.call(j, env, f, args):
  match f:
    case EVar{+name}:
      J.call.name(j, env, name, args, Str.eq(name, "%gpu"))
    case other:
      J.call.local(j, env, other, args)

law J.lam:
  for +j: JG
  for +env: Env()
  for +p: Pat
  for +body: Expr
  Gen(Doc)

# A statement-level expression used as a value: an immediately called
# function.
@unsafe
def J.block(+j: JG, +env: Env(), e: Expr) -> Gen(Doc):
  do Gen<Doc>:
    b : Doc <- J.stmt(j, env, Self.none(), TRet{}, e)
    return Doc.list([DStr{"(() => {\n"}, b, DStr{"})()"}])

@unsafe
def J.expr(j, env, e):
  match e:
    case EVar{name}:
      J.var(j, env, name)
    case ENum{n}:
      Gen.pure(Doc, DStr{U32.show(n)})
    case ENat{n}:
      Gen.pure(Doc, DStr{U32.show(n) ++ "n"})
    case EFlt{s}:
      Gen.pure(Doc, DStr{"Math.fround(" ++ s ++ ")"})
    case EStr{s}:
      Gen.pure(Doc, J.str(s))
    case ECall{f, args}:
      J.call(j, env, f, args)
    case ECtor{+name, args}:
      J.ctor.build(j, env, name, J.ctor(j, name), args)
    case ELam{p, body}:
      J.lam(j, env, p, body)
    case ELet{p, v, body}:
      J.block(j, env, ELet{p, v, body})
    case EMatch{scrs, cases}:
      J.block(j, env, EMatch{scrs, cases})
    case ESucc{k, x}:
      do Gen<Doc>:
        d : Doc <- J.expr(j, env, x)
        return Doc.list([DStr{"(("}, d, DStr{") + " ++ U32.show(k) ++ "n)"}])
    case ETy{n, targs}:
      Gen.pure(Doc, DStr{"null"})
    case EErr{m}:
      do Gen<Doc>:
        Gen.error("parse error: " ++ m)
        return DStr{"null"}
    case other:
      do Gen<Doc>:
        Gen.error("unexpected expression: " ++ Expr.show(other))
        return DStr{"null"}

@unsafe
def J.lam(j, env, p, body):
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    +a : String <- Gen.pure(String, "a" ++ U32.show(k))
    +binds : Env() <- Gen.pure(Env(), PatR.binds(J.pat(j, p, a, PatR{Nil{}, Nil{}})))
    b : Doc <- J.stmt(j, List.append(&2, Bind, binds, env), Self.none(), TRet{}, body)
    return Doc.list([DStr{"((" ++ a ++ ") => {\n"}, b, DStr{"})"}])

def J.ret(t: Tgt, d: Doc) -> Doc:
  match t:
    case TRet{}:
      Doc.list([DStr{"return "}, d, DStr{";\n"}])
    case TSet{v}:
      Doc.list([DStr{v}, DStr{" = "}, d, DStr{";\n"}])

def J.tail.temps(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"const t" ++ U32.show(i) ++ " = "}, d, DStr{"; "}, J.tail.temps(t, U32.inc(i))])

@unsafe
def J.tail(+j: JG, +env: Env(), cps: List<&2, String>, s: Split) -> Gen(Doc):
  Split{kept, all, extra, full} = s
  do Gen<Doc>:
    ds : List<&2, Doc> <- J.exprs(j, env, kept)
    return Doc.list([DStr{"{ "}, J.tail.temps(ds, 0), Gen.tail.assign(cps, 0), DStr{"continue top; }\n"}])

@unsafe
def J.tail.self(+j: JG, +env: Env(), self: Self, args: List<&2, Expr>) -> Gen(Doc):
  Self{sn, +mask, cps} = self
  J.tail(j, env, cps, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}))

@unsafe
def J.stmt.call(
  +j: JG, +env: Env(), +self: Self, +tgt: Tgt, +name: String, args: List<&2, Expr>, tail: Bool
) -> Gen(Doc):
  match tail:
    case True{}:
      J.tail.self(j, env, self, args)
    case False{}:
      do Gen<Doc>:
        d : Doc <- J.call(j, env, EVar{name}, args)
        return J.ret(tgt, d)

@unsafe
def J.let.var(
  +j: JG, +env: Env(), +self: Self, +tgt: Tgt, +x: String, v: Expr, body: Expr, hole: Bool
) -> Gen(Doc):
  match hole:
    case True{}:
      do Gen<Doc>:
        d : Doc <- J.expr(j, env, v)
        b : Doc <- J.stmt(j, env, self, tgt, body)
        return Doc.list([d, DStr{";\n"}, b])
    case False{}:
      do Gen<Doc>:
        +k : U32 <- Gen.fresh()
        +c : String <- Gen.pure(String, "v" ++ U32.show(k))
        d : Doc <- J.expr(j, env, v)
        b : Doc <- J.stmt(j, Bind{x, c} <> env, self, tgt, body)
        return Doc.list([DStr{"const " ++ c ++ " = "}, d, DStr{";\n"}, b])

@unsafe
def J.let.pat(+j: JG, +env: Env(), +self: Self, +tgt: Tgt, +p: Pat, v: Expr, body: Expr) -> Gen(Doc):
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    +c : String <- Gen.pure(String, "v" ++ U32.show(k))
    d : Doc <- J.expr(j, env, v)
    +binds : Env() <- Gen.pure(Env(), PatR.binds(J.pat(j, p, c, PatR{Nil{}, Nil{}})))
    b : Doc <- J.stmt(j, List.append(&2, Bind, binds, env), self, tgt, body)
    return Doc.list([DStr{"const " ++ c ++ " = "}, d, DStr{";\n"}, b])

# A parallel let runs its values one after another here.
@unsafe
def J.let.par(+j: JG, +env: Env(), +self: Self, +tgt: Tgt, ps: List<&2, Pat>, v: Expr, body: Expr) -> Gen(Doc):
  match ps v:
    case p <> pt ECtor{n, x <> xt}:
      J.stmt(j, env, self, tgt, ELet{p, x, ELet{PCtor{"%par", pt}, ECtor{n, xt}, body}})
    case pl other:
      J.stmt(j, env, self, tgt, body)

@unsafe
def J.let.ctor(
  +j: JG, +env: Env(), +self: Self, +tgt: Tgt, name: String, ps: List<&2, Pat>, v: Expr, body: Expr, par: Bool
) -> Gen(Doc):
  match par:
    case True{}:
      J.let.par(j, env, self, tgt, ps, v, body)
    case False{}:
      J.let.pat(j, env, self, tgt, PCtor{name, ps}, v, body)

@unsafe
def J.let(+j: JG, +env: Env(), +self: Self, +tgt: Tgt, p: Pat, v: Expr, body: Expr) -> Gen(Doc):
  match p:
    case PVar{+x}:
      J.let.var(j, env, self, tgt, x, v, body, Str.eq(x, "_"))
    case PCtor{+name, ps}:
      J.let.ctor(j, env, self, tgt, name, ps, v, body, Str.eq(name, "%par"))
    case other:
      J.let.pat(j, env, self, tgt, other, v, body)

law J.cases:
  for +j: JG
  for +env: Env()
  for +self: Self
  for +tgt: Tgt
  for +cs: List<&2, String>
  for cases: List<&2, Expr>
  Gen(Doc)

@unsafe
def J.cases.next(
  +j: JG, +env: Env(), +self: Self, +tgt: Tgt, +cs: List<&2, String>, rest: List<&2, Expr>, conds: List<&2, String>,
  b: Doc
) -> Gen(Doc):
  match conds:
    case Nil{}:
      Gen.pure(Doc, Doc.list([DStr{"{\n"}, b, DStr{"}\n"}]))
    case h <> t:
      do Gen<Doc>:
        more : Doc <- J.cases(j, env, self, tgt, cs, rest)
        return Doc.list([DStr{"if (" ++ Gen.and(h <> t) ++ ") {\n"}, b, DStr{"} else "}, more])

@unsafe
def J.cases(j, env, self, tgt, cs, cases):
  match cases:
    case Nil{}:
      Gen.pure(Doc, DStr{"{ bend_fail(\"incomplete match\"); }\n"})
    case ECase{ps, body} <> t:
      +pr = J.pats(j, ps, cs, PatR{Nil{}, Nil{}})
      +conds = PatR.conds(pr)
      +binds = PatR.binds(pr)
      do Gen<Doc>:
        b : Doc <- J.stmt(j, List.append(&2, Bind, binds, env), self, tgt, body)
        J.cases.next(j, env, self, tgt, cs, t, List.reverse(&2, String, conds), b)
    case other <> t:
      J.cases(j, env, self, tgt, cs, t)

def J.scrs.put(+c: String, d: Doc, r: List<&2, String> & Doc) -> List<&2, String> & Doc:
  (cs, code) = r
  (c <> cs, Doc.list([DStr{"const " ++ c ++ " = "}, d, DStr{";\n"}, code]))

@unsafe
def J.scrs(+j: JG, +env: Env(), xs: List<&2, Expr>) -> Gen(List<&2, String> & Doc):
  match xs:
    case Nil{}:
      Gen.pure(List<&2, String> & Doc, (Nil{}, DNil{}))
    case h <> t:
      do Gen<List<&2, String> & Doc>:
        +k : U32 <- Gen.fresh()
        +c : String <- Gen.pure(String, "s" ++ U32.show(k))
        d : Doc <- J.expr(j, env, h)
        r : List<&2, String> & Doc <- J.scrs(j, env, t)
        return J.scrs.put(c, d, r)

@unsafe
def J.match.go(+j: JG, +env: Env(), +self: Self, +tgt: Tgt, cases: List<&2, Expr>, r: List<&2, String> & Doc) ->
  Gen(Doc):
  (cs, decls) = r
  do Gen<Doc>:
    body : Doc <- J.cases(j, env, self, tgt, cs, cases)
    return Doc.list([decls, body])

@unsafe
def J.match(+j: JG, +env: Env(), +self: Self, +tgt: Tgt, scrs: List<&2, Expr>, cases: List<&2, Expr>) -> Gen(Doc):
  do Gen<Doc>:
    r : List<&2, String> & Doc <- J.scrs(j, env, scrs)
    J.match.go(j, env, self, tgt, cases, r)

@unsafe
def J.stmt(j, env, self, tgt, e):
  match e:
    case ELet{p, v, body}:
      J.let(j, env, self, tgt, p, v, body)
    case EMatch{scrs, cases}:
      J.match(j, env, self, tgt, scrs, cases)
    case ECall{EVar{+name}, +args}:
      J.stmt.call(j, env, self, tgt, name, args, Gen.is_tail(env, self, tgt, name, args))
    case other:
      do Gen<Doc>:
        d : Doc <- J.expr(j, env, other)
        return J.ret(tgt, d)

def J.params(ps: List<&2, String>) -> String:
  String.join(ps, ", ")

# W_f: f as a curried function of all its parameters (erased ones too).
def J.wrapper.go(n: Nat, +i: U32, +kept: String, +name: String) -> String:
  match n:
    case 0n:
      Gen.f(name) ++ "(" ++ kept ++ ")"
    case 1n+m:
      "(p" ++ U32.show(i) ++ ") => " ++ J.wrapper.go(m, U32.inc(i), kept, name)

def J.wkept(mask: List<&2, Bool>, +i: U32) -> List<&2, String>:
  match mask:
    case Nil{}:
      Nil{}
    case True{} <> t:
      ("p" ++ U32.show(i)) <> J.wkept(t, U32.inc(i))
    case False{} <> t:
      J.wkept(t, U32.inc(i))

def J.wrapper(+name: String, +mask: List<&2, Bool>) -> Gen(Unit):
  match mask:
    case Nil{}:
      Gen.pure(Unit, Unit{})
    case +h <> t:
      Gen.code(DStr{"const " ++ Gen.w(name) ++ " = " ++
        J.wrapper.go(List.length(&2, Bool, h <> t), 0, String.join(J.wkept(h <> t, 0), ", "), name) ++ ";\n"})

def J.def.body(+j: JG, +name: String, +mask: List<&2, Bool>, body: Expr, sig: Sig) -> Gen(Unit):
  Sig{+params, env, wargs} = sig
  do Gen<Unit>:
    b : Doc <- J.stmt(j, env, Self{name, mask, params}, TRet{}, R.ops(body, "Nat"))
    Gen.code(Doc.list([DStr{"function " ++ Gen.f(name) ++ "(" ++ J.params(params) ++ ") {\ntop: for (;;) {\n"}, b,
      DStr{"}\n}\n"}]))
    J.wrapper(name, mask)

def J.host.chr(+x: U32) -> String:
  Bool.pick(String, U32.is_eq(x, 46), "_", Str.chr(x))

def J.host(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{Chr{x}, t}:
      J.host.chr(x) ++ J.host(t)

def J.effs.js.if(h: String, +host: String, rest: List<&2, String>, keep: Bool) -> List<&2, String>:
  match keep:
    case True{}:
      (h ++ "\t" ++ host) <> rest
    case False{}:
      rest

def J.effs.js(ims: List<&2, String>, +host: String) -> List<&2, String>:
  match ims:
    case Nil{}:
      Nil{}
    case +h <> t:
      J.effs.js.if(h, host, J.effs.js(t, host), String.ends_with(h, ".js"))

def J.effs.go(ims: List<&2, String>, +host: String, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, memo, List.append(&2, String, J.effs.js(ims, host), effs)})

# Records the JS files a foreign def imports, with its host function.
def J.effs(ims: List<&2, String>, +host: String) -> Gen(Unit):
  st => J.effs.go(ims, host, st)

# Effects: F builds R => k => a request the event loop answers.
def J.def.eff(+name: String, +mask: List<&2, Bool>, sig: Sig, ims: List<&2, String>) -> Gen(Unit):
  Sig{+params, env, wargs} = sig
  +host = J.host(String.to_lower(name))
  do Gen<Unit>:
    J.effs(ims, host)
    Gen.code(DStr{"function " ++ Gen.f(name) ++ "(" ++ J.params(params) ++ ") {\n  return (R) => (k) => io_req(EFF[\"" ++
      host ++ "\"], \"" ++ host ++ "\", [" ++ J.params(params) ++ "], k);\n}\n"})
    J.wrapper(name, mask)

def J.def.native(+j: JG, +name: String, +mask: List<&2, Bool>, body: Expr, sig: Sig, native: Bool) -> Gen(Unit):
  match native:
    case True{}:
      J.wrapper(name, mask)
    case False{}:
      J.def.body(j, name, mask, body, sig)

def J.def.decl(+j: JG, +name: String, +info: DInfo, d: Decl) -> Gen(Unit):
  DInfo{+kind, +mask} = info
  match d:
    case DDef{n, ps, body, ret}:
      J.def.native(j, name, mask, body, Gen.sig(ps, mask, 0, Sig{Nil{}, Nil{}, Nil{}}), U32.is_eq(kind, 2))
    case DEff{n, ps, ims}:
      J.def.eff(name, mask, Gen.sig(ps, mask, 0, Sig{Nil{}, Nil{}, Nil{}}), ims)
    case other:
      Bool.pick(Gen(Unit), U32.is_eq(kind, 2), J.wrapper(name, mask), Gen.pure(Unit, Unit{}))

def J.def(+j: JG, +name: String) -> Gen(Unit):
  J.def.decl(j, name, G.def(JG.g(j), name), G.body(JG.g(j), name))

@unsafe
def J.all.go(+j: JG, +h: String, t: List<&2, String>, done: Set(), seen: Bool) -> Gen(Unit):
  match seen:
    case True{}:
      J.all(j, t, done)
    case False{}:
      do Gen<Unit>:
        J.def(j, h)
        refs : List<&2, String> <- Gen.take_refs()
        J.all(j, List.append(&2, String, refs, t), Set.add(done, h))

@unsafe
def J.all.seen(+j: JG, +h: String, t: List<&2, String>, r: Set() & Bool) -> Gen(Unit):
  (done, seen) = r
  J.all.go(j, h, t, done, seen)

@unsafe
def J.all(j, queue, done):
  match queue:
    case Nil{}:
      Gen.pure(Unit, Unit{})
    case +h <> t:
      J.all.seen(j, h, t, Set.has(done, h))

@unsafe
def J.printer.tuple(+j: JG, xs: List<&2, Expr>, +path: String) -> Gen(Doc):
  match xs:
    case Nil{}:
      Gen.pure(Doc, DNil{})
    case h <> Nil{}:
      do Gen<Doc>:
        f : String <- J.printer(j, h)
        return DStr{"s += " ++ f ++ "(" ++ path ++ ");\n"}
    case h <> t:
      do Gen<Doc>:
        f : String <- J.printer(j, h)
        rest : Doc <- J.printer.tuple(j, t, "(" ++ path ++ ").snd")
        return Doc.list([DStr{"s += " ++ f ++ "((" ++ path ++ ").fst) + \", \";\n"}, rest])

@unsafe
def J.printer.fields(+j: JG, +sub: List<&2, TB>, fs: List<&2, Field>, +path: String, +i: U32) -> Gen(Doc):
  match fs:
    case Nil{}:
      Gen.pure(Doc, DNil{})
    case Field{+n, t} <> rest:
      do Gen<Doc>:
        f : String <- J.printer(j, Ty.subst(t, sub))
        more : Doc <- J.printer.fields(j, sub, rest, path, U32.inc(i))
        return Doc.list([DStr{Bool.pick(String, U32.is_zero(i), "", "s += \", \";\n") ++ "s += " ++ f ++ "((" ++ path ++
          ")." ++ n ++ ");\n"}, more])

@unsafe
def J.printer.ctor(+j: JG, +sub: List<&2, TB>, +name: String, fields: List<&2, Field>, +single: Bool) -> Gen(Doc):
  do Gen<Doc>:
    fs : Doc <- J.printer.fields(j, sub, fields, "v", 0)
    return Doc.list([DStr{Bool.pick(String, single, "if (true)", "if (v.$ === \"" ++ name ++ "\")") ++
      " { let s = \"" ++ name ++ "{\";\n"}, fs, DStr{"return s + \"}\"; }\n"}])

@unsafe
def J.printer.ctors(+j: JG, +sub: List<&2, TB>, cs: List<&2, Ctor>, +single: Bool) -> Gen(Doc):
  match cs:
    case Nil{}:
      Gen.pure(Doc, DNil{})
    case Ctor{+name, fields} <> t:
      do Gen<Doc>:
        one : Doc <- J.printer.ctor(j, sub, name, fields, single)
        rest : Doc <- J.printer.ctors(j, sub, t, single)
        return Doc.list([one, rest])

@unsafe
def J.printer.adt(+j: JG, +ty: Expr, d: Decl) -> Gen(Doc):
  match d:
    case DType{name, ps, +cs}:
      do Gen<Doc>:
        b : Doc <- J.printer.ctors(j, Ty.bind(ps, Ty.args(ty)), cs, Nat.is_eq(List.length(&2, Ctor, cs), 1n))
        return Doc.list([b, DStr{"return \"?\";\n"}])
    case other:
      Gen.pure(Doc, DStr{"return \"?\";\n"})

@unsafe
def J.printer.head(+j: JG, +ty: Expr, k: Nat) -> Gen(Doc):
  match k:
    case 0n:
      Gen.pure(Doc, DStr{"return pr_u32(v);\n"})
    case 1n:
      Gen.pure(Doc, DStr{"return pr_nat(v);\n"})
    case 2n:
      Gen.pure(Doc, DStr{"return pr_f32(v);\n"})
    case 3n:
      Gen.pure(Doc, DStr{"return pr_char(v);\n"})
    case 4n:
      Gen.pure(Doc, DStr{"return pr_str(v);\n"})
    case 5n:
      do Gen<Doc>:
        e : String <- J.printer(j, P.last(Ty.args(ty)))
        return DStr{"const xs = [];\nfor (; v.$ === \"Con\"; v = v.tail) xs.push(" ++ e ++
          "(v.head));\nreturn \"[\" + xs.join(\", \") + \"]\";\n"}
    case 6n:
      do Gen<Doc>:
        parts : Doc <- J.printer.tuple(j, Ty.tuple(ty), "v")
        return Doc.list([DStr{"let s = \"(\";\n"}, parts, DStr{"return s + \")\";\n"}])
    case 7n:
      Gen.pure(Doc, DStr{"return \"<function>\";\n"})
    case 8n:
      Gen.pure(Doc, DStr{"return v ? \"True{}\" : \"False{}\";\n"})
    case 9n+p:
      J.printer.adt(j, ty, G.body(JG.g(j), "%" ++ Ty.head(ty)))

@unsafe
def J.printer.body(+j: JG, +ty: Expr, +h: String) -> Gen(Doc):
  J.printer.head(j, ty, P.which(h, ["U32", "Nat", "F32", "Char", "String", "List", "&", "->", "Bool"]))

@unsafe
def J.printer.memo(+j: JG, +ty: Expr, +key: String, m: Maybe<&2, String>) -> Gen(String):
  match m:
    case Some{f}:
      Gen.pure(String, f)
    case None{}:
      do Gen<String>:
        +k : U32 <- Gen.fresh()
        +f : String <- Gen.pure(String, "P" ++ U32.show(k))
        Gen.memo.add(Bind{key, f})
        b : Doc <- J.printer.body(j, ty, Ty.head(ty))
        Gen.code(Doc.list([DStr{"function " ++ f ++ "(v) {\n"}, b, DStr{"}\n"}]))
        return f

# The name of a JS function that prints values of a type.
@unsafe
def J.printer(j, ty):
  +key = Expr.show(ty)
  do Gen<String>:
    m : Maybe<&2, String> <- Gen.memo.find(key)
    J.printer.memo(j, ty, key, m)
