#include <pthread.h>

long long *COUNTER = 0; 
int main(int argc, *argv[]) { 
	//timer function 
	testerFunc(argc, *argv[]); 
	//timer function 
}


void testerFunc (int argc, *argv[]) 
{ 
	static struct option long_options[] = 
	{
		{"iterations", optional_argument, 0, 'i'}, 
		{"threads", optional_argument, 0, 't'}, 
		{0, 0, 0, 0}
	}
	int opt; 
	int iterations = 1; 
	int numThreads = 1; 
	opt = getopt_long(argc, argv, "a", long_options, &option_index); 
	while(opt != -1) 
	{ 
		switch(opt) 
		{
			case 'i':
			if(optarg != NULL)
				iterations = optarg; 
			break; 

			case 't':
			if(optarg != NULL)
				numThreads = optarg; 
			break; 

		}
		opt = getopt_long(argc, argv, "a", long_options, &option_index); 
	}
	pthread_t threads[numThreads]; // = malloc(sizeof(pthread_t)*numThreads*2);  
	int i; 
	int ret; 
	for(i = 0; i<numThreads; i++){
		ret = pthread_create(&threads[i], NULL, plusOne, COUNTER); 
		if(ret!=0){ 
			fprintf(stderr, "Issue creating thread"); 
		}
		ret = pthread_create(&threads[i+numThreads], NULL, minusOne, COUNTER); 
		if(ret != 0){
			fprintf(stderr, "Issue creating thread"); 
		}
	}
}

void *plusOne(void *pointer) { 
	add(pointer, 1); 
}

void *minusOne(void *pointer) { 
	add(pointer, -1); 
}


void add(long long *pointer, long long value)
{ 
	long long sum = *pointer + value; 
	*pointer = sum; 
}