#include "pch.h"
#include <iostream>

using namespace std;

int main()
{
	int num[10] = { 3,2,1,6,5,4,9,8,7,10 };

	cout << "정렬전 배열 상태: ";
	
	for (auto &ele : num)
	{
		cout << ele << " "; //정렬되기 전의 배열 출력
	}
	
	cout << endl;

	for (int j = 0; j < 10; j++)

	{
		
		for (int k = 0; k < 9; k++)

		{
			if (num[k] > num[k + 1]) //만약 다음항의 숫자보다 현재 항의 숫자가 더 클경우 서로 교환
			{
				int temp = num[k];
				num[k] = num[k + 1];
				num[k + 1] = temp;
			}
		}
	}

	printf("정렬후 배열 결과: ");



	for (int i = 0; i < 10; i++)

	{
		cout << num[i]<<" "; //오름차순으로 정렬된 배열 출력
	}

	cout << endl;

	return 0;
}



