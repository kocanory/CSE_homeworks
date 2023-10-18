#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

void delchar(char str[], const char ch); //함수 선언

int main(void)
{
	char str[20]; //배열 선언
	char ch = 'a'; //문자형 변수 선언

	strcpy(str, "java"); //함수 strcpy를 이용해 변수 str에 "java"를 복사함 
	delchar(str, ch); //함수에 str값과 ch값을 대입
}

void delchar(char str[], const char ch)
{
	int i = 0;
	
	while (str[i] != NULL) //NULL부분을 제외한 배열일 때 
	{
		if (str[i] == ch)//만약에 배열에 'a'가 있다면
		{
			for (int k = i; str[k] != NULL; k++)
			{
				str[k] = str[k + 1]; //각 배열에서 오른쪽으로 한칸씩 이동해 a부분을 삭제한 것처럼 보이게 함
			
			}
		}

		i++;//i값 증가
	}

	printf("결과: %s\n", str); // 'a'값을 삭제하고 남은 값을 출력
}