#pragma once
#define MaxSize 3
#define boolean unsigned char
#define true 1
#define false 0

typedef char Element;

Element List[MaxSize];
int size = 0;

void list_insert(Element e);
void list_delete(Element e);
boolean list_empty();
boolean list_full();
void list_show();
