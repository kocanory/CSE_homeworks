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
	 void showInfo() { cout << "I'm Engineer" << endl; } //엔지니어임을 출력
};

class Designer :  public People
{
public:
	void showInfo() { cout << "I'm Designer" << endl; } //디자이너임을 출력
};

class Director :  public People
{
public:
	void showInfo() { cout << "I'm Director" << endl; } //디렉터임을 출력
};

int main()
{
	Engineer engineer;
	Designer designer;
	Director director;

	People &p1 = engineer;
	People &p2 = designer;
	People &p3 = director;
	
	vector <std::reference_wrapper<People>> myTeam; //벡터를 참조로 받음
	
	myTeam.push_back(p1);
	myTeam.push_back(p2);
	myTeam.push_back(p3);

	for (auto &element : myTeam)
		element.get().showInfo(); //벡터 출력

	return 0;
}