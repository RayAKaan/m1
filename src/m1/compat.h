/* Cross-platform compatibility shim for gcc/clang builds.
 * Included via -include in build_selfhost.sh to suppress warnings/
 * define-common-practice issues that don't exist on Windows+clang.
 */
#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wunused-value"
#  pragma clang diagnostic ignored "-Wunused-variable"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wunused-value"
#  pragma GCC diagnostic ignored "-Wunused-variable"
#endif

/* m0_runtime.c uses _snprintf_s which is MSVC only; alias to snprintf on POSIX. */
#if !defined(_MSC_VER) && !defined(_snprintf_s)
#  define _snprintf_s(buf, sz, cnt, fmt, ...) snprintf(buf, sz, fmt, ##__VA_ARGS__)
#endif

/* strncpy_s is MSVC only; alias to strncpy+NUL on POSIX. */
#if !defined(_MSC_VER) && !defined(strncpy_s)
#  define strncpy_s(dst, dsz, src, cnt) do { \
       strncpy(dst, src, dsz); \
       dst[dsz - 1] = '\0'; \
   } while(0)
#endif
