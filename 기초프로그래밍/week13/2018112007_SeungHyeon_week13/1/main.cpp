#include <stdio.h>

int plus(int n); //�Լ� ����

int main(void)
{
	int input; //������ ���� ����
	printf("1���� n������ ��: ");
	scanf_s("%d", &input);

	printf("1���� %d������ ���� %d �Դϴ�.\n", input, plus(input)); //1���� n������ �� ���

	return 0;
}

int plus(int n)
{
	static int i = 0; //���� ���� ����
	i++;

	if (n == 1)
	{
		printf("����Լ��� ȣ��� Ƚ��: %d�� �Դϴ�.\n", i); //����Լ��� ȣ��� Ƚ�� ���
		return 1;
	}
	else
	{
		return n + plus(n - 1); //����Լ��� �̿��� �� ���
	}
}