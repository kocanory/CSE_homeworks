#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int input, system; //������ ���� ����
	printf("����(0) ����(1) ��(2) �߿��� �ϳ� �Է� -> ");
	scanf_s("%d", &input);

	srand((long)time(NULL));
	system = rand() % 3 + 0; //���� ����

	switch (input)
	{
	case 0:
		if (system == 0)
		{
			printf("����� �����̰�, �ý����� �����Դϴ�.\n\n");
			printf("���º��Դϴ�.\n");
		}
		else if (system == 1)
		{
			printf("����� �����̰�, �ý����� �����Դϴ�.\n\n");
			printf("����� �й��Դϴ�.\n");
		}
		else if (system ==2)
		{
			printf("����� �����̰�, �ý����� ���Դϴ�.\n\n");
			printf("����� �¸��Դϴ�.\n");
		}
			
		break; //�ڽ��� �Է��� ���� 0�϶� �ý����� ����ϴ� ���� ���� ��� ���

	case 1:
		if (system == 0)
		{
			printf("����� �����̰�, �ý����� �����Դϴ�.\n\n");
			printf("����� �¸��Դϴ�.\n");
		}
		else if (system == 1)
		{
			printf("����� �����̰�, �ý����� �����Դϴ�.\n\n");
			printf("���º��Դϴ�.\n");
		}
		else if (system == 2)
		{
			printf("����� �����̰�, �ý����� ���Դϴ�.\n\n");
			printf("����� �й��Դϴ�.\n");
		}

		break;//�ڽ��� �Է��� ���� 1�϶� �ý����� ����ϴ� ���� ���� ��� ���

	case 2:
		if (system == 0)
		{
			printf("����� ���̰�, �ý����� �����Դϴ�.\n\n");
			printf("����� �й��Դϴ�.\n");
		}
		else if (system == 1)
		{
			printf("����� ���̰�, �ý����� �����Դϴ�.\n\n");
			printf("����� �¸��Դϴ�.\n");
		}
		else if (system == 2)
		{
			printf("����� ���̰�, �ý����� ���Դϴ�.\n\n");
			printf("���º��Դϴ�.\n");
		}

		break;//�ڽ��� �Է��� ���� 2�϶� �ý����� ����ϴ� ���� ���� ��� ���

	}

}