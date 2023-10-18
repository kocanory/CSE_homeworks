#include <stdio.h>

int main(void)
{
	int y = 0, m = 0;

	printf("해당년도와 달: ");
	scanf_s("%d %d", &y, &m); //입력한 두 값을 불러들임

	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) //윤년을 판단하는 if문을 설정

	{
		switch (m)
		{
		case 3: case 5: case 7: case 8: case 10: case 12: //입력한 달이 3월, 5월, 7월, 8월, 10월 ,12월일경우 월말이 31일임을 출력

			printf("월말은 31일입니다.\n");

			break; 

		case 2: //입력한 달이 2월일경우 월말이 29일임을 출력
			printf("월말은 29일입니다.\n");

			break;

		default: //그 외의 달은 월말이 30일임을 출력
			printf("월말은 30일 입니다.\n");

			break;
		}
	}
	else
	{
		switch (m)
		{
		case 3: case 5: case 7: case 8: case 10: case 12: //입력한 달이 3월, 5월, 7월, 8월, 10월 ,12월일경우 월말이 31일임을 출력

			printf("월말은 31일입니다.\n");

			break;

		case 2: //입력한 달이 3월, 5월, 7월, 8월, 10월 ,12월일경우 월말이 28일임을 출력
			printf("월말은 28일입니다.\n");

			break;

		default: //입력한 달이 3월, 5월, 7월, 8월, 10월 ,12월일경우 월말이 30일임을 출력
			printf("월말은 30일 입니다.\n");

			break;
		}
	}

	return 0;
}