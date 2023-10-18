#include <stdio.h>

int main(void)
{
	int income;
	printf("종합소득(만원): ");
	scanf_s("%d", &income);

	if (income <= 1200)
	{
		double tax = income * 6 / 100;
		printf("세금: %.3lf만원\n", tax);
	}

	else if (1200 < income&&income <= 4600)
	{
		double tax = income * 15 / 100;
		printf("세금: %.3lf만원\n", tax);
	}

	else if (4600 < income&&income <= 8800)
	{
		double tax = income * 24 / 100;
		printf("세금: %.3lf만원\n", tax);
	}

	else if (8800 < income&&income <= 30000)
	{
		double tax = income * 35 / 100;
		printf("세금: %.3lf만원\n", tax);
	}

	else if (income >= 30000)
	{
		double tax = income * 38 / 100;
		printf("세금: %.3lf만원\n", tax);
	}

	return 0;
}