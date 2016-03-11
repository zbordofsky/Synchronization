#include <pthread.h> 
#include <stdio.h> 
#include <getopt.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h> 
//include list.h 


int numThreads = 1; 
int iteratinos = 1; 
int numLists = 1; 
int opt_yield = 0; 
struct timespec beginning; 

void  (int argc, char *argv[]) ; 
void *threadAction(); 

int main(int argc, char *argv[]) { 
	struct timespec end;
	testerFunc(argc, argv); 
	clock_gettime(CLOCK_REALTIME, &end);
	
	//print 
}



void testerFunc (int argc, char *argv[]) { 
	time_t t; 
	srand((unsigned) time(&t)); 
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
	SortedListElement_t *elements = malloc(sizeof(SortedListElement_t)*numThreads*iterations); 
	int j; 
	for(j=0; j < (numThreads*iterations); j++){ 
		SortedListElement_t temp; 
		temp.key = rand(); 
		elements[i] = temp; 
	}
	
	//time function-make structs gobals 
	clock_gettime(CLOCK_REALTIME, &beginning);
	pthread_t *threads = malloc(sizeof(pthread_t)*numThreads); 
	int i; 
	int ret; 
	for(i = 0; i < numThreads; i++) {
		ret = pthread_create(&threads[i], NULL, threadAction, &threads[i*iterations]); 
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

void *threadAction(SortedListElement_t *elements){
	//do the thread stuff here
	SortedList_t **list malloc(sizeof(SortedList_t*)*numLists);

	int i; 
	int j; 
	int mod; 
	int nums[numLists]; 
	for(i=0; i < numLists; i++)
		nums[i] = 0; 

	for(i=0; i < iterations; i++){
		mod = modular(elements[i].key); 
		SortedList_insert(list[mod], elements[i]); 
		nums[mod]++; 
	}

	int length; 
	for(i=0; i < numLists; i++)
		length = SortedList_length(list[i]); 

	SortedListElement_t *found = malloc(sizeof(SortedList_Element_t)*iterations); 
	for(i=0; i<numLists; i++){
		for(j=0; j < nums[i]; j++){
			found[i*numLists + j] = SortedList_lookup(list[i], elements[i].key); 
			if(found[i*numLists +j] != NULL)
				break; 
		}
		
	}

	for(i=0; i<iterations; i++){
		SortedList_delete(found[i]); 
	}

}

void printInfo(struct timespec begin, struct timespec end) {
	time_t sec = (end.tv_sec - begin.tv_sec) * 1000000000; 
	long int nsecs; 
	if( end.tv_nsec > begin.tv_nsec)
		nsecs = end.tv_nsec - begin.tv_nsec; 
	else
		nsecs = begin.tv_nsec- end.tv_nsec; 
	long int totalTime = (long int) secs + nsecs; 

	int operations; 

	printf("%d threads x %d iterations x (ins + lookup/del) x (%d/2 avg len) = %d operations\n", numThreads, iterations, iterations, operations); 
	//check list, not sure about that yet 

	printf("Elapsed time: %d ns\n", totalTime); 
	int perOp = totatTime / operations; 
	printf("per op: %d ns\n", perOp); 
}

int modular(char *key){
	int mod = key[0] % numLists; 
	return mod; 
}