#include <iostream>

using namespace std;

int divide(int n1, int n2)
{
	try
	{
		if (n2 == 0)
			throw - 1; //0���� ������ ���� ó��
		return n1 / n2;
	}

	catch(int i)
	{
		cout << "0���� ���� �� �����ϴ�!" << endl; //0���� ������ ���
	}
}

int main()
{
	divide(2018, 0);

	return 0;
}