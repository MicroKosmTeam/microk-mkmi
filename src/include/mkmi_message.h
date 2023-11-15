#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	CREATE = 1,
} QueueOperations;

typedef struct {
	QueueOperations Operation;
		
	union {
		struct {
			size_t PreallocateSize;
			size_t NewID;
		} Create;
	};
}__attribute__((packed)) QueueOperationStruct;

int IPCQueueCtl(QueueOperationStruct *ctlStruct);
int IPCMessageSend(size_t queueID, const uint8_t *messagePointer, size_t messageLength, size_t messageType, size_t messageFlags);
int IPCMessageReceive(size_t queueID, uint8_t *messageBufferPointer, size_t maxMessageLength, size_t messageType, size_t messageFlags);

#ifdef __cplusplus
}
#endif
