#include <stdio.h>

int main(void)
{
	long int a = 117900000; //태양과 화성간의 거리를 변수 a에 저장합니다.
	long int b = 2871000000; //태양과 천왕성간의 거리를 변수 b에 저장합니다.
	long int difference; //변수 difference를 만듭니다.

	difference = b - a; //변수 difference의 식을 만듭니다.

	printf("%lld\n", difference); //difference의 값을 출력합니다.

	return 0;

}