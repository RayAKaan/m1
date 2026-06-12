#include <stdio.h>
#include <stdint.h>


int64_t m0_println(char*);
char* m0_int_to_string(int64_t);
int64_t m1_string_split(char*, char*);
int64_t m1_vector_new(void);
int64_t m1_vector_len(int64_t);
char* m1_vector_get_str(int64_t, int64_t);
int64_t m0_string_to_int(char*);

int main(void) {
  return ({ int64_t parts = m1_string_split("10 20 30", " "); ({ int64_t _ = m0_println(m0_int_to_string(m1_vector_len(parts))); ({ int64_t i = 0; ({ int64_t sum = 0; ({ int64_t _ = ({ while ((i < m1_vector_len(parts))) { ({ char* part = m1_vector_get_str(parts, i); (sum = (sum + m0_string_to_int(part))); }); } 0; }); 0; }); }); }); }); });
}
