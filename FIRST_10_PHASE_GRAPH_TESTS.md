# First 10 Tests to Make Pass with Integrated Phase Graph

**Purpose:** Concrete, small tests that demonstrate the Phase Graph is actually wired in and providing value (especially constant folding for `was`).

These should be added to `tests/was/` or a new `tests/phase_graph/` directory.

---

### Test 1: Basic `was` after linear phases (should fold)

```m1
world WasBasic {
    do main() -> Int {
        set live token : Int = 0;           -- phase "issued"
        set _ : Int = token = 1;            -- phase "used"
        set _ : Int = say(int_to_string(was token.Used));
        0
    }
}
```
**Expected:** Prints `1`. Ideally `was` is folded to literal `1` in generated C.

---

### Test 2: `was` on never-reached phase (should fold to 0)

```m1
world WasNever {
    do main() -> Int {
        set live x : Int = 42;
        set _ : Int = freeze x;
        set _ : Int = say(int_to_string(was x.Used));  -- never went through "Used"
        0
    }
}
```
**Expected:** Prints `0`.

---

### Test 3: `was` before any transition

```m1
world WasBefore {
    do main() -> Int {
        set live x : Int = 0;
        set _ : Int = say(int_to_string(was x.Live));  -- should be true (current phase)
        0
    }
}
```
**Expected:** Prints `1`.

---

### Test 4: `was` after freeze (phase should be stable)

```m1
world WasAfterFreeze {
    do main() -> Int {
        set live x : Int = 7;
        set _ : Int = freeze x;
        set _ : Int = say(int_to_string(was x.Live));
        0
    }
}
```
**Expected:** Prints `1` (frozen variables keep their last phase).

---

### Test 5: Multiple variables, independent phases

```m1
world WasMulti {
    do main() -> Int {
        set live a : Int = 0;
        set live b : Int = 10;
        set _ : Int = a = 1;
        set _ : Int = say(int_to_string(was a.Used));
        set _ : Int = say(int_to_string(was b.Used));  -- should be 0
        0
    }
}
```
**Expected:** Prints `1` then `0`.

---

### Test 6: `was` inside a conditional (conservative result expected)

```m1
world WasConditional {
    do main() -> Int {
        set live x : Int = 0;
        if 1 == 1 {
            set _ : Int = x = 1;
        }
        set _ : Int = say(int_to_string(was x.Used));
        0
    }
}
```
**Expected:** Returns `1` at runtime. For v0.6, accept either a runtime query or a conservative "maybe".

---

### Test 7: Freeze prevents further phase changes

```m1
world FreezeStopsPhases {
    do main() -> Int {
        set live x : Int = 0;
        set _ : Int = freeze x;
        set _ : Int = say(int_to_string(was x.Live));
        0
    }
}
```

---

### Test 8: `will` recording (basic)

```m1
world WillBasic {
    do main() -> Int {
        set live order : Int = 0;
        set _ : Int = will order == 1;
        set _ : Int = order = 1;
        0
    }
}
```
**Expected:** The `will` should be recorded and satisfied.

---

### Test 9: Simple `will` + `now` conflict (warning desired)

```m1
world WillNowConflict {
    do main() -> Int {
        set live x : Int = 0;
        set _ : Int = will x == 5;
        set _ : Int = now x < 3;     -- contradictory
        0
    }
}
```
**Expected for v0.6:** At minimum a warning during compilation.

---

### Test 10: Regression — all previous temporal tests still pass

Run the existing 13 temporal tests and assert they still produce the same output.

---

## Implementation Notes

- Add a comment in each test file: `-- This test is part of the "First 10 Phase Graph Tests".`
- Run these 10 tests after each significant integration step.
- When all 10 pass with the integrated Phase Graph (and outputs are folded), the core contribution is real.
