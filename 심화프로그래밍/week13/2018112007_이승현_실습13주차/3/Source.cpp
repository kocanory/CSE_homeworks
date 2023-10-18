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
		} //id의 길이가 8보다 작거나 10보다 클때 예외처리

		if(!(id.find_first_not_of("0123456789") == string::npos))
		{
			throw 'a';
		} //id가 숫자가 아닐때 예외처리

		if ((password.length()) < 8 && (password.length() > 16))
		{
			throw string("error");
		} //password의 길이가 8보다 작거나 16보다 클때 예외처리

		for (auto e : password)
		{
			if ('A' <= e&&e <= 'Z')
				throw 1.0;
		} //password에 대문자가 들어가있을때 예외처리

		for (auto e : password)
		{
			if (!(('a' <= e&&e <= 'z')
				&&('33' <= e && e <= '47') && ('58' <= e && e <= '64')
				&&('91' <= e && e <= '96') &&('123' <= e && e <= '126')
				&& password.find_first_not_of("0123456789") == string::npos))
				throw 1.0f;
		} //password에 소문자나 특수문자, 숫자가 들어가 있지 않을때 예외처리
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