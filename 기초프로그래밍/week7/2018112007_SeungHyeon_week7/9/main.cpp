#include <stdio.h>

int main(void)
{
	int origin = 1000000, y; //정수형 변수 설정
	
	for (y = 1; y <= 10; y++) //1년부터 10년까지 총 수령액 계산하도록 조건 설정
	{
		double money = origin * (1 + 4.5 / 100 * y); //총 수령액을 구하는 공식 정의
		printf("%d년 말에 받을수 있는 수령액: %.1f", y, money); //총 수령액을 출력
		puts("");

	}

	return 0;
}