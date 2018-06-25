#Global variables used for compiling and linking
COMPILER=nasm
LINKER=ld
COMPILER_FLAGS=-f elf -gddb -F stabs
LINKER_FLAGS=
SOURCES=hw4.asm
OBJECTS=hw4.o
EXECUTABLE=hw4

#Calls executable to start chain
all: $(EXECUTABLE)

#Called to create executable by linking made object files
$(EXECUTABLE): $(OBJECTS)
	$(LINKER) $(LINKER_FLAGS) $(OBJECTS) -o $(EXECUTABLE)

#Called by dependency, compiles files into object files to be linked
$(OBJECTS): $(SOURCES)
	$(COMPILER) $(COMPILER_FLAGS) $(SOURCES)

clean:
	rm $(EXECUTABLE) $(OBJECTS)


