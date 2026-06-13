# Week 1 — Guided Exploration Checklist

**Goal:** Fill in `notes/phase-graph-analysis.md` by systematically exploring the Phase Graph C code and its integration surface in `m1c.m0`.

---

## Part A: Phase Graph C Implementation (`src/m1/phase_graph.c` + `.h`)

### A1. Data Structures (lines 37–59)
- [ ] `VarState` struct — understand each field: `var`, `phases[]`, `edges[]`, `terminal`, `cur_phase`, `has_cur`, `unknown`
- [ ] `PEdge` struct — simple from/to string pair
- [ ] Global `vars[MAX_VARS]` array — how many vars can be tracked? (MAX_VARS = 64)
- [ ] Limits: MAX_PHASES=16, MAX_EDGES=64 — are these enough for real programs?

### A2. Core Building Functions
- [ ] `var_index()` / `add_var()` (lines 64–81)
- [ ] `add_phase()` / `add_edge()` (lines 83–96)
- [ ] `extract_phase()` (lines 103–114) — how does it determine phase name from AST node? (N_NAME → string, N_INT → stringified integer, N_BOOL → "true"/"false", complex → NULL = unknown)

### A3. Branch Handling (Snapshot System)
- [ ] `snapshot_save()` / `snapshot_restore()` — heap-allocates VarState array
- [ ] `merge_state()` — how two branch states are unioned
- [ ] Key insight: IF, MATCH each snapshot, walk branches, then merge

### A4. AST Walker (`walk_node`, lines 193–355)
This is the heart. Understand every case:
- [ ] `N_SEQ` — walk left, walk right
- [ ] `N_LET` — registers variable, records initial phase, adds "live" phase
- [ ] `N_ASSIGN` — looks up variable, records new phase, adds edge from cur_phase
- [ ] `N_FREEZE` — sets `terminal = 1`
- [ ] `N_IF` — snapshots, walks both branches, merges
- [ ] `N_MATCH` — snapshots, walks all arms, merges
- [ ] `N_WHILE` / `N_FOR` — conservatively marks all vars as `unknown = 1`
- [ ] `N_WHEN`, `N_NOW`, `N_WILL` — just recurses into children
- [ ] `N_WAS` — skips (query, not mutation)

**Key question to answer:** Is this AST walker ever actually called? Who calls `phase_graph_build()`?

### A5. Query Functions
- [ ] `phase_graph_query()` (lines 545–592) — DFS from start nodes, looking for target phase
- [ ] Special case: `"live"` phase returns 1 if `has_cur` is true
- [ ] Returns: 1 (found), 0 (definitely not found, terminal), -1 (unknown / inconclusive)
- [ ] `phase_graph_will_query()` (lines 465–504) — also detects duplicate will + now-will conflicts
- [ ] `phase_graph_will_check()` (lines 509–532) — for `now` declarations, detects now-will conflicts

### A6. FFI Wrappers (lines 597–622)
- [ ] `phase_graph_record()` — calls `add_var()` + `extract_phase` + records transition
- [ ] `phase_graph_freeze()` — calls `add_var()` + sets `terminal = 1`
- [ ] `phase_graph_init()` — resets state, calls `phase_graph_build()` with body node

---

## Part B: Self-Hosted Compiler (`src/m1/m1c.m0`)

### B1. Declaration Sites (already found)
- [ ] Lines 19–23: externals are declared
- [ ] **Critical finding: Are these externals ever called?** (Spoiler: grep shows declarations only — no actual calls in `m1c.m0`)

### B2. Current Temporal Keyword Handling
- [ ] How does the parser/lexer tokenize `freeze`, `now`, `was`, `when`, `will`? → lexer.m0
- [ ] What AST node types are emitted for each? (N_FREEZE, N_WAS, N_NOW, N_WHEN, N_WILL)
- [ ] How does the **code generator** currently lower each temporal keyword?
  - Look for: `codegen` functions or AST-to-C emission
  - How is `freeze` currently emitted? Is `freeze_var()` called in generated C?
  - How is `was` currently emitted? Is there a runtime scan or hardcoded result?

### B3. Codegen Location
- [ ] Find the codegen pass in `m1c.m0` — where does it walk the AST and emit C?
- [ ] For each temporal node type, what C code is currently emitted?
- [ ] Where would you insert calls to `phase_graph_record()` during assignment codegen?
- [ ] Where would you insert calls to `phase_graph_freeze()` during freeze codegen?
- [ ] Where would you replace the current `was` emission with `phase_graph_query()` + constant folding?

### B4. Test Files to Read
- [ ] Find a simple `was` test in `tests/was/` — what does the golden C output look like?
- [ ] Find a `freeze` test — what C does it generate?
- [ ] Find a `now` test — what C does it generate?
- [ ] Compare: what would these look like WITH the Phase Graph integration?

---

## Part C: Gap Analysis (fill as you go)

- [ ] What is the **exact** integration gap between C Phase Graph and m1c.m0?
- [ ] What is the simplest possible first integration step?
- [ ] What is the risk that `phase_graph_build()` (which walks the C AST) won't work on the M0 AST representation?
- [ ] How does `m1c.exe` currently link against `phase_graph.c`? (Check build.bat or Makefile)
- [ ] If you add calls to `phase_graph_record/freeze/query` in the M0 codegen, does the runtime (m0_runtime.c) already have these symbols linked?

---

## Part D: Deliverable

By end of Day 2, your `notes/phase-graph-analysis.md` should have:
- [ ] All sections filled with your findings (even rough notes are fine)
- [ ] At least 3 clear "integration points" identified in the table
- [ ] At least 2 "next steps" checked off or added

---

**Quick reference: Already confirmed findings to save you time:**

1. `phase_graph.c` has a complete, working AST walker (`walk_node`) that builds the Phase Graph for: N_LET, N_ASSIGN, N_FREEZE, N_IF, N_MATCH, N_WHILE, N_FOR, N_WHEN, N_NOW, N_WILL, N_WAS.
2. `phase_graph_query()` returns 1/0/-1 via DFS — already handles `"live"` special case.
3. `phase_graph_will_query()` and `phase_graph_will_check()` already implement will-will and will-now conflict detection.
4. `m1c.m0` declares all 5 externals (lines 19–23) but **never calls them** — zero usage in codegen.
5. The Phase Graph C code is called via `phase_graph_build(body_node)` which needs an AST root — this is the C AST format, not the M0 AST format. This is likely the biggest integration challenge.
