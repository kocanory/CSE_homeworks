#include "pch.h"
#include <iostream>

using namespace std;

struct person //나이, 이름, 학번으로 구성된 구조체 설정
{
	int age;
	const char *name;
	int number;
};

int main()
{
	person me{ 21, "이승현", 2018112007 }; //나의 나이, 이름, 학번으로 구성된 구조체 설정

	cout << "나이	:	" << me.age << endl;//나이 출력
	cout << "이름	:	" << me.name << endl;//이름 출력
	cout << "학번	:	" << me.number << endl;//학번 출력
}

