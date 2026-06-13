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

## [Unreleased]
- Future work: Linear types, effect types, `m1 verify`, full self-hosting, Phase Graph integration.
