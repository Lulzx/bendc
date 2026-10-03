#!/bin/sh
set -eu
# These assertions cover the tracing backend; bounded programs may choose
# hybrid reference counting automatically unless the mode is explicit.
BEND_RC=0
export BEND_RC
BENDC=${1:-build/bendc}
BASE=${2:-build/base34/base.bend}
SRC=${3:-tests}
OUT=${4:-build/probe/pf-codegen-check}
mkdir -p "$OUT"
for name in pf_partial pf_partial_box pf_partial_foreign pf_partial_reuse pf_partial_arities; do
  "$BENDC" "$BASE" "$SRC/$name.bend" > "$OUT/$name.c"
done
# A recursive sequential frontier directly consumes the qualified helper.
grep -Fq 'static V PS_weave(' "$OUT/pf_partial.c"
grep -Eq '^PS_weave\(' "$OUT/pf_partial.c"
grep -Eq 'BEND_PF_TOK.*= u258_' "$OUT/pf_partial.c"
# Reuse is transferred before freeing its old owner.
python3 - "$OUT/pf_partial.c" <<'PY'
import re,sys
s=open(sys.argv[1]).read()
transfers=re.findall(r'if \(!BEND_PF_TOK\(([^)]*)\)\) \{ BEND_PF_TOK\(\1\) = (u258_\w+); \2 = 0; \}\nRUFG\(\2, 258\);',s)
assert transfers, 'no parent-token transfer precedes its old-owner free'
PY
# Wider results preserve aliases and reuse; arity nine uses ordinary nodes.
grep -Eq '^PS_fan3\(' "$OUT/pf_partial_arities.c"
grep -Eq '^PS_fan8\(' "$OUT/pf_partial_arities.c"
grep -Eq 'BEND_PF_TOK.*u259_' "$OUT/pf_partial_arities.c"
grep -Eq 'BEND_PF_TOK.*u264_' "$OUT/pf_partial_arities.c"
if grep -Eq 'static V P[FS]_fan9\(' "$OUT/pf_partial_arities.c"; then
  echo 'unexpected partial helper for arity nine' >&2; exit 1
fi
# Two ordinary node constructors and foreign-exposed Data retain headers.
for name in pf_partial_box pf_partial_foreign; do
  if grep -Eq 'static V P[FS]_weave\(' "$OUT/$name.c"; then
    echo "unexpected partial helper in $name" >&2; exit 1
  fi
done
# Counting references and disabling freeing keep the original path.
BEND_RC=1 "$BENDC" "$BASE" "$SRC/pf_partial.bend" > "$OUT/pf_partial_rc.c"
BEND_NO_FREE=1 "$BENDC" "$BASE" "$SRC/pf_partial.bend" > "$OUT/pf_partial_nofree.c"
for name in pf_partial_rc pf_partial_nofree; do
  if grep -Eq 'static V P[FS]_weave\(' "$OUT/$name.c"; then
    echo "unexpected partial helper in $name" >&2; exit 1
  fi
done
echo 'qualified leaf results and parent reuse present; headered, foreign, RC and no-free paths excluded'
