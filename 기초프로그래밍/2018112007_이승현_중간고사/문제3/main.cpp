#include <stdio.h>

int main(void)
{
	char input;
	printf("�Է��� ����: ");
	scanf_s("%c", &input);

	printf("����: %c, 8���� �ڵ尪: %#o, 10���� �ڵ尪: %d, 16���� �ڵ尪: %#x\n",input, input, input, input);

	return 0;

}