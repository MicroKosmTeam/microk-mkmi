#include "mkmi.h"

#include <stdarg.h>

static usize *__VirtualArgsAddr;
static usize __VirtualArgsSize;

void __MKMI_InitArgs(usize *args, usize argsSize) {
	__VirtualArgsAddr = args;
	__VirtualArgsSize = argsSize;
}

void __MKMI_SetArgs(usize totalArgs, va_list ap) {
	if (totalArgs * sizeof(usize) >= __VirtualArgsSize) {
		return;
	}

	usize *virtualArgsPos = __VirtualArgsAddr;

	for (usize current = 0; current < totalArgs; ++current) {
		void *argument = va_arg(ap, void*);

		/* All arguments are padded to a usize boundary
		 * 64-bit values in 32-bit systems, on the other hand, are only
		 * available if split in two smaller 32-bit values */
		*virtualArgsPos = (usize)argument;
		++virtualArgsPos;
	}
}

usize __MKMI_GetArgIndex(usize index) {
	if (index >= __VirtualArgsSize / sizeof(usize)) {
		return 0;
	}

	return __VirtualArgsAddr[index];
}

void __MKMI_ClearArgs() {
	//MEMCLR?
}
