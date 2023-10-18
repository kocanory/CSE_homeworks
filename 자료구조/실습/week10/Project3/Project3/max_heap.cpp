#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "max_heap.h"
int main() {
	char c, data;
	int key;
	Element item;
	printf("************* Command ************ \n");
	printf("I: Insert data, D: Delete max data \n");
	printf("P: Print heap, Q: Quit \n");
	printf("********************************** \n");
	while (1) {
		printf("\nCommand> ");
		c = _getch();
		_putch(c);
		c = toupper(c);
		switch (c) {
		case 'I':
			printf("\n key and data: ");
			scanf("%d %c", &key, &data);
			item.key = key;
			item.data = data;
			insert_max_heap(item);
			break;
		case 'D':
			if (is_heap_empty())
			{
				printf("\nHeap is empty !!!");
			}
			else
			{
				item = delete_max_heap();
				printf("\n Max: key %d, data %c \n", item.key, item.data);
			}
			break;
		case 'P':
			printf("\n");
			max_heap_show();
			break;
		case 'Q':
			printf("\n");
			exit(1);
		default: break;
		}
	}
}

void insert_max_heap(Element item)
{
	int i = ++heap_size;

	while ((i != 1) && item.key > heap[i / 2].key)
	{
		heap[i] = heap[i / 2];
		i /= 2;
	}

	heap[i] = item;
}
Element delete_max_heap()
{
	Element max = heap[1];
	Element temp = heap[heap_size--];
	int p = 1, c = 2;


		while (c <= heap_size)
		{
			if ((c < heap_size) && heap[c].key < heap[c + 1].key)
				++c;
				if (temp.key < heap[c].key)
				{
					heap[p] = heap[c];
					p = c;
					c *= 2;
				}
				else
					break;
		}
		heap[p] = temp;
		return max;
}
void max_heap_show()
{
	for (int i = 1; i <= heap_size; i++)
	{
		printf(" %d %c \n", heap[i].key, heap[i].data);
	}	
}
boolean is_heap_empty()
{
	if (heap_size < 1)
		return true;
	else
		return false;
}