#include "pch.h"
#include <iostream>
#include <cstring>


using namespace std;

int main()
{
	char a[30]; //문자형 배열 변수 선언

	cin.getline(a, sizeof(a)); //입력한 문장을 변수에 저장

	int size = strlen(a) - 1; //문장의 길이를 정수형 변수에 저장
		for (; size >= 0; size--)
		{
			cout << a[size]; //입력한 문장을 역순으로 출력
		}

		return 0;
}
