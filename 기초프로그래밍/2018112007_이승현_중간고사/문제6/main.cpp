#include <stdio.h>

int main(void)
{
	double a, b, c;
	printf("입력한 세 수: ");
	scanf_s("%lf %lf %lf", &a, &b, &c);

	if (a > b)
	{
		if (a > c)
		{
			printf("가장 큰 수: %lf\n", a);
		}

		else if(c > a)
		{
			printf("가장 큰 수: %lf\n", c);
		}
	}
	
	else if (b > a)
	{
		if (b > c)
		{
			printf("가장 큰 수: %lf\n", b);
		}

		else if (c > b)
		{
			printf("가장 큰 수: %lf\n", c);
		}
	}

	return 0;
}