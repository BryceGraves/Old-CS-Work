#Global variables used for compiling and linking
COMPILER=nasm
LINKER=ld
CLEANER=rm
COMPILER_FLAGS=-f elf -g -F stabs
SOURCES=hw5.asm
OBJECTS=hw5.o
EXECUTABLE=hw5

#Calls executable to start dependency chain
all: $(EXECUTABLE)

#Called to creat executable by linking made object files
$(EXECUTABLE): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) $(OBJECTS) -o $(EXECUTABLE)

#Called by dependency, compiles files into object files to be linked
$(OBJECTS): $(SOURCES)
	$(COMPILER) $(COMPILER_FLAGS) $(SOURCES)

clean:
	$(CLEANER) $(EXECUTABLE) $(OBJECTS)
