#include <iostream>

using namespace std;

class People
{
public:
	People() { cout << "People 생성" << endl; }
	virtual ~People() { cout << "People 소멸" << endl; } //가상 소멸자로 정의
};

class Parent : public People
{
	string *children;
public:
	Parent()
	{
		children = new string[3]; //동적할당
		cout << "Parent 생성" << endl;
	}

	~Parent()
	{
		delete[] children;
		cout << "Parent 소멸" << endl;
	}
};

int main()
{
	Parent *parent = new Parent;
	People *people = parent;

	delete people; //메모리 반환

	return 0;
}