#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char a[100]; //�迭����
	printf("�� ���� ������ �Է��ϼ���. -> \n");
	gets_s(a, sizeof(a));//�迭�� �迭�� ������ ���� �ҷ�����

	printf("�Է��� ������ �ܾ �ݴ�� ����մϴ�. -> \n");

	char *word = strtok(a," "); //" "�� �����ڷ� ������ ��ū�� �и���

	while (word != NULL) //NULL�κ��� ������ �κ�
	{
		int size = strlen(word) - 1; //" "�� ����� �� ������ ������ȣ ����
		for (int i = size; i >= 0; i--)
		{
			printf("%c", word[i]);//��ū���� ���ڸ� �������� ���
		}

		printf(" ");
		word = strtok(NULL," ");//�ι�° ȣ����� ù ���ڸ� NULL�� ȣ���Ѵ�.
	}
	
	printf("\n");
}
