#include <stdlib.h>
#include "../api.h"

typedef struct vector_variables_t {
	int size;
	int counter;
	void** array;
} vector_variables_t;


/* Very important define! As Sequential* instance->vars is of type void*
 * to be compatible with List, it's necessary to conduct defined type convertion
 * every time when trying to get access to the internal variables of instance->vars
 */
 
#define vrs ((vector_variables_t*)(this->vars))


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

char vector_private_revise_index (int index, int size);
char vector_private_validate_instance (Sequential* this);



/*--------------------------------------------------------
			VECTOR CONSTRUCTOR
--------------------------------------------------------*/


Sequential* vector_create (int size, void** initial_content) {
	
	if (size <= 0) {
		perror ("Invalid vector size!\n");
		return NULL;
	}

	if (initial_content == NULL) {
		perror ("Invalid initial values array!\n");
		return NULL;
	}
	
	Sequential* this = (Sequential*) calloc (1, sizeof (Sequential));

	this->vars = (void*) calloc (1, sizeof (vector_variables_t));
	vrs->array = (void**) calloc (size, sizeof (void*));
	
	for (int i = 0; i < size; i++) {
		vrs->array[i] = initial_content[i];
	}
	
	vrs->size = size;
	vrs->counter = size;
	
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
			VECTOR DESTRUCTOR
--------------------------------------------------------*/

void vector_destroy (Sequential* this) {
	
	if (vector_private_validate_instance (this)) {
		
		free (vrs->array);
		free (this->vars);
		free (this);
		
	}
	
}


/*--------------------------------------------------------

--------------------------------------------------------*/

void vector_push_front (Sequential* this, void* content) {

	

}


/*--------------------------------------------------------
			FIRST ELEMENT SETTER (ADDS NEW ONE)
--------------------------------------------------------*/

void vector_push_back (Sequential* this, void* content) {

	if (vector_private_validate_instance (this)) {
		
		this->resize (this, vrs->size + 1);
		
		for (int i = vrs->size - 2; i >= 0; i--) 
			vrs->array[i + 1] = vrs->array[i];
		
		vrs->array[0] = content;
	}

}


/*--------------------------------------------------------
			LAST ELEMENT GETTER
--------------------------------------------------------*/

void* vector_pull_front (Sequential* this) {

	if (!vector_private_validate_instance (this)) return NULL;
	
	return vrs->array[vrs->size - 1];

}


/*--------------------------------------------------------
			THE 1st ELEMENT GETTER
--------------------------------------------------------*/

void* vector_pull_back (Sequential* this) {

	if (!vector_private_validate_instance (this)) return NULL;
	
	return vrs->array[0];

}


/*--------------------------------------------------------
			REWRITES THE ELEMENT
--------------------------------------------------------*/

void vector_rewrite (Sequential* this, int index, void* content) {

	if (vector_private_revise_index (index, vrs->size) &&
		vector_private_validate_instance (this)) {
		vrs->array[index] = content;
	}
}


/*--------------------------------------------------------
			VECTOR ELEMENT GETTER
--------------------------------------------------------*/

void* vector_get (Sequential* this, int index) {

	if (!vector_private_revise_index (index, vrs->size) || 
		vector_private_validate_instance (this)) return NULL;
	
	return vrs->array[index];

}


/*--------------------------------------------------------
			VECTOR RESIZE FUNCTION
--------------------------------------------------------*/

void vector_resize (Sequential* this, int size) {

	if (vector_private_validate_instance (this)) {

		if (size <= 0) {
			perror ("Invalid vector size %d for resize operation!\n");
			return;
		}
		
		int old_size = vrs->size;
		vrs->size = size;
		
		void** new_array = (void**) calloc (size, sizeof (void*));
		
		for (int i = 0; i < old_size && i < size; i++) 
			new_array[i] = vrs->array[i];
			
		if (old_size < size) {
			for (int i = old_size; i < size; i++) 
				new_array[i] = 0;
		}
		
		free (vrs->array);
		vrs->array = new_array;
		vrs->counter += size - old_size;
	
	}
	
}


/*--------------------------------------------------------
			2 ELEMENTS SWAP FUNCTION
--------------------------------------------------------*/

void vector_swap (Sequential* this, int index1, int index2) {

	if (vector_private_revise_index (index1, vrs->size) &&
		vector_private_revise_index (index2, vrs->size) &&
		vector_private_validate_instance (this)) {
			
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

void vector_insert (Sequential* this, int index, void* content) {
	
	if (vector_private_revise_index (index, vrs->size) && 
		vector_private_validate_instance (this)) {
		this->resize (this, vrs->size + 1);
		
		for (int i = vrs->size - 2; i >= index; i--) 
			vrs->array[i + 1] = vrs->array[i];
			
		vrs->array[index] = content;
	}

}







char vector_private_revise_index (int index, int size) {
	
	if (index >= size) {
		//perror ("Asking for %d'th element in the vector containing %d elements!\n", index, size);
		perror ("Asking for element with an invalid index!\n");
		return 0;
	}
	
	if (index < 0) {
		//perror ("Asking for the element with negatize index %d!\n", index);
		perror ("Asking for the element with negatize index!\n");
		return 0;
	}
	
	return 1;
	
}


char vector_private_validate_instance (Sequential* this) {
	
	if (this == NULL) {
		perror ("Invalid vector pointer!\n");
		return 0;
	}
	
	if (vrs->size <= 0) {
		//perror ("Invalid size %d of the vector!\n", vrs->size);
		perror ("Invalid size of the vector!\n");
		return 0;
	}
	
	if (vrs->array == NULL) {
		perror ("Vector was not initialized properly!\n");
		return 0;
	}
	
	if (vrs->counter >= vrs->size || vrs->counter < 0) {
		//perror ("Invalid internal pointer %d in the vector containing %d elements!\n", vrs->counter, vrs->size);
		perror ("Invalid internal pointer in the vector!\n");
		return 0;
	}
	
	return 1;
}
