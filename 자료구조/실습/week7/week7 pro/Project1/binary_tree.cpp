#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include "binary_tree.h"

int main()
{
	char c;
	int n;
	tree_pointer t;
	t = build_simple_tree();
	printf("************* Command ************\n");
	printf("C: Count tree, A: Sum tree data \n");
	printf("H: Height of tree, S: Show preorder \n");
	printf("F: Free tree, Q: Quit \n");
	printf("**********************************\n");
	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case 'C':
			n = bt_count(t);
			printf("\n Total number of node = %d \n", n);
			break;
		case 'A':
			n = bt_sum(t);
			printf("\n Sum of tree data = %d \n", n);
			break;
		case 'H':
			n = bt_height(t);
			printf("\n Height of tree = %d \n", n);
			break;
		case 'S':
			printf("\n");
			bt_show_preorder(t);
			printf("\n");
			break;
		case 'F':
			printf("\n");
			bt_free(t);
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}
tree_pointer build_simple_tree()
{
	tree_pointer n1 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n2 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n3 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n4 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n5 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n6 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n7 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n8 = (tree_pointer)malloc(sizeof(tree_node));
	tree_pointer n9 = (tree_pointer)malloc(sizeof(tree_node));

	n1->data = 10;
	n2->data = 20;
	n3->data = 30;
	n4->data = 40;
	n5->data = 50;
	n6->data = 60;
	n7->data = 70;
	n8->data = 80;
	n9->data = 90;

	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;
	n3->left = n6;
	n3->right = n7;
	n4->left = n8;
	n4->right = n9;

	n8->left = n8->right = n9->left = n9->right = n5->left = n5->right = n6->left = n6->right = n7->left = n7->right = NULL;

	return n1;
}

int bt_count(tree_pointer ptr)
{
	if (ptr == NULL)
		return 0;
	else
		return { 1 + bt_count(ptr->left) + bt_count(ptr->right) };
}
int bt_sum(tree_pointer ptr)
{
	static int sum = 0;
	if (ptr != NULL)
	{
		sum += ptr->data;
		bt_sum(ptr->left);
		bt_sum(ptr->right);
	}

	return sum;
}
int bt_height(tree_pointer ptr)
{
	int i = log2(double(bt_count(ptr))) + 1;

	return i;
}
void bt_show_preorder(tree_pointer ptr)
{
	if (ptr) {
		printf("%d ", ptr->data);
		bt_show_preorder(ptr->left);
		bt_show_preorder(ptr->right);
	}

}
void bt_free(tree_pointer ptr)
{
	static int item;
	if (ptr == NULL)
		return;
	else
	{
		bt_free(ptr->left);
		bt_free(ptr->right);
		item = ptr->data;
		printf("free node with item %d ...\n", item);
		free(ptr);
	}
}
int max(int i, int j)
{
	return i > j ? i : j;
}
