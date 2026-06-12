# M1 — A Language Where Time Is a Type

M1 is a programming language with temporal logic built into the syntax. Five
operators — `freeze`, `now`, `was`, `when`/`then`, `will` — let the compiler
and runtime enforce ordering: what must happen before what, what may never
change, what must eventually occur.

The most common bugs in AI-generated code are temporal: using a connection
before opening it, mutating state after it should be final, forgetting a
cleanup that was promised. In M1 those bugs are rejected — at compile time
where possible, at runtime otherwise — instead of being found in production.

```m1
world Account {
    do main() -> Int {
        set live balance : Int = 5000;

        /* Trigger: fires the moment the condition becomes true */
        set _ : Int = when balance > 10000 then {
            say("threshold crossed")
        };

        set _ : Int = balance = 15000;   /* <-- fires the trigger */

        /* Make it immutable from here on; later writes are errors */
        set _ : Int = freeze balance;
        0
    }
}
```

## The Five Temporal Operators

| Operator | Meaning | Enforced |
|----------|---------|----------|
| `freeze x` | `x` is immutable from this point on | compile time + runtime |
| `now x` | invariant: condition must hold now and after every mutation | compile time + runtime |
| `was x.Phase` | did `x` ever pass through this phase? | compile time (phase graph) |
| `when C then { … }` | trigger: runs the moment `C` becomes true | runtime |
| `will C` | commitment: `C` must eventually hold | runtime |

Live values are tracked through a phase graph; triggers and commitments are
checked on every mutation. The `was` operator compiles to a constant when the
answer is statically known.

## Install (Build from Source)

**Requirements:** Windows, clang on PATH.

```powershell
git clone https://github.com/RayAKaan/m1
cd m1

# Step 1 — build the M0 bootstrap compiler
cd src
build.bat                          # produces m0c.exe

# Step 2 — build the m1 driver
clang -std=gnu11 -o m1\m1.exe m1.c m1\m0_runtime.c
cd ..
```

The `m1` driver is now at `src\m1\m1.exe`. Either add it to your PATH or
invoke it by full path.

## Usage

```text
m1 run <file.m1>       Compile and run
m1 build <file.m1>     Compile to executable
m1 check <file.m1>     Check syntax only
m1 version             Print version
```

## Run the Test Suite

```powershell
tests\build\run_tests.ps1
```

## Language Tour

### Records

```m1
world Records {
    shape Point = { x : Int, y : Int }

    do make_point(x : Int, y : Int) -> Point {
        set p : Point = { x = x, y = y };
        p
    }

    do point_sum(p : Point) -> Int { p.x + p.y }

    do main() -> Int {
        set p : Point = make_point(3, 7);
        say(int_to_string(point_sum(p)))
    }
}
```

### Sum Types (Enums) with Pattern Matching

```m1
world Match {
    shape Option = | Some(Int) | None

    do classify(n : Int) -> Int {
        pick n {
            0 -> 1;
            _ -> n * 2;
        }
    }
}
```

### Conditionals

```m1
do abs(n : Int) -> Int {
    if n < 0 { 0 - n } else { n }
}
```

### Temporal Examples

**`freeze`:** make a variable read-only.

```m1
set live x : Int = 42;
set _ : Int = freeze x;
set _ : Int = x = 10;    /* compile-time error */
```

**`now`:** assert an invariant checked on every mutation.

```m1
set live balance : Int = 1000;
set _ : Int = now balance >= 0;          /* OK */
set _ : Int = balance = balance - 2000;  /* runtime error: invariant violated */
```

**`was`:** query phase history.

```m1
set live token : Int = 0;                /* 0 = Issued */
set _ : Int = token = 1;                 /* 1 = Used */
set _ : Int = say(int_to_string(was token.Used));  /* prints 1 */
```

**`will`:** register a commitment that must be satisfied by return.

```m1
set live order : Int = 0;
set _ : Int = will order == 1;           /* must become 1 */
set _ : Int = order = 1;                 /* satisfies the commitment */
```

## Standard Library

No imports or `external` declarations needed — the `m1` driver injects these
automatically. (When using `m1c.exe` directly, use `inject_test.py` or the
test runner.)

| Group | Functions |
|-------|-----------|
| **Output** | `say`, `show` |
| **Strings** | `string_len`, `string_concat`, `int_to_string`, `string_to_int`, `char_at`, `substring`, `string_split` |
| **Files** | `read_file`, `write_file` |
| **Input** | `read_line`, `read_int` |
| **Vectors** | `vector_new`, `vector_push`, `vector_get`, `vector_set`, `vector_len`, `vector_sort`, `vector_get_str` |
| **Maps** | `map_new`, `map_set`, `map_get`, `map_has`, `map_len` |
| **Matrices** | `matrix_new`, `matrix_get`, `matrix_set` |
| **Floats** | `float_of_int`, `float_add`, `float_sub`, `float_mul`, `float_div`, `float_lt`, `float_gt`, `float_eq`, `float_to_string`, `string_to_float` |

## Architecture

```
src/          C implementation: lexer → parser → checker → codegen (m0c.exe)
src/m1/       Self-hosted M1 compiler (m1c.exe) + runtime (m0_runtime.c)
src/m1.c      m1 driver (stdlib injection, compilation orchestration)
spec/         Formal spec: PEG grammar, types, effects, reduction, evaluation order
stdlib/       Standard library modules (std.m1, string.m1, vector.m1)
tests/        Feature-organized suite: freeze/ now/ was/ when/ will/
paper/        Research paper + frozen evidence (paper/evidence/)
```

**Bootstrap chain:** `m0c.exe` (C) compiles `.m0` → `m1c.exe` (M0) compiles `.m1`
to C → clang links against `m0_runtime.c` → final executable.

## Status

**v0.5** — actively developed. 13/13 temporal-operator tests pass; 46/73 overall
([full results](paper/evidence/test-results.md)). Every paper claim maps to a
committed artifact in `paper/evidence/`, frozen at tag `paper-evidence`.

## What's Next

- Linear types
- Effect types
- Proposition verification (`m1 verify`)
- CI running the full suite on every push

## License

MIT. See [LICENSE](LICENSE).
