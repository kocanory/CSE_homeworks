#pragma once
#define MAX_SIZE 10
#define boolean unsigned char
#define true 1
#define false 0

typedef char Element;
Element stack[MAX_SIZE];
int top = -1;
void push(Element e);
Element pop();
void stack_show();