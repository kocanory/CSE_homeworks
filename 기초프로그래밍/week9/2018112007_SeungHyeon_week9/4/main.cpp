#include <stdio.h>

int main(void)
{
	int value = 0x2F24263F; //정수형 변수 정의
	char *pc = (char *) &value;//문자형 포인터 변수 pc를 정의하고, value의 주소 저장

	printf("문자: %c %c %c %c\n", *pc, *(pc + 1), *(pc + 2), *(pc + 3)); //문자 출력
	printf("주소: %d %d %d %d\n", *pc, *(pc + 1), *(pc + 2), *(pc + 3)); //주소값 출력

	return 0;
}