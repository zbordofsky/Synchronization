#include <pthread.h>
#include <getopt.h> 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void testerFunc (int argc, char *argv[]); 
void *threadAction(void *pointer); 
//void *minusOne(void *pointer); 
void add(long long *pointer, long long value); 

long long *COUNTER = 0; 

int main(int argc, char *argv[]) { 
	//timer function 
	testerFunc(argc, argv); 
	//timer function 
}


void testerFunc (int argc, char *argv[]) 
{ 
	static struct option long_options[] = 
	{
		{"iterations", optional_argument, 0, 'i'}, 
		{"threads", optional_argument, 0, 't'}, 
		{0, 0, 0, 0}
	}; 
	int opt; 
	int iterations = 1; 
	int numThreads = 1; 
	int option_index = 0; 
	opt = getopt_long(argc, argv, "a", long_options, &option_index); 
	while(opt != -1) 
	{ 
		switch(opt) 
		{
			case 'i':
			if(optarg != NULL)
				iterations = atoi(optarg); 
			break; 

			case 't':
			if(optarg != NULL)
				numThreads = atoi(optarg); 
			break; 

		}
		opt = getopt_long(argc, argv, "a", long_options, &option_index); 
	}
	pthread_t *threads = malloc(sizeof(pthread_t)*numThreads);  
	int i; 
	int ret = 1; 
	printf("The threads are: %d\n", numThreads); 
	for(i = 0; i<numThreads; i++){
		ret = pthread_create(&threads[i], NULL, threadAction, (void *) &COUNTER); 
		if(ret!=0){ 
			fprintf(stderr, "Issue creating thread\n"); 
		}

	}
	
	for(i = 0; i < numThreads; i++) { 
		ret = pthread_join(threads[i], NULL); 
		if(ret != 0){
			fprintf(stderr, "Isse joining threads"); 
		}
	}
	//long long count = COUNTER; 
	//printf("The count is: %d\n", count); 
	if( COUNTER == 0){
		printf("hey it works!\n"); 
	}
	else{ 
		printf("the counter is: %d\n", COUNTER); 
	}
}

void *threadAction(void *pointer) { 
	add(pointer, 1); 
	add(pointer, -1); 
}
/*
void *minusOne(void *pointer) { 
	add(pointer, -1); 
}*/


void add(long long *pointer, long long value)
{ 
	long long sum = *pointer + value; 
	*pointer = sum; 
}