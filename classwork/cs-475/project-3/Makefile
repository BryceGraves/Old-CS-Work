# Global variables used for compiling and linking
COMPILER=g++
COMPILER_FLAGS=-lm -fopenmp -o $(EXECUTABLE)
SOURCES=project_3.cpp
EXECUTABLE=project_3

# Calls executable to start dependency chain
all: $(EXECUTABLE)

# Called to create an executable by linking made object files
$(EXECUTABLE): $(SOURCES)
	$(COMPILER) $(SOURCES) $(COMPILER_FLAGS)

clean:
	rm $(EXECUTABLE)
