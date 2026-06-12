#include <stdio.h>
#include <stdint.h>



int64_t process(int64_t nums, int64_t target) {
  return ({ int64_t m = map_new(); ({ int64_t i = 0; ({ int64_t found = 0; ({ int64_t _ = ({ while ((i < vector_len(nums))) { ({ int64_t num = vector_get(nums, i); ({ int64_t need = (target - num); ({ int64_t _ = ((map_has(m, need) == 1) ? ({ int64_t _ = println(string_concat("Found: ", int_to_string(num))); (found = 1); }) : 0); 0; }); }); }); } 0; }); (main() ? 0); }); }); }); });
}
