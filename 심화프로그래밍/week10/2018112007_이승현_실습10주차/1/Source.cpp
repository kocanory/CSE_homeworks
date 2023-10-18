#include <iostream>
#include <string>

using namespace std;

class Circle
{
private:
	int radius; //반지름 값을 저장할 변수 정의
public:
	Circle(int n) : radius(n) {}
	int getRadius() const
	{
		return radius;  //반지름 값 리턴
	}
};

class NamedCircle : protected Circle //Circle 클래스 상속
{
private:
	string name; //원의 이름을 저장할 string 변수정의
public:
	NamedCircle(int n, string circlename) : Circle(n), name(circlename) {} 
	void show() 
	{
		cout << "반지름이 " << Circle::getRadius() << "인 " << name << endl; //원의 정보 출력
	}
};

int main()
{
	NamedCircle waffle(3, "waffle"); //클래스 초기화
	waffle.show(); //원의 정보 출력

	return 0;
}