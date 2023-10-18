#include <stdio.h>

int plus(int n); //함수 선언

int main(void)
{
	int input; //정수형 변수 선언
	printf("1에서 n까지의 합: ");
	scanf_s("%d", &input);

	printf("1에서 %d까지의 합은 %d 입니다.\n", input, plus(input)); //1에서 n까지의 합 출력

	return 0;
}

int plus(int n)
{
	static int i = 0; //정적 변수 선언
	i++;

	if (n == 1)
	{
		printf("재귀함수가 호출된 횟수: %d번 입니다.\n", i); //재귀함수가 호출된 횟수 출력
		return 1;
	}
	else
	{
		return n + plus(n - 1); //재귀함수를 이용해 합 계산
	}
}