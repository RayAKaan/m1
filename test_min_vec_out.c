#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* runtime function declarations */
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
int64_t char_at(const char* s, int64_t i);
char* substring(const char* s, int64_t start, int64_t len);
int64_t string_split(const char* s, const char* delim);
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
int64_t string_to_float(const char* s);


int64_t m0_vector_new(void);
int64_t m0_vector_push(int64_t, int64_t);
int64_t m0_vector_get(int64_t, int64_t);
int64_t m0_vector_set(int64_t, int64_t, int64_t);
int64_t m0_vector_length(int64_t);
int64_t m0_vector_remove(int64_t, int64_t);
char* m0_int_to_string(int64_t);
char* m0_string_concat(char*, char*);

int64_t std_vector__new() {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_vector_new();
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__push(int64_t v, int64_t val) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_vector_push(v, val);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__get(int64_t v, int64_t idx) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_vector_get(v, idx);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__set(int64_t v, int64_t idx, int64_t val) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_vector_set(v, idx, val);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__length(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_vector_length(v);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__contains(int64_t v, int64_t val) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t i;
int64_t found;
  int64_t _m1_ret = 0;
  _m1_ret = n = std_vector__length(v), i = 0, found = 0, ({ while ((i < n)) { (((std_vector__get(v, i) == val) ? ({ (found = 1); found; }) : 0), ((found ? ({ break; 0; }) : 0), (({ (i = (i + 1)); i; }), 0))); } 0; });
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__index_of(int64_t v, int64_t val) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t i;
  int64_t _m1_ret = 0;
  _m1_ret = n = std_vector__length(v), i = 0, (({ while ((i < n)) { (((std_vector__get(v, i) == val) ? ({ _m1_ret = i; goto __m1_return; 0; }) : 0), (({ (i = (i + 1)); i; }), 0)); } 0; }) - 1);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__sum(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t total;
int64_t i;
  int64_t _m1_ret = 0;
  _m1_ret = n = std_vector__length(v), total = 0, i = 0, ({ while ((i < n)) { (({ (total = (total + std_vector__get(v, i))); total; }), (({ (i = (i + 1)); i; }), 0)); } 0; });
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__max(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t result;
int64_t i;
  int64_t _m1_ret = 0;
  _m1_ret = (n = std_vector__length(v), ((n == 0) ? ({ _m1_ret = 0; goto __m1_return; 0; }) : 0), result = std_vector__get(v, 0), i = 1, ({ while ((i < n)) { (((std_vector__get(v, i) > result) ? ({ (result = std_vector__get(v, i)); result; }) : 0), (({ (i = (i + 1)); i; }), 0)); } 0; }));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__min(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t result;
int64_t i;
  int64_t _m1_ret = 0;
  _m1_ret = (n = std_vector__length(v), ((n == 0) ? ({ _m1_ret = 0; goto __m1_return; 0; }) : 0), result = std_vector__get(v, 0), i = 1, ({ while ((i < n)) { (((std_vector__get(v, i) < result) ? ({ (result = std_vector__get(v, i)); result; }) : 0), (({ (i = (i + 1)); i; }), 0)); } 0; }));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_vector__reverse(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t i;
int64_t tmp;
  int64_t _m1_ret = 0;
  _m1_ret = n = std_vector__length(v), i = 0, ({ while ((i < (n / 2))) { (tmp = std_vector__get(v, i), std_vector__set(v, i, std_vector__get(v, ((n - 1) - i))), (std_vector__set(v, ((n - 1) - i), tmp), (({ (i = (i + 1)); i; }), 0))); } 0; });
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* std_vector__to_string(int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
char* result;
int64_t i;
  char* _m1_ret = 0;
  _m1_ret = (n = std_vector__length(v), result = "[", i = 0, ({ while ((i < n)) { (({ (result = m0_string_concat(result, m0_int_to_string(std_vector__get(v, i)))); result; }), (((i < (n - 1)) ? ({ (result = m0_string_concat(result, ", ")); result; }) : 0), (({ (i = (i + 1)); i; }), 0))); } 0; }), (({ (result = m0_string_concat(result, "]")); result; }), result));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}


int main(void) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int _m1_ret = 0;
  _m1_ret = 0;
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
