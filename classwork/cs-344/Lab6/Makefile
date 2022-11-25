#Global variables used for compiling
#Remember to take out the flippin c90 flag
COMPILER=gcc
COMPILER_FLAGS=-g -c -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra
MEMORY_CHECKER=valgrind
PART_ONE_EXECUTABLE=bigFiles
PART_TWO_EXECUTABLE=bennysh
PART_ONE_OBJECT=bigFiles.o
PART_TWO_OBJECTS=bennysh.o cmd_parse.o
PART_ONE_SOURCE_FILE=bigFiles.c
PART_TWO_SOURCE_FILES=bennysh.c cmd_parse.c

all: $(PART_ONE_EXECUTABLE) $(PART_TWO_EXECUTABLE)

$(PART_ONE_EXECUTABLE): $(PART_ONE_OBJECT)

$(PART_TWO_EXECUTABLE):$(PART_TWO_OBJECTS)

$(PART_ONE_OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_ONE_SOURCE_FILE)

$(PART_TWO_OBJECTS):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_TWO_SOURCE_FILES)

clean:
	rm $(PART_ONE_EXECUTABLE) $(PART_TWO_EXECUTABLE) *.o
