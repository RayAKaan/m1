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

typedef struct { int64_t kind; int64_t line; int64_t col; int64_t int_val; char* str_val; } M1Token;
typedef struct { char* src; int64_t pos; int64_t line; int64_t col; } M1Lexer;
typedef struct { M1Token token; M1Lexer lexer; } M1LexResult;
typedef struct { M1Token tk; M1Lexer lx; int64_t err; } PS;
typedef struct { int64_t node; PS st; } PR;

char* m0_read_file(char*);
int64_t m0_print(char*);
int64_t m0_print_int(int64_t);
int64_t m0_string_eq(char*, char*);
int64_t m0_get(int64_t, int64_t);
char* m0_load_string(int64_t, int64_t);
int64_t m0_is_nil(int64_t);
int64_t m0_head(int64_t);
int64_t m0_tail(int64_t);
int64_t m0_alloc(int64_t);
int64_t m0_set(int64_t, int64_t, int64_t);
int64_t m0_store_string(int64_t, int64_t, char*);
int64_t m0_cons(int64_t, int64_t);
int64_t m0_nil;
int64_t m0_list_length(int64_t);
char* m0_get_env(char*);
int64_t phase_graph_init;
int64_t phase_graph_record(char*, char*);
int64_t phase_graph_freeze(char*);
int64_t phase_graph_query(char*, char*);
int64_t phase_graph_will_check(char*, char*);
M1Lexer m1_lexer_init(char*);
M1LexResult m1_lexer_next(M1Lexer);

int64_t M1C__ps_kind(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (s.tk.kind);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__ps_line(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (s.tk.line);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__ps_col(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (s.tk.col);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* M1C__ps_str(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (s.tk.str_val);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__ps_int(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (s.tk.int_val);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PS M1C__ps_adv(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
M1LexResult r;
  PS _m1_ret = 0;
  _m1_ret = (r = m1_lexer_next(s.lx), { .tk = r.token, .lx = r.lexer, .err = s.err });
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PS M1C__ps_err(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  PS _m1_ret = 0;
  _m1_ret = ({ .tk = s.tk, .lx = s.lx, .err = (s.err + 1) });
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__mk_pr(int64_t n, PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  PR _m1_ret = 0;
  _m1_ret = ({ .node = n, .st = s });
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__nk(int64_t k, int64_t line, int64_t col, int64_t sz) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = m0_alloc(sz), s0 = m0_set(n, 0, k), s1 = m0_set(n, 1, line), s2 = m0_set(n, 2, col), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_int(int64_t v, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_INT, line, col, 4), s = m0_set(n, 3, v), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_str(char* v, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_STRING, line, col, 4), s = m0_store_string(n, 3, v), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_bool(int64_t v, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_BOOL, line, col, 4), s = m0_set(n, 3, v), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_unit(int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (M1C__nk(N_UNIT, line, col, 3));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_name(char* nm, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_NAME, line, col, 4), s = m0_store_string(n, 3, nm), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_bin(int64_t op, int64_t l, int64_t r, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_BINARY, line, col, 6), s0 = m0_set(n, 3, op), s1 = m0_set(n, 4, l), s2 = m0_set(n, 5, r), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_not(int64_t e, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_NOT, line, col, 4), s = m0_set(n, 3, e), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_field(int64_t e, char* nm, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_FIELD, line, col, 5), s0 = m0_set(n, 3, e), s1 = m0_store_string(n, 4, nm), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_call(int64_t e, int64_t args, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_CALL, line, col, 6), s0 = m0_set(n, 3, e), s1 = m0_set(n, 4, args), s2 = m0_set(n, 5, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_let(char* nm, int64_t ty, int64_t v, int64_t body, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
int64_t s3;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_LET, line, col, 7), s0 = m0_store_string(n, 3, nm), s1 = m0_set(n, 4, ty), s2 = m0_set(n, 5, v), s3 = m0_set(n, 6, body), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_match(int64_t sc, int64_t arms, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_MATCH, line, col, 6), s0 = m0_set(n, 3, sc), s1 = m0_set(n, 4, arms), s2 = m0_set(n, 5, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_if(int64_t c, int64_t t, int64_t e, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_IF, line, col, 6), s0 = m0_set(n, 3, c), s1 = m0_set(n, 4, t), s2 = m0_set(n, 5, e), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_record(int64_t fields, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_RECORD, line, col, 5), s0 = m0_set(n, 3, fields), s1 = m0_set(n, 4, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_assign(char* nm, int64_t v, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_ASSIGN, line, col, 5), s0 = m0_store_string(n, 3, nm), s1 = m0_set(n, 4, v), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_while(int64_t cond, int64_t body, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_WHILE, line, col, 5), s0 = m0_set(n, 3, cond), s1 = m0_set(n, 4, body), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__t_name(char* nm, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(T_NAMED, line, col, 4), s = m0_store_string(n, 3, nm), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__t_fn(int64_t params, int64_t cnt, int64_t ret, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(T_FN, line, col, 6), s0 = m0_set(n, 3, params), s1 = m0_set(n, 4, cnt), s2 = m0_set(n, 5, ret), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__t_record(int64_t fields, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(T_RECORD, line, col, 5), s0 = m0_set(n, 3, fields), s1 = m0_set(n, 4, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__t_sum(int64_t ctors, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(T_SUM, line, col, 5), s0 = m0_set(n, 3, ctors), s1 = m0_set(n, 4, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__t_app(int64_t base, int64_t args, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(T_APP, line, col, 6), s0 = m0_set(n, 3, base), s1 = m0_set(n, 4, args), s2 = m0_set(n, 5, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__mk_param(char* nm, int64_t ty) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = m0_alloc(2), s0 = m0_store_string(n, 0, nm), s1 = m0_set(n, 1, ty), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__mk_fi(char* nm, int64_t v) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = m0_alloc(2), s0 = m0_store_string(n, 0, nm), s1 = m0_set(n, 1, v), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__mk_arm(int64_t p, int64_t b) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = m0_alloc(2), s0 = m0_set(n, 0, p), s1 = m0_set(n, 1, b), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__mk_ctor(char* nm, int64_t ty) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = m0_alloc(2), s0 = m0_store_string(n, 0, nm), s1 = m0_set(n, 1, ty), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__p_wild(int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (M1C__nk(P_WILD, line, col, 3));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__p_lit(int64_t e, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(P_LIT, line, col, 4), s = m0_set(n, 3, e), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__p_ctor(char* nm, int64_t arg, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(P_CTOR, line, col, 5), s0 = m0_store_string(n, 3, nm), s1 = m0_set(n, 4, arg), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__p_name(char* nm, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(P_NAME, line, col, 4), s = m0_store_string(n, 3, nm), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_type_decl(char* nm, int64_t ty, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_TYPE_DECL, line, col, 5), s0 = m0_store_string(n, 3, nm), s1 = m0_set(n, 4, ty), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_fn_decl(char* nm, int64_t params, int64_t pc, int64_t ret, int64_t body, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
int64_t s3;
int64_t s4;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_FN_DECL, line, col, 8), s0 = m0_store_string(n, 3, nm), s1 = m0_set(n, 4, params), s2 = m0_set(n, 5, pc), s3 = m0_set(n, 6, ret), s4 = m0_set(n, 7, body), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_extern(char* cn, int64_t ty, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_EXTERN, line, col, 5), s0 = m0_store_string(n, 3, cn), s1 = m0_set(n, 4, ty), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_mod(char* nm, int64_t decls, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_MOD, line, col, 6), s0 = m0_store_string(n, 3, nm), s1 = m0_set(n, 4, decls), s2 = m0_set(n, 5, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__n_prog(int64_t mods, int64_t cnt, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t n;
int64_t s0;
int64_t s1;
  int64_t _m1_ret = 0;
  _m1_ret = (n = M1C__nk(N_PROG, line, col, 5), s0 = m0_set(n, 3, mods), s1 = m0_set(n, 4, cnt), n);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__list_rev(int64_t l, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (acc) : (M1C__list_rev(m0_tail(l), m0_cons(m0_head(l), acc)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__rev(int64_t l) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (M1C__list_rev(l, m0_nil));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__list_len(int64_t l) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : ((1 + M1C__list_len(m0_tail(l))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_type_fields(PS s, int64_t acc, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* nm;
PS s2;
PR r;
int64_t f;
PS s3;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RBRACE) ? (M1C__mk_pr(M1C__t_record(M1C__rev(acc), M1C__list_len(acc), line, col), M1C__ps_adv(s))) : (nm = M1C__ps_str(s), s2 = M1C__ps_adv(M1C__ps_adv(s)), r = M1C__parse_type_expr(s2), f = M1C__mk_fi(nm, r.node), s3 = ((M1C__ps_kind(r.st) == TK_COMMA) ? (M1C__ps_adv(r.st)) : (r.st)), M1C__gather_type_fields(s3, m0_cons(f, acc), line, col))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_ctors(PS s, int64_t acc, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* nm;
PS s2;
PR arg_r;
PR r;
int64_t c;
int64_t acc2;
  PR _m1_ret = 0;
  _m1_ret = (nm = M1C__ps_str(s), s2 = M1C__ps_adv(s), arg_r = ((M1C__ps_kind(s2) == TK_LPAREN) ? (r = M1C__parse_type_expr(M1C__ps_adv(s2)), M1C__mk_pr(r.node, M1C__ps_adv(r.st))) : (M1C__mk_pr(0, s2))), c = M1C__mk_ctor(nm, arg_r.node), acc2 = m0_cons(c, acc), ((M1C__ps_kind(arg_r.st) == TK_PIPE) ? (M1C__gather_ctors(M1C__ps_adv(arg_r.st), acc2, line, col)) : (M1C__mk_pr(M1C__t_sum(M1C__rev(acc2), M1C__list_len(acc2), line, col), arg_r.st))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_type_atom(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t k;
int64_t line;
int64_t col;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (k = M1C__ps_kind(s), line = M1C__ps_line(s), col = M1C__ps_col(s), ((k == TK_IDENT) ? (M1C__mk_pr(M1C__t_name(M1C__ps_str(s), line, col), M1C__ps_adv(s))) : (((k == TK_LBRACE) ? (M1C__gather_type_fields(M1C__ps_adv(s), m0_nil, line, col)) : (((k == TK_PIPE) ? (M1C__gather_ctors(M1C__ps_adv(s), m0_nil, line, col)) : (((k == TK_LPAREN) ? (r = M1C__parse_type_expr(M1C__ps_adv(s)), M1C__mk_pr(r.node, M1C__ps_adv(r.st))) : (M1C__mk_pr(M1C__n_unit(line, col), M1C__ps_err(s)))))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_type_app_ga(int64_t base_node, PS s, int64_t acc, int64_t line, int64_t col) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR ar;
PS s2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RPAREN) ? (M1C__mk_pr(M1C__t_app(base_node, M1C__rev(acc), M1C__list_len(acc), line, col), M1C__ps_adv(s))) : (ar = M1C__parse_type_expr(s), s2 = ((M1C__ps_kind(ar.st) == TK_COMMA) ? (M1C__ps_adv(ar.st)) : (ar.st)), M1C__parse_type_app_ga(base_node, s2, m0_cons(ar.node, acc), line, col))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_type_app(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
int64_t line;
int64_t col;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_type_atom(s), ((M1C__ps_kind(r.st) == TK_LPAREN) ? (line = M1C__ps_line(r.st), col = M1C__ps_col(r.st), M1C__parse_type_app_ga(r.node, M1C__ps_adv(r.st), m0_nil, line, col)) : (r)));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_type_arrow(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_type_app(s), ((M1C__ps_kind(r.st) == TK_ARROW) ? (r2 = M1C__parse_type_arrow(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__t_fn(m0_cons(r.node, m0_nil), 1, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (r)));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_type_expr(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  PR _m1_ret = 0;
  _m1_ret = (M1C__parse_type_arrow(s));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_params(PS s, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* nm;
PS s2;
PR r;
int64_t p;
PS s3;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RPAREN) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (((M1C__ps_kind(s) == TK_UNIT) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (nm = M1C__ps_str(s), s2 = M1C__ps_adv(M1C__ps_adv(s)), r = M1C__parse_type_expr(s2), p = M1C__mk_param(nm, r.node), s3 = ((M1C__ps_kind(r.st) == TK_COMMA) ? (M1C__ps_adv(r.st)) : (r.st)), M1C__gather_params(s3, m0_cons(p, acc)))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_pat_atom(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t k;
int64_t line;
int64_t col;
char* nm;
PS s2;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (k = M1C__ps_kind(s), line = M1C__ps_line(s), col = M1C__ps_col(s), ((k == TK_INT) ? (M1C__mk_pr(M1C__p_lit(M1C__n_int(M1C__ps_int(s), line, col), line, col), M1C__ps_adv(s))) : (((k == TK_TRUE) ? (M1C__mk_pr(M1C__p_lit(M1C__n_bool(1, line, col), line, col), M1C__ps_adv(s))) : (((k == TK_FALSE) ? (M1C__mk_pr(M1C__p_lit(M1C__n_bool(0, line, col), line, col), M1C__ps_adv(s))) : (((k == TK_IDENT) ? (nm = M1C__ps_str(s), s2 = M1C__ps_adv(s), ((m0_string_eq(nm, "_") == 1) ? (M1C__mk_pr(M1C__p_wild(line, col), s2)) : (((M1C__ps_kind(s2) == TK_LPAREN) ? (r = M1C__parse_pat_atom(M1C__ps_adv(s2)), M1C__mk_pr(M1C__p_ctor(nm, r.node, line, col), M1C__ps_adv(r.st))) : (M1C__mk_pr(M1C__p_name(nm, line, col), s2)))))) : (M1C__mk_pr(M1C__p_wild(line, col), M1C__ps_err(s)))))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_args(PS s, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
PS s2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RPAREN) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (((M1C__ps_kind(s) == TK_UNIT) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (r = M1C__parse_impl(s), s2 = ((M1C__ps_kind(r.st) == TK_COMMA) ? (M1C__ps_adv(r.st)) : (r.st)), M1C__gather_args(s2, m0_cons(r.node, acc)))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_postfix_loop(int64_t n, PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* nm;
PR ar;
PR vr;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_DOT) ? (nm = M1C__ps_str(M1C__ps_adv(s)), M1C__parse_postfix_loop(M1C__n_field(n, nm, M1C__ps_line(s), M1C__ps_col(s)), M1C__ps_adv(M1C__ps_adv(s)))) : (((M1C__ps_kind(s) == TK_LPAREN) ? (ar = M1C__gather_args(M1C__ps_adv(s), m0_nil), M1C__parse_postfix_loop(M1C__n_call(n, ar.node, M1C__list_len(ar.node), M1C__ps_line(s), M1C__ps_col(s)), ar.st)) : (((M1C__ps_kind(s) == TK_UNIT) ? (M1C__parse_postfix_loop(M1C__n_call(n, m0_nil, 0, M1C__ps_line(s), M1C__ps_col(s)), M1C__ps_adv(s))) : (((M1C__ps_kind(s) == TK_EQ) ? (nm = m0_load_string(n, 3), vr = M1C__parse_expr(M1C__ps_adv(s)), M1C__mk_pr(M1C__n_assign(nm, vr.node, M1C__ps_line(s), M1C__ps_col(s)), vr.st)) : (M1C__mk_pr(n, s))))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_postfix(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_atom(s), M1C__parse_postfix_loop(r.node, r.st));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_unary(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_NOT) ? (r = M1C__parse_unary(M1C__ps_adv(s)), M1C__mk_pr(M1C__n_not(r.node, M1C__ps_line(s), M1C__ps_col(s)), r.st)) : (((M1C__ps_kind(s) == TK_MINUS) ? (r = M1C__parse_unary(M1C__ps_adv(s)), M1C__mk_pr(M1C__n_bin(OP_SUB, M1C__n_int(0, M1C__ps_line(s), M1C__ps_col(s)), r.node, M1C__ps_line(s), M1C__ps_col(s)), r.st)) : (M1C__parse_postfix(s))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_mul_loop(int64_t l, PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_STAR) ? (r2 = M1C__parse_unary(M1C__ps_adv(s)), M1C__parse_mul_loop(M1C__n_bin(OP_MUL, l, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (((M1C__ps_kind(s) == TK_SLASH) ? (r2 = M1C__parse_unary(M1C__ps_adv(s)), M1C__parse_mul_loop(M1C__n_bin(OP_DIV, l, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (((M1C__ps_kind(s) == TK_PERCENT) ? (r2 = M1C__parse_unary(M1C__ps_adv(s)), M1C__parse_mul_loop(M1C__n_bin(OP_MOD, l, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (M1C__mk_pr(l, s))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_mul(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_unary(s), M1C__parse_mul_loop(r.node, r.st));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_add_loop(int64_t l, PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_PLUS) ? (r2 = M1C__parse_mul(M1C__ps_adv(s)), M1C__parse_add_loop(M1C__n_bin(OP_ADD, l, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (((M1C__ps_kind(s) == TK_MINUS) ? (r2 = M1C__parse_mul(M1C__ps_adv(s)), M1C__parse_add_loop(M1C__n_bin(OP_SUB, l, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (M1C__mk_pr(l, s))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_add(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_mul(s), M1C__parse_add_loop(r.node, r.st));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_cmp(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
int64_t k;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_add(s), k = M1C__ps_kind(r.st), ((k == TK_EQEQ) ? (r2 = M1C__parse_add(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__n_bin(OP_EQ, r.node, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (((k == TK_NEQ) ? (r2 = M1C__parse_add(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__n_bin(OP_NEQ, r.node, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (((k == TK_LT) ? (r2 = M1C__parse_add(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__n_bin(OP_LT, r.node, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (((k == TK_GT) ? (r2 = M1C__parse_add(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__n_bin(OP_GT, r.node, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (((k == TK_LE) ? (r2 = M1C__parse_add(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__n_bin(OP_LE, r.node, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (((k == TK_GE) ? (r2 = M1C__parse_add(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__n_bin(OP_GE, r.node, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (r)))))))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_and_loop(int64_t l, PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_AND) ? (r2 = M1C__parse_cmp(M1C__ps_adv(s)), M1C__parse_and_loop(M1C__n_bin(OP_AND, l, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (M1C__mk_pr(l, s))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_and(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_cmp(s), M1C__parse_and_loop(r.node, r.st));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_or_loop(int64_t l, PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_OR) ? (r2 = M1C__parse_and(M1C__ps_adv(s)), M1C__parse_or_loop(M1C__n_bin(OP_OR, l, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (M1C__mk_pr(l, s))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_or(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_and(s), M1C__parse_or_loop(r.node, r.st));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_impl(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__parse_or(s), ((M1C__ps_kind(r.st) == TK_ARROW) ? (r2 = M1C__parse_impl(M1C__ps_adv(r.st)), M1C__mk_pr(M1C__n_bin(OP_IMPL, r.node, r2.node, M1C__ps_line(r.st), M1C__ps_col(r.st)), r2.st)) : (r)));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_expr(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r1;
PR r2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_BIDI) ? (r1 = M1C__parse_impl(M1C__ps_adv(s)), ((M1C__ps_kind(r1.st) == TK_BIDI) ? (r2 = M1C__parse_impl(M1C__ps_adv(r1.st)), M1C__mk_pr(M1C__n_bin(OP_IFF, r1.node, r2.node, M1C__ps_line(s), M1C__ps_col(s)), r2.st)) : (M1C__mk_pr(r1.node, M1C__ps_err(r1.st))))) : (M1C__parse_impl(s))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_arms(PS s, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR pr;
PS s2;
PR br;
PS s3;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RBRACE) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (pr = M1C__parse_pat_atom(s), s2 = M1C__ps_adv(pr.st), br = M1C__parse_expr(s2), s3 = M1C__ps_adv(br.st), M1C__gather_arms(s3, m0_cons(M1C__mk_arm(pr.node, br.node), acc)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_field_inits(PS s, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* nm;
PS s2;
PR r;
PS s3;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RBRACE) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (((M1C__ps_kind(s) == TK_EOF) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_err(s))) : (nm = M1C__ps_str(s), s2 = M1C__ps_adv(M1C__ps_adv(s)), r = M1C__parse_impl(s2), s3 = ((M1C__ps_kind(r.st) == TK_COMMA) ? (M1C__ps_adv(r.st)) : (r.st)), M1C__gather_field_inits(s3, m0_cons(M1C__mk_fi(nm, r.node), acc)))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_list_elems(PS s, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
PS s2;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RBRACK) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (r = M1C__parse_impl(s), s2 = ((M1C__ps_kind(r.st) == TK_COMMA) ? (M1C__ps_adv(r.st)) : (r.st)), M1C__gather_list_elems(s2, m0_cons(r.node, acc)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_atom(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t k;
int64_t line;
int64_t col;
PS s_after_let;
int64_t is_mut;
PS nm_ps;
char* nm;
PS s_after_name;
PS s_after_colon;
PR tr;
PS s_after_type;
PR vr;
PS s_after_val;
PR br;
PR sr;
PR ar;
PR cr;
PS s2;
PS s3;
PR er;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (k = M1C__ps_kind(s), line = M1C__ps_line(s), col = M1C__ps_col(s), ((k == TK_INT) ? (M1C__mk_pr(M1C__n_int(M1C__ps_int(s), line, col), M1C__ps_adv(s))) : (((k == TK_STRING) ? (M1C__mk_pr(M1C__n_str(M1C__ps_str(s), line, col), M1C__ps_adv(s))) : (((k == TK_TRUE) ? (M1C__mk_pr(M1C__n_bool(1, line, col), M1C__ps_adv(s))) : (((k == TK_FALSE) ? (M1C__mk_pr(M1C__n_bool(0, line, col), M1C__ps_adv(s))) : (((k == TK_UNIT) ? (M1C__mk_pr(M1C__n_unit(line, col), M1C__ps_adv(s))) : (((k == TK_IDENT) ? (M1C__mk_pr(M1C__n_name(M1C__ps_str(s), line, col), M1C__ps_adv(s))) : (((k == TK_LET) ? (s_after_let = M1C__ps_adv(s), is_mut = ((m0_string_eq(M1C__ps_str(s_after_let), "mut") == 1) ? (1) : (0)), nm_ps = ((is_mut == 1) ? (M1C__ps_adv(s_after_let)) : (s_after_let)), nm = M1C__ps_str(nm_ps), s_after_name = M1C__ps_adv(nm_ps), s_after_colon = M1C__ps_adv(s_after_name), tr = M1C__parse_type_expr(s_after_colon), s_after_type = M1C__ps_adv(tr.st), vr = M1C__parse_expr(s_after_type), s_after_val = M1C__ps_adv(vr.st), br = M1C__parse_expr(s_after_val), M1C__mk_pr(M1C__n_let(nm, tr.node, vr.node, br.node, line, col), br.st)) : (((k == TK_MATCH) ? (sr = M1C__parse_expr(M1C__ps_adv(s)), ar = M1C__gather_arms(M1C__ps_adv(sr.st), m0_nil), M1C__mk_pr(M1C__n_match(sr.node, ar.node, M1C__list_len(ar.node), line, col), ar.st)) : (((k == TK_IF) ? (cr = M1C__parse_expr(M1C__ps_adv(s)), s2 = M1C__ps_adv(cr.st), tr = M1C__parse_expr(s2), s3 = M1C__ps_adv(tr.st), er = ((M1C__ps_kind(s3) == TK_ELSE) ? (((M1C__ps_kind(M1C__ps_adv(s3)) == TK_LBRACE) ? (r = M1C__parse_expr(M1C__ps_adv(s3)), M1C__mk_pr(r.node, M1C__ps_adv(r.st))) : (M1C__parse_expr(M1C__ps_adv(s3))))) : (M1C__mk_pr(M1C__n_unit(line, col), s3))), M1C__mk_pr(M1C__n_if(cr.node, tr.node, er.node, line, col), er.st)) : (((k == TK_WHILE) ? (cr = M1C__parse_expr(M1C__ps_adv(s)), s2 = M1C__ps_adv(cr.st), br = M1C__parse_expr(s2), M1C__mk_pr(M1C__n_while(cr.node, br.node, line, col), br.st)) : (((k == TK_LBRACE) ? (M1C__gather_field_inits(M1C__ps_adv(s), m0_nil)) : (((k == TK_LBRACK) ? (M1C__gather_list_elems(M1C__ps_adv(s), m0_nil)) : (((k == TK_LPAREN) ? (r = M1C__parse_expr(M1C__ps_adv(s)), M1C__mk_pr(r.node, M1C__ps_adv(r.st))) : (M1C__mk_pr(M1C__n_unit(line, col), M1C__ps_err(s)))))))))))))))))))))))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_decl(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t k;
int64_t line;
int64_t col;
char* nm;
PS s2;
PR tr;
PR pr;
PR rr;
PS s3;
PR br;
PS s4;
char* cn;
  PR _m1_ret = 0;
  _m1_ret = (k = M1C__ps_kind(s), line = M1C__ps_line(s), col = M1C__ps_col(s), ((k == TK_TYPE) ? (nm = M1C__ps_str(M1C__ps_adv(s)), s2 = M1C__ps_adv(M1C__ps_adv(s)), tr = M1C__parse_type_expr(s2), M1C__mk_pr(M1C__n_type_decl(nm, tr.node, line, col), tr.st)) : (((k == TK_FN) ? (nm = M1C__ps_str(M1C__ps_adv(s)), pr = M1C__gather_params(M1C__ps_adv(M1C__ps_adv(s)), m0_nil), s2 = M1C__ps_adv(pr.st), rr = M1C__parse_type_expr(s2), s3 = M1C__ps_adv(rr.st), br = M1C__parse_expr(s3), s4 = M1C__ps_adv(br.st), M1C__mk_pr(M1C__n_fn_decl(nm, pr.node, M1C__list_len(pr.node), rr.node, br.node, line, col), s4)) : (((k == TK_EXTERNAL) ? (cn = M1C__ps_str(M1C__ps_adv(s)), s2 = M1C__ps_adv(M1C__ps_adv(s)), tr = M1C__parse_type_expr(s2), M1C__mk_pr(M1C__n_extern(cn, tr.node, line, col), tr.st)) : (M1C__mk_pr(M1C__n_unit(line, col), M1C__ps_err(s)))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_decls(PS s, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_RBRACE) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_adv(s))) : (((M1C__ps_kind(s) == TK_EOF) ? (M1C__mk_pr(M1C__rev(acc), M1C__ps_err(s))) : (r = M1C__parse_decl(s), M1C__gather_decls(r.st, m0_cons(r.node, acc)))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_module(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t line;
int64_t col;
char* nm;
PS s2;
PR dr;
  PR _m1_ret = 0;
  _m1_ret = (line = M1C__ps_line(s), col = M1C__ps_col(s), nm = M1C__ps_str(M1C__ps_adv(s)), s2 = M1C__ps_adv(M1C__ps_adv(s)), dr = M1C__gather_decls(s2, m0_nil), M1C__mk_pr(M1C__n_mod(nm, dr.node, M1C__list_len(dr.node), line, col), dr.st));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__gather_modules(PS s, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (((M1C__ps_kind(s) == TK_EOF) ? (M1C__mk_pr(M1C__rev(acc), s)) : (((M1C__ps_kind(s) == TK_MODULE) ? (r = M1C__parse_module(s), M1C__gather_modules(r.st, m0_cons(r.node, acc))) : (M1C__mk_pr(M1C__rev(acc), M1C__ps_err(s)))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
PR M1C__parse_program(PS s) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
PR r;
  PR _m1_ret = 0;
  _m1_ret = (r = M1C__gather_modules(s, m0_nil), M1C__mk_pr(M1C__n_prog(r.node, M1C__list_len(r.node), M1C__ps_line(s), M1C__ps_col(s)), r.st));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__reg_entry(char* name, int64_t t, int64_t fields) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t e;
int64_t s0;
int64_t s1;
int64_t s2;
  int64_t _m1_ret = 0;
  _m1_ret = (e = m0_alloc(3), s0 = m0_store_string(e, 0, name), s1 = m0_set(e, 1, t), s2 = m0_set(e, 2, fields), e);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
char* M1C__reg_name(int64_t e) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  char* _m1_ret = 0;
  _m1_ret = (m0_load_string(e, 0));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__reg_type(int64_t e) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m0_get(e, 1));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__reg_fields(int64_t e) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (m0_get(e, 2));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__lookup_reg(int64_t reg, char* name) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(reg) == 1) ? (0) : (((m0_string_eq(M1C__reg_name(m0_head(reg)), name) == 1) ? (m0_head(reg)) : (M1C__lookup_reg(m0_tail(reg), name))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__build_reg(int64_t decls, int64_t reg) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t d;
char* nm;
int64_t t;
int64_t fields;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(decls) == 1) ? (reg) : (d = m0_head(decls), ((m0_get(d, 0) == N_TYPE_DECL) ? (nm = m0_load_string(d, 3), t = m0_get(d, 4), fields = ((m0_get(t, 0) == T_RECORD) ? (m0_get(t, 3)) : (m0_nil)), M1C__build_reg(m0_tail(decls), m0_cons(M1C__reg_entry(nm, t, fields), reg))) : (M1C__build_reg(m0_tail(decls), reg))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_c_type(int64_t reg, int64_t t) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t k;
char* nm;
  int64_t _m1_ret = 0;
  _m1_ret = (k = m0_get(t, 0), ((k == T_NAMED) ? (nm = m0_load_string(t, 3), ((m0_string_eq(nm, "Int") == 1) ? (m0_print("int64_t")) : (((m0_string_eq(nm, "Float") == 1) ? (m0_print("double")) : (((m0_string_eq(nm, "String") == 1) ? (m0_print("char*")) : (((m0_string_eq(nm, "Bool") == 1) ? (m0_print("int")) : (((m0_string_eq(nm, "Char") == 1) ? (m0_print("char")) : (((m0_string_eq(nm, "Unit") == 1) ? (m0_print("void")) : (m0_print(nm)))))))))))))) : (((k == T_FN) ? (M1C__emit_c_type(reg, m0_get(t, 5))) : (m0_print("int64_t"))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_typedef_ef(int64_t reg, int64_t l) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t p0;
int64_t p1;
int64_t p2;
int64_t p3;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (p0 = M1C__emit_c_type(reg, m0_get(m0_head(l), 1)), p1 = m0_print(" "), p2 = m0_print(m0_load_string(m0_head(l), 0)), p3 = m0_print("; "), M1C__emit_typedef_ef(reg, m0_tail(l)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_typedef_ec(int64_t reg, int64_t l) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t arg;
int64_t _;
int64_t p0;
int64_t p1;
int64_t p2;
int64_t p3;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (arg = m0_get(m0_head(l), 1), _ = ((arg != 0) ? (p0 = M1C__emit_c_type(reg, arg), p1 = m0_print(" "), p2 = m0_print(m0_load_string(m0_head(l), 0)), p3 = m0_print("_v; "), p3) : (0)), M1C__emit_typedef_ec(reg, m0_tail(l)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_typedef(int64_t reg, int64_t t, char* name) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t k;
int64_t p0;
int64_t p1;
int64_t p2;
int64_t p3;
  int64_t _m1_ret = 0;
  _m1_ret = (k = m0_get(t, 0), ((k == T_RECORD) ? (p0 = m0_print("typedef struct { "), p1 = M1C__emit_typedef_ef(reg, m0_get(t, 3)), p2 = m0_print("} "), p3 = m0_print(name), m0_print(";\n")) : (((k == T_SUM) ? (p0 = m0_print("typedef struct { int tag; union { "), p1 = M1C__emit_typedef_ec(reg, m0_get(t, 3)), p2 = m0_print("} data; } "), p3 = m0_print(name), m0_print(";\n")) : (0)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_c_op(int64_t op) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (((op == OP_ADD) ? (m0_print("+")) : (((op == OP_SUB) ? (m0_print("-")) : (((op == OP_MUL) ? (m0_print("*")) : (((op == OP_DIV) ? (m0_print("/")) : (((op == OP_MOD) ? (m0_print("%")) : (((op == OP_EQ) ? (m0_print("==")) : (((op == OP_NEQ) ? (m0_print("!=")) : (((op == OP_LT) ? (m0_print("<")) : (((op == OP_GT) ? (m0_print(">")) : (((op == OP_LE) ? (m0_print("<=")) : (((op == OP_GE) ? (m0_print(">=")) : (((op == OP_AND) ? (m0_print("&&")) : (((op == OP_OR) ? (m0_print("||")) : (m0_print("?"))))))))))))))))))))))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_c_expr_ea(int64_t reg, int64_t l, int64_t first) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t _p0;
int64_t _p1;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (_p0 = ((first == 0) ? (m0_print(", ")) : (0)), _p1 = M1C__emit_c_expr(reg, m0_head(l)), M1C__emit_c_expr_ea(reg, m0_tail(l), 0))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_c_expr_arms_ea(int64_t reg, int64_t l, int64_t first) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t pat;
int64_t body;
int64_t pk;
int64_t _psep;
int64_t _re;
int64_t _p0;
int64_t _p1;
int64_t _p2;
int64_t _p3;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (pat = m0_get(m0_head(l), 0), body = m0_get(m0_head(l), 1), pk = m0_get(pat, 0), _psep = ((first == 0) ? (m0_print(" else ")) : (0)), _re = ((pk == P_WILD) ? (_p0 = m0_print("("), _p1 = M1C__emit_c_expr(reg, body), m0_print(")")) : (((pk == P_LIT) ? (_p0 = m0_print("("), _p1 = M1C__emit_c_expr(reg, m0_get(pat, 3)), _p2 = m0_print(" == _m ? ("), _p3 = M1C__emit_c_expr(reg, body), m0_print(") : ")) : (((pk == P_NAME) ? (_p0 = m0_print("{ int64_t "), _p1 = m0_print(m0_load_string(pat, 3)), _p2 = m0_print(" = _m; ("), _p3 = M1C__emit_c_expr(reg, body), m0_print("); }")) : (_p0 = m0_print("("), _p1 = M1C__emit_c_expr(reg, body), m0_print(")"))))))), M1C__emit_c_expr_arms_ea(reg, m0_tail(l), 0))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_c_expr_ef(int64_t reg, int64_t l, int64_t first) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t _psep;
int64_t _p0;
int64_t _p1;
int64_t _p2;
int64_t _p3;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (_psep = ((first == 0) ? (m0_print(", ")) : (0)), _p0 = m0_print("."), _p1 = m0_print(m0_load_string(m0_head(l), 0)), _p2 = m0_print(" = "), _p3 = M1C__emit_c_expr(reg, m0_get(m0_head(l), 1)), M1C__emit_c_expr_ef(reg, m0_tail(l), 0))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_fn_ep(int64_t reg, int64_t l, int64_t first) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t _psep;
int64_t _p0;
int64_t _p1;
int64_t _p2;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (_psep = ((first == 0) ? (m0_print(", ")) : (0)), _p0 = M1C__emit_c_type(reg, m0_get(m0_head(l), 1)), _p1 = m0_print(" "), _p2 = m0_print(m0_load_string(m0_head(l), 0)), M1C__emit_fn_ep(reg, m0_tail(l), 0))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_c_expr(int64_t reg, int64_t e) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t k;
int64_t _p0;
int64_t _p1;
int64_t _p2;
int64_t _p3;
int64_t _p4;
int64_t _p5;
int64_t _p6;
int64_t _p7;
int64_t el;
int64_t r2;
  int64_t _m1_ret = 0;
  _m1_ret = (k = m0_get(e, 0), ((k == N_INT) ? (m0_print_int(m0_get(e, 3))) : (((k == N_STRING) ? (_p0 = m0_print("\""), _p1 = m0_print(m0_load_string(e, 3)), m0_print("\"")) : (((k == N_BOOL) ? (((m0_get(e, 3) == 1) ? (m0_print("1")) : (m0_print("0")))) : (((k == N_UNIT) ? (m0_print("0")) : (((k == N_NAME) ? (m0_print(m0_load_string(e, 3))) : (((k == N_BINARY) ? (_p0 = m0_print("("), _p1 = M1C__emit_c_expr(reg, m0_get(e, 4)), _p2 = m0_print(" "), _p3 = M1C__emit_c_op(m0_get(e, 3)), _p4 = m0_print(" "), _p5 = M1C__emit_c_expr(reg, m0_get(e, 5)), m0_print(")")) : (((k == N_NOT) ? (_p0 = m0_print("(!"), _p1 = M1C__emit_c_expr(reg, m0_get(e, 3)), m0_print(")")) : (((k == N_FIELD) ? (_p0 = M1C__emit_c_expr(reg, m0_get(e, 3)), _p1 = m0_print("."), m0_print(m0_load_string(e, 4))) : (((k == N_CALL) ? (_p0 = M1C__emit_c_expr(reg, m0_get(e, 3)), _p1 = m0_print("("), _p2 = M1C__emit_c_expr_ea(reg, m0_get(e, 4), 1), m0_print(")")) : (((k == N_LET) ? (_p0 = m0_print("({ "), _p1 = M1C__emit_c_type(reg, m0_get(e, 4)), _p2 = m0_print(" "), _p3 = m0_print(m0_load_string(e, 3)), _p4 = m0_print(" = "), _p5 = M1C__emit_c_expr(reg, m0_get(e, 5)), _p6 = m0_print("; "), _p7 = M1C__emit_c_expr(reg, m0_get(e, 6)), m0_print("; })")) : (((k == N_IF) ? (_p0 = m0_print("("), _p1 = M1C__emit_c_expr(reg, m0_get(e, 3)), _p2 = m0_print(" ? ("), _p3 = M1C__emit_c_expr(reg, m0_get(e, 4)), _p4 = m0_print(") : ("), el = m0_get(e, 5), _p5 = ((el != 0) ? (M1C__emit_c_expr(reg, el)) : (m0_print("0"))), m0_print("))")) : (((k == N_MATCH) ? (_p0 = m0_print("({ int64_t _m = "), _p1 = M1C__emit_c_expr(reg, m0_get(e, 3)), _p2 = m0_print("; "), _p3 = M1C__emit_c_expr_arms_ea(reg, m0_get(e, 4), 1), m0_print("; })")) : (((k == N_RECORD) ? (r2 = M1C__lookup_reg(reg, m0_load_string(e, 3)), _p0 = m0_print("("), _p1 = M1C__emit_c_type(reg, M1C__reg_type(r2)), _p2 = m0_print("){ "), _p3 = M1C__emit_c_expr_ef(reg, m0_get(e, 3), 1), m0_print(" })")) : (((k == N_WHILE) ? (_p0 = m0_print("({ while ("), _p1 = M1C__emit_c_expr(reg, m0_get(e, 3)), _p2 = m0_print(") { "), _p3 = M1C__emit_c_expr(reg, m0_get(e, 4)), m0_print("; } 0; })")) : (((k == N_ASSIGN) ? (_p0 = m0_print("("), _p1 = m0_print(m0_load_string(e, 3)), _p2 = m0_print(" = "), _p3 = M1C__emit_c_expr(reg, m0_get(e, 4)), m0_print(")")) : (m0_print("0"))))))))))))))))))))))))))))))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_c_params(int64_t reg, int64_t params) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t _p0;
int64_t rest;
int64_t _p1;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(params) == 1) ? (0) : (_p0 = M1C__emit_c_type(reg, m0_head(params)), rest = m0_tail(params), _p1 = ((m0_is_nil(rest) == 0) ? (m0_print(", ")) : (0)), M1C__emit_c_params(reg, rest))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__flatten_fn_ret(int64_t t) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_get(t, 0) == T_FN) ? (M1C__flatten_fn_ret(m0_get(t, 5))) : (t)));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__flatten_fn_params(int64_t t, int64_t acc) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t p;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_get(t, 0) == T_FN) ? (p = m0_get(t, 3), M1C__flatten_fn_params(m0_get(t, 5), m0_cons(m0_head(p), acc))) : (acc)));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_extern(int64_t reg, int64_t d) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* cn;
int64_t t;
int64_t ret;
int64_t params;
int64_t _p0;
int64_t _p1;
int64_t _p2;
int64_t _p3;
int64_t _p4;
  int64_t _m1_ret = 0;
  _m1_ret = (cn = m0_load_string(d, 3), t = m0_get(d, 4), ((m0_get(t, 0) == T_FN) ? (ret = M1C__flatten_fn_ret(t), params = M1C__rev(M1C__flatten_fn_params(t, m0_nil)), _p0 = M1C__emit_c_type(reg, ret), _p1 = m0_print(" "), _p2 = m0_print(cn), _p3 = m0_print("("), _p4 = M1C__emit_c_params(reg, params), m0_print(");\n")) : (_p0 = M1C__emit_c_type(reg, t), _p1 = m0_print(" "), _p2 = m0_print(cn), m0_print(";\n"))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_fn(int64_t reg, int64_t d) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* nm;
int64_t params;
int64_t ret;
int64_t body;
int64_t is_main;
int64_t _p0;
int64_t _p1;
int64_t _p2;
int64_t _p3;
int64_t _p4;
int64_t _p5;
int64_t _p6;
  int64_t _m1_ret = 0;
  _m1_ret = (nm = m0_load_string(d, 3), params = m0_get(d, 4), ret = m0_get(d, 6), body = m0_get(d, 7), is_main = m0_string_eq(nm, "main"), _p0 = ((is_main == 1) ? (m0_print("int")) : (M1C__emit_c_type(reg, ret))), _p1 = m0_print(" "), _p2 = m0_print(nm), _p3 = m0_print("("), _p4 = ((is_main == 1) ? (m0_print("void")) : (M1C__emit_fn_ep(reg, params, 1))), _p5 = m0_print(") {\n  return "), _p6 = M1C__emit_c_expr(reg, body), m0_print(";\n}\n"));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_module_pass1(int64_t reg, int64_t l) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t d;
int64_t _e;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (d = m0_head(l), _e = ((m0_get(d, 0) == N_TYPE_DECL) ? (M1C__emit_typedef(reg, m0_get(d, 4), m0_load_string(d, 3))) : (0)), M1C__emit_module_pass1(reg, m0_tail(l)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_module_pass2(int64_t reg, int64_t l) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t d;
int64_t _e;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (d = m0_head(l), _e = ((m0_get(d, 0) == N_EXTERN) ? (M1C__emit_extern(reg, d)) : (0)), M1C__emit_module_pass2(reg, m0_tail(l)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_module_pass3(int64_t reg, int64_t l) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t d;
int64_t _e;
  int64_t _m1_ret = 0;
  _m1_ret = (((m0_is_nil(l) == 1) ? (0) : (d = m0_head(l), _e = ((m0_get(d, 0) == N_FN_DECL) ? (M1C__emit_fn(reg, d)) : (0)), M1C__emit_module_pass3(reg, m0_tail(l)))));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int64_t M1C__emit_module(int64_t m) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
int64_t decls;
int64_t reg;
int64_t _h;
int64_t _p1;
int64_t _n1;
int64_t _p2;
int64_t _n2;
int64_t _p3;
  int64_t _m1_ret = 0;
  _m1_ret = (decls = m0_get(m, 4), reg = M1C__build_reg(decls, m0_nil), _h = m0_print("#include <stdio.h>\n#include <stdint.h>\n\n"), _p1 = M1C__emit_module_pass1(reg, decls), _n1 = m0_print("\n"), _p2 = M1C__emit_module_pass2(reg, decls), _n2 = m0_print("\n"), _p3 = M1C__emit_module_pass3(reg, decls), 0);
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
int main(void) {
int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;
char* filename;
int64_t _e;
char* src;
M1Lexer l;
M1LexResult r;
PS s;
PR pr;
int64_t mods;
int64_t _em;
  int _m1_ret = 0;
  _m1_ret = (filename = m0_get_env("M1_SOURCE"), ((m0_string_eq(filename, "") == 1) ? (_e = m0_print("[M1000] error: no source file\n"), 1) : (src = m0_read_file(filename), l = m1_lexer_init(src), r = m1_lexer_next(l), s = { .tk = r.token, .lx = r.lexer, .err = 0 }, pr = M1C__parse_program(s), mods = m0_get(pr.node, 3), _em = ((m0_is_nil(mods) == 0) ? (M1C__emit_module(m0_head(mods))) : (0)), pr.st.err)));
  goto __m1_return;
__m1_return:
  return _m1_ret;
}
