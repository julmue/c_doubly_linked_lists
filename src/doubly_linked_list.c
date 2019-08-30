#include "doubly_linked_list.h"

DLLIST_HEAD* dllist_head_create(void)
{
	DLLIST_HEAD * headptr = NULL; 

	headptr = calloc(1, sizeof(DLLIST_HEAD));

	if (headptr != NULL)
		return headptr;

	fprintf(stderr, "unable to create list head\n");
	return NULL;
}


int dllist_head_destroy(DLLIST_HEAD *headptr)
{
	if (headptr != NULL && headptr->elements == 0
		&& headptr->first == NULL && headptr->tail == NULL) {
		free(headptr);
		return EXIT_SUCCESS;
	}

	fprintf(stderr, "unable to destroy list head\n");
	return EXIT_FAILURE;
}


DLLIST_NODE* dllist_node_create(void)
{
	DLLIST_NODE *nodeptr = NULL;

	nodeptr = calloc(1, sizeof(DLLIST_NODE));

	if (nodeptr != NULL)
		return nodeptr;

	fprintf(stderr, "unable to create list node\n");
	return NULL;
}


int dllist_node_destroy(DLLIST_NODE *nodeptr)
{
	if (nodeptr != NULL && nodeptr->prev == NULL
			&& nodeptr->data == NULL && nodeptr->next == NULL) {
		free(nodeptr);
		return EXIT_SUCCESS;
	}

	fprintf(stderr, "unable to destroy list node\n");
	return EXIT_FAILURE;
}


DLLIST *dllist_create(void)
{
	return dllist_head_create();
}


int dllist_add_data(DLLIST *listptr, void *dataptr)
{
	DLLIST_NODE *nodeptr = NULL;

	if (listptr->first) {
		nodeptr = dllist_node_create();
		nodeptr->next = listptr->first;
		nodeptr->next->prev = nodeptr;
		nodeptr->data = dataptr;
		listptr->first = nodeptr;
		listptr->elements++;
		return EXIT_SUCCESS;
	} else {
		listptr->first = dllist_node_create();
		listptr->tail = listptr->first;
		listptr->elements++;
		listptr->first->data = dataptr;
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}


int dllist_elements(DLLIST *listptr)
{
	if (listptr != NULL)
		return listptr->elements;

	return -1;
}

void *dllist_delete_tail(DLLIST *listptr)
{
	void *resultptr = NULL;
	
	if (listptr != NULL && dllist_elements(listptr) > 0
				&& listptr->tail->prev != NULL) {
		resultptr = listptr->tail->data;
		listptr->tail = listptr->tail->prev;
		listptr->tail->next->data = NULL;
		listptr->tail->next->prev = NULL;
		if (dllist_node_destroy(listptr->tail->next) == EXIT_FAILURE)
			goto error;
		listptr->tail->next = NULL;
		listptr->elements--;
		return	resultptr;
	} else if (listptr != NULL && dllist_elements(listptr) > 0
				&& listptr->tail->prev == NULL) {
		resultptr = listptr->tail->data;
		listptr->tail->data = NULL;
		if (dllist_node_destroy(listptr->tail) == EXIT_FAILURE)
			goto error;
		listptr->tail = NULL;
		listptr->first = NULL;
		listptr->elements--;
		return	resultptr;
	}

	error:
		return NULL;
}
