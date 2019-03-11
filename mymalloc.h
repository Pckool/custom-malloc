#ifndef MYMALLOC_H
#define MYMALLOC_H
#include <stdlib.h>
#define SIZE 4096
#define MAGIC 11119
#define META 2
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)
static unsigned char RAM[SIZE];
unsigned short int flag_get(unsigned short int index);
unsigned short int getLength(unsigned short int index);
void setLength(unsigned short int index, unsigned short int length);
void setFlag(unsigned short int index, unsigned short int flag);
void* mymalloc(size_t size, const char* fname, int lineno);
void myfree(void* ptr, const char* fname, int lineno);
#endif
