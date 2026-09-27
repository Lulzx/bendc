#!/bin/sh
# bendc under the Tiny C Compiler, the compiler bootstrappable builds reach
# first (from hex0 through M2-Planet and Mes): tcc builds seed/bendc.c,
# that bendc compiles bendc.bend to the seed byte for byte, and the test
# suite passes with tcc building the programs and the runtime.
#
# Needs tinycc 0.9.28 (mob: stdatomic.h; 0.9.27 has none). Under tcc the
# runtime keeps per-thread state in a pthread key (no TLS on every target),
# calls the constructors itself (tcc ignores constructor attributes) and
# has no Metal (the GPU simulator and the CPU remain).
#
# Usage: tools/tcc.sh [tcc]   (default: tcc on PATH)
set -e
cd "$(dirname "$0")/.."
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
case $BASE in /*) ;; *) BASE=$PWD/$BASE ;; esac
TCC=${1:-tcc}
echo "tcc: $("$TCC" -v)"
mkdir -p build/tcc
"$TCC" -O2 -w -I rt seed/bendc.c -o build/tcc/bendc -lm -lpthread
BEND_NO_FREE=1 ./build/tcc/bendc --no-check "$BASE" bendc.bend > build/tcc/self.c
cmp build/tcc/self.c seed/bendc.c
echo "tcc: the tcc-built bendc compiles bendc.bend to the seed"
# The runtime object, built by tcc (run_tests.sh reuses a newer one).
rm -f build/bendrt.o
CC=$TCC BEND_BASE=$BASE ./run_tests.sh build/tcc/bendc > build/tcc/tests.txt 2>&1 || true
rm -f build/bendrt.o
grep -v "^ok" build/tcc/tests.txt
tail -1 build/tcc/tests.txt | grep -q " 0 failed"
