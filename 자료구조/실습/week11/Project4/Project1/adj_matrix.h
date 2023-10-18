#pragma once
#define MAX_VERTICES 100
#define boolean unsigned char
#define true 1
#define false 0
// Adjacency matrix for a graph
int adj[MAX_VERTICES][MAX_VERTICES];
// Array for search
int visited[MAX_VERTICES];
void build_simple_graph();
void insert_edge(int v, int w);
void dfs(int v);
void bfs(int v);
typedef int Element;
// Global queue
typedef struct queue *queue_pointer;
typedef struct queue {
	Element item;
	queue_pointer link;
} queue;
queue_pointer front, rear;
void addq(Element e);
Element deleteq();
boolean is_queue_empty();