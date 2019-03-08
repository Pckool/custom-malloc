#include "mymalloc.h"
void * mymalloc(int min_size){
	static struct meta *master;
	struct meta *current_meta;
	struct meta *temp;
	if(min_size > 4080){
		printf("%s\n", "error.");
		return NULL;
	}

	if(memory[0] != magic1 ||  memory[1] != magic2 ){ //For the first time malloc is called.
		memory[0] = magic1;
		memory[1] =  magic2;
		memory[3] = (struct meta*) memory[3]; //Right here is the I cast a specific part of of the array to a struct pointer so I can store the address of master here and then 
		memory[3] = &master; //should be able to edit it. Some reason it wont let me edit it in line 18, which is causing the seg fault. If we get this to work then
		printf("%p\n", memory[3]); // we have to redo basically everything that is going on below it.
		printf("%p\n", &master);
		memory[3]->size = min_size; //Seg faults here.
	}
	current_meta = master;
	while(current_meta != 0){
		printf("%c\n", current_meta->inuse);
		if(current_meta->inuse == 'b'){
			current_meta = current_meta->next; 
		}
		else{
			temp = (struct meta*)((char*)current_meta + sizeof(struct meta) + min_size);
			temp->size = min_size;
			printf("%s\n", "Does it make it here");
			printf("%d\n", temp->size);
			temp->last = current_meta;
			temp->next = current_meta->next;
			current_meta->size = 0;
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
