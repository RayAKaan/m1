#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

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
extern int64_t m0_is_nil(int64_t);
extern int64_t m0_get(int64_t, int64_t);
extern int64_t m0_head(int64_t);
extern int64_t m0_cons(int64_t, int64_t);
extern int64_t m0_nil;
extern int64_t rev(int64_t);
extern int64_t list_len(int64_t);
extern int64_t n_prog(char*, int64_t, int64_t, int64_t);
extern int64_t n_mod(char*, int64_t, int64_t, int64_t, int64_t);
extern PS ps_adv(PS);
extern PS ps_err(PS);
extern PR mk_pr(int64_t, PS);
extern PR parse_module(PS);
extern int64_t emit_module(int64_t);
extern char* ps_str(PS);

PR gather_modules(PS s, int64_t acc);

int main() {
    fprintf(stderr, "starting\n");
    char* filename = m0_get_env("M1_SOURCE");
    char* src = m0_read_file(filename);
    M1Lexer l = m1_lexer_init(src);
    M1LexResult r = m1_lexer_next(l);
    PS s = {r.token, r.lexer, 0};
    fprintf(stderr, "calling gather_modules directly\n");
    PR pr = gather_modules(s, m0_nil);
    fprintf(stderr, "gather_modules returned: node=%lld, err=%lld\n", pr.node, pr.st.err);
    return 0;
}
