#include <stdio.h>
#include <stdint.h>

typedef struct {
    int64_t kind;
    int64_t line;
    int64_t col;
    int64_t int_val;
    char* str_val;
} M1Token;

typedef struct {
    char* src;
    int64_t pos;
    int64_t line;
    int64_t col;
} M1Lexer;

typedef struct {
    M1Token token;
    M1Lexer lexer;
} M1LexResult;

typedef struct {
    M1Token tk;
    M1Lexer lx;
    int64_t err;
} PS;

typedef struct {
    int64_t node;
    PS st;
} PR;

extern char* m0_get_env(char*);
extern char* m0_read_file(char*);
extern int64_t m0_print(char*);
extern M1Lexer m1_lexer_init(char*);
extern M1LexResult m1_lexer_next(M1Lexer);
extern int64_t ps_kind(PS);
extern PR get_tok(PS);
extern PR parse_expr(PS);
extern PR parse_program(PS);
extern int64_t emit_module(int64_t);
extern int64_t m0_get(int64_t, int64_t);
extern int64_t m0_is_nil(int64_t);
extern int64_t m0_head(int64_t);

int main() {
    fprintf(stderr, "starting\n");
    char* filename = m0_get_env("M1_SOURCE");
    fprintf(stderr, "filename: %s\n", filename);

    char* src = m0_read_file(filename);
    fprintf(stderr, "file read ok: %p\n", src);
    fprintf(stderr, "content: %s\n", src);

    M1Lexer l = m1_lexer_init(src);
    fprintf(stderr, "lexer init ok, src=%p\n", l.src);

    M1LexResult r = m1_lexer_next(l);
    fprintf(stderr, "next token: kind=%lld\n", r.token.kind);

    PS s = {r.token, r.lexer, 0};
    fprintf(stderr, "calling parse_program...\n");

    PR pr = parse_program(s);
    fprintf(stderr, "parse_program returned, node=%lld\n", pr.node);

    int64_t mods = m0_get(pr.node, 3);
    fprintf(stderr, "mods=%lld\n", mods);
    if (m0_is_nil(mods) == 0) {
        fprintf(stderr, "calling emit_module...\n");
        int64_t m = m0_head(mods);
        fprintf(stderr, "module=%lld\n", m);
        return emit_module(m);
    }
    return pr.st.err;
}
