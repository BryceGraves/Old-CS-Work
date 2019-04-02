#Global variables used for compiling
COMPILER=gcc
COMPILER_FLAGS=-std=c90 -g -c -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement
MEMORY_CHECKER=valgrind
EXECUTABLE=linked_list
OBJECT=linked_list.o
SOURCE_FILE=linked_list.c
FILE_PATH= ingredients1.txt ingredients2.txt ingredients3.txt

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECT)

$(OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(SOURCE_FILE)

run:
	./$(EXECUTABLE) $(FILE_PATH)

run-debug:
	$(MEMORY_CHECKER) ./$(EXECUTABLE) $(FILE_PATH)

clean:
	rm $(EXECUTABLE) $(OBJECT)
