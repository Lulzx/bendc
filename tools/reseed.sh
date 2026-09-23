#!/bin/sh
# Regenerates seed/bendc.c: compiles bendc.bend with build/bendc, then with
# each new compiler, until one compiles itself to the same C (a compiler
# change that changes its own output takes one more stage).
set -e
cd "$(dirname "$0")/.."
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
CC=${CC:-clang}
prev=build/bendc
for i in 1 2 3 4; do
  "$prev" --no-check "$BASE" bendc.bend > build/reseed$i.c
  $CC -O2 -w -I rt build/reseed$i.c -o build/reseed$i -lm -lpthread
  if [ $i -gt 1 ] && cmp -s build/reseed$i.c build/reseed$((i - 1)).c; then
    cp build/reseed$i.c seed/bendc.c
    echo "seed/bendc.c updated (fixpoint at stage $i)"
    exit 0
  fi
  prev=build/reseed$i
done
echo "no fixpoint after 4 stages"; exit 1
