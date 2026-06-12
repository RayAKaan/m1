#ifndef REDUCE_H
#define REDUCE_H

#include "ast.h"
#include "arena.h"

typedef struct {
    Arena *arena;
    int reductions;
} Reducer;

Node *reduce(Node *n, Reducer *r);

#endif
