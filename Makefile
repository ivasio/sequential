.PHONY: vector list

all: list/list.c vector/vector.c test.c
	gcc -g -std=c99 -c list/list.c
	gcc -g -std=c99 -c vector/vector.c
	ar -rc libseq.a vector.o list.o
	ranlib libseq.a
	gcc  -g -std=c99 test.c -L . -lseq -o test

vector: vector/vector.c test.c
	gcc -g -std=c99 -c vector/vector.c
	ar -rc libseq.a vector.o
	ranlib libseq.a
	gcc  -g -std=c99 test.c -L . -lseq -o test

list: list/list.c test.c
	gcc -g -std=c99 -c list/list.c
	ar -rc libseq.a list.o
	ranlib libseq.a
	gcc  -g -std=c99 test.c -L . -lseq -o test

