#include <stdio.h>

int main(void)
{
	int i = 0x324F3A24; //������ ���� ����
	char *p = (char *)&i; //������ ����ó ���� p����

	printf("%X%X%X%X\n", *(p + 3), *(p + 2), *(p + 1), *p); //���� i�� ���� 16���� �빮�ڷ� ���

	return 0;
}