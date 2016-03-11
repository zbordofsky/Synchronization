#include <pthread.h> 
#include <stdio.h> 
#include <getopt.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
//include list.h 


int numThreads = 1; 
int iteratinos = 1; 

void  (int argc, char *argv[]) ; 
void *threadAction(); 

int main(int argc, char *argv[]) { 
	
	testerFunc(argc, argv); 
	//time function
	//print 
}



void testerFunc (int argc, char *argv[]) { 
	
	static struct option long_options[] = 
	{
		{"iterations", optional_argument, 0, 'i'}, 
		{"threads", optional_argument, 0, 't'}, 
		{"yield", optional_argument, 0, 'y'},
		{"sync", optional_argument, 0, 's'}, 
		{0, 0, 0, 0}
	}; 
	int opt; 
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
		}
	}
	//create the list 
	
	//time function-make structs gobals 
	pthread_t *threads = malloc(sizeof(pthread_t)*numThreads); 
	int i; 
	int ret; 
	for(i = 0; i < numThreads; i++) {
		ret = pthread_create(&threads[i], NULL, threadAction, ???); 
		if(ret!= 0) { 
			fprintf(stderr, "Error creating threads\n"); 
			exit(1); 
		}
	}

	for(i=0; i<numThreads, i++) { 
		ret = pthread_join(threads[i], NULL); 
		if(ret!= 0){
			fprintf(stderr, "Error joining threads.\n"); 
			exit(1); 
		}
	}
}