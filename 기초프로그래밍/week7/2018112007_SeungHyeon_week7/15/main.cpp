#include<stdio.h>

int main() {

	int num; //정수형 변수 정의

	printf("입력한 정수값: ");
	scanf_s("%d", &num); //입력한 정수값을 불러들임



	if (num == 0) //입력한 정수값이 0일경우 종료

		return 1;



	for (int i = 31; i >= 0; i--) // for문의 조건을 설정 
		{
		printf("%d", (num >> i) & 1); //32번째 비트부터 오른쪽으로 이동하면서 0과1을 구분해 32비트로 출력 
		}
		
	puts("");
	
	return 0;

}