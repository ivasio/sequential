typedef struct Sequential {
	
	void* vars;
	
	void  (*destroy) (struct Sequential* container);

	void  (*push_front) (struct Sequential* container, void* content);
	void  (*push_back) (struct Sequential* container, void* content);
	void* (*pull_front) (struct Sequential* container);
	void* (*pull_back) (struct Sequential* container);
	void  (*rewrite) (struct Sequential* container, int index, void* content);
	void* (*get) (struct Sequential* container, int index);
	void  (*resize) (struct Sequential* container, int size);
	void  (*swap) (struct Sequential* container, int index1, int index2);
	void  (*insert) (struct Sequential* container, int index, void* content);
	
} Sequential;


Sequential* vector_create (int size, void** initial_content);
Sequential* list_create (int size, void** initial_content);


#include "vector/vector.c"
#include "list/list.c"
