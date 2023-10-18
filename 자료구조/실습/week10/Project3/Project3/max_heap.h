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
// 히프에 item(key, data) 삽입
void insert_max_heap(Element item);
// 히프에서 max item (루트) 삭제 및 반환
Element delete_max_heap();
// 히프의 자료들을 차례로 출력
void max_heap_show();
boolean is_heap_empty();