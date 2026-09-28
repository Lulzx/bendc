import Base

# asm.bend: an AArch64 assembler and object file writer, in Bend.
#
# bendc's native backend (bendc --native) generates a program's code as a
# list of instructions (Ins): most are encoded words, and the rest name a
# label (a branch, an address) or an external symbol (a runtime function).
# As.object lays the code out, resolves its labels, and writes a relocatable
# object file around it (Mach-O for macOS, ELF for Linux) with relocations for
# the external symbols, which the system linker then links with the runtime.
# Before that, a peephole pass (peep) turns a reload after a store to the
# same frame slot into a move.
#
# The object has two sections: the code (with the bytes of string literals),
# aligned to a page, and a zeroed data section of 8-byte slots (the caches of
# string literals), named by the local symbol bn_slots. As the code section
# starts on a page, an adrp/add pair between two of its places is resolved
# here; one into the data section, or to a function of the runtime, is a
# relocation. Words are little-endian.

# Utilities
# =========

def Str.eq(+a: String, +b: String) -> Bool:
  String.eq(a, b)

# Instructions
# ============

# IW: an encoded instruction (or a data word). ILab: a label. ISym: a label
# that is also a symbol (ext: global). IB: an imm26 branch (B, BL) to a
# label; IBc: an imm19 one (B.cond, CBZ, CBNZ); IBt: an imm14 one (TBZ,
# TBNZ). IAdr: the address of a label into rd (adrp, add). ICall: an imm26
# branch to a symbol. IAdrS: the address of a symbol into rd.
type Ins is Data:
  IW{w: U32}
  ILab{l: String}
  ISym{l: String, ext: Bool}
  IB{w: U32, l: String}
  IBc{w: U32, l: String}
  IBt{w: U32, l: String}
  IAdr{rd: U32, l: String}
  ICall{w: U32, s: String}
  IAdrS{rd: U32, s: String}

# A rope of instructions, for linear-time building.
type Code is Data:
  CNil{}
  COne{i: Ins}
  CCat{a: Code, b: Code}

def Code.go(c: Code, acc: List<&2, Ins>) -> List<&2, Ins>:
  match c:
    case CNil{}:
      acc
    case COne{i}:
      i <> acc
    case CCat{a, b}:
      Code.go(a, Code.go(b, acc))

def Code.flat(c: Code) -> List<&2, Ins>:
  Code.go(c, Nil{})

# An instruction's word (0 when it is not an encoded word).
def Ins.word(i: Ins) -> U32:
  match i:
    case IW{w}:
      w
    case ILab{l}:
      0
    case ISym{l, e}:
      0
    case IB{w, l}:
      0
    case IBc{w, l}:
      0
    case IBt{w, l}:
      0
    case IAdr{r, l}:
      0
    case ICall{w, x}:
      0
    case IAdrS{r, x}:
      0

# c with each word a replaced by the code x, and each word b by y.
def Code.subst(c: Code, +a: U32, +x: Code, +b: U32, +y: Code) -> Code:
  match c:
    case CNil{}:
      CNil{}
    case COne{+i}:
      +w = Ins.word(i)
      Bool.pick(Code, U32.is_eq(w, a), x, Bool.pick(Code, U32.is_eq(w, b), y, COne{i}))
    case CCat{l, r}:
      CCat{Code.subst(l, a, x, b, y), Code.subst(r, a, x, b, y)}

def Code.list(xs: List<&2, Code>) -> Code:
  match xs:
    case Nil{}:
      CNil{}
    case h <> t:
      CCat{h, Code.list(t)}

def Code.w(w: U32) -> Code:
  COne{IW{w}}

def Code.ws(ws: List<&2, U32>) -> Code:
  match ws:
    case Nil{}:
      CNil{}
    case w <> t:
      CCat{COne{IW{w}}, Code.ws(t)}

# Encodings
# =========
#
# Registers are numbers: 0-30, and 31 for sp or the zero register (as the
# instruction reads it). Every data instruction here is 64-bit unless its
# name ends in w. The comments give the base words in hex.

def reg3(+w: U32, +rd: U32, +rn: U32, +rm: U32) -> U32:
  (w .|. ((rm << 16n : U32) .|. ((rn << 5n : U32) .|. rd : U32) : U32) : U32)

# movz rd, #k, lsl #16*hw (D2800000)
def movz(+rd: U32, +k: U32, +hw: U32) -> U32:
  (3531603968 .|. ((hw << 21n : U32) .|. ((k << 5n : U32) .|. rd : U32) : U32) : U32)

# movk rd, #k, lsl #16*hw (F2800000)
def movk(+rd: U32, +k: U32, +hw: U32) -> U32:
  (4068474880 .|. ((hw << 21n : U32) .|. ((k << 5n : U32) .|. rd : U32) : U32) : U32)

# mov rd, rm (orr rd, xzr, rm: AA0003E0)
def mov(+rd: U32, +rm: U32) -> U32:
  reg3(2852127712, rd, 0, rm)

# add rd, rn, #k (91000000); addh: #k, lsl 12 (91400000). rn, rd may be sp.
def addi(+rd: U32, +rn: U32, +k: U32) -> U32:
  (2432696320 .|. ((k << 10n : U32) .|. ((rn << 5n : U32) .|. rd : U32) : U32) : U32)

def addh(+rd: U32, +rn: U32, +k: U32) -> U32:
  (2436890624 .|. ((k << 10n : U32) .|. ((rn << 5n : U32) .|. rd : U32) : U32) : U32)

# sub rd, rn, #k (D1000000); subh: lsl 12 (D1400000).
def subi(+rd: U32, +rn: U32, +k: U32) -> U32:
  (3506438144 .|. ((k << 10n : U32) .|. ((rn << 5n : U32) .|. rd : U32) : U32) : U32)

def subh(+rd: U32, +rn: U32, +k: U32) -> U32:
  (3510632448 .|. ((k << 10n : U32) .|. ((rn << 5n : U32) .|. rd : U32) : U32) : U32)

# cmp rn, #k (subs xzr, rn, #k: F100001F)
def cmpi(+rn: U32, +k: U32) -> U32:
  (4043309087 .|. ((k << 10n : U32) .|. (rn << 5n : U32) : U32) : U32)

# cmp rn, rm (subs xzr, rn, rm: EB00001F)
def cmp(+rn: U32, +rm: U32) -> U32:
  reg3(3942645791, 0, rn, rm)

# cmp wn, wm (6B00001F)
def cmpw(+rn: U32, +rm: U32) -> U32:
  reg3(1795162143, 0, rn, rm)

# Three-register operations, by base word.
def add(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(2332033024, rd, rn, rm)

def sub(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(3405774848, rd, rn, rm)

def and(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(2315255808, rd, rn, rm)

def orr(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(2852126720, rd, rn, rm)

def eor(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(3388997632, rd, rn, rm)

def addw(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(184549376, rd, rn, rm)

def subw(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(1258291200, rd, rn, rm)

def mulw(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(453016576, rd, rn, rm)

def mul(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(2600500224, rd, rn, rm)

def udiv(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(2596276224, rd, rn, rm)

def lslv(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(2596282368, rd, rn, rm)

def lsrv(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(2596283392, rd, rn, rm)

# ubfm rd, rn, #r, #s (D3400000): lsl, lsr and ubfx are aliases.
def ubfm(+rd: U32, +rn: U32, +r: U32, +s: U32) -> U32:
  (3544186880 .|. ((r << 16n : U32) .|. ((s << 10n : U32) .|. ((rn << 5n : U32) .|. rd : U32) : U32) : U32) : U32)

def lsli(+rd: U32, +rn: U32, +k: U32) -> U32:
  ubfm(rd, rn, ((64 - k : U32) .&. 63 : U32), (63 - k : U32))

def lsri(+rd: U32, +rn: U32, +k: U32) -> U32:
  ubfm(rd, rn, k, 63)

# and rd, rn, #1 (92400000), orr rd, rn, #1 (B2400000).
def and1(+rd: U32, +rn: U32) -> U32:
  reg3(2453667840, rd, rn, 0)

def orr1(+rd: U32, +rn: U32) -> U32:
  reg3(2990538752, rd, rn, 0)

# and rd, rn, #~(3 << 20): clears the shared bits of a tag word (926AF400).
def andsh(+rd: U32, +rn: U32) -> U32:
  reg3(2456482816, rd, rn, 0)

# cset rd, c (csinc rd, xzr, xzr, !c: 9A9F07E0 | (c ^ 1) << 12)
def cset(+rd: U32, +c: U32) -> U32:
  (2594113504 .|. (((c .^. 1 : U32) << 12n : U32) .|. rd : U32) : U32)

# csel rd, rn, rm, c (9A800000)
def csel(+rd: U32, +rn: U32, +rm: U32, +c: U32) -> U32:
  (reg3(2592079872, rd, rn, rm) .|. (c << 12n : U32) : U32)

# ldr rt, [rn, #k] and str rt, [rn, #k], k a multiple of 8 below 32768
# (F9400000, F9000000).
def ldr(+rt: U32, +rn: U32, +k: U32) -> U32:
  (4181721088 .|. (((k >> 3n : U32) << 10n : U32) .|. ((rn << 5n : U32) .|. rt : U32) : U32) : U32)

def str(+rt: U32, +rn: U32, +k: U32) -> U32:
  (4177526784 .|. (((k >> 3n : U32) << 10n : U32) .|. ((rn << 5n : U32) .|. rt : U32) : U32) : U32)

# ldr wt, [rn, #k] (B9400000), k a multiple of 4.
def ldrw(+rt: U32, +rn: U32, +k: U32) -> U32:
  (3107979264 .|. (((k >> 2n : U32) << 10n : U32) .|. ((rn << 5n : U32) .|. rt : U32) : U32) : U32)

# ldar rt, [rn] (C8DFFC00)
def ldar(+rt: U32, +rn: U32) -> U32:
  (3370122240 .|. ((rn << 5n : U32) .|. rt : U32) : U32)

# stp x29, x30, [sp, #-16]! (A9BF7BFD); ldp x29, x30, [sp], #16 (A8C17BFD).
def push_fp() -> U32:
  2847898621

def pop_fp() -> U32:
  2831252477

# stp rt, rt2, [rn, #off] and ldp rt, rt2, [rn, #off]: a signed offset, a
# multiple of 8 in -512..504 (A9000000, A9400000).
def stpo(+rt: U32, +rt2: U32, +rn: U32, +off: U32) -> U32:
  (2835349504 .|. ((((off >> 3n : U32) .&. 127 : U32) << 15n : U32) .|. ((rt2 << 10n : U32) .|. ((rn << 5n : U32) .|. rt : U32) : U32) : U32) : U32)

def ldpo(+rt: U32, +rt2: U32, +rn: U32, +off: U32) -> U32:
  (2839543808 .|. ((((off >> 3n : U32) .&. 127 : U32) << 15n : U32) .|. ((rt2 << 10n : U32) .|. ((rn << 5n : U32) .|. rt : U32) : U32) : U32) : U32)

# mov x29, sp (910003FD)
def set_fp() -> U32:
  2432697341

# mov sp, x29 (910003BF)
def sp_fp() -> U32:
  2432697279

def ret() -> U32:
  3596551104

# blr rn (D63F0000), br rn (D61F0000).
def blr(+rn: U32) -> U32:
  (3594452992 .|. (rn << 5n : U32) : U32)

def br(+rn: U32) -> U32:
  (3592355840 .|. (rn << 5n : U32) : U32)

# fmov sd, wn (1E270000); fmov wd, sn (1E260000).
def fmovsw(+rd: U32, +rn: U32) -> U32:
  reg3(505872384, rd, rn, 0)

def fmovws(+rd: U32, +rn: U32) -> U32:
  reg3(505806848, rd, rn, 0)

# Single-precision fadd, fsub, fmul, fdiv sd, sn, sm (1E202800, 1E203800,
# 1E200800, 1E201800); fcmp sn, sm (1E202000); fneg sd, sn (1E214000);
# ucvtf sd, wn (1E230000).
def fadd(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(505423872, rd, rn, rm)

def fsub(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(505427968, rd, rn, rm)

def fmul(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(505415680, rd, rn, rm)

def fdiv(+rd: U32, +rn: U32, +rm: U32) -> U32:
  reg3(505419776, rd, rn, rm)

def fcmp(+rn: U32, +rm: U32) -> U32:
  reg3(505421824, 0, rn, rm)

def fneg(+rd: U32, +rn: U32) -> U32:
  reg3(505495552, rd, rn, 0)

def ucvtf(+rd: U32, +rn: U32) -> U32:
  reg3(505610240, rd, rn, 0)

# Branch bases: b (14000000), bl (94000000), b.cond (54000000), cbz
# (B4000000), cbnz (B5000000), tbz (36000000), tbnz (37000000).
def b() -> U32:
  335544320

def bl() -> U32:
  2483027968

def bc(+c: U32) -> U32:
  (1409286144 .|. c : U32)

def cbz(+rt: U32) -> U32:
  (3019898880 .|. rt : U32)

def cbnz(+rt: U32) -> U32:
  (3036676096 .|. rt : U32)

# tbz/tbnz rt, #bit (bit below 32).
def tbz(+rt: U32, +bit: U32) -> U32:
  (905969664 .|. ((bit << 19n : U32) .|. rt : U32) : U32)

def tbnz(+rt: U32, +bit: U32) -> U32:
  (922746880 .|. ((bit << 19n : U32) .|. rt : U32) : U32)

# Condition codes.
def eq() -> U32:
  0

def ne() -> U32:
  1

def hs() -> U32:
  2

def lo() -> U32:
  3

def hi() -> U32:
  8

def ls() -> U32:
  9

def ge() -> U32:
  10

def lt() -> U32:
  11

def mi() -> U32:
  4

def gt() -> U32:
  12

def le() -> U32:
  13

# rd = k, any 64-bit word given as its halves (movz, then a movk for each
# nonzero 16 bits past the first).
def movk.if(+rd: U32, +k: U32, +hw: U32, +rest: List<&2, U32>) -> List<&2, U32>:
  Bool.pick(List<&2, U32>, U32.is_zero(k), rest, movk(rd, k, hw) <> rest)

def mov64(+rd: U32, +lo: U32, +hi: U32) -> List<&2, U32>:
  movz(rd, (lo .&. 65535 : U32), 0) <> movk.if(rd, (lo >> 16n : U32), 1,
    movk.if(rd, (hi .&. 65535 : U32), 2, movk.if(rd, (hi >> 16n : U32), 3, Nil{})))

def mov32(+rd: U32, +k: U32) -> List<&2, U32>:
  mov64(rd, k, 0)

# Layout
# ======

type Sym is Data:
  Sym{name: String, at: U32, ext: Bool}

type Rel is Data:
  Rel{at: U32, sym: String, kind: U32}

def Ins.size(i: Ins) -> U32:
  match i:
    case ILab{l}:
      0
    case ISym{l, e}:
      0
    case IAdr{r, l}:
      8
    case IAdrS{r, s}:
      8
    case other:
      4

type Lay is Data:
  Lay{labels: Map<&2, U32>, syms: List<&2, Sym>, size: U32}

# Each label's offset, and the symbols in order.
def lay(ins: List<&2, Ins>, +pc: U32, m: Map<&2, U32>, syms: List<&2, Sym>) -> Lay:
  match ins:
    case Nil{}:
      Lay{m, List.reverse(&2, Sym, syms), pc}
    case i <> t:
      match i:
        case ILab{l}:
          lay(t, pc, Map.set(&2, U32, m, l, pc), syms)
        case ISym{+l, e}:
          lay(t, pc, Map.set(&2, U32, m, l, pc), Sym{l, pc, e} <> syms)
        case other:
          lay(t, (pc + Ins.size(other) : U32), m, syms)

type Enc is Data:
  Enc{words: List<&2, U32>, rels: List<&2, Rel>, errs: List<&2, String>}

def Enc.w(w: U32, e: Enc) -> Enc:
  Enc{ws, rs, es} = e
  Enc{w <> ws, rs, es}

def Enc.rel(w: U32, r: Rel, e: Enc) -> Enc:
  Enc{ws, rs, es} = e
  Enc{w <> ws, r <> rs, es}

def Enc.err(msg: String, e: Enc) -> Enc:
  Enc{ws, rs, es} = e
  Enc{0 <> ws, rs, msg <> es}

def Enc.none() -> U32:
  4294967295

def target(+m: Map<&2, U32>, +l: String) -> U32:
  Pair.snd(Map<&2, U32>, U32, Map.get(U32, Enc.none(), m, l))

# The offset in words from pc to t (a signed word: a negative one is
# shifted in with ones).
def delta.of(+x: U32) -> U32:
  Bool.pick(U32, U32.is_ge(x, 2147483648), ((x >> 2n : U32) .|. 3221225472 : U32), (x >> 2n : U32))

def delta(+t: U32, +pc: U32) -> U32:
  delta.of((t - pc : U32))

# Whether a signed word offset d fits in bits bits.
def fits(+d: U32, +bits: Nat) -> Bool:
  +h = U32.shln(1, Nat.sub(bits, 1n))
  Bool.or(U32.is_lt(d, h), U32.is_ge(d, (0 - h : U32)))

def enc.branch(+w: U32, +d: U32, +bits: Nat, +shift: Nat, +l: String, +e: Enc) -> Enc:
  Bool.pick(Enc, fits(d, bits),
    Enc.w((w .|. U32.shln((d .&. (U32.shln(1, bits) - 1 : U32) : U32), shift) : U32), e),
    Enc.err("branch out of range: " ++ l, e))

def enc.label(+w: U32, +t: U32, +pc: U32, +bits: Nat, +shift: Nat, +l: String, +e: Enc) -> Enc:
  Bool.pick(Enc, U32.is_eq(t, Enc.none()), Enc.err("no such label: " ++ l, e),
    enc.branch(w, delta(t, pc), bits, shift, l, e))

# adrp rd, t; add rd, rd, t's offset in its page (t in the code).
def enc.adr(+rd: U32, +t: U32, +pc: U32, +l: String, +e: Enc) -> Enc:
  +pd = ((t >> 12n : U32) - (pc >> 12n : U32) : U32)
  +adrp = (2415919104 .|. (((pd .&. 3 : U32) << 29n : U32) .|. ((((pd >> 2n : U32) .&. 524287 : U32) << 5n : U32) .|. rd : U32) : U32) : U32)
  Bool.pick(Enc, U32.is_eq(t, Enc.none()), Enc.w(0, Enc.err("no such label: " ++ l, e)),
    Enc.w(addi(rd, rd, (t .&. 4095 : U32)), Enc.w(adrp, e)))

# Encodes the instructions (the words come out in reverse).
def enc(ins: List<&2, Ins>, +pc: U32, +m: Map<&2, U32>, e: Enc) -> Enc:
  match ins:
    case Nil{}:
      e
    case i <> t:
      match i:
        case IW{w}:
          enc(t, (pc + 4 : U32), m, Enc.w(w, e))
        case ILab{l}:
          enc(t, pc, m, e)
        case ISym{l, x}:
          enc(t, pc, m, e)
        case IB{+w, +l}:
          enc(t, (pc + 4 : U32), m, enc.label(w, target(m, l), pc, 26n, 0n, l, e))
        case IBc{+w, +l}:
          enc(t, (pc + 4 : U32), m, enc.label(w, target(m, l), pc, 19n, 5n, l, e))
        case IBt{+w, +l}:
          enc(t, (pc + 4 : U32), m, enc.label(w, target(m, l), pc, 14n, 5n, l, e))
        case IAdr{+rd, +l}:
          enc(t, (pc + 8 : U32), m, enc.adr(rd, target(m, l), pc, l, e))
        case ICall{+w, +s}:
          enc(t, (pc + 4 : U32), m, Enc.rel(w, Rel{pc, s, Bool.pick(U32, U32.is_eq(w, b()), 5, 2)}, e))
        case IAdrS{+rd, +s}:
          enc(t, (pc + 8 : U32), m, Enc.rel(addi(rd, rd, 0), Rel{(pc + 4 : U32), s, 4},
            Enc.rel((2415919104 .|. rd : U32), Rel{pc, s, 3}, e)))

# Bytes and words
# ===============

def bytes.pack(bs: List<&2, U32>) -> List<&2, U32>:
  match bs:
    case a <> b <> c <> d <> t:
      (a .|. ((b << 8n : U32) .|. ((c << 16n : U32) .|. (d << 24n : U32) : U32) : U32) : U32) <> bytes.pack(t)
    case a <> b <> c <> Nil{}:
      [(a .|. ((b << 8n : U32) .|. (c << 16n : U32) : U32) : U32)]
    case a <> b <> Nil{}:
      [(a .|. (b << 8n : U32) : U32)]
    case a <> Nil{}:
      [a]
    case Nil{}:
      Nil{}

# The UTF-8 bytes of a code point.
def utf8(+x: U32, +rest: List<&2, U32>) -> List<&2, U32>:
  Bool.pick(List<&2, U32>, U32.is_lt(x, 128), x <> rest,
    Bool.pick(List<&2, U32>, U32.is_lt(x, 2048),
      (192 .|. (x >> 6n : U32) : U32) <> (128 .|. (x .&. 63 : U32) : U32) <> rest,
      Bool.pick(List<&2, U32>, U32.is_lt(x, 65536),
        (224 .|. (x >> 12n : U32) : U32) <> (128 .|. ((x >> 6n : U32) .&. 63 : U32) : U32) <>
          (128 .|. (x .&. 63 : U32) : U32) <> rest,
        (240 .|. (x >> 18n : U32) : U32) <> (128 .|. ((x >> 12n : U32) .&. 63 : U32) : U32) <>
          (128 .|. ((x >> 6n : U32) .&. 63 : U32) : U32) <> (128 .|. (x .&. 63 : U32) : U32) <> rest)))

def bytes(s: String) -> List<&2, U32>:
  match s:
    case SNil{}:
      Nil{}
    case SCon{Chr{x}, t}:
      utf8(x, bytes(t))

# A string's UTF-8 bytes with a terminating zero, as words.
def cstr(s: String) -> List<&2, U32>:
  bytes.pack(List.append(&2, U32, bytes(s), [0]))

def zeros(n: Nat) -> List<&2, U32>:
  match n:
    case 0n:
      Nil{}
    case 1n+p:
      0 <> zeros(p)

# A 16-byte name field.
def name16(+s: String) -> List<&2, U32>:
  List.append(&2, U32, bytes.pack(bytes(s)), zeros(Nat.sub(4n, List.length(&2, U32, bytes.pack(bytes(s))))))

def len32(xs: List<&2, U32>) -> U32:
  U32.from_nat(List.length(&2, U32, xs))

def lens(xs: List<&2, String>) -> U32:
  U32.from_nat(List.length(&2, String, xs))

# Symbols
# =======

# The symbol table: locals, then globals, then the undefined names the
# relocations use (each once), and each one's name offset.
type Tab is Data:
  Tab{locals: List<&2, Sym>, globals: List<&2, Sym>, undef: List<&2, String>}

def Tab.put(ext: Bool, s: Sym, t: Tab) -> Tab:
  match ext:
    case True{}:
      Tab{ls, gs, us} = t
      Tab{ls, s <> gs, us}
    case False{}:
      Tab{ls, gs, us} = t
      Tab{s <> ls, gs, us}

def Tab.split(ss: List<&2, Sym>, t: Tab) -> Tab:
  match ss:
    case Nil{}:
      Tab{ls, gs, us} = t
      Tab{List.reverse(&2, Sym, ls), List.reverse(&2, Sym, gs), us}
    case Sym{n, at, +ext} <> r:
      Tab.split(r, Tab.put(ext, Sym{n, at, ext}, t))

def Tab.undef(rs: List<&2, Rel>, +data: String, +seen: Set(), +acc: List<&2, String>) -> List<&2, String>:
  match rs:
    case Nil{}:
      List.reverse(&2, String, acc)
    case Rel{at, +s, k} <> +t:
      Bool.pick(Unit -> List<&2, String>, Bool.or(Str.eq(s, data), Pair.snd(Set(), Bool, Set.has(seen, s))),
        u => Tab.undef(t, data, seen, acc),
        u => Tab.undef(t, data, Set.add(seen, s), s <> acc))(Unit{})

def Str.index(xs: List<&2, String>, +x: String, +i: U32) -> U32:
  match xs:
    case Nil{}:
      i
    case +h <> t:
      Bool.pick(U32, Str.eq(h, x), i, Str.index(t, x, U32.inc(i)))

# The names, each with a leading prefix and a terminating zero, as bytes
# (the table starts with a zero byte: offset 0 is no name).
def strtab(ns: List<&2, String>, +pre: String) -> List<&2, U32>:
  match ns:
    case Nil{}:
      Nil{}
    case n <> t:
      List.append(&2, U32, bytes(pre ++ n), 0 <> strtab(t, pre))

def Sym.names(ss: List<&2, Sym>) -> List<&2, String>:
  match ss:
    case Nil{}:
      Nil{}
    case Sym{n, a, e} <> t:
      n <> Sym.names(t)

# Each name's offset in strtab(ns, pre), from at.
def stroffs(ns: List<&2, String>, +pre: String, +at: U32) -> List<&2, U32>:
  match ns:
    case Nil{}:
      Nil{}
    case n <> t:
      at <> stroffs(t, pre, (at + U32.inc(len32(bytes(pre ++ n))) : U32))

def U32.dec(+x: U32) -> U32:
  (x - 1 : U32)

def P.last32(xs: List<&2, U32>) -> U32:
  match xs:
    case Nil{}:
      0
    case x <> Nil{}:
      x
    case x <> t:
      P.last32(t)

# Mach-O
# ======

# An nlist_64: name offset, type, section, value.
def macho.nlist(+strx: U32, +ty: U32, +sect: U32, +value: U32) -> List<&2, U32>:
  [strx, (ty .|. (sect << 8n : U32) : U32), value, 0]

def macho.syms(ss: List<&2, Sym>, offs: List<&2, U32>, +ty: U32) -> List<&2, U32>:
  match ss offs:
    case Sym{n, +at, e} <> st +o <> ot:
      List.append(&2, U32, macho.nlist(o, ty, 1, at), macho.syms(st, ot, ty))
    case a b:
      Nil{}

def macho.undef(offs: List<&2, U32>) -> List<&2, U32>:
  match offs:
    case Nil{}:
      Nil{}
    case +o <> t:
      List.append(&2, U32, macho.nlist(o, 1, 0, 0), macho.undef(t))

# A relocation_info: kind 2 branch26 (pc-relative), 3 page21 (pc-relative),
# 4 pageoff12; every one names a symbol (extern), 4 bytes long.
def macho.rel.go(+at: U32, +sym: U32, +kind: U32) -> List<&2, U32>:
  +pc = Bool.pick(U32, U32.is_eq(kind, 4), 0, 1)
  [at, (sym .|. ((pc << 24n : U32) .|. ((2 << 25n : U32) .|. ((1 << 27n : U32) .|. (kind << 28n : U32) : U32) : U32) : U32) : U32)]

# (Kind 5, a b to a symbol, is a branch26 too.)
def macho.rel(+at: U32, +sym: U32, +kind: U32) -> List<&2, U32>:
  macho.rel.go(at, sym, Bool.pick(U32, U32.is_eq(kind, 5), 2, kind))

def macho.rels(rs: List<&2, Rel>, +names: List<&2, String>, +base: U32, +data: String, +dsym: U32) -> List<&2, U32>:
  match rs:
    case Nil{}:
      Nil{}
    case Rel{+at, +s, +k} <> t:
      List.append(&2, U32, macho.rel(at, Bool.pick(U32, Str.eq(s, data), dsym, (base + Str.index(names, s, 0) : U32)), k),
        macho.rels(t, names, base, data, dsym))

# A relocatable Mach-O object for arm64: header, one segment with the code
# (__TEXT,__text, page-aligned) and the slots (__DATA,__data), a build
# version, the symbol table and its dynamic-linker view.
def macho.go(+text: List<&2, U32>, +nslots: U32, +rs: List<&2, Rel>, tab: Tab) -> List<&2, U32>:
  Tab{+locals, +globals, u} = tab
  +undef = Tab.undef(rs, "bn_slots", Set.new(), Nil{})
  +tsize = (4 * len32(text) : U32)
  +pad = (tsize .&. 4 : U32)
  +dsize = (8 * nslots : U32)
  +dat = (tsize + pad : U32)
  +nl = U32.inc(lens(Sym.names(locals)))
  +ng = lens(Sym.names(globals))
  +nu = lens(undef)
  +nrel = U32.from_nat(List.length(&2, Rel, rs))
  +toff = {392 : U32}
  +reloff = (toff + (dat + dsize : U32) : U32)
  +symoff = (reloff + (8 * nrel : U32) : U32)
  +stroff = (symoff + (16 * ((nl + ng : U32) + nu : U32) : U32) : U32)
  +lnames = List.append(&2, String, Sym.names(locals), ["bn_slots"])
  +allnames = List.append(&2, String, lnames, List.append(&2, String, Sym.names(globals), undef))
  +strs = {0 <> strtab(allnames, "_") : List<&2, U32>}
  +strw = bytes.pack(strs)
  +offs = stroffs(allnames, "_", 1)
  +loffs = List.take(&2, U32, offs, U32.to_nat(nl))
  +goffs = List.drop(&2, U32, offs, U32.to_nat(nl))
  +uoffs = List.drop(&2, U32, goffs, U32.to_nat(ng))
  +header = {[4277009103, 16777228, 0, 1, 4, 360, 0, 0] : List<&2, U32>}
  +seg = List.append(&2, U32, [25, 232], List.append(&2, U32, zeros(4n),
    [0, 0, (dat + dsize : U32), 0, toff, 0, (dat + dsize : U32), 0, 7, 7, 2, 0]))
  +stext = List.append(&2, U32, name16("__text"), List.append(&2, U32, name16("__TEXT"),
    [0, 0, tsize, 0, toff, 12, reloff, nrel, 2147484672, 0, 0, 0]))
  +sdata = List.append(&2, U32, name16("__data"), List.append(&2, U32, name16("__DATA"),
    [dat, 0, dsize, 0, (toff + dat : U32), 3, 0, 0, 0, 0, 0, 0]))
  +build = {[50, 24, 1, 917504, 0, 0] : List<&2, U32>}
  +symtab = {[2, 24, symoff, ((nl + ng : U32) + nu : U32), stroff, (4 * len32(strw) : U32)] : List<&2, U32>}
  +dysym = List.append(&2, U32, [11, 80, 0, nl, nl, ng, (nl + ng : U32), nu], zeros(12n))
  +lsyms = List.append(&2, U32, macho.syms(locals, loffs, 14),
    macho.nlist(P.last32(loffs), 14, 2, dat))
  List.concat(&2, U32, [header, seg, stext, sdata, build, symtab, dysym, text,
    Bool.pick(List<&2, U32>, U32.is_zero(pad), Nil{}, [0]), zeros(U32.to_nat((2 * nslots : U32))),
    macho.rels(rs, undef, (nl + ng : U32), "bn_slots", U32.dec(nl)),
    lsyms, macho.syms(globals, goffs, 15), macho.undef(uoffs), strw])

def macho(text: List<&2, U32>, +nslots: U32, rs: List<&2, Rel>, ss: List<&2, Sym>) -> List<&2, U32>:
  macho.go(text, nslots, rs, Tab.split(ss, Tab{Nil{}, Nil{}, Nil{}}))

# ELF
# ===

# An Elf64_Sym: name offset, info (bind << 4 | type), section, value (and
# no size).
def elf.sym(+name: U32, +info: U32, +shndx: U32, +value: U32) -> List<&2, U32>:
  [name, (info .|. (shndx << 16n : U32) : U32), value, 0, 0, 0]

def elf.syms(ss: List<&2, Sym>, offs: List<&2, U32>, +info: U32) -> List<&2, U32>:
  match ss offs:
    case Sym{n, +at, e} <> st +o <> ot:
      List.append(&2, U32, elf.sym(o, info, 1, at), elf.syms(st, ot, info))
    case a b:
      Nil{}

def elf.undef(offs: List<&2, U32>) -> List<&2, U32>:
  match offs:
    case Nil{}:
      Nil{}
    case +o <> t:
      List.append(&2, U32, elf.sym(o, 16, 0, 0), elf.undef(t))

# An Elf64_Rela with no addend (the instruction's field is zero): kind 2
# is R_AARCH64_CALL26 (bl), 5 JUMP26 (b), 3 ADR_PREL_PG_HI21, 4
# ADD_ABS_LO12_NC.
def elf.rel(+at: U32, +sym: U32, +kind: U32) -> List<&2, U32>:
  +ty = Bool.pick(U32, U32.is_eq(kind, 2), 283, Bool.pick(U32, U32.is_eq(kind, 5), 282,
    Bool.pick(U32, U32.is_eq(kind, 3), 275, 277)))
  [at, 0, ty, sym, 0, 0]

def elf.rels(rs: List<&2, Rel>, +names: List<&2, String>, +base: U32, +data: String, +dsym: U32) -> List<&2, U32>:
  match rs:
    case Nil{}:
      Nil{}
    case Rel{+at, +s, +k} <> t:
      List.append(&2, U32, elf.rel(at, Bool.pick(U32, Str.eq(s, data), dsym, (base + Str.index(names, s, 0) : U32)), k),
        elf.rels(t, names, base, data, dsym))

# An Elf64_Shdr (at address 0).
def elf.sh(+name: U32, +ty: U32, +flags: U32, +off: U32, +size: U32, +link: U32, +info: U32, +align: U32,
  +entsize: U32) -> List<&2, U32>:
  [name, ty, flags, 0, 0, 0, off, 0, size, 0, link, info, align, 0, entsize, 0]

def elf.names() -> List<&2, String>:
  [".text", ".bss", ".rela.text", ".symtab", ".strtab", ".shstrtab", ".note.GNU-stack"]

def elf.at(+offs: List<&2, U32>, +i: Nat) -> U32:
  Maybe.default(&2, U32, List.get(&2, U32, offs, i), 0)

# A relocatable ELF object for AArch64: the header, the code (.text, aligned
# to a page), the slots (.bss), the code's relocations, the symbol table
# (the null symbol, locals, globals, undefined names), its names, the
# section names, an empty .note.GNU-stack (the stack is not executable), and
# the section headers.
def elf.go(+text: List<&2, U32>, +nslots: U32, +rs: List<&2, Rel>, tab: Tab) -> List<&2, U32>:
  Tab{+locals, +globals, u} = tab
  +undef = Tab.undef(rs, "bn_slots", Set.new(), Nil{})
  +tsize = (4 * len32(text) : U32)
  +pad = (tsize .&. 4 : U32)
  +nl = U32.inc(lens(Sym.names(locals)))
  +ng = lens(Sym.names(globals))
  +nu = lens(undef)
  +nsym = U32.inc(((nl + ng : U32) + nu : U32))
  +nrel = U32.from_nat(List.length(&2, Rel, rs))
  +reloff = ((64 + tsize : U32) + pad : U32)
  +symoff = (reloff + (24 * nrel : U32) : U32)
  +stroff = (symoff + (24 * nsym : U32) : U32)
  +lnames = List.append(&2, String, Sym.names(locals), ["bn_slots"])
  +allnames = List.append(&2, String, lnames, List.append(&2, String, Sym.names(globals), undef))
  +strw = bytes.pack(0 <> strtab(allnames, ""))
  +offs = stroffs(allnames, "", 1)
  +loffs = List.take(&2, U32, offs, U32.to_nat(nl))
  +goffs = List.drop(&2, U32, offs, U32.to_nat(nl))
  +uoffs = List.drop(&2, U32, goffs, U32.to_nat(ng))
  +shw = bytes.pack(0 <> strtab(elf.names(), ""))
  +soffs = stroffs(elf.names(), "", 1)
  +shsoff = (stroff + (4 * len32(strw) : U32) : U32)
  +end = (shsoff + (4 * len32(shw) : U32) : U32)
  +shpad = (end .&. 4 : U32)
  +shoff = (end + shpad : U32)
  +header = {[1179403647, 65794, 0, 0, 11993089, 1, 0, 0, 0, 0, shoff, 0, 0, 64, 4194304, 393224] : List<&2, U32>}
  +shs = List.concat(&2, U32, [zeros(16n),
    elf.sh(elf.at(soffs, 0n), 1, 6, 64, tsize, 0, 0, 4096, 0),
    elf.sh(elf.at(soffs, 1n), 8, 3, reloff, (8 * nslots : U32), 0, 0, 8, 0),
    elf.sh(elf.at(soffs, 2n), 4, 64, reloff, (24 * nrel : U32), 4, 1, 8, 24),
    elf.sh(elf.at(soffs, 3n), 2, 0, symoff, (24 * nsym : U32), 5, U32.inc(nl), 8, 24),
    elf.sh(elf.at(soffs, 4n), 3, 0, stroff, (4 * len32(strw) : U32), 0, 0, 1, 0),
    elf.sh(elf.at(soffs, 5n), 3, 0, shsoff, (4 * len32(shw) : U32), 0, 0, 1, 0),
    elf.sh(elf.at(soffs, 6n), 1, 0, shoff, 0, 0, 0, 1, 0)])
  +lsyms = List.append(&2, U32, elf.syms(locals, loffs, 0), elf.sym(P.last32(loffs), 1, 2, 0))
  List.concat(&2, U32, [header, text, Bool.pick(List<&2, U32>, U32.is_zero(pad), Nil{}, [0]),
    elf.rels(rs, undef, U32.inc((nl + ng : U32)), "bn_slots", nl),
    zeros(6n), lsyms, elf.syms(globals, goffs, 18), elf.undef(uoffs), strw, shw,
    Bool.pick(List<&2, U32>, U32.is_zero(shpad), Nil{}, [0]), shs])

def elf.file(text: List<&2, U32>, +nslots: U32, rs: List<&2, Rel>, ss: List<&2, Sym>) -> List<&2, U32>:
  elf.go(text, nslots, rs, Tab.split(ss, Tab{Nil{}, Nil{}, Nil{}}))

# Objects
# =======

type Obj is Data:
  Obj{words: List<&2, U32>, errs: List<&2, String>}

def object.fmt(elf: Bool, text: List<&2, U32>, +nslots: U32, rs: List<&2, Rel>, ss: List<&2, Sym>) -> List<&2, U32>:
  match elf:
    case True{}:
      elf.file(text, nslots, rs, ss)
    case False{}:
      macho(text, nslots, rs, ss)

def object.enc(elf: Bool, +ss: List<&2, Sym>, +nslots: U32, e: Enc) -> Obj:
  Enc{ws, rs, es} = e
  Obj{object.fmt(elf, List.reverse(&2, U32, ws), nslots, List.reverse(&2, Rel, rs), ss), es}

def object.lay(elf: Bool, +ins: List<&2, Ins>, +nslots: U32, l: Lay) -> Obj:
  Lay{+m, +ss, size} = l
  object.enc(elf, ss, nslots, enc(ins, 0, m, Enc{Nil{}, Nil{}, Nil{}}))

# Peephole
# ========
#
# A reload right after a store to the same frame slot (str rt, [sp, #k];
# ldr ru, [sp, #k]) is dropped when ru is rt, else it becomes mov ru, rt;
# a move back (mov a, b; mov b, a) is dropped.
# Labels are instructions of their own, so nothing jumps between the two.

def peep.hit(+s: U32, +l: U32) -> Bool:
  Bool.and(U32.is_eq((s .&. 4290773984 : U32), 4177527776),
    Bool.and(U32.is_eq((l .&. 4290773984 : U32), 4181722080),
      U32.is_eq((s .&. 4193280 : U32), (l .&. 4193280 : U32))))

def peep.mov(+w: U32) -> Bool:
  U32.is_eq((w .&. 4292935648 : U32), 2852127712)

# mov a, b then mov b, a: the second does nothing.
def peep.back(+s: U32, +l: U32) -> Bool:
  Bool.and(Bool.and(peep.mov(s), peep.mov(l)),
    Bool.and(U32.is_eq((l .&. 31 : U32), ((s >> 16n : U32) .&. 31 : U32)),
      U32.is_eq(((l >> 16n : U32) .&. 31 : U32), (s .&. 31 : U32))))

def peep.ps.go(+l: U32, +s: U32, +r: List<&2, Ins>) -> List<&2, Ins>:
  Bool.pick(List<&2, Ins>, peep.hit(s, l),
    Bool.pick(List<&2, Ins>, U32.is_eq((s .&. 31 : U32), (l .&. 31 : U32)), IW{s} <> r,
      IW{mov((l .&. 31 : U32), (s .&. 31 : U32))} <> IW{s} <> r),
    IW{l} <> IW{s} <> r)

def peep.ps(+l: U32, +s: U32, +r: List<&2, Ins>) -> List<&2, Ins>:
  Bool.pick(List<&2, Ins>, peep.back(s, l), IW{s} <> r, peep.ps.go(l, s, r))

def peep.pa(+l: U32, a: Ins, r: List<&2, Ins>) -> List<&2, Ins>:
  match a:
    case IW{s}:
      peep.ps(l, s, r)
    case ILab{x}:
      IW{l} <> ILab{x} <> r
    case ISym{x, e}:
      IW{l} <> ISym{x, e} <> r
    case IB{w, x}:
      IW{l} <> IB{w, x} <> r
    case IBc{w, x}:
      IW{l} <> IBc{w, x} <> r
    case IBt{w, x}:
      IW{l} <> IBt{w, x} <> r
    case IAdr{d, x}:
      IW{l} <> IAdr{d, x} <> r
    case ICall{w, x}:
      IW{l} <> ICall{w, x} <> r
    case IAdrS{d, x}:
      IW{l} <> IAdrS{d, x} <> r

def peep.pw(+l: U32, acc: List<&2, Ins>) -> List<&2, Ins>:
  match acc:
    case Nil{}:
      [IW{l}]
    case a <> r:
      peep.pa(l, a, r)

def peep.push(h: Ins, acc: List<&2, Ins>) -> List<&2, Ins>:
  match h:
    case IW{l}:
      peep.pw(l, acc)
    case ILab{x}:
      ILab{x} <> acc
    case ISym{x, e}:
      ISym{x, e} <> acc
    case IB{w, x}:
      IB{w, x} <> acc
    case IBc{w, x}:
      IBc{w, x} <> acc
    case IBt{w, x}:
      IBt{w, x} <> acc
    case IAdr{d, x}:
      IAdr{d, x} <> acc
    case ICall{w, x}:
      ICall{w, x} <> acc
    case IAdrS{d, x}:
      IAdrS{d, x} <> acc

def peep.go(xs: List<&2, Ins>, acc: List<&2, Ins>) -> List<&2, Ins>:
  match xs:
    case Nil{}:
      List.reverse(&2, Ins, acc)
    case h <> t:
      peep.go(t, peep.push(h, acc))

def peep(xs: List<&2, Ins>) -> List<&2, Ins>:
  peep.go(xs, Nil{})

# The object file for code with nslots data slots: ELF, or Mach-O.
def object(c: Code, +nslots: U32, elf: Bool) -> Obj:
  +ins = peep(Code.flat(c))
  object.lay(elf, ins, nslots, lay(ins, 0, Map.new(&2, U32), Nil{}))
