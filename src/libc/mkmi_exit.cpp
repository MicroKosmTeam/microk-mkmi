#include <stdint.h>
#include <stddef.h>
#include <mkmi_syscall.h>

/* The objective of the exit function is to return to the kernel and
 * signal the process for deletion. This means the all of the allocated
 * resources are removed and that all the children processes are moved
 * to the process' partent
 */

extern "C" void _exit(size_t exitCode, uintptr_t stack) {
	Syscall(SYSCALL_PROC_EXIT, exitCode, stack, 0, 0, 0, 0);
}

/* This is not like the _exit function. Its objective is to return to the kernel
 * after a module is initialized. We don't expect to return here after the switch.
 */
extern "C" void _return(size_t returnCode, uintptr_t stack) {
	Syscall(SYSCALL_PROC_RETURN, returnCode, stack, 0, 0, 0, 0);
}
