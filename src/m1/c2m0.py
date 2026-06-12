"""
Convert compiled C functions from m1c_out_raw.c to M0.
"""
import re

with open(r'H:\AI-Focused_language\src\m1\m1c_out_raw.c') as f:
    lines = f.readlines()

# Find codegen functions starting from emit_c_expr_ea DEFINITION (not prototype)
start = 0
found_proto = False
for i, line in enumerate(lines):
    if 'emit_c_expr_ea' in line and '{' in line:
        start = i
        break

# Extract function bodies
funcs = []
i = start
while i < len(lines):
    line = lines[i]
    m = re.match(r'^(?:int64_t|char\*)\s+(\w+)\((.*)\)\s*\{\s*$', line)
    if m:
        name = m.group(1)
        params = m.group(2)
        body_lines = []
        depth = 1
        i += 1
        while i < len(lines) and depth > 0:
            l = lines[i]
            # Count braces (skip strings)
            in_str = False
            for ch in l:
                if ch == '"':
                    in_str = not in_str
                elif ch == '{' and not in_str:
                    depth += 1
                elif ch == '}' and not in_str:
                    depth -= 1
            if depth > 0:
                body_lines.append(l)
            i += 1
        funcs.append({'name': name, 'params': params, 'body': body_lines})
    else:
        i += 1

# Convert each function
def convert_param(p):
    p = p.strip()
    m = re.match(r'int64_t\s+(\w+)', p)
    if m:
        return m.group(1) + ' : Int'
    m = re.match(r'char\*\s+(\w+)', p)
    if m:
        return m.group(1) + ' : String'
    return p

def convert_body(body_lines, indent=8):
    """Convert function body lines to M0."""
    out = []
    multi_line_decl = None  # Track multi-line int64_t declarations
    for line_no, line in enumerate(body_lines):
        stripped = line.rstrip()
        if not stripped.strip():
            out.append('')
            continue

        # Handle multi-line declarations: "int64_t x =" on one line, expression on next
        m = re.match(r'^(\s*)int64_t\s+(\w+)\s*=\s*$', stripped)
        if m:
            multi_line_decl = (m.group(1), m.group(2))
            continue
        
        if multi_line_decl:
            ws, var = multi_line_decl
            m2 = re.match(r'^(\s*)(.*?);\s*\(void\)\w+;\s*$', stripped)
            if m2:
                expr = m2.group(2).strip()
                out.append('        let ' + var + ' : Int = ' + expr + ';')
            else:
                m2 = re.match(r'^(\s*)(.*?);\s*$', stripped)
                if m2:
                    expr = m2.group(2).strip()
                    out.append('        let ' + var + ' : Int = ' + expr + ';')
                else:
                    out.append('        let ' + var + ' : Int = ' + stripped.strip() + ';')
            multi_line_decl = None
            continue

        # int64_t x = expr; (void)x; (single line)
        m = re.match(r'^(\s*)int64_t\s+(\w+)\s*=\s*(.+);\s*\(void\)\w+;\s*$', stripped)
        if m:
            var, expr = m.group(2), m.group(3)
            out.append('        let ' + var + ' : Int = ' + expr + ';')
            continue

        # int64_t x = expr; (single line, no void)
        m = re.match(r'^(\s*)int64_t\s+(\w+)\s*=\s*(.+);\s*$', stripped)
        if m:
            var, expr = m.group(2), m.group(3)
            out.append('        let ' + var + ' : Int = ' + expr + ';')
            continue

        # char* x = expr; (void)x;
        m = re.match(r'^(\s*)char\*\s+(\w+)\s*=\s*(.+);\s*\(void\)\w+;\s*$', stripped)
        if m:
            var, expr = m.group(2), m.group(3)
            out.append('        let ' + var + ' : String = ' + expr + ';')
            continue

        # char* x = expr;
        m = re.match(r'^(\s*)char\*\s+(\w+)\s*=\s*(.+);\s*$', stripped)
        if m:
            var, expr = m.group(2), m.group(3)
            out.append('        let ' + var + ' : String = ' + expr + ';')
            continue

        # (void)x; - skip entirely
        if re.match(r'^(\s*)\(void\)\w+;\s*$', stripped):
            continue

        # Bare var; like "p;" (discard value)
        if re.match(r'^(\s*)\w+;\s*$', stripped) and not re.match(r'^(\s*)(if|return|int64_t|char)', stripped):
            continue

        # if (cond) {
        m = re.match(r'^(\s*)if\s+\((.*)\)\s*\{\s*$', stripped)
        if m:
            cond = m.group(2).strip()
            out.append('        if ' + cond + ' {')
            continue

        # } else {
        if re.match(r'^(\s*)\}\s*else\s*\{\s*$', stripped):
            out.append('        } else {')
            continue

        # else {
        if re.match(r'^(\s*)else\s*\{\s*$', stripped):
            out.append('        else {')
            continue

        # return expr;
        m = re.match(r'^(\s*)return\s+(.+);\s*$', stripped)
        if m:
            expr = m.group(2).strip()
            out.append('        ' + expr)
            continue

        # return; -> 0
        m = re.match(r'^(\s*)return;\s*$', stripped)
        if m:
            out.append('        0')
            continue

        # } (closing brace)
        if re.match(r'^(\s*)\}\s*$', stripped) or re.match(r'^(\s*)\}\s*;\s*$', stripped):
            out.append('    }')
            continue

        # }return -> split (already handled by above + return rule)
        m = re.match(r'^(\s*)\}(.*)$', stripped)
        if m:
            rest = m.group(2).strip()
            out.append('    }')
            if rest:
                # Process rest (which might be "return expr;")
                rm = re.match(r'return\s+(.+);', rest)
                if rm:
                    out.append('        ' + rm.group(1))
                else:
                    out.append('        ' + rest)
            continue

        # Bare expr; statement that's not covered by other rules
        # Look ahead to see if there's more after this line
        m = re.match(r'^(\s*)(m0_\w+\([^;]*\)|emit_\w+\([^;]*\));\s*$', stripped)
        if m:
            expr = m.group(2)
            # Check if next line is a closing brace (meaning this is the last expr)
            is_last = False
            if line_no + 1 < len(body_lines):
                next_s = body_lines[line_no + 1].strip()
                if next_s == '}':
                    is_last = True
            if is_last:
                out.append('        ' + expr)
            else:
                out.append('        let _s : Int = ' + expr + ';')
            continue

        # Handle "} int64_t" pattern
        m = re.match(r'^(\s*)\}\s+int64_t\s+(\w+)\s*=\s*(.*);\s*\(void\)\w+;\s*$', stripped)
        if m:
            var, expr = m.group(2), m.group(3)
            out.append('    }')
            out.append('        let ' + var + ' : Int = ' + expr + ';')
            continue

        # Fallback: keep the line as-is (after removing leading whitespace)
        if stripped.strip():
            out.append('        ' + stripped.strip())
        else:
            out.append('')

    return '\n'.join(out)

# Generate output
result = []
for func in funcs:
    name = func['name']
    params = ', '.join(convert_param(p) for p in func['params'].split(',') if p.strip())
    body = convert_body(func['body'])
    result.append('    fn ' + name + '(' + params + ') -> Int {')
    result.append(body)
    result.append('')
    result.append('')

with open(r'H:\AI-Focused_language\src\m1\codegen_v2.m0', 'w') as f:
    f.write('\n'.join(result))

print(f"Generated {len(result)} lines for {len(funcs)} functions")
