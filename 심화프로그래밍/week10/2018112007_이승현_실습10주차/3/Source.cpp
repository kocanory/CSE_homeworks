#include <iostream>
#include <string>

using namespace std;

class Printer
{
private:
	string model;
	string manufacturer;
	int availablePaper; //�𵨸�� ������� �������� ������ ���� ����

public:
	Printer(string name, string manu, int number) : model(name), manufacturer(manu), availablePaper(number) {}

	string getModel()
	{
		return model; //�𵨸� ��ȯ
	}
	string getManufact()
	{
		return manufacturer; //������� ��ȯ
	}

	int getAvailPaper()
	{
		return availablePaper;//���� �� ��ȯ
	}

	void print(int pages) //�μ��� ���� ������ ������ �������� ���ٸ� ���� ���� �����ϴٰ� ����ϰ�, �׷����ʴٸ� �μ�
	{
		if (availablePaper < pages)
			cout << "������ �����մϴ�!" << endl;
		else
		{
			availablePaper -= pages;
		}
	}
};

class InkjetPrinter : public Printer //Ŭ���� ���
{
private:
	int availableInk; //��ũ ���� ������ ���� ����
public:
	InkjetPrinter(string name, string manu, int number, int Ink) : Printer(name, manu, number), availableInk(Ink) {}
	void print(int pages)
	{
		if (availableInk < pages)
			cout << "��ũ�� �����մϴ�!" << endl; //��ũ ���� �����ϴٸ� ���
		else
		{
			availableInk -= pages; //�׷��� ������ �μ�
			Printer::print(pages);
		}
	}

	void showInfo() //�𵨸�� �������, �μ����� �ܷ�, ��ũ�ܷ� ���
	{
		cout << "�𵨸� : " << getModel() << ", ";
		cout << "������ : " << getManufact() << ", ";
		cout << "�μ����� �ܷ� : " << getAvailPaper() << ", ";
		cout << "��ũ�ܷ� : " << availableInk << endl;
	}
};

class LaserPrinter : public Printer
{
private:
	int availableToner; //��ʼ��� ������ ���� ����
public:
	LaserPrinter(string name, string manu, int number, int Toner) : Printer(name, manu, number), availableToner(Toner) {}
	void print(int pages)
	{
		if (availableToner < pages) //��ʰ� �����ϴٸ� ���
			cout << "��ʰ� �����մϴ�!" << endl;
		else //�׷��� ������ �μ�
		{
			availableToner -= pages;
			Printer::print(pages);
		}
	}
	void showInfo()//�𵨸�� �������, �μ����� �ܷ�, ��ũ�ܷ� ���
	{
		cout << "�𵨸� : " << getModel() << ", ";
		cout << "������ : " << getManufact() << ", ";
		cout << "�μ����� �ܷ� : " << getAvailPaper() << ", ";
		cout << "����ܷ� : " << availableToner << endl;
	}
};

int main()
{
	InkjetPrinter *IP = new InkjetPrinter("DGU0001", "DGU", 100, 50);
	LaserPrinter *LP = new LaserPrinter("GGU0002", "GGU", 100, 150); //Ŭ������ �����Ҵ�

	cout << "__ ���� �۵����� �������� ����" << endl;
	cout << "��ũ�� ������ : "; IP->showInfo();
	cout << "������ ������ : "; LP->showInfo();
	cout << endl;

	while (1)
	{
		int number, paper;
		char c;
		cout << "������(1 : ��ũ��, 2: ������) �� �ż� �Է� >>";
		cin >> number >> paper;

		if (number == 1) //1���� �Է��� ��� ��ũ�� �����ͷ� �μ�
		{
			IP->print(paper);
			IP->showInfo();
			LP->showInfo();
		}

		else //2���� �Է��� ��� ������ �����ͷ� �μ�
		{
			LP->print(paper);
			IP->showInfo();
			LP->showInfo();
		}

		cout << "��� ����Ʈ �Ͻðڽ��ϱ�? (y/n) >>";
		cin >> c;
		if (c == 'n' ||c == 'N') //n�� �����ٸ� �������� ���
			break;
		cout << endl;
	}
	delete IP;
	delete LP; //�����Ҵ��� Ŭ�������� �޸𸮸� ��ȯ

	return 0;
}