#include "parser.h"
#include "error.h"
#include <stdlib.h>
#include <string.h>

/* ---- Scratch vectors (arena-allocated, waste accepted) ---- */

typedef struct { Node **data; int count; int cap; } NodeVec;
typedef struct { Param *data; int count; int cap; } ParamVec;
typedef struct { MatchArm *data; int count; int cap; } ArmVec;
typedef struct { FieldInit *data; int count; int cap; } FieldVec;
typedef struct { FieldPat *data; int count; int cap; } FieldPatVec;
typedef struct { SumVariant *data; int count; int cap; } VariantVec;
typedef struct { Pattern **data; int count; int cap; } PatternVec;

#define VEC_PUSH(a, v, item, T) do { \
    if ((v).count >= (v).cap) { \
        int nc = (v).cap ? (v).cap * 2 : 8; \
        T *nd = arena_alloc((a), sizeof(T) * nc); \
        if ((v).data) memcpy(nd, (v).data, sizeof(T) * (v).count); \
        (v).data = nd; \
        (v).cap = nc; \
    } \
    (v).data[(v).count++] = (item); \
} while (0)

/* ---- Parser state helpers ---- */

static TokenKind peek(Parser *p) {
    return p->current.kind;
}

static Token advance(Parser *p) {
    Token t = p->current;
    p->current = lexer_next(&p->lexer);
    return t;
}

static int match_tok(Parser *p, TokenKind k) {
    if (peek(p) == k) { advance(p); return 1; }
    return 0;
}

static Token expect(Parser *p, TokenKind k, const char *msg) {
    if (peek(p) == k) return advance(p);
    error_report(PHASE_PARSER, p->current.loc, "expected %s, got token %d", msg, peek(p));
    p->error_count++;
    return advance(p);
}

static SrcLoc here(Parser *p) {
    return p->current.loc;
}

/* ---- Node constructors ---- */

static Node *alloc_node(Parser *p, NodeKind kind, SrcLoc loc) {
    Node *n = arena_alloc(p->arena, sizeof(Node));
    memset(n, 0, sizeof(Node));
    n->kind = kind;
    n->loc = loc;
    return n;
}

static Node *make_int(Parser *p, long long val, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_LITERAL_INT, loc);
    n->data.int_val = val;
    return n;
}

static Node *make_float(Parser *p, double val, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_LITERAL_FLOAT, loc);
    n->data.float_val = val;
    return n;
}

static Node *make_string(Parser *p, StringView val, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_LITERAL_STRING, loc);
    n->data.str_val = val;
    return n;
}

static Node *make_char(Parser *p, char val, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_LITERAL_CHAR, loc);
    n->data.char_val = val;
    return n;
}

static Node *make_bool(Parser *p, int val, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_LITERAL_BOOL, loc);
    n->data.bool_val = val;
    return n;
}

static Node *make_unit(Parser *p, SrcLoc loc) {
    return alloc_node(p, NODE_LITERAL_UNIT, loc);
}

static Node *make_name(Parser *p, StringView name, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_NAME, loc);
    n->data.name_val = name;
    return n;
}

static Node *make_binary(Parser *p, BinaryOp op, Node *left, Node *right, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_BINARY, loc);
    n->data.binary.op = op;
    n->data.binary.left = left;
    n->data.binary.right = right;
    return n;
}

static Node *make_not(Parser *p, Node *expr, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_NOT, loc);
    n->data.not_.expr = expr;
    return n;
}

static Node *make_field_access(Parser *p, Node *expr, StringView field, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_FIELD_ACCESS, loc);
    n->data.field_access.expr = expr;
    n->data.field_access.field = field;
    return n;
}

static Node *make_call(Parser *p, Node *expr, Node **args, int arg_count, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_CALL, loc);
    n->data.call.expr = expr;
    n->data.call.args = args;
    n->data.call.arg_count = arg_count;
    return n;
}

static Node *make_annot(Parser *p, Node *expr, Node *type, SrcLoc loc) {
    Node *n = alloc_node(p, NODE_ANNOT, loc);
    n->data.annot.expr = expr;
    n->data.annot.type = type;
    return n;
}

/* ---- Type expression parsing ---- */

static Node *parse_type_expr(Parser *p);

static Node *parse_type_atom(Parser *p) {
    SrcLoc loc = here(p);

    if (peek(p) == TOK_IDENT) {
        Token t = advance(p);
        return make_name(p, t.data.str_val, loc);
    }

    if (peek(p) == TOK_LBRACE) {
        advance(p);
        FieldVec fields = {NULL, 0, 0};
        while (peek(p) != TOK_RBRACE && peek(p) != TOK_EOF) {
            Token name = expect(p, TOK_IDENT, "field name");
            expect(p, TOK_COLON, ":");
            Node *type = parse_type_expr(p);
            FieldInit f = { .name = name.data.str_val, .value = type };
            VEC_PUSH(p->arena, fields, f, FieldInit);
            if (!match_tok(p, TOK_COMMA)) break;
        }
        expect(p, TOK_RBRACE, "}");
        Node *n = alloc_node(p, NODE_RECORD, loc);
        n->data.record.fields = fields.data;
        n->data.record.count = fields.count;
        return n;
    }

    if (peek(p) == TOK_PIPE) {
        advance(p);
        VariantVec variants = {NULL, 0, 0};
        while (1) {
            Token name = expect(p, TOK_IDENT, "constructor name");
            Node **types = NULL;
            int type_count = 0;
            if (match_tok(p, TOK_LPAREN)) {
                NodeVec tv = {NULL, 0, 0};
                while (peek(p) != TOK_RPAREN && peek(p) != TOK_EOF) {
                    VEC_PUSH(p->arena, tv, parse_type_expr(p), Node*);
                    if (!match_tok(p, TOK_COMMA)) break;
                }
                expect(p, TOK_RPAREN, ")");
                types = tv.data;
                type_count = tv.count;
            }
            SumVariant v = { .name = name.data.str_val, .types = types, .type_count = type_count };
            VEC_PUSH(p->arena, variants, v, SumVariant);
            if (!match_tok(p, TOK_PIPE)) break;
        }
        Node *n = alloc_node(p, NODE_SUM_TYPE, loc);
        n->data.sum_type.variants = variants.data;
        n->data.sum_type.count = variants.count;
        return n;
    }

    if (peek(p) == TOK_LPAREN) {
        advance(p);
        if (peek(p) == TOK_RPAREN) { advance(p); return make_name(p, (StringView){"Unit", 4}, loc); }
        Node *inner = parse_type_expr(p);
        expect(p, TOK_RPAREN, ")");
        Node *n = alloc_node(p, NODE_GROUP, loc);
        n->data.group.expr = inner;
        return n;
    }

    error_report(PHASE_PARSER, here(p), "expected type expression, got token %d", peek(p));
    p->error_count++;
    return alloc_node(p, NODE_LITERAL_UNIT, loc);
}

static Node *parse_type_app(Parser *p) {
    SrcLoc loc = here(p);
    Node *atom = parse_type_atom(p);

    if (peek(p) == TOK_LPAREN) {
        advance(p);
        NodeVec args = {NULL, 0, 0};
        while (peek(p) != TOK_RPAREN && peek(p) != TOK_EOF) {
            VEC_PUSH(p->arena, args, parse_type_expr(p), Node*);
            if (!match_tok(p, TOK_COMMA)) break;
        }
        expect(p, TOK_RPAREN, ")");
        return make_call(p, atom, args.data, args.count, loc);
    }

    return atom;
}

static Node *parse_type_arrow(Parser *p) {
    SrcLoc loc = here(p);
    Node *left = parse_type_app(p);

    if (peek(p) == TOK_ARROW) {
        advance(p);
        Node *right = parse_type_arrow(p);
        return make_binary(p, OP_IMPL, left, right, loc);
    }

    return left;
}

static Node *parse_type_expr(Parser *p) {
    return parse_type_arrow(p);
}

/* ---- Pattern parsing ---- */

static Pattern *parse_pattern(Parser *p);

static Pattern *alloc_pattern(Parser *p, PatternKind kind, SrcLoc loc) {
    Pattern *pat = arena_alloc(p->arena, sizeof(Pattern));
    memset(pat, 0, sizeof(Pattern));
    pat->kind = kind;
    pat->loc = loc;
    return pat;
}

static Pattern *parse_pattern_atom(Parser *p) {
    SrcLoc loc = here(p);

    if (peek(p) == TOK_INT) {
        Token t = advance(p);
        Pattern *pat = alloc_pattern(p, PATTERN_LITERAL, loc);
        pat->data.lit.literal = make_int(p, t.data.int_val, loc);
        return pat;
    }
    if (peek(p) == TOK_FLOAT) {
        Token t = advance(p);
        Pattern *pat = alloc_pattern(p, PATTERN_LITERAL, loc);
        pat->data.lit.literal = make_float(p, t.data.float_val, loc);
        return pat;
    }
    if (peek(p) == TOK_STRING) {
        Token t = advance(p);
        Pattern *pat = alloc_pattern(p, PATTERN_LITERAL, loc);
        pat->data.lit.literal = make_string(p, t.data.str_val, loc);
        return pat;
    }
    if (peek(p) == TOK_CHAR) {
        Token t = advance(p);
        Pattern *pat = alloc_pattern(p, PATTERN_LITERAL, loc);
        pat->data.lit.literal = make_char(p, t.data.char_val, loc);
        return pat;
    }
    if (peek(p) == TOK_TRUE) {
        advance(p);
        Pattern *pat = alloc_pattern(p, PATTERN_LITERAL, loc);
        pat->data.lit.literal = make_bool(p, 1, loc);
        return pat;
    }
    if (peek(p) == TOK_FALSE) {
        advance(p);
        Pattern *pat = alloc_pattern(p, PATTERN_LITERAL, loc);
        pat->data.lit.literal = make_bool(p, 0, loc);
        return pat;
    }
    if (peek(p) == TOK_LPAREN) {
        advance(p);
        if (peek(p) == TOK_RPAREN) { advance(p);
            Pattern *pat = alloc_pattern(p, PATTERN_LITERAL, loc);
            pat->data.lit.literal = make_unit(p, loc);
            return pat;
        }
        /* not () in pattern context - error, fall through */
        p->error_count++;
        return alloc_pattern(p, PATTERN_WILDCARD, loc);
    }

    if (peek(p) == TOK_LBRACE) {
        advance(p);
        FieldPatVec fields = {NULL, 0, 0};
        while (peek(p) != TOK_RBRACE && peek(p) != TOK_EOF) {
            Token name = expect(p, TOK_IDENT, "field name");
            expect(p, TOK_EQ, "=");
            Pattern *inner = parse_pattern(p);
            FieldPat f = { .name = name.data.str_val, .pattern = inner };
            VEC_PUSH(p->arena, fields, f, FieldPat);
            if (!match_tok(p, TOK_COMMA)) break;
        }
        expect(p, TOK_RBRACE, "}");
        Pattern *pat = alloc_pattern(p, PATTERN_RECORD, loc);
        pat->data.record.fields = fields.data;
        pat->data.record.count = fields.count;
        return pat;
    }

    if (peek(p) == TOK_IDENT) {
        Token t = advance(p);
        StringView name = t.data.str_val;

        if (name.len == 1 && name.data[0] == '_') {
            return alloc_pattern(p, PATTERN_WILDCARD, loc);
        }

        if (peek(p) == TOK_LPAREN) {
            advance(p);
            PatternVec pv = {NULL, 0, 0};
            while (peek(p) != TOK_RPAREN && peek(p) != TOK_EOF) {
                VEC_PUSH(p->arena, pv, parse_pattern(p), Pattern*);
                if (!match_tok(p, TOK_COMMA)) break;
            }
            expect(p, TOK_RPAREN, ")");
            Pattern *pat = alloc_pattern(p, PATTERN_CONSTRUCTOR, loc);
            pat->data.constructor.name = name;
            pat->data.constructor.args = pv.data;
            pat->data.constructor.arg_count = pv.count;
            return pat;
        }

        Pattern *pat = alloc_pattern(p, PATTERN_NAME, loc);
        pat->data.name.name = name;
        return pat;
    }

    error_report(PHASE_PARSER, here(p), "expected pattern, got token %d", peek(p));
    p->error_count++;
    return alloc_pattern(p, PATTERN_WILDCARD, loc);
}

static Pattern *parse_pattern(Parser *p) {
    SrcLoc loc = here(p);
    Pattern *left = parse_pattern_atom(p);

    if (peek(p) == TOK_PIPE) {
        advance(p);
        Pattern *right = parse_pattern(p);
        Pattern *pat = alloc_pattern(p, PATTERN_OR, loc);
        pat->data.or.left = left;
        pat->data.or.right = right;
        return pat;
    }

    return left;
}

/* ---- Expression parsing ---- */

static Node *parse_expr(Parser *p);
static Node *parse_impl(Parser *p);

static Node *parse_atom(Parser *p) {
    SrcLoc loc = here(p);

    if (peek(p) == TOK_INT) {
        Token t = advance(p);
        return make_int(p, t.data.int_val, loc);
    }
    if (peek(p) == TOK_FLOAT) {
        Token t = advance(p);
        return make_float(p, t.data.float_val, loc);
    }
    if (peek(p) == TOK_STRING) {
        Token t = advance(p);
        return make_string(p, t.data.str_val, loc);
    }
    if (peek(p) == TOK_CHAR) {
        Token t = advance(p);
        return make_char(p, t.data.char_val, loc);
    }
    if (peek(p) == TOK_TRUE) {
        advance(p);
        return make_bool(p, 1, loc);
    }
    if (peek(p) == TOK_FALSE) {
        advance(p);
        return make_bool(p, 0, loc);
    }
    if (peek(p) == TOK_LPAREN) {
        advance(p);
        if (peek(p) == TOK_RPAREN) { advance(p); return make_unit(p, loc); }
        Node *inner = parse_expr(p);
        expect(p, TOK_RPAREN, ")");
        Node *n = alloc_node(p, NODE_GROUP, loc);
        n->data.group.expr = inner;
        return n;
    }

    if (peek(p) == TOK_IDENT) {
        Token t = advance(p);
        return make_name(p, t.data.str_val, loc);
    }

    if (peek(p) == TOK_LET) {
        advance(p);
        Token name = expect(p, TOK_IDENT, "variable name");
        expect(p, TOK_COLON, ":");
        Node *type = parse_type_expr(p);
        expect(p, TOK_EQ, "=");
        Node *value = parse_expr(p);
        expect(p, TOK_SEMI, ";");
        Node *body = parse_expr(p);
        Node *n = alloc_node(p, NODE_LET, loc);
        n->data.let.name = name.data.str_val;
        n->data.let.type = type;
        n->data.let.value = value;
        n->data.let.body = body;
        return n;
    }

    if (peek(p) == TOK_FN) {
        advance(p);
        expect(p, TOK_LPAREN, "(");
        ParamVec params = {NULL, 0, 0};
        while (peek(p) != TOK_RPAREN && peek(p) != TOK_EOF) {
            Token pname = expect(p, TOK_IDENT, "parameter name");
            expect(p, TOK_COLON, ":");
            Node *ptype = parse_type_expr(p);
            Param param = { .name = pname.data.str_val, .type = ptype };
            VEC_PUSH(p->arena, params, param, Param);
            if (!match_tok(p, TOK_COMMA)) break;
        }
        expect(p, TOK_RPAREN, ")");
        expect(p, TOK_ARROW, "->");
        Node *ret_type = parse_type_expr(p);
        expect(p, TOK_LBRACE, "{");
        Node *body = parse_expr(p);
        expect(p, TOK_RBRACE, "}");
        Node *n = alloc_node(p, NODE_LAMBDA, loc);
        n->data.lambda.params = params.data;
        n->data.lambda.param_count = params.count;
        n->data.lambda.ret_type = ret_type;
        n->data.lambda.body = body;
        return n;
    }

    if (peek(p) == TOK_MATCH) {
        advance(p);
        Node *scrutinee = parse_expr(p);
        expect(p, TOK_LBRACE, "{");
        ArmVec arms = {NULL, 0, 0};
        while (peek(p) != TOK_RBRACE && peek(p) != TOK_EOF) {
            Pattern *pat = parse_pattern(p);
            expect(p, TOK_ARROW, "->");
            Node *body = parse_expr(p);
            expect(p, TOK_SEMI, ";");
            MatchArm arm = { .pattern = pat, .body = body };
            VEC_PUSH(p->arena, arms, arm, MatchArm);
        }
        expect(p, TOK_RBRACE, "}");
        Node *n = alloc_node(p, NODE_MATCH, loc);
        n->data.match.scrutinee = scrutinee;
        n->data.match.arms = arms.data;
        n->data.match.arm_count = arms.count;
        return n;
    }

    if (peek(p) == TOK_IF) {
        advance(p);
        Node *cond = parse_expr(p);
        expect(p, TOK_LBRACE, "{");
        Node *then_expr = parse_expr(p);
        expect(p, TOK_RBRACE, "}");
        Node *else_expr = NULL;
        if (match_tok(p, TOK_ELSE)) {
            if (peek(p) == TOK_LBRACE) {
                expect(p, TOK_LBRACE, "{");
                else_expr = parse_expr(p);
                expect(p, TOK_RBRACE, "}");
            } else {
                else_expr = parse_expr(p);
            }
        }
        Node *n = alloc_node(p, NODE_IF, loc);
        n->data.if_.cond = cond;
        n->data.if_.then_expr = then_expr;
        n->data.if_.else_expr = else_expr;
        return n;
    }

    if (peek(p) == TOK_LBRACE) {
        advance(p);
        FieldVec fields = {NULL, 0, 0};
        while (peek(p) != TOK_RBRACE && peek(p) != TOK_EOF) {
            Token name = expect(p, TOK_IDENT, "field name");
            expect(p, TOK_EQ, "=");
            Node *value = parse_impl(p);
            FieldInit f = { .name = name.data.str_val, .value = value };
            VEC_PUSH(p->arena, fields, f, FieldInit);
            if (!match_tok(p, TOK_COMMA)) break;
        }
        expect(p, TOK_RBRACE, "}");
        Node *n = alloc_node(p, NODE_RECORD, loc);
        n->data.record.fields = fields.data;
        n->data.record.count = fields.count;
        return n;
    }

    if (peek(p) == TOK_LBRACKET) {
        advance(p);
        NodeVec elems = {NULL, 0, 0};
        while (peek(p) != TOK_RBRACKET && peek(p) != TOK_EOF) {
            VEC_PUSH(p->arena, elems, parse_impl(p), Node*);
            if (!match_tok(p, TOK_COMMA)) break;
        }
        expect(p, TOK_RBRACKET, "]");
        Node *n = alloc_node(p, NODE_LIST, loc);
        n->data.list.elements = elems.data;
        n->data.list.count = elems.count;
        return n;
    }

    error_report(PHASE_PARSER, here(p), "expected expression, got token %d", peek(p));
    p->error_count++;
    return make_unit(p, loc);
}

static Node *parse_postfix(Parser *p) {
    Node *expr = parse_atom(p);

    while (1) {
        SrcLoc loc = here(p);
        if (peek(p) == TOK_DOT) {
            advance(p);
            Token field = expect(p, TOK_IDENT, "field name");
            expr = make_field_access(p, expr, field.data.str_val, loc);
        } else if (peek(p) == TOK_LPAREN) {
            advance(p);
            NodeVec args = {NULL, 0, 0};
            while (peek(p) != TOK_RPAREN && peek(p) != TOK_EOF) {
                VEC_PUSH(p->arena, args, parse_impl(p), Node*);
                if (!match_tok(p, TOK_COMMA)) break;
            }
            expect(p, TOK_RPAREN, ")");
            expr = make_call(p, expr, args.data, args.count, loc);
        } else if (peek(p) == TOK_COLON) {
            advance(p);
            Node *type = parse_type_expr(p);
            expr = make_annot(p, expr, type, loc);
        } else {
            break;
        }
    }

    return expr;
}

static Node *parse_unary(Parser *p) {
    SrcLoc loc = here(p);

    if (peek(p) == TOK_NOT) {
        advance(p);
        Node *expr = parse_unary(p);
        return make_not(p, expr, loc);
    }

    if (peek(p) == TOK_MINUS) {
        advance(p);
        Node *expr = parse_unary(p);
        Node *zero = make_int(p, 0, loc);
        return make_binary(p, OP_SUB, zero, expr, loc);
    }

    return parse_postfix(p);
}

static Node *parse_multiplicative(Parser *p) {
    SrcLoc loc = here(p);
    Node *left = parse_unary(p);

    while (peek(p) == TOK_STAR || peek(p) == TOK_SLASH || peek(p) == TOK_PERCENT) {
        BinaryOp op;
        if (peek(p) == TOK_STAR) op = OP_MUL;
        else if (peek(p) == TOK_SLASH) op = OP_DIV;
        else op = OP_MOD;
        advance(p);
        Node *right = parse_unary(p);
        left = make_binary(p, op, left, right, loc);
    }

    return left;
}

static Node *parse_additive(Parser *p) {
    SrcLoc loc = here(p);
    Node *left = parse_multiplicative(p);

    while (peek(p) == TOK_PLUS || peek(p) == TOK_MINUS) {
        BinaryOp op = (peek(p) == TOK_PLUS) ? OP_ADD : OP_SUB;
        advance(p);
        Node *right = parse_multiplicative(p);
        left = make_binary(p, op, left, right, loc);
    }

    return left;
}

static Node *parse_comparison(Parser *p) {
    SrcLoc loc = here(p);
    Node *left = parse_additive(p);

    switch (peek(p)) {
        case TOK_EQEQ: { advance(p); Node *r = parse_additive(p); return make_binary(p, OP_EQ, left, r, loc); }
        case TOK_NEQ:  { advance(p); Node *r = parse_additive(p); return make_binary(p, OP_NEQ, left, r, loc); }
        case TOK_LT:   { advance(p); Node *r = parse_additive(p); return make_binary(p, OP_LT, left, r, loc); }
        case TOK_GT:   { advance(p); Node *r = parse_additive(p); return make_binary(p, OP_GT, left, r, loc); }
        case TOK_LE:   { advance(p); Node *r = parse_additive(p); return make_binary(p, OP_LE, left, r, loc); }
        case TOK_GE:   { advance(p); Node *r = parse_additive(p); return make_binary(p, OP_GE, left, r, loc); }
        default: return left;
    }
}

static Node *parse_and(Parser *p) {
    SrcLoc loc = here(p);
    Node *left = parse_comparison(p);

    while (peek(p) == TOK_AND) {
        advance(p);
        Node *right = parse_comparison(p);
        left = make_binary(p, OP_AND, left, right, loc);
    }

    return left;
}

static Node *parse_or(Parser *p) {
    SrcLoc loc = here(p);
    Node *left = parse_and(p);

    while (peek(p) == TOK_OR) {
        advance(p);
        Node *right = parse_and(p);
        left = make_binary(p, OP_OR, left, right, loc);
    }

    return left;
}

static Node *parse_impl(Parser *p) {
    SrcLoc loc = here(p);
    Node *left = parse_or(p);

    if (peek(p) == TOK_ARROW) {
        advance(p);
        Node *right = parse_impl(p);
        return make_binary(p, OP_IMPL, left, right, loc);
    }

    return left;
}

static Node *parse_expr(Parser *p) {
    return parse_impl(p);
}

/* ---- Declaration parsing ---- */

static Node *parse_declaration(Parser *p) {
    SrcLoc loc = here(p);

    if (peek(p) == TOK_TYPE) {
        advance(p);
        Token name = expect(p, TOK_IDENT, "type name");
        expect(p, TOK_EQ, "=");
        Node *type = parse_type_expr(p);
        Node *n = alloc_node(p, NODE_TYPE_DECL, loc);
        n->data.type_decl.name = name.data.str_val;
        n->data.type_decl.type = type;
        return n;
    }

    if (peek(p) == TOK_FN) {
        advance(p);
        Token name = expect(p, TOK_IDENT, "function name");
        expect(p, TOK_LPAREN, "(");
        ParamVec params = {NULL, 0, 0};
        while (peek(p) != TOK_RPAREN && peek(p) != TOK_EOF) {
            Token pname = expect(p, TOK_IDENT, "parameter name");
            expect(p, TOK_COLON, ":");
            Node *ptype = parse_type_expr(p);
            Param param = { .name = pname.data.str_val, .type = ptype };
            VEC_PUSH(p->arena, params, param, Param);
            if (!match_tok(p, TOK_COMMA)) break;
        }
        expect(p, TOK_RPAREN, ")");
        expect(p, TOK_ARROW, "->");
        Node *ret_type = parse_type_expr(p);
        expect(p, TOK_LBRACE, "{");
        Node *body = parse_expr(p);
        expect(p, TOK_RBRACE, "}");
        Node *n = alloc_node(p, NODE_FN_DECL, loc);
        n->data.fn_decl.name = name.data.str_val;
        n->data.fn_decl.params = params.data;
        n->data.fn_decl.param_count = params.count;
        n->data.fn_decl.ret_type = ret_type;
        n->data.fn_decl.body = body;
        return n;
    }

    if (peek(p) == TOK_EXTERNAL) {
        advance(p);
        Token c_name = expect(p, TOK_STRING, "C function name");
        expect(p, TOK_COLON, ":");
        Node *type = parse_type_expr(p);
        Node *n = alloc_node(p, NODE_EXTERN_DECL, loc);
        n->data.extern_decl.name = c_name.data.str_val;
        n->data.extern_decl.type = type;
        return n;
    }

    if (peek(p) == TOK_LET) {
        advance(p);
        Token name = expect(p, TOK_IDENT, "variable name");
        expect(p, TOK_COLON, ":");
        Node *type = parse_type_expr(p);
        expect(p, TOK_EQ, "=");
        Node *body = parse_expr(p);
        Node *n = alloc_node(p, NODE_PROP_DECL, loc);
        n->data.prop_decl.name = name.data.str_val;
        n->data.prop_decl.type = type;
        n->data.prop_decl.body = body;
        n->data.prop_decl.bidi = 0;
        return n;
    }

    if (peek(p) == TOK_IDENT) {
        Token name = advance(p);
        expect(p, TOK_COLON, ":");
        Node *type = parse_type_expr(p);
        Node *body = NULL;
        if (match_tok(p, TOK_LARROW)) {
            body = parse_expr(p);
        }
        Node *n = alloc_node(p, NODE_PROP_DECL, loc);
        n->data.prop_decl.name = name.data.str_val;
        n->data.prop_decl.type = type;
        n->data.prop_decl.body = body;
        n->data.prop_decl.bidi = 0;
        return n;
    }

    error_report(PHASE_PARSER, here(p), "expected declaration, got token %d", peek(p));
    p->error_count++;
    advance(p);
    return alloc_node(p, NODE_LITERAL_UNIT, loc);
}

/* ---- Module and program ---- */

static Node *parse_module(Parser *p) {
    SrcLoc loc = here(p);
    expect(p, TOK_MODULE, "'module'");
    Token name = expect(p, TOK_IDENT, "module name");
    expect(p, TOK_LBRACE, "{");

    NodeVec decls = {NULL, 0, 0};
    while (peek(p) != TOK_RBRACE && peek(p) != TOK_EOF) {
        VEC_PUSH(p->arena, decls, parse_declaration(p), Node*);
    }
    expect(p, TOK_RBRACE, "}");

    Node *n = alloc_node(p, NODE_MODULE, loc);
    n->data.module.name = name.data.str_val;
    n->data.module.decls = decls.data;
    n->data.module.count = decls.count;
    return n;
}

void parser_init(Parser *p, const char *source, int source_len, const char *file, Arena *arena) {
    lexer_init(&p->lexer, source, source_len, file, arena);
    p->arena = arena;
    p->error_count = 0;
    p->current = lexer_next(&p->lexer);
}

Node *parse_program(Parser *p) {
    SrcLoc loc = here(p);
    NodeVec modules = {NULL, 0, 0};

    while (peek(p) != TOK_EOF) {
        if (peek(p) == TOK_MODULE) {
            VEC_PUSH(p->arena, modules, parse_module(p), Node*);
        } else {
            error_report(PHASE_PARSER, here(p), "expected 'module', got token %d", peek(p));
            p->error_count++;
            advance(p);
        }
    }

    Node *n = alloc_node(p, NODE_PROGRAM, loc);
    n->data.program.items = modules.data;
    n->data.program.count = modules.count;
    return n;
}
