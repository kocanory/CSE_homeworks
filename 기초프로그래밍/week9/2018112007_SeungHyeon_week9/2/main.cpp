#include <stdio.h>

int main(void)
{
	int data1 = 10, data2 = 20; //������ ���� data1, data2 ����
	int sum = 0; //������ ���� sum ����

	int *p = &data1; //������ ������ ���� p�� �����ϰ�, data1�� �ּ� ����
	*p = 100; //������ ���� p���� 100�� �ǵ��� ��
	sum += *p; // sum = sum + *p = 0 + 100 = 100

	 p = &data2; //������ ���� p�� data1�� �ּ� ����
	*p = 200; //������ ���� p���� 200�� �ǵ��� ��
	sum += *p; // sum = sum + *p = 100 + 200 = 300

	printf("�� ������ ��: %d\n", sum); //�� ������ ���� ���

	return 0;
}