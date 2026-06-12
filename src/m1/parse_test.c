#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "lexer_out.c"
#include "phase_graph.c"
#include "m0_runtime_core.c"

int main(void) {
    char* src = "external \"func1\" : Int -> Int\n";
    M1Lexer l = m1_lexer_init(src);
    for (int i = 0; i < 10; i++) {
        M1LexResult r = m1_lexer_next(l);
        l = r.lexer;
        int64_t kind = (int64_t)r.token.kind.tag;
        printf("Token[%d]: kind=%lld line=%lld col=%lld str=%s\n", i, kind, r.token.line, r.token.col, r.token.str_val ? r.token.str_val : "(null)");
        if (kind == 0) break; // EOF
    }
    return 0;
}
