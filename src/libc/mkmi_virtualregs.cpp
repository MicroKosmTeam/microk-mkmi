#include "mkmi.h"

static u8 *VirtualArgsAddr;
static usize VirtualArgsSize;

void MKMI_InitArgs(u8 *args, usize argsSize) {
	VirtualArgsAddr = args;
	VirtualArgsSize = argsSize;
}

void MKMI_ClearArgs() {
	//MEMCLR?
}

void MKMI_PushArg(usize arg, usize length, usize *token) {
	if (length > sizeof(usize)) {
		return;
	}
	
	if (*token >= VirtualArgsSize) {
		return;
	}

	*(usize*)((uptr)VirtualArgsAddr + *token) = arg;
	*token = *token + length;
}

usize MKMI_PopArg(usize length, usize *token) {
	if (length > sizeof(usize)) {
		return 0;
	}

	if (*token == 0) {
		return 0;
	}

	usize arg = 0;

	*token = *token - length;

	usize *addr = (usize*)((uptr)VirtualArgsAddr + *token);
	arg = *addr;
	*addr = 0;
	
	return arg;
}
