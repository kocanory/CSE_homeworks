#pragma once
#define Element char
#define bool unsigned char
#define true 1
#define false 0
typedef struct list_node *list_pointer;
struct list_node{
	Element data;
	list_pointer link;
};



void list_insert(list_pointer head, Element e)
{
	list_pointer p = (list_pointer)malloc(sizeof(list_node));
	p->link = head->link;
	head->link = p;
	p->data = e;

}
void list_delete(list_pointer head, Element e){
	list_pointer p = head->link;

	while (p){
		if (p->link->data == e){
			list_pointer temp = p->link;
			p->link = p->link->link;
			free(temp);
			break;
		}
		p = p->link;
	}


}
list_pointer list_search(list_pointer head, Element e){
	list_pointer p = head->link;

	while (p)
	{
		if (p->data == e)
			return p;
		p = p->link;
	}

	return NULL;
}
bool list_empty(list_pointer head)
{
	if (head->link == NULL)
		return true;
	else
		return false;
}
void list_show(list_pointer head){

	if (list_empty(head))
	{
		printf("\nList is Empty\n");
	}

		list_pointer p = head->link;

		puts("");
		while (p != NULL)
		{
			printf(" %c", p->data);
			p = p->link;
		}
}
