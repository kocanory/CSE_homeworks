#include <stdio.h>

int main(void)
{
	char input;
	printf("입력한 문자: ");
	scanf_s("%c", &input);

	printf("문자: %c, 8진수 코드값: %#o, 10진수 코드값: %d, 16진수 코드값: %#x\n",input, input, input, input);

	return 0;

}