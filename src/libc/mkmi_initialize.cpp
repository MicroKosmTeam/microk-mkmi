#include <stdint.h>
#include <stddef.h>

#include <mkmi_log.h>
#include <mkmi_memory.h>

extern "C" void __mkmi_init() {
	MKMI_Printf("Initializing MKMI...\r\n");


}

extern "C" void __mkmi_deinit() {
	MKMI_Printf("Deinitializing MKMI...\r\n");	
}
