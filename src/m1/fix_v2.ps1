$content = Get-Content "H:\AI-Focused_language\src\m1\codegen_v2.m0" -Raw

# 1. Fix "if (" -> "if " and remove newline between if and (
$content = $content -replace 'if\s*\n\s*\(', 'if ('
$content = $content -replace 'if\s*\(', 'if '

# 2. Fix ")\s*{" -> " {" after condition (remove newline)
$content = $content -replace '\)\s*\n\s*\{', ') {'
$content = $content -replace 'if ([^)]+)\) \{', 'if $1 {'

# 3. Remove (void)x; remnant lines
$content = $content -replace ';?\s*\(void\)\w+;', ''

# 4. Fix multi-line int64_t declarations
$content = $content -replace '(?m)^([ \t]*)int64_t (\w+) =\s*\n\s*', '$1let $2 : Int = '
$content = $content -replace '(?m)^([ \t]*)char \*(\w+) =\s*\n\s*', '$1let $2 : String = '
$content = $content -replace '(?m)^([ \t]*)int (\w+) =\s*\n\s*', '$1let $2 : Int = '

# 5. Fix int64_t declarations not caught (single line)
$content = $content -replace '(?m)^([ \t]*)int64_t (\w+) = (.+);(\s*)$', '$1let $2 : Int = $3;$4'
$content = $content -replace '(?m)^([ \t]*)char\* (\w+) = (.+);(\s*)$', '$1let $2 : String = $3;$4'

# 6. Fix "} else {" formatting (collapse)
$content = $content -replace '(?m)^([ \t]*)}\s*\n\s*else\s*{', "`$1} else {"

# 7. Remove "return " prefix (M0 uses last expression)
$content = $content -replace '(?m)^([ \t]*)return\s+', '$1'

# 8. Remove trailing ; after bare function calls (they are return values)
$content = $content -replace '(?m)^([ \t]*)((?:m0_|emit_|flatten_|rev\b)\w*\([^;]*\));\s*$', '$1$2'

# 9. Fix spacing: ";emit_" -> ";\n    emit_"
$content = $content -replace ';(emit_|m0_|flatten_)', ";`n        `$1"

# 10. Remove extra blank lines (more than 2)
$content = $content -replace "`n`n`n+", "`n`n"

# 11. Fix m0_nil -> m0_nil()
$content = $content -replace '(?<![a-zA-Z_])m0_nil(?![a-zA-Z_(])', 'm0_nil()'

$content | Set-Content "H:\AI-Focused_language\src\m1\codegen_final.m0" -Encoding ascii
Write-Host "Done fixing"
