#include <stdio.h>
#include <string.h>

struct date //��¥�� ���� ����ü
{
	int year; //��
	int month; //��
	int day; //��
};

int main(void)
{
	typedef struct movie //�ڷ��� ������ 
	{
		char *title; //����
		int attendance; //������
		char director[20]; //����
		struct date open; //������
	} movie;

	movie box[] = {
		{"��", 17613000, "���ѹ�", {2014, 7, 30} }, {"���ϵ�", 12983000, "�ֵ���", {2014, 12, 17}},
		{"��������", 14257000, "���¿�", {2014, 12, 17}}, {"�����", 7074867, "���� ����", {2012, 4, 26}},
		{"���̾��", 4300365, "�� �к��", {2008, 4, 30}} }; //����ü movie�� �迭 ���� �� �ʱ�ȭ


		printf("   ����	       ����	  ������    ������\n");
		printf("=================================================\n");
		for (int i = 0; i < 5; i++)
		{
			printf("[%8s] %10s %10d %5d. %2d. %2d\n", box[i].title, box[i].director, box[i].attendance, box[i].open.year, box[i].open.month, box[i].open.day); //���� ���� ������ ������ ���
		}

		return 0;
}