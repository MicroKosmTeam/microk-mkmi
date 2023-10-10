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

static void FlushBuffer(char *buffer) {
	Syscall(SYSCALL_DEBUG_PRINTK, buffer, 0, 0, 0, 0, 0);
}

static void PrintChar(char *buffer, size_t *position, char ch) {
	if(*position >= MAX_PRINTK_SYSCALL_MESSAGE_LENGTH - 1) {
		FlushBuffer(buffer);
		position = 0;
	}

	buffer[*position] = ch;
	*position += 1;
}

static void PrintString(char *buffer, size_t *position, char *string) {
	char *ptr = string;

	while(*ptr) {
		PrintChar(buffer, position, *ptr);
		++ptr;
	}
}

void MKMI_VPrintf(char *format, va_list ap) {
        char messageBuffer[MAX_PRINTK_SYSCALL_MESSAGE_LENGTH + 1] = { '\0' };
	size_t position = 0;

        char *ptr = format;

        while(*ptr) {
                if (*ptr == '%') {
			ptr++;
                        switch (*ptr++) {
                                case 's': {
					char *str = va_arg(ap, uint8_t*);

					PrintString(messageBuffer, &position, str);
					}
                                        break;
                                case 'u':
                                case 'd': {
					char conversionBuffer[256];
                                        Itoa(conversionBuffer, 'd', va_arg(ap, long long int));

					PrintString(messageBuffer, &position, conversionBuffer);
					}
                                        break;
                                case 'x': {
					char conversionBuffer[256];
                                        Itoa(conversionBuffer, 'x', va_arg(ap, long long int));

					PrintString(messageBuffer, &position, conversionBuffer);
					}
                                        break;
                                case '%':
					PrintString(messageBuffer, &position, "%%");
                                        break;
                                case 'c':
                                        PrintChar(messageBuffer, &position, va_arg(ap, char));
                                        break;

                        }
                } else {
			PrintChar(messageBuffer, &position, *ptr++);
                }
        }
		
	FlushBuffer(messageBuffer);
}
