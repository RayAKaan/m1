---
name: Gap — will + now conflict detection
about: Track missing compile-time conflict between will commitments and now invariants (Q3)
title: '[GAP] will + now conflict detection is missing'
labels: gap, temporal, phase-graph
---

**From `paper/evidence/test-results.md`**

> will+now conflict detection — ❌ Missing | Should produce Phase Graph warning at compile time (Q3)

### Current Behavior
You can write code that has a `will x == 1` and a `now x >= 0` that can never both be satisfied, and the compiler accepts it.

### Expected Behavior
The Phase Graph (or a simple static analysis) should detect contradictory commitments/invariants at compile time and emit a warning or error.

### Evidence
- `tests/will/` and `tests/now/` combination tests
- `paper/evidence/codegen-patterns.md` explicitly calls this out as a gap

### Priority
Medium-High (core to the "temporal logic built into the language" claim).

### References
- `paper/evidence/test-results.md` §4 Behavioral Summary
- Phase Graph module (`src/m1/phase_graph.c`)
