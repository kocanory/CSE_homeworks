#include <stdio.h>

int main(void)
{
	int ch = 126;

	printf("%d\n", ch);
	printf("%c\n", ch);
	printf("%c\n", '\176');
	printf("%c\n", '\x7e');

	return 0;
}