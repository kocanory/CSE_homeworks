#include <iostream>
#include <string>

using namespace std;

class Circle
{
private:
	int radius; //������ ���� ������ ���� ����
public:
	Circle(int n) : radius(n) {}
	int getRadius() const
	{
		return radius;  //������ �� ����
	}
};

class NamedCircle : protected Circle //Circle Ŭ���� ���
{
private:
	string name; //���� �̸��� ������ string ��������
public:
	NamedCircle(int n, string circlename) : Circle(n), name(circlename) {} 
	void show() 
	{
		cout << "�������� " << Circle::getRadius() << "�� " << name << endl; //���� ���� ���
	}
};

int main()
{
	NamedCircle waffle(3, "waffle"); //Ŭ���� �ʱ�ȭ
	waffle.show(); //���� ���� ���

	return 0;
}