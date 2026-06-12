#ifndef CHECKER_H
#define CHECKER_H

#include "types.h"

typedef struct {
    StringView name;
    Type *type;
} TyEntry;

typedef struct TyEnv {
    TyEntry *entries;
    int count;
    int cap;
    struct TyEnv *parent;
} TyEnv;

typedef struct {
    StringView name;
    Type *sum_type;
    Type **arg_types;
    int arg_count;
} CtorInfo;

typedef struct {
    Arena *arena;
    TyEnv *env;
    CtorInfo *ctors;
    int ctor_count;
    int ctor_cap;
    int error_count;
} Checker;

void check_program(Checker *c, Node *program);

/* Exposed for main.c type printing */
void env_push(Checker *c);
void env_pop(Checker *c);
Type *env_lookup(Checker *c, StringView name);
void check_decl(Checker *c, Node *n);

#endif
