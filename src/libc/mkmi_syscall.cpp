#include <mkmi_syscall.h>

inline size_t __x64_syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5) {
	asm volatile("int $0xFE" 
			: "=S"(arg1) 
			: "D"(syscallNum), "S"(arg1), "a"(arg2), "b"(arg3), "c"(arg4), "d"(arg5));

	return arg1;
}

size_t Syscall(size_t syscallNum, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5) {
	return __x64_syscall(syscallNum, arg1, arg2, arg3, arg4, arg5);
}
