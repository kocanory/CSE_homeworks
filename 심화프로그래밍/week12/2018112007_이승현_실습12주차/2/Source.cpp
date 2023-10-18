#include <iostream>

using namespace std;

class Circle
{
private:
	int radius;
public:
	Circle() {}
	Circle(int n) : radius(n) {}
	int getRadius()
	{
		return radius;
	}

}; //class 정의

template <class t> //템플릿을 이용해 MyVector정의
class MyVector
{
private:
	int length;
	t* n1; 
	t* n2;
public:
	MyVector() : length(3)
	{
		n1 = new t[length];
		n2 = new t[length];
	}

	void pushBack(t n3)
	{
		if (n3 > length)
		{
			cout << "MyVector 확장!" << endl;
			for (int i = 0; i < length ; i++)
			{
				n2[i] = n1[i];
			}
			n1 = new t[6];
			for (int i = 0; i < length ; i++)
			{
				n1[i] = n2[i];
			}
			length = 6;
		}
		n1[n3 - 1] = n3;
		cout << "push : " << n1[n3 - 1] << endl;
	}

	void print()
	{
		for (int i= 0; i<5; i++)
		{
			cout << n1[i];
		}
		cout << endl;
	}
};
template<>
class MyVector<char>//템플릿 특수화를 이용해 문자형의 MyVector정의
{
private:
	int length;
	char* n1;
	char* n2;
public:
	MyVector() : length(3)
	{
		n1 = new char[length];
		n2 = new char[length];
	}

	void pushBack(char n3)
	{
		if (n3 - 64 > length)
		{
			cout << "MyVector 확장!" << endl;
			for (int i = 0; i < length; i++)
			{
				n2[i] = n1[i];
			}
			n1 = new char[6];
			for (int i = 0; i < length; i++)
			{
				n1[i] = n2[i];
			}
			length = 6;
		}
		n1[n3 -64 - 1] = n3;
		cout << "push : " << n1[n3 -64 - 1] << endl;
	}

	void print()
	{
		for (int i = 0; i<5; i++)
		{
			cout << n1[i];
		}
		cout << endl;
	}
};

template<>
class MyVector < Circle >//템플릿 특수화를 이용해 class circle의 MyVector정의
{
private:
	int n1;
	int length;
	int *array1;
	int *array2;
	Circle n;
public:
	MyVector() : length(3)
	{
		array1 = new int[length];
		array2 = new int[length];
	}

	void pushBack(Circle(n1))
	{
		if (Circle(n1).getRadius() > length)
		{
			cout << "MyVector 확장!" << endl;
			for (int i = 0; i < length ; i++)
			{
				array2[i] = array1[i];
			}
			array1 = new int[6];
			for (int i = 0; i < length; i++)
			{
				array1[i] = array2[i];
			}
			length = 6;
		}
		array1[(Circle(n1).getRadius()) - 1] = Circle(n1).getRadius();
		cout << "radius : " << array1[(Circle(n1).getRadius() - 1)] << endl;
	}

	void print()
	{
		int sum = 0;
		for (int i = 0; i<5; i++)
		{
			sum += array1[i];
		}
		cout << "Sum of radius : "<< sum <<endl;
	}
};

int main()
{
	MyVector<int> intV;
	intV.pushBack(1);
	intV.pushBack(2);
	intV.pushBack(3);
	intV.pushBack(4);
	intV.pushBack(5);
	intV.print();

	MyVector<char> charV;
	charV.pushBack('A');
	charV.pushBack('B');
	charV.pushBack('C');
	charV.pushBack('D');
	charV.pushBack('E');
	charV.print();

	MyVector<Circle> CircleV;
	CircleV.pushBack(Circle(1));
	CircleV.pushBack(Circle(2));
	CircleV.pushBack(Circle(3));
	CircleV.pushBack(Circle(4));
	CircleV.pushBack(Circle(5));
	CircleV.print();
}
