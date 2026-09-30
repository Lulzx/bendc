#!/bin/sh
# Official tree benchmark answers under threaded, one-megabyte GC steps.
set -eu
cd "$(dirname "$0")/.."
N=${1:-5}
case "$N" in ''|*[!0-9]*|0) echo "usage: $0 [positive run count]" >&2; exit 2;; esac
BASE=${BEND_BASE:-$PWD/build/base32/base.bend}
UP=${BEND_UP:-/tmp/bendup32}
for name in tree-bitonic tree-matmul tree-radix; do
  dir=build/treestress/$name
  mkdir -p "$dir"
  cp "$UP/bench/runtime/$name/main.bend" "$dir/main.bend"
  ./build/bendc -o "$dir/bin" "$BASE" "$dir/main.bend"
  case "$name" in
    tree-bitonic) ref=3787129428;;
    tree-matmul) ref=3797651056;;
    tree-radix) ref=1998173798;;
  esac
  printf '%s\n' "$ref" > "$dir/expected"
  "$dir/bin" --gpu off --threads 8 > "$dir/default.out" 2> "$dir/default.err"
  cmp "$dir/expected" "$dir/default.out"
  i=0
  while [ "$i" -lt "$N" ]; do
    BEND_GC_MIN_MB=1 "$dir/bin" --gpu off --threads 8 > "$dir/stress.out" 2> "$dir/stress.err"
    if ! cmp -s "$dir/expected" "$dir/stress.out"; then
      echo "FAIL $name (run $i)" >&2
      diff "$dir/expected" "$dir/stress.out" || :
      exit 1
    fi
    i=$((i + 1))
  done
  echo "ok   $name x$N (answer $ref)"
done
