#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "arraylist.h"

int main()
{
	char c;

	printf("******************** Command *******************\n");
	printf("+<c>: Insert c, -<c>: Delete c, \n");
	printf("E: ListEmpty, F: ListFull, S: ListShow, Q: Quit \n");
	printf("************************************************\n");
	while (1) {
		printf("\nCommand> ");
		c = getch();
		putch(c);
		c = toupper(c);
		switch (c) {
		case '+':
			c = getch();
			getch();
			putch(c);
			list_insert(c);
			break;
		case '-':
			c = getch();
			getch();
			putch(c);
			list_delete(c);
			break;
		case 'E':
			if (list_empty())
				printf("\nTRUE \n");
			else printf("\nFALSE \n");
			break;
		case 'F':
			if (list_full())
				printf("\nTRUE \n");
			else printf("\nFALSE \n");
			break;
		case 'S':
			list_show();
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default:
			break;
		}
	}
}
void list_insert(Element e)
{
	if (size == MaxSize)
	{
		printf("\nList is full !!!");
	}
	else
		List[size++] = e;
}

void list_delete(Element e)
{
	for (int i = 0; i < size; i++)
	{
		if (e == List[i])
		{
			for (int j = i; j < size; j++)
			{
				List[j] = List[j + 1];
			}
			size--;
			break;
		}
		else
		{
			printf("\nData does not exist !!!");
			break;
		}
	}

}
boolean list_empty()
{
	if (size == 0)
		return true;
	else
		return false;

}
boolean list_full() 
	{
		if (size == MaxSize)      
			return true;      
		else    
			return false;                     
	} 
void list_show()
{
	puts("");

	if (size == 0)
	{
		printf("\nList is Empty !!!");
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			printf("%c ", List[i]);
		}
	}
}