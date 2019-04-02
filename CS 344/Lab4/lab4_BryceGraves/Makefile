#Global variables used for compiling
#Remember to take out the flippin c90 flag
COMPILER=gcc
COMPILER_FLAGS=-g -c -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra
MEMORY_CHECKER=valgrind
PART_ONE_EXECUTABLE=mystat
PART_TWO_EXECUTABLE=csv2bin
PART_THREE_EXECUTABLE=bin2csv
PART_ONE_OBJECT=mystat.o
PART_TWO_OBJECT=csv2bin.o
PART_THREE_OBJECT=bin2csv.o
PART_ONE_SOURCE_FILE=mystat.c
PART_TWO_SOURCE_FILE=csv2bin.c
PART_THREE_SOURCE_FILE=bin2csv.c

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
