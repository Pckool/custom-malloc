#include <stdio.h>
#include <time.h>
#include "mymalloc.h"
//testOne: malloc 1 1 byte pointer, then free it immediately. Does this 150 times.
void testOne(){
	int i = 0;
	char* a;
	for(i = 0; i < 150; i++){
		a = (char*) malloc(1);
		free(a);
	}
}
//testTwo: malloc 50 1 byte pointers, then free all the pointers after. Does this 150 times
void testTwo(){
	char* pntrs[50];
	int i = 0;
	int x = 0;
		while(x < 3){
			for(i = 0; i < 50; i++){
				pntrs[i] = (char*) malloc(1);
			}
			for(i = 0; i < 50; i++){
				free(pntrs[i]);
			}
			x += 1;
		}
}
//testThree: Randomly chooses to malloc a 1 byte pointer, or free a 1 byte pointer. Once it mallocs 50 1 byte pointers it just iterates through the array of pointers
//freeing all of them.
void testThree(){
	char* pntrs[50];
	int malloc_done = 0;
	int free_done = 0;
	int i = 0;
	while(malloc_done < 50){
		int randoms = rand() % 2;
		if(randoms == 0){
			pntrs[malloc_done] = (char*) malloc(1);
			malloc_done += 1;
		}
		else if(randoms == 1){
			while(malloc_done > free_done){
				free(pntrs[free_done]);
				free_done += 1;
			}
		}
	}
	if(malloc_done == 50){
		while(free_done < 50){
			free(pntrs[free_done]);
			free_done += 1;
		}
	}
}
//testFour: Randomly chooses to malloc a randomly size pointer that is size between 1-64 or freeing a pointer. Tracks to make sure that the mallocs do not exceed the
//max size of the array. Once malloc is called 50 times it iterates through the array of pointers freeing them all.
void testFour(){
	char* pntrs[50];
	int total_size = 0;
	int mallocs_called = 0;
	int frees_called = 0;
	int sizes[50];
	int i;
	while (mallocs_called < 50){
		int odds = rand() % 2;
		if (odds == 0){
			int size = (rand() % 63) + 1;
			sizes[i] = size + 20;
			total_size = total_size + size + 20;
			if(total_size >= 4000){
				if(mallocs_called > frees_called){
					free(pntrs[frees_called]);
					total_size = total_size - sizes[frees_called];
					frees_called += 1;
				}
				total_size = 0;
			}
			else{
				pntrs[mallocs_called] = (char*) malloc(size);
				mallocs_called += 1;
			}
		}
		else {
			if(mallocs_called > frees_called){
				free(pntrs[frees_called]);
				total_size = total_size - sizes[frees_called];
				frees_called +=1;
			}
		}
	}
	while(mallocs_called > frees_called){
		free(pntrs[frees_called]);
		frees_called += 1;
	}
} 
//testFive: Mallocs a pointer of 1000 bytes and a pointer of 5000. Should catch the the second malloc and send back an error. Then it frees both pointers. 
//Should free the first pointer and then catch the second free and send back an error. Then it tries to free both pointers again. This time it should
//catch both of them and send back an error for both.
void testFive(){
	char* a;
	char* b;
	a = (char*) malloc(1000);
	b = (char*) malloc(5000);
	free(a);
	free(b);
	free(a);
	free(b);
}
//testSix: Makes three char pointers and one int. Mallocs the three pointers and then tries freeing adress that are not the pointer and tries to free the int.
//Should catch these frees and send back errors. At the end it does actually free them.

void testSix(){
	char* a;
	char* b;
	char* c;
	int x = 45;
	int y = 10;
	int z = NULL;
	a = (char*) malloc(500);
	b = (char*) malloc(500);
	c = (char*) malloc(500);
	printf("%c\n", 'a');
	free(a + rand() % 4000);
	printf("%c\n", 'b');
	free(b - rand() % 4000);
	printf("%c\n", 'c');
	free(c);
	printf("%c\n", 'd');
	free(x);
	printf("%c\n", 'e');
	free(y);
	printf("%c\n", 'f');
	free(z);
	printf("%c\n", 'g');
	free(a);
	printf("%c\n", 'h');
	free(b);

}
int main(){

	struct timeval time1;
	struct timeval time2;
	long totaltime;
	int q = 0;
	srand(time(NULL));
/*
    // Runs test one 100 times and records the times. 
	printf("\n-------------------TEST 1-------------------\n");
	gettimeofday(&time1, 0);
	for(q = 0; q < 100; q++){
		testOne();
	}
	gettimeofday(&time2, 0);
    	totaltime = (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
	printf("Average time of test 1: %luμs\n", totaltime / 100);
	//Add function call that prints the memory
	
	printf("\n-------------------TEST 2-------------------\n");
		gettimeofday(&time1, 0);
		for(q = 0; q < 100; q++) {
			testTwo();
		}	
    	gettimeofday(&time2, 0);
    	totaltime= (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
    	printf("Average time of test 2: %luμs\n", totaltime / 100);
    	//Add function call that prints the memory

    	printf("\n-------------------TEST 3-------------------\n");
	gettimeofday(&time1, 0);
	for(q = 0; q < 100; q++) {
		testThree();
	}	
    	gettimeofday(&time2, 0);
    	totaltime= (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
    	printf("Average time of test 3: %luμs\n", totaltime / 100);
    	//Add function call that prints the memory

*/

	printf("\n-------------------TEST 4-------------------\n");
	gettimeofday(&time1, 0);
	for(q = 0; q < 100; q++) {
		testFour();
	}	
    	gettimeofday(&time2, 0);
    	totaltime= (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
    	printf("Average time of test 4: %luμs\n", totaltime / 100);
   	//Add function call that prints the memory

/*

	printf("\n-------------------TEST 5-------------------\n");
	gettimeofday(&time1, 0);
	for(q = 0; q < 100; q++) {
		testFive();
	}	
    	gettimeofday(&time2, 0);
    	totaltime= (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
    	printf("Average time of test 5: %luμs\n", totaltime / 100);
    	//Add function call that prints the memory


	printf("\n-------------------TEST 6-------------------\n");
	gettimeofday(&time1, 0);
	for(q = 0; q < 100; q++) {
		testSix();
	}	
    	gettimeofday(&time2, 0);
    	totaltime= (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
    	printf("Average time of test 6: %luμs\n", totaltime / 100);
    	//Add function call that prints the memory
*/

	return 0;
}

