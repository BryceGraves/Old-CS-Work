#Global variables used for compiling
#Remember to take out the flippin c90 flag
COMPILER=gcc
COMPILER_FLAGS=-g -c -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra
MEMORY_CHECKER=valgrind
PART_ONE_EXECUTABLE=bin2index
PART_TWO_EXECUTABLE=binlookup
PART_THREE_EXECUTABLE=beavar
PART_ONE_OBJECT=bin2index.o
PART_TWO_OBJECT=binlookup.o
PART_THREE_OBJECT=beavar.o
PART_ONE_SOURCE_FILE=bin2index.c
PART_TWO_SOURCE_FILE=binlookup.c
PART_THREE_SOURCE_FILE=beavar.c

all: $(PART_ONE_EXECUTABLE) $(PART_TWO_EXECUTABLE) $(PART_THREE_EXECUTABLE)

$(PART_ONE_EXECUTABLE): $(PART_ONE_OBJECT)

$(PART_TWO_EXECUTABLE):$(PART_TWO_OBJECT)

$(PART_THREE_EXECUTABLE):$(PART_THREE_OBJECT)

$(PART_ONE_OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_ONE_SOURCE_FILE)

$(PART_TWO_OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_TWO_SOURCE_FILE)

$(PART_THREE_OBJECT):
		$(COMPILER) $(COMPILER_FLAGS) $(PART_THREE_SOURCE_FILE)

clean:
	rm $(PART_ONE_EXECUTABLE) $(PART_TWO_EXECUTABLE) $(PART_THREE_EXECUTABLE) *.o
