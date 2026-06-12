# Paper Evidence — Frozen Research Artifacts

This directory contains the frozen evidence snapshot backing the claims in
`paper/mn-paper.tex`. These files are **never auto-deleted**; they are the
permanent, committed record of the research results.

## Contents

| File | Content | Paper Claim |
|------|---------|-------------|
| `test-results.md` | Empirical test results (13/13 temporal tests pass, 46/73 overall) | §4 Implementation, §5 Case Studies |
| `inventory.md` | Line-count audit validating paper's LOC table | §4 Table 1 (4,923 C / 6,848 M0) |
| `catalog.md` | Mapping of 64 golden `_test_*.c` files to `.m1` sources | §2-4 generated C examples |
| `codegen-patterns.md` | Extracted codegen patterns for all 5 temporal keywords | §2 Keyword semantics |

## Provenance

- **Commit hash**: `4e13ebd86317324c6d3f2e0617ca5565a6d820f0`
- **Tag**: `paper-evidence` (points to the pre-cleanup snapshot)
- **Date**: June 12, 2026
- **Compiler**: `m1c.exe` (308KB, June 5, 2026)
- **Bootstrap**: `m0c.exe` (654KB, May 30, 2026)

## Regeneration

To regenerate these results:
```powershell
build m1c.exe           # or: make / build.bat
tests/build/run_tests.ps1
```

Generated C output goes to `build/` (gitignored). The golden `_test_*.c` files
that were present before cleanup are preserved forever in the `pre-cleanup` and
`paper-evidence` git tags.

## ⚠️ Do Not Overwrite

These files are a **historical snapshot** backing specific paper claims. Fresh
test runs produce new output in `build/`; do not overwrite this directory.
If the paper is updated, add new files alongside these originals.
