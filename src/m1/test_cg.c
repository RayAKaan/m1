#include <stdint.h>

typedef struct { int64_t first; int64_t second; } Pair;


int64_t add(int64_t a, int64_t b) {
  return (a + b);
}
Pair make_pair(int64_t a, int64_t b) {
  return (Pair){ .first = a, .second = b };
}
int main(void) {
  return make_pair(3, 7).first;
}
