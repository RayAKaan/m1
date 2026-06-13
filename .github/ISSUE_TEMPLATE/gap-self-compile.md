---
name: Gap — self-hosting blocker
about: Track the stack overflow when m1c.exe tries to compile its own source
title: '[GAP] m1c.exe cannot self-compile (stack overflow on m1c.m0)'
labels: gap, bootstrap, self-hosting
---

**From `paper/evidence/test-results.md` and README**

> Binary cannot self-compile (stack overflow on 1,025-line m1c.m0 input).

### Current Behavior
`m1c.exe` (the golden binary used for all paper evidence) crashes with `0xC00000FD` (stack overflow) when fed `src/m1/m1c.m0`.

M0 can bootstrap the first m1c, but the self-hosted compiler cannot rebuild itself.

### Expected Behavior (M2)
Full self-hosting: `m1c.m0` compiled by `m1c.exe` produces a working new m1c binary.

### Workarounds Today
- Increase stack size for the interpreter
- Compile the compiler in pieces / use a larger bootstrap
- Keep using the prebuilt golden binary for evidence

### Priority
High for claiming "self-hosting" in future papers or v0.6+.

### References
- `paper/evidence/test-results.md` §1 Binary Self-Compilation Test
- `src/m1/m1c.m0` (size)
- README "Known Limitations" section
