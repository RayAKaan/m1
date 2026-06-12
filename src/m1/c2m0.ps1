# Convert compiled C output to M0 syntax for the codegen section
$cFile = "H:\AI-Focused_language\src\m1\m1c_out_raw.c"
$lines = Get-Content $cFile | Select-Object -Skip 1140
$out = @()
$i = 0

while ($i -lt $lines.Count) {
    $line = $lines[$i]
    $trimmed = $line.Trim()
    
    # Skip empty lines
    if ($trimmed -eq "") { $i++; continue }
    
    # Function declarations
    if ($trimmed -match '^(int64_t|char\s*\*|void|M1\w+)\s+(\w+)\((.*)\)\s*\{$') {
        $retType = $matches[1]
        $fnName = $matches[2]
        $paramsRaw = $matches[3]
        
        # Skip main - it's handled differently
        if ($fnName -eq "main") {
            $out += "    fn main() -> Int {"
            $i++
            while ($i -lt $lines.Count) {
                $innerLine = $lines[$i].Trim()
                if ($innerLine -eq "}") { $out += "    }"; $i++; break }
                $out += "        " + (Convert-CLine $innerLine)
                $i++
            }
            continue
        }
        
        # Convert parameter types
        $params = @()
        if ($paramsRaw -ne "") {
            $paramsRaw -split ',' | ForEach-Object {
                $p = $_.Trim()
                if ($p -match '^(int64_t|char\s*\*|M1\w+|PS|PR|int)\s+(\w+)$') {
                    $ptype = $matches[1].Trim()
                    $pname = $matches[2]
                    switch -Regex ($ptype) {
                        'int64_t' { $params += "$pname : Int" }
                        'char\s*\*' { $params += "$pname : String" }
                        'M1Lexer' { $params += "$pname : M1Lexer" }
                        'M1LexResult' { $params += "$pname : M1LexResult" }
                        'PS' { $params += "$pname : PS" }
                        'PR' { $params += "$pname : PR" }
                        'int' { $params += "$pname : Int" }
                        default { $params += "$pname : $ptype" }
                    }
                } else {
                    $params += $p
                }
            }
        }
        $paramsStr = $params -join ', '
        if ($retType -eq 'int64_t' -or $retType -eq 'int') { $retM0 = 'Int' }
        elseif ($retType -eq 'void') { $retM0 = 'Unit' }
        elseif ($retType -eq 'char*' -or $retType -eq 'char *') { $retM0 = 'String' }
        else { $retM0 = $retType }
        
        $out += "    fn $fnName($paramsStr) -> $retM0 {"
        $i++
        continue
    }
    
    # Previous line started a function but params continue
    if ($trimmed -match '^int64_t\s+(\w+)\(\s*$') {
        # Multi-line param - peek ahead
        $fnName = $matches[1]
        $allParams = ""
        $j = $i + 1
        while ($j -lt $lines.Count) {
            $pLine = $lines[$j].Trim()
            $allParams += $pLine
            if ($pLine -match '\)\s*\{$') { $j++; break }
            $j++
        }
        $allParams = $allParams -replace '\)\s*\{$', ''
        $params = @()
        $allParams -split ',' | ForEach-Object {
            $p = $_.Trim()
            if ($p -match '^\s*(int64_t|char\s*\*|M1\w+|PS|PR|int)\s+(\w+)\s*$') {
                $ptype = $matches[1].Trim()
                $pname = $matches[2]
                switch -Regex ($ptype) {
                    'int64_t' { $params += "$pname : Int" }
                    'char\s*\*' { $params += "$pname : String" }
                    'M1Lexer' { $params += "$pname : M1Lexer" }
                    'PS' { $params += "$pname : PS" }
                    'PR' { $params += "$pname : PR" }
                    default { $params += "$pname : $ptype" }
                }
            } else { $params += $p }
        }
        $paramsStr = $params -join ', '
        $out += "    fn $fnName($paramsStr) -> Int {"
        $i = $j
        continue
    }
    
    $i++
}

# Helper function
function Convert-CLine {
    param($text)
    # Handle void casts
    if ($text -match '^\s*\(void\)\w+;\s*$') { return "" }
    if ($text -match '^(.*?)\(void\)\w+;') { $text = $matches[1] }
    
    # Handle (expr).field -> expr.field
    $text = $text -replace '\((\w+)\)\.', '$1.'
    
    # Handle m0_nil without parens
    $text = $text -replace '(?<![\w.])m0_nil(?![\w(])', 'm0_nil()'
    
    # Handle return
    if ($text -match '^\s*return\s+(.*?);\s*$') { return $matches[1] }
    
    # Handle int64_t x = expr;
    if ($text -match '^\s*int64_t\s+(\w+)\s*=\s*$') { return "let $($matches[1]) : Int = " }
    if ($text -match '^\s*int64_t\s+(\w+)\s*=\s*(.*?);\s*(\(void\)\w+)?\s*$') { return "let $($matches[1]) : Int = $($matches[2]);" }
    
    # Handle char* x = expr;
    if ($text -match '^\s*char\s*\*\s*(\w+)\s*=\s*(.*?);\s*$') { return "let $($matches[1]) : String = $($matches[2]);" }
    
    # Handle M1Lexer/PS/PR x = expr;
    if ($text -match '^\s*(M1\w+|PS|PR|int)\s+(\w+)\s*=\s*(.*?);\s*(\(void\)\w+)?\s*$') { return "let $($matches[2]) : $($matches[1]) = $($matches[3]);" }
    
    # Handle closing braces with return
    if ($text -match '^\s*\}(return\s+(.*?);)\s*$') { return "}; $($matches[2])" }
    if ($text -match '^\s*\}\s*$') { return $text }
    
    # Handle if/else
    if ($text -match '^\s*if\s+\((.*)\)\s*\{$') { return "if $($matches[1]) {" }
    if ($text -match '^\s*\}\s*else\s*\{$') { return "} else {" }
    
    # Handle stray variable name on its own (like p3;)
    if ($text -match '^\s*(\w+);\s*$') { return "$($matches[1])" }
    
    # Handle assignment like fields = m0_get(t, 3);
    if ($text -match '^\s*(\w+)\s*=\s*(.*?);\s*$') { return "let $($matches[1]) : Int = $($matches[2]);" }
    
    return $text
}

$out | Out-File -FilePath "H:\AI-Focused_language\src\m1\codegen_m0_temp.txt" -Encoding utf8
Write-Host "Written $($out.Count) lines"
