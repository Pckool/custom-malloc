#include <stdio.h>
#include <stddef.h>
#include "mymalloc.h"

void * mymalloc(size_t min_size){
	if(min_size >= SIZE){
			printf("error1: Tried to allocate memory larger than or equal to the entire memory block\n");
			return NULL;
		}
	// creating two pointers to use (curr and last) during the progress of mymalloc
	struct meta *curr,*last;
	void *pointer;
	// if the size of the first metadata is zero, then...
	if((initList->size)==0){
		// we have not initialized the array. Let's do that now
		init();
		// done!
	}

	// this is our current block (the init meta block)
	curr = initList;

	// checking the metadata one by one until we reach a block that can fit or we reach NULL (no next meta block).
	while((curr->next != NULL) && (((curr->empty) == 0) || ((curr->size) < min_size))){
		// set the last mata to the current one (temp)
		last = curr;
		// set the curr meta to the next one (or NULL)
		curr = (curr->next);
	}
	// if there is a block with the exact amount of space needed for the allocation
	if((curr->size) == min_size){
		// curr is now in use
		curr->empty = 0;
		//
		pointer = (void*)(++curr);
		// return the pointer to the metadata of the allocated memory
		return pointer;
	}
	// if there is a block available with more than enough space for the allocation
	else if((curr->size) > (min_size + sizeof(struct meta))){
	// segmenting the large memory block
		segment(curr, min_size);
		//
		pointer = (void*)(++curr);
		// return the pointer to the metadata of the allocated memory
		return pointer;
	}
	// if there is no block with suficient memory
	else{
		result = NULL;
		printf("error0: There was no memory to allocate\n");
		// return a null pointer
		return pointer;
	}







// 	static struct meta *master;
// 	struct meta *current_meta;
// 	struct meta *temp; //Just a temp one to hold next before it is put into the linked list
// 	if(min_size > SIZE){
// 		printf("%s\n", "error.");
// 		return NULL;
// 	}
//
//
//
//
// 	if(memory[INIT] == '\0'){
// 		int i;
// 		for(i=0; i<SIZE; ++i){
// 			memory[i] = '\0';
// 		}
// 		memory[INIT] = 'i';
// 		memory[START] = 'f';
// 		*(int*)(&memory[START + 1]) = 19994; // Take an address, cast into an int pointer
// 		printf("Initialized\n");
// 	}
// 	int i = STRT;
//
// 	if(min_size > SIZE){
// 		printf("%s\n", "error.");
// 		return NULL;
// 	}
//
//
// 	if(memory[0] != magic1 ||  memory[1] != magic2 ){ //For the first time malloc is called.
// 		memory[0] = magic1;
// 		memory[1] =  magic2;
// 		master = (struct meta*) memory;
// 		master->empty = 'b';
// 		master->size = min_size;
// 	}
// 	current_meta = master;
// 	printf("%c\n", current_meta->empty);
// 	while(current_meta != 0){
// 		if(current_meta->empty == 'b'){
// 			current_meta = current_meta->next; //Broke here
// 		}
// //		else if(current_meta->empty != 'b' && current_meta->size < (min_size + sizeof(struct meta))){
// //			current_meta->empty = NULL;
// //		}
// 		else{
// 			temp = (struct meta*)((char*)current_meta + sizeof(struct meta) + min_size);
// 			temp->size = min_size;
// 			printf("%s\n", "Does it make it here");
// 			printf("%d\n", temp->size);
// 			temp->last = current_meta;
// 			temp->next = current_meta->next;
// 			current_meta = 0;
// 			return 0;
// 		}
// 	}
}

void myfree(void* pointer){
	// check if the pointer leads to a valid memory location
	// if it does,
	if((pointer <= (void*)(memory+SIZE)) && ((void*)memory<=pointer)){
		// set the metadata to empty=1
		struct meta *curr = pointer;
		--curr;
		curr->empty = 1;
		// then defragment
		defrag();
	}
	// else
	else{
		// print out an error message
		printf("error2: You did not give a valid malloc pointer.\n");
	}


}

/**
 * This function will defragment the memory blocks.
 */
void defrag(){
	// you know what this line means lol
	struct meta *curr, *last;
	// the current is equal to the start
	curr = initList;
	// while there is a next metadata...
	while((curr->next) != NULL){
		// if curr is empty (unallocated) and the next block is empty (unallocated)...
		if((curr->empty) && (curr->next->empty)){
			// set the current meta size to the size of the next block and it's metadata
			curr->size += (curr->next->size) + sizeof(struct meta);
			// the next meta in the current meta is set to the next meta in the next meta (does that even make sense? It does to me so lmao)
			curr->next = curr->next->next;
		}
		// the last meta is now equal to the current meta
		last = curr;
		// the current meta is now equal to the next meta
		curr = curr->next;
		// these last two lines we are basically traversing the different metadatas in the linked list
	}

}

/**
 * used to set the initial size of memory able to be used.
 */
void init(){
	// initial metadata
	initList->size=SIZE-sizeof(struct meta);
	initList->empty=1;
	initList->next=NULL;
}

/**
 * Used to segment the given memory size
 */
void segment(struct meta *big_block, size_t size){
	// init a new metadata block
	struct meta *new = (void*)((void*)big_block + size + sizeof(struct meta));

	// make the new metadata
	new->size = (big_block->size) - size - sizeof(struct meta);
	new->empty = 1;
	new->next = big_block->next;

	// allocate the given memory block define the next metadata in the link as the one created
	big_block->size = size;
	big_block->free = 0;
	big_block->next = new;
}
