#include <iostream>

using namespace std;

int main()
{
	int num;
	
	while (true)
	{
		try
		{
			cout << "������ �Է��ϼ��� : ";
			cin >> num; //���� �Է�
			if (num < 0)
			{
				throw 1; //0���� ������� ����ó��
			}

			else if (num > 100)
			{
				throw 1.1; //100���� ������� ����ó��
			}
		
		if (num >= 90)
			cout << "A" << endl;
		if (80 <= num&&num < 90)
			cout << "B" << endl;
		if (70 <= num&&num < 80)
			cout << "C" << endl;
		if (num < 70)
			cout << "D" << endl; //���� ������ ���� ���

		}
		catch (double i)
		{
			cout << "������ 100���� �ʰ��� �� �����ϴ�!" << endl; //������ 100�� �ʰ��϶� ���
		}
		
		catch(int i)
		{
			cout << "������ 0�� �̸��� �� �����ϴ�!"<< endl; //������ 0�� �̸��϶� ���
		}
	}

	return 0;
}