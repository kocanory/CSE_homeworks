#include <stdio.h>
#include <string.h>

struct date //날짜를 위한 구조체
{
	int year; //년
	int month; //월
	int day; //일
};

int main(void)
{
	typedef struct movie //자료형 재정의 
	{
		char *title; //제목
		int attendance; //관객수
		char director[20]; //감독
		struct date open; //개봉일
	} movie;

	movie box[] = {
		{"명량", 17613000, "김한민", {2014, 7, 30} }, {"도둑들", 12983000, "최동훈", {2014, 12, 17}},
		{"국제시장", 14257000, "류승완", {2014, 12, 17}}, {"어벤저스", 7074867, "조스 웨던", {2012, 4, 26}},
		{"아이언맨", 4300365, "존 패브로", {2008, 4, 30}} }; //구조체 movie의 배열 선언 및 초기화


		printf("   제목	       감독	  관객수    개봉일\n");
		printf("=================================================\n");
		for (int i = 0; i < 5; i++)
		{
			printf("[%8s] %10s %10d %5d. %2d. %2d\n", box[i].title, box[i].director, box[i].attendance, box[i].open.year, box[i].open.month, box[i].open.day); //제목 감독 관객수 개봉일 출력
		}

		return 0;
}