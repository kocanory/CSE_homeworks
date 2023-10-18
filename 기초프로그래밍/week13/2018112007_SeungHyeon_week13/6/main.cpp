#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int number, input; //������ ���� ����
static int min = 1, max = 100; //���� ���� ����
void setNumber();//�Լ�����
void printHead();//�Լ�����
void printHigher();//�Լ�����
void printLower();//�Լ�����
void printAnswer(); //�Լ�����

int main(void)
{
	setNumber(); //�Լ� ���
	printHead(); //�Լ� ���

	while (1)
	{
		if (input < number)
		{
			printLower(); //�Է°��� ���������� ���� �� �Լ� ���
		}

		else if (input > number)
		{
			printHigher();//�Է°��� ���������� Ŭ �� �Լ� ���
		}

		else
		{
			printAnswer();//�Է°��� �������� ������ �Լ� ���
			break;
		}
	}

}

void printHead()
{
	printf("1 ���� 100 ������ �ϳ��� ������ �����Ǿ����ϴ�.\n�� ������ ���߾� ������? > ");
	scanf_s("%d", &input);
	puts("");
}




void setNumber()
{
	srand((long)time(NULL));
	number = rand() % 100 + 1; //���� ����
}

void printLower()
{
	min = input + 1; //�ּҰ��� �Է°����� 1 ũ�� ��
	printf("���߾�� �� ������ �Է��� ���� %d ���� Ů�ϴ�.\n", input);
	printf("%d ���� %d ������ ������ �ٽ� �Է��ϼ���. > ", min, max);
	scanf_s("%d", &input);
	puts("");
}

void printHigher()
{
	max = input - 1; //�ִ밪�� �Է°����� 1 �۰� ��
	printf("���߾�� �� ������ �Է��� ���� %d ���� �۽��ϴ�.\n", input);
	printf("%d ���� %d ������ ������ �ٽ� �Է��ϼ���. > ", min, max);
	scanf_s("%d", &input);
	puts("");
}

void printAnswer()
{
	printf("�����մϴ�! ������ %d �Դϴ�.\n", number); //�����϶� �޼��� ���
}