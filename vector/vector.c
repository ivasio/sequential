#include <stdlib.h>
#include <stdio.h>
#include "../api.h"

typedef struct vector_variables_t {
	int size;
	void** array;
	size_t content_size;
} vector_variables_t;


/* Very important function! As Sequential* instance->vars is of type void*
 * to be compatible with List, it's necessary to conduct this type convertion
 * every time when trying to get access to the internal variables of instance->vars
 */
 
vector_variables_t* vectorof (void* vars) {
	
	return (vector_variables_t*)vars;
	
}

// Vector methods declarations

void vector_destroy (Sequential* this);
	
void vector_resize (Sequential* this, int size);
void vector_swap (Sequential* this, Iterator index1, Iterator index2);
void vector_insert (Sequential* this, Iterator index, void* content);

// Vector iterator methods declarations

Iterator vector_iterator_init (Sequential* this);
void vector_iterator_destroy (Iterator pointer);

void vector_begin (Sequential* this, Iterator pointer);
void vector_end (Sequential* this, Iterator pointer);
void vector_next (Sequential* this, Iterator pointer);
void vector_prev (Sequential* this, Iterator pointer);
void vector_set (Sequential* this, Iterator pointer, void* content);
void* vector_get (Sequential* this, Iterator pointer);
int vector_get_size (Sequential* container);

// Vector service functions declarations

int vector_private_revise_index (Sequential* this, Iterator pointer);
int vector_private_validate_instance (Sequential* this);



//========================================================
// 			Vector methods implementations
//========================================================

/*--------------------------------------------------------
			VECTOR CONSTRUCTOR
--------------------------------------------------------*/


Sequential* vector_create (int size, void** initial_content, size_t content_size) {
	
	// Parameters validation
	if (size <= 0) {
		perror ("Invalid vector size!\n");
		return NULL;
	}

	if (initial_content == NULL) {
		perror ("Invalid initial values array!\n");
		return NULL;
	}
	
	// Allocating the container
	Sequential* this = (Sequential*) calloc (1, sizeof (Sequential));

	// Allocating the variables storage
	this->vars = (void*) calloc (1, sizeof (vector_variables_t));
	vector_variables_t* vars = vectorof (this->vars);
	
	// Initializing the internal variables
	vars->array = (void**) calloc (size, sizeof (void*));
	
	for (int i = 0; i < size; i++) {
		vars->array[i] = *(void**)((char*)initial_content + i * content_size);
		//printf ("%d : %d\n", i, *((char*)initial_content + i * content_size));
	}
	
	vars->size = size;
	vars->content_size = content_size;
	
	
	// Initializing the methods of Vector
	this->destroy = (*vector_destroy);

	this->resize = (*vector_resize);
	this->swap = (*vector_swap);
	this->insert = (*vector_insert);
	
	this->begin = (*vector_begin);
	this->end = (*vector_end);
	this->next = (*vector_next);
	this->prev = (*vector_prev);
	this->set = (*vector_set);
	this->get = (*vector_get);
	this->get_size = (*vector_get_size);
	this->in_range = (*vector_private_revise_index);
	this->iterator_init = (*vector_iterator_init);
	this->iterator_destroy = (*vector_iterator_destroy);

	
	return this;

}


/*--------------------------------------------------------
			VECTOR DESTRUCTOR
--------------------------------------------------------*/

void vector_destroy (Sequential* this) {
	
	if (vector_private_validate_instance (this)) {
		
		vector_variables_t* vars = vectorof (this->vars);
		
		free (vars->array);
		free (this->vars);
		free (this);
		
	}
	
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
		
		vector_variables_t* vars = vectorof (this->vars);
		
		int old_size = vars->size;
		vars->size = size;
		
		void** new_array = (void**) calloc (size, sizeof (void*));
		
		for (int i = 0; i < old_size && i < size; i++) 
			new_array[i] = vars->array[i];
		
		if (old_size < size) {
			for (int i = old_size; i < size; i++) 
				new_array[i] = 0;
		}
		
		free (vars->array); 
		vars->array = new_array;
	
	}
	
}


/*--------------------------------------------------------
			2 ELEMENTS SWAP FUNCTION
--------------------------------------------------------*/

void vector_swap (Sequential* this, Iterator index1, Iterator index2) {

	if (!vector_private_validate_instance (this) || 
		!vector_private_revise_index (this, index1) || 
		!vector_private_revise_index (this, index2)) return;
	
	vector_variables_t* vars = vectorof (this->vars);

	void* temporary = **(void***)index1;
	**(void***)index1 = **(void***)index2;
	**(void***)index2 = temporary;

}


/*--------------------------------------------------------
			INSERT FUNCTION
* Resizes the vector (adding 1 element at the end of it), 
* moves all the values beginning from _index_'th one place
* farther and places _content_ on the _index_'th place
--------------------------------------------------------*/

void vector_insert (Sequential* this, Iterator pointer, void* content) {
	
	if (!vector_private_validate_instance (this) || 
		!vector_private_revise_index (this, pointer)) return;

	vector_variables_t* vars = vectorof (this->vars);

	int offset = *pointer - (void*)(vars->array);
	
	this->resize (this, vars->size + 1);
	offset += sizeof (void*);
	*pointer = (void*)(vars->array) + offset;
	
	int initial_index = (int)(offset / sizeof (void*));
	for (int i = vars->size - 2; i >= initial_index; i--) 
		vars->array[i + 1] = vars->array[i];
	
	**(void***)pointer = content; 
	
}


//========================================================
// 			Vector iterator methods implementations
//========================================================


/*--------------------------------------------------------
			ITERATOR POINTER CONSTRUCTOR +

* Default value - first element
--------------------------------------------------------*/

Iterator vector_iterator_init (Sequential* this) {
	
	if (!vector_private_validate_instance (this)) return NULL;
	
	vector_variables_t* vars = vectorof (this->vars);
	void** pointer = (void**) calloc (1, sizeof (void*));
	*pointer = vars->array;
	return (Iterator)pointer;
	
}


/*--------------------------------------------------------
			ITERATOR POINTER DESTRUCTOR
--------------------------------------------------------*/

void vector_iterator_destroy (Iterator pointer) {
	
	free (pointer);
	
}


/*--------------------------------------------------------
			PLACES THE POINTER ON THE FIRST ELEMENT
--------------------------------------------------------*/

void vector_begin (Sequential* this, Iterator pointer) {

	if (!vector_private_validate_instance (this)) return;

	vector_variables_t* vars = vectorof (this->vars);
	*pointer = (Iterator)(vars->array);

}


/*--------------------------------------------------------
			PLACES THE POINTER ON THE LAST ELEMENT
--------------------------------------------------------*/

void vector_end (Sequential* this, Iterator pointer) {

	if (!vector_private_validate_instance (this)) return;

	vector_variables_t* vars = vectorof (this->vars);
	*pointer = (Iterator)(vars->array + vars->size - 1);

}


/*--------------------------------------------------------
			PLACES THE POINTER ON THE NEXT ELEMENT
--------------------------------------------------------*/

void vector_next (Sequential* this, Iterator pointer) {

	if (!vector_private_validate_instance (this) || 
		!vector_private_revise_index (this, pointer)) return;

	vector_variables_t* vars = vectorof (this->vars);
	
	if (*pointer <= (void*)(vars->array + vars->size - 1))
		*pointer += sizeof (void*);

}


/*--------------------------------------------------------
			PLACES THE POINTER ON THE PREVIOUS ELEMENT
--------------------------------------------------------*/

void vector_prev (Sequential* this, Iterator pointer) {

	if (!vector_private_validate_instance (this) || 
		!vector_private_revise_index (this, pointer)) return;

	vector_variables_t* vars = vectorof (this->vars);
	if (*pointer >= (void*)(vars->array)) 
		*pointer -= sizeof (void*);
	
}


/*--------------------------------------------------------
			VECTOR ELEMENT SETTER
--------------------------------------------------------*/

void vector_set (Sequential* this, Iterator pointer, void* content) {

	if (!vector_private_validate_instance (this) || 
		!vector_private_revise_index (this, pointer)) return;
		
	vector_variables_t* vars = vectorof (this->vars);
	
	**(void***)pointer = content;
		
}


/*--------------------------------------------------------
			VECTOR ELEMENT GETTER
--------------------------------------------------------*/

void* vector_get (Sequential* this, Iterator pointer) {

	if (!vector_private_validate_instance (this) || 
		!vector_private_revise_index (this, pointer)) return NULL;
	
	vector_variables_t* vars = vectorof (this->vars);
	
	return **(void***)pointer;

}


/*--------------------------------------------------------
			VECTOR ARRAY SIZE GETTER
--------------------------------------------------------*/

int vector_get_size (Sequential* this) {
	
	if (!vector_private_validate_instance (this)) return 0;
	
	vector_variables_t* vars = vectorof (this->vars);
	
	return vars->size;
	
}


//========================================================
// 			Vector service functions implementations
//========================================================

int vector_private_revise_index (Sequential* this, Iterator pointer) {

	vector_variables_t* vars = vectorof (this->vars);
	
	if (*pointer >= (void*)(vars->array) && 
		*pointer < (void*)(vars->array + vars->size))
		return 1;
	else
		return 0;
		
}


int vector_private_validate_instance (Sequential* this) {
	
	if (this == NULL) {
		perror ("Invalid vector pointer!\n");
		return 0;
	}
	
	vector_variables_t* vars = vectorof (this->vars);
	
	if (vars->size <= 0) {
		//perror ("Invalid size %d of the vector!\n", vars->size);
		perror ("Invalid size of the vector!\n");
		return 0;
	}
	
	if (vars->array == NULL) {
		perror ("Vector was not initialized properly!\n");
		return 0;
	}
	
	return 1;
}
