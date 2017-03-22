#include <stdio.h>
#include <stdlib.h>
#include "gtest/gtest.h"
	
extern "C" {
#include "api.h"
}

void character_test (Sequential* (*constructor)(int , void** , size_t));

TEST(Vector_Test, Characters) {

	character_test (vector_create);
	
}

void character_test (Sequential* (*constructor)(int , void** , size_t)) {
	
	char array[3] = {'a', 'b', 'c'};
	Sequential* container = (*constructor) (3, (void**)array, sizeof (char));
	
	// Checking the size of the container (get_size method)
	
	EXPECT_EQ(3, container->get_size (container));	
	
	Iterator ptr = container->iterator_init (container);
	
	// Comparing all the elements af the container with those
	// from the original array (in_range, next, get methods)
	
	int i = 0;
	while (container->in_range (container, ptr)) {
		EXPECT_EQ(array[i], (char)container->get (container, ptr));
		container->next (container, ptr);
		i++;
	}
	
	// Checking for in_range to reach the last element
	
	EXPECT_EQ(i, container->get_size (container));
	
	// Inserting 'd' after the second letter (begin, next, insert methods)
	container->begin (container, ptr);
	container->next (container, ptr);
	EXPECT_EQ('b', (char)container->get (container, ptr));
	container->insert (container, ptr, (void*)'d');
	
	// Checking if iterator points on the inserted element
	
	EXPECT_EQ('d', (char)container->get (container, ptr));
	
	// Checking the values of other elements
	
	container->next (container, ptr);
	i = 2;
	while (container->in_range (container, ptr)) {
		EXPECT_EQ(array[i], (char)container->get (container, ptr));
		container->next (container, ptr);
		i++;
	}
	
	// Checking if get_size returns new actual size
	
	EXPECT_EQ(i+1, container->get_size (container));
	
	// Changing the last element (set method)
	
	Iterator ptr2 = container->iterator_init (container);
	container->end (container, ptr2);
	container->set (container, ptr2, (void*)'x');
	EXPECT_EQ('x', (char)container->get (container, ptr2));
		
	// Swaping the first and the last elements (swap method)
	
	container->begin (container, ptr);
	container->swap (container, ptr, ptr2);
	EXPECT_EQ('x', (char)container->get (container, ptr));
	EXPECT_EQ('a', (char)container->get (container, ptr2));
	
	
	container->iterator_destroy (ptr);
	container->iterator_destroy (ptr2);
	container->destroy (container);
	
}
