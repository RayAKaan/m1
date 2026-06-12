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

/* Module: M1Codegen */
extern int64_t m0_print(char*);
extern int64_t m0_alloc(int64_t);
extern int64_t m0_set(int64_t, int64_t, int64_t);
extern int64_t m0_get(int64_t, int64_t);
extern int64_t m0_store_string(int64_t, int64_t, char*);
extern char* m0_load_string(int64_t, int64_t);
int64_t store_line(char* text) {
  int64_t n = 
m0_alloc(1);  (void)n;
  int64_t s = 
m0_store_string(n, 0, text);  (void)s;
  int64_t p = 
m0_print(m0_load_string(n, 0));  (void)p;
return p;}
int main() {
  int64_t n = 
m0_alloc(2);  (void)n;
  int64_t s0 = 
m0_set(n, 0, 3);  (void)s0;
  int64_t s1 = 
m0_set(n, 1, 7);  (void)s1;
  int64_t keep = 
(m0_get(n, 0) + m0_get(n, 1));  (void)keep;
  int64_t l01 = 
store_line("#include <stdint.h>\n");  (void)l01;
  int64_t l02 = 
store_line("\n");  (void)l02;
  int64_t l03 = 
store_line("typedef struct { int64_t first; int64_t second; } Pair;\n");  (void)l03;
  int64_t l04 = 
store_line("\n");  (void)l04;
  int64_t l05 = 
store_line("\n");  (void)l05;
  int64_t l06 = 
store_line("int64_t add(int64_t a, int64_t b) {\n");  (void)l06;
  int64_t l07 = 
store_line("  return (a + b);\n");  (void)l07;
  int64_t l08 = 
store_line("}\n");  (void)l08;
  int64_t l09 = 
store_line("Pair make_pair(int64_t a, int64_t b) {\n");  (void)l09;
  int64_t l10 = 
store_line("  return (Pair){ .first = a, .second = b };\n");  (void)l10;
  int64_t l11 = 
store_line("}\n");  (void)l11;
  int64_t l12 = 
store_line("int main(void) {\n");  (void)l12;
  int64_t l13 = 
store_line("  return make_pair(3, 7).first;\n");  (void)l13;
  int64_t l14 = 
store_line("}\n");  (void)l14;
return 0;}
