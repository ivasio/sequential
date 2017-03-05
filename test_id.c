#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "api.h"

int is_type(char* str);
int is_space(char ch);
void skipspace(char* buffer, int* index);

int main(int argc, char* argv[]){

	char* fin = NULL;

	if (argc == 2){
		fin = (char*)malloc(sizeof(char)*strlen(argv[1]));
		strcpy(fin, argv[1]);
	}
	else {
		fin = (char*)malloc(sizeof(char)*11);
		strcpy(fin, "input.txt");
	}

	FILE* file = fopen(fin, "r");

	fseek(file, 0, SEEK_END);
	int size = ftell(file);
	rewind(file);

	char *buffer = (char*)calloc(size + 1, sizeof(*buffer));
	fread((char*)buffer, size, sizeof(*buffer), file);
	if (buffer == 0) 
		perror("fread");
	printf("%d\t %p\n", size, buffer);

	Sequential* c = list_create(1, (void**)"~~", sizeof(char*));
	Iterator ptr = c->iterator_init (c);
	//c->end(c, ptr);
	//c->set(c, ptr, "~~");
	printf("%p\n", c->get(c, ptr));
	//char* fff = (char*)c->get(c, ptr);
	//printf("%s\n", (char*)(c->get(c, ptr)));
	int index = 0;
	int i = 0;
	int k = 0;
	int is_good = 0;
	int len = 0;
//////////////////////////////////////////////////
//START OF PARSING
//////////////////////////////////////////////////
	while (index < size){
		//printf("%c", buffer[index]);
		if (is_space(buffer[index])){
			//printf("len %d\n", len);
			char* str = (char*)malloc(sizeof(char)* (len+1));
			k = 0;
			for(i = index - len; i < index; i++)
				str[k++] = buffer[i];
			str[k] = 0;
			if (!strcmp(str, "=")){
				while((buffer[index] != ';') && (buffer[index] != ','))
					index++;
			}
			if (is_good){
				c->end(c, ptr);
				c->insert(c, ptr, str);	
				//printf("%p\n", c->get(c, ptr));
				is_good = 0;
			}
			else if (is_type(str)){
				is_good = 1;
				//printf("str %s\n", str);
			}
			else
				free(str);
			len = 0;
			skipspace(buffer, &index);
		}
		else{
			len++;
			index++;
		}
		//
	}
//////////////////////////////////////////////////
//END OF PARSING
//////////////////////////////////////////////////

//////////////////////////////////////////////////
//START OF DISTINCT
//////////////////////////////////////////////////



//////////////////////////////////////////////////
//END OF DISTINCT
//////////////////////////////////////////////////


	Iterator sptr = c->iterator_init(c);
	c->begin(c, sptr);
	c->end(c, ptr);
	c->prev(c, ptr);
	printf("IM HERE\n");
	c->next(c, sptr);
	while(*sptr != *ptr){
		printf("%s\n", (char*)(c->get(c, sptr)));
		c->next(c, sptr);
	}
	printf("%s\n", (char*)(c->get(c, sptr)));
	
//////////////////////////////////////////////////
//CLEANING
//////////////////////////////////////////////////
	c->iterator_destroy(ptr);
	c->iterator_destroy(sptr);
	c->destroy(c);
	if (buffer)
		free(buffer);
	fclose(file);

	return 0;
}

void skipspace(char* buffer, int* index){

	while(is_space(buffer[*index]))
		(*index)++;

}

int is_space(char ch){

	if ((ch == ' ') || (ch == '\t') || (ch == '\n') || (ch == '*') || (ch == ';') || (ch == ',') || (ch == '(') || (ch == '[') || (ch == '{') || (ch == ')') || (ch == ']') || (ch == '}'))
		return 1;
	else
		return 0;
}

int is_type(char* str){

	return (!strcmp(str, "int") || !strcmp(str, "char")|| !strcmp(str, "void") || !strcmp(str, "float") || !strcmp(str, "double") || !strcmp(str, "struct") );

}
