#include <stdio.h>

int main(void)
{
	
	int i, k, sum; //정수형 변수 정의
	printf("입력받은 수: ");
	scanf_s("%d", &i); //입력한 정수값을 불러들임
	
	for (k = 1, sum = 0; k <= i; k++) //for문의 반복조건 정의
	{
		sum += k; //1에서 입력한 정수까지의 합 공식 정의
	}
	printf("1에서 입력받은 정수까지의 합: %d\n", sum); //1에서 입력한 정수까지의 합의 값을 출력
	
	return 0;
}