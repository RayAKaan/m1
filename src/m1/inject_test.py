import sys
with open(sys.argv[1], 'r') as f:
    src = f.read()
brace_pos = src.find('{')
if brace_pos >= 0:
    # always inject external declarations (no risk of conflict)
    lines = [
        '    external "m0_print" : String -> Int',
        '    external "m0_println" : String -> Int',
        '    external "m0_string_len" : String -> Int',
        '    external "m0_string_concat" : String -> String -> String',
        '    external "m0_int_to_string" : Int -> String',
        '    external "m0_string_to_int" : String -> Int',
        '    external "m0_read_file" : String -> String',
        '    external "m0_write_file" : String -> String -> Int',
        '    external "m1_vector_new" : Unit -> Int',
        '    external "m1_vector_push" : Int -> Int -> Int',
        '    external "m1_vector_get" : Int -> Int -> Int',
        '    external "m1_vector_set" : Int -> Int -> Int -> Int',
        '    external "m1_vector_len" : Int -> Int',
        '    external "m1_vector_sort" : Int -> Int',
        '    external "m1_read_line" : Unit -> String',
        '    external "m1_read_int" : Unit -> Int',
        '    external "m1_char_at" : String -> Int -> Int',
        '    external "m1_substring" : String -> Int -> Int -> String',
        '    external "m1_string_split" : String -> String -> Int',
        '    external "m1_vector_get_str" : Int -> Int -> String',
        '    external "m1_map_new" : Unit -> Int',
        '    external "m1_map_set" : Int -> Int -> Int -> Int',
        '    external "m1_map_get" : Int -> Int -> Int',
        '    external "m1_map_has" : Int -> Int -> Int',
        '    external "m1_map_len" : Int -> Int',
        '    external "m1_matrix_new" : Int -> Int -> Int',
        '    external "m1_matrix_get" : Int -> Int -> Int -> Int',
        '    external "m1_matrix_set" : Int -> Int -> Int -> Int -> Int',
        '    external "m1_float_of_int" : Int -> Int',
        '    external "m1_float_add" : Int -> Int -> Int',
        '    external "m1_float_sub" : Int -> Int -> Int',
        '    external "m1_float_mul" : Int -> Int -> Int',
        '    external "m1_float_div" : Int -> Int -> Int',
        '    external "m1_float_lt" : Int -> Int -> Int',
        '    external "m1_float_gt" : Int -> Int -> Int',
        '    external "m1_float_eq" : Int -> Int -> Int',
        '    external "m1_float_to_string" : Int -> String',
        '    external "m1_string_to_float" : String -> Int',
    ]
    # conditionally inject do definitions — skip if the source already defines them
    do_defs = [
        ('say',          '    do say(s : String) -> Int { m0_println(s) }'),
        ('show',         '    do show(s : String) -> Int { m0_print(s) }'),
        ('string_len',   '    do string_len(s : String) -> Int { m0_string_len(s) }'),
        ('string_concat','    do string_concat(a : String, b : String) -> String { m0_string_concat(a, b) }'),
        ('int_to_string','    do int_to_string(n : Int) -> String { m0_int_to_string(n) }'),
        ('string_to_int','    do string_to_int(s : String) -> Int { m0_string_to_int(s) }'),
        ('read_file',    '    do read_file(path : String) -> String { m0_read_file(path) }'),
        ('write_file',   '    do write_file(path : String, content : String) -> Int { m0_write_file(path, content) }'),
        ('vector_new',   '    do vector_new() -> Int { m1_vector_new() }'),
        ('vector_push',  '    do vector_push(v : Int, x : Int) -> Int { m1_vector_push(v, x) }'),
        ('vector_get',   '    do vector_get(v : Int, i : Int) -> Int { m1_vector_get(v, i) }'),
        ('vector_set',   '    do vector_set(v : Int, i : Int, x : Int) -> Int { m1_vector_set(v, i, x) }'),
        ('vector_len',   '    do vector_len(v : Int) -> Int { m1_vector_len(v) }'),
        ('vector_sort',  '    do vector_sort(v : Int) -> Int { m1_vector_sort(v) }'),
        ('read_line',    '    do read_line() -> String { m1_read_line() }'),
        ('read_int',     '    do read_int() -> Int { m1_read_int() }'),
        ('char_at',      '    do char_at(s : String, i : Int) -> Int { m1_char_at(s, i) }'),
        ('substring',    '    do substring(s : String, start : Int, len : Int) -> String { m1_substring(s, start, len) }'),
        ('string_split', '    do string_split(s : String, delim : String) -> Int { m1_string_split(s, delim) }'),
        ('vector_get_str','    do vector_get_str(v : Int, i : Int) -> String { m1_vector_get_str(v, i) }'),
        ('map_new',      '    do map_new() -> Int { m1_map_new() }'),
        ('map_set',      '    do map_set(m : Int, k : Int, v : Int) -> Int { m1_map_set(m, k, v) }'),
        ('map_get',      '    do map_get(m : Int, k : Int) -> Int { m1_map_get(m, k) }'),
        ('map_has',      '    do map_has(m : Int, k : Int) -> Int { m1_map_has(m, k) }'),
        ('map_len',      '    do map_len(m : Int) -> Int { m1_map_len(m) }'),
        ('matrix_new',   '    do matrix_new(rows : Int, cols : Int) -> Int { m1_matrix_new(rows, cols) }'),
        ('matrix_get',   '    do matrix_get(m : Int, r : Int, c : Int) -> Int { m1_matrix_get(m, r, c) }'),
        ('matrix_set',   '    do matrix_set(m : Int, r : Int, c : Int, v : Int) -> Int { m1_matrix_set(m, r, c, v) }'),
        ('float_of_int', '    do float_of_int(n : Int) -> Int { m1_float_of_int(n) }'),
        ('float_add',    '    do float_add(a : Int, b : Int) -> Int { m1_float_add(a, b) }'),
        ('float_sub',    '    do float_sub(a : Int, b : Int) -> Int { m1_float_sub(a, b) }'),
        ('float_mul',    '    do float_mul(a : Int, b : Int) -> Int { m1_float_mul(a, b) }'),
        ('float_div',    '    do float_div(a : Int, b : Int) -> Int { m1_float_div(a, b) }'),
        ('float_lt',     '    do float_lt(a : Int, b : Int) -> Int { m1_float_lt(a, b) }'),
        ('float_gt',     '    do float_gt(a : Int, b : Int) -> Int { m1_float_gt(a, b) }'),
        ('float_eq',     '    do float_eq(a : Int, b : Int) -> Int { m1_float_eq(a, b) }'),
        ('float_to_string','    do float_to_string(f : Int) -> String { m1_float_to_string(f) }'),
        ('string_to_float','    do string_to_float(s : String) -> Int { m1_string_to_float(s) }'),
    ]
    for name, line in do_defs:
        if f'do {name}(' not in src:
            lines.append(line)

    stdlib = '\n' + '\n'.join(lines) + '\n'
    injected = src[:brace_pos+1] + stdlib + src[brace_pos+1:]
    with open(sys.argv[2], 'w') as f:
        f.write(injected)
    print(f"Injected {sys.argv[1]} to {sys.argv[2]}")
else:
    print("No brace found")
