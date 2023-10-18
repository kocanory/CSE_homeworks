#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void mystrcat(char s1[], const char s2[]); //함수 선언

int main(void)
{
	char s1[50] = "C "; //배열을 선언하고, 'C'를 저장
	mystrcat(s1, "programming language"); //함수에 s1rhk "programming language'를 대입
}

void mystrcat(char s1[], const char s2[])
{
	printf("%s", strcat(s1, s2)); //함수 strcat을 이용해 s1과 s2를 이어서 출력
	printf("\n");
}