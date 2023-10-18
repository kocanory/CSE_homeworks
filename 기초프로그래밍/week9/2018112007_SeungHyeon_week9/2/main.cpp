#include <stdio.h>

int main(void)
{
	int data1 = 10, data2 = 20; //정수형 변수 data1, data2 정의
	int sum = 0; //정수형 변수 sum 정의

	int *p = &data1; //정수형 포인터 변수 p를 정의하고, data1의 주소 저장
	*p = 100; //포인터 변수 p값이 100이 되도록 함
	sum += *p; // sum = sum + *p = 0 + 100 = 100

	 p = &data2; //포인터 변수 p에 data1의 주소 저장
	*p = 200; //포인터 변수 p값이 200이 되도록 함
	sum += *p; // sum = sum + *p = 100 + 200 = 300

	printf("두 정수의 합: %d\n", sum); //두 정수의 합을 출력

	return 0;
}