#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char *strface[] = { "Ace","Deuce","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King" };
char *strsuit[] = { "Hearts","Diamonds","Clubs","Spades" };

enum enumsuit { Hearts, Diamonds, Clubs, Spades };
enum enumface { Ace, Deuce, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King };
typedef enum enumsuit enumsuit; //자료형 재정의
typedef enum enumface enumface; //자료형 재정의

struct card {
	int suit; //모양
	int face; //숫자
};
typedef struct card card;//자료형 재정의

void filldeck(card *deck); //모든 카드의 모양과 번호를 부여.
void shuffle(card *deck);  //카드를 섞는 과정.
void deal(card *deck, int cnt); //cnt에게 7장의 카드 부여.

int main()
{
	card deck[52]; //구조체card 태그변수 deck
	int cnt = 2;

	filldeck(deck);
	shuffle(deck);
	printf("카드 게임에 몇 사람이 참가합니까? >> ");
	scanf("%d", &cnt);
	printf("\n");
	deal(deck, cnt);
}

void filldeck(card *deck)//deck[52]에 카드를 순서대로 분배하는 함수
{
	int i;
	for (i = 0; i <= 51; i++)
	{
		deck[i].face = i % 13; //0~12까지 deck[i].face에 저장
		deck[i].suit = i / 13; //0~3까지 deck[i].face에 저장
	}
}

void shuffle(card *deck)//deck[52]를 섞어주는 함수
{
	int i, j;
	card temp;
	srand(time(NULL));
	for (i = 0; i <= 51; i++)
	{
		j = rand() % 52;//j에 0~51 까지 랜덤수 저장
		temp = deck[i];//temp에 deck[i]를 저장
		deck[i] = deck[j];//deck[i]에 deck[0~51]값을 저장
		deck[j] = temp;//deck[0~51]값에 deck[i]값 저장
	}
}

void deal(card *deck, int cnt)
{
	int i;
	int total = 7 * cnt; //사람수 * 개인카드수 = 총 카드 수
	for (i = 0; i<cnt; i++)
		printf("%13s%-5d", "사람", i + 1); //사람 수 만큼 출력 
	printf("\n");

	for (i = 0; i<total; i++)
		printf("%5s of %-8s %c", strface[deck[i].face],
			strsuit[deck[i].suit], (i + 1) % cnt ? ' ' : '\n'); //카드를 차례대로 출력
}