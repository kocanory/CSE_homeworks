#include <stdio.h>

int input; //정수형 전역변수 선언 

void outfunction(void); //함수 선언

int main(void)
{
	printf("전역변수 input의 값: %d\n", input);//전역변수의 값 출력
	outfunction();//함수 출력
}

