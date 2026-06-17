#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* Cross-platform shim (defines _strdup/strncpy_s on non-Windows). Included
   directly so the runtime builds even when compiled without -include compat.h. */
#if defined(__has_include)
#  if __has_include("compat.h")
#    include "compat.h"
#  endif
#endif

int64_t m0_char_at(const char* s, int64_t i) {
    if (!s || i < 0 || i >= (int64_t)strlen(s)) return -1;
    return (int64_t)(unsigned char)s[i];
}

const char* m0_substr(const char* s, int64_t start, int64_t end) {
    if (!s) return "";
    int64_t len = (int64_t)strlen(s);
    if (start < 0) start = 0;
    if (end > len) end = len;
    if (start >= end) return "";
    char* r = (char*)malloc((size_t)(end - start + 1));
    memcpy(r, s + start, (size_t)(end - start));
    r[end - start] = '\0';
    return r;
}

int64_t m0_string_eq(const char* a, const char* b) {
    if (!a || !b) return 0;
    return (int64_t)(strcmp(a, b) == 0);
}

int64_t m0_string_len(const char* s) {
    if (!s) return 0;
    return (int64_t)strlen(s);
}

int64_t m0_print(const char* s) {
    if (s) fputs(s, stdout);
    return 0;
}

int64_t m0_print_int(int64_t v) {
    printf("%lld", (long long)v);
    return 0;
}

int64_t m0_eprint(const char* s) {
    if (s) fputs(s, stderr);
    return 0;
}

int64_t m0_eprint_int(int64_t v) {
    fprintf(stderr, "%lld", (long long)v);
    return 0;
}

int64_t m0_print_char(int64_t c) {
    putchar((char)c);
    return 0;
}

/* ---- List operations (cons-list, Int = pointer) ---- */

typedef struct M0ConsCell {
    int64_t head;
    struct M0ConsCell* tail;
} M0ConsCell;

int64_t m0_nil = 0;

int64_t m0_cons(int64_t head, int64_t tail) {
    M0ConsCell* cell = (M0ConsCell*)malloc(sizeof(M0ConsCell));
    cell->head = head;
    cell->tail = (M0ConsCell*)tail;
    return (int64_t)cell;
}

int64_t m0_head(int64_t list) {
    if (!list) return 0;
    return ((M0ConsCell*)list)->head;
}

int64_t m0_tail(int64_t list) {
    if (!list) return 0;
    return (int64_t)((M0ConsCell*)list)->tail;
}

int64_t m0_is_nil(int64_t list) {
    return list == 0 ? 1 : 0;
}

int64_t m0_list_length(int64_t list) {
    int64_t n = 0;
    M0ConsCell* c = (M0ConsCell*)list;
    while (c) { n++; c = c->tail; }
    return n;
}

/* ---- Generic node allocation (array of int64_t) ---- */

int64_t m0_alloc(int64_t n_fields) {
    return (int64_t)calloc((size_t)n_fields, sizeof(int64_t));
}

int64_t m0_set(int64_t node, int64_t i, int64_t v) {
    ((int64_t*)node)[(size_t)i] = v;
    return 0;
}

int64_t m0_get(int64_t node, int64_t i) {
    return ((int64_t*)node)[(size_t)i];
}

int64_t m0_store_string(int64_t node, int64_t i, const char* s) {
    ((int64_t*)node)[(size_t)i] = (int64_t)s;
    return 0;
}

const char* m0_load_string(int64_t node, int64_t i) {
    return (const char*)(((int64_t*)node)[(size_t)i]);
}

const char* m0_read_file(const char* path) {
    FILE* f = fopen(path, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long len = ftell(f);
    fseek(f, 0, SEEK_SET);
    char* buf = (char*)malloc((size_t)len + 1);
    fread(buf, 1, (size_t)len, f);
    buf[len] = '\0';
    fclose(f);
    return buf;
}

const char* m0_get_env(const char* name) {
    const char* val = getenv(name);
    return val ? val : "";
}

int64_t m0_println(const char* s) {
    puts(s);
    return 0;
}

char* m0_string_concat(const char* a, const char* b) {
    size_t la = strlen(a), lb = strlen(b);
    char* r = malloc(la + lb + 1);
    memcpy(r, a, la);
    memcpy(r + la, b, lb + 1);
    return r;
}

char* m0_int_to_string(int64_t n) {
    char* buf = malloc(32);
    snprintf(buf, 32, "%lld", (long long)n);
    return buf;
}

int64_t m0_string_to_int(const char* s) {
    return atoll(s);
}

int64_t m0_string_length(const char* s) { return m0_string_len(s); }

int64_t m0_string_char_at(const char* s, int64_t idx) {
    if (!s || idx < 0 || idx >= (int64_t)strlen(s)) return -1;
    return (int64_t)(unsigned char)s[idx];
}

char* m0_string_substr(const char* s, int64_t start, int64_t len) {
    size_t slen = strlen(s);
    if (start < 0) start = 0;
    if (start >= (int64_t)slen) return _strdup("");
    if (len < 0) len = 0;
    if (start + len > (int64_t)slen) len = (int64_t)slen - start;
    char* r = malloc(len + 1);
    memcpy(r, s + start, len);
    r[len] = '\0';
    return r;
}

char* m0_string_to_lower(const char* s) {
    size_t len = strlen(s);
    char* r = malloc(len + 1);
    for (size_t i = 0; i < len; i++) r[i] = (s[i] >= 'A' && s[i] <= 'Z') ? s[i] + 32 : s[i];
    r[len] = '\0';
    return r;
}

char* m0_string_to_upper(const char* s) {
    size_t len = strlen(s);
    char* r = malloc(len + 1);
    for (size_t i = 0; i < len; i++) r[i] = (s[i] >= 'a' && s[i] <= 'z') ? s[i] - 32 : s[i];
    r[len] = '\0';
    return r;
}

int64_t m0_write_file(const char* path, const char* content) {
    FILE* f = fopen(path, "w");
    if (!f) return 1;
    fputs(content, f);
    fclose(f);
    return 0;
}

typedef struct {
    int64_t* data;
    int64_t len;
    int64_t cap;
} M1Vec;

int64_t m1_vector_new(void) {
    M1Vec* v = (M1Vec*)malloc(sizeof(M1Vec));
    v->data = (int64_t*)malloc(16 * sizeof(int64_t));
    v->len = 0;
    v->cap = 16;
    return (int64_t)v;
}

int64_t m1_vector_push(int64_t vec, int64_t val) {
    M1Vec* v = (M1Vec*)vec;
    if (v->len >= v->cap) {
        v->cap *= 2;
        v->data = (int64_t*)realloc(v->data, v->cap * sizeof(int64_t));
    }
    v->data[v->len++] = val;
    return 0;
}

int64_t m1_vector_get(int64_t vec, int64_t idx) {
    M1Vec* v = (M1Vec*)vec;
    return v->data[idx];
}

int64_t m1_vector_set(int64_t vec, int64_t idx, int64_t val) {
    M1Vec* v = (M1Vec*)vec;
    v->data[idx] = val;
    return 0;
}

int64_t m1_vector_len(int64_t vec) {
    M1Vec* v = (M1Vec*)vec;
    return v->len;
}

char* m1_read_line(void) {
    char* buf = malloc(4096);
    if (!fgets(buf, 4096, stdin)) {
        free(buf);
        return "";
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len-1] == '\n') buf[len-1] = '\0';
    if (len > 1 && buf[len-2] == '\r') buf[len-2] = '\0';
    return buf;
}

int64_t m1_char_at(const char* s, int64_t idx) {
    size_t len = strlen(s);
    if (idx < 0 || idx >= (int64_t)len) return -1;
    return (int64_t)(unsigned char)s[idx];
}

char* m1_substring(const char* s, int64_t start, int64_t length) {
    size_t slen = strlen(s);
    if (start < 0) start = 0;
    if (start >= (int64_t)slen) return _strdup("");
    if (length < 0) length = 0;
    if (start + length > (int64_t)slen) length = (int64_t)slen - start;
    char* r = malloc(length + 1);
    memcpy(r, s + start, length);
    r[length] = '\0';
    return r;
}

int64_t m1_string_split(const char* s, const char* delim) {
    M1Vec* v = (M1Vec*)malloc(sizeof(M1Vec));
    v->data = (int64_t*)malloc(16 * sizeof(int64_t));
    v->len = 0;
    v->cap = 16;
    size_t dlen = strlen(delim);
    if (dlen == 0) {
        char* part = _strdup(s);
        v->data[v->len++] = (int64_t)part;
        return (int64_t)v;
    }
    const char* p = s;
    while (1) {
        const char* found = strstr(p, delim);
        if (found) {
            size_t len = found - p;
            char* part = malloc(len + 1);
            memcpy(part, p, len);
            part[len] = '\0';
            if (v->len >= v->cap) { v->cap *= 2; v->data = (int64_t*)realloc(v->data, v->cap * sizeof(int64_t)); }
            v->data[v->len++] = (int64_t)part;
            p = found + dlen;
        } else {
            char* part = _strdup(p);
            if (v->len >= v->cap) { v->cap *= 2; v->data = (int64_t*)realloc(v->data, v->cap * sizeof(int64_t)); }
            v->data[v->len++] = (int64_t)part;
            break;
        }
    }
    return (int64_t)v;
}

char* m1_vector_get_str(int64_t vec, int64_t idx) {
    M1Vec* v = (M1Vec*)vec;
    return (char*)v->data[idx];
}

typedef struct {
    int64_t* keys;
    int64_t* vals;
    int64_t* occupied;
    int64_t cap;
    int64_t len;
} M1Map;

static int64_t m1_hash_key(int64_t k) {
    k = ((k >> 16) ^ k) * 0x45d9f3b;
    k = ((k >> 16) ^ k) * 0x45d9f3b;
    k = (k >> 16) ^ k;
    return k & 0x7FFFFFFFFFFFFFFFLL;
}

static int64_t m1_hash_key(int64_t k);
void m1_map_set(int64_t map, int64_t key, int64_t val);

int64_t m1_map_new(void) {
    M1Map* m = (M1Map*)malloc(sizeof(M1Map));
    m->cap = 16;
    m->len = 0;
    m->keys = (int64_t*)calloc(m->cap, sizeof(int64_t));
    m->vals = (int64_t*)calloc(m->cap, sizeof(int64_t));
    m->occupied = (int64_t*)calloc(m->cap, sizeof(int64_t));
    return (int64_t)m;
}

static void m1_map_grow(M1Map* m) {
    int64_t old_cap = m->cap;
    int64_t* old_keys = m->keys;
    int64_t* old_vals = m->vals;
    int64_t* old_occ = m->occupied;
    m->cap = old_cap * 2;
    m->len = 0;
    m->keys = (int64_t*)calloc(m->cap, sizeof(int64_t));
    m->vals = (int64_t*)calloc(m->cap, sizeof(int64_t));
    m->occupied = (int64_t*)calloc(m->cap, sizeof(int64_t));
    for (int64_t i = 0; i < old_cap; i++) {
        if (old_occ[i]) {
            m1_map_set((int64_t)m, old_keys[i], old_vals[i]);
        }
    }
    free(old_keys);
    free(old_vals);
    free(old_occ);
}

void m1_map_set(int64_t map, int64_t key, int64_t val) {
    M1Map* m = (M1Map*)map;
    if (m->len * 2 >= m->cap) m1_map_grow(m);
    int64_t idx = m1_hash_key(key) % m->cap;
    for (int64_t i = 0; i < m->cap; i++) {
        int64_t pos = (idx + i) % m->cap;
        if (!m->occupied[pos]) {
            m->keys[pos] = key;
            m->vals[pos] = val;
            m->occupied[pos] = 1;
            m->len++;
            return;
        }
        if (m->keys[pos] == key) {
            m->vals[pos] = val;
            return;
        }
    }
}

int64_t m1_map_get(int64_t map, int64_t key) {
    M1Map* m = (M1Map*)map;
    int64_t idx = m1_hash_key(key) % m->cap;
    for (int64_t i = 0; i < m->cap; i++) {
        int64_t pos = (idx + i) % m->cap;
        if (!m->occupied[pos]) return 0;
        if (m->keys[pos] == key) return m->vals[pos];
    }
    return 0;
}

int64_t m1_map_has(int64_t map, int64_t key) {
    M1Map* m = (M1Map*)map;
    int64_t idx = m1_hash_key(key) % m->cap;
    for (int64_t i = 0; i < m->cap; i++) {
        int64_t pos = (idx + i) % m->cap;
        if (!m->occupied[pos]) return 0;
        if (m->keys[pos] == key) return 1;
    }
    return 0;
}

int64_t m1_map_len(int64_t map) {
    M1Map* m = (M1Map*)map;
    return m->len;
}

int64_t m1_vector_sort(int64_t vec) {
    M1Vec* v = (M1Vec*)vec;
    for (int64_t i = 0; i < v->len - 1; i++) {
        for (int64_t j = i + 1; j < v->len; j++) {
            if (v->data[i] > v->data[j]) {
                int64_t tmp = v->data[i];
                v->data[i] = v->data[j];
                v->data[j] = tmp;
            }
        }
    }
    return 0;
}

int64_t m1_matrix_new(int64_t rows, int64_t cols) {
    int64_t* data = (int64_t*)calloc(rows * cols, sizeof(int64_t));
    int64_t* m = (int64_t*)malloc(3 * sizeof(int64_t));
    m[0] = (int64_t)data;
    m[1] = rows;
    m[2] = cols;
    return (int64_t)m;
}

int64_t m1_matrix_get(int64_t mat, int64_t r, int64_t c) {
    int64_t* m = (int64_t*)mat;
    int64_t* data = (int64_t*)m[0];
    int64_t cols = m[2];
    return data[r * cols + c];
}

int64_t m1_matrix_set(int64_t mat, int64_t r, int64_t c, int64_t val) {
    int64_t* m = (int64_t*)mat;
    int64_t* data = (int64_t*)m[0];
    int64_t cols = m[2];
    data[r * cols + c] = val;
    return 0;
}

int64_t m1_read_int(void) {
    int64_t n;
    if (scanf("%lld", (long long*)&n) != 1) return 0;
    return n;
}

typedef union { int64_t i; double f; } M1FloatUnion;

int64_t m1_float_of_int(int64_t n) {
    M1FloatUnion u; u.f = (double)n; return u.i;
}

int64_t m1_float_add(int64_t a, int64_t b) {
    M1FloatUnion ua, ub, ur; ua.i = a; ub.i = b; ur.f = ua.f + ub.f; return ur.i;
}

int64_t m1_float_sub(int64_t a, int64_t b) {
    M1FloatUnion ua, ub, ur; ua.i = a; ub.i = b; ur.f = ua.f - ub.f; return ur.i;
}

int64_t m1_float_mul(int64_t a, int64_t b) {
    M1FloatUnion ua, ub, ur; ua.i = a; ub.i = b; ur.f = ua.f * ub.f; return ur.i;
}

int64_t m1_float_div(int64_t a, int64_t b) {
    M1FloatUnion ua, ub, ur; ua.i = a; ub.i = b; ur.f = ua.f / ub.f; return ur.i;
}

int64_t m1_float_lt(int64_t a, int64_t b) {
    M1FloatUnion ua, ub; ua.i = a; ub.i = b; return ua.f < ub.f ? 1 : 0;
}

int64_t m1_float_gt(int64_t a, int64_t b) {
    M1FloatUnion ua, ub; ua.i = a; ub.i = b; return ua.f > ub.f ? 1 : 0;
}

int64_t m1_float_eq(int64_t a, int64_t b) {
    M1FloatUnion ua, ub; ua.i = a; ub.i = b; return ua.f == ub.f ? 1 : 0;
}

char* m1_float_to_string(int64_t f) {
    M1FloatUnion u; u.i = f;
    char* buf = malloc(64);
    snprintf(buf, 64, "%g", u.f);
    return buf;
}

int64_t m1_string_to_float(const char* s) {
    M1FloatUnion u; u.f = strtod(s, NULL); return u.i;
}

/* Wrapper functions matching the stdlib preamble */
int64_t say(const char* s) { return m0_println(s); }
int64_t show(const char* s) { return m0_print(s); }
const char* string_concat(const char* a, const char* b) { return m0_string_concat(a, b); }
char* int_to_string(int64_t n) { return m0_int_to_string(n); }
int64_t string_len(const char* s) { return m0_string_len(s); }
int64_t string_to_int(const char* s) { return m0_string_to_int(s); }
const char* read_file(const char* path) { return m0_read_file(path); }
int64_t write_file(const char* path, const char* content) { return m0_write_file(path, content); }
int64_t vector_new(void) { return m1_vector_new(); }
int64_t vector_push(int64_t v, int64_t x) { return m1_vector_push(v, x); }
int64_t vector_get(int64_t v, int64_t i) { return m1_vector_get(v, i); }
int64_t vector_set(int64_t v, int64_t i, int64_t x) { return m1_vector_set(v, i, x); }
int64_t vector_len(int64_t v) { return m1_vector_len(v); }
int64_t vector_sort(int64_t v) { return m1_vector_sort(v); }
int64_t m0_vector_new(void) { return m1_vector_new(); }
int64_t m0_vector_push(int64_t v, int64_t x) { return m1_vector_push(v, x); }
int64_t m0_vector_get(int64_t v, int64_t i) { return m1_vector_get(v, i); }
int64_t m0_vector_set(int64_t v, int64_t i, int64_t x) { return m1_vector_set(v, i, x); }
int64_t m0_vector_length(int64_t v) { return m1_vector_len(v); }
int64_t m0_vector_remove(int64_t v, int64_t idx) {
    M1Vec* vec = (M1Vec*)v;
    for (int64_t i = idx; i < vec->len - 1; i++) {
        vec->data[i] = vec->data[i + 1];
    }
    vec->len--;
    return 0;
}
char* read_line(void) { return m1_read_line(); }
int64_t read_int(void) { return m1_read_int(); }
int64_t char_at(const char* s, int64_t i) { return m1_char_at(s, i); }
char* substring(const char* s, int64_t start, int64_t len) { return m1_substring(s, start, len); }
int64_t string_split(const char* s, const char* delim) { return m1_string_split(s, delim); }
char* vector_get_str(int64_t v, int64_t i) { return m1_vector_get_str(v, i); }
int64_t map_new(void) { return m1_map_new(); }
int64_t map_set(int64_t m, int64_t k, int64_t v) { m1_map_set(m, k, v); return 0; }
int64_t map_get(int64_t m, int64_t k) { return m1_map_get(m, k); }
int64_t map_has(int64_t m, int64_t k) { return m1_map_has(m, k); }
int64_t map_len(int64_t m) { return m1_map_len(m); }
int64_t matrix_new(int64_t rows, int64_t cols) { return m1_matrix_new(rows, cols); }
int64_t matrix_get(int64_t m, int64_t r, int64_t c) { return m1_matrix_get(m, r, c); }
int64_t matrix_set(int64_t m, int64_t r, int64_t c, int64_t v) { return m1_matrix_set(m, r, c, v); }
int64_t float_of_int(int64_t n) { return m1_float_of_int(n); }
int64_t float_add(int64_t a, int64_t b) { return m1_float_add(a, b); }
int64_t float_sub(int64_t a, int64_t b) { return m1_float_sub(a, b); }
int64_t float_mul(int64_t a, int64_t b) { return m1_float_mul(a, b); }
int64_t float_div(int64_t a, int64_t b) { return m1_float_div(a, b); }
int64_t float_lt(int64_t a, int64_t b) { return m1_float_lt(a, b); }
int64_t float_gt(int64_t a, int64_t b) { return m1_float_gt(a, b); }
int64_t float_eq(int64_t a, int64_t b) { return m1_float_eq(a, b); }
char* float_to_string(int64_t f) { return m1_float_to_string(f); }
int64_t string_to_float(const char* s) { return m1_string_to_float(s); }
