#include "pch.h"
#include <iostream>

using namespace std;

void swap(int &x, int &y, int &z)//참조에 의한 인수전달
{
	int temp = x;
	x = y; 
	y = temp;

	temp = y;
	y = z;
	z = temp;
}

void swap(int *x, int*y, int*z) //주소에 의한 인수 전달
{
	int *temp = x;
	x = y;
	y = temp;

	temp = y;
	y = z;
	z = temp;
	
	cout << "변경후 : " << *x << ", " << *y << ", " << *z << endl << endl;//함수 밖으로 나가면 값들은 사라지므로 함수안에서 출력
}

int main()
{
	int x = 1;
	int y = 10;
	int z = 100;

	cout << "주소에 의한 인수 전달" << endl;
	cout << "변경전 : " << x << ", " << y << ", " << z << endl;

	swap(&x, &y, &z);//주소에 의한 인수 전달

	cout << "참조에 의한 인수 전달" << endl;
	cout << "변경전 : " << x << ", " << y << ", " << z << endl;

	swap(x, y, z);//참조에 의한 인수전달

	cout << "변경후 : " << x << ", " << y << ", " << z << endl;

	return 0;
}
