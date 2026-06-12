# Codegen Patterns

Extracted from golden `_test_*.c` files in `src/m1/`. Line numbers reference specific golden files.

## 1. File Prologue (every golden C file)

Every file starts with:
```c
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* runtime function declarations */
```

Then two blocks of declarations:
1. **Primary wrappers** (named `m0_print`, `m0_println`, `say`, `show`, etc. — with parameter names)
2. **FFI-style declarations** (named `m0_print`, `m0_string_len`, etc. — parameter types only, no names)

Both blocks are always emitted regardless of which functions are actually used.

## 2. Runtime Wrapper Functions (every file)

The middle section contains wrapper functions for every runtime function. Each wrapper follows this exact pattern:
```c
char* string_concat(char* a, char* b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m0_string_concat(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
```

Key elements:
- `_will_0` through `_will_9` = ten will-satisfaction counters declared per function
- `_m1_ret` = typed return accumulator (type matches function return type)
- Expression wrapped in parens: `(m0_string_concat(a, b))`
- `goto __m1_return` for unified return point
- No `_will_` counter check before return (only user functions have this)

## 3. Variable Declarations

```c
int64_t x;           // for each user variable
int64_t _;           // underscore temp variable for expression sequencing
int _m1_ret = 0;     // return accumulator (int for main, typed per function)
```

All variables declared before the first statement in the function body.

## 4. `freeze x` — Zero Runtime Code

**Golden file**: `_test_freeze_test.c` (398 lines)
**Search result**: No match for "freeze" anywhere in the file.

`freeze x` in M1 source generates **NO runtime C code**. Not even a comment. The variable `x` is just declared like any other variable. The compile-time check (reject assignment to frozen variable) happens in the compiler, not at runtime.

**Status**: ✅ Matches Q4 (freeze is purely compile-time)

## 5. `now P` — Invariant Assertion (ONE-TIME check only)

**Golden file**: `_test_now_test.c:398`

Source:
```
set balance : int = 1000
now balance >= 0
set balance : int = balance - 500
say(int_to_string(balance))
```

Generated C:
```c
_m1_ret = (balance = 1000,
  _ = ({ if (!((balance >= 0))) {
    fprintf(stderr, "H:/.../_inj_now_test.m1:84:23: error: [M1103] 'now' assertion violated: (invariant)\n");
    exit(1);
  } 0; }),
  _ = say(int_to_string(balance)),
  _ = ({ (balance = (balance - 500)); balance; }),
  say(int_to_string(balance)));
```

Pattern:
```c
_ = ({ if (!((CONDITION))) {
  fprintf(stderr, "... [M1103] 'now' assertion violated: (invariant)\\n");
  exit(1);
} 0; })
```

**Key observation**: The now check is emitted ONCE at the declaration point. After `balance = balance - 500`, there is NO re-check of `(balance >= 0)`. This is the comma-operator sequence:
1. `balance = 1000` (assignment)
2. `_ = now_check` (one-time assertion)
3. `_ = say(...)` (print)
4. `_ = ({ (balance = balance - 500); balance; })` (mutation — NO re-check!)
5. `say(...)` (print)

**GAP per Q1**: `now` SHOULD be a continuous temporal invariant (□P), re-checked after every mutation to dependent variables. The golden output does NOT emit re-checks. The new compiler MUST add re-checks after every assignment to variables used in the `now` condition.

## 6. `was x.phase` — Phase Graph Constant Folding

**Golden file**: `_test_was_test.c:398`

Source (was_test.m1):
```
let x = 42
set _ = say(int_to_string(was x.phase))
```

Generated C:
```c
_m1_ret = (x = 42, _ = 0, _ = say(int_to_string(1)), 0);
```

Key observations:
- `was x.phase` folds to **literal `1`** (or `0` for `was_never_test.m1`)
- No `phase_scan()` runtime call emitted
- The `_ = 0` is a placeholder for the was expression in the source
- The actual value `1` is directly passed to `int_to_string`

Pattern:
```
was x.phase  →  LITERAL (1 or 0)  // fully resolved at compile time by Phase Graph
```

**Status**: ✅ Matches Q3 (Phase Graph is standalone C module, 488 lines, not yet integrated into m1c.m0)

## 7. `when P then { B }` — Trigger with Re-check After Mutation

**Golden file**: `_test_when_test.c:396`

Source:
```
let balance = 5000
when balance > 10000 then say(int_to_string(balance))
set balance = 15000
```

Generated C:
```c
_m1_ret = (balance = 5000,
  _ = ({ if ((balance > 10000)) { say(int_to_string(balance)); } 0; }),
  _ = ({ (balance = 15000); if ((balance > 10000)) { say(int_to_string(balance)); } balance; }),
  0);
```

Patterns:

**Initial trigger check** (at declaration point):
```c
_ = ({ if ((CONDITION)) { BODY; } 0; })
```

**Re-check after assignment to watched variable**:
```c
({ (VARIABLE = NEWVAL); if ((CONDITION)) { BODY; } VARIABLE; })
```

The re-check is embedded in the assignment expression using comma operator + GNU statement expression `({...})`. The variable's new value is the result of the outer expression.

Key observations:
- When IS re-checked after mutation to the watched variable ✅ (matches spec)
- The check runs regardless of scope depth ✅ (matches Q2)
- No `_when_` prefix or named tracking variables — the check is purely inline
- The body is always `say(...)` or `show(...)` in examples

## 8. `will P` — Future Commitment with Return Check

**Golden file**: `_test_will_test.c:396-399`

Source:
```
let order = 0
will order == 1
set order = 1
say(int_to_string(order))
```

Generated C (main function ending):
```c
  _m1_ret = (order = 0,
    _ = ({ if ((order == 1)) { _will_0 = 1; } 0; }),
    _ = ({ (order = 1); if ((order == 1)) { _will_0 = 1; } order; }),
    say(int_to_string(order)));
  goto __m1_return;
__m1_return:
  if (!_will_0) {
    fprintf(stderr, "H:/.../_inj_will_test.m1:81:23: error: [M1102] 'will' commitment violated\n");
    exit(1);
  }
  return _m1_ret;
```

Pattern:

**Will counter declaration** (at function top):
```c
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
```

**Satisfaction marking** (inline in expression):
```c
_ = ({ if ((CONDITION)) { _will_N = 1; } 0; })
```

**Return guard** (before `return`):
```c
if (!_will_N) { fprintf(stderr, "... [M1102] 'will' commitment violated\n"); exit(1); }
```

Key observations:
- Uses 10 pre-declared counters (`_will_0` through `_will_9`)
- Counters are per-function, emitted for every function (even trivial wrappers)
- The return guard fires BEFORE the actual return statement
- Error code `M1102` for will violations

## 9. Function Naming

Functions from modules are prefixed with `module__`:
- Source file: `tests/module/lib.m1` → functions named `lib__functionname`
- Source file: `tests/module/bank.m1` → functions named `bank__withdraw`
- Global functions (no module): no prefix

## 10. Main Function

```c
int main(void) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t balance;
int64_t _;
  int _m1_ret = 0;
  _m1_ret = (...);
  goto __m1_return;
__m1_return:
  if (!_will_N) { ... }  // will check, if present
  return _m1_ret;
}
```

Note: `_m1_ret` is `int` in main but typed per function (e.g., `char*` for string-returning functions).

## 11. Return Statements (user-defined functions)

User functions use `return expr` which generates:
```c
_m1_ret = (EXPR);
goto __m1_return;
```

The `__m1_return` label is always the unified exit point. The `_will_N` check goes before `return _m1_ret`, not before `goto __m1_return`.

## 12. Expression Statement Wrapping

Every expression statement (including bare expressions) is wrapped with `set _ : Type =` in the source. The generated C wraps each statement in the comma-expression chain:
```c
_m1_ret = (expr1, _ = (expr2), expr3, ...);
```

The underscore variable `_` captures discarded results.

**GAP per Q5**: Bare expressions should be valid statements WITHOUT requiring `set _ : Type =`. The golden outputs always use the wrapper form.

## 13. Evaluation Order

**Spec order** (from `spec/07-evaluation-order.md`):
1. Phase history recording → 2. `when` trigger evaluation → 3. `will` satisfaction marking → 4. `now` invariant re-verification

**Actual golden output order**:
1. `when` trigger (initial + re-check after assign) — inline in expression
2. `will` satisfaction marking — inline in expression
3. `will` return guard — before return statement
4. `now` — ONE check at declaration, NO re-checks

**Discrepancies**:
| Aspect | Golden Output | Spec / Q1-Q6 Decision |
|--------|---------------|----------------------|
| Phase history recording | Missing entirely (was uses constant folding) | Should record phase history before when/will/now |
| `now` re-check | One-time at declaration | Should re-check after every mutation to dependent vars (Q1) |
| `when` scope filtering | None — fires at any depth | ✅ Matches Q2 |
| `will`+`now` conflict | Not detected | Should produce Phase Graph warning at compile time (Q3) |

## 14. Error Codes in Golden Outputs

| Code | Location | Meaning |
|------|----------|---------|
| `M1103` | now_test.c | `now` assertion violated at runtime |
| `M1102` | will_test.c | `will` commitment violated at return |
| `M1003` | (compile-time only) | `freeze` assignment-after-freeze rejected |

**Gap per Q6**: Error codes should use unified M10xx (compile-time), M11xx (runtime), M2xxx (C analyzer). Golden outputs already use M11xx for runtime errors. Need to verify M10xx range for compile-time errors.

## 15. Runtime Function Declarations (complete list)

```c
/* Primary wrappers (parameterized) */
int64_t m0_print(char* s);
int64_t m0_println(char* s);
int64_t say(char* s);
int64_t show(char* s);
char* string_concat(char* a, char* b);
char* int_to_string(int64_t n);
int64_t string_len(char* s);
int64_t string_to_int(char* s);
char* read_file(char* path);
int64_t write_file(char* path, char* content);
int64_t vector_new(void);
int64_t vector_push(int64_t v, int64_t x);
int64_t vector_get(int64_t v, int64_t i);
int64_t vector_set(int64_t v, int64_t i, int64_t x);
int64_t vector_len(int64_t v);
int64_t vector_sort(int64_t v);
char* read_line(void);
int64_t read_int(void);
int64_t char_at(char* s, int64_t i);
char* substring(char* s, int64_t start, int64_t len);
int64_t string_split(char* s, char* delim);
char* vector_get_str(int64_t v, int64_t i);
int64_t map_new(void);
int64_t map_set(int64_t m, int64_t k, int64_t v);
int64_t map_get(int64_t m, int64_t k);
int64_t map_has(int64_t m, int64_t k);
int64_t map_len(int64_t m);
int64_t matrix_new(int64_t rows, int64_t cols);
int64_t matrix_get(int64_t m, int64_t r, int64_t c);
int64_t matrix_set(int64_t m, int64_t r, int64_t c, int64_t v);
int64_t float_of_int(int64_t n);
int64_t float_add(int64_t a, int64_t b);
int64_t float_sub(int64_t a, int64_t b);
int64_t float_mul(int64_t a, int64_t b);
int64_t float_div(int64_t a, int64_t b);
int64_t float_lt(int64_t a, int64_t b);
int64_t float_gt(int64_t a, int64_t b);
int64_t float_eq(int64_t a, int64_t b);
char* float_to_string(int64_t f);
int64_t string_to_float(char* s);

/* FFI-style declarations (anonymous params) */
int64_t m0_print(char*);
int64_t m0_println(char*);
int64_t m0_string_len(char*);
char* m0_string_concat(char*, char*);
char* m0_int_to_string(int64_t);
int64_t m0_string_to_int(char*);
char* m0_read_file(char*);
int64_t m0_write_file(char*, char*);
int64_t m1_vector_new(void);
int64_t m1_vector_push(int64_t, int64_t);
int64_t m1_vector_get(int64_t, int64_t);
int64_t m1_vector_set(int64_t, int64_t, int64_t);
int64_t m1_vector_len(int64_t);
int64_t m1_vector_sort(int64_t);
char* m1_read_line(void);
int64_t m1_read_int(void);
int64_t m1_char_at(char*, int64_t);
char* m1_substring(char*, int64_t, int64_t);
int64_t m1_string_split(char*, char*);
char* m1_vector_get_str(int64_t, int64_t);
int64_t m1_map_new(void);
int64_t m1_map_set(int64_t, int64_t, int64_t);
int64_t m1_map_get(int64_t, int64_t);
int64_t m1_map_has(int64_t, int64_t);
int64_t m1_map_len(int64_t);
int64_t m1_matrix_new(int64_t, int64_t);
int64_t m1_matrix_get(int64_t, int64_t, int64_t);
int64_t m1_matrix_set(int64_t, int64_t, int64_t, int64_t);
int64_t m1_float_of_int(int64_t);
int64_t m1_float_add(int64_t, int64_t);
int64_t m1_float_sub(int64_t, int64_t);
int64_t m1_float_mul(int64_t, int64_t);
int64_t m1_float_div(int64_t, int64_t);
int64_t m1_float_lt(int64_t, int64_t);
int64_t m1_float_gt(int64_t, int64_t);
int64_t m1_float_eq(int64_t, int64_t);
char* m1_float_to_string(int64_t);
int64_t m1_string_to_float(char*);
```

## 16. Lexer FFI Interface

The M1 lexer (`src/m1/lexer.m0`) uses these FFI external functions:

| Function | Signature | Purpose |
|----------|-----------|---------|
| `m0_char_at` | `(string, int) → int` | Get character at index in a string |
| `m0_substr` | `(string, int, int) → string` | Extract substring |
| `m0_string_eq` | `(string, string) → bool` | String equality comparison |
| `m0_string_len` | `(string) → int` | String length |
| `m0_print` | `(string) → int` | Print string to stdout |
| `m0_print_int` | `(int) → int` | Print integer to stdout |
| `m0_print_char` | `(int) → int` | Print character to stdout |

Tokens are represented as a sum type `M1Tk` with constructors for each keyword, plus:
- `TK_IDENT(string)` — identifier
- `TK_INT(int)` — integer literal
- `TK_STRING(string)` — string literal
- `EOF` — end of file

The `keyword_or_ident` function (lines 131-152 of `lexer.m0`) maps string tokens to typed tokens. **Currently only recognizes OLD keywords**: module, type, fn, let, match, if, else, true, false, external, not, forall, exists, mut, while.

**No temporal keywords are recognized.** The temporal tokens (freeze, now, was, when, will) plus new keywords (world→module, do→fn, set→let, pick→match, shape→type) must be added.

The M0 bootstrap lexer (`src/lexer.c`) has an even smaller keyword table.
