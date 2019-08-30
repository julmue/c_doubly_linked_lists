#include <iostream>
#include <gtest/gtest.h>

#define ARRAYSIZE 150

extern "C"
{
#include "doubly_linked_list.h"
}



class DLListPrimitivesConstructorTest : public ::testing::Test {
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


TEST_F(DLListPrimitivesConstructorTest, headConstructor1) {

	ASSERT_NE(NULLptr, dllist_head_create());
}


TEST_F(DLListPrimitivesConstructorTest, nodeConstructor1) {

	ASSERT_NE(NULLptr, dllist_node_create());
}


TEST_F(DLListPrimitivesConstructorTest, headMemberInitialization) {
	DLLIST_HEAD *testhead = dllist_head_create();

	ASSERT_EQ(0, testhead->elements);
	ASSERT_EQ(NULLptr, testhead->first);
	ASSERT_EQ(NULLptr, testhead->tail);
}


TEST_F(DLListPrimitivesConstructorTest, nodeMemberInitialization) {
	DLLIST_NODE *testnode = dllist_node_create();

	ASSERT_EQ(NULLptr, testnode->prev);
	ASSERT_EQ(NULLptr, testnode->data);
	ASSERT_EQ(NULLptr, testnode->next);
}



class DLListPrimitivesDestructorTest : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		testhead1 = dllist_head_create();
		testnode1 = dllist_node_create();
		NULLptr = NULL;
		foo = 0xDEAD;
	}

	virtual void TearDown()
	{

	}

	DLLIST_HEAD *testhead1;
	DLLIST_NODE *testnode1;
	void *NULLptr;
	int foo;			// dummy integer
};


TEST_F(DLListPrimitivesDestructorTest, headDestructor1) {
	testhead1 = NULL;

	ASSERT_EQ(EXIT_FAILURE, dllist_head_destroy(testhead1));
}


TEST_F(DLListPrimitivesDestructorTest, headDestructor2) {
	testhead1->elements = foo;

	ASSERT_EQ(EXIT_FAILURE, dllist_head_destroy(testhead1));
}


TEST_F(DLListPrimitivesDestructorTest, headDestructor3) {
	testhead1->first = testnode1;

	ASSERT_EQ(EXIT_FAILURE, dllist_head_destroy(testhead1));
}


TEST_F(DLListPrimitivesDestructorTest, headDestructor4) {
	testhead1->tail = testnode1;

	ASSERT_EQ(EXIT_FAILURE, dllist_head_destroy(testhead1));
}


TEST_F(DLListPrimitivesDestructorTest, nodeDestructor1) {
	testnode1 = NULL;

	ASSERT_EQ(EXIT_FAILURE, dllist_node_destroy(testnode1));
}


TEST_F(DLListPrimitivesDestructorTest, nodeDestructor2) {
	DLLIST_NODE *testnode2 = dllist_node_create();
	testnode1->prev = testnode2;

	ASSERT_EQ(EXIT_FAILURE, dllist_node_destroy(testnode1));
}


TEST_F(DLListPrimitivesDestructorTest, nodeDestructor3) {
	DLLIST_NODE *testnode2 = dllist_node_create();
	testnode1->next = testnode2;

	ASSERT_EQ(EXIT_FAILURE, dllist_node_destroy(testnode1));
}


TEST_F(DLListPrimitivesDestructorTest, nodeDestructor4) {
	DLLIST_NODE *testnode1 = dllist_node_create();
	testnode1->data = &foo;

	ASSERT_EQ(EXIT_FAILURE, dllist_node_destroy(testnode1));
}



class DLListConstructorTest : public ::testing::Test {
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


TEST_F(DLListConstructorTest, listConstructor1) {

	ASSERT_NE(NULLptr, dllist_create());
}


TEST_F(DLListConstructorTest, listMemberInitialization1) {
	DLLIST *testlist = dllist_create();

	ASSERT_EQ(0, testlist->elements);
	ASSERT_EQ(NULLptr, testlist->first);
	ASSERT_EQ(NULLptr, testlist->tail);
}



class DLListAddDataTest : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;
		testlist1 = dllist_create();
		for (int i = 0; i < ARRAYSIZE; i++)
			testarray[i] = i;
		foo = 0xDEAD;
		fii = 0xF;
	}

	virtual void TearDown()
	{

	}

	void *NULLptr;
	DLLIST *testlist1;
	int testarray[ARRAYSIZE];
	int foo; 		// dummy integers
	int fii;
};


TEST_F(DLListAddDataTest, listMemberInitialization1) {

	ASSERT_EQ(EXIT_SUCCESS, dllist_add_data(testlist1, &foo));
	ASSERT_EQ(1, testlist1->elements);
	ASSERT_NE(NULLptr, testlist1->first->data);
	ASSERT_NE(NULLptr, testlist1->tail->data);
	ASSERT_EQ(testlist1->first, testlist1->tail);
}


TEST_F(DLListAddDataTest, listAddData2) {

	ASSERT_EQ(EXIT_SUCCESS, dllist_add_data(testlist1, &foo));
	ASSERT_EQ(EXIT_SUCCESS, dllist_add_data(testlist1, &fii));
	ASSERT_EQ(2, testlist1->elements);
	ASSERT_NE(testlist1->first, testlist1->tail);
}


TEST_F(DLListAddDataTest, listAddData3) {
	dllist_add_data(testlist1, &foo);
	dllist_add_data(testlist1, &fii);

	ASSERT_EQ(&fii, testlist1->first->data);
	ASSERT_EQ(&foo, testlist1->tail->data);
}


TEST_F(DLListAddDataTest, listAddData4) {
	dllist_add_data(testlist1, &foo);
	dllist_add_data(testlist1, &fii);

	ASSERT_EQ(fii,*(int *)testlist1->first->data);
	ASSERT_EQ(foo,*(int *)testlist1->tail->data);
}


TEST_F(DLListAddDataTest, listAddData5) {
	dllist_add_data(testlist1, &foo);
	dllist_add_data(testlist1, &fii);

	ASSERT_EQ(testlist1->tail, testlist1->first->next);
	ASSERT_EQ(testlist1->first, testlist1->tail->prev);
}


TEST_F(DLListAddDataTest, listAddData6) {
	dllist_add_data(testlist1, &foo);
	dllist_add_data(testlist1, &fii);

	ASSERT_EQ(foo, *(int *)testlist1->first->next->data);
	ASSERT_EQ(fii, *(int *)testlist1->tail->prev->data);
}


TEST_F(DLListAddDataTest, listAddData7) {
	for (int i = 0; i < ARRAYSIZE; i++)
		dllist_add_data(testlist1, &testarray[i]);

	ASSERT_EQ(testarray[ARRAYSIZE-1], *(int *)testlist1->first->data);
	ASSERT_EQ(testarray[0], *(int *)testlist1->tail->data);
	ASSERT_EQ(ARRAYSIZE, testlist1->elements);
}


TEST_F(DLListAddDataTest, listAddData8) {
	for (int i = 0; i < ARRAYSIZE; i++)
		dllist_add_data(testlist1, &testarray[i]);

	ASSERT_EQ(&testarray[ARRAYSIZE-1], (int *)testlist1->first->data);
	ASSERT_EQ(&testarray[0], (int *)testlist1->tail->data);
}

TEST_F(DLListAddDataTest, listAddData9) {
	for (int i = 0; i < ARRAYSIZE; i++)
		dllist_add_data(testlist1, &testarray[i]);

	ASSERT_EQ(NULLptr, (int *)testlist1->first->prev);
	ASSERT_EQ(NULLptr, (int *)testlist1->tail->next);
}



class DLListElementsTest : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		NULLptr = NULL;
		testlist1 = dllist_create();
	}

	virtual void TearDown()
	{

	}

	DLLIST *testlist1;
	DLLIST_NODE *testnode1;
	void *NULLptr;
	int foo; 		// dummy integers
	int fii;
};


TEST_F(DLListElementsTest, elements1) {
	testlist1 = NULL;

	ASSERT_EQ(-1, dllist_elements(testlist1));
}


TEST_F(DLListElementsTest, elements2) {
	ASSERT_EQ(0, dllist_elements(testlist1));
}


TEST_F(DLListElementsTest, elements3) {
	dllist_add_data(testlist1, &foo);

	ASSERT_EQ(1, dllist_elements(testlist1));
}



class DLListDeleteTailTest : public ::testing::Test {
 protected:
	virtual void SetUp()
	{
		testlist1 = dllist_create();
		for (int i = 0; i < ARRAYSIZE; i++)
			testarray[i] = i+1;
		for (int i = 0; i < ARRAYSIZE; i++)
			dllist_add_data(testlist1, &testarray[i]);
		empty_testlist = dllist_create();
		NULL_testlist = NULL;
		NULLptr = NULL;
	}

	virtual void TearDown()
	{

	}
	DLLIST *testlist1;
	DLLIST *empty_testlist;
	DLLIST *NULL_testlist;
	void *NULLptr;
	void *testvoidptr;
	int testarray[ARRAYSIZE];
};


TEST_F(DLListDeleteTailTest, deleteTailTest1) {
	testvoidptr = dllist_delete_tail(NULL_testlist);

	ASSERT_EQ(NULLptr, testvoidptr);
}


TEST_F(DLListDeleteTailTest, deleteTailTest2) {
	testvoidptr = dllist_delete_tail(empty_testlist);

	ASSERT_EQ(NULLptr, testvoidptr);
}


TEST_F(DLListDeleteTailTest, deleteTailTest3) {
	testvoidptr = dllist_delete_tail(testlist1);

	ASSERT_EQ(&testarray[0], testvoidptr);
}


TEST_F(DLListDeleteTailTest, deleteTailTest4) {
	testvoidptr = dllist_delete_tail(testlist1);

	ASSERT_EQ(&testarray[1], (int *)testlist1->tail->data);
}

TEST_F(DLListDeleteTailTest, deleteTailTest5) {
	testvoidptr = dllist_delete_tail(testlist1);

	ASSERT_EQ(ARRAYSIZE -1, dllist_elements(testlist1));
}
/*
TEST_F(DLListDeleteTailTest, deleteTailTestXXX) {
	DLLIST_NODE **testnodeptrptr;

	testnodeptrptr = &(testlist1->tail);

	testvoidptr = dllist_delete_tail(testlist1);

	ASSERT_EQ(NULLptr, *testnodeptrptr);
}
*/
TEST_F(DLListDeleteTailTest, deleteTailTest6) {

	for (int i = 0; i < ARRAYSIZE; i++) {
		testvoidptr = dllist_delete_tail(testlist1);

		ASSERT_EQ(&testarray[i], testvoidptr);
	}

}

TEST_F(DLListDeleteTailTest, deleteTailTest7) {

	for (int i = 0; i < ARRAYSIZE; i++) {
		testvoidptr = dllist_delete_tail(testlist1);
	}
	ASSERT_EQ(NULLptr, testlist1->tail);
	ASSERT_EQ(NULLptr, testlist1->first);
	ASSERT_EQ(0, dllist_elements(testlist1));
}


int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
