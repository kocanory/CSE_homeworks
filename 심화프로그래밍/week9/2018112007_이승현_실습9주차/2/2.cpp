#include "pch.h"
#include <iostream>

using namespace std;

class Engine //class Engine 정의
{

};

class Wheel //class Wheel 정의
{

};

class Car
{
private:
	Engine engine;
	Wheel wheel[4]; //차는 엔진과 바퀴 4개를 포함한다
public:
	Car()
	{
		cout << "set car" << endl;
	}
	void setEngine(Engine* engine)
	{
		cout << "set engine" << endl; 
	}

	void setwheel(Wheel* wheel)
	{
		cout << "set wheel" << endl;
	}
};

int main()
{
	Car car; //class Car 초기화
	Engine engine; //Class Engine 초기화
	Wheel wheel; //Class Wheel 초기화

	car.setEngine(&engine);
	car.setwheel(&wheel);

	return 0;
}
