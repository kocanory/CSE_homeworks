#pragma once
#define boolean unsigned char
#define true 1
#define false 0
typedef char Element;
// Global queue
typedef struct queue *queue_pointer;
typedef struct queue {
	Element item;
	queue_pointer link;
} queue;
queue_pointer front, rear;
void addq(Element e);
Element deleteq();
void queue_show();
boolean is_queue_empty();