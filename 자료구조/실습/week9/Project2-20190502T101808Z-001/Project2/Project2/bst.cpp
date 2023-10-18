#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "bst.h"
int main()
{
	char c, grade;
	int id;
	printf("************* Command ************\n");
	printf("I: Insert data, S: Search data \n");
	printf("P: Print inorder, Q: Quit \n");
	printf("**********************************\n");
	while (1) {
		printf("\nCommand> ");
		c = getch();
		putch(c);
		c = toupper(c);
		switch (c) {
		case 'I':
			printf("\n id and grade: ");
			scanf("%d %c", &id, &grade);
			bst_insert(id, grade);
			break;
		case 'S':
			printf("\n id: ");
			scanf("%d", &id);
			grade = bst_search(id);
			if (grade) printf(" Grade of %d: %c \n", id, grade);
			else printf(" No such id ! \n");
			break;
		case 'P':
			printf("\n");
			bst_show_inorder(root);
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

void bst_insert(int key, char data)
{
	tree_pointer p = NULL, c = root;

	while (c)
	{
		if (key == c->key)
			return;
		p = c;
		if (c->key > key)
			c = c->left;
		else
			c = c->right;
	}

	tree_pointer temp = (tree_pointer)malloc(sizeof(tree_node));
	temp->data = data;
	temp->key = key;
	temp->left = temp->right = NULL;
	
	if (p == NULL)
		root = temp;
	else if (key < p->key)
		p->left = temp;
	else
		p->right = temp;

}
char bst_search(int key)
{
	tree_pointer p = root;

	while(p)
	{
		if (key == p->key)
			return p->data;

		if (key < p->key)
			p = p->left;
		else
			p = p->right;
	}

	return NULL;
}
void bst_show_inorder(tree_pointer ptr)
{
	if (ptr == NULL) return;
	
	bst_show_inorder(ptr->left);
	printf("id : %d, Grade of %d: %c\n", ptr->key, ptr->key, ptr->data);
	bst_show_inorder(ptr->right);
}