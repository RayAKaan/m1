#!/usr/bin/env bash
# Build the self-hosted M1 compiler (m1c) and run the temporal test suite.
# v0.6.0-60: Added pick/shape, bare expressions, say(int) auto-coerce, Windows CI

set -u

HERE="$(cd "$(dirname "$0")" && pwd)"
ROOT="$(cd "$HERE/../.." && pwd)"
CC="${CC:-gcc}"
WORK="${WORK:-/tmp/m1build}"
SRC="$ROOT/src"
mkdir -p "$WORK"

pass=0
fail=0
FAILED=""

die() { echo "FATAL: $*" >&2; echo "RESULT: FAIL"; exit 1; }

count() { grep -c "$1" "$2" 2>/dev/null | head -n1 | tr -cd '0-9'; }

echo "[1/5] Build bootstrap m0c from C sources"
cp "$SRC"/*.c "$SRC"/*.h "$WORK"/ 2>/dev/null || true
sed -i 's/^static Node \*reduce(Node \*n, Reducer \*r);/\/\* fwd-decl removed: matches reduce.h \*\//' "$WORK/reduce.c" 2>/dev/null || true
sed -i 's/^static Node \*reduce(Node \*n, Reducer \*r) {/Node *reduce(Node *n, Reducer *r) {/' "$WORK/reduce.c" 2>/dev/null || true
( cd "$WORK" && $CC -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 -o m0c \
    main.c arena.c error.c lexer.c parser.c scope.c types.c checker.c reduce.c codegen.c ) \
    || die "could not build bootstrap m0c"
[ -x "$WORK/m0c" ] || die "m0c was not produced"

echo "[2/5] Compile lexer.m0 -> C, normalize M1Tk tag to int64"
"$WORK/m0c" "$SRC/m1/lexer.m0" > "$WORK/lexer_raw.c" 2>"$WORK/lexer_raw.err" \
    || die "m0c failed to compile lexer.m0 (see $WORK/lexer_raw.err)"
python3 - "$WORK/lexer_raw.c" "$WORK/lexer_int.c" <<'PY' || die "lexer transform failed"
import re, sys
c = open(sys.argv[1]).read()
c2 = re.sub(
    r'typedef struct M1Tk M1Tk;\s*struct M1Tk\s*\{.*?\}\s*;',
    'typedef int64_t M1Tk;',
    c, count=1, flags=re.S)
if c2 == c:
    sys.stderr.write("WARN: M1Tk struct pattern not found; emitting unchanged\n")
c = c2
c = re.sub(r'M1Tk v = \{\s*\.tag = (M1Tk_\w+),\s*\.data = \{0\}\s*\};', r'M1Tk v = \1;', c)
c = c.replace('.tag', '')
open(sys.argv[2], 'w').write(c)
PY
grep -q "typedef int64_t M1Tk;" "$WORK/lexer_int.c" \
    || die "lexer M1Tk normalization did not apply (struct shape changed?)"

echo "[3/5] Compile m1c.m0 -> C with bootstrap m0c"
"$WORK/m0c" "$SRC/m1/m1c.m0" > "$WORK/m1c_self.c" 2>"$WORK/m1c_self.err"
m0c_errs="$(count ERROR "$WORK/m1c_self.err")"; m0c_errs="${m0c_errs:-0}"
if [ "$m0c_errs" != "0" ]; then
    echo "---- m0c errors compiling m1c.m0 ----"; cat "$WORK/m1c_self.err"
    die "m0c reported $m0c_errs error(s) compiling m1c.m0"
fi
[ -s "$WORK/m1c_self.c" ] || die "m1c_self.c is empty"

echo "[4/5] Link the self-hosted m1c"
$CC -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 -include "$SRC/m1/compat.h" -o "$WORK/m1c" \
    "$WORK/m1c_self.c" "$SRC/m1/m0_runtime.c" "$SRC/m1/phase_graph.c" \
    "$WORK/lexer_int.c" 2>"$WORK/m1c_link.err" \
    || { echo "---- link errors ----"; cat "$WORK/m1c_link.err"; die "could not link m1c"; }
[ -x "$WORK/m1c" ] || die "m1c was not produced"
echo "    -> $WORK/m1c"

build_one() {
    local t="$1" f="$2"
    COUT="$WORK/$t.c"; CERR="$WORK/$t.err"; RERR="$WORK/$t.run_err"
    ROUT=""; REXIT=0
    M1_SOURCE="$f" "$WORK/m1c" > "$COUT" 2>"$CERR" || return 1
    $CC -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 -include "$SRC/m1/compat.h" \
        -o "$WORK/$t.exe" "$COUT" "$SRC/m1/m0_runtime.c" "$SRC/m1/phase_graph.c" \
        2>"$WORK/$t.cc" || return 1
    ROUT="$("$WORK/$t.exe" 2>"$RERR")"; REXIT=$?
    return 0
}

show_fail() {
    local t="$1"
    FAILED="$FAILED $t"
    echo "    --- $t: generated C (main) ---"
    sed -n '/int main/,/^}/p' "$WORK/$t.c" 2>/dev/null | sed 's/^/    /'
    echo "    --- $t: m1c stderr ---"; sed 's/^/    /' "$WORK/$t.err" 2>/dev/null
    echo "    --- $t: cc stderr ---";  sed 's/^/    /' "$WORK/$t.cc" 2>/dev/null
}

check_out() {
    local t="$1" f="$2" expect="$3"
    if [ ! -f "$f" ]; then echo "  $t: SKIP (missing $f)"; return; fi
    if ! build_one "$t" "$f"; then
        echo "  $t: FAIL (m1c/cc could not build)"; show_fail "$t"; fail=$((fail+1)); return
    fi
    if [ "$ROUT" = "$expect" ]; then
        echo "  $t: output=$ROUT expected=$expect PASS"; pass=$((pass+1))
    else
        echo "  $t: output=$ROUT expected=$expect FAIL"; show_fail "$t"; fail=$((fail+1))
    fi
}

check_diag() {
    local t="$1" f="$2" code="$3" expect="$4"
    if [ ! -f "$f" ]; then echo "  $t: SKIP (missing $f)"; return; fi
    if ! build_one "$t" "$f"; then
        echo "  $t: FAIL (m1c/cc could not build)"; show_fail "$t"; fail=$((fail+1)); return
    fi
    local n; n="$(count "$code" "$CERR")"; n="${n:-0}"
    if [ "$n" = "$expect" ]; then
        echo "  $t: ${code}=$n expected=$expect PASS"; pass=$((pass+1))
    else
        echo "  $t: ${code}=$n expected=$expect FAIL"; show_fail "$t"; fail=$((fail+1))
    fi
}

check_rdiag() {
    local t="$1" f="$2" code="$3" expect="$4"
    if [ ! -f "$f" ]; then echo "  $t: SKIP (missing $f)"; return; fi
    if ! build_one "$t" "$f"; then
        echo "  $t: FAIL (m1c/cc could not build)"; show_fail "$t"; fail=$((fail+1)); return
    fi
    local n; n="$(count "$code" "$RERR")"; n="${n:-0}"
    if [ "$n" = "$expect" ]; then
        echo "  $t: ${code}=$n expected=$expect PASS"; pass=$((pass+1))
    else
        echo "  $t: ${code}=$n expected=$expect FAIL"; show_fail "$t"; fail=$((fail+1))
    fi
}

PG="$ROOT/tests/phase_graph"
echo "[5/5] Run test suite (v0.6.0-60: 21 tests)"

echo "  -- Phase Graph (was folding) --"
check_out WasBasic    "$PG/WasBasic.m1"    1
check_out WasBefore   "$PG/WasBefore.m1"   1
check_out WasNever    "$PG/WasNever.m1"    0
check_out WasRuntime  "$PG/WasRuntime.m1"  0
check_out WasLive     "$PG/WasLive.m1"     1
check_out WasValPhase "$PG/WasValPhase.m1" 11110

echo "  -- now re-check (F1) --"
check_out   NowOk      "$ROOT/tests/now/NowOk.m1"      10
check_out   NowRecheck "$ROOT/tests/now/NowRecheck.m1" -5
check_rdiag NowRecheck "$ROOT/tests/now/NowRecheck.m1" M1100 1
check_rdiag NowOk      "$ROOT/tests/now/NowOk.m1"      M1100 0

echo "  -- will return guard (F2) --"
check_out   WillOk   "$ROOT/tests/will/WillOk.m1"   1
check_out   WillFail "$ROOT/tests/will/WillFail.m1" 0
check_rdiag WillOk   "$ROOT/tests/will/WillOk.m1"   M1101 0
check_rdiag WillFail "$ROOT/tests/will/WillFail.m1" M1101 1

echo "  -- surface syntax (F4) --"
check_out WorldDoSet "$ROOT/tests/surface/WorldDoSet.m1" 1
check_out SayInt     "$ROOT/tests/surface/SayInt.m1"     42

echo "  -- pick / shape (v0.6.0-60) --"
check_out PickBasic  "$ROOT/tests/pick/PickBasic.m1"   1
check_out ShapeBasic "$ROOT/tests/shape/ShapeBasic.m1" 42

echo "  -- bare expressions (v0.6.0-60) --"
check_out BareExpr   "$ROOT/tests/surface/BareExpr.m1" 1

echo "  -- say(int) auto-coerce (v0.6.0-60) --"
check_out   SayIntAuto "$ROOT/tests/surface/SayIntAuto.m1" 42
check_rdiag SayIntAuto "$ROOT/tests/surface/SayIntAuto.m1" M1100 0

echo "  -- records + function params (W3 Item 1) --"
check_out RecBasic "$ROOT/tests/records/RecBasic.m1"   3
check_out RecParam "$ROOT/tests/records/RecParam.m1"   10
check_out FnParam  "$ROOT/tests/functions/FnParam.m1"  16

echo "  -- will+now conflict detection (W3 Item 2) --"
check_diag WillNowConflict "$ROOT/tests/conflict/WillNowConflict.m1" M1102 1
check_diag NoConflict      "$ROOT/tests/conflict/NoConflict.m1"      M1102 0

echo "  -- branch-aware soundness (W3 Item 3) --"
check_out CondNoFold   "$ROOT/tests/branch/CondNoFold.m1"   0
check_out StraightFold "$ROOT/tests/branch/StraightFold.m1" 1

echo "  -- type checker (Week 5) --"
check_diag   TcCond  "$ROOT/tests/typecheck/TcCond.m1"  M1200 1
check_diag   TcArith "$ROOT/tests/typecheck/TcArith.m1" M1201 1
check_diag   TcClean "$ROOT/tests/typecheck/TcClean.m1" M1200 0
check_out    TcClean "$ROOT/tests/typecheck/TcClean.m1" 6

echo "Done: $((pass + fail)) checks ran — $pass passed, $fail failed."
if [ "$fail" -ne 0 ]; then
    echo "FAILED CHECKS:$FAILED"
    echo "RESULT: FAIL"
    exit 1
fi
echo "RESULT: PASS"
