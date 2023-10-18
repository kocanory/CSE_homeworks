#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hash_dictionary.h"
int main()
{
	char c, fname[20];
	char key[100], *data;
	int wcount;

	printf("************* CMommand ************\n");
	printf("R: Read data, S: Search data\n");
	printf("P: Print hash table, Q: Quit\n");
	printf("***********************************\n");

		while (1) {
			printf("\nCommand> ");
			c = _getch();
			_putch(c);
			c = toupper(c);
			switch (c) {
			case 'R':
				printf("\n Dictionary file name: ");
				scanf("%s", fname);
				wcount = build_dictionary(fname);
				printf(" Total number of words: %d \n", wcount);
				break;
			case 'S':
				printf("\n Word: ");
				scanf("%s", key);
				num_comparison = 0;
				data = hash_search(key);
				printf(" Hash : %d\n", hash(key));
				if (data) printf(" Meaning: %s \n", data);
				else printf(" No such word ! \n");
				printf(" Tatal number of comparison = %d \n", num_comparison);
				break;
			case 'P':
				printf("\n");
				hash_show();
				break;
			case 'Q':
				printf("\n");
				exit(1);
			default: break;
			}
		}
}

int build_dictionary(char *fname)
{
	int i = 0; // 데이터 수
	char key[100], data[200];
	FILE *ifp;
	if ((ifp = fopen(fname, "r")) == NULL) {
		printf("No such file ! \n");
		exit(1);
	}
	while (fscanf(ifp, "%s %s", key, data) == 2) { // (key data)를 읽어 해시테이블에 삽입
			hash_insert(key, data);
			i++;
	}
	fclose(ifp);
	return(i);
}

void hash_insert(char *key, char *data)
{
	int i = hash(key);

	while (hash_table[i].key[1] != NULL)
		i = (i + 1) % TABLE_SIZE;

	strcpy(hash_table[i].key, key);
	strcpy(hash_table[i].data, data);
}
// 해시테이블에서 키값이 key인 자료를 검색, data를 반환
char * hash_search(char *key)
{
	int i = hash(key);

	while (true)
	{
		if (strcmp(hash_table[i].key, key) == 0)
		{
			num_comparison++;
			return hash_table[i].key;
		}
		else if (hash_table[i].key[1] != NULL && strcmp(hash_table[i].key, key) != 0)
		{
			i = (i + 1) % TABLE_SIZE;
			num_comparison++;
		}

		else if (hash_table[i].key[1] == NULL)
			return NULL;

		if (i == hash(key))
			return NULL;
	}

}
void hash_show()
{
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		printf("hash_table[%d] : <%s>\n", i, hash_table[i].key);
	}
}
// 해시 함수 (folding + division (TABLE_SIZE로 나눈 나머지))
int hash(char *key)
{
	int i = transform(key);
	i %= TABLE_SIZE;

	return i;
}
// folding (key의 각 character 값을 더함)
int transform(char *key)
{
	int i = 0;
	for (int j = 0;key[j] != NULL;j++)
	{
		i += key[j];
	}

	return i;
}