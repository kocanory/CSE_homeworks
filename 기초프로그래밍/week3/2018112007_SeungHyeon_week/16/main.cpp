#include <stdio.h>

int main(void)
{
#define PI 0.621371 //매크로 변수 PI를 이용해 km당 마일 값을 지정합니다.
	enum l {la = 60, lb = 80, lc = 100, ld = 120}; //enum을 이용해 각각의 길이를 나열합니다.

	float mla = la * PI;
	float mlb = lb * PI;
	float mlc = lc * PI;
	float mld = ld * PI; //각각의 길이에 대하여 마일로 변환합니다.

	printf("%f %f %f %f\n", mla, mlb, mlc, mld); //변환된 마일 값을 출력합니다.

	return 0;

}