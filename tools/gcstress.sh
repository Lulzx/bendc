#!/bin/sh
# Tracing builds of the threaded tests, with a one-megabyte GC step.
set -eu
cd "$(dirname "$0")/.."
N=${1:-150}
case "$N" in ''|*[!0-9]*|0) echo "usage: $0 [positive run count]" >&2; exit 2;; esac
for name in par fork chan stress dps gc par_reuse rcstress; do
  bin=build/tests/$name
  [ -x "$bin" ] || { echo "missing $bin (run ./run_tests.sh first)" >&2; exit 1; }
  i=0
  while [ "$i" -lt "$N" ]; do
    status=0
    env $(cat "tests/$name.env" 2>/dev/null || :) BEND_GC_MIN_MB=1 "$bin" > "build/tests/$name.stress" 2>&1 || status=$?
    echo "exit $status" >> "build/tests/$name.stress"
    if ! cmp -s "build/tests/$name.stress" "tests/$name.out"; then
      echo "FAIL $name (run $i)" >&2
      diff "tests/$name.out" "build/tests/$name.stress" || :
      exit 1
    fi
    i=$((i + 1))
  done
  echo "ok   $name x$N"
done
