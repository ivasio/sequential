/*
#ifndef INC_API_H
#define INC_API_H

#ifdef __cplusplus
extern "C" {
#endif
*/
	
typedef struct Sequential {
	
	void* vars;
	
	void (*destroy) (struct Sequential* vector);

	void (*push_front) (struct Sequential* vector, void* content);
	void (*push_back) (struct Sequential* vector, void* content);
	void* (*pull_front) (struct Sequential* vector);
	void* (*pull_back) (struct Sequential* vector);
	void (*rewrite) (struct Sequential* vector, int index, void* content);
	void* (*get) (struct Sequential* vector, int index);
	void (*resize) (struct Sequential* vector, int size);
	void (*swap) (struct Sequential* vector, int index1, int index2);
	void (*insert) (struct Sequential* vector, int index, void* content);
} Sequential;

Sequential* vector_create (int size, void** initial_content);
Sequential* list_create (int size, void** initial_content);


#include "vector/vector.c"
#include "list/list.c"

/*
#ifdef __cplusplus
}
#endif

#endif  // INC_API_H

*/
