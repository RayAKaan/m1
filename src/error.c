#include "error.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

static const char *phase_name(Phase p) {
    switch (p) {
        case PHASE_LEXER:   return "lexer";
        case PHASE_PARSER:  return "parser";
        case PHASE_SCOPE:   return "scope";
        case PHASE_TYPE:    return "type";
        case PHASE_REDUCE:  return "reduce";
        case PHASE_CODEGEN: return "codegen";
    }
    return "unknown";
}

static void print_loc(SrcLoc loc) {
    if (loc.file) {
        fprintf(stderr, "%s:", loc.file);
    }
    fprintf(stderr, "%d:%d: ", loc.line, loc.col);
}

static void print_line(SrcLoc loc) {
    if (!loc.file) return;
    FILE *f = fopen(loc.file, "r");
    if (!f) return;
    char buf[1024];
    int line = 1;
    while (fgets(buf, sizeof(buf), f)) {
        if (line == loc.line) {
            size_t len = strlen(buf);
            if (len > 0 && buf[len - 1] == '\n') buf[len - 1] = '\0';
            fprintf(stderr, "  %s\n", buf);
            fprintf(stderr, "  %*s^\n", loc.col - 1, "");
            break;
        }
        line++;
    }
    fclose(f);
}

void error_report(Phase phase, SrcLoc loc, const char *fmt, ...) {
    fprintf(stderr, "[ERROR] %s: ", phase_name(phase));
    print_loc(loc);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    print_line(loc);
}

void error_warn(Phase phase, SrcLoc loc, const char *fmt, ...) {
    fprintf(stderr, "[WARN] %s: ", phase_name(phase));
    print_loc(loc);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
    print_line(loc);
}
