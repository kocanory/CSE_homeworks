#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bst_dictionary.h"
int main()
{
	char c, fname[20];
	char w1[100], *w2;
	int wcount;
	printf("************* Command ************\n");
	printf("R: Read data, S: Search data \n");
	printf("P: Print inorder, Q: Quit \n");
	printf("**********************************\n");
	while (1) {
		printf("\nCommand> ");
		c = getch();
		putch(c);
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
			scanf("%s", w1);
			w2 = bst_search(w1);
			if (w2) printf(" Meaning: %s \n", w2);
			else printf(" No such word ! \n");
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

int build_dictionary(char *fname)
{
	int i = 0;
	FILE *ifp;

	ifp = fopen(fname, "r");
	while (fscanf(ifp, "%s %s", r[i].w1, r[i].w2) == 2)
		++i;

	fclose(ifp);

	for (int j = 0; j < i; j++)
	{
		bst_insert(r[j].w1, r[j].w2);
	}
	return i;
}
void bst_insert(char *w1, char *w2)
{
	tree_pointer p = NULL, c = root;

	while (c)
	{
		if (strcmp(w1, c->w1) == 0)
			return;
		p = c;
		if (strcmp(c->w1, w1) > 0)
			c = c->left;
		else
			c = c->right;
	}

	tree_pointer temp = (tree_pointer)malloc(sizeof(tree_node));
	strcpy(temp->w1, w1);
	strcpy(temp->w2, w2);
	temp->left = temp->right = NULL;

	if (p == NULL)
		root = temp;
	else if (strcmp(p->w1, w1) > 0)
		p->left = temp;
	else
		p->right = temp;
}
char * bst_search(char *w1)
{
	tree_pointer p = root;

	while (p)
	{
		if (strcmp(w1, p->w1) == 0)
			return p->w2;

		if (strcmp(p->w1, w1) > 0)
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
	printf("%s %s\n", ptr->w1, ptr->w2);
	bst_show_inorder(ptr->right);
}