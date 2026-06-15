#include "reduce.h"
#include <string.h>

static int sv_eq(const char *a, int alen, const char *b, int blen) {
    return alen == blen && memcmp(a, b, alen) == 0;
}

/* fwd-decl removed: matches non-static decl in reduce.h */

static long long eval_int_binop(BinaryOp op, long long a, long long b) {
    switch (op) {
        case OP_ADD: return a + b;
        case OP_SUB: return a - b;
        case OP_MUL: return a * b;
        case OP_DIV: return b != 0 ? a / b : 0;
        case OP_MOD: return b != 0 ? a % b : 0;
        case OP_EQ:  return a == b ? 1 : 0;
        case OP_NEQ: return a != b ? 1 : 0;
        case OP_LT:  return a < b  ? 1 : 0;
        case OP_GT:  return a > b  ? 1 : 0;
        case OP_LE:  return a <= b ? 1 : 0;
        case OP_GE:  return a >= b ? 1 : 0;
        default: return 0;
    }
}

static int is_const_int(Node *n, long long val) {
    return n && n->kind == NODE_LITERAL_INT && n->data.int_val == val;
}

static int is_const_bool(Node *n, int val) {
    return n && n->kind == NODE_LITERAL_BOOL && n->data.bool_val == val;
}

static int pattern_matches_literal(Pattern *p, Node *lit) {
    if (!p || !lit) return 0;
    switch (p->kind) {
        case PATTERN_WILDCARD:
            return 1;
        case PATTERN_LITERAL:
            if (!p->data.lit.literal) return 0;
            if (p->data.lit.literal->kind != lit->kind) return 0;
            switch (lit->kind) {
                case NODE_LITERAL_INT:   return p->data.lit.literal->data.int_val == lit->data.int_val;
                case NODE_LITERAL_BOOL:  return p->data.lit.literal->data.bool_val == lit->data.bool_val;
                case NODE_LITERAL_CHAR:  return p->data.lit.literal->data.char_val == lit->data.char_val;
                default: return 0;
            }
        case PATTERN_NAME:
            return 1;
        default:
            return 0;
    }
}

/* Substitute `name` with `val` in `body` */
static Node *subst(Node *body, const char *name, int name_len, Node *val, Arena *a) {
    if (!body) return NULL;
    switch (body->kind) {
        case NODE_NAME:
            if (sv_eq(body->data.name_val.data, body->data.name_val.len, name, name_len))
                return val;
            return body;
        case NODE_BINARY: {
            Node *l = subst(body->data.binary.left, name, name_len, val, a);
            Node *r = subst(body->data.binary.right, name, name_len, val, a);
            if (l == body->data.binary.left && r == body->data.binary.right) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.binary.left = l;
            out->data.binary.right = r;
            return out;
        }
        case NODE_NOT: {
            Node *e = subst(body->data.not_.expr, name, name_len, val, a);
            if (e == body->data.not_.expr) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.not_.expr = e;
            return out;
        }
        case NODE_FIELD_ACCESS: {
            Node *e = subst(body->data.field_access.expr, name, name_len, val, a);
            if (e == body->data.field_access.expr) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.field_access.expr = e;
            return out;
        }
        case NODE_CALL: {
            Node *expr = subst(body->data.call.expr, name, name_len, val, a);
            int changed = (expr != body->data.call.expr);
            Node **args = body->data.call.args;
            for (int i = 0; i < body->data.call.arg_count; i++) {
                Node *a2 = subst(body->data.call.args[i], name, name_len, val, a);
                if (a2 != body->data.call.args[i]) {
                    if (!changed) {
                        args = arena_alloc(a, sizeof(Node*) * body->data.call.arg_count);
                        memcpy(args, body->data.call.args, sizeof(Node*) * body->data.call.arg_count);
                    }
                    args[i] = a2;
                    changed = 1;
                }
            }
            if (!changed) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.call.expr = expr;
            out->data.call.args = args;
            return out;
        }
        case NODE_IF: {
            Node *c = subst(body->data.if_.cond, name, name_len, val, a);
            Node *t = subst(body->data.if_.then_expr, name, name_len, val, a);
            Node *e = body->data.if_.else_expr ? subst(body->data.if_.else_expr, name, name_len, val, a) : NULL;
            if (c == body->data.if_.cond && t == body->data.if_.then_expr && e == body->data.if_.else_expr) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.if_.cond = c;
            out->data.if_.then_expr = t;
            out->data.if_.else_expr = e;
            return out;
        }
        case NODE_LET: {
            Node *v = subst(body->data.let.value, name, name_len, val, a);
            Node *b = subst(body->data.let.body, name, name_len, val, a);
            if (v == body->data.let.value && b == body->data.let.body) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.let.value = v;
            out->data.let.body = b;
            return out;
        }
        case NODE_MATCH: {
            Node *s = subst(body->data.match.scrutinee, name, name_len, val, a);
            int changed = (s != body->data.match.scrutinee);
            MatchArm *arms = body->data.match.arms;
            for (int i = 0; i < body->data.match.arm_count; i++) {
                Node *abody = subst(body->data.match.arms[i].body, name, name_len, val, a);
                if (abody != body->data.match.arms[i].body) {
                    if (!changed) {
                        arms = arena_alloc(a, sizeof(MatchArm) * body->data.match.arm_count);
                        memcpy(arms, body->data.match.arms, sizeof(MatchArm) * body->data.match.arm_count);
                    }
                    arms[i].body = abody;
                    changed = 1;
                }
            }
            if (!changed) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.match.scrutinee = s;
            out->data.match.arms = arms;
            return out;
        }
        case NODE_RECORD: {
            int changed = 0;
            FieldInit *fields = body->data.record.fields;
            for (int i = 0; i < body->data.record.count; i++) {
                Node *v = subst(body->data.record.fields[i].value, name, name_len, val, a);
                if (v != body->data.record.fields[i].value) {
                    if (!changed) {
                        fields = arena_alloc(a, sizeof(FieldInit) * body->data.record.count);
                        memcpy(fields, body->data.record.fields, sizeof(FieldInit) * body->data.record.count);
                    }
                    fields[i].value = v;
                    changed = 1;
                }
            }
            if (!changed) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.record.fields = fields;
            return out;
        }
        case NODE_LIST: {
            int changed = 0;
            Node **elems = body->data.list.elements;
            for (int i = 0; i < body->data.list.count; i++) {
                Node *e = subst(body->data.list.elements[i], name, name_len, val, a);
                if (e != body->data.list.elements[i]) {
                    if (!changed) {
                        elems = arena_alloc(a, sizeof(Node*) * body->data.list.count);
                        memcpy(elems, body->data.list.elements, sizeof(Node*) * body->data.list.count);
                    }
                    elems[i] = e;
                    changed = 1;
                }
            }
            if (!changed) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.list.elements = elems;
            return out;
        }
        case NODE_GROUP: {
            Node *inner = subst(body->data.group.expr, name, name_len, val, a);
            if (inner == body->data.group.expr) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.group.expr = inner;
            return out;
        }
        case NODE_ANNOT: {
            Node *expr = subst(body->data.annot.expr, name, name_len, val, a);
            if (expr == body->data.annot.expr) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.annot.expr = expr;
            return out;
        }
        case NODE_LAMBDA: {
            Node *b = subst(body->data.lambda.body, name, name_len, val, a);
            if (b == body->data.lambda.body) return body;
            Node *out = arena_alloc(a, sizeof(Node));
            *out = *body;
            out->data.lambda.body = b;
            return out;
        }
        default:
            return body;
    }
}

Node *reduce(Node *n, Reducer *r) {
    if (!n) return NULL;

    switch (n->kind) {
        /* Literals: already reduced */
        case NODE_LITERAL_INT:
        case NODE_LITERAL_FLOAT:
        case NODE_LITERAL_STRING:
        case NODE_LITERAL_CHAR:
        case NODE_LITERAL_BOOL:
        case NODE_LITERAL_UNIT:
        case NODE_NAME:
            return n;

        /* Binary: reduce both sides, then try constant fold */
        case NODE_BINARY: {
            Node *left = reduce(n->data.binary.left, r);
            Node *right = reduce(n->data.binary.right, r);

            /* Constant folding: both sides are int literals */
            if (left->kind == NODE_LITERAL_INT && right->kind == NODE_LITERAL_INT) {
                long long result = eval_int_binop(n->data.binary.op,
                    left->data.int_val, right->data.int_val);
                Node *out = arena_alloc(r->arena, sizeof(Node));
                *out = *n;
                out->kind = (n->data.binary.op >= OP_EQ) ? NODE_LITERAL_BOOL : NODE_LITERAL_INT;
                if (out->kind == NODE_LITERAL_BOOL) out->data.bool_val = result ? 1 : 0;
                else out->data.int_val = result;
                r->reductions++;
                return out;
            }

            /* Boolean short-circuit: true && x -> x, false && x -> false */
            if (n->data.binary.op == OP_AND) {
                if (is_const_bool(left, 0)) { r->reductions++; return left; }
                if (is_const_bool(left, 1)) { r->reductions++; return right; }
            }
            if (n->data.binary.op == OP_OR) {
                if (is_const_bool(left, 1)) { r->reductions++; return left; }
                if (is_const_bool(left, 0)) { r->reductions++; return right; }
            }

            /* 0 + x -> x, x + 0 -> x */
            if (n->data.binary.op == OP_ADD) {
                if (is_const_int(left, 0)) { r->reductions++; return right; }
                if (is_const_int(right, 0)) { r->reductions++; return left; }
            }
            /* x - 0 -> x */
            if (n->data.binary.op == OP_SUB && is_const_int(right, 0)) {
                r->reductions++; return left;
            }
            /* 1 * x -> x, x * 1 -> x, 0 * x -> 0 */
            if (n->data.binary.op == OP_MUL) {
                if (is_const_int(left, 1)) { r->reductions++; return right; }
                if (is_const_int(right, 1)) { r->reductions++; return left; }
                if (is_const_int(left, 0)) { r->reductions++; return left; }
                if (is_const_int(right, 0)) { r->reductions++; return right; }
            }

            if (left == n->data.binary.left && right == n->data.binary.right) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.binary.left = left;
            out->data.binary.right = right;
            return out;
        }

        /* Not: reduce, then fold */
        case NODE_NOT: {
            Node *expr = reduce(n->data.not_.expr, r);
            if (expr->kind == NODE_LITERAL_BOOL) {
                Node *out = arena_alloc(r->arena, sizeof(Node));
                *out = *n;
                out->kind = NODE_LITERAL_BOOL;
                out->data.bool_val = !expr->data.bool_val;
                r->reductions++;
                return out;
            }
            if (expr == n->data.not_.expr) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.not_.expr = expr;
            return out;
        }

        /* Field access: reduce expr, then try field access on record literal */
        case NODE_FIELD_ACCESS: {
            Node *expr = reduce(n->data.field_access.expr, r);
            if (expr->kind == NODE_RECORD) {
                for (int i = 0; i < expr->data.record.count; i++) {
                    if (sv_eq(expr->data.record.fields[i].name.data,
                              expr->data.record.fields[i].name.len,
                              n->data.field_access.field.data,
                              n->data.field_access.field.len)) {
                        r->reductions++;
                        return expr->data.record.fields[i].value;
                    }
                }
            }
            if (expr == n->data.field_access.expr) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.field_access.expr = expr;
            return out;
        }

        /* Call: reduce callee and args, try beta reduction */
        case NODE_CALL: {
            Node *callee = reduce(n->data.call.expr, r);
            Node **args = n->data.call.args;
            int changed = (callee != n->data.call.expr);
            for (int i = 0; i < n->data.call.arg_count; i++) {
                Node *a = reduce(n->data.call.args[i], r);
                if (a != n->data.call.args[i]) {
                    if (!changed) {
                        args = arena_alloc(r->arena, sizeof(Node*) * n->data.call.arg_count);
                        memcpy(args, n->data.call.args, sizeof(Node*) * n->data.call.arg_count);
                    }
                    args[i] = a;
                    changed = 1;
                }
            }

            /* Beta reduction: lambda applied to args */
            if (callee->kind == NODE_LAMBDA && callee->data.lambda.param_count == n->data.call.arg_count) {
                Node *body = callee->data.lambda.body;
                for (int i = 0; i < callee->data.lambda.param_count; i++) {
                    body = subst(body,
                        callee->data.lambda.params[i].name.data,
                        callee->data.lambda.params[i].name.len,
                        args[i], r->arena);
                }
                r->reductions++;
                return reduce(body, r);
            }

            if (!changed) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.call.expr = callee;
            out->data.call.args = args;
            return out;
        }

        /* Let: reduce value, try inline */
        case NODE_LET: {
            Node *val = reduce(n->data.let.value, r);
            /* Let with simple value: inline */
            if (val->kind == NODE_LITERAL_INT || val->kind == NODE_LITERAL_BOOL ||
                val->kind == NODE_LITERAL_STRING || val->kind == NODE_LITERAL_CHAR ||
                val->kind == NODE_LITERAL_UNIT || val->kind == NODE_NAME) {
                Node *body = subst(n->data.let.body,
                    n->data.let.name.data, n->data.let.name.len, val, r->arena);
                r->reductions++;
                return reduce(body, r);
            }
            Node *body = reduce(n->data.let.body, r);
            if (val == n->data.let.value && body == n->data.let.body) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.let.value = val;
            out->data.let.body = body;
            return out;
        }

        /* Lambda: reduce body */
        case NODE_LAMBDA: {
            Node *body = reduce(n->data.lambda.body, r);
            if (body == n->data.lambda.body) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.lambda.body = body;
            return out;
        }

        /* Match: reduce scrutinee, try arm selection */
        case NODE_MATCH: {
            Node *scrut = reduce(n->data.match.scrutinee, r);

            /* If scrutinee is a literal, try to pick an arm */
            if (scrut->kind == NODE_LITERAL_INT ||
                scrut->kind == NODE_LITERAL_BOOL ||
                scrut->kind == NODE_LITERAL_CHAR) {
                for (int i = 0; i < n->data.match.arm_count; i++) {
                    if (pattern_matches_literal(n->data.match.arms[i].pattern, scrut)) {
                        Node *body = n->data.match.arms[i].body;
                        /* bind name patterns */
                        if (n->data.match.arms[i].pattern->kind == PATTERN_NAME) {
                            body = subst(body,
                                n->data.match.arms[i].pattern->data.name.name.data,
                                n->data.match.arms[i].pattern->data.name.name.len,
                                scrut, r->arena);
                        }
                        r->reductions++;
                        return reduce(body, r);
                    }
                }
            }

            /* Reduce arms */
            int changed = (scrut != n->data.match.scrutinee);
            MatchArm *arms = n->data.match.arms;
            for (int i = 0; i < n->data.match.arm_count; i++) {
                Node *b = reduce(n->data.match.arms[i].body, r);
                if (b != n->data.match.arms[i].body) {
                    if (!changed) {
                        arms = arena_alloc(r->arena, sizeof(MatchArm) * n->data.match.arm_count);
                        memcpy(arms, n->data.match.arms, sizeof(MatchArm) * n->data.match.arm_count);
                    }
                    arms[i].body = b;
                    changed = 1;
                }
            }
            if (!changed) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.match.scrutinee = scrut;
            out->data.match.arms = arms;
            return out;
        }

        /* If: reduce cond, try branch selection */
        case NODE_IF: {
            Node *cond = reduce(n->data.if_.cond, r);
            if (cond->kind == NODE_LITERAL_BOOL) {
                r->reductions++;
                if (cond->data.bool_val) return reduce(n->data.if_.then_expr, r);
                else return n->data.if_.else_expr ? reduce(n->data.if_.else_expr, r) : n;
            }
            Node *then_e = reduce(n->data.if_.then_expr, r);
            Node *else_e = n->data.if_.else_expr ? reduce(n->data.if_.else_expr, r) : NULL;
            if (cond == n->data.if_.cond && then_e == n->data.if_.then_expr && else_e == n->data.if_.else_expr) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.if_.cond = cond;
            out->data.if_.then_expr = then_e;
            out->data.if_.else_expr = else_e;
            return out;
        }

        /* Record: reduce fields */
        case NODE_RECORD: {
            int changed = 0;
            FieldInit *fields = n->data.record.fields;
            for (int i = 0; i < n->data.record.count; i++) {
                Node *v = reduce(n->data.record.fields[i].value, r);
                if (v != n->data.record.fields[i].value) {
                    if (!changed) {
                        fields = arena_alloc(r->arena, sizeof(FieldInit) * n->data.record.count);
                        memcpy(fields, n->data.record.fields, sizeof(FieldInit) * n->data.record.count);
                    }
                    fields[i].value = v;
                    changed = 1;
                }
            }
            if (!changed) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.record.fields = fields;
            return out;
        }

        /* List: reduce elements */
        case NODE_LIST: {
            int changed = 0;
            Node **elems = n->data.list.elements;
            for (int i = 0; i < n->data.list.count; i++) {
                Node *e = reduce(n->data.list.elements[i], r);
                if (e != n->data.list.elements[i]) {
                    if (!changed) {
                        elems = arena_alloc(r->arena, sizeof(Node*) * n->data.list.count);
                        memcpy(elems, n->data.list.elements, sizeof(Node*) * n->data.list.count);
                    }
                    elems[i] = e;
                    changed = 1;
                }
            }
            if (!changed) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.list.elements = elems;
            return out;
        }

        /* Group: reduce inner, unwrap */
        case NODE_GROUP: {
            Node *inner = reduce(n->data.group.expr, r);
            r->reductions++;
            return inner;
        }

        /* Annot: reduce inner */
        case NODE_ANNOT: {
            Node *expr = reduce(n->data.annot.expr, r);
            if (expr == n->data.annot.expr) return n;
            Node *out = arena_alloc(r->arena, sizeof(Node));
            *out = *n;
            out->data.annot.expr = expr;
            return out;
        }

        default:
            return n;
    }
}
