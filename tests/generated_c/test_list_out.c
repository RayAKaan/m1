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
typedef struct {
  int64_t items;  
  int64_t count;  
} Foo;