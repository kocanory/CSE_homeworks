#include <stdlib.h>
#include <time.h>

#define NUMOFGAMER 5 //게임에 참가한 인원 5명

enum enumsuit { Dia, Clb, Hrt, Spd };
enum enumface { Deuce, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };
enum rank { None, Onepair, Twopair, Triple, Straight, Flush, Fullhouse, Fourcard, Straightflush, RoyalSF };

typedef enum enumsuit est;
typedef enum enumface efc;
typedef enum rank rank;

struct card {
	int sut;
	int fce;
};
typedef struct card card;

char *ssut[] = { "Diamond", "Club", "Heart", "Spade" };
char *sfce[] = { "(2)","(3)","(4)","(5)","(6)",
"(7)","(8)","(9)","(10)","Jack","Queen","King","Ace" };
char *srank[] = { "None", "One pair", "Two pair", "Triple", "Straight", "Flush",
"Full house", "Four card", "Straight flush", "Royal straight flush" };

struct gambler {
	card cd[7];
	int rk;
};

typedef struct gambler gambler; //자료형 재정의

void fdk(card *);//모든 카드의 모양과 번호를 부여.
void sfl(card *);//카드를 섞는 과정.
void del(card *, gambler *gamer); //gamer에게 7장의 카드 부여.
void printcard(gambler *);//카드를 출력하고 순위를 확인
void printrank(gambler *gamer); //순위를 출력하고 승자를 출력
void srt(card *);
void swap(card *, card *);

int checkrank(card *x);
int isstraight(card *x); //스트레이트 검사
