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
				throw 1;	//�۱��� ���� �۱��ϴ� ����� �ܾ׺��� Ŭ�� ����ó��
			payer.subMoney(m);
			payee.addMoney(m);
			if (payee.money < 2500)
				throw 1.0; //�������� ���� 2500�����϶� ����ó��
		}
		catch(double d)
		{
			cout << "���� ��ȯ�Ǿ����ϴ�." << endl;
			payer.money += m;			
		}
		catch (int n)
		{
			cout << "�ܰ��� �� ū���� �۱��Ϸ� �ϰ� �ֽ��ϴ�!" << endl;
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