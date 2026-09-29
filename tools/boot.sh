#!/bin/sh
# The bootstrap from source: a C compiler builds boot/bendi, a Bend
# interpreter written by hand in C99, and bendi runs bendc.bend on its own
# source. The C that run writes must be seed/bendc.c byte for byte, so the
# seed is what bendc.bend means, not only what an earlier bendc made of it.
# (The seed then reproduces itself: make selfcheck.)
#
# bendi reads Bend source and runs it: no seed, no official Bend, no
# generated code. It trusts the C compiler that builds it and base.bend.
#
# Usage: tools/boot.sh [cc]   (default: $CC, else cc; tcc 0.9.28 works)
set -e
cd "$(dirname "$0")/.."
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
case $BASE in /*) ;; *) BASE=$PWD/$BASE ;; esac
BOOTCC=${1:-${CC:-cc}}
mkdir -p build/boot
echo "boot: bendi ($(cat boot/*.c boot/*.h | wc -l | tr -d ' ') lines of C), built by $BOOTCC"
"$BOOTCC" -O2 -o build/boot/bendi boot/*.c -lm -lpthread
start=$(date +%s)
BEND_NO_FREE=1 ./build/boot/bendi --base "$BASE" bendc.bend --no-check "$BASE" bendc.bend > build/boot/stage.c
end=$(date +%s)
cmp build/boot/stage.c seed/bendc.c
echo "boot: bendi ran bendc.bend on itself in $((end - start))s; the output is the seed byte for byte"
