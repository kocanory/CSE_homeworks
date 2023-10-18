#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
	int r;
	int lotto[7]; //정수형 배열 정의

	srand(time(NULL)); 

	cout << "로또 번호: " << " ";
	
	for (int i = 0; i < 7; i++)
	{
		again:;
		r = rand() % 45 + 1; //난수 생성

		for (int j = 0; j < i; j++)
		{
			if (r == lotto[j])
			{
				goto again; //만약 번호가 같을경우 처음으로 다시 돌아감
			}
			
		}
		
		lotto[i] = r;

		cout << lotto[i] << " ";

		if (i == 5)
		{
			cout << "+ ";
		}
	}

	cout << endl;

	return 0;
}
