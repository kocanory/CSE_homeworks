#include <stdio.h>

int main(void)
{
#define PI 3.141592 //매크로변수 PI를 3.141592로 지정합니다.

 	double r = 7.58; //반지름을 변수 r에 저장합니다.
	double s = r * r * PI; //넓이 공식을 변수 s에 PI를 이용하여 저장합니다. 
	double c = 2 * r * PI; //둘레 공식을 변수 c에 PI를 이용하여 저장합니다.

	printf("넓이: %f\n", s); //구한 넓이를 출력합니다.
	printf("둘레: %f\n", c); //구한 둘레를 출력합니다.

	return 0;
}