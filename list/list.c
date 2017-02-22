#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../api.h"


#define LST ((list*)(lst->vars))
/*////////////////////////////////////////////////////////
typedef struct Sequential {
	
	void* vars;
	
	void (*destroy) (struct Sequential* vector);

	void (*push_front) (struct Sequential* vector, void* content);
	void (*push_back) (struct Sequential* , void* content);
	void* (*pull_front) (struct Sequential* vector);
	void* (*pull_back) (struct Sequential* vector);
	//void (*rewrite) (struct Sequential* vector, int index, void* content);
	void* (*get) (struct Sequential* vector, int index);
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
	
void push_front (Sequential* , void* content);
void push_back(Sequential* , void* content);
void* pull_front (Sequential* );
void* pull_back (Sequential* );
void* get(Sequential* , int index);
void insert (Sequential* lst, int index, void* content);
void swap(Sequential* lst, int index1, int index2);
void rewrite (Sequential* lst, int index, void* content);
node* getNth(Sequential *lst, size_t index);
Sequential* list_create(int size, void** initial_content){

	Sequential* lst = malloc(sizeof(Sequential));
	//printf("first\n");
	lst->vars = (void*)malloc(sizeof(list));
	lst->destroy = (destroy);
	lst->push_front = (push_front);
	lst->push_back = (push_back);
	lst->pull_front = (pull_front);
	lst->pull_back = (pull_back);
	lst->rewrite = rewrite;
	lst->get = (get);
	lst->insert = (insert);
	lst->swap = (swap);

	LST->tail = LST->head;
	LST->size = 0;
	printf("lst->head - %p\nlst->tail - %p\n", LST->head, LST->tail);
	//printf("%p\n %p\n %p\n %p\n",((list*)(lst->vars))->head, ((list*)(lst->vars))->tail, ((list*)(lst->vars))->head->next, ((list*)(lst->vars))->head->prev);
	//printf("second\n");
	int i = 0;
	for (i = 0; i < size; i++)
	{
		//printf("1\n");
		push_back(lst, initial_content[i]);
	}
	//printf("last\n");
	return lst;
}

void push_back(Sequential* lst, void* content){
   node *tmp = (node*) malloc(sizeof(node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->data = content;
    tmp->next = NULL;
    tmp->prev = LST->tail;
    if (LST->tail) {
        LST->tail->next = tmp;
    }
    LST->tail = tmp;
 
    if (LST->head == NULL) {
        LST->head = tmp;
    }
    LST->size++;
}


void* pull_back(Sequential* lst){
	
	void* tmp = LST->tail->data;
	//strncpy((char*)tmp, (char*)(s->tail->data), (int)(s->type_size));
	//free(((list*)(s->vars))->tail->data);
	LST->tail = LST->tail->prev;
	LST->tail->next = NULL;
	LST->size--;
	//printf("%p\n %p\n %p\n",((list*)(s->vars))->tail, ((list*)(s->vars))->tail->prev, ((list*)(s->vars))->tail->next);
	//printf("tmp - %p\n", tmp);
	//free(((list*)(s->vars))->tail->next);
	return tmp;
}

void push_front (Sequential* lst, void* content){
	printf("--------------------------------\n");
	node* tmp = (node*) malloc(sizeof(node));
	if (!tmp)
		perror("malloc_push_front");
	tmp->data = content;
	tmp->next = LST->head;
	tmp->prev = NULL;
	if (LST->head)
		LST->head->prev = tmp;

	LST->head = tmp;

	if (!(LST->tail))
		LST->tail = tmp;
	printf("LST->head = %p\nLST->head->next = %p\nLST->head->data = %s\n",LST->head, LST->head->next, (char*)LST->head->data);
	printf("--------------------------------\n");
	LST->size++;
}

void* pull_front(Sequential* lst){
	
	void* tmp = LST->head->data;
	LST->head = LST->head->next;
	LST->head->prev = NULL;
	LST->size--;
	return tmp;
}

void* get(struct Sequential* lst, int index){
    node *tmp = LST->head;
    size_t i = 0;
 
    if (index < LST->size/2) {
        i = 0;
        tmp = LST->head;
        while (tmp && i < index) {
            tmp = tmp->next;
            i++;
        }
    } else {
        i = LST->size - 1;
        tmp = LST->tail;
        while (tmp && i > index) {
            tmp = tmp->prev;
            i--;
        }
    }
	if (!tmp->data){
		printf("bad\n");
		return (void*)(-1);
	}
	printf("elem - %p	elem->data - %p	  data - %c\n", tmp,tmp->data, ((char*)(tmp->data))[0]);
    return tmp->data;
}

node* getNth(Sequential *lst, size_t index) {
    node *tmp = LST->head;
    size_t i = 0;
 
    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }
 
    return tmp;
}

void insert (Sequential* lst, int index, void* content){
    node *elm = NULL;
    node *ins = NULL;
    elm = getNth(lst, index);
    if (elm == NULL) {
        exit(5);
    }
    ins = (node*) malloc(sizeof(node));
	
    ins->data = content;
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;
 
    if (!elm->prev) {
        LST->head = elm;
    }
    if (!elm->next) {
        LST->tail = elm;
    }
 
    LST->size++;
}

void swap(Sequential* lst, int index1, int index2){
	
	node* elm1;
    node* elm2;
	void* tmp ;
	printf("swap0\n");
    elm1 = getNth(lst, index1);
	elm2 = getNth(lst, index2);
	printf("swap1 tmp - %p elm1 - %p elm2 - %p data1 - %p data2 - %p\n", tmp, elm1, elm2, elm1->data, elm2->data);
	tmp = elm1->data;
	elm1->data = elm2->data;
	elm2->data = tmp;
}

void rewrite (Sequential* lst, int index, void* content){

	node* elm = getNth(lst, index);

	elm->data = content;

}

void destroy(Sequential* lst){
	
	node* tmp = LST->head;
	node* next = NULL;
	while (tmp){
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	if (lst)
		free(lst);
	lst = NULL;
}
