#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main(void)
{
	char a[100]; //배열선언
	printf("한 줄의 문장을 입력하세요. -> \n");
	gets_s(a, sizeof(a));//배열과 배열의 사이즈 값을 불러들임

	printf("입력한 각각의 단어를 반대로 출력합니다. -> \n");

	char *word = strtok(a," "); //" "를 구분자로 설정해 토큰을 분리함

	while (word != NULL) //NULL부분을 제외한 부분
	{
		int size = strlen(word) - 1; //" "이 저장된 값 이전의 참조번호 저장
		for (int i = size; i >= 0; i--)
		{
			printf("%c", word[i]);//토큰에서 문자를 역순으로 출력
		}

		printf(" ");
		word = strtok(NULL," ");//두번째 호출부터 첫 인자를 NULL로 호출한다.
	}
	
	printf("\n");
}
