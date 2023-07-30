#pragma once
#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
template <typename Type>
class unique_ptr {
public:
	/* Constructor: Take ownership of a Pointer */
	explicit unique_ptr(Type *ptr = nullptr) : Pointer(ptr) {}

	/* Destructor: Deallocate the object on destruction */
	~unique_ptr() {
		delete Pointer;
	}

	/* Disable copy constructor and assignment to enforce unique ownership */
	unique_ptr(const unique_ptr&) = delete;
	unique_ptr& operator=(const unique_ptr&) = delete;

	/* Move constructor and move assignment */
	unique_ptr(unique_ptr&& other) noexcept : Pointer(other.release()) {}
	unique_ptr& operator=(unique_ptr&& other) noexcept {
		reset(other.release());
		return *this;
	}

	// Access the object using the dereference operator (*)
	Type& operator*() const {
		return *Pointer;
	}

	// Access members of the object using the arrow operator (->)
	Type *operator->() const {
		return Pointer;
	}

	// Get the raw Pointer
	Type *Get() const {
		return Pointer;
	}

	// Release ownership without deleting the object
	Type *Release() {
		Type *temp = Pointer;
		Pointer = nullptr;
		return temp;
	}

	// Reset the Pointer, deallocating the current object if any
	void Reset(Type *ptr = nullptr) {
		delete Pointer;
		Pointer = ptr;
	}
private:
	Type *Pointer;
};

template <typename Type>
class shared_ptr {
public:
	/* Constructor: Take ownership of a Pointer */
	explicit shared_ptr(Type *ptr = nullptr) : Pointer(ptr) {
		if (Pointer) {
			ReferenceCount = new size_t[1];
		}
	}

	/* Destructor: Deallocate the object and the reference count when the last shared_ptr is destroyed */
	~shared_ptr() {
		if (ReferenceCount) {
			if (--(*ReferenceCount) == 0) {
				delete Pointer;
				delete ReferenceCount;
			}
		}
	}

	/* Copy constructor: Share ownership and increment the reference count */
	shared_ptr(const shared_ptr& other) : Pointer(other.Pointer), ReferenceCount(other.ReferenceCount) {
		if (ReferenceCount) {
			++(*ReferenceCount);
		}
	}

	/* Copy assignment: Release the current ownership and share ownership with the assigned shared_ptr */
	shared_ptr& operator=(const shared_ptr& other) {
		if (this != &other) {
			/* Release current ownership */
			if (ReferenceCount && --(*ReferenceCount) == 0) {
				delete Pointer;
				delete ReferenceCount;
			}

			/* Share ownership with the assigned shared_ptr */
			Pointer = other.Pointer;
			ReferenceCount = other.ReferenceCount;
			if (ReferenceCount) {
				++(*ReferenceCount);
			}
		}
		return *this;
	}

	/* Access the object using the dereference operator (*) */
	Type& operator*() const {
		return *Pointer;
	}

	/* Access members of the object using the arrow operator (->) */
	Type* operator->() const {
		return Pointer;
	}

	/* Get the raw Pointer */
	Type *Get() const {
		return Pointer;
	}

private:
	Type *Pointer;
	size_t *ReferenceCount = nullptr;
};
#endif
