#include "stdlib.h"
#include "stdio.h"

#ifndef DLLISTLIB
#define DLLISTLIB
typedef struct dllist_head {
	int 			elements;
	struct dllist_node 	*first;		// node added latest to list
	struct dllist_node 	*tail;		// node longest in list
	} DLLIST_HEAD;


typedef struct dllist_node {
	struct dllist_node 	*prev;
	void 			*data;
	struct dllist_node 	*next;
	} DLLIST_NODE;

typedef struct dllist_head DLLIST;



DLLIST_HEAD *dllist_head_create(void);

int dllist_head_destroy(DLLIST_HEAD *headptr);

DLLIST_NODE *dllist_node_create(void);

int dllist_node_destroy(DLLIST_NODE *nodeptr);

DLLIST *dllist_create(void);

int dllist_add_data(DLLIST *listptr, void *dataptr);

void *dllist_delete_tail(DLLIST *listptr);

int dllist_elements(DLLIST *listptr);

#endif
