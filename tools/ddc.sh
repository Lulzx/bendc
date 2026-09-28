#!/bin/sh
# Diverse double-compiling (David A. Wheeler, 2009): shows that
# seed/bendc.c is what bendc.bend says it is, not a self-reproducing
# compiler that hides something, unless two independent toolchains collude.
#
#   A (trusted): the official Bend (TypeScript) translates boot.bend to C,
#                GCC builds it, and that stage0 compiles bendc.bend.
#   B (seed):    GCC builds seed/bendc.c, which compiles bendc.bend.
#   C (native):  on arm64, B's compiler builds bendc natively, and
#                that compiles bendc.bend.
#
# All outputs must be seed/bendc.c byte for byte. Path A shares no code
# with the seed: not bendc's C, and not clang, which builds everything else
# here (bootstrap.sh's stage0 is built by the official `bend -o`, which
# calls clang). So GCC must really be GCC: macOS's /usr/bin/gcc is clang.
# The official C needs musttail, so GCC 15 or newer.
#
# Usage: tools/ddc.sh [gcc]   (default: the newest gcc-NN on PATH, else gcc)
set -e
cd "$(dirname "$0")/.."
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
newest=$(for d in $(echo "$PATH" | tr ':' ' '); do ls "$d" 2>/dev/null || true; done |
  grep -E '^gcc-[0-9]+$' | sort -t- -k2 -n | tail -1)
GCC=${1:-${newest:-gcc}}
if ! "$GCC" --version 2>/dev/null | head -1 | grep -q "GCC\|gcc"; then
  echo "ddc: $GCC is not GCC ($("$GCC" --version 2>&1 | head -1))"; exit 1
fi
if "$GCC" --version | grep -qi clang; then
  echo "ddc: $GCC is clang, which path A must not share"; exit 1
fi
echo "ddc: $("$GCC" --version | head -1)"
mkdir -p build/ddc

echo "[A] official bend: boot.bend -> build/ddc/stage0.c"
BEND_NO_TELEMETRY=1 bend boot.bend -o build/ddc/stage0.c
"$GCC" -O2 -w build/ddc/stage0.c -o build/ddc/stage0 -lm -lpthread
echo "[A] stage0 (GCC): bendc.bend -> build/ddc/a.c"
BEND_NO_FREE=1 ./build/ddc/stage0 --no-check "$BASE" bendc.bend > build/ddc/a.c

echo "[B] seed/bendc.c (GCC): bendc.bend -> build/ddc/b.c"
"$GCC" -O2 -w -I rt seed/bendc.c -o build/ddc/seed -lm -lpthread
BEND_NO_FREE=1 ./build/ddc/seed --no-check "$BASE" bendc.bend > build/ddc/b.c

# C (on arm64): the seed built in B compiles bendc.bend to machine code with
# its own backend (bendc --native: its assembler and object writer; GCC
# builds only the runtime and the effects' C, and links), and
# that bendc compiles bendc.bend. bendc's own code in it went through no C
# compiler.
legs="a b"
case $(uname -m) in arm64|aarch64) native=1;; *) native=0;; esac
if [ $native = 1 ]; then
  echo "[C] seed (GCC) --native: bendc.bend -> build/ddc/native"
  BENDC_RT=$PWD/rt CC=$GCC ./build/ddc/seed --native -o build/ddc/native "$BASE" bendc.bend > /dev/null
  echo "[C] native bendc: bendc.bend -> build/ddc/c.c"
  BEND_NO_FREE=1 ./build/ddc/native --no-check "$BASE" bendc.bend > build/ddc/c.c
  legs="a b c"
fi

ok=1
for p in $legs; do
  if cmp -s build/ddc/$p.c seed/bendc.c; then
    echo "ddc: build/ddc/$p.c == seed/bendc.c"
  else
    echo "ddc: build/ddc/$p.c differs from seed/bendc.c"; ok=0
  fi
done
[ $ok = 1 ] && echo "ddc: the seed is bendc.bend, by two independent toolchains and bendc's own machine code ($(wc -l < seed/bendc.c | tr -d " ") lines)"
[ $ok = 1 ]
