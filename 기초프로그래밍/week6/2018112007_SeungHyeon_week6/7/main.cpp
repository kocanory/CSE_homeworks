#include <stdio.h>

int main(void)
{
	int income; //정수변수 income 정의
	float tax; //실수변수 tax 정의

	printf("종합소득(만원): ");
	scanf_s("%d", &income); //입력한 정수값을 불러들임

	if (income <= 1200) //종합소득이 1200만원 이하일경우 과세금액 계산식을 정의하고, 계산한 세금값을 출력
	{
		tax = income * 6.0f / 100.0f;
			
		printf("세금: %f만원\n", tax);
	}

	else if (1200 < income&&income <= 4600) //종합소득이 1200만원 이상 4600만원 이하일 경우 과세금액 계산식을 정의하고, 계산한 세금값을 출력
	{
		tax = 72 + (income - 1200) * 15.0f / 100.0f;

		printf("세금: %f만원\n", tax);
	}

	else if (4600 < income&&income <= 8800) //종합소득이 4600만원 이상 8800만원 이하일 경우 과세금액 계산식을 정의하고, 계산한 세금값을 출력
	{
		tax = 582 + (income - 4600) * 24.0f / 100.0f;

		printf("세금: %f만원\n", tax);

	}

	else if (8800 < income&&income <= 30000) //종합소득이 8800만원 이상 3억 이하일 경우 과세금액 계산식을 정의하고, 계산한 세금값을 출력
	{
		tax = 1590 + (income - 8800) * 35.0f / 100.0f;

		printf("세금: %f만원\n", tax);
	}

	else
	{
		tax = 9010 + (income - 30000) * 38.0f / 100.0f; //종합소득이 3억 이상일 경우 과세금액 계산식을 정의하고, 계산한 세금값을 출력

		printf("세금: %f만원\n", tax);
	}

	return 0;
}