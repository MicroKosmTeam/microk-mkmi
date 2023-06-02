#include <mkmi_syscall.h>

inline size_t __x64_int_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5) {
	size_t ret;
	asm volatile("mov %1, %%rdi\n\t"
		     "mov %2, %%rsi\n\t"
		     "mov %3, %%rdx\n\t"
		     "mov %4, %%rcx\n\t"
		     "mov %5, %%r8\n\t"
		     "mov %6, %%r9\n\t"
		     "int $0xFE\n\t"
		     "mov %%rax, %0"
		     : "=r"(ret)
		     : "r"(syscallNum), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5)
		     : "memory", "cc", "rax", "rdi", "rdi", "rdx", "rcx", "r8", "r9");


	return syscallNum;
}

inline size_t __x64_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5) {
	size_t ret;
	asm volatile("mov %1, %%rdi\n\t"
		     "mov %2, %%rsi\n\t"
		     "mov %3, %%rdx\n\t"
		     "mov %4, %%rcx\n\t"
		     "mov %5, %%r8\n\t"
		     "mov %6, %%r9\n\t"
		     "syscall\n\t"
		     "mov %%rax, %0"
		     : "=r"(ret)
		     : "r"(syscallNum), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5)
		     : "memory", "cc", "rax", "rdi", "rdi", "rdx", "rcx", "r8", "r9");


	return syscallNum;
}


size_t Syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5) {
	return __x64_syscall(syscallNum, arg1, arg2, arg3, arg4, arg5);
}