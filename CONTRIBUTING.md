# Contributing to M1

Thank you for your interest in M1 (Mn) — a language where time is a first-class type.

## Quick Start for Contributors

1. **Clone and build the bootstrap**
   ```powershell
   git clone https://github.com/RayAKaan/m1.git
   cd M1/src
   build.bat          # produces m0c.exe (requires clang on PATH)
   ```

2. **Run the test suite**
   ```powershell
   cd ..\tests\build
   powershell -ExecutionPolicy Bypass -File run_tests.ps1
   ```

The golden m1c.exe (self-hosted compiler) lives in `src/m1/`.

## Development Guidelines

- The project is currently Windows-first (PowerShell + clang).
- All temporal-operator changes must be accompanied by tests in `tests/freeze/`, `tests/now/`, etc.
- Update `paper/evidence/` only when you have frozen, reproducible evidence.
- The `paper-evidence` tag and `paper/evidence/inventory.md` are the source of truth for paper claims.

## Reporting Issues

Please use the issue templates. Include:

- Exact version (`cat VERSION` or the `m1 version` output)
- `m1c.exe` build date if relevant
- Minimal reproducing `.m1` file
- Output of `tests/build/run_tests.ps1` on your machine

## Code of Conduct

This project follows the Contributor Covenant. See `CODE_OF_CONDUCT.md`.
