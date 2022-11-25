#Global variables used for compiling
COMPILER=g++
COMPILER_FLAGS=-o
SOURCES=delete.cpp
EXECUTABLE=main

#Calls executable to start dependency chain
all: $(EXECUTABLE)

#Called to create executable
$(EXECUTABLE): $(OBJECTS)
	$(COMPILER) $(SOURCES) $(COMPILER_FLAGS) $(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)
