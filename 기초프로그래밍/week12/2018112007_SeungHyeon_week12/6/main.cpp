#include <stdio.h>
#include <string.h>

int main(void)
{
	char a[100];//배열선언
	printf("한 단어를 입력하세요. -> ");
	gets_s(a, sizeof(a));//배열과 배열의 사이즈 값을 불러들임

	int size = strlen(a); //정수형 변수를 선언하고, 배열의 길이값을 저장

	printf("입력한 단어를 반대로 출력합니다. ->");

	for (int i = size; i >= 0; i--)
	{
		printf("%c", a[i]); //문자를 역순으로 출력
	}

	printf("\n");
}