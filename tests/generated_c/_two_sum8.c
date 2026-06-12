#include <stdio.h>
#include <stdint.h>



int64_t process(int64_t nums, int64_t target) {
  return ({ int64_t m = map_new(); ({ int64_t i = 0; ({ int64_t _ = ({ while ((i < vector_len(nums))) { ({ int64_t _ = map_set(m, vector_get(nums, i), i); (i = (i + 1)); }); } 0; }); ({ int64_t _ = (i = 0); ({ int64_t result = 0; ({ int64_t _ = ({ while ((i < vector_len(nums))) { ({ int64_t need = (target - vector_get(nums, i)); ({ int64_t _ = (result = map_get(m, need)); (i = (i + 1)); }); }); } 0; }); result; }); }); }); }); }); });
}
int main(void) {
  return ({ int64_t nums = vector_new(); ({ int64_t _ = vector_push(nums, 2); ({ int64_t _ = vector_push(nums, 7); ({ int64_t _ = vector_push(nums, 11); ({ int64_t _ = vector_push(nums, 15); ({ int64_t _ = println(int_to_string(vector_get(nums, process(nums, 9)))); 0; }); }); }); }); }); });
}
