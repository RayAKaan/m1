#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* runtime function declarations */
int64_t m0_print(char* s);
int64_t m0_println(char* s);
int64_t say(char* s);
int64_t show(char* s);
char* string_concat(char* a, char* b);
char* int_to_string(int64_t n);
int64_t string_len(char* s);
int64_t string_to_int(char* s);
char* read_file(char* path);
int64_t write_file(char* path, char* content);
int64_t vector_new(void);
int64_t vector_push(int64_t v, int64_t x);
int64_t vector_get(int64_t v, int64_t i);
int64_t vector_set(int64_t v, int64_t i, int64_t x);
int64_t vector_len(int64_t v);
int64_t vector_sort(int64_t v);
char* read_line(void);
int64_t read_int(void);
int64_t char_at(char* s, int64_t i);
char* substring(char* s, int64_t start, int64_t len);
int64_t string_split(char* s, char* delim);
char* vector_get_str(int64_t v, int64_t i);
int64_t map_new(void);
int64_t map_set(int64_t m, int64_t k, int64_t v);
int64_t map_get(int64_t m, int64_t k);
int64_t map_has(int64_t m, int64_t k);
int64_t map_len(int64_t m);
int64_t matrix_new(int64_t rows, int64_t cols);
int64_t matrix_get(int64_t m, int64_t r, int64_t c);
int64_t matrix_set(int64_t m, int64_t r, int64_t c, int64_t v);
int64_t float_of_int(int64_t n);
int64_t float_add(int64_t a, int64_t b);
int64_t float_sub(int64_t a, int64_t b);
int64_t float_mul(int64_t a, int64_t b);
int64_t float_div(int64_t a, int64_t b);
int64_t float_lt(int64_t a, int64_t b);
int64_t float_gt(int64_t a, int64_t b);
int64_t float_eq(int64_t a, int64_t b);
char* float_to_string(int64_t f);
int64_t string_to_float(char* s);


int64_t m0_print(char*);
int64_t m0_println(char*);
int64_t m0_string_len(char*);
char* m0_string_concat(char*, char*);
char* m0_int_to_string(int64_t);
int64_t m0_string_to_int(char*);
char* m0_read_file(char*);
int64_t m0_write_file(char*, char*);
int64_t m1_vector_new(void);
int64_t m1_vector_push(int64_t, int64_t);
int64_t m1_vector_get(int64_t, int64_t);
int64_t m1_vector_set(int64_t, int64_t, int64_t);
int64_t m1_vector_len(int64_t);
int64_t m1_vector_sort(int64_t);
char* m1_read_line(void);
int64_t m1_read_int(void);
int64_t m1_char_at(char*, int64_t);
char* m1_substring(char*, int64_t, int64_t);
int64_t m1_string_split(char*, char*);
char* m1_vector_get_str(int64_t, int64_t);
int64_t m1_map_new(void);
int64_t m1_map_set(int64_t, int64_t, int64_t);
int64_t m1_map_get(int64_t, int64_t);
int64_t m1_map_has(int64_t, int64_t);
int64_t m1_map_len(int64_t);
int64_t m1_matrix_new(int64_t, int64_t);
int64_t m1_matrix_get(int64_t, int64_t, int64_t);
int64_t m1_matrix_set(int64_t, int64_t, int64_t, int64_t);
int64_t m1_float_of_int(int64_t);
int64_t m1_float_add(int64_t, int64_t);
int64_t m1_float_sub(int64_t, int64_t);
int64_t m1_float_mul(int64_t, int64_t);
int64_t m1_float_div(int64_t, int64_t);
int64_t m1_float_lt(int64_t, int64_t);
int64_t m1_float_gt(int64_t, int64_t);
int64_t m1_float_eq(int64_t, int64_t);
char* m1_float_to_string(int64_t);
int64_t m1_string_to_float(char*);

int64_t say(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m0_println(s));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t show(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m0_print(s));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t string_len(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m0_string_len(s));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* string_concat(char* a, char* b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m0_string_concat(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* int_to_string(int64_t n) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m0_int_to_string(n));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t string_to_int(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m0_string_to_int(s));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* read_file(char* path) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m0_read_file(path));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t write_file(char* path, char* content) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m0_write_file(path, content));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t vector_new() {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_vector_new());
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t vector_push(int64_t v, int64_t x) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_vector_push(v, x));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t vector_get(int64_t v, int64_t i) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_vector_get(v, i));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t vector_set(int64_t v, int64_t i, int64_t x) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_vector_set(v, i, x));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t vector_len(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_vector_len(v));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t vector_sort(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_vector_sort(v));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* read_line() {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m1_read_line());
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t read_int() {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_read_int());
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t char_at(char* s, int64_t i) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_char_at(s, i));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* substring(char* s, int64_t start, int64_t len) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m1_substring(s, start, len));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t string_split(char* s, char* delim) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_string_split(s, delim));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* vector_get_str(int64_t v, int64_t i) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m1_vector_get_str(v, i));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t map_new() {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_map_new());
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t map_set(int64_t m, int64_t k, int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_map_set(m, k, v));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t map_get(int64_t m, int64_t k) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_map_get(m, k));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t map_has(int64_t m, int64_t k) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_map_has(m, k));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t map_len(int64_t m) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_map_len(m));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t matrix_new(int64_t rows, int64_t cols) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_matrix_new(rows, cols));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t matrix_get(int64_t m, int64_t r, int64_t c) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_matrix_get(m, r, c));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t matrix_set(int64_t m, int64_t r, int64_t c, int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_matrix_set(m, r, c, v));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_of_int(int64_t n) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_of_int(n));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_add(int64_t a, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_add(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_sub(int64_t a, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_sub(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_mul(int64_t a, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_mul(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_div(int64_t a, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_div(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_lt(int64_t a, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_lt(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_gt(int64_t a, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_gt(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t float_eq(int64_t a, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_float_eq(a, b));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* float_to_string(int64_t f) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m1_float_to_string(f));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t string_to_float(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m1_string_to_float(s));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int main(void) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t stock;
int64_t _;
  int _m1_ret = 0;
  _m1_ret = (stock = 50, _ = ({ if (!((stock >= 0))) { fprintf(stderr, "H:/AI-Focused_language/src/m1/_inj_task8_inventory.m1:81:23: error: [M1103] 'now' assertion violated: (invariant)\n"); exit(1); } 0; }), _ = ({ if ((stock < 10)) { say("reorder"); } 0; }), _ = ({ (stock = 30); if ((stock < 10)) { say("reorder"); } stock; }), _ = ({ (stock = 8); if ((stock < 10)) { say("reorder"); } stock; }), _ = say(int_to_string(stock)), _ = ({ (stock = 20); if ((stock < 10)) { say("reorder"); } stock; }), _ = say(int_to_string(stock)), 0);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
