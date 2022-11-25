CC = gcc
DEBUG = -g -ggdb
DEFINES = -pthread

CFLAGS = $(DEBUG) -Wall -Wshadow -Wunreachable-code -Wredundant-decls \
	-Wmissing-declarations -Wold-style-definition -Wmissing-prototypes \
	-Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized \
	$(DEFINES)
PROG1 = gen_data
SRCS1 = \
	$(PROG1).c \
	$(EMPTY)
OBJS1 = $(SRCS1:.c=.o)

PROG2 = dot_prod_MT
SRCS2 = \
	$(PROG2).c \
	$(EMPTY)
OBJS2 = $(SRCS2:.c=.o)

PROG3 = dot_prod
SRCS3 = \
	$(PROG3).c \
	$(EMPTY)
OBJS3 = $(SRCS3:.c=.o)

PROG4 = dot_prod_Student
SRCS4 = \
	$(PROG4).c \
	$(EMPTY)
OBJS4 = $(SRCS4:.c=.o)

PROGS = $(PROG4)

all: $(PROGS)

$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) -o $@ $^

$(PROG1).o: $(PROG1).c
	$(CC) $(CFLAGS) -c $<

$(PROG2): $(OBJS2)
	$(CC) $(CFLAGS) -o $@ $^

$(PROG2).o: $(PROG2).c
	$(CC) $(CFLAGS) -c $<

$(PROG3): $(OBJS3)
	$(CC) $(CFLAGS) -o $@ $^

$(PROG3).o: $(PROG3).c
	$(CC) $(CFLAGS) -c $<

$(PROG4): $(OBJS4)
	$(CC) $(CFLAGS) -o $@ $^

$(PROG4).o: $(PROG4).c
	$(CC) $(CFLAGS) -c $<

opt:
	make clean all DEBUG="-Ofast -ffinite-math-only -fno-math-errno"

# clean up the compiled files and editor chaff
clean cls:
	rm -f $(PROGS) *.o *~ \#*

ci:
	ci -l -m"lazy checkin" *.[ch] [mM]akefile
