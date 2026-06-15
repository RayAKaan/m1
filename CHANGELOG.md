# Changelog

All notable changes to M1 (Mn) will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.5.0] - 2026-06-13

### Added
- GitHub Actions CI workflow (`.github/workflows/test.yml`) that runs the full test suite on Windows.
- `VERSION` file at root (contains `0.5.0`).
- `v0.5` git tag.
- `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`, `CHANGELOG.md`.
- CI status badge at the top of `README.md`.
- Clear "Known Limitations" section in README (self-hosting blocker + Phase Graph integration status).

### Changed
- **Critical provenance fixes** (paper submission hygiene):
  - `paper/evidence/README.md` now contains the correct commit hash matching the `paper-evidence` tag (`519bcac...`).
  - Added detailed "Provenance & Layout Note" explaining the pre-cleanup vs post-cleanup directory structure of evidence.
- Updated all line-count and test-count claims in `paper/mn-paper.tex` to match the authoritative numbers in `paper/evidence/inventory.md`:
  - M0: 5,222 lines (was 4,923)
  - M1: 7,362 lines (was 6,848)
  - Runtime: 803 lines (was 512)
  - Test programs: 79 (was 73)
- Removed stale tracked binary artifacts from git index (`src/m0c`, `src/m1/m0_runtime_core.obj`). The golden `m1c.exe` remains intentionally tracked.

### Fixed
- Evidence commit hash mismatch that would have failed provenance verification.

### Known Issues (unchanged from v0.5 pre-audit)
- `m1c.exe` cannot self-compile its own source (stack overflow).
- Phase Graph module is standalone and not yet integrated into the self-hosted compiler.
- Several documented codegen gaps (see `paper/evidence/test-results.md`).

## [0.5.0-clean] - 2026-06 (pre-audit tag)
Initial v0.5 release with frozen paper evidence.

## [0.6.0] - 2026-06-15

This release closes the gap between the paper's vision and the delivered artifact:
the five temporal operators are implemented, integrated, and tested in the
self-hosted compiler (`src/m1/m1c.m0`), not just the C bootstrap. Verified
end-to-end on Linux/gcc and Windows/clang via `src/m1/build_selfhost.sh`
(17/17 tests pass).

### Added
- **Self-hosting unblocked** — m0c compiles m1c.m0 into a working m1c (the old
  "stack overflow" was a chain of concrete bugs: token misalignment, brace-chain
  off-by-ones, missing token-skips in parse_module/parse_decl/freeze/let live,
  a `() -> Int` extern, and a non-advancing error path that looped forever).
- **Phase Graph integration** — `was x.Phase` folds to a compile-time literal when
  statically decidable, else a runtime query. Value-named phases (`was x.1`).
- **`now` re-check after mutation** — re-checked after every assignment; prints `[M1100]`.
- **`will` return guard** — enforced at function exit; prints `[M1101]`.
- **`will`+`now` conflict detection** — literal-bound contradiction warning `[M1102]`.
- **Branch-aware phase tracking** — conditional assignments no longer fold `was`
  to a wrong literal (soundness fix).
- **Records** — type declarations, literals, field access, records as parameters.
- **Function parameters** — previously fundamentally broken (only zero-arg `main()`
  worked); now functions take parameters correctly.
- **`world`/`do`/`set`/`say`/`show` surface syntax** — the canonical README
  dialect parses.
- **Cross-platform build** — `src/m1/compat.h` shim + `src/m1/build_selfhost.sh`
  reproducible pipeline (gcc/clang).
- **CI** — `.github/workflows/test.yml` now builds everything from source on Linux
  and runs the self-hosting test suite (replaces stale m1c.exe + run_tests.ps1 flow).
- **`.gitattributes`** — stops recurring spurious BOM/EOL diffs on
  `src/m1/stress_m1.c`/`tc_m1.c`; marks `src/m1/m1c.exe` binary.
- New test suites: `tests/{now,will,surface,records,functions,conflict,branch,
  phase_graph}/`.

### Changed
- `README.md` — build/test instructions now lead with `build_selfhost.sh`;
  Status section updated to reflect working state.
- `src/reduce.c` — fixed static/non-static `reduce()` mismatch (blocked Linux build).
- `VERSION` — bumped to 0.6.0.

### Known limitations
- True self-hosting (m1c compiling its own source) not yet complete.
- Sum types / `pick`/`shape` pattern matching not yet in the self-hosted parser.
- Conditional `was` is conservative (sound but under-approximating) pending real
  runtime phase tracking.
- Minimal type checking; rough error messages.

## [Unreleased]
- Future work: Linear types, effect types, `m1 verify`, full self-hosting, Phase Graph integration.
