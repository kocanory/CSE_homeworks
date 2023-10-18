#include <stdio.h>
#include <string.h>

struct person //구조체 개인정보
{
	char *name; //이름
	char phone[30]; //전화번호
	char address[30]; //주소
};

int main(void)
{
	typedef struct employee //자료형 재정의
	{
		struct person information; //개인정보
		int companynumber; //사번
		int income; //월급
		double incentive; //인센티브
	} employee;

	employee box[] = {
		{ { "김지혜", "011-1111-1111", "서울시 구로구 고척동" }, 20123478, 1200000, 1.2,},
		{ { "김자경", "011-2222-2456", "경기도 안양시비산동" }, 20123479, 1500000, 1.5},
		{ { "강동구", "011-3333-2456", "인천광역시 간석동" }, 20123480, 1800000, 1.8},
		{ { "안태용", "017-2222-2456", "경기도 일산시 화곡동" }, 20123481, 2200000, 2.5}
	};//구조체 employee의 배열의 선언 및 초기화

	printf("사 번    이 름   전 화 번 호            주 소            월 급  인센티브    연 봉\n");


	for (int i = 0; i < 4; i++)
	{
		double yearincome = (box[i].income) * (12 + (box[i].incentive)); //연봉 계산
		printf("%d %s %s %22s %10d %5.0f%% %13.1f\n", box[i].companynumber, box[i].information.name, box[i].information.phone, box[i].information.address, box[i].income, (box[i].incentive)*100, yearincome);
	}//사번, 이름, 전화번호, 주소, 월급, 인센티브, 연봉 출력

	return 0;
}