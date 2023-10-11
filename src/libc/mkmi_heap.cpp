#include <mkmi.h>

#define MAX_TRIES 4

/*
 * struct: HeapSegHeader 
 * Contains metadata and functions for each heap segment.
 * It's an internal structure, not meant for use by modules.
 *
 * attributes: none
 */
struct HeapSegHeader {
	/* Length of the current segment - sizeof(HeapSegHeader) */
        size_t Length;

	/* Next segment in the heap */
        HeapSegHeader *Next;

	/* Last segment in the heap */
        HeapSegHeader *Last;

	/* Is this segment Free? */
        bool Free;
	
	/*
	 * function: CombineForward 
	 * Unites this segment with the one that follows (if present).
	 * 
	 * arguments: void 
	 * return: void 
	 */
        void CombineForward();

	/*
	 * function: CombineBackward
	 * Unites this segment with the one that preceeds (if present).
	 * 
	 * arguments: void 
	 * return: void 
	 */
        void CombineBackward();
	
	/*
	 * function: Split
	 * Creates a new segment from this one of the specified Length,
	 * splitting us in two.
	 * 
	 * arguments: size_t
	 * The size of the new segment, which will be subtracted
	 * from this one's Length;
	 *
	 * return: HeapSegHeader *
	 * A pointer to the new header that has been split from this one.
	 */
        HeapSegHeader *Split(size_t splitLenght);
};

/* Wether the heap has already been Initialized through the MKMI_InitializeHeap function
 * and the MKMI_DeinitializeHeap function has not completed its execution */
static bool Initialized = false;

/* Starting and ending addresses of the heap */
static void *HeapStart;
static void *HeapEnd;

/* The last header in the heap */
static HeapSegHeader *LastHeader;

void HeapSegHeader::CombineForward() {
	/* Check if the following segment actually exists */
        if(Next == NULL) return;

	/* If it does, continue only if it's free */
        if(!Next->Free) return;

        if(Next == LastHeader) LastHeader = this;

        if(Next->Next != NULL) {
                Next->Next->Last = this;
        }

        Length = Length + Next->Length + sizeof(HeapSegHeader);

        Next = Next->Next;
}

void HeapSegHeader::CombineBackward() {
        if (Last != NULL && Last->Free) Last->CombineForward();
}

HeapSegHeader *HeapSegHeader::Split(size_t splitLength) {
        if (splitLength < 0x10) return NULL;
        int64_t splitSegLength = Length - splitLength - (sizeof(HeapSegHeader));
        if (splitSegLength < 0x10) return NULL;

        HeapSegHeader *newSplitHeader = (HeapSegHeader*)((size_t)this + splitLength + sizeof(HeapSegHeader));
	if(Next == NULL) Next = newSplitHeader;
	else Next->Last = newSplitHeader;            // Set the Next segment's Last segment to our new segment
        newSplitHeader->Next = Next;            // Set the new segment's Next segment to our original Next
        Next = newSplitHeader;                  // Set our new segment to the Next segment
        newSplitHeader->Last = this;            // Set our new segment's Last segment to us
        newSplitHeader->Length = splitSegLength;// Set the new header's Length
        newSplitHeader->Free = Free;            // Make sure both Free are the same
        Length = splitLength;                   // Set the original segment's Length to the nes one

        if (LastHeader == this) LastHeader = newSplitHeader;
        return newSplitHeader;
}

static void MallocDebug() {
       Syscall(0, 0x69, 0x69, 0x69, 0x69, 0x69, 0x69);
}

/*
 * function: malloc 
 * Weak implementation of malloc. If another C library providing this function
 * is linked, it ignores this function.
 * 
 * arguments: size_t
 * The requested length of the memory area to allocate.
 *
 * return: void *
 * The in-heap address that has been allocated.
 */
__attribute__((weak)) void *malloc(size_t size) {
	if (size % 0x10 > 0){ // Not multiple of 0x10
                size -= (size % 0x10);
                size += 0x10;
        }

        if (size == 0) return NULL;

	for (int i = 0; i < MAX_TRIES; i++) {
		HeapSegHeader *currSeg = (HeapSegHeader*)HeapStart;

		while(true) {
			if (currSeg-> Free) {
				if (currSeg->Length > size) {
					void *addr = (void*)((uint64_t)currSeg + sizeof(HeapSegHeader));
					currSeg->Split(size);
					currSeg->Free = false;

					MallocDebug();
					return addr;
				} else if (currSeg->Length == size) {
					void *addr = (void*)((uint64_t)currSeg + sizeof(HeapSegHeader));
					currSeg->Free = false;

					MallocDebug();
					return addr;
				}
			}

			if (currSeg->Next == NULL) break;
			currSeg = currSeg->Next;
		}

		MKMI_ExpandHeap(size);
	}

}

/*
 * function: free
 * Weak implementation of free. If another C library providing this function
 * is linked, it ignores this function.
 * 
 * arguments: void * 
 * The in-heap address that has to be freed.
 *
 * return: void
 */
__attribute__((weak)) void free(void *address) {
	if(address <= HeapStart || address >= HeapEnd) return;

	HeapSegHeader *segment = (HeapSegHeader*)address - 1;

	if(segment->Free) return;

        segment->Free = true;
        segment->CombineForward();
        segment->CombineBackward();
}



void MKMI_InitializeHeap(void *heapAddress, size_t initialSize) {
	if(Initialized) return;
	if(initialSize < sizeof(HeapSegHeader) + 1) return;

	Initialized = true;

	VMAlloc(heapAddress, initialSize, 0);

        HeapStart = heapAddress;
        HeapEnd = (void*)((size_t)HeapStart + initialSize);

        HeapSegHeader *startSeg = (HeapSegHeader*)heapAddress;
        startSeg->Length = initialSize - sizeof(HeapSegHeader);
        startSeg->Next = NULL;
        startSeg->Last = NULL;
        startSeg->Free = true;
        LastHeader = startSeg;
}

void MKMI_DeinitializeHeap() {
	if(!Initialized) return;

	Initialized = false;

	VMFree(HeapStart, (uintptr_t)HeapEnd - (uintptr_t)HeapStart);
}

void *Malloc(size_t size) {
	return malloc(size);
}

void Free(void *address) {
	Free(address);
}

void MKMI_ExpandHeap(size_t Length) {
	MKMI_Printf("!!!! Expand Head !!!!\r\n");

        if (Length % 4096) { // We can't allocate less that a page
                Length -= Length % 4096;
                Length += 4096;
        }

        HeapSegHeader *newSegment = (HeapSegHeader*)HeapEnd;

	VMAlloc(HeapEnd, Length, 0);

        newSegment->Free = true;
        newSegment->Last = LastHeader;
        LastHeader->Next = newSegment;
        LastHeader = newSegment;
        newSegment->Next = NULL;
        newSegment->Length = Length - sizeof(HeapSegHeader);
        newSegment->CombineBackward();
}
