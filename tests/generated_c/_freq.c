#include <stdio.h>
#include <stdint.h>



int main(void) {
  return ({ int64_t nums = vector_new(); ({ int64_t _ = vector_push(nums, 1); ({ int64_t _ = vector_push(nums, 3); ({ int64_t _ = vector_push(nums, 2); ({ int64_t _ = vector_push(nums, 1); ({ int64_t _ = vector_push(nums, 2); ({ int64_t _ = vector_push(nums, 1); ({ int64_t m = map_new(); ({ int64_t i = 0; ({ int64_t _ = ({ while ((i < vector_len(nums))) { ({ int64_t num = vector_get(nums, i); ({ int64_t count = ((map_has(m, num) == 1) ? (map_get(m, num) + 1) : 0); string_concat("Unique count: ", int_to_string(map_len(m))); }); }); } 0; }); string_concat("1 appears: ", int_to_string(map_get(m, 1))); }); }); }); }); }); }); }); }); }); });
}
