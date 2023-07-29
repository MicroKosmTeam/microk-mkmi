#include <mkmi_heap.h>
#include <mkmi_memory.h>

static bool initialized = false;

static void *heapStart;
static void *heapEnd;
static HeapSegHeader *lastHeader;

void HeapSegHeader::CombineForward() {
        if(next == NULL) return;
        if(!next->free) return;

        if(next == lastHeader) lastHeader = this;

        if(next->next != NULL) {
                next->next->last = this;
        }

        length = length + next->length + sizeof(HeapSegHeader);

        next = next->next;
}

void HeapSegHeader::CombineBackward() {
        if (last != NULL && last->free) last->CombineForward();
}

HeapSegHeader *HeapSegHeader::Split(size_t splitlength) {
        if (splitlength < 0x10) return NULL;
        int64_t splitSeglength = length - splitlength - (sizeof(HeapSegHeader));
        if (splitSeglength < 0x10) return NULL;

        HeapSegHeader *newSplitHeader = (HeapSegHeader*)((size_t)this + splitlength + sizeof(HeapSegHeader));
	if(next == NULL) next = newSplitHeader;
	else next->last = newSplitHeader;            // Set the next segment's last segment to our new segment
        newSplitHeader->next = next;            // Set the new segment's next segment to our original next
        next = newSplitHeader;                  // Set our new segment to the next segment
        newSplitHeader->last = this;            // Set our new segment's last segment to us
        newSplitHeader->length = splitSeglength;// Set the new header's length
        newSplitHeader->free = free;            // Make sure both free are the same
        length = splitlength;                   // Set the original segment's length to the nes one

        if (lastHeader == this) lastHeader = newSplitHeader;
        return newSplitHeader;
}

void MKMI_InitializeHeap(void *heapAddress, size_t initialSize) {
	if(initialized) return;

	initialized = true;

	VMAlloc(heapAddress, initialSize, 0);

        heapStart = heapAddress;
        heapEnd = (void*)((size_t)heapStart + initialSize);

        HeapSegHeader *startSeg = (HeapSegHeader*)heapAddress;
        startSeg->length = initialSize - sizeof(HeapSegHeader);
        startSeg->next = NULL;
        startSeg->last = NULL;
        startSeg->free = true;
        lastHeader = startSeg;
}

void MKMI_DeinitializeHeap() {
	if(!initialized) return;

	initialized = false;

	VMFree(heapStart, (uintptr_t)heapEnd - (uintptr_t)heapStart);
}

#define MAX_TRIES 4

size_t GetBlockSize(void *address) {
	HeapSegHeader *currSeg = (HeapSegHeader*)heapStart;

	while(true) {
		if((uintptr_t)address == (uintptr_t)currSeg) {
			if (!currSeg->free) return currSeg->length;
			else return 0;
		}

		if (currSeg->next == NULL) break;
		currSeg = currSeg->next;
	}

	return 0;
}

void *Malloc(size_t size) {
        if (size % 0x10 > 0){ // Not multiple of 0x10
                size -= (size % 0x10);
                size += 0x10;
        }

        if (size == 0) return NULL;

	for (int i = 0; i < MAX_TRIES; i++) {
		HeapSegHeader *currSeg = (HeapSegHeader*)heapStart;

		while(true) {
			if (currSeg-> free) {
				if (currSeg->length > size) {
					currSeg->Split(size);
					currSeg->free = false;
					return (void*)((uint64_t)currSeg + sizeof(HeapSegHeader));
				} else if (currSeg->length == size) {
					currSeg->free = false;
					return (void*)((uint64_t)currSeg + sizeof(HeapSegHeader));
				}
			}

			if (currSeg->next == NULL) break;
			currSeg = currSeg->next;
		}

		MKMI_ExpandHeap(size);
	}
}

void *Free(void *address) {
        HeapSegHeader *segment = (HeapSegHeader*)address - 1;
	if(segment->free) return;
        segment->free = true;
        segment->CombineForward();
        segment->CombineBackward();

	return address;
}

void MKMI_ExpandHeap(size_t length) {
        if (length % 0x1000) { // We can't allocate less that a page
                length -= length % 0x1000;
                length += 0x1000;
        }

        HeapSegHeader *newSegment = (HeapSegHeader*)heapEnd;

	VMAlloc(heapEnd, length, 0);

        newSegment->free = true;
        newSegment->last = lastHeader;
        lastHeader->next = newSegment;
        lastHeader = newSegment;
        newSegment->next = NULL;
        newSegment->length = length - sizeof(HeapSegHeader);
        newSegment->CombineBackward();
}
