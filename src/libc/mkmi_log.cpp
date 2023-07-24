#include <stdint.h>
#include <mkmi_log.h>
#include <mkmi_memory.h>
#include <mkmi_string.h>
#include <mkmi_syscall.h>

void MKMI_Printf(char *format, ...) {
        va_list ap;
        va_start(ap, format);

	MKMI_VPrintf(format, ap);

        va_end(ap);
}

void PrintChar(char ch) {
	char str[2];
	str[0] = ch;
	str[1] = '\0';

	Syscall(SYSCALL_DEBUG_PRINTK, str, 0, 0, 0, 0, 0);
}

void PrintString(char *string) {
	Syscall(SYSCALL_DEBUG_PRINTK, string, 0, 0, 0, 0, 0);
}

void MKMI_VPrintf(char *format, va_list ap) {
        char message[1024];
	Memset(message, '\0', 1024);

	char *position = message;
        char *ptr = format;

        while(*ptr) {
                if (*ptr == '%') {
			ptr++;
                        switch (*ptr++) {
                                case 's': {
					char *str = va_arg(ap, uint8_t*);

					PrintString(str);
					}
                                        break;
                                case 'u':
                                case 'd': {
					char buffer[256];
                                        Itoa(buffer, 'd', va_arg(ap, long long int));

					PrintString(buffer);
					}
                                        break;
                                case 'x': {
					char buffer[256];
                                        Itoa(buffer, 'x', va_arg(ap, long long int));

					PrintString(buffer);
					}
                                        break;
                                case '%':
					PrintString("%%");
                                        break;
                                case 'c':
                                        PrintChar(va_arg(ap, char));
                                        break;

                        }
                } else {
			PrintChar(*ptr++);
                }
        }
}
