#include <stdio.h>

int main(void)
{
	int origin = 1000000, y; //������ ���� ����
	
	for (y = 1; y <= 10; y++) //1����� 10����� �� ���ɾ� ����ϵ��� ���� ����
	{
		double money = origin * (1 + 4.5 / 100 * y); //�� ���ɾ��� ���ϴ� ���� ����
		printf("%d�� ���� ������ �ִ� ���ɾ�: %.1f", y, money); //�� ���ɾ��� ���
		puts("");

	}

	return 0;
}