#include <stdio.h>

int main(void)
{
	long int a = 117900000; //�¾�� ȭ������ �Ÿ��� ���� a�� �����մϴ�.
	long int b = 2871000000; //�¾�� õ�ռ����� �Ÿ��� ���� b�� �����մϴ�.
	long int difference; //���� difference�� ����ϴ�.

	difference = b - a; //���� difference�� ���� ����ϴ�.

	printf("%lld\n", difference); //difference�� ���� ����մϴ�.

	return 0;

}