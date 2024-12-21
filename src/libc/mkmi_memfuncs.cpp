#include <mkmi_memfuncs.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef	int word;		/* "word" used for optimal copy speed */

#define	wsize	sizeof(word)
#define	wmask	(wsize - 1)

__attribute__((weak))
void *memcpy(void *dst0, const void *src0, size_t length) {
	char *dst = dst0;
	const char *src = src0;
	size_t t;
	
	if (length == 0 || dst == src)		/* nothing to do */
		goto done;
	
	/*
	 * Macros: loop-t-times; and loop-t-times, t>0
	 */
#define	TLOOP(s) if (t) TLOOP1(s)
#define	TLOOP1(s) do { s; } while (--t)
	
	if ((unsigned long)dst < (unsigned long)src) {
		/*
		 * Copy forward.
		 */
		t = (uintptr_t)src;	/* only need low bits */
		if ((t | (uintptr_t)dst) & wmask) {
			/*
			 * Try to align operands.  This cannot be done
			 * unless the low bits match.
			 */
			if ((t ^ (uintptr_t)dst) & wmask || length < wsize)
				t = length;
			else
				t = wsize - (t & wmask);
			length -= t;
			TLOOP1(*dst++ = *src++);
		}
		/*
		 * Copy whole words, then mop up any trailing bytes.
		 */
		t = length / wsize;
		TLOOP(*(word *)dst = *(word *)src; src += wsize; dst += wsize);
		t = length & wmask;
		TLOOP(*dst++ = *src++);
	} else {
		/*
		 * Copy backwards.  Otherwise essentially the same.
		 * Alignment works as before, except that it takes
		 * (t&wmask) bytes to align, not wsize-(t&wmask).
		 */
		src += length;
		dst += length;
		t = (uintptr_t)src;
		if ((t | (uintptr_t)dst) & wmask) {
			if ((t ^ (uintptr_t)dst) & wmask || length <= wsize)
				t = length;
			else
				t &= wmask;
			length -= t;
			TLOOP1(*--dst = *--src);
		}
		t = length / wsize;
		TLOOP(src -= wsize; dst -= wsize; *(word *)dst = *(word *)src);
		t = length & wmask;
		TLOOP(*--dst = *--src);
	}
done:
	return (dst0);
}

#define	VAL	c0
#define	WIDEVAL	c

__attribute__((weak))
void *memset(void *dst0, int c0, size_t length) {
	size_t t;
	unsigned int c;
	unsigned char *dst;

	dst = dst0;
	/*
	 * If not enough words, just fill bytes.  A length >= 2 words
	 * guarantees that at least one of them is `complete' after
	 * any necessary alignment.  For instance:
	 *
	 *	|-----------|-----------|-----------|
	 *	|00|01|02|03|04|05|06|07|08|09|0A|00|
	 *	          ^---------------------^
	 *		 dst		 dst+length-1
	 *
	 * but we use a minimum of 3 here since the overhead of the code
	 * to do word writes is substantial.
	 */
	if (length < 3 * wsize) {
		while (length != 0) {
			*dst++ = VAL;
			--length;
		}
		return dst0;
	}

	if ((c = (unsigned char)c0) != 0) {	/* Fill the word. */
		c = (c << 8) | c;	/* unsigned int is 16 bits. */
#if UINT_MAX > 0xffff
		c = (c << 16) | c;	/* unsigned int is 32 bits. */
#endif
#if UINT_MAX > 0xffffffff
		c = (c << 32) | c;	/* unsigned int is 64 bits. */
#endif
	}
	/* Align destination by filling in bytes. */
	if ((t = (long)dst & wmask) != 0) {
		t = wsize - t;
		length -= t;
		do {
			*dst++ = VAL;
		} while (--t != 0);
	}

	/* Fill words.  Length was >= 2*words so we know t >= 1 here. */
	t = length / wsize;
	do {
		*(unsigned int *)dst = WIDEVAL;
		dst += wsize;
	} while (--t != 0);

	/* Mop up trailing bytes, if any. */
	t = length & wmask;
	if (t != 0)
		do {
			*dst++ = VAL;
		} while (--t != 0);
	return dst0;
}

__attribute__((weak))
void *memmove(void *s1, const void *s2, size_t n)
{
	return memcpy(s1, s2, n);
}

__attribute__((weak))
int memcmp(const void *ptr1, const void *ptr2, size_t count) {
	const unsigned char *s1 = (const unsigned char*)ptr1;
	const unsigned char *s2 = (const unsigned char*)ptr2;

	while (count-- > 0)
	{
		if (*s1++ != *s2++)
			return s1[-1] < s2[-1] ? -1 : 1;
	}
	return 0;
}

__attribute__((weak))
char *strcpy(char *dst, const char *src) {
    const size_t length = strlen(src);
    memcpy(dst, src, length+1);
    return dst;
}


__attribute__((weak))
int strcmp(const char *s1, const char *s2) {
	while (*s1 == *s2++)
		if (*s1++ == '\0')
			return (0);
	return (*(const unsigned char *)s1 - *(const unsigned char *)(s2 - 1));
}

__attribute__((weak))
size_t strlen(const char *str) {
	const char *s;

	for (s = str; *s; ++s);
	return(s - str);
}

__attribute__((weak))
bool is_delim(char c, char *delim) {
	while(*delim != '\0') {
		if(c == *delim)
			return true;
		delim++;
	}

	return false;
}


__attribute__((weak))
size_t strcspn(const char *s1, const char *s2) {
	const char *sc1, *sc2;
	for (sc1 = s1; *sc1 != '\0'; ++sc1) {
		for (sc2 = s2; *sc2 != '\0'; ++sc2) {
			if (*sc1 == *sc2)
				return (sc1 - s1);
		}
	}
	return (sc1 - s1);
}

__attribute__((weak))
size_t strspn(const char *s1, const char *s2) {
	const char *sc1, *sc2;
	for (sc1 = s1; *sc1 != '\0'; ++sc1) {
		for (sc2 = s2; ; ++sc2) {
			if (*sc2 == '\0') {
				return (sc1 - s1);
			} else if (*sc1 == *sc2) {
				break;
			}
		}
	}   
	return (sc1 - s1);
}

__attribute__((weak))
char *strtok(char *string, const char *delim, char **savePtr) {
	char *end;

	if (string == NULL) {
		string = *savePtr;
	}

	if (*string == '\0') {
		*savePtr = string;
		return NULL;
	}

	/* Scan leading delimiters.  */
	string += strspn(string, delim);
	if (*string == '\0'){
		*savePtr = string;
		return NULL;
	}

	/* Find the end of the token.  */
	end = string + strcspn(string, delim);
	if (*end == '\0') {
		*savePtr = end;
		return string;
	}

	/* Terminate the token and make *SAVE_PTR point past it.  */
	*end = '\0';
	*savePtr = end + 1;
	return string;
}



#ifdef __cplusplus
}
#endif
