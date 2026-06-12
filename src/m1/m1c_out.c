#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

/* Module: M1C */
int64_t TK_EOF = 0;
int64_t TK_INT = 1;
int64_t TK_STRING = 3;
int64_t TK_IDENT = 5;
int64_t TK_ARROW = 6;
int64_t TK_LARROW = 7;
int64_t TK_BIDI = 8;
int64_t TK_EQ = 9;
int64_t TK_EQEQ = 10;
int64_t TK_NEQ = 11;
int64_t TK_LT = 12;
int64_t TK_GT = 13;
int64_t TK_LE = 14;
int64_t TK_GE = 15;
int64_t TK_AND = 16;
int64_t TK_OR = 17;
int64_t TK_PIPE = 18;
int64_t TK_COLON = 19;
int64_t TK_COMMA = 20;
int64_t TK_DOT = 21;
int64_t TK_SEMI = 22;
int64_t TK_LBRACE = 24;
int64_t TK_RBRACE = 25;
int64_t TK_LPAREN = 26;
int64_t TK_RPAREN = 27;
int64_t TK_LBRACK = 28;
int64_t TK_RBRACK = 29;
int64_t TK_PLUS = 30;
int64_t TK_MINUS = 31;
int64_t TK_STAR = 32;
int64_t TK_SLASH = 33;
int64_t TK_PERCENT = 34;
int64_t TK_UNIT = 35;
int64_t TK_MODULE = 36;
int64_t TK_TYPE = 37;
int64_t TK_FN = 38;
int64_t TK_LET = 39;
int64_t TK_MATCH = 40;
int64_t TK_IF = 41;
int64_t TK_ELSE = 42;
int64_t TK_TRUE = 43;
int64_t TK_FALSE = 44;
int64_t TK_EXTERNAL = 45;
int64_t TK_NOT = 46;
int64_t TK_FORALL = 47;
int64_t TK_EXISTS = 48;
int64_t TK_MUT = 49;
int64_t TK_WHILE = 50;
int64_t N_PROG = 0;
int64_t N_MOD = 1;
int64_t N_TYPE_DECL = 2;
int64_t N_PROP_DECL = 3;
int64_t N_FN_DECL = 4;
int64_t N_EXTERN = 5;
int64_t N_INT = 6;
int64_t N_STRING = 7;
int64_t N_BOOL = 8;
int64_t N_UNIT = 9;
int64_t N_NAME = 10;
int64_t N_BINARY = 11;
int64_t N_NOT = 12;
int64_t N_FIELD = 13;
int64_t N_CALL = 14;
int64_t N_LET = 16;
int64_t N_LAMBDA = 17;
int64_t N_MATCH = 18;
int64_t N_IF = 19;
int64_t N_RECORD = 20;
int64_t N_LIST = 21;
int64_t N_ASSIGN = 22;
int64_t N_WHILE = 23;
int64_t T_NAMED = 100;
int64_t T_FN = 101;
int64_t T_RECORD = 102;
int64_t T_SUM = 103;
int64_t T_APP = 104;
int64_t OP_ADD = 0;
int64_t OP_SUB = 1;
int64_t OP_MUL = 2;
int64_t OP_DIV = 3;
int64_t OP_MOD = 4;
int64_t OP_EQ = 5;
int64_t OP_NEQ = 6;
int64_t OP_LT = 7;
int64_t OP_GT = 8;
int64_t OP_LE = 9;
int64_t OP_GE = 10;
int64_t OP_AND = 11;
int64_t OP_OR = 12;
int64_t OP_IMPL = 13;
int64_t OP_IFF = 14;
int64_t P_WILD = 0;
int64_t P_LIT = 1;
int64_t P_CTOR = 2;
int64_t P_NAME = 4;
typedef struct {
  int64_t kind;  
  int64_t line;  
  int64_t col;  
  int64_t int_val;  
  char* str_val;  
} M1Token;
typedef struct {
  char* src;  
  int64_t pos;  
  int64_t line;  
  int64_t col;  
} M1Lexer;
typedef struct {
  M1Token token;  
  M1Lexer lexer;  
} M1LexResult;
typedef struct {
  M1Token tk;  
  M1Lexer lx;  
  int64_t err;  
} PS;
typedef struct {
  int64_t node;  
  PS st;  
} PR;
extern char* m0_read_file(char*);
extern int64_t m0_print(char*);
extern int64_t m0_print_int(int64_t);
extern int64_t m0_string_eq(char*, char*);
extern int64_t m0_get(int64_t, int64_t);
extern char* m0_load_string(int64_t, int64_t);
extern int64_t m0_is_nil(int64_t);
extern int64_t m0_head(int64_t);
extern int64_t m0_tail(int64_t);
extern int64_t m0_alloc(int64_t);
extern int64_t m0_set(int64_t, int64_t, int64_t);
extern int64_t m0_store_string(int64_t, int64_t, char*);
extern int64_t m0_cons(int64_t, int64_t);
extern int64_t m0_nil;
extern int64_t m0_list_length(int64_t);
extern char* m0_get_env(char*);
extern M1Lexer m1_lexer_init(char*);
extern M1LexResult m1_lexer_next(M1Lexer);
int64_t ps_kind(PS s);
int64_t ps_line(PS s);
int64_t ps_col(PS s);
char* ps_str(PS s);
int64_t ps_int(PS s);
PS ps_adv(PS s);
PS ps_err(PS s);
PR mk_pr(int64_t n, PS s);
int64_t nk(int64_t k, int64_t line, int64_t col, int64_t sz);
int64_t n_int(int64_t v, int64_t line, int64_t col);
int64_t n_str(char* v, int64_t line, int64_t col);
int64_t n_bool(int64_t v, int64_t line, int64_t col);
int64_t n_unit(int64_t line, int64_t col);
int64_t n_name(char* nm, int64_t line, int64_t col);
int64_t n_bin(int64_t op, int64_t l, int64_t r, int64_t line, int64_t col);
int64_t n_not(int64_t e, int64_t line, int64_t col);
int64_t n_field(int64_t e, char* nm, int64_t line, int64_t col);
int64_t n_call(int64_t e, int64_t args, int64_t cnt, int64_t line, int64_t col);
int64_t n_let(char* nm, int64_t ty, int64_t v, int64_t body, int64_t line, int64_t col);
int64_t n_match(int64_t sc, int64_t arms, int64_t cnt, int64_t line, int64_t col);
int64_t n_if(int64_t c, int64_t t, int64_t e, int64_t line, int64_t col);
int64_t n_record(int64_t fields, int64_t cnt, int64_t line, int64_t col);
int64_t n_assign(char* nm, int64_t v, int64_t line, int64_t col);
int64_t n_while(int64_t cond, int64_t body, int64_t line, int64_t col);
int64_t t_name(char* nm, int64_t line, int64_t col);
int64_t t_fn(int64_t params, int64_t cnt, int64_t ret, int64_t line, int64_t col);
int64_t t_record(int64_t fields, int64_t cnt, int64_t line, int64_t col);
int64_t t_sum(int64_t ctors, int64_t cnt, int64_t line, int64_t col);
int64_t t_app(int64_t base, int64_t args, int64_t cnt, int64_t line, int64_t col);
int64_t mk_param(char* nm, int64_t ty);
int64_t mk_fi(char* nm, int64_t v);
int64_t mk_arm(int64_t p, int64_t b);
int64_t mk_ctor(char* nm, int64_t ty);
int64_t p_wild(int64_t line, int64_t col);
int64_t p_lit(int64_t e, int64_t line, int64_t col);
int64_t p_ctor(char* nm, int64_t arg, int64_t line, int64_t col);
int64_t p_name(char* nm, int64_t line, int64_t col);
int64_t n_type_decl(char* nm, int64_t ty, int64_t line, int64_t col);
int64_t n_fn_decl(char* nm, int64_t params, int64_t pc, int64_t ret, int64_t body, int64_t line, int64_t col);
int64_t n_extern(char* cn, int64_t ty, int64_t line, int64_t col);
int64_t n_mod(char* nm, int64_t decls, int64_t cnt, int64_t line, int64_t col);
int64_t n_prog(int64_t mods, int64_t cnt, int64_t line, int64_t col);
int64_t list_rev(int64_t l, int64_t acc);
int64_t rev(int64_t l);
int64_t list_len(int64_t l);
PR gather_type_fields(PS s, int64_t acc, int64_t line, int64_t col);
PR gather_ctors(PS s, int64_t acc, int64_t line, int64_t col);
PR parse_type_atom(PS s);
PR parse_type_app_ga(int64_t base_node, PS s, int64_t acc, int64_t line, int64_t col);
PR parse_type_app(PS s);
PR parse_type_arrow(PS s);
PR parse_type_expr(PS s);
PR gather_params(PS s, int64_t acc);
PR parse_pat_atom(PS s);
PR gather_args(PS s, int64_t acc);
PR parse_postfix_loop(int64_t n, PS s);
PR parse_postfix(PS s);
PR parse_unary(PS s);
PR parse_mul_loop(int64_t l, PS s);
PR parse_mul(PS s);
PR parse_add_loop(int64_t l, PS s);
PR parse_add(PS s);
PR parse_cmp(PS s);
PR parse_and_loop(int64_t l, PS s);
PR parse_and(PS s);
PR parse_or_loop(int64_t l, PS s);
PR parse_or(PS s);
PR parse_impl(PS s);
PR parse_expr(PS s);
PR gather_arms(PS s, int64_t acc);
PR gather_field_inits(PS s, int64_t acc);
PR gather_list_elems(PS s, int64_t acc);
PR parse_atom(PS s);
PR parse_decl(PS s);
PR gather_decls(PS s, int64_t acc);
PR parse_module(PS s);
PR gather_modules(PS s, int64_t acc);
PR parse_program(PS s);
int64_t reg_entry(char* name, int64_t t, int64_t fields);
char* reg_name(int64_t e);
int64_t reg_type(int64_t e);
int64_t reg_fields(int64_t e);
int64_t lookup_reg(int64_t reg, char* name);
int64_t build_reg(int64_t decls, int64_t reg);
int64_t emit_c_type(int64_t reg, int64_t t);
int64_t emit_typedef_ef(int64_t reg, int64_t l);
int64_t emit_typedef_ec(int64_t reg, int64_t l);
int64_t emit_typedef(int64_t reg, int64_t t, char* name);
int64_t emit_c_op(int64_t op);
int64_t emit_c_expr_ea(int64_t reg, int64_t l, int64_t first);
int64_t emit_c_expr_arms_ea(int64_t reg, int64_t l, int64_t first);
int64_t emit_c_expr_ef(int64_t reg, int64_t l, int64_t first);
int64_t emit_fn_ep(int64_t reg, int64_t l, int64_t first);
int64_t emit_c_expr(int64_t reg, int64_t e);
int64_t emit_c_params(int64_t reg, int64_t params);
int64_t flatten_fn_ret(int64_t t);
int64_t flatten_fn_params(int64_t t, int64_t acc);
int64_t emit_extern(int64_t reg, int64_t d);
int64_t emit_fn(int64_t reg, int64_t d);
int64_t emit_module_pass1(int64_t reg, int64_t l);
int64_t emit_module_pass2(int64_t reg, int64_t l);
int64_t emit_module_pass3(int64_t reg, int64_t l);
int64_t emit_module(int64_t m);
int64_t ps_kind(PS s) {
return ((s).tk).kind;}
int64_t ps_line(PS s) {
return ((s).tk).line;}
int64_t ps_col(PS s) {
return ((s).tk).col;}
char* ps_str(PS s) {
return ((s).tk).str_val;}
int64_t ps_int(PS s) {
return ((s).tk).int_val;}
PS ps_adv(PS s) {
  M1LexResult r = m1_lexer_next((s).lx);  (void)r;
return (PS){(r).token, (r).lexer, (s).err};}
PS ps_err(PS s) {
return (PS){(s).tk, (s).lx, ((s).err + 1)};}
PR mk_pr(int64_t n, PS s) {
return (PR){n, s};}
int64_t nk(int64_t k, int64_t line, int64_t col, int64_t sz) {
  int64_t n = 
m0_alloc(sz);  (void)n;
  int64_t s0 = 
m0_set(n, 0, k);  (void)s0;
  int64_t s1 = 
m0_set(n, 1, line);  (void)s1;
  int64_t s2 = 
m0_set(n, 2, col);  (void)s2;
return n;}
int64_t n_int(int64_t v, int64_t line, int64_t col) {
  int64_t n = 
nk(N_INT, line, col, 4);  (void)n;
  int64_t s = 
m0_set(n, 3, v);  (void)s;
return n;}
int64_t n_str(char* v, int64_t line, int64_t col) {
  int64_t n = 
nk(N_STRING, line, col, 4);  (void)n;
  int64_t s = 
m0_store_string(n, 3, v);  (void)s;
return n;}
int64_t n_bool(int64_t v, int64_t line, int64_t col) {
  int64_t n = 
nk(N_BOOL, line, col, 4);  (void)n;
  int64_t s = 
m0_set(n, 3, v);  (void)s;
return n;}
int64_t n_unit(int64_t line, int64_t col) {
return nk(N_UNIT, line, col, 3);}
int64_t n_name(char* nm, int64_t line, int64_t col) {
  int64_t n = 
nk(N_NAME, line, col, 4);  (void)n;
  int64_t s = 
m0_store_string(n, 3, nm);  (void)s;
return n;}
int64_t n_bin(int64_t op, int64_t l, int64_t r, int64_t line, int64_t col) {
  int64_t n = 
nk(N_BINARY, line, col, 6);  (void)n;
  int64_t s0 = 
m0_set(n, 3, op);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, l);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, r);  (void)s2;
return n;}
int64_t n_not(int64_t e, int64_t line, int64_t col) {
  int64_t n = 
nk(N_NOT, line, col, 4);  (void)n;
  int64_t s = 
m0_set(n, 3, e);  (void)s;
return n;}
int64_t n_field(int64_t e, char* nm, int64_t line, int64_t col) {
  int64_t n = 
nk(N_FIELD, line, col, 5);  (void)n;
  int64_t s0 = 
m0_set(n, 3, e);  (void)s0;
  int64_t s1 = 
m0_store_string(n, 4, nm);  (void)s1;
return n;}
int64_t n_call(int64_t e, int64_t args, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(N_CALL, line, col, 6);  (void)n;
  int64_t s0 = 
m0_set(n, 3, e);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, args);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, cnt);  (void)s2;
return n;}
int64_t n_let(char* nm, int64_t ty, int64_t v, int64_t body, int64_t line, int64_t col) {
  int64_t n = 
nk(N_LET, line, col, 7);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, ty);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, v);  (void)s2;
  int64_t s3 = 
m0_set(n, 6, body);  (void)s3;
return n;}
int64_t n_match(int64_t sc, int64_t arms, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(N_MATCH, line, col, 6);  (void)n;
  int64_t s0 = 
m0_set(n, 3, sc);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, arms);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, cnt);  (void)s2;
return n;}
int64_t n_if(int64_t c, int64_t t, int64_t e, int64_t line, int64_t col) {
  int64_t n = 
nk(N_IF, line, col, 6);  (void)n;
  int64_t s0 = 
m0_set(n, 3, c);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, t);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, e);  (void)s2;
return n;}
int64_t n_record(int64_t fields, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(N_RECORD, line, col, 5);  (void)n;
  int64_t s0 = 
m0_set(n, 3, fields);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, cnt);  (void)s1;
return n;}
int64_t n_assign(char* nm, int64_t v, int64_t line, int64_t col) {
  int64_t n = 
nk(N_ASSIGN, line, col, 5);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, v);  (void)s1;
return n;}
int64_t n_while(int64_t cond, int64_t body, int64_t line, int64_t col) {
  int64_t n = 
nk(N_WHILE, line, col, 5);  (void)n;
  int64_t s0 = 
m0_set(n, 3, cond);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, body);  (void)s1;
return n;}
int64_t t_name(char* nm, int64_t line, int64_t col) {
  int64_t n = 
nk(T_NAMED, line, col, 4);  (void)n;
  int64_t s = 
m0_store_string(n, 3, nm);  (void)s;
return n;}
int64_t t_fn(int64_t params, int64_t cnt, int64_t ret, int64_t line, int64_t col) {
  int64_t n = 
nk(T_FN, line, col, 6);  (void)n;
  int64_t s0 = 
m0_set(n, 3, params);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, cnt);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, ret);  (void)s2;
return n;}
int64_t t_record(int64_t fields, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(T_RECORD, line, col, 5);  (void)n;
  int64_t s0 = 
m0_set(n, 3, fields);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, cnt);  (void)s1;
return n;}
int64_t t_sum(int64_t ctors, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(T_SUM, line, col, 5);  (void)n;
  int64_t s0 = 
m0_set(n, 3, ctors);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, cnt);  (void)s1;
return n;}
int64_t t_app(int64_t base, int64_t args, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(T_APP, line, col, 6);  (void)n;
  int64_t s0 = 
m0_set(n, 3, base);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, args);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, cnt);  (void)s2;
return n;}
int64_t mk_param(char* nm, int64_t ty) {
  int64_t n = 
m0_alloc(2);  (void)n;
  int64_t s0 = 
m0_store_string(n, 0, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 1, ty);  (void)s1;
return n;}
int64_t mk_fi(char* nm, int64_t v) {
  int64_t n = 
m0_alloc(2);  (void)n;
  int64_t s0 = 
m0_store_string(n, 0, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 1, v);  (void)s1;
return n;}
int64_t mk_arm(int64_t p, int64_t b) {
  int64_t n = 
m0_alloc(2);  (void)n;
  int64_t s0 = 
m0_set(n, 0, p);  (void)s0;
  int64_t s1 = 
m0_set(n, 1, b);  (void)s1;
return n;}
int64_t mk_ctor(char* nm, int64_t ty) {
  int64_t n = 
m0_alloc(2);  (void)n;
  int64_t s0 = 
m0_store_string(n, 0, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 1, ty);  (void)s1;
return n;}
int64_t p_wild(int64_t line, int64_t col) {
return nk(P_WILD, line, col, 3);}
int64_t p_lit(int64_t e, int64_t line, int64_t col) {
  int64_t n = 
nk(P_LIT, line, col, 4);  (void)n;
  int64_t s = 
m0_set(n, 3, e);  (void)s;
return n;}
int64_t p_ctor(char* nm, int64_t arg, int64_t line, int64_t col) {
  int64_t n = 
nk(P_CTOR, line, col, 5);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, arg);  (void)s1;
return n;}
int64_t p_name(char* nm, int64_t line, int64_t col) {
  int64_t n = 
nk(P_NAME, line, col, 4);  (void)n;
  int64_t s = 
m0_store_string(n, 3, nm);  (void)s;
return n;}
int64_t n_type_decl(char* nm, int64_t ty, int64_t line, int64_t col) {
  int64_t n = 
nk(N_TYPE_DECL, line, col, 5);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, ty);  (void)s1;
return n;}
int64_t n_fn_decl(char* nm, int64_t params, int64_t pc, int64_t ret, int64_t body, int64_t line, int64_t col) {
  int64_t n = 
nk(N_FN_DECL, line, col, 8);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, params);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, pc);  (void)s2;
  int64_t s3 = 
m0_set(n, 6, ret);  (void)s3;
  int64_t s4 = 
m0_set(n, 7, body);  (void)s4;
return n;}
int64_t n_extern(char* cn, int64_t ty, int64_t line, int64_t col) {
  int64_t n = 
nk(N_EXTERN, line, col, 5);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, cn);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, ty);  (void)s1;
return n;}
int64_t n_mod(char* nm, int64_t decls, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(N_MOD, line, col, 6);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, nm);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, decls);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, cnt);  (void)s2;
return n;}
int64_t n_prog(int64_t mods, int64_t cnt, int64_t line, int64_t col) {
  int64_t n = 
nk(N_PROG, line, col, 5);  (void)n;
  int64_t s0 = 
m0_set(n, 3, mods);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, cnt);  (void)s1;
return n;}
int64_t list_rev(int64_t l, int64_t acc) {
  if 
(m0_is_nil(l) == 1) {    
    return acc;  
  } else {    
    return list_rev(m0_tail(l), m0_cons(m0_head(l), acc));  
  }}
int64_t rev(int64_t l) {
return list_rev(l, m0_nil);}
int64_t list_len(int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
    return (1 + list_len(m0_tail(l)));  
  }}
PR gather_type_fields(PS s, int64_t acc, int64_t line, int64_t col) {
  if 
(ps_kind(s) == TK_RBRACE) {    
    return mk_pr(t_record(rev(acc), list_len(acc), line, col), ps_adv(s));  
  } else {    
        char *nm = 
ps_str(s);    (void)nm;
    PS s2 = ps_adv(ps_adv(s));    (void)s2;
    PR r = parse_type_expr(s2);    (void)r;
    int64_t f = 
mk_fi(nm, (r).node);    (void)f;
    PS s3    ;
    if 
(ps_kind((r).st) == TK_COMMA) {      
            s3 = ps_adv((r).st);    
    } else {      
            s3 = (r).st;    
        }
    (void)s3;
return gather_type_fields(s3, m0_cons(f, acc), line, col);  
  }}
PR gather_ctors(PS s, int64_t acc, int64_t line, int64_t col) {
  char *nm = 
ps_str(s);  (void)nm;
  PS s2 = ps_adv(s);  (void)s2;
  PR arg_r  ;
  if 
(ps_kind(s2) == TK_LPAREN) {    
        PR r = parse_type_expr(ps_adv(s2));    (void)r;
    arg_r = mk_pr((r).node, ps_adv((r).st));  
  } else {    
        arg_r = mk_pr(0, s2);  
    }
  (void)arg_r;
  int64_t c = 
mk_ctor(nm, (arg_r).node);  (void)c;
  int64_t acc2 = 
m0_cons(c, acc);  (void)acc2;
  if 
(ps_kind((arg_r).st) == TK_PIPE) {    
    return gather_ctors(ps_adv((arg_r).st), acc2, line, col);  
  } else {    
    return mk_pr(t_sum(rev(acc2), list_len(acc2), line, col), (arg_r).st);  
  }}
PR parse_type_atom(PS s) {
  int64_t k = 
ps_kind(s);  (void)k;
  int64_t line = 
ps_line(s);  (void)line;
  int64_t col = 
ps_col(s);  (void)col;
  if 
(k == TK_IDENT) {    
    return mk_pr(t_name(ps_str(s), line, col), ps_adv(s));  
  } else {    
        if 
(k == TK_LBRACE) {      
      return gather_type_fields(ps_adv(s), m0_nil, line, col);    
    } else {      
            if 
(k == TK_PIPE) {        
        return gather_ctors(ps_adv(s), m0_nil, line, col);      
      } else {        
                if 
(k == TK_LPAREN) {          
                    PR r = parse_type_expr(ps_adv(s));          (void)r;
return mk_pr((r).node, ps_adv((r).st));        
        } else {          
          return mk_pr(n_unit(line, col), ps_err(s));        
        }      
      }    
    }  
  }}
PR parse_type_app_ga(int64_t base_node, PS s, int64_t acc, int64_t line, int64_t col) {
  if 
(ps_kind(s) == TK_RPAREN) {    
    return mk_pr(t_app(base_node, rev(acc), list_len(acc), line, col), ps_adv(s));  
  } else {    
        PR ar = parse_type_expr(s);    (void)ar;
    PS s2    ;
    if 
(ps_kind((ar).st) == TK_COMMA) {      
            s2 = ps_adv((ar).st);    
    } else {      
            s2 = (ar).st;    
        }
    (void)s2;
return parse_type_app_ga(base_node, s2, m0_cons((ar).node, acc), line, col);  
  }}
PR parse_type_app(PS s) {
  PR r = parse_type_atom(s);  (void)r;
  if 
(ps_kind((r).st) == TK_LPAREN) {    
        int64_t line = 
ps_line((r).st);    (void)line;
    int64_t col = 
ps_col((r).st);    (void)col;
return parse_type_app_ga((r).node, ps_adv((r).st), m0_nil, line, col);  
  } else {    
    return r;  
  }}
PR parse_type_arrow(PS s) {
  PR r = parse_type_app(s);  (void)r;
  if 
(ps_kind((r).st) == TK_ARROW) {    
        PR r2 = parse_type_arrow(ps_adv((r).st));    (void)r2;
return mk_pr(t_fn(m0_cons((r).node, m0_nil), 1, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);  
  } else {    
    return r;  
  }}
PR parse_type_expr(PS s) {
return parse_type_arrow(s);}
PR gather_params(PS s, int64_t acc) {
  if 
(ps_kind(s) == TK_RPAREN) {    
    return mk_pr(rev(acc), ps_adv(s));  
  } else {    
        if 
(ps_kind(s) == TK_UNIT) {      
      return mk_pr(rev(acc), ps_adv(s));    
    } else {      
            char *nm = 
ps_str(s);      (void)nm;
      PS s2 = ps_adv(ps_adv(s));      (void)s2;
      PR r = parse_type_expr(s2);      (void)r;
      int64_t p = 
mk_param(nm, (r).node);      (void)p;
      PS s3      ;
      if 
(ps_kind((r).st) == TK_COMMA) {        
                s3 = ps_adv((r).st);      
      } else {        
                s3 = (r).st;      
            }
      (void)s3;
return gather_params(s3, m0_cons(p, acc));    
    }  
  }}
PR parse_pat_atom(PS s) {
  int64_t k = 
ps_kind(s);  (void)k;
  int64_t line = 
ps_line(s);  (void)line;
  int64_t col = 
ps_col(s);  (void)col;
  if 
(k == TK_INT) {    
    return mk_pr(p_lit(n_int(ps_int(s), line, col), line, col), ps_adv(s));  
  } else {    
        if 
(k == TK_TRUE) {      
      return mk_pr(p_lit(n_bool(1, line, col), line, col), ps_adv(s));    
    } else {      
            if 
(k == TK_FALSE) {        
        return mk_pr(p_lit(n_bool(0, line, col), line, col), ps_adv(s));      
      } else {        
                if 
(k == TK_IDENT) {          
                    char *nm = 
ps_str(s);          (void)nm;
          PS s2 = ps_adv(s);          (void)s2;
          if 
(m0_string_eq(nm, "_") == 1) {            
            return mk_pr(p_wild(line, col), s2);          
          } else {            
                        if 
(ps_kind(s2) == TK_LPAREN) {              
                            PR r = parse_pat_atom(ps_adv(s2));              (void)r;
return mk_pr(p_ctor(nm, (r).node, line, col), ps_adv((r).st));            
            } else {              
              return mk_pr(p_name(nm, line, col), s2);            
            }          
          }        
        } else {          
          return mk_pr(p_wild(line, col), ps_err(s));        
        }      
      }    
    }  
  }}
PR gather_args(PS s, int64_t acc) {
  if 
(ps_kind(s) == TK_RPAREN) {    
    return mk_pr(rev(acc), ps_adv(s));  
  } else {    
        if 
(ps_kind(s) == TK_UNIT) {      
      return mk_pr(rev(acc), ps_adv(s));    
    } else {      
            PR r = parse_impl(s);      (void)r;
      PS s2      ;
      if 
(ps_kind((r).st) == TK_COMMA) {        
                s2 = ps_adv((r).st);      
      } else {        
                s2 = (r).st;      
            }
      (void)s2;
return gather_args(s2, m0_cons((r).node, acc));    
    }  
  }}
PR parse_postfix_loop(int64_t n, PS s) {
  if 
(ps_kind(s) == TK_DOT) {    
        char *nm = 
ps_str(ps_adv(s));    (void)nm;
return parse_postfix_loop(n_field(n, nm, ps_line(s), ps_col(s)), ps_adv(ps_adv(s)));  
  } else {    
        if 
(ps_kind(s) == TK_LPAREN) {      
            PR ar = gather_args(ps_adv(s), m0_nil);      (void)ar;
return parse_postfix_loop(n_call(n, (ar).node, list_len((ar).node), ps_line(s), ps_col(s)), (ar).st);    
    } else {      
            if 
(ps_kind(s) == TK_UNIT) {        
        return parse_postfix_loop(n_call(n, m0_nil, 0, ps_line(s), ps_col(s)), ps_adv(s));      
      } else {        
                if 
(ps_kind(s) == TK_EQ) {          
                    char *nm = 
m0_load_string(n, 3);          (void)nm;
          PR vr = parse_expr(ps_adv(s));          (void)vr;
return mk_pr(n_assign(nm, (vr).node, ps_line(s), ps_col(s)), (vr).st);        
        } else {          
          return mk_pr(n, s);        
        }      
      }    
    }  
  }}
PR parse_postfix(PS s) {
  PR r = parse_atom(s);  (void)r;
return parse_postfix_loop((r).node, (r).st);}
PR parse_unary(PS s) {
  if 
(ps_kind(s) == TK_NOT) {    
        PR r = parse_unary(ps_adv(s));    (void)r;
return mk_pr(n_not((r).node, ps_line(s), ps_col(s)), (r).st);  
  } else {    
        if 
(ps_kind(s) == TK_MINUS) {      
            PR r = parse_unary(ps_adv(s));      (void)r;
return mk_pr(n_bin(OP_SUB, n_int(0, ps_line(s), ps_col(s)), (r).node, ps_line(s), ps_col(s)), (r).st);    
    } else {      
      return parse_postfix(s);    
    }  
  }}
PR parse_mul_loop(int64_t l, PS s) {
  if 
(ps_kind(s) == TK_STAR) {    
        PR r2 = parse_unary(ps_adv(s));    (void)r2;
return parse_mul_loop(n_bin(OP_MUL, l, (r2).node, ps_line(s), ps_col(s)), (r2).st);  
  } else {    
        if 
(ps_kind(s) == TK_SLASH) {      
            PR r2 = parse_unary(ps_adv(s));      (void)r2;
return parse_mul_loop(n_bin(OP_DIV, l, (r2).node, ps_line(s), ps_col(s)), (r2).st);    
    } else {      
            if 
(ps_kind(s) == TK_PERCENT) {        
                PR r2 = parse_unary(ps_adv(s));        (void)r2;
return parse_mul_loop(n_bin(OP_MOD, l, (r2).node, ps_line(s), ps_col(s)), (r2).st);      
      } else {        
        return mk_pr(l, s);      
      }    
    }  
  }}
PR parse_mul(PS s) {
  PR r = parse_unary(s);  (void)r;
return parse_mul_loop((r).node, (r).st);}
PR parse_add_loop(int64_t l, PS s) {
  if 
(ps_kind(s) == TK_PLUS) {    
        PR r2 = parse_mul(ps_adv(s));    (void)r2;
return parse_add_loop(n_bin(OP_ADD, l, (r2).node, ps_line(s), ps_col(s)), (r2).st);  
  } else {    
        if 
(ps_kind(s) == TK_MINUS) {      
            PR r2 = parse_mul(ps_adv(s));      (void)r2;
return parse_add_loop(n_bin(OP_SUB, l, (r2).node, ps_line(s), ps_col(s)), (r2).st);    
    } else {      
      return mk_pr(l, s);    
    }  
  }}
PR parse_add(PS s) {
  PR r = parse_mul(s);  (void)r;
return parse_add_loop((r).node, (r).st);}
PR parse_cmp(PS s) {
  PR r = parse_add(s);  (void)r;
  int64_t k = 
ps_kind((r).st);  (void)k;
  if 
(k == TK_EQEQ) {    
        PR r2 = parse_add(ps_adv((r).st));    (void)r2;
return mk_pr(n_bin(OP_EQ, (r).node, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);  
  } else {    
        if 
(k == TK_NEQ) {      
            PR r2 = parse_add(ps_adv((r).st));      (void)r2;
return mk_pr(n_bin(OP_NEQ, (r).node, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);    
    } else {      
            if 
(k == TK_LT) {        
                PR r2 = parse_add(ps_adv((r).st));        (void)r2;
return mk_pr(n_bin(OP_LT, (r).node, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);      
      } else {        
                if 
(k == TK_GT) {          
                    PR r2 = parse_add(ps_adv((r).st));          (void)r2;
return mk_pr(n_bin(OP_GT, (r).node, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);        
        } else {          
                    if 
(k == TK_LE) {            
                        PR r2 = parse_add(ps_adv((r).st));            (void)r2;
return mk_pr(n_bin(OP_LE, (r).node, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);          
          } else {            
                        if 
(k == TK_GE) {              
                            PR r2 = parse_add(ps_adv((r).st));              (void)r2;
return mk_pr(n_bin(OP_GE, (r).node, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);            
            } else {              
              return r;            
            }          
          }        
        }      
      }    
    }  
  }}
PR parse_and_loop(int64_t l, PS s) {
  if 
(ps_kind(s) == TK_AND) {    
        PR r2 = parse_cmp(ps_adv(s));    (void)r2;
return parse_and_loop(n_bin(OP_AND, l, (r2).node, ps_line(s), ps_col(s)), (r2).st);  
  } else {    
    return mk_pr(l, s);  
  }}
PR parse_and(PS s) {
  PR r = parse_cmp(s);  (void)r;
return parse_and_loop((r).node, (r).st);}
PR parse_or_loop(int64_t l, PS s) {
  if 
(ps_kind(s) == TK_OR) {    
        PR r2 = parse_and(ps_adv(s));    (void)r2;
return parse_or_loop(n_bin(OP_OR, l, (r2).node, ps_line(s), ps_col(s)), (r2).st);  
  } else {    
    return mk_pr(l, s);  
  }}
PR parse_or(PS s) {
  PR r = parse_and(s);  (void)r;
return parse_or_loop((r).node, (r).st);}
PR parse_impl(PS s) {
  PR r = parse_or(s);  (void)r;
  if 
(ps_kind((r).st) == TK_ARROW) {    
        PR r2 = parse_impl(ps_adv((r).st));    (void)r2;
return mk_pr(n_bin(OP_IMPL, (r).node, (r2).node, ps_line((r).st), ps_col((r).st)), (r2).st);  
  } else {    
    return r;  
  }}
PR parse_expr(PS s) {
  if 
(ps_kind(s) == TK_BIDI) {    
        PR r1 = parse_impl(ps_adv(s));    (void)r1;
    if 
(ps_kind((r1).st) == TK_BIDI) {      
            PR r2 = parse_impl(ps_adv((r1).st));      (void)r2;
return mk_pr(n_bin(OP_IFF, (r1).node, (r2).node, ps_line(s), ps_col(s)), (r2).st);    
    } else {      
      return mk_pr((r1).node, ps_err((r1).st));    
    }  
  } else {    
    return parse_impl(s);  
  }}
PR gather_arms(PS s, int64_t acc) {
  if 
(ps_kind(s) == TK_RBRACE) {    
    return mk_pr(rev(acc), ps_adv(s));  
  } else {    
        PR pr = parse_pat_atom(s);    (void)pr;
    PS s2 = ps_adv((pr).st);    (void)s2;
    PR br = parse_expr(s2);    (void)br;
    PS s3 = ps_adv((br).st);    (void)s3;
return gather_arms(s3, m0_cons(mk_arm((pr).node, (br).node), acc));  
  }}
PR gather_field_inits(PS s, int64_t acc) {
  if 
(ps_kind(s) == TK_RBRACE) {    
    return mk_pr(rev(acc), ps_adv(s));  
  } else {    
        if 
(ps_kind(s) == TK_EOF) {      
      return mk_pr(rev(acc), ps_err(s));    
    } else {      
            char *nm = 
ps_str(s);      (void)nm;
      PS s2 = ps_adv(ps_adv(s));      (void)s2;
      PR r = parse_impl(s2);      (void)r;
      PS s3      ;
      if 
(ps_kind((r).st) == TK_COMMA) {        
                s3 = ps_adv((r).st);      
      } else {        
                s3 = (r).st;      
            }
      (void)s3;
return gather_field_inits(s3, m0_cons(mk_fi(nm, (r).node), acc));    
    }  
  }}
PR gather_list_elems(PS s, int64_t acc) {
  if 
(ps_kind(s) == TK_RBRACK) {    
    return mk_pr(rev(acc), ps_adv(s));  
  } else {    
        PR r = parse_impl(s);    (void)r;
    PS s2    ;
    if 
(ps_kind((r).st) == TK_COMMA) {      
            s2 = ps_adv((r).st);    
    } else {      
            s2 = (r).st;    
        }
    (void)s2;
return gather_list_elems(s2, m0_cons((r).node, acc));  
  }}
PR parse_atom(PS s) {
  int64_t k = 
ps_kind(s);  (void)k;
  int64_t line = 
ps_line(s);  (void)line;
  int64_t col = 
ps_col(s);  (void)col;
  if 
(k == TK_INT) {    
    return mk_pr(n_int(ps_int(s), line, col), ps_adv(s));  
  } else {    
        if 
(k == TK_STRING) {      
      return mk_pr(n_str(ps_str(s), line, col), ps_adv(s));    
    } else {      
            if 
(k == TK_TRUE) {        
        return mk_pr(n_bool(1, line, col), ps_adv(s));      
      } else {        
                if 
(k == TK_FALSE) {          
          return mk_pr(n_bool(0, line, col), ps_adv(s));        
        } else {          
                    if 
(k == TK_UNIT) {            
            return mk_pr(n_unit(line, col), ps_adv(s));          
          } else {            
                        if 
(k == TK_IDENT) {              
              return mk_pr(n_name(ps_str(s), line, col), ps_adv(s));            
            } else {              
                            if 
(k == TK_LET) {                
                                PS s_after_let = ps_adv(s);                (void)s_after_let;
                int64_t is_mut                ;
                if 
(m0_string_eq(ps_str(s_after_let), "mut") == 1) {                  
                                    is_mut = 1;                
                } else {                  
                                    is_mut = 0;                
                                }
                (void)is_mut;
                PS nm_ps                ;
                if 
(is_mut == 1) {                  
                                    nm_ps = ps_adv(s_after_let);                
                } else {                  
                                    nm_ps = s_after_let;                
                                }
                (void)nm_ps;
                char *nm = 
ps_str(nm_ps);                (void)nm;
                PS s_after_name = ps_adv(nm_ps);                (void)s_after_name;
                PS s_after_colon = ps_adv(s_after_name);                (void)s_after_colon;
                PR tr = parse_type_expr(s_after_colon);                (void)tr;
                PS s_after_type = ps_adv((tr).st);                (void)s_after_type;
                PR vr = parse_expr(s_after_type);                (void)vr;
                PS s_after_val = ps_adv((vr).st);                (void)s_after_val;
                PR br = parse_expr(s_after_val);                (void)br;
return mk_pr(n_let(nm, (tr).node, (vr).node, (br).node, line, col), (br).st);              
              } else {                
                                if 
(k == TK_MATCH) {                  
                                    PR sr = parse_expr(ps_adv(s));                  (void)sr;
                  PR ar = gather_arms(ps_adv((sr).st), m0_nil);                  (void)ar;
return mk_pr(n_match((sr).node, (ar).node, list_len((ar).node), line, col), (ar).st);                
                } else {                  
                                    if 
(k == TK_IF) {                    
                                        PR cr = parse_expr(ps_adv(s));                    (void)cr;
                    PS s2 = ps_adv((cr).st);                    (void)s2;
                    PR tr = parse_expr(s2);                    (void)tr;
                    PS s3 = ps_adv((tr).st);                    (void)s3;
                    PR er                    ;
                    if 
(ps_kind(s3) == TK_ELSE) {                      
                                            if 
(ps_kind(ps_adv(s3)) == TK_LBRACE) {                        
                                                PR r = parse_expr(ps_adv(s3));                        (void)r;
                        er = mk_pr((r).node, ps_adv((r).st));                      
                      } else {                        
                                                er = parse_expr(ps_adv(s3));                      
                                            }
                    
                    } else {                      
                                            er = mk_pr(n_unit(line, col), s3);                    
                                        }
                    (void)er;
return mk_pr(n_if((cr).node, (tr).node, (er).node, line, col), (er).st);                  
                  } else {                    
                                        if 
(k == TK_WHILE) {                      
                                            PR cr = parse_expr(ps_adv(s));                      (void)cr;
                      PS s2 = ps_adv((cr).st);                      (void)s2;
                      PR br = parse_expr(s2);                      (void)br;
return mk_pr(n_while((cr).node, (br).node, line, col), (br).st);                    
                    } else {                      
                                            if 
(k == TK_LBRACE) {                        
                        return gather_field_inits(ps_adv(s), m0_nil);                      
                      } else {                        
                                                if 
(k == TK_LBRACK) {                          
                          return gather_list_elems(ps_adv(s), m0_nil);                        
                        } else {                          
                                                    if 
(k == TK_LPAREN) {                            
                                                        PR r = parse_expr(ps_adv(s));                            (void)r;
return mk_pr((r).node, ps_adv((r).st));                          
                          } else {                            
                            return mk_pr(n_unit(line, col), ps_err(s));                          
                          }                        
                        }                      
                      }                    
                    }                  
                  }                
                }              
              }            
            }          
          }        
        }      
      }    
    }  
  }}
PR parse_decl(PS s) {
  int64_t k = 
ps_kind(s);  (void)k;
  int64_t line = 
ps_line(s);  (void)line;
  int64_t col = 
ps_col(s);  (void)col;
  if 
(k == TK_TYPE) {    
        char *nm = 
ps_str(ps_adv(s));    (void)nm;
    PS s2 = ps_adv(ps_adv(s));    (void)s2;
    PR tr = parse_type_expr(s2);    (void)tr;
return mk_pr(n_type_decl(nm, (tr).node, line, col), (tr).st);  
  } else {    
        if 
(k == TK_FN) {      
            char *nm = 
ps_str(ps_adv(s));      (void)nm;
      PR pr = gather_params(ps_adv(ps_adv(s)), m0_nil);      (void)pr;
      PS s2 = ps_adv((pr).st);      (void)s2;
      PR rr = parse_type_expr(s2);      (void)rr;
      PS s3 = ps_adv((rr).st);      (void)s3;
      PR br = parse_expr(s3);      (void)br;
      PS s4 = ps_adv((br).st);      (void)s4;
return mk_pr(n_fn_decl(nm, (pr).node, list_len((pr).node), (rr).node, (br).node, line, col), s4);    
    } else {      
            if 
(k == TK_EXTERNAL) {        
                char *cn = 
ps_str(ps_adv(s));        (void)cn;
        PS s2 = ps_adv(ps_adv(s));        (void)s2;
        PR tr = parse_type_expr(s2);        (void)tr;
return mk_pr(n_extern(cn, (tr).node, line, col), (tr).st);      
      } else {        
        return mk_pr(n_unit(line, col), ps_err(s));      
      }    
    }  
  }}
PR gather_decls(PS s, int64_t acc) {
  if 
(ps_kind(s) == TK_RBRACE) {    
    return mk_pr(rev(acc), ps_adv(s));  
  } else {    
        if 
(ps_kind(s) == TK_EOF) {      
      return mk_pr(rev(acc), ps_err(s));    
    } else {      
            PR r = parse_decl(s);      (void)r;
return gather_decls((r).st, m0_cons((r).node, acc));    
    }  
  }}
PR parse_module(PS s) {
  int64_t line = 
ps_line(s);  (void)line;
  int64_t col = 
ps_col(s);  (void)col;
  char *nm = 
ps_str(ps_adv(s));  (void)nm;
  PS s2 = ps_adv(ps_adv(s));  (void)s2;
  PR dr = gather_decls(s2, m0_nil);  (void)dr;
return mk_pr(n_mod(nm, (dr).node, list_len((dr).node), line, col), (dr).st);}
PR gather_modules(PS s, int64_t acc) {
  if 
(ps_kind(s) == TK_EOF) {    
    return mk_pr(rev(acc), s);  
  } else {    
        if 
(ps_kind(s) == TK_MODULE) {      
            PR r = parse_module(s);      (void)r;
return gather_modules((r).st, m0_cons((r).node, acc));    
    } else {      
      return mk_pr(rev(acc), ps_err(s));    
    }  
  }}
PR parse_program(PS s) {
  PR r = gather_modules(s, m0_nil);  (void)r;
return mk_pr(n_prog((r).node, list_len((r).node), ps_line(s), ps_col(s)), (r).st);}
int64_t reg_entry(char* name, int64_t t, int64_t fields) {
  int64_t e = 
m0_alloc(3);  (void)e;
  int64_t s0 = 
m0_store_string(e, 0, name);  (void)s0;
  int64_t s1 = 
m0_set(e, 1, t);  (void)s1;
  int64_t s2 = 
m0_set(e, 2, fields);  (void)s2;
return e;}
char* reg_name(int64_t e) {
return m0_load_string(e, 0);}
int64_t reg_type(int64_t e) {
return m0_get(e, 1);}
int64_t reg_fields(int64_t e) {
return m0_get(e, 2);}
int64_t lookup_reg(int64_t reg, char* name) {
  if 
(m0_is_nil(reg) == 1) {    
    return 0;  
  } else {    
        if 
(m0_string_eq(reg_name(m0_head(reg)), name) == 1) {      
      return m0_head(reg);    
    } else {      
      return lookup_reg(m0_tail(reg), name);    
    }  
  }}
int64_t build_reg(int64_t decls, int64_t reg) {
  if 
(m0_is_nil(decls) == 1) {    
    return reg;  
  } else {    
        int64_t d = 
m0_head(decls);    (void)d;
    if 
(m0_get(d, 0) == N_TYPE_DECL) {      
            char *nm = 
m0_load_string(d, 3);      (void)nm;
      int64_t t = 
m0_get(d, 4);      (void)t;
      int64_t fields      ;
      if 
(m0_get(t, 0) == T_RECORD) {        
                fields = m0_get(t, 3);      
      } else {        
                fields = m0_nil;      
            }
      (void)fields;
return build_reg(m0_tail(decls), m0_cons(reg_entry(nm, t, fields), reg));    
    } else {      
      return build_reg(m0_tail(decls), reg);    
    }  
  }}
int64_t emit_c_type(int64_t reg, int64_t t) {
  int64_t k = 
m0_get(t, 0);  (void)k;
  if 
(k == T_NAMED) {    
        char *nm = 
m0_load_string(t, 3);    (void)nm;
    if 
(m0_string_eq(nm, "Int") == 1) {      
      return m0_print("int64_t");    
    } else {      
            if 
(m0_string_eq(nm, "Float") == 1) {        
        return m0_print("double");      
      } else {        
                if 
(m0_string_eq(nm, "String") == 1) {          
          return m0_print("char*");        
        } else {          
                    if 
(m0_string_eq(nm, "Bool") == 1) {            
            return m0_print("int");          
          } else {            
                        if 
(m0_string_eq(nm, "Char") == 1) {              
              return m0_print("char");            
            } else {              
                            if 
(m0_string_eq(nm, "Unit") == 1) {                
                return m0_print("void");              
              } else {                
                return m0_print(nm);              
              }            
            }          
          }        
        }      
      }    
    }  
  } else {    
        if 
(k == T_FN) {      
      return emit_c_type(reg, m0_get(t, 5));    
    } else {      
      return m0_print("int64_t");    
    }  
  }}
int64_t emit_typedef_ef(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t p0 = 
emit_c_type(reg, m0_get(m0_head(l), 1));    (void)p0;
    int64_t p1 = 
m0_print(" ");    (void)p1;
    int64_t p2 = 
m0_print(m0_load_string(m0_head(l), 0));    (void)p2;
    int64_t p3 = 
m0_print("; ");    (void)p3;
return emit_typedef_ef(reg, m0_tail(l));  
  }}
int64_t emit_typedef_ec(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t arg = 
m0_get(m0_head(l), 1);    (void)arg;
    if 
(arg != 0) {      
            int64_t p0 = 
emit_c_type(reg, arg);      (void)p0;
      int64_t p1 = 
m0_print(" ");      (void)p1;
      int64_t p2 = 
m0_print(m0_load_string(m0_head(l), 0));      (void)p2;
      int64_t p3 = 
m0_print("_v; ");      (void)p3;
p3;    
    } else {      
      0;    
    }return emit_typedef_ec(reg, m0_tail(l));  
  }}
int64_t emit_typedef(int64_t reg, int64_t t, char* name) {
  int64_t k = 
m0_get(t, 0);  (void)k;
  if 
(k == T_RECORD) {    
        int64_t p0 = 
m0_print("typedef struct { ");    (void)p0;
    int64_t p1 = 
emit_typedef_ef(reg, m0_get(t, 3));    (void)p1;
    int64_t p2 = 
m0_print("} ");    (void)p2;
    int64_t p3 = 
m0_print(name);    (void)p3;
return m0_print(";\n");  
  } else {    
        if 
(k == T_SUM) {      
            int64_t p0 = 
m0_print("typedef struct { int tag; union { ");      (void)p0;
      int64_t p1 = 
emit_typedef_ec(reg, m0_get(t, 3));      (void)p1;
      int64_t p2 = 
m0_print("} data; } ");      (void)p2;
      int64_t p3 = 
m0_print(name);      (void)p3;
return m0_print(";\n");    
    } else {      
      return 0;    
    }  
  }}
int64_t emit_c_op(int64_t op) {
  if 
(op == OP_ADD) {    
    return m0_print("+");  
  } else {    
        if 
(op == OP_SUB) {      
      return m0_print("-");    
    } else {      
            if 
(op == OP_MUL) {        
        return m0_print("*");      
      } else {        
                if 
(op == OP_DIV) {          
          return m0_print("/");        
        } else {          
                    if 
(op == OP_MOD) {            
            return m0_print("%");          
          } else {            
                        if 
(op == OP_EQ) {              
              return m0_print("==");            
            } else {              
                            if 
(op == OP_NEQ) {                
                return m0_print("!=");              
              } else {                
                                if 
(op == OP_LT) {                  
                  return m0_print("<");                
                } else {                  
                                    if 
(op == OP_GT) {                    
                    return m0_print(">");                  
                  } else {                    
                                        if 
(op == OP_LE) {                      
                      return m0_print("<=");                    
                    } else {                      
                                            if 
(op == OP_GE) {                        
                        return m0_print(">=");                      
                      } else {                        
                                                if 
(op == OP_AND) {                          
                          return m0_print("&&");                        
                        } else {                          
                                                    if 
(op == OP_OR) {                            
                            return m0_print("||");                          
                          } else {                            
                            return m0_print("?");                          
                          }                        
                        }                      
                      }                    
                    }                  
                  }                
                }              
              }            
            }          
          }        
        }      
      }    
    }  
  }}
int64_t emit_c_expr_ea(int64_t reg, int64_t l, int64_t first) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t _p0    ;
    if 
(first == 0) {      
            _p0 = m0_print(", ");    
    } else {      
            _p0 = 0;    
        }
    (void)_p0;
    int64_t _p1 = 
emit_c_expr(reg, m0_head(l));    (void)_p1;
return emit_c_expr_ea(reg, m0_tail(l), 0);  
  }}
int64_t emit_c_expr_arms_ea(int64_t reg, int64_t l, int64_t first) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t pat = 
m0_get(m0_head(l), 0);    (void)pat;
    int64_t body = 
m0_get(m0_head(l), 1);    (void)body;
    int64_t pk = 
m0_get(pat, 0);    (void)pk;
    int64_t _psep    ;
    if 
(first == 0) {      
            _psep = m0_print(" else ");    
    } else {      
            _psep = 0;    
        }
    (void)_psep;
    int64_t _re    ;
    if 
(pk == P_WILD) {      
            int64_t _p0 = 
m0_print("(");      (void)_p0;
      int64_t _p1 = 
emit_c_expr(reg, body);      (void)_p1;
      _re = m0_print(")");    
    } else {      
            if 
(pk == P_LIT) {        
                int64_t _p0 = 
m0_print("(");        (void)_p0;
        int64_t _p1 = 
emit_c_expr(reg, m0_get(pat, 3));        (void)_p1;
        int64_t _p2 = 
m0_print(" == _m ? (");        (void)_p2;
        int64_t _p3 = 
emit_c_expr(reg, body);        (void)_p3;
        _re = m0_print(") : ");      
      } else {        
                if 
(pk == P_NAME) {          
                    int64_t _p0 = 
m0_print("{ int64_t ");          (void)_p0;
          int64_t _p1 = 
m0_print(m0_load_string(pat, 3));          (void)_p1;
          int64_t _p2 = 
m0_print(" = _m; (");          (void)_p2;
          int64_t _p3 = 
emit_c_expr(reg, body);          (void)_p3;
          _re = m0_print("); }");        
        } else {          
                    int64_t _p0 = 
m0_print("(");          (void)_p0;
          int64_t _p1 = 
emit_c_expr(reg, body);          (void)_p1;
          _re = m0_print(")");        
                }
      
            }
    
        }
    (void)_re;
return emit_c_expr_arms_ea(reg, m0_tail(l), 0);  
  }}
int64_t emit_c_expr_ef(int64_t reg, int64_t l, int64_t first) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t _psep    ;
    if 
(first == 0) {      
            _psep = m0_print(", ");    
    } else {      
            _psep = 0;    
        }
    (void)_psep;
    int64_t _p0 = 
m0_print(".");    (void)_p0;
    int64_t _p1 = 
m0_print(m0_load_string(m0_head(l), 0));    (void)_p1;
    int64_t _p2 = 
m0_print(" = ");    (void)_p2;
    int64_t _p3 = 
emit_c_expr(reg, m0_get(m0_head(l), 1));    (void)_p3;
return emit_c_expr_ef(reg, m0_tail(l), 0);  
  }}
int64_t emit_fn_ep(int64_t reg, int64_t l, int64_t first) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t _psep    ;
    if 
(first == 0) {      
            _psep = m0_print(", ");    
    } else {      
            _psep = 0;    
        }
    (void)_psep;
    int64_t _p0 = 
emit_c_type(reg, m0_get(m0_head(l), 1));    (void)_p0;
    int64_t _p1 = 
m0_print(" ");    (void)_p1;
    int64_t _p2 = 
m0_print(m0_load_string(m0_head(l), 0));    (void)_p2;
return emit_fn_ep(reg, m0_tail(l), 0);  
  }}
int64_t emit_c_expr(int64_t reg, int64_t e) {
  int64_t k = 
m0_get(e, 0);  (void)k;
  if 
(k == N_INT) {    
    return m0_print_int(m0_get(e, 3));  
  } else {    
        if 
(k == N_STRING) {      
            int64_t _p0 = 
m0_print("\"");      (void)_p0;
      int64_t _p1 = 
m0_print(m0_load_string(e, 3));      (void)_p1;
return m0_print("\"");    
    } else {      
            if 
(k == N_BOOL) {        
                if 
(m0_get(e, 3) == 1) {          
          return m0_print("1");        
        } else {          
          return m0_print("0");        
        }      
      } else {        
                if 
(k == N_UNIT) {          
          return m0_print("0");        
        } else {          
                    if 
(k == N_NAME) {            
            return m0_print(m0_load_string(e, 3));          
          } else {            
                        if 
(k == N_BINARY) {              
                            int64_t _p0 = 
m0_print("(");              (void)_p0;
              int64_t _p1 = 
emit_c_expr(reg, m0_get(e, 4));              (void)_p1;
              int64_t _p2 = 
m0_print(" ");              (void)_p2;
              int64_t _p3 = 
emit_c_op(m0_get(e, 3));              (void)_p3;
              int64_t _p4 = 
m0_print(" ");              (void)_p4;
              int64_t _p5 = 
emit_c_expr(reg, m0_get(e, 5));              (void)_p5;
return m0_print(")");            
            } else {              
                            if 
(k == N_NOT) {                
                                int64_t _p0 = 
m0_print("(!");                (void)_p0;
                int64_t _p1 = 
emit_c_expr(reg, m0_get(e, 3));                (void)_p1;
return m0_print(")");              
              } else {                
                                if 
(k == N_FIELD) {                  
                                    int64_t _p0 = 
emit_c_expr(reg, m0_get(e, 3));                  (void)_p0;
                  int64_t _p1 = 
m0_print(".");                  (void)_p1;
return m0_print(m0_load_string(e, 4));                
                } else {                  
                                    if 
(k == N_CALL) {                    
                                        int64_t _p0 = 
emit_c_expr(reg, m0_get(e, 3));                    (void)_p0;
                    int64_t _p1 = 
m0_print("(");                    (void)_p1;
                    int64_t _p2 = 
emit_c_expr_ea(reg, m0_get(e, 4), 1);                    (void)_p2;
return m0_print(")");                  
                  } else {                    
                                        if 
(k == N_LET) {                      
                                            int64_t _p0 = 
m0_print("({ ");                      (void)_p0;
                      int64_t _p1 = 
emit_c_type(reg, m0_get(e, 4));                      (void)_p1;
                      int64_t _p2 = 
m0_print(" ");                      (void)_p2;
                      int64_t _p3 = 
m0_print(m0_load_string(e, 3));                      (void)_p3;
                      int64_t _p4 = 
m0_print(" = ");                      (void)_p4;
                      int64_t _p5 = 
emit_c_expr(reg, m0_get(e, 5));                      (void)_p5;
                      int64_t _p6 = 
m0_print("; ");                      (void)_p6;
                      int64_t _p7 = 
emit_c_expr(reg, m0_get(e, 6));                      (void)_p7;
return m0_print("; })");                    
                    } else {                      
                                            if 
(k == N_IF) {                        
                                                int64_t _p0 = 
m0_print("(");                        (void)_p0;
                        int64_t _p1 = 
emit_c_expr(reg, m0_get(e, 3));                        (void)_p1;
                        int64_t _p2 = 
m0_print(" ? ");                        (void)_p2;
                        int64_t _p3 = 
emit_c_expr(reg, m0_get(e, 4));                        (void)_p3;
                        int64_t _p4 = 
m0_print(" : ");                        (void)_p4;
                        int64_t el = 
m0_get(e, 5);                        (void)el;
                        int64_t _p5                        ;
                        if 
(el != 0) {                          
                                                    _p5 = emit_c_expr(reg, el);                        
                        } else {                          
                                                    _p5 = m0_print("0");                        
                                                }
                        (void)_p5;
return m0_print(")");                      
                      } else {                        
                                                if 
(k == N_MATCH) {                          
                                                    int64_t _p0 = 
m0_print("({ int64_t _m = ");                          (void)_p0;
                          int64_t _p1 = 
emit_c_expr(reg, m0_get(e, 3));                          (void)_p1;
                          int64_t _p2 = 
m0_print("; ");                          (void)_p2;
                          int64_t _p3 = 
emit_c_expr_arms_ea(reg, m0_get(e, 4), 1);                          (void)_p3;
return m0_print("; })");                        
                        } else {                          
                                                    if 
(k == N_RECORD) {                            
                                                        int64_t r2 = 
lookup_reg(reg, m0_load_string(e, 3));                            (void)r2;
                            int64_t _p0 = 
m0_print("(");                            (void)_p0;
                            int64_t _p1 = 
emit_c_type(reg, reg_type(r2));                            (void)_p1;
                            int64_t _p2 = 
m0_print("){ ");                            (void)_p2;
                            int64_t _p3 = 
emit_c_expr_ef(reg, m0_get(e, 3), 1);                            (void)_p3;
return m0_print(" })");                          
                          } else {                            
                                                        if 
(k == N_WHILE) {                              
                                                            int64_t _p0 = 
m0_print("({ while (");                              (void)_p0;
                              int64_t _p1 = 
emit_c_expr(reg, m0_get(e, 3));                              (void)_p1;
                              int64_t _p2 = 
m0_print(") { ");                              (void)_p2;
                              int64_t _p3 = 
emit_c_expr(reg, m0_get(e, 4));                              (void)_p3;
return m0_print("; } 0; })");                            
                            } else {                              
                                                            if 
(k == N_ASSIGN) {                                
                                                                int64_t _p0 = 
m0_print("(");                                (void)_p0;
                                int64_t _p1 = 
m0_print(m0_load_string(e, 3));                                (void)_p1;
                                int64_t _p2 = 
m0_print(" = ");                                (void)_p2;
                                int64_t _p3 = 
emit_c_expr(reg, m0_get(e, 4));                                (void)_p3;
return m0_print(")");                              
                              } else {                                
                                return m0_print("0");                              
                              }                            
                            }                          
                          }                        
                        }                      
                      }                    
                    }                  
                  }                
                }              
              }            
            }          
          }        
        }      
      }    
    }  
  }}
int64_t emit_c_params(int64_t reg, int64_t params) {
  if 
(m0_is_nil(params) == 1) {    
    return 0;  
  } else {    
        int64_t _p0 = 
emit_c_type(reg, m0_head(params));    (void)_p0;
    int64_t rest = 
m0_tail(params);    (void)rest;
    int64_t _p1    ;
    if 
(m0_is_nil(rest) == 0) {      
            _p1 = m0_print(", ");    
    } else {      
            _p1 = 0;    
        }
    (void)_p1;
return emit_c_params(reg, rest);  
  }}
int64_t flatten_fn_ret(int64_t t) {
  if 
(m0_get(t, 0) == T_FN) {    
    return flatten_fn_ret(m0_get(t, 5));  
  } else {    
    return t;  
  }}
int64_t flatten_fn_params(int64_t t, int64_t acc) {
  if 
(m0_get(t, 0) == T_FN) {    
        int64_t p = 
m0_get(t, 3);    (void)p;
return flatten_fn_params(m0_get(t, 5), m0_cons(m0_head(p), acc));  
  } else {    
    return acc;  
  }}
int64_t emit_extern(int64_t reg, int64_t d) {
  char *cn = 
m0_load_string(d, 3);  (void)cn;
  int64_t t = 
m0_get(d, 4);  (void)t;
  if 
(m0_get(t, 0) == T_FN) {    
        int64_t ret = 
flatten_fn_ret(t);    (void)ret;
    int64_t params = 
rev(flatten_fn_params(t, m0_nil));    (void)params;
    int64_t _p0 = 
emit_c_type(reg, ret);    (void)_p0;
    int64_t _p1 = 
m0_print(" ");    (void)_p1;
    int64_t _p2 = 
m0_print(cn);    (void)_p2;
    int64_t _p3 = 
m0_print("(");    (void)_p3;
    int64_t _p4 = 
emit_c_params(reg, params);    (void)_p4;
return m0_print(");\n");  
  } else {    
        int64_t _p0 = 
emit_c_type(reg, t);    (void)_p0;
    int64_t _p1 = 
m0_print(" ");    (void)_p1;
    int64_t _p2 = 
m0_print(cn);    (void)_p2;
return m0_print(";\n");  
  }}
int64_t emit_fn(int64_t reg, int64_t d) {
  char *nm = 
m0_load_string(d, 3);  (void)nm;
  int64_t params = 
m0_get(d, 4);  (void)params;
  int64_t ret = 
m0_get(d, 6);  (void)ret;
  int64_t body = 
m0_get(d, 7);  (void)body;
  int64_t is_main = 
m0_string_eq(nm, "main");  (void)is_main;
  int64_t _p0  ;
  if 
(is_main == 1) {    
        _p0 = m0_print("int");  
  } else {    
        _p0 = emit_c_type(reg, ret);  
    }
  (void)_p0;
  int64_t _p1 = 
m0_print(" ");  (void)_p1;
  int64_t _p2 = 
m0_print(nm);  (void)_p2;
  int64_t _p3 = 
m0_print("(");  (void)_p3;
  int64_t _p4  ;
  if 
(is_main == 1) {    
        _p4 = m0_print("void");  
  } else {    
        _p4 = emit_fn_ep(reg, params, 1);  
    }
  (void)_p4;
  int64_t _p5 = 
m0_print(") {\n  return ");  (void)_p5;
  int64_t _p6 = 
emit_c_expr(reg, body);  (void)_p6;
return m0_print(";\n}\n");}
int64_t emit_module_pass1(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t d = 
m0_head(l);    (void)d;
    int64_t _e    ;
    if 
(m0_get(d, 0) == N_TYPE_DECL) {      
            _e = emit_typedef(reg, m0_get(d, 4), m0_load_string(d, 3));    
    } else {      
            _e = 0;    
        }
    (void)_e;
return emit_module_pass1(reg, m0_tail(l));  
  }}
int64_t emit_module_pass2(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t d = 
m0_head(l);    (void)d;
    int64_t _e    ;
    if 
(m0_get(d, 0) == N_EXTERN) {      
            _e = emit_extern(reg, d);    
    } else {      
            _e = 0;    
        }
    (void)_e;
return emit_module_pass2(reg, m0_tail(l));  
  }}
int64_t emit_module_pass3(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t d = 
m0_head(l);    (void)d;
    int64_t _e    ;
    if 
(m0_get(d, 0) == N_FN_DECL) {      
            _e = emit_fn(reg, d);    
    } else {      
            _e = 0;    
        }
    (void)_e;
return emit_module_pass3(reg, m0_tail(l));  
  }}
int64_t emit_module(int64_t m) {
  int64_t decls = 
m0_get(m, 4);  (void)decls;
  int64_t reg = 
build_reg(decls, m0_nil);  (void)reg;
  int64_t _h = 
m0_print("#include <stdio.h>\n#include <stdint.h>\n\n");  (void)_h;
  int64_t _p1 = 
emit_module_pass1(reg, decls);  (void)_p1;
  int64_t _n1 = 
m0_print("\n");  (void)_n1;
  int64_t _p2 = 
emit_module_pass2(reg, decls);  (void)_p2;
  int64_t _n2 = 
m0_print("\n");  (void)_n2;
  int64_t _p3 = 
emit_module_pass3(reg, decls);  (void)_p3;
return 0;}
int main() {
  char *filename = 
m0_get_env("M1_SOURCE");  (void)filename;
  if 
(m0_string_eq(filename, "") == 1) {    
        int64_t _e = 
m0_print("[M1000] error: no source file\n");    (void)_e;
return 1;  
  } else {    
        char *src = 
m0_read_file(filename);    (void)src;
    M1Lexer l = m1_lexer_init(src);    (void)l;
    M1LexResult r = m1_lexer_next(l);    (void)r;
    PS s = {(r).token, (r).lexer, 0};    (void)s;
    PR pr = parse_program(s);    (void)pr;
    int64_t mods = 
m0_get((pr).node, 3);    (void)mods;
    int64_t _em    ;
    if 
(m0_is_nil(mods) == 0) {      
            _em = emit_module(m0_head(mods));    
    } else {      
            _em = 0;    
        }
    (void)_em;
return ((pr).st).err;  
  }}
