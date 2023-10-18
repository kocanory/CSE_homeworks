#pragma once
#define boolean unsigned char
#define true 1
#define false 0
typedef int Element;
// Binary tree node
typedef struct tree_node *tree_pointer;
typedef struct tree_node {
	Element data;
	tree_pointer left;
	tree_pointer right;
} tree_node;
tree_pointer build_simple_tree(); // 앞에 정의된 7개의 노드를 갖는 binary tree를 생성
int bt_count(tree_pointer ptr); // 트리의 노드수를 계산
int bt_sum(tree_pointer ptr); // 트리의 데이터 합을 계산
int bt_height(tree_pointer ptr); // 트리의 높이를 계산
void bt_show_preorder(tree_pointer ptr); // 트리의 내용을 preorder로 출력
void bt_free(tree_pointer ptr); // 트리의 모든 노드를 시스템에 반환(free)
int max(int i, int j);