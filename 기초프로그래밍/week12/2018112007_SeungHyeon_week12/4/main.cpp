#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void delchar(char str[], const char ch); //�Լ� ����

int main(void)
{
	char str[20]; //�迭 ����
	char ch = 'a'; //������ ���� ����

	strcpy(str, "java"); //�Լ� strcpy�� �̿��� ���� str�� "java"�� ������ 
	delchar(str, ch); //�Լ��� str���� ch���� ����
}

void delchar(char str[], const char ch)
{
	int i = 0;
	
	while (str[i] != NULL) //NULL�κ��� ������ �迭�� �� 
	{
		if (str[i] == ch)//���࿡ �迭�� 'a'�� �ִٸ�
		{
			for (int k = i; str[k] != NULL; k++)
			{
				str[k] = str[k + 1]; //�� �迭���� ���������� ��ĭ�� �̵��� a�κ��� ������ ��ó�� ���̰� ��
			
			}
		}

		i++;//i�� ����
	}

	printf("���: %s\n", str); // 'a'���� �����ϰ� ���� ���� ���
}