#pragma once
#define MAX_SIZE 10
#define boolean unsigned char
#define true 1
#define false 0
// 정렬할 테스트 데이터
int original[] = { 25, 5, 37, 1, 61, 11, 59, 15, 48, 19 };
// 키값 비교회수 카운트를 위한 변수
int num_compare;
// insertion sort
void insertion_sort(int list[], int n);
// quick sort
//void quick_sort(int list[], int left, int right);
// merge sort
void merge_sort(int list[], int left, int right);
// merge
void merge(int list[], int left, int mid, int right);
// list를 복사
void copy_list(int original[], int list[], int n);
// list를 left 에서 right 까지만 출력
void print_list(int list[], int left, int right);