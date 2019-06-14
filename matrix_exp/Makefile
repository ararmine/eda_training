PROG := matrix_exp
TARGET := libmatrix.so
SOURCES := matrix.cpp
TEST_SRC := test.cpp
HEADERS := matrix.h
OBJECTS = $(SOURCES:.cpp=.o)

BASE_PATH := .
INCLUDE_PATH = $(BASE_PATH)/include
SRC_PATH = $(BASE_PATH)/src
BIN_PATH = $(BASE_PATH)/bin
OBJ_PATH = $(BASE_PATH)/obj
LIB_PATH = $(BASE_PATH)/libs
TEST_PATH = $(BASE_PATH)/test


CC = g++
DEBUG = -g
LIBS = -lmatrix

all: $(LIB_PATH)/$(TARGET)

$(LIB_PATH)/$(TARGET): $(OBJ_PATH)/$(OBJECTS)
		@mkdir -p $(BIN_PATH)
		@mkdir -p $(LIB_PATH)
		$(CC) -shared $(DEBUG) -fPIC $(OBJ_PATH)/$(OBJECTS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
		@mkdir -p $(OBJ_PATH)
		$(CC) -c -std=c++11 -O0 $(DEBUG) -fPIC $^ -I$(INCLUDE_PATH) -o $@ 
				

.PHONY: claen
	clean:
		rm -rf $(OBJ_PATH) $(BIN_PATH) $(LIB_PATH)

test: $(BIN_PATH)/$(PROG)
		@cd $(TEST_PATH) && LD_LIBRARY_PATH=../$(LIB_PATH) ../$(BIN_PATH)/$(PROG)

$(BIN_PATH)/$(PROG): $(TEST_PATH)/$(TEST_SRC)
		$(CC) -std=c++11 $(DEBUG) -L$(LIB_PATH) -I$(INCLUDE_PATH) $^ -o $@ $(LIBS)
