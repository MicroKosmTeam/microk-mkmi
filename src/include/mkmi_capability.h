#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus__
extern "C" {
#endif

typedef enum {
	NULL_CAPABILITY = 0,
	UNTYPED,
	FRAMES,
	CSPACE,
	CNODE,
	DOMAIN,
	SCHEDULER,
	TASK_CONTROL_BLOCK,
	SCHEDULER_CONTEXT,
	PAGING_STRUCTURE,
	OBJECT_TYPE_COUNT,
	RESERVED_SLOT = 0xFF
} MKMI_ObjectType;

typedef enum {
	NONE = 0,
	READ = 1 << 0,
	WRITE = 1 << 1,
	EXECUTE = 1 << 2,
	GRANT = 1 << 3,
	REVOKE = 1 << 4,
	MINT = 1 << 5,
	RETYPE = 1 << 6,
} MKMI_CapabilityRights;

typedef struct {
	uint8_t Type;
	uintptr_t Object;
	size_t Size;
	uint32_t AccessRights;
}__attribute__((packed)) MKMI_Capability;

#ifdef __cplusplus__
}
#endif

