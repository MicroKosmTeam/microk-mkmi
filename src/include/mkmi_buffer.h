/*
   File: include/mkmi/mkmi_buffer.h

   MKMI buffer types and managment
*/

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

enum MKMI_BufferType {
	/* Communication between the kernel and the module */
	COMMUNICATION_MODULE_KERNEL = 0xC00,
	/* Communication between modules */
	COMMUNICATION_INTERMODULE   = 0xC01,

	/* Logging interface exposed by PrintK */
	LOG_PRINTK                  = 0xC10,
	/* Internal log of the module, exposed in sysfs */
	LOG_INTERNAL_GENERIC        = 0xC11,

	/* Internal module data, saved for live switch */
	DATA_MODULE_GENERIC         = 0xD00,
	/* Last function called by module, saved for live switch */
	DATA_MODULE_LASTOP          = 0xD01,

	/* Generic memory mapped device, no buffering */
	HW_IO_GENERIC               = 0xD10,
	/* Single-buffered memory mapped device */
	HW_IO_BUFFERED              = 0xD11,
};

enum MKMI_BufferOperation {
	/* Generic reading operation. Fails if buffer is not accessible. */
	OPERATION_READDATA          = 0xA0,
	/* Syncronous reading operation. Has an obligatory timeout */
	OPERATION_READDATA_SYNC     = 0xA1,

	/* Generic writing operation. Fails if buffer is not accessible. */
	OPERATION_WRITEDATA         = 0xB0,
	/* Syncronous writing operation. Has an obligatory timeout */
	OPERATION_WRITEDATA_SYNC     = 0xB1,
};

struct MKMI_Buffer {
	uintptr_t address;
	bool lock;
	MKMI_BufferType type;
	size_t size;
}__attribute__((packed));

#ifdef __cplusplus
}
#endif
