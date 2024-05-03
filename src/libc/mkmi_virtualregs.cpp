#include "mkmi.h"

#include <stdarg.h>

static usize *virtual_args_addr;
static usize virtual_args_size;

void __mkmi_init_args(usize *args, usize argsSize) {
	virtual_args_addr = args;
	virtual_args_size = argsSize;
}

void __mkmi_set_args(usize total_args, va_list ap) {
	if (total_args * sizeof(usize) >= virtual_args_size) {
		return;
	}

	usize *virtual_args_pos = virtual_args_addr;

	for (usize current = 0; current < total_args; ++current) {
		void *argument = va_arg(ap, void*);

		/* All arguments are padded to a usize boundary
		 * 64-bit values in 32-bit systems, on the other hand, are only
		 * available if split in two smaller 32-bit values */
		*virtual_args_pos = (usize)argument;
		++virtual_args_pos;
	}
}

usize __mkmi_get_arg_index(usize index) {
	if (index >= virtual_args_size / sizeof(usize)) {
		return 0;
	}

	return virtual_args_addr[index];
}

void __mkmi_clear_args() {
	//MEMCLR?
}
