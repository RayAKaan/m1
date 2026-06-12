#include <stdio.h>
#include <stdint.h>
#include "lexer_out.c"
int main(void) {
    char* src = "external \"func1\" : Int -> Int";
    M1Lexer l = m1_lexer_init(src);
    for (int i = 0; i < 10; i++) {
        M1LexResult r = m1_lexer_next(l);
        l = r.lexer;
        printf("Token: kind=%lld line=%lld col=%lld int_val=%lld str_val=%p\n", 
               (int64_t)r.token.kind.tag, r.token.line, r.token.col, r.token.int_val, r.token.str_val);
        if (r.token.kind.tag == 0) break; // EOF
    }
    return 0;
}
