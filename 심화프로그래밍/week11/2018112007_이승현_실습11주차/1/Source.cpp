#include <iostream>

using namespace std;

class Animal
{
public:
	Animal() {};
	virtual void do_Eat() = 0
	{

	}//���� �����Լ��� ����
};

class Dog : public Animal
{
public:
	Dog() {};
	void do_Eat()
	{
		cout << "Dog's eat()" << endl; //�������� �Դ� ���� ǥ��
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
		cout << "Cat's eat()" << endl; //����̰� �Դ� ���� ǥ�� 
	}
};

class Rabbit : public Animal
{
public:
	Rabbit() {};
	void do_Eat()
	{
		cout << "Rabbit's eat()" << endl; //�䳢�� �Դ� ���� ǥ��
	}
};

int main()
{
	/*Animal animal;*/ //�߻�Ŭ�����̱� ������ �ʱ�ȭ �Ұ���
	Dog dog;
	Cat cat;
	Rabbit rabbit;

	dog.do_Eat();
	cat.do_Eat();
	rabbit.do_Eat();

	return 0;
}