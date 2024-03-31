#pragma once
#include <cdefs.h>

void MKMI_InitArgs(u8 *args, usize argsSize);
void MKMI_ClearArgs();
void MKMI_PushArg(usize arg, usize length, usize *token);
usize MKMI_PopArg(usize length, usize *token);
