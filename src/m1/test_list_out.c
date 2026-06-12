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

/* Module: ListTest */
extern int64_t m0_cons(int64_t, int64_t);
extern int64_t m0_nil(int64_t);
extern int64_t m0_head(int64_t);
extern int64_t m0_tail(int64_t);
extern int64_t m0_is_nil(int64_t);
extern int64_t m0_list_length(int64_t);
extern int64_t m0_alloc(int64_t);
extern int64_t m0_set(int64_t, int64_t, int64_t);
extern int64_t m0_get(int64_t, int64_t);
extern int64_t m0_print(char*);
extern int64_t m0_print_int(int64_t);
int64_t build(int64_t n) {
  if 
(n <= 0) {    
    return m0_nil(0);  
  } else {    
    return m0_cons(n, build((n - 1)));  
  }}
int64_t sum(int64_t list) {
  if 
(m0_is_nil(list) == 1) {    
    return 0;  
  } else {    
    return (m0_head(list) + sum(m0_tail(list)));  
  }}
int64_t test_node() {
  int64_t n = 
m0_alloc(3);  (void)n;
  int64_t s0 = 
m0_set(n, 0, 10);  (void)s0;
  int64_t s1 = 
m0_set(n, 1, 20);  (void)s1;
  int64_t s2 = 
m0_set(n, 2, 30);  (void)s2;
return ((m0_get(n, 0) + m0_get(n, 1)) + m0_get(n, 2));}
int main() {
  int64_t l = 
build(10);  (void)l;
  int64_t s = 
sum(l);  (void)s;
  int64_t len = 
m0_list_length(l);  (void)len;
  int64_t n = 
test_node();  (void)n;
return ((s + len) + n);}
