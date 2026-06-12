#include "checker.h"
#include "error.h"
#include <string.h>
#include <stdio.h>

static int sv_eq(StringView a, StringView b) {
    return a.len == b.len && memcmp(a.data, b.data, a.len) == 0;
}

/* ---- Environment ---- */

void env_push(Checker *c) {
    TyEnv *e = arena_alloc(c->arena, sizeof(TyEnv));
    memset(e, 0, sizeof(TyEnv));
    e->parent = c->env;
    c->env = e;
}

void env_pop(Checker *c) {
    if (c->env) c->env = c->env->parent;
}

Type *env_lookup(Checker *c, StringView name) {
    for (TyEnv *e = c->env; e; e = e->parent)
        for (int i = e->count - 1; i >= 0; i--)
            if (sv_eq(e->entries[i].name, name)) return e->entries[i].type;
    return NULL;
}

static void env_insert(Checker *c, StringView name, Type *type) {
    TyEnv *e = c->env;
    if (e->count >= e->cap) {
        int nc = e->cap ? e->cap * 2 : 8;
        TyEntry *nd = arena_alloc(c->arena, sizeof(TyEntry) * nc);
        if (e->entries) memcpy(nd, e->entries, sizeof(TyEntry) * e->count);
        e->entries = nd;
        e->cap = nc;
    }
    e->entries[e->count].name = name;
    e->entries[e->count].type = type;
    e->count++;
}

/* ---- Constructor registry ---- */

static void register_ctors(Checker *c, Type *sum) {
    for (int i = 0; i < sum->sum.count; i++) {
        if (c->ctor_count >= c->ctor_cap) {
            int nc = c->ctor_cap ? c->ctor_cap * 2 : 8;
            CtorInfo *nd = arena_alloc(c->arena, sizeof(CtorInfo) * nc);
            if (c->ctors) memcpy(nd, c->ctors, sizeof(CtorInfo) * c->ctor_count);
            c->ctors = nd;
            c->ctor_cap = nc;
        }
        c->ctors[c->ctor_count] = (CtorInfo){
            .name = sum->sum.ctors[i].name,
            .sum_type = sum,
            .arg_types = sum->sum.ctors[i].args,
            .arg_count = sum->sum.ctors[i].count,
        };
        c->ctor_count++;
    }
}

static CtorInfo *find_ctor(Checker *c, StringView name) {
    for (int i = 0; i < c->ctor_count; i++)
        if (sv_eq(c->ctors[i].name, name)) return &c->ctors[i];
    return NULL;
}

/* ---- Resolve named types ---- */

static Type *resolve_type(Checker *c, Type *t) {
    if (t && t->kind == TYPE_NAMED) {
        Type *r = env_lookup(c, t->name);
        if (r) return r;
    }
    return t;
}

static Type *resolve_type_deep(Checker *c, Type *t) {
    if (!t) return t;
    if (t->kind == TYPE_NAMED) {
        Type *r = env_lookup(c, t->name);
        if (r) return resolve_type_deep(c, r);
        return t;
    }
    if (t->kind == TYPE_RECORD) {
        for (int i = 0; i < t->record.count; i++)
            t->record.fields[i].type = resolve_type_deep(c, t->record.fields[i].type);
        return t;
    }
    if (t->kind == TYPE_SUM) {
        for (int i = 0; i < t->sum.count; i++)
            for (int j = 0; j < t->sum.ctors[i].count; j++)
                t->sum.ctors[i].args[j] = resolve_type_deep(c, t->sum.ctors[i].args[j]);
        return t;
    }
    if (t->kind == TYPE_FN) {
        for (int i = 0; i < t->fn.count; i++)
            t->fn.params[i] = resolve_type_deep(c, t->fn.params[i]);
        t->fn.ret = resolve_type_deep(c, t->fn.ret);
        return t;
    }
    if (t->kind == TYPE_APP) {
        t->app.base = resolve_type_deep(c, t->app.base);
        for (int i = 0; i < t->app.count; i++)
            t->app.args[i] = resolve_type_deep(c, t->app.args[i]);
        return t;
    }
    return t;
}

/* ---- Forward declarations ---- */

static Type *infer(Checker *c, Node *n);
static void check(Checker *c, Node *n, Type *expected);
static void check_pattern(Checker *c, Pattern *p, Type *expected);

/* ---- Infer ---- */

static Type *infer(Checker *c, Node *n) {
    if (!n) return type_make_error(c->arena);
    if (n->ty) return n->ty;

    switch (n->kind) {
        case NODE_LITERAL_INT:    return n->ty = type_make_int(c->arena);
        case NODE_LITERAL_FLOAT:  return n->ty = type_make_float(c->arena);
        case NODE_LITERAL_STRING: return n->ty = type_make_string(c->arena);
        case NODE_LITERAL_CHAR:   return n->ty = type_make_char(c->arena);
        case NODE_LITERAL_BOOL:   return n->ty = type_make_bool(c->arena);
        case NODE_LITERAL_UNIT:   return n->ty = type_make_unit(c->arena);

        case NODE_NAME: {
            CtorInfo *ctor = find_ctor(c, n->data.name_val);
            if (ctor) return n->ty = ctor->sum_type;
            Type *t = env_lookup(c, n->data.name_val);
            if (!t) {
                error_report(PHASE_TYPE, n->loc,
                    "undefined '%.*s'", n->data.name_val.len, n->data.name_val.data);
                c->error_count++;
                return n->ty = type_make_error(c->arena);
            }
            return n->ty = t;
        }

        case NODE_BINARY: {
            Type *lt = infer(c, n->data.binary.left);
            Type *rt = infer(c, n->data.binary.right);
            switch (n->data.binary.op) {
                case OP_ADD: case OP_SUB: case OP_MUL: case OP_DIV: case OP_MOD:
                    if (lt->kind != TYPE_INT && lt->kind != TYPE_ERROR) {
                        error_report(PHASE_TYPE, n->data.binary.left->loc,
                            "expected Int for arithmetic");
                        c->error_count++;
                    }
                    if (rt->kind != TYPE_INT && rt->kind != TYPE_ERROR) {
                        error_report(PHASE_TYPE, n->data.binary.right->loc,
                            "expected Int for arithmetic");
                        c->error_count++;
                    }
                    return n->ty = type_make_int(c->arena);
                case OP_EQ: case OP_NEQ: case OP_LT: case OP_GT: case OP_LE: case OP_GE:
                    if (!type_eq(lt, rt) && lt->kind != TYPE_ERROR && rt->kind != TYPE_ERROR) {
                        error_report(PHASE_TYPE, n->loc, "comparison of different types");
                        c->error_count++;
                    }
                    return n->ty = type_make_bool(c->arena);
                case OP_AND: case OP_OR:
                    if (lt->kind != TYPE_BOOL && lt->kind != TYPE_ERROR) {
                        error_report(PHASE_TYPE, n->data.binary.left->loc, "expected Bool");
                        c->error_count++;
                    }
                    if (rt->kind != TYPE_BOOL && rt->kind != TYPE_ERROR) {
                        error_report(PHASE_TYPE, n->data.binary.right->loc, "expected Bool");
                        c->error_count++;
                    }
                    return n->ty = type_make_bool(c->arena);
                case OP_IMPL: case OP_IFF:
                    return n->ty = type_make_bool(c->arena);
            }
            return n->ty = type_make_error(c->arena);
        }

        case NODE_NOT: {
            Type *t = infer(c, n->data.not_.expr);
            if (t->kind != TYPE_BOOL && t->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, n->data.not_.expr->loc, "expected Bool for 'not'");
                c->error_count++;
            }
            return n->ty = type_make_bool(c->arena);
        }

        case NODE_FIELD_ACCESS: {
            Type *obj = infer(c, n->data.field_access.expr);
            Type *res = resolve_type(c, obj);
            if (res->kind == TYPE_RECORD) {
                for (int i = 0; i < res->record.count; i++) {
                    if (sv_eq(res->record.fields[i].name, n->data.field_access.field))
                        return n->ty = res->record.fields[i].type;
                }
                error_report(PHASE_TYPE, n->loc, "no field '%.*s'",
                    n->data.field_access.field.len, n->data.field_access.field.data);
                c->error_count++;
                return n->ty = type_make_error(c->arena);
            }
            if (obj->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, n->data.field_access.expr->loc,
                    "expected record for field access");
                c->error_count++;
            }
            return n->ty = type_make_error(c->arena);
        }

        case NODE_CALL: {
            /* constructor call? */
            if (n->data.call.expr->kind == NODE_NAME) {
                CtorInfo *ctor = find_ctor(c, n->data.call.expr->data.name_val);
                if (ctor) {
                    if (n->data.call.arg_count != ctor->arg_count) {
                        error_report(PHASE_TYPE, n->loc,
                            "constructor expects %d arguments, got %d", ctor->arg_count, n->data.call.arg_count);
                        c->error_count++;
                    } else {
                        for (int i = 0; i < ctor->arg_count; i++)
                            check(c, n->data.call.args[i], ctor->arg_types[i]);
                    }
                    return n->ty = ctor->sum_type;
                }
            }

            Type *callee = infer(c, n->data.call.expr);
            Type *resolved = resolve_type(c, callee);
            if (resolved->kind == TYPE_FN) {
                if (resolved->fn.count != n->data.call.arg_count) {
                    error_report(PHASE_TYPE, n->loc,
                        "expected %d args, got %d", resolved->fn.count, n->data.call.arg_count);
                    c->error_count++;
                } else {
                    for (int i = 0; i < n->data.call.arg_count; i++)
                        check(c, n->data.call.args[i], resolved->fn.params[i]);
                }
                return n->ty = resolve_type_deep(c, resolved->fn.ret);
            }
            if (callee->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, n->data.call.expr->loc, "expected function");
                c->error_count++;
            }
            return n->ty = type_make_error(c->arena);
        }

        case NODE_ANNOT: {
            Type *t = type_from_ast(n->data.annot.type, c->arena);
            check(c, n->data.annot.expr, t);
            return n->ty = t;
        }

        case NODE_LET: {
            Type *val_t = resolve_type_deep(c, infer(c, n->data.let.value));
            Type *expected = resolve_type_deep(c, type_from_ast(n->data.let.type, c->arena));
            if (!type_eq(val_t, expected) && val_t->kind != TYPE_ERROR && expected->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, n->data.let.value->loc, "let type mismatch");
                c->error_count++;
            }
            env_insert(c, n->data.let.name, expected);
            return n->ty = infer(c, n->data.let.body);
        }

        case NODE_LAMBDA: {
            env_push(c);
            Type **params = arena_alloc(c->arena, sizeof(Type*) * n->data.lambda.param_count);
            for (int i = 0; i < n->data.lambda.param_count; i++) {
                params[i] = type_from_ast(n->data.lambda.params[i].type, c->arena);
                env_insert(c, n->data.lambda.params[i].name, params[i]);
            }
            Type *ret = type_from_ast(n->data.lambda.ret_type, c->arena);
            check(c, n->data.lambda.body, ret);
            env_pop(c);
            return n->ty = type_make_fn(params, n->data.lambda.param_count, ret, c->arena);
        }

        case NODE_MATCH: {
            Type *scrut = infer(c, n->data.match.scrutinee);
            Type *result = NULL;
            for (int i = 0; i < n->data.match.arm_count; i++) {
                env_push(c);
                check_pattern(c, n->data.match.arms[i].pattern, scrut);
                Type *arm_t = infer(c, n->data.match.arms[i].body);
                if (!result) result = arm_t;
                else if (!type_eq(result, arm_t) && arm_t->kind != TYPE_ERROR && result->kind != TYPE_ERROR) {
                    error_report(PHASE_TYPE, n->data.match.arms[i].body->loc,
                        "match arm type mismatch");
                    c->error_count++;
                }
                env_pop(c);
            }
            return n->ty = result ? result : type_make_error(c->arena);
        }

        case NODE_IF: {
            Type *cond = infer(c, n->data.if_.cond);
            if (cond->kind != TYPE_BOOL && cond->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, n->data.if_.cond->loc, "if condition must be Bool");
                c->error_count++;
            }
            Type *tt = resolve_type_deep(c, infer(c, n->data.if_.then_expr));
            Type *ft = n->data.if_.else_expr ? resolve_type_deep(c, infer(c, n->data.if_.else_expr)) : type_make_unit(c->arena);
            if (!type_eq(tt, ft) && tt->kind != TYPE_ERROR && ft->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, n->loc, "if branches differ");
                c->error_count++;
            }
            return n->ty = tt;
        }

        case NODE_RECORD: {
            TypeField *fields = arena_alloc(c->arena, sizeof(TypeField) * n->data.record.count);
            for (int i = 0; i < n->data.record.count; i++) {
                fields[i].name = n->data.record.fields[i].name;
                fields[i].type = infer(c, n->data.record.fields[i].value);
            }
            return n->ty = type_make_record(fields, n->data.record.count, c->arena);
        }

        case NODE_LIST: {
            Type *elem = NULL;
            for (int i = 0; i < n->data.list.count; i++) {
                Type *t = infer(c, n->data.list.elements[i]);
                if (!elem) elem = t;
                else if (!type_eq(elem, t) && t->kind != TYPE_ERROR) {
                    error_report(PHASE_TYPE, n->data.list.elements[i]->loc, "list element type mismatch");
                    c->error_count++;
                }
            }
            Type *list_base = type_make_named((StringView){"List", 4}, c->arena);
            Type **args = arena_alloc(c->arena, sizeof(Type*));
            args[0] = elem ? elem : type_make_error(c->arena);
            return n->ty = type_make_app(list_base, args, 1, c->arena);
        }

        case NODE_GROUP:
            return n->ty = infer(c, n->data.group.expr);

        default:
            return n->ty = type_make_error(c->arena);
    }
}

/* ---- Check ---- */

static void check(Checker *c, Node *n, Type *expected) {
    if (!n || !expected) return;
    switch (n->kind) {
        case NODE_LAMBDA: {
            Type *res = resolve_type(c, expected);
            if (res->kind == TYPE_FN && res->fn.count == n->data.lambda.param_count) {
                env_push(c);
                for (int i = 0; i < n->data.lambda.param_count; i++) {
                    env_insert(c, n->data.lambda.params[i].name, res->fn.params[i]);
                }
                check(c, n->data.lambda.body, res->fn.ret);
                env_pop(c);
                n->ty = expected;
            } else {
                infer(c, n);
            }
            break;
        }
        case NODE_RECORD: {
            Type *res = resolve_type_deep(c, expected);
            if (res->kind == TYPE_RECORD) {
                if (n->data.record.count != res->record.count) {
                    error_report(PHASE_TYPE, n->loc, "record field count mismatch");
                    c->error_count++;
                }
                for (int i = 0; i < n->data.record.count && i < res->record.count; i++)
                    check(c, n->data.record.fields[i].value, resolve_type_deep(c, res->record.fields[i].type));
                n->ty = expected;
            } else {
                infer(c, n);
            }
            break;
        }
        default: {
            Type *inferred = resolve_type_deep(c, infer(c, n));
            Type *exp = resolve_type_deep(c, expected);
            if (!type_eq(inferred, exp) &&
                inferred->kind != TYPE_ERROR && exp->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, n->loc, "type mismatch");
                fprintf(stderr, "  expected: ");
                type_print(expected);
                fprintf(stderr, ", got: ");
                type_print(inferred);
                fprintf(stderr, "\n");
                c->error_count++;
            }
            break;
        }
    }
}

/* ---- Pattern checking ---- */

static void check_pattern(Checker *c, Pattern *p, Type *expected) {
    if (!p || !expected) return;
    Type *res = resolve_type(c, expected);
    switch (p->kind) {
        case PATTERN_WILDCARD:
            break;
        case PATTERN_LITERAL:
            break;
        case PATTERN_CONSTRUCTOR: {
            CtorInfo *ctor = find_ctor(c, p->data.constructor.name);
            if (!ctor) {
                error_report(PHASE_TYPE, p->loc, "undefined constructor '%.*s'",
                    p->data.constructor.name.len, p->data.constructor.name.data);
                c->error_count++;
                return;
            }
            if (!type_eq(res, ctor->sum_type) && res->kind != TYPE_ERROR) {
                error_report(PHASE_TYPE, p->loc, "constructor from wrong type");
                c->error_count++;
            }
            for (int i = 0; i < ctor->arg_count && i < p->data.constructor.arg_count; i++)
                check_pattern(c, p->data.constructor.args[i], ctor->arg_types[i]);
            break;
        }
        case PATTERN_RECORD: {
            if (res->kind != TYPE_RECORD) {
                error_report(PHASE_TYPE, p->loc, "expected record for record pattern");
                c->error_count++;
                break;
            }
            for (int i = 0; i < p->data.record.count; i++) {
                int found = 0;
                for (int j = 0; j < res->record.count; j++) {
                    if (sv_eq(p->data.record.fields[i].name, res->record.fields[j].name)) {
                        check_pattern(c, p->data.record.fields[i].pattern, res->record.fields[j].type);
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    error_report(PHASE_TYPE, p->loc, "no field '%.*s'",
                        p->data.record.fields[i].name.len, p->data.record.fields[i].name.data);
                    c->error_count++;
                }
            }
            break;
        }
        case PATTERN_NAME: {
            /* Check if this is a zero-arg constructor of the expected sum type */
            int is_ctor = 0;
            if (res && res->kind == TYPE_SUM) {
                CtorInfo *ctor = find_ctor(c, p->data.name.name);
                if (ctor && type_eq(res, ctor->sum_type) && ctor->arg_count == 0) {
                    is_ctor = 1;
                }
            }
            if (is_ctor) {
                p->kind = PATTERN_CONSTRUCTOR;
                p->data.constructor.arg_count = 0;
                p->data.constructor.args = NULL;
            } else {
                env_insert(c, p->data.name.name, resolve_type(c, expected));
            }
            break;
        }
        case PATTERN_OR:
            check_pattern(c, p->data.or.left, expected);
            check_pattern(c, p->data.or.right, expected);
            break;
    }
}

/* ---- Exhaustiveness ---- */

static void check_exhaustive(Checker *c, Node *match_node) {
    Type *scrut = resolve_type(c, match_node->data.match.scrutinee->ty);
    if (!scrut) return;

    if (scrut->kind == TYPE_SUM) {
        int *covered = arena_alloc(c->arena, sizeof(int) * scrut->sum.count);
        memset(covered, 0, sizeof(int) * scrut->sum.count);
        int has_wildcard = 0;
        for (int i = 0; i < match_node->data.match.arm_count; i++) {
            Pattern *p = match_node->data.match.arms[i].pattern;
            if (p->kind == PATTERN_WILDCARD || p->kind == PATTERN_NAME) { has_wildcard = 1; break; }
            if (p->kind == PATTERN_CONSTRUCTOR) {
                for (int j = 0; j < scrut->sum.count; j++)
                    if (sv_eq(scrut->sum.ctors[j].name, p->data.constructor.name)) covered[j] = 1;
                /* also check OR patterns containing constructors */
            }
            if (p->kind == PATTERN_OR) { has_wildcard = 1; break; }
        }
        if (!has_wildcard) {
            for (int i = 0; i < scrut->sum.count; i++) {
                if (!covered[i]) {
                    error_report(PHASE_TYPE, match_node->loc,
                        "non-exhaustive: missing '%.*s'",
                        scrut->sum.ctors[i].name.len, scrut->sum.ctors[i].name.data);
                    c->error_count++;
                }
            }
        }
    }

    if (scrut->kind == TYPE_BOOL) {
        int has_true = 0, has_false = 0, has_wild = 0;
        for (int i = 0; i < match_node->data.match.arm_count; i++) {
            Pattern *p = match_node->data.match.arms[i].pattern;
            if (p->kind == PATTERN_WILDCARD || p->kind == PATTERN_NAME) { has_wild = 1; break; }
            if (p->kind == PATTERN_LITERAL && p->data.lit.literal->kind == NODE_LITERAL_BOOL) {
                if (p->data.lit.literal->data.bool_val) has_true = 1;
                else has_false = 1;
            }
        }
        if (!has_wild) {
            if (!has_true) { error_report(PHASE_TYPE, match_node->loc, "non-exhaustive: missing 'true'"); c->error_count++; }
            if (!has_false) { error_report(PHASE_TYPE, match_node->loc, "non-exhaustive: missing 'false'"); c->error_count++; }
        }
    }
}

static void walk_exhaustive(Checker *c, Node *n) {
    if (!n) return;
    switch (n->kind) {
        case NODE_MATCH:
            check_exhaustive(c, n);
            walk_exhaustive(c, n->data.match.scrutinee);
            for (int i = 0; i < n->data.match.arm_count; i++)
                walk_exhaustive(c, n->data.match.arms[i].body);
            break;
        case NODE_BINARY:
            walk_exhaustive(c, n->data.binary.left);
            walk_exhaustive(c, n->data.binary.right);
            break;
        case NODE_NOT:
            walk_exhaustive(c, n->data.not_.expr);
            break;
        case NODE_LET:
            walk_exhaustive(c, n->data.let.value);
            walk_exhaustive(c, n->data.let.body);
            break;
        case NODE_IF:
            walk_exhaustive(c, n->data.if_.cond);
            walk_exhaustive(c, n->data.if_.then_expr);
            if (n->data.if_.else_expr) walk_exhaustive(c, n->data.if_.else_expr);
            break;
        case NODE_CALL:
            walk_exhaustive(c, n->data.call.expr);
            for (int i = 0; i < n->data.call.arg_count; i++)
                walk_exhaustive(c, n->data.call.args[i]);
            break;
        case NODE_FIELD_ACCESS:
            walk_exhaustive(c, n->data.field_access.expr);
            break;
        case NODE_RECORD:
            for (int i = 0; i < n->data.record.count; i++)
                walk_exhaustive(c, n->data.record.fields[i].value);
            break;
        case NODE_LIST:
            for (int i = 0; i < n->data.list.count; i++)
                walk_exhaustive(c, n->data.list.elements[i]);
            break;
        case NODE_GROUP:
            walk_exhaustive(c, n->data.group.expr);
            break;
        case NODE_ANNOT:
            walk_exhaustive(c, n->data.annot.expr);
            break;
        default: break;
    }
}

/* ---- Declaration checking ---- */

void check_decl(Checker *c, Node *n) {
    if (!n) return;
    switch (n->kind) {
        case NODE_TYPE_DECL: {
            Type *t = resolve_type_deep(c, type_from_ast(n->data.type_decl.type, c->arena));
            env_insert(c, n->data.type_decl.name, t);
            if (t->kind == TYPE_SUM) register_ctors(c, t);
            break;
        }
        case NODE_FN_DECL: {
            Type **params = arena_alloc(c->arena, sizeof(Type*) * n->data.fn_decl.param_count);
            for (int i = 0; i < n->data.fn_decl.param_count; i++) {
                Type *raw = type_from_ast(n->data.fn_decl.params[i].type, c->arena);
                params[i] = resolve_type_deep(c, raw);
            }
            Type *ret = resolve_type_deep(c, type_from_ast(n->data.fn_decl.ret_type, c->arena));
            Type *fn_t = type_make_fn(params, n->data.fn_decl.param_count, ret, c->arena);
            env_insert(c, n->data.fn_decl.name, fn_t);
            break;
        }
        case NODE_PROP_DECL: {
            Type *t = resolve_type_deep(c, type_from_ast(n->data.prop_decl.type, c->arena));
            env_insert(c, n->data.prop_decl.name, t);
            break;
        }
        case NODE_EXTERN_DECL: {
            Type *t = resolve_type_deep(c, type_from_ast(n->data.extern_decl.type, c->arena));
            env_insert(c, n->data.extern_decl.name, t);
            break;
        }
        default: break;
    }
}

static void check_decl_body(Checker *c, Node *n) {
    if (!n) return;
    switch (n->kind) {
        case NODE_FN_DECL: {
            Type *fn_t = env_lookup(c, n->data.fn_decl.name);
            if (!fn_t || fn_t->kind != TYPE_FN) return;
            env_push(c);
            for (int i = 0; i < n->data.fn_decl.param_count; i++) {
                Type *pt = type_from_ast(n->data.fn_decl.params[i].type, c->arena);
                Type *resolved = resolve_type_deep(c, pt);
                env_insert(c, n->data.fn_decl.params[i].name, resolved);
            }
            check(c, n->data.fn_decl.body, fn_t->fn.ret);
            env_pop(c);
            walk_exhaustive(c, n->data.fn_decl.body);
            break;
        }
        case NODE_PROP_DECL: {
            if (n->data.prop_decl.body) {
                Type *expected = type_from_ast(n->data.prop_decl.type, c->arena);
                check(c, n->data.prop_decl.body, expected);
                walk_exhaustive(c, n->data.prop_decl.body);
            }
            break;
        }
        default: break;
    }
}

/* ---- Public API ---- */

void check_program(Checker *c, Node *program) {
    if (!program || program->kind != NODE_PROGRAM) return;

    for (int i = 0; i < program->data.program.count; i++) {
        Node *mod = program->data.program.items[i];
        if (mod->kind != NODE_MODULE) continue;

        env_push(c);

        /* Pass 1: types */
        for (int j = 0; j < mod->data.module.count; j++)
            if (mod->data.module.decls[j]->kind == NODE_TYPE_DECL)
                check_decl(c, mod->data.module.decls[j]);

        /* Pass 2: signatures */
        for (int j = 0; j < mod->data.module.count; j++)
            if (mod->data.module.decls[j]->kind != NODE_TYPE_DECL)
                check_decl(c, mod->data.module.decls[j]);

        /* Pass 3: bodies */
        for (int j = 0; j < mod->data.module.count; j++)
            check_decl_body(c, mod->data.module.decls[j]);

        env_pop(c);
    }
}
