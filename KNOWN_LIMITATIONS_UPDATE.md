## Known Limitations (as of v0.6 work in progress)

M1 is still early. The following limitations are actively being worked on as part of the v0.6 "Credible Prototype" effort (see `ROADMAP_v0.6.md`).

### Core Semantic Gaps (Being Closed in v0.6)

- **Phase Graph integration is incomplete**  
  The Phase Graph (the project's main technical contribution for compile-time `was` folding and phase tracking) exists as a solid standalone C module. Full integration into the self-hosted compiler (`m1c.m0`) is the highest priority item for v0.6. Until this is complete, many `was` results are not statically folded.

- **`now` invariants are not yet re-checked after mutation** (Q1)  
  A `now balance >= 0;` check is currently only emitted at the declaration site. Subsequent assignments do not automatically re-validate the invariant. This is one of the most important semantic gaps and is scheduled for v0.6.

- **Self-hosting is still fragile**  
  The self-hosted compiler (`m1c`) has historically crashed with stack overflow when compiling its own source (`src/m1/m1c.m0`). Significant progress is expected in v0.6 (via stack improvements, reduced recursion, or hybrid bootstrap strategies), but it may not be 100% seamless yet.

- **Basic `will` + `now` conflict detection is missing** (Q3)  
  It is currently possible to write contradictory combinations of `will` commitments and `now` invariants without any warning or error. This will be addressed (at least at a warning level) as part of Phase Graph integration.

### Ergonomics & Completeness

- Error messages are still rough in many cases.
- Some advanced temporal features (full interprocedural analysis, user-defined phases, etc.) are explicitly M2 work.
- The toolchain is currently easiest to use on Windows. Linux/macOS support is improving but not yet first-class.

### What v0.6 Is Trying to Deliver

By the end of the v0.6 cycle we aim to have:
- The Phase Graph actually participating in compilation (with visible constant folding for `was`)
- `now` invariants being re-checked after mutation
- Self-hosting working on the compiler's own source (possibly with some caveats)
- Bare expression statements
- All existing temporal tests still passing, plus new tests that demonstrate the integrated behavior

See `ROADMAP_v0.6.md` and the five open gap issues for the current detailed plan.

**Honesty note:** We are deliberately keeping this section visible and up-to-date. The goal is to make the gap between the paper's vision and the delivered compiler as small and transparent as possible.

Full details (including the 5 documented codegen gaps) are in `paper/evidence/test-results.md`.
