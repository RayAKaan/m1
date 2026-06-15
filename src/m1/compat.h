#ifndef M1_COMPAT_H
#define M1_COMPAT_H
/* Portability shim: lets the Windows-targeted runtime/phase_graph sources build
   with gcc/clang on Linux/macOS. Force-include with: -include src/m1/compat.h
   Also #included directly by m0_runtime.c so the shim applies even if a source is
   compiled without -include. */

#include <string.h>
#include <stdlib.h>

#ifndef _WIN32

#ifndef _TRUNCATE
#define _TRUNCATE ((size_t)-1)
#endif

/* MSVC-only bounded copy -> portable inline. */
static inline int m1_strncpy_s(char *d, size_t dn, const char *s, size_t cnt){
    if(!d||!s||dn==0) return 1;
    size_t i=0;
    for(; i+1<dn && s[i] && (cnt==(size_t)-1 || i<cnt); i++) d[i]=s[i];
    d[i]='\0';
    return 0;
}
#ifndef strncpy_s
#define strncpy_s(d,dn,s,cnt) m1_strncpy_s((d),(dn),(s),(cnt))
#endif

/* MSVC's _strdup. Provide a real inline function (not just a macro) so it links
   even if a translation unit calls _strdup without seeing the macro. strdup is a
   POSIX/GNU function; under -std=gnu11 it is declared by <string.h>. We forward
   to malloc+memcpy to avoid any feature-test-macro visibility issues. */
static inline char *m1_strdup(const char *s){
    if(!s) return 0;
    size_t n = strlen(s) + 1;
    char *p = (char*)malloc(n);
    if(p) memcpy(p, s, n);
    return p;
}
#ifndef _strdup
#define _strdup m1_strdup
#endif

#endif /* !_WIN32 */

#endif /* M1_COMPAT_H */
