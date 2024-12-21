#include <mkmi_assert.h>

#include <mkmi.h>

void mkmi_assert(bool expression, char *file, char *function, size_t line) {
	if (!expression) {
		mkmi_log("ASSERTION FAILED IN %s LINE %d, %s\r\n", function, line, file);
		while(true) { }
	}
}
