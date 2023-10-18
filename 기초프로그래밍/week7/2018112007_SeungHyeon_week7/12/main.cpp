#include <stdio.h>

int main(void)
{
	int C;
	

	for (C = -60; C <= 140; C += 20) //섭씨온도 -60도부터 20도씩 올라가 140에 반복이 멈추도록 설정
	{
		int	F = (9.0 / 5.0) * C + 32; //화씨온도를 구하는 공식을 정의
		printf("화씨온도는 %d입니다.", F); //구한 화씨온도의 값을 출력
		puts("");
	}

	return 0;
}