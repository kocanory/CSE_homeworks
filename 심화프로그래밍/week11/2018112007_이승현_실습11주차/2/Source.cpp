#include <iostream>

using namespace std;

class People
{
public:
	People() { cout << "People ����" << endl; }
	virtual ~People() { cout << "People �Ҹ�" << endl; } //���� �Ҹ��ڷ� ����
};

class Parent : public People
{
	string *children;
public:
	Parent()
	{
		children = new string[3]; //�����Ҵ�
		cout << "Parent ����" << endl;
	}

	~Parent()
	{
		delete[] children;
		cout << "Parent �Ҹ�" << endl;
	}
};

int main()
{
	Parent *parent = new Parent;
	People *people = parent;

	delete people; //�޸� ��ȯ

	return 0;
}