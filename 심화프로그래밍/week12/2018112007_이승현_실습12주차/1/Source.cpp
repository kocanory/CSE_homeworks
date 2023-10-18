#include <iostream>

using namespace std;

class Circle
{
private:
	int radius;
public:
	Circle() {}
	Circle(int n) : radius(n){}
	int getRadius()
	{
		return radius;
	}

}; //class circle ����

template <class t>
t* concat(t *array1, int n1, t *array2, int n2)
{
	t* array = new t[n1 + n2];
	for (int i = 0; i < n1; i++)
	{
		array[i] = array1[i];
	}
	for (int i = n1; i < n1 + n2; i++)
	{
		array[i] = array2[i - n1];
	}

	return array; //���ø��� �̿��� �迭�� �̾���̴� �Լ� ����
}
template<>
Circle * concat(Circle *array1, int n1, Circle *array2, int n2)
{
	Circle* array = new Circle[n1 + n2];
	for (int i = 0; i < n1; i++)
	{
		array[i] = array1[i];
	}
	for (int i = n1; i < n1 + n2; i++)
	{
		array[i] = array2[i - n1];
	}

	return array;//���ø� Ư��ȭ�� �̿��� �迭�� �̾���̴� �Լ� ����
}

template <class t>
void printList(t *array, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << array[i];
	}

	cout << endl; //�迭�� ���
}

template<>
void printList(char* array, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << array[i] << " ";
	}

	cout << endl; //������ �迭 ���
}
template<>
void printList(Circle *array, int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "radius : " << array[i].getRadius() << endl;
	} //���� ������ ���
}

int main()
{
	int iListA[] = { 1, 2, 3 };
	int iListB[] = { 4, 5, 6 };
	int *intResult = concat<int>(iListA, 3, iListB, 3);

	char cListA[] = { 'A', 'B', 'C' };
	char cListB[] = { 'D', 'E', 'F' };
	char *charResult = concat<char>(cListA, 3, cListB, 3);

	Circle circleListA[] = { Circle(1), Circle(2), Circle(3)};
	Circle circleListB[] = { Circle(4), Circle(5), Circle(6)};
	Circle *circleResult = concat <Circle>(circleListA, 3, circleListB, 3);


	printList(intResult, 6);
	printList(charResult, 6);
	printList(circleResult, 6);

	return 0;

}
