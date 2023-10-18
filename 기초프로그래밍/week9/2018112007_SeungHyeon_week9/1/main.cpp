#include <stdio.h>

int main(void)
{
	char c = '*'; //문자형 변수 정의
	char *ptrchar = &c; //문자형 포인터 변수 ptrchar 정의하고, 변수 ptrchar에 변수 c의 주소를 저장

	printf("코드값: %d, 주소값: %d, 문자: %c\n", c, &c, c);//변수 c의 코드값, 주소값, 문자 출력

	return 0;
}