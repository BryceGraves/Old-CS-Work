#include "linkedList.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

/* TO COMPILE:
Linux: gcc -shared -Wl,-soname,linkedList -o linkedList.so -fPIC linkedList.c
Mac: gcc -shared -Wl,-install_name,linkedList.so -o linkedList.so -fPIC linkedList.c
*/

/* Double Link*/
struct DLink {
	TYPE value;
	struct DLink * next;
	struct DLink * prev;
};

/* Double Linked List with Head and Tail Sentinels  */

struct linkedList {
	int size;
	struct DLink *firstLink;
	struct DLink *lastLink;
};

/*
initList
param lst the linkedList
pre: lst is not null
post: lst size is 0
*/

void _initList(struct linkedList *lst) {
	/* FIXME: you must write this */
	assert(lst != NULL);
	struct DLink *front = (struct DLink *)malloc(sizeof(struct DLink));
	struct DLink *back = (struct DLink *)malloc(sizeof(struct DLink));
	front->value = 0;
	front->next = back;
	front->prev = NULL;

	back->value = 0;
	back->next = NULL;
	back->prev = front;

	lst->size = 0;
	lst->firstLink = front;
	lst->lastLink = back;

}

/*
createList
param: none
pre: none
post: firstLink and lastLink reference sentinels
*/

struct linkedList *createLinkedList()
{
	struct linkedList *newList = malloc(sizeof(struct linkedList));
	_initList(newList);
	return(newList);
}

/*
_addLinkBeforeBefore
param: lst the linkedList
param: l the  link to add before
param: v the value to add
pre: lst is not null
pre: l is not null
post: lst is not empty
*/

/* Adds Before the provided link, l */

void _addLinkBefore(struct linkedList *lst, struct DLink *l, TYPE v)
{
	/* FIXME: you must write this */
	assert(lst != NULL);
	assert(l != NULL);
	struct DLink *newLink = (struct DLink *)(malloc(sizeof(struct DLink)));
	newLink->value = v;
	newLink->prev = l->prev;
	newLink->next = l;
	l->prev->next = newLink;
	l->prev = newLink;
	lst->size++;

}

/*
_removeLink
param: lst the linkedList
param: l the linke to be removed
pre: lst is not null
pre: l is not null
post: lst size is reduced by 1
*/
void _removeLink(struct linkedList *lst, struct DLink *l)
{

	/* FIXME: you must write this */
	assert(lst != NULL);
	assert(l != NULL);
	l->prev->next = l->next;
	l->next->prev = l->prev;
	free(l);
	lst->size--;

}

/*
isEmptyList
param: lst the linkedList
pre: lst is not null
post: none
*/
int isEmptyList(struct linkedList *lst) {
	/* FIXME: you must write this */
	assert(lst != NULL);
	/*temporary return value...you may need to change this */
	return(lst->size == 0);
}

/* De-allocate all links of the list
param: 	lst		pointer to the linked list
pre:	none
post:	All links (including the two sentinels) are de-allocated
*/
void freeLinkedList(struct linkedList *lst)
{
	while (!isEmptyList(lst)) {
		/* remove the link right after the first sentinel */
		_removeLink(lst, lst->firstLink->next);
	}
	/* remove the first and last sentinels */
	free(lst->firstLink);
	free(lst->lastLink);
}

/* 	Deallocate all the links and the linked list itself.
param: 	v		pointer to the dynamic array
pre:	v is not null
post:	the memory used by v->data is freed
*/
void deleteLinkedList(struct linkedList *lst)
{
	assert(lst != 0);
	freeLinkedList(lst);
	free(lst);
}


/* Function to print list
Pre: lst is not null
*/
void _printList(struct linkedList* lst)
{
	/* FIXME: you must write this */
	assert(lst != NULL);
	struct DLink *lLink = lst->firstLink->next;

	while(lLink != lst->lastLink){
		printf("%d\n", lLink->value);
		lLink = lLink->next;
}
}

/* ************************************************************************
Deque Interface Functions
************************************************************************ */

/*
addFrontList
param: lst the linkedList
param: e the element to be added
pre: lst is not null
post: lst is not empty, increased size by 1
*/
void addFrontList(struct linkedList *lst, TYPE e)
{

	/* FIXME: you must write this */
	assert(lst != NULL);
	_addLinkBefore(lst, lst->firstLink->next, e);
	lst += 1;
}

/*
addBackList
param: lst the linkedList
param: e the element to be added
pre: lst is not null
post: lst is not empty, increased size by 1
*/
void addBackList(struct linkedList *lst, TYPE e) {

	/* FIXME: you must write this */
	assert(lst != NULL);
	_addLinkBefore(lst, lst->lastLink->prev, e);
	lst += 1;
}

/*
frontList
param: lst the linkedList
pre: lst is not null
pre: lst is not empty
post: none
*/
TYPE frontList(struct linkedList *lst) {
	/* FIXME: you must write this */
	assert(lst != NULL);
	assert(!isEmptyList(lst));
	/*temporary return value...you may need to change this */
	return(lst->firstLink->next->value);
}

/*
backList
param: lst the linkedList
pre: lst is not null
pre: lst is not empty
post: lst is not empty
*/
TYPE backList(struct linkedList *lst)
{
	/* FIXME: you must write this */
	assert(lst != NULL);
	assert(!isEmptyList(lst));
	/*temporary return value...you may need to change this */
	return(lst->lastLink->prev->value);
}



/*
removeFrontList
param: lst the linkedList
pre:lst is not null
pre: lst is not empty
post: size is reduced by 1
*/
void removeFrontList(struct linkedList *lst) {
	/* FIXME: you must write this */
	assert(lst != NULL);
	assert(!isEmptyList(lst));
	_removeLink(lst, lst->firstLink->next);

}

/*
removeBackList
param: lst the linkedList
pre: lst is not null
pre:lst is not empty
post: size reduced by 1
*/
void removeBackList(struct linkedList *lst)
{
	/* FIXME: you must write this */
	assert(lst != NULL);
	assert(!isEmptyList(lst));
	_removeLink(lst, lst->lastLink->prev);

}
