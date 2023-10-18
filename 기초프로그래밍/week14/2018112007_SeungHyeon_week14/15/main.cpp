#include "Header.h"
#include <stdio.h>

card dck[52];

int main()
{
	int i;
	gambler gamer[NUMOFGAMER];

	fdk(dck);
	sfl(dck);
	del(dck, gamer);

	//카드 출력
	printcard(gamer);

	//족보 검사 
	for (i = 0; i<NUMOFGAMER; i++) {
		gamer[i].rk = 0;
		gamer[i].rk = checkrank(gamer[i].cd);
	}

	//족보 출력
	printrank(gamer);
	return 0;
}

void printrank(gambler *gamer) //순위를 출력하고 승자를 출력
{
	int i = 0, winner = 0;

	for (i = 0; i<NUMOFGAMER; i++) {
		printf("\t%s%d : rank = %s\n", "gamer", i + 1, srank[gamer[i].rk]);
		if (gamer[i].rk > gamer[winner].rk) winner = i;
	}

	printf("\n\t\t%s%d by rank of %s.\n\n",
		"The winner is gamer", winner + 1, srank[gamer[winner].rk]);
}

void del(card *dck, gambler *gamer)
{
	int i;
	for (i = 0; i<7 * NUMOFGAMER; i++)
		gamer[i%NUMOFGAMER].cd[i % 7] = dck[i];//사람 수 만큼 분배 
}

void printcard(gambler *gbr) //카드를 출력하고 순위를 확인
{
	int i, j, k, m;
	int total = 0, limit;

	for (i = 0; i <= (NUMOFGAMER - 1) / 3; i++) {
		j = i * 3;
		limit = 3;
		if (i == (NUMOFGAMER - 1) / 3) {
			if (NUMOFGAMER % 3 == 0)
				limit = 3;
			else
				limit = (NUMOFGAMER % 3);
		}
		printf("\n");
		for (m = 0; m<limit; m++) {
			printf("%7s[%d]\t\t", "gamer", j + m + 1);
		}
		printf("\n\n");
		for (k = 0; k <= 6; k++) {
			for (m = 0; m<limit; m++) {
				printf("%7s\t%s\t\t",
					sfce[gbr[j + m].cd[k].fce], ssut[gbr[j + m].cd[k].sut]);
			}
			printf("\n");
		}
		printf("\n");
	}
	printf("\n");
}

int checkrank(card *x)
{
	//card *y = x;
	card *y;
	int i, cntfce[13] = { 0 }, cntsut[4] = { 0 };
	int cntpair = 0, cnttriple = 0;
	int rk = 0;

	//카드를 정렬
	srt(x);
	y = x;

	//7장의 카드에서 같은 번호와 같은 무늬의 수를 각각 알아본다
	for (i = 0; i <= 6; i++)
	{
		cntfce[(y + i)->fce]++;
		cntsut[(y + i)->sut]++;
	}

	//같은 번호의 수를 조사하여 족보를 정한다.
	for (i = 0; i <= 12; i++)
	{
		switch (cntfce[i]) {
		case 2:
			cntpair++;
			break;
		case 3:
			cnttriple++;
			break;
		case 4:
			rk = Fourcard;
			break;
		}
	}

	if (cntpair >= 1) {
		if (rk < Onepair) rk = Onepair; //원페어

		if (cntpair >= 2) {
			if (rk < Twopair) rk = Twopair;//투페어
			if (cnttriple >= 1)
				if (rk < Fullhouse) rk = Fullhouse;//풀하우스
		}
	}

	if (cnttriple >= 1) {
		if (rk < Triple) rk = Triple;//트리플
	}

	y = x;
	if (isstraight(y)) {
		if (rk < Straight) rk = Straight;//스트레이트

	}

	//플러쉬 검사
	for (i = 0; i <= 3; i++)
	{
		if (cntsut[i] >= 5) {
			//printf("\n\tFlush\n\n");
			if (rk == Straight)
				rk = Straightflush;
			else if (rk < Flush)
				rk = Flush;
		}
	}

	return rk;
}

int isstraight(card *x) //스트레이트 검사 
{
	card *y = x;
	int i, j, same;
	card *start;

	for (i = 0; i <= 2; i++)
	{
		start = y + i;
		j = 0;
		same = 0;
		while ((((start + j)->fce) + 1) == ((start + (j + 1))->fce))
		{
			if (++same == 4) break;
			j++;
		}

		if (same >= 4)
		{
			return 1;
			//break;
		}
	}
	return 0;
}

void sfl(card *dck)
{
	int i, j;
	card temp;

	srand(time(NULL));

	for (i = 0; i <= 51; i++) {
		j = rand() % 52;//j에 0~51 까지 랜덤수 저장
		temp = dck[i];//temp에 deck[i]를 저장
		dck[i] = dck[j];//deck[i]에 deck[0~51]값을 저장
		dck[j] = temp;//deck[0~51]값에 deck[i]값 저장
	}
}

void srt(card *x)
{
	card *y = x;
	int i, j;

	for (i = 0; i <= 5; i++)
		for (j = i + 1; j <= 6; j++)
			if ((y + i)->fce  > (y + j)->fce)
				swap(y + i, y + j);
}

void swap(card *x, card *y)
{
	card z;
	z = *x; *x = *y; *y = z;
}

void fdk(card *dck)
{
	int i;

	for (i = 0; i<51; i++)
	{
		dck[i].fce = i % 13;
		dck[i].sut = i / 13;
	}
}




