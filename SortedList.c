#include "SortedList.h"

void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
	
	SortedList_t *head = list;
	while(list->next != head)	// find last element
	{
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
	element->prev = list;
	element->next = head;
}


int SortedList_delete( SortedListElement_t *element)
{
	if(element->next != NULL && element->prev != NULL && element->next->prev != NULL && element->prev->next != NULL)
	{	
		if(element->next->prev == element && element->prev->next == element)
		{
			
			list->next->prev = list->prev;
			if (opt_yield & DELETE_YIELD)
			{
				pthread_yield();
			}
			list->prev->next = list->next;
			free list;
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
	if(list->next == list)
	{
		return 0;
	}
	int count = 1;
	SortedList_t *head = list;
	while(list->next != head)
	{
		if (opt_yield & SEARCH_YIELD)
		{
			pthread_yield();
		}
		if(list->next->prev != list || list->prev->next != list)
		{
			return -1;
		}
		count++;
	}
	return count;
	
}