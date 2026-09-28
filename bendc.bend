# bendc: a Bend compiler written in Bend.
# Compiles a Bend program (plus the parts of Base it uses) to C.
# Usage: bendc <base.bend> <input.bend>  (C goes to stdout)

import Base
import ./check.bend as Chk
import ./core.bend as Core
import ./rt/rtjs.bend as RtJs
import ./rt/rtchan.bend as RtChan

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

def Str.split_tab(s: String) -> String & String:
  match s:
    case SNil{}:
      ("", "")
    case SCon{Chr{+c}, +t}:
      Bool.pick(Unit -> String & String, U32.is_eq(c, 9), u => ("", t),
        u => Str.split_tab.cons(c, Str.split_tab(t)))(Unit{})

def Str.codes32(s: String) -> List<&2, U32>:
  match s:
    case SNil{}:
      Nil{}
    case SCon{Chr{x}, t}:
      x <> Str.codes32(t)

# Fuel for recursion that is not structural: a parser's over tokens, or
# one def that merges a cycle of defs and switches between them. More than
# any input needs; a def that runs out fails loudly.
def Fuel.max() -> Nat:
  U32.to_nat(4000000000)

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
def Lex.id(s: String, +acc: String) -> String & String:
  match s:
    case SNil{}:
      (Str.rev(acc), SNil{})
    case SCon{+c, +t}:
      Bool.pick(Unit -> String & String, Lex.is_idc(c), u => Lex.id(t, SCon{c, acc}),
        u => (Str.rev(acc), SCon{c, t}))(Unit{})

# Spans digits, accumulating a U32 value.
def Lex.digits(s: String, +acc: U32) -> U32 & String:
  match s:
    case SNil{}:
      (acc, SNil{})
    case SCon{+c, +t}:
      Bool.pick(Unit -> U32 & String, Char.is_digit(c),
        u => Lex.digits(t, ((acc * 10 : U32) + (Char.to_u32(c) - 48 : U32) : U32)),
        u => (acc, SCon{c, t}))(Unit{})

# Spans digit chars as text (for float fractions).
def Lex.dtext(s: String, +acc: String) -> String & String:
  match s:
    case SNil{}:
      (Str.rev(acc), SNil{})
    case SCon{+c, +t}:
      Bool.pick(Unit -> String & String, Char.is_digit(c), u => Lex.dtext(t, SCon{c, acc}),
        u => (Str.rev(acc), SCon{c, t}))(Unit{})

# Escape char after a backslash.
def Lex.esc(x: U32) -> U32:
  +y = x
  Bool.pick(U32, U32.is_eq(y, 110), 10,
    Bool.pick(U32, U32.is_eq(y, 116), 9,
      Bool.pick(U32, U32.is_eq(y, 114), 13,
        Bool.pick(U32, U32.is_eq(y, 48), 0, y))))

def Lex.hex.digit(+c: U32) -> U32:
  Bool.pick(U32, U32.is_le(c, 57), (c - 48 : U32),
    Bool.pick(U32, U32.is_ge(c, 97), (c - 87 : U32), (c - 55 : U32)))

# The digits of a \u{hex} escape, through its '}'.
def Lex.hex(s: String, +acc: U32) -> U32 & String:
  match s:
    case SNil{}:
      (acc, SNil{})
    case SCon{Chr{+c}, +t}:
      Bool.pick(Unit -> U32 & String, U32.is_eq(c, 125), u => (acc, t),
        u => Lex.hex(t, (acc * 16 + Lex.hex.digit(c) : U32)))(Unit{})

def Lex.esc.brace.if(+y: U32, +c: U32, t: String, brace: Bool) -> U32 & String:
  match brace:
    case True{}:
      Lex.hex(t, 0)
    case False{}:
      (Lex.esc(y), SCon{Chr{c}, t})

def Lex.esc.brace(+y: U32, t: String) -> U32 & String:
  match t:
    case SNil{}:
      (Lex.esc(y), SNil{})
    case SCon{Chr{+c}, t2}:
      Lex.esc.brace.if(y, c, t2, U32.is_eq(c, 123))

def Lex.esc.u(+y: U32, t: String, u: Bool) -> U32 & String:
  match u:
    case True{}:
      Lex.esc.brace(y, t)
    case False{}:
      (Lex.esc(y), t)

def Lex.lit_char.esc(t: String) -> U32 & String:
  match t:
    case SNil{}:
      (92, SNil{})
    case SCon{Chr{+y}, t2}:
      Lex.esc.u(y, t2, U32.is_eq(y, 117))

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

# A string literal's lexer, a char at a time (reading escapes as
# Lex.lit_char does): its text so far (reversed), and k: 0 in the text, 1
# after a '\', 2 after '\u', 3 in the digits of a '\u{' (v their value), 4
# past the closing quote.
type StrSt is Data:
  StrSt{acc: String, k: Nat, v: U32}

# A char x of the text: its closing quote, a '\', or a plain char.
def Lex.str.text(+x: U32, +acc: String) -> StrSt:
  Bool.pick(StrSt, U32.is_eq(x, 34), StrSt{acc, 4n, 0},
    Bool.pick(StrSt, U32.is_eq(x, 92), StrSt{acc, 1n, 0}, StrSt{SCon{Chr{x}, acc}, 0n, 0}))

def Lex.str.step(+x: U32, st: StrSt) -> StrSt:
  match st:
    case StrSt{+acc, k, +v}:
      match k:
        case 0n:
          Lex.str.text(x, acc)
        case 1n:
          Bool.pick(StrSt, U32.is_eq(x, 117), StrSt{acc, 2n, 0},
            StrSt{SCon{Chr{Lex.esc(x)}, acc}, 0n, 0})
        case 2n:
          Bool.pick(StrSt, U32.is_eq(x, 123), StrSt{acc, 3n, 0},
            Lex.str.text(x, SCon{Chr{117}, acc}))
        case 3n:
          Bool.pick(StrSt, U32.is_eq(x, 125), StrSt{SCon{Chr{v}, acc}, 0n, 0},
            StrSt{acc, 3n, (v * 16 + Lex.hex.digit(x) : U32)})
        case 4n+p:
          StrSt{acc, 4n, v}

def Lex.str.done(st: StrSt) -> Bool:
  match st:
    case StrSt{acc, k, v}:
      Nat.is_eq(k, 4n)

# The text, at the closing quote or the end of the line.
def Lex.str.fin(st: StrSt) -> String:
  match st:
    case StrSt{acc, k, v}:
      match k:
        case 0n:
          Str.rev(acc)
        case 1n:
          Str.rev(SCon{Chr{92}, acc})
        case 2n:
          Str.rev(SCon{Chr{117}, acc})
        case 3n:
          Str.rev(SCon{Chr{v}, acc})
        case 4n+p:
          Str.rev(acc)

def Lex.str.go(s: String, st: StrSt) -> String & String:
  match s:
    case SNil{}:
      (Lex.str.fin(st), SNil{})
    case SCon{Chr{+x}, +t}:
      +st2 = Lex.str.step(x, st)
      Bool.pick(Unit -> String & String, Lex.str.done(st2), u => (Lex.str.fin(st2), t),
        u => Lex.str.go(t, st2))(Unit{})

# String literal body: (text, rest after closing quote).
def Lex.str(s: String, acc: String) -> String & String:
  Lex.str.go(s, StrSt{acc, 0n, 0})

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

# A step of a line's lexer: the end of its tokens, a space, or a token and
# the text after it.
type LxStep is Data:
  LxEnd{}
  LxSkip{rest: String}
  LxTok{tok: Tok, rest: String}

def Lex.class(+x: U32) -> Nat:
  # 0 space, 1 comment, 2 ident, 3 digit, 4 char, 5 string, 6 op
  Bool.pick(Nat, Bool.or(U32.is_eq(x, 32), U32.is_eq(x, 9)), 0n,
  Bool.pick(Nat, U32.is_eq(x, 35), 1n,
  Bool.pick(Nat, Lex.is_ids(Chr{x}), 2n,
  Bool.pick(Nat, Char.is_digit(Chr{x}), 3n,
  Bool.pick(Nat, U32.is_eq(x, 39), 4n,
  Bool.pick(Nat, U32.is_eq(x, 34), 5n,
  Bool.pick(Nat, U32.is_eq(x, 13), 0n, 6n)))))))

def Lex.line.id(sp: Bool, +ln: U32, r: String & String) -> LxStep:
  (name, rest) = r
  LxTok{Tok{KId{name}, sp, ln}, rest}

def Lex.line.chr(sp: Bool, +ln: U32, r: U32 & String) -> LxStep:
  (c, rest) = r
  LxTok{Tok{KChr{c}, sp, ln}, Lex.drop1(rest)}

def Lex.line.str(sp: Bool, +ln: U32, r: String & String) -> LxStep:
  (s, rest) = r
  LxTok{Tok{KStr{s}, sp, ln}, rest}

def Lex.line.op(s: String, sp: Bool, +ln: U32, +op: String) -> LxStep:
  LxTok{Tok{KSym{op}, sp, ln}, String.drop(s, String.length(op))}

def Lex.line.nat.if(sp: Bool, +ln: U32, +v: U32, x: U32, t: String, plus: Bool) -> LxStep:
  match plus:
    case True{}:
      LxTok{Tok{KNatPlus{v}, sp, ln}, t}
    case False{}:
      LxTok{Tok{KNat{v}, sp, ln}, SCon{Chr{x}, t}}

def Lex.line.nat(sp: Bool, +ln: U32, +v: U32, t: String) -> LxStep:
  match t:
    case SNil{}:
      LxTok{Tok{KNat{v}, sp, ln}, SNil{}}
    case SCon{Chr{+x}, t2}:
      Lex.line.nat.if(sp, ln, v, x, t2, U32.is_eq(x, 43))

def Lex.exp.cat(+pre: String, r: String & String) -> String & String:
  (d, rest) = r
  (pre ++ d, rest)

# 0 no exponent, 1 a signed one, 2 an unsigned one.
def Lex.exp.k(+e: U32, +c: U32, t: String, k: Nat) -> String & String:
  match k:
    case 0n:
      ("", SCon{Chr{e}, SCon{Chr{c}, t}})
    case 1n:
      Lex.exp.cat("e" ++ SCon{Chr{c}, SNil{}}, Lex.dtext(t, SNil{}))
    case 2n+p:
      Lex.exp.cat("e", Lex.dtext(SCon{Chr{c}, t}, SNil{}))

def Lex.exp.sign(+c: U32, t: String) -> Bool:
  match t:
    case SCon{Chr{d}, r}:
      Bool.and(Bool.or(U32.is_eq(c, 43), U32.is_eq(c, 45)), Char.is_digit(Chr{d}))
    case SNil{}:
      False{}

# A float's exponent after its digits (e-3, E+2, e10), and what follows.
def Lex.exp(s: String) -> String & String:
  match s:
    case SCon{Chr{+e}, SCon{Chr{+c}, +t}}:
      Lex.exp.k(e, c, t, Bool.pick(Nat, U32.is_eq(U32.or(e, 32), 101),
        Bool.pick(Nat, Lex.exp.sign(c, t), 1n, Bool.pick(Nat, Char.is_digit(Chr{c}), 2n, 0n)),
        0n))
    case other:
      ("", other)

def Lex.line.flt.e(sp: Bool, +ln: U32, +ds: String, +frac: String, r: String & String) ->
  LxStep:
  (e, rest) = r
  LxTok{Tok{KFlt{ds ++ "." ++ frac ++ e}, sp, ln}, rest}

def Lex.line.flt(sp: Bool, +ln: U32, +ds: String, r: String & String) -> LxStep:
  (frac, rest) = r
  Lex.line.flt.e(sp, ln, ds, frac, Lex.exp(rest))

def Lex.line.num.if(sp: Bool, +ln: U32, +v: U32, +ds: String, x: U32, t: String, k: Nat) ->
  LxStep:
  match k:
    case 0n:
      LxTok{Tok{KNum{v}, sp, ln}, SCon{Chr{x}, t}}
    case 1n:
      Lex.line.nat(sp, ln, v, t)
    case 2n+p:
      Lex.line.flt(sp, ln, ds, Lex.dtext(t, SNil{}))

def Lex.line.num.go(sp: Bool, +ln: U32, +v: U32, +ds: String, rest: String) -> LxStep:
  match rest:
    case SNil{}:
      LxTok{Tok{KNum{v}, sp, ln}, SNil{}}
    case SCon{Chr{+x}, t}:
      Lex.line.num.if(sp, ln, v, ds, x, t,
        Bool.pick(Nat, U32.is_eq(x, 110), 1n,
          Bool.pick(Nat, U32.is_eq(x, 46), 2n, 0n)))

# After digits: Nat literal (n / n+), float (.digits) or U32.
# ds: the digits as written, less leading zeros (a float keeps them all, as
# its integer part may pass 2^32 - 1).
def Lex.line.num(sp: Bool, +ln: U32, +ds: String, r: U32 & String) -> LxStep:
  (v, rest) = r
  Lex.line.num.go(sp, ln, v, ds, rest)

def Lex.unzero(s: String) -> String:
  match s:
    case SCon{Chr{48}, SCon{c, t}}:
      Lex.unzero(SCon{c, t})
    case other:
      other

# A lexed line: indentation, line number, tokens.
type Line is Data:
  Line{ind: U32, ln: U32, toks: List<&2, Tok>}

def Lex.lines.put(l: Line, rest: List<&2, Line>) -> List<&2, Line>:
  match l:
    case Line{i, n, Nil{}}:
      rest
    case Line{i, n, h <> t}:
      Line{i, n, h <> t} <> rest

def Lex.find_op(ops: List<&2, String>, +s: String) -> Maybe<&2, String>:
  match ops:
    case Nil{}:
      None{}
    case +h <> t:
      Bool.pick(Unit -> Maybe<&2, String>, String.starts_with(s, h), u => Some{h},
        u => Lex.find_op(t, s))(Unit{})

def Lex.op_of.go(m: Maybe<&2, String>, +s: String) -> String:
  match m:
    case Some{o}:
      o
    case None{}:
      Lex.op_of.two(Lex.find_op(Lex.ops2(), s), s)

def Lex.op_of(+s: String) -> String:
  Lex.op_of.go(Lex.find_op(Lex.ops3(), s), s)

def Lex.line.go(+x: U32, +t: String, sp: Bool, +ln: U32, cls: Nat) -> LxStep:
  match cls:
    case 0n:
      LxSkip{t}
    case 1n:
      LxEnd{}
    case 2n:
      Lex.line.id(sp, ln, Lex.id(SCon{Chr{x}, t}, SNil{}))
    case 3n:
      Lex.line.num(sp, ln, Lex.unzero(Pair.fst(String, String, Lex.dtext(SCon{Chr{x}, t}, SNil{}))),
        Lex.digits(SCon{Chr{x}, t}, 0))
    case 4n:
      Lex.line.chr(sp, ln, Lex.lit_char(t))
    case 5n:
      Lex.line.str(sp, ln, Lex.str(t, SNil{}))
    case 6n+p:
      +s = {SCon{Chr{x}, t} : String}
      Lex.line.op(s, sp, ln, Lex.op_of(s))

# The step at the head of s (sp: whether a space comes before it).
def Lex.step(s: String, sp: Bool, +ln: U32) -> LxStep:
  match s:
    case SNil{}:
      LxEnd{}
    case SCon{Chr{+x}, t}:
      Lex.line.go(x, t, sp, ln, Lex.class(x))

def Lex.line.run(n: Nat, st: LxStep, +ln: U32, acc: Toks()) -> Toks():
  match n:
    case 0n:
      Tok{KErr{"line " ++ U32.show(ln) ++ ": out of fuel"}, True{}, ln} <> acc
    case 1n+p:
      match st:
        case LxEnd{}:
          acc
        case LxSkip{rest}:
          Lex.line.run(p, Lex.step(rest, True{}, ln), ln, acc)
        case LxTok{tok, rest}:
          Lex.line.run(p, Lex.step(rest, False{}, ln), ln, tok <> acc)

# Lexes one line. acc is reversed.
def Lex.line(s: String, sp: Bool, +ln: U32, acc: Toks()) -> Toks():
  Lex.line.run(Fuel.max(), Lex.step(s, sp, ln), ln, acc)

# Leading indentation width.
def Lex.indent(s: String) -> U32:
  match s:
    case SNil{}:
      0
    case SCon{Chr{+x}, t}:
      Bool.pick(Unit -> U32, U32.is_eq(x, 32), u => U32.inc(Lex.indent(t)), u => 0)(Unit{})

def Lex.semi.if(+h: Tok, t: Toks(), semi: Bool) -> Toks():
  match semi:
    case True{}:
      t
    case False{}:
      h <> t

# A line's tokens, last first, less a ';' that ends it (a let or a step may
# end in one).
def Lex.semi(ts: Toks()) -> Toks():
  match ts:
    case Nil{}:
      Nil{}
    case Tok{KSym{+x}, sp, ln} <> t:
      Lex.semi.if(Tok{KSym{x}, sp, ln}, t, Str.eq(x, ";"))
    case h <> t:
      h <> t

def Lex.hit(h: Tok, +d: U32, +sym: String) -> Bool:
  match h:
    case Tok{KSym{x}, sp, ln}:
      Bool.and(Str.eq(x, sym), U32.is_zero(d))
    case other:
      False{}

def Lex.dep(h: Tok, +d: U32) -> U32:
  match h:
    case Tok{KSym{+x}, sp, ln}:
      U32.sub(U32.add(d, Bool.pick(U32, Str.has(["(", "[", "{"], x), 1, 0)),
        Bool.pick(U32, Bool.and(Str.has([")", "]", "}"], x), U32.is_gt(d, 0)), 1, 0))
    case other:
      d

# A binder's ':' (@x: A, @-x: A, &x: A) is no split: b is 1 after its
# '@' or '&' (and a '-' or '+'), 2 after its name.
def Lex.bind(h: Tok, +b: U32) -> U32:
  match h:
    case Tok{KSym{+x}, sp, ln}:
      Bool.pick(U32, Str.has(["@", "&"], x), 1,
        Bool.pick(U32, Bool.and(U32.is_eq(b, 1), Str.has(["-", "+"], x)), 1, 0))
    case Tok{KId{x}, sp, ln}:
      Bool.pick(U32, U32.is_eq(b, 1), 2, 0)
    case other:
      0

# How many tokens of a line end at its first sym outside brackets (0: none).
def Lex.colon.b(ts: List<&2, Tok>, +d: U32, +i: Nat, +sym: String, +b: U32) -> Nat:
  match ts:
    case Nil{}:
      0n
    case +h <> t:
      Bool.pick(Nat, Bool.and(Lex.hit(h, d, sym), Bool.not(U32.is_eq(b, 2))), Nat.add(i, 1n),
        Lex.colon.b(t, Lex.dep(h, d), Nat.add(i, 1n), sym, Lex.bind(h, b)))

def Lex.colon(ts: List<&2, Tok>, +d: U32, +i: Nat, +sym: String) -> Nat:
  Lex.colon.b(ts, d, i, sym, 0)

def Lex.is_def(ts: List<&2, Tok>) -> Bool:
  match ts:
    case Tok{KId{x}, sp, ln} <> t:
      Str.has(["def", "case"], x)
    case other:
      False{}

# Statements a ';' outside brackets separates, one line each.
def Lex.semis.go(fu: Nat, +i: U32, +ln: U32, +ts: List<&2, Tok>, +rest: List<&2, Line>) ->
  List<&2, Line>:
  match fu:
    case 0n:
      Line{i, ln, [Tok{KErr{"line " ++ U32.show(ln) ++ ": out of fuel"}, True{}, ln}]} <> rest
    case 1n+f:
      +n = Lex.colon(ts, 0, 0n, ";")
      Bool.pick(Unit -> List<&2, Line>, Nat.is_gt(n, 0n),
        u => Lex.lines.put(Line{i, ln, List.take(&2, Tok, ts, Nat.sub(n, 1n))},
          Lex.semis.go(f, i, ln, List.drop(&2, Tok, ts, n), rest)),
        u => Lex.lines.put(Line{i, ln, ts}, rest))(Unit{})

def Lex.semis(+i: U32, +ln: U32, +ts: List<&2, Tok>, +rest: List<&2, Line>) -> List<&2, Line>:
  Lex.semis.go(Fuel.max(), i, ln, ts, rest)

# A line, or a def or case with its body on the same line (def f(): e,
# case K{}: e) as two: the body goes one level deeper.
def Lex.split(+i: U32, +ln: U32, +ts: List<&2, Tok>, +rest: List<&2, Line>) -> List<&2, Line>:
  +n = Bool.pick(Nat, Lex.is_def(ts), Lex.colon(ts, 0, 0n, ":"), 0n)
  Bool.pick(List<&2, Line>, Bool.and(Nat.is_gt(n, 0n), Nat.is_lt(n, List.length(&2, Tok, ts))),
    Line{i, ln, List.take(&2, Tok, ts, n)} <> Lex.semis(U32.add(i, 2), ln, List.drop(&2, Tok, ts, n), rest),
    Lex.semis(i, ln, ts, rest))

def Lex.lines.go(ls: List<&2, String>, +ln: U32) -> List<&2, Line>:
  match ls:
    case Nil{}:
      Nil{}
    case +l <> t:
      Lex.split(Lex.indent(l), ln, List.reverse(&2, Tok, Lex.semi(Lex.line(l, True{}, ln, Nil{}))),
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

def Lay.top(+stack: List<&2, U32>) -> U32:
  match stack:
    case Nil{}:
      0
    case h <> t:
      h

# A block level is twice its indent, plus 1 when its first line is a case
# arm, plus 65536 times the bracket depth it opened at: a block can open
# inside brackets (f(do M<A>: ..)), and the bracket that closes over it
# closes it.
def Lay.ind(+h: U32) -> U32:
  U32.shrn(U32.and(h, 65535), 1n)

# The level a line at indent ind (and bracket depth d) pops down to.
def Lay.lvl(+ind: U32, +d: U32) -> U32:
  (ind * 2 + 1 + d * 65536 : U32)

def Lay.bd(+h: U32) -> U32:
  U32.shrn(h, 16n)

# The innermost block of case arms at bracket depth d, else top.
def Lay.arms(+top: U32, stack: List<&2, U32>, +d: U32) -> U32:
  match stack:
    case Nil{}:
      top
    case +h <> t:
      Bool.pick(U32, U32.is_eq(Lay.bd(h), d),
        Bool.pick(U32, U32.is_eq(U32.and(h, 1), 1), h, Lay.arms(top, t, d)), top)

def Lay.tok(k: TK, +ln: U32) -> Tok:
  Tok{k, True{}, ln}

# Pops levels deeper than ind, emitting KDe for each.
def Lay.pop(stack: List<&2, U32>, +ind: U32, +acc: List<&2, Tok>, +ln: U32) ->
  List<&2, U32> & List<&2, Tok>:
  match stack:
    case Nil{}:
      (Nil{}, acc)
    case +h <> +t:
      Bool.pick(Unit -> List<&2, U32> & List<&2, Tok>, U32.is_gt(h, ind),
        u => Lay.pop(t, ind, Lay.tok(KDe{}, ln) <> acc, ln),
        u => (h <> t, acc))(Unit{})

def Lay.close(stack: List<&2, U32>, acc: List<&2, Tok>, +d: U32, +ln: U32, lt: Bool) ->
  List<&2, U32> & List<&2, Tok>:
  match lt:
    case True{}:
      Lay.pop(stack, (d * 65536 + 65535 : U32), Lay.tok(KNL{}, ln) <> acc, ln)
    case False{}:
      (stack, acc)

def Lay.toks.go(+k: TK, sp: Bool, +ln: U32, +d: U32, r: List<&2, U32> & List<&2, Tok>) -> LS:
  (stack, acc) = r
  +arrow = Lay.is_sym(k, "=>")
  LS{Tok{k, sp, ln} <> acc, d, Bool.or(Lay.is_sym(k, ":"), arrow), stack, Bool.and(Lay.is_op(k), Bool.not(arrow))}

def Lay.toks(ts: List<&2, Tok>, st: LS) -> LS:
  match ts:
    case Nil{}:
      st
    case Tok{+k, sp, +ln} <> t:
      LS{acc, depth, colon, +stack, op} = st
      +d = (depth + Lay.delta(k) : U32)
      Lay.toks(t, Lay.toks.go(k, sp, ln, d,
        Lay.close(stack, acc, d, ln, U32.is_lt(d, Lay.bd(Lay.top(stack))))))

def Lay.dedent(depth: U32, colon: Bool, +ln: U32, r: List<&2, U32> & List<&2, Tok>) ->
  LS:
  (stack, acc) = r
  LS{acc, depth, colon, stack, False{}}

def Lay.start.open(
  acc: List<&2, Tok>, +depth: U32, colon: Bool, stack: List<&2, U32>, +ind: U32, +ln: U32, arm: Bool
) -> LS:
  LS{Lay.tok(KIn{}, ln) <> acc, depth, colon,
    (ind * 2 + Bool.pick(U32, arm, 1, 0) + depth * 65536 : U32) <> stack, False{}}

def Lay.start.eq(
  acc: List<&2, Tok>, depth: U32, colon: Bool, stack: List<&2, U32>, +ln: U32, lead: Bool
) -> LS:
  match lead:
    case True{}:
      LS{acc, depth, colon, stack, False{}}
    case False{}:
      LS{Lay.tok(KNL{}, ln) <> acc, depth, colon, stack, False{}}

# A deeper case arm closes the blocks above the innermost block of arms.
def Lay.start.stmt(
  acc: List<&2, Tok>, +depth: U32, colon: Bool, +stack: List<&2, U32>, +ln: U32, stmt: Nat
) -> LS:
  match stmt:
    case 0n:
      Lay.dedent(depth, colon, ln, Lay.pop(stack, Lay.arms(Lay.top(stack), stack, depth),
        Lay.tok(KNL{}, ln) <> acc, ln))
    case 1n:
      Lay.start.eq(acc, depth, colon, stack, ln, False{})
    case 2n+p:
      Lay.start.eq(acc, depth, colon, stack, ln, True{})

# A deeper line opens a block after a ':'; else it continues the line before
# it, but one that opens with case or return starts a statement of its own
# (the official parser reads no layout: `case A: 1` then a deeper `case B:`
# are two arms).
def Lay.start.gt(
  acc: List<&2, Tok>, +depth: U32, colon: Bool, +stack: List<&2, U32>, +ind: U32,
  +ln: U32, open: Bool, +stmt: Nat
) -> LS:
  match open:
    case True{}:
      Lay.start.open(acc, depth, colon, stack, ind, ln, Nat.is_eq(stmt, 0n))
    case False{}:
      Lay.start.stmt(acc, depth, colon, stack, ln, stmt)

def Lay.start.cmp(
  acc: List<&2, Tok>, +depth: U32, colon: Bool, stack: List<&2, U32>, +ind: U32, +ln: U32, c: Cmp,
  lead: Bool
) -> LS:
  match c:
    case EQ{}:
      Lay.start.eq(acc, depth, colon, stack, ln, lead)
    case other:
      Lay.dedent(depth, colon, ln, Lay.pop(stack, Lay.lvl(ind, depth), Lay.tok(KNL{}, ln) <> acc, ln))

# A line no deeper than the ':' line before it still opens that line's
# block, at its own indent (a do statement shallower than its head): the
# block runs until a line shallower than it. A line at column 0 is a
# declaration, and a case line an arm of a match around, after an empty
# block (type Empty is Data:, match e:).
def Lay.start.flat(
  acc: List<&2, Tok>, +depth: U32, colon: Bool, stack: List<&2, U32>, +ind: U32, +ln: U32, c: Cmp,
  lead: Bool, open: Bool
) -> LS:
  match open:
    case True{}:
      Lay.start.open(acc, depth, colon, stack, ind, ln, False{})
    case False{}:
      Lay.start.cmp(acc, depth, colon, stack, ind, ln, c, lead)

def Lay.start.go(
  acc: List<&2, Tok>, +depth: U32, +colon: Bool, stack: List<&2, U32>, +ind: U32,
  +ln: U32, c: Cmp, lead: Bool, +stmt: Nat
) -> LS:
  match c:
    case GT{}:
      Lay.start.gt(acc, depth, colon, stack, ind, ln, colon, stmt)
    case other:
      Lay.start.flat(acc, depth, colon, stack, ind, ln, other, lead,
        Bool.and(Bool.and(colon, U32.is_gt(ind, 0)), Bool.not(Nat.is_eq(stmt, 0n))))

def Lay.start.op(
  acc: List<&2, Tok>, depth: U32, colon: Bool, stack: List<&2, U32>, +ind: U32,
  +ln: U32, c: Cmp, op: Bool, lead: Bool, stmt: Nat
) -> LS:
  match op:
    case True{}:
      LS{acc, depth, colon, stack, False{}}
    case False{}:
      Lay.start.go(acc, depth, colon, stack, ind, ln, c, lead, stmt)

# Handles the start of a line at bracket depth 0.
def Lay.start(st: LS, +ind: U32, +ln: U32, lead: Bool, stmt: Nat) -> LS:
  LS{acc, depth, colon, +stack, op} = st
  +top = Lay.top(stack)
  Lay.start.op(acc, depth, colon, stack, ind, ln, U32.cmp(ind, Lay.ind(top)), op, lead, stmt)

def Lay.lead.op(+x: String) -> Bool:
  List.contains(~String, ~String.eq, ["&", "->", "|", "++", "<>"], x)

# A line opening with an infix operator (& B, -> C, ++ s) continues the one
# before it; &x: T -> B is a dependent pair, not a continuation.
def Lay.lead(ts: List<&2, Tok>) -> Bool:
  match ts:
    case Tok{KSym{+x}, a, b} <> Tok{KId{y}, c, d} <> Tok{KSym{z}, e, f} <> t:
      Bool.and(Lay.lead.op(x), Bool.not(Bool.and(String.eq(x, "&"), String.eq(z, ":"))))
    case Tok{KSym{x}, a, b} <> t:
      Lay.lead.op(x)
    case other:
      False{}

# 0 for a line that opens with case, 1 with return (each starts a
# statement), else 2.
def Lay.stmt(ts: List<&2, Tok>) -> Nat:
  match ts:
    case Tok{KId{+x}, a, b} <> t:
      Bool.pick(Nat, String.eq(x, "case"), 0n, Bool.pick(Nat, String.eq(x, "return"), 1n, 2n))
    case other:
      2n

# A line inside brackets opens a block when the one before it ends in ':'
# and it is deeper than the block it sits in.
def Lay.line.open(acc: List<&2, Tok>, depth: U32, colon: Bool, stack: List<&2, U32>, +ind: U32, +ln: U32, op: Bool, gt: Bool) -> LS:
  match gt:
    case True{}:
      Lay.start.open(acc, depth, colon, stack, ind, ln, False{})
    case False{}:
      LS{acc, depth, colon, stack, op}

def Lay.line.open.st(st: LS, +ind: U32, +ln: U32) -> LS:
  LS{acc, depth, colon, +stack, op} = st
  Lay.line.open(acc, depth, colon, stack, ind, ln, op, U32.is_gt(ind, Lay.ind(Lay.top(stack))))

def Lay.line.go(+ind: U32, +ln: U32, +toks: List<&2, Tok>, st: LS, k: Nat) -> LS:
  match k:
    case 0n:
      Lay.toks(toks, Lay.start(st, ind, ln, Lay.lead(toks), Lay.stmt(toks)))
    case 1n:
      Lay.toks(toks, Lay.line.open.st(st, ind, ln))
    case 2n+p:
      Lay.toks(toks, st)

def Lay.line(l: Line, st: LS) -> LS:
  Line{+ind, +ln, toks} = l
  LS{acc, +depth, +colon, +stack, op} = st
  +bd = Lay.bd(Lay.top(stack))
  Lay.line.go(ind, ln, toks, LS{acc, depth, colon, stack, op},
    Bool.pick(Nat, U32.is_eq(depth, bd), 0n, Bool.pick(Nat, colon, 1n, 2n)))

def Lay.lines(ls: List<&2, Line>, st: LS) -> LS:
  match ls:
    case Nil{}:
      st
    case l <> t:
      Lay.lines(t, Lay.line(l, st))

def Lay.finish.go(r: List<&2, U32> & List<&2, Tok>) -> List<&2, Tok>:
  (stack2, acc2) = r
  List.reverse(&2, Tok, Lay.tok(KEof{}, 0) <> acc2)

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
  PFlt{s: String}

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
  DLaw{name: String, params: List<&2, Param>, ret: Expr}
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

# A parser out of fuel (recursion over tokens takes some; no input needs
# as much as Fuel.max gives): an error.
def P.fuel(-A: Type, x: A) -> Parser(A):
  do Parser<A>:
    P.err("out of fuel")
    return x

def P.nls.go(ts: Toks()) -> Unit & Toks():
  match ts:
    case Tok{KNL{}, sp, ln} <> t:
      P.nls.go(t)
    case other:
      (Unit{}, other)

# Skips newlines.
def P.nls() -> Parser(Unit):
  ts => P.nls.go(ts)

# Index of s in xs (or length when absent).
def P.which(+s: String, xs: List<&2, String>) -> Nat:
  match xs:
    case Nil{}:
      0n
    case h <> t:
      Bool.pick(Unit -> Nat, String.eq(s, h), u => 0n, u => 1n+P.which(s, t))(Unit{})

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

# Negation of a numeric literal.
def P.neg(e: Expr) -> Expr:
  match e:
    case ENum{n}:
      ENum{(0 - n : U32)}
    case EFlt{s}:
      EFlt{"-" ++ s}
    case other:
      other

# &x: A -> B as the Sigma it abbreviates (a printer reads its parts).
def P.dep.sigma(+x: String, ty: Expr) -> Expr:
  match ty:
    case ETy{"->", a <> b <> Nil{}}:
      ETy{"Sigma", [ETy{"#q", Nil{}}, ETy{"#q", Nil{}}, a, ELam{PVar{x}, b}]}
    case other:
      ETy{"", Nil{}}

# The erased binders leading a '@-x: A -> B', one "@-" each, ride as a
# marker the parameter's head reads (the JS seam drops those layers).
def P.dep.mark(ty: Expr) -> String:
  match ty:
    case ETy{"", ETy{+h, Nil{}} <> Nil{}}:
      h
    case other:
      ""

def P.dep.arrow(ty: Expr) -> Expr:
  match ty:
    case ETy{"->", a <> b <> Nil{}}:
      ETy{"", [ETy{"@-" ++ P.dep.mark(b), Nil{}}]}
    case other:
      ETy{"", Nil{}}

def P.dep.erased(ty: Expr, e: Bool) -> Expr:
  match e:
    case True{}:
      P.dep.arrow(ty)
    case False{}:
      ETy{"", Nil{}}

def P.dep.fin(+x: String, ty: Expr, amp: Bool, e: Bool) -> Expr:
  match amp:
    case True{}:
      P.dep.sigma(x, ty)
    case False{}:
      P.dep.erased(ty, e)

def P.phead(ty: Expr) -> String:
  match ty:
    case ETy{"", ETy{+h, Nil{}} <> Nil{}}:
      h
    case other:
      P.head(other)

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

def P.op_find(+s: String, xs: List<&2, OpInfo>) -> OpInfo:
  match xs:
    case Nil{}:
      OpInfo{"", 0, False{}}
    case OpInfo{+o, p, r} <> t:
      Bool.pick(Unit -> OpInfo, String.eq(s, o), u => OpInfo{o, p, r},
        u => P.op_find(s, t))(Unit{})

# Binary operator at the head (operators need a space before them).
def P.tok_op(t: Tok) -> OpInfo:
  match t:
    case Tok{KSym{s}, True{}, ln}:
      P.op_find(s, P.ops())
    case other:
      OpInfo{"", 0, False{}}

# The depth after the symbol of P.lscan's index k: 1 to 3 open a bracket,
# 4 to 6 close one.
def P.lscan.depth(+depth: U32, k: Nat) -> U32:
  match k:
    case 0n:
      depth
    case 1n:
      U32.inc(depth)
    case 2n:
      U32.inc(depth)
    case 3n:
      U32.inc(depth)
    case 4n:
      (depth - 1 : U32)
    case 5n:
      (depth - 1 : U32)
    case 6n:
      (depth - 1 : U32)
    case 7n+p:
      depth

# Whether the symbol of index k ends the scan: an '=' does, and at depth 0
# a closing bracket, ';', ',' or '=>'.
def P.lscan.end(+depth: U32, k: Nat) -> Bool:
  match k:
    case 0n:
      True{}
    case 1n:
      False{}
    case 2n:
      False{}
    case 3n:
      False{}
    case 4n+p:
      Bool.and(U32.is_zero(depth), Nat.is_lt(p, 6n))

# Whether an expression opens with 'pat = value;' (an '=' at depth 0
# before any ';', ',', '=>' or closing bracket on the line).
def P.lscan(ts: Toks(), +depth: U32) -> Bool:
  match ts:
    case Tok{KSym{+s}, sp, ln} <> t:
      +k = P.which(s, ["=", "(", "[", "{", ")", "]", "}", ";", ",", "=>"])
      Bool.pick(Unit -> Bool, P.lscan.end(depth, k),
        u => Bool.and(Nat.is_eq(k, 0n), U32.is_zero(depth)),
        u => P.lscan(t, P.lscan.depth(depth, k)))(Unit{})
    case Tok{KId{s}, sp, ln} <> t:
      P.lscan(t, depth)
    case Tok{KNL{}, sp, ln} <> t:
      False{}
    case Tok{KIn{}, sp, ln} <> t:
      False{}
    case Tok{KDe{}, sp, ln} <> t:
      False{}
    case Tok{KEof{}, sp, ln} <> t:
      False{}
    case Nil{}:
      False{}
    case h <> t:
      P.lscan(t, depth)

def P.lscan.ret(+ts: Toks()) -> Bool & Toks():
  (P.lscan(ts, 0), ts)

# What a lambda-match's next arm is: 0 the closing }, 1 K: h, 2 a default.
def P.lmat.kind(ts: Toks()) -> Nat:
  match ts:
    case Tok{KSym{"}"}, a, b} <> t:
      0n
    case Tok{KId{k}, a, b} <> Tok{KSym{":"}, c, d} <> t:
      1n
    case other:
      2n

def P.lmat.peek(+ts: Toks()) -> Nat & Toks():
  (P.lmat.kind(ts), ts)

def P.is_in(t: Tok) -> Bool:
  match t:
    case Tok{KIn{}, sp, ln}:
      True{}
    case other:
      False{}

def P.tok_sp(t: Tok) -> Bool:
  Tok{k, sp, ln} = t
  sp

# Patterns
# ========

def P.pat_seq.stop(+stops: List<&2, String>, +t: Tok) -> Bool:
  Bool.or(P.stuck(P.tok_kind(t)), Bool.or(P.is_nl(t),
    Nat.is_lt(P.tok_which(t, stops), List.length(&2, String, stops))))

# A string literal pattern: a chain of SCon cells.
def P.pstr(s: String) -> Pat:
  match s:
    case SNil{}:
      PCtor{"SNil", Nil{}}
    case SCon{Chr{c}, t}:
      PCtor{"SCon", [PCtor{"Chr", [PNum{c}]}, P.pstr(t)]}

# The pattern parsers, which call each other, as one def (P.pat.go) that a
# selector switches between: each constructor is one parser, with its
# arguments.
type PsP is Data:
  PsPat{}
  PsPatCons{p: Pat, cons: Bool}
  PsPat1{}
  PsPat1K{k: TK}
  PsPatSym{k: Nat}
  PsPatId{name: String, ctor: Bool}
  PsPats{close: String}
  PsPatsGo{close: String, t: Tok, stuck: Bool}
  PsPatsClose{close: String, at: Bool}
  PsPatsItem{close: String}
  PsPatsMore{close: String, more: Bool}

# What a selected parser parses.
def PsP.ty(k: PsP) -> Type:
  match k:
    case PsPat{}:
      Pat
    case PsPatCons{p, cons}:
      Pat
    case PsPat1{}:
      Pat
    case PsPat1K{t}:
      Pat
    case PsPatSym{n}:
      Pat
    case PsPatId{name, ctor}:
      Pat
    case PsPats{close}:
      List<&2, Pat>
    case PsPatsGo{close, t, stuck}:
      List<&2, Pat>
    case PsPatsClose{close, at}:
      List<&2, Pat>
    case PsPatsItem{close}:
      List<&2, Pat>
    case PsPatsMore{close, more}:
      List<&2, Pat>

def P.pat.none(k: PsP) -> Parser(PsP.ty(k)):
  match k:
    case PsPat{}:
      P.fuel(Pat, PVar{"_"})
    case PsPatCons{p, cons}:
      P.fuel(Pat, PVar{"_"})
    case PsPat1{}:
      P.fuel(Pat, PVar{"_"})
    case PsPat1K{t}:
      P.fuel(Pat, PVar{"_"})
    case PsPatSym{n}:
      P.fuel(Pat, PVar{"_"})
    case PsPatId{name, ctor}:
      P.fuel(Pat, PVar{"_"})
    case PsPats{close}:
      P.fuel(List<&2, Pat>, Nil{})
    case PsPatsGo{close, t, stuck}:
      P.fuel(List<&2, Pat>, Nil{})
    case PsPatsClose{close, at}:
      P.fuel(List<&2, Pat>, Nil{})
    case PsPatsItem{close}:
      P.fuel(List<&2, Pat>, Nil{})
    case PsPatsMore{close, more}:
      P.fuel(List<&2, Pat>, Nil{})

def P.pat.go(+fuel: Nat, k: PsP) -> Parser(PsP.ty(k)):
  match fuel:
    case 0n:
      P.pat.none(k)
    case 1n+fl:
      match k:
        case PsPat{}:
          do Parser<Pat>:
            p : Pat <- P.pat.go(fl, PsPat1{})
            t : Tok <- P.peek()
            P.pat.go(fl, PsPatCons{p, P.tok_is(t, "<>")})
        case PsPatCons{p, cons}:
          match cons:
            case True{}:
              do Parser<Pat>:
                P.skip()
                rest : Pat <- P.pat.go(fl, PsPat{})
                return PCtor{"Con", [p, rest]}
            case False{}:
              Parser.pure(Pat, p)
        case PsPat1{}:
          do Parser<Pat>:
            t : Tok <- P.peek()
            P.pat.go(fl, PsPat1K{P.tok_kind(t)})
        case PsPat1K{k1}:
          match k1:
            case KId{name}:
              do Parser<Pat>:
                P.skip()
                +t : Tok <- P.peek()
                P.pat.go(fl, PsPatId{name, Bool.and(P.tok_is(t, "{"), Bool.not(P.tok_sp(t)))})
            case KNat{n}:
              do Parser<Pat>:
                P.skip()
                return PNat{n}
            case KNatPlus{n}:
              do Parser<Pat>:
                P.skip()
                p : Pat <- P.pat.go(fl, PsPat1{})
                return PSucc{n, p}
            case KNum{n}:
              do Parser<Pat>:
                P.skip()
                return PNum{n}
            case KFlt{s}:
              do Parser<Pat>:
                P.skip()
                return PFlt{s}
            case KChr{n}:
              do Parser<Pat>:
                P.skip()
                return PCtor{"Chr", [PNum{n}]}
            case KStr{s}:
              do Parser<Pat>:
                P.skip()
                return P.pstr(s)
            case KSym{s}:
              P.pat.go(fl, PsPatSym{P.which(s, ["+", "-", "(", "["])})
            case other:
              do Parser<Pat>:
                P.err("expected a pattern")
                return PVar{"_"}
        case PsPatSym{n}:
          match n:
            case 0n:
              do Parser<Pat>:
                P.skip()
                P.pat.go(fl, PsPat1{})
            case 1n:
              do Parser<Pat>:
                P.skip()
                P.pat.go(fl, PsPat1{})
            case 2n:
              do Parser<Pat>:
                P.skip()
                ps : List<&2, Pat> <- P.pat.go(fl, PsPats{")"})
                return P.ptuple(ps)
            case 3n:
              do Parser<Pat>:
                P.skip()
                ps : List<&2, Pat> <- P.pat.go(fl, PsPats{"]"})
                return P.plist(ps)
            case 4n+p:
              do Parser<Pat>:
                P.err("expected a pattern")
                return PVar{"_"}
        case PsPatId{+name, ctor}:
          match ctor:
            case True{}:
              do Parser<Pat>:
                P.skip()
                args : List<&2, Pat> <- P.pat.go(fl, PsPats{"}"})
                return PCtor{name, args}
            case False{}:
              Parser.pure(Pat, PVar{name})
        # Comma-separated patterns up to (and including) a closing symbol.
        case PsPats{+close}:
          do Parser<List<&2, Pat>>:
            +t : Tok <- P.peek()
            P.pat.go(fl, PsPatsGo{close, t, P.stuck(P.tok_kind(t))})
        case PsPatsGo{+close, +t, stuck}:
          match stuck:
            case True{}:
              Parser.pure(List<&2, Pat>, Nil{})
            case False{}:
              P.pat.go(fl, PsPatsClose{close, P.tok_is(t, close)})
        case PsPatsClose{+close, at}:
          match at:
            case True{}:
              do Parser<List<&2, Pat>>:
                P.skip()
                return Nil{}
            case False{}:
              P.pat.go(fl, PsPatsItem{close})
        case PsPatsItem{+close}:
          do Parser<List<&2, Pat>>:
            p : Pat <- P.pat.go(fl, PsPat{})
            more : Bool <- P.eat(",")
            rest : List<&2, Pat> <- P.pat.go(fl, PsPatsMore{close, more})
            return p <> rest
        case PsPatsMore{+close, more}:
          match more:
            case True{}:
              P.pat.go(fl, PsPats{close})
            case False{}:
              do Parser<List<&2, Pat>>:
                P.expect(close)
                return Nil{}

def P.pat() -> Parser(Pat):
  P.pat.go(Fuel.max(), PsPat{})

# Space-separated patterns up to (not including) one of the stop symbols.
def P.pat_seq.go(fuel: Nat, +stops: List<&2, String>) -> Parser(List<&2, Pat>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Pat>, Nil{})
    case 1n+fl:
      do Parser<List<&2, Pat>>:
        +t : Tok <- P.peek()
        Bool.pick(Unit -> Parser(List<&2, Pat>), P.pat_seq.stop(stops, t),
          u => Parser.pure(List<&2, Pat>, Nil{}),
          u => do Parser<List<&2, Pat>>:
            p : Pat <- P.pat()
            _c : Bool <- P.eat(",")
            rest : List<&2, Pat> <- P.pat_seq.go(fl, stops)
            return p <> rest)(Unit{})

def P.pat_seq(+stops: List<&2, String>) -> Parser(List<&2, Pat>):
  P.pat_seq.go(Fuel.max(), stops)

# Statements
# ==========

def P.lets(ps: List<&2, Pat>, vs: List<&2, Expr>) -> List<&2, Stmt>:
  match ps vs:
    case p <> pt v <> vt:
      SLet{p, v} <> P.lets(pt, vt)
    case pl vl:
      Nil{}

def P.is_de(t: Tok) -> Bool:
  match t:
    case Tok{KDe{}, sp, ln}:
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

# A parallel let (two names or more) keeps its values together, as one let
# of a %par pattern: its values may run in parallel.
def P.lets.par(+ps: List<&2, Pat>, +vs: List<&2, Expr>) -> List<&2, Stmt>:
  Bool.pick(List<&2, Stmt>, Nat.is_gt(List.length(&2, Pat, ps), 1n),
    [SLet{PCtor{"%par", ps}, ECtor{"%par", vs}}], P.lets(ps, vs))

# The depth after the symbol of P.scan.go's index k: 2 to 4 open a
# bracket, 5 to 7 close one.
def P.scan.depth(+depth: U32, k: Nat) -> U32:
  match k:
    case 0n:
      depth
    case 1n:
      depth
    case 2n:
      U32.inc(depth)
    case 3n:
      U32.inc(depth)
    case 4n:
      U32.inc(depth)
    case 5n:
      (depth - 1 : U32)
    case 6n:
      (depth - 1 : U32)
    case 7n:
      (depth - 1 : U32)
    case 8n+p:
      depth

# Finds the first '=' or '<-' at depth 0 on the current line:
# 0 none, 1 '=', 2 '<-'.
def P.scan.go(ts: Toks(), +depth: U32) -> U32:
  match ts:
    case Nil{}:
      0
    case Tok{KSym{+s}, sp, ln} <> t:
      +k = P.which(s, ["=", "<-", "(", "[", "{", ")", "]", "}"])
      Bool.pick(Unit -> U32, Bool.and(Nat.is_lt(k, 2n), U32.is_zero(depth)),
        u => Bool.pick(U32, Nat.is_eq(k, 0n), 1, 2),
        u => P.scan.go(t, P.scan.depth(depth, k)))(Unit{})
    case Tok{KId{s}, sp, ln} <> t:
      P.scan.go(t, depth)
    case Tok{KNL{}, sp, ln} <> t:
      Bool.pick(Unit -> U32, U32.is_zero(depth), u => 0, u => P.scan.go(t, depth))(Unit{})
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

# A '<-' after a line's leading '(' is an array write, (a[i] <- v)[j] <- w,
# not a bind (whose left side is a name).
def P.scan.lead(ts: Toks(), +r: U32) -> U32:
  match ts:
    case Tok{KSym{s}, sp, ln} <> t:
      Bool.pick(U32, Bool.and(Str.eq(s, "("), U32.is_eq(r, 2)), 0, r)
    case other:
      r

def P.scan.ret(+ts: Toks()) -> U32 & Toks():
  (P.scan.lead(ts, P.scan.go(ts, 0)), ts)

def P.scan() -> Parser(U32):
  ts => P.scan.ret(ts)

# Skips tokens until the matching dedent (consumed).
def P.skip_block.go(ts: Toks(), +depth: U32) -> Toks():
  match ts:
    case Nil{}:
      Nil{}
    case Tok{KIn{}, sp, ln} <> t:
      P.skip_block.go(t, U32.inc(depth))
    case Tok{KDe{}, sp, ln} <> +t:
      Bool.pick(Unit -> Toks(), U32.is_eq(depth, 1), u => t,
        u => P.skip_block.go(t, (depth - 1 : U32)))(Unit{})
    case Tok{KEof{}, sp, ln} <> t:
      Tok{KEof{}, sp, ln} <> t
    case h <> t:
      P.skip_block.go(t, depth)

# Skips the rest of the line (up to, not including, the newline).
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

def P.skip_line() -> Parser(Unit):
  ts => (Unit{}, P.skip_line.go(ts))

def P.tok_which_id(t: Tok, xs: List<&2, String>) -> Nat:
  match t:
    case Tok{KId{s}, sp, ln}:
      P.which(s, xs)
    case other:
      99n

# The expression and statement parsers, which call each other, as one def
# (P.go) that a selector switches between: each constructor is one parser,
# with its arguments, grouped by what the parser parses.
type PsSelE is Data:
  PsExpr{}
  PsArrSize{pow: Bool, t: Tok}
  PsArr{v: Expr}
  PsBraceTail{e: Expr, k: Nat}
  PsDep{amp: Bool}
  PsAmpGo{t: Tok}
  PsBraceBody{}
  PsBraceGo{refl: Bool}
  PsBrace{}
  PsBinLoopGo{min: U32, lhs: Expr, o: String, p: U32, r: Bool, ok: Bool}
  PsBinLoopOp{min: U32, lhs: Expr, op: OpInfo}
  PsBinLoop{min: U32, lhs: Expr}
  PsBin{min: U32}
  PsIlet{}
  PsIexprGo{lets: Bool}
  PsIexpr{}
  PsParenTail{e: Expr, k: Nat}
  PsParenBody{}
  PsParenGo{unit: Bool}
  PsParen{}
  PsBrackTail{e: Expr, arr: Bool}
  PsBrackBody{}
  PsBrackGo{empty: Bool}
  PsBrack{}
  PsLmatGo{k: Nat}
  PsLmat{}
  PsRwEq{first: Expr, at: Bool}
  PsRwTail{semi: Bool}
  PsRw{}
  PsPrimarySym{k: Nat}
  PsAfterIdK{name: String, k: Nat}
  PsLamBody{blk: Bool}
  PsAfterIdGo{name: String, k: Nat, lam: Bool}
  PsAfterId{name: String, t: Tok}
  PsPrimaryId{name: String, is_do: Bool}
  PsPrimaryK{k: TK}
  PsPrimary{}
  PsPostfixSet{e: Expr, i: Expr, set: Bool}
  PsPostfixK{e: Expr, k: Nat}
  PsPostfixT{e: Expr, t: Tok}
  PsPostfix{e: Expr}
  PsTerm{}
  PsDo{}
  PsBody{}
  PsMatch{}

type PsSelL is Data:
  PsListMore{close: String, more: Bool}
  PsListItem{close: String}
  PsListGo{close: String, at_close: Bool}
  PsListStuck{close: String, t: Tok, stuck: Bool}
  PsList{close: String}
  PsParenItem{e: Expr, k: Nat}
  PsParenItemsGo{close: Bool}
  PsParenItems{}
  PsTyargsMore{more: Bool}
  PsTyargsItem{}
  PsTyargsClose{close: Bool}
  PsTyargsGo{t: Tok, stuck: Bool}
  PsTyargs{}
  PsExprsN{n: Nat}
  PsCasesGo{k: Nat}
  PsCasesDe{de: Bool}
  PsCases{}
  PsMatchBody{has: Bool}
  PsScrsGo{t: Tok, stop: Bool}
  PsScrs{}

type PsSelS is Data:
  PsBindArr{name: String, arr: Bool}
  PsBindStmt{}
  PsLetStmt{}
  PsStmtScanGo{k: Nat}
  PsStmtScan{k: U32}
  PsStmtId{k: Nat}
  PsStmtGo{t: Tok, rw: Bool}
  PsStmt{}
  PsStmtsGo{t: Tok, k: Nat}
  PsStmts{}

type PsSelU is Data:
  PsSkipAnnGo{ann: Bool}
  PsSkipAnn{}

type PsSel is Data:
  PsE{s: PsSelE}
  PsL{s: PsSelL}
  PsS{s: PsSelS}
  PsU{s: PsSelU}

# What a selected parser parses.
def PsSel.ty(k: PsSel) -> Type:
  match k:
    case PsE{s}:
      Expr
    case PsL{s}:
      List<&2, Expr>
    case PsS{s}:
      List<&2, Stmt>
    case PsU{s}:
      Unit

def P.none(k: PsSel) -> Parser(PsSel.ty(k)):
  match k:
    case PsE{s}:
      P.fuel(Expr, EErr{""})
    case PsL{s}:
      P.fuel(List<&2, Expr>, Nil{})
    case PsS{s}:
      P.fuel(List<&2, Stmt>, Nil{})
    case PsU{s}:
      P.fuel(Unit, Unit{})

def P.go(+fuel: Nat, sel: PsSel) -> Parser(PsSel.ty(sel)):
  match fuel:
    case 0n:
      P.none(sel)
    case 1n+fl:
      match sel:
        case PsE{q}:
          match q:
            case PsExpr{}:
              P.go(fl, PsE{PsBin{1}})
            case PsArrSize{pow, t}:
              match pow:
                case True{}:
                  P.go(fl, PsE{PsTerm{}})
                case False{}:
                  P.arr.size.lit(t)
            case PsArr{v}:
              do Parser<Expr>:
                P.skip()
                ty : Expr <- P.go(fl, PsE{PsTerm{}})
                t : Tok <- P.peek()
                P.skip()
                t2 : Tok <- P.peek()
                d : Expr <- P.go(fl, PsE{PsArrSize{P.tok_is(t, "^"), t2}})
                P.expect("]")
                return ECall{EVar{"Array.new"}, [ETy{"", Nil{}}, d, EAnn{v, P.head(ty)}]}
            # '{' ... '}': reflexivity, equality type, or annotation.
            case PsBraceTail{e, k}:
              match k:
                case 0n:
                  do Parser<Expr>:
                    P.skip()
                    b : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(":")
                    ty : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("}")
                    return ETy{"==", Nil{}}
                case 1n:
                  do Parser<Expr>:
                    P.skip()
                    b : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(":")
                    ty : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("}")
                    return ETy{"", Nil{}}
                case 2n:
                  do Parser<Expr>:
                    P.skip()
                    ty : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("}")
                    return EAnn{e, P.head(ty)}
                case 3n+p:
                  do Parser<Expr>:
                    P.expect("}")
                    return e
            # '@x: A -> B' and '&x: A -> B' (dependent types), '&1' (quantities).
            case PsDep{amp}:
              do Parser<Expr>:
                e1 : Bool <- P.eat("-")
                e2 : Bool <- P.eat("+")
                x : String <- P.ident()
                P.expect(":")
                ty : Expr <- P.go(fl, PsE{PsExpr{}})
                return P.dep.fin(x, ty, amp, e1)
            case PsAmpGo{t}:
              match t:
                case Tok{KNum{n}, sp, ln}:
                  do Parser<Expr>:
                    P.skip()
                    return ETy{"#q", Nil{}}
                case other:
                  P.go(fl, PsE{PsDep{True{}}})
            case PsBraceBody{}:
              do Parser<Expr>:
                e : Expr <- P.go(fl, PsE{PsExpr{}})
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBraceTail{e, P.tok_which(t, ["==", "!=", ":"])}})
            case PsBraceGo{refl}:
              match refl:
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    P.expect("}")
                    return ETy{"", Nil{}}
                case False{}:
                  P.go(fl, PsE{PsBraceBody{}})
            case PsBrace{}:
              do Parser<Expr>:
                P.skip()
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBraceGo{P.tok_is(t, "==")}})
            case PsBinLoopGo{+min, lhs, o, +p, r, ok}:
              match ok:
                case False{}:
                  Parser.pure(Expr, lhs)
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    rhs : Expr <- P.go(fl, PsE{PsBin{Bool.pick(U32, r, p, U32.inc(p))}})
                    P.go(fl, PsE{PsBinLoop{min, P.mk_bin(o, lhs, rhs)}})
            case PsBinLoopOp{+min, lhs, op}:
              OpInfo{o, +p, r} = op
              P.go(fl, PsE{PsBinLoopGo{min, lhs, o, p, r, Bool.and(U32.is_ne(p, 0), U32.is_ge(p, min))}})
            case PsBinLoop{+min, lhs}:
              do Parser<Expr>:
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBinLoopOp{min, lhs, P.tok_op(t)}})
            case PsBin{min}:
              do Parser<Expr>:
                lhs : Expr <- P.go(fl, PsE{PsTerm{}})
                P.go(fl, PsE{PsBinLoop{min, lhs}})
            case PsIlet{}:
              do Parser<Expr>:
                e1 : Bool <- P.eat("-")
                e2 : Bool <- P.eat("+")
                p : Pat <- P.pat()
                P.go(fl, PsU{PsSkipAnn{}})
                P.expect("=")
                v : Expr <- P.go(fl, PsE{PsExpr{}})
                P.expect(";")
                b : Expr <- P.go(fl, PsE{PsIexpr{}})
                return ELet{p, v, b}
            case PsIexprGo{lets}:
              match lets:
                case True{}:
                  P.go(fl, PsE{PsIlet{}})
                case False{}:
                  P.go(fl, PsE{PsExpr{}})
            # An expression that may open with lets: x = a; y : T = b; e.
            case PsIexpr{}:
              do Parser<Expr>:
                lets : Bool <- ts => P.lscan.ret(ts)
                P.go(fl, PsE{PsIexprGo{lets}})
            case PsParenTail{e, k}:
              match k:
                case 0n:
                  do Parser<Expr>:
                    P.skip()
                    rest : List<&2, Expr> <- P.go(fl, PsL{PsParenItems{}})
                    return P.tuple(e <> rest)
                case 1n:
                  do Parser<Expr>:
                    P.skip()
                    ty : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(")")
                    return EAnn{e, P.head(ty)}
                case 2n+p:
                  do Parser<Expr>:
                    P.expect(")")
                    return e
            case PsParenBody{}:
              do Parser<Expr>:
                e : Expr <- P.go(fl, PsE{PsIexpr{}})
                t : Tok <- P.peek()
                P.go(fl, PsE{PsParenTail{e, P.tok_which(t, [",", ":"])}})
            case PsParenGo{unit}:
              match unit:
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    return ECtor{"Unit", Nil{}}
                case False{}:
                  P.go(fl, PsE{PsParenBody{}})
            # '(' ... ')': unit, tuple, annotation or parens.
            case PsParen{}:
              do Parser<Expr>:
                P.skip()
                t : Tok <- P.peek()
                P.go(fl, PsE{PsParenGo{P.tok_is(t, ")")}})
            case PsBrackTail{e, arr}:
              match arr:
                case True{}:
                  P.go(fl, PsE{PsArr{e}})
                case False{}:
                  do Parser<Expr>:
                    _e : Bool <- P.eat(",")
                    rest : List<&2, Expr> <- P.go(fl, PsL{PsList{"]"}})
                    return P.elist(e <> rest)
            case PsBrackBody{}:
              do Parser<Expr>:
                e : Expr <- P.go(fl, PsE{PsExpr{}})
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBrackTail{e, P.tok_is(t, ":")}})
            case PsBrackGo{empty}:
              match empty:
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    return ECtor{"Nil", Nil{}}
                case False{}:
                  P.go(fl, PsE{PsBrackBody{}})
            case PsBrack{}:
              do Parser<Expr>:
                P.skip()
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBrackGo{P.tok_is(t, "]")}})
            case PsLmatGo{k}:
              match k:
                case 0n:
                  do Parser<Expr>:
                    P.skip()
                    return ECtor{"%efq", Nil{}}
                case 1n:
                  do Parser<Expr>:
                    +c : String <- P.ident()
                    P.expect(":")
                    h : Expr <- P.go(fl, PsE{PsExpr{}})
                    _s : Bool <- P.eat(";")
                    m : Expr <- P.go(fl, PsE{PsLmat{}})
                    return ECtor{"%mat", [ECtor{c, Nil{}}, h, m]}
                case 2n+p:
                  do Parser<Expr>:
                    e : Expr <- P.go(fl, PsE{PsExpr{}})
                    _s : Bool <- P.eat(";")
                    P.expect("}")
                    return e
            # The arms of \{K: h; ...; m} after its {: K's fields go to h, any other
            # value to m; \{} (no m) matches nothing. LM.expr unfolds it once the
            # constructors' arities are known.
            case PsLmat{}:
              do Parser<Expr>:
                P.nls()
                k : Nat <- ts => P.lmat.peek(ts)
                P.go(fl, PsE{PsLmatGo{k}})
            # A rewrite %e@E : P; f (or %E : P; f) is its tail f: the equation is
            # erased evidence. On its own line the tail is the next statement.
            case PsRwEq{first, at}:
              match at:
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    P.go(fl, PsE{PsTerm{}})
                case False{}:
                  Parser.pure(Expr, first)
            case PsRwTail{semi}:
              match semi:
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    P.go(fl, PsE{PsIexpr{}})
                case False{}:
                  Parser.pure(Expr, ECtor{"Unit", Nil{}})
            case PsRw{}:
              do Parser<Expr>:
                P.skip()
                first : Expr <- P.go(fl, PsE{PsTerm{}})
                t : Tok <- P.peek()
                e : Expr <- P.go(fl, PsE{PsRwEq{first, P.tok_is(t, "@")}})
                P.expect(":")
                ty : Expr <- P.go(fl, PsE{PsExpr{}})
                t2 : Tok <- P.peek()
                P.go(fl, PsE{PsRwTail{P.tok_is(t2, ";")}})
            case PsPrimarySym{k}:
              match k:
                case 0n:
                  P.go(fl, PsE{PsParen{}})
                case 1n:
                  P.go(fl, PsE{PsBrack{}})
                case 2n:
                  P.go(fl, PsE{PsBrace{}})
                case 3n:
                  do Parser<Expr>:
                    P.skip()
                    P.go(fl, PsE{PsTerm{}})
                case 4n:
                  do Parser<Expr>:
                    P.skip()
                    P.go(fl, PsE{PsTerm{}})
                case 5n:
                  do Parser<Expr>:
                    P.skip()
                    e : Expr <- P.go(fl, PsE{PsTerm{}})
                    return P.neg(e)
                case 6n:
                  do Parser<Expr>:
                    P.skip()
                    P.go(fl, PsE{PsDep{False{}}})
                case 7n:
                  do Parser<Expr>:
                    P.skip()
                    t : Tok <- P.peek()
                    P.go(fl, PsE{PsAmpGo{t}})
                case 8n:
                  do Parser<Expr>:
                    P.skip()
                    x : String <- P.ident()
                    return ETy{"", Nil{}}
                case 9n:
                  do Parser<Expr>:
                    P.skip()
                    P.expect("{")
                    P.go(fl, PsE{PsLmat{}})
                case 10n:
                  P.go(fl, PsE{PsRw{}})
                case 11n+p:
                  do Parser<Expr>:
                    P.err("unexpected symbol")
                    return EErr{""}
            case PsAfterIdK{+name, k}:
              match k:
                case 0n:
                  do Parser<Expr>:
                    P.skip()
                    args : List<&2, Expr> <- P.go(fl, PsL{PsList{"}"}})
                    return ECtor{name, args}
                case 1n:
                  do Parser<Expr>:
                    P.skip()
                    args : List<&2, Expr> <- P.go(fl, PsL{PsTyargs{}})
                    return ETy{name, args}
                case 2n+p:
                  Parser.pure(Expr, EVar{name})
            # A lambda's body: an expression, or a block on the lines below its '=>'.
            case PsLamBody{blk}:
              match blk:
                case True{}:
                  P.go(fl, PsE{PsBody{}})
                case False{}:
                  P.go(fl, PsE{PsIexpr{}})
            case PsAfterIdGo{+name, k, lam}:
              match lam:
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    t : Tok <- P.peek()
                    body : Expr <- P.go(fl, PsE{PsLamBody{P.is_in(t)}})
                    return ELam{PVar{name}, body}
                case False{}:
                  P.go(fl, PsE{PsAfterIdK{name, k}})
            # After an identifier: lambda, constructor, type application or variable.
            case PsAfterId{+name, +t}:
              P.go(fl, PsE{PsAfterIdGo{name, Bool.pick(Nat, P.tok_sp(t), 3n, P.tok_which(t, ["{", "<"])),
                P.tok_is(t, "=>")}})
            # A name, or a do block as a term.
            case PsPrimaryId{+name, is_do}:
              match is_do:
                case True{}:
                  P.go(fl, PsE{PsDo{}})
                case False{}:
                  do Parser<Expr>:
                    P.skip()
                    t : Tok <- P.peek()
                    P.go(fl, PsE{PsAfterId{name, t}})
            case PsPrimaryK{k}:
              match k:
                case KId{+name}:
                  P.go(fl, PsE{PsPrimaryId{name, Str.eq(name, "do")}})
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
                    e : Expr <- P.go(fl, PsE{PsTerm{}})
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
                  P.go(fl, PsE{PsPrimarySym{P.which(s, ["(", "[", "{", "~", "+", "-", "@", "&", "?", "\\", "%"])}})
                case other:
                  do Parser<Expr>:
                    P.err("expected an expression")
                    return EErr{""}
            case PsPrimary{}:
              do Parser<Expr>:
                t : Tok <- P.peek()
                P.go(fl, PsE{PsPrimaryK{P.tok_kind(t)}})
            # a[i], or the write a[i] <- v (the written array).
            case PsPostfixSet{e, i, set}:
              match set:
                case True{}:
                  do Parser<Expr>:
                    P.skip()
                    v : Expr <- P.go(fl, PsE{PsExpr{}})
                    return ECall{EVar{"Array.set"}, [ETy{"U32", Nil{}}, e, i, v]}
                case False{}:
                  P.go(fl, PsE{PsPostfix{ECall{EVar{"Array.get"}, [ETy{"U32", Nil{}}, e, i]}}})
            # Postfix: calls f(..), f!(..), and indexing a[i].
            case PsPostfixK{e, k}:
              match k:
                case 0n:
                  do Parser<Expr>:
                    P.skip()
                    args : List<&2, Expr> <- P.go(fl, PsL{PsList{")"}})
                    P.go(fl, PsE{PsPostfix{ECall{e, args}}})
                case 1n:
                  do Parser<Expr>:
                    P.skip()
                    P.expect("(")
                    args : List<&2, Expr> <- P.go(fl, PsL{PsList{")"}})
                    P.go(fl, PsE{PsPostfix{ECall{EVar{"%gpu"}, e <> args}}})
                case 2n:
                  do Parser<Expr>:
                    P.skip()
                    i : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("]")
                    t : Tok <- P.peek()
                    P.go(fl, PsE{PsPostfixSet{e, i, P.tok_is(t, "<-")}})
                case 3n+p:
                  Parser.pure(Expr, e)
            case PsPostfixT{e, +t}:
              P.go(fl, PsE{PsPostfixK{e, Bool.pick(Nat, P.tok_sp(t), 9n, P.tok_which(t, ["(", "!", "["]))}})
            case PsPostfix{e}:
              do Parser<Expr>:
                t : Tok <- P.peek()
                P.go(fl, PsE{PsPostfixT{e, t}})
            case PsTerm{}:
              do Parser<Expr>:
                e : Expr <- P.go(fl, PsE{PsPrimary{}})
                P.go(fl, PsE{PsPostfix{e}})
            case PsDo{}:
              do Parser<Expr>:
                P.skip()
                m : String <- P.ident()
                P.expect("<")
                +args : List<&2, Expr> <- P.go(fl, PsL{PsTyargs{}})
                P.expect(":")
                P.expect_in()
                ss : List<&2, Stmt> <- P.go(fl, PsS{PsStmts{}})
                return Fold.do(m, P.init(args), P.last(args), ss)
            # A block body: an indented statement list, folded.
            case PsBody{}:
              do Parser<Expr>:
                P.expect_in()
                ss : List<&2, Stmt> <- P.go(fl, PsS{PsStmts{}})
                return Fold.plain(ss)
            case PsMatch{}:
              do Parser<Expr>:
                P.skip()
                scrs : List<&2, Expr> <- P.go(fl, PsL{PsScrs{}})
                P.expect(":")
                t : Tok <- P.peek()
                cases : List<&2, Expr> <- P.go(fl, PsL{PsMatchBody{P.is_in(t)}})
                return EMatch{scrs, cases}
        case PsL{q}:
          match q:
            # Comma-separated expressions up to (and including) a closing symbol.
            case PsListMore{+close, more}:
              match more:
                case True{}:
                  P.go(fl, PsL{PsList{close}})
                case False{}:
                  do Parser<List<&2, Expr>>:
                    P.expect(close)
                    return Nil{}
            case PsListItem{+close}:
              do Parser<List<&2, Expr>>:
                e : Expr <- P.go(fl, PsE{PsExpr{}})
                more : Bool <- P.eat(",")
                rest : List<&2, Expr> <- P.go(fl, PsL{PsListMore{close, more}})
                return e <> rest
            case PsListGo{+close, at_close}:
              match at_close:
                case True{}:
                  do Parser<List<&2, Expr>>:
                    P.skip()
                    return Nil{}
                case False{}:
                  P.go(fl, PsL{PsListItem{close}})
            case PsListStuck{+close, +t, stuck}:
              match stuck:
                case True{}:
                  do Parser<List<&2, Expr>>:
                    P.err("unterminated list")
                    return Nil{}
                case False{}:
                  P.go(fl, PsL{PsListGo{close, P.tok_is(t, close)}})
            case PsList{+close}:
              do Parser<List<&2, Expr>>:
                +t : Tok <- P.peek()
                P.go(fl, PsL{PsListStuck{close, t, P.stuck(P.tok_kind(t))}})
            case PsParenItem{e, k}:
              match k:
                case 0n:
                  do Parser<List<&2, Expr>>:
                    P.skip()
                    rest : List<&2, Expr> <- P.go(fl, PsL{PsParenItems{}})
                    return e <> rest
                case 1n:
                  do Parser<List<&2, Expr>>:
                    P.skip()
                    ty : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(")")
                    return [EAnn{e, P.head(ty)}]
                case 2n+p:
                  do Parser<List<&2, Expr>>:
                    P.expect(")")
                    return [e]
            # A tuple's elements after its first ',': (a, b, c : T) annotates c alone.
            case PsParenItemsGo{close}:
              match close:
                case True{}:
                  do Parser<List<&2, Expr>>:
                    P.skip()
                    return Nil{}
                case False{}:
                  do Parser<List<&2, Expr>>:
                    e : Expr <- P.go(fl, PsE{PsIexpr{}})
                    t : Tok <- P.peek()
                    P.go(fl, PsL{PsParenItem{e, P.tok_which(t, [",", ":"])}})
            case PsParenItems{}:
              do Parser<List<&2, Expr>>:
                t : Tok <- P.peek()
                P.go(fl, PsL{PsParenItemsGo{P.tok_is(t, ")")}})
            case PsTyargsMore{more}:
              match more:
                case True{}:
                  P.go(fl, PsL{PsTyargs{}})
                case False{}:
                  do Parser<List<&2, Expr>>:
                    P.gt()
                    return Nil{}
            case PsTyargsItem{}:
              do Parser<List<&2, Expr>>:
                e : Expr <- P.go(fl, PsE{PsExpr{}})
                more : Bool <- P.eat(",")
                rest : List<&2, Expr> <- P.go(fl, PsL{PsTyargsMore{more}})
                return e <> rest
            case PsTyargsClose{close}:
              match close:
                case True{}:
                  do Parser<List<&2, Expr>>:
                    P.gt()
                    return Nil{}
                case False{}:
                  P.go(fl, PsL{PsTyargsItem{}})
            case PsTyargsGo{+t, stuck}:
              match stuck:
                case True{}:
                  Parser.pure(List<&2, Expr>, Nil{})
                case False{}:
                  P.go(fl, PsL{PsTyargsClose{P.is_gt(t)}})
            case PsTyargs{}:
              do Parser<List<&2, Expr>>:
                +t : Tok <- P.peek()
                P.go(fl, PsL{PsTyargsGo{t, P.stuck(P.tok_kind(t))}})
            # Values of a parallel let: one expression per pattern.
            case PsExprsN{n}:
              match n:
                case 0n:
                  Parser.pure(List<&2, Expr>, Nil{})
                case 1n+p:
                  do Parser<List<&2, Expr>>:
                    e : Expr <- P.go(fl, PsE{PsExpr{}})
                    rest : List<&2, Expr> <- P.go(fl, PsL{PsExprsN{p}})
                    return e <> rest
            # A 'case' list of a match.
            case PsCasesGo{k}:
              match k:
                case 0n:
                  do Parser<List<&2, Expr>>:
                    P.skip()
                    ps : List<&2, Pat> <- P.pat_seq([":"])
                    P.expect(":")
                    body : Expr <- P.go(fl, PsE{PsBody{}})
                    rest : List<&2, Expr> <- P.go(fl, PsL{PsCases{}})
                    return ECase{ps, body} <> rest
                case 1n+p:
                  Parser.pure(List<&2, Expr>, Nil{})
            case PsCasesDe{de}:
              match de:
                case True{}:
                  do Parser<List<&2, Expr>>:
                    P.skip()
                    return Nil{}
                case False{}:
                  do Parser<List<&2, Expr>>:
                    +t : Tok <- P.peek()
                    P.go(fl, PsL{PsCasesGo{P.tok_which_id(t, ["case"])}})
            case PsCases{}:
              do Parser<List<&2, Expr>>:
                P.nls()
                t : Tok <- P.peek()
                P.go(fl, PsL{PsCasesDe{P.is_de(t)}})
            case PsMatchBody{has}:
              match has:
                case True{}:
                  do Parser<List<&2, Expr>>:
                    P.skip()
                    P.go(fl, PsL{PsCases{}})
                case False{}:
                  Parser.pure(List<&2, Expr>, Nil{})
            case PsScrsGo{+t, stop}:
              match stop:
                case True{}:
                  Parser.pure(List<&2, Expr>, Nil{})
                case False{}:
                  do Parser<List<&2, Expr>>:
                    e : Expr <- P.go(fl, PsE{PsExpr{}})
                    _c : Bool <- P.eat(",")
                    rest : List<&2, Expr> <- P.go(fl, PsL{PsScrs{}})
                    return e <> rest
            case PsScrs{}:
              do Parser<List<&2, Expr>>:
                +t : Tok <- P.peek()
                P.go(fl, PsL{PsScrsGo{t, Bool.or(P.tok_is(t, ":"), P.stuck(P.tok_kind(t)))}})
        case PsS{q}:
          match q:
            # Array write 'a[i] <- v' or monadic bind 'x : T <- v' / 'x <- v'.
            case PsBindArr{+name, arr}:
              match arr:
                case True{}:
                  do Parser<List<&2, Stmt>>:
                    P.skip()
                    i : Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("]")
                    P.expect("<-")
                    v : Expr <- P.go(fl, PsE{PsExpr{}})
                    return [SLet{PVar{name}, ECall{EVar{"Array.set"}, [ETy{"U32", Nil{}}, EVar{name}, i, v]}}]
                case False{}:
                  do Parser<List<&2, Stmt>>:
                    P.go(fl, PsU{PsSkipAnn{}})
                    P.expect("<-")
                    v : Expr <- P.go(fl, PsE{PsExpr{}})
                    return [SBind{name, v}]
            case PsBindStmt{}:
              do Parser<List<&2, Stmt>>:
                e1 : Bool <- P.eat("+")
                name : String <- P.ident()
                +t : Tok <- P.peek()
                P.go(fl, PsS{PsBindArr{name, Bool.and(P.tok_is(t, "["), Bool.not(P.tok_sp(t)))}})
            case PsLetStmt{}:
              do Parser<List<&2, Stmt>>:
                +ps : List<&2, Pat> <- P.pat_seq(["=", ":"])
                P.go(fl, PsU{PsSkipAnn{}})
                P.expect("=")
                +vs : List<&2, Expr> <- P.go(fl, PsL{PsExprsN{List.length(&2, Pat, ps)}})
                return P.lets.par(ps, vs)
            case PsStmtScanGo{k}:
              match k:
                case 0n:
                  do Parser<List<&2, Stmt>>:
                    e : Expr <- P.go(fl, PsE{PsExpr{}})
                    return [SExp{e}]
                case 1n:
                  P.go(fl, PsS{PsLetStmt{}})
                case 2n+p:
                  P.go(fl, PsS{PsBindStmt{}})
            case PsStmtScan{k}:
              P.go(fl, PsS{PsStmtScanGo{U32.to_nat(k)}})
            case PsStmtId{k}:
              match k:
                case 0n:
                  do Parser<List<&2, Stmt>>:
                    e : Expr <- P.go(fl, PsE{PsMatch{}})
                    return [SExp{e}]
                case 1n:
                  do Parser<List<&2, Stmt>>:
                    P.skip()
                    e : Expr <- P.go(fl, PsE{PsExpr{}})
                    return [SRet{e}]
                case 2n:
                  do Parser<List<&2, Stmt>>:
                    e : Expr <- P.go(fl, PsE{PsDo{}})
                    return [SExp{e}]
                case 3n+p:
                  do Parser<List<&2, Stmt>>:
                    k : U32 <- P.scan()
                    P.go(fl, PsS{PsStmtScan{k}})
            case PsStmtGo{+t, rw}:
              match rw:
                case True{}:
                  do Parser<List<&2, Stmt>>:
                    P.skip_line()
                    return [SSkip{}]
                case False{}:
                  P.go(fl, PsS{PsStmtId{P.tok_which_id(t, ["match", "return", "do"])}})
            case PsStmt{}:
              do Parser<List<&2, Stmt>>:
                +t : Tok <- P.peek()
                P.go(fl, PsS{PsStmtGo{t, P.tok_is(t, "%")}})
            case PsStmtsGo{+t, k}:
              match k:
                case 0n:
                  do Parser<List<&2, Stmt>>:
                    P.skip()
                    return Nil{}
                case 1n:
                  Parser.pure(List<&2, Stmt>, Nil{})
                case 2n+p:
                  do Parser<List<&2, Stmt>>:
                    s : List<&2, Stmt> <- P.go(fl, PsS{PsStmt{}})
                    rest : List<&2, Stmt> <- P.go(fl, PsS{PsStmts{}})
                    return List.append(&2, Stmt, s, rest)
            # Statements up to (and including) the block's dedent.
            case PsStmts{}:
              do Parser<List<&2, Stmt>>:
                P.nls()
                +t : Tok <- P.peek()
                P.go(fl, PsS{PsStmtsGo{t, Bool.pick(Nat, P.is_de(t), 0n,
                  Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n))}})
        case PsU{q}:
          match q:
            case PsSkipAnnGo{ann}:
              match ann:
                case True{}:
                  do Parser<Unit>:
                    P.skip()
                    ty : Expr <- P.go(fl, PsE{PsExpr{}})
                    return Unit{}
                case False{}:
                  Parser.pure(Unit, Unit{})
            # Skips an optional ': Type' annotation.
            case PsSkipAnn{}:
              do Parser<Unit>:
                t : Tok <- P.peek()
                P.go(fl, PsU{PsSkipAnnGo{P.tok_is(t, ":")}})

def P.expr() -> Parser(Expr):
  P.go(Fuel.max(), PsE{PsExpr{}})

def P.skip_ann() -> Parser(Unit):
  P.go(Fuel.max(), PsU{PsSkipAnn{}})

def P.stmts() -> Parser(List<&2, Stmt>):
  P.go(Fuel.max(), PsS{PsStmts{}})

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
        return Param{name, mode, P.phead(ty)}
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

# The parameter-list parsers, which call each other, as one def: a
# selector picks the parser (with its arguments).
type PsParamsSel is Data:
  PsParamsMore{more: Bool}
  PsParamsGo{close: Bool}
  PsParams{}

def P.params.sel(+fuel: Nat, sel: PsParamsSel) -> Parser(List<&2, Param>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Param>, Nil{})
    case 1n+fl:
      match sel:
        case PsParamsMore{more}:
          match more:
            case True{}:
              P.params.sel(fl, PsParams{})
            case False{}:
              do Parser<List<&2, Param>>:
                P.expect(")")
                return Nil{}
        case PsParamsGo{close}:
          match close:
            case True{}:
              do Parser<List<&2, Param>>:
                P.skip()
                return Nil{}
            case False{}:
              do Parser<List<&2, Param>>:
                p : Param <- P.param()
                more : Bool <- P.eat(",")
                rest : List<&2, Param> <- P.params.sel(fl, PsParamsMore{more})
                return p <> rest
        # Parameters up to (and including) ')'.
        case PsParams{}:
          do Parser<List<&2, Param>>:
            +t : Tok <- P.peek()
            P.params.sel(fl, PsParamsGo{Bool.or(P.tok_is(t, ")"), P.stuck(P.tok_kind(t)))})

def P.params() -> Parser(List<&2, Param>):
  P.params.sel(Fuel.max(), PsParams{})

def P.def() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    name : String <- P.ident()
    unsafe : Bool <- P.eat("?")
    P.expect("(")
    params : List<&2, Param> <- P.params()
    t : Tok <- P.peek()
    ret : Expr <- P.ret.go(P.tok_is(t, "->"))
    P.expect(":")
    P.expect_in()
    t2 : Tok <- P.peek()
    P.def.body(name, params, ret, P.tok_is_id(t2, "import"))

# The field-list parsers, which call each other, as one def: a selector
# picks the parser (with its arguments).
type PsFieldsSel is Data:
  PsFieldsGo{close: Bool}
  PsFields{}

def P.fields.sel(+fuel: Nat, sel: PsFieldsSel) -> Parser(List<&2, Field>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Field>, Nil{})
    case 1n+fl:
      match sel:
        case PsFieldsGo{close}:
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
                rest : List<&2, Field> <- P.fields.sel(fl, PsFields{})
                return Field{name, ty} <> rest
        # Constructor fields up to (and including) '}'.
        case PsFields{}:
          do Parser<List<&2, Field>>:
            +t : Tok <- P.peek()
            P.fields.sel(fl, PsFieldsGo{Bool.or(P.tok_is(t, "}"), P.stuck(P.tok_kind(t)))})

def P.fields() -> Parser(List<&2, Field>):
  P.fields.sel(Fuel.max(), PsFields{})

# The constructor-list parsers, which call each other, as one def: a
# selector picks the parser (with its arguments).
type PsCtorsSel is Data:
  PsCtorsGo{t: Tok, k: Nat}
  PsCtors{}

def P.ctors.sel(+fuel: Nat, sel: PsCtorsSel) -> Parser(List<&2, Ctor>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Ctor>, Nil{})
    case 1n+fl:
      match sel:
        case PsCtorsGo{+t, k}:
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
                rest : List<&2, Ctor> <- P.ctors.sel(fl, PsCtors{})
                return Ctor{name, fields} <> rest
        # Constructor lines up to (and including) the dedent.
        case PsCtors{}:
          do Parser<List<&2, Ctor>>:
            P.nls()
            +t : Tok <- P.peek()
            P.ctors.sel(fl, PsCtorsGo{t, Bool.pick(Nat, P.is_de(t), 0n,
              Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n))})

def P.ctors() -> Parser(List<&2, Ctor>):
  P.ctors.sel(Fuel.max(), PsCtors{})

def P.type.body(has: Bool) -> Parser(List<&2, Ctor>):
  match has:
    case True{}:
      do Parser<List<&2, Ctor>>:
        P.skip()
        P.ctors()
    case False{}:
      Parser.pure(List<&2, Ctor>, Nil{})

def P.until_is.go(ts: Toks()) -> Toks():
  match ts:
    case Nil{}:
      Nil{}
    case Tok{KId{+s}, sp, ln} <> +t:
      Bool.pick(Unit -> Toks(), Str.eq(s, "is"), u => t, u => P.until_is.go(t))(Unit{})
    case Tok{KEof{}, sp, ln} <> t:
      Tok{KEof{}, sp, ln} <> t
    case Tok{KErr{e}, sp, ln} <> t:
      Tok{KErr{e}, sp, ln} <> t
    case h <> t:
      P.until_is.go(t)

# Skips to just after the 'is' keyword.
def P.until_is() -> Parser(Unit):
  ts => (Unit{}, P.until_is.go(ts))

# The parsers of a law's 'for' lines, which call each other, as one def:
# a selector picks the parser (with its arguments).
type PsLawSel is Data:
  PsLawLines{}
  PsLawLine{k: Nat}
  PsLawGo{t: Tok, k: Nat}

def P.law.sel(+fuel: Nat, sel: PsLawSel) -> Parser(List<&2, Param>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Param>, Nil{})
    case 1n+fl:
      match sel:
        # The 'for' parameters of a law, up to (and including) the dedent.
        case PsLawLines{}:
          do Parser<List<&2, Param>>:
            P.nls()
            +t : Tok <- P.peek()
            P.law.sel(fl, PsLawGo{t, Bool.pick(Nat, P.is_de(t), 0n,
              Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n))})
        case PsLawLine{k}:
          match k:
            case 0n:
              do Parser<List<&2, Param>>:
                P.skip()
                p : Param <- P.param()
                P.skip_line()
                rest : List<&2, Param> <- P.law.sel(fl, PsLawLines{})
                return p <> rest
            case 1n+p:
              do Parser<List<&2, Param>>:
                P.skip_line()
                P.law.sel(fl, PsLawLines{})
        case PsLawGo{+t, k}:
          match k:
            case 0n:
              do Parser<List<&2, Param>>:
                P.skip()
                return Nil{}
            case 1n:
              Parser.pure(List<&2, Param>, Nil{})
            case 2n+p:
              P.law.sel(fl, PsLawLine{P.tok_which_id(t, ["for"])})

def P.law.lines() -> Parser(List<&2, Param>):
  P.law.sel(Fuel.max(), PsLawLines{})

# The type of a def that writes none.
def P.no_ty(e: Expr) -> Bool:
  match e:
    case ETy{n, args}:
      String.is_empty(n)
    case other:
      False{}

def P.look.fin(-A: Type, r: A & Toks(), ts: Toks()) -> A & Toks():
  (a, rest) = r
  (a, ts)

def P.look.go(-A: Type, p: Parser(A), +ts: Toks()) -> A & Toks():
  P.look.fin(A, p(ts), ts)

# p's answer, without consuming anything.
def P.look(-A: Type, p: Parser(A)) -> Parser(A):
  ts => P.look.go(A, p, ts)

def P.law.ty.pick(e: Expr, rest: Toks()) -> Expr:
  match rest:
    case Tok{KNL{}, sp, ln} <> t:
      e
    case Tok{KDe{}, sp, ln} <> t:
      e
    case other:
      ETy{"", Nil{}}

def P.law.ty.fin(r: Expr & Toks(), ts: Toks()) -> Expr & Toks():
  (e, rest) = r
  (P.law.ty.pick(e, rest), ts)

def P.law.ty.go(+ts: Toks()) -> Expr & Toks():
  P.law.ty.fin(P.expr()(ts), ts)

# A law's type line as a type, when it reads as one to its end (a claim like
# {a == b : T} may not): the type of a def that fills the law and writes none.
def P.law.ty() -> Parser(Expr):
  ts => P.law.ty.go(ts)

# The parsers of a law's type, which call each other, as one def: a
# selector picks the parser (with its arguments).
type PsRetsSel is Data:
  PsLawRetsLine{k: Nat}
  PsLawRetsGo{t: Tok, k: Nat}
  PsLawRets{}

def P.law.rets.sel(+fuel: Nat, sel: PsRetsSel) -> Parser(Expr):
  match fuel:
    case 0n:
      P.fuel(Expr, ETy{"", Nil{}})
    case 1n+fl:
      match sel:
        case PsLawRetsLine{k}:
          match k:
            case 0n:
              do Parser<Expr>:
                P.skip_line()
                P.law.rets.sel(fl, PsLawRets{})
            case 1n:
              do Parser<Expr>:
                P.skip()
                +x : String <- P.ident()
                P.expect(":")
                ty : Expr <- P.expr()
                P.skip_line()
                rest : Expr <- P.law.rets.sel(fl, PsLawRets{})
                return ETy{"Sigma", [ETy{"#q", Nil{}}, ETy{"#q", Nil{}}, ty, ELam{PVar{x}, rest}]}
            case 2n+p:
              do Parser<Expr>:
                +e : Expr <- P.law.ty()
                P.skip_line()
                +rest : Expr <- P.law.rets.sel(fl, PsLawRets{})
                return Bool.pick(Expr, P.no_ty(rest), e, rest)
        case PsLawRetsGo{+t, k}:
          match k:
            case 0n:
              Parser.pure(Expr, ETy{"", Nil{}})
            case 1n:
              Parser.pure(Expr, ETy{"", Nil{}})
            case 2n+p:
              P.law.rets.sel(fl, PsLawRetsLine{P.tok_which_id(t, ["for", "exs"])})
        # The type of a law: its last line that is not a 'for'.
        case PsLawRets{}:
          do Parser<Expr>:
            P.nls()
            +t : Tok <- P.peek()
            P.law.rets.sel(fl, PsLawRetsGo{t, Bool.pick(Nat, P.is_de(t), 0n,
              Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n))})

def P.law.rets() -> Parser(Expr):
  P.law.rets.sel(Fuel.max(), PsLawRets{})

def P.law() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    name : String <- P.ident()
    P.expect(":")
    P.expect_in()
    ret : Expr <- P.look(Expr, P.law.rets())
    params : List<&2, Param> <- P.law.lines()
    return DLaw{name, params, ret}

# The type-parameter parsers, which call each other, as one def: a
# selector picks the parser (with its arguments).
type PsTparamsSel is Data:
  PsTparamsMore{more: Bool}
  PsTparams{}

def P.tparams.sel(+fuel: Nat, sel: PsTparamsSel) -> Parser(List<&2, String>):
  match fuel:
    case 0n:
      P.fuel(List<&2, String>, Nil{})
    case 1n+fl:
      match sel:
        case PsTparamsMore{more}:
          match more:
            case True{}:
              P.tparams.sel(fl, PsTparams{})
            case False{}:
              do Parser<List<&2, String>>:
                P.gt()
                return Nil{}
        case PsTparams{}:
          do Parser<List<&2, String>>:
            e1 : Bool <- P.eat("-")
            name : String <- P.ident()
            P.skip_ann()
            more : Bool <- P.eat(",")
            rest : List<&2, String> <- P.tparams.sel(fl, PsTparamsMore{more})
            return name <> rest

def P.tparams() -> Parser(List<&2, String>):
  P.tparams.sel(Fuel.max(), PsTparams{})

# Type parameters '<a, -A: Kind(a)>' ('<-' starts one with an erased mark).
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

# The path: the text of the tokens up to 'as' or the end of the line.
def P.import.path.go(ts: Toks()) -> String & Toks():
  match ts:
    case Tok{KId{+s}, +sp, +ln} <> +t:
      Bool.pick(Unit -> String & Toks(), Str.eq(s, "as"), u => ("", Tok{KId{s}, sp, ln} <> t),
        u => P.import.path.cat(s, P.import.path.go(t)))(Unit{})
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

# A declaration's parsers ('@' marks go before it) as one def: a selector
# picks the parser (with its arguments).
type PsDeclSel is Data:
  PsDeclAt{at: Bool, t: Tok}
  PsDecl{}

def P.decl.sel(+fuel: Nat, sel: PsDeclSel) -> Parser(Decl):
  match fuel:
    case 0n:
      P.fuel(Decl, DImport{"", ""})
    case 1n+fl:
      match sel:
        case PsDeclAt{at, +t}:
          match at:
            case True{}:
              do Parser<Decl>:
                P.skip()
                P.skip()
                P.nls()
                P.decl.sel(fl, PsDecl{})
            case False{}:
              P.decl.go(P.tok_which_id(t, ["def", "type", "law", "import"]))
        case PsDecl{}:
          do Parser<Decl>:
            +t : Tok <- P.peek()
            P.decl.sel(fl, PsDeclAt{P.tok_is(t, "@"), t})

def P.decl() -> Parser(Decl):
  P.decl.sel(Fuel.max(), PsDecl{})

# The declaration-list parsers, which call each other, as one def: a
# selector picks the parser (with its arguments).
type PsDeclsSel is Data:
  PsDeclsGo{stop: Bool}
  PsDecls{}

def P.decls.sel(+fuel: Nat, sel: PsDeclsSel) -> Parser(List<&2, Decl>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Decl>, Nil{})
    case 1n+fl:
      match sel:
        case PsDeclsGo{stop}:
          match stop:
            case True{}:
              Parser.pure(List<&2, Decl>, Nil{})
            case False{}:
              do Parser<List<&2, Decl>>:
                d : Decl <- P.decl()
                rest : List<&2, Decl> <- P.decls.sel(fl, PsDecls{})
                return d <> rest
        case PsDecls{}:
          do Parser<List<&2, Decl>>:
            P.nls()
            t : Tok <- P.peek()
            P.decls.sel(fl, PsDeclsGo{P.stuck(P.tok_kind(t))})

def P.decls() -> Parser(List<&2, Decl>):
  P.decls.sel(Fuel.max(), PsDecls{})

def P.file(src: String) -> List<&2, Decl> & String:
  P.file.fin(P.decls()(Lex.all(src)))

# AST printing
# ============

def Param.show(p: Param) -> String:
  Param{n, m, t} = p
  U32.show(m) ++ n ++ ":" ++ t

# A pattern; with args, the fields of a PCtor (its name unused), each after
# a space. The fields go one at a time: PCtor{n, t} is the rest of them.
def Pat.show.go(p: Pat, +args: Bool) -> String:
  match p:
    case PVar{n}:
      n
    case PCtor{+n, xs}:
      match xs:
        case Nil{}:
          Bool.pick(String, args, "", n ++ "{}")
        case h <> t:
          Bool.pick(String, args, " ", n ++ "{") ++ Pat.show.go(h, False{}) ++
            Pat.show.go(PCtor{n, t}, True{}) ++ Bool.pick(String, args, "", "}")
    case PNat{n}:
      U32.show(n) ++ "n"
    case PSucc{k, q}:
      U32.show(k) ++ "n+" ++ Pat.show.go(q, False{})
    case PNum{n}:
      U32.show(n)
    case PFlt{s}:
      s

def Pat.show(p: Pat) -> String:
  Pat.show.go(p, False{})

def Pats.show(xs: List<&2, Pat>) -> String:
  match xs:
    case Nil{}:
      ""
    case h <> t:
      Pat.show(h) ++ Pat.show.go(PCtor{"", t}, True{})

# The text before a match's first case: after "[" (mode 0), after its
# last scrutinee (1), after a case (2).
def Expr.show.cases(k: Nat) -> String:
  match k:
    case 0n:
      "(match [] "
    case 1n:
      "] "
    case other:
      " "

# e shown, then s. A list field shows its head, then the node rebuilt
# with the rest, in mode 1 (the rest of the first list: " x" each, then
# the list's closing) or 2 (a match's rest of cases).
def Expr.show.go(e: Expr, s: String, k: Nat) -> String:
  match e:
    case EVar{n}:
      n ++ s
    case ENum{n}:
      U32.show(n) ++ s
    case ENat{n}:
      U32.show(n) ++ "n" ++ s
    case EFlt{x}:
      x ++ s
    case EStr{x}:
      "\"" ++ x ++ "\"" ++ s
    case ECall{+f, args}:
      match args:
        case Nil{}:
          match k:
            case 0n:
              "(" ++ Expr.show.go(f, " )" ++ s, 0n)
            case other:
              ")" ++ s
        case a <> t:
          match k:
            case 0n:
              "(" ++ Expr.show.go(f, " " ++ Expr.show.go(a, Expr.show.go(ECall{f, t}, s, 1n), 0n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(ECall{f, t}, s, 1n), 0n)
    case ECtor{+n, args}:
      match args:
        case Nil{}:
          match k:
            case 0n:
              n ++ "{}" ++ s
            case other:
              "}" ++ s
        case a <> t:
          match k:
            case 0n:
              n ++ "{" ++ Expr.show.go(a, Expr.show.go(ECtor{n, t}, s, 1n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(ECtor{n, t}, s, 1n), 0n)
    case ELam{p, b}:
      "(\\" ++ Pat.show(p) ++ " " ++ Expr.show.go(b, ")" ++ s, 0n)
    case ELet{p, v, b}:
      "(let " ++ Pat.show(p) ++ " " ++ Expr.show.go(v, " " ++ Expr.show.go(b, ")" ++ s, 0n), 0n)
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          match k:
            case 0n:
              "(match [" ++ Expr.show.go(a, Expr.show.go(EMatch{t, cases}, s, 1n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(EMatch{t, cases}, s, 1n), 0n)
        case Nil{}:
          match cases:
            case Nil{}:
              match k:
                case 0n:
                  "(match [] )" ++ s
                case 1n:
                  "] )" ++ s
                case other:
                  ")" ++ s
            case c <> t:
              Expr.show.cases(k) ++ Expr.show.go(c, Expr.show.go(EMatch{Nil{}, t}, s, 2n), 0n)
    case ECase{ps, b}:
      "(case " ++ Pats.show(ps) ++ " => " ++ Expr.show.go(b, ")" ++ s, 0n)
    case ESucc{n, x}:
      "(" ++ U32.show(n) ++ "n+ " ++ Expr.show.go(x, ")" ++ s, 0n)
    case EOp{op, a, b}:
      "(" ++ op ++ " " ++ Expr.show.go(a, " " ++ Expr.show.go(b, ")" ++ s, 0n), 0n)
    case EAnn{x, t}:
      "(: " ++ Expr.show.go(x, " " ++ t ++ ")" ++ s, 0n)
    case ETy{+n, targs}:
      match targs:
        case Nil{}:
          match k:
            case 0n:
              "#" ++ n ++ s
            case other:
              ">" ++ s
        case a <> t:
          match k:
            case 0n:
              "#" ++ n ++ "<" ++ Expr.show.go(a, Expr.show.go(ETy{n, t}, s, 1n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(ETy{n, t}, s, 1n), 0n)
    case EErr{m}:
      "(ERR " ++ m ++ ")" ++ s

def Expr.show(e: Expr) -> String:
  Expr.show.go(e, "", 0n)

def Fields.show(fs: List<&2, Field>) -> String:
  match fs:
    case Nil{}:
      ""
    case Field{n, t} <> r:
      n ++ ":" ++ Expr.show(t) ++ " " ++ Fields.show(r)

def Ctor.show(c: Ctor) -> String:
  Ctor{n, fs} = c
  n ++ "{" ++ Fields.show(fs) ++ "}"
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

def Decl.show(d: Decl) -> String:
  match d:
    case DDef{n, ps, b, r}:
      "def " ++ n ++ "(" ++ Params.show(ps) ++ ") = " ++ Expr.show(b)
    case DEff{n, ps, ims}:
      "eff " ++ n ++ "(" ++ Params.show(ps) ++ ")"
    case DLaw{n, ps, r}:
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

# e with a in front of its first list field (a call's or a constructor's
# arguments, a type's, a match's scrutinees), or its cases (Expr.push.case):
# a walk that rebuilds a node from its first element and the node with the
# rest (which is smaller: a self-call may take it).
def Expr.push(a: Expr, e: Expr) -> Expr:
  match e:
    case ECall{f, xs}:
      ECall{f, a <> xs}
    case ECtor{n, xs}:
      ECtor{n, a <> xs}
    case ETy{n, xs}:
      ETy{n, a <> xs}
    case EMatch{xs, cs}:
      EMatch{a <> xs, cs}
    case other:
      other

def Expr.push.case(c: Expr, e: Expr) -> Expr:
  match e:
    case EMatch{xs, cs}:
      EMatch{xs, c <> cs}
    case other:
      other

def R.ops(e: Expr, +ty: String) -> Expr:
  match e:
    case EOp{op, a, b}:
      ECall{EVar{ty ++ "." ++ R.opname(op)}, [R.ops(a, ty), R.ops(b, ty)]}
    case EAnn{x, +t}:
      R.ops(x, Bool.pick(String, String.is_empty(t), ty, t))
    case ECall{f, args}:
      match args:
        case Nil{}:
          ECall{R.ops(f, ty), Nil{}}
        case a <> t:
          Expr.push(R.ops(a, ty), R.ops(ECall{f, t}, ty))
    case ECtor{n, args}:
      match args:
        case Nil{}:
          ECtor{n, Nil{}}
        case a <> t:
          Expr.push(R.ops(a, ty), R.ops(ECtor{n, t}, ty))
    case ELam{p, b}:
      ELam{p, R.ops(b, ty)}
    case ELet{p, v, b}:
      ELet{p, R.ops(v, ty), R.ops(b, ty)}
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(R.ops(a, ty), R.ops(EMatch{t, cases}, ty))
        case Nil{}:
          match cases:
            case Nil{}:
              EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(R.ops(c, ty), R.ops(EMatch{Nil{}, t}, ty))
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

# A PCtor's fields go one at a time: PCtor{n, t} is the rest of them.
def Pat.vars(p: Pat, acc: List<&2, String>) -> List<&2, String>:
  match p:
    case PVar{x}:
      x <> acc
    case PCtor{+n, args}:
      match args:
        case Nil{}:
          acc
        case h <> t:
          Pat.vars(PCtor{n, t}, Pat.vars(h, acc))
    case PSucc{k, q}:
      Pat.vars(q, acc)
    case other:
      acc

def Pats.vars(ps: List<&2, Pat>, acc: List<&2, String>) -> List<&2, String>:
  Pat.vars(PCtor{"", ps}, acc)

# skip: the callee of the call e is done (the call was rebuilt with the
# rest of its arguments).
def FV.go(e: Expr, +bound: List<&2, String>, acc: List<&2, String>, skip: Bool) ->
  List<&2, String>:
  match e:
    case EVar{x}:
      FV.var(x, bound, acc)
    case ECall{+f, args}:
      match args:
        case Nil{}:
          match skip:
            case True{}:
              acc
            case False{}:
              FV.go(f, bound, acc, False{})
        case a <> t:
          match skip:
            case True{}:
              FV.go(ECall{f, t}, bound, FV.go(a, bound, acc, False{}), True{})
            case False{}:
              FV.go(ECall{f, t}, bound, FV.go(a, bound, FV.go(f, bound, acc, False{}), False{}), True{})
    case ECtor{n, args}:
      match args:
        case Nil{}:
          acc
        case a <> t:
          FV.go(ECtor{n, t}, bound, FV.go(a, bound, acc, False{}), False{})
    case ELam{p, b}:
      FV.go(b, Pat.vars(p, bound), acc, False{})
    case ELet{p, v, b}:
      FV.go(b, Pat.vars(p, bound), FV.go(v, bound, acc, False{}), False{})
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          FV.go(EMatch{t, cases}, bound, FV.go(a, bound, acc, False{}), False{})
        case Nil{}:
          match cases:
            case Nil{}:
              acc
            case c <> t:
              FV.go(EMatch{Nil{}, t}, bound, FV.go(c, bound, acc, False{}), False{})
    case ECase{ps, b}:
      FV.go(b, Pats.vars(ps, bound), acc, False{})
    case ESucc{k, x}:
      FV.go(x, bound, acc, False{})
    case EOp{op, a, b}:
      FV.go(b, bound, FV.go(a, bound, acc, False{}), False{})
    case EAnn{x, t}:
      FV.go(x, bound, acc, False{})
    case other:
      acc

def FV.expr(e: Expr, +bound: List<&2, String>, acc: List<&2, String>) -> List<&2, String>:
  FV.go(e, bound, acc, False{})

# Global tables
# =============

# kind: 0 node, 1 nullary, 2 newtype, 3 Nat zero, 4 Nat succ
type CInfo is Data:
  CInfo{tag: U32, arity: U32, kind: U32, single: Bool}

# kind: 0 def, 1 effect, 2 native, 3 dead (types, laws, type-level), 4 unknown
# mask: one flag per parameter, True when kept at runtime.
type DInfo is Data:
  DInfo{kind: U32, mask: List<&2, Bool>}

# A destination-passing group (see Dps below): its name and the number of
# value parameters its members' D_ functions share.
type DGrp is Data:
  DGrp{id: String, n: U32}

type G is Data:
  G{ctors: Map<&2, CInfo>, defs: Map<&2, DInfo>, bodies: Map<&2, Decl>, dps: Map<&2, DGrp>}

def G.ctor.if(+m: Map<&2, CInfo>, +name: String, has: Bool) -> Maybe<&2, CInfo>:
  match has:
    case True{}:
      Some{Pair.snd(Map<&2, CInfo>, CInfo, Map.get(CInfo, CInfo{0, 0, 4, False{}}, m, name))}
    case False{}:
      None{}

def G.ctor(+g: G, +name: String) -> Maybe<&2, CInfo>:
  G{+ctors, defs, bodies, dps} = g
  G.ctor.if(ctors, name, Pair.snd(Map<&2, CInfo>, Bool, Map.has(&2, CInfo, ctors, name)))

def G.get(-V: Data, +d: V, +m: Map<&2, V>, +key: String) -> V:
  Pair.snd(Map<&2, V>, V, Map.get(V, d, m, key))

def G.def(+g: G, +name: String) -> DInfo:
  G{ctors, defs, bodies, dps} = g
  G.get(DInfo, DInfo{4, Nil{}}, defs, name)

def G.body(+g: G, +name: String) -> Decl:
  G{ctors, defs, bodies, dps} = g
  G.get(Decl, DImport{"", ""}, bodies, name)

# The destination-passing group of a def (id "" when it has none).
def G.dps(+g: G, +name: String) -> DGrp:
  G{ctors, defs, bodies, dps} = g
  G.get(DGrp, DGrp{"", 0}, dps, name)

def Natives() -> List<&2, String>:
  ["U32.inc", "U32.add", "U32.sub", "U32.mul", "U32.div", "U32.mod", "U32.not",
   "U32.and", "U32.or", "U32.xor", "U32.shl", "U32.shr", "U32.shln", "U32.shrn",
   "U32.cmp", "U32.is_eq", "U32.is_ne", "U32.is_lt", "U32.is_le", "U32.is_gt",
   "U32.is_ge", "U32.is_zero", "U32.is_even", "U32.to_nat", "U32.from_nat",
   "U32.min", "U32.max", "U32.pow", "U32.log2", "U32.to_f32",
   "Nat.double", "Nat.add", "Nat.sub", "Nat.mul", "Nat.divmod", "Nat.div",
   "Nat.mod", "Nat.cmp", "Nat.is_eq", "Nat.is_ne", "Nat.is_lt", "Nat.is_le",
   "Nat.is_gt", "Nat.is_ge", "Nat.min", "Nat.max", "Nat.pow", "Nat.show",
   "Chk.memo.new", "Chk.memo.has", "Chk.memo.get", "Chk.memo.set",
   "F32.add", "F32.sub", "F32.mul", "F32.div", "F32.mod", "F32.pow", "F32.atan2",
   "F32.is_eq", "F32.is_ne", "F32.is_lt", "F32.is_le", "F32.is_gt", "F32.is_ge",
   "F32.neg", "F32.abs", "F32.sqrt", "F32.exp", "F32.log", "F32.log2",
   "F32.log10", "F32.sin", "F32.cos", "F32.tan", "F32.asin", "F32.acos",
   "F32.atan", "F32.sinh", "F32.cosh", "F32.tanh", "F32.floor", "F32.ceil",
   "F32.trunc", "F32.bits", "F32.to_u32", "F32.show", "F32.read", "Map.bit",
   "Array.size", "Array.get", "Array.swap", "Array.set", "Array.new", "Array.clone",
   "Array.atomic.add", "Array.atomic.min", "Array.atomic.max", "Array.atomic.and",
   "Array.atomic.or", "Array.atomic.xor", "Array.atomic.exch", "Array.atomic.cas",
   "Array.atomic.fadd"]

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

# 0 a node, 1 nullary, 2 a newtype, 3 Zero, 4 Succ, 5 ALeaf, 6 ANode (an
# Array is a flat block: see "Arrays" in bendrt.h).
def G.ctor_kind(+tname: String, +name: String, +n: U32, +ar: U32) -> U32:
  Bool.pick(U32, Str.eq(tname, "Nat"), Bool.pick(U32, Str.eq(name, "Zero"), 3, 4),
    Bool.pick(U32, Str.eq(tname, "Array"), Bool.pick(U32, Str.eq(name, "ALeaf"), 5, 6),
      Bool.pick(U32, Bool.and(U32.is_eq(n, 1), U32.is_eq(ar, 1)), 2,
        Bool.pick(U32, U32.is_zero(ar), 1, 0))))

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

def G.laws(ds: List<&2, Decl>, m: Map<&2, Decl>) -> Map<&2, Decl>:
  match ds:
    case Nil{}:
      m
    case DLaw{+name, ps, r} <> t:
      G.laws(t, Map.set(&2, Decl, m, name, DLaw{name, ps, r}))
    case d <> t:
      G.laws(t, m)

# A bare parameter a law's for lines do not cover (law f: A -> B, then
# def f(x)) is a plain one.
def G.bare(ps: List<&2, Param>) -> List<&2, Param>:
  match ps:
    case Nil{}:
      Nil{}
    case Param{n, +m, t} <> r:
      Param{n, Bool.pick(U32, U32.is_eq(m, 4), 0, m), t} <> G.bare(r)

def G.params.go(lps: List<&2, Param>, ps: List<&2, Param>) -> List<&2, Param>:
  match lps:
    case Nil{}:
      G.bare(ps)
    case h <> t:
      h <> t

def G.law.ps(d: Decl) -> List<&2, Param>:
  match d:
    case DLaw{n, ps, r}:
      ps
    case other:
      Nil{}

def G.law.ret(d: Decl) -> Expr:
  match d:
    case DLaw{n, ps, r}:
      r
    case other:
      ETy{"", Nil{}}

# Parameter modes of a def come from its law when it fills one.
def G.params(+laws: Map<&2, Decl>, +name: String, ps: List<&2, Param>) ->
  List<&2, Param>:
  G.params.go(G.law.ps(G.get(Decl, DImport{"", ""}, laws, name)), ps)

# So does its return type, when the def does not write one.
def G.ret(+laws: Map<&2, Decl>, +name: String, +ret: Expr) -> Expr:
  Bool.pick(Expr, P.no_ty(ret), G.law.ret(G.get(Decl, DImport{"", ""}, laws, name)), ret)

def G.add.type(+name: String, ps: List<&2, String>, +cs: List<&2, Ctor>, g: G) -> G:
  G{ctors, defs, bodies, dps} = g
  +n = U32.from_nat(List.length(&2, Ctor, cs))
  G{G.ctors(name, cs, 0, n, ctors), Map.set(&2, DInfo, defs, name,
    DInfo{3, Nil{}}), Map.set(&2, Decl, bodies, "%" ++ name, DType{name, ps, cs}), dps}

def G.add.law(+name: String, ps: List<&2, Param>, g: G) -> G:
  G{ctors, defs, bodies, dps} = g
  G{ctors, Map.set(&2, DInfo, defs, name,
    DInfo{Bool.pick(U32, G.is_native(name), 2, 3), G.mask(ps)}), bodies, dps}

def G.add.def(
  +name: String, +ps: List<&2, Param>, body: Expr, ret: Expr,
  +laws: Map<&2, Decl>, g: G
) -> G:
  G{ctors, defs, bodies, dps} = g
  G{ctors, Map.set(&2, DInfo, defs, name,
    DInfo{Bool.pick(U32, G.is_native(name), 2, 0),
      G.mask(G.params(laws, name, ps))}),
    Map.set(&2, Decl, bodies, name, DDef{name, ps, body, G.ret(laws, name, ret)}), dps}

def G.add.eff(+name: String, +ps: List<&2, Param>, ims: List<&2, String>,
  +laws: Map<&2, Decl>, g: G) -> G:
  G{ctors, defs, bodies, dps} = g
  G{ctors, Map.set(&2, DInfo, defs, name, DInfo{1, G.mask(G.params(laws, name, ps))}),
    Map.set(&2, Decl, Map.set(&2, Decl, bodies, name, DEff{name, G.params(laws, name, ps), ims}),
      "^" ++ name, DLaw{name, Nil{}, G.law.ret(G.get(Decl, DImport{"", ""}, laws, name))}), dps}

def G.add(d: Decl, +laws: Map<&2, Decl>, g: G) -> G:
  match d:
    case DType{name, ps, cs}:
      G.add.type(name, ps, cs, g)
    case DLaw{name, ps, r}:
      G.add.law(name, ps, g)
    case DDef{name, ps, body, ret}:
      G.add.def(name, ps, body, ret, laws, g)
    case DEff{name, ps, ims}:
      G.add.eff(name, ps, ims, laws, g)
    case DImport{p, a}:
      g

def G.build(
  ds: List<&2, Decl>, +laws: Map<&2, Decl>, g: G
) -> G:
  match ds:
    case Nil{}:
      g
    case d <> t:
      G.build(t, laws, G.add(d, laws, g))

def G.new(+ds: List<&2, Decl>) -> G:
  G.build(ds, G.laws(ds, MTip{}), G{MTip{}, MTip{}, MTip{}, MTip{}})

def DInfo.mask(i: DInfo) -> List<&2, Bool>:
  DInfo{kind, mask} = i
  mask

def G.with_dps(g: G, m: Map<&2, DGrp>) -> G:
  G{ctors, defs, bodies, dps} = g
  G{ctors, defs, bodies, m}

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

# Where a statement's value goes: returned, assigned to a C variable, or
# stored through dst (in a D_ function of destination-passing group id).
type Tgt is Data:
  TRet{}
  TSet{v: String}
  TDst{id: String, n: U32}

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
    case TDst{id, n}:
      Doc.list([DStr{"*dst = "}, d, DStr{";\nreturn 0;\n"}])

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

def Env.find(env: Env(), +x: String) -> Maybe<&2, String>:
  match env:
    case Nil{}:
      None{}
    case Bind{+n, c} <> t:
      Bool.pick(Unit -> Maybe<&2, String>, String.eq(n, x), u => Some{c}, u => Env.find(t, x))(Unit{})

def Env.has(+env: Env(), +x: String) -> Bool:
  Maybe.is_some(&2, String, Env.find(env, x))

def Gen.is_field(path: String) -> Bool:
  match path:
    case SCon{Chr{c}, t}:
      U32.is_eq(c, 70)
    case SNil{}:
      False{}

# A node the pattern opens, for bend_take: a binding named %top (a
# scrutinee) or %sub (a field), then its size in words.
def Gen.pat.node(opens: Bool, +ar: U32, +path: String, r: PatR) -> PatR:
  match opens:
    case True{}:
      PatR{conds, binds} = r
      PatR{conds, Bind{Bool.pick(String, Gen.is_field(path), "%sub", "%top") ++ U32.show(U32.inc(ar)),
        path} <> binds}
    case False{}:
      r

# An ANode's halves, copies (arr_half); "%arr" has the case load them once.
def Gen.pat.arr(+path: String, r: PatR) -> PatR:
  PatR{conds, binds} = r
  PatR{conds, Bind{"%arr", path} <> binds}

# A machine word's structural view, under U32{..} or F32{..}: WCon{head,
# tail} is its low bit and the rest shifted down, WNil what is left (the
# word is its raw bits; a Word(n) elsewhere stays a list of Bools).
def Pat.wordk(p: Pat) -> Nat:
  match p:
    case PCtor{+name, args}:
      P.which(name, ["WCon", "WNil"])
    case other:
      2n

# A pattern at a stage st, each one's steps after the stage above it (a
# pattern that stays passes a lower stage):
#   4: under U32{..} or F32{..}, by k (Pat.wordk: WCon, WNil or other);
#   3: the pattern;
#   2: a constructor with info, by k (0 or 1: U32 or F32, 2: other);
#   1: a constructor with info, by k (its kind);
#   0: a constructor's fields, the i-th first (99: the value itself, for
#      newtypes).
def Gen.pat.go(
  p: Pat, st: Nat, +g: G, +path: String, +i: U32, info: Maybe<&2, CInfo>, k: Nat, r: PatR
) -> PatR:
  match p:
    case PCtor{+name, args}:
      match args:
        case Nil{}:
          match st:
            case 0n:
              r
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      Gen.pat.go(PCtor{name, Nil{}}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(False{}, ar, path,
                          Gen.pat.tag(single, "TAG(" ++ path ++ ") == " ++ U32.show(tag), r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(PCtor{name, Nil{}}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(PCtor{name, Nil{}}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.go(PCtor{name, Nil{}}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r))
                    case 6n+q:
                      Gen.pat.cond("arr_cls(" ++ path ++ ") != 0", r)
            case 2n:
              match info:
                case None{}:
                  Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      Gen.pat.go(PCtor{name, Nil{}}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              Gen.pat.go(PCtor{name, Nil{}}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(PCtor{name, Nil{}}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +a <> Nil{}:
          match st:
            case 0n:
              Gen.pat.go(PCtor{name, Nil{}}, 0n, g, path, U32.inc(i), None{}, 0n,
                Gen.pat.go(a, 3n, g, Bool.pick(String, U32.is_eq(i, 99), path,
                  "FLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      Gen.pat.go(PCtor{name, [a]}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(True{}, ar, path,
                          Gen.pat.tag(single, "TAG(" ++ path ++ ") == " ++ U32.show(tag), r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(PCtor{name, [a]}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(PCtor{name, [a]}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.go(PCtor{name, [a]}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r))
                    case 6n+q:
                      Gen.pat.cond("arr_cls(" ++ path ++ ") != 0", r)
            case 2n:
              match info:
                case None{}:
                  Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      Gen.pat.go(PCtor{name, [a]}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      Gen.pat.go(a, 4n, g, path, 0, None{}, Pat.wordk(a), r)
            case 3n:
              Gen.pat.go(PCtor{name, [a]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(PCtor{name, [a]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +a <> +b <> Nil{}:
          match st:
            case 0n:
              Gen.pat.go(PCtor{name, [b]}, 0n, g, path, U32.inc(i), None{}, 0n,
                Gen.pat.go(a, 3n, g, Bool.pick(String, U32.is_eq(i, 99), path,
                  "FLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      Gen.pat.go(PCtor{name, [a, b]}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(True{}, ar, path,
                          Gen.pat.tag(single, "TAG(" ++ path ++ ") == " ++ U32.show(tag), r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(PCtor{name, [a, b]}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(PCtor{name, [a, b]}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.go(PCtor{name, [a, b]}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r))
                    case 6n+q:
                      Gen.pat.arr(path, Gen.pat.go(b, 3n, g, "arr_half(" ++ path ++ ", 1)", 0, None{}, 0n,
                        Gen.pat.go(a, 3n, g, "arr_half(" ++ path ++ ", 0)", 0, None{}, 0n,
                          Gen.pat.cond("arr_cls(" ++ path ++ ") != 0", r))))
            case 2n:
              match info:
                case None{}:
                  Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      Gen.pat.go(PCtor{name, [a, b]}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              Gen.pat.go(PCtor{name, [a, b]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  Gen.pat.go(b, 4n, g, "((V)(U32)(" ++ path ++ ") >> 1)", 0, None{}, Pat.wordk(b),
                    Gen.pat.go(a, 3n, g, "BOOL((" ++ path ++ ") & 1)", 0, None{}, 0n, r))
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(PCtor{name, [a, b]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +h <> +t:
          match st:
            case 0n:
              Gen.pat.go(PCtor{name, t}, 0n, g, path, U32.inc(i), None{}, 0n,
                Gen.pat.go(h, 3n, g, Bool.pick(String, U32.is_eq(i, 99), path,
                  "FLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      Gen.pat.go(PCtor{name, h <> t}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(True{}, ar, path,
                          Gen.pat.tag(single, "TAG(" ++ path ++ ") == " ++ U32.show(tag), r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(PCtor{name, h <> t}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(PCtor{name, h <> t}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.go(PCtor{name, h <> t}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r))
                    case 6n+q:
                      Gen.pat.cond("arr_cls(" ++ path ++ ") != 0", r)
            case 2n:
              match info:
                case None{}:
                  Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      Gen.pat.go(PCtor{name, h <> t}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              Gen.pat.go(PCtor{name, h <> t}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(PCtor{name, h <> t}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
    case PVar{+x}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          Gen.pat.var(x, path, r)
        case 4n:
          match k:
            case 2n+z:
              Gen.pat.var(x, path, r)
            case other:
              r
        case other:
          r
    case PNat{+n}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
        case 4n:
          match k:
            case 2n+z:
              Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
            case other:
              r
        case other:
          r
    case PSucc{+j, q}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          Gen.pat.go(q, 3n, g, "nat_subk(" ++ path ++ ", " ++ U32.show(j) ++ ")", 0, None{}, 0n,
            Gen.pat.cond("nat_ge(" ++ path ++ ", " ++ U32.show(j) ++ ")", r))
        case 4n:
          match k:
            case 2n+z:
              Gen.pat.go(q, 3n, g, "nat_subk(" ++ path ++ ", " ++ U32.show(j) ++ ")", 0, None{}, 0n,
                Gen.pat.cond("nat_ge(" ++ path ++ ", " ++ U32.show(j) ++ ")", r))
            case other:
              r
        case other:
          r
    case PNum{+n}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
        case 4n:
          match k:
            case 2n+z:
              Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
            case other:
              r
        case other:
          r
    case PFlt{+f}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          Gen.pat.cond("(" ++ path ++ ") == VF(" ++ f ++ "f)", r)
        case 4n:
          match k:
            case 2n+z:
              Gen.pat.cond("(" ++ path ++ ") == VF(" ++ f ++ "f)", r)
            case other:
              r
        case other:
          r

def Gen.pat(+g: G, p: Pat, +path: String, r: PatR) -> PatR:
  Gen.pat.go(p, 3n, g, path, 0, None{}, 0n, r)

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
    case 4n:
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

# A D_ node, with a hole: CH2 and the like (see bendrt.h).
def Gen.ctor.hnode(+tag: U32, +ds: List<&2, Doc>) -> Doc:
  +n = Gen.len(ds)
  Bool.pick(Doc, U32.is_le(n, 4),
    Doc.list([DStr{"CH" ++ U32.show(n) ++ "(" ++ U32.show(tag) ++ ", "}, Gen.commas(ds),
      DStr{")"}]),
    Doc.list([DStr{"CHN(" ++ U32.show(tag) ++ ", " ++ U32.show(n) ++ ", "},
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
    case 4n:
      Doc.list([DStr{"nat_addk("}, Doc.list(ds), DStr{", 1)"}])
    case 5n:
      Doc.list([DStr{"arr_leaf("}, Doc.list(ds), DStr{")"}])
    case 6n+p:
      Doc.list([DStr{"arr_node("}, Gen.commas(ds), DStr{")"}])

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
    case TDst{id, n}:
      True{}

def Gen.is_tail(+env: Env(), +self: Self, +tgt: Tgt, +name: String, +args: List<&2, Expr>) ->
  Bool:
  Self{+sn, +mask, cps} = self
  Bool.and(Bool.and(Gen.is_ret(tgt), Str.eq(sn, name)), Bool.and(
    Bool.not(Env.has(env, name)),
    Nat.is_eq(List.length(&2, Bool, mask), List.length(&2, Expr, args))))

# F32.add(F32.mul(x, k), b), either way round, with k a literal: 1n when k is
# the mul's second argument, 2n when its first, else 0n.
def Gen.fadd.k(e: Expr) -> Nat:
  match e:
    case ECall{EVar{f}, x <> EFlt{s} <> Nil{}}:
      Bool.pick(Nat, Str.eq(f, "F32.mul"), 1n, 0n)
    case ECall{EVar{f}, EFlt{s} <> x <> Nil{}}:
      Bool.pick(Nat, Str.eq(f, "F32.mul"), 2n, 0n)
    case other:
      0n

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

def Expr.wordk(e: Expr) -> Nat:
  match e:
    case ECtor{+name, args}:
      P.which(name, ["WCon", "WNil"])
    case other:
      2n

def DGrp.id(d: DGrp) -> String:
  DGrp{id, n} = d
  id

# Whether a tail call jumps to a D_ function: the target is a D_ function's
# (tgt) and name a def of its group, applied to all its parameters.
def Gen.dst.call(+g: G, +env: Env(), +tgt: Tgt, +name: String, +args: List<&2, Expr>) -> Bool:
  match tgt:
    case TDst{+id, n}:
      Bool.and(Str.eq(id, DGrp.id(G.dps(g, name))), Bool.and(Bool.not(Env.has(env, name)),
        Nat.is_eq(List.length(&2, Bool, DInfo.mask(G.def(g, name))), List.length(&2, Expr, args))))
    case other:
      False{}

def Tgt.n(t: Tgt) -> Nat:
  match t:
    case TDst{id, n}:
      U32.to_nat(n)
    case other:
      0n

# ", a, b, 0, 0": a D_ call's arguments after dst, padded with zeros to the
# group's parameter count.
def Gen.dst.args(n: Nat, ds: List<&2, Doc>) -> Doc:
  match n ds:
    case 0n dl:
      DNil{}
    case 1n+m Nil{}:
      Doc.list([DStr{", 0"}, Gen.dst.args(m, Nil{})])
    case 1n+m d <> t:
      Doc.list([DStr{", "}, d, Gen.dst.args(m, t)])

def Gen.dst.node(info: Maybe<&2, CInfo>) -> Bool:
  match info:
    case Some{CInfo{tag, ar, kind, single}}:
      U32.is_zero(kind)
    case None{}:
      False{}

def Gen.dst.hole.at(+g: G, +env: Env(), +tgt: Tgt, a: Expr, +i: U32, acc: U32) -> U32:
  match a:
    case ECall{EVar{+h}, +hargs}:
      Bool.pick(U32, Gen.dst.call(g, env, tgt, h, hargs), U32.inc(i), acc)
    case other:
      acc

# In a D_ function, the field of a constructor node left as a hole: the
# last one that is a call to the group (1-based; 0 when there is none).
def Gen.dst.hole(+g: G, +env: Env(), +tgt: Tgt, node: Bool, as: List<&2, Expr>, +i: U32, acc: U32) ->
  U32:
  match node as:
    case True{} a <> t:
      Gen.dst.hole(g, env, tgt, True{}, t, U32.inc(i), Gen.dst.hole.at(g, env, tgt, a, i, acc))
    case n l:
      acc

def Gen.dst.nth(k: Nat, as: List<&2, Expr>) -> Expr:
  match k as:
    case 0n a <> t:
      a
    case 1n+m a <> t:
      Gen.dst.nth(m, t)
    case n Nil{}:
      EErr{"hole"}

def Gen.stmt.ctor.tag.go(info: Maybe<&2, CInfo>) -> U32:
  match info:
    case Some{CInfo{tag, ar, kind, single}}:
      tag
    case None{}:
      0

def Gen.stmt.ctor.tag(+g: G, +name: String) -> U32:
  Gen.stmt.ctor.tag.go(G.ctor(g, name))

def Gen.share.if(ok: Bool, c: String) -> Doc:
  match ok:
    case True{}:
      DStr{"bend_share(" ++ c ++ ");\n"}
    case False{}:
      DNil{}

# Scalars (numbers, characters, booleans) are never shared: a variable known
# to hold one is bound to its C name in parentheses, "(a1)", which
# Gen.shares skips, as it skips a Nat pattern's nat_subk(..).
def Gen.scalar.ty(+t: String) -> Bool:
  Str.has(["U32", "F32", "Nat", "Bool", "Char"], t)

def Gen.scalar.wrap(scalar: Bool, +c: String) -> String:
  Bool.pick(String, scalar, "(" ++ c ++ ")", c)

def Gen.scalar.c(c: String) -> Bool:
  match c:
    case SCon{Chr{40}, t}:
      True{}
    case SCon{Chr{110}, SCon{Chr{97}, SCon{Chr{116}, SCon{Chr{95}, t}}}}:
      True{}
    case other:
      False{}

def Gen.scalar.find(m: Maybe<&2, String>) -> Bool:
  match m:
    case Some{c}:
      Gen.scalar.c(c)
    case None{}:
      False{}

# Whether a let's value is a variable holding a scalar.
def Gen.scalar.var(+env: Env(), v: Expr) -> Bool:
  match v:
    case EVar{+y}:
      Gen.scalar.find(Env.find(env, y))
    case other:
      False{}

#
# A value bound to a variable used twice (on some path) is marked shared
# where it is bound (bend_share). A match or destructuring let that opens a
# node reads its fields into locals and hands the node to bend_take, which
# frees it unless it is shared, in which case the fields are shared too. See
# "Freeing on match" in bendrt.h.
# The uses of x on the path through e that uses it most. A list field
# counts as its head and the node rebuilt with the rest.
def Use.n(+x: String, e: Expr) -> U32:
  match e:
    case EVar{+n}:
      Bool.pick(U32, Str.eq(n, x), 1, 0)
    case ECall{f, args}:
      match args:
        case Nil{}:
          Use.n(x, f)
        case a <> t:
          (Use.n(x, a) + Use.n(x, ECall{f, t}) : U32)
    case ECtor{n, args}:
      match args:
        case Nil{}:
          0
        case a <> t:
          (Use.n(x, a) + Use.n(x, ECtor{n, t}) : U32)
    case ELam{p, b}:
      Use.n(x, b)
    case ELet{p, v, b}:
      (Use.n(x, v) + Use.n(x, b) : U32)
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          (Use.n(x, a) + Use.n(x, EMatch{t, cases}) : U32)
        case Nil{}:
          match cases:
            case Nil{}:
              0
            case c <> t:
              U32.max(Use.n(x, c), Use.n(x, EMatch{Nil{}, t}))
    case ECase{ps, b}:
      Use.n(x, b)
    case ESucc{k, y}:
      Use.n(x, y)
    case EOp{op, a, b}:
      (Use.n(x, a) + Use.n(x, b) : U32)
    case EAnn{y, t}:
      Use.n(x, y)
    case other:
      0

# bend_share for each binding whose variable body uses twice.
def Gen.shares(binds: Env(), +body: Expr) -> Doc:
  match binds:
    case Nil{}:
      DNil{}
    case Bind{+x, +c} <> t:
      Doc.list([Gen.share.if(Bool.and(Bool.not(Bool.or(Bool.or(Str.eq(x, "_"), Str.eq(c, "0")), Gen.scalar.c(c))),
        U32.is_le(2, Use.n(x, body))), c), Gen.shares(t, body)])

# Whether matches free the nodes they open (BEND_NO_FREE turns it off: no
# sharing, no bend_take, the code of a traced heap only).
def Gen.free(+g: G) -> Bool:
  Str.eq(DGrp.id(G.dps(g, "%free")), "1")

def Gen.shares.if(free: Bool, binds: Env(), +body: Expr) -> Doc:
  match free:
    case True{}:
      Gen.shares(binds, body)
    case False{}:
      DNil{}

def Gen.shares.g(+g: G, binds: Env(), +body: Expr) -> Doc:
  Gen.shares.if(Gen.free(g), binds, body)

def PatR.binds(r: PatR) -> Env():
  PatR{conds, binds} = r
  binds

def Gen.takes.if(keep: Bool, c: String, rest: List<&2, String>) -> List<&2, String>:
  match keep:
    case True{}:
      c <> rest
    case False{}:
      rest

# "%top3" is "%top" and "3".
def Gen.take.kind(x: String) -> String:
  match x:
    case SCon{a, SCon{b, SCon{c, SCon{d, t}}}}:
      SCon{a, SCon{b, SCon{c, SCon{d, SNil{}}}}}
    case other:
      ""

def Gen.take.words(x: String) -> String:
  match x:
    case SCon{a, SCon{b, SCon{c, SCon{d, t}}}}:
      t
    case other:
      ""

# bend_take calls for the nodes a pattern opens (kind: "%top" or "%sub").
def Gen.takes(binds: Env(), +kind: String) -> List<&2, String>:
  match binds:
    case Nil{}:
      Nil{}
    case Bind{+x, +c} <> t:
      Gen.takes.if(Str.eq(Gen.take.kind(x), kind), "bend_take(" ++ c ++ ", " ++ Gen.take.words(x) ++ ")",
        Gen.takes(t, kind))

def Gen.is_take(x: String) -> Bool:
  match x:
    case SCon{Chr{c}, t}:
      U32.is_eq(c, 37)
    case SNil{}:
      False{}

def Gen.vars.if(skip: Bool, b: Bind, rest: Env()) -> Env():
  match skip:
    case True{}:
      rest
    case False{}:
      b <> rest

# Whether a pattern opens a node.
def Gen.opens(binds: Env()) -> Bool:
  match binds:
    case Nil{}:
      False{}
    case Bind{x, c} <> t:
      Bool.or(Gen.is_take(x), Gen.opens(t))

# Whether a pattern splits an Array (its halves are copies, made once).
def Gen.halves(binds: Env()) -> Bool:
  match binds:
    case Nil{}:
      False{}
    case Bind{x, c} <> t:
      Bool.or(Str.eq(x, "%arr"), Gen.halves(t))

# The bindings of variables (not of opened nodes).
def Gen.vars(binds: Env()) -> Env():
  match binds:
    case Nil{}:
      Nil{}
    case Bind{+x, c} <> t:
      Gen.vars.if(Gen.is_take(x), Bind{x, c}, Gen.vars(t))

def Gen.mat.put(x: String, +m: String, path: String, r: Env() & Doc) -> Env() & Doc:
  (bs, d) = r
  (Bind{x, m} <> bs, Doc.list([DStr{"V " ++ m ++ " = " ++ path ++ ";\n"}, d]))

# Reads each binding's path into a fresh local.
def Gen.mat(binds: Env()) -> Gen(Env() & Doc):
  match binds:
    case Nil{}:
      Gen.pure(Env() & Doc, (Nil{}, DNil{}))
    case Bind{x, path} <> t:
      do Gen<Env() & Doc>:
        +k : U32 <- Gen.fresh()
        r : Env() & Doc <- Gen.mat(t)
        return Gen.mat.put(x, "m" ++ U32.show(k), path, r)

def Gen.takes.stmts(cs: List<&2, String>) -> String:
  match cs:
    case Nil{}:
      ""
    case c <> t:
      c ++ ";\n" ++ Gen.takes.stmts(t)

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

# 1: in S_name (in order); 3: elsewhere (forks, and, in a def with a
# sequential clone, only above the frontier).
def Gen.par.mode(m: Maybe<&2, String>, +sn: String) -> Nat:
  match m:
    case Some{+v}:
      Bool.pick(Nat, Str.eq(v, sn), 1n, 3n)
    case None{}:
      3n

def Gen.par.decls(n: Nat, +k: U32, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "V " ++ Gen.par.name(k, i) ++ "; " ++ Gen.par.decls(m, k, U32.inc(i))

def Gen.par.copy(n: Nat, +k: U32, +j: U32, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      Gen.par.name(k, i) ++ " = " ++ Gen.par.name(j, i) ++ "; " ++ Gen.par.copy(m, k, j, U32.inc(i))

#
# The functions a !-call can reach compile into one flat state machine (see
# rt/gpu.h): a function is an entry block, a call ends a block (the callee
# returns to a fresh one), every local lives in a frame slot, S(k), and a
# parallel let forks thunks and joins. The text compiles as MSL (the Metal
# kernel) and as C (the CPU simulator).
type KSt is Data:
  KSt{n: U32, sl: U32, curl: U32, cur: Doc, out: Doc, fns: List<&2, Bind>, todo: List<&2, String>,
    frames: List<&2, Bind>, errs: List<&2, String>, flat: Doc, memo: List<&2, Bind>}

def Gen.isseq.fst(r: Bool & KSt) -> Bool:
  (b, st) = r
  b

def KM(-A: Type) -> Type:
  KSt -> A & KSt

def KM.go(-A: Type, -B: Type, r: A & KSt, f: A -> KM(B)) -> B & KSt:
  (a, st) = r
  f(a, st)

def KM.bind(-A: Type, -B: Type, m: KM(A), f: A -> KM(B)) -> KM(B):
  st => KM.go(A, B, m(st), f)

def KM.pure(-A: Type, x: A) -> KM(A):
  st => (x, st)

#
# A def is flat when its body only matches, binds, builds constructors,
# calls natives and other flat defs, and calls itself in tail position. It
# becomes a plain function, KX_name, with its locals in registers and a loop
# for its tail calls: no frames, no trips through the kernel's switch.
def K.memo.get.go(+k: String, st: KSt) -> Maybe<&2, String> & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, +memo} = st
  (Env.find(memo, k), KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo})

def K.memo.get(+k: String) -> KM(Maybe<&2, String>):
  st => K.memo.get.go(k, st)

def K.memo.put.go(k: String, v: String, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (Unit{}, KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, Bind{k, v} <> memo})

def K.memo.put(k: String, v: String) -> KM(Unit):
  st => K.memo.put.go(k, v, st)

def K.kept(mask: List<&2, Bool>) -> U32:
  match mask:
    case Nil{}:
      0
    case True{} <> t:
      U32.inc(K.kept(t))
    case False{} <> t:
      K.kept(t)

type KSelf is Data:
  KSelf{name: String, entry: U32, mask: List<&2, Bool>}

def K.params(ps: List<&2, Param>, mask: List<&2, Bool>) -> List<&2, String>:
  match ps mask:
    case Param{x, m, t} <> pt True{} <> mt:
      x <> K.params(pt, mt)
    case Param{x, m, t} <> pt False{} <> mt:
      x <> K.params(pt, mt)
    case pl ml:
      Nil{}

# Both, analysing the second only when the first holds.
def K.fl.and(a: Bool, b: KM(Bool)) -> KM(Bool):
  match a:
    case True{}:
      b
    case False{}:
      KM.pure(Bool, False{})

def KM.if(-A: Type, c: Bool, t: KM(A), e: KM(A)) -> KM(A):
  match c:
    case True{}:
      t
    case False{}:
      e

def K.error.go(msg: String, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (Unit{}, KSt{n, sl, curl, cur, out, fns, todo, frames, msg <> errs, flat, memo})

def K.error(msg: String) -> KM(Unit):
  st => K.error.go(msg, st)

# A def that merges a cycle, out of fuel: an error, and x.
def K.out(-A: Type, x: A) -> KM(A):
  do KM<A>:
    K.error("out of fuel")
    return x

def KSelf.name(s: KSelf) -> String:
  KSelf{n, e, m} = s
  n

def KSelf.mask(s: KSelf) -> List<&2, Bool>:
  KSelf{n, e, m} = s
  m

# Whether an analysis is the seq one (KSelf.entry 1): see K.isseq.
def KSelf.seq(s: KSelf) -> Bool:
  KSelf{n, e, m} = s
  U32.is_eq(e, 1)

def K.pat.is_par(p: Pat) -> Bool:
  match p:
    case PCtor{+n, ps}:
      Str.eq(n, "%par")
    case other:
      False{}

# Whether v is a call of the def itself.
def K.fl.direct(+self: KSelf, +bound: List<&2, String>, v: Expr) -> Bool:
  match v:
    case ECall{EVar{+f}, args}:
      Bool.and(Str.eq(f, KSelf.name(self)), Bool.not(Str.has(bound, f)))
    case other:
      False{}

# The flatness analysis, one def (fuel: its calls, which reach other defs):
# FlSel picks the step.
type FlSel is Type:
  FLFlExprs{g: G, self: KSelf, bound: List<&2, String>, es: List<&2, Expr>}
  FLFlCases{g: G, self: KSelf, bound: List<&2, String>, cs: List<&2, Expr>, tail: Bool}
  FLFlGlobalKind{g: G, self: KSelf, name: String, kind: Nat, mask: List<&2, Bool>}
  FLFlGlobal{g: G, self: KSelf, name: String, info: DInfo}
  FLFlVar{g: G, self: KSelf, bound: List<&2, String>, x: String}
  FLFlCallDef{g: G, self: KSelf, bound: List<&2, String>, f: String, kept: List<&2, Expr>, tail: Bool, me: Bool}
  FLFlCallKind{kind: Nat, extra: List<&2, Expr>, full: Bool, g: G, self: KSelf, bound: List<&2, String>, f: String,
      kept: List<&2, Expr>, tail: Bool}
  FLFlCallSplit{g: G, self: KSelf, bound: List<&2, String>, f: String, kind: Nat, s: Split, tail: Bool}
  FLFlCallGlobal{g: G, self: KSelf, bound: List<&2, String>, f: String, args: List<&2, Expr>, tail: Bool, info: DInfo}
  FLFlCall{g: G, self: KSelf, bound: List<&2, String>, f: String, args: List<&2, Expr>, tail: Bool}
  FLFlParVals{g: G, self: KSelf, bound: List<&2, String>, vs: List<&2, Expr>}
  FLFlLetPar{g: G, self: KSelf, bound: List<&2, String>, p: Pat, v: Expr, b: Expr}
  FLFlLetGo{par: Bool, g: G, self: KSelf, bound: List<&2, String>, p: Pat, v: Expr, b: Expr, tail: Bool}
  FLFlLet{g: G, self: KSelf, bound: List<&2, String>, p: Pat, v: Expr, b: Expr, tail: Bool}
  FLFlExpr{g: G, self: KSelf, bound: List<&2, String>, e: Expr, tail: Bool}
  FLFlDeclGo{kind: Nat, d: Decl, g: G, name: String, mask: List<&2, Bool>}
  FLFlDecl{g: G, name: String, info: DInfo, d: Decl}
  FLIsflatMemo{g: G, name: String, m: Maybe<&2, String>}
  FLIsflat{g: G, name: String}

def FlSel.ty(k: FlSel) -> Type:
  match k:
    case FLFlExprs{g, self, bound, es}:
      KM(Bool)
    case FLFlCases{g, self, bound, cs, tail}:
      KM(Bool)
    case FLFlGlobalKind{g, self, name, kind, mask}:
      KM(Bool)
    case FLFlGlobal{g, self, name, info}:
      KM(Bool)
    case FLFlVar{g, self, bound, x}:
      KM(Bool)
    case FLFlCallDef{g, self, bound, f, kept, tail, me}:
      KM(Bool)
    case FLFlCallKind{kind, extra, full, g, self, bound, f, kept, tail}:
      KM(Bool)
    case FLFlCallSplit{g, self, bound, f, kind, s, tail}:
      KM(Bool)
    case FLFlCallGlobal{g, self, bound, f, args, tail, info}:
      KM(Bool)
    case FLFlCall{g, self, bound, f, args, tail}:
      KM(Bool)
    case FLFlParVals{g, self, bound, vs}:
      KM(Bool)
    case FLFlLetPar{g, self, bound, p, v, b}:
      KM(Bool)
    case FLFlLetGo{par, g, self, bound, p, v, b, tail}:
      KM(Bool)
    case FLFlLet{g, self, bound, p, v, b, tail}:
      KM(Bool)
    case FLFlExpr{g, self, bound, e, tail}:
      KM(Bool)
    case FLFlDeclGo{kind, d, g, name, mask}:
      KM(Bool)
    case FLFlDecl{g, name, info, d}:
      KM(Bool)
    case FLIsflatMemo{g, name, m}:
      KM(Bool)
    case FLIsflat{g, name}:
      KM(Bool)

def K.fl.go(n: Nat, k: FlSel) -> FlSel.ty(k):
  match n:
    case 0n:
      match k:
        case FLFlExprs{g, self, bound, es}:
          K.out(Bool, False{})
        case FLFlCases{g, self, bound, cs, tail}:
          K.out(Bool, False{})
        case FLFlGlobalKind{g, self, name, kind, mask}:
          K.out(Bool, False{})
        case FLFlGlobal{g, self, name, info}:
          K.out(Bool, False{})
        case FLFlVar{g, self, bound, x}:
          K.out(Bool, False{})
        case FLFlCallDef{g, self, bound, f, kept, tail, me}:
          K.out(Bool, False{})
        case FLFlCallKind{kind, extra, full, g, self, bound, f, kept, tail}:
          K.out(Bool, False{})
        case FLFlCallSplit{g, self, bound, f, kind, s, tail}:
          K.out(Bool, False{})
        case FLFlCallGlobal{g, self, bound, f, args, tail, info}:
          K.out(Bool, False{})
        case FLFlCall{g, self, bound, f, args, tail}:
          K.out(Bool, False{})
        case FLFlParVals{g, self, bound, vs}:
          K.out(Bool, False{})
        case FLFlLetPar{g, self, bound, p, v, b}:
          K.out(Bool, False{})
        case FLFlLetGo{par, g, self, bound, p, v, b, tail}:
          K.out(Bool, False{})
        case FLFlLet{g, self, bound, p, v, b, tail}:
          K.out(Bool, False{})
        case FLFlExpr{g, self, bound, e, tail}:
          K.out(Bool, False{})
        case FLFlDeclGo{kind, d, g, name, mask}:
          K.out(Bool, False{})
        case FLFlDecl{g, name, info, d}:
          K.out(Bool, False{})
        case FLIsflatMemo{g, name, m}:
          K.out(Bool, False{})
        case FLIsflat{g, name}:
          K.out(Bool, False{})
    case Succ{+fu}:
      match k:
        case FLFlExprs{+g, +self, +bound, es}:
          match es:
            case Nil{}:
              KM.pure(Bool, True{})
            case e <> t:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLFlExpr{g, self, bound, e, False{}})
                K.fl.and(a, K.fl.go(fu, FLFlExprs{g, self, bound, t}))
        case FLFlCases{+g, +self, +bound, cs, +tail}:
          match cs:
            case Nil{}:
              KM.pure(Bool, True{})
            case ECase{ps, body} <> t:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLFlExpr{g, self, Pats.vars(ps, bound), body, tail})
                K.fl.and(a, K.fl.go(fu, FLFlCases{g, self, bound, t, tail}))
            case other <> t:
              KM.pure(Bool, False{})
        case FLFlGlobalKind{+g, +self, +name, kind, mask}:
          match kind mask:
            case 3n m:
              KM.pure(Bool, True{})
            case 0n Nil{}:
              KM.if(Bool, Str.eq(KSelf.name(self), name), KM.pure(Bool, False{}), K.fl.go(fu, FLIsflat{g, name}))
            case k m:
              KM.pure(Bool, False{})
        case FLFlGlobal{+g, +self, +name, info}:
          DInfo{kind, mask} = info
          K.fl.go(fu, FLFlGlobalKind{g, self, name, U32.to_nat(kind), mask})
        case FLFlVar{+g, +self, +bound, +x}:
          KM.if(Bool, Bool.or(Str.has(bound, x), Str.eq(x, "_")), KM.pure(Bool, True{}), K.fl.go(fu, FLFlGlobal{g, self, x, G.def(g, x)}))
        case FLFlCallDef{+g, +self, +bound, +f, kept, tail, me}:
          match me:
            case True{}:
              K.fl.and(tail, K.fl.go(fu, FLFlExprs{g, self, bound, kept}))
            case False{}:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLIsflat{g, f})
                K.fl.and(a, K.fl.go(fu, FLFlExprs{g, self, bound, kept}))
        case FLFlCallKind{kind, extra, full, +g, +self, +bound, +f, kept, tail}:
          match kind extra full:
            case 3n e fl:
              KM.pure(Bool, True{})
            case 2n Nil{} True{}:
              K.fl.go(fu, FLFlExprs{g, self, bound, kept})
            case 0n Nil{} True{}:
              K.fl.go(fu, FLFlCallDef{g, self, bound, f, kept, tail, Str.eq(KSelf.name(self), f)})
            case k e fl:
              KM.pure(Bool, False{})
        case FLFlCallSplit{+g, +self, +bound, +f, kind, s, +tail}:
          Split{kept, all, extra, full} = s
          K.fl.go(fu, FLFlCallKind{kind, extra, full, g, self, bound, f, kept, tail})
        case FLFlCallGlobal{+g, +self, +bound, +f, args, tail, info}:
          DInfo{kind, mask} = info
          K.fl.go(fu, FLFlCallSplit{g, self, bound, f, U32.to_nat(kind), Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}),
            tail})
        case FLFlCall{+g, +self, +bound, +f, args, tail}:
          KM.if(Bool, Bool.or(Str.has(bound, f), Str.eq(f, "%gpu")), KM.pure(Bool, False{}),
            K.fl.go(fu, FLFlCallGlobal{g, self, bound, f, args, tail, G.def(g, f)}))
        case FLFlParVals{+g, +self, +bound, vs}:
          match vs:
            case Nil{}:
              KM.pure(Bool, True{})
            case +v <> t:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLFlExpr{g, self, bound, v, K.fl.direct(self, bound, v)})
                K.fl.and(a, K.fl.go(fu, FLFlParVals{g, self, bound, t}))
        case FLFlLetPar{+g, +self, +bound, p, v, b}:
          match v:
            case ECtor{n, vs}:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLFlParVals{g, self, bound, vs})
                K.fl.and(a, K.fl.go(fu, FLFlExpr{g, self, Pat.vars(p, bound), b, True{}}))
            case other:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLFlParVals{g, self, bound, [other]})
                K.fl.and(a, K.fl.go(fu, FLFlExpr{g, self, Pat.vars(p, bound), b, True{}}))
        # A parallel let is flat for the seq analysis only (its values run in order).
        case FLFlLetGo{par, +g, +self, +bound, p, +v, b, +tail}:
          match par:
            case True{}:
              K.fl.and(Bool.and(KSelf.seq(self), tail), K.fl.go(fu, FLFlLetPar{g, self, bound, p, v, b}))
            case False{}:
              do KM<Bool>:
                # In the seq analysis a let at statement level may call the def itself.
                a : Bool <- K.fl.go(fu, FLFlExpr{g, self, bound, v, Bool.and(Bool.and(KSelf.seq(self), tail), K.fl.direct(self, bound, v))})
                K.fl.and(a, K.fl.go(fu, FLFlExpr{g, self, Pat.vars(p, bound), b, tail}))
        case FLFlLet{+g, +self, +bound, +p, v, b, +tail}:
          K.fl.go(fu, FLFlLetGo{K.pat.is_par(p), g, self, bound, p, v, b, tail})
        case FLFlExpr{+g, +self, +bound, e, tail}:
          match e:
            case EVar{+x}:
              K.fl.go(fu, FLFlVar{g, self, bound, x})
            case ENum{n}:
              KM.pure(Bool, True{})
            case ENat{n}:
              KM.pure(Bool, True{})
            case EFlt{f}:
              KM.pure(Bool, True{})
            case EStr{t}:
              KM.pure(Bool, True{})
            case ETy{n, a}:
              KM.pure(Bool, True{})
            case ESucc{k, x}:
              K.fl.go(fu, FLFlExpr{g, self, bound, x, False{}})
            case ECtor{n, args}:
              K.fl.go(fu, FLFlExprs{g, self, bound, args})
            case ELet{p, v, b}:
              K.fl.go(fu, FLFlLet{g, self, bound, p, v, b, tail})
            case EMatch{scrs, cases}:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLFlExprs{g, self, bound, scrs})
                K.fl.and(a, K.fl.go(fu, FLFlCases{g, self, bound, cases, tail}))
            case ECall{EVar{+f}, args}:
              K.fl.go(fu, FLFlCall{g, self, bound, f, args, tail})
            case other:
              KM.pure(Bool, False{})
        case FLFlDeclGo{kind, d, +g, +name, +mask}:
          match kind d:
            case 0n DDef{n, ps, body, ret}:
              K.fl.go(fu, FLFlExpr{g, KSelf{name, 0, mask}, K.params(ps, mask), R.ops(body, "Nat"), True{}})
            case k o:
              KM.pure(Bool, False{})
        case FLFlDecl{+g, +name, info, d}:
          DInfo{kind, mask} = info
          K.fl.go(fu, FLFlDeclGo{U32.to_nat(kind), d, g, name, mask})
        case FLIsflatMemo{+g, +name, m}:
          match m:
            case Some{v}:
              KM.pure(Bool, Str.eq(v, "1"))
            case None{}:
              do KM<Bool>:
                # While it is analysed, a def reached again is in a cycle: not flat.
                K.memo.put("%flat " ++ name, "0")
                +ok : Bool <- K.fl.go(fu, FLFlDecl{g, name, G.def(g, name), G.body(g, name)})
                K.memo.put("%flat " ++ name, Bool.pick(String, ok, "1", "0"))
                return ok
        case FLIsflat{+g, +name}:
          do KM<Bool>:
            m : Maybe<&2, String> <- K.memo.get("%flat " ++ name)
            K.fl.go(fu, FLIsflatMemo{g, name, m})

def K.fl.expr(g: G, self: KSelf, bound: List<&2, String>, e: Expr, tail: Bool) -> KM(Bool):
  K.fl.go(Fuel.max(), FLFlExpr{g, self, bound, e, tail})

def K.isflat(g: G, name: String) -> KM(Bool):
  K.fl.go(Fuel.max(), FLIsflat{g, name})

def K.sq.decl.go(kind: Nat, d: Decl, +g: G, +name: String, +mask: List<&2, Bool>) -> KM(Bool):
  match kind d:
    case 0n DDef{n, ps, body, ret}:
      K.fl.and(U32.is_le(K.kept(mask), 8), K.fl.expr(g, KSelf{name, 1, mask}, K.params(ps, mask), R.ops(body, "Nat"),
        True{}))
    case k o:
      KM.pure(Bool, False{})

def K.sq.decl(+g: G, +name: String, info: DInfo, d: Decl) -> KM(Bool):
  DInfo{kind, mask} = info
  K.sq.decl.go(U32.to_nat(kind), d, g, name, mask)

def K.isseq.memo(+g: G, +name: String, m: Maybe<&2, String>) -> KM(Bool):
  match m:
    case Some{v}:
      KM.pure(Bool, Str.eq(v, "1"))
    case None{}:
      do KM<Bool>:
        +ok : Bool <- K.sq.decl(g, name, G.def(g, name), G.body(g, name))
        K.memo.put("%seq " ++ name, Bool.pick(String, ok, "1", "0"))
        return ok

# A def is seq when it would be flat if its parallel lets ran in order and
# it could call itself at statement level (in tail position, or as a let's
# or a parallel let's value): its sequential part (past the fork limit)
# runs in KQ_name (see KQ.def).
def K.isseq(+g: G, +name: String) -> KM(Bool):
  do KM<Bool>:
    m : Maybe<&2, String> <- K.memo.get("%seq " ++ name)
    K.isseq.memo(g, name, m)

# Whether a def is seq (see K.isseq): flat but for its parallel lets and
# calls to itself.
def Gen.isseq(+g: G, +name: String) -> Bool:
  Gen.isseq.fst(K.isseq(g, name)(KSt{8, 0, 0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}, DNil{}, Nil{}}))

def Gen.memo.find.go(st: St, +k: String) -> Maybe<&2, String> & St:
  St{n, protos, code, refs, errs, +memo, effs} = st
  (Env.find(memo, k), St{n, protos, code, refs, errs, memo, effs})

def Gen.memo.find(+k: String) -> Gen(Maybe<&2, String>):
  st => Gen.memo.find.go(st, k)

def PatR.conds(r: PatR) -> List<&2, String>:
  PatR{conds, binds} = r
  conds

# A match's scrutinees: their C variables and the code binding them.
type Scrs is Data:
  Scrs{cs: List<&2, String>, code: Doc}

def Scrs.of(r: List<&2, String> & Doc) -> Scrs:
  (cs, code) = r
  Scrs{cs, code}

# A pattern's bindings read into locals, and the code reading them.
type Loads is Data:
  Loads{binds: Env(), code: Doc}

def Loads.of(r: Env() & Doc) -> Loads:
  (binds, code) = r
  Loads{binds, code}

#
# The code generator is one def, Gen.rec, over a selector: each GS.. names
# one of its steps and carries that step's arguments; GSel.ty is the step's
# result. Fuel bounds the recursion (the steps do not all shrink an Expr).
type GSel is Data:
  GSExprs{g: G, env: Env(), xs: List<&2, Expr>}
  GSCallFull{g: G, env: Env(), name: String, mask: List<&2, Bool>, kept: List<&2, Expr>,
    all: List<&2, Expr>, extra: List<&2, Expr>, full: Bool}
  GSCallSplit{g: G, env: Env(), name: String, mask: List<&2, Bool>, s: Split}
  GSCallKind{g: G, env: Env(), name: String, kind: Nat, mask: List<&2, Bool>, s: Split}
  GSCallDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Expr>}
  GSCallLocal{g: G, env: Env(), f: Expr, args: List<&2, Expr>}
  GSFaddDoc{g: G, env: Env(), x: Expr, k: Expr, b: Expr}
  GSFaddEmit{g: G, env: Env(), k: Nat, x: Expr, y: Expr, b: Expr}
  GSFaddMul{g: G, env: Env(), m: Expr, b: Expr, k: Nat}
  GSFaddOne{g: G, env: Env(), a: Expr, m: Expr, km: Nat}
  GSFaddTwo{g: G, env: Env(), a: Expr, b: Expr, ka: Nat, kb: Nat}
  GSFadd{g: G, env: Env(), args: List<&2, Expr>}
  GSCallGlobal{g: G, env: Env(), name: String, args: List<&2, Expr>, fadd: Bool}
  GSCallVar{g: G, env: Env(), name: String, args: List<&2, Expr>, local: Bool}
  GSCallGpu{g: G, env: Env(), name: String, kept: List<&2, Expr>}
  GSCallBangPick{kind: Nat, extra: List<&2, Expr>, full: Bool, g: G, env: Env(), name: String,
    kept: List<&2, Expr>, args: List<&2, Expr>}
  GSCallBangSplit{g: G, env: Env(), name: String, kind: Nat, s: Split, args: List<&2, Expr>}
  GSCallBangDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Expr>}
  GSCallBangVar{g: G, env: Env(), name: String, args: List<&2, Expr>, local: Bool}
  GSCallBang{g: G, env: Env(), args: List<&2, Expr>}
  GSCallName{g: G, env: Env(), name: String, args: List<&2, Expr>, bang: Bool}
  GSCall{g: G, env: Env(), f: Expr, args: List<&2, Expr>}
  GSBitsCon{g: G, env: Env(), e: Expr}
  GSBitsGo{g: G, env: Env(), k: Nat, e: Expr}
  GSBits{g: G, env: Env(), e: Expr}
  GSBitsArgs{g: G, env: Env(), w: Nat, args: List<&2, Expr>}
  GSCtorInfo{g: G, env: Env(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Expr>}
  GSCtor{g: G, env: Env(), name: String, args: List<&2, Expr>}
  GSScrs{g: G, env: Env(), xs: List<&2, Expr>}
  GSTail{g: G, env: Env(), cps: List<&2, String>, s: Split}
  GSTailSelf{g: G, env: Env(), self: Self, args: List<&2, Expr>}
  GSDstJumpSplit{g: G, env: Env(), tgt: Tgt, name: String, s: Split}
  GSDstJump{g: G, env: Env(), tgt: Tgt, name: String, args: List<&2, Expr>}
  GSStmtCallDst{g: G, env: Env(), tgt: Tgt, name: String, args: List<&2, Expr>, dst: Bool}
  GSStmtCall{g: G, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Expr>,
    tail: Bool}
  GSDstField{hole: Bool, g: G, env: Env(), a: Expr}
  GSDstFields{g: G, env: Env(), xs: List<&2, Expr>, i: U32, hole: U32}
  GSStmtCtorNext{g: G, env: Env(), self: Self, tgt: Tgt, e: Expr}
  GSStmtCtorHole{g: G, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Expr>,
    hole: U32, next: Expr}
  GSStmtCtorPick{none: Bool, g: G, env: Env(), self: Self, tgt: Tgt, name: String,
    args: List<&2, Expr>, hole: U32}
  GSStmtCtor{g: G, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Expr>,
    hole: U32}
  GSBlock{g: G, env: Env(), e: Expr}
  GSExpr{g: G, env: Env(), e: Expr}
  GSLetVar{g: G, env: Env(), self: Self, tgt: Tgt, x: String, v: Expr, body: Expr, hole: Bool}
  GSCasesNext{g: G, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>,
    rest: List<&2, Expr>, conds: List<&2, String>, b: Doc}
  GSMatchGo{g: G, env: Env(), self: Self, tgt: Tgt, cases: List<&2, Expr>, r: Scrs}
  GSMatch{g: G, env: Env(), self: Self, tgt: Tgt, scrs: List<&2, Expr>, cases: List<&2, Expr>}
  GSStmt{g: G, env: Env(), self: Self, tgt: Tgt, e: Expr}
  GSCaseBodyMat{g: G, env: Env(), self: Self, tgt: Tgt, body: Expr, r: Loads}
  GSCaseBodyGo{opens: Bool, g: G, env: Env(), self: Self, tgt: Tgt, binds: Env(), body: Expr}
  GSCaseBody{g: G, env: Env(), self: Self, tgt: Tgt, binds: Env(), body: Expr}
  GSLam{g: G, env: Env(), p: Pat, body: Expr}
  GSLetPat{g: G, env: Env(), self: Self, tgt: Tgt, p: Pat, v: Expr, body: Expr}
  GSParVals{g: G, env: Env(), k: U32, i: U32, vs: List<&2, Expr>}
  GSParSeq{g: G, env: Env(), k: U32, i: U32, vs: List<&2, Expr>, decl: Bool}
  GSParFront{g: G, env: Env(), sn: String, k: U32, vs: List<&2, Expr>}
  GSParSq{sq: Bool, g: G, env: Env(), sn: String, k: U32, vs: List<&2, Expr>}
  GSParPick{mode: Nat, g: G, env: Env(), sn: String, k: U32, vs: List<&2, Expr>}
  GSPar{g: G, env: Env(), self: Self, tgt: Tgt, ps: List<&2, Pat>, vs: List<&2, Expr>,
    body: Expr}
  GSLetPar{g: G, env: Env(), self: Self, tgt: Tgt, ps: List<&2, Pat>, v: Expr, body: Expr}
  GSLetCtor{g: G, env: Env(), self: Self, tgt: Tgt, name: String, ps: List<&2, Pat>, v: Expr,
    body: Expr, par: Bool}
  GSLet{g: G, env: Env(), self: Self, tgt: Tgt, p: Pat, v: Expr, body: Expr}
  GSCases{g: G, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>, cases: List<&2, Expr>}

def GSel.ty(k: GSel) -> Type:
  match k:
    case GSExprs{g, env, xs}:
      List<&2, Doc>
    case GSBitsArgs{g, env, w, args}:
      List<&2, Doc>
    case GSDstFields{g, env, xs, i, hole}:
      List<&2, Doc>
    case GSScrs{g, env, xs}:
      List<&2, String> & Doc
    case other:
      Doc

def GSel.none(k: GSel) -> GSel.ty(k):
  match k:
    case GSExprs{g, env, xs}:
      Nil{}
    case GSCallFull{g, env, name, mask, kept, all, extra, full}:
      DNil{}
    case GSCallSplit{g, env, name, mask, s}:
      DNil{}
    case GSCallKind{g, env, name, kind, mask, s}:
      DNil{}
    case GSCallDef{g, env, name, info, args}:
      DNil{}
    case GSCallLocal{g, env, f, args}:
      DNil{}
    case GSFaddDoc{g, env, x, k, b}:
      DNil{}
    case GSFaddEmit{g, env, k, x, y, b}:
      DNil{}
    case GSFaddMul{g, env, m, b, k}:
      DNil{}
    case GSFaddOne{g, env, a, m, km}:
      DNil{}
    case GSFaddTwo{g, env, a, b, ka, kb}:
      DNil{}
    case GSFadd{g, env, args}:
      DNil{}
    case GSCallGlobal{g, env, name, args, fadd}:
      DNil{}
    case GSCallVar{g, env, name, args, local}:
      DNil{}
    case GSCallGpu{g, env, name, kept}:
      DNil{}
    case GSCallBangPick{kind, extra, full, g, env, name, kept, args}:
      DNil{}
    case GSCallBangSplit{g, env, name, kind, s, args}:
      DNil{}
    case GSCallBangDef{g, env, name, info, args}:
      DNil{}
    case GSCallBangVar{g, env, name, args, local}:
      DNil{}
    case GSCallBang{g, env, args}:
      DNil{}
    case GSCallName{g, env, name, args, bang}:
      DNil{}
    case GSCall{g, env, f, args}:
      DNil{}
    case GSBitsCon{g, env, e}:
      DNil{}
    case GSBitsGo{g, env, k, e}:
      DNil{}
    case GSBits{g, env, e}:
      DNil{}
    case GSBitsArgs{g, env, w, args}:
      Nil{}
    case GSCtorInfo{g, env, name, info, args}:
      DNil{}
    case GSCtor{g, env, name, args}:
      DNil{}
    case GSScrs{g, env, xs}:
      (Nil{}, DNil{})
    case GSTail{g, env, cps, s}:
      DNil{}
    case GSTailSelf{g, env, self, args}:
      DNil{}
    case GSDstJumpSplit{g, env, tgt, name, s}:
      DNil{}
    case GSDstJump{g, env, tgt, name, args}:
      DNil{}
    case GSStmtCallDst{g, env, tgt, name, args, dst}:
      DNil{}
    case GSStmtCall{g, env, self, tgt, name, args, tail}:
      DNil{}
    case GSDstField{hole, g, env, a}:
      DNil{}
    case GSDstFields{g, env, xs, i, hole}:
      Nil{}
    case GSStmtCtorNext{g, env, self, tgt, e}:
      DNil{}
    case GSStmtCtorHole{g, env, self, tgt, name, args, hole, next}:
      DNil{}
    case GSStmtCtorPick{none, g, env, self, tgt, name, args, hole}:
      DNil{}
    case GSStmtCtor{g, env, self, tgt, name, args, hole}:
      DNil{}
    case GSBlock{g, env, e}:
      DNil{}
    case GSExpr{g, env, e}:
      DNil{}
    case GSLetVar{g, env, self, tgt, x, v, body, hole}:
      DNil{}
    case GSCasesNext{g, env, self, tgt, cs, rest, conds, b}:
      DNil{}
    case GSMatchGo{g, env, self, tgt, cases, r}:
      DNil{}
    case GSMatch{g, env, self, tgt, scrs, cases}:
      DNil{}
    case GSStmt{g, env, self, tgt, e}:
      DNil{}
    case GSCaseBodyMat{g, env, self, tgt, body, r}:
      DNil{}
    case GSCaseBodyGo{opens, g, env, self, tgt, binds, body}:
      DNil{}
    case GSCaseBody{g, env, self, tgt, binds, body}:
      DNil{}
    case GSLam{g, env, p, body}:
      DNil{}
    case GSLetPat{g, env, self, tgt, p, v, body}:
      DNil{}
    case GSParVals{g, env, k, i, vs}:
      DNil{}
    case GSParSeq{g, env, k, i, vs, decl}:
      DNil{}
    case GSParFront{g, env, sn, k, vs}:
      DNil{}
    case GSParSq{sq, g, env, sn, k, vs}:
      DNil{}
    case GSParPick{mode, g, env, sn, k, vs}:
      DNil{}
    case GSPar{g, env, self, tgt, ps, vs, body}:
      DNil{}
    case GSLetPar{g, env, self, tgt, ps, v, body}:
      DNil{}
    case GSLetCtor{g, env, self, tgt, name, ps, v, body, par}:
      DNil{}
    case GSLet{g, env, self, tgt, p, v, body}:
      DNil{}
    case GSCases{g, env, self, tgt, cs, cases}:
      DNil{}

# Out of fuel: an error, and a value of the step's type.
def GSel.starve(k: GSel) -> Gen(GSel.ty(k)):
  do Gen<GSel.ty(k)>:
    Gen.error("out of fuel")
    return GSel.none(k)

def Gen.rec(n: Nat, k: GSel) -> Gen(GSel.ty(k)):
  match n:
    case 0n:
      GSel.starve(k)
    case 1n+ +fu:
      match k:
        case GSExprs{+g, +env, xs}:
          match xs:
            case Nil{}:
              Gen.pure(List<&2, Doc>, Nil{})
            case h <> t:
              do Gen<List<&2, Doc>>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, h})
                ds : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, t})
                return d <> ds
        case GSCallFull{+g, +env, +name, +mask, kept, all, extra, full}:
          match full:
            case True{}:
              do Gen<Doc>:
                ks : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, kept})
                xs : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, extra})
                return Gen.apply(xs, Doc.list([DStr{Gen.f(name) ++ "("}, Gen.commas(ks), DStr{")"}]))
            case False{}:
              do Gen<Doc>:
                Gen.clo(name)
                +as : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, all})
                return Doc.list([DStr{"mk_clo(" ++ Gen.w(name) ++ ", " ++
                  U32.show(U32.from_nat(List.length(&2, Bool, mask))) ++ ", " ++
                  U32.show(Gen.len(as)) ++ ", "}, Gen.arr(as), DStr{")"}])
        case GSCallSplit{+g, +env, +name, +mask, s}:
          match s:
            case Split{kept, all, extra, full}:
              Gen.rec(fu, GSCallFull{g, env, name, mask, kept, all, extra, full})
        case GSCallKind{+g, +env, +name, kind, +mask, s}:
          match kind:
            case 3n:
              Gen.pure(Doc, DStr{"0"})
            case 4n:
              do Gen<Doc>:
                Gen.error("unknown function: " ++ name)
                return DStr{"0"}
            case other:
              do Gen<Doc>:
                Gen.ref(name)
                Gen.rec(fu, GSCallSplit{g, env, name, mask, s})
        case GSCallDef{+g, +env, +name, info, args}:
          match info:
            case DInfo{kind, +mask}:
              Gen.rec(fu, GSCallKind{g, env, name, U32.to_nat(kind), mask,
                Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case GSCallLocal{+g, +env, f, args}:
          do Gen<Doc>:
            fd : Doc <- Gen.rec(fu, GSExpr{g, env, f})
            xs : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, args})
            return Gen.apply(xs, fd)
        case GSFaddDoc{+g, +env, x, k, b}:
          do Gen<Doc>:
            xd : Doc <- Gen.rec(fu, GSExpr{g, env, x})
            kd : Doc <- Gen.rec(fu, GSExpr{g, env, k})
            bd : Doc <- Gen.rec(fu, GSExpr{g, env, b})
            return Doc.list([DStr{"F32_mulk_add("}, xd, DStr{", "}, kd, DStr{", "}, bd, DStr{")"}])
        case GSFaddEmit{+g, +env, k, x, y, b}:
          match k:
            case 1n:
              Gen.rec(fu, GSFaddDoc{g, env, x, y, b})
            case other:
              Gen.rec(fu, GSFaddDoc{g, env, y, x, b})
        case GSFaddMul{+g, +env, m, b, k}:
          match m:
            case ECall{f, x <> y <> Nil{}}:
              Gen.rec(fu, GSFaddEmit{g, env, k, x, y, b})
            case other:
              Gen.rec(fu, GSCallDef{g, env, "F32.add", G.def(g, "F32.add"), [other, b]})
        # a + m, where m is x * k when km is not 0n.
        case GSFaddOne{+g, +env, a, m, km}:
          match km:
            case 0n:
              Gen.rec(fu, GSCallDef{g, env, "F32.add", G.def(g, "F32.add"), [a, m]})
            case 1n+p:
              Gen.rec(fu, GSFaddMul{g, env, m, a, km})
        case GSFaddTwo{+g, +env, a, b, ka, kb}:
          match ka:
            case 0n:
              Gen.rec(fu, GSFaddOne{g, env, a, b, kb})
            case 1n+p:
              Gen.rec(fu, GSFaddMul{g, env, a, b, ka})
        # a + b as F32_mulk_add(x, k, b) when a is x * k (see rt/bendrt.h).
        case GSFadd{+g, +env, args}:
          match args:
            case +a <> +b <> Nil{}:
              Gen.rec(fu, GSFaddTwo{g, env, a, b, Gen.fadd.k(a), Gen.fadd.k(b)})
            case other:
              Gen.rec(fu, GSCallDef{g, env, "F32.add", G.def(g, "F32.add"), other})
        case GSCallGlobal{+g, +env, +name, args, fadd}:
          match fadd:
            case True{}:
              Gen.rec(fu, GSFadd{g, env, args})
            case False{}:
              Gen.rec(fu, GSCallDef{g, env, name, G.def(g, name), args})
        case GSCallVar{+g, +env, +name, args, local}:
          match local:
            case True{}:
              Gen.rec(fu, GSCallLocal{g, env, EVar{name}, args})
            case False{}:
              Gen.rec(fu, GSCallGlobal{g, env, name, args, Str.eq(name, "F32.add")})
        # f!(args) with every argument of a def: G_f tries the device, then the CPU.
        case GSCallGpu{+g, +env, +name, kept}:
          do Gen<Doc>:
            Gen.ref(name)
            Gen.gpu(name)
            +ks : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, kept})
            Gen.proto(DStr{"static V G_" ++ Gen.mangle(name) ++ "(" ++ Gen.cparams(Gen.gpu.params(U32.to_nat(Gen.len(ks)), 0)) ++ ");\n"})
            return Doc.list([DStr{"G_" ++ Gen.mangle(name) ++ "("}, Gen.commas(ks), DStr{")"}])
        case GSCallBangPick{kind, extra, full, +g, +env, +name, kept, args}:
          match kind extra full:
            case 0n Nil{} True{}:
              Gen.rec(fu, GSCallGpu{g, env, name, kept})
            case k e f:
              Gen.rec(fu, GSCall{g, env, EVar{name}, args})
        case GSCallBangSplit{+g, +env, +name, kind, s, args}:
          match s:
            case Split{kept, all, extra, full}:
              Gen.rec(fu, GSCallBangPick{kind, extra, full, g, env, name, kept, args})
        case GSCallBangDef{+g, +env, +name, info, +args}:
          match info:
            case DInfo{kind, +mask}:
              Gen.rec(fu, GSCallBangSplit{g, env, name, U32.to_nat(kind),
                Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}), args})
        case GSCallBangVar{+g, +env, +name, args, local}:
          match local:
            case True{}:
              Gen.rec(fu, GSCallLocal{g, env, EVar{name}, args})
            case False{}:
              Gen.rec(fu, GSCallBangDef{g, env, name, G.def(g, name), args})
        # f!(args): a call the device may run (see the GPU backend below).
        case GSCallBang{+g, +env, args}:
          match args:
            case EVar{+name} <> xs:
              Gen.rec(fu, GSCallBangVar{g, env, name, xs, Env.has(env, name)})
            case f <> xs:
              Gen.rec(fu, GSCall{g, env, f, xs})
            case Nil{}:
              Gen.pure(Doc, DStr{"0"})
        case GSCallName{+g, +env, +name, args, bang}:
          match bang:
            case True{}:
              Gen.rec(fu, GSCallBang{g, env, args})
            case False{}:
              Gen.rec(fu, GSCallVar{g, env, name, args, Env.has(env, name)})
        case GSCall{+g, +env, f, args}:
          match f:
            case EVar{+name}:
              Gen.rec(fu, GSCallName{g, env, name, args, Str.eq(name, "%gpu")})
            case other:
              Gen.rec(fu, GSCallLocal{g, env, other, args})
        case GSBitsCon{+g, +env, e}:
          match e:
            case ECtor{n, a <> b <> Nil{}}:
              do Gen<Doc>:
                da : Doc <- Gen.rec(fu, GSExpr{g, env, a})
                db : Doc <- Gen.rec(fu, GSBits{g, env, b})
                return Doc.list([DStr{"word_con("}, da, DStr{", "}, db, DStr{")"}])
            case other:
              Gen.rec(fu, GSExpr{g, env, other})
        case GSBitsGo{+g, +env, k, e}:
          match k:
            case 0n:
              Gen.rec(fu, GSBitsCon{g, env, e})
            case 1n:
              Gen.pure(Doc, DStr{"0"})
            case 2n+q:
              Gen.rec(fu, GSExpr{g, env, e})
        case GSBits{+g, +env, +e}:
          Gen.rec(fu, GSBitsGo{g, env, Expr.wordk(e), e})
        case GSBitsArgs{+g, +env, w, args}:
          match w args:
            case 2n+p xs:
              Gen.rec(fu, GSExprs{g, env, xs})
            case k a <> Nil{}:
              do Gen<List<&2, Doc>>:
                d : Doc <- Gen.rec(fu, GSBits{g, env, a})
                return [d]
            case k xs:
              Gen.rec(fu, GSExprs{g, env, xs})
        case GSCtorInfo{+g, +env, name, info, args}:
          match info:
            case None{}:
              do Gen<Doc>:
                Gen.error("unknown constructor: " ++ name)
                return DStr{"0"}
            case Some{CInfo{tag, ar, kind, single}}:
              do Gen<Doc>:
                ds : List<&2, Doc> <- Gen.rec(fu, GSBitsArgs{g, env, P.which(name, ["U32", "F32"]), args})
                return Gen.ctor.kind(tag, U32.to_nat(kind), ds)
        case GSCtor{+g, +env, +name, args}:
          Gen.rec(fu, GSCtorInfo{g, env, name, G.ctor(g, name), args})
        # Scrutinees are bound to fresh C variables.
        case GSScrs{+g, +env, xs}:
          match xs:
            case Nil{}:
              Gen.pure(List<&2, String> & Doc, (Nil{}, DNil{}))
            case h <> t:
              do Gen<List<&2, String> & Doc>:
                +k : U32 <- Gen.fresh()
                +c : String <- Gen.pure(String, "s" ++ U32.show(k))
                d : Doc <- Gen.rec(fu, GSExpr{g, env, h})
                r : List<&2, String> & Doc <- Gen.rec(fu, GSScrs{g, env, t})
                return Gen.scrs.put(c, d, r)
        case GSTail{+g, +env, cps, s}:
          match s:
            case Split{kept, all, extra, full}:
              do Gen<Doc>:
                ds : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, kept})
                return Doc.list([DStr{"{ "}, Gen.tail.temps(ds, 0), Gen.tail.assign(cps, 0),
                  DStr{"goto top; }\n"}])
        case GSTailSelf{+g, +env, self, args}:
          match self:
            case Self{sn, +mask, cps}:
              Gen.rec(fu, GSTail{g, env, cps, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case GSDstJumpSplit{+g, +env, +tgt, +name, s}:
          match s:
            case Split{kept, all, extra, full}:
              do Gen<Doc>:
                Gen.ref(name)
                ds : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, kept})
                return Doc.list([DStr{"BEND_MUSTTAIL return D_" ++ Gen.mangle(name) ++ "(dst"},
                  Gen.dst.args(Tgt.n(tgt), ds), DStr{");\n"}])
        # A tail call to another def of the group: a jump to its D_ function,
        # with the same dst.
        case GSDstJump{+g, +env, +tgt, +name, args}:
          Gen.rec(fu, GSDstJumpSplit{g, env, tgt, name,
            Gen.split(DInfo.mask(G.def(g, name)), args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case GSStmtCallDst{+g, +env, +tgt, +name, args, dst}:
          match dst:
            case True{}:
              Gen.rec(fu, GSDstJump{g, env, tgt, name, args})
            case False{}:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSCall{g, env, EVar{name}, args})
                return Gen.ret(tgt, d)
        case GSStmtCall{+g, +env, +self, +tgt, +name, +args, tail}:
          match tail:
            case True{}:
              Gen.rec(fu, GSTailSelf{g, env, self, args})
            case False{}:
              Gen.rec(fu, GSStmtCallDst{g, env, tgt, name, args, Gen.dst.call(g, env, tgt, name, args)})
        # The hole holds BEND_HOLE until it is filled (the collector looks for it).
        case GSDstField{hole, +g, +env, a}:
          match hole:
            case True{}:
              Gen.pure(Doc, DStr{"BEND_HOLE"})
            case False{}:
              Gen.rec(fu, GSExpr{g, env, a})
        case GSDstFields{+g, +env, xs, +i, +hole}:
          match xs:
            case Nil{}:
              Gen.pure(List<&2, Doc>, Nil{})
            case a <> t:
              do Gen<List<&2, Doc>>:
                d : Doc <- Gen.rec(fu, GSDstField{U32.is_eq(U32.inc(i), hole), g, env, a})
                r : List<&2, Doc> <- Gen.rec(fu, GSDstFields{g, env, t, U32.inc(i), hole})
                return d <> r
        case GSStmtCtorNext{+g, +env, +self, +tgt, e}:
          match e:
            case ECall{EVar{+h}, +hargs}:
              Gen.rec(fu, GSStmtCall{g, env, self, tgt, h, hargs, Gen.is_tail(env, self, tgt, h, hargs)})
            case other:
              Gen.pure(Doc, DStr{"bend_fail(\"hole\");\n"})
        case GSStmtCtorHole{+g, +env, +self, +tgt, +name, args, +hole, next}:
          do Gen<Doc>:
            ds : List<&2, Doc> <- Gen.rec(fu, GSDstFields{g, env, args, 0, hole})
            b : Doc <- Gen.rec(fu, GSStmtCtorNext{g, env, self, tgt, next})
            return Doc.list([DStr{"{ V dc = "}, Gen.ctor.hnode(Gen.stmt.ctor.tag(g, name), ds),
              DStr{"; *dst = dc; dst = &FLD(dc, " ++ U32.show((hole - 1 : U32)) ++ ");\n"}, b, DStr{"}\n"}])
        case GSStmtCtorPick{none, +g, +env, +self, +tgt, +name, +args, +hole}:
          match none:
            case True{}:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, ECtor{name, args}})
                return Gen.ret(tgt, d)
            case False{}:
              Gen.rec(fu, GSStmtCtorHole{g, env, self, tgt, name, args, hole,
                Gen.dst.nth(U32.to_nat(hole), EErr{"hole"} <> args)})
        # C(.., f(..), ..) with f in the group: the node is stored with a hole
        # where f's result goes, dst moves to the hole, and f's code follows.
        case GSStmtCtor{+g, +env, +self, +tgt, +name, +args, +hole}:
          Gen.rec(fu, GSStmtCtorPick{U32.is_zero(hole), g, env, self, tgt, name, args, hole})
        # A statement-level expression used as a value: ({ V r; ...; r; }).
        case GSBlock{+g, +env, e}:
          do Gen<Doc>:
            +k : U32 <- Gen.fresh()
            +r : String <- Gen.pure(String, "r" ++ U32.show(k))
            b : Doc <- Gen.rec(fu, GSStmt{g, env, Self.none(), TSet{r}, e})
            return Doc.list([DStr{"({ V " ++ r ++ ";\n"}, b, DStr{r ++ "; })"}])
        case GSExpr{+g, +env, e}:
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
              Gen.rec(fu, GSCall{g, env, f, args})
            case ECtor{name, args}:
              Gen.rec(fu, GSCtor{g, env, name, args})
            case ELam{p, body}:
              Gen.rec(fu, GSLam{g, env, p, body})
            case ELet{p, v, body}:
              Gen.rec(fu, GSBlock{g, env, ELet{p, v, body}})
            case EMatch{scrs, cases}:
              Gen.rec(fu, GSBlock{g, env, EMatch{scrs, cases}})
            case ESucc{k, x}:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, x})
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
        case GSLetVar{+g, +env, +self, +tgt, +x, +v, +body, hole}:
          match hole:
            case True{}:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, v})
                b : Doc <- Gen.rec(fu, GSStmt{g, env, self, tgt, body})
                return Doc.list([DStr{"(void)("}, d, DStr{");\n"}, b])
            case False{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +c : String <- Gen.pure(String, Gen.scalar.wrap(Gen.scalar.var(env, v), "v" ++ U32.show(k)))
                d : Doc <- Gen.rec(fu, GSExpr{g, env, v})
                b : Doc <- Gen.rec(fu, GSStmt{g, Bind{x, c} <> env, self, tgt, body})
                return Doc.list([DStr{"V " ++ c ++ " = "}, d, DStr{";\n"}, Gen.shares.g(g, [Bind{x, c}], body), b])
        case GSCasesNext{+g, +env, +self, +tgt, +cs, rest, conds, b}:
          match conds:
            case Nil{}:
              Gen.pure(Doc, Doc.list([DStr{"{\n"}, b, DStr{"}\n"}]))
            case h <> t:
              do Gen<Doc>:
                more : Doc <- Gen.rec(fu, GSCases{g, env, self, tgt, cs, rest})
                return Doc.list([DStr{"if (" ++ Gen.and(h <> t) ++ ") {\n"}, b,
                  DStr{"} else "}, more])
        case GSMatchGo{+g, +env, +self, +tgt, cases, r}:
          match r:
            case Scrs{cs, decls}:
              do Gen<Doc>:
                body : Doc <- Gen.rec(fu, GSCases{g, env, self, tgt, cs, cases})
                return Doc.list([decls, body])
        case GSMatch{+g, +env, +self, +tgt, scrs, cases}:
          do Gen<Doc>:
            r : List<&2, String> & Doc <- Gen.rec(fu, GSScrs{g, env, scrs})
            Gen.rec(fu, GSMatchGo{g, env, self, tgt, cases, Scrs.of(r)})
        case GSStmt{+g, +env, +self, +tgt, e}:
          match e:
            case ELet{p, v, body}:
              Gen.rec(fu, GSLet{g, env, self, tgt, p, v, body})
            case EMatch{scrs, cases}:
              Gen.rec(fu, GSMatch{g, env, self, tgt, scrs, cases})
            case ECall{EVar{+name}, +args}:
              Gen.rec(fu, GSStmtCall{g, env, self, tgt, name, args, Gen.is_tail(env, self, tgt, name, args)})
            case ECtor{+name, +args}:
              Gen.rec(fu, GSStmtCtor{g, env, self, tgt, name, args,
                Gen.dst.hole(g, env, tgt, Gen.dst.node(G.ctor(g, name)), args, 0, 0)})
            case other:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, other})
                return Gen.ret(tgt, d)
        # The fields and the opened nodes are read, then the nodes taken, each
        # before the nodes inside it: a shared one shares its fields, so the
        # nodes inside it are shared when they are taken, and share theirs.
        case GSCaseBodyMat{+g, +env, +self, +tgt, +body, r}:
          match r:
            case Loads{+mb, loads}:
              +vars = Gen.vars(mb)
              do Gen<Doc>:
                b : Doc <- Gen.rec(fu, GSStmt{g, List.append(&2, Bind, vars, env), self, tgt, body})
                return Doc.list([loads, DStr{Gen.takes.stmts(Gen.takes(mb, "%top")) ++
                  Gen.takes.stmts(List.reverse(&2, String, Gen.takes(mb, "%sub")))}, Gen.shares.g(g, vars, body), b])
        case GSCaseBodyGo{opens, +g, +env, +self, +tgt, +binds, +body}:
          match opens:
            case False{}:
              do Gen<Doc>:
                b : Doc <- Gen.rec(fu, GSStmt{g, List.append(&2, Bind, binds, env), self, tgt, body})
                return Doc.list([Gen.shares.g(g, binds, body), b])
            case True{}:
              do Gen<Doc>:
                r : Env() & Doc <- Gen.mat(binds)
                Gen.rec(fu, GSCaseBodyMat{g, env, self, tgt, body, Loads.of(r)})
        # A body after a pattern's bindings: the nodes the pattern opens are
        # freed (see above).
        case GSCaseBody{+g, +env, +self, +tgt, +binds, +body}:
          Gen.rec(fu, GSCaseBodyGo{Bool.or(Bool.and(Gen.free(g), Gen.opens(binds)), Gen.halves(binds)), g, env,
            self, tgt, binds, body})
        case GSLam{+g, +env, +p, +body}:
          +caps = Gen.caps(FV.expr(body, Pat.vars(p, Nil{}), Nil{}), env)
          +n = U32.from_nat(List.length(&2, Bind, caps))
          do Gen<Doc>:
            +k : U32 <- Gen.fresh()
            +name : String <- Gen.pure(String, "L" ++ U32.show(k))
            Gen.proto(DStr{"static V " ++ name ++ "(V *a);\n"})
            +binds : Env() <- Gen.pure(Env(), PatR.binds(Gen.pat(g, p, "a[" ++ U32.show(n) ++ "]",
              PatR{Nil{}, Nil{}})))
            b : Doc <- Gen.rec(fu, GSCaseBody{g, Gen.caps.inner(caps, 0), Self.none(), TRet{}, binds, body})
            Gen.code(Doc.list([DStr{"static V " ++ name ++ "(V *a) {\n"}, b, DStr{"}\n"}]))
            return Doc.list([DStr{"mk_clo(" ++ name ++ ", " ++ U32.show(U32.inc(n)) ++ ", " ++
              U32.show(n) ++ ", "}, Gen.arr(Gen.caps.outer(caps)), DStr{")"}])
        case GSLetPat{+g, +env, +self, +tgt, +p, v, +body}:
          do Gen<Doc>:
            +k : U32 <- Gen.fresh()
            +c : String <- Gen.pure(String, "v" ++ U32.show(k))
            d : Doc <- Gen.rec(fu, GSExpr{g, env, v})
            +binds : Env() <- Gen.pure(Env(), PatR.binds(Gen.pat(g, p, c, PatR{Nil{}, Nil{}})))
            b : Doc <- Gen.rec(fu, GSCaseBody{g, env, self, tgt, binds, body})
            return Doc.list([DStr{"V " ++ c ++ " = "}, d, DStr{";\n"}, b])
        # Forks every value but the last, evaluates the last, then joins the
        # forks in reverse.
        case GSParVals{+g, +env, +k, +i, vs}:
          match vs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case v <> Nil{}:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, v})
                return Doc.list([DStr{"V " ++ Gen.par.name(k, i) ++ " = "}, d, DStr{";\n"}])
            case v <> t:
              do Gen<Doc>:
                c : Doc <- Gen.rec(fu, GSLam{g, env, PVar{"_"}, v})
                rest : Doc <- Gen.rec(fu, GSParVals{g, env, k, U32.inc(i), t})
                return Doc.list([DStr{"V " ++ Gen.par.name(k, i) ++ "t = par_fork("}, c, DStr{");\n"},
                  rest, DStr{"V " ++ Gen.par.name(k, i) ++ " = par_join(" ++ Gen.par.name(k, i) ++
                  "t);\n"}])
        # The values in order: declared (in S_name), or assigned (at the
        # frontier).
        case GSParSeq{+g, +env, +k, +i, vs, +decl}:
          match vs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case v <> t:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, v})
                rest : Doc <- Gen.rec(fu, GSParSeq{g, env, k, U32.inc(i), t, decl})
                return Doc.list([DStr{Bool.pick(String, decl, "V ", "") ++ Gen.par.name(k, i) ++ " = "}, d, DStr{";\n"}, rest])
        # A seq def's parallel let: forks above the frontier (par_depth), and
        # in order below it, through S_name.
        case GSParFront{+g, +env, +sn, +k, +vs}:
          +n = List.length(&2, Expr, vs)
          do Gen<Doc>:
            sq : Doc <- Gen.rec(fu, GSParSeq{g, env, k, 0, vs, False{}})
            +j : U32 <- Gen.fresh()
            fk : Doc <- Gen.rec(fu, GSParVals{g, env, j, 0, vs})
            return Doc.list([DStr{Gen.par.decls(n, k, 0) ++ "\nif (par_depth >= par_front) {\n#define " ++ Gen.f(sn) ++ " S_" ++
              Gen.mangle(sn) ++ "\n"}, sq, DStr{"#undef " ++ Gen.f(sn) ++ "\n} else {\npar_depth += 1;\n"}, fk,
              DStr{Gen.par.copy(n, k, j, 0) ++ "\npar_depth -= 1;\n}\n"}])
        case GSParSq{sq, +g, +env, +sn, +k, +vs}:
          match sq:
            case True{}:
              Gen.rec(fu, GSParFront{g, env, sn, k, vs})
            case False{}:
              Gen.rec(fu, GSParVals{g, env, k, 0, vs})
        case GSParPick{mode, +g, +env, +sn, +k, +vs}:
          match mode:
            case 1n:
              Gen.rec(fu, GSParSeq{g, env, k, 0, vs, True{}})
            case other:
              Gen.rec(fu, GSParSq{Gen.isseq(g, sn), g, env, sn, k, vs})
        case GSPar{+g, +env, +self, +tgt, +ps, +vs, +body}:
          match self:
            case Self{+sn, sm, sc}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                mode : Maybe<&2, String> <- Gen.memo.find("%seqmode")
                pre : Doc <- Gen.rec(fu, GSParPick{Gen.par.mode(mode, sn), g, env, sn, k, vs})
                b : Doc <- Gen.rec(fu, GSStmt{g, Gen.par.env(ps, k, 0, env), Self{sn, sm, sc}, tgt, body})
                return Doc.list([pre, Gen.shares.g(g, Gen.par.env(ps, k, 0, Nil{}), body), b])
        case GSLetPar{+g, +env, +self, +tgt, ps, v, body}:
          match v:
            case ECtor{n, vs}:
              Gen.rec(fu, GSPar{g, env, self, tgt, ps, vs, body})
            case other:
              Gen.rec(fu, GSPar{g, env, self, tgt, ps, [other], body})
        case GSLetCtor{+g, +env, +self, +tgt, name, ps, v, body, par}:
          match par:
            case True{}:
              Gen.rec(fu, GSLetPar{g, env, self, tgt, ps, v, body})
            case False{}:
              Gen.rec(fu, GSLetPat{g, env, self, tgt, PCtor{name, ps}, v, body})
        case GSLet{+g, +env, +self, +tgt, p, v, body}:
          match p:
            case PVar{+x}:
              Gen.rec(fu, GSLetVar{g, env, self, tgt, x, v, body, Str.eq(x, "_")})
            case PCtor{+name, ps}:
              Gen.rec(fu, GSLetCtor{g, env, self, tgt, name, ps, v, body, Str.eq(name, "%par")})
            case other:
              Gen.rec(fu, GSLetPat{g, env, self, tgt, other, v, body})
        case GSCases{+g, +env, +self, +tgt, +cs, cases}:
          match cases:
            case Nil{}:
              Gen.pure(Doc, DStr{"{ bend_fail(\"runtime fail-stop\"); }\n"})
            case ECase{+ps, +body} <> t:
              +pr = Gen.pats(g, ps, cs, PatR{Nil{}, Nil{}})
              +conds = PatR.conds(pr)
              +binds = PatR.binds(pr)
              do Gen<Doc>:
                b : Doc <- Gen.rec(fu, GSCaseBody{g, env, self, tgt, binds, body})
                Gen.rec(fu, GSCasesNext{g, env, self, tgt, cs, t, List.reverse(&2, String, conds), b})
            case other <> t:
              Gen.rec(fu, GSCases{g, env, self, tgt, cs, t})

def Gen.stmt(+g: G, +env: Env(), +self: Self, +tgt: Tgt, e: Expr) -> Gen(Doc):
  Gen.rec(Fuel.max(), GSStmt{g, env, self, tgt, e})

# C parameter list and environment of a def.
type Sig is Data:
  Sig{params: List<&2, String>, env: Env(), wargs: List<&2, String>}

def Gen.sig(ps: List<&2, Param>, mask: List<&2, Bool>, +i: U32, r: Sig) -> Sig:
  match ps mask:
    case Param{x, m, t} <> pt True{} <> mt:
      Sig{params, env, wargs} = r
      +c = "a" ++ U32.show(i)
      Gen.sig(pt, mt, U32.inc(i), Sig{List.append(&2, String, params, [c]),
        Bind{x, Gen.scalar.wrap(Gen.scalar.ty(t), c)} <> env, List.append(&2, String, wargs,
        ["a[" ++ U32.show(i) ++ "]"])})
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

def Gen.memo.add.go(st: St, b: Bind) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, b <> memo, effs})

def Gen.memo.add(b: Bind) -> Gen(Unit):
  st => Gen.memo.add.go(st, b)

# S_name, a seq def's sequential clone: its parallel lets run in order and
# its calls to itself stay in S_name (F_name is renamed to it inside).
def Gen.def.seq(sq: Bool, +g: G, +name: String, +mask: List<&2, Bool>, +body: Expr, +env: Env(),
  +params: List<&2, String>) -> Gen(Unit):
  match sq:
    case True{}:
      +head = "static V S_" ++ Gen.mangle(name) ++ "(" ++ Gen.cparams(params) ++ ")"
      do Gen<Unit>:
        Gen.proto(DStr{head ++ ";\n"})
        Gen.memo.add(Bind{"%seqmode", name})
        b : Doc <- Gen.stmt(g, env, Self{name, mask, params}, TRet{}, R.ops(body, "Nat"))
        Gen.memo.add(Bind{"%seqmode", ""})
        Gen.code(Doc.list([DStr{"#define " ++ Gen.f(name) ++ " S_" ++ Gen.mangle(name) ++ "\n" ++ head ++ " {\ntop:;\n"},
          Gen.shares.g(g, env, R.ops(body, "Nat")), b, DStr{"}\n#undef " ++ Gen.f(name) ++ "\n"}]))
    case False{}:
      Gen.pure(Unit, Unit{})

# A C parameter or argument list padded to n entries: names z0, z1, ...
# (names) or zeros.
def Gen.dst.pad(n: Nat, xs: List<&2, String>, +names: Bool, +i: U32) -> List<&2, String>:
  match n xs:
    case 0n l:
      Nil{}
    case 1n+m Nil{}:
      Bool.pick(String, names, "z" ++ U32.show(i), "0") <> Gen.dst.pad(m, Nil{}, names, U32.inc(i))
    case 1n+m x <> t:
      x <> Gen.dst.pad(m, t, names, U32.inc(i))

# A def of a destination-passing group: D_name stores its result through
# dst (see Dps), and F_name calls it with dst pointing at a local.
def Gen.def.dst(+g: G, +name: String, +mask: List<&2, Bool>, +body: Expr, +params: List<&2, String>,
  +env: Env(), +wargs: List<&2, String>, grp: DGrp
) -> Gen(Unit):
  DGrp{+id, +n} = grp
  +m = Gen.mangle(name)
  +dhead = "static V D_" ++ m ++ "(" ++ String.join("V *dst" <> Gen.cparams.go(Gen.dst.pad(U32.to_nat(n),
    params, True{}, 0)), ", ") ++ ")"
  +head = "static V " ++ Gen.f(name) ++ "(" ++ Gen.cparams(params) ++ ")"
  do Gen<Unit>:
    Gen.proto(DStr{head ++ ";\n" ++ dhead ++ ";\n"})
    b : Doc <- Gen.stmt(g, env, Self{name, mask, params}, TDst{id, n}, R.ops(body, "Nat"))
    Gen.code(Doc.list([DStr{dhead ++ " {\ntop:;\n"}, Gen.shares.g(g, env, R.ops(body, "Nat")), b,
      DStr{"}\n"}]))
    Gen.code(DStr{head ++ " { V r; D_" ++ m ++ "(" ++ String.join("&r" <> Gen.dst.pad(U32.to_nat(n), params,
      False{}, 0), ", ") ++ "); return r; }\n"})
    Gen.wrapper(name, wargs)

def Pat.is_par(p: Pat) -> Bool:
  match p:
    case PCtor{+n, ps}:
      Str.eq(n, "%par")
    case other:
      False{}

# Whether an expression holds a parallel let (outside lambdas). A list
# field is its head, then the node rebuilt with the rest.
def Expr.has_par(e: Expr) -> Bool:
  match e:
    case ELet{p, +v, +b}:
      Bool.pick(Unit -> Bool, Pat.is_par(p), u => True{},
        u => Bool.pick(Unit -> Bool, Expr.has_par(v), u => True{}, u => Expr.has_par(b))(Unit{}))(Unit{})
    case EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(EMatch{t, cases}))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case +c <> t:
              Bool.pick(Unit -> Bool, Expr.has_par(c), u => True{}, u => Expr.has_par(EMatch{Nil{}, t}))(Unit{})
    case ECase{ps, b}:
      Expr.has_par(b)
    case ECall{f, args}:
      match args:
        case Nil{}:
          Expr.has_par(f)
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(ECall{f, t}))(Unit{})
    case ECtor{k, args}:
      match args:
        case Nil{}:
          False{}
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(ECtor{k, t}))(Unit{})
    case EOp{op, +a, +b}:
      Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(b))(Unit{})
    case ESucc{k, x}:
      Expr.has_par(x)
    case EAnn{x, ty}:
      Expr.has_par(x)
    case other:
      False{}

def Gen.def.plain(+g: G, +name: String, +mask: List<&2, Bool>, +body: Expr,
  +params: List<&2, String>, +env: Env(), +wargs: List<&2, String>
) -> Gen(Unit):
  +head = "static V " ++ Gen.f(name) ++ "(" ++ Gen.cparams(params) ++ ")"
  do Gen<Unit>:
    Gen.proto(DStr{head ++ ";\n"})
    b : Doc <- Gen.stmt(g, env, Self{name, mask, params}, TRet{}, R.ops(body, "Nat"))
    Gen.code(Doc.list([DStr{head ++ " {\ntop:;\n"}, Gen.shares.g(g, env, R.ops(body, "Nat")), b, DStr{"}\n"}]))
    Gen.wrapper(name, wargs)
    Gen.def.seq(Bool.and(Expr.has_par(body), Gen.isseq(g, name)), g, name, mask, body, env, params)

def Gen.def.body.pick(plain: Bool, +g: G, +name: String, +mask: List<&2, Bool>, +body: Expr,
  +params: List<&2, String>, +env: Env(), +wargs: List<&2, String>
) -> Gen(Unit):
  match plain:
    case False{}:
      Gen.def.dst(g, name, mask, body, params, env, wargs, G.dps(g, name))
    case True{}:
      Gen.def.plain(g, name, mask, body, params, env, wargs)

def Gen.def.body(+g: G, +name: String, +mask: List<&2, Bool>, +body: Expr, sig: Sig) ->
  Gen(Unit):
  Sig{+params, +env, +wargs} = sig
  Gen.def.body.pick(String.is_empty(DGrp.id(G.dps(g, name))), g, name, mask, body, params, env, wargs)

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

def Gen.gpu.emit.errs(+g: G, +ts: List<&2, String>, errs: List<&2, String>, +code: String, wraps: List<&2, String>) ->
  String:
  match errs:
    case Nil{}:
      "\n// The device code of the !-calls: rt/gpu.h, then this program's part\n#include \"gpu.h\"\n\n" ++ code ++
        "\n#include \"gpuhost.h\"\n\nstatic const char K_SRC[] =\n" ++ K.lit(code) ++
        ";\n\nstatic const GpuFn K_FNS[] = {" ++ Gen.gpu.fns(wraps) ++
        "{0, 0}};\nstatic GpuProg K_PROG = {K_SRC, bend_kernel, bend_kq, K_FNS};\n\n" ++ Gen.gpu.stubs(g, ts, True{})
    case e <> t:
      "\n// The !-calls run on the CPU:\n" ++ Gen.gpu.errs(e <> t) ++ Gen.gpu.stubs(g, ts, False{})

# A program's device code (what follows rt/gpu.h: label defines, frame sizes,
# flat functions and the blocks, k_cases), the defs it has wrappers for, and
# errors.
type KOut is Data:
  KOut{code: String, wraps: List<&2, String>, errs: List<&2, String>}

def Gen.gpu.emit(+g: G, +ts: List<&2, String>, out: KOut) -> String:
  KOut{code, wraps, errs} = out
  Gen.gpu.emit.errs(g, ts, errs, code, wraps)

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

def K.block_doc.if(none: Bool, +l: U32, d: Doc) -> Doc:
  match none:
    case True{}:
      DNil{}
    case False{}:
      Doc.list([DStr{"case " ++ U32.show(l) ++ ": {\n"}, d, DStr{"break;\n}\n"}])

# A finished block as a case (label 0: none, while a lambda compiles).
def K.block_doc(+l: U32, d: Doc) -> Doc:
  K.block_doc.if(U32.is_zero(l), l, d)

# The cases of k_kq, which runs a waiting KQ_ call (see rt/gpu.h).
def KQ.cases.of(memo: List<&2, Bind>) -> String:
  match memo:
    case Nil{}:
      ""
    case Bind{+k, v} <> t:
      Bool.pick(String, Str.eq(k, "%kqcase"), v, "") ++ KQ.cases.of(t)

def K.fn.new(+name: String, st: KSt) -> U32 & KSt:
  KSt{+n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (n, KSt{U32.inc(n), sl, curl, cur, out, Bind{name, U32.show(n)} <> fns, name <> todo, frames, errs, flat, memo})

def K.fn.found(+name: String, m: Maybe<&2, String>, st: KSt) -> U32 & KSt:
  match m:
    case Some{l}:
      (Maybe.default(&2, U32, U32.read(l), 0), st)
    case None{}:
      K.fn.new(name, st)

# The entry label of a function, made (and queued to compile) on first use.
def K.fn.go(+name: String, st: KSt) -> U32 & KSt:
  KSt{+n, sl, curl, cur, out, +fns, todo, frames, errs, flat, memo} = st
  K.fn.found(name, Env.find(fns, name), KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo})

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

# The C output: head (constructor ids and the runtime), the C files the
# program's effects import (spliced in by the driver), then the body.
type COut is Data:
  COut{head: String, effs: List<&2, String>, body: String, errs: List<&2, String>}

# Generates every def reachable from the queue. Fuel bounds the walk (the
# queue grows by each def's refs).
def Gen.all.go(n: Nat, +g: G, queue: List<&2, String>, +done: Set()) -> Gen(Unit):
  match n:
    case 0n:
      Gen.error("out of fuel")
    case 1n+ +fu:
      match queue:
        case Nil{}:
          Gen.pure(Unit, Unit{})
        case +h <> +t:
          Bool.pick(Unit -> Gen(Unit), Pair.snd(Set(), Bool, Set.has(done, h)),
            u => Gen.all.go(fu, g, t, done),
            u => do Gen<Unit>:
              Gen.def(g, h)
              refs : List<&2, String> <- Gen.take_refs()
              Gen.all.go(fu, g, List.append(&2, String, refs, t), Set.add(done, h)))(Unit{})

def Gen.all(+g: G, queue: List<&2, String>, done: Set()) -> Gen(Unit):
  Gen.all.go(Fuel.max(), g, queue, done)

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

# tcc ignores __attribute__((constructor)), which registers the effects
# (the official ABI's *_use functions): under tcc, main calls them first.
def Gen.ctors.call() -> String:
  "\n#ifdef __TINYC__\n  bend_ctors();\n#endif\n"

# An id, unless an earlier name took its spelling (a user's done{} beside
# Base's Done): the first keeps it, so Base's ids stay the runtime's.
def Gen.cids.def(+id: String, v: String) -> String:
  "#ifndef " ++ id ++ "\n#define " ++ id ++ " " ++ v ++ "\n#endif\n"

def Gen.cids.line(+name: String, kind: Nat, +tag: U32) -> String:
  match kind:
    case 0n:
      Gen.cids.def(Gen.cid(name), U32.show(tag) ++ "u")
    case 1n:
      Gen.cids.def(Gen.cid(name), "((1u << 16) | " ++ U32.show(tag) ++ "u)")
    case 2n:
      Gen.cids.def(Gen.cid(name), "((2u << 16) | " ++ U32.show(tag) ++ "u)")
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
      Gen.cids.def(Gen.cid(n), "((3u << 16) | " ++ U32.show(i) ++ "u)") ++
        Gen.cids(g, t, U32.inc(i))
    case d <> t:
      Gen.cids(g, t, i)

# Branches. Bend has no if, and a match takes only a parameter or a field,
# so a def that branches on a computed value and recurses in a branch needs
# a helper def, and the recursion then runs through a law. Written as
# Bool.pick(T, c, u => a, u => b)(x), the branches stay in the def (the
# termination check reads self-calls under lambdas), and here they become
# match c: case True{}: a; case False{}: b, with u = x: no closures.
def Pick.lam.is(+e: Expr) -> Bool:
  match e:
    case ELam{p, b}:
      True{}
    case other:
      False{}

def Pick.name(+f: Expr) -> Bool:
  match f:
    case EVar{+n}:
      Str.eq(n, "Bool.pick")
    case other:
      False{}

def Pick.args(+as: List<&2, Expr>) -> Bool:
  match as:
    case ty <> c <> a <> b <> Nil{}:
      Bool.and(Pick.lam.is(a), Pick.lam.is(b))
    case other:
      False{}

def Pick.lam(l: Expr, x: Expr) -> Expr:
  match l:
    case ELam{p, b}:
      ELet{p, x, b}
    case other:
      ECall{other, [x]}

def Pick.first(xs: List<&2, Expr>) -> Expr:
  match xs:
    case x <> t:
      x
    case Nil{}:
      EErr{"pick"}

def Pick.build(as: List<&2, Expr>, +x: Expr) -> Expr:
  match as:
    case ty <> c <> a <> b <> Nil{}:
      EMatch{[c], [ECase{[PCtor{"True", Nil{}}], Pick.lam(a, x)}, ECase{[PCtor{"False", Nil{}}], Pick.lam(b, x)}]}
    case other:
      ECall{EVar{"Bool.pick"}, other}

def Pick.one(+xs: List<&2, Expr>) -> Bool:
  Nat.is_eq(List.length(&2, Expr, xs), 1n)

def Pick.hit(hit: Bool, +g: Expr, +as: List<&2, Expr>, +xs: List<&2, Expr>) -> Expr:
  match hit:
    case True{}:
      Pick.build(as, Pick.first(xs))
    case False{}:
      ECall{ECall{g, as}, xs}

def Pick.call(f: Expr, +xs: List<&2, Expr>) -> Expr:
  match f:
    case ECall{+g, +as}:
      Pick.hit(Bool.and(Pick.name(g), Bool.and(Pick.args(as), Pick.one(xs))), g, as, xs)
    case other:
      ECall{other, xs}

# A call rebuilt from its parts, at the top of its node (top); below it,
# while its arguments are put back one by one, it stays as it is.
def Pick.top(top: Bool, r: Expr) -> Expr:
  match top:
    case True{}:
      match r:
        case ECall{f, xs}:
          Pick.call(f, xs)
        case other:
          other
    case False{}:
      r

def Pick.go(e: Expr, top: Bool) -> Expr:
  match e:
    case ECall{f, args}:
      match args:
        case Nil{}:
          Pick.top(top, ECall{Pick.go(f, True{}), Nil{}})
        case a <> t:
          Pick.top(top, Expr.push(Pick.go(a, True{}), Pick.go(ECall{f, t}, False{})))
    case ECtor{k, args}:
      match args:
        case Nil{}:
          ECtor{k, Nil{}}
        case a <> t:
          Expr.push(Pick.go(a, True{}), Pick.go(ECtor{k, t}, True{}))
    case EOp{op, a, b}:
      EOp{op, Pick.go(a, True{}), Pick.go(b, True{})}
    case ELam{p, b}:
      ELam{p, Pick.go(b, True{})}
    case ELet{p, v, b}:
      ELet{p, Pick.go(v, True{}), Pick.go(b, True{})}
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Pick.go(a, True{}), Pick.go(EMatch{t, cases}, True{}))
        case Nil{}:
          match cases:
            case Nil{}:
              EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Pick.go(c, True{}), Pick.go(EMatch{Nil{}, t}, True{}))
    case ECase{ps, b}:
      ECase{ps, Pick.go(b, True{})}
    case ESucc{k, x}:
      ESucc{k, Pick.go(x, True{})}
    case EAnn{x, ty}:
      EAnn{Pick.go(x, True{}), ty}
    case other:
      other

def Pick.expr(e: Expr) -> Expr:
  Pick.go(e, True{})

def Pick.decl(d: Decl) -> Decl:
  match d:
    case DDef{name, ps, body, ret}:
      DDef{name, ps, Pick.expr(body), ret}
    case other:
      other

def Pick.decls(ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Pick.decl(d) <> Pick.decls(t)

# Implicit parallelism (see Main.auto_par). Bend is pure, so the operands of
# one node (an operator's, a call's arguments, a constructor's fields) may
# run in any order; where two or more of them call back into the def (a
# tree recursion: fib(n - 1) + fib(n - 2), merge(msort(a), msort(b))),
# they become a parallel let, as if written a b = .. ..; the fork limit
# and a seq def's sequential clone then keep the small calls cheap. Only
# runtime operands move: a call's erased and dead arguments stay.

# Whether e names k anywhere (under lambdas too). A list field is its
# head, then the node rebuilt with the rest.
def Expr.mentions(e: Expr, +k: String) -> Bool:
  match e:
    case EVar{+n}:
      Str.eq(n, k)
    case ECall{f, args}:
      match args:
        case Nil{}:
          Expr.mentions(f, k)
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(ECall{f, t}, k))(Unit{})
    case ECtor{n, args}:
      match args:
        case Nil{}:
          False{}
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(ECtor{n, t}, k))(Unit{})
    case ELam{p, b}:
      Expr.mentions(b, k)
    case ELet{p, +v, +b}:
      Bool.pick(Unit -> Bool, Expr.mentions(v, k), u => True{}, u => Expr.mentions(b, k))(Unit{})
    case EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(EMatch{t, cases}, k))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case +c <> t:
              Bool.pick(Unit -> Bool, Expr.mentions(c, k), u => True{},
                u => Expr.mentions(EMatch{Nil{}, t}, k))(Unit{})
    case ECase{ps, b}:
      Expr.mentions(b, k)
    case ESucc{n, x}:
      Expr.mentions(x, k)
    case EOp{op, +a, +b}:
      Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(b, k))(Unit{})
    case EAnn{x, ty}:
      Expr.mentions(x, k)
    case other:
      False{}

def DInfo.kind(i: DInfo) -> U32:
  DInfo{kind, mask} = i
  kind

def Par.rec.body(d: Decl, +k: String) -> Bool:
  match d:
    case DDef{name, ps, body, ret}:
      Expr.mentions(body, k)
    case other:
      False{}

# Whether a call of f from d recurses: f is d, or a def that calls d (the
# helper a match on a computed value needs: msort.halves of msort).
def Par.rec(+g: G, +d: String, +f: String) -> Bool:
  Bool.or(Str.eq(f, d), Bool.and(U32.is_zero(DInfo.kind(G.def(g, f))), Par.rec.body(G.body(g, f), d)))

# Whether e runs a recursive call of d (outside lambdas: a lambda's body
# runs when it is called, not where it is built). A list field is its
# head, then the node rebuilt with the rest.
def Par.has(+g: G, +d: String, e: Expr) -> Bool:
  match e:
    case ECall{f, args}:
      match f:
        case EVar{+n}:
          match args:
            case Nil{}:
              Par.rec(g, d, n)
            case +a <> t:
              Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, ECall{EVar{n}, t}))(Unit{})
        case other:
          match args:
            case Nil{}:
              Par.has(g, d, other)
            case +a <> t:
              Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, ECall{other, t}))(Unit{})
    case ECtor{n, args}:
      match args:
        case Nil{}:
          False{}
        case +a <> t:
          Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, ECtor{n, t}))(Unit{})
    case ELet{p, +v, +b}:
      Bool.pick(Unit -> Bool, Par.has(g, d, v), u => True{}, u => Par.has(g, d, b))(Unit{})
    case EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, EMatch{t, cases}))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case +c <> t:
              Bool.pick(Unit -> Bool, Par.has(g, d, c), u => True{}, u => Par.has(g, d, EMatch{Nil{}, t}))(Unit{})
    case ECase{ps, b}:
      Par.has(g, d, b)
    case ESucc{n, x}:
      Par.has(g, d, x)
    case EOp{op, +a, +b}:
      Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, b))(Unit{})
    case EAnn{x, ty}:
      Par.has(g, d, x)
    case other:
      False{}

# The operands that may move: all of a closure's or a constructor's, a
# def's kept ones (and any past its parameters), none of a dead def's.
def Par.live.mask(xs: List<&2, Expr>, bs: List<&2, Bool>) -> List<&2, Bool>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      match bs:
        case Nil{}:
          True{} <> Par.live.mask(t, Nil{})
        case b <> mt:
          b <> Par.live.mask(t, mt)

def Par.all(+b: Bool, xs: List<&2, Expr>) -> List<&2, Bool>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      b <> Par.all(b, t)

def Par.live.info(i: DInfo, +xs: List<&2, Expr>) -> List<&2, Bool>:
  DInfo{+kind, mask} = i
  Bool.pick(List<&2, Bool>, U32.is_eq(kind, 3), Par.all(False{}, xs),
    Bool.pick(List<&2, Bool>, U32.is_eq(kind, 4), Par.all(True{}, xs), Par.live.mask(xs, mask)))

def Par.live(+g: G, f: Expr, +xs: List<&2, Expr>) -> List<&2, Bool>:
  match f:
    case EVar{+n}:
      Par.live.info(G.def(g, n), xs)
    case other:
      Par.all(True{}, xs)

# Which operands move: live ones that run a recursive call.
def Par.marks(+g: G, +d: String, live: List<&2, Bool>, xs: List<&2, Expr>) -> List<&2, Bool>:
  match live xs:
    case b <> lt +x <> xt:
      Bool.and(b, Par.has(g, d, x)) <> Par.marks(g, d, lt, xt)
    case l ys:
      Nil{}

def Par.count(ms: List<&2, Bool>) -> Nat:
  match ms:
    case Nil{}:
      0n
    case True{} <> t:
      1n+Par.count(t)
    case False{} <> t:
      Par.count(t)

def Par.name(+n: U32, +j: Nat) -> String:
  "_par" ++ U32.show(n) ++ "_" ++ Nat.show(j)

# The parallel let's names, values, and the operands left in place (a
# moved one is its name).
def Par.pats(ms: List<&2, Bool>, +n: U32, +j: Nat) -> List<&2, Pat>:
  match ms:
    case Nil{}:
      Nil{}
    case True{} <> t:
      PVar{Par.name(n, j)} <> Par.pats(t, n, 1n+j)
    case False{} <> t:
      Par.pats(t, n, j)

def Par.vals(ms: List<&2, Bool>, xs: List<&2, Expr>) -> List<&2, Expr>:
  match ms xs:
    case True{} <> mt x <> xt:
      x <> Par.vals(mt, xt)
    case False{} <> mt x <> xt:
      Par.vals(mt, xt)
    case q ys:
      Nil{}

def Par.rest(ms: List<&2, Bool>, xs: List<&2, Expr>, +n: U32, +j: Nat) -> List<&2, Expr>:
  match ms xs:
    case True{} <> mt x <> xt:
      EVar{Par.name(n, j)} <> Par.rest(mt, xt, n, 1n+j)
    case False{} <> mt x <> xt:
      x <> Par.rest(mt, xt, n, j)
    case q ys:
      ys

def Par.wrap.if(hit: Bool, +n: U32, +ms: List<&2, Bool>, +xs: List<&2, Expr>, k: List<&2, Expr> -> Expr) ->
  Expr:
  match hit:
    case True{}:
      ELet{PCtor{"%par", Par.pats(ms, n, 0n)}, ECtor{"%par", Par.vals(ms, xs)}, k(Par.rest(ms, xs, n, 0n))}
    case False{}:
      k(xs)

def Par.wrap(+n: U32, +ms: List<&2, Bool>, +xs: List<&2, Expr>, k: List<&2, Expr> -> Expr) -> Expr:
  Par.wrap.if(Nat.is_gt(Par.count(ms), 1n), n, ms, xs, k)

# An annotated operator's parallel let goes outside the annotation, which
# only types the operator: {(a + b : U32)} with a, b moved.
def Par.ann(x: Expr, +ty: String) -> Expr:
  match x:
    case ELet{PCtor{+k, +ps}, +v, +b}:
      Bool.pick(Expr, Str.eq(k, "%par"), ELet{PCtor{k, ps}, v, EAnn{b, ty}}, EAnn{ELet{PCtor{k, ps}, v, b}, ty})
    case other:
      EAnn{other, ty}

def Par.call(+g: G, +d: String, +n: U32, +f: Expr, +xs: List<&2, Expr>) -> Expr:
  Par.wrap(n, Par.marks(g, d, Par.live(g, f, xs), xs), xs, as => ECall{f, as})

def Par.ctor(+g: G, +d: String, +n: U32, +k: String, +xs: List<&2, Expr>) -> Expr:
  Bool.pick(Expr, Str.eq(k, "%par"), ECtor{k, xs},
    Par.wrap(n, Par.marks(g, d, Par.all(True{}, xs), xs), xs, as => ECtor{k, as}))

def Par.op.k(+op: String, xs: List<&2, Expr>) -> Expr:
  match xs:
    case a <> b <> Nil{}:
      EOp{op, a, b}
    case other:
      EErr{"auto-par: an operator of two operands"}

def Par.op(+g: G, +d: String, +n: U32, +op: String, a: Expr, b: Expr) -> Expr:
  +xs = {[a, b] : List<&2, Expr>}
  Par.wrap(n, Par.marks(g, d, Par.all(True{}, xs), xs), xs, as => Par.op.k(op, as))

# A call or a constructor rebuilt from its parts: grouped at the top of
# its node (top); below it, while its operands are put back one by one, it
# stays as it is.
def Par.top(top: Bool, +g: G, +d: String, +n: U32, r: Expr) -> Expr:
  match top:
    case True{}:
      match r:
        case ECall{+f, +xs}:
          Par.call(g, d, n, f, xs)
        case ECtor{+k, +xs}:
          Par.ctor(g, d, n, k, xs)
        case other:
          other
    case False{}:
      r

# e with its recursive operand groups parallel (n: the nesting depth, which
# keeps the names of nested groups apart).
def Par.go(+g: G, +d: String, e: Expr, +n: U32, top: Bool) -> Expr:
  match e:
    case ECall{f, args}:
      match args:
        case Nil{}:
          Par.top(top, g, d, n, ECall{Par.go(g, d, f, U32.inc(n), True{}), Nil{}})
        case a <> t:
          Par.top(top, g, d, n, Expr.push(Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, ECall{f, t}, n, False{})))
    case ECtor{k, args}:
      match args:
        case Nil{}:
          Par.top(top, g, d, n, ECtor{k, Nil{}})
        case a <> t:
          Par.top(top, g, d, n, Expr.push(Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, ECtor{k, t}, n, False{})))
    case EOp{op, a, b}:
      Par.op(g, d, n, op, Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, b, U32.inc(n), True{}))
    case ELam{p, b}:
      ELam{p, Par.go(g, d, b, U32.inc(n), True{})}
    case ELet{p, v, b}:
      ELet{p, Par.go(g, d, v, U32.inc(n), True{}), Par.go(g, d, b, U32.inc(n), True{})}
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, EMatch{t, cases}, n, True{}))
        case Nil{}:
          match cases:
            case Nil{}:
              EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Par.go(g, d, c, U32.inc(n), True{}), Par.go(g, d, EMatch{Nil{}, t}, n, True{}))
    case ECase{ps, b}:
      ECase{ps, Par.go(g, d, b, U32.inc(n), True{})}
    case ESucc{k, x}:
      ESucc{k, Par.go(g, d, x, U32.inc(n), True{})}
    case EAnn{x, ty}:
      Par.ann(Par.go(g, d, x, U32.inc(n), True{}), ty)
    case other:
      other

def Par.expr(+g: G, +d: String, +n: U32, e: Expr) -> Expr:
  Par.go(g, d, e, n, True{})

def Par.decl(+g: G, d: Decl) -> Decl:
  match d:
    case DDef{+name, ps, body, ret}:
      DDef{name, ps, Par.expr(g, name, 0, body), ret}
    case other:
      other

def Par.decls(+g: G, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Par.decl(g, d) <> Par.decls(g, t)

def Par.auto(on: Bool, +ds: List<&2, Decl>) -> List<&2, Decl>:
  match on:
    case True{}:
      Par.decls(G.new(ds), ds)
    case False{}:
      ds

# Destination-passing. merge(x <> xt, ys) = x <> merge(xt, ys) builds its
# result around a call to itself: compiled directly, each element costs a C
# stack frame, so merging a million elements takes a million frames. Such
# defs get a D_ function that stores its result through a pointer, dst: for
# C(.., f(..), ..) with f in the group, it stores the node with a hole where
# f's result goes, points dst at the hole and jumps to f. A group is a
# strongly connected set of defs under tail calls (C(.., f(..), ..) counts
# as one), with at least one such constructor on a cycle. Its D_ functions
# share one C signature, so the jumps between them are guaranteed tail calls
# (BEND_MUSTTAIL). The collector rescans a node whose hole was open at the
# last collection (see gc_rem in bendrt.h): the one kind of write to an
# existing node.
type DEdge is Data:
  DEdge{to: String, ctor: Bool}

def Dps.add(ok: Bool, +name: String, es: List<&2, DEdge>, m: Map<&2, List<&2, DEdge>>) ->
  Map<&2, List<&2, DEdge>>:
  match ok es:
    case True{} +e <> t:
      Map.set(&2, List<&2, DEdge>, m, name, e <> t)
    case o l:
      m

def Dps.kind(i: DInfo) -> U32:
  DInfo{kind, mask} = i
  kind

def Dps.plain(+g: G, +name: String) -> Bool:
  U32.is_zero(Dps.kind(G.def(g, name)))

def Dps.out(+em: Map<&2, List<&2, DEdge>>, +name: String) -> List<&2, DEdge>:
  G.get(List<&2, DEdge>, Nil{}, em, name)

def Dps.rev.add(+from: String, es: List<&2, DEdge>, +m: Map<&2, List<&2, DEdge>>) ->
  Map<&2, List<&2, DEdge>>:
  match es:
    case Nil{}:
      m
    case DEdge{+to, c} <> t:
      Dps.rev.add(from, t, Map.set(&2, List<&2, DEdge>, m, to,
        DEdge{from, c} <> G.get(List<&2, DEdge>, Nil{}, m, to)))

# The reversed graph: for each def, the defs with an edge to it.
def Dps.rev(ks: List<&2, String>, +em: Map<&2, List<&2, DEdge>>, m: Map<&2, List<&2, DEdge>>) ->
  Map<&2, List<&2, DEdge>>:
  match ks:
    case Nil{}:
      m
    case +k <> t:
      Dps.rev(t, em, Dps.rev.add(k, Dps.out(em, k), m))

def Dps.target.info(i: DInfo, +k: Nat) -> Bool:
  DInfo{kind, mask} = i
  Bool.and(U32.is_zero(kind), Nat.is_eq(List.length(&2, Bool, mask), k))

# Whether a call of name with args is a full call of a plain def.
def Dps.target(+g: G, +name: String, +args: List<&2, Expr>) -> Bool:
  Dps.target.info(G.def(g, name), List.length(&2, Expr, args))

def Dps.edge(ok: Bool, +to: String, ctor: Bool, acc: List<&2, DEdge>) -> List<&2, DEdge>:
  match ok:
    case True{}:
      DEdge{to, ctor} <> acc
    case False{}:
      acc

def Dps.ctor(+g: G, node: Bool, as: List<&2, Expr>, acc: List<&2, DEdge>) -> List<&2, DEdge>:
  match node as:
    case True{} ECall{EVar{+h}, +hargs} <> t:
      Dps.ctor(g, True{}, t, Dps.edge(Dps.target(g, h, hargs), h, True{}, acc))
    case True{} a <> t:
      Dps.ctor(g, True{}, t, acc)
    case n l:
      acc

# The tail calls of an expression, as Gen.stmt compiles it (a match's:
# its first case's, then the match rebuilt with the other cases).
def Dps.tails(+g: G, e: Expr, acc: List<&2, DEdge>) -> List<&2, DEdge>:
  match e:
    case ELet{p, v, b}:
      Dps.tails(g, b, acc)
    case EMatch{scrs, cases}:
      match cases:
        case Nil{}:
          acc
        case ECase{ps, b} <> t:
          Dps.tails(g, EMatch{scrs, t}, Dps.tails(g, b, acc))
        case other <> t:
          Dps.tails(g, EMatch{scrs, t}, acc)
    case ECall{EVar{+name}, +args}:
      Dps.edge(Dps.target(g, name, args), name, False{}, acc)
    case ECtor{+name, args}:
      Dps.ctor(g, Gen.dst.node(G.ctor(g, name)), args, acc)
    case other:
      acc

def Dps.has(+s: Set(), +k: String) -> Bool:
  Pair.snd(Set(), Bool, Set.has(s, k))

def Dps.tos(es: List<&2, DEdge>, acc: List<&2, String>) -> List<&2, String>:
  match es:
    case Nil{}:
      acc
    case DEdge{to, c} <> t:
      Dps.tos(t, to <> acc)

# The defs reachable from the queue (the queue's included). Fuel bounds
# the walk; out of it, the set holds a name no def has.
def Dps.reach.go(n: Nat, +em: Map<&2, List<&2, DEdge>>, todo: List<&2, String>, +seen: Set()) -> Set():
  match n:
    case 0n:
      Set.add(seen, "%out of fuel")
    case 1n+ +p:
      match todo:
        case Nil{}:
          seen
        case +h <> +t:
          Bool.pick(Unit -> Set(), Dps.has(seen, h), u => Dps.reach.go(p, em, t, seen),
            u => Dps.reach.go(p, em, Dps.tos(Dps.out(em, h), t), Set.add(seen, h)))(Unit{})

def Dps.reach(+em: Map<&2, List<&2, DEdge>>, todo: List<&2, String>, +seen: Set()) -> Set():
  Dps.reach.go(Fuel.max(), em, todo, seen)

def Dps.both.if(keep: Bool, x: String, rest: List<&2, String>) -> List<&2, String>:
  match keep:
    case True{}:
      x <> rest
    case False{}:
      rest

def Dps.both(xs: List<&2, String>, +s: Set()) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case +x <> t:
      Dps.both.if(Dps.has(s, x), x, Dps.both(t, s))

def Dps.inner(es: List<&2, DEdge>, +s: Set()) -> Bool:
  match es:
    case Nil{}:
      False{}
    case DEdge{+to, c} <> t:
      Bool.or(Bool.and(c, Dps.has(s, to)), Dps.inner(t, s))

# Whether a group has a constructor edge between two of its members.
def Dps.ctors(ms: List<&2, String>, +em: Map<&2, List<&2, DEdge>>, +s: Set()) -> Bool:
  match ms:
    case Nil{}:
      False{}
    case +m <> t:
      Bool.or(Dps.inner(Dps.out(em, m), s), Dps.ctors(t, em, s))

def Dps.kept(ms: List<&2, Bool>) -> U32:
  match ms:
    case Nil{}:
      0
    case True{} <> t:
      U32.inc(Dps.kept(t))
    case False{} <> t:
      Dps.kept(t)

def Dps.arity(+g: G, ms: List<&2, String>) -> U32:
  match ms:
    case Nil{}:
      0
    case +m <> t:
      U32.max(Dps.kept(DInfo.mask(G.def(g, m))), Dps.arity(g, t))

def Dps.put(ms: List<&2, String>, +d: DGrp, m: Map<&2, DGrp>) -> Map<&2, DGrp>:
  match ms:
    case Nil{}:
      m
    case +k <> t:
      Dps.put(t, d, Map.set(&2, DGrp, m, k, d))

def Dps.group.put(ok: Bool, +g: G, +name: String, +ms: List<&2, String>, m: Map<&2, DGrp>) ->
  Map<&2, DGrp>:
  match ok:
    case True{}:
      Dps.put(ms, DGrp{name, Dps.arity(g, ms)}, m)
    case False{}:
      m

def Dps.group.fin(+g: G, +em: Map<&2, List<&2, DEdge>>, +name: String, +ms: List<&2, String>,
  m: Map<&2, DGrp>
) -> Map<&2, DGrp>:
  +s = Set.from_list(ms)
  Dps.group.put(Dps.ctors(ms, em, s), g, name, ms, m)

def Dps.group.cyc(cyc: Bool, +g: G, +em: Map<&2, List<&2, DEdge>>, +rv: Map<&2, List<&2, DEdge>>,
  +name: String, +fwd: Set(), m: Map<&2, DGrp>
) -> Map<&2, DGrp>:
  match cyc:
    case True{}:
      Dps.group.fin(g, em, name,
        Dps.both(Set.to_list(Dps.reach(rv, Dps.tos(Dps.out(rv, name), Nil{}), Set.new())), fwd), m)
    case False{}:
      m

# name's group: what it reaches that reaches it back.
def Dps.group(+g: G, +em: Map<&2, List<&2, DEdge>>, +rv: Map<&2, List<&2, DEdge>>, +name: String,
  m: Map<&2, DGrp>
) -> Map<&2, DGrp>:
  +fwd = Dps.reach(em, Dps.tos(Dps.out(em, name), Nil{}), Set.new())
  Dps.group.cyc(Dps.has(fwd, name), g, em, rv, name, fwd, m)

def Dps.has_ctor(es: List<&2, DEdge>) -> Bool:
  match es:
    case Nil{}:
      False{}
    case DEdge{t, c} <> r:
      Bool.or(c, Dps.has_ctor(r))

def Dps.in(+m: Map<&2, DGrp>, +k: String) -> Bool:
  Pair.snd(Map<&2, DGrp>, Bool, Map.has(&2, DGrp, m, k))

# Each def with a constructor edge that is in no group yet starts one.
def Dps.groups(+g: G, ks: List<&2, String>, +em: Map<&2, List<&2, DEdge>>,
  +rv: Map<&2, List<&2, DEdge>>, +m: Map<&2, DGrp>
) -> Map<&2, DGrp>:
  match ks:
    case Nil{}:
      m
    case +k <> +t:
      Bool.pick(Unit -> Map<&2, DGrp>, Bool.and(Dps.has_ctor(Dps.out(em, k)), Bool.not(Dps.in(m, k))),
        u => Dps.groups(g, t, em, rv, Dps.group(g, em, rv, k, m)), u => Dps.groups(g, t, em, rv, m))(Unit{})

# The tail-call edges of every plain def without parallel lets.
def Dps.edges(+g: G, ds: List<&2, Decl>, m: Map<&2, List<&2, DEdge>>) -> Map<&2, List<&2, DEdge>>:
  match ds:
    case Nil{}:
      m
    case DDef{+name, ps, +body, ret} <> t:
      Dps.edges(g, t, Dps.add(Bool.and(Dps.plain(g, name), Bool.not(Expr.has_par(body))), name,
        Dps.tails(g, R.ops(body, "Nat"), Nil{}), m))
    case d <> t:
      Dps.edges(g, t, m)

def Dps.build(+g: G, +ds: List<&2, Decl>, free: Bool) -> G:
  +em = Dps.edges(g, ds, MTip{})
  +ks = Map.keys(&2, List<&2, DEdge>, em)
  G.with_dps(g, Map.set(&2, DGrp, Dps.groups(g, ks, em, Dps.rev(ks, em, MTip{}), MTip{}), "%free",
    DGrp{Bool.pick(String, free, "1", "0"), 0}))

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

# A type alias unfolded (law Entry: Type; def Entry(): Program(Unit) is
# IO(Unit)): a def of Type whose body is a type, not a match on its
# arguments, stands for its body. The printers' own heads stay.
def Ty.norm.stop(+h: String) -> Bool:
  List.contains(~String, ~String.eq, ["IO", "U32", "Nat", "F32", "Char", "String", "List",
    "&", "->", "Array", "==", "Sigma", "Bool", "Type", "", "?"], h)

def Ty.pnames(ps: List<&2, Param>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case Param{n, m, t} <> rest:
      n <> Ty.pnames(rest)

def Ty.norm.body(b: Expr) -> Bool:
  match b:
    case ETy{n, a}:
      True{}
    case EVar{n}:
      True{}
    case ECall{EVar{n}, a}:
      True{}
    case EMatch{xs, cs}:
      True{}
    case other:
      False{}

def Ty.find(sub: List<&2, TB>, +x: String) -> Maybe<&2, Expr>:
  match sub:
    case Nil{}:
      None{}
    case TB{+n, t} <> rest:
      Bool.pick(Unit -> Maybe<&2, Expr>, String.eq(n, x), u => Some{t}, u => Ty.find(rest, x))(Unit{})

def Ty.unbind.add(b: TB, acc: List<&2, TB>, skip: Bool) -> List<&2, TB>:
  match skip:
    case True{}:
      acc
    case False{}:
      b <> acc

# The binds a pattern's variables do not shadow.
def Ty.unbind(sub: List<&2, TB>, +xs: List<&2, String>) -> List<&2, TB>:
  match sub:
    case Nil{}:
      Nil{}
    case TB{+n, t} <> rest:
      Ty.unbind.add(TB{n, t}, Ty.unbind(rest, xs), Str.has(xs, n))

def Ty.subst(e: Expr, +sub: List<&2, TB>) -> Expr:
  match e:
    case EVar{+n}:
      Maybe.default(&2, Expr, Ty.find(sub, n), EVar{n})
    case ETy{n, args}:
      match args:
        case Nil{}:
          ETy{n, Nil{}}
        case a <> t:
          Expr.push(Ty.subst(a, sub), Ty.subst(ETy{n, t}, sub))
    case ECall{f, args}:
      match args:
        case Nil{}:
          ECall{f, Nil{}}
        case a <> t:
          Expr.push(Ty.subst(a, sub), Ty.subst(ECall{f, t}, sub))
    case ELam{p, b}:
      ELam{p, Ty.subst(b, sub)}
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Ty.subst(a, sub), Ty.subst(EMatch{t, cases}, sub))
        case Nil{}:
          match cases:
            case Nil{}:
              EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Ty.subst(c, sub), Ty.subst(EMatch{Nil{}, t}, sub))
    case ECase{+ps, b}:
      ECase{ps, Ty.subst(b, Ty.unbind(sub, Pats.vars(ps, Nil{})))}
    case other:
      other

# Type-level matches
# A pattern against a type argument: k 0 when it fails, 1 when it holds
# (with its binds), 2 when the argument is no value yet (a variable).
type PM is Data:
  PM{k: Nat, binds: List<&2, TB>}

def Ty.pm.k(a: Nat, +b: Nat) -> Nat:
  match a:
    case 0n:
      0n
    case 1n:
      b
    case 2n+p:
      Bool.pick(Nat, Nat.is_eq(b, 0n), 0n, 2n)

def Ty.pm.both(a: PM, b: PM) -> PM:
  PM{ka, ba} = a
  PM{kb, bb} = b
  PM{Ty.pm.k(ka, kb), List.append(&2, TB, ba, bb)}

def Ty.pm.is(c: Bool) -> PM:
  PM{Bool.pick(Nat, c, 1n, 0n), Nil{}}

def Ty.pm.nat(+n: U32, e: Expr) -> PM:
  match e:
    case ENat{+m}:
      Ty.pm.is(U32.is_eq(n, m))
    case ESucc{+k, x}:
      Bool.pick(PM, U32.is_lt(n, k), PM{0n, Nil{}}, PM{2n, Nil{}})
    case other:
      PM{2n, Nil{}}

def Ty.pm.num(+n: U32, e: Expr) -> PM:
  match e:
    case ENum{+m}:
      Ty.pm.is(U32.is_eq(n, m))
    case other:
      PM{2n, Nil{}}

# A constructor's result from its fields' r: with the test of its name, or
# r alone for the rest of the fields (lst).
def Ty.pm.at(lst: Bool, +n: String, +m: String, r: PM) -> PM:
  match lst:
    case True{}:
      r
    case False{}:
      Ty.pm.both(Ty.pm.is(Str.eq(n, m)), r)

# With lst, p is PCtor{n, ps}, e is ECtor{m, es}, and the result is that of
# ps against es alone.
def Ty.pm.go(p: Pat, e: Expr, lst: Bool) -> PM:
  match p:
    case PVar{+x}:
      PM{1n, Bool.pick(List<&2, TB>, Str.eq(x, "_"), Nil{}, [TB{x, e}])}
    case PCtor{+n, ps}:
      match ps:
        case q <> pt:
          match e:
            case ECtor{+m, es}:
              match es:
                case x <> et:
                  Ty.pm.at(lst, n, m,
                    Ty.pm.both(Ty.pm.go(q, x, False{}), Ty.pm.go(PCtor{n, pt}, ECtor{m, et}, True{})))
                case Nil{}:
                  Ty.pm.at(lst, n, m, PM{0n, Nil{}})
            case other:
              PM{2n, Nil{}}
        case Nil{}:
          match e:
            case ECtor{+m, es}:
              match es:
                case Nil{}:
                  Ty.pm.at(lst, n, m, PM{1n, Nil{}})
                case x <> et:
                  Ty.pm.at(lst, n, m, PM{0n, Nil{}})
            case other:
              PM{2n, Nil{}}
    case PNat{+n}:
      Ty.pm.nat(n, e)
    case PSucc{+k, q}:
      match e:
        case ENat{+m}:
          Bool.pick(Unit -> PM, U32.is_ge(m, k), u => Ty.pm.go(q, ENat{(m - k : U32)}, False{}),
            u => PM{0n, Nil{}})(Unit{})
        case ESucc{+j, x}:
          Bool.pick(Unit -> PM, U32.is_eq(j, k), u => Ty.pm.go(q, x, False{}),
            u => PM{2n, Nil{}})(Unit{})
        case other:
          PM{2n, Nil{}}
    case PNum{+n}:
      Ty.pm.num(n, e)
    case PFlt{s}:
      PM{2n, Nil{}}

def Ty.pm(p: Pat, e: Expr) -> PM:
  Ty.pm.go(p, e, False{})

def Ty.pms(ps: List<&2, Pat>, es: List<&2, Expr>) -> PM:
  Ty.pm.go(PCtor{"", ps}, ECtor{"", es}, True{})

# A type no value has (a datatype without constructors, Empty).
def Ty.void.d(d: Decl) -> Bool:
  match d:
    case DType{n, ps, Nil{}}:
      True{}
    case other:
      False{}

def Ty.void(+g: G, +t: Expr) -> Bool:
  Ty.void.d(G.body(g, "%" ++ Ty.head(t)))

def Ty.shows(xs: List<&2, Expr>) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case +h <> t:
      Expr.show(h) <> Ty.shows(t)

def Ty.pick.add(h: Expr, acc: List<&2, Expr>, skip: Bool) -> List<&2, Expr>:
  match skip:
    case True{}:
      acc
    case False{}:
      h <> acc

def Ty.pick.go(+g: G, xs: List<&2, Expr>, +acc: List<&2, Expr>) -> List<&2, Expr>:
  match xs:
    case Nil{}:
      acc
    case +h <> t:
      Ty.pick.go(g, t, Ty.pick.add(h, acc,
        Bool.or(Ty.void(g, h), Str.has(Ty.shows(acc), Expr.show(h)))))

def Ty.pick.first(all: List<&2, Expr>) -> Expr:
  match all:
    case h <> t:
      h
    case Nil{}:
      ETy{"?", Nil{}}

def Ty.pick.one(xs: List<&2, Expr>, all: List<&2, Expr>) -> Expr:
  match xs:
    case h <> Nil{}:
      h
    case Nil{}:
      Ty.pick.first(all)
    case other:
      ETy{"?", Nil{}}

# A match on a value the type does not know yet stands for the one
# inhabited type its arms can give (LE(r, 1n) is Unit, as its other
# arm is Empty); with none or more than one it prints ?.
def Ty.pick(+g: G, +xs: List<&2, Expr>) -> Expr:
  Ty.pick.one(Ty.pick.go(g, xs, Nil{}), xs)

# Type normalization is one def, Ty.rec, over a selector: each TS.. names
# one of its steps and carries that step's arguments; TSel.ty is the step's
# result. Fuel bounds the recursion (a def's body after substitution is no
# smaller); the steps' own fuel bounds how often a def unfolds.
type TSel is Data:
  TSNorm{ty: Expr, fuel: Nat}
  TSAt{ty: Expr, h: String, fuel: Nat, stop: Bool}
  TSDef{ty: Expr, d: Decl, fuel: Nat}
  TSGo{ty: Expr, ps: List<&2, Param>, b: Expr, fuel: Nat, ok: Bool}
  TSDeep{ty: Expr, fuel: Nat}
  TSNorms{xs: List<&2, Expr>, fuel: Nat}
  TSCands{scrs: List<&2, Expr>, cases: List<&2, Expr>, fuel: Nat}
  TSCandsAt{scrs: List<&2, Expr>, b: Expr, t: List<&2, Expr>, fuel: Nat, m: PM}

def TSel.ty(k: TSel) -> Type:
  match k:
    case TSNorms{xs, fuel}:
      List<&2, Expr>
    case TSCands{scrs, cases, fuel}:
      List<&2, Expr>
    case TSCandsAt{scrs, b, t, fuel, m}:
      List<&2, Expr>
    case other:
      Expr

# Out of fuel: a value of the step's type.
def TSel.none(k: TSel) -> TSel.ty(k):
  match k:
    case TSNorm{ty, fuel}:
      ETy{"%out of fuel", Nil{}}
    case TSAt{ty, h, fuel, stop}:
      ETy{"%out of fuel", Nil{}}
    case TSDef{ty, d, fuel}:
      ETy{"%out of fuel", Nil{}}
    case TSGo{ty, ps, b, fuel, ok}:
      ETy{"%out of fuel", Nil{}}
    case TSDeep{ty, fuel}:
      ETy{"%out of fuel", Nil{}}
    case TSNorms{xs, fuel}:
      Nil{}
    case TSCands{scrs, cases, fuel}:
      Nil{}
    case TSCandsAt{scrs, b, t, fuel, m}:
      Nil{}

def Ty.rec(n: Nat, +g: G, k: TSel) -> TSel.ty(k):
  match n:
    case 0n:
      TSel.none(k)
    case 1n+ +fu:
      match k:
        case TSNorm{+ty, fuel}:
          match fuel:
            case 0n:
              ty
            case 1n+p:
              +h = Ty.head(ty)
              Ty.rec(fu, g, TSAt{ty, h, p, Ty.norm.stop(h)})
        case TSAt{+ty, +h, fuel, stop}:
          match stop:
            case True{}:
              Ty.rec(fu, g, TSDeep{ty, 1n+fuel})
            case False{}:
              Ty.rec(fu, g, TSDef{ty, G.body(g, h), fuel})
        case TSDef{+ty, d, fuel}:
          match d:
            case DDef{n, ps, +b, +ret}:
              Ty.rec(fu, g, TSGo{ty, ps, b, fuel,
                Bool.and(Str.has(["Type", "Data"], Ty.head(ret)), Ty.norm.body(b))})
            case other:
              ty
        case TSGo{ty, ps, b, fuel, ok}:
          match ok:
            case True{}:
              Ty.rec(fu, g, TSNorm{Ty.subst(b, Ty.bind(Ty.pnames(ps), Ty.args(ty))), fuel})
            case False{}:
              ty
        # Below a head that stays, its arguments normalize too (a Pair
        # nested in a Pair prints flat).
        case TSDeep{ty, +fuel}:
          match ty:
            case ETy{n, args}:
              ETy{n, Ty.rec(fu, g, TSNorms{args, fuel})}
            case ECall{f, args}:
              ECall{f, Ty.rec(fu, g, TSNorms{args, fuel})}
            case ELam{p, b}:
              ELam{p, Ty.rec(fu, g, TSNorm{b, fuel})}
            case EMatch{scrs, cases}:
              Ty.pick(g, Ty.rec(fu, g, TSCands{scrs, cases, fuel}))
            case other:
              other
        case TSNorms{xs, +fuel}:
          match xs:
            case Nil{}:
              Nil{}
            case h <> t:
              Ty.rec(fu, g, TSNorm{h, fuel}) <> Ty.rec(fu, g, TSNorms{t, fuel})
        case TSCands{+scrs, cases, +fuel}:
          match cases:
            case Nil{}:
              Nil{}
            case ECase{ps, b} <> t:
              Ty.rec(fu, g, TSCandsAt{scrs, b, t, fuel, Ty.pms(ps, scrs)})
            case other <> t:
              Ty.rec(fu, g, TSCands{scrs, t, fuel})
        # The types a match's arms can give: the first arm whose patterns
        # hold, after arms that wait on a variable (each of which may be it).
        case TSCandsAt{+scrs, b, t, +fuel, m}:
          PM{k, binds} = m
          match k:
            case 0n:
              Ty.rec(fu, g, TSCands{scrs, t, fuel})
            case 1n:
              [Ty.rec(fu, g, TSNorm{Ty.subst(b, binds), fuel})]
            case 2n+p:
              Ty.rec(fu, g, TSNorm{Ty.subst(b, binds), fuel}) <> Ty.rec(fu, g, TSCands{scrs, t, fuel})

def Ty.norm(+g: G, +ty: Expr, fuel: Nat) -> Expr:
  Ty.rec(Fuel.max(), g, TSNorm{ty, fuel})

def Gen.printer.test(+kind: U32, +tag: U32, single: Bool) -> String:
  Bool.pick(String, single, "if (1)",
    Bool.pick(String, U32.is_eq(kind, 1), "if (v == IMM(" ++ U32.show(tag) ++ "))",
      "if (!(v & 1) && TAG(v) == " ++ U32.show(tag) ++ ")"))

# A dependent pair prints as a pair.
def Ty.alias(+h: String) -> String:
  Bool.pick(String, Str.eq(h, "Sigma"), "&", h)

# Components of a (right-nested) pair type.
def Ty.tuple(e: Expr) -> List<&2, Expr>:
  match e:
    case ETy{+n, args}:
      match args:
        case +a <> +b <> Nil{}:
          Bool.pick(Unit -> List<&2, Expr>, Str.eq(n, "&"), u => a <> Ty.tuple(b),
            u => [ETy{n, [a, b]}])(Unit{})
        case +a <> +b <> +x <> f <> fs:
          match f:
            case ELam{+p, +bd}:
              match fs:
                case Nil{}:
                  Bool.pick(Unit -> List<&2, Expr>, Str.eq(n, "Sigma"), u => x <> Ty.tuple(bd),
                    u => [ETy{n, [a, b, x, ELam{p, bd}]}])(Unit{})
                case other:
                  [ETy{n, a <> b <> x <> ELam{p, bd} <> other}]
            case +g:
              match fs:
                case Nil{}:
                  Bool.pick(Unit -> List<&2, Expr>, Str.eq(n, "Sigma"), u => x <> Ty.tuple(g),
                    u => [ETy{n, [a, b, x, g]}])(Unit{})
                case other:
                  [ETy{n, a <> b <> x <> g <> other}]
        case other:
          [ETy{n, other}]
    case other:
      [other]

# The value printers are one def, Gen.printer.rec, over a selector: each
# PS.. names one of its steps and carries that step's arguments; PSel.ty is
# the step's result. Fuel bounds the recursion (a type's fields are no
# smaller than the type).
type PSel is Data:
  PSPrinter{ty0: Expr}
  PSTuple{xs: List<&2, Expr>, path: String}
  PSFields{sub: List<&2, TB>, fs: List<&2, Field>, path: String, i: U32}
  PSCtor{sub: List<&2, TB>, name: String, fields: List<&2, Field>, info: Maybe<&2, CInfo>}
  PSCtors{sub: List<&2, TB>, cs: List<&2, Ctor>}
  PSAdt{ty: Expr, d: Decl}
  PSHead{ty: Expr, k: Nat}
  PSBody{ty: Expr, h: String}
  PSMemo{ty: Expr, key: String, m: Maybe<&2, String>}

def PSel.ty(k: PSel) -> Type:
  match k:
    case PSPrinter{ty0}:
      String
    case PSMemo{ty, key, m}:
      String
    case other:
      Doc

def PSel.none(k: PSel) -> PSel.ty(k):
  match k:
    case PSPrinter{ty0}:
      ""
    case PSTuple{xs, path}:
      DNil{}
    case PSFields{sub, fs, path, i}:
      DNil{}
    case PSCtor{sub, name, fields, info}:
      DNil{}
    case PSCtors{sub, cs}:
      DNil{}
    case PSAdt{ty, d}:
      DNil{}
    case PSHead{ty, k}:
      DNil{}
    case PSBody{ty, h}:
      DNil{}
    case PSMemo{ty, key, m}:
      ""

# Out of fuel: an error, and a value of the step's type.
def PSel.starve(k: PSel) -> Gen(PSel.ty(k)):
  do Gen<PSel.ty(k)>:
    Gen.error("out of fuel")
    return PSel.none(k)

# An array prints its cells in order, as a list.
def Gen.printer.arr(+e: String, leaf: Maybe<&2, CInfo>) -> String:
  match leaf:
    case Some{CInfo{+tag, ar, +kind, +single}}:
      "pr_s(\"[\");\nfor (size_t i = 0, n = (size_t)1 << arr_cls(v); i < n; i++) { if (i) pr_s(\", \"); " ++
        e ++ "(arr_cells(v)[i]); }\npr_s(\"]\");\n"
    case None{}:
      "(void)v; pr_s(\"[]\");\n"

def Gen.printer.rec(n: Nat, +g: G, s: PSel) -> Gen(PSel.ty(s)):
  match n:
    case 0n:
      PSel.starve(s)
    case 1n+ +fu:
      match s:
        case PSPrinter{ty0}:
          +ty = Ty.norm(g, ty0, 16n)
          +key = Expr.show(ty)
          do Gen<String>:
            m : Maybe<&2, String> <- Gen.memo.find(key)
            Gen.printer.rec(fu, g, PSMemo{ty, key, m})
        case PSTuple{xs, +path}:
          match xs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case h <> Nil{}:
              do Gen<Doc>:
                f : String <- Gen.printer.rec(fu, g, PSPrinter{h})
                return DStr{f ++ "(" ++ path ++ ");\n"}
            case h <> t:
              do Gen<Doc>:
                f : String <- Gen.printer.rec(fu, g, PSPrinter{h})
                rest : Doc <- Gen.printer.rec(fu, g, PSTuple{t, "FLD(" ++ path ++ ", 1)"})
                return Doc.list([DStr{f ++ "(FLD(" ++ path ++ ", 0));\npr_s(\", \");\n"}, rest])
        case PSFields{+sub, fs, +path, +i}:
          match fs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case Field{n, t} <> rest:
              do Gen<Doc>:
                f : String <- Gen.printer.rec(fu, g, PSPrinter{Ty.subst(t, sub)})
                more : Doc <- Gen.printer.rec(fu, g, PSFields{sub, rest, path, U32.inc(i)})
                return Doc.list([DStr{Bool.pick(String, U32.is_zero(i), "", "pr_s(\", \");\n") ++ f ++
                  "(" ++ Bool.pick(String, Str.eq(path, "v"), "v", path ++ U32.show(i) ++ ")") ++
                  ");\n"}, more])
        case PSCtor{+sub, +name, fields, info}:
          match info:
            case None{}:
              Gen.pure(Doc, DNil{})
            case Some{CInfo{+tag, ar, +kind, +single}}:
              do Gen<Doc>:
                fs : Doc <- Gen.printer.rec(fu, g, PSFields{sub, fields,
                  Bool.pick(String, U32.is_eq(kind, 2), "v", "FLD(v, "), 0})
                return Doc.list([DStr{Gen.printer.test(kind, tag, single) ++ " { pr_s(\"" ++ name ++
                  "{\");\n"}, fs, DStr{"pr_s(\"}\"); return; }\n"}])
        case PSCtors{+sub, cs}:
          match cs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case Ctor{+name, fields} <> t:
              do Gen<Doc>:
                one : Doc <- Gen.printer.rec(fu, g, PSCtor{sub, name, fields, G.ctor(g, name)})
                rest : Doc <- Gen.printer.rec(fu, g, PSCtors{sub, t})
                return Doc.list([one, rest])
        case PSAdt{+ty, d}:
          match d:
            case DType{name, ps, cs}:
              do Gen<Doc>:
                b : Doc <- Gen.printer.rec(fu, g, PSCtors{Ty.bind(ps, Ty.args(ty)), cs})
                return Doc.list([b, DStr{"pr_s(\"?\");\n"}])
            case other:
              Gen.pure(Doc, DStr{"(void)v; pr_s(\"?\");\n"})
        case PSHead{+ty, k}:
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
                e : String <- Gen.printer.rec(fu, g, PSPrinter{P.last(Ty.args(ty))})
                return DStr{"pr_s(\"[\");\nfor (int i = 0; TAG(v) == 1; i++) { if (i) pr_s(\", \"); " ++
                  e ++ "(FLD(v, 0)); v = FLD(v, 1); }\npr_s(\"]\");\n"}
            case 6n:
              do Gen<Doc>:
                parts : Doc <- Gen.printer.rec(fu, g, PSTuple{Ty.tuple(ty), "v"})
                return Doc.list([DStr{"pr_s(\"(\");\n"}, parts, DStr{"pr_s(\")\");\n"}])
            case 7n:
              Gen.pure(Doc, DStr{"(void)v; pr_s(\"<function>\");\n"})
            case 8n:
              do Gen<Doc>:
                e : String <- Gen.printer.rec(fu, g, PSPrinter{P.last(Ty.args(ty))})
                return DStr{Gen.printer.arr(e, G.ctor(g, "ALeaf"))}
            case 9n:
              Gen.pure(Doc, DStr{"(void)v; pr_s(\"{==}\");\n"})
            case 10n+p:
              Gen.printer.rec(fu, g, PSAdt{ty, G.body(g, "%" ++ Ty.head(ty))})
        case PSBody{+ty, +h}:
          Gen.printer.rec(fu, g, PSHead{ty, P.which(Ty.alias(h), ["U32", "Nat", "F32", "Char", "String",
            "List", "&", "->", "Array", "=="])})
        case PSMemo{+ty, +key, m}:
          match m:
            case Some{f}:
              Gen.pure(String, f)
            case None{}:
              do Gen<String>:
                +k : U32 <- Gen.fresh()
                +f : String <- Gen.pure(String, "P" ++ U32.show(k))
                Gen.memo.add(Bind{key, f})
                Gen.proto(DStr{"static void " ++ f ++ "(V v);\n"})
                b : Doc <- Gen.printer.rec(fu, g, PSBody{ty, Ty.head(ty)})
                Gen.code(Doc.list([DStr{"static void " ++ f ++ "(V v) {\n"}, b, DStr{"}\n"}]))
                return f

# Returns the name of a C function printing values of a type.
def Gen.printer(+g: G, +ty: Expr) -> Gen(String):
  Gen.printer.rec(Fuel.max(), g, PSPrinter{ty})

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
    case DLaw{n, ps, r} <> t:
      Mod.names(t, n <> acc)
    case DType{n, ps, cs} <> t:
      Mod.names(t, n <> Mod.ctor_names(cs, acc))
    case DImport{p, a} <> t:
      Mod.names(t, acc)

# The names a module defines, as a set: a qualified module renames every
# variable it reads, and check.bend defines thousands.
type Qual is Data:
  Qual{alias: String, names: Set()}

def Mod.q(+q: Qual, +x: String) -> String:
  Qual{+alias, +names} = q
  Bool.pick(String, Pair.snd(Set(), Bool, Set.has(names, x)), alias ++ "." ++ x, x)

def Mod.set(xs: List<&2, String>, s: Set()) -> Set():
  match xs:
    case Nil{}:
      s
    case x <> t:
      Mod.set(t, Set.add(s, x))

def Mod.param_names(ps: List<&2, Param>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case Param{n, m, t} <> rest:
      n <> Mod.param_names(rest)

def Mod.var(+q: Qual, +bound: List<&2, String>, +x: String) -> String:
  Bool.pick(String, Str.has(bound, x), x, Mod.q(q, x))

# p with a in front of its fields (see Expr.push).
def Pat.push(a: Pat, p: Pat) -> Pat:
  match p:
    case PCtor{n, xs}:
      PCtor{n, a <> xs}
    case other:
      other

def Mod.pat(+q: Qual, p: Pat) -> Pat:
  match p:
    case PCtor{n, args}:
      match args:
        case Nil{}:
          PCtor{Mod.q(q, n), Nil{}}
        case a <> t:
          Pat.push(Mod.pat(q, a), Mod.pat(q, PCtor{n, t}))
    case PSucc{k, x}:
      PSucc{k, Mod.pat(q, x)}
    case other:
      other

def Mod.pats(+q: Qual, ps: List<&2, Pat>) -> List<&2, Pat>:
  match ps:
    case Nil{}:
      Nil{}
    case h <> t:
      Mod.pat(q, h) <> Mod.pats(q, t)

# Renames references to module names (locals shadow them).
def Mod.go(+q: Qual, e: Expr, +bound: List<&2, String>) -> Expr:
  match e:
    case EVar{x}:
      EVar{Mod.var(q, bound, x)}
    case ECall{f, args}:
      match args:
        case Nil{}:
          ECall{Mod.go(q, f, bound), Nil{}}
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, ECall{f, t}, bound))
    case ECtor{n, args}:
      match args:
        case Nil{}:
          ECtor{Mod.q(q, n), Nil{}}
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, ECtor{n, t}, bound))
    case ELam{+p, b}:
      ELam{Mod.pat(q, p), Mod.go(q, b, Pat.vars(p, bound))}
    case ELet{+p, v, b}:
      ELet{Mod.pat(q, p), Mod.go(q, v, bound), Mod.go(q, b, Pat.vars(p, bound))}
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, EMatch{t, cases}, bound))
        case Nil{}:
          match cases:
            case Nil{}:
              EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Mod.go(q, c, bound), Mod.go(q, EMatch{Nil{}, t}, bound))
    case ECase{+ps, b}:
      ECase{Mod.pats(q, ps), Mod.go(q, b, Pats.vars(ps, bound))}
    case ESucc{k, x}:
      ESucc{k, Mod.go(q, x, bound)}
    case EOp{op, a, b}:
      EOp{op, Mod.go(q, a, bound), Mod.go(q, b, bound)}
    case EAnn{x, t}:
      EAnn{Mod.go(q, x, bound), Mod.var(q, bound, t)}
    case ETy{n, args}:
      match args:
        case Nil{}:
          ETy{Mod.var(q, bound, n), Nil{}}
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, ETy{n, t}, bound))
    case other:
      other

def Mod.expr(+q: Qual, +bound: List<&2, String>, e: Expr) -> Expr:
  Mod.go(q, e, bound)

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

def Mod.decl(+q: Qual, d: Decl) -> Decl:
  match d:
    case DDef{n, +ps, b, r}:
      DDef{Mod.q(q, n), ps, Mod.expr(q, Mod.param_names(ps), b), Mod.expr(q, Nil{}, r)}
    case DEff{n, ps, ims}:
      DEff{Mod.q(q, n), ps, ims}
    case DLaw{n, ps, r}:
      DLaw{Mod.q(q, n), ps, Mod.expr(q, Nil{}, r)}
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
  Mod.decls(Qual{alias, Mod.set(Mod.names(ds, Nil{}), Set.new())}, ds)

def Mod.dir.go(s: String) -> String:
  match s:
    case SNil{}:
      SNil{}
    case SCon{Chr{+x}, +t}:
      Bool.pick(Unit -> String, U32.is_eq(x, 47), u => SCon{Chr{x}, t}, u => Mod.dir.go(t))(Unit{})

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

# Fetches a hub package into lib, unless it is there (see rt/hub.c).
def Hub.ensure(lib: String, hub: String, rel: String) ->
  IO(Result<&1, &1, U32 & String, Unit>):
  import "./rt/hub.c"
  import "./rt/hub.js"

def Eff.path(+dir: String, +p: String) -> String:
  Bool.pick(String, String.starts_with(p, "/"), p, dir ++ p)

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

# Effect sources name ids as CID(Name) and FID(name) (the effect ABI since
# Bend 2.0.28): the driver reads a name in the effect's namespace first, then
# as it is, and writes the id bendc gives it (CID_NAME, F_name; on JS the
# name as a string). A name the program does not declare keeps its spelling,
# so `#ifdef CID(Name)` tests for a constructor.
def Main.ids.word(+c: U32) -> Bool:
  Bool.or(Bool.or(Bool.and(U32.is_ge(c, 48), U32.is_le(c, 57)), Bool.and(U32.is_ge(c, 65), U32.is_le(c, 90))),
    Bool.or(Bool.and(U32.is_ge(c, 97), U32.is_le(c, 122)), U32.is_eq(c, 95)))

def Main.ids.namec(+c: U32) -> Bool:
  Bool.or(Main.ids.word(c), Bool.or(Bool.or(U32.is_eq(c, 46), U32.is_eq(c, 47)),
    Bool.or(U32.is_eq(c, 126), U32.is_eq(c, 45))))

# The length of the name s starts with.
def Main.ids.len(s: String) -> Nat:
  match s:
    case SNil{}:
      0n
    case SCon{Chr{c}, t}:
      Bool.pick(Unit -> Nat, Main.ids.namec(c), u => Nat.add(Main.ids.len(t), 1n), u => 0n)(Unit{})

# How an id is written: 0 a C constructor or effect id, 1 a C function id,
# 2 a JS name.
def Main.ids.as(+mode: U32, +q: String) -> String:
  Bool.pick(String, U32.is_eq(mode, 0), Gen.cid(q), Bool.pick(String, U32.is_eq(mode, 1), Gen.f(q),
    "\"" ++ q ++ "\""))

# The first of ns.k, .., k that the program declares.
def Main.ids.pick(ns: List<&2, String>, +mode: U32, +k: String, +known: Set()) -> String:
  match ns:
    case Nil{}:
      Main.ids.as(mode, k)
    case n <> t:
      +q = n ++ "." ++ k
      Bool.pick(String, Dps.has(known, q), Main.ids.as(mode, q), Main.ids.pick(t, mode, k, known))

type IdEnv is Data:
  IdEnv{ns: List<&2, String>, known: Set(), js: Bool}

def IdEnv.ns(e: IdEnv) -> List<&2, String>:
  IdEnv{ns, known, js} = e
  ns

def IdEnv.known(e: IdEnv) -> Set():
  IdEnv{ns, known, js} = e
  known

def IdEnv.js(e: IdEnv) -> Bool:
  IdEnv{ns, known, js} = e
  js

# Whether ID( is followed by a name of n characters and ).
def Main.ids.ok(+t: String, +n: Nat) -> Bool:
  Bool.and(Nat.is_gt(n, 0n), String.starts_with(String.drop(t, n), ")"))

# What a C or F before t (which starts with ID() is written as: the id,
# or itself.
def Main.ids.head(+c: U32, +t0: String, +env: IdEnv) -> String:
  +t = String.drop(t0, 3n)
  +n = Main.ids.len(t)
  Bool.pick(String, Main.ids.ok(t, n),
    Main.ids.pick(IdEnv.ns(env), Bool.pick(U32, IdEnv.js(env), 2, Bool.pick(U32, U32.is_eq(c, 70), 1, 0)),
      String.take(t, n), IdEnv.known(env)),
    SCon{Chr{c}, SNil{}})

# How many characters of t0 the id replaces (ID(name)), or 0.
def Main.ids.skip(+t0: String) -> Nat:
  +t = String.drop(t0, 3n)
  +n = Main.ids.len(t)
  Bool.pick(Nat, Main.ids.ok(t, n), Nat.add(n, 4n), 0n)

# s with each CID(..) and FID(..) replaced; prev: the last character was
# part of a word; skip: characters an id replaced, still to drop.
def Main.ids(s: String, prev: Bool, +env: IdEnv, skip: Nat) -> String:
  match s skip:
    case SNil{} k:
      SNil{}
    case SCon{c, t} 1n+k:
      Main.ids(t, True{}, env, k)
    case SCon{Chr{+c}, +t} 0n:
      Bool.pick(Unit -> String, Bool.and(Bool.not(prev), Bool.and(Bool.or(U32.is_eq(c, 67), U32.is_eq(c, 70)),
        String.starts_with(t, "ID("))),
        u => Main.ids.head(c, t, env) ++ Main.ids(t, True{}, env, Main.ids.skip(t)),
        u => SCon{Chr{c}, Main.ids(t, Main.ids.word(c), env, 0n)})(Unit{})

def Main.ids.pre(segs: List<&2, String>, +acc: String, out: List<&2, String>) -> List<&2, String>:
  match segs:
    case Nil{}:
      out
    case +h <> t:
      +q = Bool.pick(String, String.is_empty(acc), h, acc ++ "." ++ h)
      Main.ids.pre(t, q, q <> out)

# The namespaces an effect's name is in, innermost first: M.Foo.bar is in
# M.Foo and M.
def Main.ids.ns(name: String) -> List<&2, String>:
  List.drop(&2, String, Main.ids.pre(String.split(name, '.'), "", Nil{}), 1n)

# The effect whose imports include the file p.
def Main.ids.owner(ds: List<&2, Decl>, +p: String) -> String:
  match ds:
    case Nil{}:
      ""
    case DEff{+n, ps, ims} <> t:
      Bool.pick(String, Str.has(ims, p), n, Main.ids.owner(t, p))
    case d <> t:
      Main.ids.owner(t, p)

# The effect source at p, its ids written for this program.
def Main.ids.src(+ds: List<&2, Decl>, +known: Set(), +js: Bool, +p: String, src: String) -> String:
  Main.ids(src, False{}, IdEnv{Main.ids.ns(Main.ids.owner(ds, p)), known, js}, 0n)

# Every name the program declares.
def Main.ids.known(ds: List<&2, Decl>) -> Set():
  Set.from_list(Mod.names(ds, Nil{}))

law Main.effs:
  for ps: List<&2, String>
  for +ds: List<&2, Decl>
  for +known: Set()
  for acc: String
  IO(String)

def Main.eff.pick(p: String, rt: Bool) -> IO(String):
  match rt:
    case True{}:
      IO.pure(String, RtChan.src())
    case False{}:
      IO.read_file(p)

# An effect's C source. Base's effs/chan.c keeps its channels where the
# collector does not look: rt/chan.c stands in (see there).
def Main.eff.src(+p: String) -> IO(String):
  Main.eff.pick(p, String.ends_with(p, "/effs/chan.c"))

# Reads the effect sources to splice into the output.
def Main.effs(ps, ds, known, acc):
  match ps:
    case Nil{}:
      IO.pure(String, acc)
    case +p <> t:
      do IO<String>:
        src : String <- Main.eff.src(p)
        Main.effs(t, ds, known, acc ++ Main.ids.src(ds, known, False{}, p, src) ++ "\n")

def Ctors.is_ident(+c: U32) -> Bool:
  Bool.or(Bool.or(Bool.and(U32.is_ge(c, 97), U32.is_le(c, 122)), Bool.and(U32.is_ge(c, 65), U32.is_le(c, 90))),
    Bool.or(Bool.and(U32.is_ge(c, 48), U32.is_le(c, 57)), U32.is_eq(c, 95)))

# The identifier s starts with (after blanks).
def Ctors.ident(s: String) -> String:
  match s:
    case SNil{}:
      ""
    case SCon{Chr{+c}, +t}:
      Bool.pick(Unit -> String, U32.is_eq(c, 32), u => Ctors.ident(t),
        u => Bool.pick(Unit -> String, Ctors.is_ident(c), u => SCon{Chr{c}, Ctors.ident(t)}, u => "")(Unit{}))(Unit{})

def Ctors.pat() -> String:
  "__attribute__((constructor))"

def Ctors.scan.if(hit: Bool, +t: String, rest: List<&2, String>) -> List<&2, String>:
  match hit:
    case True{}:
      Ctors.ident(String.drop(t, Nat.sub(String.length(Ctors.pat()), 1n))) <> rest
    case False{}:
      rest

# The functions a C text marks __attribute__((constructor)), in order.
def Ctors.scan(s: String) -> List<&2, String>:
  match s:
    case SNil{}:
      Nil{}
    case SCon{+c, +t}:
      Ctors.scan.if(String.starts_with(SCon{c, t}, Ctors.pat()), t, Ctors.scan(t))

def Ctors.calls(ns: List<&2, String>) -> String:
  match ns:
    case Nil{}:
      ""
    case n <> t:
      "  " ++ n ++ "();\n" ++ Ctors.calls(t)

def Ctors.def(ns: List<&2, String>) -> String:
  "\n#ifdef __TINYC__\n// tcc ignores __attribute__((constructor)): main calls these\nstatic void bend_ctors(void) {\n" ++
    Ctors.calls(ns) ++ "}\n#endif\n"

def Main.emit.ok(+ds: List<&2, Decl>, head: String, effs: List<&2, String>, body: String) -> IO(Unit):
  do IO<Unit>:
    +srcs : String <- Main.effs(effs, ds, Main.ids.known(ds), "")
    IO.write(head ++ srcs ++ Ctors.def(Ctors.scan(srcs)) ++ body)

def Main.emit(+ds: List<&2, Decl>, r: COut) -> IO(Unit):
  COut{head, effs, body, errs} = r
  match errs:
    case Nil{}:
      Main.emit.ok(ds, head, effs, body)
    case e <> t:
      do IO<Unit>:
        IO.print_err(String.join(List.reverse(&2, String, e <> t), "\n"))
        IO.die(Unit, 1, "bendc: compilation failed")

def Main.free(r: Result<&1, &1, U32 & String, String>) -> Bool:
  match r:
    case Done{v}:
      String.is_empty(v)
    case Fail{e}:
      True{}

# Implicit parallelism: BEND_AUTO_PAR=0 or 1, else on but with BEND_NO_FREE
# (bendc's own build: its tree walks are small and called often, and
# forking them made it slower).
def Main.auto_par.set(e: Bool, v: String, free: Bool) -> Bool:
  match e:
    case True{}:
      free
    case False{}:
      Bool.not(String.eq(v, "0"))

def Main.auto_par(r: Result<&1, &1, U32 & String, String>, free: Bool) -> Bool:
  match r:
    case Done{+v}:
      Main.auto_par.set(String.is_empty(v), v, free)
    case Fail{e}:
      free

def Main.js.path(r: String & String) -> String:
  (p, h) = r
  p

# The JS files of the effect table's entries (path\thost), each once.
def Main.js.paths.go(es: List<&2, String>) -> List<&2, String>:
  match es:
    case Nil{}:
      Nil{}
    case e <> t:
      Main.js.path(Str.split_tab(e)) <> Main.js.paths.go(t)

def Main.js.paths(es: List<&2, String>) -> List<&2, String>:
  Gen.dedup(Main.js.paths.go(es), Nil{})

def Main.js.hosts.if(h: String, rest: List<&2, String>, hit: Bool) -> List<&2, String>:
  match hit:
    case True{}:
      h <> rest
    case False{}:
      rest

def Main.js.hosts.one(r: String & String, +p: String, rest: List<&2, String>) -> List<&2, String>:
  (q, h) = r
  Main.js.hosts.if(h, rest, Str.eq(q, p))

# The host functions of the effect table's entries at path p.
def Main.js.hosts(es: List<&2, String>, +p: String) -> List<&2, String>:
  match es:
    case Nil{}:
      Nil{}
    case e <> t:
      Main.js.hosts.one(Str.split_tab(e), p, Main.js.hosts(t, p))

def Main.js.entry(+host: String) -> String:
  "  [\"" ++ host ++ "\"]: R[\"" ++ host ++ "\"] ?? { run: typeof " ++ host ++ " === \"function\" ? " ++ host ++
    " : undefined, need: typeof " ++ host ++ "_need === \"function\" ? " ++ host ++ "_need : undefined },\n"

def Main.js.entries(hosts: List<&2, String>) -> String:
  match hosts:
    case Nil{}:
      ""
    case h <> t:
      Main.js.entry(h) ++ Main.js.entries(t)

# A file registers its effects with io_eff(CID(Name), run, need) (Bend
# 2.0.28), or defines their host functions (before it).
def Main.js.wrap(src: String, hosts: List<&2, String>) -> String:
  "...(() => {\nconst R = {};\nconst io_eff = (k, run, need) => { R[k.toLowerCase().replaceAll(\".\", \"_\")] = " ++
    "{ run, need }; };\n" ++ src ++ "\nreturn {\n" ++ Main.js.entries(hosts) ++ "};\n})(),\n"

# The effect table: each JS file effects import, run once (Chan's four
# effects share chan.js and its state) and wrapped as the official target
# wraps it, answering the host functions of the effects that import it.
def Main.js.effs(ps: List<&2, String>, +es: List<&2, String>, +ds: List<&2, Decl>, +known: Set(), acc: String) ->
  IO(String):
  match ps:
    case Nil{}:
      IO.pure(String, acc)
    case +p <> t:
      do IO<String>:
        src : String <- IO.read_file(p)
        Main.js.effs(t, es, ds, known, acc ++ Main.js.wrap(Main.ids.src(ds, known, True{}, p, src), Main.js.hosts(es, p)))

def Main.emit.js.ok(+ds: List<&2, Decl>, head: String, +effs: List<&2, String>, body: String) -> IO(Unit):
  do IO<Unit>:
    tab : String <- Main.js.effs(Main.js.paths(effs), effs, ds, Main.ids.known(ds), "")
    IO.write(head ++ "\nconst EFF = {\n" ++ tab ++ "};\n\n" ++ body)

def Main.emit.js(+ds: List<&2, Decl>, r: COut) -> IO(Unit):
  COut{head, effs, body, errs} = r
  match errs:
    case Nil{}:
      Main.emit.js.ok(ds, head, effs, body)
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

def J.program.fin(r: String & St) -> COut:
  (entry, st) = r
  St{n, protos, code, refs, errs, memo, effs} = st
  COut{RtJs.src(), Gen.dedup(List.reverse(&2, String, Gen.effs.files(effs)), Nil{}), Doc.flat(Doc.list([code, DStr{"\n" ++ entry}])), errs}

# Lambda-matches
# ==============

# \{K: h; m} (parsed as %mat{K{}, h, m}, \{} as %efq{}) becomes
# _lm => match _lm: case K{f..}: h(f..); case y: m(y). A lambda arm binds
# the fields itself: \{Succ: p => e} is case Succ{p}: e.

# The field count of constructor c.
def LM.arity(ds: List<&2, Decl>, +c: String) -> Nat:
  match ds:
    case Nil{}:
      0n
    case DType{+n, +ps, cs} <> t:
      match cs:
        case Nil{}:
          LM.arity(t, c)
        case Ctor{+name, fs} <> r:
          Bool.pick(Unit -> Nat, Str.eq(name, c),
            u => List.length(&2, Field, fs),
            u => LM.arity(DType{n, ps, r} <> t, c))(Unit{})
    case other <> t:
      LM.arity(t, c)

def LM.names(n: Nat, +i: U32) -> List<&2, String>:
  match n:
    case 0n:
      Nil{}
    case 1n+p:
      ("_lm" ++ U32.show(i)) <> LM.names(p, (i + 1 : U32))

def LM.pvars(xs: List<&2, String>) -> List<&2, Pat>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      PVar{x} <> LM.pvars(t)

def LM.evars(xs: List<&2, String>) -> List<&2, Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      EVar{x} <> LM.evars(t)

def LM.app(h: Expr, +xs: List<&2, String>) -> List<&2, Pat> & Expr:
  (LM.pvars(xs), ECall{h, LM.evars(xs)})

def LM.cons(p: Pat, r: List<&2, Pat> & Expr) -> List<&2, Pat> & Expr:
  (ps, b) = r
  (p <> ps, b)

# An arm's field patterns and body.
def LM.fields(h: Expr, n: Nat, +i: U32) -> List<&2, Pat> & Expr:
  match h n:
    case ELam{PVar{x}, b} 1n+p:
      LM.cons(PVar{x}, LM.fields(b, p, (i + 1 : U32)))
    case other 0n:
      (Nil{}, other)
    case other 1n+p:
      LM.app(other, LM.names(1n+p, i))

def LM.arm(+c: String, r: List<&2, Pat> & Expr) -> Expr:
  (ps, b) = r
  ECase{[PCtor{c, ps}], b}

def LM.dflt(m: Expr) -> Expr:
  match m:
    case ELam{PVar{y}, b}:
      ECase{[PVar{y}], b}
    case other:
      ECase{[PVar{"_lm"}], ECall{other, [EVar{"_lm"}]}}

def LM.arms(+ds: List<&2, Decl>, e: Expr) -> List<&2, Expr>:
  match e:
    case ECtor{"%mat", ECtor{+c, cn} <> h <> m <> Nil{}}:
      LM.arm(c, LM.fields(h, LM.arity(ds, c), 0)) <> LM.arms(ds, m)
    case ECtor{"%efq", Nil{}}:
      Nil{}
    case other:
      [LM.dflt(other)]

def LM.ctor(+ds: List<&2, Decl>, +n: String, args: List<&2, Expr>, mat: Bool) -> Expr:
  match mat:
    case True{}:
      ELam{PVar{"_lm"}, EMatch{[EVar{"_lm"}], LM.arms(ds, ECtor{n, args})}}
    case False{}:
      ECtor{n, args}

# x in front of a node's first list (a call's or constructor's arguments,
# a match's scrutinees).
def LM.push(x: Expr, e: Expr) -> Expr:
  match e:
    case ECall{f, xs}:
      ECall{f, x <> xs}
    case ECtor{n, xs}:
      ECtor{n, x <> xs}
    case EMatch{xs, cs}:
      EMatch{x <> xs, cs}
    case other:
      other

# c in front of a match's cases.
def LM.push.case(c: Expr, e: Expr) -> Expr:
  match e:
    case EMatch{xs, cs}:
      EMatch{xs, c <> cs}
    case other:
      other

def LM.ctor.top(+ds: List<&2, Decl>, e: Expr) -> Expr:
  match e:
    case ECtor{+n, args}:
      LM.ctor(ds, n, args, Str.eq(n, "%mat"))
    case other:
      other

# Whether the body b never reads x.
def LM.dead(+x: String, +b: Expr) -> Bool:
  U32.is_zero(Use.n(x, b))

# A node's lists are walked one element at a time, the rest on the same
# node (smaller); raw leaves a constructor's %mat for its caller.
# A let whose name the body never reads is dropped (its value is pure):
# a proof bound only for a rewrite (e = add_comm(a, b); %e : T; ..)
# never runs.
def LM.go(+ds: List<&2, Decl>, e: Expr, raw: Bool) -> Expr:
  match e:
    case ECall{f, args}:
      match args:
        case Nil{}:
          ECall{LM.go(ds, f, False{}), Nil{}}
        case a <> t:
          LM.push(LM.go(ds, a, False{}), LM.go(ds, ECall{f, t}, False{}))
    case ECtor{+n, args}:
      match args:
        case Nil{}:
          Bool.pick(Unit -> Expr, raw, u => ECtor{n, Nil{}},
            u => LM.ctor(ds, n, Nil{}, Str.eq(n, "%mat")))(Unit{})
        case a <> t:
          +r = {LM.push(LM.go(ds, a, False{}), LM.go(ds, ECtor{n, t}, True{})) : Expr}
          Bool.pick(Unit -> Expr, raw, u => r, u => LM.ctor.top(ds, r))(Unit{})
    case ELam{p, b}:
      ELam{p, LM.go(ds, b, False{})}
    case ELet{p, v, b}:
      match p:
        case PVar{+x}:
          +b2 = {LM.go(ds, b, False{}) : Expr}
          Bool.pick(Unit -> Expr, LM.dead(x, b2), u => b2,
            u => ELet{PVar{x}, LM.go(ds, v, False{}), b2})(Unit{})
        case other:
          ELet{other, LM.go(ds, v, False{}), LM.go(ds, b, False{})}
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          LM.push(LM.go(ds, a, False{}), LM.go(ds, EMatch{t, cases}, False{}))
        case Nil{}:
          match cases:
            case c <> t:
              LM.push.case(LM.go(ds, c, False{}), LM.go(ds, EMatch{Nil{}, t}, False{}))
            case Nil{}:
              EMatch{Nil{}, Nil{}}
    case ECase{ps, b}:
      ECase{ps, LM.go(ds, b, False{})}
    case ESucc{k, x}:
      ESucc{k, LM.go(ds, x, False{})}
    case EOp{op, a, b}:
      EOp{op, LM.go(ds, a, False{}), LM.go(ds, b, False{})}
    case EAnn{x, t}:
      EAnn{LM.go(ds, x, False{}), t}
    case other:
      other

def LM.expr(+ds: List<&2, Decl>, e: Expr) -> Expr:
  LM.go(ds, e, False{})

# The type of name's law, if one declares it.
def LM.law(ds: List<&2, Decl>, +name: String) -> Expr:
  match ds:
    case Nil{}:
      ETy{"", Nil{}}
    case DLaw{n, ps, ret} <> t:
      Bool.pick(Expr, Str.eq(n, name), ret, LM.law(t, name))
    case other <> t:
      LM.law(t, name)

def LM.body(+all: List<&2, Decl>, b: Expr, claim: Bool) -> Expr:
  match claim:
    case True{}:
      ETy{"", Nil{}}
    case False{}:
      LM.expr(all, b)

# A def whose type is a claim {a == b : T} is its proof, erased: it never
# runs (it may take structural views of words the compiled lanes refuse).
def LM.decl(+all: List<&2, Decl>, d: Decl) -> Decl:
  match d:
    case DDef{+n, ps, b, +ret}:
      DDef{n, ps, LM.body(all, b, Bool.or(Str.eq(Ty.head(ret), "=="),
        Str.eq(Ty.head(LM.law(all, n)), "=="))), ret}
    case other:
      other

def LM.decls(+all: List<&2, Decl>, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      LM.decl(all, d) <> LM.decls(all, t)

def Main.ast(r: Result<&2, &2, String, List<&2, Decl>>) -> IO(Unit):
  match r:
    case Fail{e}:
      IO.die(Unit, 1, "bendc: parse error: " ++ e)
    case Done{ds}:
      IO.write(Decls.show(ds))

def Main.chk.fail(-A: Type, e: Chk.Err) -> IO(A):
  IO.die(A, 1, Chk.verdict_fail() ++ Chk.show_err(e))

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

# An import path is plain names (a letter or _, then letters, digits, _ and
# -) joined by /, after a leading / or ../s; a hub path's names follow its
# 0x head. The official rule, checked before the file is looked for.
def Imp.char(+c: U32, first: Bool) -> Bool:
  Bool.or(Bool.or(Bool.and(U32.is_ge(U32.or(c, 32), 97), U32.is_le(U32.or(c, 32), 122)), U32.is_eq(c, 95)),
    Bool.and(Bool.not(first), Bool.or(Char.is_digit(Chr{c}), U32.is_eq(c, 45))))

def Imp.name(s: String, first: Bool) -> Bool:
  match s:
    case SNil{}:
      Bool.not(first)
    case SCon{Chr{+c}, t}:
      Bool.and(Imp.char(c, first), Imp.name(t, False{}))

def Imp.names(xs: List<&2, String>, ups: Bool) -> Bool:
  match xs:
    case Nil{}:
      False{}
    case +x <> t:
      match t:
        case Nil{}:
          Imp.name(x, True{})
        case h <> r:
          +up = Bool.and(ups, String.eq(x, ".."))
          Bool.and(Bool.or(up, Imp.name(x, True{})), Imp.names(h <> r, up))

def Imp.hub.body(s: String) -> String:
  match s:
    case SCon{Chr{47}, t}:
      t
    case SCon{c, t}:
      Imp.hub.body(t)
    case SNil{}:
      SNil{}

def Imp.plain(+path: String) -> Bool:
  +p = Bool.pick(String, String.starts_with(path, "./"), String.drop(path, 2n), path)
  +q = String.take(p, Nat.sub(String.length(p), 5n))
  Bool.pick(Bool, Main.chk.is_hub(q), Bool.and(Main.chk.is_hub(path), Imp.names(String.split(Imp.hub.body(q), '/'), False{})),
    Bool.pick(Bool, String.starts_with(q, "/"), Imp.names(String.split(String.drop(q, 1n), '/'), False{}),
      Imp.names(String.split(q, '/'), True{})))

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

def Path.segs(+p: String) -> List<&2, String>:
  Bool.pick(List<&2, String>, String.eq(p, "."), Nil{}, String.split(p, '/'))

def Path.ups(xs: List<&2, String>, acc: List<&2, String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      acc
    case h <> t:
      ".." <> Path.ups(t, acc)

def Path.rel.go(xs: List<&2, String>, ys: List<&2, String>) -> List<&2, String>:
  match xs ys:
    case +x <> +xt +y <> +yt:
      Bool.pick(Unit -> List<&2, String>, String.eq(x, y), u => Path.rel.go(xt, yt),
        u => Path.ups(x <> xt, y <> yt))(Unit{})
    case a b:
      Path.ups(a, b)

# The path to normalized path b from normalized directory a (as
# path.posix.relative gives it, but without resolving symbolic links).
def Path.rel(+a: String, +b: String) -> String:
  String.join(Path.rel.go(Path.segs(a), Path.segs(b)), "/")

# The directory of the file the check started from: the first one marked.
def Main.chk.top(seen: List<&2, Chk.SB2>) -> String:
  match seen:
    case Nil{}:
      "."
    case Chk.SB2{k, v} <> Nil{}:
      Path.dirname(k)
    case h <> t:
      Main.chk.top(t)

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

def Main.pwd(r: Result<&1, &1, U32 & String, String>) -> String:
  match r:
    case Done{d}:
      d
    case Fail{e}:
      ""

# A path as the official checker names a missing file: resolved against the
# working directory (the shell's PWD).
def Path.abs(+pwd: String, +p: String) -> String:
  Path.norm(Bool.pick(String, Bool.or(String.starts_with(p, "/"), String.is_empty(pwd)), p, pwd ++ "/" ++ p))

def CS.at_end(st: CS) -> CS:
  CS{+book, seen, n0} = st
  CS{book, seen, Chk.book_len(book)}

def CS.seen(+st: CS) -> List<&2, Chk.SB2>:
  CS{book, +seen, n0} = st
  seen

# The checker's loader, one def (fuel: its calls): ChkSel picks the step.
type ChkSel is Type:
  CLImpRel{f: Nat, base: String, dir: String, ns: String, sp: Chk.Sp, rel: String, alias: String, path: String,
      st: CS, al: List<&2, Chk.SB2>, bend: Bool}
  CLImpPlain{f: Nat, base: String, dir: String, ns: String, sp: Chk.Sp, rel: String, alias: String, path: String,
      st: CS, al: List<&2, Chk.SB2>, ok: Bool}
  CLImpGo{f: Nat, base: String, dir: String, ns: String, sp: Chk.Sp, rel: String, alias: String, path: String, st: CS,
      al: List<&2, Chk.SB2>, base_imp: Bool}
  CLImpFresh{f: Nat, base: String, dir: String, ns: String, sp: Chk.Sp, rel: String, alias: String, path: String,
      st: CS, al: List<&2, Chk.SB2>, taken: Bool}
  CLImp{f: Nat, base: String, dir: String, ns: String, src: String, imp: Chk.Imp, st: CS, al: List<&2, Chk.SB2>}
  CLImpsNext{f: Nat, base: String, dir: String, ns: String, src: String, imps: List<&2, Chk.Imp>,
      r: CS & List<&2, Chk.SB2>}
  CLImps{f: Nat, base: String, dir: String, ns: String, src: String, imps: List<&2, Chk.Imp>, st: CS,
      al: List<&2, Chk.SB2>}
  CLHdr{f: Nat, base: String, file: String, ns: String, src: String, st: CS, h: Chk.Hdr}
  CLSrc{f: Nat, base: String, file: String, ns: String, src: String, st: CS}
  CLRead{f: Nat, base: String, file: String, ns: String, sp: Chk.Sp, st: CS, m: Maybe<&2, String>}
  CLSeen{f: Nat, base: String, file: String, ns: String, sp: Chk.Sp, st: CS, done: Maybe<&2, String>}
  CLLoad{fuel: Nat, base: String, file: String, ns: String, sp: Chk.Sp, st: CS}

def ChkSel.ty(k: ChkSel) -> Type:
  match k:
    case CLImpRel{f, base, dir, ns, sp, rel, alias, path, st, al, bend}:
      IO(CS & List<&2, Chk.SB2>)
    case CLImpPlain{f, base, dir, ns, sp, rel, alias, path, st, al, ok}:
      IO(CS & List<&2, Chk.SB2>)
    case CLImpGo{f, base, dir, ns, sp, rel, alias, path, st, al, base_imp}:
      IO(CS & List<&2, Chk.SB2>)
    case CLImpFresh{f, base, dir, ns, sp, rel, alias, path, st, al, taken}:
      IO(CS & List<&2, Chk.SB2>)
    case CLImp{f, base, dir, ns, src, imp, st, al}:
      IO(CS & List<&2, Chk.SB2>)
    case CLImpsNext{f, base, dir, ns, src, imps, r}:
      IO(CS & List<&2, Chk.SB2>)
    case CLImps{f, base, dir, ns, src, imps, st, al}:
      IO(CS & List<&2, Chk.SB2>)
    case CLHdr{f, base, file, ns, src, st, h}:
      IO(CS)
    case CLSrc{f, base, file, ns, src, st}:
      IO(CS)
    case CLRead{f, base, file, ns, sp, st, m}:
      IO(CS)
    case CLSeen{f, base, file, ns, sp, st, done}:
      IO(CS)
    case CLLoad{fuel, base, file, ns, sp, st}:
      IO(CS)

def Main.chk.go(n: Nat, k: ChkSel) -> ChkSel.ty(k):
  match n:
    case 0n:
      match k:
        case CLImpRel{f, base, dir, ns, sp, rel, alias, path, st, al, bend}:
          IO.die(CS & List<&2, Chk.SB2>, 1, "bendc: out of fuel loading imports")
        case CLImpPlain{f, base, dir, ns, sp, rel, alias, path, st, al, ok}:
          IO.die(CS & List<&2, Chk.SB2>, 1, "bendc: out of fuel loading imports")
        case CLImpGo{f, base, dir, ns, sp, rel, alias, path, st, al, base_imp}:
          IO.die(CS & List<&2, Chk.SB2>, 1, "bendc: out of fuel loading imports")
        case CLImpFresh{f, base, dir, ns, sp, rel, alias, path, st, al, taken}:
          IO.die(CS & List<&2, Chk.SB2>, 1, "bendc: out of fuel loading imports")
        case CLImp{f, base, dir, ns, src, imp, st, al}:
          IO.die(CS & List<&2, Chk.SB2>, 1, "bendc: out of fuel loading imports")
        case CLImpsNext{f, base, dir, ns, src, imps, r}:
          IO.die(CS & List<&2, Chk.SB2>, 1, "bendc: out of fuel loading imports")
        case CLImps{f, base, dir, ns, src, imps, st, al}:
          IO.die(CS & List<&2, Chk.SB2>, 1, "bendc: out of fuel loading imports")
        case CLHdr{f, base, file, ns, src, st, h}:
          IO.die(CS, 1, "bendc: out of fuel loading imports")
        case CLSrc{f, base, file, ns, src, st}:
          IO.die(CS, 1, "bendc: out of fuel loading imports")
        case CLRead{f, base, file, ns, sp, st, m}:
          IO.die(CS, 1, "bendc: out of fuel loading imports")
        case CLSeen{f, base, file, ns, sp, st, done}:
          IO.die(CS, 1, "bendc: out of fuel loading imports")
        case CLLoad{fuel, base, file, ns, sp, st}:
          IO.die(CS, 1, "bendc: out of fuel loading imports")
    case Succ{+fu}:
      match k:
        case CLImpRel{f, +base, +dir, +ns, +sp, +rel, +alias, +path, +st, al, bend}:
          match bend:
            case False{}:
              Main.chk.fail(CS & List<&2, Chk.SB2>, Chk.err0("an import of a .bend file", Chk.MStr{"'" ++ path ++ "'"}, sp))
            case True{}:
              Main.chk.go(fu, CLImpPlain{f, base, dir, ns, sp, rel, alias, path, st, al, Imp.plain(path)})
        case CLImpPlain{f, +base, +dir, +ns, +sp, +rel, +alias, +path, +st, al, ok}:
          match ok:
            case False{}:
              Main.chk.fail(CS & List<&2, Chk.SB2>, Chk.err0("an import path of plain names (letters, digits, _ and -; the hub's files import the hub's)",
                Chk.MStr{"'" ++ path ++ "'"}, sp))
            case True{}:
              +abs = String.starts_with(rel, "/")
              +hub = Main.chk.is_hub(rel)
              # a file's namespace is its path from the first file's directory, so
              # two spellings of one file name one module (#1087)
              +sub = Bool.pick(String, Bool.or(abs, hub), rel, Path.rel(Main.chk.top(CS.seen(st)), Path.norm(dir ++ rel)))
              +ns2 = String.take(sub, Nat.sub(String.length(sub), 5n))
              do IO<CS & List<&2, Chk.SB2>>:
                +at : String <- Bool.pick(IO(String), hub, Main.chk.hub(rel),
                  IO.pure(String, Bool.pick(String, abs, rel, dir ++ rel)))
                st2 : CS <- Main.chk.go(fu, CLLoad{f, base, at, ns2, sp, st})
                return (st2, List.append(&2, Chk.SB2, al, [Chk.SB2{alias, ns2}]))
        case CLImpGo{f, +base, +dir, +ns, +sp, +rel, +alias, +path, st, +al, base_imp}:
          match base_imp:
            case True{}:
              do IO<CS & List<&2, Chk.SB2>>:
                st2 : CS <- Main.chk.go(fu, CLLoad{f, base, base, "", sp, st})
                return (st2, al)
            case False{}:
              Main.chk.go(fu, CLImpFresh{f, base, dir, ns, sp, rel, alias, path, st, al, Chk.SB2.has(al, alias)})
        case CLImpFresh{f, +base, +dir, +ns, +sp, +rel, +alias, +path, st, al, taken}:
          match taken:
            case True{}:
              Main.chk.fail(CS & List<&2, Chk.SB2>, Chk.err0("a fresh alias (" ++ alias ++ " names an earlier import)",
                Chk.MStr{"'import " ++ path ++ " as " ++ alias ++ "'"}, sp))
            case False{}:
              Main.chk.go(fu, CLImpRel{f, base, dir, ns, sp, rel, alias, path, st, al, String.ends_with(rel, ".bend")})
        # An import of a file as alias: where it is and its namespace.
        case CLImp{f, +base, +dir, +ns, +src, imp, st, al}:
          Chk.Imp{+path, +alias, +beg} = imp
          +sp = {Chk.Sp{src, beg, beg} : Chk.Sp}
          +rel = Path.norm(path)
          Main.chk.go(fu, CLImpGo{f, base, dir, ns, sp, rel, alias, path, st, al, String.is_empty(alias)})
        case CLImpsNext{f, +base, +dir, +ns, +src, imps, r}:
          (st, al) = r
          Main.chk.go(fu, CLImps{f, base, dir, ns, src, imps, st, al})
        case CLImps{+f, +base, +dir, +ns, +src, imps, st, al}:
          match imps:
            case Nil{}:
              IO.pure(CS & List<&2, Chk.SB2>, (st, al))
            case i <> t:
              do IO<CS & List<&2, Chk.SB2>>:
                r : CS & List<&2, Chk.SB2> <- Main.chk.go(fu, CLImp{f, base, dir, ns, src, i, st, al})
                Main.chk.go(fu, CLImpsNext{f, base, dir, ns, src, t, r})
        case CLHdr{f, +base, +file, +ns, +src, st, h}:
          Chk.Hdr{lines, imps, err} = h
          match err:
            case Some{e}:
              Main.chk.fail(CS, e)
            case None{}:
              do IO<CS>:
                r : CS & List<&2, Chk.SB2> <- Main.chk.go(fu, CLImps{f, base, Mod.dir(file), ns, src, imps,
                  CS.mark(st, Path.norm(file)), Nil{}})
                Main.chk.parse(base, file, ns, src, lines, r)
        case CLSrc{f, +base, +file, +ns, +src, st}:
          Main.chk.go(fu, CLHdr{f, base, file, ns, src, st, Chk.header(src)})
        case CLRead{f, +base, +file, +ns, +sp, st, m}:
          match m:
            case None{}:
              do IO<CS>:
                pwd : Result<&1, &1, U32 & String, String> <- IO.get_env("PWD")
                Main.chk.fail(CS, Chk.err0("no such file: " ++ Path.abs(Main.pwd(pwd), file), Chk.MNone{}, sp))
            case Some{src}:
              Main.chk.go(fu, CLSrc{f, base, file, ns, src, st})
        case CLSeen{f, +base, +file, +ns, +sp, st, done}:
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
                Main.chk.go(fu, CLRead{f, base, file, ns, sp, st, m})
        case CLLoad{fuel, +base, +file, +ns, +sp, +st}:
          match fuel:
            case 0n:
              IO.die(CS, 1, "bendc: imports nested too deeply at " ++ file)
            case 1n+f:
              Main.chk.go(fu, CLSeen{f, base, file, ns, sp, st, Chk.SB2.find(CS.seen(st), Path.norm(file))})

def Main.chk.load(fuel: Nat, base: String, file: String, ns: String, sp: Chk.Sp, st: CS) -> IO(CS):
  Main.chk.go(Fuel.max(), CLLoad{fuel, base, file, ns, sp, st})

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
def Main.check(+base: String, +file: String) -> IO(Chk.Book & Nat):
  do IO<Chk.Book & Nat>:
    st : CS <- Main.chk.load(64n, base, file, "", Chk.NoSp{}, CS{Chk.book_nil(), Nil{}, 0n})
    Main.check.fin(st)

# The verdict: every proof checks (on stdout), or the defs that rely on
# unsafe or foreign code (on stderr, exit 1).
def Main.check_only.go(bad: List<&2, String>) -> IO(Unit):
  match bad:
    case Nil{}:
      IO.write(Chk.report_text(Nil{}))
    case +h <> +t:
      IO.die(Unit, 1, Chk.report_text(h <> t))

def Main.check_only.fin(r: Chk.Book & Nat) -> IO(Unit):
  (b, n0) = r
  Main.check_only.go(Chk.report(b))

# Whether main returns a value (not IO) that may hold a function.
def Main.normalized(+b: Chk.Book) -> Bool:
  Bool.and(Bool.not(Chk.main_is_io(b)), Bool.or(Chk.main_has_fun(b), Chk.main_is_family(b)))

# The hex digits of n, then acc; k: the digits left (a U32 has 8).
def J.hex.go(k: Nat, +n: U32, +acc: String) -> String:
  match k:
    case 0n:
      "<hex: out of digits>"
    case 1n+j:
      +d = (n .&. 15 : U32)
      +c = Str.chr(Bool.pick(U32, U32.is_lt(d, 10), (48 + d : U32), (87 + d : U32)))
      Bool.pick(Unit -> String, U32.is_lt(n, 16), u => c ++ acc, u => J.hex.go(j, (n >> 4n : U32), c ++ acc))(Unit{})

def J.hex(+n: U32) -> String:
  J.hex.go(8n, n, "")

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

def Main.usage() -> IO(Unit):
  IO.die(Unit, 1, "usage: bendc [--check-only | --no-check | --js | -o <binary>] <base.bend> <input.bend> | --tokens <file> | --ast <file>")

# The option an argument names (0: none). The driver matches on this number,
# not on string patterns, which the official compiler expands char by char.
def Main.code(+s: String) -> Nat:
  Bool.pick(Nat, Str.eq(s, "--tokens"), 1n, Bool.pick(Nat, Str.eq(s, "--ast"), 2n, Bool.pick(Nat,
    Str.eq(s, "--check-only"), 3n, Bool.pick(Nat, Str.eq(s, "--no-check"), 4n, Bool.pick(Nat, Str.eq(s, "--js"), 5n,
    Bool.pick(Nat, Str.eq(s, "-o"), 6n, 0n))))))

# bendc -o: what bendc writes goes to a C file (Cc.begin), which Cc.end
# compiles into the binary out against the runtime compiled once (rt/cc.c).
def Cc.begin() -> IO(Result<&1, &1, U32 & String, Unit>):
  import "./rt/cc.c"
  import "./rt/cc.js"

def Cc.end(out: String) -> IO(Result<&1, &1, U32 & String, Unit>):
  import "./rt/cc.c"
  import "./rt/cc.js"

# The arguments, past the program's own name (IO.args starts with it).
def Main.args(xs: List<&2, String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case p <> t:
      t

# The compiler's loader, one def (fuel: its calls): LoadSel picks the step.
type LoadSel is Type:
  LDHub{f: Nat, p: String}
  LDImport{f: Nat, dir: String, p: String, hub: Bool}
  LDParsed{f: Nat, dir: String, path: String, r: Result<&2, &2, String, List<&2, Decl>>}
  LDImportsOne{f: Nat, dir: String, p: String, a: String, t: List<&2, Decl>, base: Bool}
  LDImports{f: Nat, dir: String, ds: List<&2, Decl>}
  LDLoad{fuel: Nat, path: String}

def LoadSel.ty(k: LoadSel) -> Type:
  match k:
    case LDHub{f, p}:
      IO(List<&2, Decl>)
    case LDImport{f, dir, p, hub}:
      IO(List<&2, Decl>)
    case LDParsed{f, dir, path, r}:
      IO(List<&2, Decl>)
    case LDImportsOne{f, dir, p, a, t, base}:
      IO(List<&2, Decl>)
    case LDImports{f, dir, ds}:
      IO(List<&2, Decl>)
    case LDLoad{fuel, path}:
      IO(List<&2, Decl>)

def Main.load.go(n: Nat, k: LoadSel) -> LoadSel.ty(k):
  match n:
    case 0n:
      match k:
        case LDHub{f, p}:
          IO.die(List<&2, Decl>, 1, "bendc: out of fuel loading imports")
        case LDImport{f, dir, p, hub}:
          IO.die(List<&2, Decl>, 1, "bendc: out of fuel loading imports")
        case LDParsed{f, dir, path, r}:
          IO.die(List<&2, Decl>, 1, "bendc: out of fuel loading imports")
        case LDImportsOne{f, dir, p, a, t, base}:
          IO.die(List<&2, Decl>, 1, "bendc: out of fuel loading imports")
        case LDImports{f, dir, ds}:
          IO.die(List<&2, Decl>, 1, "bendc: out of fuel loading imports")
        case LDLoad{fuel, path}:
          IO.die(List<&2, Decl>, 1, "bendc: out of fuel loading imports")
    case Succ{+fu}:
      match k:
        # An import by content hash (0x<hash>/path.bend) is fetched from the hub.
        case LDHub{f, +p}:
          do IO<List<&2, Decl>>:
            +lib : String <- Main.lib()
            hr : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_HUB")
            u : Unit <- IO.try(Unit, Hub.ensure(lib, Main.hub.url(hr), p))
            Main.load.go(fu, LDLoad{f, lib ++ "/" ++ p})
        case LDImport{f, +dir, +p, hub}:
          match hub:
            case True{}:
              Main.load.go(fu, LDHub{f, p})
            case False{}:
              Main.load.go(fu, LDLoad{f, Eff.path(dir, p)})
        case LDParsed{f, +dir, +path, r}:
          match r:
            case Fail{e}:
              IO.die(List<&2, Decl>, 1, "bendc: parse error in " ++ path ++ ": " ++ e)
            case Done{+ds}:
              do IO<List<&2, Decl>>:
                imported : List<&2, Decl> <- Main.load.go(fu, LDImports{f, dir, ds})
                return List.append(&2, Decl, imported, Eff.decls(dir, ds))
        case LDImportsOne{+f, +dir, +p, a, t, base}:
          match base:
            case True{}:
              Main.load.go(fu, LDImports{f, dir, t})
            case False{}:
              do IO<List<&2, Decl>>:
                sub : List<&2, Decl> <- Main.load.go(fu, LDImport{f, dir, p, String.starts_with(p, "0x")})
                rest : List<&2, Decl> <- Main.load.go(fu, LDImports{f, dir, t})
                return List.append(&2, Decl, Mod.qualify(a, sub), rest)
        case LDImports{+f, +dir, ds}:
          match ds:
            case Nil{}:
              IO.pure(List<&2, Decl>, Nil{})
            case DImport{+p, a} <> t:
              Main.load.go(fu, LDImportsOne{f, dir, p, a, t, Str.eq(p, "Base")})
            case d <> t:
              Main.load.go(fu, LDImports{f, dir, t})
        # Loads a file and (recursively) the modules it imports; an imported
        # module's names are qualified by its alias.
        case LDLoad{fuel, +path}:
          match fuel:
            case 0n:
              IO.die(List<&2, Decl>, 1, "bendc: imports nested too deeply at " ++ path)
            case 1n+f:
              do IO<List<&2, Decl>>:
                src : String <- IO.read_file(path)
                Main.load.go(fu, LDParsed{f, Mod.dir(path), path, Main.parse(src)})

# Loads a file and (recursively) the modules it imports; an imported
# module's names are qualified by its alias.
def Main.load(fuel: Nat, path: String) -> IO(List<&2, Decl>):
  Main.load.go(Fuel.max(), LDLoad{fuel, path})

# Misc
# ====

def K.fresh.go(st: KSt) -> U32 & KSt:
  KSt{+n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (n, KSt{U32.inc(n), sl, curl, cur, out, fns, todo, frames, errs, flat, memo})

# A fresh block label.
def K.fresh() -> KM(U32):
  st => K.fresh.go(st)

def K.slot.go(st: KSt) -> U32 & KSt:
  KSt{n, +sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (sl, KSt{n, U32.inc(sl), curl, cur, out, fns, todo, frames, errs, flat, memo})

# A fresh frame slot of the function being compiled.
def K.slot() -> KM(U32):
  st => K.slot.go(st)

def K.put.go(d: Doc, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (Unit{}, KSt{n, sl, curl, DCat{cur, d}, out, fns, todo, frames, errs, flat, memo})

# Appends a statement to the current block.
def K.put(d: Doc) -> KM(Unit):
  st => K.put.go(d, st)

def K.putS(s: String) -> KM(Unit):
  K.put(DStr{s})

def K.start.go(+l: U32, st: KSt) -> Unit & KSt:
  KSt{n, sl, +curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (Unit{}, KSt{n, sl, l, DNil{}, DCat{out, K.block_doc(curl, cur)}, fns, todo, frames, errs, flat, memo})

# Ends the current block and starts block l.
def K.start(+l: U32) -> KM(Unit):
  st => K.start.go(l, st)

def S(+k: U32) -> String:
  "KS(" ++ U32.show(k) ++ ")"

def K.frame.go(+l: U32, +size: U32, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (Unit{}, KSt{n, sl, curl, cur, out, fns, todo, Bind{U32.show(l), U32.show((size + 4 : U32))} <> frames, errs, flat, memo})

# Records a function's frame size (header and slots).
def K.frame(+l: U32, +size: U32) -> KM(Unit):
  st => K.frame.go(l, size, st)

def K.take_todo.go(st: KSt) -> List<&2, String> & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (todo, KSt{n, sl, curl, cur, out, fns, Nil{}, frames, errs, flat, memo})

def K.take_todo() -> KM(List<&2, String>):
  st => K.take_todo.go(st)

def K.enter.go(+l: U32, st: KSt) -> U32 & KSt:
  KSt{n, +sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (sl, KSt{n, 0, curl, cur, out, fns, todo, frames, errs, flat, memo})

# Starts compiling a function at label l; answers the outer slot count.
def K.enter(+l: U32) -> KM(U32):
  do KM<U32>:
    +old : U32 <- st => K.enter.go(l, st)
    return old

def K.leave.go(+old: U32, st: KSt) -> U32 & KSt:
  KSt{n, +sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (sl, KSt{n, old, curl, cur, out, fns, todo, frames, errs, flat, memo})

# Ends a function: restores the outer slot count, answers this one's.
def K.leave(+old: U32) -> KM(U32):
  st => K.leave.go(old, st)

# The current block, set aside while a nested function compiles.
def K.save.go(st: KSt) -> (U32 & Doc) & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  ((curl, cur), KSt{n, sl, 0, DNil{}, out, fns, todo, frames, errs, flat, memo})

def K.save() -> KM(U32 & Doc):
  st => K.save.go(st)

def K.restore.go(r: U32 & Doc, st: KSt) -> Unit & KSt:
  (l, d) = r
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (Unit{}, KSt{n, sl, l, d, DCat{out, K.block_doc(curl, cur)}, fns, todo, frames, errs, flat, memo})

def K.restore(r: U32 & Doc) -> KM(Unit):
  st => K.restore.go(r, st)

type KTgt is Data:
  KRet{}
  KSet{slot: U32, merge: U32}

def KSelf.none() -> KSelf:
  KSelf{"", 0, Nil{}}

def K.args.put(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"KARG(nf, " ++ U32.show(i) ++ ") = "}, d, DStr{";\n"}, K.args.put(t, U32.inc(i))])

# Calls the function at entry with args; the value is in a fresh slot.
def K.invoke(+entry: U32, ds: List<&2, Doc>) -> KM(Doc):
  do KM<Doc>:
    +ret : U32 <- K.fresh()
    K.put(Doc.list([DStr{"{ KW nf = KPUSH(" ++ U32.show(ret) ++ ", " ++ U32.show(entry) ++ ");\n"},
      K.args.put(ds, 0), DStr{"KFP = nf; KPC = " ++ U32.show(entry) ++ "; }\n"}]))
    K.start(ret)
    +k : U32 <- K.slot()
    K.putS(S(k) ++ " = KRV;\n")
    return DStr{S(k)}

# Applies a closure to one argument.
def K.apply1(f: Doc, x: Doc) -> KM(Doc):
  do KM<Doc>:
    +ret : U32 <- K.fresh()
    K.put(Doc.list([DStr{"k_call_clo(c, "}, f, DStr{", "}, x, DStr{", " ++ U32.show(ret) ++ ");\n"}]))
    K.start(ret)
    +k : U32 <- K.slot()
    K.putS(S(k) ++ " = KRV;\n")
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

# An effect cannot run on the device.
def K.effect() -> KM(Doc):
  do KM<Doc>:
    K.putS("k_fail(c, KE_FX);\n")
    return DStr{"0"}

def K.commas_pre(ds: List<&2, Doc>) -> List<&2, Doc>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Doc.list([DStr{", "}, d]) <> K.commas_pre(t)

def K.flat.add.go(d: Doc, st: KSt) -> Unit & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (Unit{}, KSt{n, sl, curl, cur, out, fns, todo, frames, errs, DCat{flat, d}, memo})

def K.flat.add(d: Doc) -> KM(Unit):
  st => K.flat.add.go(d, st)

def KX.sig(ps: List<&2, Param>, mask: List<&2, Bool>, +i: U32) -> Env():
  match ps mask:
    case Param{x, m, t} <> pt True{} <> mt:
      Bind{x, "a" ++ U32.show(i)} <> KX.sig(pt, mt, U32.inc(i))
    case Param{x, m, t} <> pt False{} <> mt:
      Bind{x, "0"} <> KX.sig(pt, mt, i)
    case pl ml:
      Nil{}

def KX.cparams(+n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      ", KW a" ++ U32.show(i) ++ KX.cparams(m, U32.inc(i))

# The names an expression calls. A node's lists are walked one element at
# a time, the rest on the same node (smaller); top: the node's own head
# (a call's function) is still to walk.
def K.heads.go(e: Expr, +acc: List<&2, String>, top: Bool) -> List<&2, String>:
  match e:
    case ECall{EVar{+f}, args}:
      match args:
        case Nil{}:
          Bool.pick(List<&2, String>, top, f <> acc, acc)
        case a <> t:
          K.heads.go(ECall{EVar{f}, t}, K.heads.go(a, Bool.pick(List<&2, String>, top, f <> acc, acc), True{}), False{})
    case ECall{+f, args}:
      match args:
        case Nil{}:
          Bool.pick(Unit -> List<&2, String>, top, u => K.heads.go(f, acc, True{}), u => acc)(Unit{})
        case a <> t:
          K.heads.go(ECall{f, t}, K.heads.go(a, Bool.pick(Unit -> List<&2, String>, top,
            u => K.heads.go(f, acc, True{}), u => acc)(Unit{}), True{}), False{})
    case ECtor{n, args}:
      match args:
        case Nil{}:
          acc
        case a <> t:
          K.heads.go(ECtor{n, t}, K.heads.go(a, acc, True{}), True{})
    case ELam{p, b}:
      K.heads.go(b, acc, True{})
    case ELet{p, v, b}:
      K.heads.go(b, K.heads.go(v, acc, True{}), True{})
    case EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          K.heads.go(EMatch{t, cases}, K.heads.go(a, acc, True{}), True{})
        case Nil{}:
          match cases:
            case c <> t:
              K.heads.go(EMatch{Nil{}, t}, K.heads.go(c, acc, True{}), True{})
            case Nil{}:
              acc
    case ECase{ps, b}:
      K.heads.go(b, acc, True{})
    case ESucc{k, x}:
      K.heads.go(x, acc, True{})
    case EOp{op, a, b}:
      K.heads.go(b, K.heads.go(a, acc, True{}), True{})
    case EAnn{x, t}:
      K.heads.go(x, acc, True{})
    case other:
      acc

def K.heads(e: Expr, acc: List<&2, String>) -> List<&2, String>:
  K.heads.go(e, acc, True{})

def K.loops.body(d: Decl) -> List<&2, String>:
  match d:
    case DDef{n, ps, body, ret}:
      K.heads(body, Nil{})
    case other:
      Nil{}


# The loop analysis, one def (fuel: its calls, which reach other defs):
# KLoopSel picks the step.
type KLoopSel is Type:
  KLCallee{g: G, name: String, h: String, t: List<&2, String>, info: DInfo}
  KLAny{g: G, name: String, hs: List<&2, String>}
  KLOrIf{a: Bool, g: G, name: String, t: List<&2, String>}
  KLOr{g: G, name: String, h: String, t: List<&2, String>}
  KLMemo{g: G, name: String, m: Maybe<&2, String>}
  KLLoops{g: G, name: String}

def KLoopSel.ty(k: KLoopSel) -> Type:
  match k:
    case KLCallee{g, name, h, t, info}:
      KM(Bool)
    case KLAny{g, name, hs}:
      KM(Bool)
    case KLOrIf{a, g, name, t}:
      KM(Bool)
    case KLOr{g, name, h, t}:
      KM(Bool)
    case KLMemo{g, name, m}:
      KM(Bool)
    case KLLoops{g, name}:
      KM(Bool)

def K.loops.go(n: Nat, k: KLoopSel) -> KLoopSel.ty(k):
  match n:
    case 0n:
      match k:
        case KLCallee{g, name, h, t, info}:
          K.out(Bool, False{})
        case KLAny{g, name, hs}:
          K.out(Bool, False{})
        case KLOrIf{a, g, name, t}:
          K.out(Bool, False{})
        case KLOr{g, name, h, t}:
          K.out(Bool, False{})
        case KLMemo{g, name, m}:
          K.out(Bool, False{})
        case KLLoops{g, name}:
          K.out(Bool, False{})
    case Succ{+fu}:
      match k:
        case KLCallee{+g, +name, +h, +t, info}:
          DInfo{kind, mask} = info
          KM.if(Bool, U32.is_zero(kind), K.loops.go(fu, KLOr{g, name, h, t}), K.loops.go(fu, KLAny{g, name, t}))
        case KLAny{+g, +name, hs}:
          match hs:
            case Nil{}:
              KM.pure(Bool, False{})
            case +h <> t:
              KM.if(Bool, Str.eq(h, name), KM.pure(Bool, True{}), K.loops.go(fu, KLCallee{g, name, h, t, G.def(g, h)}))
        case KLOrIf{a, +g, +name, t}:
          match a:
            case True{}:
              KM.pure(Bool, True{})
            case False{}:
              K.loops.go(fu, KLAny{g, name, t})
        case KLOr{+g, +name, +h, t}:
          do KM<Bool>:
            a : Bool <- K.loops.go(fu, KLLoops{g, h})
            K.loops.go(fu, KLOrIf{a, g, name, t})
        case KLMemo{+g, +name, m}:
          match m:
            case Some{v}:
              KM.pure(Bool, Str.eq(v, "1"))
            case None{}:
              do KM<Bool>:
                K.memo.put("%loop " ++ name, "0")
                +r : Bool <- K.loops.go(fu, KLAny{g, name, K.loops.body(G.body(g, name))})
                K.memo.put("%loop " ++ name, Bool.pick(String, r, "1", "0"))
                return r
        # Whether a flat def loops (calls itself, or a flat def that does): its
        # calls can take long, so the kernel runs them with the SIMD group (PC_KQ).
        case KLLoops{+g, +name}:
          do KM<Bool>:
            m : Maybe<&2, String> <- K.memo.get("%loop " ++ name)
            K.loops.go(fu, KLMemo{g, name, m})

# Whether a flat def loops (calls itself, or a flat def that does): its
# calls can take long, so the kernel runs them with the SIMD group (PC_KQ).
def K.loops(g: G, name: String) -> KM(Bool):
  K.loops.go(Fuel.max(), KLLoops{g, name})
def KQ.case.args(+n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      ", c->kqa[" ++ U32.show(i) ++ "]" ++ KQ.case.args(m, U32.inc(i))

def K.kx.id.memo(+name: String, +n: Nat, m: Maybe<&2, String>) -> KM(U32):
  match m:
    case Some{v}:
      KM.pure(U32, Maybe.default(&2, U32, U32.read(v), 0))
    case None{}:
      do KM<U32>:
        +id : U32 <- K.fresh()
        K.memo.put("%kxid " ++ name, U32.show(id))
        K.memo.put("%kqcase", "case " ++ U32.show(id) ++ ":\nreturn KX_" ++ Gen.mangle(name) ++ "(c" ++ KQ.case.args(n, 0) ++
          ");\n")
        return id

# The k_kq case of a looping flat def (one per def).
def K.kx.id(+name: String, +n: Nat) -> KM(U32):
  do KM<U32>:
    m : Maybe<&2, String> <- K.memo.get("%kxid " ++ name)
    K.kx.id.memo(name, n, m)

def KQ.req(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"c->kqa[" ++ U32.show(i) ++ "] = "}, d, DStr{";\n"}, KQ.req(t, U32.inc(i))])

def K.call.flat.k.pick(gather: Bool, +g: G, +name: String, +ks: List<&2, Doc>) -> KM(Doc):
  match gather:
    case True{}:
      do KM<Doc>:
        +id : U32 <- K.kx.id(name, U32.to_nat(Gen.len(ks)))
        +ret : U32 <- K.fresh()
        +k : U32 <- K.slot()
        K.put(Doc.list([DStr{"c->kq = " ++ U32.show(id) ++ "; c->kqret = " ++ U32.show(ret) ++ "; c->kqfb = 0;\n"},
          KQ.req(ks, 0), DStr{"KPC = PC_KQ;\n"}]))
        K.start(ret)
        K.putS(S(k) ++ " = KRV;\n")
        return DStr{S(k)}
    case False{}:
      KM.pure(Doc, Doc.list([DStr{"KX_" ++ Gen.mangle(name) ++ "(c"}, Doc.list(K.commas_pre(ks)), DStr{")"}]))

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
    case 4n:
      KM.pure(Doc, Doc.list([DStr{"k_nat_add(c, "}, Doc.list(ds), DStr{", 1)"}]))
    case 5n+p:
      KM.pure(Doc, DStr{"k_arr(c)"})

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
  KSt{m, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (n, KSt{m, (sl + n : U32), curl, cur, out, fns, todo, frames, errs, flat, memo})

# Takes n slots (a function's parameters); answers n.
def K.slots(+n: U32) -> KM(U32):
  st => K.slots.go(n, st)

# An Array pattern's variables, bound to 0: the device runs no Array
# operation (k_arr fails the call over to the CPU).
def K.pat.zeros(xs: List<&2, String>, r: PatR) -> PatR:
  match xs:
    case Nil{}:
      r
    case x <> t:
      K.pat.zeros(t, Gen.pat.var(x, "0", r))


# The pattern compiler, one def (fuel: its calls): KPatSel picks the step.
# Out of fuel, a condition that names nothing fails the C compile.
type KPatSel is Type:
  KPFields{g: G, args: List<&2, Pat>, path: String, i: U32, r: PatR}
  KPKind{g: G, kind: Nat, tag: U32, single: Bool, args: List<&2, Pat>, path: String, r: PatR}
  KPCtor{g: G, info: Maybe<&2, CInfo>, name: String, args: List<&2, Pat>, path: String, r: PatR}
  KPPat{g: G, p: Pat, path: String, r: PatR}

def KPatSel.ty(k: KPatSel) -> Type:
  match k:
    case KPFields{g, args, path, i, r}:
      PatR
    case KPKind{g, kind, tag, single, args, path, r}:
      PatR
    case KPCtor{g, info, name, args, path, r}:
      PatR
    case KPPat{g, p, path, r}:
      PatR

def K.pat.go(n: Nat, k: KPatSel) -> KPatSel.ty(k):
  match n:
    case 0n:
      match k:
        case KPFields{g, args, path, i, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case KPKind{g, kind, tag, single, args, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case KPCtor{g, info, name, args, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case KPPat{g, p, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
    case Succ{+fu}:
      match k:
        case KPFields{+g, args, +path, +i, r}:
          match args:
            case Nil{}:
              r
            case h <> t:
              K.pat.go(fu, KPFields{g, t, path, U32.inc(i), K.pat.go(fu, KPPat{g, h,
                Bool.pick(String, U32.is_eq(i, 99), path, "KFLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), r})})
        case KPKind{+g, kind, +tag, +single, args, +path, r}:
          match kind:
            case 0n:
              K.pat.go(fu, KPFields{g, args, path, 0, Gen.pat.tag(single, "KTAG(" ++ path ++ ") == " ++ U32.show(tag), r)})
            case 1n:
              Gen.pat.tag(single, "(" ++ path ++ ") == KIMM(" ++ U32.show(tag) ++ ")", r)
            case 2n:
              K.pat.go(fu, KPFields{g, args, path, 99, r})
            case 3n:
              Gen.pat.cond("(" ++ path ++ ") == 0", r)
            case 4n:
              K.pat.go(fu, KPFields{g, args, "((" ++ path ++ ") - 1)", 99, Gen.pat.cond("k_nz(c, " ++ path ++ ")", r)})
            case 5n+p:
              K.pat.zeros(Pats.vars(args, Nil{}), Gen.pat.cond("k_arr(c)", r))
        case KPCtor{+g, info, name, args, +path, r}:
          match info:
            case None{}:
              Gen.pat.cond("0", r)
            case Some{CInfo{+tag, ar, +kind, +single}}:
              K.pat.go(fu, KPKind{g, U32.to_nat(kind), tag, single, args, path, r})
        case KPPat{+g, p, +path, r}:
          match p:
            case PVar{x}:
              Gen.pat.var(x, path, r)
            case PCtor{+name, args}:
              K.pat.go(fu, KPCtor{g, G.ctor(g, name), name, args, path, r})
            case PNat{n}:
              Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
            case PSucc{+k, q}:
              K.pat.go(fu, KPPat{g, q, "((" ++ path ++ ") - " ++ U32.show(k) ++ ")", Gen.pat.cond("k_nge(c, " ++ path ++ ", " ++ U32.show(k) ++ ")", r)})
            case PNum{n}:
              Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
            case PFlt{s}:
              Gen.pat.cond("(" ++ path ++ ") == KUF(" ++ s ++ "f)", r)

def K.pat(g: G, p: Pat, path: String, r: PatR) -> PatR:
  K.pat.go(Fuel.max(), KPPat{g, p, path, r})
def K.pats(+g: G, ps: List<&2, Pat>, paths: List<&2, String>, r: PatR) -> PatR:
  match ps paths:
    case p <> pt c <> ct:
      K.pats(g, pt, ct, K.pat(g, p, c, r))
    case pl cl:
      r

def K.ret(t: KTgt, d: Doc) -> KM(Unit):
  match t:
    case KRet{}:
      K.put(Doc.list([DStr{"KRET("}, d, DStr{");\n"}]))
    case KSet{k, m}:
      K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\nKPC = " ++ U32.show(m) ++ ";\n"}]))

def K.tail.set(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{S(i) ++ " = "}, d, DStr{"; "}, K.tail.set(t, U32.inc(i))])

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

def KQ.req.args(n: Nat, +i: U32) -> List<&2, Doc>:
  match n:
    case 0n:
      Nil{}
    case 1n+m:
      DStr{"c->kqa[" ++ U32.show(i) ++ "]"} <> KQ.req.args(m, U32.inc(i))

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

type KCase is Data:
  KCase{label: U32, conds: List<&2, String>, env: Env(), body: Expr}

def K.cases(+g: G, +env: Env(), +cs: List<&2, String>, cases: List<&2, Expr>) -> KM(List<&2, KCase>):
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
      Doc.list([DStr{"if (" ++ Gen.and(conds) ++ ") { KPC = " ++ U32.show(l) ++ "; } else "}, K.dispatch(t)])

def K.doc_strs(ds: List<&2, Doc>) -> List<&2, String>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Doc.flat(d) <> K.doc_strs(t)

def K.sig.env(ps: List<&2, Param>, mask: List<&2, Bool>, +i: U32) -> Env():
  match ps mask:
    case Param{x, m, t} <> pt True{} <> mt:
      Bind{x, S(i)} <> K.sig.env(pt, mt, U32.inc(i))
    case Param{x, m, t} <> pt False{} <> mt:
      Bind{x, "0"} <> K.sig.env(pt, mt, i)
    case pl ml:
      Nil{}

def K.cap.begin.go(st: KSt) -> Doc & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (out, KSt{n, sl, curl, cur, DNil{}, fns, todo, frames, errs, flat, memo})

# Sets the kernel's finished blocks aside: the blocks made until K.cap.take
# are a KQ_ function's.
def K.cap.begin() -> KM(Doc):
  st => K.cap.begin.go(st)

def K.cap.take.go(old: Doc, st: KSt) -> Doc & KSt:
  KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo} = st
  (out, KSt{n, sl, curl, cur, old, fns, todo, frames, errs, flat, memo})

# The blocks made since K.cap.begin, with the kernel's put back.
def K.cap.take(old: Doc) -> KM(Doc):
  st => K.cap.take.go(old, st)

def KQ.params(+n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      ", KW p" ++ U32.show(i) ++ KQ.params(m, U32.inc(i))

def KQ.init(+n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "KW A" ++ U32.show(i) ++ " = p" ++ U32.show(i) ++ ";\n" ++ KQ.init(m, U32.inc(i))

def KX.v(+k: U32) -> String:
  "x" ++ U32.show(k)

def KQ.sig(ps: List<&2, Param>, mask: List<&2, Bool>, +k: U32, +i: U32) -> Env():
  match ps mask:
    case Param{x, m, t} <> pt True{} <> mt:
      Bind{x, KX.v(k) ++ "_" ++ U32.show(i)} <> KQ.sig(pt, mt, k, U32.inc(i))
    case Param{x, m, t} <> pt False{} <> mt:
      Bind{x, "0"} <> KQ.sig(pt, mt, k, i)
    case pl ml:
      Nil{}

def KQ.entry(+k: U32, +n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "KW " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ " = A" ++ U32.show(i) ++ "; " ++ KQ.entry(k, m, U32.inc(i))

# A def's wrapper: every parameter a slot, calling the def with the kept ones.
def K.wrap.args(mask: List<&2, Bool>, +i: U32) -> List<&2, Doc>:
  match mask:
    case Nil{}:
      Nil{}
    case True{} <> t:
      DStr{S(i)} <> K.wrap.args(t, U32.inc(i))
    case False{} <> t:
      K.wrap.args(t, U32.inc(i))

def K.slot.docs.go(n: Nat, +i: U32) -> List<&2, Doc>:
  match n:
    case 0n:
      Nil{}
    case 1n+m:
      DStr{S(i)} <> K.slot.docs.go(m, U32.inc(i))

def K.slot.docs(+n: U32, +i: U32) -> List<&2, Doc>:
  K.slot.docs.go(U32.to_nat(n), i)

# Values in fresh locals, then a node of them (a field may allocate too).
def KX.temps(ds: List<&2, Doc>, +k: U32, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"KW " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ " = "}, d, DStr{"; "}, KX.temps(t, k, U32.inc(i))])

def KX.fields.go(n: Nat, +k: U32, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "c->H[KIX(c, " ++ KX.v(k) ++ ") + " ++ U32.show(U32.inc(i)) ++ "] = " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ "; " ++
        KX.fields.go(m, k, U32.inc(i))

def KX.fields(+n: U32, +k: U32, +i: U32) -> String:
  KX.fields.go(U32.to_nat(n), k, i)

def KX.node(+tag: U32, +ds: List<&2, Doc>) -> KM(Doc):
  +n = Gen.len(ds)
  do KM<Doc>:
    +k : U32 <- K.fresh()
    return Doc.list([DStr{"({ "}, KX.temps(ds, k, 0), DStr{"KW " ++ KX.v(k) ++ " = k_node(c, " ++ U32.show(tag) ++ ", " ++
      U32.show(n) ++ "); " ++ KX.fields(n, k, 0) ++ KX.v(k) ++ "; })"}])

def KX.ctor.kind(+tag: U32, kind: Nat, ds: List<&2, Doc>) -> KM(Doc):
  match kind:
    case 0n:
      KX.node(tag, ds)
    case 1n:
      KM.pure(Doc, DStr{"KIMM(" ++ U32.show(tag) ++ ")"})
    case 2n:
      KM.pure(Doc, Doc.list(ds))
    case 3n:
      KM.pure(Doc, DStr{"0"})
    case 4n:
      KM.pure(Doc, Doc.list([DStr{"k_nat_add(c, "}, Doc.list(ds), DStr{", 1)"}]))
    case 5n+p:
      KM.pure(Doc, DStr{"k_arr(c)"})

def KX.ret(t: KTgt, d: Doc) -> Doc:
  match t:
    case KRet{}:
      Doc.list([DStr{"return "}, d, DStr{";\n"}])
    case KSet{k, m}:
      Doc.list([DStr{KX.v(k) ++ " = "}, d, DStr{";\n"}])

def KX.scrs.put(+c: String, d: Doc, r: List<&2, String> & Doc) -> List<&2, String> & Doc:
  (cs, code) = r
  (c <> cs, Doc.list([DStr{"KW " ++ c ++ " = "}, d, DStr{";\n"}, code]))

def KX.tail.set(+k: U32, +n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "a" ++ U32.show(i) ++ " = " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ "; " ++ KX.tail.set(k, m, U32.inc(i))


# The flat compiler (KX_ functions), one def (fuel: its calls, which reach
# other defs): KXSel picks the step.
type KXSel is Type:
  KXSDefGo{g: G, name: String, mask: List<&2, Bool>, d: Decl}
  KXSDef{g: G, name: String, info: DInfo}
  KXSKFlatNeedMemo{g: G, name: String, m: Maybe<&2, String>}
  KXSKFlatNeed{g: G, name: String}
  KXSKCallFlat{g: G, name: String, ks: List<&2, Doc>, flat: Bool}
  KXSExprs{g: G, env: Env(), xs: List<&2, Expr>}
  KXSCtor{g: G, env: Env(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Expr>}
  KXSCallKind{g: G, name: String, kind: Nat, ks: List<&2, Doc>}
  KXSCallSplit{g: G, env: Env(), name: String, kind: Nat, s: Split}
  KXSCallDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Expr>}
  KXSVarGlobal{g: G, name: String, info: DInfo}
  KXSVarFound{g: G, name: String, m: Maybe<&2, String>}
  KXSBlock{g: G, env: Env(), e: Expr}
  KXSExpr{g: G, env: Env(), e: Expr}
  KXSScrs{g: G, env: Env(), xs: List<&2, Expr>}
  KXSCases{g: G, env: Env(), self: KSelf, tgt: KTgt, cs: List<&2, String>, cases: List<&2, Expr>}
  KXSMatchGo{g: G, env: Env(), self: KSelf, tgt: KTgt, r: List<&2, String> & Doc, cases: List<&2, Expr>}
  KXSMatch{g: G, env: Env(), self: KSelf, tgt: KTgt, scrs: List<&2, Expr>, cases: List<&2, Expr>}
  KXSLet{g: G, env: Env(), self: KSelf, tgt: KTgt, p: Pat, v: Expr, body: Expr}
  KXSTail{g: G, env: Env(), s: Split}
  KXSStmtCall{g: G, env: Env(), self: KSelf, tgt: KTgt, name: String, args: List<&2, Expr>, tail: Bool}
  KXSStmt{g: G, env: Env(), self: KSelf, tgt: KTgt, e: Expr}

def KXSel.ty(k: KXSel) -> Type:
  match k:
    case KXSDefGo{g, name, mask, d}:
      KM(Unit)
    case KXSDef{g, name, info}:
      KM(Unit)
    case KXSKFlatNeedMemo{g, name, m}:
      KM(Unit)
    case KXSKFlatNeed{g, name}:
      KM(Unit)
    case KXSKCallFlat{g, name, ks, flat}:
      KM(Doc)
    case KXSExprs{g, env, xs}:
      KM(List<&2, Doc>)
    case KXSCtor{g, env, name, info, args}:
      KM(Doc)
    case KXSCallKind{g, name, kind, ks}:
      KM(Doc)
    case KXSCallSplit{g, env, name, kind, s}:
      KM(Doc)
    case KXSCallDef{g, env, name, info, args}:
      KM(Doc)
    case KXSVarGlobal{g, name, info}:
      KM(Doc)
    case KXSVarFound{g, name, m}:
      KM(Doc)
    case KXSBlock{g, env, e}:
      KM(Doc)
    case KXSExpr{g, env, e}:
      KM(Doc)
    case KXSScrs{g, env, xs}:
      KM(List<&2, String> & Doc)
    case KXSCases{g, env, self, tgt, cs, cases}:
      KM(Doc)
    case KXSMatchGo{g, env, self, tgt, r, cases}:
      KM(Doc)
    case KXSMatch{g, env, self, tgt, scrs, cases}:
      KM(Doc)
    case KXSLet{g, env, self, tgt, p, v, body}:
      KM(Doc)
    case KXSTail{g, env, s}:
      KM(Doc)
    case KXSStmtCall{g, env, self, tgt, name, args, tail}:
      KM(Doc)
    case KXSStmt{g, env, self, tgt, e}:
      KM(Doc)

def KX.go(n: Nat, k: KXSel) -> KXSel.ty(k):
  match n:
    case 0n:
      match k:
        case KXSDefGo{g, name, mask, d}:
          K.out(Unit, Unit{})
        case KXSDef{g, name, info}:
          K.out(Unit, Unit{})
        case KXSKFlatNeedMemo{g, name, m}:
          K.out(Unit, Unit{})
        case KXSKFlatNeed{g, name}:
          K.out(Unit, Unit{})
        case KXSKCallFlat{g, name, ks, flat}:
          K.out(Doc, DNil{})
        case KXSExprs{g, env, xs}:
          K.out(List<&2, Doc>, Nil{})
        case KXSCtor{g, env, name, info, args}:
          K.out(Doc, DNil{})
        case KXSCallKind{g, name, kind, ks}:
          K.out(Doc, DNil{})
        case KXSCallSplit{g, env, name, kind, s}:
          K.out(Doc, DNil{})
        case KXSCallDef{g, env, name, info, args}:
          K.out(Doc, DNil{})
        case KXSVarGlobal{g, name, info}:
          K.out(Doc, DNil{})
        case KXSVarFound{g, name, m}:
          K.out(Doc, DNil{})
        case KXSBlock{g, env, e}:
          K.out(Doc, DNil{})
        case KXSExpr{g, env, e}:
          K.out(Doc, DNil{})
        case KXSScrs{g, env, xs}:
          K.out(List<&2, String> & Doc, (Nil{}, DNil{}))
        case KXSCases{g, env, self, tgt, cs, cases}:
          K.out(Doc, DNil{})
        case KXSMatchGo{g, env, self, tgt, r, cases}:
          K.out(Doc, DNil{})
        case KXSMatch{g, env, self, tgt, scrs, cases}:
          K.out(Doc, DNil{})
        case KXSLet{g, env, self, tgt, p, v, body}:
          K.out(Doc, DNil{})
        case KXSTail{g, env, s}:
          K.out(Doc, DNil{})
        case KXSStmtCall{g, env, self, tgt, name, args, tail}:
          K.out(Doc, DNil{})
        case KXSStmt{g, env, self, tgt, e}:
          K.out(Doc, DNil{})
    case Succ{+fu}:
      match k:
        case KXSDefGo{+g, +name, +mask, d}:
          match d:
            case DDef{n, ps, body, ret}:
              +head = "KINLINE KW KX_" ++ Gen.mangle(name) ++ "(KTHR KCtx *c" ++ KX.cparams(U32.to_nat(K.kept(mask)), 0) ++ ")"
              do KM<Unit>:
                b : Doc <- KX.go(fu, KXSStmt{g, KX.sig(ps, mask, 0), KSelf{name, 0, mask}, KRet{}, R.ops(body, "Nat")})
                K.flat.add(Doc.list([DStr{head ++ " {\nfor (;;) {\n"}, b, DStr{"}\n}\n"}]))
            case other:
              KM.pure(Unit, Unit{})
        case KXSDef{+g, +name, info}:
          DInfo{kind, +mask} = info
          KX.go(fu, KXSDefGo{g, name, mask, G.body(g, name)})
        case KXSKFlatNeedMemo{+g, +name, m}:
          match m:
            case Some{v}:
              KM.pure(Unit, Unit{})
            case None{}:
              do KM<Unit>:
                K.memo.put("%emit " ++ name, "1")
                KX.go(fu, KXSDef{g, name, G.def(g, name)})
        # Emits a flat def's function (once; its callees come first).
        case KXSKFlatNeed{+g, +name}:
          do KM<Unit>:
            m : Maybe<&2, String> <- K.memo.get("%emit " ++ name)
            KX.go(fu, KXSKFlatNeedMemo{g, name, m})
        case KXSKCallFlat{+g, +name, ks, flat}:
          match flat:
            case True{}:
              do KM<Doc>:
                KX.go(fu, KXSKFlatNeed{g, name})
                return Doc.list([DStr{"KX_" ++ Gen.mangle(name) ++ "(c"}, Doc.list(K.commas_pre(ks)), DStr{")"}])
            case False{}:
              do KM<Doc>:
                +e : U32 <- K.fn(name)
                K.invoke(e, ks)
        case KXSExprs{+g, +env, xs}:
          match xs:
            case Nil{}:
              KM.pure(List<&2, Doc>, Nil{})
            case h <> t:
              do KM<List<&2, Doc>>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, h})
                ds : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, t})
                return d <> ds
        case KXSCtor{+g, +env, name, info, args}:
          match info:
            case None{}:
              do KM<Doc>:
                K.error("unknown constructor: " ++ name)
                return DStr{"0"}
            case Some{CInfo{tag, ar, kind, single}}:
              do KM<Doc>:
                ds : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, args})
                KX.ctor.kind(tag, U32.to_nat(kind), ds)
        case KXSCallKind{+g, +name, kind, ks}:
          match kind:
            case 3n:
              KM.pure(Doc, DStr{"0"})
            case 2n:
              KM.pure(Doc, Doc.list([DStr{"K" ++ Gen.f(name) ++ "(c"}, Doc.list(K.commas_pre(ks)), DStr{")"}]))
            case other:
              KX.go(fu, KXSKCallFlat{g, name, ks, True{}})
        case KXSCallSplit{+g, +env, +name, kind, s}:
          Split{kept, all, extra, full} = s
          do KM<Doc>:
            ks : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, kept})
            KX.go(fu, KXSCallKind{g, name, kind, ks})
        case KXSCallDef{+g, +env, +name, info, args}:
          DInfo{kind, mask} = info
          KX.go(fu, KXSCallSplit{g, env, name, U32.to_nat(kind), Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case KXSVarGlobal{+g, +name, info}:
          DInfo{kind, mask} = info
          KX.go(fu, KXSCallKind{g, name, U32.to_nat(kind), Nil{}})
        case KXSVarFound{+g, +name, m}:
          match m:
            case Some{c}:
              KM.pure(Doc, DStr{c})
            case None{}:
              KM.if(Doc, Str.eq(name, "_"), KM.pure(Doc, DStr{"0"}), KX.go(fu, KXSVarGlobal{g, name, G.def(g, name)}))
        case KXSBlock{+g, +env, e}:
          do KM<Doc>:
            +k : U32 <- K.fresh()
            b : Doc <- KX.go(fu, KXSStmt{g, env, KSelf.none(), KSet{k, 0}, e})
            return Doc.list([DStr{"({ KW " ++ KX.v(k) ++ ";\n"}, b, DStr{KX.v(k) ++ "; })"}])
        case KXSExpr{+g, +env, e}:
          match e:
            case EVar{+name}:
              KX.go(fu, KXSVarFound{g, name, Env.find(env, name)})
            case ENum{n}:
              KM.pure(Doc, DStr{U32.show(n) ++ "u"})
            case ENat{n}:
              KM.pure(Doc, DStr{U32.show(n) ++ "u"})
            case EFlt{s}:
              KM.pure(Doc, DStr{"KUF(" ++ s ++ "f)"})
            case EStr{s}:
              KM.pure(Doc, Doc.list([DStr{"({ KW r = KIMM(0);\n"}, K.str.cells(Str.codes32(s)), DStr{"r; })"}]))
            case ECall{EVar{+f}, args}:
              KX.go(fu, KXSCallDef{g, env, f, G.def(g, f), args})
            case ECtor{+name, args}:
              KX.go(fu, KXSCtor{g, env, name, G.ctor(g, name), args})
            case ELet{p, v, body}:
              KX.go(fu, KXSBlock{g, env, ELet{p, v, body}})
            case EMatch{scrs, cases}:
              KX.go(fu, KXSBlock{g, env, EMatch{scrs, cases}})
            case ESucc{k, x}:
              do KM<Doc>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, x})
                return Doc.list([DStr{"k_nat_add(c, "}, d, DStr{", " ++ U32.show(k) ++ ")"}])
            case ETy{n, targs}:
              KM.pure(Doc, DStr{"0"})
            case other:
              do KM<Doc>:
                K.error("not flat: " ++ Expr.show(other))
                return DStr{"0"}
        # Scrutinees and let values go to fresh locals.
        case KXSScrs{+g, +env, xs}:
          match xs:
            case Nil{}:
              KM.pure(List<&2, String> & Doc, (Nil{}, DNil{}))
            case h <> t:
              do KM<List<&2, String> & Doc>:
                +k : U32 <- K.fresh()
                d : Doc <- KX.go(fu, KXSExpr{g, env, h})
                r : List<&2, String> & Doc <- KX.go(fu, KXSScrs{g, env, t})
                return KX.scrs.put(KX.v(k), d, r)
        case KXSCases{+g, +env, +self, +tgt, +cs, cases}:
          match cases:
            case Nil{}:
              KM.pure(Doc, DStr{"{ k_fail(c, KE_MATCH); return 0; }\n"})
            case ECase{ps, body} <> t:
              +pr = K.pats(g, ps, cs, PatR{Nil{}, Nil{}})
              do KM<Doc>:
                b : Doc <- KX.go(fu, KXSStmt{g, List.append(&2, Bind, PatR.binds(pr), env), self, tgt, body})
                rest : Doc <- KX.go(fu, KXSCases{g, env, self, tgt, cs, t})
                return Doc.list([DStr{"if (" ++ Gen.and(List.reverse(&2, String, PatR.conds(pr))) ++ ") {\n"}, b, DStr{"} else "},
                  rest])
            case other <> t:
              KX.go(fu, KXSCases{g, env, self, tgt, cs, t})
        case KXSMatchGo{+g, +env, +self, +tgt, r, cases}:
          (cs, code) = r
          do KM<Doc>:
            b : Doc <- KX.go(fu, KXSCases{g, env, self, tgt, cs, cases})
            return DCat{code, b}
        case KXSMatch{+g, +env, +self, +tgt, scrs, cases}:
          do KM<Doc>:
            r : List<&2, String> & Doc <- KX.go(fu, KXSScrs{g, env, scrs})
            KX.go(fu, KXSMatchGo{g, env, self, tgt, r, cases})
        case KXSLet{+g, +env, +self, +tgt, p, v, body}:
          do KM<Doc>:
            +k : U32 <- K.fresh()
            d : Doc <- KX.go(fu, KXSExpr{g, env, v})
            b : Doc <- KX.go(fu, KXSStmt{g, List.append(&2, Bind, PatR.binds(K.pat(g, p, KX.v(k), PatR{Nil{}, Nil{}})), env), self, tgt,
              body})
            return Doc.list([DStr{"KW " ++ KX.v(k) ++ " = "}, d, DStr{";\n"}, b])
        # A self tail call: the new arguments, then back to the top of the loop.
        # (No error check in the loop: reading c->err there keeps the lane's context
        # in memory, 3x slower. An error still stops the call when it returns.)
        case KXSTail{+g, +env, s}:
          Split{kept, all, extra, full} = s
          do KM<Doc>:
            +k : U32 <- K.fresh()
            +ds : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, kept})
            return Doc.list([DStr{"{ "}, KX.temps(ds, k, 0), DStr{KX.tail.set(k, U32.to_nat(Gen.len(ds)), 0) ++
              "continue; }\n"}])
        case KXSStmtCall{+g, +env, +self, +tgt, +name, args, tail}:
          match tail:
            case True{}:
              KX.go(fu, KXSTail{g, env, Gen.split(KSelf.mask(self), args, Split{Nil{}, Nil{}, Nil{}, False{}})})
            case False{}:
              do KM<Doc>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, ECall{EVar{name}, args}})
                return KX.ret(tgt, d)
        case KXSStmt{+g, +env, +self, +tgt, e}:
          match e:
            case ELet{p, v, body}:
              KX.go(fu, KXSLet{g, env, self, tgt, p, v, body})
            case EMatch{scrs, cases}:
              KX.go(fu, KXSMatch{g, env, self, tgt, scrs, cases})
            case ECall{EVar{+name}, +args}:
              KX.go(fu, KXSStmtCall{g, env, self, tgt, name, args, KSelf.is_tail(env, self, tgt, name, args)})
            case other:
              do KM<Doc>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, other})
                return KX.ret(tgt, d)

# Emits a flat def's function (once; its callees come first).
def K.flat.need(g: G, name: String) -> KM(Unit):
  KX.go(Fuel.max(), KXSKFlatNeed{g, name})

def K.call.flat(g: G, name: String, ks: List<&2, Doc>, flat: Bool) -> KM(Doc):
  KX.go(Fuel.max(), KXSKCallFlat{g, name, ks, flat})

def KX.exprs(g: G, env: Env(), xs: List<&2, Expr>) -> KM(List<&2, Doc>):
  KX.go(Fuel.max(), KXSExprs{g, env, xs})

def KX.expr(g: G, env: Env(), e: Expr) -> KM(Doc):
  KX.go(Fuel.max(), KXSExpr{g, env, e})

# Scrutinees and let values go to fresh locals.
def KX.scrs(g: G, env: Env(), xs: List<&2, Expr>) -> KM(List<&2, String> & Doc):
  KX.go(Fuel.max(), KXSScrs{g, env, xs})

# A flat def called from the kernel's blocks.
def K.call.flat.k(+g: G, +name: String, +ks: List<&2, Doc>, flat: Bool) -> KM(Doc):
  match flat:
    case True{}:
      do KM<Doc>:
        K.flat.need(g, name)
        lp : Bool <- K.loops(g, name)
        K.call.flat.k.pick(Bool.and(lp, U32.is_le(Gen.len(ks), 8)), g, name, ks)
    case False{}:
      K.call.flat(g, name, ks, False{})

# A full call: natives are expressions, effects fail, flat defs are
# functions, other defs are called through frames.
def K.call.kind(+g: G, +name: String, kind: Nat, ks: List<&2, Doc>) -> KM(Doc):
  match kind:
    case 3n:
      KM.pure(Doc, DStr{"0"})
    case 2n:
      KM.pure(Doc, Doc.list([DStr{"K" ++ Gen.f(name) ++ "(c"}, Doc.list(K.commas_pre(ks)), DStr{")"}]))
    case 1n:
      K.effect()
    case other:
      do KM<Doc>:
        flat : Bool <- K.isflat(g, name)
        K.call.flat.k(g, name, ks, flat)

def K.call.zero(+g: G, +name: String) -> KM(Doc):
  K.call.kind(g, name, 0n, Nil{})

def K.var.kind(+g: G, +name: String, kind: Nat, +total: U32) -> KM(Doc):
  match kind:
    case 3n:
      KM.pure(Doc, DStr{"0"})
    case 4n:
      do KM<Doc>:
        K.error("unknown name: " ++ name)
        return DStr{"0"}
    case 1n:
      KM.if(Doc, U32.is_zero(total), K.effect(), K.def_value(name, total))
    case other:
      KM.if(Doc, U32.is_zero(total), K.call.zero(g, name), K.def_value(name, total))

def K.var.def(+g: G, +name: String, info: DInfo) -> KM(Doc):
  DInfo{+kind, +mask} = info
  K.var.kind(g, name, U32.to_nat(kind), U32.from_nat(List.length(&2, Bool, mask)))

def K.var.found(+g: G, +name: String, m: Maybe<&2, String>) -> KM(Doc):
  match m:
    case Some{c}:
      KM.pure(Doc, DStr{c})
    case None{}:
      KM.if(Doc, Str.eq(name, "_"), KM.pure(Doc, DStr{"0"}), K.var.def(g, name, G.def(g, name)))

def K.var(+g: G, +env: Env(), +name: String) -> KM(Doc):
  K.var.found(g, name, Env.find(env, name))


# The device compiler, one def (fuel: its calls, which reach other defs):
# KSel picks the step.
type KSel is Type:
  KSExprs{g: G, env: Env(), xs: List<&2, Expr>}
  KSCallFull{g: G, env: Env(), name: String, mask: List<&2, Bool>, kind: Nat, kept: List<&2, Expr>,
      all: List<&2, Expr>, extra: List<&2, Expr>, full: Bool}
  KSCallDefKind{kind: Nat, g: G, env: Env(), name: String, mask: List<&2, Bool>, kept: List<&2, Expr>,
      all: List<&2, Expr>, extra: List<&2, Expr>, full: Bool}
  KSCallDefGo{g: G, env: Env(), name: String, mask: List<&2, Bool>, kind: Nat, s: Split}
  KSCallDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Expr>}
  KSCallLocal{g: G, env: Env(), f: Expr, args: List<&2, Expr>}
  KSCallVar{g: G, env: Env(), name: String, args: List<&2, Expr>, local: Bool}
  KSCallBang{g: G, env: Env(), args: List<&2, Expr>}
  KSCall{g: G, env: Env(), f: Expr, args: List<&2, Expr>}
  KSCtor{g: G, env: Env(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Expr>}
  KSBlock{g: G, env: Env(), e: Expr}
  KSExpr{g: G, env: Env(), e: Expr}
  KSLam{g: G, env: Env(), p: Pat, body: Expr}
  KSTail{g: G, env: Env(), entry: U32, s: Split}
  KSTailSelf{g: G, env: Env(), self: KSelf, args: List<&2, Expr>}
  KSStmtCall{g: G, env: Env(), self: KSelf, tgt: KTgt, name: String, args: List<&2, Expr>, tail: Bool}
  KSLetVar{g: G, env: Env(), self: KSelf, tgt: KTgt, x: String, v: Expr, body: Expr}
  KSLetPat{g: G, env: Env(), self: KSelf, tgt: KTgt, p: Pat, v: Expr, body: Expr}
  KSParThunks{g: G, env: Env(), vs: List<&2, Expr>}
  KSParSeqPlain{g: G, env: Env(), v: Expr, r: U32}
  KSParSeqKq{g: G, env: Env(), f: String, kept: List<&2, Expr>, r: U32}
  KSParSeqPick{sq: Bool, extra: List<&2, Expr>, full: Bool, g: G, env: Env(), f: String, args: List<&2, Expr>,
      kept: List<&2, Expr>, r: U32}
  KSParSeqSplit{sq: Bool, g: G, env: Env(), f: String, args: List<&2, Expr>, r: U32, s: Split}
  KSParSeqDef{g: G, env: Env(), f: String, args: List<&2, Expr>, r: U32, info: DInfo}
  KSParSeqVal{g: G, env: Env(), v: Expr, r: U32}
  KSParSeq{g: G, env: Env(), vs: List<&2, Expr>, rs: List<&2, U32>}
  KSPar{g: G, env: Env(), self: KSelf, tgt: KTgt, ps: List<&2, Pat>, vs: List<&2, Expr>, body: Expr}
  KSLetPar{g: G, env: Env(), self: KSelf, tgt: KTgt, ps: List<&2, Pat>, v: Expr, body: Expr}
  KSLetCtor{g: G, env: Env(), self: KSelf, tgt: KTgt, name: String, ps: List<&2, Pat>, v: Expr, body: Expr, par: Bool}
  KSLet{g: G, env: Env(), self: KSelf, tgt: KTgt, p: Pat, v: Expr, body: Expr}
  KSBodies{g: G, self: KSelf, tgt: KTgt, cases: List<&2, KCase>}
  KSMatch{g: G, env: Env(), self: KSelf, tgt: KTgt, scrs: List<&2, Expr>, cases: List<&2, Expr>}
  KSStmt{g: G, env: Env(), self: KSelf, tgt: KTgt, e: Expr}

def KSel.ty(k: KSel) -> Type:
  match k:
    case KSExprs{g, env, xs}:
      KM(List<&2, Doc>)
    case KSCallFull{g, env, name, mask, kind, kept, all, extra, full}:
      KM(Doc)
    case KSCallDefKind{kind, g, env, name, mask, kept, all, extra, full}:
      KM(Doc)
    case KSCallDefGo{g, env, name, mask, kind, s}:
      KM(Doc)
    case KSCallDef{g, env, name, info, args}:
      KM(Doc)
    case KSCallLocal{g, env, f, args}:
      KM(Doc)
    case KSCallVar{g, env, name, args, local}:
      KM(Doc)
    case KSCallBang{g, env, args}:
      KM(Doc)
    case KSCall{g, env, f, args}:
      KM(Doc)
    case KSCtor{g, env, name, info, args}:
      KM(Doc)
    case KSBlock{g, env, e}:
      KM(Doc)
    case KSExpr{g, env, e}:
      KM(Doc)
    case KSLam{g, env, p, body}:
      KM(Doc)
    case KSTail{g, env, entry, s}:
      KM(Unit)
    case KSTailSelf{g, env, self, args}:
      KM(Unit)
    case KSStmtCall{g, env, self, tgt, name, args, tail}:
      KM(Unit)
    case KSLetVar{g, env, self, tgt, x, v, body}:
      KM(Unit)
    case KSLetPat{g, env, self, tgt, p, v, body}:
      KM(Unit)
    case KSParThunks{g, env, vs}:
      KM(List<&2, U32>)
    case KSParSeqPlain{g, env, v, r}:
      KM(Unit)
    case KSParSeqKq{g, env, f, kept, r}:
      KM(Unit)
    case KSParSeqPick{sq, extra, full, g, env, f, args, kept, r}:
      KM(Unit)
    case KSParSeqSplit{sq, g, env, f, args, r, s}:
      KM(Unit)
    case KSParSeqDef{g, env, f, args, r, info}:
      KM(Unit)
    case KSParSeqVal{g, env, v, r}:
      KM(Unit)
    case KSParSeq{g, env, vs, rs}:
      KM(Unit)
    case KSPar{g, env, self, tgt, ps, vs, body}:
      KM(Unit)
    case KSLetPar{g, env, self, tgt, ps, v, body}:
      KM(Unit)
    case KSLetCtor{g, env, self, tgt, name, ps, v, body, par}:
      KM(Unit)
    case KSLet{g, env, self, tgt, p, v, body}:
      KM(Unit)
    case KSBodies{g, self, tgt, cases}:
      KM(Unit)
    case KSMatch{g, env, self, tgt, scrs, cases}:
      KM(Unit)
    case KSStmt{g, env, self, tgt, e}:
      KM(Unit)

def K.go(n: Nat, k: KSel) -> KSel.ty(k):
  match n:
    case 0n:
      match k:
        case KSExprs{g, env, xs}:
          K.out(List<&2, Doc>, Nil{})
        case KSCallFull{g, env, name, mask, kind, kept, all, extra, full}:
          K.out(Doc, DNil{})
        case KSCallDefKind{kind, g, env, name, mask, kept, all, extra, full}:
          K.out(Doc, DNil{})
        case KSCallDefGo{g, env, name, mask, kind, s}:
          K.out(Doc, DNil{})
        case KSCallDef{g, env, name, info, args}:
          K.out(Doc, DNil{})
        case KSCallLocal{g, env, f, args}:
          K.out(Doc, DNil{})
        case KSCallVar{g, env, name, args, local}:
          K.out(Doc, DNil{})
        case KSCallBang{g, env, args}:
          K.out(Doc, DNil{})
        case KSCall{g, env, f, args}:
          K.out(Doc, DNil{})
        case KSCtor{g, env, name, info, args}:
          K.out(Doc, DNil{})
        case KSBlock{g, env, e}:
          K.out(Doc, DNil{})
        case KSExpr{g, env, e}:
          K.out(Doc, DNil{})
        case KSLam{g, env, p, body}:
          K.out(Doc, DNil{})
        case KSTail{g, env, entry, s}:
          K.out(Unit, Unit{})
        case KSTailSelf{g, env, self, args}:
          K.out(Unit, Unit{})
        case KSStmtCall{g, env, self, tgt, name, args, tail}:
          K.out(Unit, Unit{})
        case KSLetVar{g, env, self, tgt, x, v, body}:
          K.out(Unit, Unit{})
        case KSLetPat{g, env, self, tgt, p, v, body}:
          K.out(Unit, Unit{})
        case KSParThunks{g, env, vs}:
          K.out(List<&2, U32>, Nil{})
        case KSParSeqPlain{g, env, v, r}:
          K.out(Unit, Unit{})
        case KSParSeqKq{g, env, f, kept, r}:
          K.out(Unit, Unit{})
        case KSParSeqPick{sq, extra, full, g, env, f, args, kept, r}:
          K.out(Unit, Unit{})
        case KSParSeqSplit{sq, g, env, f, args, r, s}:
          K.out(Unit, Unit{})
        case KSParSeqDef{g, env, f, args, r, info}:
          K.out(Unit, Unit{})
        case KSParSeqVal{g, env, v, r}:
          K.out(Unit, Unit{})
        case KSParSeq{g, env, vs, rs}:
          K.out(Unit, Unit{})
        case KSPar{g, env, self, tgt, ps, vs, body}:
          K.out(Unit, Unit{})
        case KSLetPar{g, env, self, tgt, ps, v, body}:
          K.out(Unit, Unit{})
        case KSLetCtor{g, env, self, tgt, name, ps, v, body, par}:
          K.out(Unit, Unit{})
        case KSLet{g, env, self, tgt, p, v, body}:
          K.out(Unit, Unit{})
        case KSBodies{g, self, tgt, cases}:
          K.out(Unit, Unit{})
        case KSMatch{g, env, self, tgt, scrs, cases}:
          K.out(Unit, Unit{})
        case KSStmt{g, env, self, tgt, e}:
          K.out(Unit, Unit{})
    case Succ{+fu}:
      match k:
        case KSExprs{+g, +env, xs}:
          match xs:
            case Nil{}:
              KM.pure(List<&2, Doc>, Nil{})
            case h <> t:
              do KM<List<&2, Doc>>:
                d : Doc <- K.go(fu, KSExpr{g, env, h})
                +k : U32 <- K.slot()
                K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
                ds : List<&2, Doc> <- K.go(fu, KSExprs{g, env, t})
                return DStr{S(k)} <> ds
        case KSCallFull{+g, +env, +name, +mask, kind, kept, all, extra, full}:
          match full:
            case True{}:
              do KM<Doc>:
                ks : List<&2, Doc> <- K.go(fu, KSExprs{g, env, kept})
                r : Doc <- K.call.kind(g, name, kind, ks)
                xs : List<&2, Doc> <- K.go(fu, KSExprs{g, env, extra})
                K.apply(xs, r)
            case False{}:
              do KM<Doc>:
                as : List<&2, Doc> <- K.go(fu, KSExprs{g, env, all})
                +w : U32 <- K.fn(K.wrap.name(name))
                K.clo(w, U32.from_nat(List.length(&2, Bool, mask)), as)
        case KSCallDefKind{kind, +g, +env, +name, +mask, kept, all, extra, full}:
          match kind:
            case 3n:
              KM.pure(Doc, DStr{"0"})
            case 4n:
              do KM<Doc>:
                K.error("unknown function: " ++ name)
                return DStr{"0"}
            case other:
              K.go(fu, KSCallFull{g, env, name, mask, other, kept, all, extra, full})
        case KSCallDefGo{+g, +env, +name, +mask, kind, s}:
          Split{kept, all, extra, full} = s
          K.go(fu, KSCallDefKind{kind, g, env, name, mask, kept, all, extra, full})
        case KSCallDef{+g, +env, +name, info, args}:
          DInfo{kind, +mask} = info
          K.go(fu, KSCallDefGo{g, env, name, mask, U32.to_nat(kind), Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case KSCallLocal{+g, +env, f, args}:
          do KM<Doc>:
            fd : Doc <- K.go(fu, KSExpr{g, env, f})
            +k : U32 <- K.slot()
            K.put(Doc.list([DStr{S(k) ++ " = "}, fd, DStr{";\n"}]))
            xs : List<&2, Doc> <- K.go(fu, KSExprs{g, env, args})
            K.apply(xs, DStr{S(k)})
        case KSCallVar{+g, +env, +name, args, local}:
          match local:
            case True{}:
              K.go(fu, KSCallLocal{g, env, EVar{name}, args})
            case False{}:
              K.go(fu, KSCallDef{g, env, name, G.def(g, name), args})
        # A !-call on the device is a call.
        case KSCallBang{+g, +env, args}:
          match args:
            case f <> xs:
              K.go(fu, KSCall{g, env, f, xs})
            case Nil{}:
              KM.pure(Doc, DStr{"0"})
        case KSCall{+g, +env, f, args}:
          match f:
            case EVar{"%gpu"}:
              K.go(fu, KSCallBang{g, env, args})
            case EVar{+name}:
              K.go(fu, KSCallVar{g, env, name, args, Env.has(env, name)})
            case other:
              K.go(fu, KSCallLocal{g, env, other, args})
        case KSCtor{+g, +env, name, info, args}:
          match info:
            case None{}:
              do KM<Doc>:
                K.error("unknown constructor: " ++ name)
                return DStr{"0"}
            case Some{CInfo{tag, ar, kind, single}}:
              do KM<Doc>:
                ds : List<&2, Doc> <- K.go(fu, KSExprs{g, env, args})
                K.ctor.kind(tag, U32.to_nat(kind), ds)
        case KSBlock{+g, +env, e}:
          do KM<Doc>:
            +k : U32 <- K.slot()
            +m : U32 <- K.fresh()
            K.go(fu, KSStmt{g, env, KSelf.none(), KSet{k, m}, e})
            K.start(m)
            return DStr{S(k)}
        case KSExpr{+g, +env, e}:
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
              K.go(fu, KSCall{g, env, f, args})
            case ECtor{+name, args}:
              K.go(fu, KSCtor{g, env, name, G.ctor(g, name), args})
            case ELam{p, body}:
              K.go(fu, KSLam{g, env, p, body})
            case ELet{p, v, body}:
              K.go(fu, KSBlock{g, env, ELet{p, v, body}})
            case EMatch{scrs, cases}:
              K.go(fu, KSBlock{g, env, EMatch{scrs, cases}})
            case ESucc{k, x}:
              do KM<Doc>:
                d : Doc <- K.go(fu, KSExpr{g, env, x})
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
        # A lambda: a function over its captures and its argument (slots 0..n).
        case KSLam{+g, +env, +p, +body}:
          +caps = Gen.caps(FV.expr(body, Pat.vars(p, Nil{}), Nil{}), env)
          +n = U32.from_nat(List.length(&2, Bind, caps))
          do KM<Doc>:
            +l : U32 <- K.fresh()
            saved : U32 & Doc <- K.save()
            +old : U32 <- K.enter(l)
            +arg : U32 <- K.slots(U32.inc(n))
            +binds : Env() <- KM.pure(Env(), PatR.binds(K.pat(g, p, S(n), PatR{Nil{}, Nil{}})))
            K.start(l)
            K.go(fu, KSStmt{g, List.append(&2, Bind, binds, K.caps.inner(caps, 0)), KSelf.none(), KRet{}, body})
            +size : U32 <- K.leave(old)
            K.frame(l, size)
            K.restore(saved)
            K.clo(l, U32.inc(n), K.caps.outer(caps))
        # A self tail call: the arguments (already in slots) become the parameters.
        case KSTail{+g, +env, +entry, s}:
          Split{kept, all, extra, full} = s
          do KM<Unit>:
            ds : List<&2, Doc> <- K.go(fu, KSExprs{g, env, kept})
            K.put(Doc.list([DStr{"{ "}, K.tail.set(ds, 0), DStr{"KPC = " ++ U32.show(entry) ++ "; }\n"}]))
        case KSTailSelf{+g, +env, self, args}:
          KSelf{sn, +entry, +mask} = self
          K.go(fu, KSTail{g, env, entry, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case KSStmtCall{+g, +env, +self, +tgt, +name, args, tail}:
          match tail:
            case True{}:
              K.go(fu, KSTailSelf{g, env, self, args})
            case False{}:
              do KM<Unit>:
                d : Doc <- K.go(fu, KSCall{g, env, EVar{name}, args})
                K.ret(tgt, d)
        case KSLetVar{+g, +env, +self, +tgt, +x, v, body}:
          do KM<Unit>:
            d : Doc <- K.go(fu, KSExpr{g, env, v})
            +k : U32 <- K.slot()
            K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
            K.go(fu, KSStmt{g, Bool.pick(Env(), Str.eq(x, "_"), env, Bind{x, S(k)} <> env), self, tgt, body})
        case KSLetPat{+g, +env, +self, +tgt, +p, v, body}:
          do KM<Unit>:
            d : Doc <- K.go(fu, KSExpr{g, env, v})
            +k : U32 <- K.slot()
            K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
            +binds : Env() <- KM.pure(Env(), PatR.binds(K.pat(g, p, S(k), PatR{Nil{}, Nil{}})))
            K.go(fu, KSStmt{g, List.append(&2, Bind, binds, env), self, tgt, body})
        # Each value becomes a thunk (a closure). Below the fork limit the thunks
        # but the last go to the queue, the last runs here, and a join record
        # collects the values; the lane that brings the last value continues. Past
        # the limit they run one after the other.
        case KSParThunks{+g, +env, vs}:
          match vs:
            case Nil{}:
              KM.pure(List<&2, U32>, Nil{})
            case v <> t:
              do KM<List<&2, U32>>:
                d : Doc <- K.go(fu, KSLam{g, env, PVar{"_"}, v})
                +k : U32 <- K.slot()
                K.put(Doc.list([DStr{S(k) ++ " = "}, d, DStr{";\n"}]))
                ks : List<&2, U32> <- K.go(fu, KSParThunks{g, env, t})
                return k <> ks
        case KSParSeqPlain{+g, +env, v, +r}:
          do KM<Unit>:
            x : Doc <- K.go(fu, KSExpr{g, env, v})
            K.put(Doc.list([DStr{S(r) ++ " = "}, x, DStr{";\n"}]))
        case KSParSeqKq{+g, +env, +f, kept, +r}:
          do KM<Unit>:
            +ds : List<&2, Doc> <- K.go(fu, KSExprs{g, env, kept})
            +e : U32 <- K.fn(f)
            +ret : U32 <- K.fresh()
            +after : U32 <- K.fresh()
            +fb : U32 <- K.fresh()
            # A request the kernel's loop runs with the lane's SIMD group (PC_KQ):
            # the value comes back in rv at ret, or the call goes through frames at fb.
            K.put(Doc.list([DStr{"c->kq = " ++ U32.show(e) ++ "; c->kqret = " ++ U32.show(ret) ++ "; c->kqfb = " ++ U32.show(fb) ++
              ";\n"}, KQ.req(ds, 0), DStr{"KPC = PC_KQ;\n"}]))
            K.start(fb)
            K.put(Doc.list([DStr{"{ KW nf = KPUSH(" ++ U32.show(ret) ++ ", " ++ U32.show(e) ++ ");\n"},
              K.args.put(KQ.req.args(U32.to_nat(Gen.len(ds)), 0), 0), DStr{"KFP = nf; KPC = " ++ U32.show(e) ++ "; }\n"}]))
            K.start(ret)
            K.putS(S(r) ++ " = KRV;\nKPC = " ++ U32.show(after) ++ ";\n")
            K.start(after)
        case KSParSeqPick{sq, extra, full, +g, +env, +f, args, kept, +r}:
          match sq extra full:
            case True{} Nil{} True{}:
              K.go(fu, KSParSeqKq{g, env, f, kept, r})
            case a b c:
              K.go(fu, KSParSeqPlain{g, env, ECall{EVar{f}, args}, r})
        case KSParSeqSplit{sq, +g, +env, +f, args, +r, s}:
          Split{kept, all, extra, full} = s
          K.go(fu, KSParSeqPick{sq, extra, full, g, env, f, args, kept, r})
        case KSParSeqDef{+g, +env, +f, +args, +r, info}:
          DInfo{kind, mask} = info
          do KM<Unit>:
            sq : Bool <- K.isseq(g, f)
            fl : Bool <- K.isflat(g, f)
            K.go(fu, KSParSeqSplit{Bool.and(sq, Bool.not(fl)), g, env, f, args, r, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{},
              False{}})})
        # One value of a parallel let past the fork limit: a call of a seq def runs
        # in its KQ_ function, or through frames if that gives up.
        case KSParSeqVal{+g, +env, v, +r}:
          match v:
            case ECall{EVar{+f}, +args}:
              KM.if(Unit, Env.has(env, f), K.go(fu, KSParSeqPlain{g, env, ECall{EVar{f}, args}, r}),
                K.go(fu, KSParSeqDef{g, env, f, args, r, G.def(g, f)}))
            case other:
              K.go(fu, KSParSeqPlain{g, env, other, r})
        # Past the fork limit the values are evaluated one after the other.
        case KSParSeq{+g, +env, vs, rs}:
          match vs rs:
            case v <> vt +r <> rt:
              do KM<Unit>:
                K.go(fu, KSParSeqVal{g, env, v, r})
                K.go(fu, KSParSeq{g, env, vt, rt})
            case a b:
              KM.pure(Unit, Unit{})
        case KSPar{+g, +env, +self, +tgt, +ps, +vs, body}:
          +n = List.length(&2, Expr, vs)
          do KM<Unit>:
            +rs : List<&2, U32> <- K.newslots(n)
            +j : U32 <- K.slot()
            +lpar : U32 <- K.fresh()
            +lseq : U32 <- K.fresh()
            +lcont : U32 <- K.fresh()
            +lbody : U32 <- K.fresh()
            K.putS("KPC = KFORK ? " ++ U32.show(lpar) ++ " : " ++ U32.show(lseq) ++ ";\n")
            K.start(lseq)
            K.go(fu, KSParSeq{g, env, vs, rs})
            K.putS("KPC = " ++ U32.show(lbody) ++ ";\n")
            K.start(lpar)
            +thunks : List<&2, U32> <- K.go(fu, KSParThunks{g, env, vs})
            K.putS(S(j) ++ " = k_join_new(c, " ++ U32.show(U32.from_nat(n)) ++ ", " ++ U32.show(lcont) ++ ");\n")
            K.put(K.par.push(thunks, j, 0))
            K.putS("c->dep += 1;\n")
            x : Doc <- K.apply1(DStr{S(List.last_u32(thunks))}, DStr{"0"})
            K.put(Doc.list([DStr{"k_arrive(c, " ++ S(j) ++ ", " ++ U32.show(U32.from_nat(Nat.sub(n, 1n))) ++ ", "}, x,
              DStr{");\n"}]))
            K.start(lcont)
            K.put(K.par.collect(rs, j, 0))
            K.putS("KPC = " ++ U32.show(lbody) ++ ";\n")
            K.start(lbody)
            K.go(fu, KSStmt{g, K.par.env(g, ps, rs, env), self, tgt, body})
        case KSLetPar{+g, +env, +self, +tgt, ps, v, body}:
          match v:
            case ECtor{n, vs}:
              K.go(fu, KSPar{g, env, self, tgt, ps, vs, body})
            case other:
              K.go(fu, KSPar{g, env, self, tgt, ps, [other], body})
        case KSLetCtor{+g, +env, +self, +tgt, name, ps, v, body, par}:
          match par:
            case True{}:
              K.go(fu, KSLetPar{g, env, self, tgt, ps, v, body})
            case False{}:
              K.go(fu, KSLetPat{g, env, self, tgt, PCtor{name, ps}, v, body})
        case KSLet{+g, +env, +self, +tgt, p, v, body}:
          match p:
            case PVar{+x}:
              K.go(fu, KSLetVar{g, env, self, tgt, x, v, body})
            case PCtor{+name, ps}:
              K.go(fu, KSLetCtor{g, env, self, tgt, name, ps, v, body, Str.eq(name, "%par")})
            case other:
              K.go(fu, KSLetPat{g, env, self, tgt, other, v, body})
        case KSBodies{+g, +self, +tgt, cases}:
          match cases:
            case Nil{}:
              KM.pure(Unit, Unit{})
            case KCase{+l, conds, +env, body} <> t:
              do KM<Unit>:
                K.start(l)
                K.go(fu, KSStmt{g, env, self, tgt, body})
                K.go(fu, KSBodies{g, self, tgt, t})
        case KSMatch{+g, +env, +self, +tgt, scrs, cases}:
          do KM<Unit>:
            ds : List<&2, Doc> <- K.go(fu, KSExprs{g, env, scrs})
            +cs : List<&2, KCase> <- K.cases(g, env, K.doc_strs(ds), cases)
            K.put(K.dispatch(cs))
            K.go(fu, KSBodies{g, self, tgt, cs})
        case KSStmt{+g, +env, +self, +tgt, e}:
          match e:
            case ELet{p, v, body}:
              K.go(fu, KSLet{g, env, self, tgt, p, v, body})
            case EMatch{scrs, cases}:
              K.go(fu, KSMatch{g, env, self, tgt, scrs, cases})
            case ECall{EVar{+name}, +args}:
              K.go(fu, KSStmtCall{g, env, self, tgt, name, args, KSelf.is_tail(env, self, tgt, name, args)})
            case other:
              do KM<Unit>:
                d : Doc <- K.go(fu, KSExpr{g, env, other})
                K.ret(tgt, d)

def K.stmt(g: G, env: Env(), self: KSelf, tgt: KTgt, e: Expr) -> KM(Unit):
  K.go(Fuel.max(), KSStmt{g, env, self, tgt, e})
def K.wrapper(+g: G, +name: String, +l: U32, +mask: List<&2, Bool>, kind: Nat) -> KM(Unit):
  do KM<Unit>:
    +old : U32 <- K.enter(l)
    +np : U32 <- K.slots(U32.from_nat(List.length(&2, Bool, mask)))
    K.start(l)
    r : Doc <- K.call.kind(g, name, kind, K.wrap.args(mask, 0))
    K.put(Doc.list([DStr{"KRET("}, r, DStr{");\n"}]))
    +size : U32 <- K.leave(old)
    K.frame(l, size)

def K.def.flat(+g: G, +name: String, +l: U32, +mask: List<&2, Bool>) -> KM(Unit):
  do KM<Unit>:
    +old : U32 <- K.enter(l)
    +np : U32 <- K.slots(K.kept(mask))
    K.start(l)
    r : Doc <- K.call.flat.k(g, name, K.slot.docs(np, 0), True{})
    K.put(Doc.list([DStr{"KRET("}, r, DStr{");\n"}]))
    +size : U32 <- K.leave(old)
    K.frame(l, size)

def K.one.wrap.go(+g: G, +name: String, +l: U32, info: DInfo) -> KM(Unit):
  DInfo{kind, +mask} = info
  K.wrapper(g, name, l, mask, U32.to_nat(kind))

def K.one.wrap(+g: G, +name: String, +l: U32) -> KM(Unit):
  K.one.wrap.go(g, name, l, G.def(g, name))
#
# KQ_name runs a seq def with its parallel lets in order. Its locals are C
# variables, and a block ends only where the def calls itself: the call
# saves the variables in scope and a resume label on a thread-private stack,
# passes the arguments in A0.., and jumps to the entry; a return pops the
# label and the resumed block reloads the variables. A tail call is a jump.
# If the stack would overflow, KQ_name gives up (*ok = false) and the caller
# runs the call through the kernel's frames.
def KQ.arg(+i: U32) -> String:
  "A" ++ U32.show(i)

# The bindings to save at a call: the first of each name, not erased.
def KQ.live(env: Env(), +seen: List<&2, String>) -> Env():
  match env:
    case Nil{}:
      Nil{}
    case Bind{+x, +c} <> +t:
      Bool.pick(Unit -> Env(), Bool.or(Str.has(seen, x), Str.eq(c, "0")), u => KQ.live(t, seen),
        u => Bind{x, c} <> KQ.live(t, x <> seen))(Unit{})

def KQ.used.if(keep: Bool, x: String, c: String, rest: Env()) -> Env():
  match keep:
    case True{}:
      Bind{x, c} <> rest
    case False{}:
      rest

def KQ.used(env: Env(), +names: List<&2, String>) -> Env():
  match env:
    case Nil{}:
      Nil{}
    case Bind{+x, c} <> t:
      KQ.used.if(Str.has(names, x), x, c, KQ.used(t, names))

def KQ.save(live: Env(), +i: U32) -> String:
  match live:
    case Nil{}:
      ""
    case Bind{x, c} <> t:
      "KQ_ST(sp + " ++ U32.show(i) ++ ") = " ++ c ++ "; " ++ KQ.save(t, U32.inc(i))

# After the call: each saved variable reloaded into a fresh local.
def KQ.load(live: Env(), +k: U32, +i: U32) -> String:
  match live:
    case Nil{}:
      ""
    case Bind{x, c} <> t:
      "KW " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ " = KQ_ST(sp + " ++ U32.show(i) ++ "); " ++ KQ.load(t, k, U32.inc(i))

def KQ.reenv(live: Env(), +k: U32, +i: U32) -> Env():
  match live:
    case Nil{}:
      Nil{}
    case Bind{x, c} <> t:
      Bind{x, KX.v(k) ++ "_" ++ U32.show(i)} <> KQ.reenv(t, k, U32.inc(i))

def KQ.args(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{KQ.arg(i) ++ " = "}, d, DStr{"; "}, KQ.args(t, U32.inc(i))])

def K.docs.of(e: Env()) -> List<&2, Doc>:
  match e:
    case Nil{}:
      Nil{}
    case Bind{x, c} <> t:
      DStr{c} <> K.docs.of(t)

def KQ.pass(+k: U32, +n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      KQ.arg(i) ++ " = " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ "; " ++ KQ.pass(k, m, U32.inc(i))

def KSelf.entry(s: KSelf) -> U32:
  KSelf{n, e, m} = s
  e

def KQ.tail.go(+g: G, +env: Env(), +self: KSelf, s: Split) -> KM(Unit):
  Split{kept, all, extra, full} = s
  do KM<Unit>:
    +k : U32 <- K.fresh()
    +ds : List<&2, Doc> <- KX.exprs(g, env, kept)
    # (Errors are checked here: a tail loop could spin on a failed value.
    # Other calls are bounded by the stack.)
    K.put(Doc.list([DStr{"{ "}, KX.temps(ds, k, 0), DStr{KQ.pass(k, U32.to_nat(Gen.len(ds)), 0) ++
      "if (c->err) { *ok = false; return 0; }\npc = " ++ U32.show(KSelf.entry(self)) ++ "; break; }\n"}]))

# A tail call of the def itself: new arguments, back to the entry.
def KQ.tail(+g: G, +env: Env(), +self: KSelf, args: List<&2, Expr>) -> KM(Unit):
  KQ.tail.go(g, env, self, Gen.split(KSelf.mask(self), args, Split{Nil{}, Nil{}, Nil{}, False{}}))

# A value to return: to the caller's resume label, or out of KQ_name.
def KQ.ret(+g: G, +env: Env(), e: Expr) -> KM(Unit):
  do KM<Unit>:
    d : Doc <- KX.expr(g, env, e)
    K.put(Doc.list([DStr{"RV = "}, d, DStr{";\nif (sp == 0) return RV;\nsp -= 1; pc = KQ_ST(sp); break;\n"}]))

# A parallel let runs in order: a let per value.
def KQ.par.lets(ps: List<&2, Pat>, vs: List<&2, Expr>, body: Expr) -> Expr:
  match ps vs:
    case p <> pt v <> vt:
      ELet{p, v, KQ.par.lets(pt, vt, body)}
    case a b:
      body

def KQ.par.vals(v: Expr) -> List<&2, Expr>:
  match v:
    case ECtor{n, vs}:
      vs
    case other:
      [other]

def KQ.call.args(v: Expr) -> List<&2, Expr>:
  match v:
    case ECall{f, args}:
      args
    case other:
      Nil{}


# The sequential compiler (KQ_ functions), one def (fuel: its calls):
# KQSel picks the step.
type KQSel is Type:
  KQSDef{sq: Bool, g: G, name: String, e: U32, mask: List<&2, Bool>, ps: List<&2, Param>, body: Expr}
  KQSCallGo{g: G, env: Env(), self: KSelf, x: String, s: Split, body: Expr}
  KQSCall{g: G, env: Env(), self: KSelf, x: String, args: List<&2, Expr>, body: Expr}
  KQSCases{g: G, env: Env(), self: KSelf, cs: List<&2, String>, cases: List<&2, Expr>}
  KQSMatchGo{g: G, env: Env(), self: KSelf, r: List<&2, String> & Doc, cases: List<&2, Expr>}
  KQSMatch{g: G, env: Env(), self: KSelf, scrs: List<&2, Expr>, cases: List<&2, Expr>}
  KQSLetVar{g: G, env: Env(), self: KSelf, x: String, v: Expr, body: Expr, direct: Bool}
  KQSLetPat{g: G, env: Env(), self: KSelf, p: Pat, v: Expr, body: Expr, direct: Bool}
  KQSLet{g: G, env: Env(), self: KSelf, p: Pat, v: Expr, body: Expr}
  KQSStmt{g: G, env: Env(), self: KSelf, e: Expr}

def KQSel.ty(k: KQSel) -> Type:
  match k:
    case KQSDef{sq, g, name, e, mask, ps, body}:
      KM(Unit)
    case KQSCallGo{g, env, self, x, s, body}:
      KM(Unit)
    case KQSCall{g, env, self, x, args, body}:
      KM(Unit)
    case KQSCases{g, env, self, cs, cases}:
      KM(Unit)
    case KQSMatchGo{g, env, self, r, cases}:
      KM(Unit)
    case KQSMatch{g, env, self, scrs, cases}:
      KM(Unit)
    case KQSLetVar{g, env, self, x, v, body, direct}:
      KM(Unit)
    case KQSLetPat{g, env, self, p, v, body, direct}:
      KM(Unit)
    case KQSLet{g, env, self, p, v, body}:
      KM(Unit)
    case KQSStmt{g, env, self, e}:
      KM(Unit)

def KQ.go(n: Nat, k: KQSel) -> KQSel.ty(k):
  match n:
    case 0n:
      match k:
        case KQSDef{sq, g, name, e, mask, ps, body}:
          K.out(Unit, Unit{})
        case KQSCallGo{g, env, self, x, s, body}:
          K.out(Unit, Unit{})
        case KQSCall{g, env, self, x, args, body}:
          K.out(Unit, Unit{})
        case KQSCases{g, env, self, cs, cases}:
          K.out(Unit, Unit{})
        case KQSMatchGo{g, env, self, r, cases}:
          K.out(Unit, Unit{})
        case KQSMatch{g, env, self, scrs, cases}:
          K.out(Unit, Unit{})
        case KQSLetVar{g, env, self, x, v, body, direct}:
          K.out(Unit, Unit{})
        case KQSLetPat{g, env, self, p, v, body, direct}:
          K.out(Unit, Unit{})
        case KQSLet{g, env, self, p, v, body}:
          K.out(Unit, Unit{})
        case KQSStmt{g, env, self, e}:
          K.out(Unit, Unit{})
    case Succ{+fu}:
      match k:
        case KQSDef{sq, +g, +name, +e, +mask, ps, body}:
          match sq:
            case True{}:
              +n = U32.to_nat(K.kept(mask))
              do KM<Unit>:
                K.start(0)
                saved : Doc <- K.cap.begin()
                +l : U32 <- K.fresh()
                +k : U32 <- K.fresh()
                K.start(l)
                K.putS(KQ.entry(k, n, 0) ++ "\n")
                KQ.go(fu, KQSStmt{g, KQ.sig(ps, mask, k, 0), KSelf{name, l, mask}, R.ops(body, "Nat")})
                K.start(0)
                blocks : Doc <- K.cap.take(saved)
                K.flat.add(Doc.list([DStr{"\nKINLINE KW KQ_" ++ Gen.mangle(name) ++ "(KTHR KCtx *c" ++ KQ.params(n, 0) ++
                  ", KTHR bool *ok) {\nKQ_STACK;\nKW sp = 0, pc = " ++ U32.show(l) ++ ", RV = 0;\n" ++ KQ.init(n, 0) ++
                  "for (;;) {\nswitch (pc) {\n"}, blocks,
                  DStr{"default:\n*ok = false;\nreturn 0;\n}\n}\n}\n"}]))
                K.memo.put("%kqcase", "case " ++ U32.show(e) ++ ": return KQ_" ++ Gen.mangle(name) ++ "(c" ++ KQ.case.args(n, 0) ++
                  ", ok);\n")
            case False{}:
              KM.pure(Unit, Unit{})
        case KQSCallGo{+g, +env, +self, +x, s, +body}:
          Split{kept, all, extra, full} = s
          # Saved: the variables the rest of the code uses.
          +live = KQ.live(KQ.used(env, FV.expr(body, [x], Nil{})), Nil{})
          +m = Gen.len(K.docs.of(live))
          do KM<Unit>:
            +k : U32 <- K.fresh()
            +ds : List<&2, Doc> <- KX.exprs(g, env, kept)
            +r : U32 <- K.fresh()
            K.put(Doc.list([DStr{"{ "}, KX.temps(ds, k, 0), DStr{"if (sp + " ++ U32.show(U32.inc(m)) ++
              " > KR_WORDS) { *ok = false; return 0; }\n" ++ KQ.save(live, 0) ++ "KQ_ST(sp + " ++ U32.show(m) ++ ") = " ++
              U32.show(r) ++ "; sp += " ++ U32.show(U32.inc(m)) ++ ";\n" ++ KQ.pass(k, U32.to_nat(Gen.len(ds)), 0) ++ "pc = " ++
              U32.show(KSelf.entry(self)) ++ "; break; }\n"}]))
            # The resume block is made aside, so the code around the call (an arm
            # of a match, say) stays whole in this block.
            saved : U32 & Doc <- K.save()
            K.start(r)
            +j : U32 <- K.fresh()
            K.putS("sp -= " ++ U32.show(m) ++ "; " ++ KQ.load(live, j, 0) ++ "KW " ++ KX.v(j) ++ " = RV;\n")
            KQ.go(fu, KQSStmt{g, Bool.pick(Env(), Str.eq(x, "_"), KQ.reenv(live, j, 0), Bind{x, KX.v(j)} <> KQ.reenv(live, j, 0)), self,
              body})
            K.restore(saved)
        # x = f(args) at statement level, f the def itself: save, call, resume.
        case KQSCall{+g, +env, +self, +x, args, body}:
          KQ.go(fu, KQSCallGo{g, env, self, x, Gen.split(KSelf.mask(self), args, Split{Nil{}, Nil{}, Nil{}, False{}}), body})
        case KQSCases{+g, +env, +self, +cs, cases}:
          match cases:
            case Nil{}:
              K.putS("{ k_fail(c, KE_MATCH); *ok = false; return 0; }\n")
            case ECase{ps, body} <> t:
              +pr = K.pats(g, ps, cs, PatR{Nil{}, Nil{}})
              do KM<Unit>:
                K.putS("if (" ++ Gen.and(List.reverse(&2, String, PatR.conds(pr))) ++ ") {\n")
                KQ.go(fu, KQSStmt{g, List.append(&2, Bind, PatR.binds(pr), env), self, body})
                K.putS("} else ")
                KQ.go(fu, KQSCases{g, env, self, cs, t})
            case other <> t:
              KQ.go(fu, KQSCases{g, env, self, cs, t})
        case KQSMatchGo{+g, +env, +self, r, cases}:
          (cs, code) = r
          do KM<Unit>:
            K.put(code)
            KQ.go(fu, KQSCases{g, env, self, cs, cases})
        case KQSMatch{+g, +env, +self, scrs, cases}:
          do KM<Unit>:
            r : List<&2, String> & Doc <- KX.scrs(g, env, scrs)
            KQ.go(fu, KQSMatchGo{g, env, self, r, cases})
        case KQSLetVar{+g, +env, +self, +x, v, body, direct}:
          match direct:
            case True{}:
              KQ.go(fu, KQSCall{g, env, self, x, KQ.call.args(v), body})
            case False{}:
              do KM<Unit>:
                +k : U32 <- K.fresh()
                d : Doc <- KX.expr(g, env, v)
                K.put(Doc.list([DStr{"KW " ++ KX.v(k) ++ " = "}, d, DStr{";\n"}]))
                KQ.go(fu, KQSStmt{g, Bool.pick(Env(), Str.eq(x, "_"), env, Bind{x, KX.v(k)} <> env), self, body})
        # A pattern let whose value is a call of the def: the value to a variable
        # first.
        case KQSLetPat{+g, +env, +self, +p, v, body, direct}:
          match direct:
            case True{}:
              do KM<Unit>:
                +k : U32 <- K.fresh()
                KQ.go(fu, KQSStmt{g, env, self, ELet{PVar{"%q" ++ U32.show(k)}, v, ELet{p, EVar{"%q" ++ U32.show(k)}, body}}})
            case False{}:
              do KM<Unit>:
                +k : U32 <- K.fresh()
                d : Doc <- KX.expr(g, env, v)
                K.put(Doc.list([DStr{"KW " ++ KX.v(k) ++ " = "}, d, DStr{";\n"}]))
                KQ.go(fu, KQSStmt{g, List.append(&2, Bind, PatR.binds(K.pat(g, p, KX.v(k), PatR{Nil{}, Nil{}})), env), self, body})
        case KQSLet{+g, +env, +self, p, +v, +body}:
          match p:
            case PVar{+x}:
              KQ.go(fu, KQSLetVar{g, env, self, x, v, body, K.fl.direct(self, Nil{}, v)})
            case PCtor{+n, +ps}:
              KM.if(Unit, Str.eq(n, "%par"), KQ.go(fu, KQSStmt{g, env, self, KQ.par.lets(ps, KQ.par.vals(v), body)}),
                KQ.go(fu, KQSLetPat{g, env, self, PCtor{n, ps}, v, body, K.fl.direct(self, Nil{}, v)}))
            case other:
              KQ.go(fu, KQSLetPat{g, env, self, other, v, body, K.fl.direct(self, Nil{}, v)})
        case KQSStmt{+g, +env, +self, e}:
          match e:
            case ELet{p, v, body}:
              KQ.go(fu, KQSLet{g, env, self, p, v, body})
            case EMatch{scrs, cases}:
              KQ.go(fu, KQSMatch{g, env, self, scrs, cases})
            case ECall{EVar{+name}, +args}:
              KM.if(Unit, Bool.and(Str.eq(name, KSelf.name(self)), Bool.not(Env.has(env, name))), KQ.tail(g, env, self, args),
                KQ.ret(g, env, ECall{EVar{name}, args}))
            case other:
              KQ.ret(g, env, other)

def KQ.def(sq: Bool, g: G, name: String, e: U32, mask: List<&2, Bool>, ps: List<&2, Param>, body: Expr) -> KM(Unit):
  KQ.go(Fuel.max(), KQSDef{sq, g, name, e, mask, ps, body})

def K.def.body(+g: G, +name: String, +l: U32, +mask: List<&2, Bool>, +ps: List<&2, Param>, +body: Expr) -> KM(Unit):
  do KM<Unit>:
    sq : Bool <- K.isseq(g, name)
    +old : U32 <- K.enter(l)
    +np : U32 <- K.slots(K.kept(mask))
    K.start(l)
    K.stmt(g, K.sig.env(ps, mask, 0), KSelf{name, l, mask}, KRet{}, R.ops(body, "Nat"))
    +size : U32 <- K.leave(old)
    K.frame(l, size)
    KQ.def(sq, g, name, l, mask, ps, body)

# A flat def's entry block calls its function.
def K.def.decl.flat(flat: Bool, +g: G, +name: String, +l: U32, +mask: List<&2, Bool>, ps: List<&2, Param>, body: Expr) ->
  KM(Unit):
  match flat:
    case True{}:
      K.def.flat(g, name, l, mask)
    case False{}:
      K.def.body(g, name, l, mask, ps, body)

def K.def.decl.def(kind: Nat, +g: G, +name: String, +l: U32, +mask: List<&2, Bool>, ps: List<&2, Param>, body: Expr) ->
  KM(Unit):
  match kind:
    case 0n:
      do KM<Unit>:
        flat : Bool <- K.isflat(g, name)
        K.def.decl.flat(flat, g, name, l, mask, ps, body)
    case other:
      K.wrapper(g, name, l, mask, other)

def K.def.decl.go(d: Decl, +g: G, +name: String, +l: U32, kind: Nat, +mask: List<&2, Bool>) -> KM(Unit):
  match d:
    case DDef{n, ps, body, ret}:
      K.def.decl.def(kind, g, name, l, mask, ps, body)
    case other:
      K.wrapper(g, name, l, mask, kind)

def K.def.decl(+g: G, +name: String, +l: U32, info: DInfo, d: Decl) -> KM(Unit):
  DInfo{kind, mask} = info
  K.def.decl.go(d, g, name, l, U32.to_nat(kind), mask)
# Compiles one queued function (a def, or "%wrap name").
def K.one(+g: G, +key: String, +l: U32) -> KM(Unit):
  KM.if(Unit, String.starts_with(key, "%wrap "), K.one.wrap(g, String.drop(key, 6n), l), K.def.decl(g, key, l,
    G.def(g, key), G.body(g, key)))

def K.label.go(+name: String, st: KSt) -> U32 & KSt:
  KSt{n, sl, curl, cur, out, +fns, todo, frames, errs, flat, memo} = st
  (Maybe.default(&2, U32, U32.read(Maybe.default(&2, String, Env.find(fns, name), "0")), 0),
    KSt{n, sl, curl, cur, out, fns, todo, frames, errs, flat, memo})

def K.label(+name: String) -> KM(U32):
  st => K.label.go(name, st)

# Compiles the queue, then what it queued, until none is left; fuel: the
# functions it may compile.
def K.all.list(fuel: Nat, +g: G, todo: List<&2, String>) -> KM(Unit):
  match fuel todo:
    case k Nil{}:
      KM.pure(Unit, Unit{})
    case 1n+f +h <> t:
      do KM<Unit>:
        +l : U32 <- K.label(h)
        K.one(g, h, l)
        more : List<&2, String> <- K.take_todo()
        K.all.list(f, g, List.append(&2, String, t, more))
    case 0n t:
      K.out(Unit, Unit{})

# Compiles queued functions until none is left.
def K.all(+g: G, fuel: Nat) -> KM(Unit):
  match fuel:
    case 0n:
      KM.pure(Unit, Unit{})
    case 1n+f:
      do KM<Unit>:
        todo : List<&2, String> <- K.take_todo()
        K.all.list(f, g, todo)

# The frame table and the entry labels the host needs.
def K.frame_of(frames: List<&2, Bind>, +l: U32) -> String:
  Maybe.default(&2, String, Env.find(frames, U32.show(l)), "0")

# The frames of k labels from l.
def K.frame_table.go(k: Nat, +frames: List<&2, Bind>, +l: U32) -> String:
  match k:
    case 0n:
      ""
    case 1n+j:
      K.frame_of(frames, l) ++ "u, " ++ K.frame_table.go(j, frames, U32.inc(l))

def K.frame_table(+frames: List<&2, Bind>, +l: U32, +n: U32) -> String:
  K.frame_table.go(Bool.pick(Nat, U32.is_ge(l, n), 0n, U32.to_nat((n - l : U32))), frames, l)

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
# BigInt (Nat), 3 a string (String), 4 a one-code-point string (Char), 7 a
# JS array (Array: ALeaf{x} is [x], and ANode's halves are slices).
def J.kind(+ty: String) -> Nat:
  P.which(ty, ["", "Bool", "Nat", "String", "Char", "U32", "F32", "Array"])

def J.nth(xs: List<&2, String>, n: Nat) -> String:
  match xs n:
    case x <> t 0n:
      x
    case x <> t 1n+m:
      J.nth(t, m)
    case Nil{} k:
      "_"

def J.str(s: String) -> Doc:
  DStr{"\"" ++ J.lit(s) ++ "\""}

# A def that merges a cycle, out of fuel: an error, and x.
def J.out(-A: Type, x: A) -> Gen(A):
  do Gen<A>:
    Gen.error("out of fuel")
    return x

def J.dotted(s: String) -> Bool:
  match s:
    case SNil{}:
      False{}
    case SCon{Chr{c}, t}:
      Bool.or(U32.is_eq(c, 46), J.dotted(t))

# A field as an object key and as a member: a dotted name (a.b) is
# quoted, and __proto__ computed, else it would set the prototype.
def J.key(+f: String) -> String:
  Bool.pick(String, Str.eq(f, "__proto__"), "[\"__proto__\"]",
    Bool.pick(String, J.dotted(f), "\"" ++ f ++ "\"", f))

def J.acc(+f: String) -> String:
  Bool.pick(String, J.dotted(f), "[\"" ++ f ++ "\"]", "." ++ f)

def J.paths(+path: String, fs: List<&2, String>) -> List<&2, String>:
  match fs:
    case Nil{}:
      Nil{}
    case f <> t:
      ("(" ++ path ++ ")" ++ J.acc(f)) <> J.paths(path, t)

# A host Nat is a BigInt trusted as is: a negative one matches as a Succ
# (upstream's one value model), so 1n+p tests only for nonzero.
def J.succ.cond(+path: String, +k: U32) -> String:
  Bool.pick(String, U32.is_eq(k, 1), "(" ++ path ++ ") !== 0n", "(" ++ path ++ ") >= " ++ U32.show(k) ++ "n")

def J.obj.fields(fs: List<&2, String>, ds: List<&2, Doc>) -> List<&2, Doc>:
  match fs ds:
    case f <> ft d <> dt:
      Doc.list([DStr{", " ++ J.key(f) ++ ": "}, d]) <> J.obj.fields(ft, dt)
    case a b:
      Nil{}

def J.ctor.arr(leaf: Bool, ds: List<&2, Doc>) -> Doc:
  match leaf:
    case True{}:
      Doc.list([DStr{"["}, Doc.list(ds), DStr{"]"}])
    case False{}:
      Doc.list([DStr{"array_node("}, Gen.commas(ds), DStr{")"}])

def J.ctor.kind(kind: Nat, +name: String, fs: List<&2, String>, ds: List<&2, Doc>) -> Doc:
  match kind:
    case 1n:
      DStr{Bool.pick(String, Str.eq(name, "True"), "true", "false")}
    case 2n:
      Bool.pick(Doc, Str.eq(name, "Zero"), DStr{"0n"}, Doc.list([DStr{"nat_chk("}, Doc.list(ds), DStr{" + 1n)"}]))
    case 3n:
      Bool.pick(Doc, Str.eq(name, "SNil"), DStr{"\"\""}, Doc.list([DStr{"str_cons("}, Gen.commas(ds), DStr{")"}]))
    case 4n:
      Doc.list([DStr{"char_new("}, Doc.list(ds), DStr{")"}])
    case 5n:
      Doc.list([DStr{"("}, Doc.list(ds), DStr{")"}])
    case 6n:
      Doc.list([DStr{"f32_of_bits("}, Doc.list(ds), DStr{")"}])
    case 7n:
      J.ctor.arr(Str.eq(name, "ALeaf"), ds)
    case other:
      Doc.list([DStr{"({$: \"" ++ name ++ "\""}, Doc.list(J.obj.fields(fs, ds)), DStr{"})"}])

# A float literal on JS: the binary32 that strtof reads the text as, written
# m * 2 ** e (exact in binary64), so nothing rounds it a second time
# (Math.fround(Number(s)) rounds through binary64 first, #1055).
def J.flt.mag(+m: U32, +ex: U32) -> String:
  Bool.pick(String, U32.is_ge(ex, 150), U32.show(m) ++ " * 2 ** " ++ U32.show((ex - 150 : U32)),
    U32.show(m) ++ " * 2 ** -" ++ U32.show((150 - ex : U32)))

def J.flt.bits(+b: U32) -> String:
  +ex = ((b >> 23n) .&. 255 : U32)
  +fr = (b .&. 8388607 : U32)
  Bool.pick(String, U32.is_eq((b >> 31n : U32), 1), "-", "") ++
    Bool.pick(String, U32.is_eq(ex, 0), J.flt.mag(fr, 1), J.flt.mag((fr .|. 8388608 : U32), ex))

def J.flt.of(+s: String, m: Maybe<&2, F32>) -> String:
  match m:
    case Some{f}:
      "(" ++ J.flt.bits(F32.bits(f)) ++ ")"
    case None{}:
      "Math.fround(" ++ s ++ ")"

def J.flt(+s: String) -> String:
  J.flt.of(s, F32.read(s))


# The pattern compiler, one def (fuel: its calls): JPatSel picks the step.
# Out of fuel, a condition that names nothing fails when it runs.
type JPatSel is Type:
  JPFields{j: JG, args: List<&2, Pat>, paths: List<&2, String>, r: PatR}
  JPBitsCon{j: JG, p: Pat, path: String, r: PatR}
  JPBitsGo{j: JG, k: Nat, p: Pat, path: String, r: PatR}
  JPBits{j: JG, p: Pat, path: String, r: PatR}
  JPBitsOne{j: JG, args: List<&2, Pat>, path: String, r: PatR}
  JPArr{leaf: Bool, j: JG, args: List<&2, Pat>, path: String, r: PatR}
  JPKind{j: JG, kind: Nat, name: String, args: List<&2, Pat>, path: String, fs: List<&2, String>, single: Bool,
      r: PatR}
  JPCtor{j: JG, info: Maybe<&2, JCI>, name: String, args: List<&2, Pat>, path: String, r: PatR}
  JPPat{j: JG, p: Pat, path: String, r: PatR}

def JPatSel.ty(k: JPatSel) -> Type:
  match k:
    case JPFields{j, args, paths, r}:
      PatR
    case JPBitsCon{j, p, path, r}:
      PatR
    case JPBitsGo{j, k, p, path, r}:
      PatR
    case JPBits{j, p, path, r}:
      PatR
    case JPBitsOne{j, args, path, r}:
      PatR
    case JPArr{leaf, j, args, path, r}:
      PatR
    case JPKind{j, kind, name, args, path, fs, single, r}:
      PatR
    case JPCtor{j, info, name, args, path, r}:
      PatR
    case JPPat{j, p, path, r}:
      PatR

def J.pat.go(n: Nat, k: JPatSel) -> JPatSel.ty(k):
  match n:
    case 0n:
      match k:
        case JPFields{j, args, paths, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPBitsCon{j, p, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPBitsGo{j, k, p, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPBits{j, p, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPBitsOne{j, args, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPArr{leaf, j, args, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPKind{j, kind, name, args, path, fs, single, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPCtor{j, info, name, args, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
        case JPPat{j, p, path, r}:
          Gen.pat.cond("bend_out_of_fuel", r)
    case Succ{+fu}:
      match k:
        case JPFields{+j, args, +paths, r}:
          match args paths:
            case a <> at +p <> pt:
              J.pat.go(fu, JPFields{j, at, pt, J.pat.go(fu, JPPat{j, a, p, r})})
            case x y:
              r
        case JPBitsCon{+j, p, +path, r}:
          match p:
            case PCtor{n, a <> b <> Nil{}}:
              J.pat.go(fu, JPBits{j, b, "((" ++ path ++ ") >>> 1)", J.pat.go(fu, JPPat{j, a, "(((" ++ path ++ ") & 1) === 1)", r})})
            case other:
              r
        case JPBitsGo{+j, k, p, +path, r}:
          match k:
            case 0n:
              J.pat.go(fu, JPBitsCon{j, p, path, r})
            case 1n:
              r
            case 2n+q:
              J.pat.go(fu, JPPat{j, p, path, r})
        case JPBits{+j, +p, +path, r}:
          J.pat.go(fu, JPBitsGo{j, Pat.wordk(p), p, path, r})
        case JPBitsOne{+j, args, +path, r}:
          match args:
            case a <> Nil{}:
              J.pat.go(fu, JPBits{j, a, path, r})
            case other:
              r
        case JPArr{leaf, +j, args, +path, r}:
          match leaf:
            case True{}:
              J.pat.go(fu, JPFields{j, args, ["(" ++ path ++ ")[0]"], Gen.pat.cond("(" ++ path ++ ").length === 1", r)})
            case False{}:
              J.pat.go(fu, JPFields{j, args, ["array_half(" ++ path ++ ", 0)", "array_half(" ++ path ++ ", 1)"],
                Gen.pat.cond("(" ++ path ++ ").length !== 1", r)})
        case JPKind{+j, kind, +name, args, +path, fs, single, +r}:
          match kind:
            case 1n:
              Gen.pat.cond(Bool.pick(String, Str.eq(name, "True"), "", "!") ++ "(" ++ path ++ ")", r)
            case 2n:
              Bool.pick(PatR, Str.eq(name, "Zero"), Gen.pat.cond("(" ++ path ++ ") === 0n", r),
                J.pat.go(fu, JPFields{j, args, ["((" ++ path ++ ") - 1n)"], Gen.pat.cond("(" ++ path ++ ") !== 0n", r)}))
            case 3n:
              Bool.pick(PatR, Str.eq(name, "SNil"), Gen.pat.cond("(" ++ path ++ ") === \"\"", r),
                J.pat.go(fu, JPFields{j, args, ["str_head(" ++ path ++ ")", "str_tail(" ++ path ++ ")"],
                  Gen.pat.cond("(" ++ path ++ ") !== \"\"", r)}))
            case 4n:
              J.pat.go(fu, JPFields{j, args, ["(" ++ path ++ ").codePointAt(0)"], r})
            case 5n:
              J.pat.go(fu, JPBitsOne{j, args, path, r})
            case 6n:
              J.pat.go(fu, JPBitsOne{j, args, "F_F32_dbits(" ++ path ++ ")", r})
            case 7n:
              J.pat.go(fu, JPArr{Str.eq(name, "ALeaf"), j, args, path, r})
            case other:
              J.pat.go(fu, JPFields{j, args, J.paths(path, fs), Gen.pat.tag(single, "(" ++ path ++ ").$ === \"" ++ name ++ "\"", r)})
        case JPCtor{+j, info, +name, args, +path, r}:
          match info:
            case None{}:
              Gen.pat.cond("false /* unknown constructor " ++ name ++ " */", r)
            case Some{JCI{+ty, fs, single}}:
              J.pat.go(fu, JPKind{j, J.kind(ty), name, args, path, fs, single, r})
        case JPPat{+j, p, +path, r}:
          match p:
            case PVar{x}:
              Gen.pat.var(x, path, r)
            case PCtor{+name, args}:
              J.pat.go(fu, JPCtor{j, J.ctor(j, name), name, args, path, r})
            case PNat{n}:
              Gen.pat.cond("(" ++ path ++ ") === " ++ U32.show(n) ++ "n", r)
            case PSucc{+k, q}:
              J.pat.go(fu, JPPat{j, q, "((" ++ path ++ ") - " ++ U32.show(k) ++ "n)",
                Gen.pat.cond(J.succ.cond(path, k), r)})
            case PNum{n}:
              Gen.pat.cond("(" ++ path ++ ") === " ++ U32.show(n), r)
            case PFlt{s}:
              Gen.pat.cond("(" ++ path ++ ") === " ++ J.flt(s), r)

def J.pat(j: JG, p: Pat, path: String, r: PatR) -> PatR:
  J.pat.go(Fuel.max(), JPPat{j, p, path, r})
def J.pats(+j: JG, ps: List<&2, Pat>, paths: List<&2, String>, r: PatR) -> PatR:
  match ps paths:
    case p <> pt c <> ct:
      J.pats(j, pt, ct, J.pat(j, p, c, r))
    case pl cl:
      r

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
    case 4n:
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

def J.ret(t: Tgt, d: Doc) -> Doc:
  match t:
    case TRet{}:
      Doc.list([DStr{"return "}, d, DStr{";\n"}])
    case TSet{v}:
      Doc.list([DStr{v}, DStr{" = "}, d, DStr{";\n"}])
    case TDst{id, n}:
      Doc.list([DStr{"*dst = "}, d, DStr{";\nreturn 0;\n"}])

def J.tail.temps(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"const t" ++ U32.show(i) ++ " = "}, d, DStr{"; "}, J.tail.temps(t, U32.inc(i))])

def J.scrs.put(+c: String, d: Doc, r: List<&2, String> & Doc) -> List<&2, String> & Doc:
  (cs, code) = r
  (c <> cs, Doc.list([DStr{"const " ++ c ++ " = "}, d, DStr{";\n"}, code]))


# The JS compiler, one def (fuel: its calls): JSel picks the step.
type JSel is Type:
  JSExprs{j: JG, env: Env(), xs: List<&2, Expr>}
  JSBitsCon{j: JG, env: Env(), e: Expr}
  JSBitsGo{j: JG, env: Env(), k: Nat, e: Expr}
  JSBits{j: JG, env: Env(), e: Expr}
  JSBitsArgs{j: JG, env: Env(), w: Nat, args: List<&2, Expr>}
  JSCtorBuild{j: JG, env: Env(), name: String, info: Maybe<&2, JCI>, args: List<&2, Expr>}
  JSCallFull{j: JG, env: Env(), name: String, kept: List<&2, Expr>, all: List<&2, Expr>, extra: List<&2, Expr>,
      full: Bool}
  JSCallSplit{j: JG, env: Env(), name: String, s: Split}
  JSCallKind{j: JG, env: Env(), name: String, kind: Nat, s: Split}
  JSCallDef{j: JG, env: Env(), name: String, info: DInfo, args: List<&2, Expr>}
  JSCallLocal{j: JG, env: Env(), f: Expr, args: List<&2, Expr>}
  JSCallVar{j: JG, env: Env(), name: String, args: List<&2, Expr>, local: Bool}
  JSCallBang{j: JG, env: Env(), args: List<&2, Expr>}
  JSCallName{j: JG, env: Env(), name: String, args: List<&2, Expr>, bang: Bool}
  JSCall{j: JG, env: Env(), f: Expr, args: List<&2, Expr>}
  JSBlock{j: JG, env: Env(), e: Expr}
  JSExpr{j: JG, env: Env(), e: Expr}
  JSLam{j: JG, env: Env(), p: Pat, body: Expr}
  JSTail{j: JG, env: Env(), cps: List<&2, String>, s: Split}
  JSTailSelf{j: JG, env: Env(), self: Self, args: List<&2, Expr>}
  JSStmtCall{j: JG, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Expr>, tail: Bool}
  JSLetVar{j: JG, env: Env(), self: Self, tgt: Tgt, x: String, v: Expr, body: Expr, hole: Bool}
  JSLetPat{j: JG, env: Env(), self: Self, tgt: Tgt, p: Pat, v: Expr, body: Expr}
  JSLetPar{j: JG, env: Env(), self: Self, tgt: Tgt, ps: List<&2, Pat>, v: Expr, body: Expr}
  JSLetCtor{j: JG, env: Env(), self: Self, tgt: Tgt, name: String, ps: List<&2, Pat>, v: Expr, body: Expr, par: Bool}
  JSLet{j: JG, env: Env(), self: Self, tgt: Tgt, p: Pat, v: Expr, body: Expr}
  JSCasesNext{j: JG, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>, rest: List<&2, Expr>,
      conds: List<&2, String>, b: Doc}
  JSCases{j: JG, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>, cases: List<&2, Expr>}
  JSScrs{j: JG, env: Env(), xs: List<&2, Expr>}
  JSMatchGo{j: JG, env: Env(), self: Self, tgt: Tgt, cases: List<&2, Expr>, r: List<&2, String> & Doc}
  JSMatch{j: JG, env: Env(), self: Self, tgt: Tgt, scrs: List<&2, Expr>, cases: List<&2, Expr>}
  JSStmt{j: JG, env: Env(), self: Self, tgt: Tgt, e: Expr}

def JSel.ty(k: JSel) -> Type:
  match k:
    case JSExprs{j, env, xs}:
      Gen(List<&2, Doc>)
    case JSBitsCon{j, env, e}:
      Gen(Doc)
    case JSBitsGo{j, env, k, e}:
      Gen(Doc)
    case JSBits{j, env, e}:
      Gen(Doc)
    case JSBitsArgs{j, env, w, args}:
      Gen(List<&2, Doc>)
    case JSCtorBuild{j, env, name, info, args}:
      Gen(Doc)
    case JSCallFull{j, env, name, kept, all, extra, full}:
      Gen(Doc)
    case JSCallSplit{j, env, name, s}:
      Gen(Doc)
    case JSCallKind{j, env, name, kind, s}:
      Gen(Doc)
    case JSCallDef{j, env, name, info, args}:
      Gen(Doc)
    case JSCallLocal{j, env, f, args}:
      Gen(Doc)
    case JSCallVar{j, env, name, args, local}:
      Gen(Doc)
    case JSCallBang{j, env, args}:
      Gen(Doc)
    case JSCallName{j, env, name, args, bang}:
      Gen(Doc)
    case JSCall{j, env, f, args}:
      Gen(Doc)
    case JSBlock{j, env, e}:
      Gen(Doc)
    case JSExpr{j, env, e}:
      Gen(Doc)
    case JSLam{j, env, p, body}:
      Gen(Doc)
    case JSTail{j, env, cps, s}:
      Gen(Doc)
    case JSTailSelf{j, env, self, args}:
      Gen(Doc)
    case JSStmtCall{j, env, self, tgt, name, args, tail}:
      Gen(Doc)
    case JSLetVar{j, env, self, tgt, x, v, body, hole}:
      Gen(Doc)
    case JSLetPat{j, env, self, tgt, p, v, body}:
      Gen(Doc)
    case JSLetPar{j, env, self, tgt, ps, v, body}:
      Gen(Doc)
    case JSLetCtor{j, env, self, tgt, name, ps, v, body, par}:
      Gen(Doc)
    case JSLet{j, env, self, tgt, p, v, body}:
      Gen(Doc)
    case JSCasesNext{j, env, self, tgt, cs, rest, conds, b}:
      Gen(Doc)
    case JSCases{j, env, self, tgt, cs, cases}:
      Gen(Doc)
    case JSScrs{j, env, xs}:
      Gen(List<&2, String> & Doc)
    case JSMatchGo{j, env, self, tgt, cases, r}:
      Gen(Doc)
    case JSMatch{j, env, self, tgt, scrs, cases}:
      Gen(Doc)
    case JSStmt{j, env, self, tgt, e}:
      Gen(Doc)

def J.go(n: Nat, k: JSel) -> JSel.ty(k):
  match n:
    case 0n:
      match k:
        case JSExprs{j, env, xs}:
          J.out(List<&2, Doc>, Nil{})
        case JSBitsCon{j, env, e}:
          J.out(Doc, DNil{})
        case JSBitsGo{j, env, k, e}:
          J.out(Doc, DNil{})
        case JSBits{j, env, e}:
          J.out(Doc, DNil{})
        case JSBitsArgs{j, env, w, args}:
          J.out(List<&2, Doc>, Nil{})
        case JSCtorBuild{j, env, name, info, args}:
          J.out(Doc, DNil{})
        case JSCallFull{j, env, name, kept, all, extra, full}:
          J.out(Doc, DNil{})
        case JSCallSplit{j, env, name, s}:
          J.out(Doc, DNil{})
        case JSCallKind{j, env, name, kind, s}:
          J.out(Doc, DNil{})
        case JSCallDef{j, env, name, info, args}:
          J.out(Doc, DNil{})
        case JSCallLocal{j, env, f, args}:
          J.out(Doc, DNil{})
        case JSCallVar{j, env, name, args, local}:
          J.out(Doc, DNil{})
        case JSCallBang{j, env, args}:
          J.out(Doc, DNil{})
        case JSCallName{j, env, name, args, bang}:
          J.out(Doc, DNil{})
        case JSCall{j, env, f, args}:
          J.out(Doc, DNil{})
        case JSBlock{j, env, e}:
          J.out(Doc, DNil{})
        case JSExpr{j, env, e}:
          J.out(Doc, DNil{})
        case JSLam{j, env, p, body}:
          J.out(Doc, DNil{})
        case JSTail{j, env, cps, s}:
          J.out(Doc, DNil{})
        case JSTailSelf{j, env, self, args}:
          J.out(Doc, DNil{})
        case JSStmtCall{j, env, self, tgt, name, args, tail}:
          J.out(Doc, DNil{})
        case JSLetVar{j, env, self, tgt, x, v, body, hole}:
          J.out(Doc, DNil{})
        case JSLetPat{j, env, self, tgt, p, v, body}:
          J.out(Doc, DNil{})
        case JSLetPar{j, env, self, tgt, ps, v, body}:
          J.out(Doc, DNil{})
        case JSLetCtor{j, env, self, tgt, name, ps, v, body, par}:
          J.out(Doc, DNil{})
        case JSLet{j, env, self, tgt, p, v, body}:
          J.out(Doc, DNil{})
        case JSCasesNext{j, env, self, tgt, cs, rest, conds, b}:
          J.out(Doc, DNil{})
        case JSCases{j, env, self, tgt, cs, cases}:
          J.out(Doc, DNil{})
        case JSScrs{j, env, xs}:
          J.out(List<&2, String> & Doc, (Nil{}, DNil{}))
        case JSMatchGo{j, env, self, tgt, cases, r}:
          J.out(Doc, DNil{})
        case JSMatch{j, env, self, tgt, scrs, cases}:
          J.out(Doc, DNil{})
        case JSStmt{j, env, self, tgt, e}:
          J.out(Doc, DNil{})
    case Succ{+fu}:
      match k:
        case JSExprs{+j, +env, xs}:
          match xs:
            case Nil{}:
              Gen.pure(List<&2, Doc>, Nil{})
            case h <> t:
              do Gen<List<&2, Doc>>:
                d : Doc <- J.go(fu, JSExpr{j, env, h})
                ds : List<&2, Doc> <- J.go(fu, JSExprs{j, env, t})
                return d <> ds
        case JSBitsCon{+j, +env, e}:
          match e:
            case ECtor{n, a <> b <> Nil{}}:
              do Gen<Doc>:
                da : Doc <- J.go(fu, JSExpr{j, env, a})
                db : Doc <- J.go(fu, JSBits{j, env, b})
                return Doc.list([DStr{"word_con("}, da, DStr{", "}, db, DStr{")"}])
            case other:
              J.go(fu, JSExpr{j, env, other})
        case JSBitsGo{+j, +env, k, e}:
          match k:
            case 0n:
              J.go(fu, JSBitsCon{j, env, e})
            case 1n:
              Gen.pure(Doc, DStr{"0"})
            case 2n+q:
              J.go(fu, JSExpr{j, env, e})
        case JSBits{+j, +env, +e}:
          J.go(fu, JSBitsGo{j, env, Expr.wordk(e), e})
        case JSBitsArgs{+j, +env, w, args}:
          match w args:
            case 2n+p xs:
              J.go(fu, JSExprs{j, env, xs})
            case k a <> Nil{}:
              do Gen<List<&2, Doc>>:
                d : Doc <- J.go(fu, JSBits{j, env, a})
                return [d]
            case k xs:
              J.go(fu, JSExprs{j, env, xs})
        case JSCtorBuild{+j, +env, +name, info, args}:
          match info:
            case None{}:
              do Gen<Doc>:
                Gen.error("unknown constructor: " ++ name)
                return DStr{"null"}
            case Some{JCI{+ty, fs, single}}:
              do Gen<Doc>:
                ds : List<&2, Doc> <- J.go(fu, JSBitsArgs{j, env, P.which(name, ["U32", "F32"]), args})
                return J.ctor.kind(J.kind(ty), name, fs, ds)
        case JSCallFull{+j, +env, +name, kept, all, extra, full}:
          match full:
            case True{}:
              do Gen<Doc>:
                ks : List<&2, Doc> <- J.go(fu, JSExprs{j, env, kept})
                xs : List<&2, Doc> <- J.go(fu, JSExprs{j, env, extra})
                return J.apply(xs, Doc.list([DStr{Gen.f(name) ++ "("}, Gen.commas(ks), DStr{")"}]))
            case False{}:
              do Gen<Doc>:
                as : List<&2, Doc> <- J.go(fu, JSExprs{j, env, all})
                return J.apply(as, DStr{Gen.w(name)})
        case JSCallSplit{+j, +env, +name, s}:
          Split{kept, all, extra, full} = s
          J.go(fu, JSCallFull{j, env, name, kept, all, extra, full})
        case JSCallKind{+j, +env, +name, kind, s}:
          match kind:
            case 3n:
              Gen.pure(Doc, DStr{"null"})
            case 4n:
              do Gen<Doc>:
                Gen.error("unknown function: " ++ name)
                return DStr{"null"}
            case other:
              do Gen<Doc>:
                Gen.ref(name)
                J.go(fu, JSCallSplit{j, env, name, s})
        case JSCallDef{+j, +env, +name, info, args}:
          DInfo{kind, +mask} = info
          J.go(fu, JSCallKind{j, env, name, U32.to_nat(kind), Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case JSCallLocal{+j, +env, f, args}:
          do Gen<Doc>:
            fd : Doc <- J.go(fu, JSExpr{j, env, f})
            xs : List<&2, Doc> <- J.go(fu, JSExprs{j, env, args})
            return J.apply(xs, Doc.list([DStr{"("}, fd, DStr{")"}]))
        case JSCallVar{+j, +env, +name, args, local}:
          match local:
            case True{}:
              J.go(fu, JSCallLocal{j, env, EVar{name}, args})
            case False{}:
              J.go(fu, JSCallDef{j, env, name, G.def(JG.g(j), name), args})
        # f!(args) runs as a call in JavaScript.
        case JSCallBang{+j, +env, args}:
          match args:
            case f <> xs:
              J.go(fu, JSCall{j, env, f, xs})
            case Nil{}:
              Gen.pure(Doc, DStr{"0"})
        case JSCallName{+j, +env, +name, args, bang}:
          match bang:
            case True{}:
              J.go(fu, JSCallBang{j, env, args})
            case False{}:
              J.go(fu, JSCallVar{j, env, name, args, Env.has(env, name)})
        case JSCall{+j, +env, f, args}:
          match f:
            case EVar{+name}:
              J.go(fu, JSCallName{j, env, name, args, Str.eq(name, "%gpu")})
            case other:
              J.go(fu, JSCallLocal{j, env, other, args})
        # A statement-level expression used as a value: an immediately called
        # function.
        case JSBlock{+j, +env, e}:
          do Gen<Doc>:
            b : Doc <- J.go(fu, JSStmt{j, env, Self.none(), TRet{}, e})
            return Doc.list([DStr{"(() => {\n"}, b, DStr{"})()"}])
        case JSExpr{+j, +env, e}:
          match e:
            case EVar{name}:
              J.var(j, env, name)
            case ENum{n}:
              Gen.pure(Doc, DStr{U32.show(n)})
            case ENat{n}:
              Gen.pure(Doc, DStr{U32.show(n) ++ "n"})
            case EFlt{s}:
              Gen.pure(Doc, DStr{J.flt(s)})
            case EStr{s}:
              Gen.pure(Doc, J.str(s))
            case ECall{f, args}:
              J.go(fu, JSCall{j, env, f, args})
            case ECtor{+name, args}:
              J.go(fu, JSCtorBuild{j, env, name, J.ctor(j, name), args})
            case ELam{p, body}:
              J.go(fu, JSLam{j, env, p, body})
            case ELet{p, v, body}:
              J.go(fu, JSBlock{j, env, ELet{p, v, body}})
            case EMatch{scrs, cases}:
              J.go(fu, JSBlock{j, env, EMatch{scrs, cases}})
            case ESucc{k, x}:
              do Gen<Doc>:
                d : Doc <- J.go(fu, JSExpr{j, env, x})
                return Doc.list([DStr{"nat_chk(("}, d, DStr{") + " ++ U32.show(k) ++ "n)"}])
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
        # A lambda's parameter is q<k>, apart from its def's a<i> (a JS closure
        # sees them all).
        case JSLam{+j, +env, +p, +body}:
          do Gen<Doc>:
            +k : U32 <- Gen.fresh()
            +a : String <- Gen.pure(String, "q" ++ U32.show(k))
            +binds : Env() <- Gen.pure(Env(), PatR.binds(J.pat(j, p, a, PatR{Nil{}, Nil{}})))
            b : Doc <- J.go(fu, JSStmt{j, List.append(&2, Bind, binds, env), Self.none(), TRet{}, body})
            return Doc.list([DStr{"((" ++ a ++ ") => {\n"}, b, DStr{"})"}])
        case JSTail{+j, +env, cps, s}:
          Split{kept, all, extra, full} = s
          do Gen<Doc>:
            ds : List<&2, Doc> <- J.go(fu, JSExprs{j, env, kept})
            return Doc.list([DStr{"{ "}, J.tail.temps(ds, 0), Gen.tail.assign(cps, 0), DStr{"continue top; }\n"}])
        case JSTailSelf{+j, +env, self, args}:
          Self{sn, +mask, cps} = self
          J.go(fu, JSTail{j, env, cps, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})})
        case JSStmtCall{+j, +env, +self, +tgt, +name, args, tail}:
          match tail:
            case True{}:
              J.go(fu, JSTailSelf{j, env, self, args})
            case False{}:
              do Gen<Doc>:
                d : Doc <- J.go(fu, JSCall{j, env, EVar{name}, args})
                return J.ret(tgt, d)
        case JSLetVar{+j, +env, +self, +tgt, +x, v, body, hole}:
          match hole:
            case True{}:
              do Gen<Doc>:
                d : Doc <- J.go(fu, JSExpr{j, env, v})
                b : Doc <- J.go(fu, JSStmt{j, env, self, tgt, body})
                return Doc.list([d, DStr{";\n"}, b])
            case False{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +c : String <- Gen.pure(String, "v" ++ U32.show(k))
                d : Doc <- J.go(fu, JSExpr{j, env, v})
                b : Doc <- J.go(fu, JSStmt{j, Bind{x, c} <> env, self, tgt, body})
                return Doc.list([DStr{"const " ++ c ++ " = "}, d, DStr{";\n"}, b])
        case JSLetPat{+j, +env, +self, +tgt, +p, v, body}:
          do Gen<Doc>:
            +k : U32 <- Gen.fresh()
            +c : String <- Gen.pure(String, "v" ++ U32.show(k))
            d : Doc <- J.go(fu, JSExpr{j, env, v})
            +binds : Env() <- Gen.pure(Env(), PatR.binds(J.pat(j, p, c, PatR{Nil{}, Nil{}})))
            b : Doc <- J.go(fu, JSStmt{j, List.append(&2, Bind, binds, env), self, tgt, body})
            return Doc.list([DStr{"const " ++ c ++ " = "}, d, DStr{";\n"}, b])
        # A parallel let runs its values one after another here.
        case JSLetPar{+j, +env, +self, +tgt, ps, v, body}:
          match ps v:
            case p <> pt ECtor{n, x <> xt}:
              J.go(fu, JSStmt{j, env, self, tgt, ELet{p, x, ELet{PCtor{"%par", pt}, ECtor{n, xt}, body}}})
            case pl other:
              J.go(fu, JSStmt{j, env, self, tgt, body})
        case JSLetCtor{+j, +env, +self, +tgt, name, ps, v, body, par}:
          match par:
            case True{}:
              J.go(fu, JSLetPar{j, env, self, tgt, ps, v, body})
            case False{}:
              J.go(fu, JSLetPat{j, env, self, tgt, PCtor{name, ps}, v, body})
        case JSLet{+j, +env, +self, +tgt, p, v, body}:
          match p:
            case PVar{+x}:
              J.go(fu, JSLetVar{j, env, self, tgt, x, v, body, Str.eq(x, "_")})
            case PCtor{+name, ps}:
              J.go(fu, JSLetCtor{j, env, self, tgt, name, ps, v, body, Str.eq(name, "%par")})
            case other:
              J.go(fu, JSLetPat{j, env, self, tgt, other, v, body})
        case JSCasesNext{+j, +env, +self, +tgt, +cs, rest, conds, b}:
          match conds:
            case Nil{}:
              Gen.pure(Doc, Doc.list([DStr{"{\n"}, b, DStr{"}\n"}]))
            case h <> t:
              do Gen<Doc>:
                more : Doc <- J.go(fu, JSCases{j, env, self, tgt, cs, rest})
                return Doc.list([DStr{"if (" ++ Gen.and(h <> t) ++ ") {\n"}, b, DStr{"} else "}, more])
        case JSCases{+j, +env, +self, +tgt, +cs, cases}:
          match cases:
            case Nil{}:
              Gen.pure(Doc, DStr{"{ bend_fail(\"runtime fail-stop\"); }\n"})
            case ECase{ps, body} <> t:
              +pr = J.pats(j, ps, cs, PatR{Nil{}, Nil{}})
              +conds = PatR.conds(pr)
              +binds = PatR.binds(pr)
              do Gen<Doc>:
                b : Doc <- J.go(fu, JSStmt{j, List.append(&2, Bind, binds, env), self, tgt, body})
                J.go(fu, JSCasesNext{j, env, self, tgt, cs, t, List.reverse(&2, String, conds), b})
            case other <> t:
              J.go(fu, JSCases{j, env, self, tgt, cs, t})
        case JSScrs{+j, +env, xs}:
          match xs:
            case Nil{}:
              Gen.pure(List<&2, String> & Doc, (Nil{}, DNil{}))
            case h <> t:
              do Gen<List<&2, String> & Doc>:
                +k : U32 <- Gen.fresh()
                +c : String <- Gen.pure(String, "s" ++ U32.show(k))
                d : Doc <- J.go(fu, JSExpr{j, env, h})
                r : List<&2, String> & Doc <- J.go(fu, JSScrs{j, env, t})
                return J.scrs.put(c, d, r)
        case JSMatchGo{+j, +env, +self, +tgt, cases, r}:
          (cs, decls) = r
          do Gen<Doc>:
            body : Doc <- J.go(fu, JSCases{j, env, self, tgt, cs, cases})
            return Doc.list([decls, body])
        case JSMatch{+j, +env, +self, +tgt, scrs, cases}:
          do Gen<Doc>:
            r : List<&2, String> & Doc <- J.go(fu, JSScrs{j, env, scrs})
            J.go(fu, JSMatchGo{j, env, self, tgt, cases, r})
        case JSStmt{+j, +env, +self, +tgt, e}:
          match e:
            case ELet{p, v, body}:
              J.go(fu, JSLet{j, env, self, tgt, p, v, body})
            case EMatch{scrs, cases}:
              J.go(fu, JSMatch{j, env, self, tgt, scrs, cases})
            case ECall{EVar{+name}, +args}:
              J.go(fu, JSStmtCall{j, env, self, tgt, name, args, Gen.is_tail(env, self, tgt, name, args)})
            case other:
              do Gen<Doc>:
                d : Doc <- J.go(fu, JSExpr{j, env, other})
                return J.ret(tgt, d)

def J.stmt(j: JG, env: Env(), self: Self, tgt: Tgt, e: Expr) -> Gen(Doc):
  J.go(Fuel.max(), JSStmt{j, env, self, tgt, e})
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

def J.loop.v(v: String) -> String:
  match v:
    case SCon{Chr{97}, t}:
      SCon{Chr{99}, t}
    case SCon{Chr{40}, SCon{Chr{97}, t}}:
      SCon{Chr{40}, SCon{Chr{99}, t}}
    case other:
      other

def J.loop.env(env: Env()) -> Env():
  match env:
    case Nil{}:
      Nil{}
    case Bind{x, v} <> t:
      Bind{x, J.loop.v(v)} <> J.loop.env(t)

def J.loop.copies(ps: List<&2, String>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case +p <> t:
      (J.loop.v(p) ++ " = " ++ p) <> J.loop.copies(t)

def J.loop.head(+ps: List<&2, String>) -> String:
  Bool.pick(String, List.is_empty(&2, String, ps), "",
    "const " ++ String.join(J.loop.copies(ps), ", ") ++ ";\n")

# A def's body is a loop its self tail calls continue after setting the
# a<i>; each turn reads them as consts c<i>, which a closure made in that
# turn keeps (it would see the next turn's a<i>).
def J.def.body(+j: JG, +name: String, +mask: List<&2, Bool>, body: Expr, sig: Sig) -> Gen(Unit):
  Sig{+params, env, wargs} = sig
  do Gen<Unit>:
    b : Doc <- J.stmt(j, J.loop.env(env), Self{name, mask, params}, TRet{}, R.ops(body, "Nat"))
    Gen.code(Doc.list([DStr{"function " ++ Gen.f(name) ++ "(" ++ J.params(params) ++ ") {\ntop: for (;;) {\n" ++
      J.loop.head(params)}, b, DStr{"}\n}\n"}]))
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
# A callback whose type leads with erased binders crosses at its live
# arity: each "@-" of its parameter's head is one null applied.
def J.eff.nulls(s: String) -> String:
  match s:
    case SCon{Chr{64}, SCon{Chr{45}, t}}:
      "(null)" ++ J.eff.nulls(t)
    case other:
      ""

def J.eff.wrap.go(+ty: String, +h: String, b: Bool) -> String:
  match b:
    case True{}:
      "((a) => (" ++ h ++ ")" ++ J.eff.nulls(ty) ++ "(a))"
    case False{}:
      h

def J.eff.wrap(+ty: String, +h: String) -> String:
  J.eff.wrap.go(ty, h, String.starts_with(ty, "@-"))

def J.eff.null(b: Bool, rest: List<&2, String>) -> List<&2, String>:
  match b:
    case True{}:
      "null" <> rest
    case False{}:
      rest

# The arguments an effect's host receives: its live ones, and a type
# value (a Type parameter) as null, as upstream's JS lane passes it.
def J.eff.args(ps: List<&2, Param>, kept: List<&2, String>) -> List<&2, String>:
  match ps kept:
    case Nil{} k:
      Nil{}
    case Param{+n, +m, +ty} <> +t Nil{}:
      Bool.pick(Unit -> List<&2, String>, G.keep(Param{n, m, ty}), u => Nil{},
        u => J.eff.null(Bool.and(G.erased_ty(ty), Bool.not(U32.is_eq(m, 1))), J.eff.args(t, Nil{})))(Unit{})
    case Param{+n, +m, +ty} <> +t +h <> +kt:
      Bool.pick(Unit -> List<&2, String>, G.keep(Param{n, m, ty}), u => J.eff.wrap(ty, h) <> J.eff.args(t, kt),
        u => J.eff.null(Bool.and(G.erased_ty(ty), Bool.not(U32.is_eq(m, 1))), J.eff.args(t, h <> kt)))(Unit{})

# The continuation of a host effect: one answering a value of an object
# type checks its tag first (io_tags).
def J.eff.tags.names(cs: List<&2, Ctor>) -> String:
  match cs:
    case Nil{}:
      ""
    case Ctor{n, fs} <> +t:
      "\"" ++ n ++ "\"" ++ Bool.pick(String, List.is_empty(&2, Ctor, t), "", ", ") ++ J.eff.tags.names(t)

def J.eff.tags.of(+t: String, d: Decl) -> String:
  match d:
    case DType{n, ps, +cs}:
      Bool.pick(String, List.is_empty(&2, Ctor, cs), "k",
        "io_tags(\"" ++ t ++ "\", [" ++ J.eff.tags.names(cs) ++ "], k)")
    case other:
      "k"

# The head of a type expression (IO in IO(A), Box in Box, List in List<A>).
def J.eff.head(a: Expr) -> String:
  match a:
    case ETy{t, xs}:
      t
    case EVar{t}:
      t
    case ECall{EVar{t}, xs}:
      t
    case other:
      ""

def J.eff.tags.ty(+g: G, a: Expr) -> String:
  +t = J.eff.head(a)
  Bool.pick(String, Nat.is_eq(J.kind(t), 8n),
    J.eff.tags.of(t, G.body(g, "%" ++ t)), "k")

def J.eff.tags.io(+g: G, +io: String, xs: List<&2, Expr>) -> String:
  match xs:
    case [a]:
      Bool.pick(String, Str.eq(io, "IO"), J.eff.tags.ty(g, a), "k")
    case other:
      "k"

def J.eff.tags(+g: G, d: Decl) -> String:
  match d:
    case DLaw{n, ps, ETy{io, xs}}:
      J.eff.tags.io(g, io, xs)
    case DLaw{n, ps, ECall{EVar{io}, xs}}:
      J.eff.tags.io(g, io, xs)
    case other:
      "k"

def J.def.eff(+g: G, +name: String, +mask: List<&2, Bool>, ps: List<&2, Param>, sig: Sig, ims: List<&2, String>) -> Gen(Unit):
  Sig{+params, env, wargs} = sig
  +host = J.host(String.to_lower(name))
  do Gen<Unit>:
    J.effs(ims, host)
    Gen.code(DStr{"function " ++ Gen.f(name) ++ "(" ++ J.params(params) ++ ") {\n  return (R) => (k) => io_req(EFF[\"" ++
      host ++ "\"], \"" ++ host ++ "\", [" ++ J.params(J.eff.args(ps, params)) ++ "], " ++
      J.eff.tags(g, G.body(g, "^" ++ name)) ++ ");\n}\n"})
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
    case DEff{n, +ps, ims}:
      J.def.eff(JG.g(j), name, mask, ps, Gen.sig(ps, mask, 0, Sig{Nil{}, Nil{}, Nil{}}), ims)
    case other:
      Bool.pick(Gen(Unit), U32.is_eq(kind, 2), J.wrapper(name, mask), Gen.pure(Unit, Unit{}))

def J.def(+j: JG, +name: String) -> Gen(Unit):
  J.def.decl(j, name, G.def(JG.g(j), name), G.body(JG.g(j), name))


# The queue of defs to generate, one def (fuel: its calls): JAllSel picks
# the step.
type JAllSel is Type:
  JAGo{j: JG, h: String, t: List<&2, String>, done: Set(), seen: Bool}
  JASeen{j: JG, h: String, t: List<&2, String>, r: Set() & Bool}
  JAAll{j: JG, queue: List<&2, String>, done: Set()}

def JAllSel.ty(k: JAllSel) -> Type:
  match k:
    case JAGo{j, h, t, done, seen}:
      Gen(Unit)
    case JASeen{j, h, t, r}:
      Gen(Unit)
    case JAAll{j, queue, done}:
      Gen(Unit)

def J.all.loop(n: Nat, k: JAllSel) -> JAllSel.ty(k):
  match n:
    case 0n:
      match k:
        case JAGo{j, h, t, done, seen}:
          J.out(Unit, Unit{})
        case JASeen{j, h, t, r}:
          J.out(Unit, Unit{})
        case JAAll{j, queue, done}:
          J.out(Unit, Unit{})
    case Succ{+fu}:
      match k:
        case JAGo{+j, +h, t, done, seen}:
          match seen:
            case True{}:
              J.all.loop(fu, JAAll{j, t, done})
            case False{}:
              do Gen<Unit>:
                J.def(j, h)
                refs : List<&2, String> <- Gen.take_refs()
                J.all.loop(fu, JAAll{j, List.append(&2, String, refs, t), Set.add(done, h)})
        case JASeen{+j, +h, t, r}:
          (done, seen) = r
          J.all.loop(fu, JAGo{j, h, t, done, seen})
        case JAAll{+j, queue, done}:
          match queue:
            case Nil{}:
              Gen.pure(Unit, Unit{})
            case +h <> t:
              J.all.loop(fu, JASeen{j, h, t, Set.has(done, h)})

def J.all(j: JG, queue: List<&2, String>, done: Set()) -> Gen(Unit):
  J.all.loop(Fuel.max(), JAAll{j, queue, done})

# The value printers, one def (fuel: its calls, which reach other types):
# JPrSel picks the step.
type JPrSel is Type:
  JRTuple{j: JG, xs: List<&2, Expr>, path: String}
  JRFields{j: JG, sub: List<&2, TB>, fs: List<&2, Field>, path: String, i: U32}
  JRCtor{j: JG, sub: List<&2, TB>, name: String, fields: List<&2, Field>, single: Bool}
  JRCtors{j: JG, sub: List<&2, TB>, cs: List<&2, Ctor>, single: Bool}
  JRAdt{j: JG, ty: Expr, d: Decl}
  JRHead{j: JG, ty: Expr, k: Nat}
  JRBody{j: JG, ty: Expr, h: String}
  JRMemo{j: JG, ty: Expr, key: String, m: Maybe<&2, String>}
  JRPrinter{j: JG, ty0: Expr}

def JPrSel.ty(k: JPrSel) -> Type:
  match k:
    case JRTuple{j, xs, path}:
      Gen(Doc)
    case JRFields{j, sub, fs, path, i}:
      Gen(Doc)
    case JRCtor{j, sub, name, fields, single}:
      Gen(Doc)
    case JRCtors{j, sub, cs, single}:
      Gen(Doc)
    case JRAdt{j, ty, d}:
      Gen(Doc)
    case JRHead{j, ty, k}:
      Gen(Doc)
    case JRBody{j, ty, h}:
      Gen(Doc)
    case JRMemo{j, ty, key, m}:
      Gen(String)
    case JRPrinter{j, ty0}:
      Gen(String)

def J.printer.go(n: Nat, k: JPrSel) -> JPrSel.ty(k):
  match n:
    case 0n:
      match k:
        case JRTuple{j, xs, path}:
          J.out(Doc, DNil{})
        case JRFields{j, sub, fs, path, i}:
          J.out(Doc, DNil{})
        case JRCtor{j, sub, name, fields, single}:
          J.out(Doc, DNil{})
        case JRCtors{j, sub, cs, single}:
          J.out(Doc, DNil{})
        case JRAdt{j, ty, d}:
          J.out(Doc, DNil{})
        case JRHead{j, ty, k}:
          J.out(Doc, DNil{})
        case JRBody{j, ty, h}:
          J.out(Doc, DNil{})
        case JRMemo{j, ty, key, m}:
          J.out(String, "")
        case JRPrinter{j, ty0}:
          J.out(String, "")
    case Succ{+fu}:
      match k:
        case JRTuple{+j, xs, +path}:
          match xs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case h <> Nil{}:
              do Gen<Doc>:
                f : String <- J.printer.go(fu, JRPrinter{j, h})
                return DStr{"s += " ++ f ++ "(" ++ path ++ ");\n"}
            case h <> t:
              do Gen<Doc>:
                f : String <- J.printer.go(fu, JRPrinter{j, h})
                rest : Doc <- J.printer.go(fu, JRTuple{j, t, "(" ++ path ++ ").snd"})
                return Doc.list([DStr{"s += " ++ f ++ "((" ++ path ++ ").fst) + \", \";\n"}, rest])
        case JRFields{+j, +sub, fs, +path, +i}:
          match fs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case Field{+n, t} <> rest:
              do Gen<Doc>:
                f : String <- J.printer.go(fu, JRPrinter{j, Ty.subst(t, sub)})
                more : Doc <- J.printer.go(fu, JRFields{j, sub, rest, path, U32.inc(i)})
                return Doc.list([DStr{Bool.pick(String, U32.is_zero(i), "", "s += \", \";\n") ++ "s += " ++ f ++ "((" ++ path ++
                  ")" ++ J.acc(n) ++ ");\n"}, more])
        case JRCtor{+j, +sub, +name, fields, +single}:
          do Gen<Doc>:
            fs : Doc <- J.printer.go(fu, JRFields{j, sub, fields, "v", 0})
            return Doc.list([DStr{Bool.pick(String, single, "if (true)", "if (v.$ === \"" ++ name ++ "\")") ++
              " { let s = \"" ++ name ++ "{\";\n"}, fs, DStr{"return s + \"}\"; }\n"}])
        case JRCtors{+j, +sub, cs, +single}:
          match cs:
            case Nil{}:
              Gen.pure(Doc, DNil{})
            case Ctor{+name, fields} <> t:
              do Gen<Doc>:
                one : Doc <- J.printer.go(fu, JRCtor{j, sub, name, fields, single})
                rest : Doc <- J.printer.go(fu, JRCtors{j, sub, t, single})
                return Doc.list([one, rest])
        case JRAdt{+j, +ty, d}:
          match d:
            case DType{name, ps, +cs}:
              do Gen<Doc>:
                b : Doc <- J.printer.go(fu, JRCtors{j, Ty.bind(ps, Ty.args(ty)), cs, Nat.is_eq(List.length(&2, Ctor, cs), 1n)})
                return Doc.list([b, DStr{"return \"?\";\n"}])
            case other:
              Gen.pure(Doc, DStr{"return \"?\";\n"})
        case JRHead{+j, +ty, k}:
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
                e : String <- J.printer.go(fu, JRPrinter{j, P.last(Ty.args(ty))})
                return DStr{"const xs = [];\nfor (; v.$ === \"Con\"; v = v.tail) xs.push(" ++ e ++
                  "(v.head));\nreturn \"[\" + xs.join(\", \") + \"]\";\n"}
            case 6n:
              do Gen<Doc>:
                parts : Doc <- J.printer.go(fu, JRTuple{j, Ty.tuple(ty), "v"})
                return Doc.list([DStr{"let s = \"(\";\n"}, parts, DStr{"return s + \")\";\n"}])
            case 7n:
              Gen.pure(Doc, DStr{"return \"<function>\";\n"})
            case 8n:
              Gen.pure(Doc, DStr{"return v ? \"True{}\" : \"False{}\";\n"})
            case 9n:
              do Gen<Doc>:
                e : String <- J.printer.go(fu, JRPrinter{j, P.last(Ty.args(ty))})
                return DStr{"return \"[\" + v.map((x) => " ++ e ++ "(x)).join(\", \") + \"]\";\n"}
            case 10n:
              Gen.pure(Doc, DStr{"return \"{==}\";\n"})
            case 11n+p:
              J.printer.go(fu, JRAdt{j, ty, G.body(JG.g(j), "%" ++ Ty.head(ty))})
        case JRBody{+j, +ty, +h}:
          J.printer.go(fu, JRHead{j, ty, P.which(Ty.alias(h), ["U32", "Nat", "F32", "Char", "String", "List", "&", "->", "Bool",
            "Array", "=="])})
        case JRMemo{+j, +ty, +key, m}:
          match m:
            case Some{f}:
              Gen.pure(String, f)
            case None{}:
              do Gen<String>:
                +k : U32 <- Gen.fresh()
                +f : String <- Gen.pure(String, "P" ++ U32.show(k))
                Gen.memo.add(Bind{key, f})
                b : Doc <- J.printer.go(fu, JRBody{j, ty, Ty.head(ty)})
                Gen.code(Doc.list([DStr{"function " ++ f ++ "(v) {\n"}, b, DStr{"}\n"}]))
                return f
        # The name of a JS function that prints values of a type.
        case JRPrinter{+j, +ty0}:
          +ty = Ty.norm(JG.g(j), ty0, 16n)
          +key = Expr.show(ty)
          do Gen<String>:
            m : Maybe<&2, String> <- Gen.memo.find(key)
            J.printer.go(fu, JRMemo{j, ty, key, m})

# The name of a JS function that prints values of a type.
def J.printer(j: JG, ty0: Expr) -> Gen(String):
  J.printer.go(Fuel.max(), JRPrinter{j, ty0})

# Entry points
# ============

# The program builders and the driver: they call the compilers above.

def K.fin(r: Unit & KSt) -> KOut:
  (u, st) = r
  KSt{+n, sl, +curl, cur, out, +fns, todo, +frames, errs, flat, memo} = st
  KOut{Doc.flat(Doc.list([DStr{"#define K_NLABELS " ++ U32.show(n) ++ "\n" ++ K.defines(fns) ++ "KCONST KW K_FRAME[] = {" ++
    K.frame_table(frames, 0, n) ++ "0};\n\nKINLINE KW k_frame_size(KW l) {\n  return l < K_NLABELS ? K_FRAME[l] : 0;\n}\n\n"},
    flat, DStr{"\nKINLINE KW k_kq(KTHR KCtx *c, KTHR bool *ok) {\nswitch (c->kq) {\n" ++ KQ.cases.of(memo) ++
    "default:\n*ok = false;\nreturn 0;\n}\n}\n"}, DStr{"\nKINLINE void k_cases(KTHR KCtx *c) {\nswitch (c->pc) {\n"}, out, K.block_doc(curl, cur),
    DStr{"default: {\nk_fail(c, KE_PC);\nbreak;\n}\n}\n}\n"}])), K.wraps(fns), errs}

def K.program.m(+g: G, ts: List<&2, String>, clos: List<&2, String>) -> KM(Unit):
  do KM<Unit>:
    K.targets(ts)
    K.clos(clos)
    K.all(g, 100000n)

# The device code for the !-call targets ts, with wrappers for the defs the
# CPU makes closures of (clos), which the targets may be handed.
def K.program(+g: G, ts: List<&2, String>, clos: List<&2, String>) -> KOut:
  K.fin(K.program.m(g, ts, clos)(KSt{8, 0, 0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}, DNil{}, Nil{}}))

def Gen.gpu.tail(+g: G, ts: List<&2, String>, clos: List<&2, String>) -> String:
  match ts:
    case Nil{}:
      ""
    case +t <> +rest:
      Gen.gpu.emit(g, t <> rest, K.program(g, t <> rest, clos))

# Core IR
# =======
#
# The C back end's input goes through the core IR (core.bend): Lo lowers a
# def to it, marking each argument of a call of a global def relevant or
# erased by the def's parameter mask; Core.Tm.erase boxes the erased ones
# and the types left in the body (PROOF.bend proves that this preserves the
# IR's semantics); Inl inlines monadic binds; Core.Tm.red makes each lambda
# applied to one argument a let (REDPROOF.bend proves that this preserves
# the semantics too); Core.Tm.known resolves each match on a known
# constructor (KNOWNPROOF.bend); Up raises the result back to an Expr.

def Lo.pt.push(a: Core.Pt, p: Core.Pt) -> Core.Pt:
  match p:
    case Core.PtCtr{k, ps}:
      Core.PtCtr{k, a <> ps}
    case other:
      other

def Lo.pat(p: Pat) -> Core.Pt:
  match p:
    case PVar{x}:
      Core.PtVar{x}
    case PCtor{n, ps}:
      match ps:
        case Nil{}:
          Core.PtCtr{n, Nil{}}
        case a <> t:
          Lo.pt.push(Lo.pat(a), Lo.pat(PCtor{n, t}))
    case PNat{n}:
      Core.PtNat{n}
    case PSucc{k, q}:
      Core.PtSuc{k, Lo.pat(q)}
    case PNum{n}:
      Core.PtNum{n}
    case PFlt{s}:
      Core.PtFlt{s}

def Lo.pats(ps: List<&2, Pat>) -> List<&2, Core.Pt>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> t:
      Lo.pat(p) <> Lo.pats(t)

def Lo.rel(m: List<&2, Bool>) -> Core.Rel:
  match m:
    case False{} <> t:
      Core.Era{}
    case other:
      Core.Run{}

def Lo.tail(m: List<&2, Bool>) -> List<&2, Bool>:
  match m:
    case Nil{}:
      Nil{}
    case h <> t:
      t

# Whether f names a global def (not a local of bound).
def Lo.bound(+bound: Set(), +n: String) -> Bool:
  Pair.snd(Set(), Bool, Set.has(bound, n))

def Lo.bind(xs: List<&2, String>, s: Set()) -> Set():
  match xs:
    case Nil{}:
      s
    case x <> t:
      Lo.bind(t, Set.add(s, x))

def Lo.global(+bound: Set(), f: Expr) -> Bool:
  match f:
    case EVar{+n}:
      Bool.not(Lo.bound(bound, n))
    case other:
      False{}

def Lo.fname(f: Expr) -> String:
  match f:
    case EVar{n}:
      n
    case other:
      ""

# The mask of a call's arguments: the callee's (top: e is the call itself),
# else what the walk has left of it (a list field is walked as its head and
# the node rebuilt with the rest).
def Lo.mask(top: Bool, +g: G, +f: Expr, mask: List<&2, Bool>) -> List<&2, Bool>:
  match top:
    case True{}:
      DInfo.mask(G.def(g, Lo.fname(f)))
    case False{}:
      mask

def Lo.arg(+m: List<&2, Bool>, a: Core.Tm, rest: Core.Tm) -> Core.Tm:
  Core.Tm.push.call(Core.Arg{Lo.rel(m), a}, rest)

def Lo.go(e: Expr, +g: G, +bound: Set(), +top: Bool, +mask: List<&2, Bool>) -> Core.Tm:
  match e:
    case EVar{+n}:
      Bool.pick(Core.Tm, Lo.bound(bound, n), Core.CVar{n}, Core.CRef{n})
    case ENum{n}:
      Core.CLit{Core.LNum{n}}
    case ENat{n}:
      Core.CLit{Core.LNat{n}}
    case EFlt{s}:
      Core.CLit{Core.LFlt{s}}
    case EStr{s}:
      Core.CLit{Core.LStr{s}}
    case ECall{+f, args}:
      match args:
        case Nil{}:
          Bool.pick(Unit -> Core.Tm, Lo.global(bound, f), u => Core.CCall{Lo.fname(f), Nil{}},
            u => Core.CApp{Lo.go(f, g, bound, True{}, Nil{}), Nil{}})(Unit{})
        case +a <> +t:
          Bool.pick(Unit -> Core.Tm, Lo.global(bound, f),
            u => Lo.arg(Lo.mask(top, g, f, mask), Lo.go(a, g, bound, True{}, Nil{}),
              Lo.go(ECall{f, t}, g, bound, False{}, Lo.tail(Lo.mask(top, g, f, mask)))),
            u => Core.Tm.push(Lo.go(a, g, bound, True{}, Nil{}), Lo.go(ECall{f, t}, g, bound, False{}, Nil{})))(Unit{})
    case ECtor{+n, args}:
      match args:
        case Nil{}:
          Core.CCtr{n, Nil{}}
        case a <> t:
          Core.Tm.push(Lo.go(a, g, bound, True{}, Nil{}), Lo.go(ECtor{n, t}, g, bound, False{}, Nil{}))
    case ELam{+p, b}:
      Core.CLam{Lo.pat(p), Lo.go(b, g, Lo.bind(Pat.vars(p, Nil{}), bound), True{}, Nil{})}
    case ELet{+p, v, b}:
      Core.CLet{Lo.pat(p), Lo.go(v, g, bound, True{}, Nil{}), Lo.go(b, g, Lo.bind(Pat.vars(p, Nil{}), bound), True{}, Nil{})}
    case EMatch{scrs, +cases}:
      match scrs:
        case a <> t:
          Core.Tm.push(Lo.go(a, g, bound, True{}, Nil{}), Lo.go(EMatch{t, cases}, g, bound, False{}, Nil{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.CMat{Nil{}, Nil{}}
            case c <> t:
              Core.Tm.push.case(Lo.go(c, g, bound, True{}, Nil{}), Lo.go(EMatch{Nil{}, t}, g, bound, False{}, Nil{}))
    case ECase{+ps, b}:
      Core.CCse{Lo.pats(ps), Lo.go(b, g, Lo.bind(Pats.vars(ps, Nil{}), bound), True{}, Nil{})}
    case ESucc{k, x}:
      Core.CSuc{k, Lo.go(x, g, bound, True{}, Nil{})}
    case EOp{op, a, b}:
      Core.COp{op, Lo.go(a, g, bound, True{}, Nil{}), Lo.go(b, g, bound, True{}, Nil{})}
    case EAnn{x, ty}:
      Core.CAnn{Lo.go(x, g, bound, True{}, Nil{}), ty}
    case ETy{+n, args}:
      match args:
        case Nil{}:
          Core.CTyp{n, Nil{}}
        case a <> t:
          Core.Tm.push(Lo.go(a, g, bound, True{}, Nil{}), Lo.go(ETy{n, t}, g, bound, False{}, Nil{}))
    case EErr{m}:
      Core.CErr{m}

def Lo.params(ps: List<&2, Param>, +mask: List<&2, Bool>) -> List<&2, Core.Par>:
  match ps:
    case Nil{}:
      Nil{}
    case Param{x, m, t} <> r:
      Core.Par{x, Lo.rel(mask), m, t} <> Lo.params(r, Lo.tail(mask))

def Lo.def(+g: G, +name: String, +ps: List<&2, Param>, body: Expr, ret: Expr) -> Core.Def:
  +bound = Lo.bind(Mod.param_names(ps), Set.new())
  Core.Def{name, Lo.params(ps, DInfo.mask(G.def(g, name))), Lo.go(body, g, bound, True{}, Nil{}),
    Lo.go(ret, g, bound, True{}, Nil{})}

def Up.pt.push(a: Pat, p: Pat) -> Pat:
  match p:
    case PCtor{k, ps}:
      PCtor{k, a <> ps}
    case other:
      other

def Up.pat(p: Core.Pt) -> Pat:
  match p:
    case Core.PtVar{x}:
      PVar{x}
    case Core.PtCtr{n, ps}:
      match ps:
        case Nil{}:
          PCtor{n, Nil{}}
        case a <> t:
          Up.pt.push(Up.pat(a), Up.pat(Core.PtCtr{n, t}))
    case Core.PtNat{n}:
      PNat{n}
    case Core.PtSuc{k, q}:
      PSucc{k, Up.pat(q)}
    case Core.PtNum{n}:
      PNum{n}
    case Core.PtFlt{s}:
      PFlt{s}

def Up.pats(ps: List<&2, Core.Pt>) -> List<&2, Pat>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> t:
      Up.pat(p) <> Up.pats(t)

def Up.lit(l: Core.Lit) -> Expr:
  match l:
    case Core.LNum{n}:
      ENum{n}
    case Core.LNat{n}:
      ENat{n}
    case Core.LFlt{s}:
      EFlt{s}
    case Core.LStr{s}:
      EStr{s}

def Up.go(t: Core.Tm) -> Expr:
  match t:
    case Core.CVar{x}:
      EVar{x}
    case Core.CLit{l}:
      Up.lit(l)
    case Core.CRef{f}:
      EVar{f}
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          ECall{EVar{f}, Nil{}}
        case a <> r:
          match a:
            case Core.Arg{rel, e}:
              Expr.push(Up.go(e), Up.go(Core.CCall{f, r}))
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          ECall{Up.go(f), Nil{}}
        case a <> r:
          Expr.push(Up.go(a), Up.go(Core.CApp{f, r}))
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          ECtor{k, Nil{}}
        case a <> r:
          Expr.push(Up.go(a), Up.go(Core.CCtr{k, r}))
    case Core.CLam{p, b}:
      ELam{Up.pat(p), Up.go(b)}
    case Core.CLet{p, v, b}:
      ELet{Up.pat(p), Up.go(v), Up.go(b)}
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> r:
          Expr.push(Up.go(a), Up.go(Core.CMat{r, cases}))
        case Nil{}:
          match cases:
            case Nil{}:
              EMatch{Nil{}, Nil{}}
            case c <> r:
              Expr.push.case(Up.go(c), Up.go(Core.CMat{Nil{}, r}))
    case Core.CCse{ps, b}:
      ECase{Up.pats(ps), Up.go(b)}
    case Core.CSuc{k, e}:
      ESucc{k, Up.go(e)}
    case Core.COp{op, a, b}:
      EOp{op, Up.go(a), Up.go(b)}
    case Core.CAnn{e, ty}:
      EAnn{Up.go(e), ty}
    case Core.CTyp{n, as}:
      match as:
        case Nil{}:
          ETy{n, Nil{}}
        case a <> r:
          Expr.push(Up.go(a), Up.go(Core.CTyp{n, r}))
    case Core.CBox{}:
      ETy{"", Nil{}}
    case Core.CErr{m}:
      EErr{m}

def Up.params(ps: List<&2, Core.Par>) -> List<&2, Param>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Par{x, rel, m, t} <> r:
      Param{x, m, t} <> Up.params(r)

def Up.def(d: Core.Def) -> Decl:
  match d:
    case Core.Def{name, ps, body, ret}:
      DDef{name, Up.params(ps), Up.go(body), Up.go(ret)}

# Inlining of monadic bind and pure
# ---------------------------------
#
# A do block is a chain of M.bind(m, x => ..) calls ending in M.pure(e); for
# a state monad (Parser, Gen, KM; P and K in check.bend) each bind builds a
# closure for the step and another for the continuation. Inl expands full
# calls of M.bind, M.pure and the M. defs they call (M.go, M.go.done): the
# callee's body, renamed apart and inlined in turn, takes each argument in
# place of its parameter when that moves no work into a lambda (else a let
# binds it), and each place an argument lands is reduced: an applied lambda
# becomes a let, and a let of a known constructor takes its fields, as a
# match on them with one case (they are evaluated before any is bound, so
# none sees another's name; a match of one is Core.Tm.known's, after the
# inliner).
# A do block becomes one closure. The callee's names are fresh (a suffix
# per depth), so no substitution captures, and each expansion walks only
# the callee's body: the pass is linear in the program.

# An argument for a parameter x used n times, top of them outside a lambda.
type IB is Data:
  IB{x: String, e: Core.Tm, n: U32, top: U32}

# The walk's modes: IAll does the children, then the node; IKids the
# children (a list field as its head and the node rebuilt with the rest);
# INode the rules at the node; IFin{top} them when top; ISub{x, v, top}
# puts v for x and reduces where it lands; IPlan{ps, as, s} and IBinds{bs}
# give an expanded body its arguments.
type IM is Data:
  IAll{}
  IKids{}
  INode{}
  IFin{top: Bool}
  ISub{x: String, v: Core.Tm, top: Bool}
  IPlan{ps: List<&2, Core.Par>, as: List<&2, Core.Arg>, s: String}
  IBinds{bs: List<&2, IB>}

# The variables of p.
def Inl.pvars(p: Core.Pt, +acc: List<&2, String>) -> List<&2, String>:
  match p:
    case Core.PtVar{x}:
      x <> acc
    case Core.PtCtr{k, ps}:
      match ps:
        case Nil{}:
          acc
        case q <> t:
          Inl.pvars(Core.PtCtr{k, t}, Inl.pvars(q, acc))
    case Core.PtSuc{k, q}:
      Inl.pvars(q, acc)
    case other:
      acc

def Inl.ppvars(ps: List<&2, Core.Pt>, acc: List<&2, String>) -> List<&2, String>:
  match ps:
    case Nil{}:
      acc
    case p <> t:
      Inl.ppvars(t, Inl.pvars(p, acc))

# The names in t: sel 0 the variables it reads, 1 those it binds, 2 those
# it reads outside a lambda, 3 the defs it calls or refers to (each on acc,
# maybe twice).
def Inl.names(t: Core.Tm, +sel: U32, +acc: List<&2, String>) -> List<&2, String>:
  match t:
    case Core.CVar{x}:
      Bool.pick(List<&2, String>, Bool.or(U32.is_zero(sel), U32.is_eq(sel, 2)), x <> acc, acc)
    case Core.CRef{f}:
      Bool.pick(List<&2, String>, U32.is_eq(sel, 3), f <> acc, acc)
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          Bool.pick(List<&2, String>, U32.is_eq(sel, 3), f <> acc, acc)
        case Core.Arg{r, e} <> t2:
          Inl.names(Core.CCall{f, t2}, sel, Inl.names(e, sel, acc))
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Inl.names(f, sel, acc)
        case a <> t2:
          Inl.names(Core.CApp{f, t2}, sel, Inl.names(a, sel, acc))
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          acc
        case a <> t2:
          Inl.names(Core.CCtr{k, t2}, sel, Inl.names(a, sel, acc))
    case Core.CLam{p, b}:
      Bool.pick(Unit -> List<&2, String>, U32.is_eq(sel, 2), u => acc,
        u => Inl.names(b, sel, Bool.pick(List<&2, String>, U32.is_eq(sel, 1), Inl.pvars(p, acc), acc)))(Unit{})
    case Core.CLet{p, v, b}:
      Inl.names(b, sel, Inl.names(v, sel, Bool.pick(List<&2, String>, U32.is_eq(sel, 1), Inl.pvars(p, acc), acc)))
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> t2:
          Inl.names(Core.CMat{t2, cases}, sel, Inl.names(a, sel, acc))
        case Nil{}:
          match cases:
            case Nil{}:
              acc
            case c <> t2:
              Inl.names(Core.CMat{Nil{}, t2}, sel, Inl.names(c, sel, acc))
    case Core.CCse{ps, b}:
      Inl.names(b, sel, Bool.pick(List<&2, String>, U32.is_eq(sel, 1), Inl.ppvars(ps, acc), acc))
    case Core.CSuc{k, e}:
      Inl.names(e, sel, acc)
    case Core.COp{op, a, b}:
      Inl.names(b, sel, Inl.names(a, sel, acc))
    case Core.CAnn{e, ty}:
      Inl.names(e, sel, acc)
    case Core.CTyp{n, as}:
      match as:
        case Nil{}:
          acc
        case a <> t2:
          Inl.names(Core.CTyp{n, t2}, sel, Inl.names(a, sel, acc))
    case other:
      acc

def Inl.count(xs: List<&2, String>, +x: String, +n: U32) -> U32:
  match xs:
    case Nil{}:
      n
    case +y <> t:
      Inl.count(t, x, Bool.pick(U32, String.eq(y, x), U32.inc(n), n))

def Inl.uses(+t: Core.Tm, +sel: U32, +x: String) -> U32:
  Inl.count(Inl.names(t, sel, Nil{}), x, 0)

# Whether no name of xs is in ys.
def Inl.apart(xs: List<&2, String>, +ys: List<&2, String>) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case +x <> t:
      Bool.pick(Unit -> Bool, Str.has(ys, x), u => False{}, u => Inl.apart(t, ys))(Unit{})

def Inl.rn(+s: String, +x: String) -> String:
  Bool.pick(String, String.eq(x, "_"), x, x ++ s)

def Inl.rpat(p: Core.Pt, +s: String) -> Core.Pt:
  match p:
    case Core.PtVar{x}:
      Core.PtVar{Inl.rn(s, x)}
    case Core.PtCtr{k, ps}:
      match ps:
        case Nil{}:
          Core.PtCtr{k, Nil{}}
        case q <> t:
          Lo.pt.push(Inl.rpat(q, s), Inl.rpat(Core.PtCtr{k, t}, s))
    case Core.PtSuc{k, q}:
      Core.PtSuc{k, Inl.rpat(q, s)}
    case other:
      other

def Inl.rpats(ps: List<&2, Core.Pt>, +s: String) -> List<&2, Core.Pt>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> t:
      Inl.rpat(p, s) <> Inl.rpats(t, s)

# t with every variable x renamed x ++ s (a def's body: its only free
# variables are its parameters).
def Inl.ren(t: Core.Tm, +s: String) -> Core.Tm:
  match t:
    case Core.CVar{x}:
      Core.CVar{Inl.rn(s, x)}
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          Core.CCall{f, Nil{}}
        case Core.Arg{r, e} <> t2:
          Core.Tm.push.call(Core.Arg{r, Inl.ren(e, s)}, Inl.ren(Core.CCall{f, t2}, s))
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Core.CApp{Inl.ren(f, s), Nil{}}
        case a <> t2:
          Core.Tm.push(Inl.ren(a, s), Inl.ren(Core.CApp{f, t2}, s))
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          Core.CCtr{k, Nil{}}
        case a <> t2:
          Core.Tm.push(Inl.ren(a, s), Inl.ren(Core.CCtr{k, t2}, s))
    case Core.CLam{p, b}:
      Core.CLam{Inl.rpat(p, s), Inl.ren(b, s)}
    case Core.CLet{p, v, b}:
      Core.CLet{Inl.rpat(p, s), Inl.ren(v, s), Inl.ren(b, s)}
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> t2:
          Core.Tm.push(Inl.ren(a, s), Inl.ren(Core.CMat{t2, cases}, s))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.CMat{Nil{}, Nil{}}
            case c <> t2:
              Core.Tm.push.case(Inl.ren(c, s), Inl.ren(Core.CMat{Nil{}, t2}, s))
    case Core.CCse{ps, b}:
      Core.CCse{Inl.rpats(ps, s), Inl.ren(b, s)}
    case Core.CSuc{k, e}:
      Core.CSuc{k, Inl.ren(e, s)}
    case Core.COp{op, a, b}:
      Core.COp{op, Inl.ren(a, s), Inl.ren(b, s)}
    case Core.CAnn{e, ty}:
      Core.CAnn{Inl.ren(e, s), ty}
    case Core.CTyp{n, as}:
      match as:
        case Nil{}:
          Core.CTyp{n, Nil{}}
        case a <> t2:
          Core.Tm.push(Inl.ren(a, s), Inl.ren(Core.CTyp{n, t2}, s))
    case other:
      other

def Inl.binds(+x: String, p: Core.Pt) -> Bool:
  Str.has(Inl.pvars(p, Nil{}), x)

def Inl.binds.any(+x: String, ps: List<&2, Core.Pt>) -> Bool:
  Str.has(Inl.ppvars(ps, Nil{}), x)

# Whether t is a value: evaluating it builds or reads, and never loops.
def Inl.value(t: Core.Tm) -> Bool:
  match t:
    case Core.CVar{x}:
      True{}
    case Core.CLit{l}:
      True{}
    case Core.CLam{p, b}:
      True{}
    case Core.CBox{}:
      True{}
    case Core.CTyp{n, as}:
      True{}
    case Core.CCtr{k, as}:
      List.is_empty(&2, Core.Tm, as)
    case other:
      False{}

# Whether t is a lambda or a constructor (moved, it can make a redex).
def Inl.shape(t: Core.Tm) -> Bool:
  match t:
    case Core.CLam{p, b}:
      True{}
    case Core.CCtr{k, as}:
      True{}
    case other:
      False{}

def Inl.tms.len(ts: List<&2, Core.Tm>) -> Nat:
  match ts:
    case Nil{}:
      0n
    case t <> r:
      1n+Inl.tms.len(r)

def Inl.pts.len(ps: List<&2, Core.Pt>) -> Nat:
  match ps:
    case Nil{}:
      0n
    case p <> r:
      1n+Inl.pts.len(r)

def Inl.args.len(as: List<&2, Core.Arg>) -> Nat:
  match as:
    case Nil{}:
      0n
    case a <> r:
      1n+Inl.args.len(r)

def Inl.pars.len(ps: List<&2, Core.Par>) -> Nat:
  match ps:
    case Nil{}:
      0n
    case p <> r:
      1n+Inl.pars.len(r)

# Lets binding each pattern to its term, around b.
def Inl.hit(+d: Core.Def, +f: String, +as: List<&2, Core.Arg>) -> Bool:
  match d:
    case Core.Def{+name, ps, b, ret}:
      Bool.and(String.eq(name, f), Nat.is_eq(Inl.pars.len(ps), Inl.args.len(as)))

def Inl.pars(d: Core.Def) -> List<&2, Core.Par>:
  match d:
    case Core.Def{name, ps, b, ret}:
      ps

def Inl.body(d: Core.Def) -> Core.Tm:
  match d:
    case Core.Def{name, ps, b, ret}:
      b

def Inl.plan(ps: List<&2, Core.Par>, as: List<&2, Core.Arg>, +b: Core.Tm, +s: String) -> List<&2, IB>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Par{x, rel, m, ty} <> pr:
      match as:
        case Nil{}:
          Nil{}
        case Core.Arg{r, e} <> ar:
          +y = Inl.rn(s, x)
          IB{y, e, Inl.uses(b, 0, y), Inl.uses(b, 2, y)} <> Inl.plan(pr, ar, b, s)

def Inl.app(f: Core.Tm, as: List<&2, Core.Tm>) -> Core.Tm:
  match as:
    case Nil{}:
      f
    case a <> t:
      Core.CApp{f, a <> t}

def Inl.fsuf(n: Nat) -> String:
  "@i" ++ U32.show(U32.from_nat(n))

# The walk (see IM). Fuel bounds its depth.
def Inl.go(+n: Nat, +c: Map<&2, Core.Def>, mode: IM, +t: Core.Tm) -> Core.Tm:
  match n:
    case 0n:
      t
    case 1n+p:
      match mode:
        case IAll{}:
          Inl.go(p, c, INode{}, Inl.go(p, c, IKids{}, t))
        case IFin{top}:
          Bool.pick(Unit -> Core.Tm, top, u => Inl.go(p, c, INode{}, t), u => t)(Unit{})
        case IPlan{ps, as, s}:
          Inl.go(p, c, IBinds{Inl.plan(ps, as, t, s)}, t)
        case IBinds{bs}:
          match bs:
            case Nil{}:
              t
            case IB{+x, +e, +k, +top} <> +r:
              Bool.pick(Unit -> Core.Tm, Bool.and(U32.is_zero(k), Inl.value(e)), u => Inl.go(p, c, IBinds{r}, t),
                u => Bool.pick(Unit -> Core.Tm, Bool.or(Bool.and(Inl.value(e), Bool.not(Inl.shape(e))), Bool.and(U32.is_eq(k, 1), Bool.or(U32.is_eq(top, 1), Inl.shape(e)))),
                  u2 => Inl.go(p, c, IBinds{r}, Inl.go(p, c, ISub{x, e, True{}}, t)),
                  u2 => Core.CLet{Core.PtVar{x}, e, Inl.go(p, c, IBinds{r}, t)})(Unit{}))(Unit{})
        case ISub{+x, +v, top}:
          match t:
            case Core.CVar{+y}:
              Bool.pick(Core.Tm, String.eq(x, y), v, Core.CVar{y})
            case Core.CCall{f, as}:
              match as:
                case Nil{}:
                  Core.CCall{f, Nil{}}
                case Core.Arg{r, e} <> t2:
                  Inl.go(p, c, IFin{top}, Core.Tm.push.call(Core.Arg{r, Inl.go(p, c, ISub{x, v, True{}}, e)},
                    Inl.go(p, c, ISub{x, v, False{}}, Core.CCall{f, t2})))
            case Core.CApp{f, as}:
              match as:
                case Nil{}:
                  Inl.go(p, c, IFin{top}, Core.CApp{Inl.go(p, c, ISub{x, v, True{}}, f), Nil{}})
                case a <> t2:
                  Inl.go(p, c, IFin{top}, Core.Tm.push(Inl.go(p, c, ISub{x, v, True{}}, a),
                    Inl.go(p, c, ISub{x, v, False{}}, Core.CApp{f, t2})))
            case Core.CCtr{k, as}:
              match as:
                case Nil{}:
                  Core.CCtr{k, Nil{}}
                case a <> t2:
                  Core.Tm.push(Inl.go(p, c, ISub{x, v, True{}}, a), Inl.go(p, c, ISub{x, v, False{}}, Core.CCtr{k, t2}))
            case Core.CLam{+pt, +b}:
              Bool.pick(Unit -> Core.Tm, Inl.binds(x, pt), u => Core.CLam{pt, b},
                u => Core.CLam{pt, Inl.go(p, c, ISub{x, v, True{}}, b)})(Unit{})
            case Core.CLet{+pt, v2, +b}:
              Inl.go(p, c, IFin{top}, Core.CLet{pt, Inl.go(p, c, ISub{x, v, True{}}, v2),
                Bool.pick(Unit -> Core.Tm, Inl.binds(x, pt), u => b, u => Inl.go(p, c, ISub{x, v, True{}}, b))(Unit{})})
            case Core.CMat{scrs, cases}:
              match scrs:
                case a <> t2:
                  Inl.go(p, c, IFin{top}, Core.Tm.push(Inl.go(p, c, ISub{x, v, True{}}, a),
                    Inl.go(p, c, ISub{x, v, False{}}, Core.CMat{t2, cases})))
                case Nil{}:
                  match cases:
                    case Nil{}:
                      Core.CMat{Nil{}, Nil{}}
                    case cs <> t2:
                      Core.Tm.push.case(Inl.go(p, c, ISub{x, v, True{}}, cs), Inl.go(p, c, ISub{x, v, False{}}, Core.CMat{Nil{}, t2}))
            case Core.CCse{+ps, +b}:
              Bool.pick(Unit -> Core.Tm, Inl.binds.any(x, ps), u => Core.CCse{ps, b},
                u => Core.CCse{ps, Inl.go(p, c, ISub{x, v, True{}}, b)})(Unit{})
            case Core.CSuc{k, e}:
              Core.CSuc{k, Inl.go(p, c, ISub{x, v, True{}}, e)}
            case Core.COp{op, a, b}:
              Core.COp{op, Inl.go(p, c, ISub{x, v, True{}}, a), Inl.go(p, c, ISub{x, v, True{}}, b)}
            case Core.CAnn{e, ty}:
              Core.CAnn{Inl.go(p, c, ISub{x, v, True{}}, e), ty}
            case other:
              other
        case IKids{}:
          match t:
            case Core.CCall{f, as}:
              match as:
                case Nil{}:
                  Core.CCall{f, Nil{}}
                case Core.Arg{r, e} <> t2:
                  Core.Tm.push.call(Core.Arg{r, Inl.go(p, c, IAll{}, e)}, Inl.go(p, c, IKids{}, Core.CCall{f, t2}))
            case Core.CApp{f, as}:
              match as:
                case Nil{}:
                  Core.CApp{Inl.go(p, c, IAll{}, f), Nil{}}
                case a <> t2:
                  Core.Tm.push(Inl.go(p, c, IAll{}, a), Inl.go(p, c, IKids{}, Core.CApp{f, t2}))
            case Core.CCtr{k, as}:
              match as:
                case Nil{}:
                  Core.CCtr{k, Nil{}}
                case a <> t2:
                  Core.Tm.push(Inl.go(p, c, IAll{}, a), Inl.go(p, c, IKids{}, Core.CCtr{k, t2}))
            case Core.CLam{pt, b}:
              Core.CLam{pt, Inl.go(p, c, IAll{}, b)}
            case Core.CLet{pt, v, b}:
              Core.CLet{pt, Inl.go(p, c, IAll{}, v), Inl.go(p, c, IAll{}, b)}
            case Core.CMat{scrs, cases}:
              match scrs:
                case a <> t2:
                  Core.Tm.push(Inl.go(p, c, IAll{}, a), Inl.go(p, c, IKids{}, Core.CMat{t2, cases}))
                case Nil{}:
                  match cases:
                    case Nil{}:
                      Core.CMat{Nil{}, Nil{}}
                    case cs <> t2:
                      Core.Tm.push.case(Inl.go(p, c, IAll{}, cs), Inl.go(p, c, IKids{}, Core.CMat{Nil{}, t2}))
            case Core.CCse{ps, b}:
              Core.CCse{ps, Inl.go(p, c, IAll{}, b)}
            case Core.CSuc{k, e}:
              Core.CSuc{k, Inl.go(p, c, IAll{}, e)}
            case Core.COp{op, a, b}:
              Core.COp{op, Inl.go(p, c, IAll{}, a), Inl.go(p, c, IAll{}, b)}
            case Core.CAnn{e, ty}:
              Core.CAnn{Inl.go(p, c, IAll{}, e), ty}
            case other:
              other
        case INode{}:
          match t:
            case Core.CCall{+f, +as}:
              +d = Pair.snd(Map<&2, Core.Def>, Core.Def, Map.get(Core.Def, Core.Def{"", Nil{}, Core.CBox{}, Core.CBox{}}, c, f))
              Bool.pick(Unit -> Core.Tm, Inl.hit(d, f, as),
                u => Inl.go(p, c, IPlan{Inl.pars(d), as, Inl.fsuf(p)}, Inl.go(p, c, IAll{}, Inl.ren(Inl.body(d), Inl.fsuf(p)))),
                u => Core.CCall{f, as})(Unit{})
            case Core.CApp{+f, +as}:
              match f:
                case Core.CLam{+pt, +b}:
                  match as:
                    case Nil{}:
                      Core.CApp{Core.CLam{pt, b}, Nil{}}
                    case +a <> +r:
                      Bool.pick(Unit -> Core.Tm, Inl.apart(Inl.pvars(pt, Nil{}), Inl.names(Core.CCtr{"", r}, 0, Nil{})),
                        u => Inl.go(p, c, INode{}, Core.CLet{pt, a, Inl.go(p, c, INode{}, Inl.app(b, r))}),
                        u => Core.CApp{Core.CLam{pt, b}, a <> r})(Unit{})
                case Core.CLet{+pt, +v, +b}:
                  Bool.pick(Unit -> Core.Tm, Inl.apart(Inl.pvars(pt, Nil{}), Inl.names(Core.CCtr{"", as}, 0, Nil{})),
                    u => Core.CLet{pt, v, Inl.go(p, c, INode{}, Inl.app(b, as))},
                    u => Core.CApp{Core.CLet{pt, v, b}, as})(Unit{})
                case other:
                  Core.CApp{other, as}
            case Core.CLet{+pt, +v, +b}:
              match pt:
                case Core.PtCtr{+k, +qs}:
                  match v:
                    case Core.CCtr{+k2, +as}:
                      Bool.pick(Unit -> Core.Tm, Bool.and(String.eq(k, k2), Nat.is_eq(Inl.pts.len(qs), Inl.tms.len(as))),
                        u => Core.CMat{as, [Core.CCse{qs, b}]},
                        u => Core.CLet{Core.PtCtr{k, qs}, Core.CCtr{k2, as}, b})(Unit{})
                    case other:
                      Core.CLet{Core.PtCtr{k, qs}, other, b}
                case other:
                  Core.CLet{other, v, b}
            case other:
              other

# The monad a def is part of: X for X.bind, X.pure, X.go and X.go.done
# ("" for any other def).
def Inl.cut(+n: String, +suf: String) -> String:
  Bool.pick(String, String.ends_with(n, suf), String.take(n, Nat.sub(String.length(n), String.length(suf))), "")

def Inl.monad(+n: String) -> String:
  +a = Inl.cut(n, ".bind")
  +b = Inl.cut(n, ".pure")
  +c = Inl.cut(n, ".go")
  +d = Inl.cut(n, ".go.done")
  a ++ b ++ c ++ d

# Whether d is inlined: a non-recursive def of a monad (not IO: its bind
# is the runtime's) that has both a bind and a pure.
def Inl.pick(+names: Set(), +name: String) -> Bool:
  +x = Inl.monad(name)
  Bool.pick(Unit -> Bool, Bool.or(String.is_empty(x), String.eq(x, "IO")), u => False{},
    u => Bool.and(Lo.bound(names, x ++ ".bind"), Lo.bound(names, x ++ ".pure")))(Unit{})

def Inl.add(+name: String, +d: Core.Def, +m: Map<&2, Core.Def>) -> Map<&2, Core.Def>:
  match d:
    case Core.Def{n, ps, +body, ret}:
      Bool.pick(Map<&2, Core.Def>, Str.has(Inl.names(body, 3, Nil{}), name), m, Map.set(&2, Core.Def, m, name, d))

def Inl.ctx(+g: G, +names: Set(), ds: List<&2, Decl>, +m: Map<&2, Core.Def>) -> Map<&2, Core.Def>:
  match ds:
    case Nil{}:
      m
    case d <> t:
      match d:
        case DDef{+name, +ps, body, ret}:
          Inl.ctx(g, names, t, Bool.pick(Unit -> Map<&2, Core.Def>, Inl.pick(names, name),
            u => Inl.add(name, Core.Def.erase(Lo.def(g, name, ps, body, ret)), m), u => m)(Unit{}))
        case other:
          Inl.ctx(g, names, t, m)

def Inl.names.defs(ds: List<&2, Decl>, s: Set()) -> Set():
  match ds:
    case Nil{}:
      s
    case d <> t:
      match d:
        case DDef{name, ps, body, ret}:
          Inl.names.defs(t, Set.add(s, name))
        case other:
          Inl.names.defs(t, s)

def Inl.any(xs: List<&2, String>, +c: Map<&2, Core.Def>) -> Bool:
  match xs:
    case Nil{}:
      False{}
    case +x <> t:
      Bool.pick(Unit -> Bool, Pair.snd(Map<&2, Core.Def>, Bool, Map.has(&2, Core.Def, c, x)), u => True{},
        u => Inl.any(t, c))(Unit{})

# d with its calls of c inlined (a def that makes none is left as it is).
def Inl.def(+c: Map<&2, Core.Def>, d: Core.Def) -> Core.Def:
  match d:
    case Core.Def{name, ps, +body, ret}:
      Core.Def{name, ps, Bool.pick(Unit -> Core.Tm, Inl.any(Inl.names(body, 3, Nil{}), c),
        u => Inl.go(Fuel.max(), c, IAll{}, body), u => body)(Unit{}), ret}

# The program through the core IR: each def lowered, erased, with monadic
# binds inlined, its redexes reduced (Core.Def.red, which REDPROOF.bend
# proves correct), its matches on known constructors resolved
# (Core.Def.known, which KNOWNPROOF.bend proves correct), its lets of
# variables no lookup reaches dropped (Core.Def.dead, which DEADPROOF.bend
# proves correct), and raised; a type-level def (a Type, Data, Quant or
# Kind) keeps its body, which the printers unfold.
def Lo.pass(+g: G, +c: Map<&2, Core.Def>, d: Decl) -> Decl:
  match d:
    case DDef{+name, +ps, +body, +ret}:
      Bool.pick(Unit -> Decl, G.erased_ty(Ty.head(ret)), u => DDef{name, ps, body, ret},
        u => Up.def(Core.Def.dead(Core.Def.known(Core.Def.red(Inl.def(c, Core.Def.erase(Lo.def(g, name, ps, body, ret))))))))(Unit{})
    case other:
      other

def Lo.passes(+g: G, +c: Map<&2, Core.Def>, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Lo.pass(g, c, d) <> Lo.passes(g, c, r)

def Lo.program(+ds: List<&2, Decl>) -> List<&2, Decl>:
  +g = G.new(ds)
  Lo.passes(g, Inl.ctx(g, Inl.names.defs(ds, Set.new()), ds, Map.new(&2, Core.Def)), ds)

def Gen.program.fin(+g: G, cids: String, r: String & St) -> COut:
  (entry, st) = r
  St{n, protos, code, refs, errs, memo, +effs} = st
  COut{cids ++ "#define BEND_NATIVE_MAP_BIT 1\n#ifdef BEND_RT_SPLIT\n#include \"bendrt_split.h\"\n#else\n#include \"bendrt.h\"\n#endif\n\n", Gen.dedup(List.reverse(&2, String, Gen.effs.files(effs)), Nil{}),
    Doc.flat(Doc.list([protos, DStr{"\n"}, code, DStr{Gen.gpu.tail(g, Gen.dedup(Gen.effs.tagged(effs, "%gpu\t"), Nil{}),
    Gen.dedup(Gen.effs.tagged(effs, "%clo\t"), Nil{}))},
    DStr{"\n" ++ entry}])), errs}

def Gen.entry.ty(+g: G, +ret: Expr, io: Bool) -> Gen(String):
  match io:
    case True{}:
      Gen.pure(String,
        "int main(int argc, char **argv) {" ++ Gen.ctors.call() ++ " return bend_run(argc, argv, F_main); }\n")
    case False{}:
      do Gen<String>:
        p : String <- Gen.printer(g, ret)
        return "int main(int argc, char **argv) {" ++ Gen.ctors.call() ++
          " return bend_run_value(argc, argv, F_main, " ++ p ++ "); }\n"

def Gen.entry.ret(+g: G, +ret: Expr) -> Gen(String):
  Gen.entry.ty(g, ret, Str.eq(Ty.head(ret), "IO"))

# A main that returns IO runs it; any other main is evaluated and its value
# printed in Bend syntax, driven by main's return type.
def Gen.entry(+g: G, d: Decl) -> Gen(String):
  match d:
    case DDef{n, ps, b, ret}:
      Gen.entry.ret(g, Ty.norm(g, ret, 16n))
    case other:
      do Gen<String>:
        Gen.error("no main definition")
        return ""

def Gen.program.m(+g: G) -> Gen(String):
  do Gen<String>:
    Gen.all(g, ["main"], Set.new())
    Gen.entry(g, G.body(g, "main"))

def Gen.program(+ds0: List<&2, Decl>, free: Bool, par: Bool) -> COut:
  +ds = Par.auto(par, Lo.program(Pick.decls(ds0)))
  +g = Dps.build(G.new(ds), ds, free)
  Gen.program.fin(g, Gen.cids(g, ds, 0),
    Gen.program.m(g)(St{0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}}))

# C for a program: matches free what they open unless BEND_NO_FREE is set
# (bendc builds itself so: a compiler's heap is mostly shared, short-lived
# data, which tracing handles for less).
def Main.emit.c(+ds: List<&2, Decl>) -> IO(Unit):
  do IO<Unit>:
    r : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_NO_FREE")
    r2 : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_NO_FREE")
    ap : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_AUTO_PAR")
    Main.emit(ds, Gen.program(ds, Main.free(r), Main.auto_par(ap, Main.free(r2))))

def J.entry.ty(+j: JG, +ret: Expr, io: Bool) -> Gen(String):
  match io:
    case True{}:
      Gen.pure(String, "bend_run(F_main);\n")
    case False{}:
      do Gen<String>:
        p : String <- J.printer(j, ret)
        return "bend_run_value(F_main, " ++ p ++ ");\n"

def J.entry.ret(+j: JG, +ret: Expr) -> Gen(String):
  J.entry.ty(j, ret, Str.eq(Ty.head(ret), "IO"))

def J.entry(+j: JG, d: Decl) -> Gen(String):
  match d:
    case DDef{n, ps, b, ret}:
      J.entry.ret(j, Ty.norm(JG.g(j), ret, 16n))
    case other:
      do Gen<String>:
        Gen.error("no main definition")
        return ""

def J.program.m(+j: JG) -> Gen(String):
  do Gen<String>:
    J.all(j, ["main"], Set.new())
    J.entry(j, G.body(JG.g(j), "main"))

def J.program.go(+ds: List<&2, Decl>) -> COut:
  J.program.fin(J.program.m(JG{G.new(ds), J.info(ds, MTip{})})(St{0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}}))

def J.program(ds: List<&2, Decl>) -> COut:
  J.program.go(Pick.decls(ds))

def Main.emit.to.go(js: Bool, +ds: List<&2, Decl>) -> IO(Unit):
  match js:
    case True{}:
      Main.emit.js(ds, J.program(ds))
    case False{}:
      Main.emit.c(ds)

def Main.emit.to.sh(js: Bool, +ds: List<&2, Decl>) -> IO(Unit):
  Main.emit.to.go(js, LM.decls(ds, ds))

def Main.emit.to(js: Bool, ds: List<&2, Decl>) -> IO(Unit):
  Main.emit.to.sh(js, ds)

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

def Main.build(js: Bool, +base_path: String, user_path: String) -> IO(Unit):
  do IO<Unit>:
    base : String <- IO.read_file(base_path)
    user : List<&2, Decl> <- Main.load(64n, user_path)
    Main.compile(js, Main.resolve(Mod.dir(base_path), Main.parse(base)), Done{user})

def Main.checked.go(js: Bool, +base_path: String, user_path: String, +bk: Chk.Book, norm: Bool) -> IO(Unit):
  match norm:
    case True{}:
      Main.emit_value(js, Chk.show_main(bk))
    case False{}:
      Main.build(js, base_path, user_path)

# After checking, compile. A value main that may hold a function is
# printed as the checker normalizes it.
def Main.checked(js: Bool, +base_path: String, user_path: String, r: Chk.Book & Nat) -> IO(Unit):
  (b, n0) = r
  +bk = b
  Main.checked.go(js, base_path, user_path, bk, Main.normalized(bk))

def Main.run2(code: Nat, +a: String, +b: String) -> IO(Unit):
  match code:
    case 0n:
      do IO<Unit>:
        r : Chk.Book & Nat <- Main.check(a, b)
        Main.checked(False{}, a, b, r)
    case 1n:
      do IO<Unit>:
        src : String <- IO.read_file(b)
        IO.print(Toks.show(Lex.all(src)))
    case 2n:
      do IO<Unit>:
        src : String <- IO.read_file(b)
        Main.ast(Main.parse(src))
    case other:
      Main.usage()

def Main.run3(code: Nat, +base_path: String, +user_path: String) -> IO(Unit):
  match code:
    case 3n:
      do IO<Unit>:
        r : Chk.Book & Nat <- Main.check(base_path, user_path)
        Main.check_only.fin(r)
    case 4n:
      Main.build(False{}, base_path, user_path)
    case 5n:
      do IO<Unit>:
        r : Chk.Book & Nat <- Main.check(base_path, user_path)
        Main.checked(True{}, base_path, user_path, r)
    case other:
      Main.usage()

# Main.compile to C only (reaching no JS backend).
def Main.boot.compile(base: Result<&2, &2, String, List<&2, Decl>>, user: Result<&2, &2, String, List<&2, Decl>>) ->
  IO(Unit):
  match base user:
    case Fail{e} u:
      IO.die(Unit, 1, "bendc: parse error in base: " ++ e)
    case Done{b} Fail{e}:
      IO.die(Unit, 1, "bendc: parse error: " ++ e)
    case Done{b} Done{u}:
      Main.emit.c(List.append(&2, Decl, b, u))

# The driver of boot.bend: bendc --no-check, without the checker.
def Main.boot(args: List<&2, String>) -> IO(Unit):
  match args:
    case a <> +b <> c <> Nil{}:
      do IO<Unit>:
        base : String <- IO.read_file(b)
        user : List<&2, Decl> <- Main.load(64n, c)
        Main.boot.compile(Main.resolve(Mod.dir(b), Main.parse(base)), Done{user})
    case other:
      IO.die(Unit, 1, "usage: bendc0 --no-check <base.bend> <input.bend>")

# bendc -o out base.bend input.bend: the C, compiled into out.
def Main.run4(code: Nat, +out: String, +base_path: String, +user_path: String) -> IO(Unit):
  match code:
    case 6n:
      do IO<Unit>:
        u : Unit <- IO.try(Unit, Cc.begin())
        r : Chk.Book & Nat <- Main.check(base_path, user_path)
        Main.checked(False{}, base_path, user_path, r)
        IO.try(Unit, Cc.end(out))
    case other:
      Main.usage()

def Main.run(args: List<&2, String>) -> IO(Unit):
  match args:
    case +a <> +b <> Nil{}:
      Main.run2(Main.code(a), a, b)
    case +a <> +b <> +c <> Nil{}:
      Main.run3(Main.code(a), b, c)
    case +a <> +b <> +c <> +d <> Nil{}:
      Main.run4(Main.code(a), b, c, d)
    case other:
      Main.usage()

def main() -> IO(Unit):
  do IO<Unit>:
    args : List<String> <- IO.args()
    Main.run(Main.args(IO.list2(args)))
