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

void PrintString(char *string) {
	Syscall(SYSCALL_DEBUG_PRINTK, string, 0, 0, 0, 0);
}

void MKMI_VPrintf(char *format, va_list ap) {
        char message[65536];
	
	Memset(message, '\0', 65536);

	char *position = message;
        char *ptr = format;

        while(*ptr) {
                if (*ptr == '%') {
			ptr++;
                        switch (*ptr++) {
                                case 's': {
					char *str = va_arg(ap, uint8_t*);
					while(*position++ = *str++);
					}
                                        break;
                                case 'u':
                                case 'd': {
					char buffer[256];
                                        itoa(buffer, 'd', va_arg(ap, long long int));
					size_t len = strlen(buffer);

					for (int i = 0; i < len; ++i) *position++ = buffer[i];
					}
                                        break;
                                case 'x': {
					char buffer[256];
                                        itoa(buffer, 'd', va_arg(ap, long long int));
					size_t len = strlen(buffer);

					for (int i = 0; i < len; ++i) *position++ = buffer[i];
					}
                                        break;
                                case '%':
                                        *position++ = '%';
                                        break;
                                case 'c':
                                        *position++ = va_arg(ap, uint8_t);
                                        break;

                        }
                } else {
                        *position++ = *ptr++;
                }
        }

	PrintString(message);
}
