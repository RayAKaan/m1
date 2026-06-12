#ifndef ARENA_H
#define ARENA_H

#include <stddef.h>

typedef struct ArenaBlock ArenaBlock;

typedef struct {
    char *start;
    char *current;
    char *end;
    size_t block_size;
    ArenaBlock *blocks;
} Arena;

Arena *arena_create(size_t initial_size);
void *arena_alloc(Arena *a, size_t size);
void arena_destroy(Arena *a);

#endif
