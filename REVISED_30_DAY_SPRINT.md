# REVISED 30-Day Sprint — Post-Discovery (2026-06-14)

**Major Finding:** The self-hosted compiler (`m1c.m0`) has almost no temporal language support (only token definitions; no parser, AST nodes, or codegen for `freeze`/`now`/`was`/`will`/`when`/`live`).

The original plan treated Phase Graph integration as the main task. **Reality:** We must first port the temporal frontend before the Phase Graph (or any real temporal semantics) can be integrated.

## New Primary Objective for Next 30 Days

Make the temporal language constructs actually exist and do something in the self-hosted compiler (`m1c.m0`):

- Parser can accept `live`, `freeze`, `was`, `will`, `when/then`, `now`.
- Basic AST nodes exist.
- Lowering can emit calls that exercise the existing runtime + Phase Graph C module.
- At least some temporal programs can be run through `m1c`.

---

## Revised 30-Day Breakdown

### Week 1 (Days 1–7): Discovery + Frontend Foundation (COMPLETED 2026-06-14)

- [x] Complete light exploration (reading m1c.m0 lexer/parser/codegen for temporal constructs).
- [x] Document the finding in `notes/discovery-summary.md` and `notes/phase-graph-analysis.md`.
- [x] Create planning docs: `REVISED_30_DAY_SPRINT.md`, `REVISED_PRIORITIES.md`.
- [x] Create concrete sketch in `notes/first-temporal-parser-sketch.md`.
- [x] Inject foundation code into m1c.m0 (pg_* wrappers, N_* constants, constructors, token constants).

### Week 2 (Days 8–14): Parser + AST Port

- [ ] Port parser rules for `set live x : T = e`, `freeze x`, `was x.Phase`, `will e`, `when c { ... }`, `now e`.
- [ ] Define corresponding AST node kinds in the self-hosted compiler (foundation done Week 1).
- [ ] Basic lowering that turns them into the same shapes the C bootstrap + Phase Graph expect.
- [ ] Add the first 4–5 of the "First 10 Phase Graph Tests" (adapted to what is now parsable).
- [ ] **Goal:** A non-trivial temporal program parses and lowers without immediate crash. Some `was` / `freeze` paths reach the Phase Graph externals.

### Week 3 (Days 15–21): Basic Codegen + Runtime Hookup + Self-Hosting Work

- [ ] Implement minimal codegen that emits calls to the `phase_graph_*` externals.
- [ ] Get a basic `now` example to at least run (even if re-check after mutation is still naive).
- [ ] Make progress on self-hosting stability (compiler must handle larger inputs).
- [ ] Regenerate some test outputs using the new paths.
- [ ] **Goal:** At least a few original temporal tests produce output when compiled with `m1c`.

### Week 4 (Days 22–30): Hardening, Tests, Documentation, Evidence

- [ ] Fill out more of the 10 Phase Graph tests.
- [ ] Ensure existing temporal tests still pass (or document why not).
- [ ] Update `paper/evidence/test-results.md` with new reality.
- [ ] Update `ROADMAP_v0.6.md` and sprint doc with actual progress.
- [ ] Write short public update (GitHub discussion) about the discovery and revised path.
- [ ] Decide on v0.6 scope realistically.

---

## Success Metrics (Revised)

By end of 30 days:

- [ ] Self-hosted compiler can parse and lower the five core temporal operators.
- [ ] At least some programs using `live` + `freeze` + `was` can be compiled by `m1c` and produce output.
- [ ] Much clearer picture of what a realistic v0.6 looks like.
- [ ] Discovery and revised plan are publicly documented.

---

## Next Immediate Action (Week 1 complete — 2026-06-14)

1. Create the Week 1 kickoff GitHub issue (use `.github/ISSUE_TEMPLATE/week1-kickoff-filled.md`).
2. Start implementing temporal frontend port in `src/m1/m1c.m0` using `notes/first-temporal-parser-sketch.md`.
3. Add thin pg_* wrapper functions + minimal emit stubs.
4. Test with m0c bootstrap on small temporal `.m1` snippets.
5. Update ROADMAP + evidence status as soon as first parsable temporal program works.

---

*This revised plan is more honest and will produce more credible progress than trying to integrate a Phase Graph that nothing is feeding yet.*
