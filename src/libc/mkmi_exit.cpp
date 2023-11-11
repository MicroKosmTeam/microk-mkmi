#include <mkmi_exit.h>
#include <mkmi_syscall.h>

/* The objective of the exit function is to return to the kernel and
 * signal the process for deletion. This means the all of the allocated
 * resources are removed and that all the children processes are moved
 * to the process' partent
 */

extern "C" void _exit(size_t exitCode) {
	Syscall(SYSCALL_PROC_EXIT, exitCode, 0, 0, 0, 0, 0);
}

/* This is not like the _exit function. It is a simple yeild function.
 */
extern "C" void _return(size_t returnCode) {
	Syscall(SYSCALL_PROC_RETURN, returnCode, 0, 0, 0, 0, 0);
}
