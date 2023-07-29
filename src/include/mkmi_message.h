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

typedef void (*MKMI_MessageCallback)(MKMI_Message *, void *);

MKMI_Message *ReadIncomingMessage();
void *GetMessageDataStart(MKMI_Message *msg);
void CleanUpIncomingMessage(MKMI_Message *msg);

void MKMI_MessageHandler();
void SetMessageHandlerCallback(MKMI_MessageCallback function);

#ifdef __cplusplus
}
#endif
