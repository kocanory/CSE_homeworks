#include "pch.h"
#include <iostream>

using namespace std;

class Finger
{
public:
	Finger()
	{
		cout << "Finger created" << endl; //Finger가 생성될때 출력
	}
	~Finger()
	{
		cout << "Finger deleted" << endl; //Finger가 소멸될때 출력
	}
};

class Hand
{
private:
	Finger * fingers; //손은 손가락 5개를 포함한다
public:
	Hand()
	{
		cout << "Hand created" << endl; //Hand가 생성될때 출력
		fingers = new Finger[5];//Finger 5개를 저장할수 있는 배열생성
	}

	~Hand()
	{
		delete[] fingers; //메모리 반환
		cout << "Hand deleted" << endl; //Hand가 소멸될때 출력
	}
};

int main()
{
	Hand hand; //클래스 Hand 초기화

	return 0;
}

