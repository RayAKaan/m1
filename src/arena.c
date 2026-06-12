#include "arena.h"
#include <stdlib.h>

struct ArenaBlock {
    ArenaBlock *next;
    char data[];
};

static void grow_arena(Arena *a, size_t min_size) {
    size_t new_size = a->block_size;
    while (new_size < min_size) {
        new_size *= 2;
    }
    a->block_size = new_size;
    ArenaBlock *block = (ArenaBlock *)malloc(sizeof(ArenaBlock) + new_size);
    block->next = a->blocks;
    a->blocks = block;
    a->current = block->data;
    a->end = block->data + new_size;
}

Arena *arena_create(size_t initial_size) {
    Arena *a = (Arena *)malloc(sizeof(Arena));
    a->start = (char *)malloc(initial_size);
    a->current = a->start;
    a->end = a->start + initial_size;
    a->block_size = initial_size;
    a->blocks = NULL;
    return a;
}

void *arena_alloc(Arena *a, size_t size) {
    size = (size + 7) & ~7;
    if (a->current + size > a->end) {
        grow_arena(a, size);
    }
    void *ptr = a->current;
    a->current += size;
    return ptr;
}

void arena_destroy(Arena *a) {
    ArenaBlock *block = a->blocks;
    while (block) {
        ArenaBlock *next = block->next;
        free(block);
        block = next;
    }
    free(a->start);
    free(a);
}
