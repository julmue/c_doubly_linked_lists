#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "doubly_linked_list.h"

#ifndef STRLEN
#define STRLEN 1000
#endif

#ifndef MYENQUEUE
#define MYENQUEUE

typedef struct flags { 
	int mode_ia;
	int mode_vb;
	/* types for testvalues according to the cli argv. default = string */
	int valtype;
} FLAGS;


typedef struct streams {
	FILE *instream;
	FILE *outstream;
	FILE *errstream;
} STREAMS;


typedef struct testdata {
	void *name;
	void *value;
	} TESTDATA;


// myqueue function
int myqueue(int argc, char **argv);

// myqueue core functions
TESTDATA *myqueue_testdata_create(int stringlength);

int myqueue_testdata_destroy(TESTDATA *dataptr, int stringlength);

DLLIST *myqueue_enqueue(int stringlength);

int myqueue_dequeue(DLLIST *listhead, int stringlength);

int myqueue_total_dequeue(DLLIST *listhead, int stringlength);

// myqueue data aquisition 
int myqueue_testvalues_get(DLLIST *listhead, TESTDATA *dataptr,  int stringlength);

int myqueue_getline(FILE *stream, char *string, int stringlength);

int myqueue_rawdata_convert(int type, char *rawdataptr, void *targetdataptr, int stringlength);

// functions to read and process data from the input stream
int myqueue_rawdata_get(int elements_in_queue, int value_is_name, char *testdata_raw, int stringlength);

int myqueue_rawdata_check(int type, char *rawdataptr, int stringlength);

// string constructor and destructor functions
char * myqueue_string_create(int stringlength);

int myqueue_string_destroy(char *string, int stringlength);

// integer constructor and destructor function
int * myqueue_int_create(void);

int myqueue_int_destroy(int *intptr);

// float constructor and destructor function
float * myqueue_float_create(void);

int myqueue_float_destroy(float *floatptr);

// error handling & control assistant functions
int myqueue_flags_vaild();

#endif
