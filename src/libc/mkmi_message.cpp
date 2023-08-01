#include <mkmi_message.h>

#include <mkmi.h>

static MKMI_MessageCallback callback;

MKMI_Message *ReadIncomingMessage() {
	return (MKMI_Message*)0x700000000000;
}

void *GetMessageDataStart(MKMI_Message *msg) {
	return (void*)((uintptr_t)msg + 128);
}

void CleanUpIncomingMessage(MKMI_Message *msg) {
	VMFree(msg, msg->MessageSize);
}

void MKMI_MessageHandler() {
	MKMI_Message *msg = ReadIncomingMessage();
	void *data = GetMessageDataStart(msg);

	MKMI_Printf("Message at        0x%x\r\n"
			" Sender Vendor ID:  %x\r\n"
			" Sender Product ID: %x\r\n"
			" Message Size:      %d\r\n",
			msg,
			msg->SenderVendorID,
			msg->SenderProductID,
			msg->MessageSize);

	if(!callback) _return(128);
	int result = callback(msg, data);

	CleanUpIncomingMessage(msg);

	_return(result);

	__builtin_unreachable();
}

void SetMessageHandlerCallback(MKMI_MessageCallback function) {
	callback = function;
}

int SendDirectMessage(uint32_t vendorID, uint32_t productID, uint8_t *data, size_t length) {
	Syscall(SYSCALL_MODULE_MESSAGE_SEND, vendorID, productID, data, length, 0 ,0);

	return 0;
}

