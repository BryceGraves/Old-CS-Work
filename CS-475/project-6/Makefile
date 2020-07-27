# Global variables used for compiling and linking
COMPILER=g++
COMPILER_FLAGS=-lm -fopenmp -o $(EXECUTABLE)
SOURCES=project_6.cpp /usr/lib/x86_64-linux-gnu/libOpenCL.so
EXECUTABLE=project_6

# Calls executable to start dependency chain
all: $(EXECUTABLE)

# Called to create an executable by linking made object files
$(EXECUTABLE): $(SOURCES)
	$(COMPILER) $(SOURCES) $(COMPILER_FLAGS)

clean:
	rm $(EXECUTABLE)

info:
	g++ -o printinfo printinfo.cpp /usr/lib/x86_64-linux-gnu/libOpenCL.so -lm -fopenmp