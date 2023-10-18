#include <iostream>

using namespace std;

class Animal
{
public:
	string name;
	void eat() { cout << "Animal's Eat" << endl; }
};

class Tiger: virtual public Animal{}; //가상 클래스로 상속

class Lion: virtual public Animal{}; //가상 클래스로 상속

class Liger: public Tiger, Lion{};

int main()
{
	Liger liger;
	liger.eat();
	liger.name = "liger";

	return 0;
}