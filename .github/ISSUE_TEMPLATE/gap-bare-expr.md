---
name: Gap — bare expression statements
about: Track that bare expressions are not yet supported (must use set _ wrapper) (Q5)
title: '[GAP] Bare expression statements require set _ wrapper'
labels: gap, syntax, parser
---

**From `paper/evidence/test-results.md`**

> Bare expression statements — ❌ Requires `set _` wrapper | Spec: Bare exprs valid (Q5)

### Current Behavior
`say("hello");` as a bare statement does not parse / is rejected.
You must write `set _ : Int = say("hello");`

### Expected Behavior
Top-level expressions in blocks should be allowed as statements (the value is discarded).

### Evidence
- Multiple tests in `tests/` still use the `set _` pattern
- Spec grammar and reduction rules expect bare exprs

### Priority
Low-Medium (ergonomics, not core semantics).

### References
- `paper/evidence/test-results.md`
- `spec/03-reduction.md`
