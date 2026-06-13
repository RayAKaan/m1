---
name: Gap — unified error code scheme
about: Track incomplete M10xx/M11xx error code implementation (Q6)
title: '[GAP] Error code scheme is only partially implemented'
labels: gap, diagnostics, usability
---

**From `paper/evidence/test-results.md`**

> Error codes: M10xx/M11xx — Partial (M11xx used) | Unified scheme (Q6)

### Current Behavior
Some errors use the documented M10xx (compile) / M11xx (runtime) scheme. Many still use generic messages or different numbering.

### Expected Behavior
All temporal and language errors should use a consistent, documented scheme with codes, phases (compile/runtime), and clear messages.

### Evidence
- `paper/evidence/test-results.md`
- Current error.c / error messages in the compiler

### Priority
Medium (improves paper claim credibility and user experience).
