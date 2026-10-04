#!/bin/sh
# Compiles every tests/*.bend with a bendc binary, runs it and compares the
# output with tests/*.out (produced by the official `bend`).
# Usage: ./run_tests.sh [bendc-binary]   (default: build/bendc0)
BENDC=${1:-build/bendc0}
case $BENDC in /*) ;; *) BENDC=$PWD/$BENDC ;; esac
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
mkdir -p build/tests
pass=0; fail=0
RTO=$PWD/build/bendrt.o
[ -f "$RTO" ] && [ "$RTO" -nt rt/bendrt_impl.c ] || ${CC:-clang} -O2 -w -I rt -c rt/bendrt_impl.c -o "$RTO"
LDL=; [ "$(uname)" = Linux ] && LDL=-ldl
for src in tests/*.bend; do
  name=$(basename "$src" .bend)
  out=build/tests/$name
  if ! "$BENDC" "$BASE" "$src" > "$out.c" 2> "$out.err"; then
    echo "FAIL $name (bendc)"; sed 's/^/  /' "$out.err" | head -5; fail=$((fail+1)); continue
  fi
  # Against the runtime compiled once (build/bendrt.o), but hello, which
  # compiles it whole.
  # tests/NAME.cflags: C flags for the program and a runtime of its own
  # (BEND_DEBUG_POISON, say).
  if [ "$name" = hello ]; then split=""; obj=""; else split="-DBEND_RT_SPLIT"; obj=$RTO; fi
  cflags=$(cat "tests/$name.cflags" 2>/dev/null)
  [ -n "$cflags" ] && { split=""; obj=""; }
  if ! ${CC:-clang} -O2 -w $split $cflags -I rt "$out.c" $obj -o "$out" -lm -lpthread $LDL 2> "$out.err"; then
    echo "FAIL $name (clang)"; sed 's/^/  /' "$out.err" | head -5; fail=$((fail+1)); continue
  fi
  # tests/NAME.env: environment settings for the run (BEND_GC_MIN_MB=1, say).
  env $(cat "tests/$name.env" 2>/dev/null) "./$out" > "$out.txt" 2> "$out.stderr"
  echo "exit $?" >> "$out.txt"
  if cmp -s "$out.txt" "tests/$name.out"; then
    echo "ok   $name"; pass=$((pass+1))
  else
    echo "FAIL $name (output)"; diff "$out.txt" "tests/$name.out" | head -10 | sed 's/^/  /'; fail=$((fail+1))
  fi
done
if sh tools/pf-codegen-check.sh "$BENDC" "$BASE" tests build/tests/pf_codegen > build/tests/pf_codegen.log 2>&1; then
  echo "ok   pf_codegen"; pass=$((pass+1))
else
  echo "FAIL pf_codegen"; cat build/tests/pf_codegen.log; fail=$((fail+1))
fi
if sh tools/ch-codegen-check.sh "$BENDC" "$BASE" tests build/tests/ch_codegen > build/tests/ch_codegen.log 2>&1; then
  echo "ok   ch_codegen"; pass=$((pass+1))
else
  echo "FAIL ch_codegen"; cat build/tests/ch_codegen.log; fail=$((fail+1))
fi
if python3 tools/ro-word-fold-check.py "$BENDC" "$BASE" tests build/tests/ro_word_fold_codegen > build/tests/ro_word_fold.log 2>&1; then
  echo "ok   ro_word_fold_codegen"; pass=$((pass+1))
else
  echo "FAIL ro_word_fold_codegen"; cat build/tests/ro_word_fold.log; fail=$((fail+1))
fi
if python3 tools/gpu-array-mask-check.py "$BENDC" "$BASE" tests/gpu_array_masks.bend > build/tests/gpu_array_mask_codegen.log 2>&1; then
  echo "ok   gpu_array_mask_codegen"; pass=$((pass+1))
else
  echo "FAIL gpu_array_mask_codegen"; cat build/tests/gpu_array_mask_codegen.log; fail=$((fail+1))
fi
if python3 tools/gpu-array-flow-check.py "$BENDC" "$BASE" > build/tests/gpu_array_flow_codegen.log 2>&1; then
  echo "ok   gpu_array_flow_codegen"; pass=$((pass+1))
else
  echo "FAIL gpu_array_flow_codegen"; cat build/tests/gpu_array_flow_codegen.log; fail=$((fail+1))
fi
if sh tools/gpu-zipper-check.sh "$BENDC" "$BASE" tests build/tests/gpu_zipper rt > build/tests/gpu_zipper.log 2>&1; then
  echo "ok   gpu_zipper_codegen_runtime"; pass=$((pass+1))
else
  echo "FAIL gpu_zipper_codegen_runtime"; cat build/tests/gpu_zipper.log; fail=$((fail+1))
fi
# C checks of the runtime (tests/rt/*.c, built whole with $CC): each
# prints "ok".
if sh tools/gpu-reduce-tree-check.sh "$BENDC" "$BASE" tests build/tests/gpu_reduce_tree rt > build/tests/gpu_reduce_tree.log 2>&1; then
  echo "ok   gpu_reduce_tree_codegen_runtime"; pass=$((pass+1))
else
  echo "FAIL gpu_reduce_tree_codegen_runtime"; cat build/tests/gpu_reduce_tree.log; fail=$((fail+1))
fi
if sh tools/gpu-host-check.sh "$BENDC" "$BASE" > build/tests/gpu_host_codegen.log 2>&1; then
  echo "ok   gpu_host_codegen"; pass=$((pass+1))
else
  echo "FAIL gpu_host_codegen"; cat build/tests/gpu_host_codegen.log; fail=$((fail+1))
fi
mkdir -p build/tests/rt
for src in tests/rt/*.c; do
  name=rt/$(basename "$src" .c)
  out=build/tests/$name
  if ${CC:-clang} -O2 -w -I rt "$src" -o "$out" -lm -lpthread $LDL 2> "$out.err" &&
     [ "$("./$out" 2>&1)" = ok ]; then
    echo "ok   $name"; pass=$((pass+1))
  else
    echo "FAIL $name"; { cat "$out.err"; "./$out" 2>&1; } | head -5 | sed 's/^/  /'; fail=$((fail+1))
  fi
done
# The same programs compiled with BEND_RC=1 (reference counts, no tracing),
# with the settings of tests/NAME.env. BEND_TEST_RC=0 skips them.
if [ "${BEND_TEST_RC:-1}" != 0 ]; then
  mkdir -p build/tests/rc
  for src in tests/*.bend; do
    name=$(basename "$src" .bend)
    out=build/tests/rc/$name
    if ! BEND_RC=1 "$BENDC" "$BASE" "$src" > "$out.c" 2> "$out.err" ||
       ! ${CC:-clang} -O2 -w -DBEND_RT_SPLIT -I rt "$out.c" "$RTO" -o "$out" -lm -lpthread $LDL 2> "$out.err"; then
      echo "FAIL rc/$name (build)"; sed 's/^/  /' "$out.err" | head -5; fail=$((fail+1)); continue
    fi
    env $(cat "tests/$name.env" 2>/dev/null) "./$out" > "$out.txt" 2> "$out.stderr"
    echo "exit $?" >> "$out.txt"
    if cmp -s "$out.txt" "tests/$name.out"; then
      echo "ok   rc/$name"; pass=$((pass+1))
    else
      echo "FAIL rc/$name (output)"; diff "$out.txt" "tests/$name.out" | head -10 | sed 's/^/  /'; fail=$((fail+1))
    fi
  done
fi
# !-calls on the device: the simulator everywhere, Metal on a Mac with a GPU.
# A run passes when its output matches and no !-call fell back to the CPU
# but the ones tests/NAME.fallbacks counts. A GPU
# that cannot load the cached kernels (CI's virtual one) compiles them.
gpu_modes=sim
[ "$(uname)" = Darwin ] && gpu_modes="sim metal"
for src in $(grep -l '[a-z0-9_]!(' tests/*.bend); do
  name=$(basename "$src" .bend)
  out=build/tests/$name
  for mode in $gpu_modes; do
    env $(cat "tests/$name.env" 2>/dev/null) BEND_GPU=$mode BEND_GPU_LOG=1 "./$out" > "$out.$mode.txt" 2> "$out.$mode.log"
    echo "exit $?" >> "$out.$mode.txt"
    if [ "$mode" = metal ] && grep -q "no GPU\|no Metal" "$out.$mode.log"; then continue; fi
    want=$(cat "tests/$name.fallbacks" 2>/dev/null || echo 0)
    got=$(grep -c "running on the CPU" "$out.$mode.log")
    if cmp -s "$out.$mode.txt" "tests/$name.out" && [ "$got" -eq "$want" ] &&
       ! grep -Ev '^bend gpu: (done|arena grows to [0-9]+ MB$)|does not load.*: compiling' "$out.$mode.log" | grep -qv "running on the CPU"; then
      echo "ok   $mode/$name"; pass=$((pass+1))
    else
      echo "FAIL $mode/$name"; diff "$out.$mode.txt" "tests/$name.out" | head -10 | sed 's/^/  /'
      grep -v "^bend gpu: done" "$out.$mode.log" | head -5 | sed 's/^/  /'; fail=$((fail+1))
    fi
  done
done

# The JavaScript target, run with Bun (when it is installed).
if command -v bun >/dev/null 2>&1; then
  mkdir -p build/js
  for src in tests/*.bend; do
    name=$(basename "$src" .bend)
    if ! "$BENDC" --js "$BASE" "$src" > "build/js/$name.js" 2> "build/js/$name.err"; then
      echo "FAIL js/$name (bendc)"; sed 's/^/  /' "build/js/$name.err" | head -5; fail=$((fail+1)); continue
    fi
    (cd tests && bun "../build/js/$name.js" > "../build/js/$name.txt" 2> "../build/js/$name.stderr"
     echo "exit $?" >> "../build/js/$name.txt")
    if cmp -s "build/js/$name.txt" "tests/$name.out"; then
      echo "ok   js/$name"; pass=$((pass+1))
    else
      echo "FAIL js/$name"; diff "build/js/$name.txt" "tests/$name.out" | head -10 | sed 's/^/  /'; fail=$((fail+1))
    fi
  done
fi

# The native backend (bendc --native: AArch64, Mach-O or ELF), on arm64
# macOS or Linux (BEND_TEST_NATIVE=0 skips it).
case $(uname -sm) in "Darwin arm64"|"Linux aarch64"|"Linux arm64") native=${BEND_TEST_NATIVE:-1};; *) native=0;; esac
if [ $native = 1 ]; then
  mkdir -p build/native
  for src in tests/*.bend; do
    name=$(basename "$src" .bend)
    out=build/native/$name
    if ! "$BENDC" --native -o "$out" "$BASE" "$src" > "$out.log" 2>&1; then
      echo "FAIL native/$name (bendc)"; sed 's/^/  /' "$out.log" | head -5; fail=$((fail+1)); continue
    fi
    env $(cat "tests/$name.env" 2>/dev/null) "./$out" > "$out.txt" 2> "$out.stderr"
    echo "exit $?" >> "$out.txt"
    if cmp -s "$out.txt" "tests/$name.out"; then
      echo "ok   native/$name"; pass=$((pass+1))
    else
      echo "FAIL native/$name"; diff "$out.txt" "tests/$name.out" | head -10 | sed 's/^/  /'; fail=$((fail+1))
    fi
  done
fi

# Type checking: bendc --check-only prints what bend --check-only prints.
for src in tests/check/*.bend; do
  name=check/$(basename "$src" .bend)
  (cd tests/check && "$BENDC" --check-only "$BASE" "$(basename "$src")" > "$OLDPWD/build/tests/check.txt" 2>&1
   echo "exit $?" >> "$OLDPWD/build/tests/check.txt")
  # a missing file is named by its absolute path: the .out spells the repo <repo>
  sed "s|$PWD/|<repo>/|g" build/tests/check.txt > build/tests/check.sed && mv build/tests/check.sed build/tests/check.txt
  if cmp -s build/tests/check.txt "tests/$name.out"; then
    echo "ok   $name"; pass=$((pass+1))
  else
    echo "FAIL $name"; diff build/tests/check.txt "tests/$name.out" | head -10 | sed 's/^/  /'; fail=$((fail+1))
  fi
done
if tests/hub/run.sh "$BENDC"; then pass=$((pass+1)); else fail=$((fail+1)); fi
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
