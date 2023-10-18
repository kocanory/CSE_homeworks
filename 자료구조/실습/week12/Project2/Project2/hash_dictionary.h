#pragma once
#define TABLE_SIZE 13
#define boolean unsigned char
#define true 1
#define false 0
// Hash table
typedef struct {
	char key[100];
	char data[100];
} element;
element hash_table[TABLE_SIZE];
// For caomparison count
int num_comparison;
// 파일에서 단어들을 읽어 해시테이블 구성
int build_dictionary(char *fname);
// 해시테이블에 (key, data) 자료 삽입
void hash_insert(char *key, char *data);
// 해시테이블에서 키값이 key인 자료를 검색, data를 반환
char * hash_search(char *key);
// 해시테이블의 key들을 차례로 출력
void hash_show();
// 해시 함수 (folding + division (TABLE_SIZE로 나눈 나머지))
int hash(char *key);
// folding (key의 각 character 값을 더함)
int transform(char *key);