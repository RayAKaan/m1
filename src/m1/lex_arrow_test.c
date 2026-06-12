#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

/* We need m0_runtime functions - let's just forward-declare what we use */
int64_t m0_nil;
int64_t m0_char_at(const char* s, int64_t i);
const char* m0_substr(const char* s, int64_t start, int64_t end);
int64_t m0_string_eq(const char* a, const char* b);
int64_t m0_string_len(const char* s);
int64_t m0_print(const char* s);
int64_t m0_print_int(int64_t n);
int64_t m0_print_char(int64_t c);

/* Include lexer */
#include "lexer_out.c"

/* Include the M1 parser from gen1.c - but we need to include just the relevant parts */
/* Instead, let's just replicate the test logic */

#define TK_EXTERNAL 45
#define TK_IDENT 5
#define TK_STRING 3
#define TK_COLON 19
#define TK_ARROW 6
#define TK_INT 1

int main(void) {
    const char* src = "external \"func\" : Int -> Int";
    M1Lexer l = m1_lexer_init((char*)src);
    
    printf("Testing lexer on: %s\n", src);
    
    for (int i = 0; i < 15; i++) {
        M1LexResult r = m1_lexer_next(l);
        l = r.lexer;
        int64_t kind = (int64_t)r.token.kind.tag;
        printf("Token[%d]: kind=%lld '%s' str=%s\n", i, kind, 
               kind == 45 ? "EXTERNAL" :
               kind == 5 ? "IDENT" :
               kind == 3 ? "STRING" :
               kind == 19 ? "COLON" :
               kind == 6 ? "ARROW" :
               kind == 1 ? "INT" :
               kind == 0 ? "EOF" : "OTHER",
               r.token.str_val ? r.token.str_val : "(null)");
        if (kind == 0) break;
    }
    
    return 0;
}
