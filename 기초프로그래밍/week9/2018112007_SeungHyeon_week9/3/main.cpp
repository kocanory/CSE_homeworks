#include <stdio.h>

int main(void)
{
	int data1 = 10, data2 = 20; //������ ���� data1, data2 ����
	int *p1 = &data1, *p2 = &data2; //������ ������ ���� p1�� p2�� �����ϰ�, ���� data1�� data2�� �ּ� ����

	int sum = 0; //������ ���� sum ����
	int **dp = &p1; //���� ������ dp����
	**dp = 100; //**dp�� ���� 100�� �ǵ��� ��
	sum += **dp; //sum = sum + **dp = sum + *p1 = sum + data1 = 0 + 100 = 100

	dp = &p2; //���� ������ dp�� p2�� �ּ� ���� 
	**dp = 200; //**dp�� ���� 200�� �ǵ��� ��
	sum += **dp; //sum = sum + **dp = sum + *p1 = sum + data2 = 100 + 200 = 300

	printf("�� ������ ��: %d\n", sum); //�� ������ ���� ���

	return 0;
}