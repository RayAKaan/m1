#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arena.h"
#include "parser.h"
#include "scope.h"
#include "checker.h"
#include "types.h"
#include "reduce.h"
#include "codegen.h"

static char *read_file(const char *path, int *out_len) {
    FILE *f = fopen(path, "rb");
    if (!f) { perror("fopen"); return NULL; }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buf = malloc((size_t)len + 1);
    if (!buf) { fclose(f); return NULL; }
    long nread = (long)fread(buf, 1, (size_t)len, f);
    fclose(f);
    buf[nread] = '\0';
    *out_len = (int)nread;
    return buf;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: m0c <file.m0>\n");
        return 1;
    }

    int src_len;
    char *src = read_file(argv[1], &src_len);
    if (!src) { fprintf(stderr, "cannot read %s\n", argv[1]); return 1; }

    Arena *arena = arena_create(65536);

    Parser parser;
    parser_init(&parser, src, src_len, argv[1], arena);
    Node *prog = parse_program(&parser);
    if (parser.error_count > 0) {
        printf("Parser errors: %d\n", parser.error_count);
        free(src);
        arena_destroy(arena);
        return 1;
    }

    ScopeResolver resolver;
    resolver.arena = arena;
    resolver.current = NULL;
    resolver.error_count = 0;
    scope_resolve(&resolver, prog);
    if (resolver.error_count > 0) {
        printf("Scope errors: %d\n", resolver.error_count);
        free(src);
        arena_destroy(arena);
        return 1;
    }

    Checker checker;
    checker.arena = arena;
    checker.env = NULL;
    checker.ctors = NULL;
    checker.ctor_count = 0;
    checker.ctor_cap = 0;
    checker.error_count = 0;
    check_program(&checker, prog);
    if (checker.error_count > 0) {
        printf("Type errors: %d\n", checker.error_count);
        free(src);
        arena_destroy(arena);
        return 1;
    }

    Reducer red = { .arena = arena, .reductions = 0 };
    for (int m = 0; m < prog->data.program.count; m++) {
        Node *mod = prog->data.program.items[m];
        if (mod->kind == NODE_MODULE) {
            for (int i = 0; i < mod->data.module.count; i++) {
                Node *d = mod->data.module.decls[i];
                if (d->kind == NODE_FN_DECL) {
                    d->data.fn_decl.body = reduce(d->data.fn_decl.body, &red);
                }
            }
        }
    }

    fprintf(stderr, "Reductions: %d\n", red.reductions);

    /* Generate code */
    if (codegen(prog, NULL)) {
        fprintf(stderr, "codegen failed\n");
        free(src);
        arena_destroy(arena);
        return 1;
    }

    free(src);
    arena_destroy(arena);
    return 0;
}
