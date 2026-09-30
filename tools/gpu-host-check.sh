#!/bin/sh
# Host offload must preserve parallel work reachable through a callee,
# while retaining the serial tail policy. Disable optimization so this
# checks the original direct and transitive calls, before inlining.
set -eu
cd "$(dirname "$0")/.."
BENDC=${1:-build/bendc}
BASE=${2:-${BEND_BASE:-$HOME/.bend/bend2/base.bend}}
mkdir -p build/tests
out=build/tests/gpu_host_codegen.c
BEND_OPT= "$BENDC" "$BASE" tests/gpu_host_parallel.bend > "$out"
grep -Fq 'static V KH_serial(' "$out"
grep -Fq 'static V KH_implicit(' "$out"
if grep -Eq 'static V KH_(split|bridge)\(' "$out"; then
  echo 'parallel work was offered to the serial host dispatcher' >&2
  exit 1
fi
echo 'serial host offload retained; direct/transitive parallel work stays on GPU'
