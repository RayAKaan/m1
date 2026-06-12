#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct { int64_t kind; int64_t line; int64_t col; int64_t int_val; char* str_val; } M1Token;
typedef struct { char* src; int64_t pos; int64_t line; int64_t col; } M1Lexer;
typedef struct { M1Token token; M1Lexer lexer; } M1LexResult;

extern M1Lexer m1_lexer_init(char* src);
extern M1LexResult m1_lexer_next(M1Lexer l);
extern char* m0_get_env(char*);
extern int64_t m0_print(char*);
extern int64_t m0_string_eq(char*, char*);

int main() {
    printf("test starting\n");
    char* filename = m0_get_env("M1_SOURCE");
    printf("filename: %s\n", filename);
    printf("string_eq: %lld\n", m0_string_eq("", ""));
    printf("string_eq2: %lld\n", m0_string_eq(filename, ""));
    printf("after string_eq\n");

    FILE* f = fopen(filename, "rb");
    if (!f) { printf("can't open file\n"); return 1; }
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buf = (char*)malloc((size_t)len + 1);
    fread(buf, 1, (size_t)len, f);
    buf[len] = '\0';
    fclose(f);
    printf("file content (%ld bytes):\n%s\n---\n", len, buf);

    M1Lexer l = m1_lexer_init(buf);
    printf("lexer initialized, src=%s\n", l.src);
    M1LexResult r = m1_lexer_next(l);
    printf("first token kind: %lld\n", r.token.kind);
    return 0;
}
