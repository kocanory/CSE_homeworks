#include <iostream>

using namespace std;

class People
{

public:
	int money;
	People(int n):money(n) {}

	int subMoney(int m)
	{
		return money - m;
	}

	int addMoney(int m)
	{
		return money + m;
		
	}
};


class Bank
{
public:
	int money;
	Bank() : money(0) {}

	void sendMoney(People& payer, People& payee, int m)
	{
		

		try
		{			
			if (m > payer.money)
				throw 1;	//송금할 돈이 송금하는 사람의 잔액보다 클때 예외처리
			payer.subMoney(m);
			payee.addMoney(m);
			if (payee.money < 2500)
				throw 1.0; //수령인의 돈이 2500이하일때 예외처리
		}
		catch(double d)
		{
			cout << "돈이 반환되었습니다." << endl;
			payer.money += m;			
		}
		catch (int n)
		{
			cout << "잔고보다 더 큰돈을 송금하려 하고 있습니다!" << endl;
		}
		

	}
};

int main(void)
{
	Bank bank;
	People harry(1000);
	People potter(2000);

	bank.sendMoney(harry, potter, 2500);

	return 0;
}