all: list/list.c vector/vector.c test.c
	gcc -g -std=c99 -c list/list.c
	gcc -g -std=c99 -c vector/vector.c
	ar -rc libseq.a vector.o list.o
	ranlib libseq.a
	gcc test.c -L . -lseq -o test