#include "pch.h"
#include <iostream>

using namespace std;

bool login(char a, int b)
{
	char name[10] = "이승현" ; //문자형 배열에 이름 저장
	int number = 2018112007; //정수형 변수에 학번 저장

	if (a == (char)name && b == number) //이름과 학번이 맞을경우 true로 리턴하고, 아닐경우 false 리턴
		return true;
	else
		return false;
}

int main()
{
	char a[10];
	int b;
	
	cout << "이름을 입력하세요 : ";
	cin >> a; //이름을 입력

	cout << "학번을 입력하세요 : ";
	cin >> b; //학번을 입력

	if (login((char)a, b)) //이름과 학번이 맞을경우 로그인 성공!, 아닐경우 로그인 실패! 출력
	{
		cout << "로그인 성공!" << endl;
	}
	else
	{
		cout << "로그인 실패!" << endl;
	}

}

