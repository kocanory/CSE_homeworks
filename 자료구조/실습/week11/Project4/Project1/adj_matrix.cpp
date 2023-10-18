#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "adj_matrix.h"
void main()
{
	char c;
	int i, v;
	front = rear = NULL;
	build_simple_graph();


	printf("********* Command ********\n");
	printf("D : DFS, B: BFS, Q: Quit\n");
	printf("**************************\n\n");

		while (1) {
			printf("\nCommand> ");
			c = getch();
			putch(c);
			c = toupper(c);
			switch (c) {
			case 'D':
				printf("\n Start vertex: ");
				scanf("%d", &v);
				for (i = 0; i < MAX_VERTICES; i++) visited[i] = false;
				dfs(v);
				printf("\n");
				break;
			case 'B':
				printf("\n Start vertex: ");
				scanf("%d", &v);
				for (i = 0; i < MAX_VERTICES; i++) visited[i] = false;
				bfs(v);
				printf("\n");
				break;
			case 'Q':
				printf("\n");
				exit(1);
			default: break;
			}
		}
}

void build_simple_graph()
{
	adj[1][2] = adj[2][1] = 1;
	adj[1][3] = adj[3][1] = 1;
	adj[1][4] = adj[4][1] = 1;
	adj[2][5] = adj[5][2] = 1;
	adj[3][5] = adj[5][3] = 1;
	adj[4][5] = adj[5][4] = 1;

	printf(" Graph is built. V = 5, E = 6.\n\n");
}
void insert_edge(int v, int w)
{
	adj[v][w] = adj[w][v] = 1;
}
void dfs(int v)
{
	printf(" %d", v);
	visited[v] = true;
	for (int i = 1; i < 6 ;i++)
	{
		if (adj[v][i] == 1)
		{
			if (!visited[i])
				dfs(i);
		}
	}
}
void bfs(int v)
{
	printf(" %d", v);
	visited[v] = true;
	addq(v);
	while (!is_queue_empty())
	{
		v = deleteq();
		for (int i = 1; i < 6; i++)
			if (adj[v][i] == 1)
			{
				if (!visited[i])
				{
					printf(" %d", i);
					visited[i] = true;
					addq(i);
				}
			}
	}
}

void addq(Element e)
{
	queue_pointer temp = (queue_pointer)malloc(sizeof(queue));
	temp->item = e;
	temp->link = NULL;

	if (front == NULL)
		front = rear = temp;
	else
	{
		rear->link = temp;
		temp = rear;
	}
}
Element deleteq()
{
	queue_pointer temp;
	Element item;
	if (front == NULL)
		return item;
	else
	{
		item = front->item;
		temp = front;
		front = front->link;
		free(temp);
		return item;
	}
}
boolean is_queue_empty()
{
	if (front == NULL)
		return true;
	else
		return false;
}