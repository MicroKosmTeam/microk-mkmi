#include <mkmi_string.h>

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
