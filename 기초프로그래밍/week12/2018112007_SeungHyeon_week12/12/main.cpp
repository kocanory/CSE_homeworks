#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convert(char *str);//�Լ� ����

int main(void)
{
	char a[150];//�迭 ����
	printf("���� ������ �Է��ϼ���. -> \n");
	gets_s(a);//�迭�� �ҷ�����

	convert(a); //�Լ��� a���� ����
	printf("\n������ �Է��� ���ڿ����� �빮�ڿ� �ҹ��ڸ� �ݴ�� ��ȯ�ϸ� -> \n");
	printf("%s\n", a);//�迭 ���
}

void convert(char *str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (65 <= str[i] & str[i] <= 90)
			str[i] = tolower(str[i]); //�빮���� ��� �ҹ��ڷ� �ٲ㼭 ���
		else if (97 <= str[i] & str[i] <= 122)
			str[i] = toupper(str[i]); //�ҹ����� ��� �빮�ڷ� �ٲ㼭 ���
		else
			continue;
	}
}

