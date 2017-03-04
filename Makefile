# Make anyway
.PHONY: vector list gtest

# User variables
USER_PROGRAM=test.c
COMPILER=gcc
PRE_FLAGS= -g -std=c99 
POST_FLAGS= -L . -lseq -o test

all: compile ${USER_PROGRAM}
	$(COMPILER) $(PRE_FLAGS) $(USER_PROGRAM) $(POST_FLAGS)

compile:  vector_obj
	ar -rc libseq.a vector.o 
	ranlib libseq.a


vector: vector_obj ${USER_PROGRAM}
	ar -rc libseq.a vector.o
	ranlib libseq.a
	$(COMPILER) $(PRE_FLAGS) $(USER_PROGRAM) $(POST_FLAGS)

list: list_obj ${USER_PROGRAM}
	ar -rc libseq.a list.o
	ranlib libseq.a
	$(COMPILER) $(PRE_FLAGS) $(USER_PROGRAM) $(POST_FLAGS)



list_obj: list/list.c
	gcc -g -std=c99 -c list/list.c

vector_obj: vector/vector.c
	gcc -g -std=c99 -c vector/vector.c


# Compilation with Google test framework


GTEST_DIR= googletest
GTEST_PROGRAM=google_test.cc

gtest: compile libgtest.a
	g++ -fpermissive -isystem ${GTEST_DIR}/include $(GTEST_PROGRAM) -pthread \
		libgtest.a libseq.a ${GTEST_DIR}/src/gtest_main.cc -o google_test

libgtest.a: 
	g++ -isystem ${GTEST_DIR}/include -I${GTEST_DIR} \
		-pthread -c ${GTEST_DIR}/src/gtest-all.cc

	ar -rv libgtest.a gtest-all.o
