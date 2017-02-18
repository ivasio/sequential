#include <stdlib.h>

typedef struct V_vars {
	int size;
	void** array;
};


void vector_destroy (Sequential* this);
	
void vector_push_front (Sequential* this, void* content);
void vector_push_back (Sequential* this, void* content);
void* vector_pull_front (Sequential* this);
void* vector_pull_back (Sequential* this);
void vector_rewrite (Sequential* this, int index, void* content);
void* vector_get (Sequential* this, int index);
void vector_resize (Sequential* this, int size);
void vector_swap (Sequential* this, int index1, int index2);
void vector_insert (Sequential* this, int index, void* content);



/*--------------------------------------------------------
			VECTOR CONSTRUCTOR
--------------------------------------------------------*/

Sequential* vector_create (int size, size_t elem_size, void** initial_content) {
	
	if (size <= 0) {
		perror ("Invalid vector size %d!\n", size);
		return NULL;
	}
	
	if (elem_size <= 0) {
		perror ("Invalid element size %u!\n", elem_size);
		return NULL;
	}
	
	if (initial_content == NULL) {
		perror ("Invalid initial values array!\n");
		return NULL;
	}
	
	Sequential* this = (Vector*) calloc (1, sizeof (Vector));
	this->array = (void**) calloc (size, sizeof (void*));
	
	for (int i = 0; i < size; i++) {
		this->array[i] = initial_content[i];
	}
	
	this->size = size;
	this->counter = 0;
	this->elem_size = elem_size;
	
	this->push_front = (*vector_push_front);
	this->destroy = (*vector_destroy);
	
	this->push_front = vector_push_front;
	this->push_back = vector_push_back;
	this->pull_front = vector_pull_front;
	this->pull_back = vector_pull_back;
	this->rewrite = vector_rewrite;
	this->get = vector_get;
	this->resize = vector_resize;
	this->swap = vector_swap;
	this->insert = vector_insert;
	
	return this;
}


/*--------------------------------------------------------

--------------------------------------------------------*/

void vector_destroy (Vector* this) {
	
	printf ("Destroyed myself\n");
	
}


/*--------------------------------------------------------

--------------------------------------------------------*/

void vector_push_front (Vector* this, void* content) {



}


/*--------------------------------------------------------

--------------------------------------------------------*/

void vector_push_back (Vector* this, void* content) {



}


/*--------------------------------------------------------
			FUNCTION RETURNING THE LAST ELEMENT
--------------------------------------------------------*/

void* vector_pull_front (Vector* this) {

	return this->array[this->size - 1];

}


/*--------------------------------------------------------
			FUNCTION RETURNING THE 1st ELEMENT
--------------------------------------------------------*/

void* vector_pull_back (Vector* this) {

	return this->array[0];

}


/*--------------------------------------------------------
			REWRITES THE ELEMENT
--------------------------------------------------------*/

void vector_rewrite (Vector* this, int index, void* content) {

	if (vector_private_revise_index (index, this->size)) {
		this->array[index] = content;
	}
	
}


/*--------------------------------------------------------
			VECTOR ELEMENT GETTER
--------------------------------------------------------*/

void* vector_get (Vector* this, int index) {

	if (!vector_private_revise_index (index, this->size)) return NULL;
	
	return this->array[index];

}


/*--------------------------------------------------------
			VECTOR RESIZE FUNCTION
--------------------------------------------------------*/

void vector_resize (Vector* this, int size) {

	if (size <= 0) {
		perror ("Invalid vector size %d for resize operation!\n", size);
		return NULL;
	}
	
	int old_size = this->size;
	this->size = size;
	
	(void**) new_array = (void**) calloc (size, sizeof (void*));
	
	for (int i = 0; i < old_size && i < size; i++) 
		new_array[i] = this->array[i];
		
	if (old_size < size) {
		for (int i = old_size; i < size; i++) 
			new_array[i] = 0;
	}
	
	free (this->array);
	this->array = new_array;
	
}


/*--------------------------------------------------------
			2 ELEMENTS SWAP FUNCTION
--------------------------------------------------------*/

void vector_swap (Vector* this, int index1, int index2) {

	if (vector_private_revise_index (index1, this->size) &&
		vector_private_revise_index (index2, this->size)) {
			
		void* temporary = this->array[index1];
		this->array[index1] = this->array[index2];
		this->array[index2] = temporary;
			
	}

}


/*--------------------------------------------------------
			INSERT FUNCTION
* Resizes the vector (adding 1 element at the end of it), 
* moves all the values beginning from _index_'th one place
* farther and places _content_ on the _index_'th place
--------------------------------------------------------*/

void vector_insert (Vector* this, int index, void* content) {

	if (vector_private_revise_index (index, this->size)) {
		this->resize (this, this->size + 1);
		
		for (int i = size - 2; i >= index; i--) 
			this->array[i + 1] = this->array[i];
			
		this->array[index] = content;
	}

}







char vector_private_revise_index (int index, int size) {
	
	if (index >= this->size) {
		perror ("Asking for %d'th element in the vector containing %d elements!\n", index, size);
		return 0;
	}
	
	if (index < 0) {
		perror ("Asking for the element with negatize index %d!\n", index);
		return 0;
	}
	
	return 1;
	
}
