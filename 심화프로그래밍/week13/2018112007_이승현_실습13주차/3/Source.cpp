#include <iostream>
#include <string>

using namespace std;

void login(string id, string password)
{
	try
	{
		if ((id.length()) < 8 && (id.length() > 10))
		{
			throw - 1;
		} //id�� ���̰� 8���� �۰ų� 10���� Ŭ�� ����ó��

		if(!(id.find_first_not_of("0123456789") == string::npos))
		{
			throw 'a';
		} //id�� ���ڰ� �ƴҶ� ����ó��

		if ((password.length()) < 8 && (password.length() > 16))
		{
			throw string("error");
		} //password�� ���̰� 8���� �۰ų� 16���� Ŭ�� ����ó��

		for (auto e : password)
		{
			if ('A' <= e&&e <= 'Z')
				throw 1.0;
		} //password�� �빮�ڰ� �������� ����ó��

		for (auto e : password)
		{
			if (!(('a' <= e&&e <= 'z')
				&&('33' <= e && e <= '47') && ('58' <= e && e <= '64')
				&&('91' <= e && e <= '96') &&('123' <= e && e <= '126')
				&& password.find_first_not_of("0123456789") == string::npos))
				throw 1.0f;
		} //password�� �ҹ��ڳ� Ư������, ���ڰ� �� ���� ������ ����ó��
	}

	catch (int i)
	{
		cout << "id is too short or long!" << endl; 
	}

	catch (string error)
	{
		cout << "password is too short or long!" << endl;
	}

	catch (char c)
	{
		cout << "id is not number!" << endl;
	}

	catch (double d)
	{
		cout << "password can't contain upper case!" << endl;
	}

	catch (float f)
	{
		cout << "password must have lower case, special character, number!" << endl;
	}
}
	

int main()
{
	string myid("2018112007");
	string mypassword("a12345678!");
	string id, password;

	cout << "Id, Password : ";
	cin >> id >> password;

	login(id, password);

	if (id == myid && password == mypassword)
		cout << "login successed!" << endl;
	else
		cout << "login failed!" << endl;

	return 0;
}