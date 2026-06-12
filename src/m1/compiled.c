#include <stdint.h>

typedef struct { int64_t first; int64_t second; } Pair;


Pair make_pair(int64_t a, int64_t b) {
  return (Pair){ .first = a, .second = b };
}
int64_t add(int64_t a, int64_t b) {
  return (a + b);
}
int main(void) {
  return ({ Pair p = make_pair(10, 20); add(p.first, p.second); });
}
