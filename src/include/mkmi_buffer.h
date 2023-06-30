/*
   File: include/mkmi/mkmi_buffer.h

   MKMI buffer types and managment
*/

#pragma once
#include <cdefs.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

struct MKMI_Buffer {
	uintptr_t Address;
	bool Lock;
	size_t Type;
	size_t Size;
}__attribute__((packed));

#ifdef __cplusplus
}
#endif
