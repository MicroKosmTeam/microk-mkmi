#include <mkmi_log.h>
#include <stdint.h>
#include <stdarg.h>

void MKMI_Printf(char *format, ...) {
	uint64_t *KRNSYMTABLE = 0xffffffffffff0000;
	void (*test)(char *format, va_list ap) = KRNSYMTABLE[0];

	va_list ap;
	va_start(ap, format);
	test(format, ap);
	va_end(ap);
}
