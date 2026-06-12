# Generate M0 codegen functions from compiled C output
$cfile = "H:\AI-Focused_language\src\m1\m1c_out_raw.c"
$content = Get-Content $cfile -Raw

# Split into functions
$lines = $content -split "`n"

# Find start of each codegen function
$in_func = $false
$current = @()
$out = @()

function Convert-Func {
    param($body)
    $lines = $body -split "`n"
    $result = @()
    
    foreach ($line in $lines) {
        $trimmed = $line.Trim()
        
        # Skip (void)x; lines
        if ($trimmed -match '^\(void\)\w+;') { continue }
        
        # Comment lines
        if ($trimmed -match '^//') { continue }
        
        # Function definition
        if ($trimmed -match '^int64_t\s+(\w+)\((.*)\)\s*\{\s*$') {
            $fname = $matches[1]
            $params = $matches[2]
            $plist = @()
            if ($params.Trim()) {
                foreach ($p in ($params -split ',')) {
                    $p = $p.Trim()
                    if ($p -match 'int64_t\s+(\w+)') { $plist += "$($matches[1]) : Int" }
                    elseif ($p -match 'char\*\s+(\w+)') { $plist += "$($matches[1]) : String" }
                    else { $plist += $p }
                }
            }
            $result += "    fn $fname($($plist -join ', ')) -> Int {"
            continue
        }
        
        # Closing brace
        if ($trimmed -eq '}' -or $trimmed -eq '};') {
            $result += "    }"
            continue
        }
        
        # int64_t x = expr; (void)x;
        if ($trimmed -match '^int64_t\s+(\w+)\s*=\s*(.+);\s*$') {
            $var = $matches[1]
            $expr = $matches[2]
            $result += "        let $var : Int = $expr;"
            continue
        }
        
        # char* x = expr;
        if ($trimmed -match '^char\*\s+(\w+)\s*=\s*(.+);\s*$') {
            $var = $matches[1]
            $expr = $matches[2]
            $result += "        let $var : String = $expr;"
            continue
        }
        
        # if (cond) {
        if ($trimmed -match '^if\s+\((.*)\)\s*\{\s*$') {
            $cond = $matches[1]
            $result += "        if $cond {"
            continue
        }
        
        # } else {
        if ($trimmed -eq '} else {') {
            $result += "        } else {"
            continue
        }
        
        # else {
        if ($trimmed -eq 'else {') {
            $result += "        else {"
            continue
        }
        
        # return expr;
        if ($trimmed -match '^return\s+(.+);\s*$') {
            $expr = $matches[1]
            $result += "        $expr"
            continue
        }
        
        # return;
        if ($trimmed -eq 'return;') {
            $result += "        0"
            continue
        }
        
        # Count braces to determine indent level
        $openCount = 0; $closeCount = 0
        foreach ($c in $trimmed.ToCharArray()) {
            if ($c -eq '{') { $openCount++ }
            if ($c -eq '}') { $closeCount++ }
        }
        
        # Only add non-empty or meaningful lines
        if ($trimmed -ne '') {
            $result += "        $trimmed"
        } else {
            $result += ""
        }
    }
    
    return ($result -join "`n")
}

# Extract functions from compiled C starting at emit_typedef_ef
$startIdx = -1
for ($i = 0; $i -lt $lines.Count; $i++) {
    if ($lines[$i] -match '^int64_t emit_typedef_ef\(') {
        $startIdx = $i
        break
    }
}

$funcStart = -1
$braceDepth = 0
$funcLines = @()

for ($i = $startIdx; $i -lt $lines.Count; $i++) {
    $line = $lines[$i]
    $trimmed = $line.Trim()
    
    if ($trimmed -match '^int64_t (\w+)\(.*\)\s*\{\s*$' -or $trimmed -match '^char\* (\w+)\(.*\)\s*\{\s*$') {
        if ($funcStart -ge 0) {
            # Output previous function
            $funcBody = ($funcLines -join "`n")
            $converted = Convert-Func $funcBody
            $out += $converted
            $out += ""
        }
        $funcStart = $i
        $funcLines = @($line)
        $braceDepth = 1
        continue
    }
    
    if ($funcStart -ge 0) {
        $funcLines += $line
        # Count braces
        $inStr = $false
        foreach ($c in $line.ToCharArray()) {
            if ($c -eq '"') { $inStr = -not $inStr; continue }
            if (-not $inStr) {
                if ($c -eq '{') { $braceDepth++ }
                if ($c -eq '}') { $braceDepth-- }
            }
        }
        if ($braceDepth -le 0) {
            # Output this function
            $funcBody = ($funcLines -join "`n")
            $converted = Convert-Func $funcBody
            $out += $converted
            $out += ""
            $funcStart = -1
            $funcLines = @()
        }
    }
}

# Write output
$out -join "`n" | Out-File -LiteralPath "H:\AI-Focused_language\src\m1\codegen_clean.m0" -Encoding ascii
Write-Host "Generated $($out.Count) lines"
