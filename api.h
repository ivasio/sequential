#pragma once

typedef void* Iterator;

struct Sequential typedef Sequential;

typedef struct Sequential {
	
	void* vars;
	
	void  (*destroy) (Sequential* container);

	void  (*resize) (Sequential* container, int size);
	void  (*swap) (Sequential* container, Iterator index1, Iterator index2);
	void  (*insert) (Sequential* container, Iterator index, void* content);
	
	void (*begin) (Sequential* container, Iterator pointer);
	void (*end) (Sequential* container, Iterator pointer);
	void (*next) (Sequential* container, Iterator pointer);
	void (*prev) (Sequential* container, Iterator pointer);
	void (*set) (Sequential* container, Iterator pointer, void* content);
	void* (*get) (Sequential* container, Iterator pointer);

	Iterator (*iterator_init) (struct Sequential* container);
	void (*iterator_destroy) (Iterator pointer);
	
} Sequential;

Sequential* vector_create (int size, void** initial_content);
Sequential* list_create (int size, void** initial_content);

#include "list/list.c"


