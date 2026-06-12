#include "types.h"
#include <stdio.h>
#include <string.h>

static int sv_eq(StringView a, StringView b) {
    return a.len == b.len && memcmp(a.data, b.data, a.len) == 0;
}

static Type *alloc_type(Arena *a, TypeKind kind) {
    Type *t = arena_alloc(a, sizeof(Type));
    memset(t, 0, sizeof(Type));
    t->kind = kind;
    return t;
}

Type *type_make_int(Arena *a)    { return alloc_type(a, TYPE_INT); }
Type *type_make_float(Arena *a)  { return alloc_type(a, TYPE_FLOAT); }
Type *type_make_string(Arena *a) { return alloc_type(a, TYPE_STRING); }
Type *type_make_char(Arena *a)   { return alloc_type(a, TYPE_CHAR); }
Type *type_make_bool(Arena *a)   { return alloc_type(a, TYPE_BOOL); }
Type *type_make_unit(Arena *a)   { return alloc_type(a, TYPE_UNIT); }
Type *type_make_error(Arena *a)  { return alloc_type(a, TYPE_ERROR); }

Type *type_make_named(StringView name, Arena *a) {
    Type *t = alloc_type(a, TYPE_NAMED);
    t->name = name;
    return t;
}

Type *type_make_fn(Type **params, int count, Type *ret, Arena *a) {
    Type *t = alloc_type(a, TYPE_FN);
    t->fn.params = params;
    t->fn.count = count;
    t->fn.ret = ret;
    return t;
}

Type *type_make_record(TypeField *fields, int count, Arena *a) {
    Type *t = alloc_type(a, TYPE_RECORD);
    t->record.fields = fields;
    t->record.count = count;
    return t;
}

Type *type_make_sum(TypeCtor *ctors, int count, Arena *a) {
    Type *t = alloc_type(a, TYPE_SUM);
    t->sum.ctors = ctors;
    t->sum.count = count;
    return t;
}

Type *type_make_app(Type *base, Type **args, int count, Arena *a) {
    Type *t = alloc_type(a, TYPE_APP);
    t->app.base = base;
    t->app.args = args;
    t->app.count = count;
    return t;
}

int type_eq(Type *a, Type *b) {
    if (!a || !b) return a == b;
    if (a->kind != b->kind) return 0;
    switch (a->kind) {
        case TYPE_INT: case TYPE_FLOAT: case TYPE_STRING:
        case TYPE_CHAR: case TYPE_BOOL: case TYPE_UNIT: case TYPE_ERROR:
            return 1;
        case TYPE_NAMED:
            return sv_eq(a->name, b->name);
        case TYPE_FN:
            if (a->fn.count != b->fn.count) return 0;
            for (int i = 0; i < a->fn.count; i++)
                if (!type_eq(a->fn.params[i], b->fn.params[i])) return 0;
            return type_eq(a->fn.ret, b->fn.ret);
        case TYPE_RECORD:
            if (a->record.count != b->record.count) return 0;
            for (int i = 0; i < a->record.count; i++) {
                if (!sv_eq(a->record.fields[i].name, b->record.fields[i].name)) return 0;
                if (!type_eq(a->record.fields[i].type, b->record.fields[i].type)) return 0;
            }
            return 1;
        case TYPE_SUM:
            if (a->sum.count != b->sum.count) return 0;
            for (int i = 0; i < a->sum.count; i++) {
                if (!sv_eq(a->sum.ctors[i].name, b->sum.ctors[i].name)) return 0;
                if (a->sum.ctors[i].count != b->sum.ctors[i].count) return 0;
                for (int j = 0; j < a->sum.ctors[i].count; j++)
                    if (!type_eq(a->sum.ctors[i].args[j], b->sum.ctors[i].args[j])) return 0;
            }
            return 1;
        case TYPE_APP:
            if (!type_eq(a->app.base, b->app.base)) return 0;
            if (a->app.count != b->app.count) return 0;
            for (int i = 0; i < a->app.count; i++)
                if (!type_eq(a->app.args[i], b->app.args[i])) return 0;
            return 1;
    }
    return 0;
}

Type *type_from_ast(Node *n, Arena *a) {
    if (!n) return type_make_error(a);
    switch (n->kind) {
        case NODE_NAME: {
            StringView sv = n->data.name_val;
            if (sv_eq(sv, (StringView){"Int", 3}))    return type_make_int(a);
            if (sv_eq(sv, (StringView){"Float", 5}))  return type_make_float(a);
            if (sv_eq(sv, (StringView){"String", 6})) return type_make_string(a);
            if (sv_eq(sv, (StringView){"Char", 4}))   return type_make_char(a);
            if (sv_eq(sv, (StringView){"Bool", 4}))   return type_make_bool(a);
            if (sv_eq(sv, (StringView){"Unit", 4}))   return type_make_unit(a);
            return type_make_named(sv, a);
        }
        case NODE_BINARY: {
            if (n->data.binary.op == OP_IMPL) {
                int count = 0;
                Node *cur = n;
                while (cur->kind == NODE_BINARY && cur->data.binary.op == OP_IMPL) {
                    count++;
                    cur = cur->data.binary.right;
                }
                Type **params = arena_alloc(a, sizeof(Type*) * count);
                cur = n;
                int i = 0;
                while (cur->kind == NODE_BINARY && cur->data.binary.op == OP_IMPL) {
                    params[i++] = type_from_ast(cur->data.binary.left, a);
                    cur = cur->data.binary.right;
                }
                Type *ret = type_from_ast(cur, a);
                return type_make_fn(params, count, ret, a);
            }
            return type_make_error(a);
        }
        case NODE_RECORD: {
            TypeField *fields = arena_alloc(a, sizeof(TypeField) * n->data.record.count);
            for (int i = 0; i < n->data.record.count; i++) {
                fields[i].name = n->data.record.fields[i].name;
                fields[i].type = type_from_ast(n->data.record.fields[i].value, a);
            }
            return type_make_record(fields, n->data.record.count, a);
        }
        case NODE_SUM_TYPE: {
            TypeCtor *ctors = arena_alloc(a, sizeof(TypeCtor) * n->data.sum_type.count);
            for (int i = 0; i < n->data.sum_type.count; i++) {
                ctors[i].name = n->data.sum_type.variants[i].name;
                ctors[i].count = n->data.sum_type.variants[i].type_count;
                ctors[i].args = NULL;
                if (ctors[i].count > 0) {
                    ctors[i].args = arena_alloc(a, sizeof(Type*) * ctors[i].count);
                    for (int j = 0; j < ctors[i].count; j++)
                        ctors[i].args[j] = type_from_ast(n->data.sum_type.variants[i].types[j], a);
                }
            }
            return type_make_sum(ctors, n->data.sum_type.count, a);
        }
        case NODE_CALL: {
            Type *base = type_from_ast(n->data.call.expr, a);
            Type **args = arena_alloc(a, sizeof(Type*) * n->data.call.arg_count);
            for (int i = 0; i < n->data.call.arg_count; i++)
                args[i] = type_from_ast(n->data.call.args[i], a);
            return type_make_app(base, args, n->data.call.arg_count, a);
        }
        case NODE_GROUP:
            return type_from_ast(n->data.group.expr, a);
        default:
            return type_make_error(a);
    }
}

void type_print(Type *t) {
    if (!t) { printf("NULL"); return; }
    switch (t->kind) {
        case TYPE_INT:    printf("Int"); break;
        case TYPE_FLOAT:  printf("Float"); break;
        case TYPE_STRING: printf("String"); break;
        case TYPE_CHAR:   printf("Char"); break;
        case TYPE_BOOL:   printf("Bool"); break;
        case TYPE_UNIT:   printf("Unit"); break;
        case TYPE_ERROR:  printf("Error"); break;
        case TYPE_NAMED:  printf("%.*s", t->name.len, t->name.data); break;
        case TYPE_FN:
            for (int i = 0; i < t->fn.count; i++) {
                type_print(t->fn.params[i]);
                printf(" -> ");
            }
            type_print(t->fn.ret);
            break;
        case TYPE_RECORD:
            printf("{ ");
            for (int i = 0; i < t->record.count; i++) {
                if (i > 0) printf(", ");
                printf("%.*s: ", t->record.fields[i].name.len, t->record.fields[i].name.data);
                type_print(t->record.fields[i].type);
            }
            printf(" }");
            break;
        case TYPE_SUM:
            printf("| ");
            for (int i = 0; i < t->sum.count; i++) {
                if (i > 0) printf(" | ");
                printf("%.*s", t->sum.ctors[i].name.len, t->sum.ctors[i].name.data);
                if (t->sum.ctors[i].count > 0) {
                    printf("(");
                    for (int j = 0; j < t->sum.ctors[i].count; j++) {
                        if (j > 0) printf(", ");
                        type_print(t->sum.ctors[i].args[j]);
                    }
                    printf(")");
                }
            }
            break;
        case TYPE_APP:
            type_print(t->app.base);
            printf("(");
            for (int i = 0; i < t->app.count; i++) {
                if (i > 0) printf(", ");
                type_print(t->app.args[i]);
            }
            printf(")");
            break;
    }
}
