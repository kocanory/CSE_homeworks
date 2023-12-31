#include "pch.h"
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
	
	if(b == 0)
	{
		return a; //b가 0일 경우 a 리턴
	}

	return gcd(b, a % b); //그 외에는 유클리드 호제법 실행
}
int main()
{
	int a, b;

	again:
	cout << "두 정수를 입력하세요. : ";
	cin >> a >> b; //입력한 두 정수를 변수 a, b에 저장

	while (a < b)
	{
		cout << "다시 입력하세요." << endl << endl;
		goto again; //만약 b가 a보다 클경우 다시 입력
	}

	cout << "최대공약수 : " << gcd(a, b) << endl; //최대공약수 출력

	return 0;	
}
