#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

/* Module: Test */
int64_t constant() {
  return 7;  
}
int64_t inline_let() {
  return 6;  
}
int64_t fold_if() {
  return 10;  
}
int64_t reduce_match() {
  return 100;  
}
int64_t field_proj() {
  return 7;  
}
int64_t nested() {
  return 8;  
}
int64_t identity() {
  return 42;  
}
int64_t dup() {
  return 12;  
}
int64_t neg_zero() {
  return 0;  
}
int bool_and() {
  return 0;  
}
int bool_or() {
  return 1;  
}
int not_true() {
  return 0;  
}
int main() {
  return ((((constant() + inline_let()) + fold_if()) + reduce_match()) + field_proj());  
}
