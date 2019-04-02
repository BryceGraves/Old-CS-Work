#Global variables used for compiling
#Remember to take out the flippin c90 flag
COMPILER=gcc
COMPILER_FLAGS=-g -c -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra
MEMORY_CHECKER=valgrind
PART_ONE_EXECUTABLE=bennysh
PART_ONE_OBJECT=bennysh.o cmd_parse.o
PART_ONE_SOURCE_FILES=bennysh.c cmd_parse.c

all: $(PART_ONE_EXECUTABLE)

$(PART_ONE_EXECUTABLE): $(PART_ONE_OBJECT)

$(PART_ONE_OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(PART_ONE_SOURCE_FILES)

clean:
	rm $(PART_ONE_EXECUTABLE) *.o
