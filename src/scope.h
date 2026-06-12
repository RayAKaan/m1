#ifndef SCOPE_H
#define SCOPE_H

#include "ast.h"
#include "arena.h"

typedef enum {
    SYM_TYPE,
    SYM_PROP,
    SYM_FN,
    SYM_EXTERN,
    SYM_PARAM,
    SYM_LOCAL,
    SYM_CONSTRUCTOR,
} SymKind;

typedef struct Sym {
    StringView name;
    SymKind kind;
    Node *decl;         /* the declaration node */
    struct Scope *parent; /* enclosing scope */
} Sym;

typedef struct Scope {
    Sym **syms;         /* arena-allocated array */
    int count;
    int cap;
    struct Scope *parent;
} Scope;

typedef struct {
    Arena *arena;
    Scope *current;
    int error_count;
} ScopeResolver;

void scope_resolve(ScopeResolver *r, Node *program);
Scope *scope_push(ScopeResolver *r);
void scope_pop(ScopeResolver *r);
Sym *scope_lookup(Scope *s, StringView name);
Sym *scope_insert(ScopeResolver *r, StringView name, SymKind kind, Node *decl);

#endif
