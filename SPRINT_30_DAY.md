# M1 v0.6 — 30-Day Sprint Plan

**Focus:** Make the biggest credibility gap (Phase Graph) real, and fix the most embarrassing semantic bug (`now` re-check).

**Duration:** 30 calendar days (roughly 4 weeks of focused work, assuming ~15-20 hours/week).

**Primary Owner:** You (the maintainer)

---

## Week 1: Reconnaissance & Small Wins (Days 1–7)

**Goal:** Understand the current integration surface and ship 1-2 visible improvements.

### Day 1–2: Exploration
- Clone fresh and build the M0 bootstrap on your machine.
- Study the golden generated C files (from pre-cleanup tag if available, or regenerate some simple tests).
- Find every place where `phase_graph_*` externals are declared or called in `src/m1/m1c.m0`.
- Read the entire `src/m1/phase_graph.c` + `.h` and write a 1-page internal note on how it works.
- Identify the AST representation for `was`, `freeze`, `will`, and `now` in the self-hosted compiler.
- **Deliverable:** A short `notes/phase-graph-analysis.md`.

### Day 3–4: Small Ergonomics Win
- Implement **bare expression statements** (Q5).
  - Modify parser to allow expressions as statements.
  - Update codegen to discard the value.
  - Add a few tests.
- Run the existing temporal tests to make sure nothing broke.
- **Deliverable:** Bare expressions working + 3 new tests.

### Day 5–7: `now` Re-check (Start)
- Locate the code that handles `set` / assignment for live variables.
- Prototype: On every assignment to a variable that has active `now` constraints, emit a runtime check.
- Make the bank balance example from the README actually re-check the invariant after mutation.
- Write 2 new tests that would have passed before but now correctly catch violations.
- **Deliverable:** `now` re-checks after mutation for simple cases.

---

## Week 2: Phase Graph Wiring (Days 8–14)

**Goal:** Get the Phase Graph actually participating in compilation.

### Day 8–10: Wrapper Layer in M0
- Create a small set of M0 helper functions in `m1c.m0` that wrap the phase graph externals (e.g. `pg_record(var, phase)`, `pg_query(var, phase)`).
- Hook these into the lowering of `live` variable declarations.
- Hook `freeze` to call the corresponding phase graph function.
- **Deliverable:** Phase graph calls are emitted for `freeze` and basic phase recording.

### Day 11–14: `was` Query Integration
- Modify the codegen for `was x.Phase` expressions to call `phase_graph_query`.
- Add simple constant folding: if the query returns a known literal at compile time, replace the call with 0 or 1.
- Test with the existing `was` tests (`was_test.m1`, `was_never_test.m1`).
- Add 2–3 new tests that exercise phase recording across multiple statements.
- **Deliverable:** `was` queries use the real Phase Graph and fold when possible.

---

## Week 3: Self-Hosting & Hardening (Days 15–21)

**Goal:** Make the compiler more robust so you can actually use it on its own source.

### Day 15–17: Self-Hosting Investigation
- Reproduce the stack overflow when compiling `m1c.m0`.
- Profile / add simple stack usage logging in the interpreter.
- Try the easiest fix first: increase stack size for the M0 interpreter.
- If that fails, identify the deepest recursion paths (parser? checker? codegen?).

### Day 18–21: Self-Hosting Progress + `will` + `now` Conflict
- Land whatever self-hosting improvement you can (even partial: "compiles with --big-stack" or "compiles after splitting the file").
- Start basic `will` + `now` conflict detection using the Phase Graph state.
- Add a warning (not necessarily a hard error yet) when a contradictory pair is detected.
- **Deliverable:** Self-hosting improved + first conflict detection warning.

---

## Week 4: Polish, Tests, Documentation (Days 22–30)

### Day 22–25: Test Expansion & Evidence
- Write the "First 10 Phase Graph Tests" (see `FIRST_10_PHASE_GRAPH_TESTS.md`).
- Ensure all 13 temporal tests still pass with the integrated implementation.
- Regenerate some golden C outputs using the new compiler.
- Update `paper/evidence/test-results.md` with current status.

### Day 26–28: Tooling & DX
- Add a very basic `m1 repl` (even if minimal).
- Improve error messages for at least one temporal error.
- Make sure the Linux build of the M0 bootstrap works cleanly.

### Day 29–30: Documentation & Commit
- Update `README.md` "Known Limitations" section.
- Write a short "v0.6 Progress Update".
- Commit everything with clear messages.
- Push and create/update issues for remaining work.

---

## Daily/Weekly Rituals

- **Every day:** Run the temporal test subset (`tests/freeze`, `tests/now`, etc.) before ending work.
- **Every Friday:** Update this sprint doc with what actually got done vs. planned.
- **Mid-sprint (Day 15):** Re-evaluate — if Phase Graph integration is going slower than expected, narrow scope.

---

## Success Metrics for This 30 Days

- [ ] Phase Graph is being called from `m1c.m0` for `was`, `freeze`, and phase recording.
- [ ] At least some `was` queries are constant-folded at compile time by the real Phase Graph.
- [ ] `now` invariants are re-checked after mutation.
- [ ] Self-hosting is noticeably better (even if not perfect).
- [ ] Bare expressions work.
- [ ] You have a clear picture of what is still missing for a real v0.6 release.
