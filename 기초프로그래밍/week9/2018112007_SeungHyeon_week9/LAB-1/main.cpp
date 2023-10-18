#include <stdio.h>

int main(void)
{
	char c = '*';
	char *ptrchar;
	ptrchar = &c;

	printf("%d, %p, c\n", c, &c);

	return 0;
}