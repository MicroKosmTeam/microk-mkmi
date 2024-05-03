#include "mkmi.h"

#include <stdarg.h>

static void PutStr(const char *str) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, str, 's', 0, 0, 0, 0);
}

static void PutChar(const char ch) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, ch, 'c', 0, 0, 0, 0);
}

static void PutHex(usize hex) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, hex, 'x', 0, 0, 0, 0);
}

static void PutDec(long dec) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, dec, 'd', 0, 0, 0, 0);
}

void MKMI_Log(char *format, ...) {
	va_list ap;
	va_start(ap, format);

        char *ptr = format;
        char buf[128];

        while(*ptr) {
                if (*ptr == '%') {
                        ptr++;
                        switch (*ptr++) {
                                case 's':
					PutStr(va_arg(ap, char *));
                                        break;
                                case 'd':
                                case 'u':
					PutDec(va_arg(ap, i64));
                                        break;
                                case 'x':
                                        PutHex(va_arg(ap, i64));
                                        break;
                                case '%':
                                        PutChar('%');
                                        break;
                                case 'c':
                                        PutChar((va_arg(ap, i32)));
                                        break;

                        }
                } else {
                        PutChar(*ptr++);
                }
        }

	va_end(ap);
}
