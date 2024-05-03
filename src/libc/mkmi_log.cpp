#include "mkmi.h"

#include <stdarg.h>

static void put_str(const char *str) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, str, 's', 0, 0, 0, 0);
}

static void put_char(const char ch) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, ch, 'c', 0, 0, 0, 0);
}

static void put_hex(usize hex) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, hex, 'x', 0, 0, 0, 0);
}

static void put_dec(long dec) {
	__fast_syscall(SYSCALL_VECTOR_DEBUG, dec, 'd', 0, 0, 0, 0);
}

void mkmi_log(char *format, ...) {
	va_list ap;
	va_start(ap, format);

        char *ptr = format;
        char buf[128];

        while(*ptr) {
                if (*ptr == '%') {
                        ptr++;
                        switch (*ptr++) {
                                case 's':
					put_str(va_arg(ap, char *));
                                        break;
                                case 'd':
                                case 'u':
					put_dec(va_arg(ap, i64));
                                        break;
                                case 'x':
                                        put_hex(va_arg(ap, i64));
                                        break;
                                case '%':
                                        put_char('%');
                                        break;
                                case 'c':
                                        put_char((va_arg(ap, i32)));
                                        break;

                        }
                } else {
                        put_char(*ptr++);
                }
        }

	va_end(ap);
}
