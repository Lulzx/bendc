#!/bin/sh
# Benchmarks bendc against the official bend on this machine: each program is
# built by both, their outputs must agree, and the best of 3 runs is shown.
# Usage: bench/run.sh [bendc-binary]   (default: build/bendc)
set -e
cd "$(dirname "$0")/.."
BENDC=${1:-build/bendc}
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
export BEND_NO_TELEMETRY=1
mkdir -p build/bench
best() {  # best wall time of 3 runs of "$@", in seconds
  python3 - "$@" <<'PY'
import subprocess, sys, time
ts = []
for _ in range(3):
    t = time.perf_counter()
    subprocess.run(sys.argv[1:], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=True)
    ts.append(time.perf_counter() - t)
print("%.2f" % min(ts))
PY
}
echo "| program | bendc | official bend |"
echo "|---|---|---|"
for spec in forks:28 forks_gpu:28 leaves:14 leaves_gpu:14 sort:1000000; do
  name=${spec%%:*} n=${spec#*:}
  src=bench/$name.bend out=build/bench/$name
  "$BENDC" "$BASE" "$src" > "$out.c" 2> /dev/null
  ${CC:-clang} -O2 -w -I rt "$out.c" -o "$out" -lm -lpthread
  bend "$src" -o "$out.off" > /dev/null 2>&1
  a=$("./$out" -- "$n"); b=$("./$out.off" "$n")
  [ "$a" = "$b" ] || { echo "$name: outputs differ: $a vs $b"; exit 1; }
  echo "| \`$name $n\` | $(best "./$out" -- "$n")s | $(best "./$out.off" "$n")s |"
done
echo
echo "| task | bendc | official bend |"
echo "|---|---|---|"
# The official bend caches checks in ~/.bend/check.json: time it without.
fresh=$(mktemp -d)
echo "| type-check bendc.bend | $(best "$BENDC" --check-only "$BASE" bendc.bend)s | $(HOME=$fresh best bend bendc.bend --check-only)s |"
rm -rf "$fresh"
