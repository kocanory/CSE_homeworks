#include <stdio.h>

int main(void)
{
	int value = 0x2F24263F; //������ ���� ����
	char *pc = (char *) &value;//������ ������ ���� pc�� �����ϰ�, value�� �ּ� ����

	printf("����: %c %c %c %c\n", *pc, *(pc + 1), *(pc + 2), *(pc + 3)); //���� ���
	printf("�ּ�: %d %d %d %d\n", *pc, *(pc + 1), *(pc + 2), *(pc + 3)); //�ּҰ� ���

	return 0;
}