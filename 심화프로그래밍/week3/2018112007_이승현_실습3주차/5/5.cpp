#include "pch.h"
#include <iostream>
#include <bitset>

using namespace std;

int main()
{
	bitset<8> bit = 0xFF; //비트셋 bit 설정
	bitset<8> a = 00000001; //또 하나의 비트셋 a 설정

	cout << "0xFF : " << bit << endl;
	auto b = bit & a; // 비트연산자를 이용해 비트셋 b설정

	cout << b << endl;
	cout << (b << 1) << endl;
	cout << (b << 2) << endl;
	cout << (b << 3) << endl;
	cout << (b << 4) << endl;
	cout << (b << 5) << endl;
	cout << (b << 6) << endl;
	cout << (b << 7) << endl; //비트셋 b가 왼쪽으로 1씩 이동할때마다 출력
}

