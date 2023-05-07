#include <mkmi_mutex.h>

bool MKMI_TryLockMutex(bool *lock) {
	if(__sync_bool_compare_and_swap(lock, false, true)) {
		return true;
	}

	return false;
}

void MKMI_SpinlockLockMutex(bool *lock) {
	while(!__sync_bool_compare_and_swap(lock, false, true));
}

void MKMI_UnlockMutex(bool *lock) {
	*lock = false;
}
