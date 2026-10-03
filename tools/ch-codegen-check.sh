#!/bin/sh
set -eu
BENDC=${1:-build/bendc}
BASE=${2:-build/base34/base.bend}
SRC=${3:-tests}
OUT=${4:-build/probe/ch-codegen-check}
mkdir -p "$OUT"
"$BENDC" "$BASE" "$SRC/choice_words.bend" > "$OUT/words.c"
"$BENDC" "$BASE" "$SRC/choice_effects.bend" > "$OUT/effects.c"
python3 - "$OUT" <<'PY'
import sys
from pathlib import Path
p=Path(sys.argv[1]);words=(p/'words.c').read_text();effects=(p/'effects.c').read_text()
assert words.count('V cw = ')==2, 'immutable same-shape scalar alternatives not selected'
assert 'cw != IMM(0) && cw != IMM(1)' in words, 'Bool fail-stop guard missing'
assert effects.count('V cw = ')==0, 'effectful branch was speculated'
print('same-shape scalar constructor choices retain Bool validity; effectful branches excluded')
PY
