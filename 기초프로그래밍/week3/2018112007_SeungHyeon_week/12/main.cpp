#include <stdio.h>

int main(void)
{
	enum c { ca = -10, cb = 5, cc = 15, cd = 25, ce = 35 }; //�����µ��� enum�� �̿��� �����մϴ�.
	float fa = (9.0 / 5.0) * ca + 32.0;
	float fb = (9.0 / 5.0) * cb + 32.0;
	float fc = (9.0 / 5.0) * cc + 32.0;
	float fd = (9.0 / 5.0) * cd + 32.0;
	float fe = (9.0 / 5.0) * ce + 32.0; //���� ������ �����µ��� ���Ͽ� ȭ���µ��� ����մϴ�.
		

	printf("%f %f %f %f %f\n", fa, fb, fc, fd, fe); //ȭ���µ��� ������ ä�� ����մϴ�.
}