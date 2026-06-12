#include "scope.h"
#include "error.h"
#include <string.h>

static int sv_eq(StringView a, StringView b) {
    return a.len == b.len && memcmp(a.data, b.data, a.len) == 0;
}

Scope *scope_push(ScopeResolver *r) {
    Scope *s = arena_alloc(r->arena, sizeof(Scope));
    s->syms = NULL;
    s->count = 0;
    s->cap = 0;
    s->parent = r->current;
    r->current = s;
    return s;
}

void scope_pop(ScopeResolver *r) {
    if (r->current) {
        r->current = r->current->parent;
    }
}

Sym *scope_lookup(Scope *s, StringView name) {
    for (Scope *scope = s; scope; scope = scope->parent) {
        for (int i = scope->count - 1; i >= 0; i--) {
            if (sv_eq(scope->syms[i]->name, name)) {
                return scope->syms[i];
            }
        }
    }
    return NULL;
}

Sym *scope_insert(ScopeResolver *r, StringView name, SymKind kind, Node *decl) {
    /* Allow multiple definitions of '_' (wildcard discard) */
    if (name.len == 1 && name.data[0] == '_') {
        Sym *sym = arena_alloc(r->arena, sizeof(Sym));
        sym->name = name;
        sym->kind = kind;
        sym->decl = decl;
        sym->parent = r->current;
        return sym;
    }

    for (int i = 0; i < r->current->count; i++) {
        if (sv_eq(r->current->syms[i]->name, name)) {
            SrcLoc loc = decl ? decl->loc : (SrcLoc){ .file = "<scope>", .line = 0, .col = 0 };
            error_report(PHASE_SCOPE, loc,
                "duplicate definition of '%.*s'", name.len, name.data);
            r->error_count++;
            return r->current->syms[i];
        }
    }

    Sym *sym = arena_alloc(r->arena, sizeof(Sym));
    sym->name = name;
    sym->kind = kind;
    sym->decl = decl;
    sym->parent = r->current;

    if (r->current->count >= r->current->cap) {
        int nc = r->current->cap ? r->current->cap * 2 : 8;
        Sym **nd = arena_alloc(r->arena, sizeof(Sym *) * nc);
        if (r->current->syms) {
            memcpy(nd, r->current->syms, sizeof(Sym *) * r->current->count);
        }
        r->current->syms = nd;
        r->current->cap = nc;
    }
    r->current->syms[r->current->count++] = sym;
    return sym;
}

/* ---- Forward declarations ---- */

static void resolve_decl(ScopeResolver *r, Node *n);
static void resolve_expr(ScopeResolver *r, Node *n);
static void resolve_pattern(ScopeResolver *r, Pattern *p);
static void resolve_type_expr(ScopeResolver *r, Node *n);

/* ---- Type expression resolution ---- */

static void resolve_type_expr(ScopeResolver *r, Node *n) {
    if (!n) return;

    switch (n->kind) {
        case NODE_NAME: {
            Sym *sym = scope_lookup(r->current, n->data.name_val);
            if (!sym) {
                error_report(PHASE_SCOPE, n->loc,
                    "undefined type '%.*s'", n->data.name_val.len, n->data.name_val.data);
                r->error_count++;
            }
            break;
        }
        case NODE_RECORD:
            for (int i = 0; i < n->data.record.count; i++) {
                resolve_type_expr(r, n->data.record.fields[i].value);
            }
            break;
        case NODE_SUM_TYPE:
            for (int i = 0; i < n->data.sum_type.count; i++) {
                for (int j = 0; j < n->data.sum_type.variants[i].type_count; j++) {
                    resolve_type_expr(r, n->data.sum_type.variants[i].types[j]);
                }
            }
            break;
        case NODE_CALL:
            resolve_type_expr(r, n->data.call.expr);
            for (int i = 0; i < n->data.call.arg_count; i++) {
                resolve_type_expr(r, n->data.call.args[i]);
            }
            break;
        case NODE_BINARY:
            resolve_type_expr(r, n->data.binary.left);
            resolve_type_expr(r, n->data.binary.right);
            break;
        case NODE_GROUP:
            resolve_type_expr(r, n->data.group.expr);
            break;
        default:
            break;
    }
}

/* ---- Pattern resolution ---- */

static void resolve_pattern(ScopeResolver *r, Pattern *p) {
    if (!p) return;

    switch (p->kind) {
        case PATTERN_WILDCARD:
            break;
        case PATTERN_LITERAL:
            resolve_expr(r, p->data.lit.literal);
            break;
        case PATTERN_CONSTRUCTOR: {
            Sym *sym = scope_lookup(r->current, p->data.constructor.name);
            if (!sym) {
                error_report(PHASE_SCOPE, p->loc,
                    "undefined constructor '%.*s'",
                    p->data.constructor.name.len, p->data.constructor.name.data);
                r->error_count++;
            }
            for (int i = 0; i < p->data.constructor.arg_count; i++) {
                resolve_pattern(r, p->data.constructor.args[i]);
            }
            break;
        }
        case PATTERN_RECORD:
            for (int i = 0; i < p->data.record.count; i++) {
                resolve_pattern(r, p->data.record.fields[i].pattern);
            }
            break;
        case PATTERN_NAME:
            scope_insert(r, p->data.name.name, SYM_LOCAL, NULL);
            break;
        case PATTERN_OR:
            resolve_pattern(r, p->data.or.left);
            resolve_pattern(r, p->data.or.right);
            break;
    }
}

/* ---- Expression resolution ---- */

static void resolve_expr(ScopeResolver *r, Node *n) {
    if (!n) return;

    switch (n->kind) {
        case NODE_LITERAL_INT:
        case NODE_LITERAL_FLOAT:
        case NODE_LITERAL_STRING:
        case NODE_LITERAL_CHAR:
        case NODE_LITERAL_BOOL:
        case NODE_LITERAL_UNIT:
            break;

        case NODE_NAME: {
            Sym *sym = scope_lookup(r->current, n->data.name_val);
            if (!sym) {
                error_report(PHASE_SCOPE, n->loc,
                    "undefined name '%.*s'",
                    n->data.name_val.len, n->data.name_val.data);
                r->error_count++;
            }
            break;
        }

        case NODE_BINARY:
            resolve_expr(r, n->data.binary.left);
            resolve_expr(r, n->data.binary.right);
            break;

        case NODE_NOT:
            resolve_expr(r, n->data.not_.expr);
            break;

        case NODE_FIELD_ACCESS:
            resolve_expr(r, n->data.field_access.expr);
            break;

        case NODE_CALL:
            resolve_expr(r, n->data.call.expr);
            for (int i = 0; i < n->data.call.arg_count; i++) {
                resolve_expr(r, n->data.call.args[i]);
            }
            break;

        case NODE_ANNOT:
            resolve_expr(r, n->data.annot.expr);
            resolve_type_expr(r, n->data.annot.type);
            break;

        case NODE_LET: {
            resolve_type_expr(r, n->data.let.type);
            resolve_expr(r, n->data.let.value);
            scope_insert(r, n->data.let.name, SYM_LOCAL, NULL);
            resolve_expr(r, n->data.let.body);
            break;
        }

        case NODE_LAMBDA: {
            scope_push(r);
            for (int i = 0; i < n->data.lambda.param_count; i++) {
                resolve_type_expr(r, n->data.lambda.params[i].type);
                scope_insert(r, n->data.lambda.params[i].name, SYM_PARAM, NULL);
            }
            resolve_type_expr(r, n->data.lambda.ret_type);
            resolve_expr(r, n->data.lambda.body);
            scope_pop(r);
            break;
        }

        case NODE_MATCH: {
            resolve_expr(r, n->data.match.scrutinee);
            for (int i = 0; i < n->data.match.arm_count; i++) {
                scope_push(r);
                resolve_pattern(r, n->data.match.arms[i].pattern);
                resolve_expr(r, n->data.match.arms[i].body);
                scope_pop(r);
            }
            break;
        }

        case NODE_IF:
            resolve_expr(r, n->data.if_.cond);
            scope_push(r);
            resolve_expr(r, n->data.if_.then_expr);
            scope_pop(r);
            scope_push(r);
            resolve_expr(r, n->data.if_.else_expr);
            scope_pop(r);
            break;

        case NODE_RECORD:
            for (int i = 0; i < n->data.record.count; i++) {
                resolve_expr(r, n->data.record.fields[i].value);
            }
            break;

        case NODE_LIST:
            for (int i = 0; i < n->data.list.count; i++) {
                resolve_expr(r, n->data.list.elements[i]);
            }
            break;

        case NODE_GROUP:
            resolve_expr(r, n->data.group.expr);
            break;

        default:
            break;
    }
}

/* ---- Declaration resolution ---- */

static void resolve_decl(ScopeResolver *r, Node *n) {
    if (!n) return;

    switch (n->kind) {
        case NODE_TYPE_DECL: {
            resolve_type_expr(r, n->data.type_decl.type);
            break;
        }

        case NODE_PROP_DECL: {
            resolve_type_expr(r, n->data.prop_decl.type);
            if (n->data.prop_decl.body) {
                resolve_expr(r, n->data.prop_decl.body);
            }
            scope_insert(r, n->data.prop_decl.name, SYM_PROP, n);
            break;
        }

        case NODE_FN_DECL: {
            if (!scope_lookup(r->current, n->data.fn_decl.name)) {
                scope_insert(r, n->data.fn_decl.name, SYM_FN, n);
            }

            scope_push(r);
            for (int i = 0; i < n->data.fn_decl.param_count; i++) {
                resolve_type_expr(r, n->data.fn_decl.params[i].type);
                scope_insert(r, n->data.fn_decl.params[i].name, SYM_PARAM, NULL);
            }
            resolve_type_expr(r, n->data.fn_decl.ret_type);
            resolve_expr(r, n->data.fn_decl.body);
            scope_pop(r);
            break;
        }

        case NODE_EXTERN_DECL: {
            resolve_type_expr(r, n->data.extern_decl.type);
            scope_insert(r, n->data.extern_decl.name, SYM_EXTERN, n);
            break;
        }

        default:
            break;
    }
}

/* ---- Built-in types ---- */

static const char *builtin_types[] = {
    "Int", "Float", "String", "Char", "Bool", "Unit", "List",
    NULL
};

/* ---- Public API ---- */

void scope_resolve(ScopeResolver *r, Node *program) {
    if (!program || program->kind != NODE_PROGRAM) return;

    /* root scope: built-in types visible everywhere */
    scope_push(r);
    for (const char **bt = builtin_types; *bt; bt++) {
        StringView sv = { .data = *bt, .len = (int)strlen(*bt) };
        scope_insert(r, sv, SYM_TYPE, NULL);
    }

    for (int i = 0; i < program->data.program.count; i++) {
        Node *mod = program->data.program.items[i];
        if (mod->kind != NODE_MODULE) continue;

        scope_push(r); /* module scope (parent = root) */

        /* Pass 1: register all type and function names for forward refs */
        for (int j = 0; j < mod->data.module.count; j++) {
            Node *d = mod->data.module.decls[j];
            if (d->kind == NODE_TYPE_DECL) {
                scope_insert(r, d->data.type_decl.name, SYM_TYPE, d);
                if (d->data.type_decl.type->kind == NODE_SUM_TYPE) {
                    Node *sum = d->data.type_decl.type;
                    for (int k = 0; k < sum->data.sum_type.count; k++) {
                        scope_insert(r, sum->data.sum_type.variants[k].name,
                                     SYM_CONSTRUCTOR, d);
                    }
                }
            }
            if (d->kind == NODE_FN_DECL) {
                scope_insert(r, d->data.fn_decl.name, SYM_FN, d);
            }
        }

        /* Pass 2: resolve all declarations */
        for (int j = 0; j < mod->data.module.count; j++) {
            resolve_decl(r, mod->data.module.decls[j]);
        }

        scope_pop(r);
    }

    scope_pop(r); /* pop root scope */
}
