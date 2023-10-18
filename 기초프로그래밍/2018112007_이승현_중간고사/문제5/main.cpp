#include <stdio.h>

int main(void)
{
	double length;
	printf("길이(cm): ");
	scanf_s("%lf", &length);

	double feetlength = length / 30.48;
	printf("길이(feet): %.3lf\n", feetlength);

	return 0;
}