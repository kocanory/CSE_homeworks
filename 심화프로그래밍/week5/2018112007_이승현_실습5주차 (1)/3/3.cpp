#include "pch.h"
#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	int i = 0, a = 0, b = 0, c = 0;
	char array[20];
	cout << "문자열을 입력하세요: ";
	cin.getline(array, 20); //입력한 문자열을 array 배열에 저장


	while (array[i] != NULL)
	{
		if (array[i] == ' ') //띄어쓰기일경우 c증가
		{
			c++;
		}

		else if ('A' <= array[i] && array[i] <= 'Z') //대문자일경우 a 증가
		{
			a++;
		}

		else if ('a' <= array[i] && array[i] <= 'z')//소문자일경우 b 증가
		{
			b++;
		}
			i++;
	}
	cout << "소문자의 갯수는: " << b << endl;
	cout << "대문자의 갯수는: " << a << endl;
	cout << "공백문자의 갯수는: " << c << endl;

	return 0;
}
