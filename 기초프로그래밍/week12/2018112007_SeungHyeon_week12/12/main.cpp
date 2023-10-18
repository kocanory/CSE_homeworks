#include <stdio.h>
#include <string.h>
#include <ctype.h>

void convert(char *str);//함수 선언

int main(void)
{
	char a[150];//배열 선언
	printf("영문 문장을 입력하세요. -> \n");
	gets_s(a);//배열을 불러들임

	convert(a); //함수에 a값을 대입
	printf("\n위에서 입력한 문자열에서 대문자와 소문자를 반대로 변환하면 -> \n");
	printf("%s\n", a);//배열 출력
}

void convert(char *str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (65 <= str[i] & str[i] <= 90)
			str[i] = tolower(str[i]); //대문자일 경우 소문자로 바꿔서 출력
		else if (97 <= str[i] & str[i] <= 122)
			str[i] = toupper(str[i]); //소문자일 경우 대문자로 바꿔서 출력
		else
			continue;
	}
}

