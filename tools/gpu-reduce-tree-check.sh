#!/bin/sh
set -eu
compiler=${1:-./build/bendc}
base=${2:-./build/base34/base.bend}
srcdir=${3:-./tests}
outdir=${4:-./build/gpu-reduce-tree-unit}
rtdir=${5:-./rt}
mkdir -p "$outdir"
"$compiler" "$base" "$srcdir/gpu_reduce_tree_small.bend" > "$outdir/reduce-positive.c"
"$compiler" "$base" "$srcdir/gpu_reduce_tree_exclusions.bend" > "$outdir/reduce-exclusions.c"
rg -q 'KR_fold_try' "$outdir/reduce-positive.c"
rg -q 'KR_count_try' "$outdir/reduce-positive.c"
if rg -q 'KR_(alter|duplicate)_try' "$outdir/reduce-positive.c"; then
  echo 'Changing scalar arguments or duplicate child recursion incorrectly selected' >&2
  exit 1
fi
if rg -q 'KR_(wsum|foldfp)_try' "$outdir/reduce-exclusions.c"; then
  echo 'Nat fields or F32 forwarding incorrectly selected' >&2
  exit 1
fi
"$compiler" "$base" "$srcdir/gpu_reduce_tree_array_caller.bend" > "$outdir/reduce-array-caller.c"
# A caller with array effects must retain its original embedded generic fold body.
python3 - "$outdir/reduce-array-caller.c" <<'PYCODE'
import re, sys
s = open(sys.argv[1]).read().split('static const char K_SRC[]')[0]
guards = re.findall(r'\{bool hit;KW r=KR_fold_try\(c,x[^\n]+\n([^\n]+)', s)
assert guards and all(line.startswith('KAUTO ') for line in guards), guards
PYCODE
flags='-O2'
if [ "${BEND_REDUCE_SAN:-0}" = 1 ]; then
  flags='-O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer'
fi
${CC:-cc} $flags -w -pthread -I "$outdir" -I "$rtdir" "$srcdir/lib/gpu_reduce_tree_unit.c" -o "$outdir/unit" -lm
"$outdir/unit"
printf 'Pure scalar reduction codegen exclusions and readonly depth/DAG/fallback oracle passed\n'
