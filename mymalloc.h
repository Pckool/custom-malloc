#ifndef _mymalloc_h_
#define _mymalloc_h_
#include <stdlib.h>
#include <stdio.h>
#define malloc(x) mymalloc(x)
#define free(x) myfree(x)
void * mymalloc(int min_size);
void * myfree(void* ptr);
static char* memory[4096];
char magic1 = 'a';
char magic2 = 'x';
struct meta {
	char inuse;
	short int size;
	struct meta *next, *last;
}meta;
#endif
