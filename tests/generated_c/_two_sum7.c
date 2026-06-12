#include <stdio.h>
#include <stdint.h>



int64_t process(int64_t nums, int64_t target) {
  return ({ int64_t m = map_new(); ({ int64_t i = 0; ({ int64_t _ = ({ while ((i < vector_len(nums))) { ({ int64_t _ = map_set(m, vector_get(nums, i), i); (i = (i + 1)); }); } 0; }); (i = 0); }); }); });
}
