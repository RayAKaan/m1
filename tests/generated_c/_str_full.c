#include <stdio.h>
#include <stdint.h>


int64_t m0_println(char*);
char* m0_int_to_string(int64_t);
int64_t m0_string_to_int(char*);
int64_t m1_char_at(char*, int64_t);
char* m1_substring(char*, int64_t, int64_t);
int64_t m1_string_split(char*, char*);
int64_t m1_vector_new(void);
int64_t m1_vector_push(int64_t, int64_t);
int64_t m1_vector_get(int64_t, int64_t);
int64_t m1_vector_len(int64_t);
char* m1_vector_get_str(int64_t, int64_t);

int64_t println(char* s) {
  return m0_println(s);
}
char* int_to_string(int64_t n) {
  return m0_int_to_string(n);
}
int64_t string_to_int(char* s) {
  return m0_string_to_int(s);
}
int64_t char_at(char* s, int64_t i) {
  return m1_char_at(s, i);
}
char* substring(char* s, int64_t start, int64_t len) {
  return m1_substring(s, start, len);
}
int64_t string_split(char* s, char* delim) {
  return m1_string_split(s, delim);
}
int64_t vector_new() {
  return m1_vector_new();
}
int64_t vector_push(int64_t v, int64_t x) {
  return m1_vector_push(v, x);
}
int64_t vector_get(int64_t v, int64_t i) {
  return m1_vector_get(v, i);
}
int64_t vector_len(int64_t v) {
  return m1_vector_len(v);
}
char* vector_get_str(int64_t v, int64_t i) {
  return m1_vector_get_str(v, i);
}
int main(void) {
  return ({ char* s = "Hello, World"; ({ int64_t _ = println(int_to_string(char_at(s, 0))); ({ int64_t _ = println(substring(s, 7, 5)); ({ int64_t parts = string_split("10 20 30", " "); ({ int64_t i = 0; ({ int64_t sum = 0; ({ int64_t _ = ({ while ((i < vector_len(parts))) { ({ char* part = vector_get_str(parts, i); (sum = (sum + string_to_int(part))); }); } 0; }); 0; }); }); }); }); }); }); });
}
