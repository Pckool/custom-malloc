#ifndef _mymalloc_h_
#define _mymalloc_h_
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#define malloc(x) mymalloc(x)
#define free(x) myfree(x)
#define INIT 0 // if initialized, not \0. otherwise it will be \0
#define SIZE 4096 // Size of the memory block
#define STRT 5 // the location you can start storing data

static char memory[4096];

struct meta {
	int empty;
	size_t size;
	struct meta *next;
};
struct meta *initList = (void*)memory;

void * mymalloc(size_t min_size);
void myfree(void* pointer);
void init();
void segment(struct meta *chunk, size_t size);
void defrag();


#endif
