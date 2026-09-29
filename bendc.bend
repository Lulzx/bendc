# bendc: a Bend compiler written in Bend.
# Compiles a Bend program (plus the parts of Base it uses) to C.
# Usage: bendc <base.bend> <input.bend>  (C goes to stdout)

import Base
import ./check.bend as Chk
import ./core.bend as Core
import ./rt/rtjs.bend as RtJs
import ./rt/rtchan.bend as RtChan
import ./asm.bend as As

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

type Stmt is Data:
  SLet{pat: Core.Pat, val: Core.Expr}
  SBind{name: String, val: Core.Expr}
  SRet{e: Core.Expr}
  SExp{e: Core.Expr}
  SSkip{}

type Field is Data:
  Field{name: String, ty: Core.Expr}

type Ctor is Data:
  Ctor{name: String, fields: List<&2, Field>}

type Decl is Data:
  DDef{name: String, params: List<&2, Core.Param>, body: Core.Expr, ret: Core.Expr}
  DEff{name: String, params: List<&2, Core.Param>, imports: List<&2, String>}
  DLaw{name: String, params: List<&2, Core.Param>, ret: Core.Expr}
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
def P.head(e: Core.Expr) -> String:
  match e:
    case Core.EVar{n}:
      n
    case Core.ECall{Core.EVar{n}, args}:
      n
    case Core.ETy{n, targs}:
      n
    case other:
      ""

def P.tuple(xs: List<&2, Core.Expr>) -> Core.Expr:
  match xs:
    case Nil{}:
      Core.ECtor{"Unit", Nil{}}
    case h <> Nil{}:
      h
    case h <> t:
      Core.ECtor{"Tuple", [h, P.tuple(t)]}

def P.ptuple(xs: List<&2, Core.Pat>) -> Core.Pat:
  match xs:
    case Nil{}:
      Core.PCtor{"Unit", Nil{}}
    case h <> Nil{}:
      h
    case h <> t:
      Core.PCtor{"Tuple", [h, P.ptuple(t)]}

def P.elist(xs: List<&2, Core.Expr>) -> Core.Expr:
  match xs:
    case Nil{}:
      Core.ECtor{"Nil", Nil{}}
    case h <> t:
      Core.ECtor{"Con", [h, P.elist(t)]}

def P.plist(xs: List<&2, Core.Pat>) -> Core.Pat:
  match xs:
    case Nil{}:
      Core.PCtor{"Nil", Nil{}}
    case h <> t:
      Core.PCtor{"Con", [h, P.plist(t)]}

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

def P.mk_bin.go(op: String, a: Core.Expr, b: Core.Expr, k: Nat) -> Core.Expr:
  match k:
    case 0n:
      Core.ETy{"->", [a, b]}
    case 1n:
      Core.ETy{"|", [a, b]}
    case 2n:
      Core.ETy{"&", [a, b]}
    case 3n:
      Core.ETy{"#q", Nil{}}
    case 4n:
      Core.ECall{Core.EVar{"Bool.or"}, [a, b]}
    case 5n:
      Core.ECall{Core.EVar{"Bool.and"}, [a, b]}
    case 6n:
      Core.ECtor{"Con", [a, b]}
    case 7n:
      Core.ECall{Core.EVar{"String.append"}, [a, b]}
    case 8n+p:
      Core.EOp{op, a, b}

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

def P.arr.size.lit(t: Tok) -> Parser(Core.Expr):
  match t:
    case Tok{KNat{n}, sp, ln}:
      do Parser<Core.Expr>:
        P.skip()
        return Core.ENat{P.log2(n)}
    case other:
      do Parser<Core.Expr>:
        P.err("expected an array size")
        return Core.ENat{0}

# Negation of a numeric literal.
def P.neg(e: Core.Expr) -> Core.Expr:
  match e:
    case Core.ENum{n}:
      Core.ENum{(0 - n : U32)}
    case Core.EFlt{s}:
      Core.EFlt{"-" ++ s}
    case other:
      other

# &x: A -> B as the Sigma it abbreviates (a printer reads its parts).
def P.dep.sigma(+x: String, ty: Core.Expr) -> Core.Expr:
  match ty:
    case Core.ETy{"->", a <> b <> Nil{}}:
      Core.ETy{"Sigma", [Core.ETy{"#q", Nil{}}, Core.ETy{"#q", Nil{}}, a, Core.ELam{Core.PVar{x}, b}]}
    case other:
      Core.ETy{"", Nil{}}

# The erased binders leading a '@-x: A -> B', one "@-" each, ride as a
# marker the parameter's head reads (the JS seam drops those layers).
def P.dep.mark(ty: Core.Expr) -> String:
  match ty:
    case Core.ETy{"", Core.ETy{+h, Nil{}} <> Nil{}}:
      h
    case other:
      ""

def P.dep.arrow(ty: Core.Expr) -> Core.Expr:
  match ty:
    case Core.ETy{"->", a <> b <> Nil{}}:
      Core.ETy{"", [Core.ETy{"@-" ++ P.dep.mark(b), Nil{}}]}
    case other:
      Core.ETy{"", Nil{}}

def P.dep.erased(ty: Core.Expr, e: Bool) -> Core.Expr:
  match e:
    case True{}:
      P.dep.arrow(ty)
    case False{}:
      Core.ETy{"", Nil{}}

def P.dep.fin(+x: String, ty: Core.Expr, amp: Bool, e: Bool) -> Core.Expr:
  match amp:
    case True{}:
      P.dep.sigma(x, ty)
    case False{}:
      P.dep.erased(ty, e)

def P.phead(ty: Core.Expr) -> String:
  match ty:
    case Core.ETy{"", Core.ETy{+h, Nil{}} <> Nil{}}:
      h
    case other:
      P.head(other)

def P.mk_bin(+op: String, a: Core.Expr, b: Core.Expr) -> Core.Expr:
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
def P.pstr(s: String) -> Core.Pat:
  match s:
    case SNil{}:
      Core.PCtor{"SNil", Nil{}}
    case SCon{Chr{c}, t}:
      Core.PCtor{"SCon", [Core.PCtor{"Chr", [Core.PNum{c}]}, P.pstr(t)]}

# The pattern parsers, which call each other, as one def (P.pat.go) that a
# selector switches between: each constructor is one parser, with its
# arguments.
type PsP is Data:
  PsPat{}
  PsPatCons{p: Core.Pat, cons: Bool}
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
      Core.Pat
    case PsPatCons{p, cons}:
      Core.Pat
    case PsPat1{}:
      Core.Pat
    case PsPat1K{t}:
      Core.Pat
    case PsPatSym{n}:
      Core.Pat
    case PsPatId{name, ctor}:
      Core.Pat
    case PsPats{close}:
      List<&2, Core.Pat>
    case PsPatsGo{close, t, stuck}:
      List<&2, Core.Pat>
    case PsPatsClose{close, at}:
      List<&2, Core.Pat>
    case PsPatsItem{close}:
      List<&2, Core.Pat>
    case PsPatsMore{close, more}:
      List<&2, Core.Pat>

def P.pat.none(k: PsP) -> Parser(PsP.ty(k)):
  match k:
    case PsPat{}:
      P.fuel(Core.Pat, Core.PVar{"_"})
    case PsPatCons{p, cons}:
      P.fuel(Core.Pat, Core.PVar{"_"})
    case PsPat1{}:
      P.fuel(Core.Pat, Core.PVar{"_"})
    case PsPat1K{t}:
      P.fuel(Core.Pat, Core.PVar{"_"})
    case PsPatSym{n}:
      P.fuel(Core.Pat, Core.PVar{"_"})
    case PsPatId{name, ctor}:
      P.fuel(Core.Pat, Core.PVar{"_"})
    case PsPats{close}:
      P.fuel(List<&2, Core.Pat>, Nil{})
    case PsPatsGo{close, t, stuck}:
      P.fuel(List<&2, Core.Pat>, Nil{})
    case PsPatsClose{close, at}:
      P.fuel(List<&2, Core.Pat>, Nil{})
    case PsPatsItem{close}:
      P.fuel(List<&2, Core.Pat>, Nil{})
    case PsPatsMore{close, more}:
      P.fuel(List<&2, Core.Pat>, Nil{})

def P.pat.go(+fuel: Nat, k: PsP) -> Parser(PsP.ty(k)):
  match fuel:
    case 0n:
      P.pat.none(k)
    case 1n+fl:
      match k:
        case PsPat{}:
          do Parser<Core.Pat>:
            p : Core.Pat <- P.pat.go(fl, PsPat1{})
            t : Tok <- P.peek()
            P.pat.go(fl, PsPatCons{p, P.tok_is(t, "<>")})
        case PsPatCons{p, cons}:
          match cons:
            case True{}:
              do Parser<Core.Pat>:
                P.skip()
                rest : Core.Pat <- P.pat.go(fl, PsPat{})
                return Core.PCtor{"Con", [p, rest]}
            case False{}:
              Parser.pure(Core.Pat, p)
        case PsPat1{}:
          do Parser<Core.Pat>:
            t : Tok <- P.peek()
            P.pat.go(fl, PsPat1K{P.tok_kind(t)})
        case PsPat1K{k1}:
          match k1:
            case KId{name}:
              do Parser<Core.Pat>:
                P.skip()
                +t : Tok <- P.peek()
                P.pat.go(fl, PsPatId{name, Bool.and(P.tok_is(t, "{"), Bool.not(P.tok_sp(t)))})
            case KNat{n}:
              do Parser<Core.Pat>:
                P.skip()
                return Core.PNat{n}
            case KNatPlus{n}:
              do Parser<Core.Pat>:
                P.skip()
                p : Core.Pat <- P.pat.go(fl, PsPat1{})
                return Core.PSucc{n, p}
            case KNum{n}:
              do Parser<Core.Pat>:
                P.skip()
                return Core.PNum{n}
            case KFlt{s}:
              do Parser<Core.Pat>:
                P.skip()
                return Core.PFlt{s}
            case KChr{n}:
              do Parser<Core.Pat>:
                P.skip()
                return Core.PCtor{"Chr", [Core.PNum{n}]}
            case KStr{s}:
              do Parser<Core.Pat>:
                P.skip()
                return P.pstr(s)
            case KSym{s}:
              P.pat.go(fl, PsPatSym{P.which(s, ["+", "-", "(", "["])})
            case other:
              do Parser<Core.Pat>:
                P.err("expected a pattern")
                return Core.PVar{"_"}
        case PsPatSym{n}:
          match n:
            case 0n:
              do Parser<Core.Pat>:
                P.skip()
                P.pat.go(fl, PsPat1{})
            case 1n:
              do Parser<Core.Pat>:
                P.skip()
                P.pat.go(fl, PsPat1{})
            case 2n:
              do Parser<Core.Pat>:
                P.skip()
                ps : List<&2, Core.Pat> <- P.pat.go(fl, PsPats{")"})
                return P.ptuple(ps)
            case 3n:
              do Parser<Core.Pat>:
                P.skip()
                ps : List<&2, Core.Pat> <- P.pat.go(fl, PsPats{"]"})
                return P.plist(ps)
            case 4n+p:
              do Parser<Core.Pat>:
                P.err("expected a pattern")
                return Core.PVar{"_"}
        case PsPatId{+name, ctor}:
          match ctor:
            case True{}:
              do Parser<Core.Pat>:
                P.skip()
                args : List<&2, Core.Pat> <- P.pat.go(fl, PsPats{"}"})
                return Core.PCtor{name, args}
            case False{}:
              Parser.pure(Core.Pat, Core.PVar{name})
        # Comma-separated patterns up to (and including) a closing symbol.
        case PsPats{+close}:
          do Parser<List<&2, Core.Pat>>:
            +t : Tok <- P.peek()
            P.pat.go(fl, PsPatsGo{close, t, P.stuck(P.tok_kind(t))})
        case PsPatsGo{+close, +t, stuck}:
          match stuck:
            case True{}:
              Parser.pure(List<&2, Core.Pat>, Nil{})
            case False{}:
              P.pat.go(fl, PsPatsClose{close, P.tok_is(t, close)})
        case PsPatsClose{+close, at}:
          match at:
            case True{}:
              do Parser<List<&2, Core.Pat>>:
                P.skip()
                return Nil{}
            case False{}:
              P.pat.go(fl, PsPatsItem{close})
        case PsPatsItem{+close}:
          do Parser<List<&2, Core.Pat>>:
            p : Core.Pat <- P.pat.go(fl, PsPat{})
            more : Bool <- P.eat(",")
            rest : List<&2, Core.Pat> <- P.pat.go(fl, PsPatsMore{close, more})
            return p <> rest
        case PsPatsMore{+close, more}:
          match more:
            case True{}:
              P.pat.go(fl, PsPats{close})
            case False{}:
              do Parser<List<&2, Core.Pat>>:
                P.expect(close)
                return Nil{}

def P.pat() -> Parser(Core.Pat):
  P.pat.go(Fuel.max(), PsPat{})

# Space-separated patterns up to (not including) one of the stop symbols.
def P.pat_seq.go(fuel: Nat, +stops: List<&2, String>) -> Parser(List<&2, Core.Pat>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Core.Pat>, Nil{})
    case 1n+fl:
      do Parser<List<&2, Core.Pat>>:
        +t : Tok <- P.peek()
        Bool.pick(Unit -> Parser(List<&2, Core.Pat>), P.pat_seq.stop(stops, t),
          u => Parser.pure(List<&2, Core.Pat>, Nil{}),
          u => do Parser<List<&2, Core.Pat>>:
            p : Core.Pat <- P.pat()
            _c : Bool <- P.eat(",")
            rest : List<&2, Core.Pat> <- P.pat_seq.go(fl, stops)
            return p <> rest)(Unit{})

def P.pat_seq(+stops: List<&2, String>) -> Parser(List<&2, Core.Pat>):
  P.pat_seq.go(Fuel.max(), stops)

# Statements
# ==========

def P.lets(ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>) -> List<&2, Stmt>:
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
def Fold.plain(ss: List<&2, Stmt>) -> Core.Expr:
  match ss:
    case Nil{}:
      Core.EErr{"empty block"}
    case SLet{p, v} <> Nil{}:
      v
    case SBind{x, v} <> Nil{}:
      v
    case SRet{e} <> Nil{}:
      e
    case SExp{e} <> Nil{}:
      e
    case SSkip{} <> Nil{}:
      Core.ETy{"", Nil{}}
    case SLet{p, v} <> t:
      Core.ELet{p, v, Fold.plain(t)}
    case SBind{x, v} <> t:
      Core.ELet{Core.PVar{x}, v, Fold.plain(t)}
    case SRet{e} <> t:
      e
    case SExp{e} <> t:
      Core.ELet{Core.PVar{"_"}, e, Fold.plain(t)}
    case SSkip{} <> t:
      Fold.plain(t)

def Fold.app(+m: String, +f: String, +xs: List<&2, Core.Expr>, ys: List<&2, Core.Expr>) ->
  Core.Expr:
  Core.ECall{Core.EVar{m ++ "." ++ f}, List.append(&2, Core.Expr, xs, ys)}

def Fold.do(+m: String, +xs: List<&2, Core.Expr>, +r: Core.Expr, ss: List<&2, Stmt>) ->
  Core.Expr:
  match ss:
    case Nil{}:
      Core.EErr{"empty do block"}
    case SLet{p, v} <> Nil{}:
      v
    case SBind{x, v} <> Nil{}:
      v
    case SRet{e} <> Nil{}:
      Fold.app(m, "pure", xs, [r, e])
    case SExp{e} <> Nil{}:
      e
    case SSkip{} <> Nil{}:
      Core.ETy{"", Nil{}}
    case SLet{p, v} <> t:
      Core.ELet{p, v, Fold.do(m, xs, r, t)}
    case SBind{x, v} <> t:
      Fold.app(m, "bind", xs, [Core.ETy{"", Nil{}}, r, v, Core.ELam{Core.PVar{x}, Fold.do(m, xs, r, t)}])
    case SRet{e} <> t:
      Fold.app(m, "pure", xs, [r, e])
    case SExp{e} <> t:
      Fold.app(m, "bind", xs, [Core.ETy{"", Nil{}}, r, e, Core.ELam{Core.PVar{"_"}, Fold.do(m, xs, r, t)}])
    case SSkip{} <> t:
      Fold.do(m, xs, r, t)

def P.init(xs: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case h <> Nil{}:
      Nil{}
    case h <> t:
      h <> P.init(t)

def P.last(xs: List<&2, Core.Expr>) -> Core.Expr:
  match xs:
    case Nil{}:
      Core.ETy{"", Nil{}}
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
def P.lets.par(+ps: List<&2, Core.Pat>, +vs: List<&2, Core.Expr>) -> List<&2, Stmt>:
  Bool.pick(List<&2, Stmt>, Nat.is_gt(List.length(&2, Core.Pat, ps), 1n),
    [SLet{Core.PCtor{"%par", ps}, Core.ECtor{"%par", vs}}], P.lets(ps, vs))

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
  PsArr{v: Core.Expr}
  PsBraceTail{e: Core.Expr, k: Nat}
  PsDep{amp: Bool}
  PsAmpGo{t: Tok}
  PsBraceBody{}
  PsBraceGo{refl: Bool}
  PsBrace{}
  PsBinLoopGo{min: U32, lhs: Core.Expr, o: String, p: U32, r: Bool, ok: Bool}
  PsBinLoopOp{min: U32, lhs: Core.Expr, op: OpInfo}
  PsBinLoop{min: U32, lhs: Core.Expr}
  PsBin{min: U32}
  PsIlet{}
  PsIexprGo{lets: Bool}
  PsIexpr{}
  PsParenTail{e: Core.Expr, k: Nat}
  PsParenBody{}
  PsParenGo{unit: Bool}
  PsParen{}
  PsBrackTail{e: Core.Expr, arr: Bool}
  PsBrackBody{}
  PsBrackGo{empty: Bool}
  PsBrack{}
  PsLmatGo{k: Nat}
  PsLmat{}
  PsRwEq{first: Core.Expr, at: Bool}
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
  PsPostfixSet{e: Core.Expr, i: Core.Expr, set: Bool}
  PsPostfixK{e: Core.Expr, k: Nat}
  PsPostfixT{e: Core.Expr, t: Tok}
  PsPostfix{e: Core.Expr}
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
  PsParenItem{e: Core.Expr, k: Nat}
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
      Core.Expr
    case PsL{s}:
      List<&2, Core.Expr>
    case PsS{s}:
      List<&2, Stmt>
    case PsU{s}:
      Unit

def P.none(k: PsSel) -> Parser(PsSel.ty(k)):
  match k:
    case PsE{s}:
      P.fuel(Core.Expr, Core.EErr{""})
    case PsL{s}:
      P.fuel(List<&2, Core.Expr>, Nil{})
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
              do Parser<Core.Expr>:
                P.skip()
                ty : Core.Expr <- P.go(fl, PsE{PsTerm{}})
                t : Tok <- P.peek()
                P.skip()
                t2 : Tok <- P.peek()
                d : Core.Expr <- P.go(fl, PsE{PsArrSize{P.tok_is(t, "^"), t2}})
                P.expect("]")
                return Core.ECall{Core.EVar{"Array.new"}, [Core.ETy{"", Nil{}}, d, Core.EAnn{v, P.head(ty)}]}
            # '{' ... '}': reflexivity, equality type, or annotation.
            case PsBraceTail{e, k}:
              match k:
                case 0n:
                  do Parser<Core.Expr>:
                    P.skip()
                    b : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(":")
                    ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("}")
                    return Core.ETy{"==", Nil{}}
                case 1n:
                  do Parser<Core.Expr>:
                    P.skip()
                    b : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(":")
                    ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("}")
                    return Core.ETy{"", Nil{}}
                case 2n:
                  do Parser<Core.Expr>:
                    P.skip()
                    ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("}")
                    return Core.EAnn{e, P.head(ty)}
                case 3n+p:
                  do Parser<Core.Expr>:
                    P.expect("}")
                    return e
            # '@x: A -> B' and '&x: A -> B' (dependent types), '&1' (quantities).
            case PsDep{amp}:
              do Parser<Core.Expr>:
                e1 : Bool <- P.eat("-")
                e2 : Bool <- P.eat("+")
                x : String <- P.ident()
                P.expect(":")
                ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                return P.dep.fin(x, ty, amp, e1)
            case PsAmpGo{t}:
              match t:
                case Tok{KNum{n}, sp, ln}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.ETy{"#q", Nil{}}
                case other:
                  P.go(fl, PsE{PsDep{True{}}})
            case PsBraceBody{}:
              do Parser<Core.Expr>:
                e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBraceTail{e, P.tok_which(t, ["==", "!=", ":"])}})
            case PsBraceGo{refl}:
              match refl:
                case True{}:
                  do Parser<Core.Expr>:
                    P.skip()
                    P.expect("}")
                    return Core.ETy{"", Nil{}}
                case False{}:
                  P.go(fl, PsE{PsBraceBody{}})
            case PsBrace{}:
              do Parser<Core.Expr>:
                P.skip()
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBraceGo{P.tok_is(t, "==")}})
            case PsBinLoopGo{+min, lhs, o, +p, r, ok}:
              match ok:
                case False{}:
                  Parser.pure(Core.Expr, lhs)
                case True{}:
                  do Parser<Core.Expr>:
                    P.skip()
                    rhs : Core.Expr <- P.go(fl, PsE{PsBin{Bool.pick(U32, r, p, U32.inc(p))}})
                    P.go(fl, PsE{PsBinLoop{min, P.mk_bin(o, lhs, rhs)}})
            case PsBinLoopOp{+min, lhs, op}:
              OpInfo{o, +p, r} = op
              P.go(fl, PsE{PsBinLoopGo{min, lhs, o, p, r, Bool.and(U32.is_ne(p, 0), U32.is_ge(p, min))}})
            case PsBinLoop{+min, lhs}:
              do Parser<Core.Expr>:
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBinLoopOp{min, lhs, P.tok_op(t)}})
            case PsBin{min}:
              do Parser<Core.Expr>:
                lhs : Core.Expr <- P.go(fl, PsE{PsTerm{}})
                P.go(fl, PsE{PsBinLoop{min, lhs}})
            case PsIlet{}:
              do Parser<Core.Expr>:
                e1 : Bool <- P.eat("-")
                e2 : Bool <- P.eat("+")
                p : Core.Pat <- P.pat()
                P.go(fl, PsU{PsSkipAnn{}})
                P.expect("=")
                v : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                P.expect(";")
                b : Core.Expr <- P.go(fl, PsE{PsIexpr{}})
                return Core.ELet{p, v, b}
            case PsIexprGo{lets}:
              match lets:
                case True{}:
                  P.go(fl, PsE{PsIlet{}})
                case False{}:
                  P.go(fl, PsE{PsExpr{}})
            # An expression that may open with lets: x = a; y : T = b; e.
            case PsIexpr{}:
              do Parser<Core.Expr>:
                lets : Bool <- ts => P.lscan.ret(ts)
                P.go(fl, PsE{PsIexprGo{lets}})
            case PsParenTail{e, k}:
              match k:
                case 0n:
                  do Parser<Core.Expr>:
                    P.skip()
                    rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsParenItems{}})
                    return P.tuple(e <> rest)
                case 1n:
                  do Parser<Core.Expr>:
                    P.skip()
                    ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(")")
                    return Core.EAnn{e, P.head(ty)}
                case 2n+p:
                  do Parser<Core.Expr>:
                    P.expect(")")
                    return e
            case PsParenBody{}:
              do Parser<Core.Expr>:
                e : Core.Expr <- P.go(fl, PsE{PsIexpr{}})
                t : Tok <- P.peek()
                P.go(fl, PsE{PsParenTail{e, P.tok_which(t, [",", ":"])}})
            case PsParenGo{unit}:
              match unit:
                case True{}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.ECtor{"Unit", Nil{}}
                case False{}:
                  P.go(fl, PsE{PsParenBody{}})
            # '(' ... ')': unit, tuple, annotation or parens.
            case PsParen{}:
              do Parser<Core.Expr>:
                P.skip()
                t : Tok <- P.peek()
                P.go(fl, PsE{PsParenGo{P.tok_is(t, ")")}})
            case PsBrackTail{e, arr}:
              match arr:
                case True{}:
                  P.go(fl, PsE{PsArr{e}})
                case False{}:
                  do Parser<Core.Expr>:
                    _e : Bool <- P.eat(",")
                    rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsList{"]"}})
                    return P.elist(e <> rest)
            case PsBrackBody{}:
              do Parser<Core.Expr>:
                e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBrackTail{e, P.tok_is(t, ":")}})
            case PsBrackGo{empty}:
              match empty:
                case True{}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.ECtor{"Nil", Nil{}}
                case False{}:
                  P.go(fl, PsE{PsBrackBody{}})
            case PsBrack{}:
              do Parser<Core.Expr>:
                P.skip()
                t : Tok <- P.peek()
                P.go(fl, PsE{PsBrackGo{P.tok_is(t, "]")}})
            case PsLmatGo{k}:
              match k:
                case 0n:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.ECtor{"%efq", Nil{}}
                case 1n:
                  do Parser<Core.Expr>:
                    +c : String <- P.ident()
                    P.expect(":")
                    h : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    _s : Bool <- P.eat(";")
                    m : Core.Expr <- P.go(fl, PsE{PsLmat{}})
                    return Core.ECtor{"%mat", [Core.ECtor{c, Nil{}}, h, m]}
                case 2n+p:
                  do Parser<Core.Expr>:
                    e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    _s : Bool <- P.eat(";")
                    P.expect("}")
                    return e
            # The arms of \{K: h; ...; m} after its {: K's fields go to h, any other
            # value to m; \{} (no m) matches nothing. LM.expr unfolds it once the
            # constructors' arities are known.
            case PsLmat{}:
              do Parser<Core.Expr>:
                P.nls()
                k : Nat <- ts => P.lmat.peek(ts)
                P.go(fl, PsE{PsLmatGo{k}})
            # A rewrite %e@E : P; f (or %E : P; f) is its tail f: the equation is
            # erased evidence. On its own line the tail is the next statement.
            case PsRwEq{first, at}:
              match at:
                case True{}:
                  do Parser<Core.Expr>:
                    P.skip()
                    P.go(fl, PsE{PsTerm{}})
                case False{}:
                  Parser.pure(Core.Expr, first)
            case PsRwTail{semi}:
              match semi:
                case True{}:
                  do Parser<Core.Expr>:
                    P.skip()
                    P.go(fl, PsE{PsIexpr{}})
                case False{}:
                  Parser.pure(Core.Expr, Core.ECtor{"Unit", Nil{}})
            case PsRw{}:
              do Parser<Core.Expr>:
                P.skip()
                first : Core.Expr <- P.go(fl, PsE{PsTerm{}})
                t : Tok <- P.peek()
                e : Core.Expr <- P.go(fl, PsE{PsRwEq{first, P.tok_is(t, "@")}})
                P.expect(":")
                ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
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
                  do Parser<Core.Expr>:
                    P.skip()
                    P.go(fl, PsE{PsTerm{}})
                case 4n:
                  do Parser<Core.Expr>:
                    P.skip()
                    P.go(fl, PsE{PsTerm{}})
                case 5n:
                  do Parser<Core.Expr>:
                    P.skip()
                    e : Core.Expr <- P.go(fl, PsE{PsTerm{}})
                    return P.neg(e)
                case 6n:
                  do Parser<Core.Expr>:
                    P.skip()
                    P.go(fl, PsE{PsDep{False{}}})
                case 7n:
                  do Parser<Core.Expr>:
                    P.skip()
                    t : Tok <- P.peek()
                    P.go(fl, PsE{PsAmpGo{t}})
                case 8n:
                  do Parser<Core.Expr>:
                    P.skip()
                    x : String <- P.ident()
                    return Core.ETy{"", Nil{}}
                case 9n:
                  do Parser<Core.Expr>:
                    P.skip()
                    P.expect("{")
                    P.go(fl, PsE{PsLmat{}})
                case 10n:
                  P.go(fl, PsE{PsRw{}})
                case 11n+p:
                  do Parser<Core.Expr>:
                    P.err("unexpected symbol")
                    return Core.EErr{""}
            case PsAfterIdK{+name, k}:
              match k:
                case 0n:
                  do Parser<Core.Expr>:
                    P.skip()
                    args : List<&2, Core.Expr> <- P.go(fl, PsL{PsList{"}"}})
                    return Core.ECtor{name, args}
                case 1n:
                  do Parser<Core.Expr>:
                    P.skip()
                    args : List<&2, Core.Expr> <- P.go(fl, PsL{PsTyargs{}})
                    return Core.ETy{name, args}
                case 2n+p:
                  Parser.pure(Core.Expr, Core.EVar{name})
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
                  do Parser<Core.Expr>:
                    P.skip()
                    t : Tok <- P.peek()
                    body : Core.Expr <- P.go(fl, PsE{PsLamBody{P.is_in(t)}})
                    return Core.ELam{Core.PVar{name}, body}
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
                  do Parser<Core.Expr>:
                    P.skip()
                    t : Tok <- P.peek()
                    P.go(fl, PsE{PsAfterId{name, t}})
            case PsPrimaryK{k}:
              match k:
                case KId{+name}:
                  P.go(fl, PsE{PsPrimaryId{name, Str.eq(name, "do")}})
                case KNum{n}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.ENum{n}
                case KNat{n}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.ENat{n}
                case KNatPlus{n}:
                  do Parser<Core.Expr>:
                    P.skip()
                    e : Core.Expr <- P.go(fl, PsE{PsTerm{}})
                    return Core.ESucc{n, e}
                case KFlt{s}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.EFlt{s}
                case KChr{n}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.ECtor{"Chr", [Core.ENum{n}]}
                case KStr{s}:
                  do Parser<Core.Expr>:
                    P.skip()
                    return Core.EStr{s}
                case KSym{s}:
                  P.go(fl, PsE{PsPrimarySym{P.which(s, ["(", "[", "{", "~", "+", "-", "@", "&", "?", "\\", "%"])}})
                case other:
                  do Parser<Core.Expr>:
                    P.err("expected an expression")
                    return Core.EErr{""}
            case PsPrimary{}:
              do Parser<Core.Expr>:
                t : Tok <- P.peek()
                P.go(fl, PsE{PsPrimaryK{P.tok_kind(t)}})
            # a[i], or the write a[i] <- v (the written array).
            case PsPostfixSet{e, i, set}:
              match set:
                case True{}:
                  do Parser<Core.Expr>:
                    P.skip()
                    v : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    return Core.ECall{Core.EVar{"Array.set"}, [Core.ETy{"U32", Nil{}}, e, i, v]}
                case False{}:
                  P.go(fl, PsE{PsPostfix{Core.ECall{Core.EVar{"Array.get"}, [Core.ETy{"U32", Nil{}}, e, i]}}})
            # Postfix: calls f(..), f!(..), and indexing a[i].
            case PsPostfixK{e, k}:
              match k:
                case 0n:
                  do Parser<Core.Expr>:
                    P.skip()
                    args : List<&2, Core.Expr> <- P.go(fl, PsL{PsList{")"}})
                    P.go(fl, PsE{PsPostfix{Core.ECall{e, args}}})
                case 1n:
                  do Parser<Core.Expr>:
                    P.skip()
                    P.expect("(")
                    args : List<&2, Core.Expr> <- P.go(fl, PsL{PsList{")"}})
                    P.go(fl, PsE{PsPostfix{Core.ECall{Core.EVar{"%gpu"}, e <> args}}})
                case 2n:
                  do Parser<Core.Expr>:
                    P.skip()
                    i : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("]")
                    t : Tok <- P.peek()
                    P.go(fl, PsE{PsPostfixSet{e, i, P.tok_is(t, "<-")}})
                case 3n+p:
                  Parser.pure(Core.Expr, e)
            case PsPostfixT{e, +t}:
              P.go(fl, PsE{PsPostfixK{e, Bool.pick(Nat, P.tok_sp(t), 9n, P.tok_which(t, ["(", "!", "["]))}})
            case PsPostfix{e}:
              do Parser<Core.Expr>:
                t : Tok <- P.peek()
                P.go(fl, PsE{PsPostfixT{e, t}})
            case PsTerm{}:
              do Parser<Core.Expr>:
                e : Core.Expr <- P.go(fl, PsE{PsPrimary{}})
                P.go(fl, PsE{PsPostfix{e}})
            case PsDo{}:
              do Parser<Core.Expr>:
                P.skip()
                m : String <- P.ident()
                P.expect("<")
                +args : List<&2, Core.Expr> <- P.go(fl, PsL{PsTyargs{}})
                P.expect(":")
                P.expect_in()
                ss : List<&2, Stmt> <- P.go(fl, PsS{PsStmts{}})
                return Fold.do(m, P.init(args), P.last(args), ss)
            # A block body: an indented statement list, folded.
            case PsBody{}:
              do Parser<Core.Expr>:
                P.expect_in()
                ss : List<&2, Stmt> <- P.go(fl, PsS{PsStmts{}})
                return Fold.plain(ss)
            case PsMatch{}:
              do Parser<Core.Expr>:
                P.skip()
                scrs : List<&2, Core.Expr> <- P.go(fl, PsL{PsScrs{}})
                P.expect(":")
                t : Tok <- P.peek()
                cases : List<&2, Core.Expr> <- P.go(fl, PsL{PsMatchBody{P.is_in(t)}})
                return Core.EMatch{scrs, cases}
        case PsL{q}:
          match q:
            # Comma-separated expressions up to (and including) a closing symbol.
            case PsListMore{+close, more}:
              match more:
                case True{}:
                  P.go(fl, PsL{PsList{close}})
                case False{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.expect(close)
                    return Nil{}
            case PsListItem{+close}:
              do Parser<List<&2, Core.Expr>>:
                e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                more : Bool <- P.eat(",")
                rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsListMore{close, more}})
                return e <> rest
            case PsListGo{+close, at_close}:
              match at_close:
                case True{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.skip()
                    return Nil{}
                case False{}:
                  P.go(fl, PsL{PsListItem{close}})
            case PsListStuck{+close, +t, stuck}:
              match stuck:
                case True{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.err("unterminated list")
                    return Nil{}
                case False{}:
                  P.go(fl, PsL{PsListGo{close, P.tok_is(t, close)}})
            case PsList{+close}:
              do Parser<List<&2, Core.Expr>>:
                +t : Tok <- P.peek()
                P.go(fl, PsL{PsListStuck{close, t, P.stuck(P.tok_kind(t))}})
            case PsParenItem{e, k}:
              match k:
                case 0n:
                  do Parser<List<&2, Core.Expr>>:
                    P.skip()
                    rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsParenItems{}})
                    return e <> rest
                case 1n:
                  do Parser<List<&2, Core.Expr>>:
                    P.skip()
                    ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect(")")
                    return [Core.EAnn{e, P.head(ty)}]
                case 2n+p:
                  do Parser<List<&2, Core.Expr>>:
                    P.expect(")")
                    return [e]
            # A tuple's elements after its first ',': (a, b, c : T) annotates c alone.
            case PsParenItemsGo{close}:
              match close:
                case True{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.skip()
                    return Nil{}
                case False{}:
                  do Parser<List<&2, Core.Expr>>:
                    e : Core.Expr <- P.go(fl, PsE{PsIexpr{}})
                    t : Tok <- P.peek()
                    P.go(fl, PsL{PsParenItem{e, P.tok_which(t, [",", ":"])}})
            case PsParenItems{}:
              do Parser<List<&2, Core.Expr>>:
                t : Tok <- P.peek()
                P.go(fl, PsL{PsParenItemsGo{P.tok_is(t, ")")}})
            case PsTyargsMore{more}:
              match more:
                case True{}:
                  P.go(fl, PsL{PsTyargs{}})
                case False{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.gt()
                    return Nil{}
            case PsTyargsItem{}:
              do Parser<List<&2, Core.Expr>>:
                e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                more : Bool <- P.eat(",")
                rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsTyargsMore{more}})
                return e <> rest
            case PsTyargsClose{close}:
              match close:
                case True{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.gt()
                    return Nil{}
                case False{}:
                  P.go(fl, PsL{PsTyargsItem{}})
            case PsTyargsGo{+t, stuck}:
              match stuck:
                case True{}:
                  Parser.pure(List<&2, Core.Expr>, Nil{})
                case False{}:
                  P.go(fl, PsL{PsTyargsClose{P.is_gt(t)}})
            case PsTyargs{}:
              do Parser<List<&2, Core.Expr>>:
                +t : Tok <- P.peek()
                P.go(fl, PsL{PsTyargsGo{t, P.stuck(P.tok_kind(t))}})
            # Values of a parallel let: one expression per pattern.
            case PsExprsN{n}:
              match n:
                case 0n:
                  Parser.pure(List<&2, Core.Expr>, Nil{})
                case 1n+p:
                  do Parser<List<&2, Core.Expr>>:
                    e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsExprsN{p}})
                    return e <> rest
            # A 'case' list of a match.
            case PsCasesGo{k}:
              match k:
                case 0n:
                  do Parser<List<&2, Core.Expr>>:
                    P.skip()
                    ps : List<&2, Core.Pat> <- P.pat_seq([":"])
                    P.expect(":")
                    body : Core.Expr <- P.go(fl, PsE{PsBody{}})
                    rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsCases{}})
                    return Core.ECase{ps, body} <> rest
                case 1n+p:
                  Parser.pure(List<&2, Core.Expr>, Nil{})
            case PsCasesDe{de}:
              match de:
                case True{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.skip()
                    return Nil{}
                case False{}:
                  do Parser<List<&2, Core.Expr>>:
                    +t : Tok <- P.peek()
                    P.go(fl, PsL{PsCasesGo{P.tok_which_id(t, ["case"])}})
            case PsCases{}:
              do Parser<List<&2, Core.Expr>>:
                P.nls()
                t : Tok <- P.peek()
                P.go(fl, PsL{PsCasesDe{P.is_de(t)}})
            case PsMatchBody{has}:
              match has:
                case True{}:
                  do Parser<List<&2, Core.Expr>>:
                    P.skip()
                    P.go(fl, PsL{PsCases{}})
                case False{}:
                  Parser.pure(List<&2, Core.Expr>, Nil{})
            case PsScrsGo{+t, stop}:
              match stop:
                case True{}:
                  Parser.pure(List<&2, Core.Expr>, Nil{})
                case False{}:
                  do Parser<List<&2, Core.Expr>>:
                    e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    _c : Bool <- P.eat(",")
                    rest : List<&2, Core.Expr> <- P.go(fl, PsL{PsScrs{}})
                    return e <> rest
            case PsScrs{}:
              do Parser<List<&2, Core.Expr>>:
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
                    i : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    P.expect("]")
                    P.expect("<-")
                    v : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    return [SLet{Core.PVar{name}, Core.ECall{Core.EVar{"Array.set"}, [Core.ETy{"U32", Nil{}}, Core.EVar{name}, i, v]}}]
                case False{}:
                  do Parser<List<&2, Stmt>>:
                    P.go(fl, PsU{PsSkipAnn{}})
                    P.expect("<-")
                    v : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    return [SBind{name, v}]
            case PsBindStmt{}:
              do Parser<List<&2, Stmt>>:
                e1 : Bool <- P.eat("+")
                name : String <- P.ident()
                +t : Tok <- P.peek()
                P.go(fl, PsS{PsBindArr{name, Bool.and(P.tok_is(t, "["), Bool.not(P.tok_sp(t)))}})
            case PsLetStmt{}:
              do Parser<List<&2, Stmt>>:
                +ps : List<&2, Core.Pat> <- P.pat_seq(["=", ":"])
                P.go(fl, PsU{PsSkipAnn{}})
                P.expect("=")
                +vs : List<&2, Core.Expr> <- P.go(fl, PsL{PsExprsN{List.length(&2, Core.Pat, ps)}})
                return P.lets.par(ps, vs)
            case PsStmtScanGo{k}:
              match k:
                case 0n:
                  do Parser<List<&2, Stmt>>:
                    e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
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
                    e : Core.Expr <- P.go(fl, PsE{PsMatch{}})
                    return [SExp{e}]
                case 1n:
                  do Parser<List<&2, Stmt>>:
                    P.skip()
                    e : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    return [SRet{e}]
                case 2n:
                  do Parser<List<&2, Stmt>>:
                    e : Core.Expr <- P.go(fl, PsE{PsDo{}})
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
                    ty : Core.Expr <- P.go(fl, PsE{PsExpr{}})
                    return Unit{}
                case False{}:
                  Parser.pure(Unit, Unit{})
            # Skips an optional ': Type' annotation.
            case PsSkipAnn{}:
              do Parser<Unit>:
                t : Tok <- P.peek()
                P.go(fl, PsU{PsSkipAnnGo{P.tok_is(t, ":")}})

def P.expr() -> Parser(Core.Expr):
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

def P.param.ty(name: String, +mode: U32, has: Bool) -> Parser(Core.Param):
  match has:
    case True{}:
      do Parser<Core.Param>:
        P.skip()
        ty : Core.Expr <- P.expr()
        return Core.Param{name, mode, P.phead(ty)}
    case False{}:
      Parser.pure(Core.Param, Core.Param{name, Bool.pick(U32, U32.is_zero(mode), 4, mode), ""})

def P.param.skip_mode.go(z: Bool) -> Parser(Unit):
  match z:
    case True{}:
      Parser.pure(Unit, Unit{})
    case False{}:
      P.skip()

def P.param.skip_mode(mode: U32) -> Parser(Unit):
  P.param.skip_mode.go(U32.is_zero(mode))

def P.param() -> Parser(Core.Param):
  do Parser<Core.Param>:
    +t : Tok <- P.peek()
    +mode : U32 <- Parser.pure(U32, P.param.mode(t))
    P.param.skip_mode(mode)
    name : String <- P.ident()
    t2 : Tok <- P.peek()
    P.param.ty(name, mode, P.tok_is(t2, ":"))

def P.ret.go(has: Bool) -> Parser(Core.Expr):
  match has:
    case True{}:
      do Parser<Core.Expr>:
        P.skip()
        P.expr()
    case False{}:
      Parser.pure(Core.Expr, Core.ETy{"", Nil{}})

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

def P.def.body(name: String, params: List<&2, Core.Param>, ret: Core.Expr, eff: Bool) -> Parser(Decl):
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

def P.params.sel(+fuel: Nat, sel: PsParamsSel) -> Parser(List<&2, Core.Param>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Core.Param>, Nil{})
    case 1n+fl:
      match sel:
        case PsParamsMore{more}:
          match more:
            case True{}:
              P.params.sel(fl, PsParams{})
            case False{}:
              do Parser<List<&2, Core.Param>>:
                P.expect(")")
                return Nil{}
        case PsParamsGo{close}:
          match close:
            case True{}:
              do Parser<List<&2, Core.Param>>:
                P.skip()
                return Nil{}
            case False{}:
              do Parser<List<&2, Core.Param>>:
                p : Core.Param <- P.param()
                more : Bool <- P.eat(",")
                rest : List<&2, Core.Param> <- P.params.sel(fl, PsParamsMore{more})
                return p <> rest
        # Parameters up to (and including) ')'.
        case PsParams{}:
          do Parser<List<&2, Core.Param>>:
            +t : Tok <- P.peek()
            P.params.sel(fl, PsParamsGo{Bool.or(P.tok_is(t, ")"), P.stuck(P.tok_kind(t)))})

def P.params() -> Parser(List<&2, Core.Param>):
  P.params.sel(Fuel.max(), PsParams{})

def P.def() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    name : String <- P.ident()
    unsafe : Bool <- P.eat("?")
    P.expect("(")
    params : List<&2, Core.Param> <- P.params()
    t : Tok <- P.peek()
    ret : Core.Expr <- P.ret.go(P.tok_is(t, "->"))
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
                ty : Core.Expr <- P.expr()
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

def P.law.sel(+fuel: Nat, sel: PsLawSel) -> Parser(List<&2, Core.Param>):
  match fuel:
    case 0n:
      P.fuel(List<&2, Core.Param>, Nil{})
    case 1n+fl:
      match sel:
        # The 'for' parameters of a law, up to (and including) the dedent.
        case PsLawLines{}:
          do Parser<List<&2, Core.Param>>:
            P.nls()
            +t : Tok <- P.peek()
            P.law.sel(fl, PsLawGo{t, Bool.pick(Nat, P.is_de(t), 0n,
              Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n))})
        case PsLawLine{k}:
          match k:
            case 0n:
              do Parser<List<&2, Core.Param>>:
                P.skip()
                p : Core.Param <- P.param()
                P.skip_line()
                rest : List<&2, Core.Param> <- P.law.sel(fl, PsLawLines{})
                return p <> rest
            case 1n+p:
              do Parser<List<&2, Core.Param>>:
                P.skip_line()
                P.law.sel(fl, PsLawLines{})
        case PsLawGo{+t, k}:
          match k:
            case 0n:
              do Parser<List<&2, Core.Param>>:
                P.skip()
                return Nil{}
            case 1n:
              Parser.pure(List<&2, Core.Param>, Nil{})
            case 2n+p:
              P.law.sel(fl, PsLawLine{P.tok_which_id(t, ["for"])})

def P.law.lines() -> Parser(List<&2, Core.Param>):
  P.law.sel(Fuel.max(), PsLawLines{})

# The type of a def that writes none.
def P.no_ty(e: Core.Expr) -> Bool:
  match e:
    case Core.ETy{n, args}:
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

def P.law.ty.pick(e: Core.Expr, rest: Toks()) -> Core.Expr:
  match rest:
    case Tok{KNL{}, sp, ln} <> t:
      e
    case Tok{KDe{}, sp, ln} <> t:
      e
    case other:
      Core.ETy{"", Nil{}}

def P.law.ty.fin(r: Core.Expr & Toks(), ts: Toks()) -> Core.Expr & Toks():
  (e, rest) = r
  (P.law.ty.pick(e, rest), ts)

def P.law.ty.go(+ts: Toks()) -> Core.Expr & Toks():
  P.law.ty.fin(P.expr()(ts), ts)

# A law's type line as a type, when it reads as one to its end (a claim like
# {a == b : T} may not): the type of a def that fills the law and writes none.
def P.law.ty() -> Parser(Core.Expr):
  ts => P.law.ty.go(ts)

# The parsers of a law's type, which call each other, as one def: a
# selector picks the parser (with its arguments).
type PsRetsSel is Data:
  PsLawRetsLine{k: Nat}
  PsLawRetsGo{t: Tok, k: Nat}
  PsLawRets{}

def P.law.rets.sel(+fuel: Nat, sel: PsRetsSel) -> Parser(Core.Expr):
  match fuel:
    case 0n:
      P.fuel(Core.Expr, Core.ETy{"", Nil{}})
    case 1n+fl:
      match sel:
        case PsLawRetsLine{k}:
          match k:
            case 0n:
              do Parser<Core.Expr>:
                P.skip_line()
                P.law.rets.sel(fl, PsLawRets{})
            case 1n:
              do Parser<Core.Expr>:
                P.skip()
                +x : String <- P.ident()
                P.expect(":")
                ty : Core.Expr <- P.expr()
                P.skip_line()
                rest : Core.Expr <- P.law.rets.sel(fl, PsLawRets{})
                return Core.ETy{"Sigma", [Core.ETy{"#q", Nil{}}, Core.ETy{"#q", Nil{}}, ty, Core.ELam{Core.PVar{x}, rest}]}
            case 2n+p:
              do Parser<Core.Expr>:
                +e : Core.Expr <- P.law.ty()
                P.skip_line()
                +rest : Core.Expr <- P.law.rets.sel(fl, PsLawRets{})
                return Bool.pick(Core.Expr, P.no_ty(rest), e, rest)
        case PsLawRetsGo{+t, k}:
          match k:
            case 0n:
              Parser.pure(Core.Expr, Core.ETy{"", Nil{}})
            case 1n:
              Parser.pure(Core.Expr, Core.ETy{"", Nil{}})
            case 2n+p:
              P.law.rets.sel(fl, PsLawRetsLine{P.tok_which_id(t, ["for", "exs"])})
        # The type of a law: its last line that is not a 'for'.
        case PsLawRets{}:
          do Parser<Core.Expr>:
            P.nls()
            +t : Tok <- P.peek()
            P.law.rets.sel(fl, PsLawRetsGo{t, Bool.pick(Nat, P.is_de(t), 0n,
              Bool.pick(Nat, P.stuck(P.tok_kind(t)), 1n, 2n))})

def P.law.rets() -> Parser(Core.Expr):
  P.law.rets.sel(Fuel.max(), PsLawRets{})

def P.law() -> Parser(Decl):
  do Parser<Decl>:
    P.skip()
    name : String <- P.ident()
    P.expect(":")
    P.expect_in()
    ret : Core.Expr <- P.look(Core.Expr, P.law.rets())
    params : List<&2, Core.Param> <- P.law.lines()
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
    kind : Core.Expr <- P.expr()
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

def Param.show(p: Core.Param) -> String:
  Core.Param{n, m, t} = p
  U32.show(m) ++ n ++ ":" ++ t

# A pattern; with args, the fields of a PCtor (its name unused), each after
# a space. The fields go one at a time: PCtor{n, t} is the rest of them.
def Pat.show.go(p: Core.Pat, +args: Bool) -> String:
  match p:
    case Core.PVar{n}:
      n
    case Core.PCtor{+n, xs}:
      match xs:
        case Nil{}:
          Bool.pick(String, args, "", n ++ "{}")
        case h <> t:
          Bool.pick(String, args, " ", n ++ "{") ++ Pat.show.go(h, False{}) ++
            Pat.show.go(Core.PCtor{n, t}, True{}) ++ Bool.pick(String, args, "", "}")
    case Core.PNat{n}:
      U32.show(n) ++ "n"
    case Core.PSucc{k, q}:
      U32.show(k) ++ "n+" ++ Pat.show.go(q, False{})
    case Core.PNum{n}:
      U32.show(n)
    case Core.PFlt{s}:
      s

def Pat.show(p: Core.Pat) -> String:
  Pat.show.go(p, False{})

def Pats.show(xs: List<&2, Core.Pat>) -> String:
  match xs:
    case Nil{}:
      ""
    case h <> t:
      Pat.show(h) ++ Pat.show.go(Core.PCtor{"", t}, True{})

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
def Expr.show.go(e: Core.Expr, s: String, k: Nat) -> String:
  match e:
    case Core.EVar{n}:
      n ++ s
    case Core.ENum{n}:
      U32.show(n) ++ s
    case Core.ENat{n}:
      U32.show(n) ++ "n" ++ s
    case Core.EFlt{x}:
      x ++ s
    case Core.EStr{x}:
      "\"" ++ x ++ "\"" ++ s
    case Core.ECall{+f, args}:
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
              "(" ++ Expr.show.go(f, " " ++ Expr.show.go(a, Expr.show.go(Core.ECall{f, t}, s, 1n), 0n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(Core.ECall{f, t}, s, 1n), 0n)
    case Core.ECtor{+n, args}:
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
              n ++ "{" ++ Expr.show.go(a, Expr.show.go(Core.ECtor{n, t}, s, 1n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(Core.ECtor{n, t}, s, 1n), 0n)
    case Core.ELam{p, b}:
      "(\\" ++ Pat.show(p) ++ " " ++ Expr.show.go(b, ")" ++ s, 0n)
    case Core.ELet{p, v, b}:
      "(let " ++ Pat.show(p) ++ " " ++ Expr.show.go(v, " " ++ Expr.show.go(b, ")" ++ s, 0n), 0n)
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          match k:
            case 0n:
              "(match [" ++ Expr.show.go(a, Expr.show.go(Core.EMatch{t, cases}, s, 1n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(Core.EMatch{t, cases}, s, 1n), 0n)
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
              Expr.show.cases(k) ++ Expr.show.go(c, Expr.show.go(Core.EMatch{Nil{}, t}, s, 2n), 0n)
    case Core.ECase{ps, b}:
      "(case " ++ Pats.show(ps) ++ " => " ++ Expr.show.go(b, ")" ++ s, 0n)
    case Core.ESucc{n, x}:
      "(" ++ U32.show(n) ++ "n+ " ++ Expr.show.go(x, ")" ++ s, 0n)
    case Core.EOp{op, a, b}:
      "(" ++ op ++ " " ++ Expr.show.go(a, " " ++ Expr.show.go(b, ")" ++ s, 0n), 0n)
    case Core.EAnn{x, t}:
      "(: " ++ Expr.show.go(x, " " ++ t ++ ")" ++ s, 0n)
    case Core.ETy{+n, targs}:
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
              "#" ++ n ++ "<" ++ Expr.show.go(a, Expr.show.go(Core.ETy{n, t}, s, 1n), 0n)
            case other:
              " " ++ Expr.show.go(a, Expr.show.go(Core.ETy{n, t}, s, 1n), 0n)
    case Core.EErr{m}:
      "(ERR " ++ m ++ ")" ++ s

def Expr.show(e: Core.Expr) -> String:
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
def Params.show(xs: List<&2, Core.Param>) -> String:
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
def Expr.push(a: Core.Expr, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.ECall{f, xs}:
      Core.ECall{f, a <> xs}
    case Core.ECtor{n, xs}:
      Core.ECtor{n, a <> xs}
    case Core.ETy{n, xs}:
      Core.ETy{n, a <> xs}
    case Core.EMatch{xs, cs}:
      Core.EMatch{a <> xs, cs}
    case other:
      other

def Expr.push.case(c: Core.Expr, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.EMatch{xs, cs}:
      Core.EMatch{xs, c <> cs}
    case other:
      other

def R.ops(e: Core.Expr, +ty: String) -> Core.Expr:
  match e:
    case Core.EOp{op, a, b}:
      Core.ECall{Core.EVar{ty ++ "." ++ R.opname(op)}, [R.ops(a, ty), R.ops(b, ty)]}
    case Core.EAnn{x, +t}:
      R.ops(x, Bool.pick(String, String.is_empty(t), ty, t))
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{R.ops(f, ty), Nil{}}
        case a <> t:
          Expr.push(R.ops(a, ty), R.ops(Core.ECall{f, t}, ty))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Core.ECtor{n, Nil{}}
        case a <> t:
          Expr.push(R.ops(a, ty), R.ops(Core.ECtor{n, t}, ty))
    case Core.ELam{p, b}:
      Core.ELam{p, R.ops(b, ty)}
    case Core.ELet{p, v, b}:
      Core.ELet{p, R.ops(v, ty), R.ops(b, ty)}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(R.ops(a, ty), R.ops(Core.EMatch{t, cases}, ty))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(R.ops(c, ty), R.ops(Core.EMatch{Nil{}, t}, ty))
    case Core.ECase{ps, b}:
      Core.ECase{ps, R.ops(b, ty)}
    case Core.ESucc{k, x}:
      Core.ESucc{k, R.ops(x, ty)}
    case other:
      other

# Free variables
# ==============

def FV.var(+x: String, +bound: List<&2, String>, +acc: List<&2, String>) ->
  List<&2, String>:
  Bool.pick(List<&2, String>, Bool.or(Str.has(bound, x), Str.has(acc, x)), acc,
    x <> acc)

# A PCtor's fields go one at a time: PCtor{n, t} is the rest of them.
def Pat.vars(p: Core.Pat, acc: List<&2, String>) -> List<&2, String>:
  match p:
    case Core.PVar{x}:
      x <> acc
    case Core.PCtor{+n, args}:
      match args:
        case Nil{}:
          acc
        case h <> t:
          Pat.vars(Core.PCtor{n, t}, Pat.vars(h, acc))
    case Core.PSucc{k, q}:
      Pat.vars(q, acc)
    case other:
      acc

def Pats.vars(ps: List<&2, Core.Pat>, acc: List<&2, String>) -> List<&2, String>:
  Pat.vars(Core.PCtor{"", ps}, acc)

# skip: the callee of the call e is done (the call was rebuilt with the
# rest of its arguments).
def FV.go(e: Core.Expr, +bound: List<&2, String>, acc: List<&2, String>, skip: Bool) ->
  List<&2, String>:
  match e:
    case Core.EVar{x}:
      FV.var(x, bound, acc)
    case Core.ECall{+f, args}:
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
              FV.go(Core.ECall{f, t}, bound, FV.go(a, bound, acc, False{}), True{})
            case False{}:
              FV.go(Core.ECall{f, t}, bound, FV.go(a, bound, FV.go(f, bound, acc, False{}), False{}), True{})
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          acc
        case a <> t:
          FV.go(Core.ECtor{n, t}, bound, FV.go(a, bound, acc, False{}), False{})
    case Core.ELam{p, b}:
      FV.go(b, Pat.vars(p, bound), acc, False{})
    case Core.ELet{p, v, b}:
      FV.go(b, Pat.vars(p, bound), FV.go(v, bound, acc, False{}), False{})
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          FV.go(Core.EMatch{t, cases}, bound, FV.go(a, bound, acc, False{}), False{})
        case Nil{}:
          match cases:
            case Nil{}:
              acc
            case c <> t:
              FV.go(Core.EMatch{Nil{}, t}, bound, FV.go(c, bound, acc, False{}), False{})
    case Core.ECase{ps, b}:
      FV.go(b, Pats.vars(ps, bound), acc, False{})
    case Core.ESucc{k, x}:
      FV.go(x, bound, acc, False{})
    case Core.EOp{op, a, b}:
      FV.go(b, bound, FV.go(a, bound, acc, False{}), False{})
    case Core.EAnn{x, t}:
      FV.go(x, bound, acc, False{})
    case other:
      acc

def FV.expr(e: Core.Expr, +bound: List<&2, String>, acc: List<&2, String>) -> List<&2, String>:
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

def DGrp.id(d: DGrp) -> String:
  DGrp{id, n} = d
  id

# A def's borrowed parameters (counted programs, see Bor below): one flag
# per parameter, "1" when borrowed ("" for a def with none).
def Bor.key(+name: String) -> String:
  "%b" ++ name

def Bor.flags(+g: G, +name: String) -> String:
  DGrp.id(G.dps(g, Bor.key(name)))

def Bor.list(s: String) -> List<&2, Bool>:
  match s:
    case SNil{}:
      Nil{}
    case SCon{Chr{c}, t}:
      U32.is_eq(c, 49) <> Bor.list(t)

def Bor.head(fl: List<&2, Bool>) -> Bool:
  match fl:
    case Nil{}:
      False{}
    case b <> t:
      b

def Bor.tail(fl: List<&2, Bool>) -> List<&2, Bool>:
  match fl:
    case Nil{}:
      Nil{}
    case b <> t:
      t

def Bor.any(fl: List<&2, Bool>) -> Bool:
  match fl:
    case Nil{}:
      False{}
    case b <> t:
      Bool.or(b, Bor.any(t))

# The flags of the parameters a mask keeps.
def Bor.kept(mask: List<&2, Bool>, +fl: List<&2, Bool>) -> List<&2, Bool>:
  match mask:
    case Nil{}:
      Nil{}
    case True{} <> mt:
      Bor.head(fl) <> Bor.kept(mt, Bor.tail(fl))
    case False{} <> mt:
      Bor.kept(mt, Bor.tail(fl))

# Whether a C expression is borrowed: a borrowed parameter's name, or what
# a match reads out of one, carries the comment /*b*/.
def RC.bor(s: String) -> Bool:
  match s:
    case SNil{}:
      False{}
    case SCon{Chr{+c}, +t}:
      Bool.or(Bool.and(U32.is_eq(c, 47), String.starts_with(t, "*b*/")), RC.bor(t))

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
   "Map.get", "Map.has", "String.cmp", "String.eq",
   "Array.size", "Array.get", "Array.swap", "Array.set", "Array.new", "Array.clone",
   "Array.get%w", "Array.swap%w", "Array.set%w",
   "Array.atomic.add", "Array.atomic.min", "Array.atomic.max", "Array.atomic.and",
   "Array.atomic.or", "Array.atomic.xor", "Array.atomic.exch", "Array.atomic.cas",
   "Array.atomic.fadd"]

def G.is_native(+name: String) -> Bool:
  Str.has(Natives(), name)

def G.erased_ty(+t: String) -> Bool:
  Str.has(["Type", "Data", "Quant", "Kind"], t)

def G.keep(p: Core.Param) -> Bool:
  Core.Param{n, +m, +t} = p
  Bool.not(Bool.or(Bool.or(U32.is_eq(m, 1), U32.is_eq(m, 4)), G.erased_ty(t)))

def G.mask(ps: List<&2, Core.Param>) -> List<&2, Bool>:
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
def G.bare(ps: List<&2, Core.Param>) -> List<&2, Core.Param>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Param{n, +m, t} <> r:
      Core.Param{n, Bool.pick(U32, U32.is_eq(m, 4), 0, m), t} <> G.bare(r)

def G.params.go(lps: List<&2, Core.Param>, ps: List<&2, Core.Param>) -> List<&2, Core.Param>:
  match lps:
    case Nil{}:
      G.bare(ps)
    case h <> t:
      h <> t

def G.law.ps(d: Decl) -> List<&2, Core.Param>:
  match d:
    case DLaw{n, ps, r}:
      ps
    case other:
      Nil{}

def G.law.ret(d: Decl) -> Core.Expr:
  match d:
    case DLaw{n, ps, r}:
      r
    case other:
      Core.ETy{"", Nil{}}

# Parameter modes of a def come from its law when it fills one.
def G.params(+laws: Map<&2, Decl>, +name: String, ps: List<&2, Core.Param>) ->
  List<&2, Core.Param>:
  G.params.go(G.law.ps(G.get(Decl, DImport{"", ""}, laws, name)), ps)

# So does its return type, when the def does not write one.
def G.ret(+laws: Map<&2, Decl>, +name: String, +ret: Core.Expr) -> Core.Expr:
  Bool.pick(Core.Expr, P.no_ty(ret), G.law.ret(G.get(Decl, DImport{"", ""}, laws, name)), ret)

def G.add.type(+name: String, ps: List<&2, String>, +cs: List<&2, Ctor>, g: G) -> G:
  G{ctors, defs, bodies, dps} = g
  +n = U32.from_nat(List.length(&2, Ctor, cs))
  G{G.ctors(name, cs, 0, n, ctors), Map.set(&2, DInfo, defs, name,
    DInfo{3, Nil{}}), Map.set(&2, Decl, bodies, "%" ++ name, DType{name, ps, cs}), dps}

def G.add.law(+name: String, ps: List<&2, Core.Param>, g: G) -> G:
  G{ctors, defs, bodies, dps} = g
  G{ctors, Map.set(&2, DInfo, defs, name,
    DInfo{Bool.pick(U32, G.is_native(name), 2, 3), G.mask(ps)}), bodies, dps}

def G.add.def(
  +name: String, +ps: List<&2, Core.Param>, body: Core.Expr, ret: Core.Expr,
  +laws: Map<&2, Decl>, g: G
) -> G:
  G{ctors, defs, bodies, dps} = g
  G{ctors, Map.set(&2, DInfo, defs, name,
    DInfo{Bool.pick(U32, G.is_native(name), 2, 0),
      G.mask(G.params(laws, name, ps))}),
    Map.set(&2, Decl, bodies, name, DDef{name, ps, body, G.ret(laws, name, ret)}), dps}

def G.add.eff(+name: String, +ps: List<&2, Core.Param>, ims: List<&2, String>,
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
# TOut: a flat result (see Gen.def.unb), its k fields stored through o.
type Tgt is Data:
  TRet{}
  TSet{v: String}
  TDst{id: String, n: U32}
  TOut{k: U32, free: Bool}

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
    case TOut{k, free}:
      Doc.list([DStr{"bend_open("}, d, DStr{", o, " ++ U32.show(k) ++ ", " ++ Bool.pick(String, free, "1", "0") ++
        ");\nreturn 0;\n"}])

# A pattern against a C path yields tests and bindings.
type PatR is Data:
  PatR{conds: List<&2, String>, binds: Env()}

# A counted program (BEND_RC=1) binds a pattern's _ too, as _%, to drop
# what it matches (Gen.free and Gen.rc are below).
def Gen.pat.rcname(+g: G, +x: String) -> String:
  Bool.pick(String, Bool.and(Str.eq(DGrp.id(G.dps(g, "%free")), "2"), Str.eq(x, "_")), "_%", x)

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

# Counted, an ALeaf's cell gets a reference ("%leaf", rc_dup_leaf) before
# the array is dropped ("%arr").
def Gen.pat.leaf(rc: Bool, +path: String, r: PatR) -> PatR:
  match rc:
    case True{}:
      PatR{conds, binds} = r
      PatR{conds, Bind{"%arr", path} <> Bind{"%leaf", path} <> binds}
    case False{}:
      r

# A machine word's structural view, under U32{..} or F32{..}: WCon{head,
# tail} is its low bit and the rest shifted down, WNil what is left (the
# word is its raw bits; a Word(n) elsewhere stays a list of Bools).
def Pat.wordk(p: Core.Pat) -> Nat:
  match p:
    case Core.PCtor{+name, args}:
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
  p: Core.Pat, st: Nat, +g: G, +path: String, +i: U32, info: Maybe<&2, CInfo>, k: Nat, r: PatR
) -> PatR:
  match p:
    case Core.PCtor{+name, args}:
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
                      Gen.pat.go(Core.PCtor{name, Nil{}}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(False{}, ar, path,
                          Gen.pat.tag(single, "IS_N(" ++ path ++ ", " ++ U32.show(tag) ++ ")", r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(Core.PCtor{name, Nil{}}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(Core.PCtor{name, Nil{}}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.go(Core.PCtor{name, Nil{}}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r))
                    case 6n+q:
                      Gen.pat.cond("arr_cls(" ++ path ++ ") != 0", r)
            case 2n:
              match info:
                case None{}:
                  Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      Gen.pat.go(Core.PCtor{name, Nil{}}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              Gen.pat.go(Core.PCtor{name, Nil{}}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(Core.PCtor{name, Nil{}}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +a <> Nil{}:
          match st:
            case 0n:
              Gen.pat.go(Core.PCtor{name, Nil{}}, 0n, g, path, U32.inc(i), None{}, 0n,
                Gen.pat.go(a, 3n, g, Bool.pick(String, U32.is_eq(i, 99), path,
                  "FLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      Gen.pat.go(Core.PCtor{name, [a]}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(True{}, ar, path,
                          Gen.pat.tag(single, "IS_N(" ++ path ++ ", " ++ U32.show(tag) ++ ")", r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(Core.PCtor{name, [a]}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(Core.PCtor{name, [a]}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.leaf(Str.eq(DGrp.id(G.dps(g, "%free")), "2"), path,
                        Gen.pat.go(Core.PCtor{name, [a]}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r)))
                    case 6n+q:
                      Gen.pat.cond("arr_cls(" ++ path ++ ") != 0", r)
            case 2n:
              match info:
                case None{}:
                  Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      Gen.pat.go(Core.PCtor{name, [a]}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      Gen.pat.go(a, 4n, g, path, 0, None{}, Pat.wordk(a), r)
            case 3n:
              Gen.pat.go(Core.PCtor{name, [a]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(Core.PCtor{name, [a]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +a <> +b <> Nil{}:
          match st:
            case 0n:
              Gen.pat.go(Core.PCtor{name, [b]}, 0n, g, path, U32.inc(i), None{}, 0n,
                Gen.pat.go(a, 3n, g, Bool.pick(String, U32.is_eq(i, 99), path,
                  "FLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      Gen.pat.go(Core.PCtor{name, [a, b]}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(True{}, ar, path,
                          Gen.pat.tag(single, "IS_N(" ++ path ++ ", " ++ U32.show(tag) ++ ")", r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(Core.PCtor{name, [a, b]}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(Core.PCtor{name, [a, b]}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.go(Core.PCtor{name, [a, b]}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r))
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
                      Gen.pat.go(Core.PCtor{name, [a, b]}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              Gen.pat.go(Core.PCtor{name, [a, b]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  Gen.pat.go(b, 4n, g, "((V)(U32)(" ++ path ++ ") >> 1)", 0, None{}, Pat.wordk(b),
                    Gen.pat.go(a, 3n, g, "BOOL((" ++ path ++ ") & 1)", 0, None{}, 0n, r))
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(Core.PCtor{name, [a, b]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +h <> +t:
          match st:
            case 0n:
              Gen.pat.go(Core.PCtor{name, t}, 0n, g, path, U32.inc(i), None{}, 0n,
                Gen.pat.go(h, 3n, g, Bool.pick(String, U32.is_eq(i, 99), path,
                  "FLD(" ++ path ++ ", " ++ U32.show(i) ++ ")"), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      Gen.pat.go(Core.PCtor{name, h <> t}, 0n, g, path, 0, None{}, 0n,
                        Gen.pat.node(True{}, ar, path,
                          Gen.pat.tag(single, "IS_N(" ++ path ++ ", " ++ U32.show(tag) ++ ")", r)))
                    case 1n:
                      Gen.pat.tag(single, "(" ++ path ++ ") == IMM(" ++ U32.show(tag) ++ ")", r)
                    case 2n:
                      Gen.pat.go(Core.PCtor{name, h <> t}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      Gen.pat.cond("(" ++ path ++ ") == 0", r)
                    case 4n:
                      Gen.pat.go(Core.PCtor{name, h <> t}, 0n, g, "nat_subk(" ++ path ++ ", 1)", 99, None{}, 0n,
                        Gen.pat.cond("(" ++ path ++ ") != 0", r))
                    case 5n:
                      Gen.pat.go(Core.PCtor{name, h <> t}, 0n, g, path, 0, None{}, 0n, Gen.pat.cond("arr_cls(" ++ path ++ ") == 0", r))
                    case 6n+q:
                      Gen.pat.cond("arr_cls(" ++ path ++ ") != 0", r)
            case 2n:
              match info:
                case None{}:
                  Gen.pat.cond("0 /* unknown constructor " ++ name ++ " */", r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      Gen.pat.go(Core.PCtor{name, h <> t}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              Gen.pat.go(Core.PCtor{name, h <> t}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  Gen.pat.go(Core.PCtor{name, h <> t}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
    case Core.PVar{+x}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          Gen.pat.var(Gen.pat.rcname(g, x), path, r)
        case 4n:
          match k:
            case 2n+z:
              Gen.pat.var(Gen.pat.rcname(g, x), path, r)
            case other:
              r
        case other:
          r
    case Core.PNat{+n}:
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
    case Core.PSucc{+j, q}:
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
    case Core.PNum{+n}:
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
    case Core.PFlt{+f}:
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

def Gen.pat(+g: G, p: Core.Pat, +path: String, r: PatR) -> PatR:
  Gen.pat.go(p, 3n, g, path, 0, None{}, 0n, r)

def Gen.pats(+g: G, ps: List<&2, Core.Pat>, paths: List<&2, String>, r: PatR) -> PatR:
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
  Split{kept: List<&2, Core.Expr>, all: List<&2, Core.Expr>, extra: List<&2, Core.Expr>, full: Bool}

def Gen.split(mask: List<&2, Bool>, args: List<&2, Core.Expr>, r: Split) -> Split:
  match mask args:
    case Nil{} xs:
      Split{kept, all, extra, full} = r
      Split{kept, all, xs, True{}}
    case m <> mt Nil{}:
      Split{kept, all, extra, full} = r
      Split{kept, all, Nil{}, False{}}
    case True{} <> mt +a <> at:
      Split{kept, all, extra, full} = r
      Gen.split(mt, at, Split{List.append(&2, Core.Expr, kept, [a]),
        List.append(&2, Core.Expr, all, [a]), extra, full})
    case False{} <> mt a <> at:
      Split{kept, all, extra, full} = r
      Gen.split(mt, at, Split{kept, List.append(&2, Core.Expr, all, [Core.ETy{"", Nil{}}]), extra, full})

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

# A node built in token tok's slot (h: "CR", or "CRH" for a D_ node).
def Gen.ctor.ru(+tok: String, +h: String, +tag: U32, +ds: List<&2, Doc>) -> Doc:
  +n = Gen.len(ds)
  Bool.pick(Doc, U32.is_le(n, 4),
    Doc.list([DStr{h ++ U32.show(n) ++ "(" ++ tok ++ ", " ++ U32.show(tag) ++ ", "}, Gen.commas(ds),
      DStr{")"}]),
    Doc.list([DStr{h ++ "N(" ++ tok ++ ", " ++ U32.show(tag) ++ ", " ++ U32.show(n) ++ ", "},
      Gen.arr(ds), DStr{")"}]))

def Gen.ctor.kind.ru(+tok: String, +tag: U32, +kind: Nat, +ds: List<&2, Doc>) -> Doc:
  Bool.pick(Doc, String.is_empty(tok), Gen.ctor.kind(tag, kind, ds), Gen.ctor.ru(tok, "CR", tag, ds))

def Gen.ctor.hnode.ru(+tok: String, +tag: U32, +ds: List<&2, Doc>) -> Doc:
  Bool.pick(Doc, String.is_empty(tok), Gen.ctor.hnode(tag, ds), Gen.ctor.ru(tok, "CRH", tag, ds))

# Constants
# ---------
#
# A constructor of literals (a node, and the nodes and strings and numbers
# in it) is built once and cached (KONST, see bendrt.h), as a string
# literal is: Natives() is a list of strings, built at each call before.

# A constructor kind a constant can hold: a node or a nullary.
def Gen.konst.kind(m: Maybe<&2, CInfo>) -> Bool:
  match m:
    case None{}:
      False{}
    case Some{CInfo{tag, ar, +kind, single}}:
      Bool.or(U32.is_eq(kind, 0), U32.is_eq(kind, 1))

def Gen.konst.node(m: Maybe<&2, CInfo>) -> Bool:
  match m:
    case None{}:
      False{}
    case Some{CInfo{tag, ar, +kind, single}}:
      U32.is_eq(kind, 0)

# Whether e is made of constructors of those kinds, strings and numbers
# only (a list field as its head and the node rebuilt with the rest).
def Gen.konst.ok(+g: G, e: Core.Expr) -> Bool:
  match e:
    case Core.EStr{s}:
      True{}
    case Core.ENum{n}:
      True{}
    case Core.ENat{n}:
      True{}
    case Core.ECtor{+name, args}:
      match args:
        case Nil{}:
          Gen.konst.kind(G.ctor(g, name))
        case a <> t:
          Bool.and(Gen.konst.ok(g, a), Gen.konst.ok(g, Core.ECtor{name, t}))
    case other:
      False{}

def Gen.konst.info(m: Maybe<&2, CInfo>, ds: List<&2, Doc>) -> Doc:
  match m:
    case None{}:
      DStr{"0"}
    case Some{CInfo{+tag, ar, kind, single}}:
      Gen.ctor.kind(tag, U32.to_nat(kind), ds)

# The C code building constants es (each Gen.konst.ok).
def Gen.konst.docs(+g: G, es: List<&2, Core.Expr>) -> List<&2, Doc>:
  match es:
    case Nil{}:
      Nil{}
    case e <> t:
      match e:
        case Core.EStr{s}:
          DStr{"MKS(\"" ++ Gen.lit(s) ++ "\")"} <> Gen.konst.docs(g, t)
        case Core.ENum{n}:
          DStr{U32.show(n) ++ "u"} <> Gen.konst.docs(g, t)
        case Core.ENat{n}:
          DStr{U32.show(n) ++ "u"} <> Gen.konst.docs(g, t)
        case Core.ECtor{+name, args}:
          Gen.konst.info(G.ctor(g, name), Gen.konst.docs(g, args)) <> Gen.konst.docs(g, t)
        case other:
          DStr{"0"} <> Gen.konst.docs(g, t)

# Whether constructor name of args is a constant worth caching (a node).
def Gen.konst.is(+g: G, +name: String, +args: List<&2, Core.Expr>) -> Bool:
  Bool.and(Gen.konst.node(G.ctor(g, name)), Gen.konst.ok(g, Core.ECtor{name, args}))

# A constant, built once: K<k>() answers it.
def Gen.konst(+g: G, +name: String, +args: List<&2, Core.Expr>) -> Gen(Doc):
  do Gen<Doc>:
    +k : U32 <- Gen.fresh()
    +f : String <- Gen.pure(String, "K" ++ U32.show(k))
    Gen.proto(DStr{"static V " ++ f ++ "(void);\n"})
    Gen.code(Doc.list([DStr{"static V " ++ f ++ "(void) { static V c; return KONST(c, "},
      Gen.konst.info(G.ctor(g, name), Gen.konst.docs(g, args)), DStr{"); }\n"}]))
    return DStr{f ++ "()"}

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

def Gen.scr.bor.m(m: Maybe<&2, String>) -> Bool:
  match m:
    case Some{c}:
      RC.bor(c)
    case None{}:
      False{}

# A match on a borrowed variable borrows its scrutinee.
def Gen.scr.bor(+env: Env(), e: Core.Expr) -> Bool:
  match e:
    case Core.EVar{+x}:
      Gen.scr.bor.m(Env.find(env, x))
    case other:
      False{}

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
    case TOut{k, free}:
      True{}

def Gen.is_tail(+env: Env(), +self: Self, +tgt: Tgt, +name: String, +args: List<&2, Core.Expr>) ->
  Bool:
  Self{+sn, +mask, cps} = self
  Bool.and(Bool.and(Gen.is_ret(tgt), Str.eq(sn, name)), Bool.and(
    Bool.not(Env.has(env, name)),
    Nat.is_eq(List.length(&2, Bool, mask), List.length(&2, Core.Expr, args))))

# F32.add(F32.mul(x, k), b), either way round, with k a literal: 1n when k is
# the mul's second argument, 2n when its first, else 0n.
def Gen.fadd.k(e: Core.Expr) -> Nat:
  match e:
    case Core.ECall{Core.EVar{f}, x <> Core.EFlt{s} <> Nil{}}:
      Bool.pick(Nat, Str.eq(f, "F32.mul"), 1n, 0n)
    case Core.ECall{Core.EVar{f}, Core.EFlt{s} <> x <> Nil{}}:
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

def Expr.wordk(e: Core.Expr) -> Nat:
  match e:
    case Core.ECtor{+name, args}:
      P.which(name, ["WCon", "WNil"])
    case other:
      2n

# Whether a tail call jumps to a D_ function: the target is a D_ function's
# (tgt) and name a def of its group, applied to all its parameters.
def Gen.dst.call(+g: G, +env: Env(), +tgt: Tgt, +name: String, +args: List<&2, Core.Expr>) -> Bool:
  match tgt:
    case TDst{+id, n}:
      Bool.and(Str.eq(id, DGrp.id(G.dps(g, name))), Bool.and(Bool.not(Env.has(env, name)),
        Nat.is_eq(List.length(&2, Bool, DInfo.mask(G.def(g, name))), List.length(&2, Core.Expr, args))))
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

def Gen.dst.hole.at(+g: G, +env: Env(), +tgt: Tgt, a: Core.Expr, +i: U32, acc: U32) -> U32:
  match a:
    case Core.ECall{Core.EVar{+h}, +hargs}:
      Bool.pick(U32, Gen.dst.call(g, env, tgt, h, hargs), U32.inc(i), acc)
    case other:
      acc

# In a D_ function, the field of a constructor node left as a hole: the
# last one that is a call to the group (1-based; 0 when there is none).
def Gen.dst.hole(+g: G, +env: Env(), +tgt: Tgt, node: Bool, as: List<&2, Core.Expr>, +i: U32, acc: U32) ->
  U32:
  match node as:
    case True{} a <> t:
      Gen.dst.hole(g, env, tgt, True{}, t, U32.inc(i), Gen.dst.hole.at(g, env, tgt, a, i, acc))
    case n l:
      acc

def Gen.dst.nth(k: Nat, as: List<&2, Core.Expr>) -> Core.Expr:
  match k as:
    case 0n a <> t:
      a
    case 1n+m a <> t:
      Gen.dst.nth(m, t)
    case n Nil{}:
      Core.EErr{"hole"}

def Gen.stmt.ctor.tag.go(info: Maybe<&2, CInfo>) -> U32:
  match info:
    case Some{CInfo{tag, ar, kind, single}}:
      tag
    case None{}:
      0

def Gen.stmt.ctor.tag(+g: G, +name: String) -> U32:
  Gen.stmt.ctor.tag.go(G.ctor(g, name))

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

# What a variable holds, as Gen.scalar.let says: a let's U32 local is
# "(uN)" (a uint32_t), any other scalar's name is in parentheses.
def Gen.scalar.u32.find(m: Maybe<&2, String>) -> U32:
  match m:
    case Some{+c}:
      Bool.pick(U32, String.starts_with(c, "(u"), 2, Bool.pick(U32, Gen.scalar.c(c), 1, 0))
    case None{}:
      0

# Whether a let's value is a variable holding a scalar.
def Gen.scalar.var(+env: Env(), v: Core.Expr) -> Bool:
  match v:
    case Core.EVar{+y}:
      Gen.scalar.find(Env.find(env, y))
    case other:
      False{}

# The natives whose result is a U32, and those whose result is another
# scalar (a Bool, a Nat, an F32).
def Gen.scalar.u32s() -> List<&2, String>:
  ["U32.inc", "U32.add", "U32.sub", "U32.mul", "U32.div", "U32.mod", "U32.not",
   "U32.and", "U32.or", "U32.xor", "U32.shl", "U32.shr", "U32.shln", "U32.shrn",
   "U32.from_nat", "U32.min", "U32.max", "U32.pow", "U32.log2", "F32.bits", "F32.to_u32"]

def Gen.scalar.others() -> List<&2, String>:
  ["U32.is_eq", "U32.is_ne", "U32.is_lt", "U32.is_le", "U32.is_gt", "U32.is_ge",
   "U32.is_zero", "U32.is_even", "U32.to_nat", "U32.to_f32",
   "F32.add", "F32.sub", "F32.mul", "F32.div", "F32.mod", "F32.pow", "F32.atan2",
   "F32.is_eq", "F32.is_ne", "F32.is_lt", "F32.is_le", "F32.is_gt", "F32.is_ge",
   "F32.neg", "F32.abs", "F32.sqrt", "F32.exp", "F32.log", "F32.log2",
   "F32.log10", "F32.sin", "F32.cos", "F32.tan", "F32.asin", "F32.acos",
   "F32.atan", "F32.sinh", "F32.cosh", "F32.tanh", "F32.floor", "F32.ceil",
   "F32.trunc"]

def Gen.scalar.ret.ty(+t: String) -> U32:
  Bool.pick(U32, Str.eq(t, "U32"), 2, Bool.pick(U32, Gen.scalar.ty(t), 1, 0))

# What a def's result is: 2 a U32, 1 another scalar, 0 anything else.
def Gen.scalar.ret(d: Decl) -> U32:
  match d:
    case DDef{n, ps, b, r}:
      Gen.scalar.ret.ty(P.head(r))
    case other:
      0

def Gen.scalar.fn(+g: G, +f: String, local: Bool) -> U32:
  match local:
    case True{}:
      0
    case False{}:
      Bool.pick(U32, Str.has(Gen.scalar.u32s(), f), 2,
        Bool.pick(U32, Str.has(Gen.scalar.others(), f), 1, Gen.scalar.ret(G.body(g, f))))

def Gen.scalar.bound(m: Maybe<&2, String>) -> Bool:
  match m:
    case Some{c}:
      True{}
    case None{}:
      False{}

# What a let's value is: 2 a U32 (its C local is a uint32_t), 1 another
# scalar (never shared), 0 anything else. A variable holding a scalar is 1;
# a call is what its def or native returns; a match, what its cases give
# (the least of them), a let what its body gives.
# Names bound inside a let's value: a let's variable stands for what its
# value is ("(u)" a U32, "(v)" another scalar, "x" anything else), a
# pattern's for anything.
def Gen.scalar.hide(xs: List<&2, String>, env: Env()) -> Env():
  match xs:
    case Nil{}:
      env
    case x <> t:
      Bind{x, "x"} <> Gen.scalar.hide(t, env)

def Gen.scalar.stand(+k: U32) -> String:
  Bool.pick(String, U32.is_eq(k, 2), "(u)", Bool.pick(String, U32.is_eq(k, 1), "(v)", "x"))

def Gen.scalar.tail(+g: G, v: Core.Expr, +env: Env()) -> U32:
  match v:
    case Core.EVar{+y}:
      Gen.scalar.u32.find(Env.find(env, y))
    case Core.ENum{n}:
      2
    case Core.ECall{Core.EVar{+f}, args}:
      Gen.scalar.fn(g, f, Gen.scalar.bound(Env.find(env, f)))
    case Core.ELet{p, x, b}:
      match p:
        case Core.PVar{+y}:
          Gen.scalar.tail(g, b, Bind{y, Gen.scalar.stand(Gen.scalar.tail(g, x, env))} <> env)
        case q:
          Gen.scalar.tail(g, b, Gen.scalar.hide(Pat.vars(q, Nil{}), env))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Gen.scalar.tail(g, Core.EMatch{t, cases}, env)
        case Nil{}:
          match cases:
            case Nil{}:
              2
            case c <> t:
              U32.min(Gen.scalar.tail(g, c, env), Gen.scalar.tail(g, Core.EMatch{Nil{}, t}, env))
    case Core.ECase{ps, b}:
      Gen.scalar.tail(g, b, Gen.scalar.hide(Pats.vars(ps, Nil{}), env))
    case Core.EAnn{y, t}:
      Gen.scalar.tail(g, y, env)
    case other:
      0

def Gen.scalar.let(+g: G, +env: Env(), v: Core.Expr) -> U32:
  Gen.scalar.tail(g, v, env)

def Gen.scalar.cty(+k: U32) -> String:
  Bool.pick(String, U32.is_eq(k, 2), "uint32_t ", "V ")

#
# A value bound to a variable used twice (on some path) is marked shared
# where it is bound (bend_share). A match or destructuring let that opens a
# node reads its fields into locals and hands the node to bend_take, which
# frees it unless it is shared, in which case the fields are shared too. See
# "Freeing on match" in bendrt.h.
# The uses of x in b, unless the names xs bind in front of it hide x.
def Use.under(xs: List<&2, String>, +x: String, n: Unit -> U32) -> U32:
  Bool.pick(Unit -> U32, Str.has(xs, x), u => 0, n)(Unit{})

# The uses of x on the path through e that uses it most (a use a binder of
# x hides is not one). A list field counts as its head and the node rebuilt
# with the rest.
def Use.n(+x: String, e: Core.Expr) -> U32:
  match e:
    case Core.EVar{+n}:
      Bool.pick(U32, Str.eq(n, x), 1, 0)
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Use.n(x, f)
        case a <> t:
          (Use.n(x, a) + Use.n(x, Core.ECall{f, t}) : U32)
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          0
        case a <> t:
          (Use.n(x, a) + Use.n(x, Core.ECtor{n, t}) : U32)
    case Core.ELam{p, b}:
      Use.under(Pat.vars(p, Nil{}), x, u => Use.n(x, b))
    case Core.ELet{p, v, b}:
      (Use.n(x, v) + Use.under(Pat.vars(p, Nil{}), x, u => Use.n(x, b)) : U32)
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          (Use.n(x, a) + Use.n(x, Core.EMatch{t, cases}) : U32)
        case Nil{}:
          match cases:
            case Nil{}:
              0
            case c <> t:
              U32.max(Use.n(x, c), Use.n(x, Core.EMatch{Nil{}, t}))
    case Core.ECase{ps, b}:
      Use.under(Pats.vars(ps, Nil{}), x, u => Use.n(x, b))
    case Core.ESucc{k, y}:
      Use.n(x, y)
    case Core.EOp{op, a, b}:
      (Use.n(x, a) + Use.n(x, b) : U32)
    case Core.EAnn{y, t}:
      Use.n(x, y)
    case other:
      0

# A binding's variable that body uses twice gets bend_share; one no path of
# body uses, bend_dead (an unshared array is then kept for Array.new).
def Gen.share.use(ok: Bool, +c: String, +u: U32) -> Doc:
  match ok:
    case True{}:
      Bool.pick(Doc, U32.is_le(2, u), DStr{"bend_share(" ++ c ++ ");\n"},
        Bool.pick(Doc, U32.is_zero(u), DStr{"bend_dead(" ++ c ++ ");\n"}, DNil{}))
    case False{}:
      DNil{}

def Gen.shares(binds: Env(), +body: Core.Expr) -> Doc:
  match binds:
    case Nil{}:
      DNil{}
    case Bind{+x, +c} <> t:
      Doc.list([Gen.share.use(Bool.not(Bool.or(Bool.or(Str.eq(x, "_"), Str.eq(c, "0")), Gen.scalar.c(c))),
        c, Use.n(x, body)), Gen.shares(t, body)])

# Whether matches free the nodes they open (BEND_NO_FREE turns it off: no
# sharing, no bend_take, the code of a traced heap only).
def Gen.free(+g: G) -> Bool:
  Str.has(["1", "2"], DGrp.id(G.dps(g, "%free")))

def Gen.shares.if(free: Bool, binds: Env(), +body: Core.Expr) -> Doc:
  match free:
    case True{}:
      Gen.shares(binds, body)
    case False{}:
      DNil{}

def Gen.shares.g(+g: G, binds: Env(), +body: Core.Expr) -> Doc:
  Gen.shares.if(Gen.free(g), binds, body)

# Reference counting
# ------------------
#
# A program compiled with BEND_RC=1 counts references (see "Reference
# counting" in bendrt.h). A variable owns one reference where it is bound;
# each use of it hands one on (to a call, a constructor, a closure that
# captures it, a match that opens it). So where a variable is bound, it gets
# a reference more for each use past the first on the path through its scope
# that uses it most (rc_dupn), or is dropped when no path uses it (rc_drop);
# a case that uses an outer variable fewer times than the most any case of
# its match does drops the difference first (RC.arm).
def Gen.rc(+g: G) -> Bool:
  Str.eq(DGrp.id(G.dps(g, "%free")), "2")

def Env.names(env: Env()) -> List<&2, String>:
  match env:
    case Nil{}:
      Nil{}
    case Bind{x, c} <> t:
      x <> Env.names(t)

def RC.kept.one(skip: Bool, a: Core.Expr, rest: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match skip:
    case True{}:
      rest
    case False{}:
      a <> rest

def Expr.is_var(e: Core.Expr, +x: String) -> Bool:
  match e:
    case Core.EVar{+y}:
      Str.eq(y, x)
    case other:
      False{}

# Temporary nodes
# ---------------
#
# A constructor passed where the callee borrows, whose fields are
# variables and numbers, is only read by the callee: when its variables are
# borrowed too (a borrowed parameter, or what a match reads out of one), it
# is built on the caller's stack (RC_TMP), without references, and a loop's
# next argument in one of two buffers per parameter (RC_TB; its fields must
# be read out of nodes, which never point into those buffers). This is the
# walk that rebuilds the node it opens with one field less, Opt.sz(CCall{f,
# t2}): the node it walks stays borrowed. RC.tmp.pass marks such arguments
# (%tmp) where the value cannot outlive the call: not in a lambda or a
# parallel let's values, and only in a full call. A marked argument whose
# variables are not all borrowed is built on the heap, each borrowed
# variable in it getting a reference there (RC.kept does not count them).

def RC.tmp.imm(m: Maybe<&2, CInfo>) -> Bool:
  match m:
    case None{}:
      False{}
    case Some{CInfo{tag, ar, +kind, single}}:
      Bool.not(U32.is_zero(kind))

# A field of a temporary: a variable, a number or a nullary constructor.
def RC.tmp.field(+g: G, e: Core.Expr) -> Bool:
  match e:
    case Core.ECtor{+n, as}:
      match as:
        case Nil{}:
          RC.tmp.imm(G.ctor(g, n))
        case a <> t:
          False{}
    case Core.EVar{x}:
      True{}
    case Core.ENum{n}:
      True{}
    case Core.ENat{n}:
      True{}
    case Core.EFlt{f}:
      True{}
    case other:
      False{}

def RC.tmp.fields(+g: G, as: List<&2, Core.Expr>) -> Bool:
  match as:
    case Nil{}:
      True{}
    case a <> t:
      Bool.and(RC.tmp.field(g, a), RC.tmp.fields(g, t))

def RC.tmp.node(m: Maybe<&2, CInfo>) -> Bool:
  match m:
    case None{}:
      False{}
    case Some{CInfo{tag, ar, +kind, single}}:
      U32.is_zero(kind)

def RC.tmp.size(+k: Nat) -> Bool:
  Bool.and(Nat.is_ge(k, 1n), Nat.is_le(k, 8n))

# A constructor that can be a temporary node.
def RC.tmp.syn(+g: G, e: Core.Expr) -> Bool:
  match e:
    case Core.ECtor{+n, +as}:
      Bool.and(Bool.and(RC.tmp.size(List.length(&2, Core.Expr, as)), RC.tmp.fields(g, as)), RC.tmp.node(G.ctor(g, n)))
    case other:
      False{}

def RC.tmp.is(e: Core.Expr) -> Bool:
  match e:
    case Core.ECtor{+n, as}:
      String.starts_with(n, "%tmp")
    case other:
      False{}

# A field of a temporary, by its C name (tail: a loop's, read out of a node).
def RC.tmp.c(tail: Bool, m: Maybe<&2, String>) -> Bool:
  match m:
    case Some{+c}:
      Bool.or(Bool.or(Str.eq(c, "0"), Gen.scalar.c(c)),
        Bool.and(RC.bor(c), Bool.or(Bool.not(tail), String.starts_with(c, "FLD("))))
    case None{}:
      False{}

def RC.tmp.env(+env: Env(), +tail: Bool, as: List<&2, Core.Expr>) -> Bool:
  match as:
    case Nil{}:
      True{}
    case Core.EVar{+x} <> t:
      Bool.and(RC.tmp.c(tail, Env.find(env, x)), RC.tmp.env(env, tail, t))
    case a <> t:
      RC.tmp.env(env, tail, t)

# The inner constructor's fields are all borrowed (a marked argument).
def RC.tmp.ok(+env: Env(), tail: Bool, as: List<&2, Core.Expr>) -> Bool:
  match as:
    case Core.ECtor{n, bs} <> Nil{}:
      RC.tmp.env(env, tail, bs)
    case other:
      False{}

# The references a marked argument built on the heap takes.
def RC.tmp.dup(m: Maybe<&2, String>) -> String:
  match m:
    case Some{+c}:
      Bool.pick(String, RC.bor(c), "rc_bdup(" ++ c ++ "); ", "")
    case None{}:
      ""

def RC.tmp.dups(+env: Env(), as: List<&2, Core.Expr>) -> String:
  match as:
    case Nil{}:
      ""
    case Core.EVar{+x} <> t:
      RC.tmp.dup(Env.find(env, x)) ++ RC.tmp.dups(env, t)
    case a <> t:
      RC.tmp.dups(env, t)

def RC.tmp.mark1(hit: Bool, a: Core.Expr) -> Core.Expr:
  match hit:
    case True{}:
      Core.ECtor{"%tmp", [a]}
    case False{}:
      a

# A full call's arguments, marked where the def borrows (fl, by parameter).
def RC.tmp.mark(+g: G, mask: List<&2, Bool>, +fl: List<&2, Bool>, args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match mask args:
    case Nil{} xs:
      xs
    case m <> mt Nil{}:
      Nil{}
    case True{} <> mt +a <> at:
      RC.tmp.mark1(Bool.and(Bor.head(fl), RC.tmp.syn(g, a)), a) <> RC.tmp.mark(g, mt, Bor.tail(fl), at)
    case False{} <> mt a <> at:
      a <> RC.tmp.mark(g, mt, Bor.tail(fl), at)

def RC.tmp.args(e: Core.Expr) -> List<&2, Core.Expr>:
  match e:
    case Core.ECtor{n, as}:
      as
    case other:
      Nil{}

def RC.tmp.call.pick(hit: Bool, +g: G, +h: String, args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match hit:
    case True{}:
      RC.tmp.mark(g, DInfo.mask(G.def(g, h)), Bor.list(Bor.flags(g, h)), args)
    case False{}:
      args

def RC.tmp.call(+g: G, +loc: List<&2, String>, f: Core.Expr, +args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match f:
    case Core.EVar{+h}:
      RC.tmp.call.pick(Bool.and(Bool.and(Bool.not(Str.has(loc, h)), Bor.any(Bor.list(Bor.flags(g, h)))),
        Nat.is_eq(List.length(&2, Bool, DInfo.mask(G.def(g, h))), List.length(&2, Core.Expr, args))), g, h, args)
    case other:
      args

def RC.tmp.par(p: Core.Pat) -> Bool:
  match p:
    case Core.PCtor{+n, as}:
      Str.eq(n, "%par")
    case other:
      False{}

# e with its temporaries marked (loc: the local names).
def RC.tmp.pass(n: Nat, +g: G, +loc: List<&2, String>, e: Core.Expr) -> Core.Expr:
  match n:
    case 0n:
      e
    case 1n+ +m:
      match e:
        case Core.ECall{+f, args}:
          Core.ECall{f, RC.tmp.args(RC.tmp.pass(m, g, loc, Core.ECtor{"", RC.tmp.call(g, loc, f, args)}))}
        case Core.ECtor{+c, args}:
          match args:
            case Nil{}:
              Core.ECtor{c, Nil{}}
            case a <> t:
              Core.ECtor{c, RC.tmp.pass(m, g, loc, a) <> RC.tmp.args(RC.tmp.pass(m, g, loc, Core.ECtor{c, t}))}
        case Core.ELet{+p, +v, b}:
          Core.ELet{p, Bool.pick(Core.Expr, RC.tmp.par(p), v, RC.tmp.pass(m, g, loc, v)),
            RC.tmp.pass(m, g, Pat.vars(p, loc), b)}
        case Core.EMatch{scrs, cases}:
          Core.EMatch{RC.tmp.args(RC.tmp.pass(m, g, loc, Core.ECtor{"", scrs})),
            RC.tmp.args(RC.tmp.pass(m, g, loc, Core.ECtor{"", cases}))}
        case Core.ECase{+ps, b}:
          Core.ECase{ps, RC.tmp.pass(m, g, Pats.vars(ps, loc), b)}
        case Core.ESucc{k, x}:
          Core.ESucc{k, RC.tmp.pass(m, g, loc, x)}
        case Core.EOp{op, a, b}:
          Core.EOp{op, RC.tmp.pass(m, g, loc, a), RC.tmp.pass(m, g, loc, b)}
        case Core.EAnn{x, t}:
          Core.EAnn{RC.tmp.pass(m, g, loc, x), t}
        case other:
          other

# A def's body, its temporaries marked when it counts references.
def RC.tmp.body(rc: Bool, +g: G, +loc: List<&2, String>, e: Core.Expr) -> Core.Expr:
  match rc:
    case True{}:
      RC.tmp.pass(Fuel.max(), g, loc, e)
    case False{}:
      e

# The buffers of a loop's temporaries, one pair for each parameter it
# borrows (fl), and which of the two is the last one written.
def RC.tmp.decl(fl: List<&2, Bool>, +used: List<&2, String>, +i: U32) -> String:
  match fl:
    case Nil{}:
      ""
    case b <> t:
      Bool.pick(String, Bool.and(b, Str.has(used, U32.show(i))),
        "V tb" ++ U32.show(i) ++ "[2][9]; unsigned tbi" ++ U32.show(i) ++ " = 0; ", "") ++
        RC.tmp.decl(t, used, U32.inc(i))

def RC.tmp.add(hit: Bool, +x: String, acc: List<&2, String>) -> List<&2, String>:
  match hit:
    case True{}:
      x <> acc
    case False{}:
      acc

# The (kept) positions of a call to the def itself that get a temporary.
def RC.tmp.idx(mask: List<&2, Bool>, args: List<&2, Core.Expr>, +k: U32, acc: List<&2, String>) -> List<&2, String>:
  match mask args:
    case True{} <> mt a <> at:
      RC.tmp.idx(mt, at, U32.inc(k), RC.tmp.add(RC.tmp.is(a), U32.show(k), acc))
    case False{} <> mt a <> at:
      RC.tmp.idx(mt, at, k, acc)
    case ml al:
      acc

def RC.tmp.selfc.go(hit: Bool, +mask: List<&2, Bool>, +args: List<&2, Core.Expr>, acc: List<&2, String>) ->
  List<&2, String>:
  match hit:
    case True{}:
      RC.tmp.idx(mask, args, 0, acc)
    case False{}:
      acc

def RC.tmp.selfc(+self: String, +mask: List<&2, Bool>, f: Core.Expr, +args: List<&2, Core.Expr>,
  acc: List<&2, String>) -> List<&2, String>:
  match f:
    case Core.EVar{+h}:
      RC.tmp.selfc.go(Str.eq(h, self), mask, args, acc)
    case other:
      acc

# The positions whose loop buffers a def's body (its temporaries marked)
# uses.
def RC.tmp.used(n: Nat, +self: String, +mask: List<&2, Bool>, e: Core.Expr, acc: List<&2, String>) -> List<&2, String>:
  match n:
    case 0n:
      acc
    case 1n+ +m:
      match e:
        case Core.ECall{+f, +args}:
          RC.tmp.used(m, self, mask, Core.ECtor{"", args}, RC.tmp.selfc(self, mask, f, args, acc))
        case Core.ECtor{+c, args}:
          match args:
            case Nil{}:
              acc
            case a <> t:
              RC.tmp.used(m, self, mask, Core.ECtor{c, t}, RC.tmp.used(m, self, mask, a, acc))
        case Core.ELet{p, v, b}:
          RC.tmp.used(m, self, mask, b, RC.tmp.used(m, self, mask, v, acc))
        case Core.EMatch{scrs, cases}:
          RC.tmp.used(m, self, mask, Core.ECtor{"", cases}, RC.tmp.used(m, self, mask, Core.ECtor{"", scrs}, acc))
        case Core.ECase{ps, b}:
          RC.tmp.used(m, self, mask, b, acc)
        case Core.ESucc{k, x}:
          RC.tmp.used(m, self, mask, x, acc)
        case Core.EOp{op, a, b}:
          RC.tmp.used(m, self, mask, b, RC.tmp.used(m, self, mask, a, acc))
        case Core.EAnn{x, t}:
          RC.tmp.used(m, self, mask, x, acc)
        case other:
          acc

def RC.tmp.tag(m: Maybe<&2, CInfo>) -> U32:
  match m:
    case None{}:
      0
    case Some{CInfo{tag, ar, kind, single}}:
      tag

def RC.tmp.doc(+tb: String, +tag: U32, ds: List<&2, Doc>) -> Doc:
  Doc.list([DStr{Bool.pick(String, String.is_empty(tb), "RC_TMP(", "RC_TB(tb" ++ tb ++ ", tbi" ++ tb ++ ", ") ++
    U32.show(tag) ++ ", "}, Gen.commas(ds), DStr{")"}])

def RC.tmp.tail1(a: Core.Expr, +i: U32) -> Core.Expr:
  match a:
    case Core.ECtor{+n, as}:
      Core.ECtor{Bool.pick(String, Str.eq(n, "%tmp"), "%tmp" ++ U32.show(i), n), as}
    case other:
      other

# A loop's next arguments, a marked one tagged with its parameter.
def RC.tmp.tail(as: List<&2, Core.Expr>, +i: U32) -> List<&2, Core.Expr>:
  match as:
    case Nil{}:
      Nil{}
    case a <> t:
      RC.tmp.tail1(a, i) <> RC.tmp.tail(t, U32.inc(i))

# The arguments of a call to a def that are evaluated: those its mask keeps
# (and any past it), but for a borrowed x (b), itself where the def borrows
# it (fl: the def's flags), and any temporary (whose variables are borrowed,
# or get their reference where it is built).
def RC.kept(mask: List<&2, Bool>, +fl: List<&2, Bool>, +x: String, args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match mask args:
    case Nil{} xs:
      xs
    case m <> mt Nil{}:
      Nil{}
    case True{} <> mt +a <> at:
      RC.kept.one(Bool.and(Bor.head(fl), Bool.or(Expr.is_var(a, x), RC.tmp.is(a))), a, RC.kept(mt, Bor.tail(fl), x, at))
    case False{} <> mt a <> at:
      RC.kept(mt, Bor.tail(fl), x, at)

def RC.global(info: DInfo, +fl: List<&2, Bool>, +x: String, args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  DInfo{+kind, mask} = info
  Bool.pick(List<&2, Core.Expr>, U32.is_eq(kind, 3), Nil{}, RC.kept(mask, fl, x, args))

def RC.fl(b: Bool, +g: G, +h: String) -> List<&2, Bool>:
  match b:
    case True{}:
      Bor.list(Bor.flags(g, h))
    case False{}:
      Nil{}

# A call's arguments where its def borrows them: a borrowed variable (or a
# number) is passed as it is; any other value is bound first and dropped
# after the call.
type RcW is Data:
  RcW{args: List<&2, Doc>, pre: Doc, post: Doc, any: Bool}

def RC.owned.c(m: Maybe<&2, String>) -> Bool:
  match m:
    case Some{+c}:
      Bool.not(Bool.or(Bool.or(Str.eq(c, "0"), Gen.scalar.c(c)), RC.bor(c)))
    case None{}:
      True{}

def RC.owned.arg(+env: Env(), e: Core.Expr) -> Bool:
  match e:
    case Core.EVar{+x}:
      RC.owned.c(Env.find(env, x))
    case Core.ENum{n}:
      False{}
    case Core.ENat{n}:
      False{}
    case Core.EFlt{f}:
      False{}
    case Core.EStr{t}:
      False{}
    case Core.ETy{n, a}:
      False{}
    case Core.ECtor{+n, as}:
      Bool.not(Bool.and(String.starts_with(n, "%tmp"), RC.tmp.ok(env, False{}, as)))
    case other:
      True{}

def RC.wrap.one(w: Bool, d: Doc, +k: U32, +i: U32, r: RcW) -> RcW:
  match w:
    case False{}:
      RcW{args, pre, post, any} = r
      RcW{List.append(&2, Doc, args, [d]), pre, post, any}
    case True{}:
      RcW{args, pre, post, any} = r
      +b = "b" ++ U32.show(k) ++ "_" ++ U32.show(i)
      RcW{List.append(&2, Doc, args, [DStr{b}]), Doc.list([pre, DStr{"V " ++ b ++ " = "}, d, DStr{"; "}]),
        Doc.list([post, DStr{"rc_drop(" ++ b ++ "); "}]), True{}}

def RC.wrap.go(kept: List<&2, Core.Expr>, ks: List<&2, Doc>, +fl: List<&2, Bool>, +env: Env(), +k: U32, +i: U32,
  r: RcW) -> RcW:
  match kept ks:
    case a <> at d <> dt:
      RC.wrap.go(at, dt, Bor.tail(fl), env, k, U32.inc(i),
        RC.wrap.one(Bool.and(Bor.head(fl), RC.owned.arg(env, a)), d, k, i, r))
    case al dl:
      r

def RC.wrap.call(+k: U32, +call: Doc, any: Bool, +pre: Doc, +post: Doc) -> Doc:
  Bool.pick(Doc, any, Doc.list([DStr{"({ "}, pre, DStr{"V r" ++ U32.show(k) ++ " = "}, call, DStr{"; "}, post,
    DStr{"r" ++ U32.show(k) ++ "; })"}]), call)

def RC.wrap(+k: U32, +name: String, xs: List<&2, Doc>, r: RcW) -> Doc:
  RcW{args, pre, post, any} = r
  RC.wrap.call(k, Gen.apply(xs, Doc.list([DStr{Gen.f(name) ++ "("}, Gen.commas(args), DStr{")"}])), any, pre, post)

# The call of a flat result's U_ function, its fields stored through o.
def RC.wrap.u(+k: U32, +name: String, +o: String, r: RcW) -> Doc:
  RcW{args, pre, post, any} = r
  RC.wrap.call(k, Doc.list([DStr{"U_" ++ Gen.mangle(name) ++ "("}, Gen.commas(List.append(&2, Doc, args, [DStr{o}])),
    DStr{")"}]), any, pre, post)

def RC.call.args(+g: G, +loc: List<&2, String>, +b: Bool, +x: String, +h: String, +args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  Bool.pick(List<&2, Core.Expr>, Str.has(loc, h), Core.EVar{h} <> args, RC.global(G.def(g, h), RC.fl(b, g, h), x, args))

def RC.view.gpu(args: List<&2, Core.Expr>) -> Core.Expr:
  match args:
    case Nil{}:
      Core.ENum{0}
    case h <> t:
      Core.ECtor{"", [Core.ECall{h, t}]}

def RC.view.named(+g: G, +loc: List<&2, String>, +b: Bool, +x: String, +h: String, +args: List<&2, Core.Expr>, gpu: Bool) -> Core.Expr:
  match gpu:
    case True{}:
      RC.view.gpu(args)
    case False{}:
      Core.ECtor{"", RC.call.args(g, loc, b, x, h, args)}

def RC.view.call(+g: G, +loc: List<&2, String>, +b: Bool, +x: String, f: Core.Expr, +args: List<&2, Core.Expr>) -> Core.Expr:
  match f:
    case Core.EVar{+h}:
      RC.view.named(g, loc, b, x, h, args, Str.eq(h, "%gpu"))
    case other:
      Core.ECtor{"", other <> args}

def RC.view.let(shadow: Bool, p: Core.Pat, v: Core.Expr, b: Core.Expr) -> Core.Expr:
  match shadow:
    case True{}:
      Core.ECtor{"", [v]}
    case False{}:
      Core.ELet{p, v, b}

def RC.view.case(shadow: Bool, ps: List<&2, Core.Pat>, b: Core.Expr) -> Core.Expr:
  match shadow:
    case True{}:
      Core.ENum{0}
    case False{}:
      Core.ECase{ps, b}

# e, one level down, for counting x's uses (RC.uses.v): ENum{k}, k uses;
# ECtor, the sum of its fields'; ELet, ECase and EMatch (whose cases count
# their most), which bind names; what the generated code evaluates only.
# A borrowed x (b) is not used where a call borrows it.
def RC.view(+g: G, +loc: List<&2, String>, +b: Bool, +x: String, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.EVar{+y}:
      Core.ENum{Bool.pick(U32, Str.eq(y, x), 1, 0)}
    case Core.ECall{f, +args}:
      RC.view.call(g, loc, b, x, f, args)
    case Core.ECtor{n, args}:
      Core.ECtor{"", args}
    case Core.ELam{+p, +bd}:
      Core.ENum{Bool.pick(U32, Str.has(FV.expr(bd, Pat.vars(p, Nil{}), Nil{}), x), 1, 0)}
    case Core.ELet{+p, v, bd}:
      RC.view.let(Str.has(Pat.vars(p, Nil{}), x), p, v, bd)
    case Core.EMatch{scrs, cases}:
      Core.EMatch{scrs, cases}
    case Core.ECase{+ps, bd}:
      RC.view.case(Str.has(Pats.vars(ps, Nil{}), x), ps, bd)
    case Core.ESucc{k, y}:
      Core.ECtor{"", [y]}
    case Core.EOp{op, a, bd}:
      Core.ECtor{"", [a, bd]}
    case Core.EAnn{y, t}:
      Core.ECtor{"", [y]}
    case other:
      Core.ENum{0}

# A match's scrutinee: a borrowed x matched is not used.
def RC.view.scr(+g: G, +loc: List<&2, String>, b: Bool, +x: String, +e: Core.Expr) -> Core.Expr:
  match b:
    case True{}:
      Bool.pick(Core.Expr, Expr.is_var(e, x), Core.ENum{0}, RC.view(g, loc, True{}, x, e))
    case False{}:
      RC.view(g, loc, False{}, x, e)

# The most uses of a match's cases (the least for a borrowed variable, b:
# a case that uses one more takes the references there).
def RC.most(b: Bool, +u: U32, +v: U32) -> U32:
  match b:
    case True{}:
      U32.min(u, v)
    case False{}:
      U32.max(u, v)

def RC.uses.v(n: Nat, +g: G, +loc: List<&2, String>, +b: Bool, +x: String, e: Core.Expr) -> U32:
  match n:
    case 0n:
      0
    case 1n+ +m:
      match e:
        case Core.ENum{k}:
          k
        case Core.ECtor{c, args}:
          match args:
            case Nil{}:
              0
            case a <> t:
              (RC.uses.v(m, g, loc, b, x, RC.view(g, loc, b, x, a)) + RC.uses.v(m, g, loc, b, x, Core.ECtor{c, t}) : U32)
        case Core.ELet{+p, v, bd}:
          (RC.uses.v(m, g, loc, b, x, RC.view(g, loc, b, x, v)) +
            RC.uses.v(m, g, Pat.vars(p, loc), b, x, RC.view(g, Pat.vars(p, loc), b, x, bd)) : U32)
        case Core.EMatch{scrs, cases}:
          match scrs:
            case a <> t:
              (RC.uses.v(m, g, loc, b, x, RC.view.scr(g, loc, b, x, a)) + RC.uses.v(m, g, loc, b, x, Core.EMatch{t, cases}) : U32)
            case Nil{}:
              match cases:
                case Nil{}:
                  0
                case c <> t:
                  match t:
                    case Nil{}:
                      RC.uses.v(m, g, loc, b, x, RC.view(g, loc, b, x, c))
                    case t2:
                      RC.most(b, RC.uses.v(m, g, loc, b, x, RC.view(g, loc, b, x, c)), RC.uses.v(m, g, loc, b, x, Core.EMatch{Nil{}, t2}))
        case Core.ECase{+ps, bd}:
          RC.uses.v(m, g, Pats.vars(ps, loc), b, x, RC.view(g, Pats.vars(ps, loc), b, x, bd))
        case other:
          0

# The uses of x on the path through e that uses it most (loc: the local
# names, whose calls pass every argument; b: x is borrowed).
def RC.uses(+g: G, +loc: List<&2, String>, +b: Bool, +x: String, e: Core.Expr) -> U32:
  RC.uses.v(Fuel.max(), g, loc, b, x, RC.view(g, loc, b, x, e))

# Numbers, characters and erased values are not counted.
def RC.skip(+c: String) -> Bool:
  Bool.or(Str.eq(c, "0"), Gen.scalar.c(c))

def RC.op(+c: String, +u: U32) -> Doc:
  Bool.pick(Doc, U32.is_zero(u), DStr{"rc_drop(" ++ c ++ ");\n"},
    Bool.pick(Doc, U32.is_le(u, 1), DNil{}, DStr{"rc_dupn(" ++ c ++ ", " ++ U32.show((u - 1 : U32)) ++ ");\n"}))

# A borrowed value gets a reference for each use (none is dropped), with
# rc_bdupFLD for one read out of a borrowed node and rc_bdup for any other
# (its own mark says whether other threads reach it: see RC_TS).
def RC.bdup(+c: String, n: Nat) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "rc_bdup" ++ Bool.pick(String, String.starts_with(c, "FLD("), c, "(" ++ c ++ ")") ++ ";\n" ++ RC.bdup(c, m)

def RC.bind.pick(bor: Bool, +g: G, +loc: List<&2, String>, +x: String, +c: String, +body: Core.Expr) -> Doc:
  match bor:
    case True{}:
      DStr{RC.bdup(c, U32.to_nat(RC.uses(g, loc, True{}, x, body)))}
    case False{}:
      RC.op(c, RC.uses(g, loc, False{}, x, body))

def RC.bind(skip: Bool, +g: G, +loc: List<&2, String>, +x: String, +c: String, +body: Core.Expr) -> Doc:
  match skip:
    case True{}:
      DNil{}
    case False{}:
      RC.bind.pick(RC.bor(c), g, loc, x, c, body)

def RC.binds(+g: G, +loc: List<&2, String>, binds: Env(), +body: Core.Expr) -> Doc:
  match binds:
    case Nil{}:
      DNil{}
    case Bind{+x, +c} <> t:
      Doc.list([RC.bind(RC.skip(c), g, loc, x, c, body), RC.binds(g, loc, t, body)])

def Gen.own.pick(rc: Bool, +g: G, +scope: Env(), binds: Env(), +body: Core.Expr) -> Doc:
  match rc:
    case True{}:
      RC.binds(g, Env.names(scope), binds, body)
    case False{}:
      Gen.shares.g(g, binds, body)

# What variables bound where body starts get: references (counted) or a
# shared mark (see Gen.shares); scope is every name bound there.
def Gen.own(+g: G, +scope: Env(), binds: Env(), +body: Core.Expr) -> Doc:
  Gen.own.pick(Gen.rc(g), g, scope, binds, body)

# An outer variable a match's cases use: its C name and the most uses of a
# case.
type RcM is Data:
  RcM{x: String, c: String, m: U32}

def RC.mx.keep(skip: Bool, r: RcM, rest: List<&2, RcM>) -> List<&2, RcM>:
  match skip:
    case True{}:
      rest
    case False{}:
      r <> rest

def RC.mx.put(m: Maybe<&2, String>, +g: G, +loc: List<&2, String>, +x: String, +all: Core.Expr,
  rest: List<&2, RcM>) -> List<&2, RcM>:
  match m:
    case None{}:
      rest
    case Some{+c}:
      RC.mx.keep(RC.skip(c), RcM{x, c, RC.uses(g, loc, RC.bor(c), x, all)}, rest)

def RC.mx.vars(+g: G, +loc: List<&2, String>, +env: Env(), xs: List<&2, String>, +all: Core.Expr) -> List<&2, RcM>:
  match xs:
    case Nil{}:
      Nil{}
    case +x <> t:
      RC.mx.put(Env.find(env, x), g, loc, x, all, RC.mx.vars(g, loc, env, t, all))

# The outer variables e uses (counted).
def RC.mx(+g: G, +env: Env(), +e: Core.Expr) -> List<&2, RcM>:
  RC.mx.vars(g, Env.names(env), env, FV.expr(e, Nil{}, Nil{}), e)

# Traced (matches free what they open), the outer variables a match's cases
# use, for Dead.arm.
def Dead.put(m: Maybe<&2, String>, +x: String, rest: List<&2, RcM>) -> List<&2, RcM>:
  match m:
    case None{}:
      rest
    case Some{+c}:
      RC.mx.keep(RC.skip(c), RcM{x, c, 1}, rest)

def Dead.vars(+env: Env(), xs: List<&2, String>) -> List<&2, RcM>:
  match xs:
    case Nil{}:
      Nil{}
    case +x <> t:
      Dead.put(Env.find(env, x), x, Dead.vars(env, t))

def Dead.mx(free: Bool, +env: Env(), cases: List<&2, Core.Expr>) -> List<&2, RcM>:
  match free:
    case True{}:
      Dead.vars(env, FV.expr(Core.EMatch{Nil{}, cases}, Nil{}, Nil{}))
    case False{}:
      Nil{}

def RC.mx.if(rc: Bool, +g: G, +env: Env(), cases: List<&2, Core.Expr>) -> List<&2, RcM>:
  match rc:
    case True{}:
      RC.mx(g, env, Core.EMatch{Nil{}, cases})
    case False{}:
      Dead.mx(Gen.free(g), env, cases)

def RC.dropn(+c: String, +n: U32) -> Doc:
  Bool.pick(Doc, U32.is_zero(n), DNil{}, DStr{"rc_dropn(" ++ c ++ ", " ++ U32.show(n) ++ ");\n"})

def RC.arm.one(bor: Bool, +cn: String, +m: U32, +u: U32) -> Doc:
  match bor:
    case True{}:
      DStr{RC.bdup(cn, U32.to_nat((u - m : U32)))}
    case False{}:
      RC.dropn(cn, (m - u : U32))

# A case's drops: what its match's most using case uses of each outer
# variable, less its own uses; for a borrowed one, the references its own
# uses take past the least using case's.
def RC.arm(+g: G, +loc: List<&2, String>, mx: List<&2, RcM>, +c: Core.Expr) -> Doc:
  match mx:
    case Nil{}:
      DNil{}
    case RcM{+x, +cn, +m} <> t:
      Doc.list([RC.arm.one(RC.bor(cn), cn, m, RC.uses(g, loc, RC.bor(cn), x, c)), RC.arm(g, loc, t, c)])

# Traced, a case's bend_dead for each outer variable another case of its
# match uses and it does not.
def Dead.arm(mx: List<&2, RcM>, +c: Core.Expr) -> Doc:
  match mx:
    case Nil{}:
      DNil{}
    case RcM{+x, +cn, m} <> t:
      Doc.list([Bool.pick(Doc, U32.is_zero(Use.n(x, c)), DStr{"bend_dead(" ++ cn ++ ");\n"}, DNil{}), Dead.arm(t, c)])

def RC.arm.pick(rc: Bool, +g: G, +loc: List<&2, String>, mx: List<&2, RcM>, +c: Core.Expr) -> Doc:
  match rc:
    case True{}:
      RC.arm(g, loc, mx, c)
    case False{}:
      Dead.arm(mx, c)

# A forked value's closure takes one reference of each variable it
# captures: it had its uses (the in-order path evaluates it in place).
def RC.fork.one(+c: String, +u: U32) -> Doc:
  Bool.pick(Doc, U32.is_zero(u), DStr{"rc_dup(" ++ c ++ ");\n"}, RC.dropn(c, (u - 1 : U32)))

def RC.fork.go(mx: List<&2, RcM>) -> Doc:
  match mx:
    case Nil{}:
      DNil{}
    case RcM{x, +c, +m} <> t:
      Doc.list([RC.fork.one(c, m), RC.fork.go(t)])

def RC.fork(rc: Bool, +g: G, +env: Env(), +v: Core.Expr) -> Doc:
  match rc:
    case True{}:
      RC.fork.go(RC.mx(g, env, v))
    case False{}:
      DNil{}

# Counted, an opened ALeaf's cell gets a reference and each opened Array is
# dropped (its halves are copies).
def RC.arrs.go(binds: Env(), +kind: String, +op: String) -> Doc:
  match binds:
    case Nil{}:
      DNil{}
    case Bind{+x, +c} <> t:
      Doc.list([Bool.pick(Doc, Str.eq(x, kind), DStr{op ++ "(" ++ c ++ ");\n"}, DNil{}), RC.arrs.go(t, kind, op)])

def RC.arrs(rc: Bool, +binds: Env()) -> Doc:
  match rc:
    case True{}:
      Doc.list([RC.arrs.go(binds, "%leaf", "rc_dup_leaf"), RC.arrs.go(binds, "%arr", "rc_drop")])
    case False{}:
      DNil{}

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
def Gen.takes(binds: Env(), +kind: String, +fn: String) -> List<&2, String>:
  match binds:
    case Nil{}:
      Nil{}
    case Bind{+x, +c} <> t:
      Gen.takes.if(Str.eq(Gen.take.kind(x), kind), fn ++ "(" ++ c ++ ", " ++ Gen.take.words(x) ++ ")",
        Gen.takes(t, kind, fn))

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

# Reuse (counted programs): a node a case opens, when it had one reference,
# is not freed but kept as a token, its slot (rc_take_ru), for a constructor
# of its size built after it (CR2 and the like). The tokens in reach are the
# memo's "%ru", names u<words>_<node> joined by spaces. A token is for the
# code straight after its case: a nested match's cases each use or free
# (RUF) the tokens they get, and closures and parallel lets get none.
type RuT is Data:
  RuT{tok: String, c: String, w: String, k: String}

def RU.head(memo: List<&2, Bind>) -> String:
  match memo:
    case Nil{}:
      ""
    case Bind{+k, c} <> t:
      Bool.pick(String, Str.eq(k, "%ru"), c, "")

def RU.put.if(hit: Bool, k: String, c: String, t: List<&2, Bind>, v: String) -> List<&2, Bind>:
  match hit:
    case True{}:
      Bind{"%ru", v} <> t
    case False{}:
      Bind{"%ru", v} <> Bind{k, c} <> t

def RU.put(memo: List<&2, Bind>, v: String) -> List<&2, Bind>:
  match memo:
    case Nil{}:
      [Bind{"%ru", v}]
    case Bind{+k, c} <> t:
      RU.put.if(Str.eq(k, "%ru"), k, c, t, v)

def RU.keep.if(drop: Bool, h: String, rest: List<&2, String>) -> List<&2, String>:
  match drop:
    case True{}:
      rest
    case False{}:
      h <> rest

def RU.nonempty(xs: List<&2, String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case +h <> t:
      RU.keep.if(String.is_empty(h), h, RU.nonempty(t))

def RU.list(s: String) -> List<&2, String>:
  RU.nonempty(String.split(s, ' '))

def RU.minus(xs: List<&2, String>, +rm: List<&2, String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case +h <> t:
      RU.keep.if(Str.has(rm, h), h, RU.minus(t, rm))

def RU.first.if(hit: Bool, h: String, rest: String) -> String:
  match hit:
    case True{}:
      h
    case False{}:
      rest

def RU.first(xs: List<&2, String>, +pre: String) -> String:
  match xs:
    case Nil{}:
      ""
    case +h <> t:
      RU.first.if(String.starts_with(h, pre), h, RU.first(t, pre))

def Gen.ru.get.go(st: St) -> String & St:
  St{n, protos, code, refs, errs, +memo, effs} = st
  (RU.head(memo), St{n, protos, code, refs, errs, memo, effs})

# The tokens in reach ("" when the program is not counted).
def Gen.ru.get(rc: Bool) -> Gen(String):
  match rc:
    case True{}:
      st => Gen.ru.get.go(st)
    case False{}:
      Gen.pure(String, "")

def Gen.ru.set.go(v: String, st: St) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, RU.put(memo, v), effs})

def Gen.ru.set(rc: Bool, v: String) -> Gen(Unit):
  match rc:
    case True{}:
      st => Gen.ru.set.go(v, st)
    case False{}:
      Gen.pure(Unit, Unit{})

def Gen.ru.take.go(+w: U32, st: St) -> String & St:
  St{n, protos, code, refs, errs, +memo, effs} = st
  +ts = RU.list(RU.head(memo))
  +tok = RU.first(ts, "u" ++ U32.show(w) ++ "_")
  (tok, St{n, protos, code, refs, errs, RU.put(memo, String.join(RU.minus(ts, [tok]), " ")), effs})

# A token for a node of w words, used up ("" when none is in reach).
def Gen.ru.take(ok: Bool, +w: U32) -> Gen(String):
  match ok:
    case True{}:
      st => Gen.ru.take.go(w, st)
    case False{}:
      Gen.pure(String, "")

def RU.toks.if(keep: Bool, r: RuT, rest: List<&2, RuT>) -> List<&2, RuT>:
  match keep:
    case True{}:
      r <> rest
    case False{}:
      rest

# Unused fields (counted): a case that leaves fields of a node it opens
# unused takes the node with them (rc_take_d: dropped with it when it had one
# reference, not given one when it was shared) instead of dropping each
# after it gave them one. dead: the paths (FLD(node, i)) of the pattern's
# variables the body does not use.
def RC.fld(+q: String, +i: U32) -> String:
  "FLD(" ++ q ++ ", " ++ U32.show(i) ++ ")"

def RC.dead.one(hit: Bool, +path: String, rest: List<&2, String>) -> List<&2, String>:
  match hit:
    case True{}:
      path <> rest
    case False{}:
      rest

def RC.dead(+g: G, +loc: List<&2, String>, +body: Core.Expr, pre: Env(), post: Env()) -> List<&2, String>:
  match pre post:
    case Bind{+x, +path} <> pt Bind{y, +c} <> qt:
      RC.dead.one(Bool.and(Bool.and(Bool.not(Gen.is_take(x)), String.starts_with(path, "FLD(")),
        Bool.and(Bool.not(RC.bor(c)), U32.is_zero(RC.uses(g, loc, False{}, x, body)))), path,
        RC.dead(g, loc, body, pt, qt))
    case pl ql:
      Nil{}

def RC.dead.if(rc: Bool, +g: G, +loc: List<&2, String>, +body: Core.Expr, +pre: Env(), +post: Env()) -> List<&2, String>:
  match rc:
    case True{}:
      RC.dead(g, loc, body, pre, post)
    case False{}:
      Nil{}

# The unused fields of node q among its first n: "|1u<<i" each.
def RC.dbits(+q: String, +dead: List<&2, String>, n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      Bool.pick(String, Str.has(dead, RC.fld(q, i)), "|1ull<<" ++ U32.show(i), "") ++ RC.dbits(q, dead, m, U32.inc(i))

# The unused fields of the nodes a pattern opens (which their takes drop).
def RC.hand.node(+q: String, +dead: List<&2, String>, n: Nat, +i: U32, acc: List<&2, String>) -> List<&2, String>:
  match n:
    case 0n:
      acc
    case 1n+m:
      RC.hand.node(q, dead, m, U32.inc(i), RC.dead.one(Str.has(dead, RC.fld(q, i)), RC.fld(q, i), acc))

def RC.hand.one(hit: Bool, +q: String, +dead: List<&2, String>, acc: List<&2, String>) -> List<&2, String>:
  match hit:
    case True{}:
      RC.hand.node(q, dead, 32n, 0, acc)
    case False{}:
      acc

def RC.hand.all(pre: Env(), +dead: List<&2, String>) -> List<&2, String>:
  match pre:
    case Nil{}:
      Nil{}
    case Bind{+x, +path} <> t:
      RC.hand.one(Gen.is_take(x), path, dead, RC.hand.all(t, dead))

def RC.hand(+pre: Env(), +dead: List<&2, String>) -> List<&2, String>:
  Bool.pick(Unit -> List<&2, String>, List.is_empty(&2, String, dead), u => Nil{}, u => RC.hand.all(pre, dead))(Unit{})

# The pattern's variables but the fields the takes drop (for Gen.own).
def RC.alive(pre: Env(), post: Env(), +hand: List<&2, String>) -> Env():
  match pre post:
    case Bind{+x, +path} <> pt Bind{+y, +c} <> qt:
      Gen.vars.if(Bool.or(Gen.is_take(x), Str.has(hand, path)), Bind{y, c}, RC.alive(pt, qt, hand))
    case pl ql:
      Nil{}

# The tokens of the nodes a pattern opens (kind "%top" or "%sub"; pre: the
# paths the bindings were loaded from).
def RU.toks(pre: Env(), binds: Env(), +kind: String, +dead: List<&2, String>) -> List<&2, RuT>:
  match pre binds:
    case Bind{px, +path} <> pt Bind{+x, +c} <> t:
      RU.toks.if(Str.eq(Gen.take.kind(x), kind), RuT{"u" ++ Gen.take.words(x) ++ "_" ++ c, c, Gen.take.words(x),
        Bool.pick(Unit -> String, List.is_empty(&2, String, dead), u => "", u => RC.dbits(path, dead, 32n, 0))(Unit{})},
        RU.toks(pt, t, kind, dead))
    case pl bl:
      Nil{}

def RU.names(ts: List<&2, RuT>) -> List<&2, String>:
  match ts:
    case Nil{}:
      Nil{}
    case RuT{tok, c, w, k} <> t:
      tok <> RU.names(t)

def RU.take(+tok: String, +c: String, +w: String, +k: String, keep: Bool) -> String:
  +d = Bool.pick(String, String.is_empty(k), "", "_d")
  +m = Bool.pick(String, String.is_empty(k), "", ", ~(0" ++ k ++ ")")
  Bool.pick(String, keep, "rc_take" ++ d ++ "(" ++ c ++ ", " ++ w ++ m ++ ");\n",
    "V " ++ tok ++ " = rc_take_ru" ++ d ++ "(" ++ c ++ ", " ++ w ++ m ++ ");\n")

# The takes of a case's nodes: a token used after them is kept (left: the
# tokens not used).
def RU.takes(ts: List<&2, RuT>, +left: List<&2, String>) -> Doc:
  match ts:
    case Nil{}:
      DNil{}
    case RuT{+tok, +c, +w, +k} <> t:
      Doc.list([DStr{RU.take(tok, c, w, k, Str.has(left, tok))}, RU.takes(t, left)])

def RU.takes.pick(rc: Bool, ts: List<&2, RuT>, +left: List<&2, String>, old: String) -> Doc:
  match rc:
    case True{}:
      RU.takes(ts, left)
    case False{}:
      DStr{old}

def RU.frees(ts: List<&2, String>) -> Doc:
  match ts:
    case Nil{}:
      DNil{}
    case +h <> t:
      Doc.list([DStr{"RUF(" ++ h ++ ");\n"}, RU.frees(t)])

# Whether a pattern opens a node.
def Gen.opens(binds: Env()) -> Bool:
  match binds:
    case Nil{}:
      False{}
    case Bind{x, c} <> t:
      Bool.or(Gen.is_take(x), Gen.opens(t))

# Whether a pattern splits an Array (its halves are copies, made once).
# A borrowed node is not taken (nor are the nodes in it).
def RC.bfilter(binds: Env()) -> Env():
  match binds:
    case Nil{}:
      Nil{}
    case Bind{+x, +c} <> t:
      Gen.vars.if(Bool.and(Gen.is_take(x), RC.bor(c)), Bind{x, c}, RC.bfilter(t))

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

def Gen.mat.put.go(bor: Bool, x: String, +m: String, +path: String, r: Env() & Doc) -> Env() & Doc:
  match bor:
    case True{}:
      (bs, d) = r
      (Bind{x, path} <> bs, d)
    case False{}:
      (bs, d) = r
      (Bind{x, m} <> bs, Doc.list([DStr{"V " ++ m ++ " = " ++ path ++ ";\n"}, d]))

# (a borrowed node's field is read where it is used: the node outlives the
# case)
def Gen.mat.put(x: String, +m: String, +path: String, r: Env() & Doc) -> Env() & Doc:
  Gen.mat.put.go(RC.bor(path), x, m, path, r)

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
def Gen.par.env(ps: List<&2, Core.Pat>, +k: U32, +i: U32, +env: Env()) -> Env():
  match ps:
    case Nil{}:
      env
    case Core.PVar{+x} <> t:
      Gen.par.env(t, k, U32.inc(i), Bool.pick(Env(), Str.eq(x, "_"), env,
        Bind{x, Gen.par.name(k, i)} <> env))
    case other <> t:
      Gen.par.env(t, k, U32.inc(i), env)

# Counted, a parallel let's _ is bound (as _%), to be dropped.
def RC.unders(+rc: Bool, ps: List<&2, Core.Pat>) -> List<&2, Core.Pat>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.PVar{+x} <> t:
      Core.PVar{Bool.pick(String, Bool.and(rc, Str.eq(x, "_")), "_%", x)} <> RC.unders(rc, t)
    case p <> t:
      p <> RC.unders(rc, t)

# 1: in S_name (in order); 3: elsewhere (forks, and, in a def with a
# sequential clone, only above the frontier).
def Gen.par.mode(m: Maybe<&2, String>, +sn: String) -> Nat:
  match m:
    case Some{+v}:
      Bool.pick(Nat, Str.eq(v, sn), 1n, 3n)
    case None{}:
      3n

# A parallel let of n values forks lg(n) levels deep: par_depth counts
# log2 of the tasks above, so the frontier (par_front) is 2^par_front tasks
# whatever the fan-out.
def Gen.par.lg(n: Nat) -> U32:
  match n:
    case 0n:
      1
    case 1n:
      1
    case 2n:
      1
    case 3n:
      2
    case 4n:
      2
    case 5n:
      3
    case 6n:
      3
    case 7n:
      3
    case 8n:
      3
    case 9n+m:
      4

# Past the frontier, a def with a sequential clone (S_name) calls it; any
# other def runs its parallel let's values in order (sn = "").
def Gen.par.def(+sn: String) -> String:
  Bool.pick(String, String.is_empty(sn), "", "#define " ++ Gen.f(sn) ++ " S_" ++ Gen.mangle(sn) ++ "\n")

def Gen.par.undef(+sn: String) -> String:
  Bool.pick(String, String.is_empty(sn), "", "#undef " ++ Gen.f(sn) ++ "\n")

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

def K.params(ps: List<&2, Core.Param>, mask: List<&2, Bool>) -> List<&2, String>:
  match ps mask:
    case Core.Param{x, m, t} <> pt True{} <> mt:
      x <> K.params(pt, mt)
    case Core.Param{x, m, t} <> pt False{} <> mt:
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

# Whether an analysis is the seq one (KSelf.entry 1, or 2 and 3 for the
# GPU's): see K.isseq.
def KSelf.seq(s: KSelf) -> Bool:
  KSelf{n, +e, m} = s
  Bool.and(U32.is_le(1, e), U32.is_le(e, 3))

# Whether the seq analysis takes a parallel let (not in mode 3: K.isseq1).
def KSelf.par(s: KSelf) -> Bool:
  KSelf{n, +e, m} = s
  Bool.or(U32.is_eq(e, 1), U32.is_eq(e, 2))

def K.pat.is_par(p: Core.Pat) -> Bool:
  match p:
    case Core.PCtor{+n, ps}:
      Str.eq(n, "%par")
    case other:
      False{}

# Whether v is a call of the def itself.
def K.fl.direct(+self: KSelf, +bound: List<&2, String>, v: Core.Expr) -> Bool:
  match v:
    case Core.ECall{Core.EVar{+f}, args}:
      Bool.and(Str.eq(f, KSelf.name(self)), Bool.not(Str.has(bound, f)))
    case other:
      False{}

# The seq view of a body (see K.isseq): a call of a def inside an expression
# (an argument or a field) becomes a let before its statement, and a parallel
# let lets its values one after the other, so a seq def calls defs at
# statement level only (where KQ_ code can call another seq def).
type AnfL is Data:
  AnfL{x: String, v: Core.Expr}

type Anf is Data:
  Anf{n: U32, ls: List<&2, AnfL>, e: Core.Expr}

type Anfs is Data:
  Anfs{n: U32, ls: List<&2, AnfL>, es: List<&2, Core.Expr>}

# The lets ls (the last made first) around body.
def Anf.wrap(ls: List<&2, AnfL>, body: Core.Expr) -> Core.Expr:
  match ls:
    case Nil{}:
      body
    case AnfL{x, v} <> t:
      Anf.wrap(t, Core.ELet{Core.PVar{x}, v, body})

def Anf.kind(i: DInfo) -> U32:
  DInfo{kind, mask} = i
  kind

# Whether a call of f is lifted: f a def, not a local.
def Anf.lifts(+g: G, +bound: List<&2, String>, +f: String) -> Bool:
  Bool.and(Bool.not(Str.has(bound, f)), U32.is_zero(Anf.kind(G.def(g, f))))

def Anf.call.lift(+f: String, r: Anfs) -> Anf:
  Anfs{+n, ls, es} = r
  +x = "%l" ++ U32.show(n)
  Anf{U32.inc(n), AnfL{x, Core.ECall{Core.EVar{f}, es}} <> ls, Core.EVar{x}}

def Anf.call.keep(+f: String, r: Anfs) -> Anf:
  Anfs{n, ls, es} = r
  Anf{n, ls, Core.ECall{Core.EVar{f}, es}}

def Anf.call(lift: Bool, +f: String, r: Anfs) -> Anf:
  match lift:
    case True{}:
      Anf.call.lift(f, r)
    case False{}:
      Anf.call.keep(f, r)

def Anf.ctor(name: String, r: Anfs) -> Anf:
  Anfs{n, ls, es} = r
  Anf{n, ls, Core.ECtor{name, es}}

def Anf.succ(k: U32, r: Anf) -> Anf:
  Anf{n, ls, e} = r
  Anf{n, ls, Core.ESucc{k, e}}

def Anf.cons(e: Core.Expr, r: Anfs) -> Anfs:
  Anfs{n, ls, es} = r
  Anfs{n, ls, e <> es}

def Anf.cons.stop(t: List<&2, Core.Expr>, r: Anf) -> Anfs:
  Anf{n, ls, e} = r
  Anfs{n, ls, e <> t}

def Anf.done(r: Anf) -> Anf:
  Anf{n, ls, e} = r
  Anf{n, Nil{}, Anf.wrap(ls, e)}

def Anf.let(ls: List<&2, AnfL>, p: Core.Pat, v: Core.Expr, r: Anf) -> Anf:
  Anf{n, l2, b} = r
  Anf{n, Nil{}, Anf.wrap(ls, Core.ELet{p, v, b})}

def Anf.let.stop(p: Core.Pat, b: Core.Expr, r: Anf) -> Anf:
  Anf{n, ls, v} = r
  Anf{n, Nil{}, Anf.wrap(ls, Core.ELet{p, v, b})}

def Anf.match(ls: List<&2, AnfL>, es: List<&2, Core.Expr>, r: Anfs) -> Anf:
  Anfs{n, l2, cs} = r
  Anf{n, Nil{}, Anf.wrap(ls, Core.EMatch{es, cs})}

def Anf.match.stop(cs: List<&2, Core.Expr>, r: Anfs) -> Anf:
  Anfs{n, ls, es} = r
  Anf{n, Nil{}, Anf.wrap(ls, Core.EMatch{es, cs})}

def Anf.case(ps: List<&2, Core.Pat>, b: Core.Expr, r: Anfs) -> Anfs:
  Anfs{n, ls, cs} = r
  Anfs{n, ls, Core.ECase{ps, b} <> cs}

def Anf.case.stop(ps: List<&2, Core.Pat>, t: List<&2, Core.Expr>, r: Anf) -> Anfs:
  Anf{n, ls, b} = r
  Anfs{n, Nil{}, Core.ECase{ps, b} <> t}

def Anf.par.lets(ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>, body: Core.Expr) -> Core.Expr:
  match ps vs:
    case p <> pt v <> vt:
      Core.ELet{p, v, Anf.par.lets(pt, vt, body)}
    case a b:
      body

def Anf.par.vals(v: Core.Expr) -> List<&2, Core.Expr>:
  match v:
    case Core.ECtor{n, vs}:
      vs
    case other:
      [other]

# A parallel let as lets (the seq view runs its values in order).
def Anf.par(p: Core.Pat, v: Core.Expr, b: Core.Expr) -> Core.Expr:
  match p:
    case Core.PCtor{n, ps}:
      Anf.par.lets(ps, Anf.par.vals(v), b)
    case other:
      Core.ELet{other, v, b}

# The lifting, one def (fuel: the expression's depth): AnfSel picks the step.
# top: the expression is a statement's own call (its args are lifted, not it).
type AnfSel is Type:
  ANEx{g: G, bound: List<&2, String>, e: Core.Expr, top: Bool, n: U32, ls: List<&2, AnfL>}
  ANCall{lift: Bool, f: String, r: Anfs}
  ANExs{g: G, bound: List<&2, String>, es: List<&2, Core.Expr>, top: Bool, n: U32, ls: List<&2, AnfL>}
  ANExsCons{g: G, bound: List<&2, String>, t: List<&2, Core.Expr>, top: Bool, r: Anf}
  ANSt{g: G, bound: List<&2, String>, e: Core.Expr, n: U32}
  ANStLet{par: Bool, g: G, bound: List<&2, String>, p: Core.Pat, v: Core.Expr, b: Core.Expr, n: U32}
  ANStLetGo{g: G, bound: List<&2, String>, p: Core.Pat, b: Core.Expr, r: Anf}
  ANStMatch{g: G, bound: List<&2, String>, r: Anfs, cases: List<&2, Core.Expr>}
  ANCases{g: G, bound: List<&2, String>, cs: List<&2, Core.Expr>, n: U32}
  ANCasesCons{g: G, bound: List<&2, String>, ps: List<&2, Core.Pat>, t: List<&2, Core.Expr>, r: Anf}
  ANExLets{g: G, bound: List<&2, String>, ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>, b: Core.Expr, top: Bool, n: U32,
      ls: List<&2, AnfL>}
  ANExPar{par: Bool, g: G, bound: List<&2, String>, k: String, ps: List<&2, Core.Pat>, v: Core.Expr, b: Core.Expr, top: Bool,
      n: U32, ls: List<&2, AnfL>}
  ANExLetsGo{g: G, bound: List<&2, String>, x: String, ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>, b: Core.Expr, top: Bool,
      r: Anf}

def AnfSel.ty(k: AnfSel) -> Type:
  match k:
    case ANExLets{g, bound, ps, vs, b, top, n, ls}:
      Anf
    case ANExPar{par, g, bound, k, ps, v, b, top, n, ls}:
      Anf
    case ANExLetsGo{g, bound, x, ps, vs, b, top, r}:
      Anf
    case ANEx{g, bound, e, top, n, ls}:
      Anf
    case ANCall{lift, f, r}:
      Anf
    case ANExs{g, bound, es, top, n, ls}:
      Anfs
    case ANExsCons{g, bound, t, top, r}:
      Anfs
    case ANSt{g, bound, e, n}:
      Anf
    case ANStLet{par, g, bound, p, v, b, n}:
      Anf
    case ANStLetGo{g, bound, p, b, r}:
      Anf
    case ANStMatch{g, bound, r, cases}:
      Anf
    case ANCases{g, bound, cs, n}:
      Anfs
    case ANCasesCons{g, bound, ps, t, r}:
      Anfs

def Anf.go(fuel: Nat, k: AnfSel) -> AnfSel.ty(k):
  match fuel:
    case 0n:
      match k:
        case ANEx{g, bound, e, top, n, ls}:
          Anf{n, ls, e}
        case ANCall{lift, f, r}:
          Anf.call.keep(f, r)
        case ANExs{g, bound, es, top, n, ls}:
          Anfs{n, ls, es}
        case ANExsCons{g, bound, t, top, r}:
          Anf.cons.stop(t, r)
        case ANSt{g, bound, e, n}:
          Anf{n, Nil{}, e}
        case ANStLet{par, g, bound, p, v, b, n}:
          Anf{n, Nil{}, Core.ELet{p, v, b}}
        case ANStLetGo{g, bound, p, b, r}:
          Anf.let.stop(p, b, r)
        case ANStMatch{g, bound, r, cases}:
          Anf.match.stop(cases, r)
        case ANCases{g, bound, cs, n}:
          Anfs{n, Nil{}, cs}
        case ANCasesCons{g, bound, ps, t, r}:
          Anf.case.stop(ps, t, r)
        case ANExLets{g, bound, ps, vs, b, top, n, ls}:
          Anf{n, ls, Anf.par.lets(ps, vs, b)}
        case ANExPar{par, g, bound, k, ps, v, b, top, n, ls}:
          Anf{n, ls, Core.ELet{Core.PCtor{k, ps}, v, b}}
        case ANExLetsGo{g, bound, x, ps, vs, b, top, r}:
          Anf{n, ls, e} = r
          Anf{n, ls, Core.ELet{Core.PVar{x}, e, Anf.par.lets(ps, vs, b)}}
    case Succ{+fu}:
      match k:
        # A parallel let inside an expression (implicit parallelism puts one
        # around an operator's calls): its values become lets before the
        # statement, one after the other; its names are fresh (Par.name).
        case ANExLets{+g, +bound, ps, vs, b, +top, n, ls}:
          match ps vs:
            case Core.PVar{+x} <> pt v <> vt:
              Anf.go(fu, ANExLetsGo{g, bound, x, pt, vt, b, top, Anf.go(fu, ANEx{g, bound, v, True{}, n, ls})})
            case Nil{} Nil{}:
              Anf.go(fu, ANEx{g, bound, b, top, n, ls})
            case pr vr:
              Anf{n, ls, Anf.par.lets(pr, vr, b)}
        case ANExPar{par, +g, +bound, k, ps, v, b, +top, n, ls}:
          match par:
            case True{}:
              Anf.go(fu, ANExLets{g, bound, ps, Anf.par.vals(v), b, top, n, ls})
            case False{}:
              Anf{n, ls, Core.ELet{Core.PCtor{k, ps}, v, b}}
        case ANExLetsGo{+g, +bound, +x, ps, vs, b, +top, r}:
          Anf{n, ls, e} = r
          Anf.go(fu, ANExLets{g, x <> bound, ps, vs, b, top, n, AnfL{x, e} <> ls})
        case ANEx{+g, +bound, e, top, n, ls}:
          match e:
            case Core.ECall{Core.EVar{+f}, args}:
              Anf.go(fu, ANCall{Bool.and(Bool.not(top), Anf.lifts(g, bound, f)), f, Anf.go(fu, ANExs{g, bound, args, False{}, n, ls})})
            case Core.ECtor{name, args}:
              Anf.ctor(name, Anf.go(fu, ANExs{g, bound, args, False{}, n, ls}))
            case Core.ESucc{j, x}:
              Anf.succ(j, Anf.go(fu, ANEx{g, bound, x, False{}, n, ls}))
            case Core.ELet{Core.PCtor{+k, ps}, v, b}:
              Anf.go(fu, ANExPar{Str.eq(k, "%par"), g, bound, k, ps, v, b, top, n, ls})
            case other:
              Anf{n, ls, other}
        case ANCall{lift, +f, r}:
          Anf.call(lift, f, r)
        case ANExs{+g, +bound, es, +top, n, ls}:
          match es:
            case Nil{}:
              Anfs{n, ls, Nil{}}
            case h <> t:
              Anf.go(fu, ANExsCons{g, bound, t, top, Anf.go(fu, ANEx{g, bound, h, top, n, ls})})
        case ANExsCons{+g, +bound, t, +top, r}:
          Anf{n, ls, e} = r
          Anf.cons(e, Anf.go(fu, ANExs{g, bound, t, top, n, ls}))
        case ANSt{+g, +bound, e, n}:
          match e:
            case Core.ELet{+p, v, b}:
              # (the analysis of mode 3 keeps parallel lets, to refuse them: K.isseq1)
              Anf.go(fu, ANStLet{Bool.and(K.pat.is_par(p), Bool.not(Str.has(bound, "%keeppar"))), g, bound, p, v, b, n})
            case Core.EMatch{scrs, cases}:
              Anf.go(fu, ANStMatch{g, bound, Anf.go(fu, ANExs{g, bound, scrs, False{}, n, Nil{}}), cases})
            case other:
              Anf.done(Anf.go(fu, ANEx{g, bound, other, True{}, n, Nil{}}))
        case ANStLet{par, +g, +bound, +p, v, b, n}:
          match par:
            case True{}:
              Anf.go(fu, ANSt{g, bound, Anf.par(p, v, b), n})
            case False{}:
              Anf.go(fu, ANStLetGo{g, bound, p, b, Anf.go(fu, ANEx{g, bound, v, True{}, n, Nil{}})})
        case ANStLetGo{+g, +bound, +p, b, r}:
          Anf{n, ls, v} = r
          Anf.let(ls, p, v, Anf.go(fu, ANSt{g, Pat.vars(p, bound), b, n}))
        case ANStMatch{+g, +bound, r, cases}:
          Anfs{n, ls, es} = r
          Anf.match(ls, es, Anf.go(fu, ANCases{g, bound, cases, n}))
        case ANCases{+g, +bound, cs, n}:
          match cs:
            case Nil{}:
              Anfs{n, Nil{}, Nil{}}
            case Core.ECase{+ps, body} <> t:
              Anf.go(fu, ANCasesCons{g, bound, ps, t, Anf.go(fu, ANSt{g, Pats.vars(ps, bound), body, n})})
            case other <> t:
              Anf.cons(other, Anf.go(fu, ANCases{g, bound, t, n}))
        case ANCasesCons{+g, +bound, ps, t, r}:
          Anf{n, ls, b} = r
          Anf.case(ps, b, Anf.go(fu, ANCases{g, bound, t, n}))

def Anf.expr(r: Anf) -> Core.Expr:
  Anf{n, ls, e} = r
  e

def KQ.anf(+g: G, bound: List<&2, String>, e: Core.Expr) -> Core.Expr:
  Anf.expr(Anf.go(Fuel.max(), ANSt{g, bound, e, 0}))

def KQ.anf.if(grp: Bool, +g: G, bound: List<&2, String>, e: Core.Expr) -> Core.Expr:
  match grp:
    case True{}:
      KQ.anf(g, bound, e)
    case False{}:
      e

def K.seq.key(+grp: U32, +name: String) -> String:
  "%seq" ++ U32.show(grp) ++ " " ++ name

# In the GPU's seq analysis (KSelf.entry 2) a seq def may call other seq
# defs: see K.isseq.
def KSelf.grp(s: KSelf) -> Bool:
  KSelf{n, +e, m} = s
  Bool.or(U32.is_eq(e, 2), U32.is_eq(e, 3))

# The mode a callee is analysed in (see FLSeqCall): mode 3 refuses the
# def's own parallel lets only (its callees run on its lane, a bounded
# number of steps: see K.call.seq.kq).
def KSelf.callee(s: KSelf) -> U32:
  KSelf{n, +e, m} = s
  Bool.pick(U32, U32.is_eq(e, 3), 2, e)

# Whether v calls a def (in the GPU's seq analysis a let's value may call
# any def at statement level: see FLFlCallDef).
def K.fl.gcall(+bound: List<&2, String>, v: Core.Expr) -> Bool:
  match v:
    case Core.ECall{Core.EVar{+f}, args}:
      Bool.not(Str.has(bound, f))
    case other:
      False{}

def K.fl.stmtcall(+self: KSelf, +bound: List<&2, String>, +v: Core.Expr) -> Bool:
  Bool.or(K.fl.direct(self, bound, v), Bool.and(KSelf.grp(self), K.fl.gcall(bound, v)))

# The flatness analysis, one def (fuel: its calls, which reach other defs):
# FlSel picks the step.
type FlSel is Type:
  FLFlExprs{g: G, self: KSelf, bound: List<&2, String>, es: List<&2, Core.Expr>}
  FLFlCases{g: G, self: KSelf, bound: List<&2, String>, cs: List<&2, Core.Expr>, tail: Bool}
  FLFlGlobalKind{g: G, self: KSelf, name: String, kind: Nat, mask: List<&2, Bool>}
  FLFlGlobal{g: G, self: KSelf, name: String, info: DInfo}
  FLFlVar{g: G, self: KSelf, bound: List<&2, String>, x: String}
  FLFlCallDef{g: G, self: KSelf, bound: List<&2, String>, f: String, kept: List<&2, Core.Expr>, tail: Bool, me: Bool}
  FLFlCallKind{kind: Nat, extra: List<&2, Core.Expr>, full: Bool, g: G, self: KSelf, bound: List<&2, String>, f: String,
      kept: List<&2, Core.Expr>, tail: Bool}
  FLFlCallSplit{g: G, self: KSelf, bound: List<&2, String>, f: String, kind: Nat, s: Split, tail: Bool}
  FLFlCallGlobal{g: G, self: KSelf, bound: List<&2, String>, f: String, args: List<&2, Core.Expr>, tail: Bool, info: DInfo}
  FLFlCall{g: G, self: KSelf, bound: List<&2, String>, f: String, args: List<&2, Core.Expr>, tail: Bool}
  FLFlParVals{g: G, self: KSelf, bound: List<&2, String>, vs: List<&2, Core.Expr>}
  FLFlLetPar{g: G, self: KSelf, bound: List<&2, String>, p: Core.Pat, v: Core.Expr, b: Core.Expr}
  FLFlLetGo{par: Bool, g: G, self: KSelf, bound: List<&2, String>, p: Core.Pat, v: Core.Expr, b: Core.Expr, tail: Bool}
  FLFlLet{g: G, self: KSelf, bound: List<&2, String>, p: Core.Pat, v: Core.Expr, b: Core.Expr, tail: Bool}
  FLFlExpr{g: G, self: KSelf, bound: List<&2, String>, e: Core.Expr, tail: Bool}
  FLFlDeclGo{kind: Nat, d: Decl, g: G, name: String, mask: List<&2, Bool>}
  FLFlDecl{g: G, name: String, info: DInfo, d: Decl}
  FLIsflatMemo{g: G, name: String, m: Maybe<&2, String>}
  FLIsflat{g: G, name: String}
  FLSeqCall{ok: Bool, mode: U32, g: G, f: String}
  FLSqDeclGo{grp: U32, kind: Nat, d: Decl, g: G, name: String, mask: List<&2, Bool>}
  FLSqDecl{grp: U32, g: G, name: String, info: DInfo, d: Decl}
  FLIsseqMemo{grp: U32, g: G, name: String, m: Maybe<&2, String>}
  FLIsseq{grp: U32, g: G, name: String}

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
    case FLSeqCall{ok, mode, g, f}:
      KM(Bool)
    case FLSqDeclGo{grp, kind, d, g, name, mask}:
      KM(Bool)
    case FLSqDecl{grp, g, name, info, d}:
      KM(Bool)
    case FLIsseqMemo{grp, g, name, m}:
      KM(Bool)
    case FLIsseq{grp, g, name}:
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
        case FLSeqCall{ok, mode, g, f}:
          K.out(Bool, False{})
        case FLSqDeclGo{grp, kind, d, g, name, mask}:
          K.out(Bool, False{})
        case FLSqDecl{grp, g, name, info, d}:
          K.out(Bool, False{})
        case FLIsseqMemo{grp, g, name, m}:
          K.out(Bool, False{})
        case FLIsseq{grp, g, name}:
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
            case Core.ECase{ps, body} <> t:
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
            # The GPU's seq analysis also takes a call of a seq def at statement level.
            case False{}:
              do KM<Bool>:
                +a : Bool <- K.fl.go(fu, FLIsflat{g, f})
                b : Bool <- K.fl.go(fu, FLSeqCall{Bool.and(Bool.and(KSelf.grp(self), tail), Bool.not(a)), KSelf.callee(self), g, f})
                K.fl.and(Bool.or(a, b), K.fl.go(fu, FLFlExprs{g, self, bound, kept}))
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
            case Core.ECtor{n, vs}:
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
              K.fl.and(Bool.and(KSelf.par(self), tail), K.fl.go(fu, FLFlLetPar{g, self, bound, p, v, b}))
            case False{}:
              do KM<Bool>:
                # In the seq analysis a let at statement level may call the def itself
                # (in the GPU's, another seq def too).
                a : Bool <- K.fl.go(fu, FLFlExpr{g, self, bound, v, Bool.and(Bool.and(KSelf.seq(self), tail), K.fl.stmtcall(self, bound,
                  v))})
                K.fl.and(a, K.fl.go(fu, FLFlExpr{g, self, Pat.vars(p, bound), b, tail}))
        case FLFlLet{+g, +self, +bound, +p, v, b, +tail}:
          K.fl.go(fu, FLFlLetGo{K.pat.is_par(p), g, self, bound, p, v, b, tail})
        case FLFlExpr{+g, +self, +bound, e, tail}:
          match e:
            case Core.EVar{+x}:
              K.fl.go(fu, FLFlVar{g, self, bound, x})
            case Core.ENum{n}:
              KM.pure(Bool, True{})
            case Core.ENat{n}:
              KM.pure(Bool, True{})
            case Core.EFlt{f}:
              KM.pure(Bool, True{})
            case Core.EStr{t}:
              KM.pure(Bool, True{})
            case Core.ETy{n, a}:
              KM.pure(Bool, True{})
            case Core.ESucc{k, x}:
              K.fl.go(fu, FLFlExpr{g, self, bound, x, False{}})
            case Core.ECtor{n, args}:
              K.fl.go(fu, FLFlExprs{g, self, bound, args})
            case Core.ELet{p, v, b}:
              K.fl.go(fu, FLFlLet{g, self, bound, p, v, b, tail})
            case Core.EMatch{scrs, cases}:
              do KM<Bool>:
                a : Bool <- K.fl.go(fu, FLFlExprs{g, self, bound, scrs})
                K.fl.and(a, K.fl.go(fu, FLFlCases{g, self, bound, cases, tail}))
            case Core.ECall{Core.EVar{+f}, args}:
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
        case FLSeqCall{ok, +mode, +g, +f}:
          match ok:
            case True{}:
              K.fl.go(fu, FLIsseq{mode, g, f})
            case False{}:
              KM.pure(Bool, False{})
        case FLSqDeclGo{+grp, kind, d, +g, +name, +mask}:
          match kind d:
            case 0n DDef{n, ps, body, ret}:
              +bound = K.params(ps, mask)
              +ab = Bool.pick(List<&2, String>, U32.is_eq(grp, 3), "%keeppar" <> bound, bound)
              K.fl.and(U32.is_le(K.kept(mask), 12), K.fl.go(fu, FLFlExpr{g, KSelf{name, grp, mask}, bound,
                KQ.anf.if(U32.is_le(2, grp), g, ab, R.ops(body, "Nat")), True{}}))
            case k o:
              KM.pure(Bool, False{})
        case FLSqDecl{grp, +g, +name, info, d}:
          DInfo{kind, mask} = info
          K.fl.go(fu, FLSqDeclGo{grp, U32.to_nat(kind), d, g, name, mask})
        case FLIsseqMemo{+grp, +g, +name, m}:
          match m:
            case Some{v}:
              KM.pure(Bool, Str.eq(v, "1"))
            case None{}:
              do KM<Bool>:
                # While it is analysed, a def reached again is in a cycle: not seq.
                K.memo.put(K.seq.key(grp, name), "0")
                +ok : Bool <- K.fl.go(fu, FLSqDecl{grp, g, name, G.def(g, name), G.body(g, name)})
                K.memo.put(K.seq.key(grp, name), Bool.pick(String, ok, "1", "0"))
                return ok
        case FLIsseq{+grp, +g, +name}:
          do KM<Bool>:
            m : Maybe<&2, String> <- K.memo.get(K.seq.key(grp, name))
            K.fl.go(fu, FLIsseqMemo{grp, g, name, m})

def K.fl.expr(g: G, self: KSelf, bound: List<&2, String>, e: Core.Expr, tail: Bool) -> KM(Bool):
  K.fl.go(Fuel.max(), FLFlExpr{g, self, bound, e, tail})

def K.isflat(g: G, name: String) -> KM(Bool):
  K.fl.go(Fuel.max(), FLIsflat{g, name})

# A def is seq when it would be flat if its parallel lets ran in order and
# it could call itself at statement level (in tail position, or as a let's
# or a parallel let's value): its sequential part (past the fork limit)
# runs in KQ_name (see KQ.def).
def K.isseq(+g: G, +name: String) -> KM(Bool):
  K.fl.go(Fuel.max(), FLIsseq{1, g, name})

# The GPU's seq defs: also those that call other seq defs (its KQ_ code
# holds theirs: see KQ.def).
def K.isseqg(+g: G, +name: String) -> KM(Bool):
  K.fl.go(Fuel.max(), FLIsseq{2, g, name})

# The GPU's seq defs with no parallel let of their own: a call of one from
# the kernel's blocks runs on its lane (see K.call.seq.kq).
def K.isseq1(+g: G, +name: String) -> KM(Bool):
  K.fl.go(Fuel.max(), FLIsseq{3, g, name})

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
# Flat results. U_name stores a flat result's fields through o (see
# Gen.def.unb); Gen.sret is its arity, 0 for a def that returns a node.
def DGrp.n(d: DGrp) -> U32:
  DGrp{id, n} = d
  n

def Gen.sret(+g: G, +name: String) -> U32:
  DGrp.n(G.dps(g, "%r:" ++ name))

def Gen.pvars(ps: List<&2, Core.Pat>) -> Bool:
  match ps:
    case Nil{}:
      True{}
    case Core.PVar{x} <> t:
      Gen.pvars(t)
    case p <> t:
      False{}

def Gen.pnames(ps: List<&2, Core.Pat>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.PVar{x} <> t:
      x <> Gen.pnames(t)
    case p <> t:
      Gen.pnames(t)

def Gen.out.binds(xs: List<&2, String>, +o: String, +i: U32) -> Env():
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      Bind{x, o ++ "[" ++ U32.show(i) ++ "]"} <> Gen.out.binds(t, o, U32.inc(i))

def Gen.out.stores(ds: List<&2, Doc>, +i: U32) -> Doc:
  match ds:
    case Nil{}:
      DNil{}
    case d <> t:
      Doc.list([DStr{"o[" ++ U32.show(i) ++ "] = "}, d, DStr{";\n"}, Gen.out.stores(t, U32.inc(i))])

# Whether f(as) is a full call of a def with a flat result of n fields.
def Gen.out.full(+g: G, +env: Env(), +f: String, +n: Nat, +as: List<&2, Core.Expr>) -> Bool:
  Bool.and(Bool.and(Nat.is_gt(n, 0n), U32.is_eq(Gen.sret(g, f), U32.from_nat(n))),
    Bool.and(Bool.not(Env.has(env, f)),
      Nat.is_eq(List.length(&2, Bool, DInfo.mask(G.def(g, f))), List.length(&2, Core.Expr, as))))

# A let opening a call's flat result into variables: the fields go into a
# local array.
def Gen.out.let(+g: G, +env: Env(), +f: String, +qs: List<&2, Core.Pat>, +as: List<&2, Core.Expr>) -> Bool:
  Bool.and(Gen.pvars(qs), Gen.out.full(g, env, f, List.length(&2, Core.Pat, qs), as))

# A constructor or a call returned as a flat result.
def Gen.out.ctor(t: Tgt, +args: List<&2, Core.Expr>) -> Bool:
  match t:
    case TOut{k, free}:
      U32.is_eq(k, U32.from_nat(List.length(&2, Core.Expr, args)))
    case other:
      False{}

def Gen.out.call(+g: G, +env: Env(), t: Tgt, +name: String, +args: List<&2, Core.Expr>) -> Bool:
  match t:
    case TOut{k, free}:
      Gen.out.full(g, env, name, U32.to_nat(k), args)
    case other:
      False{}

# A flat result of two fields returned by Array.get (1) or Array.swap (2),
# unless a local shadows them; else 0.
def Gen.out.arr(+env: Env(), t: Tgt, +name: String) -> Nat:
  match t:
    case TOut{k, free}:
      Bool.pick(Nat, Bool.or(Bool.not(U32.is_eq(k, 2)), Env.has(env, name)), 0n,
        Bool.pick(Nat, Str.has(["Array.get", "Array.get%w"], name), 1n,
          Bool.pick(Nat, Str.has(["Array.swap", "Array.swap%w"], name), 2n, 0n)))
    case other:
      0n

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
  GSExprs{g: G, env: Env(), xs: List<&2, Core.Expr>}
  GSCallFull{g: G, env: Env(), name: String, mask: List<&2, Bool>, kept: List<&2, Core.Expr>,
    all: List<&2, Core.Expr>, extra: List<&2, Core.Expr>, full: Bool}
  GSCallSplit{g: G, env: Env(), name: String, mask: List<&2, Bool>, s: Split}
  GSCallKind{g: G, env: Env(), name: String, kind: Nat, mask: List<&2, Bool>, s: Split}
  GSCallDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Core.Expr>}
  GSCallLocal{g: G, env: Env(), f: Core.Expr, args: List<&2, Core.Expr>}
  GSFaddDoc{g: G, env: Env(), x: Core.Expr, k: Core.Expr, b: Core.Expr}
  GSFaddEmit{g: G, env: Env(), k: Nat, x: Core.Expr, y: Core.Expr, b: Core.Expr}
  GSFaddMul{g: G, env: Env(), m: Core.Expr, b: Core.Expr, k: Nat}
  GSFaddOne{g: G, env: Env(), a: Core.Expr, m: Core.Expr, km: Nat}
  GSFaddTwo{g: G, env: Env(), a: Core.Expr, b: Core.Expr, ka: Nat, kb: Nat}
  GSFadd{g: G, env: Env(), args: List<&2, Core.Expr>}
  GSCallGlobal{g: G, env: Env(), name: String, args: List<&2, Core.Expr>, fadd: Bool}
  GSCallVar{g: G, env: Env(), name: String, args: List<&2, Core.Expr>, local: Bool}
  GSCallGpu{g: G, env: Env(), name: String, kept: List<&2, Core.Expr>}
  GSCallBangPick{kind: Nat, extra: List<&2, Core.Expr>, full: Bool, g: G, env: Env(), name: String,
    kept: List<&2, Core.Expr>, args: List<&2, Core.Expr>}
  GSCallBangSplit{g: G, env: Env(), name: String, kind: Nat, s: Split, args: List<&2, Core.Expr>}
  GSCallBangDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Core.Expr>}
  GSCallBangVar{g: G, env: Env(), name: String, args: List<&2, Core.Expr>, local: Bool}
  GSCallBang{g: G, env: Env(), args: List<&2, Core.Expr>}
  GSCallName{g: G, env: Env(), name: String, args: List<&2, Core.Expr>, bang: Bool}
  GSCall{g: G, env: Env(), f: Core.Expr, args: List<&2, Core.Expr>}
  GSBitsCon{g: G, env: Env(), e: Core.Expr}
  GSBitsGo{g: G, env: Env(), k: Nat, e: Core.Expr}
  GSBits{g: G, env: Env(), e: Core.Expr}
  GSBitsArgs{g: G, env: Env(), w: Nat, args: List<&2, Core.Expr>}
  GSCtorInfo{g: G, env: Env(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Core.Expr>}
  GSCtor{g: G, env: Env(), name: String, args: List<&2, Core.Expr>}
  GSTmp{g: G, env: Env(), tb: String, args: List<&2, Core.Expr>}
  GSTmpNode{g: G, env: Env(), tb: String, name: String, args: List<&2, Core.Expr>}
  GSTmpHeap{g: G, env: Env(), name: String, args: List<&2, Core.Expr>}
  GSScrs{g: G, env: Env(), xs: List<&2, Core.Expr>}
  GSTail{g: G, env: Env(), cps: List<&2, String>, s: Split}
  GSTailSelf{g: G, env: Env(), self: Self, args: List<&2, Core.Expr>}
  GSDstJumpSplit{g: G, env: Env(), tgt: Tgt, name: String, s: Split}
  GSDstJump{g: G, env: Env(), tgt: Tgt, name: String, args: List<&2, Core.Expr>}
  GSStmtCallDst{g: G, env: Env(), tgt: Tgt, name: String, args: List<&2, Core.Expr>, dst: Bool}
  GSStmtCall{g: G, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Core.Expr>,
    tail: Bool}
  GSDstField{hole: Bool, g: G, env: Env(), a: Core.Expr}
  GSDstFields{g: G, env: Env(), xs: List<&2, Core.Expr>, i: U32, hole: U32}
  GSStmtCtorNext{g: G, env: Env(), self: Self, tgt: Tgt, e: Core.Expr}
  GSStmtCtorHole{g: G, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Core.Expr>,
    hole: U32, next: Core.Expr}
  GSStmtCtorPick{none: Bool, g: G, env: Env(), self: Self, tgt: Tgt, name: String,
    args: List<&2, Core.Expr>, hole: U32}
  GSStmtCtor{g: G, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Core.Expr>,
    hole: U32}
  GSBlock{g: G, env: Env(), e: Core.Expr}
  GSExpr{g: G, env: Env(), e: Core.Expr}
  GSLetVar{g: G, env: Env(), self: Self, tgt: Tgt, x: String, v: Core.Expr, body: Core.Expr, hole: Bool}
  GSCasesNext{g: G, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>,
    rest: List<&2, Core.Expr>, conds: List<&2, String>, b: Doc, mx: List<&2, RcM>}
  GSMatchGo{g: G, env: Env(), self: Self, tgt: Tgt, cases: List<&2, Core.Expr>, r: Scrs}
  GSMatch{g: G, env: Env(), self: Self, tgt: Tgt, scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>}
  GSStmt{g: G, env: Env(), self: Self, tgt: Tgt, e: Core.Expr}
  GSCaseBodyMat{g: G, env: Env(), self: Self, tgt: Tgt, body: Core.Expr, pre: Env(), r: Loads}
  GSCaseBodyGo{opens: Bool, g: G, env: Env(), self: Self, tgt: Tgt, binds: Env(), body: Core.Expr}
  GSCaseBody{g: G, env: Env(), self: Self, tgt: Tgt, binds: Env(), body: Core.Expr}
  GSLam{g: G, env: Env(), p: Core.Pat, body: Core.Expr}
  GSLetPat{g: G, env: Env(), self: Self, tgt: Tgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  GSParVals{g: G, env: Env(), k: U32, i: U32, vs: List<&2, Core.Expr>}
  GSParSeq{g: G, env: Env(), k: U32, i: U32, vs: List<&2, Core.Expr>, decl: Bool}
  GSParFront{g: G, env: Env(), sn: String, k: U32, vs: List<&2, Core.Expr>}
  GSParSq{sq: Bool, g: G, env: Env(), sn: String, k: U32, vs: List<&2, Core.Expr>}
  GSParPick{mode: Nat, g: G, env: Env(), sn: String, k: U32, vs: List<&2, Core.Expr>}
  GSPar{g: G, env: Env(), self: Self, tgt: Tgt, ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>,
    body: Core.Expr}
  GSLetPar{g: G, env: Env(), self: Self, tgt: Tgt, ps: List<&2, Core.Pat>, v: Core.Expr, body: Core.Expr}
  GSLetCtor{g: G, env: Env(), self: Self, tgt: Tgt, name: String, ps: List<&2, Core.Pat>, v: Core.Expr,
    body: Core.Expr, par: Bool}
  GSLetUnb{g: G, env: Env(), self: Self, tgt: Tgt, name: String, ps: List<&2, Core.Pat>, v: Core.Expr, body: Core.Expr}
  GSLetCall{g: G, env: Env(), self: Self, tgt: Tgt, name: String, ps: List<&2, Core.Pat>, f: String,
    args: List<&2, Core.Expr>, body: Core.Expr}
  GSLetGet{hit: Bool, g: G, env: Env(), self: Self, tgt: Tgt, name: String, f: String, a: String,
    x: String, t: Core.Expr, arr: Core.Expr, idx: Core.Expr, body: Core.Expr}
  GSLetOut{hit: Bool, g: G, env: Env(), self: Self, tgt: Tgt, name: String, ps: List<&2, Core.Pat>,
    f: String, args: List<&2, Core.Expr>, body: Core.Expr}
  GSLetSwap{hit: Bool, g: G, env: Env(), self: Self, tgt: Tgt, name: String, f: String, a: String,
    x: String, t: Core.Expr, arr: Core.Expr, idx: Core.Expr, v: Core.Expr, body: Core.Expr}
  GSRetArr{hit: Nat, g: G, env: Env(), tgt: Tgt, name: String, args: List<&2, Core.Expr>}
  GSSwap{g: G, env: Env(), k: U32, arr: Core.Expr, idx: Core.Expr, v: Core.Expr}
  GSCallU{g: G, env: Env(), name: String, s: Split, o: String}
  GSRetCtor{out: Bool, g: G, env: Env(), tgt: Tgt, name: String, args: List<&2, Core.Expr>}
  GSRetCall{out: Bool, g: G, env: Env(), tgt: Tgt, name: String, args: List<&2, Core.Expr>}
  GSLet{g: G, env: Env(), self: Self, tgt: Tgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  GSCases{g: G, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>, cases: List<&2, Core.Expr>,
    mx: List<&2, RcM>}

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
    case GSTmp{g, env, tb, args}:
      DNil{}
    case GSTmpNode{g, env, tb, name, args}:
      DNil{}
    case GSTmpHeap{g, env, name, args}:
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
    case GSCasesNext{g, env, self, tgt, cs, rest, conds, b, mx}:
      DNil{}
    case GSMatchGo{g, env, self, tgt, cases, r}:
      DNil{}
    case GSMatch{g, env, self, tgt, scrs, cases}:
      DNil{}
    case GSStmt{g, env, self, tgt, e}:
      DNil{}
    case GSCaseBodyMat{g, env, self, tgt, body, pre, r}:
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
    case GSLetUnb{g, env, self, tgt, name, ps, v, body}:
      DNil{}
    case GSLetCall{g, env, self, tgt, name, ps, f, args, body}:
      DNil{}
    case GSLetGet{hit, g, env, self, tgt, name, f, a, x, t, arr, idx, body}:
      DNil{}
    case GSLetOut{hit, g, env, self, tgt, name, ps, f, args, body}:
      DNil{}
    case GSLetSwap{hit, g, env, self, tgt, name, f, a, x, t, arr, idx, v, body}:
      DNil{}
    case GSRetArr{hit, g, env, tgt, name, args}:
      DNil{}
    case GSSwap{g, env, k, arr, idx, v}:
      DNil{}
    case GSCallU{g, env, name, s, o}:
      DNil{}
    case GSRetCtor{out, g, env, tgt, name, args}:
      DNil{}
    case GSRetCall{out, g, env, tgt, name, args}:
      DNil{}
    case GSLet{g, env, self, tgt, p, v, body}:
      DNil{}
    case GSCases{g, env, self, tgt, cs, cases, mx}:
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
        case GSCallFull{+g, +env, +name, +mask, +kept, all, extra, full}:
          match full:
            case True{}:
              do Gen<Doc>:
                ks : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, kept})
                xs : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, extra})
                +k : U32 <- Gen.fresh()
                return RC.wrap(k, name, xs, RC.wrap.go(kept, ks, Bor.kept(mask, RC.fl(Gen.rc(g), g, name)), env, k, 0,
                  RcW{Nil{}, DNil{}, DNil{}, False{}}))
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
            case Core.ECall{f, x <> y <> Nil{}}:
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
              Gen.rec(fu, GSCallLocal{g, env, Core.EVar{name}, args})
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
              Gen.rec(fu, GSCall{g, env, Core.EVar{name}, args})
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
              Gen.rec(fu, GSCallLocal{g, env, Core.EVar{name}, args})
            case False{}:
              Gen.rec(fu, GSCallBangDef{g, env, name, G.def(g, name), args})
        # f!(args): a call the device may run (see the GPU backend below).
        case GSCallBang{+g, +env, args}:
          match args:
            case Core.EVar{+name} <> xs:
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
            case Core.EVar{+name}:
              Gen.rec(fu, GSCallName{g, env, name, args, Str.eq(name, "%gpu")})
            case other:
              Gen.rec(fu, GSCallLocal{g, env, other, args})
        case GSBitsCon{+g, +env, e}:
          match e:
            case Core.ECtor{n, a <> b <> Nil{}}:
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
            case Some{CInfo{+tag, ar, +kind, single}}:
              do Gen<Doc>:
                +ds : List<&2, Doc> <- Gen.rec(fu, GSBitsArgs{g, env, P.which(name, ["U32", "F32"]), args})
                +tok : String <- Gen.ru.take(Bool.and(Gen.rc(g), U32.is_zero(kind)), U32.inc(Gen.len(ds)))
                return Gen.ctor.kind.ru(tok, tag, U32.to_nat(kind), ds)
        case GSCtor{+g, +env, +name, args}:
          Gen.rec(fu, GSCtorInfo{g, env, name, G.ctor(g, name), args})
        # A marked argument (see RC.tmp.pass): a temporary node (tb: the
        # loop parameter's buffers, or none), or a node on the heap.
        case GSTmp{+g, +env, +tb, args}:
          match args:
            case Core.ECtor{+n, +as} <> Nil{}:
              Bool.pick(Unit -> Gen(Doc), RC.tmp.env(env, Bool.not(String.is_empty(tb)), as),
                u => Gen.rec(fu, GSTmpNode{g, env, tb, n, as}), u => Gen.rec(fu, GSTmpHeap{g, env, n, as}))(Unit{})
            case other:
              Gen.pure(Doc, DStr{"bend_fail(\"temporary\")"})
        case GSTmpNode{+g, +env, +tb, +name, args}:
          do Gen<Doc>:
            ds : List<&2, Doc> <- Gen.rec(fu, GSBitsArgs{g, env, P.which(name, ["U32", "F32"]), args})
            return RC.tmp.doc(tb, RC.tmp.tag(G.ctor(g, name)), ds)
        case GSTmpHeap{+g, +env, +name, +args}:
          do Gen<Doc>:
            d : Doc <- Gen.rec(fu, GSCtor{g, env, name, args})
            return Doc.list([DStr{"({ " ++ RC.tmp.dups(env, args)}, d, DStr{"; })"}])
        # Scrutinees are bound to fresh C variables.
        case GSScrs{+g, +env, xs}:
          match xs:
            case Nil{}:
              Gen.pure(List<&2, String> & Doc, (Nil{}, DNil{}))
            case +h <> t:
              do Gen<List<&2, String> & Doc>:
                +k : U32 <- Gen.fresh()
                +c : String <- Gen.pure(String, "s" ++ U32.show(k) ++ Bool.pick(String, Gen.scr.bor(env, h), "/*b*/", ""))
                d : Doc <- Gen.rec(fu, GSExpr{g, env, h})
                r : List<&2, String> & Doc <- Gen.rec(fu, GSScrs{g, env, t})
                return Gen.scrs.put(c, d, r)
        case GSTail{+g, +env, cps, s}:
          match s:
            case Split{kept, all, extra, full}:
              # (no reuse in a loop's next arguments: an accumulator built in
              # the nodes it walks scatters them, as a split's halves)
              do Gen<Doc>:
                +outer : String <- Gen.ru.get(Gen.rc(g))
                Gen.ru.set(Gen.rc(g), "")
                ds : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, RC.tmp.tail(kept, 0)})
                Gen.ru.set(Gen.rc(g), outer)
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
        case GSStmtCallDst{+g, +env, +tgt, +name, +args, dst}:
          match dst:
            case True{}:
              Gen.rec(fu, GSDstJump{g, env, tgt, name, args})
            case False{}:
              Gen.rec(fu, GSRetCall{Gen.out.call(g, env, tgt, name, args), g, env, tgt, name, args})
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
            case Core.ECall{Core.EVar{+h}, +hargs}:
              Gen.rec(fu, GSStmtCall{g, env, self, tgt, h, hargs, Gen.is_tail(env, self, tgt, h, hargs)})
            case other:
              Gen.pure(Doc, DStr{"bend_fail(\"hole\");\n"})
        case GSStmtCtorHole{+g, +env, +self, +tgt, +name, args, +hole, next}:
          do Gen<Doc>:
            +ds : List<&2, Doc> <- Gen.rec(fu, GSDstFields{g, env, args, 0, hole})
            +tok : String <- Gen.ru.take(Gen.rc(g), U32.inc(Gen.len(ds)))
            b : Doc <- Gen.rec(fu, GSStmtCtorNext{g, env, self, tgt, next})
            return Doc.list([DStr{"{ V dc = "}, Gen.ctor.hnode.ru(tok, Gen.stmt.ctor.tag(g, name), ds),
              DStr{"; *dst = dc; dst = &FLD(dc, " ++ U32.show((hole - 1 : U32)) ++ ");\n"}, b, DStr{"}\n"}])
        case GSStmtCtorPick{none, +g, +env, +self, +tgt, +name, +args, +hole}:
          match none:
            case True{}:
              Gen.rec(fu, GSRetCtor{Gen.out.ctor(tgt, args), g, env, tgt, name, args})
            case False{}:
              Gen.rec(fu, GSStmtCtorHole{g, env, self, tgt, name, args, hole,
                Gen.dst.nth(U32.to_nat(hole), Core.EErr{"hole"} <> args)})
        # C(.., f(..), ..) with f in the group: the node is stored with a hole
        # where f's result goes, dst moves to the hole, and f's code follows.
        case GSStmtCtor{+g, +env, +self, +tgt, +name, +args, +hole}:
          Gen.rec(fu, GSStmtCtorPick{U32.is_zero(hole), g, env, self, tgt, name, args, hole})
        # A statement-level expression used as a value: ({ V r; ...; r; }),
        # r a uint32_t when e is a U32 (so C selects and compares a U32 in
        # 32 bits: editdist's min, 11.1G -> 8.6G cycles).
        case GSBlock{+g, +env, +e}:
          do Gen<Doc>:
            +k : U32 <- Gen.fresh()
            +r : String <- Gen.pure(String, "r" ++ U32.show(k))
            b : Doc <- Gen.rec(fu, GSStmt{g, env, Self.none(), TSet{r}, e})
            return Doc.list([DStr{"({ " ++ Gen.scalar.cty(Gen.scalar.let(g, env, e)) ++ r ++ ";\n"}, b, DStr{r ++ "; })"}])
        case GSExpr{+g, +env, e}:
          match e:
            case Core.EVar{name}:
              Gen.var(g, env, name)
            case Core.ENum{n}:
              Gen.pure(Doc, DStr{U32.show(n) ++ "u"})
            case Core.ENat{n}:
              Gen.pure(Doc, DStr{U32.show(n) ++ "u"})
            case Core.EFlt{s}:
              Gen.pure(Doc, DStr{"VF(" ++ s ++ "f)"})
            case Core.EStr{s}:
              Gen.str(s)
            case Core.ECall{f, args}:
              Gen.rec(fu, GSCall{g, env, f, args})
            case Core.ECtor{+name, +args}:
              Bool.pick(Unit -> Gen(Doc), String.starts_with(name, "%tmp"),
                u => Gen.rec(fu, GSTmp{g, env, String.drop(name, 4n), args}),
                u => Bool.pick(Unit -> Gen(Doc), Gen.konst.is(g, name, args), u2 => Gen.konst(g, name, args),
                  u2 => Gen.rec(fu, GSCtor{g, env, name, args}))(Unit{}))(Unit{})
            case Core.ELam{p, body}:
              Gen.rec(fu, GSLam{g, env, p, body})
            case Core.ELet{p, v, body}:
              Gen.rec(fu, GSBlock{g, env, Core.ELet{p, v, body}})
            case Core.EMatch{scrs, cases}:
              Gen.rec(fu, GSBlock{g, env, Core.EMatch{scrs, cases}})
            case Core.ESucc{k, x}:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, x})
                return Doc.list([DStr{"nat_addk("}, d, DStr{", " ++ U32.show(k) ++ ")"}])
            case Core.ETy{n, targs}:
              Gen.pure(Doc, DStr{"0"})
            case Core.EErr{m}:
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
                return Doc.list([DStr{Bool.pick(String, Gen.rc(g), "rc_drop(", "(void)(")}, d, DStr{");\n"}, b])
            case False{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +sk : U32 <- Gen.pure(U32, Gen.scalar.let(g, env, v))
                +c : String <- Gen.pure(String, Gen.scalar.wrap(U32.is_ne(sk, 0),
                  Bool.pick(String, U32.is_eq(sk, 2), "u", "v") ++ U32.show(k)))
                d : Doc <- Gen.rec(fu, GSExpr{g, env, v})
                b : Doc <- Gen.rec(fu, GSStmt{g, Bind{x, c} <> env, self, tgt, body})
                return Doc.list([DStr{Gen.scalar.cty(sk) ++ c ++ " = "}, d, DStr{";\n"}, Gen.own(g, Bind{x, c} <> env, [Bind{x, c}], body), b])
        case GSCasesNext{+g, +env, +self, +tgt, +cs, rest, conds, b, mx}:
          match conds:
            case Nil{}:
              Gen.pure(Doc, Doc.list([DStr{"{\n"}, b, DStr{"}\n"}]))
            case h <> t:
              do Gen<Doc>:
                more : Doc <- Gen.rec(fu, GSCases{g, env, self, tgt, cs, rest, mx})
                return Doc.list([DStr{"if (" ++ Gen.and(h <> t) ++ ") {\n"}, b,
                  DStr{"} else "}, more])
        case GSMatchGo{+g, +env, +self, +tgt, +cases, r}:
          match r:
            # (a match whose value goes on, not back, leaves the tokens in
            # reach to what follows it: its cases neither take nor free them)
            case Scrs{cs, decls}:
              do Gen<Doc>:
                +outer : String <- Gen.ru.get(Gen.rc(g))
                Gen.ru.set(Gen.rc(g), Bool.pick(String, Gen.is_ret(tgt), outer, ""))
                body : Doc <- Gen.rec(fu, GSCases{g, env, self, tgt, cs, cases, RC.mx.if(Gen.rc(g), g, env, cases)})
                Gen.ru.set(Gen.rc(g), Bool.pick(String, Gen.is_ret(tgt), "", outer))
                return Doc.list([decls, body])
        case GSMatch{+g, +env, +self, +tgt, scrs, cases}:
          do Gen<Doc>:
            r : List<&2, String> & Doc <- Gen.rec(fu, GSScrs{g, env, scrs})
            Gen.rec(fu, GSMatchGo{g, env, self, tgt, cases, Scrs.of(r)})
        case GSStmt{+g, +env, +self, +tgt, e}:
          match e:
            case Core.ELet{p, v, body}:
              Gen.rec(fu, GSLet{g, env, self, tgt, p, v, body})
            case Core.EMatch{scrs, cases}:
              Gen.rec(fu, GSMatch{g, env, self, tgt, scrs, cases})
            case Core.ECall{Core.EVar{+name}, +args}:
              Gen.rec(fu, GSStmtCall{g, env, self, tgt, name, args, Gen.is_tail(env, self, tgt, name, args)})
            case Core.ECtor{+name, +args}:
              Gen.rec(fu, GSStmtCtor{g, env, self, tgt, name, args,
                Gen.dst.hole(g, env, tgt, Gen.dst.node(G.ctor(g, name)), args, 0, 0)})
            case other:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, other})
                return Gen.ret(tgt, d)
        # The fields and the opened nodes are read, then the nodes taken, each
        # before the nodes inside it: a shared one shares its fields, so the
        # nodes inside it are shared when they are taken, and share theirs.
        case GSCaseBodyMat{+g, +env, +self, +tgt, +body, +pre, r}:
          match r:
            case Loads{+mb, loads}:
              +vars = Gen.vars(mb)
              +dead = RC.dead.if(Gen.rc(g), g, Env.names(List.append(&2, Bind, vars, env)), body, pre, mb)
              +ts = List.append(&2, RuT, RU.toks(pre, mb, "%top", dead), List.reverse(&2, RuT, RU.toks(pre, mb, "%sub", dead)))
              do Gen<Doc>:
                outer : String <- Gen.ru.get(Gen.rc(g))
                Gen.ru.set(Gen.rc(g), String.join(List.append(&2, String, RU.names(ts), RU.list(outer)), " "))
                b : Doc <- Gen.rec(fu, GSStmt{g, List.append(&2, Bind, vars, env), self, tgt, body})
                after : String <- Gen.ru.get(Gen.rc(g))
                +left : List<&2, String> <- Gen.pure(List<&2, String>, RU.list(after))
                Gen.ru.set(Gen.rc(g), String.join(RU.minus(left, RU.names(ts)), " "))
                return Doc.list([loads, RC.arrs(Gen.rc(g), mb), RU.takes.pick(Gen.rc(g), ts, left,
                  Gen.takes.stmts(Gen.takes(mb, "%top", "bend_take")) ++
                  Gen.takes.stmts(List.reverse(&2, String, Gen.takes(mb, "%sub", "bend_take")))),
                  Gen.own(g, List.append(&2, Bind, vars, env), RC.alive(pre, mb, RC.hand(pre, dead)), body), b])
        case GSCaseBodyGo{opens, +g, +env, +self, +tgt, +binds, +body}:
          match opens:
            case False{}:
              do Gen<Doc>:
                b : Doc <- Gen.rec(fu, GSStmt{g, List.append(&2, Bind, binds, env), self, tgt, body})
                return Doc.list([Gen.own(g, List.append(&2, Bind, binds, env), binds, body), b])
            case True{}:
              do Gen<Doc>:
                r : Env() & Doc <- Gen.mat(binds)
                Gen.rec(fu, GSCaseBodyMat{g, env, self, tgt, body, binds, Loads.of(r)})
        # A body after a pattern's bindings: the nodes the pattern opens are
        # freed (see above).
        case GSCaseBody{+g, +env, +self, +tgt, binds0, +body}:
          +binds = RC.bfilter(binds0)
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
            +inner : Env() <- Gen.pure(Env(), Gen.caps.inner(caps, 0))
            +outer : String <- Gen.ru.get(Gen.rc(g))
            Gen.ru.set(Gen.rc(g), "")
            b : Doc <- Gen.rec(fu, GSCaseBody{g, inner, Self.none(), TRet{},
              Bool.pick(Env(), Gen.rc(g), List.append(&2, Bind, binds, inner), binds), body})
            Gen.ru.set(Gen.rc(g), outer)
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
            case +v <> t:
              do Gen<Doc>:
                c : Doc <- Gen.rec(fu, GSLam{g, env, Core.PVar{"_"}, v})
                rest : Doc <- Gen.rec(fu, GSParVals{g, env, k, U32.inc(i), t})
                return Doc.list([RC.fork(Gen.rc(g), g, env, v), DStr{"V " ++ Gen.par.name(k, i) ++ "t = par_fork("}, c, DStr{");\n"},
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
          +n = List.length(&2, Core.Expr, vs)
          +lg = U32.show(Gen.par.lg(n))
          do Gen<Doc>:
            sq : Doc <- Gen.rec(fu, GSParSeq{g, env, k, 0, vs, False{}})
            +j : U32 <- Gen.fresh()
            fk : Doc <- Gen.rec(fu, GSParVals{g, env, j, 0, vs})
            return Doc.list([DStr{Gen.par.decls(n, k, 0) ++ "\nif (par_depth >= par_front) {\n" ++ Gen.par.def(sn)}, sq,
              DStr{Gen.par.undef(sn) ++ "} else {\npar_depth += " ++ lg ++ ";\n"}, fk,
              DStr{Gen.par.copy(n, k, j, 0) ++ "\npar_depth -= " ++ lg ++ ";\n}\n"}])
        case GSParSq{sq, +g, +env, +sn, +k, +vs}:
          match sq:
            case True{}:
              Gen.rec(fu, GSParFront{g, env, sn, k, vs})
            case False{}:
              Gen.rec(fu, GSParFront{g, env, "", k, vs})
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
                +outer : String <- Gen.ru.get(Gen.rc(g))
                Gen.ru.set(Gen.rc(g), "")
                pre : Doc <- Gen.rec(fu, GSParPick{Gen.par.mode(mode, sn), g, env, sn, k, vs})
                Gen.ru.set(Gen.rc(g), outer)
                +qs : List<&2, Core.Pat> <- Gen.pure(List<&2, Core.Pat>, RC.unders(Gen.rc(g), ps))
                b : Doc <- Gen.rec(fu, GSStmt{g, Gen.par.env(qs, k, 0, env), Self{sn, sm, sc}, tgt, body})
                return Doc.list([pre, Gen.own(g, Gen.par.env(qs, k, 0, env), Gen.par.env(qs, k, 0, Nil{}), body), b])
        case GSLetPar{+g, +env, +self, +tgt, ps, v, body}:
          match v:
            case Core.ECtor{n, vs}:
              Gen.rec(fu, GSPar{g, env, self, tgt, ps, vs, body})
            case other:
              Gen.rec(fu, GSPar{g, env, self, tgt, ps, [other], body})
        case GSLetCtor{+g, +env, +self, +tgt, name, ps, v, body, par}:
          match par:
            case True{}:
              Gen.rec(fu, GSLetPar{g, env, self, tgt, ps, v, body})
            case False{}:
              Gen.rec(fu, GSLetUnb{g, env, self, tgt, name, ps, v, body})
        # A let opening a call's pair or record: Array.get's pair is the
        # array and its cell; a flat result's fields go into a local array.
        case GSLetUnb{+g, +env, +self, +tgt, +name, ps, v, +body}:
          match v:
            case Core.ECall{Core.EVar{+f}, args}:
              Gen.rec(fu, GSLetCall{g, env, self, tgt, name, ps, f, args, body})
            case other:
              Gen.rec(fu, GSLetPat{g, env, self, tgt, Core.PCtor{name, ps}, other, body})
        case GSLetCall{+g, +env, +self, +tgt, +name, ps, +f, args, +body}:
          match ps args:
            case Core.PVar{+a} <> Core.PVar{+x} <> Nil{} t <> arr <> idx <> Nil{}:
              Gen.rec(fu, GSLetGet{Bool.and(Bool.and(Str.has(["Array.get", "Array.get%w"], f), Str.eq(name, "Tuple")),
                Bool.not(Env.has(env, f))), g, env, self, tgt, name, f, a, x, t, arr, idx, body})
            case Core.PVar{+a} <> Core.PVar{+x} <> Nil{} t <> arr <> idx <> v <> Nil{}:
              Gen.rec(fu, GSLetSwap{Bool.and(Bool.and(Str.has(["Array.swap", "Array.swap%w"], f), Str.eq(name, "Tuple")),
                Bool.not(Env.has(env, f))), g, env, self, tgt, name, f, a, x, t, arr, idx, v, body})
            case +qs +as:
              Gen.rec(fu, GSLetOut{Gen.out.let(g, env, f, qs, as), g, env, self, tgt, name, qs, f, as, body})
        case GSLetGet{hit, +g, +env, +self, +tgt, +name, +f, +a, +x, t, arr, idx, +body}:
          match hit:
            case True{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +ca : String <- Gen.pure(String, "ga" ++ U32.show(k))
                +cx : String <- Gen.pure(String, "gx" ++ U32.show(k))
                +sc : Bool <- Gen.pure(Bool, Str.eq(f, "Array.get%w"))
                +bx : String <- Gen.pure(String, Gen.scalar.wrap(sc, cx))
                da : Doc <- Gen.rec(fu, GSExpr{g, env, arr})
                di : Doc <- Gen.rec(fu, GSExpr{g, env, idx})
                b : Doc <- Gen.rec(fu, GSStmt{g, Bind{a, ca} <> Bind{x, bx} <> env, self, tgt, body})
                return Doc.list([DStr{"V " ++ ca ++ " = "}, da, DStr{";\nV " ++ cx ++ " = *arr_at(" ++ ca ++ ", "}, di,
                  DStr{Bool.pick(String, sc, ");\n", "); arr_got(" ++ ca ++ ", " ++ cx ++ ");\n")},
                  Gen.own(g, Bind{a, ca} <> Bind{x, bx} <> env, [Bind{a, ca}, Bind{x, bx}], body), b])
            case False{}:
              +qs = {[Core.PVar{a}, Core.PVar{x}] : List<&2, Core.Pat>}
              +as = {[t, arr, idx] : List<&2, Core.Expr>}
              Gen.rec(fu, GSLetOut{Gen.out.let(g, env, f, qs, as), g, env, self, tgt, name, qs, f, as, body})
        # (a, x) = Array.swap(T, arr, i, v): the old cell and the array, with
        # no pair in between.
        case GSLetSwap{hit, +g, +env, +self, +tgt, +name, +f, +a, +x, t, arr, idx, v, +body}:
          match hit:
            case True{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +ca : String <- Gen.pure(String, "ga" ++ U32.show(k))
                +cx : String <- Gen.pure(String, "gx" ++ U32.show(k))
                +bx : String <- Gen.pure(String, Gen.scalar.wrap(Str.eq(f, "Array.swap%w"), cx))
                sw : Doc <- Gen.rec(fu, GSSwap{g, env, k, arr, idx, v})
                b : Doc <- Gen.rec(fu, GSStmt{g, Bind{a, ca} <> Bind{x, bx} <> env, self, tgt, body})
                return Doc.list([sw, Gen.own(g, Bind{a, ca} <> Bind{x, bx} <> env, [Bind{a, ca}, Bind{x, bx}], body), b])
            case False{}:
              +qs = {[Core.PVar{a}, Core.PVar{x}] : List<&2, Core.Pat>}
              +as = {[t, arr, idx, v] : List<&2, Core.Expr>}
              Gen.rec(fu, GSLetOut{Gen.out.let(g, env, f, qs, as), g, env, self, tgt, name, qs, f, as, body})
        # V gaK = arr; V gxK = old cell, with v stored in it.
        case GSSwap{+g, +env, +k, arr, idx, v}:
          +ks = U32.show(k)
          do Gen<Doc>:
            da : Doc <- Gen.rec(fu, GSExpr{g, env, arr})
            di : Doc <- Gen.rec(fu, GSExpr{g, env, idx})
            dv : Doc <- Gen.rec(fu, GSExpr{g, env, v})
            return Doc.list([DStr{"V ga" ++ ks ++ " = "}, da, DStr{";\nV gi" ++ ks ++ " = "}, di, DStr{";\nV gv" ++ ks ++ " = "},
              dv, DStr{";\nV *gp" ++ ks ++ " = arr_at(ga" ++ ks ++ ", gi" ++ ks ++ ");\nV gx" ++ ks ++ " = *gp" ++ ks ++
              ";\narr_put(ga" ++ ks ++ ", gp" ++ ks ++ ", gv" ++ ks ++ ");\n"}])
        # A flat result of two fields returned from Array.get (1) or
        # Array.swap (2): the array and the cell go straight out.
        case GSRetArr{hit, +g, +env, +tgt, +name, +args}:
          match hit args:
            case 1n t <> arr <> idx <> Nil{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +ks : String <- Gen.pure(String, U32.show(k))
                da : Doc <- Gen.rec(fu, GSExpr{g, env, arr})
                di : Doc <- Gen.rec(fu, GSExpr{g, env, idx})
                return Doc.list([DStr{"{\nV ga" ++ ks ++ " = "}, da, DStr{";\nV gx" ++ ks ++ " = *arr_at(ga" ++ ks ++ ", "}, di,
                  DStr{Bool.pick(String, Str.eq(name, "Array.get%w"), ");", "); arr_got(ga" ++ ks ++ ", gx" ++ ks ++ ");") ++
                  "\no[0] = ga" ++ ks ++ "; o[1] = gx" ++ ks ++ ";\nreturn 0;\n}\n"}])
            case 2n t <> arr <> idx <> v <> Nil{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +ks : String <- Gen.pure(String, U32.show(k))
                sw : Doc <- Gen.rec(fu, GSSwap{g, env, k, arr, idx, v})
                return Doc.list([DStr{"{\n"}, sw, DStr{"o[0] = ga" ++ ks ++ "; o[1] = gx" ++ ks ++ ";\nreturn 0;\n}\n"}])
            case h as:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSCall{g, env, Core.EVar{name}, as})
                return Gen.ret(tgt, d)
        case GSLetOut{hit, +g, +env, +self, +tgt, +name, +ps, +f, +args, +body}:
          match hit:
            case True{}:
              do Gen<Doc>:
                +k : U32 <- Gen.fresh()
                +o : String <- Gen.pure(String, "uo" ++ U32.show(k))
                c : Doc <- Gen.rec(fu, GSCallU{g, env, f, Gen.split(DInfo.mask(G.def(g, f)), args,
                  Split{Nil{}, Nil{}, Nil{}, False{}}), o})
                +binds : Env() <- Gen.pure(Env(), Gen.out.binds(Gen.pnames(ps), o, 0))
                b : Doc <- Gen.rec(fu, GSStmt{g, List.append(&2, Bind, binds, env), self, tgt, body})
                return Doc.list([DStr{"V " ++ o ++ "[" ++ U32.show(Gen.sret(g, f)) ++ "]; "}, c, DStr{";\n"},
                  Gen.own(g, List.append(&2, Bind, binds, env), binds, body), b])
            case False{}:
              Gen.rec(fu, GSLetPat{g, env, self, tgt, Core.PCtor{name, ps}, Core.ECall{Core.EVar{f}, args}, body})
        case GSCallU{+g, +env, +name, s, +o}:
          match s:
            case Split{+kept, all, extra, full}:
              do Gen<Doc>:
                Gen.ref(name)
                ks : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, kept})
                +k : U32 <- Gen.fresh()
                return RC.wrap.u(k, name, o, RC.wrap.go(kept, ks, Bor.kept(DInfo.mask(G.def(g, name)),
                  RC.fl(Gen.rc(g), g, name)), env, k, 0, RcW{Nil{}, DNil{}, DNil{}, False{}}))
        # A flat result's constructor stores its fields; a call of a def with
        # a flat result of the same arity passes o on.
        case GSRetCtor{out, +g, +env, +tgt, +name, +args}:
          match out:
            case True{}:
              do Gen<Doc>:
                ds : List<&2, Doc> <- Gen.rec(fu, GSExprs{g, env, args})
                return Doc.list([Gen.out.stores(ds, 0), DStr{"return 0;\n"}])
            case False{}:
              do Gen<Doc>:
                d : Doc <- Gen.rec(fu, GSExpr{g, env, Core.ECtor{name, args}})
                return Gen.ret(tgt, d)
        case GSRetCall{out, +g, +env, +tgt, +name, +args}:
          match out:
            case True{}:
              do Gen<Doc>:
                c : Doc <- Gen.rec(fu, GSCallU{g, env, name, Gen.split(DInfo.mask(G.def(g, name)), args,
                  Split{Nil{}, Nil{}, Nil{}, False{}}), "o"})
                return Doc.list([DStr{"return "}, c, DStr{";\n"}])
            case False{}:
              Gen.rec(fu, GSRetArr{Gen.out.arr(env, tgt, name), g, env, tgt, name, args})
        case GSLet{+g, +env, +self, +tgt, p, v, body}:
          match p:
            case Core.PVar{+x}:
              Gen.rec(fu, GSLetVar{g, env, self, tgt, x, v, body, Str.eq(x, "_")})
            case Core.PCtor{+name, ps}:
              Gen.rec(fu, GSLetCtor{g, env, self, tgt, name, ps, v, body, Str.eq(name, "%par")})
            case other:
              Gen.rec(fu, GSLetPat{g, env, self, tgt, other, v, body})
        case GSCases{+g, +env, +self, +tgt, +cs, cases, +mx}:
          match cases:
            case Nil{}:
              Gen.pure(Doc, DStr{"{ bend_fail(\"runtime fail-stop\"); }\n"})
            case Core.ECase{+ps, +body} <> t:
              +pr = Gen.pats(g, ps, cs, PatR{Nil{}, Nil{}})
              +conds = PatR.conds(pr)
              +binds = PatR.binds(pr)
              do Gen<Doc>:
                +outer : String <- Gen.ru.get(Gen.rc(g))
                b : Doc <- Gen.rec(fu, GSCaseBody{g, env, self, tgt, binds, body})
                after : String <- Gen.ru.get(Gen.rc(g))
                Gen.ru.set(Gen.rc(g), outer)
                Gen.rec(fu, GSCasesNext{g, env, self, tgt, cs, t, List.reverse(&2, String, conds),
                  Doc.list([RC.arm.pick(Gen.rc(g), g, Env.names(env), mx, Core.ECase{ps, body}), RU.frees(RU.list(after)), b]), mx})
            case other <> t:
              Gen.rec(fu, GSCases{g, env, self, tgt, cs, t, mx})

def Gen.stmt(+g: G, +env: Env(), +self: Self, +tgt: Tgt, e: Core.Expr) -> Gen(Doc):
  Gen.rec(Fuel.max(), GSStmt{g, env, self, tgt, e})

# C parameter list and environment of a def.
type Sig is Data:
  Sig{params: List<&2, String>, env: Env(), wargs: List<&2, String>}

# (fl: the def's borrow flags; a borrowed parameter's C name is marked
# /*b*/)
def Gen.sig.b(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +fl: List<&2, Bool>, +i: U32, r: Sig) -> Sig:
  match ps mask:
    case Core.Param{x, m, t} <> pt True{} <> mt:
      Sig{params, env, wargs} = r
      +c = "a" ++ U32.show(i)
      Gen.sig.b(pt, mt, Bor.tail(fl), U32.inc(i), Sig{List.append(&2, String, params, [c]),
        Bind{x, Bool.pick(String, Bor.head(fl), c ++ "/*b*/", Gen.scalar.wrap(Gen.scalar.ty(t), c))} <> env,
        List.append(&2, String, wargs, ["a[" ++ U32.show(i) ++ "]"])})
    case Core.Param{x, m, t} <> pt False{} <> mt:
      Sig{params, env, wargs} = r
      Gen.sig.b(pt, mt, Bor.tail(fl), U32.inc(i), Sig{params, Bind{x, "0"} <> env, wargs})
    case pl ml:
      r

def Gen.sig(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32, r: Sig) -> Sig:
  Gen.sig.b(ps, mask, Nil{}, i, r)

def Gen.wrapper(+name: String, wargs: List<&2, String>) -> Gen(Unit):
  +w = Gen.w(name)
  do Gen<Unit>:
    Gen.proto(DStr{"static V " ++ w ++ "(V *a);\n"})
    Gen.code(DStr{"static V " ++ w ++ "(V *a) { (void)a; return " ++ Gen.f(name) ++ "(" ++
      String.join(wargs, ", ") ++ "); }\n"})

# A closure owns its arguments: the wrapper of a def that borrows some
# drops those after the call.
def Gen.wrapper.args(wargs: List<&2, String>, +fl: List<&2, Bool>, +i: U32) -> List<&2, String>:
  match wargs:
    case Nil{}:
      Nil{}
    case a <> t:
      Bool.pick(String, Bor.head(fl), "b" ++ U32.show(i), a) <> Gen.wrapper.args(t, Bor.tail(fl), U32.inc(i))

def Gen.wrapper.drops(wargs: List<&2, String>, +fl: List<&2, Bool>, +i: U32) -> String:
  match wargs:
    case Nil{}:
      ""
    case a <> t:
      Bool.pick(String, Bor.head(fl), " rc_drop(b" ++ U32.show(i) ++ ");", "") ++
        Gen.wrapper.drops(t, Bor.tail(fl), U32.inc(i))

def Gen.wrapper.loads(wargs: List<&2, String>, +fl: List<&2, Bool>, +i: U32) -> String:
  match wargs:
    case Nil{}:
      ""
    case a <> t:
      Bool.pick(String, Bor.head(fl), "V b" ++ U32.show(i) ++ " = " ++ a ++ "; ", "") ++
        Gen.wrapper.loads(t, Bor.tail(fl), U32.inc(i))

def Gen.wrapper.pick(any: Bool, +name: String, +wargs: List<&2, String>, +fl: List<&2, Bool>) -> Gen(Unit):
  match any:
    case False{}:
      Gen.wrapper(name, wargs)
    case True{}:
      +w = Gen.w(name)
      do Gen<Unit>:
        Gen.proto(DStr{"static V " ++ w ++ "(V *a);\n"})
        Gen.code(DStr{"static V " ++ w ++ "(V *a) { " ++ Gen.wrapper.loads(wargs, fl, 0) ++ "V r = " ++
          Gen.f(name) ++ "(" ++ String.join(Gen.wrapper.args(wargs, fl, 0), ", ") ++ ");" ++
          Gen.wrapper.drops(wargs, fl, 0) ++ " return r; }\n"})

# fl: the flags of the kept parameters.
def Gen.wrapper.b(+name: String, +wargs: List<&2, String>, +fl: List<&2, Bool>) -> Gen(Unit):
  Gen.wrapper.pick(Bor.any(fl), name, wargs, fl)

def Gen.memo.add.go(st: St, b: Bind) -> Unit & St:
  St{n, protos, code, refs, errs, memo, effs} = st
  (Unit{}, St{n, protos, code, refs, errs, b <> memo, effs})

def Gen.memo.add(b: Bind) -> Gen(Unit):
  st => Gen.memo.add.go(st, b)

# A def's U32 parameters live in uint32_t locals: the C parameter is aK_
# and the local aK, so clang sees 32-bit values (a loop over them, a self
# call's goto top, can then use 32-bit vector lanes).
def Gen.u32.if(+c: String, rest: List<&2, String>, keep: Bool) -> List<&2, String>:
  match keep:
    case True{}:
      c <> rest
    case False{}:
      rest

def Gen.u32.names(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32) -> List<&2, String>:
  match ps mask:
    case Core.Param{x, m, +t} <> pt True{} <> mt:
      Gen.u32.if("a" ++ U32.show(i), Gen.u32.names(pt, mt, U32.inc(i)), Str.eq(t, "U32"))
    case Core.Param{x, m, t} <> pt False{} <> mt:
      Gen.u32.names(pt, mt, U32.inc(i))
    case pl ml:
      Nil{}

def Gen.u32.of(d: Decl, +mask: List<&2, Bool>) -> List<&2, String>:
  match d:
    case DDef{n, ps, b, r}:
      Gen.u32.names(ps, mask, 0)
    case other:
      Nil{}

def Gen.u32(+g: G, +name: String, +mask: List<&2, Bool>) -> List<&2, String>:
  Gen.u32.of(G.body(g, name), mask)

def Gen.cparams.u.go(ps: List<&2, String>, +us: List<&2, String>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case +h <> t:
      ("V " ++ h ++ Bool.pick(String, Str.has(us, h), "_", "")) <> Gen.cparams.u.go(t, us)

def Gen.cparams.u(ps: List<&2, String>, +us: List<&2, String>) -> String:
  match ps:
    case Nil{}:
      "void"
    case h <> t:
      String.join(Gen.cparams.u.go(h <> t, us), ", ")

def Gen.u32.open(us: List<&2, String>) -> String:
  match us:
    case Nil{}:
      ""
    case +h <> t:
      "uint32_t " ++ h ++ " = (uint32_t)" ++ h ++ "_;\n" ++ Gen.u32.open(t)

# S_name, a seq def's sequential clone: its parallel lets run in order and
# its calls to itself stay in S_name (F_name is renamed to it inside).
def Gen.def.seq(sq: Bool, +g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr, +env: Env(),
  +params: List<&2, String>) -> Gen(Unit):
  match sq:
    case True{}:
      +us = Gen.u32(g, name, mask)
      +head = "static V S_" ++ Gen.mangle(name) ++ "(" ++ Gen.cparams.u(params, us) ++ ")"
      do Gen<Unit>:
        Gen.proto(DStr{head ++ ";\n"})
        Gen.memo.add(Bind{"%seqmode", name})
        b : Doc <- Gen.stmt(g, env, Self{name, mask, params}, TRet{}, R.ops(body, "Nat"))
        Gen.memo.add(Bind{"%seqmode", ""})
        Gen.code(Doc.list([DStr{"#define " ++ Gen.f(name) ++ " S_" ++ Gen.mangle(name) ++ "\n" ++ head ++ " {\n" ++
          Gen.u32.open(us) ++ "top:;\n"},
          Gen.own(g, env, env, R.ops(body, "Nat")), b, DStr{"}\n#undef " ++ Gen.f(name) ++ "\n"}]))
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
def Gen.def.dst(+g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr, +params: List<&2, String>,
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
    Gen.code(Doc.list([DStr{dhead ++ " {\ntop:;\n"}, Gen.own(g, env, env, R.ops(body, "Nat")), b,
      DStr{"}\n"}]))
    Gen.code(DStr{head ++ " { V r; D_" ++ m ++ "(" ++ String.join("&r" <> Gen.dst.pad(U32.to_nat(n), params,
      False{}, 0), ", ") ++ "); return r; }\n"})
    Gen.wrapper(name, wargs)

def Pat.is_par(p: Core.Pat) -> Bool:
  match p:
    case Core.PCtor{+n, ps}:
      Str.eq(n, "%par")
    case other:
      False{}

# Whether an expression holds a parallel let (outside lambdas). A list
# field is its head, then the node rebuilt with the rest.
def Expr.has_par(e: Core.Expr) -> Bool:
  match e:
    case Core.ELet{p, +v, +b}:
      Bool.pick(Unit -> Bool, Pat.is_par(p), u => True{},
        u => Bool.pick(Unit -> Bool, Expr.has_par(v), u => True{}, u => Expr.has_par(b))(Unit{}))(Unit{})
    case Core.EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(Core.EMatch{t, cases}))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case +c <> t:
              Bool.pick(Unit -> Bool, Expr.has_par(c), u => True{}, u => Expr.has_par(Core.EMatch{Nil{}, t}))(Unit{})
    case Core.ECase{ps, b}:
      Expr.has_par(b)
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Expr.has_par(f)
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(Core.ECall{f, t}))(Unit{})
    case Core.ECtor{k, args}:
      match args:
        case Nil{}:
          False{}
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(Core.ECtor{k, t}))(Unit{})
    case Core.EOp{op, +a, +b}:
      Bool.pick(Unit -> Bool, Expr.has_par(a), u => True{}, u => Expr.has_par(b))(Unit{})
    case Core.ESucc{k, x}:
      Expr.has_par(x)
    case Core.EAnn{x, ty}:
      Expr.has_par(x)
    case other:
      False{}

def Gen.def.boxed(+g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr,
  +params: List<&2, String>, +env: Env(), +wargs: List<&2, String>
) -> Gen(Unit):
  +us = Gen.u32(g, name, mask)
  +head = "static V " ++ Gen.f(name) ++ "(" ++ Gen.cparams.u(params, us) ++ ")"
  do Gen<Unit>:
    Gen.proto(DStr{head ++ ";\n"})
    +e : Core.Expr = RC.tmp.body(Gen.rc(g), g, Env.names(env), R.ops(body, "Nat"))
    b : Doc <- Gen.stmt(g, env, Self{name, mask, params}, TRet{}, e)
    Gen.code(Doc.list([DStr{head ++ " {\n" ++ Gen.u32.open(us) ++ RC.tmp.decl(Bor.kept(mask, Bor.list(Bor.flags(g, name))),
      RC.tmp.used(Fuel.max(), name, mask, e, Nil{}), 0) ++ "top:;\n"}, Gen.own(g, env, env, e), b, DStr{"}\n"}]))
    Gen.wrapper.b(name, wargs, Bor.kept(mask, Bor.list(Bor.flags(g, name))))
    Gen.def.seq(Bool.and(Expr.has_par(body), Gen.isseq(g, name)), g, name, mask, body, env, params)

# A def with a flat result of k fields: U_name stores them through o, and
# F_name, for the callers that want a node, builds it from them. U_name is
# inlined into its callers (BEND_UINL), so o stays in registers.
def Gen.def.unb(+k: U32, +g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr,
  +params: List<&2, String>, +env: Env(), +wargs: List<&2, String>
) -> Gen(Unit):
  +u = "U_" ++ Gen.mangle(name)
  +us = Gen.u32(g, name, mask)
  +uhead = "static V " ++ u ++ "(" ++ String.join(List.append(&2, String, Gen.cparams.u.go(params, us), ["V *o"]), ", ") ++ ")"
  +head = "static V " ++ Gen.f(name) ++ "(" ++ Gen.cparams(params) ++ ")"
  do Gen<Unit>:
    Gen.proto(DStr{head ++ ";\n" ++ uhead ++ ";\n"})
    +e : Core.Expr = RC.tmp.body(Gen.rc(g), g, Env.names(env), R.ops(body, "Nat"))
    b : Doc <- Gen.stmt(g, env, Self{name, mask, params}, TOut{k, Gen.free(g)}, e)
    Gen.code(Doc.list([DStr{"BEND_UINL" ++ String.drop(uhead, 6n) ++ " {\n" ++ Gen.u32.open(us) ++
      RC.tmp.decl(Bor.kept(mask, Bor.list(Bor.flags(g, name))), RC.tmp.used(Fuel.max(), name, mask, e, Nil{}), 0) ++
      "top:;\n"}, Gen.own(g, env, env, e), b, DStr{"}\n"}]))
    Gen.code(DStr{head ++ " { V o[" ++ U32.show(k) ++ "]; " ++ u ++ "(" ++ String.join(List.append(&2, String, params,
      ["o"]), ", ") ++ "); return CN(0, " ++ U32.show(k) ++ ", o); }\n"})
    Gen.wrapper.b(name, wargs, Bor.kept(mask, Bor.list(Bor.flags(g, name))))

def Gen.def.plain.pick(boxed: Bool, +k: U32, +g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr,
  +params: List<&2, String>, +env: Env(), +wargs: List<&2, String>
) -> Gen(Unit):
  match boxed:
    case True{}:
      Gen.def.boxed(g, name, mask, body, params, env, wargs)
    case False{}:
      Gen.def.unb(k, g, name, mask, body, params, env, wargs)

def Gen.def.plain(+g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr,
  +params: List<&2, String>, +env: Env(), +wargs: List<&2, String>
) -> Gen(Unit):
  +k = Gen.sret(g, name)
  Gen.def.plain.pick(U32.is_zero(k), k, g, name, mask, body, params, env, wargs)

def Gen.def.body.pick(plain: Bool, +g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr,
  +params: List<&2, String>, +env: Env(), +wargs: List<&2, String>
) -> Gen(Unit):
  match plain:
    case False{}:
      Gen.def.dst(g, name, mask, body, params, env, wargs, G.dps(g, name))
    case True{}:
      Gen.def.plain(g, name, mask, body, params, env, wargs)

def Gen.def.body(+g: G, +name: String, +mask: List<&2, Bool>, +body: Core.Expr, sig: Sig) ->
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
  +g: G, +name: String, +mask: List<&2, Bool>, body: Core.Expr, sig: Sig, native: Bool
) -> Gen(Unit):
  match native:
    case True{}:
      Gen.wrapper.b(name, Sig.wargs(sig), Bor.kept(mask, Bor.list(Bor.flags(g, name))))
    case False{}:
      Gen.def.body(g, name, mask, body, sig)

def Gen.dummy_params(mask: List<&2, Bool>) -> List<&2, Core.Param>:
  match mask:
    case Nil{}:
      Nil{}
    case h <> t:
      Core.Param{"_", 0, ""} <> Gen.dummy_params(t)

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
      Gen.def.native(g, name, mask, body, Gen.sig.b(ps, mask, Bor.list(Bor.flags(g, name)), 0,
        Sig{Nil{}, Nil{}, Nil{}}), U32.is_eq(kind, 2))
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

# Whether a value of a type in ts can stay in the device's arena for the
# CPU to read in place (see gpu_pinnable in rt/gpuhost.h): it reaches no
# closure (the device's hold labels) and no array, through the fields of
# the data types named. seen: the types met, and their type parameters
# (whose arguments are among the types checked).
def Gen.gpu.pin.fs(fs: List<&2, Field>, rest: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match fs:
    case Nil{}:
      rest
    case Field{n, t} <> fs2:
      t <> Gen.gpu.pin.fs(fs2, rest)

def Gen.gpu.pin.cs(cs: List<&2, Ctor>, rest: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match cs:
    case Nil{}:
      rest
    case Ctor{n, fs} <> cs2:
      Gen.gpu.pin.fs(fs, Gen.gpu.pin.cs(cs2, rest))

def Gen.gpu.pin.targs(t: Core.Expr) -> List<&2, Core.Expr>:
  match t:
    case Core.ETy{n, args}:
      args
    case Core.ECall{f, args}:
      args
    case other:
      Nil{}

def Gen.gpu.pin.head(+t: Core.Expr) -> String:
  Bool.pick(String, Str.eq(P.head(t), "&"), "Sigma", P.head(t))

# The declaration of t's type: none to look into (an empty one) for a type
# met or a scalar.
def Gen.gpu.pin.d(+g: G, +seen: List<&2, String>, +t: Core.Expr) -> Decl:
  +h = Gen.gpu.pin.head(t)
  Bool.pick(Decl, Bool.or(Str.has(seen, h), Str.has(["U32", "F32", "I32", "Bool", "Nat", "Char", "Unit"], h)),
    DType{h, Nil{}, Nil{}}, G.body(g, "%" ++ h))

def Gen.gpu.pin.ok(d: Decl) -> Bool:
  match d:
    case DType{n, ps, cs}:
      True{}
    case other:
      False{}

def Gen.gpu.pin.seen(d: Decl, +seen: List<&2, String>) -> List<&2, String>:
  match d:
    case DType{n, ps, cs}:
      n <> List.append(&2, String, ps, seen)
    case other:
      seen

def Gen.gpu.pin.next(d: Decl, t: Core.Expr, rest: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match d:
    case DType{n, ps, cs}:
      List.append(&2, Core.Expr, Gen.gpu.pin.targs(t), Gen.gpu.pin.cs(cs, rest))
    case other:
      rest

def Gen.gpu.pin(fuel: Nat, ok: Bool, ts: List<&2, Core.Expr>, +g: G, +seen: List<&2, String>) -> Bool:
  match fuel:
    case 0n:
      False{}
    case 1n+f:
      match ok:
        case False{}:
          False{}
        case True{}:
          match ts:
            case Nil{}:
              True{}
            case +t <> rest:
              +d = (Gen.gpu.pin.d(g, seen, t) : Decl)
              Gen.gpu.pin(f, Gen.gpu.pin.ok(d), Gen.gpu.pin.next(d, t, rest), g, Gen.gpu.pin.seen(d, seen))

def Gen.gpu.pin.def(+g: G, d: Decl) -> Bool:
  match d:
    case DDef{n, ps, body, ret}:
      Gen.gpu.pin(256n, True{}, [ret], g, Nil{})
    case other:
      False{}

def Gen.gpu.stub.pick(kernel: Bool, head: String, cpu: String, +name: String, +n: Nat, +pin: Bool) -> String:
  match kernel:
    case True{}:
      head ++ "V ga[] = {" ++ String.join(List.append(&2, String, Gen.gpu.params(n, 0), ["0"]), ", ") ++ "}, r;\nif (gpu_call(&K_PROG, " ++ K.label.name(name) ++ ", ga, " ++
        U32.show(U32.from_nat(n)) ++ ", " ++ Bool.pick(String, pin, "1", "0") ++ ", &r)) return r;\n" ++ cpu
    case False{}:
      head ++ cpu

def Gen.gpu.stub.go(+name: String, kernel: Bool, +n: Nat, +pin: Bool) -> String:
  Gen.gpu.stub.pick(kernel, "static V G_" ++ Gen.mangle(name) ++ "(" ++ Gen.cparams(Gen.gpu.params(n, 0)) ++ ") {\n",
    "return " ++ Gen.f(name) ++ "(" ++ Gen.gpu.args(n) ++ ");\n}\n", name, n, pin)

# G_f for a target f: on the device when it compiled, else on the CPU. The
# result may stay in the arena when its type allows (Gen.gpu.pin).
def Gen.gpu.stub(+g: G, +name: String, kernel: Bool) -> String:
  Gen.gpu.stub.go(name, kernel, U32.to_nat(K.kept(DInfo.mask(G.def(g, name)))), Gen.gpu.pin.def(g, G.body(g, name)))

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

def Ty.head(e: Core.Expr) -> String:
  match e:
    case Core.EVar{n}:
      n
    case Core.ETy{n, args}:
      n
    case Core.ECall{Core.EVar{n}, args}:
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
def Pick.lam.is(+e: Core.Expr) -> Bool:
  match e:
    case Core.ELam{p, b}:
      True{}
    case other:
      False{}

def Pick.name(+f: Core.Expr) -> Bool:
  match f:
    case Core.EVar{+n}:
      Str.eq(n, "Bool.pick")
    case other:
      False{}

def Pick.args(+as: List<&2, Core.Expr>) -> Bool:
  match as:
    case ty <> c <> a <> b <> Nil{}:
      Bool.and(Pick.lam.is(a), Pick.lam.is(b))
    case other:
      False{}

def Pick.lam(l: Core.Expr, x: Core.Expr) -> Core.Expr:
  match l:
    case Core.ELam{p, b}:
      Core.ELet{p, x, b}
    case other:
      Core.ECall{other, [x]}

def Pick.first(xs: List<&2, Core.Expr>) -> Core.Expr:
  match xs:
    case x <> t:
      x
    case Nil{}:
      Core.EErr{"pick"}

def Pick.build(as: List<&2, Core.Expr>, +x: Core.Expr) -> Core.Expr:
  match as:
    case ty <> c <> a <> b <> Nil{}:
      Core.EMatch{[c], [Core.ECase{[Core.PCtor{"True", Nil{}}], Pick.lam(a, x)}, Core.ECase{[Core.PCtor{"False", Nil{}}], Pick.lam(b, x)}]}
    case other:
      Core.ECall{Core.EVar{"Bool.pick"}, other}

def Pick.one(+xs: List<&2, Core.Expr>) -> Bool:
  Nat.is_eq(List.length(&2, Core.Expr, xs), 1n)

def Pick.hit(hit: Bool, +g: Core.Expr, +as: List<&2, Core.Expr>, +xs: List<&2, Core.Expr>) -> Core.Expr:
  match hit:
    case True{}:
      Pick.build(as, Pick.first(xs))
    case False{}:
      Core.ECall{Core.ECall{g, as}, xs}

def Pick.call(f: Core.Expr, +xs: List<&2, Core.Expr>) -> Core.Expr:
  match f:
    case Core.ECall{+g, +as}:
      Pick.hit(Bool.and(Pick.name(g), Bool.and(Pick.args(as), Pick.one(xs))), g, as, xs)
    case other:
      Core.ECall{other, xs}

# A call rebuilt from its parts, at the top of its node (top); below it,
# while its arguments are put back one by one, it stays as it is.
def Pick.top(top: Bool, r: Core.Expr) -> Core.Expr:
  match top:
    case True{}:
      match r:
        case Core.ECall{f, xs}:
          Pick.call(f, xs)
        case other:
          other
    case False{}:
      r

def Pick.go(e: Core.Expr, top: Bool) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Pick.top(top, Core.ECall{Pick.go(f, True{}), Nil{}})
        case a <> t:
          Pick.top(top, Expr.push(Pick.go(a, True{}), Pick.go(Core.ECall{f, t}, False{})))
    case Core.ECtor{k, args}:
      match args:
        case Nil{}:
          Core.ECtor{k, Nil{}}
        case a <> t:
          Expr.push(Pick.go(a, True{}), Pick.go(Core.ECtor{k, t}, True{}))
    case Core.EOp{op, a, b}:
      Core.EOp{op, Pick.go(a, True{}), Pick.go(b, True{})}
    case Core.ELam{p, b}:
      Core.ELam{p, Pick.go(b, True{})}
    case Core.ELet{p, v, b}:
      Core.ELet{p, Pick.go(v, True{}), Pick.go(b, True{})}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Pick.go(a, True{}), Pick.go(Core.EMatch{t, cases}, True{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Pick.go(c, True{}), Pick.go(Core.EMatch{Nil{}, t}, True{}))
    case Core.ECase{ps, b}:
      Core.ECase{ps, Pick.go(b, True{})}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Pick.go(x, True{})}
    case Core.EAnn{x, ty}:
      Core.EAnn{Pick.go(x, True{}), ty}
    case other:
      other

def Pick.expr(e: Core.Expr) -> Core.Expr:
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

# Scalar cells (C back end). Array.get, Array.set and Array.swap on an
# array of U32, F32, Bool or Char become Array.get%w, Array.set%w and
# Array.swap%w: natives of the same type whose cells are words, so a read
# takes no reference and a write drops none (reference counted), and the
# cell a read or a swap gives is a scalar (see GSLetGet). The type argument
# says which; the core IR erases it, so this runs before (Lo.program).
def Arrw.scalar(t: Core.Expr) -> Bool:
  match t:
    case Core.ETy{+n, a}:
      Bool.and(List.is_empty(&2, Core.Expr, a), Str.has(["U32", "F32", "Bool", "Char"], n))
    case Core.EVar{+n}:
      Str.has(["U32", "F32", "Bool", "Char"], n)
    case other:
      False{}

def Arrw.hit(+n: String, as: List<&2, Core.Expr>) -> Bool:
  match as:
    case t <> r:
      Bool.and(Str.has(["Array.get", "Array.set", "Array.swap"], n), Arrw.scalar(t))
    case Nil{}:
      False{}

def Arrw.name(f: Core.Expr, +as: List<&2, Core.Expr>) -> Core.Expr:
  match f:
    case Core.EVar{+n}:
      Core.EVar{Bool.pick(String, Arrw.hit(n, as), n ++ "%w", n)}
    case other:
      other

# (a call renamed at the top of its node, as Pick.top)
def Arrw.top(top: Bool, r: Core.Expr) -> Core.Expr:
  match top:
    case True{}:
      match r:
        case Core.ECall{f, +xs}:
          Core.ECall{Arrw.name(f, xs), xs}
        case other:
          other
    case False{}:
      r

def Arrw.go(e: Core.Expr, top: Bool) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Arrw.top(top, Core.ECall{Arrw.go(f, True{}), Nil{}})
        case a <> t:
          Arrw.top(top, Expr.push(Arrw.go(a, True{}), Arrw.go(Core.ECall{f, t}, False{})))
    case Core.ECtor{k, args}:
      match args:
        case Nil{}:
          Core.ECtor{k, Nil{}}
        case a <> t:
          Expr.push(Arrw.go(a, True{}), Arrw.go(Core.ECtor{k, t}, True{}))
    case Core.EOp{op, a, b}:
      Core.EOp{op, Arrw.go(a, True{}), Arrw.go(b, True{})}
    case Core.ELam{p, b}:
      Core.ELam{p, Arrw.go(b, True{})}
    case Core.ELet{p, v, b}:
      Core.ELet{p, Arrw.go(v, True{}), Arrw.go(b, True{})}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Arrw.go(a, True{}), Arrw.go(Core.EMatch{t, cases}, True{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Arrw.go(c, True{}), Arrw.go(Core.EMatch{Nil{}, t}, True{}))
    case Core.ECase{ps, b}:
      Core.ECase{ps, Arrw.go(b, True{})}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Arrw.go(x, True{})}
    case Core.EAnn{x, ty}:
      Core.EAnn{Arrw.go(x, True{}), ty}
    case other:
      other

# Each def's body rewritten; Array.get, Array.set and Array.swap each get
# their %w copy.
def Arrw.decls(ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case DDef{+name, +ps, +body, +ret} <> t:
      List.append(&2, Decl, Bool.pick(List<&2, Decl>, Str.has(["Array.get", "Array.set", "Array.swap"], name),
        [DDef{name, ps, body, ret}, DDef{name ++ "%w", ps, body, ret}], [DDef{name, ps, Arrw.go(body, True{}), ret}]),
        Arrw.decls(t))
    case d <> t:
      d <> Arrw.decls(t)

# Implicit parallelism (see Main.auto_par). Bend is pure, so the operands of
# one node (an operator's, a call's arguments, a constructor's fields) may
# run in any order; where two or more of them call back into the def (a
# tree recursion: fib(n - 1) + fib(n - 2), merge(msort(a), msort(b))),
# they become a parallel let, as if written a b = .. ..; the fork limit
# and a seq def's sequential clone then keep the small calls cheap. Only
# runtime operands move: a call's erased and dead arguments stay.

# Whether e names k anywhere (under lambdas too). A list field is its
# head, then the node rebuilt with the rest.
def Expr.mentions(e: Core.Expr, +k: String) -> Bool:
  match e:
    case Core.EVar{+n}:
      Str.eq(n, k)
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Expr.mentions(f, k)
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(Core.ECall{f, t}, k))(Unit{})
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          False{}
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(Core.ECtor{n, t}, k))(Unit{})
    case Core.ELam{p, b}:
      Expr.mentions(b, k)
    case Core.ELet{p, +v, +b}:
      Bool.pick(Unit -> Bool, Expr.mentions(v, k), u => True{}, u => Expr.mentions(b, k))(Unit{})
    case Core.EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(Core.EMatch{t, cases}, k))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case +c <> t:
              Bool.pick(Unit -> Bool, Expr.mentions(c, k), u => True{},
                u => Expr.mentions(Core.EMatch{Nil{}, t}, k))(Unit{})
    case Core.ECase{ps, b}:
      Expr.mentions(b, k)
    case Core.ESucc{n, x}:
      Expr.mentions(x, k)
    case Core.EOp{op, +a, +b}:
      Bool.pick(Unit -> Bool, Expr.mentions(a, k), u => True{}, u => Expr.mentions(b, k))(Unit{})
    case Core.EAnn{x, ty}:
      Expr.mentions(x, k)
    case other:
      False{}

# Whether k is free in e: as Expr.mentions, but a pattern that binds k hides
# its scope.
def Expr.free(e: Core.Expr, +k: String) -> Bool:
  match e:
    case Core.EVar{+n}:
      Str.eq(n, k)
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Expr.free(f, k)
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.free(a, k), u => True{}, u => Expr.free(Core.ECall{f, t}, k))(Unit{})
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          False{}
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.free(a, k), u => True{}, u => Expr.free(Core.ECtor{n, t}, k))(Unit{})
    case Core.ELam{p, +b}:
      Bool.pick(Unit -> Bool, Str.has(Pat.vars(p, Nil{}), k), u => False{}, u => Expr.free(b, k))(Unit{})
    case Core.ELet{p, +v, +b}:
      Bool.pick(Unit -> Bool, Expr.free(v, k), u => True{},
        u => Bool.pick(Unit -> Bool, Str.has(Pat.vars(p, Nil{}), k), w => False{}, w => Expr.free(b, k))(Unit{}))(Unit{})
    case Core.EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          Bool.pick(Unit -> Bool, Expr.free(a, k), u => True{}, u => Expr.free(Core.EMatch{t, cases}, k))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case +c <> t:
              Bool.pick(Unit -> Bool, Expr.free(c, k), u => True{},
                u => Expr.free(Core.EMatch{Nil{}, t}, k))(Unit{})
    case Core.ECase{ps, +b}:
      Bool.pick(Unit -> Bool, Str.has(Pats.vars(ps, Nil{}), k), u => False{}, u => Expr.free(b, k))(Unit{})
    case Core.ESucc{n, x}:
      Expr.free(x, k)
    case Core.EOp{op, +a, +b}:
      Bool.pick(Unit -> Bool, Expr.free(a, k), u => True{}, u => Expr.free(b, k))(Unit{})
    case Core.EAnn{x, ty}:
      Expr.free(x, k)
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
def Par.has(+g: G, +d: String, e: Core.Expr) -> Bool:
  match e:
    case Core.ECall{f, args}:
      match f:
        case Core.EVar{+n}:
          match args:
            case Nil{}:
              Par.rec(g, d, n)
            case +a <> t:
              Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, Core.ECall{Core.EVar{n}, t}))(Unit{})
        case other:
          match args:
            case Nil{}:
              Par.has(g, d, other)
            case +a <> t:
              Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, Core.ECall{other, t}))(Unit{})
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          False{}
        case +a <> t:
          Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, Core.ECtor{n, t}))(Unit{})
    case Core.ELet{p, +v, +b}:
      Bool.pick(Unit -> Bool, Par.has(g, d, v), u => True{}, u => Par.has(g, d, b))(Unit{})
    case Core.EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, Core.EMatch{t, cases}))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case +c <> t:
              Bool.pick(Unit -> Bool, Par.has(g, d, c), u => True{}, u => Par.has(g, d, Core.EMatch{Nil{}, t}))(Unit{})
    case Core.ECase{ps, b}:
      Par.has(g, d, b)
    case Core.ESucc{n, x}:
      Par.has(g, d, x)
    case Core.EOp{op, +a, +b}:
      Bool.pick(Unit -> Bool, Par.has(g, d, a), u => True{}, u => Par.has(g, d, b))(Unit{})
    case Core.EAnn{x, ty}:
      Par.has(g, d, x)
    case other:
      False{}

# The operands that may move: all of a closure's or a constructor's, a
# def's kept ones (and any past its parameters), none of a dead def's.
def Par.live.mask(xs: List<&2, Core.Expr>, bs: List<&2, Bool>) -> List<&2, Bool>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      match bs:
        case Nil{}:
          True{} <> Par.live.mask(t, Nil{})
        case b <> mt:
          b <> Par.live.mask(t, mt)

def Par.all(+b: Bool, xs: List<&2, Core.Expr>) -> List<&2, Bool>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      b <> Par.all(b, t)

def Par.live.info(i: DInfo, +xs: List<&2, Core.Expr>) -> List<&2, Bool>:
  DInfo{+kind, mask} = i
  Bool.pick(List<&2, Bool>, U32.is_eq(kind, 3), Par.all(False{}, xs),
    Bool.pick(List<&2, Bool>, U32.is_eq(kind, 4), Par.all(True{}, xs), Par.live.mask(xs, mask)))

def Par.live(+g: G, f: Core.Expr, +xs: List<&2, Core.Expr>) -> List<&2, Bool>:
  match f:
    case Core.EVar{+n}:
      Par.live.info(G.def(g, n), xs)
    case other:
      Par.all(True{}, xs)

# Which operands move: live ones that run a recursive call.
def Par.marks(+g: G, +d: String, live: List<&2, Bool>, xs: List<&2, Core.Expr>) -> List<&2, Bool>:
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
def Par.pats(ms: List<&2, Bool>, +n: U32, +j: Nat) -> List<&2, Core.Pat>:
  match ms:
    case Nil{}:
      Nil{}
    case True{} <> t:
      Core.PVar{Par.name(n, j)} <> Par.pats(t, n, 1n+j)
    case False{} <> t:
      Par.pats(t, n, j)

def Par.vals(ms: List<&2, Bool>, xs: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match ms xs:
    case True{} <> mt x <> xt:
      x <> Par.vals(mt, xt)
    case False{} <> mt x <> xt:
      Par.vals(mt, xt)
    case q ys:
      Nil{}

def Par.rest(ms: List<&2, Bool>, xs: List<&2, Core.Expr>, +n: U32, +j: Nat) -> List<&2, Core.Expr>:
  match ms xs:
    case True{} <> mt x <> xt:
      Core.EVar{Par.name(n, j)} <> Par.rest(mt, xt, n, 1n+j)
    case False{} <> mt x <> xt:
      x <> Par.rest(mt, xt, n, j)
    case q ys:
      ys

def Par.wrap.if(hit: Bool, +n: U32, +ms: List<&2, Bool>, +xs: List<&2, Core.Expr>, k: List<&2, Core.Expr> -> Core.Expr) ->
  Core.Expr:
  match hit:
    case True{}:
      Core.ELet{Core.PCtor{"%par", Par.pats(ms, n, 0n)}, Core.ECtor{"%par", Par.vals(ms, xs)}, k(Par.rest(ms, xs, n, 0n))}
    case False{}:
      k(xs)

def Par.wrap(+n: U32, +ms: List<&2, Bool>, +xs: List<&2, Core.Expr>, k: List<&2, Core.Expr> -> Core.Expr) -> Core.Expr:
  Par.wrap.if(Nat.is_gt(Par.count(ms), 1n), n, ms, xs, k)

# An annotated operator's parallel let goes outside the annotation, which
# only types the operator: {(a + b : U32)} with a, b moved.
def Par.ann(x: Core.Expr, +ty: String) -> Core.Expr:
  match x:
    case Core.ELet{Core.PCtor{+k, +ps}, +v, +b}:
      Bool.pick(Core.Expr, Str.eq(k, "%par"), Core.ELet{Core.PCtor{k, ps}, v, Core.EAnn{b, ty}}, Core.EAnn{Core.ELet{Core.PCtor{k, ps}, v, b}, ty})
    case other:
      Core.EAnn{other, ty}

def Par.call(+g: G, +d: String, +n: U32, +f: Core.Expr, +xs: List<&2, Core.Expr>) -> Core.Expr:
  Par.wrap(n, Par.marks(g, d, Par.live(g, f, xs), xs), xs, as => Core.ECall{f, as})

def Par.ctor(+g: G, +d: String, +n: U32, +k: String, +xs: List<&2, Core.Expr>) -> Core.Expr:
  Bool.pick(Core.Expr, Str.eq(k, "%par"), Core.ECtor{k, xs},
    Par.wrap(n, Par.marks(g, d, Par.all(True{}, xs), xs), xs, as => Core.ECtor{k, as}))

def Par.op.k(+op: String, xs: List<&2, Core.Expr>) -> Core.Expr:
  match xs:
    case a <> b <> Nil{}:
      Core.EOp{op, a, b}
    case other:
      Core.EErr{"auto-par: an operator of two operands"}

def Par.op(+g: G, +d: String, +n: U32, +op: String, a: Core.Expr, b: Core.Expr) -> Core.Expr:
  +xs = {[a, b] : List<&2, Core.Expr>}
  Par.wrap(n, Par.marks(g, d, Par.all(True{}, xs), xs), xs, as => Par.op.k(op, as))

# A call or a constructor rebuilt from its parts: grouped at the top of
# its node (top); below it, while its operands are put back one by one, it
# stays as it is.
def Par.top(top: Bool, +g: G, +d: String, +n: U32, r: Core.Expr) -> Core.Expr:
  match top:
    case True{}:
      match r:
        case Core.ECall{+f, +xs}:
          Par.call(g, d, n, f, xs)
        case Core.ECtor{+k, +xs}:
          Par.ctor(g, d, n, k, xs)
        case other:
          other
    case False{}:
      r

# e with its recursive operand groups parallel (n: the nesting depth, which
# keeps the names of nested groups apart).
def Par.go(+g: G, +d: String, e: Core.Expr, +n: U32, top: Bool) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Par.top(top, g, d, n, Core.ECall{Par.go(g, d, f, U32.inc(n), True{}), Nil{}})
        case a <> t:
          Par.top(top, g, d, n, Expr.push(Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, Core.ECall{f, t}, n, False{})))
    case Core.ECtor{k, args}:
      match args:
        case Nil{}:
          Par.top(top, g, d, n, Core.ECtor{k, Nil{}})
        case a <> t:
          Par.top(top, g, d, n, Expr.push(Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, Core.ECtor{k, t}, n, False{})))
    case Core.EOp{op, a, b}:
      Par.op(g, d, n, op, Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, b, U32.inc(n), True{}))
    case Core.ELam{p, b}:
      Core.ELam{p, Par.go(g, d, b, U32.inc(n), True{})}
    case Core.ELet{p, v, b}:
      Core.ELet{p, Par.go(g, d, v, U32.inc(n), True{}), Par.go(g, d, b, U32.inc(n), True{})}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Par.go(g, d, a, U32.inc(n), True{}), Par.go(g, d, Core.EMatch{t, cases}, n, True{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Par.go(g, d, c, U32.inc(n), True{}), Par.go(g, d, Core.EMatch{Nil{}, t}, n, True{}))
    case Core.ECase{ps, b}:
      Core.ECase{ps, Par.go(g, d, b, U32.inc(n), True{})}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Par.go(g, d, x, U32.inc(n), True{})}
    case Core.EAnn{x, ty}:
      Par.ann(Par.go(g, d, x, U32.inc(n), True{}), ty)
    case other:
      other

def Par.expr(+g: G, +d: String, +n: U32, e: Core.Expr) -> Core.Expr:
  Par.go(g, d, e, n, True{})

# Independent calls in a block. A block is a def's body, a case's or a
# lambda's: a chain of lets and the expression they end in. A call is
# heavy when it calls a def (not a native or an effect) that recurses
# (Par.rec) or forks (fs: a def with a parallel let). The heavy calls of a block that no let of it feeds may
# run at once: two or more become a parallel let, at the place of the
# block where the most of them can move (the top, or after the last let
# they read). A call under a lambda or a match's cases stays, as do a
# parallel let's values and a call that ends the block (a loop's tail
# call). As any parallel let, it forks only above the frontier.
def Par.heavy(+g: G, +d: String, +fs: List<&2, String>, +f: String) -> Bool:
  +k = DInfo.kind(G.def(g, f))
  Bool.and(Bool.not(Bool.or(U32.is_eq(k, 1), U32.is_eq(k, 2))), Bool.or(Par.rec(g, d, f), Str.has(fs, f)))

# Whether e reads one of the names s.
def Par.dep(s: List<&2, String>, +e: Core.Expr) -> Bool:
  match s:
    case Nil{}:
      False{}
    case +k <> t:
      Bool.pick(Unit -> Bool, Expr.free(e, k), u => True{}, u => Par.dep(t, e))(Unit{})

# Whether the call of f on args may move: heavy, and reading none of s.
def Par.ok(+g: G, +d: String, +fs: List<&2, String>, +s: List<&2, String>, +f: String,
  +args: List<&2, Core.Expr>) -> Bool:
  Bool.and(Par.heavy(g, d, fs, f), Bool.not(Par.dep(s, Core.ECall{Core.EVar{f}, args})))

# The calls of e that move, in order, before acc (top: e is a whole node,
# not a call or constructor rebuilt with the rest of its operands; tl: e
# ends the block).
def Par.calls(e: Core.Expr, top: Bool, tl: Bool, +g: G, +d: String, +fs: List<&2, String>,
  +s: List<&2, String>, +acc: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match e:
    case Core.ECall{f, args}:
      match f:
        case Core.EVar{+n}:
          match args:
            case Nil{}:
              Bool.pick(List<&2, Core.Expr>, Bool.and(Bool.and(top, Bool.not(tl)), Par.heavy(g, d, fs, n)),
                Core.ECall{Core.EVar{n}, Nil{}} <> acc, acc)
            case +a <> +t:
              Bool.pick(Unit -> List<&2, Core.Expr>, Bool.and(Bool.and(top, Bool.not(tl)), Par.ok(g, d, fs, s, n, a <> t)),
                u => Core.ECall{Core.EVar{n}, a <> t} <> acc,
                u => Par.calls(a, True{}, False{}, g, d, fs, s,
                  Par.calls(Core.ECall{Core.EVar{n}, t}, False{}, False{}, g, d, fs, s, acc)))(Unit{})
        case other:
          match args:
            case Nil{}:
              Par.calls(other, True{}, False{}, g, d, fs, s, acc)
            case a <> t:
              Par.calls(a, True{}, False{}, g, d, fs, s, Par.calls(Core.ECall{other, t}, False{}, False{}, g, d, fs, s, acc))
    case Core.ECtor{+k, args}:
      match args:
        case Nil{}:
          acc
        case +a <> +t:
          Bool.pick(Unit -> List<&2, Core.Expr>, Bool.and(top, Str.eq(k, "%par")), u => acc,
            u => Par.calls(a, True{}, False{}, g, d, fs, s,
              Par.calls(Core.ECtor{k, t}, False{}, False{}, g, d, fs, s, acc)))(Unit{})
    case Core.EOp{op, a, b}:
      Par.calls(a, True{}, False{}, g, d, fs, s, Par.calls(b, True{}, False{}, g, d, fs, s, acc))
    case Core.ELet{p, v, b}:
      Par.calls(v, True{}, False{}, g, d, fs, s, Par.calls(b, True{}, tl, g, d, fs, Pat.vars(p, s), acc))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case Nil{}:
          acc
        case a <> t:
          Par.calls(a, True{}, False{}, g, d, fs, s, Par.calls(Core.EMatch{t, cases}, True{}, False{}, g, d, fs, s, acc))
    case Core.ESucc{k, x}:
      Par.calls(x, True{}, False{}, g, d, fs, s, acc)
    case Core.EAnn{x, ty}:
      Par.calls(x, True{}, tl, g, d, fs, s, acc)
    case other:
      acc

def Par.ncalls(+e: Core.Expr, +g: G, +d: String, +fs: List<&2, String>, +s: List<&2, String>) -> Nat:
  List.length(&2, Core.Expr, Par.calls(e, True{}, False{}, g, d, fs, s, Nil{}))

def Par.bname(+n: U32, +j: Nat) -> String:
  "_pb" ++ U32.show(n) ++ "_" ++ Nat.show(j)

# e with the calls Par.calls lists replaced by the names _pbN_J, J from j.
def Par.sub(e: Core.Expr, top: Bool, tl: Bool, +j: Nat, +n: U32, +g: G, +d: String,
  +fs: List<&2, String>, +s: List<&2, String>) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match f:
        case Core.EVar{+x}:
          match args:
            case Nil{}:
              Bool.pick(Core.Expr, Bool.and(Bool.and(top, Bool.not(tl)), Par.heavy(g, d, fs, x)),
                Core.EVar{Par.bname(n, j)}, Core.ECall{Core.EVar{x}, Nil{}})
            case +a <> +t:
              Bool.pick(Unit -> Core.Expr, Bool.and(Bool.and(top, Bool.not(tl)), Par.ok(g, d, fs, s, x, a <> t)),
                u => Core.EVar{Par.bname(n, j)},
                u => Expr.push(Par.sub(a, True{}, False{}, j, n, g, d, fs, s),
                  Par.sub(Core.ECall{Core.EVar{x}, t}, False{}, False{}, Nat.add(j, Par.ncalls(a, g, d, fs, s)), n, g, d, fs, s)))(Unit{})
        case other:
          match args:
            case Nil{}:
              Core.ECall{Par.sub(other, True{}, False{}, j, n, g, d, fs, s), Nil{}}
            case +a <> t:
              Expr.push(Par.sub(a, True{}, False{}, j, n, g, d, fs, s),
                Par.sub(Core.ECall{other, t}, False{}, False{}, Nat.add(j, Par.ncalls(a, g, d, fs, s)), n, g, d, fs, s))
    case Core.ECtor{+k, args}:
      match args:
        case Nil{}:
          Core.ECtor{k, Nil{}}
        case +a <> +t:
          Bool.pick(Unit -> Core.Expr, Bool.and(top, Str.eq(k, "%par")), u => Core.ECtor{k, a <> t},
            u => Expr.push(Par.sub(a, True{}, False{}, j, n, g, d, fs, s),
              Par.sub(Core.ECtor{k, t}, False{}, False{}, Nat.add(j, Par.ncalls(a, g, d, fs, s)), n, g, d, fs, s)))(Unit{})
    case Core.EOp{op, +a, b}:
      Core.EOp{op, Par.sub(a, True{}, False{}, j, n, g, d, fs, s),
        Par.sub(b, True{}, False{}, Nat.add(j, Par.ncalls(a, g, d, fs, s)), n, g, d, fs, s)}
    case Core.ELet{+p, +v, b}:
      Core.ELet{p, Par.sub(v, True{}, False{}, j, n, g, d, fs, s),
        Par.sub(b, True{}, tl, Nat.add(j, Par.ncalls(v, g, d, fs, s)), n, g, d, fs, Pat.vars(p, s))}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case Nil{}:
          Core.EMatch{Nil{}, cases}
        case +a <> t:
          Expr.push(Par.sub(a, True{}, False{}, j, n, g, d, fs, s),
            Par.sub(Core.EMatch{t, cases}, True{}, False{}, Nat.add(j, Par.ncalls(a, g, d, fs, s)), n, g, d, fs, s))
    case Core.ESucc{k, x}:
      Core.ESucc{k, Par.sub(x, True{}, False{}, j, n, g, d, fs, s)}
    case Core.EAnn{x, ty}:
      Core.EAnn{Par.sub(x, True{}, tl, j, n, g, d, fs, s), ty}
    case other:
      other

# The names a block's lets bind, from e on.
def Par.svars(e: Core.Expr, acc: List<&2, String>) -> List<&2, String>:
  match e:
    case Core.ELet{p, v, b}:
      Par.svars(b, Pat.vars(p, acc))
    case other:
      acc

# How many calls may move to the top of the block e (none of its lets feeds them).
def Par.here(+e: Core.Expr, +g: G, +d: String, +fs: List<&2, String>) -> Nat:
  List.length(&2, Core.Expr, Par.calls(e, True{}, True{}, g, d, fs, Par.svars(e, Nil{}), Nil{}))

# The most calls that may move to one place of the block e.
def Par.most(e: Core.Expr, +g: G, +d: String, +fs: List<&2, String>) -> Nat:
  match e:
    case Core.ELet{+p, +v, +b}:
      Nat.max(Par.here(Core.ELet{p, v, b}, g, d, fs), Par.most(b, g, d, fs))
    case other:
      Par.here(other, g, d, fs)

def Par.bpats(k: Nat, +n: U32, +j: Nat) -> List<&2, Core.Pat>:
  match k:
    case 0n:
      Nil{}
    case 1n+r:
      Core.PVar{Par.bname(n, j)} <> Par.bpats(r, n, 1n+j)

# The parallel let at the top of e.
def Par.put(+e: Core.Expr, +n: U32, +g: G, +d: String, +fs: List<&2, String>) -> Core.Expr:
  +s = Par.svars(e, Nil{})
  +cs = Par.calls(e, True{}, True{}, g, d, fs, s, Nil{})
  Core.ELet{Core.PCtor{"%par", Par.bpats(List.length(&2, Core.Expr, cs), n, 0n)}, Core.ECtor{"%par", cs},
    Par.sub(e, True{}, True{}, 0n, n, g, d, fs, s)}

# The parallel let at the first place of e where m calls may move.
def Par.at(e: Core.Expr, +m: Nat, +n: U32, +g: G, +d: String, +fs: List<&2, String>) -> Core.Expr:
  match e:
    case Core.ELet{+p, +v, +b}:
      Bool.pick(Unit -> Core.Expr, Nat.is_eq(Par.here(Core.ELet{p, v, b}, g, d, fs), m),
        u => Par.put(Core.ELet{p, v, b}, n, g, d, fs), u => Core.ELet{p, v, Par.at(b, m, n, g, d, fs)})(Unit{})
    case other:
      Par.put(other, n, g, d, fs)

def Par.blk(+e: Core.Expr, +n: U32, +g: G, +d: String, +fs: List<&2, String>) -> Core.Expr:
  +m = Par.most(e, g, d, fs)
  Bool.pick(Unit -> Core.Expr, Nat.is_gt(m, 1n), u => Par.at(e, m, n, g, d, fs), u => e)(Unit{})

# e with each block's independent calls parallel, inner blocks first (n:
# the nesting depth, which keeps the names of nested blocks apart).
def Par.hoist(e: Core.Expr, +n: U32, +g: G, +d: String, +fs: List<&2, String>) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{Par.hoist(f, U32.inc(n), g, d, fs), Nil{}}
        case a <> t:
          Expr.push(Par.hoist(a, U32.inc(n), g, d, fs), Par.hoist(Core.ECall{f, t}, n, g, d, fs))
    case Core.ECtor{k, args}:
      match args:
        case Nil{}:
          Core.ECtor{k, Nil{}}
        case a <> t:
          Expr.push(Par.hoist(a, U32.inc(n), g, d, fs), Par.hoist(Core.ECtor{k, t}, n, g, d, fs))
    case Core.EOp{op, a, b}:
      Core.EOp{op, Par.hoist(a, U32.inc(n), g, d, fs), Par.hoist(b, U32.inc(n), g, d, fs)}
    case Core.ELam{p, b}:
      Core.ELam{p, Par.blk(Par.hoist(b, U32.inc(n), g, d, fs), U32.inc(n), g, d, fs)}
    case Core.ELet{p, v, b}:
      Core.ELet{p, Par.hoist(v, U32.inc(n), g, d, fs), Par.hoist(b, U32.inc(n), g, d, fs)}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Par.hoist(a, U32.inc(n), g, d, fs), Par.hoist(Core.EMatch{t, cases}, n, g, d, fs))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Par.hoist(c, U32.inc(n), g, d, fs), Par.hoist(Core.EMatch{Nil{}, t}, n, g, d, fs))
    case Core.ECase{ps, b}:
      Core.ECase{ps, Par.blk(Par.hoist(b, U32.inc(n), g, d, fs), U32.inc(n), g, d, fs)}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Par.hoist(x, U32.inc(n), g, d, fs)}
    case Core.EAnn{x, ty}:
      Core.EAnn{Par.hoist(x, U32.inc(n), g, d, fs), ty}
    case other:
      other

# Whether e has a parallel let.
def Par.forks.e(e: Core.Expr) -> Bool:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Par.forks.e(f)
        case a <> t:
          Bool.or(Par.forks.e(a), Par.forks.e(Core.ECall{f, t}))
    case Core.ECtor{k, args}:
      match args:
        case Nil{}:
          False{}
        case a <> t:
          Bool.or(Par.forks.e(a), Par.forks.e(Core.ECtor{k, t}))
    case Core.EOp{op, a, b}:
      Bool.or(Par.forks.e(a), Par.forks.e(b))
    case Core.ELam{p, b}:
      Par.forks.e(b)
    case Core.ELet{p, v, b}:
      match p:
        case Core.PCtor{+k, ps}:
          Bool.or(Str.eq(k, "%par"), Bool.or(Par.forks.e(v), Par.forks.e(b)))
        case other:
          Bool.or(Par.forks.e(v), Par.forks.e(b))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Bool.or(Par.forks.e(a), Par.forks.e(Core.EMatch{t, cases}))
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case c <> t:
              Bool.or(Par.forks.e(c), Par.forks.e(Core.EMatch{Nil{}, t}))
    case Core.ECase{ps, b}:
      Par.forks.e(b)
    case Core.ESucc{k, x}:
      Par.forks.e(x)
    case Core.EAnn{x, ty}:
      Par.forks.e(x)
    case other:
      False{}

# The defs that fork.
def Par.forks(ds: List<&2, Decl>) -> List<&2, String>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> +t:
      match d:
        case DDef{+name, ps, body, ret}:
          Bool.pick(List<&2, String>, Par.forks.e(body), name <> Par.forks(t), Par.forks(t))
        case other:
          Par.forks(t)

def Par.decl(+g: G, +fs: List<&2, String>, d: Decl) -> Decl:
  match d:
    case DDef{+name, ps, body, ret}:
      DDef{name, ps, Par.expr(g, name, 0, Par.blk(Par.hoist(body, 1, g, name, fs), 0, g, name, fs)), ret}
    case other:
      other

def Par.decls(+g: G, +fs: List<&2, String>, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      Par.decl(g, fs, d) <> Par.decls(g, fs, t)

# Rounds until the defs that fork (fs) stop growing (at most k): a round
# that moves calls of defs that fork may make more defs fork.
def Par.rounds(k: Nat, +g: G, +fs: List<&2, String>, +ds: List<&2, Decl>) -> List<&2, Decl>:
  match k:
    case 0n:
      Par.decls(g, fs, ds)
    case 1n+r:
      +out = Par.decls(g, fs, ds)
      +fs2 = Par.forks(out)
      Bool.pick(Unit -> List<&2, Decl>, Nat.is_gt(List.length(&2, String, fs2), List.length(&2, String, fs)),
        u => Par.rounds(r, g, fs2, ds), u => out)(Unit{})

def Par.auto(on: Bool, +ds: List<&2, Decl>) -> List<&2, Decl>:
  match on:
    case True{}:
      Par.rounds(6n, G.new(ds), Nil{}, ds)
    case False{}:
      ds

# Unboxed parameters. A parameter whose type has one constructor of two to eight fields (a
# record, a pair) can go as its fields. Such a def f gets a worker, f%u,
# that takes the fields as parameters, and f becomes a wrapper that opens
# the node and calls f%u (closures and partial calls still use f). In f%u
# the parameter is its constructor rebuilt from the fields, which a pattern
# then opens again without building it (Unb.known). A full call of f passes
# a constructor argument's fields as they are, and opens any other argument
# with a let around the call (for Array.get's pair, the code generator then
# reads the cell without building the pair: see GSLetUnb). A parameter is
# unboxed when each use of it is a pattern or an argument of a worker.
# BEND_UNBOX=0 turns this off.

# A flat type: its constructor, and its fields' type heads.
type Unb is Data:
  Unb{ctor: String, tys: List<&2, String>}

def Unb.none() -> Unb:
  Unb{"", Nil{}}

def Unb.is(u: Unb) -> Bool:
  Unb{k, ts} = u
  Bool.not(String.is_empty(k))

def Unb.arity(u: Unb) -> Nat:
  Unb{k, ts} = u
  List.length(&2, String, ts)

def Unb.tys.of(u: Unb) -> List<&2, String>:
  Unb{k, ts} = u
  ts

def Unb.ctor.of(u: Unb) -> String:
  Unb{k, ts} = u
  k

def Unb.tys(fs: List<&2, Field>) -> List<&2, String>:
  match fs:
    case Nil{}:
      Nil{}
    case Field{n, t} <> r:
      P.phead(t) <> Unb.tys(r)

def Unb.fits(+fs: List<&2, Field>) -> Bool:
  +n = List.length(&2, Field, fs)
  Bool.and(Nat.is_ge(n, 2n), Nat.is_le(n, 8n))

def Unb.type.put(ok: Bool, +key: String, u: Unb, m: Map<&2, Unb>) -> Map<&2, Unb>:
  match ok:
    case True{}:
      Map.set(&2, Unb, m, key, u)
    case False{}:
      m

# The flat types, by type name ("&" for a pair) or, with ctor, by
# constructor name.
def Unb.type(+ctor: Bool, +name: String, cs: List<&2, Ctor>, m: Map<&2, Unb>) -> Map<&2, Unb>:
  match cs:
    case Ctor{+k, +fs} <> Nil{}:
      Unb.type.put(Unb.fits(fs), Bool.pick(String, ctor, k, Bool.pick(String, Str.eq(name, "Sigma"), "&", name)),
        Unb{k, Unb.tys(fs)}, m)
    case other:
      m

def Unb.types(+ctor: Bool, ds: List<&2, Decl>, m: Map<&2, Unb>) -> Map<&2, Unb>:
  match ds:
    case Nil{}:
      m
    case DType{name, ps, cs} <> t:
      Unb.types(ctor, t, Unb.type(ctor, name, cs, m))
    case d <> t:
      Unb.types(ctor, t, m)

def Unb.find(+m: Map<&2, Unb>, +t: String) -> Unb:
  G.get(Unb, Unb.none(), m, t)

# A parameter whose type is no flat one by name (a pair's component, as a
# worker takes it, say) is of the type of a flat constructor that a let in
# the body opens it with (x not rebound on the way).
def Unb.infer.n(+u: Unb, +n: Nat) -> Unb:
  Bool.pick(Unb, Bool.and(Unb.is(u), Nat.is_eq(Unb.arity(u), n)), u, Unb.none())

def Unb.infer.or.go(hit: Bool, a: Unb, b: Unb) -> Unb:
  match hit:
    case True{}:
      a
    case False{}:
      b

def Unb.infer.or(+a: Unb, b: Unb) -> Unb:
  Unb.infer.or.go(Unb.is(a), a, b)

def Unb.infer.v(v: Core.Expr, +x: String, +cm: Map<&2, Unb>, +k: String, +n: Nat) -> Unb:
  match v:
    case Core.EVar{+y}:
      Bool.pick(Unb, Str.eq(x, y), Unb.infer.n(Unb.find(cm, k), n), Unb.none())
    case other:
      Unb.none()

def Unb.infer.let(p: Core.Pat, v: Core.Expr, +x: String, +cm: Map<&2, Unb>) -> Unb:
  match p:
    case Core.PCtor{+k, qs}:
      Unb.infer.v(v, x, cm, k, List.length(&2, Core.Pat, qs))
    case other:
      Unb.none()

# The name x has in a let's body: the variable a let y = x binds, x when
# the let does not bind it again, else none ("").
def Unb.infer.alias.v(v: Core.Expr, +x: String, +y: String) -> String:
  match v:
    case Core.EVar{+z}:
      Bool.pick(String, Str.eq(z, x), y, Bool.pick(String, Str.eq(y, x), "", x))
    case other:
      Bool.pick(String, Str.eq(y, x), "", x)

def Unb.infer.next(p: Core.Pat, v: Core.Expr, +x: String) -> String:
  match p:
    case Core.PVar{+y}:
      Unb.infer.alias.v(v, x, y)
    case other:
      Bool.pick(String, Str.has(Pat.vars(other, Nil{}), x), "", x)

def Unb.infer(e: Core.Expr, +x: String, +cm: Map<&2, Unb>) -> Unb:
  match e:
    case Core.ELet{+pt, +v, b}:
      +y = Unb.infer.next(pt, v, x)
      Unb.infer.or(Unb.infer.let(pt, v, x, cm), Unb.infer.or(Unb.infer(v, x, cm),
        Bool.pick(Unit -> Unb, String.is_empty(y), u => Unb.none(), u => Unb.infer(b, y, cm))(Unit{})))
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Unb.none()
        case a <> t:
          Unb.infer.or(Unb.infer(a, x, cm), Unb.infer(Core.ECall{f, t}, x, cm))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Unb.none()
        case a <> t:
          Unb.infer.or(Unb.infer(a, x, cm), Unb.infer(Core.ECtor{n, t}, x, cm))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Unb.infer.or(Unb.infer(a, x, cm), Unb.infer(Core.EMatch{t, cases}, x, cm))
        case Nil{}:
          match cases:
            case Nil{}:
              Unb.none()
            case c <> t:
              Unb.infer.or(Unb.infer(c, x, cm), Unb.infer(Core.EMatch{Nil{}, t}, x, cm))
    case Core.ECase{+ps, b}:
      Bool.pick(Unb, Str.has(Pats.vars(ps, Nil{}), x), Unb.none(), Unb.infer(b, x, cm))
    case Core.EAnn{y, ty}:
      Unb.infer(y, x, cm)
    case other:
      Unb.none()

# Whether e answers the variable x itself (in a tail position, x not
# rebound on the way): then x is of the def's result type.
def Unb.tail(e: Core.Expr, +x: String) -> Bool:
  match e:
    case Core.EVar{+y}:
      Str.eq(x, y)
    case Core.ELet{pt, v, b}:
      Bool.and(Bool.not(Str.has(Pat.vars(pt, Nil{}), x)), Unb.tail(b, x))
    case Core.EMatch{scrs, cases}:
      match cases:
        case Nil{}:
          False{}
        case c <> t:
          Bool.or(Unb.tail(c, x), Unb.tail(Core.EMatch{scrs, t}, x))
    case Core.ECase{+ps, b}:
      Bool.and(Bool.not(Str.has(Pats.vars(ps, Nil{}), x)), Unb.tail(b, x))
    case Core.EAnn{y, ty}:
      Unb.tail(y, x)
    case other:
      False{}

def Unb.cand.two(+u: Unb, +x: String, +ts: Map<&2, Unb>, +rt: String, +body: Core.Expr) -> Unb:
  Bool.pick(Unit -> Unb, Bool.or(Unb.is(u), Bool.not(Unb.tail(body, x))), w => u, w => Unb.find(ts, rt))(Unit{})

def Unb.cand.one(+u: Unb, +x: String, +ts: Map<&2, Unb>, +cm: Map<&2, Unb>, +rt: String, +body: Core.Expr) -> Unb:
  Bool.pick(Unit -> Unb, Unb.is(u), w => u, w => Unb.cand.two(Unb.infer(body, x, cm), x, ts, rt, body))(Unit{})

# A def's parameters that may go unboxed: plain or shared, of a flat type
# (or of one Unb.infer finds).
def Unb.cands(+ts: Map<&2, Unb>, +cm: Map<&2, Unb>, +rt: String, +body: Core.Expr, ps: List<&2, Core.Param>) -> List<&2, Unb>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Param{+x, +m, +t} <> r:
      Bool.pick(Unb, Bool.or(U32.is_zero(m), U32.is_eq(m, 2)), Unb.cand.one(Unb.find(ts, t), x, ts, cm, rt, body), Unb.none()) <>
        Unb.cands(ts, cm, rt, body, r)

def Unb.any(us: List<&2, Unb>) -> Bool:
  match us:
    case Nil{}:
      False{}
    case u <> t:
      Bool.or(Unb.is(u), Unb.any(t))

def Unb.ok.def(+name: String, +ret: Core.Expr, +laws: Map<&2, Decl>) -> Bool:
  Bool.not(Bool.or(Bool.or(G.is_native(name), Str.eq(name, "main")),
    Bool.or(G.erased_ty(Ty.head(ret)), Pair.snd(Map<&2, Decl>, Bool, Map.has(&2, Decl, laws, name)))))

def Unb.put(ok: Bool, +name: String, us: List<&2, Unb>, m: Map<&2, List<&2, Unb>>) ->
  Map<&2, List<&2, Unb>>:
  match ok:
    case True{}:
      Map.set(&2, List<&2, Unb>, m, name, us)
    case False{}:
      m

def Unb.cand(+name: String, +ret: Core.Expr, +laws: Map<&2, Decl>, +us: List<&2, Unb>,
  m: Map<&2, List<&2, Unb>>) -> Map<&2, List<&2, Unb>>:
  Unb.put(Bool.and(Unb.ok.def(name, ret, laws), Unb.any(us)), name, us, m)

def Unb.cands.all(+ts: Map<&2, Unb>, +cm: Map<&2, Unb>, +laws: Map<&2, Decl>, ds: List<&2, Decl>,
  m: Map<&2, List<&2, Unb>>) -> Map<&2, List<&2, Unb>>:
  match ds:
    case Nil{}:
      m
    case DDef{+name, ps, body, +ret} <> t:
      Unb.cands.all(ts, cm, laws, t, Unb.cand(name, ret, laws, Unb.cands(ts, cm, Ty.head(ret), body, ps), m))
    case d <> t:
      Unb.cands.all(ts, cm, laws, t, m)

# A def's worker flags (Nil when it has no worker).
def Unb.flags(+wm: Map<&2, List<&2, Unb>>, +f: String) -> List<&2, Unb>:
  G.get(List<&2, Unb>, Nil{}, wm, f)

def Unb.has.ctor(us: List<&2, Unb>, +k: String) -> Bool:
  match us:
    case Nil{}:
      False{}
    case Unb{c, ts} <> t:
      Bool.or(Str.eq(c, k), Unb.has.ctor(t, k))

# Whether a call of f may take a k node field-wise (f has a worker with a
# k parameter).
def Unb.wk(f: Core.Expr, +k: String, +wm: Map<&2, List<&2, Unb>>) -> Bool:
  match f:
    case Core.EVar{+n}:
      Unb.has.ctor(Unb.flags(wm, n), k)
    case other:
      False{}

def Unb.is_var(e: Core.Expr, +p: String) -> Bool:
  match e:
    case Core.EVar{+x}:
      Str.eq(x, p)
    case other:
      False{}

# How e uses the variable p, of constructor k: 0 not at all, 1 only as a
# node a pattern opens, an argument of a worker, or the result (tail) of a
# def whose result has constructor rk, 2 also otherwise. A list field is
# its head, then the node rebuilt with the rest.
def Unb.use(e: Core.Expr, +tail: Bool, +p: String, +k: String, +rk: String, +wm: Map<&2, List<&2, Unb>>) -> U32:
  match e:
    case Core.EVar{+x}:
      Bool.pick(U32, Str.eq(x, p), Bool.pick(U32, Bool.and(tail, Str.eq(rk, k)), 1, 2), 0)
    case Core.ECall{+f, args}:
      match args:
        case Nil{}:
          Unb.use(f, False{}, p, k, rk, wm)
        case +a <> t:
          U32.max(Bool.pick(U32, Bool.and(Unb.is_var(a, p), Unb.wk(f, k, wm)), 1, Unb.use(a, False{}, p, k, rk, wm)),
            Unb.use(Core.ECall{f, t}, False{}, p, k, rk, wm))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          0
        case +a <> t:
          U32.max(Unb.use(a, False{}, p, k, rk, wm), Unb.use(Core.ECtor{n, t}, False{}, p, k, rk, wm))
    case Core.ELam{pt, +b}:
      Bool.pick(U32, Str.has(Pat.vars(pt, Nil{}), p), 0, Unb.use(b, False{}, p, k, rk, wm))
    case Core.ELet{pt, +v, +b}:
      U32.max(Bool.pick(U32, Unb.is_var(v, p), 1, Unb.use(v, False{}, p, k, rk, wm)),
        Bool.pick(U32, Str.has(Pat.vars(pt, Nil{}), p), 0, Unb.use(b, tail, p, k, rk, wm)))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case +a <> t:
          U32.max(Bool.pick(U32, Unb.is_var(a, p), 1, Unb.use(a, False{}, p, k, rk, wm)),
            Unb.use(Core.EMatch{t, cases}, tail, p, k, rk, wm))
        case Nil{}:
          match cases:
            case Nil{}:
              0
            case +c <> t:
              U32.max(Unb.use(c, tail, p, k, rk, wm), Unb.use(Core.EMatch{Nil{}, t}, tail, p, k, rk, wm))
    case Core.ECase{ps, +b}:
      Bool.pick(U32, Str.has(Pats.vars(ps, Nil{}), p), 0, Unb.use(b, tail, p, k, rk, wm))
    case Core.ESucc{n, x}:
      Unb.use(x, False{}, p, k, rk, wm)
    case Core.EOp{op, +a, +b}:
      U32.max(Unb.use(a, False{}, p, k, rk, wm), Unb.use(b, False{}, p, k, rk, wm))
    case Core.EAnn{x, ty}:
      Unb.use(x, tail, p, k, rk, wm)
    case other:
      0

def Unb.prune.one(+x: String, u: Unb, +body: Core.Expr, +rk: String, +wm: Map<&2, List<&2, Unb>>) -> Unb:
  Unb{+k, ts} = u
  Bool.pick(Unb, Bool.and(Bool.not(String.is_empty(k)), U32.is_eq(Unb.use(body, True{}, x, k, rk, wm), 1)),
    Unb{k, ts}, Unb.none())

def Unb.prune.ps(ps: List<&2, Core.Param>, us: List<&2, Unb>, +body: Core.Expr, +rk: String,
  +wm: Map<&2, List<&2, Unb>>) -> List<&2, Unb>:
  match ps us:
    case Core.Param{x, m, t} <> pt u <> ut:
      Unb.prune.one(x, u, body, rk, wm) <> Unb.prune.ps(pt, ut, body, rk, wm)
    case pl ul:
      Nil{}

def Unb.prune.put(us: List<&2, Unb>, +name: String, ps: List<&2, Core.Param>, +body: Core.Expr, +rk: String,
  +wm: Map<&2, List<&2, Unb>>, acc: Map<&2, List<&2, Unb>>) -> Map<&2, List<&2, Unb>>:
  match us:
    case Nil{}:
      acc
    case u <> t:
      Map.set(&2, List<&2, Unb>, acc, name, Unb.prune.ps(ps, u <> t, body, rk, wm))

# A def's result: its constructor when flat, and the def's arity.
type URet is Data:
  URet{u: Unb, n: U32}

def URet.u(r: URet) -> Unb:
  URet{u, n} = r
  u

def URet.n(r: URet) -> U32:
  URet{u, n} = r
  n

def Unb.ret(+rm: Map<&2, URet>, +f: String) -> Unb:
  URet.u(G.get(URet, URet{Unb.none(), 0}, rm, f))

def Unb.rets(+ts: Map<&2, Unb>, ds: List<&2, Decl>, m: Map<&2, URet>) -> Map<&2, URet>:
  match ds:
    case Nil{}:
      m
    case DDef{+name, +ps, body, +ret} <> t:
      Unb.rets(ts, t, Map.set(&2, URet, m, name, URet{Unb.find(ts, Ty.head(ret)),
        U32.from_nat(List.length(&2, Core.Param, ps))}))
    case d <> t:
      Unb.rets(ts, t, m)

# One round of pruning: a parameter stays unboxed when its uses allow it
# under the last round's flags.
def Unb.prune(ds: List<&2, Decl>, +rm: Map<&2, URet>, +wm: Map<&2, List<&2, Unb>>,
  acc: Map<&2, List<&2, Unb>>) -> Map<&2, List<&2, Unb>>:
  match ds:
    case Nil{}:
      acc
    case DDef{+name, ps, +body, ret} <> t:
      Unb.prune(t, rm, wm, Unb.prune.put(Unb.flags(wm, name), name, ps, body, Unb.ctor.of(Unb.ret(rm, name)), wm, acc))
    case d <> t:
      Unb.prune(t, rm, wm, acc)

def Unb.names(+pre: String, ts: List<&2, String>, +j: U32) -> List<&2, String>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      (pre ++ U32.show(j)) <> Unb.names(pre, r, U32.inc(j))

def Unb.vars(xs: List<&2, String>) -> List<&2, Core.Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      Core.EVar{x} <> Unb.vars(t)

def Unb.pvars(xs: List<&2, String>) -> List<&2, Core.Pat>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      Core.PVar{x} <> Unb.pvars(t)

# The names of a worker's parameters for the fields of its parameter x.
def Unb.fields(+x: String, u: Unb) -> List<&2, String>:
  Unb.names("_ub_" ++ x ++ "_", Unb.tys.of(u), 0)

# The node a worker's parameter x stands for: its constructor over the
# fields' parameters.
def Unb.rebox(+x: String, +u: Unb) -> Core.Expr:
  Unb{k, ts} = u
  Core.ECtor{k, Unb.vars(Unb.fields(x, u))}

# e with p replaced by r, where p is free.
def Unb.sub(e: Core.Expr, +p: String, +r: Core.Expr) -> Core.Expr:
  match e:
    case Core.EVar{+x}:
      Bool.pick(Core.Expr, Str.eq(x, p), r, Core.EVar{x})
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{Unb.sub(f, p, r), Nil{}}
        case a <> t:
          Expr.push(Unb.sub(a, p, r), Unb.sub(Core.ECall{f, t}, p, r))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Core.ECtor{n, Nil{}}
        case a <> t:
          Expr.push(Unb.sub(a, p, r), Unb.sub(Core.ECtor{n, t}, p, r))
    case Core.ELam{+pt, +b}:
      Core.ELam{pt, Bool.pick(Core.Expr, Str.has(Pat.vars(pt, Nil{}), p), b, Unb.sub(b, p, r))}
    case Core.ELet{+pt, v, +b}:
      Core.ELet{pt, Unb.sub(v, p, r), Bool.pick(Core.Expr, Str.has(Pat.vars(pt, Nil{}), p), b, Unb.sub(b, p, r))}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Unb.sub(a, p, r), Unb.sub(Core.EMatch{t, cases}, p, r))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Unb.sub(c, p, r), Unb.sub(Core.EMatch{Nil{}, t}, p, r))
    case Core.ECase{+ps, +b}:
      Core.ECase{ps, Bool.pick(Core.Expr, Str.has(Pats.vars(ps, Nil{}), p), b, Unb.sub(b, p, r))}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Unb.sub(x, p, r)}
    case Core.EOp{op, a, b}:
      Core.EOp{op, Unb.sub(a, p, r), Unb.sub(b, p, r)}
    case Core.EAnn{x, ty}:
      Core.EAnn{Unb.sub(x, p, r), ty}
    case other:
      other

def Unb.sub.if(on: Bool, +x: String, +u: Unb, e: Core.Expr) -> Core.Expr:
  match on:
    case True{}:
      Unb.sub(e, x, Unb.rebox(x, u))
    case False{}:
      e

def Unb.subs(ps: List<&2, Core.Param>, us: List<&2, Unb>, e: Core.Expr) -> Core.Expr:
  match ps us:
    case Core.Param{+x, m, t} <> pt +u <> ut:
      Unb.subs(pt, ut, Unb.sub.if(Unb.is(u), x, u, e))
    case pl ul:
      e

# A let binding x to a full call of a def with a flat result opens it into
# variables, when each use of x allows it (see Unb.use): x is then its
# constructor rebuilt from them.
def Unb.lvar.go(hit: Bool, +x: String, +u: Unb, v: Core.Expr, b: Core.Expr) -> Core.Expr:
  match hit:
    case True{}:
      +xs = Unb.names("_ubl_" ++ x ++ "_", Unb.tys.of(u), 0)
      Core.ELet{Core.PCtor{Unb.ctor.of(u), Unb.pvars(xs)}, v, Unb.sub(b, x, Core.ECtor{Unb.ctor.of(u), Unb.vars(xs)})}
    case False{}:
      Core.ELet{Core.PVar{x}, v, b}

def Unb.lvar.call(+tail: Bool, +x: String, +rm: Map<&2, URet>, +rk: String, +wm: Map<&2, List<&2, Unb>>,
  +bound: List<&2, String>, v: Core.Expr, +b: Core.Expr) -> Core.Expr:
  match v:
    case Core.ECall{Core.EVar{+f}, +args}:
      +r = G.get(URet, URet{Unb.none(), 0}, rm, f)
      Unb.lvar.go(Bool.and(Bool.and(Unb.is(URet.u(r)), Bool.not(Str.has(bound, f))),
        Bool.and(U32.is_eq(URet.n(r), U32.from_nat(List.length(&2, Core.Expr, args))),
          U32.is_eq(Unb.use(b, tail, x, Unb.ctor.of(URet.u(r)), rk, wm), 1))), x, URet.u(r), Core.ECall{Core.EVar{f}, args}, b)
    case other:
      Core.ELet{Core.PVar{x}, other, b}

def Unb.lvar(+tail: Bool, p: Core.Pat, +rm: Map<&2, URet>, +rk: String, +wm: Map<&2, List<&2, Unb>>,
  +bound: List<&2, String>, v: Core.Expr, b: Core.Expr) -> Core.Expr:
  match p:
    case Core.PVar{+x}:
      Unb.lvar.call(tail, x, rm, rk, wm, bound, v, b)
    case other:
      Core.ELet{other, v, b}

# e with its let-bound flat results opened, innermost first (tail: e is
# the def's result; rk: its constructor).
def Unb.lvars(e: Core.Expr, +tail: Bool, +rm: Map<&2, URet>, +rk: String, +wm: Map<&2, List<&2, Unb>>,
  +bound: List<&2, String>) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{Unb.lvars(f, False{}, rm, rk, wm, bound), Nil{}}
        case a <> t:
          Expr.push(Unb.lvars(a, False{}, rm, rk, wm, bound), Unb.lvars(Core.ECall{f, t}, False{}, rm, rk, wm, bound))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Core.ECtor{n, Nil{}}
        case a <> t:
          Expr.push(Unb.lvars(a, False{}, rm, rk, wm, bound), Unb.lvars(Core.ECtor{n, t}, False{}, rm, rk, wm, bound))
    case Core.ELam{+pt, b}:
      Core.ELam{pt, Unb.lvars(b, False{}, rm, rk, wm, Pat.vars(pt, bound))}
    case Core.ELet{+pt, v, b}:
      Unb.lvar(tail, pt, rm, rk, wm, bound, Unb.lvars(v, False{}, rm, rk, wm, bound),
        Unb.lvars(b, tail, rm, rk, wm, Pat.vars(pt, bound)))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Unb.lvars(a, False{}, rm, rk, wm, bound), Unb.lvars(Core.EMatch{t, cases}, tail, rm, rk, wm, bound))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Unb.lvars(c, tail, rm, rk, wm, bound), Unb.lvars(Core.EMatch{Nil{}, t}, tail, rm, rk, wm, bound))
    case Core.ECase{+ps, b}:
      Core.ECase{ps, Unb.lvars(b, tail, rm, rk, wm, Pats.vars(ps, bound))}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Unb.lvars(x, False{}, rm, rk, wm, bound)}
    case Core.EOp{op, a, b}:
      Core.EOp{op, Unb.lvars(a, False{}, rm, rk, wm, bound), Unb.lvars(b, False{}, rm, rk, wm, bound)}
    case Core.EAnn{x, ty}:
      Core.EAnn{Unb.lvars(x, tail, rm, rk, wm, bound), ty}
    case other:
      other

# Known constructors: a match on a flat constructor's node, or a let that
# opens one, binds its fields' values instead (a variable pattern for the
# node rebuilds it).
type ULet is Data:
  ULet{p: Core.Pat, v: Core.Expr}

def Unb.free.none(xs: List<&2, String>, +e: Core.Expr) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case x <> t:
      Bool.and(Bool.not(Expr.free(e, x)), Unb.free.none(t, e))

# let p = v; e, with the lets v opens with (a worker call's own) floated out
# of it, so the code generator sees the call (see GSLetOut): each when its
# variables are not free in e (but for those p binds again).
def Unb.float(+p: Core.Pat, v: Core.Expr, +e: Core.Expr) -> Core.Expr:
  match v:
    case Core.ELet{+q, +w, +c}:
      Bool.pick(Unit -> Core.Expr, Unb.free.none(Pat.vars(q, Nil{}), Core.ELam{p, e}),
        u => Core.ELet{q, w, Unb.float(p, c, e)}, u => Core.ELet{p, Core.ELet{q, w, c}, e})(Unit{})
    case other:
      Core.ELet{p, other, e}

def Unb.wrap(ls: List<&2, ULet>, e: Core.Expr) -> Core.Expr:
  match ls:
    case Nil{}:
      e
    case ULet{p, v} <> t:
      Unb.float(p, v, Unb.wrap(t, e))

def Unb.shape.one(+u: Unb, +es: List<&2, Core.Expr>) -> Unb:
  Bool.pick(Unb, Bool.and(Unb.is(u), Nat.is_eq(Unb.arity(u), List.length(&2, Core.Expr, es))), u, Unb.none())

def Unb.shape(+cm: Map<&2, Unb>, scrs: List<&2, Core.Expr>) -> List<&2, Unb>:
  match scrs:
    case Nil{}:
      Nil{}
    case Core.ECtor{+k, +es} <> t:
      Unb.shape.one(Unb.find(cm, k), es) <> Unb.shape(cm, t)
    case s <> t:
      Unb.none() <> Unb.shape(cm, t)

def Unb.args(s: Core.Expr) -> List<&2, Core.Expr>:
  match s:
    case Core.ECtor{k, es}:
      es
    case other:
      [other]

def Unb.scrs.one(hit: Bool, s: Core.Expr, rest: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match hit:
    case True{}:
      List.append(&2, Core.Expr, Unb.args(s), rest)
    case False{}:
      s <> rest

def Unb.scrs(sh: List<&2, Unb>, scrs: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match sh scrs:
    case u <> ut s <> st:
      Unb.scrs.one(Unb.is(u), s, Unb.scrs(ut, st))
    case ul sl:
      sl

type UPats is Data:
  UPats{ps: List<&2, Core.Pat>, lets: List<&2, ULet>}

def Unb.wild(ts: List<&2, String>) -> List<&2, Core.Pat>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      Core.PVar{"_"} <> Unb.wild(r)

def Unb.pat.wild(ts: List<&2, String>, r: UPats) -> UPats:
  UPats{ps, lets} = r
  UPats{List.append(&2, Core.Pat, Unb.wild(ts), ps), lets}

def Unb.pat.rebox(+x: String, k: String, +xs: List<&2, String>, r: UPats) -> UPats:
  UPats{ps, lets} = r
  UPats{List.append(&2, Core.Pat, Unb.pvars(xs), ps), ULet{Core.PVar{x}, Core.ECtor{k, Unb.vars(xs)}} <> lets}

def Unb.pat.bind(wild: Bool, +x: String, +u: Unb, +j: U32, r: UPats) -> UPats:
  match wild:
    case True{}:
      Unb.pat.wild(Unb.tys.of(u), r)
    case False{}:
      Unb.pat.rebox(x, Unb.ctor.of(u), Unb.names("_ubm" ++ U32.show(j) ++ "_", Unb.tys.of(u), 0), r)

def Unb.pat(p: Core.Pat, u: Unb, +j: U32, r: UPats) -> UPats:
  match p:
    case Core.PCtor{k, qs}:
      UPats{ps, lets} = r
      UPats{List.append(&2, Core.Pat, qs, ps), lets}
    case Core.PVar{+x}:
      Unb.pat.bind(Str.eq(x, "_"), x, u, j, r)
    case other:
      Unb.pat.bind(True{}, "_", u, j, r)

def Unb.pat.one(hit: Bool, p: Core.Pat, u: Unb, +j: U32, r: UPats) -> UPats:
  match hit:
    case True{}:
      Unb.pat(p, u, j, r)
    case False{}:
      UPats{ps, lets} = r
      UPats{p <> ps, lets}

def Unb.pats(sh: List<&2, Unb>, ps: List<&2, Core.Pat>, +j: U32) -> UPats:
  match sh ps:
    case +u <> ut p <> pt:
      Unb.pat.one(Unb.is(u), p, u, j, Unb.pats(ut, pt, U32.inc(j)))
    case ul pl:
      UPats{pl, Nil{}}

def Unb.case(r: UPats, b: Core.Expr) -> Core.Expr:
  UPats{ps, lets} = r
  Core.ECase{ps, Unb.wrap(lets, b)}

def Unb.cases(+sh: List<&2, Unb>, cs: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match cs:
    case Nil{}:
      Nil{}
    case Core.ECase{ps, b} <> t:
      Unb.case(Unb.pats(sh, ps, 0), b) <> Unb.cases(sh, t)
    case c <> t:
      c <> Unb.cases(sh, t)

def Unb.mat.go(+sh: List<&2, Unb>, scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>) -> Core.Expr:
  Core.EMatch{Unb.scrs(sh, scrs), Unb.cases(sh, cases)}

def Unb.mat(+cm: Map<&2, Unb>, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.EMatch{+scrs, cases}:
      Unb.mat.go(Unb.shape(cm, scrs), scrs, cases)
    case other:
      other

def Unb.mat.top(top: Bool, +cm: Map<&2, Unb>, e: Core.Expr) -> Core.Expr:
  match top:
    case True{}:
      Unb.mat(cm, e)
    case False{}:
      e

# A let opening a flat constructor's node: a match on its fields' values,
# which binds them all at once (a value may name a variable the pattern
# binds).
# Fields that are a worker's parameters (fresh names) bound to plain
# variables: the variables are renamed to the parameters.
def Unb.alias.ok(qs: List<&2, Core.Pat>, es: List<&2, Core.Expr>) -> Bool:
  match qs es:
    case Core.PVar{x} <> qt Core.EVar{+y} <> et:
      Bool.and(String.starts_with(y, "_ub"), Unb.alias.ok(qt, et))
    case Nil{} Nil{}:
      True{}
    case ql el:
      False{}

def Unb.alias.sub(qs: List<&2, Core.Pat>, es: List<&2, Core.Expr>, b: Core.Expr) -> Core.Expr:
  match qs es:
    case Core.PVar{+x} <> qt Core.EVar{+y} <> et:
      Unb.alias.sub(qt, et, Unb.sub(b, x, Core.EVar{y}))
    case ql el:
      b

def Unb.let.hit(ok: Bool, qs: List<&2, Core.Pat>, es: List<&2, Core.Expr>, b: Core.Expr) -> Core.Expr:
  match ok:
    case True{}:
      Unb.alias.sub(qs, es, b)
    case False{}:
      Core.EMatch{es, [Core.ECase{qs, b}]}

def Unb.let.es(+qs: List<&2, Core.Pat>, +es: List<&2, Core.Expr>, b: Core.Expr) -> Core.Expr:
  Unb.let.hit(Unb.alias.ok(qs, es), qs, es, b)

def Unb.let.go(hit: Bool, +k: String, qs: List<&2, Core.Pat>, v: Core.Expr, b: Core.Expr) -> Core.Expr:
  match hit:
    case True{}:
      Unb.let.es(qs, Unb.args(v), b)
    case False{}:
      Core.ELet{Core.PCtor{k, qs}, v, b}

def Unb.let.ctor(+cm: Map<&2, Unb>, +k: String, qs: List<&2, Core.Pat>, v: Core.Expr, b: Core.Expr) -> Core.Expr:
  match v:
    case Core.ECtor{+c, +es}:
      Unb.let.go(Bool.and(Str.eq(c, k), Unb.is(Unb.shape.one(Unb.find(cm, k), es))), k, qs, Core.ECtor{c, es}, b)
    case other:
      Core.ELet{Core.PCtor{k, qs}, other, b}

def Unb.let(+cm: Map<&2, Unb>, p: Core.Pat, v: Core.Expr, b: Core.Expr) -> Core.Expr:
  match p:
    case Core.PCtor{+k, qs}:
      Unb.let.ctor(cm, k, qs, v, b)
    case other:
      Core.ELet{other, v, b}

def Unb.known(+cm: Map<&2, Unb>, e: Core.Expr, top: Bool) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{Unb.known(cm, f, True{}), Nil{}}
        case a <> t:
          Expr.push(Unb.known(cm, a, True{}), Unb.known(cm, Core.ECall{f, t}, False{}))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Core.ECtor{n, Nil{}}
        case a <> t:
          Expr.push(Unb.known(cm, a, True{}), Unb.known(cm, Core.ECtor{n, t}, False{}))
    case Core.ELam{pt, b}:
      Core.ELam{pt, Unb.known(cm, b, True{})}
    case Core.ELet{pt, v, b}:
      Unb.let(cm, pt, Unb.known(cm, v, True{}), Unb.known(cm, b, True{}))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Unb.mat.top(top, cm, Expr.push(Unb.known(cm, a, True{}), Unb.known(cm, Core.EMatch{t, cases}, False{})))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Unb.known(cm, c, True{}), Unb.known(cm, Core.EMatch{Nil{}, t}, False{}))
    case Core.ECase{ps, b}:
      Core.ECase{ps, Unb.known(cm, b, True{})}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Unb.known(cm, x, True{})}
    case Core.EOp{op, a, b}:
      Core.EOp{op, Unb.known(cm, a, True{}), Unb.known(cm, b, True{})}
    case Core.EAnn{x, ty}:
      Core.EAnn{Unb.known(cm, x, True{}), ty}
    case other:
      other

# Calls of workers: a worker's arguments, and the lets that open the ones not built in place.
type UArgs is Data:
  UArgs{args: List<&2, Core.Expr>, lets: List<&2, ULet>}

def Unb.arg.open(+k: String, v: Core.Expr, +names: List<&2, String>, r: UArgs) -> UArgs:
  UArgs{args, lets} = r
  UArgs{List.append(&2, Core.Expr, Unb.vars(names), args), ULet{Core.PCtor{k, Unb.pvars(names)}, v} <> lets}

def Unb.arg.ctor(same: Bool, +k: String, es: List<&2, Core.Expr>, +names: List<&2, String>, r: UArgs) -> UArgs:
  match same:
    case True{}:
      UArgs{args, lets} = r
      UArgs{List.append(&2, Core.Expr, es, args), lets}
    case False{}:
      Unb.arg.open(k, Core.ECtor{k, es}, names, r)

# A let of Nest's or of a worker call's arguments (their names apart)
# around an argument goes around the call instead.
def Unb.nc(xs: List<&2, String>) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case +x <> t:
      Bool.and(Bool.or(String.starts_with(x, "_nc"), Bool.and(String.starts_with(x, "_ub"),
        Bool.not(Bool.or(String.starts_with(x, "_ub_"), String.starts_with(x, "_ubl"))))), Unb.nc(t))

def Unb.arg.float(p: Core.Pat, v: Core.Expr, r: UArgs) -> UArgs:
  UArgs{args, lets} = r
  UArgs{args, ULet{p, v} <> lets}

def Unb.arg.flat(a: Core.Expr, +k: String, +n: Nat, +names: List<&2, String>, r: UArgs) -> UArgs:
  match a:
    case Core.ECtor{+c, +es}:
      Unb.arg.ctor(Bool.and(Str.eq(c, k), Nat.is_eq(n, List.length(&2, Core.Expr, es))), k, es, names, r)
    case Core.ELet{+p, +v, +b}:
      Bool.pick(UArgs -> UArgs, Unb.nc(Pat.vars(p, Nil{})), w => Unb.arg.float(p, v, Unb.arg.flat(b, k, n, names, w)),
        w => Unb.arg.open(k, Core.ELet{p, v, b}, names, w))(r)
    case other:
      Unb.arg.open(k, other, names, r)

def Unb.arg(hit: Bool, a: Core.Expr, u: Unb, +names: List<&2, String>, r: UArgs) -> UArgs:
  match hit:
    case True{}:
      Unb{+k, +ts} = u
      Unb.arg.flat(a, k, List.length(&2, String, ts), names, r)
    case False{}:
      UArgs{args, lets} = r
      UArgs{a <> args, lets}

def Unb.cargs(us: List<&2, Unb>, as: List<&2, Core.Expr>, +n: U32, +i: U32) -> UArgs:
  match us as:
    case +u <> ut a <> at:
      Unb.arg(Unb.is(u), a, u, Unb.names("_ub" ++ U32.show(n) ++ "_" ++ U32.show(i) ++ "_", Unb.tys.of(u), 0),
        Unb.cargs(ut, at, n, U32.inc(i)))
    case ul al:
      UArgs{al, Nil{}}

def Unb.call.fin(+f: String, r: UArgs) -> Core.Expr:
  UArgs{as, lets} = r
  Unb.wrap(lets, Core.ECall{Core.EVar{f ++ "%u"}, as})

def Unb.call.pick(hit: Bool, us: List<&2, Unb>, +f: String, args: List<&2, Core.Expr>, +n: U32) -> Core.Expr:
  match hit:
    case True{}:
      Unb.call.fin(f, Unb.cargs(us, args, n, 0))
    case False{}:
      Core.ECall{Core.EVar{f}, args}

def Unb.call.us(+us: List<&2, Unb>, +bound: List<&2, String>, +f: String, +args: List<&2, Core.Expr>, +n: U32) -> Core.Expr:
  Unb.call.pick(Bool.and(Bool.and(Unb.any(us), Bool.not(Str.has(bound, f))),
    Nat.is_eq(List.length(&2, Unb, us), List.length(&2, Core.Expr, args))), us, f, args, n)

# A full call of a def with a worker (not a local of its name) calls the
# worker.
def Unb.call(+wm: Map<&2, List<&2, Unb>>, +bound: List<&2, String>, +n: U32, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.ECall{Core.EVar{+f}, args}:
      Unb.call.us(Unb.flags(wm, f), bound, f, args, n)
    case other:
      other

def Unb.call.top(top: Bool, +wm: Map<&2, List<&2, Unb>>, +bound: List<&2, String>, +n: U32, e: Core.Expr) -> Core.Expr:
  match top:
    case True{}:
      Unb.call(wm, bound, n, e)
    case False{}:
      e

# e with its calls of workers' defs rewritten (n: the nesting depth, which
# keeps the names of the lets apart; bound: the locals in scope).
def Unb.calls(e: Core.Expr, +wm: Map<&2, List<&2, Unb>>, +bound: List<&2, String>, +n: U32, top: Bool) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Unb.call.top(top, wm, bound, n, Core.ECall{Unb.calls(f, wm, bound, U32.inc(n), True{}), Nil{}})
        case a <> t:
          Unb.call.top(top, wm, bound, n, Expr.push(Unb.calls(a, wm, bound, U32.inc(n), True{}),
            Unb.calls(Core.ECall{f, t}, wm, bound, n, False{})))
    case Core.ECtor{k, args}:
      match args:
        case Nil{}:
          Core.ECtor{k, Nil{}}
        case a <> t:
          Expr.push(Unb.calls(a, wm, bound, U32.inc(n), True{}), Unb.calls(Core.ECtor{k, t}, wm, bound, n, False{}))
    case Core.ELam{+pt, b}:
      Core.ELam{pt, Unb.calls(b, wm, Pat.vars(pt, bound), U32.inc(n), True{})}
    case Core.ELet{+pt, v, b}:
      Unb.float(pt, Unb.calls(v, wm, bound, U32.inc(n), True{}), Unb.calls(b, wm, Pat.vars(pt, bound), U32.inc(n), True{}))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Unb.calls(a, wm, bound, U32.inc(n), True{}), Unb.calls(Core.EMatch{t, cases}, wm, bound, n, False{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Unb.calls(c, wm, bound, U32.inc(n), True{}), Unb.calls(Core.EMatch{Nil{}, t}, wm, bound, n, False{}))
    case Core.ECase{+ps, b}:
      Core.ECase{ps, Unb.calls(b, wm, Pats.vars(ps, bound), U32.inc(n), True{})}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Unb.calls(x, wm, bound, U32.inc(n), True{})}
    case Core.EOp{op, a, b}:
      Core.EOp{op, Unb.calls(a, wm, bound, U32.inc(n), True{}), Unb.calls(b, wm, bound, U32.inc(n), True{})}
    case Core.EAnn{x, ty}:
      Core.EAnn{Unb.calls(x, wm, bound, U32.inc(n), True{}), ty}
    case other:
      other

def Unb.params.of(xs: List<&2, String>, +m: U32, ts: List<&2, String>) -> List<&2, Core.Param>:
  match xs ts:
    case x <> xt t <> tt:
      Core.Param{x, m, t} <> Unb.params.of(xt, m, tt)
    case xl tl:
      Nil{}

def Unb.param(hit: Bool, p: Core.Param, +u: Unb) -> List<&2, Core.Param>:
  match hit:
    case True{}:
      Core.Param{+x, m, t} = p
      Unb.params.of(Unb.fields(x, u), m, Unb.tys.of(u))
    case False{}:
      [p]

def Unb.params(ps: List<&2, Core.Param>, us: List<&2, Unb>) -> List<&2, Core.Param>:
  match ps us:
    case p <> pt +u <> ut:
      List.append(&2, Core.Param, Unb.param(Unb.is(u), p, u), Unb.params(pt, ut))
    case pl ul:
      pl

def Unb.wrapper.one(hit: Bool, +x: String, +u: Unb, r: UArgs) -> UArgs:
  match hit:
    case True{}:
      Unb{k, ts} = u
      Unb.arg.open(k, Core.EVar{x}, Unb.fields(x, u), r)
    case False{}:
      UArgs{as, lets} = r
      UArgs{Core.EVar{x} <> as, lets}

# The wrapper's call of the worker: its unboxed parameters opened.
def Unb.wrapper(ps: List<&2, Core.Param>, us: List<&2, Unb>) -> UArgs:
  match ps us:
    case Core.Param{+x, m, t} <> pt +u <> ut:
      Unb.wrapper.one(Unb.is(u), x, u, Unb.wrapper(pt, ut))
    case pl ul:
      UArgs{Nil{}, Nil{}}

# Whether e is a full call of a def with a flat result, after the lets it
# opens with.
def Unb.flat.tail(e: Core.Expr, +rm: Map<&2, URet>) -> Bool:
  match e:
    case Core.ELet{p, v, b}:
      Unb.flat.tail(b, rm)
    case Core.ECall{f, as}:
      match f:
        case Core.EVar{+h}:
          +r = G.get(URet, URet{Unb.none(), 0}, rm, h)
          Bool.and(Unb.is(URet.u(r)), U32.is_eq(URet.n(r), U32.from_nat(List.length(&2, Core.Expr, as))))
        case other:
          False{}
    case other:
      False{}

# a in front of the arguments of the call under e's lets.
def Unb.push.deep(a: Core.Expr, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.ELet{p, v, b}:
      Core.ELet{p, v, Unb.push.deep(a, b)}
    case other:
      Expr.push(a, other)

def Unb.pull.one(hit: Bool, a: Core.Expr, +x: String, e: Core.Expr) -> Core.Expr:
  match hit:
    case True{}:
      Unb.float(Core.PVar{x}, a, Unb.push.deep(Core.EVar{x}, e))
    case False{}:
      Unb.push.deep(a, e)

# e with each call's arguments that call a def with a flat result let-bound
# before it (_ufD_I: the call's depth D, the argument's place I from the
# end), so Unb.lvars opens them: the optimizer's inlining nests such calls
# (look(.., look(.., st))), and a flat call that is an argument builds its
# node.
def Unb.flet(e: Core.Expr, +rm: Map<&2, URet>, +d: U32) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{Unb.flet(f, rm, d), Nil{}}
        case a <> +t:
          +a2 = Unb.flet(a, rm, U32.inc(d))
          Unb.pull.one(Unb.flat.tail(a2, rm), a2,
            "_uf" ++ U32.show(d) ++ "_" ++ U32.show(U32.from_nat(List.length(&2, Core.Expr, t))),
            Unb.flet(Core.ECall{f, t}, rm, d))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Core.ECtor{n, Nil{}}
        case a <> t:
          Expr.push(Unb.flet(a, rm, U32.inc(d)), Unb.flet(Core.ECtor{n, t}, rm, d))
    case Core.ELam{pt, b}:
      Core.ELam{pt, Unb.flet(b, rm, d)}
    case Core.ELet{pt, v, b}:
      Core.ELet{pt, Unb.flet(v, rm, d), Unb.flet(b, rm, d)}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Unb.flet(a, rm, d), Unb.flet(Core.EMatch{t, cases}, rm, d))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Unb.flet(c, rm, d), Unb.flet(Core.EMatch{Nil{}, t}, rm, d))
    case Core.ECase{ps, b}:
      Core.ECase{ps, Unb.flet(b, rm, d)}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Unb.flet(x, rm, d)}
    case Core.EOp{op, a, b}:
      Core.EOp{op, Unb.flet(a, rm, d), Unb.flet(b, rm, d)}
    case Core.EAnn{x, ty}:
      Core.EAnn{Unb.flet(x, rm, d), ty}
    case other:
      other

def Unb.fix(+rm: Map<&2, URet>, +rk: String, +wm: Map<&2, List<&2, Unb>>, +cm: Map<&2, Unb>, e: Core.Expr) -> Core.Expr:
  Unb.calls(Unb.known(cm, Unb.lvars(Unb.flet(e, rm, 0), True{}, rm, rk, wm, Nil{}), True{}), wm, Nil{}, 0, True{})

# A worker's parameter of a type variable's type (a pair's component, say)
# that the body hands to a U32 native where it takes a U32 (an array's
# index, say) is a U32 (so the code generator keeps it in a uint32_t, never
# shared).
def Unb.u32.fs() -> List<&2, String>:
  ["U32.inc", "U32.add", "U32.sub", "U32.mul", "U32.div", "U32.mod", "U32.not", "U32.and", "U32.or",
   "U32.xor", "U32.shl", "U32.shr", "U32.min", "U32.max", "U32.is_eq", "U32.is_ne", "U32.is_lt",
   "U32.is_le", "U32.is_gt", "U32.is_ge", "U32.is_zero", "U32.is_even", "U32.to_nat", "U32.to_f32",
   "U32.show", "U32.log2"]

def Unb.u32.args(as: List<&2, Core.Expr>, +x: String) -> Bool:
  match as:
    case Nil{}:
      False{}
    case a <> t:
      Bool.or(Unb.is_var(a, x), Unb.u32.args(t, x))

def Unb.u32.first(as: List<&2, Core.Expr>, +x: String) -> Bool:
  match as:
    case Nil{}:
      False{}
    case a <> t:
      Unb.is_var(a, x)

def Unb.u32.second(as: List<&2, Core.Expr>, +x: String) -> Bool:
  match as:
    case Nil{}:
      False{}
    case a <> t:
      Unb.u32.first(t, x)

# (an array native's arguments: the erased type, the array, the index)
def Unb.u32.third(as: List<&2, Core.Expr>, +x: String) -> Bool:
  match as:
    case Nil{}:
      False{}
    case a <> t:
      Unb.u32.second(t, x)

def Unb.u32.arg(+f: String, +as: List<&2, Core.Expr>, +x: String) -> Bool:
  Bool.or(Bool.or(Bool.and(Str.has(Unb.u32.fs(), f), Unb.u32.args(as, x)),
    Bool.and(Str.has(["U32.shln", "U32.shrn", "U32.pow"], f), Unb.u32.first(as, x))),
    Bool.and(Str.has(["Array.get", "Array.set", "Array.swap", "Array.get%w", "Array.set%w", "Array.swap%w"], f),
      Unb.u32.third(as, x)))

def Unb.u32.call(f: Core.Expr, +as: List<&2, Core.Expr>, +x: String) -> Bool:
  match f:
    case Core.EVar{+n}:
      Unb.u32.arg(n, as, x)
    case other:
      False{}

def Unb.u32(e: Core.Expr, +x: String, top: Bool) -> Bool:
  match e:
    case Core.ECall{+f, args}:
      match args:
        case Nil{}:
          Unb.u32(f, x, True{})
        case +a <> +t:
          Bool.or(Bool.or(Bool.and(top, Unb.u32.call(f, a <> t, x)), Unb.u32(a, x, True{})), Unb.u32(Core.ECall{f, t}, x, False{}))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          False{}
        case a <> t:
          Bool.or(Unb.u32(a, x, True{}), Unb.u32(Core.ECtor{n, t}, x, True{}))
    case Core.ELam{pt, +b}:
      Bool.and(Bool.not(Str.has(Pat.vars(pt, Nil{}), x)), Unb.u32(b, x, True{}))
    case Core.ELet{pt, v, +b}:
      Bool.or(Unb.u32(v, x, True{}), Bool.and(Bool.not(Str.has(Pat.vars(pt, Nil{}), x)), Unb.u32(b, x, True{})))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Bool.or(Unb.u32(a, x, True{}), Unb.u32(Core.EMatch{t, cases}, x, True{}))
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case c <> t:
              Bool.or(Unb.u32(c, x, True{}), Unb.u32(Core.EMatch{Nil{}, t}, x, True{}))
    case Core.ECase{ps, +b}:
      Bool.and(Bool.not(Str.has(Pats.vars(ps, Nil{}), x)), Unb.u32(b, x, True{}))
    case Core.ESucc{k, y}:
      Unb.u32(y, x, True{})
    case Core.EOp{op, a, b}:
      Bool.or(Unb.u32(a, x, True{}), Unb.u32(b, x, True{}))
    case Core.EAnn{y, ty}:
      Unb.u32(y, x, True{})
    case other:
      False{}

def Unb.typed(ps: List<&2, Core.Param>, +body: Core.Expr) -> List<&2, Core.Param>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Param{+x, +m, +t} <> r:
      Core.Param{x, m, Bool.pick(String, Bool.and(Nat.is_eq(String.length(t), 1n), Unb.u32(body, x, True{})), "U32", t)} <>
        Unb.typed(r, body)

def Unb.decl.pick(hit: Bool, +us: List<&2, Unb>, +rm: Map<&2, URet>, +wm: Map<&2, List<&2, Unb>>,
  +cm: Map<&2, Unb>, +name: String, +ps: List<&2, Core.Param>, body: Core.Expr, +ret: Core.Expr) -> List<&2, Decl>:
  match hit:
    case True{}:
      +b = Unb.fix(rm, Unb.ctor.of(Unb.ret(rm, name)), wm, cm, Unb.subs(ps, us, body))
      [DDef{name ++ "%u", Unb.typed(Unb.params(ps, us), b), b, ret}, DDef{name, ps, Unb.call.fin(name, Unb.wrapper(ps, us)), ret}]
    case False{}:
      [DDef{name, ps, Unb.fix(rm, Unb.ctor.of(Unb.ret(rm, name)), wm, cm, body), ret}]

def Unb.decl.go(+us: List<&2, Unb>, +rm: Map<&2, URet>, +wm: Map<&2, List<&2, Unb>>, +cm: Map<&2, Unb>,
  +name: String, +ps: List<&2, Core.Param>, body: Core.Expr, +ret: Core.Expr) -> List<&2, Decl>:
  Unb.decl.pick(Unb.any(us), us, rm, wm, cm, name, ps, body, ret)

def Unb.decl(+rm: Map<&2, URet>, +wm: Map<&2, List<&2, Unb>>, +cm: Map<&2, Unb>, d: Decl) -> List<&2, Decl>:
  match d:
    case DDef{+name, +ps, body, +ret}:
      Unb.decl.go(Unb.flags(wm, name), rm, wm, cm, name, ps, body, ret)
    case other:
      [other]

def Unb.decls(+rm: Map<&2, URet>, +wm: Map<&2, List<&2, Unb>>, +cm: Map<&2, Unb>, ds: List<&2, Decl>) ->
  List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      List.append(&2, Decl, Unb.decl(rm, wm, cm, d), Unb.decls(rm, wm, cm, t))

# Two rounds of pruning: a parameter a worker takes field-wise may lose its
# flag in the first.
def Unb.run(+ds: List<&2, Decl>, +rm: Map<&2, URet>, +w0: Map<&2, List<&2, Unb>>) -> List<&2, Decl>:
  Unb.decls(rm, Unb.prune(ds, rm, Unb.prune(ds, rm, w0, MTip{}), MTip{}), Unb.types(True{}, ds, MTip{}), ds)

# Defs with a worker already, as if laws (a second round leaves them be).
def Unb.done.put(ok: Bool, +r: String, m: Map<&2, Decl>) -> Map<&2, Decl>:
  match ok:
    case True{}:
      Map.set(&2, Decl, m, Str.rev(String.drop(r, 2n)), DLaw{"", Nil{}, Core.EVar{""}})
    case False{}:
      m

def Unb.done(ds: List<&2, Decl>, m: Map<&2, Decl>) -> Map<&2, Decl>:
  match ds:
    case Nil{}:
      m
    case DDef{+name, ps, body, ret} <> t:
      Unb.done(t, Unb.done.put(String.starts_with(Str.rev(name), "u%"), Str.rev(name), m))
    case d <> t:
      Unb.done(t, m)

def Unb.program.go(+ds: List<&2, Decl>, +ts: Map<&2, Unb>) -> List<&2, Decl>:
  Unb.run(ds, Unb.rets(ts, ds, MTip{}), Unb.cands.all(ts, Unb.types(True{}, ds, MTip{}), Unb.done(ds, G.laws(ds, MTip{})), ds, MTip{}))

def Unb.program(on: Bool, +ds: List<&2, Decl>) -> List<&2, Decl>:
  match on:
    case True{}:
      Unb.program.go(ds, Unb.types(False{}, ds, MTip{}))
    case False{}:
      ds

# Nested results. A def whose result is a pair with a record in it (a type
# of one constructor of two to eight fields and no parameters, like bfs's
# pop: St & Bool) gets a worker, f%n, that returns the pair's leaves as a
# record of their own, N%f, which the unboxing below returns flat; f then
# rebuilds the pair from it (for closures and partial calls). A full call
# of f elsewhere calls f%n and rebuilds the pair where it is, so a match or
# a worker call that opens it builds neither node (Unb.known, Unb.calls). In
# f%n, a result pair's components go in field by field (a record built in
# place gives its fields, another one is opened with a let), and a tail
# call of another such def of the same components stays a tail call.
type NComp is Data:
  NComp{k: String, fs: List<&2, Field>}

type NRet is Data:
  NRet{cs: List<&2, NComp>, n: Nat}

def NRet.cs(r: NRet) -> List<&2, NComp>:
  NRet{cs, n} = r
  cs

def NRet.n(r: NRet) -> Nat:
  NRet{cs, n} = r
  n

def Nest.put.type(ok: Bool, +key: String, c: Ctor, m: Map<&2, Ctor>) -> Map<&2, Ctor>:
  match ok:
    case True{}:
      Map.set(&2, Ctor, m, key, c)
    case False{}:
      m

def Nest.type(+name: String, ps: List<&2, String>, cs: List<&2, Ctor>, m: Map<&2, Ctor>) -> Map<&2, Ctor>:
  match ps cs:
    case Nil{} Ctor{+k, +fs} <> Nil{}:
      Nest.put.type(Unb.fits(fs), name, Ctor{k, fs}, m)
    case pl cl:
      m

# The records: types of one constructor of two to eight fields, with no
# parameters, by name.
def Nest.types(ds: List<&2, Decl>, m: Map<&2, Ctor>) -> Map<&2, Ctor>:
  match ds:
    case Nil{}:
      m
    case DType{+name, ps, cs} <> t:
      Nest.types(t, Nest.type(name, ps, cs, m))
    case d <> t:
      Nest.types(t, m)

def Nest.sigma(f: Core.Expr, ok: Bool, a: Core.Expr) -> List<&2, Core.Expr>:
  match f:
    case Core.ELam{p, b}:
      Bool.pick(List<&2, Core.Expr>, ok, [a, b], Nil{})
    case other:
      Nil{}

# The components of a pair type.
def Nest.comps(ty: Core.Expr) -> List<&2, Core.Expr>:
  match ty:
    case Core.ETy{+n, args}:
      match args:
        case a <> b <> Nil{}:
          Bool.pick(List<&2, Core.Expr>, Str.eq(n, "&"), [a, b], Nil{})
        case q1 <> q2 <> a <> f <> Nil{}:
          Nest.sigma(f, Str.eq(n, "Sigma"), a)
        case other:
          Nil{}
    case other:
      Nil{}

def Nest.comp.pick(leaf: Bool, +n: String, fs: List<&2, Field>, c: Core.Expr) -> NComp:
  match leaf:
    case True{}:
      NComp{"", [Field{"x", c}]}
    case False{}:
      NComp{n, fs}

def Nest.comp.go(k: Ctor, c: Core.Expr) -> NComp:
  match k:
    case Ctor{+n, fs}:
      Nest.comp.pick(String.is_empty(n), n, fs, c)

def Nest.comp(+tm: Map<&2, Ctor>, +c: Core.Expr) -> NComp:
  Nest.comp.go(G.get(Ctor, Ctor{"", Nil{}}, tm, Ty.head(c)), c)

def Nest.comps.of(+tm: Map<&2, Ctor>, cs: List<&2, Core.Expr>) -> List<&2, NComp>:
  match cs:
    case Nil{}:
      Nil{}
    case c <> t:
      Nest.comp(tm, c) <> Nest.comps.of(tm, t)

# Whether a component is a record.
def Nest.nested(cs: List<&2, NComp>) -> Bool:
  match cs:
    case Nil{}:
      False{}
    case NComp{k, fs} <> t:
      Bool.or(Bool.not(String.is_empty(k)), Nest.nested(t))

# The components' fields, in order.
def Nest.fields(cs: List<&2, NComp>) -> List<&2, Field>:
  match cs:
    case Nil{}:
      Nil{}
    case NComp{k, fs} <> t:
      List.append(&2, Field, fs, Nest.fields(t))

def Nest.cand.go(+cs: List<&2, NComp>, ok: Bool, +n: Nat) -> NRet:
  Bool.pick(NRet, Bool.and(ok, Bool.and(Nest.nested(cs), Unb.fits(Nest.fields(cs)))), NRet{cs, n}, NRet{Nil{}, 0n})

def Nest.cand(+tm: Map<&2, Ctor>, +laws: Map<&2, Decl>, +name: String, ps: List<&2, Core.Param>, +ret: Core.Expr) -> NRet:
  Nest.cand.go(Nest.comps.of(tm, Nest.comps(ret)), Unb.ok.def(name, ret, laws), List.length(&2, Core.Param, ps))

def Nest.put(r: NRet, +name: String, m: Map<&2, NRet>) -> Map<&2, NRet>:
  match r:
    case NRet{cs, n}:
      match cs:
        case Nil{}:
          m
        case c <> t:
          Map.set(&2, NRet, m, name, NRet{c <> t, n})

def Nest.cands(+tm: Map<&2, Ctor>, +laws: Map<&2, Decl>, ds: List<&2, Decl>, m: Map<&2, NRet>) -> Map<&2, NRet>:
  match ds:
    case Nil{}:
      m
    case DDef{+name, ps, body, +ret} <> t:
      Nest.cands(tm, laws, t, Nest.put(Nest.cand(tm, laws, name, ps, ret), name, m))
    case d <> t:
      Nest.cands(tm, laws, t, m)

def Nest.get(+cm: Map<&2, NRet>, +f: String) -> NRet:
  G.get(NRet, NRet{Nil{}, 0n}, cm, f)

# Names of the fields fs (pre0, pre1, ..).
def Nest.fnames(+pre: String, fs: List<&2, Field>, +j: U32) -> List<&2, String>:
  match fs:
    case Nil{}:
      Nil{}
    case f <> t:
      (pre ++ U32.show(j)) <> Nest.fnames(pre, t, U32.inc(j))

# Names of the leaves, component i's fields as pre{i}_{j}.
def Nest.names(+pre: String, cs: List<&2, NComp>, +i: U32) -> List<&2, String>:
  match cs:
    case Nil{}:
      Nil{}
    case NComp{k, fs} <> t:
      List.append(&2, String, Nest.fnames(pre ++ U32.show(i) ++ "_", fs, 0), Nest.names(pre, t, U32.inc(i)))

def Nest.one(leaf: Bool, +k: String, +pre: String, fs: List<&2, Field>) -> Core.Expr:
  match leaf:
    case True{}:
      Core.EVar{pre ++ "0"}
    case False{}:
      Core.ECtor{k, Unb.vars(Nest.fnames(pre, fs, 0))}

# The components rebuilt from the leaves' variables.
def Nest.out(+pre: String, cs: List<&2, NComp>, +i: U32) -> List<&2, Core.Expr>:
  match cs:
    case Nil{}:
      Nil{}
    case NComp{+k, fs} <> t:
      Nest.one(String.is_empty(k), k, pre ++ U32.show(i) ++ "_", fs) <> Nest.out(pre, t, U32.inc(i))

# f's pair from a call of f%n (the lets' names apart by n).
def Nest.rebuild(+f: String, +cs: List<&2, NComp>, as: List<&2, Core.Expr>, +n: String) -> Core.Expr:
  +pre = "_nc" ++ n ++ "_"
  Core.ELet{Core.PCtor{"N%" ++ f, Unb.pvars(Nest.names(pre, cs, 0))}, Core.ECall{Core.EVar{f ++ "%n"}, as},
    Core.ECtor{"Tuple", Nest.out(pre, cs, 0)}}

def Nest.call.go(r: NRet, +bound: List<&2, String>, +f: String, +args: List<&2, Core.Expr>, +n: String) -> Core.Expr:
  match r:
    case NRet{+cs, k}:
      Bool.pick(Unit -> Core.Expr, Bool.and(Bool.and(Nest.nested(cs), Bool.not(Str.has(bound, f))),
        Nat.is_eq(k, List.length(&2, Core.Expr, args))), u => Nest.rebuild(f, cs, args, n), u => Core.ECall{Core.EVar{f}, args})(Unit{})

def Nest.call(+cm: Map<&2, NRet>, +bound: List<&2, String>, +n: String, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.ECall{Core.EVar{+f}, +args}:
      Nest.call.go(Nest.get(cm, f), bound, f, args, n)
    case other:
      other

def Nest.call.top(top: Bool, +cm: Map<&2, NRet>, +bound: List<&2, String>, +n: String, e: Core.Expr) -> Core.Expr:
  match top:
    case True{}:
      Nest.call(cm, bound, n, e)
    case False{}:
      e

# e with its full calls of such defs rewritten (but for a parallel let's
# own calls; bound: the locals in scope).
def Nest.calls(e: Core.Expr, +cm: Map<&2, NRet>, +bound: List<&2, String>, +n: String, top: Bool) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Nest.call.top(top, cm, bound, n, Core.ECall{Nest.calls(f, cm, bound, n ++ "a", True{}), Nil{}})
        case a <> t:
          Nest.call.top(top, cm, bound, n, Expr.push(Nest.calls(a, cm, bound, n ++ "a", True{}),
            Nest.calls(Core.ECall{f, t}, cm, bound, n ++ "b", False{})))
    case Core.ECtor{+k, args}:
      match args:
        case Nil{}:
          Core.ECtor{k, Nil{}}
        case a <> t:
          Expr.push(Nest.calls(a, cm, bound, n ++ "a", Bool.not(Str.eq(k, "%par"))),
            Nest.calls(Core.ECtor{k, t}, cm, bound, n ++ "b", False{}))
    case Core.ELam{+pt, b}:
      Core.ELam{pt, Nest.calls(b, cm, Pat.vars(pt, bound), n ++ "a", True{})}
    case Core.ELet{+pt, v, b}:
      Core.ELet{pt, Nest.calls(v, cm, bound, n ++ "a", True{}), Nest.calls(b, cm, Pat.vars(pt, bound), n ++ "b", True{})}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Nest.calls(a, cm, bound, n ++ "a", True{}), Nest.calls(Core.EMatch{t, cases}, cm, bound, n ++ "b", False{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Nest.calls(c, cm, bound, n ++ "a", True{}), Nest.calls(Core.EMatch{Nil{}, t}, cm, bound, n ++ "b", False{}))
    case Core.ECase{+ps, b}:
      Core.ECase{ps, Nest.calls(b, cm, Pats.vars(ps, bound), n ++ "a", True{})}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Nest.calls(x, cm, bound, n ++ "a", True{})}
    case Core.EOp{op, a, b}:
      Core.EOp{op, Nest.calls(a, cm, bound, n ++ "a", True{}), Nest.calls(b, cm, bound, n ++ "b", True{})}
    case Core.EAnn{x, ty}:
      Core.EAnn{Nest.calls(x, cm, bound, n ++ "a", True{}), ty}
    case other:
      other

def Nest.leaf(leaf: Bool, e: Core.Expr, +k: String, fs: List<&2, Field>, +names: List<&2, String>, r: UArgs) -> UArgs:
  match leaf:
    case True{}:
      UArgs{args, lets} = r
      UArgs{e <> args, lets}
    case False{}:
      Unb.arg.flat(e, k, List.length(&2, Field, fs), names, r)

# The leaves of components es, and the lets that open the ones not built
# in place.
def Nest.leaves(cs: List<&2, NComp>, es: List<&2, Core.Expr>, +pre: String, +i: U32) -> UArgs:
  match cs es:
    case NComp{+k, +fs} <> ct e <> et:
      Nest.leaf(String.is_empty(k), e, k, fs, Nest.fnames(pre ++ U32.show(i) ++ "_", fs, 0),
        Nest.leaves(ct, et, pre, U32.inc(i)))
    case cl el:
      UArgs{Nil{}, Nil{}}

def Nest.build(r: UArgs, +me: String) -> Core.Expr:
  UArgs{as, lets} = r
  Unb.wrap(lets, Core.ECtor{me, as})

def Nest.pnames(+pre: String, cs: List<&2, NComp>, +i: U32) -> List<&2, String>:
  match cs:
    case Nil{}:
      Nil{}
    case c <> t:
      (pre ++ U32.show(i)) <> Nest.pnames(pre, t, U32.inc(i))

# Any other result: its pair opened.
def Nest.open(e: Core.Expr, +me: String, +cs: List<&2, NComp>, +n: U32) -> Core.Expr:
  +ys = Nest.pnames("_nt" ++ U32.show(n) ++ "_", cs, 0)
  Core.ELet{Core.PCtor{"Tuple", Unb.pvars(ys)}, e, Nest.build(Nest.leaves(cs, Unb.vars(ys), "_nq" ++ U32.show(n) ++ "_", 0), me)}

def Nest.ctor(hit: Bool, +k: String, +es: List<&2, Core.Expr>, +me: String, +cs: List<&2, NComp>, +n: U32) -> Core.Expr:
  match hit:
    case True{}:
      Nest.build(Nest.leaves(cs, es, "_nq" ++ U32.show(n) ++ "_", 0), me)
    case False{}:
      Nest.open(Core.ECtor{k, es}, me, cs, n)

# Whether two components' lists have the same records.
def Nest.same(as: List<&2, NComp>, bs: List<&2, NComp>) -> Bool:
  match as bs:
    case NComp{+k, fs} <> at NComp{+j, gs} <> bt:
      Bool.and(Bool.and(Str.eq(k, j), Nat.is_eq(List.length(&2, Field, fs), List.length(&2, Field, gs))), Nest.same(at, bt))
    case Nil{} Nil{}:
      True{}
    case al bl:
      False{}

def Nest.tcall.go(r: NRet, +g: String, +as: List<&2, Core.Expr>, +me: String, +cs: List<&2, NComp>, +n: U32) -> Core.Expr:
  match r:
    case NRet{+ds, k}:
      Bool.pick(Unit -> Core.Expr, Bool.and(Bool.and(Nest.nested(ds), Nest.same(ds, cs)), Nat.is_eq(k, List.length(&2, Core.Expr, as))),
        u => Core.ECall{Core.EVar{g ++ "%n"}, as}, u => Nest.open(Core.ECall{Core.EVar{g}, as}, me, cs, n))(Unit{})

def Nest.tcall(f: Core.Expr, +as: List<&2, Core.Expr>, +cm: Map<&2, NRet>, +me: String, +cs: List<&2, NComp>, +n: U32) -> Core.Expr:
  match f:
    case Core.EVar{+g}:
      Nest.tcall.go(Nest.get(cm, g), g, as, me, cs, n)
    case other:
      Nest.open(Core.ECall{other, as}, me, cs, n)

# f%n's body: e's results as N%f (me) (n keeps the lets' names apart).
def Nest.tail(e: Core.Expr, +cm: Map<&2, NRet>, +me: String, +cs: List<&2, NComp>, +n: U32) -> Core.Expr:
  match e:
    case Core.ELet{p, v, b}:
      Core.ELet{p, v, Nest.tail(b, cm, me, cs, U32.inc(n))}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(a, Nest.tail(Core.EMatch{t, cases}, cm, me, cs, n))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Nest.tail(c, cm, me, cs, U32.inc(n)), Nest.tail(Core.EMatch{Nil{}, t}, cm, me, cs, n))
    case Core.ECase{ps, b}:
      Core.ECase{ps, Nest.tail(b, cm, me, cs, U32.inc(n))}
    case Core.EAnn{x, ty}:
      Nest.tail(x, cm, me, cs, n)
    case Core.ECtor{+k, +es}:
      Nest.ctor(Bool.and(Str.eq(k, "Tuple"), Nat.is_eq(List.length(&2, Core.Expr, es), List.length(&2, NComp, cs))), k, es, me, cs, n)
    case Core.ECall{f, +as}:
      Nest.tcall(f, as, cm, me, cs, n)
    case other:
      Nest.open(other, me, cs, n)

def Nest.args(ps: List<&2, Core.Param>) -> List<&2, Core.Expr>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Param{x, m, t} <> r:
      Core.EVar{x} <> Nest.args(r)

def Nest.decl.go(r: NRet, +cm: Map<&2, NRet>, +name: String, +ps: List<&2, Core.Param>, body: Core.Expr, +ret: Core.Expr) -> List<&2, Decl>:
  match r:
    case NRet{cs, n}:
      match cs:
        case Nil{}:
          [DDef{name, ps, Nest.calls(body, cm, Nil{}, "", True{}), ret}]
        case +c <> +t:
          [DType{"N%" ++ name, Nil{}, [Ctor{"N%" ++ name, Nest.fields(c <> t)}]},
            DDef{name ++ "%n", ps, Nest.calls(Nest.tail(body, cm, "N%" ++ name, c <> t, 0), cm, Nil{}, "", True{}),
              Core.ETy{"N%" ++ name, Nil{}}},
            DDef{name, ps, Nest.rebuild(name, c <> t, Nest.args(ps), ""), ret}]

def Nest.decl(+cm: Map<&2, NRet>, d: Decl) -> List<&2, Decl>:
  match d:
    case DDef{+name, +ps, body, +ret}:
      Nest.decl.go(Nest.get(cm, name), cm, name, ps, body, ret)
    case other:
      [other]

def Nest.decls(+cm: Map<&2, NRet>, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      List.append(&2, Decl, Nest.decl(cm, d), Nest.decls(cm, t))

def Nest.program(on: Bool, +ds: List<&2, Decl>) -> List<&2, Decl>:
  match on:
    case True{}:
      Nest.decls(Nest.cands(Nest.types(ds, MTip{}), G.laws(ds, MTip{}), ds, MTip{}), ds)
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
def Dps.target(+g: G, +name: String, +args: List<&2, Core.Expr>) -> Bool:
  Dps.target.info(G.def(g, name), List.length(&2, Core.Expr, args))

def Dps.edge(ok: Bool, +to: String, ctor: Bool, acc: List<&2, DEdge>) -> List<&2, DEdge>:
  match ok:
    case True{}:
      DEdge{to, ctor} <> acc
    case False{}:
      acc

def Dps.ctor(+g: G, node: Bool, as: List<&2, Core.Expr>, acc: List<&2, DEdge>) -> List<&2, DEdge>:
  match node as:
    case True{} Core.ECall{Core.EVar{+h}, +hargs} <> t:
      Dps.ctor(g, True{}, t, Dps.edge(Dps.target(g, h, hargs), h, True{}, acc))
    case True{} a <> t:
      Dps.ctor(g, True{}, t, acc)
    case n l:
      acc

# The tail calls of an expression, as Gen.stmt compiles it (a match's:
# its first case's, then the match rebuilt with the other cases).
def Dps.tails(+g: G, e: Core.Expr, acc: List<&2, DEdge>) -> List<&2, DEdge>:
  match e:
    case Core.ELet{p, v, b}:
      Dps.tails(g, b, acc)
    case Core.EMatch{scrs, cases}:
      match cases:
        case Nil{}:
          acc
        case Core.ECase{ps, b} <> t:
          Dps.tails(g, Core.EMatch{scrs, t}, Dps.tails(g, b, acc))
        case other <> t:
          Dps.tails(g, Core.EMatch{scrs, t}, acc)
    case Core.ECall{Core.EVar{+name}, +args}:
      Dps.edge(Dps.target(g, name, args), name, False{}, acc)
    case Core.ECtor{+name, args}:
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

# Borrowed parameters
# -------------------
#
# Counted (BEND_RC=1), a def may borrow a parameter: its caller keeps the
# reference, and drops it after the call when it owned the value (RC.wrap),
# and the def neither takes the nodes it opens in it nor drops it. A
# parameter is borrowed when the def only matches it and passes it, or what
# it reads out of it, where a def borrows; a value read out of it and used
# otherwise gets a reference where it is bound (RC.bdup). A def that does
# that stays borrowing only when it walks on down the value in a tail call
# to itself (a search: Env.find); any other owns the parameter (its nodes
# are for reuse: List.map). A tail call to itself must pass a borrowed value
# where it borrows (the loop has no caller to drop an owned one). Never
# borrowed: the parameters of defs with parallel lets, of destination-
# passing groups, of main and of !-called defs, and one an Array match
# opens.
#
# Bor.ev collects a def's events: a<i> parameter i used (owned), o<i> a
# value read out of it used, t<i> one passed on in a tail call to the def
# itself, x<i> a tail call passing an owned value as parameter i, z<i> an
# Array match opening it (z: out of fuel). A variable's tag is p<i> for
# parameter i (or a name for all of it), f<i> for a value read out of it,
# and "" for any other.
type BorC is Data:
  BorC{g: G, bm: Map<&2, DGrp>, self: String, n: Nat, tmp: Bool}

type BorA is Data:
  BorA{ev: List<&2, String>, xs: List<&2, Core.Expr>}

def BorC.g(c: BorC) -> G:
  BorC{g, bm, self, n, tmp} = c
  g

# Outside of a parallel let's values, where temporaries are made.
def BorC.par(c: BorC, +p: Core.Pat) -> BorC:
  BorC{g, bm, self, n, tmp} = c
  BorC{g, bm, self, n, Bool.and(tmp, Bool.not(RC.tmp.par(p)))}

def BorA.ev(r: BorA) -> List<&2, String>:
  BorA{ev, xs} = r
  ev

def BorA.xs(r: BorA) -> List<&2, Core.Expr>:
  BorA{ev, xs} = r
  xs

def Bor.get(+m: Map<&2, DGrp>, +name: String) -> String:
  DGrp.id(G.get(DGrp, DGrp{"", 0}, m, Bor.key(name)))

def Bor.idx(t: String) -> String:
  match t:
    case SNil{}:
      ""
    case SCon{c, i}:
      i

def Bor.use.tag(t: String, acc: List<&2, String>) -> List<&2, String>:
  match t:
    case SNil{}:
      acc
    case SCon{Chr{+c}, +i}:
      (Bool.pick(String, U32.is_eq(c, 112), "a", "o") ++ i) <> acc

def Bor.found(m: Maybe<&2, String>) -> String:
  match m:
    case Some{t}:
      t
    case None{}:
      ""

def Bor.tag(+tags: Env(), +x: String) -> String:
  Bor.found(Env.find(tags, x))

def Bor.use(+tags: Env(), +x: String, acc: List<&2, String>) -> List<&2, String>:
  Bor.use.tag(Bor.tag(tags, x), acc)

def Bor.uses(xs: List<&2, String>, +tags: Env(), acc: List<&2, String>) -> List<&2, String>:
  match xs:
    case Nil{}:
      acc
    case +x <> t:
      Bor.uses(t, tags, Bor.use(tags, x, acc))

def Bor.binds(xs: List<&2, String>, +t: String, acc: Env()) -> Env():
  match xs:
    case Nil{}:
      acc
    case x <> rest:
      Bind{x, t} <> Bor.binds(rest, t, acc)

def Bor.field(t: String) -> String:
  match t:
    case SNil{}:
      ""
    case SCon{c, i}:
      "f" ++ i

def Bor.pat(p: Core.Pat, +t: String, acc: Env()) -> Env():
  match p:
    case Core.PVar{x}:
      Bind{x, t} <> acc
    case other:
      Bor.binds(Pat.vars(other, Nil{}), Bor.field(t), acc)

def Bor.pats(ps: List<&2, Core.Pat>, ts: List<&2, String>, acc: Env()) -> Env():
  match ps ts:
    case p <> pt t <> tt:
      Bor.pats(pt, tt, Bor.pat(p, t, acc))
    case pl tl:
      Bor.binds(Pats.vars(pl, Nil{}), "", acc)

def Bor.kind.arr(m: Maybe<&2, CInfo>) -> Bool:
  match m:
    case Some{CInfo{tag, ar, kind, s}}:
      U32.is_ge(kind, 5)
    case None{}:
      False{}

def Pat.arr(p: Core.Pat, +g: G) -> Bool:
  match p:
    case Core.PCtor{+n, args}:
      match args:
        case Nil{}:
          Bor.kind.arr(G.ctor(g, n))
        case h <> t:
          Bool.or(Pat.arr(h, g), Pat.arr(Core.PCtor{n, t}, g))
    case Core.PSucc{k, q}:
      Pat.arr(q, g)
    case other:
      False{}

def Bor.arr(hit: Bool, +t: String, acc: List<&2, String>) -> List<&2, String>:
  match hit:
    case True{}:
      ("z" ++ Bor.idx(t)) <> acc
    case False{}:
      acc

def Bor.arrs(ps: List<&2, Core.Pat>, ts: List<&2, String>, +g: G, acc: List<&2, String>) -> List<&2, String>:
  match ps ts:
    case p <> pt +t <> tt:
      Bor.arrs(pt, tt, g, Bor.arr(Bool.and(Bool.not(String.is_empty(t)), Pat.arr(p, g)), t, acc))
    case pl tl:
      acc

def Bor.scr(+tags: Env(), e: Core.Expr) -> String:
  match e:
    case Core.EVar{+x}:
      Bor.tag(tags, x)
    case other:
      ""

def Bor.scrs(xs: List<&2, Core.Expr>, +tags: Env()) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case a <> t:
      Bor.scr(tags, a) <> Bor.scrs(t, tags)

def Bor.keep(k: Bool, a: Core.Expr, rest: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match k:
    case True{}:
      a <> rest
    case False{}:
      rest

# The scrutinees a match takes (the others it borrows).
def Bor.oscrs(xs: List<&2, Core.Expr>, +tags: Env()) -> List<&2, Core.Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case +a <> t:
      Bor.keep(String.is_empty(Bor.scr(tags, a)), a, Bor.oscrs(t, tags))

def Bor.x(st: Bool, +j: U32, acc: List<&2, String>) -> List<&2, String>:
  match st:
    case True{}:
      ("x" ++ U32.show(j)) <> acc
    case False{}:
      acc

def Bor.t(st: Bool, +i: String, acc: List<&2, String>) -> List<&2, String>:
  match st:
    case True{}:
      ("t" ++ i) <> acc
    case False{}:
      acc

def Bor.arg.tag(t: String, st: Bool, +j: U32, r: BorA) -> BorA:
  match t:
    case SNil{}:
      BorA{ev, ys} = r
      BorA{Bor.x(st, j, ev), ys}
    case SCon{c, i}:
      BorA{ev, ys} = r
      BorA{Bor.t(st, i, ev), ys}

# The variables of a temporary (see RC.tmp) are all read out of a
# parameter (tag f<i>).
def Bor.tmp.f(+tags: Env(), as: List<&2, Core.Expr>) -> Bool:
  match as:
    case Nil{}:
      True{}
    case Core.EVar{+x} <> t:
      Bool.and(String.starts_with(Bor.tag(tags, x), "f"), Bor.tmp.f(tags, t))
    case a <> t:
      Bor.tmp.f(tags, t)

# Each variable of a loop's next temporary is lent on (t).
def Bor.tmp.t(+tags: Env(), as: List<&2, Core.Expr>, +j: U32, r: BorA) -> BorA:
  match as:
    case Nil{}:
      r
    case Core.EVar{+x} <> t:
      Bor.tmp.t(tags, t, j, Bor.arg.tag(Bor.tag(tags, x), True{}, j, r))
    case a <> t:
      Bor.tmp.t(tags, t, j, r)

# An argument that is not a variable: a temporary (RC.tmp.syn) is only read
# by the callee, as its variables are: outside of a loop's next arguments
# it lends nothing on, and in them, it is kept in a buffer of the loop's
# (RC_TB), which only holds what is read out of its parameters.
def Bor.arg.x(a: Core.Expr, st: Bool, +j: U32, r: BorA) -> BorA:
  BorA{ev, ys} = r
  BorA{Bor.x(st, j, ev), List.append(&2, Core.Expr, ys, [a])}

def Bor.arg.st(ok: Bool, +a: Core.Expr, +tags: Env(), +j: U32, r: BorA) -> BorA:
  match ok:
    case True{}:
      Bor.tmp.t(tags, RC.tmp.args(a), j, r)
    case False{}:
      Bor.arg.x(a, True{}, j, r)

def Bor.arg.o(tmp: Bool, +a: Core.Expr, +tags: Env(), st: Bool, +j: U32, r: BorA) -> BorA:
  match tmp:
    case True{}:
      match st:
        case True{}:
          Bor.arg.st(Bor.tmp.f(tags, RC.tmp.args(a)), a, tags, j, r)
        case False{}:
          r
    case False{}:
      Bor.arg.x(a, st, j, r)

# An argument where the callee borrows (st: in a tail call to the def
# itself): a tagged variable is lent on.
def Bor.arg.b(+g: G, +rc: Bool, +a: Core.Expr, +tags: Env(), st: Bool, +j: U32, r: BorA) -> BorA:
  match a:
    case Core.EVar{+x}:
      Bor.arg.tag(Bor.tag(tags, x), st, j, r)
    case other:
      Bor.arg.o(Bool.and(rc, RC.tmp.syn(g, other)), other, tags, st, j, r)

# A value read out of a parameter (x, tag f<i>) and passed to a scalar
# parameter (sc) or an operator: a number, which holds no reference (so it
# does not make the def own its parameter).
def Bor.scalar(sc: Bool, +tags: Env(), a: Core.Expr) -> Bool:
  match sc:
    case True{}:
      match a:
        case Core.EVar{+x}:
          String.starts_with(Bor.tag(tags, x), "f")
        case other:
          False{}
    case False{}:
      False{}

# A let's value, but for a variable naming one read out of a parameter
# (which gets its reference there, RC.bdup, as an inlined Char.is_eq's
# do): its uses are the new name's, which is not tagged.
def Bor.letv(+tags: Env(), +p: Core.Pat, +v: Core.Expr) -> Core.Expr:
  match p:
    case Core.PVar{x}:
      Bool.pick(Core.Expr, Bor.scalar(True{}, tags, v), Core.ENum{0}, v)
    case other:
      v

# An operator's operands but the numbers read out of a parameter.
def Bor.ops(+tags: Env(), xs: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case +a <> t:
      Bor.keep(Bool.not(Bor.scalar(True{}, tags, a)), a, Bor.ops(tags, t))

# An argument the callee owns (sc: a scalar parameter's).
def Bor.arg.own.go(hit: Bool, a: Core.Expr, r: BorA) -> BorA:
  match hit:
    case True{}:
      r
    case False{}:
      BorA{ev, ys} = r
      BorA{ev, List.append(&2, Core.Expr, ys, [a])}

def Bor.arg.own(sc: Bool, +tags: Env(), +a: Core.Expr, r: BorA) -> BorA:
  Bor.arg.own.go(Bor.scalar(sc, tags, a), a, r)

def Bor.arg(+g: G, +rc: Bool, sc: Bool, b: Bool, a: Core.Expr, +tags: Env(), st: Bool, +j: U32, r: BorA) -> BorA:
  match b:
    case True{}:
      Bor.arg.b(g, rc, a, tags, st, j, r)
    case False{}:
      Bor.arg.own(sc, tags, a, r)

# A call's events, and the arguments it owns.
def Bor.args(+g: G, +rc: Bool, mask: List<&2, Bool>, args: List<&2, Core.Expr>, +fl: List<&2, Bool>,
  +sc: List<&2, Bool>, +tags: Env(), +st: Bool, +j: U32, r: BorA) -> BorA:
  match mask args:
    case Nil{} xs:
      BorA{ev, ys} = r
      BorA{ev, List.append(&2, Core.Expr, ys, xs)}
    case m <> mt Nil{}:
      r
    case True{} <> mt a <> at:
      Bor.args(g, rc, mt, at, Bor.tail(fl), Bor.tail(sc), tags, st, U32.inc(j),
        Bor.arg(g, rc, Bor.head(sc), Bor.head(fl), a, tags, st, j, r))
    case False{} <> mt a <> at:
      Bor.args(g, rc, mt, at, Bor.tail(fl), Bor.tail(sc), tags, st, U32.inc(j), r)

def Bor.call.name(local: Bool, +cx: BorC, +tags: Env(), +h: String, tail: Bool, +args: List<&2, Core.Expr>,
  acc: List<&2, String>) -> BorA:
  match local:
    case True{}:
      BorA{acc, Core.EVar{h} <> args}
    case False{}:
      BorC{+g, +bm, +self, +n, +tmp} = cx
      +full : Bool = Bool.and(tmp, Nat.is_eq(List.length(&2, Bool, DInfo.mask(G.def(g, h))), List.length(&2, Core.Expr, args)))
      Bor.args(g, full, DInfo.mask(G.def(g, h)), args, Bor.list(Bor.get(bm, h)),
        Bor.list(DGrp.id(G.get(DGrp, DGrp{"", 0}, bm, "%s" ++ h))), tags,
        Bool.and(tail, Bool.and(Str.eq(self, h), Nat.is_eq(n, List.length(&2, Core.Expr, args)))), 0, BorA{acc, Nil{}})

def Bor.call(+cx: BorC, +tags: Env(), +loc: List<&2, String>, tail: Bool, f: Core.Expr, +args: List<&2, Core.Expr>,
  acc: List<&2, String>) -> BorA:
  match f:
    case Core.EVar{+h}:
      Bor.call.name(Bool.or(Str.has(loc, h), Str.eq(h, "%gpu")), cx, tags, h, tail, args, acc)
    case other:
      BorA{acc, other <> args}

# acc and e's events (st: the tags of the scrutinees of the match whose
# cases e holds; tail: e is in tail position).
def Bor.ev(n: Nat, +cx: BorC, +tags: Env(), +loc: List<&2, String>, +st: List<&2, String>, +tail: Bool,
  e: Core.Expr, acc: List<&2, String>) -> List<&2, String>:
  match n:
    case 0n:
      "z" <> acc
    case 1n+ +m:
      match e:
        case Core.EVar{+x}:
          Bor.use(tags, x, acc)
        case Core.ECall{f, +args}:
          +r = Bor.call(cx, tags, loc, tail, f, args, acc)
          Bor.ev(m, cx, tags, loc, st, False{}, Core.ECtor{"", BorA.xs(r)}, BorA.ev(r))
        case Core.ECtor{c, args}:
          match args:
            case Nil{}:
              acc
            case a <> t:
              Bor.ev(m, cx, tags, loc, st, False{}, Core.ECtor{c, t}, Bor.ev(m, cx, tags, loc, st, False{}, a, acc))
        case Core.ELam{+p, +b}:
          Bor.uses(FV.expr(b, Pat.vars(p, Nil{}), Nil{}), tags, acc)
        case Core.ELet{+p, v, b}:
          Bor.ev(m, cx, Bor.binds(Pat.vars(p, Nil{}), "", tags), Pat.vars(p, loc), st, tail, b,
            Bor.ev(m, BorC.par(cx, p), tags, loc, st, False{}, Bor.letv(tags, p, v), acc))
        case Core.EMatch{scrs, cases}:
          match scrs:
            case Nil{}:
              match cases:
                case Nil{}:
                  acc
                case c <> t:
                  Bor.ev(m, cx, tags, loc, st, tail, Core.EMatch{Nil{}, t}, Bor.ev(m, cx, tags, loc, st, tail, c, acc))
            case +a <> +t:
              Bor.ev(m, cx, tags, loc, Bor.scrs(a <> t, tags), tail, Core.EMatch{Nil{}, cases},
                Bor.ev(m, cx, tags, loc, st, False{}, Core.ECtor{"", Bor.oscrs(a <> t, tags)}, acc))
        case Core.ECase{+ps, b}:
          Bor.ev(m, cx, Bor.pats(ps, st, tags), Pats.vars(ps, loc), st, tail, b, Bor.arrs(ps, st, BorC.g(cx), acc))
        case Core.ESucc{k, x}:
          Bor.ev(m, cx, tags, loc, st, False{}, x, acc)
        case Core.EOp{op, a, b}:
          Bor.ev(m, cx, tags, loc, st, False{}, Core.ECtor{"", Bor.ops(tags, [a, b])}, acc)
        case Core.EAnn{x, t}:
          Bor.ev(m, cx, tags, loc, st, False{}, x, acc)
        case other:
          acc

def Bor.gpu.var(+f: String, a: Core.Expr, +acc: List<&2, String>) -> List<&2, String>:
  match a:
    case Core.EVar{x}:
      Bool.pick(List<&2, String>, Str.eq(f, "%gpu"), x <> acc, acc)
    case other:
      acc

def Bor.gpu(+f: Core.Expr, +a: Core.Expr, acc: List<&2, String>) -> List<&2, String>:
  match f:
    case Core.EVar{+h}:
      Bor.gpu.var(h, a, acc)
    case other:
      acc

# The targets of !-calls in e (and, harmlessly, any variable passed to one).
def Expr.gpus(e: Core.Expr, acc: List<&2, String>) -> List<&2, String>:
  match e:
    case Core.ECall{+f, args}:
      match args:
        case Nil{}:
          Expr.gpus(f, acc)
        case +a <> t:
          Expr.gpus(Core.ECall{f, t}, Expr.gpus(a, Bor.gpu(f, a, acc)))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          acc
        case a <> t:
          Expr.gpus(Core.ECtor{n, t}, Expr.gpus(a, acc))
    case Core.ELam{p, b}:
      Expr.gpus(b, acc)
    case Core.ELet{p, v, b}:
      Expr.gpus(b, Expr.gpus(v, acc))
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.gpus(Core.EMatch{t, cases}, Expr.gpus(a, acc))
        case Nil{}:
          match cases:
            case Nil{}:
              acc
            case c <> t:
              Expr.gpus(Core.EMatch{Nil{}, t}, Expr.gpus(c, acc))
    case Core.ECase{ps, b}:
      Expr.gpus(b, acc)
    case Core.ESucc{k, x}:
      Expr.gpus(x, acc)
    case Core.EOp{op, a, b}:
      Expr.gpus(b, Expr.gpus(a, acc))
    case Core.EAnn{x, t}:
      Expr.gpus(x, acc)
    case other:
      acc

def Bor.gpus(ds: List<&2, Decl>, acc: List<&2, String>) -> List<&2, String>:
  match ds:
    case Nil{}:
      acc
    case DDef{name, ps, body, ret} <> t:
      Bor.gpus(t, Expr.gpus(body, acc))
    case d <> t:
      Bor.gpus(t, acc)

# The flags a def starts from: its kept parameters that hold no scalar.
def Bor.cand(ps: List<&2, Core.Param>, mask: List<&2, Bool>) -> String:
  match ps mask:
    case Core.Param{x, m, t} <> pt True{} <> mt:
      Bool.pick(String, Gen.scalar.ty(t), "0", "1") ++ Bor.cand(pt, mt)
    case Core.Param{x, m, t} <> pt False{} <> mt:
      "0" ++ Bor.cand(pt, mt)
    case pl ml:
      ""

# A def's scalar parameters ("1"), kept for every def under "%s" and its
# name: a variable passed to one is used, but holds no reference.
def Bor.scal(ps: List<&2, Core.Param>) -> String:
  match ps:
    case Nil{}:
      ""
    case Core.Param{x, m, +t} <> pt:
      Bool.pick(String, Gen.scalar.ty(t), "1", "0") ++ Bor.scal(pt)

def Bor.ok(+g: G, +name: String, +gpus: List<&2, String>, +body: Core.Expr) -> Bool:
  Bool.and(Bool.and(U32.is_eq(DInfo.kind(G.def(g, name)), 0), String.is_empty(DGrp.id(G.dps(g, name)))),
    Bool.and(Bool.not(Str.eq(name, "main")), Bool.and(Bool.not(Str.has(gpus, name)), Bool.not(Expr.has_par(body)))))

def Bor.init.one(ok: Bool, +name: String, ps: List<&2, Core.Param>, mask: List<&2, Bool>, m: Map<&2, DGrp>) ->
  Map<&2, DGrp>:
  match ok:
    case True{}:
      Map.set(&2, DGrp, m, Bor.key(name), DGrp{Bor.cand(ps, mask), 0})
    case False{}:
      m

def Bor.init(ds: List<&2, Decl>, +g: G, +gpus: List<&2, String>, m: Map<&2, DGrp>) -> Map<&2, DGrp>:
  match ds:
    case Nil{}:
      m
    case DDef{+name, +ps, +body, ret} <> t:
      Bor.init(t, g, gpus, Bor.init.one(Bor.ok(g, name, gpus, body), name, ps, DInfo.mask(G.def(g, name)),
        Map.set(&2, DGrp, m, "%s" ++ name, DGrp{Bor.scal(ps), 0})))
    case d <> t:
      Bor.init(t, g, gpus, m)

def Bor.tags(ps: List<&2, Core.Param>, +fl: List<&2, Bool>, +i: U32, acc: Env()) -> Env():
  match ps:
    case Nil{}:
      acc
    case Core.Param{x, m, t} <> pt:
      Bor.tags(pt, Bor.tail(fl), U32.inc(i), Bind{x, Bool.pick(String, Bor.head(fl), "p" ++ U32.show(i), "")} <> acc)

def Bor.names(ps: List<&2, Core.Param>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Param{x, m, t} <> pt:
      x <> Bor.names(pt)

def Bor.keep1(b: Bool, +ev: List<&2, String>, +i: String) -> Bool:
  match b:
    case False{}:
      False{}
    case True{}:
      Bool.and(Bool.not(Bool.or(Bool.or(Str.has(ev, "a" ++ i), Str.has(ev, "x" ++ i)),
        Bool.or(Str.has(ev, "z" ++ i), Str.has(ev, "z")))),
        Bool.or(Bool.not(Str.has(ev, "o" ++ i)), Str.has(ev, "t" ++ i)))

def Bor.next(fl: List<&2, Bool>, +ev: List<&2, String>, +i: U32) -> String:
  match fl:
    case Nil{}:
      ""
    case b <> t:
      Bool.pick(String, Bor.keep1(b, ev, U32.show(i)), "1", "0") ++ Bor.next(t, ev, U32.inc(i))

# A def's flags, given everyone's (bm) and its own (fl).
def Bor.def(+g: G, +bm: Map<&2, DGrp>, +name: String, +ps: List<&2, Core.Param>, +body: Core.Expr, +fl: List<&2, Bool>) ->
  String:
  Bor.next(fl, Bor.ev(Fuel.max(), BorC{g, bm, name, List.length(&2, Bool, DInfo.mask(G.def(g, name))), True{}},
    Bor.tags(ps, fl, 0, Nil{}), Bor.names(ps), Nil{}, True{}, R.ops(body, "Nat"), Nil{}), 0)

type BorP is Data:
  BorP{m: Map<&2, DGrp>, ch: Bool}

def BorP.m(r: BorP) -> Map<&2, DGrp>:
  BorP{m, ch} = r
  m

def BorP.ch(r: BorP) -> Bool:
  BorP{m, ch} = r
  ch

def Bor.step(same: Bool, +name: String, +nw: String, m: Map<&2, DGrp>, ch: Bool) -> BorP:
  match same:
    case True{}:
      BorP{m, ch}
    case False{}:
      BorP{Map.set(&2, DGrp, m, Bor.key(name), DGrp{nw, 0}), True{}}

def Bor.redo(any: Bool, +g: G, +name: String, +ps: List<&2, Core.Param>, +body: Core.Expr, +old: String, +m: Map<&2, DGrp>,
  ch: Bool) -> BorP:
  match any:
    case False{}:
      BorP{m, ch}
    case True{}:
      +nw = Bor.def(g, m, name, ps, body, Bor.list(old))
      Bor.step(Str.eq(old, nw), name, nw, m, ch)

def Bor.redo.m(+g: G, +name: String, +ps: List<&2, Core.Param>, +body: Core.Expr, r: BorP) -> BorP:
  BorP{+m, ch} = r
  +old = Bor.get(m, name)
  Bor.redo(Bool.and(Bor.any(Bor.list(old)), U32.is_eq(DInfo.kind(G.def(g, name)), 0)), g, name, ps, body, old,
    m, ch)

def Bor.pass(ds: List<&2, Decl>, +g: G, r: BorP) -> BorP:
  match ds:
    case Nil{}:
      r
    case DDef{+name, +ps, +body, ret} <> t:
      Bor.pass(t, g, Bor.redo.m(g, name, ps, body, r))
    case d <> t:
      Bor.pass(t, g, r)

# Passes until no flag changes (flags only go from 1 to 0); out of fuel,
# none is borrowed (orig).
def Bor.fix(n: Nat, +ds: List<&2, Decl>, +g: G, m: Map<&2, DGrp>, +orig: Map<&2, DGrp>) -> Map<&2, DGrp>:
  match n:
    case 0n:
      orig
    case 1n+ +k:
      +r = Bor.pass(ds, g, BorP{m, False{}})
      Bool.pick(Unit -> Map<&2, DGrp>, BorP.ch(r), u => Bor.fix(k, ds, g, BorP.m(r), orig), u => BorP.m(r))(Unit{})

def Bor.build.go(+g: G, +ds: List<&2, Decl>, +m: Map<&2, DGrp>) -> Map<&2, DGrp>:
  Bor.fix(64n, ds, g, Bor.init(ds, g, Bor.gpus(ds, Nil{}), m), m)

# (the runtime's String.eq borrows both strings)
def Bor.build(rc: Bool, +g: G, +ds: List<&2, Decl>, +m: Map<&2, DGrp>) -> Map<&2, DGrp>:
  match rc:
    case False{}:
      m
    case True{}:
      Bor.build.go(g, ds, Map.set(&2, DGrp, m, Bor.key("String.eq"), DGrp{"11", 0}))

# "%free" holds the memory mode: 0 traced only, 1 matches free what they
# open, 2 reference counted.
def Dps.build(+g: G, +ds: List<&2, Decl>, free: Bool, +rc: Bool) -> G:
  +em = Dps.edges(g, ds, MTip{})
  +ks = Map.keys(&2, List<&2, DEdge>, em)
  +m = Map.set(&2, DGrp, Dps.groups(g, ks, em, Dps.rev(ks, em, MTip{}), MTip{}), "%free",
    DGrp{Bool.pick(String, rc, "2", Bool.pick(String, free, "1", "0")), 0})
  G.with_dps(g, Bor.build(rc, G.with_dps(g, m), ds, m))

# Value printers
# ==============

type TB is Data:
  TB{name: String, ty: Core.Expr}

def Ty.args(e: Core.Expr) -> List<&2, Core.Expr>:
  match e:
    case Core.ETy{n, args}:
      args
    case Core.ECall{f, args}:
      args
    case other:
      Nil{}

def Ty.bind.go(ps: List<&2, String>, xs: List<&2, Core.Expr>) -> List<&2, TB>:
  match ps xs:
    case p <> pt x <> xt:
      TB{p, x} <> Ty.bind.go(pt, xt)
    case pl xl:
      Nil{}

# Binds type parameters to arguments, aligned from the right (a leading
# quantity argument may be left out).
def Ty.bind(ps: List<&2, String>, xs: List<&2, Core.Expr>) -> List<&2, TB>:
  Ty.bind.go(List.reverse(&2, String, ps), List.reverse(&2, Core.Expr, xs))

# A type alias unfolded (law Entry: Type; def Entry(): Program(Unit) is
# IO(Unit)): a def of Type whose body is a type, not a match on its
# arguments, stands for its body. The printers' own heads stay.
def Ty.norm.stop(+h: String) -> Bool:
  List.contains(~String, ~String.eq, ["IO", "U32", "Nat", "F32", "Char", "String", "List",
    "&", "->", "Array", "==", "Sigma", "Bool", "Type", "", "?"], h)

def Ty.pnames(ps: List<&2, Core.Param>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Param{n, m, t} <> rest:
      n <> Ty.pnames(rest)

def Ty.norm.body(b: Core.Expr) -> Bool:
  match b:
    case Core.ETy{n, a}:
      True{}
    case Core.EVar{n}:
      True{}
    case Core.ECall{Core.EVar{n}, a}:
      True{}
    case Core.EMatch{xs, cs}:
      True{}
    case other:
      False{}

def Ty.find(sub: List<&2, TB>, +x: String) -> Maybe<&2, Core.Expr>:
  match sub:
    case Nil{}:
      None{}
    case TB{+n, t} <> rest:
      Bool.pick(Unit -> Maybe<&2, Core.Expr>, String.eq(n, x), u => Some{t}, u => Ty.find(rest, x))(Unit{})

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

def Ty.subst(e: Core.Expr, +sub: List<&2, TB>) -> Core.Expr:
  match e:
    case Core.EVar{+n}:
      Maybe.default(&2, Core.Expr, Ty.find(sub, n), Core.EVar{n})
    case Core.ETy{n, args}:
      match args:
        case Nil{}:
          Core.ETy{n, Nil{}}
        case a <> t:
          Expr.push(Ty.subst(a, sub), Ty.subst(Core.ETy{n, t}, sub))
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{f, Nil{}}
        case a <> t:
          Expr.push(Ty.subst(a, sub), Ty.subst(Core.ECall{f, t}, sub))
    case Core.ELam{p, b}:
      Core.ELam{p, Ty.subst(b, sub)}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Ty.subst(a, sub), Ty.subst(Core.EMatch{t, cases}, sub))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Ty.subst(c, sub), Ty.subst(Core.EMatch{Nil{}, t}, sub))
    case Core.ECase{+ps, b}:
      Core.ECase{ps, Ty.subst(b, Ty.unbind(sub, Pats.vars(ps, Nil{})))}
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

def Ty.pm.nat(+n: U32, e: Core.Expr) -> PM:
  match e:
    case Core.ENat{+m}:
      Ty.pm.is(U32.is_eq(n, m))
    case Core.ESucc{+k, x}:
      Bool.pick(PM, U32.is_lt(n, k), PM{0n, Nil{}}, PM{2n, Nil{}})
    case other:
      PM{2n, Nil{}}

def Ty.pm.num(+n: U32, e: Core.Expr) -> PM:
  match e:
    case Core.ENum{+m}:
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
def Ty.pm.go(p: Core.Pat, e: Core.Expr, lst: Bool) -> PM:
  match p:
    case Core.PVar{+x}:
      PM{1n, Bool.pick(List<&2, TB>, Str.eq(x, "_"), Nil{}, [TB{x, e}])}
    case Core.PCtor{+n, ps}:
      match ps:
        case q <> pt:
          match e:
            case Core.ECtor{+m, es}:
              match es:
                case x <> et:
                  Ty.pm.at(lst, n, m,
                    Ty.pm.both(Ty.pm.go(q, x, False{}), Ty.pm.go(Core.PCtor{n, pt}, Core.ECtor{m, et}, True{})))
                case Nil{}:
                  Ty.pm.at(lst, n, m, PM{0n, Nil{}})
            case other:
              PM{2n, Nil{}}
        case Nil{}:
          match e:
            case Core.ECtor{+m, es}:
              match es:
                case Nil{}:
                  Ty.pm.at(lst, n, m, PM{1n, Nil{}})
                case x <> et:
                  Ty.pm.at(lst, n, m, PM{0n, Nil{}})
            case other:
              PM{2n, Nil{}}
    case Core.PNat{+n}:
      Ty.pm.nat(n, e)
    case Core.PSucc{+k, q}:
      match e:
        case Core.ENat{+m}:
          Bool.pick(Unit -> PM, U32.is_ge(m, k), u => Ty.pm.go(q, Core.ENat{(m - k : U32)}, False{}),
            u => PM{0n, Nil{}})(Unit{})
        case Core.ESucc{+j, x}:
          Bool.pick(Unit -> PM, U32.is_eq(j, k), u => Ty.pm.go(q, x, False{}),
            u => PM{2n, Nil{}})(Unit{})
        case other:
          PM{2n, Nil{}}
    case Core.PNum{+n}:
      Ty.pm.num(n, e)
    case Core.PFlt{s}:
      PM{2n, Nil{}}

def Ty.pm(p: Core.Pat, e: Core.Expr) -> PM:
  Ty.pm.go(p, e, False{})

def Ty.pms(ps: List<&2, Core.Pat>, es: List<&2, Core.Expr>) -> PM:
  Ty.pm.go(Core.PCtor{"", ps}, Core.ECtor{"", es}, True{})

# A type no value has (a datatype without constructors, Empty).
def Ty.void.d(d: Decl) -> Bool:
  match d:
    case DType{n, ps, Nil{}}:
      True{}
    case other:
      False{}

def Ty.void(+g: G, +t: Core.Expr) -> Bool:
  Ty.void.d(G.body(g, "%" ++ Ty.head(t)))

def Ty.shows(xs: List<&2, Core.Expr>) -> List<&2, String>:
  match xs:
    case Nil{}:
      Nil{}
    case +h <> t:
      Expr.show(h) <> Ty.shows(t)

def Ty.pick.add(h: Core.Expr, acc: List<&2, Core.Expr>, skip: Bool) -> List<&2, Core.Expr>:
  match skip:
    case True{}:
      acc
    case False{}:
      h <> acc

def Ty.pick.go(+g: G, xs: List<&2, Core.Expr>, +acc: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match xs:
    case Nil{}:
      acc
    case +h <> t:
      Ty.pick.go(g, t, Ty.pick.add(h, acc,
        Bool.or(Ty.void(g, h), Str.has(Ty.shows(acc), Expr.show(h)))))

def Ty.pick.first(all: List<&2, Core.Expr>) -> Core.Expr:
  match all:
    case h <> t:
      h
    case Nil{}:
      Core.ETy{"?", Nil{}}

def Ty.pick.one(xs: List<&2, Core.Expr>, all: List<&2, Core.Expr>) -> Core.Expr:
  match xs:
    case h <> Nil{}:
      h
    case Nil{}:
      Ty.pick.first(all)
    case other:
      Core.ETy{"?", Nil{}}

# A match on a value the type does not know yet stands for the one
# inhabited type its arms can give (LE(r, 1n) is Unit, as its other
# arm is Empty); with none or more than one it prints ?.
def Ty.pick(+g: G, +xs: List<&2, Core.Expr>) -> Core.Expr:
  Ty.pick.one(Ty.pick.go(g, xs, Nil{}), xs)

# Type normalization is one def, Ty.rec, over a selector: each TS.. names
# one of its steps and carries that step's arguments; TSel.ty is the step's
# result. Fuel bounds the recursion (a def's body after substitution is no
# smaller); the steps' own fuel bounds how often a def unfolds.
type TSel is Data:
  TSNorm{ty: Core.Expr, fuel: Nat}
  TSAt{ty: Core.Expr, h: String, fuel: Nat, stop: Bool}
  TSDef{ty: Core.Expr, d: Decl, fuel: Nat}
  TSGo{ty: Core.Expr, ps: List<&2, Core.Param>, b: Core.Expr, fuel: Nat, ok: Bool}
  TSDeep{ty: Core.Expr, fuel: Nat}
  TSNorms{xs: List<&2, Core.Expr>, fuel: Nat}
  TSCands{scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>, fuel: Nat}
  TSCandsAt{scrs: List<&2, Core.Expr>, b: Core.Expr, t: List<&2, Core.Expr>, fuel: Nat, m: PM}

def TSel.ty(k: TSel) -> Type:
  match k:
    case TSNorms{xs, fuel}:
      List<&2, Core.Expr>
    case TSCands{scrs, cases, fuel}:
      List<&2, Core.Expr>
    case TSCandsAt{scrs, b, t, fuel, m}:
      List<&2, Core.Expr>
    case other:
      Core.Expr

# Out of fuel: a value of the step's type.
def TSel.none(k: TSel) -> TSel.ty(k):
  match k:
    case TSNorm{ty, fuel}:
      Core.ETy{"%out of fuel", Nil{}}
    case TSAt{ty, h, fuel, stop}:
      Core.ETy{"%out of fuel", Nil{}}
    case TSDef{ty, d, fuel}:
      Core.ETy{"%out of fuel", Nil{}}
    case TSGo{ty, ps, b, fuel, ok}:
      Core.ETy{"%out of fuel", Nil{}}
    case TSDeep{ty, fuel}:
      Core.ETy{"%out of fuel", Nil{}}
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
            case Core.ETy{n, args}:
              Core.ETy{n, Ty.rec(fu, g, TSNorms{args, fuel})}
            case Core.ECall{f, args}:
              Core.ECall{f, Ty.rec(fu, g, TSNorms{args, fuel})}
            case Core.ELam{p, b}:
              Core.ELam{p, Ty.rec(fu, g, TSNorm{b, fuel})}
            case Core.EMatch{scrs, cases}:
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
            case Core.ECase{ps, b} <> t:
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

def Ty.norm(+g: G, +ty: Core.Expr, fuel: Nat) -> Core.Expr:
  Ty.rec(Fuel.max(), g, TSNorm{ty, fuel})

def Gen.printer.test(+kind: U32, +tag: U32, single: Bool) -> String:
  Bool.pick(String, single, "if (1)",
    Bool.pick(String, U32.is_eq(kind, 1), "if (v == IMM(" ++ U32.show(tag) ++ "))",
      "if (!(v & 1) && TAG(v) == " ++ U32.show(tag) ++ ")"))

# A dependent pair prints as a pair.
def Ty.alias(+h: String) -> String:
  Bool.pick(String, Str.eq(h, "Sigma"), "&", h)

# Components of a (right-nested) pair type.
def Ty.tuple(e: Core.Expr) -> List<&2, Core.Expr>:
  match e:
    case Core.ETy{+n, args}:
      match args:
        case +a <> +b <> Nil{}:
          Bool.pick(Unit -> List<&2, Core.Expr>, Str.eq(n, "&"), u => a <> Ty.tuple(b),
            u => [Core.ETy{n, [a, b]}])(Unit{})
        case +a <> +b <> +x <> f <> fs:
          match f:
            case Core.ELam{+p, +bd}:
              match fs:
                case Nil{}:
                  Bool.pick(Unit -> List<&2, Core.Expr>, Str.eq(n, "Sigma"), u => x <> Ty.tuple(bd),
                    u => [Core.ETy{n, [a, b, x, Core.ELam{p, bd}]}])(Unit{})
                case other:
                  [Core.ETy{n, a <> b <> x <> Core.ELam{p, bd} <> other}]
            case +g:
              match fs:
                case Nil{}:
                  Bool.pick(Unit -> List<&2, Core.Expr>, Str.eq(n, "Sigma"), u => x <> Ty.tuple(g),
                    u => [Core.ETy{n, [a, b, x, g]}])(Unit{})
                case other:
                  [Core.ETy{n, a <> b <> x <> g <> other}]
        case other:
          [Core.ETy{n, other}]
    case other:
      [other]

# The value printers are one def, Gen.printer.rec, over a selector: each
# PS.. names one of its steps and carries that step's arguments; PSel.ty is
# the step's result. Fuel bounds the recursion (a type's fields are no
# smaller than the type).
type PSel is Data:
  PSPrinter{ty0: Core.Expr}
  PSTuple{xs: List<&2, Core.Expr>, path: String}
  PSFields{sub: List<&2, TB>, fs: List<&2, Field>, path: String, i: U32}
  PSCtor{sub: List<&2, TB>, name: String, fields: List<&2, Field>, info: Maybe<&2, CInfo>}
  PSCtors{sub: List<&2, TB>, cs: List<&2, Ctor>}
  PSAdt{ty: Core.Expr, d: Decl}
  PSHead{ty: Core.Expr, k: Nat}
  PSBody{ty: Core.Expr, h: String}
  PSMemo{ty: Core.Expr, key: String, m: Maybe<&2, String>}

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
def Gen.printer(+g: G, +ty: Core.Expr) -> Gen(String):
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

def Mod.param_names(ps: List<&2, Core.Param>) -> List<&2, String>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Param{n, m, t} <> rest:
      n <> Mod.param_names(rest)

def Mod.var(+q: Qual, +bound: List<&2, String>, +x: String) -> String:
  Bool.pick(String, Str.has(bound, x), x, Mod.q(q, x))

# p with a in front of its fields (see Expr.push).
def Pat.push(a: Core.Pat, p: Core.Pat) -> Core.Pat:
  match p:
    case Core.PCtor{n, xs}:
      Core.PCtor{n, a <> xs}
    case other:
      other

def Mod.pat(+q: Qual, p: Core.Pat) -> Core.Pat:
  match p:
    case Core.PCtor{n, args}:
      match args:
        case Nil{}:
          Core.PCtor{Mod.q(q, n), Nil{}}
        case a <> t:
          Pat.push(Mod.pat(q, a), Mod.pat(q, Core.PCtor{n, t}))
    case Core.PSucc{k, x}:
      Core.PSucc{k, Mod.pat(q, x)}
    case other:
      other

def Mod.pats(+q: Qual, ps: List<&2, Core.Pat>) -> List<&2, Core.Pat>:
  match ps:
    case Nil{}:
      Nil{}
    case h <> t:
      Mod.pat(q, h) <> Mod.pats(q, t)

# Renames references to module names (locals shadow them).
def Mod.go(+q: Qual, e: Core.Expr, +bound: List<&2, String>) -> Core.Expr:
  match e:
    case Core.EVar{x}:
      Core.EVar{Mod.var(q, bound, x)}
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{Mod.go(q, f, bound), Nil{}}
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, Core.ECall{f, t}, bound))
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          Core.ECtor{Mod.q(q, n), Nil{}}
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, Core.ECtor{n, t}, bound))
    case Core.ELam{+p, b}:
      Core.ELam{Mod.pat(q, p), Mod.go(q, b, Pat.vars(p, bound))}
    case Core.ELet{+p, v, b}:
      Core.ELet{Mod.pat(q, p), Mod.go(q, v, bound), Mod.go(q, b, Pat.vars(p, bound))}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, Core.EMatch{t, cases}, bound))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
            case c <> t:
              Expr.push.case(Mod.go(q, c, bound), Mod.go(q, Core.EMatch{Nil{}, t}, bound))
    case Core.ECase{+ps, b}:
      Core.ECase{Mod.pats(q, ps), Mod.go(q, b, Pats.vars(ps, bound))}
    case Core.ESucc{k, x}:
      Core.ESucc{k, Mod.go(q, x, bound)}
    case Core.EOp{op, a, b}:
      Core.EOp{op, Mod.go(q, a, bound), Mod.go(q, b, bound)}
    case Core.EAnn{x, t}:
      Core.EAnn{Mod.go(q, x, bound), Mod.var(q, bound, t)}
    case Core.ETy{n, args}:
      match args:
        case Nil{}:
          Core.ETy{Mod.var(q, bound, n), Nil{}}
        case a <> t:
          Expr.push(Mod.go(q, a, bound), Mod.go(q, Core.ETy{n, t}, bound))
    case other:
      other

def Mod.expr(+q: Qual, +bound: List<&2, String>, e: Core.Expr) -> Core.Expr:
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

# BEND_RC=1: reference counting (see "Reference counting" in bendrt.h).
def Main.rc(r: Result<&1, &1, U32 & String, String>) -> Bool:
  match r:
    case Done{v}:
      String.eq(v, "1")
    case Fail{e}:
      False{}

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

# Unboxed parameters (see Unb.program): on unless BEND_UNBOX=0.
def Main.unbox(r: Result<&1, &1, U32 & String, String>) -> Bool:
  match r:
    case Done{v}:
      Bool.not(String.eq(v, "0"))
    case Fail{e}:
      True{}

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

def LM.pvars(xs: List<&2, String>) -> List<&2, Core.Pat>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      Core.PVar{x} <> LM.pvars(t)

def LM.evars(xs: List<&2, String>) -> List<&2, Core.Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case x <> t:
      Core.EVar{x} <> LM.evars(t)

def LM.app(h: Core.Expr, +xs: List<&2, String>) -> List<&2, Core.Pat> & Core.Expr:
  (LM.pvars(xs), Core.ECall{h, LM.evars(xs)})

def LM.cons(p: Core.Pat, r: List<&2, Core.Pat> & Core.Expr) -> List<&2, Core.Pat> & Core.Expr:
  (ps, b) = r
  (p <> ps, b)

# An arm's field patterns and body.
def LM.fields(h: Core.Expr, n: Nat, +i: U32) -> List<&2, Core.Pat> & Core.Expr:
  match h n:
    case Core.ELam{Core.PVar{x}, b} 1n+p:
      LM.cons(Core.PVar{x}, LM.fields(b, p, (i + 1 : U32)))
    case other 0n:
      (Nil{}, other)
    case other 1n+p:
      LM.app(other, LM.names(1n+p, i))

def LM.arm(+c: String, r: List<&2, Core.Pat> & Core.Expr) -> Core.Expr:
  (ps, b) = r
  Core.ECase{[Core.PCtor{c, ps}], b}

def LM.dflt(m: Core.Expr) -> Core.Expr:
  match m:
    case Core.ELam{Core.PVar{y}, b}:
      Core.ECase{[Core.PVar{y}], b}
    case other:
      Core.ECase{[Core.PVar{"_lm"}], Core.ECall{other, [Core.EVar{"_lm"}]}}

def LM.arms(+ds: List<&2, Decl>, e: Core.Expr) -> List<&2, Core.Expr>:
  match e:
    case Core.ECtor{"%mat", Core.ECtor{+c, cn} <> h <> m <> Nil{}}:
      LM.arm(c, LM.fields(h, LM.arity(ds, c), 0)) <> LM.arms(ds, m)
    case Core.ECtor{"%efq", Nil{}}:
      Nil{}
    case other:
      [LM.dflt(other)]

def LM.ctor(+ds: List<&2, Decl>, +n: String, args: List<&2, Core.Expr>, mat: Bool) -> Core.Expr:
  match mat:
    case True{}:
      Core.ELam{Core.PVar{"_lm"}, Core.EMatch{[Core.EVar{"_lm"}], LM.arms(ds, Core.ECtor{n, args})}}
    case False{}:
      Core.ECtor{n, args}

# x in front of a node's first list (a call's or constructor's arguments,
# a match's scrutinees).
def LM.push(x: Core.Expr, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.ECall{f, xs}:
      Core.ECall{f, x <> xs}
    case Core.ECtor{n, xs}:
      Core.ECtor{n, x <> xs}
    case Core.EMatch{xs, cs}:
      Core.EMatch{x <> xs, cs}
    case other:
      other

# c in front of a match's cases.
def LM.push.case(c: Core.Expr, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.EMatch{xs, cs}:
      Core.EMatch{xs, c <> cs}
    case other:
      other

def LM.ctor.top(+ds: List<&2, Decl>, e: Core.Expr) -> Core.Expr:
  match e:
    case Core.ECtor{+n, args}:
      LM.ctor(ds, n, args, Str.eq(n, "%mat"))
    case other:
      other

# Whether the body b never reads x.
def LM.dead(+x: String, +b: Core.Expr) -> Bool:
  U32.is_zero(Use.n(x, b))

# A node's lists are walked one element at a time, the rest on the same
# node (smaller); raw leaves a constructor's %mat for its caller.
# A let whose name the body never reads is dropped (its value is pure):
# a proof bound only for a rewrite (e = add_comm(a, b); %e : T; ..)
# never runs.
def LM.go(+ds: List<&2, Decl>, e: Core.Expr, raw: Bool) -> Core.Expr:
  match e:
    case Core.ECall{f, args}:
      match args:
        case Nil{}:
          Core.ECall{LM.go(ds, f, False{}), Nil{}}
        case a <> t:
          LM.push(LM.go(ds, a, False{}), LM.go(ds, Core.ECall{f, t}, False{}))
    case Core.ECtor{+n, args}:
      match args:
        case Nil{}:
          Bool.pick(Unit -> Core.Expr, raw, u => Core.ECtor{n, Nil{}},
            u => LM.ctor(ds, n, Nil{}, Str.eq(n, "%mat")))(Unit{})
        case a <> t:
          +r = {LM.push(LM.go(ds, a, False{}), LM.go(ds, Core.ECtor{n, t}, True{})) : Core.Expr}
          Bool.pick(Unit -> Core.Expr, raw, u => r, u => LM.ctor.top(ds, r))(Unit{})
    case Core.ELam{p, b}:
      Core.ELam{p, LM.go(ds, b, False{})}
    case Core.ELet{p, v, b}:
      match p:
        case Core.PVar{+x}:
          +b2 = {LM.go(ds, b, False{}) : Core.Expr}
          Bool.pick(Unit -> Core.Expr, LM.dead(x, b2), u => b2,
            u => Core.ELet{Core.PVar{x}, LM.go(ds, v, False{}), b2})(Unit{})
        case other:
          Core.ELet{other, LM.go(ds, v, False{}), LM.go(ds, b, False{})}
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          LM.push(LM.go(ds, a, False{}), LM.go(ds, Core.EMatch{t, cases}, False{}))
        case Nil{}:
          match cases:
            case c <> t:
              LM.push.case(LM.go(ds, c, False{}), LM.go(ds, Core.EMatch{Nil{}, t}, False{}))
            case Nil{}:
              Core.EMatch{Nil{}, Nil{}}
    case Core.ECase{ps, b}:
      Core.ECase{ps, LM.go(ds, b, False{})}
    case Core.ESucc{k, x}:
      Core.ESucc{k, LM.go(ds, x, False{})}
    case Core.EOp{op, a, b}:
      Core.EOp{op, LM.go(ds, a, False{}), LM.go(ds, b, False{})}
    case Core.EAnn{x, t}:
      Core.EAnn{LM.go(ds, x, False{}), t}
    case other:
      other

def LM.expr(+ds: List<&2, Decl>, e: Core.Expr) -> Core.Expr:
  LM.go(ds, e, False{})

def LM.body(+all: List<&2, Decl>, b: Core.Expr, claim: Bool) -> Core.Expr:
  match claim:
    case True{}:
      Core.ETy{"", Nil{}}
    case False{}:
      LM.expr(all, b)

# A def whose type is a claim {a == b : T} is its proof, erased: it never
# runs (it may take structural views of words the compiled lanes refuse).
# (laws: each law's type, see LM.laws)
def LM.decl(+all: List<&2, Decl>, +laws: Map<&2, Core.Expr>, d: Decl) -> Decl:
  match d:
    case DDef{+n, ps, b, +ret}:
      DDef{n, ps, LM.body(all, b, Bool.or(Str.eq(Ty.head(ret), "=="),
        Str.eq(Ty.head(G.get(Core.Expr, Core.ETy{"", Nil{}}, laws, n)), "=="))), ret}
    case other:
      other

def LM.decls.go(+all: List<&2, Decl>, +laws: Map<&2, Core.Expr>, ds: List<&2, Decl>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      LM.decl(all, laws, d) <> LM.decls.go(all, laws, t)

# The type of each name's law (the first that declares it, so ds is read
# from its end).
def LM.laws(ds: List<&2, Decl>, m: Map<&2, Core.Expr>) -> Map<&2, Core.Expr>:
  match ds:
    case Nil{}:
      m
    case DLaw{n, ps, ret} <> t:
      LM.laws(t, Map.set(&2, Core.Expr, m, n, ret))
    case other <> t:
      LM.laws(t, m)

def LM.decls(+all: List<&2, Decl>, ds: List<&2, Decl>) -> List<&2, Decl>:
  LM.decls.go(all, LM.laws(List.reverse(&2, Decl, all), MTip{}), ds)

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
  IO.die(Unit, 1, "usage: bendc [--check-only | --no-check | --js | -o <binary> | --native -o <binary>] <base.bend> <input.bend> | --tokens <file> | --ast <file>")

# The option an argument names (0: none). The driver matches on this number,
# not on string patterns, which the official compiler expands char by char.
def Main.code(+s: String) -> Nat:
  Bool.pick(Nat, Str.eq(s, "--tokens"), 1n, Bool.pick(Nat, Str.eq(s, "--ast"), 2n, Bool.pick(Nat,
    Str.eq(s, "--check-only"), 3n, Bool.pick(Nat, Str.eq(s, "--no-check"), 4n, Bool.pick(Nat, Str.eq(s, "--js"), 5n,
    Bool.pick(Nat, Str.eq(s, "-o"), 6n, Bool.pick(Nat, Str.eq(s, "--native"), 7n, 0n)))))))

# bendc -o: what bendc writes goes to a C file (Cc.begin), which Cc.end
# compiles into the binary out against the runtime compiled once (rt/cc.c).
def Cc.begin() -> IO(Result<&1, &1, U32 & String, Unit>):
  import "./rt/cc.c"
  import "./rt/cc.js"

def Cc.end(out: String) -> IO(Result<&1, &1, U32 & String, Unit>):
  import "./rt/cc.c"
  import "./rt/cc.js"

# bendc --native: whether objects are ELF (1, on Linux) or Mach-O (0).
def Cc.elf() -> IO(Result<&1, &1, U32 & String, U32>):
  import "./rt/cc.c"
  import "./rt/cc.js"

# bendc --native: links out.o (the program's code) with the effects' C that
# bendc wrote (Cc.begin) and the runtime (rt/cc.c).
def Cc.link(out: String) -> IO(Result<&1, &1, U32 & String, Unit>):
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

def KX.sig(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32) -> Env():
  match ps mask:
    case Core.Param{x, m, t} <> pt True{} <> mt:
      Bind{x, "a" ++ U32.show(i)} <> KX.sig(pt, mt, U32.inc(i))
    case Core.Param{x, m, t} <> pt False{} <> mt:
      Bind{x, "0"} <> KX.sig(pt, mt, i)
    case pl ml:
      Nil{}

# A U32, F32 or Bool fits a KU (see rt/gpu.h): so do a flat def's parameters
# and result of those types, and its Nat parameters, checked (KNAT32).
def KX.narrow(+t: String) -> Bool:
  Str.has(["U32", "F32", "Bool"], t)

def KX.cty(+t: String) -> String:
  Bool.pick(String, KX.narrow(t), "KU", "KW")

def KX.cparams(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32) -> String:
  match ps mask:
    case Core.Param{x, m, +t} <> pt True{} <> mt:
      ", " ++ Bool.pick(String, Str.eq(t, "Nat"), "KW a" ++ U32.show(i) ++ "_", KX.cty(t) ++ " a" ++ U32.show(i)) ++
        KX.cparams(pt, mt, U32.inc(i))
    case Core.Param{x, m, t} <> pt False{} <> mt:
      KX.cparams(pt, mt, i)
    case pl ml:
      ""

def KX.nats(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32) -> String:
  match ps mask:
    case Core.Param{x, m, +t} <> pt True{} <> mt:
      Bool.pick(String, Str.eq(t, "Nat"), "KU a" ++ U32.show(i) ++ " = KNAT32(a" ++ U32.show(i) ++ "_);\n", "") ++
        KX.nats(pt, mt, U32.inc(i))
    case Core.Param{x, m, t} <> pt False{} <> mt:
      KX.nats(pt, mt, i)
    case pl ml:
      ""

def KX.ret.narrow(d: Decl) -> Bool:
  match d:
    case DDef{n, ps, b, r}:
      KX.narrow(P.head(r))
    case other:
      False{}

def KX.v(+k: U32) -> String:
  "x" ++ U32.show(k)

# A flat def's result goes back in c->ko, no node, when its type has one
# constructor of 2 to 8 fields, or is a pair, whose fields each fit a KU or
# are arrays (see KBOX in rt/gpu.h): KX.ko.tys is the fields' C types then
# (an array's a KW), else none, and KX.ko their number.
def KX.ko.fty(+h: String) -> String:
  Bool.pick(String, KX.narrow(h), "KU", Bool.pick(String, Str.eq(h, "Array"), "KW", ""))

def KX.ko.fields(fs: List<&2, Field>) -> List<&2, String>:
  match fs:
    case Nil{}:
      Nil{}
    case Field{x, t} <> r:
      KX.ko.fty(P.head(t)) <> KX.ko.fields(r)

def KX.ko.types(ts: List<&2, Core.Expr>) -> List<&2, String>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      KX.ko.fty(P.head(t)) <> KX.ko.types(r)

def KX.ko.fit(+tys: List<&2, String>) -> List<&2, String>:
  +n = U32.from_nat(List.length(&2, String, tys))
  Bool.pick(List<&2, String>, Bool.and(Bool.not(Str.has(tys, "")), Bool.and(U32.is_le(2, n), U32.is_le(n, 8))), tys, Nil{})

def KX.ko.ctors(cs: List<&2, Ctor>) -> List<&2, String>:
  match cs:
    case Ctor{x, fs} <> Nil{}:
      KX.ko.fit(KX.ko.fields(fs))
    case other:
      Nil{}

def KX.ko.ty(d: Decl) -> List<&2, String>:
  match d:
    case DType{n, ps, cs}:
      KX.ko.ctors(cs)
    case other:
      Nil{}

def KX.ko.ret(+g: G, r: Core.Expr) -> List<&2, String>:
  match r:
    case Core.ETy{+n, ts}:
      Bool.pick(List<&2, String>, Str.eq(n, "&"), KX.ko.fit(KX.ko.types(ts)), KX.ko.ty(G.body(g, "%" ++ n)))
    case other:
      KX.ko.ty(G.body(g, "%" ++ P.head(other)))

def KX.ko.def(+g: G, d: Decl) -> List<&2, String>:
  match d:
    case DDef{n, ps, b, r}:
      KX.ko.ret(g, r)
    case other:
      Nil{}

def KX.ko.tys(+g: G, +name: String) -> List<&2, String>:
  Bool.pick(List<&2, String>, U32.is_zero(DInfo.kind(G.def(g, name))), KX.ko.def(g, G.body(g, name)), Nil{})

def KX.ko(+g: G, +name: String) -> U32:
  U32.from_nat(List.length(&2, String, KX.ko.tys(g, name)))

# A call of a def with n fields in c->ko, for a caller that keeps the value.
def KX.box(+n: U32) -> String:
  Bool.pick(String, U32.is_zero(n), "(", "KBOX(" ++ U32.show(n) ++ ", ")

# c->ko set from the temps xk_i, or from the node ko_.
def KX.ko.set(+k: U32, +n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "c->ko[" ++ U32.show(i) ++ "] = " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ "; " ++ KX.ko.set(k, m, U32.inc(i))

def KX.ko.get(+n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "c->ko[" ++ U32.show(i) ++ "] = KFLD(ko_, " ++ U32.show(i) ++ "); " ++ KX.ko.get(m, U32.inc(i))

# The fields of a call's result, read from c->ko into locals xk_i.
def KX.ko.locals(+k: U32, tys: List<&2, String>, +i: U32) -> String:
  match tys:
    case Nil{}:
      ""
    case t <> r:
      t ++ " " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ " = c->ko[" ++ U32.show(i) ++ "]; " ++ KX.ko.locals(k, r, U32.inc(i))

def KX.ko.names(+k: U32, +n: Nat, +i: U32) -> List<&2, String>:
  match n:
    case 0n:
      Nil{}
    case 1n+m:
      (KX.v(k) ++ "_" ++ U32.show(i)) <> KX.ko.names(k, m, U32.inc(i))

# The number of fields a return to tgt leaves in c->ko (0: none).
def KX.ret.ko(+g: G, self: KSelf, t: KTgt) -> U32:
  match t:
    case KRet{}:
      KX.ko(g, KSelf.name(self))
    case KSet{k, m}:
      0

# The arguments a call of f passes (see Gen.split).
def KX.kept.split(s: Split) -> List<&2, Core.Expr>:
  Split{kept, all, extra, full} = s
  kept

def KX.kept.info(i: DInfo, args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  DInfo{kind, mask} = i
  KX.kept.split(Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}}))

def KX.kept(+g: G, +f: String, args: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  KX.kept.info(G.def(g, f), args)

# Whether a let binds the fields of a call's result left in c->ko.
# A let's value: 1 for a call whose result fields are in c->ko, 2 for an
# Array.get and 3 for an Array.swap opened as a pair (no pair is built:
# see KXSLetArr), else 0.
def KX.arr.op(+f: String, +n: Nat) -> Nat:
  Bool.pick(Nat, Bool.and(Str.has(["Array.get", "Array.get%w"], f), Nat.is_eq(n, 3n)), 2n,
    Bool.pick(Nat, Bool.and(Str.has(["Array.swap", "Array.swap%w"], f), Nat.is_eq(n, 4n)), 3n, 0n))

def KX.let.ko.pick(+arr: Nat, ko: Bool) -> Nat:
  match arr:
    case 0n:
      Bool.pick(Nat, ko, 1n, 0n)
    case 1n+q:
      1n+q

def KX.let.ko(+g: G, p: Core.Pat, v: Core.Expr) -> Nat:
  match p v:
    case Core.PCtor{n, ps} Core.ECall{Core.EVar{+f}, +args}:
      KX.let.ko.pick(Bool.pick(Nat, Nat.is_eq(List.length(&2, Core.Pat, ps), 2n), KX.arr.op(f, List.length(&2, Core.Expr, args)),
        0n), Bool.not(U32.is_zero(KX.ko(g, f))))
    case q w:
      0n

# An Array.get (sw False) or Array.swap (sw True) of the words ds (the type,
# the array, the index and the value), into locals xk_0 (the array) and xk_1
# (the cell read).
def KX.arr.call(sw: Bool, +k: U32, ds: List<&2, Doc>) -> Doc:
  match ds:
    case t <> a <> r:
      Doc.list([DStr{"KW " ++ KX.v(k) ++ "_0 = "}, a, DStr{"; KW " ++ KX.v(k) ++ "_1 = " ++ Bool.pick(String, sw, "k_aswap", "k_aget") ++
        "(c, " ++ KX.v(k) ++ "_0"}, Doc.list(K.commas_pre(r)), DStr{");\n"}])
    case other:
      DStr{"k_fail(c, KE_FX);\n"}

# A flat def's function: a def that loops is not inlined (the kernel's code
# grows past the GPU's instruction cache, raytrace 1.5x slower).
def KX.head(lp: Bool, +name: String, +ps: List<&2, Core.Param>, +mask: List<&2, Bool>, r: Core.Expr) -> String:
  Bool.pick(String, lp, "KNOINLINE ", "KINLINE ") ++ KX.cty(P.head(r)) ++ " KX_" ++ Gen.mangle(name) ++ "(KTHR KCtx *c" ++
    KX.cparams(ps, mask, 0) ++ ") {\n" ++ KX.nats(ps, mask, 0)

# A call of flat def name from a flat def: one that loops, with a scalar
# result, gives back the words it allocated (see KSCAL in rt/gpu.h); the
# check costs more than it saves around a call that does not loop.
def KX.call(sc: Bool, +name: String, ks: List<&2, Doc>) -> Doc:
  Doc.list([DStr{Bool.pick(String, sc, "KSCAL(", "(") ++ "KX_" ++ Gen.mangle(name) ++ "(c"}, Doc.list(K.commas_pre(ks)),
    DStr{"))"}])

def KX.call.box(sc: Bool, +n: U32, +name: String, ks: List<&2, Doc>) -> Doc:
  Doc.list([DStr{KX.box(n)}, KX.call(sc, name, ks), DStr{")"}])

# The names an expression calls. A node's lists are walked one element at
# a time, the rest on the same node (smaller); top: the node's own head
# (a call's function) is still to walk.
def K.heads.go(e: Core.Expr, +acc: List<&2, String>, top: Bool) -> List<&2, String>:
  match e:
    case Core.ECall{Core.EVar{+f}, args}:
      match args:
        case Nil{}:
          Bool.pick(List<&2, String>, top, f <> acc, acc)
        case a <> t:
          K.heads.go(Core.ECall{Core.EVar{f}, t}, K.heads.go(a, Bool.pick(List<&2, String>, top, f <> acc, acc), True{}), False{})
    case Core.ECall{+f, args}:
      match args:
        case Nil{}:
          Bool.pick(Unit -> List<&2, String>, top, u => K.heads.go(f, acc, True{}), u => acc)(Unit{})
        case a <> t:
          K.heads.go(Core.ECall{f, t}, K.heads.go(a, Bool.pick(Unit -> List<&2, String>, top,
            u => K.heads.go(f, acc, True{}), u => acc)(Unit{}), True{}), False{})
    case Core.ECtor{n, args}:
      match args:
        case Nil{}:
          acc
        case a <> t:
          K.heads.go(Core.ECtor{n, t}, K.heads.go(a, acc, True{}), True{})
    case Core.ELam{p, b}:
      K.heads.go(b, acc, True{})
    case Core.ELet{p, v, b}:
      K.heads.go(b, K.heads.go(v, acc, True{}), True{})
    case Core.EMatch{scrs, cases}:
      match scrs:
        case a <> t:
          K.heads.go(Core.EMatch{t, cases}, K.heads.go(a, acc, True{}), True{})
        case Nil{}:
          match cases:
            case c <> t:
              K.heads.go(Core.EMatch{Nil{}, t}, K.heads.go(c, acc, True{}), True{})
            case Nil{}:
              acc
    case Core.ECase{ps, b}:
      K.heads.go(b, acc, True{})
    case Core.ESucc{k, x}:
      K.heads.go(x, acc, True{})
    case Core.EOp{op, a, b}:
      K.heads.go(b, K.heads.go(a, acc, True{}), True{})
    case Core.EAnn{x, t}:
      K.heads.go(x, acc, True{})
    case other:
      acc

def K.heads(e: Core.Expr, acc: List<&2, String>) -> List<&2, String>:
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

def K.kx.id.memo(+name: String, +n: Nat, +ko: U32, m: Maybe<&2, String>) -> KM(U32):
  match m:
    case Some{v}:
      KM.pure(U32, Maybe.default(&2, U32, U32.read(v), 0))
    case None{}:
      do KM<U32>:
        +id : U32 <- K.fresh()
        K.memo.put("%kxid " ++ name, U32.show(id))
        K.memo.put("%kqcase", "case " ++ U32.show(id) ++ ":\nreturn " ++ KX.box(ko) ++ "KX_" ++ Gen.mangle(name) ++ "(c" ++
          KQ.case.args(n, 0) ++ "));\n")
        return id

# The k_kq case of a looping flat def (one per def).
def K.kx.id(+name: String, +n: Nat, +ko: U32) -> KM(U32):
  do KM<U32>:
    m : Maybe<&2, String> <- K.memo.get("%kxid " ++ name)
    K.kx.id.memo(name, n, ko, m)

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
        +id : U32 <- K.kx.id(name, U32.to_nat(Gen.len(ks)), KX.ko(g, name))
        +ret : U32 <- K.fresh()
        +k : U32 <- K.slot()
        K.put(Doc.list([DStr{"c->kq = " ++ U32.show(id) ++ "; c->kqret = " ++ U32.show(ret) ++ "; c->kqfb = 0;\n"},
          KQ.req(ks, 0), DStr{"KPC = PC_KQ;\n"}]))
        K.start(ret)
        K.putS(S(k) ++ " = KRV;\n")
        return DStr{S(k)}
    case False{}:
      KM.pure(Doc, Doc.list([DStr{"KREG("}, KX.call.box(False{}, KX.ko(g, name), name, ks), DStr{")"}]))

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
  KPFields{g: G, args: List<&2, Core.Pat>, path: String, i: U32, r: PatR}
  KPKind{g: G, kind: Nat, tag: U32, single: Bool, args: List<&2, Core.Pat>, path: String, r: PatR}
  KPCtor{g: G, info: Maybe<&2, CInfo>, name: String, args: List<&2, Core.Pat>, path: String, r: PatR}
  KPPat{g: G, p: Core.Pat, path: String, r: PatR}

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
            case Core.PVar{x}:
              Gen.pat.var(x, path, r)
            case Core.PCtor{+name, args}:
              K.pat.go(fu, KPCtor{g, G.ctor(g, name), name, args, path, r})
            case Core.PNat{n}:
              Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
            case Core.PSucc{+k, q}:
              K.pat.go(fu, KPPat{g, q, "((" ++ path ++ ") - " ++ U32.show(k) ++ ")", Gen.pat.cond("k_nge(c, " ++ path ++ ", " ++ U32.show(k) ++ ")", r)})
            case Core.PNum{n}:
              Gen.pat.cond("(" ++ path ++ ") == " ++ U32.show(n), r)
            case Core.PFlt{s}:
              Gen.pat.cond("(" ++ path ++ ") == KUF(" ++ s ++ "f)", r)

def K.pat(g: G, p: Core.Pat, path: String, r: PatR) -> PatR:
  K.pat.go(Fuel.max(), KPPat{g, p, path, r})
def K.pats(+g: G, ps: List<&2, Core.Pat>, paths: List<&2, String>, r: PatR) -> PatR:
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

def KSelf.is_tail(+env: Env(), +self: KSelf, +tgt: KTgt, +name: String, +args: List<&2, Core.Expr>) -> Bool:
  KSelf{+sn, e, +mask} = self
  Bool.and(Bool.and(K.is_ret(tgt), Str.eq(sn, name)), Bool.and(Bool.not(Env.has(env, name)),
    Nat.is_eq(List.length(&2, Bool, mask), List.length(&2, Core.Expr, args))))

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

def K.par.env(+g: G, ps: List<&2, Core.Pat>, rs: List<&2, U32>, +env: Env()) -> Env():
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
  KCase{label: U32, conds: List<&2, String>, env: Env(), body: Core.Expr}

def K.cases(+g: G, +env: Env(), +cs: List<&2, String>, cases: List<&2, Core.Expr>) -> KM(List<&2, KCase>):
  match cases:
    case Nil{}:
      KM.pure(List<&2, KCase>, Nil{})
    case Core.ECase{ps, body} <> t:
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

def K.sig.env(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32) -> Env():
  match ps mask:
    case Core.Param{x, m, t} <> pt True{} <> mt:
      Bind{x, S(i)} <> K.sig.env(pt, mt, U32.inc(i))
    case Core.Param{x, m, t} <> pt False{} <> mt:
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

def KQ.sig(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +k: U32, +i: U32) -> Env():
  match ps mask:
    case Core.Param{x, m, t} <> pt True{} <> mt:
      Bind{x, KX.v(k) ++ "_" ++ U32.show(i)} <> KQ.sig(pt, mt, k, U32.inc(i))
    case Core.Param{x, m, t} <> pt False{} <> mt:
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
      Doc.list([DStr{"KAUTO " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ " = "}, d, DStr{"; "}, KX.temps(t, k, U32.inc(i))])

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
  (c <> cs, Doc.list([DStr{"KAUTO " ++ c ++ " = "}, d, DStr{";\n"}, code]))

def KX.tail.set(+k: U32, +n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "KSET(a" ++ U32.show(i) ++ ", " ++ KX.v(k) ++ "_" ++ U32.show(i) ++ "); " ++ KX.tail.set(k, m, U32.inc(i))


# The flat compiler (KX_ functions), one def (fuel: its calls, which reach
# other defs): KXSel picks the step.
type KXSel is Type:
  KXSDefGo{g: G, name: String, mask: List<&2, Bool>, d: Decl}
  KXSDef{g: G, name: String, info: DInfo}
  KXSKFlatNeedMemo{g: G, name: String, m: Maybe<&2, String>}
  KXSKFlatNeed{g: G, name: String}
  KXSKCallFlat{g: G, name: String, ks: List<&2, Doc>, flat: Bool}
  KXSExprs{g: G, env: Env(), xs: List<&2, Core.Expr>}
  KXSCtor{g: G, env: Env(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Core.Expr>}
  KXSCallKind{g: G, name: String, kind: Nat, ks: List<&2, Doc>}
  KXSCallSplit{g: G, env: Env(), name: String, kind: Nat, s: Split}
  KXSCallDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Core.Expr>}
  KXSVarGlobal{g: G, name: String, info: DInfo}
  KXSVarFound{g: G, name: String, m: Maybe<&2, String>}
  KXSBlock{g: G, env: Env(), e: Core.Expr}
  KXSExpr{g: G, env: Env(), e: Core.Expr}
  KXSScrs{g: G, env: Env(), xs: List<&2, Core.Expr>}
  KXSCases{g: G, env: Env(), self: KSelf, tgt: KTgt, cs: List<&2, String>, cases: List<&2, Core.Expr>}
  KXSMatchGo{g: G, env: Env(), self: KSelf, tgt: KTgt, r: List<&2, String> & Doc, cases: List<&2, Core.Expr>}
  KXSMatch{g: G, env: Env(), self: KSelf, tgt: KTgt, scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>}
  KXSLet{g: G, env: Env(), self: KSelf, tgt: KTgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  KXSLetGo{ko: Nat, g: G, env: Env(), self: KSelf, tgt: KTgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  KXSLetKo{g: G, env: Env(), self: KSelf, tgt: KTgt, ps: List<&2, Core.Pat>, f: String, args: List<&2, Core.Expr>,
      body: Core.Expr}
  KXSLetArr{sw: Bool, g: G, env: Env(), self: KSelf, tgt: KTgt, ps: List<&2, Core.Pat>, args: List<&2, Core.Expr>,
      body: Core.Expr}
  KXSRetArr{sw: Bool, g: G, env: Env(), n: U32, args: List<&2, Core.Expr>}
  KXSRetArrGo{op: Nat, g: G, env: Env(), n: U32, f: String, args: List<&2, Core.Expr>}
  KXSRetCall{same: Bool, g: G, env: Env(), n: U32, f: String, args: List<&2, Core.Expr>}
  KXSRetKo{g: G, env: Env(), n: U32, e: Core.Expr}
  KXSRet{g: G, env: Env(), n: U32, e: Core.Expr}
  KXSRetPlain{g: G, env: Env(), e: Core.Expr}
  KXSRetTo{g: G, env: Env(), self: KSelf, tgt: KTgt, e: Core.Expr}
  KXSLetPlain{g: G, env: Env(), self: KSelf, tgt: KTgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  KXSTail{g: G, env: Env(), s: Split}
  KXSStmtCall{g: G, env: Env(), self: KSelf, tgt: KTgt, name: String, args: List<&2, Core.Expr>, tail: Bool}
  KXSStmt{g: G, env: Env(), self: KSelf, tgt: KTgt, e: Core.Expr}

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
    case KXSLetGo{ko, g, env, self, tgt, p, v, body}:
      KM(Doc)
    case KXSLetKo{g, env, self, tgt, ps, f, args, body}:
      KM(Doc)
    case KXSLetArr{sw, g, env, self, tgt, ps, args, body}:
      KM(Doc)
    case KXSRetArr{sw, g, env, n, args}:
      KM(Doc)
    case KXSRetArrGo{op, g, env, n, f, args}:
      KM(Doc)
    case KXSRetCall{same, g, env, n, f, args}:
      KM(Doc)
    case KXSRetKo{g, env, n, e}:
      KM(Doc)
    case KXSRet{g, env, n, e}:
      KM(Doc)
    case KXSRetPlain{g, env, e}:
      KM(Doc)
    case KXSRetTo{g, env, self, tgt, e}:
      KM(Doc)
    case KXSLetPlain{g, env, self, tgt, p, v, body}:
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
        case KXSLetGo{ko, g, env, self, tgt, p, v, body}:
          K.out(Doc, DNil{})
        case KXSLetKo{g, env, self, tgt, ps, f, args, body}:
          K.out(Doc, DNil{})
        case KXSLetArr{sw, g, env, self, tgt, ps, args, body}:
          K.out(Doc, DNil{})
        case KXSRetArr{sw, g, env, n, args}:
          K.out(Doc, DNil{})
        case KXSRetArrGo{op, g, env, n, f, args}:
          K.out(Doc, DNil{})
        case KXSRetCall{same, g, env, n, f, args}:
          K.out(Doc, DNil{})
        case KXSRetKo{g, env, n, e}:
          K.out(Doc, DNil{})
        case KXSRet{g, env, n, e}:
          K.out(Doc, DNil{})
        case KXSRetPlain{g, env, e}:
          K.out(Doc, DNil{})
        case KXSRetTo{g, env, self, tgt, e}:
          K.out(Doc, DNil{})
        case KXSLetPlain{g, env, self, tgt, p, v, body}:
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
            case DDef{n, +ps, body, ret}:
              do KM<Unit>:
                lp : Bool <- K.loops(g, name)
                b : Doc <- KX.go(fu, KXSStmt{g, KX.sig(ps, mask, 0), KSelf{name, 0, mask}, KRet{}, R.ops(body, "Nat")})
                K.flat.add(Doc.list([DStr{KX.head(lp, name, ps, mask, ret) ++ "for (;;) {\n"}, b, DStr{"}\n}\n"}]))
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
                lp : Bool <- K.loops(g, name)
                return KX.call.box(Bool.and(lp, KX.ret.narrow(G.body(g, name))), KX.ko(g, name), name, ks)
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
            case Core.EVar{+name}:
              KX.go(fu, KXSVarFound{g, name, Env.find(env, name)})
            case Core.ENum{n}:
              KM.pure(Doc, DStr{U32.show(n) ++ "u"})
            case Core.ENat{n}:
              KM.pure(Doc, DStr{U32.show(n) ++ "u"})
            case Core.EFlt{s}:
              KM.pure(Doc, DStr{"KUF(" ++ s ++ "f)"})
            case Core.EStr{s}:
              KM.pure(Doc, Doc.list([DStr{"({ KW r = KIMM(0);\n"}, K.str.cells(Str.codes32(s)), DStr{"r; })"}]))
            case Core.ECall{Core.EVar{+f}, args}:
              KX.go(fu, KXSCallDef{g, env, f, G.def(g, f), args})
            case Core.ECtor{+name, args}:
              KX.go(fu, KXSCtor{g, env, name, G.ctor(g, name), args})
            case Core.ELet{p, v, body}:
              KX.go(fu, KXSBlock{g, env, Core.ELet{p, v, body}})
            case Core.EMatch{scrs, cases}:
              KX.go(fu, KXSBlock{g, env, Core.EMatch{scrs, cases}})
            case Core.ESucc{k, x}:
              do KM<Doc>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, x})
                return Doc.list([DStr{"k_nat_add(c, "}, d, DStr{", " ++ U32.show(k) ++ ")"}])
            case Core.ETy{n, targs}:
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
            case Core.ECase{ps, body} <> t:
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
        case KXSLet{+g, +env, +self, +tgt, +p, +v, body}:
          KX.go(fu, KXSLetGo{KX.let.ko(g, p, v), g, env, self, tgt, p, v, body})
        # A let of a call's result fields left in c->ko: the fields go to
        # locals, the pattern's fields bind them.
        case KXSLetGo{ko, +g, +env, +self, +tgt, p, v, body}:
          match ko p v:
            case 1n Core.PCtor{n, ps} Core.ECall{Core.EVar{f}, args}:
              KX.go(fu, KXSLetKo{g, env, self, tgt, ps, f, args, body})
            case 2n Core.PCtor{n, ps} Core.ECall{f, args}:
              KX.go(fu, KXSLetArr{False{}, g, env, self, tgt, ps, args, body})
            case 3n Core.PCtor{n, ps} Core.ECall{f, args}:
              KX.go(fu, KXSLetArr{True{}, g, env, self, tgt, ps, args, body})
            case k2 p2 v2:
              KX.go(fu, KXSLetPlain{g, env, self, tgt, p2, v2, body})
        # (a, x) = Array.get(T, arr, i) or Array.swap(T, arr, i, v): the
        # array and the cell, with no pair in between.
        case KXSLetArr{sw, +g, +env, +self, +tgt, ps, args, body}:
          do KM<Doc>:
            +k : U32 <- K.fresh()
            ds : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, args})
            b : Doc <- KX.go(fu, KXSStmt{g, List.append(&2, Bind, PatR.binds(K.pats(g, ps, KX.ko.names(k, 2n, 0), PatR{Nil{},
              Nil{}})), env), self, tgt, body})
            return Doc.list([KX.arr.call(sw, k, ds), b])
        # A return of an Array.get or Array.swap's pair, by a def whose
        # result goes in c->ko.
        case KXSRetArr{sw, +g, +env, +n, args}:
          do KM<Doc>:
            +k : U32 <- K.fresh()
            ds : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, args})
            return Doc.list([DStr{"{ "}, KX.arr.call(sw, k, ds), DStr{KX.ko.set(k, 2n, 0) ++ "return 0; }\n"}])
        case KXSLetKo{+g, +env, +self, +tgt, ps, +f, args, body}:
          +n = U32.to_nat(KX.ko(g, f))
          do KM<Doc>:
            +k : U32 <- K.fresh()
            ks : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, KX.kept(g, f, args)})
            KX.go(fu, KXSKFlatNeed{g, f})
            b : Doc <- KX.go(fu, KXSStmt{g, List.append(&2, Bind, PatR.binds(K.pats(g, ps, KX.ko.names(k, n, 0), PatR{Nil{},
              Nil{}})), env), self, tgt, body})
            return Doc.list([KX.call(False{}, f, ks), DStr{";\n" ++ KX.ko.locals(k, KX.ko.tys(g, f), 0) ++ "\n"}, b])
        # A return from a def whose result goes in c->ko (n fields): a
        # constructor's fields go there, a call of such a def leaves them.
        case KXSRet{+g, +env, +n, +e}:
          KM.if(Doc, U32.is_zero(n), KX.go(fu, KXSRetPlain{g, env, e}), KX.go(fu, KXSRetKo{g, env, n, e}))
        case KXSRetKo{+g, +env, +n, e}:
          match e:
            case Core.ECtor{name, args}:
              do KM<Doc>:
                +k : U32 <- K.fresh()
                ds : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, args})
                return Doc.list([DStr{"{ "}, KX.temps(ds, k, 0), DStr{KX.ko.set(k, U32.to_nat(n), 0) ++ "return 0; }\n"}])
            case Core.ECall{Core.EVar{+f}, +args}:
              KX.go(fu, KXSRetArrGo{KX.arr.op(f, List.length(&2, Core.Expr, args)), g, env, n, f, args})
            case other:
              do KM<Doc>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, other})
                return Doc.list([DStr{"{ KW ko_ = "}, d, DStr{"; " ++ KX.ko.get(U32.to_nat(n), 0) ++ "return 0; }\n"}])
        case KXSRetArrGo{op, +g, +env, +n, +f, args}:
          match op:
            case 2n:
              KX.go(fu, KXSRetArr{False{}, g, env, n, args})
            case 3n:
              KX.go(fu, KXSRetArr{True{}, g, env, n, args})
            case other:
              KX.go(fu, KXSRetCall{U32.is_eq(KX.ko(g, f), n), g, env, n, f, args})
        case KXSRetCall{same, +g, +env, +n, +f, +args}:
          match same:
            case True{}:
              do KM<Doc>:
                ks : List<&2, Doc> <- KX.go(fu, KXSExprs{g, env, KX.kept(g, f, args)})
                KX.go(fu, KXSKFlatNeed{g, f})
                return Doc.list([DStr{"return "}, KX.call(False{}, f, ks), DStr{";\n"}])
            case False{}:
              do KM<Doc>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, Core.ECall{Core.EVar{f}, args}})
                return Doc.list([DStr{"{ KW ko_ = "}, d, DStr{"; " ++ KX.ko.get(U32.to_nat(n), 0) ++ "return 0; }\n"}])
        case KXSRetPlain{+g, +env, e}:
          do KM<Doc>:
            d : Doc <- KX.go(fu, KXSExpr{g, env, e})
            return KX.ret(KRet{}, d)
        case KXSLetPlain{+g, +env, +self, +tgt, p, v, body}:
          do KM<Doc>:
            +k : U32 <- K.fresh()
            d : Doc <- KX.go(fu, KXSExpr{g, env, v})
            b : Doc <- KX.go(fu, KXSStmt{g, List.append(&2, Bind, PatR.binds(K.pat(g, p, KX.v(k), PatR{Nil{}, Nil{}})), env), self, tgt,
              body})
            return Doc.list([DStr{"KAUTO " ++ KX.v(k) ++ " = "}, d, DStr{";\n"}, b])
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
              KX.go(fu, KXSRetTo{g, env, self, tgt, Core.ECall{Core.EVar{name}, args}})
        case KXSStmt{+g, +env, +self, +tgt, e}:
          match e:
            case Core.ELet{p, v, body}:
              KX.go(fu, KXSLet{g, env, self, tgt, p, v, body})
            case Core.EMatch{scrs, cases}:
              KX.go(fu, KXSMatch{g, env, self, tgt, scrs, cases})
            case Core.ECall{Core.EVar{+name}, +args}:
              KX.go(fu, KXSStmtCall{g, env, self, tgt, name, args, KSelf.is_tail(env, self, tgt, name, args)})
            case other:
              KX.go(fu, KXSRetTo{g, env, self, tgt, other})
        case KXSRetTo{+g, +env, +self, +tgt, e}:
          match tgt:
            case KRet{}:
              KX.go(fu, KXSRet{g, env, KX.ret.ko(g, self, KRet{}), e})
            case KSet{k, m}:
              do KM<Doc>:
                d : Doc <- KX.go(fu, KXSExpr{g, env, e})
                return KX.ret(KSet{k, m}, d)

# Emits a flat def's function (once; its callees come first).
def K.flat.need(g: G, name: String) -> KM(Unit):
  KX.go(Fuel.max(), KXSKFlatNeed{g, name})

def K.call.flat(g: G, name: String, ks: List<&2, Doc>, flat: Bool) -> KM(Doc):
  KX.go(Fuel.max(), KXSKCallFlat{g, name, ks, flat})

def KX.exprs(g: G, env: Env(), xs: List<&2, Core.Expr>) -> KM(List<&2, Doc>):
  KX.go(Fuel.max(), KXSExprs{g, env, xs})

def KX.expr(g: G, env: Env(), e: Core.Expr) -> KM(Doc):
  KX.go(Fuel.max(), KXSExpr{g, env, e})

# Scrutinees and let values go to fresh locals.
def KX.scrs(g: G, env: Env(), xs: List<&2, Core.Expr>) -> KM(List<&2, String> & Doc):
  KX.go(Fuel.max(), KXSScrs{g, env, xs})

# A call of a seq def from the kernel's blocks: a KQ_ request (PC_KQ), as a
# parallel let's value past the fork limit is (see KSParSeqKq); the value
# comes back at ret, or the call goes through frames at fb. (symreg's climb,
# 32 rounds on one lane, took 1.6s through frames.)
def K.call.seq.kq(+g: G, +name: String, +ks: List<&2, Doc>) -> KM(Doc):
  do KM<Doc>:
    +e : U32 <- K.fn(name)
    +ret : U32 <- K.fresh()
    +after : U32 <- K.fresh()
    +fb : U32 <- K.fresh()
    +k : U32 <- K.slot()
    K.put(Doc.list([DStr{"c->kq = " ++ U32.show(e) ++ "; c->kqret = " ++ U32.show(ret) ++ "; c->kqfb = " ++ U32.show(fb) ++
      " | K_KQLIM;\n"},
      KQ.req(ks, 0), DStr{"KPC = PC_KQ;\n"}]))
    K.start(fb)
    K.put(Doc.list([DStr{"{ KW nf = KPUSH(" ++ U32.show(ret) ++ ", " ++ U32.show(e) ++ ");\n"},
      K.args.put(KQ.req.args(U32.to_nat(Gen.len(ks)), 0), 0), DStr{"KFP = nf; KPC = " ++ U32.show(e) ++ "; }\n"}]))
    K.start(ret)
    K.putS(S(k) ++ " = KRV;\nKPC = " ++ U32.show(after) ++ ";\n")
    K.start(after)
    return DStr{S(k)}

def K.call.seq.pick(sq: Bool, +g: G, +name: String, +ks: List<&2, Doc>) -> KM(Doc):
  match sq:
    case True{}:
      K.call.seq.kq(g, name, ks)
    case False{}:
      K.call.flat(g, name, ks, False{})

# A flat def called from the kernel's blocks.
def K.call.flat.k(+g: G, +name: String, +ks: List<&2, Doc>, flat: Bool) -> KM(Doc):
  match flat:
    case True{}:
      do KM<Doc>:
        K.flat.need(g, name)
        lp : Bool <- K.loops(g, name)
        K.call.flat.k.pick(Bool.and(lp, U32.is_le(Gen.len(ks), 8)), g, name, ks)
    case False{}:
      do KM<Doc>:
        sq : Bool <- K.isseq1(g, name)
        K.call.seq.pick(Bool.and(sq, U32.is_le(Gen.len(ks), 12)), g, name, ks)

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
  KSExprs{g: G, env: Env(), xs: List<&2, Core.Expr>}
  KSCallFull{g: G, env: Env(), name: String, mask: List<&2, Bool>, kind: Nat, kept: List<&2, Core.Expr>,
      all: List<&2, Core.Expr>, extra: List<&2, Core.Expr>, full: Bool}
  KSCallDefKind{kind: Nat, g: G, env: Env(), name: String, mask: List<&2, Bool>, kept: List<&2, Core.Expr>,
      all: List<&2, Core.Expr>, extra: List<&2, Core.Expr>, full: Bool}
  KSCallDefGo{g: G, env: Env(), name: String, mask: List<&2, Bool>, kind: Nat, s: Split}
  KSCallDef{g: G, env: Env(), name: String, info: DInfo, args: List<&2, Core.Expr>}
  KSCallLocal{g: G, env: Env(), f: Core.Expr, args: List<&2, Core.Expr>}
  KSCallVar{g: G, env: Env(), name: String, args: List<&2, Core.Expr>, local: Bool}
  KSCallBang{g: G, env: Env(), args: List<&2, Core.Expr>}
  KSCall{g: G, env: Env(), f: Core.Expr, args: List<&2, Core.Expr>}
  KSCtor{g: G, env: Env(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Core.Expr>}
  KSBlock{g: G, env: Env(), e: Core.Expr}
  KSExpr{g: G, env: Env(), e: Core.Expr}
  KSLam{g: G, env: Env(), p: Core.Pat, body: Core.Expr}
  KSTail{g: G, env: Env(), entry: U32, s: Split}
  KSTailSelf{g: G, env: Env(), self: KSelf, args: List<&2, Core.Expr>}
  KSStmtCall{g: G, env: Env(), self: KSelf, tgt: KTgt, name: String, args: List<&2, Core.Expr>, tail: Bool}
  KSLetVar{g: G, env: Env(), self: KSelf, tgt: KTgt, x: String, v: Core.Expr, body: Core.Expr}
  KSLetPat{g: G, env: Env(), self: KSelf, tgt: KTgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  KSParThunks{g: G, env: Env(), vs: List<&2, Core.Expr>}
  KSParSeqPlain{g: G, env: Env(), v: Core.Expr, r: U32}
  KSParSeqKq{g: G, env: Env(), f: String, kept: List<&2, Core.Expr>, r: U32}
  KSParSeqPick{sq: Bool, extra: List<&2, Core.Expr>, full: Bool, g: G, env: Env(), f: String, args: List<&2, Core.Expr>,
      kept: List<&2, Core.Expr>, r: U32}
  KSParSeqSplit{sq: Bool, g: G, env: Env(), f: String, args: List<&2, Core.Expr>, r: U32, s: Split}
  KSParSeqDef{g: G, env: Env(), f: String, args: List<&2, Core.Expr>, r: U32, info: DInfo}
  KSParSeqVal{g: G, env: Env(), v: Core.Expr, r: U32}
  KSParSeq{g: G, env: Env(), vs: List<&2, Core.Expr>, rs: List<&2, U32>}
  KSPar{g: G, env: Env(), self: KSelf, tgt: KTgt, ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>, body: Core.Expr}
  KSLetPar{g: G, env: Env(), self: KSelf, tgt: KTgt, ps: List<&2, Core.Pat>, v: Core.Expr, body: Core.Expr}
  KSLetCtor{g: G, env: Env(), self: KSelf, tgt: KTgt, name: String, ps: List<&2, Core.Pat>, v: Core.Expr, body: Core.Expr, par: Bool}
  KSLet{g: G, env: Env(), self: KSelf, tgt: KTgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  KSBodies{g: G, self: KSelf, tgt: KTgt, cases: List<&2, KCase>}
  KSMatch{g: G, env: Env(), self: KSelf, tgt: KTgt, scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>}
  KSStmt{g: G, env: Env(), self: KSelf, tgt: KTgt, e: Core.Expr}

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
              K.go(fu, KSCallLocal{g, env, Core.EVar{name}, args})
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
            case Core.EVar{"%gpu"}:
              K.go(fu, KSCallBang{g, env, args})
            case Core.EVar{+name}:
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
            case Core.EVar{name}:
              K.var(g, env, name)
            case Core.ENum{n}:
              KM.pure(Doc, DStr{U32.show(n) ++ "u"})
            case Core.ENat{n}:
              KM.pure(Doc, DStr{U32.show(n) ++ "u"})
            case Core.EFlt{s}:
              KM.pure(Doc, DStr{"KUF(" ++ s ++ "f)"})
            case Core.EStr{s}:
              K.str(s)
            case Core.ECall{f, args}:
              K.go(fu, KSCall{g, env, f, args})
            case Core.ECtor{+name, args}:
              K.go(fu, KSCtor{g, env, name, G.ctor(g, name), args})
            case Core.ELam{p, body}:
              K.go(fu, KSLam{g, env, p, body})
            case Core.ELet{p, v, body}:
              K.go(fu, KSBlock{g, env, Core.ELet{p, v, body}})
            case Core.EMatch{scrs, cases}:
              K.go(fu, KSBlock{g, env, Core.EMatch{scrs, cases}})
            case Core.ESucc{k, x}:
              do KM<Doc>:
                d : Doc <- K.go(fu, KSExpr{g, env, x})
                return Doc.list([DStr{"k_nat_add(c, "}, d, DStr{", " ++ U32.show(k) ++ ")"}])
            case Core.ETy{n, targs}:
              KM.pure(Doc, DStr{"0"})
            case Core.EErr{m}:
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
                d : Doc <- K.go(fu, KSCall{g, env, Core.EVar{name}, args})
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
                d : Doc <- K.go(fu, KSLam{g, env, Core.PVar{"_"}, v})
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
              K.go(fu, KSParSeqPlain{g, env, Core.ECall{Core.EVar{f}, args}, r})
        case KSParSeqSplit{sq, +g, +env, +f, args, +r, s}:
          Split{kept, all, extra, full} = s
          K.go(fu, KSParSeqPick{sq, extra, full, g, env, f, args, kept, r})
        case KSParSeqDef{+g, +env, +f, +args, +r, info}:
          DInfo{kind, mask} = info
          do KM<Unit>:
            sq : Bool <- K.isseqg(g, f)
            fl : Bool <- K.isflat(g, f)
            K.go(fu, KSParSeqSplit{Bool.and(sq, Bool.not(fl)), g, env, f, args, r, Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{},
              False{}})})
        # One value of a parallel let past the fork limit: a call of a seq def runs
        # in its KQ_ function, or through frames if that gives up.
        case KSParSeqVal{+g, +env, v, +r}:
          match v:
            case Core.ECall{Core.EVar{+f}, +args}:
              KM.if(Unit, Env.has(env, f), K.go(fu, KSParSeqPlain{g, env, Core.ECall{Core.EVar{f}, args}, r}),
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
          +n = List.length(&2, Core.Expr, vs)
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
            case Core.ECtor{n, vs}:
              K.go(fu, KSPar{g, env, self, tgt, ps, vs, body})
            case other:
              K.go(fu, KSPar{g, env, self, tgt, ps, [other], body})
        case KSLetCtor{+g, +env, +self, +tgt, name, ps, v, body, par}:
          match par:
            case True{}:
              K.go(fu, KSLetPar{g, env, self, tgt, ps, v, body})
            case False{}:
              K.go(fu, KSLetPat{g, env, self, tgt, Core.PCtor{name, ps}, v, body})
        case KSLet{+g, +env, +self, +tgt, p, v, body}:
          match p:
            case Core.PVar{+x}:
              K.go(fu, KSLetVar{g, env, self, tgt, x, v, body})
            case Core.PCtor{+name, ps}:
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
            case Core.ELet{p, v, body}:
              K.go(fu, KSLet{g, env, self, tgt, p, v, body})
            case Core.EMatch{scrs, cases}:
              K.go(fu, KSMatch{g, env, self, tgt, scrs, cases})
            case Core.ECall{Core.EVar{+name}, +args}:
              K.go(fu, KSStmtCall{g, env, self, tgt, name, args, KSelf.is_tail(env, self, tgt, name, args)})
            case other:
              do KM<Unit>:
                d : Doc <- K.go(fu, KSExpr{g, env, other})
                K.ret(tgt, d)

def K.stmt(g: G, env: Env(), self: KSelf, tgt: KTgt, e: Core.Expr) -> KM(Unit):
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

def KQ.tail.go(+g: G, +env: Env(), +e: U32, s: Split) -> KM(Unit):
  Split{kept, all, extra, full} = s
  do KM<Unit>:
    +k : U32 <- K.fresh()
    +ds : List<&2, Doc> <- KX.exprs(g, env, kept)
    # (Errors are checked here: a tail loop could spin on a failed value.
    # Other calls are bounded by the stack.)
    K.put(Doc.list([DStr{"{ "}, KX.temps(ds, k, 0), DStr{KQ.pass(k, U32.to_nat(Gen.len(ds)), 0) ++
      "if (c->err) { *ok = false; return 0; }\npc = " ++ U32.show(e) ++ "; break; }\n"}]))

# A value to return: to the caller's resume label, or out of KQ_name.
def KQ.ret(+g: G, +env: Env(), e: Core.Expr) -> KM(Unit):
  do KM<Unit>:
    d : Doc <- KX.expr(g, env, e)
    K.put(Doc.list([DStr{"RV = "}, d, DStr{";\nif (sp == 0) return RV;\nsp -= 1; pc = KQ_ST(sp); break;\n"}]))

# A parallel let runs in order: a let per value.
def KQ.par.lets(ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>, body: Core.Expr) -> Core.Expr:
  match ps vs:
    case p <> pt v <> vt:
      Core.ELet{p, v, KQ.par.lets(pt, vt, body)}
    case a b:
      body

def KQ.par.vals(v: Core.Expr) -> List<&2, Core.Expr>:
  match v:
    case Core.ECtor{n, vs}:
      vs
    case other:
      [other]

def KQ.call.args(v: Core.Expr) -> List<&2, Core.Expr>:
  match v:
    case Core.ECall{f, args}:
      args
    case other:
      Nil{}


# A KQ_ function's argument registers past its own: A0.. hold the arguments
# of any seq def its code calls (12 at most, see K.isseq).
def KQ.init.rest(+n: Nat, +i: U32) -> String:
  match n:
    case 0n:
      ""
    case 1n+m:
      "KW A" ++ U32.show(i) ++ " = 0;\n" ++ KQ.init.rest(m, U32.inc(i))

def KQ.callee(v: Core.Expr) -> String:
  match v:
    case Core.ECall{Core.EVar{f}, args}:
      f
    case other:
      ""

def KQ.gcall.go(+g: G, +self: KSelf, +f: String) -> KM(Bool):
  do KM<Bool>:
    sq : Bool <- K.isseqg(g, f)
    fl : Bool <- K.isflat(g, f)
    return Bool.or(Str.eq(f, KSelf.name(self)), Bool.and(sq, Bool.not(fl)))

# Whether v calls the def itself or another seq def that is not flat: a
# call through the KQ_ stack.
def KQ.gcall(+g: G, +env: Env(), +self: KSelf, v: Core.Expr) -> KM(Bool):
  match v:
    case Core.ECall{Core.EVar{+f}, args}:
      KM.if(Bool, Env.has(env, f), KM.pure(Bool, False{}), KQ.gcall.go(g, self, f))
    case other:
      KM.pure(Bool, False{})

# Whether a def returns a scalar: a call of it does not give back what it
# allocated (see KQSCallGo; symreg calls eval 110 times a candidate).
def KQ.scalret(d: Decl) -> Bool:
  match d:
    case DDef{n, ps, body, ret}:
      Str.has(["U32", "F32", "Bool", "Nat", "Char"], P.head(ret))
    case other:
      False{}

# Whether a call gives back what it allocated (see KQSCallGo): not with a
# scalar result; with a node, a call of another def, or of the def itself
# when the node is a record of scalars (symreg's batch: the result moves
# down, a subtree's candidates go).
def KQ.reg(me: Bool, sc: Bool, +ko: U32) -> Bool:
  Bool.and(Bool.not(sc), Bool.or(Bool.not(me), Bool.not(U32.is_zero(ko))))

def KQ.split(+g: G, +f: String, args: List<&2, Core.Expr>) -> Split:
  Gen.split(DInfo.mask(G.def(g, f)), args, Split{Nil{}, Nil{}, Nil{}, False{}})

# The sequential compiler (KQ_ functions), one def (fuel: its calls):
# KQSel picks the step.
type KQSel is Type:
  KQSDef{sq: Bool, g: G, name: String, e: U32, mask: List<&2, Bool>, ps: List<&2, Core.Param>, body: Core.Expr}
  KQSCallGo{reg: Bool, g: G, env: Env(), self: KSelf, x: String, s: Split, e: U32, body: Core.Expr}
  KQSCall{g: G, env: Env(), self: KSelf, x: String, f: String, args: List<&2, Core.Expr>, body: Core.Expr}
  KQSEntryMemo{g: G, f: String, key: String, m: Maybe<&2, String>}
  KQSEntry{g: G, f: String}
  KQSGroupGo{g: G, f: String, l: U32, mask: List<&2, Bool>, d: Decl}
  KQSGroup{g: G, f: String, l: U32, info: DInfo, d: Decl}
  KQSTail{gc: Bool, g: G, env: Env(), name: String, args: List<&2, Core.Expr>}
  KQSLetPatQ{g: G, env: Env(), self: KSelf, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  KQSCases{g: G, env: Env(), self: KSelf, cs: List<&2, String>, cases: List<&2, Core.Expr>}
  KQSMatchGo{g: G, env: Env(), self: KSelf, r: List<&2, String> & Doc, cases: List<&2, Core.Expr>}
  KQSMatch{g: G, env: Env(), self: KSelf, scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>}
  KQSLetVar{g: G, env: Env(), self: KSelf, x: String, v: Core.Expr, body: Core.Expr, direct: Bool}
  KQSLetPat{g: G, env: Env(), self: KSelf, p: Core.Pat, v: Core.Expr, body: Core.Expr, direct: Bool}
  KQSLet{g: G, env: Env(), self: KSelf, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  KQSStmt{g: G, env: Env(), self: KSelf, e: Core.Expr}

def KQSel.ty(k: KQSel) -> Type:
  match k:
    case KQSDef{sq, g, name, e, mask, ps, body}:
      KM(Unit)
    case KQSCallGo{reg, g, env, self, x, s, e, body}:
      KM(Unit)
    case KQSCall{g, env, self, x, f, args, body}:
      KM(Unit)
    case KQSEntryMemo{g, f, key, m}:
      KM(U32)
    case KQSEntry{g, f}:
      KM(U32)
    case KQSGroupGo{g, f, l, mask, d}:
      KM(Unit)
    case KQSGroup{g, f, l, info, d}:
      KM(Unit)
    case KQSTail{gc, g, env, name, args}:
      KM(Unit)
    case KQSLetPatQ{g, env, self, p, v, body}:
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
        case KQSCallGo{reg, g, env, self, x, s, e, body}:
          K.out(Unit, Unit{})
        case KQSCall{g, env, self, x, f, args, body}:
          K.out(Unit, Unit{})
        case KQSEntryMemo{g, f, key, m}:
          K.out(U32, 0)
        case KQSEntry{g, f}:
          K.out(U32, 0)
        case KQSGroupGo{g, f, l, mask, d}:
          K.out(Unit, Unit{})
        case KQSGroup{g, f, l, info, d}:
          K.out(Unit, Unit{})
        case KQSTail{gc, g, env, name, args}:
          K.out(Unit, Unit{})
        case KQSLetPatQ{g, env, self, p, v, body}:
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
        case KQSDef{sq, +g, +name, +e, +mask, +ps, body}:
          match sq:
            case True{}:
              +n = U32.to_nat(K.kept(mask))
              +bound = K.params(ps, mask)
              do KM<Unit>:
                K.start(0)
                saved : Doc <- K.cap.begin()
                +l : U32 <- K.fresh()
                +k : U32 <- K.fresh()
                # The entries of the seq defs this code calls (see KQSEntry).
                K.memo.put("%kqroot", name)
                K.memo.put("%kqe " ++ name ++ " " ++ name, U32.show(l))
                K.start(l)
                K.putS(KQ.entry(k, n, 0) ++ "\n")
                KQ.go(fu, KQSStmt{g, KQ.sig(ps, mask, k, 0), KSelf{name, l, mask}, KQ.anf(g, bound, R.ops(body, "Nat"))})
                K.start(0)
                blocks : Doc <- K.cap.take(saved)
                K.flat.add(Doc.list([DStr{"\nKINLINE KW KQ_" ++ Gen.mangle(name) ++ "(KTHR KCtx *c" ++ KQ.params(n, 0) ++
                  ", KTHR bool *ok) {\nKQ_STACK;\nKW sp = 0, pc = " ++ U32.show(l) ++ ", RV = 0, st = c->kqlim;\n" ++ KQ.init(n, 0) ++
                  KQ.init.rest(Nat.sub(12n, n), U32.from_nat(n)) ++
                  "for (;;) {\nif (st-- == 0 || c->err != 0) { *ok = false; return 0; }\nswitch (pc) {\n"}, blocks,
                  DStr{"default:\n*ok = false;\nreturn 0;\n}\n}\n}\n"}]))
                K.memo.put("%kqcase", "case " ++ U32.show(e) ++ ": return KQ_" ++ Gen.mangle(name) ++ "(c" ++ KQ.case.args(n, 0) ++
                  ", ok);\n")
            case False{}:
              KM.pure(Unit, Unit{})
        # A call that gives back what it allocated (KQ.reg) keeps the lane's hp
        # and he under its return pc: at the resume k_region takes the words
        # back (the call is flat, so only its result can reach them). Calls
        # with a scalar result, and self calls that build a tree (gen), do not:
        # the check cost symreg 0.5s.
        case KQSCallGo{+reg, +g, +env, +self, +x, s, +e, +body}:
          Split{kept, all, extra, full} = s
          # Saved: the variables the rest of the code uses.
          +live = KQ.live(KQ.used(env, FV.expr(body, [x], Nil{})), Nil{})
          +m = Gen.len(K.docs.of(live))
          +w = Bool.pick(U32, reg, U32.add(m, 2), m)
          do KM<Unit>:
            +k : U32 <- K.fresh()
            +ds : List<&2, Doc> <- KX.exprs(g, env, kept)
            +r : U32 <- K.fresh()
            K.put(Doc.list([DStr{"{ "}, KX.temps(ds, k, 0), DStr{"if (sp + " ++ U32.show(U32.inc(w)) ++
              " > KR_WORDS) { *ok = false; return 0; }\n" ++ KQ.save(live, 0) ++ Bool.pick(String, reg, "KQ_ST(sp + " ++
              U32.show(m) ++ ") = c->hp; KQ_ST(sp + " ++ U32.show(U32.inc(m)) ++ ") = c->he; ", "") ++ "KQ_ST(sp + " ++
              U32.show(w) ++ ") = " ++ U32.show(r) ++ "; sp += " ++ U32.show(U32.inc(w)) ++ ";\n" ++
              KQ.pass(k, U32.to_nat(Gen.len(ds)), 0) ++ "pc = " ++ U32.show(e) ++ "; break; }\n"}]))
            # The resume block is made aside, so the code around the call (an arm
            # of a match, say) stays whole in this block.
            saved : U32 & Doc <- K.save()
            K.start(r)
            +j : U32 <- K.fresh()
            K.putS("sp -= " ++ U32.show(w) ++ "; " ++ KQ.load(live, j, 0) ++ "KW " ++ KX.v(j) ++ " = " ++ Bool.pick(String, reg,
              "k_region(c, KQ_ST(sp + " ++ U32.show(m) ++ "), KQ_ST(sp + " ++ U32.show(U32.inc(m)) ++ "), RV)", "RV") ++ ";\n")
            KQ.go(fu, KQSStmt{g, Bool.pick(Env(), Str.eq(x, "_"), KQ.reenv(live, j, 0), Bind{x, KX.v(j)} <> KQ.reenv(live, j, 0)), self,
              body})
            K.restore(saved)
        # x = f(args) at statement level, f the def itself or another seq def:
        # save, call, resume.
        case KQSCall{+g, +env, +self, +x, +f, args, body}:
          do KM<Unit>:
            +e : U32 <- KQ.go(fu, KQSEntry{g, f})
            KQ.go(fu, KQSCallGo{KQ.reg(Str.eq(f, KSelf.name(self)), KQ.scalret(G.body(g, f)), KX.ko(g, f)), g, env, self, x,
              KQ.split(g, f, args), e, body})
        # The entry of seq def f in the KQ_ function being made: its blocks are
        # made (aside) the first time.
        case KQSEntryMemo{+g, +f, +key, m}:
          match m:
            case Some{v}:
              KM.pure(U32, Maybe.default(&2, U32, U32.read(v), 0))
            case None{}:
              do KM<U32>:
                +l : U32 <- K.fresh()
                K.memo.put(key, U32.show(l))
                KQ.go(fu, KQSGroup{g, f, l, G.def(g, f), G.body(g, f)})
                return l
        case KQSEntry{+g, +f}:
          do KM<U32>:
            r : Maybe<&2, String> <- K.memo.get("%kqroot")
            +key : String = "%kqe " ++ Maybe.default(&2, String, r, "") ++ " " ++ f
            m : Maybe<&2, String> <- K.memo.get(key)
            KQ.go(fu, KQSEntryMemo{g, f, key, m})
        case KQSGroupGo{+g, +f, +l, +mask, d}:
          match d:
            case DDef{n, +ps, body, ret}:
              do KM<Unit>:
                saved : U32 & Doc <- K.save()
                +k : U32 <- K.fresh()
                K.start(l)
                K.putS(KQ.entry(k, U32.to_nat(K.kept(mask)), 0) ++ "\n")
                KQ.go(fu, KQSStmt{g, KQ.sig(ps, mask, k, 0), KSelf{f, l, mask}, KQ.anf(g, K.params(ps, mask), R.ops(body, "Nat"))})
                K.restore(saved)
            case other:
              KM.pure(Unit, Unit{})
        case KQSGroup{+g, +f, +l, info, d}:
          DInfo{kind, mask} = info
          KQ.go(fu, KQSGroupGo{g, f, l, mask, d})
        # A call in tail position: of a seq def, new arguments and a jump to its
        # entry; else the value to return.
        case KQSTail{gc, +g, +env, +name, args}:
          match gc:
            case True{}:
              do KM<Unit>:
                +e : U32 <- KQ.go(fu, KQSEntry{g, name})
                KQ.tail.go(g, env, e, KQ.split(g, name, args))
            case False{}:
              KQ.ret(g, env, Core.ECall{Core.EVar{name}, args})
        case KQSCases{+g, +env, +self, +cs, cases}:
          match cases:
            case Nil{}:
              K.putS("{ k_fail(c, KE_MATCH); *ok = false; return 0; }\n")
            case Core.ECase{ps, body} <> t:
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
        case KQSLetVar{+g, +env, +self, +x, +v, body, direct}:
          match direct:
            case True{}:
              KQ.go(fu, KQSCall{g, env, self, x, KQ.callee(v), KQ.call.args(v), body})
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
                KQ.go(fu, KQSStmt{g, env, self, Core.ELet{Core.PVar{"%q" ++ U32.show(k)}, v, Core.ELet{p, Core.EVar{"%q" ++ U32.show(k)}, body}}})
            case False{}:
              do KM<Unit>:
                +k : U32 <- K.fresh()
                d : Doc <- KX.expr(g, env, v)
                K.put(Doc.list([DStr{"KW " ++ KX.v(k) ++ " = "}, d, DStr{";\n"}]))
                KQ.go(fu, KQSStmt{g, List.append(&2, Bind, PatR.binds(K.pat(g, p, KX.v(k), PatR{Nil{}, Nil{}})), env), self, body})
        case KQSLet{+g, +env, +self, p, +v, +body}:
          match p:
            case Core.PVar{+x}:
              do KM<Unit>:
                gc : Bool <- KQ.gcall(g, env, self, v)
                KQ.go(fu, KQSLetVar{g, env, self, x, v, body, gc})
            case Core.PCtor{+n, +ps}:
              KM.if(Unit, Str.eq(n, "%par"), KQ.go(fu, KQSStmt{g, env, self, KQ.par.lets(ps, KQ.par.vals(v), body)}),
                KQ.go(fu, KQSLetPatQ{g, env, self, Core.PCtor{n, ps}, v, body}))
            case other:
              KQ.go(fu, KQSLetPatQ{g, env, self, other, v, body})
        case KQSLetPatQ{+g, +env, +self, +p, +v, +body}:
          do KM<Unit>:
            gc : Bool <- KQ.gcall(g, env, self, v)
            KQ.go(fu, KQSLetPat{g, env, self, p, v, body, gc})
        case KQSStmt{+g, +env, +self, e}:
          match e:
            case Core.ELet{p, v, body}:
              KQ.go(fu, KQSLet{g, env, self, p, v, body})
            case Core.EMatch{scrs, cases}:
              KQ.go(fu, KQSMatch{g, env, self, scrs, cases})
            case Core.ECall{Core.EVar{+name}, +args}:
              do KM<Unit>:
                gc : Bool <- KQ.gcall(g, env, self, Core.ECall{Core.EVar{name}, args})
                KQ.go(fu, KQSTail{gc, g, env, name, args})
            case other:
              KQ.ret(g, env, other)

def KQ.def(sq: Bool, g: G, name: String, e: U32, mask: List<&2, Bool>, ps: List<&2, Core.Param>, body: Core.Expr) -> KM(Unit):
  KQ.go(Fuel.max(), KQSDef{sq, g, name, e, mask, ps, body})

def K.def.body(+g: G, +name: String, +l: U32, +mask: List<&2, Bool>, +ps: List<&2, Core.Param>, +body: Core.Expr) -> KM(Unit):
  do KM<Unit>:
    sq : Bool <- K.isseqg(g, name)
    +old : U32 <- K.enter(l)
    +np : U32 <- K.slots(K.kept(mask))
    K.start(l)
    K.stmt(g, K.sig.env(ps, mask, 0), KSelf{name, l, mask}, KRet{}, R.ops(body, "Nat"))
    +size : U32 <- K.leave(old)
    K.frame(l, size)
    KQ.def(sq, g, name, l, mask, ps, body)

# A flat def's entry block calls its function.
def K.def.decl.flat(flat: Bool, +g: G, +name: String, +l: U32, +mask: List<&2, Bool>, ps: List<&2, Core.Param>, body: Core.Expr) ->
  KM(Unit):
  match flat:
    case True{}:
      K.def.flat(g, name, l, mask)
    case False{}:
      K.def.body(g, name, l, mask, ps, body)

def K.def.decl.def(kind: Nat, +g: G, +name: String, +l: U32, +mask: List<&2, Bool>, ps: List<&2, Core.Param>, body: Core.Expr) ->
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
  JPFields{j: JG, args: List<&2, Core.Pat>, paths: List<&2, String>, r: PatR}
  JPBitsCon{j: JG, p: Core.Pat, path: String, r: PatR}
  JPBitsGo{j: JG, k: Nat, p: Core.Pat, path: String, r: PatR}
  JPBits{j: JG, p: Core.Pat, path: String, r: PatR}
  JPBitsOne{j: JG, args: List<&2, Core.Pat>, path: String, r: PatR}
  JPArr{leaf: Bool, j: JG, args: List<&2, Core.Pat>, path: String, r: PatR}
  JPKind{j: JG, kind: Nat, name: String, args: List<&2, Core.Pat>, path: String, fs: List<&2, String>, single: Bool,
      r: PatR}
  JPCtor{j: JG, info: Maybe<&2, JCI>, name: String, args: List<&2, Core.Pat>, path: String, r: PatR}
  JPPat{j: JG, p: Core.Pat, path: String, r: PatR}

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
            case Core.PCtor{n, a <> b <> Nil{}}:
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
            case Core.PVar{x}:
              Gen.pat.var(x, path, r)
            case Core.PCtor{+name, args}:
              J.pat.go(fu, JPCtor{j, J.ctor(j, name), name, args, path, r})
            case Core.PNat{n}:
              Gen.pat.cond("(" ++ path ++ ") === " ++ U32.show(n) ++ "n", r)
            case Core.PSucc{+k, q}:
              J.pat.go(fu, JPPat{j, q, "((" ++ path ++ ") - " ++ U32.show(k) ++ "n)",
                Gen.pat.cond(J.succ.cond(path, k), r)})
            case Core.PNum{n}:
              Gen.pat.cond("(" ++ path ++ ") === " ++ U32.show(n), r)
            case Core.PFlt{s}:
              Gen.pat.cond("(" ++ path ++ ") === " ++ J.flt(s), r)

def J.pat(j: JG, p: Core.Pat, path: String, r: PatR) -> PatR:
  J.pat.go(Fuel.max(), JPPat{j, p, path, r})
def J.pats(+j: JG, ps: List<&2, Core.Pat>, paths: List<&2, String>, r: PatR) -> PatR:
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

def J.nulls(all: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  all

def J.ret(t: Tgt, d: Doc) -> Doc:
  match t:
    case TRet{}:
      Doc.list([DStr{"return "}, d, DStr{";\n"}])
    case TSet{v}:
      Doc.list([DStr{v}, DStr{" = "}, d, DStr{";\n"}])
    case TDst{id, n}:
      Doc.list([DStr{"*dst = "}, d, DStr{";\nreturn 0;\n"}])
    case TOut{k, free}:
      Doc.list([DStr{"return "}, d, DStr{";\n"}])

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
  JSExprs{j: JG, env: Env(), xs: List<&2, Core.Expr>}
  JSBitsCon{j: JG, env: Env(), e: Core.Expr}
  JSBitsGo{j: JG, env: Env(), k: Nat, e: Core.Expr}
  JSBits{j: JG, env: Env(), e: Core.Expr}
  JSBitsArgs{j: JG, env: Env(), w: Nat, args: List<&2, Core.Expr>}
  JSCtorBuild{j: JG, env: Env(), name: String, info: Maybe<&2, JCI>, args: List<&2, Core.Expr>}
  JSCallFull{j: JG, env: Env(), name: String, kept: List<&2, Core.Expr>, all: List<&2, Core.Expr>, extra: List<&2, Core.Expr>,
      full: Bool}
  JSCallSplit{j: JG, env: Env(), name: String, s: Split}
  JSCallKind{j: JG, env: Env(), name: String, kind: Nat, s: Split}
  JSCallDef{j: JG, env: Env(), name: String, info: DInfo, args: List<&2, Core.Expr>}
  JSCallLocal{j: JG, env: Env(), f: Core.Expr, args: List<&2, Core.Expr>}
  JSCallVar{j: JG, env: Env(), name: String, args: List<&2, Core.Expr>, local: Bool}
  JSCallBang{j: JG, env: Env(), args: List<&2, Core.Expr>}
  JSCallName{j: JG, env: Env(), name: String, args: List<&2, Core.Expr>, bang: Bool}
  JSCall{j: JG, env: Env(), f: Core.Expr, args: List<&2, Core.Expr>}
  JSBlock{j: JG, env: Env(), e: Core.Expr}
  JSExpr{j: JG, env: Env(), e: Core.Expr}
  JSLam{j: JG, env: Env(), p: Core.Pat, body: Core.Expr}
  JSTail{j: JG, env: Env(), cps: List<&2, String>, s: Split}
  JSTailSelf{j: JG, env: Env(), self: Self, args: List<&2, Core.Expr>}
  JSStmtCall{j: JG, env: Env(), self: Self, tgt: Tgt, name: String, args: List<&2, Core.Expr>, tail: Bool}
  JSLetVar{j: JG, env: Env(), self: Self, tgt: Tgt, x: String, v: Core.Expr, body: Core.Expr, hole: Bool}
  JSLetPat{j: JG, env: Env(), self: Self, tgt: Tgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  JSLetPar{j: JG, env: Env(), self: Self, tgt: Tgt, ps: List<&2, Core.Pat>, v: Core.Expr, body: Core.Expr}
  JSLetCtor{j: JG, env: Env(), self: Self, tgt: Tgt, name: String, ps: List<&2, Core.Pat>, v: Core.Expr, body: Core.Expr, par: Bool}
  JSLet{j: JG, env: Env(), self: Self, tgt: Tgt, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  JSCasesNext{j: JG, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>, rest: List<&2, Core.Expr>,
      conds: List<&2, String>, b: Doc}
  JSCases{j: JG, env: Env(), self: Self, tgt: Tgt, cs: List<&2, String>, cases: List<&2, Core.Expr>}
  JSScrs{j: JG, env: Env(), xs: List<&2, Core.Expr>}
  JSMatchGo{j: JG, env: Env(), self: Self, tgt: Tgt, cases: List<&2, Core.Expr>, r: List<&2, String> & Doc}
  JSMatch{j: JG, env: Env(), self: Self, tgt: Tgt, scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>}
  JSStmt{j: JG, env: Env(), self: Self, tgt: Tgt, e: Core.Expr}

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
            case Core.ECtor{n, a <> b <> Nil{}}:
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
              J.go(fu, JSCallLocal{j, env, Core.EVar{name}, args})
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
            case Core.EVar{+name}:
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
            case Core.EVar{name}:
              J.var(j, env, name)
            case Core.ENum{n}:
              Gen.pure(Doc, DStr{U32.show(n)})
            case Core.ENat{n}:
              Gen.pure(Doc, DStr{U32.show(n) ++ "n"})
            case Core.EFlt{s}:
              Gen.pure(Doc, DStr{J.flt(s)})
            case Core.EStr{s}:
              Gen.pure(Doc, J.str(s))
            case Core.ECall{f, args}:
              J.go(fu, JSCall{j, env, f, args})
            case Core.ECtor{+name, args}:
              J.go(fu, JSCtorBuild{j, env, name, J.ctor(j, name), args})
            case Core.ELam{p, body}:
              J.go(fu, JSLam{j, env, p, body})
            case Core.ELet{p, v, body}:
              J.go(fu, JSBlock{j, env, Core.ELet{p, v, body}})
            case Core.EMatch{scrs, cases}:
              J.go(fu, JSBlock{j, env, Core.EMatch{scrs, cases}})
            case Core.ESucc{k, x}:
              do Gen<Doc>:
                d : Doc <- J.go(fu, JSExpr{j, env, x})
                return Doc.list([DStr{"nat_chk(("}, d, DStr{") + " ++ U32.show(k) ++ "n)"}])
            case Core.ETy{n, targs}:
              Gen.pure(Doc, DStr{"null"})
            case Core.EErr{m}:
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
                d : Doc <- J.go(fu, JSCall{j, env, Core.EVar{name}, args})
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
            case p <> pt Core.ECtor{n, x <> xt}:
              J.go(fu, JSStmt{j, env, self, tgt, Core.ELet{p, x, Core.ELet{Core.PCtor{"%par", pt}, Core.ECtor{n, xt}, body}}})
            case pl other:
              J.go(fu, JSStmt{j, env, self, tgt, body})
        case JSLetCtor{+j, +env, +self, +tgt, name, ps, v, body, par}:
          match par:
            case True{}:
              J.go(fu, JSLetPar{j, env, self, tgt, ps, v, body})
            case False{}:
              J.go(fu, JSLetPat{j, env, self, tgt, Core.PCtor{name, ps}, v, body})
        case JSLet{+j, +env, +self, +tgt, p, v, body}:
          match p:
            case Core.PVar{+x}:
              J.go(fu, JSLetVar{j, env, self, tgt, x, v, body, Str.eq(x, "_")})
            case Core.PCtor{+name, ps}:
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
            case Core.ECase{ps, body} <> t:
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
            case Core.ELet{p, v, body}:
              J.go(fu, JSLet{j, env, self, tgt, p, v, body})
            case Core.EMatch{scrs, cases}:
              J.go(fu, JSMatch{j, env, self, tgt, scrs, cases})
            case Core.ECall{Core.EVar{+name}, +args}:
              J.go(fu, JSStmtCall{j, env, self, tgt, name, args, Gen.is_tail(env, self, tgt, name, args)})
            case other:
              do Gen<Doc>:
                d : Doc <- J.go(fu, JSExpr{j, env, other})
                return J.ret(tgt, d)

def J.stmt(j: JG, env: Env(), self: Self, tgt: Tgt, e: Core.Expr) -> Gen(Doc):
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
def J.def.body(+j: JG, +name: String, +mask: List<&2, Bool>, body: Core.Expr, sig: Sig) -> Gen(Unit):
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
def J.eff.args(ps: List<&2, Core.Param>, kept: List<&2, String>) -> List<&2, String>:
  match ps kept:
    case Nil{} k:
      Nil{}
    case Core.Param{+n, +m, +ty} <> +t Nil{}:
      Bool.pick(Unit -> List<&2, String>, G.keep(Core.Param{n, m, ty}), u => Nil{},
        u => J.eff.null(Bool.and(G.erased_ty(ty), Bool.not(U32.is_eq(m, 1))), J.eff.args(t, Nil{})))(Unit{})
    case Core.Param{+n, +m, +ty} <> +t +h <> +kt:
      Bool.pick(Unit -> List<&2, String>, G.keep(Core.Param{n, m, ty}), u => J.eff.wrap(ty, h) <> J.eff.args(t, kt),
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
def J.eff.head(a: Core.Expr) -> String:
  match a:
    case Core.ETy{t, xs}:
      t
    case Core.EVar{t}:
      t
    case Core.ECall{Core.EVar{t}, xs}:
      t
    case other:
      ""

def J.eff.tags.ty(+g: G, a: Core.Expr) -> String:
  +t = J.eff.head(a)
  Bool.pick(String, Nat.is_eq(J.kind(t), 8n),
    J.eff.tags.of(t, G.body(g, "%" ++ t)), "k")

def J.eff.tags.io(+g: G, +io: String, xs: List<&2, Core.Expr>) -> String:
  match xs:
    case [a]:
      Bool.pick(String, Str.eq(io, "IO"), J.eff.tags.ty(g, a), "k")
    case other:
      "k"

def J.eff.tags(+g: G, d: Decl) -> String:
  match d:
    case DLaw{n, ps, Core.ETy{io, xs}}:
      J.eff.tags.io(g, io, xs)
    case DLaw{n, ps, Core.ECall{Core.EVar{io}, xs}}:
      J.eff.tags.io(g, io, xs)
    case other:
      "k"

def J.def.eff(+g: G, +name: String, +mask: List<&2, Bool>, ps: List<&2, Core.Param>, sig: Sig, ims: List<&2, String>) -> Gen(Unit):
  Sig{+params, env, wargs} = sig
  +host = J.host(String.to_lower(name))
  do Gen<Unit>:
    J.effs(ims, host)
    Gen.code(DStr{"function " ++ Gen.f(name) ++ "(" ++ J.params(params) ++ ") {\n  return (R) => (k) => io_req(EFF[\"" ++
      host ++ "\"], \"" ++ host ++ "\", [" ++ J.params(J.eff.args(ps, params)) ++ "], " ++
      J.eff.tags(g, G.body(g, "^" ++ name)) ++ ");\n}\n"})
    J.wrapper(name, mask)

def J.def.native(+j: JG, +name: String, +mask: List<&2, Bool>, body: Core.Expr, sig: Sig, native: Bool) -> Gen(Unit):
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
  JRTuple{j: JG, xs: List<&2, Core.Expr>, path: String}
  JRFields{j: JG, sub: List<&2, TB>, fs: List<&2, Field>, path: String, i: U32}
  JRCtor{j: JG, sub: List<&2, TB>, name: String, fields: List<&2, Field>, single: Bool}
  JRCtors{j: JG, sub: List<&2, TB>, cs: List<&2, Ctor>, single: Bool}
  JRAdt{j: JG, ty: Core.Expr, d: Decl}
  JRHead{j: JG, ty: Core.Expr, k: Nat}
  JRBody{j: JG, ty: Core.Expr, h: String}
  JRMemo{j: JG, ty: Core.Expr, key: String, m: Maybe<&2, String>}
  JRPrinter{j: JG, ty0: Core.Expr}

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
def J.printer(j: JG, ty0: Core.Expr) -> Gen(String):
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
# The C back end's input goes through the core IR (core.bend): Core.Lo
# lowers a def to it, marking each argument of a call of a global def relevant or
# erased by the def's parameter mask; Core.Tm.erase boxes the erased ones
# and the types left in the body (PROOF.bend proves that this preserves the
# IR's semantics); Inl inlines monadic binds; Core.Tm.red makes each lambda
# applied to one argument a let (REDPROOF.bend proves that this preserves
# the semantics too); Core.Tm.known resolves each match on a known
# constructor (KNOWNPROOF.bend); Core.Tm.lit puts the numbers lets bind in
# the place of their variables' lookups (LITPROOF.bend); Core.Tm.dead drops
# lets of variables no lookup reaches (DEADPROOF.bend); Core.Up raises the
# result back to an Expr. LOPROOF.bend proves that raising a lowered def
# gives it back, and that a lowered def never fails a variable lookup.

# The parameter masks of the program's defs, which Core.Lo.go reads a
# call's from.
def Lo.mask.add(+g: G, d: Decl, m: Map<&2, List<&2, Bool>>) -> Map<&2, List<&2, Bool>>:
  match d:
    case DDef{+name, ps, b, r}:
      Map.set(&2, List<&2, Bool>, m, name, DInfo.mask(G.def(g, name)))
    case DLaw{+name, ps, r}:
      Map.set(&2, List<&2, Bool>, m, name, DInfo.mask(G.def(g, name)))
    case DEff{+name, ps, ims}:
      Map.set(&2, List<&2, Bool>, m, name, DInfo.mask(G.def(g, name)))
    case other:
      m

def Lo.masks(+g: G, ds: List<&2, Decl>, m: Map<&2, List<&2, Bool>>) -> Map<&2, List<&2, Bool>>:
  match ds:
    case Nil{}:
      m
    case d <> t:
      Lo.masks(g, t, Lo.mask.add(g, d, m))

def Up.def(d: Core.Def) -> Decl:
  match d:
    case Core.Def{name, ps, body, ret}:
      DDef{name, Core.Up.params(ps), Core.Up.go(body), Core.Up.go(ret)}

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
          Core.Lo.pt.push(Inl.rpat(q, s), Inl.rpat(Core.PtCtr{k, t}, s))
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
                      Bool.pick(Unit -> Core.Tm, Bool.and(Bool.and(String.eq(k, k2), Bool.not(String.eq(k, "%par"))), Nat.is_eq(Inl.pts.len(qs), Inl.tms.len(as))),
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
def Inl.has(+names: Set(), +n: String) -> Bool:
  Pair.snd(Set(), Bool, Set.has(names, n))

def Inl.pick(+names: Set(), +name: String) -> Bool:
  +x = Inl.monad(name)
  Bool.pick(Unit -> Bool, Bool.or(String.is_empty(x), String.eq(x, "IO")), u => False{},
    u => Bool.and(Inl.has(names, x ++ ".bind"), Inl.has(names, x ++ ".pure")))(Unit{})

def Inl.add(+name: String, +d: Core.Def, +m: Map<&2, Core.Def>) -> Map<&2, Core.Def>:
  match d:
    case Core.Def{n, ps, +body, ret}:
      Bool.pick(Map<&2, Core.Def>, Str.has(Inl.names(body, 3, Nil{}), name), m, Map.set(&2, Core.Def, m, name, d))

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

# Optimizer
# ---------
#
# Opt runs on the whole program in the core IR, after erasure. Each pass
# can be turned off for measurement: BEND_OPT lists the passes that run
# (i general inlining, s simplification, ...); unset, all of them run.

# A declaration on its way through the core IR: a def lowered to it, or a
# declaration that stays as it is (a type, an effect, a type-level def).
type OD is Data:
  OCore{d: Core.Def}
  OKeep{d: Decl}

def Opt.on(+flags: String, +c: U32) -> Bool:
  String.contains(flags, Str.chr(c))

def Opt.dname(d: Core.Def) -> String:
  match d:
    case Core.Def{name, ps, b, ret}:
      name

# A def's return type, its law's when it writes none.
def Opt.ret.of(d: Decl, ret: Core.Expr) -> Core.Expr:
  match d:
    case DDef{n, ps, b, r}:
      r
    case other:
      ret

def Opt.ret(+g: G, +name: String, ret: Core.Expr) -> Core.Expr:
  Opt.ret.of(G.body(g, name), ret)

def Opt.lower(+g: G, +ms: Map<&2, List<&2, Bool>>, d: Decl) -> OD:
  match d:
    case DDef{+name, +ps, +body, +ret}:
      Bool.pick(Unit -> OD, G.erased_ty(Ty.head(ret)), u => OKeep{DDef{name, ps, body, ret}},
        u => OCore{Core.Def.erase(Core.Lo.def(ms, name, ps, body, Opt.ret(g, name, ret)))})(Unit{})
    case other:
      OKeep{other}

def Opt.lowers(+g: G, +ms: Map<&2, List<&2, Bool>>, ds: List<&2, Decl>) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Opt.lower(g, ms, d) <> Opt.lowers(g, ms, r)

def Opt.raise(d: OD) -> Decl:
  match d:
    case OCore{c}:
      Up.def(c)
    case OKeep{k}:
      k

def Opt.raises(ds: List<&2, OD>) -> List<&2, Decl>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Opt.raise(d) <> Opt.raises(r)

# acc plus the number of nodes of t (a list field as its head and the
# node rebuilt with the rest, as everywhere), stopping once past cap: a
# budget test reads only as much of a body as the budget allows.
def Opt.sz(t: Core.Tm, +acc: U32, +cap: U32) -> U32:
  match t:
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          U32.inc(acc)
        case Core.Arg{r, e} <> t2:
          +a = Opt.sz(e, acc, cap)
          Bool.pick(Unit -> U32, U32.is_lt(cap, a), u => a, u => Opt.sz(Core.CCall{f, t2}, a, cap))(Unit{})
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Opt.sz(f, U32.inc(acc), cap)
        case x <> t2:
          +a = Opt.sz(x, acc, cap)
          Bool.pick(Unit -> U32, U32.is_lt(cap, a), u => a, u => Opt.sz(Core.CApp{f, t2}, a, cap))(Unit{})
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          U32.inc(acc)
        case x <> t2:
          +a = Opt.sz(x, acc, cap)
          Bool.pick(Unit -> U32, U32.is_lt(cap, a), u => a, u => Opt.sz(Core.CCtr{k, t2}, a, cap))(Unit{})
    case Core.CLam{p, b}:
      Opt.sz(b, U32.inc(acc), cap)
    case Core.CLet{p, v, b}:
      +a = Opt.sz(v, U32.inc(acc), cap)
      Bool.pick(Unit -> U32, U32.is_lt(cap, a), u => a, u => Opt.sz(b, a, cap))(Unit{})
    case Core.CMat{scrs, cases}:
      match scrs:
        case x <> t2:
          +a = Opt.sz(x, acc, cap)
          Bool.pick(Unit -> U32, U32.is_lt(cap, a), u => a, u => Opt.sz(Core.CMat{t2, cases}, a, cap))(Unit{})
        case Nil{}:
          match cases:
            case Nil{}:
              U32.inc(acc)
            case c <> t2:
              +a = Opt.sz(c, acc, cap)
              Bool.pick(Unit -> U32, U32.is_lt(cap, a), u => a, u => Opt.sz(Core.CMat{Nil{}, t2}, a, cap))(Unit{})
    case Core.CCse{ps, b}:
      Opt.sz(b, U32.inc(acc), cap)
    case Core.CSuc{k, e}:
      Opt.sz(e, U32.inc(acc), cap)
    case Core.COp{op, x, b}:
      +a = Opt.sz(x, U32.inc(acc), cap)
      Bool.pick(Unit -> U32, U32.is_lt(cap, a), u => a, u => Opt.sz(b, a, cap))(Unit{})
    case Core.CAnn{e, ty}:
      Opt.sz(e, acc, cap)
    case other:
      U32.inc(acc)

# The number of nodes of t.
def Opt.size(t: Core.Tm) -> U32:
  Opt.sz(t, 0, 4294967295)

# Whether t has at most n nodes.
def Opt.size.le(t: Core.Tm, +n: U32) -> Bool:
  U32.is_le(Opt.sz(t, 0, n), n)

# General inlining
# ----------------
#
# Inl's context also takes every small def that calls only defs declared
# before it: a def is declared before its uses but for a law's (a cycle
# goes through a law), so the defs it picks inline into each other only
# finitely. Natives keep their calls (their Bend bodies are not what runs),
# and so does IO, whose binds the runtime reads.

def Opt.dots(s: String) -> U32:
  match s:
    case SNil{}:
      0
    case SCon{Chr{c}, t}:
      U32.add(Bool.pick(U32, U32.is_eq(c, 46), 1, 0), Opt.dots(t))

def Opt.budget(+flags: String) -> U32:
  U32.add(4, U32.mul(2, Opt.dots(flags)))

def Opt.rank(ds: List<&2, OD>, +i: U32, m: Map<&2, U32>) -> Map<&2, U32>:
  match ds:
    case Nil{}:
      m
    case d <> t:
      match d:
        case OCore{Core.Def{+name, ps, b, ret}}:
          Opt.rank(t, U32.inc(i), Map.set(&2, U32, m, name, i))
        case OKeep{k}:
          Opt.rank(t, i, m)

# Whether each def xs names comes before rank i (a name that is no def,
# a constructor's or an effect's, never inlines).
def Opt.before.one(+x: String, +rank: Map<&2, U32>, +i: U32) -> Bool:
  Bool.or(U32.is_lt(Pair.snd(Map<&2, U32>, U32, Map.get(U32, 4294967295, rank, x)), i),
    Bool.not(Pair.snd(Map<&2, U32>, Bool, Map.has(&2, U32, rank, x))))

def Opt.before(xs: List<&2, String>, +rank: Map<&2, U32>, +i: U32) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case +x <> t:
      Bool.and(Opt.before.one(x, rank, i), Opt.before(t, rank, i))

# A result built of variables, literals and constructors only.
def Opt.shape.atom(t: Core.Tm) -> Bool:
  match t:
    case Core.CVar{x}:
      True{}
    case Core.CLit{l}:
      True{}
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          True{}
        case a <> r:
          Bool.and(Opt.shape.atom(a), Opt.shape.atom(Core.CCtr{k, r}))
    case Core.CAnn{e, ty}:
      Opt.shape.atom(e)
    case other:
      False{}

# Constructor patterns (a number's would not go to the device, see Gpu).
def Opt.shape.pat(p: Core.Pt) -> Bool:
  match p:
    case Core.PtVar{x}:
      True{}
    case Core.PtCtr{k, ps}:
      match ps:
        case Nil{}:
          True{}
        case q <> r:
          Bool.and(Opt.shape.pat(q), Opt.shape.pat(Core.PtCtr{k, r}))
    case other:
      False{}

def Opt.shape.pats(ps: List<&2, Core.Pt>) -> Bool:
  match ps:
    case Nil{}:
      True{}
    case q <> r:
      Bool.and(Opt.shape.pat(q), Opt.shape.pats(r))

# Whether constructor fields hold a variable (a node, not a constant).
def Opt.shape.holds(as: List<&2, Core.Tm>) -> Bool:
  match as:
    case Nil{}:
      False{}
    case a <> r:
      match a:
        case Core.CVar{x}:
          True{}
        case Core.CCtr{k, bs}:
          Bool.or(Opt.shape.holds(bs), Opt.shape.holds(r))
        case other:
          Opt.shape.holds(r)

# Whether a result builds a node (a constructor with fields).
def Opt.shape.builds(t: Core.Tm) -> Bool:
  match t:
    case Core.CMat{scrs, cases}:
      match scrs:
        case x <> t2:
          Opt.shape.builds(Core.CMat{t2, cases})
        case Nil{}:
          match cases:
            case Nil{}:
              False{}
            case c <> r:
              Bool.or(Opt.shape.builds(c), Opt.shape.builds(Core.CMat{Nil{}, r}))
    case Core.CCse{ps, b}:
      Opt.shape.builds(b)
    case Core.CAnn{e, ty}:
      Opt.shape.builds(e)
    case Core.CLet{p, v, b}:
      Opt.shape.builds(b)
    case Core.CCtr{k, as}:
      Opt.shape.holds(as)
    case other:
      False{}

# A def that only matches and builds: every case's result is an atom, or
# a match of the same kind.
def Opt.shape(t: Core.Tm) -> Bool:
  match t:
    case Core.CMat{scrs, cases}:
      match scrs:
        case x <> t2:
          Opt.shape(Core.CMat{t2, cases})
        case Nil{}:
          match cases:
            case Nil{}:
              True{}
            case c <> r:
              Bool.and(Opt.shape(c), Opt.shape(Core.CMat{Nil{}, r}))
    case Core.CCse{ps, b}:
      Bool.and(Opt.shape.pats(ps), Opt.shape(b))
    case Core.CAnn{e, ty}:
      Opt.shape(e)
    case Core.CLet{p, v, b}:
      Bool.and(Opt.shape.atom(v), Opt.shape(b))
    case other:
      Opt.shape.atom(other)

# A def small enough to inline: its size is in the budget, or in three
# times it for a def that only matches its arguments and builds its result
# of what the match reads (inlined, the nodes its caller opens and those it
# opens are there for the result to be built in, see RU, and a match on a
# constructor the caller built is gone).
def Opt.fits(+flags: String, +b: Core.Tm) -> Bool:
  Bool.or(Opt.size.le(b, Opt.budget(flags)),
    Bool.and(Bool.and(Opt.shape(b), Opt.shape.builds(b)), Opt.size.le(b, U32.mul(3, Opt.budget(flags)))))

def Opt.small(+flags: String, +rank: Map<&2, U32>, +d: Core.Def) -> Bool:
  match d:
    case Core.Def{+name, ps, +b, ret}:
      Bool.and(Bool.and(Opt.fits(flags, b), Bool.not(G.is_native(name))),
        Bool.and(Bool.not(String.starts_with(name, "IO.")),
          Opt.before(Inl.names(b, 3, Nil{}), rank, Pair.snd(Map<&2, U32>, U32, Map.get(U32, 0, rank, name)))))

# The defs a def's calls of which are inlined: those of a monad (mon, for
# Inl), or the small ones (for Core.Tm.inline, when i is on).
def Opt.ctx(+flags: String, +mon: Bool, +names: Set(), +rank: Map<&2, U32>, ds: List<&2, OD>, +m: Map<&2, Core.Def>) -> Map<&2, Core.Def>:
  match ds:
    case Nil{}:
      m
    case d <> t:
      match d:
        case OCore{+cd}:
          Opt.ctx(flags, mon, names, rank, t, Bool.pick(Unit -> Map<&2, Core.Def>, Inl.pick(names, Opt.dname(cd)),
            u => Bool.pick(Map<&2, Core.Def>, mon, Inl.add(Opt.dname(cd), cd, m), m),
            u => Bool.pick(Unit -> Map<&2, Core.Def>, Bool.and(Bool.not(mon), Opt.on(flags, 105)),
              u2 => Bool.pick(Map<&2, Core.Def>, Opt.small(flags, rank, cd), Map.set(&2, Core.Def, m, Opt.dname(cd), cd), m),
              u2 => m)(Unit{}))(Unit{}))
        case OKeep{k}:
          Opt.ctx(flags, mon, names, rank, t, m)

# How deep Core.Tm.inline inlines the bodies it inlines.
def Opt.depth() -> Nat:
  16n

# Monad calls are expanded by Inl (the defs of cm), then calls of the small
# defs inlined by the proven pass (Core.Tm.inline, INLINEPROOF.bend), their
# bodies with monad calls expanded.
def Opt.mon(+cm: Map<&2, Core.Def>, ds: List<&2, OD>) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      match d:
        case OCore{cd}:
          OCore{Inl.def(cm, cd)} <> Opt.mon(cm, r)
        case OKeep{k}:
          OKeep{k} <> Opt.mon(cm, r)

# The defs of ds that cs holds, in its place.
def Opt.ctx.of(ds: List<&2, OD>, +cs: Map<&2, Core.Def>) -> Map<&2, Core.Def>:
  match ds:
    case Nil{}:
      cs
    case d <> r:
      match d:
        case OCore{+cd}:
          Opt.ctx.of(r, Bool.pick(Map<&2, Core.Def>, Pair.snd(Map<&2, Core.Def>, Bool, Map.has(&2, Core.Def, cs, Opt.dname(cd))),
            Map.set(&2, Core.Def, cs, Opt.dname(cd), cd), cs))
        case OKeep{k}:
          Opt.ctx.of(r, cs)

def Opt.inl(+cs: Map<&2, Core.Def>, d: OD) -> OD:
  match d:
    case OCore{cd}:
      OCore{Core.Def.dead(Core.Def.lit(Core.Def.known(Core.Def.red(Core.Def.inline(cs, Opt.depth(), cd)))))}
    case OKeep{k}:
      OKeep{k}

def Opt.inls.go(+cs: Map<&2, Core.Def>, ds: List<&2, OD>) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Opt.inl(cs, d) <> Opt.inls.go(cs, r)

def Opt.inls(+cs: Map<&2, Core.Def>, +ds: List<&2, OD>) -> List<&2, OD>:
  Opt.inls.go(Opt.ctx.of(ds, cs), ds)

# Simplification
# --------------
#
# After inlining, each def's body is simplified bottom up (s in BEND_OPT).
# The rules, at a node whose children are simplified:
# - A let whose variable is unused is dropped: its value is pure.
# - A let of an atom (a variable, a literal, a box, a nullary constructor,
#   a def's name) puts it in its variable's place; so does a let whose
#   variable is used once, outside a lambda (or anywhere, when the value is
#   a lambda or a constructor), when that captures nothing. The value then
#   runs only if its place is reached (a match's case). The walk does this
#   only when some lookup is under a binding (Opt.flat); lookups under none
#   are left to the proven Core.Def.subst (SUBSTPROOF.bend), which runs
#   after each of Opt.rounds' walks, the next walk reducing where it put
#   values.
# - A match on known constructors or literals takes the first case whose
#   patterns match, as lets (a variable bound to itself is dropped; when a
#   term would see a bound variable, the terms are bound to fresh names
#   first); one whose patterns may not match stops it.
# - A let or a match on a let floats the let out; a match on a match whose
#   cases all end in constructors the outer one knows moves the outer match
#   into them (case of case), when the copies are small.
# - An applied lambda becomes a let; an applied let or match takes the
#   arguments inside, when they are atoms.
# A substitution reduces where it lands, as Inl's does.

# A pattern against a term: the bindings (reversed), no match, or unknown.
type OPm is Data:
  PmYes{ps: List<&2, Core.Pt>, ts: List<&2, Core.Tm>}
  PmNo{}
  PmUnk{}

# What a rule gives: the node as it was, a finished term, a substitution
# of v for x in b, a term to simplify again, k new lets on top of t, or a
# new let around a new node t.
type OR is Data:
  RKeep{t: Core.Tm}
  RTo{t: Core.Tm}
  RSub{x: String, v: Core.Tm, b: Core.Tm}
  RAll{t: Core.Tm}
  RLets{k: Nat, t: Core.Tm}
  RLet1{p: Core.Pt, v: Core.Tm, t: Core.Tm}

# The simplifier's walk modes: OAll the children, then the node; OKids the
# children; ONode the rules at the node; ODo{r} what a rule gave; OFin{top}
# the rules when top; OSub{x, v, top} puts v for x and applies the rules
# where it lands; OLets{k} simplifies k new lets on top of a term.
type OW is Data:
  OAll{}
  OKids{}
  ONode{}
  ODo{r: OR}
  OFin{top: Bool}
  OSub{x: String, v: Core.Tm, top: Bool}
  OLets{k: Nat}

def Opt.strip(t: Core.Tm) -> Core.Tm:
  match t:
    case Core.CAnn{e, ty}:
      Opt.strip(e)
    case other:
      other

# Whether t is an atom: copying it copies no work. (A def's name is no
# atom: an application of it would be a call, whose arguments the erased
# parameters take; Opt.refs makes such calls.)
def Opt.atom(t: Core.Tm) -> Bool:
  match t:
    case Core.CVar{x}:
      True{}
    case Core.CLit{l}:
      True{}
    case Core.CBox{}:
      True{}
    case Core.CCtr{k, as}:
      List.is_empty(&2, Core.Tm, as)
    case other:
      False{}

def Opt.atoms(ts: List<&2, Core.Tm>) -> Bool:
  match ts:
    case Nil{}:
      True{}
    case t <> r:
      Bool.and(Opt.atom(t), Opt.atoms(r))

def Opt.pm.bind(x: Core.Pt, t: Core.Tm, r: OPm) -> OPm:
  match r:
    case PmYes{ps, ts}:
      PmYes{x <> ps, t <> ts}
    case other:
      other

def Opt.pm.and(a: OPm, b: OPm) -> OPm:
  match a:
    case PmYes{ps, ts}:
      b
    case other:
      other

def Opt.pm.if(c: Bool, r: OPm) -> OPm:
  match c:
    case True{}:
      r
    case False{}:
      PmNo{}

def Opt.pm.nat(+m: U32, p: Core.Pt, r: OPm) -> OPm:
  match p:
    case Core.PtNat{n}:
      Opt.pm.if(U32.is_eq(n, m), r)
    case Core.PtSuc{+k, q}:
      match q:
        case Core.PtVar{y}:
          Opt.pm.if(U32.is_le(k, m), Opt.pm.bind(Core.PtVar{y}, Core.CLit{Core.LNat{U32.sub(m, k)}}, r))
        case other:
          PmUnk{}
    case other:
      PmUnk{}

def Opt.pm.lit(l: Core.Lit, p: Core.Pt, r: OPm) -> OPm:
  match l:
    case Core.LNat{m}:
      Opt.pm.nat(m, p, r)
    case Core.LNum{+m}:
      match p:
        case Core.PtNum{n}:
          Opt.pm.if(U32.is_eq(n, m), r)
        case other:
          PmUnk{}
    case other:
      PmUnk{}

# Constructors k and k2 of a pattern and a term: r when they are the same,
# no match when not (Nat's are numbers, and a %par is no value: unknown).
def Opt.pm.same(+k: String, +k2: String) -> Bool:
  Bool.and(String.eq(k, k2), Bool.not(Str.has(["Zero", "Succ", "%par"], k)))

def Opt.pm.name(+k: String, +k2: String, r: OPm) -> OPm:
  Bool.pick(OPm, Str.has(["Zero", "Succ", "%par"], k), PmUnk{}, Opt.pm.if(String.eq(k, k2), r))

# The pattern p against t, onto r (a constructor's fields as its head and
# the node rebuilt with the rest).
def Opt.pm(t: Core.Tm, p: Core.Pt, r: OPm) -> OPm:
  match t p:
    case t0 Core.PtVar{x}:
      Opt.pm.bind(Core.PtVar{x}, t0, r)
    case Core.CAnn{e, ty} q:
      Opt.pm(e, q, r)
    case Core.CCtr{k2, Nil{}} Core.PtCtr{k, Nil{}}:
      Opt.pm.name(k, k2, r)
    case Core.CCtr{+k2, a <> ar} Core.PtCtr{+k, q <> qr}:
      Bool.pick(Unit -> OPm, Opt.pm.same(k, k2), u => Opt.pm(Core.CCtr{k2, ar}, Core.PtCtr{k, qr}, Opt.pm(a, q, r)),
        u => Opt.pm.name(k, k2, PmUnk{}))(Unit{})
    case Core.CLit{l} q:
      Opt.pm.lit(l, q, r)
    case t0 q:
      PmUnk{}

def Opt.pms(ps: List<&2, Core.Pt>, ts: List<&2, Core.Tm>, r: OPm) -> OPm:
  match ps:
    case Nil{}:
      r
    case p <> pr:
      match ts:
        case Nil{}:
          PmUnk{}
        case t <> tr:
          Opt.pms(pr, tr, Opt.pm(t, p, r))

# Lets binding each pattern to its term (the lists reversed), around b.
def Opt.lets(ps: List<&2, Core.Pt>, ts: List<&2, Core.Tm>, b: Core.Tm) -> Core.Tm:
  match ps:
    case Nil{}:
      b
    case p <> pr:
      match ts:
        case Nil{}:
          b
        case t <> tr:
          Opt.lets(pr, tr, Core.CLet{p, t, b})

def Opt.pvars(ps: List<&2, Core.Pt>) -> List<&2, String>:
  Inl.ppvars(ps, Nil{})

# Whether a binding binds x to x (and all, the variables bound, binds x
# once): it changes nothing.
def Opt.same(+all: List<&2, String>, p: Core.Pt, t: Core.Tm) -> Bool:
  match p t:
    case Core.PtVar{+x} Core.CVar{+y}:
      Bool.and(String.eq(x, y), U32.is_eq(Inl.count(all, x, 0), 1))
    case p0 t0:
      False{}

def Opt.trim.one(drop: Bool, p: Core.Pt, t: Core.Tm, r: OPm) -> OPm:
  match drop:
    case True{}:
      r
    case False{}:
      Opt.pm.bind(p, t, r)

# The bindings less those that change nothing.
def Opt.trim(+all: List<&2, String>, ps: List<&2, Core.Pt>, ts: List<&2, Core.Tm>) -> OPm:
  match ps:
    case Nil{}:
      PmYes{Nil{}, Nil{}}
    case +p <> pr:
      match ts:
        case Nil{}:
          PmYes{Nil{}, Nil{}}
        case +t <> tr:
          Opt.trim.one(Opt.same(all, p, t), p, t, Opt.trim(all, pr, tr))

# A name x@tI no name of avoid is (fuel: avoid's length, so one is found).
def Opt.fresh(+avoid: List<&2, String>, +x: String, fu: Nat, +i: U32) -> String:
  match fu:
    case 0n:
      x ++ "@t" ++ U32.show(i)
    case 1n+p:
      +y = x ++ "@t" ++ U32.show(i)
      Bool.pick(Unit -> String, Str.has(avoid, y), u => Opt.fresh(avoid, x, p, U32.inc(i)), u => y)(Unit{})

def Opt.pt.name(p: Core.Pt) -> String:
  match p:
    case Core.PtVar{x}:
      x
    case other:
      "_"

# The patterns (variables) with fresh names.
def Opt.freshen(+avoid: List<&2, String>, ps: List<&2, Core.Pt>) -> List<&2, Core.Pt>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> r:
      Core.PtVar{Opt.fresh(avoid, Opt.pt.name(p), List.length(&2, String, avoid), 0)} <> Opt.freshen(avoid, r)

def Opt.pt.vars(ps: List<&2, Core.Pt>) -> List<&2, Core.Tm>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> r:
      Core.CVar{Opt.pt.name(p)} <> Opt.pt.vars(r)

# Lets that bind the terms to fresh variables qs, then the patterns to
# those: no term sees a pattern's variable.
def Opt.bound.fresh(+qs: List<&2, Core.Pt>, +ps: List<&2, Core.Pt>, ts: List<&2, Core.Tm>, +b: Core.Tm) -> OR:
  RLets{Nat.add(Inl.pts.len(ps), Inl.pts.len(ps)), Opt.lets(qs, ts, Opt.lets(ps, Opt.pt.vars(qs), b))}

def Opt.bound.go(r: OPm, +b: Core.Tm) -> OR:
  match r:
    case PmYes{+ps, +ts}:
      +avoid = Inl.names(Core.CCtr{"", ts}, 0, Nil{})
      Bool.pick(Unit -> OR, Inl.apart(Opt.pvars(ps), avoid),
        u => RLets{Inl.pts.len(ps), Opt.lets(ps, ts, b)},
        u => Opt.bound.fresh(Opt.freshen(Inl.names(b, 0, Inl.names(b, 1, Inl.names(Core.CCtr{"", ts}, 1,
          List.append(&2, String, Opt.pvars(ps), avoid)))), ps), ps, ts, b))(Unit{})
    case other:
      RKeep{Core.CErr{"%miss"}}

# The bindings of a matched case, less those of a variable to itself: when
# no bound variable is read by a term bound (a let would capture it), its
# lets, else nothing.
def Opt.bound(r: OPm, +b: Core.Tm) -> OR:
  match r:
    case PmYes{+ps, ts}:
      Opt.bound.go(Opt.trim(Opt.pvars(ps), ps, ts), b)
    case other:
      RKeep{Core.CErr{"%miss"}}

def Opt.known.go(m: OPm, +b: Core.Tm, next: Unit -> OR) -> OR:
  match m:
    case PmNo{}:
      next(Unit{})
    case PmUnk{}:
      RKeep{Core.CErr{"%miss"}}
    case PmYes{ps, ts}:
      Opt.bound(PmYes{ps, ts}, b)

# The case a match on scrs takes, when it is known (RKeep{%miss} if not).
def Opt.known(+scrs: List<&2, Core.Tm>, cases: List<&2, Core.Tm>) -> OR:
  match cases:
    case Nil{}:
      RKeep{Core.CErr{"%miss"}}
    case c <> r:
      match c:
        case Core.CCse{ps, +b}:
          Opt.known.go(Opt.pms(ps, scrs, PmYes{Nil{}, Nil{}}), b, u => Opt.known(scrs, r))
        case other:
          RKeep{Core.CErr{"%miss"}}

def Opt.miss(r: OR) -> Bool:
  match r:
    case RKeep{Core.CErr{m}}:
      String.eq(m, "%miss")
    case other:
      False{}

# The term of a rule's result (a known case's lets).
def Opt.res(r: OR) -> Core.Tm:
  match r:
    case RKeep{t}:
      t
    case RTo{t}:
      t
    case RSub{x, v, b}:
      Core.CLet{Core.PtVar{x}, v, b}
    case RAll{t}:
      t
    case RLets{k, t}:
      t
    case RLet1{p, v, t}:
      Core.CLet{p, v, t}

# The body a case ends in, under its lets.
def Opt.end(t: Core.Tm) -> Core.Tm:
  match t:
    case Core.CLet{p, v, b}:
      Opt.end(b)
    case Core.CAnn{e, ty}:
      Opt.end(e)
    case other:
      other

# Case of case: each inner case's end against the outer cases (Nil{} when
# one is unknown).
def Opt.coc.ok(cs: List<&2, Core.Tm>, +outer: List<&2, Core.Tm>) -> Bool:
  match cs:
    case Nil{}:
      True{}
    case c <> r:
      match c:
        case Core.CCse{ps, b}:
          Bool.and(Bool.not(Opt.miss(Opt.known([Opt.end(b)], outer))), Opt.coc.ok(r, outer))
        case other:
          False{}

# The inner case with the outer match around its end.
def Opt.coc.put(b: Core.Tm, +outer: List<&2, Core.Tm>) -> Core.Tm:
  match b:
    case Core.CLet{p, v, e}:
      Core.CLet{p, v, Opt.coc.put(e, outer)}
    case Core.CAnn{e, ty}:
      Opt.coc.put(e, outer)
    case other:
      Core.CMat{[other], outer}

def Opt.coc.cases(cs: List<&2, Core.Tm>, +outer: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match cs:
    case Nil{}:
      Nil{}
    case c <> r:
      match c:
        case Core.CCse{ps, b}:
          Core.CCse{ps, Opt.coc.put(b, outer)} <> Opt.coc.cases(r, outer)
        case other:
          other <> Opt.coc.cases(r, outer)

# Whether moving the outer cases into n inner ones copies little, and the
# inner cases bind none of the names the outer ones read.
def Opt.coc.small(+inner: List<&2, Core.Tm>, +outer: List<&2, Core.Tm>) -> Bool:
  Bool.and(U32.is_le(U32.mul(Opt.size(Core.CMat{Nil{}, outer}), U32.from_nat(Nat.sub(Inl.tms.len(inner), 1n))), 24),
    Inl.apart(Inl.names(Core.CMat{Nil{}, inner}, 1, Nil{}), Inl.names(Core.CMat{Nil{}, outer}, 0, Nil{})))

def Opt.coc(+s: List<&2, Core.Tm>, +inner: List<&2, Core.Tm>, +outer: List<&2, Core.Tm>) -> OR:
  Bool.pick(Unit -> OR, Bool.and(Opt.coc.small(inner, outer), Opt.coc.ok(inner, outer)),
    u => RAll{Core.CMat{s, Opt.coc.cases(inner, outer)}},
    u => RKeep{Core.CMat{[Core.CMat{s, inner}], outer}})(Unit{})

# A match's rules: a known case, a let floated out of its scrutinee, a
# case of case.
def Opt.mat.one(s: Core.Tm, +cases: List<&2, Core.Tm>) -> OR:
  match s:
    case Core.CLet{+p, +v, +b}:
      Bool.pick(Unit -> OR, Inl.apart(Inl.pvars(p, Nil{}), Inl.names(Core.CMat{Nil{}, cases}, 0, Nil{})),
        u => RLet1{p, v, Core.CMat{[b], cases}},
        u => RKeep{Core.CMat{[Core.CLet{p, v, b}], cases}})(Unit{})
    case Core.CMat{+s2, +inner}:
      Opt.coc(s2, inner, cases)
    case other:
      RKeep{Core.CMat{[other], cases}}

def Opt.mat.scrs(scrs: List<&2, Core.Tm>, +cases: List<&2, Core.Tm>) -> OR:
  match scrs:
    case s <> Nil{}:
      Opt.mat.one(s, cases)
    case other:
      RKeep{Core.CMat{other, cases}}

def Opt.mat.go(+r: OR, +scrs: List<&2, Core.Tm>, +cases: List<&2, Core.Tm>) -> OR:
  Bool.pick(Unit -> OR, Opt.miss(r), u => Opt.mat.scrs(scrs, cases), u => r)(Unit{})

def Opt.mat(+scrs: List<&2, Core.Tm>, +cases: List<&2, Core.Tm>) -> OR:
  Opt.mat.go(Opt.known(scrs, cases), scrs, cases)

# A let's rules.
def Opt.let.cases(+x: String, +v: Core.Tm, cs: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match cs:
    case Nil{}:
      Nil{}
    case c <> r:
      match c:
        case Core.CCse{ps, b}:
          Core.CCse{ps, Core.CLet{Core.PtVar{x}, v, b}} <> Opt.let.cases(x, v, r)
        case other:
          other <> Opt.let.cases(x, v, r)

# A small let over a match that reads it only in its cases goes into them.
def Opt.let.sink(+x: String, +v: Core.Tm, b: Core.Tm) -> OR:
  match b:
    case Core.CMat{+scrs, +cases}:
      Bool.pick(Unit -> OR, Bool.and(Bool.and(Opt.size.le(v, 16), Bool.not(Str.has(Inl.names(Core.CMat{scrs, Nil{}}, 0, Nil{}), x))),
          Inl.apart(x <> Inl.names(v, 0, Nil{}), Inl.names(Core.CMat{Nil{}, cases}, 1, Nil{}))),
        u => RAll{Core.CMat{scrs, Opt.let.cases(x, v, cases)}},
        u => RKeep{Core.CLet{Core.PtVar{x}, v, Core.CMat{scrs, cases}}})(Unit{})
    case other:
      RKeep{Core.CLet{Core.PtVar{x}, v, other}}

# How many lookups of x t has under no binding (a lambda's, a let's in
# its body, a case's): those the proven substitution reaches.
def Opt.flat(t: Core.Tm, +x: String) -> U32:
  match t:
    case Core.CVar{y}:
      Bool.pick(U32, String.eq(x, y), 1, 0)
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          0
        case Core.Arg{r, e} <> t2:
          U32.add(Opt.flat(e, x), Opt.flat(Core.CCall{f, t2}, x))
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Opt.flat(f, x)
        case a <> t2:
          U32.add(Opt.flat(a, x), Opt.flat(Core.CApp{f, t2}, x))
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          0
        case a <> t2:
          U32.add(Opt.flat(a, x), Opt.flat(Core.CCtr{k, t2}, x))
    case Core.CLet{p, v, b}:
      Opt.flat(v, x)
    case Core.CMat{scrs, cases}:
      match scrs:
        case Nil{}:
          0
        case a <> t2:
          U32.add(Opt.flat(a, x), Opt.flat(Core.CMat{t2, cases}, x))
    case Core.CSuc{k, e}:
      Opt.flat(e, x)
    case Core.COp{op, a, b}:
      U32.add(Opt.flat(a, x), Opt.flat(b, x))
    case Core.CAnn{e, ty}:
      Opt.flat(e, x)
    case other:
      0

def Opt.let.var(+x: String, +v: Core.Tm, +b: Core.Tm) -> OR:
  +n = Inl.uses(b, 0, x)
  Bool.pick(Unit -> OR, U32.is_zero(n), u => RTo{b},
    u => Bool.pick(Unit -> OR, Bool.and(Bool.and(Bool.or(Opt.atom(v), Bool.and(U32.is_eq(n, 1), Bool.or(U32.is_eq(Inl.uses(b, 2, x), 1), Inl.shape(v)))),
        Inl.apart(Inl.names(v, 0, Nil{}), Inl.names(b, 1, Nil{}))), True{}),
      u2 => Bool.pick(Unit -> OR, U32.is_lt(Opt.flat(b, x), n), u3 => RSub{x, v, b}, u3 => Opt.let.sink(x, v, b))(Unit{}),
      u2 => Opt.let.sink(x, v, b))(Unit{}))(Unit{})

def Opt.let.ctr(+k: String, +qs: List<&2, Core.Pt>, v: Core.Tm, +b: Core.Tm) -> OR:
  match v:
    case Core.CCtr{+k2, +as}:
      Bool.pick(Unit -> OR, Bool.and(Bool.and(String.eq(k, k2), Bool.not(String.eq(k, "%par"))),
          Nat.is_eq(Inl.pts.len(qs), Inl.tms.len(as))),
        u => Opt.bound(Opt.pms(qs, as, PmYes{Nil{}, Nil{}}), b),
        u => RKeep{Core.CLet{Core.PtCtr{k, qs}, Core.CCtr{k2, as}, b}})(Unit{})
    case Core.CLet{+p2, +v2, +b2}:
      Bool.pick(Unit -> OR, Bool.and(Bool.not(String.eq(k, "%par")), Inl.apart(Inl.pvars(p2, Nil{}), Inl.names(b, 0, Nil{}))),
        u => RLet1{p2, v2, Core.CLet{Core.PtCtr{k, qs}, b2, b}},
        u => RKeep{Core.CLet{Core.PtCtr{k, qs}, Core.CLet{p2, v2, b2}, b}})(Unit{})
    case other:
      RKeep{Core.CLet{Core.PtCtr{k, qs}, other, b}}

def Opt.let(p: Core.Pt, +v: Core.Tm, +b: Core.Tm) -> OR:
  match p:
    case Core.PtVar{+x}:
      Opt.let.var(x, v, b)
    case Core.PtCtr{+k, +qs}:
      Opt.let.ctr(k, qs, v, b)
    case other:
      RKeep{Core.CLet{other, v, b}}

# An application's rules.
def Opt.app.cases(cs: List<&2, Core.Tm>, +as: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match cs:
    case Nil{}:
      Nil{}
    case c <> r:
      match c:
        case Core.CCse{ps, b}:
          Core.CCse{ps, Inl.app(b, as)} <> Opt.app.cases(r, as)
        case other:
          other <> Opt.app.cases(r, as)

def Opt.app(f: Core.Tm, +as: List<&2, Core.Tm>) -> OR:
  match f:
    case Core.CLam{+pt, +b}:
      match as:
        case Nil{}:
          RKeep{Core.CApp{Core.CLam{pt, b}, Nil{}}}
        case +a <> +r:
          Bool.pick(Unit -> OR, Inl.apart(Inl.pvars(pt, Nil{}), Inl.names(Core.CCtr{"", r}, 0, Nil{})),
            u => RLet1{pt, a, Inl.app(b, r)},
            u => RKeep{Core.CApp{Core.CLam{pt, b}, a <> r}})(Unit{})
    case Core.CLet{+pt, +v, +b}:
      Bool.pick(Unit -> OR, Inl.apart(Inl.pvars(pt, Nil{}), Inl.names(Core.CCtr{"", as}, 0, Nil{})),
        u => RLet1{pt, v, Inl.app(b, as)},
        u => RKeep{Core.CApp{Core.CLet{pt, v, b}, as}})(Unit{})
    case Core.CMat{+scrs, +cases}:
      Bool.pick(Unit -> OR, Bool.and(Opt.atoms(as), Inl.apart(Inl.names(Core.CMat{Nil{}, cases}, 1, Nil{}), Inl.names(Core.CCtr{"", as}, 0, Nil{}))),
        u => RAll{Core.CMat{scrs, Opt.app.cases(cases, as)}},
        u => RKeep{Core.CApp{Core.CMat{scrs, cases}, as}})(Unit{})
    case other:
      RKeep{Core.CApp{other, as}}

# A comparison of literal numbers, folded; a comparison of a match whose
# cases give literals goes into the cases, where it folds (b2u-style code:
# U32.is_zero(match c: 0, 1) is a match on c).
def Opt.bool(b: Bool) -> Core.Tm:
  match b:
    case True{}:
      Core.CCtr{"True", Nil{}}
    case False{}:
      Core.CCtr{"False", Nil{}}

def Opt.cmp2(+f: String, +a: U32, +b: U32) -> Core.Tm:
  Bool.pick(Core.Tm, String.eq(f, "U32.is_eq"), Opt.bool(U32.is_eq(a, b)),
    Bool.pick(Core.Tm, String.eq(f, "U32.is_ne"), Opt.bool(U32.is_ne(a, b)),
    Bool.pick(Core.Tm, String.eq(f, "U32.is_lt"), Opt.bool(U32.is_lt(a, b)),
    Bool.pick(Core.Tm, String.eq(f, "U32.is_le"), Opt.bool(U32.is_le(a, b)),
    Bool.pick(Core.Tm, String.eq(f, "U32.is_gt"), Opt.bool(U32.is_gt(a, b)),
    Bool.pick(Core.Tm, String.eq(f, "U32.is_ge"), Opt.bool(U32.is_ge(a, b)), Core.CErr{"%nofold"}))))))

def Opt.cmps(+f: String) -> Bool:
  Bool.or(Bool.or(Bool.or(String.eq(f, "U32.is_zero"), String.eq(f, "U32.is_eq")), Bool.or(String.eq(f, "U32.is_ne"), String.eq(f, "U32.is_lt"))),
    Bool.or(String.eq(f, "U32.is_le"), Bool.or(String.eq(f, "U32.is_gt"), String.eq(f, "U32.is_ge"))))

def Opt.fold(+f: String, as: List<&2, Core.Arg>) -> Core.Tm:
  match as:
    case Core.Arg{r, Core.CLit{Core.LNum{+n}}} <> Nil{}:
      Bool.pick(Core.Tm, String.eq(f, "U32.is_zero"), Opt.bool(U32.is_zero(n)), Core.CErr{"%nofold"})
    case Core.Arg{r, Core.CLit{Core.LNum{n}}} <> Core.Arg{r2, Core.CLit{Core.LNum{m}}} <> Nil{}:
      Opt.cmp2(f, n, m)
    case other:
      Core.CErr{"%nofold"}

def Opt.nofold(t: Core.Tm) -> Bool:
  match t:
    case Core.CErr{m}:
      String.eq(m, "%nofold")
    case other:
      False{}

# Whether each case of cs gives a literal number.
def Opt.lits(cs: List<&2, Core.Tm>) -> Bool:
  match cs:
    case Nil{}:
      True{}
    case c <> r:
      match c:
        case Core.CCse{ps, Core.CLit{Core.LNum{n}}}:
          Opt.lits(r)
        case other:
          False{}

# The first argument that is a match whose cases give literals (the count
# when none).
def Opt.lit.mat(as: List<&2, Core.Arg>, +i: Nat) -> Nat:
  match as:
    case Nil{}:
      i
    case Core.Arg{r, e} <> t:
      match e:
        case Core.CMat{scrs, cs}:
          Bool.pick(Unit -> Nat, Opt.lits(cs), u => i, u => Opt.lit.mat(t, 1n+i))(Unit{})
        case other:
          Opt.lit.mat(t, 1n+i)

def Opt.arg.at(n: Nat, as: List<&2, Core.Arg>) -> Core.Tm:
  match n as:
    case k Nil{}:
      Core.CBox{}
    case 0n Core.Arg{r, e} <> t:
      e
    case 1n+k a <> t:
      Opt.arg.at(k, t)

def Opt.arg.set(n: Nat, as: List<&2, Core.Arg>, +e: Core.Tm) -> List<&2, Core.Arg>:
  match n as:
    case k Nil{}:
      Nil{}
    case 0n Core.Arg{r, x} <> t:
      Core.Arg{r, e} <> t
    case 1n+k a <> t:
      a <> Opt.arg.set(k, t, e)

def Opt.arg.tms(as: List<&2, Core.Arg>) -> List<&2, Core.Tm>:
  match as:
    case Nil{}:
      Nil{}
    case Core.Arg{r, e} <> t:
      e <> Opt.arg.tms(t)

def Opt.arg.others(n: Nat, as: List<&2, Core.Arg>) -> List<&2, Core.Tm>:
  match n as:
    case k Nil{}:
      Nil{}
    case 0n a <> t:
      Opt.arg.tms(t)
    case 1n+k Core.Arg{r, e} <> t:
      e <> Opt.arg.others(k, t)

def Opt.push.cases(+f: String, +j: Nat, +as: List<&2, Core.Arg>, cs: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match cs:
    case Nil{}:
      Nil{}
    case c <> r:
      match c:
        case Core.CCse{ps, b}:
          Core.CCse{ps, Core.CCall{f, Opt.arg.set(j, as, b)}} <> Opt.push.cases(f, j, as, r)
        case other:
          other <> Opt.push.cases(f, j, as, r)

def Opt.push.at(+f: String, +j: Nat, +as: List<&2, Core.Arg>, m: Core.Tm) -> OR:
  match m:
    case Core.CMat{+scrs, +cs}:
      Bool.pick(Unit -> OR, Bool.and(Opt.atoms(Opt.arg.others(j, as)),
          Inl.apart(Inl.names(Core.CMat{Nil{}, cs}, 1, Nil{}), Inl.names(Core.CCtr{"", Opt.arg.others(j, as)}, 0, Nil{}))),
        u => RAll{Core.CMat{scrs, Opt.push.cases(f, j, as, cs)}},
        u => RKeep{Core.CCall{f, as}})(Unit{})
    case other:
      RKeep{Core.CCall{f, as}}

def Opt.push(+f: String, +as: List<&2, Core.Arg>) -> OR:
  +j = Opt.lit.mat(as, 0n)
  Bool.pick(Unit -> OR, Bool.and(Opt.cmps(f), Nat.is_lt(j, Inl.args.len(as))),
    u => Opt.push.at(f, j, as, Opt.arg.at(j, as)), u => RKeep{Core.CCall{f, as}})(Unit{})

def Opt.call(+f: String, +as: List<&2, Core.Arg>) -> OR:
  +k = Opt.fold(f, as)
  Bool.pick(Unit -> OR, Opt.nofold(k), u => Opt.push(f, as), u => RTo{k})(Unit{})

def Opt.rule(t: Core.Tm) -> OR:
  match t:
    case Core.CLet{p, v, b}:
      Opt.let(p, v, b)
    case Core.CMat{scrs, cases}:
      Opt.mat(scrs, cases)
    case Core.CApp{f, as}:
      Opt.app(f, as)
    case Core.CCall{f, as}:
      Opt.call(f, as)
    case other:
      RKeep{other}

# The walk (see OW). Fuel bounds its depth.
def Opt.go(+n: Nat, mode: OW, +t: Core.Tm) -> Core.Tm:
  match n:
    case 0n:
      t
    case 1n+p:
      match mode:
        case OAll{}:
          Opt.go(p, ONode{}, Opt.go(p, OKids{}, t))
        case ONode{}:
          Opt.go(p, ODo{Opt.rule(t)}, Core.CBox{})
        case ODo{r}:
          match r:
            case RKeep{e}:
              e
            case RTo{e}:
              e
            case RSub{+x, +v, b}:
              Opt.go(p, OSub{x, v, True{}}, b)
            case RAll{e}:
              Opt.go(p, OAll{}, e)
            case RLets{k, e}:
              Opt.go(p, OLets{k}, e)
            case RLet1{+pt, +v, e}:
              Opt.go(p, ONode{}, Core.CLet{pt, v, Opt.go(p, ONode{}, e)})
        case OLets{k}:
          match k:
            case 0n:
              t
            case 1n+j:
              match t:
                case Core.CLet{+pt, +v, +b}:
                  Opt.go(p, ONode{}, Core.CLet{pt, v, Opt.go(p, OLets{j}, b)})
                case other:
                  other
        case OFin{top}:
          Bool.pick(Unit -> Core.Tm, top, u => Opt.go(p, ONode{}, t), u => t)(Unit{})
        case OSub{+x, +v, top}:
          match t:
            case Core.CVar{+y}:
              Bool.pick(Core.Tm, String.eq(x, y), v, Core.CVar{y})
            case Core.CCall{f, as}:
              match as:
                case Nil{}:
                  Core.CCall{f, Nil{}}
                case Core.Arg{r, e} <> t2:
                  Core.Tm.push.call(Core.Arg{r, Opt.go(p, OSub{x, v, True{}}, e)},
                    Opt.go(p, OSub{x, v, False{}}, Core.CCall{f, t2}))
            case Core.CApp{f, as}:
              match as:
                case Nil{}:
                  Opt.go(p, OFin{top}, Core.CApp{Opt.go(p, OSub{x, v, True{}}, f), Nil{}})
                case a <> t2:
                  Opt.go(p, OFin{top}, Core.Tm.push(Opt.go(p, OSub{x, v, True{}}, a),
                    Opt.go(p, OSub{x, v, False{}}, Core.CApp{f, t2})))
            case Core.CCtr{k, as}:
              match as:
                case Nil{}:
                  Core.CCtr{k, Nil{}}
                case a <> t2:
                  Core.Tm.push(Opt.go(p, OSub{x, v, True{}}, a), Opt.go(p, OSub{x, v, False{}}, Core.CCtr{k, t2}))
            case Core.CLam{+pt, +b}:
              Bool.pick(Unit -> Core.Tm, Inl.binds(x, pt), u => Core.CLam{pt, b},
                u => Core.CLam{pt, Opt.go(p, OSub{x, v, True{}}, b)})(Unit{})
            case Core.CLet{+pt, v2, +b}:
              Opt.go(p, OFin{top}, Core.CLet{pt, Opt.go(p, OSub{x, v, True{}}, v2),
                Bool.pick(Unit -> Core.Tm, Inl.binds(x, pt), u => b, u => Opt.go(p, OSub{x, v, True{}}, b))(Unit{})})
            case Core.CMat{scrs, cases}:
              match scrs:
                case a <> t2:
                  Opt.go(p, OFin{top}, Core.Tm.push(Opt.go(p, OSub{x, v, True{}}, a),
                    Opt.go(p, OSub{x, v, False{}}, Core.CMat{t2, cases})))
                case Nil{}:
                  match cases:
                    case Nil{}:
                      Core.CMat{Nil{}, Nil{}}
                    case cs <> t2:
                      Core.Tm.push.case(Opt.go(p, OSub{x, v, True{}}, cs), Opt.go(p, OSub{x, v, False{}}, Core.CMat{Nil{}, t2}))
            case Core.CCse{+ps, +b}:
              Bool.pick(Unit -> Core.Tm, Inl.binds.any(x, ps), u => Core.CCse{ps, b},
                u => Core.CCse{ps, Opt.go(p, OSub{x, v, True{}}, b)})(Unit{})
            case Core.CSuc{k, e}:
              Core.CSuc{k, Opt.go(p, OSub{x, v, True{}}, e)}
            case Core.COp{op, a, b}:
              Core.COp{op, Opt.go(p, OSub{x, v, True{}}, a), Opt.go(p, OSub{x, v, True{}}, b)}
            case Core.CAnn{e, ty}:
              Core.CAnn{Opt.go(p, OSub{x, v, True{}}, e), ty}
            case other:
              other
        case OKids{}:
          match t:
            case Core.CCall{f, as}:
              match as:
                case Nil{}:
                  Core.CCall{f, Nil{}}
                case Core.Arg{r, e} <> t2:
                  Core.Tm.push.call(Core.Arg{r, Opt.go(p, OAll{}, e)}, Opt.go(p, OKids{}, Core.CCall{f, t2}))
            case Core.CApp{f, as}:
              match as:
                case Nil{}:
                  Core.CApp{Opt.go(p, OAll{}, f), Nil{}}
                case a <> t2:
                  Core.Tm.push(Opt.go(p, OAll{}, a), Opt.go(p, OKids{}, Core.CApp{f, t2}))
            case Core.CCtr{k, as}:
              match as:
                case Nil{}:
                  Core.CCtr{k, Nil{}}
                case a <> t2:
                  Core.Tm.push(Opt.go(p, OAll{}, a), Opt.go(p, OKids{}, Core.CCtr{k, t2}))
            case Core.CLam{pt, b}:
              Core.CLam{pt, Opt.go(p, OAll{}, b)}
            case Core.CLet{pt, v, b}:
              Core.CLet{pt, Opt.go(p, OAll{}, v), Opt.go(p, OAll{}, b)}
            case Core.CMat{scrs, cases}:
              match scrs:
                case a <> t2:
                  Core.Tm.push(Opt.go(p, OAll{}, a), Opt.go(p, OKids{}, Core.CMat{t2, cases}))
                case Nil{}:
                  match cases:
                    case Nil{}:
                      Core.CMat{Nil{}, Nil{}}
                    case cs <> t2:
                      Core.Tm.push.case(Opt.go(p, OAll{}, cs), Opt.go(p, OKids{}, Core.CMat{Nil{}, t2}))
            case Core.CCse{ps, b}:
              Core.CCse{ps, Opt.go(p, OAll{}, b)}
            case Core.CSuc{k, e}:
              Core.CSuc{k, Opt.go(p, OAll{}, e)}
            case Core.COp{op, a, b}:
              Core.COp{op, Opt.go(p, OAll{}, a), Opt.go(p, OAll{}, b)}
            case Core.CAnn{e, ty}:
              Core.CAnn{Opt.go(p, OAll{}, e), ty}
            case other:
              other

# Opt's walk on a def's body.
def Opt.walk(d: Core.Def) -> Core.Def:
  match d:
    case Core.Def{name, ps, body, ret}:
      Core.Def{name, ps, Opt.go(Fuel.max(), OAll{}, body), ret}

# The proven substitution (Core.Def.subst, SUBSTPROOF.bend), then the
# proven dead-let pass, which drops the lets it emptied.
def Opt.sub(d: Core.Def) -> Core.Def:
  Core.Def.dead(Core.Def.subst(d))

# n rounds of the walk, each followed by the proven substitution (which
# does not reduce where it lands; the next round does).
def Opt.rounds(n: Nat, d: Core.Def) -> Core.Def:
  match n:
    case 0n:
      d
    case 1n+k:
      Opt.rounds(k, Opt.sub(Opt.walk(d)))

def Opt.simp(+flags: String, d: OD) -> OD:
  match d:
    case OCore{+cd}:
      OCore{Bool.pick(Unit -> Core.Def, Opt.on(flags, 115), u => Opt.rounds(3n, Opt.sub(cd)), u => cd)(Unit{})}
    case OKeep{k}:
      OKeep{k}

def Opt.simps(+flags: String, ds: List<&2, OD>) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Opt.simp(flags, d) <> Opt.simps(flags, r)

# The proven substitution once more, after specialization and fusion,
# whose walks leave to it the lookups under no binding.
def Opt.resub(+flags: String, ds: List<&2, OD>) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      match d:
        case OCore{+cd}:
          OCore{Bool.pick(Unit -> Core.Def, Opt.on(flags, 115), u => Opt.sub(cd), u => cd)(Unit{})} <> Opt.resub(flags, r)
        case OKeep{k}:
          OKeep{k} <> Opt.resub(flags, r)

# A def's name applied to arguments (which inlining and substitution make
# of a function parameter given a def) becomes a call of it, the erased
# parameters boxed: raised, an application of a name is a call, and a
# call's arguments are the def's, erased ones too.
def Opt.refs.take(ps: List<&2, Core.Par>, as: List<&2, Core.Tm>) -> List<&2, Core.Arg>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Par{x, rel, m, ty} <> pr:
      match rel:
        case Core.Era{}:
          Core.Arg{Core.Era{}, Core.CBox{}} <> Opt.refs.take(pr, as)
        case Core.Run{}:
          match as:
            case Nil{}:
              Nil{}
            case a <> ar:
              Core.Arg{Core.Run{}, a} <> Opt.refs.take(pr, ar)

def Opt.refs.left(ps: List<&2, Core.Par>, as: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match ps:
    case Nil{}:
      as
    case Core.Par{x, rel, m, ty} <> pr:
      match rel:
        case Core.Era{}:
          Opt.refs.left(pr, as)
        case Core.Run{}:
          match as:
            case Nil{}:
              Nil{}
            case a <> ar:
              Opt.refs.left(pr, ar)

# Every parameter's argument, the erased ones boxed.
def Opt.refs.all(ps: List<&2, Core.Par>, as: List<&2, Core.Tm>) -> List<&2, Core.Arg>:
  match ps as:
    case Core.Par{x, Core.Era{}, m, ty} <> pr a <> ar:
      Core.Arg{Core.Era{}, Core.CBox{}} <> Opt.refs.all(pr, ar)
    case Core.Par{x, Core.Run{}, m, ty} <> pr a <> ar:
      Core.Arg{Core.Run{}, a} <> Opt.refs.all(pr, ar)
    case qs bs:
      Nil{}

# An application with an argument for every parameter (a function type
# with erased parameters, as @-x: A -> B, is applied to them) pairs them;
# one with fewer takes them for the runtime parameters.
def Opt.refs.fix(+g: String, +has: Bool, +ps: List<&2, Core.Par>, +as: List<&2, Core.Tm>) -> Core.Tm:
  Bool.pick(Unit -> Core.Tm, Bool.and(has, Nat.is_eq(Inl.pars.len(ps), Inl.tms.len(as))),
    u => Core.CCall{g, Opt.refs.all(ps, as)},
    u => Bool.pick(Core.Tm, has, Inl.app(Core.CCall{g, Opt.refs.take(ps, as)}, Opt.refs.left(ps, as)),
      Core.CApp{Core.CRef{g}, as}))(Unit{})

def Opt.refs.app(+c: Map<&2, Core.Def>, f: Core.Tm, +as: List<&2, Core.Tm>) -> Core.Tm:
  match f:
    case Core.CRef{+g}:
      Opt.refs.fix(g, Pair.snd(Map<&2, Core.Def>, Bool, Map.has(&2, Core.Def, c, g)),
        Inl.pars(Pair.snd(Map<&2, Core.Def>, Core.Def, Map.get(Core.Def, Core.Def{"", Nil{}, Core.CBox{}, Core.CBox{}}, c, g))), as)
    case other:
      Core.CApp{other, as}

def Opt.refs.top(+c: Map<&2, Core.Def>, top: Bool, t: Core.Tm) -> Core.Tm:
  match top:
    case True{}:
      match t:
        case Core.CApp{f, as}:
          Opt.refs.app(c, f, as)
        case other:
          other
    case False{}:
      t

# t with its applications of names made calls (top: t is the node itself,
# not one rebuilt with the rest of a list field).
def Opt.refs(+c: Map<&2, Core.Def>, t: Core.Tm, top: Bool) -> Core.Tm:
  match t:
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          Core.CCall{f, Nil{}}
        case Core.Arg{r, e} <> t2:
          Core.Tm.push.call(Core.Arg{r, Opt.refs(c, e, True{})}, Opt.refs(c, Core.CCall{f, t2}, False{}))
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Opt.refs.top(c, top, Core.CApp{Opt.refs(c, f, True{}), Nil{}})
        case a <> t2:
          Opt.refs.top(c, top, Core.Tm.push(Opt.refs(c, a, True{}), Opt.refs(c, Core.CApp{f, t2}, False{})))
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          Core.CCtr{k, Nil{}}
        case a <> t2:
          Core.Tm.push(Opt.refs(c, a, True{}), Opt.refs(c, Core.CCtr{k, t2}, False{}))
    case Core.CLam{pt, b}:
      Core.CLam{pt, Opt.refs(c, b, True{})}
    case Core.CLet{pt, v, b}:
      Core.CLet{pt, Opt.refs(c, v, True{}), Opt.refs(c, b, True{})}
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> t2:
          Core.Tm.push(Opt.refs(c, a, True{}), Opt.refs(c, Core.CMat{t2, cases}, False{}))
        case Nil{}:
          match cases:
            case Nil{}:
              Core.CMat{Nil{}, Nil{}}
            case cs <> t2:
              Core.Tm.push.case(Opt.refs(c, cs, True{}), Opt.refs(c, Core.CMat{Nil{}, t2}, False{}))
    case Core.CCse{ps, b}:
      Core.CCse{ps, Opt.refs(c, b, True{})}
    case Core.CSuc{k, e}:
      Core.CSuc{k, Opt.refs(c, e, True{})}
    case Core.COp{op, a, b}:
      Core.COp{op, Opt.refs(c, a, True{}), Opt.refs(c, b, True{})}
    case Core.CAnn{e, ty}:
      Core.CAnn{Opt.refs(c, e, True{}), ty}
    case other:
      other


# Specialization
# --------------
#
# A call that passes a closed function (a lambda with no free variables,
# as every ~template argument is, or a def's name) for a parameter the
# callee passes unchanged to each of its own calls (List.map's f) calls a
# copy of the callee for that function instead (p in BEND_OPT): the copy's
# body takes the function in the parameter's place, simplified, so each
# application of it is the function's body, and its self-calls drop the
# argument. Copies are shared by name (the callee and a hash of the
# argument's text); each round specializes the calls in the copies the
# round before made.

# A term's text, for a copy's name: it determines the term.
def Opt.show.pt(p: Core.Pt) -> String:
  match p:
    case Core.PtVar{x}:
      x
    case Core.PtCtr{k, ps}:
      match ps:
        case Nil{}:
          k ++ "{}"
        case q <> t:
          Opt.show.pt(q) ++ "," ++ Opt.show.pt(Core.PtCtr{k, t})
    case Core.PtNat{n}:
      U32.show(n) ++ "n"
    case Core.PtSuc{k, q}:
      U32.show(k) ++ "+" ++ Opt.show.pt(q)
    case Core.PtNum{n}:
      U32.show(n)
    case Core.PtFlt{s}:
      s ++ "f"

def Opt.show.pts(ps: List<&2, Core.Pt>) -> String:
  match ps:
    case Nil{}:
      ""
    case p <> t:
      Opt.show.pt(p) ++ " " ++ Opt.show.pts(t)

def Opt.show.lit(l: Core.Lit) -> String:
  match l:
    case Core.LNum{n}:
      U32.show(n)
    case Core.LNat{n}:
      U32.show(n) ++ "n"
    case Core.LFlt{s}:
      s ++ "f"
    case Core.LStr{s}:
      "\"" ++ s ++ "\""

def Opt.show(t: Core.Tm) -> String:
  match t:
    case Core.CVar{x}:
      x
    case Core.CLit{l}:
      Opt.show.lit(l)
    case Core.CRef{f}:
      "&" ++ f
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          f ++ "()"
        case Core.Arg{r, e} <> t2:
          "(" ++ Opt.show(e) ++ ")" ++ Opt.show(Core.CCall{f, t2})
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          "@" ++ Opt.show(f)
        case a <> t2:
          "(" ++ Opt.show(a) ++ ")" ++ Opt.show(Core.CApp{f, t2})
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          k ++ "{}"
        case a <> t2:
          "(" ++ Opt.show(a) ++ ")" ++ Opt.show(Core.CCtr{k, t2})
    case Core.CLam{p, b}:
      "\\" ++ Opt.show.pt(p) ++ "." ++ Opt.show(b)
    case Core.CLet{p, v, b}:
      "let " ++ Opt.show.pt(p) ++ "=" ++ Opt.show(v) ++ ";" ++ Opt.show(b)
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> t2:
          "(" ++ Opt.show(a) ++ ")" ++ Opt.show(Core.CMat{t2, cases})
        case Nil{}:
          match cases:
            case Nil{}:
              "match"
            case c <> t2:
              "[" ++ Opt.show(c) ++ "]" ++ Opt.show(Core.CMat{Nil{}, t2})
    case Core.CCse{ps, b}:
      "case " ++ Opt.show.pts(ps) ++ ":" ++ Opt.show(b)
    case Core.CSuc{k, e}:
      U32.show(k) ++ "+(" ++ Opt.show(e) ++ ")"
    case Core.COp{op, a, b}:
      "(" ++ Opt.show(a) ++ " " ++ op ++ " " ++ Opt.show(b) ++ ")"
    case Core.CAnn{e, ty}:
      "(" ++ Opt.show(e) ++ ":" ++ ty ++ ")"
    case Core.CTyp{n, as}:
      "T"
    case Core.CBox{}:
      "_"
    case Core.CErr{m}:
      "!" ++ m

# Two hashes of a string (FNV-1a, and base 31).
def Opt.hash(s: String, +a: U32, +b: U32) -> String:
  match s:
    case SNil{}:
      U32.show(a) ++ "x" ++ U32.show(b)
    case SCon{Chr{+c}, t}:
      Opt.hash(t, U32.mul(U32.xor(a, c), 16777619), U32.add(U32.mul(b, 31), c))

# The variables t reads that it does not bind (onto acc).
def Opt.fv(t: Core.Tm, +bound: List<&2, String>, +acc: List<&2, String>) -> List<&2, String>:
  match t:
    case Core.CVar{+x}:
      Bool.pick(List<&2, String>, Str.has(bound, x), acc, x <> acc)
    case Core.CCall{f, as}:
      match as:
        case Nil{}:
          acc
        case Core.Arg{r, e} <> t2:
          Opt.fv(Core.CCall{f, t2}, bound, Opt.fv(e, bound, acc))
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Opt.fv(f, bound, acc)
        case a <> t2:
          Opt.fv(Core.CApp{f, t2}, bound, Opt.fv(a, bound, acc))
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          acc
        case a <> t2:
          Opt.fv(Core.CCtr{k, t2}, bound, Opt.fv(a, bound, acc))
    case Core.CLam{p, b}:
      Opt.fv(b, Inl.pvars(p, bound), acc)
    case Core.CLet{p, v, b}:
      Opt.fv(b, Inl.pvars(p, bound), Opt.fv(v, bound, acc))
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> t2:
          Opt.fv(Core.CMat{t2, cases}, bound, Opt.fv(a, bound, acc))
        case Nil{}:
          match cases:
            case Nil{}:
              acc
            case c <> t2:
              Opt.fv(Core.CMat{Nil{}, t2}, bound, Opt.fv(c, bound, acc))
    case Core.CCse{ps, b}:
      Opt.fv(b, Inl.ppvars(ps, bound), acc)
    case Core.CSuc{k, e}:
      Opt.fv(e, bound, acc)
    case Core.COp{op, a, b}:
      Opt.fv(b, bound, Opt.fv(a, bound, acc))
    case Core.CAnn{e, ty}:
      Opt.fv(e, bound, acc)
    case Core.CTyp{n, as}:
      match as:
        case Nil{}:
          acc
        case a <> t2:
          Opt.fv(Core.CTyp{n, t2}, bound, Opt.fv(a, bound, acc))
    case other:
      acc

# Whether t is a closed function: a lambda that reads no variable it does
# not bind, or a def's name.
def Opt.fn(t: Core.Tm) -> Bool:
  match t:
    case Core.CLam{p, +b}:
      List.is_empty(&2, String, Opt.fv(Core.CLam{p, b}, Nil{}, Nil{}))
    case Core.CRef{f}:
      True{}
    case Core.CAnn{e, ty}:
      Opt.fn(e)
    case other:
      False{}

def Opt.nth.arg(n: Nat, as: List<&2, Core.Arg>) -> Core.Tm:
  match n as:
    case k Nil{}:
      Core.CBox{}
    case 0n Core.Arg{r, e} <> t:
      e
    case 1n+m Core.Arg{r, e} <> t:
      Opt.nth.arg(m, t)

def Opt.drop.arg(n: Nat, as: List<&2, Core.Arg>) -> List<&2, Core.Arg>:
  match n as:
    case k Nil{}:
      Nil{}
    case 0n a <> t:
      t
    case 1n+m a <> t:
      a <> Opt.drop.arg(m, t)

def Opt.drop.par(n: Nat, ps: List<&2, Core.Par>) -> List<&2, Core.Par>:
  match n ps:
    case k Nil{}:
      Nil{}
    case 0n p <> t:
      t
    case 1n+m p <> t:
      p <> Opt.drop.par(m, t)

def Opt.is.var(+x: String, t: Core.Tm) -> Bool:
  match t:
    case Core.CVar{y}:
      String.eq(x, y)
    case other:
      False{}

def Opt.args.tms(as: List<&2, Core.Arg>) -> List<&2, Core.Tm>:
  match as:
    case Nil{}:
      Nil{}
    case Core.Arg{r, e} <> t:
      e <> Opt.args.tms(t)

# Whether a call of g with as passes x at position i, with every argument,
# if g is f.
def Opt.static.self(+f: String, +g: String, +i: Nat, +x: String, +n: Nat, +as: List<&2, Core.Arg>) -> Bool:
  Bool.or(Bool.not(String.eq(f, g)), Bool.and(Nat.is_eq(Inl.args.len(as), n), Opt.is.var(x, Opt.nth.arg(i, as))))

# Whether each call of f in t passes x at position i, with every argument,
# and t names f nowhere else (fuel bounds the walk, which takes a call's
# arguments as an application's).
def Opt.static(fu: Nat, +f: String, +i: Nat, +x: String, +n: Nat, t: Core.Tm) -> Bool:
  match fu:
    case 0n:
      False{}
    case 1n+(+p):
      match t:
        case Core.CRef{g}:
          Bool.not(String.eq(f, g))
        case Core.CCall{+g, +as}:
          Bool.and(Opt.static.self(f, g, i, x, n, as), Opt.static(p, f, i, x, n, Core.CApp{Core.CBox{}, Opt.args.tms(as)}))
        case Core.CApp{h, as}:
          match as:
            case Nil{}:
              Opt.static(p, f, i, x, n, h)
            case a <> t2:
              Bool.and(Opt.static(p, f, i, x, n, a), Opt.static(p, f, i, x, n, Core.CApp{h, t2}))
        case Core.CCtr{k, as}:
          match as:
            case Nil{}:
              True{}
            case a <> t2:
              Bool.and(Opt.static(p, f, i, x, n, a), Opt.static(p, f, i, x, n, Core.CCtr{k, t2}))
        case Core.CLam{pt, b}:
          Opt.static(p, f, i, x, n, b)
        case Core.CLet{pt, v, b}:
          Bool.and(Opt.static(p, f, i, x, n, v), Opt.static(p, f, i, x, n, b))
        case Core.CMat{scrs, cases}:
          match scrs:
            case a <> t2:
              Bool.and(Opt.static(p, f, i, x, n, a), Opt.static(p, f, i, x, n, Core.CMat{t2, cases}))
            case Nil{}:
              match cases:
                case Nil{}:
                  True{}
                case c <> t2:
                  Bool.and(Opt.static(p, f, i, x, n, c), Opt.static(p, f, i, x, n, Core.CMat{Nil{}, t2}))
        case Core.CCse{ps, b}:
          Opt.static(p, f, i, x, n, b)
        case Core.CSuc{k, e}:
          Opt.static(p, f, i, x, n, e)
        case Core.COp{op, a, b}:
          Bool.and(Opt.static(p, f, i, x, n, a), Opt.static(p, f, i, x, n, b))
        case Core.CAnn{e, ty}:
          Opt.static(p, f, i, x, n, e)
        case other:
          True{}

# A copy to make: its name, the callee, the position and the function.
type OSp is Data:
  OSp{name: String, f: String, i: Nat, arg: Core.Tm}

# Where a call goes: to a copy of the callee (without argument i), or as
# it is.
type OPk is Data:
  PkNo{}
  PkYes{name: String, i: Nat, arg: Core.Tm}
  PkFuse{name: String, j: Nat, g: String, p: String}

# What decides a call: the program's defs (a call that passes a closed
# function), or a copy being made (its callee's self-calls).
type ODec is Data:
  DCtx{c: Map<&2, Core.Def>}
  DSelf{f: String, i: Nat, name: String}
  DFuCtx{c: Map<&2, Core.Def>}
  DFuSelf{g: String, j: Nat, p: String, n: Nat, name: String}

def Opt.sp.budget() -> U32:
  400

def Opt.sp.name(+f: String, +i: Nat, +a: Core.Tm) -> String:
  f ++ "%s" ++ Opt.hash(Opt.show(a) ++ "#" ++ U32.show(U32.from_nat(i)), 2166136261, 7)

def Opt.get(+c: Map<&2, Core.Def>, +f: String) -> Core.Def:
  Pair.snd(Map<&2, Core.Def>, Core.Def, Map.get(Core.Def, Core.Def{"", Nil{}, Core.CBox{}, Core.CBox{}}, c, f))

def Opt.has(+c: Map<&2, Core.Def>, +f: String) -> Bool:
  Pair.snd(Map<&2, Core.Def>, Bool, Map.has(&2, Core.Def, c, f))

def Opt.rel.run(r: Core.Rel) -> Bool:
  match r:
    case Core.Run{}:
      True{}
    case Core.Era{}:
      False{}

# Whether a def's name names a function (a def with a runtime parameter).
def Opt.sp.runs(ps: List<&2, Core.Par>) -> Bool:
  match ps:
    case Nil{}:
      False{}
    case Core.Par{x, rel, m, ty} <> r:
      Bool.or(Opt.rel.run(rel), Opt.sp.runs(r))

def Opt.sp.fn(+c: Map<&2, Core.Def>, t: Core.Tm) -> Bool:
  match t:
    case Core.CRef{+g}:
      Bool.and(Opt.has(c, g), Opt.sp.runs(Inl.pars(Opt.get(c, g))))
    case other:
      Opt.fn(other)

# The first position a call's closed function can be specialized at (the
# arity when none).
def Opt.sp.pos(+c: Map<&2, Core.Def>, ps: List<&2, Core.Par>, as: List<&2, Core.Arg>, +i: Nat, +f: String, +b: Core.Tm, +n: Nat) -> Nat:
  match ps as:
    case Core.Par{+x, rel, m, ty} <> pr Core.Arg{r, +e} <> ar:
      Bool.pick(Unit -> Nat, Bool.and(Bool.and(Opt.rel.run(rel), Opt.sp.fn(c, e)),
          Bool.and(Opt.static(Fuel.max(), f, i, x, n, b), Bool.not(Str.has(Inl.names(b, 1, Nil{}), x)))),
        u => i, u => Opt.sp.pos(c, pr, ar, 1n+i, f, b, n))(Unit{})
    case qs bs:
      n

def Opt.sp.at.pos(+i: Nat, +f: String, +as: List<&2, Core.Arg>) -> OPk:
  Bool.pick(Unit -> OPk, Nat.is_eq(i, Inl.args.len(as)), u => PkNo{},
    u => PkYes{Opt.sp.name(f, i, Opt.nth.arg(i, as)), i, Opt.nth.arg(i, as)})(Unit{})

def Opt.sp.def(+c: Map<&2, Core.Def>, +f: String, +as: List<&2, Core.Arg>, d: Core.Def) -> OPk:
  match d:
    case Core.Def{name, +ps, +b, ret}:
      Bool.pick(Unit -> OPk, Bool.and(Bool.and(Nat.is_eq(Inl.pars.len(ps), Inl.args.len(as)), Bool.not(Nat.is_eq(Inl.args.len(as), 0n))),
          Bool.and(Bool.not(G.is_native(f)), Bool.not(String.starts_with(f, "IO.")))),
        u => Bool.pick(Unit -> OPk, Opt.size.le(b, Opt.sp.budget()),
          u2 => Opt.sp.at.pos(Opt.sp.pos(c, ps, as, 0n, f, b, Inl.pars.len(ps)), f, as), u2 => PkNo{})(Unit{}),
        u => PkNo{})(Unit{})

# Fusion decides a call g(.., p(..), ..) where g matches on that argument
# alone and uses it nowhere else, and some result of p is a constructor.
def Opt.fu.ok(+f: String) -> Bool:
  Bool.and(Bool.not(G.is_native(f)), Bool.not(String.starts_with(f, "IO.")))

def Opt.fu.name(+g: String, +j: Nat, +p: String) -> String:
  g ++ "%f" ++ Opt.hash(p ++ "#" ++ U32.show(U32.from_nat(j)), 2166136261, 7)

# The variable a body matches on, alone ("" when it does not).
def Opt.fu.scr(b: Core.Tm) -> String:
  match b:
    case Core.CMat{scrs, cases}:
      match scrs:
        case Core.CVar{x} <> Nil{}:
          x
        case other:
          ""
    case Core.CAnn{e, ty}:
      Opt.fu.scr(e)
    case other:
      ""

def Opt.par.pos(ps: List<&2, Core.Par>, +x: String, +i: Nat) -> Nat:
  match ps:
    case Nil{}:
      i
    case Core.Par{y, rel, m, ty} <> r:
      Bool.pick(Unit -> Nat, String.eq(x, y), u => i, u => Opt.par.pos(r, x, 1n+i))(Unit{})

# Whether a field of a constructor is a call of p.
def Opt.fu.self.field(+p: String, as: List<&2, Core.Tm>) -> Bool:
  match as:
    case Nil{}:
      False{}
    case a <> r:
      match a:
        case Core.CCall{q, qs}:
          Bool.or(String.eq(p, q), Opt.fu.self.field(p, r))
        case other:
          Opt.fu.self.field(p, r)

# Whether some result of t is a constructor with a field that calls p
# (p builds a structure, one node a call).
def Opt.fu.ctail(+p: String, t: Core.Tm) -> Bool:
  match t:
    case Core.CCtr{k, as}:
      Opt.fu.self.field(p, as)
    case Core.CLet{pt, v, b}:
      Opt.fu.ctail(p, b)
    case Core.CAnn{e, ty}:
      Opt.fu.ctail(p, e)
    case Core.CMat{scrs, cases}:
      match cases:
        case Nil{}:
          False{}
        case c <> t2:
          Bool.or(Opt.fu.ctail(p, c), Opt.fu.ctail(p, Core.CMat{scrs, t2}))
    case Core.CCse{ps, b}:
      Opt.fu.ctail(p, b)
    case other:
      False{}

def Opt.fu.gbudget() -> U32:
  120

def Opt.fu.pbudget() -> U32:
  300

# The position a consumer g matches on (n, the arity, when none).
# (the tests from the cheapest, each only when those before it hold)
def Opt.fu.j.go(+name: String, +ps: List<&2, Core.Par>, +b: Core.Tm, +x: String, +n: Nat) -> Nat:
  Bool.pick(Unit -> Nat, Bool.and(Str.has(Inl.names(b, 3, Nil{}), name), U32.is_eq(Inl.uses(b, 0, x), 1)),
    u => Opt.par.pos(ps, x, 0n), u => n)(Unit{})

def Opt.fu.j(d: Core.Def, +n: Nat) -> Nat:
  match d:
    case Core.Def{+name, +ps, +b, ret}:
      +x = Opt.fu.scr(b)
      Bool.pick(Unit -> Nat, Bool.and(Nat.is_eq(Inl.pars.len(ps), n), Bool.not(String.eq(x, ""))),
        u => Bool.pick(Unit -> Nat, Opt.size.le(b, Opt.fu.gbudget()), u2 => Opt.fu.j.go(name, ps, b, x, n), u2 => n)(Unit{}),
        u => n)(Unit{})

def Opt.fu.prod(d: Core.Def, +n: Nat) -> Bool:
  match d:
    case Core.Def{+name, ps, +b, ret}:
      Bool.pick(Unit -> Bool, Nat.is_eq(Inl.pars.len(ps), n),
        u => Bool.pick(Unit -> Bool, Opt.size.le(b, Opt.fu.pbudget()), u2 => Opt.fu.ctail(name, b), u2 => False{})(Unit{}),
        u => False{})(Unit{})

def Opt.fu.pick(+c: Map<&2, Core.Def>, +g: String, +j: Nat, a: Core.Tm) -> OPk:
  match a:
    case Core.CCall{+p, pas}:
      Bool.pick(Unit -> OPk, Bool.and(Bool.and(Opt.has(c, p), Opt.fu.ok(p)), Bool.not(String.eq(g, p))),
        u => Bool.pick(OPk, Opt.fu.prod(Opt.get(c, p), Inl.args.len(pas)), PkFuse{Opt.fu.name(g, j, p), j, g, p}, PkNo{}),
        u => PkNo{})(Unit{})
    case other:
      PkNo{}

def Opt.fu.at.j(+c: Map<&2, Core.Def>, +g: String, +j: Nat, +as: List<&2, Core.Arg>) -> OPk:
  Bool.pick(Unit -> OPk, Nat.is_lt(j, Inl.args.len(as)), u => Opt.fu.pick(c, g, j, Opt.nth.arg(j, as)), u => PkNo{})(Unit{})

def Opt.fu.at(+c: Map<&2, Core.Def>, +g: String, +as: List<&2, Core.Arg>) -> OPk:
  Bool.pick(Unit -> OPk, Bool.and(Opt.has(c, g), Opt.fu.ok(g)),
    u => Opt.fu.at.j(c, g, Opt.fu.j(Opt.get(c, g), Inl.args.len(as)), as),
    u => PkNo{})(Unit{})

def Opt.fu.is.call(+p: String, +n: Nat, a: Core.Tm) -> Bool:
  match a:
    case Core.CCall{q, pas}:
      Bool.and(String.eq(p, q), Nat.is_eq(Inl.args.len(pas), n))
    case other:
      False{}

def Opt.fu.redirect(+name: String, +f: String, +j: Nat, +p: String, +as: List<&2, Core.Arg>, a: Core.Tm) -> Core.Tm:
  match a:
    case Core.CCall{+q, pas}:
      Bool.pick(Unit -> Core.Tm, String.eq(p, q), u => Core.CCall{name, List.append(&2, Core.Arg, Opt.drop.arg(j, as), pas)},
        u => Core.CCall{f, as})(Unit{})
    case other:
      Core.CCall{f, as}

def Opt.sp.at(dec: ODec, +f: String, +as: List<&2, Core.Arg>) -> OPk:
  match dec:
    case DCtx{+c}:
      Bool.pick(Unit -> OPk, Opt.has(c, f), u => Opt.sp.def(c, f, as, Opt.get(c, f)), u => PkNo{})(Unit{})
    case DSelf{+g, i, name}:
      Bool.pick(OPk, String.eq(f, g), PkYes{name, i, Core.CBox{}}, PkNo{})
    case DFuCtx{+c}:
      Opt.fu.at(c, f, as)
    case DFuSelf{+g, +j, +p, +n, name}:
      Bool.pick(Unit -> OPk, String.eq(f, g), u => Bool.pick(OPk, Opt.fu.is.call(p, n, Opt.nth.arg(j, as)), PkFuse{name, j, g, p}, PkNo{}),
        u => PkNo{})(Unit{})

def Opt.sp.redirect(k: OPk, t: Core.Tm) -> Core.Tm:
  match k:
    case PkNo{}:
      t
    case PkYes{name, i, a}:
      match t:
        case Core.CCall{f, as}:
          Core.CCall{name, Opt.drop.arg(i, as)}
        case other:
          other
    case PkFuse{+name, +j, g, +p}:
      match t:
        case Core.CCall{+f, +as}:
          Opt.fu.redirect(name, f, j, p, as, Opt.nth.arg(j, as))
        case other:
          other

# t with the calls dec picks sent to their copies (fuel bounds the walk;
# top: t is the node itself, not one rebuilt with the rest of a list field).
def Opt.sp.rw(fu: Nat, +dec: ODec, top: Bool, t: Core.Tm) -> Core.Tm:
  match fu:
    case 0n:
      t
    case 1n+(+p):
      match top:
        case True{}:
          match t:
            case Core.CCall{+f, +as}:
              Opt.sp.rw(p, dec, False{}, Opt.sp.redirect(Opt.sp.at(dec, f, as), Core.CCall{f, as}))
            case other:
              Opt.sp.rw(p, dec, False{}, other)
        case False{}:
          match t:
            case Core.CCall{f, as}:
              match as:
                case Nil{}:
                  Core.CCall{f, Nil{}}
                case Core.Arg{r, e} <> t2:
                  Core.Tm.push.call(Core.Arg{r, Opt.sp.rw(p, dec, True{}, e)}, Opt.sp.rw(p, dec, False{}, Core.CCall{f, t2}))
            case Core.CApp{f, as}:
              match as:
                case Nil{}:
                  Core.CApp{Opt.sp.rw(p, dec, True{}, f), Nil{}}
                case a <> t2:
                  Core.Tm.push(Opt.sp.rw(p, dec, True{}, a), Opt.sp.rw(p, dec, False{}, Core.CApp{f, t2}))
            case Core.CCtr{k, as}:
              match as:
                case Nil{}:
                  Core.CCtr{k, Nil{}}
                case a <> t2:
                  Core.Tm.push(Opt.sp.rw(p, dec, True{}, a), Opt.sp.rw(p, dec, False{}, Core.CCtr{k, t2}))
            case Core.CLam{pt, b}:
              Core.CLam{pt, Opt.sp.rw(p, dec, True{}, b)}
            case Core.CLet{pt, v, b}:
              Core.CLet{pt, Opt.sp.rw(p, dec, True{}, v), Opt.sp.rw(p, dec, True{}, b)}
            case Core.CMat{scrs, cases}:
              match scrs:
                case a <> t2:
                  Core.Tm.push(Opt.sp.rw(p, dec, True{}, a), Opt.sp.rw(p, dec, False{}, Core.CMat{t2, cases}))
                case Nil{}:
                  match cases:
                    case Nil{}:
                      Core.CMat{Nil{}, Nil{}}
                    case cs <> t2:
                      Core.Tm.push.case(Opt.sp.rw(p, dec, True{}, cs), Opt.sp.rw(p, dec, False{}, Core.CMat{Nil{}, t2}))
            case Core.CCse{ps, b}:
              Core.CCse{ps, Opt.sp.rw(p, dec, True{}, b)}
            case Core.CSuc{k, e}:
              Core.CSuc{k, Opt.sp.rw(p, dec, True{}, e)}
            case Core.COp{op, a, b}:
              Core.COp{op, Opt.sp.rw(p, dec, True{}, a), Opt.sp.rw(p, dec, True{}, b)}
            case Core.CAnn{e, ty}:
              Core.CAnn{Opt.sp.rw(p, dec, True{}, e), ty}
            case other:
              other

def Opt.calls.add(top: Bool, t: Core.Tm, acc: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match top:
    case True{}:
      t <> acc
    case False{}:
      acc

# The calls in t (each call node, onto acc).
def Opt.calls(t: Core.Tm, top: Bool, acc: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match t:
    case Core.CCall{+f, as}:
      match as:
        case Nil{}:
          Opt.calls.add(top, Core.CCall{f, Nil{}}, acc)
        case Core.Arg{+r, +e} <> +t2:
          Opt.calls(Core.CCall{f, t2}, False{}, Opt.calls(e, True{}, Opt.calls.add(top, Core.CCall{f, Core.Arg{r, e} <> t2}, acc)))
    case Core.CApp{f, as}:
      match as:
        case Nil{}:
          Opt.calls(f, True{}, acc)
        case a <> t2:
          Opt.calls(Core.CApp{f, t2}, False{}, Opt.calls(a, True{}, acc))
    case Core.CCtr{k, as}:
      match as:
        case Nil{}:
          acc
        case a <> t2:
          Opt.calls(Core.CCtr{k, t2}, False{}, Opt.calls(a, True{}, acc))
    case Core.CLam{pt, b}:
      Opt.calls(b, True{}, acc)
    case Core.CLet{pt, v, b}:
      Opt.calls(b, True{}, Opt.calls(v, True{}, acc))
    case Core.CMat{scrs, cases}:
      match scrs:
        case a <> t2:
          Opt.calls(Core.CMat{t2, cases}, False{}, Opt.calls(a, True{}, acc))
        case Nil{}:
          match cases:
            case Nil{}:
              acc
            case cs <> t2:
              Opt.calls(Core.CMat{Nil{}, t2}, False{}, Opt.calls(cs, True{}, acc))
    case Core.CCse{ps, b}:
      Opt.calls(b, True{}, acc)
    case Core.CSuc{k, e}:
      Opt.calls(e, True{}, acc)
    case Core.COp{op, a, b}:
      Opt.calls(b, True{}, Opt.calls(a, True{}, acc))
    case Core.CAnn{e, ty}:
      Opt.calls(e, True{}, acc)
    case other:
      acc

# The copies the calls ask for, but those named in seen.
def Opt.sp.pk(+f: String, k: OPk, acc: List<&2, OSp>) -> List<&2, OSp>:
  match k:
    case PkNo{}:
      acc
    case PkYes{name, i, a}:
      OSp{name, f, i, a} <> acc
    case PkFuse{name, j, g, p}:
      OSp{name, g, j, Core.CRef{p}} <> acc

def Opt.sp.picks(+dec: ODec, ts: List<&2, Core.Tm>) -> List<&2, OSp>:
  match ts:
    case Nil{}:
      Nil{}
    case t <> r:
      match t:
        case Core.CCall{+f, +as}:
          Opt.sp.pk(f, Opt.sp.at(dec, f, as), Opt.sp.picks(dec, r))
        case other:
          Opt.sp.picks(dec, r)

def Opt.sp.reqs(ss: List<&2, OSp>, +seen: Set(), +acc: List<&2, OSp>) -> List<&2, OSp>:
  match ss:
    case Nil{}:
      acc
    case OSp{+name, f, i, a} <> +r:
      Bool.pick(Unit -> List<&2, OSp>, Inl.has(seen, name), u => Opt.sp.reqs(r, seen, acc),
        u => Opt.sp.reqs(r, Set.add(seen, name), OSp{name, f, i, a} <> acc))(Unit{})

# A copy's parameters keep their relevance in their modes: it fills no
# law to take them from.
def Opt.sp.par(p: Core.Par) -> Core.Par:
  match p:
    case Core.Par{x, rel, +m, ty}:
      match rel:
        case Core.Era{}:
          Core.Par{x, Core.Era{}, 1, ty}
        case Core.Run{}:
          Core.Par{x, Core.Run{}, Bool.pick(U32, Bool.or(U32.is_eq(m, 1), U32.is_eq(m, 4)), 0, m), ty}

def Opt.sp.pars(ps: List<&2, Core.Par>) -> List<&2, Core.Par>:
  match ps:
    case Nil{}:
      Nil{}
    case p <> r:
      Opt.sp.par(p) <> Opt.sp.pars(r)

def Opt.nth.par(n: Nat, ps: List<&2, Core.Par>) -> String:
  match n ps:
    case k Nil{}:
      ""
    case 0n Core.Par{x, rel, m, ty} <> t:
      x
    case 1n+k Core.Par{x, rel, m, ty} <> t:
      Opt.nth.par(k, t)

def Opt.sp.make.def(+c: Map<&2, Core.Def>, +name: String, +i: Nat, a: Core.Tm, d: Core.Def) -> OD:
  match d:
    case Core.Def{+f, +ps, b, ret}:
      OCore{Core.Def{name, Opt.sp.pars(Opt.drop.par(i, ps)),
        Opt.go(Fuel.max(), OAll{}, Opt.go(Fuel.max(), OSub{Opt.nth.par(i, ps), Opt.strip(a), True{}},
          Opt.sp.rw(Fuel.max(), DSelf{f, i, name}, True{}, b))), ret}}

# The copy an OSp asks for.
def Opt.sp.make(+c: Map<&2, Core.Def>, s: OSp) -> OD:
  match s:
    case OSp{+name, +f, +i, a}:
      Opt.sp.make.def(c, name, i, a, Opt.get(c, f))

def Opt.sp.makes(+c: Map<&2, Core.Def>, ss: List<&2, OSp>) -> List<&2, OD>:
  match ss:
    case Nil{}:
      Nil{}
    case s <> r:
      Opt.sp.make(c, s) <> Opt.sp.makes(c, r)

def Opt.defs(ds: List<&2, OD>, m: Map<&2, Core.Def>) -> Map<&2, Core.Def>:
  match ds:
    case Nil{}:
      m
    case d <> t:
      match d:
        case OCore{+cd}:
          Opt.defs(t, Map.set(&2, Core.Def, m, Opt.dname(cd), cd))
        case OKeep{k}:
          Opt.defs(t, m)

def Opt.names(ds: List<&2, OD>, s: Set()) -> Set():
  match ds:
    case Nil{}:
      s
    case d <> t:
      match d:
        case OCore{cd}:
          Opt.names(t, Set.add(s, Opt.dname(cd)))
        case OKeep{k}:
          Opt.names(t, s)

def Opt.bodies.calls(ds: List<&2, OD>, acc: List<&2, Core.Tm>) -> List<&2, Core.Tm>:
  match ds:
    case Nil{}:
      acc
    case d <> t:
      match d:
        case OCore{Core.Def{n, ps, b, ret}}:
          Opt.bodies.calls(t, Opt.calls(b, True{}, acc))
        case OKeep{k}:
          Opt.bodies.calls(t, acc)

def Opt.sp.rws(+dec: ODec, ds: List<&2, OD>) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> t:
      match d:
        case OCore{Core.Def{n, ps, b, ret}}:
          OCore{Core.Def{n, ps, Opt.sp.rw(Fuel.max(), dec, True{}, b), ret}} <> Opt.sp.rws(dec, t)
        case OKeep{k}:
          OKeep{k} <> Opt.sp.rws(dec, t)

# Rounds of specialization: old are the defs done, new the ones whose
# calls this round sends to copies.
def Opt.sp.rounds(k: Nat, +old: List<&2, OD>, +new: List<&2, OD>) -> List<&2, OD>:
  match k:
    case 0n:
      List.append(&2, OD, old, new)
    case 1n+j:
      +c = Opt.defs(new, Opt.defs(old, Map.new(&2, Core.Def)))
      +made = Opt.sp.makes(c, Opt.sp.reqs(Opt.sp.picks(DCtx{c}, Opt.bodies.calls(new, Nil{})), Opt.names(new, Opt.names(old, Set.new())), Nil{}))
      +done = List.append(&2, OD, old, Opt.sp.rws(DCtx{c}, new))
      Bool.pick(Unit -> List<&2, OD>, List.is_empty(&2, OD, made), u => done, u => Opt.sp.rounds(j, done, made))(Unit{})

def Opt.spec(+flags: String, +ds: List<&2, OD>) -> List<&2, OD>:
  Bool.pick(Unit -> List<&2, OD>, Opt.on(flags, 112), u => Opt.sp.rounds(4n, Nil{}, ds), u => ds)(Unit{})

# Fusion
# ------
#
# A call g(.., p(as), ..) where g matches on that argument alone, and p
# has a result that is a constructor, calls a fused def instead (f in
# BEND_OPT): p's body with g around each of its results, g unfolded where
# the result is a constructor (so the match on it is known), and each
# g(.., p(bs), ..) that leaves made a call of the fused def. The list
# p built is never built. Each round fuses the calls the round before
# made; fused defs no call names are dropped at the end.
def Opt.fu.oarg(q: Core.Par, +s: String) -> Core.Arg:
  match q:
    case Core.Par{x, rel, m, ty}:
      match rel:
        case Core.Era{}:
          Core.Arg{Core.Era{}, Core.CBox{}}
        case Core.Run{}:
          Core.Arg{Core.Run{}, Core.CVar{x ++ s}}

def Opt.fu.oargs(ps: List<&2, Core.Par>, +s: String) -> List<&2, Core.Arg>:
  match ps:
    case Nil{}:
      Nil{}
    case q <> r:
      Opt.fu.oarg(q, s) <> Opt.fu.oargs(r, s)

def Opt.fu.opars(ps: List<&2, Core.Par>, +s: String) -> List<&2, Core.Par>:
  match ps:
    case Nil{}:
      Nil{}
    case Core.Par{x, rel, m, ty} <> r:
      Core.Par{x ++ s, rel, m, ty} <> Opt.fu.opars(r, s)

def Opt.fu.ins(n: Nat, as: List<&2, Core.Arg>, +a: Core.Arg) -> List<&2, Core.Arg>:
  match n as:
    case 0n bs:
      a <> bs
    case 1n+k Nil{}:
      a <> Nil{}
    case 1n+k b <> r:
      b <> Opt.fu.ins(k, r, a)

# g around a result t of p: unfolded when t is a constructor.
def Opt.fu.hole(+g: String, +dg: Core.Def, +j: Nat, +os: List<&2, Core.Arg>, +suf: String, t: Core.Tm) -> Core.Tm:
  match t:
    case Core.CCtr{+k, +xs}:
      Inl.go(Fuel.max(), Map.new(&2, Core.Def), IPlan{Inl.pars(dg), Opt.fu.ins(j, os, Core.Arg{Core.Run{}, Core.CCtr{k, xs}}), suf},
        Inl.ren(Inl.body(dg), suf))
    case other:
      Core.CCall{g, Opt.fu.ins(j, os, Core.Arg{Core.Run{}, other})}

def Opt.fu.tails(+g: String, +dg: Core.Def, +j: Nat, +os: List<&2, Core.Arg>, +suf: String, t: Core.Tm) -> Core.Tm:
  match t:
    case Core.CLet{pt, v, b}:
      Core.CLet{pt, v, Opt.fu.tails(g, dg, j, os, suf, b)}
    case Core.CAnn{e, ty}:
      Opt.fu.tails(g, dg, j, os, suf, e)
    case Core.CMat{scrs, cases}:
      match cases:
        case Nil{}:
          Core.CMat{scrs, Nil{}}
        case c <> t2:
          Core.Tm.push.case(Opt.fu.tails(g, dg, j, os, suf, c), Opt.fu.tails(g, dg, j, os, suf, Core.CMat{scrs, t2}))
    case Core.CCse{ps, b}:
      Core.CCse{ps, Opt.fu.tails(g, dg, j, os, suf, b)}
    case other:
      Opt.fu.hole(g, dg, j, os, suf, other)

def Opt.fu.ret(d: Core.Def) -> Core.Tm:
  match d:
    case Core.Def{name, ps, b, ret}:
      ret

def Opt.fu.make.def(+name: String, +g: String, +j: Nat, +p: String, +dg: Core.Def, dp: Core.Def) -> OD:
  match dp:
    case Core.Def{f, +ps, b, ret}:
      +gps = Opt.drop.par(j, Inl.pars(dg))
      +h = Opt.hash(name, 2166136261, 7)
      +body = Opt.fu.tails(g, dg, j, Opt.fu.oargs(gps, "%z" ++ h), "@" ++ h, b)
      OCore{Core.Def{name, Opt.sp.pars(List.append(&2, Core.Par, Opt.fu.opars(gps, "%z" ++ h), ps)),
        Opt.sp.rw(Fuel.max(), DFuSelf{g, j, p, Inl.pars.len(ps), name}, True{}, Opt.go(Fuel.max(), OAll{}, body)), Opt.fu.ret(dg)}}

def Opt.fu.refname(t: Core.Tm) -> String:
  match t:
    case Core.CRef{f}:
      f
    case other:
      ""

def Opt.fu.make(+c: Map<&2, Core.Def>, s: OSp) -> OD:
  match s:
    case OSp{+name, +g, +j, a}:
      +p = Opt.fu.refname(a)
      Opt.fu.make.def(name, g, j, p, Opt.get(c, g), Opt.get(c, p))

def Opt.fu.makes(+c: Map<&2, Core.Def>, ss: List<&2, OSp>) -> List<&2, OD>:
  match ss:
    case Nil{}:
      Nil{}
    case s <> r:
      Opt.fu.make(c, s) <> Opt.fu.makes(c, r)

def Opt.fu.rounds(k: Nat, +ds: List<&2, OD>) -> List<&2, OD>:
  match k:
    case 0n:
      ds
    case 1n+j:
      +c = Opt.defs(ds, Map.new(&2, Core.Def))
      +made = Opt.fu.makes(c, Opt.sp.reqs(Opt.sp.picks(DFuCtx{c}, Opt.bodies.calls(ds, Nil{})), Opt.names(ds, Set.new()), Nil{}))
      Bool.pick(Unit -> List<&2, OD>, List.is_empty(&2, OD, made), u => ds,
        u => Opt.fu.rounds(j, List.append(&2, OD, Opt.sp.rws(DFuCtx{c}, ds), made)))(Unit{})

# The names the bodies of ds call or refer to.
def Opt.used(ds: List<&2, OD>, +acc: List<&2, String>) -> List<&2, String>:
  match ds:
    case Nil{}:
      acc
    case d <> t:
      match d:
        case OCore{Core.Def{n, ps, b, ret}}:
          Opt.used(t, Inl.names(b, 3, acc))
        case OKeep{k}:
          Opt.used(t, acc)

# ds without the fused defs no def names.
def Opt.drop.dead(ds: List<&2, OD>, +used: Set()) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> +t:
      match d:
        case OCore{+cd}:
          +n = Opt.dname(cd)
          Bool.pick(Unit -> List<&2, OD>, Bool.and(String.contains(n, "%f"), Bool.not(Inl.has(used, n))),
            u => Opt.drop.dead(t, used), u => OCore{cd} <> Opt.drop.dead(t, used))(Unit{})
        case OKeep{k}:
          OKeep{k} <> Opt.drop.dead(t, used)

def Opt.dead(k: Nat, +ds: List<&2, OD>) -> List<&2, OD>:
  match k:
    case 0n:
      ds
    case 1n+j:
      Opt.dead(j, Opt.drop.dead(ds, Set.from_list(Opt.used(ds, Nil{}))))

def Opt.fuse(+flags: String, +ds: List<&2, OD>) -> List<&2, OD>:
  Bool.pick(Unit -> List<&2, OD>, Opt.on(flags, 102), u => Opt.dead(3n, Opt.fu.rounds(4n, ds)), u => ds)(Unit{})

# The last step: applications of names made calls.
def Opt.fix(+c: Map<&2, Core.Def>, d: OD) -> OD:
  match d:
    case OCore{Core.Def{n, ps, b, ret}}:
      OCore{Core.Def{n, ps, Opt.refs(c, b, True{}), ret}}
    case OKeep{k}:
      OKeep{k}

def Opt.fixes(+c: Map<&2, Core.Def>, ds: List<&2, OD>) -> List<&2, OD>:
  match ds:
    case Nil{}:
      Nil{}
    case d <> r:
      Opt.fix(c, d) <> Opt.fixes(c, r)

def Opt.finish(+ds: List<&2, OD>) -> List<&2, OD>:
  Opt.fixes(Opt.defs(ds, Map.new(&2, Core.Def)), ds)

# The program through the core IR: each def lowered, erased, optimized
# (see Opt), and raised; a type-level def (a Type, Data, Quant or Kind)
# keeps its body, which the printers unfold.
def Lo.program(+flags: String, +ds: List<&2, Decl>) -> List<&2, Decl>:
  +g = G.new(ds)
  +ods = Opt.lowers(g, Lo.masks(g, ds, Map.new(&2, List<&2, Bool>)), ds)
  +rank = Opt.rank(ods, 0, Map.new(&2, U32))
  Opt.raises(Opt.finish(Opt.resub(flags, Opt.fuse(flags, Opt.spec(flags, Opt.simps(flags, Opt.inls(Opt.ctx(flags, False{}, Inl.names.defs(ds, Set.new()), rank, ods, Map.new(&2, Core.Def)), Opt.mon(Opt.ctx(flags, True{}, Inl.names.defs(ds, Set.new()), rank, ods, Map.new(&2, Core.Def)), ods))))))))

# Flat results (see Gen.def.unb): "%r:name" in the dps table holds a def's
# result arity. A def's result is flat when its type has one constructor
# of two to eight fields, and the def is no destination-passing one and
# has no parallel let (its sequential clone returns a node).
def Unb.sret.ty(d: Decl) -> Nat:
  match d:
    case DType{n, ps, cs}:
      match cs:
        case Ctor{k, +fs} <> Nil{}:
          Bool.pick(Nat, Unb.fits(fs), List.length(&2, Field, fs), 0n)
        case other:
          0n
    case other:
      0n

def Unb.sret.head(+g: G, +t: String) -> Nat:
  Unb.sret.ty(G.body(g, "%" ++ Bool.pick(String, Str.eq(t, "&"), "Sigma", t)))

def Unb.sret.def(+g: G, +name: String, +body: Core.Expr, +ret: Core.Expr) -> Nat:
  Bool.pick(Nat, Bool.or(Bool.or(Expr.has_par(body), Bool.not(String.is_empty(DGrp.id(G.dps(g, name))))),
    Bool.or(G.is_native(name), Str.eq(name, "main"))), 0n, Unb.sret.head(g, Ty.head(ret)))

def Unb.sret.put(k: Nat, +name: String, m: Map<&2, DGrp>) -> Map<&2, DGrp>:
  match k:
    case 0n:
      m
    case 1n+q:
      Map.set(&2, DGrp, m, "%r:" ++ name, DGrp{"", U32.from_nat(1n+q)})

def Unb.sret.all(+g: G, ds: List<&2, Decl>, m: Map<&2, DGrp>) -> Map<&2, DGrp>:
  match ds:
    case Nil{}:
      m
    case DDef{+name, ps, +body, +ret} <> t:
      Unb.sret.all(g, t, Unb.sret.put(Unb.sret.def(g, name, body, ret), name, m))
    case d <> t:
      Unb.sret.all(g, t, m)

def G.dps.map(g: G) -> Map<&2, DGrp>:
  G{ctors, defs, bodies, dps} = g
  dps

def Unb.sret(on: Bool, +ds: List<&2, Decl>, +g: G) -> G:
  match on:
    case True{}:
      G.with_dps(g, Unb.sret.all(g, ds, G.dps.map(g)))
    case False{}:
      g

def Gen.program.fin(+g: G, cids: String, r: String & St) -> COut:
  (entry, st) = r
  St{n, protos, code, refs, errs, memo, +effs} = st
  COut{cids ++ "#define BEND_NATIVE_MAP_BIT 1\n#define BEND_NATIVE_STR 1\n#define BEND_NATIVE_MAP 1\n#ifdef BEND_RT_SPLIT\n#include \"bendrt_split.h\"\n#else\n#include \"bendrt.h\"\n#endif\n\n", Gen.dedup(List.reverse(&2, String, Gen.effs.files(effs)), Nil{}),
    Doc.flat(Doc.list([protos, DStr{"\n"}, code, DStr{Gen.gpu.tail(g, Gen.dedup(Gen.effs.tagged(effs, "%gpu\t"), Nil{}),
    Gen.dedup(Gen.effs.tagged(effs, "%clo\t"), Nil{}))},
    DStr{"\n" ++ entry}])), errs}

def Gen.rc.main(+g: G) -> String:
  Bool.pick(String, Gen.rc(g), " bend_rc_req = 1;", "")

def Gen.entry.ty(+g: G, +ret: Core.Expr, io: Bool) -> Gen(String):
  match io:
    case True{}:
      Gen.pure(String,
        "int main(int argc, char **argv) {" ++ Gen.ctors.call() ++ Gen.rc.main(g) ++ " return bend_run(argc, argv, F_main); }\n")
    case False{}:
      do Gen<String>:
        p : String <- Gen.printer(g, ret)
        return "int main(int argc, char **argv) {" ++ Gen.ctors.call() ++ Gen.rc.main(g) ++
          " return bend_run_value(argc, argv, F_main, " ++ p ++ "); }\n"

def Gen.entry.ret(+g: G, +ret: Core.Expr) -> Gen(String):
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

def Gen.program(+ds0: List<&2, Decl>, free: Bool, par: Bool, +opt: String, +unb: Bool, +rc: Bool) -> COut:
  +ds = Unb.program(unb, Unb.program(unb, Nest.program(unb, Par.auto(par, Lo.program(opt, Arrw.decls(Pick.decls(ds0)))))))
  +g = Unb.sret(unb, ds, Dps.build(G.new(ds), ds, free, rc))
  Gen.program.fin(g, Gen.cids(g, ds, 0),
    Gen.program.m(g)(St{0, DNil{}, DNil{}, Nil{}, Nil{}, Nil{}, Nil{}}))

# Native code generation
# ======================
#
# bendc --native writes a program's code as AArch64 machine code, with the
# assembler and object writer of asm.bend: no C compiler sees it. It starts
# from the same lowered defs as the C generator (Lo.program), and keeps the
# runtime's value representation (see "Runtime" in the README) and the
# platform's calling convention (AAPCS64), so the code calls the runtime
# (build/bendrt.o, and rt/native.c's names for its inline natives) as C does.
#
# Every value lives in a slot of the function's frame, an expression leaves
# its value in x0, and the operands of a call are loaded from their slots
# into x0..x7 just before it. The first 10 slots are the callee-saved
# registers x19..x28 (see Registers); the rest are [sp + 8 i]. A def with at
# most 8 kept parameters takes them in x0..x7; a wider one takes x0, the
# address of its arguments in a row. A tail call to itself moves the new
# arguments over the parameters and jumps back; one to another narrow def
# pops the frame and branches. As the C backend does, matches free the nodes
# they open (bend_take, bend_share), parallel lets fork on the runtime's
# pool (par_fork, par_join; a seq def gets an S_ clone), and a def of a
# destination-passing group stores its result through dst (N.def.dst).
# Nested F32 operations compute in FP registers (Float trees), and a loop's
# F32 parameters stay in them (twins). !-calls run on the CPU.

# An operand: a frame slot or a constant.
type NO is Data:
  NOS{s: U32}
  NOK{k: U32}

type NB is Data:
  NB{name: String, o: NO}

def NEnv() -> Data:
  List<&2, NB>

def NEnv.find(env: NEnv(), +x: String) -> Maybe<&2, NO>:
  match env:
    case Nil{}:
      None{}
    case NB{+n, o} <> t:
      Bool.pick(Unit -> Maybe<&2, NO>, String.eq(n, x), u => Some{o}, u => NEnv.find(t, x))(Unit{})

def NEnv.has(+env: NEnv(), +x: String) -> Bool:
  Maybe.is_some(&2, NO, NEnv.find(env, x))

# Where a statement's value goes: returned, or stored in a slot, then a jump
# to the join label, or stored through the address in slot d (in a D_
# function of destination-passing group id).
type NT is Data:
  NTRet{}
  NTSet{s: U32, join: String}
  NTDst{d: U32, id: String}

# The def being generated: its name, parameter mask and the label after its
# prologue (a tail call to itself jumps there).
type NSelf is Data:
  NSelf{name: String, mask: List<&2, Bool>, top: String}

def NSelf.none() -> NSelf:
  NSelf{"", Nil{}, ""}

def N.self.name(s: NSelf) -> String:
  NSelf{sn, mask, top} = s
  sn

# The generator's state: a counter for fresh names, the current frame's next
# slot and its most, the finished functions, the defs referenced since the
# last def, errors, the data slots used (string literal caches), the literal
# bytes (after the code), printers made, effect sources and effect ids.
type NSt is Data:
  NSt{n: U32, slot: U32, max: U32, out: As.Code, refs: List<&2, String>, errs: List<&2, String>,
    data: U32, lits: As.Code, memo: List<&2, Bind>, effs: List<&2, String>, eids: Map<&2, U32>}

def NG(-A: Type) -> Type:
  NSt -> A & NSt

def NG.go(-A: Type, -B: Type, r: A & NSt, f: A -> NG(B)) -> B & NSt:
  (a, st) = r
  f(a, st)

def NG.bind(-A: Type, -B: Type, m: NG(A), f: A -> NG(B)) -> NG(B):
  st => NG.go(A, B, m(st), f)

def NG.pure(-A: Type, x: A) -> NG(A):
  st => (x, st)

def N.fresh.go(st: NSt) -> U32 & NSt:
  NSt{+n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (n, NSt{U32.inc(n), slot, max, out, refs, errs, data, lits, memo, effs, eids})

def N.fresh() -> NG(U32):
  st => N.fresh.go(st)

# A fresh local label.
def N.label() -> NG(String):
  do NG<String>:
    +k : U32 <- N.fresh()
    return ".L" ++ U32.show(k)

def N.slots.go(+k: U32, st: NSt) -> U32 & NSt:
  NSt{n, +slot, +max, out, refs, errs, data, lits, memo, effs, eids} = st
  +top = (slot + k : U32)
  (slot, NSt{n, top, U32.max(max, top), out, refs, errs, data, lits, memo, effs, eids})

# k new slots of the frame: the first one's index.
def N.slots(+k: U32) -> NG(U32):
  st => N.slots.go(k, st)

def N.mark.go(st: NSt) -> U32 & NSt:
  NSt{n, +slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (slot, NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids})

def N.mark() -> NG(U32):
  st => N.mark.go(st)

def N.release.go(+s: U32, st: NSt) -> Unit & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (Unit{}, NSt{n, s, max, out, refs, errs, data, lits, memo, effs, eids})

# Frees the slots from s up (the temporaries of an expression, a case's).
def N.release(+s: U32) -> NG(Unit):
  st => N.release.go(s, st)

def N.enter.go(st: NSt) -> (U32 & U32) & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  ((slot, max), NSt{n, 0, 0, out, refs, errs, data, lits, memo, effs, eids})

# A new frame (a lambda's inside a def's): the old one's counts.
def N.enter() -> NG(U32 & U32):
  st => N.enter.go(st)

def N.leave.go(saved: U32 & U32, st: NSt) -> U32 & NSt:
  (s0, m0) = saved
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (max, NSt{n, s0, m0, out, refs, errs, data, lits, memo, effs, eids})

# Back to the frame before: the slots the inner one used.
def N.leave(saved: U32 & U32) -> NG(U32):
  st => N.leave.go(saved, st)

def N.emit.go(c: As.Code, st: NSt) -> Unit & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (Unit{}, NSt{n, slot, max, As.CCat{out, c}, refs, errs, data, lits, memo, effs, eids})

# Appends a finished function.
def N.emit(c: As.Code) -> NG(Unit):
  st => N.emit.go(c, st)

def N.ref.go(name: String, st: NSt) -> Unit & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (Unit{}, NSt{n, slot, max, out, name <> refs, errs, data, lits, memo, effs, eids})

def N.ref(name: String) -> NG(Unit):
  st => N.ref.go(name, st)

def N.take_refs.go(st: NSt) -> List<&2, String> & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (refs, NSt{n, slot, max, out, Nil{}, errs, data, lits, memo, effs, eids})

def N.take_refs() -> NG(List<&2, String>):
  st => N.take_refs.go(st)

def N.error.go(msg: String, st: NSt) -> Unit & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (Unit{}, NSt{n, slot, max, out, refs, ("native: " ++ msg) <> errs, data, lits, memo, effs, eids})

def N.error(msg: String) -> NG(Unit):
  st => N.error.go(msg, st)

def N.dslot.go(st: NSt) -> U32 & NSt:
  NSt{n, slot, max, out, refs, errs, +data, lits, memo, effs, eids} = st
  (data, NSt{n, slot, max, out, refs, errs, U32.inc(data), lits, memo, effs, eids})

# A new data slot (a literal's cache).
def N.dslot() -> NG(U32):
  st => N.dslot.go(st)

def N.lit.go(+l: String, s: String, st: NSt) -> Unit & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (Unit{}, NSt{n, slot, max, out, refs, errs, data,
    As.CCat{lits, As.CCat{As.COne{As.ILab{l}}, As.Code.ws(As.cstr(s))}}, memo, effs, eids})

def N.lit(+l: String, s: String) -> NG(Unit):
  st => N.lit.go(l, s, st)

# The label of a NUL-terminated copy of s's UTF-8 bytes (after the code).
def N.cstr(s: String) -> NG(String):
  do NG<String>:
    +k : U32 <- N.fresh()
    +l : String <- NG.pure(String, ".C" ++ U32.show(k))
    N.lit(l, s)
    return l

def N.memo.find.go(+k: String, st: NSt) -> Maybe<&2, String> & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, +memo, effs, eids} = st
  (Env.find(memo, k), NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids})

def N.memo.find(+k: String) -> NG(Maybe<&2, String>):
  st => N.memo.find.go(k, st)

def N.memo.add.go(b: Bind, st: NSt) -> Unit & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (Unit{}, NSt{n, slot, max, out, refs, errs, data, lits, b <> memo, effs, eids})

def N.memo.add(b: Bind) -> NG(Unit):
  st => N.memo.add.go(b, st)

def N.effs.go(ims: List<&2, String>, st: NSt) -> Unit & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids} = st
  (Unit{}, NSt{n, slot, max, out, refs, errs, data, lits, memo, List.append(&2, String, Gen.effs.c(ims), effs), eids})

# Records the C files an effect imports (compiled apart: see Cc.link).
def N.effs(ims: List<&2, String>) -> NG(Unit):
  st => N.effs.go(ims, st)

def N.eid.go(+name: String, st: NSt) -> U32 & NSt:
  NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, +eids} = st
  (Pair.snd(Map<&2, U32>, U32, Map.get(U32, 0, eids, name)), NSt{n, slot, max, out, refs, errs, data, lits, memo, effs, eids})

# An effect's id, as Gen.cids numbers them: (3 << 16) | its index.
def N.eid(+name: String) -> NG(U32):
  st => N.eid.go(name, st)

def N.eids(ds: List<&2, Decl>, +i: U32, m: Map<&2, U32>) -> Map<&2, U32>:
  match ds:
    case Nil{}:
      m
    case DEff{+n, ps, ims} <> t:
      N.eids(t, U32.inc(i), Map.set(&2, U32, m, n, (196608 .|. i : U32)))
    case d <> t:
      N.eids(t, i, m)

# Instructions
# ------------

def N.w(+w: U32) -> As.Code:
  As.Code.w(w)

def N.ws(ws: List<&2, U32>) -> As.Code:
  As.Code.ws(ws)

def N.cat(xs: List<&2, As.Code>) -> As.Code:
  As.Code.list(xs)

def N.one(i: As.Ins) -> As.Code:
  As.COne{i}

def N.k(+r: U32, +k: U32) -> As.Code:
  N.ws(As.mov32(r, k))

# rd = rn + k (k below 2^24).
def N.addk(+rd: U32, +rn: U32, +k: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_lt(k, 4096), N.w(As.addi(rd, rn, k)),
    N.ws([As.addh(rd, rn, (k >> 12n : U32)), As.addi(rd, rd, (k .&. 4095 : U32))]))

# ldr/str r at sp + off (x17 holds the high part past 32 KiB).
def N.ldx(+r: U32, +off: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_lt(off, 32768), N.w(As.ldr(r, 31, off)),
    N.ws([As.addh(17, 31, (off >> 12n : U32)), As.ldr(r, 17, (off .&. 4095 : U32))]))

def N.stx(+r: U32, +off: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_lt(off, 32768), N.w(As.str(r, 31, off)),
    N.ws([As.addh(17, 31, (off >> 12n : U32)), As.str(r, 17, (off .&. 4095 : U32))]))

# Registers
# ---------
#
# The first N.nregs() slots of a frame live in the callee-saved registers
# x19, x20, ...: slots are handed out in order and freed after the
# expression or case that took them (N.mark, N.release), so the low ones hold
# a def's parameters and the variables that live longest, and a call keeps
# them without a store. A function saves the ones it uses under its frame
# pointer (N.func); its returns and tail calls restore them (N.epilogue and
# N.pop stand for the code that does, filled in by N.fix once the frame's
# size is known). The collector scans registers as it scans the stack, so a
# value in one stays live.
def N.nregs() -> U32:
  10

def N.sreg(+s: U32) -> U32:
  (s + 19 : U32)

def N.mov(+rd: U32, +rm: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_eq(rd, rm), As.CNil{}, N.w(As.mov(rd, rm)))

def N.ld(+r: U32, +s: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_lt(s, N.nregs()), N.mov(r, N.sreg(s)), N.ldx(r, (s * 8 : U32)))

def N.st(+r: U32, +s: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_lt(s, N.nregs()), N.mov(N.sreg(s), r), N.stx(r, (s * 8 : U32)))

# An operand into register r.
def N.lo(o: NO, +r: U32) -> As.Code:
  match o:
    case NOS{+s}:
      N.ld(r, s)
    case NOK{+k}:
      N.k(r, k)

# Operands into registers r, r + 1, ...
def N.lregs(os: List<&2, NO>, +r: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case o <> t:
      As.CCat{N.lo(o, r), N.lregs(t, U32.inc(r))}

# The position of the last operand computed into a slot of its own (from
# base up), or 4294967295 when there is none.
def N.lastc(os: List<&2, NO>, +base: U32, +i: U32, +j: U32) -> U32:
  match os:
    case Nil{}:
      j
    case o <> t:
      match o:
        case NOS{+s}:
          N.lastc(t, base, U32.inc(i), Bool.pick(U32, U32.is_ge(s, base), i, j))
        case NOK{k}:
          N.lastc(t, base, U32.inc(i), j)

# Operands into registers r, r + 1, ..., but not the one for register j.
def N.lregs.skip(os: List<&2, NO>, +r: U32, +j: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case o <> t:
      As.CCat{Bool.pick(As.Code, U32.is_eq(r, j), As.CNil{}, N.lo(o, r)), N.lregs.skip(t, U32.inc(r), j)}

# Operands evaluated from slot base up into x0, x1, ...: the last one
# computed first, right after the store that ends its code, so that the
# peephole (As.peep) turns its load into a move.
def N.lregs.b(+os: List<&2, NO>, +base: U32) -> As.Code:
  +j = N.lastc(os, base, 0, 4294967295)
  Bool.pick(As.Code, U32.is_eq(j, 4294967295), N.lregs(os, 0),
    As.CCat{N.lo(Maybe.default(&2, NO, List.get(&2, NO, os, U32.to_nat(j)), NOK{0}), j), N.lregs.skip(os, 0, j)})

# The frame of a function whose slots number max, in bytes (a multiple of 16).
def N.frame(+max: U32) -> U32:
  (((max * 8 : U32) + 15 : U32) .&. 4294967280 : U32)

# The register pairs a frame of max slots saves.
def N.pairs(+max: U32) -> U32:
  (U32.inc(U32.min(max, N.nregs())) >> 1n : U32)

# stp or ldp of the pairs x19.. from i up, at x29 - 16 (i + 1).
def N.saves(k: Nat, +i: U32, +ld: Bool) -> List<&2, U32>:
  match k:
    case 0n:
      Nil{}
    case 1n+j:
      +off = (0 - (16 * U32.inc(i) : U32) : U32)
      +r = N.sreg((2 * i : U32))
      Bool.pick(U32, ld, As.ldpo(r, U32.inc(r), 29, off), As.stpo(r, U32.inc(r), 29, off)) <>
        N.saves(j, U32.inc(i), ld)

# stp or ldp of d8..d15, below the np pairs of x19...
def N.fsaves(k: Nat, +j: U32, +np: U32, +ld: Bool) -> List<&2, U32>:
  match k:
    case 0n:
      Nil{}
    case 1n+q:
      +off = (0 - (16 * U32.inc((np + j : U32)) : U32) : U32)
      +r = (8 + (2 * j : U32) : U32)
      Bool.pick(U32, ld, As.ldpd(r, U32.inc(r), 29, off), As.stpd(r, U32.inc(r), 29, off)) <>
        N.fsaves(q, U32.inc(j), np, ld)

def N.fpairs(+fp: Bool) -> U32:
  Bool.pick(U32, fp, 4, 0)

def N.prologue.fp(+max: U32, +np: U32, +fp: Bool) -> As.Code:
  +f = (N.frame(max) + (16 * (np + N.fpairs(fp) : U32) : U32) : U32)
  N.cat([N.ws([As.push_fp(), As.set_fp()]),
    Bool.pick(As.Code, U32.is_lt(f, 4096), N.w(As.subi(31, 31, f)),
      N.ws([As.subh(31, 31, (f >> 12n : U32)), As.subi(31, 31, (f .&. 4095 : U32))])),
    N.ws(N.saves(U32.to_nat(np), 0, False{})), N.ws(N.fsaves(U32.to_nat(N.fpairs(fp)), 0, np, False{}))])

def N.prologue(+max: U32, +np: U32) -> As.Code:
  N.prologue.fp(max, np, False{})

# Placeholders for the restores, then the frame popped (and a return).
def N.pop.w() -> U32:
  4294901762

def N.epi.w() -> U32:
  4294901761

def N.pop() -> As.Code:
  N.w(N.pop.w())

def N.epilogue() -> As.Code:
  N.w(N.epi.w())

# The placeholders filled in, for a frame saving np pairs.
def N.fix.fp(c: As.Code, +np: U32, +fp: Bool) -> As.Code:
  +rs = List.append(&2, U32, N.saves(U32.to_nat(np), 0, True{}), N.fsaves(U32.to_nat(N.fpairs(fp)), 0, np, True{}))
  As.Code.subst(c, N.epi.w(), N.ws(List.append(&2, U32, rs, [As.sp_fp(), As.pop_fp(), As.ret()])),
    N.pop.w(), N.ws(List.append(&2, U32, rs, [As.sp_fp(), As.pop_fp()])))

def N.fix(c: As.Code, +np: U32) -> As.Code:
  N.fix.fp(c, np, False{})

# Register allocation
# -------------------
#
# The generator hands out slots 0..9 (x19..x28) in order and frees them
# after the expression or case that took them, so a register holds many
# values in turn, and a function would save as many as it used at its
# deepest. N.ra, over a function's code before its prologue, finds where
# each of them is live (a backward pass over the code, again until the
# labels' sets stay the same) and which are live across a call, then gives
# each one register for the whole function: one of x11..x15 (which the
# generated code does not use otherwise) when it is never live across a call,
# else the first of x19.. that no register live with it has. A function then
# saves only the callee-saved registers that keep a value across a call.
# Code it cannot follow (an encoding As.du does not know that names one of
# these registers, a branch by offset back or far) keeps its registers.

# x19..x28, and x11..x15.
def N.ra.slots() -> U32:
  536346624

def N.ra.free() -> U32:
  63488

# The pass's state: each label's live set, whether one changed, the
# registers live where each of x19..x28 is written (at i), the ones live
# across a call, and the set of the label last looked up.
type NRa is Data:
  NRa{m: Map<&2, U32>, ch: Bool, ig: List<&2, U32>, cross: U32, v: U32}

def N.ra.set(+l: String, +out: U32, r: Map<&2, U32> & U32, ch: Bool, ig: List<&2, U32>, cross: U32) -> NRa:
  (m, +old) = r
  NRa{Map.set(&2, U32, m, l, out), Bool.or(ch, U32.is_ne(old, out)), ig, cross, 0}

def N.ra.label(+l: String, +out: U32, st: NRa) -> NRa:
  NRa{m, ch, ig, cross, v} = st
  N.ra.set(l, out, Map.get(U32, 0, m, l), ch, ig, cross)

def N.ra.got(r: Map<&2, U32> & U32, ch: Bool, ig: List<&2, U32>, cross: U32) -> NRa:
  (m, v) = r
  NRa{m, ch, ig, cross, v}

# A branch to label l (kind 2 or 3): its set, in v.
def N.ra.look(+kind: U32, +l: String, st: NRa) -> NRa:
  NRa{+m, +ch, +ig, +cross, v} = st
  Bool.pick(Unit -> NRa, U32.is_lt((kind - 2 : U32), 2),
    z => N.ra.got(Map.get(U32, 0, m, l), ch, ig, cross),
    z => NRa{m, ch, ig, cross, 0})(Unit{})

def N.ra.v(+st: NRa) -> U32:
  NRa{m, ch, ig, cross, v} = st
  v

def N.ra.ch(+st: NRa) -> Bool:
  NRa{m, ch, ig, cross, v} = st
  ch

def N.ra.igs(+st: NRa) -> List<&2, U32>:
  NRa{m, ch, ig, cross, v} = st
  ig

def N.ra.cross(+st: NRa) -> U32:
  NRa{m, ch, ig, cross, v} = st
  cross

def N.ra.m(st: NRa) -> Map<&2, U32>:
  NRa{m, ch, ig, cross, v} = st
  m

# The registers live after an instruction of kind k: out after it in
# order, lab at its label, raw at its offset.
def N.ra.succ(+k: U32, +out: U32, +lab: U32, +raw: U32) -> U32:
  Bool.pick(U32, U32.is_eq(k, 2), (out .|. lab : U32),
  Bool.pick(U32, U32.is_eq(k, 3), lab,
  Bool.pick(U32, U32.is_eq(k, 4), 0,
  Bool.pick(U32, U32.is_eq(k, 5), (out .|. raw : U32),
  Bool.pick(U32, U32.is_eq(k, 6), raw, out)))))

# The live set off words ahead (win: the next words', nearest first).
def N.ra.at(win: List<&2, U32>, +off: U32) -> U32:
  Maybe.default(&2, U32, List.get(&2, U32, win, U32.to_nat(((off - 1 : U32) .&. 15 : U32))), 0)

def N.ra.win(+x: U32, +n: U32, +win: List<&2, U32>) -> List<&2, U32>:
  Bool.pick(List<&2, U32>, U32.is_zero(n), win,
    List.take(&2, U32, x <> Bool.pick(List<&2, U32>, U32.is_eq(n, 2), x <> win, win), 8n))

# s added to the sets of the registers written (d), from x(19 + r).
def N.ra.ig(ig: List<&2, U32>, +d: U32, +s: U32, +r: U32) -> List<&2, U32>:
  match ig:
    case Nil{}:
      Nil{}
    case +x <> t:
      +b = As.reg.bit((19 + r : U32))
      Bool.pick(U32, U32.is_zero((d .&. b : U32)), x, (x .|. (s .&. (b .^. 4294967295 : U32) : U32) : U32)) <>
        N.ra.ig(t, d, s, U32.inc(r))

def N.ra.note(+d: U32, +s: U32, call: Bool, st: NRa) -> NRa:
  NRa{m, ch, ig, +cross, v} = st
  NRa{m, ch, N.ra.ig(ig, (d .&. N.ra.slots() : U32), s, 0), Bool.pick(U32, call, (cross .|. s : U32), cross), v}

# One backward pass over the code (reversed): out, the registers live after
# the instruction.
def N.ra.pass(us: List<&2, As.Use>, +tr: U32, +out: U32, +win: List<&2, U32>, +st: NRa) -> NRa:
  match us:
    case Nil{}:
      st
    case As.Use{+d, +u, +kind, +l, +off, +n} <> +t:
      +st1 = N.ra.look(kind, l, st)
      +s = N.ra.succ(kind, out, N.ra.v(st1), N.ra.at(win, off))
      +live = (((s .&. (d .^. 4294967295 : U32) : U32) .|. u : U32) .&. tr : U32)
      Bool.pick(Unit -> NRa, U32.is_eq(kind, 8),
        z => N.ra.pass(t, tr, out, win, N.ra.label(l, out, st)),
        z => N.ra.pass(t, tr, live, N.ra.win(live, n, win), N.ra.note(d, s, U32.is_eq(kind, 1), st1)))(Unit{})

def N.ra.zeros(k: Nat) -> List<&2, U32>:
  match k:
    case 0n:
      Nil{}
    case 1n+j:
      0 <> N.ra.zeros(j)

def N.ra.reset(st: NRa) -> NRa:
  NRa{m, ch, ig, cross, v} = st
  NRa{m, False{}, N.ra.zeros(10n), 0, 0}

# Passes until no label's set changes (None past k of them).
def N.ra.live(k: Nat, +tr: U32, +us: List<&2, As.Use>, st: NRa) -> Maybe<&2, NRa>:
  match k:
    case 0n:
      None{}
    case 1n+j:
      +r = N.ra.pass(us, tr, 0, Nil{}, N.ra.reset(st))
      Bool.pick(Unit -> Maybe<&2, NRa>, N.ra.ch(r), z => N.ra.live(j, tr, us, r), z => Some{r})(Unit{})

# The instructions as uses, reversed; whether one cannot be followed; the
# registers named.
def N.ra.uses(ins: List<&2, As.Ins>, acc: List<&2, As.Use>) -> List<&2, As.Use>:
  match ins:
    case Nil{}:
      acc
    case i <> t:
      N.ra.uses(t, As.use(i, (N.ra.slots() .|. N.ra.free() : U32), N.epi.w()) <> acc)

def N.ra.bad(us: List<&2, As.Use>) -> Bool:
  match us:
    case Nil{}:
      False{}
    case As.Use{d, u, +kind, l, off, n} <> t:
      Bool.or(U32.is_eq(kind, 7), N.ra.bad(t))

def N.ra.named(us: List<&2, As.Use>, +acc: U32) -> U32:
  match us:
    case Nil{}:
      acc
    case As.Use{d, u, kind, l, off, n} <> t:
      N.ra.named(t, (acc .|. (d .|. u : U32) : U32))

# The colors that registers before x(19 + i) live with it have (cs: theirs
# in order, from x(19 + j); mine: the set live where it is written).
def N.ra.nb(cs: List<&2, U32>, +ig: List<&2, U32>, +i: U32, +j: U32, +mine: U32) -> U32:
  match cs:
    case Nil{}:
      0
    case +c <> t:
      +ij = Bool.or(As.du.bit(mine, As.reg.bit((19 + j : U32))),
        As.du.bit(Maybe.default(&2, U32, List.get(&2, U32, ig, U32.to_nat(j)), 0), As.reg.bit((19 + i : U32))))
      (As.du.if(ij, As.reg.bit(c)) .|. N.ra.nb(t, ig, i, U32.inc(j), mine) : U32)

# The first of k registers from r not in bad (99: none).
def N.ra.first(k: Nat, +r: U32, +bad: U32) -> U32:
  match k:
    case 0n:
      99
    case 1n+j:
      Bool.pick(U32, As.du.bit(bad, As.reg.bit(r)), N.ra.first(j, U32.inc(r), bad), r)

def N.ra.pick(+caller: Bool, +bad: U32) -> U32:
  +c = N.ra.first(5n, 11, bad)
  Bool.pick(U32, Bool.and(caller, U32.is_lt(c, 99)), c, N.ra.first(10n, 19, bad))

# The registers for x19..x28 in order (one not named keeps its own).
def N.ra.colors(k: Nat, +i: U32, +ig: List<&2, U32>, +cross: U32, +named: U32, +free: Bool, +cs: List<&2, U32>) ->
  List<&2, U32>:
  match k:
    case 0n:
      cs
    case 1n+j:
      +b = As.reg.bit((19 + i : U32))
      +mine = Maybe.default(&2, U32, List.get(&2, U32, ig, U32.to_nat(i)), 0)
      +c = Bool.pick(U32, As.du.bit(named, b),
        N.ra.pick(Bool.and(free, Bool.not(As.du.bit(cross, b))), N.ra.nb(cs, ig, i, 0, mine)), (19 + i : U32))
      N.ra.colors(j, U32.inc(i), ig, cross, named, free, List.append(&2, U32, cs, [c]))

# How many of x19.. the colors of the named registers reach.
def N.ra.top(cs: List<&2, U32>, +i: U32, +named: U32, +acc: U32) -> U32:
  match cs:
    case Nil{}:
      acc
    case +c <> t:
      N.ra.top(t, U32.inc(i), named, Bool.pick(U32,
        Bool.and(As.du.bit(named, As.reg.bit((19 + i : U32))), U32.is_ge(c, 19)), U32.max(acc, (c - 18 : U32)), acc))

def N.ra.ren(ins: List<&2, As.Ins>, +cs: List<&2, U32>) -> List<&2, As.Ins>:
  match ins:
    case Nil{}:
      Nil{}
    case i <> t:
      As.ren(i, 19, cs) <> N.ra.ren(t, cs)

def N.ra.fin(+ins: List<&2, As.Ins>, +named: U32, +max: U32, r: Maybe<&2, NRa>) -> List<&2, As.Ins> & U32:
  match r:
    case None{}:
      (ins, N.pairs(max))
    case Some{+st}:
      +cs = N.ra.colors(10n, 0, N.ra.igs(st), N.ra.cross(st), (named .&. N.ra.slots() : U32),
        U32.is_zero((named .&. N.ra.free() : U32)), Nil{})
      (N.ra.ren(ins, cs), (U32.inc(N.ra.top(cs, 0, named, 0)) >> 1n : U32))

# Branches by offset (N.tag's, the share guard's, the fused multiply's) as
# branches to labels (the function's name, .r and the word they reach), so
# that N.ra and N.sw follow them as any other.
def N.ra.none() -> U32:
  4294967295

def N.ra.tgt(i: As.Ins, +pc: U32) -> U32:
  match i:
    case As.IW{+w}:
      Bool.pick(U32, As.du.bit(As.du(w), 3072), (pc + As.du.off(w) : U32), N.ra.none())
    case other:
      N.ra.none()

def N.ra.pc(+i: As.Ins, +pc: U32) -> U32:
  (pc + (As.Ins.size(i) >> 2n : U32) : U32)

def N.ra.tgts(ins: List<&2, As.Ins>, +pc: U32, +acc: List<&2, U32>) -> List<&2, U32>:
  match ins:
    case Nil{}:
      acc
    case +i <> t:
      +x = N.ra.tgt(i, pc)
      N.ra.tgts(t, N.ra.pc(i, pc), Bool.pick(List<&2, U32>, U32.is_eq(x, N.ra.none()), acc, x <> acc))

def N.ra.has(xs: List<&2, U32>, +x: U32) -> Bool:
  match xs:
    case Nil{}:
      False{}
    case y <> t:
      Bool.or(U32.is_eq(y, x), N.ra.has(t, x))

def N.ra.lab(+name: String, +q: U32) -> String:
  name ++ ".r" ++ U32.show(q)

def N.ra.conv1(i: As.Ins, +pc: U32, +name: String) -> As.Ins:
  match i:
    case As.IW{+w}:
      +x = As.du(w)
      +l = N.ra.lab(name, (pc + As.du.off(w) : U32))
      Bool.pick(As.Ins, As.du.bit(x, 2048), As.IB{(w .&. 4227858432 : U32), l},
        Bool.pick(As.Ins, As.du.bit(x, 1024),
          Bool.pick(As.Ins, As.du.is(w, 2113929216, 905969664), As.IBt{(w .&. 4294443039 : U32), l},
            As.IBc{(w .&. 4278190111 : U32), l}),
          As.IW{w}))
    case other:
      other

def N.ra.conv(ins: List<&2, As.Ins>, +pc: U32, +tg: List<&2, U32>, +name: String) -> List<&2, As.Ins>:
  match ins:
    case Nil{}:
      Nil{}
    case +i <> t:
      +rest = {N.ra.conv1(i, pc, name) <> N.ra.conv(t, N.ra.pc(i, pc), tg, name) : List<&2, As.Ins>}
      Bool.pick(List<&2, As.Ins>, Bool.and(U32.is_ne(As.Ins.size(i), 0), N.ra.has(tg, pc)),
        As.ILab{N.ra.lab(name, pc)} <> rest, rest)

def N.ra.go(+ins: List<&2, As.Ins>, +max: U32) -> List<&2, As.Ins> & U32:
  +us = N.ra.uses(ins, Nil{})
  N.ra.fin(ins, N.ra.named(us, 0), max, Bool.pick(Unit -> Maybe<&2, NRa>, N.ra.bad(us), z => None{},
    z => N.ra.live(8n, N.ra.slots(), us, NRa{Map.new(&2, U32), False{}, Nil{}, 0, 0}))(Unit{}))

# A function's body with its registers given, and the pairs of x19.. its
# prologue saves.
def N.ra(+name: String, body: As.Code, +max: U32) -> List<&2, As.Ins> & U32:
  +ins = As.Code.flat(body)
  +tg = N.ra.tgts(ins, 0, Nil{})
  N.ra.go(Bool.pick(List<&2, As.Ins>, List.is_empty(&2, U32, tg), ins, N.ra.conv(ins, 0, tg, name)), max)

# Shrink-wrapping
# ---------------
#
# A function with a path from its entry to a return (or a tail call) that
# calls nothing and touches no frame slot, as forks's case 0n, gets that
# path first, without the frame: its callee-saved registers renamed to
# scratch ones it does not use, and every branch off it going to the whole
# function after it (at label full), which starts over. So a branch may
# leave the path only while the arguments (x0..x8) are as they came and
# nothing is stored (clean). N.sw.walk tries the branches' next
# instruction first, then their label.

def N.use.d(+u: As.Use) -> U32:
  As.Use{d, uu, k, l, off, n} = u
  d

def N.use.kind(+u: As.Use) -> U32:
  As.Use{d, uu, k, l, off, n} = u
  k

def N.use.u(+u: As.Use) -> U32:
  As.Use{d, uu, k, l, off, n} = u
  uu

def N.use.regs(+u: As.Use) -> U32:
  As.Use{d, uu, k, l, off, n} = u
  (d .|. uu : U32)

# A conditional branch the other way (b.cond, cbz and cbnz, tbz and tbnz).
def N.sw.inv(+w: U32) -> U32:
  Bool.pick(U32, As.du.is(w, 4278190096, 1409286144), (w .^. 1 : U32), (w .^. 16777216 : U32))

def N.sw.label(+labs: Map<&2, List<&2, As.Ins>>, +l: String) -> Maybe<&2, List<&2, As.Ins>>:
  Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, Pair.snd(Map<&2, List<&2, As.Ins>>, Bool, Map.has(&2, List<&2, As.Ins>, labs, l)),
    z => Some{Pair.snd(Map<&2, List<&2, As.Ins>>, List<&2, As.Ins>, Map.get(List<&2, As.Ins>, Nil{}, labs, l))},
    z => None{})(Unit{})

def N.sw.done(+path: List<&2, As.Ins>) -> Maybe<&2, List<&2, As.Ins>>:
  Some{List.reverse(&2, As.Ins, path)}

def N.sw.or(+a: Maybe<&2, List<&2, As.Ins>>, b: Unit -> Maybe<&2, List<&2, As.Ins>>) -> Maybe<&2, List<&2, As.Ins>>:
  Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, Maybe.is_some(&2, List<&2, As.Ins>, a), z => a, b)(Unit{})

# Whether a word keeps the path clean: no store, nothing written to x0..x8.
def N.sw.clean(+w: U32, +d: U32) -> Bool:
  Bool.and(Bool.not(As.mem.st(w)), U32.is_zero((d .&. 511 : U32)))

def N.sw.walk(k: Nat, ins: List<&2, As.Ins>, +labs: Map<&2, List<&2, As.Ins>>, +path: List<&2, As.Ins>, +clean: Bool,
  +full: String
) -> Maybe<&2, List<&2, As.Ins>>:
  match k:
    case 0n:
      None{}
    case 1n+ +j:
      match ins:
        case Nil{}:
          None{}
        case +i <> +t:
          match i:
            case As.IW{+w}:
              +u = As.use.word(w, 0, N.epi.w())
              +kind = N.use.kind(u)
              Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, U32.is_eq(w, N.epi.w()),
                z => N.sw.done(As.IW{As.ret()} <> path),
                z => Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, U32.is_eq(w, N.pop.w()),
                  y => N.sw.walk(j, t, labs, path, clean, full),
                  y => Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, Bool.or(U32.is_ne(kind, 0), As.mem.sp(w)),
                    x => None{},
                    x => N.sw.walk(j, t, labs, As.IW{w} <> path, Bool.and(clean, N.sw.clean(w, N.use.d(u))), full))(Unit{}))(
                  Unit{}))(Unit{})
            case As.ILab{l}:
              N.sw.walk(j, t, labs, path, clean, full)
            case As.ISym{l, e}:
              None{}
            case As.IB{+w, +l}:
              +m = N.sw.label(labs, l)
              Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, U32.is_eq(w, As.bl()), z => None{},
                z => Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, Maybe.is_some(&2, List<&2, As.Ins>, m),
                  y => N.sw.walk(j, Maybe.default(&2, List<&2, As.Ins>, m, Nil{}), labs, path, clean, full),
                  y => N.sw.done(As.IB{w, l} <> path))(Unit{}))(Unit{})
            case As.IBc{+w, +l}:
              Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, clean,
                z => N.sw.or(N.sw.walk(j, t, labs, As.IBc{w, full} <> path, clean, full),
                  y => Maybe.bind(&2, List<&2, As.Ins>, List<&2, As.Ins>, N.sw.label(labs, l),
                    s => N.sw.walk(j, s, labs, As.IBc{N.sw.inv(w), full} <> path, clean, full))),
                z => None{})(Unit{})
            case As.IBt{+w, +l}:
              Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, clean,
                z => N.sw.or(N.sw.walk(j, t, labs, As.IBt{w, full} <> path, clean, full),
                  y => Maybe.bind(&2, List<&2, As.Ins>, List<&2, As.Ins>, N.sw.label(labs, l),
                    s => N.sw.walk(j, s, labs, As.IBt{N.sw.inv(w), full} <> path, clean, full))),
                z => None{})(Unit{})
            case As.IAdr{+rd, l}:
              N.sw.walk(j, t, labs, As.IAdr{rd, l} <> path, Bool.and(clean, U32.is_gt(rd, 8)), full)
            case As.ICall{+w, s}:
              Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, U32.is_eq(w, As.bl()), z => None{},
                z => N.sw.done(As.ICall{w, s} <> path))(Unit{})
            case As.IAdrS{+rd, s}:
              N.sw.walk(j, t, labs, As.IAdrS{rd, s} <> path, Bool.and(clean, U32.is_gt(rd, 8)), full)

# Each label with the code from it.
def N.sw.labs.at(i: As.Ins, t: List<&2, As.Ins>, m: Map<&2, List<&2, As.Ins>>) -> Map<&2, List<&2, As.Ins>>:
  match i:
    case As.ILab{l}:
      Map.set(&2, List<&2, As.Ins>, m, l, t)
    case other:
      m

def N.sw.labs(ins: List<&2, As.Ins>, m: Map<&2, List<&2, As.Ins>>) -> Map<&2, List<&2, As.Ins>>:
  match ins:
    case Nil{}:
      m
    case +i <> +t:
      N.sw.labs(t, N.sw.labs.at(i, t, m))

def N.sw.regs(ins: List<&2, As.Ins>, +acc: U32) -> U32:
  match ins:
    case Nil{}:
      acc
    case i <> t:
      N.sw.regs(t, (acc .|. N.use.regs(As.use(i, 0, N.epi.w())) : U32))

# Registers for x19..x28 on the path: for each it uses, one of x9..x17
# it does not (99: none left).
def N.sw.map(k: Nat, +i: U32, +used: U32, +cs: List<&2, U32>) -> List<&2, U32>:
  match k:
    case 0n:
      List.reverse(&2, U32, cs)
    case 1n+ +j:
      +c = N.ra.first(9n, 9, used)
      Bool.pick(Unit -> List<&2, U32>, As.du.bit(used, As.reg.bit((19 + i : U32))),
        z => N.sw.map(j, U32.inc(i), (used .|. As.reg.bit(c) : U32), c <> cs),
        z => N.sw.map(j, U32.inc(i), used, (19 + i : U32) <> cs))(Unit{})

def N.sw.ok(cs: List<&2, U32>) -> Bool:
  match cs:
    case Nil{}:
      True{}
    case c <> t:
      Bool.and(U32.is_lt(c, 99), N.sw.ok(t))

# A word of the code (else the epilogue's placeholder).
def N.pp.w(i: As.Ins) -> U32:
  match i:
    case As.IW{+w}:
      w
    case other:
      N.epi.w()

# mov a, b with a and b below 29 and not the same: a, else 99.
def N.pp.mv(+w: U32) -> U32:
  +a = (w .&. 31 : U32)
  +b = ((w >> 16n : U32) .&. 31 : U32)
  Bool.pick(U32, Bool.and(As.peep.mov(w), Bool.and(Bool.and(U32.is_lt(a, 29), U32.is_lt(b, 29)), U32.is_ne(a, b))), a,
    99)

# The path is straight code, so its copies are easy to follow: a read of
# a scratch register (x9..x17) that holds a copy of another reads that one
# instead, and a move to a scratch register no one reads is dropped. Past
# the path's end, and at a branch off it, every register but the scratch
# ones counts as read (N.sw.cp.out).
def N.sw.cp.id(k: Nat, +i: U32) -> List<&2, U32>:
  match k:
    case 0n:
      Nil{}
    case 1n+j:
      i <> N.sw.cp.id(j, U32.inc(i))

def N.sw.cp.kill(cp: List<&2, U32>, +i: U32, +d: U32) -> List<&2, U32>:
  match cp:
    case Nil{}:
      Nil{}
    case +c <> t:
      Bool.pick(U32, Bool.or(As.du.bit(d, As.reg.bit(i)), As.du.bit(d, As.reg.bit(c))), i, c) <>
        N.sw.cp.kill(t, U32.inc(i), d)

def N.sw.cp.set(cp: List<&2, U32>, +i: U32, +a: U32, +b: U32) -> List<&2, U32>:
  match cp:
    case Nil{}:
      Nil{}
    case +c <> t:
      Bool.pick(U32, U32.is_eq(i, a), b, c) <> N.sw.cp.set(t, U32.inc(i), a, b)

def N.sw.cp.ren(i: As.Ins, +cp: List<&2, U32>) -> As.Ins:
  match i:
    case As.IW{+w}:
      +x = As.du(w)
      +f = ((x >> 4n : U32) .&. 15 : U32)
      Bool.pick(As.Ins, Bool.and(U32.is_zero((x .&. 256 : U32)), U32.is_zero(((x .&. 15 : U32) .&. f : U32))),
        As.IW{As.ren.fields(w, f, 0, cp)}, As.IW{w})
    case As.IBc{+w, l}:
      As.IBc{Bool.pick(U32, As.du.is(w, 2113929216, 872415232), As.ren.field(w, 0n, 0, cp), w), l}
    case As.IBt{+w, l}:
      As.IBt{As.ren.field(w, 0n, 0, cp), l}
    case other:
      other

# An encoding du does not know.
def N.sw.cp.unk(i: As.Ins) -> Bool:
  match i:
    case As.IW{+w}:
      As.du.bit(As.du(w), 256)
    case other:
      False{}

def N.sw.cp.fw(ins: List<&2, As.Ins>, +cp: List<&2, U32>) -> List<&2, As.Ins>:
  match ins:
    case Nil{}:
      Nil{}
    case +i <> t:
      +i2 = N.sw.cp.ren(i, cp)
      +w = N.pp.w(i2)
      +a = N.pp.mv(w)
      +cp2 = Bool.pick(List<&2, U32>, N.sw.cp.unk(i2), N.sw.cp.id(32n, 0),
        N.sw.cp.kill(cp, 0, N.use.d(As.use(i2, 0, N.epi.w()))))
      +cp3 = Bool.pick(List<&2, U32>, Bool.and(U32.is_ge(a, 9), U32.is_le(a, 17)),
        N.sw.cp.set(cp2, 0, a, ((w >> 16n : U32) .&. 31 : U32)), cp2)
      i2 <> N.sw.cp.fw(t, cp3)

def N.sw.cp.out() -> U32:
  4294705663

def N.sw.cp.bw(rev: List<&2, As.Ins>, +live: U32, +acc: List<&2, As.Ins>) -> List<&2, As.Ins>:
  match rev:
    case Nil{}:
      acc
    case +i <> +t:
      +u = As.use(i, 0, N.epi.w())
      +d = N.use.d(u)
      +a = N.pp.mv(N.pp.w(i))
      +in = Bool.pick(U32, N.sw.cp.unk(i), 4294967295,
        ((((live .&. (d .^. 4294967295 : U32) : U32) .|. N.use.u(u) : U32) .|.
          Bool.pick(U32, U32.is_eq(N.use.kind(u), 2), N.sw.cp.out(), 0) : U32)))
      Bool.pick(Unit -> List<&2, As.Ins>,
        Bool.and(Bool.and(U32.is_ge(a, 9), U32.is_le(a, 17)), Bool.not(As.du.bit(live, As.reg.bit(a)))),
        z => N.sw.cp.bw(t, live, acc), z => N.sw.cp.bw(t, in, i <> acc))(Unit{})

def N.sw.cp(+path: List<&2, As.Ins>) -> List<&2, As.Ins>:
  N.sw.cp.bw(List.reverse(&2, As.Ins, N.sw.cp.fw(path, N.sw.cp.id(32n, 0))), N.sw.cp.out(), Nil{})

def N.sw.fin(+path: List<&2, As.Ins>) -> Maybe<&2, List<&2, As.Ins>>:
  +cs = N.sw.map(10n, 0, N.sw.regs(path, 0), Nil{})
  Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, N.sw.ok(cs), z => Some{N.sw.cp(N.ra.ren(path, cs))}, z => None{})(
    Unit{})

# The path, if there is one (not in a def with twins, whose FP registers
# the path could not keep).
def N.sw(+ins: List<&2, As.Ins>, +fp: Bool, +full: String) -> Maybe<&2, List<&2, As.Ins>>:
  Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, fp, z => None{},
    z => Maybe.bind(&2, List<&2, As.Ins>, List<&2, As.Ins>,
      N.sw.walk(64n, ins, N.sw.labs(ins, Map.new(&2, List<&2, As.Ins>)), Nil{}, True{}, full), p => N.sw.fin(p)))(Unit{})

def N.ins.code(ins: List<&2, As.Ins>) -> As.Code:
  match ins:
    case Nil{}:
      As.CNil{}
    case i <> t:
      As.CCat{As.COne{i}, N.ins.code(t)}

# A frame with no slot in memory (nothing in the body reads or writes sp,
# and no twins): fp and lr pushed with room for the pairs above them, the
# pairs at sp + 16, sp + 32, ..., and sp left as it is.
def N.cpairs(k: Nat, +i: U32, +ld: Bool) -> List<&2, U32>:
  match k:
    case 0n:
      Nil{}
    case 1n+j:
      +r = N.sreg((2 * i : U32))
      +off = (16 * U32.inc(i) : U32)
      Bool.pick(U32, ld, As.ldpo(r, U32.inc(r), 31, off), As.stpo(r, U32.inc(r), 31, off)) <> N.cpairs(j, U32.inc(i), ld)

def N.cframe(+np: U32) -> U32:
  (16 + (16 * np : U32) : U32)

def N.prologue.c(+np: U32) -> As.Code:
  N.ws(As.push_fpk(N.cframe(np)) <> As.set_fp() <> N.cpairs(U32.to_nat(np), 0, False{}))

def N.fix.c(c: As.Code, +np: U32) -> As.Code:
  +rs = N.cpairs(U32.to_nat(np), 0, True{})
  As.Code.subst(c, N.epi.w(), N.ws(List.append(&2, U32, rs, [As.pop_fpk(N.cframe(np)), As.ret()])),
    N.pop.w(), N.ws(List.append(&2, U32, rs, [As.pop_fpk(N.cframe(np))])))

def N.sp.any(ins: List<&2, As.Ins>) -> Bool:
  match ins:
    case Nil{}:
      False{}
    case i <> t:
      Bool.or(As.mem.sp(As.Ins.word(i)), N.sp.any(t))

def N.func.frame(+compact: Bool, +max: U32, +np: U32, +fp: Bool, body: As.Code) -> As.Code:
  match compact:
    case True{}:
      As.CCat{N.prologue.c(np), N.fix.c(body, np)}
    case False{}:
      As.CCat{N.prologue.fp(max, np, fp), N.fix.fp(body, np, fp)}

def N.func.sw(+name: String, +compact: Bool, +max: U32, +np: U32, +fp: Bool, body: As.Code,
  m: Maybe<&2, List<&2, As.Ins>>
) -> As.Code:
  match m:
    case None{}:
      As.CCat{N.one(As.ISym{name, False{}}), N.func.frame(compact, max, np, fp, body)}
    case Some{path}:
      N.cat([N.one(As.ISym{name, False{}}), N.ins.code(path), N.one(As.ILab{name ++ ".full"}),
        N.func.frame(compact, max, np, fp, body)])

# Moves and dead writes
# ---------------------
#
# After N.ra, a value often goes into a register only to be moved on
# (mov x11, x0; mov x1, x11), or into one no one reads. N.pp, with where
# the registers N.ra gives (x11..x15, x19..x28) and x0..x8 are live after each
# instruction: drops an instruction that only writes such registers when
# none is read later (not a store, a call or a branch), and turns mov a, b
# then an instruction that reads a (and does not write it) into that
# instruction reading b, when a is not read after it.

def N.pp.tr() -> U32:
  (511 .|. (N.ra.slots() .|. N.ra.free() : U32) : U32)

# The argument registers x0..x8 are followed too: a call reads them all
# and changes x0..x18, a return reads x0, a branch out of the function (to
# a label not in labs) reads them all, and so does an encoding du does not
# know.
def N.pp.ret(i: As.Ins) -> Bool:
  match i:
    case As.IW{+w}:
      Bool.or(U32.is_eq(w, N.epi.w()), U32.is_eq(w, As.ret()))
    case other:
      False{}

def N.pp.use.go(x: As.Use, +unk: Bool, +ret: Bool, +labs: Map<&2, List<&2, As.Ins>>) -> As.Use:
  As.Use{+d, +u, +kind, +l, off, n} = x
  +away = Bool.and(U32.is_eq(kind, 3), Bool.not(Pair.snd(Map<&2, List<&2, As.Ins>>, Bool, Map.has(&2, List<&2, As.Ins>, labs, l))))
  +out = Bool.or(Bool.or(unk, U32.is_eq(kind, 1)), Bool.or(away, U32.is_eq(kind, 4)))
  As.Use{Bool.pick(U32, U32.is_eq(kind, 1), (d .|. 524287 : U32), d),
    (u .|. Bool.pick(U32, ret, 1, Bool.pick(U32, out, 511, 0)) : U32), kind, l, off, n}

def N.pp.use(+i: As.Ins, +labs: Map<&2, List<&2, As.Ins>>) -> As.Use:
  N.pp.use.go(As.use(i, (N.ra.slots() .|. N.ra.free() : U32), N.epi.w()), N.sw.cp.unk(i), N.pp.ret(i), labs)

def N.pp.uses(ins: List<&2, As.Ins>, +labs: Map<&2, List<&2, As.Ins>>, acc: List<&2, As.Use>) -> List<&2, As.Use>:
  match ins:
    case Nil{}:
      acc
    case i <> t:
      N.pp.uses(t, labs, N.pp.use(i, labs) <> acc)

# The registers of tr live after each instruction, in order (m: the labels'
# sets once they stay the same).
def N.pp.outs(us: List<&2, As.Use>, +out: U32, +m: Map<&2, U32>, acc: List<&2, U32>) -> List<&2, U32>:
  match us:
    case Nil{}:
      acc
    case As.Use{+d, +u, +kind, +l, off, n} <> t:
      +lab = Bool.pick(Unit -> U32, U32.is_lt((kind - 2 : U32), 2),
        z => Pair.snd(Map<&2, U32>, U32, Map.get(U32, 0, m, l)), z => 0)(Unit{})
      +s = N.ra.succ(kind, out, lab, 0)
      +label = U32.is_eq(kind, 8)
      N.pp.outs(t, Bool.pick(U32, label, out, (((s .&. (d .^. 4294967295 : U32) : U32) .|. u : U32) .&. N.pp.tr() : U32)),
        m, Bool.pick(U32, label, out, s) <> acc)

# Whether the code has a branch by offset or an instruction it cannot read.
def N.pp.bad(us: List<&2, As.Use>) -> Bool:
  match us:
    case Nil{}:
      False{}
    case As.Use{d, u, +kind, l, off, n} <> t:
      Bool.or(Bool.and(U32.is_ge(kind, 5), U32.is_le(kind, 7)), N.pp.bad(t))

# Whether word w only writes registers of tr that are dead after it (o).
def N.pp.dead(+w: U32, +o: U32) -> Bool:
  +u = As.use.word(w, N.pp.tr(), N.epi.w())
  +d = N.use.d(u)
  Bool.and(Bool.and(U32.is_eq(N.use.kind(u), 0), U32.is_ne(w, N.epi.w())),
    Bool.and(Bool.and(Bool.not(As.mem.st(w)), Bool.not(As.mem.sp(w))),
      Bool.and(U32.is_ne(d, 0), U32.is_zero((d .&. ((N.pp.tr() .^. 4294967295 : U32) .|. o : U32) : U32)))))

def N.pp.drop(i: As.Ins, +o: U32) -> Bool:
  match i:
    case As.IW{+w}:
      Bool.or(Bool.and(As.peep.mov(w), U32.is_eq((w .&. 31 : U32), ((w >> 16n : U32) .&. 31 : U32))),
        Bool.and(U32.is_ne(w, N.pop.w()), N.pp.dead(w, o)))
    case other:
      False{}

# mov a, b (a of tr, b not 31): a, else 99.
def N.pp.mov(i: As.Ins) -> U32:
  match i:
    case As.IW{+w}:
      +a = (w .&. 31 : U32)
      Bool.pick(U32, Bool.and(As.peep.mov(w), Bool.and(As.du.bit(N.pp.tr(), As.reg.bit(a)),
        U32.is_ne(((w >> 16n : U32) .&. 31 : U32), 31))), a, 99)
    case other:
      99

def N.pp.src(i: As.Ins) -> U32:
  match i:
    case As.IW{w}:
      ((w >> 16n : U32) .&. 31 : U32)
    case other:
      99

# Whether i reads register a, does not write it, and a is dead after it (o).
def N.pp.fwd(+i: As.Ins, +a: U32, +o: U32) -> Bool:
  +u = As.use(i, N.pp.tr(), N.epi.w())
  +b = As.reg.bit(a)
  Bool.and(Bool.and(As.du.bit(N.use.u(u), b), Bool.not(As.du.bit(N.use.d(u), b))),
    Bool.and(Bool.not(As.du.bit(o, b)), U32.is_lt(N.use.kind(u), 4)))

def N.pp.alu(+w: U32) -> Bool:
  +x = As.du(w)
  Bool.and(Bool.and(U32.is_zero((x .&. 7936 : U32)), Bool.not(As.mem.ls(w))),
    Bool.and(U32.is_zero(((x .&. 15 : U32) .&. ((x >> 4n : U32) .&. 15 : U32) : U32)),
      Bool.and(U32.is_ne(w, N.epi.w()), U32.is_ne(w, N.pop.w()))))

# i that writes only a (by rd), then mov b, a, and a is not read after:
# i writing b.
def N.pp.back(+w1: U32, +w2: U32, +o: U32) -> Bool:
  +a = (w1 .&. 31 : U32)
  Bool.and(Bool.and(Bool.and(N.pp.alu(w1), U32.is_eq((As.du(w1) .&. 15 : U32), 1)),
    Bool.and(Bool.and(U32.is_lt(a, 29), As.du.bit(N.pp.tr(), As.reg.bit(a))),
      Bool.and(U32.is_lt(N.pp.mv(w2), 99), U32.is_eq(((w2 >> 16n : U32) .&. 31 : U32), a)))),
    Bool.not(As.du.bit(o, As.reg.bit(a))))

def N.pp.b.w(+w1: U32, +w2: U32) -> U32:
  As.ren.fields(w1, 1, (w1 .&. 31 : U32), [(w2 .&. 31 : U32)])

def N.pp.go(k: Nat, ins: List<&2, As.Ins>, outs: List<&2, U32>) -> List<&2, As.Ins>:
  match k:
    case 0n:
      ins
    case 1n+ +j:
      match ins outs:
        case +i <> +t +o <> +ot:
          +a = N.pp.mov(i)
          +i2 = Maybe.default(&2, As.Ins, List.head(&2, As.Ins, t), As.ILab{""})
          +o2 = Maybe.default(&2, U32, List.head(&2, U32, ot), 4294967295)
          Bool.pick(Unit -> List<&2, As.Ins>, N.pp.drop(i, o),
            z => N.pp.go(j, t, ot),
            z => Bool.pick(Unit -> List<&2, As.Ins>, Bool.and(U32.is_lt(a, 99), N.pp.fwd(i2, a, o2)),
              y => N.pp.go(j, As.ren(i2, a, [N.pp.src(i)]) <> List.tail(&2, As.Ins, t), ot),
              y => Bool.pick(Unit -> List<&2, As.Ins>, N.pp.back(N.pp.w(i), N.pp.w(i2), o2),
                x => N.pp.go(j, As.IW{N.pp.b.w(N.pp.w(i), N.pp.w(i2))} <> List.tail(&2, As.Ins, t), ot),
                x => i <> N.pp.go(j, t, ot))(Unit{}))(Unit{}))(Unit{})
        case il ol:
          il

# Then, with no liveness, for any registers but sp and x29..x30, where
# i is an instruction that only reads and writes registers (no memory, no
# branch) and reads no register it writes by the same field:
# - mov a, b then i that reads a and writes only a: i reading b.
# - i that writes only a (by rd), mov b, a, then such a j that writes a and
#   does not read it: i writing b, then j.
def N.pp.wr(+w: U32) -> U32:
  As.reg.fields(w, (As.du(w) .&. 15 : U32))

def N.pp.rd(+w: U32) -> U32:
  As.reg.fields(w, ((As.du(w) >> 4n : U32) .&. 15 : U32))

def N.pp.f(+w1: U32, +w2: U32) -> Bool:
  +a = N.pp.mv(w1)
  Bool.and(Bool.and(U32.is_lt(a, 99), N.pp.alu(w2)),
    Bool.and(As.du.bit(N.pp.rd(w2), As.reg.bit(a)), U32.is_eq(N.pp.wr(w2), As.reg.bit(a))))

def N.pp.f.w(+w1: U32, +w2: U32) -> U32:
  As.ren.fields(w2, ((As.du(w2) >> 4n : U32) .&. 15 : U32), (w1 .&. 31 : U32), [((w1 >> 16n : U32) .&. 31 : U32)])

def N.pp.b(+w1: U32, +w2: U32, +w3: U32) -> Bool:
  +a = (w1 .&. 31 : U32)
  +ab = As.reg.bit(a)
  Bool.and(Bool.and(Bool.and(N.pp.alu(w1), U32.is_eq((As.du(w1) .&. 15 : U32), 1)),
    Bool.and(U32.is_lt(a, 29), Bool.and(U32.is_lt(N.pp.mv(w2), 99), U32.is_eq(((w2 >> 16n : U32) .&. 31 : U32), a)))),
    Bool.and(N.pp.alu(w3), Bool.and(As.du.bit(N.pp.wr(w3), ab), Bool.not(As.du.bit(N.pp.rd(w3), ab)))))

def N.pp.loc(k: Nat, ins: List<&2, As.Ins>) -> List<&2, As.Ins>:
  match k:
    case 0n:
      ins
    case 1n+ +j:
      match ins:
        case Nil{}:
          Nil{}
        case +i <> +t:
          +w1 = N.pp.w(i)
          +w2 = N.pp.w(Maybe.default(&2, As.Ins, List.head(&2, As.Ins, t), As.ILab{""}))
          +w3 = N.pp.w(Maybe.default(&2, As.Ins, List.head(&2, As.Ins, List.tail(&2, As.Ins, t)), As.ILab{""}))
          Bool.pick(Unit -> List<&2, As.Ins>, N.pp.f(w1, w2),
            z => N.pp.loc(j, As.IW{N.pp.f.w(w1, w2)} <> List.tail(&2, As.Ins, t)),
            z => Bool.pick(Unit -> List<&2, As.Ins>, N.pp.b(w1, w2, w3),
              y => N.pp.loc(j, As.IW{N.pp.b.w(w1, w2)} <> List.tail(&2, As.Ins, t)),
              y => i <> N.pp.loc(j, t))(Unit{}))(Unit{})

# A Nat match tests 0n with cbnz r, L, and then 1n+p with cmp r, #1 and
# b.lo at L. When that cbnz is the only way to L (nothing else names L,
# and the code before L does not fall into it), r is not 0 there and the
# second test goes. The labels map to r + 1 for one cbnz r, else 999.
def N.nz.ref(+w: U32, +l: String, +m: Map<&2, U32>) -> Map<&2, U32>:
  +r = (w .&. 31 : U32)
  +seen = Pair.snd(Map<&2, U32>, Bool, Map.has(&2, U32, m, l))
  Map.set(&2, U32, m, l, Bool.pick(U32, Bool.and(Bool.not(seen), U32.is_eq(w, As.cbnz(r))), U32.inc(r), 999))

def N.nz.refs(ins: List<&2, As.Ins>, +m: Map<&2, U32>) -> Map<&2, U32>:
  match ins:
    case Nil{}:
      m
    case i <> t:
      match i:
        case As.IBc{+w, +l}:
          N.nz.refs(t, N.nz.ref(w, l, m))
        case As.IBt{+w, +l}:
          N.nz.refs(t, N.nz.ref(999, l, m))
        case As.IB{+w, +l}:
          N.nz.refs(t, N.nz.ref(999, l, m))
        case As.IAdr{+rd, +l}:
          N.nz.refs(t, N.nz.ref(999, l, m))
        case other:
          N.nz.refs(t, m)

# Whether the code does not go on past i.
def N.nz.stop(i: As.Ins) -> Bool:
  match i:
    case As.IW{+w}:
      Bool.or(U32.is_eq(w, N.epi.w()), U32.is_ne((As.du(w) .&. 6144 : U32), 0))
    case As.IB{+w, l}:
      U32.is_ne(w, As.bl())
    case As.ICall{+w, s}:
      U32.is_ne(w, As.bl())
    case other:
      False{}

def N.nz.test(+r: U32, i: As.Ins, j: As.Ins) -> Bool:
  match i j:
    case As.IW{+w} As.IBc{+c, l}:
      Bool.and(Bool.and(U32.is_lt(r, 31), U32.is_eq(w, As.cmpi(r, 1))), U32.is_eq(c, As.bc(As.lo())))
    case x y:
      False{}

# At label l: its r + 1, else 0.
def N.nz.lab(i: As.Ins, +m: Map<&2, U32>) -> U32:
  match i:
    case As.ILab{+l}:
      +v = Pair.snd(Map<&2, U32>, U32, Map.get(U32, 0, m, l))
      Bool.pick(U32, U32.is_lt(v, 999), v, 0)
    case other:
      0

def N.nz.go(k: Nat, ins: List<&2, As.Ins>, +m: Map<&2, U32>, +stop: Bool) -> List<&2, As.Ins>:
  match k:
    case 0n:
      ins
    case 1n+ +j:
      match ins:
        case Nil{}:
          Nil{}
        case +i <> +t:
          +r = Bool.pick(Unit -> U32, stop, z => N.nz.lab(i, m), z => 0)(Unit{})
          +i1 = Maybe.default(&2, As.Ins, List.head(&2, As.Ins, t), As.ILab{""})
          +i2 = Maybe.default(&2, As.Ins, List.head(&2, As.Ins, List.tail(&2, As.Ins, t)), As.ILab{""})
          Bool.pick(Unit -> List<&2, As.Ins>, Bool.and(U32.is_ne(r, 0), N.nz.test((r - 1 : U32), i1, i2)),
            z => i <> N.nz.go(j, List.tail(&2, As.Ins, List.tail(&2, As.Ins, t)), m, False{}),
            z => i <> N.nz.go(j, t, m, N.nz.stop(i)))(Unit{})

def N.nz(+ins: List<&2, As.Ins>) -> List<&2, As.Ins>:
  N.nz.go((1n + List.length(&2, As.Ins, ins) : Nat), ins, N.nz.refs(ins, Map.new(&2, U32)), False{})

def N.pp.all(+ins: List<&2, As.Ins>) -> List<&2, As.Ins>:
  N.nz(N.pp.loc((1n + Nat.double(List.length(&2, As.Ins, ins)) : Nat), ins))

def N.pp(+ins: List<&2, As.Ins>) -> List<&2, As.Ins>:
  +us = N.pp.uses(ins, N.sw.labs(ins, Map.new(&2, List<&2, As.Ins>)), Nil{})
  Bool.pick(Unit -> List<&2, As.Ins>, N.pp.bad(us), z => ins,
    z => Maybe.default(&2, List<&2, As.Ins>, Maybe.bind(&2, NRa, List<&2, As.Ins>,
      N.ra.live(8n, N.pp.tr(), us, NRa{Map.new(&2, U32), False{}, Nil{}, 0, 0}),
      st => Some{N.pp.all(N.pp.go((1n + List.length(&2, As.Ins, ins) : Nat), ins,
        N.pp.outs(us, 0, N.ra.m(st), Nil{})))}), ins))(Unit{})

# Allocation without a call
# -------------------------
#
# A call of bn_alloc2 .. bn_alloc6 becomes the fast path rt/native.c
# describes (the contract is there): the thread's caches found from sp, and
# the slot at the cache's bump pointer handed out while there is one, else
# the lowest of its free bits; else the call, which refills the cache. It
# uses x0, x9 .. x13, x16 and x17, which the call may change too.
def N.fast.size(k: Nat, +s: String) -> U32:
  match k:
    case 0n:
      0
    case 1n+ +j:
      +w = (U32.from_nat(j) + 2 : U32)
      Bool.pick(U32, As.Str.eq(s, "bn_alloc" ++ U32.show(w)), w, N.fast.size(j, s))

def N.fast.at(+w: U32, s: String, +l: String) -> As.Code:
  +k = (64 * (w - 2 : U32) : U32)
  N.cat([N.ws([As.addi(16, 31, 0), As.andhi(16, 16), As.ldr(16, 16, 0), As.ldpo(0, 17, 16, k), As.cmp(0, 17)]),
    N.one(As.IBc{As.bc(As.hs()), l ++ ".b"}),
    N.ws([As.addi(17, 0, (8 * w : U32)), As.str(17, 16, k), As.ldrw(9, 16, (k + 24 : U32)), As.addwi(10, 9, 1),
      As.strw(10, 16, (k + 24 : U32)), As.ldr(10, 16, (k + 16 : U32)), As.lsri(11, 9, 6), As.ldrx(12, 10, 11),
      As.movz(13, 1, 0), As.lslv(13, 13, 9), As.orr(12, 12, 13), As.strx(12, 10, 11), As.stpo(31, 31, 0, 0)]),
    N.one(As.IB{As.b(), l ++ ".d"}), N.one(As.ILab{l ++ ".b"}), N.w(As.ldr(9, 16, (k + 32 : U32))),
    N.one(As.IBc{As.cbz(9), l ++ ".s"}),
    N.ws([As.rbit(10, 9), As.clz(10, 10), As.subi(11, 9, 1), As.and(11, 11, 9), As.str(11, 16, (k + 32 : U32)),
      As.ldrw(12, 16, (k + 28 : U32)), As.ldr(13, 16, (k + 16 : U32)), As.ldrx(11, 13, 12), As.movz(17, 1, 0),
      As.lslv(17, 17, 10), As.orr(11, 11, 17), As.strx(11, 13, 12), As.add6(10, 10, 12), As.movz(11, (8 * w : U32), 0),
      As.ldr(12, 16, (k + 40 : U32)), As.madd(0, 10, 11, 12), As.stpo(31, 31, 0, 0)]),
    N.one(As.IB{As.b(), l ++ ".d"}), N.one(As.ILab{l ++ ".s"}), N.one(As.ICall{As.bl(), s}),
    N.one(As.ILab{l ++ ".d"})])

def N.fast(ins: List<&2, As.Ins>, +n: U32, +name: String) -> As.Code:
  match ins:
    case Nil{}:
      As.CNil{}
    case +i <> +t:
      match i:
        case As.ICall{+w, +s}:
          +sz = N.fast.size(5n, s)
          Bool.pick(Unit -> As.Code, Bool.and(U32.is_eq(w, As.bl()), U32.is_ne(sz, 0)),
            z => As.CCat{N.fast.at(sz, s, name ++ ".a" ++ U32.show(n)), N.fast(t, U32.inc(n), name)},
            z => As.CCat{N.one(As.ICall{w, s}), N.fast(t, n, name)})(Unit{})
        case other:
          As.CCat{N.one(other), N.fast(t, n, name)}

# Leaving the path at its first branch
# ------------------------------------
#
# When the path falls through the body's first branch (b.cond, cbz or tbz
# to L), the body before it only moves and computes, and the code before L
# does not fall into it, the path leaves there for a copy of the prologue
# and of that code (without its labels) placed just before L (label st),
# not for the whole function, which would take the same branch again.
type NFirst is Data:
  NFirst{pre: List<&2, As.Ins>, w: U32, l: String}

def N.fb(ins: List<&2, As.Ins>, acc: List<&2, As.Ins>) -> Maybe<&2, NFirst>:
  match ins:
    case Nil{}:
      None{}
    case i <> t:
      match i:
        case As.IW{+w}:
          Bool.pick(Unit -> Maybe<&2, NFirst>,
            Bool.or(Bool.or(U32.is_eq(w, N.epi.w()), U32.is_eq(w, N.pop.w())), U32.is_ne((As.du(w) .&. 7936 : U32), 0)),
            z => None{}, z => N.fb(t, As.IW{w} <> acc))(Unit{})
        case As.IBc{+c, +l}:
          Some{NFirst{List.reverse(&2, As.Ins, acc), c, l}}
        case As.IBt{+c, +l}:
          Some{NFirst{List.reverse(&2, As.Ins, acc), c, l}}
        case As.IAdr{+rd, +l}:
          N.fb(t, As.IAdr{rd, l} <> acc)
        case As.IAdrS{+rd, +s}:
          N.fb(t, As.IAdrS{rd, s} <> acc)
        case As.ILab{l}:
          N.fb(t, acc)
        case other:
          None{}

# The word of the path's first branch (0: none).
def N.fb.w(path: List<&2, As.Ins>) -> U32:
  match path:
    case Nil{}:
      0
    case i <> t:
      match i:
        case As.IBc{+w, l}:
          w
        case As.IBt{+w, l}:
          w
        case other:
          N.fb.w(t)

# The same branch, but for the register a path may have renamed.
def N.fb.same(+a: U32, +b: U32) -> Bool:
  Bool.pick(Bool, As.du.is(b, 4278190096, 1409286144), U32.is_eq(a, b),
    U32.is_eq((a .&. 4294967264 : U32), (b .&. 4294967264 : U32)))

def N.fb.lab(i: As.Ins) -> String:
  match i:
    case As.ILab{+l}:
      l
    case other:
      ""

def N.fb.at(ins: List<&2, As.Ins>, +l: String, +stub: List<&2, As.Ins>, +stop: Bool) -> Maybe<&2, List<&2, As.Ins>>:
  match ins:
    case Nil{}:
      None{}
    case +i <> +t:
      +here = Bool.and(stop, Str.eq(N.fb.lab(i), l))
      Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, here,
        z => Some{List.append(&2, As.Ins, stub, i <> t)},
        z => Maybe.bind(&2, List<&2, As.Ins>, List<&2, As.Ins>, N.fb.at(t, l, stub, N.nz.stop(i)), r => Some{i <> r}))(
        Unit{})

def N.fb.ret(path: List<&2, As.Ins>, +st: String) -> List<&2, As.Ins>:
  match path:
    case Nil{}:
      Nil{}
    case i <> t:
      match i:
        case As.IBc{+w, l}:
          As.IBc{w, st} <> t
        case As.IBt{+w, l}:
          As.IBt{w, st} <> t
        case other:
          other <> N.fb.ret(t, st)

def N.fb.stub(+name: String, ins: List<&2, As.Ins>, +pw: U32, pro: As.Code, f: NFirst) -> Maybe<&2, List<&2, As.Ins>>:
  match f:
    case NFirst{pre, +w, +l}:
      Bool.pick(Unit -> Maybe<&2, List<&2, As.Ins>>, Bool.and(U32.is_ne(pw, 0), N.fb.same(pw, w)),
        z => N.fb.at(ins, l, As.ILab{name ++ ".st"} <> List.append(&2, As.Ins, As.Code.flat(pro), pre), False{}),
        z => None{})(Unit{})

# The body with the stub, if the path can leave for it.
def N.fb.body(+name: String, ins: List<&2, As.Ins>, +path: List<&2, As.Ins>, pro: As.Code) -> Maybe<&2, List<&2, As.Ins>>:
  +pw = N.fb.w(path)
  +ins2 = ins
  Maybe.bind(&2, NFirst, List<&2, As.Ins>, N.fb(ins2, Nil{}),
    f => N.fb.stub(name, ins2, pw, pro, f))

def N.func.pro(+compact: Bool, +max: U32, +np: U32, +fp: Bool) -> As.Code:
  Bool.pick(As.Code, compact, N.prologue.c(np), N.prologue.fp(max, np, fp))

def N.func.st2(+name: String, +compact: Bool, +max: U32, +np: U32, +fp: Bool, +ins: List<&2, As.Ins>,
  +path: List<&2, As.Ins>, b: Maybe<&2, List<&2, As.Ins>>
) -> As.Code:
  match b:
    case None{}:
      N.func.sw(name, compact, max, np, fp, N.fast(ins, 0, name), Some{path})
    case Some{body}:
      N.func.sw(name, compact, max, np, fp, N.fast(body, 0, name), Some{N.fb.ret(path, name ++ ".st")})

def N.func.st(+name: String, +compact: Bool, +max: U32, +np: U32, +fp: Bool, +ins: List<&2, As.Ins>,
  m: Maybe<&2, List<&2, As.Ins>>
) -> As.Code:
  match m:
    case None{}:
      N.func.sw(name, compact, max, np, fp, N.fast(ins, 0, name), None{})
    case Some{+path}:
      N.func.st2(name, compact, max, np, fp, ins, path, N.fb.body(name, ins, path, N.func.pro(compact, max, np, fp)))

def N.func.ra(+name: String, +max: U32, +fp: Bool, r: List<&2, As.Ins> & U32) -> As.Code:
  (ins0, +np) = r
  +ins = N.pp(N.pp(ins0))
  N.func.st(name, Bool.and(Bool.not(fp), Bool.not(N.sp.any(ins))), max, np, fp, ins, N.sw(ins, fp, name ++ ".full"))

# A function: its symbol, its prologue for a frame of max slots (saving the
# callee-saved registers N.ra leaves it), and its body; first, the path
# N.sw finds.
# The same, saving d8..d15 too (fp: a def with twins, N.twins).
def N.func.fp(+name: String, +max: U32, +fp: Bool, body: As.Code) -> As.Code:
  N.func.ra(name, max, fp, N.ra(name, body, max))

def N.func(+name: String, +max: U32, body: As.Code) -> As.Code:
  N.func.fp(name, max, False{}, body)

def N.call(s: String) -> As.Code:
  N.one(As.ICall{As.bl(), s})

def N.bl(l: String) -> As.Code:
  N.one(As.IB{As.bl(), l})

def N.b(l: String) -> As.Code:
  N.one(As.IB{As.b(), l})

def N.lab(l: String) -> As.Code:
  N.one(As.ILab{l})

def N.adr(+r: U32, l: String) -> As.Code:
  N.one(As.IAdr{r, l})

# x0 = a new block of w words (bn_alloc, in rt/native.c; bn_alloc2 ..
# bn_alloc6 for the common sizes).
def N.alloc.by(+f: String, +w: U32) -> As.Code:
  Bool.pick(As.Code, Bool.and(U32.is_ge(w, 2), U32.is_le(w, 6)), N.call(f ++ U32.show(w)),
    As.CCat{N.k(0, w), N.call(f)})

def N.alloc(+w: U32) -> As.Code:
  N.alloc.by("bn_alloc", w)

def N.alloc.hole(+w: U32) -> As.Code:
  N.alloc.by("bn_alloc_hole", w)

# Stores operands at [x0 + off], [x0 + off + 8], ... (through x9).
def N.fields(os: List<&2, NO>, +off: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case o <> t:
      N.cat([N.lo(o, 9), N.w(As.str(9, 0, off)), N.fields(t, (off + 8 : U32))])

# x0 = TAG(x0): the tag of a nullary constructor (v >> 3) or of a node (its
# first word, without the sharing bits).
def N.tag() -> As.Code:
  N.ws([(As.tbnz(0, 0) .|. 128 : U32), As.ldr(0, 0, 0), As.andsh(0, 0), (As.b() .|. 2 : U32),
    As.lsri(0, 0, 3)])

# x0 = x0 + k, stopping at the Nat wall (NAT_IMM = 2^48 - 1).
def N.natk(+k: U32) -> As.Code:
  N.cat([N.k(9, k), N.w(As.add(0, 0, 9)), N.ws(As.mov64(9, 4294967295, 65535)),
    N.w(As.cmp(0, 9)), N.w((As.bc(As.ls()) .|. 64 : U32)), N.call("nat_wall")])

# A closure {fn, arity, n, args...} of the function at label f.
def N.clo(+f: String, +arity: U32, +os: List<&2, NO>) -> As.Code:
  +n = U32.from_nat(List.length(&2, NO, os))
  N.cat([N.alloc((n + 3 : U32)), N.adr(9, f), N.w(As.str(9, 0, 0)), N.k(9, arity), N.w(As.str(9, 0, 8)),
    N.k(9, n), N.w(As.str(9, 0, 16)), N.fields(os, 24)])

# x0 = the address of data slot d.
def N.dslot.at(+d: U32) -> As.Code:
  As.CCat{N.one(As.IAdrS{0, "bn_slots"}), N.addk(0, 0, (d * 8 : U32))}

# A string literal: built once (str_cache), then loaded from its slot.
def N.str(+s: String) -> NG(As.Code):
  do NG<As.Code>:
    +d : U32 <- N.dslot()
    +l : String <- N.cstr(s)
    +slow : String <- N.label()
    +done : String <- N.label()
    return N.cat([N.dslot.at(d), N.w(As.ldar(9, 0)), N.one(As.IBc{As.cbz(9), slow}), N.w(As.mov(0, 9)),
      N.b(done), N.lab(slow), N.adr(1, l), N.k(2, As.len32(As.bytes(s))), N.call("str_cache"), N.lab(done)])

# A float literal's bits, at compile time: a decimal of at most 14 digits,
# 6 of them after the point, rounded to nearest (ties to even) as strtof
# rounds, with every number below 2^48 (Nat's range); others (and ones
# that would be subnormal or infinite) are read at run time (N.flt).
type FltP is Data:
  FltP{m: Nat, f: Nat, nd: Nat, ok: Bool}

def Flt.scan(s: String, r: FltP, +dot: Bool) -> FltP:
  match s:
    case SNil{}:
      r
    case SCon{Chr{+c}, +t}:
      FltP{+m, +f, +nd, +ok} = r
      Bool.pick(Unit -> FltP, U32.is_eq(c, 46), u => Bool.pick(Unit -> FltP, dot, v => FltP{m, f, nd, False{}},
        v => Flt.scan(t, FltP{m, f, nd, ok}, True{}))(Unit{}),
        u => Bool.pick(Unit -> FltP, Bool.and(Bool.and(U32.is_ge(c, 48), U32.is_le(c, 57)), Nat.is_lt(nd, 14n)),
          v => Flt.scan(t, FltP{Nat.add(Nat.mul(m, 10n), U32.to_nat((c - 48 : U32))), Bool.pick(Nat, dot, 1n+f, f),
            1n+nd, ok}, dot),
          v => FltP{m, f, nd, False{}})(Unit{}))(Unit{})

# The bits a number needs.
def Flt.blen(fu: Nat, +n: Nat) -> Nat:
  match fu:
    case 0n:
      0n
    case 1n+k:
      Bool.pick(Unit -> Nat, Nat.is_eq(n, 0n), u => 0n, u => 1n+Flt.blen(k, Nat.div(n, 2n)))(Unit{})

def Flt.fin(+q: Nat, +t: Nat, +ld: Nat) -> Maybe<&2, U32>:
  +e = Nat.sub(t, ld)
  Bool.pick(Maybe<&2, U32>, Bool.and(Nat.is_gt(t, ld), Nat.is_lt(e, 255n)),
    Some{U32.from_nat(Nat.add(Nat.mul(e, Nat.pow(2n, 23n)), Nat.sub(q, Nat.pow(2n, 23n))))}, None{})

# q (below 2^25) and the remainder r of the division by d, rounded.
def Flt.round(qr: Nat & Nat, +d: Nat, +t: Nat, +ld: Nat) -> Maybe<&2, U32>:
  (+q, +r) = qr
  +up = Bool.or(Nat.is_gt(Nat.double(r), d), Bool.and(Nat.is_eq(Nat.double(r), d), Nat.is_eq(Nat.mod(q, 2n), 1n)))
  +q1 = Bool.pick(Nat, up, 1n+q, q)
  +top = Nat.is_eq(q1, Nat.pow(2n, 24n))
  Flt.fin(Bool.pick(Nat, top, Nat.pow(2n, 23n), q1), Bool.pick(Nat, top, 1n+t, t), ld)

# m * 2^a / (den * 2^b) is in [2^23, 2^25): halved into [2^23, 2^24).
def Flt.q(+n: Nat, +d: Nat, +t: Nat, +ld: Nat) -> Maybe<&2, U32>:
  +hi = Nat.is_ge(Nat.div(n, d), Nat.pow(2n, 24n))
  +d2 = Bool.pick(Nat, hi, Nat.double(d), d)
  Flt.round(Nat.divmod(n, d2), d2, Bool.pick(Nat, hi, 1n+t, t), ld)

# m / den = q * 2^(lm - ld - 24 + h), q in [2^23, 2^24): the biased exponent
# is lm + 126 + h - ld.
def Flt.mag(+m: Nat, +den: Nat) -> Maybe<&2, U32>:
  +lm = Flt.blen(64n, m)
  +ld = Flt.blen(64n, den)
  +up = Nat.is_ge(Nat.add(24n, ld), lm)
  Flt.q(Bool.pick(Nat, up, Nat.mul(m, Nat.pow(2n, Nat.sub(Nat.add(24n, ld), lm))), m),
    Bool.pick(Nat, up, den, Nat.mul(den, Nat.pow(2n, Nat.sub(lm, Nat.add(24n, ld))))), Nat.add(lm, 126n), ld)

def Flt.parsed(r: FltP) -> Maybe<&2, U32>:
  FltP{+m, +f, +nd, +ok} = r
  Bool.pick(Unit -> Maybe<&2, U32>, Bool.and(ok, Bool.and(Nat.is_le(f, 6n), Nat.is_gt(nd, 0n))),
    u => Bool.pick(Unit -> Maybe<&2, U32>, Nat.is_eq(m, 0n), v => Some{0}, v => Flt.mag(m, Nat.pow(10n, f)))(Unit{}),
    u => None{})(Unit{})

def Flt.neg(m: Maybe<&2, U32>) -> Maybe<&2, U32>:
  match m:
    case Some{+b}:
      Some{(b .|. 2147483648 : U32)}
    case None{}:
      None{}

def Flt.bits(s: String) -> Maybe<&2, U32>:
  match s:
    case SCon{Chr{45}, t}:
      Flt.neg(Flt.parsed(Flt.scan(t, FltP{0n, 0n, 0n, True{}}, False{})))
    case other:
      Flt.parsed(Flt.scan(other, FltP{0n, 0n, 0n, True{}}, False{}))

# A float literal, read once (bn_flt, in rt/native.c, reads as C does). Its
# slot holds a number, not a pointer, so a plain load will do.
def N.flt.rt(s: String) -> NG(As.Code):
  do NG<As.Code>:
    +d : U32 <- N.dslot()
    +l : String <- N.cstr(s)
    +slow : String <- N.label()
    +done : String <- N.label()
    return N.cat([N.dslot.at(d), N.w(As.ldr(9, 0, 0)), N.one(As.IBc{As.cbz(9), slow}), N.w(As.ubfm(0, 9, 0, 31)),
      N.b(done), N.lab(slow), N.adr(1, l), N.call("bn_flt"), N.lab(done)])

def N.flt.or(m: Maybe<&2, U32>, s: String) -> NG(As.Code):
  match m:
    case Some{+b}:
      NG.pure(As.Code, N.k(0, b))
    case None{}:
      N.flt.rt(s)

def N.flt(+s: String) -> NG(As.Code):
  N.flt.or(Flt.bits(s), s)

# Patterns
# --------

# A place in a value a pattern looks at: an operand, a field, a Nat minus
# k, a word's low bit (as a Bool) or the rest of it, an array's half.
type NPa is Data:
  NPO{o: NO}
  NPF{p: NPa, i: U32}
  NPK{p: NPa, k: U32}
  NPB{p: NPa}
  NPW{p: NPa}
  NPH{p: NPa, hi: U32}

# A test: equal to a word, not zero, at least k, a tag, an array's leaf or
# node, a float literal, never.
type NCo is Data:
  NCEq{p: NPa, k: U32}
  NCNz{p: NPa}
  NCGe{p: NPa, k: U32}
  NCTag{p: NPa, tag: U32}
  NCLeaf{p: NPa}
  NCNode{p: NPa}
  NCFlt{p: NPa, s: String}
  NCNo{}

type NBd is Data:
  NBd{name: String, p: NPa}

type NPr is Data:
  NPr{conds: List<&2, NCo>, binds: List<&2, NBd>}

def N.pat.var(+x: String, path: NPa, r: NPr) -> NPr:
  NPr{conds, +binds} = r
  NPr{conds, Bool.pick(List<&2, NBd>, Str.eq(x, "_"), binds, NBd{x, path} <> binds)}

def N.pat.cond(c: NCo, r: NPr) -> NPr:
  NPr{conds, binds} = r
  NPr{c <> conds, binds}

def N.pat.tag(single: Bool, c: NCo, r: NPr) -> NPr:
  match single:
    case True{}:
      r
    case False{}:
      N.pat.cond(c, r)

def N.is_field(p: NPa) -> Bool:
  match p:
    case NPF{q, i}:
      True{}
    case other:
      False{}

# A node the pattern opens (Gen.pat.node): %top (a scrutinee) or %sub (a
# field), then its size in words.
def N.pat.node(+ar: U32, +path: NPa, r: NPr) -> NPr:
  NPr{conds, binds} = r
  NPr{conds, NBd{Bool.pick(String, N.is_field(path), "%sub", "%top") ++ U32.show(U32.inc(ar)), path} <> binds}

def N.imm(+t: U32) -> U32:
  ((t * 8 : U32) + 1 : U32)

def N.fld(+path: NPa, +i: U32) -> NPa:
  Bool.pick(NPa, U32.is_eq(i, 99), path, NPF{path, i})

# Gen.pat.go, on places (see there for the stages).
def N.pat.go(
  p: Core.Pat, st: Nat, +g: G, +path: NPa, +i: U32, info: Maybe<&2, CInfo>, k: Nat, r: NPr
) -> NPr:
  match p:
    case Core.PCtor{+name, args}:
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
                      N.pat.tag(single, NCTag{path, tag}, r)
                    case 1n:
                      N.pat.tag(single, NCEq{path, N.imm(tag)}, r)
                    case 2n:
                      r
                    case 3n:
                      N.pat.cond(NCEq{path, 0}, r)
                    case 4n:
                      N.pat.cond(NCNz{path}, r)
                    case 5n:
                      N.pat.cond(NCLeaf{path}, r)
                    case 6n+q:
                      N.pat.cond(NCNode{path}, r)
            case 2n:
              match info:
                case None{}:
                  N.pat.cond(NCNo{}, r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      N.pat.go(Core.PCtor{name, Nil{}}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              N.pat.go(Core.PCtor{name, Nil{}}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  N.pat.go(Core.PCtor{name, Nil{}}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +a <> Nil{}:
          match st:
            case 0n:
              N.pat.go(Core.PCtor{name, Nil{}}, 0n, g, path, U32.inc(i), None{}, 0n,
                N.pat.go(a, 3n, g, N.fld(path, i), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      N.pat.go(Core.PCtor{name, [a]}, 0n, g, path, 0, None{}, 0n,
                        N.pat.node(ar, path, N.pat.tag(single, NCTag{path, tag}, r)))
                    case 1n:
                      N.pat.tag(single, NCEq{path, N.imm(tag)}, r)
                    case 2n:
                      N.pat.go(Core.PCtor{name, [a]}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      N.pat.cond(NCEq{path, 0}, r)
                    case 4n:
                      N.pat.go(Core.PCtor{name, [a]}, 0n, g, NPK{path, 1}, 99, None{}, 0n,
                        N.pat.cond(NCNz{path}, r))
                    case 5n:
                      N.pat.go(Core.PCtor{name, [a]}, 0n, g, path, 0, None{}, 0n, N.pat.cond(NCLeaf{path}, r))
                    case 6n+q:
                      N.pat.cond(NCNode{path}, r)
            case 2n:
              match info:
                case None{}:
                  N.pat.cond(NCNo{}, r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      N.pat.go(Core.PCtor{name, [a]}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      N.pat.go(a, 4n, g, path, 0, None{}, Pat.wordk(a), r)
            case 3n:
              N.pat.go(Core.PCtor{name, [a]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  N.pat.go(Core.PCtor{name, [a]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +a <> +b <> Nil{}:
          match st:
            case 0n:
              N.pat.go(Core.PCtor{name, [b]}, 0n, g, path, U32.inc(i), None{}, 0n,
                N.pat.go(a, 3n, g, N.fld(path, i), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      N.pat.go(Core.PCtor{name, [a, b]}, 0n, g, path, 0, None{}, 0n,
                        N.pat.node(ar, path, N.pat.tag(single, NCTag{path, tag}, r)))
                    case 1n:
                      N.pat.tag(single, NCEq{path, N.imm(tag)}, r)
                    case 2n:
                      N.pat.go(Core.PCtor{name, [a, b]}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      N.pat.cond(NCEq{path, 0}, r)
                    case 4n:
                      N.pat.go(Core.PCtor{name, [a, b]}, 0n, g, NPK{path, 1}, 99, None{}, 0n,
                        N.pat.cond(NCNz{path}, r))
                    case 5n:
                      N.pat.go(Core.PCtor{name, [a, b]}, 0n, g, path, 0, None{}, 0n, N.pat.cond(NCLeaf{path}, r))
                    case 6n+q:
                      N.pat.go(b, 3n, g, NPH{path, 1}, 0, None{}, 0n,
                        N.pat.go(a, 3n, g, NPH{path, 0}, 0, None{}, 0n,
                          N.pat.cond(NCNode{path}, r)))
            case 2n:
              match info:
                case None{}:
                  N.pat.cond(NCNo{}, r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      N.pat.go(Core.PCtor{name, [a, b]}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              N.pat.go(Core.PCtor{name, [a, b]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  N.pat.go(b, 4n, g, NPW{path}, 0, None{}, Pat.wordk(b),
                    N.pat.go(a, 3n, g, NPB{path}, 0, None{}, 0n, r))
                case 1n:
                  r
                case 2n+q:
                  N.pat.go(Core.PCtor{name, [a, b]}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
        case +h <> +t:
          match st:
            case 0n:
              N.pat.go(Core.PCtor{name, t}, 0n, g, path, U32.inc(i), None{}, 0n,
                N.pat.go(h, 3n, g, N.fld(path, i), 0, None{}, 0n, r))
            case 1n:
              match info:
                case None{}:
                  r
                case Some{CInfo{+tag, +ar, kind, +single}}:
                  match k:
                    case 0n:
                      N.pat.go(Core.PCtor{name, h <> t}, 0n, g, path, 0, None{}, 0n,
                        N.pat.node(ar, path, N.pat.tag(single, NCTag{path, tag}, r)))
                    case 1n:
                      N.pat.tag(single, NCEq{path, N.imm(tag)}, r)
                    case 2n:
                      N.pat.go(Core.PCtor{name, h <> t}, 0n, g, path, 99, None{}, 0n, r)
                    case 3n:
                      N.pat.cond(NCEq{path, 0}, r)
                    case 4n:
                      N.pat.go(Core.PCtor{name, h <> t}, 0n, g, NPK{path, 1}, 99, None{}, 0n,
                        N.pat.cond(NCNz{path}, r))
                    case 5n:
                      N.pat.go(Core.PCtor{name, h <> t}, 0n, g, path, 0, None{}, 0n, N.pat.cond(NCLeaf{path}, r))
                    case 6n+q:
                      N.pat.cond(NCNode{path}, r)
            case 2n:
              match info:
                case None{}:
                  N.pat.cond(NCNo{}, r)
                case Some{CInfo{+tag, +ar, +kind, +single}}:
                  match k:
                    case 2n+q:
                      N.pat.go(Core.PCtor{name, h <> t}, 1n, g, path, 0, Some{CInfo{tag, ar, kind, single}}, U32.to_nat(kind), r)
                    case other:
                      r
            case 3n:
              N.pat.go(Core.PCtor{name, h <> t}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case 4n:
              match k:
                case 0n:
                  r
                case 1n:
                  r
                case 2n+q:
                  N.pat.go(Core.PCtor{name, h <> t}, 2n, g, path, 0, G.ctor(g, name), P.which(name, ["U32", "F32"]), r)
            case other:
              r
    case Core.PVar{+x}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          N.pat.var(x, path, r)
        case 4n:
          match k:
            case 2n+z:
              N.pat.var(x, path, r)
            case other:
              r
        case other:
          r
    case Core.PNat{+n}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          N.pat.cond(NCEq{path, n}, r)
        case 4n:
          match k:
            case 2n+z:
              N.pat.cond(NCEq{path, n}, r)
            case other:
              r
        case other:
          r
    case Core.PSucc{+j, q}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          N.pat.go(q, 3n, g, NPK{path, j}, 0, None{}, 0n, N.pat.cond(NCGe{path, j}, r))
        case 4n:
          match k:
            case 2n+z:
              N.pat.go(q, 3n, g, NPK{path, j}, 0, None{}, 0n, N.pat.cond(NCGe{path, j}, r))
            case other:
              r
        case other:
          r
    case Core.PNum{+n}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          N.pat.cond(NCEq{path, n}, r)
        case 4n:
          match k:
            case 2n+z:
              N.pat.cond(NCEq{path, n}, r)
            case other:
              r
        case other:
          r
    case Core.PFlt{+f}:
      match st:
        case 0n:
          r
        case 1n:
          r
        case 2n:
          r
        case 3n:
          N.pat.cond(NCFlt{path, f}, r)
        case 4n:
          match k:
            case 2n+z:
              N.pat.cond(NCFlt{path, f}, r)
            case other:
              r
        case other:
          r

def N.pat(+g: G, p: Core.Pat, +path: NPa, r: NPr) -> NPr:
  N.pat.go(p, 3n, g, path, 0, None{}, 0n, r)

def N.pats(+g: G, ps: List<&2, Core.Pat>, os: List<&2, NO>, r: NPr) -> NPr:
  match ps os:
    case p <> pt o <> ot:
      N.pats(g, pt, ot, N.pat(g, p, NPO{o}, r))
    case pl ol:
      r

# The register a place is in with no code (a slot's), else 0 (x0, after
# N.path).
def N.preg(p: NPa) -> U32:
  match p:
    case NPO{o}:
      match o:
        case NOS{+s}:
          Bool.pick(U32, U32.is_lt(s, N.nregs()), N.sreg(s), 0)
        case NOK{k}:
          0
    case other:
      0

# rd = rn - k.
def N.subk(+rd: U32, +rn: U32, +k: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_lt(k, 4096), N.w(As.subi(rd, rn, k)), As.CCat{N.k(9, k), N.w(As.sub(rd, rn, 9))})

# The value at a place into x0 (x9 is scratch; arr_half is a call).
def N.path(p: NPa) -> As.Code:
  match p:
    case NPO{o}:
      N.lo(o, 0)
    case NPF{q, +i}:
      As.CCat{N.path(q), N.w(As.ldr(0, 0, ((i + 1 : U32) * 8 : U32)))}
    case NPK{+q, +k}:
      As.CCat{Bool.pick(As.Code, U32.is_zero(N.preg(q)), N.path(q), As.CNil{}), N.subk(0, N.preg(q), k)}
    case NPB{q}:
      N.cat([N.path(q), N.ws([As.and1(0, 0), As.lsli(0, 0, 3), As.orr1(0, 0)])])
    case NPW{q}:
      As.CCat{N.path(q), N.w(As.ubfm(0, 0, 1, 31))}
    case NPH{q, +hi}:
      N.cat([N.path(q), N.k(1, hi), N.call("arr_half")])

def N.pcode(+p: NPa) -> As.Code:
  Bool.pick(As.Code, U32.is_zero(N.preg(p)), N.path(p), As.CNil{})

# cmp r, k (through x9 past 12 bits).
def N.cmpk(+r: U32, +k: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_lt(k, 4096), N.w(As.cmpi(r, k)), As.CCat{N.k(9, k), N.w(As.cmp(r, 9))})

def N.cond.eq(+r: U32, +k: U32, +no: String) -> As.Code:
  Bool.pick(As.Code, U32.is_zero(k), N.one(As.IBc{As.cbnz(r), no}),
    As.CCat{N.cmpk(r, k), N.one(As.IBc{As.bc(As.ne()), no})})

# A test, branching to no when it fails (a place in a register is read
# there).
def N.cond(c: NCo, +no: String) -> NG(As.Code):
  match c:
    case NCEq{+p, +k}:
      NG.pure(As.Code, As.CCat{N.pcode(p), N.cond.eq(N.preg(p), k, no)})
    case NCNz{+p}:
      NG.pure(As.Code, As.CCat{N.pcode(p), N.one(As.IBc{As.cbz(N.preg(p)), no})})
    case NCGe{+p, +k}:
      NG.pure(As.Code, N.cat([N.pcode(p), N.cmpk(N.preg(p), k), N.one(As.IBc{As.bc(As.lo()), no})]))
    case NCTag{p, +tag}:
      NG.pure(As.Code, N.cat([N.path(p), N.tag(), N.k(9, tag), N.w(As.cmp(0, 9)),
        N.one(As.IBc{As.bc(As.ne()), no})]))
    case NCLeaf{p}:
      NG.pure(As.Code, N.cat([N.path(p), N.w(As.ldr(0, 0, 0)), N.k(9, 31), N.w(As.and(0, 0, 9)),
        N.one(As.IBc{As.cbnz(0), no})]))
    case NCNode{p}:
      NG.pure(As.Code, N.cat([N.path(p), N.w(As.ldr(0, 0, 0)), N.k(9, 31), N.w(As.and(0, 0, 9)),
        N.one(As.IBc{As.cbz(0), no})]))
    case NCFlt{p, s}:
      do NG<As.Code>:
        f : As.Code <- N.flt(s)
        return N.cat([f, N.w(As.mov(11, 0)), N.path(p), N.w(As.cmp(0, 11)), N.one(As.IBc{As.bc(As.ne()), no})])
    case NCNo{}:
      NG.pure(As.Code, N.b(no))

def N.conds(cs: List<&2, NCo>, +no: String) -> NG(As.Code):
  match cs:
    case Nil{}:
      NG.pure(As.Code, As.CNil{})
    case c <> t:
      do NG<As.Code>:
        a : As.Code <- N.cond(c, no)
        b : As.Code <- N.conds(t, no)
        return As.CCat{a, b}

# A pattern's bindings: a place that is an operand is bound to it, any
# other is loaded into a slot from base up.
def N.binds.n(bs: List<&2, NBd>) -> U32:
  match bs:
    case Nil{}:
      0
    case NBd{x, p} <> t:
      match p:
        case NPO{o}:
          N.binds.n(t)
        case other:
          U32.inc(N.binds.n(t))

def N.binds.env(bs: List<&2, NBd>, +base: U32, env: NEnv()) -> NEnv():
  match bs:
    case Nil{}:
      env
    case NBd{x, p} <> t:
      match p:
        case NPO{o}:
          N.binds.env(t, base, NB{x, o} <> env)
        case other:
          N.binds.env(t, U32.inc(base), NB{x, NOS{base}} <> env)

def N.binds.code(bs: List<&2, NBd>, +base: U32) -> As.Code:
  match bs:
    case Nil{}:
      As.CNil{}
    case NBd{x, p} <> t:
      match p:
        case NPO{o}:
          N.binds.code(t, base)
        case other:
          N.cat([N.path(other), N.st(0, base), N.binds.code(t, U32.inc(base))])

# Freeing on match
# ----------------
#
# As the C backend does (see "Freeing on match" in bendrt.h, and
# GSCaseBodyMat): after a pattern's bindings are loaded, the nodes it opens
# go to bend_take (a scrutinee's, then its fields' in reverse, each before
# the nodes inside it), and a binding its body uses twice to bend_share
# (bn_take and bn_share in rt/native.c). BEND_NO_FREE turns it off: the
# pattern then binds no nodes.

# The bindings, without the nodes, when matches do not free.
def N.binds.keep.if(drop: Bool, b: NBd, rest: List<&2, NBd>) -> List<&2, NBd>:
  match drop:
    case True{}:
      rest
    case False{}:
      b <> rest

def N.binds.keep(+free: Bool, bs: List<&2, NBd>) -> List<&2, NBd>:
  match bs:
    case Nil{}:
      Nil{}
    case NBd{+x, p} <> t:
      N.binds.keep.if(Bool.and(Bool.not(free), Gen.is_take(x)), NBd{x, p}, N.binds.keep(free, t))

# Each binding's operand, in order (where N.binds.env puts it).
def N.binds.ops(bs: List<&2, NBd>, +base: U32) -> NEnv():
  match bs:
    case Nil{}:
      Nil{}
    case NBd{x, p} <> t:
      match p:
        case NPO{o}:
          NB{x, o} <> N.binds.ops(t, base)
        case other:
          NB{x, NOS{base}} <> N.binds.ops(t, U32.inc(base))

def N.num(s: String, +acc: U32) -> U32:
  match s:
    case SCon{Chr{+c}, t}:
      N.num(t, ((acc * 10 : U32) + (c - 48 : U32) : U32))
    case SNil{}:
      acc

def N.is_slot(o: NO) -> Bool:
  match o:
    case NOS{s}:
      True{}
    case NOK{k}:
      False{}

def N.takes(bs: NEnv(), +kind: String) -> As.Code:
  match bs:
    case Nil{}:
      As.CNil{}
    case NB{+x, o} <> t:
      As.CCat{Bool.pick(As.Code, Str.eq(Gen.take.kind(x), kind),
        N.cat([N.lo(o, 0), N.k(1, N.num(Gen.take.words(x), 0)), N.call("bn_take")]), As.CNil{}), N.takes(t, kind)}

# bn_share(v), unless v is below 2^32 (a number: no node is).
def N.share(o: NO) -> As.Code:
  N.cat([N.lo(o, 0), N.ws([As.lsri(9, 0, 32), (As.cbz(9) .|. 64 : U32)]), N.call("bn_share")])

# bend_share for each variable body uses twice (a constant is no node, nor
# is a variable of sc: a number a pattern binds, as Gen.shares skips).
def N.shares(bs: NEnv(), +body: Core.Expr, +sc: List<&2, String>) -> As.Code:
  match bs:
    case Nil{}:
      As.CNil{}
    case NB{+x, +o} <> t:
      As.CCat{Bool.pick(As.Code, Bool.and(Bool.not(Bool.or(Bool.or(Gen.is_take(x), Str.eq(x, "_")), Str.has(sc, x))),
        Bool.and(N.is_slot(o), U32.is_le(2, Use.n(x, body)))), N.share(o), As.CNil{}),
        N.shares(t, body, sc)}

def N.shares.if(free: Bool, bs: NEnv(), +body: Core.Expr) -> As.Code:
  match free:
    case True{}:
      N.shares(bs, body, Nil{})
    case False{}:
      As.CNil{}

def N.shares.g(+g: G, bs: NEnv(), +body: Core.Expr) -> As.Code:
  N.shares.if(Gen.free(g), bs, body)

def N.open.go(bs: NEnv(), +body: Core.Expr, +sc: List<&2, String>) -> As.Code:
  +ops = bs
  N.cat([N.takes(ops, "%top"), N.takes(List.reverse(&2, NB, ops), "%sub"), N.shares(ops, body, sc)])

# Whether a pattern binds a number there: a Nat less k, a U32 or a Bool.
def N.pa.num(p: NPa) -> Bool:
  match p:
    case NPK{q, k}:
      True{}
    case NPW{q}:
      True{}
    case NPB{q}:
      True{}
    case other:
      False{}

def N.pa.nums(bs: List<&2, NBd>) -> List<&2, String>:
  match bs:
    case Nil{}:
      Nil{}
    case NBd{+x, p} <> +t:
      Bool.pick(List<&2, String>, N.pa.num(p), x <> N.pa.nums(t), N.pa.nums(t))

# After a pattern's bindings (from slot base up): its takes and shares.
def N.open.if(free: Bool, bs: List<&2, NBd>, +base: U32, +body: Core.Expr) -> As.Code:
  match free:
    case True{}:
      +bs2 = bs
      N.open.go(N.binds.ops(bs2, base), body, N.pa.nums(bs2))
    case False{}:
      As.CNil{}

def N.open(+g: G, bs: List<&2, NBd>, +base: U32, +body: Core.Expr) -> As.Code:
  N.open.if(Gen.free(g), bs, base, body)

# Operands
# --------

def N.simple.var(m: Maybe<&2, NO>, +x: String) -> Maybe<&2, NO>:
  match m:
    case Some{o}:
      Some{o}
    case None{}:
      Bool.pick(Maybe<&2, NO>, Str.eq(x, "_"), Some{NOK{0}}, None{})

def N.simple.flt(m: Maybe<&2, U32>) -> Maybe<&2, NO>:
  match m:
    case Some{+b}:
      Some{NOK{b}}
    case None{}:
      None{}

# An expression that needs no code: a variable in a slot, a constant (a
# float literal's bits among them).
def N.simple(+env: NEnv(), e: Core.Expr) -> Maybe<&2, NO>:
  match e:
    case Core.EVar{+x}:
      N.simple.var(NEnv.find(env, x), x)
    case Core.ENum{n}:
      Some{NOK{n}}
    case Core.ENat{n}:
      Some{NOK{n}}
    case Core.ETy{n, a}:
      Some{NOK{0}}
    case Core.EFlt{f}:
      N.simple.flt(Flt.bits(f))
    case other:
      None{}

def N.op.or(m: Maybe<&2, NO>, +s: U32) -> NO:
  match m:
    case Some{o}:
      o
    case None{}:
      NOS{s}

# The slot after base for arguments: the same for one that needs no code.
def N.next(+env: NEnv(), x: Core.Expr, +base: U32) -> U32:
  Bool.pick(U32, Maybe.is_some(&2, NO, N.simple(env, x)), base, U32.inc(base))

# The arguments that need code (each one gets a slot).
def N.cx(+env: NEnv(), xs: List<&2, Core.Expr>) -> U32:
  match xs:
    case Nil{}:
      0
    case +x <> t:
      (N.next(env, x, 0) + N.cx(env, t) : U32)

# A wide call's row (n > 8 arguments in memory): n slots, else none.
def N.wide(+n: U32) -> U32:
  Bool.pick(U32, U32.is_gt(n, 8), n, 0)

# The operands of arguments evaluated from slot base up (see NSArgs): the
# ones that need code in slots base, base + 1, ...
def N.ops(+env: NEnv(), xs: List<&2, Core.Expr>, +base: U32) -> List<&2, NO>:
  match xs:
    case Nil{}:
      Nil{}
    case +x <> t:
      N.op.or(N.simple(env, x), base) <> N.ops(env, t, N.next(env, x, base))

# Operands into slots base, base + 1, ... (a wide call's arguments in a row).
def N.row(os: List<&2, NO>, +base: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case o <> t:
      match o:
        case NOS{+s}:
          As.CCat{Bool.pick(As.Code, U32.is_eq(s, base), As.CNil{}, As.CCat{N.ld(9, s), N.st(9, base)}),
            N.row(t, U32.inc(base))}
        case NOK{+k}:
          N.cat([N.k(9, k), N.st(9, base), N.row(t, U32.inc(base))])

# Operands into the frame's memory at slots base, base + 1, ... (a wide
# call's row, which the callee reads through its address).
def N.row.mem(os: List<&2, NO>, +base: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case o <> t:
      N.cat([N.lo(o, 9), N.stx(9, (base * 8 : U32)), N.row.mem(t, U32.inc(base))])

def N.kept(mask: List<&2, Bool>) -> U32:
  match mask:
    case Nil{}:
      0
    case True{} <> t:
      U32.inc(N.kept(t))
    case False{} <> t:
      N.kept(t)

# A def's parameters: kept ones in slots 0, 1, ..., erased ones 0.
def N.params(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32, env: NEnv()) -> NEnv():
  match ps mask:
    case Core.Param{x, m, t} <> pt True{} <> mt:
      N.params(pt, mt, U32.inc(i), NB{x, NOS{i}} <> env)
    case Core.Param{x, m, t} <> pt False{} <> mt:
      N.params(pt, mt, i, NB{x, NOK{0}} <> env)
    case pl ml:
      env

# The kept parameters that may hold nodes (Gen.scalar.ty: not numbers).
def N.params.boxed(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32) -> NEnv():
  match ps mask:
    case Core.Param{x, m, +t} <> pt True{} <> mt:
      List.append(&2, NB, Bool.pick(NEnv(), Gen.scalar.ty(t), Nil{}, [NB{x, NOS{i}}]), N.params.boxed(pt, mt, U32.inc(i)))
    case Core.Param{x, m, t} <> pt False{} <> mt:
      N.params.boxed(pt, mt, i)
    case pl ml:
      Nil{}

# The prologue's stores of the parameters: from x0..x7, or from the row x0
# points at (a wide def).
def N.params.in(k: Nat, +i: U32, +wide: Bool) -> As.Code:
  match k:
    case 0n:
      As.CNil{}
    case 1n+j:
      As.CCat{Bool.pick(As.Code, wide, As.CCat{N.w(As.ldr(9, 0, (i * 8 : U32))), N.st(9, i)}, N.st(i, i)),
        N.params.in(j, U32.inc(i), wide)}

def N.split.kept(s: Split) -> List<&2, Core.Expr>:
  Split{kept, all, extra, full} = s
  kept

def N.split0(mask: List<&2, Bool>, args: List<&2, Core.Expr>) -> Split:
  Gen.split(mask, args, Split{Nil{}, Nil{}, Nil{}, False{}})

# Natives inlined: their operands in x0 and x1, their result in x0.
type NI is Data:
  NI{name: String, code: As.Code}

# BOOL(c) of the flags.
def N.bool(+c: U32) -> List<&2, U32>:
  [As.cset(0, c), As.lsli(0, 0, 3), As.orr1(0, 0)]

def N.fop(+w: U32) -> As.Code:
  N.ws([As.fmovsw(0, 0), As.fmovsw(1, 1), w, As.fmovws(0, 0)])

# Float trees
# -----------
#
# Nested F32 operations compute in FP registers, each node's value in the
# register of its depth (s0..s7, then s16..s27: s8..s15 are callee-saved),
# with no trip through x0 between them; their other operands are computed
# first, into slots, as a call's arguments are. Past depth 20 a node is an
# operand.

# 0..3: F32.add, sub, mul, div of two; 4: F32.neg of one; 5: x * k + b
# and 6: b + x * k, for a literal k that is a power of two (see N.ft.fma);
# 7: not a node.
def N.ft.arity(k: Nat, n: Nat) -> Nat:
  match k:
    case 4n:
      Bool.pick(Nat, Nat.is_eq(n, 1n), 4n, 7n)
    case 5n+q:
      7n
    case other:
      Bool.pick(Nat, Nat.is_eq(n, 2n), other, 7n)

# A float's bits, a power of two (its product with a normal float is exact
# when it is normal).
def N.ft.pow2(m: Maybe<&2, U32>) -> Bool:
  match m:
    case Some{+b}:
      +e = ((b >> 23n : U32) .&. 255 : U32)
      Bool.and(U32.is_zero((b .&. 8388607 : U32)), Bool.and(U32.is_ne(e, 0), U32.is_ne(e, 255)))
    case None{}:
      False{}

# Whether e is x * k, k such a literal.
def N.ft.mk(+env: NEnv(), e: Core.Expr) -> Bool:
  match e:
    case Core.ECall{Core.EVar{+f}, x <> Core.EFlt{s} <> Nil{}}:
      Bool.and(Bool.and(Str.eq(f, "F32.mul"), Bool.not(NEnv.has(env, f))), N.ft.pow2(Flt.bits(s)))
    case other:
      False{}

def N.ft.fused(k: Nat, +env: NEnv(), args: List<&2, Core.Expr>, +d: U32) -> Nat:
  match k:
    case 0n:
      match args:
        case a <> b <> Nil{}:
          Bool.pick(Nat, U32.is_ge(d, 18), 0n,
            Bool.pick(Nat, N.ft.mk(env, a), 5n, Bool.pick(Nat, N.ft.mk(env, b), 6n, 0n)))
        case other:
          0n
    case other:
      other

def N.ft.kind(+env: NEnv(), e: Core.Expr, +d: U32) -> Nat:
  match e:
    case Core.ECall{Core.EVar{+name}, +args}:
      Bool.pick(Nat, Bool.or(NEnv.has(env, name), U32.is_ge(d, 20)), 7n,
        N.ft.fused(N.ft.arity(P.which(name, ["F32.add", "F32.sub", "F32.mul", "F32.div", "F32.neg"]),
          List.length(&2, Core.Expr, args)), env, args, d))
    case other:
      7n

def N.ft.sreg(+d: U32) -> U32:
  Bool.pick(U32, U32.is_lt(d, 8), d, (d + 8 : U32))

def N.ft.push(simple: Bool, e: Core.Expr, acc: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match simple:
    case True{}:
      acc
    case False{}:
      e <> acc

# A tree's operands that need code, in order (n bounds the depth: a tree
# is no deeper than 21).
def N.ft.leaves(n: Nat, kind: Nat, +env: NEnv(), +e: Core.Expr, +d: U32, acc: List<&2, Core.Expr>) -> List<&2, Core.Expr>:
  match n:
    case 0n:
      acc
    case 1n+ +fu:
      match kind:
        case 7n+q:
          N.ft.push(Maybe.is_some(&2, NO, N.simple(env, e)), e, acc)
        case other:
          match e:
            case Core.ECall{f, +a <> +b <> Nil{}}:
              N.ft.leaves(fu, N.ft.kind(env, a, d), env, a, d,
                N.ft.leaves(fu, N.ft.kind(env, b, U32.inc(d)), env, b, U32.inc(d), acc))
            case Core.ECall{f, +a <> Nil{}}:
              N.ft.leaves(fu, N.ft.kind(env, a, d), env, a, d, acc)
            case other:
              acc

# How many of them there are.
def N.ft.count(n: Nat, kind: Nat, +env: NEnv(), +e: Core.Expr, +d: U32) -> U32:
  match n:
    case 0n:
      0
    case 1n+ +fu:
      match kind:
        case 7n+q:
          Bool.pick(U32, Maybe.is_some(&2, NO, N.simple(env, e)), 0, 1)
        case other:
          match e:
            case Core.ECall{f, +a <> +b <> Nil{}}:
              (N.ft.count(fu, N.ft.kind(env, a, d), env, a, d) +
                N.ft.count(fu, N.ft.kind(env, b, U32.inc(d)), env, b, U32.inc(d)) : U32)
            case Core.ECall{f, +a <> Nil{}}:
              N.ft.count(fu, N.ft.kind(env, a, d), env, a, d)
            case other:
              0

# Twins: a def that calls itself in tail position keeps its F32 parameters
# among the first 4 (bit i of tw for slot i) in s8 + i as well as in their
# slots, so a loop's float trees read and write them with no trip through
# the integer registers; a tail call to itself computes a float tree for
# such a parameter into s12 + i, then moves it to s8 + i and its slot. The
# def saves d8..d15.
def N.tw.bit(+tw: U32, +i: U32) -> Bool:
  Bool.and(U32.is_lt(i, 4), U32.is_ne((tw .&. U32.shln(1, U32.to_nat(i)) : U32), 0))

def N.twins(ps: List<&2, Core.Param>, mask: List<&2, Bool>, +i: U32) -> U32:
  match ps mask:
    case Core.Param{x, m, +t} <> pt True{} <> mt:
      (Bool.pick(U32, Bool.and(Str.eq(t, "F32"), U32.is_lt(i, 4)), U32.shln(1, U32.to_nat(i)), 0) .|.
        N.twins(pt, mt, U32.inc(i)) : U32)
    case Core.Param{x, m, t} <> pt False{} <> mt:
      N.twins(pt, mt, i)
    case pl ml:
      0

def N.tw.find(m: Maybe<&2, NO>) -> U32:
  match m:
    case Some{NOK{+k}}:
      k
    case other:
      0

# The def's twins, from the environment's "%fp" (lambdas have none).
def N.tw.get(+env: NEnv()) -> U32:
  N.tw.find(NEnv.find(env, "%fp"))

def N.tw.entry(k: Nat, +tw: U32, +i: U32) -> As.Code:
  match k:
    case 0n:
      As.CNil{}
    case 1n+q:
      As.CCat{Bool.pick(As.Code, N.tw.bit(tw, i), N.w(As.fmovsw((8 + i : U32), N.sreg(i))), As.CNil{}),
        N.tw.entry(q, tw, U32.inc(i))}

# Whether argument i of a tail call to itself is a float tree for a twin.
def N.tw.is(+env: NEnv(), e: Core.Expr, +tw: U32, +i: U32) -> Bool:
  Bool.and(N.tw.bit(tw, i), Nat.is_lt(N.ft.kind(env, e, 0), 7n))

# Those arguments as no code (they are computed apart).
def N.tw.strip(xs: List<&2, Core.Expr>, +env: NEnv(), +tw: U32, +i: U32) -> List<&2, Core.Expr>:
  match xs:
    case Nil{}:
      Nil{}
    case +e <> t:
      Bool.pick(Core.Expr, N.tw.is(env, e, tw, i), Core.ENum{0}, e) <> N.tw.strip(t, env, tw, U32.inc(i))

# ... and their operands as the parameters themselves (the move leaves them).
def N.tw.ops(os: List<&2, NO>, xs: List<&2, Core.Expr>, +env: NEnv(), +tw: U32, +i: U32) -> List<&2, NO>:
  match os xs:
    case o <> ot +e <> xt:
      Bool.pick(NO, N.tw.is(env, e, tw, i), NOS{i}, o) <> N.tw.ops(ot, xt, env, tw, U32.inc(i))
    case ol xl:
      Nil{}

def N.is_param(o: NO, +i: U32) -> Bool:
  match o:
    case NOS{+s}:
      U32.is_eq(s, i)
    case NOK{k}:
      False{}

def N.tw.fin1(+tree: Bool, +last: Bool, o: NO, +i: U32) -> As.Code:
  Bool.pick(As.Code, tree, Bool.pick(As.Code, last, N.w(As.fmovws(N.sreg(i), (8 + i : U32))),
    N.ws([As.fmovss((8 + i : U32), (12 + i : U32)), As.fmovws(N.sreg(i), (12 + i : U32))])),
    Bool.pick(As.Code, N.is_param(o, i), As.CNil{}, N.w(As.fmovsw((8 + i : U32), N.sreg(i)))))

# Whether no argument after the i-th is a float tree for a twin (the i-th's
# then goes to s8 + i at once: none reads it after).
def N.tw.last(xs: List<&2, Core.Expr>, +env: NEnv(), +tw: U32, +i: U32) -> Bool:
  match xs:
    case Nil{}:
      True{}
    case +e <> t:
      Bool.and(Bool.not(N.tw.is(env, e, tw, U32.inc(i))), N.tw.last(t, env, tw, U32.inc(i)))

# Where the i-th argument's tree goes (xs: the ones after it).
def N.tw.dst(xs: List<&2, Core.Expr>, +env: NEnv(), +tw: U32, +i: U32) -> U32:
  Bool.pick(U32, N.tw.last(xs, env, tw, i), (8 + i : U32), (12 + i : U32))

# After the move: each twin from s12 + i (a float tree's) or its slot.
def N.tw.fin(os: List<&2, NO>, xs: List<&2, Core.Expr>, +env: NEnv(), +tw: U32, +i: U32) -> As.Code:
  match os xs:
    case o <> ot +e <> +xt:
      As.CCat{Bool.pick(As.Code, N.tw.bit(tw, i), N.tw.fin1(N.tw.is(env, e, tw, i), N.tw.last(xt, env, tw, i), o, i),
        As.CNil{}), N.tw.fin(ot, xt, env, tw, U32.inc(i))}
    case ol xl:
      As.CNil{}

# s(d) = an operand (none for a twin: its FP register is read in place).
def N.ft.lo(o: NO, +d: U32, +tw: U32) -> As.Code:
  match o:
    case NOS{+s}:
      Bool.pick(As.Code, N.tw.bit(tw, s), As.CNil{},
        Bool.pick(As.Code, U32.is_lt(s, N.nregs()), N.w(As.fmovsw(N.ft.sreg(d), N.sreg(s))),
          As.CCat{N.ldx(9, (s * 8 : U32)), N.w(As.fmovsw(N.ft.sreg(d), 9))}))
    case NOK{+k}:
      As.CCat{N.k(9, k), N.w(As.fmovsw(N.ft.sreg(d), 9))}

def N.ft.reg.leaf(m: Maybe<&2, NO>, +d: U32, +tw: U32) -> U32:
  match m:
    case Some{NOS{+s}}:
      Bool.pick(U32, N.tw.bit(tw, s), (8 + s : U32), N.ft.sreg(d))
    case other:
      N.ft.sreg(d)

# The register an operand of depth d is in: s(d), or a twin's.
def N.ft.reg(kind: Nat, +env: NEnv(), e: Core.Expr, +d: U32, +tw: U32) -> U32:
  match kind:
    case 7n+q:
      N.ft.reg.leaf(N.simple(env, e), d, tw)
    case other:
      N.ft.sreg(d)

def N.ft.leaf(m: Maybe<&2, NO>, +d: U32, +k: U32, +tw: U32) -> As.Code:
  match m:
    case Some{o}:
      N.ft.lo(o, d, tw)
    case None{}:
      N.ft.lo(NOS{k}, d, tw)

# Whether a def's tail calls include one to itself.
def N.tails.self(es: List<&2, DEdge>, +name: String) -> Bool:
  match es:
    case Nil{}:
      False{}
    case DEdge{+to, c} <> t:
      Bool.or(Str.eq(to, name), N.tails.self(t, name))

# rd = rx * k + rb (rk holds k, a power of two, with biased exponent ke):
# one fmadd when rx * k is a normal float, for then the product is exact
# and fmadd rounds the sum as fadd would; else the two, as written (the
# C backend's F32_mulk_add). rx's exponent e is in range when e + ke - 127
# is in 1..254.
def N.ft.fma(+kb: U32, +rd: U32, +rx: U32, +rb: U32, +rk: U32) -> As.Code:
  +ke = ((kb >> 23n : U32) .&. 255 : U32)
  +lo = Bool.pick(U32, U32.is_lt(ke, 127), (128 - ke : U32), 1)
  +hi = Bool.pick(U32, U32.is_gt(ke, 127), (381 - ke : U32), 254)
  As.CCat{N.k(9, kb), N.ws([As.fmovsw(rk, 9), As.fmovws(9, rx), As.ubfxw(9, 9, 23, 8), As.subi(9, 9, lo),
    As.cmpi(9, (hi - lo : U32)), (As.bc(As.hi()) .|. 96 : U32), As.fmadd(rd, rx, rk, rb), (As.b() .|. 3 : U32),
    As.fmul(rk, rx, rk), As.fadd(rd, rk, rb)])}

def N.ft.ins(op: Nat, +rd: U32, +rn: U32, +rm: U32) -> U32:
  match op:
    case 0n:
      As.fadd(rd, rn, rm)
    case 1n:
      As.fsub(rd, rn, rm)
    case 2n:
      As.fmul(rd, rn, rm)
    case other:
      As.fdiv(rd, rn, rm)

# The tree's value into rd (a node below the root: s(d)), its operands
# that need code in slots k, k + 1, ... (a node's second operand's after its
# first's).
def N.ft.code(n: Nat, kind: Nat, +env: NEnv(), +e: Core.Expr, +d: U32, +k: U32, +tw: U32, +rd: U32) -> As.Code:
  match n:
    case 0n:
      As.CNil{}
    case 1n+ +fu:
      match kind:
        case 7n+q:
          N.ft.leaf(N.simple(env, e), d, k, tw)
        case 5n:
          match e:
            case Core.ECall{f, Core.ECall{m, +x <> Core.EFlt{ks} <> Nil{}} <> +b <> Nil{}}:
              +d1 = U32.inc(d)
              N.cat([N.ft.code(fu, N.ft.kind(env, x, d), env, x, d, k, tw, N.ft.sreg(d)),
                N.ft.code(fu, N.ft.kind(env, b, d1), env, b, d1, (k + N.ft.count(fu, N.ft.kind(env, x, d), env, x, d) : U32),
                  tw, N.ft.sreg(d1)),
                N.ft.fma(Maybe.default(&2, U32, Flt.bits(ks), 0), rd, N.ft.reg(N.ft.kind(env, x, d), env, x, d, tw),
                  N.ft.reg(N.ft.kind(env, b, d1), env, b, d1, tw), N.ft.sreg((d + 2 : U32)))])
            case other:
              As.CNil{}
        case 6n:
          match e:
            case Core.ECall{f, +a <> Core.ECall{m, +x <> Core.EFlt{ks} <> Nil{}} <> Nil{}}:
              +d1 = U32.inc(d)
              N.cat([N.ft.code(fu, N.ft.kind(env, a, d), env, a, d, k, tw, N.ft.sreg(d)),
                N.ft.code(fu, N.ft.kind(env, x, d1), env, x, d1, (k + N.ft.count(fu, N.ft.kind(env, a, d), env, a, d) : U32),
                  tw, N.ft.sreg(d1)),
                N.ft.fma(Maybe.default(&2, U32, Flt.bits(ks), 0), rd, N.ft.reg(N.ft.kind(env, x, d1), env, x, d1, tw),
                  N.ft.reg(N.ft.kind(env, a, d), env, a, d, tw), N.ft.sreg((d + 2 : U32)))])
            case other:
              As.CNil{}
        case 4n:
          match e:
            case Core.ECall{f, +a <> Nil{}}:
              As.CCat{N.ft.code(fu, N.ft.kind(env, a, d), env, a, d, k, tw, N.ft.sreg(d)),
                N.w(As.fneg(rd, N.ft.reg(N.ft.kind(env, a, d), env, a, d, tw)))}
            case other:
              As.CNil{}
        case +op:
          match e:
            case Core.ECall{f, +a <> +b <> Nil{}}:
              +d1 = U32.inc(d)
              N.cat([N.ft.code(fu, N.ft.kind(env, a, d), env, a, d, k, tw, N.ft.sreg(d)),
                N.ft.code(fu, N.ft.kind(env, b, d1), env, b, d1, (k + N.ft.count(fu, N.ft.kind(env, a, d), env, a, d) : U32),
                  tw, N.ft.sreg(d1)),
                N.w(N.ft.ins(op, rd, N.ft.reg(N.ft.kind(env, a, d), env, a, d, tw), N.ft.reg(N.ft.kind(env, b, d1), env, b, d1, tw)))])
            case other:
              As.CNil{}

def N.fcmp(+c: U32) -> As.Code:
  N.ws(As.fmovsw(0, 0) <> As.fmovsw(1, 1) <> As.fcmp(0, 1) <> N.bool(c))

def N.ucmp(+c: U32) -> As.Code:
  N.ws(As.cmp(0, 1) <> N.bool(c))

def N.inlines() -> List<&2, NI>:
  [NI{"U32.add", N.w(As.addw(0, 0, 1))}, NI{"U32.sub", N.w(As.subw(0, 0, 1))},
   NI{"U32.mul", N.w(As.mulw(0, 0, 1))}, NI{"U32.inc", As.CCat{N.k(1, 1), N.w(As.addw(0, 0, 1))}},
   NI{"U32.shrn", N.ws([As.cmpi(1, 32), As.lsrv(0, 0, 1), As.csel(0, 0, 31, As.lo())])},
   NI{"U32.shln", N.ws([As.cmpi(1, 32), As.lslvw(0, 0, 1), As.csel(0, 0, 31, As.lo())])},
   NI{"U32.and", N.w(As.and(0, 0, 1))}, NI{"U32.or", N.w(As.orr(0, 0, 1))}, NI{"U32.xor", N.w(As.eor(0, 0, 1))},
   NI{"U32.is_eq", N.ucmp(As.eq())}, NI{"U32.is_ne", N.ucmp(As.ne())}, NI{"U32.is_lt", N.ucmp(As.lo())},
   NI{"U32.is_le", N.ucmp(As.ls())}, NI{"U32.is_gt", N.ucmp(As.hi())}, NI{"U32.is_ge", N.ucmp(As.hs())},
   NI{"U32.is_zero", N.ws(As.cmpi(0, 0) <> N.bool(As.eq()))}, NI{"U32.to_nat", As.CNil{}},
   NI{"U32.to_f32", N.ws([As.ucvtf(0, 0), As.fmovws(0, 0)])},
   NI{"Nat.is_eq", N.ucmp(As.eq())}, NI{"Nat.is_ne", N.ucmp(As.ne())}, NI{"Nat.is_lt", N.ucmp(As.lo())},
   NI{"Nat.is_le", N.ucmp(As.ls())}, NI{"Nat.is_gt", N.ucmp(As.hi())}, NI{"Nat.is_ge", N.ucmp(As.hs())},
   NI{"Nat.add", N.cat([N.w(As.add(0, 0, 1)), N.ws(As.mov64(9, 4294967295, 65535)), N.w(As.cmp(0, 9)),
     N.w((As.bc(As.ls()) .|. 64 : U32)), N.call("nat_wall")])},
   NI{"Nat.sub", N.ws([As.cmp(0, 1), As.sub(0, 0, 1), As.csel(0, 0, 31, As.hi())])},
   NI{"F32.add", N.fop(As.fadd(0, 0, 1))}, NI{"F32.sub", N.fop(As.fsub(0, 0, 1))},
   NI{"F32.mul", N.fop(As.fmul(0, 0, 1))}, NI{"F32.div", N.fop(As.fdiv(0, 0, 1))},
   NI{"F32.is_eq", N.fcmp(As.eq())}, NI{"F32.is_ne", N.fcmp(As.ne())}, NI{"F32.is_lt", N.fcmp(As.mi())},
   NI{"F32.is_le", N.fcmp(As.ls())}, NI{"F32.is_gt", N.fcmp(As.gt())}, NI{"F32.is_ge", N.fcmp(As.ge())},
   NI{"F32.neg", N.ws([As.fmovsw(0, 0), As.fneg(0, 0), As.fmovws(0, 0)])}]

def N.inline.find(xs: List<&2, NI>, +name: String) -> Maybe<&2, As.Code>:
  match xs:
    case Nil{}:
      None{}
    case NI{+n, c} <> t:
      Bool.pick(Unit -> Maybe<&2, As.Code>, String.eq(n, name), u => Some{c}, u => N.inline.find(t, name))(Unit{})

# A native whose second operand is a constant k, as one instruction on x0:
# U32.shrn and U32.shln by k, U32.mul by a power of two, U32.add and
# U32.sub of k below 4096.
def N.inline.kc(w: Nat, +k: U32) -> Maybe<&2, As.Code>:
  match w:
    case 0n:
      Some{Bool.pick(As.Code, U32.is_lt(k, 32), N.w(As.lsri(0, 0, k)), N.k(0, 0))}
    case 1n:
      Some{Bool.pick(As.Code, U32.is_lt(k, 32), N.w(As.lslwi(0, 0, k)), N.k(0, 0))}
    case 2n:
      Bool.pick(Maybe<&2, As.Code>, Bool.and(U32.is_ne(k, 0), U32.is_zero((k .&. (k - 1 : U32) : U32))),
        Some{N.w(As.lslwi(0, 0, U32.from_nat(U32.log2(k))))}, None{})
    case 3n:
      Bool.pick(Maybe<&2, As.Code>, U32.is_lt(k, 4096), Some{N.w(As.addwi(0, 0, k))}, None{})
    case 4n:
      Bool.pick(Maybe<&2, As.Code>, U32.is_lt(k, 4096), Some{N.w(As.subwi(0, 0, k))}, None{})
    case other:
      None{}

def N.inline.kop(+name: String, m: Maybe<&2, NO>) -> Maybe<&2, As.Code>:
  match m:
    case Some{NOK{+k}}:
      N.inline.kc(P.which(name, ["U32.shrn", "U32.shln", "U32.mul", "U32.add", "U32.sub"]), k)
    case other:
      None{}

def N.inline.k(native: Bool, +name: String, +env: NEnv(), xs: List<&2, Core.Expr>) -> Maybe<&2, As.Code>:
  match native:
    case True{}:
      match xs:
        case a <> b <> Nil{}:
          N.inline.kop(name, N.simple(env, b))
        case other:
          None{}
    case False{}:
      None{}

def N.inline.or(m: Maybe<&2, As.Code>, +w: U32, +name: String) -> As.Code:
  match m:
    case Some{c}:
      c
    case None{}:
      N.one(As.ICall{w, "N_" ++ Gen.mangle(name)})

# A call's branch: to a native's name in rt/native.c, or to a def here.
def N.target(native: Bool, +w: U32, +name: String) -> As.Code:
  match native:
    case True{}:
      N.one(As.ICall{w, "N_" ++ Gen.mangle(name)})
    case False{}:
      N.one(As.IB{w, Gen.f(name)})

# A call: a native inlined when it can be (its code in place of the branch).
def N.ncall(native: Bool, +name: String, sym: String) -> As.Code:
  match native:
    case True{}:
      N.inline.or(N.inline.find(N.inlines(), name), As.bl(), name)
    case False{}:
      N.one(As.IB{As.bl(), sym})

def N.fsym.pick(m: Maybe<&2, String>, +name: String) -> String:
  match m:
    case Some{+v}:
      Bool.pick(String, Str.eq(v, name), "S_" ++ Gen.mangle(name), Gen.f(name))
    case None{}:
      Gen.f(name)

# A def's symbol: F_name, or S_name inside S_name's code (Gen.def.seq).
def N.fsym(+name: String) -> NG(String):
  do NG<String>:
    m : Maybe<&2, String> <- N.memo.find("%seqmode")
    return N.fsym.pick(m, name)

def N.ntail.go(m: Maybe<&2, As.Code>, +name: String) -> As.Code:
  match m:
    case Some{c}:
      As.CCat{c, N.epilogue()}
    case None{}:
      As.CCat{N.pop(), N.one(As.ICall{As.b(), "N_" ++ Gen.mangle(name)})}

# A tail call's end: an inlined native, then the epilogue; else pop the frame
# and branch.
def N.ntail(native: Bool, +name: String, sym: String) -> As.Code:
  match native:
    case True{}:
      N.ntail.go(N.inline.find(N.inlines(), name), name)
    case False{}:
      As.CCat{N.pop(), N.one(As.IB{As.b(), sym})}

# The operands of a call into x0..x7, or (a wide call) into the row from
# slot base up, whose address goes in x0.
def N.callops(+os: List<&2, NO>, +base: U32, +row: U32, +n: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_le(n, 8), N.lregs.b(os, base), As.CCat{N.row.mem(os, row), N.addk(0, 31, (row * 8 : U32))})

def N.first(os: List<&2, NO>) -> List<&2, NO>:
  match os:
    case o <> t:
      [o]
    case Nil{}:
      Nil{}

# The call itself: one of those, or N.ncall.
def N.callk(m: Maybe<&2, As.Code>, +os: List<&2, NO>, +base: U32, +row: U32, +n: U32, native: Bool, +name: String,
  sym: String
) -> As.Code:
  match m:
    case Some{c}:
      As.CCat{N.lregs.b(N.first(os), base), c}
    case None{}:
      As.CCat{N.callops(os, base, row, n), N.ncall(native, name, sym)}

# The same in tail position.
def N.tailk(m: Maybe<&2, As.Code>, +os: List<&2, NO>, +base: U32, native: Bool, +name: String, sym: String) -> As.Code:
  match m:
    case Some{c}:
      N.cat([N.lregs.b(N.first(os), base), c, N.epilogue()])
    case None{}:
      As.CCat{N.lregs.b(os, base), N.ntail(native, name, sym)}

def N.fin(t: NT) -> As.Code:
  match t:
    case NTRet{}:
      N.epilogue()
    case NTSet{+s, j}:
      As.CCat{N.st(0, s), N.b(j)}
    case NTDst{+d, id}:
      N.cat([N.ld(9, d), N.w(As.str(0, 9, 0)), N.epilogue()])

def N.is_ret(t: NT) -> Bool:
  match t:
    case NTRet{}:
      True{}
    case NTSet{s, j}:
      False{}
    case NTDst{d, id}:
      True{}

def N.dst.slot(t: NT) -> U32:
  match t:
    case NTDst{d, id}:
      d
    case other:
      0

# Destination passing (Dps, as the C backend does it: Gen.def.dst). D_name
# takes its parameters in x0..x7 and dst in x8, and stores its result
# through dst; a constructor node with a field that is a call to the group
# is stored with BEND_HOLE there, and dst moves to that field before the
# call (a jump). A group whose members take more than 8 parameters has
# none here.
def N.dps.go(g: DGrp) -> String:
  DGrp{+id, +n} = g
  Bool.pick(String, U32.is_le(n, 8), id, "")

def N.dps(+g: G, +name: String) -> String:
  N.dps.go(G.dps(g, name))

# Whether a call in a D_ function's tail jumps to a D_ function: name is of
# the group, applied to all its parameters.
def N.dst.call(+g: G, +env: NEnv(), +tgt: NT, +name: String, +args: List<&2, Core.Expr>) -> Bool:
  match tgt:
    case NTDst{d, +id}:
      Bool.and(Str.eq(id, N.dps(g, name)), Bool.and(Bool.not(NEnv.has(env, name)),
        Nat.is_eq(List.length(&2, Bool, DInfo.mask(G.def(g, name))), List.length(&2, Core.Expr, args))))
    case other:
      False{}

def N.dst.hole.at(+g: G, +env: NEnv(), +tgt: NT, a: Core.Expr, +i: U32, acc: U32) -> U32:
  match a:
    case Core.ECall{Core.EVar{+h}, +hargs}:
      Bool.pick(U32, N.dst.call(g, env, tgt, h, hargs), U32.inc(i), acc)
    case other:
      acc

# The field of a constructor node left as a hole: the last one that is a
# call to the group (1-based; 0 when there is none).
def N.dst.hole(+g: G, +env: NEnv(), +tgt: NT, node: Bool, as: List<&2, Core.Expr>, +i: U32, acc: U32) -> U32:
  match node as:
    case True{} a <> t:
      N.dst.hole(g, env, tgt, True{}, t, U32.inc(i), N.dst.hole.at(g, env, tgt, a, i, acc))
    case n l:
      acc

# The fields with the hole's (the i-th, from 1) as BEND_HOLE (IMM(0x7ffff)).
def N.dst.fields(as: List<&2, Core.Expr>, +i: U32, +hole: U32) -> List<&2, Core.Expr>:
  match as:
    case Nil{}:
      Nil{}
    case a <> t:
      Bool.pick(Core.Expr, U32.is_eq(i, hole), Core.ENum{4194297}, a) <> N.dst.fields(t, U32.inc(i), hole)

# x0 = a node with a hole: its tag word holds BEND_HOLE until its fields are
# in (bn_alloc_hole, as CH2 and the like do).
def N.hnode(+tag: U32, +os: List<&2, NO>) -> As.Code:
  N.cat([N.alloc.hole(U32.inc(U32.from_nat(List.length(&2, NO, os)))), N.fields(os, 8), N.k(9, tag),
    N.w(As.str(9, 0, 0))])

# F_name: D_name with dst at a cell of its frame, then the cell.
def N.dst.entry(+m: String, +f: String) -> As.Code:
  N.cat([N.one(As.ISym{f, False{}}),
    N.ws([As.push_fp(), As.set_fp(), As.subi(31, 31, 16), As.str(31, 31, 0), As.addi(8, 31, 0)]),
    N.one(As.IB{As.bl(), "D_" ++ m}), N.ws([As.ldr(0, 31, 0), As.sp_fp(), As.pop_fp(), As.ret()])])

def N.is_tail(+env: NEnv(), +self: NSelf, +tgt: NT, +name: String, +args: List<&2, Core.Expr>) -> Bool:
  NSelf{+sn, +mask, top} = self
  Bool.and(Bool.and(N.is_ret(tgt), Str.eq(sn, name)), Bool.and(
    Bool.not(NEnv.has(env, name)),
    Nat.is_eq(List.length(&2, Bool, mask), List.length(&2, Core.Expr, args))))

def N.can_tail.info(i: DInfo, +n: Nat) -> Bool:
  DInfo{+kind, +mask} = i
  Bool.and(Bool.and(U32.is_le(kind, 2), Nat.is_eq(List.length(&2, Bool, mask), n)), U32.is_le(N.kept(mask), 8))

# A call in tail position that can pop the frame and branch: to a narrow
# def, with all its arguments.
def N.can_tail(+g: G, +env: NEnv(), +name: String, +args: List<&2, Core.Expr>) -> Bool:
  Bool.and(Bool.and(Bool.not(NEnv.has(env, name)), Bool.not(Str.eq(name, "%gpu"))),
    N.can_tail.info(G.def(g, name), List.length(&2, Core.Expr, args)))

# Slots i, i + 1, ... as operands.
def N.seq(k: Nat, +i: U32) -> List<&2, NO>:
  match k:
    case 0n:
      Nil{}
    case 1n+j:
      NOS{i} <> N.seq(j, U32.inc(i))

# Slot from + i into slot to + i, for k of them.
def N.copy(k: Nat, +from: U32, +to: U32) -> As.Code:
  match k:
    case 0n:
      As.CNil{}
    case 1n+j:
      N.cat([N.ld(9, from), N.st(9, to), N.copy(j, U32.inc(from), U32.inc(to))])

# A parallel move of operands into parameters 0..n-1 (slots 0..n-1): the
# ones read from another parameter go through x0..x7, all read first;
# a parameter that stays is left; the rest are written in place.
def N.pm.kind(o: NO, +n: U32, +i: U32) -> U32:
  match o:
    case NOS{+s}:
      Bool.pick(U32, U32.is_eq(s, i), 1, Bool.pick(U32, U32.is_lt(s, n), 0, 2))
    case NOK{k}:
      2

def N.pm.read(os: List<&2, NO>, +n: U32, +i: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case +o <> t:
      As.CCat{Bool.pick(As.Code, U32.is_zero(N.pm.kind(o, n, i)), N.lo(o, i), As.CNil{}), N.pm.read(t, n, U32.inc(i))}

# Slot i = operand o, register to register when both are.
def N.pm.put(o: NO, +i: U32) -> As.Code:
  match o:
    case NOS{+s}:
      Bool.pick(As.Code, Bool.and(U32.is_lt(s, N.nregs()), U32.is_lt(i, N.nregs())), N.mov(N.sreg(i), N.sreg(s)),
        As.CCat{N.ld(9, s), N.st(9, i)})
    case NOK{+k}:
      Bool.pick(As.Code, U32.is_lt(i, N.nregs()), N.k(N.sreg(i), k), As.CCat{N.k(9, k), N.st(9, i)})

def N.pm.direct(os: List<&2, NO>, +n: U32, +i: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case +o <> t:
      As.CCat{Bool.pick(As.Code, U32.is_eq(N.pm.kind(o, n, i), 2), N.pm.put(o, i), As.CNil{}), N.pm.direct(t, n, U32.inc(i))}

def N.pm.write(os: List<&2, NO>, +n: U32, +i: U32) -> As.Code:
  match os:
    case Nil{}:
      As.CNil{}
    case +o <> t:
      As.CCat{Bool.pick(As.Code, U32.is_zero(N.pm.kind(o, n, i)), N.st(i, i), As.CNil{}), N.pm.write(t, n, U32.inc(i))}

# The new arguments of a tail call to itself over the parameters: a
# parallel move, or (past 8) through the temporaries.
def N.tail.move(+os: List<&2, NO>, +base: U32, +row: U32, +n: U32) -> As.Code:
  Bool.pick(As.Code, U32.is_le(n, 8), N.cat([N.pm.read(os, n, 0), N.pm.direct(os, n, 0), N.pm.write(os, n, 0)]),
    As.CCat{N.row(os, row), N.copy(U32.to_nat(n), row, 0)})

# A constructor's value from its fields' operands, by kind (see G.ctor_kind).
def N.ctor.code(kind: Nat, +tag: U32, +os: List<&2, NO>) -> As.Code:
  match kind:
    case 0n:
      +n = U32.from_nat(List.length(&2, NO, os))
      N.cat([N.alloc(U32.inc(n)), N.k(9, tag), N.w(As.str(9, 0, 0)), N.fields(os, 8)])
    case 1n:
      N.k(0, N.imm(tag))
    case 2n:
      N.lregs(os, 0)
    case 3n:
      N.k(0, 0)
    case 4n:
      As.CCat{N.lregs(os, 0), N.natk(1)}
    case 5n:
      N.cat([N.lregs(os, 1), N.k(0, 0), N.call("arr_new")])
    case 6n+q:
      As.CCat{N.lregs(os, 0), N.call("arr_node")}

def N.caps.put(x: String, m: Maybe<&2, NO>, rest: NEnv()) -> NEnv():
  match m:
    case None{}:
      rest
    case Some{o}:
      NB{x, o} <> rest

# A lambda's captures: the free variables the environment has.
def N.caps(names: List<&2, String>, +env: NEnv()) -> NEnv():
  match names:
    case Nil{}:
      Nil{}
    case +x <> t:
      N.caps.put(x, NEnv.find(env, x), N.caps(t, env))

def N.caps.inner(caps: NEnv(), +i: U32) -> NEnv():
  match caps:
    case Nil{}:
      Nil{}
    case NB{x, o} <> t:
      NB{x, NOS{i}} <> N.caps.inner(t, U32.inc(i))

def N.caps.ops(caps: NEnv()) -> List<&2, NO>:
  match caps:
    case Nil{}:
      Nil{}
    case NB{x, o} <> t:
      o <> N.caps.ops(t)

def NPr.binds(r: NPr) -> List<&2, NBd>:
  NPr{conds, binds} = r
  binds

def NPr.conds(r: NPr) -> List<&2, NCo>:
  NPr{conds, binds} = r
  List.reverse(&2, NCo, conds)

def NPr.none() -> NPr:
  NPr{Nil{}, Nil{}}

# The generator is one def, N.rec, over a selector, as Gen.rec: each NS..
# names a step and carries its arguments; every step gives code. Fuel
# bounds the recursion.
type NS is Data:
  NSExpr{g: G, env: NEnv(), e: Core.Expr}
  NSVarFound{g: G, name: String, m: Maybe<&2, NO>}
  NSVar{g: G, name: String, info: DInfo}
  NSVarKind{name: String, kind: Nat, total: U32}
  NSArg{g: G, env: NEnv(), x: Core.Expr, base: U32, m: Maybe<&2, NO>}
  NSArgs{g: G, env: NEnv(), xs: List<&2, Core.Expr>, base: U32}
  NSApp{g: G, env: NEnv(), xs: List<&2, Core.Expr>, r: U32}
  NSApply{g: G, env: NEnv(), f: Core.Expr, args: List<&2, Core.Expr>}
  NSCallFull{g: G, env: NEnv(), name: String, native: Bool, mask: List<&2, Bool>, kept: List<&2, Core.Expr>,
    all: List<&2, Core.Expr>, extra: List<&2, Core.Expr>, full: Bool}
  NSCallSplit{g: G, env: NEnv(), name: String, native: Bool, mask: List<&2, Bool>, s: Split}
  NSCallKind{g: G, env: NEnv(), name: String, kind: Nat, mask: List<&2, Bool>, args: List<&2, Core.Expr>}
  NSCallDef{g: G, env: NEnv(), name: String, info: DInfo, args: List<&2, Core.Expr>}
  NSCallVar{g: G, env: NEnv(), name: String, args: List<&2, Core.Expr>, local: Bool}
  NSCallGpu{g: G, env: NEnv(), args: List<&2, Core.Expr>}
  NSCallName{g: G, env: NEnv(), name: String, args: List<&2, Core.Expr>, gpu: Bool}
  NSCall{g: G, env: NEnv(), f: Core.Expr, args: List<&2, Core.Expr>}
  NSCallF{ft: Bool, g: G, env: NEnv(), f: Core.Expr, args: List<&2, Core.Expr>}
  NSFloat{g: G, env: NEnv(), e: Core.Expr}
  NSFloatS{g: G, env: NEnv(), e: Core.Expr, rd: U32}
  NSTwins{g: G, env: NEnv(), xs: List<&2, Core.Expr>, tw: U32, i: U32}
  NSTwin{ok: Bool, g: G, env: NEnv(), e: Core.Expr, r: U32}
  NSBitsGo{g: G, env: NEnv(), k: Nat, e: Core.Expr}
  NSBits{g: G, env: NEnv(), e: Core.Expr}
  NSCtorBits{g: G, env: NEnv(), args: List<&2, Core.Expr>}
  NSCtorGo{g: G, env: NEnv(), tag: U32, kind: U32, args: List<&2, Core.Expr>}
  NSCtorKind{g: G, env: NEnv(), tag: U32, kind: U32, args: List<&2, Core.Expr>, w: Nat}
  NSCtorInfo{g: G, env: NEnv(), name: String, info: Maybe<&2, CInfo>, args: List<&2, Core.Expr>}
  NSCtor{g: G, env: NEnv(), name: String, args: List<&2, Core.Expr>}
  NSLam{g: G, env: NEnv(), p: Core.Pat, body: Core.Expr}
  NSBlock{g: G, env: NEnv(), e: Core.Expr}
  NSTailSelf{g: G, env: NEnv(), self: NSelf, args: List<&2, Core.Expr>}
  NSTailGo{g: G, env: NEnv(), name: String, info: DInfo, args: List<&2, Core.Expr>}
  NSTailCall{g: G, env: NEnv(), name: String, args: List<&2, Core.Expr>, ok: Bool}
  NSStmtCallTo{g: G, env: NEnv(), tgt: NT, name: String, args: List<&2, Core.Expr>}
  NSStmtCall{g: G, env: NEnv(), self: NSelf, tgt: NT, name: String, args: List<&2, Core.Expr>, tail: Bool}
  NSDstCall{g: G, env: NEnv(), d: U32, id: String, name: String, args: List<&2, Core.Expr>, ok: Bool}
  NSStmtCtor{none: Bool, g: G, env: NEnv(), self: NSelf, tgt: NT, name: String, args: List<&2, Core.Expr>,
    hole: U32}
  NSLetVar{g: G, env: NEnv(), self: NSelf, tgt: NT, x: String, v: Core.Expr, body: Core.Expr, m: Maybe<&2, NO>}
  NSLetHole{g: G, env: NEnv(), self: NSelf, tgt: NT, v: Core.Expr, body: Core.Expr}
  NSLetPat{g: G, env: NEnv(), self: NSelf, tgt: NT, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  NSLets{g: G, env0: NEnv(), env: NEnv(), self: NSelf, tgt: NT, ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>,
    body: Core.Expr}
  NSLetPar{g: G, env: NEnv(), self: NSelf, tgt: NT, ps: List<&2, Core.Pat>, v: Core.Expr, body: Core.Expr}
  NSPar{g: G, env: NEnv(), self: NSelf, tgt: NT, ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>, body: Core.Expr}
  NSParPick{mode: Nat, g: G, env: NEnv(), self: NSelf, tgt: NT, ps: List<&2, Core.Pat>, vs: List<&2, Core.Expr>,
    body: Core.Expr}
  NSParSq{sq: Bool, g: G, env: NEnv(), sn: String, prev: String, s: U32, vs: List<&2, Core.Expr>}
  NSParSeq{g: G, env: NEnv(), s: U32, vs: List<&2, Core.Expr>}
  NSParVals{g: G, env: NEnv(), s: U32, vs: List<&2, Core.Expr>}
  NSParBind{g: G, env: NEnv(), self: NSelf, tgt: NT, ps: List<&2, Core.Pat>, s: U32, body: Core.Expr}
  NSLetCtor{g: G, env: NEnv(), self: NSelf, tgt: NT, name: String, ps: List<&2, Core.Pat>, v: Core.Expr,
    body: Core.Expr, par: Bool}
  NSLet{g: G, env: NEnv(), self: NSelf, tgt: NT, p: Core.Pat, v: Core.Expr, body: Core.Expr}
  NSCaseGo{g: G, env: NEnv(), self: NSelf, tgt: NT, os: List<&2, NO>, cs: List<&2, NCo>,
    binds: List<&2, NBd>, body: Core.Expr, rest: List<&2, Core.Expr>}
  NSCases{g: G, env: NEnv(), self: NSelf, tgt: NT, os: List<&2, NO>, cases: List<&2, Core.Expr>}
  NSMatch{g: G, env: NEnv(), self: NSelf, tgt: NT, scrs: List<&2, Core.Expr>, cases: List<&2, Core.Expr>}
  NSStmt{g: G, env: NEnv(), self: NSelf, tgt: NT, e: Core.Expr}

def NS.starve() -> NG(As.Code):
  do NG<As.Code>:
    N.error("out of fuel")
    return As.CNil{}

def N.rec(n: Nat, k: NS) -> NG(As.Code):
  match n:
    case 0n:
      NS.starve()
    case 1n+ +fu:
      match k:
        case NSExpr{+g, +env, e}:
          match e:
            case Core.EVar{+name}:
              N.rec(fu, NSVarFound{g, name, N.simple(env, Core.EVar{name})})
            case Core.ENum{+n}:
              NG.pure(As.Code, N.k(0, n))
            case Core.ENat{+n}:
              NG.pure(As.Code, N.k(0, n))
            case Core.EFlt{s}:
              N.flt(s)
            case Core.EStr{s}:
              N.str(s)
            case Core.ECall{+f, +args}:
              do NG<As.Code>:
                +m : U32 <- N.mark()
                c : As.Code <- N.rec(fu, NSCallF{Nat.is_lt(N.ft.kind(env, Core.ECall{f, args}, 0), 7n), g, env, f, args})
                N.release(m)
                return c
            case Core.ECtor{name, args}:
              do NG<As.Code>:
                +m : U32 <- N.mark()
                c : As.Code <- N.rec(fu, NSCtor{g, env, name, args})
                N.release(m)
                return c
            case Core.ELam{p, body}:
              N.rec(fu, NSLam{g, env, p, body})
            case Core.ELet{p, v, body}:
              N.rec(fu, NSBlock{g, env, Core.ELet{p, v, body}})
            case Core.EMatch{scrs, cases}:
              N.rec(fu, NSBlock{g, env, Core.EMatch{scrs, cases}})
            case Core.ESucc{+j, x}:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, x})
                return As.CCat{c, N.natk(j)}
            case Core.ETy{n, targs}:
              NG.pure(As.Code, N.k(0, 0))
            case Core.EErr{m}:
              do NG<As.Code>:
                N.error("parse error: " ++ m)
                return As.CNil{}
            case other:
              do NG<As.Code>:
                N.error("unexpected expression: " ++ Expr.show(other))
                return As.CNil{}
        case NSVarFound{+g, +name, m}:
          match m:
            case Some{o}:
              NG.pure(As.Code, N.lo(o, 0))
            case None{}:
              N.rec(fu, NSVar{g, name, G.def(g, name)})
        case NSVar{+g, +name, info}:
          match info:
            case DInfo{kind, mask}:
              N.rec(fu, NSVarKind{name, U32.to_nat(kind), U32.from_nat(List.length(&2, Bool, mask))})
        case NSVarKind{+name, kind, +total}:
          match kind:
            case 3n:
              NG.pure(As.Code, N.k(0, 0))
            case 4n:
              do NG<As.Code>:
                N.error("unknown name: " ++ name)
                return As.CNil{}
            case other:
              do NG<As.Code>:
                N.ref(name)
                return Bool.pick(As.Code, U32.is_zero(total), N.target(Nat.is_eq(other, 2n), As.bl(), name),
                  N.clo(Gen.w(name), total, Nil{}))
        case NSArg{+g, +env, x, +base, m}:
          match m:
            case Some{o}:
              NG.pure(As.Code, As.CNil{})
            case None{}:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, x})
                return As.CCat{c, N.st(0, base)}
        case NSArgs{+g, +env, xs, +base}:
          match xs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case +x <> t:
              do NG<As.Code>:
                a : As.Code <- N.rec(fu, NSArg{g, env, x, base, N.simple(env, x)})
                b : As.Code <- N.rec(fu, NSArgs{g, env, t, N.next(env, x, base)})
                return As.CCat{a, b}
        # Applies the value in x0 (kept in slot r) to each argument.
        case NSApp{+g, +env, xs, +r}:
          match xs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case x <> t:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, x})
                rest : As.Code <- N.rec(fu, NSApp{g, env, t, r})
                return N.cat([N.st(0, r), c, N.w(As.mov(1, 0)), N.ld(0, r), N.call("apply"), rest])
        case NSApply{+g, +env, f, args}:
          do NG<As.Code>:
            +r : U32 <- N.slots(1)
            c : As.Code <- N.rec(fu, NSExpr{g, env, f})
            x : As.Code <- N.rec(fu, NSApp{g, env, args, r})
            return As.CCat{c, x}
        case NSCallFull{+g, +env, +name, +native, +mask, +kept, +all, extra, full}:
          match full:
            case True{}:
              +n = U32.from_nat(List.length(&2, Core.Expr, kept))
              do NG<As.Code>:
                +base : U32 <- N.slots(N.cx(env, kept))
                a : As.Code <- N.rec(fu, NSArgs{g, env, kept, base})
                +row : U32 <- N.slots(N.wide(n))
                +r : U32 <- N.slots(1)
                x : As.Code <- N.rec(fu, NSApp{g, env, extra, r})
                sym : String <- N.fsym(name)
                return N.cat([a, N.callk(N.inline.k(native, name, env, kept), N.ops(env, kept, base), base, row, n, native,
                  name, sym), x])
            case False{}:
              do NG<As.Code>:
                +base : U32 <- N.slots(N.cx(env, all))
                a : As.Code <- N.rec(fu, NSArgs{g, env, all, base})
                return As.CCat{a, N.clo(Gen.w(name), U32.from_nat(List.length(&2, Bool, mask)), N.ops(env, all, base))}
        case NSCallSplit{+g, +env, +name, +native, +mask, s}:
          match s:
            case Split{kept, all, extra, full}:
              N.rec(fu, NSCallFull{g, env, name, native, mask, kept, all, extra, full})
        case NSCallKind{+g, +env, +name, kind, +mask, +args}:
          match kind:
            case 3n:
              NG.pure(As.Code, N.k(0, 0))
            case 4n:
              do NG<As.Code>:
                N.error("unknown function: " ++ name)
                return As.CNil{}
            case other:
              do NG<As.Code>:
                N.ref(name)
                N.rec(fu, NSCallSplit{g, env, name, Nat.is_eq(other, 2n), mask, N.split0(mask, args)})
        case NSCallDef{+g, +env, +name, info, args}:
          match info:
            case DInfo{kind, mask}:
              N.rec(fu, NSCallKind{g, env, name, U32.to_nat(kind), mask, args})
        case NSCallVar{+g, +env, +name, args, local}:
          match local:
            case True{}:
              N.rec(fu, NSApply{g, env, Core.EVar{name}, args})
            case False{}:
              N.rec(fu, NSCallDef{g, env, name, G.def(g, name), args})
        # f!(args) runs on the CPU here.
        case NSCallGpu{+g, +env, args}:
          match args:
            case f <> xs:
              N.rec(fu, NSCall{g, env, f, xs})
            case Nil{}:
              NG.pure(As.Code, N.k(0, 0))
        case NSCallName{+g, +env, +name, args, gpu}:
          match gpu:
            case True{}:
              N.rec(fu, NSCallGpu{g, env, args})
            case False{}:
              N.rec(fu, NSCallVar{g, env, name, args, NEnv.has(env, name)})
        case NSCallF{ft, +g, +env, f, args}:
          match ft:
            case True{}:
              N.rec(fu, NSFloat{g, env, Core.ECall{f, args}})
            case False{}:
              N.rec(fu, NSCall{g, env, f, args})
        # A tree of float operations: its other operands that need code into
        # slots, then the tree in FP registers (N.ft.code).
        case NSFloat{+g, +env, e}:
          do NG<As.Code>:
            c : As.Code <- N.rec(fu, NSFloatS{g, env, e, 0})
            return As.CCat{c, N.w(As.fmovws(0, 0))}
        case NSFloatS{+g, +env, +e, +rd}:
          +ls = N.ft.leaves(24n, N.ft.kind(env, e, 0), env, e, 0, Nil{})
          do NG<As.Code>:
            +base : U32 <- N.slots(U32.from_nat(List.length(&2, Core.Expr, ls)))
            a : As.Code <- N.rec(fu, NSArgs{g, env, ls, base})
            return As.CCat{a, N.ft.code(24n, N.ft.kind(env, e, 0), env, e, 0, base, N.tw.get(env), rd)}
        # A tail call's float trees for twins, each into s12 + i.
        case NSTwins{+g, +env, xs, +tw, +i}:
          match xs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case +e <> +t:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSTwin{N.tw.is(env, e, tw, i), g, env, e, N.tw.dst(t, env, tw, i)})
                r : As.Code <- N.rec(fu, NSTwins{g, env, t, tw, U32.inc(i)})
                return As.CCat{c, r}
        case NSTwin{ok, +g, +env, e, +r}:
          match ok:
            case True{}:
              N.rec(fu, NSFloatS{g, env, e, r})
            case False{}:
              NG.pure(As.Code, As.CNil{})
        case NSCall{+g, +env, f, args}:
          match f:
            case Core.EVar{+name}:
              N.rec(fu, NSCallName{g, env, name, args, Str.eq(name, "%gpu")})
            case other:
              N.rec(fu, NSApply{g, env, other, args})
        # U32{..} and F32{..} of a word's structural view: word_con, as the C
        # backend's (the head's low bit, the tail shifted up).
        case NSBitsGo{+g, +env, k, e}:
          match k:
            case 0n:
              match e:
                case Core.ECtor{c, a <> b <> Nil{}}:
                  do NG<As.Code>:
                    +r : U32 <- N.slots(1)
                    cb : As.Code <- N.rec(fu, NSBits{g, env, b})
                    ca : As.Code <- N.rec(fu, NSExpr{g, env, a})
                    return N.cat([cb, N.st(0, r), ca, N.k(9, 9), N.w(As.cmp(0, 9)), N.w(As.cset(0, As.eq())),
                      N.ld(9, r), N.ws([As.lsli(9, 9, 1), As.ubfm(9, 9, 0, 31), As.orr(0, 0, 9)])])
                case other:
                  N.rec(fu, NSExpr{g, env, other})
            case 1n:
              NG.pure(As.Code, N.k(0, 0))
            case 2n+q:
              N.rec(fu, NSExpr{g, env, e})
        case NSBits{+g, +env, +e}:
          N.rec(fu, NSBitsGo{g, env, Expr.wordk(e), e})
        case NSCtorBits{+g, +env, args}:
          match args:
            case a <> Nil{}:
              N.rec(fu, NSBits{g, env, a})
            case other:
              do NG<As.Code>:
                N.error("a word with more than one field")
                return As.CNil{}
        case NSCtorGo{+g, +env, +tag, +kind, +args}:
          do NG<As.Code>:
            +base : U32 <- N.slots(N.cx(env, args))
            a : As.Code <- N.rec(fu, NSArgs{g, env, args, base})
            return As.CCat{a, N.ctor.code(U32.to_nat(kind), tag, N.ops(env, args, base))}
        case NSCtorKind{+g, +env, +tag, +kind, args, w}:
          match w:
            case 0n:
              N.rec(fu, NSCtorBits{g, env, args})
            case 1n:
              N.rec(fu, NSCtorBits{g, env, args})
            case 2n+q:
              N.rec(fu, NSCtorGo{g, env, tag, kind, args})
        case NSCtorInfo{+g, +env, +name, info, args}:
          match info:
            case None{}:
              do NG<As.Code>:
                N.error("unknown constructor: " ++ name)
                return As.CNil{}
            case Some{CInfo{tag, ar, kind, single}}:
              N.rec(fu, NSCtorKind{g, env, tag, kind, args, P.which(name, ["U32", "F32"])})
        case NSCtor{+g, +env, +name, args}:
          N.rec(fu, NSCtorInfo{g, env, name, G.ctor(g, name), args})
        # A lambda: a function L_k(V *a) with its captures at a[0..n-1] and
        # its argument at a[n], all copied into its slots; its closure holds
        # the captures.
        case NSLam{+g, +env, +p, +body}:
          +caps = N.caps(FV.expr(body, Pat.vars(p, Nil{}), Nil{}), env)
          +n = U32.from_nat(List.length(&2, NB, caps))
          +binds = N.binds.keep(Gen.free(g), NPr.binds(N.pat(g, p, NPO{NOS{n}}, NPr.none())))
          do NG<As.Code>:
            +k : U32 <- N.fresh()
            +name : String <- NG.pure(String, "L_" ++ U32.show(k))
            saved : U32 & U32 <- N.enter()
            +a0 : U32 <- N.slots(U32.inc(n))
            +bb : U32 <- N.slots(N.binds.n(binds))
            b : As.Code <- N.rec(fu, NSStmt{g, N.binds.env(binds, bb, N.caps.inner(caps, 0)), NSelf.none(), NTRet{}, body})
            +max : U32 <- N.leave(saved)
            N.emit(N.func(name, max, N.cat([N.params.in(U32.to_nat(U32.inc(n)), 0, True{}),
              N.binds.code(binds, bb), N.open(g, binds, bb, body), b])))
            return N.clo(name, U32.inc(n), N.caps.ops(caps))
        # A statement as a value: its arms store it in a slot and jump to the
        # join label.
        case NSBlock{+g, +env, e}:
          do NG<As.Code>:
            +s : U32 <- N.slots(1)
            +j : String <- N.label()
            b : As.Code <- N.rec(fu, NSStmt{g, env, NSelf.none(), NTSet{s, j}, e})
            return N.cat([b, N.lab(j), N.ld(0, s)])
        case NSTailSelf{+g, +env, self, args}:
          match self:
            case NSelf{sn, +mask, +top}:
              +kept = N.split.kept(N.split0(mask, args))
              +n = U32.from_nat(List.length(&2, Core.Expr, kept))
              +tw = N.tw.get(env)
              +ks = N.tw.strip(kept, env, tw, 0)
              do NG<As.Code>:
                +base : U32 <- N.slots(N.cx(env, ks))
                a : As.Code <- N.rec(fu, NSArgs{g, env, ks, base})
                f : As.Code <- N.rec(fu, NSTwins{g, env, kept, tw, 0})
                +row : U32 <- N.slots(N.wide(n))
                +os : List<&2, NO> <- NG.pure(List<&2, NO>, N.tw.ops(N.ops(env, ks, base), kept, env, tw, 0))
                return N.cat([a, f, N.tail.move(os, base, row, n), N.tw.fin(os, kept, env, tw, 0), N.b(top)])
        case NSTailGo{+g, +env, +name, info, args}:
          match info:
            case DInfo{+kind, +mask}:
              +kept = N.split.kept(N.split0(mask, args))
              do NG<As.Code>:
                N.ref(name)
                +base : U32 <- N.slots(N.cx(env, kept))
                a : As.Code <- N.rec(fu, NSArgs{g, env, kept, base})
                sym : String <- N.fsym(name)
                return As.CCat{a, N.tailk(N.inline.k(U32.is_eq(kind, 2), name, env, kept), N.ops(env, kept, base), base,
                  U32.is_eq(kind, 2), name, sym)}
        case NSTailCall{+g, +env, +name, +args, ok}:
          match ok:
            case True{}:
              N.rec(fu, NSTailGo{g, env, name, G.def(g, name), args})
            case False{}:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, Core.ECall{Core.EVar{name}, args}})
                return As.CCat{c, N.epilogue()}
        case NSStmtCall{+g, +env, +self, tgt, +name, +args, tail}:
          match tail:
            case True{}:
              N.rec(fu, NSTailSelf{g, env, self, args})
            case False{}:
              N.rec(fu, NSStmtCallTo{g, env, tgt, name, args})
        case NSStmtCallTo{+g, +env, tgt, +name, +args}:
          match tgt:
            case NTRet{}:
              N.rec(fu, NSTailCall{g, env, name, args, N.can_tail(g, env, name, args)})
            case NTSet{+s, +j}:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, Core.ECall{Core.EVar{name}, args}})
                return As.CCat{c, N.fin(NTSet{s, j})}
            case NTDst{+d, +id}:
              N.rec(fu, NSDstCall{g, env, d, id, name, args, N.dst.call(g, env, NTDst{d, id}, name, args)})
        # A call to the group: its arguments, dst into x8, and a jump.
        case NSDstCall{+g, +env, +d, +id, +name, +args, ok}:
          match ok:
            case True{}:
              +kept = N.split.kept(N.split0(DInfo.mask(G.def(g, name)), args))
              do NG<As.Code>:
                N.ref(name)
                +base : U32 <- N.slots(N.cx(env, kept))
                a : As.Code <- N.rec(fu, NSArgs{g, env, kept, base})
                return N.cat([a, N.lregs.b(N.ops(env, kept, base), base), N.ld(8, d), N.pop(),
                  N.one(As.IB{As.b(), "D_" ++ Gen.mangle(name)})])
            case False{}:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, Core.ECall{Core.EVar{name}, args}})
                return As.CCat{c, N.fin(NTDst{d, id})}
        # C(.., f(..), ..) with f in the group: the node is stored through dst
        # with a hole where f's result goes, dst moves to the hole, and f's
        # code follows.
        case NSStmtCtor{none, +g, +env, +self, +tgt, +name, +args, +hole}:
          match none:
            case True{}:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, Core.ECtor{name, args}})
                return As.CCat{c, N.fin(tgt)}
            case False{}:
              +fs = N.dst.fields(args, 1, hole)
              +d = N.dst.slot(tgt)
              do NG<As.Code>:
                +base : U32 <- N.slots(N.cx(env, fs))
                a : As.Code <- N.rec(fu, NSArgs{g, env, fs, base})
                b : As.Code <- N.rec(fu, NSStmt{g, env, self, tgt, Gen.dst.nth(U32.to_nat(hole), Core.EErr{"hole"} <> args)})
                return N.cat([a, N.hnode(Gen.stmt.ctor.tag(g, name), N.ops(env, fs, base)), N.ld(9, d),
                  N.w(As.str(0, 9, 0)), N.addk(0, 0, (hole * 8 : U32)), N.st(0, d), b])
        case NSLetVar{+g, +env, +self, +tgt, +x, v, +body, m}:
          match m:
            case Some{+o}:
              do NG<As.Code>:
                b : As.Code <- N.rec(fu, NSStmt{g, NB{x, o} <> env, self, tgt, body})
                return As.CCat{N.shares.g(g, [NB{x, o}], body), b}
            case None{}:
              do NG<As.Code>:
                +s : U32 <- N.slots(1)
                c : As.Code <- N.rec(fu, NSExpr{g, env, v})
                b : As.Code <- N.rec(fu, NSStmt{g, NB{x, NOS{s}} <> env, self, tgt, body})
                return N.cat([c, N.st(0, s), N.shares.g(g, [NB{x, NOS{s}}], body), b])
        case NSLetHole{+g, +env, +self, +tgt, v, body}:
          do NG<As.Code>:
            c : As.Code <- N.rec(fu, NSExpr{g, env, v})
            b : As.Code <- N.rec(fu, NSStmt{g, env, self, tgt, body})
            return As.CCat{c, b}
        case NSLetPat{+g, +env, +self, +tgt, +p, v, +body}:
          do NG<As.Code>:
            +s : U32 <- N.slots(1)
            c : As.Code <- N.rec(fu, NSExpr{g, env, v})
            +binds : List<&2, NBd> = N.binds.keep(Gen.free(g), NPr.binds(N.pat(g, p, NPO{NOS{s}}, NPr.none())))
            +bb : U32 <- N.slots(N.binds.n(binds))
            b : As.Code <- N.rec(fu, NSStmt{g, N.binds.env(binds, bb, env), self, tgt, body})
            return N.cat([c, N.st(0, s), N.binds.code(binds, bb), N.open(g, binds, bb, body), b])
        # A parallel let, in order: each value in the environment before it.
        case NSLets{+g, +env0, +env, +self, +tgt, ps, vs, +body}:
          match ps vs:
            case +p <> pt v <> vt:
              do NG<As.Code>:
                +s : U32 <- N.slots(1)
                c : As.Code <- N.rec(fu, NSExpr{g, env0, v})
                +binds : List<&2, NBd> = N.binds.keep(Gen.free(g), NPr.binds(N.pat(g, p, NPO{NOS{s}}, NPr.none())))
                +bb : U32 <- N.slots(N.binds.n(binds))
                b : As.Code <- N.rec(fu, NSLets{g, env0, N.binds.env(binds, bb, env), self, tgt, pt, vt, body})
                return N.cat([c, N.st(0, s), N.binds.code(binds, bb), N.open(g, binds, bb, body), b])
            case pl vl:
              N.rec(fu, NSStmt{g, env, self, tgt, body})
        case NSLetPar{+g, +env, +self, +tgt, ps, v, body}:
          match v:
            case Core.ECtor{n, vs}:
              N.rec(fu, NSPar{g, env, self, tgt, ps, vs, body})
            case other:
              N.rec(fu, NSPar{g, env, self, tgt, ps, [other], body})
        # A parallel let (GSPar): in S_name its values run in order; else
        # they fork (every one but the last, which runs here, then the forks
        # are joined in reverse), in a seq def only above the frontier.
        case NSPar{+g, +env, +self, +tgt, +ps, +vs, +body}:
          do NG<As.Code>:
            m : Maybe<&2, String> <- N.memo.find("%seqmode")
            N.rec(fu, NSParPick{Gen.par.mode(m, N.self.name(self)), g, env, self, tgt, ps, vs, body})
        case NSParPick{mode, +g, +env, +self, +tgt, +ps, +vs, +body}:
          match mode:
            case 1n:
              N.rec(fu, NSLets{g, env, env, self, tgt, ps, vs, body})
            case other:
              +sn = N.self.name(self)
              do NG<As.Code>:
                m : Maybe<&2, String> <- N.memo.find("%seqmode")
                +s : U32 <- N.slots(U32.from_nat(List.length(&2, Core.Expr, vs)))
                pre : As.Code <- N.rec(fu, NSParSq{Gen.isseq(g, sn), g, env, sn, Maybe.default(&2, String, m, ""), s,
                  vs})
                b : As.Code <- N.rec(fu, NSParBind{g, env, self, tgt, ps, s, body})
                return As.CCat{pre, b}
        # At the frontier (bn_front: par_depth against par_front) the values
        # run in order, calling S_name; below it they fork.
        case NSParSq{sq, +g, +env, +sn, +prev, +s, +vs}:
          match sq:
            case True{}:
              do NG<As.Code>:
                +fk : String <- N.label()
                +done : String <- N.label()
                N.memo.add(Bind{"%seqmode", sn})
                q : As.Code <- N.rec(fu, NSParSeq{g, env, s, vs})
                N.memo.add(Bind{"%seqmode", prev})
                f : As.Code <- N.rec(fu, NSParVals{g, env, s, vs})
                return N.cat([N.call("bn_front"), N.one(As.IBc{As.cbz(0), fk}), q, N.b(done), N.lab(fk), f,
                  N.call("bn_back"), N.lab(done)])
            case False{}:
              N.rec(fu, NSParVals{g, env, s, vs})
        case NSParSeq{+g, +env, +s, vs}:
          match vs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case v <> t:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, v})
                rest : As.Code <- N.rec(fu, NSParSeq{g, env, U32.inc(s), t})
                return N.cat([c, N.st(0, s), rest])
        case NSParVals{+g, +env, +s, vs}:
          match vs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case v <> Nil{}:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, v})
                return As.CCat{c, N.st(0, s)}
            case v <> t:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSLam{g, env, Core.PVar{"_"}, v})
                rest : As.Code <- N.rec(fu, NSParVals{g, env, U32.inc(s), t})
                return N.cat([c, N.call("par_fork"), N.st(0, s), rest, N.ld(0, s), N.call("par_join"), N.st(0, s)])
        case NSParBind{+g, +env, +self, +tgt, ps, +s, +body}:
          match ps:
            case +p <> pt:
              do NG<As.Code>:
                +binds : List<&2, NBd> = N.binds.keep(Gen.free(g), NPr.binds(N.pat(g, p, NPO{NOS{s}}, NPr.none())))
                +bb : U32 <- N.slots(N.binds.n(binds))
                b : As.Code <- N.rec(fu, NSParBind{g, N.binds.env(binds, bb, env), self, tgt, pt, U32.inc(s), body})
                return N.cat([N.binds.code(binds, bb), N.open(g, binds, bb, body), b])
            case Nil{}:
              N.rec(fu, NSStmt{g, env, self, tgt, body})
        case NSLetCtor{+g, +env, +self, +tgt, name, ps, v, body, par}:
          match par:
            case True{}:
              N.rec(fu, NSLetPar{g, env, self, tgt, ps, v, body})
            case False{}:
              N.rec(fu, NSLetPat{g, env, self, tgt, Core.PCtor{name, ps}, v, body})
        case NSLet{+g, +env, +self, +tgt, p, +v, +body}:
          match p:
            case Core.PVar{+x}:
              Bool.pick(Unit -> NG(As.Code), Str.eq(x, "_"),
                u => N.rec(fu, NSLetHole{g, env, self, tgt, v, body}),
                u => N.rec(fu, NSLetVar{g, env, self, tgt, x, v, body, N.simple(env, v)}))(Unit{})
            case Core.PCtor{+name, ps}:
              N.rec(fu, NSLetCtor{g, env, self, tgt, name, ps, v, body, Str.eq(name, "%par")})
            case other:
              N.rec(fu, NSLetPat{g, env, self, tgt, other, v, body})
        # A case: its tests (a failing one jumps to the next case), its
        # bindings, its body, each in slots freed after it.
        case NSCaseGo{+g, +env, +self, +tgt, +os, cs, +binds, +body, rest}:
          match cs:
            case Nil{}:
              do NG<As.Code>:
                +m : U32 <- N.mark()
                +bb : U32 <- N.slots(N.binds.n(binds))
                b : As.Code <- N.rec(fu, NSStmt{g, N.binds.env(binds, bb, env), self, tgt, body})
                N.release(m)
                return N.cat([N.binds.code(binds, bb), N.open(g, binds, bb, body), b])
            case c <> t:
              do NG<As.Code>:
                +no : String <- N.label()
                cc : As.Code <- N.conds(c <> t, no)
                +m : U32 <- N.mark()
                +bb : U32 <- N.slots(N.binds.n(binds))
                b : As.Code <- N.rec(fu, NSStmt{g, N.binds.env(binds, bb, env), self, tgt, body})
                N.release(m)
                more : As.Code <- N.rec(fu, NSCases{g, env, self, tgt, os, rest})
                return N.cat([cc, N.binds.code(binds, bb), N.open(g, binds, bb, body), b, N.lab(no), more])
        case NSCases{+g, +env, +self, +tgt, +os, cases}:
          match cases:
            case Nil{}:
              do NG<As.Code>:
                +l : String <- N.cstr("runtime fail-stop")
                return As.CCat{N.adr(0, l), N.call("bend_fail")}
            case Core.ECase{+ps, body} <> t:
              +pr = N.pats(g, ps, os, NPr.none())
              N.rec(fu, NSCaseGo{g, env, self, tgt, os, NPr.conds(pr), N.binds.keep(Gen.free(g), NPr.binds(pr)), body, t})
            case other <> t:
              N.rec(fu, NSCases{g, env, self, tgt, os, t})
        case NSMatch{+g, +env, +self, +tgt, +scrs, cases}:
          do NG<As.Code>:
            +base : U32 <- N.slots(N.cx(env, scrs))
            a : As.Code <- N.rec(fu, NSArgs{g, env, scrs, base})
            c : As.Code <- N.rec(fu, NSCases{g, env, self, tgt, N.ops(env, scrs, base), cases})
            return As.CCat{a, c}
        case NSStmt{+g, +env, +self, +tgt, e}:
          match e:
            case Core.ELet{p, v, body}:
              N.rec(fu, NSLet{g, env, self, tgt, p, v, body})
            case Core.EMatch{scrs, cases}:
              N.rec(fu, NSMatch{g, env, self, tgt, scrs, cases})
            case Core.ECall{Core.EVar{+name}, +args}:
              N.rec(fu, NSStmtCall{g, env, self, tgt, name, args, N.is_tail(env, self, tgt, name, args)})
            case Core.ECtor{+name, +args}:
              +hole = N.dst.hole(g, env, tgt, Gen.dst.node(G.ctor(g, name)), args, 0, 0)
              N.rec(fu, NSStmtCtor{U32.is_zero(hole), g, env, self, tgt, name, args, hole})
            case other:
              do NG<As.Code>:
                c : As.Code <- N.rec(fu, NSExpr{g, env, other})
                return As.CCat{c, N.fin(tgt)}

def N.stmt(+g: G, +env: NEnv(), +self: NSelf, +tgt: NT, e: Core.Expr) -> NG(As.Code):
  N.rec(Fuel.max(), NSStmt{g, env, self, tgt, e})

# Defs
# ----

# W_name(V *a): the closure entry, with every parameter at a[i]: loads the
# kept ones into x0..x7 and branches to the def; a wide def gets them in a
# row of its own frame.
def N.wargs(mask: List<&2, Bool>, +j: U32, +i: U32, +wide: Bool) -> As.Code:
  match mask:
    case Nil{}:
      As.CNil{}
    case True{} <> t:
      As.CCat{Bool.pick(As.Code, wide, As.CCat{N.w(As.ldr(9, 10, (j * 8 : U32))), N.stx(9, (i * 8 : U32))},
        N.w(As.ldr(i, 10, (j * 8 : U32)))), N.wargs(t, U32.inc(j), U32.inc(i), wide)}
    case False{} <> t:
      N.wargs(t, U32.inc(j), i, wide)

def N.wrapper(+name: String, +mask: List<&2, Bool>, +native: Bool) -> NG(Unit):
  +n = N.kept(mask)
  N.emit(As.CCat{N.one(As.ISym{Gen.w(name), False{}}),
    Bool.pick(As.Code, U32.is_le(n, 8),
      N.cat([N.w(As.mov(10, 0)), N.wargs(mask, 0, 0, False{}), N.target(native, As.b(), name)]),
      N.cat([N.prologue(n, 0), N.w(As.mov(10, 0)), N.wargs(mask, 0, 0, True{}), N.w(As.addi(0, 31, 0)),
        N.target(native, As.bl(), name), N.fix(N.epilogue(), 0)]))})

def N.def.fn(+g: G, +sym: String, +name: String, +mask: List<&2, Bool>, +ps: List<&2, Core.Param>, +e: Core.Expr) -> NG(Unit):
  +n = N.kept(mask)
  +tw = Bool.pick(U32, Bool.and(U32.is_le(n, 8), N.tails.self(Dps.tails(g, e, Nil{}), name)), N.twins(ps, mask, 0), 0)
  do NG<Unit>:
    saved : U32 & U32 <- N.enter()
    +p0 : U32 <- N.slots(n)
    +top : String <- N.label()
    b : As.Code <- N.stmt(g, NB{"%fp", NOK{tw}} <> N.params(ps, mask, 0, Nil{}), NSelf{name, mask, top}, NTRet{}, e)
    +max : U32 <- N.leave(saved)
    N.emit(N.func.fp(sym, max, U32.is_ne(tw, 0), N.cat([N.params.in(U32.to_nat(n), 0, U32.is_gt(n, 8)),
      N.tw.entry(4n, tw, 0), N.lab(top), N.shares.g(g, N.params.boxed(ps, mask, 0), e), b])))

# S_name, a seq def's sequential clone (Gen.def.seq): its parallel lets run
# in order and its calls to itself stay in it.
def N.def.seq(sq: Bool, +g: G, +name: String, +mask: List<&2, Bool>, +ps: List<&2, Core.Param>, +e: Core.Expr) -> NG(Unit):
  match sq:
    case True{}:
      do NG<Unit>:
        N.memo.add(Bind{"%seqmode", name})
        N.def.fn(g, "S_" ++ Gen.mangle(name), name, mask, ps, e)
        N.memo.add(Bind{"%seqmode", ""})
    case False{}:
      NG.pure(Unit, Unit{})

# D_name and F_name, a def of destination-passing group id (see N.dps).
def N.def.dst(+g: G, +name: String, +mask: List<&2, Bool>, +ps: List<&2, Core.Param>, +e: Core.Expr, +id: String) ->
  NG(Unit):
  +n = N.kept(mask)
  +m = Gen.mangle(name)
  do NG<Unit>:
    saved : U32 & U32 <- N.enter()
    +p0 : U32 <- N.slots(n)
    +d : U32 <- N.slots(1)
    +top : String <- N.label()
    b : As.Code <- N.stmt(g, N.params(ps, mask, 0, Nil{}), NSelf{name, mask, top}, NTDst{d, id}, e)
    +max : U32 <- N.leave(saved)
    N.emit(N.func("D_" ++ m, max, N.cat([N.params.in(U32.to_nat(n), 0, False{}), N.st(8, d), N.lab(top),
      N.shares.g(g, N.params.boxed(ps, mask, 0), e), b])))
    N.emit(N.dst.entry(m, Gen.f(name)))

def N.def.pick(plain: Bool, +g: G, +name: String, +mask: List<&2, Bool>, +ps: List<&2, Core.Param>, +e: Core.Expr,
  +id: String
) -> NG(Unit):
  match plain:
    case True{}:
      N.def.fn(g, Gen.f(name), name, mask, ps, e)
    case False{}:
      N.def.dst(g, name, mask, ps, e, id)

def N.def.body(+g: G, +name: String, +mask: List<&2, Bool>, +ps: List<&2, Core.Param>, body: Core.Expr) -> NG(Unit):
  +e = R.ops(body, "Nat")
  +id = N.dps(g, name)
  do NG<Unit>:
    N.def.pick(String.is_empty(id), g, name, mask, ps, e, id)
    N.wrapper(name, mask, False{})
    N.def.seq(Bool.and(Expr.has_par(e), Gen.isseq(g, name)), g, name, mask, ps, e)

# a[j] into the request's field j (x10 holds a, x0 the node).
def N.eff.args(k: Nat, +j: U32) -> As.Code:
  match k:
    case 0n:
      As.CNil{}
    case 1n+q:
      As.CCat{N.ws([As.ldr(9, 10, (j * 8 : U32)), As.str(9, 0, (U32.inc(j) * 8 : U32))]), N.eff.args(q, U32.inc(j))}

# Effects: F builds the closure R => k => {args..., k}; E, its code, the
# request node the event loop answers (io_req in bendrt.h).
def N.def.eff(+name: String, +mask: List<&2, Bool>, ims: List<&2, String>) -> NG(Unit):
  +n = N.kept(mask)
  +e = "E_" ++ Gen.mangle(name)
  do NG<Unit>:
    N.effs(ims)
    +cid : U32 <- N.eid(name)
    N.emit(N.func(Gen.f(name), n, N.cat([N.params.in(U32.to_nat(n), 0, U32.is_gt(n, 8)),
      N.clo(e, (n + 2 : U32), N.seq(U32.to_nat(n), 0)), N.epilogue()])))
    N.emit(N.func(e, 1, N.cat([N.st(0, 0), N.alloc((n + 2 : U32)), N.ld(10, 0),
      N.k(9, (cid .|. (U32.inc(n) << 24n : U32) : U32)), N.w(As.str(9, 0, 0)),
      N.eff.args(U32.to_nat(n), 0), N.w(As.ldr(9, 10, (U32.inc(n) * 8 : U32))),
      N.w(As.str(9, 0, (U32.inc(n) * 8 : U32))), N.epilogue()])))
    N.wrapper(name, mask, False{})

def N.def.native(+g: G, +name: String, +mask: List<&2, Bool>, ps: List<&2, Core.Param>, body: Core.Expr, native: Bool) ->
  NG(Unit):
  match native:
    case True{}:
      N.wrapper(name, mask, True{})
    case False{}:
      N.def.body(g, name, mask, ps, body)

def N.def.law(+name: String, +mask: List<&2, Bool>, native: Bool) -> NG(Unit):
  match native:
    case True{}:
      N.wrapper(name, mask, True{})
    case False{}:
      NG.pure(Unit, Unit{})

def N.def.decl(+g: G, +name: String, info: DInfo, d: Decl) -> NG(Unit):
  DInfo{+kind, +mask} = info
  match d:
    case DDef{n, ps, body, ret}:
      N.def.native(g, name, mask, ps, body, U32.is_eq(kind, 2))
    case DEff{n, ps, ims}:
      N.def.eff(name, mask, ims)
    case other:
      N.def.law(name, mask, U32.is_eq(kind, 2))

def N.def(+g: G, +name: String) -> NG(Unit):
  N.def.decl(g, name, G.def(g, name), G.body(g, name))

def N.all.go(n: Nat, +g: G, queue: List<&2, String>, +done: Set()) -> NG(Unit):
  match n:
    case 0n:
      N.error("out of fuel")
    case 1n+ +fu:
      match queue:
        case Nil{}:
          NG.pure(Unit, Unit{})
        case +h <> +t:
          Bool.pick(Unit -> NG(Unit), Pair.snd(Set(), Bool, Set.has(done, h)),
            u => N.all.go(fu, g, t, done),
            u => do NG<Unit>:
              N.def(g, h)
              refs : List<&2, String> <- N.take_refs()
              N.all.go(fu, g, List.append(&2, String, refs, t), Set.add(done, h)))(Unit{})

# Printers
# --------

# pr_s of a literal.
def N.prs(s: String) -> NG(As.Code):
  do NG<As.Code>:
    +l : String <- N.cstr(s)
    return As.CCat{N.adr(0, l), N.call("pr_s")}

# The printers of values of a type, as Gen.printer's: P_k(V v), with v in
# slot 0 (and a loop's index in slot 1).
type NPS is Data:
  NPSPrinter{ty0: Core.Expr}
  NPSTuple{xs: List<&2, Core.Expr>, path: NPa}
  NPSFields{sub: List<&2, TB>, fs: List<&2, Field>, nt: Bool, i: U32}
  NPSCtor{sub: List<&2, TB>, name: String, fields: List<&2, Field>, info: Maybe<&2, CInfo>}
  NPSCtors{sub: List<&2, TB>, cs: List<&2, Ctor>}
  NPSAdt{ty: Core.Expr, d: Decl}
  NPSArr{e: String, leaf: Maybe<&2, CInfo>}
  NPSHead{ty: Core.Expr, k: Nat}
  NPSBody{ty: Core.Expr, h: String}
  NPSMemo{ty: Core.Expr, key: String, m: Maybe<&2, String>}

def NPS.ty(k: NPS) -> Type:
  match k:
    case NPSPrinter{ty0}:
      String
    case NPSMemo{ty, key, m}:
      String
    case other:
      As.Code

def NPS.none(k: NPS) -> NPS.ty(k):
  match k:
    case NPSPrinter{ty0}:
      ""
    case NPSTuple{xs, path}:
      As.CNil{}
    case NPSFields{sub, fs, nt, i}:
      As.CNil{}
    case NPSCtor{sub, name, fields, info}:
      As.CNil{}
    case NPSCtors{sub, cs}:
      As.CNil{}
    case NPSAdt{ty, d}:
      As.CNil{}
    case NPSArr{e, leaf}:
      As.CNil{}
    case NPSHead{ty, k}:
      As.CNil{}
    case NPSBody{ty, h}:
      As.CNil{}
    case NPSMemo{ty, key, m}:
      ""

def NPS.starve(k: NPS) -> NG(NPS.ty(k)):
  do NG<NPS.ty(k)>:
    N.error("out of fuel")
    return NPS.none(k)

# v's test for a constructor: none (the only one), v == IMM(tag), or a node
# with the tag.
def N.pr.test(+kind: U32, +tag: U32, single: Bool, +no: String) -> As.Code:
  Bool.pick(As.Code, single, As.CNil{},
    Bool.pick(As.Code, U32.is_eq(kind, 1), N.cat([N.ld(0, 0), N.k(9, N.imm(tag)), N.w(As.cmp(0, 9)),
      N.one(As.IBc{As.bc(As.ne()), no})]),
      N.cat([N.ld(0, 0), N.w(As.and1(9, 0)), N.one(As.IBc{As.cbnz(9), no}), N.tag(), N.k(9, tag), N.w(As.cmp(0, 9)),
        N.one(As.IBc{As.bc(As.ne()), no})])))

def N.pr.rec(n: Nat, +g: G, s: NPS) -> NG(NPS.ty(s)):
  match n:
    case 0n:
      NPS.starve(s)
    case 1n+ +fu:
      match s:
        case NPSPrinter{ty0}:
          +ty = Ty.norm(g, ty0, 16n)
          +key = Expr.show(ty)
          do NG<String>:
            m : Maybe<&2, String> <- N.memo.find(key)
            N.pr.rec(fu, g, NPSMemo{ty, key, m})
        case NPSTuple{xs, +path}:
          match xs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case h <> Nil{}:
              do NG<As.Code>:
                f : String <- N.pr.rec(fu, g, NPSPrinter{h})
                return As.CCat{N.path(path), N.bl(f)}
            case h <> t:
              do NG<As.Code>:
                f : String <- N.pr.rec(fu, g, NPSPrinter{h})
                sep : As.Code <- N.prs(", ")
                rest : As.Code <- N.pr.rec(fu, g, NPSTuple{t, NPF{path, 1}})
                return N.cat([N.path(NPF{path, 0}), N.bl(f), sep, rest])
        case NPSFields{+sub, fs, +nt, +i}:
          match fs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case Field{fname, t} <> rest:
              do NG<As.Code>:
                f : String <- N.pr.rec(fu, g, NPSPrinter{Ty.subst(t, sub)})
                sep : As.Code <- Bool.pick(NG(As.Code), U32.is_zero(i), NG.pure(As.Code, As.CNil{}), N.prs(", "))
                more : As.Code <- N.pr.rec(fu, g, NPSFields{sub, rest, nt, U32.inc(i)})
                return N.cat([sep, N.path(Bool.pick(NPa, nt, NPO{NOS{0}}, NPF{NPO{NOS{0}}, i})), N.bl(f), more])
        case NPSCtor{+sub, +name, fields, info}:
          match info:
            case None{}:
              NG.pure(As.Code, As.CNil{})
            case Some{CInfo{+tag, ar, +kind, +single}}:
              do NG<As.Code>:
                +no : String <- N.label()
                open : As.Code <- N.prs(name ++ "{")
                fs : As.Code <- N.pr.rec(fu, g, NPSFields{sub, fields, U32.is_eq(kind, 2), 0})
                close : As.Code <- N.prs("}")
                return N.cat([N.pr.test(kind, tag, single, no), open, fs, close, N.epilogue(), N.lab(no)])
        case NPSCtors{+sub, cs}:
          match cs:
            case Nil{}:
              NG.pure(As.Code, As.CNil{})
            case Ctor{+name, fields} <> t:
              do NG<As.Code>:
                one : As.Code <- N.pr.rec(fu, g, NPSCtor{sub, name, fields, G.ctor(g, name)})
                rest : As.Code <- N.pr.rec(fu, g, NPSCtors{sub, t})
                return As.CCat{one, rest}
        case NPSAdt{+ty, d}:
          match d:
            case DType{name, ps, cs}:
              do NG<As.Code>:
                b : As.Code <- N.pr.rec(fu, g, NPSCtors{Ty.bind(ps, Ty.args(ty)), cs})
                q : As.Code <- N.prs("?")
                return As.CCat{b, q}
            case other:
              N.prs("?")
        # An array prints its cells in order, as a list.
        case NPSArr{+e, leaf}:
          match leaf:
            case Some{CInfo{tag, ar, kind, single}}:
              do NG<As.Code>:
                +loop : String <- N.label()
                +skip : String <- N.label()
                +done : String <- N.label()
                ob : As.Code <- N.prs("[")
                sep : As.Code <- N.prs(", ")
                cb : As.Code <- N.prs("]")
                return N.cat([ob, N.k(9, 0), N.st(9, 1), N.lab(loop), N.ld(0, 0), N.w(As.ldr(9, 0, 0)), N.k(10, 31),
                  N.w(As.and(9, 9, 10)), N.k(10, 1), N.w(As.lslv(10, 10, 9)), N.ld(9, 1), N.w(As.cmp(9, 10)),
                  N.one(As.IBc{As.bc(As.hs()), done}), N.one(As.IBc{As.cbz(9), skip}), sep, N.lab(skip),
                  N.ld(0, 0), N.ld(9, 1), N.ws([As.lsli(9, 9, 3), As.add(0, 0, 9), As.ldr(0, 0, 8)]), N.bl(e),
                  N.ld(9, 1), N.w(As.addi(9, 9, 1)), N.st(9, 1), N.b(loop), N.lab(done), cb])
            case None{}:
              N.prs("[]")
        case NPSHead{+ty, k}:
          match k:
            case 0n:
              NG.pure(As.Code, As.CCat{N.ld(0, 0), N.call("pr_u32")})
            case 1n:
              NG.pure(As.Code, As.CCat{N.ld(0, 0), N.call("pr_nat")})
            case 2n:
              NG.pure(As.Code, As.CCat{N.ld(0, 0), N.call("pr_f32")})
            case 3n:
              NG.pure(As.Code, As.CCat{N.ld(0, 0), N.call("pr_char")})
            case 4n:
              NG.pure(As.Code, As.CCat{N.ld(0, 0), N.call("pr_str")})
            case 5n:
              do NG<As.Code>:
                e : String <- N.pr.rec(fu, g, NPSPrinter{P.last(Ty.args(ty))})
                +loop : String <- N.label()
                +skip : String <- N.label()
                +done : String <- N.label()
                ob : As.Code <- N.prs("[")
                sep : As.Code <- N.prs(", ")
                cb : As.Code <- N.prs("]")
                return N.cat([ob, N.k(9, 0), N.st(9, 1), N.lab(loop), N.ld(0, 0), N.tag(), N.k(9, 1), N.w(As.cmp(0, 9)),
                  N.one(As.IBc{As.bc(As.ne()), done}), N.ld(9, 1), N.one(As.IBc{As.cbz(9), skip}), sep, N.lab(skip),
                  N.k(9, 1), N.st(9, 1), N.ld(0, 0), N.w(As.ldr(0, 0, 8)), N.bl(e), N.ld(0, 0), N.w(As.ldr(0, 0, 16)),
                  N.st(0, 0), N.b(loop), N.lab(done), cb])
            case 6n:
              do NG<As.Code>:
                ob : As.Code <- N.prs("(")
                parts : As.Code <- N.pr.rec(fu, g, NPSTuple{Ty.tuple(ty), NPO{NOS{0}}})
                cb : As.Code <- N.prs(")")
                return N.cat([ob, parts, cb])
            case 7n:
              N.prs("<function>")
            case 8n:
              do NG<As.Code>:
                e : String <- N.pr.rec(fu, g, NPSPrinter{P.last(Ty.args(ty))})
                N.pr.rec(fu, g, NPSArr{e, G.ctor(g, "ALeaf")})
            case 9n:
              N.prs("{==}")
            case 10n+p:
              N.pr.rec(fu, g, NPSAdt{ty, G.body(g, "%" ++ Ty.head(ty))})
        case NPSBody{+ty, +h}:
          N.pr.rec(fu, g, NPSHead{ty, P.which(Ty.alias(h), ["U32", "Nat", "F32", "Char", "String",
            "List", "&", "->", "Array", "=="])})
        case NPSMemo{+ty, +key, m}:
          match m:
            case Some{f}:
              NG.pure(String, f)
            case None{}:
              do NG<String>:
                +k : U32 <- N.fresh()
                +f : String <- NG.pure(String, "P_" ++ U32.show(k))
                N.memo.add(Bind{key, f})
                b : As.Code <- N.pr.rec(fu, g, NPSBody{ty, Ty.head(ty)})
                N.emit(N.func(f, 2, N.cat([N.st(0, 0), b, N.epilogue()])))
                return f

def N.printer(+g: G, +ty: Core.Expr) -> NG(String):
  N.pr.rec(Fuel.max(), g, NPSPrinter{ty})

# Programs
# --------

# main: bend_run(argc, argv, F_main), or bend_run_value with the printer of
# main's type.
def N.entry.head() -> As.Code:
  N.cat([N.one(As.ISym{"main", True{}}), N.adr(2, Gen.f("main"))])

# main goes through bn_run (or bn_run_value), C beside the effects: under
# tcc, which ignores constructor attributes, it registers them first, as
# the C backend's main does (Gen.ctors.call).
def N.runs() -> String:
  "\nint bn_run(int argc, char **argv, V (*m)(void)) {" ++ Gen.ctors.call() ++ "  return bend_run(argc, argv, m);\n}\n" ++
    "int bn_run_value(int argc, char **argv, V (*m)(void), void (*p)(V)) {" ++ Gen.ctors.call() ++
    "  return bend_run_value(argc, argv, m, p);\n}\n"

def N.entry.ty(+g: G, +ret: Core.Expr, io: Bool) -> NG(As.Code):
  match io:
    case True{}:
      NG.pure(As.Code, As.CCat{N.entry.head(), N.one(As.ICall{As.b(), "bn_run"})})
    case False{}:
      do NG<As.Code>:
        p : String <- N.printer(g, ret)
        return N.cat([N.entry.head(), N.adr(3, p), N.one(As.ICall{As.b(), "bn_run_value"})])

def N.entry.ret(+g: G, +ret: Core.Expr) -> NG(As.Code):
  N.entry.ty(g, ret, Str.eq(Ty.head(ret), "IO"))

def N.entry(+g: G, d: Decl) -> NG(As.Code):
  match d:
    case DDef{n, ps, b, ret}:
      N.entry.ret(g, Ty.norm(g, ret, 16n))
    case other:
      do NG<As.Code>:
        N.error("no main definition")
        return As.CNil{}

def N.program.m(+g: G) -> NG(As.Code):
  do NG<As.Code>:
    N.all.go(Fuel.max(), g, ["main"], Set.new())
    N.entry(g, G.body(g, "main"))

# A program's object, and the C around its effects (their ids, the
# runtime's header, their sources: see Main.native).
type NOut is Data:
  NOut{head: String, effs: List<&2, String>, obj: As.Obj, errs: List<&2, String>}

def N.program.fin(elf: Bool, cids: String, r: As.Code & NSt) -> NOut:
  (entry, st) = r
  NSt{n, slot, max, out, refs, errs, +data, lits, memo, effs, eids} = st
  NOut{cids ++ "#define BEND_NATIVE_MAP_BIT 1\n#include \"bendrt_split.h\"\n\n",
    Gen.dedup(List.reverse(&2, String, effs), Nil{}), As.object(N.cat([out, entry, lits]), U32.max(data, 1), elf), errs}

# (An ELF object for Linux, else Mach-O.)
def N.program(+ds0: List<&2, Decl>, elf: Bool, free: Bool, par: Bool, +opt: String) -> NOut:
  +ds = Par.auto(par, Lo.program(opt, Pick.decls(ds0)))
  +g = Dps.build(G.new(ds), ds, free, False{})
  N.program.fin(elf, Gen.cids(g, ds, 0), N.program.m(g)(NSt{0, 0, 0, As.CNil{}, Nil{}, Nil{}, 0, As.CNil{}, Nil{}, Nil{},
    N.eids(ds, 0, Map.new(&2, U32))}))

# The bytes of little-endian words.
def N.bytes(ws: List<&2, U32>) -> List<&2, U32>:
  match ws:
    case Nil{}:
      Nil{}
    case +w <> t:
      (w .&. 255 : U32) <> ((w >> 8n : U32) .&. 255 : U32) <> ((w >> 16n : U32) .&. 255 : U32) <> (w >> 24n : U32) <>
        N.bytes(t)

# The optimizer's passes (see Opt): BEND_OPT's letters, else all of them.
def Main.opt(r: Result<&1, &1, U32 & String, String>) -> String:
  match r:
    case Done{v}:
      v
    case Fail{e}:
      "i..spf"

# C for a program: matches free what they open unless BEND_NO_FREE is set
# (bendc builds itself so: a compiler's heap is mostly shared, short-lived
# data, which tracing handles for less).
def Main.emit.c(+ds: List<&2, Decl>) -> IO(Unit):
  do IO<Unit>:
    r : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_NO_FREE")
    r2 : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_NO_FREE")
    ap : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_AUTO_PAR")
    ub : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_UNBOX")
    op : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_OPT")
    rc : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_RC")
    Main.emit(ds, Gen.program(ds, Main.free(r), Main.auto_par(ap, Main.free(r2)), Main.opt(op), Main.unbox(ub), Main.rc(rc)))

def J.entry.ty(+j: JG, +ret: Core.Expr, io: Bool) -> Gen(String):
  match io:
    case True{}:
      Gen.pure(String, "bend_run(F_main);\n")
    case False{}:
      do Gen<String>:
        p : String <- J.printer(j, ret)
        return "bend_run_value(F_main, " ++ p ++ ");\n"

def J.entry.ret(+j: JG, +ret: Core.Expr) -> Gen(String):
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

# bendc --native -o out base.bend input.bend
# ------------------------------------------
#
# The object goes to out.o; what bendc writes (Cc.begin) is the C of the
# program's effects (their sources, from Base's effs/*.c, with the ids they
# name), which Cc.link compiles and links with out.o and the runtime.

def Main.native.fin(r: File & Result<&1, &1, U32 & String, Unit>) -> IO(Unit):
  (f, res) = r
  File.close(f)

def Main.native.write(+path: String, ws: List<&2, U32>) -> IO(Unit):
  do IO<Unit>:
    f : File <- IO.try(File, File.open(path, "w"))
    r : File & Result<&1, &1, U32 & String, Unit> <- File.write_bytes(f, N.bytes(ws))
    Main.native.fin(r)

def Main.native.obj(+out: String, o: As.Obj) -> IO(Unit):
  As.Obj{ws, es} = o
  match es:
    case Nil{}:
      Main.native.write(out ++ ".o", ws)
    case e <> t:
      do IO<Unit>:
        IO.print_err(String.join(List.reverse(&2, String, e <> t), "\n"))
        IO.die(Unit, 1, "bendc: assembly failed")

def Main.native.ok(+ds: List<&2, Decl>, +out: String, head: String, effs: List<&2, String>, obj: As.Obj) -> IO(Unit):
  do IO<Unit>:
    +srcs : String <- Main.effs(effs, ds, Main.ids.known(ds), "")
    IO.write(head ++ srcs ++ Ctors.def(Ctors.scan(srcs)) ++ N.runs())
    Main.native.obj(out, obj)

def Main.native.emit(+ds: List<&2, Decl>, +out: String, r: NOut) -> IO(Unit):
  NOut{head, effs, obj, errs} = r
  match errs:
    case Nil{}:
      Main.native.ok(ds, out, head, effs, obj)
    case e <> t:
      do IO<Unit>:
        IO.print_err(String.join(List.reverse(&2, String, e <> t), "\n"))
        IO.die(Unit, 1, "bendc: compilation failed")

# (Matches free what they open unless BEND_NO_FREE is set, and parallel
# lets are found as BEND_AUTO_PAR says, as in C.)
def Main.native.to(+ds: List<&2, Decl>, +out: String, elf: Bool) -> IO(Unit):
  do IO<Unit>:
    r : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_NO_FREE")
    r2 : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_NO_FREE")
    ap : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_AUTO_PAR")
    op : Result<&1, &1, U32 & String, String> <- IO.get_env("BEND_OPT")
    Main.native.emit(ds, out, N.program(ds, elf, Main.free(r), Main.auto_par(ap, Main.free(r2)), Main.opt(op)))

def Main.native.compile(+out: String, elf: Bool, base: Result<&2, &2, String, List<&2, Decl>>,
  user: Result<&2, &2, String, List<&2, Decl>>
) -> IO(Unit):
  match base user:
    case Fail{e} u:
      IO.die(Unit, 1, "bendc: parse error in base: " ++ e)
    case Done{b} Fail{e}:
      IO.die(Unit, 1, "bendc: parse error: " ++ e)
    case Done{b} Done{u}:
      +ds = List.append(&2, Decl, b, u)
      Main.native.to(LM.decls(ds, ds), out, elf)

def Main.native.build(+out: String, elf: Bool, +base_path: String, user_path: String) -> IO(Unit):
  do IO<Unit>:
    base : String <- IO.read_file(base_path)
    user : List<&2, Decl> <- Main.load(64n, user_path)
    Main.native.compile(out, elf, Main.resolve(Mod.dir(base_path), Main.parse(base)), Done{user})

# A value main the checker normalized: main puts the text.
def Main.native.value(+out: String, elf: Bool, v: String) -> IO(Unit):
  do IO<Unit>:
    IO.write("")
    Main.native.obj(out, As.object(N.cat([N.one(As.ISym{"main", True{}}), N.ws([As.push_fp(), As.set_fp()]),
      N.adr(0, ".V"), N.call("puts"), N.k(0, 0), N.fix(N.epilogue(), 0), N.lab(".V"), N.ws(As.cstr(v))]), 1, elf))

def Main.native.checked.go(+out: String, +elf: Bool, +base_path: String, user_path: String, +bk: Chk.Book,
  norm: Bool) -> IO(Unit):
  match norm:
    case True{}:
      Main.native.value(out, elf, Chk.show_main(bk))
    case False{}:
      Main.native.build(out, elf, base_path, user_path)

def Main.native.checked(+out: String, +elf: Bool, +base_path: String, user_path: String, r: Chk.Book & Nat) ->
  IO(Unit):
  (b, n0) = r
  +bk = b
  Main.native.checked.go(out, elf, base_path, user_path, bk, Main.normalized(bk))

# bendc --native -o out base.bend input.bend: the program as machine code
# (see "Native code generation"), linked into out.
def Main.run5(code: Nat, o: Nat, +out: String, +base_path: String, +user_path: String) -> IO(Unit):
  match code o:
    case 7n 6n:
      do IO<Unit>:
        k : U32 <- IO.try(U32, Cc.elf())
        u : Unit <- IO.try(Unit, Cc.begin())
        r : Chk.Book & Nat <- Main.check(base_path, user_path)
        Main.native.checked(out, U32.is_eq(k, 1), base_path, user_path, r)
        IO.try(Unit, Cc.link(out))
    case c k:
      Main.usage()

def Main.run(args: List<&2, String>) -> IO(Unit):
  match args:
    case +a <> +b <> Nil{}:
      Main.run2(Main.code(a), a, b)
    case +a <> +b <> +c <> Nil{}:
      Main.run3(Main.code(a), b, c)
    case +a <> +b <> +c <> +d <> Nil{}:
      Main.run4(Main.code(a), b, c, d)
    case +a <> +b <> +c <> +d <> +e <> Nil{}:
      Main.run5(Main.code(a), Main.code(b), c, d, e)
    case other:
      Main.usage()

def main() -> IO(Unit):
  do IO<Unit>:
    args : List<String> <- IO.args()
    Main.run(Main.args(IO.list2(args)))
