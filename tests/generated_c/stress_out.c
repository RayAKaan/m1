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

/* Module: Stress */
extern int64_t printf(char*);
extern int64_t putchar(int64_t);
typedef struct Option Option;
struct Option {
  int tag;
  union {
    struct {
      int64_t f0;      
    } Some;    
    char _unused[1];
    } data;
};
enum Option_tag {
  Option_Some,
  Option_None
};
typedef struct {
  int64_t first;  
  int64_t second;  
} Pair;
static inline Option Some(int64_t x0) {
  Option v = { .tag = Option_Some, .data.Some = {.f0 = x0} };  
  return v;
}
static inline Option None() {
  Option v = { .tag = Option_None, .data = {0} };
  return v;
}
Option some_val() {
return Some(42);}
Option none_val() {
return None();}
int64_t unwrap_or(Option o, int64_t def) {
    switch (
o.tag) {      case Option_Some: {
        int64_t v = o.data.Some.f0;        
        return v;      
      }
      case Option_None: {
        return def;      
      }
      default: { return 0; }
    }
}
int64_t fib(int64_t n) {
  if (
(n < 2)) {    
    return n;  
  } else {    
    return (fib((n - 1)) + fib((n - 2)));  
  }}
int64_t fact(int64_t n) {
  if (
(n < 1)) {    
    return 1;  
  } else {    
    return (n * fact((n - 1)));  
  }}
Pair make_pair(int64_t a, int64_t b) {
return (Pair){a, b};}
int64_t pair_sum(Pair p) {
return ((p).first + (p).second);}
Pair swap_pair(Pair p) {
return (Pair){(p).second, (p).first};}
int64_t gcd(int64_t a, int64_t b) {
  if (
(b == 0)) {    
    return a;  
  } else {    
    return gcd(b, (a - ((a / b) * b)));  
  }}
int64_t max(int64_t a, int64_t b) {
  if (
(a > b)) {    
    return a;  
  } else {    
    return b;  
  }}
int64_t min(int64_t a, int64_t b) {
  if (
(a < b)) {    
    return a;  
  } else {    
    return b;  
  }}
int64_t clamp(int64_t v, int64_t lo, int64_t hi) {
return max(lo, min(v, hi));}
int64_t count_down(int64_t n) {
  if (
(n == 0)) {    
    return 0;  
  } else {    
    return (n + count_down((n - 1)));  
  }}
int64_t power(int64_t base, int64_t exp) {
  if (
(exp == 0)) {    
    return 1;  
  } else {    
    return (base * power(base, (exp - 1)));  
  }}
int64_t ack(int64_t m, int64_t n) {
  if (
(m == 0)) {    
    return (n + 1);  
  } else {    
        if (
(n == 0)) {      
      return ack((m - 1), 1);    
    } else {      
      return ack((m - 1), ack(m, (n - 1)));    
    };  
  }}
int main() {
  int64_t a = 
fib(10);  int64_t b = 
fact(10);  int64_t c = 
unwrap_or(some_val(), 0);  int64_t d = 
unwrap_or(none_val(), 99);  int64_t e = 
gcd(48, 18);  int64_t f = 
power(2, 10);  int64_t g = 
clamp(15, 0, 10);  int64_t h = 
count_down(100);  int64_t i = 
pair_sum(make_pair(3, 7));  int64_t j = 
pair_sum(swap_pair(make_pair(3, 7)));  int64_t k = 
ack(3, 3);return ((((((((((a + b) + c) + d) + e) + f) + g) + h) + i) + j) + k);}