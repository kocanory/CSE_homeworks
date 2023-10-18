#include <iostream>
#include <string>

using namespace std;

class Printer
{
private:
	string model;
	string manufacturer;
	int availablePaper; //모델명과 제조사와 용지수를 저장할 변수 정의

public:
	Printer(string name, string manu, int number) : model(name), manufacturer(manu), availablePaper(number) {}

	string getModel()
	{
		return model; //모델명 반환
	}
	string getManufact()
	{
		return manufacturer; //제조사명 반환
	}

	int getAvailPaper()
	{
		return availablePaper;//용지 수 반환
	}

	void print(int pages) //인쇄할 용지 수보다 보유한 용지수가 적다면 용지 수가 부족하다고 출력하고, 그렇지않다면 인쇄
	{
		if (availablePaper < pages)
			cout << "용지가 부족합니다!" << endl;
		else
		{
			availablePaper -= pages;
		}
	}
};

class InkjetPrinter : public Printer //클래스 상속
{
private:
	int availableInk; //잉크 수를 저장할 변수 정의
public:
	InkjetPrinter(string name, string manu, int number, int Ink) : Printer(name, manu, number), availableInk(Ink) {}
	void print(int pages)
	{
		if (availableInk < pages)
			cout << "잉크가 부족합니다!" << endl; //잉크 수가 부족하다면 출력
		else
		{
			availableInk -= pages; //그렇지 않으면 인쇄
			Printer::print(pages);
		}
	}

	void showInfo() //모델명과 제조사명, 인쇄종이 잔량, 잉크잔량 출력
	{
		cout << "모델명 : " << getModel() << ", ";
		cout << "제조사 : " << getManufact() << ", ";
		cout << "인쇄종이 잔량 : " << getAvailPaper() << ", ";
		cout << "잉크잔량 : " << availableInk << endl;
	}
};

class LaserPrinter : public Printer
{
private:
	int availableToner; //토너수를 저장할 변수 정의
public:
	LaserPrinter(string name, string manu, int number, int Toner) : Printer(name, manu, number), availableToner(Toner) {}
	void print(int pages)
	{
		if (availableToner < pages) //토너가 부족하다면 출력
			cout << "토너가 부족합니다!" << endl;
		else //그렇지 않으면 인쇄
		{
			availableToner -= pages;
			Printer::print(pages);
		}
	}
	void showInfo()//모델명과 제조사명, 인쇄종이 잔량, 잉크잔량 출력
	{
		cout << "모델명 : " << getModel() << ", ";
		cout << "제조사 : " << getManufact() << ", ";
		cout << "인쇄종이 잔량 : " << getAvailPaper() << ", ";
		cout << "토너잔량 : " << availableToner << endl;
	}
};

int main()
{
	InkjetPrinter *IP = new InkjetPrinter("DGU0001", "DGU", 100, 50);
	LaserPrinter *LP = new LaserPrinter("GGU0002", "GGU", 100, 150); //클래스를 동적할당

	cout << "__ 현재 작동중인 프린터의 정보" << endl;
	cout << "잉크젯 프린터 : "; IP->showInfo();
	cout << "레이저 프린터 : "; LP->showInfo();
	cout << endl;

	while (1)
	{
		int number, paper;
		char c;
		cout << "프린터(1 : 잉크젯, 2: 레이저) 와 매수 입력 >>";
		cin >> number >> paper;

		if (number == 1) //1번을 입력할 경우 잉크젯 프린터로 인쇄
		{
			IP->print(paper);
			IP->showInfo();
			LP->showInfo();
		}

		else //2번을 입력할 경우 레이저 프린터로 인쇄
		{
			LP->print(paper);
			IP->showInfo();
			LP->showInfo();
		}

		cout << "계속 프린트 하시겠습니까? (y/n) >>";
		cin >> c;
		if (c == 'n' ||c == 'N') //n을 눌렀다면 루프에서 벗어남
			break;
		cout << endl;
	}
	delete IP;
	delete LP; //동적할당한 클래스들의 메모리를 반환

	return 0;
}