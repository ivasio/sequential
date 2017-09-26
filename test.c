#include <stdlib.h>
#include <stdio.h>
#include "api.h"

int main (int argc, char** argv) {
	
	char array[50];
	for (int i = 0; i < 50; i++) array[i] = 'a';
	Sequential* container = vector_create (50, (void**)array, sizeof (char));
	printf ("Size = %d\n", container->get_size (container));
	
	/* ===========================================
	 * 			end + set + get + prev test
	 * ===========================================
	 */
	/*
	Iterator ptr = container->iterator_init (container);
	container->end (container, ptr);
	
	for (int i = 4; i >= 0; i--) {
		printf ("%d : %d\n", i, (int)container->get (container, ptr));
		container->set (container, ptr, (void*)i);
		printf ("Changed %d : %d\n", i, (int)container->get (container, ptr));
		
		container->prev (container, ptr);
	}
			
	container->iterator_destroy (ptr);
	*/

	/* ===========================================
	 * 			swap test
	 * ===========================================
	 */
	/*
	Iterator ptr1 = container->iterator_init (container);
	Iterator ptr2 = container->iterator_init (container);
	container->next (container, ptr2);
	
	printf ("%d : %d\n", 0, (int)container->get (container, ptr1));
	printf ("%d : %d\n", 1, (int)container->get (container, ptr2));
	
	container->swap (container, ptr1, ptr2);	
	
	printf ("%d : %d\n", 0, (int)container->get (container, ptr1));
	printf ("%d : %d\n", 1, (int)container->get (container, ptr2));
	
	container->iterator_destroy (ptr1);
	container->iterator_destroy (ptr2);
	*/
	
	/* ===========================================
	 * 			insert (+ resize) test
	 * ===========================================
	 */
	
	Iterator ptr = container->iterator_init (container);
	container->end (container, ptr);
	
	printf ("%c\n", (int)container->get(container, ptr));
	
	container -> insert (container, ptr, (void*)'f');
	printf ("Size = %d\n", container->get_size (container));
	printf ("%c\n", (int)container->get(container, ptr));
		
	container->destroy (container);
	
	return 0;
}
