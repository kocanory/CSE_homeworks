#include <stdio.h>

int main(void)
{
	float h, w, BMI; //실수변수 h, W, BMI 정의

	printf("신장(m)과 몸무게(kg): ");
	scanf_s("%f %f", &h, &w); // 신장과 몸무게 값을 불러들임

	BMI = w / (h * h); //BMI식을 정의

	printf("BMI지수: %f\n", BMI);

	if (BMI < 18.5) //BMI가 18.5이하일 때 저체중이라는 메세지 출력
	{
		printf("저체중입니다.\n");
	}

	else if (18.5 <= BMI&&BMI < 22.9) //BMI가 18.5이상 22.9 이하일 때 정상이라는 메세지 출력
	{
		printf("정상입니다.\n");
	}

	else if (23.0 <= BMI&&BMI < 24.9) //BMI가 23이상 24.9이하일 때 과체중이라는 메세지 출력
	{
		printf("과체중입니다.\n");
	}
	
	else if (25.0 <= BMI&&BMI < 29.9) //BMI가 25이상 29.9이하일 때 경도비만이라는 메세지 출력
	{
		printf("경도비만입니다.\n");
	}

	else //BMI가 30이상일 때 중등도비만이라는 메세지 출력
	{
		printf("중등도비만입니다.\n");
	}

	return 0;
}