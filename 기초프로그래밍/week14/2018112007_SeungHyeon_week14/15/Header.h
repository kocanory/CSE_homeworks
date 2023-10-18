#include <stdlib.h>
#include <time.h>

#define NUMOFGAMER 5 //���ӿ� ������ �ο� 5��

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

typedef struct gambler gambler; //�ڷ��� ������

void fdk(card *);//��� ī���� ���� ��ȣ�� �ο�.
void sfl(card *);//ī�带 ���� ����.
void del(card *, gambler *gamer); //gamer���� 7���� ī�� �ο�.
void printcard(gambler *);//ī�带 ����ϰ� ������ Ȯ��
void printrank(gambler *gamer); //������ ����ϰ� ���ڸ� ���
void srt(card *);
void swap(card *, card *);

int checkrank(card *x);
int isstraight(card *x); //��Ʈ����Ʈ �˻�
