#pragma once
#define MAX_SIZE 100
#define boolean unsigned char
#define true 1
#define false 0
typedef struct {
	int key;
	char data;
}	Element;
// Global heap
Element heap[MAX_SIZE];
int heap_size = 0;
// ������ item(key, data) ����
void insert_max_heap(Element item);
// �������� max item (��Ʈ) ���� �� ��ȯ
Element delete_max_heap();
// ������ �ڷ���� ���ʷ� ���
void max_heap_show();
boolean is_heap_empty();