#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	uint32_t SenderVendorID : 32;
	uint32_t SenderProductID : 32;

	size_t MessageSize : 64;
}__attribute__((packed)) MKMI_Message;

typedef int (*MKMI_MessageCallback)(MKMI_Message *, void *);

MKMI_Message *ReadIncomingMessage();
void *GetMessageDataStart(MKMI_Message *msg);
void CleanUpIncomingMessage(MKMI_Message *msg);

void MKMI_MessageHandler();
void SetMessageHandlerCallback(MKMI_MessageCallback function);

int SendDirectMessage(uint32_t vendorID, uint32_t productID, uint8_t *data, size_t length);

#ifdef __cplusplus
}
#endif
