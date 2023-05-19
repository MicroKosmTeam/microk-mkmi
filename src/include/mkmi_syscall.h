#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t Syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5);

#ifdef __cplusplus
}
#endif
