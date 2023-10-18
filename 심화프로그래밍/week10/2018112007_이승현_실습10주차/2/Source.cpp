#include <iostream>
#include <string>

using namespace std;

class Shape
{
protected:
	string type;
	double width, height; //������ ���� �ʺ�� ���̸� ������ ���� ����

public:
	Shape(string S_type, double w, double h) : type(S_type), width(w), height(h){}
	double getArea()
	{
		return 0; //������ ��ȯ���� �Լ� ����
	}
	string getType()
	{
		return type;//������ ����� ��ȯ���� �Լ� ����
	}
};

class Rectangle : public Shape //Ŭ���� ���
{

public:
	Rectangle(string s_type, double w, double h) : Shape(s_type, w, h) {}

	double getArea()
	{
		return width * height; // �簢���� ���� ��ȯ
	}
};

class Triangle : public Shape //Ŭ���� ���
{

public:
	Triangle(string s_type, double w, double h) : Shape(s_type, w, h) {}

	double getArea()
	{
		return width * height * 0.5; //�ﰢ���� ���� ��ȯ
	}
};

class Oval : public Shape
{
public:
	Oval(string s_type, double w, double h) : Shape(s_type, w, h) {}

	double getArea()
	{
		return width * height * 3.141592; //Ÿ���� ���� ��ȯ
	}
};

int main()
{
	Rectangle rectangle("Rectangle", 1.5, 2.0); //Ŭ���� �ʱ�ȭ
	Triangle triangle("Triangle", 1.5, 2.0); //Ŭ���� �ʱ�ȭ
	Oval oval("Oval", 1.5, 2.0);//Ŭ���� �ʱ�ȭ

	cout << rectangle.getType() << " �� ���̴� : " << rectangle.getArea() << endl;
	cout << triangle.getType() << " �� ���̴� : " << triangle.getArea() << endl;
	cout << oval.getType() << " �� ���̴� : " << oval.getArea() << endl;

	return 0;
}

