#include <stdio.h>
#include <string.h>

struct person //���������� ���� ����ü
{
	char *name; //�̸�
	char phone[30]; //��ȭ��ȣ
	char address[30]; //�ּ�
};

int main(void)
{
	typedef struct professor //�ڷ��� ������
	{
		struct person information; //��������
		char *major; //�а�
		char *study; //���
		char *subject; //����
	} professor;

	professor box[] = {
		{{"������", "011-3333-2456", "��õ������ ������"}, "�����", "��ǻ�Ͱ���", "���α׷���" },
		{ {"������", "016-3467-4389", "����� ������ ���"}, "�����", "����ȸȭ", "����" },
		{{"�ſ���", "017-2222-2456", "��⵵ �ϻ�� ȭ�"}, "�����", "���ʼ���", "�̻����"}
	}; //����ü professor�� �迭�� ���� �� �ʱ�ȭ

	printf("�� ��   �� ȭ �� ȣ            �� ��             �� ��    �� ��      �� ��\n");
	
	
	for (int i = 0; i < 3; i++)
	{
		printf("%s %s %22s %10s %10s %10s\n", box[i].information.name, box[i].information.phone, box[i].information.address, box[i].major, box[i].study, box[i].subject);
	} //��������, �а�, ���, ���� ���

	return 0;
}

			


