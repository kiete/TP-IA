#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

/* Item Functions */

int cmpBoard(char *a, char *b, char size)
{
	int i;

	for (i = 0; i < size; i++)
	{
		printf("%c , %c \n" , a[i] , b[i] );
		if (a[i] != b[i]) return 0;
	}
	return 1;
}

Item *nodeAlloc()
{
  Item *node;

  node = (Item *) malloc( sizeof(Item) );
  assert(node);

  node->parent = NULL;
  node->prev = NULL;
  node->next = NULL;
  node->f = node->g = node->h = (double)0.0;
  return node;
}

void freeItem( Item *node )
{
  if (node && node->board) free(node->board);
	if (node) free(node);
}


void initList( list_t *list_p )
{
  //if (list_p == NULL) list_p = malloc(sizeof(list_t));
	assert(list_p);

  list_p->numElements = 0;
  list_p->first = NULL;
  list_p->last = NULL;
}

int listCount( list_t *list )
{
	return list->numElements;
}


// return an item with corresponding board , or null
Item* onList( list_t *list, char *board)
{
	int i;

	Item* premier = list->first ;
	printf("\n\n\n%d\n\n\n" , premier->size);
	while (premier != NULL  && !cmpBoard(premier->board, board , premier->size))
	{
		printf("%s | %s | %d\n", premier->board, board, cmpBoard(premier->board, board ,premier->size ));
		premier = premier->next ;
	}
	
	return premier;
}

// return and remove first item
Item *popFirst( list_t *list ) //
{
	Item *Temp = list->first;
	list->first=list->first->next ;
	list->first->prev = NULL ;
	list->numElements -- ;

	return Temp;
}

// return and remove last item
Item *popLast( list_t *list ) //
{
	Item *temp = list->last ;
	list->last = list->last->prev ;
	list->last->next = NULL ;
	list->numElements -- ;

	return temp;
}

// remove a node from list
void delList( list_t *list, Item *node) {
	Item *tempPrev = node->prev ;
	Item *tempNext = node->next ;
	if (tempPrev == NULL){
		// On est au premier element
		list->first = tempNext ;
		list->first->prev = NULL ;
	}else{
		tempPrev->next = tempNext;
	}
	if (tempNext == NULL){
		// On est au dernier element
		list->last = tempPrev ;
		list->last->next = NULL ;
	}else{
		tempNext->prev = tempPrev;
	}

	list->numElements -- ;
	freeItem(node);
	return;
}

// return and remove best item with minimal f value
Item *popBest( list_t *list ) // and remove the best board from the list.
{
	Item *minimum , *challenger ;

	if (list->numElements == 0) return NULL ;

	minimum , challenger = list->first ;
	do{
		if (minimum->f > challenger->f) minimum = challenger ;
		challenger = challenger->next ;
	}while (challenger != NULL) ;

	Item *tempPrev = minimum->prev;
	Item *tempNext = minimum->next;

	if (tempPrev == NULL)
	{
		// On est au premier element
		list->first = tempNext;
		list->first->prev = NULL;
	}
	else
	{
		tempPrev->next = tempNext;
	}
	if (tempNext == NULL)
	{
		// On est au dernier element
		list->last = tempPrev;
		list->last->next = NULL;
	}
	else
	{
		tempNext->prev = tempPrev;
	}

	list->numElements--;

	return minimum ;
}

 // add item in top
void addFirst( list_t *list, Item *node ) // add in head
{
	if (list->numElements == 0)
	{
		list->last = node;
	}else{
		list->first->prev = node ;
	}
	node->next = list->first ;
	node->prev = NULL ;
	list->first = node ;

	list->numElements ++ ;
	return ;
}

 // add item in queue
void addLast( list_t *list, Item *node ) // add in tail
{
	if (list->numElements==0){
		list->first = node ;
	}else{
		list->last->next = node ;
	}
	node->prev = list->last;
	node->next = NULL;
	list->last = node;

	list->numElements ++ ;
	return ;
}

void cleanupList( list_t *list )
{
	Item *temp , *temp2 ;

	temp = list->first ;
	while (temp != NULL)
	{
		temp2 = temp->next ;
		free(temp) ;
		temp = temp2 ;
	}
	list->first = NULL ; 
	list->last = NULL ;
	list->numElements = 0 ;
	return ;
}

void printList( list_t list ) {
	Item *item = list.first;
  while (item) {
    printf("%.2f [%s] - ", item->f, item->board);
    item = item->next;
  }
  printf(" (nb_items: %d)\n", list.numElements);
}

