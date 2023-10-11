/*
   File: include/mkmi/mkmi_mutex.h

   MKMI syncronization primitives 
*/

#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

bool MKMI_TryLockMutex(bool *lock);
void MKMI_SpinlockLockMutex(bool *lock);

inline void MKMI_LockMutex(bool *lock) {
	MKMI_SpinlockLockMutex(lock);
}

void MKMI_UnlockMutex(bool *lock);

#ifdef __cplusplus
}
#endif
