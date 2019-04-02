#
# R Jesse Chaney
# 

CC = gcc
DEBUG = -g -ggdb
OPT = -O3 -fno-math-errno
VERBOSE = -DALLOW_VERBOSE
DEFINES = -DDEBUG $(VERBOSE)
LDFLAGS = 
BITS    = -DBITS=uint32_t

CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wunsafe-loop-optimizations \
	$(DEFINES)

PROG1 = primesMT
SRCS1 = \
	$(PROG1).c \
	$(EMPTY)
HEADERS1 = \
	$(EMPTY)
OBJS1 = $(SRCS1:.c=.o)

PROG2 = fifo_server
SRCS2 = \
	$(PROG2).c \
	$(EMPTY)
HEADERS2 = \
	fifo_cs.h \
	$(EMPTY)
OBJS2 = $(SRCS2:.c=.o)

PROG3 = fifo_client
SRCS3 = \
	$(PROG3).c \
	$(EMPTY)
HEADERS3 = \
	fifo_cs.h \
	$(EMPTY)
OBJS3 = $(SRCS3:.c=.o)

PROG4 = fifo_server_student
SRCS4 = \
	$(PROG4).c \
	$(EMPTY)
HEADERS4 = \
	fifo_cs.h \
	$(EMPTY)
OBJS4 = $(SRCS4:.c=.o)

PROG5 = fifo_client_student
SRCS5 = \
	$(PROG5).c \
	$(EMPTY)
HEADERS5 = \
	fifo_cs.h \
	$(EMPTY)
OBJS5 = $(SRCS5:.c=.o)


PROGS = $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5)


all: $(PROGS)


$(PROG1): $(PROG1).o
	$(CC) $(CFLAGS) -pthread -o $@ $^ -lm
	chmod a+rx $(PROG1)

$(PROG1).o: $(PROG1).c $(HEADERS1)
	$(CC) $(CFLAGS) -pthread $(BITS) -c $<

$(PROG2): $(OBJS2)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	chmod a+rx $(PROG2)

$(PROG2).o: $(PROG2).c $(HEADERS2)
	$(CC) $(CFLAGS) -c $<

$(PROG3): $(OBJS3)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	chmod a+rx $(PROG3)

$(PROG3).o: $(PROG3).c $(HEADERS3)
	$(CC) $(CFLAGS) -c $<


$(PROG4): $(OBJS4)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	chmod a+rx $(PROG4)

$(PROG4).o: $(PROG4).c $(HEADERS4)
	$(CC) $(CFLAGS) -c $<

$(PROG5): $(OBJS5)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	chmod a+rx $(PROG5)

$(PROG5).o: $(PROG5).c $(HEADERS5)
	$(CC) $(CFLAGS) -c $<


u8: clean
	make BITS=-DBITS=uint8_t DEBUG="$(OPT)"

u16: clean
	make BITS=-DBITS=uint16_t DEBUG="$(OPT)"

u32: clean
	make BITS=-DBITS=uint32_t DEBUG="$(OPT)"

u64: clean
	make BITS=-DBITS=uint64_t DEBUG="$(OPT)"

u128: clean
	make BITS="-DBITS=__uint128_t -DD128" DEBUG="$(OPT)"

prof gprof: clean
	make DEBUG="$(DEBUG) -pg"

detail: clean
	make DEBUG="$(DEBUG) -Q"

opt: clean
	$(MAKE) DEBUG="$OPT" DEFINES= BITS=-DBITS=__uint128_t LDFLAGS=-s

# clean up the compiled files and editor chaff
clean cls:
	rm -f $(PROGS) *.o *~ \#*

ci:
	ci -m"Lazy Check-in" -l *.[ch] [mM]akefile *.bash

#	git add *.c [mM]akefile *.bash
#	git commit -m "lazy commit"
