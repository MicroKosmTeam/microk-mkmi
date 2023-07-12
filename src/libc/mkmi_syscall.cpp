#include <mkmi_syscall.h>

inline size_t __x64_int_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6) {
	asm volatile("mov %0, %%rax\n\t"
		     "mov %1, %%rdi\n\t"
		     "mov %2, %%rsi\n\t"
		     "mov %3, %%rdx\n\t"
		     "mov %4, %%rcx\n\t"
		     "mov %5, %%r8\n\t"
		     "mov %6, %%r9\n\t"
		     "int $0xFE\n\t"
		     "mov %%rax, %0\n\r"
		     : 
		     : "r"(syscallNum), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5), "r"(arg6)
		     : "memory", "cc", "rax", "rdi", "rsi", "rdx", "rcx", "r8", "r9");

	return syscallNum;
}

inline size_t __x64_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6) {
	asm volatile("push %%rdi\n\t"
		     "push %%rsi\n\t"
		     "push %%rbx\n\t"
		     "push %%rcx\n\r"
		     "push %%rdx\n\t"
		     "push %%r8\n\t"
		     "push %%r9\n\t"
		     "push %%r10\n\t"
		     "push %%r11\n\t"
		     "push %%r12\n\t"
		     "push %%r13\n\t"
		     "push %%r14\n\t"
		     "push %%r15\n\t"
		     "mov %0, %%rax\n\t"
		     "mov %1, %%rdi\n\t"
		     "mov %2, %%rsi\n\t"
		     "mov %3, %%rdx\n\t"
		     "mov %4, %%r8\n\t"
		     "mov %5, %%r9\n\t"
		     "mov %6, %%r10\n\t"
		     "syscall\n\t"
		     "mov %%rax, %0\n\t"
		     "pop %%r15\n\t"
		     "pop %%r14\n\t"
		     "pop %%r13\n\t"
		     "pop %%r12\n\t"
		     "pop %%r11\n\t"
		     "pop %%r10\n\t"
		     "pop %%r9\n\t"
		     "pop %%r8\n\t"
		     "pop %%rdx\n\t"
		     "pop %%rcx\n\t"
		     "pop %%rbx\n\t"
		     "pop %%rsi\n\t"
		     "pop %%rdi\n\t"
		     :
		     : "r"(syscallNum), "r"(arg1), "r"(arg2), "r"(arg3), "r"(arg4), "r"(arg5), "r"(arg6)
		     : "memory", "cc", "rax", "rdi", "rsi", "rdx", "r8", "r9", "r10");

	return syscallNum;
}


size_t Syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5, size_t arg6) {
	return __x64_syscall(syscallNum, arg1, arg2, arg3, arg4, arg5, arg6);
}
