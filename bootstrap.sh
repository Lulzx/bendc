#!/bin/sh
# Bootstraps bendc and checks that it reaches a fixpoint:
#   stage0: bendc.bend built by the official `bend`
#   stage1: bendc.bend compiled by stage0 (C, then clang)
#   stage2: bendc.bend compiled by stage1
# stage1.c and stage2.c must be byte-identical.
set -e
cd "$(dirname "$0")"
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
mkdir -p build
echo "[stage0] bend bendc.bend -o build/bendc0"
if ! out=$(bend bendc.bend -o build/bendc0 2>&1); then echo "$out"; exit 1; fi
echo "$out" | head -1
echo "[stage1] bendc0 -> build/stage1.c"
./build/bendc0 "$BASE" bendc.bend > build/stage1.c
${CC:-clang} -O2 -w -I rt build/stage1.c -o build/stage1 -lm -lpthread
echo "[stage2] stage1 -> build/stage2.c"
./build/stage1 "$BASE" bendc.bend > build/stage2.c
${CC:-clang} -O2 -w -I rt build/stage2.c -o build/stage2 -lm -lpthread
if cmp -s build/stage1.c build/stage2.c; then
  echo "fixpoint: stage1.c == stage2.c ($(wc -l < build/stage1.c) lines)"
else
  echo "NO FIXPOINT: stage1.c and stage2.c differ"; exit 1
fi
for b in bendc0 stage1 stage2; do
  printf "tests with %-7s " "$b:"; ./run_tests.sh build/$b | tail -1
done
