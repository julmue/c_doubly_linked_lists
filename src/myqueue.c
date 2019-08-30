#include "myqueue.h"

FLAGS qflags;

STREAMS qstreams;

// every function has access to the flags and the streams

// Enumeration to simplify recognition of the selected data type in flags 
enum{type_string = 1, type_int, type_float};


int myqueue(int argc, char *argv[])
{	
	// function declaration for flaggetter
	int myqueue_streams_set(void);
	int myqueue_flags_get(int argc, char **argv);

	// default setting for flags
	qflags.mode_ia = true;
	qflags.mode_vb = false;
	qflags.valtype = type_string;

	// default setting for streams
	qstreams.instream = stdin;
	qstreams.outstream = stdout;
	qstreams.errstream = stderr;

	if (myqueue_flags_get(argc, argv) == EXIT_FAILURE)
		exit(EXIT_FAILURE);

	if (qflags.mode_ia == true)
		fprintf(stdout, "\n ================ MYQUEUE ================ \n\n");

	DLLIST * queue;
	queue = myqueue_enqueue(STRLEN);
	myqueue_total_dequeue(queue, STRLEN);

	dllist_head_destroy(queue);

	// exit(EXIT_SUCCESS);
	return 0;
}
// functions to map the command-line Argumentes to the global FLAGS object
int myqueue_flags_get(int argc, char **argv)
{
	int value_flags_count = 0;
	char c;

	while (--argc > 0 && (*++argv)[0] == '-') {

		while ((c = *++argv[0])) {
			switch (c) {
			case 'i':
				qflags.mode_ia = true;
				break;
			case 'v':
				qflags.mode_vb = true;
				break;
			case 'd':
				qflags.valtype = type_int;
				value_flags_count++;
				break;
			case 'f':
				qflags.valtype = type_float;
				value_flags_count++;
				break;
			case 's':
				value_flags_count++;
				break;
			default :
				fprintf(qstreams.errstream,"unknown flag");
				goto error;
			}
		}
	}

	if (value_flags_count == 0 || value_flags_count == 1) {
		return (EXIT_SUCCESS);
	} else {
		fprintf(qstreams.errstream,"error: too many flags"
						" for testvalue format\n");
		goto error;
	}

	error:
		return EXIT_FAILURE;
}

// function to set the global STREAMS object
int myqueue_streams_set(void)
{
	// redirection of streams according to set flags
	// to be implemented later
	return EXIT_SUCCESS;
}

// functions to build and unbuild the data-queue
DLLIST * myqueue_enqueue(int stringlength)
{
	DLLIST * listhead;
	TESTDATA * dataptr;

	
	if ((listhead = dllist_head_create()) == NULL)
		return NULL;

	dataptr = myqueue_testdata_create(stringlength);

	while ( myqueue_testvalues_get(listhead, dataptr, stringlength) != EXIT_FAILURE) { 
			dllist_add_data(listhead, dataptr);
			dataptr = NULL;
			dataptr = myqueue_testdata_create(stringlength);


	}


	myqueue_testdata_destroy(dataptr, stringlength);

	dataptr= NULL;

	return listhead;

}

int myqueue_dequeue(DLLIST *listhead, int stringlength)
{
	TESTDATA * dataptr;
	
	(TESTDATA *)(dataptr = (TESTDATA *)dllist_delete_tail(listhead));
		if (dataptr == NULL)
			goto error;
		fprintf(stdout, "testdata name: %s\n", (char *)dataptr->name);
		memset(dataptr->name, 0, (stringlength * sizeof(char)));
		switch (qflags.valtype) {
			case type_string:
				fprintf(stdout, "testdata value: %s\n", (char *)dataptr->value);
				memset(dataptr->value, 0, (stringlength * sizeof(char)));
				break;
			case type_int:
				fprintf(stdout, "testdata value: %d\n", *(int *)dataptr->value);
				memset(dataptr->value, 0, sizeof(int));
				break;
			case type_float:
				fprintf(stdout, "testdata value: %f\n", *(float *)dataptr->value);
				memset(dataptr->value, 0, sizeof(int));
				break;
		}
		myqueue_testdata_destroy(dataptr, stringlength);

	return EXIT_SUCCESS;

	error:
	fprintf(stderr, "dequeue failed\n");
	return EXIT_FAILURE;
}


int myqueue_total_dequeue(DLLIST *listhead, int stringlength)
{
	if (listhead == NULL)
		goto error;

	while (dllist_elements(listhead) > 0) {

		if (myqueue_dequeue(listhead, stringlength) == EXIT_FAILURE)
			goto error;
	}

	return EXIT_SUCCESS;

	error:
		fprintf(stderr, "total dequeue failed\n");
		return EXIT_FAILURE;
}

// functions to read and process data from the input stream
int myqueue_testvalues_get(DLLIST *listhead, TESTDATA *dataptr,  int stringlength)
{
	char testdata_raw_name[stringlength];
	char testdata_raw_value[stringlength];
	char *targetptr;

	memset(testdata_raw_name, 0, sizeof(testdata_raw_name));
	memset(testdata_raw_value, 0, sizeof(testdata_raw_value));

	int testdata_name_accepted = false;
	int testdata_value_accepted = false;
	int value_is_name = true;

	int result_rawdata_get = 0;
	int result_rawdata_check = 0;
	int result_rawdata_convert = 0;

	if (dataptr == NULL || dataptr->name == NULL || dataptr->value == NULL)
		return EXIT_FAILURE;

	while (testdata_name_accepted == false || testdata_value_accepted == false) {
		if (value_is_name)
			targetptr = testdata_raw_name;
		else
			targetptr = testdata_raw_value;
			
		result_rawdata_get = myqueue_rawdata_get((dllist_elements(listhead) +1), value_is_name, targetptr, stringlength);
		if (result_rawdata_get == EXIT_FAILURE)
			return EXIT_FAILURE;
		if (result_rawdata_get == -1) {
			fprintf(stdout,"\nfolgender Wert wurde aus der Liste entfernt:\n\n");
			myqueue_dequeue(listhead, stringlength);
			continue;
		}
		result_rawdata_check = myqueue_rawdata_check(qflags.valtype, targetptr, stringlength);
		if (result_rawdata_check == EXIT_SUCCESS && value_is_name == true) {
			testdata_name_accepted = true;
			value_is_name = false;
		}
		else if (result_rawdata_check == EXIT_SUCCESS && value_is_name == false) {
			testdata_value_accepted = true;
		}
	}
	// convert and attach data_name
	result_rawdata_convert = myqueue_rawdata_convert(type_string, testdata_raw_name, dataptr->name, stringlength);
	if (result_rawdata_convert != EXIT_SUCCESS)
		return EXIT_FAILURE;
	// convert and attach data_value
	result_rawdata_convert = myqueue_rawdata_convert(qflags.valtype, testdata_raw_value, dataptr->value, stringlength);
	if (result_rawdata_convert != EXIT_SUCCESS)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;
}

int myqueue_rawdata_get(int elements_in_queue, int value_is_name, char *testdata_raw, int stringlength)
{
	int extracted_chars = 0;
	char answer = 0;
	char answerstring[stringlength]; //memset?
	
	while (extracted_chars <= 1) {
		if (qflags.mode_ia == true && value_is_name == true)
			printf("Bitte geben Sie einen Namen für den %d Datensatz ein:\n", elements_in_queue);
		if (qflags.mode_ia == true && value_is_name == false)
			printf("Bitte geben Sie einen Wert des %d Datensatzes ein:\n", elements_in_queue);
		extracted_chars = myqueue_getline(qstreams.instream, testdata_raw, stringlength);

		if (extracted_chars <= 1 && qflags.mode_ia == false)
			return EXIT_FAILURE;
		if (extracted_chars > 1 && qflags.mode_ia == true)
			return EXIT_SUCCESS;

		// dialogue for human interaction
		while (answer != 'j' && answer != 'n') {	
		printf("Eingabe beenden (alle Elemente werden ausgegeben) (j / n) "
			"oder erstes Element in der Queue ausgeben (d)\n");
			myqueue_getline(qstreams.instream, answerstring, stringlength);
			sscanf(answerstring, "%[j n d]c",&answer);  
		if (answer == 'j')
			return EXIT_FAILURE;
		else if (answer == 'n')
			break;
		else if (answer == 'd')
			return -1;
		else
			printf("Unglütlige Eingabe!\n");
		}
	}
}

int myqueue_rawdata_check(int type, char *rawdataptr, int stringlength)
{
	return EXIT_SUCCESS;
	/*	to be implemented later
	testdata_valid = false;
	switch (qflags.valtype) {
		case type_string:
			if (testdata_valid = myqueue_testdata_stringcheck();
				testdata_value_accepted = true;
			break;
		case type_int:
			if (testdata_valid = myqueue_testdata_intcheck());
				testdata_value_accepted = true;
			break;
		case type_float:
	 		if (testdata_valid = myqueue_testdata_floatcheck());
				testdata_value_accepted = true;
			break;
		default:
			return EXIT_FAILURE;
		}
	}
	*/
}

int myqueue_rawdata_convert(int type, char *rawdataptr, void * targetdataptr, int stringlength)
{
		switch (qflags.valtype) {
			case type_string:
				strcpy(targetdataptr, rawdataptr);
				return EXIT_SUCCESS;
			case type_int:
				// to be implemented ...
				return EXIT_FAILURE;
			case type_float:
				// to be implemented ...
				return EXIT_FAILURE;
			default :
				return EXIT_FAILURE;
		}
	return EXIT_FAILURE;
}

int myqueue_getline(FILE * stream, char *string, int stringlength)
{
	int c = 0;
	int i = 0;

	if (stream != NULL) {
		for (i = 0; (c = getc(qstreams.instream)) != '\n' && c != EOF; i++)
			string[i] = c;
		if ( c == '\n') {
			string[i] = c;
			i++;
		}
		return i;
	}

	return -1;
}

// creation of test data objects specific to the correct type
TESTDATA * myqueue_testdata_create(int stringlength)
{
	TESTDATA * dataptr = calloc(1, sizeof(dataptr));
	if (dataptr != NULL) {
		(dataptr->name = myqueue_string_create(stringlength));
		switch(qflags.valtype) {
			case type_string:
				(dataptr->value = myqueue_string_create(stringlength));
				break;
			case type_int:
				(dataptr->value = myqueue_int_create());
				break;
			case type_float:
				(dataptr->value = myqueue_float_create());
				break;
			default:
				goto error;
		}
		if (dataptr->value == NULL || dataptr->value == NULL) {
			goto error;
		}
		return dataptr;
	}

	error:
		fprintf(qstreams.errstream, "error: unable to create testdata\n");
		return NULL;
}


int myqueue_testdata_destroy(TESTDATA *dataptr, int stringlength)
{
	int op_result;

	if (dataptr != NULL && dataptr->name != NULL && dataptr->value != NULL) {

		op_result = 0;
		op_result = myqueue_string_destroy(dataptr->name, stringlength);
		if (op_result != EXIT_SUCCESS)
			goto error;

		op_result = 0;
		switch(qflags.valtype) {
			case type_string:
				op_result = myqueue_string_destroy(dataptr->value, stringlength);
				break;
			case type_int:
				op_result = myqueue_int_destroy(dataptr->value);
				break;
			case type_float:
				op_result = myqueue_float_destroy(dataptr->value);
				break;
			default:
				goto error;
		}
		if (op_result != EXIT_SUCCESS)
			goto error;
		return EXIT_SUCCESS;
	}

	error:
		fprintf(qstreams.errstream, "error: unable to destroy testdata\n");
		return EXIT_FAILURE;
}

// constructor and destructor funtions for primitives
char * myqueue_string_create(int stringlength)
{
	char * string = 0;

	string = calloc(stringlength, sizeof(char));

	if (string != NULL)
		return string;

	fprintf(stderr,"error: unable to create string\n");
	return NULL;
}

int myqueue_string_destroy(char *string, int stringlength)
{
	if (string != NULL ) {

	int i = 0;

	for (/*empty*/; i < stringlength && string[i] == 0; i++);
		if (i == (stringlength)) {
			free(string);
			string = NULL;
			return EXIT_SUCCESS;
		}
	}

	fprintf(stderr,"error: unable to destroy string\n");
	return EXIT_FAILURE;
}

int * myqueue_int_create(void)
{
	int * intptr = 0;

	intptr = calloc(1, sizeof(int));

	if (intptr != NULL)
		return intptr;

	fprintf(stderr,"error: unable to create integer\n");
	return NULL;
}

int myqueue_int_destroy(int *intptr)
{
	if (intptr != NULL && *intptr == 0) {
		free(intptr);
		intptr = NULL;
		return EXIT_SUCCESS;
	}
	fprintf(stderr,"error: unable to destroy integer\n");
	return EXIT_FAILURE;
};

float * myqueue_float_create(void)
{
	float * floatptr = 0;

	floatptr = calloc(1, sizeof(float));

	if (floatptr != NULL)
		return floatptr;

	fprintf(stderr,"error: unable to create float\n");
	return NULL;
}

int myqueue_float_destroy(float *floatptr)
{
	if (floatptr != NULL && *floatptr == 0) {
		free(floatptr);
		floatptr = NULL;
		return EXIT_SUCCESS;
	}

	fprintf(stderr,"error: unable to destroy float\n");
	return EXIT_FAILURE;
};


