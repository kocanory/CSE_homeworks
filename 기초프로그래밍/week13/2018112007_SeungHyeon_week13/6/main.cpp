#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int number, input; //정수형 변수 선언
static int min = 1, max = 100; //정적 변수 선언
void setNumber();//함수선언
void printHead();//함수선언
void printHigher();//함수선언
void printLower();//함수선언
void printAnswer(); //함수선언

int main(void)
{
	setNumber(); //함수 출력
	printHead(); //함수 출력

	while (1)
	{
		if (input < number)
		{
			printLower(); //입력값이 난수값보다 작을 때 함수 출력
		}

		else if (input > number)
		{
			printHigher();//입력값이 난수값보다 클 때 함수 출력
		}

		else
		{
			printAnswer();//입력값이 난수값과 같을때 함수 출력
			break;
		}
	}

}

void printHead()
{
	printf("1 에서 100 까지의 하나의 정수가 결정되었습니다.\n이 정수를 맞추어 보세요? > ");
	scanf_s("%d", &input);
	puts("");
}




void setNumber()
{
	srand((long)time(NULL));
	number = rand() % 100 + 1; //난수 생성
}

void printLower()
{
	min = input + 1; //최소값을 입력값보다 1 크게 함
	printf("맞추어야 할 정수가 입력한 정수 %d 보다 큽니다.\n", input);
	printf("%d 에서 %d 사이의 정수를 다시 입력하세요. > ", min, max);
	scanf_s("%d", &input);
	puts("");
}

void printHigher()
{
	max = input - 1; //최대값을 입력값보다 1 작게 함
	printf("맞추어야 할 정수가 입력한 정수 %d 보다 작습니다.\n", input);
	printf("%d 에서 %d 사이의 정수를 다시 입력하세요. > ", min, max);
	scanf_s("%d", &input);
	puts("");
}

void printAnswer()
{
	printf("축하합니다! 정답은 %d 입니다.\n", number); //정답일때 메세지 출력
}