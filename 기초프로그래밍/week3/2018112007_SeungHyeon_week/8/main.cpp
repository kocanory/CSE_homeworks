#include <stdio.h>

int main(void)
{
	printf("%d %d %d\n", 1, 01, 0x1);
	printf("%d %d %d\n", 2, 02, 0x2);
	printf("%d %d %d\n", 3, 03, 0x3);
	printf("%d %d %d\n", 4, 04, 0x4);
	printf("%d %d %d\n", 5, 05, 0x5);
	printf("%d %d %d\n", 6, 06, 0x6);
	printf("%d %d %d\n", 7, 07, 0x7);
	printf("%d %d %d\n", 8, 010, 0x8);
	printf("%d %d %d\n", 9, 011, 0x9);
	printf("%d %d %d\n", 10, 012, 0x0A);
	printf("%d %d %d\n", 11, 013, 0x0B);
	printf("%d %d %d\n", 12, 014, 0x0C);
	printf("%d %d %d\n", 13, 015, 0x0D);
	printf("%d %d %d\n", 14, 016, 0x0E);
	printf("%d %d %d\n", 15, 017, 0x0F);
	printf("%d %d %d\n", 16, 020, 0x10); //1~16의 정수들을 10진수, 8진수, 16진수로 표현하고 그 값을 다시 10진수로 표현합니다ㅣ.

	return 0;
	

}