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

/* Module: M1Lexer */
typedef struct M1Tk M1Tk;
struct M1Tk {
  int tag;
  union {
    char _unused[1];
    } data;
};
enum M1Tk_tag {
  M1Tk_TkEof,
  M1Tk_TkInt,
  M1Tk_TkFloat,
  M1Tk_TkString,
  M1Tk_TkChar,
  M1Tk_TkIdent,
  M1Tk_TkArrow,
  M1Tk_TkLArrow,
  M1Tk_TkBidi,
  M1Tk_TkEq,
  M1Tk_TkEqEq,
  M1Tk_TkNeq,
  M1Tk_TkLt,
  M1Tk_TkGt,
  M1Tk_TkLe,
  M1Tk_TkGe,
  M1Tk_TkAnd,
  M1Tk_TkOr,
  M1Tk_TkPipe,
  M1Tk_TkColon,
  M1Tk_TkComma,
  M1Tk_TkDot,
  M1Tk_TkSemi,
  M1Tk_TkAt,
  M1Tk_TkLBrace,
  M1Tk_TkRBrace,
  M1Tk_TkLParen,
  M1Tk_TkRParen,
  M1Tk_TkLBrack,
  M1Tk_TkRBrack,
  M1Tk_TkPlus,
  M1Tk_TkMinus,
  M1Tk_TkStar,
  M1Tk_TkSlash,
  M1Tk_TkPercent,
  M1Tk_TkUnit,
  M1Tk_TkModule,
  M1Tk_TkType,
  M1Tk_TkFn,
  M1Tk_TkLet,
  M1Tk_TkMatch,
  M1Tk_TkIf,
  M1Tk_TkElse,
  M1Tk_TkTrue,
  M1Tk_TkFalse,
  M1Tk_TkExternal,
  M1Tk_TkNot,
  M1Tk_TkForall,
  M1Tk_TkExists,
  M1Tk_TkMut,
  M1Tk_TkWhile,
  M1Tk_TkFreeze,
  M1Tk_TkNow,
  M1Tk_TkWwas,
  M1Tk_TkWhen,
  M1Tk_TkWill,
  M1Tk_TkWorld,
  M1Tk_TkDo,
  M1Tk_TkSet,
  M1Tk_TkPick,
  M1Tk_TkShape,
  M1Tk_TkLive,
  M1Tk_TkSay,
  M1Tk_TkShow,
  M1Tk_TkThen,
  M1Tk_TkRequires,
  M1Tk_TkEnsures
};
typedef struct {
  M1Tk kind;  
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
extern int64_t m0_char_at(char*, int64_t);
extern char* m0_substr(char*, int64_t, int64_t);
extern int64_t m0_string_eq(char*, char*);
extern int64_t m0_string_len(char*);
extern int64_t m0_print(char*);
extern int64_t m0_print_int(int64_t);
extern int64_t m0_print_char(int64_t);
static inline M1Tk TkEof() {
  M1Tk v = { .tag = M1Tk_TkEof, .data = {0} };
  return v;
}
static inline M1Tk TkInt() {
  M1Tk v = { .tag = M1Tk_TkInt, .data = {0} };
  return v;
}
static inline M1Tk TkFloat() {
  M1Tk v = { .tag = M1Tk_TkFloat, .data = {0} };
  return v;
}
static inline M1Tk TkString() {
  M1Tk v = { .tag = M1Tk_TkString, .data = {0} };
  return v;
}
static inline M1Tk TkChar() {
  M1Tk v = { .tag = M1Tk_TkChar, .data = {0} };
  return v;
}
static inline M1Tk TkIdent() {
  M1Tk v = { .tag = M1Tk_TkIdent, .data = {0} };
  return v;
}
static inline M1Tk TkArrow() {
  M1Tk v = { .tag = M1Tk_TkArrow, .data = {0} };
  return v;
}
static inline M1Tk TkLArrow() {
  M1Tk v = { .tag = M1Tk_TkLArrow, .data = {0} };
  return v;
}
static inline M1Tk TkBidi() {
  M1Tk v = { .tag = M1Tk_TkBidi, .data = {0} };
  return v;
}
static inline M1Tk TkEq() {
  M1Tk v = { .tag = M1Tk_TkEq, .data = {0} };
  return v;
}
static inline M1Tk TkEqEq() {
  M1Tk v = { .tag = M1Tk_TkEqEq, .data = {0} };
  return v;
}
static inline M1Tk TkNeq() {
  M1Tk v = { .tag = M1Tk_TkNeq, .data = {0} };
  return v;
}
static inline M1Tk TkLt() {
  M1Tk v = { .tag = M1Tk_TkLt, .data = {0} };
  return v;
}
static inline M1Tk TkGt() {
  M1Tk v = { .tag = M1Tk_TkGt, .data = {0} };
  return v;
}
static inline M1Tk TkLe() {
  M1Tk v = { .tag = M1Tk_TkLe, .data = {0} };
  return v;
}
static inline M1Tk TkGe() {
  M1Tk v = { .tag = M1Tk_TkGe, .data = {0} };
  return v;
}
static inline M1Tk TkAnd() {
  M1Tk v = { .tag = M1Tk_TkAnd, .data = {0} };
  return v;
}
static inline M1Tk TkOr() {
  M1Tk v = { .tag = M1Tk_TkOr, .data = {0} };
  return v;
}
static inline M1Tk TkPipe() {
  M1Tk v = { .tag = M1Tk_TkPipe, .data = {0} };
  return v;
}
static inline M1Tk TkColon() {
  M1Tk v = { .tag = M1Tk_TkColon, .data = {0} };
  return v;
}
static inline M1Tk TkComma() {
  M1Tk v = { .tag = M1Tk_TkComma, .data = {0} };
  return v;
}
static inline M1Tk TkDot() {
  M1Tk v = { .tag = M1Tk_TkDot, .data = {0} };
  return v;
}
static inline M1Tk TkSemi() {
  M1Tk v = { .tag = M1Tk_TkSemi, .data = {0} };
  return v;
}
static inline M1Tk TkAt() {
  M1Tk v = { .tag = M1Tk_TkAt, .data = {0} };
  return v;
}
static inline M1Tk TkLBrace() {
  M1Tk v = { .tag = M1Tk_TkLBrace, .data = {0} };
  return v;
}
static inline M1Tk TkRBrace() {
  M1Tk v = { .tag = M1Tk_TkRBrace, .data = {0} };
  return v;
}
static inline M1Tk TkLParen() {
  M1Tk v = { .tag = M1Tk_TkLParen, .data = {0} };
  return v;
}
static inline M1Tk TkRParen() {
  M1Tk v = { .tag = M1Tk_TkRParen, .data = {0} };
  return v;
}
static inline M1Tk TkLBrack() {
  M1Tk v = { .tag = M1Tk_TkLBrack, .data = {0} };
  return v;
}
static inline M1Tk TkRBrack() {
  M1Tk v = { .tag = M1Tk_TkRBrack, .data = {0} };
  return v;
}
static inline M1Tk TkPlus() {
  M1Tk v = { .tag = M1Tk_TkPlus, .data = {0} };
  return v;
}
static inline M1Tk TkMinus() {
  M1Tk v = { .tag = M1Tk_TkMinus, .data = {0} };
  return v;
}
static inline M1Tk TkStar() {
  M1Tk v = { .tag = M1Tk_TkStar, .data = {0} };
  return v;
}
static inline M1Tk TkSlash() {
  M1Tk v = { .tag = M1Tk_TkSlash, .data = {0} };
  return v;
}
static inline M1Tk TkPercent() {
  M1Tk v = { .tag = M1Tk_TkPercent, .data = {0} };
  return v;
}
static inline M1Tk TkUnit() {
  M1Tk v = { .tag = M1Tk_TkUnit, .data = {0} };
  return v;
}
static inline M1Tk TkModule() {
  M1Tk v = { .tag = M1Tk_TkModule, .data = {0} };
  return v;
}
static inline M1Tk TkType() {
  M1Tk v = { .tag = M1Tk_TkType, .data = {0} };
  return v;
}
static inline M1Tk TkFn() {
  M1Tk v = { .tag = M1Tk_TkFn, .data = {0} };
  return v;
}
static inline M1Tk TkLet() {
  M1Tk v = { .tag = M1Tk_TkLet, .data = {0} };
  return v;
}
static inline M1Tk TkMatch() {
  M1Tk v = { .tag = M1Tk_TkMatch, .data = {0} };
  return v;
}
static inline M1Tk TkIf() {
  M1Tk v = { .tag = M1Tk_TkIf, .data = {0} };
  return v;
}
static inline M1Tk TkElse() {
  M1Tk v = { .tag = M1Tk_TkElse, .data = {0} };
  return v;
}
static inline M1Tk TkTrue() {
  M1Tk v = { .tag = M1Tk_TkTrue, .data = {0} };
  return v;
}
static inline M1Tk TkFalse() {
  M1Tk v = { .tag = M1Tk_TkFalse, .data = {0} };
  return v;
}
static inline M1Tk TkExternal() {
  M1Tk v = { .tag = M1Tk_TkExternal, .data = {0} };
  return v;
}
static inline M1Tk TkNot() {
  M1Tk v = { .tag = M1Tk_TkNot, .data = {0} };
  return v;
}
static inline M1Tk TkForall() {
  M1Tk v = { .tag = M1Tk_TkForall, .data = {0} };
  return v;
}
static inline M1Tk TkExists() {
  M1Tk v = { .tag = M1Tk_TkExists, .data = {0} };
  return v;
}
static inline M1Tk TkMut() {
  M1Tk v = { .tag = M1Tk_TkMut, .data = {0} };
  return v;
}
static inline M1Tk TkWhile() {
  M1Tk v = { .tag = M1Tk_TkWhile, .data = {0} };
  return v;
}
static inline M1Tk TkFreeze() {
  M1Tk v = { .tag = M1Tk_TkFreeze, .data = {0} };
  return v;
}
static inline M1Tk TkNow() {
  M1Tk v = { .tag = M1Tk_TkNow, .data = {0} };
  return v;
}
static inline M1Tk TkWwas() {
  M1Tk v = { .tag = M1Tk_TkWwas, .data = {0} };
  return v;
}
static inline M1Tk TkWhen() {
  M1Tk v = { .tag = M1Tk_TkWhen, .data = {0} };
  return v;
}
static inline M1Tk TkWill() {
  M1Tk v = { .tag = M1Tk_TkWill, .data = {0} };
  return v;
}
static inline M1Tk TkWorld() {
  M1Tk v = { .tag = M1Tk_TkWorld, .data = {0} };
  return v;
}
static inline M1Tk TkDo() {
  M1Tk v = { .tag = M1Tk_TkDo, .data = {0} };
  return v;
}
static inline M1Tk TkSet() {
  M1Tk v = { .tag = M1Tk_TkSet, .data = {0} };
  return v;
}
static inline M1Tk TkPick() {
  M1Tk v = { .tag = M1Tk_TkPick, .data = {0} };
  return v;
}
static inline M1Tk TkShape() {
  M1Tk v = { .tag = M1Tk_TkShape, .data = {0} };
  return v;
}
static inline M1Tk TkLive() {
  M1Tk v = { .tag = M1Tk_TkLive, .data = {0} };
  return v;
}
static inline M1Tk TkSay() {
  M1Tk v = { .tag = M1Tk_TkSay, .data = {0} };
  return v;
}
static inline M1Tk TkShow() {
  M1Tk v = { .tag = M1Tk_TkShow, .data = {0} };
  return v;
}
static inline M1Tk TkThen() {
  M1Tk v = { .tag = M1Tk_TkThen, .data = {0} };
  return v;
}
static inline M1Tk TkRequires() {
  M1Tk v = { .tag = M1Tk_TkRequires, .data = {0} };
  return v;
}
static inline M1Tk TkEnsures() {
  M1Tk v = { .tag = M1Tk_TkEnsures, .data = {0} };
  return v;
}
M1Token mk_tok(M1Tk kind, int64_t line, int64_t col);
M1Token mk_int_tok(int64_t val, int64_t line, int64_t col);
M1Token mk_str_tok(M1Tk kind, char* val, int64_t line, int64_t col);
int64_t peek(M1Lexer l);
int64_t peek_at(M1Lexer l, int64_t offset);
M1Lexer advance(M1Lexer l);
M1Lexer advance_n(M1Lexer l, int64_t n);
int is_space(int64_t c);
int is_alpha(int64_t c);
int is_digit(int64_t c);
int is_alnum(int64_t c);
M1Lexer skip_line(M1Lexer l);
M1Lexer skip_block(M1Lexer l, int64_t depth);
M1Lexer skip_ws(M1Lexer l);
M1Token keyword_or_ident(char* s, int64_t line, int64_t col);
M1LexResult scan_ident(M1Lexer l, int64_t start, int64_t line, int64_t col);
int64_t parse_int_rec(char* s, int64_t i, int64_t len, int64_t acc);
int64_t parse_int(char* s);
M1LexResult scan_float(M1Lexer l, int64_t start, int64_t line, int64_t col);
M1LexResult scan_int(M1Lexer l, int64_t start, int64_t line, int64_t col);
M1LexResult scan_string(M1Lexer l, int64_t start, int64_t line, int64_t col);
M1LexResult scan_char(M1Lexer l, int64_t line, int64_t col);
M1Lexer m1_lexer_init(char* src);
M1LexResult m1_lexer_next(M1Lexer l);
char* tk_name(M1Tk k);
int64_t print_token_value(M1Token t);
int64_t print_tokens(M1Lexer l);
int64_t lexer_demo();
M1Token mk_tok(M1Tk kind, int64_t line, int64_t col) {
return (M1Token){kind, line, col, 0, ""};}
M1Token mk_int_tok(int64_t val, int64_t line, int64_t col) {
return (M1Token){TkInt(), line, col, val, ""};}
M1Token mk_str_tok(M1Tk kind, char* val, int64_t line, int64_t col) {
return (M1Token){kind, line, col, 0, val};}
int64_t peek(M1Lexer l) {
return m0_char_at((l).src, (l).pos);}
int64_t peek_at(M1Lexer l, int64_t offset) {
return m0_char_at((l).src, ((l).pos + offset));}
M1Lexer advance(M1Lexer l) {
  int64_t c = 
peek(l);  (void)c;
  if 
(c == 10) {    
    return (M1Lexer){(l).src, ((l).pos + 1), ((l).line + 1), 1};  
  } else {    
    return (M1Lexer){(l).src, ((l).pos + 1), (l).line, ((l).col + 1)};  
  }}
M1Lexer advance_n(M1Lexer l, int64_t n) {
  if 
(n <= 0) {    
    return l;  
  } else {    
    return advance_n(advance(l), (n - 1));  
  }}
int is_space(int64_t c) {
return ((((c == 32) || (c == 9)) || (c == 10)) || (c == 13));}
int is_alpha(int64_t c) {
return ((((c >= 65) && (c <= 90)) || ((c >= 97) && (c <= 122))) || (c == 95));}
int is_digit(int64_t c) {
return ((c >= 48) && (c <= 57));}
int is_alnum(int64_t c) {
return (is_alpha(c) || is_digit(c));}
M1Lexer skip_line(M1Lexer l) {
  int64_t c = 
peek(l);  (void)c;
  if 
(c == -1) {    
    return l;  
  } else {    
        if 
(c == 10) {      
      return l;    
    } else {      
      return skip_line(advance(l));    
    }  
  }}
M1Lexer skip_block(M1Lexer l, int64_t depth) {
  if 
(depth == 0) {    
    return l;  
  } else {    
        int64_t c = 
peek(l);    (void)c;
    if 
(c == -1) {      
      return l;    
    } else {      
            if 
((c == 123) && (peek_at(l, 1) == 45)) {        
        return skip_block(advance_n(l, 2), (depth + 1));      
      } else {        
                if 
((c == 45) && (peek_at(l, 1) == 125)) {          
          return skip_block(advance_n(l, 2), (depth - 1));        
        } else {          
          return skip_block(advance(l), depth);        
        }      
      }    
    }  
  }}
M1Lexer skip_ws(M1Lexer l) {
  int64_t c = 
peek(l);  (void)c;
  if 
(c == -1) {    
    return l;  
  } else {    
        if (
is_space(c)) {      
      return skip_ws(advance(l));    
    } else {      
            if 
((c == 45) && (peek_at(l, 1) == 45)) {        
        return skip_ws(skip_line(advance_n(l, 2)));      
      } else {        
                if 
((c == 123) && (peek_at(l, 1) == 45)) {          
          return skip_ws(skip_block(advance_n(l, 2), 1));        
        } else {          
          return l;        
        }      
      }    
    }  
  }}
M1Token keyword_or_ident(char* s, int64_t line, int64_t col) {
  if 
(m0_string_eq(s, "module") == 1) {    
    return mk_str_tok(TkModule(), s, line, col);  
  } else {    
        if 
(m0_string_eq(s, "type") == 1) {      
      return mk_str_tok(TkType(), s, line, col);    
    } else {      
            if 
(m0_string_eq(s, "fn") == 1) {        
        return mk_str_tok(TkFn(), s, line, col);      
      } else {        
                if 
(m0_string_eq(s, "let") == 1) {          
          return mk_str_tok(TkLet(), s, line, col);        
        } else {          
                    if 
(m0_string_eq(s, "match") == 1) {            
            return mk_str_tok(TkMatch(), s, line, col);          
          } else {            
                        if 
(m0_string_eq(s, "if") == 1) {              
              return mk_str_tok(TkIf(), s, line, col);            
            } else {              
                            if 
(m0_string_eq(s, "else") == 1) {                
                return mk_str_tok(TkElse(), s, line, col);              
              } else {                
                                if 
(m0_string_eq(s, "true") == 1) {                  
                  return mk_str_tok(TkTrue(), s, line, col);                
                } else {                  
                                    if 
(m0_string_eq(s, "false") == 1) {                    
                    return mk_str_tok(TkFalse(), s, line, col);                  
                  } else {                    
                                        if 
(m0_string_eq(s, "external") == 1) {                      
                      return mk_str_tok(TkExternal(), s, line, col);                    
                    } else {                      
                                            if 
(m0_string_eq(s, "not") == 1) {                        
                        return mk_str_tok(TkNot(), s, line, col);                      
                      } else {                        
                                                if 
(m0_string_eq(s, "forall") == 1) {                          
                          return mk_str_tok(TkForall(), s, line, col);                        
                        } else {                          
                                                    if 
(m0_string_eq(s, "exists") == 1) {                            
                            return mk_str_tok(TkExists(), s, line, col);                          
                          } else {                            
                                                        if 
(m0_string_eq(s, "mut") == 1) {                              
                              return mk_str_tok(TkMut(), s, line, col);                            
                            } else {                              
                                                            if 
(m0_string_eq(s, "while") == 1) {                                
                                return mk_str_tok(TkWhile(), s, line, col);                              
                              } else {                                
                                                                if 
(m0_string_eq(s, "freeze") == 1) {                                  
                                  return mk_str_tok(TkFreeze(), s, line, col);                                
                                } else {                                  
                                                                    if 
(m0_string_eq(s, "now") == 1) {                                    
                                    return mk_str_tok(TkNow(), s, line, col);                                  
                                  } else {                                    
                                                                        if 
(m0_string_eq(s, "was") == 1) {                                      
                                      return mk_str_tok(TkWwas(), s, line, col);                                    
                                    } else {                                      
                                                                            if 
(m0_string_eq(s, "when") == 1) {                                        
                                        return mk_str_tok(TkWhen(), s, line, col);                                      
                                      } else {                                        
                                                                                if 
(m0_string_eq(s, "will") == 1) {                                          
                                          return mk_str_tok(TkWill(), s, line, col);                                        
                                        } else {                                          
                                                                                    if 
(m0_string_eq(s, "world") == 1) {                                            
                                            return mk_str_tok(TkWorld(), s, line, col);                                          
                                          } else {                                            
                                                                                        if 
(m0_string_eq(s, "do") == 1) {                                              
                                              return mk_str_tok(TkDo(), s, line, col);                                            
                                            } else {                                              
                                                                                            if 
(m0_string_eq(s, "set") == 1) {                                                
                                                return mk_str_tok(TkSet(), s, line, col);                                              
                                              } else {                                                
                                                                                                if 
(m0_string_eq(s, "pick") == 1) {                                                  
                                                  return mk_str_tok(TkPick(), s, line, col);                                                
                                                } else {                                                  
                                                                                                    if 
(m0_string_eq(s, "shape") == 1) {                                                    
                                                    return mk_str_tok(TkShape(), s, line, col);                                                  
                                                  } else {                                                    
                                                                                                        if 
(m0_string_eq(s, "live") == 1) {                                                      
                                                      return mk_str_tok(TkLive(), s, line, col);                                                    
                                                    } else {                                                      
                                                                                                            if 
(m0_string_eq(s, "say") == 1) {                                                        
                                                        return mk_str_tok(TkSay(), s, line, col);                                                      
                                                      } else {                                                        
                                                                                                                if 
(m0_string_eq(s, "show") == 1) {                                                          
                                                          return mk_str_tok(TkShow(), s, line, col);                                                        
                                                        } else {                                                          
                                                                                                                    if 
(m0_string_eq(s, "then") == 1) {                                                            
                                                             return mk_str_tok(TkThen(), s, line, col);                                                          
                                                           } else {                                                            
                                                                                                                         if 
(m0_string_eq(s, "requires") == 1) {                                                              
                                                                   return mk_str_tok(TkRequires(), s, line, col);                                                            
                                                                 } else {                                                                
                                                                                                                                     if 
(m0_string_eq(s, "ensures") == 1) {                                                                      
                                                                       return mk_str_tok(TkEnsures(), s, line, col);                                                                    
                                                                     } else {                                                                      
                                                             return mk_str_tok(TkIdent(), s, line, col);                                                          
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
          }        
        }      
      }    
    }  
  }}
M1LexResult scan_ident(M1Lexer l, int64_t start, int64_t line, int64_t col) {
  int64_t c = 
peek(l);  (void)c;
  if (
is_alnum(c)) {    
    return scan_ident(advance(l), start, line, col);  
  } else {    
        char *s = 
m0_substr((l).src, start, (l).pos);    (void)s;
    if 
((m0_string_eq(s, "Int") == 1) && (m0_char_at((l).src, (start - 1)) != 40)) {      
      return (M1LexResult){mk_str_tok(TkInt(), s, line, col), l};    
    } else {      
      return (M1LexResult){keyword_or_ident(s, line, col), l};    
    }  
  }}
int64_t parse_int_rec(char* s, int64_t i, int64_t len, int64_t acc) {
  if 
(i >= len) {    
    return acc;  
  } else {    
        int64_t c = 
m0_char_at(s, i);    (void)c;
return parse_int_rec(s, (i + 1), len, ((acc * 10) + (c - 48)));  
  }}
int64_t parse_int(char* s) {
return parse_int_rec(s, 0, m0_string_len(s), 0);}
M1LexResult scan_float(M1Lexer l, int64_t start, int64_t line, int64_t col) {
  int64_t c = 
peek(l);  (void)c;
  if (
is_digit(c)) {    
    return scan_float(advance(l), start, line, col);  
  } else {    
        char *s = 
m0_substr((l).src, start, (l).pos);    (void)s;
return (M1LexResult){mk_str_tok(TkFloat(), s, line, col), l};  
  }}
M1LexResult scan_int(M1Lexer l, int64_t start, int64_t line, int64_t col) {
  int64_t c = 
peek(l);  (void)c;
  if (
is_digit(c)) {    
    return scan_int(advance(l), start, line, col);  
  } else {    
        if 
((c == 46) && is_digit(peek_at(l, 1))) {      
      return scan_float(advance(l), start, line, col);    
    } else {      
            char *s = 
m0_substr((l).src, start, (l).pos);      (void)s;
      int64_t v = 
parse_int(s);      (void)v;
return (M1LexResult){mk_int_tok(v, line, col), l};    
    }  
  }}
M1LexResult scan_string(M1Lexer l, int64_t start, int64_t line, int64_t col) {
  int64_t c = 
peek(l);  (void)c;
  if 
(c == 34) {    
        char *s = 
m0_substr((l).src, start, (l).pos);    (void)s;
return (M1LexResult){mk_str_tok(TkString(), s, line, col), advance(l)};  
  } else {    
        if 
(c == -1) {      
            char *s = 
m0_substr((l).src, start, (l).pos);      (void)s;
return (M1LexResult){mk_str_tok(TkString(), s, line, col), l};    
    } else {      
            if 
(c == 92) {        
        return scan_string(advance_n(l, 2), start, line, col);      
      } else {        
        return scan_string(advance(l), start, line, col);      
      }    
    }  
  }}
M1LexResult scan_char(M1Lexer l, int64_t line, int64_t col) {
  int64_t v = 
peek_at(l, 1);  (void)v;
  if 
(v == 92) {    
        int64_t e = 
peek_at(l, 2);    (void)e;
    if 
(e == 110) {      
      return (M1LexResult){mk_int_tok(10, line, col), advance_n(l, 4)};    
    } else {      
            if 
(e == 116) {        
        return (M1LexResult){mk_int_tok(9, line, col), advance_n(l, 4)};      
      } else {        
        return (M1LexResult){mk_int_tok(e, line, col), advance_n(l, 4)};      
      }    
    }  
  } else {    
    return (M1LexResult){{TkChar(), line, col, v, ""}, advance_n(l, 3)};  
  }}
M1Lexer m1_lexer_init(char* src) {
return (M1Lexer){src, 0, 1, 1};}
M1LexResult m1_lexer_next(M1Lexer l) {
  M1Lexer l2 = skip_ws(l);  (void)l2;
  int64_t c = 
peek(l2);  (void)c;
  int64_t line = 
(l2).line;  (void)line;
  int64_t col = 
(l2).col;  (void)col;
  if 
(c == -1) {    
    return (M1LexResult){mk_tok(TkEof(), line, col), l2};  
  } else {    
        if 
((c == 40) && (peek_at(l2, 1) == 41)) {      
      return (M1LexResult){mk_tok(TkUnit(), line, col), advance_n(l2, 2)};    
    } else {      
            if 
(c == 34) {        
        return scan_string(advance(l2), ((l2).pos + 1), line, col);      
      } else {        
                if 
(c == 39) {          
          return scan_char(l2, line, col);        
        } else {          
                    if (
is_digit(c)) {            
            return scan_int(l2, (l2).pos, line, col);          
          } else {            
                        if (
is_alpha(c)) {              
              return scan_ident(l2, (l2).pos, line, col);            
            } else {              
                            if 
(((c == 60) && (peek_at(l2, 1) == 45)) && (peek_at(l2, 2) == 62)) {                
                return (M1LexResult){mk_tok(TkBidi(), line, col), advance_n(l2, 3)};              
              } else {                
                                if 
((c == 60) && (peek_at(l2, 1) == 45)) {                  
                  return (M1LexResult){mk_tok(TkLArrow(), line, col), advance_n(l2, 2)};                
                } else {                  
                                    if 
((c == 45) && (peek_at(l2, 1) == 62)) {                    
                    return (M1LexResult){mk_tok(TkArrow(), line, col), advance_n(l2, 2)};                  
                  } else {                    
                                        if 
((c == 60) && (peek_at(l2, 1) == 61)) {                      
                      return (M1LexResult){mk_tok(TkLe(), line, col), advance_n(l2, 2)};                    
                    } else {                      
                                            if 
((c == 62) && (peek_at(l2, 1) == 61)) {                        
                        return (M1LexResult){mk_tok(TkGe(), line, col), advance_n(l2, 2)};                      
                      } else {                        
                                                if 
((c == 61) && (peek_at(l2, 1) == 61)) {                          
                          return (M1LexResult){mk_tok(TkEqEq(), line, col), advance_n(l2, 2)};                        
                        } else {                          
                                                    if 
((c == 33) && (peek_at(l2, 1) == 61)) {                            
                            return (M1LexResult){mk_tok(TkNeq(), line, col), advance_n(l2, 2)};                          
                          } else {                            
                                                        if 
((c == 47) && (peek_at(l2, 1) == 92)) {                              
                              return (M1LexResult){mk_tok(TkAnd(), line, col), advance_n(l2, 2)};                            
                            } else {                              
                                                            if 
((c == 92) && (peek_at(l2, 1) == 47)) {                                
                                return (M1LexResult){mk_tok(TkOr(), line, col), advance_n(l2, 2)};                              
                              } else {                                
                                                                if 
(c == 60) {                                  
                                  return (M1LexResult){mk_tok(TkLt(), line, col), advance(l2)};                                
                                } else {                                  
                                                                    if 
(c == 62) {                                    
                                    return (M1LexResult){mk_tok(TkGt(), line, col), advance(l2)};                                  
                                  } else {                                    
                                                                        if 
(c == 61) {                                      
                                      return (M1LexResult){mk_tok(TkEq(), line, col), advance(l2)};                                    
                                    } else {                                      
                                                                            if 
(c == 124) {                                        
                                        return (M1LexResult){mk_tok(TkPipe(), line, col), advance(l2)};                                      
                                      } else {                                        
                                                                                if 
(c == 58) {                                          
                                          return (M1LexResult){mk_tok(TkColon(), line, col), advance(l2)};                                        
                                        } else {                                          
                                                                                    if 
(c == 44) {                                            
                                            return (M1LexResult){mk_tok(TkComma(), line, col), advance(l2)};                                          
                                          } else {                                            
                                                                                        if 
(c == 46) {                                              
                                              return (M1LexResult){mk_tok(TkDot(), line, col), advance(l2)};                                            
                                            } else {                                              
                                                                                            if 
(c == 59) {                                                
                                                return (M1LexResult){mk_tok(TkSemi(), line, col), advance(l2)};                                              
                                              } else {                                                
                                                                                                if 
(c == 64) {                                                  
                                                  return (M1LexResult){mk_tok(TkAt(), line, col), advance(l2)};                                                
                                                } else {                                                  
                                                                                                    if 
(c == 123) {                                                    
                                                    return (M1LexResult){mk_tok(TkLBrace(), line, col), advance(l2)};                                                  
                                                  } else {                                                    
                                                                                                        if 
(c == 125) {                                                      
                                                      return (M1LexResult){mk_tok(TkRBrace(), line, col), advance(l2)};                                                    
                                                    } else {                                                      
                                                                                                            if 
(c == 40) {                                                        
                                                        return (M1LexResult){mk_tok(TkLParen(), line, col), advance(l2)};                                                      
                                                      } else {                                                        
                                                                                                                if 
(c == 41) {                                                          
                                                          return (M1LexResult){mk_tok(TkRParen(), line, col), advance(l2)};                                                        
                                                        } else {                                                          
                                                                                                                    if 
(c == 91) {                                                            
                                                            return (M1LexResult){mk_tok(TkLBrack(), line, col), advance(l2)};                                                          
                                                          } else {                                                            
                                                                                                                        if 
(c == 93) {                                                              
                                                              return (M1LexResult){mk_tok(TkRBrack(), line, col), advance(l2)};                                                            
                                                            } else {                                                              
                                                                                                                            if 
(c == 43) {                                                                
                                                                return (M1LexResult){mk_tok(TkPlus(), line, col), advance(l2)};                                                              
                                                              } else {                                                                
                                                                                                                                if 
(c == 45) {                                                                  
                                                                  return (M1LexResult){mk_tok(TkMinus(), line, col), advance(l2)};                                                                
                                                                } else {                                                                  
                                                                                                                                    if 
(c == 42) {                                                                    
                                                                    return (M1LexResult){mk_tok(TkStar(), line, col), advance(l2)};                                                                  
                                                                  } else {                                                                    
                                                                                                                                        if 
(c == 47) {                                                                      
                                                                      return (M1LexResult){mk_tok(TkSlash(), line, col), advance(l2)};                                                                    
                                                                    } else {                                                                      
                                                                                                                                            if 
(c == 37) {                                                                        
                                                                        return (M1LexResult){mk_tok(TkPercent(), line, col), advance(l2)};                                                                      
                                                                      } else {                                                                        
                                                                        return (M1LexResult){mk_tok(TkEof(), line, col), advance(l2)};                                                                      
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
                  }                
                }              
              }            
            }          
          }        
        }      
      }    
    }  
  }}
char* tk_name(M1Tk k) {
    switch (
k.tag) {      case M1Tk_TkEof: {
        return "EOF";      
      }
      case M1Tk_TkInt: {
        return "INT";      
      }
      case M1Tk_TkFloat: {
        return "FLOAT";      
      }
      case M1Tk_TkString: {
        return "STRING";      
      }
      case M1Tk_TkChar: {
        return "CHAR";      
      }
      case M1Tk_TkIdent: {
        return "IDENT";      
      }
      case M1Tk_TkArrow: {
        return "ARROW";      
      }
      case M1Tk_TkLArrow: {
        return "LARROW";      
      }
      case M1Tk_TkBidi: {
        return "BIDI";      
      }
      case M1Tk_TkEq: {
        return "EQ";      
      }
      case M1Tk_TkEqEq: {
        return "EQEQ";      
      }
      case M1Tk_TkNeq: {
        return "NEQ";      
      }
      case M1Tk_TkLt: {
        return "LT";      
      }
      case M1Tk_TkGt: {
        return "GT";      
      }
      case M1Tk_TkLe: {
        return "LE";      
      }
      case M1Tk_TkGe: {
        return "GE";      
      }
      case M1Tk_TkAnd: {
        return "AND";      
      }
      case M1Tk_TkOr: {
        return "OR";      
      }
      case M1Tk_TkPipe: {
        return "PIPE";      
      }
      case M1Tk_TkColon: {
        return "COLON";      
      }
      case M1Tk_TkComma: {
        return "COMMA";      
      }
      case M1Tk_TkDot: {
        return "DOT";      
      }
      case M1Tk_TkSemi: {
        return "SEMI";      
      }
      case M1Tk_TkAt: {
        return "AT";      
      }
      case M1Tk_TkLBrace: {
        return "LBRACE";      
      }
      case M1Tk_TkRBrace: {
        return "RBRACE";      
      }
      case M1Tk_TkLParen: {
        return "LPAREN";      
      }
      case M1Tk_TkRParen: {
        return "RPAREN";      
      }
      case M1Tk_TkLBrack: {
        return "LBRACK";      
      }
      case M1Tk_TkRBrack: {
        return "RBRACK";      
      }
      case M1Tk_TkPlus: {
        return "PLUS";      
      }
      case M1Tk_TkMinus: {
        return "MINUS";      
      }
      case M1Tk_TkStar: {
        return "STAR";      
      }
      case M1Tk_TkSlash: {
        return "SLASH";      
      }
      case M1Tk_TkPercent: {
        return "PERCENT";      
      }
      case M1Tk_TkUnit: {
        return "UNIT";      
      }
      case M1Tk_TkModule: {
        return "MODULE";      
      }
      case M1Tk_TkType: {
        return "TYPE";      
      }
      case M1Tk_TkFn: {
        return "FN";      
      }
      case M1Tk_TkLet: {
        return "LET";      
      }
      case M1Tk_TkMatch: {
        return "MATCH";      
      }
      case M1Tk_TkIf: {
        return "IF";      
      }
      case M1Tk_TkElse: {
        return "ELSE";      
      }
      case M1Tk_TkTrue: {
        return "TRUE";      
      }
      case M1Tk_TkFalse: {
        return "FALSE";      
      }
      case M1Tk_TkExternal: {
        return "EXTERNAL";      
      }
      case M1Tk_TkNot: {
        return "NOT";      
      }
      case M1Tk_TkForall: {
        return "FORALL";      
      }
      case M1Tk_TkExists: {
        return "EXISTS";      
      }
      case M1Tk_TkMut: {
        return "MUT";      
      }
      case M1Tk_TkWhile: {
        return "WHILE";      
      }
      case M1Tk_TkFreeze: {
        return "FREEZE";      
      }
      case M1Tk_TkNow: {
        return "NOW";      
      }
      case M1Tk_TkWwas: {
        return "WAS";      
      }
      case M1Tk_TkWhen: {
        return "WHEN";      
      }
      case M1Tk_TkWill: {
        return "WILL";      
      }
      case M1Tk_TkWorld: {
        return "WORLD";      
      }
      case M1Tk_TkDo: {
        return "DO";      
      }
      case M1Tk_TkSet: {
        return "SET";      
      }
      case M1Tk_TkPick: {
        return "PICK";      
      }
      case M1Tk_TkShape: {
        return "SHAPE";      
      }
      case M1Tk_TkLive: {
        return "LIVE";      
      }
      case M1Tk_TkSay: {
        return "SAY";      
      }
      case M1Tk_TkShow: {
        return "SHOW";      
      }
      case M1Tk_TkThen: {
        return "THEN";      
      }
      case M1Tk_TkRequires: {
        return "REQUIRES";      
      }
      case M1Tk_TkEnsures: {
        return "ENSURES";      
      }
      default: { return 0; }
    }
}
int64_t print_token_value(M1Token t) {
    switch (
(t).kind.tag) {      case M1Tk_TkIdent: {
                int64_t p1 = 
m0_print(" ");        (void)p1;
return m0_print((t).str_val);      
      }
      case M1Tk_TkInt: {
                if 
(m0_string_len((t).str_val) > 0) {          
                    int64_t p2 = 
m0_print(" ");          (void)p2;
return m0_print((t).str_val);        
        } else {          
                    int64_t p3 = 
m0_print(" ");          (void)p3;
return m0_print_int((t).int_val);        
        }      
      }
      case M1Tk_TkFloat: {
                int64_t p4 = 
m0_print(" ");        (void)p4;
return m0_print((t).str_val);      
      }
      case M1Tk_TkString: {
                int64_t p5 = 
m0_print(" ");        (void)p5;
return m0_print((t).str_val);      
      }
      case M1Tk_TkChar: {
                int64_t p6 = 
m0_print(" ");        (void)p6;
return m0_print_char((t).int_val);      
      }
      default: {
        return 0;      }
    }
}
int64_t print_tokens(M1Lexer l) {
  M1LexResult r = m1_lexer_next(l);  (void)r;
  int64_t p1 = 
m0_print(tk_name(((r).token).kind));  (void)p1;
  int64_t p2 = 
print_token_value((r).token);  (void)p2;
  int64_t p3 = 
m0_print("\n");  (void)p3;
    switch (
((r).token).kind.tag) {      case M1Tk_TkEof: {
        return 0;      
      }
      default: {
        return print_tokens((r).lexer);      }
    }
}
int64_t lexer_demo() {
return print_tokens(m1_lexer_init("module Test {\n    forall x : Int -> x\n    exists y : Bool /\\ y\n    Linear(Int)\n    [IO] Unit\n    x <-> y\n}"));}
