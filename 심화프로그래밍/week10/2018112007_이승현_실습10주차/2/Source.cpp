#include <iostream>
#include <string>

using namespace std;

class Shape
{
protected:
	string type;
	double width, height; //도형의 모양과 너비와 높이를 저장할 변수 정의

public:
	Shape(string S_type, double w, double h) : type(S_type), width(w), height(h){}
	double getArea()
	{
		return 0; //면적을 반환해줄 함수 정의
	}
	string getType()
	{
		return type;//도형의 모양을 반환해줄 함수 정의
	}
};

class Rectangle : public Shape //클래스 상속
{

public:
	Rectangle(string s_type, double w, double h) : Shape(s_type, w, h) {}

	double getArea()
	{
		return width * height; // 사각형의 면적 반환
	}
};

class Triangle : public Shape //클래스 상속
{

public:
	Triangle(string s_type, double w, double h) : Shape(s_type, w, h) {}

	double getArea()
	{
		return width * height * 0.5; //삼각혁의 면적 반환
	}
};

class Oval : public Shape
{
public:
	Oval(string s_type, double w, double h) : Shape(s_type, w, h) {}

	double getArea()
	{
		return width * height * 3.141592; //타원의 면적 반환
	}
};

int main()
{
	Rectangle rectangle("Rectangle", 1.5, 2.0); //클래스 초기화
	Triangle triangle("Triangle", 1.5, 2.0); //클래스 초기화
	Oval oval("Oval", 1.5, 2.0);//클래스 초기화

	cout << rectangle.getType() << " 의 넓이는 : " << rectangle.getArea() << endl;
	cout << triangle.getType() << " 의 넓이는 : " << triangle.getArea() << endl;
	cout << oval.getType() << " 의 넓이는 : " << oval.getArea() << endl;

	return 0;
}

