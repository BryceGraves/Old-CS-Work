#Global variables used for compiling
#Remember to take out the flippin c90 flag
COMPILER=gcc
COMPILER_FLAGS=-g -c -pthread -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra -Werror -Wunsafe-loop-optimizations
MEMORY_CHECKER=valgrind
PART_ONE_EXECUTABLE=primesMT
PART_ONE_OBJECT=primesMT.o
PART_ONE_SOURCE_FILE=primesMT.c
PART_TWO_EXECUTABLE_ONE=fifo_client
PART_TWO_EXECUTABLE_TWO=fifo_server
PART_TWO_OBJECT_ONE=fifo_client.o
PART_TWO_OBJECT_TWO=fifo_server.o
PART_TWO_SOURCE_FILE_ONE=fifo_client.c
PART_TWO_SOURCE_FILE_TWO=fifo_server.c

all: $(PART_ONE_EXECUTABLE) $(PART_TWO_EXECUTABLE_ONE) $(PART_TWO_EXECUTABLE_TWO)

$(PART_ONE_EXECUTABLE): -lpthread $(PART_ONE_OBJECT)

$(PART_ONE_OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_ONE_SOURCE_FILE)

$(PART_TWO_EXECUTABLE_ONE): $(PART_TWO_OBJECT_ONE)

$(PART_TWO_OBJECT_ONE):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_TWO_SOURCE_FILE_ONE)

$(PART_TWO_EXECUTABLE_TWO): $(PART_TWO_OBJECT_TWO)

$(PART_TWO_OBJECT_TWO):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_TWO_SOURCE_FILE_TWO)

clean:
	rm $(PART_ONE_EXECUTABLE) $(PART_TWO_EXECUTABLE_ONE) $(PART_TWO_EXECUTABLE_TWO) *.o
