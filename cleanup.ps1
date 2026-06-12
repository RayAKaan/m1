# ============================================================
# M1 Repo Cleanup Script — SAFE BY DEFAULT
# Usage:
#   .\cleanup.ps1 -DryRun     # show what WOULD be deleted (start here!)
#   .\cleanup.ps1             # actually delete
#
# Run from repo root: H:\AI-Focused_language\
# Prerequisite: git commit + tag 'pre-cleanup' already created.
# ============================================================
param(
    [switch]$DryRun
)

$ErrorActionPreference = "Stop"
$root = Get-Location

# ---- Sanity checks: refuse to run in the wrong place / without a safety net ----
if (-not (Test-Path "$root\spec") -or -not (Test-Path "$root\src")) {
    Write-Error "This doesn't look like the M1 repo root (no spec/ or src/). Aborting."
    exit 1
}
if (-not (Test-Path "$root\.git")) {
    Write-Error "No .git directory found. Create a snapshot commit first (see CLEANUP_PLAN.md Phase 0). Aborting."
    exit 1
}
$dirty = git status --porcelain
if ($dirty -and -not $DryRun) {
    Write-Error "Working tree has uncommitted changes. Commit first so cleanup is revertible. Aborting."
    exit 1
}

# ---- Whitelist: files that match delete patterns but are REAL SOURCE ----
$whitelist = @(
    "src\m0_runtime.c",
    "src\runtime\m0_runtime.c",
    "src\m1\release\m0_runtime.c",
    "tests\build\run_tests.ps1"
)

function Is-Whitelisted($file) {
    $rel = $file.FullName.Substring($root.Path.Length + 1)
    # Paper evidence dir is sacred: frozen research artifacts backing mn-paper.tex
    if ($rel -ilike "paper\evidence\*") { return $true }
    foreach ($w in $whitelist) {
        if ($rel -ieq $w) { return $true }
    }
    return $false
}

$toDelete = New-Object System.Collections.Generic.List[System.IO.FileInfo]
$orphans  = New-Object System.Collections.Generic.List[string]

# ============================================================
# 1. Binary build artifacts — always generated, always safe
# ============================================================
$binPatterns = @("*.exe", "*.obj", "*.o", "*.pdb", "*.ilk")
foreach ($p in $binPatterns) {
    Get-ChildItem -Path $root -Recurse -File -Filter $p |
        Where-Object { $_.FullName -notmatch '\\\.git\\' -and -not (Is-Whitelisted $_) } |
        ForEach-Object { $toDelete.Add($_) }
}

# ============================================================
# 2. Debug session text dumps
# ============================================================
$txtPatterns = @(
    "_m1_*.txt", "_m1c_*.txt", "_out.txt", "out.txt",
    "*stderr*.txt", "*stdout*.txt", "*_err.txt", "*_err[0-9].txt",
    "_e[0-9].txt", "_o[0-9].txt", "ts_err*.txt", "ts_out*.txt",
    "clang_err.txt", "hello_err.txt"
)
foreach ($p in $txtPatterns) {
    Get-ChildItem -Path $root -Recurse -File -Filter $p |
        Where-Object { $_.FullName -notmatch '\\\.git\\' -and -not (Is-Whitelisted $_) } |
        ForEach-Object { $toDelete.Add($_) }
}

# ============================================================
# 3. Generated C files — but ONLY if a paired .m1/.m0 source exists.
#    foo_gen.c / foo_out.c is deletable iff some foo*.m1 or foo*.m0
#    exists anywhere in the repo. Otherwise it's flagged as an ORPHAN
#    for manual review (it might be the only surviving copy of a test).
# ============================================================
$allM1Sources = Get-ChildItem -Path $root -Recurse -File -Include "*.m1","*.m0" |
    Where-Object { $_.FullName -notmatch '\\\.git\\' }
$sourceBaseNames = $allM1Sources | ForEach-Object { $_.BaseName.ToLower() } | Sort-Object -Unique

$genFiles = Get-ChildItem -Path $root -Recurse -File -Include "*_gen.c","*_out.c" |
    Where-Object { $_.FullName -notmatch '\\\.git\\' -and -not (Is-Whitelisted $_) }

foreach ($g in $genFiles) {
    # strip _gen / _out suffix to find the logical test name
    $base = $g.BaseName -replace '_(gen|out)$', ''
    $base = $base.ToLower()
    $hasSource = $sourceBaseNames | Where-Object { $_ -like "$base*" -or $base -like "$_*" }
    if ($hasSource) {
        $toDelete.Add($g)
    } else {
        $orphans.Add($g.FullName.Substring($root.Path.Length + 1))
    }
}

# ============================================================
# 4. Whole directories that are pure output
# ============================================================
$dirsToEmpty = @("tests\generated_c", "tests\debug_logs")
foreach ($d in $dirsToEmpty) {
    $full = Join-Path $root $d
    if (Test-Path $full) {
        Get-ChildItem -Path $full -Recurse -File |
            Where-Object { -not (Is-Whitelisted $_) } |
            ForEach-Object { $toDelete.Add($_) }
    }
}

# tests/build: everything except run_tests.ps1
$tb = Join-Path $root "tests\build"
if (Test-Path $tb) {
    Get-ChildItem -Path $tb -Recurse -File |
        Where-Object { $_.Name -ine "run_tests.ps1" } |
        ForEach-Object { $toDelete.Add($_) }
}

# ============================================================
# Dedupe + report
# ============================================================
$unique = $toDelete | Sort-Object FullName -Unique
$totalSize = ($unique | Measure-Object Length -Sum).Sum / 1MB

Write-Host ""
Write-Host "=================== CLEANUP REPORT ===================" -ForegroundColor Cyan
Write-Host ("Files to delete : {0}" -f $unique.Count)
Write-Host ("Space reclaimed : {0:N1} MB" -f $totalSize)
Write-Host ("Orphan _gen/_out C files (NOT deleted, review by hand): {0}" -f $orphans.Count)
Write-Host "======================================================="
Write-Host ""

if ($orphans.Count -gt 0) {
    Write-Host "ORPHANS (generated C with no matching .m1/.m0 source found):" -ForegroundColor Yellow
    $orphans | ForEach-Object { Write-Host "  KEEP?  $_" -ForegroundColor Yellow }
    Write-Host ""
}

if ($DryRun) {
    Write-Host "DRY RUN — nothing deleted. Full list:" -ForegroundColor Green
    $unique | ForEach-Object { Write-Host ("  DEL  " + $_.FullName.Substring($root.Path.Length + 1)) }
    Write-Host ""
    Write-Host "Re-run without -DryRun to delete." -ForegroundColor Green
} else {
    $unique | ForEach-Object { Remove-Item -LiteralPath $_.FullName -Force }
    # remove now-empty directories
    Get-ChildItem -Path $root -Recurse -Directory |
        Where-Object { $_.FullName -notmatch '\\\.git\\' } |
        Sort-Object { $_.FullName.Length } -Descending |
        Where-Object { -not (Get-ChildItem $_.FullName -Force -ErrorAction SilentlyContinue) } |
        Remove-Item -Force -ErrorAction SilentlyContinue
    Write-Host "Deleted. Now: rebuild (make / build.bat), run tests, then:" -ForegroundColor Green
    Write-Host '  git add -A ; git commit -m "chore: remove generated artifacts"' -ForegroundColor Green
}
