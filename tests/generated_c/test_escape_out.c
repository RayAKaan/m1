#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

/* Module: Test */
extern int64_t m0_char_at(char*, int64_t);
extern char* m0_substr(char*, int64_t, int64_t);
extern int64_t m0_string_eq(char*, char*);
extern int64_t m0_string_len(char*);
extern int64_t m0_print(char*);
extern int64_t m0_print_int(int64_t);
int64_t hello() {
return m0_print("hello\n42");}
int main() {
return hello();}