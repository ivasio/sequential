#ifndef SEQUENTIAL_LIB_H_
#define SEQUENTIAL_LIB_H_

typedef void** Iterator;

struct Sequential typedef Sequential;

typedef struct Sequential {
	
	void* vars;
	
	void  (*destroy) (Sequential* container);

	void  (*resize) (Sequential* container, int size);
	void  (*swap) (Sequential* container, Iterator pointer1, Iterator pointer2);
	void  (*insert) (Sequential* container, Iterator pointer, void* content);
	
	void (*begin) (Sequential* container, Iterator pointer);
	void (*end) (Sequential* container, Iterator pointer);
	void (*next) (Sequential* container, Iterator pointer);
	void (*prev) (Sequential* container, Iterator pointer);
	void (*set) (Sequential* container, Iterator pointer, void* content);
	void* (*get) (Sequential* container, Iterator pointer);

	Iterator (*iterator_init) (struct Sequential* container);
	void (*iterator_destroy) (Iterator pointer);
	
} Sequential;

Sequential* vector_create (int size, void** initial_content, size_t content_size);
Sequential* list_create (int size, void** initial_content, size_t content_size);


#endif  // SEQUENTIAL_LIB_H_
