#ifndef LEXER_H
#define LEXER_H

#include "arena.h"
#include "ast.h"

typedef enum {
    TOK_EOF,

    /* Keywords */
    TOK_MODULE,
    TOK_TYPE,
    TOK_FN,
    TOK_LET,
    TOK_MATCH,
    TOK_IF,
    TOK_ELSE,
    TOK_TRUE,
    TOK_FALSE,
    TOK_EXTERNAL,
    TOK_NOT,

    /* Symbols */
    TOK_ARROW,       /* -> */
    TOK_FAT_ARROW,   /* -> (match arm) — same token, context determines */
    TOK_BIDI,        /* <-> */
    TOK_LARROW,      /* <- */
    TOK_EQ,          /* = */
    TOK_EQEQ,        /* == */
    TOK_NEQ,         /* != */
    TOK_LT,
    TOK_GT,
    TOK_LE,          /* <= */
    TOK_GE,          /* >= */
    TOK_AND,         /* /\ */
    TOK_OR,          /* \/ */
    TOK_PIPE,        /* | */
    TOK_COLON,       /* : */
    TOK_COMMA,
    TOK_DOT,
    TOK_SEMI,
    TOK_AT,          /* @ */
    TOK_LBRACE,
    TOK_RBRACE,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACKET,
    TOK_RBRACKET,

    /* Operators */
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_PERCENT,

    /* Literals */
    TOK_INT,
    TOK_FLOAT,
    TOK_STRING,
    TOK_CHAR,

    /* Identifier */
    TOK_IDENT,

} TokenKind;

typedef struct {
    TokenKind kind;
    SrcLoc loc;
    union {
        long long int_val;
        double float_val;
        StringView str_val;
        char char_val;
    } data;
} Token;

typedef struct {
    const char *source;
    int source_len;
    const char *file;
    int pos;
    int line;
    int col;
    Arena *arena;
} Lexer;

void lexer_init(Lexer *l, const char *source, int source_len, const char *file, Arena *arena);
Token lexer_next(Lexer *l);
Token lexer_peek(Lexer *l);

#endif
