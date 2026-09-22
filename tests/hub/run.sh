#!/bin/sh
# Hub imports against a local hub: publishes tests/hub/pkg the way the hub
# stores packages (manifest of "sha256 path" lines, named by its own hash),
# serves it over HTTP, and imports it by hash.
# Usage: tests/hub/run.sh <bendc-binary>
set -e
BENDC=$(cd "$(dirname "$1")" && pwd)/$(basename "$1")
BASE=${BEND_BASE:-$HOME/.bend/bend2/base.bend}
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
W=$(mktemp -d)
trap 'kill $SRV 2>/dev/null; rm -rf "$W"' EXIT
cd "$ROOT/tests/hub/pkg"
H=$(python3 - "$W/www" <<'PY'
import hashlib, os, sys
files = {}
for d, _, fs in os.walk('.'):
    for f in fs:
        p = os.path.relpath(os.path.join(d, f), '.')
        files[p] = open(p).read()
sha = lambda t: hashlib.sha256(t.encode()).hexdigest()
man = ''.join(f"{sha(files[p])} {p}\n" for p in sorted(files))
h = '0x' + sha(man)[:32]
for p, t in files.items():
    os.makedirs(os.path.dirname(f'{sys.argv[1]}/{h}/{p}'), exist_ok=True)
    open(f'{sys.argv[1]}/{h}/{p}', 'w').write(t)
open(f'{sys.argv[1]}/{h}/manifest', 'w').write(man)
print(h)
PY
)
PORT=$((20000 + $$ % 20000))
python3 -m http.server $PORT --directory "$W/www" >/dev/null 2>&1 &
SRV=$!
printf 'import Base\nimport %s/geo.bend as Geo\n\ndef main() -> IO(Unit):\n  IO.print(U32.show(Geo.area(3, 7)))\n' "$H" > "$W/main.bend"
for i in 1 2 3 4 5 6 7 8 9 10; do curl -fs "http://127.0.0.1:$PORT/$H/manifest" >/dev/null && break; sleep 0.3; done
export BEND_HUB=http://127.0.0.1:$PORT BEND_LIB=$W/lib
"$BENDC" "$BASE" "$W/main.bend" > "$W/main.c"
${CC:-clang} -O2 -w -I "$ROOT/rt" "$W/main.c" -o "$W/main" -lm -lpthread
out=$("$W/main")
[ "$out" = 42 ] || { echo "FAIL hub (got '$out')"; exit 1; }
# A file that no longer matches its hash is refused.
rm -rf "$W/lib"
echo "# tampered" >> "$W/www/$H/util/sq.bend"
if "$BENDC" "$BASE" "$W/main.bend" > /dev/null 2>&1; then echo "FAIL hub (accepted a tampered file)"; exit 1; fi
echo "ok   hub"
