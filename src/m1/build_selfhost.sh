#!/usr/bin/env bash
# Build the self-hosted M1 compiler (m1c) on Linux/macOS and run the
# full temporal test suite. This is the reproducible pipeline that
# validates all Week 1-3 features.
#
#   bootstrap m0c (C)  ->  compile m1c.m0 -> C  ->  link -> m1c
#   m1c  ->  compile tests/*.m1 -> C  ->  link -> run
#
# Requirements: gcc (or clang via CC=clang), python3.
set -euo pipefail
HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
CC="${CC:-gcc}"
WORK="${WORK:-/tmp/m1build}"
mkdir -p "$WORK"

pass=0
fail=0

run_test() {
    local t="$1" f="$2" expect="$3"
    [ -f "$f" ] || return
    M1_SOURCE="$f" "$WORK/m1c" > "$WORK/$t.c" 2>"$WORK/$t.err" || {
        echo "  $t: m1c FAILED"; fail=$((fail+1)); return
    }
    $CC -std=gnu11 -w -fcommon -include "$ROOT/src/m1/compat.h" \
        -o "$WORK/$t.exe" "$WORK/$t.c" \
        "$ROOT/src/m1/m0_runtime.c" "$ROOT/src/m1/phase_graph.c" 2>/dev/null || {
        echo "  $t: gcc FAILED"; fail=$((fail+1)); return
    }
    local out; out="$("$WORK/$t.exe" 2>/dev/null)"
    if [ "$out" = "$expect" ]; then
        echo "  $t: output=$out  expected=$expect  PASS"; pass=$((pass+1))
    else
        echo "  $t: output=$out  expected=$expect  FAIL"
        echo "  $t: stderr=$(cat "$WORK/$t.err" 2>/dev/null)"
        fail=$((fail+1))
    fi
}

run_conflict() {
    local t="$1" f="$2" expect="$3"
    [ -f "$f" ] || return
    M1_SOURCE="$f" "$WORK/m1c" > "$WORK/$t.c" 2>"$WORK/$t.err" || {
        echo "  $t: m1c FAILED"; fail=$((fail+1)); return
    }
    local n; n="$(grep -c M1102 "$WORK/$t.err" 2>/dev/null)" || true; n="${n:-0}"
    if [ "$n" = "$expect" ]; then
        echo "  $t: M1102_conflicts=$n  expected=$expect  PASS"; pass=$((pass+1))
    else
        echo "  $t: M1102_conflicts=$n  expected=$expect  FAIL"; fail=$((fail+1))
    fi
}

echo "[1/5] Build bootstrap m0c from C sources"
SRC="$ROOT/src"
cp "$SRC"/*.c "$SRC"/*.h "$WORK"/ 2>/dev/null || true
( cd "$WORK" && $CC -std=gnu11 -w -fcommon -o m0c \
    main.c arena.c error.c lexer.c parser.c scope.c types.c checker.c reduce.c codegen.c )
echo "    -> $WORK/m0c"

echo "[2/5] Compile lexer.m0 -> C, transform M1Tk sum tag to int64"
"$WORK/m0c" "$SRC/m1/lexer.m0" > "$WORK/lexer_raw.c"
python3 - "$WORK/lexer_raw.c" "$WORK/lexer_int.c" <<'PY'
import re, sys
c = open(sys.argv[1]).read()
c = c.replace(
    "typedef struct M1Tk M1Tk;\nstruct M1Tk {\n  int tag;\n  union {\n    char _unused[1];\n    } data;\n};",
    "typedef int64_t M1Tk;"
)
c = re.sub(r'M1Tk v = \{ \.tag = (M1Tk_\w+), \.data = \{0\} \};', r'M1Tk v = \1;', c)
c = c.replace('.tag', '')
open(sys.argv[2], 'w').write(c)
PY

echo "[3/5] Compile m1c.m0 -> C with bootstrap m0c"
"$WORK/m0c" "$SRC/m1/m1c.m0" > "$WORK/m1c_self.c"
echo "    -> $WORK/m1c_self.c"

echo "[4/5] Link the self-hosted m1c"
$CC -std=gnu11 -w -fcommon -include "$ROOT/src/m1/compat.h" -o "$WORK/m1c" \
    "$WORK/m1c_self.c" "$ROOT/src/m1/m0_runtime.c" "$ROOT/src/m1/phase_graph.c" \
    "$WORK/lexer_int.c"
echo "    -> $WORK/m1c"

echo "[5/5] Run temporal test suite"

echo "  5a) Phase graph basic tests"
for t in WasBasic WasBefore WasNever WasRuntime WasLive; do
    run_test "$t" "$ROOT/tests/phase_graph/$t.m1" ""
done

echo "  5b) Now re-check tests"
run_test NowRecheck "$ROOT/tests/now/NowRecheck.m1" ""
run_test NowOk     "$ROOT/tests/now/NowOk.m1" 1

echo "  5c) Will return-guard tests"
run_test WillOk   "$ROOT/tests/will/WillOk.m1"   1
run_test WillFail "$ROOT/tests/will/WillFail.m1" 0

echo "  5d) Value-named phase test"
run_test WasValPhase "$ROOT/tests/phase_graph/WasValPhase.m1" 11110

echo "  5e) Surface syntax tests"
run_test WorldDoSet "$ROOT/tests/surface/WorldDoSet.m1" 1
run_test SaySay    "$ROOT/tests/surface/SaySay.m1"     ""
run_test SayInt    "$ROOT/tests/surface/SayInt.m1"     ""

echo "  5f) Records + function-parameter tests"
run_test RecBasic "$ROOT/tests/records/RecBasic.m1"       3
run_test RecParam "$ROOT/tests/records/RecParam.m1"      10
run_test FnParam  "$ROOT/tests/functions/FnParam.m1"     16

echo "  5g) Conflict detection tests"
run_conflict WillNowConflict "$ROOT/tests/conflict/WillNowConflict.m1" 1
run_conflict NoConflict      "$ROOT/tests/conflict/NoConflict.m1"     0

echo "  5h) Branch-aware soundness tests"
run_test CondNoFold   "$ROOT/tests/branch/CondNoFold.m1"   0
run_test StraightFold "$ROOT/tests/branch/StraightFold.m1" 1

echo "Done: $((pass + fail)) tests ran — $pass passed, $fail failed."
if [ "$fail" -ne 0 ]; then
    echo "RESULT: FAIL"
    exit 1
fi
echo "RESULT: PASS"
