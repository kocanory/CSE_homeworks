#include <iostream>

using namespace std;

int main()
{
	int num;
	
	while (true)
	{
		try
		{
			cout << "점수를 입력하세요 : ";
			cin >> num; //점수 입력
			if (num < 0)
			{
				throw 1; //0보다 작을경우 예외처리
			}

			else if (num > 100)
			{
				throw 1.1; //100보다 작을경우 예외처리
			}
		
		if (num >= 90)
			cout << "A" << endl;
		if (80 <= num&&num < 90)
			cout << "B" << endl;
		if (70 <= num&&num < 80)
			cout << "C" << endl;
		if (num < 70)
			cout << "D" << endl; //점수 구간에 따라 출력

		}
		catch (double i)
		{
			cout << "점수는 100점을 초과할 수 없습니다!" << endl; //점수가 100점 초과일때 출력
		}
		
		catch(int i)
		{
			cout << "점수는 0점 미만일 수 없습니다!"<< endl; //점수가 0점 미만일때 출력
		}
	}

	return 0;
}