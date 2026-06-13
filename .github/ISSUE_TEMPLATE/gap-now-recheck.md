---
name: Gap — now invariant re-check after mutation
about: Track the missing now re-evaluation after assignment (Q1 from test-results)
title: '[GAP] now invariants are only checked at declaration, not after mutation'
labels: gap, temporal, spec-vs-impl
---

**From `paper/evidence/test-results.md` (Behavioral Summary)**

> now: re-check after mutation — ❌ Missing | Spec Requires re-check | **GAP**

### Current Behavior
`now balance >= 0;` only emits a check at the declaration site. Subsequent mutations (e.g. `balance = balance - 2000;`) do **not** re-evaluate the invariant.

### Expected Behavior
Every mutation of a `live` variable that is under a `now` invariant must re-check the condition at runtime (or prove it statically).

### Evidence
- `tests/now/now_test.m1` and `now_mutation_test.m1`
- Generated C in evidence shows only one-time check
- Related: `task1_bank.m1`

### Priority
High for v0.6 / M2.

### References
- `paper/evidence/test-results.md`
- `paper/evidence/codegen-patterns.md`
- Spec section on invariants
