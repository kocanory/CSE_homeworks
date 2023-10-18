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
// ���Ͽ��� �ܾ���� �о� �ؽ����̺� ����
int build_dictionary(char *fname);
// �ؽ����̺� (key, data) �ڷ� ����
void hash_insert(char *key, char *data);
// �ؽ����̺��� Ű���� key�� �ڷḦ �˻�, data�� ��ȯ
char * hash_search(char *key);
// �ؽ����̺��� key���� ���ʷ� ���
void hash_show();
// �ؽ� �Լ� (folding + division (TABLE_SIZE�� ���� ������))
int hash(char *key);
// folding (key�� �� character ���� ����)
int transform(char *key);