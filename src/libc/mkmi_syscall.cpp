#include "mkmi.h"

#include <stdarg.h>

inline __attribute__((always_inline))
size_t __x64_int_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6) {
	asm volatile(
		     "mov %0, %%rax\n\t"
		     "mov %1, %%rdi\n\t"
		     "mov %2, %%rsi\n\t"
		     "mov %3, %%rdx\n\t"
		     "mov %4, %%r8\n\t"
		     "mov %5, %%r9\n\t"
		     "mov %6, %%r10\n\t"
		     "int $0xFE\n\t"
		     "mov %%rax, %0\n\t"
		     :
		     : "r"(syscallNum), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5), "r"(arg6)
		     : "memory", "cc", "rax", "rdi", "rsi", "rdx", "r8", "r9", "r10");

	return syscallNum;
}

inline __attribute__((always_inline))
size_t __x64_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6) {
	asm volatile(
		     "mov %0, %%rax\n\t"
		     "mov %1, %%rdi\n\t"
		     "mov %2, %%rsi\n\t"
		     "mov %3, %%rdx\n\t"
		     "mov %4, %%r8\n\t"
		     "mov %5, %%r9\n\t"
		     "mov %6, %%r10\n\t"
		     "syscall\n\t"
		     "mov %%rax, %0\n\t"
		     :
		     : "r"(syscallNum), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5), "r"(arg6)
		     : "memory", "cc", "rax", "rdi", "rsi", "rdx", "r8", "r9", "r10");

	return syscallNum;
}

size_t __fast_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6) {
#ifdef __x86_64__
	return __x64_syscall(syscallNum, arg1, arg2, arg3, arg4, arg5, arg6);
#else
#endif
}


size_t Syscall(usize totalArgs, ...) {
	va_list ap;
	va_start(ap, totalArgs);

	__MKMI_SetArgs(totalArgs, ap);

	va_end(ap);

	usize status = __fast_syscall(
		__MKMI_GetArgIndex(0),
		__MKMI_GetArgIndex(1),
		__MKMI_GetArgIndex(2),
		__MKMI_GetArgIndex(3),
		__MKMI_GetArgIndex(4),
		__MKMI_GetArgIndex(5),
		__MKMI_GetArgIndex(6));
	
	__MKMI_ClearArgs();

	return status;
}

