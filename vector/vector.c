#include <stdlib.h>

typedef struct V_vars {
	int size;
	int counter;
	void** array;
};


#define (V_vars*)(this->vars) vrs


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


Sequential* vector_create (int size, void** initial_content) {
	
	if (size <= 0) {
		perror ("Invalid vector size %d!\n", size);
		return NULL;
	}

	if (initial_content == NULL) {
		perror ("Invalid initial values array!\n");
		return NULL;
	}
	
	Sequential* this = (Vector*) calloc (1, sizeof (Vector));

	this->vars = (void*) calloc (1, size (V_vars));
	vrs->array = (void*) calloc (size, sizeof (void*));
	
	for (int i = 0; i < size; i++) {
		this->array[i] = initial_content[i];
	}
	
	vrs->size = size;
	vrs->counter = 0;
	vrs->elem_size = elem_size;
	
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

	return vrs->array[vrs->size - 1];

}


/*--------------------------------------------------------
			FUNCTION RETURNING THE 1st ELEMENT
--------------------------------------------------------*/

void* vector_pull_back (Vector* this) {

	return vrs->array[0];

}


/*--------------------------------------------------------
			REWRITES THE ELEMENT
--------------------------------------------------------*/

void vector_rewrite (Vector* this, int index, void* content) {

	if (vector_private_revise_index (index, vrs->size)) {
		vrs->array[index] = content;
	
}


/*--------------------------------------------------------
			VECTOR ELEMENT GETTER
--------------------------------------------------------*/

void* vector_get (Vector* this, int index) {

	if (!vector_private_revise_index (index, vrs->size)) return NULL;
	
	return vrs->array[index];

}


/*--------------------------------------------------------
			VECTOR RESIZE FUNCTION
--------------------------------------------------------*/

void vector_resize (Vector* this, int size) {

	if (size <= 0) {
		perror ("Invalid vector size %d for resize operation!\n", size);
		return NULL;
	}
	
	int old_size = vrs->size;
	vrs->size = size;
	
	(void**) new_array = (void**) calloc (size, sizeof (void*));
	
	for (int i = 0; i < old_size && i < size; i++) 
		new_array[i] = vrs->array[i];
		
	if (old_size < size) {
		for (int i = old_size; i < size; i++) 
			new_array[i] = 0;
	}
	
	free (vrs->array);
	vrs->array = new_array;
	
}


/*--------------------------------------------------------
			2 ELEMENTS SWAP FUNCTION
--------------------------------------------------------*/

void vector_swap (Vector* this, int index1, int index2) {

	if (vector_private_revise_index (index1, vrs->size) &&
		vector_private_revise_index (index2, vrs->size)) {
			
		void* temporary = vrs->array[index1];
		vrs->array[index1] = vrs->array[index2];
		vrs->array[index2] = temporary;
	}

}


/*--------------------------------------------------------
			INSERT FUNCTION
* Resizes the vector (adding 1 element at the end of it), 
* moves all the values beginning from _index_'th one place
* farther and places _content_ on the _index_'th place
--------------------------------------------------------*/

void vector_insert (Vector* this, int index, void* content) {

	if (vector_private_revise_index (index, vrs->size)) {
		this->resize (this, vrs->size + 1);
		
		for (int i = size - 2; i >= index; i--) 
			vrs->array[i + 1] = vrs->array[i];
			
		vrs->array[index] = content;
	}

}







char vector_private_revise_index (int index, int size) {
	
	if (index >= size) {
		perror ("Asking for %d'th element in the vector containing %d elements!\n", index, size);
		return 0;
	}
	
	if (index < 0) {
		perror ("Asking for the element with negatize index %d!\n", index);
		return 0;
	}
	
	return 1;
	
}
