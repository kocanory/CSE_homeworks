#include <stdio.h>

int main(void)
{
	int month; //정수변수 month 정의

	printf("월(month): ");
	scanf_s("%d", &month); //입력한 정수값을 불러들임

	if (1 <= month&&month <= 3 ) //입력한 달이 1월에서 3월일경우 1사분기임을 출력
	{
		printf("1사분기 입니다.\n");
	}

	else if (4 <= month&&month <= 6) //입력한 달이 4월에서 6월일경우 2사분기임을 출력
	{
		printf("2사분기 입니다.\n");
	}

	else if (7 <= month&&month <= 9) //입력한 달이 7월에서 9월일경우 3사분기임을 출력
	{
		printf("3사분기 입니다.\n");
	}

	else if (10 <= month&&month <= 12) //입력한 달이 10월에서 12월일경우 4사분기임을 출력
	{
		printf("4사분기 입니다.\n");
	}

	else //1월에서 12월 이외의 값을 입력할 경우 오류메세지 출력
	{
		printf("지구가 아닙니다.\n"); 
	}

	return 0;
}