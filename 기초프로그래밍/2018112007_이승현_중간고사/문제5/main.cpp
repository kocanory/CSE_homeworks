#include <stdio.h>

int main(void)
{
	double length;
	printf("����(cm): ");
	scanf_s("%lf", &length);

	double feetlength = length / 30.48;
	printf("����(feet): %.3lf\n", feetlength);

	return 0;
}