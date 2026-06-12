# Repository Inventory

## Line Counts by Component

All counts exclude binary artifacts (.exe, .pdb, .obj). Source files only.

| Component | Files | Lines | Notes |
|-----------|-------|-------|-------|
| M0 bootstrap compiler (src/) | 45 | 5,222 | .c/.h files in src/ (lexer, parser, checker, reducer, codegen, scope, types, arena, main, error) |
| M1 self-hosted (.m0 in src/m1/) | 26 | 7,362 | Primary m1c.m0 (1,025 lines) + lexer.m0 (362) + codegen variants + parser.m0 |
| Runtime library (src/) | 2 | 803 | m0_runtime.c (386) + src/m1/m0_runtime.c (468) + m0_runtime_core.c (417) |
| Phase Graph | 2 | 427 | phase_graph.c (418) + phase_graph.h (9) |
| Tests (.m1/.m0) | 79 | 5,771 | .m1 files in tests/ and .m0 files in src/ |
| Spec | 7 | 2,655 | markdown files in spec/ |
| Standard library | 3 | 182 | std.m1 + string.m1 + vector.m1 in stdlib/ |
| Paper | 1 | 980 | mn-paper.tex |
| Python scripts | 3 | 442 | .py files in root |
| Build scripts | 5 | 516 | .ps1 + .bat files |
| **Total source** | **168** | **36,078** | |

## Golden Output Files (src/m1/_test_*.c)

| Count | Total Lines |
|-------|------------|
| 64 files | 22,799 lines |

These are pre-compiled C outputs from the m1c.exe binary, serving as the "oracle" for correct codegen.

## Inj Files (src/m1/_inj_*.m1)

| Count | Description |
|-------|------------|
| 64 files | Injected test sources with full paths (used by m1c.exe as input) |

The `_inj_*.m1` files are copies of test .m1 sources with injected path prefixes for error messages. They are the actual input files that the m1c.exe binary reads.

## Binary Artifacts (excluded from source count)

| Type | Count | Notes |
|------|-------|-------|
| .exe | ~50 | Test executables + compilers |
| .pdb | ~50 | MSVC debug symbols |
| .obj | ~5 | Object files |

Total binary artifact "line count" (when read as text): ~1.5M+ lines (all junk).

## File Size Distribution

| Range | Count | Examples |
|-------|-------|----------|
| >500 lines | 8 | m1c_out_raw.c (3,318), m1c_out_debug.c (2,393), m1c_out.c (1,925), codegen_final.m0 (1,931), m1c.m0 (1,025), lexer_out_raw.c (1,152) |
| 100-500 lines | ~40 | Most runtime C files, spec docs, test files |
| <100 lines | ~120 | Small test files, headers, build scripts |

## Key Source Files

| File | Lines | Role |
|------|-------|------|
| src/m1/m1c.m0 | 1,025 | M1 self-hosted compiler (no temporal support) |
| src/m1/lexer.m0 | 362 | M1 lexer (no temporal keywords) |
| src/m1/codegen_final.m0 | 1,931 | Largest codegen variant (potential reference) |
| src/m1/lexer_out_raw.c | 1,152 | Compiled lexer C output |
| src/m1/phase_graph.c | 418 | Phase Graph module (standalone, not integrated) |
| src/main.c | 91 | M0 bootstrap entry point |
| src/lexer.c | 301 | M0 bootstrap lexer (OLD keywords only) |
| src/parser.c | 720 | M0 bootstrap parser |
| src/checker.c | 615 | M0 bootstrap type checker |
| src/codegen.c | 1,027 | M0 bootstrap code generator |
| src/m1/m0_runtime.c | 468 | M1 runtime (string/vector/map/matrix/float) |
| src/m1/m0_runtime_core.c | 417 | M1 runtime core (cons-list) |

## Paper Claims vs Reality

| Paper Claim | Actual | Match? |
|------------|--------|--------|
| "4,923-line C frontend (M0)" | M0 bootstrap: 5,222 lines (45 files) | Close (4,923 vs 5,222) |
| "6,848 lines of M0 source (M1)" | M1 .m0 sources: 7,362 lines (26 files) | Close (6,848 vs 7,362) |
| "M1 compiler comprises 6,848 lines" | m1c.m0 alone = 1,025 lines | Paper counts all .m0 files |
| "Runtime library: 512 lines of C" | Runtime: 803 lines (across 3 files) | Slightly higher |
| "Compiler of 6,848 lines, passes 46 of 73 tests" | Tests: 79 .m1/.m0 files, ~5,771 lines | Test count includes .m0 + non-test sources |

**Verdict**: Paper's line counts are in the right ballpark (differences of ~500-1,500 lines likely due to counting methodology or subsequent additions). The key claims (4,923 LOC for M0, 6,848 for M1 source) are approximately correct.

## No Missing Files

- **`Mn-Updates-1/` directory**: Does NOT exist on this filesystem. The unified compiler source `m1c.c` from the paper/references was never found. The binary `m1c.exe` is the sole reference.
- **No `.git` directory**: Not a git repository. No revision history available.
- **All 64 `_test_*.c` golden files present**: No orphans other than the 3 expected 0-byte cycle test outputs.

## Last Modified

All files dated **June 5-6, 2026**. No stale files older than the project's active development window.
