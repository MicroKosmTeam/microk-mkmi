#include <mkmi_string.h>

char *strcpy(char *strDest, const char *strSrc){
        if(strDest==NULL || strSrc==NULL) return NULL;
        char *temp = strDest;
        while(*strDest++ = *strSrc++);
        return temp;
}

int strcmp(const char *s1, const char *s2) {
        const unsigned char *p1 = (const unsigned char *)s1;
        const unsigned char *p2 = (const unsigned char *)s2;

        while (*p1 != '\0') {
                if (*p2 == '\0') return  1;
                if (*p2 > *p1)   return -1;
                if (*p1 > *p2)   return  1;

                p1++;
                p2++;
        }

        if (*p2 != '\0') return -1;

        return 0;
}

size_t strlen(const char *str) {
        const char *s;
        for (s = str; *s; ++s);
        return (s - str);
}

void itoa(char *buf, char base, long long int num) {
	char *p = buf;
	char *p1, *p2;
	size_t ud = num;
	int divisor = 10;

	/*  If %d is specified and D is minus, put ‘-’ in the head. */
	if (base == 'd' && num < 0) {
		*p++ = '-';
		buf++;
		ud = -num;
	} else if (base == 'x')
		divisor = 16;

	/*  Divide UD by DIVISOR until UD == 0. */
	do {
		int remainder = ud % divisor;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
	} while (ud /= divisor);

	/*  Terminate BUF. */
	*p = 0;

	/*  Reverse BUF. */
	p1 = buf;
	p2 = p - 1;

	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
}
