# Phase Graph Analysis Notes

**Date started:** YYYY-MM-DD
**Author:**

## 1. Current Phase Graph Implementation (C side)

- **File locations:** `src/m1/phase_graph.c`, `src/m1/phase_graph.h`
- **Key data structures:**
- **Main functions and their responsibilities:**
  - `phase_graph_init`:
  - `phase_graph_record`:
  - `phase_graph_freeze`:
  - `phase_graph_query`:
  - `phase_graph_will_check`:
- **How phases are represented internally:**
- **How the graph is updated on assignment / freeze:**
- **Any existing tests or usage in the standalone C module:**
- **Key observations / surprises:**

## 2. Current Usage in Self-Hosted Compiler (m1c.m0)

- Where are the `phase_graph_*` externals declared?
- Are they called anywhere today in the parser / checker / codegen?
- How are `live` variables, `freeze`, `was`, `will`, `now` currently lowered?
- Current representation of phases in the AST or during codegen:
- **Gaps identified:**

## 3. Integration Points

List the functions / passes in `m1c.m0` that will need to be modified:

| Function/Pass | What needs to be added |
|---------------|----------------------|
| | |
| | |

## 4. Wrapper Design (M0 side)

Proposed thin wrapper functions:
```m0
fn pg_init() -> Int { ... }
fn pg_record(var: String, phase: String) -> Int { ... }
fn pg_freeze(var: String) -> Int { ... }
fn pg_query(var: String, phase: String) -> Int { ... }
```

**Decisions:**
- Phase name strategy:
- How to maintain "current phase" for live variables during compilation:

## 5. Constant Folding Strategy for `was`

- When do we call `pg_query`?
- How do we decide at compile time whether the result can be folded to a literal?
- What should the generated C look like for a folded `was`?

## 6. Risks & Open Questions

- Stack usage / performance when recording many phases
- Keeping C implementation and M0 wrappers in sync
- Handling of phases across function boundaries
- Error reporting when phase graph operations fail

## 7. Next Steps (from this analysis)

- [ ]
- [ ]
