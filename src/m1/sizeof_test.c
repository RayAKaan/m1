#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
typedef struct M1Tk M1Tk;
struct M1Tk {
  int tag;
  union {
    char _unused[1];
  } data;
};
typedef struct {
  M1Tk kind;
  int64_t line;
  int64_t col;
  int64_t int_val;
  char* str_val;
} M1Token_lexer;
typedef struct { int64_t kind; int64_t line; int64_t col; int64_t int_val; char* str_val; } M1Token_parser;
int main(void) {
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(M1Tk) = %zu\n", sizeof(M1Tk));
    printf("offsetof(M1Token_lexer, kind) = %zu\n", offsetof(M1Token_lexer, kind));
    printf("offsetof(M1Token_lexer, line) = %zu\n", offsetof(M1Token_lexer, line));
    printf("sizeof(M1Token_lexer) = %zu\n", sizeof(M1Token_lexer));
    printf("sizeof(M1Token_parser) = %zu\n", sizeof(M1Token_parser));
    M1Tk tk = { .tag = 6, .data = {0} };
    int64_t as_int64 = 0;
    memcpy(&as_int64, &tk, sizeof(tk));
    printf("M1Tk tag=6 as int64_t = %lld (0x%llx)\n", (long long)as_int64, (unsigned long long)as_int64);
    M1Token_lexer lt = {{.tag = 6, .data = {0}}, 1, 2, 3, (char*)"hello"};
    M1Token_parser* pt = (M1Token_parser*)&lt;
    printf("Lexer token: kind.tag=%d, line=%lld, col=%lld\n", lt.kind.tag, lt.line, lt.col);
    printf("Parser read: kind=%lld, line=%lld, col=%lld\n", pt->kind, pt->line, pt->col);
    M1Tk tk2 = { .tag = 6, .data = {{0}} };
    int64_t v;
    memcpy(&v, &tk2, 8);
    printf("Direct value: %lld\n", (long long)v);
    return 0;
}
