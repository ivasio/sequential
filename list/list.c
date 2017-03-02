#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../api.h"


#define listof(lst) ((list*)(lst->vars))
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

	void  list_destroy (Sequential* );
	void  list_resize (Sequential* , int size);
	void  list_swap (Sequential*, Iterator index1, Iterator index2);
	void  list_insert (Sequential*, Iterator index, void* content);
	
	void list_begin (Sequential*, Iterator pointer);
	void list_end (Sequential*, Iterator pointer);
	void list_next (Sequential*, Iterator pointer);
	void list_prev (Sequential*, Iterator pointer);
	void list_set (Sequential*, Iterator pointer, void* content);
	void* list_get (Sequential*, Iterator pointer);

	Iterator list_iterator_init (struct Sequential* container);
	void list_iterator_destroy (Iterator pointer);

	node* getNth(Sequential *lst, size_t index);
	void list_show(Sequential* lst);


Sequential* list_create(int size, void** initial_content, int content_size){

	Sequential* lst = malloc(sizeof(Sequential));

	lst->vars = (void*)malloc(sizeof(list));

	lst->destroy = (*list_destroy);
	lst->resize = (*list_resize);
	lst->swap = (*list_swap);
	lst->insert = (*list_insert);

	lst->begin = (*list_begin);
	lst->end = (*list_end);
	lst->next = (*list_next);
	lst->prev = (*list_prev);
	lst->set = (*list_set);
	lst->get = (*list_get);

	lst->iterator_init = (*list_iterator_init);
	lst->iterator_destroy = (*list_iterator_destroy);
	
	list* l = listof(lst);
	l->head = (node*)malloc(sizeof(node));
	l->head->data = NULL;
	l->head->next = NULL;
	l->head->prev = NULL;
	l->tail = l->head;
	l->size = 1;

	Iterator p = list_iterator_init(lst);
	int i = 0;
	if (size >= 1)
		lst->set(lst, (Iterator)(((void**)&(l->head))), initial_content[i]);
	for (i = 1; i < size; i++)
	{
		lst->end(lst, p);
		lst->insert(lst, p, initial_content[i]);
		printf("%d - %s\n", i, (char*)initial_content[i]);
	}
	return lst;
}


Iterator list_iterator_init (struct Sequential* lst){
	list* l = listof(lst);
	void** pointer = (void**) malloc (sizeof (void*));
	*pointer = l->head;
	return pointer;
}

void list_iterator_destroy (Iterator p){
	
	if(p)
		free(p);
}

void* list_get (Sequential* lst, Iterator p){

	return ((node*)(*p))->data;
}

void list_set (Sequential* lst, Iterator p, void* content){
	
	((node*)(*p))->data = content;
}

void list_begin (Sequential* lst, Iterator p){

	*p = ((list*)(lst->vars))->head;
}

void list_end (Sequential* lst, Iterator p){

	*p = ((list*)(lst->vars))->tail;
}


void list_next (Sequential* lst, Iterator p){

	if((((node*)(*p))->next) != ((list*)(lst->vars))->tail)
		*p = ((node*)(*p))->next;
	else *p = NULL;
}

void list_prev (Sequential* lst, Iterator p){

	if((((node*)(*p))->prev)!= ((list*)(lst->vars))->head)
		*p = ((node*)(*p))->prev;
	else *p = NULL;
}


void list_insert(Sequential* lst, Iterator index, void* content){

 	if (*index == NULL) {
       return;
    }

	list* l = listof(lst);
    node *elm = NULL;
    node *ins = (node*) malloc(sizeof(node));
    elm = *index;
	
    ins->data = content;
    ins->prev = elm;
    ins->next = elm->next;

    if (elm->next) {
        elm->next->prev = ins;
    }
    elm->next = ins;

    if (!ins->prev) {
        l->head = ins;
    }

    if (!ins->next) {
        l->tail = ins;
    }
    l->size++;
}

void list_show(Sequential* lst){

	list* l = listof(lst);

	node* elm = l->head;
	printf("////////////////////////////\n");
	while (elm != l->tail){
		printf("\nelm - %p\nelm->prev - %p\nelm->next - %p\nelm->data - %p\n\n", elm, elm->prev, elm->next, (char*)(elm->data));
	elm = elm->next;
	}
	printf("\nelm - %p\nelm->prev - %p\nelm->next - %p\nelm->data - %p\n", elm, elm->prev, elm->next, (char*)(elm->data));

	printf("\nsize - %d\n",l->size);
	printf("/\\\\\\\\\\\\\\\\\\\\\\\\\\/\n");

}

void list_swap(Sequential* lst, Iterator index1, Iterator index2){
	
	node* elm1;
    node* elm2;
	void* tmp = NULL;
	//printf("swap0\n");
    elm1 = *index1;
	elm2 = *index2;
	//printf("swap1 tmp - %p elm1 - %p elm2 - %p data1 - %p data2 - %p\n", tmp, elm1, elm2, elm1->data, elm2->data);
	tmp = elm1->data;
	elm1->data = elm2->data;
	elm2->data = tmp;
}


void  list_resize (Sequential* lst, int size){
	printf("resize\n");

}

void list_destroy(Sequential* lst){
	
	list* l = listof(lst);
	node* tmp = l->tail;
	node* next = NULL;
	while (tmp){
		next = (node*)tmp->prev;
		free(tmp);
		tmp = next;
	}
	if (lst)
		free(lst);
	lst = NULL;
}

/*void rewrite (Sequential* lst, Iterator index, void* content){

	node* elm = index;

	elm->data = content;

}*/

/*
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
*/
