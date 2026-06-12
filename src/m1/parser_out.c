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

/* Module: M1Parser */
extern int64_t m0_alloc(int64_t);
extern int64_t m0_set(int64_t, int64_t, int64_t);
extern int64_t m0_get(int64_t, int64_t);
extern int64_t m0_store_string(int64_t, int64_t, char*);
extern char* m0_load_string(int64_t, int64_t);
extern int64_t m0_print(char*);
extern int64_t m1_lexer_init(char*);
extern int64_t m1_lexer_next(int64_t);
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
int64_t store_line(char* text) {
  int64_t n = 
m0_alloc(1);  (void)n;
  int64_t s = 
m0_store_string(n, 0, text);  (void)s;
  int64_t p = 
m0_print(m0_load_string(n, 0));  (void)p;
return p;}
int main() {
  int64_t l01 = 
store_line("module Test {\n");  (void)l01;
  int64_t l02 = 
store_line("  type Pair = { first: Int, second: Int }\n");  (void)l02;
  int64_t l03 = 
store_line("  type Option = | Some(Int) | None\n");  (void)l03;
  int64_t l04 = 
store_line("  fn add(a: Int, b: Int) -> Int { (a + b) }\n");  (void)l04;
  int64_t l05 = 
store_line("  fn first_of(p: Pair) -> Int { p.first }\n");  (void)l05;
  int64_t l06 = 
store_line("  let x : Int = 42; x\n");  (void)l06;
  int64_t l07 = 
store_line("  y : Int <- add(x, x)\n");  (void)l07;
  int64_t l08 = 
store_line("  forall z : Int -> (z > 0)\n");  (void)l08;
  int64_t l09 = 
store_line("  exists w : Int -> (w == w)\n");  (void)l09;
  int64_t l10 = 
store_line("  a : Int <-> b\n");  (void)l10;
  int64_t l11 = 
store_line("  external \"puts\" : String -> Int\n");  (void)l11;
  int64_t l12 = 
store_line("  fn test(v: Int) -> Int { match v { 0 -> 1; _ -> v; } }\n");  (void)l12;
  int64_t l13 = 
store_line("  fn abs(v: Int) -> Int { if (v < 0) { 0 - v } else { v } }\n");  (void)l13;
  int64_t l14 = 
store_line("}\n");  (void)l14;
return (((((((((((((l01 + l02) + l03) + l04) + l05) + l06) + l07) + l08) + l09) + l10) + l11) + l12) + l13) + l14);}
