#include <stdint.h>
#include <stddef.h>

#include <mkmi.h>

extern uint32_t VendorID;
extern uint32_t ProductID;

extern "C" void __mkmi_init() {
	MKMI_Printf("Initializing MKMI...\r\n");
	Syscall(SYSCALL_MODULE_REGISTER, VendorID, ProductID, 0, 0, 0, 0);

	MKMI_Printf("Initializing the heap...\r\n");

	/* 1TB as base, 1MB in size. Anything else doesn't seem to work optimally */
	const uintptr_t heapBase = (0x10000000000);
	const size_t heapLength = (1024 * 1024);
	MKMI_InitializeHeap(heapBase, heapLength);

	MKMI_Printf("Initialization complete.\r\n");
}

extern "C" void __mkmi_deinit() {
	MKMI_Printf("Deinitializing MKMI...\r\n");
	Syscall(SYSCALL_MODULE_UNREGISTER, 0, 0, 0, 0, 0, 0);

	MKMI_Printf("Deinitializing the heap...\r\n");
	MKMI_DeinitializeHeap();

	MKMI_Printf("Deinitialization complete.\r\n");
}
