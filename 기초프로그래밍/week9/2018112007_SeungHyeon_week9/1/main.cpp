#include <stdio.h>

int main(void)
{
	char c = '*'; //������ ���� ����
	char *ptrchar = &c; //������ ������ ���� ptrchar �����ϰ�, ���� ptrchar�� ���� c�� �ּҸ� ����

	printf("�ڵ尪: %d, �ּҰ�: %d, ����: %c\n", c, &c, c);//���� c�� �ڵ尪, �ּҰ�, ���� ���

	return 0;
}