#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "arena.h"
#include "lexer.h"

typedef struct {
    Lexer lexer;
    Token current;
    Arena *arena;
    int error_count;
} Parser;

void parser_init(Parser *p, const char *source, int source_len, const char *file, Arena *arena);
Node *parse_program(Parser *p);

#endif
