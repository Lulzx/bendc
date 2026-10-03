#!/bin/sh
# Guarded packed zipper shape, ordinary Nat exclusions, and prefix invariants.
# BEND_ZIPPER_SAN=1 enables ASAN/UBSAN; portable default is an ordinary C unit.
set -eu
BENDC=${1:-build/bendc}
BASE=${2:-build/base34/base.bend}
SRC=${3:-tests}
OUT=${4:-build/probe/gpu-zipper-check}
RT=${5:-rt}
mkdir -p "$OUT"
for name in mixed_wide scalar_types scalar_export wide_nat low_nat; do
  "$BENDC" "$BASE" "$SRC/gpu_zipper_$name.bend" > "$OUT/$name.c"
done
cp "$OUT/mixed_wide.c" "$OUT/zipper-positive.c"
# Mixed32 schema specializes; both mixed scalar export and computation use it.
for name in scalar_types scalar_export; do
  grep -Fq 'KZ_merge_try(' "$OUT/$name.c"
  grep -Fq '#define K_GPU_PACKED 1' "$OUT/$name.c"
done
# The ordinary Nat schema stays unpacked even beside a specialized U32 schema.
grep -Fq 'KZ_combine_try(' "$OUT/mixed_wide.c"
if grep -Fq 'KZ_wcombine_' "$OUT/mixed_wide.c"; then
  echo 'Nat zipper was specialized in mixed program' >&2; exit 1
fi
for name in wide_nat low_nat; do
  if grep -Eq 'KZ_combine_|#define K_GPU_PACKED' "$OUT/$name.c"; then
    echo "Nat zipper unexpectedly packed: $name" >&2; exit 1
  fi
done
cp "$SRC/lib/gpu_zipper_unit.c" "$OUT/unit.c"
flags='-O2 -w'
if [ "${BEND_ZIPPER_SAN:-0}" = 1 ]; then flags='-O1 -g -w -fsanitize=address,undefined'; fi
ldl=; [ "$(uname)" != Linux ] || ldl=-ldl
${CC:-clang} $flags -pthread -I "$RT" "$OUT/unit.c" -o "$OUT/unit" -lm $ldl
"$OUT/unit"
echo 'ok: mixed32 zipper; Nat exclusions; depth0..4, mixed/DAG, overflow, input preservation, physical ledger and compaction'
