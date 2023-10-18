#include <stdio.h>

int main(void)
{
	int point1 = 95; //중간고사 성적인 95점을 변수 point1에 저장합니다.
	int point2 = 84; //기말고사 성적인 84점을 변수 point2에 저장합니다.
		int total; //total이라는 변수를 생성합니다.

		total = point1 + point2; //성적의 합을 total로 지정합니다.
		
		printf("중간고사 성적: %d\n", point1); //중간고사 성적을 출력합니다.
		printf("기말고사 성적: %d\n", point2); //기말고사 성적을 출력합니다.
		printf("성적의 합: %d\n", total); //total의 값을 출력합니다.

		return 0;
}