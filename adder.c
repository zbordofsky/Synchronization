#include <pthread.h>
#include <getopt.h> 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include "SortedList.h"
#define BILLION  1000000000;

void testerFunc (int argc, char *argv[]); 
void *threadAction(void *pointer); 
void printInfo(struct timespec begin, struct timespec end); 
void add_synC(long long *pointer, long long value); 
//void *minusOne(void *pointer); 
int iterations = 1; 
int numThreads = 1; 
int syncMethod = 0; 
int opt_yield = 0; 
int test_lock = 0; 
int lock = 0; 
pthread_mutex_t mutexAdd; 
void add(long long *pointer, long long value); 

long long *COUNTER = 0; 

int main(int argc, char *argv[]) { 
	//timer function 
	struct timespec beginning, end; 
	clock_gettime(CLOCK_REALTIME, &beginning); 
	testerFunc(argc, argv); 
	clock_gettime(CLOCK_REALTIME, &end); 
	printInfo(beginning, end); 
	pthread_mutex_destroy(&mutexAdd); 
}


void testerFunc (int argc, char *argv[]) 
{ 
	static struct option long_options[] = 
	{
		{"iterations", optional_argument, 0, 'i'}, 
		{"threads", optional_argument, 0, 't'}, 
		{"yield", optional_argument, 0, 'y'},
		{"sync", optional_argument, 0, 's'}, 
		{0, 0, 0, 0}
	}; 
	int opt; 
	
	int option_index = 0; 
	opt = getopt_long(argc, argv, "a", long_options, &option_index); 
	while(opt != -1) 
	{ 
		switch(opt) 
		{
			case 'i':
			if(optarg != NULL)
				iterations = atoi(optarg); 
			if(iterations <=0){ 
					fprintf(stderr, "Invalid number of iterations\n"); 
					exit(1); 
			}
			break; 

			case 't':
			if(optarg != NULL)
				numThreads = atoi(optarg); 
			if(iterations <=0) {
				fprintf(stderr, "Invalid number of threads\n"); 
				exit(1); 
			}
			break; 
			
			case 'y': 
				opt_yield = 1; 
			break; 
			
			case 's': 
				if(optarg[0] != '\0'){ 
					if(optarg[0] == 'm') { 
						syncMethod = 1; 
						pthread_mutex_init(&mutexAdd, NULL); 
					}	 
					else if(optarg[0] == 's') { 
						syncMethod = 2; 
					}
					else if(optarg[0] == 'c'){ 
						syncMethod = 3; 
					}
					else { 
						fprintf(stderr, "Invalid parameter passed to sync.\n"); 
						exit(1); 
					}
				}
				else { 
					fprintf(stderr, "No value for sync passed. Default value used.\n"); 
				} 
				break; 

		}
		opt = getopt_long(argc, argv, "a", long_options, &option_index); 
	}
	pthread_t *threads = malloc(sizeof(pthread_t)*numThreads);  
	if(threads == NULL){ 
		fprintf(stderr, "Error allocating memory.\n"); 
		exit(1); 
	}
	int i; 
	int ret = 1; 
	//printf("The threads are: %d\n", numThreads); 
	for(i = 0; i<numThreads; i++){
		ret = pthread_create(&threads[i], NULL, threadAction, (void *) &COUNTER); 
		if(ret!=0){ 
			fprintf(stderr, "Issue creating thread\n"); 
			exit(1); 
		}

	}
	
	for(i = 0; i < numThreads; i++) { 
		ret = pthread_join(threads[i], NULL); 
		if(ret != 0){
			fprintf(stderr, "Issue joining threads"); 
			exit(1); 
		}
	}
}

void *threadAction(void *pointer) { 
	int j; 
	switch(syncMethod) 
	{
		case 1: 
			for(j=0; j< iterations; j++) { 
				pthread_mutex_lock(&mutexAdd); 
				add(pointer, 1); 
				add(pointer, -1); 
				pthread_mutex_unlock(&mutexAdd); 
			}
		break; 
		
		case 2: 
			for(j=0; j < iterations; j++) { 
				while(__sync_lock_test_and_set(&test_lock, 1)); 
				add(pointer, 1); 
				add(pointer, -1); 
				__sync_lock_release(&test_lock); 
			} 
			break; 
			
		case 3: 
			for(j = 0; j < iterations; j++) { 
				add_synC(pointer, 1); 
			}
			for(j=0; j < iterations; j++) { 
				add_synC(pointer, -1); 
			}
			break; 
		case 0: 
			for(j=0; j < iterations; j++) { 
				add(pointer, 1); 
				add(pointer, -1); 
			}
		break; 
	}
}

void printInfo(struct timespec begin, struct timespec end){ 
	time_t secs = (end.tv_sec - begin.tv_sec) * 1000000000; 
	long int nsecs; 
	if( end.tv_nsec > begin.tv_nsec)
		nsecs = end.tv_nsec - begin.tv_nsec; 
	else
		nsecs = begin.tv_nsec- end.tv_nsec; 
	long int totalTime = (long int) secs + nsecs; 
	
	int operations = numThreads * iterations * 2; 
	
	printf("%d threads x %d iterations x (add + subtract) = %d operations\n", numThreads, iterations, operations); 
	if(COUNTER == 0)
		printf("Everything worked!\n"); 
	else
		printf("Error: counter = %lld\n", COUNTER); 
	printf("Elapsed time: %ld ns\n", totalTime); 
	int perOp = totalTime / operations; 
	printf("per operation: %d ns\n", perOp); 
}

void add(long long *pointer, long long value)
{ 
	long long sum = *pointer + value; 
	if(opt_yield)
		pthread_yield(); 
	*pointer = sum; 
}

void add_synC(long long *pointer, long long value) { 
	long long original; 
	long long sum; 
	do{ 
		original = *pointer; 
		sum = original + value; 
	}while(__sync_val_compare_and_swap(pointer, original, sum) != original); 
}