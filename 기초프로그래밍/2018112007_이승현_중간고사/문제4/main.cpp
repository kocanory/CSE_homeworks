#include <stdio.h>

int main(void)
{
	double a, b;
	printf("�簢���� ����, ���� ����: ");
	scanf_s("%lf %lf", &a, &b);

	double S = a * b;

	printf("�簢���� ����: %12.3lf\n", S);

	return 0;
}