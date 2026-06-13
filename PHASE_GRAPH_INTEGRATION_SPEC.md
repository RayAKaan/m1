# Phase Graph Integration Technical Spec

**Target:** v0.6 "Credible Prototype"
**Document Status:** Draft (2026-06-13)

---

## 1. Current State

### 1.1 Standalone Phase Graph (Already Exists)
**Location:** `src/m1/phase_graph.c` + `phase_graph.h` (~637 lines)

**Provides:**
- `phase_graph_init()`
- `phase_graph_record(var, phase)`
- `phase_graph_freeze(var)`
- `phase_graph_query(var, phase)` → 0/1
- `phase_graph_will_check(var, phase)`
- Supporting functions for building and querying the graph

The C module is mature enough that the golden evidence relies on it for correct `was` folding.

### 1.2 Self-Hosted Compiler Surface
In `src/m1/m1c.m0` the following externals are already declared:

```m0
external "phase_graph_init"       : () -> Int
external "phase_graph_record"     : String -> String -> Int
external "phase_graph_freeze"     : String -> Int
external "phase_graph_query"      : String -> String -> Int
external "phase_graph_will_check" : String -> String -> Int
```

However, these are not meaningfully used by the type checker or code generator yet.

### 1.3 Current Temporal Implementation (Ad-hoc)
Most temporal behavior today is implemented directly in the code generator of `m1c.m0`. This produces the correct behavior for many tests, but:
- Does not use the Phase Graph for static folding of `was`.
- Does not have a unified live-variable phase tracking mechanism.
- Makes it hard to implement advanced features like `will` + `now` conflict detection.

---

## 2. Integration Architecture (Proposed)

### 2.1 High-Level Flow

```
Source with temporal operators
         │
         ▼
Parser / AST (already has N_FREEZE, N_WAS, N_WILL, N_NOW, etc.)
         │
         ▼
Checker / Live Variable Analysis
         │
         +---> Phase Graph recording (new)
         │
         ▼
Code Generator
         │
         +---> Emit calls to phase_graph_* wrappers (new)
         +---> Use phase_graph_query results for constant folding (new)
         │
         ▼
Generated C (with real Phase Graph calls)
```

### 2.2 Key Components to Build in M0

**Phase Graph Wrapper Module** (new or inside `m1c.m0`)
Thin, safe M0 functions that call the externals:
```m0
fn pg_init() -> Int { phase_graph_init() }
fn pg_record(var : String, phase : String) -> Int { phase_graph_record(var, phase) }
fn pg_freeze(var : String) -> Int { phase_graph_freeze(var) }
fn pg_was(var : String, phase : String) -> Int { phase_graph_query(var, phase) }
```

**Live Variable Phase Tracker** (inside checker or a new pass)
- Maintains current phase for each live variable.
- On declaration of a live var → record initial phase (e.g. `"live"`).
- On assignment → record new phase if applicable.
- On freeze → call `pg_freeze`.
- On `will` → call appropriate will tracking.

**Constant Folding for `was`**
When generating code for `was x.Phase`:
1. Call `pg_was(x, "Phase")`
2. If the result is known at compile time, emit the literal instead of a runtime call.

**Conflict Detection Hook** (for `will` + `now`)
After recording a `will`, check against active `now` constraints using Phase Graph state.

---

## 3. Suggested Call Sites in `m1c.m0`

Look for these areas in the self-hosted compiler:
- Variable declaration lowering (especially `live` variables)
- Assignment / `set` handling
- Expression lowering for `was`, `freeze`, `will`, `now`
- Function entry / exit (for `will` return guards)
- Block / sequence handling (to maintain phase state across statements)

---

## 4. Minimal Viable Integration for v0.6

Minimum that moves the needle:
- `freeze x` → calls `phase_graph_freeze`
- Assignment to live variables → calls `phase_graph_record`
- `was x.Phase` → calls `phase_graph_query` and uses the result (with constant folding)
- Basic `will` recording
- At least one place where `will` + `now` conflict produces a warning

Everything else (advanced folding, interprocedural, etc.) → M2.

---

## 5. Testing Strategy

See `FIRST_10_PHASE_GRAPH_TESTS.md`.

Key test categories:
- `was` folding on simple linear code
- `was` after `freeze`
- `was` that should remain dynamic
- `now` + mutation (cross-check with the separate `now` fix)
- Conflict detection between `will` and `now`

---

## 6. Risks & Mitigations

| Risk | Mitigation |
|------|------------|
| Interpreter stack blowup from many Phase Graph calls | Keep wrapper layer very thin. Consider batching recordings. |
| Phase names inconsistent between C and M0 | Define canonical phase names early (`"live"`, `"frozen"`, etc.) and document them. |
| Keeping C and M0 versions in sync | Treat C version as reference implementation for v0.6. |

---

## 7. Open Questions

1. Should phase names be user-visible strings or internal integers?
2. Do we want user-defined phases beyond built-in ones in v0.6?
3. How to handle phases across function calls (be conservative for now)?

---

## 8. Next Actions (Immediate)

1. Create `notes/phase-graph-analysis.md` with findings from reading the C code.
2. Add a new file or section in `m1c.m0` for the Phase Graph wrapper functions.
3. Pick one simple test (e.g. `was_test.m1`) and manually instrument it to call the phase graph externals.
4. Iterate until `was` queries start returning useful values from the real Phase Graph.
