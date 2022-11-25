# Global variables used for compiling and linking
COMPILER=g++
COMPILER_FLAGS=-lm -fopenmp -o $(EXECUTABLE)
SOURCES=project-1.cpp
EXECUTABLE=project-1

# Calls executable to start dependency chain
all: $(EXECUTABLE)

# Called to create an executable by linking made object files
$(EXECUTABLE): $(SOURCES)
	$(COMPILER) $(SOURCES) $(COMPILER_FLAGS)

clean:
	rm project-1
