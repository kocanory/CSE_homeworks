#include <stdio.h>
#include <string.h>

struct person //개인정보를 위한 구조체
{
	char *name; //이름
	char phone[30]; //전화번호
	char address[30]; //주소
};

int main(void)
{
	typedef struct professor //자료형 재정의
	{
		struct person information; //개인정보
		char *major; //학과
		char *study; //담당
		char *subject; //과목
	} professor;

	professor box[] = {
		{{"박종학", "011-3333-2456", "인천광역시 간석동"}, "전산과", "컴퓨터개론", "프로그래밍" },
		{ {"이종석", "016-3467-4389", "서울시 강남구 도곡동"}, "교양과", "영어회화", "국어" },
		{{"신용현", "017-2222-2456", "경기도 일산시 화곡동"}, "교양과", "기초수학", "이산수학"}
	}; //구조체 professor의 배열의 선언 및 초기화

	printf("이 름   전 화 번 호            주 소             학 과    담 당      과 목\n");
	
	
	for (int i = 0; i < 3; i++)
	{
		printf("%s %s %22s %10s %10s %10s\n", box[i].information.name, box[i].information.phone, box[i].information.address, box[i].major, box[i].study, box[i].subject);
	} //개인정보, 학과, 담당, 과목 출력

	return 0;
}

			


