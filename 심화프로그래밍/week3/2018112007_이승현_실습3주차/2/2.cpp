#include "pch.h"
#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	
	for (int a = 2; a < 5; a++)
	{
		cout << a << "의 " << a+1 << "제곱 은 : "<<pow(a, a+1) << endl; //거듭제곱을 차례대로 출력
	}

}
