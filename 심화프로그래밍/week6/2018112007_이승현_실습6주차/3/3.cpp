#include "pch.h"
#include <iostream>

using namespace std;

int fibo(int n)
{
	if (n == 0 || n == 1)
	{
		return 1; //n = 0 또는 1일 경우 1 리턴
	}
	else
	{
		return fibo(n - 2) + fibo(n - 1); //그 외에는 전전항과 전항 더하기
	}
}
int main()
{
	for (int i = 0; i < 15; i++)
	{
		cout << fibo(i) << " "; //1항부터 15항까지의 피보나치 함수 출력
	}

	cout<<endl;

	return 0;
}
