import re

def c_to_m0(c_code):
    """Convert compiled C functions to M0 syntax."""
    lines = c_code.split('\n')
    out = []
    i = 0
    while i < len(lines):
        line = lines[i]
        stripped = line.strip()

        # Skip (void)x; lines - these are C-only
        if re.match(r'^\(\s*void\s*\)', stripped):
            i += 1
            continue

        # Function definition: int64_t name(int64_t p1, int64_t p2, ...) {
        m = re.match(r'^int64_t\s+(\w+)\((.*)\)\s*\{\s*$', stripped)
        if m:
            name = m.group(1)
            params_str = m.group(2)
            params = []
            if params_str.strip():
                for p in params_str.split(','):
                    p = p.strip()
                    pm = re.match(r'int64_t\s+(\w+)', p)
                    if pm:
                        params.append(pm.group(1) + ' : Int')
                    else:
                        pm2 = re.match(r'char\*\s+(\w+)', p)
                        if pm2:
                            params.append(pm2.group(1) + ' : String')
                        else:
                            params.append(p.strip())
            out.append('    fn ' + name + '(' + ', '.join(params) + ') -> Int {')
            i += 1
            continue

        # Closing brace
        if stripped == '}':
            out.append('    }')
            i += 1
            continue

        # Block end: }
        if stripped == '};':
            out.append('    };')
            i += 1
            continue

        # int64_t x = expr; (void)x; pattern -> let x : Int = expr;
        m = re.match(r'int64_t\s+(\w+)\s*=\s*(.*);', stripped)
        if m:
            var = m.group(1)
            expr = m.group(2).rstrip()
            # Check if next line is (void)var;
            if i + 1 < len(lines):
                next_stripped = lines[i + 1].strip()
                if re.match(r'\(\s*void\s*\)\s*' + re.escape(var) + r'\s*;', next_stripped):
                    i += 1  # skip the (void) line
            out.append('        let ' + var + ' : Int = ' + expr + ';')
            i += 1
            continue

        # if (cond) { -> if cond {
        m = re.match(r'^if\s+\((.*)\)\s*\{\s*$', stripped)
        if m:
            cond = m.group(1).strip()
            out.append('        if ' + cond + ' {')
            i += 1
            continue

        # } else { -> } else {
        if stripped == '} else {':
            out.append('        } else {')
            i += 1
            continue

        # else { -> else {
        if stripped == 'else {':
            out.append('        else {')
            i += 1
            continue

        # return expr; -> expr (if not followed by more expressions needing ;)
        m = re.match(r'^return\s+(.*);\s*$', stripped)
        if m:
            expr = m.group(1)
            # Check if this is the last expression before }
            # Look ahead for closing brace
            j = i + 1
            while j < len(lines) and lines[j].strip() == '':
                j += 1
            if j < len(lines) and lines[j].strip() == '}':
                out.append('        ' + expr)
            else:
                out.append('        let _r : Int = ' + expr + ';')
            i += 1
            continue

        # expr; (bare statement) -> let _tmpN : Int = expr;
        m = re.match(r'^((?:m0_|emit_|TK_|N_|OP_)[a-zA-Z_0-9]*(?:\([^;]*\))?)\s*;\s*$', stripped)
        if m and not stripped.startswith('int64_t') and not stripped.startswith('if ') and not stripped.startswith('return'):
            # Simple function call as bare statement
            expr = m.group(1)
            # Check if it's just a function call with no special handling
            if expr == ';':
                out.append('        ' + stripped)
                i += 1
                continue
            out.append('        let _s : Int = ' + expr + ';')
            i += 1
            continue

        # Single bare function call without semicolon (as expression)
        m = re.match(r'^(m0_[a-zA-Z_0-9]+\([^;]*\))\s*$', stripped)
        if m and not stripped.startswith('int64_t') and not stripped.startswith('if '):
            out.append('        ' + stripped)
            i += 1
            continue

        # Lines that might have multiple ;-separated expressions
        if ';' in stripped and not stripped.startswith('int64_t') and not stripped.startswith('if ') and not stripped.startswith('return') and not stripped.startswith('//'):
            parts = stripped.split(';')
            parts = [p.strip() for p in parts if p.strip()]
            if len(parts) > 1 and not any(p.startswith('if ') for p in parts):
                # Multiple expressions separated by ;
                for pi, part in enumerate(parts):
                    if part.endswith(')'):
                        out.append('        let _s' + str(pi) + ' : Int = ' + part + ';')
                    else:
                        out.append('        ' + part)
                i += 1
                continue

        # Keep everything else as-is
        if stripped:
            out.append('        ' + stripped)
        else:
            out.append('')
        i += 1

    return '\n'.join(out)


# Read the compiled C output
with open(r'H:\AI-Focused_language\src\m1\m1c_out_raw.c', 'r') as f:
    content = f.read()

# Find all function definitions
# Start from emit_c_expr_ea (line 1308) to end
lines = content.split('\n')
in_codegen = False
codegen_lines = []
for line in lines:
    if re.match(r'^int64_t emit_c_expr_ea\(', line.strip()):
        in_codegen = True
    if in_codegen:
        codegen_lines.append(line)

codegen_c = '\n'.join(codegen_lines)

# Convert to M0
m0_code = c_to_m0(codegen_c)

# Save
with open(r'H:\AI-Focused_language\src\m1\codegen_converted.m0', 'w') as f:
    f.write(m0_code)

print("Done. Output written to codegen_converted.m0")
print(f"Generated {len(m0_code)} chars")
