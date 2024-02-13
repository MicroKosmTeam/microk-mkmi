#pragma once
#include <stdint.h>
#include <stddef.h>
#include <cdefs.h>

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
	ACCESS = 1 << 0,
	SEE = 1 << 1,
	RETYPE = 1 << 2,
	GRANT = 1 << 3,
	MINT = 1 << 4,
	REVOKE = 1 << 5,
	READ = 1 << 6,
	WRITE = 1 << 7,
	EXECUTE = 1 << 8,
} MKMI_CapabilityRights;

typedef enum {
	NULL_SLOT = 0,
	CSPACE_SLOT,
	ROOT_CNODE_SLOT,
	TASK_CONTROL_BLOCK_SLOT,
	MEMORY_MAP_CNODE_SLOT,
	FIRST_FREE_SLOT,
} MKMI_RootCNodeSlots;

typedef struct {
	u8 Type;
	uptr Object;
	usize Size;
	u32 AccessRights;
}__attribute__((packed)) MKMI_Capability;

#ifdef __cplusplus__
}
#endif
