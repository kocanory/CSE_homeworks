#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void mystrcat(char s1[], const char s2[]); //�Լ� ����

int main(void)
{
	char s1[50] = "C "; //�迭�� �����ϰ�, 'C'�� ����
	mystrcat(s1, "programming language"); //�Լ��� s1rhk "programming language'�� ����
}

void mystrcat(char s1[], const char s2[])
{
	printf("%s", strcat(s1, s2)); //�Լ� strcat�� �̿��� s1�� s2�� �̾ ���
	printf("\n");
}