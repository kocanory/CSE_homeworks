#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "arraystack.h"


int main() {
	char c, e;
	printf("*********** Command **********\n");
	printf("+<c>: Push c, -: Pop,\n");
	printf("S: Show, Q: Quit\n");
	printf("******************************\n");

	while (1) {
			printf("\nCommand> ");
			c = getch();
			putch(c);
			c = toupper(c); 
			
			switch (c) {
			case '+':
				e = getch();
				putch(e);
				push(e);
				break;
			case '-':
				e = pop();
				printf("\n %c \n", e);
				break;
			case 'S':
				stack_show();
				break;
			case 'Q':
				printf("\n");
				exit(1);
			default: break;
			}
		}
}

void push(Element e)
{
	if (top >= MAX_SIZE-1)
	{
		printf("\n Stack is full !!!");
		return;
	}
		stack[++top] = e;
}
Element pop()
{
	if (top == -1)
	{
		printf("\n Stack is empty !!!"); 
		return NULL;
	}
		return stack[top--];
	
}
void stack_show()
{
	puts("");
	for (int i = 0; i <= top; i++)
	{
		printf(" %c", stack[i]);
	}
}