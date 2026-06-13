# Phase Graph Analysis Notes

**Date started:** 2026-06-14
**Author:** (fill in)

## 1. Current Phase Graph Implementation (C side)

- **File locations:** `src/m1/phase_graph.c` (622 lines), `src/m1/phase_graph.h` (15 lines)
- **Key data structures:**
  - `VarState` — tracks one variable: phases array (MAX_PHASES=16), edges array (MAX_EDGES=64), `cur_phase`, `terminal` (frozen), `has_cur`, `unknown`
  - `PEdge` — simple `from`/`to` string pair
  - `WillCommit` — for will/now conflict tracking
  - Global `vars[MAX_VARS=64]` array, static `var_count`
- **Main functions and their responsibilities:**
  - `phase_graph_init()` — zeros all state, resets commitments
  - `phase_graph_build(body_node)` — calls `init()` then `walk_node(body_node)` — walks entire function AST
  - `phase_graph_record(var, phase)` — adds var, records phase transition, updates `cur_phase`
  - `phase_graph_freeze(var)` — sets `terminal = 1`
  - `phase_graph_query(var, phase)` — DFS reachability via edges; returns 1 (found), 0 (definitely absent, terminal), -1 (unknown/inconclusive)
  - `phase_graph_will_check(var, phase)` — for `now` declarations, detects now-will conflicts
  - `phase_graph_will_query(var, phase)` — for `will` declarations, detects conflicts + duplicate will
- **How phases are represented internally:** Strings stored in `phases[16][64]`. Variable names are strings. Edges stored as string pairs. The "live" phase is special-cased.
- **How the graph is updated:**
  - `N_LET` → registers var, records initial value as phase, adds "live" phase
  - `N_ASSIGN` → records new phase, adds edge from `cur_phase` to new phase
  - `N_FREEZE` → sets `terminal = 1`
  - `N_IF` → saves snapshot, walks both branches, merges
  - `N_MATCH` → saves snapshot per arm, merges all
  - `N_WHILE/FOR` → marks all vars as `unknown = 1` (conservative)
  - `N_WHEN/N_NOW/N_WILL` → recurses into children (no graph change)
  - `N_WAS` → skipped (query, not mutation)
- **AST format expected:** Uses `N_*` constants (`N_FREEZE=13`, `N_WAS=14`, `N_WHEN=20`, `N_NOW=21`, `N_WILL=22`) defined in `m1c_out_raw.c` (C bootstrap format). Accesses AST via `m0_get(node, idx)` — expects node at slot 0, children at slots 3+.
- **Key observations / surprises:**
  - The C implementation is **complete** — it handles all temporal cases, branching, merging, will/now conflict detection, and DFS-based was queries.
  - It was used to generate the nice folded results in the paper evidence.
  - But it expects the **C bootstrap AST format** (N_FREEZE etc.), NOT the M0 AST format.

## 2. Current Usage in Self-Hosted Compiler (m1c.m0)

- **Where are the `phase_graph_*` externals declared?** Lines 19–23 of `m1c.m0` — all 5 are declared.
- **Are they called anywhere today?** **NO.** Grep shows zero calls to `phase_graph_record`, `phase_graph_query`, `phase_graph_init`, or `phase_graph_freeze` in `m1c.m0`. The externals are declared but completely unused.
- **How are `live`, `freeze`, `was`, `will`, `now` currently lowered in m1c.m0?** They are **not handled at all** in the self-hosted compiler:
  - `m1c.m0` defines AST node types (lines 80–102): `N_PROG`, `N_MOD`, `N_INT`, `N_STRING`, `N_BOOL`, `N_UNIT`, `N_NAME`, `N_BINARY`, `N_NOT`, `N_FIELD`, `N_CALL`, `N_LET`, `N_LAMBDA`, `N_MATCH`, `N_IF`, `N_RECORD`, `N_LIST`, `N_ASSIGN`, `N_WHILE` — **no temporal node types**
  - `m1c.m0` defines token kinds (lines 64–78): `TK_UNIT` through `TK_WHILE` — **no temporal tokens** (no TkFreeze, TkNow, TkWwas, TkWhen, TkWill)
  - `emit_c_expr()` (lines 898–988) handles `N_INT` through `N_ASSIGN` — the default case prints "0" for anything unrecognized
  - `parser.m0` is only 39 lines — a test harness, not a real parser
- **The self-hosted compiler currently does NOT support temporal keywords at all.**
  - The C bootstrap lexer (`lexer.c`) does recognize `freeze`, `now`, `was`, `when`, `will` and returns `M1Tk_Tk*` tokens (lines 1083–1095)
  - But `m1c.m0` doesn't define these token constants and doesn't handle them in parsing or codegen
- **Gaps identified:**
  1. No temporal AST node types in m1c.m0
  2. No temporal token constants in m1c.m0
  3. No parser logic for temporal constructs
  4. No codegen logic for temporal constructs
  5. Phase Graph externals declared but never called
  6. **Fundamental gap:** The C Phase Graph expects the C bootstrap AST format, which differs from the M0 AST format — N_FREEZE=13 in C bootstrap vs. not defined in m1c.m0

## 3. Integration Points

List the functions / passes in `m1c.m0` that will need to be modified:

| Function/Pass | What needs to be added |
|---------------|----------------------|
| Token definitions (~line 64) | Add `TK_FREEZE`, `TK_NOW`, `TK_WAS`, `TK_WHEN`, `TK_WILL` |
| AST node type definitions (~line 80) | Add `N_FREEZE`, `N_WAS`, `N_NOW`, `N_WHEN`, `N_WILL` (must match C bootstrap values for Phase Graph compat) |
| AST constructor functions (~line 146) | Add `n_freeze`, `n_was`, `n_now`, `n_when`, `n_will` |
| Parser (inside m1c.m0, ~line 400-600) | Add parsing cases for temporal keyword tokens |
| `emit_c_expr()` (~line 898) | Add codegen cases for N_FREEZE, N_WAS, N_NOW, N_WILL, N_WHEN |
| `emit_fn_ep()` or similar (~line 880) | Add function-level temporal setup (phase_graph_init, will return guards) |
| New: M0 wrapper functions | Thin wrappers calling phase_graph_* externals |

## 4. Wrapper Design (M0 side)

Proposed thin wrapper functions:
```m0
fn pg_init() -> Int { phase_graph_init() }
fn pg_record(var: String, phase: String) -> Int { phase_graph_record(var, phase) }
fn pg_freeze(var: String) -> Int { phase_graph_freeze(var) }
fn pg_query(var: String, phase: String) -> Int { phase_graph_query(var, phase) }
```

**Decisions:**
- Phase name strategy: Use simple strings matching the AST (`"live"`, `"frozen"`, integer values as strings, etc.)
- How to maintain "current phase": The Phase Graph C code maintains this internally in `VarState.cur_phase`

## 5. Constant Folding Strategy for `was`

- When do we call `pg_query`? During codegen of `was x.Phase` — call after building the graph, before emitting C
- How to decide if foldable? If `pg_query` returns 0 or 1 (not -1 = unknown), emit literal; otherwise emit runtime scan
- Example generated C before: `phase_graph_query("x", "Live") ? 1 : 0`  →  after folding: `1` (literal)

## 6. Risks & Open Questions

- **Major risk:** The Phase Graph C code expects AST nodes in the C bootstrap format (e.g. `N_FREEZE=13`). If `m1c.m0` uses different node type values for its own N_*, the Phase Graph's `walk_node` won't recognize them. Need to either (a) make m1c.m0 use the same N_* values as the C bootstrap, or (b) create a translation layer.
- **Even larger risk:** The self-hosted compiler currently has NO temporal support at all — no tokens, no AST nodes, no parser, no codegen. Adding all of these is a bigger first step than just "wiring the Phase Graph."
- Stack usage when calling many Phase Graph functions from M0 interpreter
- Will `phase_graph_build()` work correctly if called with the M0-compiler AST (which uses different node layouts)?

## 7. Next Steps (from this analysis)

- [ ] **Decision point:** Choose approach for temporal implementation in m1c.m0:
  - Option A: Add temporal AST nodes to m1c.m0 (N_FREEZE etc.) + parser + codegen + Phase Graph calls
  - Option B: Use the C bootstrap's temporal support for now, focus on M0 compiler first
- [ ] If Option A: Define N_FREEZE etc. with same numeric values as C bootstrap for Phase Graph compatibility
- [ ] Read the rest of m1c.m0 to find where parsing logic lives (it's embedded, not in parser.m0)
- [ ] ] Verify whether the C bootstrap's AST node field layout matches what m1c.m0 produces
- [ ] Write the 3 concrete integration tests first (before coding)
