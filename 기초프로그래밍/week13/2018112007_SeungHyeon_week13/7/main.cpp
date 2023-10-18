#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int number, input, trycount; //정수형 변수 선언
static int min = 1, max = 100;//정적 변수 선언
void setNumber();//함수 선언
void printHead();//함수 선언
void printHigher();//함수 선언
void printLower();//함수 선언
void printAnswer();//함수 선언

int main(void)
{
	setNumber(); //함수 출력
	printHead(); //함수 출력

	while (1)
	{
		trycount++; //시도 회수 증가
		if (input < number)
		{
			printLower(); //입력값이 난수값보다 작을 때 함수 출력
		}

		else if (input > number)
		{
			printHigher(); //입력값이 난수값보다 클 때 함수 출력
		}

		else 
		{
			printAnswer(); //입력값이 난수값과 같을 때 함수 출력
			break;
		}

		if (trycount == 4)
		{
			printf("5번의 기회를 사용하셨습니다. 난수는 %d 입니다.\n", number);
			break; //5번 시도해서 맞추지 못했을 때, 출력
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
	min = input + 1;
	printf("<%d>. 맞추어야 할 정수가 입력한 정수 %d 보다 큽니다.\n", trycount, input);
	printf("%d 에서 %d 사이의 정수를 다시 입력하세요. > ", min, max);
	scanf_s("%d", &input);
	puts("");
}

void printHigher()
{
	max = input - 1;
	printf("<%d>. 맞추어야 할 정수가 입력한 정수 %d 보다 작습니다.\n", trycount, input);
	printf("%d 에서 %d 사이의 정수를 다시 입력하세요. > ", min, max);
	scanf_s("%d", &input);
	puts("");
}

void printAnswer()
{
	printf("축하합니다! 정답은 %d 입니다.\n", number); //정답 메세지 출력
}