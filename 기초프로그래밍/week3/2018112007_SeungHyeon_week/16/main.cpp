#include <stdio.h>

int main(void)
{
#define PI 0.621371 //��ũ�� ���� PI�� �̿��� km�� ���� ���� �����մϴ�.
	enum l {la = 60, lb = 80, lc = 100, ld = 120}; //enum�� �̿��� ������ ���̸� �����մϴ�.

	float mla = la * PI;
	float mlb = lb * PI;
	float mlc = lc * PI;
	float mld = ld * PI; //������ ���̿� ���Ͽ� ���Ϸ� ��ȯ�մϴ�.

	printf("%f %f %f %f\n", mla, mlb, mlc, mld); //��ȯ�� ���� ���� ����մϴ�.

	return 0;

}