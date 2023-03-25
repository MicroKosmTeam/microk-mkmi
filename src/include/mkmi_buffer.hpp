/*
   File: include/mkmi/mkmi_buffer.hpp

   MKMI buffer types and managment
*/

#pragma once
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>

namespace MKMI {
	enum BufferType {
		COMMUNICATION_MODULEKERNEL = 0xC00,
		COMMUNICATION_INTERMODULE  = 0xC02,

		DATA_MODULE_GENERIC        = 0xD00,
	};

	enum BufferOperation {
		OPERATION_READDATA         = 0xD0,
		OPERATION_WRITEDATA        = 0xD1,
	};

	struct Buffer {
		uintptr_t address;
		bool readable;
		BufferType type;
		size_t size;
	}__attribute__((packed));

	struct BufferMetadata {
		uint64_t code;
		Buffer *buffer;
	};

	Buffer *BufferCreate(uint64_t code, BufferType type, size_t size);
	uint64_t BufferIO(Buffer *buffer, BufferOperation operation, ...);
	uint64_t BufferDelete(Buffer *buffer);
}
