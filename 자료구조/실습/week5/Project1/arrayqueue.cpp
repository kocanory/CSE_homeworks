#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "arrayqueue.h"
int main() {
	char c, e;
	printf("*********** Command **********\n");
	printf("+<c>: Addq c, -: DeleteQ,\n");
	printf("S: Show, Q: Quit\n");
	printf("******************************\n");
		while (1) {
			printf("\nCommand> ");
			c = _getch();
			_putch(c);
			c = toupper(c);
			switch (c) {
			case '+':
				e = _getch();
				_putch(e);
				addq(e);
				break;
			case '-':
				e = deleteq();
				printf("\n %c ", e);
				break;
			case 'S':
				queue_show();
				break;
			case 'Q': printf("\n");
				exit(1);
			default: break;
			}
		}
}

void addq(Element e)
{
	if (front == (rear + 1) % MAX_SIZE)
		printf("\nQueue is full !!!");

	else
	{
		rear = ((rear + 1) % MAX_SIZE);
		queue[rear] = e;
	}

}
Element deleteq()
{
	if (front == rear)
	{
		printf("\nQueue is empty !!!");
		return NULL;
	}
	else
	{
		front = (front + 1) % MAX_SIZE;
		return queue[front];
	}
	
}
void queue_show()
{
	puts("");
	
	int i = (front + 1) % MAX_SIZE;

	

	
	while (true)
	{
		if(i == MAX_SIZE)
			i = i % MAX_SIZE;
		
		if (queue[i] == NULL)
		{
			i += 1;
		}
		else
		{
			printf(" %c", queue[i]);

			if (i == rear)
				break;
		}
		i++;
	}
}