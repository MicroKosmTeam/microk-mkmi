#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MKMI_Message {
	uint32_t SenderVendorID : 32;
	uint32_t SenderProductID : 32;

	size_t MessageSize : 64;
}__attribute__((packed));

#ifdef __cplusplus
}
#endif
