#include "mymalloc.h"
void * mymalloc(int min_size){
	static struct meta *master; 
	struct meta *current_meta;
	struct meta *temp; //Just a temp one to hold next before it is put into the linked list
	if(min_size > 4080){
		printf("%s\n", "error.");
		return NULL;
	}

	if(memory[0] != magic1 ||  memory[1] != magic2 ){ //For the first time malloc is called.
		memory[0] = magic1;
		memory[1] =  magic2;
		master = (struct meta*) memory;
		master->inuse = 'b';
		master->size = min_size;
	}
	current_meta = master;
	printf("%c\n", current_meta->inuse);
	while(current_meta != 0){
		if(current_meta->inuse == 'b'){
			current_meta = current_meta->next; //Broke here
		}
//		else if(current_meta->inuse != 'b' && current_meta->size < (min_size + sizeof(struct meta))){
//			current_meta->inuse = NULL;
//		}
		else{
			temp = (struct meta*)((char*)current_meta + sizeof(struct meta) + min_size);
			temp->size = min_size;
			printf("%s\n", "Does it make it here");
			printf("%d\n", temp->size);
			temp->last = current_meta;
			temp->next = current_meta->next;
			current_meta = 0;
			return 0; 
		}
	}
}
int main(){
	malloc(1000);
	malloc(500);
	malloc(250);
	malloc(125);
	malloc(75);
}
