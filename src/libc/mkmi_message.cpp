#include <mkmi.h>

int IPCQueueCtl(QueueOperationStruct *ctlStruct) {
	return Syscall(SYSCALL_IPC_MESSAGE_QUEUE, ctlStruct, 0, 0, 0, 0, 0);
}

int IPCMessageSend(size_t queueID, const uint8_t *messagePointer, size_t messageLength, size_t messageType, size_t messageFlags) {
	return Syscall(SYSCALL_IPC_MESSAGE_SEND, queueID, messagePointer, messageLength, messageType, messageFlags, 0);
}

int IPCMessageReceive(size_t queueID, uint8_t *messageBufferPointer, size_t maxMessageLength, size_t messageType, size_t messageFlags) {
	return Syscall(SYSCALL_IPC_MESSAGE_RECEIVE, queueID, messageBufferPointer, maxMessageLength, messageType, messageFlags, 0);
}
