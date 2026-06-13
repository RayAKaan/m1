---
name: "Week 1 Kickoff — Phase Graph Exploration (FILLED 2026-06-14)"
about: "Track Week 1 exploration and reconnaissance for Phase Graph integration (v0.6). This is the completed version of the template for direct use when creating the GitHub issue."
title: "[Week 1] Phase Graph Exploration Progress + Major Discovery: Temporal Frontend Missing from m1c.m0"
labels: week-1, phase-graph, v0.6, exploration, discovery
---

## Week 1 Goal

Understand the current state of the standalone C Phase Graph and identify exactly where (and why) it is not yet wired into `m1c.m0`.

**Focus files:**
- `src/m1/phase_graph.c` + `.h`
- `src/m1/m1c.m0`
- `notes/phase-graph-analysis.md`
- `notes/exploration-checklist.md`
- `notes/discovery-summary.md`

---

## Progress Log

### Part A: C Phase Graph Analysis

- [x] Read `phase_graph.h` and `phase_graph.c` (full source; 637 lines total).
- [x] Summarized key data structures and functions in `notes/phase-graph-analysis.md`.

**Key findings:**
- `VarState` (64 vars max): `phases[16]`, `edges[64]`, `cur_phase`, `terminal`, `has_cur`, `unknown`.
- Full public API: `init`, `record(var,phase)`, `freeze(var)`, `query(var,phase) → 0/1/-1`, `will_check`, `will_query`.
- Internal: recursive `walk_node` on N_FREEZE/N_WAS/N_NOW/N_WILL/N_WHEN/N_LIVE (externs from C bootstrap), snapshot/merge for IF/MATCH, DFS reachability for `was`, commitment tracking for now/will conflicts (Q3).
- Used to generate all golden evidence in `paper/evidence/` (via C bootstrap).
- **Complete enough to support the claims in the paper for simple cases.**

### Part B: m1c.m0 Inspection

- [x] Searched for all `phase_graph_*` declarations and calls (multiple greps).
- [x] Analyzed how `live`, `freeze`, `was`, `will`, `now` are currently handled.

**Key finding (confirmed with exact output):**
- All 5 externals are declared (`m1c.m0` lines 19-23) but **none** are called in the main compilation logic (parser, checker, codegen). Grep for "phase_graph" returns only the 5 declaration lines.

**Deeper finding: Temporal language support is almost entirely absent from the self-hosted compiler:**
- Lexer (`lexer.m0`): Tokens exist (`TkFreeze`, `TkNow`, `TkWwas`, `TkWhen`, `TkWill`, `TkLive`).
- `m1c.m0` (1098 lines): **No parser productions** for any temporal construct in `parse_atom` / `parse_decl` / `parse_expr`.
- **No AST node kinds** (`N_FREEZE`, `N_WAS`, `N_WILL`, `N_NOW`, `N_LIVE`, `N_WHEN` missing; only up to `N_WHILE`).
- **No lowering or codegen paths.**
- **No phase tracking state at all.**
- Only the C bootstrap (`src/codegen.c`, `src/parser.c`, `src/m1/phase_graph.c`) has the real implementation.
- All 13/13 temporal tests in `paper/evidence/test-results.md` were produced by the C bootstrap, **not** `m1c.m0`.

### Part C: Gap Analysis

- [x] Identified best insertion points for Phase Graph calls.
- [x] Started thinking about M0 wrapper layer design.

**Recommended thin wrappers:**
```
fn pg_init() -> Int { phase_graph_init() }
fn pg_record(v: String, p: String) -> Int { phase_graph_record(v, p) }
fn pg_freeze(v: String) -> Int { phase_graph_freeze(v) }
fn pg_query(v: String, p: String) -> Int { phase_graph_query(v, p) }
fn pg_will_check(v: String, p: String) -> Int { phase_graph_will_check(v, p) }
```

**Constant folding:** Call `pg_query` in `was` codegen; emit literal if 0/1.

**Major risk:** Self-host stack overflow (already 0xC00000FD on 1098 lines) will get worse with added parser/AST/codegen code.

---

## Deliverables This Week (achieved)

- [x] `notes/phase-graph-analysis.md` — sections 1–7 filled with C details + M0 gap.
- [x] `notes/exploration-checklist.md` — completed with all grep outputs + answers.
- [x] `notes/discovery-summary.md` — summary of the major finding.
- [x] `notes/first-temporal-parser-sketch.md` — concrete starter code for Week 2.
- [x] `REVISED_30_DAY_SPRINT.md` — updated sprint plan.
- [x] `REVISED_PRIORITIES.md` — updated priority order.
- [x] `src/m1/m1c.m0` — injected foundation code (pg_* wrappers, N_* constants, constructors, token constants).

---

## Blockers / Questions for Discussion

- Self-hosting stability must be addressed in parallel (or use hybrid m0c for large files during port).
- Exact AST representation for `set live x : T = e` (new `N_LIVE` node?).
- Timeline adjustment for v0.6 (this discovery pushes realistic "credible prototype" out).

---

**References (in repo):**
- `ROADMAP_v0.6.md` (has "Major Discovery (2026-06-13)" section)
- `REVISED_30_DAY_SPRINT.md`
- `REVISED_PRIORITIES.md`
- `notes/discovery-summary.md`
- `notes/first-temporal-parser-sketch.md`
- `paper/evidence/test-results.md` (13/13 with explicit gaps listed)

**Status at end of Week 1:** Exploration complete. Pivot to Tier 1 temporal frontend port (live + freeze first). All artifacts ready for real repo.
