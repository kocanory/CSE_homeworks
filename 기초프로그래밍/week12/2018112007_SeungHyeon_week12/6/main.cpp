#include <stdio.h>
#include <string.h>

int main(void)
{
	char a[100];//�迭����
	printf("�� �ܾ �Է��ϼ���. -> ");
	gets_s(a, sizeof(a));//�迭�� �迭�� ������ ���� �ҷ�����

	int size = strlen(a); //������ ������ �����ϰ�, �迭�� ���̰��� ����

	printf("�Է��� �ܾ �ݴ�� ����մϴ�. ->");

	for (int i = size; i >= 0; i--)
	{
		printf("%c", a[i]); //���ڸ� �������� ���
	}

	printf("\n");
}