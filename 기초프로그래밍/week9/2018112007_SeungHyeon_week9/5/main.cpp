#include <stdio.h>

int main(void)
{
	int i = 0x324F3A24; //정수형 변수 정의
	char *p = (char *)&i; //문자형 포인처 변수 p정의

	printf("%X%X%X%X\n", *(p + 3), *(p + 2), *(p + 1), *p); //변수 i의 값을 16진수 대문자로 출력

	return 0;
}