#!/bin/sh
# Stress the threaded builds used by the tcc merge gate.
set -eu
cd "$(dirname "$0")/.."
N=${1:-100}
case "$N" in ''|*[!0-9]*|0) echo "usage: $0 [positive run count]" >&2; exit 2;; esac
for name in rc/autopar autopar maps par fork chan stress dps par_free gc; do
  [ -x "build/tests/$name" ] || { echo "missing build/tests/$name" >&2; exit 1; }
done
for name in rc/autopar autopar maps par fork chan stress dps par_free gc; do
  test=${name#rc/}
  i=0
  while [ "$i" -lt "$N" ]; do
    status=0
    env $(cat "tests/$test.env" 2>/dev/null || :) BEND_GC_MIN_MB=1 "build/tests/$name" > "build/tests/$name.threadstress" 2>&1 || status=$?
    echo "exit $status" >> "build/tests/$name.threadstress"
    if ! cmp -s "build/tests/$name.threadstress" "tests/$test.out"; then
      echo "FAIL $name (run $i)" >&2
      diff "tests/$test.out" "build/tests/$name.threadstress" || :
      exit 1
    fi
    i=$((i + 1))
  done
  echo "ok   $name x$N"
done
