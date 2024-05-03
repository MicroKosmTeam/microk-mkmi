#include <stddef.h>
#include <cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t __fast_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6);

size_t Syscall(usize totalArgs, ...);

#ifdef __cplusplus
}
#endif
