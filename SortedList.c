#define _GNU_SOURCE
#include "SortedList.h"
#include <pthread.h>
#include <getopt.h> 
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#define BILLION  1000000000;


//int opt_yield = 0;


void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{	/* 
	if(list->next == NULL || list->next == list){ //nothing has been made
		list->next= element; 
		list->prev = element; 
		element->prev = list; 
		element->next = list; 
		return; 
	}
	
	else {
		SortedListElement_t *temp = list->next;  
		while(temp->next != list && temp->next != NULL){ 
			if(strcmp(temp->key, element->key) >=0){
				SortedListElement_t *previous = temp->prev; 
				previous->next = element; 
				element->prev = previous; 
				element->next = temp; 
				temp->prev = element; 
				return; 
			}
			else{
				temp = temp->next; 
			}
		}
		if(temp->next == list){
			temp->next = element; 
			element->prev = temp; 
			element->next = list; 
			list->prev = element; 
		}
	}*/
	
	
	//new 
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
/////
}


int SortedList_delete( SortedListElement_t *element)
{

	if(element->next != NULL && element->prev != NULL && element->next->prev != NULL && element->prev->next != NULL)
	{	
		if(element->next->prev == element && element->prev->next == element)
		{
			element->next->prev = element->prev;
			if (opt_yield & DELETE_YIELD)
			{
				pthread_yield();
			}
			element->prev->next = element->next;
			element->next = NULL;
			element->prev = NULL;
			return 0;
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
	SortedList_t *curr = list->next;
	while(strcmp(curr->key, key) != 0 /*curr->key != key*/ && curr->key != NULL)
	{
		SortedList_t* temp = curr->next;
		if (opt_yield & SEARCH_YIELD)
		{
			pthread_yield();
		}
		curr = temp;
	}
	if(strcmp(curr->key, key) == 0)
	{
		return curr;
	}

		return NULL;
}
	



int SortedList_length(SortedList_t *list)
{
	if(list->next == list)
	{
		return 0;
	}
	int count = 0;
	SortedList_t *head = list;
	list = list->next;
	while(list != head)
	{
		if (opt_yield & SEARCH_YIELD)
		{
			pthread_yield();
		}
		if(list->next->prev != list)//|| list->prev->next != list)
		{
			return -1;
		}
		if(list->prev->next != list)
		{
			return -2;
		}
		list = list->next;
		count++;
	}
	return count;
	
}
