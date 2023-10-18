#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class People
{
public:
	virtual void showInfo() { cout << "I'm People" << endl; } 
};

class Engineer :  public People
{
public:
	 void showInfo() { cout << "I'm Engineer" << endl; } //�����Ͼ����� ���
};

class Designer :  public People
{
public:
	void showInfo() { cout << "I'm Designer" << endl; } //�����̳����� ���
};

class Director :  public People
{
public:
	void showInfo() { cout << "I'm Director" << endl; } //�������� ���
};

int main()
{
	Engineer engineer;
	Designer designer;
	Director director;

	People &p1 = engineer;
	People &p2 = designer;
	People &p3 = director;
	
	vector <std::reference_wrapper<People>> myTeam; //���͸� ������ ����
	
	myTeam.push_back(p1);
	myTeam.push_back(p2);
	myTeam.push_back(p3);

	for (auto &element : myTeam)
		element.get().showInfo(); //���� ���

	return 0;
}