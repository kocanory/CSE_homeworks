#include <stdio.h>

int main(void)
{
	double a, b;
	printf("사각형의 가로, 세로 길이: ");
	scanf_s("%lf %lf", &a, &b);

	double S = a * b;

	printf("사각형의 넓이: %12.3lf\n", S);

	return 0;
}