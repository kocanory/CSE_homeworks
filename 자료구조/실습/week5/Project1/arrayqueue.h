#pragma once
#define MAX_SIZE 10
#define boolean unsigned char
#define true 1
#define false 0
typedef char Element;

Element queue[MAX_SIZE];
int front = 0;
int rear = 0;
void addq(Element e);
Element deleteq();
void queue_show();