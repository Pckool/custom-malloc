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
//testTwo: malloc 150 1 byte pointers, then free all the pointers after
void testTwo(){
	char* pntrs[150];
	int i = 0;
	int x = 0;
		while(x < 3){
			for(i = 0; i < 150; i++){
				pntrs[i] = (char*) malloc(1);
			}
			for(i = 0; i < 150; i++){
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
			free(pntrs[free_done]);
			free_done += 1;
		}
	}
	if(malloc_done = 50){
		while(free_done < 50){
			free(pntrs[free_done]);
			free_done += 1;
		}
	}
}
//testFour: Randomly chooses to malloc a randomly size pointer that is size between 1-64 or freeing a pointer. Tracks to make sure that the mallocs do not exceed the
//max size of the array. Once malloc is called 50 times it iterates through the array of pointers freeing them all.
void testFour(){
		char*pntrs[50];
		int malloc_done = 0;
		int free_done = 0;
		int i = 0;
		int total_malloc = 0;
		while(malloc_done < 50){
			int randoms = rand() % 2;
			if(randoms == 0){
				int random_size = (rand() % 50) + 1;
				if((total_malloc + random_size)  > 4016){
					random_size = (rand() % (4096 - total_malloc) + 1);
				}
			pntrs[malloc_done] = (char*) malloc(random_size);
			malloc_done += 1;
			total_malloc = total_malloc + random_size + 16;
		}
		else if(randoms == 1){
			free(pntrs[free_done]);
			free_done += 1;
		}
	}
	if(malloc_done = 50){
		for(i = 0; i < 50; i++){
			free(pntrs[i]);
		}
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
	free(a + 10);
	free(b - 6);
	free(c);
	free(x);
	free(x + 800);
	free(y);
	free(z);
	free(a);
	free(b);
}
int main(){
	struct timeval time1;
	struct timeval time2;
	long totaltime;
	int q = 0;
	srand(time(NULL));
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
	
	printf("\n-------------------TEST 4-------------------\n");
		gettimeofday(&time1, 0);
		for(q = 0; q < 100; q++) {
			testFour();
		}	
    gettimeofday(&time2, 0);
    totaltime= (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
    printf("Average time of test 4: %luμs\n", totaltime / 100);
    //Add function call that prints the memory
	
	printf("\n-------------------TEST 5-------------------\n");
		gettimeofday(&time1, 0);
		for(q = 0; q < 100; q++) {
			testFive();
		}	
    gettimeofday(&time2, 0);
    totaltime= (time2.tv_sec-time1.tv_sec)*1000000 + time2.tv_usec-time1.tv_usec;
    printf("Average time of test 4: %luμs\n", totaltime / 100);
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
