#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

static char base[1024];

static void find_base(void) {
    GetModuleFileNameA(NULL, base, sizeof(base));
    char* s = strrchr(base, '\\');
    if (s) *s = '\0';
}

static void usage(void) {
    printf("m1 0.1.0\n\n");
    printf("Usage:\n");
    printf("  m1 run <file.m1>     Compile and run\n");
    printf("  m1 build <file.m1>   Compile to executable\n");
    printf("  m1 check <file.m1>   Check syntax\n");
    printf("  m1 version           Print version\n");
}

static const char* stdlib_preamble =
    "\n    external \"m0_print\" : String -> Int\n"
    "    external \"m0_println\" : String -> Int\n"
    "    external \"m0_string_len\" : String -> Int\n"
    "    external \"m0_string_concat\" : String -> String -> String\n"
    "    external \"m0_int_to_string\" : Int -> String\n"
    "    external \"m0_string_to_int\" : String -> Int\n"
    "    external \"m0_read_file\" : String -> String\n"
    "    external \"m0_write_file\" : String -> String -> Int\n"
    "    external \"m1_vector_new\" : Unit -> Int\n"
    "    external \"m1_vector_push\" : Int -> Int -> Int\n"
    "    external \"m1_vector_get\" : Int -> Int -> Int\n"
    "    external \"m1_vector_set\" : Int -> Int -> Int -> Int\n"
    "    external \"m1_vector_len\" : Int -> Int\n"
    "    external \"m1_vector_sort\" : Int -> Int\n"
    "    external \"m1_read_line\" : Unit -> String\n"
    "    external \"m1_read_int\" : Unit -> Int\n"
    "    external \"m1_char_at\" : String -> Int -> Int\n"
    "    external \"m1_substring\" : String -> Int -> Int -> String\n"
    "    external \"m1_string_split\" : String -> String -> Int\n"
    "    external \"m1_vector_get_str\" : Int -> Int -> String\n"
    "    external \"m1_map_new\" : Unit -> Int\n"
    "    external \"m1_map_set\" : Int -> Int -> Int -> Int\n"
    "    external \"m1_map_get\" : Int -> Int -> Int\n"
    "    external \"m1_map_has\" : Int -> Int -> Int\n"
    "    external \"m1_map_len\" : Int -> Int\n"
    "    external \"m1_matrix_new\" : Int -> Int -> Int\n"
    "    external \"m1_matrix_get\" : Int -> Int -> Int -> Int\n"
    "    external \"m1_matrix_set\" : Int -> Int -> Int -> Int -> Int\n"
    "    external \"m1_float_of_int\" : Int -> Int\n"
    "    external \"m1_float_add\" : Int -> Int -> Int\n"
    "    external \"m1_float_sub\" : Int -> Int -> Int\n"
    "    external \"m1_float_mul\" : Int -> Int -> Int\n"
    "    external \"m1_float_div\" : Int -> Int -> Int\n"
    "    external \"m1_float_lt\" : Int -> Int -> Int\n"
    "    external \"m1_float_gt\" : Int -> Int -> Int\n"
    "    external \"m1_float_eq\" : Int -> Int -> Int\n"
    "    external \"m1_float_to_string\" : Int -> String\n"
    "    external \"m1_string_to_float\" : String -> Int\n"
    "    do say(s : String) -> Int { m0_println(s) }\n"
    "    do show(s : String) -> Int { m0_print(s) }\n"
    "    do string_len(s : String) -> Int { m0_string_len(s) }\n"
    "    do string_concat(a : String, b : String) -> String { m0_string_concat(a, b) }\n"
    "    do int_to_string(n : Int) -> String { m0_int_to_string(n) }\n"
    "    do string_to_int(s : String) -> Int { m0_string_to_int(s) }\n"
    "    do read_file(path : String) -> String { m0_read_file(path) }\n"
    "    do write_file(path : String, content : String) -> Int { m0_write_file(path, content) }\n"
    "    do vector_new() -> Int { m1_vector_new() }\n"
    "    do vector_push(v : Int, x : Int) -> Int { m1_vector_push(v, x) }\n"
    "    do vector_get(v : Int, i : Int) -> Int { m1_vector_get(v, i) }\n"
    "    do vector_set(v : Int, i : Int, x : Int) -> Int { m1_vector_set(v, i, x) }\n"
    "    do vector_len(v : Int) -> Int { m1_vector_len(v) }\n"
    "    do vector_sort(v : Int) -> Int { m1_vector_sort(v) }\n"
    "    do read_line() -> String { m1_read_line() }\n"
    "    do read_int() -> Int { m1_read_int() }\n"
    "    do char_at(s : String, i : Int) -> Int { m1_char_at(s, i) }\n"
    "    do substring(s : String, start : Int, len : Int) -> String { m1_substring(s, start, len) }\n"
    "    do string_split(s : String, delim : String) -> Int { m1_string_split(s, delim) }\n"
    "    do vector_get_str(v : Int, i : Int) -> String { m1_vector_get_str(v, i) }\n"
    "    do map_new() -> Int { m1_map_new() }\n"
    "    do map_set(m : Int, k : Int, v : Int) -> Int { m1_map_set(m, k, v) }\n"
    "    do map_get(m : Int, k : Int) -> Int { m1_map_get(m, k) }\n"
    "    do map_has(m : Int, k : Int) -> Int { m1_map_has(m, k) }\n"
    "    do map_len(m : Int) -> Int { m1_map_len(m) }\n"
    "    do matrix_new(rows : Int, cols : Int) -> Int { m1_matrix_new(rows, cols) }\n"
    "    do matrix_get(m : Int, r : Int, c : Int) -> Int { m1_matrix_get(m, r, c) }\n"
    "    do matrix_set(m : Int, r : Int, c : Int, v : Int) -> Int { m1_matrix_set(m, r, c, v) }\n"
    "    do float_of_int(n : Int) -> Int { m1_float_of_int(n) }\n"
    "    do float_add(a : Int, b : Int) -> Int { m1_float_add(a, b) }\n"
    "    do float_sub(a : Int, b : Int) -> Int { m1_float_sub(a, b) }\n"
    "    do float_mul(a : Int, b : Int) -> Int { m1_float_mul(a, b) }\n"
    "    do float_div(a : Int, b : Int) -> Int { m1_float_div(a, b) }\n"
    "    do float_lt(a : Int, b : Int) -> Int { m1_float_lt(a, b) }\n"
    "    do float_gt(a : Int, b : Int) -> Int { m1_float_gt(a, b) }\n"
    "    do float_eq(a : Int, b : Int) -> Int { m1_float_eq(a, b) }\n"
    "    do float_to_string(f : Int) -> String { m1_float_to_string(f) }\n"
    "    do string_to_float(s : String) -> Int { m1_string_to_float(s) }\n";

static int count_lines(const char* s) {
    int n = 0;
    for (; *s; s++) if (*s == '\n') n++;
    return n;
}

static int preamble_line_offset(void) {
    return count_lines(stdlib_preamble);
}

static int inject_stdlib(const char* src_path, const char* out_path) {
    FILE* f = fopen(src_path, "rb");
    if (!f) {
        fprintf(stderr, "error: cannot open %s\n", src_path);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buf = malloc(len + 1);
    fread(buf, 1, len, f);
    buf[len] = '\0';
    fclose(f);

    char* brace = strchr(buf, '{');
    if (!brace) {
        fprintf(stderr, "error: no module body found\n");
        free(buf);
        return 1;
    }

    long pos = (brace - buf) + 1;

    FILE* out = fopen(out_path, "wb");
    if (!out) {
        fprintf(stderr, "error: cannot write %s\n", out_path);
        free(buf);
        return 1;
    }
    fwrite(buf, 1, pos, out);
    fputs(stdlib_preamble, out);
    fwrite(buf + pos, 1, len - pos, out);
    fclose(out);
    free(buf);
    return 0;
}

int main(int argc, char** argv) {
    find_base();

    if (argc < 2) { usage(); return 1; }

    if (strcmp(argv[1], "version") == 0) {
        printf("m1 0.1.0\n");
        return 0;
    }

    if (strcmp(argv[1], "run") == 0 && argc >= 3) {
        char cmd[4096];

        if (inject_stdlib(argv[2], "_m1_tmp_src.m1") != 0) return 1;

        const char* src_path = argv[2];
        const char* basename = src_path;
        for (const char* p = src_path; *p; p++)
            if (*p == '\\' || *p == '/') basename = p + 1;

        char env[4096];
        snprintf(env, sizeof(env), "M1_SOURCE=_m1_tmp_src.m1");
        _putenv(env);

        char pl_str[64];
        snprintf(pl_str, sizeof(pl_str), "M1_PREAMBLE_LINES=%d", preamble_line_offset());
        _putenv(pl_str);

        snprintf(cmd, sizeof(cmd), "\"%s\\m1c.exe\" %s > _m1_tmp.c", base, basename);
        int ret = system(cmd);
        remove("_m1_tmp_src.m1");
        if (ret != 0) {
            fprintf(stderr, "error: compilation failed\n");
            remove("_m1_tmp.c");
            return 1;
        }

        snprintf(cmd, sizeof(cmd),
            "clang -std=gnu11 -Xlinker /subsystem:console "
            "-Wno-incompatible-library-redeclaration "
            "-Wno-parentheses-equality "
            "-Wno-implicit-function-declaration "
            "-Wno-int-conversion "
            "-o _m1_tmp.exe _m1_tmp.c \"%s\\m0_runtime.c\"", base);
        ret = system(cmd);
        if (ret != 0) {
            fprintf(stderr, "error: c compilation failed\n");
            remove("_m1_tmp.c");
            return 1;
        }

        ret = system("_m1_tmp.exe");
        int code = ret;

        remove("_m1_tmp.c");
        remove("_m1_tmp.exe");

        return code;
    }

    if (strcmp(argv[1], "build") == 0 && argc >= 3) {
        char cmd[4096];
        char out[256];

        if (inject_stdlib(argv[2], "_m1_tmp_src.m1") != 0) return 1;

        const char* src_path = argv[2];
        const char* basename = src_path;
        for (const char* p = src_path; *p; p++)
            if (*p == '\\' || *p == '/') basename = p + 1;

        char env[4096];
        snprintf(env, sizeof(env), "M1_SOURCE=_m1_tmp_src.m1");
        _putenv(env);

        char pl_str[64];
        snprintf(pl_str, sizeof(pl_str), "M1_PREAMBLE_LINES=%d", preamble_line_offset());
        _putenv(pl_str);

        strncpy(out, argv[2], sizeof(out) - 1);
        out[sizeof(out) - 1] = '\0';
        char* dot = strrchr(out, '.');
        if (dot) *dot = '\0';
        strcat(out, ".exe");

        snprintf(cmd, sizeof(cmd), "\"%s\\m1c.exe\" %s > _m1_tmp.c", base, basename);
        int ret = system(cmd);
        remove("_m1_tmp_src.m1");
        if (ret != 0) {
            fprintf(stderr, "error: compilation failed\n");
            remove("_m1_tmp.c");
            return 1;
        }

        snprintf(cmd, sizeof(cmd),
            "clang -std=gnu11 -Xlinker /subsystem:console "
            "-Wno-incompatible-library-reclaration "
            "-Wno-parentheses-equality "
            "-o \"%s\" _m1_tmp.c \"%s\\m0_runtime.c\"", out, base);
        ret = system(cmd);
        remove("_m1_tmp.c");
        if (ret != 0) {
            fprintf(stderr, "error: c compilation failed\n");
            return 1;
        }

        printf("Built %s\n", out);
        return 0;
    }

    if (strcmp(argv[1], "check") == 0 && argc >= 3) {
        char cmd[4096];

        if (inject_stdlib(argv[2], "_m1_tmp_src.m1") != 0) return 1;

        const char* src_path = argv[2];
        const char* basename = src_path;
        for (const char* p = src_path; *p; p++)
            if (*p == '\\' || *p == '/') basename = p + 1;

        char env[4096];
        snprintf(env, sizeof(env), "M1_SOURCE=_m1_tmp_src.m1");
        _putenv(env);

        char pl_str[64];
        snprintf(pl_str, sizeof(pl_str), "M1_PREAMBLE_LINES=%d", preamble_line_offset());
        _putenv(pl_str);

        snprintf(cmd, sizeof(cmd), "\"%s\\m1c.exe\" %s > NUL", base, basename);
        int ret = system(cmd);
        remove("_m1_tmp_src.m1");
        if (ret == 0) printf("OK\n");
        else fprintf(stderr, "error: check failed\n");
        return ret ? 1 : 0;
    }

    usage();
    return 1;
}
