#include <stdio.h>

static int input = 10; //정적 전역변수 선언

void outfunction()
{
	printf("정적 전역변수 input의 값: %d\n", input);//정적 전역변수 출력
}