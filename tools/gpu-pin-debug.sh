#!/bin/sh
# Inspect the failing pinned-tree fixture on the actual device. Run after
# building bendc; each executable has its own runtime and arena.
set -eu
cd "$(dirname "$0")/.."
root=$PWD
compiler=${1:-build/bendc}
case $compiler in /*) ;; *) compiler=$root/$compiler ;; esac
base=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
case $base in /*) ;; *) base=$root/$base ;; esac
dir=$root/build/gpu-pin-debug
mkdir -p "$dir"
"$compiler" "$base" tests/gpu_growth_pinned.bend > "$dir/pin_program.c"
ldl=; [ "$(uname -s)" != Linux ] || ldl=-ldl
"${CC:-cc}" -O2 -w -I rt -c rt/bendrt_impl.c -o "$dir/bendrt.o"
status=0
for layout in full split; do
  split=; obj=
  if [ "$layout" = split ]; then split=-DBEND_RT_SPLIT; obj=$dir/bendrt.o; fi
  "${CC:-cc}" -O2 -w $split -I rt -I "$dir" tools/gpu-pin-debug.c $obj \
    -o "$dir/$layout" -lm -lpthread $ldl
  for pin in 0 512; do
    echo "=== pinned-tree diagnostic: runtime=$layout pin_min_mb=$pin ==="
    backend=sim; [ "$(uname -s)" != Darwin ] || backend=metal
    if BEND_GPU=$backend BEND_GPU_PIN_MB=$pin "$dir/$layout" \
       > "$dir/$layout-$pin.out" 2> "$dir/$layout-$pin.log"; then
      echo "exit 0"
    else
      result=$?
      echo "exit $result"
      status=1
    fi
    cat "$dir/$layout-$pin.log"
  done
done
exit "$status"
