#include <stdio.h>

int main(void)
{
	double a, b;
	int input;

	printf("�� �Ǽ� �Է�: ");
	scanf_s("%lf %lf", &a, &b);

	printf("�������� ��ȣ���� 1(+), 2(-), 3(*), 4(/): ");
	scanf_s("%d", &input);

	switch (input)
	
	case 1:
	{
		printf("%.2lf + %.2lf = %.2lf\n", a, b, a + b);
		
		break;

	case 2:
		printf("%.2lf - %.2lf = %.2lf\n", a, b, a - b);

		break;

	case 3:
		printf("%.2lf * %.2lf = %.2lf\n", a, b, a * b);
	
		break;
	
	case 4:
		printf("%.2lf / %.2lf = %.2lf\n", a, b, a / b);
		
		break;
	}

	return 0;
}