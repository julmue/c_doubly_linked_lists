# PROJECT DIRECTORIES
PROJECT_DIRECTORY = .
INCLUDE_DIR = $(PROJECT_DIRECTORY)/include

# GOGGLE TEST DIRECTORIES
# Google Test headers
GTEST_HEADER_DIRECTORY = /usr/include/gtest
GTEST_HEADERS = $(GTEST_HEADER_DIRECTORY)/*.h \
                $(GTEST_HEADER_DIRECTORY)/internal/*.h
# Google Test direcotry
GTEST_DIR = /usr/src/gtest
# Google Test source code
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# VPATH
VPATH = $(PROJECT_DIRECTORY) $(SOURCE_DIR) $(INCLUDE_DIR) $(TESTS_DIR) $(GTEST_TEMP_DIR)


# COMPILATION
# Flags passed to the preprocessor.
CPPFLAGS += -I$(GTEST_DIR)/include -I$(INCLUDE_DIR)
# Flags passed to the C++ compiler.
CXXFLAGS += -g -Wall -Wextra -pthread 


#GTEST TARGETS
all: gtest.a gtest_main.a 

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GTEST_HEADER_DIRECTORY) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) -I$(GTEST_HEADER_DIRECTORY) $(CXXFLAGS) -c $(GTEST_DIR)/src/gtest_main.cc


# House-keeping build targets.
.PHONY: clean
clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o
