#declare variable
CC = g++
INCLUDE_FILES = ./include ../Fibonacci_Heap/include ../Linked_List/include ../Adjacent_List/include ../MST_Edge/include ../Union_Find/include
INCLUDE_FLAGS = $(foreach d, $(INCLUDE_FILES), -I $d)
CTAGS_UTIL = /usr/local/bin/
CTAGS_FILES = ./include ../Fibonacci_Heap ../Fibonacci_Heap/include ../Linked_List ../Linked_List/include ../Adjacent_List ../Adjacent_List/include ../MST_Edge/include ../Union_Find ../Union_Find/include
CTAGS_FLAGS = $(foreach d, $(CTAGS_FILES),-a $d/*)
CFLAGS = -g -Wall -O3 -std=c++11 
COMPILE_FLAGS = -c
MAIN_OBJECT_NAME_MAIN = Kruskal_main
MAIN_OBJECT_SOURCE_MAIN = $(MAIN_OBJECT_NAME_MAIN).cpp
MAIN_OBJECT_EXEC_MAIN = $(MAIN_OBJECT_NAME_MAIN).o
MAIN_OBJECT_NAME = Kruskal
MAIN_OBJECT_SOURCE = $(MAIN_OBJECT_NAME).cpp
MAIN_OBJECT_EXEC = $(MAIN_OBJECT_NAME).o
MAIN_OBJECT_EXEC_OUTPUT = ../exec_output/
SUB_LINKED_LIST_SOURCE_PATH = ../Linked_List/
SUB_FIBONACCI_HEAP_SOURCE_PATH = ../Fibonacci_Heap/
SUB_ADJ_LIST_SOURCE_PATH = ../Adjacent_List/
SUB_UNION_FIND_SOURCE_PATH = ../Union_Find/

all : clean Kruskal all_file_tags
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(MAIN_OBJECT_EXEC_OUTPUT)Linked_List.o $(MAIN_OBJECT_EXEC_OUTPUT)Fibonacci_Heap.o $(MAIN_OBJECT_EXEC_OUTPUT)AdjList.o $(MAIN_OBJECT_EXEC_OUTPUT)Union_Find.o $(MAIN_OBJECT_EXEC_OUTPUT)$(MAIN_OBJECT_EXEC) $(MAIN_OBJECT_SOURCE_MAIN) -o $(MAIN_OBJECT_EXEC_OUTPUT)$(MAIN_OBJECT_EXEC_MAIN)
	${MAIN_OBJECT_EXEC_OUTPUT}$(MAIN_OBJECT_EXEC_MAIN)

Kruskal : $(MAIN_OBJECT_SOURCE) Linked_List Fibonacci_Heap Adjacent_List Union_Find
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) $(COMPILE_FLAGS) $(MAIN_OBJECT_SOURCE) -o $(MAIN_OBJECT_EXEC_OUTPUT)$(MAIN_OBJECT_EXEC)

Linked_List : $(SUB_LINKED_LIST_SOURCE_PATH)Linked_List.cpp 
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) $(SUB_LINKED_LIST_SOURCE_PATH)Linked_List.cpp $(INCLUDE_FLAGS) -o $(MAIN_OBJECT_EXEC_OUTPUT)Linked_List.o

Fibonacci_Heap : $(SUB_FIBONACCI_HEAP_SOURCE_PATH)Fibonacci_Heap.cpp
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) $(SUB_FIBONACCI_HEAP_SOURCE_PATH)Fibonacci_Heap.cpp $(INCLUDE_FLAGS) -o $(MAIN_OBJECT_EXEC_OUTPUT)Fibonacci_Heap.o

Adjacent_List : $(SUB_ADJ_LIST_SOURCE_PATH)AdjList.cpp
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) $(SUB_ADJ_LIST_SOURCE_PATH)AdjList.cpp $(INCLUDE_FLAGS) -o $(MAIN_OBJECT_EXEC_OUTPUT)AdjList.o

Union_Find : $(SUB_UNION_FIND_SOURCE_PATH)Union_Find.cpp
	$(CC) $(CFLAGS) $(COMPILE_FLAGS) $(SUB_UNION_FIND_SOURCE_PATH)Union_Find.cpp $(INCLUDE_FLAGS) -o $(MAIN_OBJECT_EXEC_OUTPUT)Union_Find.o

all_file_tags : 
	$(CTAGS_UTIL)ctags -R ./*
	$(CTAGS_UTIL)ctags $(CTAGS_FLAGS)

clean :
	rm -rf $(MAIN_OBJECT_EXEC_OUTPUT)Linked_List.o
	rm -rf $(MAIN_OBJECT_EXEC_OUTPUT)Fibonacci_Heap.o
	rm -rf $(MAIN_OBJECT_EXEC_OUTPUT)AdjList.o
	rm -rf $(MAIN_OBJECT_EXEC_OUTPUT)Union_Find.o
	rm -rf $(MAIN_OBJECT_EXEC_OUTPUT)$(MAIN_OBJECT_EXEC)
	rm -rf $(MAIN_OBJECT_EXEC_OUTPUT)$(MAIN_OBJECT_EXEC_MAIN)
	rm -rf ./tags
