# PROJECT DIRECTORIES
PROJECT_DIRECTORY = .
SOURCE_DIR = $(PROJECT_DIRECTORY)/src
INCLUDE_DIR = $(PROJECT_DIRECTORY)/include
TESTS_DIR = $(PROJECT_DIRECTORY)/tests
GTEST_TEMP_DIR = $(PROJECT_DIRECTORY)/gtemp

# VPATH - variable for locateing the sourcefiles
VPATH = $(PROJECT_DIRECTORY) $(SOURCE_DIR) $(INCLUDE_DIR) $(TESTS_DIR) $(GTEST_TEMP_DIR)


# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
TESTS = dllist_unittest queue_unittest


# COMPILATION
# included libraries for C
LIBRARIESC =
# included libraries for C++
LIBRARIESCXX =
# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include -I$(INCLUDE_DIR)
# Flags passed to the C Compiler
CFLAGS += -g -Wall -std=c99 $(LIBRARIESC)
# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread $(LIBRARIESXX)
# Flags passed to gtest
GTESTFLAGS = --gtest_print_time=0

#MAKE
# shuts up make
SILENT = @

# TEST TARGETS
# A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.
all:  dllist_unittest queue_unittest
	$(SILENT)./dllist_unittest $(GTESTFLAGS)
	$(SILENT)./queue_unittest $(GTESTFLAGS)

# TEST1 : DOUBLY LINKED LIST LIBRARY
dllist_unittest : 	doubly_linked_list.o\
			dllist_unittest.o\
			$(GTEST_TEMP_DIR)/gtest_main.a
	$(SILENT) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

dllist_unittest.o : 	dllist_unittest.cc\
			doubly_linked_list.h\
			$(GTEST_HEADERS)
	$(SILENT) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 

# For external linkage in C++ compile C code with gcc!!!
doubly_linked_list.o : doubly_linked_list.c doubly_linked_list.h $(GTEST_HEADERS)
	$(SILENT) $(CC) $(CPPFLAGS) $(CFLAGS) -c $(SOURCE_DIR)/doubly_linked_list.c



# TEST2 : QUEUE
queue_unittest : 	myqueue.o\
			queue_unittest.o\
			doubly_linked_list.o\
			$(GTEST_TEMP_DIR)/gtest_main.a
	$(SILENT) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

queue_unittest.o : 	queue_unittest.cc\
			myqueue.h\
			doubly_linked_list.h\
			$(GTEST_HEADERS)
	$(SILENT) $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< 


myqueue.o : myqueue.c myqueue.h $(GTEST_HEADERS)
	$(SILENT) $(CC) $(CPPFLAGS) $(CFLAGS) -c $(SOURCE_DIR)/myqueue.c


# RUNNABLE PROGRAM
myqueue_run: 	myqueue_run.c\
		myqueue.c myqueue.h\
		doubly_linked_list.c doubly_linked_list.h
	$(SILENT) $(CC) $(CPPFLAGS) $(CFLAGS) $(SOURCE_DIR)/myqueue_run.c $(SOURCE_DIR)/myqueue.c $(SOURCE_DIR)/doubly_linked_list.c -o $@


# RUNNABLE WINDOWS PROGRAM
myqueuewin_run: 	myqueue_run.c\
		myqueue.c myqueue.h\
		doubly_linked_list.c doubly_linked_list.h
	$(SILENT) i586-mingw32msvc-gcc $(CPPFLAGS) $(CFLAGS) $(SOURCE_DIR)/myqueue_run.c $(SOURCE_DIR)/myqueue.c $(SOURCE_DIR)/doubly_linked_list.c -o $@



# House-keeping build targets.
tests : $(TESTS)


.PHONY: clean
clean :
	rm -f $(TESTS) gtest.a gtest_main.a myqueue_run *.o


.PHONY: clean_test
clean_tests :
	rm -f $(TESTS)


# Build messages
.PHONY: build_msg

build_msg:
	@printf "#\n# Building $(Program) \n#\n"

