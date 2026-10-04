#!/usr/bin/env python3
"""Check borrowed fixed-width folds and conservative ownership exclusions."""
from pathlib import Path
import os, re, subprocess, sys
compiler, base, tests, out = sys.argv[1:5]
tests = Path(tests); out = Path(out); out.mkdir(parents=True, exist_ok=True)
env = {k:v for k,v in os.environ.items() if k not in ("BEND_RC", "BEND_NO_FREE")}
env["BEND_RC"] = "1"
programs = {}
for name in ("ro_word_fold", "ro_word_nat_fold", "ro_word_callback_fold"):
    r = subprocess.run([compiler, base, str(tests/(name+".bend"))], env=env, capture_output=True, text=True)
    (out/(name+".c")).write_text(r.stdout)
    (out/(name+".log")).write_text(r.stderr)
    assert r.returncode == 0, name + ": " + r.stderr
    programs[name] = r.stdout
positive = programs["ro_word_fold"]
body = re.search(r"static __attribute__\(\(noinline\)\) V H_F_fold_x37bseq\([^\n]*\) \{\n(.*?)\n\}\n(?=BEND_UINL|static)", positive, re.S)
assert body, "fixed-width fold has no borrowed clone"
assert "FLD(" in body.group(1) and "/*b*/" in body.group(1), "clone does not borrow its fields"
assert not re.search(r"\brc_(take|take_ru|drop|share|inc|dec)\w*\(", body.group(1)), "clone retains per-node RC work"
assert re.search(r"if \(par_depth >= par_front\).*F_fold_x37bseq.*rc_drop", positive), "frontier must retain then drop owned root"
assert "F_pointer_x37bseq" not in positive, "pointer result must retain owned traversal"
assert "F_fold_x37bseq" not in programs["ro_word_nat_fold"], "Nat result must not use fixed-width clone"
assert "F_effect_x37bseq" not in programs["ro_word_callback_fold"], "unknown callable must retain ownership"
print("ok")
