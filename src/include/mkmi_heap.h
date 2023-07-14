#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct HeapSegHeader{
        size_t length;
        HeapSegHeader *next;
        HeapSegHeader *last;
        bool free;

        void CombineForward();
        void CombineBackward();
        HeapSegHeader *Split(size_t splitLenght);
};

void MKMI_InitializeHeap(void *heapAddress, size_t pageCount);
void MKMI_DeinitializeHeap();
void MKMI_ExpandHeap(size_t lenght);

void *Malloc(size_t size);
size_t GetBlockSize(void *address);
void Free(void *address);

#ifdef __cplusplus
}
#endif
