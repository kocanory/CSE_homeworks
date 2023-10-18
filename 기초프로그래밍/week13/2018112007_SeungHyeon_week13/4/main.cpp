#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int input, system; //정수형 변수 선언
	printf("가위(0) 바위(1) 보(2) 중에서 하나 입력 -> ");
	scanf_s("%d", &input);

	srand((long)time(NULL));
	system = rand() % 3 + 0; //난수 대입

	switch (input)
	{
	case 0:
		if (system == 0)
		{
			printf("당신은 가위이고, 시스템은 가위입니다.\n\n");
			printf("무승부입니다.\n");
		}
		else if (system == 1)
		{
			printf("당신은 가위이고, 시스템은 바위입니다.\n\n");
			printf("당신의 패배입니다.\n");
		}
		else if (system ==2)
		{
			printf("당신은 가위이고, 시스템은 보입니다.\n\n");
			printf("당신의 승리입니다.\n");
		}
			
		break; //자신이 입력한 값이 0일때 시스템이 출력하는 값에 따라 결과 출력

	case 1:
		if (system == 0)
		{
			printf("당신은 바위이고, 시스템은 가위입니다.\n\n");
			printf("당신의 승리입니다.\n");
		}
		else if (system == 1)
		{
			printf("당신은 바위이고, 시스템은 바위입니다.\n\n");
			printf("무승부입니다.\n");
		}
		else if (system == 2)
		{
			printf("당신은 바위이고, 시스템은 보입니다.\n\n");
			printf("당신의 패배입니다.\n");
		}

		break;//자신이 입력한 값이 1일때 시스템이 출력하는 값에 따라 결과 출력

	case 2:
		if (system == 0)
		{
			printf("당신은 보이고, 시스템은 가위입니다.\n\n");
			printf("당신의 패배입니다.\n");
		}
		else if (system == 1)
		{
			printf("당신은 보이고, 시스템은 바위입니다.\n\n");
			printf("당신의 승리입니다.\n");
		}
		else if (system == 2)
		{
			printf("당신은 보이고, 시스템은 보입니다.\n\n");
			printf("무승부입니다.\n");
		}

		break;//자신이 입력한 값이 2일때 시스템이 출력하는 값에 따라 결과 출력

	}

}