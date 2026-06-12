#ifndef TYPES_H
#define TYPES_H

#include "ast.h"
#include "arena.h"

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_CHAR,
    TYPE_BOOL,
    TYPE_UNIT,
    TYPE_NAMED,
    TYPE_FN,
    TYPE_RECORD,
    TYPE_SUM,
    TYPE_APP,
    TYPE_ERROR,
} TypeKind;

typedef struct TypeField {
    StringView name;
    struct Type *type;
} TypeField;

typedef struct TypeCtor {
    StringView name;
    struct Type **args;
    int count;
} TypeCtor;

typedef struct Type {
    TypeKind kind;
    union {
        StringView name;
        struct { struct Type **params; int count; struct Type *ret; } fn;
        struct { TypeField *fields; int count; } record;
        struct { TypeCtor *ctors; int count; } sum;
        struct { struct Type *base; struct Type **args; int count; } app;
    };
} Type;

Type *type_make_int(Arena *a);
Type *type_make_float(Arena *a);
Type *type_make_string(Arena *a);
Type *type_make_char(Arena *a);
Type *type_make_bool(Arena *a);
Type *type_make_unit(Arena *a);
Type *type_make_error(Arena *a);
Type *type_make_named(StringView name, Arena *a);
Type *type_make_fn(Type **params, int count, Type *ret, Arena *a);
Type *type_make_record(TypeField *fields, int count, Arena *a);
Type *type_make_sum(TypeCtor *ctors, int count, Arena *a);
Type *type_make_app(Type *base, Type **args, int count, Arena *a);

Type *type_from_ast(Node *n, Arena *a);
int type_eq(Type *a, Type *b);
void type_print(Type *t);

#endif
