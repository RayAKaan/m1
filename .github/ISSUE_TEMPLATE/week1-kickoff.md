---
name: Sprint Week 1 — Exploration & Reconnaissance
about: Track Week 1 progress for v0.6 sprint (Phase Graph + now fix prep)
title: '[Sprint] Week 1: Exploration & Reconnaissance'
labels: sprint, v0.6, phase-graph
assignees: 
---

## Goal
Understand the current Phase Graph implementation and its integration surface in `m1c.m0`.

## Checklist

### Day 1–2: Exploration
- [ ] Build M0 bootstrap on local machine
- [ ] Read `src/m1/phase_graph.c` + `phase_graph.h` end-to-end
- [ ] Search `m1c.m0` for: `phase_graph_*`, `N_WAS`, `N_FREEZE`, `N_WILL`, `N_NOW`
- [ ] Identify how temporal keywords are currently lowered in codegen
- [ ] Find the gap between C Phase Graph and M0 codegen
- [ ] Fill in `notes/phase-graph-analysis.md`
- [ ] **Deliverable:** Filled analysis notes (even rough)

### Day 3–4: Bare expressions (Q5)
- [ ] Implement and validate

### Day 5–7: `now` re-check (start)
- [ ] Prototype runtime re-check on assignment

## Known Findings (pre-seeded)
- `phase_graph.c` has a complete AST walker building the Phase Graph
- `m1c.m0` declares externals but **never calls them**
- `phase_graph_query()` returns 1/0/-1 via DFS
- Conflict detection (will-will, now-will) already implemented in C
- Integration challenge: C AST format vs M0 AST format may differ

## References
- `notes/exploration-checklist.md`
- `notes/phase-graph-analysis.md` (template)
- `PHASE_GRAPH_INTEGRATION_SPEC.md`
- `FIRST_10_PHASE_GRAPH_TESTS.md`
- `SPRINT_30_DAY.md`

## Daily Log

### Day 1 (date):
- 

### Day 2 (date):
- 

### Day 3 (date):
- 

### Day 4 (date):
- 

### Day 5 (date):
- 

### Day 6–7 (date):
-
