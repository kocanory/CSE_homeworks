#include "pch.h"
#include <iostream>

int main()
{
	using namespace std;
	int sum = 0; //정수형 변수 선언
	for (int i = 1; i < 11;i++)
	{
		 sum += i; //1에서 10까지의 합을 변수 sum에 저장
	}

	cout << "1에서 10 까지의 합은 : " << sum	<< endl; //1에서 10까지의 합을 출력

	return 0;
}

