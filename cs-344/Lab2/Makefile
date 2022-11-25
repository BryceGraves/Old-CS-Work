#Global variables used for compiling
COMPILER=gcc
COMPILER_FLAGS=-g -Wall -o
EXECUTABLE=mywc
SOURCES=mywc.c
RUNNING_FLAGS=-f
FILE_PATH= ingredients1.txt

all:
	$(COMPILER) $(COMPILER_FLAGS) $(EXECUTABLE) $(SOURCES)

run:
	./$(EXECUTABLE) $(RUNNING_FLAGS) $(FILE_PATH)

clean:
	rm $(EXECUTABLE)
