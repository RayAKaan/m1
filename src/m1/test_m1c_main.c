#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

extern M1Lexer m1_lexer_init(char* src);
extern M1LexResult m1_lexer_next(M1Lexer l);
extern char* m0_get_env(char*);
extern int64_t m0_print(char*);
extern int64_t m0_string_eq(char*, char*);
extern char* m0_read_file(char*);
extern PR parse_program(PS s);

int test_main() {
    printf("test starting\n");
    char* filename = m0_get_env("M1_SOURCE");
    printf("filename: %s\n", filename);

    char* src = m0_read_file(filename);
    printf("src loaded: %p\n", src);
    printf("src: %s\n", src);

    M1Lexer l = m1_lexer_init(src);
    printf("lexer init done\n");

    M1LexResult r = m1_lexer_next(l);
    printf("first token: kind=%lld line=%lld col=%lld\n", r.token.kind, r.token.line, r.token.col);

    PS s = {r.token, r.lexer, 0};
    printf("calling parse_program...\n");

    PR pr = parse_program(s);
    printf("parse_program returned, node=%lld\n", pr.node);

    return 0;
}
