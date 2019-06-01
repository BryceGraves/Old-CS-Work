CC = gcc
DEBUG = -g
DEFINES = 

CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
        -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
        -Wdeclaration-after-statement $(DEFINES)
PROGS = beavalloc


all: $(PROGS)


beavalloc: beavalloc.o main.o
	$(CC) $(CFLAGS) -o $@ $^
	chmod a+rx,g-w $@

beavalloc.o: beavalloc.c beavalloc.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c beavalloc.h
	$(CC) $(CFLAGS) -c $<

# clean up the compiled files and editor chaff
clean:
	rm -f $(PROGS) *.o *~ \#*
