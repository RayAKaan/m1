#include "lexer.h"
#include "error.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

void lexer_init(Lexer *l, const char *source, int source_len, const char *file, Arena *arena) {
    l->source = source;
    l->source_len = source_len;
    l->file = file;
    l->pos = 0;
    l->line = 1;
    l->col = 1;
    l->arena = arena;
}

static char peek(Lexer *l) {
    if (l->pos >= l->source_len) return '\0';
    return l->source[l->pos];
}

static char advance(Lexer *l) {
    char c = l->source[l->pos];
    l->pos++;
    if (c == '\n') {
        l->line++;
        l->col = 1;
    } else {
        l->col++;
    }
    return c;
}

static SrcLoc here(Lexer *l) {
    return (SrcLoc){ .file = l->file, .line = l->line, .col = l->col };
}

static int match(Lexer *l, char c) {
    if (l->pos < l->source_len && l->source[l->pos] == c) {
        advance(l);
        return 1;
    }
    return 0;
}

static void skip_whitespace_and_comments(Lexer *l) {
    while (l->pos < l->source_len) {
        char c = peek(l);
        if (isspace((unsigned char)c)) {
            advance(l);
        } else if (c == '-' && l->pos + 1 < l->source_len && l->source[l->pos + 1] == '-') {
            /* line comment */
            advance(l); advance(l);
            while (l->pos < l->source_len && peek(l) != '\n') advance(l);
        } else if (c == '{' && l->pos + 1 < l->source_len && l->source[l->pos + 1] == '-') {
            /* block comment {- -} */
            advance(l); advance(l);
            int depth = 1;
            while (l->pos < l->source_len && depth > 0) {
                if (peek(l) == '{' && l->pos + 1 < l->source_len && l->source[l->pos + 1] == '-') {
                    advance(l); advance(l);
                    depth++;
                } else if (peek(l) == '-' && l->pos + 1 < l->source_len && l->source[l->pos + 1] == '}') {
                    advance(l); advance(l);
                    depth--;
                } else {
                    advance(l);
                }
            }
        } else {
            break;
        }
    }
}

typedef struct {
    const char *text;
    TokenKind kind;
} Keyword;

static Keyword keywords[] = {
    {"module",   TOK_MODULE},
    {"type",     TOK_TYPE},
    {"fn",       TOK_FN},
    {"let",      TOK_LET},
    {"match",    TOK_MATCH},
    {"if",       TOK_IF},
    {"else",     TOK_ELSE},
    {"true",     TOK_TRUE},
    {"false",    TOK_FALSE},
    {"external", TOK_EXTERNAL},
    {"not",      TOK_NOT},
    {NULL,       TOK_EOF},
};

static Token make_ident_or_keyword(Lexer *l, int start) {
    while (l->pos < l->source_len && (isalnum((unsigned char)peek(l)) || peek(l) == '_')) {
        advance(l);
    }
    int len = l->pos - start;
    const char *text = l->source + start;
    for (Keyword *kw = keywords; kw->text; kw++) {
        if ((int)strlen(kw->text) == len && strncmp(kw->text, text, len) == 0) {
            Token t;
            t.kind = kw->kind;
            t.loc = (SrcLoc){ .file = l->file, .line = l->line, .col = l->col - len };
            return t;
        }
    }
    Token t;
    t.kind = TOK_IDENT;
    t.loc = (SrcLoc){ .file = l->file, .line = l->line, .col = l->col - len };
    t.data.str_val = (StringView){ .data = text, .len = len };
    return t;
}

static Token make_string(Lexer *l) {
    SrcLoc loc = here(l);
    advance(l); /* skip opening " */
    int start = l->pos;
    /* First pass: count interpreted length */
    int ilen = 0;
    while (l->pos < l->source_len && l->source[l->pos] != '"') {
        if (l->source[l->pos] == '\\') {
            l->pos++;
            if (l->pos < l->source_len) {
                switch (l->source[l->pos]) {
                    case 'n': case 't': case '\\': case '"': break;
                    default: break;
                }
                l->pos++;
            }
        } else {
            l->pos++;
        }
        ilen++;
    }
    /* Allocate and fill */
    char *buf = arena_alloc(l->arena, ilen + 1);
    int di = 0;
    int i = start;
    while (i < l->source_len && l->source[i] != '"') {
        if (l->source[i] == '\\') {
            i++;
            if (i < l->source_len) {
                switch (l->source[i]) {
                    case 'n': buf[di++] = '\n'; break;
                    case 't': buf[di++] = '\t'; break;
                    case '\\': buf[di++] = '\\'; break;
                    case '"': buf[di++] = '"'; break;
                    default: buf[di++] = l->source[i]; break;
                }
                i++;
            }
        } else {
            buf[di++] = l->source[i++];
        }
    }
    buf[ilen] = '\0';
    l->pos = i + 1; /* skip closing " */
    Token t;
    t.kind = TOK_STRING;
    t.loc = loc;
    t.data.str_val = (StringView){ .data = buf, .len = ilen };
    return t;
}

static Token make_char(Lexer *l) {
    SrcLoc loc = here(l);
    advance(l); /* skip opening ' */
    char val;
    if (peek(l) == '\\') {
        advance(l);
        switch (peek(l)) {
            case 'n':  val = '\n'; break;
            case 't':  val = '\t'; break;
            case 'r':  val = '\r'; break;
            case '\\': val = '\\'; break;
            case '\'': val = '\''; break;
            case '0':  val = '\0'; break;
            default:   val = peek(l); break;
        }
        advance(l);
    } else {
        val = peek(l);
        advance(l);
    }
    advance(l); /* skip closing ' */
    Token t;
    t.kind = TOK_CHAR;
    t.loc = loc;
    t.data.char_val = val;
    return t;
}

static Token make_number(Lexer *l) {
    SrcLoc loc = here(l);
    int start = l->pos;
    while (l->pos < l->source_len && isdigit((unsigned char)peek(l))) advance(l);
    if (l->pos < l->source_len && peek(l) == '.' &&
        l->pos + 1 < l->source_len && isdigit((unsigned char)l->source[l->pos + 1])) {
        advance(l); /* skip . */
        while (l->pos < l->source_len && isdigit((unsigned char)peek(l))) advance(l);
        int len = l->pos - start;
        Token t;
        t.kind = TOK_FLOAT;
        t.loc = loc;
        char buf[64];
        if (len >= (int)sizeof(buf)) len = (int)sizeof(buf) - 1;
        memcpy(buf, l->source + start, len);
        buf[len] = '\0';
        t.data.float_val = strtod(buf, NULL);
        return t;
    }
    int len = l->pos - start;
    Token t;
    t.kind = TOK_INT;
    t.loc = loc;
    char buf[64];
    if (len >= (int)sizeof(buf)) len = (int)sizeof(buf) - 1;
    memcpy(buf, l->source + start, len);
    buf[len] = '\0';
    t.data.int_val = strtoll(buf, NULL, 10);
    return t;
}

Token lexer_next(Lexer *l) {
    skip_whitespace_and_comments(l);
    if (l->pos >= l->source_len) {
        Token t;
        t.kind = TOK_EOF;
        t.loc = here(l);
        return t;
    }

    SrcLoc loc = here(l);
    char c = peek(l);

    /* String literal */
    if (c == '"') return make_string(l);

    /* Char literal */
    if (c == '\'') return make_char(l);

    /* Number literal */
    if (isdigit((unsigned char)c)) return make_number(l);

    /* Identifier or keyword */
    if (isalpha((unsigned char)c) || c == '_') return make_ident_or_keyword(l, l->pos);

    /* Two-character tokens (ordered by priority) */
    advance(l);
    switch (c) {
        case '-':
            if (match(l, '>'))  { Token t; t.kind = TOK_ARROW;   t.loc = loc; return t; }
            if (match(l, '-'))  { /* shouldn't reach here, handled in comments */ break; }
            { Token t; t.kind = TOK_MINUS; t.loc = loc; return t; }
        case '<':
            if (match(l, '-'))  { Token t; t.kind = TOK_LARROW;  t.loc = loc; return t; }
            if (match(l, '>'))  { Token t; t.kind = TOK_BIDI;    t.loc = loc; return t; }
            if (match(l, '='))  { Token t; t.kind = TOK_LE;      t.loc = loc; return t; }
            { Token t; t.kind = TOK_LT; t.loc = loc; return t; }
        case '>':
            if (match(l, '='))  { Token t; t.kind = TOK_GE;      t.loc = loc; return t; }
            { Token t; t.kind = TOK_GT; t.loc = loc; return t; }
        case '!':
            if (match(l, '='))  { Token t; t.kind = TOK_NEQ;     t.loc = loc; return t; }
            break;
        case '=':
            if (match(l, '='))  { Token t; t.kind = TOK_EQEQ;    t.loc = loc; return t; }
            { Token t; t.kind = TOK_EQ; t.loc = loc; return t; }
        case '/':
            if (match(l, '\\')) { Token t; t.kind = TOK_AND;      t.loc = loc; return t; }
            { Token t; t.kind = TOK_SLASH; t.loc = loc; return t; }
        case '\\':
            if (match(l, '/'))  { Token t; t.kind = TOK_OR;       t.loc = loc; return t; }
            break;
        case '|':
            { Token t; t.kind = TOK_PIPE; t.loc = loc; return t; }
        case ':':
            { Token t; t.kind = TOK_COLON; t.loc = loc; return t; }
        case ',':
            { Token t; t.kind = TOK_COMMA; t.loc = loc; return t; }
        case '.':
            { Token t; t.kind = TOK_DOT; t.loc = loc; return t; }
        case ';':
            { Token t; t.kind = TOK_SEMI; t.loc = loc; return t; }
        case '@':
            { Token t; t.kind = TOK_AT; t.loc = loc; return t; }
        case '{':
            { Token t; t.kind = TOK_LBRACE; t.loc = loc; return t; }
        case '}':
            { Token t; t.kind = TOK_RBRACE; t.loc = loc; return t; }
        case '(':
            { Token t; t.kind = TOK_LPAREN; t.loc = loc; return t; }
        case ')':
            { Token t; t.kind = TOK_RPAREN; t.loc = loc; return t; }
        case '[':
            { Token t; t.kind = TOK_LBRACKET; t.loc = loc; return t; }
        case ']':
            { Token t; t.kind = TOK_RBRACKET; t.loc = loc; return t; }
        case '+':
            { Token t; t.kind = TOK_PLUS; t.loc = loc; return t; }
        case '*':
            { Token t; t.kind = TOK_STAR; t.loc = loc; return t; }
        case '%':
            { Token t; t.kind = TOK_PERCENT; t.loc = loc; return t; }
    }

    Token t;
    t.kind = TOK_EOF;
    t.loc = loc;
    error_report(PHASE_LEXER, loc, "unexpected character '%c'", c);
    return t;
}

Token lexer_peek(Lexer *l) {
    Lexer save = *l;
    Token t = lexer_next(l);
    *l = save;
    return t;
}
