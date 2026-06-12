#include <stdio.h>
#include <stdint.h>

typedef struct { int64_t x; int64_t y; } Point;


Point make_point(int64_t x, int64_t y) {
  return 0;
}
int64_t point_sum(Point p) {
  return (p.x + p.y);
}
int main(void) {
  return ({ Point p = make_point(3, 7); println(int_to_string(point_sum(p))); });
}
