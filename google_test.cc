#include <stdio.h>
#include <stdlib.h>
#include "gtest/gtest.h"
	
extern "C" {
#include "api.h"
}

TEST(BasicTest, Equality) {
	
	char array[5] = {'a', 'b', 'c', 'd', 'e'};
	Sequential* container = vector_create (5, (void**)array, sizeof (char));
	
	Iterator ptr = container->iterator_init (container);
	container->end (container, ptr);
	
	EXPECT_EQ('e', (char)container->get(container, ptr));
	
	container->iterator_destroy (ptr);
	container->destroy (container);
	
}

