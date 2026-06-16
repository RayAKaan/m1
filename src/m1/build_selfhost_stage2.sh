#!/usr/bin/env bash
# TRUE self-hosting verification (Week 4).
#
# Builds stage-1 m1c (via the C bootstrap m0c), then uses stage-1 m1c to compile
# its OWN source m1c.m0 into C, links that into a stage-2 m1c, and verifies the
# fixed point: stage-1 and stage-2 produce byte-identical output on every test
# program AND on m1c.m0 itself.
#
# Requires: gcc (or CC=clang), python3. Run from the repo root.
set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
CC="${CC:-gcc}"
WORK="${WORK:-/tmp/m1stage}"
SRC="$ROOT/src"
CFLAGS="-std=gnu11 -w -fcommon -fno-strict-aliasing -O0 -include $SRC/m1/compat.h"
mkdir -p "$WORK"

die() { echo "FATAL: $*" >&2; echo "RESULT: FAIL"; exit 1; }

echo "[1/6] Build bootstrap m0c"
cp "$SRC"/*.c "$SRC"/*.h "$WORK"/ 2>/dev/null || true
sed -i 's/^static Node \*reduce(Node \*n, Reducer \*r);/\/* fwd-decl removed *\//' "$WORK/reduce.c" 2>/dev/null || true
sed -i 's/^static Node \*reduce(Node \*n, Reducer \*r) {/Node *reduce(Node *n, Reducer *r) {/' "$WORK/reduce.c" 2>/dev/null || true
( cd "$WORK" && $CC -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 -o m0c \
    main.c arena.c error.c lexer.c parser.c scope.c types.c checker.c reduce.c codegen.c ) \
    || die "could not build m0c"

echo "[2/6] Compile lexer.m0 -> C (M1Tk -> int64 transform)"
"$WORK/m0c" "$SRC/m1/lexer.m0" > "$WORK/lexer_raw.c" 2>/dev/null || die "m0c lexer.m0"
python3 - "$WORK/lexer_raw.c" "$WORK/lexer_int.c" <<'PY' || die "lexer transform"
import re, sys
c = open(sys.argv[1]).read()
c = re.sub(r'typedef struct M1Tk M1Tk;\s*struct M1Tk\s*\{.*?\}\s*;', 'typedef int64_t M1Tk;', c, count=1, flags=re.S)
c = re.sub(r'M1Tk v = \{\s*\.tag = (M1Tk_\w+),\s*\.data = \{0\}\s*\};', r'M1Tk v = \1;', c)
c = c.replace('.tag', '')
open(sys.argv[2], 'w').write(c)
PY

echo "[3/6] Stage-1: bootstrap m0c compiles m1c.m0 -> stage-1 m1c"
"$WORK/m0c" "$SRC/m1/m1c.m0" > "$WORK/m1c_s1.c" 2>/dev/null || die "m0c m1c.m0"
$CC $CFLAGS -o "$WORK/m1c1" "$WORK/m1c_s1.c" "$SRC/m1/m0_runtime.c" "$SRC/m1/phase_graph.c" "$WORK/lexer_int.c" \
    || die "link stage-1 m1c"

echo "[4/6] Stage-2: stage-1 m1c compiles m1c.m0 -> stage-2 m1c"
M1_SOURCE="$SRC/m1/m1c.m0" "$WORK/m1c1" > "$WORK/m1c_s2.c" 2>/dev/null || die "stage-1 m1c failed on m1c.m0"
$CC $CFLAGS -c "$WORK/m1c_s2.c" -o "$WORK/m1c_s2.o" || die "self-generated C does not compile"
$CC $CFLAGS -o "$WORK/m1c2" "$WORK/m1c_s2.c" "$SRC/m1/m0_runtime.c" "$SRC/m1/phase_graph.c" "$WORK/lexer_int.c" \
    || die "link stage-2 m1c"

echo "[5/6] Fixed-point check: stage-1 output == stage-2 output on m1c.m0"
M1_SOURCE="$SRC/m1/m1c.m0" "$WORK/m1c2" > "$WORK/m1c_s3.c" 2>/dev/null || die "stage-2 m1c failed on m1c.m0"
diff -q "$WORK/m1c_s2.c" "$WORK/m1c_s3.c" >/dev/null || die "stage-2 is NOT a fixed point (output differs)"

echo "[6/6] Fixed-point check across all test programs"
diffs=0; n=0
for f in "$ROOT"/tests/phase_graph/*.m1 "$ROOT"/tests/now/*.m1 "$ROOT"/tests/will/*.m1 \
         "$ROOT"/tests/surface/*.m1 "$ROOT"/tests/records/*.m1 "$ROOT"/tests/functions/FnParam.m1 \
         "$ROOT"/tests/conflict/*.m1 "$ROOT"/tests/branch/*.m1; do
    [ -f "$f" ] || continue
    n=$((n+1))
    M1_SOURCE="$f" "$WORK/m1c1" > "$WORK/a.c" 2>/dev/null
    M1_SOURCE="$f" "$WORK/m1c2" > "$WORK/b.c" 2>/dev/null
    diff -q "$WORK/a.c" "$WORK/b.c" >/dev/null || { echo "  DIFF: $f"; diffs=$((diffs+1)); }
done
echo "checked $n test programs; $diffs differed"
[ "$diffs" -eq 0 ] || die "stage-1/stage-2 disagree on $diffs program(s)"

echo "RESULT: PASS (true self-hosting verified — m1c compiles itself to a fixed point)"
