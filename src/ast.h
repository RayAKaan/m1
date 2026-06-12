#ifndef AST_H
#define AST_H

#include <stddef.h>

typedef struct Node Node;

typedef struct {
    const char *file;
    int line;
    int col;
} SrcLoc;

typedef struct {
    const char *data;
    int len;
} StringView;

typedef enum {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,
    OP_EQ,
    OP_NEQ,
    OP_LT,
    OP_GT,
    OP_LE,
    OP_GE,
    OP_AND,
    OP_OR,
    OP_IMPL,
    OP_IFF,
} BinaryOp;

typedef enum {
    PATTERN_WILDCARD,
    PATTERN_LITERAL,
    PATTERN_CONSTRUCTOR,
    PATTERN_RECORD,
    PATTERN_NAME,
    PATTERN_OR,
} PatternKind;

typedef struct Pattern {
    PatternKind kind;
    SrcLoc loc;
    union {
        struct { Node *literal; } lit;
        struct { StringView name; struct Pattern **args; int arg_count; } constructor;
        struct { struct FieldPat *fields; int count; } record;
        struct { StringView name; } name;
        struct { struct Pattern *left; struct Pattern *right; } or;
    } data;
} Pattern;

typedef struct FieldPat {
    StringView name;
    Pattern *pattern;
} FieldPat;

typedef struct {
    Pattern *pattern;
    Node *body;
} MatchArm;

typedef struct {
    StringView name;
    Node *type;
} Param;

typedef struct {
    StringView name;
    Node *value;
} FieldInit;

typedef struct {
    StringView name;
    Node **types;  /* NULL if no arguments */
    int type_count;
} SumVariant;

typedef enum {
    NODE_PROGRAM,
    NODE_MODULE,
    NODE_TYPE_DECL,
    NODE_PROP_DECL,
    NODE_FN_DECL,
    NODE_EXTERN_DECL,
    NODE_SUM_TYPE,

    NODE_LITERAL_INT,
    NODE_IF,
    NODE_LITERAL_FLOAT,
    NODE_LITERAL_STRING,
    NODE_LITERAL_CHAR,
    NODE_LITERAL_BOOL,
    NODE_LITERAL_UNIT,
    NODE_NAME,
    NODE_MATCH,
    NODE_LET,
    NODE_LAMBDA,
    NODE_RECORD,
    NODE_LIST,
    NODE_GROUP,
    NODE_NOT,
    NODE_BINARY,
    NODE_FIELD_ACCESS,
    NODE_CALL,
    NODE_ANNOT,
} NodeKind;

typedef struct Type Type;

struct Node {
    NodeKind kind;
    SrcLoc loc;
    Type *ty;  /* set by type checker, NULL before checking */
    union {
        long long int_val;
        double float_val;
        char char_val;
        int bool_val;
        StringView str_val;
        StringView name_val;

        struct { Node **items; int count; } program;
        struct { StringView name; Node **decls; int count; } module;
        struct { StringView name; Node *type; } type_decl;
        struct { SumVariant *variants; int count; } sum_type;
        struct { StringView name; Node *type; Node *body; int bidi; } prop_decl;
        struct { StringView name; Param *params; int param_count; Node *ret_type; Node *body; } fn_decl;
        struct { StringView name; Node *type; } extern_decl;

        struct { Node *scrutinee; MatchArm *arms; int arm_count; } match;
        struct { Node *cond; Node *then_expr; Node *else_expr; } if_;
        struct { StringView name; Node *type; Node *value; Node *body; } let;
        struct { Param *params; int param_count; Node *ret_type; Node *body; } lambda;
        struct { FieldInit *fields; int count; } record;
        struct { Node **elements; int count; } list;
        struct { Node *expr; } group;
        struct { Node *expr; } not_;
        struct { BinaryOp op; Node *left; Node *right; } binary;
        struct { Node *expr; StringView field; } field_access;
        struct { Node *expr; Node **args; int arg_count; } call;
        struct { Node *expr; Node *type; } annot;
    } data;
};

#endif
