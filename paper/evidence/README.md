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

- **Commit hash**: `519bcac179f4128a984a40b164bec3fb4aaea956`
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

## Provenance & Layout Note (added 2026-06-13)

The `paper-evidence` tag (`519bcac179f4128a984a40b164bec3fb4aaea956`) captures the
pre-cleanup state. At the time of that tag:

- Evidence files (`catalog.md`, `inventory.md`, `test-results.md`, `codegen-patterns.md`, `README.md`)
  lived at the repository **root**.
- Later cleanup commit `7cd3374` moved the evidence into `paper/evidence/`.
- Current `HEAD` (and the `paper/evidence/` directory) reflects the post-cleanup
  canonical layout used for ongoing development.
- When checking out the tag (`git checkout paper-evidence`), look for the evidence
  files at the root of the working tree, not inside `paper/evidence/`.

The hash and tag above now match (`git rev-parse paper-evidence`).

This README is maintained at HEAD and describes both the frozen snapshot and the
current location.
