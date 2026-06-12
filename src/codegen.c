#include "codegen.h"
#include "error.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/* ---- Name helpers ---- */

typedef struct {
    char **names;
    char **values;
    int count;
    int cap;
    Arena *arena;
} NameMap;

static void map_init(NameMap *m, Arena *a) {
    m->names = NULL;
    m->values = NULL;
    m->count = 0;
    m->cap = 0;
    m->arena = a;
}

static void map_put(NameMap *m, const char *name, const char *val) {
    if (m->count >= m->cap) {
        int nc = m->cap ? m->cap * 2 : 32;
        char **nn = arena_alloc(m->arena, sizeof(char*) * nc);
        char **nv = arena_alloc(m->arena, sizeof(char*) * nc);
        if (m->names) memcpy(nn, m->names, sizeof(char*) * m->count);
        if (m->values) memcpy(nv, m->values, sizeof(char*) * m->count);
        m->names = nn;
        m->values = nv;
        m->cap = nc;
    }
    m->names[m->count] = (char*)name;
    m->values[m->count] = (char*)val;
    m->count++;
}

static const char *map_get(NameMap *m, const char *name) {
    for (int i = m->count - 1; i >= 0; i--)
        if (strcmp(m->names[i], name) == 0) return m->values[i];
    return NULL;
}

static char *sv_dup(StringView sv, Arena *a) {
    char *s = arena_alloc(a, sv.len + 1);
    memcpy(s, sv.data, sv.len);
    s[sv.len] = '\0';
    return s;
}

/* ---- C name sanitizer ---- */

static char *c_name(StringView sv, Arena *a) {
    char *s = sv_dup(sv, a);
    for (char *p = s; *p; p++)
        if (!((*p >= 'a' && *p <= 'z') || (*p >= 'A' && *p <= 'Z') ||
              (*p >= '0' && *p <= '9') || *p == '_'))
            *p = '_';
    return s;
}

/* ---- Codegen state ---- */

typedef struct {
    Arena *arena;
    FILE *out;
    int indent;
    NameMap type_names;   /* M₀ type name -> C typedef name */
    NameMap fn_names;     /* M₀ fn name -> C fn name */
    NameMap ctor_names;   /* Constructor name -> C tag enum name */
    NameMap sum_types;    /* Constructor name -> M₀ sum type name */
    const char *current_type;  /* type being defined (for recursive refs) */
    const char *ret_type_name; /* expected return type for context */
    int arm_need_return;       /* 1: emit 'return' in match arms, 0: no return */
} CodeGen;

static void emit_indent(CodeGen *cg) {
    for (int i = 0; i < cg->indent; i++) fputc(' ', cg->out);
}

static void emit(CodeGen *cg, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(cg->out, fmt, args);
    va_end(args);
}

static void emit_line(CodeGen *cg, const char *fmt, ...) {
    emit_indent(cg);
    va_list args;
    va_start(args, fmt);
    vfprintf(cg->out, fmt, args);
    va_end(args);
    fputc('\n', cg->out);
}

/* ---- Type lowering ---- */

static void lower_type_expr(CodeGen *cg, Node *n);

static void lower_type_expr(CodeGen *cg, Node *n) {
    if (!n) { emit(cg, "void"); return; }

    switch (n->kind) {
        case NODE_NAME: {
            const char *type_name = sv_dup(n->data.name_val, cg->arena);
            const char *cname = map_get(&cg->type_names, type_name);
            if (cname && (!cg->current_type || strcmp(type_name, cg->current_type) != 0)) {
                emit(cg, "%s", cname);
            } else {
                emit(cg, "int64_t");
            }
            break;
        }
        case NODE_RECORD: {
            emit(cg, "struct { ");
            for (int i = 0; i < n->data.record.count; i++) {
                if (i > 0) emit(cg, "; ");
                emit(cg, "%.*s ", n->data.record.fields[i].name.len,
                     n->data.record.fields[i].name.data);
                lower_type_expr(cg, n->data.record.fields[i].value);
            }
            emit(cg, " }");
            break;
        }
        case NODE_SUM_TYPE: {
            emit(cg, "struct { int tag; union { ");
            int has_payload = 0;
            for (int i = 0; i < n->data.sum_type.count; i++) {
                if (n->data.sum_type.variants[i].type_count > 0) {
                    if (has_payload) emit(cg, "; ");
                    emit(cg, "struct { ");
                    for (int j = 0; j < n->data.sum_type.variants[i].type_count; j++) {
                        if (j > 0) emit(cg, "; ");
                        lower_type_expr(cg, n->data.sum_type.variants[i].types[j]);
                        emit(cg, " f%d", j);
                    }
                    emit(cg, " } %.*s",
                         n->data.sum_type.variants[i].name.len,
                         n->data.sum_type.variants[i].name.data);
                    has_payload = 1;
                }
            }
            if (has_payload) emit(cg, "; ");
            emit(cg, "char _unused[1]; } data; }");
            break;
        }
        case NODE_CALL: {
            lower_type_expr(cg, n->data.call.expr);
            /* ignore type app args for now */
            break;
        }
        case NODE_GROUP:
            lower_type_expr(cg, n->data.group.expr);
            break;
        case NODE_BINARY: {
            emit(cg, "int64_t (*)(");
            lower_type_expr(cg, n->data.binary.left);
            emit(cg, ")");
            break;
        }
        default:
            emit(cg, "void");
    }
}

/* ---- Expression codegen ---- */

static void cg_expr(CodeGen *cg, Node *n, int want_semi);
static void cg_emit_body(CodeGen *cg, Node *n, int need_return);
static void cg_emit_if_assign(CodeGen *cg, StringView var_name, Node *if_node, Node *type_ann);
static void cg_emit_if_statement(CodeGen *cg, Node *if_node);

static void cg_expr(CodeGen *cg, Node *n, int want_semi) {
    if (!n) return;

    switch (n->kind) {
        case NODE_LITERAL_INT:
            emit(cg, "%lld", n->data.int_val);
            if (want_semi) emit(cg, ";");
            break;

        case NODE_LITERAL_FLOAT:
            emit(cg, "%f", n->data.float_val);
            if (want_semi) emit(cg, ";");
            break;

        case NODE_LITERAL_STRING: {
            emit(cg, "\"");
            for (int i = 0; i < n->data.str_val.len; i++) {
                char c = n->data.str_val.data[i];
                switch (c) {
                    case '\n': emit(cg, "\\n"); break;
                    case '\t': emit(cg, "\\t"); break;
                    case '\\': emit(cg, "\\\\"); break;
                    case '"':  emit(cg, "\\\""); break;
                    default:   fputc(c, cg->out);
                }
            }
            emit(cg, "\"");
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_LITERAL_CHAR:
            emit(cg, "'%c'", n->data.char_val);
            if (want_semi) emit(cg, ";");
            break;

        case NODE_LITERAL_BOOL:
            emit(cg, "%s", n->data.bool_val ? "1" : "0");
            if (want_semi) emit(cg, ";");
            break;

        case NODE_LITERAL_UNIT:
            if (want_semi) emit(cg, ";");
            break;

        case NODE_NAME: {
            char *name = sv_dup(n->data.name_val, cg->arena);
            const char *cname = map_get(&cg->fn_names, name);
            const char *ctor_type = map_get(&cg->sum_types, name);
            if (ctor_type) {
                emit(cg, "%s()", name);
            } else {
                emit(cg, "%s", cname ? cname : name);
            }
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_BINARY: {
            emit(cg, "(");
            cg_expr(cg, n->data.binary.left, 0);
            switch (n->data.binary.op) {
                case OP_ADD:  emit(cg, " + "); break;
                case OP_SUB:  emit(cg, " - "); break;
                case OP_MUL:  emit(cg, " * "); break;
                case OP_DIV:  emit(cg, " / "); break;
                case OP_MOD:  emit(cg, " %% "); break;
                case OP_EQ:   emit(cg, " == "); break;
                case OP_NEQ:  emit(cg, " != "); break;
                case OP_LT:   emit(cg, " < "); break;
                case OP_GT:   emit(cg, " > "); break;
                case OP_LE:   emit(cg, " <= "); break;
                case OP_GE:   emit(cg, " >= "); break;
                case OP_AND:  emit(cg, " && "); break;
                case OP_OR:   emit(cg, " || "); break;
                case OP_IMPL: emit(cg, " <= "); break;
                case OP_IFF:  emit(cg, " == "); break;
            }
            cg_expr(cg, n->data.binary.right, 0);
            emit(cg, ")");
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_NOT: {
            emit(cg, "(!");
            cg_expr(cg, n->data.not_.expr, 0);
            emit(cg, ")");
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_FIELD_ACCESS: {
            emit(cg, "(");
            cg_expr(cg, n->data.field_access.expr, 0);
            emit(cg, ").%.*s", n->data.field_access.field.len,
                 n->data.field_access.field.data);
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_CALL: {
            if (n->data.call.expr->kind == NODE_NAME) {
                char *name = sv_dup(n->data.call.expr->data.name_val, cg->arena);
                const char *ctor_type = map_get(&cg->sum_types, name);
                if (ctor_type) {
                    emit(cg, "%s", name);
                } else {
                    cg_expr(cg, n->data.call.expr, 0);
                }
            } else {
                cg_expr(cg, n->data.call.expr, 0);
            }
            emit(cg, "(");
            for (int i = 0; i < n->data.call.arg_count; i++) {
                if (i > 0) emit(cg, ", ");
                cg_expr(cg, n->data.call.args[i], 0);
            }
            emit(cg, ")");
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_LET: {
            Type *ty = n->data.let.value->ty;
            if (n->data.let.name.len == 1 && n->data.let.name.data[0] == '_') {
                /* Wildcard: just evaluate value for side effects */
                if (n->data.let.value->kind == NODE_IF) {
                    cg_emit_if_statement(cg, n->data.let.value);
                } else {
                    cg_expr(cg, n->data.let.value, 1);
                }
                cg_expr(cg, n->data.let.body, want_semi);
                break;
            }
            if (n->data.let.value->kind == NODE_IF) {
                /* If-expression assign: declare var, then if/else sets it */
                cg_emit_if_assign(cg, n->data.let.name, n->data.let.value, n->data.let.type);
                emit_line(cg, "(void)%.*s;", n->data.let.name.len, n->data.let.name.data);
                cg_expr(cg, n->data.let.body, want_semi);
                break;
            }
            if (ty && (ty->kind == TYPE_SUM || ty->kind == TYPE_NAMED || ty->kind == TYPE_RECORD)) {
                if (n->data.let.type && n->data.let.type->kind == NODE_NAME) {
                    const char *tname = map_get(&cg->type_names,
                        sv_dup(n->data.let.type->data.name_val, cg->arena));
                    emit_indent(cg);
                    emit(cg, "%s %.*s = ", tname ? tname : "int64_t",
                         n->data.let.name.len, n->data.let.name.data);
                } else {
                    emit_indent(cg);
                    emit(cg, "int64_t %.*s = ",
                         n->data.let.name.len, n->data.let.name.data);
                }
            } else if (ty && ty->kind == TYPE_INT) emit_line(cg, "int64_t %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_FLOAT) emit_line(cg, "double %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_BOOL) emit_line(cg, "int %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_CHAR) emit_line(cg, "char %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_STRING) emit_line(cg, "char *%.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else emit_line(cg, "int64_t %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            cg_expr(cg, n->data.let.value, 1);
            emit_line(cg, "(void)%.*s;", n->data.let.name.len, n->data.let.name.data);
            cg_expr(cg, n->data.let.body, want_semi);
            break;
        }

        case NODE_IF: {
            if (n->data.if_.cond &&
                (n->data.if_.cond->kind == NODE_BINARY || n->data.if_.cond->kind == NODE_NOT)) {
                emit_line(cg, "if ");
                cg_expr(cg, n->data.if_.cond, 0);
                emit(cg, " {");
            } else {
                emit_line(cg, "if (");
                cg_expr(cg, n->data.if_.cond, 0);
                emit(cg, ") {");
            }
            cg->indent += 2;
            emit_line(cg, "");
            emit_indent(cg);
            cg_emit_body(cg, n->data.if_.then_expr, 1);
            cg->indent -= 2;
            emit_line(cg, "");
            emit_indent(cg);
            emit(cg, "}");
            if (n->data.if_.else_expr) {
                emit(cg, " else {");
                cg->indent += 2;
                emit_line(cg, "");
                emit_indent(cg);
                cg_emit_body(cg, n->data.if_.else_expr, 1);
                cg->indent -= 2;
                emit_line(cg, "");
                emit_indent(cg);
                emit(cg, "}");
            }
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_MATCH: {
            cg->indent += 2;
            /* Determine if we're matching on sum type or primitive */
            Type *scrut_type = n->data.match.scrutinee->ty;
            int is_sum = scrut_type && scrut_type->kind == TYPE_SUM;

            if (is_sum) {
                emit_line(cg, "switch (");
                cg_expr(cg, n->data.match.scrutinee, 0);
                emit(cg, ".tag) {");
                cg->indent += 2;
                int default_arm = -1;
                for (int i = 0; i < n->data.match.arm_count; i++) {
                    Pattern *p = n->data.match.arms[i].pattern;
                    if (p->kind == PATTERN_CONSTRUCTOR) {
                        const char *tag_name = map_get(&cg->ctor_names,
                            sv_dup(p->data.constructor.name, cg->arena));
                        emit_line(cg, "case %s: {", tag_name ? tag_name : "0");
                        cg->indent += 2;
                for (int ai = 0; ai < p->data.constructor.arg_count; ai++) {
                    emit_indent(cg);
                    emit(cg, "int64_t %.*s = ",
                         p->data.constructor.args[ai]->data.name.name.len,
                         p->data.constructor.args[ai]->data.name.name.data);
                    cg_expr(cg, n->data.match.scrutinee, 0);
                    emit(cg, ".data.%.*s.f%d;",
                         p->data.constructor.name.len,
                         p->data.constructor.name.data, ai);
                    emit_line(cg, "");
                }
                emit_indent(cg);
                cg_emit_body(cg, n->data.match.arms[i].body, cg->arm_need_return);
                cg->indent -= 2;
                emit_line(cg, "");
                emit_line(cg, "}");
            } else if (p->kind == PATTERN_WILDCARD || p->kind == PATTERN_NAME) {
                        default_arm = i;
                    }
                }
                if (default_arm >= 0) {
                    Pattern *p = n->data.match.arms[default_arm].pattern;
            emit_line(cg, "default: {");
            cg->indent += 2;
            if (p->kind == PATTERN_NAME) {
                emit_indent(cg);
                emit(cg, "int64_t %.*s = ",
                     p->data.name.name.len, p->data.name.name.data);
                cg_expr(cg, n->data.match.scrutinee, 0);
                emit(cg, ";");
                emit_line(cg, "");
            }
            emit_indent(cg);
            cg_emit_body(cg, n->data.match.arms[default_arm].body, cg->arm_need_return);
                    cg->indent -= 2;
                    emit_line(cg, "}");
                }
                if (default_arm < 0) { emit_line(cg, "default: { return 0; }"); }
                cg->indent -= 2;
                emit_line(cg, "}");
            } else {
                /* If-else chain for primitive matches */
                for (int i = 0; i < n->data.match.arm_count; i++) {
                    if (i > 0) emit_indent(cg);
                    emit(cg, "%s", i == 0 ? "if (" : " else if (");
                    Pattern *p = n->data.match.arms[i].pattern;
                    if (p->kind == PATTERN_LITERAL && p->data.lit.literal) {
                        cg_expr(cg, n->data.match.scrutinee, 0);
                        emit(cg, " == ");
                        cg_expr(cg, p->data.lit.literal, 0);
                    } else if (p->kind == PATTERN_WILDCARD || p->kind == PATTERN_NAME) {
                        emit(cg, "1");
                    } else {
                        emit(cg, "1");
                    }
                    emit(cg, ") {");
                    cg->indent += 2;
                    emit_line(cg, "");
                    emit_indent(cg);
                    cg_emit_body(cg, n->data.match.arms[i].body, cg->arm_need_return);
                    cg->indent -= 2;
                    emit_indent(cg);
                    emit(cg, "}");
                }
            }
            cg->indent -= 2;
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_RECORD: {
            emit(cg, "{");
            for (int i = 0; i < n->data.record.count; i++) {
                if (i > 0) emit(cg, ", ");
                cg_expr(cg, n->data.record.fields[i].value, 0);
            }
            emit(cg, "}");
            if (want_semi) emit(cg, ";");
            break;
        }

        case NODE_LIST:
            if (want_semi) emit(cg, ";");
            break;

        case NODE_GROUP:
            cg_expr(cg, n->data.group.expr, want_semi);
            break;

        case NODE_ANNOT:
            cg_expr(cg, n->data.annot.expr, want_semi);
            break;

        case NODE_LAMBDA:
            emit(cg, "/* lambda */");
            if (want_semi) emit(cg, ";");
            break;

        default:
            if (want_semi) emit(cg, ";");
            break;
    }
}

/* ---- Declaration codegen ---- */

static void cg_type_decl(CodeGen *cg, Node *n) {
    char *type_name = c_name(n->data.type_decl.name, cg->arena);

    /* Build tag enum if sum type */
    Node *ty = n->data.type_decl.type;
    if (ty->kind == NODE_SUM_TYPE) {
        const char *saved_cur = cg->current_type;
        cg->current_type = type_name;
        /* Forward declare for recursive types */
        emit_line(cg, "typedef struct %s %s;", type_name, type_name);
        emit_line(cg, "struct %s {", type_name);
        cg->indent += 2;
        emit_line(cg, "int tag;");
        emit_line(cg, "union {");
        cg->indent += 2;
        for (int i = 0; i < ty->data.sum_type.count; i++) {
            int tc = ty->data.sum_type.variants[i].type_count;
            if (tc > 0) {
                emit_line(cg, "struct {");
                cg->indent += 2;
                for (int j = 0; j < tc; j++) {
                    emit_indent(cg);
                    lower_type_expr(cg, ty->data.sum_type.variants[i].types[j]);
                    emit(cg, " f%d;", j);
                    emit_line(cg, "");
                }
                cg->indent -= 2;
                emit_indent(cg);
                emit(cg, "} %.*s;",
                     ty->data.sum_type.variants[i].name.len,
                     ty->data.sum_type.variants[i].name.data);
                emit_line(cg, "");
            }
            /* Register constructor name -> tag */
            char *ctor_name = sv_dup(ty->data.sum_type.variants[i].name, cg->arena);
            char *tag_name = arena_alloc(cg->arena, strlen(ctor_name) + 20);
            snprintf(tag_name, strlen(ctor_name) + 20, "%s_%s",
                     type_name, ctor_name);
            map_put(&cg->ctor_names, ctor_name, tag_name);
            map_put(&cg->sum_types, ctor_name, type_name);
        }
        emit_line(cg, "char _unused[1];");
        emit_line(cg, "} data;");
        cg->indent -= 2;
        cg->indent -= 2;
        emit_line(cg, "};");
        cg->current_type = saved_cur;
        map_put(&cg->type_names, sv_dup(n->data.type_decl.name, cg->arena), type_name);

        /* Emit tag enum */
        emit_line(cg, "enum %s_tag {", type_name);
        cg->indent += 2;
        for (int i = 0; i < ty->data.sum_type.count; i++) {
            char *ctor_name = sv_dup(ty->data.sum_type.variants[i].name, cg->arena);
            emit_line(cg, "%s_%s%s", type_name, ctor_name,
                 i < ty->data.sum_type.count - 1 ? "," : "");
        }
        cg->indent -= 2;
        emit_line(cg, "};");
    }

    /* Regular record types */
    if (ty->kind == NODE_RECORD) {
        emit_line(cg, "typedef struct {");
        cg->indent += 2;
        for (int i = 0; i < ty->data.record.count; i++) {
            emit_indent(cg);
            lower_type_expr(cg, ty->data.record.fields[i].value);
            emit(cg, " %.*s;",
                 ty->data.record.fields[i].name.len,
                 ty->data.record.fields[i].name.data);
            emit_line(cg, "");
        }
        cg->indent -= 2;
        emit_line(cg, "} %s;", type_name);
        map_put(&cg->type_names, sv_dup(n->data.type_decl.name, cg->arena), type_name);
    }

    /* Named type aliases */
    if (ty->kind == NODE_NAME) {
        emit_indent(cg);
        emit(cg, "typedef ");
        lower_type_expr(cg, ty);
        emit(cg, " %s;", type_name);
        emit_line(cg, "");
        map_put(&cg->type_names, sv_dup(n->data.type_decl.name, cg->arena), type_name);
    }
}

static void cg_extern_decl(CodeGen *cg, Node *n) {
    Node *type = n->data.extern_decl.type;
    emit_indent(cg);
    emit(cg, "extern ");
    if (type->kind == NODE_BINARY && type->data.binary.op == OP_IMPL) {
        Node *cur = type;
        Node *params[64];
        int count = 0;
        while (cur->kind == NODE_BINARY && cur->data.binary.op == OP_IMPL) {
            params[count++] = cur->data.binary.left;
            cur = cur->data.binary.right;
        }
        lower_type_expr(cg, cur);
        emit(cg, " %.*s(", n->data.extern_decl.name.len, n->data.extern_decl.name.data);
        for (int i = 0; i < count; i++) {
            if (i > 0) emit(cg, ", ");
            lower_type_expr(cg, params[i]);
        }
        emit(cg, ");");
    } else {
        lower_type_expr(cg, type);
        emit(cg, " %.*s;",
             n->data.extern_decl.name.len,
             n->data.extern_decl.name.data);
    }
    emit_line(cg, "");
}

/* ---- If-expression assignment helper ---- */

static Node *body_tail_expr(Node *n) {
    if (n && n->kind == NODE_LET) return body_tail_expr(n->data.let.body);
    return n;
}

static void cg_emit_tail_assign(CodeGen *cg, Node *n, StringView var_name);
static void cg_emit_if_body(CodeGen *cg, StringView var_name, Node *if_node);

static void cg_emit_if_body(CodeGen *cg, StringView var_name, Node *if_node) {
    /* Emit if (cond) { then_body; var = ... } else { else_body; var = ... } */
    if (if_node->data.if_.cond &&
        (if_node->data.if_.cond->kind == NODE_BINARY || if_node->data.if_.cond->kind == NODE_NOT)) {
        emit_line(cg, "if ");
        cg_expr(cg, if_node->data.if_.cond, 0);
        emit(cg, " {");
    } else {
        emit_line(cg, "if (");
        cg_expr(cg, if_node->data.if_.cond, 0);
        emit(cg, ") {");
    }
    cg->indent += 2;
    emit_line(cg, "");
    emit_indent(cg);
    cg_emit_tail_assign(cg, if_node->data.if_.then_expr, var_name);
    cg->indent -= 2;
    emit_line(cg, "");
    emit_indent(cg);
    emit(cg, "} else {");
    cg->indent += 2;
    emit_line(cg, "");
    emit_indent(cg);
    if (if_node->data.if_.else_expr) {
        cg_emit_tail_assign(cg, if_node->data.if_.else_expr, var_name);
    } else {
        emit_indent(cg);
        emit(cg, "%.*s = 0;", var_name.len, var_name.data);
    }
    cg->indent -= 2;
    emit_line(cg, "");
    emit_indent(cg);
    emit_line(cg, "}");
}

static void cg_emit_if_statement(CodeGen *cg, Node *if_node) {
    Node *cond = if_node->data.if_.cond;
    Node *then_val = if_node->data.if_.then_expr;
    Node *else_val = if_node->data.if_.else_expr;
    if (cond && (cond->kind == NODE_BINARY || cond->kind == NODE_NOT)) {
        emit_line(cg, "if ");
        cg_expr(cg, cond, 0);
        emit(cg, " {");
    } else {
        emit_line(cg, "if (");
        cg_expr(cg, cond, 0);
        emit(cg, ") {");
    }
    cg->indent += 2;
    emit_line(cg, "");
    emit_indent(cg);
    cg_emit_body(cg, then_val, 0);
    cg->indent -= 2;
    emit_line(cg, "");
    emit_indent(cg);
    emit(cg, "}");
    if (else_val) {
        emit(cg, " else {");
        cg->indent += 2;
        emit_line(cg, "");
        emit_indent(cg);
        cg_emit_body(cg, else_val, 0);
        cg->indent -= 2;
        emit_line(cg, "");
        emit_indent(cg);
        emit(cg, "}");
    }
}

static void cg_emit_tail_assign(CodeGen *cg, Node *n, StringView var_name) {
    if (n->kind == NODE_LET) {
        Type *ty = n->data.let.value->ty;
        if (n->data.let.name.len == 1 && n->data.let.name.data[0] == '_') {
            cg_expr(cg, n->data.let.value, 1);
        } else {
            if (ty && (ty->kind == TYPE_SUM || ty->kind == TYPE_NAMED || ty->kind == TYPE_RECORD)) {
                if (n->data.let.type && n->data.let.type->kind == NODE_NAME) {
                    const char *tname = map_get(&cg->type_names,
                        sv_dup(n->data.let.type->data.name_val, cg->arena));
                    emit_indent(cg);
                    emit(cg, "%s %.*s = ", tname ? tname : "int64_t",
                         n->data.let.name.len, n->data.let.name.data);
                } else {
                    emit_indent(cg);
                    emit(cg, "int64_t %.*s = ",
                         n->data.let.name.len, n->data.let.name.data);
                }
            } else if (ty && ty->kind == TYPE_INT) emit_line(cg, "int64_t %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_FLOAT) emit_line(cg, "double %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_BOOL) emit_line(cg, "int %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_CHAR) emit_line(cg, "char %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else if (ty && ty->kind == TYPE_STRING) emit_line(cg, "char *%.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            else emit_line(cg, "int64_t %.*s = ",
                 n->data.let.name.len, n->data.let.name.data);
            cg_expr(cg, n->data.let.value, 1);
            emit_line(cg, "(void)%.*s;", n->data.let.name.len, n->data.let.name.data);
        }
        cg_emit_tail_assign(cg, n->data.let.body, var_name);
    } else if (n->kind == NODE_IF) {
        cg_emit_if_body(cg, var_name, n);
    } else {
        emit_indent(cg);
        emit(cg, "%.*s = ", var_name.len, var_name.data);
        cg_expr(cg, n, 1);
    }
}

static void cg_emit_if_assign(CodeGen *cg, StringView var_name, Node *if_node, Node *type_ann) {
    Type *ty = NULL;
    Node *then_val = body_tail_expr(if_node->data.if_.then_expr);
    if (then_val) ty = then_val->ty;
    if (type_ann && type_ann->kind == NODE_NAME) {
        const char *tname = map_get(&cg->type_names,
            sv_dup(type_ann->data.name_val, cg->arena));
        if (tname) {
            emit_indent(cg);
            emit(cg, "%s %.*s", tname, var_name.len, var_name.data);
            emit_line(cg, ";");
            cg_emit_if_body(cg, var_name, if_node);
            return;
        }
    }
    if (ty && (ty->kind == TYPE_NAMED || ty->kind == TYPE_APP)) {
        StringView name = ty->kind == TYPE_NAMED ? ty->name : ty->app.base->name;
        const char *tname = map_get(&cg->type_names, sv_dup(name, cg->arena));
        if (tname) { emit_indent(cg); emit(cg, "%s %.*s", tname, var_name.len, var_name.data); }
        else emit_indent(cg), emit(cg, "int64_t %.*s", var_name.len, var_name.data);
    } else if (ty && ty->kind == TYPE_INT) emit_indent(cg), emit(cg, "int64_t %.*s", var_name.len, var_name.data);
    else if (ty && ty->kind == TYPE_FLOAT) emit_indent(cg), emit(cg, "double %.*s", var_name.len, var_name.data);
    else if (ty && ty->kind == TYPE_BOOL) emit_indent(cg), emit(cg, "int %.*s", var_name.len, var_name.data);
    else if (ty && ty->kind == TYPE_CHAR) emit_indent(cg), emit(cg, "char %.*s", var_name.len, var_name.data);
    else if (ty && ty->kind == TYPE_STRING) emit_indent(cg), emit(cg, "char *%.*s", var_name.len, var_name.data);
    else emit_indent(cg), emit(cg, "int64_t %.*s", var_name.len, var_name.data);
    emit_line(cg, ";");
    cg_emit_if_body(cg, var_name, if_node);
}

/* ---- Body emission with proper return handling ---- */

static void cg_emit_body(CodeGen *cg, Node *n, int need_return) {
    if (!n) return;
    if (n->kind == NODE_LET) {
        Type *ty = n->data.let.value->ty;
        if (n->data.let.name.len == 1 && n->data.let.name.data[0] == '_') {
            if (n->data.let.value->kind == NODE_IF) {
                cg_emit_if_statement(cg, n->data.let.value);
            } else {
                cg_expr(cg, n->data.let.value, 1);
            }
            cg_emit_body(cg, n->data.let.body, need_return);
            return;
        }
        if (n->data.let.value->kind == NODE_IF) {
            cg_emit_if_assign(cg, n->data.let.name, n->data.let.value, n->data.let.type);
            emit_line(cg, "(void)%.*s;", n->data.let.name.len, n->data.let.name.data);
            cg_emit_body(cg, n->data.let.body, need_return);
            return;
        }
        if (ty && (ty->kind == TYPE_SUM || ty->kind == TYPE_NAMED || ty->kind == TYPE_RECORD)) {
            if (n->data.let.type && n->data.let.type->kind == NODE_NAME) {
                const char *tname = map_get(&cg->type_names,
                    sv_dup(n->data.let.type->data.name_val, cg->arena));
                emit_indent(cg);
                emit(cg, "%s %.*s = ", tname ? tname : "int64_t",
                     n->data.let.name.len, n->data.let.name.data);
            } else {
                emit_indent(cg);
                emit(cg, "int64_t %.*s = ",
                     n->data.let.name.len, n->data.let.name.data);
            }
        } else if (ty && ty->kind == TYPE_INT) emit_line(cg, "int64_t %.*s = ",
             n->data.let.name.len, n->data.let.name.data);
        else if (ty && ty->kind == TYPE_FLOAT) emit_line(cg, "double %.*s = ",
             n->data.let.name.len, n->data.let.name.data);
        else if (ty && ty->kind == TYPE_BOOL) emit_line(cg, "int %.*s = ",
             n->data.let.name.len, n->data.let.name.data);
        else if (ty && ty->kind == TYPE_CHAR) emit_line(cg, "char %.*s = ",
             n->data.let.name.len, n->data.let.name.data);
        else if (ty && ty->kind == TYPE_STRING) emit_line(cg, "char *%.*s = ",
             n->data.let.name.len, n->data.let.name.data);
        else emit_line(cg, "int64_t %.*s = ",
             n->data.let.name.len, n->data.let.name.data);
        cg_expr(cg, n->data.let.value, 1);
        emit_line(cg, "(void)%.*s;", n->data.let.name.len, n->data.let.name.data);
        cg_emit_body(cg, n->data.let.body, need_return);
        return;
    }
    if (n->kind == NODE_MATCH) {
        cg->arm_need_return = need_return;
        cg_expr(cg, n, 0);
        cg->arm_need_return = 1;
        return;
    }
    if (n->kind == NODE_IF) {
        if (n->data.if_.cond &&
            (n->data.if_.cond->kind == NODE_BINARY || n->data.if_.cond->kind == NODE_NOT)) {
            emit_line(cg, "if ");
            cg_expr(cg, n->data.if_.cond, 0);
            emit(cg, " {");
        } else {
            emit_line(cg, "if (");
            cg_expr(cg, n->data.if_.cond, 0);
            emit(cg, ") {");
        }
        cg->indent += 2;
        emit_line(cg, "");
        emit_indent(cg);
        cg_emit_body(cg, n->data.if_.then_expr, need_return);
        cg->indent -= 2;
        emit_line(cg, "");
        emit_indent(cg);
        emit(cg, "}");
        if (n->data.if_.else_expr) {
            emit(cg, " else {");
            cg->indent += 2;
            emit_line(cg, "");
            emit_indent(cg);
            cg_emit_body(cg, n->data.if_.else_expr, need_return);
            cg->indent -= 2;
            emit_line(cg, "");
            emit_indent(cg);
            emit(cg, "}");
        }
        return;
    }
    if (n->kind == NODE_RECORD && cg->ret_type_name) {
        emit(cg, "return (%s){", cg->ret_type_name);
        for (int i = 0; i < n->data.record.count; i++) {
            if (i > 0) emit(cg, ", ");
            cg_expr(cg, n->data.record.fields[i].value, 0);
        }
        emit(cg, "};");
        return;
    }
    if (need_return) emit(cg, "return ");
    cg_expr(cg, n, 1);
}

static void cg_fn_forward_decl(CodeGen *cg, Node *n) {
    int is_main = (n->data.fn_decl.param_count == 0 &&
        n->data.fn_decl.name.len == 4 &&
        memcmp(n->data.fn_decl.name.data, "main", 4) == 0);
    if (is_main) return;

    const char *fn_name = c_name(n->data.fn_decl.name, cg->arena);
    emit_indent(cg);
    Node *ret_ty = n->data.fn_decl.ret_type;
    lower_type_expr(cg, ret_ty);
    emit(cg, " %s(", fn_name);
    for (int i = 0; i < n->data.fn_decl.param_count; i++) {
        if (i > 0) emit(cg, ", ");
        lower_type_expr(cg, n->data.fn_decl.params[i].type);
        emit(cg, " %.*s",
             n->data.fn_decl.params[i].name.len,
             n->data.fn_decl.params[i].name.data);
    }
    emit_line(cg, ");");
}

static void cg_fn_decl(CodeGen *cg, Node *n) {
    /* Determine function name */
    int is_main = (n->data.fn_decl.param_count == 0 &&
        n->data.fn_decl.name.len == 4 &&
        memcmp(n->data.fn_decl.name.data, "main", 4) == 0);

    const char *fn_name;
    if (is_main) {
        fn_name = "main";
    } else {
        fn_name = c_name(n->data.fn_decl.name, cg->arena);
        if (!map_get(&cg->fn_names, fn_name))
            map_put(&cg->fn_names, fn_name, fn_name);
    }

    /* Emit return type */
    emit_indent(cg);
    if (is_main) {
        emit(cg, "int");
    } else {
        Node *ret_ty = n->data.fn_decl.ret_type;
        lower_type_expr(cg, ret_ty);
    }
    emit(cg, " %s(", fn_name);

    /* Emit parameters */
    for (int i = 0; i < n->data.fn_decl.param_count; i++) {
        if (i > 0) emit(cg, ", ");
        lower_type_expr(cg, n->data.fn_decl.params[i].type);
        emit(cg, " %.*s",
             n->data.fn_decl.params[i].name.len,
             n->data.fn_decl.params[i].name.data);
    }
    emit(cg, ") {");
    emit_line(cg, "");

    /* Emit body */
    cg->indent += 2;
    if (n->data.fn_decl.body) {
        const char *saved_ret_type = cg->ret_type_name;
        Node *ret_ty_ast = n->data.fn_decl.ret_type;
        if (ret_ty_ast && ret_ty_ast->kind == NODE_NAME) {
            cg->ret_type_name = sv_dup(ret_ty_ast->data.name_val, cg->arena);
        } else {
            cg->ret_type_name = NULL;
        }
        cg_emit_body(cg, n->data.fn_decl.body, 1);
        cg->ret_type_name = saved_ret_type;
    }
    cg->indent -= 2;
    emit_line(cg, "}");
}

/* ---- Constructor wrapper ---- */

static void cg_constructor_wrappers(CodeGen *cg, Node *mod) {
    for (int i = 0; i < mod->data.module.count; i++) {
        Node *d = mod->data.module.decls[i];
        if (d->kind == NODE_TYPE_DECL) {
            Node *ty = d->data.type_decl.type;
            if (ty->kind == NODE_SUM_TYPE) {
                char *type_name = c_name(d->data.type_decl.name, cg->arena);
                const char *saved_cur = cg->current_type;
                cg->current_type = type_name;
                for (int j = 0; j < ty->data.sum_type.count; j++) {
                    char *ctor_name = sv_dup(ty->data.sum_type.variants[j].name, cg->arena);
                    if (ty->data.sum_type.variants[j].type_count == 0) {
                        emit_line(cg, "static inline %s %s() {", type_name, ctor_name);
                        cg->indent += 2;
                        emit_line(cg, "%s v = { .tag = %s_%s, .data = {0} };",
                             type_name, type_name, ctor_name);
                        emit_line(cg, "return v;");
                        cg->indent -= 2;
                        emit_line(cg, "}");
                    } else {
                        emit_indent(cg);
                        emit(cg, "static inline %s %s(", type_name, ctor_name);
                        for (int k = 0; k < ty->data.sum_type.variants[j].type_count; k++) {
                            if (k > 0) emit(cg, ", ");
                            lower_type_expr(cg, ty->data.sum_type.variants[j].types[k]);
                            emit(cg, " x%d", k);
                        }
                        emit(cg, ") {");
                        emit_line(cg, "");
                        cg->indent += 2;
                        emit_indent(cg);
                        emit(cg, "%s v = { .tag = %s_%s, .data.%.*s = {",
                             type_name, type_name, ctor_name,
                             ty->data.sum_type.variants[j].name.len,
                             ty->data.sum_type.variants[j].name.data);
                        for (int k = 0; k < ty->data.sum_type.variants[j].type_count; k++) {
                            if (k > 0) emit(cg, ", ");
                            emit(cg, ".f%d = x%d", k, k);
                        }
                        emit(cg, "} };");
                        emit_line(cg, "");
                        emit_line(cg, "return v;");
                        cg->indent -= 2;
                        emit_line(cg, "}");
                    }
                }
                cg->current_type = saved_cur;
            }
        }
    }
}

/* ---- Module codegen ---- */

static void cg_module(CodeGen *cg, Node *mod) {
    emit_line(cg, "/* Module: %.*s */",
         mod->data.module.name.len, mod->data.module.name.data);

    /* Pass 1: top-level constant declarations */
    for (int i = 0; i < mod->data.module.count; i++) {
        Node *d = mod->data.module.decls[i];
        if (d->kind == NODE_PROP_DECL) {
            emit(cg, "int64_t %.*s = ", d->data.prop_decl.name.len, d->data.prop_decl.name.data);
            cg_expr(cg, d->data.prop_decl.body, 0);
            emit_line(cg, ";");
        }
    }

    /* Pass 2: type declarations (must precede externs for type resolution) */
    for (int i = 0; i < mod->data.module.count; i++) {
        Node *d = mod->data.module.decls[i];
        if (d->kind == NODE_TYPE_DECL)
            cg_type_decl(cg, d);
    }

    /* Pass 3: extern declarations */
    for (int i = 0; i < mod->data.module.count; i++) {
        Node *d = mod->data.module.decls[i];
        if (d->kind == NODE_EXTERN_DECL)
            cg_extern_decl(cg, d);
    }
    /* Pass 4: constructor wrappers */
    cg_constructor_wrappers(cg, mod);

    /* Pass 5: forward declarations for all functions (for C compatibility) */
    for (int i = 0; i < mod->data.module.count; i++) {
        Node *d = mod->data.module.decls[i];
        if (d->kind == NODE_FN_DECL)
            cg_fn_forward_decl(cg, d);
    }

    /* Pass 6: function definitions */
    for (int i = 0; i < mod->data.module.count; i++) {
        Node *d = mod->data.module.decls[i];
        if (d->kind == NODE_FN_DECL)
            cg_fn_decl(cg, d);
    }
}

/* ---- Public API ---- */

int codegen(Node *program, const char *output_path) {
    if (!program || program->kind != NODE_PROGRAM) return 1;

    Arena *arena = arena_create(1 << 20);
    CodeGen cg = {0};
    cg.arm_need_return = 1;
    cg.arena = arena;
    map_init(&cg.type_names, arena);
    map_init(&cg.fn_names, arena);
    map_init(&cg.ctor_names, arena);
    map_init(&cg.sum_types, arena);

    /* Pre-populate type mappings */
    map_put(&cg.type_names, "Int", "int64_t");
    map_put(&cg.type_names, "Float", "double");
    map_put(&cg.type_names, "Bool", "int");
    map_put(&cg.type_names, "Char", "char");
    map_put(&cg.type_names, "String", "char*");
    map_put(&cg.type_names, "Unit", "void");
    map_put(&cg.type_names, "List", "int64_t");

    /* Determine output: stdout or file */
    FILE *out = stdout;
    int should_close = 0;
    if (output_path) {
        out = fopen(output_path, "w");
        if (!out) { perror("codegen: fopen"); arena_destroy(arena); return 1; }
        should_close = 1;
    }
    cg.out = out;

    /* Emit header */
    emit_line(&cg, "#include <stdint.h>");
    emit_line(&cg, "#include <stddef.h>");
    emit_line(&cg, "#include <string.h>");
    emit_line(&cg, "#include <stdlib.h>");
    emit_line(&cg, "#ifdef max");
    emit_line(&cg, "#undef max");
    emit_line(&cg, "#endif");
    emit_line(&cg, "#ifdef min");
    emit_line(&cg, "#undef min");
    emit_line(&cg, "#endif");
    emit_line(&cg, "");

    /* Process each module */
    for (int i = 0; i < program->data.program.count; i++) {
        if (program->data.program.items[i]->kind == NODE_MODULE)
            cg_module(&cg, program->data.program.items[i]);
    }

    if (should_close) fclose(out);
    arena_destroy(arena);
    return 0;
}
