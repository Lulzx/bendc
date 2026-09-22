#!/bin/sh
# Compiles every tests/*.bend with a bendc binary, runs it and compares the
# output with tests/*.out (produced by the official `bend`).
# Usage: ./run_tests.sh [bendc-binary]   (default: build/bendc0)
BENDC=${1:-build/bendc0}
case $BENDC in /*) ;; *) BENDC=$PWD/$BENDC ;; esac
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
mkdir -p build/tests
pass=0; fail=0
for src in tests/*.bend; do
  name=$(basename "$src" .bend)
  out=build/tests/$name
  if ! "$BENDC" "$BASE" "$src" > "$out.c" 2> "$out.err"; then
    echo "FAIL $name (bendc)"; sed 's/^/  /' "$out.err" | head -5; fail=$((fail+1)); continue
  fi
  if ! ${CC:-clang} -O2 -w -I rt "$out.c" -o "$out" -lm -lpthread 2> "$out.err"; then
    echo "FAIL $name (clang)"; sed 's/^/  /' "$out.err" | head -5; fail=$((fail+1)); continue
  fi
  "./$out" > "$out.txt" 2> "$out.stderr"
  echo "exit $?" >> "$out.txt"
  if cmp -s "$out.txt" "tests/$name.out"; then
    echo "ok   $name"; pass=$((pass+1))
  else
    echo "FAIL $name (output)"; diff "$out.txt" "tests/$name.out" | head -10 | sed 's/^/  /'; fail=$((fail+1))
  fi
done
# Type checking: bendc --check-only prints what bend --check-only prints.
for src in tests/check/*.bend; do
  name=check/$(basename "$src" .bend)
  (cd tests/check && "$BENDC" --check-only "$BASE" "$(basename "$src")" > "$OLDPWD/build/tests/check.txt" 2>&1
   echo "exit $?" >> "$OLDPWD/build/tests/check.txt")
  if cmp -s build/tests/check.txt "tests/$name.out"; then
    echo "ok   $name"; pass=$((pass+1))
  else
    echo "FAIL $name"; diff build/tests/check.txt "tests/$name.out" | head -10 | sed 's/^/  /'; fail=$((fail+1))
  fi
done
if tests/hub/run.sh "$BENDC"; then pass=$((pass+1)); else fail=$((fail+1)); fi
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
