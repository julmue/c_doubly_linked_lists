#include <iostream>
#include <gtest/gtest.h>
#include <cstdio>
//#include <cerrno>

extern "C"
{
#include "myqueue.h"
}



class myQueueStringCreate : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;		

	}

	virtual void TearDown()
	{

	}

	int argc;
	char argv[2][1];

	void *NULLptr;
};


TEST_F(myQueueStringCreate, constructorTest1) {

	ASSERT_NE(NULLptr, myqueue_string_create(STRLEN));

}

TEST_F(myQueueStringCreate, constructorTest2) {

	char * string = myqueue_string_create(STRLEN);
	for (int i = 0; i < STRLEN; i++)
		ASSERT_EQ(0, string[i]);

}


class myQueueStringDestroy : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;
	}

	virtual void TearDown()
	{

	}

	void *NULLptr;
};

TEST_F(myQueueStringDestroy, destructorTest1) {

	ASSERT_EQ(EXIT_FAILURE, myqueue_string_destroy(NULL, STRLEN));

}

TEST_F(myQueueStringDestroy, destructorTest2) {
	char * string = myqueue_string_create(STRLEN);

	ASSERT_EQ(EXIT_SUCCESS, myqueue_string_destroy(string, STRLEN));

}

TEST_F(myQueueStringDestroy, destructorTest3) {

	char * string = myqueue_string_create(STRLEN);

	ASSERT_NE(NULLptr, string);
	strcpy(string, "TEST TEST TEST");
	ASSERT_EQ(EXIT_FAILURE, myqueue_string_destroy(string, STRLEN));

}


class myQueueIntCreate : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;		
	}

	virtual void TearDown()
	{

	}

	void *NULLptr;
};

TEST_F(myQueueIntCreate, constructorTest1) {

	ASSERT_NE(NULLptr, myqueue_int_create());

}

TEST_F(myQueueIntCreate, constructorTest2) {

	ASSERT_EQ(0, *myqueue_int_create());

}


class myQueueIntDestroy : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;		
	}

	virtual void TearDown()
	{

	}

	void *NULLptr;
};

TEST_F(myQueueIntDestroy, destructorTest1) {

	ASSERT_EQ(EXIT_FAILURE, myqueue_int_destroy(NULL));

}

TEST_F(myQueueIntDestroy, destructorTest2) {
	int *intptr = myqueue_int_create();

	ASSERT_EQ(EXIT_SUCCESS, myqueue_int_destroy(intptr));

}

TEST_F(myQueueIntDestroy, destructorTest3) {
	int *intptr = myqueue_int_create();

	*intptr = 1;
	
	ASSERT_NE(EXIT_SUCCESS, myqueue_int_destroy(intptr));

}


class myQueueFloatCreate : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;		
	}

	virtual void TearDown()
	{

	}

	void *NULLptr;
};

TEST_F(myQueueFloatCreate, constructorTest1) {

	ASSERT_NE(NULLptr, myqueue_float_create());

}

TEST_F(myQueueFloatCreate, constructorTest2) {

	ASSERT_EQ(0, *myqueue_float_create());

}


class myQueueFloatDestroy : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;		
	}

	virtual void TearDown()
	{

	}

	void *NULLptr;
};

TEST_F(myQueueFloatDestroy, destructorTest1) {

	ASSERT_EQ(EXIT_FAILURE, myqueue_float_destroy(NULL));

}

TEST_F(myQueueFloatDestroy, destructorTest2) {
	float *intptr = myqueue_float_create();

	ASSERT_EQ(EXIT_SUCCESS, myqueue_float_destroy(intptr));

}

TEST_F(myQueueFloatDestroy, destructorTest3) {
	float *floatptr = myqueue_float_create();

	*floatptr = 1;
	
	ASSERT_NE(EXIT_SUCCESS, myqueue_float_destroy(floatptr));

}


class myQueueTestDataCreate : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;
		args[0] = 's';
		args[1] = '0';
		argv = &args;
		// have to call myqueue() first to set up global variabls
		myqueue(1, (char **)argv);
	}

	virtual void TearDown()
	{

	}
	// mock command line args for myqueue()
	char (*argv)[2];
	char args[2];
	
	

	void *NULLptr;
};

TEST_F(myQueueTestDataCreate, constructorTest1) {

	ASSERT_NE(NULLptr, myqueue_testdata_create(STRLEN));
}

TEST_F(myQueueTestDataCreate, constructorTest2) {
	TESTDATA * testdataptr;
	testdataptr = myqueue_testdata_create(STRLEN);

	strcpy((char *)(testdataptr->name), "TEST TEST TEST");

	ASSERT_STREQ("TEST TEST TEST", (char *)(testdataptr->name));
}

TEST_F(myQueueTestDataCreate, memberInitialziation1) {
	TESTDATA * testdataptr;
	testdataptr = myqueue_testdata_create(STRLEN);

	char * testname_string = (char *)(testdataptr->name);
	char * testvalue_string = (char *)(testdataptr->value);

	for (int i = 0; i < STRLEN; i++) {
		ASSERT_EQ(0, testname_string[i]);
		ASSERT_EQ(0, testvalue_string[i]);
	}
}
/*
TEST_F(myQueueTestDataCreate, memberInitialziation2) {
	TESTDATA * testdataptr;
	float testnumber = 123456.78910;

	testflagptr->testvalue = 3;
	testdataptr = myqueue_testdata_create(teststreamptr, testflagptr, STRLEN);
	
	float * testvalue_float = (float *)testdataptr->testdata_value;
	*testvalue_float = testnumber;

	ASSERT_EQ(testnumber, *(float *)testdataptr->testdata_value);
}
*/

class myQueueTestDataDestroy : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;

		args[0] = 's';
		args[1] = '0';
		argv = &args;
		// have to call myqueue() first to set up global variabls
		myqueue(1, (char **)argv);

		dataptr = myqueue_testdata_create( STRLEN);
	}

	virtual void TearDown()
	{

	}
	// mock command line args for myqueue()
	char (*argv)[2];
	char args[2];	
	
	TESTDATA * dataptr;
	void *NULLptr;
};

TEST_F(myQueueTestDataDestroy, destructorTest1) {

	ASSERT_EQ(EXIT_FAILURE, myqueue_testdata_destroy( NULL, STRLEN));
}

TEST_F(myQueueTestDataDestroy, destructorTest2) {

	ASSERT_EQ(EXIT_SUCCESS, myqueue_testdata_destroy( dataptr, STRLEN));
}

TEST_F(myQueueTestDataDestroy, destructorTest3) {

	dataptr->name = NULL;

	ASSERT_EQ(EXIT_FAILURE, myqueue_testdata_destroy( dataptr, STRLEN));
}

TEST_F(myQueueTestDataDestroy, destructorTest4) {

	dataptr->value = NULL;

	ASSERT_EQ(EXIT_FAILURE, myqueue_testdata_destroy( dataptr, STRLEN));
}

TEST_F(myQueueTestDataDestroy, destructorTest5) {

	strcpy ((char *)(dataptr->name), "TEST TEST TEST");

	ASSERT_EQ(EXIT_FAILURE, myqueue_testdata_destroy(dataptr, STRLEN));
}

TEST_F(myQueueTestDataDestroy, constructorTest6) {

	strcpy ((char *)(dataptr->value), "TEST TEST TEST");

	ASSERT_EQ(EXIT_FAILURE, myqueue_testdata_destroy(dataptr, STRLEN));
}
/*
class myQueueGetLine : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		// initialize test objects
		memset(target_string, 0, sizeof(target_string));
		NULLfileptr = 0;
		
		// initialize flags
		testflags.mode_interactive = false;
		testflags.mode_verbose = false;
		testflags.testvalue = 1;

		testflagptr = &testflags;
	
		// Attaching streams to stream object
		teststreams.myqueue_instream = stdin;
		teststreams.myqueue_outstream = stdout;
		teststreams.myqueue_errorstream = stdout;
	
		teststreamptr = &teststreams;

		dataptr = myqueue_testdata_create(teststreamptr, testflagptr, STRLEN);
		
		// Preparation of the simulated user input
		strcpy(testname, "TESTNAME1");
		strcpy(testvalue, "TESTVALUE1");

		// Preparation of the strings including the '\n' charachters
		// this is the goal of stringextract method
		strcpy(required_testdata_name, testname);
		strcat(required_testdata_name, "\n");
		strcpy(required_testdata_value, testvalue);
		strcat(required_testdata_value, "\n");

		// Preparing stream object
		teststream = fopen("TESTSTREAM1", "w+");
		fprintf(teststream, "%s\n%s\n", testname, testvalue); 
		fclose(teststream);
		
		// Reopening stream object for test
		teststream = fopen("TESTSTREAM1", "r");

	}

	virtual void TearDown()
	{
		// Closing and removing stream object
		fclose(teststream);
		remove( "TESTSTREAM1");
	}

	FILE * NULLfileptr;
	FILE * teststream;

	FLAGS testflags;
	FLAGS * testflagptr;
	
	STREAMS teststreams;
	STREAMS * teststreamptr;
	
	TESTDATA * dataptr;

	char testname[100];
	char testvalue[100];
	char required_testdata_name[100];
	char required_testdata_value[100];
	char target_string[STRLEN];
	int result;
};


TEST_F(myQueueGetLine, getlineTest1) {

	ASSERT_EQ(-1, myqueue_getline(NULLfileptr, target_string, STRLEN));
}

TEST_F(myQueueGetLine, getlineTest2) {

	ASSERT_NE(-1, myqueue_getline(teststream, target_string, STRLEN));
}

TEST_F(myQueueGetLine, getlineTest3) {

	result = myqueue_getline(teststream, target_string, STRLEN);

	ASSERT_STREQ(required_testdata_name, target_string);

	ASSERT_EQ(10, result);
}

TEST_F(myQueueGetLine, getlineTest4) {
	result = myqueue_getline(teststream, target_string, STRLEN);

	ASSERT_STREQ(required_testdata_name, target_string);
	ASSERT_EQ(10, result);

	result = myqueue_getline(teststream, target_string, STRLEN);

	ASSERT_STREQ(required_testdata_value, target_string);
	ASSERT_EQ(11, result);
}
*/

class myQueueRawDataGet : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;

		args[0] = 's';
		args[1] = '0';
		argv = &args;
		// have to call myqueue() first to set up global variabls
		myqueue(1, (char **)argv);

		dataptr = myqueue_testdata_create( STRLEN);
	}

	virtual void TearDown()
	{
	}
	// mock command line args for myqueue()
	char (*argv)[2];
	char args[2];	

	char target_sting[STRLEN];
	void *NULLptr;

	TESTDATA * dataptr;

};

/*
TEST_F(myQueueRawDataGet, Test1) {

	ASSERT_EQ(EXIT_FAILURE, myqueue_rawdata_get((char *)(&target_sting), STRLEN));
}
*/
/*
class myQueueTestValuesGet : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		// initialize flags
		testflags.mode_interactive = false;
		testflags.mode_verbose = false;
		testflags.testvalue = 1;

		testflagptr = &testflags;

		// Attaching streams to stream object
		teststreams.myqueue_instream = stdin;
		teststreams.myqueue_outstream = stdout;
		teststreams.myqueue_errorstream = stdout;
	
		teststreamptr = &teststreams;


		// initialize pointers
		dataptr = myqueue_testdata_create(teststreamptr, testflagptr, STRLEN);
		NULLptr = NULL;
		
		// Preparation of the simulated user input
		strcpy(testname, "TESTNAME1");
		strcpy(testvalue, "TESTVALUE1");

		// Preparation of the strings including the '\n' charachters
		// this is the goal of stringextract method
		strcpy(required_testdata_name, testname);
		strcat(required_testdata_name, "\n");
		strcpy(required_testdata_value, testvalue);
		strcat(required_testdata_value, "\n");

		// Preparing stream object
		teststream = fopen("TESTSTREAM1", "w+");
		fprintf(teststream, "%s\n%s\n", testname, testvalue); 
		fclose(teststream);
		
		// Reopening stream object for test
		teststream = fopen("TESTSTREAM1", "r");
	}

	virtual void TearDown()
	{
		// Closing and removing stream object
		fclose(teststream);
		remove( "TESTSTREAM1");
	}

	FLAGS testflags;
	FLAGS * testflagptr;

	STREAMS teststreams;
	STREAMS * teststreamptr;
	
	TESTDATA * dataptr;

	FILE * teststream;

	void *NULLptr;
	char testname[100];
	char testvalue[100];
	char required_testdata_name[100];
	char required_testdata_value[100];
	int result;
};

TEST_F(myQueueTestValuesGet, Test1) {
	TESTDATA * NULLdataptr = NULL;
	
	ASSERT_EQ(EXIT_FAILURE,
			myqueue_testvalues_get(teststream, NULLdataptr, &testflags, STRLEN));
}

TEST_F(myQueueTestValuesGet, Test2) {
	
	ASSERT_EQ(EXIT_SUCCESS,
			myqueue_testvalues_get(teststream, dataptr, &testflags, STRLEN));
}


TEST_F(myQueueTestValuesGet, constructorTest3) {

	result = myqueue_testvalues_get(teststream, dataptr, &testflags, STRLEN);
	
	ASSERT_STREQ(dataptr->testdata_name, required_testdata_name);
}


TEST_F(myQueueTestValuesGet, constructorTest4) {

	result = myqueue_testvalues_get(teststream, dataptr, &testflags, STRLEN);
	
	ASSERT_STREQ(dataptr->testdata_value, required_testdata_value);
}




class myQueueEnqueue : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		// initialize flags
		testflags.mode_interactive = false;
		testflags.mode_verbose = false;
		testflags.testvalue = 1;

		// initialize pointers
		NULLfileptr = NULL;
		NULLptr = NULL;
		// Preparation of the simulated user input
		strcpy(testname, "TESTNAME1");
		strcpy(testvalue, "TESTVALUE1");

		// Preparation of the strings including the '\n' charachters
		// this is the goal of stringextract method
		strcpy(required_testdata_name, testname);
		strcat(required_testdata_name, "\n");
		strcpy(required_testdata_value, testvalue);
		strcat(required_testdata_value, "\n");

		// Preparing stream object
		teststream = fopen("TESTSTREAM1", "w+");
		fprintf(teststream, "%s\n%s\n", testname, testvalue); 
		fclose(teststream);
		
		// Reopening stream object for test
		teststream = fopen("TESTSTREAM1", "r");

		// Attaching streams to stream object
		teststreams.myqueue_instream = teststream;
		teststreams.myqueue_outstream = stdout;
		teststreams.myqueue_errorstream = stdout;
	}

	virtual void TearDown()
	{
		// Closing and removing stream object
		fclose(teststream);
		remove( "TESTSTREAM1");
	}

	FLAGS testflags;
	STREAMS teststreams;
	FILE * NULLfileptr;
	FILE * teststream;
	TESTDATA * dataptr;
	void * NULLptr;
	char testname[100];
	char testvalue[100];
	char required_testdata_name[100];
	char required_testdata_value[100];
	int result;
};


TEST_F(myQueueEnqueue, constructorTest1) {

	ASSERT_EQ(NULLptr, myqueue_enqueue(NULL, &testflags, STRLEN));
	
}

TEST_F(myQueueEnqueue, constructorTest2) {

	ASSERT_NE(NULLptr, myqueue_enqueue(&teststreams, &testflags, STRLEN));
	
}



class myQueueDequeue : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;
	}

	virtual void TearDown()
	{

	}

	void *NULLptr;
};


TEST_F(myQueueEnqueue, constructorTest3) {


	ASSERT_NE(NULLptr, myqueue_enqueue(stdin, STRLEN));
	
}



class myQueue : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		memset(argv, 0, sizeof(argv));
		strcpy(arg0,  "program_name");
		argv[0] = arg0;
		argv[1] = NULL;
		NULLptr = NULL;
	
		argc = 0;
	}

	virtual void TearDown()
	{

	}
	
	int argc;
	char *argv[4];
	char arg0[20];
	char arg1[20];
	char arg2[20];
	char arg3[20];

	void *NULLptr;
};
*/

/*
TEST_F(myQueue, Test1) {

	ASSERT_EQ(EXIT_SUCCESS, myqueue(argc, argv));
}
*/

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
