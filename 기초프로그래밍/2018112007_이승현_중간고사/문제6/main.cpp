#include <stdio.h>

int main(void)
{
	double a, b, c;
	printf("�Է��� �� ��: ");
	scanf_s("%lf %lf %lf", &a, &b, &c);

	if (a > b)
	{
		if (a > c)
		{
			printf("���� ū ��: %lf\n", a);
		}

		else if(c > a)
		{
			printf("���� ū ��: %lf\n", c);
		}
	}
	
	else if (b > a)
	{
		if (b > c)
		{
			printf("���� ū ��: %lf\n", b);
		}

		else if (c > b)
		{
			printf("���� ū ��: %lf\n", c);
		}
	}

	return 0;
}