#include <stdio.h>

int main(void)
{
	int i, j, k;
	
	for (i = 0; i < 8; i++) //for문의 반복조건 정의
	{
		for (j = 7; j >= 0; j--) //7부터 1까지 반대로 출력하게 조건 설정
		{

			if (j > i)
			{
				printf(" "); //밑에서부터 올라오면서 왼쪽에 빈칸이 생기게 설정
			}
			else
			{
				printf("%d", j); //아래서부터 7부터 1까지 숫자가 줄어들게 출력
			}

		}
	
		
	for (k = 1; k <= i; k++)
	{
		printf("%d", k); //0을 기준으로 왼쪽의 숫자들과 대칭되도록 설정
	}
	puts("");
	}
	

	return 0;

}