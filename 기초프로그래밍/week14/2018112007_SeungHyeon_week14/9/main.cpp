#include <stdio.h>
#include <string.h>

struct person //����ü ��������
{
	char *name; //�̸�
	char phone[30]; //��ȭ��ȣ
	char address[30]; //�ּ�
};

int main(void)
{
	typedef struct employee //�ڷ��� ������
	{
		struct person information; //��������
		int companynumber; //���
		int income; //����
		double incentive; //�μ�Ƽ��
	} employee;

	employee box[] = {
		{ { "������", "011-1111-1111", "����� ���α� ��ô��" }, 20123478, 1200000, 1.2,},
		{ { "���ڰ�", "011-2222-2456", "��⵵ �Ⱦ�ú�굿" }, 20123479, 1500000, 1.5},
		{ { "������", "011-3333-2456", "��õ������ ������" }, 20123480, 1800000, 1.8},
		{ { "���¿�", "017-2222-2456", "��⵵ �ϻ�� ȭ�" }, 20123481, 2200000, 2.5}
	};//����ü employee�� �迭�� ���� �� �ʱ�ȭ

	printf("�� ��    �� ��   �� ȭ �� ȣ            �� ��            �� ��  �μ�Ƽ��    �� ��\n");


	for (int i = 0; i < 4; i++)
	{
		double yearincome = (box[i].income) * (12 + (box[i].incentive)); //���� ���
		printf("%d %s %s %22s %10d %5.0f%% %13.1f\n", box[i].companynumber, box[i].information.name, box[i].information.phone, box[i].information.address, box[i].income, (box[i].incentive)*100, yearincome);
	}//���, �̸�, ��ȭ��ȣ, �ּ�, ����, �μ�Ƽ��, ���� ���

	return 0;
}