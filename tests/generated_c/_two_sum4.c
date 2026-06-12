#include <stdio.h>
#include <stdint.h>



int main(void) {
  return ({ int64_t nums = vector_new(); ({ int64_t _ = vector_push(nums, 2); ({ int64_t _ = vector_push(nums, 7); ({ int64_t _ = vector_push(nums, 11); ({ int64_t _ = vector_push(nums, 15); ({ int64_t target = 9; ({ int64_t m = map_new(); ({ int64_t i = 0; ({ int64_t found = 0; ({ int64_t _ = ({ while ((i < vector_len(nums))) { ({ int64_t num = vector_get(nums, i); ({ int64_t need = (target - num); ((map_has(m, need) == 1) ? ({ int64_t _ = println(string_concat("Found: ", int_to_string(num))); ({ int64_t _ = (found = 1); (i = (i + 1)); }); }) : 0); }); }); } 0; }); (found == 0); }); }); }); }); }); }); }); }); }); });
}
