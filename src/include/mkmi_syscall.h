#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus__
extern "C" {
#endif

size_t Syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6);

#ifdef __cplusplus__
}
#endif
