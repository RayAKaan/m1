#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* runtime function declarations */
int64_t say(const char* s);
int64_t show(const char* s);
const char* string_concat(const char* a, const char* b);
char* int_to_string(int64_t n);
int64_t string_len(const char* s);
int64_t string_to_int(const char* s);
const char* read_file(const char* path);
int64_t write_file(const char* path, const char* content);
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



int main(void) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int _m1_ret = 0;
  _m1_ret = ({ int64_t Setup = 0; ({ int64_t Playing = 1; ({ int64_t Paused = 2; ({ int64_t GameOver = 3; ({ int64_t state = Setup; ({ int64_t score = 0; ({ int64_t _ = ({ if (!((score >= 0))) { fprintf(stderr, "H:\AI-Focused_language\tests\benchmark\task10_game.m1:10:23: error: [M1103] 'now' assertion violated: (invariant)\n"); exit(1); } 0; }); ({ int64_t _ = ({ if ((score >= 100)) { say("win"); } 0; }); ({ int64_t _ = ({ (state = Playing); state; }); ({ int64_t _ = say(int_to_string(1)); ({ int64_t _ = ({ (score = 50); if ((score >= 100)) { say("win"); } score; }); ({ int64_t _ = ({ (score = 100); if ((score >= 100)) { say("win"); } score; }); ({ int64_t _ = ({ (state = GameOver); state; }); ({ int64_t _ = say(int_to_string(1)); ({ int64_t _ = say(int_to_string(score)); 0; }); }); }); }); }); }); }); }); }); }); }); }); }); }); });
__m1_return:
  return _m1_ret;
}
