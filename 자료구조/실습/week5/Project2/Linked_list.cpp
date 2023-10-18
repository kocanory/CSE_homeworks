#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include "Linked_list.h"
int main()
{
	char c, e;
	list_pointer head, p;

	head = (list_pointer)malloc(sizeof(list_node));
	head->data = NULL;
	head->link = NULL;
	printf("*********** Command **********\n");
	printf("+<c>: Insert c, -: Delete c,\n");
	printf("?<c>: Search c, S: Show, Q: Quit\n");
	printf("******************************\n");
		while(1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case '+':
			e = _getch();
			_putch(e);
			list_insert(head, e); break;
		case '-':
			e = _getch();
			_putch(e);
			list_delete(head, e); break;
		case '?':
			e = _getch();
			_putch(e);
			p = list_search(head, e);
			if (p) {
				printf("\n %c is in the list. \n", e);
				printf(" Node address = %p, data = %c, link = %p \n", p, p->data, p->link);
			}
			else printf("\n %c is not in the list \n", e);
			break;
		case 'S':
			list_show(head); break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
		}
}

void list_insert(list_pointer head, Element e)
{
	list_pointer p = (list_pointer)malloc(sizeof(list_node));
	p->link = head->link;
	head->link = p;
	p->data = e;

}
void list_delete(list_pointer head, Element e)
{
	list_pointer p = head->link;

	while (p)
	{
		if (p->link->data == e)
		{
			list_pointer temp = p->link;
			p->link = p->link->link;
			free(temp);
			break;
		}
		p = p->link;
	}


}
list_pointer list_search(list_pointer head, Element e)
{
	list_pointer p = head->link;

	while (p)
	{
		if (p->data == e)
			return p;
		p = p->link;
	}

	return NULL;
}
bool list_empty(list_pointer head)
{
	if (head->link == NULL)
		return true;
	else
		return false;
}
void list_show(list_pointer head)
{

	if (list_empty(head))
	{
		printf("\nList is Empty\n");
	}

		list_pointer p = head->link;

		puts("");
		while (p != NULL)
		{
			printf(" %c", p->data);
			p = p->link;
		}
}
