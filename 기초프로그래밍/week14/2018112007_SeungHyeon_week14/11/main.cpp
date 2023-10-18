#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *strface[] = { "Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King" };
char *strsuit[] = { "Hearts","Diamonds","Clubs","Spades" };

enum enumsuit { Hearts, Diamonds, Clubs, Spades };
enum enumface { Ace, Deuce, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
typedef enum enumsuit enumsuit; //�ڷ��� ������
typedef enum enumface enumface; //�ڷ��� ������

struct card {
	int suit; //���
	int face; //����
};
typedef struct card card;//�ڷ��� ������

void filldeck(card *deck); //��� ī���� ���� ��ȣ�� �ο�.
void shuffle(card *deck);  //ī�带 ���� ����.
void deal(card *deck, int cnt); //cnt���� 7���� ī�� �ο�.

int main()
{
	card deck[52]; //����ücard �±׺��� deck
	int cnt = 2;

	filldeck(deck);
	shuffle(deck);
	printf("ī�� ���ӿ� �� ����� �����մϱ�? >> ");
	scanf("%d", &cnt);
	printf("\n");
	deal(deck, cnt);
}

void filldeck(card *deck)//deck[52]�� ī�带 ������� �й��ϴ� �Լ�
{
	int i;
	for (i = 0; i <= 51; i++)
	{
		deck[i].face = i % 13; //0~12���� deck[i].face�� ����
		deck[i].suit = i / 13; //0~3���� deck[i].face�� ����
	}
}

void shuffle(card *deck)//deck[52]�� �����ִ� �Լ�
{
	int i, j;
	card temp;
	srand(time(NULL));
	for (i = 0; i <= 51; i++)
	{
		j = rand() % 52;//j�� 0~51 ���� ������ ����
		temp = deck[i];//temp�� deck[i]�� ����
		deck[i] = deck[j];//deck[i]�� deck[0~51]���� ����
		deck[j] = temp;//deck[0~51]���� deck[i]�� ����
	}
}

void deal(card *deck, int cnt)
{
	int i;
	int total = 7 * cnt; //����� * ����ī��� = �� ī�� ��
	for (i = 0; i<cnt; i++)
		printf("%13s%-5d", "���", i + 1); //��� �� ��ŭ ��� 
	printf("\n");

	for (i = 0; i<total; i++)
		printf("%5s of %-8s %c", strface[deck[i].face],
			strsuit[deck[i].suit], (i + 1) % cnt ? ' ' : '\n'); //ī�带 ���ʴ�� ���
}