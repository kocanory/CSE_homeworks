#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int a;
	
	while (true)
	{
		cout << "학생의 점수를 입력하세요 : ";
		cin >> a; //입력받은 정수를 a에 저장


		if (a >= 90)
		{
			cout << "A 입니다." << endl; //90점 이상일경우 출력
		}

		else if (80 <= a && a < 90)
		{
			cout << "B 입니다." << endl; //80점 이상 90점 미만일경우 출력
		}

		else if (70 <= a && a < 80)
		{
			cout << "C 입니다." << endl; //70점이상 80점 미만일경우 출력
		}

		else if (a < 70)
		{
			cout << "D 입니다." << endl; //70점 미만일경우 출력
		}
	}

	return 0;
}
