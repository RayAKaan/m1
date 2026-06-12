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


char* m0_string_concat(char*, char*);
int64_t m0_string_length(char*);
char* m0_string_substr(char*, int64_t, int64_t);
int64_t m0_string_eq(char*, char*);
int64_t m0_string_to_int(char*);
char* m0_int_to_string(int64_t);
int64_t m0_string_char_at(char*, int64_t);
char* m0_string_to_lower(char*);
char* m0_string_to_upper(char*);

char* std_string__concat(char* a, char* b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = m0_string_concat(a, b);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__length(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_string_length(s);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* std_string__substr(char* s, int64_t start, int64_t len) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = m0_string_substr(s, start, len);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__equals(char* a, char* b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_string_eq(a, b);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__char_at(char* s, int64_t idx) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_string_char_at(s, idx);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* std_string__to_lower(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = m0_string_to_lower(s);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* std_string__to_upper(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = m0_string_to_upper(s);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__starts_with(char* s, char* prefix) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = ((std_string__length(s) < std_string__length(prefix)) ? 0 : std_string__equals(std_string__substr(s, 0, std_string__length(prefix)), prefix));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__ends_with(char* s, char* suffix) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = ((std_string__length(s) < std_string__length(suffix)) ? 0 : std_string__equals(std_string__substr(s, (std_string__length(s) - std_string__length(suffix)), std_string__length(suffix)), suffix));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__contains_loop(char* s, char* sub, int64_t i) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = ((i > (std_string__length(s) - std_string__length(sub))) ? 0 : ((std_string__equals(std_string__substr(s, i, std_string__length(sub)), sub) == 1) ? 1 : std_string__contains_loop(s, sub, (i + 1))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__contains(char* s, char* sub) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = ((std_string__length(sub) == 0) ? 1 : ((std_string__length(s) < std_string__length(sub)) ? 0 : std_string__contains_loop(s, sub, 0)));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t std_string__to_int(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_string_to_int(s);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* std_string__from_int(int64_t i) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = m0_int_to_string(i);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}

int64_t m0_println(char*);
char* m0_int_to_string(int64_t);

int64_t main__say(char* s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = m0_println(s);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* main__int_to_string(int64_t n) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = m0_int_to_string(n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int main(void) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int _m1_ret = 0;
  _m1_ret = (main__say(main__int_to_string(std_string__length(std_string__concat("hello", " world")))), (main__say(main__int_to_string(std_string__equals("hello world", std_string__concat("hello", " world")))), (main__say(main__int_to_string(std_string__starts_with(std_string__concat("hello", " world"), "hello"))), (main__say(main__int_to_string(std_string__ends_with(std_string__concat("hello", " world"), "world"))), (main__say(main__int_to_string(std_string__contains(std_string__concat("hello", " world"), "lo w"))), (main__say(main__int_to_string(std_string__contains(std_string__concat("hello", " world"), "xyz"))), (main__say(main__int_to_string(std_string__to_int("42"))), (main__say(std_string__from_int(99)), 0))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
