#include <iostream>

using namespace std;

class Animal
{
public:
	Animal() {};
	virtual void do_Eat() = 0
	{

	}//순수 가상함수로 정의
};

class Dog : public Animal
{
public:
	Dog() {};
	void do_Eat()
	{
		cout << "Dog's eat()" << endl; //강아지가 먹는 것을 표현
	}
};

class Cat : public Animal
{
public:
	Cat()
	{
	};
	void do_Eat()
	{
		cout << "Cat's eat()" << endl; //고양이가 먹는 것을 표현 
	}
};

class Rabbit : public Animal
{
public:
	Rabbit() {};
	void do_Eat()
	{
		cout << "Rabbit's eat()" << endl; //토끼가 먹는 것을 표현
	}
};

int main()
{
	/*Animal animal;*/ //추상클래스이기 때문에 초기화 불가능
	Dog dog;
	Cat cat;
	Rabbit rabbit;

	dog.do_Eat();
	cat.do_Eat();
	rabbit.do_Eat();

	return 0;
}