#include <mkmi_log.h>
#include <stdint.h>
#include <mkmi_syscall.h>

void MKMI_Printf(char *format, ...) {
        va_list ap;
        va_start(ap, format);

	MKMI_VPrintf(format, ap);

        va_end(ap);
}

void PrintString(char *string) {
	Syscall(1, string, 0, 0, 0, 0);
}

void MKMI_VPrintf(char *format, va_list ap) {
       PrintString(format);
}
