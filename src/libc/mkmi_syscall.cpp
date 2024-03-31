#include "mkmi.h"

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

size_t __syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6) {
	return __x64_syscall(syscallNum, arg1, arg2, arg3, arg4, arg5, arg6);
}


size_t Syscall() {
	return __syscall(
		*(usize*)MKMI_GetIndex(0),
		*(usize*)MKMI_GetIndex(sizeof(usize) * 1),
		*(usize*)MKMI_GetIndex(sizeof(usize) * 2),
		*(usize*)MKMI_GetIndex(sizeof(usize) * 3),
		*(usize*)MKMI_GetIndex(sizeof(usize) * 4),
		*(usize*)MKMI_GetIndex(sizeof(usize) * 5),
		*(usize*)MKMI_GetIndex(sizeof(usize) * 6));
}

