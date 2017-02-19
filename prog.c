#include <stdio.h>
#include "api.h"

int main(){

	char* arr[4] = {"1", "2", "3", "4"};
	printf("prog first\n");
	Sequential* c = list_create(4, (void**)arr);
	//printf("%p\n", ((list*)(c->vars))->head);
	char ch = '5'; 
	push_back(c, (void*)(&ch));
	void* str = pull_back(c);
	printf("%p %s\n", str,(char*)str);
	free(str);
	destroy(c);
	printf("%p\n", (void*)(c->vars));

	return 0;

}
