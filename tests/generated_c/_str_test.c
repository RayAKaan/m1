#include <stdio.h>
#include <stdint.h>



int main(void) {
  return ({ char* s = "Hello, World"; ({ int64_t _ = println(int_to_string(char_at(s, 0))); ({ int64_t _ = println(substring(s, 7, 5)); ({ int64_t parts = string_split("10 20 30", " "); ({ int64_t i = 0; ({ int64_t sum = 0; ({ int64_t _ = ({ while ((i < vector_len(parts))) { ({ char* part = vector_get_str(parts, i); (sum = (sum + string_to_int(part))); }); } 0; }); 0; }); }); }); }); }); }); });
}
