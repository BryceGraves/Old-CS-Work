#Global variables used for compiling
#Remember to take out the flippin c90 flag
COMPILER=gcc
COMPILER_FLAGS=-g -c -pthread -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra -Werror -Wunsafe-loop-optimizations -pthread
LINKING_FLAGS= -lpthread
SERVER_EXE=server
SERVER_OBJECT=server.o
SERVER_SOURCE_FILE=server.c
CLIENT_EXE=client
CLIENT_OBJECT=client.o
CLIENT_SOURCE_FILE=client.c

all: $(SERVER_EXE) $(CLIENT_EXE)

$(SERVER_EXE): $(LINKING_FLAGS) $(SERVER_OBJECT)

$(SERVER_OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(SERVER_SOURCE_FILE)

$(CLIENT_EXE): $(LINKING_FLAGS) $(CLIENT_OBJECT)

$(CLIENT_OBJECT):
	$(COMPILER) $(COMPILER_FLAGS) $(CLIENT_SOURCE_FILE)

clean:
	rm $(SERVER_EXE) $(CLIENT_EXE) *.o
