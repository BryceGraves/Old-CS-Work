# Global variables used for compiling and linking
COMPILER=g++
COMPILER_FLAGS=-lm -fopenmp -o $(EXECUTABLE)
SOURCES=project-0.cpp
EXECUTABLE=project-0

# Calls executable to start dependency chain
all: $(EXECUTABLE)

# Called to create an executable by linking made object files
$(EXECUTABLE): $(SOURCES)
	$(COMPILER) $(SOURCES) $(COMPILER_FLAGS)

clean:
	rm project-0

test:
	./project-0 -v -s 600 -t 10
