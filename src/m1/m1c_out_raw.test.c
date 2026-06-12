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
#include <stdio.h>
/* #include "phase_graph.h" */

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
int64_t TK_FOR = 51;
int64_t TK_FREEZE = 52;
int64_t TK_NOW = 53;
int64_t TK_WAS = 54;
int64_t TK_WHEN = 55;
int64_t TK_THEN = 56;
int64_t TK_WILL = 57;
int64_t TK_RETURN = 58;
int64_t TK_BREAK = 59;
int64_t TK_CONTINUE = 60;
int64_t TK_MODULE_DECL = 61;
int64_t TK_IMPORT = 62;
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
int64_t N_FOR = 24;
int64_t N_FREEZE = 25;
int64_t N_NOW = 26;
int64_t N_WAS = 27;
int64_t N_WHEN = 28;
int64_t N_WILL = 29;
int64_t N_RETURN = 30;
int64_t N_BREAK = 31;
int64_t N_CONTINUE = 32;
int64_t N_SEQ = 33;
int64_t N_MODULE_DECL = 40;
int64_t N_IMPORT = 41;
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
  int64_t loop_depth;  
} PS;
typedef struct {
  int64_t node;  
  PS st;  
} PR;
extern char* m0_read_file(char*);
extern char* m0_string_concat(char*, char*);
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
extern int64_t m1_vector_new(void);
extern int64_t m1_vector_push(int64_t, int64_t);
extern int64_t m1_vector_get(int64_t, int64_t);
extern int64_t m1_vector_len(int64_t);
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

static char* frozen_names[256];
static int64_t frozen_lines[256];
static int64_t frozen_count;

static void freeze_var(char* name, int64_t line) {
    if (frozen_count < 256) {
        frozen_names[frozen_count] = name;
        frozen_lines[frozen_count] = line;
        frozen_count++;
    }
}

static int64_t is_frozen(char* name) {
    for (int64_t i = 0; i < frozen_count; i++) {
        if (m0_string_eq(frozen_names[i], name) == 1) return 1;
    }
    return 0;
}

static int64_t get_freeze_line(char* name) {
    for (int64_t i = frozen_count - 1; i >= 0; i--) {
        if (m0_string_eq(frozen_names[i], name) == 1) return frozen_lines[i];
    }
    return 0;
}

static void reset_frozen(void) {
    frozen_count = 0;
}

/* module resolution globals */
static char   g_src_dir[512] = ".";
static char   g_stdlib_dir[512] = ".";

/* Phase 2.4: module context for name mangling */
static char* g_current_module_name = "";
#define MAX_EXPORTS 512
static char* g_export_modname[MAX_EXPORTS];
static char* g_export_fnname[MAX_EXPORTS];
static char* g_export_emitname[MAX_EXPORTS];
static int64_t g_export_count = 0;
static int64_t g_sema_errors = 0;

/* resolve a module name to a file path; returns NULL if not found */
static char* resolve_module(char* name, int64_t* out_is_stdlib) {
    char fullpath[1024];
    *out_is_stdlib = 0;
    /* check for std. or bare std (stdlib root) */
    {
      int64_t is_std = (name[0] == 's' && name[1] == 't' && name[2] == 'd');
      if (is_std && name[3] == '.') {
        *out_is_stdlib = 1;
        snprintf(fullpath, sizeof(fullpath), "%s/%s.m1", g_stdlib_dir, name + 4);
      } else if (is_std) {
        /* bare 'std' maps to std/std.m1 */
        *out_is_stdlib = 1;
        snprintf(fullpath, sizeof(fullpath), "%s/std.m1", g_stdlib_dir);
      } else {
        snprintf(fullpath, sizeof(fullpath), "%s/%s.m1", g_src_dir, name);
    }
    }
    char* content = m0_read_file(fullpath);
    if (content) {
        char* result = (char*)malloc(strlen(fullpath) + 1);
        strcpy(result, fullpath);
        return result;
    }
    return NULL;
}

/* error reporting globals */
static char   g_filename[512] = "<unknown>";
static int64_t g_preamble_line_offset = 0;

static void report_error(int64_t line, int64_t col, const char* msg) {
    int64_t user_line = line - g_preamble_line_offset;
    if (user_line < 1) user_line = 1;
    fprintf(stderr, "%s:%lld:%lld: error: %s\n",
        g_filename,
        (long long)user_line,
        (long long)col,
        msg);
}

/* forward declarations needed by now-set helpers */
int64_t emit_c_expr(int64_t reg, int64_t e);

/* now-set: tracks active now assertions */
#define MAX_NOW 256

static char*   now_watched[MAX_NOW];
static char*   now_cond_text[MAX_NOW];
static int64_t now_cond_node[MAX_NOW];
static int64_t now_line[MAX_NOW];
static int64_t now_col[MAX_NOW];
static int64_t now_count = 0;

static void now_add(char* var, int64_t node,
                    int64_t line, int64_t col) {
    if (now_count >= MAX_NOW) return;
    now_watched[now_count]   = var;
    now_cond_text[now_count] = "(invariant)";
    now_cond_node[now_count] = node;
    now_line[now_count]      = line;
    now_col[now_count]       = col;
    now_count++;
}

static void reset_now(void) { now_count = 0; }

/* emit all now-checks that watch variable 'var' */
static void emit_now_checks_for(int64_t reg, char* var) {
    for (int64_t i = 0; i < now_count; i++) {
        if (m0_string_eq(now_watched[i], var) == 1) {
            int64_t user_line = now_line[i] - g_preamble_line_offset;
            if (user_line < 1) user_line = 1;
            m0_print("if (!(");
            emit_c_expr(reg, now_cond_node[i]);
            m0_print(")) { fprintf(stderr, \"");
            m0_print(g_filename);
            m0_print(":");
            /* print line */
            { char lbuf[32]; snprintf(lbuf, sizeof(lbuf), "%lld", (long long)user_line); m0_print(lbuf); }
            m0_print(":");
            { char lbuf[32]; snprintf(lbuf, sizeof(lbuf), "%lld", (long long)(now_col[i])); m0_print(lbuf); }
            m0_print(": error: [M1101] 'now' assertion violated: ");
            m0_print(now_cond_text[i]);
            m0_print("\\n\"); exit(1); } ");
        }
    }
}

/* --- when/trigger set --- */

#define MAX_WHEN 256

static char*   when_watched[MAX_WHEN];
static int64_t when_cond_node[MAX_WHEN];
static int64_t when_body_node[MAX_WHEN];
static int64_t when_line[MAX_WHEN];
static int64_t when_col[MAX_WHEN];
static int64_t when_count = 0;

static void when_add(char* var, int64_t cond, int64_t body,
                     int64_t line, int64_t col) {
    if (when_count >= MAX_WHEN) return;
    when_watched[when_count]   = var;
    when_cond_node[when_count] = cond;
    when_body_node[when_count] = body;
    when_line[when_count]      = line;
    when_col[when_count]       = col;
    when_count++;
}

static void reset_when(void) { when_count = 0; }

static void emit_when_checks_for(int64_t reg, char* var) {
    for (int64_t i = 0; i < when_count; i++) {
        if (m0_string_eq(when_watched[i], var) == 1) {
            m0_print("if (");
            emit_c_expr(reg, when_cond_node[i]);
            m0_print(") { ");
            emit_c_expr(reg, when_body_node[i]);
            m0_print("; } ");
        }
    }
}

/* --- end when/trigger set --- */

/* --- will/commitment set --- */

#define MAX_WILL 10

static char*   will_watched[MAX_WILL];
static int64_t will_cond_node[MAX_WILL];
static int64_t will_line[MAX_WILL];
static int64_t will_col[MAX_WILL];
static int64_t will_count = 0;

static void will_add(char* var, int64_t cond,
                     int64_t line, int64_t col) {
    if (will_count >= MAX_WILL) return;
    will_watched[will_count]   = var;
    will_cond_node[will_count] = cond;
    will_line[will_count]      = line;
    will_col[will_count]       = col;
    will_count++;
}

static void reset_will(void) { will_count = 0; }

static int64_t is_phase_will(int64_t node);
static char* extract_phase_name(int64_t node);
static int64_t phase_was(char* var, char* name);

static void emit_will_checks_for(int64_t reg, char* var) {
    for (int64_t i = 0; i < will_count; i++) {
        if (m0_string_eq(will_watched[i], var) == 1) {
            char ibuf[16];
            snprintf(ibuf, sizeof(ibuf), "%lld", (long long)i);
            if (is_phase_will(will_cond_node[i])) {
                char* phase = extract_phase_name(will_cond_node[i]);
                if (phase_was(var, phase) == 1) {
                    m0_print("_will_");
                    m0_print(ibuf);
                    m0_print(" = 1; ");
                }
            } else {
                m0_print("if (");
                emit_c_expr(reg, will_cond_node[i]);
                m0_print(") { _will_");
                m0_print(ibuf);
                m0_print(" = 1; } ");
            }
        }
    }
}

static void emit_will_return_checks(void) {
    for (int64_t i = 0; i < will_count; i++) {
        int64_t user_line = will_line[i] - g_preamble_line_offset;
        if (user_line < 1) user_line = 1;
        char ibuf[16];
        snprintf(ibuf, sizeof(ibuf), "%lld", (long long)i);
        char lbuf[32];
        m0_print("if (!_will_");
        m0_print(ibuf);
        m0_print(") { fprintf(stderr, \"");
        m0_print(g_filename);
        m0_print(":");
        snprintf(lbuf, sizeof(lbuf), "%lld", (long long)user_line);
        m0_print(lbuf);
        m0_print(":");
        snprintf(lbuf, sizeof(lbuf), "%lld", (long long)will_col[i]);
        m0_print(lbuf);
        m0_print(": error: [M1102] 'will' commitment violated\\n\"); exit(1); } ");
    }
}

/* --- end will/commitment set --- */

/* --- phase history --- */

#define MAX_PHASE_HISTORY 256

static char*   phase_var[MAX_PHASE_HISTORY];
static char*   phase_name[MAX_PHASE_HISTORY];
static int64_t phase_count = 0;

static void phase_record(char* var, char* name) {
    if (phase_count >= MAX_PHASE_HISTORY) return;
    phase_var[phase_count] = var;
    phase_name[phase_count] = name;
    phase_count++;
}

static int64_t phase_was(char* var, char* name) {
    for (int64_t i = 0; i < phase_count; i++) {
        if (m0_string_eq(phase_var[i], var) == 1 &&
            m0_string_eq(phase_name[i], name) == 1) return 1;
    }
    return 0;
}

static void reset_phase(void) { phase_count = 0; }

/* --- end phase history --- */

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
int64_t emit_c_expr_ea(int64_t reg, int64_t l, int64_t first);
int64_t emit_c_expr_arms_ea(int64_t reg, int64_t l);
int64_t emit_c_expr_ef(int64_t reg, int64_t l, int64_t first);
int64_t emit_fn_ep(int64_t reg, int64_t l, int64_t first);
int64_t emit_c_op(int64_t op);
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
return (PS){(r).token, (r).lexer, (s).err, (s).loop_depth};}
PS ps_err(PS s) {
return (PS){(s).tk, (s).lx, ((s).err + 1), (s).loop_depth};}
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
int64_t n_for(char* var_name, int64_t start, int64_t end, int64_t body, int64_t line, int64_t col) {
  int64_t n = 
nk(N_FOR, line, col, 7);  (void)n;
  int64_t s0 = 
m0_store_string(n, 3, var_name);  (void)s0;
  int64_t s1 = 
m0_set(n, 4, start);  (void)s1;
  int64_t s2 = 
m0_set(n, 5, end);  (void)s2;
  int64_t s3 = 
m0_set(n, 6, body);  (void)s3;
return n;}
int64_t n_freeze(char* var_name, int64_t line, int64_t col) {
  int64_t n = nk(N_FREEZE, line, col, 4);
  int64_t s0 = m0_store_string(n, 3, var_name);  (void)s0;
  return n;}
int64_t n_now(int64_t cond_node, int64_t line, int64_t col) {
  int64_t n = nk(N_NOW, line, col, 5);
  int64_t s0 = m0_set(n, 3, cond_node);  (void)s0;
  return n;}
int64_t n_was(char* var_name, char* phase_name_str, int64_t line, int64_t col) {
  int64_t n = nk(N_WAS, line, col, 5);
  int64_t s0 = m0_store_string(n, 3, var_name);  (void)s0;
  int64_t s1 = m0_store_string(n, 4, phase_name_str);  (void)s1;
  return n;}
int64_t n_when(int64_t cond, int64_t body, int64_t line, int64_t col) {
  int64_t n = nk(N_WHEN, line, col, 5);
  int64_t s0 = m0_set(n, 3, cond);  (void)s0;
  int64_t s1 = m0_set(n, 4, body);  (void)s1;
  return n;}
int64_t n_will(int64_t cond, int64_t line, int64_t col) {
  int64_t n = nk(N_WILL, line, col, 4);
  int64_t s0 = m0_set(n, 3, cond);  (void)s0;
  return n;}
int64_t n_return(int64_t val, int64_t line, int64_t col) {
  int64_t n = nk(N_RETURN, line, col, 4);
  int64_t s0 = m0_set(n, 3, val);  (void)s0;
  return n;}
int64_t n_break(int64_t line, int64_t col) {
  int64_t n = nk(N_BREAK, line, col, 3);
  return n;}
int64_t n_continue(int64_t line, int64_t col) {
  int64_t n = nk(N_CONTINUE, line, col, 3);
  return n;}
int64_t n_module_decl(char* name, int64_t line, int64_t col) {
  int64_t n = nk(N_MODULE_DECL, line, col, 4);
  int64_t s0 = m0_store_string(n, 3, name);  (void)s0;
  return n;}
int64_t n_import(char* name, int64_t line, int64_t col) {
  int64_t n = nk(N_IMPORT, line, col, 5);
  int64_t s0 = m0_store_string(n, 3, name);  (void)s0;
  int64_t s1 = m0_store_string(n, 4, "");  (void)s1;
  return n;}
int64_t n_seq(int64_t l, int64_t r, int64_t line, int64_t col) {
  int64_t n = nk(N_SEQ, line, col, 5);
  int64_t s0 = m0_set(n, 3, l);  (void)s0;
  int64_t s1 = m0_set(n, 4, r);  (void)s1;
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
(k == TK_INT) {      
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
                        PR r = parse_type_expr(ps_adv(s));            (void)r;
return mk_pr((r).node, ps_adv((r).st));          
          } else {            
            return mk_pr(n_unit(line, col), ps_err(s));          
          }        
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
          if
(m0_get(n, 0) == N_NAME) {
            PR vr = parse_expr(ps_adv(s));          (void)vr;
            return mk_pr(n_assign(m0_load_string(n, 3), (vr).node, ps_line(s), ps_col(s)), (vr).st);
          } else {
            return mk_pr(n, s);
          }
        } else {
          return mk_pr(n, s);
        }    
    }  
  }
}
}
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
PR parse_stmts(PS s) {
  if 
(ps_kind(s) == TK_RBRACE || ps_kind(s) == TK_EOF) {    
    int64_t line = 
ps_line(s);    (void)line;
    int64_t col = 
ps_col(s);    (void)col;
    return mk_pr(n_unit(line, col), s);  
  }
  PR r = parse_expr(s);  (void)r;
  if 
(ps_kind((r).st) == TK_SEMI) {    
    PS s2 = ps_adv((r).st);    (void)s2;
    PR rest = parse_stmts(s2);    (void)rest;
    int64_t line = 
ps_line(s);    (void)line;
    int64_t col = 
ps_col(s);    (void)col;
    return mk_pr(n_seq((r).node, (rest).node, line, col), (rest).st);  
  } else {    
    return r;  
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
                                PS s1 = ps_adv(s);                (void)s1;
                                int64_t is_mut = 0;
                                if 
(ps_kind(s1) == TK_MUT) {
                                    is_mut = 1;
                                    s1 = ps_adv(s1);
                                }
                                (void)is_mut;
                                char *nm = 
ps_str(s1);                (void)nm;
                PS s2 = ps_adv(ps_adv(s1));                (void)s2;
                PR tr = parse_type_expr(s2);                (void)tr;
                PS s3 = ps_adv((tr).st);                (void)s3;
                PR vr = parse_expr(s3);                (void)vr;
                PS s4 = ps_adv((vr).st);                (void)s4;
                PR br = parse_expr(s4);                (void)br;
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
                    PS s_then_open = (cr).st;                    (void)s_then_open;
                    PR tr = parse_expr(ps_adv(s_then_open));                    (void)tr;
                    PS s4 = (tr).st;                    (void)s4;
                    if 
(ps_kind(s4) == TK_SEMI) {                      
                        s4 = ps_adv(s4);                    
                    }
                    PS s_then_close = s4;                    
                    if 
(ps_kind(s_then_close) == TK_RBRACE) {                      
                        s4 = ps_adv(s_then_close);                    
                    }
                    PR er                    ;
                    if 
(ps_kind(s4) == TK_ELSE) {                      
                        PS s5 = ps_adv(s4);                      
                        if 
(ps_kind(s5) == TK_LBRACE) {                        
                            PR r = parse_expr(ps_adv(s5));                        (void)r;
                            PS s6 = (r).st;                            
                            if 
(ps_kind(s6) == TK_SEMI) {                              
                                s6 = ps_adv(s6);                            
                            }                            
                            er = mk_pr((r).node, ps_adv(s6));                        
                        } else {                        
                            er = parse_expr(s5);                        
                        }                    
                    } else {                    
                        er = mk_pr(n_unit(line, col), s4);                    
                    }
                    (void)er;
return mk_pr(n_if((cr).node, (tr).node, (er).node, line, col), (er).st);                  
                  } else {                    
                                        if 
(k == TK_LBRACE) {                      
                      PR inits = gather_field_inits(ps_adv(s), m0_nil);                    
                      return mk_pr(n_record((inits).node, list_len((inits).node), line, col), (inits).st);                    
                    } else {                      
                                            if 
(k == TK_LBRACK) {                        
                        return gather_list_elems(ps_adv(s), m0_nil);                      
                      } else {                        
                                                if 
(k == TK_LPAREN) {                          
                                                    PR r = parse_expr(ps_adv(s));                          (void)r;
return mk_pr((r).node, ps_adv((r).st));                        
                        } else {
                           if
(k == TK_WHILE) {
                                 PS s_cond = ps_adv(s);
                                 s_cond.loop_depth++;
                                 PR cr = parse_expr(s_cond);                            (void)cr;
                                 PS s2 = ps_adv((cr).st);                            (void)s2;
                                 PR br = parse_stmts(s2);                            (void)br;
                                 (br).st.loop_depth--;
                                PS s3 = (br).st;                            (void)s3;
                                if 
(ps_kind(s3) == TK_SEMI) {                                  
                                    s3 = ps_adv(s3);                                
                                }                                
                                if 
(ps_kind(s3) == TK_RBRACE) {                                  
                                    s3 = ps_adv(s3);                                
                                }                                
                                return mk_pr(n_while((cr).node, (br).node, line, col), s3);
                            } else {
                              if
(k == TK_FOR) {
                                   char* var_nm = ps_str(ps_adv(s));                            (void)var_nm;
                                   PS s_in = ps_adv(ps_adv(s));                                  (void)s_in;
                                   s_in.loop_depth++;
                                   PR start_r = parse_expr(s_in);                                 (void)start_r;
                                   PS s_to = ps_adv((start_r).st);                               (void)s_to;
                                   PR end_r = parse_expr(s_to);                                   (void)end_r;
                                   PS s_body = ps_adv((end_r).st);                               (void)s_body;
                                   PR body_r = parse_stmts(s_body);                                (void)body_r;
                                   (body_r).st.loop_depth--;
                                  PS s6 = (body_r).st;                                   (void)s6;
                                  if 
(ps_kind(s6) == TK_SEMI) {                                    
                                      s6 = ps_adv(s6);                                  
                                  }                                  
                                  if 
(ps_kind(s6) == TK_RBRACE) {                                    
                                      s6 = ps_adv(s6);                                  
                                  }                                  
                                  return mk_pr(n_for(var_nm, (start_r).node, (end_r).node, (body_r).node, line, col), s6);
                              } else {
                                 if
(k == TK_FREEZE) {
                                     char* var_name = ps_str(ps_adv(s));
                                     PS s2 = ps_adv(ps_adv(s));
                                     return mk_pr(n_freeze(var_name, line, col), s2);
                                 } else {
                                 if
(k == TK_NOW) {
                                     PS s_cond = ps_adv(s);
                                     PR cr = parse_expr(s_cond);
                                      return mk_pr(n_now((cr).node, line, col), (cr).st);
                                  } else {
                                   if
 (k == TK_WAS) {
                                        PS var_state = ps_adv(s);
                                        char* var_name = ps_str(var_state);
                                        PS dot_state = ps_adv(var_state);
                                        PS phase_state = ps_adv(dot_state);
                                        char* phase_name_str;
                                        if (ps_kind(phase_state) == TK_MUT) {
                                            phase_name_str = "live";
                                        } else {
                                            phase_name_str = ps_str(phase_state);
                                        }
                                        PS s2 = ps_adv(phase_state);
                                        return mk_pr(n_was(var_name, phase_name_str, line, col), s2);
                                   } else {
                                   if
(k == TK_WHEN) {
                                       PS s_cond = ps_adv(s);
                                       PR cr = parse_expr(s_cond);
                                       PS s_then = ps_adv((cr).st);
                                       PS s_body = ps_adv(s_then);
                                       PR br = parse_expr(s_body);
                                       PS s_end = ps_adv((br).st);
                                        return mk_pr(n_when((cr).node, (br).node, line, col), s_end);
                                    } else {
                                    if
 (k == TK_WILL) {
                                        PS s2 = ps_adv(s);
                                        PR cr = parse_expr(s2);
                                        return mk_pr(n_will((cr).node, line, col), (cr).st);
                                    } else {
                                     if
  (k == TK_RETURN) {
                                         PR vr = parse_expr(ps_adv(s));
                                         return mk_pr(n_return((vr).node, line, col), (vr).st);
                                     } else {
                                       if
  (k == TK_BREAK) {
                                         if ((s).loop_depth == 0) {
                                              report_error(line, col, "[M1001] break outside loop");
                                             return mk_pr(n_break(line, col), ps_err(ps_adv(s)));
                                         }
                                         return mk_pr(n_break(line, col), ps_adv(s));
                                       } else {
                                         if
  (k == TK_CONTINUE) {
                                             if ((s).loop_depth == 0) {
                                                  report_error(line, col, "[M1002] continue outside loop");
                                                 return mk_pr(n_continue(line, col), ps_err(ps_adv(s)));
                                             }
                                             return mk_pr(n_continue(line, col), ps_adv(s));
                                          } else {
                                            if
   (k == TK_MODULE_DECL) {
                                              char* mod_name = ps_str(ps_adv(s));
                                              PS s2 = ps_adv(ps_adv(s));
                                              return mk_pr(n_module_decl(mod_name, line, col), s2);
                                            } else {
                                              if
   (k == TK_IMPORT) {
                                                 PS s_after_import = ps_adv(s);
                                                 char* imp_name = ps_str(s_after_import);
                                                 PS s2 = ps_adv(s_after_import);
                                                 while (ps_kind(s2) == TK_DOT) {
                                                   PS s_after_dot = ps_adv(s2);
                                                   char* seg = ps_str(s_after_dot);
                                                   imp_name = m0_string_concat(imp_name, ".");
                                                   imp_name = m0_string_concat(imp_name, seg);
                                                   s2 = ps_adv(s_after_dot);
                                                 }
                                                 return mk_pr(n_import(imp_name, line, col), s2);
                                              } else {
                                                if
   (k == TK_RBRACE) {
                                                  return mk_pr(n_unit(line, col), s);
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
  }}}
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
    PS s2 = ps_adv(ps_adv(ps_adv(s)));    (void)s2;
    PR tr = parse_type_expr(s2);    (void)tr;
return mk_pr(n_type_decl(nm, (tr).node, line, col), (tr).st);  
  } else {    
        if 
(k == TK_FN) {      
            char *nm = 
ps_str(ps_adv(s));      (void)nm;
      PS s2 = ps_adv(ps_adv(s));      (void)s2;
      PS ps      ;
      if 
(ps_kind(s2) == TK_LPAREN) {        
                ps = ps_adv(s2);      
      } else {        
                ps = s2;      
            }
      (void)ps;
      PR pr = gather_params(ps, m0_nil);      (void)pr;
      PS s3 = ps_adv((pr).st);      (void)s3;
      PR rr = parse_type_expr(s3);      (void)rr;
      PS s4 = ps_adv((rr).st);      (void)s4;
      PR br = parse_stmts(s4);      (void)br;
      PS s5 = ps_adv((br).st);      (void)s5;
return mk_pr(n_fn_decl(nm, (pr).node, list_len((pr).node), (rr).node, (br).node, line, col), s5);    
    } else {      
            if 
(k == TK_EXTERNAL) {        
                char *cn = 
ps_str(ps_adv(s));        (void)cn;
        PS s2 = ps_adv(ps_adv(ps_adv(s)));        (void)s2;
        PR tr = parse_type_expr(s2);        (void)tr;
return mk_pr(n_extern(cn, (tr).node, line, col), (tr).st);      
      } else {        
        return mk_pr(n_unit(line, col), ps_adv(ps_err(s)));      
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
  PS s2 = ps_adv(ps_adv(ps_adv(s)));  (void)s2;
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
      if
(ps_kind(s) == TK_MODULE_DECL) {
            PS s_after_mod = ps_adv(s);
            char* mod_name = ps_str(s_after_mod);
            PS s2 = ps_adv(s_after_mod);
            while (ps_kind(s2) == TK_DOT) {
              PS s_after_dot = ps_adv(s2);
              char* seg = ps_str(s_after_dot);
              mod_name = m0_string_concat(mod_name, ".");
              mod_name = m0_string_concat(mod_name, seg);
              s2 = ps_adv(s_after_dot);
            }
            s2 = ps_adv(s2);
            PR r = { .node = n_module_decl(mod_name, ps_line(s), ps_col(s)), .st = s2 };
return gather_modules((r).st, m0_cons((r).node, acc));
      } else {
        if
(ps_kind(s) == TK_IMPORT) {
              PS s_after_import = ps_adv(s);
              char* imp_name = ps_str(s_after_import);
              PS s2 = ps_adv(s_after_import);
              while (ps_kind(s2) == TK_DOT) {
                PS s_after_dot = ps_adv(s2);
                char* seg = ps_str(s_after_dot);
                imp_name = m0_string_concat(imp_name, ".");
                imp_name = m0_string_concat(imp_name, seg);
                s2 = ps_adv(s_after_dot);
              }
              s2 = ps_adv(s2);
              PR r = { .node = n_import(imp_name, ps_line(s), ps_col(s)), .st = s2 };
return gather_modules((r).st, m0_cons((r).node, acc));
        } else {
            return mk_pr(rev(acc), ps_err(s));
        }
      }
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
                 if (m0_string_eq(nm, "Vector") == 1) {                  
                   return m0_print("int64_t");                
                 } else {                  
                   return m0_print(nm);                
                 }              
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
int64_t emit_c_expr_ea(int64_t reg, int64_t l, int64_t first) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        if 
(first == 0) {      
            int64_t p = 
m0_print(", ");      (void)p;
p;    
    } else {      
      0;    
    }    int64_t p = 
emit_c_expr(reg, m0_head(l));    (void)p;
return emit_c_expr_ea(reg, m0_tail(l), 0);  
  }}
int64_t emit_c_expr_arms_ea(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    m0_print("0");
    return 0;  
  } else {    
        int64_t pat = 
m0_get(m0_head(l), 0);    (void)pat;
    int64_t body = 
m0_get(m0_head(l), 1);    (void)body;
    int64_t pk = 
m0_get(pat, 0);    (void)pk;
    if 
(pk == P_WILD) {      
            int64_t p0 = 
m0_print("(");      (void)p0;
      int64_t p1 = 
emit_c_expr(reg, body);      (void)p1;
return m0_print(")");    
    } else {      
            if 
(pk == P_LIT) {        
                int64_t p0 = 
emit_c_expr(reg, m0_get(pat, 3));        (void)p0;
        int64_t p1 = 
m0_print(" == _m ? (");        (void)p1;
        int64_t p2 = 
emit_c_expr(reg, body);        (void)p2;
        int64_t p3 = 
m0_print(") : ");        (void)p3;
      } else {        
                if 
(pk == P_NAME) {          
                    int64_t p0 = 
m0_print("{ int64_t ");          (void)p0;
          int64_t p1 = 
m0_print(m0_load_string(pat, 3));          (void)p1;
          int64_t p2 = 
m0_print(" = _m; (");          (void)p2;
          int64_t p3 = 
emit_c_expr(reg, body);          (void)p3;
return m0_print("); }");        
        } else {          
                    int64_t p0 = 
m0_print("(");          (void)p0;
          int64_t p1 = 
emit_c_expr(reg, body);          (void)p1;
return m0_print(")");        
        }      
      }    
    }return emit_c_expr_arms_ea(reg, m0_tail(l));  
  }}
int64_t emit_c_expr_ef(int64_t reg, int64_t l, int64_t first) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        if 
(first == 0) {      
            int64_t p = 
m0_print(", ");      (void)p;
p;    
    } else {      
      0;    
    }    int64_t p0 = 
m0_print(".");    (void)p0;
    int64_t p1 = 
m0_print(m0_load_string(m0_head(l), 0));    (void)p1;
    int64_t p2 = 
m0_print(" = ");    (void)p2;
    int64_t p3 = 
emit_c_expr(reg, m0_get(m0_head(l), 1));    (void)p3;
return emit_c_expr_ef(reg, m0_tail(l), 0);  
  }}
int64_t emit_fn_ep(int64_t reg, int64_t l, int64_t first) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        if 
(first == 0) {      
            int64_t p = 
m0_print(", ");      (void)p;
p;    
    } else {      
      0;    
    }    int64_t p0 = 
emit_c_type(reg, m0_get(m0_head(l), 1));    (void)p0;
    int64_t p1 = 
m0_print(" ");    (void)p1;
    int64_t p2 = 
m0_print(m0_load_string(m0_head(l), 0));    (void)p2;
return emit_fn_ep(reg, m0_tail(l), 0);  
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
/* Walk a condition node to find the left-most variable name.
   For 'balance >= 0', the condition is N_BINARY with left = N_NAME("balance"). */
static char* extract_watched_var(int64_t node) {
    if (node == 0) return "";
    int64_t k = m0_get(node, 0);
    if (k == N_NAME) {
        return m0_load_string(node, 3);
    }
    if (k == N_BINARY) {
        return extract_watched_var(m0_get(node, 4));
    }
    if (k == N_NOT) {
        return extract_watched_var(m0_get(node, 3));
    }
    if (k == N_FIELD) {
        return extract_watched_var(m0_get(node, 3));
    }
    return "";
}

static char* extract_phase_name(int64_t node) {
    if (node == 0) return "";
    if (m0_get(node, 0) == N_FIELD) {
        return m0_load_string(node, 4);
    }
    return "";
}

static int64_t is_phase_will(int64_t node) {
    if (node == 0) return 0;
    return (m0_get(node, 0) == N_FIELD) ? 1 : 0;
}
static void emit_c_expr_check_names(int64_t e) {
    if (e == 0) return;
    if (g_sema_errors) return;
    int64_t k = m0_get(e, 0);
    if (k == N_NAME) {
        char* nm = m0_load_string(e, 3);
        if (g_current_module_name[0] != '\0') {
            for (int64_t xi = 0; xi < g_export_count; xi++) {
                if (m0_string_eq(g_export_fnname[xi], nm)) {
                    return;
                }
            }
            for (int64_t xi = 0; xi < g_export_count; xi++) {
                if (g_export_modname[xi] == (char*)1) continue;
                if (!m0_string_eq(g_export_modname[xi], g_current_module_name) &&
                    m0_string_eq(g_export_fnname[xi], nm)) {
                    int64_t nmln = m0_get(e, 1);
                    int64_t nmcl = m0_get(e, 2);
                    fprintf(stderr, "%s:%lld:%lld: warning: [M1008] unqualified name '%s' (did you mean '%s.%s'?)\n",
                        g_filename, (long long)nmln, (long long)nmcl, nm,
                        g_export_modname[xi], nm);
                    break;
                }
            }
        }
        return;
    }
    if (k == N_FIELD) { emit_c_expr_check_names(m0_get(e, 3)); return; }
    if (k == N_NOT || k == N_NOW || k == N_WAS || k == N_WHEN || k == N_WILL) { emit_c_expr_check_names(m0_get(e, 3)); return; }
    if (k == N_BINARY) { emit_c_expr_check_names(m0_get(e, 4)); emit_c_expr_check_names(m0_get(e, 5)); return; }
    if (k == N_CALL) { emit_c_expr_check_names(m0_get(e, 3)); int64_t a = m0_get(e, 4); while (m0_is_nil(a) == 0) { emit_c_expr_check_names(m0_head(a)); a = m0_tail(a); } return; }
    if (k == N_LET) { emit_c_expr_check_names(m0_get(e, 5)); emit_c_expr_check_names(m0_get(e, 6)); return; }
    if (k == N_IF) { emit_c_expr_check_names(m0_get(e, 3)); emit_c_expr_check_names(m0_get(e, 4)); emit_c_expr_check_names(m0_get(e, 5)); return; }
    if (k == N_ASSIGN) { emit_c_expr_check_names(m0_get(e, 5)); return; }
    if (k == N_RETURN) { if (m0_get(e, 3)) emit_c_expr_check_names(m0_get(e, 3)); return; }
    if (k == N_WHILE || k == N_FOR) { emit_c_expr_check_names(m0_get(e, 4)); emit_c_expr_check_names(m0_get(e, 5)); return; }
    if (k == N_MATCH) { emit_c_expr_check_names(m0_get(e, 4)); return; }
}
int64_t emit_c_expr(int64_t reg, int64_t e) {
  if (g_sema_errors) return 0;
  int64_t k = 
m0_get(e, 0);  (void)k;
  if 
(k == N_INT) {    
    return m0_print_int(m0_get(e, 3));  
  } else {    
        if 
(k == N_STRING) {      
            int64_t p0 = 
m0_print("\"");      (void)p0;
      int64_t p1 = 
m0_print(m0_load_string(e, 3));      (void)p1;
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
            char* nm = m0_load_string(e, 3);
            if (g_current_module_name[0] != '\0') {
              for (int64_t xi = 0; xi < g_export_count; xi++) {
                if (m0_string_eq(g_export_fnname[xi], nm)) {
                  return m0_print(g_export_emitname[xi]);
                }
              }
            }
            /* [M1008] check: name not found in any module */
            if (g_current_module_name[0] != '\0') {
              for (int64_t xi = 0; xi < g_export_count; xi++) {
                if (g_export_modname[xi] == (char*)1) continue;
                if (!m0_string_eq(g_export_modname[xi], g_current_module_name) &&
                    m0_string_eq(g_export_fnname[xi], nm)) {
                  int64_t nmln = m0_get(e, 1);
                  int64_t nmcl = m0_get(e, 2);
                  fprintf(stderr, "%s:%lld:%lld: warning: [M1008] unqualified name '%s' (did you mean '%s.%s'?)\n",
                      g_filename, (long long)nmln, (long long)nmcl, nm,
                      g_export_modname[xi], nm);
                  break;
                }
              }
            }
            if (g_sema_errors) return 0;
            return m0_print(nm);          
          } else {            
                        if 
(k == N_BINARY) {              
                            int64_t p0 = 
m0_print("(");              (void)p0;
              int64_t p1 = 
emit_c_expr(reg, m0_get(e, 4));              (void)p1;
              int64_t p2 = 
m0_print(" ");              (void)p2;
              int64_t p3 = 
emit_c_op(m0_get(e, 3));              (void)p3;
              int64_t p4 = 
m0_print(" ");              (void)p4;
              int64_t p5 = 
emit_c_expr(reg, m0_get(e, 5));              (void)p5;
return m0_print(")");            
            } else {              
                            if 
(k == N_NOT) {                
                                int64_t p0 = 
m0_print("(!");                (void)p0;
                int64_t p1 = 
emit_c_expr(reg, m0_get(e, 3));                (void)p1;
return m0_print(")");              
              } else {                
                                if 
(k == N_FIELD) {                  
                                    int64_t base = m0_get(e, 3);
                    if (m0_get(base, 0) == N_NAME) {
                    char* mod_name = m0_load_string(base, 3);
                    char* fn_name = m0_load_string(e, 4);
                    for (int64_t xi = 0; xi < g_export_count; xi++) {
                      if (g_export_modname[xi] == (char*)1) continue;
                      if (m0_string_eq(g_export_modname[xi], mod_name) &&
                          m0_string_eq(g_export_fnname[xi], fn_name)) {
                        return m0_print(g_export_emitname[xi]);
                      }
                    }
                  }
                                    /* multi-level module name resolution
                                       e.g. std.string.concat → modpath="std.string" fn="concat" */
                  {
                    int64_t _cur = e;
                    char* _parts[16];
                    int _np = 0;
                    while (m0_get(_cur, 0) == N_FIELD && _np < 15) {
                      _parts[_np++] = m0_load_string(_cur, 4);
                      _cur = m0_get(_cur, 3);
                    }
                    if (m0_get(_cur, 0) == N_NAME && _np >= 1) {
                      _parts[_np++] = m0_load_string(_cur, 3);
                      char _mp[256] = "";
                      for (int _pi = _np - 1; _pi >= 1; _pi--) {
                        if (_mp[0]) strcat(_mp, ".");
                        strcat(_mp, _parts[_pi]);
                      }
                      char* _fn = _parts[0];
                      for (int64_t xi = 0; xi < g_export_count; xi++) {
                        if (g_export_modname[xi] == (char*)1) continue;
                        if (m0_string_eq(g_export_modname[xi], _mp) &&
                            m0_string_eq(g_export_fnname[xi], _fn)) {
                          return m0_print(g_export_emitname[xi]);
                        }
                      }
                    }
                  }
                  int64_t p0 = 
emit_c_expr(reg, m0_get(e, 3));                  (void)p0;
                  int64_t p1 = 
m0_print(".");                  (void)p1;
return m0_print(m0_load_string(e, 4));                
                } else {                  
                                    if 
(k == N_CALL) {                    
                                        int64_t p0 = 
emit_c_expr(reg, m0_get(e, 3));                    (void)p0;
                    int64_t p1 = 
m0_print("(");                    (void)p1;
                    int64_t p2 = 
emit_c_expr_ea(reg, m0_get(e, 4), 1);                    (void)p2;
return m0_print(")");                  
                  } else {                    
                                        if 
 (k == N_LET) {                      
    m0_print(m0_load_string(e, 3));                      
    m0_print(" = ");                      
    emit_c_expr(reg, m0_get(e, 5));                      
    m0_print(", ");                      
    return emit_c_expr(reg, m0_get(e, 6));                    
                       } else {                      
                                            if 
(k == N_IF) {                        
                                                int64_t p0 = 
m0_print("(");                        (void)p0;
                        int64_t p1 = 
emit_c_expr(reg, m0_get(e, 3));                        (void)p1;
                        int64_t p2 = 
m0_print(" ? ");                        (void)p2;
                        int64_t p3 = 
emit_c_expr(reg, m0_get(e, 4));                        (void)p3;
                        int64_t p4 = 
m0_print(" : ");                        (void)p4;
                        int64_t el = 
m0_get(e, 5);                        (void)el;
                        if 
(el != 0) {                          
                                                    int64_t p5 = 
emit_c_expr(reg, el);                          (void)p5;
p5;                        
                        } else {                          
                                                    int64_t p5 = 
m0_print("0");                          (void)p5;
p5;                        
                        }return m0_print(")");                      
                      } else {                        
                                                if 
(k == N_MATCH) {                          
                                                    int64_t p0 = 
m0_print("({ int64_t _m = ");                          (void)p0;
                          int64_t p1 = 
emit_c_expr(reg, m0_get(e, 3));                          (void)p1;
                          int64_t p2 = 
m0_print("; ");                          (void)p2;
                          int64_t p3 = 
emit_c_expr_arms_ea(reg, m0_get(e, 4));                          (void)p3;
return m0_print("; })");                        
                        } else {                          
                                                    if 
(k == N_RECORD) {                            
                            int64_t p0 = 
m0_print("{ ");                            (void)p0;
                            int64_t p1 = 
emit_c_expr_ef(reg, m0_get(e, 3), 1);                            (void)p1;
return m0_print(" }");                          
                          } else {
                            if
(k == N_WHILE) {
                                 m0_print("({ while (");
                                 emit_c_expr(reg, m0_get(e, 3));
                                 m0_print(") { ");
                                 emit_c_expr(reg, m0_get(e, 4));
                                 m0_print("; } 0; })");
                                 return 0;
                             } else {
                               if
 (k == N_FOR) {
                                    m0_print("({ int64_t ");
                                    m0_print(m0_load_string(e, 3));
                                    m0_print(" = ");
                                    emit_c_expr(reg, m0_get(e, 4));
                                    m0_print("; while (");
                                    m0_print(m0_load_string(e, 3));
                                    m0_print(" < ");
                                    emit_c_expr(reg, m0_get(e, 5));
                                    m0_print(") { ");
                                    emit_c_expr(reg, m0_get(e, 6));
                                    m0_print("; } 0; })");
                                   return 0;
                                  } else {
                                  if
 (k == N_FREEZE) {
                                        char* name = m0_load_string(e, 3);
                                        int64_t freeze_line = m0_get(e, 1);
                                        freeze_var(name, freeze_line);
                                        return m0_print("0");
                                    } else {
                                    if
 (k == N_NOW) {
                                        int64_t cond  = m0_get(e, 3);
                                        int64_t nline = m0_get(e, 1);
                                        int64_t ncol  = m0_get(e, 2);
                                        int64_t user_line = nline - g_preamble_line_offset;
                                        if (user_line < 1) user_line = 1;
                                        m0_print("({ if (!(");
                                        emit_c_expr(reg, cond);
                                        m0_print(")) { fprintf(stderr, \"");
                                        m0_print(g_filename);
                                        m0_print(":");
                                        { char lbuf[32]; snprintf(lbuf, sizeof(lbuf), "%lld", (long long)user_line); m0_print(lbuf); }
                                        m0_print(":");
                                        { char lbuf[32]; snprintf(lbuf, sizeof(lbuf), "%lld", (long long)ncol); m0_print(lbuf); }
                                        m0_print(": error: [M1103] 'now' assertion violated: (invariant)\\n\"); exit(1); } 0; })");
                                        return 0;
                                    } else {
                                     if
  (k == N_WAS) {
                                        char* name = m0_load_string(e, 3);
                                        char* phase = m0_load_string(e, 4);
                                        /* Phase Graph: try compile-time resolution first */
                                        int pg_result = phase_graph_query(name, phase);
                                        if (pg_result == 1) {
                                            m0_print("1");
                                            return 0;
                                        } else if (pg_result == 0) {
                                            m0_print("0");
                                            return 0;
                                        }
                                        /* Fall back to runtime phase history scan */
                                        if (m0_string_eq(phase, "live") == 1) {
                                            if (is_frozen(name) == 1) {
                                                m0_print("1");
                                            } else {
                                                m0_print("0");
                                            }
                                        } else {
                                            if (phase_was(name, phase) == 1) {
                                                m0_print("1");
                                            } else {
                                                m0_print("0");
                                            }
                                        }
                                        return 0;
                                    } else {
                                    if
 (k == N_WHEN) {
                                        int64_t cond = m0_get(e, 3);
                                        int64_t body = m0_get(e, 4);
                                        char* watched = extract_watched_var(cond);
                                        if (watched && watched[0] != '\0') {
                                            when_add(watched, cond, body, m0_get(e, 1), m0_get(e, 2));
                                        }
                                        m0_print("({ if (");
                                        emit_c_expr(reg, cond);
                                        m0_print(") { ");
                                        emit_c_expr(reg, body);
                                        m0_print("; } 0; })");
                                        return 0;
                                    } else {
                                    if
 (k == N_WILL) {
                                        int64_t cond = m0_get(e, 3);
                                        char* watched = extract_watched_var(cond);
                                        if (watched && watched[0] != '\0') {
                                            will_add(watched, cond, m0_get(e, 1), m0_get(e, 2));
                                        }
                                        int64_t idx = will_count - 1;
                                        if (idx < 0) idx = 0;
                                        char ibuf[16];
                                        snprintf(ibuf, sizeof(ibuf), "%lld", (long long)idx);
                                        if (is_phase_will(cond)) {
                                            char* phase = extract_phase_name(cond);
                                            if (phase_was(watched, phase) == 1) {
                                                m0_print("({ _will_");
                                                m0_print(ibuf);
                                                m0_print(" = 1; 0; })");
                                            } else {
                                                m0_print("0");
                                            }
                                        } else {
                                            m0_print("({ if (");
                                            emit_c_expr(reg, cond);
                                            m0_print(") { _will_");
                                            m0_print(ibuf);
                                            m0_print(" = 1; } 0; })");
                                        }
                                        return 0;
                                    } else {
                                    if
   (k == N_RETURN) {
                                         int64_t val = m0_get(e, 3);
                                         m0_print("({ _m1_ret = ");
                                         emit_c_expr(reg, val);
                                         m0_print("; goto __m1_return; 0; })");
                                         return 0;
                                     } else {
                                     if
   (k == N_BREAK) {
                                          m0_print("({ break; 0; })");
                                          return 0;
                                     } else {
                                     if
   (k == N_CONTINUE) {
                                          m0_print("({ continue; 0; })");
                                          return 0;
                                     } else {
                                     if
   (k == N_SEQ) {
                                        m0_print("(");
                                        emit_c_expr(reg, m0_get(e, 3));
                                        m0_print(", ");
                                        emit_c_expr(reg, m0_get(e, 4));
                                        return m0_print(")");
                                    } else {
                                    if
  (k == N_ASSIGN) {
                                        char* name = m0_load_string(e, 3);
                                            if (is_frozen(name) == 1) {
                                           int64_t assign_line = m0_get(e, 1);
                                           int64_t origin_line = get_freeze_line(name);
                                           int64_t user_origin = origin_line - g_preamble_line_offset;
                                           if (user_origin < 1) user_origin = 1;
                                           char errbuf[512];
                                           snprintf(errbuf, sizeof(errbuf),
                                                "[M1003] cannot assign to '%s', frozen at line %lld",
                                               name, (long long)user_origin);
                                           report_error(assign_line, m0_get(e, 2), errbuf);
                                           exit(1);
                                       }
                                    /* track phase history */
                                    {
                                        int64_t rhs = m0_get(e, 4);
                                        if (m0_get(rhs, 0) == N_NAME) {
                                            char* rhs_name = m0_load_string(rhs, 3);
                                            phase_record(name, rhs_name);
                                        }
                                    }
                                    m0_print("({ ");
                                    m0_print("(");
                                    m0_print(name);
                                    m0_print(" = ");
                                    emit_c_expr(reg, m0_get(e, 4));
                                    m0_print("); ");
                                     emit_when_checks_for(reg, name);
                                      emit_will_checks_for(reg, name);
                                    m0_print(name);
                                    m0_print("; })");
                                   return 0;
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
int64_t emit_c_params(int64_t reg, int64_t params) {
  if 
(m0_is_nil(params) == 1) {    
    return 0;  
  } else {    
    emit_c_type(reg, m0_head(params));    int64_t rest = 
m0_tail(params);    (void)rest;
    if 
(m0_is_nil(rest) == 0) {      
      m0_print(", ");    
    } else {      
      0;    
    }return emit_c_params(reg, rest);  
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
    int64_t pl = p;
    while (m0_is_nil(pl) == 0) {
      acc = m0_cons(m0_head(pl), acc);
      pl = m0_tail(pl);
    }
return flatten_fn_params(m0_get(t, 5), acc);  
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
emit_c_type(reg, ret);m0_print(" ");m0_print(cn);m0_print("(");emit_c_params(reg, params);return m0_print(");\n");  
  } else {    
        int64_t p0 = 
emit_c_type(reg, t);    (void)p0;
    int64_t p1 = 
m0_print(" ");    (void)p1;
    int64_t p2 = 
m0_print(cn);    (void)p2;
return m0_print(";\n");  
  }}
int64_t emit_let_decls(int64_t e) {
  if (e == 0) return 0;
  int64_t k = m0_get(e, 0);
  if (k == N_LET) {
    char* nm = m0_load_string(e, 3);
    int already = 0;
    for (int64_t _di = 0; _di < g_export_count; _di++) {
      if (g_export_modname[_di] == (char*)1 && g_export_fnname[_di] == nm) { already = 1; break; }
    }
    if (!already && g_export_count < MAX_EXPORTS) {
      g_export_modname[g_export_count] = (char*)1;
      g_export_fnname[g_export_count] = nm;
      g_export_emitname[g_export_count] = nm;
      g_export_count++;
      emit_c_type(0, m0_get(e, 4));
      m0_print(" ");
      m0_print(nm);
      m0_print(";\n");
    }
    emit_let_decls(m0_get(e, 6));
    return 0;
  } else if (k == N_SEQ) {
    emit_let_decls(m0_get(e, 3));
    emit_let_decls(m0_get(e, 4));
    return 0;
  } else if (k == N_IF) {
    emit_let_decls(m0_get(e, 4));
    emit_let_decls(m0_get(e, 5));
    return 0;
  } else if (k == N_WHILE || k == N_FOR) {
    emit_let_decls(m0_get(e, 4));
    return 0;
  }
  return 0;
}

int64_t emit_fn(int64_t reg, int64_t d) {
  reset_frozen();
  reset_now();
  reset_when();
  reset_will();
  reset_phase();
  char *nm = 
m0_load_string(d, 3);  (void)nm;
  int64_t params = 
m0_get(d, 4);  (void)params;
  int64_t ret = 
m0_get(d, 6);  (void)ret;
  int64_t body = 
m0_get(d, 7);  (void)body;
  int is_main = 
(m0_string_eq(nm, "main") == 1);  (void)is_main;
  if (
is_main) {    
        int64_t p = 
m0_print("int");    (void)p;
p;  
  } else {    
    emit_c_type(reg, ret);  
  }  int64_t p0 = 
m0_print(" ");  (void)p0;
  int64_t p1;  
  if (g_current_module_name[0] != '\0' && !is_main) {
    char _mod_emit[256];
    strncpy_s(_mod_emit, sizeof(_mod_emit), g_current_module_name, _TRUNCATE);
    for (char* _mp = _mod_emit; *_mp; _mp++) if (*_mp == '.') *_mp = '_';
    p1 = m0_print(_mod_emit);
    p1 = m0_print("__");
  }  p1 = m0_print(nm);  (void)p1;
  int64_t p2 = 
m0_print("(");  (void)p2;
  if (
is_main) {    
        int64_t p3 = 
m0_print("void");    (void)p3;
p3;  
  } else {    
    emit_fn_ep(reg, params, 1);  
  }  int64_t p3 = 
m0_print(") {\n");  (void)p3;
  int64_t p4 = 
m0_print("int64_t _will_0=0,_will_1=0,_will_2=0,_will_3=0,"
         "_will_4=0,_will_5=0,_will_6=0,_will_7=0,_will_8=0,_will_9=0;\n");  (void)p4;
  emit_let_decls(body);
  /* Phase Graph: build static transition graph for compile-time was folding */
  phase_graph_build(body);

  int64_t p5;
  if (is_main) {
      p5 = m0_print("  int _m1_ret = 0;\n  _m1_ret = ");
  } else {
      p5 = m0_print("  ");
      p5 = emit_c_type(reg, ret);
      p5 = m0_print(" _m1_ret = 0;\n  _m1_ret = ");
  }  (void)p5;
  int64_t p6 = 
m0_print("(");  (void)p6;
  p6 = 
emit_c_expr(reg, body);  (void)p6;
  p6 = 
m0_print(")");  (void)p6;
  int64_t p7 = 
m0_print(";\n  goto __m1_return;\n__m1_return:\n");  (void)p7;
  emit_will_return_checks();
return m0_print("  return _m1_ret;\n}\n");}
int64_t emit_module_pass1(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t d = 
m0_head(l);    (void)d;
    if 
(m0_get(d, 0) == N_TYPE_DECL) {      
      emit_typedef(reg, m0_get(d, 4), m0_load_string(d, 3));    
    } else {      
      0;    
    }return emit_module_pass1(reg, m0_tail(l));  
  }}
int64_t emit_module_pass2(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t d = 
m0_head(l);    (void)d;
    if 
(m0_get(d, 0) == N_EXTERN) {      
      emit_extern(reg, d);    
    } else {      
      0;    
    }return emit_module_pass2(reg, m0_tail(l));  
  }}
int64_t emit_module_pass3(int64_t reg, int64_t l) {
  if 
(m0_is_nil(l) == 1) {    
    return 0;  
  } else {    
        int64_t d = 
m0_head(l);    (void)d;
    if 
(m0_get(d, 0) == N_FN_DECL) {      
      emit_fn(reg, d);    
    } else {      
      0;    
    }return emit_module_pass3(reg, m0_tail(l));  
  }}
int64_t emit_module(int64_t m) {
  int64_t decls = 
m0_get(m, 4);  (void)decls;
  int64_t reg = 
build_reg(decls, m0_nil);  (void)reg;
  int64_t p1 = 
emit_module_pass1(reg, decls);  (void)p1;
  int64_t n1 = 
m0_print("\n");  (void)n1;
  int64_t p2 = 
emit_module_pass2(reg, decls);  (void)p2;
  int64_t n2 = 
m0_print("\n");  (void)n2;
  int64_t p3 = 
emit_module_pass3(reg, decls);  (void)p3;
return 0;}
int main(int argc, char** argv) {
  char *filename = 
m0_get_env("M1_SOURCE");  (void)filename;
  if (argc >= 2) {
    strncpy_s(g_filename, sizeof(g_filename), argv[1], _TRUNCATE);
    filename = argv[1];
  }
  for (char* _c = g_filename; *_c; _c++) { if (*_c == '\\') *_c = '/'; }
  if 
(m0_string_eq(filename, "") == 1) {    
        int64_t e = 
m0_print("[M1000] error: no source file\n");    (void)e;
return 1;  
  } else {    
        char *src = 
m0_read_file(filename);    (void)src;
    /* compute preamble line offset from env */
    {
      char* pl = m0_get_env("M1_PREAMBLE_LINES");
      g_preamble_line_offset = 0;
      if (pl && m0_string_eq(pl, "") == 0) {
        for (const char* c = pl; *c >= '0' && *c <= '9'; c++)
          g_preamble_line_offset = g_preamble_line_offset * 10 + (*c - '0');
      }
    }
    /* set up module resolution directories */
    {
      char* stdlib_dir = m0_get_env("M1_STDLIB_DIR");
      if (stdlib_dir && m0_string_eq(stdlib_dir, "") == 0) {
        strncpy_s(g_stdlib_dir, sizeof(g_stdlib_dir), stdlib_dir, _TRUNCATE);
      } else {
        /* try common locations relative to source file */
        const char* candidates[] = {
          ".\\stdlib",
          "..\\stdlib",
          "..\\..\\stdlib",
          "..\\..\\..\\stdlib",
          "stdlib",
          NULL
        };
        int64_t found = 0;
        for (int64_t ci = 0; candidates[ci] != NULL; ci++) {
          char testpath[1024];
          snprintf(testpath, sizeof(testpath), "%s\\std.m1", candidates[ci]);
          if (m0_read_file(testpath)) {
            strncpy_s(g_stdlib_dir, sizeof(g_stdlib_dir), candidates[ci], _TRUNCATE);
            found = 1;
            break;
          }
        }
        if (!found) {
          strncpy_s(g_stdlib_dir, sizeof(g_stdlib_dir), ".\\stdlib", _TRUNCATE);
        }
      }
      /* extract source directory from filename */
      strncpy_s(g_src_dir, sizeof(g_src_dir), filename, _TRUNCATE);
      for (int64_t i = strlen(g_src_dir) - 1; i >= 0; i--) {
        if (g_src_dir[i] == '/' || g_src_dir[i] == '\\') {
          g_src_dir[i] = '\0';
          break;
        }
        if (i == 0) {
          strncpy_s(g_src_dir, sizeof(g_src_dir), ".", _TRUNCATE);
        }
      }
    }
    M1Lexer l = m1_lexer_init(src);    (void)l;
    M1LexResult r = m1_lexer_next(l);    (void)r;
    PS s = {(r).token, (r).lexer, 0, 0};    (void)s;
    PR pr = parse_program(s);    (void)pr;
    int64_t mods = 
m0_get((pr).node, 3);    (void)mods;
    /* Parse top-level declarations after module/import list
       (new-style `module name;` syntax puts decls at top level, not in { }) */
    {
      PS cur = pr.st;
      int64_t extra = m0_nil;
      while (ps_kind(cur) != TK_EOF) {
        if (ps_kind(cur) == TK_IMPORT) {
          /* inline import parsing (same pattern as gather_modules) */
          PS s_after_import = ps_adv(cur);
          char* imp_name = ps_str(s_after_import);
          PS s2 = ps_adv(s_after_import);
          while (ps_kind(s2) == TK_DOT) {
            PS s_after_dot = ps_adv(s2);
            char* seg = ps_str(s_after_dot);
            imp_name = m0_string_concat(imp_name, ".");
            imp_name = m0_string_concat(imp_name, seg);
            s2 = ps_adv(s_after_dot);
          }
          s2 = ps_adv(s2);
          extra = m0_cons(n_import(imp_name, ps_line(cur), ps_col(cur)), extra);
          cur = s2;
        } else {
          PR dr = parse_decl(cur);
          extra = m0_cons((dr).node, extra);
          cur = (dr).st;
        }
      }
            if (m0_is_nil(extra) == 0) {
        /* prepend extra items to mods (append to end of list) */
        int64_t rm = rev(mods);
        int64_t fe = rev(extra);
        while (m0_is_nil(fe) == 0) {
          rm = m0_cons(m0_head(fe), rm);
          fe = m0_tail(fe);
        }
        mods = rev(rm);
        /* update N_PROG slot 3 */
        m0_set((pr).node, 3, mods);
      }
    }
    /* resolve imports */
    {
      int64_t err_count = 0;
      int64_t ml = mods;
      while (m0_is_nil(ml) == 0) {
        int64_t m = m0_head(ml);
        if (m0_get(m, 0) == N_IMPORT) {
          char* imp_name = m0_load_string(m, 3);
          int64_t is_stdlib = 0;
          char* resolved = resolve_module(imp_name, &is_stdlib);
          if (resolved == NULL) {
            int64_t imp_line = m0_get(m, 1);
            int64_t imp_col = m0_get(m, 2);
            int64_t user_line = imp_line - g_preamble_line_offset;
            if (user_line < 1) user_line = 1;
            fprintf(stderr, "%s:%lld:%lld: error: [M1007] module '%s' not found\n",
                g_filename, (long long)user_line, (long long)imp_col, imp_name);
            err_count++;
          } else {
            m0_store_string(m, 4, resolved);
          }
        }
        ml = m0_tail(ml);
      }
      if (err_count > 0) {
        return 1;
      }
    }
    /* ---- Phase 2.3: Build dependency graph, detect cycles, topological sort ---- */
    int64_t all_mods = m1_vector_new();
    int64_t graph_err = 0;
    int64_t cycle_found = 0;
    /* Helper to find module entry by path in the registry */
    /* Step 1: Add entry file modules to registry */
    {
      char* entry_name = "";
      {
        int64_t ml2 = mods;
        while (m0_is_nil(ml2) == 0) {
          int64_t m = m0_head(ml2);
          if (m0_get(m, 0) == N_MODULE_DECL) {
            entry_name = m0_load_string(m, 3);
          }
          ml2 = m0_tail(ml2);
        }
      }
      int64_t entry = m0_alloc(5);
      m0_store_string(entry, 0, entry_name);
      m0_store_string(entry, 1, g_filename);
      m0_set(entry, 2, mods);
      m0_set(entry, 3, m0_nil);
      m0_set(entry, 4, 0);
      m1_vector_push(all_mods, entry);
    }
    /* Step 2: Recursively parse all imported files */
    {
      int64_t worklist = m1_vector_new();
      /* Seed worklist with imports from entry file */
      {
        int64_t wl = mods;
        while (m0_is_nil(wl) == 0) {
          int64_t m = m0_head(wl);
          if (m0_get(m, 0) == N_IMPORT) {
            char* rp = m0_load_string(m, 4);
            if (rp) m1_vector_push(worklist, (int64_t)rp);
          }
          wl = m0_tail(wl);
        }
      }
      int64_t wl_idx = 0;
      while (wl_idx < m1_vector_len(worklist)) {
        char* path = (char*)m1_vector_get(worklist, wl_idx);
        wl_idx++;
        /* Skip if already registered */
        int64_t found = 0;
        for (int64_t ri = 0; ri < m1_vector_len(all_mods); ri++) {
          int64_t e = m1_vector_get(all_mods, ri);
          if (m0_string_eq(m0_load_string(e, 1), path)) { found = 1; break; }
        }
        if (found) continue;
        char* content = m0_read_file(path);
        if (!content) {
          fprintf(stderr, "%s: error: [M1008] cannot read module file '%s'\n", g_filename, path);
          graph_err = 1; break;
        }
        M1Lexer lx = m1_lexer_init(content);
        M1LexResult lr = m1_lexer_next(lx);
        PS ps2 = {lr.token, lr.lexer, 0, 0};
        PR pr2 = parse_program(ps2);
        int64_t imp_mods = m0_get(pr2.node, 3);
        /* Parse remaining top-level decls (new-style `module name;` syntax) */
        {
          PS icur = pr2.st;
          int64_t iextra = m0_nil;
          while (ps_kind(icur) != TK_EOF) {
            if (ps_kind(icur) == TK_IMPORT) {
              PS s_after_import = ps_adv(icur);
              char* iname2 = ps_str(s_after_import);
              PS s3 = ps_adv(s_after_import);
              while (ps_kind(s3) == TK_DOT) {
                PS s_after_dot = ps_adv(s3);
                char* seg = ps_str(s_after_dot);
                iname2 = m0_string_concat(iname2, ".");
                iname2 = m0_string_concat(iname2, seg);
                s3 = ps_adv(s_after_dot);
              }
              s3 = ps_adv(s3);
              iextra = m0_cons(n_import(iname2, ps_line(icur), ps_col(icur)), iextra);
              icur = s3;
            } else {
              PR dr = parse_decl(icur);
              iextra = m0_cons((dr).node, iextra);
              icur = (dr).st;
            }
          }
          if (m0_is_nil(iextra) == 0) {
            int64_t rmi = rev(imp_mods);
            int64_t fei = rev(iextra);
            while (m0_is_nil(fei) == 0) {
              rmi = m0_cons(m0_head(fei), rmi);
              fei = m0_tail(fei);
            }
            imp_mods = rev(rmi);
            m0_set((pr2).node, 3, imp_mods);
          }
        }
        /* Extract module name */
        char* imp_name = "";
        {
          int64_t iml = imp_mods;
          while (m0_is_nil(iml) == 0) {
            int64_t im = m0_head(iml);
            if (m0_get(im, 0) == N_MODULE_DECL) {
              imp_name = m0_load_string(im, 3);
            }
            if (m0_get(im, 0) == N_MOD) {
              imp_name = m0_load_string(im, 3);
            }
            iml = m0_tail(iml);
          }
        }
        /* Resolve imports within this imported file */
        {
          int64_t iml = imp_mods;
          while (m0_is_nil(iml) == 0) {
            int64_t im = m0_head(iml);
            if (m0_get(im, 0) == N_IMPORT) {
              char* iname = m0_load_string(im, 3);
              int64_t is_stdlib = 0;
              char* resolved = resolve_module(iname, &is_stdlib);
              if (!resolved) {
                int64_t iline = m0_get(im, 1) - g_preamble_line_offset;
                if (iline < 1) iline = 1;
                fprintf(stderr, "%s:%lld:%lld: error: [M1007] module '%s' not found (imported by '%s')\n",
                  path, (long long)iline, (long long)m0_get(im, 2), iname, imp_name);
                graph_err = 1;
              } else {
                m0_store_string(im, 4, resolved);
                int64_t already = 0;
                for (int64_t wi = 0; wi < m1_vector_len(worklist); wi++) {
                  if (m0_string_eq((char*)m1_vector_get(worklist, wi), resolved)) { already = 1; break; }
                }
                if (!already) m1_vector_push(worklist, (int64_t)resolved);
              }
            }
            iml = m0_tail(iml);
          }
        }
        if (graph_err) break;
        int64_t entry = m0_alloc(5);
        m0_store_string(entry, 0, imp_name);
        m0_store_string(entry, 1, path);
        m0_set(entry, 2, imp_mods);
        m0_set(entry, 3, m0_nil);
        m0_set(entry, 4, 0);
        m1_vector_push(all_mods, entry);
      }
      if (graph_err) return 1;
    }
    /* Step 3: Build dependency edges */
    {
      int64_t rlen = m1_vector_len(all_mods);
      for (int64_t i = 0; i < rlen; i++) {
        int64_t e = m1_vector_get(all_mods, i);
        int64_t mlist = m0_get(e, 2);
        int64_t deps = m0_nil;
        int64_t ml = mlist;
        while (m0_is_nil(ml) == 0) {
          int64_t m = m0_head(ml);
          if (m0_get(m, 0) == N_IMPORT) {
            char* rp = m0_load_string(m, 4);
            if (rp) {
              for (int64_t j = 0; j < rlen; j++) {
                if (j == i) continue;
                int64_t other = m1_vector_get(all_mods, j);
                if (m0_string_eq(m0_load_string(other, 1), rp)) {
                  deps = m0_cons(j, deps);
                  break;
                }
              }
            }
          }
          ml = m0_tail(ml);
        }
        m0_set(e, 3, deps);
      }
    }
    /* Step 4: DFS cycle detection */
    {
      int64_t rlen = m1_vector_len(all_mods);
      int64_t* order = (int64_t*)malloc((size_t)rlen * sizeof(int64_t));
      int64_t order_len = 0;
      /* iterative DFS with explicit stack for state */
      int64_t* state = (int64_t*)calloc((size_t)rlen, sizeof(int64_t)); /* 0=unvisited */
      int64_t* visit_stack = (int64_t*)malloc((size_t)rlen * sizeof(int64_t));
      int64_t vs_top = 0;
      for (int64_t i = 0; i < rlen; i++) {
        if (state[i] != 0) continue;
        visit_stack[vs_top++] = i;
        state[i] = 1; /* visiting */
        while (vs_top > 0) {
          int64_t cur = visit_stack[vs_top - 1];
          int64_t e = m1_vector_get(all_mods, cur);
          int64_t dl = m0_get(e, 3);
          /* advance iter for this node */
          int64_t found_next = 0;
          while (m0_is_nil(dl) == 0) {
            int64_t head = m0_head(dl);
            int64_t next_idx = (int64_t)head;
            dl = m0_tail(dl);
            if (state[next_idx] == 0) {
              visit_stack[vs_top++] = next_idx;
              state[next_idx] = 1;
              found_next = 1;
              break;
            } else if (state[next_idx] == 1) {
              /* cycle detected! */
              if (!cycle_found) {
                fprintf(stderr, "%s: error: [M1009] circular module dependency detected\n", g_filename);
                cycle_found = 1;
              }
            }
          }
          if (found_next) continue;
          /* no more children: mark done and pop */
          state[cur] = 2;
          vs_top--;
          order[order_len++] = cur;
        }
      }
      free(state);
      /* post-order gives dependencies before dependents — emit directly */
      if (cycle_found) { free(order); return 1; }
      /* Step 4a.5: Group flat module items into N_MOD containers
         (new-style `module name;` puts decls at top level, not in { }) */
      for (int64_t gi = 0; gi < rlen; gi++) {
        int64_t ge = m1_vector_get(all_mods, gi);
        int64_t flat = m0_get(ge, 2);
          int64_t grouped = m0_nil;
        int64_t gf = flat;
        int64_t cur_decls = m0_nil;
        char* cur_mname = NULL;
        int64_t cur_mln = 0, cur_mcl = 0;
        while (m0_is_nil(gf) == 0) {
          int64_t item = m0_head(gf);
          int64_t item_type = m0_get(item, 0);
          gf = m0_tail(gf);
          if (item_type == N_MODULE_DECL) {
            if (cur_mname) {
              cur_decls = rev(cur_decls);
              grouped = m0_cons(n_mod(cur_mname, cur_decls, list_len(cur_decls), cur_mln, cur_mcl), grouped);
              cur_decls = m0_nil;
            }
            cur_mname = m0_load_string(item, 3);
            cur_mln = m0_get(item, 1);
            cur_mcl = m0_get(item, 2);
          } else if (item_type == N_MOD) {
            if (cur_mname) {
              cur_decls = rev(cur_decls);
              grouped = m0_cons(n_mod(cur_mname, cur_decls, list_len(cur_decls), cur_mln, cur_mcl), grouped);
              cur_decls = m0_nil; cur_mname = NULL;
            }
            grouped = m0_cons(item, grouped);
          } else {
            if (cur_mname) { cur_decls = m0_cons(item, cur_decls); }
            else { grouped = m0_cons(item, grouped); }
          }
        }
        if (cur_mname) {
          cur_decls = rev(cur_decls);
          grouped = m0_cons(n_mod(cur_mname, cur_decls, list_len(cur_decls), cur_mln, cur_mcl), grouped);
        }
        m0_set(ge, 2, rev(grouped));
      }
      /* Step 4b: Build export table for module-qualified name resolution */
      g_export_count = 0;
      for (int64_t ei = 0; ei < rlen; ei++) {
        int64_t e = m1_vector_get(all_mods, order[ei]);
        char* ename = m0_load_string(e, 0);
        if (ename[0] == '\0') continue;
        int64_t mlist = m0_get(e, 2);
        int64_t el = mlist;
        while (m0_is_nil(el) == 0) {
          int64_t m = m0_head(el);
          if (m0_get(m, 0) == N_MOD) {
            int64_t decls = m0_get(m, 4);
            int64_t dl = decls;
            while (m0_is_nil(dl) == 0) {
              int64_t d = m0_head(dl);
              if (m0_get(d, 0) == N_FN_DECL && g_export_count < MAX_EXPORTS) {
                char* fn = m0_load_string(d, 3);
                g_export_modname[g_export_count] = ename;
                g_export_fnname[g_export_count] = fn;
                /* build emit name: module__fn */
                {
                  char emitbuf[256];
                  snprintf(emitbuf, sizeof(emitbuf), "%s__%s", ename, fn);
                  for (char* _p = emitbuf; *_p; _p++) if (*_p == '.') *_p = '_';
                  {
                    size_t _elen = strlen(emitbuf) + 1;
                    char* _edup = (char*)malloc(_elen);
                    if (_edup) memcpy(_edup, emitbuf, _elen);
                    g_export_emitname[g_export_count] = _edup ? _edup : emitbuf;
                  }
                }
                g_export_count++;
              }
              if (m0_get(d, 0) == N_EXTERN && g_export_count < MAX_EXPORTS) {
                char* cn = m0_load_string(d, 3);
                g_export_modname[g_export_count] = ename;
                g_export_fnname[g_export_count] = cn;
                g_export_emitname[g_export_count] = cn;
                g_export_count++;
              }
              dl = m0_tail(dl);
            }
          }
          el = m0_tail(el);
        }
      }
      /* Step 4c: Pre-codegen semantic pass — check for M1008 errors */
      if (g_sema_errors == 0) {
        for (int64_t si = 0; si < rlen; si++) {
          int64_t e = m1_vector_get(all_mods, order[si]);
          g_current_module_name = m0_load_string(e, 0);
          if (g_current_module_name[0] == '\0') continue;
          int64_t mlist = m0_get(e, 2);
          int64_t ml = mlist;
          while (m0_is_nil(ml) == 0) {
            int64_t m = m0_head(ml);
            if (m0_get(m, 0) == N_MOD) {
              int64_t decls = m0_get(m, 4);
              int64_t dl = decls;
              while (m0_is_nil(dl) == 0) {
                int64_t d = m0_head(dl);
                if (m0_get(d, 0) == N_FN_DECL) {
                  emit_c_expr_check_names(m0_get(d, 6));
                }
                dl = m0_tail(dl);
              }
            }
            ml = m0_tail(ml);
          }
        }
        g_current_module_name = "";
      }
      if (g_sema_errors) return 1;
      /* Step 5: Emit modules in topological order */
      int64_t header_printed = 0;
      for (int64_t si = 0; si < rlen; si++) {
        int64_t e = m1_vector_get(all_mods, order[si]);
        g_current_module_name = m0_load_string(e, 0);
        int64_t mlist = m0_get(e, 2);
        int64_t ml = mlist;
        while (m0_is_nil(ml) == 0) {
          int64_t m = m0_head(ml);
          if (m0_get(m, 0) == N_MOD) {
            if (!header_printed) {
              m0_print("#include <stdio.h>\n#include <stdint.h>\n#include <stdlib.h>\n\n");
              m0_print("/* runtime function declarations */\n");
              m0_print("int64_t say(char* s);\n");
              m0_print("int64_t show(char* s);\n");
              m0_print("char* string_concat(char* a, char* b);\n");
              m0_print("char* int_to_string(int64_t n);\n");
              m0_print("int64_t string_len(char* s);\n");
              m0_print("int64_t string_to_int(char* s);\n");
              m0_print("char* read_file(char* path);\n");
              m0_print("int64_t write_file(char* path, char* content);\n");
              m0_print("int64_t vector_new(void);\n");
              m0_print("int64_t vector_push(int64_t v, int64_t x);\n");
              m0_print("int64_t vector_get(int64_t v, int64_t i);\n");
              m0_print("int64_t vector_set(int64_t v, int64_t i, int64_t x);\n");
              m0_print("int64_t vector_len(int64_t v);\n");
              m0_print("int64_t vector_sort(int64_t v);\n");
              m0_print("char* read_line(void);\n");
              m0_print("int64_t read_int(void);\n");
              m0_print("int64_t char_at(const char* s, int64_t i);\n");
              m0_print("char* substring(const char* s, int64_t start, int64_t len);\n");
              m0_print("int64_t string_split(const char* s, const char* delim);\n");
              m0_print("char* vector_get_str(int64_t v, int64_t i);\n");
              m0_print("int64_t map_new(void);\n");
              m0_print("int64_t map_set(int64_t m, int64_t k, int64_t v);\n");
              m0_print("int64_t map_get(int64_t m, int64_t k);\n");
              m0_print("int64_t map_has(int64_t m, int64_t k);\n");
              m0_print("int64_t map_len(int64_t m);\n");
              m0_print("int64_t matrix_new(int64_t rows, int64_t cols);\n");
              m0_print("int64_t matrix_get(int64_t m, int64_t r, int64_t c);\n");
              m0_print("int64_t matrix_set(int64_t m, int64_t r, int64_t c, int64_t v);\n");
              m0_print("int64_t float_of_int(int64_t n);\n");
              m0_print("int64_t float_add(int64_t a, int64_t b);\n");
              m0_print("int64_t float_sub(int64_t a, int64_t b);\n");
              m0_print("int64_t float_mul(int64_t a, int64_t b);\n");
              m0_print("int64_t float_div(int64_t a, int64_t b);\n");
              m0_print("int64_t float_lt(int64_t a, int64_t b);\n");
              m0_print("int64_t float_gt(int64_t a, int64_t b);\n");
              m0_print("int64_t float_eq(int64_t a, int64_t b);\n");
              m0_print("char* float_to_string(int64_t f);\n");
              m0_print("int64_t string_to_float(const char* s);\n\n");
              header_printed = 1;
            }
            emit_module(m);
          }
          ml = m0_tail(ml);
        }
      }
      g_current_module_name = "";
    }
    return graph_err || cycle_found || g_sema_errors;
  }}
