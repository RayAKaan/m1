param(
    [string]$M1cPath = "H:\AI-Focused_language\src\m1\m1c.exe",
    [string]$M0RuntimeObj = "H:\AI-Focused_language\src\m1\m0_runtime_core.obj",
    [string]$InjectPy = "H:\AI-Focused_language\src\m1\inject_test.py",
    [string]$TestRoot = "H:\AI-Focused_language\tests",
    [string]$WorkDir = "H:\AI-Focused_language\src\m1",
    [switch]$PGDebug
)

$passed = 0
$failed = 0
$skipped = 0
$failures = @()

# Compile and run a single .m1 test file.
# Uses inject_test.py to add stdlib extern declarations before compilation.
# Returns $true if expected behavior matches.
function Run-Test {
    param([string]$TestFile, [string]$Label, [bool]$ExpectError = $false)

    $baseName = [System.IO.Path]::GetFileNameWithoutExtension($TestFile)
    $injPath = Join-Path $WorkDir "_inj_$baseName.m1"
    $cPath = Join-Path $WorkDir "_test_$baseName.c"
    $exePath = Join-Path $WorkDir "_test_$baseName.exe"

    # Clean up previous artifacts
    Remove-Item -Path $injPath, $cPath, $exePath, "$exePath.pdb" -ErrorAction SilentlyContinue

    # Step 1: Inject stdlib externs into the source
    $injOut = python $InjectPy $TestFile $injPath 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  [FAIL] $Label (injection failed: $injOut)"
        return $false
    }

    # Step 2: Compile with m1c (self-hosted m1c reads from M1_SOURCE env var)
    $env:M1_SOURCE = $injPath
    $compileOut = & $M1cPath 2>&1
    $compileOk = $LASTEXITCODE -eq 0

    if ($ExpectCompileError) {
        # Compile-time error tests: M1 compiler itself should reject the code
        if ($compileOk) {
            Write-Host "  [FAIL] $Label (expected compile error, but compiled successfully)"
            return $false
        } else {
            Write-Host "  [PASS] $Label (correctly rejected at compile time)"
            return $true
        }
    }

    if ($ExpectError) {
        # Error tests: should compile successfully but fail at runtime
        if (-not $compileOk) {
            Write-Host "  [FAIL] $Label (unexpected compilation failure)"
            return $false
        }
        # Write C output and compile
        $compileOut | Out-File -FilePath $cPath -Encoding ascii -Force
        $clangFlags = @('-std=c11', '-g', '-D_CRT_SECURE_NO_WARNINGS', '-o', $exePath, $cPath, $M0RuntimeObj)
        $clangOut = clang @clangFlags 2>&1
        if ($LASTEXITCODE -ne 0) {
            Write-Host "  [FAIL] $Label (clang failed: $clangOut)"
            return $false
        }
        # Run — expected to exit with non-zero code
        $runOut = & $exePath 2>&1
        $exitOk = ($LASTEXITCODE -ne 0)
        if ($exitOk) {
            Write-Host "  [PASS] $Label (correctly failed at runtime)"
            return $true
        } else {
            Write-Host "  [FAIL] $Label (expected runtime error, but succeeded)"
            return $false
        }
    }

    if (-not $compileOk) {
        Write-Host "  [FAIL] $Label (compilation failed: $compileOut)"
        return $false
    }

    # Step 3: Write generated C
    $compileOut | Out-File -FilePath $cPath -Encoding ascii -Force

    # Step 4: Compile with clang
    $clangFlags = @('-std=c11', '-g', '-D_CRT_SECURE_NO_WARNINGS', '-o', $exePath, $cPath, $M0RuntimeObj)
    if ($PGDebug) { $clangFlags += '-DPG_DEBUG' }
    
    $clangOut = clang @clangFlags 2>&1
    if ($LASTEXITCODE -ne 0) {
        Write-Host "  [FAIL] $Label (clang compilation failed: $clangOut)"
        return $false
    }

    # Step 5: Run the executable
    $runOut = & $exePath 2>&1
    if ($LASTEXITCODE -eq 0) {
        Write-Host "  [PASS] $Label"
        return $true
    } else {
        Write-Host "  [FAIL] $Label (runtime exit code $LASTEXITCODE, output: $runOut)"
        return $false
    }
}

# Discover all test files
$testFiles = Get-ChildItem -Path $TestRoot -Recurse -Filter "*.m1" `
    | Where-Object { $_.DirectoryName -notlike "*\m0\*" -and $_.DirectoryName -notlike "*\debug_logs\*" }

Write-Host "========================================"
Write-Host "  Mn M1 Compiler Test Suite"
Write-Host "  Compiler: $M1cPath"
Write-Host "  Tests:    $($testFiles.Count) files"
Write-Host "========================================"
Write-Host ""

foreach ($tf in $testFiles) {
    $relPath = $tf.FullName.Substring($TestRoot.Length + 1)
    $label = $relPath -replace '\.m1$', ''
    $fileName = $tf.Name

    # Skip debug/scratch files
    if ($fileName -match '^_') {
        Write-Host "  [SKIP] $label (scratch file)"
        $skipped++
        continue
    }

    # Determine if this is an error test
    $expectError = $fileName -match 'error'
    $expectCompileError = $fileName -match 'error_compile'

    # Module tests need special handling (multiple files)
    if ($relPath -match '^module\\') {
        # Module tests have a main file and dependencies
        # For now, skip module tests that aren't standalone
        if ($fileName -match '^test\d|^app|^_debug') {
            # These need the module resolution path set up
            Write-Host "  [SKIP] $label (module test - needs module path setup)"
            $skipped++
            continue
        }
    }

    $ok = Run-Test -TestFile $tf.FullName -Label $label -ExpectError $expectError
    if ($ok) {
        $passed++
    } else {
        $failed++
        $failures += $label
    }
}

Write-Host ""
Write-Host "========================================"
Write-Host "  Results: $passed passed, $failed failed, $skipped skipped"
Write-Host "========================================"

if ($failures.Count -gt 0) {
    Write-Host "`nFailed tests:"
    foreach ($f in $failures) {
        Write-Host "  - $f"
    }
}

exit $failed
