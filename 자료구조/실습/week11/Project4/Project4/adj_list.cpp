#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#include "adj_list.h"
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
	node_pointer node1 = (node_pointer)malloc(sizeof(node));
	node_pointer node2 = (node_pointer)malloc(sizeof(node));
	node_pointer node3 = (node_pointer)malloc(sizeof(node));
	node_pointer node4 = (node_pointer)malloc(sizeof(node));
	node_pointer node5 = (node_pointer)malloc(sizeof(node));

	node1->vertex = 1;
	node2->vertex = 2;
	node3->vertex = 3;
	node4->vertex = 4;
	node5->vertex = 5;

	node4->link = node3;
	node3->link = node2;
	node2->link = NULL;
	node5->link = node1;
	node1->link = NULL;
	
	adj[1] = adj[5] = node4;
	adj[2] = adj[3] = adj[4] = node5;

	printf(" Graph is built. V = 5, E = 6.\n\n");
} 
void insert_edge(int v, int w)
{
	node_pointer temp = (node_pointer)malloc(sizeof(node));
	temp->vertex = w;
	temp->link = adj[v];
	adj[v] = temp;
}
void dfs(int v)
{
	node_pointer w;
	printf(" %d", v);
	visited[v] = true;
	for (w = adj[v]; w; w = w->link)
	{
		if (!visited[w->vertex])
			dfs(w->vertex);
	}
}
void bfs(int v)
{
	node_pointer w;
	printf(" %d", v);
	visited[v] = true;
	addq(v);
	while (!is_queue_empty())
	{
		v = deleteq();
		for(w = adj[v];w;w = w->link)
			if (!visited[w->vertex])
			{
				printf(" %d", w->vertex);
				visited[w->vertex] = true;
				addq(w->vertex);
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