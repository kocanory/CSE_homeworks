#include <stdio.h>

int main(void)
{
	int data1 = 10, data2 = 20; //정수형 변수 data1, data2 정의
	int *p1 = &data1, *p2 = &data2; //정수형 포인터 변수 p1과 p2를 정의하고, 각각 data1과 data2의 주소 저장

	int sum = 0; //정수형 변수 sum 정의
	int **dp = &p1; //이중 포인터 dp정의
	**dp = 100; //**dp의 값이 100이 되도록 함
	sum += **dp; //sum = sum + **dp = sum + *p1 = sum + data1 = 0 + 100 = 100

	dp = &p2; //이중 포인터 dp에 p2의 주소 저장 
	**dp = 200; //**dp의 값이 200이 되도록 함
	sum += **dp; //sum = sum + **dp = sum + *p1 = sum + data2 = 100 + 200 = 300

	printf("두 정수의 합: %d\n", sum); //두 정수의 합을 출력

	return 0;
}