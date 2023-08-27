/* MKMI, a library intended for MicroKosm modules
 * Copyright (C) 2022-2023 Mutta Filippo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General does return to userspacePublic License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * File: include/mkmi_heap.h
 */

#pragma once

#if !defined(_MKMI_MAIN_HEADER_)
#error "This file cannot be included separately"
#else

#pragma once
#include <cdefs.h>
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * function: MKMI_InitializeHeap 
 * Initialized the heap.
 * 
 * arguments: void *, size_t
 *  heapAddress -> The base virtual address where the heap starts
 *  initialSize -> Preallocated initial size of the heap, has to be bigger
 *                 than sizeof(HeapSegHeader) + 1
 *
 * return: void 
 */
void MKMI_InitializeHeap(void *heapAddress, size_t initialSize);

/*
 * function: MKMI_DeinitializeHeap 
 * Deinitializes the heap, freeing all allocated memory.
 * 
 * arguments: void 
 * return: void
 */
void MKMI_DeinitializeHeap();

/*
 * function: MKMI_ExpandHeap 
 * Increases the size of the heap by the specified amount
 * 
 * arguments: size_t
 * Amount of memory to append to the heap. If it is less than the
 * smallest amount allocated by VMAlloc (PAGE_SIZE), it is rounded
 * up to that number.
 *
 * return: never
 */
void MKMI_ExpandHeap(size_t length);

/*
 * function: Malloc 
 * Function wrapper for malloc.
 * 
 * arguments: size_t
 * The requested length of the memory area to allocate.
 *
 * return: void *
 * The in-heap address that has been allocated.
 */
void *Malloc(size_t size);

/*
 * function: Free 
 * Function wrapper for free.
 * 
 * arguments: void * 
 * The in-heap address that has to be freed.
 *
 * return: void
 */
void Free(void *address);

#ifdef __cplusplus
}

inline void *operator new(size_t size) {
	return Malloc(size);
}

inline void *operator new[](size_t size) {
	return Malloc(size);
}

inline void operator delete(void* p) {
	Free(p);
}

inline void operator delete[](void* p) {
	Free(p);
}

inline void operator delete(void* p, size_t unused) {
	Free(p);
}

inline void operator delete[](void* p, size_t unused) {
	Free(p);
}
#endif

#endif
