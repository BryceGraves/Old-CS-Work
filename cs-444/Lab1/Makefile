#Global variables used for compiling
#Remember to take out the flippin' c90 flag
COMPILER=gcc
COMPILER_FLAGS=-g -Wall -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized -Wextra -Werror -Wunsafe-loop-optimizations -o
EXECUTABLES= fork_1 fork_2 fork_3 fork_4
EXEC_ONE= fork_1
EXEC_TWO= fork_2
EXEC_THREE= fork_3
EXEC_FOUR= fork_4
SRC_ONE= fork_1.c
SRC_TWO= fork_2.c
SRC_THREE= fork_3.c
SRC_FOUR= fork_4.c

all: $(EXECUTABLES)

$(EXEC_ONE):
	$(COMPILER) $(COMPILER_FLAGS) $(EXEC_ONE) $(SRC_ONE)

$(EXEC_TWO):
	$(COMPILER) $(COMPILER_FLAGS) $(EXEC_TWO) $(SRC_TWO)

$(EXEC_THREE):
	$(COMPILER) $(COMPILER_FLAGS) $(EXEC_THREE) $(SRC_THREE)

$(EXEC_FOUR):
	$(COMPILER) $(COMPILER_FLAGS) $(EXEC_FOUR) $(SRC_FOUR)

clean:
	rm $(EXECUTABLES)
