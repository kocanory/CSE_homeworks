#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

int add(int a, int b)
{
	return a + b; //정수들의 합 리턴
}

double add(double a, double b)
{
	return a + b;//실수들의 합 리턴
}

string add(string s1, string s2)
{
	return s1 + s2; //string s1, s2 이어붙인 것을 리턴
}

vector<int> add(vector<int>matrix1, vector<int> matrix2)
{
	
	matrix1.insert(matrix1.end(), matrix2.begin(), matrix2.end()); //vecter matrix1 뒤에 matrix2 이어 붙임

	return matrix1; //이어붙인 matrix1 리턴
}

int main()
{
	int a = 1, b = 2;
	double c = 2.1, d = 3.4;
	
	string s1 = "ABC";
	string s2 = "DEF";

	vector<int> matrix1 = { 1, 2, 3 };
	vector<int> matrix2 = { 4, 5, 6 };

	cout << "두 정수의 합 : " <<add(a, b) << endl; //정수들의 합 출력
	cout << "두 실수의 합 : " << add(c, d) << endl; //실수들의 합 출력
	
	for (auto &e : add(s1, s2))
	{
		cout << e; //string si, s2 이어붙인 것을 출력
	}

	cout << endl;

	for (auto &e : add(matrix1, matrix2))
	{
		cout << e; //vector matrix1, matrix2 이어붙인 것을 출력
	}
	return 0;
}

