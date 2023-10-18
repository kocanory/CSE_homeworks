#include <stdio.h>

int main(void)
{
	int z; //정수변수 z 정의
	int answer = 10; //정수변수 answer를 정의하고, 변수에 10을 입력함.

	printf("추측한 수: ");
	scanf_s("%d", &z); //입력한 정수값을 불러들임

	if (20 >= z&&z > answer) // 입력한 정수값이 정답보다 클 경우 정답보다 크다는 메세지 출력
	{
		printf("정답보다 큽니다.\n");
	}
	
	else if ( z < answer) //입력한 정수값이 정답보다 작을 경우 정답보다 작다는 메세지 출력
	{
		printf("정답보다 작습니다.\n");
	}
	
	else if (z > 20) //입력한 정수값이 20보다 클 경우 오류메세지 출력
	{
		printf("정의 되지 않았습니다.\n");
	}
	
	else if (z = answer) //입력한 정수값이 정답과 같을경우 정답이라는 메세지 출력
	{
		printf("정답입니다!\n");
	}

	

	return 0;
}