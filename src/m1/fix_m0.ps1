$content = Get-Content "H:\AI-Focused_language\src\m1\codegen_clean.m0" -Raw

# 1. Remove parens from if (cond) -> if cond
$content = $content -replace 'if\s*\(', 'if '
$content = $content -replace '\)\s*\{', ' {'

# 2. Fix int64_t/char* declarations to let bindings
# Pattern: "    int64_t x =" on one line, then "    expr; (void)x;" on next
$content = $content -replace '(?m)^([ \t]*)int64_t (\w+) =\s*$', "`$1let `$2 : Int ="
$content = $content -replace '(?m)^([ \t]*)char\* (\w+) =\s*$', "`$1let `$2 : String ="

# Remove (void)x; lines entirely
$content = $content -replace '(?m)^[ \t]*\(void\)\w+;\s*$', ''

# Remove p; after let bindings (the "use" of the value)
$content = $content -replace '(?m)^([ \t]*)p;\s*$', ''

# 3. Fix "expr;    (void)x;" suffix on a line
$content = $content -replace ';\s*\(void\)\w+;', ';'

# 4. Remove trailing ; on .*x; lines that are standalone
$content = $content -replace '(?m)^([ \t]*(?:\w|\.)+\([^;]*\));\s*$', '$1'

# 5. Fix {int64_t -> { int64_t (spacing)
$content = $content -replace '\{int64_t', '{ int64_t'

# 6. Remove return keyword (M0 uses last expression)
$content = $content -replace '(?m)^([ \t]*)return\s+', '$1'

# 7. Fix ; on return lines that shouldn't have them
$content = $content -replace '(?m)^([ \t]*)(\w[\w_]*\([^;]*\));$', '$1$2'
$content = $content -replace '(?m)^([ \t]*)(\d+);$', '$1$2'

# 8. Handle }return patterns -> split
$content = $content -replace '\}return ', "}`n        return "

# 9. Fix misplaced }};
$content = $content -replace '(?m)^([ \t]*)}\s*}\s*$', '$1}}'

# 10. Remove extra blank lines
$content = $content -replace "`n`n`n", "`n`n"

$content | Set-Content "H:\AI-Focused_language\src\m1\codegen_fixed.m0" -Encoding ascii
Write-Host "Done fixing M0"
