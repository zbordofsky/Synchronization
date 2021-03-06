#define _GNU_SOURCE
#include "SortedList.h"
#include <pthread.h>
#include <getopt.h> 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#define BILLION  1000000000;


SortedList_t *dummy;
int opt_yield = 0;


void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
	
	SortedList_t *head = list;
	SortedList_t *curr = list;
	SortedList_t* oneBefore = list;
	if(head->next == head)
	{
		head->next = element;
		head->prev = element;
		element->next = head;
		element->prev = head;
		return;
	}
/*	if(strcmp(element->key, curr->next->key) < 0)
	{
		head->next = element;
		head->prev = curr->next;
		curr->prev = element;
		element->next = curr;
		element->prev = head;
	}*/
	curr = curr->next;		// i start at first term
	if(strcmp(element->key, curr->key) <= 0)	//special case add to beginning
	{
		curr->prev = element;
		element->next = curr;
		element->prev = head;
		head->next = element;
		return;
	}
	while(curr->next != head) //|| strcmp(curr->key, element->key) < 0 )
	{
		if(strcmp(curr->key, element->key) <= 0)
		{
			if(strcmp(element->key, curr->next->key) <= 0)
			{
				break;
			}
		}
	
		oneBefore = curr;
		curr = curr->next;
/*		if(oneBefore == head)
		{
			if(strcmp(element->key, curr->key) < 0)
			{
				head->next = element;
				
				head->prev = curr->next;
				curr->prev = element;
				element->next = curr;
				element->prev = head;			
				return;
			}
		}*/
	}
	if(curr->next == head)
	{
		head->prev = element;
		element->next = head;
		element->prev = curr;
		curr->next = element;
	}
	else
	{
	SortedList_t *temp;
	
	temp = curr->next;
	printf("temp is: %s\n", temp->key);
	curr->next = element;
	curr->prev = oneBefore;
	temp->prev = element;
//	printf("curr is: %s\n", curr->key);
//	printf("curr->next is: %s\n", temp->key);
//	printf("element is: %s\n", element->key);
	element->next = temp;
	element->prev = curr;
	}
//	}
/*	else
	{
		SortedList_t *temp;
		temp = curr->next;
		curr->next = element;
		element->next = temp;
		element->prev = curr;
	}*/
/*	while(list->next != head)	// find last element
	{
		oneBefore = list;
		SortedList_t* temp = list->next;
		if(opt_yield & INSERT_YIELD)
		{
			pthread_yield();
		}
		list = temp;
	}
	list->next = element;
	if(opt_yield & INSERT_YIELD)
	{
		pthread_yield();
	}
	oneBefore->next = list;
	element->prev = list;
	element->next = head;
	head->prev = element;*/
}


int SortedList_delete( SortedListElement_t *element)
{
	SortedList_t* temp = dummy;
	if(element->next != NULL && element->prev != NULL && element->next->prev != NULL && element->prev->next != NULL)
	{	
		if(element->next->prev == element && element->prev->next == element)
		{
			
			temp->next->prev = temp->prev;
			if (opt_yield & DELETE_YIELD)
			{
				pthread_yield();
			}
			temp->prev->next = temp->next;
			free(temp);
		}
		else
		{
			return 1;
		}
	}
	else 
		return 1;
	return 0;
}



SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
	SortedList_t *head = list;
	while(strcmp(list->key, key) != 0 || list->next == head)
	{
		SortedList_t* temp = list->next;
		if (opt_yield & SEARCH_YIELD)
		{
			pthread_yield();
		}
		list = temp;
	}
	if(list->key == NULL)
	{
		return NULL;
	}
	return list;
	
}


int SortedList_length(SortedList_t *list)
{
	SortedList_t *head = list;
	SortedList_t *curr = list->next;
	printf("curr is: %s\n", curr->key);
	SortedList_t* oneBefore = list;
	if(head->next == list)
	{
		return 0;
	}
	int count = 0;
//	SortedList_t *head = list;
//	list = list->next;
	while(curr != head)
	{
//		if (opt_yield & SEARCH_YIELD)
//		{
//			pthread_yield();
//		}
		if(curr->next->prev != curr)//|| list->prev->next != list)
		{
			printf("curr is: %s\n", curr->key);
			printf("curr blah is: %s\n", curr->next->prev->key);
			return -1;
		}
		if(curr->prev->next != curr)
		{
			return -2;
		}
		curr = curr->next;
		printf("fucking niggers\n");
		count++;
	}
	return count;
	
}


int main(int argc, char *argv[]) { 
	//timer function 
//	struct timespec beginning, end; 
//	clock_gettime(CLOCK_REALTIME, &beginning); 
//	testerFunc(argc, argv); 
//	clock_gettime(CLOCK_REALTIME, &end); 
//	printInfo(beginning, end); 
//	pthread_mutex_destroy(&mutexAdd); 
SortedList_t *dummy;
dummy = (SortedList_t *)malloc(sizeof(SortedList_t));
dummy->prev = dummy;
dummy->next = dummy;

SortedList_t *list;
int size = 4;
list = (SortedList_t *)malloc(sizeof(SortedList_t) * size);

char *string1;
string1 = (char *)malloc(sizeof(char) * 5);
string1 = "apple";
char *string2;
string2 = (char *)malloc(sizeof(char) * 5);
string2= "aaaaa";
char *string3;
string3 = (char *)malloc(sizeof(char) * 5);
string3= "aaaaa";

char *string4;
string4 = (char *)malloc(sizeof(char) * 5);
string4= "abcde";

list[0].key = string1;
list[0].prev = NULL;
list[0].next = NULL;
list[1].key = string2; 
list[1].prev = NULL;
list[1].next = NULL;
list[2].key = string3;
list[2].prev = NULL;
list[2].next = NULL;
list[3].key = string4;
list[3].prev = NULL;
list[3].next = NULL;

SortedList_insert(dummy, &list[0]);
SortedList_insert(dummy, &list[1]);
SortedList_insert(dummy, &list[2]);
SortedList_insert(dummy, &list[3]);

int index;
SortedList_t *temp = dummy;
printf("temp key is: %s\n", temp->key);
printf("temp prev key is: %s\n", temp->prev->key);
printf("temp next key is: %s\n\n", temp->next->key);

temp = temp->next;

printf("temp key is: %s\n", temp->key);
printf("temp prev key is: %s\n", temp->prev->key);
printf("temp next key is: %s\n\n", temp->next->key);

temp = temp->next;
printf("temp key is: %s\n", temp->key);
printf("temp prev key is: %s\n", temp->prev->key);
//printf("pobelter");
printf("temp next key is: %s\n\n", temp->next->key);


temp = temp->next;

printf("temp key is: %s\n", temp->key);
printf("temp prev key is: %s\n", temp->prev->key);
printf("temp next key is: %s\n\n", temp->next->key);

temp = temp->next;

printf("temp key is: %s\n", temp->key);
printf("temp prev key is: %s\n", temp->prev->key);
printf("temp next key is: %s\n\n", temp->next->key);
//printf("pobelter");
/*for(index = 0; index < size; index++)
{
//	printf("pobelter");
//	printf("temp key is: %s\n", temp->key);
//	printf("temp prev key is: %s\n", temp->prev->key);
//	temp = temp->next;
}*/

printf("pobelter\n");
int shit = SortedList_length(dummy);
printf("the length is: %d\n", shit);
return 0;
	



}