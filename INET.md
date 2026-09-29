# Interaction nets and bendc

This note covers two questions: whether bendc should run programs as interaction nets, and what
the net model can add to the C backend. It records the measurements behind each decision. The
machine was an Apple M4 Pro with 12 cores, shared with other jobs. The load average is given with
each measurement.

## No net engine

The first plan was a `bendc --inet` backend: compile the Core IR to an interaction net and reduce
it with a parallel runtime, as HVM2 does, or as HVM4 does for the Interaction Calculus. HVM4 is a
single-threaded Interaction Calculus runtime (docs/hvm and docs/theory in its repository). It
evaluates terms with affine variables and explicit duplication (DUP) and superposition (SUP)
nodes, and it gets optimal sharing from them. Nothing here uses its code.

That plan is dropped because of speed. `fib(38)` takes 20.5s on HVM4 and 0.19s as C from bendc,
about 100 times slower. A net runtime rewrites a graph in memory: every beta step and every
duplication allocates and links nodes. The C backend compiles a call to a C call, keeps
arguments in registers, and unboxes numbers. No amount of parallelism wins back a factor of
100 on 12 cores. The requirement is that bendc is never slower than its own C backend, so the
compiled C stays the execution engine.

## What the net model gives: independence

The net model does give one thing: a reason why parallelism is safe. In an interaction net, two
redexes that share no wire reduce in either order, or at once. In Bend the same holds at the level
of source terms. Bend is pure, and its linear variables (`+x`) are used exactly once. So the
operands of one node, and the calls of a block that no let of it feeds, share nothing that one of
them could change. A shared value is immutable. In reference-counting mode, a value may be
updated in place only when it has one reference. A value that goes to another thread is marked
shared first (`rc_publish`). So these operands and calls can run at once, whatever they are. No
annotation and no alias analysis is needed.

bendc uses this in `Par.auto` (see README, How it works). It groups independent calls into
parallel lets:

- an operator's or a call's operands, or a constructor's fields, where two or more of them
  recurse;
- the calls of a block that no let of the block feeds, where two or more are heavy.

A heavy call recurses or forks. A match's scrutinees count as calls of its block, so
`match warp(a) warp(b)` (tree-bitonic, after `warp_zip` is inlined) forks too.

The parallel lets of the six tree benchmarks were rewritten as sequential lets
(`bench/unpar.py`). With the pass, bendc then forks at the places below.

| program | forks, lets removed | forks, as written |
|---|---|---|
| tree-bitonic | 4 | 4 |
| tree-matmul | 29 | 29 |
| tree-radix | 5 | 5 |
| merkle | 6 | 5 |
| queens | 1 | 1 |
| symreg | 10 | 10 |

A fork is a `par_fork` in the C. merkle forks at one more place with the lets removed. The pass
finds the program's own `pgen` fork and also the `htree` under it.

## The scheduler

A parallel let's values run on a work-stealing pool (`par_fork` and `par_join` in
`rt/bendrt.h`). Each value but the last is a closure pushed on the thread's Chase-Lev deque. A
fork nobody took runs inline at its join. When the deque already holds 4 tasks, the fork is only
a tagged closure, which the join applies. A thief that finds nothing sets `want` on a victim,
which then releases its oldest held task. Below a fork depth of log2(threads) + 6, a parallel
let runs its values in order, through the def's sequential clone (`S_name`). On one thread the
code takes the same path, and does what the C backend does.

The clone is the reason one thread costs nothing. It is also a static cutoff: a subtree past the
frontier cannot be split again, even when other threads are idle. The obvious fix is dynamic
granularity: forks cheap enough that every parallel let can offer work, and work handed over
only when a thread asks for it.

### An experiment: latent tasks on private deques

Commit 59c6bc3 on this branch tried this, and 5563078 reverts it. The design is lazy task
creation with private deques (Acar, Chargueraud and Rainey, PPoPP 2013):

- A parallel let's values but the last become descriptors on the C stack: the lifted code, its
  captured values, and a state.
- Each descriptor is pushed on a stack that only its own thread touches. A push is two stores
  and a load, with no atomics and no heap closure.
- A thread with nothing to do writes its id into a busy thread's `want`. The busy thread answers
  at its next push or join with its oldest latent task.
- A join whose task nobody took is a plain call. A join whose task was taken waits and answers
  other asks meanwhile.
- One variant pushed at every parallel let. A second variant (`par_go`/`par_end`) stopped
  pushing past a depth frontier, and reset the depth for each stolen task.

**One thread.** The one-thread path does the same work as before. At first, tree-matmul ran 4.4%
more instructions (61.9G before, 64.7G after) with the same one-thread code. The cause was
clang's default `-fstack-protector-strong`, which guards every function that takes the address
of a local. The stack descriptors did that in every function with a parallel let. The experiment
turned the protector off in generated code (`BEND_CODE_BEGIN` and `BEND_CODE_END`, a
`clang attribute` pragma). With that, one thread ran the same instructions or fewer. These are
the small inputs of `build/mksmall.sh`, with instructions retired from `/usr/bin/time -l`:

| program | before | latent tasks |
|---|---|---|
| tree-bitonic | 57.83G | 57.75G |
| tree-matmul | 61.75G | 60.96G |
| tree-radix | 4.44G | 4.42G |
| merkle | 11.58G | 11.59G |
| queens | 0.43G | 0.43G |
| symreg | 7.11G | 7.01G |

**Pushing at every let is too dear.** The next figures come from the same small inputs on one
thread, with every parallel let pushing a latent task and none taken:

| program | before | a latent task at every let |
|---|---|---|
| tree-matmul | 61.9G | 76.4G (+23%) |
| tree-radix | 4.47G | 5.70G (+27%) |
| symreg | 7.14G | 15.77G (+121%) |

The push itself is cheap. The cost is the rest: the value runs through the lifted lambda, an
indirect call with its captures in an array, instead of the sequential clone, where clang
inlines and unboxes. symreg's `eval` is about 31 instructions a call, so it doubles.

**Many threads.** Best of 3 runs, interleaved, small inputs, load 31 to 46. `old` is the
Chase-Lev scheduler, `lz` pushes at every let, and `hy` uses the depth frontier with the reset.

| program | binary | 1 thr | 4 thr | 8 thr | 12 thr |
|---|---|---|---|---|---|
| tree-bitonic | old | 4.62s | 2.02s | 1.74s | 1.63s |
| | lz | 4.62s | 2.06s | 2.00s | 2.13s |
| | hy | 4.73s | 2.23s | 1.94s | 2.63s |
| tree-matmul | old | 3.83s | 1.65s | 1.10s | 0.86s |
| | lz | 4.10s | 1.63s | 1.22s | 0.95s |
| | hy | 4.39s | 1.55s | 1.04s | 1.01s |
| tree-radix | old | 0.55s | 0.27s | 0.22s | 0.18s |
| | lz | 0.55s | 0.30s | 0.26s | 0.26s |
| | hy | 0.58s | 0.28s | 0.24s | 0.29s |
| merkle | old | 1.00s | 0.38s | 0.23s | 0.18s |
| | lz | 0.81s | 0.48s | 0.26s | 0.24s |
| | hy | 1.50s | 0.45s | 0.37s | 0.32s |
| queens | old | 0.030s | 0.019s | 0.013s | 0.013s |
| | lz | 0.034s | 0.013s | 0.013s | 0.012s |
| | hy | 0.030s | 0.017s | 0.014s | 0.014s |
| symreg | old | 0.84s | 0.23s | 0.14s | 0.12s |
| | lz | 0.77s | 0.34s | 0.18s | 0.17s |
| | hy | 0.75s | 0.20s | 0.14s | 0.17s |

The one-thread column of `old`, `lz` and `hy` runs the same instructions. Its spread (merkle
0.81s to 1.50s) is the machine's noise. At 8 and 12 threads the Chase-Lev scheduler is as fast or
faster everywhere except queens, which is within noise. A second run, with only `old` and `lz`,
gave the same order.

There are two reasons:

1. **Nothing to gain at the forks.** With the frontier, a program forks about 2^9 times per
   stolen task. A heap closure per fork costs nothing measurable at that rate. At 8 threads the
   Chase-Lev build retires fewer instructions in total than on one thread (tree-bitonic 52.1G
   against 57.9G, tree-radix 4.28G against 4.45G). No scheduling overhead is left to remove.
2. **Private deques need the victim to run.** A thief waits for the victim to answer at a push
   or a join. On a machine with more runnable threads than cores, as here, the victim is often
   descheduled. The thief then gets nothing, and neither does a joiner whose task went to a
   descheduled thief. A Chase-Lev thief takes the task without the victim's help.

So the Chase-Lev scheduler stays. Its `want` flag and inline forks already make task creation
lazy. The latent-task code is on the branch for reference.

## Sharing under lambdas

The one thing a net runtime does that compiled C cannot is optimal sharing: a DUP of a lambda
shares the work inside its body across copies. In C, each copy recomputes that work. Programs
that depend on this are λ-encodings and some Church-numeral computations, where it can save
exponentially. None of the official benchmarks is such a program. bendc has no net-style
reduction, because no benchmark shows a gain from it, and it costs about 100 times per step
(fib above).

## Measurements at full size

The unannotated programs (`bench/unpar.py`) at the official sizes. Each figure is the best of 2
interleaved runs, at 1, 4, 8 and 12 threads:

- bendc: bendc on the unannotated program, so all its parallelism is found by `Par.auto`;
- bendc as written: bendc on the program with its own parallel lets;
- official: the official build of the program as written;
- official unannotated: the official build of the unannotated program.

FULLTABLE

## Reproducing

- `bench/unpar.py in.bend out.bend` removes a program's parallel lets.
- `bench/scale.py -r R -t 1,4,8 name=binary ...` runs binaries at several thread counts,
  interleaved, and prints the best wall time and the speedup. The binaries must print the same
  last line.
