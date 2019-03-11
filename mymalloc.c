#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include "mymalloc.h"

//SETTER FUNCTIONS

//Sets the first bit of the metadata (which is 2 bytes) to whatever is inputed. Like said before 1 means used and 0 means not used. |= is the bit wise operator for 'or'.
void flag_set(unsigned short int index, unsigned short int flag){
	unsigned short int * meta = (unsigned short int *)&RAM[index];
	//This makes sure that mast only reads the first bit
	unsigned short int mask = ~1;
	*meta &= mask;
        *meta |= flag;
}
//Sets the remainder of the 2 bytes to deal with the legnth of the block. Takes up 15 bits I believe. Each byte is 8 bits and 1 bit is used on the flag.
void length_set(unsigned short int index, unsigned short int length){
         unsigned short int * meta = (unsigned short int *)&RAM[index];
         // Create a mask that clears the length bits
         unsigned short int clear = 1;
         *meta &= clear;
         // The length is everything but the Least Significant Bit of the block
         *meta |= length << 1;
 }

//GETTER FUNCTIONS

//Returns the flag which is the first bit of the meta data.
unsigned short int flag_get(unsigned short int index){
	unsigned short int * meta = (unsigned short int *)&RAM[index];
	unsigned short int flag = (*meta) & 1;
	return flag;
}
// Returns everything but the first bit of the meta data as that is where the length of the block is stored
unsigned short int length_get(unsigned short int index){
 	unsigned short int * meta = (unsigned short int *)&RAM[index];
 	unsigned short int length = (*meta) >> 1;
 	return length;
}
void* mymalloc(size_t size, const char* fname, int lineno){
	int * magic = (int*)RAM;
	//Only done once to check to see if malloc has been called before. If not it goes into this if statement
	if (*magic != MAGIC){
		*magic = MAGIC;
		unsigned short int* meta = (unsigned short int*)&RAM[4];
		*meta = 0;
		unsigned short int length = SIZE - 6;
		*meta |= length << 1;
	}
	if(size > SIZE - (4 + META) || size <= 0){
		//Error for when the size they are trying to allocate is too large.
		if(size > SIZE - (4 + META))
		{
			fprintf(stderr, "Error in mymalloc call in file %s, line %d: Can't malloc something that big.\n", fname, lineno);
		}
		//Error for when the size they are trying to allocate is zero or a negative.
		else
		{
			fprintf(stderr, "Error in mymalloc call in file %s, line %d: Size can't be zero or smaller.\n", fname, lineno);
		}
		return NULL;
	}
	unsigned short int mem_size = (unsigned short int)size;
	unsigned short i = 4;
	//Checking to make sure i is in range of the array.
	while(i < SIZE - META){
		// Get the length and the flag of the block you are looking at.
		unsigned short int blockl = length_get(i);
		unsigned short currflag = flag_get(i);
        	//Checks to make sure that the block it is looking at is not being used.
		if(!currflag){
			if((blockl == mem_size) || (blockl > META + mem_size)){
				flag_set(i, 1);
				length_set(i, mem_size);
				if(blockl > META + mem_size){
					unsigned short int length_new = blockl - (META + mem_size);
					unsigned short int new_i = i + META + mem_size;
					flag_set(new_i, 0);
					length_set(new_i, length_new);
				}
				return (void *)&RAM[i+2];
			}
			//This is for when the block can hold the data but isnt big enough to be broken up.
			else if(blockl > mem_size && blockl <= META + mem_size){
				flag_set(i, 1);
				return (void *)&RAM[i+2];
			}
			else{
				//Moves to the next meta data block
				i += (META + blockl);
			}
		}
		//The meta data block is already being used.
		else
		{
			i += (META + blockl);
		}
	}
	//Error for when there is not enough space for the malloc.
	fprintf(stderr, "Error in mymalloc at file %s, line %d: Not enough space for malloc call.\n", fname, lineno);
	return NULL;

}

void myfree(void* ptr, const char* fname, int lineno)
{
	//Every time free is called it goes to the start of the meta data blocks.
	unsigned short int curr = 4;
	unsigned short int last = 0;
	unsigned char * ptrb = (unsigned char *)ptr;
	if(ptrb == NULL){
		fprintf(stderr, "Error in myfree at file %s, line %d: Cant free NULL pointers.\n", fname, lineno);
		return;
	}
	//Incase wwe go out of bounds of the array
	if(ptrb < RAM + 4 || ptrb > RAM + (SIZE - META - 1)){
		//Print an error and exit.
		fprintf(stderr, "Error in myfree at file %s, line %d: Pointer at address: %X is out of bounds.\n", fname, lineno, ptr);
		return;
	}
	//Goes through the array until we hit the pointer we want to free.
	while(RAM + curr <= ptrb - META){
		if(RAM + curr == ptrb - META){
			//Makes sure we are freeing an allocated block
			if(flag_get(curr)){
				flag_set(curr, 0);
				// Defraging
				unsigned short int next = curr + META + length_get(curr);
				if(last == 0 || flag_get(last) == 1){
					if(next < SIZE && flag_get(next) == 0){
						unsigned short int length_new = length_get(curr) + META + length_get(next);
						length_set(curr, length_new);
					}
				}
				else{
					if(next < SIZE && flag_get(next) == 0){
						unsigned short int length_new = (length_get(last) + META + length_get(curr) + META + length_get(next));
						length_set(last, length_new);
					}
					else{
						unsigned short int length_new = length_get(last) + META + length_get(curr);
						length_set(last, length_new);
					}
				}
				return;
			}
			//Error for when they are trying to free a pointer thats already been freed.
			else{
				fprintf(stderr, "Error in myfree at file %s, line %d: Pointer at address %X, has already been freed.\n", fname, lineno, ptr);
				return;
			}
		}
		last = curr;
		curr += (META + length_get(curr));
	}
	//Error for when it is not a dynamic variable
	fprintf(stderr, "Error in myfree at file %s, line %d: The adrress: %X doesn't point to a dyanimcally alllocated variable.\n", fname, lineno, ptr);
	return;
}
