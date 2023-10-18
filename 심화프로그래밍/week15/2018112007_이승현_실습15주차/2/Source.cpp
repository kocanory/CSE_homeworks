#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a;
	string b;
	string c;
	int i1 = 0;
	int i2 = 0;

	cout << "문자를 입력하세요. : ";
	cin >> a >> b;

		for (i2 ; i2 < a.length(); i2++)
		{
			for (i1; i1 < b.length(); i1++)
			{
				if (a[i2] == b[i1])
				{
					c.push_back(a[i2]);
					
				}
			}
		}
		
	if (c == a)
	{
		cout << "subset" << endl;
	}
	else
	{
		cout << "not subset" << endl;
	}
}