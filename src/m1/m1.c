#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32
  #include <process.h>
  #define popen _popen
  #define pclose _pclose
#else
  #include <unistd.h>
#endif

#define M1_VERSION "0.7.0"

static const char* SRC_DIR;
static char CC[256] = {0};

static void die(const char* msg) {
    fprintf(stderr, "FATAL: %s\n", msg);
    exit(1);
}

static const char* ldflags(void) {
#ifdef _WIN32
    return "-Wl,/stack:8388608";
#else
    return "";
#endif
}

static const char* src_dir(void) {
    if (!SRC_DIR) {
        SRC_DIR = getenv("M1_SRC");
        if (!SRC_DIR) SRC_DIR = "src/m1";
    }
    return SRC_DIR;
}

static void detect_cc(void) {
    if (CC[0]) return;
    char* env = getenv("CC");
    if (env) { strncpy(CC, env, sizeof(CC)-1); return; }
#ifdef _WIN32
    const char* try_cc[] = {"gcc", "clang", "cl", 0};
#else
    const char* try_cc[] = {"gcc", "clang", "cc", 0};
#endif
    for (int i = 0; try_cc[i]; i++) {
        char cmd[512];
#ifdef _WIN32
        snprintf(cmd, sizeof(cmd), "where %s >nul 2>nul", try_cc[i]);
#else
        snprintf(cmd, sizeof(cmd), "which %s >/dev/null 2>/dev/null", try_cc[i]);
#endif
        if (system(cmd) == 0) {
            strncpy(CC, try_cc[i], sizeof(CC)-1);
            return;
        }
    }
    strncpy(CC, "gcc", sizeof(CC)-1);
}

static int run_cmd(const char* fmt, ...) {
    char buf[4096];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof(buf), fmt, ap);
    va_end(ap);
    return system(buf);
}

static int build_m0bootstrap(void) {
    const char* d = src_dir();
    char work[1024];
    snprintf(work, sizeof(work), "%s/../..", d);
    char cmd[8192];
    detect_cc();
    snprintf(cmd, sizeof(cmd),
        "mkdir -p /tmp/m1b && cp %s/*.c %s/*.h /tmp/m1b/ 2>/dev/null; "
        "cd /tmp/m1b && sed -i 's/^static Node \\*reduce(Node \\*n, Reducer \\*r);/\\/* fwd *\\//' reduce.c 2>/dev/null; "
        "sed -i 's/^static Node \\*reduce(Node \\*n, Reducer \\*r) {/Node *reduce(Node *n, Reducer *r) {/' reduce.c 2>/dev/null; "
        "%s -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 -o m0c main.c arena.c error.c lexer.c parser.c scope.c types.c checker.c reduce.c codegen.c",
        d, d, CC);
    int r = system(cmd);
    if (r != 0) die("could not build bootstrap m0c");
    return 0;
}

static int cmd_build(const char* m1file) {
    const char* d = src_dir();
    char work[1024];
    snprintf(work, sizeof(work), "/tmp/m1b");
    detect_cc();

    /* Build bootstrap if needed */
    build_m0bootstrap();

    /* Compile lexer.m0 */
    char cmd[8192];
    snprintf(cmd, sizeof(cmd),
        "cd /tmp/m1b && ./m0c %s/lexer.m0 > lexer_raw.c 2>/dev/null; "
        "python3 -c \"import re,sys; c=open('lexer_raw.c').read(); "
        "c=re.sub(r'typedef struct M1Tk M1Tk;\\\\s*struct M1Tk\\\\s*\\\\{.*?\\\\}\\\\s*;', 'typedef int64_t M1Tk;', c, count=1, flags=re.S); "
        "c=re.sub(r'M1Tk v = \\\\{\\\\s*\\\\.tag = (M1Tk_\\\\w+),\\\\s*\\\\.data = \\\\{0\\\\}\\\\s*\\\\};', r'M1Tk v = \\\\1;', c); "
        "c=c.replace('.tag', ''); "
        "open('lexer_int.c','w').write(c)\"",
        d);
    if (system(cmd) != 0) die("lexer.m0 compilation failed");

    /* Compile m1c.m0 */
    snprintf(cmd, sizeof(cmd),
        "cd /tmp/m1b && ./m0c %s/m1c.m0 > m1c_self.c 2>/dev/null",
        d);
    if (system(cmd) != 0) die("m1c.m0 compilation failed");

    /* Link self-hosted m1c */
    snprintf(cmd, sizeof(cmd),
        "%s -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 %s -include %s/compat.h -o /tmp/m1b/m1c "
        "/tmp/m1b/m1c_self.c %s/m0_runtime.c %s/phase_graph.c /tmp/m1b/lexer_int.c 2>/dev/null",
        CC, ldflags(), d, d, d);
    if (system(cmd) != 0) die("m1c link failed");

    /* Compile user .m1 file */
    char out_c[1024], out_exe[1024];
    snprintf(out_c, sizeof(out_c), "%s.c", m1file);
    snprintf(out_exe, sizeof(out_exe), "%s.exe", m1file);
    char set_m1src[2048];
#ifdef _WIN32
    snprintf(set_m1src, sizeof(set_m1src), "set M1_SOURCE=%s && /tmp/m1b/m1c", m1file);
#else
    snprintf(set_m1src, sizeof(set_m1src), "M1_SOURCE=%s /tmp/m1b/m1c", m1file);
#endif
    snprintf(cmd, sizeof(cmd),
        "%s > %s 2>/dev/null; "
        "%s -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 %s -include %s/compat.h -o %s %s %s/m0_runtime.c %s/phase_graph.c 2>/dev/null",
        set_m1src, out_c, CC, ldflags(), d, out_exe, out_c, d, d);
    if (system(cmd) != 0) die("user program build failed");
    return 0;
}

static int cmd_run(const char* m1file) {
    if (cmd_build(m1file) != 0) return 1;
    char out_exe[1024];
    snprintf(out_exe, sizeof(out_exe), "%s.exe", m1file);
    return system(out_exe);
}

static int cmd_check(const char* m1file) {
    const char* d = src_dir();
    char work[1024];
    snprintf(work, sizeof(work), "/tmp/m1b");
    detect_cc();

    build_m0bootstrap();

    char cmd[8192];
    snprintf(cmd, sizeof(cmd),
        "cd /tmp/m1b && ./m0c %s/lexer.m0 > lexer_raw.c 2>/dev/null; "
        "python3 -c \"import re,sys; c=open('lexer_raw.c').read(); "
        "c=re.sub(r'typedef struct M1Tk M1Tk;\\\\s*struct M1Tk\\\\s*\\\\{.*?\\\\}\\\\s*;', 'typedef int64_t M1Tk;', c, count=1, flags=re.S); "
        "c=re.sub(r'M1Tk v = \\\\{\\\\s*\\\\.tag = (M1Tk_\\\\w+),\\\\s*\\\\.data = \\\\{0\\\\}\\\\s*\\\\};', r'M1Tk v = \\\\1;', c); "
        "c=c.replace('.tag', ''); "
        "open('lexer_int.c','w').write(c)\"",
        d);
    system(cmd);

    snprintf(cmd, sizeof(cmd),
        "cd /tmp/m1b && ./m0c %s/m1c.m0 > m1c_self.c 2>/dev/null",
        d);
    system(cmd);

    snprintf(cmd, sizeof(cmd),
        "%s -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 %s -include %s/compat.h -o /tmp/m1b/m1c "
        "/tmp/m1b/m1c_self.c %s/m0_runtime.c %s/phase_graph.c /tmp/m1b/lexer_int.c 2>/dev/null",
        CC, ldflags(), d, d, d);
    system(cmd);

    char out_c[1024], out_exe[1024], err_file[1024];
    snprintf(out_c, sizeof(out_c), "%s.c", m1file);
    snprintf(out_exe, sizeof(out_exe), "%s.exe", m1file);
    snprintf(err_file, sizeof(err_file), "%s.err", m1file);
#ifdef _WIN32
    snprintf(cmd, sizeof(cmd), "set M1_SOURCE=%s && /tmp/m1b/m1c > %s 2>%s", m1file, out_c, err_file);
#else
    snprintf(cmd, sizeof(cmd), "M1_SOURCE=%s /tmp/m1b/m1c > %s 2>%s", m1file, out_c, err_file);
#endif
    system(cmd);

    /* Compile C */
    snprintf(cmd, sizeof(cmd),
        "%s -std=gnu11 -w -fcommon -fno-strict-aliasing -O0 %s -include %s/compat.h -o %s %s %s/m0_runtime.c %s/phase_graph.c 2>/dev/null",
        CC, ldflags(), d, out_exe, out_c, d, d);
    if (system(cmd) != 0) return 1;

    /* Run and capture stderr */
#ifdef _WIN32
    snprintf(cmd, sizeof(cmd), "%s 2>&1", out_exe);
#else
    snprintf(cmd, sizeof(cmd), "%s 2>&1", out_exe);
#endif
    return system(cmd);
}

static int cmd_test(void) {
    /* Run the full test suite via build_selfhost.sh */
    const char* d = src_dir();
    char cmd[4096];
    snprintf(cmd, sizeof(cmd), "cd %s/../.. && bash %s/build_selfhost.sh", d, d);
    return system(cmd);
}

static void cmd_version(void) {
    printf("M1 Compiler v%s\n", M1_VERSION);
    printf("Self-hosted compiler for the M1 language\n");
}

static void usage(void) {
    printf("M1 Compiler v%s\n", M1_VERSION);
    printf("Usage: m1 <command> [args]\n");
    printf("Commands:\n");
    printf("  build <file.m1>   Compile .m1 file to executable\n");
    printf("  run   <file.m1>   Compile and run .m1 file\n");
    printf("  check <file.m1>   Compile, compile C, run, print stderr\n");
    printf("  test              Run the full test suite\n");
    printf("  version           Print version info\n");
    printf("  help              Print this help\n");
}

int main(int argc, char** argv) {
    if (argc < 2) { usage(); return 1; }
    const char* cmd = argv[1];
    if (strcmp(cmd, "build") == 0) {
        if (argc < 3) { fprintf(stderr, "Usage: m1 build <file.m1>\n"); return 1; }
        return cmd_build(argv[2]);
    } else if (strcmp(cmd, "run") == 0) {
        if (argc < 3) { fprintf(stderr, "Usage: m1 run <file.m1>\n"); return 1; }
        return cmd_run(argv[2]);
    } else if (strcmp(cmd, "check") == 0) {
        if (argc < 3) { fprintf(stderr, "Usage: m1 check <file.m1>\n"); return 1; }
        return cmd_check(argv[2]);
    } else if (strcmp(cmd, "test") == 0) {
        return cmd_test();
    } else if (strcmp(cmd, "version") == 0 || strcmp(cmd, "--version") == 0) {
        cmd_version();
        return 0;
    } else {
        usage();
        return 1;
    }
}
