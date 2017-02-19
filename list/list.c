#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*////////////////////////////////////////////////////////
typedef struct Sequential {
	
	void* vars;
	
	//void (*destroy) (struct Sequential* vector);

	//void (*push_front) (struct Sequential* vector, void* content);
	//void (*push_back) (struct Sequential* , void* content);
	//void* (*pull_front) (struct Sequential* vector);
	//void* (*pull_back) (struct Sequential* vector);
	//void (*rewrite) (struct Sequential* vector, int index, void* content);
	//void* (*get) (struct Sequential* vector, int index);
	//void (*resize) (struct Sequential* vector, int size);
	//void (*swap) (struct Sequential* vector, int index1, int index2);
	//void (*insert) (struct Sequential* vector, int index, void* content);
} Sequential;
Sequential* list_create (int size, void** initial_content);
////////////////////////////////////////////////////////
*/
struct node typedef node;

struct node{
	void* data;
	node* prev;
	node* next;
}typedef node;

struct list{
	node* head;
	node* tail;
	int size;
	//int type_size;
}typedef list;

void destroy (Sequential* );
	
//void list_push_front (Sequential* this, void* content);
void push_back(Sequential* , void* content);
//void* list_pull_front (Sequential* this);
void* pull_back (Sequential* );

Sequential* list_create(int size, void** initial_content){

	Sequential* lst = malloc(sizeof(Sequential));
	//printf("first\n");
	lst->vars = (void*)malloc(sizeof(list));
	lst->destroy = (destroy);
	lst->push_back = (push_back);
	lst->pull_back = (pull_back);
	//lst.vars.type_size = size_of;
	((list*)(lst->vars))->head = (node*)malloc(sizeof(node*));
	((list*)(lst->vars))->tail = (node*)malloc(sizeof(node*));
	((list*)(lst->vars))->head->next = ((list*)(lst->vars))->tail;
	((list*)(lst->vars))->head->prev = NULL;
	//printf("%p\n %p\n %p\n %p\n",((list*)(lst->vars))->head, ((list*)(lst->vars))->tail, ((list*)(lst->vars))->head->next, ((list*)(lst->vars))->head->prev);
	//printf("second\n");
	int i = 0;
	for (i = 0; i < size; i++)
	{
		printf("1\n");
		push_back(lst, initial_content[i]);
	}
	printf("last\n");
	return lst;
}

void push_back(Sequential* s, void* content){
	//printf("---------------------\n");
	node* newElem = (node*)malloc(sizeof(node*));
	newElem->data = (char*)malloc(sizeof(void*));
	strncpy((char*)newElem->data, (char*)(content), sizeof(void*));
	//printf("newElem->data = %s\ncontent = %s\n", (char*)newElem->data, (char*)(content));
	newElem->prev = (node*)(((list*)(s->vars))->tail);
	//printf("newElem = %p\nnewElem->prev = %p\nnewElem->next = %p\nnewElem->data = %s\n",newElem, newElem->prev, newElem->next, (char*)newElem->data);
	((list*)(s->vars))->tail->next = newElem;
	//printf("---------------------\n");
	((list*)(s->vars))->tail = newElem;
	newElem->next = NULL;
	((list*)(s->vars))->size++;
}

void* pull_back(Sequential* s){
	
	void* tmp = ((list*)(s->vars))->tail->data;
	//strncpy((char*)tmp, (char*)(s->tail->data), (int)(s->type_size));
	//free(((list*)(s->vars))->tail->data);
	((list*)(s->vars))->tail = ((list*)(s->vars))->tail->prev;
	((list*)(s->vars))->tail->next = NULL;
	//printf("%p\n %p\n %p\n",((list*)(s->vars))->tail, ((list*)(s->vars))->tail->prev, ((list*)(s->vars))->tail->next);
	//printf("tmp - %p\n", tmp);
	//free(((list*)(s->vars))->tail->next);
	return tmp;
}



void destroy(Sequential* s){
	
	node* tmp = ((list*)(s->vars))->head;
	node* next = NULL;
	while (tmp){
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	if (s)
		free(s);
	s = NULL;
}
