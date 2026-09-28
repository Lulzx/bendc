<h1 align="center">bendc</h1>

<p align="center">
  <b>A self-hosting compiler for <a href="https://bend-lang.com">Bend 2</a>, written in Bend 2.</b><br>
  Bend in, C out. The compiler compiles itself, and the output reproduces itself byte for byte.
</p>

<p align="center">
  <a href="https://github.com/Lulzx/bendc/actions/workflows/ci.yml"><img alt="CI" src="https://github.com/Lulzx/bendc/actions/workflows/ci.yml/badge.svg"></a>
  <img alt="language" src="https://img.shields.io/badge/written%20in-Bend%202-6f42c1">
  <img alt="target" src="https://img.shields.io/badge/target-C-555">
  <a href="LICENSE"><img alt="license" src="https://img.shields.io/badge/license-MIT-blue"></a>
</p>

---

```
$ ./bootstrap.sh
[stage0] bend boot.bend -o build/bendc0           # the official Bend builds bendc once
[stage1] bendc0 -> build/stage1.c                 # bendc compiles itself
[stage2] stage1 -> build/stage2.c                 # the result compiles itself again
fixpoint: stage1.c == stage2.c (44696 lines)
tests with stage1: 80 passed, 0 failed
tests with stage2: 80 passed, 0 failed
```

`bendc.bend` (the compiler) and `check.bend` (the type checker) are Bend: about 22,000 lines that
`bend --check-only` accepts: `check.bend` outright, and `bendc.bend` with exit status 1 since Bend
2.0.32, which lists the 18 defs that rely on foreign code (the package fetcher `Hub.ensure`, which
imports C, and its callers); bendc's checker prints the same report. bendc type-checks
a program the way the official checker does (a port of it, with the same error reports), then lexes, parses, erases, and code-generates it, including the
parts of Bend's standard library (`Base`) that the program uses. The result is a single C file that
clang builds against the runtime (`rt/bendrt.h`): a garbage collector, native `Nat` and arrays, a
work-stealing pool for parallel calls, an event loop that speaks the official effect ABI, and a GPU
backend that runs `f!(x)` calls on Metal.

## Contents

- [Quick start](#quick-start)
- [What it looks like](#what-it-looks-like)
- [Bootstrapping](#bootstrapping)
- [Language support](#language-support)
- [How it works](#how-it-works)
- [The GPU backend](#the-gpu-backend)
- [The native backend](#the-native-backend)
- [Benchmarks](#benchmarks)
- [Writing a compiler under Bend's rules](#writing-a-compiler-under-bends-rules)
- [Testing](#testing)
- [Limitations](#limitations)
- [Repository layout](#repository-layout)

## Quick start

You need a C compiler (clang) and a [Bend install](https://bend-lang.com), which provides `base.bend`:

```sh
curl -fsSL https://bend-lang.com/install.sh | sh    # the official Bend (provides ~/.bend/bend2/base.bend)

git clone https://github.com/Lulzx/bendc && cd bendc
make                  # builds build/bendc from the committed C seed, in about 2 seconds
make test             # compiles and runs every program in tests/, comparing with the official bend
```

Compile a program:

```sh
./build/bendc ~/.bend/bend2/base.bend hello.bend > hello.c
clang -O2 -I rt hello.c -o hello -lm && ./hello
```

`bendc --js <base.bend> file.bend > file.js` emits JavaScript instead (run it with `bun file.js`; see
[The JavaScript target](#the-javascript-target)). `bendc --check-only <base.bend> file.bend` only type-checks, printing what `bend --check-only` prints.
`bendc --no-check ...` compiles without checking. Debugging aids: `bendc --tokens file.bend` prints the
token stream after layout, and `bendc --ast file.bend` prints the parsed declarations.

A compiled program takes the official runtime's options: `--threads N` (default: the CPU count),
`--gpu on|off|SIZE` (`off` runs `f!(x)` calls on the CPU threads), `--bend-help`, and `--` before
the program's own arguments.

## What it looks like

A Bend program:

```python
import Base

type Shape is Data:
  Circle{r: U32}
  Square{s: U32}

def area(x: Shape) -> U32:
  match x:
    case Circle{+r}:
      (3 * r * r : U32)
    case Square{+s}:
      (s * s : U32)

def sum(xs: List<U32>, acc: U32) -> U32:
  match xs:
    case Nil{}:
      acc
    case Con{h, t}:
      sum(t, (acc + h : U32))

def adder(k: U32) -> U32 -> U32:
  x => (x + k : U32)
```

The C that `bendc` generates for it, unedited:

```c
static V F_area(V a0) {
top:;
V s0 = a0;
if (TAG(s0) == 0) {
return F_U32_dmul(F_U32_dmul(3u, FLD(s0, 0)), FLD(s0, 0));
} else if (TAG(s0) == 1) {
return F_U32_dmul(FLD(s0, 0), FLD(s0, 0));
} else { bend_fail("runtime fail-stop"); }
}

static V F_sum(V a0, V a1) {               // the tail call becomes a loop
top:;
V s33 = a0;
if ((s33) == IMM(0)) {
return a1;
} else if (TAG(s33) == 1) {
{ V t0 = FLD(s33, 1); V t1 = F_U32_dadd(a1, FLD(s33, 0)); a0 = t0; a1 = t1; goto top; }
} else { bend_fail("runtime fail-stop"); }
}

static V F_adder(V a0) {                   // lambdas are lifted into closures
top:;
return mk_clo(L35, 2, 1, (V[]){a0});
}
```

A `main` that returns a value, rather than `IO`, is evaluated, and the value is printed in Bend
syntax. This matches the official tool:

```python
def main() -> List<&2, Tree<String>> & Maybe<&2, Box> & Nat & Char & String & Bool:
  ([Node{Leaf{}, "a\n\"b\"", Node{Leaf{}, "c", Leaf{}}}, Leaf{}], Some{Box{3.0}}, 42n, '\'', "tab\there", True{})
```
```
([Node{Leaf{}, "a\n\"b\"", Node{Leaf{}, "c", Leaf{}}}, Leaf{}], Some{Box{3.0}}, 42n, '\'', "tab\there", True{})
```

## Bootstrapping

```mermaid
flowchart LR
    boot[boot.bend] -->|official bend| s0[stage0 binary]
    src -->|stage0| c1[stage1.c]
    c1 -->|clang| s1[stage1 binary]
    src -->|stage1| c2[stage2.c]
    c1 -. byte-identical .- c2
    c2 -.-> seed[seed/bendc.c]
```

- **`make bootstrap`** does the full chain. The official `bend` builds stage0 from `boot.bend`, an
  entry that reaches bendc's C code generator but not its type checker or JavaScript backend (stage0
  only translates `bendc.bend` with `--no-check`). Stage0 compiles `bendc.bend` into `stage1.c`, and
  stage1 compiles it again into `stage2.c`. The two C files must be identical, and stage1 and stage2
  must pass the test suite.
- **Memory.** The official compiler's footprint grows with the code `main` reaches, and it expands a
  `match` on string literals char by char (and a large `Nat` literal level by level), copying the
  other arms into every branch. bendc avoids such patterns, so building stage0 takes about 16 s and
  4 GB (building all of `bendc.bend` would take about 70 s and 10 GB).
- **`seed/bendc.c`** is the committed fixpoint, the way self-hosting compilers usually ship a seed.
  Building `bendc` needs only a C compiler. `make selfcheck` verifies that the current `bendc.bend`
  still compiles to exactly this seed, and `make seed` regenerates it after the compiler changes.
- **`make ddc`** checks the seed by diverse double-compiling ([Wheeler,
  2009](https://dwheeler.com/trusting-trust/)): a 45,000-line generated C file can't be audited
  by reading it, so a compiler that plants something in its own output would survive every
  fixpoint above. `tools/ddc.sh` compiles `bendc.bend` twice, once with a stage0 the official Bend
  translates to C and GCC builds, once with the seed GCC builds. Both outputs must equal
  `seed/bendc.c` byte for byte. The first path shares nothing with the seed (not its C, and not
  clang, which the official `bend -o` calls), so a tampered seed would have to be matched by the
  official Bend and GCC together. It needs GCC 15 or newer (the official C uses `musttail`). On
  arm64 a third leg builds bendc with its own native backend (see [The native
  backend](#the-native-backend)) and checks that it compiles `bendc.bend` to the seed too.
- **`make tcc`** builds the seed with the [Tiny C Compiler](https://repo.or.cz/tinycc.git), which
  [bootstrappable builds](https://bootstrappable.org) reach from a few hundred bytes of hex (through
  M2-Planet and GNU Mes), so bendc can join that chain. The tcc-built bendc must compile `bendc.bend`
  to the seed byte for byte, and the test suite must pass with tcc building the programs and the
  runtime (`tools/tcc.sh`; `TCC=...` picks the binary). It needs tinycc 0.9.28 (the `mob` branch):
  0.9.27 has no `stdatomic.h`. Under tcc the runtime keeps per-thread state in a pthread key (tcc
  has no thread-local storage in Mach-O), `main` runs the constructors itself (tcc ignores
  `__attribute__((constructor))`), and `!`-calls have the simulator and the CPU but not Metal.

CI runs the whole chain on Linux (arm64) and macOS: seed build, tests, selfcheck, full bootstrap,
`make ddc` (on macOS, with Homebrew's GCC), and `make tcc` (on Linux, with tinycc built from a
pinned commit). It
pins the official Bend it tests against (`tools/install-bend.sh`, Bend 2.0.32),
and a weekly run tries the latest release, so a new Bend shows up there before it breaks a push.

## Language support

| Area | Supported |
|---|---|
| Declarations | `type` (with type parameters, `is Data` / `is Type`), `def`, `law`, `@unsafe`, `import Base`, `import ./file.bend as M` |
| Proofs | laws and proofs are accepted and erased at runtime: `{==}`, `{a == b : T}`, `%e : P` rewrites, `?holes`, dependent types |
| Patterns | several scrutinees at once; nested constructors; `h <> t`; tuples; `0n` / `1n+p`; char, number and **string** literals; `_`; `+x` |
| Bindings | `x = v`, `+x = v`, `-x = v`, `(a, b) = v`, `K{..} = v`, parallel lets `a b = f(x) g(y)` |
| Functions | closures, currying and partial application, templates (`~f`), `f!(x)` calls, and tail calls compiled to loops |
| Monads | `do M<..>:` for any monad (`IO`, `Maybe`, `Result`, your own), `x : T <- m`, `return` |
| Operators | `(a + b : T)` typed arithmetic, bitwise and comparison operators, `&&` `\|\|` `++` `<>` |
| Data | `U32`, `Nat`, `F32`, `Char`, `String`, lists, tuples, `Map`, `Set`, arrays (`[v : T*n]`, `a[i]`, `a[i] <- v`) |
| Effects | every Base effect but windows: printing, audio, `IO.args`, `IO.get_env`, files, TCP, UDP, `IO.now`/`sleep`/`random_u32`, concurrent `IO.fork`/`IO.join`/`IO.spawn` and channels, `IO.die` exit codes |
| Foreign code | `def f(..) -> IO(R): import "./f.c"` and `import "./f.js"` effects, written against the official C and JS effect ABIs (Base's own `effs/*.c` and `effs/*.js` are compiled this way) |
| Modules | `import ./file.bend as M`, and hub packages by content hash: `import 0x<hash>/main.bend as P` |
| Parallelism | parallel lets `a b = f(x) g(y)`, written or found by the compiler, run on a work-stealing thread pool; `f!(x)` calls run on the GPU (Metal), parallel lets inside them as GPU tasks |
| Checking | the official type checker, ported: quantities, termination, templates, laws and proofs, dependent types |
| Output | an `IO` main runs its effects; any other main prints its value in Bend syntax |

## How it works

```
source ─► lexer ─► layout ─► parser ─► operator  ─► tables ─► core IR ─► codegen ─► C file ─► clang ─► binary
          chars    INDENT/   (parser    resolution            erasure,    (state          +
          →tokens  DEDENT    monad)                           inlining    monad)       rt/bendrt.h
```

1. **Lexer and layout.** Characters become tokens, and indentation becomes `NEWLINE`/`INDENT`/`DEDENT`.
   A deeper line opens a block only after a `:`. Otherwise it continues the previous line, and so
   does a line after one that ends in an operator. Newlines inside brackets are ignored.
2. **Parser.** Recursive descent, written with a parser monad `Toks -> A & Toks` and Bend's own
   `do`-notation. Statements fold into `let`/`match`/bind expressions, and `do` blocks desugar into
   `M.bind`/`M.pure` calls. Types are terms in Bend, so they parse with the expression grammar;
   `List<a, A>` is recognised by the missing space before `<`, and `>>` is split when it closes one.
3. **Operator resolution.** `(a + b : T)` becomes `T.add(a, b)`, with the type taken from the nearest
   annotation. Unannotated operators belong to `Nat`.
4. **Tables and erasure.** Every constructor gets a tag, an arity and a representation. Every def gets
   a mask of its runtime parameters. Erased parameters (`-x`, bare quantity parameters, and
   `Type`/`Data`/`Kind`-typed ones) are dropped at each known call site. Parameters of a def that
   fills a `law` take their modes from the law.
5. **Core IR.** Each def (but a type-level one, whose body the printers unfold) is lowered to
   [`core.bend`](core.bend)'s IR, where every argument of a call of a global def is marked relevant
   or erased by the callee's mask. `Core.Def.erase` replaces the erased arguments, and the types left
   in runtime positions, with a box. [`PROOF.bend`](PROOF.bend) proves that this preserves the IR's
   semantics, which `core.bend` gives in Bend as a fuelled machine (`Core.run`): the law
   ([`LAWS.bend`](LAWS.bend)) says running a program and erasing the result gives what running the
   erased program gives. Then full calls of a monad's `bind`, `pure`,
   `go` and `go.done` (the parser's, the generator's, the checker's) are inlined. The callee is
   renamed apart, each argument takes its parameter's place when that moves no work into a lambda,
   and the places it lands are reduced: an applied lambda becomes a `let`, and a `let` of a known
   constructor binds its fields. A `do` block becomes one closure, and the
   checker, which runs on these monads, runs 9% fewer instructions. Last, `Core.Def.red` turns
   every lambda applied to one argument, `(p => b)(a)`, into `let p = a; b`, anywhere in the def.
   [`REDPROOF.bend`](REDPROOF.bend) proves the law in [`RED.bend`](RED.bend): if a run does not run
   out of fuel, the reduced program, with as much fuel or more, gives the same result, reduced
   (`red_ok`; `red_prog` for a program's `main`). The let takes fewer steps than the application,
   so the proof shows that more fuel does not change a result that did not run out (`L.mono`), and
   that in one program the application and the let give the same result (`L.beta.law`). Like
   erasure's proof, it assumes that the natives commute with the pass (`ok`); it also assumes that
   a native gives one value or fails (`one`). Then `Core.Def.known` resolves each `match` on a
   known constructor `K{as}`: it drops each case whose pattern is another constructor's, and when
   the first case left is `K`'s with a variable for each field, it makes the match one on `as`
   with that case alone, which bendc compiles as lets (no `K` is built). A field pattern that can
   fail keeps the match, since its case can move on to the next. [`KNOWNPROOF.bend`](KNOWNPROOF.bend)
   proves the law in [`KNOWN.bend`](KNOWN.bend), `known_ok` (and `known_prog`), stated as
   `red_ok` is, with the same assumptions; the resolved match takes no more steps than the source,
   and in one program the two give the same result (`K.mat`). The proven functions are the ones
   bendc runs; the inliner no longer resolves matches itself. The inliner's own rules (the
   substitution of arguments, a `let` of a known constructor, applications of more than one
   argument) are not proven, nor are lowering, raising back to an `Expr`, or code generation. Both
   checkers verify the three proofs in CI.
6. **Code generation.** A state monad threads fresh names, emitted C, references and errors through
   the generator. Only defs reachable from `main` are emitted.
   - Each def becomes a C function, and self tail calls become `goto` loops.
   - Defs that build their result around a tail call (`x <> merge(xt, ys)`) are compiled
     destination-passing: see [Benchmarks](#benchmarks).
   - Lambdas are lambda-lifted using free-variable analysis.
   - A call with every argument goes direct; with fewer it builds a partial closure; with more it
     goes through `apply`.
   - A match becomes a first-match `if` chain over tags. A `match` or `let` in expression position
     uses a GNU statement expression.
7. **Value printers.** For a non-`IO` main, printers are generated from main's return type and the
   field types of each constructor, specialised per type instance (e.g. `Tree<String>`).

**Runtime** (`rt/bendrt.h`, about 520 lines). Every value is one 64-bit word:

| Value | Representation |
|---|---|
| `U32`, `Char`, `F32` | the raw number (`F32` as IEEE bits) |
| `Nat` | the raw number, at most 2^48 - 1 (as in the official runtime; past it is an error) |
| `Array<T>` | pointer to a flat block of 2^depth cells, written in place (a shared array is one block) |
| nullary constructor (`Nil{}`, `True{}`) | `(tag << 3) \| 1` |
| constructor with fields | pointer to `{tag, fields...}` |
| one constructor with one field (`Chr{code}`) | the field itself |
| closure | pointer to `{fn, arity, nargs, args...}` |

Base implements `U32` as a 32-bit vector of `Bool`s, which proofs can reason about. `bendc` replaces
those defs, and the `Nat`/`F32`/`Array` primitives, with native C; `Nat` arithmetic stops with an
error past 2^48 - 1, where the official runtime does. Memory is managed by a conservative mark-sweep collector: the threads that run
Bend code are stopped with a signal while it marks their stacks. The program runs on a thread with a
4 GB stack, so deep non-tail recursion is fine: a million-deep recursive list builds and folds in about
0.1s, where the official runtime overflows its stack at 100,000.

A parallel let forks every value but the last onto a Chase-Lev work-stealing deque and joins them in
reverse; a fork nobody stole runs inline, so fine-grained recursion stays cheap (`pow2!(26n)` from the
guide takes 0.70s on one thread, 0.15s on eight).

Parallel lets are also found. Bend is pure, so the operands of one node (an operator's, a call's
arguments, a constructor's fields) may run in any order. Where two or more of them call back into
the def, as in `fib(n - 1) + fib(n - 2)` or `merge(msort(a), msort(b))`, `bendc` turns them into a
parallel let, and the fork depth above keeps the small calls cheap. An argument the callee erases or
never reads stays where it is. The pass is on by default and `BEND_AUTO_PAR=0` turns it off. With
`BEND_NO_FREE=1` it defaults to off (`BEND_AUTO_PAR=1` turns it back on), because a compiler's tree
walks are small and called often, and forking them made bendc's self-build 60% slower. `fib 44`
runs 4.5x faster on 12 cores, and `sort` in [Benchmarks](#benchmarks) 2.4x.

IO follows Base's continuation-passing `IO` type. An effect call becomes a request node that an event
loop answers, as in the official runtime: computations run their pure code up to their next effect,
`IO.fork` computations run concurrently, blocking work parks, and a deadlock is reported. Effects use the
official ABI (`Term`, `Env`, `IoWork`, `io_eff`, `CID_*`), so the `.c` files that effect defs import,
Base's own `effs/*.c` included, are spliced into the output unchanged.

## The GPU backend

A `f!(x)` call hands the call, and every parallel let inside it, to the GPU. `bendc` compiles every
function the call can reach into one kernel, a flat state machine: each function is a set of blocks
(a call ends a block, and the callee returns to the next one), locals live in frame slots, and `pc`
names the block to run. A parallel let pushes its values as tasks to a lock-free queue and continues
through a join record, so no lane ever waits: the lane that brings a join its last value runs the
rest of the function. Past a fork depth that fills the lanes, parallel lets run in order. A def that
only matches, binds, builds constructors, calls natives and other such defs, and calls itself in tail
position is *flat*: it becomes a plain device function with its locals in registers and a loop for its
tail calls.

Below the fork depth, a def that is flat but for its parallel lets and calls to itself becomes
`KQ_name`: its parallel lets run in order, its locals stay in registers, and a call to itself saves
only the variables used after it, with a resume label, on a small thread-private stack (a tail call is
a jump). The lanes of a SIMD group run in lockstep, so a lane that entered such a call alone would
hold its 31 neighbours up for the whole subtree; instead a lane waits at the call until each lane of
its group waits too or has nothing to do, and they run their calls together. Calls of looping flat
defs are gathered the same way. A 2^30-leaf fork tree runs in 0.14s on an M4 Pro's GPU, against
0.24s for the official runtime (see [Benchmarks](#benchmarks)).

The kernel's text (`rt/gpu.h` plus the generated blocks) compiles both as Metal Shading Language and
as C. The host (`rt/gpuhost.h`) reaches Metal through the Objective-C runtime and asks the linker
for Metal itself, so programs need no extra link flags. The first run of a program keeps its
compiled kernels in `~/Library/Caches/bend` (see [Benchmarks](#benchmarks)). Memory is unified: the
device reads the arguments where they are in the CPU heap, builds new objects in an arena, and the
host copies the result back into the heap. Anything the
device cannot do (an effect, a `Nat` past 2^63, a full arena, a closure made by a CPU lambda) stops
the device, and the call runs on the CPU instead, so a `!` never changes what a program prints.

```sh
BEND_GPU_LOG=1 ./prog       # say where each !-call ran
BEND_GPU=sim ./prog         # run the kernel in its C form, lanes interleaved (any OS)
./prog --gpu off            # !-calls on the CPU threads
```

`BEND_GPU_LANES` (default 8192), `BEND_GPU_MB` (arena size) and `BEND_GPU_FORK` (fork depth, default
log2 of the lanes plus 2) tune the device.
Without Metal (Linux), `!` runs on the CPU threads, as the official runtime does without a GPU.

## The JavaScript target

`bendc --js` emits one JavaScript file: the runtime (`rt/bendrt.js`, embedded in bendc through
`rt/rtjs.bend`), the `.js` files the program's effects import, and the program. Values are what the
official JS target uses, so JS effects written for it run unchanged: a `U32` or `F32` is a number, a
`Nat` a `BigInt`, a `Bool` a boolean, a `Char` a one-code-point string, a `String` a string, and any
other constructor an object `{$: "Name", field: value}`. Functions are curried JS functions, and self
tail calls become loops. Effects are requests answered by an event loop with the official helpers
(`io_done`, `io_fail`, `io_tup`, `io_park_on`, `io_sys`, ...); the ones that make system calls use
`bun:ffi`, so run the output with Bun. Parallel lets run one value after the other.

## The native backend

`bendc --native -o prog base.bend prog.bend` compiles a program to AArch64 machine code without a C
compiler seeing it. The code generator (the "Native code generation" section of `bendc.bend`) and
the assembler and object writer ([`asm.bend`](asm.bend)) are Bend. bendc encodes the instructions,
lays out the code, resolves its labels, and writes the relocatable object itself: Mach-O on macOS,
ELF on Linux (`Cc.elf` asks the host which). The system linker then links it with the runtime.

- **What still goes through `cc`.** The runtime (`build/bendrt.o`, compiled once), `rt/native.c`
  (external names for the runtime's inline natives, compiled once as `natives.o`), and the C of the
  program's effects (their sources from Base's `effs/*.c`, with the ids they use), which bendc
  writes next to the object. `cc` also links them.
- **Same runtime, same ABI.** The code starts from the same lowered defs as the C generator and keeps
  the runtime's value representation (see [How it works](#how-it-works)) and AAPCS64, so it calls
  the runtime's functions (`apply`, `str_cache`, the allocator, the effect loop) as C does.
- **Code shape.** Every value lives in a frame slot and an expression leaves its value in `x0`. A
  def with at most 8 kept parameters takes them in `x0`..`x7`; a wider one takes the address of a
  row of arguments. A self tail call stores the new arguments over the parameters and branches back,
  and a tail call to another narrow def pops the frame and branches. Integer, `U32` and `F32`
  natives are inlined (`add`, compares, shifts, `fadd`, `fmul`, `fcmp`, `ucvtf`, ...); the others
  call their `N_` name in `rt/native.c`. A peephole pass turns a reload right after a store to the
  same slot into a register move. String literals are cached in data slots as the C backend does.
- **Coverage.** All 26 programs in `tests/` pass with `--native` on macOS (arm64) and on Linux
  (arm64, in Docker), and `run_tests.sh` runs them there. bendc compiles itself with `--native`:
  the native bendc prints the same C for `bendc.bend` as the C build, and the object it writes for
  itself is the one the C build writes, byte for byte. `tools/ddc.sh` has this as a third leg: the
  seed, built by GCC, compiles `bendc.bend` natively, and that bendc compiles `bendc.bend` to
  `seed/bendc.c`.

What it does not do, against the C backend:

- Matches do not free what they open (programs run as with `BEND_NO_FREE=1`), so allocation-heavy
  programs rely on the collector alone.
- Parallel lets run in order, on one thread, and `!`-calls run on the CPU.
- No destination passing: a def like `merge` recurses on the stack.
- No register allocation: every value goes through memory, which is what the numbers below mostly
  measure.
- AArch64 only. The target is picked by the host, so there is no cross-compiling.

Against the C backend (clang `-O2`), interleaved runs, best of 3, on an Apple M4 Pro that was
running other heavy jobs at the time (load average near 50), so only the ratios mean much:

| program | C backend | native | native / C |
|---|---|---|---|
| `forks 24` (1 thread) | 0.034s | 0.062s | 1.8 |
| `leaves 12` (1 thread) | 5.68s | 39.2s | 6.9 |
| `sort 1000000` (1 thread) | 0.314s | 0.535s | 1.7 |
| `forks 24` (C: all threads) | 0.011s | 0.060s | 5.7 |
| `leaves 12` (C: all threads) | 0.849s | 41.5s | 49 |
| `sort 1000000` (C: all threads) | 0.114s | 0.527s | 4.6 |
| bendc compiling `bendc.bend` to C | 1.52s | 2.73s | 1.8 |
| bendc checking `bendc.bend` | 3.16s | 6.87s | 2.2 |

On one thread, and for bendc itself, the native code takes 1.7 to 2.2 times as long, but for
`leaves`, a float loop, where it takes 7 times as long: clang keeps `x` in a float register and fuses `x * x * 0.5 + c` into
two instructions, while the native loop moves every value through its frame slot and between
integer and float registers. On all threads the gap is the missing parallel lets. Building is
where it wins: `bendc --native` builds bendc (check, code generation, assembly, link) in 3.5s,
where `bendc -o` takes 20s, most of it clang compiling 59,000 lines of C.

## Benchmarks

`bench/run.sh` builds each program in [`bench/`](bench) with bendc (`bendc -o`) and with the official
`bend` (2.0.25, `bend -o`), checks that both print the same thing, and reports the best of three runs
with its peak memory. Sizes come from the command line, so neither compiler can compute the answer at
compile time. On an Apple M4 Pro (12 cores, 24 GB, macOS 27):

| program | what it does | bendc | official bend | bendc memory | official memory |
|---|---|---|---|---|---|
| `forks 28` | a parallel let at every level of a 2^28-leaf tree, CPU threads | **0.06s** | 0.12s | 2.8 MB | 2.7 MB |
| `forks_gpu 28` | the same as a `!`-call, on the GPU | **0.07s** | 0.13s | **13.0 MB** | 13.3 MB |
| `leaves 14` | 16384 leaves of a 200,000-step `F32` loop, CPU threads | **0.68s** | 1.02s | 2.8 MB | 2.7 MB |
| `leaves_gpu 14` | the same as a `!`-call, on the GPU | **0.05s** | 0.10s | **13.1 MB** | 13.2 MB |
| `leaves_gpu 16` | the same with 65536 leaves | **0.08s** | 0.15s | 13.1 MB | 13.1 MB |
| `sort 1000000` | build, merge sort and sum a million `U32`s (allocation-heavy; bendc sorts the halves in parallel, see [How it works](#how-it-works)) | **0.14s** | 1.10s | 72.9 MB | **32.4 MB** |

| task | bendc | official bend |
|---|---|---|
| build `forks.bend` (source to binary) | **0.19s** | 0.31s |
| build `forks_gpu.bend` | **0.32s** | 0.55s |
| build `leaves.bend` | **0.19s** | 0.30s |
| build `leaves_gpu.bend` | **0.31s** | 0.55s |
| build `sort.bend` | **0.21s** | 0.32s |
| type-check `bendc.bend` (16,000 lines with `check.bend`) | 1.30s, **590 MB** | **0.77s**, 840 MB |
| build `bendc.bend` into a binary | **8.1s** | 70s, 9.9 GB |

Where the time goes:

- **Forks on the CPU.** A def that is flat but for its parallel lets and calls to itself gets a
  sequential clone, `S_name`. Each thread tracks its fork depth; past log2(threads) + 6 levels a
  parallel let runs its values in order through the clone: no closures, deque pushes or joins.
- **Forks and loops on the GPU.** See [The GPU backend](#the-gpu-backend): seq defs and looping flat
  defs run in their own small kernel (`bend_kq`), a whole SIMD group at a time. A `Nat` is a
  plain word, so a `1n+p` match is one compare. With a bignum check in it, `iter`'s loop was no
  longer a counted loop to Metal, and ran 2.4x slower.
- **Implicit forks.** `msort(a)` and `msort(b)`, the arguments of one `merge`, become a parallel
  let (see [How it works](#how-it-works)): `sort` takes 0.14s where it took 0.33s on one thread,
  for 73 MB where it took 30 (the halves are live at once).
- **Float loops on the CPU.** `iter`'s step, `x * x * 0.5 + c`, is a chain of three float operations,
  each waiting on the last. `bendc` emits `a * k + b` with a literal `k` as `F32_mulk_add`, one
  `fma` when `k` is a power of two and `a * k` a normal float: the product is then exact, so the
  `fma`'s one rounding is the add's, and the result the same to the bit. The chain is two operations,
  and `leaves` 17% faster; any other case branches to the two operations as written.
- **Builds.** The runtime is compiled once (`build/bendrt.o`, from `rt/bendrt_impl.c`), so a program
  compiles only its own code; bendc's own front end takes about 0.1s for these programs.
- **Building lists.** `merge` returns `x <> merge(xt, ys)`: a cell around a call. Such defs (a group
  of defs that tail-call one another, with such a cell on the cycle) get a `D_name(dst, ..)` function
  that stores its result through `dst`: it allocates the cell with a hole, stores it, points `dst`
  at the hole and jumps to the next call. That jump is `goto top` for the def itself, and a call
  marked `musttail` for another def of the group (the group's `D_` functions share one signature).
  `sort` builds its lists in a loop instead of a million-deep recursion.
- **Checking.** Declarations are checked in parallel on the CPU threads, against the book as it stands
  before each; the allocator hands out partly free blocks by their bitmaps; `Map.bit` is native.

**Memory.** Bend values are affine: a value has one owner unless it went through a variable used
more than once. So, as in the official runtime (which counts references), a `match` that opens a
node frees it, and `sort` stays near one list's size: 30 MB where the collector alone needed 481 MB.

- A value bound to a variable that some path uses twice is marked shared where it is bound
  (`bend_share`): a bit in the node's tag word. Cached string literals are shared too.
- A match reads the node's fields, then hands it to `bend_take`: a shared node stays and marks its
  fields shared (once: a second bit says it did); any other is dead, and its slot goes back to its
  block's allocation bitmap.
- A block where a fifth of the slots are free again is a reuse candidate. A thread's next
  allocations of that size take its free slots in address order, blocks in address order, so a list
  built from reused slots stays in order in memory, which keeps list walks fast.
- The tracing collector still runs; freed slots only make it rarer.

A compiler's heap is mostly shared, short-lived data, where freeing costs more than it saves:
bendc builds itself with `BEND_NO_FREE=1`, which compiles matches without it (as do `make
selfcheck`, `tools/reseed.sh` and `bootstrap.sh`). `-DBEND_DEBUG_FREE` builds a program whose
freed nodes are poisoned and kept, so a use after free stops with the C line that freed it.

On the GPU, most of the memory is Metal's: making the device alone costs about 6 MB. The rest is
kept down three ways:

- Metal is linked with the program (weakly, through a `.linker_option` in `rt/gpuhost.h`), which
  the loader maps for about 3 MB less than opening it at the first `!`-call.
- The first run keeps Metal's binary archive of the kernels in `~/Library/Caches/bend`, named by a
  hash of the device code; later runs load the library and the pipelines from it, for 1 MB where
  compiling costs 2.5 (an archive for another GPU or OS misses, and the kernels compile again).
  The first run, which compiles, peaks near 16 MB.
- Pages the GPU writes and the CPU never reads are not counted: the host reads the lanes' `pc`s after
  each dispatch, so a lane's state is stored word by word across all lanes (the `pc`s take 64 KB,
  not the 1.5 MB of every lane's state), and the queue, whose slots keep their sequence numbers
  less their index, starts empty on fresh zero pages.

Filling a hole writes into a cell after it was made, which the collector otherwise never sees: a
minor collection skips the fields of old cells. A hole holds `BEND_HOLE` until it is filled (and a
D_ node's tag word holds it from before its slot is allocated until its fields are stored), so a
collection records the objects a thread's stack or registers point to that hold `BEND_HOLE`, and
the next minor collection rescans them.

## Writing a compiler under Bend's rules

Bend 2 is a proof language, and its checker is strict about code that runs. It shaped this compiler:

- **Define before use, no mutual recursion.** A parser is mutually recursive by nature. Bend allows
  forward declaration through a `law` (a typed claim) that a later `def` fills, but a def that calls
  a law before it is filled must be `@unsafe`. So each cycle of defs is one def instead: an extra
  argument, a selector, says which of the old defs runs, and its constructors carry that def's
  arguments. The return type is a type-level function of the selector (`P.go(fuel, k: PsSel) ->
  Parser(PsSel.ty(k))`), and the old names stay as one-line wrappers.
- **`match` only on parameters.** A match cannot inspect a computed value, and neither can
  destructuring. So each decision is a small helper def whose parameter is the thing being matched.
  The parser monad avoids most of the tuple-destructuring helpers a hand-threaded token list would
  need. After a match, the parameters and fields before the matched one cannot be matched: a proof
  that needs the fuel's shape deep in a case (as `REDPROOF.bend`'s redex does) takes it from a
  separate lemma.
- **Affine variables.** A variable is used at most once unless it is marked `+`, which requires a
  copyable `Data` type. Every AST type is `Data`, and `+` appears where values are reused.
- **Totality.** A recursive call must shrink its first changing argument. Walks over a node and a
  list of nodes recurse on the list's head, then on the node rebuilt with the list's tail (the same
  constructor with a smaller field counts as smaller). Recursion that shrinks nothing (a parser's
  over tokens, a selector-merged cycle, the checker's evaluation of normalized terms) counts down a
  `Nat` fuel argument that starts at `Fuel.max()`, about 4 billion, and fails loudly if it ever
  runs out. A branch on a computed value that recurses is `Bool.pick(T, c, u => a, u => b)(x)`:
  the termination check sees the self-call under the lambda, and bendc compiles it as a match, with
  no closures. Neither `bendc.bend` nor `check.bend` has an `@unsafe` def: the checker's parser
  normalizes each def's value and prints terms in its errors, so the evaluator and the printer
  (`higher`, `term_lower`, `term_show` and what they use) come before the parser's declarations
  (`tools/unsafe_min.py` keeps the markers minimal: it strips them all and puts back one for each
  def the checker rejects).

The compiler compiles every one of these patterns in its own source. It handles its own laws, its
own dependent selectors, and its own user-defined monads (`Parser`, `Gen`), which is what makes the
fixpoint meaningful.

## Testing

`tests/` holds programs covering the features above: closures, trees, maps, sorting, strings and
UTF-8, file IO, concurrent fork/join, TCP, user-defined C effects, modules, string patterns, arrays,
proofs, value printing, exit codes, deep recursion, parallel lets, the collector, destination-passing,
and the `Nat` bound.
Each `.out` file is the stdout and exit code of the **official** `bend` running the same program.
`run_tests.sh` compiles each program with a given `bendc`, runs it, and diffs the result; programs
with `!`-calls run again on the GPU simulator and, on a Mac, on Metal, and must not fall back to the
CPU. On arm64 (macOS or Linux) every program runs again through `bendc --native`. A
`tests/NAME.env` file sets environment variables for a run (`dps` collects every megabyte, so
collections happen while holes are open);
`tests/hub/run.sh` serves a package from a local hub and imports it by hash.
`tests/check/` holds programs the checker rejects; each `.out` is the official
`bend --check-only` report and exit code, with the repository's path spelled `<repo>` (a missing
import is named by its absolute path).

```sh
make test                      # with build/bendc
./run_tests.sh build/stage1    # with any stage
```

The official repository's own tests are a second, larger suite. `tools/upstream.py` runs every one
that imports Base, has a `main` and expects output (not an error) through a given `bendc`, and
compares the result with the test's `#|` lines as the official gate does. The failures go to
`build/upstream/fails.txt`. Against Bend 2.0.32, all 799 pass in C and 818 of 820 in JavaScript;
the rest are the limitations below. With `--check`, the tests whose check fails
(`#|SOME PROOFS FAIL`) run through `bendc --check-only` instead, which must print the same error
report: all 493 do.

```sh
git clone --depth 1 -b v2.0.32 https://github.com/bendlang/bend /tmp/bendup
python3 tools/upstream.py build/bendc /tmp/bendup           # C
python3 tools/upstream.py build/bendc /tmp/bendup --js io_  # JavaScript, tests whose name has io_
python3 tools/upstream.py build/bendc /tmp/bendup --check   # the checker's error reports
```

## Limitations

- The native backend (`--native`) is AArch64 only, does not free on match, runs parallel lets in
  order, and has no destination passing (see [The native backend](#the-native-backend)).
- The GPU backend targets Metal only; elsewhere `f!(x)` runs on the CPU threads (or on the
  simulator, with `BEND_GPU=sim`).
- No windowing effects (Base's `Window`).
- On JavaScript, a TCP send to a peer that does not read blocks the event loop, and a `select` a
  signal interrupts is not restarted (`io_tcp_send_slow_peer`, `io_select_eintr`).
- A main whose type is `Type` or a type family is printed by normalizing it at compile time, as the
  official interpreter does. A field whose type is a type-level match on a runtime value prints as
  the one inhabited type its arms can give (`LE(r, 1n)` is `Unit` when its other arm is `Empty`),
  and as `?` when there are several.
- Blocks still follow indentation, with the official parser's readings for the layouts it takes
  without reading layout: a `do` statement shallower than its head, and a `case` arm deeper than
  the arm before it.

## Repository layout

| Path | |
|---|---|
| [`check.bend`](check.bend) | the type checker, a port of the official one: parser, normalizer, conversion, quantities, termination, templates, error reports |
| [`asm.bend`](asm.bend) | the native backend's AArch64 assembler, peephole pass, and Mach-O and ELF object writers |
| [`rt/native.c`](rt/native.c) | external names for the runtime's inline natives, which native code calls |
| [`bendc.bend`](bendc.bend) | the compiler, organized by section: lexer, layout, parser monad, expressions, patterns, statements, declarations, operator resolution, free variables, global tables, code generation, value printers, modules, driver |
| [`core.bend`](core.bend) | the core IR between the front end and code generation: terms with relevance-marked arguments, erasure, and a semantics |
| [`LAWS.bend`](LAWS.bend), [`PROOF.bend`](PROOF.bend) | the law that erasure preserves the core IR's semantics, and its proof (induction on the fuel, one case per step) |
| [`RED.bend`](RED.bend), [`REDPROOF.bend`](REDPROOF.bend) | the law that reducing applied lambdas to lets (`Core.Def.red`) preserves the core IR's semantics, and its proof |
| [`KNOWN.bend`](KNOWN.bend), [`KNOWNPROOF.bend`](KNOWNPROOF.bend) | the law that resolving matches on known constructors (`Core.Def.known`) preserves the core IR's semantics, and its proof |
| [`rt/bendrt.h`](rt/bendrt.h) | C runtime: garbage collector, closures, strings, arrays, native `Nat`, `U32`/`F32`, fork-join pool, event loop and effect ABI, entry points |
| [`rt/gpu.h`](rt/gpu.h), [`rt/gpuhost.h`](rt/gpuhost.h) | the GPU kernel's runtime (one text for Metal and C) and its host: arena, Metal through the Objective-C runtime, the kernel cache, the simulator, copying results back |
| [`rt/hub.c`](rt/hub.c) | bendc's own effect for fetching hub packages (curl and SHA-256) |
| [`rt/chan.c`](rt/chan.c) | the channel effects, spliced for Base's `effs/chan.c` (whose own channel rows the collector would not see) |
| [`seed/bendc.c`](seed/bendc.c) | the fixpoint C output of `bendc.bend`, for building without Bend |
| [`bench/`](bench) | benchmark programs and `run.sh`, which times them against the official `bend` |
| [`tests/`](tests) | test programs and the official `bend`'s output for each |
| [`bootstrap.sh`](bootstrap.sh), [`run_tests.sh`](run_tests.sh), [`Makefile`](Makefile) | bootstrap and fixpoint check, test runner, build entry points |
| [`tools/ddc.sh`](tools/ddc.sh) | diverse double-compiling: the seed, reproduced by two toolchains that share no C compiler, and by bendc's native build |
| [`tools/tcc.sh`](tools/tcc.sh) | the seed built by tcc reproduces itself, and the tests pass with tcc |
| [`tools/unsafe_min.py`](tools/unsafe_min.py) | dev tool: drops the `@unsafe` markers the checker does not need |
| [`tools/order.py`](tools/order.py) | dev tool: section-aware dependency sort, with automatic `law` forward declarations for cycles |
| [`tools/upstream.py`](tools/upstream.py) | dev tool: runs the official repository's tests through a `bendc` (see [Testing](#testing)) |
| [`tools/embed.py`](tools/embed.py) | dev tool: embeds `rt/bendrt.js`, `rt/chan.c` and `rt/gpu.h` (`rt/rtjs.bend`, `rt/rtchan.bend`, `rt/gpu_src.h`) |

## License

[MIT](LICENSE)
