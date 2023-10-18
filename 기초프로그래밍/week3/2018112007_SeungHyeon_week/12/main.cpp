#include <stdio.h>

int main(void)
{
	enum c { ca = -10, cb = 5, cc = 15, cd = 25, ce = 35 }; //섭씨온도를 enum을 이용해 나열합니다.
	float fa = (9.0 / 5.0) * ca + 32.0;
	float fb = (9.0 / 5.0) * cb + 32.0;
	float fc = (9.0 / 5.0) * cc + 32.0;
	float fd = (9.0 / 5.0) * cd + 32.0;
	float fe = (9.0 / 5.0) * ce + 32.0; //각각 나열한 섭씨온도에 대하여 화씨온도를 계산합니다.
		

	printf("%f %f %f %f %f\n", fa, fb, fc, fd, fe); //화씨온도를 나열된 채로 출력합니다.
}