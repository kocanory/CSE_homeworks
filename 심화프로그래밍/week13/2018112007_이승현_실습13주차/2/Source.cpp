#include <iostream>

using namespace std;

int divide(int n1, int n2)
{
	try
	{
		if (n2 == 0)
			throw - 1; //0으로 나눌때 예외 처리
		return n1 / n2;
	}

	catch(int i)
	{
		cout << "0으로 나눌 수 없습니다!" << endl; //0으로 나눌때 출력
	}
}

int main()
{
	divide(2018, 0);

	return 0;
}