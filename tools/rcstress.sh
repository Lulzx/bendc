#!/bin/sh
# Runs the multithreaded tests, compiled with BEND_RC=1 by run_tests.sh, many
# times each with a one-megabyte heap, and fails on the first run whose
# output differs.  Usage: tools/rcstress.sh [runs]   (default 300)
N=${1:-300}
fail=0
for name in rcstress par fork chan stress dps gc; do
  bin=build/tests/rc/$name
  [ -x "$bin" ] || { echo "missing $bin (run ./run_tests.sh first)"; exit 1; }
  i=0
  while [ $i -lt "$N" ]; do
    BEND_GC_MIN_MB=1 "$bin" > build/tests/rc/$name.stress 2>&1
    echo "exit $?" >> build/tests/rc/$name.stress
    if ! cmp -s build/tests/rc/$name.stress "tests/$name.out"; then
      echo "FAIL $name (run $i)"; diff build/tests/rc/$name.stress "tests/$name.out" | head -5; fail=1; break
    fi
    i=$((i+1))
  done
  [ $i -eq "$N" ] && echo "ok   $name x$N"
done
exit $fail
